package sk.breviar.android;

import java.io.File;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/** Integration checks against real CGI exports; no Android SDK or device needed. */
public final class SettingsXmlTest {
  private static File root;
  private static int roundTrips;

  private static void check(boolean condition, String message) {
    if (!condition) throw new AssertionError(message);
  }

  private static String export(Map<String, String> params) throws Exception {
    StringBuilder query = new StringBuilder("qt=pxml&d=13&m=10&r=2026");
    for (Map.Entry<String, String> entry : params.entrySet()) {
      query.append('&').append(URLEncoder.encode(entry.getKey(), "UTF-8"))
          .append('=').append(URLEncoder.encode(entry.getValue(), "UTF-8"));
    }
    ProcessBuilder builder = new ProcessBuilder(new File(root, "l.cgi").getPath());
    builder.directory(root);
    builder.environment().put("REQUEST_METHOD", "GET");
    builder.environment().put("QUERY_STRING", query.toString());
    builder.redirectError(ProcessBuilder.Redirect.INHERIT);
    Process process = builder.start();
    String output = new String(process.getInputStream().readAllBytes(), StandardCharsets.UTF_8);
    check(process.waitFor() == 0, "CGI export failed");
    int start = output.indexOf("<?xml");
    check(start >= 0, "CGI returned no XML");
    return output.substring(start);
  }

  private static SettingsXml.Option option(SettingsXml.Group group, String name) {
    for (SettingsXml.Option option : group.options) {
      if (option.element.equals(name)) return option;
    }
    throw new AssertionError("Missing option " + name);
  }

  private static void checkLabel(String label) {
    check(!label.isEmpty(), "Empty native label");
    check(!Character.isLowerCase(label.codePointAt(0)), "Uncapitalized native label: " + label);
    check(!label.matches("(?i)[a-z0-9]+_text"), "Placeholder shown as a native label: " + label);
  }

  private static void checkMenu(List<SettingsXml.MenuEntry> entries, Map<String, SettingsXml.MenuEntry> visibleOptions) {
    for (SettingsXml.MenuEntry entry : entries) {
      if (!entry.label.isEmpty()) checkLabel(entry.label);
      check(!entry.label.contains("<"), "HTML in menu label");
      if (entry.option != null) visibleOptions.put(entry.option.element, entry);
      checkMenu(entry.children, visibleOptions);
    }
  }

  public static void main(String[] args) throws Exception {
    root = new File(args[0]).getCanonicalFile();
    for (String language : new String[]{"sk", "cz", "c2", "hu", "la", "is"}) {
      Map<String, String> params = new HashMap<>();
      params.put("j", language);
      params.put("css", "custom.css");
      params.put("o6", "100");
      String xml = export(params);
      List<SettingsXml.Language> languages = SettingsXml.parseLanguages(xml);
      Map<String, String> locales = new HashMap<>();
      for (SettingsXml.Language entry : languages) {
        checkLabel(entry.label);
        locales.put(entry.value, entry.locale);
      }
      for (String code : new String[]{"sk", "cz", "c2", "hu", "la", "is"}) {
        String expected = code.equals("cz") || code.equals("c2") ? "cs" : code;
        check(expected.equals(locales.get(code)), "Missing or incorrect locale for " + code);
      }
      SettingsXml settings = SettingsXml.parse(xml);
      Map<String, SettingsXml.MenuEntry> visibleOptions = new HashMap<>();
      checkMenu(settings.menu, visibleOptions);
      check(settings.findEntry("calendar").children.size() == 1, "Missing nested calendar settings");
      check(settings.findEntry("language").choices.size() == languages.size(), "Language choices differ");
      check(settings.findGroup("o6") == null, "Contextual alternatives must stay in prayers");
      check(settings.groups.size() >= 4, "Missing groups for " + language);
      for (SettingsXml.Group group : settings.groups) {
        checkLabel(group.label);
        long initial = group.value;
        for (SettingsXml.Option option : group.options) {
          // Only Menu entries are editable; raw metadata also contains internal renderer flags.
          if (!visibleOptions.containsKey(option.element)) continue;
          Map<String, String> edited = new HashMap<>(params);
          visibleOptions.get(option.element).setValue(edited, group.isChecked(option) ? "0" : "1");
          SettingsXml reloaded = SettingsXml.parse(export(edited));
          check(reloaded.findGroup(group.name).value == group.value,
              language + ": round trip failed for " + option.element);
          check(edited.get("css").equals("custom.css") && edited.get("o6").equals("100"),
              "Unrelated settings lost");
          ++roundTrips;
          group.value = initial;
        }
        for (SettingsXml.Choice choice : group.choices) {
          checkLabel(choice.label);
          Map<String, String> edited = new HashMap<>(params);
          edited.put("of3", "0");
          settings.findEntry("prayers.common").setValue(edited, choice.value);
          check(!edited.containsKey("of3"), "Stale communia override retained");
          SettingsXml.Group reloaded = SettingsXml.parse(export(edited)).findGroup(group.name);
          // The renderer canonicalizes translated aliases (e.g. Icelandic 27 -> 4).
          String selectedLabel = null;
          for (SettingsXml.Choice current : reloaded.choices) {
            if (current.value.equals(Long.toString(reloaded.value))) selectedLabel = current.label;
          }
          check(choice.label.equals(selectedLabel), "Communia selection lost: " + choice.value);
          ++roundTrips;
          group.value = initial;
        }
      }
      boolean selectedFound = false;
      for (SettingsXml.Choice calendar : settings.calendars) {
        // A single calendar has no selector; some languages export no label.
        if (settings.calendars.size() > 1 || !calendar.label.isEmpty()) checkLabel(calendar.label);
        if (calendar.value.equals(settings.selectedCalendar)) selectedFound = true;
        Map<String, String> edited = new HashMap<>(params);
        settings.findEntry("calendar").setValue(edited, calendar.value);
        check(SettingsXml.parse(export(edited)).selectedCalendar.equals(calendar.value),
            "Calendar selection lost for " + language + ": " + calendar.value);
        ++roundTrips;
      }
      check(selectedFound, "No selected calendar for " + language);
      System.out.println(language + ": localized settings, choices and calendars passed");
    }

    Map<String, String> overrides = new HashMap<>();
    overrides.put("j", "sk");
    overrides.put("of0", "8835");
    overrides.put("of0v", "1");
    overrides.put("of0uac", "1");
    overrides.put("of0fn", "1"); // a setting still owned by DisplaySettings
    overrides.put("of1r", "1"); // an unrelated group must be left alone
    SettingsXml.Group group = SettingsXml.parse(export(overrides)).findGroup("o0");
    long original = group.value;
    SettingsXml.Option verses = option(group, "BitOpt0VerseNumbers");
    group.setChecked(overrides, verses, false);
    check(!overrides.containsKey("of0") && !overrides.containsKey("of0v")
        && !overrides.containsKey("of0uac") && !overrides.containsKey("of0fn"),
        "Stale full-word or per-bit overrides retained");
    check(overrides.get("of1r").equals("1"), "Another group's override was removed");
    check(group.value == (original & ~1L), "Hidden or unmodified bits changed");
    check(SettingsXml.parse(export(overrides)).findGroup("o0").value == group.value,
        "Legacy overrides undid the native setting");

    // Returning to an existing WebView URL must not revive overrides removed
    // from preferences; keep date/prayer navigation and untouched groups.
    Map<String, String> readerUrl = new HashMap<>();
    readerUrl.put("d", "13");
    readerUrl.put("p", "mc");
    readerUrl.put("of0v", "1");
    readerUrl.put("of0", "8835");
    readerUrl.put("of2hk", "1");
    SettingsXml.applySavedOptions(readerUrl, overrides);
    check(!readerUrl.containsKey("of0") && !readerUrl.containsKey("of0v"),
        "Reader URL revived a removed override");
    check(readerUrl.get("of2hk").equals("1") && readerUrl.get("d").equals("13")
        && readerUrl.get("p").equals("mc"), "Unrelated reader parameters changed");
    check(SettingsXml.parse(export(readerUrl)).findGroup("o0").value == group.value,
        "Reader URL ignored saved options");

    group.value |= 1L << 40; // preserve bits unknown to this app version
    group.setChecked(overrides, verses, true);
    check((Long.parseLong(overrides.get("o0")) & (1L << 40)) != 0, "Unknown bit lost");
    SettingsXml.Option references = option(group, "BitOpt0References");
    SettingsXml.Option bibleCom = option(group, "BitOpt0ReferencesBibleDotCom");
    group.setChecked(overrides, bibleCom, true);
    check(group.isChecked(references), "bible.com must enable references");
    group.setChecked(overrides, references, false);
    check(!group.isChecked(bibleCom), "Disabling references must disable bible.com");

    String labelsXml = "<LHData><Menu Version='1'><MenuGroup Key='test' Label='žalm ABC:'>"
        + "<MenuItem Key='flag' Label='&lt;b&gt;číslovanie veršov&lt;/b&gt;' Control='toggle' OptionRef='Flag'/>"
        + "</MenuGroup></Menu><SupportedLanguages><Language Value='sk' Locale='sk'>slovenčina</Language>"
        + "</SupportedLanguages><Options><Opt Name='o0' Value='0' Text='  žalm ABC:  '>"
        + "<Flag Id='1' Text='&lt;b&gt;číslovanie veršov&lt;/b&gt;'/>"
        + "<Unused Id='2' Text='hu_text'/><Empty Id='4' Text='  '/>"
        + "</Opt></Options><SupportedValues><LiturgicalCalendarValues Name='k' Value=''>"
        + "<Calendar>íslenska</Calendar></LiturgicalCalendarValues></SupportedValues></LHData>";
    SettingsXml labels = SettingsXml.parse(labelsXml);
    check(labels.groups.get(0).label.equals("Žalm ABC"), "Title casing changed the rest of the label");
    check(labels.groups.get(0).options.size() == 3, "Hidden option state lost");
    check(labels.menu.get(0).children.size() == 1, "Non-menu options leaked into presentation");
    check(labels.groups.get(0).options.get(0).label.equals("Číslovanie veršov"), "Accented label not capitalized");
    check(labels.calendars.get(0).label.equals("Íslenska"), "Calendar label not capitalized");

    for (String invalid : new String[]{labelsXml.replace("Version='1'", "Version='2'"),
        labelsXml.replace("OptionRef='Flag'", "OptionRef='Missing'"),
        labelsXml.replace("OptionRef='Flag'", "OptionRef='Flag' Parameter='o0'"),
        labelsXml.replace("Key='flag'", "Key='test'"),
        labelsXml.replace("OptionRef='Flag'", "ValuesRef='Missing'"),
        "<html/>", "<LHData/>",
        "<!DOCTYPE LHData [<!ENTITY x SYSTEM 'file:///no-such-file'>]><LHData>&x;</LHData>"}) {
      try {
        SettingsXml.parse(invalid);
        throw new AssertionError("Invalid export accepted");
      } catch (IllegalArgumentException expected) {
        // The activity turns invalid exports into a retry row.
      }
    }
    // Language discovery is independent of calendars/options and enum indices.
    List<SettingsXml.Language> languages = SettingsXml.parseLanguages(
        "<LHData><SupportedLanguages Name='j'>"
        + "<Language Id='987' Value='custom' Locale='pt-BR'>português</Language>"
        + "</SupportedLanguages></LHData>");
    check(languages.size() == 1 && languages.get(0).value.equals("custom")
        && languages.get(0).locale.equals("pt-BR") && languages.get(0).label.equals("Português"),
        "Language metadata lost");
    for (String invalid : new String[]{"<html/>", "<LHData/>",
        "<LHData><SupportedLanguages/></LHData>",
        "<LHData><SupportedLanguages><Language Value='cz'>Czech</Language></SupportedLanguages></LHData>",
        "<LHData><SupportedLanguages><Language Value='cz' Locale='cs'>Czech</Language>"
            + "<Language Value='cz' Locale='cs'>Duplicate</Language></SupportedLanguages></LHData>",
        "<!DOCTYPE LHData [<!ENTITY x SYSTEM 'file:///no-such-file'>]><LHData>&x;</LHData>"}) {
      try {
        SettingsXml.parseLanguages(invalid);
        throw new AssertionError("Invalid language export accepted");
      } catch (IllegalArgumentException expected) {
        // Keep existing locale preferences if an export cannot be loaded.
      }
    }
    System.out.println("Passed " + roundTrips + " CGI round trips, legacy overrides and parser checks");
  }
}

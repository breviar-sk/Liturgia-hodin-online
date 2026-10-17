package sk.breviar.android;

import java.io.StringReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

/** The same settings export consumed by the iOS app. */
public final class SettingsXml {
  public static final class Language {
    public final String value, locale, label;

    Language(Element element) {
      value = element.getAttribute("Value");
      locale = element.getAttribute("Locale");
      label = label(element.getTextContent());
      if (value.isEmpty() || locale.isEmpty() || label.isEmpty()) {
        throw new IllegalArgumentException("Incomplete language metadata");
      }
    }
  }

  public static final class Option {
    public final String element, label;
    public final long mask;

    Option(Element element) {
      this.element = element.getTagName();
      label = label(element.getAttribute("Text"));
      mask = Long.parseLong(element.getAttribute("Id"));
    }
  }

  public static final class Choice {
    public final String value, label;

    Choice(String value, String label) {
      this.value = value;
      this.label = label(label);
    }
  }

  public static final class Group {
    public final String name, label;
    public long value;
    public final List<Option> options = new ArrayList<>();
    public final List<Choice> choices = new ArrayList<>();
    private final List<String> forceNames = new ArrayList<>();

    Group(Element element) {
      name = element.getAttribute("Name");
      label = label(element.getAttribute("Text"));
      value = Long.parseLong(element.getAttribute("Value"));
      forceNames.add(element.getAttribute("ForceName"));
    }

    public boolean isChecked(Option option) {
      return (value & option.mask) != 0;
    }

    public void setChecked(Map<String, String> params, Option option, boolean checked) {
      value = checked ? value | option.mask : value & ~option.mask;
      // Preserve the relationship already enforced by the Android prayer menu.
      if (option.element.equals("BitOpt0References") && !checked) {
        setRelated("BitOpt0ReferencesBibleDotCom", false);
      } else if (option.element.equals("BitOpt0ReferencesBibleDotCom") && checked) {
        setRelated("BitOpt0References", true);
      }
      save(params);
    }

    private void setRelated(String element, boolean checked) {
      for (Option option : options) {
        if (option.element.equals(element)) {
          value = checked ? value | option.mask : value & ~option.mask;
        }
      }
    }

    public void select(Map<String, String> params, String selected) {
      for (Choice choice : choices) {
        if (choice.value.equals(selected)) {
          value = Long.parseLong(selected);
          save(params);
          return;
        }
      }
      throw new IllegalArgumentException("Unknown choice for " + name);
    }

    void save(Map<String, String> params) {
      // value is the effective word returned by C++, including unlisted bits.
      // Old per-bit overrides must not undo the newly selected value.
      for (String forceName : forceNames) params.remove(forceName);
      params.put(name, Long.toString(value));
    }
  }

  public final List<Group> groups = new ArrayList<>();
  public final List<Choice> calendars = new ArrayList<>();
  public String calendarParameter;
  public String selectedCalendar;

  /** Presentation metadata; option words remain the single source of renderer state. */
  public static final class MenuEntry {
    public final String key, label, control, parameter, handler;
    public final boolean isGroup;
    public final String defaultValue, resetValue;
    public final Integer min, max;
    public final List<MenuEntry> children = new ArrayList<>();
    public final List<Choice> choices = new ArrayList<>();
    public Group optionGroup;
    public Option option;
    private String selectedValue;

    MenuEntry(Element element) {
      key = element.getAttribute("Key");
      label = label(element.getAttribute("Label"));
      isGroup = element.getTagName().equals("MenuGroup");
      control = element.getAttribute("Control");
      parameter = element.getAttribute("Parameter");
      handler = element.getAttribute("Handler");
      defaultValue = attribute(element, "Default");
      resetValue = attribute(element, "ResetValue");
      min = element.hasAttribute("Min") ? Integer.valueOf(element.getAttribute("Min")) : null;
      max = element.hasAttribute("Max") ? Integer.valueOf(element.getAttribute("Max")) : null;
      if (key.isEmpty()) throw new IllegalArgumentException("Missing menu key");
    }

    public String value(Map<String, String> params) {
      if (option != null) return optionGroup.isChecked(option) ? "1" : "0";
      if (optionGroup != null) return Long.toString(optionGroup.value);
      if (selectedValue != null) return selectedValue;
      String value = params.get(parameter);
      return value == null || value.isEmpty() ? (defaultValue == null ? "" : defaultValue) : value;
    }

    public void setValue(Map<String, String> params, String value) {
      if (control.equals("choice") && !choices.isEmpty()) {
        boolean found = false;
        for (Choice choice : choices) if (choice.value.equals(value)) found = true;
        if (!found) throw new IllegalArgumentException("Unknown choice for " + key);
      }
      if (option != null) {
        optionGroup.setChecked(params, option, value.equals("1"));
      } else if (optionGroup != null) {
        optionGroup.value = Long.parseLong(value);
        optionGroup.save(params);
      } else if (!parameter.isEmpty()) {
        // Empty ResetValue is an explicit assignment, never a deletion.
        params.put(parameter, value);
        if (selectedValue != null) selectedValue = value;
      } else {
        throw new IllegalStateException("Native handler owns " + key);
      }
    }
  }

  public final List<MenuEntry> menu = new ArrayList<>();
  public final List<Language> languages = new ArrayList<>();
  private final Map<String, MenuEntry> entries = new LinkedHashMap<>();

  public MenuEntry findEntry(String key) { return entries.get(key); }

  private static String attribute(Element element, String name) {
    return element.hasAttribute(name) ? element.getAttribute(name) : null;
  }

  private static Element parseDocument(String xml) throws Exception {
    // Android's DOM factory does not support Xerces' disallow-doctype feature.
    // This export has no DTD; reject one before parsing on either platform.
    if (xml.contains("<!DOCTYPE")) throw new IllegalArgumentException("Unexpected DTD");
    DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
    factory.setExpandEntityReferences(false);
    DocumentBuilder builder = factory.newDocumentBuilder();
    builder.setEntityResolver((publicId, systemId) -> {
      throw new SAXException("Unexpected external entity");
    });
    Document document = builder.parse(new InputSource(new StringReader(xml)));
    if (!document.getDocumentElement().getTagName().equals("LHData")) {
      throw new IllegalArgumentException("Expected LHData settings export");
    }
    return document.getDocumentElement();
  }

  public static List<Language> parseLanguages(String xml) throws Exception {
    return parseLanguages(parseDocument(xml));
  }

  private static List<Language> parseLanguages(Element root) {
    Element supported = child(root, "SupportedLanguages");
    if (supported == null) throw new IllegalArgumentException("Missing supported languages");
    List<Language> languages = new ArrayList<>();
    Set<String> values = new HashSet<>();
    for (Element element : children(supported)) {
      if (!element.getTagName().equals("Language")) continue;
      Language language = new Language(element);
      if (!values.add(language.value)) throw new IllegalArgumentException("Duplicate language");
      languages.add(language);
    }
    if (languages.isEmpty()) throw new IllegalArgumentException("No supported languages");
    return languages;
  }

  public static SettingsXml parse(String xml) throws Exception {
    Element root = parseDocument(xml);
    SettingsXml result = new SettingsXml();
    Element options = child(root, "Options");
    if (options == null) throw new IllegalArgumentException("Missing settings options");
    for (Element element : children(options)) {
      String name = element.getAttribute("Name");
      // o6 describes context-specific, decimal-place alternatives, not flags.
      // They remain selectable in the prayer, as on iOS; the form uses o0-o5.
      if (!Arrays.asList("o0", "o1", "o2", "o3", "o5").contains(name)) continue;
      Group group = new Group(element);
      for (Element bit : children(element)) {
        group.forceNames.add(bit.getAttribute("ForceName"));
        Option option = new Option(bit);
        if (option.mask <= 0 || (option.mask & (option.mask - 1)) != 0) {
          throw new IllegalArgumentException("Invalid option mask");
        }
        group.options.add(option);
      }
      result.groups.add(group);
    }

    Element supported = child(root, "SupportedValues");
    if (supported == null) throw new IllegalArgumentException("Missing supported values");
    Element calendars = child(supported, "LiturgicalCalendarValues");
    if (calendars == null) throw new IllegalArgumentException("Missing calendars");
    result.calendarParameter = calendars.getAttribute("Name");
    result.selectedCalendar = calendars.getAttribute("Value");
    for (Element calendar : children(calendars)) {
      // The general calendar has no Value: the empty parameter selects it.
      result.calendars.add(new Choice(calendar.getAttribute("Value"), calendar.getTextContent()));
    }
    Element communia = child(supported, "LiturgicalCelebrationCommuniaValues");
    for (Group group : result.groups) {
      if (group.name.equals("o3") && communia != null) {
        for (Element choice : children(communia)) {
          if (usableLabel(choice.getTextContent())) {
            group.choices.add(new Choice(choice.getAttribute("Id"), choice.getTextContent()));
          }
        }
      }
    }
    if (result.groups.isEmpty() || result.calendars.isEmpty() || result.calendarParameter.isEmpty()) {
      throw new IllegalArgumentException("Incomplete settings export");
    }
    result.languages.addAll(parseLanguages(root));
    Element menu = child(root, "Menu");
    if (menu == null || !menu.getAttribute("Version").equals("1")) {
      throw new IllegalArgumentException("Expected Menu version 1");
    }
    for (Element element : children(menu)) {
      if (element.getTagName().equals("MenuGroup")) result.menu.add(result.parseEntry(element, root));
    }
    if (result.menu.isEmpty()) throw new IllegalArgumentException("Missing menu groups");
    return result;
  }

  private MenuEntry parseEntry(Element element, Element root) {
    MenuEntry entry = new MenuEntry(element);
    if (entries.put(entry.key, entry) != null) throw new IllegalArgumentException("Duplicate menu key");
    String reference = element.getAttribute("OptionRef");
    if (!reference.isEmpty()) {
      if (!entry.parameter.isEmpty()) throw new IllegalArgumentException("Conflicting menu bindings");
      Element options = child(root, "Options");
      for (Element word : children(options)) {
        Group group = findGroup(word.getAttribute("Name"));
        if (group == null) continue;
        if (word.getTagName().equals(reference)) entry.optionGroup = group;
        for (Option bit : group.options) {
          if (bit.element.equals(reference)) {
            entry.optionGroup = group;
            entry.option = bit;
          }
        }
      }
      if (entry.optionGroup == null) throw new IllegalArgumentException("Unknown OptionRef: " + reference);
    }
    String valuesRef = element.getAttribute("ValuesRef");
    if (!valuesRef.isEmpty()) {
      Element values = child(root, valuesRef);
      if (values == null) values = child(child(root, "SupportedValues"), valuesRef);
      if (values == null) throw new IllegalArgumentException("Unknown ValuesRef: " + valuesRef);
      entry.selectedValue = attribute(values, "Value");
      String valueAttribute = element.hasAttribute("ValueAttribute") ? element.getAttribute("ValueAttribute") : "Value";
      for (Element choice : children(values)) {
        // A missing calendar Value denotes the default; its label can be empty.
        if (valuesRef.equals("LiturgicalCelebrationCommuniaValues") && !usableLabel(choice.getTextContent())) continue;
        entry.choices.add(new Choice(choice.getAttribute(valueAttribute), choice.getTextContent()));
      }
    }
    for (Element child : children(element)) {
      if (child.getTagName().equals("MenuGroup") || (entry.isGroup && child.getTagName().equals("MenuItem"))) {
        entry.children.add(parseEntry(child, root));
      }
    }
    return entry;
  }

  public Group findGroup(String name) {
    for (Group group : groups) if (group.name.equals(name)) return group;
    return null;
  }

  /** Apply canonical saved words without reviving an override in the reader URL. */
  public static void applySavedOptions(Map<String, String> current, Map<String, String> saved) {
    current.keySet().removeIf(key -> key.matches("of[0-6].*")
        && saved.containsKey("o" + key.charAt(2)));
    current.putAll(saved);
  }

  private static boolean usableLabel(String text) {
    String label = plainLabel(text);
    return !label.isEmpty() && !label.equals("/") && !label.matches("[a-z0-9]+_text");
  }

  private static String label(String text) {
    String label = plainLabel(text);
    if (label.isEmpty()) return label;
    int first = label.codePointAt(0);
    return new StringBuilder().appendCodePoint(Character.toTitleCase(first))
        .append(label.substring(Character.charCount(first))).toString();
  }

  private static String plainLabel(String text) {
    return text.replaceAll("<[^>]*>", " ").replace('\u00a0', ' ').trim().replaceAll(":$", "").trim();
  }

  private static Element child(Element parent, String name) {
    for (Element element : children(parent)) if (element.getTagName().equals(name)) return element;
    return null;
  }

  private static List<Element> children(Element parent) {
    List<Element> result = new ArrayList<>();
    for (Node node = parent.getFirstChild(); node != null; node = node.getNextSibling()) {
      if (node instanceof Element) result.add((Element)node);
    }
    return result;
  }
}

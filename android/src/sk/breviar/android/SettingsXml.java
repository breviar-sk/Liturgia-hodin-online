package sk.breviar.android;

import java.io.StringReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
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

/** The same Options/SupportedValues export consumed by the iOS app. */
public final class SettingsXml {
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

    private void save(Map<String, String> params) {
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

  // These controls already have Android-specific behavior in DisplaySettings
  // or the reader toolbar. Keep them there, without duplicate menu entries.
  private static final Set<String> NATIVE_OPTIONS = new HashSet<>(Arrays.asList(
      "BitOpt0ForceNormalFontWeight", "BitOpt0ButtonsOrder", "BitOpt0VoiceOutput",
      "BitOpt0TransparentNav", "BitOpt0TransparentNavLeft", "BitOpt0TransparentNavDownOnly",
      "BitOpt0NavigationMenu", "BitOpt2FirstVespersButton", "BitOpt2FontFamily",
      "BitOpt2FontNameChooser", "BitOpt2FontSizeChooser", "BitOpt2Navigation",
      "BitOpt2ButtonsCondensed", "BitOpt2NightMode", "BitOpt2RoundedCorners"));

  public static SettingsXml parse(String xml) throws Exception {
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
    SettingsXml result = new SettingsXml();
    Element options = child(document.getDocumentElement(), "Options");
    if (options == null) throw new IllegalArgumentException("Missing settings options");
    for (Element element : children(options)) {
      String name = element.getAttribute("Name");
      // o6 describes context-specific, decimal-place alternatives, not flags.
      // They remain selectable in the prayer, as on iOS; the form uses o0-o5.
      if (!Arrays.asList("o0", "o1", "o2", "o3", "o5").contains(name)) continue;
      Group group = new Group(element);
      for (Element bit : children(element)) {
        group.forceNames.add(bit.getAttribute("ForceName"));
        if (NATIVE_OPTIONS.contains(bit.getTagName()) || !usableLabel(bit.getAttribute("Text"))) continue;
        Option option = new Option(bit);
        if (option.mask <= 0 || (option.mask & (option.mask - 1)) != 0) {
          throw new IllegalArgumentException("Invalid option mask");
        }
        group.options.add(option);
      }
      if (name.equals("o3") || !group.options.isEmpty()) result.groups.add(group);
    }

    Element supported = child(document.getDocumentElement(), "SupportedValues");
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
    return result;
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

package sk.breviar.android;

import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.os.Build;
import android.view.MenuItem;
import android.widget.Toast;
import java.util.ArrayList;
import java.util.List;

/** Android behavior behind semantic XML handlers. Layout and URL bindings stay in XML. */
final class NativeSettings {
  private final XmlSettingsActivity activity;
  private final FontPicker fonts;

  NativeSettings(XmlSettingsActivity activity) {
    this.activity = activity;
    fonts = new FontPicker(activity, activity::editStarted);
  }

  static boolean supports(SettingsXml.MenuEntry entry) {
    if (!entry.handler.isEmpty()) {
      switch (entry.handler) {
        case "language.select":
        case "reading.navigation": return entry.control.equals("choice");
        case "language.use-for-interface":
        case "device.eink":
        case "device.volume-paging":
        case "device.keep-awake":
        case "device.lock-zoom":
        case "speech.psalm-pauses": return entry.control.equals("toggle");
        case "device.do-not-disturb": return Build.VERSION.SDK_INT >= 24 && entry.control.equals("toggle");
        case "appearance.font": return entry.control.equals("font");
        case "appearance.font-size":
          if (!entry.control.equals("number")) return false;
          break; // Generic numeric editor plus zoom reset.
        case "speech.help": return entry.control.equals("action");
        default: return false; // Includes online/offline and speech rate, not owned by Android.
      }
    }
    boolean bound = entry.optionGroup != null || !entry.parameter.isEmpty();
    switch (entry.control) {
      case "toggle": return bound && (entry.option != null || !entry.parameter.isEmpty());
      case "choice": return bound && !entry.choices.isEmpty();
      case "number": return bound && entry.defaultValue != null && entry.resetValue != null
          && entry.min != null && entry.max != null && entry.min <= entry.max;
      case "color": return bound && entry.defaultValue != null && entry.resetValue != null;
      default: return false;
    }
  }

  boolean bind(MenuItem row, SettingsXml.MenuEntry entry) {
    SettingsActivity.BooleanOption flag = flag(entry.handler);
    if (flag != null) {
      row.setActionView(R.layout.widget_switch);
      row.getActionView().setContentDescription(row.getTitle());
      row.getActionView().setSaveEnabled(false);
      activity.handleSwitch(row.getItemId(), new SettingsActivity.BooleanOption() {
        public boolean get() { return flag.get(); }
        public void set(boolean checked) {
          activity.editStarted();
          flag.set(checked);
        }
      });
      return true;
    }
    if (entry.handler.equals("appearance.font")) {
      fonts.bind(row);
      return true;
    }
    if (entry.handler.equals("speech.help")) {
      row.setActionView(R.layout.widget_submenu);
      activity.handleClick(row.getItemId(), () -> activity.startActivity(new Intent(activity, DialogActivity.class)
          .putExtra("title", R.string.tts_settings_help_title)
          .putExtra("static_text", "qt=pst&st=i&p=2") // INFO_TTS_HELP in liturgia.h
          .putExtra("show_ok", false)));
      return true;
    }
    return false;
  }

  private SettingsActivity.BooleanOption flag(String handler) {
    switch (handler) {
      case "language.use-for-interface": return new SettingsActivity.BooleanOption() {
        public boolean get() { return BreviarApp.getOverrideLocale(activity); }
        public void set(boolean value) { BreviarApp.setOverrideLocale(activity, value); }
      };
      case "device.eink": return new SettingsActivity.BooleanOption() {
        public boolean get() { return BreviarApp.getEinkMode(activity); }
        public void set(boolean value) { activity.changeAppearance(value); }
      };
      case "device.volume-paging": return new SettingsActivity.BooleanOption() {
        public boolean get() { return BreviarApp.getVolButtons(activity); }
        public void set(boolean value) { BreviarApp.setVolButtons(activity, value); }
      };
      case "device.keep-awake": return new SettingsActivity.BooleanOption() {
        public boolean get() { return BreviarApp.getDimLock(activity); }
        public void set(boolean value) { BreviarApp.setDimLock(activity, value); }
      };
      case "device.do-not-disturb": return new SettingsActivity.BooleanOption() {
        public boolean get() { return BreviarApp.getMute(activity) && DoNotDisturb.get(activity).hasAccess(); }
        public void set(boolean value) {
          if (value && !DoNotDisturb.get(activity).hasAccess()) {
            value = false;
            Toast.makeText(activity, R.string.notification_not_allowed, Toast.LENGTH_LONG).show();
            try {
              activity.startActivity(new Intent(android.provider.Settings.ACTION_NOTIFICATION_POLICY_ACCESS_SETTINGS));
            } catch (ActivityNotFoundException error) {
              // Some OEM builds do not provide this settings screen.
            }
          }
          BreviarApp.setMute(activity, value);
        }
      };
      case "device.lock-zoom": return new SettingsActivity.BooleanOption() {
        public boolean get() { return BreviarApp.getNoZoom(activity); }
        public void set(boolean value) { BreviarApp.setNoZoom(activity, value); }
      };
      case "speech.psalm-pauses": return new SettingsActivity.BooleanOption() {
        public boolean get() { return BreviarApp.getTtsUsePauseInPsalms(activity); }
        public void set(boolean value) { BreviarApp.setTtsUsePauseInPsalms(activity, value); }
      };
      default: return null;
    }
  }

  List<SettingsXml.Choice> choices(SettingsXml.MenuEntry entry) {
    if (entry.handler.equals("reading.navigation")) {
      List<SettingsXml.Choice> result = new ArrayList<>();
      for (ReadingNavigation.Mode mode : ReadingNavigation.Mode.values()) {
        result.add(new SettingsXml.Choice(mode.value, activity.getString(mode.label)));
      }
      return result;
    }
    return entry.choices;
  }

  String choiceLabel(SettingsXml.MenuEntry entry, SettingsXml.Choice choice) {
    if (entry.handler.equals("language.select")) {
      int resource = activity.getResources().getIdentifier("lang_" + choice.value, "string", activity.getPackageName());
      if (resource != 0) return activity.getString(resource);
    }
    return choice.label.isEmpty() ? activity.getString(R.string.default_calendar) : choice.label;
  }

  String value(SettingsXml.MenuEntry entry) {
    if (entry.handler.equals("language.select")) return BreviarApp.getString(activity, "language", "sk");
    if (entry.handler.equals("reading.navigation")) return navigationMode().value;
    return entry.value(activity.options().params);
  }

  private UrlOptions navigationOptions() {
    UrlOptions options = activity.options();
    SettingsXml.Group word = activity.settings.findGroup("o0");
    if (word != null) word.save(options.params); // Include effective overrides before editing this word.
    return options;
  }

  ReadingNavigation.Mode navigationMode() {
    return ReadingNavigation.get(activity, navigationOptions());
  }

  boolean select(SettingsXml.MenuEntry entry, String value) {
    if (entry.handler.equals("language.select")) {
      activity.editStarted();
      // The reader owns language-change side effects and its Server instance.
      activity.setResult(activity.RESULT_OK, new Intent().putExtra("lang", value));
      activity.finish();
      return true;
    }
    if (entry.handler.equals("reading.navigation")) {
      activity.editStarted();
      for (ReadingNavigation.Mode mode : ReadingNavigation.Mode.values()) {
        if (mode.value.equals(value)) {
          UrlOptions options = navigationOptions();
          ReadingNavigation.set(activity, mode, options);
          SettingsXml.Group word = activity.settings.findGroup("o0");
          if (word != null) word.value = Long.parseLong(options.params.get("o0"));
          activity.refresh();
          return true;
        }
      }
      throw new IllegalArgumentException("Unknown reading navigation mode");
    }
    return false;
  }

  void beforeSave(SettingsXml.MenuEntry entry) {
    if (entry.handler.equals("appearance.font-size")) BreviarApp.resetScale(activity);
  }

  void clear() { fonts.close(); }
}

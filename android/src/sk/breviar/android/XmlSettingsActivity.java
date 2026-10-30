package sk.breviar.android;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

/** Menu v1 renderer. C++ owns the catalog; NativeSettings supplies Android behavior. */
public class XmlSettingsActivity extends SettingsActivity {
  private static final String GROUP = "settings_group";
  private final ExecutorService worker = Executors.newSingleThreadExecutor();
  private final Map<String, MenuItem> rows = new LinkedHashMap<>();
  private Future<?> pending;
  private int generation;
  private String groupName;
  private NativeSettings nativeSettings;
  SettingsXml settings;

  public static Intent calendarIntent(Context context) { return entryIntent(context, "calendar"); }

  static Intent entryIntent(Context context, String key) {
    return new Intent(context, XmlSettingsActivity.class).putExtra(GROUP, key);
  }

  protected String initialKey() { return getIntent().getStringExtra(GROUP); }

  @Override public void onCreate(Bundle state) {
    super.onCreate(state);
    groupName = initialKey();
    // Preserve restored activity intents from versions that navigated by option word.
    if (groupName != null) {
      switch (groupName) {
        case "o0": case "o1": case "o5": groupName = "prayers"; break;
        case "o2": groupName = "appearance"; break;
        case "o3": groupName = "prayers.common"; break;
      }
    }
    getSupportActionBar().setTitle("language".equals(groupName) ? R.string.lang_select
        : "calendar".equals(groupName) ? R.string.calendar_settings_title : R.string.settings);
    nativeSettings = new NativeSettings(this);
    navigationView.setItemMaxLines(5);
  }

  @Override protected void onResume() {
    super.onResume();
    if (!appearanceChanged()) loadSettings();
  }

  @Override protected void onStop() {
    editStarted();
    super.onStop();
  }

  @Override protected void onDestroy() {
    nativeSettings.clear();
    worker.shutdownNow();
    super.onDestroy();
  }

  void editStarted() {
    ++generation;
    if (pending != null) pending.cancel(false);
  }

  void refresh() {
    updateMenu();
    loadSettings();
  }

  UrlOptions options() { return new UrlOptions(BreviarApp.getUrlOptions(this)); }

  MenuItem menuItem(String key) { return rows.get(key); }

  private void loadSettings() {
    editStarted();
    final int request = generation;
    final LoadTiming timing = new LoadTiming("Settings menu " + (groupName == null ? "root" : groupName));
    final Context context = getApplicationContext();
    final String options = BreviarApp.getUrlOptions(context);
    final String language = BreviarApp.getString(context, "language", "sk");
    if (navigationView.getMenu().size() == 0) {
      replaceMenu(() -> navigationView.getMenu().add(R.string.settings_loading).setEnabled(false));
    }
    pending = worker.submit(() -> {
      timing.mark("worker started");
      try {
        String xml = Server.getSettingsXml(context, options, language);
        timing.mark("XML received");
        SettingsXml result = SettingsXml.parse(xml);
        timing.mark("parsed; posting to UI");
        runOnUiThread(() -> {
          if (request != generation || isFinishing() || isDestroyed()) return;
          BreviarApp.cacheLanguageLocales(context, result.languages);
          showSettings(result);
          timing.mark("displayed");
        });
      } catch (Exception error) {
        timing.mark("failed");
        Log.e("breviar", "Loading native settings failed", error);
        runOnUiThread(() -> {
          if (request != generation || isFinishing() || isDestroyed()) return;
          replaceMenu(() -> {
            // Retain working controls if only a refresh failed.
            if (settings != null) populateSettings();
            MenuItem retry = navigationView.getMenu().add(Menu.NONE, View.generateViewId(),
                Menu.NONE, R.string.settings_load_failed);
            handleClick(retry.getItemId(), this::loadSettings);
          });
          updateMenu();
        });
      }
    });
  }

  private void showSettings(SettingsXml result) {
    settings = result;
    replaceMenu(this::populateSettings);
    updateMenu();
  }

  private boolean visible(SettingsXml.MenuEntry entry, boolean settingsPage) {
    // Android promotes these items with their children into the main drawer.
    if (settingsPage && (entry.key.equals("language") || entry.key.equals("calendar"))) return false;
    if (!entry.isGroup) return NativeSettings.supports(entry);
    for (SettingsXml.MenuEntry child : entry.children) if (visible(child, settingsPage)) return true;
    return false;
  }

  private void populateSettings() {
    nativeSettings.clear();
    rows.clear();
    Menu menu = navigationView.getMenu();
    if (groupName == null) {
      for (SettingsXml.MenuEntry group : settings.menu) {
        if (visible(group, true)) addSubmenu(menu, group);
      }
      return;
    }
    SettingsXml.MenuEntry entry = settings.findEntry(groupName);
    if (entry == null || !visible(entry, false)) {
      finish();
      return;
    }
    getSupportActionBar().setTitle(entry.key.equals("language") ? getString(R.string.lang_select)
        : entry.key.equals("calendar") ? getString(R.string.calendar_settings_title) : entry.label);
    if (entry.isGroup) {
      renderChildren(menu, entry, true);
    } else if (entry.control.equals("choice")) {
      // Android keeps calendar options reachable above a potentially long list.
      boolean childrenFirst = entry.key.equals("calendar");
      if (childrenFirst) renderChildren(menu, entry, false);
      // A distinct group makes Material separate choices from nested controls,
      // including the untitled interface-language section.
      int choicesGroup = View.generateViewId();
      for (SettingsXml.Choice choice : nativeSettings.choices(entry)) {
        addCheckedChoice(choicesGroup, nativeSettings.choiceLabel(entry, choice),
            choice.value.equals(nativeSettings.value(entry)), () -> {
          if (nativeSettings.select(entry, choice.value)) return;
          write(entry, choice.value);
          // Keep screens with nested settings open after choosing a value.
          if (entry.children.isEmpty()) finish();
        });
      }
      if (!childrenFirst) renderChildren(menu, entry, false);
    }
  }

  private void renderChildren(Menu menu, SettingsXml.MenuEntry parent, boolean settingsPage) {
    renderChildren(menu, parent, settingsPage, "");
  }

  private void renderChildren(Menu menu, SettingsXml.MenuEntry parent, boolean settingsPage, String heading) {
    // NavigationView only displays one submenu level. Flatten deeper XML groups
    // into sections, retaining their context and the order of every control.
    Menu section = null;
    for (SettingsXml.MenuEntry entry : parent.children) {
      if (!visible(entry, settingsPage)) continue;
      if (entry.isGroup) {
        String title = entry.label.isEmpty() ? heading
            : heading.isEmpty() ? entry.label : heading + " / " + entry.label;
        renderChildren(menu, entry, settingsPage, title);
        // Controls after a nested group need a new section at this position.
        section = null;
      } else {
        if (section == null) {
          section = heading.isEmpty() ? menu
              : menu.addSubMenu(Menu.NONE, View.generateViewId(), Menu.NONE, heading);
        }
        if (entry.control.equals("choice")) {
          addSubmenu(section, entry);
        } else {
          MenuItem row = addRow(section, entry);
          if (!nativeSettings.bind(row, entry)) bind(row, entry);
          if (!entry.children.isEmpty()) {
            renderChildren(menu, entry, settingsPage, heading);
            section = null;
          }
        }
      }
    }
  }

  private MenuItem addRow(Menu menu, SettingsXml.MenuEntry entry) {
    MenuItem row = menu.add(Menu.NONE, View.generateViewId(), Menu.NONE, entry.label);
    rows.put(entry.key, row);
    return row;
  }

  private void addSubmenu(Menu menu, SettingsXml.MenuEntry entry) {
    MenuItem row = addRow(menu, entry);
    row.setActionView(R.layout.widget_submenu);
    handleClick(row.getItemId(), () -> startActivity(entryIntent(this, entry.key)));
  }

  private void bind(MenuItem row, SettingsXml.MenuEntry entry) {
    switch (entry.control) {
      case "toggle":
        row.setActionView(R.layout.widget_switch);
        handleSwitch(row.getItemId(), new BooleanOption() {
          public boolean get() { return entry.value(options().params).equals("1"); }
          public void set(boolean checked) { write(entry, checked ? "1" : "0"); }
        });
        break;
      case "number":
        row.setActionView(R.layout.widget_int);
        handleInt(row.getItemId(), entry.min, entry.max, new IntOption() {
          public int get() {
            try { return Integer.parseInt(entry.value(options().params)); }
            catch (NumberFormatException error) { return Integer.parseInt(entry.defaultValue); }
          }
          public void set(int value) { write(entry, Integer.toString(value)); }
          public void reset() { write(entry, entry.resetValue); }
        });
        break;
      case "color":
        row.setActionView(R.layout.widget_color);
        handleColor(row.getItemId(), new String[]{"ffffcc", "ffddbb", "ddeeff", "111111", "222222", "333333"}, new ColorOption() {
          public String get() {
            String value = entry.value(options().params);
            return value.matches("[a-fA-F0-9]{6}") ? value : "";
          }
          public void set(String value) { write(entry, value); }
          public void reset() { write(entry, entry.resetValue); }
        });
        break;
    }
    if (row.getActionView() != null) {
      row.getActionView().setContentDescription(entry.label);
      row.getActionView().setSaveEnabled(false);
    }
  }

  private void write(SettingsXml.MenuEntry entry, String value) {
    editStarted();
    UrlOptions options = options();
    nativeSettings.beforeSave(entry);
    entry.setValue(options.params, value);
    BreviarApp.setUrlOptions(getApplicationContext(), options.build(true));
    refresh();
  }

  private void enableChildren(SettingsXml.MenuEntry parent, boolean enabled) {
    for (SettingsXml.MenuEntry child : parent.children) {
      MenuItem row = rows.get(child.key);
      if (row != null) {
        row.setEnabled(enabled);
        if (row.getActionView() != null) row.getActionView().setEnabled(enabled);
      }
      enableChildren(child, enabled);
    }
  }

  @Override public void updateMenu() {
    super.updateMenu();
    if (settings == null || nativeSettings == null) return;
    for (Map.Entry<String, MenuItem> row : rows.entrySet()) {
      SettingsXml.MenuEntry entry = settings.findEntry(row.getKey());
      if (entry == null || !entry.control.equals("choice")) continue;
      String caption = entry.label;
      for (SettingsXml.Choice choice : nativeSettings.choices(entry)) {
        if (choice.value.equals(nativeSettings.value(entry))) {
          caption += "\n" + nativeSettings.choiceLabel(entry, choice);
          break;
        }
      }
      row.getValue().setTitle(caption);
    }
    SettingsXml.MenuEntry entry = settings.findEntry(groupName);
    if (entry != null && entry.handler.equals("reading.navigation")) {
      enableChildren(entry, nativeSettings.navigationMode() == ReadingNavigation.Mode.ARROWS);
    }
  }
}

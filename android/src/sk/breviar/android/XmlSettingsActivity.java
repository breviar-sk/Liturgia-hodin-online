package sk.breviar.android;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import androidx.appcompat.app.AlertDialog;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/** Native controls populated by Server's localized XML settings export. */
public class XmlSettingsActivity extends SettingsActivity {
  private static final String GROUP = "settings_group";
  private final ExecutorService worker = Executors.newSingleThreadExecutor();
  private int generation;
  private String groupName;

  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    groupName = getIntent().getStringExtra(GROUP);
    getSupportActionBar().setTitle(R.string.settings);
    navigationView.setItemMaxLines(5);
  }

  @Override
  protected void onResume() {
    super.onResume();
    if (!appearanceChanged()) loadSettings();
  }

  @Override
  protected void onStop() {
    ++generation;
    super.onStop();
  }

  @Override
  protected void onDestroy() {
    worker.shutdownNow();
    super.onDestroy();
  }

  private void addDeviceSettings() {
    inflateMenu(R.menu.main_settings);
    handleClick(R.id.device_settings, () -> startActivity(new Intent(this, DeviceSettings.class)));
    handleClick(R.id.display_settings, () -> startActivity(new Intent(this, DisplaySettings.class)));
    handleClick(R.id.tts_settings, () -> startActivity(new Intent(this, TtsSettings.class)));
  }

  private void loadSettings() {
    final int request = ++generation;
    final Context context = getApplicationContext();
    final String options = BreviarApp.getUrlOptions(context);
    final String language = BreviarApp.getString(context, "language", "sk");
    // Keep the existing menu usable while refreshing after Back or a choice.
    if (navigationView.getMenu().size() == 0) {
      replaceMenu(() -> {
        if (groupName == null) addDeviceSettings();
        navigationView.getMenu().add(R.string.settings_loading).setEnabled(false);
      });
    }
    worker.execute(() -> {
      try {
        SettingsXml settings = SettingsXml.parse(Server.getSettingsXml(context, options, language));
        runOnUiThread(() -> {
          if (request == generation && !isFinishing() && !isDestroyed()) showSettings(settings);
        });
      } catch (Exception error) {
        Log.e("breviar", "Loading native settings failed", error);
        runOnUiThread(() -> {
          if (request != generation || isFinishing() || isDestroyed()) return;
          replaceMenu(() -> {
            if (groupName == null) addDeviceSettings();
            MenuItem retry = navigationView.getMenu().add(Menu.NONE, View.generateViewId(),
                Menu.NONE, R.string.settings_load_failed);
            handleClick(retry.getItemId(), this::loadSettings);
          });
        });
      }
    });
  }

  private void showSettings(SettingsXml settings) {
    replaceMenu(() -> populateSettings(settings));
  }

  private void populateSettings(SettingsXml settings) {
    if (groupName == null) {
      addDeviceSettings();
      if (settings.calendars.size() > 1) {
        String title = getString(R.string.calendar_settings_title);
        addChoice(title, settings.calendars, settings.selectedCalendar, selected -> {
          UrlOptions options = new UrlOptions(BreviarApp.getUrlOptions(this));
          options.params.put(settings.calendarParameter, selected);
          save(options);
          loadSettings();
        });
      }
      for (SettingsXml.Group group : settings.groups) {
        if (!group.choices.isEmpty()) {
          addChoice(group.label, group.choices, Long.toString(group.value), selected -> {
            UrlOptions options = new UrlOptions(BreviarApp.getUrlOptions(this));
            group.select(options.params, selected);
            save(options);
            loadSettings();
          });
        } else if (!group.options.isEmpty()) {
          MenuItem item = navigationView.getMenu().add(Menu.NONE, View.generateViewId(), Menu.NONE, group.label);
          item.setActionView(R.layout.widget_submenu);
          handleClick(item.getItemId(), () -> startActivity(new Intent(this, XmlSettingsActivity.class)
              .putExtra(GROUP, group.name)));
        }
      }
    } else {
      SettingsXml.Group group = settings.findGroup(groupName);
      if (group == null) {
        finish();
        return;
      }
      getSupportActionBar().setTitle(group.label);
      for (SettingsXml.Option option : group.options) {
        MenuItem item = navigationView.getMenu().add(Menu.NONE, View.generateViewId(), Menu.NONE, option.label);
        item.setActionView(R.layout.widget_switch);
        item.getActionView().setContentDescription(option.label);
        handleSwitch(item.getItemId(), new BooleanOption() {
          public boolean get() { return group.isChecked(option); }
          public void set(boolean checked) {
            UrlOptions options = new UrlOptions(BreviarApp.getUrlOptions(XmlSettingsActivity.this));
            group.setChecked(options.params, option, checked);
            save(options);
          }
        });
      }
      updateMenu();
    }
  }

  private interface Selection { void select(String value); }

  private void addChoice(String title, List<SettingsXml.Choice> choices, String value, Selection selection) {
    String[] labels = new String[choices.size()];
    int selected = -1;
    for (int i = 0; i < choices.size(); ++i) {
      labels[i] = choices.get(i).label;
      if (choices.get(i).value.equals(value)) selected = i;
    }
    final int checked = selected;
    String caption = selected >= 0 ? title + "\n" + labels[selected] : title;
    MenuItem item = navigationView.getMenu().add(Menu.NONE, View.generateViewId(), Menu.NONE, caption);
    item.setActionView(R.layout.widget_submenu);
    handleClick(item.getItemId(), () -> new AlertDialog.Builder(this)
        .setTitle(title)
        .setSingleChoiceItems(labels, checked, (dialog, index) -> {
          selection.select(choices.get(index).value);
          dialog.dismiss();
        })
        .setNegativeButton(android.R.string.cancel, null)
        .show());
  }

  private void save(UrlOptions options) {
    // A refresh started before this edit must not restore its older snapshot.
    ++generation;
    BreviarApp.setUrlOptions(getApplicationContext(), options.build(true));
  }
}

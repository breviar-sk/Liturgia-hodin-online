package sk.breviar.android;

import java.lang.Runnable;

import android.content.Intent;
import android.os.Bundle;

public class MainSettings extends SettingsActivity {
  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    inflateMenu(R.menu.main_settings);
    getSupportActionBar().setTitle(getString(R.string.settings));

    final SettingsActivity act = this;
    handleClick(R.id.device_settings, new Runnable() {
      public void run() {
        startActivity(new Intent(act, DeviceSettings.class));
      }
    });
    handleClick(R.id.prayer_settings, new Runnable() {
      public void run() {
        startActivity(new Intent(act, PrayerSettings.class));
      }
    });
    handleClick(R.id.display_settings, new Runnable() {
      public void run() {
        startActivity(new Intent(act, DisplaySettings.class));
      }
    });
    handleClick(R.id.calendar_settings, new Runnable() {
      public void run() {
        startActivity(new Intent(act, CalendarSettings.class));
      }
    });
    handleClick(R.id.tts_settings, new Runnable() {
      public void run() {
        startActivity(new Intent(act, TtsSettings.class));
      }
    });
  }
}

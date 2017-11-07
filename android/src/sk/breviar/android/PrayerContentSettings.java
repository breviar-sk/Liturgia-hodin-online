package sk.breviar.android;

import java.lang.Runnable;

import android.os.Bundle;

public class PrayerContentSettings extends SettingsActivity {
  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    inflateMenu(R.menu.prayer_content_settings);
    getSupportActionBar().setTitle(getString(R.string.prayer_content_settings1_title));

    final SettingsActivity act = this;
    handleSwitch(R.id.various_options_in_prayers, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setDisplayVariousOptions(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isDisplayVariousOptions(); }
    });
    handleSwitch(R.id.alternatives, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setDisplayAlternatives(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isDisplayAlternatives(); }
    });
  }
}


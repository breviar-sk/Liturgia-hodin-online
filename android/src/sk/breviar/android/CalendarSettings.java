package sk.breviar.android;

import java.lang.Runnable;

import android.os.Bundle;

public class CalendarSettings extends SettingsActivity {
  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    inflateMenu(R.menu.calendar_settings);
    getSupportActionBar().setTitle(getString(R.string.calendar_settings_title));

    final SettingsActivity act = this;
    handleSwitch(R.id.epiphany_sunday, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setEpiphanySunday(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isEpiphanySunday(); }
    });
    handleSwitch(R.id.ascension_sunday, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setAscensionSunday(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isAscensionSunday(); }
    });
    handleSwitch(R.id.body_blood_sunday, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setBodyBloodSunday(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isBodyBloodSunday(); }
    });
    handleSwitch(R.id.emphasize_local_calendar, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setEmphasizeLocalCalendar(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isEmphasizeLocalCalendar(); }
    });
  }
}


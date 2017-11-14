package sk.breviar.android;

import java.lang.Runnable;

import android.os.Bundle;

public class DisplaySettings extends SettingsActivity {
  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    inflateMenu(R.menu.display_settings);
    getSupportActionBar().setTitle(getString(R.string.display_settings_title));

    final SettingsActivity act = this;
    handleSwitch(R.id.first_vespers_buttons, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setFirstVespersButtons(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isFirstVespersButtons(); }
    });
    handleSwitch(R.id.navigation, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setNavigation(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isNavigation(); }
    });
    handleSwitch(R.id.wrapping_printed, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setTextWrap(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isTextWrap(); }
    });
    handleSwitch(R.id.smart_buttons, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setSmartButtons(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isSmartButtons(); }
    });
    handleSwitch(R.id.night_mode, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setNightmode(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isNightmode(); }
    });
    handleSwitch(R.id.background_override, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setBackgroundOverride(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isBackgroundOverride(); }
    });
    handleSwitch(R.id.normal_font, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setOnlyNonBoldFont(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isOnlyNonBoldFont(); }
    });
    handleSwitch(R.id.buttons_order, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setButtonsOrder(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isButtonsOrder(); }
    });
    handleSwitch(R.id.transparent_nav, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setTransparentNav(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isTransparentNav(); }
    });
  }
}


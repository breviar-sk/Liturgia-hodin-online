package sk.breviar.android;

import java.lang.Runnable;

import android.os.Bundle;

public class DeviceSettings extends SettingsActivity {
  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    inflateMenu(R.menu.device_settings);
    getSupportActionBar().setTitle(getString(R.string.settings_title));

    final SettingsActivity act = this;
    handleSwitch(R.id.vol_buttons, new BooleanOption() {
      public void set(boolean value) { BreviarApp.setVolButtons(act, value); }
      public boolean get() { return BreviarApp.getVolButtons(act); }
    });
    handleSwitch(R.id.dimlock, new BooleanOption() {
      public void set(boolean value) { BreviarApp.setDimLock(act, value); }
      public boolean get() { return BreviarApp.getDimLock(act); }
    });
    handleSwitch(R.id.mute, new BooleanOption() {
      public void set(boolean value) { BreviarApp.setMute(act, value); }
      public boolean get() { return BreviarApp.getMute(act); }
    });
  }
}


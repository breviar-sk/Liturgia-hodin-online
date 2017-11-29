package sk.breviar.android;

import java.lang.Runnable;

import android.app.NotificationManager;
import android.os.Build;
import android.os.Bundle;
import android.widget.Toast;

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
      public void set(boolean value) {
        if (value && Build.VERSION.SDK_INT >= 23) {
          NotificationManager manager =
              (NotificationManager)act.getSystemService(act.NOTIFICATION_SERVICE);
          if (!manager.isNotificationPolicyAccessGranted()) {
            value = false;
            Toast.makeText(act, R.string.notification_not_allowed, Toast.LENGTH_SHORT).show();
          }
        }
        BreviarApp.setMute(act, value);
      }
      public boolean get() { return BreviarApp.getMute(act); }
    });
  }
}

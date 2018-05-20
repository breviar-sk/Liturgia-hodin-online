package sk.breviar.android;

import java.lang.Runnable;

import android.content.Intent;
import android.os.Bundle;

public class TtsSettings extends SettingsActivity {
  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    inflateMenu(R.menu.tts_settings);
    getSupportActionBar().setTitle(getString(R.string.tts_settings_title));

    final SettingsActivity act = this;

    handleSwitch(R.id.tts_use_pause_in_psalms, new BooleanOption() {
      public void set(boolean value) { BreviarApp.setTtsUsePauseInPsalms(act, value); }
      public boolean get() { return BreviarApp.getTtsUsePauseInPsalms(act); }
    });

    handleClick(R.id.tts_settings_help, new Runnable() {
      public void run() {
        startActivity(new Intent(act, DialogActivity.class)
            .putExtra("title", R.string.tts_settings_help_title)
            .putExtra("content", getString(R.string.tts_settings_help_content))
            .putExtra("show_ok", false));
      }
    });
  }
}

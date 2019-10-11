package sk.breviar.android;

import java.lang.Runnable;

import android.content.Intent;
import android.os.Bundle;

public class LangSelect extends SettingsActivity {
  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    inflateMenu(R.menu.lang_select);
    getSupportActionBar().setTitle(getString(R.string.lang_select));

    final SettingsActivity act = this;
    handleClick(R.id.lang_cz, new Runnable() {
      public void run() {
        act.setResult(RESULT_OK, new Intent().putExtra("lang", "cz"));
        act.finish();
      }
    });
    handleClick(R.id.lang_c2, new Runnable() {
      public void run() {
        act.setResult(RESULT_OK, new Intent().putExtra("lang", "c2"));
        act.finish();
      }
    });
    handleClick(R.id.lang_hu, new Runnable() {
      public void run() {
        act.setResult(RESULT_OK, new Intent().putExtra("lang", "hu"));
        act.finish();
      }
    });
    handleClick(R.id.lang_sk, new Runnable() {
      public void run() {
        act.setResult(RESULT_OK, new Intent().putExtra("lang", "sk"));
        act.finish();
      }
    });
    handleClick(R.id.lang_la, new Runnable() {
      public void run() {
        act.setResult(RESULT_OK, new Intent().putExtra("lang", "la"));
        act.finish();
      }
    });
    handleSwitch(R.id.override_locale, new BooleanOption() {
      public void set(boolean value) {
        BreviarApp.setOverrideLocale(getApplicationContext(), value);
      }
      public boolean get() {
        return BreviarApp.getOverrideLocale(getApplicationContext());
      }
    });
  }
}

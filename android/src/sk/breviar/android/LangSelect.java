package sk.breviar.android;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.CheckBox;

import sk.breviar.android.BreviarApp;

public class LangSelect extends Activity {
    static final int DIALOG_ABOUT = 1;
    static final int DIALOG_NEWS = 2;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
      super.onCreate(savedInstanceState);
      setContentView(R.layout.langselect);

      final Activity activity = this;

      ((Button)findViewById(R.id.lang_sk)).setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          activity.setResult(RESULT_OK, new Intent().putExtra("lang", "sk"));
          activity.finish();
        }
      });

      ((Button)findViewById(R.id.lang_cz)).setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          activity.setResult(RESULT_OK, new Intent().putExtra("lang", "cz"));
          activity.finish();
        }
      });

      ((Button)findViewById(R.id.lang_hu)).setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          activity.setResult(RESULT_OK, new Intent().putExtra("lang", "hu"));
          activity.finish();
        }
      });

      CheckBox override_check = (CheckBox)findViewById(R.id.override_locale_check);

      override_check.setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          BreviarApp.setOverrideLocale(getApplicationContext(), ((CheckBox)v).isChecked());
        }
      });

      override_check.setChecked(BreviarApp.getOverrideLocale(getApplicationContext()));

      CheckBox vol_buttons_check = (CheckBox)findViewById(R.id.vol_buttons_check);

      vol_buttons_check.setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          BreviarApp.setVolButtons(getApplicationContext(), ((CheckBox)v).isChecked());
        }
      });

      vol_buttons_check.setChecked(BreviarApp.getVolButtons(getApplicationContext()));

      CheckBox dimlock_check = (CheckBox)findViewById(R.id.dimlock_check);

      dimlock_check.setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          BreviarApp.setDimLock(getApplicationContext(), ((CheckBox)v).isChecked());
        }
      });

      dimlock_check.setChecked(BreviarApp.getDimLock(getApplicationContext()));

      CheckBox mute_check = (CheckBox)findViewById(R.id.mute_check);

      mute_check.setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          BreviarApp.setMute(getApplicationContext(), ((CheckBox)v).isChecked());
        }
      });

      mute_check.setChecked(BreviarApp.getMute(getApplicationContext()));

      CheckBox epiphany_sunday_check = (CheckBox)findViewById(R.id.epiphany_sunday_check);

      epiphany_sunday_check.setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          BreviarApp.setMenuEpiphanySunday(getApplicationContext(), ((CheckBox)v).isChecked());
        }
      });

      epiphany_sunday_check.setChecked(BreviarApp.getMenuEpiphanySunday(getApplicationContext()));

      CheckBox ascension_sunday_check = (CheckBox)findViewById(R.id.ascension_sunday_check);

      ascension_sunday_check.setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          BreviarApp.setMenuAscensionSunday(getApplicationContext(), ((CheckBox)v).isChecked());
        }
      });

      ascension_sunday_check.setChecked(BreviarApp.getMenuAscensionSunday(getApplicationContext()));

      CheckBox body_blood_sunday_check = (CheckBox)findViewById(R.id.body_blood_sunday_check);

      body_blood_sunday_check.setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          BreviarApp.setMenuBodyBloodSunday(getApplicationContext(), ((CheckBox)v).isChecked());
        }
      });

      body_blood_sunday_check.setChecked(BreviarApp.getMenuBodyBloodSunday(getApplicationContext()));

      CheckBox emphasize_local_calendar_check = (CheckBox)findViewById(R.id.emphasize_local_calendar_check);

      emphasize_local_calendar_check.setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          BreviarApp.setMenuEmphasizeLocalCalendar(getApplicationContext(), ((CheckBox)v).isChecked());
        }
      });

      emphasize_local_calendar_check.setChecked(BreviarApp.getMenuEmphasizeLocalCalendar(getApplicationContext()));

      ((Button)findViewById(R.id.about)).setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          showDialog(DIALOG_ABOUT);
        }
      });

      ((Button)findViewById(R.id.btn_news)).setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          showDialog(DIALOG_NEWS);
        }
      });

      ((Button)findViewById(R.id.alarms)).setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          startActivity(new Intent("sk.breviar.android.ALARMS"));
        }
      });
    }

    @Override
    protected Dialog onCreateDialog(int id) {
      String content = null;
      switch(id) {
        case DIALOG_ABOUT:
          content = Util.getAboutText(this);
          break;
        case DIALOG_NEWS:
          content = getString(R.string.news);
          break;
        default:
          // fall through
      }
      return Util.createHtmlDialog(this, content);
    }
}

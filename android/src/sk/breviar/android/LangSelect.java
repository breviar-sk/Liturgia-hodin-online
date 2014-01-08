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

      ((Button)findViewById(R.id.about)).setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          showDialog(DIALOG_ABOUT);
        }
      });
    }

    @Override
    protected Dialog onCreateDialog(int id) {
      switch(id) {
        case DIALOG_ABOUT:
          WebView wv = new WebView(this);
          try {
            wv.loadData(android.util.Base64.encodeToString(
                            getString(R.string.about_text).getBytes("UTF-8"),
                            android.util.Base64.DEFAULT),
                        "text/html; charset=utf-8", "base64");
          } catch (java.io.UnsupportedEncodingException e) {
            wv.loadData("unsupported encoding utf-8", "text/html", null);
          }
          return new AlertDialog.Builder(this)
                 .setView(wv)
                 .setCancelable(false)
                 .setNeutralButton("OK", new DialogInterface.OnClickListener() {
                     public void onClick(DialogInterface dialog, int id) {
                          dialog.cancel();
                     }
                 })
                 .create();
        default:
          // fall through
      }
      return null;
    }
}

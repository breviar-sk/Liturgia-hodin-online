package sk.breviar.android;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;

import sk.breviar.android.BreviarApp;

public class LangSelect extends Activity {

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
    }
}

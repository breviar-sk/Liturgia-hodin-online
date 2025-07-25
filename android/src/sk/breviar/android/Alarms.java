package sk.breviar.android;

import android.content.Context;
import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import android.widget.CompoundButton;

import sk.breviar.android.BreviarApp;
import sk.breviar.android.Util;

public class Alarms extends AppCompatActivity {
    @Override
    protected void attachBaseContext(Context newBase) {
      super.attachBaseContext(newBase);
      BreviarApp.applyCustomLocale(this);
    }

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);

      setContentView(R.layout.alarms);

      Toolbar toolbar = (Toolbar) findViewById(R.id.alarms_toolbar);
      setSupportActionBar(toolbar);
      getSupportActionBar().setDisplayHomeAsUpEnabled(true);
      getSupportActionBar().setTitle(getString(R.string.alarms));

      for (int i = 0; i < Util.events.length; ++i) {
        final CompoundButton box = ((CompoundButton)findViewById(Util.events[i].id));
        Util.events[i].updateBox(box, Util.events[i].getTime(this));
        final int j = i;
        box.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
          public void onCheckedChanged(CompoundButton v, boolean isChecked) {
            boolean enabled = Util.events[j].getTime(v.getContext()).enabled;
            if (isChecked == enabled) return;
            if (isChecked) {
              AlarmTimePickerFragment f = new AlarmTimePickerFragment();
              f.show(getSupportFragmentManager(), "event-" + j);
              v.setChecked(false);
            } else {
              Util.events[j].disable(box.getContext());
              Util.events[j].updateBox(box, new Util.AlarmTime(0, 0, false));
            }
          }
        });
      }
    }
}

package sk.breviar.android;

import android.content.Context;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
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
        box.setOnClickListener(new View.OnClickListener() {
          public void onClick(View v) {
            if (((CompoundButton)v).isChecked()) {
              ((CompoundButton)v).setChecked(false);
              AlarmTimePickerFragment f = new AlarmTimePickerFragment();
              f.show(getSupportFragmentManager(), "event-" + j);
            } else {
              Util.events[j].updateBox(box, new Util.AlarmTime(0, 0, false));
              Util.events[j].disable(box.getContext());
            }
          }
        });
      }
    }
}

package sk.breviar.android;

import android.support.v4.app.FragmentActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.CheckBox;
import sk.breviar.android.Util;

public class Alarms extends FragmentActivity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
      super.onCreate(savedInstanceState);

      setContentView(R.layout.alarms);

      for (int i = 0; i < Util.events.length; ++i) {
        final CheckBox box = ((CheckBox)findViewById(Util.events[i].id));
        Util.events[i].updateBox(box, Util.events[i].getTime(this));
        final int j = i;
        box.setOnClickListener(new View.OnClickListener() {
          public void onClick(View v) {
            if (((CheckBox)v).isChecked()) {
              ((CheckBox)v).setChecked(false);
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

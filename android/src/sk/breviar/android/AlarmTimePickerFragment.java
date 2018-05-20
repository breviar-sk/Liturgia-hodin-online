package sk.breviar.android;

import android.support.v4.app.DialogFragment;

import android.app.Dialog;
import android.app.TimePickerDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.text.format.DateFormat;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.TimePicker;

import sk.breviar.android.Util;

public class AlarmTimePickerFragment extends DialogFragment 
    implements TimePickerDialog.OnTimeSetListener{

  int eventId() {
    return Integer.parseInt(getTag().substring(6));
  }

  Util.EventInfo event() {
    return Util.events[eventId()];
  }

  CompoundButton box() {
    return (CompoundButton)getActivity().findViewById(Util.events[eventId()].id);
  }

  @Override
  public Dialog onCreateDialog(Bundle savedInstanceState) {
    Util.AlarmTime t = event().getTime(getActivity());
    TimePickerDialog d = new TimePickerDialog(getActivity(), this,
        t.hour, t.minute, DateFormat.is24HourFormat(getActivity()));

    return d;
  }

  public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
    Util.EventInfo e = event();
    e.setTime(getActivity(), hourOfDay, minute);
    e.updateBox(box(), new Util.AlarmTime(minute, hourOfDay, true));
  }
}

package sk.breviar.android;

import static org.hamcrest.CoreMatchers.is;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertSame;

import android.app.Dialog;
import android.content.res.ColorStateList;
import android.graphics.Typeface;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import androidx.fragment.app.DialogFragment;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ErrorCollector;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.Shadows;
import org.robolectric.android.controller.ActivityController;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.LooperMode;

/** Named font weights can bypass fonts selected in the device's settings. */
@RunWith(RobolectricTestRunner.class)
@Config(sdk = {24, 35})
@LooperMode(LooperMode.Mode.PAUSED)
public class DialogFontTest {
  @Rule public ErrorCollector errors = new ErrorCollector();

  private void checkFont(View view) {
    if (view instanceof TextView) {
      TextView text = (TextView)view;
      if (text.getText().length() > 0 && text.getTypeface() != null) {
        String family = Shadows.shadowOf(text.getTypeface()).getFontDescription().getFamilyName();
        String label = text.getText().toString() + " (" + family + ")";
        // A null family uses Typeface.DEFAULT, also the regular system font.
        errors.checkThat(label, family == null || family.equals("sans-serif"), is(true));
        errors.checkThat(label, text.getTypeface().getStyle(), is(Typeface.NORMAL));
      }
    }
    if (view instanceof ViewGroup) {
      ViewGroup group = (ViewGroup)view;
      for (int i = 0; i < group.getChildCount(); ++i) checkFont(group.getChildAt(i));
    }
  }

  private void checkDialog(SettingsActivity activity, DialogFragment fragment, String tag) {
    fragment.showNow(activity.getSupportFragmentManager(), tag);
    checkFont(fragment.requireDialog().getWindow().getDecorView());
    fragment.dismissNow();
  }

  @Test public void chooserAndSpeechWarningUseRegularSystemFont() {
    for (boolean eink : new boolean[]{false, true}) {
      BreviarApp.setEinkMode(RuntimeEnvironment.getApplication(), eink);
      try (ActivityController<SettingsActivity> controller = Robolectric.buildActivity(SettingsActivity.class).setup()) {
        checkDialog(controller.get(), new AppearanceChooser(), AppearanceChooser.TAG);
        checkDialog(controller.get(), new TtsBackgroundUsageWarning(), TtsBackgroundUsageWarning.TAG);
      }
    }
  }

  @Test public void frameworkAlertsUseRegularSystemFont() {
    for (boolean eink : new boolean[]{false, true}) {
      BreviarApp.setEinkMode(RuntimeEnvironment.getApplication(), eink);
      try (ActivityController<SettingsActivity> controller = Robolectric.buildActivity(SettingsActivity.class).setup()) {
        Dialog dialog = new android.app.AlertDialog.Builder(controller.get())
            .setTitle("Title").setMessage("Message")
            .setPositiveButton("OK", null).setNegativeButton("Cancel", null).setNeutralButton("Default", null).show();
        try {
          TextView button = dialog.findViewById(android.R.id.button1);
          float size = button.getTextSize();
          ColorStateList colors = button.getTextColors();
          SystemFontDialogFragment.applySystemFont(dialog);
          checkFont(dialog.getWindow().getDecorView());
          assertEquals(size, button.getTextSize(), 0f);
          assertSame(colors, button.getTextColors());
        } finally {
          dialog.dismiss();
        }
      }
    }
  }

  @Test public void settingsPickersUseRegularSystemFont() {
    for (boolean eink : new boolean[]{false, true}) {
      BreviarApp.setEinkMode(RuntimeEnvironment.getApplication(), eink);
      try (ActivityController<SettingsActivity> controller = Robolectric.buildActivity(SettingsActivity.class).setup()) {
        SettingsActivity activity = controller.get();
        SettingsActivity.IntOption number = new SettingsActivity.IntOption() {
          public int get() { return 16; }
          public void set(int value) {}
          public void reset() {}
        };
        checkDialog(activity, new SettingsActivity.IntAlertDialogFragment(activity,
            new SettingsActivity.IntOptionInfo(number, 8, 40)), "number");
        SettingsActivity.ColorOption color = new SettingsActivity.ColorOption() {
          public String get() { return "ffffff"; }
          public void set(String value) {}
        };
        checkDialog(activity, new SettingsActivity.ColorDialogFragment(activity,
            new SettingsActivity.ColorOptionInfo(color, new String[]{"ffffff", "000000"})), "color");
      }
    }
  }

  @Test public void alarmPickerUsesRegularSystemFont() {
    for (boolean eink : new boolean[]{false, true}) {
      BreviarApp.setEinkMode(RuntimeEnvironment.getApplication(), eink);
      try (ActivityController<SettingsActivity> controller = Robolectric.buildActivity(SettingsActivity.class).setup()) {
        checkDialog(controller.get(), new AlarmTimePickerFragment(), "event-0");
      }
    }
  }
}

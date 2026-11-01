package sk.breviar.android;

import android.app.Dialog;
import android.graphics.Typeface;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import androidx.fragment.app.DialogFragment;

/** Use the same regular system font as the native menus and toolbar. */
public class SystemFontDialogFragment extends DialogFragment {
  @Override public void onStart() {
    super.onStart();
    applySystemFont(requireDialog());
  }

  static void applySystemFont(Dialog dialog) {
    applySystemFont(dialog.getWindow().getDecorView());
  }

  private static void applySystemFont(View view) {
    // Do this after inflation: framework picker layouts and AppCompat title and
    // button styles can explicitly name sans-serif-medium, bypassing the font
    // chosen in device settings. Leave sizes, colors and other styling intact.
    if (view instanceof TextView) {
      ((TextView)view).setTypeface(Typeface.create("sans-serif", Typeface.NORMAL));
    }
    if (view instanceof ViewGroup) {
      ViewGroup group = (ViewGroup)view;
      for (int i = 0; i < group.getChildCount(); ++i) applySystemFont(group.getChildAt(i));
    }
  }
}

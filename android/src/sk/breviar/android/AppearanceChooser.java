package sk.breviar.android;

import android.app.Dialog;
import android.os.Bundle;
import androidx.appcompat.app.AlertDialog;
import androidx.fragment.app.DialogFragment;

/** A readable entry point to e-ink mode, even when the normal menu is unreadable. */
public class AppearanceChooser extends DialogFragment {
  static final String TAG = "appearance-chooser";

  @Override public void onCreate(Bundle state) {
    super.onCreate(state);
    setCancelable(false);
  }

  @Override public Dialog onCreateDialog(Bundle state) {
    return new AlertDialog.Builder(requireContext(), R.style.AppearanceChooserTheme)
        .setTitle(R.string.appearance_title)
        .setMessage(getString(R.string.appearance_message,
            getString(R.string.settings), getString(R.string.settings_title)))
        .setPositiveButton(R.string.appearance_normal, (dialog, which) -> choose(false))
        .setNegativeButton(R.string.appearance_eink, (dialog, which) -> choose(true))
        .create();
  }

  private void choose(boolean eink) {
    Breviar reader = (Breviar)requireActivity();
    // Remove the fragment before recreation can save it in the back stack.
    dismissNow();
    reader.onAppearanceChosen(eink);
  }
}

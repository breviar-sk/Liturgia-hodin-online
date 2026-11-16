package sk.breviar.android;

import android.app.Dialog;
import android.os.Bundle;
import androidx.appcompat.app.AlertDialog;

/** Choose what incoming prayer links may change before importing the first one. */
public class SharedAppearanceChooser extends SystemFontDialogFragment {
  static final String TAG = "shared-appearance-chooser";

  @Override public void onCreate(Bundle state) {
    super.onCreate(state);
    setCancelable(false);
  }

  @Override public Dialog onCreateDialog(Bundle state) {
    return new AlertDialog.Builder(requireContext(), R.style.AppearanceChooserTheme)
        .setTitle(R.string.shared_appearance_title)
        .setMessage(getString(R.string.shared_appearance_message,
            getString(R.string.settings), getString(R.string.settings_title)))
        .setPositiveButton(R.string.shared_appearance_all, (dialog, which) -> choose(true))
        .setNegativeButton(R.string.shared_appearance_content, (dialog, which) -> choose(false))
        .create();
  }

  private void choose(boolean appearance) {
    Breviar reader = (Breviar)requireActivity();
    dismissNow();
    reader.onSharedAppearanceChosen(appearance);
  }
}

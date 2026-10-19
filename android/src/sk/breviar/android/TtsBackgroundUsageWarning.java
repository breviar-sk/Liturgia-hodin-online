package sk.breviar.android;

import android.app.ActivityManager;
import android.app.Dialog;
import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.provider.Settings;
import android.widget.Toast;
import androidx.appcompat.app.AlertDialog;
import androidx.fragment.app.DialogFragment;
import androidx.fragment.app.FragmentManager;

/** Explain explicit background restrictions before the reader starts speech. */
public class TtsBackgroundUsageWarning extends DialogFragment {
  static final String TAG = "tts-background-usage";
  private static final String RESUME = "resume";

  static boolean showIfRestricted(Breviar reader, boolean resume) {
    FragmentManager fragments = reader.getSupportFragmentManager();
    if (fragments.findFragmentByTag(TAG) != null) return true;
    if (Build.VERSION.SDK_INT < 28) return false;
    ActivityManager manager = (ActivityManager)reader.getSystemService(Context.ACTIVITY_SERVICE);
    // This is the user's background restriction, not the normal battery optimization.
    // Read it on each attempt: the user can change it outside the app at any time.
    if (manager == null || !manager.isBackgroundRestricted()) return false;

    Bundle args = new Bundle();
    args.putBoolean(RESUME, resume);
    TtsBackgroundUsageWarning warning = new TtsBackgroundUsageWarning();
    warning.setArguments(args);
    warning.showNow(fragments, TAG);
    return true;
  }

  @Override public Dialog onCreateDialog(Bundle state) {
    return new AlertDialog.Builder(requireContext())
        .setTitle(R.string.tts_background_title)
        .setMessage(R.string.tts_background_message)
        .setPositiveButton(R.string.tts_background_settings, (dialog, which) -> openSettings())
        .setNeutralButton(R.string.tts_background_continue, (dialog, which) -> continueSpeaking())
        .setNegativeButton(android.R.string.cancel, null)
        .create();
  }

  private void continueSpeaking() {
    Breviar reader = (Breviar)requireActivity();
    boolean resume = requireArguments().getBoolean(RESUME);
    dismissNow();
    reader.speakAfterBackgroundCheck(resume);
  }

  private void openSettings() {
    Breviar reader = (Breviar)requireActivity();
    dismissNow();
    // App info is a public, portable entry point to the manufacturer's battery controls.
    // Do not request a Doze exemption: that is a different setting.
    Intent intent = new Intent(Settings.ACTION_APPLICATION_DETAILS_SETTINGS,
        Uri.fromParts("package", reader.getPackageName(), null));
    try {
      reader.startActivity(intent);
    } catch (ActivityNotFoundException | SecurityException e) {
      Toast.makeText(reader, R.string.tts_background_settings_unavailable, Toast.LENGTH_LONG).show();
    }
  }
}

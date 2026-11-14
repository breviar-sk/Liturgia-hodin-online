package sk.breviar.android;

import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import androidx.appcompat.app.AlertDialog;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/** One-time offer; the XML catalogue remains the source of both palettes. */
public class HighContrastPrompt extends SystemFontDialogFragment {
  static final String TAG = "high-contrast-prompt";
  private static final String APPLYING = "applying";
  private final ExecutorService worker = Executors.newSingleThreadExecutor();
  private final Handler ui = new Handler(Looper.getMainLooper());
  private boolean applying, loading;
  private Map<String, String> colors;
  private Exception failure;

  static boolean showIfNeeded(AppearanceActivity activity) {
    if (activity.getSupportFragmentManager().findFragmentByTag(TAG) != null) return true;
    if (!BreviarApp.getEinkMode(activity) || BreviarApp.wasHighContrastOffered(activity)
        || activity.appearanceChanged() || activity.isFinishing() || activity.isDestroyed()
        || activity.getSupportFragmentManager().isStateSaved()) return false;
    new HighContrastPrompt().showNow(activity.getSupportFragmentManager(), TAG);
    // Remember the notification itself, including a No answer or closing the
    // application. Fragment restoration preserves an unanswered open dialog.
    BreviarApp.markHighContrastOffered(activity);
    return true;
  }

  @Override public void onCreate(Bundle state) {
    super.onCreate(state);
    setCancelable(false);
    applying = state != null && state.getBoolean(APPLYING);
  }

  @Override public Dialog onCreateDialog(Bundle state) {
    return new AlertDialog.Builder(requireContext(), R.style.AppearanceChooserTheme)
        .setTitle(R.string.high_contrast_title)
        .setMessage(R.string.high_contrast_message)
        .setPositiveButton(R.string.high_contrast_yes, null)
        .setNegativeButton(R.string.high_contrast_no, (dialog, which) -> close())
        .create();
  }

  @Override public void onStart() {
    super.onStart();
    AlertDialog dialog = (AlertDialog)requireDialog();
    dialog.getButton(AlertDialog.BUTTON_POSITIVE).setOnClickListener(view -> loadPresets());
    if (applying && colors == null && failure == null) loadPresets();
  }

  @Override public void onResume() {
    super.onResume();
    deliverResult();
  }

  private void loadPresets() {
    if (loading) return;
    applying = loading = true;
    AlertDialog dialog = (AlertDialog)requireDialog();
    dialog.getButton(AlertDialog.BUTTON_POSITIVE).setEnabled(false);
    dialog.setMessage(getString(R.string.settings_loading));
    final Context context = requireContext().getApplicationContext();
    final String options = BreviarApp.getUrlOptions(context);
    final String language = BreviarApp.getString(context, "language", "sk");
    worker.submit(() -> {
      Map<String, String> result = new LinkedHashMap<>();
      Exception error = null;
      try {
        SettingsXml settings = SettingsXml.parse(Server.getSettingsXml(context, options, language));
        for (String mode : new String[]{"day", "night"}) {
          SettingsXml.MenuEntry preset = settings.findEntry("appearance.colors." + mode + ".high-contrast");
          if (preset == null) throw new IllegalArgumentException("Missing high-contrast preset: " + mode);
          preset.applyPreset(result);
        }
      } catch (Exception caught) {
        error = caught;
        Log.e("breviar", "Loading high-contrast presets failed", caught);
      }
      final Map<String, String> values = result;
      final Exception problem = error;
      ui.post(() -> {
        if (!isAdded() || isRemoving()) return;
        loading = false;
        colors = problem == null ? values : null;
        failure = problem;
        deliverResult();
      });
    });
  }

  private void deliverResult() {
    if (!isResumed() || getParentFragmentManager().isStateSaved()
        || requireActivity().isFinishing()) return;
    if (failure != null) {
      failure = null;
      applying = false;
      AlertDialog dialog = (AlertDialog)requireDialog();
      dialog.setMessage(getString(R.string.high_contrast_load_failed));
      dialog.getButton(AlertDialog.BUTTON_POSITIVE).setEnabled(true);
    } else if (colors != null) {
      ((AppearanceActivity)requireActivity()).applyColorPresets(colors);
      close();
    }
  }

  private void close() {
    AppearanceActivity activity = (AppearanceActivity)requireActivity();
    dismissNow();
    activity.showAppearanceDialogs();
  }

  @Override public void onSaveInstanceState(Bundle state) {
    state.putBoolean(APPLYING, applying);
    super.onSaveInstanceState(state);
  }

  @Override public void onDestroy() {
    worker.shutdownNow();
    super.onDestroy();
  }
}

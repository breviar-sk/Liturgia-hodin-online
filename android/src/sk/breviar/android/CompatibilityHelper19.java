package sk.breviar.android;

import android.app.Activity;
import android.util.Log;

public class CompatibilityHelper19 {
  public static void SetLayoutAlgorithmTextAutosizing(android.webkit.WebView wv) {
    try {
      wv.getSettings().setLayoutAlgorithm(
          android.webkit.WebSettings.LayoutAlgorithm.TEXT_AUTOSIZING);
    } catch (java.lang.IllegalArgumentException e) {
      Log.v("breviar", "Can not set TEXT_AUTOSIZING. Cyanogenmod weirdness?");
    }
  }
}

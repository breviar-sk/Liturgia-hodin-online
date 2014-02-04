package sk.breviar.android;

import android.app.Activity;

public class CompatibilityHelper19 {
  public static void SetLayoutAlgorithmTextAutosizing(android.webkit.WebView wv) {
    wv.getSettings().setLayoutAlgorithm(
        android.webkit.WebSettings.LayoutAlgorithm.TEXT_AUTOSIZING);
  }
}

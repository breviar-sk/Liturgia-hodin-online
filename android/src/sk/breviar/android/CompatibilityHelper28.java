package sk.breviar.android;

import android.webkit.WebView;

public class CompatibilityHelper28 {
  static void setDataDirectorySuffix(String suffix) {
    try {
      WebView.setDataDirectorySuffix(suffix);
    } catch (java.lang.IllegalStateException e) {
    }
  }
}

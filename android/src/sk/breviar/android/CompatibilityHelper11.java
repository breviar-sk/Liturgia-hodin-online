package sk.breviar.android;

import android.app.Activity;

public class CompatibilityHelper11 {
  public void recreate(Activity context) {
    context.recreate();
  }

  public static void hideZoomControls(android.webkit.WebSettings settings) {
    settings.setDisplayZoomControls(false);
  }
}

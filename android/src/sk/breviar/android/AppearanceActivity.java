package sk.breviar.android;

import android.content.res.TypedArray;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import androidx.activity.OnBackPressedCallback;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.view.WindowCompat;
import androidx.core.view.WindowInsetsControllerCompat;
import java.util.UUID;

/** Applies the device appearance to every native screen, including the back stack. */
public class AppearanceActivity extends AppCompatActivity {
  private static final String SCREEN_ID = "appearance-screen";
  private static final String QUIET_RETURN = "appearance-quiet-return";
  private boolean eink;
  private String screenId;
  private AppearanceChanges changes;
  private AppearanceChanges.Screen screen;
  private final OnBackPressedCallback appearanceBack = new OnBackPressedCallback(false) {
    @Override public void handleOnBackPressed() {
      if (!isTaskRoot()) {
        finish();
        return;
      }
      // Preserve the platform's launcher-root behavior (which can move the
      // reader's task to the background instead of finishing it).
      setEnabled(false);
      try {
        getOnBackPressedDispatcher().onBackPressed();
      } finally {
        setEnabled(true);
      }
    }
  };

  @Override
  public void onCreate(Bundle state) {
    eink = BreviarApp.getEinkMode(this);
    setTheme(eink ? R.style.BreviarEinkTheme : R.style.BreviarTheme);
    super.onCreate(state);
    screenId = state == null ? null : state.getString(SCREEN_ID);
    if (screenId == null) screenId = UUID.randomUUID().toString();
    changes = ((BreviarApp)getApplication()).appearanceChanges;
    screen = changes.attach(screenId, this, state != null && state.getBoolean(QUIET_RETURN));
    getOnBackPressedDispatcher().addCallback(this, appearanceBack);
    if (screen.quietReturn) prepareAppearanceChange();
  }

  final void changeAppearance(boolean value) {
    BreviarApp.setEinkMode(this, value);
    changes.refresh();
  }

  final void prepareAppearanceChange() {
    // Consume Back ourselves during the handoff, including predictive Back.
    // Toolbar Up and dialog buttons use the same deferred finish() below.
    // Keep this callback for the first return from each affected screen so a
    // system Back preview cannot use its pre-change snapshot.
    appearanceBack.setEnabled(true);
    if (Build.VERSION.SDK_INT >= 34) Api34.quietClose(this);
  }

  void recreateForAppearance() {
    ActivityCompat.recreate(this);
    overridePendingTransition(0, 0);
  }

  @Override
  public void finish() {
    if (screen != null && changes.deferFinish(screen)) return;
    boolean quiet = screen != null && screen.quietReturn;
    if (quiet && Build.VERSION.SDK_INT >= 34) Api34.quietClose(this);
    super.finish();
    if (quiet) overridePendingTransition(0, 0);
  }

  @Override
  protected void onSaveInstanceState(Bundle state) {
    state.putString(SCREEN_ID, screenId);
    state.putBoolean(QUIET_RETURN, screen.quietReturn);
    super.onSaveInstanceState(state);
  }

  @Override
  protected void onDestroy() {
    changes.detach(screenId, this);
    super.onDestroy();
  }

  protected boolean appearanceChanged() {
    return eink != BreviarApp.getEinkMode(this);
  }

  @Override
  protected void onResume() {
    super.onResume();
    if (appearanceChanged()) changes.refresh();
  }

  @Override
  protected void onPostCreate(Bundle state) {
    super.onPostCreate(state);
    // Reapply both appearances after state restoration. A retained window must
    // not keep the previous mode's background or system-bar icon colors.
    View decor = getWindow().getDecorView();
    WindowInsetsControllerCompat bars = WindowCompat.getInsetsController(getWindow(), decor);
    TypedArray appearance = obtainStyledAttributes(new int[]{android.R.attr.windowBackground,
        android.R.attr.windowLightStatusBar, android.R.attr.windowLightNavigationBar});
    try {
      decor.setBackground(appearance.getDrawable(0));
      bars.setAppearanceLightStatusBars(appearance.getBoolean(1, false));
      bars.setAppearanceLightNavigationBars(appearance.getBoolean(2, false));
    } finally {
      appearance.recycle();
    }
    if (eink) {
      // Android 7 cannot draw dark navigation-bar icons.
      if (android.os.Build.VERSION.SDK_INT < 26) getWindow().setNavigationBarColor(android.graphics.Color.BLACK);
      EinkUi.apply(findViewById(android.R.id.content));
    }
    changes.ready(screen, this);
  }

  @android.annotation.TargetApi(34)
  private static class Api34 {
    static void quietClose(AppearanceActivity activity) {
      activity.overrideActivityTransition(OVERRIDE_TRANSITION_CLOSE, 0, 0);
    }
  }
}

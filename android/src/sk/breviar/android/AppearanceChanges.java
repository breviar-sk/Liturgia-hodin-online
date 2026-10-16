package sk.breviar.android;

import android.os.Handler;
import android.os.Looper;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.Map;

/** Main-thread coordination of appearance changes across the existing back stack. */
final class AppearanceChanges {
  static final class Screen {
    AppearanceActivity activity;
    boolean ready, pending, recreating, finishRequested, quietReturn;
  }

  private final Map<String, Screen> screens = new LinkedHashMap<>();
  private final Handler ui = new Handler(Looper.getMainLooper());
  private final Runnable advance = this::advance;

  Screen attach(String id, AppearanceActivity activity, boolean quietReturn) {
    Screen screen = screens.get(id);
    if (screen == null) {
      screen = new Screen();
      screens.put(id, screen);
    }
    screen.activity = activity;
    screen.ready = screen.recreating = false;
    screen.quietReturn |= quietReturn;
    return screen;
  }

  void detach(String id, AppearanceActivity activity) {
    Screen screen = screens.get(id);
    if (screen == null || screen.activity != activity) return;
    if (activity.isChangingConfigurations()) {
      screen.activity = null;
      screen.ready = false;
    } else {
      screens.remove(id);
    }
    schedule();
  }

  void ready(Screen screen, AppearanceActivity activity) {
    // Run after the entire subclass onPostCreate, including drawer restoration.
    ui.post(() -> {
      if (screen.activity != activity || screen.recreating || activity.isDestroyed()) return;
      screen.ready = true;
      screen.pending = activity.appearanceChanged();
      schedule();
    });
  }

  void refresh() {
    // Mark the whole stack before starting any recreation. Registration order
    // keeps covered parents ahead of the visible Device Settings screen.
    for (Screen screen : screens.values()) {
      AppearanceActivity activity = screen.activity;
      if (activity != null && !activity.isFinishing() && activity.appearanceChanged()) {
        screen.pending = true;
        screen.quietReturn = true;
        activity.prepareAppearanceChange();
      }
    }
    schedule();
  }

  boolean deferFinish(Screen screen) {
    for (Screen other : screens.values()) {
      if (other.pending) {
        screen.finishRequested = true;
        return true;
      }
    }
    return false;
  }

  private void schedule() {
    ui.removeCallbacks(advance);
    ui.post(advance);
  }

  private void advance() {
    for (Screen screen : screens.values()) {
      if (!screen.pending) continue;
      AppearanceActivity activity = screen.activity;
      if (screen.recreating || activity == null || !screen.ready) return;
      if (activity.isFinishing()) {
        screen.pending = false;
        continue;
      }
      if (activity.appearanceChanged()) {
        screen.recreating = true;
        activity.recreateForAppearance();
        return;
      }
      // The user may switch back again before this screen needs rebuilding.
      screen.pending = false;
    }
    for (Screen screen : new ArrayList<>(screens.values())) {
      if (screen.finishRequested && screen.ready && screen.activity != null) {
        screen.finishRequested = false;
        screen.activity.finish();
      }
    }
  }
}

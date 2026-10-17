package sk.breviar.android;

import android.content.Context;
import android.content.SharedPreferences;

/** Device-local paging controls, retaining the renderer's existing arrow option. */
final class ReadingNavigation {
  private static final String PREFERENCE = "reading_navigation";

  enum Mode {
    SCROLL("scroll", R.string.navigation_scroll),
    ARROWS("arrows", R.string.navigation_arrows),
    BUTTONS("buttons", R.string.navigation_buttons),
    TAPS("taps", R.string.navigation_taps),
    TAPS_HORIZONTAL("taps_horizontal", R.string.navigation_taps_horizontal);

    final String value;
    final int label;
    Mode(String value, int label) { this.value = value; this.label = label; }

    boolean isTapNavigation() { return this == TAPS || this == TAPS_HORIZONTAL; }
  }

  private ReadingNavigation() {}

  static Mode get(Context context) {
    return get(context, new UrlOptions(BreviarApp.getUrlOptions(context)));
  }

  static Mode get(Context context, UrlOptions options) {
    String saved = BreviarApp.getString(context, PREFERENCE, "");
    if (saved.isEmpty()) {
      // Migrate once. Subsequent appearance changes must not change navigation.
      Mode initial = options.isTransparentNav() ? Mode.ARROWS
          : BreviarApp.getEinkMode(context) ? Mode.BUTTONS : Mode.SCROLL;
      saved = initial.value;
      BreviarApp.setString(context, PREFERENCE, saved);
    }
    // URLs and the web settings can still change the renderer's arrow flag.
    if (options.isTransparentNav()) return Mode.ARROWS;
    if (Mode.TAPS.value.equals(saved)) return Mode.TAPS;
    if (Mode.TAPS_HORIZONTAL.value.equals(saved)) return Mode.TAPS_HORIZONTAL;
    return Mode.BUTTONS.value.equals(saved) ? Mode.BUTTONS : Mode.SCROLL;
  }

  static void set(Context context, Mode mode) {
    set(context, mode, new UrlOptions(BreviarApp.getUrlOptions(context)));
  }

  static void set(Context context, Mode mode, UrlOptions options) {
    options.setTransparentNav(mode == Mode.ARROWS);
    SharedPreferences.Editor editor = context.getSharedPreferences(Util.prefname, 0).edit();
    editor.putString(PREFERENCE, mode.value);
    editor.putString(BreviarApp.stringUrlOptions, options.build(true));
    editor.commit();
  }
}

package sk.breviar.android;

import android.content.Context;
import android.content.SharedPreferences;

/** One durable backup for a temporary shared-prayer session, including across restarts. */
final class SharedPrayerSession {
  private static final String OPTIONS = "shared.original-options";
  private static final String LANGUAGE = "shared.original-language";
  private static final String PAGE = "shared.original-page";
  private static final String POSITION = "shared.original-position";
  private static final String FONT_CSS = "shared.original-font-css";
  private static final String APPEARANCE = "shared.appearance-imported";

  private static SharedPreferences preferences(Context context) {
    return context.getSharedPreferences(Util.prefname, 0);
  }

  static boolean active(Context context) { return preferences(context).contains(OPTIONS); }

  static void begin(Context context, UrlOptions link, String page, float position) {
    begin(context, link, page, position, false, null);
  }

  static void begin(Context context, UrlOptions link, String page, float position,
      boolean appearance, String fontCss) {
    SharedPreferences prefs = preferences(context);
    SharedPreferences.Editor edit = prefs.edit();
    String current = BreviarApp.getUrlOptions(context);
    if (!active(context)) {
      edit.putString(OPTIONS, current).putString(LANGUAGE, prefs.getString("language", "sk"))
          .putString(PAGE, page).putFloat(POSITION, position)
          .putString(FONT_CSS, BreviarApp.getFontsCss(context));
    }
    edit.putBoolean(APPEARANCE, prefs.getBoolean(APPEARANCE, false)
        || (appearance && PrayerLink.hasAppearance(link)));
    if (fontCss != null) edit.putString(BreviarApp.stringFontsCss, fontCss);
    edit.putString(BreviarApp.stringUrlOptions, PrayerLink.applySettings(current, link.build(true), appearance))
        .putString("language", link.params.get("j"));
    // Publish backup and imported settings together, before a render or lifecycle save.
    if (!edit.commit()) throw new IllegalStateException("Cannot save shared prayer settings");
  }

  static final class ReturnPage {
    final String url;
    final float position;
    ReturnPage(String url, float position) { this.url = url; this.position = position; }
  }

  static ReturnPage restore(Context context) {
    SharedPreferences prefs = preferences(context);
    if (!active(context)) return null;
    UrlOptions original = new UrlOptions(prefs.getString(OPTIONS, ""));
    original.params.put("j", prefs.getString(LANGUAGE, "sk"));
    original.params.putIfAbsent("k", "");
    UrlOptions current = new UrlOptions(BreviarApp.getUrlOptions(context));
    boolean appearance = prefs.getBoolean(APPEARANCE, false);
    current.params.keySet().removeIf(key -> PrayerLink.isContentSetting(key)
        && !key.equals("o0") && !key.equals("o2"));
    for (String key : new String[]{"o0", "o2"}) {
      if (!original.params.containsKey(key)) current.params.remove(key);
    }
    original.params.keySet().removeAll(UrlOptions.SELECTION);
    String options = appearance ? original.build(true)
        : PrayerLink.applySettings(current.build(true), original.build(true));
    ReturnPage page = new ReturnPage(prefs.getString(PAGE, null), prefs.getFloat(POSITION, -1));
    SharedPreferences.Editor edit = clear(prefs.edit());
    if (appearance) edit.putString(BreviarApp.stringFontsCss, prefs.getString(FONT_CSS, ""));
    if (!edit.putString(BreviarApp.stringUrlOptions, options)
        .putString("language", original.params.get("j")).commit()) {
      throw new IllegalStateException("Cannot restore prayer settings");
    }
    return page;
  }

  static void keep(Context context) {
    if (!clear(preferences(context).edit()).commit()) {
      throw new IllegalStateException("Cannot keep prayer settings");
    }
  }

  private static SharedPreferences.Editor clear(SharedPreferences.Editor edit) {
    return edit.remove(OPTIONS).remove(LANGUAGE).remove(PAGE).remove(POSITION)
        .remove(FONT_CSS).remove(APPEARANCE);
  }
}

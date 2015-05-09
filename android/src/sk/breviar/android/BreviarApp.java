package sk.breviar.android;

import android.app.Application;
import android.content.Context;
import android.content.res.Configuration;
import android.content.SharedPreferences;

import java.util.Locale;

import sk.breviar.android.Util;

public class BreviarApp extends Application {
  static int eventId = 1;

  static public int getEventId() {
    return eventId;
  }

  @Override
  public void onCreate() {
    initLocale(this);
    super.onCreate();
  }

  static public boolean getOverrideLocale(Context ctx) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    return settings.getBoolean("override_locale", false);
  }

  static public void setOverrideLocale(Context ctx, boolean override) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    SharedPreferences.Editor editor = settings.edit();
    editor.putBoolean("override_locale", override);
    editor.commit();

    initLocale(ctx);
  }

  static public boolean getVolButtons(Context ctx) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    return settings.getBoolean("vol_buttons", false);
  }

  static public void setVolButtons(Context ctx, boolean use_for_scrolling) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    SharedPreferences.Editor editor = settings.edit();
    editor.putBoolean("vol_buttons", use_for_scrolling);
    editor.commit();
  }

  static public boolean getDimLock(Context ctx) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    return settings.getBoolean("dim_lock", true);
  }

  static public void setDimLock(Context ctx, boolean dim_lock) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    SharedPreferences.Editor editor = settings.edit();
    editor.putBoolean("dim_lock", dim_lock);
    editor.commit();
  }

  static public boolean getNavBarShown(Context ctx) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    return settings.getBoolean("nav_bar_shown", true);
  }

  static public void setNavBarShown(Context ctx, boolean shown) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    SharedPreferences.Editor editor = settings.edit();
    editor.putBoolean("nav_bar_shown", shown);
    editor.commit();
  }

  static public boolean getMute(Context ctx) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    return settings.getBoolean("mute", false);
  }

  static public void setMute(Context ctx, boolean mute) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    SharedPreferences.Editor editor = settings.edit();
    editor.putBoolean("mute", mute);
    editor.commit();
  }

  static public boolean getMenuEpiphanySunday(Context ctx) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    return settings.getBoolean("calendar_epiphany_set_on_sunday", false);
  }

  static public void setMenuEpiphanySunday(Context ctx, boolean status) {
    // ToDo: give some code to change URL options similar as follows: (taken from public boolean onOptionsItemSelected() in Breviar.java)
    // UrlOptions opts;
    // opts = new UrlOptions(wv.getUrl() + S.getOpts().replaceAll("&amp;", "&"), true);
    // opts.setEpiphanySunday(!opts.isEpiphanySunday());
    // wv.loadUrl(opts.build());
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    SharedPreferences.Editor editor = settings.edit();
    editor.putBoolean("calendar_epiphany_set_on_sunday", status);
    editor.commit();
  }

  static public boolean getMenuAscensionSunday(Context ctx) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    return settings.getBoolean("calendar_ascension_set_on_sunday", false);
  }

  static public void setMenuAscensionSunday(Context ctx, boolean status) {
    // ToDo: give some code to change URL options similar as follows: (taken from public boolean onOptionsItemSelected() in Breviar.java)
    // UrlOptions opts;
    // opts = new UrlOptions(wv.getUrl() + S.getOpts().replaceAll("&amp;", "&"), true);
    // opts.setAscensionSunday(!opts.isAscensionSunday());
    // wv.loadUrl(opts.build());
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    SharedPreferences.Editor editor = settings.edit();
    editor.putBoolean("calendar_ascension_set_on_sunday", status);
    editor.commit();
  }

  static public boolean getMenuBodyBloodSunday(Context ctx) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    return settings.getBoolean("calendar_body_blood_set_on_sunday", false);
  }

  static public void setMenuBodyBloodSunday(Context ctx, boolean status) {
    // ToDo: give some code to change URL options similar as follows: (taken from public boolean onOptionsItemSelected() in Breviar.java)
    // UrlOptions opts;
    // opts = new UrlOptions(wv.getUrl() + S.getOpts().replaceAll("&amp;", "&"), true);
    // opts.setBodyBloodSunday(!opts.isBodyBloodSunday());
    // wv.loadUrl(opts.build());
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    SharedPreferences.Editor editor = settings.edit();
    editor.putBoolean("calendar_body_blood_set_on_sunday", status);
    editor.commit();
  }

  static public boolean getMenuEmphasizeLocalCalendar(Context ctx) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    return settings.getBoolean("emphasize_local_calendar_set_on", false);
  }

  static public void setMenuEmphasizeLocalCalendar(Context ctx, boolean status) {
    // ToDo: give some code to change URL options similar as follows: (taken from public boolean onOptionsItemSelected() in Breviar.java)
    // UrlOptions opts;
    // opts = new UrlOptions(wv.getUrl() + S.getOpts().replaceAll("&amp;", "&"), true);
    // opts.setEmphasizeLocalCalendar(!opts.isEmphasizeLocalCalendar());
    // wv.loadUrl(opts.build());
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    SharedPreferences.Editor editor = settings.edit();
    editor.putBoolean("emphasize_local_calendar_set_on", status);
    editor.commit();
  }

  static public void initLocale(Context ctx) {
    Configuration cfg = new Configuration();
    if (getOverrideLocale(ctx)) {
      SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
      String lang = settings.getString("language", "sk");
      if (lang.equals("cz")) lang = "cs";
      cfg.locale = new Locale(lang);
    } else {
      cfg.locale = Locale.getDefault();
    }
    ctx.getResources().updateConfiguration(cfg, null);
    eventId++;
  }
}


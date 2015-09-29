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

  static public String getUrlOptions(Context ctx) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    return settings.getString("params", "");
  }

  static public void setUrlOptions(Context ctx, String opts) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    SharedPreferences.Editor editor = settings.edit();
    editor.putString("params", opts);
    editor.commit();
  }

  static public boolean getLongClickTogglesBar(Context ctx) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    return settings.getBoolean("long_click_toggles_bar", false);
  }

  static public void setLongClickTogglesBar(Context ctx, boolean toggles) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    SharedPreferences.Editor editor = settings.edit();
    editor.putBoolean("long_click_toggles_bar", toggles);
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


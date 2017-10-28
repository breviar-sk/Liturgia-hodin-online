package sk.breviar.android;

import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.content.res.Configuration;
import android.content.SharedPreferences;
import android.os.Build;

import java.util.Locale;

import sk.breviar.android.CompatibilityHelper17;
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
    String output = settings.getString("params", "");
    return output;
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

  static Locale appLanguageToLocale(String lang) {
    if (lang.equals("cz")) lang = "cs";
    return new Locale(lang);
  }

  static Locale currentLocale(Context ctx) {
    if (getOverrideLocale(ctx)) {
      SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
      return appLanguageToLocale(settings.getString("language", "sk"));
    } else {
      return Locale.getDefault();
    }
  }

  // This is needed for api levels < 24.
  static public void initLocale(Context ctx) {
    if (Build.VERSION.SDK_INT < 17) {
      Configuration cfg = new Configuration();
      cfg.locale = currentLocale(ctx);
      ctx.getResources().updateConfiguration(cfg, null);
    }
    eventId++;
  }

  // For api levels >=17, we can (and for >= 24 we must) explicitly attach
  // proper locale to every activity at startup.
  static public void applyCustomLocale(Activity activity) {
    if (Build.VERSION.SDK_INT >= 17) {
      new CompatibilityHelper17().applyLocale(activity, currentLocale(activity));
    }
  }
}


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
  public static final int NOTIFY_ALARM_ID = 1;
  public static final int NOTIFY_TTS_ID = 2;

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

  static Locale appLanguageToLocale(String lang) {
    if (lang.equals("cz") || lang.equals("c2")) lang = "cs";
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

  static public Context getLocaleForCurrentLanguage(Context ctx) {
    Configuration cfg = new Configuration();
    cfg.locale = currentLocale(ctx);
    if (Build.VERSION.SDK_INT < 24) {
      ctx.getResources().updateConfiguration(cfg, null);
      return ctx;
    } else {
      return ctx.createConfigurationContext(cfg);
    }
  }

  // This is needed for api levels < 24.
  static public void initLocale(Context ctx) {
    if (Build.VERSION.SDK_INT < 24) {
      Configuration cfg = new Configuration();
      cfg.locale = currentLocale(ctx);
      ctx.getResources().updateConfiguration(cfg, null);
    }
    eventId++;
  }

  // For api levels >=17, we can (and for >= 24 we must) explicitly attach
  // proper locale to every activity at startup.
  static public void applyCustomLocale(Activity activity) {
    if (Build.VERSION.SDK_INT >= 24) {
      new CompatibilityHelper17().applyLocale(activity, currentLocale(activity));
    }
  }

  static public Context getContextForCustomLocale(Context context) {
    if (Build.VERSION.SDK_INT >= 17) {
      return new CompatibilityHelper17().getContextForLocale(
          context, currentLocale(context));
    } else {
      return context;
    }
  }

  static public void setBoolean(Context ctx, String key, boolean value) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    SharedPreferences.Editor editor = settings.edit();
    editor.putBoolean(key, value);
    editor.commit();
  }

  static public boolean getBoolean(Context ctx, String key, boolean default_value) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    return settings.getBoolean(key, default_value);
  }

  static public void setString(Context ctx, String key, String value) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    SharedPreferences.Editor editor = settings.edit();
    editor.putString(key, value);
    editor.commit();
  }

  static public String getString(Context ctx, String key, String default_value) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    return settings.getString(key, default_value);
  }

  static public void resetScale(Context ctx) {
    SharedPreferences settings = ctx.getSharedPreferences(Util.prefname, 0);
    SharedPreferences.Editor editor = settings.edit();
    editor.remove("scale");  // TODO: cleanup use in Breviar.java
    editor.commit();
  }

  static final String booleanVolButtons = "vol_buttons";
  static final String booleanDimLock = "dim_lock";
  static final String booleanMute = "mute";
  static final String booleanTtsUsePauseInPsalms = "tts_use_pause_in_psalms";
  static final String booleanNoZoom = "no_zoom";
  static final String stringUrlOptions = "params";
  static final String stringFontsCss = "fonts_css";

  static public boolean getVolButtons(Context ctx) {
    return getBoolean(ctx, booleanVolButtons, true);
  }

  static public void setVolButtons(Context ctx, boolean use_for_scrolling) {
    setBoolean(ctx, booleanVolButtons, use_for_scrolling);
  }

  static public boolean getDimLock(Context ctx) {
    return getBoolean(ctx, booleanDimLock, true);
  }

  static public void setDimLock(Context ctx, boolean dim_lock) {
    setBoolean(ctx, booleanDimLock, dim_lock);
  }

  static public boolean getMute(Context ctx) {
    return getBoolean(ctx, booleanMute, false);
  }

  static public void setMute(Context ctx, boolean mute) {
    setBoolean(ctx, booleanMute, mute);
  }

  static public boolean getTtsUsePauseInPsalms(Context ctx) {
    return getBoolean(ctx, booleanTtsUsePauseInPsalms, true);
  }

  static public void setTtsUsePauseInPsalms(Context ctx, boolean use_pause) {
    setBoolean(ctx, booleanTtsUsePauseInPsalms, use_pause);
  }

  static public boolean getNoZoom(Context ctx) {
    return getBoolean(ctx, booleanNoZoom, false);
  }

  static public void setNoZoom(Context ctx, boolean no_zoom) {
    setBoolean(ctx, booleanNoZoom, no_zoom);
  }

  static public String getUrlOptions(Context ctx) {
    return getString(ctx, stringUrlOptions, "");
  }

  static public void setUrlOptions(Context ctx, String opts) {
    setString(ctx, stringUrlOptions, opts);
  }

  static public String getFontsCss(Context ctx) {
    return getString(ctx, stringFontsCss, "");
  }

  static public void setFontsCss(Context ctx, String css) {
    setString(ctx, stringFontsCss, css);
  }

}


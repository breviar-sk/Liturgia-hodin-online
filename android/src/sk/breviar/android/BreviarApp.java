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


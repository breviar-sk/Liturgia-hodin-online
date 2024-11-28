package sk.breviar.android;

import java.lang.Runnable;
import java.util.Map;

import android.content.Context;
import android.graphics.Typeface; import android.os.Bundle;
import android.support.v4.view.MenuItemCompat;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.TextView;

import sk.breviar.android.Fonts;

public class DisplaySettings extends SettingsActivity {
  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    inflateMenu(R.menu.display_settings);
    getSupportActionBar().setTitle(getString(R.string.display_settings_title));

    final SettingsActivity act = this;
    handleSwitch(R.id.first_vespers_buttons, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setFirstVespersButtons(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isFirstVespersButtons(); }
    });
    handleSwitch(R.id.navigation, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setNavigation(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isNavigation(); }
    });
    handleSwitch(R.id.smart_buttons, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setSmartButtons(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isSmartButtons(); }
    });
    handleSwitch(R.id.night_mode, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setNightmode(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isNightmode(); }
    });
    handleColor(R.id.background_day_mode, new String[]{"ffffcc", "ffddbb", "ddeeff"}, new ColorUrlOption() {
      public void setOpt(UrlOptions opts, String value) { opts.setBackgroundDayMode(value); }
      public String getOpt(UrlOptions opts) { return opts.getBackgroundDayMode(); }
    });
    handleColor(R.id.background_night_mode, new String[]{"111111", "222222", "333333"}, new ColorUrlOption() {
      public void setOpt(UrlOptions opts, String value) { opts.setBackgroundNightMode(value); }
      public String getOpt(UrlOptions opts) { return opts.getBackgroundNightMode(); }
    });
    handleSwitch(R.id.normal_font, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setOnlyNonBoldFont(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isOnlyNonBoldFont(); }
    });
    handleSwitch(R.id.buttons_rounded_corners, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setRoundedCorners(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isRoundedCorners(); }
    });
    handleSwitch(R.id.buttons_order, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setButtonsOrder(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isButtonsOrder(); }
    });
    handleSwitch(R.id.transparent_nav, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setTransparentNav(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isTransparentNav(); }
    });
    handleSwitch(R.id.transparent_nav_left, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setTransparentNavLeft(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isTransparentNavLeft(); }
    });
    handleSwitch(R.id.transparent_nav_down_only, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setTransparentNavDownOnly(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isTransparentNavDownOnly(); }
    });
    handleInt(R.id.option_mm, 1, 200, new IntUrlOption() {
      public void setOpt(UrlOptions opts, int value) { opts.setMm(value); }
      public void resetOpt(UrlOptions opts) { opts.resetMm(); }
      public int getOpt(UrlOptions opts) { return opts.getMm(); }
    });
    handleInt(R.id.option_lh, 1, 500, new IntUrlOption() {
      public void setOpt(UrlOptions opts, int value) { opts.setLh(value); }
      public void resetOpt(UrlOptions opts) { opts.resetLh(); }
      public int getOpt(UrlOptions opts) { return opts.getLh(); }
    });
    handleInt(R.id.option_ff, 4, 60, new IntUrlOption() {
      public void setOpt(UrlOptions opts, int value) { BreviarApp.resetScale(act); opts.setFf(value); }
      public void resetOpt(UrlOptions opts) { BreviarApp.resetScale(act); opts.resetFf(); }
      public int getOpt(UrlOptions opts) { return opts.getFf(); }
    });

    // Font select
    {
      try {
        UrlOptions opts = new UrlOptions(BreviarApp.getUrlOptions(getApplicationContext()));
        String current_font = opts.getFont();

        Spinner spinner = ((Spinner)MenuItemCompat.getActionView(
            navigationView.getMenu().findItem(R.id.font_select)));
        FontSelectAdapter adapter = new FontSelectAdapter(this);
        spinner.setAdapter(adapter);
        if (current_font != null) {
          for (int i = 0; i < adapter.getCount(); ++i) {
            FontInfo fi = adapter.getItem(i);
            if (fi != null && fi.family_name != null && fi.family_name.equals(current_font)) {
              spinner.setSelection(i);
              break;
            }
          }
        }
        spinner.setOnItemSelectedListener(adapter);
      } catch (java.lang.NullPointerException e) {
        Log.v("breviar", "Cannot setup navigation view!");
      }
    }
  }

  static class FontInfo {
    public FontInfo(String name_, String family_name_, Typeface typeface_, Fonts.FontMap.Variants variants_) {
      name = name_;
      family_name = family_name_;
      typeface = typeface_;
      variants = variants_;
    }

    String name;
    String family_name;
    Typeface typeface;
    Fonts.FontMap.Variants variants;

    public String toString() {
      return name;
    }
  }

  static class FontSelectAdapter extends ArrayAdapter<FontInfo> implements AdapterView.OnItemSelectedListener {
    public FontSelectAdapter(Context ctx) {
      super(ctx, android.R.layout.simple_spinner_item);
      setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
      add(new FontInfo(ctx.getString(R.string.default_font), null, null, null));
      add(new FontInfo(ctx.getString(R.string.default_serif_font), "serif", Typeface.SERIF, null));
      add(new FontInfo(ctx.getString(R.string.default_sans_serif_font), "sans-serif", Typeface.SANS_SERIF, null));

      Fonts.ResetFonts();
      for (Map.Entry<String, Fonts.FontMap.Variants> e : Fonts.GetFonts(ctx).families.entrySet()) {
        try {
          Typeface t = Typeface.createFromFile(e.getValue().GetDisplayFont().filename);
          add(new FontInfo(e.getKey(), e.getKey(), t, e.getValue()));
        } catch (java.lang.Exception exc) {
          Log.v("breviar", "Skipped font: " + exc.getMessage());
        }
      }

      // todo: set current selection
    }

    void SetupView(int position, View view) {
      if (view == null) return;
      if (!(view instanceof TextView)) return;

      FontInfo fi = getItem(position);
      if (fi == null) return;
      if (fi.typeface == null) return;
      ((TextView)view).setTypeface(fi.typeface);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
      View res = super.getView(position, convertView, parent);
      SetupView(position, res);
      return res;
    }

    @Override
    public View getDropDownView(int position, View convertView, ViewGroup parent) {
      View res = super.getDropDownView(position, convertView, parent);
      SetupView(position, res);
      return res;
    }

    @Override
    public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
      FontInfo fi = getItem(position);
      if (fi == null) return;

      UrlOptions opts = new UrlOptions(BreviarApp.getUrlOptions(getContext().getApplicationContext()));
      if (fi.family_name == null) {
        Log.v("breviar", "Removing font selection");
        opts.setFont("");
      } else {
        Log.v("breviar", "Setting font to " + fi.family_name);
        opts.setFont(fi.family_name);
      }
      Context ctx = getContext().getApplicationContext();
      BreviarApp.setUrlOptions(ctx, opts.build(true));
      String css;
      if (fi.variants == null) {
        css = "";
      } else {
        css = fi.variants.GetCss();
      }
      BreviarApp.setFontsCss(ctx, css);
    }

    @Override
    public void onNothingSelected(AdapterView<?> parent) {
    }

  }

  // TODO: Override updateMenu to refresh font selection adapter if there is
  // any other place that changes fonts.
}


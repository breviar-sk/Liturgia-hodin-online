package sk.breviar.android;

import java.lang.Runnable;

import android.os.Bundle;

public class PrayerSettings extends SettingsActivity {
  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    inflateMenu(R.menu.prayer_settings);
    getSupportActionBar().setTitle(getString(R.string.prayer_settings_title));

    final SettingsActivity act = this;
    handleSwitch(R.id.various_options_in_prayers, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setDisplayVariousOptions(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isDisplayVariousOptions(); }
    });
    handleSwitch(R.id.alternatives, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setDisplayAlternatives(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isDisplayAlternatives(); }
    });

    handleSwitch(R.id.display_communia_info, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setDisplayCommuniaInfo(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isDisplayCommuniaInfo(); }
    });
    handleSwitch(R.id.verse_numbering, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setVerseNumbering(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isVerseNumbering(); }
    });
    handleSwitch(R.id.bible_references, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) {
        opts.setBibleReferences(value);
        if (!value && opts.isBibleRefBibleCom()) {
          opts.setBibleRefBibleCom(false);
        }
      }
      public boolean getOpt(UrlOptions opts) { return opts.isBibleReferences(); }
    });
    handleSwitch(R.id.bible_ref_bible_com, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) {
        opts.setBibleRefBibleCom(value);
        if (value && !opts.isBibleReferences()) {
          opts.setBibleReferences(true);
        }
      }
      public boolean getOpt(UrlOptions opts) { return opts.isBibleRefBibleCom(); }
    });
    handleSwitch(R.id.footnotes, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setFootnotes(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isFootnotes(); }
    });
    handleSwitch(R.id.liturgical_readings, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setLiturgicalReadings(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isLiturgicalReadings(); }
    });
    handleSwitch(R.id.psalms_omissions, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setPsalmsOmissions(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isPsalmsOmissions(); }
    });
    handleSwitch(R.id.italics_conditional, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setItalicsConditional(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isItalicsConditional(); }
    });
    handleSwitch(R.id.printed_edtition, new BooleanUrlOption() {
      public void setOpt(UrlOptions opts, boolean value) { opts.setPrintedEdition(value); }
      public boolean getOpt(UrlOptions opts) { return opts.isPrintedEdition(); }
    });
  }
}

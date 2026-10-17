package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.graphics.Typeface;
import android.graphics.drawable.ColorDrawable;
import android.graphics.drawable.GradientDrawable;
import android.os.Looper;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.TextView;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.TimeUnit;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.Shadows;
import org.robolectric.android.controller.ActivityController;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.Implementation;
import org.robolectric.annotation.Implements;
import org.robolectric.annotation.LooperMode;
import org.robolectric.util.ReflectionHelpers;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = {24, 35}, shadows = {DisplaySettingsTest.FontLoader.class, XmlSettingsActivityTest.SettingsServer.class})
@LooperMode(LooperMode.Mode.PAUSED)
public class DisplaySettingsTest {
  private final Context context = RuntimeEnvironment.getApplication();

  @Implements(value = Fonts.class, isInAndroidSdk = false)
  public static class FontLoader {
    static CountDownLatch entered, release;
    static boolean fail;

    @Implementation protected static List<Fonts.Choice> getChoices(Context context) throws InterruptedException {
      assertNotSame("Font discovery/previews must run off the UI thread",
          Looper.getMainLooper().getThread(), Thread.currentThread());
      entered.countDown();
      assertTrue("Font load timed out", release.await(10, TimeUnit.SECONDS));
      if (fail) throw new IllegalStateException("Font storage unavailable");
      return Arrays.asList(new Fonts.Choice("Custom", Typeface.MONOSPACE, "custom CSS"),
          new Fonts.Choice("Other", Typeface.SERIF, "other CSS"));
    }
  }

  @Before public void prepare() {
    FontLoader.entered = new CountDownLatch(1);
    FontLoader.release = new CountDownLatch(0);
    FontLoader.fail = false;
  }

  @After public void drainLoader() throws Exception {
    FontLoader.release.countDown();
    awaitFonts();
  }

  private static void awaitFonts() throws Exception {
    ExecutorService worker = ReflectionHelpers.getStaticField(FontPicker.class, "fontWorker");
    worker.submit(() -> {}).get(10, TimeUnit.SECONDS);
    Shadows.shadowOf(Looper.getMainLooper()).idle();
  }

  private static Spinner spinner(DisplaySettings activity) {
    return (Spinner)activity.menuItem("appearance.font").getActionView();
  }

  private static String selected(Spinner spinner) {
    return ((FontPicker.FontInfo)spinner.getSelectedItem()).family_name;
  }

  private static void select(Spinner spinner, String family) {
    for (int i = 0; i < spinner.getCount(); ++i) {
      if (((FontPicker.FontInfo)spinner.getItemAtPosition(i)).family_name.equals(family)) {
        spinner.setSelection(i);
        // Exercise the same listener even if this detached test view has not laid out yet.
        spinner.getOnItemSelectedListener().onItemSelected(spinner, null, i, i);
        return;
      }
    }
    fail("Missing font: " + family);
  }

  @Test public void slowFontLoadingLeavesSettingsAndBackUsable() throws Exception {
    String options = "&amp;f=Custom&amp;o0=123";
    BreviarApp.setUrlOptions(context, options);
    BreviarApp.setFontsCss(context, "saved CSS");
    FontLoader.release = new CountDownLatch(1);
    try (ActivityController<DisplaySettings> controller = Robolectric.buildActivity(DisplaySettings.class).setup()) {
      XmlSettingsActivityTest.awaitSettings(controller.get());
      DisplaySettings activity = controller.get();
      assertTrue(FontLoader.entered.await(10, TimeUnit.SECONDS));
      Spinner spinner = spinner(activity);
      assertFalse(spinner.isEnabled());
      assertEquals("Custom", selected(spinner));
      Shadows.shadowOf(Looper.getMainLooper()).idle();
      assertEquals(options, BreviarApp.getUrlOptions(context));
      activity.navigationView.getMenu().performIdentifierAction(activity.menuItem("appearance.night-mode").getItemId(), 0);
      assertTrue(new UrlOptions(BreviarApp.getUrlOptions(context)).isNightmode());
      activity.onSupportNavigateUp();
      assertTrue(activity.isFinishing());
      FontLoader.release.countDown();
      awaitFonts();
      assertFalse("Late results must not update a closed page", spinner.isEnabled());
      assertEquals("saved CSS", BreviarApp.getFontsCss(context));
    }
  }

  @Test public void openingAndRecreatingPreservesFontWithoutWritingPreferences() throws Exception {
    BreviarApp.setEinkMode(context, true);
    String options = "&amp;f=Custom&amp;o0=123";
    BreviarApp.setUrlOptions(context, options);
    BreviarApp.setFontsCss(context, "saved CSS");
    ReadingNavigation.get(context); // Complete the existing one-time navigation migration first.
    List<String> changes = new ArrayList<>();
    SharedPreferences prefs = context.getSharedPreferences(Util.prefname, 0);
    SharedPreferences.OnSharedPreferenceChangeListener listener = (p, key) -> changes.add(key);
    prefs.registerOnSharedPreferenceChangeListener(listener);
    try (ActivityController<DisplaySettings> controller = Robolectric.buildActivity(DisplaySettings.class).setup()) {
      XmlSettingsActivityTest.awaitSettings(controller.get());
      awaitFonts();
      Spinner spinner = spinner(controller.get());
      assertTrue(spinner.isEnabled());
      assertEquals("Custom", selected(spinner));
      select(spinner, "Custom");
      TextView row = (TextView)spinner.getAdapter().getView(spinner.getSelectedItemPosition(), null, spinner);
      assertEquals(Color.BLACK, row.getCurrentTextColor());
      assertEquals(Typeface.MONOSPACE, row.getTypeface());
      controller.recreate();
      XmlSettingsActivityTest.awaitSettings(controller.get());
      awaitFonts();
      assertEquals("Custom", selected(spinner(controller.get())));
      assertEquals(options, BreviarApp.getUrlOptions(context));
      assertEquals("saved CSS", BreviarApp.getFontsCss(context));
      assertTrue("Unexpected preference changes: " + changes, changes.isEmpty());
    } finally {
      prefs.unregisterOnSharedPreferenceChangeListener(listener);
    }
  }

  @Test public void selectingFontPublishesOptionsAndCssTogetherAndKeepsRecentEdits() throws Exception {
    BreviarApp.setUrlOptions(context, "&amp;f=Custom");
    BreviarApp.setFontsCss(context, "custom CSS");
    try (ActivityController<DisplaySettings> controller = Robolectric.buildActivity(DisplaySettings.class).setup()) {
      XmlSettingsActivityTest.awaitSettings(controller.get());
      awaitFonts();
      // Another display option changes after the font catalog was loaded.
      BreviarApp.setUrlOptions(context, "&amp;f=Custom&amp;o0=456&amp;k=sj");
      SharedPreferences prefs = context.getSharedPreferences(Util.prefname, 0);
      SharedPreferences.OnSharedPreferenceChangeListener listener = (p, key) -> {
        assertEquals("Other", new UrlOptions(p.getString("params", "")).getFont());
        assertEquals("other CSS", p.getString("fonts_css", ""));
      };
      prefs.registerOnSharedPreferenceChangeListener(listener);
      Spinner spinner = spinner(controller.get());
      try {
        select(spinner, "Other");
        Shadows.shadowOf(Looper.getMainLooper()).idle();
        UrlOptions saved = new UrlOptions(BreviarApp.getUrlOptions(context));
        assertEquals("Other", saved.getFont());
        assertEquals("other CSS", BreviarApp.getFontsCss(context));
        assertEquals("456", saved.params.get("o0"));
        assertEquals("sj", saved.params.get("k"));
      } finally {
        prefs.unregisterOnSharedPreferenceChangeListener(listener);
      }
      select(spinner, "");
      assertEquals("", new UrlOptions(BreviarApp.getUrlOptions(context)).getFont());
      assertEquals("", BreviarApp.getFontsCss(context));
    }
  }

  @Test public void failedDiscoveryPreservesUnavailableFontAndAllowsDefaultSelection() throws Exception {
    FontLoader.fail = true;
    BreviarApp.setUrlOptions(context, "&amp;f=Missing");
    BreviarApp.setFontsCss(context, "old CSS");
    try (ActivityController<DisplaySettings> controller = Robolectric.buildActivity(DisplaySettings.class).setup()) {
      XmlSettingsActivityTest.awaitSettings(controller.get());
      awaitFonts();
      Spinner spinner = spinner(controller.get());
      assertTrue(spinner.isEnabled());
      assertEquals("Missing", selected(spinner));
      assertEquals("old CSS", BreviarApp.getFontsCss(context));
      select(spinner, "");
      assertEquals("", BreviarApp.getFontsCss(context));
    }
  }

  @Test public void resultForDestroyedActivityDoesNotReplaceNewActivitysMenu() throws Exception {
    FontLoader.release = new CountDownLatch(1);
    ActivityController<DisplaySettings> old = Robolectric.buildActivity(DisplaySettings.class).setup();
    XmlSettingsActivityTest.awaitSettings(old.get());
    assertTrue(FontLoader.entered.await(10, TimeUnit.SECONDS));
    Spinner previous = spinner(old.get());
    old.close();
    try (ActivityController<DisplaySettings> current = Robolectric.buildActivity(DisplaySettings.class).setup()) {
      XmlSettingsActivityTest.awaitSettings(current.get());
      FontLoader.release.countDown();
      awaitFonts();
      assertFalse(previous.isEnabled());
      assertTrue(spinner(current.get()).isEnabled());
      assertEquals("", selected(spinner(current.get())));
    }
  }

  @Test public void fontPickerPreservesTheStockPhonePalette() throws Exception {
    try (ActivityController<DisplaySettings> controller = Robolectric.buildActivity(DisplaySettings.class).setup()) {
      XmlSettingsActivityTest.awaitSettings(controller.get());
      awaitFonts();
      Spinner picker = spinner(controller.get());
      Spinner stock = new Spinner(controller.get(), Spinner.MODE_DROPDOWN);
      GradientDrawable stockBackground = (GradientDrawable)stock.getPopupBackground();
      GradientDrawable background = (GradientDrawable)picker.getPopupBackground();
      assertEquals(stockBackground.getColor(), background.getColor());
      assertEquals(stockBackground.getCornerRadius(), background.getCornerRadius(), 0.01f);
      ArrayAdapter<String> stockRows = new ArrayAdapter<>(controller.get(), android.R.layout.simple_spinner_item,
          new String[]{"Preview"});
      stockRows.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
      for (boolean dropdown : new boolean[]{false, true}) {
        TextView original = (TextView)(dropdown ? stockRows.getDropDownView(0, null, stock)
            : stockRows.getView(0, null, stock));
        TextView preview = (TextView)(dropdown ? picker.getAdapter().getDropDownView(0, null, picker)
            : picker.getAdapter().getView(0, null, picker));
        for (boolean enabled : new boolean[]{false, true}) {
          original.setEnabled(enabled);
          preview.setEnabled(enabled);
          assertEquals(original.getCurrentTextColor(), preview.getCurrentTextColor());
        }
      }
    }
  }

  @Test public void fontPreviewsRemainReadableWithConflictingFrameworkColors() throws Exception {
    for (boolean eink : new boolean[]{false, true}) {
      BreviarApp.setEinkMode(context, eink);
      BreviarApp.setUrlOptions(context, "&amp;f=Custom");
      try (ActivityController<DisplaySettings> controller = Robolectric.buildActivity(DisplaySettings.class).create()) {
        // Simulate firmware supplying light popup/row defaults to our dark app.
        controller.get().getTheme().applyStyle(android.R.style.Theme_Material_Light, true);
        controller.start().resume();
        XmlSettingsActivityTest.awaitSettings(controller.get());
        awaitFonts();
        Spinner picker = spinner(controller.get());
        assertEquals(eink ? Color.WHITE : 0xff303030,
            ((GradientDrawable)picker.getPopupBackground()).getColor().getDefaultColor());
        int selected = picker.getSelectedItemPosition();
        for (boolean dropdown : new boolean[]{false, true}) {
          TextView row = (TextView)(dropdown ? picker.getAdapter().getDropDownView(selected, null, picker)
              : picker.getAdapter().getView(selected, null, picker));
          assertEquals(eink ? Color.BLACK : Color.WHITE, row.getCurrentTextColor());
          assertEquals(Typeface.MONOSPACE, row.getTypeface());
          // Rebinding must clear conflicting colors/backgrounds from recycled rows too.
          row.setTextColor(eink ? Color.WHITE : Color.BLACK);
          row.setBackgroundColor(Color.WHITE);
          row = (TextView)(dropdown ? picker.getAdapter().getDropDownView(0, row, picker)
              : picker.getAdapter().getView(0, row, picker));
          assertEquals(eink ? Color.BLACK : Color.WHITE, row.getCurrentTextColor());
          assertEquals(Color.TRANSPARENT, ((ColorDrawable)row.getBackground()).getColor());
          assertEquals(Typeface.DEFAULT, row.getTypeface());
        }
      }
    }
  }
}

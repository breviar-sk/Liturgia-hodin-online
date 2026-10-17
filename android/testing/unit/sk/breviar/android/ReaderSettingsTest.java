package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
import android.view.View;
import android.webkit.WebView;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.android.controller.ActivityController;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.Implementation;
import org.robolectric.annotation.Implements;
import org.robolectric.annotation.LooperMode;
import org.robolectric.shadow.api.Shadow;
import org.robolectric.shadows.ShadowWebView;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = {24, 35}, shadows = {
    XmlSettingsActivityTest.SettingsServer.class, ReaderSettingsTest.RecordingWebView.class})
@LooperMode(LooperMode.Mode.PAUSED)
public class ReaderSettingsTest {
  private final Context context = RuntimeEnvironment.getApplication();
  private static final String OPTIONS = "&amp;o0=1&amp;k=sj&amp;c=1";
  private static final String PRAYER = "http://127.0.0.1:50000/l.cgi?qt=pdt&d=16&m=10&r=2026&p=1";

  @Implements(WebView.class)
  public static class RecordingWebView extends ShadowWebView {
    int pageLoads;
    @Implementation protected void loadUrl(String url) {
      if (!url.startsWith("javascript:")) ++pageLoads;
      super.loadUrl(url);
    }
    @Implementation protected int getContentHeight() { return 1000; }
  }

  @Before public void configure() {
    BreviarApp.setString(context, "version", context.getString(R.string.version));
    BreviarApp.setEinkMode(context, false);
    BreviarApp.setUrlOptions(context, OPTIONS);
  }

  private RecordingWebView openPrayer(Breviar reader) {
    reader.wv.loadUrl(PRAYER);
    reader.wv.scrollTo(0, 400);
    reader.scroll_to = -1;
    Breviar.S.setOpts(OPTIONS); // Effective defaults need not appear in the page URL.
    return Shadow.extract(reader.wv);
  }

  @Test public void unchangedSettingsLanguageAndCalendarKeepThePageInBothAppearances() {
    for (boolean eink : new boolean[]{false, true}) {
      BreviarApp.setEinkMode(context, eink);
      try (ActivityController<EinkModeTest.Reader> controller =
          Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
        Breviar reader = controller.get();
        RecordingWebView web = openPrayer(reader);
        int loads = web.pageLoads;
        for (int menu : new int[]{R.id.settings, R.id.lang_select, R.id.calendar_select}) {
          reader.onNavigationItemSelected(menu);
          controller.pause().stop();
          controller.restart().start().resume();
          assertEquals(loads, web.pageLoads);
          assertEquals(PRAYER, reader.wv.getUrl());
          assertEquals(400, reader.wv.getScrollY());
          assertEquals(-1f, reader.scroll_to, 0f);
          assertFalse(reader.need_to_reload_preferences);
        }
      }
    }
  }

  @Test public void nativeControlsAndRestoredOptionsDoNotReloadThePage() {
    try (ActivityController<EinkModeTest.Reader> controller =
        Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
      Breviar reader = controller.get();
      RecordingWebView web = openPrayer(reader);
      int loads = web.pageLoads;
      for (ReadingNavigation.Mode mode : new ReadingNavigation.Mode[]{
          ReadingNavigation.Mode.BUTTONS, ReadingNavigation.Mode.TAPS, ReadingNavigation.Mode.TAPS_HORIZONTAL}) {
        reader.onNavigationItemSelected(R.id.settings);
        controller.pause().stop();
        BreviarApp.setNoZoom(context, true);
        // A change followed by undo, with a different parameter order, is also unchanged.
        BreviarApp.setUrlOptions(context, "&amp;k=&amp;o0=7&amp;c=0");
        BreviarApp.setUrlOptions(context, "&amp;c=1&amp;k=sj&amp;o0=1");
        ReadingNavigation.set(context, mode);
        controller.restart().start().resume();
        assertEquals(loads, web.pageLoads);
        assertEquals(400, reader.wv.getScrollY());
        assertEquals(mode == ReadingNavigation.Mode.BUTTONS ? View.VISIBLE : View.GONE,
            reader.findViewById(R.id.navigation_paging).getVisibility());
        assertEquals(mode, ReadingNavigation.get(context));
      }
    }
  }

  @Test public void prayerOptionsAndFontCssStillReloadAndPreserveThePrayerAndPosition() {
    for (Runnable change : new Runnable[]{
        () -> BreviarApp.setUrlOptions(context, "&amp;o0=1&amp;k=&amp;c=1&amp;o3=7"),
        () -> BreviarApp.setFont(context, "CustomFont", "@font-face { font-family: CustomFont; }"),
        () -> BreviarApp.setFontsCss(context, "@font-face { font-family: UpdatedFont; }")}) {
      try (ActivityController<EinkModeTest.Reader> controller =
          Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
        Breviar reader = controller.get();
        RecordingWebView web = openPrayer(reader);
        int loads = web.pageLoads;
        reader.onNavigationItemSelected(R.id.settings);
        controller.pause().stop();
        change.run();
        UrlOptions saved = new UrlOptions(BreviarApp.getUrlOptions(context));
        controller.restart().start().resume();
        assertEquals(loads + 1, web.pageLoads);
        UrlOptions page = new UrlOptions(reader.wv.getUrl(), true);
        assertEquals("16", page.params.get("d"));
        assertEquals("1", page.params.get("p"));
        for (String key : saved.params.keySet()) assertEquals(saved.params.get(key), page.params.get(key));
        assertEquals(0.4f, reader.scroll_to, 0.001f);
        // The next visit must use the newly applied settings as its baseline.
        reader.onNavigationItemSelected(R.id.settings);
        controller.pause().stop().restart().start().resume();
        assertEquals(loads + 1, web.pageLoads);
        assertEquals(0.4f, reader.scroll_to, 0.001f);
      }
    }
  }

  @Test public void zoomOnlyChangeStillAppliesWithoutReloadingThePage() {
    try (ActivityController<EinkModeTest.Reader> controller =
        Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
      Breviar reader = controller.get();
      RecordingWebView web = openPrayer(reader);
      int loads = web.pageLoads;
      reader.onNavigationItemSelected(R.id.settings);
      controller.pause().stop();
      context.getSharedPreferences(Util.prefname, 0).edit().putInt("scale", 150).commit();
      controller.restart().start().resume();
      assertEquals(150, reader.scale);
      assertEquals(loads, web.pageLoads);
    }
  }
}

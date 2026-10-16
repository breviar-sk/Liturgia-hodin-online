package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.view.MenuItem;
import android.view.View;
import android.webkit.WebView;
import android.widget.ListView;
import android.widget.TextView;
import androidx.appcompat.app.AlertDialog;
import org.json.JSONObject;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.Shadows;
import org.robolectric.android.controller.ActivityController;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.LooperMode;
import org.robolectric.shadows.ShadowDialog;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = 35, shadows = XmlSettingsActivityTest.SettingsServer.class)
@LooperMode(LooperMode.Mode.PAUSED)
public class ReadingNavigationTest {
  private final Context context = RuntimeEnvironment.getApplication();

  @Test
  public void migratesStandardScrollingWithoutCouplingItToLaterAppearanceChanges() {
    assertEquals(ReadingNavigation.Mode.SCROLL, ReadingNavigation.get(context));
    BreviarApp.setEinkMode(context, true);
    assertEquals(ReadingNavigation.Mode.SCROLL, ReadingNavigation.get(context));
  }

  @Test
  public void migratesEinkButtonsAndKeepsThemAfterAppearanceChange() {
    BreviarApp.setEinkMode(context, true);
    assertEquals(ReadingNavigation.Mode.BUTTONS, ReadingNavigation.get(context));
    BreviarApp.setEinkMode(context, false);
    assertEquals(ReadingNavigation.Mode.BUTTONS, ReadingNavigation.get(context));
  }

  @Test
  public void legacyArrowFlagRemainsAuthoritativeWithoutShowingBothControls() {
    BreviarApp.setEinkMode(context, true);
    BreviarApp.setUrlOptions(context, "&amp;o0=1024");
    assertEquals(ReadingNavigation.Mode.ARROWS, ReadingNavigation.get(context));
    ReadingNavigation.set(context, ReadingNavigation.Mode.BUTTONS);
    assertEquals(ReadingNavigation.Mode.BUTTONS, ReadingNavigation.get(context));
    // An older URL/web form can still enable arrows; it must hide the bottom row.
    assertEquals(ReadingNavigation.Mode.ARROWS,
        ReadingNavigation.get(context, new UrlOptions("&amp;o0=1024")));
    assertEquals(ReadingNavigation.Mode.BUTTONS,
        ReadingNavigation.get(context, new UrlOptions("&amp;o0=0")));
  }

  @Test
  public void selectionPreservesOtherFlagsAndOverridesAndSurvivesStaleReaderUrls() {
    int original = 64 | (1 << 18) | (1 << 20);
    BreviarApp.setUrlOptions(context, "&amp;o0=" + original + "&amp;of0tn=0&amp;of0r=1&amp;c=1&amp;f=Georgia");
    for (ReadingNavigation.Mode mode : ReadingNavigation.Mode.values()) {
      ReadingNavigation.set(context, mode);
      UrlOptions saved = new UrlOptions(BreviarApp.getUrlOptions(context));
      assertEquals(mode, ReadingNavigation.get(context));
      assertEquals(original | (mode == ReadingNavigation.Mode.ARROWS ? 1024 : 0), saved.getInt("o0"));
      assertFalse(saved.params.containsKey("of0tn"));
      assertEquals("1", saved.params.get("of0r"));
      assertEquals("Georgia", saved.getFont());
      assertTrue(saved.isNightmode());
      UrlOptions stale = new UrlOptions("&amp;o0=1024&amp;of0tn=1&amp;d=14&amp;p=1");
      SettingsXml.applySavedOptions(stale.params, saved.params);
      assertEquals(mode == ReadingNavigation.Mode.ARROWS, stale.isTransparentNav());
      assertEquals("14", stale.params.get("d"));
      assertEquals("1", stale.params.get("p"));
    }
  }

  @Test
  public void selectionBeforeFirstRenderKeepsUnspecifiedBackendDefaults() {
    ReadingNavigation.set(context, ReadingNavigation.Mode.ARROWS);
    UrlOptions options = new UrlOptions(BreviarApp.getUrlOptions(context));
    assertFalse(options.params.containsKey("o0"));
    assertEquals("1", options.params.get("of0tn"));
    assertEquals(ReadingNavigation.Mode.ARROWS, ReadingNavigation.get(context));
    ReadingNavigation.set(context, ReadingNavigation.Mode.SCROLL);
    assertEquals("0", new UrlOptions(BreviarApp.getUrlOptions(context)).params.get("of0tn"));
    assertEquals(ReadingNavigation.Mode.SCROLL, ReadingNavigation.get(context));
  }

  @Test
  public void displayChooserWorksInBothThemesAndKeepsArrowSuboptions() {
    for (boolean eink : new boolean[]{false, true}) {
      BreviarApp.setEinkMode(context, eink);
      BreviarApp.setUrlOptions(context, "&amp;o0=" + ((1 << 18) | (1 << 20)));
      try (ActivityController<DisplaySettings> controller = Robolectric.buildActivity(DisplaySettings.class).setup()) {
        DisplaySettings activity = controller.get();
        for (ReadingNavigation.Mode mode : ReadingNavigation.Mode.values()) {
          activity.navigationView.getMenu().performIdentifierAction(R.id.reading_navigation, 0);
          AlertDialog dialog = (AlertDialog)ShadowDialog.getLatestDialog();
          ListView list = dialog.getListView();
          assertEquals(5, list.getCount());
          TextView row = (TextView)list.getAdapter().getView(mode.ordinal(), null, list);
          if (eink) assertEquals(Color.BLACK, row.getCurrentTextColor());
          list.performItemClick(row, mode.ordinal(), mode.ordinal());
          assertFalse(dialog.isShowing());
          assertEquals(mode, ReadingNavigation.get(context));
          assertTrue(activity.navigationView.getMenu().findItem(R.id.reading_navigation)
              .getTitle().toString().contains(activity.getString(mode.label)));
          MenuItem left = activity.navigationView.getMenu().findItem(R.id.transparent_nav_left);
          assertEquals(mode == ReadingNavigation.Mode.ARROWS, left.isEnabled());
          assertEquals(left.isEnabled(), left.getActionView().isEnabled());
          UrlOptions options = new UrlOptions(BreviarApp.getUrlOptions(context));
          assertTrue(options.isTransparentNavLeft());
          assertTrue(options.isTransparentNavDownOnly());
        }
      }
    }
  }

  @Test
  public void returningFromSettingsUpdatesReaderControlsAndPrayerUrlInEitherTheme() throws Exception {
    BreviarApp.setString(context, "version", context.getString(R.string.version));
    for (boolean eink : new boolean[]{false, true}) {
      BreviarApp.setEinkMode(context, eink);
      ReadingNavigation.set(context, ReadingNavigation.Mode.SCROLL);
      try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
        EinkModeTest.Reader reader = controller.get();
        reader.wv.loadUrl("http://127.0.0.1:50000/l.cgi?qt=pdt&d=14&m=10&r=2026&p=1&of0tn=1");
        for (ReadingNavigation.Mode mode : ReadingNavigation.Mode.values()) {
          controller.pause().stop();
          ReadingNavigation.set(context, mode);
          reader.need_to_reload_preferences = true;
          reader.scroll_to = 0.4f;
          controller.restart().start().resume();
          assertEquals(mode == ReadingNavigation.Mode.BUTTONS ? View.VISIBLE : View.GONE,
              reader.findViewById(R.id.navigation_paging).getVisibility());
          UrlOptions page = new UrlOptions(reader.wv.getUrl(), true);
          assertEquals(mode == ReadingNavigation.Mode.ARROWS, page.isTransparentNav());
          assertEquals("14", page.params.get("d"));
          assertEquals("1", page.params.get("p"));
          assertEquals(0.4f, reader.scroll_to, 0.001f);
          reader.tapNavigation.pageStarted(reader.wv.getUrl());
          JSONObject taps = new JSONObject(reader.tapNavigation.settings());
          assertEquals(mode.isTapNavigation(), taps.getBoolean("enabled"));
          assertEquals(mode == ReadingNavigation.Mode.TAPS_HORIZONTAL, taps.getBoolean("horizontal"));
        }
        // A later web settings change is reflected when the new page finishes.
        Breviar.S.setOpts("&amp;o0=1024");
        Shadows.shadowOf(reader.wv).getWebViewClient().onPageFinished(reader.wv, reader.wv.getUrl());
        assertEquals(View.GONE, reader.findViewById(R.id.navigation_paging).getVisibility());
      }
    }
  }

  @Test
  public void savedTopBottomChoiceIsRetainedAndHorizontalChoiceSurvivesAppearanceChanges() {
    BreviarApp.setString(context, "reading_navigation", "taps");
    assertEquals(ReadingNavigation.Mode.TAPS, ReadingNavigation.get(context));
    ReadingNavigation.set(context, ReadingNavigation.Mode.TAPS_HORIZONTAL);
    BreviarApp.setEinkMode(context, true);
    assertEquals(ReadingNavigation.Mode.TAPS_HORIZONTAL, ReadingNavigation.get(context));
    BreviarApp.setEinkMode(context, false);
    assertEquals(ReadingNavigation.Mode.TAPS_HORIZONTAL, ReadingNavigation.get(context));
    assertEquals(ReadingNavigation.Mode.ARROWS,
        ReadingNavigation.get(context, new UrlOptions("&amp;o0=1024")));
    assertEquals(ReadingNavigation.Mode.TAPS_HORIZONTAL,
        ReadingNavigation.get(context, new UrlOptions("&amp;o0=0")));
  }

  @Test
  public void htmlDialogsFollowBothTapModesAfterReturningFromSettings() throws Exception {
    Intent help = new Intent().putExtra("content", "<html><body>Help</body></html>");
    for (boolean eink : new boolean[]{false, true}) {
      BreviarApp.setEinkMode(context, eink);
      ReadingNavigation.set(context, ReadingNavigation.Mode.SCROLL);
      try (ActivityController<DialogActivity> controller = Robolectric.buildActivity(DialogActivity.class, help).setup()) {
        DialogActivity dialog = controller.get();
        dialog.tapNavigation.pageStarted("data:text/html,help");
        for (ReadingNavigation.Mode mode : new ReadingNavigation.Mode[]{
            ReadingNavigation.Mode.TAPS_HORIZONTAL, ReadingNavigation.Mode.TAPS}) {
          controller.pause().stop();
          ReadingNavigation.set(context, mode);
          controller.restart().start().resume();
          JSONObject taps = new JSONObject(dialog.tapNavigation.settings());
          assertTrue(taps.getBoolean("enabled"));
          assertEquals(mode == ReadingNavigation.Mode.TAPS_HORIZONTAL, taps.getBoolean("horizontal"));
          assertFalse(taps.getBoolean("fullscreen"));
          assertEquals(View.GONE, dialog.findViewById(R.id.navigation_paging).getVisibility());
        }
      }
    }
  }

  private static class PagingView extends WebView {
    int turns;
    PagingView(Context context) { super(context); }
    @Override public boolean pageDown(boolean bottom) { ++turns; return true; }
    @Override public boolean pageUp(boolean top) { --turns; return true; }
  }

  @Test
  public void bottomButtonsPageInStandardModeAndHtmlDialogsFollowTheSelection() {
    BreviarApp.setString(context, "version", context.getString(R.string.version));
    ReadingNavigation.set(context, ReadingNavigation.Mode.BUTTONS);
    try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
      EinkModeTest.Reader reader = controller.get();
      WebView original = reader.wv;
      PagingView paging = new PagingView(reader);
      reader.wv = paging;
      reader.findViewById(R.id.navigation_page_down).performClick();
      assertEquals(1, paging.turns);
      reader.findViewById(R.id.navigation_page_up).performClick();
      assertEquals(0, paging.turns);
      reader.wv = original;
      paging.destroy();
    }
    Intent help = new Intent().putExtra("content", "<html><body>Help</body></html>");
    try (ActivityController<DialogActivity> controller = Robolectric.buildActivity(DialogActivity.class, help).setup()) {
      assertEquals(View.VISIBLE, controller.get().findViewById(R.id.navigation_paging).getVisibility());
      controller.pause().stop();
      ReadingNavigation.set(context, ReadingNavigation.Mode.SCROLL);
      controller.restart().start().resume();
      assertEquals(View.GONE, controller.get().findViewById(R.id.navigation_paging).getVisibility());
      // Installing a client for tap lifecycle tracking must preserve help links.
      assertTrue(Shadows.shadowOf(controller.get().wv).getWebViewClient().shouldOverrideUrlLoading(
          controller.get().wv, "https://example.com/help"));
      Intent opened = Shadows.shadowOf(controller.get()).getNextStartedActivity();
      assertEquals(Intent.ACTION_VIEW, opened.getAction());
      assertEquals("https://example.com/help", opened.getDataString());
    }
  }
}

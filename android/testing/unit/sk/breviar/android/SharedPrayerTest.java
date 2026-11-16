package sk.breviar.android;

import static org.junit.Assert.*;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Looper;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CompoundButton;
import androidx.recyclerview.widget.RecyclerView;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.Shadows;
import org.robolectric.android.controller.ActivityController;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.LooperMode;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = {24, 35}, shadows = XmlSettingsActivityTest.SettingsServer.class)
@LooperMode(LooperMode.Mode.PAUSED)
public class SharedPrayerTest {
  private final Context context = RuntimeEnvironment.getApplication();
  private static final String MINE = "&amp;j=sk&amp;k=sj&amp;o0=1088&amp;o1=31&amp;o2=288&amp;o3=28&amp;f=Custom&amp;c=1";
  private static final String LINK = "https://breviar.sk/cgi-bin/l.cgi?qt=pdt&d=12&m=11&r=2026&p=mv&j=la&k=op&o0=1&o1=7&o2=0&o3=6&o6=11000000000";

  @Before public void configure() {
    BreviarApp.setString(context, "version", context.getString(R.string.version));
    BreviarApp.setEinkMode(context, false);
    BreviarApp.setString(context, "language", "sk");
    BreviarApp.setUrlOptions(context, MINE);
    BreviarApp.markSharedAppearanceOffered(context);
  }

  private Intent link(String url) { return new Intent(Intent.ACTION_VIEW, Uri.parse(url)); }

  private void assertActions(Breviar reader, boolean visible) {
    assertEquals(visible, reader.navigationView.getMenu().findItem(R.id.restore_shared_settings).isVisible());
    assertEquals(visible, reader.navigationView.getMenu().findItem(R.id.keep_shared_settings).isVisible());
  }

  private static RecyclerView menuList(View view) {
    if (view instanceof RecyclerView) return (RecyclerView)view;
    if (view instanceof ViewGroup) {
      ViewGroup group = (ViewGroup)view;
      for (int i = 0; i < group.getChildCount(); ++i) {
        RecyclerView found = menuList(group.getChildAt(i));
        if (found != null) return found;
      }
    }
    return null;
  }

  @SuppressWarnings({"rawtypes", "unchecked"})
  private List<Integer> drawerRows(Breviar reader, int click) {
    RecyclerView list = menuList(reader.navigationView);
    RecyclerView.Adapter adapter = list.getAdapter();
    List<Integer> rows = new ArrayList<>();
    // Position zero reuses the header already attached to the NavigationView.
    rows.add(0);
    View selected = null;
    for (int i = 1; i < adapter.getItemCount(); ++i) {
      RecyclerView.ViewHolder holder = adapter.createViewHolder(list, adapter.getItemViewType(i));
      adapter.bindViewHolder(holder, i);
      MenuItem item = reader.navigationView.getMenu().findItem(holder.itemView.getId());
      if (item != null) {
        assertTrue("A hidden item still occupies a drawer row: " + item.getTitle(), item.isVisible());
        rows.add(item.getItemId());
        if (item.getItemId() == click) selected = holder.itemView;
      } else rows.add(0); // Header or horizontal separator.
    }
    if (click != 0) {
      assertNotNull(selected);
      // Exercise NavigationMenuPresenter's actual click dispatch, which suspends
      // its adapter while calling the app's selection listener.
      assertTrue(selected.performClick());
      Shadows.shadowOf(Looper.getMainLooper()).idle();
    }
    return rows;
  }

  @Test public void sharingActionsStayTogetherAndDisappearWithoutEmptyRowsAfterClick() {
    for (boolean eink : new boolean[]{false, true}) {
      for (int action : new int[]{R.id.restore_shared_settings, R.id.keep_shared_settings}) {
        configure();
        BreviarApp.setEinkMode(context, eink);
        try (ActivityController<EinkModeTest.Reader> screen = Robolectric.buildActivity(EinkModeTest.Reader.class).setup().visible()) {
          Breviar reader = screen.get();
          List<Integer> original = drawerRows(reader, 0);
          assertTrue(reader.handleIntent(link(LINK)));
          List<Integer> sharing = drawerRows(reader, 0);
          int share = sharing.indexOf(R.id.share_prayer);
          assertEquals(share + 1, sharing.indexOf(R.id.restore_shared_settings));
          assertEquals(share + 2, sharing.indexOf(R.id.keep_shared_settings));
          drawerRows(reader, action);
          assertActions(reader, false);
          assertEquals(original, drawerRows(reader, 0));
        }
      }
    }
  }

  @Test public void deviceSwitchDefaultsOffAndPersistsInBothAppearances() {
    assertFalse(BreviarApp.getSharedAppearance(context));
    for (boolean eink : new boolean[]{false, true}) {
      BreviarApp.setEinkMode(context, eink);
      BreviarApp.setSharedAppearance(context, false);
      try (ActivityController<DeviceSettings> controller = Robolectric.buildActivity(DeviceSettings.class).setup()) {
        DeviceSettings activity = controller.get();
        XmlSettingsActivityTest.awaitSettings(activity);
        CompoundButton toggle = (CompoundButton)activity.menuItem("device.shared-appearance").getActionView();
        assertFalse(toggle.isChecked());
        toggle.performClick();
        assertTrue(BreviarApp.getSharedAppearance(context));
        controller.recreate();
        activity = controller.get();
        XmlSettingsActivityTest.awaitSettings(activity);
        toggle = (CompoundButton)activity.menuItem("device.shared-appearance").getActionView();
        assertTrue(toggle.isChecked());
        toggle.performClick();
        assertFalse(BreviarApp.getSharedAppearance(context));
        assertEquals(MINE, BreviarApp.getUrlOptions(context));
      }
    }
  }

  @Test public void warmLinkAndRepeatedLinksRestoreTheOriginalPrayerAndSettings() {
    try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
      Breviar reader = controller.get();
      assertActions(reader, false);
      reader.wv.loadUrl("http://127.0.0.1:50000/l.cgi?qt=pdt&d=13&m=11&r=2026&p=mr");
      assertTrue(reader.handleIntent(link(LINK)));
      assertActions(reader, true);
      assertEquals("la", reader.language);
      UrlOptions applied = new UrlOptions(reader.wv.getUrl(), true);
      assertEquals("pdt", applied.params.get("qt"));
      assertEquals("12", applied.params.get("d"));
      assertEquals("mv", applied.params.get("p"));
      assertEquals(1089, applied.getInt("o0"));
      assertEquals(288, applied.getInt("o2"));
      assertEquals("Custom", applied.getFont());
      assertTrue(applied.isNightmode());
      assertTrue(reader.handleIntent(link(LINK.replace("j=la", "j=hu").replace("p=mv", "p=mr"))));
      // Native device changes made in the meantime must survive restoration.
      BreviarApp.setEinkMode(context, true);
      reader.restoreSharedSettings();
      assertActions(reader, false);
      assertFalse(SharedPrayerSession.active(context));
      assertEquals("sk", reader.language);
      UrlOptions restored = new UrlOptions(Breviar.S.getOpts());
      assertEquals("sj", restored.params.get("k"));
      assertEquals("31", restored.params.get("o1"));
      assertEquals("28", restored.params.get("o3"));
      assertFalse(restored.params.containsKey("o6"));
      assertTrue(reader.wv.getUrl().contains("d=13"));
      assertTrue(reader.wv.getUrl().contains("p=mr"));
      assertTrue(BreviarApp.getEinkMode(context));
    }
  }

  @Test public void coldLinkSurvivesRecreationWithoutReplayingTheIntentAndCanBeKept() {
    try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class, link(LINK)).setup()) {
      Breviar reader = controller.get();
      assertActions(reader, true);
      assertEquals("la", reader.language);
      String edited = "&amp;j=la&amp;k=op&amp;o1=99&amp;f=Other&amp;c=1";
      Breviar.S.setOpts(edited);
      reader.syncPreferences();
      controller.recreate();
      reader = controller.get();
      assertActions(reader, true);
      assertEquals("99", new UrlOptions(Breviar.S.getOpts()).params.get("o1"));
      reader.keepSharedSettings();
      assertActions(reader, false);
      assertFalse(SharedPrayerSession.active(context));
      assertEquals("99", new UrlOptions(BreviarApp.getUrlOptions(context)).params.get("o1"));
    }
    try (ActivityController<EinkModeTest.Reader> restarted = Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
      assertActions(restarted.get(), false);
      assertEquals("la", restarted.get().language);
      assertEquals("99", new UrlOptions(Breviar.S.getOpts()).params.get("o1"));
    }
  }

  @Test public void durableBackupSurvivesReaderDestructionAndDeviceFontChanges() {
    try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class, link(LINK)).setup()) {
      Breviar.S.setOpts(PrayerLink.applySettings(MINE, new UrlOptions(LINK, true).build(true)));
      controller.get().syncPreferences();
    }
    BreviarApp.setFont(context, "NewDeviceFont", "custom-css");
    try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
      assertActions(controller.get(), true);
      controller.get().restoreSharedSettings();
      assertActions(controller.get(), false);
      assertEquals("sk", controller.get().language);
      assertEquals("31", new UrlOptions(Breviar.S.getOpts()).params.get("o1"));
      assertEquals("NewDeviceFont", new UrlOptions(Breviar.S.getOpts()).getFont());
      assertEquals("custom-css", BreviarApp.getFontsCss(context));
      assertEquals("pdnes", new UrlOptions(controller.get().wv.getUrl(), true).params.get("qt"));
    }
  }

  @Test public void invalidIntentDoesNotChangeSettingsOrStartASession() {
    try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
      assertFalse(controller.get().handleIntent(link(LINK.replace("breviar.sk", "evil.example"))));
      assertFalse(SharedPrayerSession.active(context));
      assertActions(controller.get(), false);
      assertEquals(MINE, BreviarApp.getUrlOptions(context));
    }
  }

  @Test public void prayerLanguageUiOverrideRecreatesAndStillAllowsRestoration() {
    BreviarApp.setOverrideLocale(context, true);
    try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
      controller.newIntent(link(LINK));
      Shadows.shadowOf(Looper.getMainLooper()).idle();
      Breviar reader = controller.get();
      assertEquals("la", reader.language);
      assertEquals("la", reader.getResources().getConfiguration().getLocales().get(0).getLanguage());
      assertActions(reader, true);
      reader.restoreSharedSettings();
      Shadows.shadowOf(Looper.getMainLooper()).idle();
      reader = controller.get();
      assertEquals("sk", reader.language);
      assertEquals("sk", reader.getResources().getConfiguration().getLocales().get(0).getLanguage());
      assertActions(reader, false);
    }
  }

  @Test public void appearanceIsOptInAndRestoresEvenAfterSwitchingBackToContentOnly() {
    assertFalse(BreviarApp.getSharedAppearance(context));
    BreviarApp.setFontsCss(context, "original-font-css");
    String visual = LINK + "&c=0&f=serif&ct1=ffffcc&cr1=112233&ff=18&mm=21&lh=150&of0fn=0";
    try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
      Breviar reader = controller.get();
      assertTrue(reader.handleIntent(link(visual)));
      UrlOptions content = new UrlOptions(reader.wv.getUrl(), true);
      assertTrue(content.isNightmode());
      assertTrue(content.isOnlyNonBoldFont());
      assertEquals("Custom", content.getFont());
      for (String key : new String[]{"ct1", "cr1", "ff", "mm", "lh", "of0fn"}) {
        assertTrue(key, content.params.getOrDefault(key, "").isEmpty());
      }

      BreviarApp.setSharedAppearance(context, true);
      assertTrue(reader.handleIntent(link(visual)));
      UrlOptions full = new UrlOptions(reader.wv.getUrl(), true);
      assertFalse(full.isNightmode());
      assertEquals("1", full.params.get("o0"));
      assertEquals("0", full.params.get("of0fn"));
      assertEquals("serif", full.getFont());
      assertEquals("ffffcc", full.params.get("ct1"));
      assertEquals("112233", full.params.get("cr1"));
      assertEquals("18", full.params.get("ff"));
      assertEquals("21", full.params.get("mm"));
      assertEquals("150", full.params.get("lh"));
      assertEquals("", BreviarApp.getFontsCss(context));

      BreviarApp.setSharedAppearance(context, false);
      assertTrue(reader.handleIntent(link(LINK + "&c=1&f=Other&ct1=bad-color")));
      controller.recreate();
      reader = controller.get();
      reader.restoreSharedSettings();
      UrlOptions restored = new UrlOptions(BreviarApp.getUrlOptions(context));
      assertTrue(restored.isNightmode());
      assertEquals("Custom", restored.getFont());
      assertEquals("31", restored.params.get("o1"));
      for (String key : new String[]{"ct1", "cr1", "ff", "mm", "lh", "of0fn"}) {
        assertTrue(key, restored.params.getOrDefault(key, "").isEmpty());
      }
      assertEquals("original-font-css", BreviarApp.getFontsCss(context));
      assertFalse(BreviarApp.getSharedAppearance(context));
    }
  }

  @Test public void keptAppearanceSurvivesRecreationAndDoesNotChangeDeviceSettingsOrZoom() {
    BreviarApp.setSharedAppearance(context, true);
    BreviarApp.setNoZoom(context, true);
    BreviarApp.setBoolean(context, "dim_lock", false);
    context.getSharedPreferences(Util.prefname, 0).edit().putInt("scale", 150).commit();
    try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class,
        link(LINK + "&c=0&f=sans-serif&ct0=112233&ff=20&eink_mode=true&scale=500&shared_appearance=false")).setup()) {
      Breviar reader = controller.get();
      controller.recreate();
      reader = controller.get();
      reader.keepSharedSettings();
      assertFalse(SharedPrayerSession.active(context));
      UrlOptions kept = new UrlOptions(BreviarApp.getUrlOptions(context));
      assertEquals("sans-serif", kept.getFont());
      assertEquals("112233", kept.params.get("ct0"));
      assertFalse(kept.isNightmode());
      assertTrue(BreviarApp.getSharedAppearance(context));
      assertTrue(BreviarApp.getNoZoom(context));
      assertFalse(BreviarApp.getDimLock(context));
      assertFalse(BreviarApp.getEinkMode(context));
      assertEquals(150, reader.scale);
    }
  }

  @Test @Config(shadows = {XmlSettingsActivityTest.SettingsServer.class, SharedPrayerImportTest.FontResolver.class})
  public void resolvedFontCssIsAppliedAndRestoredTogetherWithTheFontName() throws Exception {
    BreviarApp.setSharedAppearance(context, true);
    BreviarApp.setFontsCss(context, "original-font-css");
    try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
      Breviar reader = controller.get();
      assertTrue(reader.handleIntent(link(LINK + "&f=Test%20Font")));
      SharedPrayerImportTest.drain();
      assertEquals("Test Font", new UrlOptions(reader.wv.getUrl(), true).getFont());
      assertEquals("local-font-css", BreviarApp.getFontsCss(context));
      assertTrue(reader.handleIntent(link(LINK + "&f=Missing&cr1=ffffcc")));
      SharedPrayerImportTest.drain();
      assertEquals("Test Font", new UrlOptions(reader.wv.getUrl(), true).getFont());
      assertEquals("local-font-css", BreviarApp.getFontsCss(context));
      reader.restoreSharedSettings();
      assertEquals("Custom", new UrlOptions(BreviarApp.getUrlOptions(context)).getFont());
      assertEquals("original-font-css", BreviarApp.getFontsCss(context));
    }
  }

  @Test @Config(shadows = {XmlSettingsActivityTest.SettingsServer.class, SharedPrayerImportTest.FontResolver.class})
  public void recreatingWhileAFontIsLoadingResumesTheIncomingPrayer() throws Exception {
    BreviarApp.setSharedAppearance(context, true);
    SharedPrayerImportTest.FontResolver.entered = new CountDownLatch(1);
    SharedPrayerImportTest.FontResolver.release = new CountDownLatch(1);
    try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class,
        link(LINK + "&f=Test%20Font&c=0")).setup()) {
      assertTrue(SharedPrayerImportTest.FontResolver.entered.await(5, TimeUnit.SECONDS));
      controller.recreate();
      SharedPrayerImportTest.FontResolver.release.countDown();
      SharedPrayerImportTest.drain();
      Breviar reader = controller.get();
      assertActions(reader, true);
      UrlOptions page = new UrlOptions(reader.wv.getUrl(), true);
      assertEquals("12", page.params.get("d"));
      assertEquals("mv", page.params.get("p"));
      assertEquals("Test Font", page.getFont());
      assertFalse(page.isNightmode());
      reader.restoreSharedSettings();
      assertEquals("Custom", new UrlOptions(BreviarApp.getUrlOptions(context)).getFont());
    } finally {
      SharedPrayerImportTest.FontResolver.release.countDown();
      SharedPrayerImportTest.drain();
    }
  }
}

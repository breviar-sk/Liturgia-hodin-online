package sk.breviar.android;

import static org.junit.Assert.*;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Looper;
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
  }

  private Intent link(String url) { return new Intent(Intent.ACTION_VIEW, Uri.parse(url)); }

  private void assertActions(Breviar reader, boolean visible) {
    assertEquals(visible, reader.navigationView.getMenu().findItem(R.id.restore_shared_settings).isVisible());
    assertEquals(visible, reader.navigationView.getMenu().findItem(R.id.keep_shared_settings).isVisible());
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
}

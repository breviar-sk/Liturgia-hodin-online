package sk.breviar.android;

import static org.junit.Assert.*;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.os.Looper;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.CompoundButton;
import com.google.android.material.navigation.NavigationView;
import java.util.Locale;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
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
import org.robolectric.annotation.Implementation;
import org.robolectric.annotation.Implements;
import org.robolectric.annotation.LooperMode;
import org.robolectric.util.ReflectionHelpers;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = {24, 35}, shadows = LangSelectTest.LanguageServer.class)
@LooperMode(LooperMode.Mode.PAUSED)
public class LangSelectTest {
  private static final String XML = withLanguages("<SupportedLanguages Name='j'>"
      + "<Language Id='5' Value='c2' Locale='cs'>different XML label</Language>"
      + "<Language Id='91' Value='custom' Locale='pt-BR'>português</Language>"
      + "</SupportedLanguages>");
  private static String withLanguages(String languages) {
    return XmlSettingsActivityTest.settingsXml(true).replaceAll(
        "<SupportedLanguages.*?</SupportedLanguages>", languages);
  }

  private final Context context = RuntimeEnvironment.getApplication();

  @Implements(value = Server.class, isInAndroidSdk = false)
  public static class LanguageServer {
    static volatile String xml;
    static volatile String options, language;
    static volatile CountDownLatch entered, release;
    @Implementation protected static void __staticInitializer__() {}
    @Implementation protected static String getSettingsXml(Context context, String opts, String lang)
        throws InterruptedException {
      assertNotSame("XML must not render on the UI thread", Looper.getMainLooper().getThread(),
          Thread.currentThread());
      options = opts;
      language = lang;
      if (entered != null) {
        entered.countDown();
        assertTrue("Timed out waiting to finish XML rendering", release.await(10, TimeUnit.SECONDS));
      }
      return xml;
    }
  }

  @Before public void reset() {
    LanguageServer.xml = XML;
    LanguageServer.entered = LanguageServer.release = null;
    context.getSharedPreferences(Util.prefname, 0).edit().clear().commit();
    context.getSharedPreferences("language_locales", 0).edit().clear().commit();
  }

  static void awaitLanguages(LangSelect activity) throws Exception {
    ExecutorService worker = ReflectionHelpers.getField(activity, "worker");
    worker.submit(() -> {}).get(10, TimeUnit.SECONDS);
    Shadows.shadowOf(Looper.getMainLooper()).idle();
  }

  @Test public void xmlControlsEntriesAndSelectionUsesRendererCode() throws Exception {
    BreviarApp.setString(context, "language", "c2");
    BreviarApp.setUrlOptions(context, "&amp;o0=123&amp;c=some-calendar");
    try (ActivityController<LangSelect> controller = Robolectric.buildActivity(LangSelect.class).setup()) {
      LangSelect activity = controller.get();
      awaitLanguages(activity);
      Menu menu = activity.navigationView.getMenu();
      assertEquals(3, menu.size()); // Exactly the XML entries plus the Android locale switch.
      assertEquals(activity.getString(R.string.lang_c2), menu.getItem(0).getTitle());
      assertEquals("Português", menu.getItem(1).getTitle());
      assertSame(activity.menuItem("language.use-for-interface"), menu.getItem(2));
      assertTrue(menu.getItem(0).isChecked());
      assertFalse(menu.getItem(1).isChecked());
      assertEquals("c2", LanguageServer.language);
      assertEquals(BreviarApp.getUrlOptions(context), LanguageServer.options);
      menu.performIdentifierAction(menu.getItem(1).getItemId(), 0);
      assertEquals(Activity.RESULT_OK, Shadows.shadowOf(activity).getResultCode());
      assertEquals("custom", Shadows.shadowOf(activity).getResultIntent().getStringExtra("lang"));
      assertTrue(activity.isFinishing());
      assertFalse(menu.getItem(0).isChecked());
      assertTrue(menu.getItem(1).isChecked());
      assertEquals("pt-BR", BreviarApp.appLanguageToLocale(context, "custom").toLanguageTag());
      // The reader still owns the selected language and calendar reset on return.
      assertEquals("c2", BreviarApp.getString(context, "language", ""));
      assertEquals("&amp;o0=123&amp;c=some-calendar", BreviarApp.getUrlOptions(context));
    }
  }

  @Test public void upgradeKeepsExistingLanguagesBeforeAnyXmlLoad() {
    SharedPreferences preferences = context.getSharedPreferences(Util.prefname, 0);
    for (String code : new String[]{"sk", "cz", "c2", "hu", "la", "is"}) {
      preferences.edit().putString("language", code).putBoolean("override_locale", true)
          .putString("params", "&amp;o0=123").commit();
      String expected = code.equals("cz") || code.equals("c2") ? "cs" : code;
      assertEquals(expected, BreviarApp.currentLocale(context).getLanguage());
      assertEquals(expected, BreviarApp.appLanguageToLocale(context, code).getLanguage());
      // Context attachment happens before any language-menu worker can run.
      try (ActivityController<SettingsActivity> controller =
          Robolectric.buildActivity(SettingsActivity.class).create()) {
        assertEquals(expected, controller.get().getResources().getConfiguration().locale.getLanguage());
      }
      assertEquals(code, preferences.getString("language", ""));
      assertEquals("&amp;o0=123", BreviarApp.getUrlOptions(context));
      assertTrue(context.getSharedPreferences("language_locales", 0).getAll().isEmpty());
    }
  }

  @Test public void cachedLocaleWorksWithoutReopeningTheLanguageMenu() throws Exception {
    BreviarApp.cacheLanguageLocales(context, SettingsXml.parseLanguages(XML));
    BreviarApp.setString(context, "language", "custom");
    BreviarApp.setOverrideLocale(context, true);
    // A fresh context consumes persisted metadata, with no static catalog or renderer.
    Context fresh = context.createPackageContext(context.getPackageName(), 0);
    assertEquals("pt-BR", BreviarApp.currentLocale(fresh).toLanguageTag());
    assertEquals("pt-BR", BreviarApp.appLanguageToLocale(fresh, "custom").toLanguageTag());
    assertEquals("cs", BreviarApp.appLanguageToLocale(fresh, "c2").getLanguage());
    BreviarApp.setOverrideLocale(context, false);
    assertEquals(Locale.getDefault(), BreviarApp.currentLocale(fresh));
    assertEquals("pt-BR", BreviarApp.appLanguageToLocale(fresh, "custom").toLanguageTag());
  }

  @Test public void localeSwitchRetainsItsValueAfterLoading() throws Exception {
    BreviarApp.setString(context, "language", "c2");
    BreviarApp.setOverrideLocale(context, true);
    try (ActivityController<LangSelect> controller = Robolectric.buildActivity(LangSelect.class).setup()) {
      LangSelect activity = controller.get();
      awaitLanguages(activity);
      CompoundButton toggle = (CompoundButton)activity.menuItem("language.use-for-interface").getActionView();
      assertTrue(toggle.isChecked());
      assertEquals("cs", BreviarApp.currentLocale(context).getLanguage());
      toggle.performClick();
      assertFalse(BreviarApp.getOverrideLocale(context));
      assertEquals(Locale.getDefault(), BreviarApp.currentLocale(context));
    }
  }

  @Test public void failedLoadPreservesCacheAndOffersRetry() throws Exception {
    BreviarApp.cacheLanguageLocales(context, SettingsXml.parseLanguages(XML));
    LanguageServer.xml = "<LHData><SupportedLanguages/></LHData>";
    try (ActivityController<LangSelect> controller = Robolectric.buildActivity(LangSelect.class).setup()) {
      LangSelect activity = controller.get();
      awaitLanguages(activity);
      assertEquals("pt-BR", BreviarApp.appLanguageToLocale(context, "custom").toLanguageTag());
      MenuItem retry = activity.navigationView.getMenu().getItem(0);
      assertEquals(activity.getString(R.string.settings_load_failed), retry.getTitle());
      assertNull(activity.menuItem("language.use-for-interface"));
      LanguageServer.xml = XML;
      activity.navigationView.getMenu().performIdentifierAction(retry.getItemId(), 0);
      awaitLanguages(activity);
      assertEquals(3, activity.navigationView.getMenu().size());
      assertEquals("Português", activity.navigationView.getMenu().getItem(1).getTitle());
    }
  }

  @Test public void stoppedScreenIgnoresPendingResultsAndRefreshesOnReturn() throws Exception {
    LanguageServer.entered = new CountDownLatch(1);
    LanguageServer.release = new CountDownLatch(1);
    try (ActivityController<LangSelect> controller = Robolectric.buildActivity(LangSelect.class).setup()) {
      LangSelect activity = controller.get();
      NavigationView initial = activity.navigationView;
      assertTrue(LanguageServer.entered.await(10, TimeUnit.SECONDS));
      controller.pause().stop();
      LanguageServer.release.countDown();
      awaitLanguages(activity);
      assertSame(initial, activity.navigationView);
      assertTrue(context.getSharedPreferences("language_locales", 0).getAll().isEmpty());
      controller.restart().start().resume();
      awaitLanguages(activity);
      assertNotSame(initial, activity.navigationView);
      assertEquals(3, activity.navigationView.getMenu().size());
      NavigationView previous = activity.navigationView;
      controller.pause().stop();
      LanguageServer.xml = withLanguages("<SupportedLanguages>"
          + "<Language Value='la' Locale='la'>latin</Language></SupportedLanguages>");
      controller.restart().start().resume();
      awaitLanguages(activity);
      assertEquals(2, activity.navigationView.getMenu().size());
      assertEquals(3, previous.getMenu().size()); // Old accessibility rows remain valid.
    } finally {
      LanguageServer.release.countDown();
    }
  }
}

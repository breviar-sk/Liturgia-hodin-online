package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
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
import org.robolectric.annotation.RealObject;
import org.robolectric.util.ReflectionHelpers;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = {24, 35}, shadows = TtsHelpTest.HelpServer.class)
@LooperMode(LooperMode.Mode.PAUSED)
public class TtsHelpTest {
  private final Context context = RuntimeEnvironment.getApplication();

  @Implements(value = Server.class, isInAndroidSdk = false)
  public static class HelpServer {
    @RealObject Server server;
    static CountDownLatch stopped;
    @Implementation protected static void __staticInitializer__() {}
    @Implementation protected void __constructor__(Context context, String script, String language, String options) {
      server.ctx = context;
      server.port_nonpersistent = 49999;
    }
    @Implementation protected void run() {} // No JNI or sockets in these activity tests.
    @Implementation protected void stopServer() { stopped.countDown(); }
  }

  private Server server() {
    Server server = ReflectionHelpers.callConstructor(Server.class,
        ReflectionHelpers.ClassParameter.from(Context.class, context));
    server.port_nonpersistent = 49999;
    return server;
  }

  private Intent helpIntent() {
    return new Intent(context, DialogActivity.class)
        .putExtra("title", R.string.tts_settings_help_title)
        .putExtra("static_text", "qt=pst&st=i&p=2");
  }

  private Uri dialogUrl(int page) {
    Server previous = Breviar.S;
    Breviar.S = server();
    Intent intent = new Intent(context, DialogActivity.class)
        .putExtra("static_text", "qt=pst&st=i&p=" + page);
    try (ActivityController<DialogActivity> dialog = Robolectric.buildActivity(DialogActivity.class, intent).setup()) {
      Uri url = Uri.parse(Shadows.shadowOf(dialog.get().wv).getLastLoadedUrl());
      assertEquals(49999, url.getPort());
      assertEquals("pst", url.getQueryParameter("qt"));
      assertEquals("i", url.getQueryParameter("st"));
      assertEquals(Integer.toString(page), url.getQueryParameter("p"));
      assertEquals("", url.getQueryParameter("k"));
      return url;
    } finally {
      Breviar.S = previous;
    }
  }

  @Test public void aboutAndChangelogUseTheSameStaticTextPathAsHelp() {
    Breviar.S = null;
    Breviar reader = Robolectric.buildActivity(Breviar.class).get();
    reader.showAbout();
    Intent about = Shadows.shadowOf(reader).getNextStartedActivity();
    assertEquals("qt=pst&st=i&p=0", about.getStringExtra("static_text"));
    assertEquals(R.string.about_title, about.getIntExtra("title", -1));
    assertFalse(about.hasExtra("url"));
    assertFalse(about.getBooleanExtra("show_ok", true));

    reader.showChangelog(true);
    Intent changelog = Shadows.shadowOf(reader).getNextStartedActivity();
    assertEquals("qt=pst&st=i&p=1", changelog.getStringExtra("static_text"));
    assertEquals(R.string.news_title, changelog.getIntExtra("title", -1));
    assertFalse(changelog.hasExtra("url"));
    assertTrue(changelog.getBooleanExtra("show_ok", false));
  }

  @Test public void settingsActionOpensStyledPageWithLatestPreferences() throws Exception {
    Breviar.S = server();
    Breviar.S.setOpts("&amp;f=serif&amp;ff=12&amp;o2=0");
    String options = "&amp;f=Custom Font&amp;ff=26&amp;o2=256&amp;p=mpc&amp;k=czop&amp;j=la";
    BreviarApp.setUrlOptions(context, options);
    BreviarApp.setString(context, "language", "c2");
    BreviarApp.setOverrideLocale(context, true);
    try (ActivityController<XmlSettingsActivity> settings = Robolectric.buildActivity(
        XmlSettingsActivity.class, XmlSettingsActivity.entryIntent(context, "speech")).create()) {
      XmlSettingsActivity activity = settings.get();
      ReflectionHelpers.callInstanceMethod(activity, "showSettings", ReflectionHelpers.ClassParameter.from(
          SettingsXml.class, SettingsXml.parse(XmlSettingsActivityTest.settingsXml(true))));
      activity.navigationView.getMenu().performIdentifierAction(activity.menuItem("speech.help").getItemId(), 0);
      Intent intent = Shadows.shadowOf(activity).getNextStartedActivity();
      assertEquals("qt=pst&st=i&p=2", intent.getStringExtra("static_text"));
      assertFalse(intent.hasExtra("content"));
      try (ActivityController<DialogActivity> help = Robolectric.buildActivity(DialogActivity.class, intent).setup()) {
        Uri url = Uri.parse(Shadows.shadowOf(help.get().wv).getLastLoadedUrl());
        assertEquals(49999, url.getPort());
        assertEquals("/l.cgi", url.getPath());
        assertEquals("pst", url.getQueryParameter("qt"));
        assertEquals("i", url.getQueryParameter("st"));
        assertEquals("2", url.getQueryParameter("p"));
        assertEquals("c2", url.getQueryParameter("j"));
        assertEquals("", url.getQueryParameter("k"));
        assertEquals("Custom Font", url.getQueryParameter("f"));
        assertEquals("26", url.getQueryParameter("ff"));
        assertEquals("256", url.getQueryParameter("o2"));
        assertEquals(options, BreviarApp.getUrlOptions(context));
        assertEquals("&amp;f=serif&amp;ff=12&amp;o2=0", Breviar.S.getOpts());
      }
    } finally {
      Breviar.S = null;
    }
  }

  @Test public void restoredHelpOwnsAndClosesItsServer() throws Exception {
    Breviar.S = null;
    for (int page = 0; page < 3; page++) {
      HelpServer.stopped = new CountDownLatch(1);
      Intent intent = helpIntent().putExtra("static_text", "qt=pst&st=i&p=" + page);
      try (ActivityController<DialogActivity> help = Robolectric.buildActivity(DialogActivity.class, intent).setup()) {
        assertTrue(Shadows.shadowOf(help.get().wv).getLastLoadedUrl().startsWith("http://127.0.0.1:49999/l.cgi?"));
        assertNotNull(ReflectionHelpers.getField(help.get(), "ownedServer"));
        assertNull(Breviar.S);
      }
      assertTrue(HelpServer.stopped.await(5, TimeUnit.SECONDS));
    }
  }

  private String content(Server server, String path) throws Exception {
    assertEquals(1, server.checkfile(path));
    return content(server.openAsset(path));
  }

  private String content(InputStream stream) throws Exception {
    try (InputStream input = stream) {
      ByteArrayOutputStream result = new ByteArrayOutputStream();
      byte[] buffer = new byte[1024];
      int size;
      while ((size = input.read(buffer)) != -1) result.write(buffer, 0, size);
      return result.toString("UTF-8");
    }
  }

  @Test public void helpKeepsUiTranslationsWithoutOverridingReaderStyles() throws Exception {
    Server server = server();
    String[][] languages = {{"sk", "include", "Ako si nastaviť"},
        {"cz", "include_cz", "Jak nastavit"}, {"c2", "include_czop", "Jak nastavit"},
        {"hu", "include_hu", "A hangkimenet"}, {"is", "include_is", "Hvernig setja"},
        {"la", "include_la", "Præceptum"}, {"en", "include_en", "How to set up"}};
    for (String[] language : languages) {
      BreviarApp.setString(context, "language", language[0]);
      BreviarApp.setOverrideLocale(context, true);
      assertEquals(language[0], dialogUrl(2).getQueryParameter("j"));
      // The native renderer needs its static-text template in this language too.
      assertTrue(content(server, language[1] + "/m_text.htm").contains("<!--{TEXT}-->"));
      String html = content(server, language[1] + "/tts-android.htm");
      assertTrue(html.contains(language[2]));
      assertTrue(html.contains("<!--{BEGIN:INFO}-->"));
      assertTrue(html.contains("<!--{END:INFO}-->"));
      assertTrue(html.contains("bridge.openTTSSettings()"));
      assertTrue(html.contains("<button class=\"button\"")); // Inherit font and night colors too.
      assertFalse(html.contains("<style"));
      assertFalse(html.contains("<body"));
    }
  }

  @Test @Config(qualifiers = "fr")
  public void unsupportedUiLanguageFallsBackToEnglishRegardlessOfPrayerLanguage() throws Exception {
    BreviarApp.setString(context, "language", "sk");
    BreviarApp.setOverrideLocale(context, false);
    Server server = server();
    for (int page = 0; page < 3; page++) assertEquals("en", dialogUrl(page).getQueryParameter("j"));
    assertTrue(content(server, "include_en/tts-android.htm").contains("How to set up voice output"));
    assertTrue(content(server, "include_en/about.htm").contains("Breviary Application"));
    assertTrue(content(server, "include_en/version-android.htm").contains("Changelog"));
    // Server must load exactly the requested asset, independently of UI preferences.
    assertTrue(content(server, "include/tts-android.htm").contains("Ako si nastaviť"));
    for (String name : new String[]{"about.htm", "version-android.htm"}) {
      String html = content(server, "include_en/" + name);
      assertTrue(html.contains(context.getString(R.string.version)));
      assertFalse(html.contains("[VERSION]"));
      assertFalse(html.contains("[PROJECT-URL]"));
      assertFalse(html.contains("[E-MAIL]"));
      assertFalse(html.contains("[APP-NAME]"));
    }
  }

  @Test @Config(qualifiers = "cs")
  public void infoPagesRespectOverrideAndPreservePrayerVariants() throws Exception {
    Server server = server();
    BreviarApp.setUrlOptions(context, "&amp;k=czop&amp;j=c2&amp;f=serif&amp;ff=26");
    for (String[] prayer : new String[][]{{"la", "include_la"}, {"c2", "include_czop"}}) {
      BreviarApp.setString(context, "language", prayer[0]);
      for (boolean override : new boolean[]{false, true}) {
        BreviarApp.setOverrideLocale(context, override);
        String expectedDirectory = override ? prayer[1] : "include_cz";
        for (int page = 0; page < 3; page++) {
          Uri url = dialogUrl(page);
          assertEquals(override ? prayer[0] : "cz", url.getQueryParameter("j"));
          assertEquals("serif", url.getQueryParameter("f"));
          assertEquals("26", url.getQueryParameter("ff"));
        }
        for (String name : new String[]{"about.htm", "version-android.htm", "tts-android.htm"}) {
          assertEquals(content(context.getAssets().open(expectedDirectory + "/" + name)),
              content(server, expectedDirectory + "/" + name));
        }
        assertEquals("&amp;k=czop&amp;j=c2&amp;f=serif&amp;ff=26", BreviarApp.getUrlOptions(context));
      }
    }
  }

  @Test public void settingsAndExternalLinksStillUseTheDialogBridge() {
    try (ActivityController<DialogActivity> help = Robolectric.buildActivity(DialogActivity.class,
        new Intent().putExtra("content", "<html><body>Help</body></html>")).setup()) {
      DialogActivity activity = help.get();
      DialogActivity.Bridge bridge = activity.new Bridge(activity);
      bridge.openTTSSettings();
      assertEquals("com.android.settings.TTS_SETTINGS", Shadows.shadowOf(activity).getNextStartedActivity().getAction());
      String url = "https://play.google.com/store/apps/details?id=com.redzoc.ramees.tts.espeak";
      bridge.openIntent(url);
      Intent external = Shadows.shadowOf(activity).getNextStartedActivity();
      assertEquals(Intent.ACTION_VIEW, external.getAction());
      assertEquals(url, external.getDataString());
    }
  }
}

package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import java.io.ByteArrayOutputStream;
import java.io.OutputStream;
import java.net.Socket;
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
public class ReaderControlsTest {
  private final Context context = RuntimeEnvironment.getApplication();
  private static final String OPTIONS = "&amp;j=sk&amp;k=sj&amp;c=1&amp;o0=8835&amp;o1=1123143&amp;o2=29432&amp;o3=28"
      + "&amp;ct0=123456&amp;cr0=654321&amp;c0=ffffcc&amp;ct1=eeeeee&amp;cr1=ffaaaa&amp;c1=111111"
      + "&amp;f=Custom Font&amp;ff=22&amp;lh=150&amp;mm=12";

  @Before public void configure() {
    BreviarApp.setString(context, "version", context.getString(R.string.version));
    BreviarApp.setUrlOptions(context, OPTIONS);
  }

  private String response(Server server, Uri uri) throws Exception {
    ByteArrayOutputStream bytes = new ByteArrayOutputStream();
    Socket socket = new Socket() {
      @Override public OutputStream getOutputStream() { return bytes; }
    };
    server.handleFile(socket, uri.getEncodedPath().substring(1) + "?" + uri.getEncodedQuery(), true);
    return bytes.toString("UTF-8");
  }

  private void assertSettingsKept(UrlOptions actual) {
    UrlOptions original = new UrlOptions(OPTIONS);
    for (String key : original.params.keySet()) {
      if (!key.equals("c") && !key.equals("o0"))
        assertEquals(key, original.params.get(key), actual.params.get(key));
    }
  }

  @Test public void catechesisControlsKeepTheAssetPaletteAndSavedSettings() throws Exception {
    for (boolean eink : new boolean[]{false, true}) {
      BreviarApp.setEinkMode(context, eink);
      for (String page : new String[]{"include/kat-z51.htm", "katechezy.htm",
          "include/kat-z51.htm?refresh=1&c=0&ct0=badbad&of0fn=1#section"}) {
        BreviarApp.setUrlOptions(context, OPTIONS);
        try (ActivityController<EinkModeTest.Reader> screen = Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
          Breviar reader = screen.get();
          reader.wv.loadUrl("http://127.0.0.1:" + Breviar.S.port + "/" + page);
          // The fake reader does not run JNI: model the last completed render's
          // settings snapshot, without its page-selection fields.
          Breviar.S.setOpts(OPTIONS);
          Uri original = Uri.parse(reader.wv.getUrl());
          // Start in night mode, including when the old URL says otherwise.
          for (boolean night : new boolean[]{false, true}) {
            reader.toggleNightMode();
            Uri reloaded = Uri.parse(reader.wv.getUrl());
            assertEquals(original.getPath(), reloaded.getPath());
            assertEquals(original.getFragment(), reloaded.getFragment());
            assertEquals(original.getQueryParameter("refresh"), reloaded.getQueryParameter("refresh"));
            UrlOptions saved = new UrlOptions(Breviar.S.getOpts());
            assertEquals(night, saved.isNightmode());
            assertFalse(saved.isOnlyNonBoldFont());
            assertSettingsKept(saved);
            assertFalse(saved.params.containsKey("refresh"));
            assertNull(reloaded.getQueryParameter("of0fn"));
            String html = response(Breviar.S, reloaded);
            assertTrue(html.contains("Katechézy k žalmom a chválospevom"));
            assertEquals(night, html.contains("breviar-invert-colors.css"));
            assertTrue(html.contains("--prayer-text: #" + (night ? "eeeeee" : "123456")));
            assertTrue(html.contains("background-color: #" + (night ? "111111" : "ffffcc")));
            reader.syncPreferences();
            assertEquals(saved.params, new UrlOptions(BreviarApp.getUrlOptions(context)).params);
          }
          for (boolean onlyNonBold : new boolean[]{true, false}) {
            reader.toggleOnlyNonBoldFont();
            Uri reloaded = Uri.parse(reader.wv.getUrl());
            assertEquals(original.getPath(), reloaded.getPath());
            UrlOptions saved = new UrlOptions(Breviar.S.getOpts());
            assertEquals(onlyNonBold, saved.isOnlyNonBoldFont());
            assertSettingsKept(saved);
            assertEquals(onlyNonBold, response(Breviar.S, reloaded).contains("breviar-normal-font.css"));
          }
        }
      }
    }
  }

  @Test public void togglesRetainPrayerSelectionWhileReplacingStaleUrlSettings() {
    try (ActivityController<EinkModeTest.Reader> screen = Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
      Breviar reader = screen.get();
      reader.wv.loadUrl("http://127.0.0.1:" + Breviar.S.port + "/" + Breviar.scriptname
          + "?qt=pdt&d=12&m=11&r=2026&p=mpc&ds=1&c=0&ct0=badbad&of0fn=1");
      Breviar.S.setOpts(OPTIONS);
      reader.toggleNightMode();
      Uri reloaded = Uri.parse(reader.wv.getUrl());
      assertEquals("pdt", reloaded.getQueryParameter("qt"));
      assertEquals("12", reloaded.getQueryParameter("d"));
      assertEquals("11", reloaded.getQueryParameter("m"));
      assertEquals("2026", reloaded.getQueryParameter("r"));
      assertEquals("mpc", reloaded.getQueryParameter("p"));
      assertEquals("1", reloaded.getQueryParameter("ds"));
      assertEquals("0", reloaded.getQueryParameter("c"));
      assertEquals("123456", reloaded.getQueryParameter("ct0"));
      assertNull(reloaded.getQueryParameter("of0fn"));
      assertSettingsKept(new UrlOptions(Breviar.S.getOpts()));
      assertFalse(new UrlOptions(Breviar.S.getOpts()).params.containsKey("qt"));
    }
  }

  @Test public void staticSpeechRequestsUseTheArticleWithoutChangingReaderSettings() {
    try (ActivityController<EinkModeTest.Reader> screen = Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
      Breviar reader = screen.get();
      Breviar.S.setOpts(OPTIONS);
      for (String page : new String[]{"include/kat-z51.htm", "include/kat-z51.htm?refresh=1&ct0=badbad"}) {
        reader.wv.loadUrl("http://127.0.0.1:" + Breviar.S.port + "/" + page);
        while (Shadows.shadowOf(reader).getNextStartedService() != null) {}
        String before = Breviar.S.getOpts();
        reader.speakAfterBackgroundCheck(false);
        Intent request = Shadows.shadowOf(reader).getNextStartedService();
        assertEquals(TtsService.TTS_START, request.getAction());
        Uri url = Uri.parse(request.getStringExtra("url"));
        assertEquals("/include/kat-z51.htm", url.getPath());
        assertEquals(Breviar.S.port_nonpersistent, url.getPort());
        UrlOptions speech = new UrlOptions(url.toString(), true);
        assertTrue(speech.isVoiceOutput());
        assertSettingsKept(speech);
        assertEquals(before, Breviar.S.getOpts());
        assertEquals(new UrlOptions(OPTIONS).params, new UrlOptions(BreviarApp.getUrlOptions(context)).params);
      }
    }
  }
}

package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.OutputStream;
import java.net.Socket;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.Implementation;
import org.robolectric.annotation.Implements;
import org.robolectric.util.ReflectionHelpers;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = {24, 35}, shadows = StaticHtmlTest.NoNative.class)
public class StaticHtmlTest {
  @Implements(value = Server.class, isInAndroidSdk = false)
  public static class NoNative {
    @Implementation protected static void __staticInitializer__() {}
  }

  private Server server() {
    return ReflectionHelpers.callConstructor(Server.class,
        ReflectionHelpers.ClassParameter.from(Context.class, RuntimeEnvironment.getApplication()));
  }

  private String request(Server server, String file) throws Exception {
    ByteArrayOutputStream bytes = new ByteArrayOutputStream();
    Socket socket = new Socket() {
      @Override public OutputStream getOutputStream() { return bytes; }
    };
    server.handleFile(socket, file, true);
    return bytes.toString("UTF-8");
  }

  private String style(String html, String options) throws Exception {
    return new String(StaticHtml.style(new ByteArrayInputStream(html.getBytes("UTF-8")), options), "UTF-8");
  }

  @Test public void allColorRolesFollowOnlyTheActivePalette() throws Exception {
    String colors = "ct0=AbC&cr0=f00&c0=ffffcc&ct1=ffffff&cr1=ffff00&c1=000000";
    String day = style("<html><head></head><body>Text</body></html>", "c=0&" + colors);
    assertTrue(day.contains("--prayer-text: #aabbcc"));
    assertTrue(day.contains("--prayer-rubric: #ff0000"));
    assertTrue(day.contains("--prayer-background: #ffffcc"));
    assertFalse(day.contains("--prayer-text: #ffffff"));
    String night = style("<p>Text</p>", "c=1&" + colors);
    assertTrue(night.contains("--prayer-text: #ffffff"));
    assertTrue(night.contains("--prayer-rubric: #ffff00"));
    assertTrue(night.contains("--prayer-background: #000000"));
    String defaults = style("<p>Text</p>", "ct0=&cr0=gggggg&c0=ffffff;bad");
    assertFalse(defaults.contains("--prayer-text:"));
    assertFalse(defaults.contains("--prayer-rubric:"));
    assertFalse(defaults.contains("--prayer-background:"));
  }

  @Test public void catechesesAndTheirIndexUseLatestAppearanceWithoutChangingPreferences() throws Exception {
    Server server = server();
    String options = "&amp;c=1&amp;c0=abcdef&amp;c1=123456&amp;f=Custom Font&amp;ff=22&amp;lh=150&amp;mm=12";
    server.setOpts(options);
    for (String file : new String[]{"include/kat-z51.htm", "katechezy.htm?refresh=1"}) {
      String html = request(server, file);
      assertTrue(html.startsWith("HTTP/1.1 200 OK"));
      assertTrue(html.contains("Content-Type: text/html; charset=utf-8"));
      assertTrue(html.contains("Cache-Control: no-store"));
      assertTrue(html.contains("/breviar-invert-colors.css"));
      assertTrue(html.contains("html, body { background-color: #123456; }"));
      assertFalse(html.contains("background-color: #abcdef"));
      assertTrue(html.contains("font-family: 'Custom Font'"));
      assertTrue(html.contains("font-size: 22pt"));
      assertTrue(html.contains("line-height: 150%"));
      assertTrue(html.contains("margin-left: 12px"));
      assertTrue(html.indexOf("static-page-appearance") < html.indexOf("</head>"));
      assertTrue(html.contains("Katechézy k žalmom a chválospevom"));
      assertEquals(options, server.getOpts());
    }
    server.setOpts("&amp;c=0&amp;c0=abc&amp;c1=123456");
    String day = request(server, "include/kat-z51.htm");
    assertFalse(day.contains("breviar-invert-colors.css"));
    assertTrue(day.contains("background-color: #aabbcc"));
  }

  @Test public void legacyNightModeOverridesAndExplicitThemeFollowReaderPrecedence() throws Exception {
    for (String options : new String[]{"o2=256", "o2=0&of2nr=1", "c=&of2nr=1"}) {
      assertTrue(style("<HTML><HEAD></HEAD><BODY>Text</BODY></HTML>", options)
          .contains("breviar-invert-colors.css"));
    }
    for (String options : new String[]{"o2=256&of2nr=0", "o2=256&c=0", "of2nr=1&c=0"}) {
      assertFalse(style("<html><head></head><body>Text</body></html>", options)
          .contains("breviar-invert-colors.css"));
    }
    String overrides = style("<p>Fragment</p>", "of0fn=1&of2rc=1&of2ff=1");
    assertTrue(overrides.contains("breviar-normal-font.css"));
    assertTrue(overrides.contains("breviar-rounded-corners.css"));
    assertTrue(overrides.contains("font-family: sans-serif"));
    assertTrue(overrides.endsWith("<p>Fragment</p>"));
  }

  @Test public void fontNamesCannotTerminateTheInjectedStyles() throws Exception {
    String html = style("<head></head><body>Text</body>", "f=O%27Brien%3C%2Fstyle%3E&c0=zzzzzz");
    assertTrue(html.contains("O\\'Brien\\3c /style>"));
    assertEquals(1, html.split("</style>", -1).length - 1);
    assertFalse(html.contains("background-color:"));
  }

  @Test public void rendererAssetsIncludeOrdinarySectionsAndTranslatedFallbacks() throws Exception {
    Server server = server();
    for (String directory : new String[]{"include", "include_cz", "include_czop", "include_hu", "include_la", "include_is"}) {
      for (String file : new String[]{"ord_invitat.htm", "ord_posvcit.htm", "ord_rchvaly.htm", "ord_vespery.htm",
          "ord_komplet.htm", "ord_km.htm", "static-unavailable.htm"}) {
        assertEquals(directory + "/" + file, 1, server.checkfile(directory + "/" + file));
      }
    }
  }
}

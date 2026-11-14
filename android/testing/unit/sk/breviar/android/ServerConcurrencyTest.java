package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
import android.net.Uri;
import java.io.ByteArrayOutputStream;
import java.io.FileDescriptor;
import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.Implementation;
import org.robolectric.annotation.Implements;
import org.robolectric.shadow.api.Shadow;
import org.robolectric.util.ReflectionHelpers;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = {24, 35}, shadows = {ServerConcurrencyTest.Renderer.class,
    ServerConcurrencyTest.NoPipeCopy.class, ServerConcurrencyTest.InputPipe.class,
    ServerConcurrencyTest.OutputPipe.class})
public class ServerConcurrencyTest {
  // Replace only JNI and pipe I/O; exercise the real HTTP handler and settings locks.
  @Implements(value = Server.class, isInAndroidSdk = false)
  public static class Renderer {
    CountDownLatch rendering, release;
    String result, environment;
    @Implementation protected static void __staticInitializer__() {
      ReflectionHelpers.setStaticField(Server.class, "NATIVE_LOCK", new Object());
    }
    @Implementation protected FileDescriptor[] createPipe() {
      return new FileDescriptor[]{new FileDescriptor(), new FileDescriptor()};
    }
    @Implementation protected String main(FileDescriptor out, FileDescriptor in, String env) {
      environment = env;
      if (rendering != null) {
        rendering.countDown();
        try {
          assertTrue("Timed out waiting to finish rendering", release.await(5, TimeUnit.SECONDS));
        } catch (InterruptedException error) {
          Thread.currentThread().interrupt();
          throw new AssertionError(error);
        }
      }
      return result;
    }
  }

  @Implements(value = Copy.class, isInAndroidSdk = false)
  public static class NoPipeCopy {
    @Implementation protected void run() {}
  }

  @Implements(value = FdInputStream.class, isInAndroidSdk = false)
  public static class InputPipe {
    @Implementation protected static void __staticInitializer__() {}
  }

  @Implements(value = FdOutputStream.class, isInAndroidSdk = false)
  public static class OutputPipe {
    @Implementation protected static void __staticInitializer__() {}
  }

  private static Server server() {
    Context context = RuntimeEnvironment.getApplication();
    Server server = ReflectionHelpers.callConstructor(Server.class,
        ReflectionHelpers.ClassParameter.from(Context.class, context));
    Server.scriptname = "breviar.cgi";
    server.setOpts("&amp;o0=0");
    server.setLanguage("en");
    return server;
  }

  private static void request(Server server, boolean persistent) throws IOException {
    request(server, "breviar.cgi?qt=pdnes", persistent);
  }

  private static void request(Server server, String page, boolean persistent) throws IOException {
    ByteArrayOutputStream output = new ByteArrayOutputStream();
    Socket client = new Socket() {
      @Override public OutputStream getOutputStream() { return output; }
    };
    server.handleCgi(client, page, false, 0, new byte[0], persistent);
  }

  private static Uri query(Renderer renderer) {
    for (String field : renderer.environment.split("\001")) {
      if (field.startsWith("QUERY_STRING=")) return Uri.parse("http://localhost/?" + field.substring(13));
    }
    throw new AssertionError("Missing CGI query string");
  }

  @Test public void settingsUpdatesDoNotWaitForSlowHttpOutput() throws Exception {
    Server server = server();
    CountDownLatch writing = new CountDownLatch(1);
    CountDownLatch release = new CountDownLatch(1);
    Socket client = new Socket() {
      @Override public OutputStream getOutputStream() {
        return new OutputStream() {
          @Override public void write(int value) throws IOException {
            writing.countDown();
            try {
              if (!release.await(5, TimeUnit.SECONDS)) throw new IOException("Test output timed out");
            } catch (InterruptedException error) {
              Thread.currentThread().interrupt();
              throw new IOException(error);
            }
          }
        };
      }
    };
    ExecutorService workers = Executors.newFixedThreadPool(2);
    try {
      Future<?> response = workers.submit(() -> {
        server.handleFile(client, "tap-navigation.js", true);
        return null;
      });
      assertTrue(writing.await(5, TimeUnit.SECONDS));
      // These methods are called on the UI thread when returning from settings.
      Future<String> update = workers.submit(() -> {
        server.setOpts("&amp;o0=64");
        server.setLanguage("sk");
        server.forceOptsForNextRequest();
        return server.getOpts();
      });
      assertEquals("&amp;o0=64", update.get(1, TimeUnit.SECONDS));
      assertFalse(response.isDone());
      release.countDown();
      response.get(5, TimeUnit.SECONDS);
    } finally {
      release.countDown();
      workers.shutdown();
      assertTrue(workers.awaitTermination(5, TimeUnit.SECONDS));
    }
  }

  @Test public void oldRenderCannotOverwriteNewSettingsOrConsumeNextRequestsOverride() throws Exception {
    Server server = server();
    Renderer renderer = Shadow.extract(server);
    renderer.rendering = new CountDownLatch(1);
    renderer.release = new CountDownLatch(1);
    renderer.result = "&amp;o0=1";
    ExecutorService workers = Executors.newFixedThreadPool(2);
    try {
      Future<?> response = workers.submit(() -> { request(server, true); return null; });
      if (!renderer.rendering.await(5, TimeUnit.SECONDS)) {
        response.get(1, TimeUnit.SECONDS); // Surface any failure before the renderer was reached.
        fail("HTTP request did not reach the renderer");
      }
      Future<?> update = workers.submit(() -> {
        server.setOpts("&amp;o0=64");
        server.setLanguage("sk");
        server.forceOptsForNextRequest();
      });
      update.get(1, TimeUnit.SECONDS);
      assertFalse(response.isDone());
      renderer.release.countDown();
      response.get(5, TimeUnit.SECONDS);
      assertEquals("&amp;o0=64", server.getOpts());
      assertTrue(renderer.environment.contains("WWW_j=en\001"));

      renderer.result = "&amp;o0=65";
      request(server, true);
      assertEquals("64", query(renderer).getQueryParameter("o0"));
      assertEquals("pdnes", query(renderer).getQueryParameter("qt"));
      assertFalse(query(renderer).getQueryParameterNames().contains("amp;o0"));
      assertTrue(renderer.environment.contains("WWW_j=sk\001"));
      assertEquals("&amp;o0=65", server.getOpts()); // Web form changes still persist.

      renderer.result = "&amp;o0=2";
      request(server, false);
      assertTrue(renderer.environment.contains("QUERY_STRING=qt=pdnes\001"));
      assertEquals("&amp;o0=65", server.getOpts()); // Dialog requests never persist.
    } finally {
      renderer.release.countDown();
      workers.shutdown();
      assertTrue(workers.awaitTermination(5, TimeUnit.SECONDS));
    }
  }

  @Test public void backKeepsClearedColorsAfterTheRendererCompactsItsSnapshot() throws Exception {
    for (String mode : new String[]{"0", "1"}) {
      Server server = server();
      Renderer renderer = Shadow.extract(server);
      String oldPage = "breviar.cgi?qt=pdt&d=13&m=11&r=2026&p=mrch&ds=1&c=" + mode
          + "&ct" + mode + "=123456&cr" + mode + "=ffffcc&c" + mode + "=111111&of0v=1";
      // Rubrics were yellow, then Default was selected, then text became yellow.
      // The completed reload drops the empty rubric/background assignments.
      renderer.result = "&amp;j=sk&amp;c=" + mode + "&amp;ct" + mode + "=ffffcc&amp;o0=64";
      request(server, "breviar.cgi?qt=pdt&d=14&m=11&r=2026&p=mv&c=" + mode
          + "&ct" + mode + "=ffffcc&cr" + mode + "=&c" + mode + "=", true);

      for (int back = 0; back < 2; ++back) {
        server.forceOptsForNextRequest();
        request(server, oldPage, true);
        Uri query = query(renderer);
        assertEquals("ffffcc", query.getQueryParameter("ct" + mode));
        for (String key : new String[]{"ct0", "cr0", "c0", "ct1", "cr1", "c1"}) {
          assertEquals(1, query.getQueryParameters(key).size());
          if (!key.equals("ct" + mode)) assertEquals("", query.getQueryParameter(key));
        }
        assertEquals(mode, query.getQueryParameter("c"));
        assertEquals("64", query.getQueryParameter("o0"));
        assertNull(query.getQueryParameter("of0v"));
        assertEquals("pdt", query.getQueryParameter("qt"));
        assertEquals("13", query.getQueryParameter("d"));
        assertEquals("mrch", query.getQueryParameter("p"));
        assertEquals("1", query.getQueryParameter("ds"));
      }
    }
  }

  @Test public void backClearsColorsWithEmptyOptionsAndPreservesSelectionFromHistory() throws Exception {
    for (String saved : new String[]{"", "ct1=ffffcc", "&amp;qt=pdnes&amp;p=mk&amp;d=14&amp;m=12&amp;r=2027&amp;ds=2"}) {
      Server server = server();
      Renderer renderer = Shadow.extract(server);
      server.setOpts(saved);
      renderer.result = "&amp;j=sk";
      server.forceOptsForNextRequest();
      request(server, "breviar.cgi?qt=pdt&d=13&m=11&r=2026&p=mrch&ds=1&cr1=ffffcc&c1=111111", true);
      Uri query = query(renderer);
      assertEquals("", query.getQueryParameter("cr1"));
      assertEquals("", query.getQueryParameter("c1"));
      assertEquals("pdt", query.getQueryParameter("qt"));
      assertEquals("13", query.getQueryParameter("d"));
      assertEquals("11", query.getQueryParameter("m"));
      assertEquals("2026", query.getQueryParameter("r"));
      assertEquals("mrch", query.getQueryParameter("p"));
      assertEquals("1", query.getQueryParameter("ds"));
    }
  }

  @Test public void completedPostSelectionIsAvailableForSharingWithoutAffectingOtherPages() throws Exception {
    Server server = server();
    Renderer renderer = Shadow.extract(server);
    renderer.result = "&amp;j=sk&amp;o1=123";
    byte[] form = "d=14&m=11&r=2026&p=mv".getBytes(java.nio.charset.StandardCharsets.UTF_8);
    Socket client = new Socket() {
      @Override public OutputStream getOutputStream() { return new ByteArrayOutputStream(); }
    };
    String address = "http://127.0.0.1:50000/breviar.cgi?qt=pdt&d=13";
    server.handleCgi(client, "breviar.cgi?qt=pdt&d=13", true, form.length, form, true);
    UrlOptions page = new UrlOptions(server.getPageUrl(address), true);
    assertEquals("pdt", page.params.get("qt"));
    assertEquals("14", page.params.get("d"));
    assertEquals("mv", page.params.get("p"));
    String earlier = "http://127.0.0.1:50000/breviar.cgi?qt=pdnes";
    assertEquals(earlier, server.getPageUrl(earlier));
    request(server, false); // Background XML/TTS must not replace the reader selection.
    assertEquals("14", new UrlOptions(server.getPageUrl(address), true).params.get("d"));
  }

  @Test public void backendResolvedDateIsSharedAndDoesNotBecomeAPersistentSetting() throws Exception {
    Server server = server();
    Renderer renderer = Shadow.extract(server);
    renderer.result = "&amp;j=sk&amp;o1=123\nqt=pdt&d=12&m=11&r=2026&p=mpc&ds=1";
    request(server, true);
    String page = server.getPageUrl("http://127.0.0.1:50000/breviar.cgi?qt=pdnes");
    UrlOptions query = new UrlOptions(page, true);
    assertEquals("pdt", query.params.get("qt"));
    assertEquals("12", query.params.get("d"));
    assertEquals("1", query.params.get("ds"));
    assertEquals("&amp;j=sk&amp;o1=123", server.getOpts());
    String shared = PrayerLink.share(page, server.getOpts(), "sk");
    assertEquals("2026", new UrlOptions(shared, true).params.get("r"));
    // A settings/TTS render cannot replace the foreground page's identity.
    renderer.result = "&amp;j=la\nqt=pdt&d=13&m=11&r=2026&p=mv";
    request(server, false);
    assertEquals(page, server.getPageUrl("http://127.0.0.1:50000/breviar.cgi?qt=pdnes"));
    // An overview carries no resolved identity and stays relative.
    renderer.result = "&amp;j=sk\n";
    request(server, true);
    assertEquals("pdnes", new UrlOptions(server.getPageUrl(
        "http://127.0.0.1:50000/breviar.cgi?qt=pdnes"), true).params.get("qt"));
  }
}

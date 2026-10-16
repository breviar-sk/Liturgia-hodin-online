package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
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
    ByteArrayOutputStream output = new ByteArrayOutputStream();
    Socket client = new Socket() {
      @Override public OutputStream getOutputStream() { return output; }
    };
    server.handleCgi(client, "breviar.cgi?qt=pdnes", false, 0, new byte[0], persistent);
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
      assertTrue(renderer.environment.contains("QUERY_STRING=amp;o0=64&qt=pdnes\001"));
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
}

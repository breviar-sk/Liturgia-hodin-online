package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
import android.os.Bundle;
import android.os.Looper;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.LinearLayout;
import java.time.Duration;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import org.junit.After;
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
import org.robolectric.shadow.api.Shadow;
import org.robolectric.shadows.ShadowWebView;
import org.robolectric.util.ReflectionHelpers.ClassParameter;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = {24, 35}, shadows = {
    XmlSettingsActivityTest.SettingsServer.class, ScrollRestorationTest.RenderingWebView.class})
@LooperMode(LooperMode.Mode.PAUSED)
public class ScrollRestorationTest {
  @Implements(WebView.class)
  public static class RenderingWebView extends ShadowWebView {
    int height = 2000;
    final List<Runnable> frames = new ArrayList<>();
    @Implementation protected int getContentHeight() { return height; }
    @Implementation protected boolean setFrame(int left, int top, int right, int bottom) {
      // WebView delegates this to Chromium, which Robolectric does not run.
      return Shadow.directlyOn(realView, View.class, "setFrame",
          ClassParameter.from(int.class, left), ClassParameter.from(int.class, top),
          ClassParameter.from(int.class, right), ClassParameter.from(int.class, bottom));
    }
    @Implementation protected void postVisualStateCallback(long request, WebView.VisualStateCallback callback) {
      frames.add(() -> callback.onComplete(request));
    }
  }

  private ActivityController<EinkModeTest.Reader> controller;
  private Breviar reader;
  private RenderingWebView web;
  private WebViewClient client;
  private Breviar.Bridge bridge;

  @Before public void createReader() {
    Context context = RuntimeEnvironment.getApplication();
    BreviarApp.setString(context, "version", context.getString(R.string.version));
    BreviarApp.setEinkMode(context, true);
    Bundle state = new Bundle();
    state.putString("wv-url", "http://127.0.0.1:50000/l.cgi?qt=pdt&d=16&m=10&r=2026&p=1");
    state.putFloat("wv-scroll-to", 0.4f);
    controller = Robolectric.buildActivity(EinkModeTest.Reader.class)
        .create(state).start().restoreInstanceState(state).postCreate(state).resume().visible();
    reader = controller.get();
    viewport(800);
    web = Shadow.extract(reader.wv);
    client = web.getWebViewClient();
    bridge = (Breviar.Bridge)web.getJavascriptInterface("bridge");
  }

  @After public void closeReader() { controller.close(); }

  private void viewport(int height) {
    // Robolectric has no rendered web contents. Give the reader a fixed viewport
    // so activity traversals cannot shrink its weight-based layout back to zero.
    reader.wv.setLayoutParams(new LinearLayout.LayoutParams(600, height));
    reader.wv.measure(android.view.View.MeasureSpec.makeMeasureSpec(600, android.view.View.MeasureSpec.EXACTLY),
        android.view.View.MeasureSpec.makeMeasureSpec(height, android.view.View.MeasureSpec.EXACTLY));
    reader.wv.layout(0, 0, 600, height);
  }

  private long finishLoad() {
    String url = reader.wv.getUrl();
    client.onPageStarted(reader.wv, url, null);
    client.onPageFinished(reader.wv, url);
    Matcher request = Pattern.compile("prepareScrollRestore\\((\\d+)," + reader.scale + "\\)")
        .matcher(web.getLastEvaluatedJavascript());
    assertTrue("Expected zoom/font-readiness request", request.find());
    return Long.parseLong(request.group(1));
  }

  private static void idle() { Shadows.shadowOf(Looper.getMainLooper()).idle(); }
  private static void slowDevice() {
    Shadows.shadowOf(Looper.getMainLooper()).idleFor(Duration.ofSeconds(3));
  }

  @Test public void waitsForFontsAndRenderingThenRestoresImmediatelyExactlyOnce() throws Exception {
    long request = finishLoad();
    slowDevice();
    assertEquals(0, reader.wv.getScrollY());
    assertTrue(web.frames.isEmpty());
    assertEquals(0.4f, reader.scroll_to, 0f);
    // JavaScript interfaces run on a background thread; only the UI may call WebView.
    Thread javascript = new Thread(() -> bridge.scrollReady(request));
    javascript.start();
    javascript.join();
    idle();
    assertEquals(1, web.frames.size());
    slowDevice();
    assertEquals(0, reader.wv.getScrollY());
    assertEquals(2000, reader.wv.getContentHeight());
    assertTrue("Viewport height=" + reader.wv.getHeight(), reader.wv.getHeight() > 0);
    web.frames.get(0).run(); // No clock advance after the frame becomes ready.
    assertEquals(800, reader.wv.getScrollY());
    assertEquals(-1f, reader.scroll_to, 0f);
    reader.wv.scrollTo(0, 300);
    bridge.scrollReady(request);
    web.frames.get(0).run();
    assertEquals(300, reader.wv.getScrollY());
    assertEquals(1, web.frames.size());
  }

  @Test public void missingViewportOrContentWaitsForLayoutWithoutDroppingThePosition() {
    long request = finishLoad();
    web.height = 0;
    viewport(0);
    bridge.scrollReady(request);
    web.frames.get(0).run();
    slowDevice();
    assertEquals(0.4f, reader.scroll_to, 0f);
    Bundle saved = new Bundle();
    controller.saveInstanceState(saved);
    assertEquals(0.4f, saved.getFloat("wv-scroll-to"), 0f);
    web.height = 3000;
    reader.wv.getViewTreeObserver().dispatchOnPreDraw();
    assertEquals(0.4f, reader.scroll_to, 0f); // Still no viewport.
    viewport(800);
    reader.wv.getViewTreeObserver().dispatchOnPreDraw();
    assertEquals(1200, reader.wv.getScrollY());
    assertEquals(-1f, reader.scroll_to, 0f);
  }

  @Test public void anotherNavigationRejectsBothFontAndVisualCallbacks() {
    long request = finishLoad();
    bridge.scrollReady(request);
    String next = "http://127.0.0.1:50000/l.cgi?qt=pdnes&p=2";
    reader.wv.loadUrl(next);
    client.onPageStarted(reader.wv, next, null);
    bridge.scrollReady(request);
    web.frames.get(0).run();
    assertEquals(0, reader.wv.getScrollY());
    assertEquals(-1f, reader.scroll_to, 0f);
    assertEquals(1, web.frames.size());
  }

  @Test public void repeatedReloadPreservesPositionAndRejectsOlderRequests() {
    long old = finishLoad();
    bridge.scrollReady(old);
    reader.toggleNightMode();
    // An old finish notification must not start restoration before the new page starts.
    client.onPageFinished(reader.wv, reader.wv.getUrl());
    bridge.scrollReady(old);
    web.frames.get(0).run();
    assertEquals(0.4f, reader.scroll_to, 0f);
    assertEquals(0, reader.wv.getScrollY());
    long current = finishLoad();
    assertNotEquals(old, current);
    bridge.scrollReady(current);
    web.frames.get(1).run();
    assertEquals(800, reader.wv.getScrollY());
  }

  @Test public void touchPagingKeysAndButtonsCancelLateRestoration() {
    for (int input = 0; input < 5; ++input) {
      reader.scroll_to = 0.4f;
      reader.toggleNightMode();
      long request = finishLoad();
      bridge.scrollReady(request);
      Runnable frame = web.frames.get(web.frames.size() - 1);
      switch (input) {
        case 0:
          int[] location = new int[2];
          reader.wv.getLocationOnScreen(location);
          MotionEvent touch = MotionEvent.obtain(0, 0, MotionEvent.ACTION_DOWN,
              location[0] + 20, location[1] + 20, 0);
          reader.dispatchTouchEvent(touch);
          touch.recycle();
          break;
        case 1: reader.findViewById(R.id.navigation_page_down).performClick(); break;
        case 2: reader.onKeyDown(KeyEvent.KEYCODE_VOLUME_DOWN,
            new KeyEvent(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_VOLUME_DOWN)); break;
        case 3: reader.dispatchKeyEvent(new KeyEvent(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_DPAD_DOWN)); break;
        default: bridge.pageDown();
      }
      int position = reader.wv.getScrollY();
      assertEquals("Input=" + input + ", viewport=" + reader.wv.getWidth() + "x" + reader.wv.getHeight(),
          -1f, reader.scroll_to, 0f);
      frame.run();
      bridge.scrollReady(request);
      assertEquals(position, reader.wv.getScrollY());
    }
  }

  @Test public void homeCancelsEvenBeforeTheNewPageStarts() {
    long request = finishLoad();
    bridge.scrollReady(request);
    reader.goHome();
    bridge.scrollReady(request);
    web.frames.get(0).run();
    assertEquals(0, reader.wv.getScrollY());
    assertEquals(-1f, reader.scroll_to, 0f);
  }

  @Test public void destructionRejectsQueuedCallbacks() {
    long request = finishLoad();
    bridge.scrollReady(request);
    controller.pause().stop().destroy();
    bridge.scrollReady(request);
    web.frames.get(0).run();
    assertEquals(0, reader.wv.getScrollY());
    assertEquals(1, web.frames.size());
  }
}

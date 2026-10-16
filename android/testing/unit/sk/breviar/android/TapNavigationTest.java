package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
import android.os.Looper;
import android.os.SystemClock;
import android.view.MotionEvent;
import android.view.ViewConfiguration;
import android.webkit.ValueCallback;
import android.webkit.WebView;
import java.time.Duration;
import org.json.JSONObject;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.Shadows;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.LooperMode;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = {24, 35})
@LooperMode(LooperMode.Mode.PAUSED)
public class TapNavigationTest {
  private final Context context = RuntimeEnvironment.getApplication();

  private static class Pages extends WebView {
    int turns, jumps, configurations;
    String lastConfiguration;
    Pages(Context context) { super(context); layout(0, 0, 600, 800); }
    @Override public boolean pageDown(boolean bottom) { ++turns; return true; }
    @Override public boolean pageUp(boolean top) { --turns; return true; }
    @Override public void scrollBy(int x, int y) { jumps += y; }
    @Override public void evaluateJavascript(String script, ValueCallback<String> callback) {
      ++configurations;
      lastConfiguration = script;
      super.evaluateJavascript(script, callback);
    }
  }

  private static void idle() { Shadows.shadowOf(Looper.getMainLooper()).idle(); }
  private static void settle() {
    Shadows.shadowOf(Looper.getMainLooper()).idleFor(Duration.ofMillis(ViewConfiguration.getDoubleTapTimeout() + 1));
  }
  private static String token(TapNavigation taps) throws Exception {
    return new JSONObject(taps.settings()).getString("token");
  }
  private TapNavigation ready(Pages pages, Runnable fullscreen) throws Exception {
    TapNavigation taps = new TapNavigation(pages, 50000, false, fullscreen);
    taps.pageStarted("http://127.0.0.1:50000/l.cgi?qt=pdnes");
    taps.setMode(ReadingNavigation.Mode.TAPS);
    taps.setActive(true);
    taps.ready(token(taps));
    idle();
    return taps;
  }
  private static void touch(TapNavigation taps, int action, long start, long time, float x, float y) {
    MotionEvent event = MotionEvent.obtain(start, time, action, x, y, 0);
    taps.observeTouch(event);
    event.recycle();
  }
  private static void tap(TapNavigation taps, long id) throws Exception {
    long now = SystemClock.uptimeMillis();
    touch(taps, MotionEvent.ACTION_DOWN, now, now, 100, 100);
    taps.begin(token(taps), id);
    touch(taps, MotionEvent.ACTION_UP, now, now + 20, 100, 100);
    idle();
  }

  @Test public void unusedTapPagesImmediatelyOnceAndRetainsEinkPaging() throws Exception {
    Pages pages = new Pages(context);
    TapNavigation taps = ready(pages, null);
    tap(taps, 1);
    taps.perform(token(taps), 1, "down");
    taps.perform(token(taps), 1, "down");
    idle(); // No clock advance: there must be no double-tap wait.
    assertEquals(1, pages.turns);
    BreviarApp.setEinkMode(context, true);
    tap(taps, 2);
    taps.perform(token(taps), 2, "up");
    idle();
    assertEquals(1, pages.turns);
    assertTrue(pages.jumps < 0 && pages.jumps > -800);
    taps.close(); pages.destroy();
  }

  @Test public void requiresReadyScriptRealCompletedTouchAndExplicitUnusedReport() throws Exception {
    Pages pages = new Pages(context);
    TapNavigation taps = ready(pages, null);
    taps.begin(token(taps), 1);
    taps.perform(token(taps), 1, "down");
    settle();
    assertEquals(0, pages.turns);
    tap(taps, 2); // claimed or uncertain: no perform report
    settle();
    assertEquals(0, pages.turns);
    taps.setActive(false); taps.setActive(true); // no ready from the new session
    tap(taps, 3);
    taps.perform(token(taps), 3, "down");
    settle();
    assertEquals(0, pages.turns);
    taps.close(); pages.destroy();
  }

  @Test public void newerTouchAndNewerJavascriptGestureInvalidateQueuedActions() throws Exception {
    Pages pages = new Pages(context);
    TapNavigation taps = ready(pages, null);
    tap(taps, 1);
    taps.perform(token(taps), 1, "down");
    long now = SystemClock.uptimeMillis();
    touch(taps, MotionEvent.ACTION_DOWN, now, now, 100, 100);
    taps.begin(token(taps), 2);
    idle(); // The queued report belongs to the previous touch.
    touch(taps, MotionEvent.ACTION_UP, now, now + 20, 100, 100);
    settle();
    assertEquals(0, pages.turns);
    taps.perform(token(taps), 1, "down");
    settle();
    assertEquals(0, pages.turns);
    taps.perform(token(taps), 2, "down");
    settle();
    assertEquals(1, pages.turns);
    taps.close(); pages.destroy();
  }

  @Test public void navigationPauseModeAndSelectionRejectDelayedReports() throws Exception {
    for (int reason = 0; reason < 7; ++reason) {
      Pages pages = new Pages(context);
      TapNavigation taps = ready(pages, null);
      tap(taps, 1);
      String old = token(taps);
      taps.perform(old, 1, "down");
      switch (reason) {
        case 0: taps.pageStarted("http://127.0.0.1:50000/l.cgi?p=2"); break;
        case 1: taps.setActive(false); break;
        case 2: taps.setMode(ReadingNavigation.Mode.SCROLL); break;
        case 3: taps.setSelecting(true); break;
        case 4: taps.cancelPendingGesture(); break;
        case 5: taps.setMode(ReadingNavigation.Mode.TAPS_HORIZONTAL); break;
        default: taps.close();
      }
      assertNotEquals(old, token(taps));
      taps.perform(old, 1, "down");
      settle();
      assertEquals(0, pages.turns);
      taps.close(); pages.destroy();
    }
  }

  @Test public void switchingTapAxisRequiresNewReadyReportAndPreservesImmediatePaging() throws Exception {
    Pages pages = new Pages(context);
    TapNavigation taps = ready(pages, null);
    assertFalse(new JSONObject(taps.settings()).getBoolean("horizontal"));
    for (ReadingNavigation.Mode mode : new ReadingNavigation.Mode[]{
        ReadingNavigation.Mode.TAPS_HORIZONTAL, ReadingNavigation.Mode.TAPS}) {
      String previous = token(taps);
      taps.setMode(mode);
      assertNotEquals(previous, token(taps));
      JSONObject settings = new JSONObject(taps.settings());
      assertTrue(settings.getBoolean("enabled"));
      assertEquals(mode == ReadingNavigation.Mode.TAPS_HORIZONTAL, settings.getBoolean("horizontal"));
      int before = pages.turns;
      tap(taps, 1);
      taps.perform(token(taps), 1, "down");
      idle();
      assertEquals(before, pages.turns);
      taps.ready(token(taps));
      idle();
      tap(taps, 2);
      taps.perform(token(taps), 2, "down");
      idle();
      assertEquals(before + 1, pages.turns);
    }
    taps.close(); pages.destroy();
  }

  @Test public void missingAcknowledgementRetriesAndCurrentReadyStopsRetries() throws Exception {
    Pages pages = new Pages(context);
    TapNavigation taps = ready(pages, null);
    String previous = token(taps);
    taps.setMode(ReadingNavigation.Mode.TAPS_HORIZONTAL);
    int attempts = pages.configurations;
    taps.ready(previous); idle(); // A delayed acknowledgement is not sufficient.
    Shadows.shadowOf(Looper.getMainLooper()).idleFor(Duration.ofMillis(250));
    assertTrue(pages.configurations > attempts);
    assertEquals("window.BreviarTaps && window.BreviarTaps.configure()", pages.lastConfiguration);
    assertFalse(pages.lastConfiguration.contains(previous));
    attempts = pages.configurations;
    taps.ready(token(taps)); idle();
    Shadows.shadowOf(Looper.getMainLooper()).idleFor(Duration.ofSeconds(5));
    assertEquals(attempts, pages.configurations);
    tap(taps, 1); taps.perform(token(taps), 1, "down"); idle();
    assertEquals(1, pages.turns);
    taps.close(); pages.destroy();
  }

  @Test public void repeatedSwitchesRecoverAcrossReloadAndResumeOrderings() throws Exception {
    Pages pages = new Pages(context);
    int[] fullscreen = {0};
    TapNavigation taps = ready(pages, () -> ++fullscreen[0]);
    for (int i = 0; i < 24; ++i) {
      boolean eink = i % 4 < 2;
      BreviarApp.setEinkMode(context, eink);
      String previous = token(taps);
      String url = "http://127.0.0.1:50000/l.cgi?d=" + i;
      taps.setActive(false);
      if (i % 3 == 0) taps.pageStarted(url);
      taps.setMode(i % 2 == 0 ? ReadingNavigation.Mode.TAPS_HORIZONTAL : ReadingNavigation.Mode.TAPS);
      if (i % 3 == 1) taps.pageStarted(url);
      taps.setActive(true);
      if (i % 3 == 2) taps.pageStarted(url);
      taps.pageFinished();
      taps.ready(token(taps));
      taps.ready(previous); // A late acknowledgement cannot disable the current session.
      idle();
      int turns = pages.turns, jumps = pages.jumps;
      tap(taps, 1); taps.perform(token(taps), 1, "down"); idle();
      if (eink) assertTrue(pages.jumps > jumps);
      else assertEquals(turns + 1, pages.turns);
      tap(taps, 2); taps.perform(token(taps), 2, "fullscreen"); idle();
      assertEquals(i + 1, fullscreen[0]);
      tap(taps, 3); taps.perform(token(taps), 3, "up"); idle();
      assertEquals(turns, pages.turns);
      assertEquals(jumps, pages.jumps);
    }
    taps.close(); pages.destroy();
  }

  @Test public void retriesAreBoundedAndNextTouchCanRestartHandshakeWithoutPagingThatTouch() throws Exception {
    Pages pages = new Pages(context);
    TapNavigation taps = ready(pages, null);
    taps.setMode(ReadingNavigation.Mode.TAPS_HORIZONTAL);
    int firstAttempt = pages.configurations;
    Shadows.shadowOf(Looper.getMainLooper()).idleFor(Duration.ofSeconds(5));
    int exhausted = pages.configurations;
    assertTrue(exhausted > firstAttempt && exhausted <= firstAttempt + 4);
    Shadows.shadowOf(Looper.getMainLooper()).idleFor(Duration.ofSeconds(5));
    assertEquals(exhausted, pages.configurations);
    long now = SystemClock.uptimeMillis();
    touch(taps, MotionEvent.ACTION_DOWN, now, now, 100, 100);
    assertTrue(pages.configurations > exhausted);
    taps.begin(token(taps), 1);
    taps.ready(token(taps)); idle();
    touch(taps, MotionEvent.ACTION_UP, now, now + 20, 100, 100);
    taps.perform(token(taps), 1, "down"); idle();
    assertEquals(0, pages.turns); // Never authorize a tap that began before ready.
    tap(taps, 2); taps.perform(token(taps), 2, "down"); idle();
    assertEquals(1, pages.turns);
    taps.close(); pages.destroy();
  }

  @Test public void staleJavascriptSessionRequestsCurrentSettingsWithoutAcceptingOldActions() throws Exception {
    Pages pages = new Pages(context);
    TapNavigation taps = ready(pages, null);
    String previous = token(taps);
    taps.setMode(ReadingNavigation.Mode.TAPS_HORIZONTAL);
    taps.ready(token(taps)); idle();
    int attempts = pages.configurations;
    taps.begin(previous, 100);
    taps.perform(previous, 100, "down"); idle();
    assertEquals(attempts + 1, pages.configurations);
    assertEquals(0, pages.turns);
    tap(taps, 1); taps.perform(token(taps), 1, "down"); idle();
    assertEquals(1, pages.turns);
    taps.close(); pages.destroy();
  }

  @Test public void pendingReadinessRetriesStopOnPauseSelectionNavigationAndClose() throws Exception {
    for (int reason = 0; reason < 5; ++reason) {
      Pages pages = new Pages(context);
      TapNavigation taps = ready(pages, null);
      taps.setMode(ReadingNavigation.Mode.TAPS_HORIZONTAL);
      switch (reason) {
        case 0: taps.setActive(false); break;
        case 1: taps.setSelecting(true); break;
        case 2: taps.pageStarted("https://example.com"); break;
        case 3: taps.setMode(ReadingNavigation.Mode.SCROLL); break;
        default: taps.close();
      }
      int attempts = pages.configurations;
      Shadows.shadowOf(Looper.getMainLooper()).idleFor(Duration.ofSeconds(5));
      assertEquals(attempts, pages.configurations);
      taps.close(); pages.destroy();
    }
  }

  @Test public void dragLongPressAndCanceledTouchCannotPage() throws Exception {
    for (int reason = 0; reason < 3; ++reason) {
      Pages pages = new Pages(context);
      TapNavigation taps = ready(pages, null);
      long now = SystemClock.uptimeMillis();
      touch(taps, MotionEvent.ACTION_DOWN, now, now, 100, 100);
      taps.begin(token(taps), 1);
      if (reason == 0) touch(taps, MotionEvent.ACTION_MOVE, now, now + 10, 100, 400);
      if (reason == 2) touch(taps, MotionEvent.ACTION_CANCEL, now, now + 10, 100, 100);
      touch(taps, MotionEvent.ACTION_UP, now,
          now + (reason == 1 ? ViewConfiguration.getLongPressTimeout() + 10 : 20), 100, 100);
      taps.perform(token(taps), 1, "down");
      settle();
      assertEquals(0, pages.turns);
      taps.close(); pages.destroy();
    }
  }

  @Test public void externalPagesNeverEnableTapNavigation() throws Exception {
    Pages pages = new Pages(context);
    TapNavigation taps = ready(pages, null);
    for (String url : new String[]{"https://example.com/", "http://127.0.0.1:50001/l.cgi",
        "http://127.0.0.1:50000/katechezy.htm", "data:text/html,external"}) {
      taps.pageStarted(url);
      assertFalse(taps.ownsGestures());
      assertFalse(new JSONObject(taps.settings()).getBoolean("enabled"));
      taps.ready(token(taps));
      tap(taps, 1);
      taps.perform(token(taps), 1, "down");
      settle();
      assertEquals(0, pages.turns);
    }
    taps.close(); pages.destroy();
  }

  @Test public void doubleTapRequestTogglesFullscreenWithoutPaging() throws Exception {
    Pages pages = new Pages(context);
    int[] count = {0};
    TapNavigation taps = ready(pages, () -> ++count[0]);
    tap(taps, 1); tap(taps, 2);
    taps.perform(token(taps), 2, "fullscreen");
    settle();
    assertEquals(1, count[0]);
    assertEquals(0, pages.turns);
    taps.close(); pages.destroy();
  }

  @Test public void scrollingCancelsNativeActionAlreadyQueuedByJavascript() throws Exception {
    Pages pages = new Pages(context);
    TapNavigation taps = ready(pages, null);
    tap(taps, 1);
    taps.perform(token(taps), 1, "down");
    pages.scrollTo(0, 100);
    assertEquals(100, pages.getScrollY());
    settle();
    assertEquals(0, pages.turns);
    taps.close(); pages.destroy();
  }
}

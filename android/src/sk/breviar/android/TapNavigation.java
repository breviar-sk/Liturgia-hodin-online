package sk.breviar.android;

import android.content.Context;
import android.net.Uri;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.view.MotionEvent;
import android.view.ViewConfiguration;
import android.webkit.JavascriptInterface;
import android.webkit.WebView;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.util.UUID;
import org.json.JSONException;
import org.json.JSONObject;

/** The HTML classifies and arbitrates taps; this controller validates their lifetime
 * and performs native actions. All mutable state except settingsJson stays on UI. */
final class TapNavigation {
  private static final int READY_RETRY_DELAY_MS = 250;
  private static final int MAX_READY_RETRIES = 4;
  private final WebView view;
  private final int port;
  private final boolean inlineContent;
  private final Runnable fullscreen;
  private final Handler ui = new Handler(Looper.getMainLooper());
  private final int slop, doubleSlop;
  private ReadingNavigation.Mode mode = ReadingNavigation.Mode.SCROLL;
  private boolean active, localPage, ready, selecting;
  private boolean fingerDown, validTouch;
  private float downX, downY;
  private long inputSerial, downTime, gestureId, performedId;
  private String token = UUID.randomUUID().toString();
  private volatile String settingsJson;
  private int readyRetries;
  private boolean retryPending;
  private final Runnable retryReady = () -> {
    retryPending = false;
    if (needsReady()) {
      ++readyRetries;
      configurePage();
    }
  };

  TapNavigation(WebView view, int port, boolean inlineContent, Runnable fullscreen) {
    this.view = view;
    this.port = port;
    this.inlineContent = inlineContent;
    this.fullscreen = fullscreen;
    ViewConfiguration configuration = ViewConfiguration.get(view.getContext());
    slop = configuration.getScaledTouchSlop();
    doubleSlop = configuration.getScaledDoubleTapSlop();
    publishSettings();
    view.addJavascriptInterface(this, "tapNavigation");
    view.setOnTouchListener((v, event) -> {
      observeTouch(event);
      return false; // WebView always receives the original event.
    });
    view.setOnScrollChangeListener((v, x, y, oldX, oldY) -> {
      // Includes volume keys, restored position, flings and HTML anchor jumps.
      ++inputSerial;
      validTouch = false;
    });
  }

  boolean ownsGestures() { return mode.isTapNavigation() && active && localPage; }

  boolean contains(float screenX, float screenY) {
    int[] location = new int[2];
    view.getLocationOnScreen(location);
    return screenX >= location[0] && screenX < location[0] + view.getWidth()
        && screenY >= location[1] && screenY < location[1] + view.getHeight();
  }

  void observeTouch(MotionEvent event) {
    switch (event.getActionMasked()) {
      case MotionEvent.ACTION_DOWN:
        ++inputSerial;
        fingerDown = true;
        // A slow/missed handshake must not disable taps until the next reload.
        // Retry without authorizing this touch or bypassing HTML classification.
        if (needsReady() && !retryPending) {
          readyRetries = 0;
          configurePage();
        }
        validTouch = ownsGestures() && ready && !selecting;
        downX = event.getX();
        downY = event.getY();
        downTime = event.getEventTime();
        break;
      case MotionEvent.ACTION_MOVE:
        float dx = event.getX() - downX, dy = event.getY() - downY;
        if (dx * dx + dy * dy > slop * slop) validTouch = false;
        break;
      case MotionEvent.ACTION_POINTER_DOWN:
      case MotionEvent.ACTION_CANCEL:
        validTouch = false;
        ++inputSerial;
        break;
      case MotionEvent.ACTION_UP:
        fingerDown = false;
        if (event.getEventTime() - downTime >= ViewConfiguration.getLongPressTimeout()) validTouch = false;
        break;
    }
  }

  void pageStarted(String url) {
    Uri uri = Uri.parse(url == null ? "" : url);
    localPage = (inlineContent && "data".equals(uri.getScheme())) ||
        (port > 0 && "http".equals(uri.getScheme()) && "127.0.0.1".equals(uri.getHost())
            && uri.getPort() == port && "/l.cgi".equals(uri.getPath()));
    invalidate(false);
  }

  void pageFinished() { configurePage(); }

  void setMode(ReadingNavigation.Mode value) {
    if (mode == value) return;
    mode = value;
    invalidate(true);
  }

  void setActive(boolean value) {
    if (active == value) return;
    active = value;
    invalidate(true);
  }

  void setSelecting(boolean value) {
    selecting = value;
    invalidate(true);
  }

  void cancelPendingGesture() { invalidate(true); }

  void close() {
    active = false;
    invalidate(false);
    ui.removeCallbacksAndMessages(null);
    view.setOnTouchListener(null);
    view.setOnScrollChangeListener(null);
    view.removeJavascriptInterface("tapNavigation");
  }

  private void invalidate(boolean configure) {
    stopReadyRetry();
    readyRetries = 0;
    token = UUID.randomUUID().toString();
    ready = validTouch = false;
    gestureId = performedId = 0;
    ++inputSerial;
    publishSettings();
    if (configure) configurePage();
  }

  private void publishSettings() {
    float density = view.getResources().getDisplayMetrics().density;
    try {
      settingsJson = new JSONObject().put("token", token)
          .put("enabled", ownsGestures() && !selecting)
          .put("horizontal", mode == ReadingNavigation.Mode.TAPS_HORIZONTAL)
          .put("fullscreen", fullscreen != null)
          .put("touchSlop", slop / density).put("doubleTapSlop", doubleSlop / density)
          .put("doubleTapTimeout", ViewConfiguration.getDoubleTapTimeout())
          .put("longPressTimeout", ViewConfiguration.getLongPressTimeout()).toString();
    } catch (JSONException error) { throw new IllegalStateException(error); }
  }

  private void configurePage() {
    if (!localPage) return;
    // Fetch settings when JavaScript actually runs. A queued call must not
    // restore an old mode/token after resume or another configuration change.
    view.evaluateJavascript("window.BreviarTaps && window.BreviarTaps.configure()", null);
    if (needsReady() && !retryPending) {
      if (readyRetries < MAX_READY_RETRIES) {
        retryPending = true;
        ui.postDelayed(retryReady, READY_RETRY_DELAY_MS);
      } else {
        Log.w("BreviarTaps", "No readiness acknowledgement; mode=" + mode.value
            + ". Will retry on the next touch or page callback.");
      }
    }
  }

  private boolean needsReady() { return ownsGestures() && !selecting && !ready; }

  private void stopReadyRetry() {
    ui.removeCallbacks(retryReady);
    retryPending = false;
  }

  @JavascriptInterface public String settings() { return settingsJson; }

  @JavascriptInterface public void ready(String pageToken) {
    ui.post(() -> {
      if (token.equals(pageToken) && ownsGestures() && !selecting) {
        ready = true;
        stopReadyRetry();
      }
    });
  }

  @JavascriptInterface public void begin(String pageToken, long id) {
    ui.post(() -> {
      if (!token.equals(pageToken)) {
        if (ownsGestures() && !selecting) configurePage();
        return;
      }
      if (ownsGestures() && id > gestureId) gestureId = id;
    });
  }

  @JavascriptInterface public void perform(String pageToken, long id, String action) {
    ui.post(() -> {
      if (!canPerform(pageToken, id)) return;
      if (!action.equals("up") && !action.equals("down") && !action.equals("fullscreen")) return;
      long serial = inputSerial;
      // Outer-third taps page immediately. Still reject new input that arrives
      // while the reported action is queued on the UI thread.
      ui.post(() -> {
        if (serial != inputSerial || !canPerform(pageToken, id)) return;
        performedId = id;
        if (action.equals("fullscreen")) {
          if (fullscreen != null) fullscreen.run();
        } else {
          EinkUi.page(view, action.equals("down"));
        }
      });
    });
  }

  private boolean canPerform(String pageToken, long id) {
    return token.equals(pageToken) && ownsGestures() && ready && !selecting &&
        validTouch && !fingerDown && id == gestureId && id > performedId;
  }

  static String withScript(Context context, String html) throws IOException {
    try (InputStream in = context.getAssets().open("tap-navigation.js")) {
      ByteArrayOutputStream bytes = new ByteArrayOutputStream();
      byte[] buffer = new byte[4096];
      int count;
      while ((count = in.read(buffer)) != -1) bytes.write(buffer, 0, count);
      String script = "<script>" + new String(bytes.toByteArray(), StandardCharsets.UTF_8) + "</script>";
      int head = html.indexOf("</head>");
      return head >= 0 ? html.substring(0, head) + script + html.substring(head) : script + html;
    }
  }
}

package sk.breviar.android;

import android.os.SystemClock;
import android.util.Log;
import java.util.concurrent.atomic.AtomicInteger;

/** Correlate background loading and UI delivery without logging user settings. */
final class LoadTiming {
  private static final AtomicInteger nextId = new AtomicInteger();
  private final String name;
  private final long started = SystemClock.elapsedRealtime();

  LoadTiming(String operation) {
    name = operation + " #" + nextId.incrementAndGet();
    mark("requested");
  }

  void mark(String stage) {
    Log.i("breviar", name + ": " + stage + " at +"
        + (SystemClock.elapsedRealtime() - started) + " ms ["
        + Thread.currentThread().getName() + "]");
  }
}

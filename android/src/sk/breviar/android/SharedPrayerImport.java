package sk.breviar.android;

import android.content.Context;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import java.util.concurrent.Future;
import java.util.function.Consumer;

/** Resolve local fonts asynchronously before atomically applying an incoming link. */
final class SharedPrayerImport {
  private static final String PENDING_URL = "shared.pending-url";
  private static final String PENDING_APPEARANCE = "shared.pending-appearance";

  static final class Ready {
    final UrlOptions link;
    final boolean appearance;
    final String fontCss; // null preserves the current font and its CSS.

    Ready(UrlOptions link, boolean appearance, String fontCss) {
      this.link = link;
      this.appearance = appearance;
      this.fontCss = fontCss;
    }
  }

  private final Context context;
  private final Handler ui = new Handler(Looper.getMainLooper());
  private Consumer<Ready> ready;
  private Future<?> fontLoad;
  private int generation;
  private String pendingUrl;
  private boolean pendingAppearance;

  SharedPrayerImport(Context context, Consumer<Ready> ready) {
    this.context = context.getApplicationContext();
    this.ready = ready;
  }

  boolean open(Uri uri, boolean appearance) {
    UrlOptions link = PrayerLink.read(uri, appearance);
    if (link == null) return false;
    cancel();
    final int request = generation;
    pendingUrl = link.build();
    pendingAppearance = appearance;
    String font = link.getFont();
    if (font == null || font.equals(new UrlOptions(BreviarApp.getUrlOptions(context)).getFont())) {
      deliver(request, link, appearance, null);
    } else if (Fonts.genericFamily(font)) {
      deliver(request, link, appearance, "");
    } else {
      fontLoad = Fonts.worker.submit(() -> {
        Fonts.Choice choice = null;
        try {
          choice = Fonts.findChoice(context, font);
        } catch (RuntimeException error) {
          Log.w("breviar", "Cannot resolve shared font", error);
        }
        final Fonts.Choice resolved = choice;
        ui.post(() -> {
          if (resolved == null) link.params.remove("f"); // Keep recipient's current font.
          else link.setFont(resolved.family);
          deliver(request, link, appearance, resolved == null ? null : resolved.css);
        });
      });
    }
    return true;
  }

  private void deliver(int request, UrlOptions link, boolean appearance, String fontCss) {
    if (request != generation || ready == null) return;
    pendingUrl = null;
    ready.accept(new Ready(link, appearance, fontCss));
  }

  void save(Bundle state) {
    state.putString(PENDING_URL, pendingUrl);
    state.putBoolean(PENDING_APPEARANCE, pendingAppearance);
  }

  boolean restore(Bundle state) {
    String url = state == null ? null : state.getString(PENDING_URL);
    return url != null && open(Uri.parse(url), state.getBoolean(PENDING_APPEARANCE));
  }

  void cancel() {
    ++generation;
    pendingUrl = null;
    if (fontLoad != null) fontLoad.cancel(false);
  }

  void close() {
    cancel();
    ready = null;
  }
}

package sk.breviar.android;

import android.content.ContentProvider;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.os.Build;
import android.util.Log;

/** Private synchronous IPC: grant the TTS process media access before it queues audio. */
public class DoNotDisturbProvider extends ContentProvider {
  static boolean reportSpeech(Context context, boolean speaking) {
    if (Build.VERSION.SDK_INT < 24) return true;
    try {
      Uri uri = Uri.parse("content://" + context.getPackageName() + ".dnd");
      return context.getContentResolver().call(uri, "speech", Boolean.toString(speaking), null) != null;
    } catch (IllegalArgumentException | IllegalStateException | SecurityException error) {
      Log.w("breviar", "Cannot update DND media allowance", error);
      return false;
    }
  }

  @Override public boolean onCreate() { return true; }

  @Override public Bundle call(String method, String argument, Bundle extras) {
    if (!"speech".equals(method)) throw new IllegalArgumentException("Unknown DND operation");
    DoNotDisturb.get(getContext()).setSpeaking(Boolean.parseBoolean(argument));
    return new Bundle();
  }

  @Override public Cursor query(Uri uri, String[] projection, String selection, String[] args, String sort) {
    throw new UnsupportedOperationException();
  }
  @Override public String getType(Uri uri) { return null; }
  @Override public Uri insert(Uri uri, ContentValues values) { throw new UnsupportedOperationException(); }
  @Override public int delete(Uri uri, String selection, String[] args) { throw new UnsupportedOperationException(); }
  @Override public int update(Uri uri, ContentValues values, String selection, String[] args) {
    throw new UnsupportedOperationException();
  }
}

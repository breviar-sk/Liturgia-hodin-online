package sk.breviar.android;

import static org.junit.Assert.*;

import android.app.ActivityManager;
import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.os.Looper;
import android.os.PowerManager;
import android.provider.Settings;
import android.widget.TextView;
import androidx.appcompat.app.AlertDialog;
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
import org.robolectric.shadows.ShadowToast;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = {28, 35}, shadows = XmlSettingsActivityTest.SettingsServer.class)
@LooperMode(LooperMode.Mode.PAUSED)
public class TtsBackgroundUsageTest {
  private final Context context = RuntimeEnvironment.getApplication();

  public static class Reader extends EinkModeTest.Reader {
    boolean settingsUnavailable;
    @Override public void startActivity(Intent intent) {
      if (settingsUnavailable && Settings.ACTION_APPLICATION_DETAILS_SETTINGS.equals(intent.getAction())) {
        throw new ActivityNotFoundException();
      }
      super.startActivity(intent);
    }
  }

  @Before public void skipStartupDialogs() {
    BreviarApp.setEinkMode(context, false);
    BreviarApp.setString(context, "version", context.getString(R.string.version));
  }

  private static void idle() { Shadows.shadowOf(Looper.getMainLooper()).idle(); }

  private static void restrict(Reader reader, boolean restricted) {
    ActivityManager manager = (ActivityManager)reader.getSystemService(Context.ACTIVITY_SERVICE);
    Shadows.shadowOf(manager).setBackgroundRestricted(restricted);
  }

  private static TtsBackgroundUsageWarning warning(Reader reader) {
    return (TtsBackgroundUsageWarning)reader.getSupportFragmentManager()
        .findFragmentByTag(TtsBackgroundUsageWarning.TAG);
  }

  private static AlertDialog dialog(Reader reader) {
    assertNotNull(warning(reader));
    AlertDialog dialog = (AlertDialog)warning(reader).requireDialog();
    assertTrue(dialog.isShowing());
    return dialog;
  }

  private static void click(Reader reader, int button) {
    dialog(reader).getButton(button).performClick();
    idle();
  }

  // The reader requests a status update on every start; that must not start playback.
  private static Intent nextPlayback(Reader reader) {
    Intent intent;
    while ((intent = Shadows.shadowOf(reader).getNextStartedService()) != null) {
      if (!TtsService.TTS_REQUEST_UPDATE.equals(intent.getAction())) return intent;
    }
    return null;
  }

  private static void assertPlayback(Reader reader, String action) {
    Intent intent = nextPlayback(reader);
    assertNotNull(intent);
    assertEquals(action, intent.getAction());
    assertEquals(TtsService.class.getName(), intent.getComponent().getClassName());
    assertNull(nextPlayback(reader));
  }

  @Test public void ordinaryBatteryOptimizationDoesNotPromptOrChangeSpeechRequest() {
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      Reader reader = controller.get();
      restrict(reader, false);
      PowerManager power = (PowerManager)reader.getSystemService(Context.POWER_SERVICE);
      Shadows.shadowOf(power).setIgnoringBatteryOptimizations(reader.getPackageName(), false);
      reader.wv.loadUrl("http://127.0.0.1:50000/l.cgi?qt=pdt&d=16&m=10&r=2026&p=1");
      reader.wv_title = "Prayer title";
      reader.language = "cs";
      Breviar.S.setOpts("&amp;f=Georgia&amp;k=sj");
      reader.startSpeaking();
      assertNull(warning(reader));
      Intent start = nextPlayback(reader);
      assertNotNull(start);
      assertEquals(TtsService.TTS_START, start.getAction());
      assertEquals("cs", start.getStringExtra("language"));
      assertEquals("Prayer title", start.getStringExtra("url_title"));
      UrlOptions options = new UrlOptions(start.getStringExtra("url"), true);
      assertTrue(options.isVoiceOutput());
      assertEquals("sj", options.params.get("k"));
      assertEquals("Georgia", options.params.get("f"));
      assertEquals("16", options.params.get("d"));
      assertEquals("1", options.params.get("p"));
      assertTrue(start.getStringExtra("url").startsWith("http://127.0.0.1:50001/"));
      assertNull(nextPlayback(reader));
      reader.resumeSpeaking();
      assertNull(warning(reader));
      assertPlayback(reader, TtsService.TTS_RESUME);
    }
  }

  @Test public void restrictedStartWaitsForUserAndRepeatedTapsShowOnlyOneWarning() {
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      Reader reader = controller.get();
      restrict(reader, true);
      reader.startSpeaking();
      AlertDialog original = dialog(reader);
      reader.startSpeaking();
      assertSame(original, dialog(reader));
      assertNull(nextPlayback(reader));
      click(reader, AlertDialog.BUTTON_NEGATIVE);
      assertNull(warning(reader));
      assertNull(nextPlayback(reader));
      reader.startSpeaking();
      dialog(reader).cancel();
      idle();
      assertNull(warning(reader));
      assertNull(nextPlayback(reader));
    }
  }

  @Test public void readAnywayBypassesOnlyThisAttempt() {
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      Reader reader = controller.get();
      restrict(reader, true);
      reader.startSpeaking();
      click(reader, AlertDialog.BUTTON_NEUTRAL);
      assertNull(warning(reader));
      assertPlayback(reader, TtsService.TTS_START);
      reader.startSpeaking();
      dialog(reader);
      assertNull(nextPlayback(reader));
    }
  }

  @Test public void resumeWarningSurvivesRecreationAndResumesInsteadOfRestarting() {
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      Reader reader = controller.get();
      restrict(reader, true);
      reader.resumeSpeaking();
      dialog(reader);
      assertNull(nextPlayback(reader));
      controller.recreate();
      idle();
      reader = controller.get();
      click(reader, AlertDialog.BUTTON_NEUTRAL);
      assertNull(warning(reader));
      assertPlayback(reader, TtsService.TTS_RESUME);
    }
  }

  @Test public void opensAppInfoAndRechecksRestrictionOnTheNextAttempt() {
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      Reader reader = controller.get();
      restrict(reader, true);
      reader.startSpeaking();
      click(reader, AlertDialog.BUTTON_POSITIVE);
      assertNull(warning(reader));
      Intent settings = Shadows.shadowOf(reader).getNextStartedActivity();
      assertNotNull(settings);
      assertEquals(Settings.ACTION_APPLICATION_DETAILS_SETTINGS, settings.getAction());
      assertEquals("package:" + reader.getPackageName(), settings.getDataString());
      assertNull(nextPlayback(reader));
      controller.pause().stop().restart().start().resume();
      assertNull(nextPlayback(reader));
      // Merely visiting Settings does not mean the user granted background usage.
      reader.startSpeaking();
      dialog(reader);
      assertNull(nextPlayback(reader));
      click(reader, AlertDialog.BUTTON_NEGATIVE);
      restrict(reader, false);
      reader.startSpeaking();
      assertNull(warning(reader));
      assertPlayback(reader, TtsService.TTS_START);
      // Do not cache the successful check either.
      restrict(reader, true);
      reader.resumeSpeaking();
      dialog(reader);
      assertNull(nextPlayback(reader));
    }
  }

  @Test public void missingSettingsActivityShowsManualInstructionsWithoutStartingSpeech() {
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      Reader reader = controller.get();
      restrict(reader, true);
      reader.settingsUnavailable = true;
      reader.startSpeaking();
      click(reader, AlertDialog.BUTTON_POSITIVE);
      assertEquals(reader.getString(R.string.tts_background_settings_unavailable),
          ShadowToast.getTextOfLatestToast());
      assertNull(nextPlayback(reader));
      assertNull(warning(reader));
    }
  }

  @Test public void warningUsesTheEinkDialogTheme() {
    BreviarApp.setEinkMode(context, true);
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      Reader reader = controller.get();
      restrict(reader, true);
      reader.startSpeaking();
      AlertDialog dialog = dialog(reader);
      assertEquals(Color.BLACK, ((TextView)dialog.findViewById(android.R.id.message)).getCurrentTextColor());
      assertEquals(Color.BLACK, dialog.getButton(AlertDialog.BUTTON_POSITIVE).getCurrentTextColor());
    }
  }

  @Test @Config(sdk = {24, 27})
  public void olderAndroidKeepsExistingPlaybackWithoutCallingNewApi() {
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      Reader reader = controller.get();
      restrict(reader, true);
      reader.startSpeaking();
      assertNull(warning(reader));
      assertPlayback(reader, TtsService.TTS_START);
      reader.resumeSpeaking();
      assertPlayback(reader, TtsService.TTS_RESUME);
    }
  }
}

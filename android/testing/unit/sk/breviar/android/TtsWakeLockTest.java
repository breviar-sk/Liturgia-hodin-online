package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
import android.content.Intent;
import android.media.AudioManager;
import android.os.PowerManager;
import android.speech.tts.TextToSpeech;
import android.speech.tts.UtteranceProgressListener;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Locale;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.Shadows;
import org.robolectric.android.controller.ServiceController;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.Implementation;
import org.robolectric.annotation.Implements;
import org.robolectric.annotation.LooperMode;
import org.robolectric.shadow.api.Shadow;
import org.robolectric.shadows.ShadowPowerManager;
import org.robolectric.shadows.ShadowTextToSpeech;
import org.robolectric.util.ReflectionHelpers;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = {24, 35}, shadows = {TtsWakeLockTest.PrayerText.class, TtsWakeLockTest.Speech.class})
@LooperMode(LooperMode.Mode.PAUSED)
public class TtsWakeLockTest {
  // Supply prayer text without a WebView/JNI server; exercise the real service state machine.
  @Implements(value = HeadlessWebview.class, isInAndroidSdk = false)
  public static class PrayerText {
    HeadlessWebview.Callback callback;
    @Implementation protected void __constructor__(Context context, String process) {}
    @Implementation protected void LoadAndExecute(String url, String script, HeadlessWebview.Callback callback) {
      this.callback = callback;
    }
  }

  @Implements(TextToSpeech.class)
  public static class Speech extends ShadowTextToSpeech {
    final ArrayList<String> queued = new ArrayList<>();
    int next;
    int silences;
    boolean rejectSpeech, rejectSilence, throwOnQueue;

    private int enqueue(boolean silence, HashMap<String, String> params) {
      PowerManager.WakeLock lock = ShadowPowerManager.getLatestWakeLock();
      assertNotNull("Acquire before handing work to the engine", lock);
      assertTrue(lock.isHeld());
      if (throwOnQueue) throw new IllegalStateException("Engine unavailable");
      if (silence ? rejectSilence : rejectSpeech) return TextToSpeech.ERROR;
      queued.add(params.get(TextToSpeech.Engine.KEY_PARAM_UTTERANCE_ID));
      return TextToSpeech.SUCCESS;
    }

    @Override @Implementation
    protected int speak(String text, int mode, HashMap<String, String> params) {
      return enqueue(false, params);
    }

    @Implementation protected int playSilence(long duration, int mode, HashMap<String, String> params) {
      if (duration > 0) ++silences;
      return enqueue(true, params);
    }

    void completeNext() {
      String id = queued.get(next++);
      getUtteranceProgressListener().onStart(id);
      getUtteranceProgressListener().onDone(id);
    }
  }

  private ServiceController<TtsService> controller;
  private TtsService service;
  private Speech speech;

  @Before public void createService() {
    ShadowTextToSpeech.addLanguageAvailability(Locale.forLanguageTag("sk"));
    controller = Robolectric.buildService(TtsService.class).create();
    service = controller.get();
    BreviarApp.setTtsUsePauseInPsalms(service, true);
  }

  @After public void destroyService() {
    if (controller != null) controller.destroy();
  }

  private void begin() {
    service.onStartCommand(new Intent(TtsService.TTS_START)
        .putExtra("url", "http://127.0.0.1:50001/l.cgi?qt=pdt")
        .putExtra("language", "sk"), 0, 1);
    speech = Shadow.extract(service.tts);
    assertEquals(TtsService.State.INITIALIZING_TTS, service.state);
  }

  private void initialize() {
    begin();
    speech.getOnInitListener().onInit(TextToSpeech.SUCCESS);
    assertEquals(TtsService.State.GETTING_TEXT, service.state);
  }

  private void load(String... sections) {
    PrayerText text = Shadow.extract(service.headless);
    text.callback.run(sections);
  }

  private void action(String action) { service.onStartCommand(new Intent(action), 0, 1); }

  private void assertReleased() {
    PowerManager.WakeLock lock = ShadowPowerManager.getLatestWakeLock();
    assertTrue(lock == null || !lock.isHeld());
  }

  @Test public void holdsPartialLockAcrossSilencesAndSectionsUntilCompletion() {
    initialize();
    assertReleased();
    PowerManager power = (PowerManager)service.getSystemService(Context.POWER_SERVICE);
    Shadows.shadowOf(power).setIsInteractive(false);
    load("First#TTS_PAUSE_SHORTSecond#TTS_PAUSE_LONGThird#TTS_PAUSE_DIV", "Last");
    assertEquals(3, speech.silences);
    PowerManager.WakeLock lock = ShadowPowerManager.getLatestWakeLock();
    assertEquals(PowerManager.PARTIAL_WAKE_LOCK, (int)ReflectionHelpers.getField(lock, "mFlags"));
    assertFalse(Shadows.shadowOf(lock).isReferenceCounted());
    assertFalse(power.isInteractive());
    while (service.state == TtsService.State.PLAYING) {
      assertTrue("Keep awake while awaiting every speech/silence callback", lock.isHeld());
      speech.completeNext();
    }
    assertEquals(TtsService.State.IDLE, service.state);
    assertTrue(speech.isShutdown());
    assertReleased();
  }

  @Test public void pauseReleasesAndLateCompletionDoesNotStartAnotherSection() {
    initialize();
    load("First", "Second");
    action(TtsService.TTS_PAUSE);
    assertEquals(TtsService.State.PAUSED, service.state);
    assertReleased();
    speech.completeNext(); // The last callback was already in flight when pause was pressed.
    assertEquals(TtsService.State.PAUSED, service.state);
    assertEquals(1, speech.queued.size());
    assertReleased();
    action(TtsService.TTS_RESUME);
    assertEquals(TtsService.State.PLAYING, service.state);
    assertTrue(ShadowPowerManager.getLatestWakeLock().isHeld());
    assertEquals(2, speech.queued.size());
    action(TtsService.TTS_STOP);
    assertReleased();
  }

  @Test public void audioFocusLossReleasesAndGainReacquires() {
    initialize();
    load("First#TTS_PAUSE_LONGSecond");
    service.onAudioFocusChange(AudioManager.AUDIOFOCUS_LOSS_TRANSIENT);
    assertEquals(TtsService.State.PAUSED, service.state);
    assertReleased();
    service.onAudioFocusChange(AudioManager.AUDIOFOCUS_GAIN);
    assertEquals(TtsService.State.PLAYING, service.state);
    assertTrue(ShadowPowerManager.getLatestWakeLock().isHeld());
    action(TtsService.TTS_STOP);
    assertEquals(TtsService.State.IDLE, service.state);
    assertReleased();
  }

  @Test public void deniedAudioFocusDoesNotAcquire() {
    initialize();
    AudioManager audio = (AudioManager)service.getSystemService(Context.AUDIO_SERVICE);
    Shadows.shadowOf(audio).setNextFocusRequestResponse(AudioManager.AUDIOFOCUS_REQUEST_FAILED);
    load("First");
    assertEquals(TtsService.State.PAUSED, service.state);
    assertTrue(speech.queued.isEmpty());
    assertReleased();
  }

  @Test public void nextAndPreviousSectionsDoNotAccumulateLockAcquisitions() {
    initialize();
    load("First", "Second");
    PowerManager.WakeLock lock = ShadowPowerManager.getLatestWakeLock();
    action(TtsService.TTS_FORWARD);
    action(TtsService.TTS_BACK);
    assertTrue(lock.isHeld());
    assertEquals(1, Shadows.shadowOf(lock).getTimesHeld());
    action(TtsService.TTS_STOP);
    assertReleased();
  }

  @Test public void synthesisErrorReleases() {
    initialize();
    load("First");
    speech.getUtteranceProgressListener().onError(speech.queued.get(0));
    assertEquals(TtsService.State.IDLE, service.state);
    assertTrue(speech.isShutdown());
    assertReleased();
  }

  @Test public void rejectedSpeechDoesNotWaitForeverForAnErrorCallback() {
    initialize();
    speech.rejectSpeech = true;
    load("First");
    assertEquals(TtsService.State.IDLE, service.state);
    assertTrue(speech.isShutdown());
    assertReleased();
  }

  @Test public void rejectedSilenceStopsAlreadyQueuedSpeechAndReleases() {
    initialize();
    speech.rejectSilence = true;
    load("First#TTS_PAUSE_LONGSecond");
    assertEquals(1, speech.queued.size());
    assertEquals(TtsService.State.IDLE, service.state);
    assertTrue(speech.isStopped());
    assertTrue(speech.isShutdown());
    assertReleased();
  }

  @Test public void unexpectedEngineExceptionDoesNotLeakLock() {
    initialize();
    speech.throwOnQueue = true;
    assertThrows(IllegalStateException.class, () -> load("First"));
    assertReleased();
  }

  @Test public void initializationFailureAndIdleStatusRequestsDoNotAcquire() {
    action(TtsService.TTS_REQUEST_UPDATE);
    assertReleased();
    begin();
    assertReleased();
    speech.getOnInitListener().onInit(TextToSpeech.ERROR);
    assertEquals(TtsService.State.IDLE, service.state);
    assertReleased();
  }

  @Test public void destructionStopsSpeechAndLateCallbacksCannotReacquire() {
    initialize();
    load("First", "Second");
    UtteranceProgressListener listener = speech.getUtteranceProgressListener();
    controller.destroy();
    controller = null;
    assertTrue(speech.isStopped());
    assertTrue(speech.isShutdown());
    assertReleased();
    listener.onDone(speech.queued.get(0));
    service.onAudioFocusChange(AudioManager.AUDIOFOCUS_GAIN);
    speech.getOnInitListener().onInit(TextToSpeech.SUCCESS);
    assertEquals(TtsService.State.IDLE, service.state);
    assertEquals(1, speech.queued.size());
    assertReleased();
  }
}

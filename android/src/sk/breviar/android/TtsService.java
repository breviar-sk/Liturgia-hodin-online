package sk.breviar.android;

import androidx.core.app.NotificationCompat;
import androidx.media.app.NotificationCompat.MediaStyle;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.media.AudioManager;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.speech.tts.TextToSpeech;
import android.speech.tts.UtteranceProgressListener;
import android.util.Log;
import android.widget.Toast;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.HashMap;
import java.util.Vector;

import sk.breviar.android.BreviarApp;

// TODO: handle exceptions.

public class TtsService extends Service
                        implements TextToSpeech.OnInitListener,
                                   AudioManager.OnAudioFocusChangeListener {
  // Public commands:
  // Contains TtsState `state` as serializable extra.
  public static final String TTS_UPDATE_ACTION = "sk.breviar.android.action.TTS_UPDATE";

  // No extras included, just a request to broadcast the current state.
  public static final String TTS_REQUEST_UPDATE = "sk.breviar.android.action.TTS_REQUEST_UPDATE";

  // Included extra string `url`.
  public static final String TTS_START = "sk.breviar.android.action.TTS_START";

  // No extras.
  public static final String TTS_STOP = "sk.breviar.android.action.TTS_STOP";

  // No extras.
  public static final String TTS_PAUSE = "sk.breviar.android.action.TTS_PAUSE";
  public static final String TTS_AUDIOFOCUS_LOSS = "sk.breviar.android.action.TTS_AUDIOFOCUS_LOSS";

  // No extras.
  public static final String TTS_RESUME = "sk.breviar.android.action.TTS_RESUME";
  public static final String TTS_AUDIOFOCUS_GAIN = "sk.breviar.android.action.TTS_AUDIOFOCUS_GAIN";

  // No extras.
  public static final String TTS_FORWARD = "sk.breviar.android.action.TTS_FORWARD";

  // No extras.
  public static final String TTS_BACK = "sk.breviar.android.action.TTS_BACK";

  // Publicly visible state.
  public enum TtsState {
    READY,
    SPEAKING,
    PAUSED
  }

  // Internal commands.
  static final String TTS_INIT_DONE = "TTS_INIT_DONE";
  static final String TTS_INIT_FAILED = "TTS_INIT_FAILED";
  static final String GOT_TEXT = "GOT_TEXT";
  static final String SYNTHESIS_DONE = "SYNTHESIS_DONE";
  static final String SYNTHESIS_ERROR = "SYNTHESIS_ERROR";
  static final String IDLE_PROCESSING = "IDLE_PROCESSING";

  // Internal state.
  enum State {
    IDLE,
    INITIALIZING_TTS,
    GETTING_TEXT,
    START_SECTION,
    PLAYING,
    PAUSED,
    PAUSING,
    REJECT
  }
  State state = State.IDLE;

  TtsState publicState() {
    if (state == State.IDLE) return TtsState.READY;
    if (state == State.PAUSED) return TtsState.PAUSED;
    return TtsState.SPEAKING;
  }

  void displayError() {
    final Context parent = this;
    Handler handler = new Handler(getMainLooper());
    handler.post(new Runnable() {
      public void run() {
        CharSequence message = BreviarApp.getContextForCustomLocale(parent)
            .getResources().getText(R.string.tts_language_not_available);
        Toast.makeText(parent, message, Toast.LENGTH_LONG).show();
      }
    });
  }

  synchronized void processAction(Intent immediate_action) {
    TtsState old_public_state = publicState();

    while (true) {
      Log.v("breviar", "TTS in state " + state.name());
      State new_state;
      if (immediate_action != null) {
        Log.v("breviar", "Immediate action " + immediate_action.getAction());
        new_state = delta(immediate_action);
        Log.v("breviar", "New state = " + new_state.name());
        if (new_state != State.REJECT) {
          state = new_state;
          immediate_action = null;
          continue;
        } else {
          // This is an error, but we have no better option than to ignore the action.
          Log.v("breviar", "Error in FA: state " + state.name() +
                           " rejected immediate action " +
                           immediate_action.getAction());
          immediate_action = null;
        }
      }

      if (pending_action != null) {
        Log.v("breviar", "Pending action " + pending_action.getAction());
        new_state = delta(pending_action);
        Log.v("breviar", "New state = " + new_state.name());
        if (new_state != State.REJECT) {
          state = new_state;
          pending_action = null;
          continue;
        }
      }

      Log.v("breviar", "Idle processing");
      new_state = delta(new Intent(IDLE_PROCESSING));
      Log.v("breviar", "New state = " + new_state.name());
      if (new_state != State.REJECT) {
        state = new_state;
        continue;
      }
      break;
    }

    TtsState new_public_state = publicState();
    if (new_public_state != old_public_state) {
      broadcastUpdate();

      // TODO(riso): Android 5.1 crashes due to notifications in the following
      // code. I do not know what is missing there; it is not reproducible in
      // emulator and other versions of Android work well.
      if (Build.VERSION.SDK_INT != Build.VERSION_CODES.LOLLIPOP_MR1) {
        if (new_public_state == TtsState.READY) {
          stopForeground(true);
        } else {
          String title;
          if (url_title == null) {
            title = getString(R.string.channel_name);
          } else {
            title = url_title;
          }

          int icon;
          if (Build.VERSION.SDK_INT < Build.VERSION_CODES.LOLLIPOP) {
            icon = R.drawable.icon;
          } else {
            icon = R.drawable.icon_transparent;
          }

          PendingIntent open_activity = PendingIntent.getActivity(this, 0,
            new Intent("sk.breviar.android.action.SHOW"), PendingIntent.FLAG_UPDATE_CURRENT | PendingIntent.FLAG_IMMUTABLE);

          PendingIntent stop = PendingIntent.getService(this, 0,
              new Intent().setClass(this, TtsService.class)
                          .setAction(TtsService.TTS_STOP),  PendingIntent.FLAG_IMMUTABLE);

          PendingIntent forward = PendingIntent.getService(this, 0,
              new Intent().setClass(this, TtsService.class)
                          .setAction(TtsService.TTS_FORWARD), PendingIntent.FLAG_IMMUTABLE);

          PendingIntent back = PendingIntent.getService(this, 0,
              new Intent().setClass(this, TtsService.class)
                          .setAction(TtsService.TTS_BACK), PendingIntent.FLAG_IMMUTABLE);

          if (Build.VERSION.SDK_INT >= 26) {
            CompatibilityHelper26.updateChannel(this);
          }

          int priority;
          if (Build.VERSION.SDK_INT < Build.VERSION_CODES.LOLLIPOP) {
            priority = NotificationCompat.PRIORITY_LOW;
          } else {
            priority = NotificationCompat.PRIORITY_HIGH;
          }

          NotificationCompat.Builder builder = new NotificationCompat.Builder(this, "tts")
                .setContentText(getString(R.string.channel_name))
                .setContentTitle(title)
                .setSmallIcon(icon)
                .setContentIntent(open_activity)
                .setColor(getResources().getColor(R.color.colorPrimary))
                .setPriority(priority)
                .setOnlyAlertOnce(true)
                .setStyle(new MediaStyle().setShowActionsInCompactView(0, 2, 3));

          if (new_public_state == TtsState.SPEAKING) {
            PendingIntent pause = PendingIntent.getService(this, 0,
                new Intent().setClass(this, TtsService.class)
                            .setAction(TtsService.TTS_PAUSE), PendingIntent.FLAG_IMMUTABLE);
            builder.addAction(R.drawable.ic_pause_white_24dp, getString(R.string.tts_pause), pause);
          } else {
            PendingIntent resume = PendingIntent.getService(this, 0,
                new Intent().setClass(this, TtsService.class)
                            .setAction(TtsService.TTS_RESUME), PendingIntent.FLAG_IMMUTABLE);
            builder.addAction(R.drawable.ic_play_arrow_white_24dp, getString(R.string.tts_resume), resume);
          }

          builder.addAction(R.drawable.ic_volume_off_white_24dp, getString(R.string.tts_speaking), stop)
                 .addAction(R.drawable.ic_fast_rewind_white_24dp, getString(R.string.tts_back), back)
                 .addAction(R.drawable.ic_fast_forward_white_24dp, getString(R.string.tts_forward), forward)
                 .setDefaults(Notification.DEFAULT_SOUND | Notification.DEFAULT_LIGHTS)
                 .setVibrate(new long[]{0l, 0l});

          if (old_public_state == TtsState.READY) {
            if (Build.VERSION.SDK_INT < 29) {
              startForegroundOld(builder.build());
            } else {
              startForegroundNew(builder.build());
            }
          } else {
            ((NotificationManager)getSystemService(NOTIFICATION_SERVICE)).notify(
                BreviarApp.NOTIFY_TTS_ID, builder.build());
          }
        }
      }
    }
  }

  void startForegroundOld(Notification n) {
    startForeground(BreviarApp.NOTIFY_TTS_ID, n);
  }

  void startForegroundNew(Notification n) {
    startForeground(BreviarApp.NOTIFY_TTS_ID, n,
        android.content.pm.ServiceInfo.FOREGROUND_SERVICE_TYPE_MEDIA_PLAYBACK);
  }

  void broadcastUpdate() {
    Log.v("breviar", "TtsService: sending broadcast");
    sendBroadcast(new Intent(TTS_UPDATE_ACTION)
        .setPackage(getPackageName())
        .putExtra("state", publicState()));
  }

  // Bridge from provided interfaces.

  @Override
  public void onStart(Intent intent, int startId) {
    onStartCommand(intent, -1, -1);
  }

  @Override
  public int onStartCommand(Intent intent, int flags, int startId) {
    if (headless == null) {
      headless = new HeadlessWebview(getApplicationContext(), "tts_service");
    }

    // Log.v("breviar", "TtsService: got intent");
    if (intent != null) {
      String action = intent.getAction();
      if (action != null) {
        if (action == TTS_REQUEST_UPDATE) {
          broadcastUpdate();
        } else {
          pending_action = intent;
          processAction(null);
        }
      }
    }
    return START_STICKY;
  }

  @Override
  public void onInit(int status) {
    if (status == TextToSpeech.SUCCESS) {
      processAction(new Intent(TTS_INIT_DONE));
    } else {
      processAction(new Intent(TTS_INIT_FAILED));
    }
  }

  Intent pending_action = null;        // pending action from clients.

  // State variables:

  // `headless` is not null whenever the service is running.
  HeadlessWebview headless = null;

  // Objects below are valid <=> not null.
  String url = null;                   // valid <=> internal_state > IDLE
  String url_title = null;             // valid <=> internal_state > IDLE
  String language = null;              // valid <=> internal_state > IDLE
  TextToSpeech tts = null;             // valid <=> internal_state > IDLE
  String[] sections = null;            // valid <=> internal_state > GETTING_TEXT
  int section;                         // valid <=> internal_state > GETTING_TEXT
  Vector<String> chunks = null;        // valid <=> internal_state > START_SECTION
  int chunk;                           // valid <=> internal_state > START_SECTION

  // Transition function:

  State delta(Intent action) {
    switch (state) {
      case IDLE:
        switch (action.getAction()) {
          case TTS_START:
            url = action.getStringExtra("url");
            url_title = action.getStringExtra("url_title");
            language = action.getStringExtra("language");
            if (url != null) {
              tts = new TextToSpeech(this, this);
              return State.INITIALIZING_TTS;
            } else {
              url = null;
              url_title = null;
              language = null;
              return State.IDLE;
            }
          default:
            return State.REJECT;
        }

      case INITIALIZING_TTS:
        switch (action.getAction()) {
          case TTS_INIT_DONE:
            if (requestText()) {
              return State.GETTING_TEXT;
            }
            // if language is not supported, fallthrough to init failed.

          case TTS_INIT_FAILED:
            Log.v("breviar", "TTS init failed");
            tts = null;
            language = null;
            url = null;
            url_title = null;
            return State.IDLE;

          default:
            return State.REJECT;
        }

      case GETTING_TEXT:
        switch (action.getAction()) {
          case GOT_TEXT:
            // sections and section were initialized in HeadlessWebview
            // callback
            return state.START_SECTION;
          default:
            return State.REJECT;
        }

      case START_SECTION:
        switch (action.getAction()) {
          case TTS_STOP:
            sections = null;
            shutdownTts();
            language = null;
            url = null;
            url_title = null;
            return State.IDLE;

          case TTS_FORWARD:
            if (section < sections.length - 1) {
              ++section;
            }
            return State.START_SECTION;

          case TTS_BACK:
            if (section > 0) {
              --section;
            }
            return State.START_SECTION;

          case IDLE_PROCESSING:
            while (section < sections.length &&
                   sections[section].length() == 0) {
              ++section;
            }
            if (section >= sections.length) {
              sections = null;
              shutdownTts();
              url = null;
              url_title = null;
              language = null;
              return State.IDLE;
            }
            initializeChunks();
            return startSynthesis(IDLE_PROCESSING);

          default:
            return State.REJECT;
        }

      case PLAYING:
      case PAUSED:
        switch (action.getAction()) {
          case SYNTHESIS_DONE:
            ++chunk;
            return state;

          case IDLE_PROCESSING:
            if (chunk >= chunks.size()) {
              chunks = null;
              ++section;
              return State.START_SECTION;
            }
            return State.REJECT;

          case SYNTHESIS_ERROR:
            Log.v("breviar", "Synthesis error, displaying toast");
            displayError();
          case TTS_STOP:
            if (state == State.PLAYING) stopSynthesis(TTS_STOP);
            chunks = null;
            sections = null;
            shutdownTts();
            language = null;
            url = null;
            url_title = null;
            return State.IDLE;

          case TTS_PAUSE:
          case TTS_AUDIOFOCUS_LOSS:
            if (state == State.PLAYING) {
              stopSynthesis(action.getAction());
              return State.PAUSED;
            } else {
              return State.REJECT;
            }

          case TTS_RESUME:
          case TTS_AUDIOFOCUS_GAIN:
            if (state == State.PAUSED) {
              return startSynthesis(action.getAction());
            } else {
              return State.REJECT;
            }

          case TTS_FORWARD:
          case TTS_BACK:
            if (action.getAction() == TTS_FORWARD) {
              if (section >= sections.length) {
                return State.REJECT;
              }
              ++section;
            } else {
              if (section <= 0) {
                return State.REJECT;
              }
              --section;
            }
            if (state == State.PLAYING) stopSynthesis(action.getAction());
            chunks = null;
            return State.START_SECTION;

          default:
            return State.REJECT;
        }

      default:
        Log.v("breviar", "Error in FA: delta undefined for " + state.name());
        return State.REJECT;
    }
  }

  void shutdownTts() {
    try {
      tts.shutdown();
    } catch (java.lang.IllegalArgumentException e) {
      Log.v("breviar", "TTS shutdow failed, ignoring.");
    }
    tts = null;
  }

  boolean requestText() {
    int ret = tts.setLanguage(BreviarApp.appLanguageToLocale(language));
    Log.v("breviar", "setTTSLanguage: " + ret);
    if (ret == TextToSpeech.LANG_NOT_SUPPORTED ||
        ret == TextToSpeech.LANG_MISSING_DATA) {
      displayError();
      return false;
    }

    tts.setOnUtteranceProgressListener(new UtteranceProgressListener() {
      @Override
      public void onDone(String utteranceId) {
        processAction(new Intent(SYNTHESIS_DONE));
      }
      @Override
      public void onError(String utteranceId) {
        processAction(new Intent(SYNTHESIS_ERROR));
      }
      @Override
      public void onStart(String utteranceId) {}
    });

    Log.v("breviar", "Loading nonpersistent url " + url);
    headless.LoadAndExecute(url,
        "function getText(node, sections) {" +
        "  if (node.nodeType == Node.TEXT_NODE) {" +
        "    sections[sections.length - 1] += node.textContent;" +
        "    return !(node.textContent === '');" +
        "  }" +
        "  if (node.nodeType != Node.ELEMENT_NODE) {" +
        "    return false;" +
        "  }" +
        "  if (node.className == 'tts_pause') {" +
        "    sections[sections.length - 1] += '#TTS_PAUSE_LONG';" +
        "    return false;" +
        "  }" +
        "  if (node.className == 'tts_pause_short') {" +
        "    sections[sections.length - 1] += '#TTS_PAUSE_SHORT';" +
        "    return false;" +
        "  }" +
        "  if (node.className == 'tts_section') {" +
        "    sections.push(\"\");" +
        "  }" +
        "  if (window.getComputedStyle(node).display == 'none') {" +
        "    return false;" +
        "  }" +
        "  var nonempty = false; " +
        "  for (var i = 0; i < node.childNodes.length; ++i) {" +
        "    if (getText(node.childNodes[i], sections)) { nonempty = true; } " +
        "  }" +
        "  if (nonempty && (node.tagName === 'DIV')) {" +
        "    sections[sections.length - 1] += '#TTS_PAUSE_DIV';" +
        "  }" +
        "  return nonempty; " +
        "}" +
        "" +
        "function prune(sections) {" +
        "  var pruned = [];" +
        "  for (var i = 0; i < sections.length; ++i) {" +
        "    sections[i] = sections[i].trim();" +
        "    if (sections[i] != \"\") {" +
        "      pruned.push(sections[i]);" +
        "    }" +
        "  }" +
        "  return pruned;" +
        "}" +
        "" +
        "var sections = [\"\"];" +
        "getText(document.getElementById(\"contentRoot\"), sections);" +
        "bridge.callback(prune(sections));",
        new HeadlessWebview.Callback() {
          public void run(String[] result) {
            // Log.v("breviar", "Got callback result");
            for (int i = 0; i < result.length; ++i) {
              result[i] = result[i].replace('\n', ' ').trim();
            }
            sections = result;
            section = 0;
            processAction(new Intent(GOT_TEXT));
          }
        });
    return true;
  }

  void initializeChunks() {
    chunks = new Vector<String>();
    int pos = 0;
    while (pos < sections[section].length()) {
      int new_pos = findTtsSplit(sections[section], pos);
      chunks.add(sections[section].substring(pos, new_pos).trim());
      pos = new_pos;
    }
    chunk = 0;
  }

  void stopSynthesis(String action) {
    if (!action.equals(TTS_AUDIOFOCUS_LOSS)) {
      AudioManager audio_manager = (AudioManager)getSystemService(AUDIO_SERVICE);
      if (audio_manager != null) {
        audio_manager.abandonAudioFocus(this);
      }
    }
    tts.stop();
    Log.v("breviar", "TTS: stopped synthesis");
  }

  @Override
  public void onAudioFocusChange(int focusChange) {
    if (focusChange == AudioManager.AUDIOFOCUS_GAIN) {
      processAction(new Intent(TTS_AUDIOFOCUS_GAIN));
    } else {
      processAction(new Intent(TTS_AUDIOFOCUS_LOSS));
    }
  }

  State startSynthesis(String action) {
    if (!action.equals(TTS_AUDIOFOCUS_GAIN)) {
      AudioManager audio_manager = (AudioManager)getSystemService(AUDIO_SERVICE);
      if (audio_manager == null) {
        Log.v("breviar", "TTS: cannot get audio manager");
      } else {
        if (audio_manager.requestAudioFocus(this, AudioManager.STREAM_MUSIC,
                                            AudioManager.AUDIOFOCUS_GAIN) !=
            AudioManager.AUDIOFOCUS_REQUEST_GRANTED) {
          return State.PAUSED;
        };
      }
    }

    boolean use_pauses = BreviarApp.getTtsUsePauseInPsalms(this);
    for (int i = chunk; i < chunks.size(); ++i) {
      HashMap<String, String> params = new HashMap<String, String>();
      params.put(TextToSpeech.Engine.KEY_PARAM_UTTERANCE_ID,
          "s" + new java.lang.Integer(section).toString() + "ch" + new java.lang.Integer(i).toString());

      String chunk_text = chunks.elementAt(i);
      Log.v("breviar", "TTS chunk: " + chunk_text);
      if (chunk_text.equals("#TTS_PAUSE_DIV")) {
        tts.playSilence(200, TextToSpeech.QUEUE_ADD, params);
      } else if (chunk_text.equals("#TTS_PAUSE_SHORT")) {
        int pause = 0;
        if (use_pauses) {
          pause = 200;
        }
        tts.playSilence(pause, TextToSpeech.QUEUE_ADD, params);
      } else if (chunk_text.equals("#TTS_PAUSE_LONG")) {
        int pause = 0;
        if (use_pauses) {
          pause = 1000;
        }
        tts.playSilence(pause, TextToSpeech.QUEUE_ADD, params);
      } else {
        tts.speak(chunks.elementAt(i), TextToSpeech.QUEUE_ADD, params);
      }
    }
    return State.PLAYING;
  }

  int findTtsSplit(String chunk, int pos) {
    int i = pos;
    while (i < chunk.length() && Character.isWhitespace(chunk.charAt(i))) {
      ++i;
    }
    if (chunk.startsWith("#TTS_PAUSE_DIV", i)) {
      return i + 14;
    }
    if (chunk.startsWith("#TTS_PAUSE_SHORT", i)) {
      return i + 16;
    }
    if (chunk.startsWith("#TTS_PAUSE_LONG", i)) {
      return i + 15;
    }

    for (; i < chunk.length(); ++i) {
      if (chunk.startsWith("#TTS_PAUSE", i)) {
        return i;
      }
      if (chunk.charAt(i) == '.' || chunk.charAt(i) == '!' ||
          chunk.charAt(i) == '?' || chunk.charAt(i) == ':' ||
          chunk.charAt(i) == ';') {
        if (i == chunk.length() - 1) {
          return i + 1;
        } else if (Character.isWhitespace(chunk.charAt(i + 1))) {
          return i + 2;
        }
      }
    }
    return chunk.length();
  }

  @Override
  public IBinder onBind(Intent in) {
    return null;
  }
}

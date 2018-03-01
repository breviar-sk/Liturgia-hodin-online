package sk.breviar.android;

import android.support.v4.app.NotificationCompat;
import android.support.v4.media.app.NotificationCompat.MediaStyle;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.os.Build;
import android.os.IBinder;
import android.speech.tts.TextToSpeech;
import android.util.Log;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.HashMap;
import java.util.Vector;

import sk.breviar.android.BreviarApp;

// TODO: handle exceptions.

public class TtsService extends Service
                        implements MediaPlayer.OnCompletionListener,
                                   TextToSpeech.OnInitListener,
                                   TextToSpeech.OnUtteranceCompletedListener {
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

  // No extras.
  public static final String TTS_RESUME = "sk.breviar.android.action.TTS_RESUME";

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
  static final String PLAY_DONE = "PLAY_DONE";
  static final String IDLE_PROCESSING = "IDLE_PROCESSING";

  // Internal state.
  enum State {
    IDLE,
    INITIALIZING_TTS,
    GETTING_TEXT,
    START_SECTION,
    SYNTHESIZING,
    SYNTHESIZING_AND_PLAYING,
    PLAYING,
    SYNTHESIZING_AND_PAUSED,
    PAUSED,
    PAUSED_AFTER_COMPLETED,
    REJECT
  }
  State state = State.IDLE;

  TtsState publicState() {
    if (state == State.IDLE) return TtsState.READY;
    if (state == State.PAUSED) return TtsState.PAUSED;
    if (state == State.SYNTHESIZING_AND_PAUSED) return TtsState.PAUSED;
    if (state == State.PAUSED_AFTER_COMPLETED) return TtsState.PAUSED;
    return TtsState.SPEAKING;
  }

  void processAction(Intent immediate_action) {
    TtsState old_public_state = publicState();

    while (true) {
      Log.v("breviar", "TTS in state " + state.name());
      State new_state;
      if (immediate_action != null) {
        new_state = delta(immediate_action);
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
        new_state = delta(pending_action);
        if (new_state != State.REJECT) {
          state = new_state;
          pending_action = null;
          continue;
        }
      }

      new_state = delta(new Intent(IDLE_PROCESSING));
      if (new_state != State.REJECT) {
        state = new_state;
        continue;
      }
      break;
    }

    TtsState new_public_state = publicState();
    if (new_public_state != old_public_state) {
      broadcastUpdate();

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
          new Intent("sk.breviar.android.action.SHOW"), PendingIntent.FLAG_UPDATE_CURRENT);

        PendingIntent stop = PendingIntent.getService(this, 0,
            new Intent().setClass(this, TtsService.class)
                        .setAction(TtsService.TTS_STOP), 0);

        PendingIntent forward = PendingIntent.getService(this, 0,
            new Intent().setClass(this, TtsService.class)
                        .setAction(TtsService.TTS_FORWARD), 0);

        PendingIntent back = PendingIntent.getService(this, 0,
            new Intent().setClass(this, TtsService.class)
                        .setAction(TtsService.TTS_BACK), 0);

        if (Build.VERSION.SDK_INT >= 26) {
          CompatibilityHelper26.updateChannel(this, false);
        }

        NotificationCompat.Builder builder = new NotificationCompat.Builder(this, "default")
              .setContentText(getString(R.string.channel_name))
              .setContentTitle(title)
              .setSmallIcon(icon)
              .setContentIntent(open_activity)
              .setColor(getResources().getColor(R.color.colorPrimary))
              .setPriority(NotificationCompat.PRIORITY_HIGH)
              .setStyle(new MediaStyle().setShowActionsInCompactView(0, 2, 3));

        if (new_public_state == TtsState.SPEAKING) {
          PendingIntent pause = PendingIntent.getService(this, 0,
              new Intent().setClass(this, TtsService.class)
                          .setAction(TtsService.TTS_PAUSE), 0);
          builder.addAction(R.drawable.ic_pause_white_24dp, getString(R.string.tts_pause), pause);
        } else {
          PendingIntent resume = PendingIntent.getService(this, 0,
              new Intent().setClass(this, TtsService.class)
                          .setAction(TtsService.TTS_RESUME), 0);
          builder.addAction(R.drawable.ic_play_arrow_white_24dp, getString(R.string.tts_resume), resume);
        }

        builder.addAction(R.drawable.ic_volume_off_white_24dp, getString(R.string.tts_speaking), stop)
               .addAction(R.drawable.ic_fast_rewind_white_24dp, getString(R.string.tts_back), back)
               .addAction(R.drawable.ic_fast_forward_white_24dp, getString(R.string.tts_forward), forward)
               .setDefaults(Notification.DEFAULT_SOUND | Notification.DEFAULT_LIGHTS)
               .setVibrate(new long[]{0l, 0l});

        if (old_public_state == TtsState.READY) {
          startForeground(
              BreviarApp.NOTIFY_TTS_ID,
              builder.build());
        } else {
          ((NotificationManager)getSystemService(NOTIFICATION_SERVICE)).notify(
              BreviarApp.NOTIFY_TTS_ID, builder.build());
        }
      }
    }
  }

  void broadcastUpdate() {
    sendBroadcast(new Intent(TTS_UPDATE_ACTION).putExtra("state", publicState()));
  }

  // Bridge from provided interfaces.

  @Override
  public void onStart(Intent intent, int startId) {
    onStartCommand(intent, -1, -1);
  }

  @Override
  public int onStartCommand(Intent intent, int flags, int startId) {
    if (headless == null) {
      headless = new HeadlessWebview(getApplicationContext());
    }
    if (player == null) {
      player = new MediaPlayer();
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

  @Override
  public void onUtteranceCompleted(String utteranceId) {
    processAction(new Intent(SYNTHESIS_DONE));
  }

  @Override
  public void onCompletion(MediaPlayer mp) {
    processAction(new Intent(PLAY_DONE));
  }

  Intent pending_action = null;        // pending action from clients.

  // State variables:

  // `player` and `headless` are not null whenever the service is running.
  MediaPlayer player = null;           // in initialized state <=> internal_state > SETTING_UP_PLAYER
  HeadlessWebview headless = null;

  // Objects below are valid <=> not null.
  String url = null;                   // valid <=> internal_state > IDLE
  String url_title = null;             // valid <=> internal_state > IDLE
  String language = null;              // valid <=> internal_state > IDLE
  TextToSpeech tts = null;             // valid <=> internal_state > IDLE
  String[] sections = null;            // valid <=> internal_state > GETTING_TEXT
  int tts_section;                     // valid <=> internal_state > GETTING_TEXT
  int synthesized_begin;               // valid <=> internal_state > START_SECTION
  int synthesized_end;                 // valid <=> internal_state > START_SECTION
  File synthesized_file = null;        // valid <=> internal_state in {SYNTHESIZING*} or (in {PLAYING,PAUSED,PAUSED_AFTER_COMPLETED} and sythesized_begin < synthesized_end)
  File played_file = null;             // valid <=> internal_state in {*PLAYING, *PAUSED}
  FileInputStream played_fd = null;    // same as played_file

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
            requestText();
            return State.GETTING_TEXT;

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
            // sections and tts_section were initialized in HeadlessWebview
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
            if (tts_section < sections.length - 1) {
              ++tts_section;
            }
            return State.START_SECTION;

          case TTS_BACK:
            if (tts_section > 0) {
              --tts_section;
            }
            return State.START_SECTION;

          case IDLE_PROCESSING:
            while (tts_section < sections.length &&
                   sections[tts_section].length() == 0) {
              ++tts_section;
            }
            if (tts_section >= sections.length) {
              sections = null;
              shutdownTts();
              url = null;
              url_title = null;
              language = null;
              return State.IDLE;
            }
            synthesized_begin = 0;
            // setups synthesized_end and synthesized_file
            startSynthesis();
            return State.SYNTHESIZING;

          default:
            return State.REJECT;
        }

      case SYNTHESIZING:
        switch (action.getAction()) {
          case SYNTHESIS_DONE:
            // setup synthesized_begin, synthesized_file, and played*
            startPlaying();
            return State.PLAYING;

          default:
            return State.REJECT;
        }

      case PLAYING:
        switch (action.getAction()) {
          case TTS_STOP:
            player.reset();
            deletePlayedFile();
            if (synthesized_begin < synthesized_end) {
              deleteSynthesizedFile();
            }
            sections = null;
            shutdownTts();
            language = null;
            url = null;
            url_title = null;
            return State.IDLE;

          case TTS_PAUSE:
            player.pause();
            return State.PAUSED;

          case TTS_FORWARD:
          case TTS_BACK:
            return ForwardOrBackwardFromPlayingOrPaused(action.getAction());

          case PLAY_DONE:
            player.reset();
            deletePlayedFile();

            if (synthesized_begin < synthesized_end)  {
              startPlaying();
              return State.PLAYING;
            }

            if (synthesized_end == sections[tts_section].length()) {
              ++tts_section;
              return State.START_SECTION;
            }

            startSynthesis();
            return State.SYNTHESIZING;

          case IDLE_PROCESSING:
            if (synthesized_begin < synthesized_end ||
                synthesized_end == sections[tts_section].length()) {
              return State.REJECT;
            }
            startSynthesis();
            return State.SYNTHESIZING_AND_PLAYING;

          default:
            return State.REJECT;
        }

      case SYNTHESIZING_AND_PLAYING:
        switch (action.getAction()) {
          case TTS_PAUSE:
            player.pause();
            return State.SYNTHESIZING_AND_PAUSED;

          case SYNTHESIS_DONE:
            return State.PLAYING;

          case PLAY_DONE:
            player.reset();
            deletePlayedFile();
            return State.SYNTHESIZING;

          default:
            return State.REJECT;
        }

      case SYNTHESIZING_AND_PAUSED:
        switch (action.getAction()) {
          case TTS_RESUME:
            player.start();
            return State.SYNTHESIZING_AND_PLAYING;

          case SYNTHESIS_DONE:
            return State.PAUSED;

          case PLAY_DONE:
            player.reset();
            deletePlayedFile();
            return State.SYNTHESIZING;

          default:
            return State.REJECT;
        }

      case PAUSED:
        switch (action.getAction()) {
          case TTS_STOP:
            player.reset();
            deletePlayedFile();
            if (synthesized_begin < synthesized_end) {
              deleteSynthesizedFile();
            }
            sections = null;
            shutdownTts();
            language = null;
            url = null;
            url_title = null;
            return State.IDLE;

          case TTS_RESUME:
            player.start();
            return State.PLAYING;

          case TTS_FORWARD:
          case TTS_BACK:
            return ForwardOrBackwardFromPlayingOrPaused(action.getAction());

          case PLAY_DONE:
            player.reset();
            deletePlayedFile();
            return State.PAUSED_AFTER_COMPLETED;

          case IDLE_PROCESSING:
            if (synthesized_begin < synthesized_end ||
                synthesized_end == sections[tts_section].length()) {
              return State.REJECT;
            }
            startSynthesis();
            return State.SYNTHESIZING_AND_PAUSED;

          default:
            return State.REJECT;
        }

      case PAUSED_AFTER_COMPLETED:
        switch (action.getAction()) {
          case TTS_STOP:
            if (synthesized_begin < synthesized_end) {
              deleteSynthesizedFile();
            }
            sections = null;
            shutdownTts();
            language = null;
            url = null;
            url_title = null;
            return State.IDLE;

          case TTS_RESUME:
            if (synthesized_begin < synthesized_end)  {
              startPlaying();
              return State.PLAYING;
            }

            if (synthesized_end == sections[tts_section].length()) {
              // This will start playing.
              ++tts_section;
              return State.START_SECTION;
            }

            startSynthesis();
            return State.SYNTHESIZING;

          case TTS_FORWARD:
          case TTS_BACK:
            if (action.getAction() == TTS_FORWARD) {
              if (tts_section >= sections.length) {
                return State.REJECT;
              }
              ++tts_section;
            } else {
              if (tts_section <= 0) {
                return State.REJECT;
              }
              --tts_section;
            }
            if (synthesized_begin < synthesized_end) {
              deleteSynthesizedFile();
            }
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

  void requestText() {
    tts.setOnUtteranceCompletedListener(this);
    int ret = tts.setLanguage(BreviarApp.appLanguageToLocale(language));
    Log.v("breviar", "setTTSLanguage: " + ret);

    Log.v("breviar", "Loading nonpersistent url " + url);
    headless.LoadAndExecute(url,
        "var x = document.querySelectorAll(\"h2,form\"); " +
        "for (var i = 0; i < x.length; ++i) { " +
        "  x[i].style.display = \"none\"; " +
        "}; " +
        "" +
        "function getText(node, sections) {" +
        "  if (node.nodeType == Node.TEXT_NODE) {" +
        "    sections[sections.length - 1] += node.textContent;" +
        "    return;" +
        "  }" +
        "  if (node.nodeType != Node.ELEMENT_NODE) {" +
        "    return;" +
        "  }" +
        "  if (node.className == 'tts_section') {" +
        "    sections.push(\"\");" +
        "  }" +
        "  if (window.getComputedStyle(node).display == 'none') {" +
        "    return;" +
        "  }" +
        "  for (var i = 0; i < node.childNodes.length; ++i) {" +
        "    getText(node.childNodes[i], sections);" +
        "  }" +
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
            Log.v("breviar", "Got callback result");
            for (int i = 0; i < result.length; ++i) {
              result[i] = result[i].replace('\n', ' ');
            }
            sections = result;
            tts_section = 0;
            processAction(new Intent(GOT_TEXT));
          }
        });
  }

  // Requires synthesized_begin < sections[tts_section].length
  // Setups synthesized_end and synthesized_file
  void startSynthesis() {
    if (synthesized_begin >= sections[tts_section].length()) {
      Log.v("breviar", "startSynthesis(): invariant violated");
    }
    synthesized_end = findTtsSplit(sections[tts_section], synthesized_begin);
    try {
      synthesized_file = File.createTempFile("speech", ".wav", null);
    } catch (IOException e) {
      Log.v("breviar", "Cannot create temp file");
    }

    HashMap<String, String> params = new HashMap<String, String>();
    params.put(TextToSpeech.Engine.KEY_PARAM_UTTERANCE_ID, "id");

    String chunk_text = sections[tts_section].substring(
                            synthesized_begin, synthesized_end);
    Log.v("breviar", "render chunk: " + chunk_text);
    tts.synthesizeToFile(chunk_text, params,
                         synthesized_file.getAbsolutePath());
  }

  int findTtsSplit(String chunk, int pos) {
    for (int i = pos; i < chunk.length(); ++i) {
      if (chunk.charAt(i) == '.' || chunk.charAt(i) == '!' ||
          chunk.charAt(i) == '?' || chunk.charAt(i) == ':' ||
          chunk.charAt(i) == ',' || chunk.charAt(i) == ';') {
        if (i == chunk.length() - 1) {
          return i + 1;
        } else if (Character.isWhitespace(chunk.charAt(i + 1))) {
          if (chunk.charAt(i) != ',' || i - pos > 100) {
            return i + 2;
          }
        }
      }
    }
    return chunk.length();
  }

  void deletePlayedFile() {
    try {
      played_fd.close();
      played_file.delete();
    } catch (IOException e) {
      Log.v("breviar", "Cannot close fd");
    }
  }

  void deleteSynthesizedFile() {
    synthesized_file.delete();
  }

  // Start to play the freshly synthesized file.
  // Setup synthesized_begin, synthesized_file, and played*
  void startPlaying() {
    synthesized_begin = synthesized_end;
    played_file = synthesized_file;
    synthesized_file = null;
    try {
      played_fd = new FileInputStream(played_file);
    } catch (IOException e) {
      Log.v("breviar", "Cannot open " + played_file.getAbsolutePath());
    }

    try {
      player.setDataSource(played_fd.getFD());
      player.prepare();
    } catch (IOException e) {
      Log.v("breviar", "Cannot set data source");
    }
    player.setOnCompletionListener(this);
    player.start();
  }

  State ForwardOrBackwardFromPlayingOrPaused(String action) {
    if (action == TTS_FORWARD) {
      if (tts_section >= sections.length) {
        return State.REJECT;
      }
      ++tts_section;
    } else {
      if (tts_section <= 0) {
        return State.REJECT;
      }
      --tts_section;
    }
    player.reset();
    deletePlayedFile();
    if (synthesized_begin < synthesized_end) {
      deleteSynthesizedFile();
    }
    return State.START_SECTION;
  }

  @Override
  public IBinder onBind(Intent in) {
    return null;
  }
}

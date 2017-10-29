package sk.breviar.android;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.media.AudioManager;
import android.net.Uri;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.PowerManager;
import android.speech.tts.TextToSpeech;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.text.Html;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.ScaleGestureDetector;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.webkit.JavascriptInterface;
import android.webkit.WebChromeClient;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.TextView;

import java.io.IOException;
import java.util.HashMap;

import sk.breviar.android.Alarms;
import sk.breviar.android.ClearProxy;
import sk.breviar.android.CompatibilityHelper11;
import sk.breviar.android.CompatibilityHelper19;
import sk.breviar.android.HeadlessWebview;
import sk.breviar.android.LangSelect;
import sk.breviar.android.Server;
import sk.breviar.android.UrlOptions;
import sk.breviar.android.Util;

public class Breviar extends Activity implements View.OnLongClickListener,
                                                 ScaleGestureDetector.OnScaleGestureListener,
                                                 NavigationView.OnNavigationItemSelectedListener,
                                                 TextToSpeech.OnInitListener,
                                                 TextToSpeech.OnUtteranceCompletedListener {
    static String scriptname = "l.cgi";
    static final int DIALOG_ABOUT = 1;
    static final int DIALOG_NEWS = 2;

    // Server singleton
    static Server S = null;

    DrawerLayout drawer;
    WebView wv;
    int scale;
    String language;
    boolean initialized, clearHistory;
    boolean fullscreen = false;
    boolean need_to_reload_preferences = true;
    boolean save_instance_enabled = true;
    float scroll_to = -1;
    NavigationView navigationView = null;

    HeadlessWebview headless;

    int appEventId = -1;
    PowerManager.WakeLock lock;

    int ringMode = -1;

    ScaleGestureDetector gesture_detector;

    TextToSpeech tts;
    enum TTSState {
      UNINITIALIZED,
      READY,
      SPEAKING
    }
    TTSState tts_state = TTSState.UNINITIALIZED;
    String tts_to_speak = "";

    @Override
    public void onInit(int status) {
      if (status == TextToSpeech.SUCCESS) {
        tts_state = TTSState.READY;
        tts.setOnUtteranceCompletedListener(this);
        setTTSLanguage();
        updateTTSState();
      } else {
        Log.v("breviar", "TTS engine failed to initialize");
      }
    }

    @Override
    public void onUtteranceCompleted(String utteranceId) {
      Log.v("breviar", "speaking completed");
      speakChunk();
    }

    void goHome() {
      Log.v("breviar", "goHome");
      wv.loadUrl("http://127.0.0.1:" + S.port + "/" + scriptname + 
                 "?qt=pdnes" + Html.fromHtml(S.getOpts()));
    }

    synchronized void initServer(String opts) {
      if (S != null) {
        S.setOpts(opts);
        return;
      }
      try {
        S = new Server(this, scriptname, language, opts);
      } catch (IOException e) {
        Log.v("breviar", "Can not initialize server!");
        finish();
        return;
      }
      S.start();
    }

    synchronized void stopServer() {
      Log.v("breviar", "stopServer called");
      if (S == null) return;
      S.stopServer();
      Log.v("breviar", "Server stopped");
      S = null;
    }

    void resetLanguage() {
      S.setLanguage(language);
      setTTSLanguage();
      clearHistory = true;

      // Povodne sme zahadzovali cele nastavenia:
      // wv.loadUrl("http://127.0.0.1:" + S.port + "/" + scriptname + "?qt=pdnes");
      // namiesto toho sa snazime z nich iba dat prec co je nekompatibilne. Toto je prvy pokus.
      // Since we call this only after LangSelect, url options in shared settings are up to date.
      String new_opts = BreviarApp.getUrlOptions(getApplicationContext())
                            .replaceAll("&amp;c=[^&]*&amp;", "&amp;")
                            .replaceAll("&amp;c=[^&]*$", "")
                            .replaceAll("&amp;j=[^&]*&amp;", "&amp;")
                            .replaceAll("&amp;j=[^&]*$", "");
      S.setOpts(new_opts);

      String new_url = "http://127.0.0.1:" + S.port + "/" + scriptname +
                       "?qt=pdnes" + Html.fromHtml(new_opts);

      Log.v("breviar", "resetLanguage: " + language + " new_url: " + new_url);

      wv.loadUrl(new_url);

      need_to_reload_preferences = false;

      syncPreferences();
      BreviarApp.initLocale(getApplicationContext());
      recreateIfNeeded();
    }

    public boolean tryOpenBible(String url) {
      try {
        if (url.startsWith("https://")) {
          url = "http://" + url.substring(8);
        }
        UrlOptions opts = new UrlOptions(S.getOpts());
        startActivity(new Intent("sk.ksp.riso.svpismo.action.SHOW", Uri.parse(url))
                          .putExtra("nightmode", opts.isNightmode()));
      } catch (android.content.ActivityNotFoundException e) {
        return false;
      }
      return true;
    }

    @Override
    protected void attachBaseContext(Context newBase) {
      super.attachBaseContext(newBase);
      BreviarApp.applyCustomLocale(this);
    }

    class Bridge {
      Breviar parent;

      public Bridge(Breviar parent_) {
        parent = parent_;
      }

      @JavascriptInterface
      public void pageUp() {
        parent.runOnUiThread(new Runnable() {
          public void run() {
            parent.wv.pageUp(false);
          }
        });
      }

      @JavascriptInterface
      public void pageDown() {
        parent.runOnUiThread(new Runnable() {
          public void run() {
            parent.wv.pageDown(false);
          }
        });
      }
    }


    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
      Log.v("breviar", "onCreate");

      tts_state = TTSState.UNINITIALIZED;
      tts = new TextToSpeech(this, this);

      appEventId = BreviarApp.getEventId();

      headless = new HeadlessWebview(this);

      // Restore preferences
      SharedPreferences settings = getSharedPreferences(Util.prefname, 0);
      language = settings.getString("language", "sk");
      scale = settings.getInt("scale", 100);
      fullscreen = settings.getBoolean("fullscreen", false);

      String opts = BreviarApp.getUrlOptions(getApplicationContext());

      lock = ((PowerManager)getSystemService(POWER_SERVICE))
                 .newWakeLock(PowerManager.SCREEN_BRIGHT_WAKE_LOCK, "breviar");

      // Initialize server very early, to avoid races
      initServer(opts);

      super.onCreate(savedInstanceState);
      requestWindowFeature(Window.FEATURE_NO_TITLE);

      setContentView(R.layout.breviar);

      navigationView = (NavigationView) findViewById(R.id.navigation);
      navigationView.setNavigationItemSelectedListener(this);

      drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
      wv = (WebView)findViewById(R.id.wv);
      ClearProxy.clearProxy(wv);
      wv.clearCache(true);
      wv.getSettings().setCacheMode(WebSettings.LOAD_NO_CACHE);
      wv.getSettings().setJavaScriptEnabled(true);
      wv.addJavascriptInterface(new Bridge(this), "bridge");
      // TODO(riso): replace constants by symbolic values after sdk upgrade
      if (Build.VERSION.SDK_INT < 19) {  // pre-KitKat
        wv.getSettings().setLayoutAlgorithm(WebSettings.LayoutAlgorithm.NARROW_COLUMNS);
      } else {
        CompatibilityHelper19.SetLayoutAlgorithmTextAutosizing(wv);
      }
      if (Build.VERSION.SDK_INT >= 11) {
        CompatibilityHelper11.hideZoomControls(wv.getSettings());
      }
      wv.getSettings().setUseWideViewPort(false);
      initialized = false;
      Log.v("breviar", "setting scale = " + scale);

      final Breviar parent = this;
      wv.setWebChromeClient(new WebChromeClient() {
          public void onConsoleMessage(String message, int lineNumber, String sourceID) {
          Log.d("breviarjs", message + " -- From line "
              + lineNumber + " of "
              + sourceID);
          }
          });

      wv.setWebViewClient(new WebViewClient() {
        @Override
        public boolean shouldOverrideUrlLoading(WebView view, String url) {
          if (url.startsWith("mailto:")) {
            String[] split_url = url.split(":");
            String email;
            if (split_url.length < 2) {
              email = "videky@breviar.sk";
            } else {
              email = split_url[1];
            }
            Intent emailIntent = new Intent(android.content.Intent.ACTION_SEND);
            emailIntent.setType("text/plain");
            emailIntent.putExtra(android.content.Intent.EXTRA_EMAIL, new String[]{email});
            emailIntent.putExtra(android.content.Intent.EXTRA_SUBJECT, "Komentár k breviáru");
            startActivity(emailIntent);
            return true;
          }
          if (url.startsWith("http://dkc.kbs.sk") || url.startsWith("https://dkc.kbs.sk")) {
            if (tryOpenBible(url)) return true;
          }
          if (url.startsWith("svpismo:")) {
            if (tryOpenBible(url)) return true;
          }

          Log.v("breviar", "sync in overrideurlloading");
          parent.syncScale();
          /*
          view.loadUrl(url);
          return true;
          */
          return false;
        }

        @Override
        public void onPageStarted(WebView view, String url, Bitmap favicon) {
          Log.v("breviar", "onPageStarted " + url);
          parent.syncScale();
          parent.initialized = true;
          super.onPageStarted(view, url, favicon);
        }

        @Override
        public void onPageFinished(WebView view, String url) {
          Log.v("breviar", "onPageFinished " + url);
          if (parent.clearHistory) view.clearHistory();
          parent.clearHistory = false;
          super.onPageFinished(view, url);

          // Ugly hack. But we have no reliable notification when is webview scrollable.
          if (parent.scroll_to < 0) return;
          final WebView wv = view;
          view.postDelayed(new Runnable() {
            public void run() {
              if (parent.scroll_to >= 0) {
                int Y = (int)(parent.scroll_to*wv.getContentHeight());
                wv.scrollTo(0, Y);
              }
              parent.scroll_to = -1;
            }
          }, 400);
        }
      });

      gesture_detector = new ScaleGestureDetector(this, this);

      wv.setOnLongClickListener(this);
      wv.setLongClickable(true);

      /*
      ((Button)findViewById(R.id.forwardBtn)).setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          parent.syncScale();
          wv.goForward();
        }
      });
      ((Button)findViewById(R.id.menuBtn)).setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          parent.openOptionsMenu();
        }
      });
      */
 
      ((Button)findViewById(R.id.pgupBtn)).setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          wv.pageUp(false);
        }
      });
 
      ((Button)findViewById(R.id.todayBtn)).setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          parent.syncScale();
          goHome();
        }
      });
 
      ((Button)findViewById(R.id.pgdnBtn)).setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          wv.pageDown(false);
        }
      });

      if (!getResources().getString(R.string.version).equals(settings.getString("version", ""))) {
        showDialog(DIALOG_NEWS);
        markVersion();
      }

      int id = -1;
      Intent intent = getIntent();
      if (intent != null) {
        String action = intent.getAction();
        if (action != null) {
          if (action.equals("sk.breviar.android.action.SHOW")) {
            id = intent.getIntExtra("id", -1);
          }
        }
      }

      Log.v("breviar", "onCreate: intent id = " + id);

      if (id >=0 && id < Util.events.length) {
        wv.loadUrl("http://127.0.0.1:" + S.port + "/" + scriptname + 
                   "?qt=pdnes&p=" + Util.events[id].p + Html.fromHtml(S.getOpts()));
      } else {
        if (savedInstanceState == null) {
          goHome();
        } else {
          Log.v("breviar", "onCreate: savedInstanceState != null");
          String url = savedInstanceState.getString("wv-url");
          Log.v("breviar", "onCreate: saved url: " + url);
          if (url == null) {
            goHome();
          } else {
            url = url.replaceFirst("http://[^/]*/", "http://127.0.0.1:" + S.port + "/");
            Log.v("breviar", "onCreate: loading url: " + url);
            wv.loadUrl(url);
          }
        }
      }

      save_instance_enabled = true;
      Log.v("breviar", "onCreate: Updating fullscreen and menu");
      updateFullscreen();
      updateMenu();
      Log.v("breviar", "onCreate: done");
    }

    @Override
    public boolean onScaleBegin(ScaleGestureDetector gd) {
      return true;
    }

    @Override
    public boolean onScale(ScaleGestureDetector gd) {
      if (gd.getScaleFactor() < 1/1.1 || gd.getScaleFactor() > 1.1) {
        onScaleEnd(gd);
        return true;
      }
      return false;
    }

    @Override
    public void onScaleEnd(ScaleGestureDetector gd) {
      scale *= gd.getScaleFactor();
      if (scale < 10) scale = 10;
      if (scale > 1000) scale = 1000;
      syncScale();
    }

    @Override
    public boolean dispatchTouchEvent(android.view.MotionEvent e) {
      gesture_detector.onTouchEvent(e);  
      return super.dispatchTouchEvent(e);
    }

    void recreateIfNeeded() {
      appEventId = BreviarApp.getEventId();
      if (Build.VERSION.SDK_INT >= 11) {
        save_instance_enabled = false;
        new CompatibilityHelper11().recreate(this);
      }
    }

    boolean resumed = false;
    @Override
    protected void onResume() {
      String url = wv.getUrl();
      if (url != null && need_to_reload_preferences) {
        need_to_reload_preferences = false;
        scroll_to = wv.getScrollY() / (float)wv.getContentHeight();

        UrlOptions opts = new UrlOptions(url, true);
        opts.override(new UrlOptions(BreviarApp.getUrlOptions(
              getApplicationContext()).replaceAll("&amp;", "&")));
        S.setOpts(opts.build(true));

        String new_url = opts.build();
        Log.v("breviar", "Reloading preferences; new url = " + new_url);
        wv.loadUrl(new_url);
        updateMenu();  // nightmode setting may have changed.
      }
      if (!resumed) {
        resumed = true;
        if (BreviarApp.getDimLock(getApplicationContext())) {
          lock.acquire();
        }
        if (BreviarApp.getMute(getApplicationContext())) {
          AudioManager manager = (AudioManager)getSystemService(Context.AUDIO_SERVICE);
          ringMode = manager.getRingerMode();
          manager.setRingerMode(AudioManager.RINGER_MODE_SILENT);
        } else {
          ringMode = -1;
        }
        if (appEventId < BreviarApp.getEventId()) recreateIfNeeded();
      }
      super.onResume();
    }

    @Override
    protected void onPause() {
      super.onPause();
      if (resumed) {
        resumed = false;
        if (BreviarApp.getDimLock(getApplicationContext())) {
          lock.release();
        }
        if (ringMode != -1) {
          AudioManager manager = (AudioManager)getSystemService(Context.AUDIO_SERVICE);
          manager.setRingerMode(ringMode);
          ringMode = -1;
        }
      }
    }

    @Override
    protected void onNewIntent(Intent intent) {
      int id = -1;
      if (intent.getAction().equals("sk.breviar.android.action.SHOW")) {
        id = intent.getIntExtra("id", -1);
      }
      Log.v("breviar", "onNewIntent: id = " + id);

      if (id >=0 && id < Util.events.length) {
        wv.loadUrl("http://127.0.0.1:" + S.port + "/" + scriptname + 
                   "?qt=pdnes&p=" + Util.events[id].p + Html.fromHtml(S.getOpts()));
      }
    }

    protected void onSaveInstanceState(Bundle outState) {
      Log.v("breviar", "onSaveInstanceState");
      if (save_instance_enabled) {
        syncScale();
        //wv.saveState(outState);
        String url = wv.getUrl();
        if (url != null) {
          outState.putString("wv-url", url);
        }
        Log.v("breviar", "onSaveInstanceState: saved url: " + url);
        syncPreferences();
      }
      super.onSaveInstanceState(outState);
    }

    void syncPreferences() {
      // We need an Editor object to make preference changes.
      // All objects are from android.context.Context
      SharedPreferences settings = getSharedPreferences(Util.prefname, 0);
      SharedPreferences.Editor editor = settings.edit();
      editor.putInt("scale", scale);
      if (need_to_reload_preferences) {
        editor.commit();
        return;
      }
      editor.putString("language", language);
      editor.putBoolean("fullscreen", fullscreen);
      editor.commit();

      if (S != null) {
        BreviarApp.setUrlOptions(getApplicationContext(), S.getOpts());
      }
    }

    void markVersion() {
      SharedPreferences settings = getSharedPreferences(Util.prefname, 0);
      SharedPreferences.Editor editor = settings.edit();
      editor.putString("version", getResources().getString(R.string.version));
      editor.commit();
    }

    protected void syncScale() {
      wv.loadUrl("javascript:document.cookie = 'zoom=" + (int)(scale) + "'; syncScale();");
      Log.v("breviar", "syncScale "+scale);
    }

    protected void onStop(){
      Log.v("breviar", "onStop");
      syncScale();
      super.onStop();
      syncPreferences();
    }

    @Override
    public void onDestroy() {
      Log.v("breviar", "onDestroy");
      tts.shutdown();
      stopServer();
      super.onDestroy();
    }

    @Override
    protected Dialog onCreateDialog(int id) {
      String content = null;
      switch(id) {
        case DIALOG_ABOUT:
          content = Util.getAboutText(this);
          break;
        case DIALOG_NEWS:
          content = getString(R.string.news);
          break;
        default:
          // fall through
      }
      return Util.createHtmlDialog(this, content);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
      if (resultCode == RESULT_OK) {
        language = data.getStringExtra("lang");
        if (language == null) language = "sk";
        resetLanguage();
      }
    }

    void updateFullscreen() {
      WindowManager.LayoutParams params = getWindow().getAttributes();
      if (fullscreen) {
        findViewById(R.id.navbar).setVisibility(View.GONE);
        params.flags |= WindowManager.LayoutParams.FLAG_FULLSCREEN;
      } else {
        findViewById(R.id.navbar).setVisibility(View.VISIBLE);
        params.flags &= ~WindowManager.LayoutParams.FLAG_FULLSCREEN;
      }
      getWindow().setAttributes(params);
    }

    public void updateMenu() {
      if (navigationView == null) return;
      Menu menu = navigationView.getMenu();
      if (menu == null) return;

      if (fullscreen) {
        menu.findItem(R.id.fullscreen_toggle).setTitle(R.string.fullscreenOff);
      } else {
        menu.findItem(R.id.fullscreen_toggle).setTitle(R.string.fullscreenOn);
      }

      UrlOptions opts = new UrlOptions(S.getOpts());
      if (opts.isNightmode()) {
        menu.findItem(R.id.nightmode_toggle).setTitle(R.string.nightmodeOff);
      } else {
        menu.findItem(R.id.nightmode_toggle).setTitle(R.string.nightmodeOn);
      }

      if (opts.isOnlyNonBoldFont()) {
        menu.findItem(R.id.only_non_bold_font_toggle).setTitle(R.string.onlyNonBoldFontOff);
      } else {
        menu.findItem(R.id.only_non_bold_font_toggle).setTitle(R.string.onlyNonBoldFontOn);
      }
    }

    void stopSpeaking() {
      tts_to_speak = "";
      tts_state = TTSState.READY;
      tts.stop();
    }

    void speakChunk() {
      if (tts_state != TTSState.SPEAKING) {
        return;
      }
      if (tts_to_speak.isEmpty()) {
        Log.v("breviar", "speak chunk: finished");
        tts_state = TTSState.READY;
        runOnUiThread(new Runnable() {
          public void run() {
            updateTTSState();
          }
        });
      } else {
        String chunk;
        if (tts_to_speak.length() <= 1024) {
          chunk = tts_to_speak;
          tts_to_speak = "";
          Log.v("breviar", "speak chunk: last chunk");
        } else {
          int pos = tts_to_speak.indexOf(" ", 1000);
          if (pos < 0) {
            chunk = tts_to_speak;
            tts_to_speak = "";
            Log.v("breviar", "speak chunk: last chunk, but maybe too long");
          } else {
            chunk = tts_to_speak.substring(0, pos);
            tts_to_speak = tts_to_speak.substring(pos);
            Log.v("breviar", "speak chunk: speaking " + pos + " characters, " +
                              tts_to_speak.length() + " still left");
          }
        }
        HashMap<String, String> params = new HashMap<String, String>();
        params.put(TextToSpeech.Engine.KEY_PARAM_UTTERANCE_ID, "id");
        Log.v("breviar", "speak chunk: speaking " + chunk);
        tts.speak(chunk, TextToSpeech.QUEUE_FLUSH, params);
      }
    }

    void startSpeaking() {
      tts_state = TTSState.SPEAKING;
      UrlOptions opts = new UrlOptions(wv.getUrl() + S.getOpts().replaceAll("&amp;", "&"), true);
      opts.setBlindFriendly(true);

      String url = opts.getBuilder().encodedAuthority("127.0.0.1:" + S.port_nonpersistent)
                       .build().toString();
      Log.v("breviar", "Loading nonpersistent url " + url);

      headless.LoadAndExecute(url,
          "var x = document.querySelectorAll(\"h2,form\"); " +
          "for (var i = 0; i < x.length; ++i) { " +
          "  x[i].style.display = \"none\"; " +
          "}; " +
          "bridge.callback(document.getElementById(\"contentRoot\").innerText);",
          new HeadlessWebview.Callback() {
            public void run(String result) {
              Log.v("breviar", "Got callback result");
              if (tts_state == TTSState.SPEAKING) {
                tts_to_speak = result;
                speakChunk();
              }
            }
          });
    }

    void setTTSLanguage() {
      if (tts_state == TTSState.UNINITIALIZED) return;
      if (tts_state == TTSState.SPEAKING) {
        stopSpeaking();
      }
      int ret = tts.setLanguage(BreviarApp.appLanguageToLocale(language));
      Log.v("breviar", "setTTSLanguage: " + ret);
    }

    void updateTTSState() {
      Log.v("breviar", "updating speak toggle menu label");
      MenuItem item = navigationView.getMenu().findItem(R.id.speak_toggle);
      switch (tts_state) {
        case UNINITIALIZED:
          item.setTitle(R.string.tts_uninitialized);
          break;
        case READY:
          item.setTitle(R.string.tts_ready);
          break;
        case SPEAKING:
          item.setTitle(R.string.tts_speaking);
          break;
      }
    }

    @Override
    public boolean onNavigationItemSelected(MenuItem item) {
      UrlOptions opts;
      switch (item.getItemId()) {
        case R.id.lang_select:
          syncPreferences();
          need_to_reload_preferences = true;
          Intent selectLang = new Intent(this, LangSelect.class);
          startActivityForResult(selectLang, 0);
          break;

        case R.id.fullscreen_toggle:
          fullscreen = !fullscreen;
          updateFullscreen();
          syncPreferences();
          break;

        case R.id.nightmode_toggle:
          opts = new UrlOptions(wv.getUrl() + S.getOpts().replaceAll("&amp;", "&"), true);
          opts.setNightmode(!opts.isNightmode());

          scroll_to = wv.getScrollY() / (float)wv.getContentHeight();
          S.setOpts(opts.build(true));
          wv.loadUrl(opts.build());
          break;

        case R.id.only_non_bold_font_toggle:
          opts = new UrlOptions(wv.getUrl() + S.getOpts().replaceAll("&amp;", "&"), true);
          opts.setOnlyNonBoldFont(!opts.isOnlyNonBoldFont());

          scroll_to = wv.getScrollY() / (float)wv.getContentHeight();
          S.setOpts(opts.build(true));
          wv.loadUrl(opts.build());
          break;

        case R.id.menu_about:
          showDialog(DIALOG_ABOUT);
          break;

        case R.id.speak_toggle:
          if (tts_state == TTSState.SPEAKING) {
            stopSpeaking();
          } else if (tts_state == TTSState.READY) {
            startSpeaking();
          }
          updateTTSState();
          break;
      }
      updateMenu();
      drawer.closeDrawer(GravityCompat.START);

      /*
      if (getSupportActionBar() != null)
          getSupportActionBar().setTitle(mTitle);
       
      FragmentManager fragmentManager = getSupportFragmentManager();
      fragmentManager.beginTransaction()
              .replace(R.id.container, PlaceholderFragment.newInstance(position + 1))
              .commit();
      */
       
      return true;
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
      if (keyCode == KeyEvent.KEYCODE_BACK) {
        if (drawer.isDrawerOpen(GravityCompat.START)) {
          drawer.closeDrawer(GravityCompat.START, true);
          return true;
        } else if (wv.canGoBack()) {
          wv.goBack();
          return true;
        } else {
          return super.onKeyDown(keyCode, event);
        }
      }
      if ((keyCode == KeyEvent.KEYCODE_VOLUME_UP) && BreviarApp.getVolButtons(this)) {
        wv.pageUp(false);
        return true;
      }
      if ((keyCode == KeyEvent.KEYCODE_VOLUME_DOWN) && BreviarApp.getVolButtons(this)) {
        wv.pageDown(false);
        return true;
      }
      if (keyCode == KeyEvent.KEYCODE_MENU) {
        if (drawer.isDrawerOpen(GravityCompat.START)) {
          drawer.closeDrawer(GravityCompat.START, true);
        } else {
          drawer.openDrawer(GravityCompat.START, true);
        }
        return true;
      }
      return super.onKeyDown(keyCode, event);
    }

    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
      if ((keyCode == KeyEvent.KEYCODE_VOLUME_UP) && BreviarApp.getVolButtons(this)) {
        return true;
      }
      if ((keyCode == KeyEvent.KEYCODE_VOLUME_DOWN) && BreviarApp.getVolButtons(this)) {
        return true;
      }
      return super.onKeyUp(keyCode, event);
    }

    // handle long click in webview
    public boolean onLongClick (View v) {
      if (!fullscreen && BreviarApp.getLongClickTogglesBar(this)) {
        boolean shown = !BreviarApp.getNavBarShown(this);
        BreviarApp.setNavBarShown(this, shown);
        if (shown) {
          findViewById(R.id.navbar).setVisibility(View.VISIBLE);
        } else {
          findViewById(R.id.navbar).setVisibility(View.GONE);
        }
        return true;
      }
      return false;
    }


}

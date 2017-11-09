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
import android.os.Build;
import android.os.Bundle;
import android.os.PowerManager;
import android.speech.tts.TextToSpeech;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.view.MenuItemCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.widget.Toolbar;
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
import android.widget.CompoundButton;
import android.widget.TextView;

import java.io.IOException;
import java.util.HashMap;

import sk.breviar.android.Alarms;
import sk.breviar.android.ClearProxy;
import sk.breviar.android.CompatibilityHelper19;
import sk.breviar.android.DialogActivity;
import sk.breviar.android.HeadlessWebview;
import sk.breviar.android.LangSelect;
import sk.breviar.android.Server;
import sk.breviar.android.UrlOptions;
import sk.breviar.android.Util;

public class Breviar extends AppCompatActivity
                     implements View.OnLongClickListener,
                                ScaleGestureDetector.OnScaleGestureListener,
                                NavigationView.OnNavigationItemSelectedListener,
                                TextToSpeech.OnInitListener,
                                TextToSpeech.OnUtteranceCompletedListener {
    static String scriptname = "l.cgi";

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
    Toolbar toolbar = null;

    HeadlessWebview headless;

    int appEventId = -1;
    PowerManager.WakeLock lock;

    int ringMode = -1;

    ScaleGestureDetector gesture_detector;

    TextToSpeech tts = null;
    enum TTSState {
      READY,
      SPEAKING
    }
    TTSState tts_state = TTSState.READY;
    String tts_to_speak = "";

    @Override
    public void onInit(int status) {
      if (status == TextToSpeech.SUCCESS && tts_state == TTSState.SPEAKING && tts != null) {
        tts.setOnUtteranceCompletedListener(this);
        int ret = tts.setLanguage(BreviarApp.appLanguageToLocale(language));
        Log.v("breviar", "setTTSLanguage: " + ret);

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
      } else {
        Log.v("breviar", "TTS engine failed to initialize");
        if (tts != null) {
          tts.shutdown();
        }
        tts = null;
        tts_state = TTSState.READY;
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

    void startDialogActivity(int title_id, String query) {
      startActivity(new Intent(this, DialogActivity.class)
          .putExtra("title", title_id)
          .putExtra("url", "http://127.0.0.1:" + S.port_nonpersistent + "/" +
                           scriptname + "?" + query + Html.fromHtml(S.getOpts())));
    }

    void showAbout() {
      startDialogActivity(R.string.about_title, "qt=pst&st=i&p=0");
    }

    void showChangelog() {
      startDialogActivity(R.string.news_title, "qt=pst&st=i&p=1");
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

      toolbar = (Toolbar) findViewById(R.id.breviar_toolbar);
      setSupportActionBar(toolbar);
      getSupportActionBar().setDisplayHomeAsUpEnabled(true);
      getSupportActionBar().setTitle(getString(R.string.app_name));

      navigationView = (NavigationView) findViewById(R.id.navigation);
      navigationView.setNavigationItemSelectedListener(this);

      Menu menu = navigationView.getMenu();
      try {
        ((CompoundButton)MenuItemCompat.getActionView(menu.findItem(R.id.nightmode_toggle)))
            .setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
                    @Override public void onCheckedChanged(CompoundButton button,
                                                           boolean isChecked) {
                      if (isChecked == new UrlOptions(S.getOpts()).isNightmode()) {
                        return;
                      }
                      toggleNightMode();
                      updateMenu();
                    }
                });

        ((CompoundButton)MenuItemCompat.getActionView(menu.findItem(R.id.only_non_bold_font_toggle)))
            .setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
                    @Override public void onCheckedChanged(CompoundButton button,
                                                           boolean isChecked) {
                      if (isChecked == !(new UrlOptions(S.getOpts()).isOnlyNonBoldFont())) {
                        return;
                      }
                      toggleOnlyNonBoldFont();
                      updateMenu();
                    }
                });

        ((CompoundButton)MenuItemCompat.getActionView(menu.findItem(R.id.fullscreen_toggle)))
            .setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
                    @Override public void onCheckedChanged(CompoundButton button,
                                                           boolean isChecked) {
                      if (isChecked == fullscreen) {
                        return;
                      }
                      toggleFullscreen();
                      updateMenu();
                    }
                });

      } catch (java.lang.NullPointerException e) {
        Log.v("breviar", "Cannot setup navigation view!");
      }

      drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
      ActionBarDrawerToggle drawerToggle = new ActionBarDrawerToggle(
          this,  drawer, toolbar,
          R.string.navigation_drawer_open, R.string.navigation_drawer_close
      );
      drawer.setDrawerListener(drawerToggle);
      getSupportActionBar().setDisplayHomeAsUpEnabled(true);
      getSupportActionBar().setHomeButtonEnabled(true);
      drawerToggle.syncState();

      wv = (WebView)findViewById(R.id.wv);
      ClearProxy.clearProxy(wv);
      wv.clearCache(true);
      wv.getSettings().setCacheMode(WebSettings.LOAD_NO_CACHE);
      wv.getSettings().setJavaScriptEnabled(true);
      wv.getSettings().setBuiltInZoomControls(true);
      wv.addJavascriptInterface(new Bridge(this), "bridge");
      // TODO(riso): replace constants by symbolic values after sdk upgrade
      if (Build.VERSION.SDK_INT < 19) {  // pre-KitKat
        wv.getSettings().setLayoutAlgorithm(WebSettings.LayoutAlgorithm.NARROW_COLUMNS);
      } else {
        CompatibilityHelper19.SetLayoutAlgorithmTextAutosizing(wv);
      }
      wv.getSettings().setDisplayZoomControls(false);
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

        String capitalize(String s) {
          s = s.trim();
          if (s.length() < 1) return s;
          return s.substring(0, 1).toUpperCase() + s.substring(1);
        }

        @Override
        public void onPageFinished(WebView view, String url) {
          Log.v("breviar", "onPageFinished " + url);
          if (parent.clearHistory) view.clearHistory();
          parent.clearHistory = false;
          super.onPageFinished(view, url);

          String title = null;
          String subtitle = "";
          String wv_title = wv.getTitle();
          // Hack: CGI module does not set title for some pages. Revert to app name then.
          if (wv_title != null && !wv_title.contains("127.0.0.1")) {
            String[] split_title = wv_title.split(" *\\| *", 2);
            if (split_title.length == 1) {
              title = split_title[0];
            } else if (split_title.length == 2) {
              title = split_title[1];
              subtitle = split_title[0];
            }
          }
          if (title == null) {
            title = getString(R.string.app_name);
          }
          getSupportActionBar().setTitle(capitalize(title));
          getSupportActionBar().setSubtitle(subtitle);

          if (need_to_update_menu) {
            need_to_update_menu = false;
            updateMenu();
          }

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

      if (!getResources().getString(R.string.version).equals(settings.getString("version", ""))) {
        showChangelog();
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
      Log.v("breviar", "onCreate: done");
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
      switch (item.getItemId()) {
        case R.id.todayBtn:
          syncScale();
          goHome();
          return true;

        case R.id.speakBtn:
          toggleSpeakState();
          return true;

        case R.id.nightmodeBtn:
          toggleNightMode();
          updateMenu();
          return true;

        default:
          // If we got here, the user's action was not recognized.
          // Invoke the superclass to handle it.
          return super.onOptionsItemSelected(item);
      }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.breviar_toolbar_menu, menu);
        return true;
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
      save_instance_enabled = false;
      recreate();
    }

    boolean resumed = false;
    // After resume we need to update menu after the page is reloaded.
    boolean need_to_update_menu = false;
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
        need_to_update_menu = true;
        wv.loadUrl(new_url);
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
      stopServer();
      super.onDestroy();
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
        getSupportActionBar().hide();
        params.flags |= WindowManager.LayoutParams.FLAG_FULLSCREEN;
      } else {
        getSupportActionBar().show();
        params.flags &= ~WindowManager.LayoutParams.FLAG_FULLSCREEN;
      }
      getWindow().setAttributes(params);
    }

    void updateMenuItemSwitch(MenuItem item, boolean value) {
      if (item == null) return;
      CompoundButton s = (CompoundButton)MenuItemCompat.getActionView(item);
      if (s == null) return;
      s.setChecked(value);
    }

    public void updateMenu() {
      if (navigationView == null) return;
      Menu menu = navigationView.getMenu();
      if (menu == null) return;

      UrlOptions opts = new UrlOptions(S.getOpts());
      MenuItem drawer_item = menu.findItem(R.id.nightmode_toggle);
      MenuItem action_item = toolbar.getMenu().findItem(R.id.nightmodeBtn);

      if (opts.isNightmode()) {
        updateMenuItemSwitch(drawer_item, true);
        if (action_item != null) {
          action_item.setTitle(R.string.nightmodeOff);
          action_item.setIcon(R.drawable.ic_wb_sunny_white_24dp);
        }
      } else {
        updateMenuItemSwitch(drawer_item, false);
        if (action_item != null) {
          action_item.setTitle(R.string.nightmodeOn);
          action_item.setIcon(R.drawable.ic_brightness_3_white_24dp);
        }
      }

      drawer_item = menu.findItem(R.id.only_non_bold_font_toggle);
      updateMenuItemSwitch(drawer_item, !opts.isOnlyNonBoldFont());

      drawer_item = menu.findItem(R.id.fullscreen_toggle);
      updateMenuItemSwitch(drawer_item, fullscreen);
    }

    void stopSpeaking() {
      tts_to_speak = "";
      tts.stop();
      tts.shutdown();
      tts = null;
      tts_state = TTSState.READY;
      runOnUiThread(new Runnable() {
        public void run() {
          updateTTSState();
        }
      });
    }

    void speakChunk() {
      if (tts_state != TTSState.SPEAKING) {
        return;
      }
      if (tts_to_speak.isEmpty()) {
        Log.v("breviar", "speak chunk: finished");
        tts.shutdown();
        tts = null;
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
      tts = new TextToSpeech(this, this);
      updateTTSState();
    }

    void updateTTSState() {
      Log.v("breviar", "updating speak toggle menu label");
      MenuItem drawer_item = navigationView.getMenu().findItem(R.id.speak_toggle);
      MenuItem action_item = toolbar.getMenu().findItem(R.id.speakBtn);
      switch (tts_state) {
        case READY:
          drawer_item.setTitle(R.string.tts_ready);
          action_item.setTitle(R.string.tts_ready);
          action_item.setIcon(R.drawable.ic_action_volume_on);
          break;
        case SPEAKING:
          drawer_item.setTitle(R.string.tts_speaking);
          action_item.setTitle(R.string.tts_speaking);
          action_item.setIcon(R.drawable.ic_action_volume_muted);
          break;
      }
    }

    void toggleSpeakState() {
      if (tts_state == TTSState.SPEAKING) {
        stopSpeaking();
      } else if (tts_state == TTSState.READY) {
        startSpeaking();
      }
      updateTTSState();
    }

    void toggleNightMode() {
      UrlOptions opts;
      opts = new UrlOptions(wv.getUrl() + S.getOpts().replaceAll("&amp;", "&"), true);
      opts.setNightmode(!opts.isNightmode());

      scroll_to = wv.getScrollY() / (float)wv.getContentHeight();
      S.setOpts(opts.build(true));
      wv.loadUrl(opts.build());
    }

    void toggleOnlyNonBoldFont() {
      UrlOptions opts;
      opts = new UrlOptions(wv.getUrl() + S.getOpts().replaceAll("&amp;", "&"), true);
      opts.setOnlyNonBoldFont(!opts.isOnlyNonBoldFont());

      scroll_to = wv.getScrollY() / (float)wv.getContentHeight();
      S.setOpts(opts.build(true));
      wv.loadUrl(opts.build());
    }

    void toggleFullscreen() {
      fullscreen = !fullscreen;
      updateFullscreen();
      syncPreferences();
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

        case R.id.settings:
          syncPreferences();
          need_to_reload_preferences = true;
          startActivity(new Intent(this, MainSettings.class));
          break;

        case R.id.fullscreen_toggle:
          toggleFullscreen();
          break;

        case R.id.nightmode_toggle:
          toggleNightMode();
          break;

        case R.id.only_non_bold_font_toggle:
          toggleOnlyNonBoldFont();
          break;

        case R.id.menu_about:
          showAbout();
          break;

        case R.id.menu_news:
          showChangelog();
          break;

        case R.id.menu_alarms:
          startActivity(new Intent("sk.breviar.android.ALARMS"));
          break;

        case R.id.speak_toggle:
          toggleSpeakState();
          break;
      }
      updateMenu();
      drawer.closeDrawer(GravityCompat.START);
      return true;
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
      if (keyCode == KeyEvent.KEYCODE_BACK) {
        if (drawer.isDrawerOpen(GravityCompat.START)) {
          drawer.closeDrawer(GravityCompat.START, true);
          return true;
        } else if (wv.canGoBack()) {
          S.forceOptsForNextRequest();
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
          getSupportActionBar().show();
        } else {
          getSupportActionBar().hide();
        }
        return true;
      }
      return false;
    }


}

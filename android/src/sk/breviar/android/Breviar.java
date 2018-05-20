package sk.breviar.android;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.app.Dialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.media.AudioManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.PowerManager;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.view.MenuItemCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.widget.Toolbar;
import android.text.Html;
import android.util.Log;
import android.view.GestureDetector;
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
import java.lang.Character;
import java.util.HashMap;

import sk.breviar.android.Alarms;
import sk.breviar.android.ClearProxy;
import sk.breviar.android.CompatibilityHelper19;
import sk.breviar.android.DialogActivity;
import sk.breviar.android.HeadlessWebview;
import sk.breviar.android.LangSelect;
import sk.breviar.android.Server;
import sk.breviar.android.TtsService;
import sk.breviar.android.UrlOptions;
import sk.breviar.android.Util;


public class Breviar extends AppCompatActivity
                     implements GestureDetector.OnDoubleTapListener,
                                ScaleGestureDetector.OnScaleGestureListener,
                                NavigationView.OnNavigationItemSelectedListener {
    static String scriptname = "l.cgi";

    // Server singleton
    static Server S = null;

    DrawerLayout drawer;
    WebView wv;
    String wv_title = null;
    String wv_subtitle = "";
    int scale;
    String language;
    boolean initialized, clearHistory;
    boolean fullscreen = false;
    boolean need_to_reload_preferences = true;
    boolean save_instance_enabled = true;
    float scroll_to = -1;
    NavigationView navigationView = null;
    Toolbar toolbar = null;

    int appEventId = -1;
    PowerManager.WakeLock lock;

    int ringMode = -1;

    ScaleGestureDetector scale_gesture_detector;
    GestureDetector tap_gesture_detector;

    TtsService.TtsState tts_state = TtsService.TtsState.READY;
    class TtsStateReceiver extends BroadcastReceiver {
      public TtsStateReceiver(Breviar parent_) {
        parent = parent_;
      }

      public void onReceive(Context context, Intent intent) {
        Log.v("breviar", "Received broadcast");
        if (intent != null) {
          if (intent.getAction() != null) {
            if (intent.getAction().equals(TtsService.TTS_UPDATE_ACTION)) {
              tts_state = (TtsService.TtsState)intent.getSerializableExtra("state");
              Log.v("breviar", "Updating TTS state");
              updateTtsState();
            }
          }
        }
      }

      Breviar parent;
    };
    TtsStateReceiver tts_receiver;


    void goHome() {
      Log.v("breviar", "goHome");
      if (wv == null) return;
      if (S == null) return;
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
      S.setBackgroundOverride(BreviarApp.getBackgroundOverride(this));
      S.start();
    }

    void startDialogActivity(int title_id, String query, boolean show_ok) {
      startActivity(new Intent(this, DialogActivity.class)
          .putExtra("title", title_id)
          .putExtra("url", "http://127.0.0.1:" + S.port_nonpersistent + "/" +
                           scriptname + "?" + query + Html.fromHtml(S.getOpts()))
          .putExtra("show_ok", show_ok));
    }

    void showAbout() {
      startDialogActivity(R.string.about_title, "qt=pst&st=i&p=0", false);
    }

    void showChangelog(boolean show_ok) {
      startDialogActivity(R.string.news_title, "qt=pst&st=i&p=1", show_ok);
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

      tts_receiver = new TtsStateReceiver(this);
      appEventId = BreviarApp.getEventId();

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
      menu.findItem(R.id.speak_pause_toggle).setVisible(false);
      menu.findItem(R.id.speak_back).setVisible(false);
      menu.findItem(R.id.speak_forward).setVisible(false);;
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
      wv.getSettings().setBuiltInZoomControls(false);
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
            if (tryOpenBible(url)) {
              return true;
            } else {
              Log.v("breviar", "link to svpismo:// ignored, cannot open the app");
              return true;
            }
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

          wv_title = null;
          wv_subtitle = "";
          String raw_title = wv.getTitle();
          // Hack: CGI module does not set title for some pages. Revert to app name then.
          if (raw_title != null && !raw_title.contains("127.0.0.1")) {
            String[] split_title = raw_title.split(" *\\| *", 2);
            if (split_title.length == 1) {
              wv_title = split_title[0];
            } else if (split_title.length == 2) {
              wv_title = split_title[1];
              wv_subtitle = split_title[0];
            }
          }
          if (wv_title == null) {
            wv_title = getString(R.string.app_name);
          }
          wv_title = capitalize(wv_title);
          getSupportActionBar().setTitle(wv_title);
          getSupportActionBar().setSubtitle(wv_subtitle);

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

      scale_gesture_detector = new ScaleGestureDetector(this, this);
      if (Build.VERSION.SDK_INT >= 19) {
        scale_gesture_detector.setQuickScaleEnabled(false);
      }
      tap_gesture_detector = new GestureDetector(this,
                                     new GestureDetector.SimpleOnGestureListener());
      tap_gesture_detector.setOnDoubleTapListener(this);

      if (!getResources().getString(R.string.version).equals(settings.getString("version", ""))) {
        showChangelog(true);
        markVersion();
      }

      if (!handleIntent(getIntent())) {
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
          if (tts_state == TtsService.TtsState.READY) {
            toggleSpeakState();
          } else if (tts_state == TtsService.TtsState.SPEAKING) {
            pauseSpeaking();
          } else if (tts_state == TtsService.TtsState.PAUSED) {
            resumeSpeaking();
          }
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
        updateTtsState();
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
      scale_gesture_detector.onTouchEvent(e);
      tap_gesture_detector.onTouchEvent(e);
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
    synchronized protected void onResume() {
      String url = wv.getUrl();
      if (url != null && need_to_reload_preferences) {
        need_to_reload_preferences = false;
        scroll_to = wv.getScrollY() / (float)wv.getContentHeight();

        UrlOptions opts = new UrlOptions(url, true);
        opts.override(new UrlOptions(BreviarApp.getUrlOptions(
              getApplicationContext()).replaceAll("&amp;", "&")));
        S.setOpts(opts.build(true));
        S.setBackgroundOverride(BreviarApp.getBackgroundOverride(this));

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
          try {
            manager.setRingerMode(AudioManager.RINGER_MODE_SILENT);
          } catch (java.lang.SecurityException e) {
            Log.v("breviar", "Switching to silent mode is not allowed");
          }
        } else {
          ringMode = -1;
        }
        if (appEventId < BreviarApp.getEventId()) recreateIfNeeded();
      }
      super.onResume();
    }

    @Override
    synchronized protected void onPause() {
      super.onPause();
      if (resumed) {
        resumed = false;
        if (BreviarApp.getDimLock(getApplicationContext())) {
          lock.release();
        }
        if (ringMode != -1) {
          AudioManager manager = (AudioManager)getSystemService(Context.AUDIO_SERVICE);
          try {
            manager.setRingerMode(ringMode);
          } catch (java.lang.SecurityException e) {
            Log.v("breviar", "Switching to silent mode is not allowed");
          }
          ringMode = -1;
        }
      }
    }

    // Return if the intent loaded a page.
    boolean handleIntent(Intent intent) {
      if (intent != null) {
        if (intent.getAction() != null) {
          if (intent.getAction().equals("sk.breviar.android.action.SHOW")) {
            int id = intent.getIntExtra("id", -1);
            if (id >=0 && id < Util.events.length) {
              wv.loadUrl("http://127.0.0.1:" + S.port + "/" + scriptname +
                         "?qt=pdnes&p=" + Util.events[id].p + Html.fromHtml(S.getOpts()));
              return true;
            }
          }
        }
      }
      return false;
    }

    @Override
    protected void onNewIntent(Intent intent) {
      Log.v("breviar", "onNewIntent");
      handleIntent(intent);
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

    boolean stopped = true;

    @Override
    synchronized protected void onStop(){
      if (!stopped) {
        stopped = true;
        Log.v("breviar", "Unregistering receiver");
        unregisterReceiver(tts_receiver);
      }
      Log.v("breviar", "onStop");
      syncScale();
      super.onStop();
      syncPreferences();
    }

    @Override
    synchronized protected void onStart(){
      if (stopped) {
        stopped = false;
        Log.v("breviar", "Registering receiver");
        registerReceiver(tts_receiver, new IntentFilter(TtsService.TTS_UPDATE_ACTION));
        startService(new Intent().setClass(this, TtsService.class).setAction(TtsService.TTS_REQUEST_UPDATE));
      }
      Log.v("breviar", "onStart");
      super.onStart();
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
      if (S == null) return;
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
      if (drawer_item != null) {
        updateMenuItemSwitch(drawer_item, !opts.isOnlyNonBoldFont());
      }

      drawer_item = menu.findItem(R.id.fullscreen_toggle);
      if (drawer_item != null) {
        updateMenuItemSwitch(drawer_item, fullscreen);
      }
    }

    void updateTtsState() {
      Log.v("breviar", "updating speak toggle menu label");
      MenuItem drawer_item = navigationView.getMenu().findItem(R.id.speak_toggle);
      MenuItem action_item = toolbar.getMenu().findItem(R.id.speakBtn);

      MenuItem drawer_item_pause = navigationView.getMenu().findItem(R.id.speak_pause_toggle);
      MenuItem drawer_item_back = navigationView.getMenu().findItem(R.id.speak_back);
      MenuItem drawer_item_forward = navigationView.getMenu().findItem(R.id.speak_forward);
      switch (tts_state) {
        case READY:
          drawer_item.setTitle(R.string.tts_ready);
          drawer_item.setIcon(R.drawable.ic_volume_up_white_24dp);

          if (action_item != null) {
            action_item.setTitle(R.string.tts_ready);
            action_item.setIcon(R.drawable.ic_volume_up_white_24dp);
          }

          drawer_item_pause.setVisible(false);
          drawer_item_back.setVisible(false);
          drawer_item_forward.setVisible(false);
          break;
        case SPEAKING:
          drawer_item.setTitle(R.string.tts_speaking);
          drawer_item.setIcon(R.drawable.ic_volume_off_white_24dp);

          if (action_item != null) {
            action_item.setTitle(R.string.tts_pause);
            action_item.setIcon(R.drawable.ic_pause_white_24dp);
          }

          drawer_item_pause.setVisible(true);
          drawer_item_pause.setTitle(R.string.tts_pause);
          drawer_item_pause.setIcon(R.drawable.ic_pause_white_24dp);

          drawer_item_back.setVisible(true);
          drawer_item_forward.setVisible(true);
          break;
        case PAUSED:
          drawer_item.setTitle(R.string.tts_speaking);
          drawer_item.setIcon(R.drawable.ic_volume_off_white_24dp);

          if (action_item != null) {
            action_item.setTitle(R.string.tts_resume);
            action_item.setIcon(R.drawable.ic_play_arrow_white_24dp);
          }

          drawer_item_pause.setVisible(true);
          drawer_item_pause.setTitle(R.string.tts_resume);
          drawer_item_pause.setIcon(R.drawable.ic_play_arrow_white_24dp);

          drawer_item_back.setVisible(true);
          drawer_item_forward.setVisible(true);
          break;
      }
    }

    void startSpeaking() {
      UrlOptions opts = new UrlOptions(wv.getUrl() + S.getOpts().replaceAll("&amp;", "&"), true);
      opts.setBlindFriendly(true);
      String url = opts.getBuilder().encodedAuthority("127.0.0.1:" + S.port_nonpersistent)
                       .build().toString();

      startService(new Intent().setClass(this, TtsService.class)
                               .setAction(TtsService.TTS_START)
                               .putExtra("language", language)
                               .putExtra("url", url)
                               .putExtra("url_title", (wv_title == null ? getString(R.string.app_name) : wv_title)));
    }

    void stopSpeaking() {
      startService(new Intent().setClass(this, TtsService.class).setAction(TtsService.TTS_STOP));
    }

    void pauseSpeaking() {
      startService(new Intent().setClass(this, TtsService.class).setAction(TtsService.TTS_PAUSE));
    }

    void resumeSpeaking() {
      startService(new Intent().setClass(this, TtsService.class).setAction(TtsService.TTS_RESUME));
    }

    void speakForward() {
      startService(new Intent().setClass(this, TtsService.class).setAction(TtsService.TTS_FORWARD));
    }

    void speakBack() {
      startService(new Intent().setClass(this, TtsService.class).setAction(TtsService.TTS_BACK));
    }

    void toggleSpeakState() {
      if (tts_state != TtsService.TtsState.READY) {
        stopSpeaking();
      } else {
        startSpeaking();
      }
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
          showChangelog(false);
          break;

        case R.id.menu_alarms:
          startActivity(new Intent("sk.breviar.android.ALARMS"));
          break;

        case R.id.speak_toggle:
          toggleSpeakState();
          break;

        case R.id.speak_pause_toggle:
          if (tts_state == TtsService.TtsState.SPEAKING) {
            pauseSpeaking();
          } else if (tts_state == TtsService.TtsState.PAUSED) {
            resumeSpeaking();
          }
          break;

        case R.id.speak_back:
          speakBack();
          break;

        case R.id.speak_forward:
          speakForward();
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
          if (S != null) {
            S.forceOptsForNextRequest();
          }
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

    @Override
    public boolean onDoubleTap(android.view.MotionEvent e) {
      toggleFullscreen();
      updateMenu();
      return true;
    }

    @Override
    public boolean onDoubleTapEvent(android.view.MotionEvent e) {
      return false;
    }

    @Override
    public boolean onSingleTapConfirmed(android.view.MotionEvent e) {
      return false;
    }
}

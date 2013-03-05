package sk.breviar.android;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.DialogInterface;
import android.app.Dialog;
import android.graphics.Bitmap;
import android.net.Uri;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.text.Html;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;

import java.io.IOException;

import sk.breviar.android.Alarms;
import sk.breviar.android.LangSelect;
import sk.breviar.android.Server;
import sk.breviar.android.Util;

public class Breviar extends Activity {
    static String scriptname = "cgi-bin/l.cgi";
    static final int DIALOG_HU_BETA = 1;
    static final int DIALOG_NEWS = 2;

    // Server singleton
    static Server S = null;

    WebView wv;
    int scale;
    String language;
    boolean initialized, clearHistory;
    boolean fullscreen = false;

    int appEventId = -1;

    void goHome() {
      Log.v("breviar", "goHome");
      wv.loadUrl("http://127.0.0.1:" + S.port + "/" + scriptname + 
                 "?qt=pdnes" + Html.fromHtml(S.getOpts()));
    }

    synchronized void initServer(String opts) {
      if (S != null) return;
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
      clearHistory = true;
      // povodne sme zahadzovali cele nastavenia:
      // wv.loadUrl("http://127.0.0.1:" + S.port + "/" + scriptname + "?qt=pdnes");
      // namiesto toho sa snazime z nich iba dat prec co je nekompatibilne. Toto je prvy pokus.
      wv.loadUrl("http://127.0.0.1:" + S.port + "/" + scriptname +
                 "?qt=pdnes" + Html.fromHtml(S.getOpts()
                     .replaceAll("&amp;c=[^&]*&amp;", "&amp;")
                     .replaceAll("&amp;j=[^&]*&amp;", "&amp;")));
      syncPreferences();
      BreviarApp.initLocale(this);
      recreateIfNeeded();
    }

    public boolean tryOpenBible(String url) {
      try {
        startActivity(new Intent("sk.ksp.riso.svpismo.action.SHOW", Uri.parse(url)));
      } catch (android.content.ActivityNotFoundException e) {
        return false;
      }
      return true;
    }

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
      Log.v("breviar", "onCreate");

      appEventId = BreviarApp.getEventId();

      // Restore preferences
      SharedPreferences settings = getSharedPreferences(Util.prefname, 0);
      language = settings.getString("language", "sk");
      scale = settings.getInt("scale", 100);
      fullscreen = settings.getBoolean("fullscreen", false);
      String opts = settings.getString("params", "");

      // Initialize server very early, to avoid races
      initServer(opts);

      super.onCreate(savedInstanceState);
      requestWindowFeature(Window.FEATURE_NO_TITLE);

      setContentView(R.layout.breviar);

      wv = (WebView)findViewById(R.id.wv);
      wv.clearCache(true);
      wv.getSettings().setCacheMode(WebSettings.LOAD_NO_CACHE);
      wv.getSettings().setBuiltInZoomControls(true);
      wv.getSettings().setSupportZoom(true);
      wv.getSettings().setLayoutAlgorithm(WebSettings.LayoutAlgorithm.NARROW_COLUMNS);
      wv.getSettings().setUseWideViewPort(false);
      wv.setInitialScale(scale);
      initialized = false;
      Log.v("breviar", "setting scale = " + scale);

      final Breviar parent = this;
      wv.setWebViewClient(new WebViewClient() {
        @Override
        public boolean shouldOverrideUrlLoading(WebView view, String url) {
          if (url.startsWith("mailto:")) {
            String[] blah_email = url.split(":");
            Intent emailIntent = new Intent(android.content.Intent.ACTION_SEND);
            emailIntent.setType("text/plain");
            emailIntent.putExtra(android.content.Intent.EXTRA_EMAIL, new String[]{blah_email[1]});
            emailIntent.putExtra(android.content.Intent.EXTRA_SUBJECT, "Komentár k breviáru");
            startActivity(emailIntent);
            return true;
          }
          if (url.startsWith("http://dkc.kbs.sk")) {
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
        public void onScaleChanged(WebView view, float oldSc, float newSc) {
          parent.scale = (int)(newSc*100);
          Log.v("breviar", "onScaleChanged: setting scale = " + scale);
          view.setInitialScale(parent.scale);
          super.onScaleChanged(view, oldSc, newSc);
        }

        @Override
        public void onPageStarted(WebView view, String url, Bitmap favicon) {
          Log.v("breviar", "onPageStarted " + url);
          if (parent.initialized) parent.syncScale();
          parent.initialized = true;
          super.onPageStarted(view, url, favicon);
        }

        @Override
        public void onPageFinished(WebView view, String url) {
          Log.v("breviar", "onPageFinished " + url);
          if (parent.clearHistory) view.clearHistory();
          parent.clearHistory = false;
          super.onPageFinished(view, url);
        }
      } );

      ((Button)findViewById(R.id.forwardBtn)).setOnClickListener(new View.OnClickListener() {
        public void onClick(View v) {
          parent.syncScale();
          wv.goForward();
        }
      });
 
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

      Log.v("breviar", "onCreate: Updating fullscreen");
      updateFullscreen();
      Log.v("breviar", "onCreate: done");
    }

    void recreateIfNeeded() {
      appEventId = BreviarApp.getEventId();
      if (Build.VERSION.SDK_INT >= 11) recreate();
    }

    @Override
    protected void onResume() {
      if (appEventId < BreviarApp.getEventId()) recreateIfNeeded();
      super.onResume();
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
      syncScale();
      //wv.saveState(outState);
      String url = wv.getUrl();
      if (url != null) {
        outState.putString("wv-url", url);
      }
      Log.v("breviar", "onSaveInstanceState: saved url: " + url);
      syncPreferences();
      super.onSaveInstanceState(outState);
    }

    void syncPreferences() {
      // We need an Editor object to make preference changes.
      // All objects are from android.context.Context
      SharedPreferences settings = getSharedPreferences(Util.prefname, 0);
      SharedPreferences.Editor editor = settings.edit();
      editor.putString("language", language);
      editor.putInt("scale", scale);
      editor.putBoolean("fullscreen", fullscreen);
      if (S != null) {
        editor.putString("params", S.getOpts());
      }

      // Commit the edits!
      editor.commit();
    }

    void markVersion() {
      SharedPreferences settings = getSharedPreferences(Util.prefname, 0);
      SharedPreferences.Editor editor = settings.edit();
      editor.putString("version", getResources().getString(R.string.version));
      editor.commit();
    }

    protected void syncScale() {
      scale = (int)(wv.getScale()*100);
      wv.setInitialScale(scale);
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
    public boolean onCreateOptionsMenu( Menu menu ) {
      // Inflate the currently selected menu XML resource.
      MenuInflater inflater = getMenuInflater();
      inflater.inflate( R.menu.menu, menu );
      return true;
    }

    @Override
    protected Dialog onCreateDialog(int id) {
      switch(id) {
        case DIALOG_NEWS:
          return new AlertDialog.Builder(this)
                 .setMessage(R.string.news)
                 .setCancelable(false)
                 .setNeutralButton("Ok", new DialogInterface.OnClickListener() {
                     public void onClick(DialogInterface dialog, int id) {
                          dialog.cancel();
                     }
                 })
                 .create();
        case DIALOG_HU_BETA:
          return new AlertDialog.Builder(this)
                 .setMessage(R.string.hu_beta_warning)
                 .setCancelable(false)
                 .setNeutralButton("Ok", new DialogInterface.OnClickListener() {
                     public void onClick(DialogInterface dialog, int id) {
                          dialog.cancel();
                     }
                 })
                 .create();
        default:
          // fall through
      }
      return null;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
      if (resultCode == RESULT_OK) {
        language = data.getStringExtra("lang");
        if (language == null) language = "sk";
        resetLanguage();
        if (language.equals("hu")) showDialog(DIALOG_HU_BETA);
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

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
      // Handle item selection
      switch (item.getItemId()) {
        case R.id.lang_select:
          Intent selectLang = new Intent(this, LangSelect.class);
          startActivityForResult(selectLang, 0);
          return true;
        case R.id.fullscreen_toggle:
          fullscreen = !fullscreen;
          updateFullscreen();
          syncPreferences();
          return true;
        case R.id.alarms:
          startActivity(new Intent("sk.breviar.android.ALARMS"));
          return true;
        default:
          return super.onOptionsItemSelected(item);
      }
    }

    @Override
    public boolean onPrepareOptionsMenu(Menu menu) {
      if (fullscreen) {
        menu.findItem(R.id.fullscreen_toggle).setTitle(R.string.fullscreenOff);
      } else {
        menu.findItem(R.id.fullscreen_toggle).setTitle(R.string.fullscreenOn);
      }
      return super.onPrepareOptionsMenu(menu);
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
      if ((keyCode == KeyEvent.KEYCODE_BACK) && wv.canGoBack()) {
        wv.goBack();
        return true;
      }
      if ((keyCode == KeyEvent.KEYCODE_VOLUME_UP) && BreviarApp.getVolButtons(this)) {
        wv.pageUp(false);
        return true;
      }
      if ((keyCode == KeyEvent.KEYCODE_VOLUME_DOWN) && BreviarApp.getVolButtons(this)) {
        wv.pageDown(false);
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
}

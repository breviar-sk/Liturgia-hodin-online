package sk.breviar.android;

import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import androidx.appcompat.widget.Toolbar;
import android.view.View;
import android.webkit.JavascriptInterface;
import android.webkit.WebView;
import android.widget.Button;

public class DialogActivity extends AppearanceActivity {
  @Override
  protected void attachBaseContext(Context newBase) {
    super.attachBaseContext(newBase);
    BreviarApp.applyCustomLocale(this);
  }
  
  WebView wv;
  TapNavigation tapNavigation;
  private Server ownedServer;

  class Bridge {
    DialogActivity parent;

    public Bridge(DialogActivity parent_) {
      parent = parent_;
    }

    @JavascriptInterface
    public void pageUp() {
      parent.runOnUiThread(new Runnable() {
        public void run() {
          EinkUi.page(parent.wv, false);
        }
      });
    }

    @JavascriptInterface
    public void pageDown() {
      parent.runOnUiThread(new Runnable() {
        public void run() {
          EinkUi.page(parent.wv, true);
        }
      });
    }

    @JavascriptInterface
    public void openTTSSettings() {
      parent.runOnUiThread(new Runnable() {
        public void run() {
          Intent intent = new Intent();
          intent.setAction("com.android.settings.TTS_SETTINGS");
          intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
          parent.startActivity(intent);
        }
      });
    }

    @JavascriptInterface
    public void openIntent(String url) {
      final android.net.Uri uri = android.net.Uri.parse(url);
      parent.runOnUiThread(new Runnable() {
        public void run() {
          Intent intent = new Intent(Intent.ACTION_VIEW, uri);
          intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
          parent.startActivity(intent);
        }
      });
    }
  }

  private String staticTextLanguage() {
    if (BreviarApp.getOverrideLocale(this)) {
      // Preserve prayer-language variants such as Czech Dominican (c2).
      return BreviarApp.getString(this, "language", "sk");
    }
    String language = BreviarApp.currentLocale(this).getLanguage();
    if (language.equals("cs")) language = "cz";
    String directory = language.equals("sk") ? "include" : "include_" + language;
    try {
      // Use the bundled translations, including English even though it is not
      // offered in the prayer-language menu.
      String[] files = getAssets().list(directory);
      if (files != null && files.length > 0) return language;
    } catch (java.io.IOException missingTranslation) {
      // Unsupported UI languages use the bundled English information pages.
    }
    return "en";
  }

  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);

    setContentView(R.layout.dialog_activity);
    wv = (WebView)findViewById(R.id.dialog_webview);
    findViewById(R.id.navigation_page_up).setOnClickListener(v -> EinkUi.page(wv, false));
    findViewById(R.id.navigation_page_down).setOnClickListener(v -> EinkUi.page(wv, true));
    wv.getSettings().setJavaScriptEnabled(true);
    wv.getSettings().setCacheMode(android.webkit.WebSettings.LOAD_NO_CACHE);
    wv.addJavascriptInterface(new Bridge(this), "bridge");

    Intent intent = getIntent();
    if (intent == null) {
      finish();
      return;
    }
    int title = intent.getIntExtra("title", -1);
    String url = intent.getStringExtra("url");
    Server server = Breviar.S;
    if (intent.hasExtra("static_text")) {
      // Settings can change before the reader resumes and updates its server.
      // Read the current preferences, and never persist this dialog's options.
      String options = BreviarApp.getUrlOptions(this);
      String language = staticTextLanguage();
      if (server == null) {
        // Android may restore settings/help after the reader process was killed.
        try {
          ownedServer = new Server(getApplicationContext(), Breviar.scriptname, language, options);
          ownedServer.start();
          server = ownedServer;
        } catch (java.io.IOException error) {
          android.util.Log.e("breviar", "Cannot start information-page server", error);
          finish();
          return;
        }
      }
      UrlOptions query = new UrlOptions(options);
      query.override(new UrlOptions(intent.getStringExtra("static_text")));
      query.params.put("j", language);
      // Information pages have no calendar. An inherited calendar could change
      // the requested language (notably cz to c2 in debug builds).
      query.params.put("k", "");
      url = "http://127.0.0.1:" + server.port_nonpersistent + "/" + Breviar.scriptname
          + "?" + query.getBuilder().build().getEncodedQuery();
    }
    tapNavigation = new TapNavigation(wv, server == null ? -1 : server.port_nonpersistent, url == null, null);
    wv.setWebViewClient(new android.webkit.WebViewClient() {
      @Override public boolean shouldOverrideUrlLoading(WebView view, String url) {
        // Preserve the default external-link behavior from before a client was installed.
        try {
          startActivity(new Intent(Intent.ACTION_VIEW, android.net.Uri.parse(url)));
          return true;
        } catch (android.content.ActivityNotFoundException error) {
          return false;
        }
      }
      @Override public void onPageStarted(WebView view, String url, android.graphics.Bitmap icon) {
        tapNavigation.pageStarted(url);
      }
      @Override public void onPageFinished(WebView view, String url) {
        tapNavigation.pageFinished();
      }
    });
    if (url == null) {
      String content = intent.getStringExtra("content");

      try {
        content = TapNavigation.withScript(this, content);
        wv.loadData(android.util.Base64.encodeToString(
                        content.getBytes("UTF-8"), android.util.Base64.DEFAULT),
                    "text/html; charset=utf-8", "base64");
      } catch (java.io.IOException e) {
        // Help remains usable if the optional gesture script cannot be read.
        wv.loadData(content, "text/html; charset=utf-8", null);
      }
    } else {
      android.util.Log.v("breviar", "DialogActivity loading url: " + url);
      wv.loadUrl(url);
    }
    boolean show_ok = intent.getBooleanExtra("show_ok", false);
    if (!show_ok) {
      View ok = (View)findViewById(R.id.dialog_ok);
      ok.setVisibility(View.GONE);
    }

    Toolbar toolbar = (Toolbar) findViewById(R.id.dialog_activity_toolbar);
    setSupportActionBar(toolbar);
    getSupportActionBar().setDisplayHomeAsUpEnabled(true);
    getSupportActionBar().setHomeAsUpIndicator(R.drawable.ic_action_cancel);
    if (title >= 0) {
      getSupportActionBar().setTitle(title);
    }

    final DialogActivity parent = this;
    ((Button)findViewById(R.id.dialog_ok)).setOnClickListener(new View.OnClickListener() {
      public void onClick(View v) {
        parent.finish();
      }
    });
  }

  @Override
  public boolean dispatchTouchEvent(android.view.MotionEvent event) {
    if (event.getActionMasked() == android.view.MotionEvent.ACTION_DOWN &&
        tapNavigation != null && tapNavigation.ownsGestures() &&
        !tapNavigation.contains(event.getRawX(), event.getRawY())) {
      tapNavigation.cancelPendingGesture();
    }
    return super.dispatchTouchEvent(event);
  }

  @Override
  protected void onResume() {
    super.onResume();
    if (tapNavigation != null) {
      tapNavigation.setMode(ReadingNavigation.get(this));
      tapNavigation.setActive(true);
    }
    findViewById(R.id.navigation_paging).setVisibility(
        ReadingNavigation.get(this) == ReadingNavigation.Mode.BUTTONS ? View.VISIBLE : View.GONE);
  }

  @Override
  protected void onPause() {
    if (tapNavigation != null) tapNavigation.setActive(false);
    super.onPause();
  }

  @Override protected void onDestroy() {
    if (tapNavigation != null) tapNavigation.close();
    // Closing a server can wait for rendering; never block the UI on that work.
    if (ownedServer != null) new Thread(ownedServer::stopServer, "Close help server").start();
    super.onDestroy();
  }

  @Override public void onActionModeStarted(android.view.ActionMode mode) {
    super.onActionModeStarted(mode);
    if (tapNavigation != null) tapNavigation.setSelecting(true);
  }

  @Override public void onActionModeFinished(android.view.ActionMode mode) {
    super.onActionModeFinished(mode);
    if (tapNavigation != null) tapNavigation.setSelecting(false);
  }

  @Override
  public boolean onSupportNavigateUp() {
    finish(); // close this activity as oppose to navigating up
    return false;
  }
}

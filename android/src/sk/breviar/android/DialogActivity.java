package sk.breviar.android;

import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.webkit.JavascriptInterface;
import android.webkit.WebView;
import android.widget.Button;

public class DialogActivity extends AppCompatActivity {
  @Override
  protected void attachBaseContext(Context newBase) {
    super.attachBaseContext(newBase);
    BreviarApp.applyCustomLocale(this);
  }
  
  WebView wv;

  class Bridge {
    DialogActivity parent;

    public Bridge(DialogActivity parent_) {
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

  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);

    setContentView(R.layout.dialog_activity);
    wv = (WebView)findViewById(R.id.dialog_webview);
    wv.getSettings().setJavaScriptEnabled(true);
    wv.addJavascriptInterface(new Bridge(this), "bridge");

    Intent intent = getIntent();
    if (intent == null) {
      finish();
      return;
    }
    int title = intent.getIntExtra("title", -1);
    String url = intent.getStringExtra("url");
    if (url == null) {
      String content = intent.getStringExtra("content");

      try {
        wv.loadData(android.util.Base64.encodeToString(
                        content.getBytes("UTF-8"), android.util.Base64.DEFAULT),
                    "text/html; charset=utf-8", "base64");
      } catch (java.io.UnsupportedEncodingException e) {
        wv.loadData("unsupported encoding utf-8", "text/html", null);
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
  public boolean onSupportNavigateUp() {
    finish(); // close this activity as oppose to navigating up
    return false;
  }
}

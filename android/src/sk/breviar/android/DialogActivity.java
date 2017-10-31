package sk.breviar.android;

import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.webkit.WebView;
import android.widget.Button;

public class DialogActivity extends AppCompatActivity {
  @Override
  protected void attachBaseContext(Context newBase) {
    super.attachBaseContext(newBase);
    BreviarApp.applyCustomLocale(this);
  }

  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);

    setContentView(R.layout.dialog_activity);
    WebView wv = (WebView)findViewById(R.id.dialog_webview);

    Intent intent = getIntent();
    if (intent == null) {
      finish();
      return;
    }
    int title = intent.getIntExtra("title", -1);
    String content = intent.getStringExtra("content");

    if (Build.VERSION.SDK_INT < 8) {
      wv.loadData(content, "text/html; charset=utf-8", "utf-8");
    } else {
      
      try {
        wv.loadData(CompatibilityHelper8.Base64EncodeToString(
                        content.getBytes("UTF-8")),
                    "text/html; charset=utf-8", "base64");
      } catch (java.io.UnsupportedEncodingException e) {
        wv.loadData("unsupported encoding utf-8", "text/html", null);
      }
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

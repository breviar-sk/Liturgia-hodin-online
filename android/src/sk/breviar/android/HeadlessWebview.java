package sk.breviar.android;

import android.content.Context;
import android.util.Log;
import android.webkit.JavascriptInterface;
import android.webkit.WebView;
import android.webkit.WebViewClient;

public class HeadlessWebview {
  public interface Callback {
    public void run(String[] result);
  }

  WebView wv;
  String client_command = "";
  Callback client_callback = null;

  class Bridge {
    HeadlessWebview parent;

    public Bridge(HeadlessWebview parent_) {
      parent = parent_;
    }

    @JavascriptInterface
    public void callback(String[] result) {
      if (parent.client_callback != null) {
        parent.client_callback.run(result);
      }
    }
  }

  public HeadlessWebview(Context context) {
    wv = new WebView(context);
    wv.getSettings().setJavaScriptEnabled(true);
    wv.addJavascriptInterface(new Bridge(this), "bridge");
    wv.setWebViewClient(new WebViewClient() {
      @Override
      public void onPageFinished(WebView view, String url) {
        Log.v("breviar", "headless onPageFinished " + url);
        super.onPageFinished(view, url);

        if (url.startsWith("javascript:")) {
          return;
        }

        if (!client_command.isEmpty()) {
          Log.v("breviar", "headless: running javascript");
          wv.loadUrl("javascript:" + client_command);
        }
      }
    });
  }

  // Load @url. After the loading finished, execute javascript @command. The
  // command can use javascript function 'bridge.callback(_)' to report a
  // string result to @callback.
  public void LoadAndExecute(String url, String command, Callback callback) {
    client_command = command;
    client_callback = callback;
    wv.loadUrl(url);
  }

  public String GetTitle() {
    String wv_title = wv.getTitle();
    if (wv_title != null && !wv_title.contains("127.0.0.1")) {
      String[] split_title = wv_title.split(" *\\| *", 2);
      if (split_title.length == 1) {
        return split_title[0];
      } else if (split_title.length == 2) {
        return split_title[1];
      }
    }
    return null;
  }
}

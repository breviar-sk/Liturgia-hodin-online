package sk.breviar.android;

import android.net.Uri;
import java.util.Map;

public class UrlOptions {
  public UrlOptions(String opts, boolean is_full_url) {
    if (is_full_url) {
      base_uri = Uri.parse(opts);
    } else {
      base_uri = Uri.parse("http://127.0.0.1/cgi?q=pdnes" + opts.replaceAll("&amp;", "&"));
    }
    params = new java.util.HashMap<String, String>();
    for (String param : base_uri.getQueryParameterNames()) {
      params.put(param, base_uri.getQueryParameter(param));
    }
  }

  public UrlOptions(String opts) {
    this(opts, false);
  }

  public String build() {
    Uri.Builder builder = base_uri.buildUpon();
    builder.clearQuery();
    for (Map.Entry<String, String> entry : params.entrySet()) {
      builder.appendQueryParameter(entry.getKey(), entry.getValue());
    }
    return builder.build().toString();
  }

  public boolean isNightmode() {
    return hasBit("o2", 8);
  }

  public void setNightmode(boolean value) {
    setBit("o2", 8, value);
  }

  int getInt(String key) {
    try {
      return Integer.parseInt(params.get(key));
    } catch (java.lang.Exception e) {
      return 0;
    }
  }

  boolean hasBit(String key, int bit) {
    return (getInt(key) & (1 << bit)) != 0;
  }

  void setBit(String key, int bit, boolean val) {
    int v = getInt(key) & ~(1 << bit);
    if (val) {
      v |= 1 << bit;
    }
    params.put(key, Integer.toString(v));
  }

  Map<String, String> params;
  Uri base_uri;
}

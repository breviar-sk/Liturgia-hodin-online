package sk.breviar.android;

import android.net.Uri;
import android.util.Log;
import java.util.Map;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlOptions {
  public UrlOptions(String opts, boolean is_full_url) {
    if (is_full_url) {
      base_uri = Uri.parse(opts);
    } else {
      base_uri = Uri.parse("http://127.0.0.1/cgi?q=pdnes" + opts.replaceAll("&amp;", "&"));
    }
    params = new java.util.HashMap<String, String>();

    Pattern p = Pattern.compile("(^|&)([^;=]+)=");
    Matcher m = p.matcher(base_uri.getQuery());
    while (m.find()) {
      String key = m.group(2);
      String value = base_uri.getQueryParameter(key);
      if (value != null) {
        params.put(key, base_uri.getQueryParameter(key));
      }
    }
  }

  public UrlOptions(String opts) {
    this(opts, false);
  }

  public String build() {
    Uri.Builder builder = new Uri.Builder();
    builder.scheme(base_uri.getScheme());
    builder.encodedAuthority(base_uri.getEncodedAuthority());
    builder.appendEncodedPath(base_uri.getEncodedPath().replaceAll("^/", ""));
    for (Map.Entry<String, String> entry : params.entrySet()) {
      builder.appendQueryParameter(entry.getKey(), entry.getValue());
    }
    String result = builder.build().toString();
    return result;
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

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
      String decoded = opts.replaceAll("&amp;", "&");
      if (decoded.startsWith("&")) {
        decoded = decoded.substring(1);
      }
      base_uri = Uri.parse("http://127.0.0.1/cgi?" + decoded);
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

  public void override(UrlOptions other) {
    params.putAll(other.params);
  }

  public String build(boolean build_query_only) {
    Uri.Builder builder = new Uri.Builder();
    builder.scheme(base_uri.getScheme());
    builder.encodedAuthority(base_uri.getEncodedAuthority());
    builder.appendEncodedPath(base_uri.getEncodedPath().replaceAll("^/", ""));
    for (Map.Entry<String, String> entry : params.entrySet()) {
      builder.appendQueryParameter(entry.getKey(), entry.getValue());
    }
    String result;
    if (build_query_only) {
      result = "&amp;" + builder.build().getEncodedQuery().replaceAll("&", "&amp;");
    } else {
      result = builder.build().toString();
    }
    Log.v("breviar", "url built: " + result);
    return result;
  }

  public String build() {
    return build(false);
  }

  public boolean isOnlyNonBoldFont() {
    return hasBit("o0", 6);
  }

  public void setOnlyNonBoldFont(boolean value) {
    setBit("o0", 6, value);
  }

  public boolean isButtonsOrder() {
    return hasBit("o0", 7);
  }

  public void setButtonsOrder(boolean value) {
    setBit("o0", 7, value);
  }

  public boolean isVerseNumbering() {
    return hasBit("o0", 0);
  }

  public void setVerseNumbering(boolean value) {
    setBit("o0", 0, value);
  }

  public boolean isBibleReferences() {
    return hasBit("o0", 1);
  }

  public void setBibleReferences(boolean value) {
    setBit("o0", 1, value);
  }

  public boolean isLiturgicalReadings() {
    return hasBit("o0", 2);
  }

  public void setLiturgicalReadings(boolean value) {
    setBit("o0", 2, value);
  }

  public boolean isEpiphanySunday() {
    return hasBit("o0", 3);
  }

  public void setEpiphanySunday(boolean value) {
    setBit("o0", 3, value);
  }

  public boolean isAscensionSunday() {
    return hasBit("o0", 4);
  }

  public void setAscensionSunday(boolean value) {
    setBit("o0", 4, value);
  }

  public boolean isBodyBloodSunday() {
    return hasBit("o0", 5);
  }

  public void setBodyBloodSunday(boolean value) {
    setBit("o0", 5, value);
  }

  public boolean isNavigation() {
    return hasBit("o2", 5);
  }

  public void setNavigation(boolean value) {
    setBit("o2", 5, value);
  }

  public boolean isTextWrap() {
    return hasBit("o2", 6);
  }

  public void setTextWrap(boolean value) {
    setBit("o2", 6, value);
  }

  public boolean isSmartButtons() {
    return hasBit("o2", 7);
  }

  public void setSmartButtons(boolean value) {
    setBit("o2", 7, value);
  }

  public boolean isNightmode() {
    return hasBit("o2", 8);
  }

  public void setNightmode(boolean value) {
    setBit("o2", 8, value);
  }

  public boolean isEmphasizeLocalCalendar() {
    return hasBit("o2", 15);
  }

  public void setEmphasizeLocalCalendar(boolean value) {
    setBit("o2", 15, value);
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

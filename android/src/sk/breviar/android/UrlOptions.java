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

  // of0fn
  public boolean isOnlyNonBoldFont() {
    return hasBit("o0", 6);
  }

  public void setOnlyNonBoldFont(boolean value) {
    setBit("o0", 6, value);
  }

  // of0bo
  public boolean isButtonsOrder() {
    return hasBit("o0", 7);
  }

  public void setButtonsOrder(boolean value) {
    setBit("o0", 7, value);
  }

  // of0v
  public boolean isVerseNumbering() {
    return hasBit("o0", 0);
  }

  public void setVerseNumbering(boolean value) {
    setBit("o0", 0, value);
  }

  // of0r
  public boolean isBibleReferences() {
    return hasBit("o0", 1);
  }

  public void setBibleReferences(boolean value) {
    setBit("o0", 1, value);
  }

  // of0bc
  public boolean isBibleRefBibleCom() {
    return hasBit("o0", 12);
  }

  public void setBibleRefBibleCom(boolean value) {
    setBit("o0", 12, value);
	// set of0r to true if it was unchecked and used checked of0bc
	if(value && !hasBit("o0", 1)) {
		setBit("o0", 1, value);
	}
  }

  // of0ff
  public boolean isFootnotes() {
    return hasBit("o0", 9);
  }

  public void setFootnotes(boolean value) {
    setBit("o0", 9, value);
  }

  // of0cit
  public boolean isLiturgicalReadings() {
    return hasBit("o0", 2);
  }

  public void setLiturgicalReadings(boolean value) {
    setBit("o0", 2, value);
  }

  // of0cit
  public boolean isPsalmsOmissions() {
    return hasBit("o0", 11);
  }

  public void setPsalmsOmissions(boolean value) {
    setBit("o0", 11, value);
  }

  // of0zjvne
  public boolean isEpiphanySunday() {
    return hasBit("o0", 3);
  }

  public void setEpiphanySunday(boolean value) {
    setBit("o0", 3, value);
  }

  // of0nanne
  public boolean isAscensionSunday() {
    return hasBit("o0", 4);
  }

  public void setAscensionSunday(boolean value) {
    setBit("o0", 4, value);
  }

  // of0tkne
  public boolean isBodyBloodSunday() {
    return hasBit("o0", 5);
  }

  public void setBodyBloodSunday(boolean value) {
    setBit("o0", 5, value);
  }

  // of0tn
  public boolean isTransparentNav() {
    return hasBit("o0", 10);
  }

  public void setTransparentNav(boolean value) {
    setBit("o0", 10, value);
  }

  // of1zspc
  public boolean isDisplayCommuniaInfo() {
    return hasBit("o1", 12);
  }

  public void setDisplayCommuniaInfo(boolean value) {
    setBit("o1", 12, value);
  }

  // of2pv
  public boolean isFirstVespersButtons() {
    return hasBit("o2", 1);
  }

  public void setFirstVespersButtons(boolean value) {
    setBit("o2", 1, value);
  }

  // of2nav
  public boolean isNavigation() {
    return hasBit("o2", 5);
  }

  public void setNavigation(boolean value) {
    setBit("o2", 5, value);
  }

  // of2tw
  public boolean isTextWrap() {
    return hasBit("o2", 6);
  }

  public void setTextWrap(boolean value) {
    setBit("o2", 6, value);
  }

  // of2btnu
  public boolean isSmartButtons() {
    return hasBit("o2", 7);
  }

  public void setSmartButtons(boolean value) {
    setBit("o2", 7, value);
  }

  // of2nr
  public boolean isNightmode() {
    return hasBit("o2", 8);
  }

  public void setNightmode(boolean value) {
    setBit("o2", 8, value);
  }

  // of2bo
  public boolean isBackgroundOverride() {
    return hasBit("o2", 16);
  }

  public void setBackgroundOverride(boolean value) {
    setBit("o2", 16, value);
  }

  // of2rm
  public boolean isDisplayVariousOptions() {
    return hasBit("o2", 9);
  }

  public void setDisplayVariousOptions(boolean value) {
    setBit("o2", 9, value);
  }

  // of2a
  public boolean isDisplayAlternatives() {
    return hasBit("o2", 14);
  }

  public void setDisplayAlternatives(boolean value) {
    setBit("o2", 14, value);
  }

  // of2sdc
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

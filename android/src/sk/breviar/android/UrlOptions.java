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
    if (base_uri == null) return;
    if (base_uri.getQuery() == null) return;
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

  public Uri.Builder getBuilder() {
    Uri.Builder builder = new Uri.Builder();
    builder.scheme(base_uri.getScheme());
    builder.encodedAuthority(base_uri.getEncodedAuthority());
    String encoded_path = base_uri.getEncodedPath();
    if (encoded_path != null) {
      builder.appendEncodedPath(base_uri.getEncodedPath().replaceAll("^/", ""));
    }
    for (Map.Entry<String, String> entry : params.entrySet()) {
      builder.appendQueryParameter(entry.getKey(), entry.getValue());
    }
    return builder;
  }

  public String build(boolean build_query_only) {
    Uri.Builder builder = getBuilder();
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

  // of0bf
  public boolean isVoiceOutput() {
    return hasBit("o0", 8);
  }

  public void setVoiceOutput(boolean value) {
    setBit("o0", 8, value);
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

  // of0zft
  public boolean isPsalmsOmissions() {
    return hasBit("o0", 11);
  }

  public void setPsalmsOmissions(boolean value) {
    setBit("o0", 11, value);
  }

  // of0ic
  public boolean isItalicsConditional() {
    return hasBit("o0", 13);
  }

  public void setItalicsConditional(boolean value) {
    setBit("o0", 13, value);
  }

  // of0pe
  public boolean isPrintedEdition() {
    return hasBit("o0", 14);
  }

  public void setPrintedEdition(boolean value) {
    setBit("o0", 14, value);
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

  // of0ltn
  public boolean isTransparentNavLeft() {
    return hasBit("o0", 18);
  }

  public void setTransparentNavLeft(boolean value) {
    setBit("o0", 18, value);
  }

  // of0dotn
  public boolean isTransparentNavDownOnly() {
    return hasBit("o0", 20);
  }

  public void setTransparentNavDownOnly(boolean value) {
    setBit("o0", 20, value);
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

  // of2btnu
  public boolean isSmartButtons() {
    return hasBit("o2", 7);
  }

  public void setSmartButtons(boolean value) {
    setBit("o2", 7, value);
  }

  // of2nr
  public boolean isNightmode() {
    if (params.get("c") == null) {
      return hasBit("o2", 8);
    }
    return hasBit("c", 0);
  }

  public void setNightmode(boolean value) {
    setBit("c", 0, value);
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

  // of2rc
  public boolean isRoundedCorners() {
    return hasBit("o2", 16);
  }

  public void setRoundedCorners(boolean value) {
    setBit("o2", 16, value);
  }

  // of2sdc
  public boolean isEmphasizeLocalCalendar() {
    return hasBit("o2", 15);
  }

  public void setEmphasizeLocalCalendar(boolean value) {
    setBit("o2", 15, value);
  }

  // c0
  public String getBackgroundDayMode() {
    return getColor("c0", "");
  }

  public void setBackgroundDayMode(String value) {
    setColor("c0", value, "");
  }

  // c1
  public String getBackgroundNightMode() {
    return getColor("c1", "");
  }

  public void setBackgroundNightMode(String value) {
    setColor("c1", value, "");
  }

  // mm
  static int kDefaultMm = 5;
  public int getMm() {
    // Default value, must be consistent with DEF_STYLE_MARGIN in liturgia.h.
    // Alternatively, native code should always export mm parameter.
    return getInt("mm", kDefaultMm);
  }

  public void resetMm() {
    resetInt("mm");
  }

  public void setMm(int value) {
    setInt("mm", value, kDefaultMm);
  }

  // lh
  static int kDefaultLh = 130;
  public int getLh() {
    // Default value, must be consistent with liturgia.h.
    // Alternatively, native code should always export lh parameter.
    return getInt("lh", kDefaultLh);
  }

  public void resetLh() {
    resetInt("lh");
  }

  public void setLh(int value) {
    setInt("lh", value, kDefaultLh);
  }

  // ff
  static int kDefaultFf = 12;
  public int getFf() {
    // Default value, must be consistent with liturgia.h.
    // Alternatively, native code should always export ff parameter.
    return getInt("ff", kDefaultFf);
  }

  public void resetFf() {
    // Resetting to default means kDefaultFf, which must be explicitly set, because
    // browser might have different default.
    setInt("ff", kDefaultFf);
  }

  public void setFf(int value) {
    setInt("ff", value);
  }

  public String getFont() {
    return params.get("f");
  }

  public void setFont(String font) {
    params.remove("f");
    if (font != null) {
      params.put("f", font);
    }
  }

  int getInt(String key, int dflt) {
    try {
      return Integer.parseInt(params.get(key));
    } catch (java.lang.Exception e) {
      return dflt;
    }
  }

  int getInt(String key) {
    return getInt(key, 0);
  }

  void resetInt(String key) {
    params.remove(key);
    params.put(key, "");
  }

  void setInt(String key, int value, int dflt) {
    params.remove(key);
    if (value != dflt) {
      params.put(key, Integer.toString(value));
    } else {
      params.put(key, "");
    }
  }

  void setInt(String key, int value) {
    params.put(key, Integer.toString(value));
  }

  String maybeGetText(String key) {
    try {
      return params.get(key);
    } catch (java.lang.Exception e) {
      return null;
    }
  }

  private Pattern color_pattern =
      Pattern.compile("^([0-9a-z]{3}){1,2}$", Pattern.CASE_INSENSITIVE);

  // precondition: rgb is valid according to color_pattern
  String getColorRRGGBB(String rgb) {
	  String rrggbb = rgb;
	  if(rgb.length() == 3) {
		  rrggbb = "";
		  for (int i = 0; i < rgb.length(); i++) {
			  rrggbb += (rgb.charAt(i) + "" + rgb.charAt(i));
		  }
	  }
	  return rrggbb;
  }

  String getColor(String key, String dflt) {
    String c = maybeGetText(key);
    if (c != null && color_pattern.matcher(c).find()) {
      return getColorRRGGBB(c);
    }
    return dflt;
  }

  void setColor(String key, String value, String dflt) {
    params.remove(key);
    if (!value.equals(dflt) && color_pattern.matcher(value).find()) {
      params.put(key, getColorRRGGBB(value));
    } else {
      params.put(key, "");
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

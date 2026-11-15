package sk.breviar.android;

import android.net.Uri;
import java.math.BigInteger;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

/** The public CGI URL is the sharing format; keep selection and resolved options together. */
final class PrayerLink {
  static final String HOST = "breviar.sk";
  static final String PATH = "/cgi-bin/l.cgi";
  private static final String LINK_VERSION = "1";
  // Content flags from source/liturgia.h. Other bits control local presentation.
  private static final long CONTENT_0 = 1 | 2 | 4 | 8 | 16 | 32 | 512 | 2048 | 4096
      | 8192 | 16384 | 32768 | 65536 | 131072;
  private static final long CONTENT_2 = 2 | 64 | 512 | 16384;
  private static final Set<String> CONTENT_FORCES = new HashSet<>(Arrays.asList(
      "of0v", "of0r", "of0cit", "of0zjvne", "of0nanne", "of0tkne", "of0ff",
      "of0zft", "of0bc", "of0ic", "of0pe", "of0u2rc", "of02rcinv", "of0uac",
      "of2pv", "of2tw", "of2rm", "of2a"));
  private static final Set<String> APPEARANCE = new HashSet<>(Arrays.asList(
      "c", "ct0", "cr0", "c0", "ct1", "cr1", "c1", "f", "s", "ff", "mm", "lh", "v"));

  private PrayerLink() {}

  static boolean isSetting(String key) {
    return isContentSetting(key) || APPEARANCE.contains(key) || key.matches("of[0-6][a-z0-9]*");
  }

  static boolean isContentSetting(String key) {
    return key.equals("j") || key.equals("k") || key.matches("o[0-6]")
        || CONTENT_FORCES.contains(key) || key.matches("of[13456][a-z0-9]*");
  }

  static boolean hasAppearance(UrlOptions link) {
    for (String key : link.params.keySet()) {
      if (APPEARANCE.contains(key) || key.equals("o0") || key.equals("o2")
          || (isSetting(key) && !isContentSetting(key))) return true;
    }
    return false;
  }

  static String share(String page, String options, String language) {
    UrlOptions result = new UrlOptions(page, true);
    UrlOptions resolved = new UrlOptions(options);
    // Resolved words supersede force flags left in the URL of an earlier render.
    result.params.keySet().removeIf(key -> key.matches("of[0-6].*")
        && resolved.params.containsKey("o" + key.charAt(2)));
    result.override(resolved);
    result.params.keySet().removeIf(key -> !UrlOptions.SELECTION.contains(key) && !isSetting(key));
    result.params.putIfAbsent("j", language);
    result.params.putIfAbsent("k", ""); // Explicitly request the language's default calendar.
    result.params.put("sh", LINK_VERSION);
    if (!readable(result)) throw new IllegalArgumentException("Not a prayer page");
    Uri.Builder builder = new Uri.Builder().scheme("https").authority(HOST).path(PATH);
    Map<String, String> parameters = new TreeMap<>(result.params);
    for (String key : new String[]{"qt", "d", "m", "r", "j"}) {
      String value = parameters.remove(key);
      if (value != null) builder.appendQueryParameter(key, value);
    }
    for (Map.Entry<String, String> parameter : parameters.entrySet()) {
      builder.appendQueryParameter(parameter.getKey(), parameter.getValue());
    }
    String url = builder.build().toString();
    if (Uri.parse(url).getEncodedQuery().length() >= 2000) {
      throw new IllegalArgumentException("Prayer link exceeds the CGI query limit");
    }
    return url;
  }

  static UrlOptions read(Uri uri) {
    return read(uri, false);
  }

  static UrlOptions read(Uri uri, boolean appearance) {
    if (uri == null || !("https".equals(uri.getScheme()) || "http".equals(uri.getScheme()))
        || !HOST.equals(uri.getHost()) || !PATH.equals(uri.getPath())
        || uri.getUserInfo() != null || uri.getPort() != -1
        || uri.getEncodedQuery() == null || uri.getEncodedQuery().length() >= 2000) return null;
    try {
      UrlOptions result = new UrlOptions(uri.toString(), true);
      for (String key : uri.getQueryParameterNames()) {
        // Ignore settings the recipient will not use, including their values.
        if (!UrlOptions.SELECTION.contains(key) && !(appearance ? isSetting(key) : isContentSetting(key))) {
          result.params.remove(key);
          continue;
        }
        if (uri.getQueryParameters(key).size() != 1) return null;
        String value = result.params.get(key);
        if (!validValue(key, value)) return null;
      }
      if (!readable(result)) return null;
      result.params.putIfAbsent("j", "sk");
      result.params.putIfAbsent("k", "");
      return result;
    } catch (IllegalArgumentException error) {
      return null;
    }
  }

  private static boolean validValue(String key, String value) {
    if (value == null) return false;
    if (key.matches("o[0-6]|of[0-6][a-z0-9]*")) {
      bits(value);
      return true;
    }
    if (key.equals("f")) return value.matches("[\\p{L}\\p{N} _.-]{0,128}");
    if (key.matches("c[tr]?[01]")) return value.isEmpty() || !UrlOptions.normalizeColor(value).isEmpty();
    if (key.equals("c") || key.equals("v")) return value.isEmpty() || value.matches("[01]");
    if (key.equals("ff") || key.equals("mm") || key.equals("lh")) {
      return value.isEmpty() || (value.matches("[0-9]{1,5}") && Integer.parseInt(value) <= 32767);
    }
    return value.matches("[a-zA-Z0-9_-]{0,64}");
  }

  private static boolean readable(UrlOptions options) {
    String type = options.params.get("qt");
    return Arrays.asList("pdnes", "pdt", "plo", "pcr", "psv", "pmr").contains(type)
        || ("pst".equals(type) && "2".equals(options.params.get("st")));
  }

  /** Replace prayer settings while retaining this device's appearance and navigation. */
  static String applySettings(String current, String imported) {
    return applySettings(current, imported, false);
  }

  static String applySettings(String current, String imported, boolean appearance) {
    UrlOptions result = new UrlOptions(current);
    // Restored reader URLs can temporarily be the server's option snapshot.
    // Their selection must never overwrite the prayer being imported.
    result.params.keySet().removeAll(UrlOptions.SELECTION);
    UrlOptions source = new UrlOptions(imported);
    result.params.keySet().removeIf(key -> key.matches("of[0-6].*")
        && source.params.containsKey("o" + key.charAt(2))
        && (appearance ? isSetting(key) : isContentSetting(key)));
    for (Map.Entry<String, String> entry : source.params.entrySet()) {
      String key = entry.getKey();
      if (!(appearance ? isSetting(key) : isContentSetting(key))) continue;
      String value = entry.getValue();
      if (!appearance && (key.equals("o0") || key.equals("o2"))) {
        BigInteger mask = BigInteger.valueOf(mask(key.charAt(1) - '0'));
        value = bits(result.params.get(key)).andNot(mask).or(bits(value).and(mask)).toString();
      }
      result.params.put(key, value);
    }
    return result.build(true);
  }

  private static long mask(int word) { return word == 0 ? CONTENT_0 : CONTENT_2; }

  private static BigInteger bits(String value) {
    if (value == null || value.isEmpty()) return BigInteger.ZERO;
    if (!value.matches("[0-9]{1,20}")) throw new IllegalArgumentException("Invalid option word");
    BigInteger result = new BigInteger(value);
    if (result.bitLength() > 64) throw new IllegalArgumentException("Option word overflow");
    return result;
  }
}

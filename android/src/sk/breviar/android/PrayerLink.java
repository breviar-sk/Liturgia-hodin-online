package sk.breviar.android;

import android.net.Uri;
import java.math.BigInteger;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

/** The public CGI URL is the sharing format; keep selection and resolved options together. */
final class PrayerLink {
  static final String HOST = "breviar.sk";
  static final String PATH = "/cgi-bin/l.cgi";
  // Content flags from source/liturgia.h. Other bits control local presentation.
  private static final long CONTENT_0 = 1 | 2 | 4 | 8 | 16 | 32 | 512 | 2048 | 4096
      | 8192 | 16384 | 32768 | 65536 | 131072;
  private static final long CONTENT_2 = 2 | 64 | 512 | 16384;
  private static final Set<String> CONTENT_FORCES = new HashSet<>(Arrays.asList(
      "of0v", "of0r", "of0cit", "of0zjvne", "of0nanne", "of0tkne", "of0ff",
      "of0zft", "of0bc", "of0ic", "of0pe", "of0u2rc", "of02rcinv", "of0uac",
      "of2pv", "of2tw", "of2rm", "of2a"));

  private PrayerLink() {}

  static boolean isSetting(String key) {
    return key.equals("j") || key.equals("k") || key.matches("o[0-6]")
        || CONTENT_FORCES.contains(key) || key.matches("of[13456][a-z0-9]*");
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
    for (int word : new int[]{0, 2}) {
      String key = "o" + word;
      if (result.params.containsKey(key)) result.params.put(key,
          bits(result.params.get(key)).and(BigInteger.valueOf(mask(word))).toString());
    }
    if (!readable(result)) throw new IllegalArgumentException("Not a prayer page");
    String url = result.getBuilder().scheme("https").authority(HOST).path(PATH).build().toString();
    if (Uri.parse(url).getEncodedQuery().length() >= 2000) {
      throw new IllegalArgumentException("Prayer link exceeds the CGI query limit");
    }
    return url;
  }

  static UrlOptions read(Uri uri) {
    if (uri == null || !("https".equals(uri.getScheme()) || "http".equals(uri.getScheme()))
        || !HOST.equals(uri.getHost()) || !PATH.equals(uri.getPath())
        || uri.getUserInfo() != null || uri.getPort() != -1
        || uri.getEncodedQuery() == null || uri.getEncodedQuery().length() >= 2000) return null;
    try {
      UrlOptions result = new UrlOptions(uri.toString(), true);
      for (String key : uri.getQueryParameterNames()) {
        if (uri.getQueryParameters(key).size() != 1) return null;
        if (!UrlOptions.SELECTION.contains(key) && !isSetting(key)) continue;
        String value = result.params.get(key);
        if (value == null || !value.matches("[a-zA-Z0-9_-]{0,64}")) return null;
        if (key.matches("o[0-6]|of[0-6][a-z0-9]*") && !value.isEmpty()) bits(value);
      }
      result.params.keySet().removeIf(key -> !UrlOptions.SELECTION.contains(key) && !isSetting(key));
      if (!readable(result)) return null;
      result.params.putIfAbsent("j", "sk");
      result.params.putIfAbsent("k", "");
      return result;
    } catch (IllegalArgumentException error) {
      return null;
    }
  }

  private static boolean readable(UrlOptions options) {
    String type = options.params.get("qt");
    return Arrays.asList("pdnes", "pdt", "plo", "pcr", "psv", "pmr").contains(type)
        || ("pst".equals(type) && "2".equals(options.params.get("st")));
  }

  /** Replace prayer settings while retaining this device's appearance and navigation. */
  static String applySettings(String current, String imported) {
    UrlOptions result = new UrlOptions(current);
    // Restored reader URLs can temporarily be the server's option snapshot.
    // Their selection must never overwrite the prayer being imported.
    result.params.keySet().removeAll(UrlOptions.SELECTION);
    UrlOptions source = new UrlOptions(imported);
    result.params.keySet().removeIf(key -> isSetting(key) && key.startsWith("of"));
    for (Map.Entry<String, String> entry : source.params.entrySet()) {
      String key = entry.getKey();
      if (!isSetting(key)) continue;
      String value = entry.getValue();
      if (key.equals("o0") || key.equals("o2")) {
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

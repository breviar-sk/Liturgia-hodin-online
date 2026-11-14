package sk.breviar.android;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/** Appearance for bundled HTML pages that do not pass through the prayer renderer. */
final class StaticHtml {
  private static final Pattern HEAD_END = Pattern.compile("</head\\s*>", Pattern.CASE_INSENSITIVE);

  static byte[] style(InputStream input, String preferences) throws IOException {
    ByteArrayOutputStream bytes = new ByteArrayOutputStream();
    try (InputStream stream = input) {
      byte[] buffer = new byte[8192];
      int size;
      while ((size = stream.read(buffer)) != -1) bytes.write(buffer, 0, size);
    }
    String html = bytes.toString("UTF-8");
    String styles = appearance(new UrlOptions(preferences));
    Matcher head = HEAD_END.matcher(html);
    // Some linked psalm files are HTML fragments rather than complete documents.
    int position = head.find() ? head.start() : 0;
    return (html.substring(0, position) + styles + html.substring(position)).getBytes("UTF-8");
  }

  private static boolean enabled(UrlOptions options, String word, int bit, String override) {
    return options.getInt(override, options.hasBit(word, bit) ? 1 : 0) == 1;
  }

  private static void stylesheet(StringBuilder html, String name) {
    html.append("<link rel=\"stylesheet\" href=\"/").append(name).append(".css\">\n");
  }

  private static String appearance(UrlOptions options) {
    StringBuilder html = new StringBuilder();
    stylesheet(html, "breviar"); // Also supplies @font-face for installed fonts.
    boolean night = options.params.containsKey("c") && !options.params.get("c").isEmpty()
        ? options.isNightmode() : enabled(options, "o2", 8, "of2nr");
    if (night) stylesheet(html, "breviar-invert-colors");
    if (enabled(options, "o0", 6, "of0fn")) stylesheet(html, "breviar-normal-font");
    if (enabled(options, "o2", 16, "of2rc")) stylesheet(html, "breviar-rounded-corners");
    String background = night ? options.getBackgroundNightMode() : options.getBackgroundDayMode();
    html.append("<style id=\"static-page-appearance\">\n");
    // The stylesheets own the role-to-selector mapping, shared with CGI pages.
    html.append("html { ");
    String suffix = night ? "1" : "0";
    String[] parameters = {"ct" + suffix, "cr" + suffix, "c" + suffix};
    String[] roles = {"text", "rubric", "background"};
    for (int i = 0; i < parameters.length; ++i) {
      String color = options.getColor(parameters[i], "");
      if (!color.isEmpty()) html.append("--prayer-").append(roles[i]).append(": #").append(color).append("; ");
    }
    html.append("}\n");
    if (background.matches("[0-9a-fA-F]{6}")) {
      html.append("html, body { background-color: #").append(background).append("; }\n");
    }
    html.append("body { font-size: ").append(options.getFf()).append("pt; ")
        .append("line-height: ").append(options.getLh()).append("%; ")
        .append("margin-left: ").append(options.getMm()).append("px; ")
        .append("margin-right: ").append(options.getMm()).append("px; ");
    String font = options.getFont();
    if (font == null || font.isEmpty() || font.equals("podľa výberu")) {
      font = enabled(options, "o2", 2, "of2ff") ? "sans-serif" : "serif";
    }
    if (font.equals("podľa CSS")) font = "inherit";
    if (font.equals("serif") || font.equals("sans-serif") || font.equals("inherit")) {
      html.append("font-family: ").append(font).append(";");
    } else {
      // A font name is data, including quotes, newlines and HTML delimiters.
      String quoted = font.replace("\\", "\\\\").replace("'", "\\'")
          .replace("<", "\\3c ").replace("\n", "\\a ").replace("\r", "\\d ");
      html.append("font-family: '").append(quoted).append("';");
    }
    return html.append(" }\n</style>\n").toString();
  }

  private StaticHtml() {}
}

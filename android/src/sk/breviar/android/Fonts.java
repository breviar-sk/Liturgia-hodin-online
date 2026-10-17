package sk.breviar.android;

import android.content.Context;
import android.graphics.Typeface;
import android.graphics.fonts.Font;
import android.graphics.fonts.SystemFonts;
import android.os.Build;
import android.os.SystemClock;
import android.util.Log;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.TreeMap;
import java.util.Vector;

public class Fonts {
  public static class FontMap {
    public static class Variant {
      public Variant(String filename_, int weight_, int slant_) {
        filename = filename_;
        weight = weight_;
        slant = slant_;
      }

      String filename;
      int weight;
      int slant;
    }

    public static class Variants {
      public Variants(String family_name_) {
        variants = new Vector<Variant>();
        family_name = family_name_;
        display_font = null;
        css = null;
      }

      public void Add(Variant variant) {
        variants.add(variant);
        display_font = null;
        css = null;
      }

      public Variant GetDisplayFont() {
        if (display_font == null) {
          double best_score = 1e9;
          for (Variant v : variants) {
            double wdiff = v.weight - 400.0;
            double sdiff = v.slant;
            double score = wdiff * wdiff + sdiff * sdiff;
            if (score < best_score) {
              best_score = score;
              display_font = v;
            }
          }
        }
        return display_font;
      }

      public String GetCss() {
        if (css == null) {
          StringBuilder out = new StringBuilder();
          for (Variant v : variants) {
            out.append("@font-face {\n");

            out.append("  font-family: \"");
            out.append(family_name);
            out.append("\";\n");
            out.append("  src: url(\"/file");
            // Todo: Escape unexpected characters
            out.append(v.filename);
            out.append("\");\n");
            if (v.slant > 0) {
              out.append("  font-style: italic;\n");
            } else {
              out.append("  font-style: normal;\n");
            }
            out.append("  font-weight: ");
            out.append(v.weight);
            out.append(";\n");

            out.append("}\n");
          }
          css = out.toString();
        }
        return css;
      }

      String family_name;
      Vector<Variant> variants;
      Variant display_font;
      String css;
    }

    public TreeMap<String, Variants> families;

    public FontMap() {
      families = new TreeMap<String, Variants>();
    }

    static String parseFamily(String filename) {
      // Todo: use proper .ttf parsing from https://stackoverflow.com/questions/30034746/how-to-retrieve-font-name-from-ttf-file-for-android
      // Todo: Sanitize unexpected characters
      return filename
        .replaceAll("[^/]*/", "")
        .replaceFirst("\\.[^.]*$", "")
        .replaceFirst("-[^-]*$", "");
    }

    public void Insert(Variant font) {
      String family = parseFamily(font.filename);
      if (!families.containsKey(family)) {
        families.put(family, new Variants(family));
      }
      families.get(family).Add(font);
    }
  }

  /** A fully prepared, immutable choice; no font files are opened by the UI. */
  static final class Choice {
    final String family, css;
    final Typeface typeface;

    Choice(String family, Typeface typeface, String css) {
      this.family = family;
      this.typeface = typeface;
      this.css = css;
    }
  }

  private static FontMap systemFonts;
  private static Map<String, String> cachedFiles;
  private static List<Choice> cachedChoices;

  /** Worker-thread only. Reuse previews unless custom font files changed. */
  synchronized static List<Choice> getChoices(Context ctx) {
    LoadTiming timing = new LoadTiming("Font catalog");
    Map<String, String> files = storageFiles(ctx);
    timing.mark("custom font metadata read");
    if (cachedChoices != null && files.equals(cachedFiles)) {
      timing.mark("cache hit (" + cachedChoices.size() + " families)");
      return cachedChoices;
    }

    if (systemFonts == null) systemFonts = readSystemFonts();
    timing.mark("system fonts available");
    FontMap fonts = new FontMap();
    for (String filename : files.keySet()) addStorageFont(fonts, filename);
    for (FontMap.Variants family : systemFonts.families.values()) {
      for (FontMap.Variant variant : family.variants) fonts.Insert(variant);
    }
    List<Choice> choices = new ArrayList<>();
    for (Map.Entry<String, FontMap.Variants> entry : fonts.families.entrySet()) {
      long started = SystemClock.elapsedRealtime();
      try {
        Typeface preview = Typeface.createFromFile(entry.getValue().GetDisplayFont().filename);
        choices.add(new Choice(entry.getKey(), preview, entry.getValue().GetCss()));
      } catch (RuntimeException error) {
        Log.w("breviar", "Skipped font family " + entry.getKey(), error);
      }
      if (SystemClock.elapsedRealtime() - started >= 500) {
        timing.mark("slow preview: " + entry.getKey() + " ("
            + (SystemClock.elapsedRealtime() - started) + " ms)");
      }
    }
    cachedFiles = files;
    cachedChoices = Collections.unmodifiableList(choices);
    timing.mark("previews ready (" + choices.size() + " families)");
    return cachedChoices;
  }

  private static FontMap readSystemFonts() {
    FontMap fonts = new FontMap();
    if (Build.VERSION.SDK_INT >= 29) {
      for(Font font : SystemFonts.getAvailableFonts()) {
        if (!font.getLocaleList().isEmpty()) {
          // ignore non-latin fonts.
          continue;
        }
        java.io.File file = font.getFile();
        if (file == null) {
          Log.v("breviar", "font without file: " + font.toString());
          continue;
        }
        fonts.Insert(new FontMap.Variant(
              file.getAbsolutePath(),
              font.getStyle().getWeight(), font.getStyle().getSlant()));
      }
    }
    return fonts;
  }

  private static void addStorageFont(FontMap fonts, String filename) {
    String lowname = new File(filename).getName().toLowerCase(Locale.ROOT);
    boolean italic = lowname.contains("italic");
    boolean bold = lowname.contains("bold");
    if (!italic && !bold && !lowname.contains("regular")) {
      // Use it as all variants.
      fonts.Insert(new FontMap.Variant(filename, 400, 0));
      fonts.Insert(new FontMap.Variant(filename, 400, 1));
      fonts.Insert(new FontMap.Variant(filename, 700, 0));
      fonts.Insert(new FontMap.Variant(filename, 700, 1));
    } else {
      fonts.Insert(new FontMap.Variant(filename, bold ? 700 : 400, italic ? 1 : 0));
    }
  }

  private static Map<String, String> storageFiles(Context ctx) {
    Map<String, String> files = new TreeMap<>();
    File root = ctx.getExternalFilesDir(null);
    File[] entries = root == null ? null : root.listFiles();
    if (entries != null) {
      for (File file : entries) {
        if (file.isFile() && file.getName().endsWith(".ttf")) {
          files.put(file.getAbsolutePath(), file.length() + ":" + file.lastModified());
        }
      }
    }
    return files;
  }
}

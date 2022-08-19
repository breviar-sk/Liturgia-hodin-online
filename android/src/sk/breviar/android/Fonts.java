package sk.breviar.android;

import android.content.Context;
import android.graphics.fonts.Font;
import android.graphics.fonts.SystemFonts;
import android.graphics.fonts.FontStyle;
import android.os.Build;
import android.util.Log;

import java.io.File;
import java.util.Map;
import java.util.SortedMap;
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

    public void DebugDump() {
      for (Map.Entry<String, Variants> e : families.entrySet()) {
        Log.v("breviar", "font family: " + e.getKey());
        for (Variant v : e.getValue().variants) {
          Log.v("breviar", "  weight: " + v.weight +
                " slant: " + v.slant +
                " " + v.filename);
        }
      }
    }
  }

  static FontMap fonts = null;

  synchronized static void ResetFonts() {
    fonts = null;
  }

  synchronized static FontMap GetFonts(Context ctx) {
    if (fonts == null) {
      fonts = new FontMap();
      AddStorageFonts(ctx);
      AddSystemFonts();
      // Debug:
      fonts.DebugDump();
    }
    return fonts;
  }

  synchronized static void AddSystemFonts() {
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
  }

  private static void AddFontsFromDir(File dir) {
    Log.v("breviar", "AddFontsFromDir " + dir.getAbsolutePath());
    for (String name : dir.list()) {
      if (!name.endsWith(".ttf")) continue;

      File f = new File(dir, name);

      String filename = f.getAbsolutePath();

      // Todo: use proper .ttf parsing from https://stackoverflow.com/questions/30034746/how-to-retrieve-font-name-from-ttf-file-for-android
      String lowname = name.toLowerCase();
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
  }

  synchronized static void AddStorageFonts(Context ctx) {
    try {
      File root = ctx.getExternalFilesDir(null);
      AddFontsFromDir(root);
    } catch (java.lang.Exception e) {
      Log.v("breviar", "io exception: " + e.getMessage());
    }
  }
}

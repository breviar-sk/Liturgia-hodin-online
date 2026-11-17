package sk.breviar.android;

import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;
import androidx.appcompat.widget.Toolbar;
import com.google.zxing.WriterException;
import com.google.zxing.qrcode.decoder.ErrorCorrectionLevel;
import com.google.zxing.qrcode.encoder.ByteMatrix;
import com.google.zxing.qrcode.encoder.Encoder;
import java.util.Arrays;

/** Offline QR generation: no camera permission, upload, or URL-shortening service. */
public class PrayerShareActivity extends AppearanceActivity {
  @Override protected void attachBaseContext(Context context) {
    super.attachBaseContext(context);
    BreviarApp.applyCustomLocale(this);
  }

  static Bitmap qrCode(Context context, String url) throws WriterException {
    ByteMatrix matrix = null;
    // Prefer high correction for the badge. Retain the previous URL capacity
    // by falling back to Q/M only when a longer link cannot fit at H.
    for (ErrorCorrectionLevel level : new ErrorCorrectionLevel[]{ErrorCorrectionLevel.H,
        ErrorCorrectionLevel.Q, ErrorCorrectionLevel.M}) {
      try {
        matrix = Encoder.encode(url, level).getMatrix();
        break;
      } catch (WriterException tooLong) {
        if (level == ErrorCorrectionLevel.M) throw tooLong;
      }
    }
    int modules = matrix.getWidth(), size = 768;
    int scale = size / (modules + 8), offset = (size - modules * scale) / 2;
    int[] pixels = new int[size * size];
    Arrays.fill(pixels, Color.WHITE); // Includes the four-module quiet zone.
    for (int y = 0; y < modules * scale; ++y) {
      for (int x = 0; x < modules * scale; ++x) {
        if (matrix.get(x / scale, y / scale) != 0) pixels[(offset + y) * size + offset + x] = Color.BLACK;
      }
    }
    // Match the web SVG: an odd, centered badge about 1/8 of the code width,
    // including one white module on each side. Keep the rest of the QR intact.
    int badge = Math.max(5, (modules / 8) | 1), start = offset + (modules - badge) / 2 * scale;
    for (int y = start; y < start + badge * scale; ++y)
      Arrays.fill(pixels, y * size + start, y * size + start + badge * scale, Color.WHITE);
    BitmapFactory.Options options = new BitmapFactory.Options();
    options.inScaled = false;
    Bitmap icon = BitmapFactory.decodeResource(context.getResources(), R.drawable.icon, options);
    int width = icon.getWidth(), height = icon.getHeight(), iconSize = (badge - 2) * scale;
    int[] artwork = new int[width * height];
    icon.getPixels(artwork, 0, width, 0, 0, width, height);
    for (int y = 0; y < iconSize; ++y) {
      for (int x = 0; x < iconSize; ++x) {
        int color = artwork[(y * height / iconSize) * width + x * width / iconSize];
        int alpha = Color.alpha(color), white = 255 * (255 - alpha);
        pixels[(start + scale + y) * size + start + scale + x] = Color.rgb(
            (Color.red(color) * alpha + white) / 255,
            (Color.green(color) * alpha + white) / 255,
            (Color.blue(color) * alpha + white) / 255);
      }
    }
    icon.recycle();
    return Bitmap.createBitmap(pixels, size, size, Bitmap.Config.ARGB_8888);
  }

  @Override public void onCreate(Bundle state) {
    super.onCreate(state);
    String url = getIntent().getStringExtra("url");
    if (url == null) {
      finish();
      return;
    }
    setContentView(R.layout.prayer_share);
    setSupportActionBar((Toolbar)findViewById(R.id.share_toolbar));
    getSupportActionBar().setTitle(R.string.share_prayer);
    getSupportActionBar().setDisplayHomeAsUpEnabled(true);
    getSupportActionBar().setHomeAsUpIndicator(R.drawable.ic_action_cancel);
    // Use the native settings palette even if reader firmware overrides the
    // inherited foreground. Reader day/night colors do not style native menus.
    int foreground = BreviarApp.getEinkMode(this) ? Color.BLACK : Color.WHITE;
    for (int id : new int[]{R.id.share_message, R.id.copy_link, R.id.share_link}) {
      TextView text = findViewById(id);
      text.setTextColor(foreground);
      text.setTypeface(android.graphics.Typeface.create("sans-serif", android.graphics.Typeface.NORMAL));
    }
    try {
      ImageView qr = findViewById(R.id.share_qr);
      BitmapDrawable image = new BitmapDrawable(getResources(), qrCode(this, url));
      image.setFilterBitmap(false);
      qr.setImageDrawable(image);
    } catch (WriterException | IllegalArgumentException error) {
      ((TextView)findViewById(R.id.share_message)).setText(R.string.share_prayer_unavailable);
      findViewById(R.id.share_qr).setVisibility(View.GONE);
    }
    findViewById(R.id.share_link).setOnClickListener(v -> startActivity(Intent.createChooser(
            new Intent(Intent.ACTION_SEND).setType("text/plain").putExtra(Intent.EXTRA_TEXT, url),
            getString(R.string.share_link))));
    findViewById(R.id.copy_link).setOnClickListener(v -> {
          ((ClipboardManager)getSystemService(Context.CLIPBOARD_SERVICE))
              .setPrimaryClip(ClipData.newPlainText(getString(R.string.share_prayer), url));
          Toast.makeText(this, R.string.link_copied, Toast.LENGTH_SHORT).show();
    });
  }

  @Override public boolean onSupportNavigateUp() {
    finish();
    return true;
  }
}

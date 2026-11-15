package sk.breviar.android;

import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;
import androidx.appcompat.widget.Toolbar;
import com.google.zxing.BarcodeFormat;
import com.google.zxing.EncodeHintType;
import com.google.zxing.WriterException;
import com.google.zxing.common.BitMatrix;
import com.google.zxing.qrcode.QRCodeWriter;
import com.google.zxing.qrcode.decoder.ErrorCorrectionLevel;
import java.util.EnumMap;
import java.util.Map;

/** Offline QR generation: no camera permission, upload, or URL-shortening service. */
public class PrayerShareActivity extends AppearanceActivity {
  @Override protected void attachBaseContext(Context context) {
    super.attachBaseContext(context);
    BreviarApp.applyCustomLocale(this);
  }

  static Bitmap qrCode(String url) throws WriterException {
    Map<EncodeHintType, Object> hints = new EnumMap<>(EncodeHintType.class);
    hints.put(EncodeHintType.ERROR_CORRECTION, ErrorCorrectionLevel.M);
    hints.put(EncodeHintType.MARGIN, 4);
    BitMatrix matrix = new QRCodeWriter().encode(url, BarcodeFormat.QR_CODE, 768, 768, hints);
    int width = matrix.getWidth(), height = matrix.getHeight();
    int[] pixels = new int[width * height];
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) pixels[y * width + x] = matrix.get(x, y) ? Color.BLACK : Color.WHITE;
    }
    return Bitmap.createBitmap(pixels, width, height, Bitmap.Config.ARGB_8888);
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
      BitmapDrawable image = new BitmapDrawable(getResources(), qrCode(url));
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

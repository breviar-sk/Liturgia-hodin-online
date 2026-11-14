package sk.breviar.android;

import android.app.Dialog;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;
import androidx.appcompat.app.AlertDialog;
import com.google.zxing.BarcodeFormat;
import com.google.zxing.EncodeHintType;
import com.google.zxing.WriterException;
import com.google.zxing.common.BitMatrix;
import com.google.zxing.qrcode.QRCodeWriter;
import com.google.zxing.qrcode.decoder.ErrorCorrectionLevel;
import java.util.EnumMap;
import java.util.Map;

/** Offline QR generation: no camera permission, upload, or URL-shortening service. */
public class PrayerShareDialog extends SystemFontDialogFragment {
  static final String TAG = "share-prayer";

  static PrayerShareDialog create(String url) {
    PrayerShareDialog dialog = new PrayerShareDialog();
    Bundle args = new Bundle();
    args.putString("url", url);
    dialog.setArguments(args);
    return dialog;
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

  @Override public Dialog onCreateDialog(Bundle state) {
    String url = requireArguments().getString("url");
    Context context = requireContext();
    LinearLayout content = new LinearLayout(context);
    content.setOrientation(LinearLayout.VERTICAL);
    int padding = (int)(16 * getResources().getDisplayMetrics().density);
    content.setPadding(padding, padding, padding, padding);
    content.setBackgroundColor(Color.WHITE);
    TextView message = new TextView(context);
    message.setText(R.string.share_prayer_message);
    message.setTextColor(Color.BLACK);
    content.addView(message);
    try {
      ImageView qr = new ImageView(context);
      BitmapDrawable image = new BitmapDrawable(getResources(), qrCode(url));
      image.setFilterBitmap(false);
      qr.setImageDrawable(image);
      qr.setAdjustViewBounds(true);
      qr.setContentDescription(getString(R.string.share_prayer));
      content.addView(qr, new LinearLayout.LayoutParams(
          ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
    } catch (WriterException error) {
      message.setText(R.string.share_prayer_unavailable);
    }
    TextView link = new TextView(context);
    link.setText(url);
    link.setTextColor(Color.BLACK);
    link.setTextIsSelectable(true);
    content.addView(link);
    ScrollView scroll = new ScrollView(context);
    scroll.addView(content);
    return new AlertDialog.Builder(context, R.style.AppearanceChooserTheme)
        .setTitle(R.string.share_prayer)
        .setView(scroll)
        .setPositiveButton(R.string.share_link, (dialog, which) -> startActivity(Intent.createChooser(
            new Intent(Intent.ACTION_SEND).setType("text/plain").putExtra(Intent.EXTRA_TEXT, url),
            getString(R.string.share_link))))
        .setNeutralButton(R.string.copy_link, (dialog, which) -> {
          ((ClipboardManager)context.getSystemService(Context.CLIPBOARD_SERVICE))
              .setPrimaryClip(ClipData.newPlainText(getString(R.string.share_prayer), url));
          Toast.makeText(context, R.string.link_copied, Toast.LENGTH_SHORT).show();
        })
        .setNegativeButton(android.R.string.cancel, null)
        .create();
  }
}

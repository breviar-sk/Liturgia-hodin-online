package sk.breviar.android;

import static org.junit.Assert.*;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.os.Looper;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.widget.ScrollView;
import android.widget.ImageView;
import androidx.appcompat.widget.Toolbar;
import com.google.zxing.BinaryBitmap;
import com.google.zxing.RGBLuminanceSource;
import com.google.zxing.common.HybridBinarizer;
import com.google.zxing.qrcode.QRCodeReader;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.Shadows;
import org.robolectric.android.controller.ActivityController;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.GraphicsMode;
import org.robolectric.annotation.LooperMode;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = {24, 35}, shadows = XmlSettingsActivityTest.SettingsServer.class)
@LooperMode(LooperMode.Mode.PAUSED)
@GraphicsMode(GraphicsMode.Mode.NATIVE)
public class PrayerShareActivityTest {
  private final Context context = RuntimeEnvironment.getApplication();

  @Before public void configure() {
    BreviarApp.setString(context, "version", context.getString(R.string.version));
    BreviarApp.setEinkMode(context, false);
    BreviarApp.setUrlOptions(context, "&amp;j=sk&amp;o0=8835&amp;o1=1123143&amp;o2=29432&amp;o3=28&amp;o4=0&amp;o5=0&amp;o6=11000000000");
  }

  @Test public void generatedQrDecodesToTheExactPortablePrayerUrl() throws Exception {
    String url = PrayerLink.share("http://127.0.0.1/l.cgi?qt=plo&lo=5&t=28&dvt=3&lr=C&p=mpc",
        BreviarApp.getUrlOptions(context), "sk");
    Bitmap image = PrayerShareActivity.qrCode(url);
    assertEquals(url, decode(image));
  }

  private static String decode(Bitmap image) throws Exception {
    int size = image.getWidth();
    int[] pixels = new int[size * size];
    image.getPixels(pixels, 0, size, 0, 0, size, size);
    return new QRCodeReader().decode(new BinaryBitmap(new HybridBinarizer(
        new RGBLuminanceSource(size, size, pixels)))).getText();
  }

  @Test public void drawerShowsQrAndCopiesOrSharesTheSameUrlInBothAppearances() throws Exception {
    for (boolean eink : new boolean[]{false, true}) {
      BreviarApp.setEinkMode(context, eink);
      try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
        Breviar reader = controller.get();
        reader.onNavigationItemSelected(R.id.share_prayer);
        Intent intent = Shadows.shadowOf(reader).getNextStartedActivity();
        assertEquals(PrayerShareActivity.class.getName(), intent.getComponent().getClassName());
        try (ActivityController<PrayerShareActivity> screen = Robolectric.buildActivity(PrayerShareActivity.class, intent).setup().visible()) {
          PrayerShareActivity activity = screen.get();
          ScrollView scroll = activity.findViewById(R.id.share_scroll);
          assertTrue(isInside(scroll, activity.findViewById(R.id.share_qr)));
          assertTrue(isInside(scroll, activity.findViewById(R.id.copy_link)));
          assertTrue(isInside(scroll, activity.findViewById(R.id.share_link)));
          Toolbar toolbar = activity.findViewById(R.id.share_toolbar);
          assertNotNull(toolbar.getNavigationIcon());
          assertEquals(context.getString(R.string.share_prayer), toolbar.getTitle());
          assertEquals(eink ? Color.BLACK : Color.WHITE,
              ((android.widget.TextView)activity.findViewById(R.id.share_message)).getCurrentTextColor());
          assertEquals(Color.WHITE, ((ColorDrawable)activity.findViewById(R.id.share_qr).getBackground()).getColor());
          ImageView qr = activity.findViewById(R.id.share_qr);
          assertNull(qr.getColorFilter());
          // Decode the displayed ImageView after e-ink styling, not merely the
          // original bitmap: a tint can turn a valid QR into a solid rectangle.
          qr.layout(0, 0, 768, 768);
          Bitmap displayed = Bitmap.createBitmap(768, 768, Bitmap.Config.ARGB_8888);
          qr.draw(new Canvas(displayed));
          assertEquals(intent.getStringExtra("url"), decode(displayed));
          activity.findViewById(R.id.copy_link).performClick();
          Shadows.shadowOf(Looper.getMainLooper()).idle();
          ClipboardManager clipboard = (ClipboardManager)context.getSystemService(Context.CLIPBOARD_SERVICE);
          String copied = clipboard.getPrimaryClip().getItemAt(0).getText().toString();
          assertTrue(copied.startsWith("https://breviar.sk/cgi-bin/l.cgi?"));
          assertTrue(copied.contains("qt=pdnes"));
          // Recreation keeps the same share target without modifying reader settings.
          String options = BreviarApp.getUrlOptions(context);
          screen.recreate();
          activity = screen.get();
          activity.findViewById(R.id.share_link).performClick();
          Shadows.shadowOf(Looper.getMainLooper()).idle();
          Intent chooser = Shadows.shadowOf(activity).getNextStartedActivity();
          Intent shared = chooser.getParcelableExtra(Intent.EXTRA_INTENT);
          assertEquals(Intent.ACTION_SEND, shared.getAction());
          assertEquals("text/plain", shared.getType());
          assertEquals(copied, shared.getStringExtra(Intent.EXTRA_TEXT));
          assertEquals(options, BreviarApp.getUrlOptions(context));
          activity.onSupportNavigateUp();
          assertTrue(activity.isFinishing());
        }
      }
    }
  }
  private static boolean isInside(android.view.View parent, android.view.View child) {
    for (android.view.ViewParent p = child.getParent(); p != null; p = p.getParent()) {
      if (p == parent) return true;
    }
    return false;
  }
}

package sk.breviar.android;

import static org.junit.Assert.*;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.net.Uri;
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
    Bitmap image = PrayerShareActivity.qrCode(context, url);
    assertEquals(url, decode(image));
  }

  @Test public void brandedCodesRemainReadableAcrossLinkLengths() throws Exception {
    for (int length : new int[]{60, 150, 400, 900, 1350, 1800, 1990}) {
      StringBuilder text = new StringBuilder("https://breviar.sk/cgi-bin/l.cgi?qt=pst&st=1&j=sk&sh=1#");
      while (text.length() < length) text.append("abcdefghijklmnopqrstuvwxyz0123456789");
      String url = text.substring(0, length);
      Bitmap image = PrayerShareActivity.qrCode(context, url);
      // The app artwork must actually be present; a plain QR also decodes.
      assertTrue(hasColor(image));
      assertEquals(url, decode(image));
      // Optional artifacts for scanning resized previews with an independent
      // decoder; the Java detector also rejects some unbranded resampled codes.
      String folder = System.getProperty("breviar.qr.previews");
      if (folder != null) {
        java.io.File outputFolder = new java.io.File(folder);
        outputFolder.mkdirs();
        try (java.io.FileOutputStream output = new java.io.FileOutputStream(
            new java.io.File(outputFolder, "android-" + length + ".png"))) {
          image.compress(Bitmap.CompressFormat.PNG, 100, output);
        }
      }
    }
  }

  private static boolean hasColor(Bitmap image) {
    int center = image.getWidth() / 2;
    for (int y = center - 80; y < center + 80; ++y) {
      for (int x = center - 80; x < center + 80; ++x) {
        int color = image.getPixel(x, y);
        if (Color.red(color) != Color.green(color) || Color.green(color) != Color.blue(color)) return true;
      }
    }
    return false;
  }

  private static String decode(Bitmap image) throws Exception {
    int size = image.getWidth();
    int[] pixels = new int[size * size];
    image.getPixels(pixels, 0, size, 0, 0, size, size);
    return new QRCodeReader().decode(new BinaryBitmap(new HybridBinarizer(
        new RGBLuminanceSource(size, size, pixels)))).getText();
  }

  @Test public void marianAntiphonsCanBeSharedFromTheReaderAndOpenedAgain() throws Exception {
    BreviarApp.markSharedAppearanceOffered(context);
    try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
      Breviar reader = controller.get();
      reader.wv.loadUrl("http://127.0.0.1:50000/l.cgi?qt=pst&st=1#rsnk");
      // The test reader has no JNI response to publish the resolved settings.
      Breviar.S.setOpts(BreviarApp.getUrlOptions(context));
      reader.onNavigationItemSelected(R.id.share_prayer);
      Intent activity = Shadows.shadowOf(reader).getNextStartedActivity();
      assertEquals(PrayerShareActivity.class.getName(), activity.getComponent().getClassName());
      String url = activity.getStringExtra("url");
      assertEquals("rsnk", Uri.parse(url).getFragment());
      assertEquals(url, decode(PrayerShareActivity.qrCode(context, url)));
      assertTrue(reader.handleIntent(new Intent(Intent.ACTION_VIEW, Uri.parse(url))));
      UrlOptions opened = new UrlOptions(reader.wv.getUrl(), true);
      assertEquals("pst", opened.params.get("qt"));
      assertEquals("1", opened.params.get("st"));
      assertFalse(opened.params.containsKey("p"));
      assertEquals("rsnk", Uri.parse(reader.wv.getUrl()).getFragment());
      assertTrue(SharedPrayerSession.active(context));
      controller.recreate();
      assertEquals("rsnk", Uri.parse(controller.get().wv.getUrl()).getFragment());
      controller.get().restoreSharedSettings();
      assertEquals("rsnk", Uri.parse(controller.get().wv.getUrl()).getFragment());
    }
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
          assertTrue(hasColor(displayed));
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

package sk.breviar.android;

import static org.junit.Assert.*;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.os.Looper;
import androidx.appcompat.app.AlertDialog;
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
public class PrayerShareDialogTest {
  private final Context context = RuntimeEnvironment.getApplication();

  @Before public void configure() {
    BreviarApp.setString(context, "version", context.getString(R.string.version));
    BreviarApp.setEinkMode(context, false);
    BreviarApp.setUrlOptions(context, "&amp;j=sk&amp;o0=8835&amp;o1=1123143&amp;o2=29432&amp;o3=28&amp;o4=0&amp;o5=0&amp;o6=11000000000");
  }

  @Test public void generatedQrDecodesToTheExactPortablePrayerUrl() throws Exception {
    String url = PrayerLink.share("http://127.0.0.1/l.cgi?qt=plo&lo=5&t=28&dvt=3&lr=C&p=mpc",
        BreviarApp.getUrlOptions(context), "sk");
    Bitmap image = PrayerShareDialog.qrCode(url);
    int size = image.getWidth();
    int[] pixels = new int[size * size];
    image.getPixels(pixels, 0, size, 0, 0, size, size);
    String decoded = new QRCodeReader().decode(new BinaryBitmap(new HybridBinarizer(
        new RGBLuminanceSource(size, size, pixels)))).getText();
    assertEquals(url, decoded);
  }

  private AlertDialog show(Breviar reader) {
    reader.onNavigationItemSelected(R.id.share_prayer);
    Shadows.shadowOf(Looper.getMainLooper()).idle();
    PrayerShareDialog fragment = (PrayerShareDialog)reader.getSupportFragmentManager().findFragmentByTag(PrayerShareDialog.TAG);
    assertNotNull(fragment);
    return (AlertDialog)fragment.requireDialog();
  }

  @Test public void drawerShowsQrAndCopiesOrSharesTheSameUrlInBothAppearances() {
    for (boolean eink : new boolean[]{false, true}) {
      BreviarApp.setEinkMode(context, eink);
      try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
        Breviar reader = controller.get();
        AlertDialog dialog = show(reader);
        dialog.getButton(AlertDialog.BUTTON_NEUTRAL).performClick();
        Shadows.shadowOf(Looper.getMainLooper()).idle();
        ClipboardManager clipboard = (ClipboardManager)context.getSystemService(Context.CLIPBOARD_SERVICE);
        String copied = clipboard.getPrimaryClip().getItemAt(0).getText().toString();
        assertTrue(copied.startsWith("https://breviar.sk/cgi-bin/l.cgi?"));
        assertTrue(copied.contains("qt=pdnes"));
        dialog = show(reader);
        dialog.getButton(AlertDialog.BUTTON_POSITIVE).performClick();
        Shadows.shadowOf(Looper.getMainLooper()).idle();
        Intent chooser = Shadows.shadowOf(reader).getNextStartedActivity();
        Intent shared = chooser.getParcelableExtra(Intent.EXTRA_INTENT);
        assertEquals(Intent.ACTION_SEND, shared.getAction());
        assertEquals("text/plain", shared.getType());
        assertEquals(copied, shared.getStringExtra(Intent.EXTRA_TEXT));
      }
    }
  }
}

package sk.breviar.android;

import static org.junit.Assert.*;
import android.content.Context;
import android.graphics.Typeface;
import android.net.Uri;
import android.os.Bundle;
import android.os.Looper;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import org.junit.Test;
import org.junit.Before;
import org.junit.runner.RunWith;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.Shadows;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.Implementation;
import org.robolectric.annotation.Implements;
import org.robolectric.annotation.LooperMode;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = {24, 35}, shadows = SharedPrayerImportTest.FontResolver.class)
@LooperMode(LooperMode.Mode.PAUSED)
public class SharedPrayerImportTest {
  private final Context context = RuntimeEnvironment.getApplication();

  @Before public void resetResolver() {
    FontResolver.calls = 0;
    FontResolver.entered = null;
    FontResolver.release = null;
  }

  @Implements(value = Fonts.class, isInAndroidSdk = false)
  public static class FontResolver {
    static CountDownLatch entered, release;
    static int calls;

    @Implementation protected static Fonts.Choice findChoice(Context context, String family) {
      assertNotSame(Looper.getMainLooper().getThread(), Thread.currentThread());
      ++calls;
      if (entered != null) {
        entered.countDown();
        try {
          assertTrue(release.await(5, TimeUnit.SECONDS));
        } catch (InterruptedException error) { throw new AssertionError(error); }
      }
      return family.equals("Missing") ? null : new Fonts.Choice("Test Font", Typeface.SERIF, "local-font-css");
    }
  }

  static void drain() throws Exception {
    Fonts.worker.submit(() -> {}).get(5, TimeUnit.SECONDS);
    Shadows.shadowOf(Looper.getMainLooper()).idle();
  }

  private Uri link(String parameters) {
    return Uri.parse("https://breviar.sk/cgi-bin/l.cgi?qt=pdt&d=13&m=11&r=2026&p=mv&" + parameters);
  }

  @Test public void ignoredAppearanceNeverLoadsFontsOrRejectsTheirValues() {
    List<SharedPrayerImport.Ready> received = new ArrayList<>();
    SharedPrayerImport importer = new SharedPrayerImport(context, received::add);
    assertTrue(importer.open(link("f=%3Cinvalid%3E&cr1=bad-color&c=1"), false));
    assertEquals(1, received.size());
    assertNull(received.get(0).link.getFont());
    assertNull(received.get(0).link.params.get("cr1"));
    assertEquals(0, FontResolver.calls);
    importer.close();
  }

  @Test public void importedFontsUseOnlyLocalCssAndMissingFontsRetainTheCurrentFont() throws Exception {
    List<SharedPrayerImport.Ready> received = new ArrayList<>();
    SharedPrayerImport importer = new SharedPrayerImport(context, received::add);
    for (String family : new String[]{"Test%20Font", "Missing"}) {
      assertTrue(importer.open(link("f=" + family), true));
      drain();
    }
    assertEquals("Test Font", received.get(0).link.getFont());
    assertEquals("local-font-css", received.get(0).fontCss);
    assertNull(received.get(1).link.getFont());
    assertNull(received.get(1).fontCss);
    importer.close();
  }

  @Test public void canceledFontResultsCannotReplaceANewerLink() throws Exception {
    List<SharedPrayerImport.Ready> received = new ArrayList<>();
    SharedPrayerImport importer = new SharedPrayerImport(context, received::add);
    FontResolver.entered = new CountDownLatch(1);
    FontResolver.release = new CountDownLatch(1);
    try {
      assertTrue(importer.open(link("f=Test%20Font"), true));
      assertTrue(FontResolver.entered.await(5, TimeUnit.SECONDS));
      assertTrue(importer.open(link("f=serif&c=1"), true));
      FontResolver.release.countDown();
      drain();
      assertEquals(1, received.size());
      assertEquals("serif", received.get(0).link.getFont());
      assertEquals("", received.get(0).fontCss);
    } finally {
      FontResolver.release.countDown();
      importer.close();
    }
  }

  @Test public void pendingImportRestoresItsCapturedPolicyAfterRecreation() throws Exception {
    List<SharedPrayerImport.Ready> received = new ArrayList<>();
    SharedPrayerImport previous = new SharedPrayerImport(context, received::add);
    SharedPrayerImport replacement = new SharedPrayerImport(context, received::add);
    FontResolver.entered = new CountDownLatch(1);
    FontResolver.release = new CountDownLatch(1);
    try {
      assertTrue(previous.open(link("f=Test%20Font&c=1"), true));
      assertTrue(FontResolver.entered.await(5, TimeUnit.SECONDS));
      Bundle saved = new Bundle();
      previous.save(saved);
      previous.close();
      BreviarApp.setSharedAppearance(context, false);
      assertTrue(replacement.restore(saved));
      FontResolver.release.countDown();
      drain();
      assertEquals(1, received.size());
      assertTrue(received.get(0).appearance);
      assertEquals("Test Font", received.get(0).link.getFont());
      assertEquals("1", received.get(0).link.params.get("c"));
    } finally {
      FontResolver.release.countDown();
      previous.close();
      replacement.close();
    }
  }
}

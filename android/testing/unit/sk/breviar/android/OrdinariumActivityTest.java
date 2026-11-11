package sk.breviar.android;

import static org.junit.Assert.*;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.view.Menu;
import android.webkit.WebView;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.Shadows;
import org.robolectric.android.controller.ActivityController;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.Implementation;
import org.robolectric.annotation.Implements;
import org.robolectric.annotation.LooperMode;
import org.robolectric.util.ReflectionHelpers;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = {24, 35}, shadows = OrdinariumActivityTest.NoNative.class)
@LooperMode(LooperMode.Mode.PAUSED)
public class OrdinariumActivityTest {
  private final Context context = RuntimeEnvironment.getApplication();

  @Implements(value = Server.class, isInAndroidSdk = false)
  public static class NoNative {
    @Implementation protected static void __staticInitializer__() {}
  }

  @Test public void drawerEntryAndAllFiveChoicesReturnToTheReader() {
    try (ActivityController<OrdinariumActivity> controller =
        Robolectric.buildActivity(OrdinariumActivity.class).setup()) {
      OrdinariumActivity activity = controller.get();
      Menu menu = activity.navigationView.getMenu();
      String[] prayers = {"mi", "mrch", "mpc", "mv", "mk"};
      int[] labels = {R.string.inv, R.string.rch, R.string.read, R.string.vesp, R.string.kompl};
      assertEquals(5, menu.size());
      for (int i = 0; i < prayers.length; ++i) {
        assertEquals(activity.getString(labels[i]), menu.getItem(i).getTitle().toString());
        menu.performIdentifierAction(menu.getItem(i).getItemId(), 0);
        assertEquals(Activity.RESULT_OK, Shadows.shadowOf(activity).getResultCode());
        assertEquals(prayers[i], Shadows.shadowOf(activity).getResultIntent().getStringExtra("ordinarium_prayer"));
        assertTrue(activity.isFinishing());
        assertNull(Shadows.shadowOf(activity).getNextStartedActivity());
      }
      menu.clear();
      activity.getMenuInflater().inflate(R.menu.menu, menu);
      assertNotNull(menu.findItem(R.id.menu_ordinarium));
      assertFalse(menu.findItem(R.id.menu_ordinarium).hasSubMenu());
    }
  }

  @Test @Config(qualifiers = "en")
  public void selectionLoadsStyledCgiInMainWebViewInPrayerLanguage() {
    Server previous = Breviar.S;
    Breviar.S = ReflectionHelpers.callConstructor(Server.class,
        ReflectionHelpers.ClassParameter.from(Context.class, context));
    Breviar.S.port = 49999;
    String options = "&amp;c=1&amp;c1=123456&amp;f=Custom Font&amp;ff=26&amp;d=9&amp;m=11&amp;r=2026&amp;ds=1";
    BreviarApp.setUrlOptions(context, options);
    BreviarApp.setOverrideLocale(context, false);
    Breviar reader = Robolectric.buildActivity(Breviar.class).get();
    reader.wv = new WebView(context);
    try {
      for (String language : new String[]{"sk", "cz", "c2", "hu", "la", "is"}) {
        BreviarApp.setString(context, "language", language);
        for (String prayer : new String[]{"mi", "mrch", "mpc", "mv", "mk"}) {
          reader.onActivityResult(Breviar.ORDINARIUM_REQUEST, Activity.RESULT_OK,
              new Intent().putExtra("ordinarium_prayer", prayer));
          Uri url = Uri.parse(Shadows.shadowOf(reader.wv).getLastLoadedUrl());
          assertEquals(49999, url.getPort());
          assertEquals("/l.cgi", url.getPath());
          assertEquals("pst", url.getQueryParameter("qt"));
          assertEquals("2", url.getQueryParameter("st"));
          assertEquals(prayer, url.getQueryParameter("p"));
          assertEquals(language, url.getQueryParameter("j"));
          assertEquals("1", url.getQueryParameter("c"));
          assertEquals("123456", url.getQueryParameter("c1"));
          assertEquals("26", url.getQueryParameter("ff"));
          assertEquals("Custom Font", url.getQueryParameter("f"));
          for (String key : new String[]{"d", "m", "r", "ds"}) assertNull(url.getQueryParameter(key));
          assertFalse(reader.need_to_reload_preferences);
        }
      }
      String loaded = Shadows.shadowOf(reader.wv).getLastLoadedUrl();
      reader.onActivityResult(Breviar.ORDINARIUM_REQUEST, Activity.RESULT_CANCELED, null);
      reader.openOrdinarium("../invalid");
      assertEquals(loaded, Shadows.shadowOf(reader.wv).getLastLoadedUrl());
      assertEquals(options, BreviarApp.getUrlOptions(context));
    } finally {
      reader.wv.destroy();
      Breviar.S = previous;
    }
  }
}

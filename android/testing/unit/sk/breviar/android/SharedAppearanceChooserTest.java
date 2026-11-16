package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.net.Uri;
import android.os.Looper;
import android.widget.TextView;
import androidx.appcompat.app.AlertDialog;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.Shadows;
import org.robolectric.android.controller.ActivityController;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.LooperMode;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = {24, 35}, shadows = XmlSettingsActivityTest.SettingsServer.class)
@LooperMode(LooperMode.Mode.PAUSED)
public class SharedAppearanceChooserTest {
  private final Context context = RuntimeEnvironment.getApplication();
  private static final String MINE = "&amp;j=sk&amp;o1=31&amp;f=Custom&amp;c=1";
  private static final String LINK = "https://breviar.sk/cgi-bin/l.cgi?qt=pdt&d=12&m=11&r=2026&p=mv&j=la&o1=7&f=serif&c=0";

  @Before public void configure() {
    BreviarApp.setString(context, "version", context.getString(R.string.version));
    BreviarApp.setEinkMode(context, false);
    BreviarApp.setString(context, "language", "sk");
    BreviarApp.setUrlOptions(context, MINE);
  }

  private static Intent link(String url) { return new Intent(Intent.ACTION_VIEW, Uri.parse(url)); }

  private static SharedAppearanceChooser chooser(Breviar reader) {
    return (SharedAppearanceChooser)reader.getSupportFragmentManager()
        .findFragmentByTag(SharedAppearanceChooser.TAG);
  }

  private static AlertDialog dialog(Breviar reader) {
    assertNotNull(chooser(reader));
    AlertDialog dialog = (AlertDialog)chooser(reader).requireDialog();
    assertTrue(dialog.isShowing());
    return dialog;
  }

  private static void choose(Breviar reader, boolean appearance) {
    dialog(reader).getButton(appearance ? AlertDialog.BUTTON_POSITIVE : AlertDialog.BUTTON_NEGATIVE).performClick();
    Shadows.shadowOf(Looper.getMainLooper()).idle();
  }

  private void assertImported(Breviar reader, boolean appearance, String prayer) {
    assertNull(chooser(reader));
    assertTrue(SharedPrayerSession.active(context));
    assertEquals(appearance, BreviarApp.getSharedAppearance(context));
    UrlOptions page = new UrlOptions(reader.wv.getUrl(), true);
    assertEquals(prayer, page.params.get("p"));
    assertEquals("7", page.params.get("o1"));
    assertEquals(appearance ? "serif" : "Custom", page.getFont());
    assertEquals(!appearance, page.isNightmode());
  }

  @Test public void firstWarmLinkWaitsForTheAnswerAndRemembersBothChoices() {
    for (boolean eink : new boolean[]{false, true}) {
      for (boolean appearance : new boolean[]{false, true}) {
        context.getSharedPreferences(Util.prefname, 0).edit().clear().commit();
        configure();
        BreviarApp.setEinkMode(context, eink);
        BreviarApp.markHighContrastOffered(context);
        try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
          Breviar reader = controller.get();
          assertNull(chooser(reader));
          String previousPage = reader.wv.getUrl();
          assertTrue(reader.handleIntent(link(LINK)));
          TextView message = dialog(reader).findViewById(android.R.id.message);
          assertEquals(Color.BLACK, message.getCurrentTextColor());
          assertTrue(message.getText().toString().contains(reader.getString(R.string.settings)
              + " > " + reader.getString(R.string.settings_title)));
          assertTrue(BreviarApp.wasSharedAppearanceOffered(context));
          assertFalse(chooser(reader).isCancelable());
          assertEquals(previousPage, reader.wv.getUrl());
          assertEquals(MINE, BreviarApp.getUrlOptions(context));
          assertFalse(SharedPrayerSession.active(context));
          choose(reader, appearance);
          assertImported(controller.get(), appearance, "mv");
          controller.get().restoreSharedSettings();
        }
        // Restarting the app, or changing the Device switch, must not ask again.
        BreviarApp.setSharedAppearance(context, !appearance);
        try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class, link(LINK)).setup()) {
          assertImported(controller.get(), !appearance, "mv");
        }
      }
    }
  }

  @Test public void coldLinkAndANewerLinkSurviveAnUnansweredDialogRecreation() {
    // Existing users who have explicitly set the switch still get the explanation once.
    BreviarApp.setSharedAppearance(context, true);
    try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class, link(LINK + "#section")).setup()) {
      dialog(controller.get());
      controller.newIntent(link(LINK.replace("p=mv", "p=mrch") + "#new-section"));
      controller.recreate();
      dialog(controller.get());
      assertFalse(SharedPrayerSession.active(context));
      assertEquals(MINE, BreviarApp.getUrlOptions(context));
      choose(controller.get(), false);
      assertImported(controller.get(), false, "mrch");
      assertEquals("new-section", Uri.parse(controller.get().wv.getUrl()).getFragment());
      controller.recreate();
      assertImported(controller.get(), false, "mrch");
      assertEquals("new-section", Uri.parse(controller.get().wv.getUrl()).getFragment());
    }
  }

  @Test public void firstInstallSequencesAppearanceSharingAndChangelogDialogs() {
    context.getSharedPreferences(Util.prefname, 0).edit().remove(BreviarApp.booleanEinkMode)
        .remove("version").commit();
    try (ActivityController<AppearanceChooserTest.Reader> controller = Robolectric.buildActivity(AppearanceChooserTest.Reader.class, link(LINK)).setup()) {
      Breviar reader = controller.get();
      assertNull(chooser(reader));
      AppearanceChooser appearance = (AppearanceChooser)reader.getSupportFragmentManager().findFragmentByTag(AppearanceChooser.TAG);
      assertNotNull(appearance);
      ((AlertDialog)appearance.requireDialog()).getButton(AlertDialog.BUTTON_POSITIVE).performClick();
      Shadows.shadowOf(Looper.getMainLooper()).idle();
      dialog(controller.get());
      assertEquals(0, controller.get().changelogs);
      choose(controller.get(), false);
      assertImported(controller.get(), false, "mv");
      assertEquals(1, controller.get().changelogs);
    }
  }

  @Test public void invalidLinksDoNotUseUpTheNotification() {
    try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
      assertFalse(controller.get().handleIntent(link(LINK.replace("breviar.sk", "example.org"))));
      assertNull(chooser(controller.get()));
      assertFalse(BreviarApp.wasSharedAppearanceOffered(context));
      assertTrue(controller.get().handleIntent(link(LINK)));
      dialog(controller.get());
    }
  }

  @Test public void aLinkReceivedWithSavedFragmentStateWaitsUntilResume() {
    try (ActivityController<EinkModeTest.Reader> controller = Robolectric.buildActivity(EinkModeTest.Reader.class).setup()) {
      controller.pause().saveInstanceState(new android.os.Bundle()).stop();
      assertTrue(controller.get().handleIntent(link(LINK)));
      assertNull(chooser(controller.get()));
      assertFalse(BreviarApp.wasSharedAppearanceOffered(context));
      controller.restart().start().resume();
      dialog(controller.get());
      choose(controller.get(), true);
      assertImported(controller.get(), true, "mv");
    }
  }
}

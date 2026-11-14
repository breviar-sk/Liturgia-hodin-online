package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
import android.graphics.Color;
import android.graphics.Typeface;
import android.os.Looper;
import android.widget.CompoundButton;
import android.widget.TextView;
import androidx.appcompat.app.AlertDialog;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.TimeUnit;
import org.junit.After;
import org.junit.Before;
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
@Config(sdk = {24, 35}, shadows = HighContrastPromptTest.SettingsServer.class)
@LooperMode(LooperMode.Mode.PAUSED)
public class HighContrastPromptTest {
  private final Context context = RuntimeEnvironment.getApplication();

  @Implements(value = Server.class, isInAndroidSdk = false)
  public static class SettingsServer {
    static boolean missingNight;
    static String dayRubric;
    static CountDownLatch entered, release;
    @Implementation protected static void __staticInitializer__() {}
    @Implementation protected static String getSettingsXml(Context context, String options, String language)
        throws Exception {
      assertNotSame(Looper.getMainLooper().getThread(), Thread.currentThread());
      entered.countDown();
      assertTrue("XML load timed out", release.await(10, TimeUnit.SECONDS));
      String xml = XmlSettingsActivityTest.settingsXml(true);
      String presets = "<MenuGroup Key='contrast' Label='High contrast'>"
          + preset("day", "0", new String[]{"000000", dayRubric, "ffffff"})
          + (missingNight ? "" : preset("night", "1", new String[]{"ffffff", "ffff00", "000000"}))
          + "</MenuGroup>";
      return xml.replace("</Menu>", presets + "</Menu>");
    }

    private static String preset(String mode, String suffix, String[] colors) {
      String xml = "<MenuItem Key='appearance.colors." + mode + ".high-contrast' Label='High contrast' Control='preset'>";
      String[] parameters = {"ct" + suffix, "cr" + suffix, "c" + suffix};
      for (int i = 0; i < parameters.length; ++i) {
        xml += "<Set Parameter='" + parameters[i] + "' Value='" + colors[i] + "'/>";
      }
      return xml + "</MenuItem>";
    }
  }

  public static class Reader extends EinkModeTest.Reader {
    int changelogs;
    @Override void showChangelog(boolean showOk) { ++changelogs; }
  }

  @Before public void configure() {
    BreviarApp.setString(context, "version", context.getString(R.string.version));
    SettingsServer.missingNight = false;
    SettingsServer.dayRubric = "800000";
    SettingsServer.entered = new CountDownLatch(1);
    SettingsServer.release = new CountDownLatch(0);
  }

  @After public void releaseWorker() { SettingsServer.release.countDown(); }

  private static void idle() { Shadows.shadowOf(Looper.getMainLooper()).idle(); }

  static HighContrastPrompt prompt(AppearanceActivity activity) {
    return (HighContrastPrompt)activity.getSupportFragmentManager().findFragmentByTag(HighContrastPrompt.TAG);
  }

  private static AlertDialog dialog(AppearanceActivity activity) {
    assertNotNull(prompt(activity));
    return (AlertDialog)prompt(activity).requireDialog();
  }

  static void decline(AppearanceActivity activity) {
    dialog(activity).getButton(AlertDialog.BUTTON_NEGATIVE).performClick();
    idle();
  }

  private static void await(HighContrastPrompt prompt) throws Exception {
    ExecutorService worker = ReflectionHelpers.getField(prompt, "worker");
    worker.submit(() -> {}).get(10, TimeUnit.SECONDS);
    idle();
  }

  @Test public void existingEinkUsersAreAskedBeforeChangelogAndNoPersistsAcrossRestartsAndUpgrades() {
    BreviarApp.setEinkMode(context, true);
    BreviarApp.setString(context, "version", "previous-version");
    String saved = "&amp;c=1&amp;f=Georgia&amp;ct0=123456&amp;c1=abcdef";
    BreviarApp.setUrlOptions(context, saved);
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      Reader reader = controller.get();
      assertTrue(dialog(reader).isShowing());
      assertTrue(BreviarApp.wasHighContrastOffered(context));
      assertEquals(0, reader.changelogs);
      decline(reader);
      assertEquals(saved, BreviarApp.getUrlOptions(context));
      assertEquals(1, reader.changelogs);
      assertNull(prompt(reader));
      controller.recreate();
      assertNull(prompt(controller.get()));
    }
    BreviarApp.setString(context, "version", "another-version");
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      assertNull(prompt(controller.get()));
      assertEquals(1, controller.get().changelogs);
    }
  }

  @Test public void yesUsesBothXmlPresetsAndPreservesLiveReaderOptionsAndPosition() throws Exception {
    BreviarApp.setEinkMode(context, true);
    BreviarApp.setUrlOptions(context, "&amp;c=0&amp;f=Saved");
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      Reader reader = controller.get();
      reader.need_to_reload_preferences = false;
      Breviar.S.setOpts("&amp;c=1&amp;f=Live&amp;k=sj&amp;o0=123&amp;ct0=123456&amp;c1=abcdef");
      reader.scroll_to = 0.37f;
      SettingsServer.dayRubric = "654321"; // Catalogue changes must need no Android changes.
      HighContrastPrompt offer = prompt(reader);
      dialog(reader).getButton(AlertDialog.BUTTON_POSITIVE).performClick();
      await(offer);
      assertNull(prompt(reader));
      UrlOptions saved = new UrlOptions(BreviarApp.getUrlOptions(context));
      assertEquals("000000", saved.params.get("ct0"));
      assertEquals("654321", saved.params.get("cr0"));
      assertEquals("ffffff", saved.params.get("c0"));
      assertEquals("ffffff", saved.params.get("ct1"));
      assertEquals("ffff00", saved.params.get("cr1"));
      assertEquals("000000", saved.params.get("c1"));
      assertEquals("Live", saved.params.get("f"));
      assertEquals("1", saved.params.get("c"));
      assertEquals("sj", saved.params.get("k"));
      assertEquals("123", saved.params.get("o0"));
      assertEquals("654321", new UrlOptions(Breviar.S.getOpts()).params.get("cr0"));
      assertEquals("000000", new UrlOptions(reader.wv.getUrl(), true).params.get("c1"));
      assertEquals(0.37f, reader.scroll_to, 0f);
      reader.syncPreferences();
      assertEquals("654321", new UrlOptions(BreviarApp.getUrlOptions(context)).params.get("cr0"));
    }
  }

  @Test public void normalUsersWaitUntilEinkIsEnabledAndAreNeverAskedAgain() {
    BreviarApp.setEinkMode(context, false);
    try (ActivityController<DeviceSettings> controller = Robolectric.buildActivity(DeviceSettings.class).setup()) {
      XmlSettingsActivityTest.awaitSettings(controller.get());
      assertNull(prompt(controller.get()));
      assertFalse(BreviarApp.wasHighContrastOffered(context));
      int offers = 0;
      for (boolean eink : new boolean[]{true, false, true}) {
        ((CompoundButton)controller.get().menuItem("device.eink").getActionView()).performClick();
        idle();
        XmlSettingsActivityTest.awaitSettings(controller.get());
        assertEquals(eink, BreviarApp.getEinkMode(context));
        if (eink && prompt(controller.get()) != null) {
          ++offers;
          decline(controller.get());
        }
        else assertNull(prompt(controller.get()));
        assertTrue(BreviarApp.wasHighContrastOffered(context));
      }
      assertEquals(1, offers);
    }
  }

  @Test public void freshInstallOffersContrastOnlyAfterChoosingEink() {
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      assertNull(prompt(controller.get()));
      AppearanceChooser chooser = (AppearanceChooser)controller.get().getSupportFragmentManager()
          .findFragmentByTag(AppearanceChooser.TAG);
      assertNotNull(chooser);
      ((AlertDialog)chooser.requireDialog()).getButton(AlertDialog.BUTTON_NEGATIVE).performClick();
      idle();
      assertTrue(BreviarApp.getEinkMode(context));
      assertNotNull(prompt(controller.get()));
      assertNull(controller.get().getSupportFragmentManager().findFragmentByTag(AppearanceChooser.TAG));
    }
  }

  @Test public void unansweredDialogSurvivesRecreationWithoutDuplicatesAndUsesSystemFont() {
    BreviarApp.setEinkMode(context, true);
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      controller.recreate();
      idle();
      assertEquals(1, controller.get().getSupportFragmentManager().getFragments().size());
      AlertDialog dialog = dialog(controller.get());
      TextView message = dialog.findViewById(android.R.id.message);
      assertEquals(Color.BLACK, message.getCurrentTextColor());
      assertEquals(Typeface.create("sans-serif", Typeface.NORMAL), message.getTypeface());
      dialog.onBackPressed();
      idle();
      assertTrue(dialog.isShowing());
      decline(controller.get());
      controller.recreate();
      assertNull(prompt(controller.get()));
    }
  }

  @Test public void slowLoadDoesNotBlockTheUiAndNoCancelsWithoutApplyingColors() throws Exception {
    BreviarApp.setEinkMode(context, true);
    String saved = "&amp;ct0=123456&amp;c1=abcdef";
    BreviarApp.setUrlOptions(context, saved);
    SettingsServer.release = new CountDownLatch(1);
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      dialog(controller.get()).getButton(AlertDialog.BUTTON_POSITIVE).performClick();
      assertTrue(SettingsServer.entered.await(10, TimeUnit.SECONDS));
      assertFalse(dialog(controller.get()).getButton(AlertDialog.BUTTON_POSITIVE).isEnabled());
      assertTrue(dialog(controller.get()).getButton(AlertDialog.BUTTON_NEGATIVE).isEnabled());
      decline(controller.get());
      SettingsServer.release.countDown();
      assertEquals(saved, BreviarApp.getUrlOptions(context));
      assertNull(prompt(controller.get()));
    }
  }

  @Test public void missingPresetDoesNotPartiallyApplyAndRetryCanSucceed() throws Exception {
    BreviarApp.setEinkMode(context, true);
    String saved = "&amp;ct0=123456&amp;c1=abcdef";
    BreviarApp.setUrlOptions(context, saved);
    SettingsServer.missingNight = true;
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      HighContrastPrompt offer = prompt(controller.get());
      dialog(controller.get()).getButton(AlertDialog.BUTTON_POSITIVE).performClick();
      await(offer);
      assertEquals(saved, BreviarApp.getUrlOptions(context));
      assertTrue(dialog(controller.get()).getButton(AlertDialog.BUTTON_POSITIVE).isEnabled());
      SettingsServer.missingNight = false;
      dialog(controller.get()).getButton(AlertDialog.BUTTON_POSITIVE).performClick();
      await(offer);
      assertNull(prompt(controller.get()));
      assertEquals("000000", new UrlOptions(BreviarApp.getUrlOptions(context)).params.get("ct0"));
    }
  }

  @Test public void enablingEinkInSettingsCanApplyBothPresetsWithoutReopeningTheApp() throws Exception {
    BreviarApp.setEinkMode(context, false);
    BreviarApp.setUrlOptions(context, "&amp;c=0&amp;f=Georgia&amp;c0=abcdef");
    try (ActivityController<DeviceSettings> controller = Robolectric.buildActivity(DeviceSettings.class).setup()) {
      XmlSettingsActivityTest.awaitSettings(controller.get());
      ((CompoundButton)controller.get().menuItem("device.eink").getActionView()).performClick();
      idle();
      XmlSettingsActivityTest.awaitSettings(controller.get());
      HighContrastPrompt offer = prompt(controller.get());
      dialog(controller.get()).getButton(AlertDialog.BUTTON_POSITIVE).performClick();
      await(offer);
      XmlSettingsActivityTest.awaitSettings(controller.get());
      UrlOptions saved = controller.get().options();
      assertEquals("000000", saved.params.get("ct0"));
      assertEquals("800000", saved.params.get("cr0"));
      assertEquals("ffffff", saved.params.get("c0"));
      assertEquals("ffffff", saved.params.get("ct1"));
      assertEquals("ffff00", saved.params.get("cr1"));
      assertEquals("000000", saved.params.get("c1"));
      assertEquals("0", saved.params.get("c"));
      assertEquals("Georgia", saved.params.get("f"));
      assertNull(prompt(controller.get()));
    }
  }

  @Test public void pendingPreferencesTakePriorityOverTheOlderReaderSnapshot() throws Exception {
    BreviarApp.setEinkMode(context, true);
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      Reader reader = controller.get();
      Breviar.S.setOpts("&amp;f=Old&amp;c=0");
      BreviarApp.setUrlOptions(context, "&amp;f=Pending&amp;c=1");
      reader.need_to_reload_preferences = true;
      HighContrastPrompt offer = prompt(reader);
      dialog(reader).getButton(AlertDialog.BUTTON_POSITIVE).performClick();
      await(offer);
      UrlOptions saved = new UrlOptions(BreviarApp.getUrlOptions(context));
      assertEquals("Pending", saved.params.get("f"));
      assertEquals("1", saved.params.get("c"));
      assertFalse(reader.need_to_reload_preferences);
    }
  }

  @Test public void acceptingSurvivesRecreationWhileTheCatalogueLoads() throws Exception {
    BreviarApp.setEinkMode(context, true);
    SettingsServer.release = new CountDownLatch(1);
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      HighContrastPrompt original = prompt(controller.get());
      dialog(controller.get()).getButton(AlertDialog.BUTTON_POSITIVE).performClick();
      assertTrue(SettingsServer.entered.await(10, TimeUnit.SECONDS));
      controller.recreate();
      idle();
      HighContrastPrompt restored = prompt(controller.get());
      assertNotSame(original, restored);
      assertFalse(dialog(controller.get()).getButton(AlertDialog.BUTTON_POSITIVE).isEnabled());
      SettingsServer.release.countDown();
      await(restored);
      assertNull(prompt(controller.get()));
      assertEquals("000000", new UrlOptions(BreviarApp.getUrlOptions(context)).params.get("ct0"));
    }
  }
}

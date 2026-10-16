package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Build;
import android.os.Bundle;
import android.os.Looper;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import androidx.appcompat.app.AlertDialog;
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
public class AppearanceChooserTest {
  private final Context context = RuntimeEnvironment.getApplication();

  public static class Reader extends EinkModeTest.Reader {
    int changelogs;
    @Override void showChangelog(boolean showOk) {
      assertFalse("Changelog must use the chosen appearance", appearanceChanged());
      ++changelogs;
      super.showChangelog(showOk);
    }
  }

  private static void idle() { Shadows.shadowOf(Looper.getMainLooper()).idle(); }

  private static AppearanceChooser chooser(Reader reader) {
    return (AppearanceChooser)reader.getSupportFragmentManager().findFragmentByTag(AppearanceChooser.TAG);
  }

  private static AlertDialog dialog(Reader reader) {
    assertNotNull(chooser(reader));
    AlertDialog dialog = (AlertDialog)chooser(reader).requireDialog();
    assertTrue(dialog.isShowing());
    return dialog;
  }

  private static void choose(Reader reader, boolean eink) {
    dialog(reader).getButton(eink ? AlertDialog.BUTTON_NEGATIVE : AlertDialog.BUTTON_POSITIVE).performClick();
    idle();
  }

  @Test public void freshInstallAsksBeforeChangelogAndNormalChoicePersistsAcrossUpgrades() {
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      Reader original = controller.get();
      dialog(original);
      assertEquals(0, original.changelogs);
      assertEquals("", BreviarApp.getString(context, "version", ""));
      assertFalse(BreviarApp.hasAppearanceChoice(context));
      choose(original, false);
      assertSame(original, controller.get());
      assertNull(chooser(original));
      assertTrue(BreviarApp.hasAppearanceChoice(context));
      assertFalse(BreviarApp.getEinkMode(context));
      assertEquals(1, original.changelogs);
    }
    try (ActivityController<Reader> restart = Robolectric.buildActivity(Reader.class).setup()) {
      assertNull(chooser(restart.get()));
      assertEquals(0, restart.get().changelogs);
    }
    BreviarApp.setString(context, "version", "old-version");
    try (ActivityController<Reader> upgrade = Robolectric.buildActivity(Reader.class).setup()) {
      assertNull(chooser(upgrade.get()));
      assertFalse(BreviarApp.getEinkMode(context));
      assertEquals(1, upgrade.get().changelogs);
    }
  }

  @Test public void einkChoiceRecreatesBeforeChangelogAndPreservesReadingState() {
    BreviarApp.setUrlOptions(context, "&amp;c=1&amp;f=Georgia");
    context.getSharedPreferences(Util.prefname, 0).edit()
        .putBoolean("fullscreen", true).putInt("scale", 135).commit();
    Bundle saved = new Bundle();
    saved.putString("wv-url", "http://127.0.0.1:50000/l.cgi?qt=pdt&d=14&m=10&r=2026&p=1");
    saved.putFloat("wv-scroll-to", 0.4f);
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class)
        .create(saved).start().restoreInstanceState(saved).postCreate(saved).resume().visible()) {
      Reader original = controller.get();
      choose(original, true);
      Reader reader = controller.get();
      assertNotSame(original, reader);
      assertEquals(0, original.changelogs);
      assertEquals(1, reader.changelogs);
      assertTrue(BreviarApp.getEinkMode(context));
      assertNull(chooser(reader));
      assertEquals(Color.WHITE, ((ColorDrawable)reader.toolbar.getBackground()).getColor());
      assertTrue(reader.fullscreen);
      assertEquals(135, reader.scale);
      assertEquals(0.4f, reader.scroll_to, 0.001f);
      assertTrue(reader.wv.getUrl().contains("d=14"));
      assertTrue(reader.wv.getUrl().contains("p=1"));
      assertTrue(new UrlOptions(Breviar.S.getOpts()).isNightmode());
    }
    try (ActivityController<Reader> restart = Robolectric.buildActivity(Reader.class).setup()) {
      assertNull(chooser(restart.get()));
      assertEquals(0, restart.get().changelogs);
      assertTrue(BreviarApp.getEinkMode(context));
    }
  }

  @Test public void upgradeWithoutExplicitModeAsksAndRetainsPreferences() {
    BreviarApp.setString(context, "version", "old-version");
    String options = "&amp;c=1&amp;o0=123&amp;f=Georgia";
    BreviarApp.setUrlOptions(context, options);
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      dialog(controller.get());
      assertEquals(0, controller.get().changelogs);
      assertEquals("old-version", BreviarApp.getString(context, "version", ""));
      choose(controller.get(), false);
      assertEquals(options, BreviarApp.getUrlOptions(context));
      assertEquals(1, controller.get().changelogs);
    }
  }

  @Test public void existingExplicitModesSkipChooserOnUpgrade() {
    for (boolean eink : new boolean[]{false, true}) {
      BreviarApp.setEinkMode(context, eink);
      BreviarApp.setString(context, "version", "old-version");
      try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
        assertNull(chooser(controller.get()));
        assertEquals(eink, BreviarApp.getEinkMode(context));
        assertFalse(controller.get().appearanceChanged());
        assertEquals(1, controller.get().changelogs);
      }
    }
  }

  @Test public void unansweredChooserSurvivesRecreationAndBackDoesNotSaveAnImplicitChoice() {
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      dialog(controller.get()).onBackPressed();
      idle();
      dialog(controller.get());
      assertFalse(BreviarApp.hasAppearanceChoice(context));
      controller.recreate();
      idle();
      dialog(controller.get());
      assertEquals(1, controller.get().getSupportFragmentManager().getFragments().size());
      assertEquals(0, controller.get().changelogs);
      choose(controller.get(), false);
      controller.recreate();
      idle();
      assertNull(chooser(controller.get()));
      assertEquals(0, controller.get().changelogs);
    }
  }

  private static void assertBlackText(View view) {
    if (view instanceof TextView && ((TextView)view).getText().length() > 0) {
      assertEquals(((TextView)view).getText().toString(), Color.BLACK, ((TextView)view).getCurrentTextColor());
    }
    if (view instanceof ViewGroup) {
      ViewGroup group = (ViewGroup)view;
      for (int i = 0; i < group.getChildCount(); ++i) assertBlackText(group.getChildAt(i));
    }
  }

  @Test @Config(qualifiers = "night")
  public void chooserHasBlackTextOnWhiteEvenWithSystemNightMode() {
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      AlertDialog dialog = dialog(controller.get());
      assertBlackText(dialog.getWindow().getDecorView());
      TypedArray appearance = dialog.getContext().obtainStyledAttributes(
          new int[]{android.R.attr.windowBackground, android.R.attr.backgroundDimEnabled});
      try {
        assertEquals(Color.WHITE, ((ColorDrawable)appearance.getDrawable(0)).getColor());
        assertFalse(appearance.getBoolean(1, true));
      } finally {
        appearance.recycle();
      }
      if (Build.VERSION.SDK_INT >= 29) assertFalse(dialog.getWindow().getDecorView().isForceDarkAllowed());
    }
  }
}

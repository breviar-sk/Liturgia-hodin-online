package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.os.Looper;
import android.widget.CompoundButton;
import androidx.lifecycle.Lifecycle;
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
public class AppearanceChangesTest {
  private final Context context = RuntimeEnvironment.getApplication();

  private static void idle() { Shadows.shadowOf(Looper.getMainLooper()).idle(); }

  private static void toggle(DeviceSettings activity) {
    if (activity.menuItem("device.eink") == null) XmlSettingsActivityTest.awaitSettings(activity);
    ((CompoundButton)activity.menuItem("device.eink").getActionView()).performClick();
  }

  @Test public void rebuildsCoveredScreensBeforeBackAndPreservesReaderStateInBothDirections() {
    BreviarApp.setString(context, "version", context.getString(R.string.version));
    BreviarApp.setUrlOptions(context, "&amp;c=1&amp;f=Georgia");
    context.getSharedPreferences(Util.prefname, 0).edit().putBoolean("fullscreen", true).commit();
    Bundle saved = new Bundle();
    saved.putString("wv-url", "http://127.0.0.1:50000/l.cgi?qt=pdt&d=14&m=10&r=2026&p=1");
    saved.putFloat("wv-scroll-to", 0.4f);
    try (ActivityController<EinkModeTest.Reader> reader = Robolectric.buildActivity(EinkModeTest.Reader.class)
        .create(saved).start().restoreInstanceState(saved).postCreate(saved).resume().visible()) {
      reader.get().scale = 135;
      reader.get().syncPreferences();
      reader.get().need_to_reload_preferences = true;
      reader.pause().stop();
      try (ActivityController<MainSettings> parent = Robolectric.buildActivity(MainSettings.class).setup()) {
        parent.pause().stop();
        try (ActivityController<DeviceSettings> device = Robolectric.buildActivity(DeviceSettings.class).setup()) {
          idle();
          for (boolean eink : new boolean[]{true, false}) {
            EinkModeTest.Reader oldReader = reader.get();
            MainSettings oldParent = parent.get();
            DeviceSettings oldDevice = device.get();
            Server oldServer = Breviar.S;
            toggle(oldDevice);
            idle();
            assertNotSame(oldReader, reader.get());
            assertNotSame(oldParent, parent.get());
            assertNotSame(oldDevice, device.get());
            assertNotSame(oldServer, Breviar.S);
            assertFalse(reader.get().appearanceChanged());
            assertFalse(parent.get().appearanceChanged());
            assertFalse(device.get().appearanceChanged());
            // No Back or resume of either covered screen was needed.
            assertEquals(Lifecycle.State.CREATED, reader.get().getLifecycle().getCurrentState());
            assertEquals(Lifecycle.State.CREATED, parent.get().getLifecycle().getCurrentState());
            assertEquals(eink, BreviarApp.getEinkMode(context));
            int toolbar = ((ColorDrawable)reader.get().toolbar.getBackground()).getColor();
            if (eink) assertEquals(Color.WHITE, toolbar);
            else assertNotEquals(Color.WHITE, toolbar);
            assertTrue(reader.get().fullscreen);
            assertEquals(135, reader.get().scale);
            assertEquals(0.4f, reader.get().scroll_to, 0.001f);
            assertTrue(reader.get().wv.getUrl().contains("d=14"));
            assertTrue(reader.get().wv.getUrl().contains("p=1"));
            assertTrue(new UrlOptions(Breviar.S.getOpts()).isNightmode());
            assertFalse(device.get().isFinishing());
          }
        }
      }
    }
  }

  /** Hold one parent's asynchronous recreation to exercise a very quick Back. */
  public static class HeldSettings extends SettingsActivity {
    int requests;
    @Override void recreateForAppearance() { ++requests; }
  }

  private void immediateBack(boolean toolbar) {
    try (ActivityController<HeldSettings> parent = Robolectric.buildActivity(HeldSettings.class).setup()) {
      parent.pause().stop();
      try (ActivityController<DeviceSettings> device = Robolectric.buildActivity(DeviceSettings.class).setup()) {
        idle();
        DeviceSettings oldDevice = device.get();
        Shadows.shadowOf(oldDevice).setIsTaskRoot(false);
        toggle(oldDevice);
        if (toolbar) oldDevice.onSupportNavigateUp();
        else oldDevice.getOnBackPressedDispatcher().onBackPressed();
        // Repeated Back while waiting must not accidentally close the parent.
        if (toolbar) oldDevice.onSupportNavigateUp();
        else oldDevice.getOnBackPressedDispatcher().onBackPressed();
        assertFalse(oldDevice.isFinishing());
        idle();
        assertEquals(1, parent.get().requests);
        assertSame(oldDevice, device.get());
        assertFalse(oldDevice.isFinishing());
        // Once the parent is ready, finish exactly the replacement of the
        // originally requested screen, not its destroyed predecessor.
        parent.recreate();
        idle();
        assertFalse(parent.get().appearanceChanged());
        assertNotSame(oldDevice, device.get());
        assertTrue(device.get().isFinishing());
        assertFalse(parent.get().isFinishing());
        assertEquals(0, Shadows.shadowOf(device.get()).getPendingTransitionEnterAnimationResourceId());
        assertEquals(0, Shadows.shadowOf(device.get()).getPendingTransitionExitAnimationResourceId());
      }
    }
  }

  @Test public void immediateToolbarUpWaitsForTheCoveredParent() { immediateBack(true); }
  @Test public void immediateSystemBackWaitsForTheCoveredParent() { immediateBack(false); }

  @Test public void rapidSwitchBackKeepsLatestChoiceWithoutUnnecessaryRecreation() {
    try (ActivityController<DeviceSettings> device = Robolectric.buildActivity(DeviceSettings.class).setup()) {
      idle();
      DeviceSettings original = device.get();
      toggle(original);
      toggle(original);
      idle();
      assertFalse(BreviarApp.getEinkMode(context));
      assertSame(original, device.get());
      original.onSupportNavigateUp();
      assertTrue(original.isFinishing());
    }
  }

  @Test public void destroyedCoveredActivityDoesNotBlockReturn() {
    ActivityController<HeldSettings> parent = Robolectric.buildActivity(HeldSettings.class).setup();
    parent.pause().stop();
    try (ActivityController<DeviceSettings> device = Robolectric.buildActivity(DeviceSettings.class).setup()) {
      idle();
      toggle(device.get());
      device.get().onSupportNavigateUp();
      idle();
      parent.destroy();
      idle();
      assertFalse(device.get().appearanceChanged());
      assertTrue(device.get().isFinishing());
    }
  }

  @Test public void changingChoiceDuringParentRecreationUsesLatestMode() {
    try (ActivityController<HeldSettings> parent = Robolectric.buildActivity(HeldSettings.class).setup()) {
      parent.pause().stop();
      try (ActivityController<DeviceSettings> device = Robolectric.buildActivity(DeviceSettings.class).setup()) {
        idle();
        DeviceSettings original = device.get();
        toggle(original);
        idle();
        assertEquals(1, parent.get().requests);
        toggle(original);
        original.onSupportNavigateUp();
        assertFalse(original.isFinishing());
        parent.recreate();
        idle();
        assertFalse(BreviarApp.getEinkMode(context));
        assertFalse(parent.get().appearanceChanged());
        assertSame(original, device.get());
        assertTrue(original.isFinishing());
      }
    }
  }

  @Test public void ordinaryBackDoesNotTriggerAppearanceRecreation() {
    try (ActivityController<DeviceSettings> device = Robolectric.buildActivity(DeviceSettings.class).setup()) {
      idle();
      DeviceSettings original = device.get();
      original.onSupportNavigateUp();
      assertTrue(original.isFinishing());
      idle();
      assertSame(original, device.get());
    }
  }
}

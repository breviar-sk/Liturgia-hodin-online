package sk.breviar.android;

import static org.junit.Assert.*;

import android.app.Activity;
import android.app.AutomaticZenRule;
import android.app.NotificationManager;
import android.app.NotificationManager.Policy;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.Looper;
import android.provider.Settings;
import android.service.notification.Condition;
import android.service.notification.ConditionProviderService;
import android.service.notification.ZenPolicy;
import android.widget.CompoundButton;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.Shadows;
import org.robolectric.android.controller.ActivityController;
import org.robolectric.android.controller.ServiceController;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.Implementation;
import org.robolectric.annotation.Implements;
import org.robolectric.annotation.LooperMode;
import org.robolectric.shadows.ShadowNotificationManager;
import org.robolectric.shadows.ShadowService;
import org.robolectric.util.ReflectionHelpers;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = {24, 28, 29, 35}, shadows = DoNotDisturbTest.Provider.class)
@LooperMode(LooperMode.Mode.PAUSED)
public class DoNotDisturbTest {
  @Implements(ConditionProviderService.class)
  public static class Provider extends ShadowService {
    static final List<Condition> conditions = new ArrayList<>();
    @Implementation protected void notifyCondition(Condition condition) { conditions.add(condition); }
  }

  private BreviarApp app;
  private NotificationManager notifications;
  private ShadowNotificationManager shadow;
  private Policy previous;

  @Before public void setup() {
    Provider.conditions.clear();
    app = (BreviarApp)RuntimeEnvironment.getApplication();
    notifications = (NotificationManager)app.getSystemService(Context.NOTIFICATION_SERVICE);
    shadow = Shadows.shadowOf(notifications);
    shadow.setNotificationPolicyAccessGranted(true);
    previous = new Policy(Policy.PRIORITY_CATEGORY_CALLS | Policy.PRIORITY_CATEGORY_ALARMS,
        Policy.PRIORITY_SENDERS_STARRED, Policy.PRIORITY_SENDERS_CONTACTS, 0);
    notifications.setNotificationPolicy(previous);
    notifications.setInterruptionFilter(NotificationManager.INTERRUPTION_FILTER_ALL);
  }

  private static void idle() { Shadows.shadowOf(Looper.getMainLooper()).idle(); }

  private AutomaticZenRule rule() {
    Map<String, AutomaticZenRule> rules = notifications.getAutomaticZenRules();
    assertEquals(1, rules.size());
    return rules.values().iterator().next();
  }

  private int conditionState() {
    return ReflectionHelpers.callInstanceMethod(shadow, "getAutomaticZenRuleState",
        ReflectionHelpers.ClassParameter.from(String.class,
            notifications.getAutomaticZenRules().keySet().iterator().next()));
  }

  private void assertReadingPolicy(boolean speaking) {
    assertEquals(Build.VERSION.SDK_INT < 28 && !speaking
        ? NotificationManager.INTERRUPTION_FILTER_NONE : NotificationManager.INTERRUPTION_FILTER_PRIORITY,
        rule().getInterruptionFilter());
    if (Build.VERSION.SDK_INT >= 29) {
      ZenPolicy policy = rule().getZenPolicy();
      assertEquals(speaking ? ZenPolicy.STATE_ALLOW : ZenPolicy.STATE_DISALLOW, policy.getPriorityCategoryMedia());
      assertEquals(ZenPolicy.STATE_DISALLOW, policy.getPriorityCategoryCalls());
      assertEquals(ZenPolicy.STATE_DISALLOW, policy.getPriorityCategoryMessages());
      assertEquals(ZenPolicy.STATE_DISALLOW, policy.getPriorityCategoryRepeatCallers());
      assertEquals(ZenPolicy.STATE_DISALLOW, policy.getPriorityCategoryAlarms());
      assertEquals(ZenPolicy.STATE_DISALLOW, policy.getPriorityCategoryEvents());
      assertEquals(ZenPolicy.STATE_DISALLOW, policy.getPriorityCategoryReminders());
      assertEquals(ZenPolicy.STATE_DISALLOW, policy.getPriorityCategorySystem());
      assertEquals(ZenPolicy.STATE_DISALLOW, policy.getVisualEffectFullScreenIntent());
      assertEquals(ZenPolicy.STATE_DISALLOW, policy.getVisualEffectPeek());
      assertEquals(ZenPolicy.STATE_DISALLOW, policy.getVisualEffectStatusBar());
      assertEquals(ZenPolicy.STATE_DISALLOW, policy.getVisualEffectNotificationList());
      assertEquals(ZenPolicy.STATE_DISALLOW, policy.getVisualEffectLights());
      assertEquals(ZenPolicy.STATE_DISALLOW, policy.getVisualEffectBadge());
      assertEquals(ZenPolicy.STATE_DISALLOW, policy.getVisualEffectAmbient());
      if (Build.VERSION.SDK_INT >= 30) {
        assertEquals(ZenPolicy.CONVERSATION_SENDERS_NONE, policy.getPriorityConversationSenders());
      }
      if (Build.VERSION.SDK_INT >= 35) assertEquals(ZenPolicy.STATE_DISALLOW, policy.getPriorityChannelsAllowed());
      assertEquals(previous, notifications.getNotificationPolicy());
      assertEquals(Condition.STATE_TRUE, conditionState());
    } else {
      Policy policy = notifications.getNotificationPolicy();
      assertEquals(Build.VERSION.SDK_INT >= 28 && speaking ? Policy.PRIORITY_CATEGORY_MEDIA : 0, policy.priorityCategories);
      int popupFlags = Policy.SUPPRESSED_EFFECT_SCREEN_ON | Policy.SUPPRESSED_EFFECT_SCREEN_OFF;
      assertEquals(popupFlags, policy.suppressedVisualEffects & popupFlags);
      if (Build.VERSION.SDK_INT >= 28) {
        assertTrue((policy.suppressedVisualEffects & Policy.SUPPRESSED_EFFECT_NOTIFICATION_LIST) != 0);
        assertTrue((policy.suppressedVisualEffects & Policy.SUPPRESSED_EFFECT_STATUS_BAR) != 0);
      }
    }
  }

  @Test public void readingSuppressesNotificationsAndMediaAndRestoresOnExit() {
    BreviarApp.setMute(app, true);
    try (ActivityController<Activity> activity = Robolectric.buildActivity(Activity.class).setup()) {
      assertTrue(rule().isEnabled());
      assertReadingPolicy(false);
      assertEquals(NotificationManager.INTERRUPTION_FILTER_ALL, notifications.getCurrentInterruptionFilter());
    }
    idle();
    assertFalse(rule().isEnabled());
    assertEquals(previous, notifications.getNotificationPolicy());
    if (Build.VERSION.SDK_INT >= 29) assertEquals(Condition.STATE_FALSE, conditionState());
  }

  @Test public void settingsAndTransientPausesDoNotEndTheSession() {
    BreviarApp.setMute(app, true);
    try (ActivityController<Activity> reader = Robolectric.buildActivity(Activity.class).setup()) {
      reader.pause(); // e.g. notification shade / transient system UI
      idle();
      assertTrue(rule().isEnabled());
      try (ActivityController<Activity> settings = Robolectric.buildActivity(Activity.class).setup()) {
        reader.stop();
        idle();
        assertTrue(rule().isEnabled());
        BreviarApp.setMute(app, false);
        assertFalse(rule().isEnabled());
        assertEquals(previous, notifications.getNotificationPolicy());
        BreviarApp.setMute(app, true);
        assertReadingPolicy(false);
      }
    }
    idle();
    assertFalse(rule().isEnabled());
  }

  @Test public void recreationDoesNotMomentarilyDisableDnd() {
    BreviarApp.setMute(app, true);
    try (ActivityController<Activity> first = Robolectric.buildActivity(Activity.class).setup()) {
      first.pause().stop();
      try (ActivityController<Activity> replacement = Robolectric.buildActivity(Activity.class).setup()) {
        idle();
        assertTrue(rule().isEnabled());
        assertReadingPolicy(false);
      }
    }
    idle();
    assertFalse(rule().isEnabled());
  }

  @Test public void neverDisablesTheUsersExistingDnd() {
    notifications.setInterruptionFilter(NotificationManager.INTERRUPTION_FILTER_NONE);
    BreviarApp.setMute(app, true);
    try (ActivityController<Activity> activity = Robolectric.buildActivity(Activity.class).setup()) {
      assertTrue(rule().isEnabled());
      assertEquals(NotificationManager.INTERRUPTION_FILTER_NONE, notifications.getCurrentInterruptionFilter());
    }
    idle();
    assertEquals(NotificationManager.INTERRUPTION_FILTER_NONE, notifications.getCurrentInterruptionFilter());
    assertEquals(previous, notifications.getNotificationPolicy());
  }

  @Test public void noChangesWithoutPermissionAndRecoversWhenPermissionGranted() {
    shadow.setNotificationPolicyAccessGranted(false);
    BreviarApp.setMute(app, true);
    try (ActivityController<Activity> activity = Robolectric.buildActivity(Activity.class).setup()) {
      assertEquals(previous, notifications.getNotificationPolicy());
      shadow.setNotificationPolicyAccessGranted(true);
      assertTrue(notifications.getAutomaticZenRules().isEmpty());
      activity.pause().resume();
      assertReadingPolicy(false);
      // Revocation must not crash the foreground reader or its exit callbacks.
      shadow.setNotificationPolicyAccessGranted(false);
      activity.pause().resume();
    }
    idle();
  }

  @Test public void ruleIsReusedAndDeletedRuleIsRecreatedOnTheNextSession() {
    BreviarApp.setMute(app, true);
    try (ActivityController<Activity> activity = Robolectric.buildActivity(Activity.class).setup()) {
      assertTrue(rule().isEnabled());
    }
    idle();
    String id = notifications.getAutomaticZenRules().keySet().iterator().next();
    app.getSharedPreferences("do_not_disturb", 0).edit().remove("rule").commit();
    try (ActivityController<Activity> activity = Robolectric.buildActivity(Activity.class).setup()) {
      assertTrue(rule().isEnabled());
      assertTrue(notifications.getAutomaticZenRules().containsKey(id));
    }
    idle();
    notifications.removeAutomaticZenRule(id);
    try (ActivityController<Activity> activity = Robolectric.buildActivity(Activity.class).setup()) {
      assertTrue(rule().isEnabled());
      assertFalse(notifications.getAutomaticZenRules().containsKey(id));
    }
  }

  @Test public void providerReportsTheActualSessionAndClearsStaleStateAfterRestart() {
    BreviarApp.setMute(app, true);
    ServiceController<DoNotDisturbService> provider = Robolectric.buildService(DoNotDisturbService.class).create();
    try (ActivityController<Activity> activity = Robolectric.buildActivity(Activity.class).setup()) {
      provider.get().onConnected();
      provider.get().onSubscribe(app.doNotDisturb.conditionId());
      assertEquals(Condition.STATE_TRUE, Provider.conditions.get(Provider.conditions.size() - 1).state);
      // Constructing the Application/controller in the separate TTS process must
      // not turn off the foreground reader's rule.
      new DoNotDisturb(app);
      assertTrue(rule().isEnabled());
      // Simulate the main process restarting without a reading activity.
      app.unregisterActivityLifecycleCallbacks(app.doNotDisturb);
      app.doNotDisturb = new DoNotDisturb(app);
      app.registerActivityLifecycleCallbacks(app.doNotDisturb);
      provider.get().onConnected();
      assertFalse(rule().isEnabled());
      assertEquals(Condition.STATE_FALSE, Provider.conditions.get(Provider.conditions.size() - 1).state);
      assertEquals(previous, notifications.getNotificationPolicy());
    } finally {
      provider.destroy();
    }
  }

  @Test public void speechTemporarilyAllowsMediaWithoutAllowingNotifications() {
    BreviarApp.setMute(app, true);
    try (ActivityController<Activity> activity = Robolectric.buildActivity(Activity.class).setup()) {
      assertReadingPolicy(false);
      assertTrue(DoNotDisturbProvider.reportSpeech(app, true));
      assertReadingPolicy(true);
      assertTrue(DoNotDisturbProvider.reportSpeech(app, false));
      assertReadingPolicy(false);
    }
    idle();
    assertEquals(previous, notifications.getNotificationPolicy());
  }

  @Test public void speechOutsideTheAppDoesNotActivateDndAndIsRememberedWhenReturning() {
    BreviarApp.setMute(app, true);
    assertTrue(DoNotDisturbProvider.reportSpeech(app, true));
    assertTrue(notifications.getAutomaticZenRules().isEmpty());
    try (ActivityController<Activity> activity = Robolectric.buildActivity(Activity.class).setup()) {
      assertReadingPolicy(true);
    }
    idle();
    assertFalse(rule().isEnabled());
    assertEquals(previous, notifications.getNotificationPolicy());
  }

  @Test public void doesNotOverwriteLegacyPolicyEditsMadeByTheUser() {
    BreviarApp.setMute(app, true);
    Policy edited = new Policy(Policy.PRIORITY_CATEGORY_MESSAGES,
        Policy.PRIORITY_SENDERS_ANY, Policy.PRIORITY_SENDERS_STARRED, Policy.SUPPRESSED_EFFECT_SCREEN_ON);
    try (ActivityController<Activity> activity = Robolectric.buildActivity(Activity.class).setup()) {
      notifications.setNotificationPolicy(edited);
      DoNotDisturbProvider.reportSpeech(app, true);
    }
    idle();
    assertEquals(edited, notifications.getNotificationPolicy());
  }

  @Test @Config(shadows = {Provider.class, XmlSettingsActivityTest.SettingsServer.class})
  public void settingsRequestsAccessAndOnlyEnablesAfterGrant() {
    shadow.setNotificationPolicyAccessGranted(false);
    BreviarApp.setEinkMode(app, false);
    try (ActivityController<DeviceSettings> screen = Robolectric.buildActivity(DeviceSettings.class).setup()) {
      DeviceSettings activity = screen.get();
      XmlSettingsActivityTest.awaitSettings(activity);
      CompoundButton toggle = (CompoundButton)activity.menuItem("device.do-not-disturb").getActionView();
      toggle.performClick();
      assertFalse(BreviarApp.getMute(app));
      assertFalse(toggle.isChecked());
      Intent settings = Shadows.shadowOf(activity).getNextStartedActivity();
      assertEquals(Settings.ACTION_NOTIFICATION_POLICY_ACCESS_SETTINGS, settings.getAction());
      shadow.setNotificationPolicyAccessGranted(true);
      toggle.performClick();
      assertTrue(toggle.isChecked());
      assertReadingPolicy(false);
      toggle.performClick();
      assertFalse(rule().isEnabled());
    }
  }
}

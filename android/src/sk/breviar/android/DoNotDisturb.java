package sk.breviar.android;

import android.app.Activity;
import android.app.Application;
import android.app.AutomaticZenRule;
import android.app.NotificationManager;
import android.content.ComponentName;
import android.content.Context;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.service.notification.Condition;
import android.service.notification.ZenPolicy;
import android.util.Log;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

/** A reading-session DND rule shared by UI callbacks and the private TTS IPC provider. */
final class DoNotDisturb implements Application.ActivityLifecycleCallbacks {
  private final Application app;
  private final NotificationManager notifications;
  private final SharedPreferences preferences;
  private final Set<Activity> visible = new HashSet<>();
  private final Handler handler = new Handler(Looper.getMainLooper());
  private final Runnable refresh = this::refresh;
  private boolean active;
  private boolean initialized;
  private boolean speaking;
  private boolean appliedSpeaking;
  private DoNotDisturbService provider;

  static DoNotDisturb get(Context context) {
    return ((BreviarApp)context.getApplicationContext()).getDoNotDisturb();
  }

  DoNotDisturb(Application app) {
    this.app = app;
    notifications = (NotificationManager)app.getSystemService(Context.NOTIFICATION_SERVICE);
    preferences = app.getSharedPreferences("do_not_disturb", Context.MODE_PRIVATE);
    // Do not touch DND here: TtsService creates its own Application in another process.
  }

  boolean hasAccess() { return notifications.isNotificationPolicyAccessGranted(); }

  Uri conditionId() {
    return new Uri.Builder().scheme(Condition.SCHEME).authority(app.getPackageName())
        .appendPath("reading").build();
  }

  private ComponentName owner() { return new ComponentName(app, DoNotDisturbService.class); }

  private String findRule() {
    String id = preferences.getString("rule", null);
    if (id != null && isOurs(notifications.getAutomaticZenRule(id))) return id;
    // Recover after preferences are restored from backup, or a process dies between
    // creating the system rule and saving its ID. Never accumulate duplicate rules.
    for (Map.Entry<String, AutomaticZenRule> entry : notifications.getAutomaticZenRules().entrySet()) {
      if (isOurs(entry.getValue())) {
        preferences.edit().putString("rule", entry.getKey()).apply();
        return entry.getKey();
      }
    }
    return null;
  }

  private boolean isOurs(AutomaticZenRule rule) {
    return rule != null && owner().equals(rule.getOwner()) && conditionId().equals(rule.getConditionId());
  }

  private String createRule() {
    AutomaticZenRule rule = new AutomaticZenRule(app.getString(R.string.app_name), owner(),
        conditionId(), NotificationManager.INTERRUPTION_FILTER_PRIORITY, true);
    if (Build.VERSION.SDK_INT >= 29) configurePolicy(rule, speaking);
    String id = notifications.addAutomaticZenRule(rule);
    if (id == null) throw new IllegalStateException("Cannot create reading DND rule");
    preferences.edit().putString("rule", id).apply();
    return id;
  }

  private static void configurePolicy(AutomaticZenRule rule, boolean speaking) {
    // Block every notification category; allow the media stream only during TTS.
    ZenPolicy.Builder policy = new ZenPolicy.Builder().disallowAllSounds()
        .allowMedia(speaking).hideAllVisualEffects();
    if (Build.VERSION.SDK_INT >= 30) policy.allowConversations(ZenPolicy.CONVERSATION_SENDERS_NONE);
    if (Build.VERSION.SDK_INT >= 35) policy.allowPriorityChannels(false);
    rule.setZenPolicy(policy.build());
  }

  // The internal content provider calls from TTS's separate process. Serialize
  // its Binder thread with activity callbacks so policy and visibility cannot race.
  synchronized void setSpeaking(boolean value) {
    speaking = value;
    refresh();
  }

  synchronized void refresh() {
    handler.removeCallbacks(refresh);
    if (!hasAccess()) {
      // Permission may be revoked in Settings while the app is running.
      active = false;
      initialized = false;
      return;
    }
    boolean wanted = !visible.isEmpty() && BreviarApp.getMute(app);
    if (initialized && wanted == active && (!wanted || speaking == appliedSpeaking)) return;
    try {
      String id = findRule();
      if (wanted && id == null) id = createRule();
      if (wanted && Build.VERSION.SDK_INT < 29) LegacyDndPolicy.apply(notifications, preferences, speaking);
      if (id != null) {
        AutomaticZenRule rule = notifications.getAutomaticZenRule(id);
        // Disabling on exit also works before the condition provider has connected.
        // Never set the global filter: other apps' rules and user schedules survive.
        rule.setEnabled(wanted);
        if (wanted) {
          // Android 7-8 cannot exclude media from a priority policy. NONE is
          // needed for silent reading there; priority mode allows TTS playback.
          rule.setInterruptionFilter(Build.VERSION.SDK_INT < 28 && !speaking
              ? NotificationManager.INTERRUPTION_FILTER_NONE : NotificationManager.INTERRUPTION_FILTER_PRIORITY);
          if (Build.VERSION.SDK_INT >= 29) configurePolicy(rule, speaking);
        }
        if (!notifications.updateAutomaticZenRule(id, rule)) {
          throw new IllegalStateException("Cannot update reading DND rule");
        }
        if (Build.VERSION.SDK_INT >= 29) {
          notifications.setAutomaticZenRuleState(id, condition(wanted));
        }
      }
      active = wanted;
      appliedSpeaking = speaking;
      initialized = true;
      publishCondition();
      if (!wanted && Build.VERSION.SDK_INT < 29) LegacyDndPolicy.restore(notifications, preferences);
    } catch (SecurityException | IllegalArgumentException | IllegalStateException error) {
      // System permission/rule changes must not crash the reader. Retry at the
      // next lifecycle event; retain the legacy snapshot until restoration succeeds.
      initialized = false;
      Log.w("breviar", "Cannot update reading Do Not Disturb", error);
    }
  }

  Condition condition(boolean enabled) {
    return new Condition(conditionId(), app.getString(R.string.mute),
        enabled ? Condition.STATE_TRUE : Condition.STATE_FALSE);
  }

  synchronized void connected(DoNotDisturbService service) {
    provider = service;
    // After a process restart/boot there are no visible activities. Clear a stale
    // condition instead of leaving the device in DND until the next app launch.
    refresh();
    publishCondition();
  }

  synchronized void disconnected(DoNotDisturbService service) {
    if (provider == service) provider = null;
  }

  synchronized void publishCondition() {
    if (provider != null) provider.notifyCondition(condition(active && hasAccess()));
  }

  @Override public synchronized void onActivityStarted(Activity activity) {
    visible.add(activity);
    refresh();
  }

  @Override public void onActivityResumed(Activity activity) { refresh(); }

  @Override public synchronized void onActivityStopped(Activity activity) {
    visible.remove(activity);
    // Navigation/recreation starts the replacement activity before this runs.
    // A transient onPause (e.g. opening the notification shade) must not end DND.
    handler.removeCallbacks(refresh);
    handler.post(refresh);
  }

  @Override public synchronized void onActivityDestroyed(Activity activity) {
    if (visible.contains(activity)) onActivityStopped(activity);
  }
  @Override public void onActivityCreated(Activity activity, Bundle state) {}
  @Override public void onActivityPaused(Activity activity) {}
  @Override public void onActivitySaveInstanceState(Activity activity, Bundle state) {}
}

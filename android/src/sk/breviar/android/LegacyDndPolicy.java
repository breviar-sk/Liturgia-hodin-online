package sk.breviar.android;

import android.app.NotificationManager;
import android.app.NotificationManager.Policy;
import android.content.SharedPreferences;
import android.os.Build;

/** Android 7-9 have automatic rules, but only a shared notification policy. */
final class LegacyDndPolicy {
  private LegacyDndPolicy() {}

  static Policy readingPolicy(boolean speaking) {
    int effects = Policy.SUPPRESSED_EFFECT_SCREEN_ON | Policy.SUPPRESSED_EFFECT_SCREEN_OFF;
    int categories = 0; // Before Android 9 DND priority mode already allows media.
    if (Build.VERSION.SDK_INT >= 28) {
      categories = speaking ? Policy.PRIORITY_CATEGORY_MEDIA : 0;
      effects |= Policy.SUPPRESSED_EFFECT_FULL_SCREEN_INTENT | Policy.SUPPRESSED_EFFECT_LIGHTS
          | Policy.SUPPRESSED_EFFECT_PEEK | Policy.SUPPRESSED_EFFECT_STATUS_BAR
          | Policy.SUPPRESSED_EFFECT_BADGE | Policy.SUPPRESSED_EFFECT_AMBIENT
          | Policy.SUPPRESSED_EFFECT_NOTIFICATION_LIST;
    }
    return new Policy(categories, Policy.PRIORITY_SENDERS_ANY, Policy.PRIORITY_SENDERS_ANY, effects);
  }

  static void apply(NotificationManager manager, SharedPreferences preferences, boolean speaking) {
    if (preferences.contains("previous.categories") && !samePolicy(manager.getNotificationPolicy(),
        readingPolicy(preferences.getBoolean("applied.media", false)))) {
      return; // The user has edited the shared policy; do not replace that edit.
    }
    if (!preferences.contains("previous.categories")) {
      Policy previous = manager.getNotificationPolicy();
      // Persist before changing the system, so a process restart can undo our edit.
      if (!preferences.edit().putInt("previous.categories", previous.priorityCategories)
          .putInt("previous.calls", previous.priorityCallSenders)
          .putInt("previous.messages", previous.priorityMessageSenders)
          .putInt("previous.effects", previous.suppressedVisualEffects).commit()) {
        throw new IllegalStateException("Cannot save previous DND policy");
      }
    }
    preferences.edit().putBoolean("applied.media", speaking).commit();
    manager.setNotificationPolicy(readingPolicy(speaking));
  }

  static void restore(NotificationManager manager, SharedPreferences preferences) {
    if (!preferences.contains("previous.categories")) return;
    Policy current = manager.getNotificationPolicy();
    Policy applied = readingPolicy(preferences.getBoolean("applied.media", false));
    // Do not overwrite a policy the user changed while Breviar was open.
    if (samePolicy(current, applied)) {
      manager.setNotificationPolicy(new Policy(preferences.getInt("previous.categories", 0),
          preferences.getInt("previous.calls", Policy.PRIORITY_SENDERS_ANY),
          preferences.getInt("previous.messages", Policy.PRIORITY_SENDERS_ANY),
          preferences.getInt("previous.effects", 0)));
    }
    preferences.edit().remove("previous.categories").remove("previous.calls")
        .remove("previous.messages").remove("previous.effects").remove("applied.media").apply();
  }

  private static boolean samePolicy(Policy first, Policy second) {
    return first.priorityCategories == second.priorityCategories
        && first.priorityCallSenders == second.priorityCallSenders
        && first.priorityMessageSenders == second.priorityMessageSenders
        && first.suppressedVisualEffects == second.suppressedVisualEffects;
  }
}

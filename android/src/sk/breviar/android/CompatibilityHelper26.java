package sk.breviar.android;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.Context;

public class CompatibilityHelper26 {
  static NotificationChannel channel = null;
  
  static synchronized void updateChannel(Context ctx, boolean enable_vibration) {
    String channel_name = ctx.getString(R.string.channel_name);
    if (channel == null) {
      channel = new NotificationChannel("default", channel_name, NotificationManager.IMPORTANCE_DEFAULT);
    } else {
      channel.setName(channel_name);
    }
    channel.setDescription(ctx.getString(R.string.channel_description));
    channel.enableVibration(enable_vibration);
    if (enable_vibration) {
      channel.setImportance(NotificationManager.IMPORTANCE_DEFAULT);
    } else {
      channel.setImportance(NotificationManager.IMPORTANCE_LOW);
    }
    NotificationManager notificator =
        (NotificationManager)ctx.getSystemService(ctx.NOTIFICATION_SERVICE);
    notificator.createNotificationChannel(channel);
  }
}

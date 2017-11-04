package sk.breviar.android;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.Context;

public class CompatibilityHelper26 {
  static NotificationChannel channel = null;
  
  static synchronized void updateChannel(Context ctx) {
    String channel_name = ctx.getString(R.string.channel_name);
    if (channel == null) {
      channel = new NotificationChannel("default", channel_name, NotificationManager.IMPORTANCE_DEFAULT);
    } else {
      channel.setName(channel_name);
    }
    channel.setDescription(ctx.getString(R.string.channel_description));
    NotificationManager notificator =
        (NotificationManager)ctx.getSystemService(ctx.NOTIFICATION_SERVICE);
    notificator.createNotificationChannel(channel);
  }
}

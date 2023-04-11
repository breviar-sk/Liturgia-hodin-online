package sk.breviar.android;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.Context;

public class CompatibilityHelper26 {
  static NotificationChannel channel = null;
  static NotificationChannel channel_tts = null;
  
  static synchronized void updateChannel(Context ctx) {
    String channel_name = ctx.getString(R.string.channel_name);
    if (channel == null) {
      channel = new NotificationChannel("default", channel_name, NotificationManager.IMPORTANCE_DEFAULT);
    } else {
      channel.setName(channel_name);
    }
    if (channel_tts == null) {
      channel_tts = new NotificationChannel("tts", channel_name, NotificationManager.IMPORTANCE_LOW);
    } else {
      channel_tts.setName(channel_name);
    }
    channel.setDescription(ctx.getString(R.string.channel_description));
    channel_tts.setDescription(ctx.getString(R.string.channel_description));
    channel.enableVibration(true);
    channel_tts.enableVibration(false);
    channel.setImportance(NotificationManager.IMPORTANCE_DEFAULT);
    channel_tts.setImportance(NotificationManager.IMPORTANCE_LOW);
    NotificationManager notificator =
        (NotificationManager)ctx.getSystemService(ctx.NOTIFICATION_SERVICE);
    notificator.createNotificationChannel(channel);
    notificator.createNotificationChannel(channel_tts);
  }
}

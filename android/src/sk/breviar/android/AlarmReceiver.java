package sk.breviar.android;

import android.support.v4.app.NotificationCompat;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.util.Log;

import sk.breviar.android.BreviarApp;
import sk.breviar.android.Util;

public class AlarmReceiver extends BroadcastReceiver {
  @Override
  public void onReceive(Context ctx, Intent in) {
    Log.v("breviar", "AlarmReceiver onReceive");
    if (in.getAction().equals("sk.breviar.android.NOTIFY")) {
      int id = in.getIntExtra("id", -1);
      Log.v("breviar", "notification id " + id);
      if (id != -1) {
        ctx = BreviarApp.getLocaleForCurrentLanguage(ctx);

        PendingIntent pi = PendingIntent.getActivity(ctx, 0, 
          new Intent("sk.breviar.android.action.SHOW")
              .putExtra("id", id), PendingIntent.FLAG_UPDATE_CURRENT);

        if (Build.VERSION.SDK_INT >= 26) {
          CompatibilityHelper26.updateChannel(ctx, true);
        }

        NotificationManager notificator =
            (NotificationManager)ctx.getSystemService(ctx.NOTIFICATION_SERVICE);
        int icon;
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.LOLLIPOP) {
          icon = R.drawable.icon;
        } else {
          icon = R.drawable.icon_transparent;
        }
        notificator.notify(BreviarApp.NOTIFY_ALARM_ID, 
          new NotificationCompat.Builder(ctx, "default")
            .setContentText(ctx.getString(R.string.channel_name))
            .setContentTitle(ctx.getString(Util.events[id].notify_text))
            .setSmallIcon(icon)
            .setAutoCancel(true)
            .setContentIntent(pi)
            .setDefaults(Notification.DEFAULT_ALL)
            .setColor(ctx.getResources().getColor(R.color.colorPrimary))
            .build()
        );
      }
    }
    Util.setAlarm(ctx);
  }
}

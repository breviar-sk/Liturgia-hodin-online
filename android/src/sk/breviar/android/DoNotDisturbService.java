package sk.breviar.android;

import android.net.Uri;
import android.service.notification.ConditionProviderService;

/** System-bound owner of the reading rule; also clears its condition after process restart. */
public class DoNotDisturbService extends ConditionProviderService {
  @Override public void onConnected() { DoNotDisturb.get(this).connected(this); }

  @Override public void onSubscribe(Uri id) {
    DoNotDisturb mode = DoNotDisturb.get(this);
    if (mode.conditionId().equals(id)) mode.publishCondition();
  }

  @Override public void onUnsubscribe(Uri id) {}

  @Override public void onDestroy() {
    DoNotDisturb.get(this).disconnected(this);
    super.onDestroy();
  }
}

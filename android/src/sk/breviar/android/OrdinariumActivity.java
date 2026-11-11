package sk.breviar.android;

import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

/** The five sections of the Ordinary, using the selected prayer edition. */
public class OrdinariumActivity extends SettingsActivity {
  static final String[] PRAYERS = {"mi", "mrch", "mpc", "mv", "mk"};
  static final int[] LABELS = {R.string.inv, R.string.rch, R.string.read, R.string.vesp, R.string.kompl};

  @Override public void onCreate(Bundle state) {
    super.onCreate(state);
    getSupportActionBar().setTitle(R.string.ordinarium);
    Menu menu = navigationView.getMenu();
    for (int i = 0; i < PRAYERS.length; ++i) {
      final int page = i;
      MenuItem item = menu.add(Menu.NONE, i + 1, Menu.NONE, LABELS[i]);
      handleClick(item.getItemId(), () -> {
        setResult(RESULT_OK, new Intent().putExtra("ordinarium_prayer", PRAYERS[page]));
        finish();
      });
    }
  }
}

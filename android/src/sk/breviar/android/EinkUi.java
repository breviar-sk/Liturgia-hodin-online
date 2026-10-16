package sk.breviar.android;

import android.content.res.ColorStateList;
import android.graphics.Color;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.WebView;
import android.widget.TextView;
import android.widget.ImageView;
import androidx.appcompat.widget.SwitchCompat;
import androidx.appcompat.widget.Toolbar;
import androidx.recyclerview.widget.RecyclerView;
import com.google.android.material.navigation.NavigationView;

/** Portable e-ink presentation; display waveform/refresh control stays with the device. */
final class EinkUi {
  private EinkUi() {}

  static void tintMenu(Menu menu) {
    for (int i = 0; i < menu.size(); ++i) {
      MenuItem item = menu.getItem(i);
      if (item.getIcon() != null) item.getIcon().mutate().setTint(Color.BLACK);
      if (item.hasSubMenu()) tintMenu(item.getSubMenu());
    }
  }

  static void apply(View view) {
    if (view == null || !BreviarApp.getEinkMode(view.getContext())) return;
    view.setElevation(0);
    view.setStateListAnimator(null);
    view.setOverScrollMode(View.OVER_SCROLL_NEVER);
    if (view instanceof TextView) {
      TextView text = (TextView)view;
      text.setTextColor(Color.BLACK);
      text.setHintTextColor(Color.BLACK);
      text.setLinkTextColor(Color.BLACK);
    }
    if (view instanceof ImageView) ((ImageView)view).setColorFilter(Color.BLACK);
    if (view instanceof Toolbar) {
      Toolbar toolbar = (Toolbar)view;
      toolbar.setBackgroundColor(Color.WHITE);
      toolbar.setTitleTextColor(Color.BLACK);
      toolbar.setSubtitleTextColor(Color.BLACK);
      if (toolbar.getNavigationIcon() != null) toolbar.getNavigationIcon().mutate().setTint(Color.BLACK);
      if (toolbar.getOverflowIcon() != null) toolbar.getOverflowIcon().mutate().setTint(Color.BLACK);
      tintMenu(toolbar.getMenu());
    }
    if (view instanceof NavigationView) {
      NavigationView menu = (NavigationView)view;
      menu.setBackgroundColor(Color.WHITE);
      menu.setItemTextColor(ColorStateList.valueOf(Color.BLACK));
      menu.setItemIconTintList(ColorStateList.valueOf(Color.BLACK));
      menu.setItemBackgroundResource(R.drawable.eink_selection);
      for (int i = 0; i < menu.getHeaderCount(); ++i) apply(menu.getHeaderView(i));
      for (int i = 0; i < menu.getMenu().size(); ++i) apply(menu.getMenu().getItem(i).getActionView());
    }
    if (view instanceof RecyclerView) ((RecyclerView)view).setItemAnimator(null);
    if (view instanceof SwitchCompat) {
      SwitchCompat toggle = (SwitchCompat)view;
      toggle.setThumbTintList(ColorStateList.valueOf(Color.BLACK));
      toggle.setTrackTintList(null);
      toggle.setTrackResource(R.drawable.eink_switch_track);
      toggle.jumpDrawablesToCurrentState();
    }
    if (view instanceof WebView) {
      view.setBackgroundColor(Color.WHITE);
      view.setVerticalScrollBarEnabled(false);
      view.setHorizontalScrollBarEnabled(false);
    }
    if (view instanceof ViewGroup) {
      ViewGroup group = (ViewGroup)view;
      group.setLayoutTransition(null);
      for (int i = 0; i < group.getChildCount(); ++i) apply(group.getChildAt(i));
    }
  }

  /** WebView.pageUp/pageDown animate. E-ink needs a single jump with some overlap. */
  static void page(WebView view, boolean down) {
    if (BreviarApp.getEinkMode(view.getContext())) {
      int overlap = Math.round(48 * view.getResources().getDisplayMetrics().density);
      int step = Math.max(1, view.getHeight() - overlap);
      view.scrollBy(0, down ? step : -step);
    } else if (down) {
      view.pageDown(false);
    } else {
      view.pageUp(false);
    }
  }
}

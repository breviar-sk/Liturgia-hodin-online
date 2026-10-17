package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CheckedTextView;
import androidx.recyclerview.widget.RecyclerView;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.android.controller.ActivityController;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.GraphicsMode;
import org.robolectric.annotation.LooperMode;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = 35)
@GraphicsMode(GraphicsMode.Mode.NATIVE)
@LooperMode(LooperMode.Mode.PAUSED)
public class ChoiceRowsTest {
  private static <T extends View> T find(View view, Class<T> type) {
    if (type.isInstance(view)) return type.cast(view);
    if (view instanceof ViewGroup) {
      ViewGroup group = (ViewGroup)view;
      for (int i = 0; i < group.getChildCount(); ++i) {
        T child = find(group.getChildAt(i), type);
        if (child != null) return child;
      }
    }
    return null;
  }

  @SuppressWarnings({"rawtypes", "unchecked"})
  private static void assertRow(SettingsActivity activity, int position, boolean checked, int color) {
    RecyclerView list = find(activity.navigationView, RecyclerView.class);
    RecyclerView.Adapter adapter = list.getAdapter();
    RecyclerView.ViewHolder holder = adapter.createViewHolder(list, adapter.getItemViewType(position));
    adapter.bindViewHolder(holder, position);
    CheckedTextView label = find(holder.itemView, CheckedTextView.class);
    assertNotNull(label);
    assertEquals(checked, label.isChecked());
    assertEquals(color, label.getCurrentTextColor());
    assertTrue(label.createAccessibilityNodeInfo().isCheckable());
    assertEquals(checked, label.createAccessibilityNodeInfo().isChecked());
    Drawable[] icons = label.getCompoundDrawablesRelative();
    assertNotNull("Check mark must precede the label", icons[0]);
    assertNull(icons[2]);
    Drawable icon = icons[0];
    icon.setBounds(0, 0, 48, 48);
    Bitmap bitmap = Bitmap.createBitmap(48, 48, Bitmap.Config.ARGB_8888);
    icon.draw(new Canvas(bitmap));
    int painted = 0;
    for (int y = 0; y < 48; ++y) {
      for (int x = 0; x < 48; ++x) {
        int pixel = bitmap.getPixel(x, y);
        if (Color.alpha(pixel) > 128) {
          ++painted;
          assertEquals(color & 0xffffff, pixel & 0xffffff);
        }
      }
    }
    bitmap.recycle();
    assertEquals("Only the current choice should paint a check mark", checked, painted > 0);
  }

  @Test public void checkMarksFollowSelectionAndRemainReadableInBothAppearances() {
    Context context = RuntimeEnvironment.getApplication();
    for (boolean eink : new boolean[]{false, true}) {
      BreviarApp.setEinkMode(context, eink);
      try (ActivityController<SettingsActivity> controller = Robolectric.buildActivity(SettingsActivity.class).setup()) {
        SettingsActivity activity = controller.get();
        activity.addCheckedChoice(0, "First choice", true, () -> {});
        activity.addCheckedChoice(0, "Second choice", false, () -> {});
        int color = eink ? Color.BLACK : Color.WHITE;
        assertRow(activity, 1, true, color);
        assertRow(activity, 2, false, color);
        activity.navigationView.getMenu().performIdentifierAction(
            activity.navigationView.getMenu().getItem(1).getItemId(), 0);
        assertRow(activity, 1, false, color);
        assertRow(activity, 2, true, color);
      }
    }
  }
}

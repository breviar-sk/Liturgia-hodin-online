package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Intent;
import android.content.Context;
import android.os.Looper;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.view.accessibility.AccessibilityNodeInfo;
import android.widget.CompoundButton;
import androidx.recyclerview.widget.RecyclerView;
import com.google.android.material.navigation.NavigationView;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.Shadows;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.Implementation;
import org.robolectric.annotation.Implements;
import org.robolectric.annotation.LooperMode;
import org.robolectric.android.controller.ActivityController;
import org.robolectric.util.ReflectionHelpers;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.TimeUnit;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = 35, shadows = XmlSettingsActivityTest.SettingsServer.class)
@LooperMode(LooperMode.Mode.PAUSED)
public class XmlSettingsActivityTest {
  @Implements(value = Server.class, isInAndroidSdk = false)
  public static class SettingsServer {
    // Exercise real activities, XML parsing and Material widgets without JNI.
    @Implementation protected static void __staticInitializer__() {}
    @Implementation protected static String getSettingsXml(Context context, String options, String language) {
      return settingsXml(true);
    }
  }

  private static String settingsXml(boolean full) {
    String options = "<Opt0 Name='o0' Value='1' Text='nastavenia pre kalendár'>"
        + "<Verse Id='1' Text='číslovanie veršov'/>"
        + "<References Id='2' Text='biblické odkazy'/>"
        + "</Opt0>";
    if (full) {
      for (String name : new String[]{"o1", "o2", "o5"}) {
        options += "<Opt Name='" + name + "' Value='0' Text='ďalšie možnosti'>"
            + "<Flag Id='1' Text='možnosť'/></Opt>";
      }
    }
    return "<LHData><Options>" + options + "</Options>"
        + "<SupportedValues><LiturgicalCalendarValues Name='k' Value=''>"
        + "<Calendar>všeobecný</Calendar>"
        + (full ? "<Calendar Value='sj'>jezuiti</Calendar>" : "")
        + "</LiturgicalCalendarValues></SupportedValues></LHData>";
  }

  private static SettingsXml settings(boolean full) throws Exception {
    return SettingsXml.parse(settingsXml(full));
  }

  private static void awaitSettings(XmlSettingsActivity activity) throws Exception {
    ExecutorService worker = ReflectionHelpers.getField(activity, "worker");
    worker.submit(() -> {}).get(10, TimeUnit.SECONDS);
    Shadows.shadowOf(Looper.getMainLooper()).idle();
  }

  private static void show(XmlSettingsActivity activity, SettingsXml settings) {
    ReflectionHelpers.callInstanceMethod(activity, "showSettings",
        ReflectionHelpers.ClassParameter.from(SettingsXml.class, settings));
  }

  private static RecyclerView recycler(View view) {
    if (view instanceof RecyclerView) return (RecyclerView)view;
    if (view instanceof ViewGroup) {
      ViewGroup group = (ViewGroup)view;
      for (int i = 0; i < group.getChildCount(); ++i) {
        RecyclerView result = recycler(group.getChildAt(i));
        if (result != null) return result;
      }
    }
    return null;
  }

  @SuppressWarnings({"rawtypes", "unchecked"})
  private static View bindLastRow(NavigationView menu) {
    RecyclerView recycler = recycler(menu);
    assertNotNull(recycler);
    RecyclerView.Adapter adapter = recycler.getAdapter();
    int position = adapter.getItemCount() - 1;
    RecyclerView.ViewHolder holder = adapter.createViewHolder(recycler, adapter.getItemViewType(position));
    adapter.bindViewHolder(holder, position);
    return holder.itemView;
  }

  @Test
  public void backToParentKeepsOldRowsAccessibleDuringRefresh() throws Exception {
    try (ActivityController<MainSettings> controller = Robolectric.buildActivity(MainSettings.class).setup()) {
      MainSettings activity = controller.get();
      awaitSettings(activity);
      NavigationView previous = activity.navigationView;
      View oldRow = bindLastRow(previous);

      // The parent stops while a submenu is open, then resumes on Back.
      controller.pause().stop().restart().start().resume();
      assertSame(previous, activity.navigationView);
      assertNotNull(oldRow.createAccessibilityNodeInfo().getCollectionItemInfo());
      awaitSettings(activity);
      assertNotNull(oldRow.createAccessibilityNodeInfo().getCollectionItemInfo());
      assertNotNull(bindLastRow(activity.navigationView).createAccessibilityNodeInfo().getCollectionItemInfo());
    }
  }

  @Test
  public void shorterMenuPreservesAccessibilityForPreviouslyBoundRows() throws Exception {
    // Do not resume: rendering is supplied directly, without the JNI backend.
    try (ActivityController<MainSettings> controller = Robolectric.buildActivity(MainSettings.class).create()) {
      MainSettings activity = controller.get();
      show(activity, settings(true));
      NavigationView previous = activity.navigationView;
      int originalSize = previous.getMenu().size();
      View oldRow = bindLastRow(previous);
      int oldIndex = oldRow.createAccessibilityNodeInfo().getCollectionItemInfo().getRowIndex();

      // Back/refresh can shorten the menu before content capture visits old rows.
      show(activity, settings(false));
      assertTrue(activity.navigationView.getMenu().size() < originalSize);
      AccessibilityNodeInfo info = oldRow.createAccessibilityNodeInfo();
      assertEquals(oldIndex, info.getCollectionItemInfo().getRowIndex());
      assertEquals(originalSize, previous.getMenu().size());
      assertSame(activity.navigationView, activity.findViewById(R.id.settings_activity_content));
      assertNotNull(bindLastRow(activity.navigationView).createAccessibilityNodeInfo().getCollectionItemInfo());
    }
  }

  @Test
  public void refreshedMenuStillOpensXmlSubmenus() throws Exception {
    try (ActivityController<MainSettings> controller = Robolectric.buildActivity(MainSettings.class).create()) {
      MainSettings activity = controller.get();
      show(activity, settings(true));
      show(activity, settings(false));
      MenuItem group = activity.navigationView.getMenu().getItem(3);
      assertEquals("Nastavenia pre kalendár", group.getTitle().toString());
      activity.navigationView.getMenu().performIdentifierAction(group.getItemId(), 0);
      Intent intent = Shadows.shadowOf(activity).getNextStartedActivity();
      assertEquals(XmlSettingsActivity.class.getName(), intent.getComponent().getClassName());
      assertEquals("o0", intent.getStringExtra("settings_group"));
    }
  }

  @Test
  public void refreshedSubmenuSwitchesStillSavePreferences() throws Exception {
    Intent intent = new Intent().putExtra("settings_group", "o0");
    try (ActivityController<XmlSettingsActivity> controller =
        Robolectric.buildActivity(XmlSettingsActivity.class, intent).create()) {
      XmlSettingsActivity activity = controller.get();
      show(activity, settings(true));
      show(activity, settings(false));
      MenuItem verse = activity.navigationView.getMenu().getItem(0);
      CompoundButton toggle = (CompoundButton)verse.getActionView();
      assertEquals("Číslovanie veršov", verse.getTitle().toString());
      assertTrue(toggle.isChecked());
      toggle.performClick();
      assertFalse(toggle.isChecked());
      assertEquals("0", new UrlOptions(BreviarApp.getUrlOptions(activity)).params.get("o0"));
    }
  }
}

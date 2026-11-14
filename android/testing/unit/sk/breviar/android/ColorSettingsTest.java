package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.view.MenuItem;
import android.widget.EditText;
import java.util.ArrayList;
import java.util.List;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.Shadows;
import org.robolectric.android.controller.ActivityController;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.Implementation;
import org.robolectric.annotation.Implements;
import org.robolectric.annotation.LooperMode;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = {24, 35}, shadows = ColorSettingsTest.SettingsServer.class)
@LooperMode(LooperMode.Mode.PAUSED)
public class ColorSettingsTest {
  private final Context context = RuntimeEnvironment.getApplication();

  @Implements(value = Server.class, isInAndroidSdk = false)
  public static class SettingsServer {
    @Implementation protected static void __staticInitializer__() {}
    @Implementation protected static String getSettingsXml(Context context, String options, String language) {
      String xml = XmlSettingsActivityTest.settingsXml(true);
      String groups = palette("day", "0") + palette("night", "1");
      return xml.replace("</Menu>", "<MenuGroup Key='colors' Label='Colors'>" + groups + "</MenuGroup></Menu>");
    }
  }

  private static String palette(String mode, String suffix) {
    String key = "appearance.colors." + mode;
    String xml = "<MenuGroup Key='" + key + "' Label='" + mode + "' Control='submenu'>";
    String[] roles = {"text", "rubric", "background"};
    String[] params = {"ct" + suffix, "cr" + suffix, "c" + suffix};
    for (int i = 0; i < roles.length; ++i) {
      xml += "<MenuItem Key='" + key + "." + roles[i] + "' Label='" + roles[i]
          + "' Control='color' Parameter='" + params[i] + "' Default='' ResetValue=''/>";
    }
    xml += "<MenuGroup Key='" + key + ".presets' Label='Presets'>";
    for (String preset : new String[]{"default", "alternative"}) {
      xml += "<MenuItem Key='" + key + "." + preset + "' Label='" + preset + "' Control='preset'>";
      String[] values = preset.equals("default") ? new String[]{"", "", ""}
          : mode.equals("day") ? new String[]{"", "", "ffffcc"} : new String[]{"ffffff", "ffff00", "000000"};
      for (int i = 0; i < params.length; ++i) {
        xml += "<Set Parameter='" + params[i] + "' Value='" + values[i] + "'/>";
      }
      xml += "</MenuItem>";
    }
    return xml + "</MenuGroup></MenuGroup>";
  }

  private ActivityController<XmlSettingsActivity> open(String key) {
    return Robolectric.buildActivity(XmlSettingsActivity.class, XmlSettingsActivity.entryIntent(context, key)).setup();
  }

  @Test public void palettesOpenAsSeparatePages() {
    try (ActivityController<XmlSettingsActivity> controller = open("colors")) {
      XmlSettingsActivity activity = controller.get();
      XmlSettingsActivityTest.awaitSettings(activity);
      assertNull(activity.menuItem("appearance.colors.day.text"));
      MenuItem night = activity.menuItem("appearance.colors.night");
      assertNotNull(night);
      activity.onNavigationItemSelected(night);
      Intent intent = Shadows.shadowOf(activity).getNextStartedActivity();
      assertEquals("appearance.colors.night", intent.getStringExtra("settings_group"));
    }
  }

  @Test public void presetsSaveOnceAndClearOnlyTheirOwnPaletteIncludingStaleReaderColors() {
    BreviarApp.setUrlOptions(context, "ct0=123456&cr0=654321&c0=abcdef&ct1=eeeeee&cr1=ffaaaa&c1=111111&c=1&k=sj");
    try (ActivityController<XmlSettingsActivity> controller = open("appearance.colors.day")) {
      XmlSettingsActivity activity = controller.get();
      XmlSettingsActivityTest.awaitSettings(activity);
      UrlOptions staleReader = activity.options();
      List<String> saved = new ArrayList<>();
      SharedPreferences preferences = context.getSharedPreferences(Util.prefname, 0);
      SharedPreferences.OnSharedPreferenceChangeListener listener = (prefs, key) -> {
        if (key.equals(BreviarApp.stringUrlOptions)) saved.add(BreviarApp.getUrlOptions(context));
      };
      preferences.registerOnSharedPreferenceChangeListener(listener);
      try {
        activity.onNavigationItemSelected(activity.menuItem("appearance.colors.day.alternative"));
        XmlSettingsActivityTest.awaitSettings(activity);
        assertEquals(1, saved.size());
        UrlOptions options = new UrlOptions(saved.get(0));
        assertEquals("", options.params.get("ct0"));
        assertEquals("", options.params.get("cr0"));
        assertEquals("ffffcc", options.params.get("c0"));
        assertEquals("eeeeee", options.params.get("ct1"));
        assertEquals("ffaaaa", options.params.get("cr1"));
        assertEquals("111111", options.params.get("c1"));
        assertEquals("1", options.params.get("c"));
        assertEquals("sj", options.params.get("k"));
        assertTrue(activity.menuItem("appearance.colors.day.alternative").isChecked());
        SettingsXml.applySavedOptions(staleReader.params, options.params);
        assertEquals("", staleReader.params.get("ct0"));
        assertEquals("", staleReader.params.get("cr0"));
        activity.onNavigationItemSelected(activity.menuItem("appearance.colors.day.default"));
        XmlSettingsActivityTest.awaitSettings(activity);
        assertTrue(activity.menuItem("appearance.colors.day.default").isChecked());
        assertEquals("", activity.options().params.get("c0"));
        assertEquals("111111", activity.options().params.get("c1"));
      } finally {
        preferences.unregisterOnSharedPreferenceChangeListener(listener);
      }
    }
  }

  @Test public void nightPresetAndIndividualEditsUseTheExistingColorPicker() {
    BreviarApp.setUrlOptions(context, "c0=ffeeaa&c=0");
    for (boolean eink : new boolean[]{false, true}) {
      BreviarApp.setEinkMode(context, eink);
      try (ActivityController<XmlSettingsActivity> controller = open("appearance.colors.night")) {
        XmlSettingsActivity activity = controller.get();
        XmlSettingsActivityTest.awaitSettings(activity);
        activity.onNavigationItemSelected(activity.menuItem("appearance.colors.night.alternative"));
        XmlSettingsActivityTest.awaitSettings(activity);
        assertEquals("ffffff", activity.options().params.get("ct1"));
        assertEquals("ffff00", activity.options().params.get("cr1"));
        assertEquals("000000", activity.options().params.get("c1"));
        assertEquals("ffeeaa", activity.options().params.get("c0"));
        assertEquals("0", activity.options().params.get("c"));
        String key = "appearance.colors.night.rubric";
        SettingsActivity.ColorOption color = activity.color_options.get(activity.menuItem(key).getItemId()).color_option;
        assertEquals("ffff00", color.get());
        color.set("AbC");
        XmlSettingsActivityTest.awaitSettings(activity);
        assertEquals("aabbcc", activity.options().params.get("cr1"));
        assertFalse(activity.menuItem("appearance.colors.night.alternative").isChecked());
        color = activity.color_options.get(activity.menuItem(key).getItemId()).color_option;
        color.reset();
        XmlSettingsActivityTest.awaitSettings(activity);
        assertEquals("", activity.options().params.get("cr1"));
      }
    }
  }

  @Test public void colorDialogAcceptsShorthandAndResetsWithoutChangingTheBackground() {
    BreviarApp.setUrlOptions(context, "c0=ffffcc");
    try (ActivityController<XmlSettingsActivity> controller = open("appearance.colors.day")) {
      XmlSettingsActivity activity = controller.get();
      XmlSettingsActivityTest.awaitSettings(activity);
      for (boolean reset : new boolean[]{false, true}) {
        activity.onNavigationItemSelected(activity.menuItem("appearance.colors.day.text"));
        activity.getSupportFragmentManager().executePendingTransactions();
        SettingsActivity.ColorDialogFragment fragment = (SettingsActivity.ColorDialogFragment)
            activity.getSupportFragmentManager().findFragmentByTag("dialog");
        AlertDialog dialog = (AlertDialog)fragment.getDialog();
        assertNotNull(dialog.findViewById(R.id.color_picker_root));
        EditText input = dialog.findViewById(R.id.color_picker_edittext);
        input.setText("ABC");
        dialog.getButton(reset ? DialogInterface.BUTTON_NEUTRAL : DialogInterface.BUTTON_POSITIVE).performClick();
        XmlSettingsActivityTest.awaitSettings(activity);
        assertEquals(reset ? "" : "aabbcc", activity.options().params.get("ct0"));
        assertEquals("ffffcc", activity.options().params.get("c0"));
      }
    }
  }
}

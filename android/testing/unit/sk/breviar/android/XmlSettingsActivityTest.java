package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Intent;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.os.Looper;
import android.view.MenuItem;
import android.view.Menu;
import android.view.View;
import android.view.ViewGroup;
import android.view.accessibility.AccessibilityNodeInfo;
import android.widget.CompoundButton;
import androidx.recyclerview.widget.RecyclerView;
import androidx.recyclerview.widget.LinearLayoutManager;
import com.google.android.material.navigation.NavigationView;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.Shadows;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.Implementation;
import org.robolectric.annotation.Implements;
import org.robolectric.annotation.LooperMode;
import org.robolectric.android.controller.ActivityController;
import org.robolectric.util.ReflectionHelpers;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.CountDownLatch;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = 35, shadows = XmlSettingsActivityTest.SettingsServer.class)
@LooperMode(LooperMode.Mode.PAUSED)
public class XmlSettingsActivityTest {
  @Implements(value = Server.class, isInAndroidSdk = false)
  public static class SettingsServer {
    // Exercise real activities, XML parsing and Material widgets without JNI.
    @Implementation protected static void __staticInitializer__() {}
    @Implementation protected static String getSettingsXml(Context context, String options, String language) {
      UrlOptions params = new UrlOptions(options);
      String selected = params.params.get("k");
      String result = settingsXml(true).replace("Name='k' Value=''",
          "Name='k' Value='" + ("sj".equals(selected) ? "sj" : "") + "'")
          .replace("Name='o3' Value='4'", "Name='o3' Value='"
              + ("7".equals(params.params.get("o3")) ? "7" : "4") + "'");
      for (String word : new String[]{"o0", "o2"}) {
        long value = Long.parseLong(params.params.getOrDefault(word, word.equals("o0") ? "1" : "0"));
        if (word.equals("o0") && params.params.containsKey("of0v")) {
          value = params.params.get("of0v").equals("1") ? value | 1 : value & ~1L;
        }
        result = result.replace("Name='" + word + "' Value='" + (word.equals("o0") ? "1" : "0") + "'",
            "Name='" + word + "' Value='" + value + "'");
      }
      return result;
    }
  }

  static String settingsXml(boolean full) {
    String options = "<Opt0 Name='o0' Value='1' ForceName='of0' Text='voľby'>"
        + "<Verse Id='1' ForceName='of0v' Text='číslovanie veršov'/>"
        + "<References Id='2' ForceName='of0r' Text='biblické odkazy'/>"
        + "<Epiphany Id='8' ForceName='of0zjvne' Text='Zjavenie Pána v nedeľu'/>"
        + "<BitOpt0TransparentNav Id='1024' ForceName='of0tn' Text='šípky'/>"
        + "<Left Id='262144' ForceName='of0tnl' Text='Šípky vľavo'/>"
        + "<Down Id='1048576' ForceName='of0tnd' Text='Len nadol'/></Opt0>"
        + "<Opt2 Name='o2' Value='0' ForceName='of2' Text='zobrazenie'>"
        + "<Night Id='256' ForceName='of2nr' Text='nočný režim'/></Opt2>"
        + "<Opt3Communia Name='o3' Value='4' ForceName='of3' Text='časti modlitby zo spoločnej časti'/>";
    String calendar = "<MenuItem Key='calendar' Label='kalendár' Control='choice' Parameter='k' ValuesRef='LiturgicalCalendarValues'>"
        + "<MenuGroup Key='calendar.options' Label='Kalendárové voľby'>"
        + "<MenuItem Key='calendar.epiphany' Label='Zjavenie Pána v nedeľu' Control='toggle' OptionRef='Epiphany'/>"
        + "</MenuGroup></MenuItem>";
    String menu = "<Menu Version='1'><MenuGroup Key='general' Label='všeobecné'>"
        + "<MenuItem Key='language' Label='jazyk' Control='choice' Parameter='j' ValuesRef='SupportedLanguages' Handler='language.select'>"
        + "<MenuGroup Key='language.interface'><MenuItem Key='language.use-for-interface' Label='Použiť jazyk v aplikácii' Control='toggle' Handler='language.use-for-interface'/></MenuGroup>"
        + "</MenuItem>" + calendar
        + "<MenuItem Key='general.online-mode' Label='online' Control='choice' Handler='general.online-mode'/></MenuGroup>";
    if (full) {
      menu += "<MenuGroup Key='device' Label='zariadenie'>";
      for (String handler : new String[]{"eink", "volume-paging", "keep-awake", "do-not-disturb", "lock-zoom"}) {
        menu += "<MenuItem Key='device." + handler + "' Label='" + handler + "' Control='toggle' Handler='device." + handler + "'/>";
      }
      menu += "</MenuGroup><MenuGroup Key='appearance' Label='zobrazenie'>"
          + "<MenuItem Key='appearance.font' Label='Písmo' Control='font' Parameter='f' Default='' ResetValue='' Handler='appearance.font'/>"
          + "<MenuItem Key='appearance.night-mode' Label='nočný režim' Control='toggle' OptionRef='Night'/>"
          + "<MenuItem Key='appearance.font-size' Label='Veľkosť' Control='number' Parameter='ff' Default='12' ResetValue='12' Min='4' Max='60' Handler='appearance.font-size'/>"
          + "<MenuItem Key='appearance.margin' Label='Okraje' Control='number' Parameter='mm' Default='5' ResetValue='' Min='1' Max='200'/>"
          + "<MenuItem Key='appearance.background-day' Label='Pozadie' Control='color' Parameter='c0' Default='' ResetValue=''/>"
          + "<MenuItem Key='reading.navigation' Label='Navigácia pri čítaní' Control='choice' Handler='reading.navigation'>"
          + "<MenuGroup Key='reading.arrow-options' Label='Šípky'>"
          + "<MenuItem Key='reading.arrows-left' Label='Šípky vľavo' Control='toggle' OptionRef='Left'/>"
          + "<MenuItem Key='reading.down-arrow-only' Label='Len nadol' Control='toggle' OptionRef='Down'/>"
          + "</MenuGroup></MenuItem></MenuGroup>";
    }
    menu += "<MenuGroup Key='prayers' Label='Texty modlitieb'>"
        + "<MenuGroup Key='prayers.presentation' Label='Zobrazenie'>"
        + "<MenuItem Key='prayers.verses' Label='číslovanie veršov' Control='toggle' OptionRef='Verse'/>"
        + "<MenuItem Key='prayers.references' Label='biblické odkazy' Control='toggle' OptionRef='References'/></MenuGroup>";
    if (full) menu += "<MenuGroup Key='prayers.celebration' Label='Slávenie'>"
        + "<MenuItem Key='prayers.common' Label='časti modlitby zo spoločnej časti' Control='choice' OptionRef='Opt3Communia' ValuesRef='LiturgicalCelebrationCommuniaValues' ValueAttribute='Id'/></MenuGroup>";
    menu += "</MenuGroup>";
    if (full) menu += "<MenuGroup Key='speech' Label='Hlasový výstup'>"
        + "<MenuItem Key='speech.rate' Label='Rýchlosť' Control='number' Handler='speech.rate'/>"
        + "<MenuItem Key='speech.psalm-pauses' Label='Pauzy' Control='toggle' Handler='speech.psalm-pauses'/>"
        + "<MenuItem Key='speech.help' Label='Návod' Control='action' Handler='speech.help'/></MenuGroup>";
    return "<LHData>" + menu + "</Menu><Options>" + options + "</Options>"
        + "<SupportedLanguages Name='j'><Language Value='sk' Locale='sk'>slovenčina</Language>"
        + "<Language Value='cz' Locale='cs'>čeština</Language></SupportedLanguages>"
        + "<SupportedValues><LiturgicalCalendarValues Name='k' Value=''>"
        + "<Calendar>všeobecný</Calendar>" + (full ? "<Calendar Value='sj'>jezuiti</Calendar>" : "")
        + "</LiturgicalCalendarValues><LiturgicalCelebrationCommuniaValues>"
        + "<LiturgicalCelebrationCommunia Id='4'>učiteľov Cirkvi</LiturgicalCelebrationCommunia>"
        + "<LiturgicalCelebrationCommunia Id='7'>viacerých mučeníkov</LiturgicalCelebrationCommunia>"
        + "</LiturgicalCelebrationCommuniaValues></SupportedValues></LHData>";
  }

  private static SettingsXml settings(boolean full) throws Exception {
    return SettingsXml.parse(settingsXml(full));
  }

  static void awaitSettings(XmlSettingsActivity activity) {
    try {
      ExecutorService worker = ReflectionHelpers.getField(activity, "worker");
      worker.submit(() -> {}).get(10, TimeUnit.SECONDS);
      Shadows.shadowOf(Looper.getMainLooper()).idle();
    } catch (Exception error) { throw new AssertionError(error); }
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
  @SuppressWarnings({"rawtypes", "unchecked"})
  public void nestedGroupsDisplayAllControlsInXmlOrder() throws Exception {
    String verse = "<MenuItem Key='prayers.verses' Label='číslovanie veršov' Control='toggle' OptionRef='Verse'/>";
    String xml = settingsXml(true).replace(verse,
        "<MenuItem Key='prayers.before' Label='Pred skupinou' Control='toggle' OptionRef='References'/>"
        + "<MenuGroup Key='prayers.nested' Label='Vnorená skupina'>" + verse + "</MenuGroup>");
    Intent intent = XmlSettingsActivity.entryIntent(RuntimeEnvironment.getApplication(), "prayers");
    try (ActivityController<XmlSettingsActivity> controller = Robolectric.buildActivity(
        XmlSettingsActivity.class, intent).create()) {
      XmlSettingsActivity activity = controller.get();
      show(activity, SettingsXml.parse(xml));
      RecyclerView recycler = recycler(activity.navigationView);
      RecyclerView.Adapter adapter = recycler.getAdapter();
      java.util.List<Integer> displayed = new java.util.ArrayList<>();
      for (int position = 0; position < adapter.getItemCount(); ++position) {
        RecyclerView.ViewHolder holder = adapter.createViewHolder(recycler, adapter.getItemViewType(position));
        adapter.bindViewHolder(holder, position);
        displayed.add(holder.itemView.getId());
      }
      int previous = -1;
      for (String key : new String[]{"prayers.before", "prayers.verses", "prayers.references", "prayers.common"}) {
        int position = displayed.indexOf(activity.menuItem(key).getItemId());
        assertTrue("Control missing or out of order: " + key, position > previous);
        previous = position;
      }
    }
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
      MenuItem group = activity.navigationView.getMenu().getItem(0);
      assertEquals("Texty modlitieb", group.getTitle().toString());
      activity.navigationView.getMenu().performIdentifierAction(group.getItemId(), 0);
      Intent intent = Shadows.shadowOf(activity).getNextStartedActivity();
      assertEquals(XmlSettingsActivity.class.getName(), intent.getComponent().getClassName());
      assertEquals("prayers", intent.getStringExtra("settings_group"));
    }
  }

  @Test
  public void refreshedSubmenuSwitchesStillSavePreferences() throws Exception {
    Intent intent = new Intent().putExtra("settings_group", "prayers");
    try (ActivityController<XmlSettingsActivity> controller =
        Robolectric.buildActivity(XmlSettingsActivity.class, intent).create()) {
      XmlSettingsActivity activity = controller.get();
      show(activity, settings(true));
      show(activity, settings(false));
      MenuItem verse = activity.menuItem("prayers.verses");
      CompoundButton toggle = (CompoundButton)verse.getActionView();
      assertEquals("Číslovanie veršov", verse.getTitle().toString());
      assertTrue(toggle.isChecked());
      toggle.performClick();
      assertFalse(toggle.isChecked());
      assertEquals("0", new UrlOptions(BreviarApp.getUrlOptions(activity)).params.get("o0"));
    }
  }

  @Test
  @Config(sdk = {24, 35})
  @SuppressWarnings({"rawtypes", "unchecked"})
  public void nestedChoicesOpenAsSeparateActivities() throws Exception {
    Context context = RuntimeEnvironment.getApplication();
    for (String[] path : new String[][]{
        {"appearance", "reading.navigation"}, {"prayers", "prayers.common"}}) {
      try (ActivityController<XmlSettingsActivity> parent = Robolectric.buildActivity(
          XmlSettingsActivity.class, XmlSettingsActivity.entryIntent(context, path[0])).setup()) {
        XmlSettingsActivity activity = parent.get();
        awaitSettings(activity);
        int itemId = activity.menuItem(path[1]).getItemId();
        RecyclerView list = recycler(activity.navigationView);
        RecyclerView.Adapter adapter = list.getAdapter();
        boolean clicked = false;
        // Position zero is Material's shared header view, already attached to the list.
        for (int i = 1; i < adapter.getItemCount(); ++i) {
          RecyclerView.ViewHolder holder = adapter.createViewHolder(list, adapter.getItemViewType(i));
          adapter.bindViewHolder(holder, i);
          if (holder.itemView.getId() == itemId) {
            clicked = holder.itemView.performClick();
            break;
          }
        }
        assertTrue("The displayed row must open the choice", clicked);
        Intent intent = Shadows.shadowOf(activity).getNextStartedActivity();
        assertNotNull(intent);
        assertEquals(path[1], intent.getStringExtra("settings_group"));
        // Both screens use the same class: singleTop would silently reuse the parent.
        ActivityInfo info = context.getPackageManager().getActivityInfo(intent.getComponent(), 0);
        assertEquals(ActivityInfo.LAUNCH_MULTIPLE, info.launchMode);
        assertEquals(0, intent.getFlags() & (Intent.FLAG_ACTIVITY_SINGLE_TOP | Intent.FLAG_ACTIVITY_CLEAR_TOP));
        parent.pause().stop();
        try (ActivityController<XmlSettingsActivity> child =
            Robolectric.buildActivity(XmlSettingsActivity.class, intent).setup()) {
          awaitSettings(child.get());
          assertTrue(child.get().navigationView.getMenu().getItem(0).isCheckable());
          child.get().onSupportNavigateUp();
          assertTrue(child.get().isFinishing());
        }
        parent.restart().start().resume();
        awaitSettings(activity);
        assertNotNull(activity.menuItem(path[1]));
      }
    }
  }

  @Test
  @Config(sdk = {24, 35})
  public void languageSwitchHasASeparatorInBothAppearances() {
    Context context = RuntimeEnvironment.getApplication();
    for (boolean eink : new boolean[]{false, true}) {
      BreviarApp.setEinkMode(context, eink);
      try (ActivityController<LangSelect> controller = Robolectric.buildActivity(LangSelect.class).setup()) {
        LangSelect activity = controller.get();
        awaitSettings(activity);
        Menu menu = activity.navigationView.getMenu();
        assertEquals(3, menu.size());
        assertSame(activity.menuItem("language.use-for-interface"), menu.getItem(2));
        RecyclerView.Adapter<?> adapter = recycler(activity.navigationView).getAdapter();
        assertEquals(5, adapter.getItemCount()); // Header, two languages, divider, switch.
        assertNotEquals(adapter.getItemViewType(2), adapter.getItemViewType(3));
        assertEquals(adapter.getItemViewType(2), adapter.getItemViewType(4));
      }
    }
  }

  @Test public void calendarIsNoLongerListedInMainSettings() throws Exception {
    try (ActivityController<MainSettings> controller = Robolectric.buildActivity(MainSettings.class).setup()) {
      MainSettings activity = controller.get();
      awaitSettings(activity);
      Menu menu = activity.navigationView.getMenu();
      assertEquals(4, menu.size()); // Visible XML root groups; language/calendar are promoted.
      for (int i = 0; i < menu.size(); ++i) {
        assertFalse(menu.getItem(i).getTitle().toString().startsWith(
            activity.getString(R.string.calendar_settings_title)));
      }
    }
  }

  @Test
  @Config(sdk = {24, 35})
  public void commonPartsChoiceOpensCheckedListAndRefreshesParent() throws Exception {
    Context context = RuntimeEnvironment.getApplication();
    // The XML supplies the effective selection, including canonicalized aliases.
    BreviarApp.setUrlOptions(context, "&amp;o3=27&amp;of3=0&amp;k=sj&amp;o0=123");
    try (ActivityController<XmlSettingsActivity> parent = Robolectric.buildActivity(XmlSettingsActivity.class,
        XmlSettingsActivity.entryIntent(context, "prayers")).setup()) {
      XmlSettingsActivity settings = parent.get();
      awaitSettings(settings);
      Menu menu = settings.navigationView.getMenu();
      MenuItem commonParts = settings.menuItem("prayers.common");
      assertEquals("Časti modlitby zo spoločnej časti\nUčiteľov Cirkvi", commonParts.getTitle());
      menu.performIdentifierAction(commonParts.getItemId(), 0);
      Intent intent = Shadows.shadowOf(settings).getNextStartedActivity();
      assertEquals(XmlSettingsActivity.class.getName(), intent.getComponent().getClassName());
      assertEquals("prayers.common", intent.getStringExtra("settings_group"));
      parent.pause().stop();

      try (ActivityController<XmlSettingsActivity> child =
          Robolectric.buildActivity(XmlSettingsActivity.class, intent).setup()) {
        XmlSettingsActivity activity = child.get();
        awaitSettings(activity);
        assertEquals("Časti modlitby zo spoločnej časti", activity.getSupportActionBar().getTitle());
        Menu choices = activity.navigationView.getMenu();
        assertEquals(2, choices.size());
        assertTrue(choices.getItem(0).isChecked());
        assertFalse(choices.getItem(1).isChecked());
        assertNotNull(choices.getItem(0).getIcon());
        assertNull(choices.getItem(0).getActionView());
        choices.performIdentifierAction(choices.getItem(1).getItemId(), 0);
        assertTrue(activity.isFinishing());
        assertFalse(choices.getItem(0).isChecked());
        assertTrue(choices.getItem(1).isChecked());
        UrlOptions saved = new UrlOptions(BreviarApp.getUrlOptions(context));
        assertEquals("7", saved.params.get("o3"));
        assertFalse(saved.params.containsKey("of3"));
        assertEquals("sj", saved.params.get("k"));
        assertEquals("123", saved.params.get("o0"));
      }

      parent.restart().start().resume();
      awaitSettings(settings);
      Menu refreshed = settings.navigationView.getMenu();
      assertEquals("Časti modlitby zo spoločnej časti\nViacerých mučeníkov",
          settings.menuItem("prayers.common").getTitle());

      String saved = BreviarApp.getUrlOptions(context);
      try (ActivityController<XmlSettingsActivity> child =
          Robolectric.buildActivity(XmlSettingsActivity.class, intent).setup()) {
        XmlSettingsActivity activity = child.get();
        awaitSettings(activity);
        assertFalse(activity.navigationView.getMenu().getItem(0).isChecked());
        assertTrue(activity.navigationView.getMenu().getItem(1).isChecked());
        activity.onSupportNavigateUp();
        assertTrue(activity.isFinishing());
        assertEquals(saved, BreviarApp.getUrlOptions(context));
      }
    }
  }

  @Test
  @Config(sdk = {24, 35})
  public void calendarChoicePersistsAndDefaultCanBeRestored() throws Exception {
    Context context = RuntimeEnvironment.getApplication();
    BreviarApp.setUrlOptions(context, "&amp;o0=123&amp;d=16&amp;p=mc&amp;bc=ffeeaa");
    for (int selection : new int[]{1, 0}) {
      try (ActivityController<XmlSettingsActivity> controller = Robolectric.buildActivity(
          XmlSettingsActivity.class, XmlSettingsActivity.calendarIntent(context)).setup()) {
        XmlSettingsActivity activity = controller.get();
        awaitSettings(activity);
        assertEquals(activity.getString(R.string.calendar_settings_title), activity.getSupportActionBar().getTitle());
        Menu menu = activity.navigationView.getMenu();
        assertEquals(3, menu.size()); // XML calendar section, then the choices.
        assertSame(activity.menuItem("calendar.epiphany"), menu.getItem(0).getSubMenu().getItem(0));
        assertFalse(menu.getItem(1 + selection).isChecked());
        assertTrue(menu.getItem(2 - selection).isChecked());
        menu.performIdentifierAction(menu.getItem(1 + selection).getItemId(), 0);
        assertFalse(activity.isFinishing());
        assertNotNull(activity.menuItem("calendar.epiphany"));
        assertTrue(menu.getItem(1 + selection).isChecked());
        assertFalse(menu.getItem(2 - selection).isChecked());
        UrlOptions saved = new UrlOptions(BreviarApp.getUrlOptions(context));
        assertEquals(selection == 1 ? "sj" : "", saved.params.get("k"));
        assertEquals("123", saved.params.get("o0"));
        assertEquals("16", saved.params.get("d"));
        assertEquals("mc", saved.params.get("p"));
        assertEquals("ffeeaa", saved.params.get("bc"));
      }
    }
  }

  @Test public void calendarCheckUsesEffectiveXmlValueRatherThanStalePreference() throws Exception {
    Context context = RuntimeEnvironment.getApplication();
    BreviarApp.setUrlOptions(context, "&amp;k=unsupported");
    try (ActivityController<XmlSettingsActivity> controller = Robolectric.buildActivity(
        XmlSettingsActivity.class, XmlSettingsActivity.calendarIntent(context)).setup()) {
      XmlSettingsActivity activity = controller.get();
      awaitSettings(activity);
      assertTrue(activity.navigationView.getMenu().getItem(1).isChecked());
      assertFalse(activity.navigationView.getMenu().getItem(2).isChecked());
    }
  }

  @Test public void singleUnnamedCalendarStillHasALabelAndCheckMark() throws Exception {
    Context context = RuntimeEnvironment.getApplication();
    try (ActivityController<XmlSettingsActivity> controller = Robolectric.buildActivity(
        XmlSettingsActivity.class, XmlSettingsActivity.calendarIntent(context)).create()) {
      XmlSettingsActivity activity = controller.get();
      show(activity, SettingsXml.parse(settingsXml(false).replace("všeobecný", "")));
      Menu menu = activity.navigationView.getMenu();
      assertEquals(2, menu.size()); // Nested section and one choice.
      assertEquals(activity.getString(R.string.default_calendar), menu.getItem(1).getTitle());
      assertTrue(menu.getItem(1).isChecked());
    }
  }

  @Test public void xmlOwnsLayoutAndUnsupportedHandlersHideTheirChildren() throws Exception {
    String xml = settingsXml(true).replace("Key='device' Label='zariadenie'", "Key='custom' Label='Custom section'")
        .replace("</Menu>", "<MenuGroup Key='unsupported'>"
            + "<MenuItem Key='unknown' Label='Unknown' Control='choice' Handler='future.handler'>"
            + "<MenuGroup Key='unknown.children'><MenuItem Key='hidden-child' Label='Hidden' Control='toggle' OptionRef='Verse'/></MenuGroup>"
            + "</MenuItem><MenuItem Key='unknown-control' Label='Unknown control' Control='future'/></MenuGroup></Menu>");
    try (ActivityController<MainSettings> controller = Robolectric.buildActivity(MainSettings.class).create()) {
      MainSettings activity = controller.get();
      show(activity, SettingsXml.parse(xml));
      assertEquals(4, activity.navigationView.getMenu().size());
      assertEquals("Custom section", activity.navigationView.getMenu().getItem(0).getTitle());
      assertNull(activity.menuItem("unsupported"));
      assertNull(activity.menuItem("general"));
    }
    try (ActivityController<XmlSettingsActivity> controller = Robolectric.buildActivity(XmlSettingsActivity.class,
        XmlSettingsActivity.entryIntent(RuntimeEnvironment.getApplication(), "custom")).create()) {
      show(controller.get(), SettingsXml.parse(xml));
      assertEquals(5, controller.get().navigationView.getMenu().size());
      assertNotNull(controller.get().menuItem("device.eink"));
    }
  }

  @Test public void calendarOptionsShareTheWordWithoutChangingTheCalendar() {
    Context context = RuntimeEnvironment.getApplication();
    long initial = (1L << 40) | 1;
    BreviarApp.setUrlOptions(context, "&amp;k=sj&amp;o0=" + initial + "&amp;of0v=1&amp;of2nr=1");
    try (ActivityController<XmlSettingsActivity> controller = Robolectric.buildActivity(XmlSettingsActivity.class,
        XmlSettingsActivity.calendarIntent(context)).setup()) {
      XmlSettingsActivity activity = controller.get();
      awaitSettings(activity);
      ((CompoundButton)activity.menuItem("calendar.epiphany").getActionView()).performClick();
      awaitSettings(activity);
      UrlOptions saved = activity.options();
      assertEquals(Long.toString(initial | 8), saved.params.get("o0"));
      assertEquals("sj", saved.params.get("k"));
      assertFalse(saved.params.containsKey("of0v"));
      assertEquals("1", saved.params.get("of2nr"));
      assertTrue(activity.navigationView.getMenu().getItem(2).isChecked());
      assertTrue(((CompoundButton)activity.menuItem("calendar.epiphany").getActionView()).isChecked());
    }
  }

  @Test public void scalarEditorsUseXmlBoundsAndExplicitResetValues() {
    Context context = RuntimeEnvironment.getApplication();
    BreviarApp.setUrlOptions(context, "&amp;mm=30&amp;ff=18&amp;c0=ffeeaa&amp;k=sj");
    try (ActivityController<DisplaySettings> controller = Robolectric.buildActivity(DisplaySettings.class).setup()) {
      DisplaySettings activity = controller.get();
      awaitSettings(activity);
      SettingsActivity.IntOptionInfo margin = activity.int_handlers.get(activity.menuItem("appearance.margin").getItemId());
      assertEquals(1, margin.min);
      assertEquals(200, margin.max);
      assertEquals(30, margin.int_option.get());
      margin.int_option.reset();
      awaitSettings(activity);
      assertEquals("", activity.options().params.get("mm"));
      margin = activity.int_handlers.get(activity.menuItem("appearance.margin").getItemId());
      assertEquals(5, margin.int_option.get());
      BreviarApp.setString(context, "scale", "1.5");
      activity.int_handlers.get(activity.menuItem("appearance.font-size").getItemId()).int_option.reset();
      awaitSettings(activity);
      assertEquals("12", activity.options().params.get("ff"));
      assertEquals("", BreviarApp.getString(context, "scale", ""));
      SettingsActivity.ColorOption color = activity.color_options.get(activity.menuItem("appearance.background-day").getItemId()).color_option;
      assertEquals("ffeeaa", color.get());
      color.set("ddeeff");
      awaitSettings(activity);
      activity.color_options.get(activity.menuItem("appearance.background-day").getItemId()).color_option.reset();
      awaitSettings(activity);
      assertEquals("", activity.options().params.get("c0"));
      assertEquals("sj", activity.options().params.get("k"));
    }
  }

  @Test public void refreshPreservesScrollPosition() throws Exception {
    StringBuilder extra = new StringBuilder();
    for (int i = 0; i < 40; ++i) extra.append("<MenuItem Key='extra." + i + "' Label='Option " + i
        + "' Control='toggle' OptionRef='Verse'/>");
    SettingsXml data = SettingsXml.parse(settingsXml(false).replace("<MenuGroup Key='prayers.presentation'", extra + "<MenuGroup Key='prayers.presentation'"));
    try (ActivityController<XmlSettingsActivity> controller = Robolectric.buildActivity(XmlSettingsActivity.class,
        XmlSettingsActivity.entryIntent(RuntimeEnvironment.getApplication(), "prayers")).create()) {
      XmlSettingsActivity activity = controller.get();
      show(activity, data);
      RecyclerView list = recycler(activity.navigationView);
      list.measure(View.MeasureSpec.makeMeasureSpec(600, View.MeasureSpec.EXACTLY), View.MeasureSpec.makeMeasureSpec(500, View.MeasureSpec.EXACTLY));
      list.layout(0, 0, 600, 500);
      LinearLayoutManager layout = (LinearLayoutManager)list.getLayoutManager();
      layout.scrollToPositionWithOffset(20, 0);
      list.measure(View.MeasureSpec.makeMeasureSpec(600, View.MeasureSpec.EXACTLY), View.MeasureSpec.makeMeasureSpec(500, View.MeasureSpec.EXACTLY));
      list.layout(0, 0, 600, 500);
      int position = layout.findFirstVisibleItemPosition();
      assertTrue("Expected scrolled list, position=" + position, position > 0);
      show(activity, data);
      RecyclerView replacement = recycler(activity.navigationView);
      replacement.measure(View.MeasureSpec.makeMeasureSpec(600, View.MeasureSpec.EXACTLY), View.MeasureSpec.makeMeasureSpec(500, View.MeasureSpec.EXACTLY));
      replacement.layout(0, 0, 600, 500);
      assertEquals(position, ((LinearLayoutManager)replacement.getLayoutManager()).findFirstVisibleItemPosition());
    }
  }

  @Implements(value = Server.class, isInAndroidSdk = false)
  public static class SlowSettingsServer extends SettingsServer {
    static CountDownLatch entered, release;
    @Implementation protected static String getSettingsXml(Context context, String options, String language) {
      String result = SettingsServer.getSettingsXml(context, options, language);
      if (entered != null) {
        entered.countDown();
        try { assertTrue(release.await(10, TimeUnit.SECONDS)); }
        catch (InterruptedException error) { throw new AssertionError(error); }
      }
      return result;
    }
  }

  @Test @Config(shadows = SlowSettingsServer.class)
  public void pendingRefreshCannotUndoEditsOrLoseAnotherBitInTheSameWord() throws Exception {
    BreviarApp.setUrlOptions(RuntimeEnvironment.getApplication(), "&amp;o0=1&amp;of0v=1");
    try (ActivityController<XmlSettingsActivity> controller = Robolectric.buildActivity(XmlSettingsActivity.class,
        XmlSettingsActivity.entryIntent(RuntimeEnvironment.getApplication(), "prayers")).setup()) {
      XmlSettingsActivity activity = controller.get();
      awaitSettings(activity);
      SlowSettingsServer.entered = new CountDownLatch(1);
      SlowSettingsServer.release = new CountDownLatch(1);
      controller.pause().stop().restart().start().resume();
      assertTrue(SlowSettingsServer.entered.await(10, TimeUnit.SECONDS));
      try {
        ((CompoundButton)activity.menuItem("prayers.verses").getActionView()).performClick();
        ((CompoundButton)activity.menuItem("prayers.references").getActionView()).performClick();
      } finally {
        SlowSettingsServer.release.countDown();
      }
      awaitSettings(activity);
      assertEquals("2", activity.options().params.get("o0"));
      assertFalse(activity.options().params.containsKey("of0v"));
      assertFalse(((CompoundButton)activity.menuItem("prayers.verses").getActionView()).isChecked());
      assertTrue(((CompoundButton)activity.menuItem("prayers.references").getActionView()).isChecked());
    }
  }
}

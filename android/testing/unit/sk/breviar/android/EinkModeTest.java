package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.os.Looper;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.WebView;
import android.widget.CompoundButton;
import android.widget.TextView;
import androidx.recyclerview.widget.RecyclerView;
import com.google.android.material.navigation.NavigationView;
import androidx.appcompat.widget.Toolbar;
import androidx.core.view.GravityCompat;
import androidx.core.view.WindowCompat;
import androidx.drawerlayout.widget.DrawerLayout;
import java.io.ByteArrayOutputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.time.Duration;
import java.util.ArrayList;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.Shadows;
import org.robolectric.android.controller.ActivityController;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.GraphicsMode;
import org.robolectric.annotation.LooperMode;
import org.robolectric.util.ReflectionHelpers;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = 35, shadows = XmlSettingsActivityTest.SettingsServer.class)
@LooperMode(LooperMode.Mode.PAUSED)
public class EinkModeTest {
  private final Context context = RuntimeEnvironment.getApplication();

  private static Server server(Context context) {
    return ReflectionHelpers.callConstructor(Server.class,
        ReflectionHelpers.ClassParameter.from(Context.class, context));
  }

  // Exercise the real reader lifecycle, navigation and WebView, without JNI or a server thread.
  public static class Reader extends Breviar {
    @Override synchronized void initServer(String opts) {
      S = server(this);
      S.port = 50000;
      S.port_nonpersistent = 50001;
      S.setOpts(opts);
    }
    @Override synchronized void stopServer() { S = null; }
    @Override protected void syncScale() {} // Robolectric does not execute zoom.js.
  }

  @Test
  public void switchRecreatesDeviceSettingsAndPreservesPrayerPreferences() {
    String options = "&amp;o0=123&amp;o1=456&amp;f=Georgia&amp;bc=ffeeaa";
    BreviarApp.setUrlOptions(context, options);
    assertFalse(BreviarApp.getEinkMode(context));
    try (ActivityController<DeviceSettings> controller = Robolectric.buildActivity(DeviceSettings.class).setup()) {
      DeviceSettings activity = controller.get();
      CompoundButton toggle = (CompoundButton)activity.navigationView.getMenu()
          .findItem(R.id.eink_mode).getActionView();
      toggle.performClick();
      assertTrue(BreviarApp.getEinkMode(context));
      Shadows.shadowOf(Looper.getMainLooper()).idle();
      assertNotSame(activity, controller.get());
      assertEquals(options, BreviarApp.getUrlOptions(context));
    }
    try (ActivityController<DeviceSettings> controller = Robolectric.buildActivity(DeviceSettings.class).setup()) {
      DeviceSettings activity = controller.get();
      assertEquals(Color.WHITE, ((ColorDrawable)activity.navigationView.getBackground()).getColor());
      assertEquals(Color.BLACK, activity.navigationView.getItemTextColor().getDefaultColor());
      CompoundButton toggle = (CompoundButton)activity.navigationView.getMenu()
          .findItem(R.id.eink_mode).getActionView();
      assertTrue(toggle.isChecked());
      toggle.performClick();
      assertFalse(BreviarApp.getEinkMode(context));
      Shadows.shadowOf(Looper.getMainLooper()).idle();
      assertNotSame(activity, controller.get());
      assertEquals(options, BreviarApp.getUrlOptions(context));
    }
  }

  @Test
  public void parentSettingsRecreateWhenReturningAfterModeChange() {
    try (ActivityController<SettingsActivity> controller = Robolectric.buildActivity(SettingsActivity.class).setup()) {
      SettingsActivity previous = controller.get();
      controller.pause().stop();
      BreviarApp.setEinkMode(context, true);
      controller.restart().start().resume();
      Shadows.shadowOf(Looper.getMainLooper()).idle();
      assertNotSame(previous, controller.get());
    }
  }

  private String stylesheet(Server server) throws Exception {
    ByteArrayOutputStream response = new ByteArrayOutputStream();
    server.handleFile(new Socket() {
      @Override public OutputStream getOutputStream() { return response; }
    }, "breviar.css", true);
    return response.toString("UTF-8");
  }

  @Test
  public void serverKeepsStandardCssAndSavedOptionsInEinkMode() throws Exception {
    Server server = server(context);
    server.setOpts("&amp;o0=123");
    String standard = stylesheet(server);
    assertFalse(standard.contains("color-scheme: light !important"));
    BreviarApp.setEinkMode(context, true);
    String eink = stylesheet(server);
    assertEquals(standard, eink);
    assertEquals("&amp;o0=123", server.getOpts());
    BreviarApp.setEinkMode(context, false);
    assertEquals(standard, stylesheet(server));
  }

  @Test
  public void readerHasPagingAndInstantDrawerAndPreservesLocationOnModeChange() {
    BreviarApp.setEinkMode(context, true);
    BreviarApp.setString(context, "version", context.getString(R.string.version));
    Bundle state = new Bundle();
    state.putString("wv-url", "http://127.0.0.1:50000/l.cgi?qt=pdt&d=14&m=10&r=2026&p=1");
    state.putFloat("wv-scroll-to", 0.4f);
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class)
        .create(state).start().restoreInstanceState(state).postCreate(state).resume().visible()) {
      Reader reader = controller.get();
      assertTrue(reader.wv.getUrl().contains("d=14"));
      assertTrue(reader.wv.getUrl().contains("p=1"));
      assertEquals(0.4f, reader.scroll_to, 0.001f);
      assertEquals(View.VISIBLE, reader.findViewById(R.id.navigation_paging).getVisibility());
      assertEquals(View.OVER_SCROLL_NEVER, reader.wv.getOverScrollMode());
      assertEquals(DrawerLayout.LOCK_MODE_LOCKED_CLOSED, reader.drawer.getDrawerLockMode(GravityCompat.START));
      reader.onKeyDown(KeyEvent.KEYCODE_MENU, new KeyEvent(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_MENU));
      assertTrue(reader.drawer.isDrawerOpen(GravityCompat.START));
      reader.onKeyDown(KeyEvent.KEYCODE_MENU, new KeyEvent(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_MENU));
      assertFalse(reader.drawer.isDrawerOpen(GravityCompat.START));
      reader.onCreateOptionsMenu(reader.toolbar.getMenu());
      assertTrue(reader.toolbar.getMenu().findItem(R.id.nightmodeBtn).isVisible());
      assertTrue(reader.navigationView.getMenu().findItem(R.id.nightmode_toggle).isVisible());

      controller.pause().stop();
      BreviarApp.setEinkMode(context, false);
      controller.restart().start().resume();
      Shadows.shadowOf(Looper.getMainLooper()).idle();
      assertNotSame(reader, controller.get());
      assertTrue(controller.get().wv.getUrl().contains("d=14"));
      assertTrue(controller.get().wv.getUrl().contains("p=1"));
      assertEquals(0.4f, controller.get().scroll_to, 0.001f);
      // Navigation remains independent of the newly selected appearance.
      assertEquals(View.VISIBLE, controller.get().findViewById(R.id.navigation_paging).getVisibility());
    }
  }

  private static void clickDrawerButton(Reader reader) {
    ArrayList<View> buttons = new ArrayList<>();
    reader.toolbar.findViewsWithText(buttons, reader.toolbar.getNavigationContentDescription(),
        View.FIND_VIEWS_WITH_CONTENT_DESCRIPTION);
    assertEquals(1, buttons.size());
    assertTrue(buttons.get(0).performClick());
    // Robolectric does not draw frames; drive DrawerLayout's normal animation.
    for (int frame = 0; frame < 60; ++frame) {
      Shadows.shadowOf(Looper.getMainLooper()).idleFor(Duration.ofMillis(16));
      reader.drawer.computeScroll();
    }
  }

  @Test
  @Config(sdk = {24, 35})
  public void drawerButtonWorksAfterSwitchingEinkOnAndOffFromFullscreenNightMode() {
    BreviarApp.setString(context, "version", context.getString(R.string.version));
    BreviarApp.setUrlOptions(context, "&amp;c=1");
    context.getSharedPreferences(Util.prefname, 0).edit().putBoolean("fullscreen", true).commit();
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup().visible()) {
      Reader reader = controller.get();
      int standardBackground = ((ColorDrawable)reader.getWindow().getDecorView().getBackground()).getColor();
      assertTrue(reader.fullscreen);
      MotionEvent tap = MotionEvent.obtain(0, 0, MotionEvent.ACTION_DOWN, 100, 100, 0);
      reader.onDoubleTap(tap);
      tap.recycle();
      assertFalse(reader.fullscreen);
      clickDrawerButton(reader);
      assertTrue(reader.drawer.isDrawerOpen(GravityCompat.START));
      clickDrawerButton(reader);
      assertFalse(reader.drawer.isDrawerOpen(GravityCompat.START));

      for (boolean eink : new boolean[]{true, false, true, false}) {
        controller.pause().stop();
        BreviarApp.setEinkMode(context, eink);
        controller.restart().start().resume();
        Shadows.shadowOf(Looper.getMainLooper()).idle();
        assertNotSame(reader, controller.get());
        reader = controller.get();
        assertFalse(reader.fullscreen);
        assertTrue(new UrlOptions(Breviar.S.getOpts()).isNightmode());
        assertEquals(eink ? Color.WHITE : standardBackground,
            ((ColorDrawable)reader.getWindow().getDecorView().getBackground()).getColor());
        assertEquals(eink, WindowCompat.getInsetsController(reader.getWindow(),
            reader.getWindow().getDecorView()).isAppearanceLightStatusBars());
        assertEquals(eink ? DrawerLayout.LOCK_MODE_LOCKED_CLOSED : DrawerLayout.LOCK_MODE_UNLOCKED,
            reader.drawer.getDrawerLockMode(GravityCompat.START));
        clickDrawerButton(reader);
        assertTrue("Hamburger must open the drawer after e-ink=" + eink,
            reader.drawer.isDrawerOpen(GravityCompat.START));
        clickDrawerButton(reader);
        assertFalse(reader.drawer.isDrawerOpen(GravityCompat.START));
        reader.toggleFullscreen();
        reader.toggleFullscreen();
        clickDrawerButton(reader);
        assertTrue(reader.drawer.isDrawerOpen(GravityCompat.START));
        clickDrawerButton(reader);
      }
      // A normal recreation retains an open standard drawer and a working
      // close button; applying the mode must not discard unrelated view state.
      clickDrawerButton(reader);
      controller.recreate();
      reader = controller.get();
      assertTrue(reader.drawer.isDrawerOpen(GravityCompat.START));
      assertEquals(reader.getString(R.string.navigation_drawer_close),
          reader.toolbar.getNavigationContentDescription());
      clickDrawerButton(reader);
      assertFalse(reader.drawer.isDrawerOpen(GravityCompat.START));
    }
  }

  @Test
  @Config(sdk = {24, 35})
  public void systemBarsResetFromThemeWhenWindowIsReused() {
    try (ActivityController<DeviceSettings> controller = Robolectric.buildActivity(DeviceSettings.class)
        .create().start().resume().visible()) {
      DeviceSettings activity = controller.get();
      View decor = activity.getWindow().getDecorView();
      int standardBackground = ((ColorDrawable)decor.getBackground()).getColor();
      // Android may retain the old window during recreation. Simulate e-ink
      // appearance surviving until onPostCreate, after hierarchy restoration.
      decor.setBackgroundColor(Color.WHITE);
      WindowCompat.getInsetsController(activity.getWindow(), decor).setAppearanceLightStatusBars(true);
      WindowCompat.getInsetsController(activity.getWindow(), decor).setAppearanceLightNavigationBars(true);
      assertTrue(WindowCompat.getInsetsController(activity.getWindow(), decor).isAppearanceLightStatusBars());
      controller.postCreate(null);
      assertEquals(standardBackground, ((ColorDrawable)decor.getBackground()).getColor());
      assertFalse(WindowCompat.getInsetsController(activity.getWindow(), decor).isAppearanceLightStatusBars());
      assertFalse(WindowCompat.getInsetsController(activity.getWindow(), decor).isAppearanceLightNavigationBars());
    }
  }

  @Test
  public void einkReaderSupportsNightModeAndReadableSearchAfterCreation() {
    BreviarApp.setEinkMode(context, true);
    BreviarApp.setUrlOptions(context, "&amp;c=1");
    BreviarApp.setString(context, "version", context.getString(R.string.version));
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class)
        .create().start().resume().postCreate(null).visible()) {
      Reader reader = controller.get();
      assertTrue(new UrlOptions(Breviar.S.getOpts()).isNightmode());
      assertEquals(Color.WHITE, reader.searchEdit.getCurrentTextColor());
      assertEquals(Color.WHITE, reader.searchEdit.getCurrentHintTextColor());
      assertEquals(0xFF2D2D2D, ((ColorDrawable)reader.searchContainer.getBackground()).getColor());
      reader.toggleNightMode();
      assertFalse(new UrlOptions(Breviar.S.getOpts()).isNightmode());
      assertEquals(Color.BLACK, reader.searchEdit.getCurrentTextColor());
      reader.toggleNightMode();
      assertTrue(new UrlOptions(Breviar.S.getOpts()).isNightmode());
      assertTrue(reader.wv.getUrl().contains("c=1"));
      assertEquals(Color.WHITE, reader.searchEdit.getCurrentTextColor());
    }
  }

  @Test
  public void standardReaderKeepsExistingNavigation() {
    BreviarApp.setString(context, "version", context.getString(R.string.version));
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      Reader reader = controller.get();
      assertEquals(View.GONE, reader.findViewById(R.id.navigation_paging).getVisibility());
      assertEquals(DrawerLayout.LOCK_MODE_UNLOCKED, reader.drawer.getDrawerLockMode(GravityCompat.START));
      reader.onCreateOptionsMenu(reader.toolbar.getMenu());
      assertTrue(reader.toolbar.getMenu().findItem(R.id.nightmodeBtn).isVisible());
    }
  }

  private static class PagingView extends WebView {
    int delta;
    boolean animatedPage;
    PagingView(Context context) { super(context); }
    @Override public void scrollBy(int x, int y) { delta = y; }
    @Override public boolean pageDown(boolean bottom) { animatedPage = true; return true; }
  }

  @Test
  public void pageTurnsJumpWithOverlapWhileStandardModeUsesWebViewPaging() {
    PagingView view = new PagingView(context);
    view.layout(0, 0, 600, 800);
    BreviarApp.setEinkMode(context, true);
    EinkUi.page(view, true);
    int step = view.delta;
    assertTrue(step > 0 && step < 800);
    assertFalse(view.animatedPage);
    EinkUi.page(view, false);
    assertEquals(-step, view.delta);
    BreviarApp.setEinkMode(context, false);
    EinkUi.page(view, true);
    assertTrue(view.animatedPage);
    view.destroy();
  }

  @Test
  public void helpContentAndAlarmsUseEinkAppearance() {
    BreviarApp.setEinkMode(context, true);
    Intent intent = new Intent().putExtra("content", context.getString(R.string.tts_settings_help_content));
    try (ActivityController<DialogActivity> controller = Robolectric.buildActivity(DialogActivity.class, intent).setup()) {
      String encoded = Shadows.shadowOf(controller.get().wv).getLastLoadData().data;
      String html = new String(android.util.Base64.decode(encoded, android.util.Base64.DEFAULT),
          java.nio.charset.StandardCharsets.UTF_8);
      assertTrue(html.contains("window.BreviarTaps"));
      assertEquals(intent.getStringExtra("content"), html.replaceAll("(?s)<script>.*?</script>", ""));
      assertEquals(View.VISIBLE, controller.get().findViewById(R.id.navigation_paging).getVisibility());
    }
    try (ActivityController<Alarms> controller = Robolectric.buildActivity(Alarms.class).setup()) {
      Toolbar toolbar = controller.get().findViewById(R.id.alarms_toolbar);
      assertEquals(Color.WHITE, ((ColorDrawable)toolbar.getBackground()).getColor());
      assertEquals(Color.BLACK, ((CompoundButton)controller.get().findViewById(R.id.inv_check)).getCurrentTextColor());
    }
  }

  @Test
  public void refreshedXmlSettingsAndCalendarDialogUseEinkAppearance() throws Exception {
    BreviarApp.setEinkMode(context, true);
    try (ActivityController<MainSettings> controller = Robolectric.buildActivity(MainSettings.class).setup()) {
      MainSettings activity = controller.get();
      java.util.concurrent.ExecutorService worker = ReflectionHelpers.getField(activity, "worker");
      worker.submit(() -> {}).get(10, java.util.concurrent.TimeUnit.SECONDS);
      Shadows.shadowOf(Looper.getMainLooper()).idle();
      assertEquals(Color.WHITE, ((ColorDrawable)activity.navigationView.getBackground()).getColor());
      assertEquals(Color.BLACK, activity.navigationView.getItemTextColor().getDefaultColor());
      android.view.Menu menu = activity.navigationView.getMenu();
      for (int i = 0; i < menu.size(); ++i) {
        if (menu.getItem(i).getTitle().toString().startsWith(context.getString(R.string.calendar_settings_title))) {
          menu.performIdentifierAction(menu.getItem(i).getItemId(), 0);
        }
      }
      androidx.appcompat.app.AlertDialog dialog = (androidx.appcompat.app.AlertDialog)
          org.robolectric.shadows.ShadowDialog.getLatestDialog();
      assertNotNull(dialog);
      android.widget.ListView list = dialog.getListView();
      android.widget.TextView row = (android.widget.TextView)list.getAdapter().getView(0, null, list);
      assertEquals(Color.BLACK, row.getCurrentTextColor());
      assertEquals(0, dialog.getWindow().getAttributes().flags & android.view.WindowManager.LayoutParams.FLAG_DIM_BEHIND);
      dialog.dismiss();
    }
  }

  @Test
  @Config(sdk = 24)
  public void androidSevenKeepsSystemNavigationButtonsVisible() {
    BreviarApp.setEinkMode(context, true);
    try (ActivityController<DeviceSettings> controller = Robolectric.buildActivity(DeviceSettings.class).setup()) {
      assertEquals(Color.BLACK, controller.get().getWindow().getNavigationBarColor());
      assertEquals(Color.WHITE, ((ColorDrawable)controller.get().navigationView.getBackground()).getColor());
    }
  }

  private static RecyclerView recycler(View view) {
    if (view instanceof RecyclerView) return (RecyclerView)view;
    if (view instanceof ViewGroup) {
      ViewGroup group = (ViewGroup)view;
      for (int i = 0; i < group.getChildCount(); ++i) {
        RecyclerView found = recycler(group.getChildAt(i));
        if (found != null) return found;
      }
    }
    return null;
  }

  private static void assertBlackText(View view) {
    if (view instanceof TextView) {
      TextView text = (TextView)view;
      if (text.getVisibility() == View.VISIBLE && text.getText().length() > 0) {
        assertEquals(text.getText().toString(), Color.BLACK, text.getCurrentTextColor());
      }
    }
    if (view instanceof ViewGroup) {
      ViewGroup group = (ViewGroup)view;
      for (int i = 0; i < group.getChildCount(); ++i) assertBlackText(group.getChildAt(i));
    }
  }

  @SuppressWarnings({"rawtypes", "unchecked"})
  private static void assertBoundMenuTextBlack(NavigationView menu) {
    RecyclerView list = recycler(menu);
    assertNotNull(list);
    RecyclerView.Adapter adapter = list.getAdapter();
    // Position zero is the single header view, which is already attached.
    for (int i = 0; i < menu.getHeaderCount(); ++i) assertBlackText(menu.getHeaderView(i));
    for (int i = 1; i < adapter.getItemCount(); ++i) {
      RecyclerView.ViewHolder holder = adapter.createViewHolder(list, adapter.getItemViewType(i));
      adapter.bindViewHolder(holder, i);
      assertBlackText(holder.itemView);
      holder.itemView.setPressed(true);
      assertBlackText(holder.itemView);
      holder.itemView.setPressed(false);
      adapter.onViewRecycled(holder);
      adapter.bindViewHolder(holder, i);
      assertBlackText(holder.itemView);
    }
  }

  @Test
  @Config(sdk = {24, 35})
  public void nativeSettingsRowsStayBlackWhenBoundAndRecycled() {
    BreviarApp.setEinkMode(context, true);
    for (Class<? extends SettingsActivity> screen : java.util.Arrays.<Class<? extends SettingsActivity>>asList(
        DeviceSettings.class, DisplaySettings.class, TtsSettings.class, LangSelect.class)) {
      try (ActivityController<? extends SettingsActivity> controller = Robolectric.buildActivity(screen).setup()) {
        assertBoundMenuTextBlack(controller.get().navigationView);
      }
    }
  }

  @Test
  public void drawerRowsStayBlackWhenBoundAndRecycled() {
    BreviarApp.setEinkMode(context, true);
    BreviarApp.setString(context, "version", context.getString(R.string.version));
    try (ActivityController<Reader> controller = Robolectric.buildActivity(Reader.class).setup()) {
      Reader reader = controller.get();
      reader.drawer.openDrawer(GravityCompat.START, false);
      assertBoundMenuTextBlack(reader.navigationView);
      reader.updateTtsState();
      reader.updateMenu();
      assertBoundMenuTextBlack(reader.navigationView);
    }
  }

  @Test
  @Config(sdk = {24, 35})
  public void menuThemeIsReadableBeforeLateStylingAndForCheckedItems() {
    BreviarApp.setEinkMode(context, true);
    try (ActivityController<SettingsActivity> controller = Robolectric.buildActivity(SettingsActivity.class).create()) {
      // A newly inflated menu must already be readable, without a walk of existing views.
      NavigationView menu = controller.get().navigationView;
      menu.inflateMenu(R.menu.lang_select);
      menu.getMenu().findItem(R.id.lang_sk).setCheckable(true).setChecked(true);
      menu.getMenu().findItem(R.id.lang_cz).setEnabled(false);
      menu.getMenu().addSubMenu("More settings").add("Nested option");
      assertBoundMenuTextBlack(menu);
      assertEquals(Color.BLACK, menu.getItemIconTintList().getColorForState(
          new int[]{android.R.attr.state_enabled, android.R.attr.state_checked}, Color.TRANSPARENT));
    }
  }

  @Test
  public void standardMenusRetainTheirLightTextOnDarkBackground() {
    try (ActivityController<DeviceSettings> controller = Robolectric.buildActivity(DeviceSettings.class).setup()) {
      NavigationView menu = controller.get().navigationView;
      assertNotEquals(Color.BLACK, menu.getItemTextColor().getDefaultColor());
      android.content.res.TypedArray colors = menu.getContext().obtainStyledAttributes(
          new int[]{android.R.attr.colorBackground});
      try {
        assertNotEquals(Color.WHITE, colors.getColor(0, Color.TRANSPARENT));
      } finally {
        colors.recycle();
      }
    }
  }

  @Test
  public void einkToolbarThemeUsesDarkForegroundsForNewViews() {
    BreviarApp.setEinkMode(context, true);
    try (ActivityController<DeviceSettings> controller = Robolectric.buildActivity(DeviceSettings.class).setup()) {
      Toolbar toolbar = controller.get().findViewById(R.id.settings_activity_toolbar);
      android.content.res.TypedArray colors = toolbar.getContext().obtainStyledAttributes(
          new int[]{android.R.attr.textColorPrimary, android.R.attr.textColorSecondary,
              androidx.appcompat.R.attr.colorControlNormal});
      try {
        for (int i = 0; i < colors.length(); ++i) assertEquals(Color.BLACK, colors.getColor(i, Color.TRANSPARENT));
      } finally {
        colors.recycle();
      }
    }
  }

  @Test
  @GraphicsMode(GraphicsMode.Mode.NATIVE)
  @SuppressWarnings({"rawtypes", "unchecked"})
  public void menuForegroundDoesNotPaintOverLabelsOrIcons() {
    BreviarApp.setEinkMode(context, true);
    try (ActivityController<LangSelect> controller = Robolectric.buildActivity(LangSelect.class).setup()) {
      RecyclerView list = recycler(controller.get().navigationView);
      RecyclerView.Adapter adapter = list.getAdapter();
      RecyclerView.ViewHolder holder = adapter.createViewHolder(list, adapter.getItemViewType(1));
      adapter.bindViewHolder(holder, 1);
      android.graphics.drawable.Drawable foreground = holder.itemView.getForeground();
      assertNotNull(foreground);
      foreground.setBounds(0, 0, 200, 100);
      for (int[] state : new int[][]{
          {android.R.attr.state_enabled},
          {android.R.attr.state_enabled, android.R.attr.state_pressed},
          {android.R.attr.state_enabled, android.R.attr.state_focused},
          {android.R.attr.state_enabled, android.R.attr.state_checked}}) {
        foreground.setState(state);
        android.graphics.Bitmap pixels = android.graphics.Bitmap.createBitmap(200, 100,
            android.graphics.Bitmap.Config.ARGB_8888);
        foreground.draw(new android.graphics.Canvas(pixels));
        assertEquals("Menu foreground must not cover its contents", 0,
            Color.alpha(pixels.getPixel(100, 50)));
        pixels.recycle();
      }
    }
  }
}

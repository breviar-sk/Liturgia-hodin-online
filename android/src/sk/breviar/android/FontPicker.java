package sk.breviar.android;

import java.lang.ref.WeakReference;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import android.content.Context;
import android.content.res.ColorStateList;
import android.graphics.Color;
import android.graphics.Typeface;
import android.graphics.drawable.GradientDrawable;
import android.view.MenuItem;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.TextView;

/** Asynchronous, lifecycle-bound font editor shared by XML settings screens. */
final class FontPicker {
  // Match the stock dark spinner palette, without inheriting reader firmware colors.
  private static final ColorStateList PREVIEW_TEXT = new ColorStateList(
      new int[][]{new int[]{-android.R.attr.state_enabled}, new int[]{}},
      new int[]{0x4dffffff, Color.WHITE});
  private static final ExecutorService fontWorker = Executors.newSingleThreadExecutor(
      task -> new Thread(task, "Breviar-fonts"));
  private final SettingsActivity activity;
  private final Runnable changed;
  private Future<?> fontLoad;
  private Spinner spinner;
  private int generation;

  FontPicker(SettingsActivity activity, Runnable changed) {
    this.activity = activity;
    this.changed = changed;
  }

  void bind(MenuItem item) {
    close();
    item.setActionView(R.layout.widget_spinner);
    spinner = (Spinner)item.getActionView();
    spinner.setContentDescription(item.getTitle());
    // Set the popup surface as well as row text: some readers supply a light
    // popup even when the app uses a dark theme. Keep Material's corner radius.
    GradientDrawable background = new GradientDrawable();
    background.setColor(BreviarApp.getEinkMode(activity) ? Color.WHITE : 0xff303030);
    background.setCornerRadius(2 * activity.getResources().getDisplayMetrics().density);
    spinner.setPopupBackgroundDrawable(background);
    showFonts(Collections.emptyList(), false);
    final int request = ++generation;
    Context context = activity.getApplicationContext();
    WeakReference<FontPicker> owner = new WeakReference<>(this);
    Handler ui = new Handler(Looper.getMainLooper());
    LoadTiming timing = new LoadTiming("Display fonts");
    fontLoad = fontWorker.submit(() -> {
      timing.mark("worker started");
      List<Fonts.Choice> choices;
      try {
        choices = Fonts.getChoices(context);
      } catch (RuntimeException error) {
        Log.e("breviar", "Loading fonts failed", error);
        choices = Collections.emptyList();
      }
      final List<Fonts.Choice> result = choices;
      timing.mark("posting to UI");
      ui.post(() -> {
        FontPicker picker = owner.get();
        if (picker == null || request != picker.generation || picker.activity.isFinishing()
            || picker.activity.isDestroyed()) return;
        picker.showFonts(result, true);
        timing.mark("displayed");
      });
    });
  }

  private void showFonts(List<Fonts.Choice> choices, boolean ready) {
    spinner.setSaveEnabled(false);
    spinner.setOnItemSelectedListener(null);
    String current = new UrlOptions(BreviarApp.getUrlOptions(activity)).getFont();
    FontSelectAdapter adapter = new FontSelectAdapter(activity, choices, current, changed);
    spinner.setAdapter(adapter);
    for (int i = 0; i < adapter.getCount(); ++i) {
      if (adapter.getItem(i).family_name.equals(current == null ? "" : current)) {
        spinner.setSelection(i);
        break;
      }
    }
    spinner.setEnabled(ready);
    if (ready) spinner.setOnItemSelectedListener(adapter);
  }

  void close() {
    ++generation;
    // Leave a shared cached discovery running, but cancel queued work/results.
    if (fontLoad != null) fontLoad.cancel(false);
    spinner = null;
  }

  static class FontInfo {
    public FontInfo(String name_, String family_name_, Typeface typeface_, String css_) {
      name = name_;
      family_name = family_name_;
      typeface = typeface_;
      css = css_;
    }

    final String name;
    final String family_name;
    final Typeface typeface;
    final String css;

    public String toString() {
      return name;
    }
  }

  static class FontSelectAdapter extends ArrayAdapter<FontInfo> implements AdapterView.OnItemSelectedListener {
    private final Runnable changed;

    public FontSelectAdapter(Context ctx, List<Fonts.Choice> choices, String current, Runnable changed) {
      super(ctx, android.R.layout.simple_spinner_item);
      this.changed = changed;
      setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
      add(new FontInfo(ctx.getString(R.string.default_font), "", null, ""));
      add(new FontInfo(ctx.getString(R.string.default_serif_font), "serif", Typeface.SERIF, ""));
      add(new FontInfo(ctx.getString(R.string.default_sans_serif_font), "sans-serif", Typeface.SANS_SERIF, ""));
      for (Fonts.Choice choice : choices) {
        add(new FontInfo(choice.family, choice.family, choice.typeface, choice.css));
      }
      // Missing/unreadable custom fonts must not silently reset saved preferences.
      if (current != null && !current.isEmpty()) {
        for (int i = 0; i < getCount(); ++i) {
          if (getItem(i).family_name.equals(current)) return;
        }
        add(new FontInfo(current, current, null, BreviarApp.getFontsCss(ctx)));
      }
    }

    void SetupView(int position, View view) {
      if (view == null) return;
      if (!(view instanceof TextView)) return;

      FontInfo fi = getItem(position);
      if (fi == null) return;
      TextView text = (TextView)view;
      text.setTypeface(fi.typeface == null ? Typeface.DEFAULT : fi.typeface);
      text.setTextColor(PREVIEW_TEXT);
      // Both the selected preview and dropdown rows use their parent's surface.
      // Clear any background inherited from framework row styles, also on reuse.
      text.setBackgroundTintList(null);
      text.setBackgroundColor(Color.TRANSPARENT);
      EinkUi.apply(view);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
      View res = super.getView(position, convertView, parent);
      SetupView(position, res);
      return res;
    }

    @Override
    public View getDropDownView(int position, View convertView, ViewGroup parent) {
      View res = super.getDropDownView(position, convertView, parent);
      SetupView(position, res);
      return res;
    }

    @Override
    public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
      FontInfo fi = getItem(position);
      if (fi == null) return;

      String current = new UrlOptions(BreviarApp.getUrlOptions(getContext())).getFont();
      if (fi.family_name.equals(current == null ? "" : current)) return;
      changed.run();
      BreviarApp.setFont(getContext().getApplicationContext(), fi.family_name, fi.css);
    }

    @Override
    public void onNothingSelected(AdapterView<?> parent) {
    }

  }

}

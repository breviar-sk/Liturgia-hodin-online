package sk.breviar.android;

import java.lang.Runnable;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import com.google.android.material.navigation.NavigationView;
import androidx.fragment.app.DialogFragment;
import androidx.core.view.MenuItemCompat;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.NumberPicker;
import android.widget.TextView;

public class SettingsActivity extends AppCompatActivity
                              implements NavigationView.OnNavigationItemSelectedListener {
  @Override
  protected void attachBaseContext(Context newBase) {
    super.attachBaseContext(newBase);
    BreviarApp.applyCustomLocale(this);
  }

  NavigationView navigationView;

  static class IntOptionInfo {
    IntOptionInfo(IntOption int_option_, int min_, int max_) {
      int_option = int_option_;
      min = min_;
      max = max_;
    }

    public IntOption int_option;
    public int min;
    public int max;
  };

  static class ColorOptionInfo {
    ColorOptionInfo(ColorOption color_option_, String[] predefined_colors_) {
      color_option = color_option_;
      predefined_colors = predefined_colors_;
    }

    public ColorOption color_option;
    String[] predefined_colors;
  };

  @Override
  public void onCreate(Bundle savedInstanceState) {
    switch_handlers = new java.util.LinkedHashMap<Integer, BooleanOption>();
    click_handlers = new java.util.LinkedHashMap<Integer, Runnable>();
    int_handlers = new java.util.LinkedHashMap<Integer, IntOptionInfo>();
    color_options = new java.util.LinkedHashMap<Integer, ColorOptionInfo>();
    super.onCreate(savedInstanceState);

    setContentView(R.layout.settings_activity);
    Toolbar toolbar = (Toolbar)findViewById(R.id.settings_activity_toolbar);
    setSupportActionBar(toolbar);
    getSupportActionBar().setDisplayHomeAsUpEnabled(true);

    navigationView = (NavigationView)findViewById(R.id.settings_activity_content);
    navigationView.setNavigationItemSelectedListener(this);
    navigationView.setItemMaxLines(2);
  }

  public void inflateMenu(int menu_resource) {
    navigationView.inflateMenu(menu_resource);
  }

  @Override
  public boolean onSupportNavigateUp() {
    finish(); // close this activity as oppose to navigating up
    return false;
  }

  public interface BooleanOption {
    abstract public void set(boolean value);
    abstract public boolean get();
  }

  public abstract class BooleanUrlOption implements BooleanOption {
    public void set(boolean value) {
      UrlOptions opts = initOpts();
      setOpt(opts, value);
      BreviarApp.setUrlOptions(getApplicationContext(), opts.build(true));
    }

    public boolean get() {
      return getOpt(initOpts());
    }

    private UrlOptions initOpts() {
      return new UrlOptions(BreviarApp.getUrlOptions(getApplicationContext()));
    }

    public abstract void setOpt(UrlOptions opts, boolean value);
    public abstract boolean getOpt(UrlOptions opts);
  }

  public interface ColorOption {
    abstract public void set(String value);
    abstract public String get();
  }

  public abstract class ColorUrlOption implements ColorOption {
    public void set(String value) {
      UrlOptions opts = initOpts();
      setOpt(opts, value);
      BreviarApp.setUrlOptions(getApplicationContext(), opts.build(true));
    }

    public String get() {
      return getOpt(initOpts());
    }

    private UrlOptions initOpts() {
      return new UrlOptions(BreviarApp.getUrlOptions(getApplicationContext()));
    }

    public abstract void setOpt(UrlOptions opts, String value);
    public abstract String getOpt(UrlOptions opts);
  }

  public interface IntOption {
    abstract public void set(int value);
    abstract public void reset();
    abstract public int get();
  }

  public abstract class IntUrlOption implements IntOption {
    public void set(int value) {
      UrlOptions opts = initOpts();
      setOpt(opts, value);
      BreviarApp.setUrlOptions(getApplicationContext(), opts.build(true));
    }

    public void reset() {
      UrlOptions opts = initOpts();
      resetOpt(opts);
      BreviarApp.setUrlOptions(getApplicationContext(), opts.build(true));
    }

    public int get() {
      return getOpt(initOpts());
    }

    private UrlOptions initOpts() {
      return new UrlOptions(BreviarApp.getUrlOptions(getApplicationContext()));
    }

    public abstract void setOpt(UrlOptions opts, int value);
    public abstract void resetOpt(UrlOptions opts);
    public abstract int getOpt(UrlOptions opts);
  }


  java.util.LinkedHashMap<Integer, BooleanOption> switch_handlers;
  java.util.LinkedHashMap<Integer, Runnable> click_handlers;
  java.util.LinkedHashMap<Integer, IntOptionInfo> int_handlers;
  java.util.LinkedHashMap<Integer, ColorOptionInfo> color_options;

  public void handleClick(int menu_resource, Runnable handler) {
    click_handlers.put(menu_resource, handler);
  }

  public void handleSwitch(int menu_resource, BooleanOption handler) {
    switch_handlers.put(menu_resource, handler);

    final BooleanOption final_handler = handler;
    try {
      ((CompoundButton)MenuItemCompat.getActionView(
          navigationView.getMenu().findItem(menu_resource)))
          .setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
                  @Override public void onCheckedChanged(CompoundButton button,
                                                         boolean isChecked) {
                    if (isChecked == final_handler.get()) {
                      return;
                    }
                    final_handler.set(isChecked);
                    updateMenu();
                  }
              });
    } catch (java.lang.NullPointerException e) {
      Log.v("breviar", "Cannot setup navigation view!");
    }
  }

  public void handleColor(int menu_resource, String[] predefined_colors, ColorOption handler) {
    color_options.put(menu_resource, new ColorOptionInfo(handler, predefined_colors));
  }


  public void handleInt(int menu_resource, int min, int max, IntOption handler) {
    int_handlers.put(menu_resource, new IntOptionInfo(handler, min, max));
  }

  @Override
  protected void onResume() {
    updateMenu();
    super.onResume();
  }


  public static class IntAlertDialogFragment extends DialogFragment {
    SettingsActivity ctx;
    IntOptionInfo info;
    NumberPicker picker = null;

    public IntAlertDialogFragment(SettingsActivity ctx_, IntOptionInfo info_) {
      ctx = ctx_;
      info = info_;
      /*
      int title
      Bundle args = new Bundle();
      args.putInt("title", title);
      setArguments(args);
      */
    }

    void Ok() {
      int newval = picker.getValue();
      if (newval < info.min) newval = info.min;
      if (newval > info.max) newval = info.max;
      if (newval != info.int_option.get()) {
        info.int_option.set(newval);
        ctx.updateMenu();
      }
    }

    void Cancel() {
      // nothing to do
    }

    void Default() {
      info.int_option.reset();
      ctx.updateMenu();
    }

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
      picker = new NumberPicker(ctx);
      picker.setMinValue(info.min);
      picker.setMaxValue(info.max);
      picker.setValue(info.int_option.get());

      return new AlertDialog.Builder(getActivity())
//              .setIcon(R.drawable.alert_dialog_icon)
//              .setTitle(title)
              .setPositiveButton(R.string.int_dialog_ok,
                      (dialogInterface, i) -> Ok())
              .setNegativeButton(R.string.int_dialog_cancel,
                      (dialogInterface, i) -> Cancel())
              .setNeutralButton(R.string.int_dialog_default,
                      (dialogInterface, i) -> Default())
              .setView(picker)
              .create();
    }
  }

  public static class ColorDialogFragment extends DialogFragment {
    SettingsActivity ctx;
    ColorOptionInfo info;

    public ColorDialogFragment(SettingsActivity ctx_, ColorOptionInfo info_) {
      ctx = ctx_;
      info = info_;
    }

    void Ok() {
      Dialog d = getDialog();
      String v = ((EditText)(d.findViewById(R.id.color_picker_edittext))).getText().toString();
      info.color_option.set(v);
      ctx.updateMenu();
    }

    void Cancel() {
      // nothing to do
    }

    void Default() {
      info.color_option.set("");
      ctx.updateMenu();
    }

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
      Dialog d = new AlertDialog.Builder(getActivity())
//              .setIcon(R.drawable.alert_dialog_icon)
//              .setTitle(title)
              .setPositiveButton(R.string.color_dialog_ok,
                      (dialogInterface, i) -> Ok())
              .setNegativeButton(R.string.color_dialog_cancel,
                      (dialogInterface, i) -> Cancel())
              .setNeutralButton(R.string.color_dialog_default,
                      (dialogInterface, i) -> Default())
              .setView(R.layout.dialog_color_picker)
              .create();
      d.create();
      final EditText input = (EditText)(d.findViewById(R.id.color_picker_edittext));
      input.setText(info.color_option.get());

      LinearLayout root = (LinearLayout)(d.findViewById(R.id.color_picker_root));
      for (int i = 0; i < info.predefined_colors.length; ++i) {
        final String textc = info.predefined_colors[i];
        int c = Color.parseColor("#" + textc);
        Button v = new Button(ctx);
        // v.setText(textc);
        // v.setTextColor(Color.BLACK);
        v.setWidth(ViewGroup.LayoutParams.MATCH_PARENT);
        v.setHeight(ViewGroup.LayoutParams.WRAP_CONTENT);
        v.setBackgroundColor(c);
        v.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
              input.setText(textc);
            }
        });

        root.addView(v);
        Log.v("breviar", "Added predefined color " + info.predefined_colors[i]);
      }
      return d;
    }

  }

  @Override
  public boolean onNavigationItemSelected(MenuItem item) {
    {
      BooleanOption handler = switch_handlers.get(item.getItemId());
      if (handler != null) {
        handler.set(!handler.get());
        updateMenu();
      }
    }
    {
      Runnable handler = click_handlers.get(item.getItemId());
      if (handler != null) {
        handler.run();
      }
    }
    {
      IntOptionInfo info = int_handlers.get(item.getItemId());
      if (info != null) {
        DialogFragment dialog = new IntAlertDialogFragment(this, info);
        dialog.show(getSupportFragmentManager(), "dialog");
      }
    }
    {
      ColorOptionInfo info = color_options.get(item.getItemId());
      if (info != null) {
        DialogFragment dialog = new ColorDialogFragment(this, info);
        dialog.show(getSupportFragmentManager(), "dialog");
      }
    }
    return true;
  }

  public void updateMenu() {
    try {
      Menu menu = navigationView.getMenu();
      for (java.util.Map.Entry<Integer, BooleanOption> entry :
           switch_handlers.entrySet()) {
        boolean value = entry.getValue().get();
        CompoundButton button = (CompoundButton)MenuItemCompat.getActionView(
            menu.findItem(entry.getKey().intValue()));
        if (button.isChecked() != value) {
          button.setChecked(value);
        }
      }
      for (java.util.Map.Entry<Integer, IntOptionInfo> entry :
           int_handlers.entrySet()) {
        int value = entry.getValue().int_option.get();
        TextView view = (TextView)MenuItemCompat.getActionView(
            menu.findItem(entry.getKey().intValue())).findViewById(R.id.int_widget_textview);
        view.setText(Integer.toString(value));
      }
      for (java.util.Map.Entry<Integer, ColorOptionInfo> entry :
           color_options.entrySet()) {
        ColorOptionInfo info = entry.getValue();
        String value = info.color_option.get();
        TextView view = (TextView)MenuItemCompat.getActionView(
            menu.findItem(entry.getKey().intValue())).findViewById(R.id.color_widget_textview);
        Log.v("breviar", "Color '" + value + "' for " + entry.getKey());
        if (value.isEmpty()) {
          view.setText(getString(R.string.default_color));
          view.setBackgroundColor(Color.TRANSPARENT);
        } else {
          view.setText("    ");
          view.setBackgroundColor(Color.parseColor("#" + value));
        }
      }
    } catch (java.lang.NullPointerException e) {
      Log.v("breviar", "Cannot update menu!");
    }
  }
}

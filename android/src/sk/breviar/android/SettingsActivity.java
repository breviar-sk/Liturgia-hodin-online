package sk.breviar.android;

import java.lang.Runnable;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import android.support.design.widget.NavigationView;
import android.support.v4.app.DialogFragment;
import android.support.v4.view.MenuItemCompat;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.CompoundButton;
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
  
  @Override
  public void onCreate(Bundle savedInstanceState) {
    switch_handlers = new java.util.LinkedHashMap<Integer, BooleanOption>();
    click_handlers = new java.util.LinkedHashMap<Integer, Runnable>();
    int_handlers = new java.util.LinkedHashMap<Integer, IntOptionInfo>();
    super.onCreate(savedInstanceState);

    setContentView(R.layout.settings_activity);
    Toolbar toolbar = (Toolbar)findViewById(R.id.settings_activity_toolbar);
    setSupportActionBar(toolbar);
    getSupportActionBar().setDisplayHomeAsUpEnabled(true);

    navigationView = (NavigationView)findViewById(R.id.settings_activity_content);
    navigationView.setNavigationItemSelectedListener(this);
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
        final TextView view =
            (TextView)MenuItemCompat.getActionView(item).findViewById(R.id.int_widget_textview);

        DialogFragment dialog = new IntAlertDialogFragment(this, info);
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
    } catch (java.lang.NullPointerException e) {
      Log.v("breviar", "Cannot update menu!");
    }
  }
}

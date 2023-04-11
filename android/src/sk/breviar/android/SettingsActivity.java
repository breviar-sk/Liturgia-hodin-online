package sk.breviar.android;

import java.lang.Runnable;

import android.content.Context;
import android.os.Bundle;
import android.support.design.widget.NavigationView;
import android.support.v4.view.MenuItemCompat;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.CompoundButton;
import android.widget.NumberPicker;

public class SettingsActivity extends AppCompatActivity
                              implements NavigationView.OnNavigationItemSelectedListener {
  @Override
  protected void attachBaseContext(Context newBase) {
    super.attachBaseContext(newBase);
    BreviarApp.applyCustomLocale(this);
  }

  NavigationView navigationView;
  
  @Override
  public void onCreate(Bundle savedInstanceState) {
    switch_handlers = new java.util.LinkedHashMap<Integer, BooleanOption>();
    click_handlers = new java.util.LinkedHashMap<Integer, Runnable>();
    int_handlers = new java.util.LinkedHashMap<Integer, IntOption>();
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
    abstract public int get();
  }

  public abstract class IntUrlOption implements IntOption {
    public void set(int value) {
      UrlOptions opts = initOpts();
      setOpt(opts, value);
      BreviarApp.setUrlOptions(getApplicationContext(), opts.build(true));
    }

    public int get() {
      return getOpt(initOpts());
    }

    private UrlOptions initOpts() {
      return new UrlOptions(BreviarApp.getUrlOptions(getApplicationContext()));
    }

    public abstract void setOpt(UrlOptions opts, int value);
    public abstract int getOpt(UrlOptions opts);
  }


  java.util.LinkedHashMap<Integer, BooleanOption> switch_handlers;
  java.util.LinkedHashMap<Integer, Runnable> click_handlers;
  java.util.LinkedHashMap<Integer, IntOption> int_handlers;

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
    int_handlers.put(menu_resource, handler);

    final IntOption final_handler = handler;
    final int minVal = min;
    final int maxVal = max;
    try {
      NumberPicker picker = (NumberPicker)MenuItemCompat.getActionView(
          navigationView.getMenu().findItem(menu_resource));
      picker.setMinValue(min);
      picker.setMaxValue(max);

      picker.setOnValueChangedListener(new NumberPicker.OnValueChangeListener() {
                  @Override public void onValueChange(NumberPicker picker,
                                                      int oldVal, int newVal) {
                    int curVal = final_handler.get();
                    if (newVal == curVal) {
                      return;
                    }
                    if (newVal < minVal) {
                      newVal = minVal;
                    }
                    if (newVal > maxVal) {
                      newVal = maxVal;
                    }
                    final_handler.set(newVal);
                    updateMenu();
                  }
              });
    } catch (java.lang.NullPointerException e) {
      Log.v("breviar", "Cannot setup navigation view!");
    }
  }

  @Override
  protected void onResume() {
    updateMenu();
    super.onResume();
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
    return true;
  }

  void updateMenu() {
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
      for (java.util.Map.Entry<Integer, IntOption> entry :
           int_handlers.entrySet()) {
        int value = entry.getValue().get();
        NumberPicker picker = (NumberPicker)MenuItemCompat.getActionView(
            menu.findItem(entry.getKey().intValue()));
        if (picker.getValue() != value) {
          picker.setValue(value);
        }
      }
    } catch (java.lang.NullPointerException e) {
      Log.v("breviar", "Cannot update menu!");
    }
  }
}

package sk.breviar.android;

/** Retains the activity entry point while its contents come from Menu v1. */
public class DeviceSettings extends XmlSettingsActivity {
  @Override protected String initialKey() { return "device"; }
}

package sk.breviar.android;

public class CompatibilityHelper8 {
  static public String Base64EncodeToString(byte[] what) {
    return android.util.Base64.encodeToString(
        what, android.util.Base64.DEFAULT);
  }
}

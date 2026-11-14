package sk.breviar.android;

import static org.junit.Assert.*;
import android.net.Uri;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.annotation.Config;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = 24)
public class PrayerLinkTest {
  @Test public void datedPrayerAndResolvedSettingsReplaceStaleForces() {
    String url = PrayerLink.share("http://127.0.0.1:50000/l.cgi?qt=pdt&d=12&m=11&r=2026&p=mv&of1r=0&o1=7",
        "&amp;j=la&amp;o0=1048575&amp;o1=123&amp;o2=131071&amp;o3=6&amp;o6=11000000000"
        + "&amp;f=CustomFont&amp;ff=18&amp;c=1&amp;tc0=ffffff&amp;dl=hu", "sk");
    UrlOptions query = PrayerLink.read(Uri.parse(url));
    assertNotNull(query);
    assertTrue(url.startsWith("https://breviar.sk/cgi-bin/l.cgi?"));
    assertEquals("pdt", query.params.get("qt"));
    assertEquals("mv", query.params.get("p"));
    assertEquals("12", query.params.get("d"));
    assertFalse(query.params.containsKey("of1r"));
    assertEquals("123", query.params.get("o1"));
    assertEquals("11000000000", query.params.get("o6"));
    assertEquals("la", query.params.get("j"));
    assertEquals("", query.params.get("k"));
    for (String local : new String[]{"f", "ff", "c", "tc0", "dl"}) assertFalse(query.params.containsKey(local));
    assertEquals(0, query.getInt("o0") & (64 | 128 | 256 | 1024 | 262144 | 524288));
    assertEquals(0, query.getInt("o2") & (4 | 8 | 16 | 32 | 128 | 256 | 65536));
  }

  @Test public void dailyOverviewRemainsRelativeAndSeasonalYearSurvivesSharing() {
    String overview = PrayerLink.share("http://127.0.0.1/l.cgi?qt=pdnes", "&amp;j=sk&amp;o1=7", "sk");
    UrlOptions query = PrayerLink.read(Uri.parse(overview));
    assertEquals("pdnes", query.params.get("qt"));
    assertFalse(query.params.containsKey("d"));
    assertFalse(query.params.containsKey("p"));
    String seasonal = PrayerLink.share("http://127.0.0.1/l.cgi?qt=plo&lo=3&t=1&dvt=1&lr=C&r=2026&p=mrch",
        "&amp;j=sk", "sk");
    assertEquals("2026", PrayerLink.read(Uri.parse(seasonal)).params.get("r"));
  }

  @Test public void datedAndCommonsSelectionsSurviveAndLocalSettingsAreRetained() {
    String page = "http://127.0.0.1/l.cgi?qt=plo&lo=5&t=28&dvt=3&lr=C&p=mpc&ds=1";
    String url = PrayerLink.share(page, "&amp;j=la&amp;k=op&amp;o0=1&amp;o1=2&amp;o2=0&amp;o3=6", "sk");
    UrlOptions link = PrayerLink.read(Uri.parse(url));
    for (String key : new String[]{"qt", "lo", "t", "dvt", "lr", "p", "ds"}) {
      assertEquals(new UrlOptions(page, true).params.get(key), link.params.get(key));
    }
    UrlOptions applied = new UrlOptions(PrayerLink.applySettings(
        "&amp;qt=pdnes&amp;p=mi&amp;r=2025&amp;j=sk&amp;k=sj&amp;o0=1088&amp;o2=288&amp;f=Custom&amp;c=1", link.build(true)));
    assertEquals(1089, applied.getInt("o0"));
    assertEquals(288, applied.getInt("o2"));
    assertEquals("Custom", applied.getFont());
    assertTrue(applied.isNightmode());
    assertEquals("la", applied.params.get("j"));
    assertEquals("op", applied.params.get("k"));
    assertFalse(applied.params.containsKey("qt"));
    assertFalse(applied.params.containsKey("p"));
    assertFalse(applied.params.containsKey("r"));
    String dated = PrayerLink.share("http://127.0.0.1/l.cgi?qt=pdt&d=13&m=11&r=2026&p=mv", "", "sk");
    assertEquals("13", PrayerLink.read(Uri.parse(dated)).params.get("d"));
  }

  @Test public void untrustedMalformedOrNonReaderLinksAreRejected() {
    for (String link : new String[]{"https://evil.example/cgi-bin/l.cgi?qt=pdnes",
        "https://breviar.sk.evil.example/cgi-bin/l.cgi?qt=pdnes",
        "https://user@breviar.sk/cgi-bin/l.cgi?qt=pdnes",
        "https://breviar.sk:123/cgi-bin/l.cgi?qt=pdnes", "file:///cgi-bin/l.cgi?qt=pdnes",
        "https://breviar.sk/other?qt=pdnes", "https://breviar.sk/cgi-bin/l.cgi?qt=pxml",
        "https://breviar.sk/cgi-bin/l.cgi?qt=pst&st=i&p=0",
        "https://breviar.sk/cgi-bin/l.cgi?qt=pdnes&j=sk&j=la",
        "https://breviar.sk/cgi-bin/l.cgi?qt=pdnes&o1=-1",
        "https://breviar.sk/cgi-bin/l.cgi?qt=pdnes&o1=18446744073709551616",
        "https://breviar.sk/cgi-bin/l.cgi?qt=pdnes&p=%0A"}) {
      assertNull(link, PrayerLink.read(Uri.parse(link)));
    }
    assertNotNull(PrayerLink.read(Uri.parse("https://breviar.sk/cgi-bin/l.cgi?qt=pst&st=2&p=mr")));
  }
}

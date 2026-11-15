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
  @Test public void shareOrdersIdentityFirstWithoutInventingMissingParameters() {
    assertTrue(PrayerLink.share("http://127.0.0.1/l.cgi?p=mv&r=2026&m=11&d=13&qt=pdt",
        "j=cz&o1=7", "sk").startsWith(
        "https://breviar.sk/cgi-bin/l.cgi?qt=pdt&d=13&m=11&r=2026&j=cz&"));
    String today = PrayerLink.share("http://127.0.0.1/l.cgi?qt=pdnes", "j=sk", "sk");
    assertEquals("https://breviar.sk/cgi-bin/l.cgi?qt=pdnes&j=sk&k=&sh=1", today);
    assertTrue(PrayerLink.share("http://127.0.0.1/l.cgi?qt=plo&lo=3&r=2026&p=mrch",
        "j=la", "sk").startsWith("https://breviar.sk/cgi-bin/l.cgi?qt=plo&r=2026&j=la&"));
  }

  @Test public void sharingEmitsTheCurrentVersionAndStillAcceptsUnmarkedLinks() {
    String page = "https://breviar.sk/cgi-bin/l.cgi?qt=pdt&d=13&m=11&r=2026&p=mv&j=sk";
    String shared = PrayerLink.share(page + "&sh=99", "sh=2", "sk");
    assertEquals("1", Uri.parse(shared).getQueryParameter("sh"));
    assertEquals(1, Uri.parse(shared).getQueryParameters("sh").size());
    assertNotNull(PrayerLink.read(Uri.parse(page)));
    UrlOptions accepted = PrayerLink.read(Uri.parse(shared));
    assertNotNull(accepted);
    assertFalse(accepted.params.containsKey("sh")); // Metadata must not become saved settings.
  }

  @Test public void datedPrayerAndResolvedSettingsReplaceStaleForces() {
    String url = PrayerLink.share("http://127.0.0.1:50000/l.cgi?qt=pdt&d=12&m=11&r=2026&p=mv&of1r=0&o1=7",
        "&amp;j=la&amp;o0=1048575&amp;o1=123&amp;o2=131071&amp;o3=6&amp;o6=11000000000"
        + "&amp;f=CustomFont&amp;ff=18&amp;c=1&amp;ct0=ffffff&amp;dl=hu", "sk");
    UrlOptions query = PrayerLink.read(Uri.parse(url), true);
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
    assertEquals("CustomFont", query.getFont());
    assertEquals("18", query.params.get("ff"));
    assertEquals("1", query.params.get("c"));
    assertEquals("ffffff", query.params.get("ct0"));
    assertFalse(query.params.containsKey("dl"));
    assertEquals("1048575", query.params.get("o0"));
    assertEquals("131071", query.params.get("o2"));
  }

  @Test public void recipientPolicyFiltersBeforeValidatingAndAllModeKeepsVisualFlags() {
    String url = PrayerLink.share("http://127.0.0.1/l.cgi?qt=pdt&d=13&m=11&r=2026&p=mv",
        "&amp;j=sk&amp;o0=65&amp;o2=256&amp;c=1&amp;cr1=ffffcc&amp;ff=18&amp;f=Noto Serif", "sk");
    UrlOptions full = PrayerLink.read(Uri.parse(url), true);
    assertNotNull(full);
    assertEquals("Noto Serif", full.getFont());
    assertEquals("ffffcc", full.params.get("cr1"));
    assertTrue(full.isOnlyNonBoldFont());
    assertTrue(full.isNightmode());
    UrlOptions content = PrayerLink.read(Uri.parse(url));
    assertNotNull(content);
    assertNull(content.getFont());
    assertNull(content.params.get("cr1"));
    UrlOptions mine = new UrlOptions("c=0&o0=0&o2=0&f=Mine&mm=20");
    UrlOptions applied = new UrlOptions(PrayerLink.applySettings(mine.build(true), content.build(true)));
    assertFalse(applied.isOnlyNonBoldFont());
    assertFalse(applied.isNightmode());
    assertEquals("Mine", applied.getFont());
    applied = new UrlOptions(PrayerLink.applySettings(mine.build(true), full.build(true), true));
    assertTrue(applied.isOnlyNonBoldFont());
    assertTrue(applied.isNightmode());
    assertEquals("Noto Serif", applied.getFont());
    assertEquals("20", applied.params.get("mm")); // Missing settings retain current values.
    assertEquals("ffffcc", applied.params.get("cr1"));
    assertNotNull(PrayerLink.read(Uri.parse(url + "&ct1=not-a-color&of0fn=bad")));
    assertNull(PrayerLink.read(Uri.parse(url + "&ct1=not-a-color&of0fn=bad"), true));
    assertNotNull(PrayerLink.read(Uri.parse(url + "&f=ignored-duplicate")));
    assertNull(PrayerLink.read(Uri.parse(url + "&f=duplicate"), true));
  }

  @Test public void fullLinksRetainAllVisualParametersButNeverDevicePreferences() {
    String url = PrayerLink.share("http://127.0.0.1/l.cgi?qt=pdnes",
        "c=0&ct0=123456&cr0=abcdef&c0=ffffff&ct1=eeeeee&cr1=ffffcc&c1=000000"
        + "&f=Test Font&ff=20&s=large&mm=15&lh=140&v=1&of0fn=1&of2nr=1"
        + "&eink_mode=true&scale=150&appVersion=123&dl=hu", "sk");
    UrlOptions link = PrayerLink.read(Uri.parse(url), true);
    assertNotNull(link);
    for (String key : new String[]{"c", "ct0", "cr0", "c0", "ct1", "cr1", "c1", "f", "ff", "s", "mm", "lh", "v", "of0fn", "of2nr"}) {
      assertTrue(key, link.params.containsKey(key));
    }
    for (String key : new String[]{"eink_mode", "scale", "appVersion", "dl"}) assertFalse(link.params.containsKey(key));
    assertFalse(PrayerLink.read(Uri.parse(url)).params.containsKey("of0fn"));
    for (String value : new String[]{"ct0=not-a-color", "f=%3Cscript%3E", "ff=999999999", "c=2", "v=other"}) {
      assertNull(value, PrayerLink.read(Uri.parse("https://breviar.sk/cgi-bin/l.cgi?qt=pdnes&" + value), true));
    }
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

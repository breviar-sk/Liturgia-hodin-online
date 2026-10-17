package sk.breviar.android;

import static org.junit.Assert.*;

import android.content.Context;
import android.content.ContextWrapper;
import android.graphics.Typeface;
import android.os.Looper;
import java.io.File;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import org.junit.After;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;
import org.junit.runner.RunWith;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.annotation.Config;
import org.robolectric.annotation.Implementation;
import org.robolectric.annotation.Implements;
import org.robolectric.shadows.ShadowLegacyTypeface;

@RunWith(RobolectricTestRunner.class)
@Config(sdk = 24, shadows = FontsTest.Previews.class)
public class FontsTest {
  @Rule public TemporaryFolder temporary = new TemporaryFolder();
  private final ExecutorService worker = Executors.newSingleThreadExecutor();

  @Implements(Typeface.class)
  public static class Previews extends ShadowLegacyTypeface {
    static int loads;

    @Implementation protected static Typeface createFromFile(String filename) {
      assertNotSame(Looper.getMainLooper().getThread(), Thread.currentThread());
      ++loads;
      if (filename.contains("Broken")) throw new RuntimeException("Invalid font");
      return Typeface.SERIF;
    }
  }

  @After public void stopWorker() throws Exception {
    worker.shutdown();
    assertTrue(worker.awaitTermination(10, TimeUnit.SECONDS));
  }

  private Context storage(File root) {
    return new ContextWrapper(RuntimeEnvironment.getApplication()) {
      @Override public File getExternalFilesDir(String type) { return root; }
    };
  }

  private List<Fonts.Choice> load(Context context) throws Exception {
    return worker.submit(() -> Fonts.getChoices(context)).get(10, TimeUnit.SECONDS);
  }

  @Test public void previewsAreCachedUntilCustomFontsAreAddedChangedOrRemoved() throws Exception {
    File root = temporary.newFolder();
    Context context = storage(root);
    File custom = new File(root, "Custom-Regular.ttf");
    Files.write(custom.toPath(), "first font".getBytes(StandardCharsets.UTF_8));
    List<Fonts.Choice> first = load(context);
    assertEquals(1, first.size());
    assertEquals("Custom", first.get(0).family);
    assertTrue(first.get(0).css.contains("/file" + custom.getAbsolutePath()));
    int previews = Previews.loads;
    assertSame(first, load(context));
    assertEquals("Cache hits must not reopen font files", previews, Previews.loads);

    Files.write(custom.toPath(), "replacement font with different size".getBytes(StandardCharsets.UTF_8));
    List<Fonts.Choice> changed = load(context);
    assertNotSame(first, changed);
    assertEquals(previews + 1, Previews.loads);

    File other = new File(root, "Other-Italic.ttf");
    Files.write(other.toPath(), new byte[]{1});
    List<Fonts.Choice> added = load(context);
    assertEquals(2, added.size());
    assertTrue(added.get(1).css.contains("font-style: italic"));
    Files.delete(custom.toPath());
    List<Fonts.Choice> removed = load(context);
    assertEquals(1, removed.size());
    assertEquals("Other", removed.get(0).family);
  }

  @Test public void malformedFontDoesNotHideOtherFontsAndMissingStorageIsAllowed() throws Exception {
    assertTrue(load(storage(null)).isEmpty());
    File root = temporary.newFolder();
    Files.write(new File(root, "Broken.ttf").toPath(), new byte[]{1});
    Files.write(new File(root, "Good.ttf").toPath(), new byte[]{1});
    List<Fonts.Choice> choices = load(storage(root));
    assertEquals(1, choices.size());
    assertEquals("Good", choices.get(0).family);
  }
}

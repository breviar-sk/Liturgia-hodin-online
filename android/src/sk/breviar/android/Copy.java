package sk.breviar.android;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.Thread;
import android.content.Context;
import android.util.Log;
import java.lang.IndexOutOfBoundsException;

import java.util.Random;

public class Copy extends Thread
{
    InputStream in;
    OutputStream out;
    int inst;
    

    public Copy(InputStream _in, OutputStream _out) {
      in = _in;
      out = _out;
      inst = new Random().nextInt();
    }

    static int maxLen = 32*1024;
    public void run() {
      byte[] buf;
      int len;

      buf = new byte[maxLen];

      try {
        while (true) {
          // Log.v("breviar: Copy: " + inst, "reading");
          len = in.read(buf, 0, maxLen);
          if (len==-1) break;
          // Log.v("breviar: Copy:" + inst, "writing " + len + " bytes: " + new String(buf, 0, len, "ISO-8859-1"));
          out.write(buf, 0, len);
        }
      } catch (IOException e) {
        Log.v("Breviar: Copy:", "IOException "+e.getMessage());
      } catch (IndexOutOfBoundsException e) {
        Log.v("Breviar: Copy:", "IndexOutOfBoundsException "+e.getMessage());
      }

      // Log.v("breviar: Copy: " + inst, "finished");
      try { in.close(); } catch (IOException e) { Log.v("Breviar: Copy:", "IOException "+e.getMessage()); }
      try { out.close(); } catch (IOException e) { Log.v("Breviar: Copy:", "IOException "+e.getMessage()); }
    }

}

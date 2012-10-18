package sk.breviar.android;

import java.net.Socket;
import java.net.ServerSocket;
import java.io.*;
import java.lang.Thread;
import android.content.Context;
import android.content.res.*;
import android.util.Log;
import sk.breviar.android.Copy;
import sk.breviar.android.FdInputStream;
import sk.breviar.android.FdOutputStream;
import java.lang.InterruptedException;

public class Server extends Thread
{
    public int port;
    ServerSocket listener;
    Context ctx;
    boolean running;
    static String scriptname;
    String language;
    String persistentOpts;

    public Server(Context _ctx, String sn, String lang, String opts) throws IOException {
      int i;
      boolean ok = true;
      Log.v("breviar", "Server: constructor");
      scriptname = sn;
      language = lang;
      persistentOpts = opts;
      ctx = _ctx;
      for (i=50000; i>20000; i--) {
        ok = true;
        try {
          listener = new ServerSocket(i, 50, java.net.Inet4Address.getLocalHost());
        } catch (IOException e) {
          ok = false;
        }
        if (ok) break;
      }
      if (!ok) throw new IOException();
      port = i;
      Log.v("breviar", "Server: socket opened at port " + port);
      running = true;
      // setDaemon(true);
    }

    public synchronized void setLanguage(String lang) {
      language = lang;
    }

    public synchronized void setOpts(String s) {
      persistentOpts = s;
    }

    public synchronized String getOpts() {
      return persistentOpts;
    }

    public void run() {
      Log.v("breviar", "Server: run started");
      while (running) {
        try {
          Socket client = listener.accept();
          Log.v("breviar", "Server: handling connection");
          handle(client);
          client.close();
        } catch (IOException e) {
          Log.v("Breviar: Server:", "run failed: " + e.getMessage());
        }
      }
      Log.v("breviar", "Server: run finished");
    }

    public void stopServer() {
      boolean intr;

      running = false;
      try {
        listener.close();
        do {
          intr = false;
          try { this.join(); } catch (java.lang.InterruptedException e) { intr = true; }
        } while (intr);
      } catch (IOException e) {
        Log.v("Breviar: Server:", "stopServer failed: " + e.getMessage());
      }
    }

    native String main(FileDescriptor outfd, FileDescriptor infd, String environ);
    native FileDescriptor[] createPipe();

    int checkfile(String fn) {
      int ret;
      fn = fn.replace("/_", "/x");
      try {
        InputStream tst = ctx.getAssets().open(fn);
        tst.close();
        ret = 1;
      } catch (IOException e) {
        ret = 0;
      }
      return ret;
    }

    void reader(String fn, FileDescriptor fd) {
      //Log.v("Breviar: Server:", "reader(" + fn + ") called");
      fn = fn.replace("/_", "/x");
      try {
        new Copy( ctx.getAssets().open(fn), new FdOutputStream(fd) ).start();
      } catch (IOException e) {
        // Log.v("Breviar: Server:", "reader(" + fn + ") failed: " + e.getMessage());
        try {
          new FdOutputStream(fd).close();
        } catch (IOException e2) {
          Log.v("Breviar: Server:", "dummy reader failed");
        }
      }
    }

    synchronized void handle(Socket client) throws IOException {
      String dokument = "unknown";
      BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
      byte[] buf;

      boolean postmethod = false;
      int cntlen=0;
      while (true) {
        String s = in.readLine();
        if (s == null) break;
        s = s.trim();
        // Log.v("breviar", s);

        if (s.equals("")) break;

        if (s.startsWith("GET")) {
          int leerstelle = s.indexOf(" HTTP/");
          dokument = s.substring(5,leerstelle);
          dokument = dokument.replaceAll("[/]+","/");
        } else if (s.startsWith("POST")) {
          int leerstelle = s.indexOf(" HTTP/");
          dokument = s.substring(6,leerstelle);
          dokument = dokument.replaceAll("[/]+","/");
          postmethod = true;
        } else if (s.startsWith("Content-Length")) {
          cntlen = Integer.parseInt(s.substring(16));
        }
      }
      if (postmethod) {
        char[] buf2 = new char[cntlen];
        in.read(buf2, 0, cntlen);
        buf = new String(buf2).getBytes();
      } else {
        cntlen = 0;
        buf = new byte[0];
      }
      Log.v("breviar", "handle connection: document = " + dokument);

      if (dokument.length() >=scriptname.length() && 
          dokument.substring(0,scriptname.length()).equals(scriptname)) {
        // Log.v("breviar", "handling cgi request");
        client.getOutputStream().write(
            (
            "HTTP/1.1 200 OK\n" +
            "Server: Breviar\n" +
            "Connection: close\n"
            ).getBytes("UTF-8")
        );
        client.getOutputStream().flush();
        FileDescriptor[] pipe = createPipe();
        Copy cp = new Copy( new FdInputStream(pipe[0]), client.getOutputStream() );
        cp.start();
        String qs = dokument.substring(scriptname.length()+1);
        FileDescriptor[] pipein = createPipe();
        Copy cpin = new Copy( new ByteArrayInputStream(buf, 0, cntlen), new FdOutputStream(pipein[1]) );
        cpin.start();
        if (!postmethod) {
          persistentOpts = main(pipe[1], pipein[0], "REQUEST_METHOD=GET\001QUERY_STRING=" + qs + "\001WWW_j=" + language + "\001");
        } else {
          persistentOpts = main(pipe[1], pipein[0], "REQUEST_METHOD=POST\001CONTENT_TYPE=application/x-www-form-urlencoded\001CONTENT_LENGTH=" +
              cntlen + "\001QUERY_STRING=" + qs + "\001WWW_j=" + language + "\001");
        }
        boolean ok;
        do {
          try {
            ok = true;
            cp.join();
          } catch (InterruptedException e) {
            ok = false;
          }
        } while (!ok);
      } else {
        try {
          InputStream infile = ctx.getAssets().open(dokument, AssetManager.ACCESS_STREAMING);
          client.getOutputStream().write(
              (
              "HTTP/1.1 200 OK\n" +
              "Server: Breviar\n" +
              "Connection: close\n\n"
              ).getBytes("UTF-8")
          );
          // do not start new thread, just copy here.
          new Copy( infile, client.getOutputStream() ).run();
        } catch (IOException e) {
          // Log.v("breviar", "file not found: " + dokument);
          client.getOutputStream().write(
              (
              "HTTP/1.1 404 - File Not Found\n" +
              "Server: Breviar\n" +
              "Connection: close\n"
              ).getBytes("UTF-8")
          );
          client.getOutputStream().close();
        }
      }
    }

    static {
        System.loadLibrary("breviar");
    }

}

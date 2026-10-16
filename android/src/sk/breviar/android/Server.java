package sk.breviar.android;

import java.io.*;
import java.lang.InterruptedException;
import java.lang.Thread;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Set;

import android.content.Context;
import android.content.res.*;
import android.util.Log;

import sk.breviar.android.Copy;
import sk.breviar.android.FdInputStream;
import sk.breviar.android.FdOutputStream;

public class Server extends Thread {
    // The JNI bridge and renderer use process-global request state.
    private static final Object NATIVE_LOCK = new Object();
    // UI settings updates must never wait for rendering, socket writes or Copy.join().
    private final Object settingsLock = new Object();
    private long settingsRevision;

    private Server(Context context) {
      ctx = context.getApplicationContext();
    }

    private String render(FileDescriptor out, FileDescriptor in, String environment) {
      synchronized (NATIVE_LOCK) {
        return main(out, in, environment);
      }
    }

    /** Render the iOS settings export without sockets or changes to reader options.
     * Call on a worker thread; HTTP requests use the same native lock.
     */
    public static String getSettingsXml(Context context, String options, String language)
        throws IOException, InterruptedException {
      Server renderer = new Server(context);
      UrlOptions query = new UrlOptions(options);
      for (String key : new String[]{"d", "m", "r", "p", "ds"}) query.params.remove(key);
      query.params.put("qt", "pxml");
      query.params.put("j", language);
      FileDescriptor[] output = renderer.createPipe();
      FileDescriptor[] input = renderer.createPipe();
      new FdOutputStream(input[1]).close();
      ByteArrayOutputStream bytes = new ByteArrayOutputStream();
      Copy copy = new Copy(new FdInputStream(output[0]), bytes);
      copy.start(); // Drain concurrently: exports can exceed pipe capacity.
      renderer.render(output[1], input[0], "REQUEST_METHOD=GET\001QUERY_STRING=" +
          query.getBuilder().build().getEncodedQuery() + "\001WWW_j=" + language + "\001");
      copy.join();
      String response = bytes.toString("UTF-8");
      int start = response.indexOf("<?xml");
      if (start < 0) throw new IOException("Missing settings XML");
      return response.substring(start);
    }

    public int port;
    public int port_nonpersistent;
    ServerSocketChannel listener;
    ServerSocketChannel listener_nonpersistent;
    Context ctx;
    boolean running;
    static String scriptname;
    private String language;
    private String persistentOpts;

    public Server(Context _ctx, String sn, String lang, String opts) throws IOException {
      int i;
      boolean ok = false;
      Log.v("breviar", "Server: constructor");
      scriptname = sn;
      language = lang;
      persistentOpts = opts;
      ctx = _ctx;
      for (i = 50000; i > 20000; i--) {
        ok = true;
        listener = null;
        try {
          listener = ServerSocketChannel.open();
          byte[] lo = new byte[4];
          lo[0] = 127;
          lo[1] = 0;
          lo[2] = 0;
          lo[3] = 1;
          listener.socket().bind(new java.net.InetSocketAddress(java.net.Inet4Address.getByAddress(lo), i), 50);
        } catch (IOException e) {
          if (listener != null) {
            listener.close();
            listener = null;
          }
          ok = false;
        }
        if (ok) break;
      }
      if (!ok) throw new IOException();
      port = i;
      Log.v("breviar", "Server: socket opened at port " + port);

      ok = false;
      for (i = i - 1; i > 20000; i--) {
        ok = true;
        listener_nonpersistent = null;
        try {
          listener_nonpersistent = ServerSocketChannel.open();
          byte[] lo = new byte[4];
          lo[0] = 127;
          lo[1] = 0;
          lo[2] = 0;
          lo[3] = 1;
          listener_nonpersistent.socket().bind(new java.net.InetSocketAddress(java.net.Inet4Address.getByAddress(lo), i), 50);
        } catch (IOException e) {
          listener_nonpersistent.close();
          listener_nonpersistent = null;
          ok = false;
        }
        if (ok) break;
      }
      if (!ok) throw new IOException();
      port_nonpersistent = i;

      Log.v("breviar", "Server: socket opened at nonpersistent port " + port_nonpersistent);
      running = true;
      // setDaemon(true);
    }

    public void setLanguage(String lang) {
      synchronized (settingsLock) {
        language = lang;
        ++settingsRevision;
      }
    }

    public void setOpts(String s) {
      synchronized (settingsLock) {
        persistentOpts = s;
        ++settingsRevision;
      }
    }

    public String getOpts() {
      synchronized (settingsLock) {
        return persistentOpts;
      }
    }

    // Force using current persistent options for the next request.
    // This is rather hacky (since it would not work well if there were multiple clients
    // talking to the server), but it is needed to avoid resetting options when using goBack()
    // in the WebView.
    private boolean force_opts_for_next_request = false;
    public void forceOptsForNextRequest() {
      synchronized (settingsLock) {
        force_opts_for_next_request = true;
      }
    }

    public void run() {
      Log.v("breviar", "Server: run started");
      try {
        Selector selector = Selector.open();
        listener.configureBlocking(false);
        listener.register(selector, SelectionKey.OP_ACCEPT, listener);
        listener_nonpersistent.configureBlocking(false);
        listener_nonpersistent.register(selector, SelectionKey.OP_ACCEPT, listener_nonpersistent);
        while (running) {
          try {
            if (selector.select() == 0) continue;
            Set keys = selector.selectedKeys();
            Iterator it = keys.iterator();
            while (it.hasNext()) {
              SelectionKey key = (SelectionKey)it.next();
              ServerSocketChannel socket = (ServerSocketChannel)(key.attachment());
              Socket client = socket.accept().socket();
              Log.v("breviar", "Server: handling connection");
              handle(client, socket == listener);
              client.close();
            }
            keys.clear();
          } catch (IOException e) {
            Log.v("Breviar: Server:", "run failed: " + e.getMessage());
          }
        }
        selector.close();
      } catch (IOException e) {
        Log.v("Breviar: Server:", "run failed at initialization: " + e.getMessage());
        running = false;
      }
      Log.v("breviar", "Server: run finished");
    }

    public void stopServer() {
      boolean intr;

      Log.v("breviar: Server:", "stopServer() called");
      running = false;
      try {
        listener.close();
        listener_nonpersistent.close();
        do {
          interrupt();
          try { join(100); } catch (java.lang.InterruptedException e) {}
        } while (isAlive());
      } catch (IOException e) {
        Log.v("breviar: Server:", "stopServer failed: " + e.getMessage());
      } catch (java.lang.SecurityException e) {
        Log.v("breviar: Server:", "stopServer failed: " + e.getMessage());
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

    synchronized void handleCgi(Socket client, String dokument, boolean postmethod, int cntlen, byte[] buf, boolean persistent) throws IOException {
      String requestOpts, requestLanguage;
      long requestRevision;
      boolean forceOpts;
      synchronized (settingsLock) {
        requestOpts = persistentOpts;
        requestLanguage = language;
        requestRevision = settingsRevision;
        forceOpts = force_opts_for_next_request;
        force_opts_for_next_request = false;
      }
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
      String localOpts;

      if (forceOpts) {
        if (requestOpts.startsWith("&") && !qs.isEmpty()) {
          qs = requestOpts.substring(1) + "&" + qs;
          Log.v("breviar", "Forcing persistent options: " + qs);
        }
      }

      if (!postmethod) {
        localOpts = render(pipe[1], pipein[0], "REQUEST_METHOD=GET\001QUERY_STRING=" + qs + "\001WWW_j=" + requestLanguage + "\001");
      } else {
        localOpts = render(pipe[1], pipein[0], "REQUEST_METHOD=POST\001CONTENT_TYPE=application/x-www-form-urlencoded\001CONTENT_LENGTH=" +
            cntlen + "\001QUERY_STRING=" + qs + "\001WWW_j=" + requestLanguage + "\001");
      }

      if (persistent) {
        synchronized (settingsLock) {
          // An older page may finish after the UI has already changed settings.
          if (requestRevision == settingsRevision) {
            persistentOpts = localOpts;
          }
        }
        Log.v("breviar", "persistentOpts = " + getOpts());
      } else {
        Log.v("breviar", "localOpts = " + localOpts);
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
    }

    synchronized void handleFile(Socket client, String dokument, boolean persistent) throws IOException {
      boolean is_css = dokument.equals("breviar.css");
      try {
        InputStream infile;
        if (dokument.startsWith("file/")) {
          String fn = dokument.substring(4);
          Log.v("breviar", "request for file " + fn);
          try {
            infile = new java.io.FileInputStream(fn);
          } catch (java.io.IOException e) {
            infile = new java.io.ByteArrayInputStream(new byte[0]);
          }
        } else {
          infile = ctx.getAssets().open(dokument, AssetManager.ACCESS_STREAMING);
        }
        client.getOutputStream().write(
            (
            "HTTP/1.1 200 OK\n" +
            "Server: Breviar\n" +
            "Connection: close\n\n"
            ).getBytes("UTF-8")
        );

        try {
          if (is_css) {
            client.getOutputStream().write(
                BreviarApp.getFontsCss(ctx).getBytes("UTF-8"));
          }
        } catch (java.io.IOException e) {
          Log.v("Breviar:", "IOException " + e.getMessage());
        }

        // do not start new thread, just copy here.
        new Copy(infile, client.getOutputStream() ).run();
      } catch (IOException e) {
        Log.v("breviar", "file not found: " + dokument);
        // last effort - default page
        try {
          handleCgi(client, scriptname + "?qt=pdnes&" + getOpts() , false, 0, new byte[0], persistent);
        } catch (IOException e2) {
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

    void handle(Socket client, boolean persistent) throws IOException {
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

      if (dokument.length() > scriptname.length() &&
          dokument.substring(0,scriptname.length()).equals(scriptname)) {
        handleCgi(client, dokument, postmethod, cntlen, buf, persistent);
      } else {
        handleFile(client, dokument, persistent);
      }
    }

    static {
      System.loadLibrary("breviar");
    }

}

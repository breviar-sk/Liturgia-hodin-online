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
    public int port;
    public int port_nonpersistent;
    ServerSocketChannel listener;
    ServerSocketChannel listener_nonpersistent;
    Context ctx;
    boolean running;
    static String scriptname;
    String language;
    String persistentOpts;
    boolean backgroundOverride = false;

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

    public synchronized void setLanguage(String lang) {
      language = lang;
    }

    public synchronized void setOpts(String s) {
      persistentOpts = s;
    }

    public String getOpts() {
      return persistentOpts;
    }

    public synchronized void setBackgroundOverride(boolean value) {
      backgroundOverride = value;
    }

    // Force using current persistent options for the next request.
    // This is rather hacky (since it would not work well if there were multiple clients
    // talking to the server), but it is needed to avoid resetting options when using goBack()
    // in the WebView.
    boolean force_opts_for_next_request = false;
    synchronized public void forceOptsForNextRequest() {
      force_opts_for_next_request = true;
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
      String localOpts = persistentOpts;

      if (force_opts_for_next_request) {
        force_opts_for_next_request = false;
        if (persistentOpts.startsWith("&") && !qs.isEmpty()) {
          qs = persistentOpts.substring(1) + "&" + qs;
          Log.v("breviar", "Forcing persistent options: " + qs);
        }
      }

      if (!postmethod) {
        localOpts = main(pipe[1], pipein[0], "REQUEST_METHOD=GET\001QUERY_STRING=" + qs + "\001WWW_j=" + language + "\001");
      } else {
        localOpts = main(pipe[1], pipein[0], "REQUEST_METHOD=POST\001CONTENT_TYPE=application/x-www-form-urlencoded\001CONTENT_LENGTH=" +
            cntlen + "\001QUERY_STRING=" + qs + "\001WWW_j=" + language + "\001");
      }

      if (persistent) {
        persistentOpts = localOpts;
        Log.v("breviar", "persistentOpts = " + persistentOpts);
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

    synchronized void handle(Socket client, boolean persistent) throws IOException {
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
        boolean is_css = dokument.equals("breviar.css");
        if (backgroundOverride && is_css) {
          Log.v("breviar", "Overriding url due to background override");
          dokument = "breviar-background-override.css";
        }
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
          new Copy( infile, client.getOutputStream() ).run();
        } catch (IOException e) {
          Log.v("breviar", "file not found: " + dokument);
          // last effort - default page
          try {
            handleCgi(client, scriptname + "?qt=pdnes&" + persistentOpts , false, 0, new byte[0], persistent);
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
    }

    static {
        System.loadLibrary("breviar");
    }

}

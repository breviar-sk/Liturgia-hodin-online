package sk.breviar.android;

import java.io.FileInputStream;
import java.io.FileDescriptor;
import java.io.IOException;

public class FdInputStream extends FileInputStream
{
    boolean closed;

    public FdInputStream(FileDescriptor fd) {
      super(fd);
      closed = false;
    }

    public void close() throws IOException {
      FileDescriptor fd = getFD();
      super.close();
      if (!closed) {
        closefd(fd);
        closed = true;
      }
    }

    public native void closefd(FileDescriptor fd);

    static {
        System.loadLibrary("breviar");
    }

}

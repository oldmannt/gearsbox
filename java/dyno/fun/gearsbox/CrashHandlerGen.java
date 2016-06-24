// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

package dyno.fun.gearsbox;

import java.util.concurrent.atomic.AtomicBoolean;

public abstract class CrashHandlerGen {
    public abstract void header(String path, String url);

    private static final class CppProxy extends CrashHandlerGen
    {
        private final long nativeRef;
        private final AtomicBoolean destroyed = new AtomicBoolean(false);

        private CppProxy(long nativeRef)
        {
            if (nativeRef == 0) throw new RuntimeException("nativeRef is zero");
            this.nativeRef = nativeRef;
        }

        private native void nativeDestroy(long nativeRef);
        public void destroy()
        {
            boolean destroyed = this.destroyed.getAndSet(true);
            if (!destroyed) nativeDestroy(this.nativeRef);
        }
        protected void finalize() throws java.lang.Throwable
        {
            destroy();
            super.finalize();
        }

        @Override
        public void header(String path, String url)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_header(this.nativeRef, path, url);
        }
        private native void native_header(long _nativeRef, String path, String url);
    }
}

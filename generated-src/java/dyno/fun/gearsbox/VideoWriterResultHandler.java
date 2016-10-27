// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

package dyno.fun.gearsbox;

import java.util.concurrent.atomic.AtomicBoolean;

public abstract class VideoWriterResultHandler {
    public abstract void onComplete(boolean success, String path);

    /** there is frame in buffer, especially in slo-mo mode memory full */
    public abstract void beforeComplete();

    public abstract void onProgress(float percent);

    private static final class CppProxy extends VideoWriterResultHandler
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
        public void onComplete(boolean success, String path)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_onComplete(this.nativeRef, success, path);
        }
        private native void native_onComplete(long _nativeRef, boolean success, String path);

        @Override
        public void beforeComplete()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_beforeComplete(this.nativeRef);
        }
        private native void native_beforeComplete(long _nativeRef);

        @Override
        public void onProgress(float percent)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_onProgress(this.nativeRef, percent);
        }
        private native void native_onProgress(long _nativeRef, float percent);
    }
}
// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

package dyno.fun.gearsbox;

import java.util.concurrent.atomic.AtomicBoolean;

public abstract class CameraCaptureHandler {
    public abstract void captureOutput(VideoFrameGen picture, String error);

    private static final class CppProxy extends CameraCaptureHandler
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
        public void captureOutput(VideoFrameGen picture, String error)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_captureOutput(this.nativeRef, picture, error);
        }
        private native void native_captureOutput(long _nativeRef, VideoFrameGen picture, String error);
    }
}

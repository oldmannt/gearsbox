// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

package dyno.fun.gearsbox;

import java.util.concurrent.atomic.AtomicBoolean;

public abstract class VideoEncoderGen {
    public abstract boolean initialize(String filepath, int fps, int bitrate, int width, int height, VideoFrameGen frame);

    public abstract void encodeFrame(VideoFrameGen frame);

    public abstract void saveNRelease();

    private static final class CppProxy extends VideoEncoderGen
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
        public boolean initialize(String filepath, int fps, int bitrate, int width, int height, VideoFrameGen frame)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_initialize(this.nativeRef, filepath, fps, bitrate, width, height, frame);
        }
        private native boolean native_initialize(long _nativeRef, String filepath, int fps, int bitrate, int width, int height, VideoFrameGen frame);

        @Override
        public void encodeFrame(VideoFrameGen frame)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_encodeFrame(this.nativeRef, frame);
        }
        private native void native_encodeFrame(long _nativeRef, VideoFrameGen frame);

        @Override
        public void saveNRelease()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_saveNRelease(this.nativeRef);
        }
        private native void native_saveNRelease(long _nativeRef);
    }
}

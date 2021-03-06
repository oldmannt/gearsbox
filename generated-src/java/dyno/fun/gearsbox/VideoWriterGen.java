// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

package dyno.fun.gearsbox;

import java.util.concurrent.atomic.AtomicBoolean;

public abstract class VideoWriterGen {
    public abstract void setReslutHandler(VideoWriterResultHandler handler);

    public abstract void setFilePath(String file);

    public abstract String getFilePath();

    public abstract void setFPS(int fps);

    public abstract int getFPS();

    public abstract void setBitRate(int rate);

    public abstract void setOrientation(VideoOrientation ori);

    public abstract void setVideoEncoder(VideoEncoderGen encoder);

    public abstract void encodeFrame(VideoFrameGen frame);

    public abstract void start(long interval);

    public abstract void pause();

    public abstract void resume();

    public abstract boolean isRunning();

    public abstract void setInterval(long interval);

    public abstract void saveNRlease();

    public static native VideoWriterGen create();

    private static final class CppProxy extends VideoWriterGen
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
        public void setReslutHandler(VideoWriterResultHandler handler)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setReslutHandler(this.nativeRef, handler);
        }
        private native void native_setReslutHandler(long _nativeRef, VideoWriterResultHandler handler);

        @Override
        public void setFilePath(String file)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setFilePath(this.nativeRef, file);
        }
        private native void native_setFilePath(long _nativeRef, String file);

        @Override
        public String getFilePath()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getFilePath(this.nativeRef);
        }
        private native String native_getFilePath(long _nativeRef);

        @Override
        public void setFPS(int fps)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setFPS(this.nativeRef, fps);
        }
        private native void native_setFPS(long _nativeRef, int fps);

        @Override
        public int getFPS()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getFPS(this.nativeRef);
        }
        private native int native_getFPS(long _nativeRef);

        @Override
        public void setBitRate(int rate)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setBitRate(this.nativeRef, rate);
        }
        private native void native_setBitRate(long _nativeRef, int rate);

        @Override
        public void setOrientation(VideoOrientation ori)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setOrientation(this.nativeRef, ori);
        }
        private native void native_setOrientation(long _nativeRef, VideoOrientation ori);

        @Override
        public void setVideoEncoder(VideoEncoderGen encoder)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setVideoEncoder(this.nativeRef, encoder);
        }
        private native void native_setVideoEncoder(long _nativeRef, VideoEncoderGen encoder);

        @Override
        public void encodeFrame(VideoFrameGen frame)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_encodeFrame(this.nativeRef, frame);
        }
        private native void native_encodeFrame(long _nativeRef, VideoFrameGen frame);

        @Override
        public void start(long interval)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_start(this.nativeRef, interval);
        }
        private native void native_start(long _nativeRef, long interval);

        @Override
        public void pause()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_pause(this.nativeRef);
        }
        private native void native_pause(long _nativeRef);

        @Override
        public void resume()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_resume(this.nativeRef);
        }
        private native void native_resume(long _nativeRef);

        @Override
        public boolean isRunning()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_isRunning(this.nativeRef);
        }
        private native boolean native_isRunning(long _nativeRef);

        @Override
        public void setInterval(long interval)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setInterval(this.nativeRef, interval);
        }
        private native void native_setInterval(long _nativeRef, long interval);

        @Override
        public void saveNRlease()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_saveNRlease(this.nativeRef);
        }
        private native void native_saveNRlease(long _nativeRef);
    }
}

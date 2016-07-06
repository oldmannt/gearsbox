// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

package dyno.fun.gearsbox;

import java.util.concurrent.atomic.AtomicBoolean;

public abstract class TimerGen {
    public abstract boolean start();

    public abstract void stop();

    public abstract int getRepeated();

    public abstract long getTimePassed();

    public abstract boolean isRunning();

    public static native TimerGen create(long timeout, int repeatTimes, TimerHandlerGen hander);

    private static final class CppProxy extends TimerGen
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
        public boolean start()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_start(this.nativeRef);
        }
        private native boolean native_start(long _nativeRef);

        @Override
        public void stop()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_stop(this.nativeRef);
        }
        private native void native_stop(long _nativeRef);

        @Override
        public int getRepeated()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getRepeated(this.nativeRef);
        }
        private native int native_getRepeated(long _nativeRef);

        @Override
        public long getTimePassed()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getTimePassed(this.nativeRef);
        }
        private native long native_getTimePassed(long _nativeRef);

        @Override
        public boolean isRunning()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_isRunning(this.nativeRef);
        }
        private native boolean native_isRunning(long _nativeRef);
    }
}
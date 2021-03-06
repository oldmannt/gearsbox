// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

package dyno.fun.gearsbox;

import java.util.concurrent.atomic.AtomicBoolean;

public abstract class CameraConfigGen {
    public static final String FLASH_MODE = "flash_mode";

    public static final String FLASH_MODE_AUTO = "auto";

    public static final String FLASH_MODE_ON = "on";

    public static final String FLASH_MODE_OFF = "off";

    public static final String QUALITY = "quality";

    public static final String QUALITY_360P = "360p";

    public static final String QUALITY_480P = "480p";

    public static final String QUALITY_720P = "720p";

    public static final String QUALITY_1080P = "1080p";

    public abstract boolean initialize(ConfigGen cfg);

    public abstract CameraFlash getFlashMode();

    public abstract CameraQuality getQuatityLevel();

    public abstract void setFlashMode(CameraFlash mode);

    public abstract void setQuatityLevel(CameraQuality quality);

    public static native CameraConfigGen instance();

    private static final class CppProxy extends CameraConfigGen
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
        public boolean initialize(ConfigGen cfg)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_initialize(this.nativeRef, cfg);
        }
        private native boolean native_initialize(long _nativeRef, ConfigGen cfg);

        @Override
        public CameraFlash getFlashMode()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getFlashMode(this.nativeRef);
        }
        private native CameraFlash native_getFlashMode(long _nativeRef);

        @Override
        public CameraQuality getQuatityLevel()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getQuatityLevel(this.nativeRef);
        }
        private native CameraQuality native_getQuatityLevel(long _nativeRef);

        @Override
        public void setFlashMode(CameraFlash mode)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setFlashMode(this.nativeRef, mode);
        }
        private native void native_setFlashMode(long _nativeRef, CameraFlash mode);

        @Override
        public void setQuatityLevel(CameraQuality quality)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setQuatityLevel(this.nativeRef, quality);
        }
        private native void native_setQuatityLevel(long _nativeRef, CameraQuality quality);
    }
}

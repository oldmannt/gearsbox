// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

package dyno.fun.gearsbox;

import java.util.concurrent.atomic.AtomicBoolean;

public abstract class InstanceGetterGen {
    public static native CameraControllerGen getCameraController();

    public static native void setCameraController(CameraControllerGen camera);

    public static native PlatformUtilityGen getPlatformUtility();

    public static native void setPlatformUtility(PlatformUtilityGen mgr);

    public static native ConfigGen getConfig(String id);

    private static final class CppProxy extends InstanceGetterGen
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
    }
}

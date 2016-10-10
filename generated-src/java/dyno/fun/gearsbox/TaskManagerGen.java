// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

package dyno.fun.gearsbox;

import java.util.concurrent.atomic.AtomicBoolean;

/**
 *delay<0 immediately
 *delay==0 next frame
 */
public abstract class TaskManagerGen {
    /**delay<0 excuse immidiately, delay==0 next frame, repeaed <=0 not reapead */
    public abstract void addTask(long taskId, long delay, long repeated, TaskExcuserGen task);

    public abstract void addTaskI(long taskId, TaskExcuserGen task);

    public abstract void addTaskInfo(TaskInfoGen task, TaskExcuserGen taskExcuser);

    public abstract void addTaskExcuser(TaskExcuserGen task);

    public abstract void removeTask(long taskId);

    public static native TaskManagerGen instance();

    public static native TaskInfoGen createInfo(long taskId, long delay, int repeated);

    private static final class CppProxy extends TaskManagerGen
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
        public void addTask(long taskId, long delay, long repeated, TaskExcuserGen task)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_addTask(this.nativeRef, taskId, delay, repeated, task);
        }
        private native void native_addTask(long _nativeRef, long taskId, long delay, long repeated, TaskExcuserGen task);

        @Override
        public void addTaskI(long taskId, TaskExcuserGen task)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_addTaskI(this.nativeRef, taskId, task);
        }
        private native void native_addTaskI(long _nativeRef, long taskId, TaskExcuserGen task);

        @Override
        public void addTaskInfo(TaskInfoGen task, TaskExcuserGen taskExcuser)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_addTaskInfo(this.nativeRef, task, taskExcuser);
        }
        private native void native_addTaskInfo(long _nativeRef, TaskInfoGen task, TaskExcuserGen taskExcuser);

        @Override
        public void addTaskExcuser(TaskExcuserGen task)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_addTaskExcuser(this.nativeRef, task);
        }
        private native void native_addTaskExcuser(long _nativeRef, TaskExcuserGen task);

        @Override
        public void removeTask(long taskId)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_removeTask(this.nativeRef, taskId);
        }
        private native void native_removeTask(long _nativeRef, long taskId);
    }
}

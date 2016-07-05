package dyno.fun.gearsbox;

import android.os.Handler;
import android.os.Message;

import java.util.Timer;
import java.util.TimerTask;

/**
 * Created by dyno on 7/1/16.
 */

public class MainThreadLooper {

    public interface Listenner {
        void doSomething(long elapse);
    }

    public MainThreadLooper(long msecond, Listenner listenner){
        m_period = msecond;
        m_listenner = listenner;
    }

    public void start(){
        m_handler = new Handler();
        m_net_looper = new Runnable() {
            private long last = System.currentTimeMillis();
            @Override
            public void run() {
                long current = System.currentTimeMillis();
                //LogGen.instance().log(LogGen.LOG_CONSOLE, LogGen.LOG_INFO, String.format("timer run elapse %d", current-last));
                m_listenner.doSomething(current-last);
                last = current;
            }
        };

        m_timer = new Timer();
        m_timer.schedule(new TimerTask() {

            public void run() {
                //s_handler.sendEmptyMessage(999);

                m_handler.post(m_net_looper);
            }
        }, 0, m_period);
    }

    private Timer m_timer;
    private Handler m_handler = null;
    private Runnable m_net_looper = null;
    private long m_period;
    private Listenner m_listenner;
}

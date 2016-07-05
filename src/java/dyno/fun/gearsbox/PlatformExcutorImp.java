package dyno.fun.gearsbox;

import android.app.Activity;
import android.os.IBinder;
import android.view.inputmethod.InputMethodManager;

/**
 * Created by dyno on 7/1/16.
 */

public class PlatformExcutorImp extends PlatformExecutorGen {
    @Override
    public void endEniting(boolean force) {
        utils.hideKeyboard();
    }
}

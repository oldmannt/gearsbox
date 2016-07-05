package dyno.fun.gearsbox;

import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.content.res.Resources;
import android.os.IBinder;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;

/**
 * Created by dyno on 6/27/16.
 */

public class utils {

    private static Activity s_cur_activity;
    public static Activity getCurActivity() {
        return s_cur_activity;
    }

    public static void setCurActivity(Activity act){
        s_cur_activity = act;
    }

    public static void clearActivity(Activity act_clear){
        if (act_clear != s_cur_activity)
            return;
        s_cur_activity = null;
    }

    public static View getAndroidView(ViewGen view_gen){
        if (null == view_gen){
            LogGen.instance().logerrf("getAndroidView viewgen null");
            return null;
        }

        View view = ((ViewImp)view_gen).getUIView();
        if (null == view){
            LogGen.instance().logerrf("getAndroidView viewfrom android view null");
            return null;
        }

        return view;
    }

    public static View getActivityRoot(Activity activity) {
        return ((ViewGroup) activity.findViewById(android.R.id.content)).getChildAt(0);
    }

    public static View getAndroidView(String view_name){
        ViewGen view_gen = UiManagerGen.instance().getView(view_name);

        return getAndroidView(view_gen);
    }

    public static float convertDpToPx(Context context, float dp) {
        Resources res = context.getResources();

        return dp * (res.getDisplayMetrics().densityDpi / 160f);
    }

    /**
     * Show keyboard and focus to given EditText
     *
     * @param context Context
     * @param target  EditText to focus
     */
    public static void showKeyboard(Context context, EditText target) {
        if (context == null || target == null) {
            return;
        }

        InputMethodManager imm = getInputMethodManager(context);

        imm.showSoftInput(target, InputMethodManager.SHOW_IMPLICIT);
    }

    /**
     * hide keyboard
     *
     * @param context Context
     * @param target  View that currently has focus
     */
    public static void hideKeyboard(Context context, View target) {
        if (context == null || target == null) {
            return;
        }

        InputMethodManager imm = getInputMethodManager(context);
        imm.hideSoftInputFromWindow(target.getWindowToken(), 0);
    }

    /**
     * Show keyboard and focus to given EditText.
     * Use this method if target EditText is in Dialog.
     *
     * @param dialog Dialog
     * @param target EditText to focus
     */
    public static void showKeyboardInDialog(Dialog dialog, EditText target) {
        if (dialog == null || target == null) {
            return;
        }

        dialog.getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_VISIBLE);
        target.requestFocus();
    }

    /**
     * hide keyboard
     *
     * @param activity Activity
     */
    public static void hideKeyboard(Activity activity) {
        View view = activity.getCurrentFocus();

        if (view != null) {
            hideKeyboard(activity, view);
        }
    }

    public static void hideKeyboard(){
        Activity activity = utils.getCurActivity();
        if (null == activity){
            LogGen.instance().logerrf("endEniting current activity null");
            return;
        }
        InputMethodManager inputMethodManager = (InputMethodManager)  activity.getSystemService(Activity.INPUT_METHOD_SERVICE);

        IBinder ib = null;
        if (activity.getCurrentFocus()!=null){
            ib = activity.getCurrentFocus().getWindowToken();
        }
        else if (activity.getWindow().getDecorView()!=null){
            ib = activity.getWindow().getDecorView().getWindowToken();
        }
        inputMethodManager.hideSoftInputFromWindow(ib, 0);
    }

    private static InputMethodManager getInputMethodManager(Context context) {
        return (InputMethodManager) context.getSystemService(Context.INPUT_METHOD_SERVICE);
    }

}

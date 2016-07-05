package dyno.fun.gearsbox;

import android.graphics.Color;
import android.support.annotation.ColorInt;
import android.text.InputType;
import android.view.View;

import static dyno.fun.gearsbox.TextAlign.*;

/**
 * Created by dyno on 6/27/16.
 */

public class TyperConvertor {
    
    static int convertUIColor(ArgbColor color) {
        return  Color.argb((int)color.getA()*255, (int)color.getR()*255, (int)color.getG()*255, (int)color.getB()*255);
    }

    public void convertUIRect(ViewFrame rect) {

    }

    public void convertUIConstraintType(ConstraintType type) {

    }

    public void convertUITextBoarder(TextBoarder type) {

    }

    public static int convertUITextAlign(TextAlign type) {
        switch (type){
            case LEFT:
                return View.TEXT_ALIGNMENT_TEXT_START;
            case RIGHT:
                return View.TEXT_ALIGNMENT_TEXT_END;
            case CENTER:
                return View.TEXT_ALIGNMENT_CENTER;
            case NONE:
            default:
                break;
        }

        LogGen.instance().logerrf("convert err TextAlign type: " + type.toString());
        return  -1;
    }

    public static int convertKeyboardType(TextKeyboard type) {
        switch (type){
            case ASCII:
                return InputType.TYPE_TEXT_VARIATION_PERSON_NAME;
            case URL:
                return InputType.TYPE_TEXT_VARIATION_URI;
            case NUMBERPAD:
                return InputType.TYPE_NUMBER_FLAG_SIGNED;
            case PHONEPAD:
                return InputType.TYPE_TEXT_VARIATION_PHONETIC;
            case DECIMALPAD:
                return InputType.TYPE_NUMBER_FLAG_DECIMAL;
            case DEFAULT:
            default:
                return InputType.TYPE_NUMBER_VARIATION_NORMAL;
        }
    }
}

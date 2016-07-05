// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

package dyno.fun.gearsbox;

import java.util.ArrayList;

public final class ViewConf {

    public static final ViewFrame NOFRAME = new ViewFrame(
        -1 /* mX */ ,
        -1 /* mY */ ,
        -1 /* mW */ ,
        -1 /* mH */ );

    public static final ArgbColor NOGBCOLOR = new ArgbColor(
        -1 /* mA */ ,
        0 /* mR */ ,
        0 /* mG */ ,
        0 /* mB */ );


    /*package*/ final String mId;

    /*package*/ final ViewType mType;

    /*package*/ final ViewFrame mFrame;

    /*package*/ final ArgbColor mBgcolor;

    /*package*/ final int mFontsize;

    /*package*/ final TextAlign mTextalign;

    /*package*/ final TextBoarder mTextboarder;

    /*package*/ final String mText;

    /*package*/ final boolean mNumericText;

    /*package*/ final TextKeyboard mKeyboardtype;

    /*package*/ final int mMaxlength;

    /*package*/ final ArrayList<ViewConstraint> mConstraints;

    /*package*/ final ArrayList<ViewConf> mSubviews;

    public ViewConf(
            String id,
            ViewType type,
            ViewFrame frame,
            ArgbColor bgcolor,
            int fontsize,
            TextAlign textalign,
            TextBoarder textboarder,
            String text,
            boolean numericText,
            TextKeyboard keyboardtype,
            int maxlength,
            ArrayList<ViewConstraint> constraints,
            ArrayList<ViewConf> subviews) {
        this.mId = id;
        this.mType = type;
        this.mFrame = frame;
        this.mBgcolor = bgcolor;
        this.mFontsize = fontsize;
        this.mTextalign = textalign;
        this.mTextboarder = textboarder;
        this.mText = text;
        this.mNumericText = numericText;
        this.mKeyboardtype = keyboardtype;
        this.mMaxlength = maxlength;
        this.mConstraints = constraints;
        this.mSubviews = subviews;
    }

    public String getId() {
        return mId;
    }

    public ViewType getType() {
        return mType;
    }

    public ViewFrame getFrame() {
        return mFrame;
    }

    public ArgbColor getBgcolor() {
        return mBgcolor;
    }

    public int getFontsize() {
        return mFontsize;
    }

    public TextAlign getTextalign() {
        return mTextalign;
    }

    public TextBoarder getTextboarder() {
        return mTextboarder;
    }

    public String getText() {
        return mText;
    }

    public boolean getNumericText() {
        return mNumericText;
    }

    public TextKeyboard getKeyboardtype() {
        return mKeyboardtype;
    }

    public int getMaxlength() {
        return mMaxlength;
    }

    public ArrayList<ViewConstraint> getConstraints() {
        return mConstraints;
    }

    public ArrayList<ViewConf> getSubviews() {
        return mSubviews;
    }

    @Override
    public String toString() {
        return "ViewConf{" +
                "mId=" + mId +
                "," + "mType=" + mType +
                "," + "mFrame=" + mFrame +
                "," + "mBgcolor=" + mBgcolor +
                "," + "mFontsize=" + mFontsize +
                "," + "mTextalign=" + mTextalign +
                "," + "mTextboarder=" + mTextboarder +
                "," + "mText=" + mText +
                "," + "mNumericText=" + mNumericText +
                "," + "mKeyboardtype=" + mKeyboardtype +
                "," + "mMaxlength=" + mMaxlength +
                "," + "mConstraints=" + mConstraints +
                "," + "mSubviews=" + mSubviews +
        "}";
    }

}

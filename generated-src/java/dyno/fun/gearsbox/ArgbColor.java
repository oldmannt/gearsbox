// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

package dyno.fun.gearsbox;

public final class ArgbColor {

    public static final ArgbColor NOCOLOR = new ArgbColor(
        0 /* mA */ ,
        0 /* mR */ ,
        0 /* mG */ ,
        0 /* mB */ );

    public static final ArgbColor REDCOLOR = new ArgbColor(
        1 /* mA */ ,
        1 /* mR */ ,
        0 /* mG */ ,
        0 /* mB */ );

    public static final ArgbColor GREENCOLOR = new ArgbColor(
        1 /* mA */ ,
        0 /* mR */ ,
        1 /* mG */ ,
        0 /* mB */ );

    public static final ArgbColor BLUECOLOR = new ArgbColor(
        1 /* mA */ ,
        0 /* mR */ ,
        0 /* mG */ ,
        1 /* mB */ );

    public static final ArgbColor BLACKCOLOR = new ArgbColor(
        1 /* mA */ ,
        0 /* mR */ ,
        0 /* mG */ ,
        0 /* mB */ );

    public static final ArgbColor WHITECOLOR = new ArgbColor(
        1 /* mA */ ,
        1 /* mR */ ,
        1 /* mG */ ,
        1 /* mB */ );


    /*package*/ final float mA;

    /*package*/ final float mR;

    /*package*/ final float mG;

    /*package*/ final float mB;

    public ArgbColor(
            float a,
            float r,
            float g,
            float b) {
        this.mA = a;
        this.mR = r;
        this.mG = g;
        this.mB = b;
    }

    public float getA() {
        return mA;
    }

    public float getR() {
        return mR;
    }

    public float getG() {
        return mG;
    }

    public float getB() {
        return mB;
    }

    @Override
    public String toString() {
        return "ArgbColor{" +
                "mA=" + mA +
                "," + "mR=" + mR +
                "," + "mG=" + mG +
                "," + "mB=" + mB +
        "}";
    }

}
package dyno.fun.gearsbox;

import android.content.Context;
import android.view.View;

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.MobileAds;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GoogleApiAvailability;

import static com.google.android.gms.common.ConnectionResult.SERVICE_INVALID;

/**
 * Created by dyno on 7/3/16.
 */

public class AdmodBanner {
    private AdView mAdView;
    public AdmodBanner(Context context, View adview, String appid){

        int gps = GoogleApiAvailability.getInstance().isGooglePlayServicesAvailable(context);

        if (gps != ConnectionResult.SERVICE_DISABLED &&
                gps != ConnectionResult.SERVICE_INVALID &&
                gps != ConnectionResult.SERVICE_MISSING){
            MobileAds.initialize(context, appid);
            // Gets the ad view defined in layout/ad_fragment.xml with ad unit ID set in
            // values/strings.xml.
            mAdView = (AdView) adview;
        }
        else {
            LogGen.instance().logerrf("google service invalid:"+ GoogleApiAvailability.getInstance().getErrorString(gps));
            adview.setVisibility(View.GONE);
        }

    }

    public void loadRequest(){
        if (null == mAdView){
            return;
        }
        // Create an ad request. Check your logcat output for the hashed device ID to
        // get test ads on a physical device. e.g.
        // "Use AdRequest.Builder.addTestDevice("ABCDEF012345") to get test ads on this device."
        AdRequest adRequest = new AdRequest.Builder()
                .addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
                .build();

        // Start loading the ad in the background.
        mAdView.loadAd(adRequest);
    }

    public void setVisibility(int state){
        if (null==mAdView){
            return;
        }
        mAdView.setVisibility(state);
    }

    public void onDestroy() {
        if (mAdView != null) {
            mAdView.destroy();
        }
    }

    public void onPause() {
        if (mAdView != null) {
            mAdView.pause();
        }
    }

    /** Called when returning to the activity */
    public void onResume() {
        if (mAdView != null) {
            mAdView.resume();
        }
    }

}

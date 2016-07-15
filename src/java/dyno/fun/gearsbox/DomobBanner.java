package dyno.fun.gearsbox;

import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;

import cn.domob.android.ads.AdEventListener;
import cn.domob.android.ads.AdManager.ErrorCode;
import cn.domob.android.ads.AdView;

/**
 * Created by dyno on 7/14/16.
 */

public class DomobBanner {
    private AdView mAdview;
    private Activity m_context;
    public DomobBanner(Activity context, View container_view, String public_id, String inline_id) {
        // Create ad view
        m_context = context;
        mAdview = new AdView(context, public_id, inline_id);
        mAdview.setKeyword("game");
        mAdview.setUserGender("male");
        mAdview.setUserBirthdayStr("2000-08-08");
        mAdview.setUserPostcode("123456");
        mAdview.setAdEventListener(new AdEventListener() {
            @Override
            public void onAdOverlayPresented(AdView adView) {
                //Log.i("DomobSDKDemo", "overlayPresented");
            }
            @Override
            public void onAdOverlayDismissed(AdView adView) {
                //Log.i("DomobSDKDemo", "Overrided be dismissed");
            }
            @Override
            public void onAdClicked(AdView arg0) {
                //Log.i("DomobSDKDemo", "onDomobAdClicked");
            }
            @Override
            public void onLeaveApplication(AdView arg0) {
                //Log.i("DomobSDKDemo", "onDomobLeaveApplication");
            }
            @Override
            public Context onAdRequiresCurrentContext() {
                return DomobBanner.this.m_context;
            }
            @Override
            public void onAdFailed(AdView arg0, ErrorCode arg1) {
                //Log.i("DomobSDKDemo", "onDomobAdFailed");
            }
            @Override
            public void onEventAdReturned(AdView arg0) {
                //Log.i("DomobSDKDemo", "onDomobAdReturned");
            }
        });
        RelativeLayout.LayoutParams layout = new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT,
                ViewGroup.LayoutParams.WRAP_CONTENT);
        layout.addRule(RelativeLayout.CENTER_HORIZONTAL);
        mAdview.setLayoutParams(layout);
        ((RelativeLayout)container_view).addView(mAdview);

    }

    public void orientationChange(){
        if (null != mAdview){
            mAdview.orientationChanged();
        }
    }
}

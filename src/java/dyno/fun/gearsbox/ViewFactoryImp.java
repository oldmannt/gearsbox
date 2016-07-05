package dyno.fun.gearsbox;

import android.app.Activity;
import android.graphics.Color;
import android.text.InputFilter;
import android.text.InputType;
import android.text.method.DigitsKeyListener;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RelativeLayout;
import android.widget.TextView;
import java.util.ArrayList;

/**
 * Created by dyno on 6/28/16.
 */

public class ViewFactoryImp extends ViewFactoryGen {
    public static ViewFactoryGen instance = new ViewFactoryImp();
    @Override
    public ViewGen createView(ViewConf conf) {
        if (conf == null){
            LogGen.instance().logerrf("conf null");
            return  null;
        }

        ViewImp viewimp = (ViewImp)UiManagerGen.instance().getView(conf.getId());
        if (viewimp!=null){
            //LogGen.instance().logerrf("create failed already in manager id: "+ conf.getId());
            configViewImp(viewimp, conf);
            return viewimp;
        }

        View new_view = null;
        switch (conf.getType()){
            case BASE:{
                View view = new View(utils.getCurActivity());
                setBaseConf(view, conf);
                new_view = view;
            }
            break;
            case LABEL:{
                TextView view = new TextView(utils.getCurActivity());
                setBaseConf(view, conf);
                setTextViewConf(view, conf);
                new_view = view;
            }
                break;
            case INPUT:{
                EditText view = new EditText(utils.getCurActivity());
                setBaseConf(view, conf);
                setEditTextConf(view, conf);
                new_view = view;
            }
                break;
            case BTN:{
                Button view = new Button(utils.getCurActivity());
                setBaseConf(view, conf);
                setBtnConf(view, conf);
                new_view = view;
            }
                break;
        }

        viewimp = new ViewImp(conf.getId(), new_view);
        return viewimp;
    }

    @Override
    public ViewGen createViewById(String id, ViewType type) {
        if (id == null){
            LogGen.instance().logerrf("createViewById id null ");
            return null;
        }
        ViewConf conf = new ViewConf(id,type, ViewConf.NOFRAME,
                ViewConf.NOGBCOLOR, -1, TextAlign.NONE, TextBoarder.NONE,
                "", false, TextKeyboard.DEFAULT, -1,new ArrayList<ViewConstraint>(), new ArrayList<ViewConf>());
        return createView(conf);
    }

    @Override
    public boolean injectView(ViewGen view) {
        if (null == view){
            LogGen.instance().logerrf("inject null view");
            return false;
        }

        ViewConf conf = UiConfGen.instance().getViewConf(view.getId());
        if (null == conf){
            LogGen.instance().logerrf("injectView conf null");
            return false;
        }

        ViewImp viewImp = (ViewImp)view;
        //setBaseConf(viewImp.getUIView(), conf);
        createSubViews(viewImp, conf);
        //createConstraints(viewImp, conf);

        return true;
    }

    public boolean configViewImp(ViewImp view_imp, ViewConf conf){
        if (view_imp==null || conf==null){
            LogGen.instance().logerrf("configViewImp view_imp or conf null");
            return false;
        }

        View view = view_imp.getUIView();
        if (view == null){
            LogGen.instance().logerrf("configViewImp android view null:"+view_imp.getId());
            return false;
        }

        if (view instanceof TextView){
            setTextViewConf((TextView)view,conf);
        }
        if (view instanceof EditText){
            setEditTextConf((EditText)view, conf);
        }
        if (view instanceof Button){
            setBtnConf((Button)view, conf);
        }

        return true;
    }

    private void setBaseConf(View view, ViewConf conf){
        if (view == null || conf == null){
            return;
        }

        int width = RelativeLayout.LayoutParams.WRAP_CONTENT;
        int height = RelativeLayout.LayoutParams.WRAP_CONTENT;
        //if (UiValueCheckerGen.instance().isValidFrame(conf.getFrame())){
        //    width = (int)conf.getFrame().getW()==0?RelativeLayout.LayoutParams.WRAP_CONTENT:(int)conf.getFrame().getW();
        //    height = (int)conf.getFrame().getH()==0?RelativeLayout.LayoutParams.WRAP_CONTENT:(int)conf.getFrame().getH();
        //}

        if (UiValueCheckerGen.instance().isValidColor(conf.getBgcolor())){
            view.setBackgroundColor(TyperConvertor.convertUIColor(conf.getBgcolor()));
        }

        RelativeLayout.LayoutParams lp = new RelativeLayout.LayoutParams(width, height);
        view.setLayoutParams(lp);
        view.setId(View.generateViewId());
        //view.setBackgroundColor(Color.BLACK);
    }

    private void setTextViewConf(TextView view, ViewConf conf){
        if (view == null || conf == null){
            return;
        }

        if (conf.getFontsize()>0)
            view.setTextSize(conf.getFontsize());

        switch (conf.getTextalign()){
            case LEFT:
                view.setTextAlignment(View.TEXT_ALIGNMENT_TEXT_START);
            case RIGHT:
                view.setTextAlignment(View.TEXT_ALIGNMENT_TEXT_END);
            case CENTER:
                view.setTextAlignment(View.TEXT_ALIGNMENT_CENTER);
            case NONE:
            default:
                break;
        }

        if (conf.getMaxlength()>0){
            view.setFilters(new InputFilter[]{new InputFilter.LengthFilter(conf.getMaxlength())});
        }
        //view.setBackgroundColor(Color.rgb(0,0,100));
        //view.setText("fire in the hole");
    }

    private void setEditTextConf(EditText edit, ViewConf conf){
        if (edit == null || conf == null){
            return;
        }

        if (conf.getKeyboardtype() != TextKeyboard.DEFAULT)
            edit.setInputType(TyperConvertor.convertKeyboardType(conf.getKeyboardtype()));

        if (conf.getNumericText())
            edit.setKeyListener(DigitsKeyListener.getInstance(false,true));

        if (conf.getText().length()>0){
            edit.setText(conf.getText());
        }
        //edit.setBackgroundColor(Color.GREEN);
    }

    private void setBtnConf(Button btn, ViewConf conf){
        if (btn == null || conf == null){
            return;
        }

        if (conf.getText().length()>0){
            btn.setText(conf.getText());
        }
    }

    private void createSubViews(ViewImp viewimp, ViewConf conf){
        for (ViewConf subconf: conf.getSubviews()){
            if (null == viewimp.addSubView(subconf)){
                LogGen.instance().logerrf("createSubViews failed conf:"+conf.toString());
                continue;
            }
        }
    }

    private void createConstraints(ViewImp viewimp, ViewConf conf){
        for (ViewConstraint constraint: conf.getConstraints()){
            viewimp.addConstraint(constraint);
        }
    }
}

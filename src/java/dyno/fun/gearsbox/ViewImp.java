package dyno.fun.gearsbox;

import android.graphics.Color;
import android.graphics.drawable.GradientDrawable;
import android.support.annotation.NonNull;
import android.text.Editable;
import android.text.InputFilter;
import android.text.TextWatcher;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewTreeObserver;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RelativeLayout;
import android.widget.Space;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import static android.view.ViewGroup.LayoutParams.MATCH_PARENT;

/**
 * Created by dyno on 6/26/16.
 */

public class ViewImp extends ViewGen {
    @Override
    public String getId() {
        return m_id;
    }

    @Override
    public void setFrame(ViewFrame frame) {
        if (null == m_view){
            LogGen.instance().logerrf("setFrame m_view null "+m_id);
            return;
        }
        m_view.setLeft((int) frame.getX());
        m_view.setTop((int) frame.getY());
        m_view.setRight((int)(frame.getX()+frame.getW()));
        m_view.setBottom((int)(frame.getY()+frame.getH()));
    }

    @Override
    public ViewFrame getFrame() {
        if (null == m_view){
            LogGen.instance().logerrf("getFrame m_view null "+m_id);
            return null;
        }

        ViewFrame frame = new ViewFrame(m_view.getLeft(), m_view.getTop(),
                                        m_view.getWidth(), m_view.getHeight());
        return frame;
    }

    @Override
    public void setBackgroundColor(float a, float r, float g, float b) {
        if (null == m_view){
            LogGen.instance().logerrf("setBackgroundColor m_view null "+m_id);
            return;
        }

        //m_view.setBackgroundColor(Color.argb((int)a*255,(int)r*255,(int)g*255,(int)b*255));
    }

    @Override
    public void setVisiable(boolean v) {
        if (null == m_view){
            LogGen.instance().logerrf("setVisiable m_view null "+m_id);
            return;
        }

        m_view.setVisibility(v?View.VISIBLE:View.INVISIBLE);
    }

    @Override
    public ViewType getType() {
        if (m_view instanceof EditText)
            return ViewType.INPUT;
        else if (m_view instanceof Button)
            return ViewType.BTN;
        else if (m_view instanceof TextView)
            return ViewType.LABEL;
        else if (m_view instanceof ViewGroup)
            return ViewType.BASE;

        LogGen.instance().logerrf("error type ");
        return ViewType.BASE;
    }

    @Override
    public void setBoard(float width, ArgbColor color) {
        if (null == m_view){
            LogGen.instance().logerrf("setBoard m_view null "+m_id);
            return;
        }

        int icolor = TyperConvertor.convertUIColor(color);
        GradientDrawable gd = new GradientDrawable();
        gd.setColor(0x000000); // Changes this drawbale to use a single color instead of a gradient
        gd.setCornerRadius(0);
        gd.setStroke((int)width, icolor);
        m_view.setBackgroundDrawable(gd);
    }

    @Override
    public void setText(final String text) {
        if (null == m_view){
            LogGen.instance().logerrf("setText m_view null "+m_id);
            return;
        }
        if (m_view instanceof TextView){
            TextView label = (TextView)m_view;
            label.setText(text);
        }
        else if (m_view instanceof EditText){
            EditText edit = (EditText)m_view;
            edit.setText(text);
        }
        else  if (m_view instanceof Button){
            Button btn = (Button)m_view;
            btn.setText(text);
        }
        else
            LogGen.instance().logerrf("m_view can't setText");
    }

    @Override
    public String getText() {
        if (null == m_view){
            LogGen.instance().logerrf("getText m_view null "+m_id);
            return "";
        }

        if (m_view instanceof TextView){
            TextView label = (TextView)m_view;
            return label.getText().toString();
        }
        else if (m_view instanceof EditText){
            EditText edit = (EditText)m_view;
            return  edit.getText().toString();
        }
        else  if (m_view instanceof Button){
            Button btn = (Button)m_view;
            return btn.getText().toString();
        }
        LogGen.instance().logerrf("m_view can't getText");
        return "";
    }

    @Override
    public void setTextColor(ArgbColor color) {
        if (null == m_view){
            LogGen.instance().logerrf("setTextColor m_view null "+m_id);
            return;
        }

        if (m_view instanceof TextView){
            TextView label = (TextView)m_view;
            label.setTextColor(TyperConvertor.convertUIColor(color));
        }
        else if (m_view instanceof EditText){
            EditText edit = (EditText)m_view;
            edit.setTextColor(TyperConvertor.convertUIColor(color));
        }
        else  if (m_view instanceof Button){
            Button btn = (Button)m_view;
            btn.setTextColor(TyperConvertor.convertUIColor(color));
        }
        else
            LogGen.instance().logerrf("m_view can't setTextColor "+m_id);
    }

    @Override
    public void setFontSize(int size) {
        if (null == m_view){
            LogGen.instance().logerrf("setFontSize m_view null "+m_id);
            return;
        }

        if (m_view instanceof TextView){
            TextView label = (TextView)m_view;
            label.setTextSize(size);
        }
        else if (m_view instanceof EditText){
            EditText edit = (EditText)m_view;
            edit.setTextSize(size);
        }
        else  if (m_view instanceof Button){
            Button btn = (Button)m_view;
            btn.setTextSize(size);
        }
    }

    @Override
    public void setNumbernic(int type) {

    }

    @Override
    public void setMaxTextLen(int length) {
        if (m_view instanceof EditText){
            EditText edit = (EditText)m_view;
            edit.setFilters(new InputFilter[]{new InputFilter.LengthFilter(length)});
        }
    }

    @Override
    public ViewGen getSubView(String id) {

        if (null == m_view){
            LogGen.instance().logerrf("getSubView m_view null "+m_id);
            return null;
        }

        return m_subviews.get(id);
    }

    @Override
    public ViewGen addSubViewById(String id, ViewType type) {
        if (!(m_view instanceof ViewGroup)){
            LogGen.instance().logerrf("not viewgroup cant add view ");
            return null;
        }

        ViewImp view_imp = (ViewImp)ViewFactoryImp.instance.createViewById(id, type);
        //ViewImp view_imp = (ViewImp)UiManagerGen.instance().getView(id);
        if (null == view_imp){
            LogGen.instance().logerrf("addSubViewById createViewById null ");
            return null;
        }
        addSubView(view_imp);
        return view_imp;
    }

    @Override
    public ViewGen addSubView(ViewConf conf) {
        if (!(m_view instanceof ViewGroup)){
            LogGen.instance().logerrf("not viewgroup cant add view ");
            return null;
        }

        if (conf.getId() == m_id){
            LogGen.instance().logerrf("not addSubView can't add self");
            return null;
        }

        ViewImp view_imp = (ViewImp) ViewFactoryImp.instance.createView(conf);
        //ViewImp view_imp = (ViewImp) UiManagerGen.instance().getView(conf.getId());

        if (null == view_imp){
            return null;
        }

        addSubView(view_imp);
        return view_imp;
    }

    @Override
    public boolean removeSubView(String id) {
        if (!(m_view instanceof ViewGroup)) {
            LogGen.instance().logerrf("not viewgroup cant remove view ");
            return false;
        }

        ViewImp view = m_subviews.remove(id);
        if (null == view)
            return false;

        ((ViewGroup) m_view).removeView(view.getUIView());
        return  false;
    }

    @Override
    public void removeAllSubView() {
        if (!(m_view instanceof ViewGroup)) {
            LogGen.instance().logerrf("not viewgroup cant remove view ");
            return;
        }

        ((ViewGroup) m_view).removeAllViews();
    }

    @Override
    public void addConstraint(ViewConstraint constraint) {
        if (constraint!=null){
            return;
        }

        if (!(m_view instanceof ViewGroup)) {
            LogGen.instance().logerrf("not viewgroup cant add constraint");
            return;
        }

        ViewImp viewimp_from = m_subviews.get(constraint.getViewFrom());
        if (null == viewimp_from){
            LogGen.instance().logerrf("addConstraint viewfrom null");
            return;
        }
        View view_from = viewimp_from.getUIView();
        if (null == view_from){
            LogGen.instance().logerrf("addConstraint android viewfrom null");
            return;
        }

        View view_anchor = null;
        if (constraint.getViewTo().equals(ViewConstraint.SELF)){
            view_anchor = m_view;
        }
        else {
            ViewImp viewimp_anchor = m_subviews.get(constraint.getViewTo());
            if (null != viewimp_anchor){
                view_anchor = viewimp_anchor.getUIView();
            }
        }

        int rule = 0;
        RelativeLayout.LayoutParams lp = (RelativeLayout.LayoutParams)view_from.getLayoutParams();
        if (lp == null){
            LogGen.instance().logerrf("addConstraint layoutparams not RelativeLayout's null "+constraint.toString());
            return;
        }

        if (constraint.getType() == ConstraintType.WIDTH || constraint.getType() == ConstraintType.HEIGHT){
            if (constraint.getTypeTo() == ConstraintType.WIDTH && constraint.getMultiplier()==1
                    && constraint.getOffset() == 0 && view_anchor == m_view){
                lp.width = MATCH_PARENT;
            }
            else if (constraint.getTypeTo() == ConstraintType.HEIGHT && constraint.getMultiplier()==1
                    && constraint.getOffset() == 0 && view_anchor == m_view){
                lp.height = MATCH_PARENT;
            }
            else {
                m_sizing_constraints.add(constraint);
                return;
            }

        }

        if (null == view_anchor){
            LogGen.instance().logerrf("addConstraint android viewto null not size"+constraint.toString());
            return;
        }

        if (constraint.getType() == ConstraintType.TOP && constraint.getTypeTo() == ConstraintType.BOTTOM){
            rule = RelativeLayout.BELOW;
            lp.addRule(rule, view_anchor.getId());
            lp.setMargins(lp.leftMargin, (int)constraint.getOffset(),lp.rightMargin, lp.bottomMargin);
        }
        else if (constraint.getType() == ConstraintType.TOP && constraint.getTypeTo() == ConstraintType.TOP) {
            rule = RelativeLayout.ALIGN_TOP;
            lp.addRule(rule, view_anchor.getId());
            lp.setMargins(lp.leftMargin, (int)constraint.getOffset(),lp.rightMargin, lp.bottomMargin);
        }
        else if (constraint.getType() == ConstraintType.BOTTOM && constraint.getTypeTo() == ConstraintType.BOTTOM){
            rule = RelativeLayout.ALIGN_BOTTOM;
            lp.addRule(rule, view_anchor.getId());
            lp.setMargins(lp.leftMargin, lp.topMargin,lp.rightMargin, (int)constraint.getOffset());
        }
        else if (constraint.getType() == ConstraintType.LEADING && constraint.getTypeTo() == ConstraintType.LEADING) {
            rule = RelativeLayout.ALIGN_LEFT;
            lp.addRule(rule, view_anchor.getId());
            lp.setMargins((int)constraint.getOffset(), lp.topMargin,lp.rightMargin, lp.bottomMargin);
        }
        else if (constraint.getType() == ConstraintType.LEADING && constraint.getTypeTo() == ConstraintType.TRAILING) {
            rule = RelativeLayout.RIGHT_OF;
            lp.addRule(rule, view_anchor.getId());
            lp.setMargins((int)constraint.getOffset(), lp.topMargin,lp.rightMargin, lp.bottomMargin);
        }
        else if (constraint.getType() == ConstraintType.TRAILING && constraint.getTypeTo() == ConstraintType.LEADING) {
            rule = RelativeLayout.LEFT_OF;
            lp.addRule(rule, view_anchor.getId());
            lp.setMargins(lp.leftMargin, (int)constraint.getOffset(),lp.rightMargin, lp.bottomMargin);
        }
        else if (constraint.getType() == ConstraintType.TRAILING && constraint.getTypeTo() == ConstraintType.TRAILING) {
            rule = RelativeLayout.ALIGN_END;
            lp.addRule(rule, view_anchor.getId());
            lp.setMargins(lp.leftMargin, (int)constraint.getOffset(),lp.rightMargin, lp.bottomMargin);
        }
        else if (constraint.getType() == ConstraintType.BOTTOM && constraint.getTypeTo() == ConstraintType.TOP) {
            rule = RelativeLayout.ABOVE;
            lp.addRule(rule, view_anchor.getId());
            lp.setMargins(lp.leftMargin, lp.topMargin,lp.rightMargin, (int)constraint.getOffset());
        }
        else if (constraint.getType() == ConstraintType.BOTTOM && constraint.getTypeTo() == ConstraintType.BOTTOM) {
            rule = RelativeLayout.ALIGN_BOTTOM;
            lp.addRule(rule, view_anchor.getId());
            lp.setMargins(lp.leftMargin, lp.topMargin,lp.rightMargin, (int)constraint.getOffset());
        }
        else if (constraint.getType() == ConstraintType.CENTERX && constraint.getType() == ConstraintType.CENTERX && view_anchor == m_view){
            rule = RelativeLayout.CENTER_HORIZONTAL;
            lp.addRule(rule);
            //lp.setMargins(lp.leftMargin, lp.topMargin,lp.rightMargin, lp.bottomMargin);
        }
        else if (constraint.getType() == ConstraintType.CENTERY && constraint.getTypeTo() == ConstraintType.CENTERY && view_anchor == m_view) {
            rule = RelativeLayout.CENTER_HORIZONTAL;
            lp.addRule(rule);
            //lp.setMargins(lp.leftMargin, lp.topMargin,lp.rightMargin, lp.bottomMargin);
        }
        //else if (constraint.getType() == ConstraintType. && constraint.getTypeTo() == ConstraintType.) {
        //    rule = RelativeLayout
        //}
        else if (m_view == view_anchor){
            // align to parent's center, use a dummy in the center
            if (constraint.getTypeTo() == ConstraintType.CENTERX || constraint.getTypeTo() == ConstraintType.CENTERY){
                if (constraint.getTypeTo() == ConstraintType.CENTERX){
                    view_anchor = m_dummy_center;
                }

                if (constraint.getType() == ConstraintType.LEADING){
                    rule = RelativeLayout.RIGHT_OF;
                    lp.setMargins((int)constraint.getOffset(), lp.topMargin,lp.rightMargin, lp.bottomMargin);
                }
                else if (constraint.getType() == ConstraintType.TRAILING){
                    rule = RelativeLayout.LEFT_OF;
                    lp.setMargins(lp.leftMargin, lp.rightMargin,(int)constraint.getOffset(), lp.bottomMargin);
                }
                else if (constraint.getType() == ConstraintType.TOP){
                    rule = RelativeLayout.BELOW;
                    lp.setMargins(lp.leftMargin, (int)constraint.getOffset(),lp.rightMargin, lp.bottomMargin);
                }
                else if (constraint.getType() == ConstraintType.BOTTOM){
                    rule = RelativeLayout.ABOVE;
                    lp.setMargins(lp.leftMargin, lp.topMargin,lp.rightMargin, (int)constraint.getOffset());
                }

                lp.addRule(rule, view_anchor.getId());
            }

        }

        view_from.setLayoutParams(lp);
    }

    @Override
    public void setEventHandler(ViewEvent event, ViewEventHandler handler) {

        if (event==ViewEvent.TEXTCHANGE && m_view instanceof EditText){
            ((EditText) m_view).addTextChangedListener(new GBTextWatcher(this));
        }
        else if (event==ViewEvent.TAP)
            m_view.setOnClickListener(new ViewTapListener(this));

        m_handler.put(event,handler);
    }

    public View getUIView(){
        return m_view;
    }

    public int getAndroidId(){
        if (null == m_view){
            LogGen.instance().logerrf("getAndroidId m_view null "+m_id);
            return -1;
        }
        return m_view.getId();
    }

    public ViewImp(String id, View view){
        m_id = id;
        m_view = view;

        /*if (view instanceof ViewGroup){
            m_dummy_center = new Space(utils.getCurActivity());
            RelativeLayout.LayoutParams lp = new RelativeLayout.LayoutParams(0,0);
            lp.addRule(RelativeLayout.CENTER_IN_PARENT);
            m_dummy_center.setLayoutParams(lp);

            ViewGroup group = (ViewGroup)view;
            group.addView(m_dummy_center, lp);

            ViewTreeObserver vto = group.getViewTreeObserver();
            vto.addOnGlobalLayoutListener(m_layout_listener);
        }*/
    }

    private boolean addSubView(ViewImp view_imp){
        if (!(m_view instanceof ViewGroup)) {
            LogGen.instance().logerrf("not viewgroup cant add constraint");
            return false;
        }

        //((ViewGroup) m_view).addView(view_imp.getUIView());
        m_subviews.put(view_imp.getId(), view_imp);
        //UiManagerGen.instance().addView(view_imp);
        return true;
    }

    private ViewTreeObserver.OnGlobalLayoutListener m_layout_listener = new ViewTreeObserver.OnGlobalLayoutListener() {

        @Override
        public void onGlobalLayout() {
            for (ViewConstraint constraint: m_sizing_constraints){
                View view = utils.getAndroidView(constraint.getViewFrom());
                if (null == view){
                    LogGen.instance().logerrf("onGlobalLayout viewfrom android view null");
                    continue;
                }

                int anchor_width = 0;
                int anchor_height = 0;
                View view_anchor = null;
                if (constraint.getViewTo().equals(ViewConstraint.SELF)){
                    view_anchor = m_view;
                }
                else {
                    view_anchor = utils.getAndroidView(constraint.getViewTo());
                }

                if (null != view_anchor){
                    anchor_width = view_anchor.getWidth();
                    anchor_height = view_anchor.getHeight();
                }

                if (constraint.getType() == ConstraintType.HEIGHT){
                    view.getLayoutParams().height = (int)(anchor_height*constraint.getMultiplier()+constraint.getOffset());
                }else if (constraint.getType() == ConstraintType.WIDTH){
                    view.getLayoutParams().width = (int)(anchor_width*constraint.getMultiplier()+constraint.getOffset());
                }
                LogGen.instance().logerrf(String.format("%s %s view width:%d height:%d anchor width:%d height:%d",
                        constraint.getViewFrom(),constraint.getType().toString(),view.getLayoutParams().width,
                                                    view.getLayoutParams().height,anchor_width,anchor_height));
            }
            m_sizing_constraints.clear();
        }
    };

    private String m_id;
    private View m_view;
    private View m_dummy_center;
    private Map<String, ViewImp> m_subviews = new HashMap<String, ViewImp>();
    private List<ViewConstraint> m_sizing_constraints = new ArrayList<ViewConstraint>();
    private Map<ViewEvent, ViewEventHandler> m_handler = new HashMap<>();

    class ViewImpKeeper{
        ViewImpKeeper(ViewImp view_imp){
            m_viewimp = view_imp;
        }

        private ViewImp m_viewimp;
    }

    class ViewTapListener extends ViewImpKeeper implements View.OnClickListener {

        ViewTapListener(ViewImp view_imp) {
            super(view_imp);
        }

        @Override
        public void onClick(View v) {
            if (m_handler.get(ViewEvent.TAP)!=null)
                m_handler.get(ViewEvent.TAP).handle(new ViewEventParam(0,0, ViewEvent.TAP, ViewImp.this.getId()), ViewImp.this);
        }
    }

    class GBTextWatcher extends ViewImpKeeper implements TextWatcher {
        public GBTextWatcher(ViewImp view_imp){
            super(view_imp);
            m_view_imp = view_imp;
        }
        @Override
        public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
        @Override
        public void afterTextChanged(Editable s) {}

        @Override
        public void onTextChanged(CharSequence s, int start, int before, int count) {
            m_handler.get(ViewEvent.TEXTCHANGE).handle(new ViewEventParam(0,0, ViewEvent.TEXTCHANGE,s.toString()),m_view_imp);
        }

        ViewImp m_view_imp;
    }
}

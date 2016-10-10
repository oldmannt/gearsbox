//
//  GBViewImp.swift
//  gearsbox
//
//  Created by dyno on 5/26/16.
//
//

import Foundation
import UIKit

open
class GBViewImp: GBViewGen {
    fileprivate var m_id: String!
    fileprivate var m_view: UIView!
    fileprivate var m_controller:UIViewController?
    fileprivate var m_subView:[String:GBViewImp] = [:]
    fileprivate var m_event_handler:[GBViewEvent:GBViewEventHandler] = [:]
    fileprivate var m_edit_delegates:EditDelegate?
    
    public init(id: String, view: UIView){
        m_id = id
        m_view = view
    }
    
    public init(id: String, view: UIView, constroller:UIViewController){
        m_id = id
        m_view = view
        m_controller = constroller
    }
    
    @objc open func getId() -> String{
        return m_id;
    }
    
    @objc open func setFrame(_ frame: GBViewFrame){
        m_view.frame = CGRect(origin: CGPoint(x: CGFloat(frame.x), y: CGFloat(frame.y)),
               size: CGSize(width: CGFloat(frame.w), height: CGFloat(frame.h)))
    }
    
    @objc open func getFrame() -> GBViewFrame{
        let frame:GBViewFrame = GBViewFrame(
            x:Float(m_view.frame.origin.x),
            y:Float(m_view.frame.origin.y),
            w:Float(m_view.frame.size.width),
            h:Float(m_view.frame.size.height))
        
        return frame;
    }
    
    @objc open func setBackgroundColor(_ a: Float, r: Float, g: Float, b: Float){
        m_view.backgroundColor = UIColor(colorLiteralRed: r, green: g, blue: b, alpha: a)
    }
    
    @objc open func getType() -> GBViewType{
        if m_view is UILabel {
            return GBViewType.label
        }
        else if m_view is UITextField{
            return GBViewType.input
        }
        else{
            return GBViewType.base
        }
    }
    
    
    @objc open func setBoard(_ width: Float, color: GBArgbColor){
        m_view.layer.borderWidth = CGFloat(width)
        m_view.layer.borderColor = GBTyperConvertor.convertUIColor(color)
    }
    
    @objc open func setText(_ text: String) {
        if let label = m_view as? UILabel {
            label.text = text
        }
        else if let text_view = m_view as? UITextField {
            text_view.text = text
        }
    }
    
    @objc open func getText() -> String{
        if let label = m_view as? UILabel {
            return label.text!
        }
        else if let text_view = m_view as? UITextField {
            return  text_view.text!
        }
        GBLogGen.instance()?.logerrf("m_view \(type(of: m_view)) ")
        return ""
    }
    
    @objc open func setTextColor(_ color: GBArgbColor){
        if let label = m_view as? UILabel {
            label.textColor = GBTyperConvertor.convertUIColor(color)
        }
        else if let text_view = m_view as? UITextField {
            text_view.textColor = GBTyperConvertor.convertUIColor(color)
        }
    }
    
    @objc open func setFontSize(_ size: Int32){
        if let label = m_view as? UILabel {
            //label.font.fontWithSize(CGFloat(size));
            label.font = UIFont.systemFont(ofSize: CGFloat(size))
        }
        else if let text_view = m_view as? UITextField {
            text_view.font!.withSize(CGFloat(size));
        }
    }
    
    @objc open func setNumbernic(_ type:Int32){
        if nil == getEdit(){
            return
        }
        
        let edit:UITextField = getEdit()!
        if nil == m_edit_delegates {
            m_edit_delegates = EditDelegate(edt: edit)
            edit.delegate = m_edit_delegates
        }
        
        m_edit_delegates?.addDelegates(NumInputDelegate(edt: edit))
    }
    
    @objc open func setMaxTextLen(_ length:Int32){
        if nil == getEdit(){
            return
        }
        
        let edit:UITextField = getEdit()!
        if nil == m_edit_delegates {
            m_edit_delegates = EditDelegate(edt: edit)
        }

        m_edit_delegates?.addDelegates(EditMaxLength(edt:edit, length: Int(length)))
    }
    
    @objc open func setVisiable(_ v: Bool){
        m_view.isHidden = !v
    }
    
    @objc open func becomeFirstResponder(){
        m_view.becomeFirstResponder()
    }
    
    @objc open func getSubView(_ id: String) -> GBViewGen?{
        return m_subView[id]
    }
    
    @objc open func addSubView(byId id: String, type:GBViewType) -> GBViewGen?{
        if m_subView[id] != nil {
            GBLogGen.instance()?.logerrf("addSubViewById failed aready exist id: \(id) \(#file) \(#function) \(#line) ")
            return nil;
        }
        
        if id == m_id {
            GBLogGen.instance()?.logerrf("addSubViewById failed this parent id: \(id) \(#file) \(#function) \(#line) ")
            return nil;
        }
        
        let view_gen:GBViewImp? = GBViewFactoryImp.instance.createView(byId: id, type: type) as? GBViewImp;
        if (nil == view_gen){
            return nil
        }

        addSubView(view_gen!)
        return view_gen
    }
    
    @objc open func addSubView(_ conf: GBViewConf) -> GBViewGen?{
        if m_subView[conf.id] != nil {
            GBLogGen.instance()?.logerrf("addView failed aready exist id: \(conf.id) \(#file) \(#function) \(#line) ")
            return nil;
        }
        
        if conf.id == m_id {
            GBLogGen.instance()?.logerrf("addView failed this parent id: \(conf.id) \(#file) \(#function) \(#line) ")
            return nil;
        }
        
        let view_gen:GBViewImp? = GBViewFactoryImp.instance.createView(conf) as? GBViewImp;
        if (nil == view_gen){
            return nil
        }
        
        addSubView(view_gen!)
        return view_gen
    }
    
    fileprivate func addSubView(_ subview:GBViewImp)->Bool{
        m_view.addSubview(subview.getUIView())
        subview.setUIViewController(m_controller!)
        m_subView[subview.getId()] = subview
        GBUiManagerGen.instance()?.addView(subview)
        return true;
    }

    @objc open func removeSubView(_ id: String) -> Bool{
        if !removeSubViewImp(id){
            return false
        }
        m_subView.removeValue(forKey: id)
        return true
    }
    
    @objc open func removeAllSubView(){
        for (id, _) in m_subView{
            removeSubViewImp(id)
        }
        m_subView.removeAll()
    }
    
    @objc open func add(_ constraint: GBViewConstraint){
        //let typestr = ["None    ","Leading ","Trailing","Top     ","Bottom  ","Width   ","Height  ","CenterX ","CenterY "]
        //print("constraint: viewFrome:\(constraint.viewFrom) viewTo:\(constraint.viewTo) type:\(typestr[constraint.type.rawValue]) typeTo:\(typestr[constraint.typeTo.rawValue]) multiplier:\(constraint.multiplier) offset:\(constraint.offset)")
        
        let view:GBViewImp? = m_subView[constraint.viewFrom]
        if view == nil{
            GBLogGen.instance()?.logerrf("viewFrome nil in view id:\(getId())\(#file) \(#function) \(#line) ")
            return
        }
        
        var toview:GBViewImp?
        if GBViewConstraintSelf == constraint.viewTo{
            toview = self
        }else{
            toview = m_subView[constraint.viewTo]
        }
        
        let ios_view1:UIView = (view?.getUIView())!
        let ios_toview:UIView? = (toview != nil) ? (toview!.getUIView()) : nil
        
        let multi:CGFloat = CGFloat(constraint.multiplier)
        let offset:CGFloat = CGFloat(constraint.offset)
        let attr:NSLayoutAttribute = GBTyperConvertor.convertUIConstraintType(constraint.type)
        var toattr:NSLayoutAttribute = GBTyperConvertor.convertUIConstraintType(constraint.typeTo)
        if nil == toview{
            toattr = NSLayoutAttribute.notAnAttribute
        }
        
        if attr == NSLayoutAttribute.notAnAttribute {
            GBLogGen.instance()?.logerrf("GBConstraintType err type:\(constraint.type) toype:\(constraint.typeTo)\(#file) \(#function) \(#line) ")
            return
        }
        
        view!.getUIView().translatesAutoresizingMaskIntoConstraints = false
        m_view.addConstraint(NSLayoutConstraint(item: ios_view1, attribute: attr, relatedBy: .equal,
            toItem: ios_toview, attribute: toattr, multiplier: multi, constant: offset))

    }
    
    @objc open func setEventHandler(_ event:GBViewEvent, handler: GBViewEventHandler?){
        let recognizer = UITapGestureRecognizer(target: self, action:#selector(GBViewImp.tapEvent(_:)))
        m_view.addGestureRecognizer(recognizer)
        
        if m_view is UIControl{
            let ctrl:UIControl = m_view as! UIControl;
            ctrl.addTarget(self, action: #selector(GBViewImp.textChange(_:)), for: UIControlEvents.editingChanged)
        }
        m_event_handler[event] = handler;
    }
    
    @objc internal func tapEvent(_ sender:UIGestureRecognizer){
        if nil == m_event_handler[GBViewEvent.tap] {
            return
        }
        let point:CGPoint = sender.location(in: sender.view)
        let param:GBViewEventParam = GBViewEventParam(x: Float(point.x), y: Float(point.y),type: GBViewEvent.tap, text: "")
        
        m_event_handler[GBViewEvent.tap]!.handle(param, view: self)
    }
    
    @objc internal func textChange(_ sender: UITextField){
        if nil == m_event_handler[GBViewEvent.textChange] {
            return
        }
        
        let param:GBViewEventParam = GBViewEventParam(x: 0,y: 0,type: GBViewEvent.textChange, text: sender.text!)
        m_event_handler[GBViewEvent.textChange]!.handle(param, view: self)
    }
    
    internal func getDelegate() -> EditDelegate?{return m_edit_delegates}
    internal func getUIView() -> UIView{
        return m_view
    }
    
    internal func setUIViewController(_ controller:UIViewController){
        m_controller = controller
    }
    
    fileprivate func removeSubViewImp(_ id:String) -> Bool{
        let view_gen:GBViewImp? = m_subView[id]
        if view_gen == nil{
            GBLogGen.instance()?.logerrf("nothing to remove \(#file) \(#function) \(#line) ")
            return false
        }
        
        view_gen?.getUIView().removeFromSuperview()
        GBUiManagerGen.instance()?.removeView(id)
        return true
    }
    
    fileprivate func getLabel() -> UILabel?{
        let label = m_view as? UILabel
        return label
    }
    
    fileprivate func getEdit() -> UITextField?{
        let edit = m_view as? UITextField
        return edit

    }
    
}

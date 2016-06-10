//
//  GBViewImp.swift
//  gearsbox
//
//  Created by dyno on 5/26/16.
//
//

import Foundation
import UIKit

public
class GBViewImp: GBViewGen {
    private var m_id: String!
    private var m_view: UIView!
    private var m_controller:UIViewController?
    private var m_subView:[String:GBViewImp] = [:]
    private var m_handler:GBViewEventHandler?
    
    public init(id: String, view: UIView){
        m_id = id
        m_view = view
    }
    
    public init(id: String, view: UIView, constroller:UIViewController){
        m_id = id
        m_view = view
        m_controller = constroller
    }
    
    @objc public func getId() -> String{
        return m_id;
    }
    
    @objc public func setFrame(frame: GBViewFrame){
        m_view.frame = CGRect(origin: CGPoint(x: CGFloat(frame.x), y: CGFloat(frame.y)),
               size: CGSize(width: CGFloat(frame.w), height: CGFloat(frame.h)))
    }
    
    @objc public func getFrame() -> GBViewFrame{
        let frame:GBViewFrame = GBViewFrame(
            x:Float(m_view.frame.origin.x),
            y:Float(m_view.frame.origin.y),
            w:Float(m_view.frame.size.width),
            h:Float(m_view.frame.size.height))
        
        return frame;
    }
    
    @objc public func setBackgroundColor(a: Float, r: Float, g: Float, b: Float){
        m_view.backgroundColor = UIColor(colorLiteralRed: r, green: g, blue: b, alpha: a)
    }
    
    @objc public func getType() -> GBViewType{
        if m_view is UILabel {
            return GBViewType.Label
        }
        else if m_view is UITextField{
            return GBViewType.Input
        }
        else{
            return GBViewType.Base
        }
    }
    
    @objc public func setBoardColor(color: GBArgbColor){
        m_view.layer.borderColor = GBTyperConvertor.convertUIColor(color)
    }
    
    @objc public func setBoardWidth(width: Float){
        m_view.layer.borderWidth = CGFloat(width)
    }
    
    @objc public func setVisiable(v: Bool){
        m_view.hidden = !v
    }
    
    @objc public func getSubView(id: String) -> GBViewGen?{
        for (view_id,view_gen) in m_subView {
            if id == view_id {
                return view_gen
            }
        }
        GBLogGen.instance()?.logerrf("get sub view nil \(#file) \(#function) \(#line) ")
        return nil
    }
    
    @objc public func addSubViewById(id: String) -> GBViewGen?{
        let view_conf:GBViewConf = (GBUiConfGen.instance()?.getViewConf(id))!
        if view_conf.id != id {
            GBLogGen.instance()?.logerrf("add subview failed can't find ViewConf id:\(id) \(#file) \(#function) \(#line) ")
            return nil
        }

        return addSubView(view_conf)
    }
    
    @objc public func addSubView(conf: GBViewConf) -> GBViewGen?{
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
        
        m_view.addSubview(view_gen!.getUIView())
        view_gen?.setUIViewController(m_controller!)
        m_subView[conf.id] = view_gen
        return view_gen
    }
    
    
    
    @objc public func removeSubView(id: String) -> Bool{
        if !removeSubViewImp(id){
            return false
        }
        m_subView.removeValueForKey(id)
        return true
    }
    
    @objc public func removeAllSubView(){
        for (id, _) in m_subView{
            removeSubViewImp(id)
        }
        m_subView.removeAll()
    }
    
    @objc public func addConstraint(constraint: GBViewConstraint){
        let typestr = ["None    ","Leading ","Trailing","Top     ","Bottom  ","Width   ","Height  ","CenterX ","CenterY "]
        print("constraint: viewFrome:\(constraint.viewFrom) viewTo:\(constraint.viewTo) type:\(typestr[constraint.type.rawValue]) typeTo:\(typestr[constraint.typeTo.rawValue]) multiplier:\(constraint.multiplier) offset:\(constraint.offset)")
        
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
            toattr = NSLayoutAttribute.NotAnAttribute
        }
        
        if attr == NSLayoutAttribute.NotAnAttribute {
            GBLogGen.instance()?.logerrf("GBConstraintType err type:\(constraint.type) toype:\(constraint.typeTo)\(#file) \(#function) \(#line) ")
            return
        }
        
        view!.getUIView().translatesAutoresizingMaskIntoConstraints = false
        m_view.addConstraint(NSLayoutConstraint(item: ios_view1, attribute: attr, relatedBy: .Equal,
            toItem: ios_toview, attribute: toattr, multiplier: multi, constant: offset))

    }
    
    @objc public func setEventHandler(handler: GBViewEventHandler?){
        let recognizer = UITapGestureRecognizer(target: self, action:#selector(GBViewImp.tapEvent(_:)))
        m_view.addGestureRecognizer(recognizer)
        
        if m_view is UIControl{
            let ctrl:UIControl = m_view as! UIControl;
            ctrl.addTarget(self, action: #selector(GBViewImp.textChange(_:)), forControlEvents: UIControlEvents.EditingChanged)
        }
        m_handler = handler;
    }
    
    @objc internal func tapEvent(sender:UIGestureRecognizer){
        if nil == m_handler {
            return
        }
        let point:CGPoint = sender.locationInView(sender.view)
        let param:GBViewEventParam = GBViewEventParam(x: Float(point.x), y: Float(point.y),type: GBViewEvent.Tap, text: "")
        
        m_handler!.handle(param, view: self)
    }
    
    @objc internal func textChange(sender: UITextField){
        if nil == m_handler {
            return
        }
        
        let param:GBViewEventParam = GBViewEventParam(x: 0,y: 0,type: GBViewEvent.TextChange, text: sender.text!)
        m_handler!.handle(param, view: self)
    }
    
    internal func getUIView() -> UIView{
        return m_view
    }
    
    internal func setUIViewController(controller:UIViewController){
        m_controller = controller
    }
    
    private func removeSubViewImp(id:String) -> Bool{
        let view_gen:GBViewImp? = m_subView[id]
        if view_gen == nil{
            GBLogGen.instance()?.logerrf("nothing to remove \(#file) \(#function) \(#line) ")
            return false
        }
        
        view_gen?.getUIView().removeFromSuperview()
        GBUiManagerGen.instance()?.removeView(id)
        return true
    }
    
    
}
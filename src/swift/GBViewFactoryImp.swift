//
//  GBViewFactoryImp.swift
//  usnit_app
//
//  Created by dyno on 5/27/16.
//  Copyright © 2016 dyno. All rights reserved.
//

import Foundation
import UIKit

class GBViewFactoryImp: GBViewFactoryGen {
    
    static let instance = GBViewFactoryImp()
    @objc internal func injectView(_ view: GBViewGen?) -> Bool{
        if view == nil {
            GBLogGen.instance()?.logerrf("param view nil \(#file) \(#function) \(#line) ")
            return false
        }
        
        let view_imp:GBViewImp? = view! as? GBViewImp;
        if (nil == view_imp){
            GBLogGen.instance()?.logerrf("case view failed id:\(view!.getId()) \(#file) \(#function) \(#line) ")
        }

        let view_conf:GBViewConf = (GBUiConfGen.instance()?.getViewConf(view!.getId()))!
        if view_conf.id != view!.getId() {
            GBLogGen.instance()?.logerrf("create failed can't find ViewConf id:\(view!.getId()) \(#file) \(#function) \(#line) ")
            return false
        }
        
        if (!confView(view_imp!, conf: view_conf)){
            return false;
        }
        
        GBUiManagerGen.instance()?.addView(view_imp);
        return true;
    }
    
    @objc internal func createView(_ conf: GBViewConf) -> GBViewGen?{
        if ((GBUiManagerGen.instance()?.getView(conf.id)) != nil){
            GBLogGen.instance()?.logerrf("create failed already in manager id:\(conf.id) \(#file) \(#function) \(#line) ")
            return nil
        }

        let ios_view:UIView? = createView(conf);
        if (nil == ios_view){
            return nil
        }
        
        let view_imp:GBViewImp = GBViewImp(id: conf.id, view:ios_view!)
        confiView(view_imp, conf: conf)
        createSubViews(view_imp, subviews: conf.subviews)
        createConstraints(view_imp, constraints: conf.constraints)
        return view_imp
    }
    
    @objc internal func createView(byId id: String, type:GBViewType) -> GBViewGen?{
        var view_conf:GBViewConf = (GBUiConfGen.instance()?.getViewConf(id))!
        if view_conf.id != id {
            view_conf = createViewConf(id, type: type)
        }

        return createView(view_conf)
    }
    
    @objc internal func showViewController(_ id: String, animated: Bool){
        let current_vc = UIApplication.shared.keyWindow?.rootViewController
        if nil==current_vc{
            GBLogGen.instance()?.logerrf("showViewController current_vc null")
            return
        }
        
        let next_vc = current_vc?.storyboard?.instantiateViewController(withIdentifier: id)
        current_vc?.present(next_vc!, animated: false, completion: nil)
    }
    
    internal func addIOSViewToUIMgr(_ view:UIView, id:String, constroller: ViewController){
        let view_imp = GBViewImp(id:id, view: view, constroller: constroller)
        GBUiManagerGen.instance()?.addView(view_imp)
    }
    
    fileprivate func confView(_ view_imp: GBViewImp, conf:GBViewConf)->Bool{
        setBaseConf(view_imp, conf: conf)
        createSubViews(view_imp, subviews: conf.subviews)
        createConstraints(view_imp, constraints: conf.constraints)
        return true
    }
    
    fileprivate func createBase(_ conf:GBViewConf)->UIView{
        let ios_view = UIView();
        return ios_view;
    }
    
    fileprivate func createLabel(_ conf:GBViewConf)->UILabel{
        let label:UILabel = UILabel();
        label.numberOfLines = 0;
        return label;
    }
    
    fileprivate func createInput(_ conf:GBViewConf)->UITextField{
        let view:UITextField = UITextField()
        return view;
    }
    
    fileprivate func confiView(_ view_imp:GBViewImp, conf:GBViewConf){
        switch conf.type {
        case GBViewType.base:
            setBaseConf(view_imp, conf: conf)
            break
        case GBViewType.label:
            setLabelConf(view_imp, conf: conf)
            break
        case GBViewType.input:
            setInput(view_imp, conf: conf)
            break
        default:
            GBLogGen.instance()?.logerrf("unsupported type id:\(conf.id) type:\(conf.type) \(#file) \(#function) \(#line) ")
            break
        }
        
    }
    
    fileprivate func createView(_ view_conf:GBViewConf) -> UIView?{
        
        switch view_conf.type {
        case GBViewType.base:
            return createBase(view_conf)
        case GBViewType.label:
            return createLabel(view_conf)
        case GBViewType.input:
            return createInput(view_conf)
        default: break
        }
        
        GBLogGen.instance()?.logerrf("unsupported type id:\(view_conf.id) type:\(view_conf.type) \(#file) \(#function) \(#line) ")
        return nil
    }
       
    fileprivate func setLabelConf(_ label:GBViewImp, conf:GBViewConf){
        setBaseConf(label, conf: conf)
        let uiview:UILabel? = label.getUIView() as? UILabel
        if nil == uiview{
            return
        }
        if (conf.text.characters.count>0){
            uiview!.text = conf.text
        }
        //label.backgroundColor = UIColor.blackColor()
        //label.text = "12345678"
        //label.adjustsFontSizeToFitWidth = true;
        uiview!.isUserInteractionEnabled = true;
        
        if (conf.fontsize>0){
            uiview!.font = uiview!.font.withSize(CGFloat(conf.fontsize));
        }
        
        if (conf.textalign != GBTextAlign.none){
            uiview!.textAlignment = GBTyperConvertor.convertUITextAlign(conf.textalign)!
        }
    }
    
    fileprivate func setInput(_ input:GBViewImp, conf:GBViewConf){
        let uiview:UITextField? = input.getUIView() as? UITextField
        if nil == uiview{
            return
        }
        
        setBaseConf(input, conf: conf)
        if (conf.text.characters.count>0){
            uiview!.text = conf.text
        }
        if (GBUiValueCheckerGen.instance()?.isValidTextBoarder(conf.textboarder) == true){
            uiview!.borderStyle = GBTyperConvertor.convertUITextBoarder(conf.textboarder);
        }
        if (conf.keyboardtype != GBTextKeyboard.default){
            uiview!.keyboardType = GBTyperConvertor.convertKeyboardType(conf.keyboardtype)
        }
        if (conf.numericText){
            input.setNumbernic(GBViewGenNUMBERFLOAT)
        }
        if (conf.maxlength > 0){
            input.setMaxTextLen(conf.maxlength)
        }
    }
    
    fileprivate func createSubViews(_ view_imp:GBViewImp, subviews:[GBViewConf]){
        for sub_conf in subviews {
            view_imp.addSubView(sub_conf);
        }
    }
    
    fileprivate func createConstraints(_ view_imp:GBViewImp, constraints:[GBViewConstraint]){
        for constraint in constraints {
            view_imp.add(constraint)
        }
    }

    fileprivate func setBaseConf(_ view:GBViewImp, conf:GBViewConf)->Bool{
        let uiview:UIView = view.getUIView()
        uiview.accessibilityIdentifier = conf.id;

        if (GBUiValueCheckerGen.instance()?.isValidFrame(conf.frame) == true){
            uiview.frame = GBTyperConvertor.convertUIRect(conf.frame);
        }
        
        if (GBUiValueCheckerGen.instance()?.isValidColor(conf.bgcolor) == true){
            uiview.backgroundColor = GBTyperConvertor.convertUIColor(conf.bgcolor);
        }
        
        return true
    }
    

    fileprivate func createViewConf(_ id:String, type:GBViewType)->GBViewConf{
        let conf:GBViewConf = GBViewConf(id: id, type: type, frame: GBViewConf.noframe(),
                        bgcolor: GBViewConf.nogbcolor(), fontsize: -1, textalign: GBTextAlign.none,
                        textboarder: GBTextBoarder.none, text: "",
                        numericText: false, keyboardtype: GBTextKeyboard.default, maxlength: -1,
                        constraints: [GBViewConstraint](), subviews: [GBViewConf]())
        return conf
    }

}

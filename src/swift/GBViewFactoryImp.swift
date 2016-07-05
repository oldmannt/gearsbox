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
    @objc internal func injectView(view: GBViewGen?) -> Bool{
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
    
    @objc internal func createView(conf: GBViewConf) -> GBViewGen?{
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
    
    @objc internal func createViewById(id: String, type:GBViewType) -> GBViewGen?{
        var view_conf:GBViewConf = (GBUiConfGen.instance()?.getViewConf(id))!
        if view_conf.id != id {
            view_conf = createViewConf(id, type: type)
        }

        return createView(view_conf)
    }
    
    private func confView(view_imp: GBViewImp, conf:GBViewConf)->Bool{
        setBaseConf(view_imp, conf: conf)
        createSubViews(view_imp, subviews: conf.subviews)
        createConstraints(view_imp, constraints: conf.constraints)
        return true
    }
    
    private func createBase(conf:GBViewConf)->UIView{
        let ios_view = UIView();
        return ios_view;
    }
    
    private func createLabel(conf:GBViewConf)->UILabel{
        let label:UILabel = UILabel();
        return label;
    }
    
    private func createInput(conf:GBViewConf)->UITextField{
        let view:UITextField = UITextField()
        return view;
    }
    
    private func confiView(view_imp:GBViewImp, conf:GBViewConf){
        switch conf.type {
        case GBViewType.Base:
            setBaseConf(view_imp, conf: conf)
            break
        case GBViewType.Label:
            setLabelConf(view_imp, conf: conf)
            break
        case GBViewType.Input:
            setInput(view_imp, conf: conf)
            break
        default:
            GBLogGen.instance()?.logerrf("unsupported type id:\(conf.id) type:\(conf.type) \(#file) \(#function) \(#line) ")
            break
        }
        
    }
    
    private func createView(view_conf:GBViewConf) -> UIView?{
        
        switch view_conf.type {
        case GBViewType.Base:
            return createBase(view_conf)
        case GBViewType.Label:
            return createLabel(view_conf)
        case GBViewType.Input:
            return createInput(view_conf)
        default: break
        }
        
        GBLogGen.instance()?.logerrf("unsupported type id:\(view_conf.id) type:\(view_conf.type) \(#file) \(#function) \(#line) ")
        return nil
    }
       
    private func setLabelConf(label:GBViewImp, conf:GBViewConf){
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
        uiview!.userInteractionEnabled = true;
        
        if (conf.fontsize>0){
            uiview!.font = uiview!.font.fontWithSize(CGFloat(conf.fontsize));
        }
        
        if (conf.textalign != GBTextAlign.None){
            uiview!.textAlignment = GBTyperConvertor.convertUITextAlign(conf.textalign)!
        }
    }
    
    private func setInput(input:GBViewImp, conf:GBViewConf){
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
        if (conf.keyboardtype != GBTextKeyboard.Default){
            uiview!.keyboardType = GBTyperConvertor.convertKeyboardType(conf.keyboardtype)
        }
        if (conf.numericText){
            input.setNumbernic(GBViewGenNUMBERFLOAT)
        }
        if (conf.maxlength > 0){
            input.setMaxTextLen(conf.maxlength)
        }
    }
    
    private func createSubViews(view_imp:GBViewImp, subviews:[GBViewConf]){
        for sub_conf in subviews {
            view_imp.addSubView(sub_conf);
        }
    }
    
    private func createConstraints(view_imp:GBViewImp, constraints:[GBViewConstraint]){
        for constraint in constraints {
            view_imp.addConstraint(constraint)
        }
    }

    private func setBaseConf(view:GBViewImp, conf:GBViewConf)->Bool{
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
    

    private func createViewConf(id:String, type:GBViewType)->GBViewConf{
        let conf:GBViewConf = GBViewConf(id: id, type: type, frame: GBViewConf.noframe(),
                        bgcolor: GBViewConf.nogbcolor(), fontsize: -1, textalign: GBTextAlign.None,
                        textboarder: GBTextBoarder.None, text: "",
                        numericText: false, keyboardtype: GBTextKeyboard.Default, maxlength: -1,
                        constraints: [GBViewConstraint](), subviews: [GBViewConf]())
        return conf
    }

}

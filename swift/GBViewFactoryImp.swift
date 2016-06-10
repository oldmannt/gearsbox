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
        
        return confView(view_imp!, conf: view_conf);
        
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
        createSubViews(view_imp, subviews: conf.subviews)
        createConstraints(view_imp, constraints: conf.constraints)
        return view_imp
    }
    
    private func confView(view_imp: GBViewImp, conf:GBViewConf)->Bool{
        let ios_view:UIView = view_imp.getUIView()
        setBaseConf(ios_view, conf: conf)
        createSubViews(view_imp, subviews: conf.subviews)
        createConstraints(view_imp, constraints: conf.constraints)
        return true
    }
    
    private func createBase(conf:GBViewConf)->UIView{
        let ios_view = UIView();
        setBaseConf(ios_view, conf: conf);
        return ios_view;
    }
    
    private func createLabel(conf:GBViewConf)->UILabel{
        let label:UILabel = UILabel();
        setLabelConf(label, conf: conf);
        return label;
    }
    
    private func createInput(conf:GBViewConf)->UITextField{
        let view:UITextField = UITextField()
        setInput(view, conf: conf)
        return view;
    }
    
    private func createView(view_conf:GBViewConf) -> UIView?{
        
        switch view_conf.type {
        case GBViewType.Base:
            return createBase(view_conf);
        case GBViewType.Label:
            return createLabel(view_conf);
        case GBViewType.Input:
            return createInput(view_conf);
        default: break
        }
        
        GBLogGen.instance()?.logerrf("unsupported type id:\(view_conf.id) type:\(view_conf.type) \(#file) \(#function) \(#line) ")
        return nil
    }
    
    private func setLabelConf(label:UILabel, conf:GBViewConf){
        setBaseConf(label, conf: conf)
        if (conf.text.characters.count>0){
            label.text = conf.text
        }
        label.backgroundColor = UIColor.blackColor()
        label.text = "12345678"
        
        if (conf.fontsize>0){
            label.font = label.font.fontWithSize(CGFloat(conf.fontsize));
        }
    }
    
    private func setInput(input:UITextField, conf:GBViewConf){
        setBaseConf(input, conf: conf)
        if (conf.text.characters.count>0){
            input.text = conf.text
        }
        if (GBUiValueCheckerGen.instance()?.isValidTextBoarder(conf.textboarder) == true){
            input.borderStyle = GBTyperConvertor.convertUITextBoarder(conf.textboarder);
        }
    }
    
    private func createSubViews(view_imp:GBViewImp, subviews:[String: GBViewConf]){
        for (_, sub_conf) in subviews {
            view_imp.addSubView(sub_conf);
        }
    }
    
    private func createConstraints(view_imp:GBViewImp, constraints:[GBViewConstraint]){
        for constraint in constraints {
            view_imp.addConstraint(constraint)
        }
    }

    private func setBaseConf(view:UIView, conf:GBViewConf)->Bool{
        view.accessibilityIdentifier = conf.id;

        if (GBUiValueCheckerGen.instance()?.isValidFrame(conf.frame) == true){
            view.frame = GBTyperConvertor.convertUIRect(conf.frame);
        }
        
        if (GBUiValueCheckerGen.instance()?.isValidColor(conf.bgcolor) == true){
            view.backgroundColor = GBTyperConvertor.convertUIColor(conf.bgcolor);
        }
        
        return true
    }

}

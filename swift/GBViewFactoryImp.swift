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
    
    @objc internal func createView(id: String) -> GBViewGen?{
        if ((GBUiManagerGen.instance()?.getView(id)) != nil){
            GBLogGen.instance()?.logerrf("create failed already in manager id:\(id) \(#file) \(#function) \(#line) ")
            return nil
        }
        
        let view_conf:GBViewConf = (GBUiConfGen.instance()?.getViewConf(id))!
        if view_conf.id != id {
            GBLogGen.instance()?.logerrf("create failed can't find ViewConf id:\(id) \(#file) \(#function) \(#line) ")
            return nil
        }
        
        let ios_view:UIView? = createView(view_conf);
        if (nil == ios_view){
            return nil
        }
        
        let view_gen:GBViewImp = GBViewImp(id: id, view:ios_view!)
        return view_gen
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
            return createBase(view_conf);
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

    private func setBaseConf(view:UIView, conf:GBViewConf){
        view.accessibilityIdentifier = conf.id;

        if (GBUiValueCheckerGen.instance()?.isValidFrame(conf.frame) == true){
            view.frame = GBTyperConvertor.convertUIRect(conf.frame);
        }
        
        if (GBUiValueCheckerGen.instance()?.isValidColor(conf.bgcolor) == true){
            view.backgroundColor = GBTyperConvertor.convertUIColor(conf.bgcolor);
        }
    }

}

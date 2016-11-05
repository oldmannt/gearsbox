//
//  UIButtonBottomTittle.swift
//  lapse_app
//
//  Created by dyno on 9/29/16.
//  Copyright © 2016 dyno. All rights reserved.
//

import UIKit

class UIButtonBottomTittle: UIButton {
    override func layoutSubviews() {
        super.layoutSubviews()
        
        if self.imageView == nil || self.titleLabel == nil {
            return
        }
        
        let btn_h = self.frame.size.height
        let img_size = (self.imageView?.image?.size)!
        self.imageView?.frame = CGRect(origin: (self.imageView?.frame.origin)!, size: img_size)
        
        let img_h = self.imageView?.frame.size.height
        let lab_h = self.titleLabel?.frame.size.height
        
        self.imageView?.center.x = self.center.x
        self.imageView?.frame.origin.y = btn_h - img_h! - lab_h!
        
        self.titleLabel?.sizeToFit()
        self.titleLabel?.center.x = self.center.x
        self.titleLabel?.frame.origin.y = btn_h - lab_h!
    }
}

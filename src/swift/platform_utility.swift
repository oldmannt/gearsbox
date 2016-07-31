//
//  platform_excutor.swift
//  usnit_app
//
//  Created by dyno on 6/12/16.
//  Copyright © 2016 dyno. All rights reserved.
//

import Foundation
import UIKit

public class GBPlatformUtilityImp: GBPlatformUtilityGen {
    
    @objc public func endEniting(force: Bool){
        UIApplication.sharedApplication().keyWindow?.endEditing(force)
    }
    
    @objc public func getRootDirectory() -> String {
        return NSSearchPathForDirectoriesInDomains(.DocumentDirectory, .UserDomainMask, true)[0] as String
    }
    
    @objc public func getPackFilePath(file: String) -> String {
        let rt = NSBundle.mainBundle().pathForResource(file, ofType: "")
        return rt == nil ? "" : rt!
    }
}

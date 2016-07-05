//
//  platform_excutor.swift
//  usnit_app
//
//  Created by dyno on 6/12/16.
//  Copyright © 2016 dyno. All rights reserved.
//

import Foundation
import UIKit

class IOSExecutor: GBPlatformExecutorGen {
    
    @objc internal func endEniting(force: Bool){
        UIApplication.sharedApplication().keyWindow?.endEditing(force)
    }
}

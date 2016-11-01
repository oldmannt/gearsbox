//
//  GBDeviceImp.swift
//  lapse_app
//
//  Created by dyno on 10/31/16.
//  Copyright © 2016 dyno. All rights reserved.
//

import Foundation
import UIKit

open class GBDeviceImp : NSObject, GBDeviceGen {
    static let sharedInstance = GBDeviceImp()
    private override init() {
        
    }
    
    public func getOrientation() -> GBDeviceOrientation{
        return toGBDeviceOrientation(ori: UIDevice.current.orientation)
    }
    
    private func toGBDeviceOrientation(ori:UIDeviceOrientation) -> GBDeviceOrientation{
        switch ori {
        case .unknown:
            return GBDeviceOrientation.unknown
        case .portrait:
            return GBDeviceOrientation.portrait
        case .portraitUpsideDown:
            return GBDeviceOrientation.protraitDown
        case .landscapeLeft:
            return GBDeviceOrientation.landscapeLeft
        case .landscapeRight:
            return GBDeviceOrientation.landscapeRight
        case .faceUp:
            return GBDeviceOrientation.faceup
        case .faceDown:
            return GBDeviceOrientation.facedown
        }
    }
}

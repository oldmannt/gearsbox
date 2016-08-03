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
    
    /**ios home directory */
    @objc public func getHomeDirectory() -> String {
        return NSSearchPathForDirectoriesInDomains(.DocumentDirectory, .UserDomainMask, true)[0] as String
    }
    
    @objc public func getPackFilePath(file: String) -> String {
        let rt = NSBundle.mainBundle().pathForResource(file, ofType: "")
        if rt == nil {
            GBLogGen.instance()?.logerrf("getPackFilePath \(file) failed")
            return ""
        }
        return rt!
    }
    
    @objc public func getPackFileBuffer(file: String) -> String{
        let pack_path = getPackFilePath(file)
        if pack_path==""{
            return ""
        }
        
        var buffer:String = "";
        do {
            buffer = try NSString(contentsOfFile: pack_path, usedEncoding: nil) as String
        } catch let error as NSError{
            // contents could not be loaded
            GBLogGen.instance()?.logerrf("SFUsnitLogic.load_conf read \(pack_path) \(error.userInfo) load \(file) failed")
            return ""
        }
        
        return buffer
    }
    
    /**copy pack file to home directory and return path in home directory */
    @objc public func getPackFileToHomePath(file: String) -> String{
        let buffer = getPackFileBuffer(file)
        if buffer==""{
            return ""
        }
        
        let doc_path = getHomeDirectory()+"/\(file)"
        do {
            try buffer.writeToFile(doc_path, atomically: true, encoding: NSUTF8StringEncoding)
        } catch let error as NSError{
            // contents could not be loaded
            GBLogGen.instance()?.logerrf("write \(doc_path) failed \(error.userInfo) ")
            return ""
        }
        
        return doc_path
    }
}

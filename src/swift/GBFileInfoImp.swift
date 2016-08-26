//
//  File.swift
//  lapse_app
//
//  Created by dyno on 8/20/16.
//  Copyright © 2016 dyno. All rights reserved.
//

import Foundation

public class GBFileInfoImp:  GBFileInfoGen{
    var m_create:NSDate = NSDate()
    var m_size:Int64 = 0
    var m_name:String = ""
    var m_suffix:String = ""
    var m_prefix:String = ""
    var m_path_only:String = ""
    
    @objc public func initialize(path: String) -> Bool {
        var attr:NSDictionary
        do {
            attr = try NSFileManager.defaultManager().attributesOfItemAtPath(path)
        } catch let error as NSError{
            // contents could not be loaded
            GBLogGen.instance()?.logerrf("GBFileInfoImp initialize failed path:\(path) \(error.userInfo) ")
            return false
        }

        m_create = attr.fileCreationDate()!
        m_size = Int64(attr.fileSize())
        if attr.fileType()==nil {
            m_suffix = ""
        }else{
            m_suffix = attr.fileType()!
        }
        
        let ns_path:NSString = path
        let fix_index:NSRange = ns_path.rangeOfString(".", options: NSStringCompareOptions.BackwardsSearch)
        let path_inex:NSRange = ns_path.rangeOfString("/", options: NSStringCompareOptions.BackwardsSearch)
        
        if path_inex.length != 0 {
            m_path_only = ns_path.substringToIndex(path_inex.location+1)
            if fix_index.length != 0 && path_inex.location < fix_index.location {
                m_suffix = ns_path.substringFromIndex(fix_index.location+1)
            }
            m_prefix = ns_path.substringWithRange(NSRange(location: path_inex.location+1, length: fix_index.location-path_inex.location-1))
        }
        
        return true
    }
    
    @objc public func getSize() -> Int64 {
        return m_size
    }
    
    @objc public func getCreateDate() -> NSDate{
        return m_create
    }
    
    @objc public func getName() -> String {
        return m_prefix+m_suffix
    }
    
    @objc public func getSuffix() -> String {
        return m_suffix
    }
    
    @objc public func getPrefix() -> String {
        return m_prefix
    }
    
    @objc public func getPath() -> String {
        return m_path_only
    }
}


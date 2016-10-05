//
//  platform_excutor.swift
//  usnit_app
//
//  Created by dyno on 6/12/16.
//  Copyright © 2016 dyno. All rights reserved.
//

import Foundation
import UIKit
import AVKit

public class GBPlatformUtilityImp: GBPlatformUtilityGen {
    static let sharedInstance = GBPlatformUtilityImp()
    
    private init(){}
    
    @objc public func endEniting(force: Bool){
        UIApplication.sharedApplication().keyWindow?.endEditing(force)
    }
    
    @objc public func getLanguage() -> GBLangType{
        let strlangId = NSLocale.currentLocale().objectForKey(NSLocaleLanguageCode) as! String
        if strlangId.rangeOfString("zh")==nil {
            return GBLangType.LANGENG
        }
        else{
            return GBLangType.LANGCHS
        }
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
    
    @objc public func getFilesFromPathBySuffix(path: String, suffix: String) -> Set<String>{
        var rt:Set<String> = Set<String>()
        do {
            let url:NSURL = NSURL(fileURLWithPath:path)
            // Get the directory contents urls (including subfolders urls)
            let directoryContents = try NSFileManager.defaultManager().contentsOfDirectoryAtURL( url, includingPropertiesForKeys: nil, options: [])
            
            // if you want to filter the directory contents you can do like this:
            let files = directoryContents.filter{ $0.pathExtension == suffix }
        
            for item in files {
                rt.insert(item.path!)
            }
            return rt
            
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("getFilesFromPathBySuffix path:\(path) suffix:\(suffix) failed err:\(error)")
        }
        
        return rt
    }
    
    @objc public func getSubDirInHome(subDir: String) -> String{
        let paths = NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory.DocumentDirectory, NSSearchPathDomainMask.UserDomainMask, true)
        let documentsDirectory: AnyObject = paths[0]
        let sub_dir = documentsDirectory.stringByAppendingPathComponent(subDir)
        
        if NSFileManager.defaultManager().fileExistsAtPath(sub_dir){
            return sub_dir
        }
        do {
            try NSFileManager.defaultManager().createDirectoryAtPath(sub_dir, withIntermediateDirectories: false, attributes: nil)
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("createPathInHome path:\(sub_dir) failed err:\(error)")
            return ""
        }
        
        return sub_dir
    }
    
    @objc public func getFileNameFromPath(path: String) -> String{
        let theFileName = (path as NSString).lastPathComponent
        return theFileName
    }
    
    @objc public func getFileInfo(pathName: String) -> GBFileInfoGen?{
        let info = GBFileInfoImp()
        if info.initialize(pathName){
            return info
        }
        
        return nil
    }
    
    @objc public func deleteFile(fullpath: String) -> Bool {
        
        do {
            try NSFileManager.defaultManager().removeItemAtPath(fullpath)
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("deleteFile path:\(fullpath) failed err:\(error)")
            return false
        }
        return true
    }
    
    @objc public func isVideoFileCompatibleToSavedPhotosAlbum(fullpath: String) -> Bool{
        return UIVideoAtPathIsCompatibleWithSavedPhotosAlbum(fullpath)
    }
    
    @objc public func saveVideoFileToSavedPhotosAlbum(fullpath: String) -> Bool{
        UISaveVideoAtPathToSavedPhotosAlbum(fullpath, nil, nil, nil)
        return true
    }
    
    @objc public func playVideo(file: String){
        let player = AVPlayerViewController()
        let url:NSURL = NSURL(fileURLWithPath:file)
        player.player = AVPlayer(URL: url)
        
        getTopViewController()!.presentViewController(player, animated: false, completion: nil)
    }
    
    @objc public func createVideoFrame() -> GBVideoFrameGen?{
        let rt:GBVideoFrameGen = GBVideoFrameImp()
        return rt
    }
    
    func getTopViewController() -> UIViewController? {
        var top = UIApplication.sharedApplication().keyWindow?.rootViewController
        while let presentedViewController = top!.presentedViewController {
            top = presentedViewController
        }
        if nil==top{
            GBLogGen.instance()?.logerrf("getTopViewController null")
            return nil
        }
        return top
    }
    
    func getViewController(id:String) -> UIViewController? {
        let current_vc = UIApplication.sharedApplication().keyWindow?.rootViewController
        if nil==current_vc{
            GBLogGen.instance()?.logerrf("getViewController current_vc null")
            return nil
        }
        
        let vc = current_vc?.storyboard?.instantiateViewControllerWithIdentifier(id)
        return vc
    }
    
}

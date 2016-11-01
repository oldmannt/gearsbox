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

open class GBPlatformUtilityImp: GBPlatformUtilityGen {
    static let sharedInstance = GBPlatformUtilityImp()
    
    fileprivate init(){
        
    }
    
    public func getSystemTickNano() -> Int64{
        return Int64(CACurrentMediaTime()*1000000000)
    }
    
    public func getSystemTickMsec() -> Int64{
        return Int64(CACurrentMediaTime()*1000)
    }
    
    public func getSystemTickSec() -> Double{
        return CACurrentMediaTime()
    }
    
    @objc open func endEniting(_ force: Bool){
        UIApplication.shared.keyWindow?.endEditing(force)
    }
    
    @objc open func getLanguage() -> GBLangType{
        let strlangId = (Locale.current as NSLocale).object(forKey: NSLocale.Key.languageCode) as! String
        if strlangId.range(of: "zh")==nil {
            return GBLangType.LANGENG
        }
        else{
            return GBLangType.LANGCHS
        }
    }
    
    /**ios home directory */
    @objc open func getHomeDirectory() -> String {
        return NSSearchPathForDirectoriesInDomains(.documentDirectory, .userDomainMask, true)[0] as String
    }
    
    @objc open func getPackFilePath(_ file: String) -> String {
        let rt = Bundle.main.path(forResource: file, ofType: "")
        if rt == nil {
            GBLogGen.instance()?.logerrf("getPackFilePath \(file) failed")
            return ""
        }
        return rt!
    }
    
    @objc open func getPackFileBuffer(_ file: String) -> String{
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
    @objc open func getPackFile(toHomePath file: String) -> String{
        let buffer = getPackFileBuffer(file)
        if buffer==""{
            return ""
        }
        
        let doc_path = getHomeDirectory()+"/\(file)"
        do {
            try buffer.write(toFile: doc_path, atomically: true, encoding: String.Encoding.utf8)
        } catch let error as NSError{
            // contents could not be loaded
            GBLogGen.instance()?.logerrf("write \(doc_path) failed \(error.userInfo) ")
            return ""
        }
        
        return doc_path
    }
    
    @objc open func getFilesFromPath(bySuffix path: String, suffix: String) -> Set<String>{
        var rt:Set<String> = Set<String>()
        do {
            let url:URL = URL(fileURLWithPath:path)
            // Get the directory contents urls (including subfolders urls)
            let directoryContents = try FileManager.default.contentsOfDirectory( at: url, includingPropertiesForKeys: nil, options: [])
            
            // if you want to filter the directory contents you can do like this:
            let files = directoryContents.filter{ $0.pathExtension == suffix }
        
            for item in files {
                rt.insert(item.path)
            }
            return rt
            
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("getFilesFromPathBySuffix path:\(path) suffix:\(suffix) failed err:\(error)")
        }
        
        return rt
    }
    
    @objc open func getSubDir(inHome subDir: String) -> String{
        let documentsDirectory: String = self.getHomeDirectory()
        let sub_dir = documentsDirectory.appending(subDir)
        
        if FileManager.default.fileExists(atPath: sub_dir){
            return sub_dir
        }
        do {
            try FileManager.default.createDirectory(atPath: sub_dir, withIntermediateDirectories: false, attributes: nil)
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("createPathInHome path:\(sub_dir) failed err:\(error)")
            return ""
        }
        
        return sub_dir
    }
    
    @objc open func getFileName(fromPath path: String) -> String{
        let theFileName = (path as NSString).lastPathComponent
        return theFileName
    }
    
    @objc open func getFileInfo(_ pathName: String) -> GBFileInfoGen?{
        let info = GBFileInfoImp()
        if info.initialize(pathName){
            return info
        }
        
        return nil
    }
    
    public func fileExists(_ pathName: String) -> Bool{
        return FileManager.default.fileExists(atPath: pathName);
    }
    
    @objc open func deleteFile(_ fullpath: String) -> Bool {
        
        do {
            try FileManager.default.removeItem(atPath: fullpath)
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("deleteFile path:\(fullpath) failed err:\(error)")
            return false
        }
        return true
    }
    
    @objc open func isVideoFileCompatible(toSavedPhotosAlbum fullpath: String) -> Bool{
        return UIVideoAtPathIsCompatibleWithSavedPhotosAlbum(fullpath)
    }
    
    @objc open func saveVideoFile(toSavedPhotosAlbum fullpath: String) -> Bool{
        UISaveVideoAtPathToSavedPhotosAlbum(fullpath, nil, nil, nil)
        return true
    }
    
    @objc open func playVideo(_ file: String){
        let player = AVPlayerViewController()
        let url:URL = URL(fileURLWithPath:file)
        player.player = AVPlayer(url: url)
        
        getTopViewController()!.present(player, animated: false, completion: nil)
    }
    
    @objc open func createVideoFrame() -> GBVideoFrameGen?{
        let rt:GBVideoFrameGen = GBVideoFrameImp()
        return rt
    }
    
    fileprivate var m_indicate:UIActivityIndicatorView? = nil
    fileprivate var m_indicateOverlay:UIView? = nil
    public func showLoadingView(_ show: Bool){
        if (m_indicateOverlay != nil) {
            m_indicateOverlay?.isHidden = !show
        }
        
        let top_vc = self.getTopViewController()
        if nil == top_vc{
            return
        }
        
        if nil == m_indicate {
            if !show {
                return
            }
            m_indicate = UIActivityIndicatorView(activityIndicatorStyle: .whiteLarge)
            m_indicate?.frame = CGRect(x: 0, y: 0, width: 80, height: 80)
            m_indicate?.center = (top_vc?.view.center)!
            
            m_indicateOverlay = UIView(frame: (top_vc?.view.bounds)!)
            m_indicateOverlay?.backgroundColor = UIColor.black
            m_indicateOverlay?.alpha = 0.5
            m_indicateOverlay?.tag = self.getAddress(object: m_indicateOverlay!)
            m_indicateOverlay?.addSubview(m_indicate!)
        }
        
        m_indicateOverlay?.isHidden = !show
        if show {
            if nil == top_vc?.view.viewWithTag((m_indicateOverlay?.tag)!){
                top_vc?.view.addSubview(m_indicateOverlay!)
            }
            m_indicate?.startAnimating()
            top_vc?.view.bringSubview(toFront: m_indicateOverlay!)
        }
        else {
            m_indicate?.stopAnimating()
            m_indicateOverlay?.removeFromSuperview()
        }
        
    }
    
    fileprivate var m_alert_vc:UIAlertController = UIAlertController(title: nil, message: nil, preferredStyle: .alert)
    public func alertDialog(_ tittle: String, msg: String){
        var _tittle = tittle
        if _tittle == "" {
            _tittle = (GBLanguageStoreGen.instance()?.getString(LPAConfigKeyValueALERTTILLEINFO))!
        }
        if m_alert_vc.title == nil{
              m_alert_vc.addAction(UIAlertAction(title: GBLanguageStoreGen.instance()?.getString("ok"), style: .default, handler: { (act:UIAlertAction) in
                self.m_alert_vc.dismiss(animated: true, completion: nil)
            }))
        }
        m_alert_vc.title = _tittle
        m_alert_vc.message = msg
        
        getTopViewController()?.present(m_alert_vc, animated: true, completion: nil)
    }
    
    func getTopViewController() -> UIViewController? {
        var top = UIApplication.shared.keyWindow?.rootViewController
        while let presentedViewController = top!.presentedViewController {
            top = presentedViewController
        }
        if nil==top{
            GBLogGen.instance()?.logerrf("getTopViewController null")
            return nil
        }
        return top
    }
    
    func getViewController(_ id:String) -> UIViewController? {
        let current_vc = UIApplication.shared.keyWindow?.rootViewController
        if nil==current_vc{
            GBLogGen.instance()?.logerrf("getViewController current_vc null")
            return nil
        }
        
        let vc = current_vc?.storyboard?.instantiateViewController(withIdentifier: id)
        return vc
    }
    
    func getAddress<T: AnyObject>(object:T) -> Int {
        return unsafeBitCast(object, to: Int.self)
    }
    
}

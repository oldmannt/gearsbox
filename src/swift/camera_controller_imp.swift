//
//  camera_controller.swift
//  lapse_app
//
//  Created by dyno on 7/24/16.
//  Copyright © 2016 dyno. All rights reserved.
//

import Foundation
import UIKit
import AVFoundation
fileprivate func < <T : Comparable>(lhs: T?, rhs: T?) -> Bool {
  switch (lhs, rhs) {
  case let (l?, r?):
    return l < r
  case (nil, _?):
    return true
  default:
    return false
  }
}

fileprivate func > <T : Comparable>(lhs: T?, rhs: T?) -> Bool {
  switch (lhs, rhs) {
  case let (l?, r?):
    return l > r
  default:
    return rhs < lhs
  }
}


protocol CapturePictureHandler {
    func captureOutput(_ image:UIImage?, error:String?) -> Void
}

var last_tick:Double = 0
open class GBCameraControllerImp:  NSObject,GBCameraControllerGen,AVCaptureVideoDataOutputSampleBufferDelegate,AVCaptureAudioDataOutputSampleBufferDelegate {
    static let instance:GBCameraControllerImp = GBCameraControllerImp()
    
    @objc open func captureOutput(_ captureOutput: AVCaptureOutput!, didOutputSampleBuffer sampleBuffer: CMSampleBuffer!, from connection: AVCaptureConnection!) {
        
        if connection == self.m_audio_connection {
            m_audio_buffer = sampleBuffer
            let frame = ObjcUtility.toAudeoFrame(sampleBuffer)
            if self.m_capture_handler != nil && frame.getAudioData() != 0{
                self.m_capture_handler?.captureOutput(frame, error: "")
            }
        }
        else {
            m_cmbuffer = sampleBuffer
            if self.m_capture_mode == .immediateVideo &&
                (self.m_capture_handler != nil) &&
                !m_immediate_pause {
                //print("capture out \(CACurrentMediaTime()-last_tick)")
                self.m_capture_handler?.captureOutput(ObjcUtility.toVideoFrame(m_cmbuffer!), error: "")
            }
            //last_tick = CACurrentMediaTime()
        }
    }

    open func initializ_swif(_ view:UIView) -> Bool{
        requestCamera(m_cameraPosition, addinput: true)
        if m_captureDevice == nil{
            GBLogGen.instance()?.logerrf("request camera failed \(#file) \(#function) \(#line)");
            return false
        }
        
        setRefreshDuration(1, scale: 30)
        self.setQuality(GBCameraQuality.P720)
        outputToView(view)
        outputToBuffer()
        
        
        return true
    }
    
    @objc open func setRefreshDuration(_ value: Int64, scale: Int32) {
        do {
            try m_captureDevice!.lockForConfiguration()
            m_captureDevice?.activeVideoMaxFrameDuration = CMTimeMake(value, Int32(scale));
            m_captureDevice?.activeVideoMinFrameDuration = CMTimeMake(value, Int32(scale));
            m_captureDevice?.unlockForConfiguration()
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("setRefreshDuration err:\(error) \(#file) \(#function) \(#line)");
        }        
    }
    
    @objc open func initialize(_ audio: Bool){
        setupAudio()
        setAudioEnable(audio)
    }
    
    @objc open func setAudioEnable(_ enable: Bool){
        m_audio_enable = enable
        m_audio_connection?.isEnabled = m_audio_enable
    }
    
    @objc open func startCamera(){
        m_captureSession.startRunning()
    }
    
    @objc open func stopCamera(){
        m_captureSession.stopRunning()
    }
    
    @objc open func switchFront(_ front: Bool) {
        if m_isfront == front {
            return
        }
        let position:AVCaptureDevicePosition = front ? .front : .back
        let currentInput = m_captureSession.inputs[0] as! AVCaptureInput
        m_captureSession.removeInput(currentInput)
        requestCamera(position, addinput: true);
    }
    
    @objc open func isFront() -> Bool {
        return m_isfront
    }
    
    func setupAudio() {
        let audio_device:AVCaptureDevice = AVCaptureDevice(uniqueID: AVMediaTypeAudio)
        var audio_input:AVCaptureDeviceInput?
            
        do {
            try audio_input = AVCaptureDeviceInput(device: audio_device)
        } catch {
            GBLogGen.instance()?.logerrf("setupAuodio AVCaptureDeviceInput failed \(#file) \(#function) \(#line)");
            return
        }
        
        self.m_audio_output = AVCaptureAudioDataOutput()
        if self.m_captureSession.canAddInput(audio_input){
            m_captureSession.addInput(audio_input)
        }

        self.m_audio_output = AVCaptureAudioDataOutput()
        self.m_audio_output?.setSampleBufferDelegate(self, queue: DispatchQueue.main)
        if self.m_captureSession.canAddOutput(self.m_audio_output){
            m_captureSession.addOutput(self.m_audio_output)
        }
        self.m_audio_connection = self.m_audio_output?.connection(withMediaType: AVMediaTypeAudio)
    }
    
    func toFlashMode(_ mode:GBCameraFlash) -> AVCaptureFlashMode {
        var camera_flash:AVCaptureFlashMode = AVCaptureFlashMode.on
        switch mode {
        case GBCameraFlash.on:
            camera_flash = AVCaptureFlashMode.on
            break
        case GBCameraFlash.off:
            camera_flash = AVCaptureFlashMode.off
            break
        case GBCameraFlash.auto:
            camera_flash = AVCaptureFlashMode.auto
            break
        default:
            GBLogGen.instance()?.logerrf("toFlashMode unsorppted mode:\(mode) \(#file) \(#function) \(#line)");
            break
        }
        return camera_flash
    }
    
    func toGBFlashMode(_ mode:AVCaptureFlashMode) -> GBCameraFlash {
        switch mode {
        case AVCaptureFlashMode.on:
            return GBCameraFlash.on
        case AVCaptureFlashMode.off:
            return GBCameraFlash.off
        case AVCaptureFlashMode.auto:
            return GBCameraFlash.auto
        default:
            break
        }
        
        GBLogGen.instance()?.logerrf("toGBFlashMode unsorppted mode:\(mode) \(#file) \(#function) \(#line)");
        return GBCameraFlash.none
    }
    
    @objc open func setFlashMode(_ mode: GBCameraFlash){
        let camera_flash:AVCaptureFlashMode = toFlashMode(mode)
        for device in AVCaptureDevice.devices(withMediaType: AVMediaTypeVideo) {
            let captureDevice = device as! AVCaptureDevice
            if (captureDevice.isFlashModeSupported(camera_flash)) {
                do {
                    try captureDevice.lockForConfiguration()
                    m_captureSession.beginConfiguration()
                    captureDevice.flashMode = camera_flash
                    m_captureSession.commitConfiguration()
                    captureDevice.unlockForConfiguration()
                }  catch let error as NSError {
                    GBLogGen.instance()?.logerrf("setFlash failed err:\(error) \(#file) \(#function) \(#line)");
                    return
                }
            }
        }
    }

    
    @objc open func getFlashMode() -> GBCameraFlash {
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getFlash m_captureDevice nil \(#file) \(#function) \(#line)");
            return GBCameraFlash.none
        }
        
        return toGBFlashMode((m_captureDevice?.flashMode)!)
    }
    
    fileprivate func getQualityConfig() -> GBCameraQuality {
        return (GBCameraConfigGen.instance()?.getQuatityLevel())!
    }
    
    @objc open func setQuality(_ quality: GBCameraQuality) {
        if m_quality == quality {
            return
        }
        m_quality = quality
        if m_quality == GBCameraQuality.none {
            m_quality = getQualityConfig()
        }
        var sessionPreset = AVCaptureSessionPreset1280x720
        GBCameraConfigGen.instance()?.setQuatityLevel(quality)
        switch (quality) {
        case GBCameraQuality.P360:
            sessionPreset = AVCaptureSessionPreset352x288
        case GBCameraQuality.P480:
            sessionPreset = AVCaptureSessionPreset640x480
        case GBCameraQuality.P720:
            sessionPreset = AVCaptureSessionPreset1280x720
        case GBCameraQuality.P1080:
            sessionPreset = AVCaptureSessionPreset1920x1080
        default: break
        }
        m_captureSession.beginConfiguration()
        m_captureSession.sessionPreset = sessionPreset
        m_captureSession.commitConfiguration()
    }
    
    @objc open func getQuality() -> GBCameraQuality{
        return m_quality
    }
    
    func getExposureMode(_ gb:GBCameraExposureMode) -> AVCaptureExposureMode {
        switch gb {
        case GBCameraExposureMode.locked:
            return AVCaptureExposureMode.locked
        case GBCameraExposureMode.autoExpose:
            return AVCaptureExposureMode.autoExpose
        case GBCameraExposureMode.continuousAutoExposure:
            return AVCaptureExposureMode.continuousAutoExposure
        case GBCameraExposureMode.modeCustom:
            return AVCaptureExposureMode.custom
        default:
            break
        }
        GBLogGen.instance()?.logerrf("getSExposureMode unsupport model:\(gb) \(#file) \(#function) \(#line)");
        return AVCaptureExposureMode.init(rawValue: -1)!
    }
    
    func getGBExposureMode(_ mode:AVCaptureExposureMode) -> GBCameraExposureMode {
        switch mode {
        case AVCaptureExposureMode.locked:
            return GBCameraExposureMode.locked
        case AVCaptureExposureMode.autoExpose:
            return GBCameraExposureMode.autoExpose
        case AVCaptureExposureMode.continuousAutoExposure:
            return GBCameraExposureMode.continuousAutoExposure
        case AVCaptureExposureMode.custom:
            return GBCameraExposureMode.modeCustom
        default:
            break
        }
        GBLogGen.instance()?.logerrf("getGBExposureMode unsupport model:\(mode) \(#file) \(#function) \(#line)");
        return GBCameraExposureMode.none
    }
    
    @objc open func setExposureMode(_ modle: GBCameraExposureMode){
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("setExposureMode m_captureDevice nil \(#file) \(#function) \(#line)");
            return
        }
        do {
            try m_captureDevice!.lockForConfiguration()
            m_captureDevice?.exposureMode = self.getExposureMode(modle)
            m_captureDevice?.unlockForConfiguration()
            } catch let error as NSError {
                GBLogGen.instance()?.logerrf("setExposureMode err:\(error) \(#file) \(#function) \(#line)");
        }
    }
    
    open func getExposureMode() -> GBCameraExposureMode {
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getExposureMode m_captureDevice nil \(#file) \(#function) \(#line)");
            return GBCameraExposureMode.none
        }
        return getGBExposureMode((m_captureDevice?.exposureMode)!)
    }
    
    @objc open func setExposurePoint(_ x: Float, y: Float){
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("setExposurePoint m_captureDevice nil \(#file) \(#function) \(#line)");
            return
        }
        if !(m_captureDevice?.isExposurePointOfInterestSupported)! {
            GBLogGen.instance()?.logerrf("unsupport setExposurePoint \(#file) \(#function) \(#line)");
            return
        }
        
        do {
            try m_captureDevice!.lockForConfiguration()
            m_captureDevice?.exposurePointOfInterest = CGPoint(x: Double(x), y: Double(y))
            m_captureDevice?.exposureMode = AVCaptureExposureMode.continuousAutoExposure
            m_captureDevice?.unlockForConfiguration()
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("setExposurePoint err:\(error) \(#file) \(#function) \(#line)");
        }
    }
    
    @objc open func setExposureEv(_ ev: Float) {
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("setExposureEv m_captureDevice nil \(#file) \(#function) \(#line)");
            return
        }
        if ev > m_captureDevice?.maxExposureTargetBias || ev < m_captureDevice?.minExposureTargetBias{
            GBLogGen.instance()?.logerrf("setExposureEv ev:\(ev) outof range \(#file) \(#function) \(#line)");
            return
        }
        do {
            try m_captureDevice!.lockForConfiguration()
            m_captureDevice?.setExposureTargetBias(ev, completionHandler: nil)
            m_captureDevice?.unlockForConfiguration()
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("setExposureEv err:\(error) \(#file) \(#function) \(#line)");
        }
    }
    
    @objc open func getExposureEv() -> Float{
        return (m_captureDevice?.exposureTargetBias)!
    }
    
    @objc open func getExposureMaxEv() -> Float {
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getExposureMaxEv m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0.0
        }
        return (m_captureDevice?.maxExposureTargetBias)!
    }
    
    @objc open func getExposureMinEv() -> Float {
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getExposureMminEv m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0.0
        }
        return (m_captureDevice?.minExposureTargetBias)!
    }
    
    @objc open func setExposureDuration(_ seconds: Float){
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getExposureMaxEv m_captureDevice nil \(#file) \(#function) \(#line)");
            return
        }
        do {
            try m_captureDevice!.lockForConfiguration()
            m_captureDevice?.setExposureModeCustomWithDuration(CMTime(seconds: Double(seconds), preferredTimescale: CMTimeScale(1000)), iso: AVCaptureISOCurrent, completionHandler: nil)
            m_captureDevice?.unlockForConfiguration()
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("setExposureEv err:\(error) \(#file) \(#function) \(#line)");
        }
    }
    
    @objc open func getExposureDuration() -> Float{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getExposureMaxEv m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0.0
        }
        return Float((m_captureDevice?.exposureDuration.seconds)!)
    }
    
    open func getExposureDurationCMT() -> CMTime?{
        return m_captureDevice?.exposureDuration
    }
    
    @objc open func getExposureMinDuration() -> Float{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getExposrueMinDuration m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0.0
        }
        return Float((m_captureDevice?.activeFormat.minExposureDuration.seconds)!)
    }
    
    @objc open func getExposureMaxDuration() -> Float{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getExposureMaxDuration m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0.0
        }
        return Float((m_captureDevice?.activeFormat.maxExposureDuration.seconds)!)
    }
    
    @objc open func setISO(_ iso: Int32){
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("setISO m_captureDevice nil \(#file) \(#function) \(#line)");
            return
        }
        do {
            try m_captureDevice!.lockForConfiguration()
            m_captureDevice?.setExposureModeCustomWithDuration(AVCaptureExposureDurationCurrent, iso: Float(iso), completionHandler: nil)
            m_captureDevice?.unlockForConfiguration()
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("setISO err:\(error) \(#file) \(#function) \(#line)");
        }
    }
    
    @objc open func getISO() -> Int32{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getISO m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0
        }
        
        return Int32((m_captureDevice?.iso)!)
    }
    
    @objc open func getISOMax() -> Int32{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getISOMax m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0
        }
        return Int32((m_captureDevice?.activeFormat.maxISO)!)
    }
    
    @objc open func getISOMin() -> Int32{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getISOMin m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0
        }
        return Int32((m_captureDevice?.activeFormat.minISO)!)
    }
    
    func toFocusMode(_ mode:GBCameraFocusMode) -> AVCaptureFocusMode {
        switch mode {
        case GBCameraFocusMode.locked:
            return AVCaptureFocusMode.locked
        case GBCameraFocusMode.autoFocus:
            return AVCaptureFocusMode.autoFocus
        case GBCameraFocusMode.continuousAutoFocus:
            return AVCaptureFocusMode.continuousAutoFocus
        default:
            break
        }
        GBLogGen.instance()?.logerrf("toFocusMode unsport mode:\(mode) \(#file) \(#function) \(#line)");
        return AVCaptureFocusMode.autoFocus
    }
    
    func toGBFocusMode(_ mode:AVCaptureFocusMode) -> GBCameraFocusMode {
        switch mode {
        case AVCaptureFocusMode.locked:
            return GBCameraFocusMode.locked
        case AVCaptureFocusMode.autoFocus:
            return GBCameraFocusMode.autoFocus
        case AVCaptureFocusMode.continuousAutoFocus:
            return GBCameraFocusMode.continuousAutoFocus
        default:
            break
        }
        GBLogGen.instance()?.logerrf("toGBFocusMode unsport mode:\(mode) \(#file) \(#function) \(#line)");
        return GBCameraFocusMode.none
    }
    
    @objc open func setFocusMode(_ mode: GBCameraFocusMode){
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("setFocusModel m_captureDevice nil \(#file) \(#function) \(#line)");
            return
        }
        do {
            try m_captureDevice!.lockForConfiguration()
            m_captureDevice?.focusMode = toFocusMode(mode)
            m_captureDevice?.unlockForConfiguration()
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("setFocusModel err:\(error) \(#file) \(#function) \(#line)");
        }
    }
    
    @objc open func getFocusMode() -> GBCameraFocusMode{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getFocusModel m_captureDevice nil \(#file) \(#function) \(#line)");
            return GBCameraFocusMode.none
        }
        return toGBFocusMode((m_captureDevice?.focusMode)!)
    }
    
    /** lens form 0.0 to 1.0, shortest to furthest */
    @objc open func setFocusLens(_ lens: Float){
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("m_captureDevice nil \(#file) \(#function) \(#line)");
        }
        if lens > self.getFocusMax() || lens < self.getFocusMin(){
            GBLogGen.instance()?.logerrf("lens:\(lens) out of range \(#file) \(#function) \(#line)");
            return
        }
        do {
            try m_captureDevice!.lockForConfiguration()
            m_captureDevice?.setFocusModeLockedWithLensPosition(lens, completionHandler: nil)
            m_captureDevice?.unlockForConfiguration()
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("setFocusLens err:\(error) \(#file) \(#function) \(#line)");
        }


    }
    
    @objc open func getFocusLens() -> Float{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0
        }
        return m_captureDevice!.lensPosition
    }
    
    @objc open func getFocusMax() -> Float {
        return 1.0
    }
    
    @objc open func getFocusMin() -> Float {
        return 0.0
    }
    
    @objc open func setFocusPoint(_ x: Float, y: Float){
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("setFocusPoint m_captureDevice nil \(#file) \(#function) \(#line)");
            return
        }
        if !(m_captureDevice?.isFocusPointOfInterestSupported)!{
            GBLogGen.instance()?.logerrf("setFocusPoint unsupport \(#file) \(#function) \(#line)");
            return
        }
        do {
            try m_captureDevice!.lockForConfiguration()
            m_captureDevice?.focusPointOfInterest = CGPoint(x: Double(x), y: Double(y))
            m_captureDevice?.focusMode = AVCaptureFocusMode.continuousAutoFocus
            m_captureDevice?.unlockForConfiguration()
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("setFocusPoint err:\(error) \(#file) \(#function) \(#line)");
        }
    }
    
    func toAVCaptureAutoFocusRangeRestriction(_ range:GBCameraFocusRange) -> AVCaptureAutoFocusRangeRestriction {
        switch range {
        case GBCameraFocusRange.none:
            return AVCaptureAutoFocusRangeRestriction.none
        case GBCameraFocusRange.near:
            return AVCaptureAutoFocusRangeRestriction.near
        case GBCameraFocusRange.far:
            return AVCaptureAutoFocusRangeRestriction.far
        default:
            break
        }
        return AVCaptureAutoFocusRangeRestriction.none
    }
    
    func toGBFocusRange(_ range:AVCaptureAutoFocusRangeRestriction) -> GBCameraFocusRange {
        switch range {
        case AVCaptureAutoFocusRangeRestriction.none:
            return GBCameraFocusRange.none
        case AVCaptureAutoFocusRangeRestriction.near:
            return GBCameraFocusRange.near
        case AVCaptureAutoFocusRangeRestriction.far:
            return GBCameraFocusRange.far
        default:
            break
        }
        return GBCameraFocusRange.none
    }
    
    @objc open func setFocusAutoRange(_ range: GBCameraFocusRange){
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("setFocusAutoRange m_captureDevice nil \(#file) \(#function) \(#line)")
            return
        }
        if !(m_captureDevice?.isAutoFocusRangeRestrictionSupported)!{
            GBLogGen.instance()?.logerrf("setFocusAutoRange unsupported \(#file) \(#function) \(#line)");
            return
        }
        do {
            try m_captureDevice!.lockForConfiguration()
            m_captureDevice?.autoFocusRangeRestriction = toAVCaptureAutoFocusRangeRestriction(range)
            m_captureDevice?.unlockForConfiguration()
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("setFocusAutoRange err:\(error) \(#file) \(#function) \(#line)");
        }
    }
    
    @objc open func getFocusAutoRange() -> GBCameraFocusRange{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getFocusAutoRange m_captureDevice nil \(#file) \(#function) \(#line)")
            return toGBFocusRange(AVCaptureAutoFocusRangeRestriction.none)
        }
        
        return toGBFocusRange((m_captureDevice?.autoFocusRangeRestriction)!)
    }

    
    @objc open func setZoom(_ zoom: Float){
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("setZoom m_captureDevice nil \(#file) \(#function) \(#line)")
            return
        }
        do {
            try m_captureDevice!.lockForConfiguration()
            m_captureDevice?.videoZoomFactor = CGFloat(zoom)
            m_captureDevice?.unlockForConfiguration()
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("setZoom err:\(error) \(#file) \(#function) \(#line)");
        }
    }
    
    @objc open func getZoom() -> Float{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getZoom m_captureDevice nil \(#file) \(#function) \(#line)")
            return 0.0
        }
        return Float((m_captureDevice?.videoZoomFactor)!)
    }
    
    /** minimum value is 1.0 */
    @objc open func getZoomMax() -> Float{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getMaxZoom m_captureDevice nil \(#file) \(#function) \(#line)")
            return 1.0
        }
        return Float((m_captureDevice?.activeFormat.videoMaxZoomFactor)!)
    }
    
    @objc open func getZoomMin() -> Float {
        return 1.0
    }
    
    @objc open func captureOneFrame() -> GBVideoFrameGen? {
        if nil == m_cmbuffer {
            return nil
        }

        return ObjcUtility.toVideoFrame(m_cmbuffer!)
    }
    
    @objc open func asnyOnePicture(){

        let capture_connection:AVCaptureConnection = self.m_stillImageOutput.connection(withMediaType: AVMediaTypeVideo)
        //let curent_device_orientation:UIDeviceOrientation = UIDevice.currentDevice().orientation
        //let av_orientation:AVCaptureVideoOrientation = self.orientationDevice2AV(curent_device_orientation)
        capture_connection.videoOrientation = AVCaptureVideoOrientation.landscapeRight
        //capture_connection.videoScaleAndCropFactor = 1.0
        
        m_stillImageOutput.captureStillImageAsynchronously(from: capture_connection,
         completionHandler:{ (sampleBuffer, error) -> Void in
            // ...
            // Process the image data (sampleBuffer) here to get an image file we can put in our captureImageView
            self.m_cmbuffer = sampleBuffer
            let err_msg:String = (error != nil) ? error.debugDescription : ""
            
            if nil == sampleBuffer{
                GBLogGen.instance()?.logerrf("sampleBuffer nil, err:\(err_msg) \(#file) \(#function) \(#line)")
                return
            }
            
            if self.m_capture_image_handler != nil {
                let imageData = AVCaptureStillImageOutput.jpegStillImageNSDataRepresentation(sampleBuffer)
                let dataProvider = CGDataProvider(data: imageData as! CFData)
                let cgImageRef = CGImage(jpegDataProviderSource: dataProvider!, decode: nil, shouldInterpolate: true, intent: CGColorRenderingIntent.defaultIntent)
                let image = UIImage(cgImage: cgImageRef!)
                
                self.m_capture_image_handler?.captureOutput(image, error: err_msg)
            }
            else if self.m_capture_mode == .photo && self.m_capture_handler != nil {
                self.m_capture_handler?.captureOutput(ObjcUtility.toVideoFrame(sampleBuffer!), error: err_msg)
            }
        })
    }
    
    @objc open func asnyOneFrame() {
        if m_capture_mode == .photo {
            asnyOnePicture()
            return
        }
        
        if m_capture_mode == .immediateVideo {
            return
        }
        let frame = self.captureOneFrame()
        
        if self.m_capture_handler != nil && frame != nil{
            self.m_capture_handler?.captureOutput(frame, error: "")
        }
    }
    
    @objc open func setCaptureHandler(_ handler: GBCameraCaptureHandler?){
        m_capture_handler = handler
    }
    
    @objc open  func setImmediaPause(_ flag: Bool){
        m_immediate_pause = flag
    }
    
    public func setCaptureMode(_ mode: GBCameraCaptureMode) {
        self.m_capture_mode = mode
    }
    
    public func getCaptureMode() -> GBCameraCaptureMode {
        return self.m_capture_mode
    }

    func asnyOnePictureUIImage() {
        self.asnyOnePicture()
    }
    func setCapturePictureHandler(_ handler:CapturePictureHandler?) -> Void {
        m_capture_image_handler = handler
    }
    open func rotate(){
        m_previewLayer?.frame = UIScreen.main.bounds
    }
    
    func rotateScreen() {
        let ori:UIInterfaceOrientation = UIApplication.shared.statusBarOrientation
        
        if ori == UIInterfaceOrientation.landscapeRight  {
            m_previewLayer?.connection.videoOrientation = AVCaptureVideoOrientation.landscapeRight
        }
        else if ori == UIInterfaceOrientation.landscapeLeft {
            m_previewLayer?.connection.videoOrientation = AVCaptureVideoOrientation.landscapeLeft
        }
    }
    
    fileprivate func requestCamera(_ type: AVCaptureDevicePosition, addinput:Bool) -> Bool {
        for device in AVCaptureDevice.devices() {
            if ((device as AnyObject).hasMediaType(AVMediaTypeVideo)) {
                if((device as AnyObject).position == type) {
                    m_captureDevice = device as? AVCaptureDevice
                }
            }
        }
        
        if nil == m_captureDevice {
            NSLog("capture device error")
        }
        else if addinput{
            do {
                try m_captureSession.addInput(AVCaptureDeviceInput(device: m_captureDevice))
            } catch {
                GBLogGen.instance()?.logerrf("captureSession addInput failed \(#file) \(#function) \(#line)");
                return false
            }
        }
        
        return m_captureDevice != nil
    }
    
    fileprivate func outputToView(_ view:UIView){
        
        //previewLayer.videoGravity = AVLayerVideoGravityResizeAspectFill; // 设置预览时的视频缩放方式
        //[[previewLayer connection] setVideoOrientation:AVCaptureVideoOrientationPortrait]; // 设置视频的朝向
        //m_stillImageOutput.outputSettings = [AVVideoCodecKey: AVVideoCodecJPEG]

        let dctPixelFormatType : Dictionary<NSString, NSNumber> = [kCVPixelBufferPixelFormatTypeKey : NSNumber(value: kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange as UInt32)]
        
        m_stillImageOutput.outputSettings = dctPixelFormatType

        if m_captureSession.canAddOutput(m_stillImageOutput) {
            m_captureSession.addOutput(m_stillImageOutput)
        }
        
        m_previewLayer = AVCaptureVideoPreviewLayer(session: m_captureSession)
        m_previewLayer?.videoGravity = AVLayerVideoGravityResizeAspectFill
        m_previewLayer?.frame = UIScreen.main.bounds
        
        m_previewLayer?.connection.videoOrientation = AVCaptureVideoOrientation.landscapeRight
        view.layer.addSublayer(m_previewLayer!)
    }
    
    fileprivate func outputToBuffer(){
        // Acquisition of output data
        let videoDataOutput:AVCaptureVideoDataOutput = AVCaptureVideoDataOutput()
        
        // Set of color channel
        let dctPixelFormatType : Dictionary<NSString, NSNumber> = [kCVPixelBufferPixelFormatTypeKey : NSNumber(value: kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange as UInt32)]
        videoDataOutput.videoSettings = dctPixelFormatType
        videoDataOutput.alwaysDiscardsLateVideoFrames = true
        
        // Specified queue to capture the image
        //var videoDataOutputQueue: dispatch_queue_t = dispatch_queue_create("CtrlVideoQueue", DISPATCH_QUEUE_SERIAL)
        videoDataOutput.setSampleBufferDelegate(self, queue: DispatchQueue.main)
        videoDataOutput.alwaysDiscardsLateVideoFrames = true
        
        if m_captureSession.canAddOutput(videoDataOutput) {
            m_captureSession.addOutput(videoDataOutput)
        }
    }
    
    fileprivate func orientationDevice2AV(_ device:UIDeviceOrientation) -> AVCaptureVideoOrientation {
        switch device {
        case UIDeviceOrientation.landscapeLeft:
            return AVCaptureVideoOrientation.landscapeLeft
        case UIDeviceOrientation.landscapeRight:
            return AVCaptureVideoOrientation.landscapeRight
        default:
            break
        }
        
        GBLogGen.instance()?.logerrf("orientationDevice2AV unexpected device orientation \(device) \(#file) \(#function) \(#line)");
        return AVCaptureVideoOrientation.portrait
    }
    
    fileprivate let m_devices = AVCaptureDevice.devices()
    fileprivate var m_captureDevice : AVCaptureDevice?
    fileprivate let m_captureSession = AVCaptureSession()
    fileprivate var m_cameraPosition = AVCaptureDevicePosition.back
    
    fileprivate var m_previewLayer : AVCaptureVideoPreviewLayer?
    fileprivate let m_stillImageOutput = AVCaptureStillImageOutput()
    fileprivate var m_cmbuffer:CMSampleBuffer?
    fileprivate var m_isfront:Bool = false
    fileprivate var m_quality:GBCameraQuality = GBCameraQuality.none
    
    fileprivate var m_immediate_pause:Bool = false
    fileprivate var m_capture_mode:GBCameraCaptureMode = .photo
    fileprivate var m_capture_handler: GBCameraCaptureHandler?
    fileprivate var m_capture_image_handler: CapturePictureHandler?
    
    fileprivate var m_audio_enable: Bool = false
    fileprivate var m_audio_output: AVCaptureAudioDataOutput?
    fileprivate var m_audio_connection: AVCaptureConnection?
    fileprivate var m_audio_buffer: CMSampleBuffer?
}

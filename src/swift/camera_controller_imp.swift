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

protocol CapturePictureHandler {
    func captureOutput(image:UIImage?, error:String?) -> Void
}

public class GBCameraControllerImp:  NSObject,GBCameraControllerGen,AVCaptureVideoDataOutputSampleBufferDelegate,AVCaptureAudioDataOutputSampleBufferDelegate {
    static let instance:GBCameraControllerImp = GBCameraControllerImp()
    
    @objc public func captureOutput(captureOutput: AVCaptureOutput!, didOutputSampleBuffer sampleBuffer: CMSampleBuffer!, fromConnection connection: AVCaptureConnection!) {
        
        if connection == self.m_audio_connection {
            m_audio_buffer = sampleBuffer
            let frame = ObjcUtility.toAudeoFrame(sampleBuffer)
            if self.m_capture_handler != nil && frame.getAudioData() != 0{
                self.m_capture_handler?.captureOutput(frame, error: "")
            }
        }
        else {
            m_cmbuffer = sampleBuffer
        }
    }

    public func initializ_swif(view:UIView) -> Bool{
        requestCamera(m_cameraPosition, addinput: true)
        if m_captureDevice == nil{
            GBLogGen.instance()?.logerrf("request camera failed \(#file) \(#function) \(#line)");
            return false
        }
        
        m_captureDevice?.activeVideoMaxFrameDuration = CMTimeMake(1, Int32(30));
        self.setQuality(GBCameraQuality.P720)
        outputToView(view)
        outputToBuffer()
        
        
        return true
    }
    
    @objc public func initialize(audio: Bool){
        setupAudio()
        setAudioEnable(audio)
    }
    
    @objc public func setAudioEnable(enable: Bool){
        m_audio_enable = enable
        m_audio_connection?.enabled = m_audio_enable
    }
    
    @objc public func startCamera(){
        m_captureSession.startRunning()
    }
    
    @objc public func stopCamera(){
        m_captureSession.stopRunning()
    }
    
    @objc public func switchFront(front: Bool) {
        if m_isfront == front {
            return
        }
        let position:AVCaptureDevicePosition = front ? .Front : .Back
        let currentInput = m_captureSession.inputs[0] as! AVCaptureInput
        m_captureSession.removeInput(currentInput)
        requestCamera(position, addinput: true);
    }
    
    @objc public func isFront() -> Bool {
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
        self.m_audio_output?.setSampleBufferDelegate(self, queue: dispatch_get_main_queue())
        if self.m_captureSession.canAddOutput(self.m_audio_output){
            m_captureSession.addOutput(self.m_audio_output)
        }
        self.m_audio_connection = self.m_audio_output?.connectionWithMediaType(AVMediaTypeAudio)
    }
    
    func toFlashMode(mode:GBCameraFlash) -> AVCaptureFlashMode {
        var camera_flash:AVCaptureFlashMode = AVCaptureFlashMode.On
        switch mode {
        case GBCameraFlash.On:
            camera_flash = AVCaptureFlashMode.On
            break
        case GBCameraFlash.Off:
            camera_flash = AVCaptureFlashMode.Off
            break
        case GBCameraFlash.Auto:
            camera_flash = AVCaptureFlashMode.Auto
            break
        default:
            GBLogGen.instance()?.logerrf("toFlashMode unsorppted mode:\(mode) \(#file) \(#function) \(#line)");
            break
        }
        return camera_flash
    }
    
    func toGBFlashMode(mode:AVCaptureFlashMode) -> GBCameraFlash {
        switch mode {
        case AVCaptureFlashMode.On:
            return GBCameraFlash.On
        case AVCaptureFlashMode.Off:
            return GBCameraFlash.Off
        case AVCaptureFlashMode.Auto:
            return GBCameraFlash.Auto
        default:
            break
        }
        
        GBLogGen.instance()?.logerrf("toGBFlashMode unsorppted mode:\(mode) \(#file) \(#function) \(#line)");
        return GBCameraFlash.None
    }
    
    @objc public func setFlashMode(mode: GBCameraFlash){
        let camera_flash:AVCaptureFlashMode = toFlashMode(mode)
        for device in AVCaptureDevice.devicesWithMediaType(AVMediaTypeVideo) {
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

    
    @objc public func getFlashMode() -> GBCameraFlash {
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getFlash m_captureDevice nil \(#file) \(#function) \(#line)");
            return GBCameraFlash.None
        }
        
        return toGBFlashMode((m_captureDevice?.flashMode)!)
    }
    
    private func getQualityConfig() -> GBCameraQuality {
        return (GBCameraConfigGen.instance()?.getQuatityLevel())!
    }
    
    @objc public func setQuality(quality: GBCameraQuality) {
        if m_quality == quality {
            return
        }
        m_quality = quality
        if m_quality == GBCameraQuality.None {
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
    
    @objc public func getQuality() -> GBCameraQuality{
        return m_quality
    }
    
    func getExposureMode(gb:GBCameraExposureMode) -> AVCaptureExposureMode {
        switch gb {
        case GBCameraExposureMode.Locked:
            return AVCaptureExposureMode.Locked
        case GBCameraExposureMode.AutoExpose:
            return AVCaptureExposureMode.AutoExpose
        case GBCameraExposureMode.ContinuousAutoExposure:
            return AVCaptureExposureMode.ContinuousAutoExposure
        case GBCameraExposureMode.ModeCustom:
            return AVCaptureExposureMode.Custom
        default:
            break
        }
        GBLogGen.instance()?.logerrf("getSExposureMode unsupport model:\(gb) \(#file) \(#function) \(#line)");
        return AVCaptureExposureMode.init(rawValue: -1)!
    }
    
    func getGBExposureMode(mode:AVCaptureExposureMode) -> GBCameraExposureMode {
        switch mode {
        case AVCaptureExposureMode.Locked:
            return GBCameraExposureMode.Locked
        case AVCaptureExposureMode.AutoExpose:
            return GBCameraExposureMode.AutoExpose
        case AVCaptureExposureMode.ContinuousAutoExposure:
            return GBCameraExposureMode.ContinuousAutoExposure
        case AVCaptureExposureMode.Custom:
            return GBCameraExposureMode.ModeCustom
        default:
            break
        }
        GBLogGen.instance()?.logerrf("getGBExposureMode unsupport model:\(mode) \(#file) \(#function) \(#line)");
        return GBCameraExposureMode.None
    }
    
    @objc public func setExposureMode(modle: GBCameraExposureMode){
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
    
    public func getExposureMode() -> GBCameraExposureMode {
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getExposureMode m_captureDevice nil \(#file) \(#function) \(#line)");
            return GBCameraExposureMode.None
        }
        return getGBExposureMode((m_captureDevice?.exposureMode)!)
    }
    
    @objc public func setExposurePoint(x: Float, y: Float){
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("setExposurePoint m_captureDevice nil \(#file) \(#function) \(#line)");
            return
        }
        if !(m_captureDevice?.exposurePointOfInterestSupported)! {
            GBLogGen.instance()?.logerrf("unsupport setExposurePoint \(#file) \(#function) \(#line)");
            return
        }
        
        do {
            try m_captureDevice!.lockForConfiguration()
            m_captureDevice?.exposurePointOfInterest = CGPoint(x: Double(x), y: Double(y))
            m_captureDevice?.exposureMode = AVCaptureExposureMode.ContinuousAutoExposure
            m_captureDevice?.unlockForConfiguration()
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("setExposurePoint err:\(error) \(#file) \(#function) \(#line)");
        }
    }
    
    @objc public func setExposureEv(ev: Float) {
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
    
    @objc public func getExposureEv() -> Float{
        return (m_captureDevice?.exposureTargetBias)!
    }
    
    @objc public func getExposureMaxEv() -> Float {
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getExposureMaxEv m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0.0
        }
        return (m_captureDevice?.maxExposureTargetBias)!
    }
    
    @objc public func getExposureMinEv() -> Float {
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getExposureMminEv m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0.0
        }
        return (m_captureDevice?.minExposureTargetBias)!
    }
    
    @objc public func setExposureDuration(seconds: Float){
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getExposureMaxEv m_captureDevice nil \(#file) \(#function) \(#line)");
            return
        }
        do {
            try m_captureDevice!.lockForConfiguration()
            m_captureDevice?.setExposureModeCustomWithDuration(CMTime(seconds: Double(seconds), preferredTimescale: CMTimeScale(1000)), ISO: AVCaptureISOCurrent, completionHandler: nil)
            m_captureDevice?.unlockForConfiguration()
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("setExposureEv err:\(error) \(#file) \(#function) \(#line)");
        }
    }
    
    @objc public func getExposureDuration() -> Float{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getExposureMaxEv m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0.0
        }
        return Float((m_captureDevice?.exposureDuration.seconds)!)
    }
    
    public func getExposureDurationCMT() -> CMTime?{
        return m_captureDevice?.exposureDuration
    }
    
    @objc public func getExposureMinDuration() -> Float{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getExposrueMinDuration m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0.0
        }
        return Float((m_captureDevice?.activeFormat.minExposureDuration.seconds)!)
    }
    
    @objc public func getExposureMaxDuration() -> Float{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getExposureMaxDuration m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0.0
        }
        return Float((m_captureDevice?.activeFormat.maxExposureDuration.seconds)!)
    }
    
    @objc public func setISO(iso: Int32){
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("setISO m_captureDevice nil \(#file) \(#function) \(#line)");
            return
        }
        do {
            try m_captureDevice!.lockForConfiguration()
            m_captureDevice?.setExposureModeCustomWithDuration(AVCaptureExposureDurationCurrent, ISO: Float(iso), completionHandler: nil)
            m_captureDevice?.unlockForConfiguration()
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("setISO err:\(error) \(#file) \(#function) \(#line)");
        }
    }
    
    @objc public func getISO() -> Int32{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getISO m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0
        }
        
        return Int32((m_captureDevice?.ISO)!)
    }
    
    @objc public func getISOMax() -> Int32{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getISOMax m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0
        }
        return Int32((m_captureDevice?.activeFormat.maxISO)!)
    }
    
    @objc public func getISOMin() -> Int32{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getISOMin m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0
        }
        return Int32((m_captureDevice?.activeFormat.minISO)!)
    }
    
    func toFocusMode(mode:GBCameraFocusMode) -> AVCaptureFocusMode {
        switch mode {
        case GBCameraFocusMode.Locked:
            return AVCaptureFocusMode.Locked
        case GBCameraFocusMode.AutoFocus:
            return AVCaptureFocusMode.AutoFocus
        case GBCameraFocusMode.ContinuousAutoFocus:
            return AVCaptureFocusMode.ContinuousAutoFocus
        default:
            break
        }
        GBLogGen.instance()?.logerrf("toFocusMode unsport mode:\(mode) \(#file) \(#function) \(#line)");
        return AVCaptureFocusMode.AutoFocus
    }
    
    func toGBFocusMode(mode:AVCaptureFocusMode) -> GBCameraFocusMode {
        switch mode {
        case AVCaptureFocusMode.Locked:
            return GBCameraFocusMode.Locked
        case AVCaptureFocusMode.AutoFocus:
            return GBCameraFocusMode.AutoFocus
        case AVCaptureFocusMode.ContinuousAutoFocus:
            return GBCameraFocusMode.ContinuousAutoFocus
        default:
            break
        }
        GBLogGen.instance()?.logerrf("toGBFocusMode unsport mode:\(mode) \(#file) \(#function) \(#line)");
        return GBCameraFocusMode.None
    }
    
    @objc public func setFocusMode(mode: GBCameraFocusMode){
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
    
    @objc public func getFocusMode() -> GBCameraFocusMode{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getFocusModel m_captureDevice nil \(#file) \(#function) \(#line)");
            return GBCameraFocusMode.None
        }
        return toGBFocusMode((m_captureDevice?.focusMode)!)
    }
    
    /** lens form 0.0 to 1.0, shortest to furthest */
    @objc public func setFocusLens(lens: Float){
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
    
    @objc public func getFocusLens() -> Float{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0
        }
        return m_captureDevice!.lensPosition
    }
    
    @objc public func getFocusMax() -> Float {
        return 1.0
    }
    
    @objc public func getFocusMin() -> Float {
        return 0.0
    }
    
    @objc public func setFocusPoint(x: Float, y: Float){
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("setFocusPoint m_captureDevice nil \(#file) \(#function) \(#line)");
            return
        }
        if !(m_captureDevice?.focusPointOfInterestSupported)!{
            GBLogGen.instance()?.logerrf("setFocusPoint unsupport \(#file) \(#function) \(#line)");
            return
        }
        do {
            try m_captureDevice!.lockForConfiguration()
            m_captureDevice?.focusPointOfInterest = CGPoint(x: Double(x), y: Double(y))
            m_captureDevice?.focusMode = AVCaptureFocusMode.ContinuousAutoFocus
            m_captureDevice?.unlockForConfiguration()
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("setFocusPoint err:\(error) \(#file) \(#function) \(#line)");
        }
    }
    
    func toAVCaptureAutoFocusRangeRestriction(range:GBCameraFocusRange) -> AVCaptureAutoFocusRangeRestriction {
        switch range {
        case GBCameraFocusRange.None:
            return AVCaptureAutoFocusRangeRestriction.None
        case GBCameraFocusRange.Near:
            return AVCaptureAutoFocusRangeRestriction.Near
        case GBCameraFocusRange.Far:
            return AVCaptureAutoFocusRangeRestriction.Far
        default:
            break
        }
        return AVCaptureAutoFocusRangeRestriction.None
    }
    
    func toGBFocusRange(range:AVCaptureAutoFocusRangeRestriction) -> GBCameraFocusRange {
        switch range {
        case AVCaptureAutoFocusRangeRestriction.None:
            return GBCameraFocusRange.None
        case AVCaptureAutoFocusRangeRestriction.Near:
            return GBCameraFocusRange.Near
        case AVCaptureAutoFocusRangeRestriction.Far:
            return GBCameraFocusRange.Far
        default:
            break
        }
        return GBCameraFocusRange.None
    }
    
    @objc public func setFocusAutoRange(range: GBCameraFocusRange){
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("setFocusAutoRange m_captureDevice nil \(#file) \(#function) \(#line)")
            return
        }
        if !(m_captureDevice?.autoFocusRangeRestrictionSupported)!{
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
    
    @objc public func getFocusAutoRange() -> GBCameraFocusRange{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getFocusAutoRange m_captureDevice nil \(#file) \(#function) \(#line)")
            return toGBFocusRange(AVCaptureAutoFocusRangeRestriction.None)
        }
        
        return toGBFocusRange((m_captureDevice?.autoFocusRangeRestriction)!)
    }

    
    @objc public func setZoom(zoom: Float){
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
    
    @objc public func getZoom() -> Float{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getZoom m_captureDevice nil \(#file) \(#function) \(#line)")
            return 0.0
        }
        return Float((m_captureDevice?.videoZoomFactor)!)
    }
    
    /** minimum value is 1.0 */
    @objc public func getZoomMax() -> Float{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("getMaxZoom m_captureDevice nil \(#file) \(#function) \(#line)")
            return 1.0
        }
        return Float((m_captureDevice?.activeFormat.videoMaxZoomFactor)!)
    }
    
    @objc public func getZoomMin() -> Float {
        return 1.0
    }
    
    @objc public func setFramePhoto(flag: Bool) {
        m_frame_photo = flag
    }
    
    @objc public func captureOneFrame() -> GBVideoFrameGen? {
        if nil == m_cmbuffer {
            return nil
        }

        return ObjcUtility.toVideoFrame(m_cmbuffer!)
    }
    
    @objc public func asnyOnePicture(){
        let capture_connection:AVCaptureConnection = self.m_stillImageOutput.connectionWithMediaType(AVMediaTypeVideo)
        //let curent_device_orientation:UIDeviceOrientation = UIDevice.currentDevice().orientation
        //let av_orientation:AVCaptureVideoOrientation = self.orientationDevice2AV(curent_device_orientation)
        capture_connection.videoOrientation = AVCaptureVideoOrientation.LandscapeRight
        //capture_connection.videoScaleAndCropFactor = 1.0
        
        m_stillImageOutput.captureStillImageAsynchronouslyFromConnection(capture_connection,
         completionHandler:{ (sampleBuffer, error) -> Void in
            // ...
            // Process the image data (sampleBuffer) here to get an image file we can put in our captureImageView
            self.m_cmbuffer = sampleBuffer
            let err_msg:String = (error != nil) ? error.description : ""
            
            if nil == sampleBuffer{
                GBLogGen.instance()?.logerrf("sampleBuffer nil, err:\(err_msg) \(#file) \(#function) \(#line)")
                return
            }
            
            if self.m_capture_image && self.m_capture_image_handler != nil {
                let imageData = AVCaptureStillImageOutput.jpegStillImageNSDataRepresentation(sampleBuffer)
                let dataProvider = CGDataProviderCreateWithCFData(imageData)
                let cgImageRef = CGImageCreateWithJPEGDataProvider(dataProvider, nil, true, CGColorRenderingIntent.RenderingIntentDefault)
                let image = UIImage(CGImage: cgImageRef!)
                
                self.m_capture_image_handler?.captureOutput(image, error: err_msg)
            }
            else if self.m_capture_handler != nil {
                self.m_capture_handler?.captureOutput(ObjcUtility.toVideoFrame(sampleBuffer), error: err_msg)
            }
        })
    }
    
    @objc public func asnyOneFrame() {
        if m_frame_photo {
            asnyOnePicture()
            return
        }
        let frame = self.captureOneFrame()
        
        if self.m_capture_handler != nil && frame != nil{
            self.m_capture_handler?.captureOutput(frame, error: "")
        }
    }
    
    @objc public func setCaptureHandler(handler: GBCameraCaptureHandler?){
        m_capture_handler = handler
    }

    func asnyOnePictureUIImage() {
        m_capture_image = true
        self.asnyOnePicture()
    }
    func setCapturePictureHandler(handler:CapturePictureHandler?) -> Void {
        m_capture_image_handler = handler
    }
    public func rotate(){
        m_previewLayer?.frame = UIScreen.mainScreen().bounds
    }
    
    func rotateScreen() {
        let ori:UIInterfaceOrientation = UIApplication.sharedApplication().statusBarOrientation
        
        if ori == UIInterfaceOrientation.LandscapeRight  {
            m_previewLayer?.connection.videoOrientation = AVCaptureVideoOrientation.LandscapeRight
        }
        else if ori == UIInterfaceOrientation.LandscapeLeft {
            m_previewLayer?.connection.videoOrientation = AVCaptureVideoOrientation.LandscapeLeft
        }
    }
    
    private func requestCamera(type: AVCaptureDevicePosition, addinput:Bool) -> Bool {
        for device in AVCaptureDevice.devices() {
            if (device.hasMediaType(AVMediaTypeVideo)) {
                if(device.position == type) {
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
    
    private func outputToView(view:UIView){
        
        //previewLayer.videoGravity = AVLayerVideoGravityResizeAspectFill; // 设置预览时的视频缩放方式
        //[[previewLayer connection] setVideoOrientation:AVCaptureVideoOrientationPortrait]; // 设置视频的朝向
        //m_stillImageOutput.outputSettings = [AVVideoCodecKey: AVVideoCodecJPEG]

        let dctPixelFormatType : Dictionary<NSString, NSNumber> = [kCVPixelBufferPixelFormatTypeKey : NSNumber(unsignedInt: kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange)]
        
        m_stillImageOutput.outputSettings = dctPixelFormatType

        if m_captureSession.canAddOutput(m_stillImageOutput) {
            m_captureSession.addOutput(m_stillImageOutput)
        }
        
        m_previewLayer = AVCaptureVideoPreviewLayer(session: m_captureSession)
        m_previewLayer?.videoGravity = AVLayerVideoGravityResizeAspectFill
        m_previewLayer?.frame = UIScreen.mainScreen().bounds
        
        m_previewLayer?.connection.videoOrientation = AVCaptureVideoOrientation.LandscapeRight
        view.layer.addSublayer(m_previewLayer!)
    }
    
    private func outputToBuffer(){
        // Acquisition of output data
        let videoDataOutput:AVCaptureVideoDataOutput = AVCaptureVideoDataOutput()
        
        // Set of color channel
        let dctPixelFormatType : Dictionary<NSString, NSNumber> = [kCVPixelBufferPixelFormatTypeKey : NSNumber(unsignedInt: kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange)]
        videoDataOutput.videoSettings = dctPixelFormatType
        videoDataOutput.alwaysDiscardsLateVideoFrames = true
        
        // Specified queue to capture the image
        //var videoDataOutputQueue: dispatch_queue_t = dispatch_queue_create("CtrlVideoQueue", DISPATCH_QUEUE_SERIAL)
        videoDataOutput.setSampleBufferDelegate(self, queue: dispatch_get_main_queue())
        videoDataOutput.alwaysDiscardsLateVideoFrames = true
        
        if m_captureSession.canAddOutput(videoDataOutput) {
            m_captureSession.addOutput(videoDataOutput)
        }
    }
    
    private func orientationDevice2AV(device:UIDeviceOrientation) -> AVCaptureVideoOrientation {
        switch device {
        case UIDeviceOrientation.LandscapeLeft:
            return AVCaptureVideoOrientation.LandscapeLeft
        case UIDeviceOrientation.LandscapeRight:
            return AVCaptureVideoOrientation.LandscapeRight
        default:
            break
        }
        
        GBLogGen.instance()?.logerrf("orientationDevice2AV unexpected device orientation \(device) \(#file) \(#function) \(#line)");
        return AVCaptureVideoOrientation.Portrait
    }
    
    private let m_devices = AVCaptureDevice.devices()
    private var m_captureDevice : AVCaptureDevice?
    private let m_captureSession = AVCaptureSession()
    private var m_cameraPosition = AVCaptureDevicePosition.Back
    
    private var m_previewLayer : AVCaptureVideoPreviewLayer?
    private let m_stillImageOutput = AVCaptureStillImageOutput()
    private var m_cmbuffer:CMSampleBuffer?
    private var m_isfront:Bool = false
    private var m_quality:GBCameraQuality = GBCameraQuality.None
    
    private var m_capture_handler: GBCameraCaptureHandler?
    private var m_capture_image_handler: CapturePictureHandler?
    private var m_capture_image:Bool = false
    private var m_frame_photo:Bool = false
    
    private var m_audio_enable: Bool = false
    private var m_audio_output: AVCaptureAudioDataOutput?
    private var m_audio_connection: AVCaptureConnection?
    private var m_audio_buffer: CMSampleBuffer?
}
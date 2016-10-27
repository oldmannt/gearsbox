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

fileprivate var m_last_tick:Double = 0
fileprivate var m_second_counter:Double = 0;
fileprivate var m_frame_counter:Double = 0
fileprivate var m_frame_rate:Double = 0
open class GBCameraControllerImp:  NSObject,GBCameraControllerGen,AVCaptureVideoDataOutputSampleBufferDelegate,AVCaptureAudioDataOutputSampleBufferDelegate {
    static let instance:GBCameraControllerImp = GBCameraControllerImp()
    
    @objc open func captureOutput(_ captureOutput: AVCaptureOutput!, didOutputSampleBuffer sampleBuffer: CMSampleBuffer!, from connection: AVCaptureConnection!) {
        if connection == self.m_audio_connection {
            m_audio_buffer = sampleBuffer
            let frame = GBVideoFrameImp(audio: sampleBuffer)
            if self.m_capture_handler != nil {
                self.m_capture_handler?.captureOutput(frame, error: "")
            }
        }
        else {
            //m_cmbuffer = sampleBuffer
            if self.m_capture_mode == .immediateVideo &&
                (self.m_capture_handler != nil) &&
                !m_immediate_pause {
                
                self.m_capture_handler?.captureOutput(GBVideoFrameImp(image: sampleBuffer), error: "")
            }
        }
        
        let elapse = CACurrentMediaTime()-m_last_tick
        m_second_counter+=elapse
        m_frame_counter += 1.0
        if m_second_counter >= 1.0 {
            m_frame_rate = m_frame_counter/m_second_counter;
            m_frame_counter = 0.0
            m_second_counter = 0.0
        }
        //print("capture lapsed:%f", CACurrentMediaTime()-m_last_tick)
        m_last_tick = CACurrentMediaTime()
    }

    open func initializ_swif(_ view:PreviewView, complition:@escaping (Bool, String?) -> Swift.Void ){
        self.m_previewLayer = view.videoPreviewLayer
        view.session = self.m_captureSession
        
        self.m_session_queue.async {[unowned self] in
            self.configureSession(complition: complition)
        }

    }
    
    // Call this on the session queue.
    private func configureSession(complition: (Bool, String?) -> Swift.Void) {
        m_captureSession.beginConfiguration()
        
        /*
         We do not create an AVCaptureMovieFileOutput when setting up the session because the
         AVCaptureMovieFileOutput does not support movie recording with AVCaptureSessionPresetPhoto.
         */
        m_captureSession.sessionPreset = AVCaptureSessionPreset1280x720
        
        // Add video input.
        do {
            var defaultVideoDevice: AVCaptureDevice?
            
            // Choose the back dual camera if available, otherwise default to a wide angle camera.
            if #available(iOS 10.0, *) {
                if let dualCameraDevice = AVCaptureDevice.defaultDevice(withDeviceType: .builtInDuoCamera, mediaType: AVMediaTypeVideo, position: .back) {
                    defaultVideoDevice = dualCameraDevice
                }
                else if let backCameraDevice = AVCaptureDevice.defaultDevice(withDeviceType: .builtInWideAngleCamera, mediaType: AVMediaTypeVideo, position: .back) {
                    // If the back dual camera is not available, default to the back wide angle camera.
                    defaultVideoDevice = backCameraDevice
                }
                else if let frontCameraDevice = AVCaptureDevice.defaultDevice(withDeviceType: .builtInWideAngleCamera, mediaType: AVMediaTypeVideo, position: .front) {
                    // In some cases where users break their phones, the back wide angle camera is not available. In this case, we should default to the front wide angle camera.
                    defaultVideoDevice = frontCameraDevice
                }
            } else {
                // Fallback on earlier versions
                defaultVideoDevice = GBCameraControllerImp.deviceWithMediaType(type: AVMediaTypeVideo, position: .back)
            }
            m_captureDevice = defaultVideoDevice
            
            let videoDeviceInput = try AVCaptureDeviceInput(device: defaultVideoDevice)
            
            if m_captureSession.canAddInput(videoDeviceInput) {
                m_captureSession.addInput(videoDeviceInput)
                self.m_video_device_input = videoDeviceInput
                
                DispatchQueue.main.async {
                    /*
                     Why are we dispatching this to the main queue?
                     Because AVCaptureVideoPreviewLayer is the backing layer for PreviewView and UIView
                     can only be manipulated on the main thread.
                     Note: As an exception to the above rule, it is not necessary to serialize video orientation changes
                     on the AVCaptureVideoPreviewLayer’s connection with other session manipulation.
                     
                     Use the status bar orientation as the initial video orientation. Subsequent orientation changes are
                     handled by CameraViewController.viewWillTransition(to:with:).
                     */
                    let initialVideoOrientation: AVCaptureVideoOrientation = .landscapeLeft
                    /*
                    let statusBarOrientation = UIApplication.shared.statusBarOrientation
                    if statusBarOrientation != .unknown {
                        if let videoOrientation = statusBarOrientation.videoOrientation {
                            initialVideoOrientation = videoOrientation
                        }
                    }
                    */
                    self.m_previewLayer?.connection.videoOrientation = initialVideoOrientation
                }
            }
            else {
                let msg = "Could not add video device input to the session"
                GBLogGen.instance()?.logerrf("\(msg) \(#file) \(#function) \(#line)");
                //setupResult = .configurationFailed
                m_captureSession.commitConfiguration()
                complition(false, msg)
                return
            }
        }
        catch {
            let msg = "Could not create video device input:  \(error)"
            GBLogGen.instance()?.logerrf("\(msg) \(#file) \(#function) \(#line)");
            //setupResult = .configurationFailed
            m_captureSession.commitConfiguration()
            complition(false, msg)
            return
        }
        
        if self.m_audio_enable {
            // Add audio input.
            do {
                let audioDevice = AVCaptureDevice.defaultDevice(withMediaType: AVMediaTypeAudio)
                let audioDeviceInput = try AVCaptureDeviceInput(device: audioDevice)
                
                if m_captureSession.canAddInput(audioDeviceInput) {
                    m_captureSession.addInput(audioDeviceInput)
                }
                else {
                    GBLogGen.instance()?.logerrf("Could not add audio device input to the session:  \(#file) \(#function) \(#line)");
                }
            }
            catch {
                GBLogGen.instance()?.logerrf("Could not create audio device input: \(error) \(#file) \(#function) \(#line)");
            }
        }
        
        // for take photo
        let dctPixelFormatType : Dictionary<NSString, NSNumber> = [kCVPixelBufferPixelFormatTypeKey : NSNumber(value: kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange as UInt32)]
        self.m_stillImageOutput.outputSettings = dctPixelFormatType
        //self.m_stillImageOutput.isHighResolutionStillImageOutputEnabled = true
        if self.m_captureSession.canAddOutput(self.m_stillImageOutput) {
            self.m_captureSession.addOutput(self.m_stillImageOutput)
        }
        
        DispatchQueue.main.async {[unowned self] in
            self.m_previewLayer?.videoGravity = AVLayerVideoGravityResizeAspectFill
            self.m_previewLayer?.frame = UIScreen.main.bounds
            
            self.m_previewLayer?.connection.videoOrientation = AVCaptureVideoOrientation.landscapeRight
        }
        
        // Acquisition of output data
        let videoDataOutput:AVCaptureVideoDataOutput = AVCaptureVideoDataOutput()
        // Set of color channel
        videoDataOutput.videoSettings = dctPixelFormatType
        // Specified queue to capture the image
        videoDataOutput.setSampleBufferDelegate(self, queue: DispatchQueue.main)
        videoDataOutput.alwaysDiscardsLateVideoFrames = true
        if self.m_captureSession.canAddOutput(videoDataOutput) {
            self.m_captureSession.addOutput(videoDataOutput)
        }

        // Add photo output. todo
        /*
        if session.canAddOutput(photoOutput)
        {
            session.addOutput(photoOutput)
            
            photoOutput.isHighResolutionCaptureEnabled = true
            photoOutput.isLivePhotoCaptureEnabled = photoOutput.isLivePhotoCaptureSupported
            livePhotoMode = photoOutput.isLivePhotoCaptureSupported ? .on : .off
        }
        else {
            print("Could not add photo output to the session")
            setupResult = .configurationFailed
            session.commitConfiguration()
            return
        } */
        
        self.initializeDeviceFormat()
        self.setFrameDuration(1, scale: 30)
        
        self.m_captureSession.commitConfiguration()
        
        if self.m_captureDevice == nil{
            let msg = "request camera failed, m_captureDevice nil"
            GBLogGen.instance()?.logerrf("\(msg) \(#file) \(#function) \(#line)");
            complition(false, msg)
        }
        
        complition(true, nil)
    }
    
    fileprivate func initializeDeviceFormat(){
        m_default_device_format = m_captureDevice?.activeFormat
        let default_ranges = m_captureDevice?.activeFormat.videoSupportedFrameRateRanges as! [AVFrameRateRange]
        m_default_frame_rate = default_ranges[0]
        
        //print("default max_frame_duration:\(default_ranges)")
        //print("\(m_captureDevice?.formats.count)")
        var max_frame_rate:Float64 = 0.0
        for format in m_captureDevice!.formats {
            let ranges = (format as AnyObject).videoSupportedFrameRateRanges as! [AVFrameRateRange]
            let frame_range = ranges[0]
            if frame_range.maxFrameRate > max_frame_rate {
                max_frame_rate = frame_range.maxFrameRate
                m_max_frame_rate = frame_range
                m_maxframe_device_format = format as? AVCaptureDeviceFormat
            }
        }// end for
        //print("default max_frame_duration:\(m_maxframe_device_format?.videoSupportedFrameRateRanges as! [AVFrameRateRange])")
    }
    
    @objc open func setFrameDuration(_ value: Int64, scale: Int32) {
        let duration = CMTimeMake(value, Int32(scale))
        if duration < m_max_frame_rate?.minFrameDuration {
            GBLogGen.instance()?.logerrf("unsuport duraton, vaule:\(value) scale:\(scale) \(#file) \(#function) \(#line)");
            return
        }
        
        if duration < m_default_frame_rate?.minFrameDuration &&
            m_captureDevice?.activeFormat != m_maxframe_device_format {
            self.setSloMo(true)
        }
        
        do {
            try m_captureDevice!.lockForConfiguration()
            m_captureDevice?.activeVideoMaxFrameDuration = duration;
            m_captureDevice?.activeVideoMinFrameDuration = duration;
            m_captureDevice?.unlockForConfiguration()
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("setFrameDuration err:\(error) \(#file) \(#function) \(#line)");
        }        
    }
    
    public func getFrameDuration() -> GBDuration{
        let duration:CMTime = (m_captureDevice?.activeVideoMaxFrameDuration)!
        return GBDuration(value: duration.value, scale: duration.timescale);
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
        m_session_queue.async { [unowned self] in
            self.m_captureSession.startRunning()
        }
    }
    
    @objc open func stopCamera(){
        m_session_queue.async { [unowned self] in
         self.m_captureSession.stopRunning()
        }
    }
    
    @objc open func switchFront(_ front: Bool) {
        if m_isfront == front {
            return
        }
        
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
        
        m_session_queue.async {[unowned self] in
            if self.m_captureDevice == nil {
                return
            }
            let camera_flash:AVCaptureFlashMode = self.toFlashMode(mode)
            if !(self.m_captureDevice?.isFlashModeSupported(camera_flash))! {
                return
            }
            do {
                try self.m_captureDevice?.lockForConfiguration()
                self.m_captureDevice?.flashMode = camera_flash
                self.m_captureDevice?.unlockForConfiguration()
            }  catch let error as NSError {
                GBLogGen.instance()?.logerrf("setFlash failed err:\(error) \(#file) \(#function) \(#line)");
                return
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
        GBCameraConfigGen.instance()?.setQuatityLevel(quality)
        
        m_session_queue.async {[unowned self] in
            var sessionPreset = AVCaptureSessionPreset1280x720
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
            self.m_captureSession.beginConfiguration()
            self.m_captureSession.sessionPreset = sessionPreset
            self.m_captureSession.commitConfiguration()
        }
    }
    
    @objc open func getQuality() -> GBCameraQuality{
        return m_quality
    }
    
    public func setSloMo(_ flag: Bool) {
        do {
            try m_captureDevice?.lockForConfiguration()
            m_captureDevice?.activeFormat = self.m_maxframe_device_format
            m_captureDevice?.unlockForConfiguration()
        }  catch let error as NSError {
            GBLogGen.instance()?.logerrf("setSloMo failed err:\(error) \(#file) \(#function) \(#line)");
            return
        }
    }
    
    public func getSloMo() -> Bool{
        if m_captureDevice?.activeFormat == self.m_maxframe_device_format &&
            nil != self.m_maxframe_device_format {
            return true
        }
        return false
    }
    
    public func getMaxFrameRate() -> Int32 {
        return Int32((m_max_frame_rate?.maxFrameRate)!)
    }
    
    public func getDefaultFrameRate() -> Int32 {
        return Int32((m_default_frame_rate?.maxFrameRate)!)
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
        self.setFlashMode(.off)
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
        
        var t = CMTime(seconds: Double(seconds), preferredTimescale: CMTimeScale(1000000))
        if t < m_captureDevice?.activeFormat.minExposureDuration{
            t = (m_captureDevice?.activeFormat.minExposureDuration)!
        }

        do {
            try m_captureDevice!.lockForConfiguration()
            m_captureDevice?.setExposureModeCustomWithDuration(t, iso: AVCaptureISOCurrent, completionHandler: nil)
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
    
    public func getEV() -> Float{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0.0
        }
        return m_captureDevice!.exposureTargetBias
    }
    
    public func setEV(_ ev: Float){
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("m_captureDevice nil \(#file) \(#function) \(#line)");
            return
        }
        do {
            try m_captureDevice!.lockForConfiguration()
            m_captureDevice?.setExposureTargetBias(ev, completionHandler: nil)
            m_captureDevice?.unlockForConfiguration()
        } catch let error as NSError {
            GBLogGen.instance()?.logerrf("setISO err:\(error) \(#file) \(#function) \(#line)");
        }
    }
    
    public func getEVMax() -> Float{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0.0
        }
        return m_captureDevice!.maxExposureTargetBias
    }
    
    public func getEVMin() -> Float{
        if m_captureDevice == nil {
            GBLogGen.instance()?.logerrf("m_captureDevice nil \(#file) \(#function) \(#line)");
            return 0.0
        }
        return m_captureDevice!.minExposureTargetBias
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

        return GBVideoFrameImp(image: m_cmbuffer!)
    }
    
    var m_taking_photo = false
    @objc open func asnyOnePicture(){
        if m_taking_photo {
            print("m_taking_photo")
            return
        }
        m_taking_photo = true
        m_session_queue.async {[unowned self] in
            let capture_connection:AVCaptureConnection = self.m_stillImageOutput.connection(withMediaType: AVMediaTypeVideo)
            capture_connection.videoOrientation = AVCaptureVideoOrientation.landscapeRight
            
            self.m_stillImageOutput.captureStillImageAsynchronously(from: capture_connection,
               completionHandler:{ (sampleBuffer, error) -> Void in

                DispatchQueue.main.async {[unowned self] in
                    self.m_taking_photo = false
                    self.m_cmbuffer = sampleBuffer
                    let err_msg:String = (error != nil) ? error.debugDescription : ""
                    
                    if nil == sampleBuffer{
                        GBLogGen.instance()?.logerrf("sampleBuffer nil, err:\(err_msg) \(#file) \(#function) \(#line)")
                        return
                    }
                    
                    if self.m_capture_mode == .photo && self.m_capture_handler != nil {
                        self.m_capture_handler?.captureOutput(GBVideoFrameImp(image: sampleBuffer!), error: err_msg)
                    }
                    else if self.m_capture_image_handler != nil {
                        /*
                        let imageData = AVCaptureStillImageOutput.jpegStillImageNSDataRepresentation(sampleBuffer)
                        let dataProvider = CGDataProvider(data: imageData as! CFData)
                        let cgImageRef = CGImage(jpegDataProviderSource: dataProvider!, decode: nil, shouldInterpolate: true, intent: CGColorRenderingIntent.defaultIntent)
                        let image = UIImage(cgImage: cgImageRef!)
                        
                        self.m_capture_image_handler?.captureOutput(image, error: err_msg)
                        */
                    }
                } // end sync main
                
            }) // end capture
        } // end sync session
        
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
    
    fileprivate func outputToView(_ view:UIView){
        m_session_queue.async {[unowned self] in
            //previewLayer.videoGravity = AVLayerVideoGravityResizeAspectFill; // 设置预览时的视频缩放方式
            //[[previewLayer connection] setVideoOrientation:AVCaptureVideoOrientationPortrait]; // 设置视频的朝向
            //m_stillImageOutput.outputSettings = [AVVideoCodecKey: AVVideoCodecJPEG]
            
            let dctPixelFormatType : Dictionary<NSString, NSNumber> = [kCVPixelBufferPixelFormatTypeKey : NSNumber(value: kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange as UInt32)]
            
            self.m_stillImageOutput.outputSettings = dctPixelFormatType
            self.m_stillImageOutput.isHighResolutionStillImageOutputEnabled = true
            
            if self.m_captureSession.canAddOutput(self.m_stillImageOutput) {
                self.m_captureSession.addOutput(self.m_stillImageOutput)
            }
            
            DispatchQueue.main.async {[unowned self] in
                self.m_previewLayer = AVCaptureVideoPreviewLayer(session: self.m_captureSession)
                self.m_previewLayer?.videoGravity = AVLayerVideoGravityResizeAspectFill
                self.m_previewLayer?.frame = UIScreen.main.bounds
                
                self.m_previewLayer?.connection.videoOrientation = AVCaptureVideoOrientation.landscapeRight
                view.layer.addSublayer(self.m_previewLayer!)
            }
        }
        
    }
    
    fileprivate func outputToBuffer(){
        
        m_session_queue.async {[unowned self] in
            // Acquisition of output data
            let videoDataOutput:AVCaptureVideoDataOutput = AVCaptureVideoDataOutput()
            
            // Set of color channel
            let dctPixelFormatType : Dictionary<NSString, NSNumber> = [kCVPixelBufferPixelFormatTypeKey : NSNumber(value: kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange as UInt32)]
            videoDataOutput.videoSettings = dctPixelFormatType
            
            // Specified queue to capture the image
            //var videoDataOutputQueue: dispatch_queue_t = dispatch_queue_create("CtrlVideoQueue", DISPATCH_QUEUE_SERIAL)
            videoDataOutput.setSampleBufferDelegate(self, queue: DispatchQueue.main)
            videoDataOutput.alwaysDiscardsLateVideoFrames = true
            
            if self.m_captureSession.canAddOutput(videoDataOutput) {
                self.m_captureSession.addOutput(videoDataOutput)
            }
        }// end async
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
    
    static func deviceWithMediaType(type: String, position: AVCaptureDevicePosition) -> AVCaptureDevice{
        let devices = AVCaptureDevice.devices(withMediaType: type)
        var capture_device = devices?.first as? AVCaptureDevice
        for device in AVCaptureDevice.devices() {
            if ((device as AnyObject).hasMediaType(AVMediaTypeVideo)) {
                if((device as AnyObject).position == position) {
                    capture_device = device as? AVCaptureDevice
                }
            }
        }// end for
        return capture_device!
    }
    
    fileprivate var m_captureDevice : AVCaptureDevice?
    fileprivate var m_video_device_input: AVCaptureDeviceInput!
    fileprivate let m_captureSession = AVCaptureSession()
    fileprivate var m_cameraPosition = AVCaptureDevicePosition.back
    
    fileprivate var m_default_device_format:AVCaptureDeviceFormat?
    fileprivate var m_maxframe_device_format:AVCaptureDeviceFormat?
    fileprivate var m_max_frame_rate:AVFrameRateRange?
    fileprivate var m_default_frame_rate:AVFrameRateRange?
    
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
    
    fileprivate let m_session_queue = DispatchQueue(label: "session queue", attributes: [], target: nil)
    
    
    open func getDebugInfo() -> String {
        var text:String = ""
        
        let duration:CMTime = (m_captureDevice?.exposureDuration)!
        let duration_max:Double = (m_captureDevice?.activeFormat.maxExposureDuration.seconds)!
        let duration_min:Double = (m_captureDevice?.activeFormat.minExposureDuration.seconds)!

        let duration_model = GBCameraControllerImp.instance.getExposureMode()
        
        let iso:Float = (m_captureDevice?.iso)!
        let iso_max:Float = (m_captureDevice?.activeFormat.maxISO)!
        let iso_min:Float = (m_captureDevice?.activeFormat.minISO)!
        
        let focus:Float = m_captureDevice!.lensPosition
        let focus_max:Float = 1.0
        let focus_min:Float = 0
        let focus_model = GBCameraControllerImp.instance.getFocusMode()
        let focus_range = GBCameraControllerImp.instance.getFocusAutoRange()
        
        let zoom:Float = Float((m_captureDevice?.videoZoomFactor)!)
        let zoom_max:Float = Float((m_captureDevice?.activeFormat.videoMaxZoomFactor)!)
        
        let frame_duration:CMTime = (m_captureDevice?.activeVideoMaxFrameDuration)!
        
        text += String.init(format: "exposure %d:%d second:%.03f max:%.03f min:%.03f mode:%d\n",
                           duration.value/1000,duration.timescale/1000, duration.seconds,
                           duration_max, duration_min, duration_model.rawValue);
        text += String.init(format: "iso:%.01f max:%.01f min:%.01f\n", iso, iso_max, iso_min);
        text += String.init(format: "focus: %.03f max:%.03f min:%.03f mode:%d range:%d\n",
                            focus, focus_max, focus_min, focus_model.rawValue, focus_range.rawValue);
        text += String("zoom: \(zoom) max:\(zoom_max)\n")
        text += String.init(format: "frame duration:%d/%d seconds:%.03f\n",
                            frame_duration.value, frame_duration.timescale, Float(frame_duration.value)/Float(frame_duration.timescale))
        text += String.init(format: "fps:%.02f", m_frame_rate)
        
        return text
    }
}

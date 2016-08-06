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

public class GBCameraControllerImp:  NSObject,GBCameraControllerGen,AVCaptureVideoDataOutputSampleBufferDelegate {
    
    @objc public func captureOutput(captureOutput: AVCaptureOutput!, didOutputSampleBuffer sampleBuffer: CMSampleBuffer!, fromConnection connection: AVCaptureConnection!) {
        
        m_cmbuffer = sampleBuffer
    }

    public func initializ_swif(view:UIView) -> Bool{
        requestCamera(m_cameraPosition, addinput: true)
        if m_captureDevice == nil{
            GBLogGen.instance()?.logerrf("request camera failed \(#file) \(#function) \(#line)");
            return false
        }
        
        m_captureDevice?.activeVideoMaxFrameDuration = CMTimeMake(1, Int32(30));
        outputToView(view)
        outputToBuffer()
        return true
    }
    
    @objc public func startCamera(){
        m_captureSession.startRunning()
    }
    
    @objc public func stopCamera(){
        m_captureSession.stopRunning()
    }
    
    @objc public func setFlash(mode: GBCameraFlash){
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
        default: break
        }
        
        for device in AVCaptureDevice.devicesWithMediaType(AVMediaTypeVideo) {
            let captureDevice = device as! AVCaptureDevice
            if (captureDevice.isFlashModeSupported(camera_flash)) {
                do {
                    try captureDevice.lockForConfiguration()
                    m_captureSession.beginConfiguration()
                    captureDevice.flashMode = camera_flash
                    m_captureSession.commitConfiguration()
                    captureDevice.unlockForConfiguration()
                } catch {
                    GBLogGen.instance()?.logerrf("setFlash lockForConfiguration failed \(#file) \(#function) \(#line)");
                    return
                }
            }
        }
    }
    
    @objc public func setQuality(quality: GBCameraQuality) {
        if m_quality == quality {
            return
        }
        var sessionPreset = AVCaptureSessionPreset640x480
        switch (quality) {
        case GBCameraQuality.P288:
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
    
    @objc public func getFlash() -> GBCameraFlash {
        return m_flash
    }
    
    @objc public func getQuality() -> GBCameraQuality{
        return m_quality
    }
    
    @objc public func setFousePoint(x: Int32, y: Int32){
        
    }
    
    @objc public func setExposurePoint(x: Int32, y: Int32){
        
    }
    
    @objc public func setZoom(zoom: Float){
        m_zoom = zoom
    }
    
    @objc public func getZoom() -> Float{
        return m_zoom;
    }
    
    @objc public func setISO(iso: Int32){
        m_iso = iso
    }
    
    @objc public func getISO() -> Int32{
        return m_iso
    }
    
    @objc public func setShutter(shutter: Int32){
        m_shutter = shutter
    }
    
    @objc public func getShutter() -> Int32{
        return m_shutter
    }
    
    @objc public func setAperture(f: Float){
        m_aperture = f
    }
    
    @objc public func getAperture() -> Float{
        return m_aperture
    }
    
    @objc public func captureOneFrame() -> GBVideoFrameGen? {

        if nil == m_cmbuffer {
            return nil
        }

        return ObjcUtility.toVideoFrame(m_cmbuffer!)
    }
    
    public func rotate(){
        m_previewLayer?.frame = UIScreen.mainScreen().bounds
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
        
        m_stillImageOutput.outputSettings = [AVVideoCodecKey: AVVideoCodecJPEG]
        m_captureSession.sessionPreset = AVCaptureSessionPreset640x480
        
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
    
    private let m_devices = AVCaptureDevice.devices()
    private var m_captureDevice : AVCaptureDevice?
    private let m_captureSession = AVCaptureSession()
    private var m_cameraPosition = AVCaptureDevicePosition.Back
    
    private var m_previewLayer : AVCaptureVideoPreviewLayer?
    private let m_stillImageOutput = AVCaptureStillImageOutput()
    private var m_cmbuffer:CMSampleBuffer?
    private var m_isfront:Bool = false
    private var m_flash:GBCameraFlash = GBCameraFlash.Auto
    private var m_quality:GBCameraQuality = GBCameraQuality.P480
    private var m_zoom: Float32 = 0.0
    private var m_iso: Int32 = 0
    private var m_shutter: Int32 = 0
    private var m_aperture: Float32 = 0.0
}
/*
	Copyright (C) 2016 Apple Inc. All Rights Reserved.
	See LICENSE.txt for this sample’s licensing information
	
	Abstract:
	Photo capture delegate.
*/

import AVFoundation
import Photos

@available(iOS 10.0, *)
class PhotoCaptureDelegate: NSObject, AVCapturePhotoCaptureDelegate {
	private let m_willCapturePhotoAnimation: () -> ()?
	private let m_completed: (CMSampleBuffer?, String?) -> ()
	private var m_photoData: CMSampleBuffer? = nil
    private(set) var m_setting:AVCapturePhotoSettings
    init(with  setting:AVCapturePhotoSettings, completed: @escaping (CMSampleBuffer?, String?) -> (), willCapturePhotoAnimation: @escaping () -> ()) {
		self.m_willCapturePhotoAnimation = willCapturePhotoAnimation
		self.m_completed = completed
        self.m_setting = setting
	}
	
	func capture(_ captureOutput: AVCapturePhotoOutput, willCapturePhotoForResolvedSettings resolvedSettings: AVCaptureResolvedPhotoSettings) {
		m_willCapturePhotoAnimation()
	}
	
    func capture(_ captureOutput: AVCapturePhotoOutput, didFinishProcessingPhotoSampleBuffer photoSampleBuffer: CMSampleBuffer?, previewPhotoSampleBuffer: CMSampleBuffer?, resolvedSettings: AVCaptureResolvedPhotoSettings, bracketSettings: AVCaptureBracketedStillImageSettings?, error: Error?) {
        m_photoData = photoSampleBuffer!
		if nil != error {
			GBLogGen.instance()?.logerrf("capture buffer \(error) \(#file) \(#function) \(#line)");
		}
	}
	
    // all the capture were invoked in main thread
    func capture(_ captureOutput: AVCapturePhotoOutput, didFinishCaptureForResolvedSettings resolvedSettings: AVCaptureResolvedPhotoSettings, error: Error?) {
		if let error = error {
			GBLogGen.instance()?.logerrf("capture didfinish \(error) \(#file) \(#function) \(#line)");
			m_completed(nil, error.localizedDescription)
			return
		}
		m_completed(m_photoData, nil)
	}
}

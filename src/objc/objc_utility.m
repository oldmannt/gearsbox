//
//  objc_utility.m
//  lapse_app
//
//  Created by dyno on 7/24/16.
//  Copyright © 2016 dyno. All rights reserved.
//

#import "objc_utility.h"
#import "GBVideoInfoGen.h"
#import <UIKit/UIKit.h>

@implementation ObjcUtility

+(GBVideoFrameImp* _Nonnull)toVideoFrame:(CMSampleBufferRef)sampleBuffer{
    CVPixelBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    
    if (CVPixelBufferLockBaseAddress(imageBuffer, 0) != kCVReturnSuccess) {
        return Nil;
    }
    UInt8 *bufferbasePtr = (UInt8 *)CVPixelBufferGetBaseAddress(imageBuffer);
    UInt8 *bufferPtr = (UInt8 *)CVPixelBufferGetBaseAddressOfPlane(imageBuffer,0);
    UInt8 *bufferPtr1 =(UInt8 *)CVPixelBufferGetBaseAddressOfPlane(imageBuffer,1);
    size_t buffeSize = CVPixelBufferGetDataSize(imageBuffer);
    size_t width = CVPixelBufferGetWidth(imageBuffer);
    size_t height = CVPixelBufferGetHeight(imageBuffer);
    size_t bytesPerRow = CVPixelBufferGetBytesPerRow(imageBuffer);
    size_t bytesrow0 = CVPixelBufferGetBytesPerRowOfPlane(imageBuffer,0);
    size_t bytesrow1  = CVPixelBufferGetBytesPerRowOfPlane(imageBuffer,1);
    size_t bytesrow2 = CVPixelBufferGetBytesPerRowOfPlane(imageBuffer,2);
    UInt8 *yuv420_data = (UInt8 *)malloc(width * height *3/ 2); // buffer to store YUV with layout YYYYYYYYUUVV
    
    GBVideoFrameImp* video_frame = [[GBVideoFrameImp alloc] init];
    video_frame.m_data =(int64_t)yuv420_data;
    video_frame.m_size = (int64_t)buffeSize;
    video_frame.m_width = (int32_t)width;
    video_frame.m_height = (int32_t)height;

    
    /* convert NV12 data to YUV420*/
    UInt8 *pY = bufferPtr ;
    UInt8 *pUV = bufferPtr1;
    UInt8 *pU = yuv420_data + width*height;
    UInt8 *pV = pU + width*height/4;
    for(int i =0;i<height;i++){
        memcpy(yuv420_data+i*width,pY+i*bytesrow0,width);
    }
    for(int j = 0;j<height/2;j++){
        for(int i =0;i<width/2;i++){
            *(pU++) = pUV[i<<1];
            *(pV++) = pUV[(i<<1) + 1];
        }
        pUV+=bytesrow1;
    }

    CVPixelBufferUnlockBaseAddress(imageBuffer, 0);
    return video_frame;
}

+(UIImage* _Nullable)VideoFram2UIImage:(GBVideoFrameImp* _Nonnull)gbVideoFrame{
    int32_t width = [gbVideoFrame getWidth];
    int32_t height = [gbVideoFrame getHeight];
    int32_t linesize = [gbVideoFrame getLineSize];
    UInt8*  buffer = [gbVideoFrame getData];
    
    
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    CFDataRef data = CFDataCreateWithBytesNoCopy(kCFAllocatorDefault, buffer, linesize*height,kCFAllocatorNull);
    CGDataProviderRef provider = CGDataProviderCreateWithCFData(data);
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGImageRef cgImage = CGImageCreate(width,
                                       height,
                                       8,
                                       24,
                                       linesize,
                                       colorSpace,
                                       bitmapInfo,
                                       provider,
                                       NULL,
                                       NO,
                                       kCGRenderingIntentDefault);
    CGColorSpaceRelease(colorSpace);
    UIImage *image = [UIImage imageWithCGImage:cgImage];
    CGImageRelease(cgImage);
    CGDataProviderRelease(provider);
    CFRelease(data);
    
    return image;

}

+(UIImage* _Nullable)VideoReview2UIImage:(NSString* _Nonnull)video_path{
    GBVideoInfoGen *video_info = [GBVideoInfoGen getVideoInfo:video_path outWidth:0 outHeight:0];
    if (NULL == video_info){
        return NULL;
    }
    
    return [ObjcUtility VideoFram2UIImage:[video_info getVideoFrame]];
}

@end

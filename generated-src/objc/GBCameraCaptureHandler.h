// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#import <Foundation/Foundation.h>
@protocol GBVideoFrameGen;


@protocol GBCameraCaptureHandler

- (void)captureOutput:(nullable id<GBVideoFrameGen>)picture
                error:(nonnull NSString *)error;

@end
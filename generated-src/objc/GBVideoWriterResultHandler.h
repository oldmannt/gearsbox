// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#import <Foundation/Foundation.h>


@protocol GBVideoWriterResultHandler

- (void)onComplete:(BOOL)success
              path:(nonnull NSString *)path
          duration:(int32_t)duration;

/** there is frame in buffer, especially in slo-mo mode memory full */
- (void)beforeComplete;

- (void)onProgress:(float)percent;

@end

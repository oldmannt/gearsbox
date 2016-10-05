//
//  objc_utility.h
//  lapse_app
//
//  Created by dyno on 7/24/16.
//  Copyright © 2016 dyno. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreMedia/CoreMedia.h>
#import "GBVideoFrameGen.h"
#import "video_frame_imp.h"

@interface ObjcUtility : NSObject 

+(GBVideoFrameImp* _Nonnull)toVideoFrame:(CMSampleBufferRef _Nonnull)sampleBuffer;
+(GBVideoFrameImp* _Nonnull)toAudeoFrame:(CMSampleBufferRef _Nonnull)audioBuffer;
+(UIImage* _Nullable)VideoFram2UIImage:(GBVideoFrameImp* _Nonnull)gbVideoFrame;
+(UIImage* _Nullable)VideoReview2UIImage:(NSString* _Nonnull)video_path;
@end

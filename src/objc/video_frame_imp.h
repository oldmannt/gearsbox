//
//  video_frame_imp.h
//  lapse_app
//
//  Created by dyno on 7/25/16.
//  Copyright © 2016 dyno. All rights reserved.
//


#import <Foundation/Foundation.h>
#import "GBVideoFrameGen.h"

@interface GBVideoFrameImp : NSObject<GBVideoFrameGen>;
@property int64_t m_data;
@property int64_t m_size;
@property int32_t m_width;
@property int32_t m_height;
- (int64_t)getData;

- (int32_t)getWidth;

- (int32_t)getHeight;

- (int64_t)getSize;
@end

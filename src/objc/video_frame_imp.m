//
//  video_frame_imp.m
//  lapse_app
//
//  Created by dyno on 7/25/16.
//  Copyright © 2016 dyno. All rights reserved.
//

#import "video_frame_imp.h"

@implementation GBVideoFrameImp
@synthesize m_data;
@synthesize m_size;
@synthesize m_width;
@synthesize m_height;

-(id)init{
    m_data = 0;
    m_size = 0;
    m_width = 0;
    m_height = 0;
    return self;
}

- (int64_t)getData{
    return m_data;
}

- (int32_t)getWidth{
    return m_width;
}

- (int32_t)getHeight{
    return m_height;
}

- (int64_t)getSize{
    return m_size;
}

- (void)dealloc{
    void* ptr = (void*)m_data;
    free(ptr);
}
@end
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
@synthesize m_linesize;

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

- (int32_t)getLineSize{
    return m_linesize;
}

- (void)setData:(int64_t)data{
    m_data = data;
}

- (void)setWidth:(int32_t)width{
    m_width = width;
}

- (void)setHeight:(int32_t)height{
    m_height = height;
}

- (void)setSize:(int64_t)size{
    m_size = size;
}

- (void)setLineSize:(int32_t)linesize{
    m_linesize = linesize;
}

- (void)dealloc{
    void* ptr = (void*)m_data;
    free(ptr);
}

@end
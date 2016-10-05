//
//  video_frame_imp.m
//  lapse_app
//
//  Created by dyno on 7/25/16.
//  Copyright © 2016 dyno. All rights reserved.
//

#import "video_frame_imp.h"

#include "libavutil/mem.h"

@implementation GBVideoFrameImp
@synthesize m_data;
@synthesize m_size;
@synthesize m_width;
@synthesize m_height;
@synthesize m_linesize;
@synthesize m_audio_data;
@synthesize m_audio_data_size;
@synthesize m_audio_pts_value;
@synthesize m_audio_pts_scale;
@synthesize m_audio_num_sample;
@synthesize m_audio_channels_per_frame;
@synthesize m_audio_sample_rate;
@synthesize m_audio_bits_per_channel;
-(id)init{
    m_data = 0;
    m_size = 0;
    m_width = 0;
    m_height = 0;
    m_audio_data = 0;
    m_audio_data_size = 0;
    m_audio_pts_value = 0;
    m_audio_pts_scale = 0;
    return self;
}

- (void)dealloc{
    if (m_data!=0){
        void* ptr = (void*)m_data;
        free(ptr);
    }
    
    if (m_audio_data!=0){
        void* ptr = (void*)m_audio_data;
        free(ptr);
    }
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

- (int64_t)getAudioData{
    return m_audio_data;
}

- (int64_t)getAudioDataSize{
    return m_audio_data_size;
}

- (int64_t)getAudioPSTValue{
    return m_audio_pts_value;
}

- (int32_t)getAudioPSTScale{
    return m_audio_pts_scale;
}

- (int32_t)getNumSamples{
    return m_audio_num_sample;
}

- (int32_t)getChannelsPerFrame{
    return m_audio_channels_per_frame;
}

- (double)getSampleRate{
    return m_audio_sample_rate;
}

- (int32_t)getBitsPerChannel{
    return m_audio_bits_per_channel;
}

- (void)setAudioData:(int64_t)data{
    m_audio_data = data;
}

- (void)setAudioDataSize:(int64_t)size{
    m_audio_data_size = size;
}

- (void)setAudioPSTValue:(int64_t)value{
    m_audio_pts_value = value;
}

- (void)setAudioPSTScale:(int32_t)scale{
    m_audio_pts_scale = scale;
}

- (void)setNumSamples:(int32_t)num{
    m_audio_num_sample = num;
}

- (void)setChannelsPerFrame:(int32_t)channels{
    m_audio_channels_per_frame = channels;
}

- (void)setSampleRate:(double)rate{
    m_audio_sample_rate = rate;
}

- (void)setBitsPerChannel:(int32_t)bits{
    m_audio_bits_per_channel = bits;
}

@end
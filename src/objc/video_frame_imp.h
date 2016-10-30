//
//  video_frame_imp.h
//  lapse_app
//
//  Created by dyno on 7/25/16.
//  Copyright © 2016 dyno. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "GBVideoFrameGen.h"

@interface GBVideoFrameImp : NSObject<GBVideoFrameGen>;
@property int64_t m_data;
@property int64_t m_size;
@property int32_t m_width;
@property int32_t m_height;
@property int32_t m_linesize;
@property int64_t m_audio_data;
@property int64_t m_audio_data_size;
@property int64_t m_audio_pts_value;
@property int32_t m_audio_pts_scale;
@property int32_t m_audio_num_sample;
@property int32_t m_audio_channels_per_frame;
@property double m_audio_sample_rate;
@property int32_t m_audio_bits_per_channel;
- (instancetype _Nonnull) initWithImage:(CMSampleBufferRef _Nonnull)ios_image;
- (instancetype _Nonnull) initWithAudio:(CMSampleBufferRef _Nonnull)ios_sample;
- (BOOL)parserSample;
- (int64_t)getData;

- (int32_t)getWidth;

- (int32_t)getHeight;

- (int64_t)getSize;

- (int32_t)getLineSize;

- (void)setData:(int64_t)data;

- (void)setWidth:(int32_t)width;

- (void)setHeight:(int32_t)height;

- (void)setSize:(int64_t)size;

- (void)setLineSize:(int32_t)linesize;

- (int64_t)getAudioData;

- (int64_t)getAudioDataSize;

- (int64_t)getAudioPSTValue;

- (int32_t)getAudioPSTScale;

- (int32_t)getNumSamples;

- (int32_t)getChannelsPerFrame;

- (double)getSampleRate;

- (int32_t)getBitsPerChannel;

- (void)setAudioData:(int64_t)data;

- (void)setAudioDataSize:(int64_t)size;

- (void)setAudioPSTValue:(int64_t)value;

- (void)setAudioPSTScale:(int32_t)scale;

- (void)setNumSamples:(int32_t)num;

- (void)setChannelsPerFrame:(int32_t)channels;

- (void)setSampleRate:(double)rate;

- (void)setBitsPerChannel:(int32_t)bits;
@end

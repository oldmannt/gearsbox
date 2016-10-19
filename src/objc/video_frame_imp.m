//
//  video_frame_imp.m
//  lapse_app
//
//  Created by dyno on 7/25/16.
//  Copyright © 2016 dyno. All rights reserved.
//

#import "video_frame_imp.h"
#import "GBLogGen.h"

@interface GBVideoFrameImp()
@property (nonatomic) CMSampleBufferRef m_ios_sample;
@property (nonatomic) BOOL m_is_image;
@end


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

static NSMutableDictionary *dictionary = nil;
static NSInteger si = 0;
-(id)init{
    
    if (self = [super init]){
        m_data = 0;
        m_size = 0;
        m_width = 0;
        m_height = 0;
        m_audio_data = 0;
        m_audio_data_size = 0;
        m_audio_pts_value = 0;
        m_audio_pts_scale = 0;
    }
    
    //if (nil == dictionary){
    //    dictionary = [NSMutableDictionary dictionaryWithCapacity:100];
    //}
    //NSLog(@"GBVideoFrameImp allocate %@ + %x",dictionary, self);
    //[dictionary setValue:[NSString stringWithFormat:@"%d", si++] forKey:[NSString stringWithFormat:@"%x", self]];
    
    return self;
}

- (instancetype)initWithImage:(CMSampleBufferRef _Nonnull)ios_sample {
    if (self = [self init]){
        _m_ios_sample = ios_sample;
        _m_is_image = true;
        CFRetain(_m_ios_sample);
    }
    
    [self parserImage];
    return self;
}

- (instancetype)initWithAudio:(CMSampleBufferRef _Nonnull)ios_sample {
    if (self = [self init]){
        _m_ios_sample = ios_sample;
        _m_is_image = false;
    }
    
    return self;
}

#pragma mark
- (void)dealloc{
    //NSLog(@"GBVideoFrameImp dealloc %x",self);
    if (m_data!=0){
        void* ptr = (void*)m_data;
        free(ptr);
    }
    
    if (m_audio_data!=0){
        void* ptr = (void*)m_audio_data;
        free(ptr);
    }
    
    if (_m_ios_sample)
        CFRelease(_m_ios_sample);
    _m_ios_sample = NULL;
    //[dictionary removeObjectForKey:[NSString stringWithFormat:@"%x", self]];
    //NSLog(@"GBVideoFrameImp allocate %@ - %x",dictionary, self);
}

- (BOOL)parserImage{
    CVPixelBufferRef imageBuffer = CMSampleBufferGetImageBuffer(_m_ios_sample);
    if (nil == imageBuffer){
        return false;
    }
    
    CVReturn rt = CVPixelBufferLockBaseAddress(imageBuffer, kCVPixelBufferLock_ReadOnly);
    if (rt != kCVReturnSuccess) {
        [[GBLogGen instance] logerrf: [NSString stringWithFormat:@"CVPixelBufferLockBaseAddress lock failed:%i %x", rt, _m_ios_sample]];
        return false;
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
    UInt8 *yuv420_data = (UInt8 *)malloc(width * height *3/ 2); // buffer to store YUV with layout YYYYYYYYUUVV free in GBVideoFrameImp
    
    m_data =(int64_t)yuv420_data;
    m_size = (int64_t)buffeSize;
    m_width = (int32_t)width;
    m_height = (int32_t)height;
    
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
    
    CVPixelBufferUnlockBaseAddress(imageBuffer, kCVPixelBufferLock_ReadOnly);
    CFRelease(_m_ios_sample);
    _m_ios_sample = NULL;
    return true;
}

- (BOOL)parserAudio{
    CMItemCount num_samples = CMSampleBufferGetNumSamples(_m_ios_sample); //CMSampleBufferRef
    NSUInteger channel_index = 0;
    CMBlockBufferRef block_buffer = CMSampleBufferGetDataBuffer(_m_ios_sample);
    size_t offset = (channel_index * num_samples * sizeof(SInt16));
    size_t block_buffer_size  = CMBlockBufferGetDataLength(block_buffer);
    UInt8 *samples_buffer = malloc(block_buffer_size);
    CMBlockBufferCopyDataBytes(block_buffer, 0, block_buffer_size, samples_buffer);
    
    const AudioStreamBasicDescription *audioDescription = CMAudioFormatDescriptionGetStreamBasicDescription(CMSampleBufferGetFormatDescription(_m_ios_sample));
    CMTime pts = CMSampleBufferGetPresentationTimeStamp(_m_ios_sample);
    
    m_audio_data = (int64_t)samples_buffer;
    m_audio_data_size = block_buffer_size;
    m_audio_pts_value = pts.value;
    m_audio_pts_scale = pts.timescale;
    
    m_audio_num_sample = num_samples;
    m_audio_channels_per_frame = audioDescription->mChannelsPerFrame;
    m_audio_sample_rate = audioDescription->mSampleRate;
    m_audio_bits_per_channel = audioDescription->mBitsPerChannel;
    _m_ios_sample = NULL;
    return true;
}

- (BOOL)parserSample{
    if (m_data!=0 || m_audio_data!=0){ // alread parsered
        return true;
    }
    if (_m_ios_sample==NULL) {
        [[GBLogGen instance] logerrf: [NSString stringWithFormat:@"sample null"]];
        return false;
    }
    if (_m_is_image)
        return [self parserImage];
    
    return [self parserAudio];
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

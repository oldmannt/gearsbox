//
//  objc_utility.m
//  lapse_app
//
//  Created by dyno on 7/24/16.
//  Copyright © 2016 dyno. All rights reserved.
//

#import "objc_utility.h"
#import "GBVideoInfoGen.h"
#import "GBLogGen.h"
#import <UIKit/UIKit.h>

#include "libavcodec/avcodec.h"
#include "libavutil/pixdesc.h"
#include "libavutil/opt.h"
#include "libavutil/avstring.h"
#include "libavutil/parseutils.h"
#include "libavutil/time.h"

@implementation ObjcUtility

typedef struct
{
    int             config; // 0 not conifg, 1 done
    int             audio_channels;
    int             audio_bits_per_sample;
    int             audio_float;
    int             audio_be;
    int             audio_signed_integer;
    int             audio_packed;
    int             audio_non_interleaved;
    
    int32_t         *audio_buffer;
    int             audio_buffer_size;
    uint8_t         *packet_data;
    int             packet_size;
    CMSampleBufferRef         current_audio_frame;
    int64_t         pts_value;
    int32_t         pts_scale;
} AVFContext;

static const int avf_time_base = 1000000;

static const AVRational avf_time_base_q = {
    .num = 1,
    .den = avf_time_base
};

static int get_audio_config(AVFContext *ctx)
{
    CMFormatDescriptionRef format_desc;
    format_desc = CMSampleBufferGetFormatDescription(ctx->current_audio_frame);
    const AudioStreamBasicDescription *basic_desc = CMAudioFormatDescriptionGetStreamBasicDescription(format_desc);
    
    if (!basic_desc) {
        [[GBLogGen instance] logerrf: [NSString stringWithFormat:@"audio format not available"]];
        return -1;
    }
    
    //stream->codecpar->sample_rate    = basic_desc->mSampleRate;
    //stream->codecpar->channels       = basic_desc->mChannelsPerFrame;
    //stream->codecpar->channel_layout = av_get_default_channel_layout(stream->codecpar->channels);
    
    ctx->audio_channels        = basic_desc->mChannelsPerFrame;
    ctx->audio_bits_per_sample = basic_desc->mBitsPerChannel;
    ctx->audio_float           = basic_desc->mFormatFlags & kAudioFormatFlagIsFloat;
    ctx->audio_be              = basic_desc->mFormatFlags & kAudioFormatFlagIsBigEndian;
    ctx->audio_signed_integer  = basic_desc->mFormatFlags & kAudioFormatFlagIsSignedInteger;
    ctx->audio_packed          = basic_desc->mFormatFlags & kAudioFormatFlagIsPacked;
    ctx->audio_non_interleaved = basic_desc->mFormatFlags & kAudioFormatFlagIsNonInterleaved;
    
    /*
    if (basic_desc->mFormatID == kAudioFormatLinearPCM &&
        ctx->audio_float &&
        ctx->audio_bits_per_sample == 32 &&
        ctx->audio_packed) {
        stream->codecpar->codec_id = ctx->audio_be ? AV_CODEC_ID_PCM_F32BE : AV_CODEC_ID_PCM_F32LE;
    } else if (basic_desc->mFormatID == kAudioFormatLinearPCM &&
               ctx->audio_signed_integer &&
               ctx->audio_bits_per_sample == 16 &&
               ctx->audio_packed) {
        stream->codecpar->codec_id = ctx->audio_be ? AV_CODEC_ID_PCM_S16BE : AV_CODEC_ID_PCM_S16LE;
    } else if (basic_desc->mFormatID == kAudioFormatLinearPCM &&
               ctx->audio_signed_integer &&
               ctx->audio_bits_per_sample == 24 &&
               ctx->audio_packed) {
        stream->codecpar->codec_id = ctx->audio_be ? AV_CODEC_ID_PCM_S24BE : AV_CODEC_ID_PCM_S24LE;
    } else if (basic_desc->mFormatID == kAudioFormatLinearPCM &&
               ctx->audio_signed_integer &&
               ctx->audio_bits_per_sample == 32 &&
               ctx->audio_packed) {
        stream->codecpar->codec_id = ctx->audio_be ? AV_CODEC_ID_PCM_S32BE : AV_CODEC_ID_PCM_S32LE;
    } else {
        av_log(s, AV_LOG_ERROR, "audio format is not supported\n");
        return 1;
    }*/
    
    if (ctx->audio_non_interleaved) {
        CMBlockBufferRef block_buffer = CMSampleBufferGetDataBuffer(ctx->current_audio_frame);
        ctx->audio_buffer_size        = CMBlockBufferGetDataLength(block_buffer);
        ctx->audio_buffer             = av_malloc(ctx->audio_buffer_size);
        if (!ctx->audio_buffer) {
            [[GBLogGen instance] logerrf: [NSString stringWithFormat:@"error allocating audio buffer"]];
            return 1;
        }
    }
    ctx->config=1;
    return 0;
}

static int get_audio_packet(AVFContext* ctx) {
    if (NULL == ctx || ctx->current_audio_frame == nil){
        [[GBLogGen instance] logerrf: [NSString stringWithFormat:@"avf null"]];
        return -1;
    }
    
    if (ctx->config==0){
        
    }
    
    CMBlockBufferRef block_buffer = CMSampleBufferGetDataBuffer(ctx->current_audio_frame);
    int block_buffer_size         = CMBlockBufferGetDataLength(block_buffer);
    ctx->audio_buffer             = av_malloc(ctx->audio_buffer_size);
    
    if (!block_buffer || !block_buffer_size) {
        return AVERROR(EIO);
    }
    
    if (ctx->audio_non_interleaved && block_buffer_size > ctx->audio_buffer_size) {
        return AVERROR_BUFFER_TOO_SMALL;
    }
    
    /*
    AVPacket *pkt = NULL;
    if (av_new_packet(pkt, block_buffer_size) < 0) {
        return AVERROR(EIO);
    }
    */
    ctx->packet_data = malloc(block_buffer_size);
    ctx->packet_size = block_buffer_size;
    
    CMItemCount count;
    CMSampleTimingInfo timing_info;
    
    if (CMSampleBufferGetOutputSampleTimingInfoArray(ctx->current_audio_frame, 1, &timing_info, &count) == noErr) {
        AVRational timebase_q = av_make_q(1, timing_info.presentationTimeStamp.timescale);
        ctx->pts_value = av_rescale_q(timing_info.presentationTimeStamp.value, timebase_q, avf_time_base_q);
    }
    
    //pkt->stream_index  = ctx->audio_stream_index;
    //pkt->flags        |= AV_PKT_FLAG_KEY;
    
    if (ctx->audio_non_interleaved) {
        int sample, c, shift, num_samples;
        
        OSStatus ret = CMBlockBufferCopyDataBytes(block_buffer, 0, ctx->packet_size, ctx->audio_buffer);
        if (ret != kCMBlockBufferNoErr) {
            return AVERROR(EIO);
        }
        
        num_samples =  ctx->packet_size / (ctx->audio_channels * (ctx->audio_bits_per_sample >> 3));
        
        // transform decoded frame into output format
        #define INTERLEAVE_OUTPUT(bps)                                         \
        {                                                                      \
            int##bps##_t **src;                                                \
            int##bps##_t *dest;                                                \
            src = av_malloc(ctx->audio_channels * sizeof(int##bps##_t*));      \
            if (!src) return AVERROR(EIO);                                     \
            for (c = 0; c < ctx->audio_channels; c++) {                        \
                src[c] = ((int##bps##_t*)ctx->audio_buffer) + c * num_samples; \
            }                                                                  \
            dest  = (int##bps##_t*)ctx->packet_data;                                  \
            shift = bps - ctx->audio_bits_per_sample;                          \
            for (sample = 0; sample < num_samples; sample++)                   \
                for (c = 0; c < ctx->audio_channels; c++)                      \
                    *dest++ = src[c][sample] << shift;                         \
            av_freep(&src);                                                    \
        }
        
        if (ctx->audio_bits_per_sample <= 16) {
            INTERLEAVE_OUTPUT(16)
        } else {
            INTERLEAVE_OUTPUT(32)
        }
    } else {
        OSStatus ret = CMBlockBufferCopyDataBytes(block_buffer, 0, ctx->packet_size, ctx->packet_data);
        if (ret != kCMBlockBufferNoErr) {
            return AVERROR(EIO);
        }
    }

    ctx->current_audio_frame = nil;
    return 0;
}

static AVFContext s_ctx = {0};
+(GBVideoFrameImp* _Nonnull)toAudeoFrameCxt:(CMSampleBufferRef _Nonnull)audioBuffer{
    
    // need to config stream or add variables for GBVideoFrame
    s_ctx.current_audio_frame = audioBuffer;
    get_audio_packet(&s_ctx);
    
    CMTime pts = CMSampleBufferGetPresentationTimeStamp(audioBuffer);
    GBVideoFrameImp* video_frame = [[GBVideoFrameImp alloc] init];
    video_frame.m_audio_data = (int64_t)s_ctx.packet_data;
    video_frame.m_audio_data_size = s_ctx.packet_size;
    video_frame.m_audio_pts_value = s_ctx.pts_value;
    video_frame.m_audio_pts_scale = s_ctx.pts_scale;
    
    return video_frame;
}

+(GBVideoFrameImp* _Nonnull)toAudeoFrame:(CMSampleBufferRef _Nonnull)audioBuffer{
    CMItemCount num_samples = CMSampleBufferGetNumSamples(audioBuffer); //CMSampleBufferRef
    NSUInteger channel_index = 0;
    CMBlockBufferRef block_buffer = CMSampleBufferGetDataBuffer(audioBuffer);
    size_t offset = (channel_index * num_samples * sizeof(SInt16));
    size_t block_buffer_size  = CMBlockBufferGetDataLength(block_buffer);
    UInt8 *samples_buffer = malloc(block_buffer_size);
    CMBlockBufferCopyDataBytes(block_buffer, 0, block_buffer_size, samples_buffer);
    
    const AudioStreamBasicDescription *audioDescription = CMAudioFormatDescriptionGetStreamBasicDescription(CMSampleBufferGetFormatDescription(audioBuffer));
    CMTime pts = CMSampleBufferGetPresentationTimeStamp(audioBuffer);
    
    GBVideoFrameImp* video_frame = [[GBVideoFrameImp alloc] init];
    video_frame.m_audio_data = (int64_t)samples_buffer;
    video_frame.m_audio_data_size = block_buffer_size;
    video_frame.m_audio_pts_value = pts.value;
    video_frame.m_audio_pts_scale = pts.timescale;
    
    video_frame.m_audio_num_sample = num_samples;
    video_frame.m_audio_channels_per_frame = audioDescription->mChannelsPerFrame;
    video_frame.m_audio_sample_rate = audioDescription->mSampleRate;
    video_frame.m_audio_bits_per_channel = audioDescription->mBitsPerChannel;

    return video_frame;
}

+(GBVideoFrameImp* _Nonnull)toVideoFrame:(CMSampleBufferRef _Nonnull)sampleBuffer{
    CVPixelBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    
    CVReturn rt = CVPixelBufferLockBaseAddress(imageBuffer, kCVPixelBufferLock_ReadOnly);
    if (rt != kCVReturnSuccess) {
        [[GBLogGen instance] logerrf: [NSString stringWithFormat:@"CVPixelBufferLockBaseAddress lock failed:%i", rt]];
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
    UInt8 *yuv420_data = (UInt8 *)malloc(width * height *3/ 2); // buffer to store YUV with layout YYYYYYYYUUVV free in GBVideoFrameImp
    
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

    CVPixelBufferUnlockBaseAddress(imageBuffer, kCVPixelBufferLock_ReadOnly);
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

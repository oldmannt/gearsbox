//
//  ffencode_mp4.hpp
//  gearsbox
//
//  Created by dyno on 8/7/16.
//
//

#ifndef VideoEncoderImp_ffmp4_hpp
#define VideoEncoderImp_ffmp4_hpp

#include "video_encoder_gen.hpp"

#include <string>

#ifdef __cplusplus
extern "C" {
#endif
    
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/timestamp.h>
    
#ifdef __cplusplus
};
#endif

namespace gearsbox {
    
class VideoFrameGen;

// a wrapper around a single output AVStream
typedef struct OutputStream {
    AVStream *st;
    AVCodecContext *enc;
    
    /* pts of the next frame that will be generated */
    int64_t next_pts;
    int samples_count;
    
    AVFrame *frame;
    AVFrame *tmp_frame;
    
    float t, tincr, tincr2;
    
    struct SwsContext *sws_ctx;
    struct SwrContext *swr_ctx;
} OutputStream;
    
class VideoEncoderImp_ffmp4 : public VideoEncoderGen{
public:
    VideoEncoderImp_ffmp4():m_video_steam({0}),m_audio_steam({0}),m_format_ctx(0)
                        ,m_av_frame(0),m_ysize(0),m_frame_counter(0) {
        
    }
    virtual ~VideoEncoderImp_ffmp4() {}
    
    virtual bool initialize(const std::string & filepath, int32_t fps, int32_t bitrate, int32_t width, int32_t height);
    
    virtual void encodeFrame(const std::shared_ptr<VideoFrameGen> & frame);
    
    virtual void saveNRelease();
    
private:

    OutputStream m_video_steam;
    OutputStream m_audio_steam;
    AVFormatContext *m_format_ctx;
    AVFrame* m_av_frame;
    int64_t m_ysize;
    int32_t m_frame_counter;
    int32_t m_width;
    int32_t m_height;
    std::string m_file_path;
};
    
}  // namespace gearsbox

#endif /* ffencode_mp4_hpp */

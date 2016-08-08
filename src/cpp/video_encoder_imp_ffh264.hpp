//
//  VideoEncoderImp_ffh264.hpp
//  gearsbox
//
//  Created by dyno on 8/7/16.
//
//

#ifndef VideoEncoderImp_ffh264_hpp
#define VideoEncoderImp_ffh264_hpp

#include "video_encoder_gen.hpp"

#include <string>

#ifdef __cplusplus
extern "C" {
#endif
    
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
    
#ifdef __cplusplus
};
#endif

namespace gearsbox {
    
    class VideoFrameGen;
    
    class VideoEncoderImp_ffh264 {
    public:
        VideoEncoderImp_ffh264(): m_init(false), m_format_ctx(0),m_video_stream(0),m_av_frame(0),m_ysize(0){
            
        }
        virtual ~VideoEncoderImp_ffh264() {}
        
        virtual bool initialize(const std::string & filepath, int32_t fps, int32_t bitrate, int32_t width, int32_t height);
        
        virtual void encodeFrame(const std::shared_ptr<VideoFrameGen> & frame);
        
        virtual void saveNRelease();
        
    private:
        
        bool m_init;
        
        AVFormatContext *m_format_ctx;
        AVStream* m_video_stream;
        AVFrame* m_av_frame;
        int64_t m_ysize;
        int32_t m_frame_counter;
        
        AVPacket m_av_packet;
        std::string m_file_path;
    };
    
}  // namespace gearsbox


#endif /* VideoEncoderImp_ffh264_hpp */

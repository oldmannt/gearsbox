//
//  video_writer_imp.hpp
//  gearsbox
//
//  Created by dyno on 7/25/16.
//
//

#ifndef video_writer_imp_hpp
#define video_writer_imp_hpp

#include <string>
#include "video_writer_gen.hpp"
#include "timer_gen.hpp"
#include "task_excuser_gen.hpp"

#ifdef __cplusplus
extern "C" {
#endif
    
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
    
#ifdef __cplusplus
};
#endif

namespace gearsbox {
    
class VideoFrameGen;

class VideoWriterImp : public VideoWriterGen, public gearsbox::TaskExcuserGen, public std::enable_shared_from_this<VideoWriterImp>{
public:
    virtual ~VideoWriterImp() {}
    
    VideoWriterImp():m_width(0),m_height(0),m_resolution(0),m_fps(0),m_bitrate(0),
        m_init(false), m_format_ctx(0),m_video_stream(0),m_av_frame(0),m_ysize(0){
        
    }
    
    //TaskExcuserGen
    virtual void excuse(const TaskInfo & info);
    
    //VideoWriterGen
    virtual void setFilePath(const std::string & file);
    
    virtual void setFPS(int32_t fps);
    
    virtual void setBitRate(int32_t rate);
    
    virtual void encodeFrame(const std::shared_ptr<VideoFrameGen> & frame);
    
    virtual void start(int64_t interval);
    
    virtual void pause();
    
    virtual void resume();
    
    virtual bool isRunning();
    
    virtual void saveNRlease();
    
private:
    std::shared_ptr<gearsbox::TimerGen> m_writting_timer;
    std::string m_file_path;
    int32_t m_width;
    int32_t m_height;
    int32_t m_resolution;
    int32_t m_fps;
    int32_t m_bitrate;
    bool m_init;
    
    AVFormatContext *m_format_ctx;
    AVStream* m_video_stream;
    AVFrame* m_av_frame;
    int64_t m_ysize;
    int32_t m_frame_counter;
    
    AVPacket m_av_packet;
    
    bool initialize(const std::shared_ptr<VideoFrameGen> & frame);
};
    
}  // namespace gearsbox


#endif /* video_writer_imp_hpp */

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
#include "video_encoder_gen.hpp"
#include "camera_capture_handler.hpp"
#include "instance_getter_gen.hpp"

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

class VideoWriterImp : public VideoWriterGen, public TaskExcuserGen, public CameraCaptureHandler, public std::enable_shared_from_this<VideoWriterImp>{
public:
    virtual ~VideoWriterImp() {
        m_video_encoder = nullptr;
    }
    
    VideoWriterImp():m_video_encoder(nullptr),m_fps(0),m_bitrate(0),m_init(false){
        
    }
    
    // CameraCaptureHandler
    virtual void captureOutput(const std::shared_ptr<VideoFrameGen> & picture, const std::string & error);
    
    //TaskExcuserGen
    virtual void excuse(const std::shared_ptr<TaskInfoGen> & info);
    
    //VideoWriterGen
    virtual void setFilePath(const std::string & file);
    
    virtual std::string getFilePath(){return m_file_path;}
    
    virtual void setFPS(int32_t fps);
    
    virtual int32_t getFPS();
    
    virtual void setBitRate(int32_t rate);
    
    virtual void setVideoEncoder(const std::shared_ptr<VideoEncoderGen> & encoder){
        m_video_encoder = encoder;
    }
    
    virtual void encodeFrame(const std::shared_ptr<VideoFrameGen> & frame);
    
    virtual void start(int64_t interval);
    
    virtual void setInterval(int64_t interval);
    
    virtual void pause();
    
    virtual void resume();
    
    virtual bool isRunning();
    
    virtual void saveNRlease();
    
private:
    std::shared_ptr<gearsbox::TimerGen> m_writting_timer;
    std::shared_ptr<gearsbox::VideoEncoderGen> m_video_encoder;
    std::string m_file_path;
    int32_t m_fps;
    int32_t m_bitrate;
    bool m_init;
    
    bool initialize(const std::shared_ptr<VideoFrameGen> & frame);
};
    
}  // namespace gearsbox


#endif /* video_writer_imp_hpp */

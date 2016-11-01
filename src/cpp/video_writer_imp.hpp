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
#include "uv.h"

#include "video_writer_gen.hpp"
#include "timer_gen.hpp"
#include "task_excuser_gen.hpp"
#include "video_encoder_gen.hpp"
#include "camera_capture_handler.hpp"
#include "instance_getter_gen.hpp"
#include "ring_buffer_ptr.hpp"
#include "work_thread.hpp"
#include "video_orientation.hpp"

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
    }
    
    VideoWriterImp():m_video_encoder(nullptr),m_fps(0),m_bitrate(0),m_orientation(VideoOrientation::LANDSPACE_0),m_init(false),m_auto_callback(false),m_rw_lock({0}),m_end_thread(false){
        
    }
    
    // CameraCaptureHandler
    virtual void captureOutput(const std::shared_ptr<VideoFrameGen> & picture, const std::string & error);
    
    //TaskExcuserGen
    virtual void excuse(const std::shared_ptr<TaskInfoGen> & info);
    
    //VideoWriterGen
    virtual void setReslutHandler(const std::shared_ptr<VideoWriterResultHandler> & handler);
    
    virtual void setFilePath(const std::string & file);
    
    virtual std::string getFilePath(){return m_file_path;}
    
    virtual void setFPS(int32_t fps);
    
    virtual int32_t getFPS();
    
    virtual void setBitRate(int32_t rate);
    
    virtual void setOrientation(VideoOrientation ori);
    
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
    std::shared_ptr<VideoWriterResultHandler> m_write_result_handler;
    std::shared_ptr<gearsbox::TimerGen> m_writting_timer;
    std::shared_ptr<gearsbox::VideoEncoderGen> m_video_encoder;
    std::shared_ptr<RingBufferPtr> m_frame_buffer;
    std::string m_file_path;
    int32_t m_fps;
    int32_t m_bitrate;
    VideoOrientation m_orientation;
    
    bool m_init;
    bool m_auto_callback;
    uv_rwlock_t m_rw_lock;
    std::shared_ptr<uv_rwlock_t> m_auto_release_lock;
    std::shared_ptr<WorkThread> m_work_thread;
    bool m_end_thread;
    
    
    bool initialize(const std::shared_ptr<VideoFrameGen> & frame);
    void initializeTheard();
    void encodeFrameAsyn(const std::shared_ptr<VideoFrameGen> & frame);
    void asynWritting();
    void destoryThread();
};
    
}  // namespace gearsbox


#endif /* video_writer_imp_hpp */

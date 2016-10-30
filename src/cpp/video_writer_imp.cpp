//
//  video_writer_imp.cpp
//  gearsbox
//
//  Created by dyno on 7/25/16.
//
//
#include <unistd.h>

#include "video_writer_imp.hpp"
#include "video_writer_result_handler.hpp"
#include "video_frame_gen.hpp"
#include "macro.h"
#include "camera_controller_gen.hpp"
#include "video_encoder_imp_ffmp4.hpp"
#include "task_info_gen.hpp"
#include "instance_getter_gen.hpp"
#include "platform_utility_gen.hpp"
#include "uv.h"


using namespace gearsbox;

std::shared_ptr<VideoWriterGen> VideoWriterGen::create(){
    return std::make_shared<VideoWriterImp>();
}

void VideoWriterImp::setReslutHandler(const std::shared_ptr<VideoWriterResultHandler> & handle) {
    m_write_result_handler = handle;
}

void VideoWriterImp::setFilePath(const std::string & file){
    m_file_path = file;
}

void VideoWriterImp::setFPS(int32_t fps){
    m_fps = fps;
    if (m_init && m_video_encoder)
        m_video_encoder->setFps(m_fps);
}

int32_t VideoWriterImp::getFPS(){
    return m_fps;
}

void VideoWriterImp::setBitRate(int32_t rate){
    m_bitrate = rate;
}

void VideoWriterImp::encodeFrame(const std::shared_ptr<VideoFrameGen> & frame){
    CHECK_RT(frame!=nullptr, "frame null");
    this->initialize(frame);
    
    if (m_video_encoder==nullptr){
        return;
    }
    if (m_frame_buffer){
        this->encodeFrameAsyn(frame);
        return;
    }
    //m_video_encoder->encodeFrame(frame);
}

void VideoWriterImp::initializeTheard(){
    CHECK_RT(m_frame_buffer==nullptr, "thread already initialized, should not call again");
    uint32_t size = 1000/m_writting_timer->getInterval()+1;
    if (size < 100 ) size = 100;
    m_frame_buffer = std::make_shared<RingBufferPtr>(size);
    m_end_thread = false;
    m_auto_release_lock = nullptr;
    uv_rwlock_init(&m_rw_lock);
    m_auto_release_lock = std::shared_ptr<uv_rwlock_t>(&m_rw_lock, uv_rwlock_destroy);
    
    std::function<void()> work = std::bind(&VideoWriterImp::asynWritting, shared_from_this());
    std::function<void()> after_work = std::bind(&VideoWriterImp::destoryThread, shared_from_this());
    m_work_thread = std::make_shared<WorkThread>(work, after_work);
    m_work_thread->start();
}

void VideoWriterImp::encodeFrameAsyn(const std::shared_ptr<VideoFrameGen> & frame){
    std::shared_ptr<uv_rwlock_t> auto_unlock(&m_rw_lock, uv_rwlock_wrunlock);
    uv_rwlock_wrlock(&m_rw_lock);
    m_frame_buffer->push(frame);
    //if (m_frame_buffer->getDistence() == 0){
    //    this->saveNRlease();
    //}
}

void VideoWriterImp::destoryThread(){
    m_auto_release_lock = nullptr;
    m_frame_buffer = nullptr;

    CHECK_RTF(m_video_encoder!=nullptr, "saveNRlease m_video_encoder null");
    if (m_video_encoder){
        m_video_encoder->saveNRelease();
        m_video_encoder = nullptr;
    }
    
    if (m_writting_timer){
        m_writting_timer->stop();
        m_writting_timer = nullptr;
        
    }
    
    if (m_write_result_handler){
        bool success = InstanceGetterGen::getPlatformUtility()->fileExists(m_file_path);
        m_write_result_handler->onComplete(success, m_file_path);
    }
    m_work_thread = nullptr; // VideoWriterImp will be destory here
}

void VideoWriterImp::asynWritting(){
    while (true) {
        long long cost = nowMilli();
        int buffer = 0;
        std::shared_ptr<VideoFrameGen> frame = nullptr;
        {
            std::shared_ptr<uv_rwlock_t> auto_unlock(&m_rw_lock, uv_rwlock_rdunlock);
            uv_rwlock_rdlock(&m_rw_lock);
            frame = std::static_pointer_cast<VideoFrameGen>(m_frame_buffer->pop());
            buffer = m_frame_buffer->getDistence();
            //G_LOG_C(LOG_INFO,"buffer distance:%d", m_frame_buffer->getDistence());
        }
        
        if (m_end_thread) { // write all the frames in buffer and quick
            do{
                std::shared_ptr<uv_rwlock_t> auto_unlock(&m_rw_lock, uv_rwlock_rdunlock);
                uv_rwlock_rdlock(&m_rw_lock);
                frame = std::static_pointer_cast<VideoFrameGen>(m_frame_buffer->pop());
                G_LOG_C(LOG_INFO,"count donw:%d", m_frame_buffer->getBufferSize() - m_frame_buffer->getDistence());
                if (frame)  m_video_encoder->encodeFrame(frame);
            }while (frame);
            break;
        }
        
        if (frame == nullptr){
            usleep(10000);
            continue;
        }
        else{
            m_video_encoder->encodeFrame(frame);
        }
        G_LOG_C(LOG_INFO,"encodeFrame end:%d dis:%d", nowMilli() - cost, buffer);
    }
    
}

void VideoWriterImp::excuse(const std::shared_ptr<TaskInfoGen> & info){
    //static long long last = nowMilli();
    //G_LOG_C(LOG_INFO,"timer %d", nowMilli() - last);
    if (!m_end_thread)
        InstanceGetterGen::getCameraController()->asnyOneFrame();
    else if (m_write_result_handler && m_frame_buffer){
        float percent = (float)m_frame_buffer->getDistence()/m_frame_buffer->getBufferSize();
        m_write_result_handler->onProgress(percent);
    }
    //last = nowMilli();
}

void VideoWriterImp::start(int64_t interval){
    G_LOG_C(LOG_INFO,"VideoWriterImp::start interval:%d %d",interval,uv_now(uv_default_loop()));
    if (m_writting_timer==nullptr){
        m_writting_timer = TimerGen::create(interval, -1, shared_from_this());
    }
    if (!m_writting_timer->isRunning())
        m_writting_timer->start();
    else
        m_writting_timer->setInterval(interval);
    
    if (!m_init)
        InstanceGetterGen::getCameraController()->setCaptureHandler(shared_from_this());
    
    // encode the first frame
    InstanceGetterGen::getCameraController()->asnyOneFrame();
}

void VideoWriterImp::captureOutput(const std::shared_ptr<VideoFrameGen> & frame, const std::string & error){
    if (error.size()>0){
        G_LOG_C(LOG_ERROR,"captureOutput err:%s", error.c_str());
    }

    this->encodeFrame(frame);
}

void VideoWriterImp::setInterval(int64_t interval){
    CHECK_RT(m_writting_timer, "m_writting_timer null");
    m_writting_timer->setInterval(interval);
}

void VideoWriterImp::pause(){
    CHECK_RT(m_writting_timer, "m_writting_timer null");
    m_writting_timer->pause();
}

void VideoWriterImp::resume(){
    CHECK_RT(m_writting_timer, "m_writting_timer null");
    m_writting_timer->resume();
}

bool VideoWriterImp::isRunning(){
    CHECK_RT(m_writting_timer, "m_writting_timer null");
    return m_writting_timer->isRunning();
}

void VideoWriterImp::saveNRlease(){
    if (m_writting_timer)
        m_writting_timer->setInterval(500); // frequency of update the progress
    m_end_thread = true;
    InstanceGetterGen::getCameraController()->setCaptureHandler(nullptr);
    
    if (m_frame_buffer && m_frame_buffer->getDistence() != 0 && m_write_result_handler){
        m_write_result_handler->beforeComplete();
    }
}

bool VideoWriterImp::initialize(const std::shared_ptr<VideoFrameGen> & frame){
    if (m_init)
        return false;
    
    CHECK_RTF(frame!=nullptr,"frame null");
    CHECK_RT(frame->parserSample(),"frame parser failed");

    if (m_video_encoder == nullptr){
        m_video_encoder = std::make_shared<VideoEncoderImp_ffmp4>();
    }
    

    if (!m_video_encoder->initialize(m_file_path, m_fps, m_bitrate, frame->getWidth(), frame->getHeight(), frame)){
        G_LOG_FC(LOG_ERROR, "video encoder initialize failed");
        m_video_encoder = nullptr;
        if (m_writting_timer){
            m_writting_timer->stop();
            m_writting_timer = nullptr;
            
        }
        InstanceGetterGen::getCameraController()->setCaptureHandler(nullptr);
        if (m_write_result_handler){
            m_write_result_handler->onComplete(false, m_file_path);
        }
        return false;
    }

    
    this->initializeTheard();
    m_init = true;
    return true;
}


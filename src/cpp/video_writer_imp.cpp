//
//  video_writer_imp.cpp
//  gearsbox
//
//  Created by dyno on 7/25/16.
//
//

#include "video_writer_imp.hpp"
#include "video_frame_gen.hpp"
#include "macro.h"
#include "camera_controller_gen.hpp"
#include "video_encoder_imp_ffmp4.hpp"
#include "task_info_gen.hpp"
#include "uv.h"

using namespace gearsbox;

std::shared_ptr<VideoWriterGen> VideoWriterGen::create(){
    return std::make_shared<VideoWriterImp>();
}

void VideoWriterImp::setFilePath(const std::string & file){
    m_file_path = file;
}

void VideoWriterImp::setFPS(int32_t fps){
    m_fps = fps;
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
    static int frame_counter = 0;
    G_LOG_C(LOG_INFO,"VideoWriterImp::captureOutput frame:%d %d",++frame_counter,uv_now(uv_default_loop())); 
    m_video_encoder->encodeFrame(frame);
}

void VideoWriterImp::excuse(const std::shared_ptr<TaskInfoGen> & info){
    //this->encodeFrame(InstanceGetterGen::getCameraController()->captureOneFrame());
    InstanceGetterGen::getCameraController()->asnyOneFrame();
    //InstanceGetterGen::getCameraController()->asnyOnePicture();
}

void VideoWriterImp::start(int64_t interval){
    G_LOG_C(LOG_INFO,"VideoWriterImp::start %d",uv_now(uv_default_loop()));
    if (m_writting_timer==nullptr){
        m_writting_timer = TimerGen::create((int64_t)this, interval, -1, shared_from_this());
    }
    if (!m_writting_timer->isRunning())
        m_writting_timer->start();
    else
        m_writting_timer->setInterval(interval);
    
    if (!m_init)
        InstanceGetterGen::getCameraController()->setCaptureHandler(shared_from_this());
    
    // encode the first frame
    //this->encodeFrame(InstanceGetterGen::getCameraController()->captureOneFrame());
    InstanceGetterGen::getCameraController()->asnyOneFrame();
    //InstanceGetterGen::getCameraController()->asnyOnePicture();
    
}

void VideoWriterImp::captureOutput(const std::shared_ptr<VideoFrameGen> & picture, const std::string & error){
    if (error.size()>0){
        G_LOG_C(LOG_ERROR,"captureOutput err:%s", error.c_str());
    }
    
    this->encodeFrame(picture);
}

void VideoWriterImp::setInterval(int64_t interval){
    CHECK_RT(m_writting_timer, "m_writting_timer null");
    m_writting_timer->setInterval(interval);
}

void VideoWriterImp::pause(){
    if (m_writting_timer==nullptr)
        return;
    m_writting_timer->pause();
}

void VideoWriterImp::resume(){
    if (m_writting_timer==nullptr)
        return;
    m_writting_timer->resume();
}

bool VideoWriterImp::isRunning(){
    if (m_writting_timer==nullptr)
        return false;
    return m_writting_timer->isRunning();
}

void VideoWriterImp::saveNRlease(){
    CHECK_RTF(m_video_encoder!=nullptr, "saveNRlease m_video_encoder null");
    if (m_video_encoder){
        m_video_encoder->saveNRelease();
        m_video_encoder = nullptr;
    }
    m_init = false;
    if (m_writting_timer){
        m_writting_timer->stop();
        m_writting_timer = nullptr;

    }
}

bool VideoWriterImp::initialize(const std::shared_ptr<VideoFrameGen> & frame){
    CHECK_RTF(frame!=nullptr,"frame null");
    if (m_init)
        return false;

    if (m_video_encoder == nullptr){
        m_video_encoder = std::make_shared<VideoEncoderImp_ffmp4>();
    }
    CHECK_RTF(m_video_encoder!=nullptr, "m_video_encoder null");
    CHECK_RTF(m_video_encoder->initialize(m_file_path, m_fps, m_bitrate, frame->getWidth(), frame->getHeight()),
              "video encoder initialize failed");
    
    m_init = true;
    return true;
}
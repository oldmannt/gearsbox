//
//  video_writer_imp.cpp
//  gearsbox
//
//  Created by dyno on 7/25/16.
//
//

#include "video_writer_imp.hpp"
#include "video_frame_gen.hpp"
#include "ilog.h"
#include "camera_controller_gen.hpp"
#include "instance_getter_gen.hpp"

using namespace gearsbox;

std::shared_ptr<VideoWriterGen> VideoWriterGen::create(){
    return std::make_shared<VideoWriterImp>();
}

void VideoWriterImp::setFilePath(const std::string & file){
    m_file_path = file;
}

void VideoWriterImp::setFrameSize(int32_t width, int32_t height){
    m_width = width, m_height = height;
}

void VideoWriterImp::setResolution(int32_t short_one){
    m_resolution = short_one;
}

void VideoWriterImp::setFPS(int32_t fps){
    m_fps = fps;
}

void VideoWriterImp::setBitRate(int32_t rate){
    m_bitrate = rate;
}

void VideoWriterImp::encodeFrame(const std::shared_ptr<VideoFrameGen> & frame){
    this->initialize(frame);
    
    //Read raw YUV data
    uint8_t* picture_buf = (uint8_t*)frame->getData();
    m_av_frame->data[0] = picture_buf;              // Y
    m_av_frame->data[1] = picture_buf+ m_ysize;      // U
    m_av_frame->data[2] = picture_buf+ m_ysize*5/4;  // V
    
    // PTS
    m_av_frame->pts = m_frame_counter;
    int got_picture = 0;
    
    // Encode
    m_av_frame->width = m_width;
    m_av_frame->height = m_height;
    m_av_frame->format = AV_PIX_FMT_YUV420P16LE;
    
    int ret = avcodec_encode_video2(m_video_stream->codec, &m_av_packet, m_av_frame, &got_picture);
    if(ret < 0) {
        G_LOG_FC(LOG_ERROR, "Failed to encode! \n");
    }
    if (got_picture==1) {
        
        G_LOG_FC(LOG_INFO, "Succeed to encode frame: %5d\tsize:%5d", m_frame_counter, m_av_packet.size);
        m_frame_counter++;
        m_av_packet.stream_index = m_video_stream->index;
        ret = av_write_frame(m_format_ctx, &m_av_packet);
        av_free_packet(&m_av_packet);
    }
    
    //free(picture_buf);
}

void VideoWriterImp::excuse(const TaskInfo & info){
    this->encodeFrame(InstanceGetterGen::getCameraController()->captureOneFrame());
}

void VideoWriterImp::start(int64_t interval){
    if (m_writting_timer==nullptr){
        m_writting_timer = TimerGen::create((int64_t)this, interval, -1, shared_from_this());
    }
    if (!m_writting_timer->isRunning())
        m_writting_timer->start();
    else
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

int flush_encoder(AVFormatContext *fmt_ctx,unsigned int stream_index)
{
    int ret;
    int got_frame;
    AVPacket enc_pkt;
    if (!(fmt_ctx->streams[stream_index]->codec->codec->capabilities &
          CODEC_CAP_DELAY))
        return 0;
    
    while (true) {
        enc_pkt.data = NULL;
        enc_pkt.size = 0;
        av_init_packet(&enc_pkt);
        ret = avcodec_encode_video2 (fmt_ctx->streams[stream_index]->codec, &enc_pkt,
                                     NULL, &got_frame);
        av_frame_free(NULL);
        if (ret < 0)
            break;
        if (!got_frame){
            ret=0;
            break;
        }
        G_LOG_FC(LOG_ERROR,"Flush Encoder: Succeed to encode 1 frame!\tsize:%5d",enc_pkt.size);
        /* mux encoded frame */
        ret = av_write_frame(fmt_ctx, &enc_pkt);
        if (ret < 0)
            break;
    }
    return ret;
}

void VideoWriterImp::saveNRlease(){
    //Flush Encoder
    int ret = flush_encoder(m_format_ctx,0);
    if (ret < 0) {
        G_LOG_FC(LOG_ERROR,"Flushing encoder failed");
    }
    
    //Write file trailer
    av_write_trailer(m_format_ctx);
    
    //Clean
    if (m_video_stream){
        avcodec_close(m_video_stream->codec);
        av_free(m_av_frame);
        //        av_free(picture_buf);
    }
    avio_close(m_format_ctx->pb);
    avformat_free_context(m_format_ctx);

    m_init = false;
    m_format_ctx = nullptr;
    m_video_stream = nullptr;
    m_av_frame = nullptr;
    m_ysize = 0;
    m_writting_timer->stop();
    m_writting_timer = nullptr;
}

bool VideoWriterImp::initialize(const std::shared_ptr<VideoFrameGen> & frame){
    if (m_init||nullptr==frame)
        return false;
    
    m_frame_counter = 0;
    if (m_width==0 && m_height==0 && m_resolution!=0){
        m_width = frame->getWidth();
        m_height = frame->getHeight();
        
        m_height = m_height * m_resolution/m_width;
        m_width = m_resolution;
    }
    
    /* initialize libavcodec, and register all codecs and formats */
    av_register_all();
    
    /* allocate the output media context */
    m_format_ctx = avformat_alloc_context();
    
    /* auto detect the output format from the name. default is mpeg. */
    AVOutputFormat* fmt = av_guess_format(NULL, m_file_path.c_str(), NULL);
    m_format_ctx->oformat = fmt;
    
    //Open output URL
    if (avio_open(&m_format_ctx->pb, m_file_path.c_str(), AVIO_FLAG_READ_WRITE) < 0){
        G_LOG_FC(LOG_ERROR,"Failed to open output file:%s", m_file_path.c_str());
        return false;
    }
    
    m_video_stream = avformat_new_stream(m_format_ctx, 0);
    if (m_video_stream==NULL){
        G_LOG_FC(LOG_ERROR,"Failed to avformat_new_stream");
        return false;
    }
    m_video_stream->time_base.num = 1;
    m_video_stream->time_base.den = 15;
    
    // Param that must set
    AVCodecContext* av_codec_context = m_video_stream->codec;
    av_codec_context->codec_id = fmt->video_codec;
    av_codec_context->codec_type = AVMEDIA_TYPE_VIDEO;
    av_codec_context->pix_fmt = AV_PIX_FMT_YUV420P;
    av_codec_context->width = m_width;
    av_codec_context->height = m_height;
    /* time base: this is the fundamental unit of time (in seconds) in terms
    of which frame timestamps are represented. for fixed-fps content,
    timebase should be 1/framerate and timestamp increments should be
    identically 1. */
    av_codec_context->time_base.num = 1;
    av_codec_context->time_base.den = m_fps;
    av_codec_context->bit_rate = m_bitrate; // 400000;
    av_codec_context->gop_size = 250;
    // H264
    // av_codec_context->me_range = 16;
    // av_codec_context->max_qdiff = 4;
    // av_codec_context->qcompress = 0.6;
    av_codec_context->qmin = 10;
    av_codec_context->qmax = 51;
    
    // Optional Param
    av_codec_context->max_b_frames=3;
    
    // Set Option
    AVDictionary *param = 0;
    
    // H.264
    if(av_codec_context->codec_id == AV_CODEC_ID_H264) {
        av_dict_set(&param, "preset", "slow", 0);
        av_dict_set(&param, "tune", "zerolatency", 0);
        // av_dict_set(&param, "profile", "main", 0);
    }
    
    // Show some Information
    av_dump_format(m_format_ctx, 0, m_file_path.c_str(), 1);
    
    AVCodec* pCodec = avcodec_find_encoder(av_codec_context->codec_id);
    if (!pCodec) {
        G_LOG_FC(LOG_ERROR, "Can not find encoder!");
        return false;
    }
    
    if (avcodec_open2(av_codec_context, pCodec,&param) < 0) {
        G_LOG_FC(LOG_ERROR, "Failed to open encoder!");
        return false;
    }
    
    uint8_t* picture_buf = 0;
    int64_t picture_size = 0;
    
    m_av_frame = av_frame_alloc();
    avpicture_fill((AVPicture *)m_av_frame, picture_buf, av_codec_context->pix_fmt, av_codec_context->width, av_codec_context->height);
    
    //Write File Header
    avformat_write_header(m_format_ctx, NULL);
    
    av_new_packet(&m_av_packet, picture_size);
    
    m_ysize = av_codec_context->width * av_codec_context->height;
    
    m_init = true;
    return true;
}
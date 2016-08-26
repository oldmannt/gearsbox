//
//  video_info_imp.cpp
//  gearsbox
//
//  Created by dyno on 8/16/16.
//
//

#include "video_info_imp.hpp"
#include "macro.h"
#include "instance_getter_gen.hpp"
#include "platform_utility_gen.hpp"
#include "instance_getter_gen.hpp"

#include <unordered_map>

using namespace gearsbox;

typedef std::unordered_map<std::string, std::shared_ptr<VideoInfoGen>> MAP_VIDEO_INFO;
MAP_VIDEO_INFO s_video_infos;

std::shared_ptr<VideoInfoGen> VideoInfoGen::getVideoInfo(const std::string & path, int32_t out_width, int32_t out_height){
    MAP_VIDEO_INFO::iterator find(s_video_infos.find(path));
    if (find!=s_video_infos.end()){
        return find->second;
    }
    
    std::shared_ptr<VideoInfoImp> info = std::make_shared<VideoInfoImp>();
    CHECK_RTNULL(info->initialize(path, out_width, out_height), "VideoInfoGen initializ failed path:%s", path.c_str());
    s_video_infos[path] = info;
    return info;
}

VideoInfoImp::~VideoInfoImp() {
    if (m_buffer) av_free(m_buffer);
    if (m_av_picture)av_free(m_av_picture);
    
    MAP_VIDEO_INFO::iterator find(s_video_infos.find(m_path));
    if (find!=s_video_infos.end()){
        s_video_infos.erase(find);
    }

}

bool VideoInfoImp::initialize(std::string path, int32_t out_width, int32_t out_height){
    m_out_w = out_width;
    m_out_h = out_height;
    av_register_all();
    
    AVFormatContext* format_cxt = 0;
    AVCodec* av_codec = 0;
    AVStream* stream = 0;
    AVCodecContext* av_codec_ctx = 0;
    AVFrame *av_frame = 0;
    struct SwsContext* sws_ctx = 0;
    int64_t buffer_size = 0;
    AVPacket packet;
    AVPixelFormat pix_fmt = AVPixelFormat::AV_PIX_FMT_RGB24;
    
    do {
        
        int err = avformat_open_input(&format_cxt, path.c_str(), 0, 0);
        BREAK(err==0, "avformat_open_input file:%s failed err:%s", path.c_str(), av_err2str(err));
        err = avformat_find_stream_info(format_cxt, 0);
        BREAK(err>=0, "avformat_find_stream_info file:%s failed err:%s", path.c_str(), av_err2str(err));
        
        //G_LOG_C(LOG_INFO,"path: %s", format_cxt->filename);
        //G_LOG_C(LOG_INFO,"fps_probe_size: %d", format_cxt->fps_probe_size);
        m_path = format_cxt->filename;
        m_file_name = InstanceGetterGen::getPlatformUtility()->getFileNameFromPath(m_path);
        
        
        // Find the first video stream
        int video_index = av_find_best_stream(format_cxt, AVMEDIA_TYPE_VIDEO, -1, -1, &av_codec, 0);
        BREAK(video_index >= 0,"Cannot find a video stream in the input file");
        
        stream = format_cxt->streams[video_index];
        BREAK(stream->codecpar!=nullptr, "stream->codecpar null ");
        
        m_fps = stream->r_frame_rate.num/stream->r_frame_rate.den;
        m_duration = stream->duration/stream->time_base.den*stream->time_base.num;
        m_width = stream->codecpar->width;
        m_height = stream->codecpar->height;
        m_frame_amount = stream->nb_frames;
        
        if (m_out_w==0 || m_out_h==0){
            m_out_w = m_width; m_out_h = m_height;
        }
        
        av_codec_ctx = stream->codec;
        av_codec = avcodec_find_decoder(av_codec_ctx->codec_id);
        BREAK(av_codec!=nullptr,"Unsupported codec!");
        
        BREAK(avcodec_open2(av_codec_ctx, av_codec, 0)>=0, "Cannot open video decoder");
        av_frame = av_frame_alloc();
        
        
        sws_ctx = sws_getContext(av_codec_ctx->width, av_codec_ctx->height,
                                                    av_codec_ctx->pix_fmt, m_out_w, m_out_h,
                                                    pix_fmt, SWS_BILINEAR, 0, 0, 0);
        int finish_frame = 0;
        while (!finish_frame && av_read_frame(format_cxt, &packet)>=0) {
            if (packet.stream_index == video_index){
                // Decode video frame
                avcodec_decode_video2(av_codec_ctx, av_frame, &finish_frame, &packet);
            }
        }
        
        m_av_picture = av_frame_alloc();
        BREAK(m_av_picture!=nullptr, "av_picture alloc failed");
        //buffer_size = avpicture_get_size(pix_fmt, m_width, m_height);
        buffer_size = av_image_get_buffer_size(pix_fmt, m_width, m_height, 1);
        m_buffer = (uint8_t*)av_malloc(buffer_size);
        //avpicture_fill((AVPicture*)av_picture, buffer, pix_fmt, m_width, m_height);
        av_image_fill_arrays(m_av_picture->data,m_av_picture->linesize,m_buffer,pix_fmt, m_width, m_height, 1);
        
        // Convert the image from its native format to RGB
        sws_scale(sws_ctx, av_frame->data, av_frame->linesize,
                  0, av_codec_ctx->height,
                  m_av_picture->data, m_av_picture->linesize);
        av_free_packet(&packet);
        // image frome av_picture
        
        m_video_frame = InstanceGetterGen::getPlatformUtility()->createVideoFrame();
        BREAK(m_video_frame!=nullptr, "createVideoFrame return null");
        
        m_video_frame->setData((int64_t)m_av_picture->data[0]);
        m_video_frame->setSize(buffer_size);
        m_video_frame->setLineSize(m_av_picture->linesize[0]);
        m_video_frame->setWidth(m_out_w);
        m_video_frame->setHeight(m_out_h);
    } while(false);
    
    /*
    G_LOG_C(LOG_INFO, "frame rate den:%d num:%d", stream->r_frame_rate.den, stream->r_frame_rate.num);
    G_LOG_C(LOG_INFO,"time bae den:%d num:%d", stream->time_base.den, stream->time_base.num);
    G_LOG_C(LOG_INFO,"duration %d", stream->duration);
    G_LOG_C(LOG_INFO,"width:%d height:%d", stream->codecpar->width,stream->codecpar->height);
    G_LOG_C(LOG_INFO,"frames:%d", stream->nb_frames);*/
    
    if (av_frame) av_free(av_frame);
    if (sws_ctx) sws_freeContext(sws_ctx);
    if (av_codec_ctx) avcodec_close(av_codec_ctx);
    if (format_cxt) avformat_close_input(&format_cxt);
    return true;
}

/*
std::string VideoInfoImp::getName(){
    
}

std::string VideoInfoImp::getPath(){
    
}

int32_t VideoInfoImp::getFPS(){
    
}

int32_t VideoInfoImp::getWidth(){
    
}

int32_t VideoInfoImp::getHeight(){
    
}

int64_t VideoInfoImp::getFrameAmount(){
    
}

int64_t VideoInfoImp::getDuration(){
    
}
*/
//
//  ffencode_mp4.cpp
//  gearsbox
//
//  Created by dyno on 8/7/16.
//
//

#include "video_encoder_imp_ffmp4.hpp"
#include "video_frame_gen.hpp"

#include "macro.h"

using namespace gearsbox;

static AVFrame *alloc_picture(enum AVPixelFormat pix_fmt, int width, int height)
{
    AVFrame *picture;
    int ret;
    
    picture = av_frame_alloc();
    if (!picture)
        return NULL;
    
    picture->format = pix_fmt;
    picture->width  = width;
    picture->height = height;
    
    /* allocate the buffers for the frame data */
    ret = av_frame_get_buffer(picture, 32);
    if (ret < 0) {
        G_LOG_FC(LOG_ERROR, "Could not allocate frame data.");
        return NULL;
    }
    
    return picture;
}

static bool open_video(AVFormatContext *oc, AVCodec *codec, OutputStream *ost, AVDictionary *opt_arg)
{
    int ret;
    AVCodecContext *av_codec_context = ost->enc;
    AVDictionary *opt = NULL;
    
    av_dict_copy(&opt, opt_arg, 0);
    
    /* open the codec */
    ret = avcodec_open2(av_codec_context, codec, &opt);
    av_dict_free(&opt);
    if (ret < 0) {
        G_LOG_FC(LOG_ERROR, "Could not open video codec: %s", av_err2str(ret));
        return false;
    }
    
    /* allocate and init a re-usable frame */
    ost->frame = alloc_picture(av_codec_context->pix_fmt, av_codec_context->width, av_codec_context->height);
    if (!ost->frame) {
        G_LOG_FC(LOG_ERROR, "Could not allocate video frame");
        return false;
    }
    
    /* If the output format is not YUV420P, then a temporary YUV420P
     * picture is needed too. It is then converted to the required
     * output format. */
    ost->tmp_frame = NULL;
    if (av_codec_context->pix_fmt != AV_PIX_FMT_YUV420P) {
        ost->tmp_frame = alloc_picture(AV_PIX_FMT_YUV420P, av_codec_context->width, av_codec_context->height);
        if (!ost->tmp_frame) {
            G_LOG_FC(LOG_ERROR, "Could not allocate temporary picture");
            return false;
        }
    }
    
    /* copy the stream parameters to the muxer */
    ret = avcodec_parameters_from_context(ost->st->codecpar, av_codec_context);
    if (ret < 0) {
        G_LOG_FC(LOG_ERROR, "Could not copy the stream parameters");
        return false;
    }
}


/* Add an output stream. */
static bool add_stream(OutputStream *ost, AVFormatContext *format_context,
                       AVCodec **codec,
                       enum AVCodecID codec_id, int fps, enum AVPixelFormat pix_fmt,
                       int width, int height, int bitrate)
{
    AVCodecContext *av_codec_context;
    int i;
    
    /* find the encoder */
    *codec = avcodec_find_encoder(codec_id);
    if (!(*codec)) {
        G_LOG_FC(LOG_ERROR, "Could not find encoder for '%s'",
                 avcodec_get_name(codec_id));
        return false;
    }
    
    ost->st = avformat_new_stream(format_context, NULL);
    if (!ost->st) {
        G_LOG_FC(LOG_ERROR, "Could not allocate stream");
        return false;
    }
    ost->st->id = format_context->nb_streams-1;
    av_codec_context = avcodec_alloc_context3(*codec);
    if (!av_codec_context) {
        G_LOG_FC(LOG_ERROR, "Could not alloc an encoding context");
        return false;
    }
    ost->enc = av_codec_context;
    
    switch ((*codec)->type) {
        case AVMEDIA_TYPE_AUDIO:
            av_codec_context->sample_fmt  = (*codec)->sample_fmts ?
            (*codec)->sample_fmts[0] : AV_SAMPLE_FMT_FLTP;
            av_codec_context->bit_rate    = 64000;
            av_codec_context->sample_rate = 44100;
            if ((*codec)->supported_samplerates) {
                av_codec_context->sample_rate = (*codec)->supported_samplerates[0];
                for (i = 0; (*codec)->supported_samplerates[i]; i++) {
                    if ((*codec)->supported_samplerates[i] == 44100)
                        av_codec_context->sample_rate = 44100;
                }
            }
            av_codec_context->channels        = av_get_channel_layout_nb_channels(av_codec_context->channel_layout);
            av_codec_context->channel_layout = AV_CH_LAYOUT_STEREO;
            if ((*codec)->channel_layouts) {
                av_codec_context->channel_layout = (*codec)->channel_layouts[0];
                for (i = 0; (*codec)->channel_layouts[i]; i++) {
                    if ((*codec)->channel_layouts[i] == AV_CH_LAYOUT_STEREO)
                        av_codec_context->channel_layout = AV_CH_LAYOUT_STEREO;
                }
            }
            av_codec_context->channels        = av_get_channel_layout_nb_channels(av_codec_context->channel_layout);
            ost->st->time_base = (AVRational){ 1, av_codec_context->sample_rate };
            break;
            
        case AVMEDIA_TYPE_VIDEO:
            av_codec_context->codec_id = codec_id;
            
            av_codec_context->bit_rate = bitrate;
            /* Resolution must be a multiple of two. */
            av_codec_context->width    = width;
            av_codec_context->height   = height;
            /* timebase: This is the fundamental unit of time (in seconds) in terms
             * of which frame timestamps are represented. For fixed-fps content,
             * timebase should be 1/framerate and timestamp increments should be
             * identical to 1. */
            ost->st->time_base = (AVRational){ 1, fps };
            av_codec_context->time_base       = ost->st->time_base;
            
            av_codec_context->gop_size      = 12; /* emit one intra frame every twelve frames at most */
            av_codec_context->pix_fmt       = pix_fmt;
            if (av_codec_context->codec_id == AV_CODEC_ID_MPEG2VIDEO) {
                /* just for testing, we also add B-frames */
                av_codec_context->max_b_frames = 2;
            }
            if (av_codec_context->codec_id == AV_CODEC_ID_MPEG1VIDEO) {
                /* Needed to avoid using macroblocks in which some coeffs overflow.
                 * This does not happen with normal video, it just happens here as
                 * the motion of the chroma plane does not match the luma plane. */
                av_codec_context->mb_decision = 2;
            }
            break;
            
        default:
            break;
    }
    
    /* Some formats want stream headers to be separate. */
    if (format_context->oformat->flags & AVFMT_GLOBALHEADER)
        av_codec_context->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
}

bool VideoEncoderImp_ffmp4::initialize(const std::string & filepath, int32_t fps, int32_t bitrate, int32_t width, int32_t height){
    m_video_steam = {0}, m_audio_steam = {0};
    AVCodec *audio_codec, *video_codec;
    int have_video = 0, have_audio = 0;
    int encode_video = 0, encode_audio = 0;
    AVDictionary *av_dictionary = 0;
    m_file_path = filepath;
    
    av_register_all();
    /* allocate the output media context */
    avformat_alloc_output_context2(&m_format_ctx, NULL, "mp4", m_file_path.c_str());
    if (!m_format_ctx) {
        G_LOG_FC(LOG_ERROR,"Could not deduce output format from file extension: using MPEG.");
        avformat_alloc_output_context2(&m_format_ctx, NULL, "mpeg", m_file_path.c_str());
    }
    CHECK_RTF(m_format_ctx!=nullptr, "m_format_ctx null");
    
    AVOutputFormat* fmt = m_format_ctx->oformat;
    
    /* Add the audio and video streams using the default format codecs
     * and initialize the codecs. */
    if (fmt->video_codec != AV_CODEC_ID_NONE) {
        add_stream(&m_video_steam, m_format_ctx, &video_codec, fmt->video_codec, fps, AV_PIX_FMT_YUV420P, width, height, bitrate);
        have_video = 1;
        encode_video = 1;
    }
    /*
    if (fmt->audio_codec != AV_CODEC_ID_NONE) {
        add_stream(&m_audio_steam, m_format_ctx, &audio_codec, fmt->audio_codec, fps, AV_PIX_FMT_NONE, width, height);
        have_audio = 1;
        encode_audio = 1;
    }*/
    
    /* Now that all the parameters are set, we can open the audio and
     * video codecs and allocate the necessary encode buffers. */
    if (have_video)
        open_video(m_format_ctx, video_codec, &m_video_steam, av_dictionary);
    
    //if (have_audio)
    //    open_audio(m_format_ctx, audio_codec, &audio_st, av_dictionary);
    
    av_dump_format(m_format_ctx, 0, m_file_path.c_str(), 1);
    
    /* open the output file, if needed */
    if (!(fmt->flags & AVFMT_NOFILE)) {
        int ret = avio_open(&m_format_ctx->pb, m_file_path.c_str(), AVIO_FLAG_WRITE);
        if (ret < 0) {
            G_LOG_FC(LOG_ERROR,"Could not open '%s': %s", m_file_path.c_str(),av_err2str(ret));
            return false;
        }
    }
    
    /* Write the stream header, if any. */
    int ret = avformat_write_header(m_format_ctx, &av_dictionary);
    if (ret < 0) {
        G_LOG_FC(LOG_ERROR,"Error occurred when opening output file: %s",av_err2str(ret));
        return false;
    }
    m_ysize = m_video_steam.enc->width * m_video_steam.enc->height;
    return true;
    
}

static void log_packet(const AVFormatContext *fmt_ctx, const AVPacket *pkt)
{
    AVRational *time_base = &fmt_ctx->streams[pkt->stream_index]->time_base;
    
    G_LOG_FC(LOG_ERROR, "pts:%s pts_time:%s dts:%s dts_time:%s duration:%s duration_time:%s stream_index:%d",
           av_ts2str(pkt->pts), av_ts2timestr(pkt->pts, time_base),
           av_ts2str(pkt->dts), av_ts2timestr(pkt->dts, time_base),
           av_ts2str(pkt->duration), av_ts2timestr(pkt->duration, time_base),
           pkt->stream_index);
}

static int write_frame(AVFormatContext *fmt_ctx, const AVRational *time_base, AVStream *st, AVPacket *pkt)
{
    /* rescale output packet timestamp values from codec to stream timebase */
    av_packet_rescale_ts(pkt, *time_base, st->time_base);
    pkt->stream_index = st->index;
    
    /* Write the compressed frame to the media file. */
    log_packet(fmt_ctx, pkt);
    return av_interleaved_write_frame(fmt_ctx, pkt);
}

static int write_video_frame(AVFormatContext *format_context, OutputStream *output_stream)
{
    int ret;
    AVCodecContext *codec_context;
    AVFrame *frame;
    int got_packet = 0;
    AVPacket pkt = { 0 };
    
    codec_context = output_stream->enc;

    frame = output_stream->frame;
    
    av_init_packet(&pkt);
    
    /* encode the image */
    ret = avcodec_encode_video2(codec_context, &pkt, frame, &got_packet);
    if (ret < 0) {
        G_LOG_FC(LOG_ERROR, "Error encoding video frame: %s", av_err2str(ret));
        return ret;
    }
    
    if (got_packet) {
        ret = write_frame(format_context, &codec_context->time_base, output_stream->st, &pkt);
    } else {
        ret = 0;
    }
    
    if (ret < 0) {
        G_LOG_FC(LOG_ERROR,"Error while writing video frame: %s", av_err2str(ret));
        return ret;
    }
    return got_packet;
}

int flush_encoder(AVFormatContext *fmt_ctx,OutputStream* ost)
{
    int i =100;
    AVFrame* save_frame = ost->frame;
    ost->frame = NULL;
    while (true && --i) {
        if (write_video_frame(fmt_ctx, ost)<=0){
            break;
        }
    }
    
    ost->frame = save_frame;
    return true;
    int ret = 0;
    int got_packet = 0;
    AVPacket enc_pkt = {0};
    
    if (!(ost->enc->codec->capabilities & CODEC_CAP_DELAY))
        return 0;

    while (true) {
        av_init_packet(&enc_pkt);
        ret = avcodec_encode_video2 (ost->st->codec, &enc_pkt, NULL, &got_packet);
        av_frame_free(NULL);
        if (ret < 0)
            break;
        if (!got_packet){
            ret=0;
            break;
        }
        G_LOG_FC(LOG_INFO,"Flush Encoder: Succeed to encode 1 frame!\tsize:%5d",enc_pkt.size);
        // mux encoded frame
        ret = av_write_frame(fmt_ctx, &enc_pkt);
        if (ret < 0)
            break;
    }
    if (ret<0)
        G_LOG_FC(LOG_ERROR,"Flushing encoder failed");
    return ret;
}

void VideoEncoderImp_ffmp4::encodeFrame(const std::shared_ptr<VideoFrameGen> & frame){
    
    CHECK_RT(m_video_steam.st!=nullptr, "video stream null, no initialize");
    CHECK_RT(m_video_steam.frame!=nullptr, "video frame null, no initialize");
    //Read raw YUV data
    CHECK_RT(frame->getData()!=0,"VideoFrameGen data null");
    uint8_t* picture_buf = (uint8_t*)frame->getData();

    int ret = av_frame_make_writable(m_video_steam.frame);
    CHECK_RT(ret>=0,"av_frame_make_writable failed");
    m_video_steam.frame->data[0] = picture_buf;              // Y
    m_video_steam.frame->data[1] = picture_buf+ m_ysize;      // U
    m_video_steam.frame->data[2] = picture_buf+ m_ysize*5/4;  // V
    m_video_steam.frame->pts = m_video_steam.next_pts++;
    
    write_video_frame(m_format_ctx, &m_video_steam);
}

static void close_stream(AVFormatContext *format_ctx, OutputStream *output_stream)
{
    avcodec_free_context(&output_stream->enc);
    av_frame_free(&output_stream->frame);
    av_frame_free(&output_stream->tmp_frame);
    sws_freeContext(output_stream->sws_ctx);
    // audio swr_free(&output_stream->swr_ctx);
}

void VideoEncoderImp_ffmp4::saveNRelease(){
    CHECK_RT(m_format_ctx!=nullptr,"needt to initialize");
    flush_encoder(m_format_ctx,&m_video_steam);
    av_write_trailer(m_format_ctx);
    
    close_stream(m_format_ctx, &m_video_steam);
    avio_close(m_format_ctx->pb);
    avformat_free_context(m_format_ctx);
    m_format_ctx = 0;
    m_video_steam = {0};
}

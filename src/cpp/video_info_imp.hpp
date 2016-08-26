//
//  video_info_imp.hpp
//  gearsbox
//
//  Created by dyno on 8/16/16.
//
//

#ifndef video_info_imp_hpp
#define video_info_imp_hpp

#include "video_info_gen.hpp"
#include "video_frame_gen.hpp"

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
    
    class VideoInfoImp: public VideoInfoGen {
    public:
        virtual ~VideoInfoImp();
        VideoInfoImp():m_width(0), m_height(0), m_fps(0), m_frame_amount(0),
        m_duration(0), m_out_w(0), m_out_h(0),m_buffer(0),m_av_picture(0),
        m_video_frame(nullptr){
            
        }
        
        virtual std::string getName(){return m_file_name;}
        
        virtual std::string getPath(){return m_path;}
        
        virtual int32_t getFPS(){return m_fps;}
        
        virtual int32_t getWidth(){return m_width;}
        
        virtual int32_t getHeight(){return m_height;}
        
        virtual int64_t getFrameAmount(){return m_frame_amount;}
        
        virtual int64_t getDuration(){return m_duration;}
        
        virtual std::shared_ptr<VideoFrameGen> getVideoFrame(){return m_video_frame;}
        
        bool initialize(std::string path, int32_t out_width, int32_t out_height);
        
    private:
        std::string m_file_name;
        std::string m_path;
        int32_t m_width;
        int32_t m_height;
        int32_t m_fps;
        int64_t m_frame_amount;
        int64_t m_duration; // second
        int32_t m_out_w;
        int32_t m_out_h;
        
        uint8_t* m_buffer;
        AVFrame* m_av_picture;
        std::shared_ptr<VideoFrameGen> m_video_frame;
    };
    
}  // namespace gearsbox


#endif /* video_info_imp_hpp */

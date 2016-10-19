//
//  ring_buffer_ptr.hpp
//  gearsbox
//
//  Created by dyno on 10/14/16.
//
//

#ifndef ring_buffer_ptr_hpp
#define ring_buffer_ptr_hpp

#include <memory>
#include <vector>

namespace gearsbox {
    class RingBufferPtr {
    public:
        static std::shared_ptr<RingBufferPtr> create(uint32_t size);
        
        RingBufferPtr(uint32_t size);
        void push(std::shared_ptr<void> data);
        std::shared_ptr<void> pop();
        uint32_t getBufferSize();
        uint32_t getDataSize();
        uint32_t getDistence();
        void resize(uint32_t size);
        void clean();
        
    private:
        typedef std::vector<std::shared_ptr<void>> VEC_DATA;
        
        VEC_DATA m_vec_data;
        VEC_DATA::size_type m_write_index;
        VEC_DATA::size_type m_read_index;
        uint32_t m_reader_catched;
        uint32_t m_writer_catched;
    };
}
#endif /* ring_buffer_ptr_hpp */

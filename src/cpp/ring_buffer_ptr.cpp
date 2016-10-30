//
//  ring_buffer_ptr.cpp
//  gearsbox
//
//  Created by dyno on 10/14/16.
//
//
#include <thread>

#include "ring_buffer_ptr.hpp"
#include "macro.h"

using namespace gearsbox;

std::shared_ptr<RingBufferPtr> RingBufferPtr::create(uint32_t size){
    return std::make_shared<RingBufferPtr>(size);
}

RingBufferPtr::RingBufferPtr(uint32_t size){
    m_vec_data.resize(size);
    m_write_index = 0;
    m_read_index = 0;
    m_reader_catched = 0;
    m_writer_catched = 0;
}

void RingBufferPtr::push(std::shared_ptr<void> data){
    CHECK_RT(data!=nullptr, "data null");
    
    if (m_writer_catched>m_reader_catched && m_write_index == m_read_index){
        return;
    }
    
    m_vec_data[m_write_index++] = data;
    if (m_write_index>= m_vec_data.size()){
        m_write_index = 0;
    }
    
    if (m_write_index == m_read_index){
        m_writer_catched = m_reader_catched+1;
        //G_LOG_FC(LOG_WARN,"buffer too small, writer on waitting");
    }
}

std::shared_ptr<void> RingBufferPtr::pop(){
    if (m_reader_catched>m_writer_catched && m_read_index == m_write_index){
        return nullptr;
    }
    
    std::shared_ptr<void> data = m_vec_data[m_read_index++];
    if (nullptr == data){
        return nullptr;
    }
    
    if (m_read_index>=m_vec_data.size()){
        m_read_index = 0;
    }
    
    if (m_write_index == m_read_index){
        m_reader_catched = m_writer_catched+1;
    }
    return data;
}

uint32_t RingBufferPtr::getBufferSize(){
    return m_vec_data.size();
}

// in overwriter mode no meaning
uint32_t RingBufferPtr::getDataSize(){
    if (m_vec_data.size() == 0)
        return 0;
    CHECK_RTP(m_read_index<m_vec_data.size() && m_write_index<m_vec_data.size()
              , 0, "index out of range, write:%d read:%d", m_write_index, m_read_index);
    if (m_read_index == m_write_index){
        return m_vec_data[m_read_index] == nullptr ? 0 : m_vec_data.size();
    }
    
    if (m_write_index > m_read_index){
        return m_write_index - m_read_index;
    }
    else {
        return m_vec_data.size() + m_write_index - m_read_index;
    }
}

uint32_t RingBufferPtr::getDistence(){
    if (m_reader_catched>m_writer_catched && (m_read_index==m_write_index)){
        return m_vec_data.size();
    }
    else if (m_writer_catched>m_reader_catched && (m_read_index==m_write_index)){
        return 0;
    }
    else if (m_write_index<m_read_index){
        return m_read_index-m_write_index;
    }
    else {// (m_write_index>m_read_index){
        return m_vec_data.size() - (m_write_index-m_read_index);
    }
}

void RingBufferPtr::resize(uint32_t size){
    uint32_t data_size = this->getDataSize();
    CHECK_RT(size >= data_size, "size lese than data");
    if (data_size == 0) {
        m_vec_data.resize(size);
        return;
    }
    
    VEC_DATA new_data;
    new_data.reserve(size);
    VEC_DATA::iterator it(m_vec_data.begin()+m_read_index);
    
    if (m_read_index < m_write_index) {
        new_data.insert(new_data.begin(), it, it+m_write_index-m_read_index);
    }
    else {
        new_data.insert(new_data.end(), it, m_vec_data.end());
        new_data.insert(new_data.end(), m_vec_data.begin(), m_vec_data.begin()+m_write_index);
    }
    new_data.resize(size);
    
    std::swap(m_vec_data, new_data);
    m_read_index = 0;
    m_write_index = data_size==m_vec_data.size() ? 0 : data_size;
    new_data.clear();
}

void RingBufferPtr::clean(){
    m_vec_data.clear();
    m_read_index = m_write_index = 0;
}

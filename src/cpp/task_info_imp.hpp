//
//  task_info_imp.hpp
//  gearsbox
//
//  Created by dyno on 8/10/16.
//
//

#ifndef task_info_imp_hpp
#define task_info_imp_hpp

#include <unordered_map>
#include "task_info_gen.hpp"
#include "uv.h"

namespace gearsbox {
    
class TaskInfoImp: public TaskInfoGen {
public:
    TaskInfoImp():m_task_id(0),m_delay(0),m_assign_tick(0),m_repeated(0){
        
    }
    
    TaskInfoImp(int64_t id, int64_t delay, int32_t repeated)
    :m_task_id(std::move(id))
    ,m_delay(std::move(delay))
    ,m_assign_tick(0)
    ,m_repeated(std::move(repeated)){
        
    }
    virtual ~TaskInfoImp() {}
    
    virtual int64_t getTaskId(){return m_task_id;}
    
    virtual int64_t getDelay(){return m_delay;}
    
    virtual int32_t getRepeated(){return m_repeated;}
    
    virtual int64_t getAssignTick(){return m_assign_tick;}
    
    virtual std::string getData(){return m_data;}
    
    virtual std::string getValue(const std::string & key);
    
    virtual int64_t getIValue(const std::string & key);
    
    virtual double getFValue(const std::string & key);
    
    virtual void setTaskId(int64_t id){m_task_id=id;}
    
    virtual void setDelay(int64_t delay){m_delay=delay;}
    
    virtual void setRepeated(int32_t repeated){m_repeated=repeated;}
    
    virtual void setAssignTick(int64_t assign){m_assign_tick=assign;}
    
    virtual void setData(const std::string & data){m_data=data;}
    
    virtual void setValue(const std::string & key, const std::string & value);
    
    virtual void setIValue(const std::string & key, int64_t value);
    
    virtual void setFValue(const std::string & key, double value);
    
private:
    typedef std::unordered_map<std::string, std::string> STR_MAP_VALUE;
    typedef std::unordered_map<std::string, int64_t> STR_MAP_IVALUE;
    typedef std::unordered_map<std::string, double> STR_MAP_FVALUE;
    int64_t m_task_id;
    int64_t m_delay;
    int64_t m_assign_tick;
    int32_t m_repeated;
    std::string m_data;
    STR_MAP_VALUE m_str_values;
    STR_MAP_IVALUE m_i64_values;
    STR_MAP_FVALUE m_f64_values;
};
    
}  // namespace gearsbox

#endif /* task_info_imp_hpp */

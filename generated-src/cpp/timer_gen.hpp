// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#pragma once

#include <cstdint>
#include <memory>

namespace gearsbox {

class TaskExcuserGen;

class TimerGen {
public:
    virtual ~TimerGen() {}

    static std::shared_ptr<TimerGen> create(int64_t task_id, int64_t interval, int32_t repeat_times, const std::shared_ptr<TaskExcuserGen> & hander);

    static int64_t currentTick();

    virtual bool start() = 0;

    virtual void stop() = 0;

    virtual void pause() = 0;

    virtual void resume() = 0;

    virtual void setInterval(int64_t interval) = 0;

    virtual int64_t getInterval() = 0;

    virtual int32_t getRepeated() = 0;

    virtual int64_t getTimePassed() = 0;

    virtual bool isRunning() = 0;
};

}  // namespace gearsbox

// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#pragma once

#include <chrono>
#include <cstdint>
#include <string>

namespace gearsbox {

class FileInfoGen {
public:
    virtual ~FileInfoGen() {}

    virtual bool initialize(const std::string & path) = 0;

    virtual int64_t getSize() = 0;

    virtual std::chrono::system_clock::time_point getCreateDate() = 0;

    virtual std::string getName() = 0;

    virtual std::string getSuffix() = 0;

    virtual std::string getPrefix() = 0;

    virtual std::string getPath() = 0;
};

}  // namespace gearsbox
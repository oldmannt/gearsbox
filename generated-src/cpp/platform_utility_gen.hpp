// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#pragma once

#include <memory>
#include <string>
#include <unordered_set>

namespace gearsbox {

class FileInfoGen;
class VideoFrameGen;
enum class LangType;

class PlatformUtilityGen {
public:
    virtual ~PlatformUtilityGen() {}

    virtual void endEniting(bool force) = 0;

    virtual LangType getLanguage() = 0;

    /**ios home directory */
    virtual std::string getHomeDirectory() = 0;

    virtual std::string getPackFilePath(const std::string & file) = 0;

    virtual std::string getPackFileBuffer(const std::string & file) = 0;

    /**copy pack file to home directory and return path in home directory */
    virtual std::string getPackFileToHomePath(const std::string & file) = 0;

    virtual std::unordered_set<std::string> getFilesFromPathBySuffix(const std::string & path, const std::string & suffix) = 0;

    virtual std::string getSubDirInHome(const std::string & sub_dir) = 0;

    virtual std::string getFileNameFromPath(const std::string & path) = 0;

    virtual std::shared_ptr<FileInfoGen> getFileInfo(const std::string & path_name) = 0;

    virtual void playVideo(const std::string & file) = 0;

    virtual std::shared_ptr<VideoFrameGen> createVideoFrame() = 0;
};

}  // namespace gearsbox

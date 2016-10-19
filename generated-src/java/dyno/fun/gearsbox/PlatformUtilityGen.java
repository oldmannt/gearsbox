// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

package dyno.fun.gearsbox;

import java.util.HashSet;

public abstract class PlatformUtilityGen {
    public abstract long getSystemTickNano();

    public abstract long getSystemTickMsec();

    public abstract double getSystemTickSec();

    public abstract void endEniting(boolean force);

    public abstract LangType getLanguage();

    /**ios home directory */
    public abstract String getHomeDirectory();

    public abstract String getPackFilePath(String file);

    public abstract String getPackFileBuffer(String file);

    /**copy pack file to home directory and return path in home directory */
    public abstract String getPackFileToHomePath(String file);

    public abstract HashSet<String> getFilesFromPathBySuffix(String path, String suffix);

    public abstract String getSubDirInHome(String subDir);

    public abstract String getFileNameFromPath(String path);

    public abstract FileInfoGen getFileInfo(String pathName);

    public abstract boolean fileExists(String pathName);

    public abstract boolean deleteFile(String fullpath);

    public abstract boolean isVideoFileCompatibleToSavedPhotosAlbum(String fullpath);

    public abstract boolean saveVideoFileToSavedPhotosAlbum(String fullpath);

    public abstract void playVideo(String file);

    public abstract void alertDialog(String tittle, String msg);

    public abstract void showLoadingView();

    public abstract VideoFrameGen createVideoFrame();
}

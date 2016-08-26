// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#import "GBLangType.h"
#import <Foundation/Foundation.h>
@protocol GBFileInfoGen;
@protocol GBVideoFrameGen;


@protocol GBPlatformUtilityGen

- (void)endEniting:(BOOL)force;

- (GBLangType)getLanguage;

/**ios home directory */
- (nonnull NSString *)getHomeDirectory;

- (nonnull NSString *)getPackFilePath:(nonnull NSString *)file;

- (nonnull NSString *)getPackFileBuffer:(nonnull NSString *)file;

/**copy pack file to home directory and return path in home directory */
- (nonnull NSString *)getPackFileToHomePath:(nonnull NSString *)file;

- (nonnull NSSet<NSString *> *)getFilesFromPathBySuffix:(nonnull NSString *)path
                                                 suffix:(nonnull NSString *)suffix;

- (nonnull NSString *)getSubDirInHome:(nonnull NSString *)subDir;

- (nonnull NSString *)getFileNameFromPath:(nonnull NSString *)path;

- (nullable id<GBFileInfoGen>)getFileInfo:(nonnull NSString *)pathName;

- (void)playVideo:(nonnull NSString *)file;

- (nullable id<GBVideoFrameGen>)createVideoFrame;

@end

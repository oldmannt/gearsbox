// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#import "GBLangType.h"
#import <Foundation/Foundation.h>
@class GBLanguageStoreGen;


@interface GBLanguageStoreGen : NSObject

+ (nullable GBLanguageStoreGen *)instance;

- (BOOL)initialize:(nonnull NSString *)param;

- (void)setLanguage:(GBLangType)lang;

- (GBLangType)getLanguage;

- (nonnull NSString *)getString:(nonnull NSString *)type;

@end
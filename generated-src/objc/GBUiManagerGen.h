// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#import <Foundation/Foundation.h>
@class GBUiManagerGen;
@protocol GBViewFactoryGen;
@protocol GBViewGen;


@interface GBUiManagerGen : NSObject

+ (nullable GBUiManagerGen *)instance;

- (BOOL)initialize:(nonnull NSString *)param
           factory:(nullable id<GBViewFactoryGen>)factory;

- (void)inject:(nullable id<GBViewGen>)view;

- (nullable id<GBViewGen>)getView:(nonnull NSString *)id;

- (nullable id<GBViewGen>)addView:(nullable id<GBViewGen>)view;

- (void)removeView:(nonnull NSString *)id;

@end

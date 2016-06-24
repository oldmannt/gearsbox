// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#import "GBViewEvent.h"
#import <Foundation/Foundation.h>

@interface GBViewEventParam : NSObject
- (nonnull instancetype)initWithX:(float)x
                                y:(float)y
                             type:(GBViewEvent)type
                             text:(nonnull NSString *)text;
+ (nonnull instancetype)viewEventParamWithX:(float)x
                                          y:(float)y
                                       type:(GBViewEvent)type
                                       text:(nonnull NSString *)text;

@property (nonatomic, readonly) float x;

@property (nonatomic, readonly) float y;

@property (nonatomic, readonly) GBViewEvent type;

@property (nonatomic, readonly, nonnull) NSString * text;

@end

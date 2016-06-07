// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#import "GBArgbColor.h"
#import <Foundation/Foundation.h>

@interface GBArgbColor : NSObject
- (nonnull instancetype)initWithA:(float)a
                                r:(float)r
                                g:(float)g
                                b:(float)b;
+ (nonnull instancetype)argbColorWithA:(float)a
                                     r:(float)r
                                     g:(float)g
                                     b:(float)b;

+ (GBArgbColor * __nonnull)noColor;
+ (GBArgbColor * __nonnull)redColor;
+ (GBArgbColor * __nonnull)greenColor;
+ (GBArgbColor * __nonnull)blueColor;
+ (GBArgbColor * __nonnull)blackColor;
+ (GBArgbColor * __nonnull)whiteColor;
@property (nonatomic, readonly) float a;

@property (nonatomic, readonly) float r;

@property (nonatomic, readonly) float g;

@property (nonatomic, readonly) float b;

@end


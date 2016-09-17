// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#import <Foundation/Foundation.h>
@class GBTimerGen;
@protocol GBTaskExcuserGen;


@interface GBTimerGen : NSObject

/**repeat_times<0 means forever, timer just pass task_id, nothing else  */
+ (nullable GBTimerGen *)create:(int64_t)taskId
                       interval:(int64_t)interval
                    repeatTimes:(int32_t)repeatTimes
                         hander:(nullable id<GBTaskExcuserGen>)hander;

+ (int64_t)currentTick;

- (BOOL)start;

- (void)stop;

- (void)pause;

- (void)resume;

- (void)setInterval:(int64_t)interval;

- (int64_t)getInterval;

- (int32_t)getRepeated;

- (int64_t)getTimePassed;

- (BOOL)isRunning;

@end

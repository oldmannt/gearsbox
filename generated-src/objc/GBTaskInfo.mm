// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from gearsbox.djinni

#import "GBTaskInfo.h"


@implementation GBTaskInfo

- (nonnull instancetype)initWithTarskId:(int32_t)tarskId
                                  delay:(int64_t)delay
                               repeated:(int32_t)repeated
                                elapsed:(int64_t)elapsed
{
    if (self = [super init]) {
        _tarskId = tarskId;
        _delay = delay;
        _repeated = repeated;
        _elapsed = elapsed;
    }
    return self;
}

+ (nonnull instancetype)taskInfoWithTarskId:(int32_t)tarskId
                                      delay:(int64_t)delay
                                   repeated:(int32_t)repeated
                                    elapsed:(int64_t)elapsed
{
    return [[self alloc] initWithTarskId:tarskId
                                   delay:delay
                                repeated:repeated
                                 elapsed:elapsed];
}

- (NSString *)description
{
    return [NSString stringWithFormat:@"<%@ %p tarskId:%@ delay:%@ repeated:%@ elapsed:%@>", self.class, (void *)self, @(self.tarskId), @(self.delay), @(self.repeated), @(self.elapsed)];
}

@end

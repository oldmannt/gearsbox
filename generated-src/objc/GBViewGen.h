// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#import "GBArgbColor.h"
#import "GBViewConf.h"
#import "GBViewConstraint.h"
#import "GBViewEvent.h"
#import "GBViewFrame.h"
#import "GBViewType.h"
#import <Foundation/Foundation.h>
@class GBViewEventHandler;
@protocol GBViewGen;

extern int32_t const GBViewGenNUMBERINT;
extern int32_t const GBViewGenNUMBERFLOAT;
extern int32_t const GBViewGenNUMBERPOSITIVE;
extern int32_t const GBViewGenNUMBERNEGATIVE;

@protocol GBViewGen

- (nonnull NSString *)getId;

- (void)setFrame:(nonnull GBViewFrame *)frame;

- (nonnull GBViewFrame *)getFrame;

- (void)setBackgroundColor:(float)a
                         r:(float)r
                         g:(float)g
                         b:(float)b;

- (void)setVisiable:(BOOL)v;

- (void)becomeFirstResponder;

- (GBViewType)getType;

- (void)setBoard:(float)width
           color:(nonnull GBArgbColor *)color;

- (void)setText:(nonnull NSString *)text;

- (nonnull NSString *)getText;

- (void)setTextColor:(nonnull GBArgbColor *)color;

- (void)setFontSize:(int32_t)size;

- (void)setNumbernic:(int32_t)type;

- (void)setMaxTextLen:(int32_t)length;

- (nullable id<GBViewGen>)getSubView:(nonnull NSString *)id;

- (nullable id<GBViewGen>)addSubViewById:(nonnull NSString *)id
                                    type:(GBViewType)type;

- (nullable id<GBViewGen>)addSubView:(nonnull GBViewConf *)conf;

- (BOOL)removeSubView:(nonnull NSString *)id;

- (void)removeAllSubView;

- (void)addConstraint:(nonnull GBViewConstraint *)constraint;

- (void)setEventHandler:(GBViewEvent)event
                handler:(nullable GBViewEventHandler *)handler;

@end

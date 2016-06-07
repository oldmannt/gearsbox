// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from ui.djinni

#import "GBViewConf.h"


@implementation GBViewConf

- (nonnull instancetype)initWithId:(nonnull NSString *)id
                              type:(GBViewType)type
                             frame:(nonnull GBViewFrame *)frame
                           bgcolor:(nonnull GBArgbColor *)bgcolor
                          fontsize:(int32_t)fontsize
                         textalign:(GBTextAlign)textalign
                       textboarder:(GBTextBoarder)textboarder
                              text:(nonnull NSString *)text
                       constraints:(nonnull NSArray<GBViewConstraint *> *)constraints
                          subviews:(nonnull NSDictionary<NSString *, GBViewConf *> *)subviews
{
    if (self = [super init]) {
        _id = [id copy];
        _type = type;
        _frame = frame;
        _bgcolor = bgcolor;
        _fontsize = fontsize;
        _textalign = textalign;
        _textboarder = textboarder;
        _text = [text copy];
        _constraints = [constraints copy];
        _subviews = [subviews copy];
    }
    return self;
}

+ (nonnull instancetype)viewConfWithId:(nonnull NSString *)id
                                  type:(GBViewType)type
                                 frame:(nonnull GBViewFrame *)frame
                               bgcolor:(nonnull GBArgbColor *)bgcolor
                              fontsize:(int32_t)fontsize
                             textalign:(GBTextAlign)textalign
                           textboarder:(GBTextBoarder)textboarder
                                  text:(nonnull NSString *)text
                           constraints:(nonnull NSArray<GBViewConstraint *> *)constraints
                              subviews:(nonnull NSDictionary<NSString *, GBViewConf *> *)subviews
{
    return [[self alloc] initWithId:id
                               type:type
                              frame:frame
                            bgcolor:bgcolor
                           fontsize:fontsize
                          textalign:textalign
                        textboarder:textboarder
                               text:text
                        constraints:constraints
                           subviews:subviews];
}

+ (GBViewFrame * __nonnull)noframe
{
    static GBViewFrame * const s_noframe = [[GBViewFrame alloc] initWithX:-1
            y:-1
            w:-1
            h:-1];
    return s_noframe;
}

+ (GBArgbColor * __nonnull)nogbcolor
{
    static GBArgbColor * const s_nogbcolor = [[GBArgbColor alloc] initWithA:-1
            r:0
            g:0
            b:0];
    return s_nogbcolor;
}

- (NSString *)description
{
    return [NSString stringWithFormat:@"<%@ %p id:%@ type:%@ frame:%@ bgcolor:%@ fontsize:%@ textalign:%@ textboarder:%@ text:%@ constraints:%@ subviews:%@>", self.class, (void *)self, self.id, @(self.type), self.frame, self.bgcolor, @(self.fontsize), @(self.textalign), @(self.textboarder), self.text, self.constraints, self.subviews];
}

@end
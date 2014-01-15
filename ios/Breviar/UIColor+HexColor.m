//
//  UIColor+HexColor.m
//  Breviar
//
//  Created by Oto Kominak on 08.01.14.
//
//

#import "UIColor+HexColor.h"

@implementation UIColor (HexColor)

+ (UIColor *)colorWithHex:(NSUInteger)hexColor {
    CGFloat alpha = (CGFloat)((0xff000000 & hexColor) >> 24) / 255.0;
    CGFloat red   = (CGFloat)((0x00ff0000 & hexColor) >> 16) / 255.0;
    CGFloat green = (CGFloat)((0x0000ff00 & hexColor) >>  8) / 255.0;
    CGFloat blue  = (CGFloat)((0x000000ff & hexColor) >>  0) / 255.0;

    if (hexColor <= 0xffffff) alpha = 1.0;

    return [UIColor colorWithRed:red green:green blue:blue alpha:alpha];
}

@end

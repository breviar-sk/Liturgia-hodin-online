//
//  BRUI.m
//  Breviar
//
//  Created by Oto Kominak on 08.01.14.
//
//

#import "BRUI.h"

@implementation BRUI

+ (BOOL)iOS7 {
#ifdef __IPHONE_7_0
    return self.osVersion >= 7;
#else
    return NO;
#endif
}

+ (float)osVersion {
    return [UIDevice currentDevice].systemVersion.floatValue;
}

+ (BOOL)isPhoneRetina4 {
    return UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone && [UIScreen mainScreen].bounds.size.height == 568.0;
}


@end

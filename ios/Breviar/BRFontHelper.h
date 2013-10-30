//
//  BRFontHelper.h
//  Breviar
//
//  Created by Gyimesi Akos on 9/9/12.
//
//

#import <Foundation/Foundation.h>

@interface BRFontHelper : NSObject

@property(strong) NSArray *availableFonts;
@property(strong) NSArray *availableSizes;
@property(strong) NSDictionary *fontNames;

+ (BRFontHelper *)instance;
- (NSString *)fontNameForFamily:(NSString *)fontFamily;

@end

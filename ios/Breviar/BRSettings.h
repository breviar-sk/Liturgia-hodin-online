//
//  BRSettings.h
//  Breviar
//
//  Created by Gyimesi Akos on 9/9/12.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface BRSettings : NSObject

@property(strong) NSArray *sections;
@property(strong) NSDictionary *options;

@property(readonly) NSDictionary *prayerQueryOptions;

@property NSString *prayerFontFamily;
@property NSInteger prayerFontSize;

+ (BRSettings *)instance;

- (BOOL)boolForOption:(NSString *)optionId;
- (void)setBool:(BOOL)value forOption:(NSString *)optionId;

- (UIFont *)fontForOption:(NSString *)optionId;
- (void)setFont:(UIFont *)value forOption:(NSString *)optionId;

- (NSString *)stringForOption:(NSString *)optionId;
- (void)setString:(NSString *)value forOption:(NSString *)optionId;
- (NSArray *)stringOptionsForOption:(NSString *)optionId;

@end

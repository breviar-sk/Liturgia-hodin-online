//
//  BRDataSource.h
//  Breviar
//
//  Created by Gyimesi Akos on 11/1/12.
//
//

#import <Foundation/Foundation.h>
#import "BRDay.h"
#import "BRCelebration.h"
#import "BRPrayer.h"

@interface BRDataSource : NSObject

@property(strong) NSString *language;

+ (BRDataSource *)instance;
- (BRDay *)dayForDate:(NSDate *)date;

@end

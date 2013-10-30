//
//  BRPrayer.h
//  Breviar
//
//  Created by Gyimesi Akos on 9/7/12.
//
//

#import <Foundation/Foundation.h>

typedef enum {
	BRInvitatory = 0,
	BROfficeOfReadings,
	BRMorningPrayer,
	BRMidMorningPrayer,
	BRMiddayPrayer,
	BRMidAfternoonPrayer,
	BREveningPrayer,
	BRCompline
} BRPrayerType;

@interface BRPrayer : NSObject {
	NSString *body;
}

@property BRPrayerType prayerType;
@property(strong) NSDate *date;
@property NSInteger celebrationId;
@property(readonly) NSString *title;
@property(readonly) NSString *body;

+ (BRPrayerType)prayerTypeFromQueryId:(NSString *)queryId;
+ (NSString *)queryIdFromPrayerType:(BRPrayerType)prayerType;

@end

//
//  BRPrayer.m
//  Breviar
//
//  Created by Gyimesi Akos on 9/7/12.
//
//

#import "BRPrayer.h"
#import "BRCGIQuery.h"
#import "BRSettings.h"
#import "BRUtil.h"

@interface BRPrayer ()
@property(strong) NSString *cachedBody;
@end

@implementation BRPrayer

@synthesize prayerType;
@synthesize title;
@synthesize body;

static NSString *prayerQueryIds[] = {
	[BRInvitatory]         = @"mi",
	[BROfficeOfReadings]   = @"mpc",
	[BRMorningPrayer]      = @"mrch",
	[BRMidMorningPrayer]   = @"mpred",
	[BRMiddayPrayer]       = @"mna",
	[BRMidAfternoonPrayer] = @"mpo",
	[BREveningPrayer]      = @"mv",
	[BRCompline]           = @"mk"
};

static NSString *prayerNames[] = {
	[BRInvitatory]         = @"Invitatory",
	[BROfficeOfReadings]   = @"Readings",
	[BRMorningPrayer]      = @"Laudes",
	[BRMidMorningPrayer]   = @"Tertia",
	[BRMiddayPrayer]       = @"Sexta",
	[BRMidAfternoonPrayer] = @"Nona",
	[BREveningPrayer]      = @"Vespers",
	[BRCompline]           = @"Compline"
};

- (NSString *)title {
	return BREVIAR_STR(prayerQueryIds[self.prayerType]);
}

- (NSString *)prayerName {
	return prayerNames[self.prayerType];
}

- (NSString *)queryId {
	return prayerQueryIds[self.prayerType];
}

- (NSString *)body {
	if (!self.cachedBody) {
		self.cachedBody = [self generateBody];
	}
	return self.cachedBody;
}

- (NSString *)generateBody {
	NSDateComponents *components = [[NSCalendar currentCalendar] components:NSDayCalendarUnit | NSMonthCalendarUnit | NSYearCalendarUnit fromDate:self.date];
	
	NSMutableDictionary *queryOptions = [NSMutableDictionary dictionary];
	[queryOptions addEntriesFromDictionary:[BRSettings instance].prayerQueryOptions];
	[queryOptions addEntriesFromDictionary:@{
											 @"qt": @"pdt",
											 @"d": [NSNumber numberWithInteger:components.day],
											 @"m": [NSNumber numberWithInteger:components.month],
											 @"r": [NSNumber numberWithInteger:components.year],
											 @"p": prayerQueryIds[self.prayerType],
											 @"ds": [NSNumber numberWithInteger:self.celebrationId],
											 @"o0": @"65",
											 @"o1": @"5440",
											 @"o2": @"16384",
											 @"o3": @"0",
											 @"o4": @"0",
											 @"o5": @"0"
											 }];
	
	return [BRCGIQuery queryWithArgs:queryOptions];
}

+ (BRPrayerType)prayerTypeFromQueryId:(NSString *)queryId {
	int i;
	for (i=BRInvitatory; i<=BRCompline; i++) {
		if ([prayerQueryIds[i] isEqualToString:queryId]) {
			return (BRPrayerType)i;
		}
	}
	return BRInvitatory;
}

+ (NSString *)queryIdFromPrayerType:(BRPrayerType)prayerType {
	return prayerQueryIds[prayerType];
}

@end

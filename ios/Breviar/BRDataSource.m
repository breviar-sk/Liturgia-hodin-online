//
//  BRDataSource.m
//  Breviar
//
//  Created by Gyimesi Akos on 11/1/12.
//
//

#import "BRDataSource.h"
#import "BRCGIQuery.h"
#import "BRSettings.h"
#import "RaptureXML/RXMLElement.h"

static BRDataSource *_instance;

@implementation BRDataSource

+ (BRDataSource *)instance {
	if (!_instance) {
		_instance = [[BRDataSource alloc] init];
	}
	return _instance;
}

- (BRDay *)dayForDate:(NSDate *)date {
	BRDay *day = [[BRDay alloc] init];
	day.date = date;
	
	NSMutableDictionary *queryOptions = [NSMutableDictionary dictionary];
	
	// Add query options for date
	NSDateComponents *components = [[NSCalendar currentCalendar] components:NSDayCalendarUnit | NSMonthCalendarUnit | NSYearCalendarUnit fromDate:date];
	NSString *dayData;
	[queryOptions addEntriesFromDictionary:@{
		 @"qt": @"pxml",
		 @"d": [NSNumber numberWithInteger:components.day],
		 @"m": [NSNumber numberWithInteger:components.month],
		 @"r": [NSNumber numberWithInteger:components.year],
		 @"j": [[BRSettings instance] stringForOption:@"j"],
	 }];
	
	// Get XML data for the day
	dayData = [BRCGIQuery queryWithArgs:queryOptions];
	
	//NSLog(@"%@", dayData);
	
	// Find XML header
	NSRange r = [dayData rangeOfString:@"<?xml"];
	if (r.location != NSNotFound) {
		dayData = [dayData substringFromIndex:r.location];
	}
	dayData = [dayData stringByAppendingString:@"</LHData>"]; // HACK
	
	// Parse XML data
	RXMLElement *xml = [RXMLElement elementFromXMLString:dayData encoding:NSWindowsCP1250StringEncoding];
	NSMutableArray *celebrations = [NSMutableArray array];
	
	// Get celebrations
	[xml iterate:@"CalendarDay.Celebration" usingBlock:^(RXMLElement *celebrationXml) {
		BRCelebration *celebration = [[BRCelebration alloc] init];
		celebration.celebrationId = [celebrationXml attributeAsInt:@"Id"];
		
		// TODO: turn HTML code into separate XML elements
		[celebrationXml iterate:@"StringTitle.span" usingBlock:^(RXMLElement *node) {
			NSString *value = node.description;
			if (!celebration.title)
				celebration.title = value;
			else
				celebration.subtitle = value;
		}];
		
		[celebrationXml iterate:@"LiturgicalCelebrationColor" usingBlock:^(RXMLElement *colorXml) {
			celebration.liturgicalColor = (BRLiturgicalColor)[colorXml attributeAsInt:@"Id"];
		}];
		
		// Create prayer objects
		NSMutableArray *prayers = [NSMutableArray array];
		int i;
		for (i=0; i<8; i++) {
			BRPrayer *prayer = [[BRPrayer alloc] init];
			prayer.date = date;
			prayer.celebrationId = celebration.celebrationId;
			prayer.prayerType = (BRPrayerType)i;
			[prayers addObject:prayer];
		}
		
		celebration.prayers = [NSArray arrayWithArray:prayers];
		[celebrations addObject:celebration];
	}];
	
	day.celebrations = [NSArray arrayWithArray:celebrations];
	return day;
}

@end

//
//  BRFontHelper.m
//  Breviar
//
//  Created by Gyimesi Akos on 9/9/12.
//
//

#import "BRFontHelper.h"

static BRFontHelper *_instance;

@implementation BRFontHelper

+ (BRFontHelper *)instance
{
	if (!_instance) {
		_instance = [[BRFontHelper alloc] init];
	}
	return _instance;
}

- (id)init {
	if (self = [super init]) {
		self.availableFonts = [NSArray arrayWithObjects:
							   @"HelveticaNeue",
							   @"HelveticaNeue-Light",
							   @"TimesNewRomanPSMT",
							   @"Baskerville",
							   @"Didot",
							   @"GillSans",
							   @"HoeflerText-Regular",
							   @"Palatino-Roman",
							   @"TrebuchetMS",
							   @"Verdana",
							   nil];
		
		self.fontNames = [NSDictionary dictionaryWithObjectsAndKeys:
						  @"Helvetica",        @"HelveticaNeue",
						  @"Helvetica Light",  @"HelveticaNeue-Light",
						  @"Times",            @"TimesNewRomanPSMT",
						  @"Baskerville",      @"Baskerville",
						  @"Didot",            @"Didot",
						  @"Gill Sans",        @"GillSans",
						  @"Hoefler Text",     @"HoeflerText-Regular",
						  @"Palatino",         @"Palatino-Roman",
						  @"Trebuchet MS",     @"TrebuchetMS",
						  @"Verdana",          @"Verdana",
						  nil];
		
		self.availableSizes = [NSArray arrayWithObjects:
							   [NSNumber numberWithInt:14],
							   [NSNumber numberWithInt:16],
							   [NSNumber numberWithInt:18],
							   [NSNumber numberWithInt:20],
							   [NSNumber numberWithInt:22],
							   nil];
	}
	return self;
}

- (NSString *)fontNameForFamily:(NSString *)fontFamily
{
	return [self.fontNames objectForKey:fontFamily];
}

@end

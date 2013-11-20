//
//  BRCGIQuery.m
//  Breviar
//
//  Created by Gyimesi Akos on 10/17/12.
//
//

#import "BRCGIQuery.h"
#import "BRUtil.h"
#include "breviar.h"
#include "myexpt.h"

@implementation BRCGIQuery

+(NSString *)queryWithArgs:(NSDictionary *)args {
	NSMutableString *queryString = [[NSMutableString alloc] init];
	NSMutableString *result = [[NSMutableString alloc] init];
	
	// Generate query string
	int i=0;
	for (NSString *key in args) {
#if DEBUG_SETTINGS
		[result appendFormat:@"%@=%@<br>", key, [args objectForKey:key]];
#endif
		
		if (i++ == 0) {
			[queryString appendFormat:@"-s%@=%@", key, [args objectForKey:key]];
		}
		else {
			[queryString appendFormat:@"&%@=%@", key, [args objectForKey:key]];
		}
	}

	// Include directory
	NSString *includeString = [NSString stringWithFormat:@"-i%@",
							   [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"html/include"]];
	
	int argc = 5;
	const char *argv[] = {
		"l.cgi",
		"-qpdt",
		"-H",
		queryString.UTF8String,
		includeString.UTF8String
	};
	breviar_main(argc, (char **)argv);
	
	NSString *prayerBody = [NSString stringWithCString:getExportedString() encoding:NSWindowsCP1250StringEncoding];
	[result appendString:prayerBody];
	return result;
}

@end

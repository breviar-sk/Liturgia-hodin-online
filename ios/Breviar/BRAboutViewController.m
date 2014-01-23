//
//  BRAboutViewController.m
//  Breviar
//
//  Created by Akos Gyimesi on 13/01/14.
//
//

#import "BRAboutViewController.h"
#import "BRSettings.h"
#import "config.build.h"
#import "GAI.h"
#import "GAIFields.h"
#import "GAIDictionaryBuilder.h"

@interface BRAboutViewController ()

@end

@implementation BRAboutViewController

- (void)viewWillAppear:(BOOL)animated
{
	// Get current language (based on UI language)
	NSArray *availableLanguages = @[@"sk", @"cs", @"hu", @"en"];
	NSString *lang = @"en";
	for (NSString *l in [NSLocale preferredLanguages]) {
		if ([availableLanguages containsObject:l]) {
			lang = l;
			break;
		}
	}
	
	// Determine about.htm location
	NSDictionary *langDirs = @{@"sk": @"html/include",
							   @"cs": @"html/include_cz",
							   @"hu": @"html/include_hu",
							   @"en": @"html"};
	
	NSString *filename = [[NSBundle mainBundle] pathForResource:@"about" ofType:@"htm" inDirectory:[langDirs objectForKey:lang]];
	
	// Load content
	NSString *aboutContent = [NSString stringWithContentsOfFile:filename encoding:NSWindowsCP1250StringEncoding error:nil];
	NSString *version = [NSString stringWithFormat:@"%@ (%@)", [NSBundle mainBundle].infoDictionary[@"CFBundleVersion"], BUILD_NUMBER];
	NSString *html = [aboutContent stringByReplacingOccurrencesOfString:@"<!--{VERSION}-->" withString:version];
	
	// Show content
	self.htmlContent = [NSString stringWithFormat:@"<div id='about'>%@</div>", html];
	[super viewWillAppear:animated];
	
	// Track page
	id<GAITracker> tracker = [[GAI sharedInstance] defaultTracker];
	[tracker set:kGAIScreenName value:@"About"];
	[tracker send:[[GAIDictionaryBuilder createAppView] build]];
}

@end

//
//  BRAboutViewController.m
//  Breviar
//
//  Created by Akos Gyimesi on 13/01/14.
//
//

#import "BRAboutViewController.h"
#import "BRSettings.h"

@interface BRAboutViewController ()

@end

@implementation BRAboutViewController

- (void)viewWillAppear:(BOOL)animated
{
	BRSettings *settings = [BRSettings instance];
	
	NSString *lang = [settings stringForOption:@"j"];
	NSDictionary *langDirs = @{@"sk": @"html/include",
							   @"cz": @"html/include_cz",
							   @"hu": @"html/include_hu"};
	
	NSString *filename = [[NSBundle mainBundle] pathForResource:@"about" ofType:@"htm" inDirectory:[langDirs objectForKey:lang]];
	NSString *aboutContent = [NSString stringWithContentsOfFile:filename encoding:NSWindowsCP1250StringEncoding error:nil];
	self.htmlContent = [NSString stringWithFormat:@"<div id='about'>%@</div>", aboutContent];
	[super viewWillAppear:animated];
}

@end

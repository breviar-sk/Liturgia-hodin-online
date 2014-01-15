//
//  BRWebViewController.m
//  Breviar
//
//  Created by Akos Gyimesi on 13/01/14.
//
//

#import "BRWebViewController.h"
#import "BRSettings.h"

@interface BRWebViewController ()

@end

@implementation BRWebViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.webView.scrollView.decelerationRate = UIScrollViewDecelerationRateNormal;
}

- (void)viewWillAppear:(BOOL)animated {
	[super viewWillAppear:animated];
	
	BRSettings *settings = [BRSettings instance];
	
	NSMutableString *extraStylesheets = [[NSMutableString alloc] init];
	if ([settings boolForOption:@"of0fn"]) {
		[extraStylesheets appendString:@"<link rel='stylesheet' type='text/css' href='html/breviar-normal-font.css'>"];
	}
    // Night mode
	if ([settings boolForOption:@"of2nr"]) {
		[extraStylesheets appendString:@"<link rel='stylesheet' type='text/css' href='html/breviar-invert-colors.css'>"];
        self.view.backgroundColor = [UIColor colorWithHex:0x333333];
        self.webView.scrollView.indicatorStyle = UIScrollViewIndicatorStyleWhite;
	}
	
	NSString *body =
	[NSString stringWithFormat:
	 @"<!DOCTYPE html>\n"
	 "<html><head>\n"
	 "	<meta http-equiv='Content-Type' content='text/html; charset=windows-1250'>\n"
	 "	<link rel='stylesheet' type='text/css' href='html/breviar.css'>\n"
	 "	<link rel='stylesheet' type='text/css' href='breviar-ios.css'>\n"
	 "  %@\n"
	 "</head>\n"
	 "<body style='padding-top: 64px; font: %dpx %@'>%@</body>\n"
	 "</html>",
	 extraStylesheets,
	 settings.prayerFontSize,
	 settings.prayerFontFamily,
	 self.htmlContent];
	
	NSURL *baseURL = [NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]];
	[self.webView loadHTMLString:body baseURL:baseURL];
}

@end

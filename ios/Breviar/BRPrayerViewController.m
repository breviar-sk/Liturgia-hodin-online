//
//  BRPrayerViewController.m
//  Breviar
//
//  Created by Gyimesi Akos on 9/7/12.
//
//

#import "BRPrayerViewController.h"
#import "BRSettings.h"

@interface BRPrayerViewController ()

@end

@implementation BRPrayerViewController
@synthesize prayer;

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
	// Do any additional setup after loading the view.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void)viewWillAppear:(BOOL)animated {
	self.navigationItem.title = self.prayer.title;
	
	BRSettings *settings = [BRSettings instance];
	
	NSString *body =
		[NSString stringWithFormat:
		 @"<!DOCTYPE html>\n"
		 "<html><head>\n"
		 "	<meta http-equiv='Content-Type' content='text/html; charset=windows-1250'>\n"
		 "	<link rel='stylesheet' type='text/css' href='html/breviar.css'>\n"
		 "	<link rel='stylesheet' type='text/css' href='breviar-ios.css'>\n"
		 "</head>\n"
		 "<body style='font: %dpx %@'>%@</body>\n"
		 "</html>",
		 settings.prayerFontSize,
		 settings.prayerFontFamily,
		 self.prayer.body];
	
	NSURL *baseURL = [NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]];
	[self.webView loadHTMLString:body baseURL:baseURL];
}

@end

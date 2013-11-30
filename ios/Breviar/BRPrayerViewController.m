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
	
	UITapGestureRecognizer *tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(showHideNavbar:)];
	tapGesture.delegate = self;
	[self.view addGestureRecognizer:tapGesture];
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
		 "<body style='padding-top: 64px; font: %dpx %@'>%@</body>\n"
		 "</html>",
		 settings.prayerFontSize,
		 settings.prayerFontFamily,
		 self.prayer.body];
	
	NSURL *baseURL = [NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]];
	[self.webView loadHTMLString:body baseURL:baseURL];
}

- (void)showHideNavbar:(id)sender
{
	BOOL navbarHidden = [UIApplication sharedApplication].isStatusBarHidden;
	
	if (navbarHidden) {
		self.navigationController.navigationBarHidden = NO;
		self.navigationController.navigationBar.alpha = 0;
	}
	
	[UIView animateWithDuration:UINavigationControllerHideShowBarDuration
					 animations:^{
						 [[UIApplication sharedApplication] setStatusBarHidden:!navbarHidden withAnimation:UIStatusBarAnimationFade];
						 self.navigationController.navigationBar.alpha = navbarHidden ? 1.0 : 0.0;
					 }
					 completion:^(BOOL finished) {
						 if (finished && !navbarHidden) {
							 self.navigationController.navigationBarHidden = YES;
						 }
					 }
	 ];
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer
{
	return YES;
}

@end

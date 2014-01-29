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
@property(strong) NSString *oldHtmlSource;
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
    
    // Use shared web view. Hide it now, and show it using animation once the content is loaded
    self.webView.alpha = 0;
    self.webView.delegate = self;
    self.webView.scrollView.decelerationRate = UIScrollViewDecelerationRateNormal;
    
    [self.webView removeFromSuperview];
    [self.view addSubview:self.webView];
}

- (void)viewWillAppear:(BOOL)animated {
	[super viewWillAppear:animated];
	
    self.webView.frame = self.view.bounds;
    self.webView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    
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
    } else {
        self.view.backgroundColor = [UIColor colorWithHex:0xFBFCD7];
        self.webView.scrollView.indicatorStyle = UIScrollViewIndicatorStyleDefault;
    }
	
	NSString *htmlSource =
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
	
	if (![htmlSource isEqual:self.oldHtmlSource]) {
		NSURL *baseURL = [NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]];
		[self.webView loadHTMLString:htmlSource baseURL:baseURL];
		self.oldHtmlSource = htmlSource;
	}
}

- (void)webViewDidFinishLoad:(UIWebView *)webView {
    [UIView animateWithDuration:0.25 delay:0 options:UIViewAnimationOptionCurveEaseInOut animations:^{
        self.webView.alpha = 1;
    } completion:nil];
}

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType {
	// Allow requests to local files only
	return request.URL.isFileURL;
}

@end

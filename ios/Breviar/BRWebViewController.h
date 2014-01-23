//
//  BRWebViewController.h
//  Breviar
//
//  Created by Akos Gyimesi on 13/01/14.
//
//

#import <UIKit/UIKit.h>
#import "BRViewController.h"

@interface BRWebViewController : UIViewController <UIWebViewDelegate>
@property(strong) IBOutlet UIWebView *webView;
@property(strong) NSString *htmlContent;
@end

//
//  BRWebViewController.h
//  Breviar
//
//  Created by Akos Gyimesi on 13/01/14.
//
//

#import <UIKit/UIKit.h>

@interface BRWebViewController : UIViewController
@property(strong) IBOutlet UIWebView *webView;
@property(strong) NSString *htmlContent;
@end

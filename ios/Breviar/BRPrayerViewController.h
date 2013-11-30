//
//  BRPrayerViewController.h
//  Breviar
//
//  Created by Gyimesi Akos on 9/7/12.
//
//

#import <UIKit/UIKit.h>
#import "BRPrayer.h"

@interface BRPrayerViewController : UIViewController <UIGestureRecognizerDelegate>
@property(strong) BRPrayer *prayer;
@property(strong) IBOutlet UIWebView *webView;
@end

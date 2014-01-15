//
//  BRPrayerViewController.h
//  Breviar
//
//  Created by Gyimesi Akos on 9/7/12.
//
//

#import <UIKit/UIKit.h>
#import "BRWebViewController.h"
#import "BRPrayer.h"

@interface BRPrayerViewController : BRWebViewController <UIGestureRecognizerDelegate>
@property(strong) BRPrayer *prayer;
@end

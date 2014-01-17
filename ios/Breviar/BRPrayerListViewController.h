//
//  BRPrayerListViewController.h
//  Breviar
//
//  Created by Gyimesi Akos on 9/7/12.
//
//

#import <UIKit/UIKit.h>
#import "BRDatePickerViewController.h"
#import "BRDay.h"

@interface BRPrayerListViewController : UIViewController <BRDatePickerDelegate, UITableViewDataSource, UITableViewDelegate>

- (void)loadSelectedDateAndReloadTable:(BOOL)reload resetCelebrationIndex:(BOOL)resetCelebration;

@end

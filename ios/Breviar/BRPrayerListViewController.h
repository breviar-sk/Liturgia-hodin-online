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

@property(weak) IBOutlet UITableView *tableView;
@property(weak) IBOutlet UIButton *showDatePickerButton;

@property(strong) UIPopoverController *datePickerPopover;

@property(strong) NSDate *date;
@property(strong) BRDay *day;
@property(strong) NSArray *sections;
@property NSInteger celebrationIndex;

@end

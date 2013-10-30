//
//  BRDatePickerViewController.h
//  Breviar
//
//  Created by Gyimesi Akos on 9/8/12.
//
//

#import <UIKit/UIKit.h>

@class BRDatePickerViewController;

@protocol BRDatePickerDelegate <NSObject>
- (void)datePicker:(BRDatePickerViewController *)datePicker pickedDate:(NSDate *)date;
@end

@interface BRDatePickerViewController : UIViewController

@property(strong) IBOutlet UIDatePicker *datePicker;
@property(weak) IBOutlet NSObject<BRDatePickerDelegate> *datePickerDelegate;
@property(strong) NSDate *initialDate;

- (IBAction)donePressed:(id)sender;
- (IBAction)todayPressed:(id)sender;
- (IBAction)tomorrowPressed:(id)sender;
- (IBAction)yesterdayPressed:(id)sender;

@end

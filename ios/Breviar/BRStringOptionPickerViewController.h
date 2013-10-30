//
//  BRStringOptionPickerViewController.h
//  Breviar
//
//  Created by Gyimesi Akos on 4/14/13.
//
//

#import <UIKit/UIKit.h>

@class BRStringOptionPickerViewController;

@protocol BRStringOptionPickerDelegate <NSObject>
- (void)stringOptionPicker:(BRStringOptionPickerViewController *)picker didPickOption:(NSString *)value;
@end

@interface BRStringOptionPickerViewController : UIViewController <UITableViewDataSource,UITableViewDelegate>

@property(weak) IBOutlet UITableView *tableView;
@property(weak) IBOutlet UINavigationBar *navigationBar;
@property(weak) NSObject<BRStringOptionPickerDelegate> *delegate;
@property(strong) NSString *optionId;
@property(strong) NSArray *options;
@property(strong) NSString *currentValue;

- (IBAction)doneButtonPressed:(id)sender;

@end

//
//  BRSettingsViewController.h
//  Breviar
//
//  Created by Gyimesi Akos on 9/8/12.
//
//

#import <UIKit/UIKit.h>
#import "BRFontPickerViewController.h"
#import "BRStringOptionPickerViewController.h"

@interface BRSettingsViewController : UITableViewController <BRFontPickerDelegate, BRStringOptionPickerDelegate, UITableViewDelegate, UITableViewDataSource>

@property(strong) NSString *currentOptionId;

@end

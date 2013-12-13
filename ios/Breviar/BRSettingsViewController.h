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
#import "BRBoolSettingsCell.h"

@interface BRSettingsViewController : UITableViewController <BRFontPickerDelegate, BRStringOptionPickerDelegate, UITableViewDelegate, UITableViewDataSource, BRBoolSettingsCellDelegate>

@property(strong) NSString *currentOptionId;
@property(strong) NSDictionary *visibleOptionIndexPaths;
@property(strong) NSArray *visibleOptionsPerSection;

@end

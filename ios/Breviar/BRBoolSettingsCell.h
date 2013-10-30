//
//  BRBoolSettingsCell.h
//  Breviar
//
//  Created by Gyimesi Akos on 1/27/13.
//
//

#import <UIKit/UIKit.h>

@interface BRBoolSettingsCell : UITableViewCell
@property(strong) NSString *optionId;
@property(weak, nonatomic) IBOutlet UILabel *label;
@property(weak, nonatomic) IBOutlet UISwitch *switcher;

- (IBAction)switcherChanged:(id)sender;
@end

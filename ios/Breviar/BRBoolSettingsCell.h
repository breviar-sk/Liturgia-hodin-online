//
//  BRBoolSettingsCell.h
//  Breviar
//
//  Created by Gyimesi Akos on 1/27/13.
//
//

#import <UIKit/UIKit.h>

@protocol BRBoolSettingsCellDelegate <NSObject>
- (void)boolOptionChanged:(NSString *)optionId toValue:(BOOL)newValue;
@end

@interface BRBoolSettingsCell : UITableViewCell
@property(strong) NSString *optionId;
@property(weak, nonatomic) IBOutlet UILabel *label;
@property(weak, nonatomic) IBOutlet UISwitch *switcher;
@property(weak, nonatomic) NSObject<BRBoolSettingsCellDelegate> *delegate;

- (IBAction)switcherChanged:(id)sender;
@end

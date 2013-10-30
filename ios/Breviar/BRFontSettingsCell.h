//
//  BRFontSettingsCell.h
//  Breviar
//
//  Created by Gyimesi Akos on 1/26/13.
//
//

#import <UIKit/UIKit.h>

@interface BRFontSettingsCell : UITableViewCell
@property(strong) NSString *optionId;
@property(weak,nonatomic) IBOutlet UILabel *fontLabel;
@end

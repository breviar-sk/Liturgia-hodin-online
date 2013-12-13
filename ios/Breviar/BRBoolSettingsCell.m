//
//  BRBoolSettingsCell.m
//  Breviar
//
//  Created by Gyimesi Akos on 1/27/13.
//
//

#import "BRBoolSettingsCell.h"
#import "BRSettings.h"

@implementation BRBoolSettingsCell

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code
    }
    return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    //[super setSelected:selected animated:animated];
}

- (IBAction)switcherChanged:(id)sender
{
	[[BRSettings instance] setBool:self.switcher.on forOption:self.optionId];
	[self.delegate boolOptionChanged:self.optionId toValue:self.switcher.on];
}

@end

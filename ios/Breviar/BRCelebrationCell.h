//
//  BRCelebrationCell.h
//  Breviar
//
//  Created by Gyimesi Akos on 1/12/13.
//
//

#import <UIKit/UIKit.h>

@interface BRCelebrationCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UILabel *celebrationNameLabel;
@property (weak, nonatomic) IBOutlet UILabel *celebrationDescriptionLabel;
@property (weak, nonatomic) IBOutlet UIImageView *liturgicalColorView;
@end

//
//  BRFontPickerViewController.h
//  Breviar
//
//  Created by Gyimesi Akos on 9/8/12.
//
//

#import <UIKit/UIKit.h>
#import "BRViewController.h"

@class BRFontPickerViewController;

@protocol BRFontPickerDelegate <NSObject>
- (void)fontPicker:(BRFontPickerViewController *)fontPicker didPickFont:(UIFont *)font;
@end

@interface BRFontPickerViewController : BRViewController <UIPickerViewDataSource, UIPickerViewDelegate>

@property(strong) NSString *fontFamily;
@property NSInteger fontSize;
@property(weak) NSObject<BRFontPickerDelegate> *delegate;

@end

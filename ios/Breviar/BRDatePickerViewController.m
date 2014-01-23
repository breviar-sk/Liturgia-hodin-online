//
//  BRDatePickerViewController.m
//  Breviar
//
//  Created by Gyimesi Akos on 9/8/12.
//
//

#import "BRDatePickerViewController.h"

@interface BRDatePickerViewController ()

@property (strong, nonatomic) IBOutlet UIDatePicker *datePicker;
@property (strong, nonatomic) IBOutlet UIView *datePickerPlaceholder;
@property (strong, nonatomic) IBOutlet UIToolbar *toolbar;
@property (strong, nonatomic) IBOutlet UIBarButtonItem *toolbarCenteringItem;
@property (strong, nonatomic) IBOutlet UIButton *todayButton;

@end

@implementation BRDatePickerViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	self.screenName = @"DataPicker";
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (void)viewWillAppear:(BOOL)animated
{
	[super viewWillAppear:animated];
    
    if (!self.datePicker) {
        self.datePicker = [[UIDatePicker alloc] init];
        self.datePicker.datePickerMode = UIDatePickerModeDate;
        
        
        if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
            self.datePicker.frame = self.datePickerPlaceholder.bounds;
            [self.datePickerPlaceholder addSubview:self.datePicker];
        }
        
        else if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
            CGRect rect = self.datePicker.frame;
            rect.size.width = self.view.frame.size.width;
            rect.origin.y = self.toolbar.frame.size.height;
            self.datePicker.frame = rect;
            [self.view addSubview:self.datePicker];
        }
    }

	self.datePicker.date = self.initialDate;

    // Center the toolbar content in iPad popover (Yesterday/Today/Tomorrow)
    if (self.toolbarCenteringItem) {
        UIView *doneButtonView = self.toolbar.subviews.lastObject;
        if (doneButtonView) {
            self.toolbarCenteringItem.width = doneButtonView.frame.size.width;
        }
    }
}

#pragma mark -

- (IBAction)donePressed:(id)sender
{
	[self.datePickerDelegate datePicker:self pickedDate:self.datePicker.date];
}

- (IBAction)todayPressed:(id)sender
{
	self.datePicker.date = [NSDate date];
}

- (IBAction)tomorrowPressed:(id)sender
{
	NSDate *now = [NSDate date];
	
	NSDateComponents *comps = [[NSDateComponents alloc] init];
	comps.day = 1;
	
	NSCalendar *cal = [[NSCalendar alloc] initWithCalendarIdentifier:NSGregorianCalendar];
	NSDate *tomorrow = [cal dateByAddingComponents:comps toDate:now options:0];
	
	[self.datePicker setDate:tomorrow animated:YES];
}

- (IBAction)yesterdayPressed:(id)sender
{
	NSDate *now = [NSDate date];
	
	NSDateComponents *comps = [[NSDateComponents alloc] init];
	comps.day = -1;
	
	NSCalendar *cal = [[NSCalendar alloc] initWithCalendarIdentifier:NSGregorianCalendar];
	NSDate *yesterday = [cal dateByAddingComponents:comps toDate:now options:0];
	
	[self.datePicker setDate:yesterday animated:YES];
}

@end

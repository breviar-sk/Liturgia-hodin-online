//
//  BRDatePickerViewController.m
//  Breviar
//
//  Created by Gyimesi Akos on 9/8/12.
//
//

#import "BRDatePickerViewController.h"

@interface BRDatePickerViewController ()

@end

@implementation BRDatePickerViewController

@synthesize datePicker;
@synthesize datePickerDelegate;
@synthesize initialDate;

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
	// Do any additional setup after loading the view.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (void)viewWillAppear:(BOOL)animated
{
	[super viewWillAppear:animated];
	self.datePicker.date = self.initialDate;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
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

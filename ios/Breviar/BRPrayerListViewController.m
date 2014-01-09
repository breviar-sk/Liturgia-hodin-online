//
//  BRPrayerListViewController.m
//  Breviar
//
//  Created by Gyimesi Akos on 9/7/12.
//
//

#import "BRPrayerListViewController.h"
#import "BRPrayerViewController.h"
#import "BRDataSource.h"
#import "BRCelebrationCell.h"
#import "BRUtil.h"

static NSString *liturgicalColorImages[] = {
	[BRColorUnknown]       = @"",
	[BRColorRed]           = @"bullet_red.png",
	[BRColorWhite]         = @"bullet_white.png",
	[BRColorGreen]         = @"bullet_green.png",
	[BRColorViolet]        = @"bullet_violet.png",
	[BRColorRose]          = @"bullet_rose.png",
	[BRColorBlack]         = @"bullet_black.png",
	[BRColorVioletOrBlack] = @"bullet_violet_or_black.png",
	[BRColorVioletOrWhite] = @"bullet_violet_or_white.png",
	[BRColorRoseOrViolet]  = @"bullet_rose_or_violet.png"
};

@interface BRPrayerListViewController ()

@end

@implementation BRPrayerListViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	self.date = [NSDate date];
	
	if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
		self.sections = @[@"Date", @"PrayerListCell", @"Settings"];
	}
	else {
		self.sections = @[@"Date", @"PrayerList"];
	}
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}

- (void)viewWillAppear:(BOOL)animated
{
	[super viewWillAppear:animated];
	
	// Load celebrations for date
	self.day = [[BRDataSource instance] dayForDate:self.date];
	if (self.celebrationIndex > self.day.celebrations.count - 1) {
		self.celebrationIndex = 0;
	}
	
	// Show date in title
	[self updateTitleView];
	
	// Update data
	[self.tableView reloadData];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
	return self.sections.count;
}

#pragma mark -
#pragma mark Title view

- (void)updateTitleView
{
	self.navigationItem.title = [self getDateLabel];
	self.navigationItem.titleView = [self getTitleView];
}

- (UIView *)getTitleView
{
	UIButton *btn = [[UIButton alloc] init];
	[btn setTitle:[self getDateLabel] forState:UIControlStateNormal];
	btn.titleLabel.font = [UIFont boldSystemFontOfSize:18.0];
	[btn addTarget:self action:@selector(showDatePicker:) forControlEvents:UIControlEventTouchUpInside];
	return btn;
}

- (NSString *)getDateLabel
{
	NSCalendar *calendar = [NSCalendar currentCalendar];
	NSInteger currentDay = [calendar ordinalityOfUnit:NSDayCalendarUnit inUnit:NSEraCalendarUnit forDate:[NSDate date]];
	NSInteger selectedDay = [calendar ordinalityOfUnit:NSDayCalendarUnit inUnit:NSEraCalendarUnit forDate:self.date];
    
    int dayDiff = ABS(currentDay - selectedDay);
	
	if (dayDiff < 3) {
		NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
		dateFormatter.dateFormat = @"EEEE";
		return [[dateFormatter stringFromDate:self.date] capitalizedString];
	}
	else {
		NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
		[dateFormatter setDateStyle:NSDateFormatterLongStyle];
		return [dateFormatter stringFromDate:self.date];
	}
}

#pragma mark -
#pragma mark UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	NSString *sectionType = [self.sections objectAtIndex:section];
	
	if ([sectionType isEqualToString:@"Date"]) {
		return self.day.celebrations.count;
	}
	else if ([sectionType isEqualToString:@"PrayerList"]) {
		return 8;
	}
	else {
		return 1;
	}
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	NSString *sectionType = [self.sections objectAtIndex:indexPath.section];
	
	if ([sectionType isEqualToString:@"Date"]) {
		// Celebration cell
		BRCelebrationCell *cell = [tableView dequeueReusableCellWithIdentifier:@"CelebrationCell"];
		
		BRCelebration *celebration = [self.day.celebrations objectAtIndex:indexPath.row];
		cell.celebrationNameLabel.text = celebration.title;
		cell.celebrationDescriptionLabel.text = celebration.subtitle;
		cell.liturgicalColorView.image = [UIImage imageNamed:liturgicalColorImages[celebration.liturgicalColor]];
		cell.accessoryType = (self.celebrationIndex == indexPath.row ? UITableViewCellAccessoryCheckmark : UITableViewCellAccessoryNone);
		
		return cell;
	}
	else if ([sectionType isEqualToString:@"PrayerListCell"]) {
		// Prayer list cell
		UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"PrayerListCell"];
		
		return cell;
	}
	else if ([sectionType isEqualToString:@"PrayerList"]) {
		UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"PrayerCell"];
		
		cell.textLabel.text = BREVIAR_STR([BRPrayer queryIdFromPrayerType:(BRPrayerType)indexPath.row]);
		return cell;
	}
	else if ([sectionType isEqualToString:@"Settings"]) {
		// Settings cell
		return [tableView dequeueReusableCellWithIdentifier:@"SettingsCell"];
	}
	
	return nil;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
	NSString *sectionType = [self.sections objectAtIndex:indexPath.section];
	
	if ([sectionType isEqualToString:@"PrayerListCell"]) {
		return 125;
	}
	else {
		return 44;
	}
}

#pragma mark -
#pragma mark UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	NSString *sectionType = [self.sections objectAtIndex:indexPath.section];
	
	if ([sectionType isEqualToString:@"Date"]) {
		// Select celebration
		NSIndexPath *oldIndexPath = [NSIndexPath indexPathForRow:self.celebrationIndex inSection:indexPath.section];
		[self.tableView cellForRowAtIndexPath:oldIndexPath].accessoryType = UITableViewCellAccessoryNone;
		[self.tableView cellForRowAtIndexPath:indexPath].accessoryType = UITableViewCellAccessoryCheckmark;
		
		self.celebrationIndex = indexPath.row;
		[self.tableView deselectRowAtIndexPath:indexPath animated:YES];
	}
}

#pragma mark -
#pragma mark Date selection

- (void)showDatePicker:(id)sender
{
	[self performSegueWithIdentifier:@"ShowDatePicker" sender:self];
}

- (void)jumpDate:(int)dayDiff
{
	NSDateComponents *components = [[NSDateComponents alloc] init];
	[components setDay:dayDiff];
	
	self.date = [[NSCalendar currentCalendar] dateByAddingComponents:components toDate:self.date options:0];
	self.day = [[BRDataSource instance] dayForDate:self.date];
	self.celebrationIndex = 0;
	
	[self updateTitleView];
	
	NSIndexSet *indexSet = [NSIndexSet indexSetWithIndexesInRange:NSMakeRange(0, self.sections.count)];
	[self.tableView reloadSections:indexSet withRowAnimation:(dayDiff > 0 ? UITableViewRowAnimationLeft : UITableViewRowAnimationRight)];
}

- (IBAction)prevDayPressed:(id)sender
{
	[self jumpDate:-1];
}

- (IBAction)nextDayPressed:(id)sender
{
	[self jumpDate:1];
}

#pragma mark -
#pragma mark UI transitions

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
	NSString *segueId = segue.identifier;
	
	if ([segueId isEqualToString:@"ShowDatePicker"]) {
		BRDatePickerViewController *destController;
        
        if ([segue.destinationViewController isKindOfClass:[BRDatePickerViewController class]]) {
            destController = segue.destinationViewController;
        } else {
            UINavigationController *navController = segue.destinationViewController;
            destController = [navController.viewControllers objectAtIndex:0];
        }
        
		destController.initialDate = self.date;
		destController.datePickerDelegate = self;
		
		if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
			self.datePickerPopover = [(UIStoryboardPopoverSegue *)segue popoverController];
		}
	}
	else if ([segueId isEqualToString:@"ShowPrayer"]) {
		BRPrayerViewController *destController = segue.destinationViewController;
		NSIndexPath *indexPath = [self.tableView indexPathForSelectedRow];
		BRPrayerType prayerType = (BRPrayerType)indexPath.row;
		BRCelebration *celebration = [self.day.celebrations objectAtIndex:self.celebrationIndex];
		destController.prayer = [celebration.prayers objectAtIndex:prayerType];
	}
	else if ([[segueId substringToIndex:11] isEqualToString:@"ShowPrayer."]) {
		BRPrayerViewController *destController = segue.destinationViewController;
		NSString *prayerQueryId = [segueId substringFromIndex:11];
		BRPrayerType prayerType = [BRPrayer prayerTypeFromQueryId:prayerQueryId];
		BRCelebration *celebration = [self.day.celebrations objectAtIndex:self.celebrationIndex];
		destController.prayer = [celebration.prayers objectAtIndex:prayerType];
	}
}

- (void)datePicker:(BRDatePickerViewController *)datePicker pickedDate:(NSDate *)date
{
	self.date = date;
	self.day = [[BRDataSource instance] dayForDate:self.date];
	self.celebrationIndex = 0;
	
	if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
		[self dismissViewControllerAnimated:YES completion:nil];
	}
	else if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
		[self.datePickerPopover dismissPopoverAnimated:YES];
		[self updateTitleView];
		[self.tableView reloadData];
		self.datePickerPopover = nil;
	}
}

@end

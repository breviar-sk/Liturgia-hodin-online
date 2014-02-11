//
//  BRPrayerListViewController.m
//  Breviar
//
//  Created by Gyimesi Akos on 9/7/12.
//
//

#import "BRPrayerListViewController.h"
#import "BRPrayerViewController.h"
#import "BRAboutViewController.h"
#import "BRDataSource.h"
#import "BRCelebrationCell.h"
#import "BRUtil.h"
#import "BRSettings.h"

#import "GAI.h"
#import "GAIDictionaryBuilder.h"
#import "GAIFields.h"

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

@property (nonatomic, weak) IBOutlet UITableView *tableView;
@property (nonatomic, weak) IBOutlet UIButton *showDatePickerButton; // Unused?
@property (nonatomic, strong) UIPopoverController *datePickerPopover;

@property (nonatomic, strong) UIWebView *sharedWebView;
@property (nonatomic, strong) BRCelebrationCell *celebrationCellPortrait;
@property (nonatomic, strong) BRCelebrationCell *celebrationCellLanscape;

@property (strong) NSDate *date;
@property (strong) BRDay *day;
@property NSInteger celebrationIndex;

@property (strong) dispatch_queue_t preloadQueue;

@end

@implementation BRPrayerListViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
	self.screenName = @"MainScreen";
	self.preloadQueue = dispatch_queue_create("Prayer Generator Queue", DISPATCH_QUEUE_SERIAL);

	self.date = [NSDate date];
    
    // Prepare reusable web view
    self.sharedWebView = [[UIWebView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)];
    self.sharedWebView.backgroundColor = [UIColor clearColor];
    self.sharedWebView.opaque = NO;
    [self.view addSubview:self.sharedWebView];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(applicationWillEnterForeground:)
                                                 name:UIApplicationWillEnterForegroundNotification
                                               object:nil];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}

- (void)viewWillAppear:(BOOL)animated
{
	[super viewWillAppear:animated];
	
	// Load celebrations for date (if not already loaded for the very same date, e.g. when going back from prayer VC)
    if (!self.day) {
        [self loadSelectedDateAndReloadTable:YES resetCelebrationIndex:YES forcePrayerRegeneration:NO];
    } else {
        [self updateTitleView];
        
        // Deselect row when returning from subcontroller to give the user a sense of context
        if (self.tableView.indexPathForSelectedRow) {
            [self.tableView deselectRowAtIndexPath:self.tableView.indexPathForSelectedRow animated:YES];
        }
    }
}

- (void)applicationWillEnterForeground:(NSNotification *)notification {
    if (self.day && self.navigationController.topViewController == self) {
        [self updateTitleView];
    }
}

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration {
	[super willRotateToInterfaceOrientation:toInterfaceOrientation duration:duration];
	[self.tableView reloadData];
}

#pragma mark - Data Source, Loader, etc.

- (NSArray *)sections {
    BRSettings *settings = [BRSettings instance];
    BOOL prayersAsCells = [settings boolForOption:@"prayersAsCells"];
    
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone && !prayersAsCells) {
		return @[@"Date", @"PrayerListCell", @"Settings"];
	}
	else {
		return @[@"Date", @"PrayerList", @"Settings"];
	}
}

- (void)loadSelectedDateAndReloadTable:(BOOL)reload resetCelebrationIndex:(BOOL)resetCelebration forcePrayerRegeneration:(BOOL)regenerate {
    
	if (regenerate || !self.day || ![[self dayComponentsForDate:self.day.date] isEqual:[self dayComponentsForDate:self.date]]) {
		self.day = [[BRDataSource instance] dayForDate:self.date];
		
        if (self.celebrationIndex > self.day.celebrations.count - 1) {
            self.celebrationIndex = 0;
        }
		
		[self preloadPrayers];
    }

    if (resetCelebration) {
        self.celebrationIndex = 0;
    }
    
    // Show date in title
    [self updateTitleView];
    
    // Update data
    if (reload) {
        [self.tableView reloadData];
    }
}

- (NSDateComponents *)dayComponentsForDate:(NSDate *)date {
	NSCalendarUnit dayUnit = NSYearCalendarUnit | NSMonthCalendarUnit | NSDayCalendarUnit;
	return [[NSCalendar currentCalendar] components:dayUnit fromDate:date];
}

- (void)preloadPrayers {
	BRDay *day = self.day;
	dispatch_async(self.preloadQueue, ^{
		for (BRCelebration *celebration in day.celebrations) {
			for (BRPrayer *prayer in celebration.prayers) {
				if (day == self.day) {
					[prayer body];
				}
			}
		}
	});
}

#pragma mark -
#pragma mark UITableViewDataSource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
	return self.sections.count;
}

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

- (NSString *)celebrationCellType {
	return UIInterfaceOrientationIsPortrait(self.interfaceOrientation) ? @"CelebrationCellPortrait" : @"CelebrationCellLandscape";
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	NSString *sectionType = [self.sections objectAtIndex:indexPath.section];
	
	if ([sectionType isEqualToString:@"Date"]) {
		// Celebration cell
		BRCelebrationCell *cell = [tableView dequeueReusableCellWithIdentifier:[self celebrationCellType]];
		
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
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"SettingsCell"];
		return cell;
	}
	
	return nil;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
	NSString *sectionType = [self.sections objectAtIndex:indexPath.section];
	
	if ([sectionType isEqualToString:@"PrayerListCell"]) {
		return 125;
	}
	else if ([sectionType isEqualToString:@"Date"]) {
		BRCelebrationCell *cell = [tableView dequeueReusableCellWithIdentifier:[self celebrationCellType]];
		cell.bounds = CGRectMake(0.0f, 0.0f, CGRectGetWidth(tableView.bounds), CGRectGetHeight(cell.bounds));
		
		BRCelebration *celebration = [self.day.celebrations objectAtIndex:indexPath.row];
		cell.celebrationNameLabel.text = celebration.title;
		cell.celebrationDescriptionLabel.text = celebration.subtitle;
		cell.accessoryType = UITableViewCellAccessoryCheckmark;

		[cell.contentView setNeedsLayout];
		[cell.contentView layoutIfNeeded];
		
		CGFloat height = [cell.contentView systemLayoutSizeFittingSize:UILayoutFittingCompressedSize].height;
		return height + 2;
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
#pragma mark Title view

- (void)updateTitleView
{
    if (![self.navigationItem.title isEqualToString:[self getDateLabel]]) {
        self.navigationItem.title = [self getDateLabel];
        self.navigationItem.titleView = [self getTitleView];
    }
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
    
    NSInteger dayDiff = ABS(currentDay - selectedDay);
	
    if (dayDiff < 3) {
		NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
		dateFormatter.dateFormat = @"EEEE";
        NSString *day = [[dateFormatter stringFromDate:self.date] capitalizedString];
        
        if (dayDiff == 0) {
            return [NSString stringWithFormat:@"%@ (%@)", day, BREVIAR_STR(@"today")];
        } else {
            return day;
        }
	}
	else {
		NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
		[dateFormatter setDateStyle:NSDateFormatterLongStyle];
		return [dateFormatter stringFromDate:self.date];
	}
}

#pragma mark -
#pragma mark Date selection

- (void)showDatePicker:(id)sender
{
	id<GAITracker> tracker = [[GAI sharedInstance] defaultTracker];
	[tracker send:[[GAIDictionaryBuilder createEventWithCategory:@"MainScreen"
														  action:@"PickDate"
														   label:nil
														   value:nil] build]];
	
	[self performSegueWithIdentifier:@"ShowDatePicker" sender:self];
}

- (void)jumpDate:(int)dayDiff
{
	NSDateComponents *components = [[NSDateComponents alloc] init];
	[components setDay:dayDiff];
	
	self.date = [[NSCalendar currentCalendar] dateByAddingComponents:components toDate:self.date options:0];
    [self loadSelectedDateAndReloadTable:NO resetCelebrationIndex:YES forcePrayerRegeneration:NO];
	
    // Animate only the celebrations section
	NSIndexSet *indexSet = [NSIndexSet indexSetWithIndexesInRange:NSMakeRange(0, 1)];
	[self.tableView reloadSections:indexSet withRowAnimation:(dayDiff > 0 ? UITableViewRowAnimationLeft : UITableViewRowAnimationRight)];
}

- (IBAction)prevDayPressed:(id)sender
{
	id<GAITracker> tracker = [[GAI sharedInstance] defaultTracker];
	[tracker send:[[GAIDictionaryBuilder createEventWithCategory:@"MainScreen"
														  action:@"JumpDate"
														   label:@"Yesterday"
														   value:nil] build]];
	
	[self jumpDate:-1];
}

- (IBAction)nextDayPressed:(id)sender
{
	id<GAITracker> tracker = [[GAI sharedInstance] defaultTracker];
	[tracker send:[[GAIDictionaryBuilder createEventWithCategory:@"MainScreen"
														  action:@"JumpDate"
														   label:@"Tomorrow"
														   value:nil] build]];
	
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
    else if ([segueId isEqualToString:@"ShowPrayer"] || (segueId.length > 11 && [[segueId substringToIndex:11] isEqualToString:@"ShowPrayer."])) {
		BRPrayerViewController *destController = segue.destinationViewController;
		BRPrayerType prayerType;
		
		if ([segueId isEqualToString:@"ShowPrayer"]) {
			NSIndexPath *indexPath = [self.tableView indexPathForSelectedRow];
			prayerType = (BRPrayerType)indexPath.row;
		} else { // ShowPrayer.*
			NSString *prayerQueryId = [segueId substringFromIndex:11];
			prayerType = [BRPrayer prayerTypeFromQueryId:prayerQueryId];
		}
		
		BRCelebration *celebration = [self.day.celebrations objectAtIndex:self.celebrationIndex];
		destController.prayer = celebration.prayers[prayerType];
		
		destController.webView = self.sharedWebView;
    }
	else if ([segueId isEqualToString:@"ShowAbout"]) {
		BRAboutViewController *destController = segue.destinationViewController;
		destController.webView = self.sharedWebView;
	}
}

- (void)datePicker:(BRDatePickerViewController *)datePicker pickedDate:(NSDate *)date
{
	self.date = date;

	if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
		[self dismissViewControllerAnimated:YES completion:nil];
	}
	else if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
		[self.datePickerPopover dismissPopoverAnimated:YES];
		self.datePickerPopover = nil;
	}
    
    [self loadSelectedDateAndReloadTable:YES resetCelebrationIndex:YES forcePrayerRegeneration:NO];
}

@end

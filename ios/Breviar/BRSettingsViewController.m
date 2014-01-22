//
//  BRSettingsViewController.m
//  Breviar
//
//  Created by Gyimesi Akos on 9/8/12.
//
//

#import "BRSettingsViewController.h"
#import "BRFontHelper.h"
#import "BRFontSettingsCell.h"
#import "BRBoolSettingsCell.h"
#import "BRStringOptionPickerViewController.h"
#import "BRSettings.h"
#import "BRUtil.h"
#import "BRPrayerListViewController.h"

#define CELL_NORMAL_HEIGHT			44
#define CELL_LABEL_WIDTH			192
#define CELL_LABEL_MARGIN			24

#define SECT_APPEARANCE				0
#define SECT_PRAYER_PARTS			1
#define SECT_PRAYER_TEXT			2
#define SECT_OTHER					3

@interface BRSettingsViewController ()

@property(strong) NSString *currentOptionId;
@property(strong) NSDictionary *visibleOptionIndexPaths;
@property(strong) NSArray *visibleOptionsPerSection;

@end

@implementation BRSettingsViewController

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}

- (void)viewWillAppear:(BOOL)animated
{
	[super viewWillAppear:animated];
	[self calculateVisibleOptions];
	[self.tableView reloadData];
}

- (void)viewWillDisappear:(BOOL)animated {
    // Going back to BRPrayerListViewController? Reload the whole table because
    if ([self.navigationController.topViewController isKindOfClass:[BRPrayerListViewController class]]) {
        BRPrayerListViewController *parent = (BRPrayerListViewController *)self.navigationController.topViewController;
        [parent loadSelectedDateAndReloadTable:YES resetCelebrationIndex:NO forcePrayerRegeneration:YES];
    }
}

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
	[super willRotateToInterfaceOrientation:toInterfaceOrientation duration:duration];
	[self.tableView reloadData];
}

#pragma mark -
#pragma mark Settings table

- (NSDictionary *)sectionForIndexPath:(NSIndexPath *)indexPath {
	NSDictionary *section = [[BRSettings instance].sections objectAtIndex:indexPath.section];
	return section;
}

- (NSDictionary *)optionForIndexPath:(NSIndexPath *)indexPath {
	NSArray *section = [self.visibleOptionsPerSection objectAtIndex:indexPath.section];
	NSDictionary *option = [section objectAtIndex:indexPath.row];
	return option;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return [BRSettings instance].sections.count;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
	NSDictionary *sectionObj = [[BRSettings instance].sections objectAtIndex:section];
	NSString *sectionId = [sectionObj objectForKey:@"id"];
	return BREVIAR_STR(sectionId);
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	NSArray *sectionItems = [self.visibleOptionsPerSection objectAtIndex:section];
	return sectionItems.count;
}

- (NSString *)boolCellType
{
	return UIInterfaceOrientationIsPortrait(self.interfaceOrientation) ? @"BoolCellPortrait" : @"BoolCellLandscape";
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
	NSDictionary *option = [self optionForIndexPath:indexPath];
	NSString *optionType = [option objectForKey:@"type"];
	
	if ([optionType isEqualToString:@"bool"]) {
		// Boolean option for iPhone
		NSString *optId = [option objectForKey:@"id"];
		NSString *optTitle = BREVIAR_STR(optId);
		
		BRBoolSettingsCell *cell = [tableView dequeueReusableCellWithIdentifier:[self boolCellType]];
		cell.label.text = optTitle;
		[cell.contentView setNeedsLayout];
		[cell.contentView layoutIfNeeded];
		
		CGFloat height = [cell.contentView systemLayoutSizeFittingSize:UILayoutFittingCompressedSize].height;
		return height + 2;
	}
	else {
		return CELL_NORMAL_HEIGHT;
	}
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	BRSettings *settings = [BRSettings instance];
	NSDictionary *option = [self optionForIndexPath:indexPath];
	NSString *optionType = [option objectForKey:@"type"];
	NSString *optionId = [option objectForKey:@"id"];
	
	if ([optionType isEqualToString:@"font"]) {
		BRFontSettingsCell *cell = [tableView dequeueReusableCellWithIdentifier:@"FontCell"];

		// Update font cell
		UIFont *font = [settings fontForOption:optionId];
		NSString *fontName = [[BRFontHelper instance] fontNameForFamily:font.fontName];
		NSInteger fontSize = font.pointSize;
		
		cell.optionId = optionId;
		cell.fontLabel.font = font;
		cell.fontLabel.text = [NSString stringWithFormat:@"%@, %dpx", fontName, fontSize];
		
		return cell;
	}
	else if ([optionType isEqualToString:@"bool"]) {
		// Boolean option
		BRBoolSettingsCell *cell = [tableView dequeueReusableCellWithIdentifier:[self boolCellType]];
		cell.optionId = optionId;
		cell.label.text = BREVIAR_STR(optionId);
		cell.switcher.on = [settings boolForOption:optionId];
		cell.delegate = self;
		
		return cell;
	}
	else if ([optionType isEqualToString:@"stringOption"]) {
		// String option
		UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"StringOptionCell"];
		NSString *valueId = [NSString stringWithFormat:@"%@.%@", optionId, [settings stringForOption:optionId]];
		cell.textLabel.text = BREVIAR_STR(optionId);
		cell.detailTextLabel.text = BREVIAR_STR(valueId);
		
		return cell;
	}
	
	return nil;
}

#pragma mark -
#pragma mark Option visibility

- (void)calculateVisibleOptions
{
	NSInteger sectionId, rowId;
	BRSettings *settings = [BRSettings instance];
	NSMutableDictionary *visibleOptionIndexPaths = [[NSMutableDictionary alloc] init];
	NSMutableArray *visibleOptionsPerSection = [[NSMutableArray alloc] init];
	
	sectionId = 0;
	for (NSDictionary *section in [BRSettings instance].sections) {
		NSMutableArray *items = [[NSMutableArray alloc] init];
		
		rowId = 0;
		for (NSDictionary *item in [section objectForKey:@"items"]) {
			NSString *visibility = [item objectForKey:@"visibility"];
			BOOL visible;
			
            if ([visibility isEqualToString:@"iPhoneOnly"]) {
                visible = UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone;
            } else if (visibility) {
				NSPredicate *predicate = [NSPredicate predicateWithFormat:visibility];
				visible = [predicate evaluateWithObject:settings];
			} else {
				visible = YES;
			}

			if (visible) {
				[items addObject:item];
				NSIndexPath *indexPath = [NSIndexPath indexPathForItem:rowId inSection:sectionId];
				[visibleOptionIndexPaths setObject:indexPath forKey:[item objectForKey:@"id"]];
				rowId++;
			}
		}
		[visibleOptionsPerSection addObject:items];
		sectionId++;
	}
	
	self.visibleOptionIndexPaths = visibleOptionIndexPaths;
	self.visibleOptionsPerSection = visibleOptionsPerSection;
}

- (void)boolOptionChanged:(NSString *)optionId toValue:(BOOL)newValue
{
	// Get old list of visible options
	NSDictionary *oldVisibleOptionIndexPaths = self.visibleOptionIndexPaths;
	
	// Get new list of visible options
	[self calculateVisibleOptions];
	NSDictionary *newVisibleOptionIndexPaths = self.visibleOptionIndexPaths;
	
	// Calculate diff
	NSMutableArray *rowsToDelete = [[NSMutableArray alloc] init];
	NSMutableArray *rowsToAdd = [[NSMutableArray alloc] init];
	
	for (NSString *optionId in oldVisibleOptionIndexPaths) {
		if (![newVisibleOptionIndexPaths objectForKey:optionId]) {
			[rowsToDelete addObject:[oldVisibleOptionIndexPaths objectForKey:optionId]];
		}
	}

	for (NSString *optionId in newVisibleOptionIndexPaths) {
		if (![oldVisibleOptionIndexPaths objectForKey:optionId]) {
			[rowsToAdd addObject:[newVisibleOptionIndexPaths objectForKey:optionId]];
		}
	}
	
	// Apply diff to table
	if (rowsToAdd.count > 0 || rowsToDelete.count > 0) {
		[self.tableView beginUpdates];
		[self.tableView deleteRowsAtIndexPaths:rowsToDelete withRowAnimation:UITableViewRowAnimationFade];
		[self.tableView insertRowsAtIndexPaths:rowsToAdd withRowAnimation:UITableViewRowAnimationBottom];
		[self.tableView endUpdates];
	}
}

#pragma mark -
#pragma mark Transitions

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
	NSString *segueId = segue.identifier;
	NSIndexPath *indexPath = [self.tableView indexPathForSelectedRow];
	NSDictionary *option = [self optionForIndexPath:indexPath];
	self.currentOptionId = [option objectForKey:@"id"];
	
	[self.tableView deselectRowAtIndexPath:indexPath animated:YES];
	
	if ([segueId isEqualToString:@"ShowFontPicker"]) {
		BRFontPickerViewController *fontPicker = segue.destinationViewController;
		fontPicker.fontFamily = [BRSettings instance].prayerFontFamily;
		fontPicker.fontSize = [BRSettings instance].prayerFontSize;
		fontPicker.delegate = self;
	}
	else if ([segueId isEqualToString:@"ShowStringOptions"]) {
		BRStringOptionPickerViewController *picker = segue.destinationViewController;
		picker.title = BREVIAR_STR(self.currentOptionId);
		picker.optionId = [option objectForKey:@"id"];
		picker.options = [option objectForKey:@"options"];
		picker.currentValue = [[BRSettings instance] stringForOption:self.currentOptionId];
		picker.delegate = self;
	}
}

- (void)fontPicker:(BRFontPickerViewController *)fontPicker didPickFont:(UIFont *)font
{
	[[BRSettings instance] setFont:font forOption:self.currentOptionId];
	[self.tableView reloadData];
}

- (void)stringOptionPicker:(BRStringOptionPickerViewController *)picker didPickOption:(NSString *)value
{
	[[BRSettings instance] setString:value forOption:self.currentOptionId];
	[self.tableView reloadData];
}

@end

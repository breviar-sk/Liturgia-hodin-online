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

#define CELL_NORMAL_HEIGHT			44
#define CELL_LABEL_WIDTH			192
#define CELL_LABEL_MARGIN			24

#define SECT_APPEARANCE				0
#define SECT_PRAYER_PARTS			1
#define SECT_PRAYER_TEXT			2
#define SECT_OTHER					3

@interface BRSettingsViewController ()

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
	[self.tableView reloadData];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark -
#pragma mark Settings table

- (NSDictionary *)sectionForIndexPath:(NSIndexPath *)indexPath {
	NSDictionary *section = [[BRSettings instance].sections objectAtIndex:indexPath.section];
	return section;
}

- (NSArray *)visibleOptionsForSection:(NSDictionary *)section {
	NSArray *allOptions = [section objectForKey:@"items"];
	return [allOptions filteredArrayUsingPredicate:[NSPredicate predicateWithBlock:^BOOL(NSDictionary *item, NSDictionary *bindings) {
		NSNumber *hidden = [item objectForKey:@"hidden"];
		return [hidden integerValue] != 1;
	}]];
}

- (NSDictionary *)optionForIndexPath:(NSIndexPath *)indexPath {
	NSDictionary *section = [[BRSettings instance].sections objectAtIndex:indexPath.section];
	NSArray *options = [self visibleOptionsForSection:section];
	NSDictionary *option = [options objectAtIndex:indexPath.row];
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
	NSDictionary *sectionObj = [[BRSettings instance].sections objectAtIndex:section];
	NSArray *sectionItems = [self visibleOptionsForSection:sectionObj];
	return sectionItems.count;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
	NSDictionary *section = [self sectionForIndexPath:indexPath];
	NSDictionary *option = [self optionForIndexPath:indexPath];
	NSString *optionType = [option objectForKey:@"type"];
	
	if ([optionType isEqualToString:@"bool"] && UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
		// Boolean option for iPhone
		NSArray *opts = [self visibleOptionsForSection:section];
		NSString *optId = [[opts objectAtIndex:indexPath.row] objectForKey:@"id"];
		NSString *optTitle = BREVIAR_STR(optId);
		
		UIFont *font = [UIFont systemFontOfSize:[UIFont labelFontSize]];
		CGSize size = [optTitle sizeWithFont:font constrainedToSize:CGSizeMake(CELL_LABEL_WIDTH, CGFLOAT_MAX)];
		return size.height + CELL_LABEL_MARGIN;
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
		BRBoolSettingsCell *cell = [tableView dequeueReusableCellWithIdentifier:@"BoolCell"];
		cell.optionId = optionId;
		cell.label.text = BREVIAR_STR(optionId);
		cell.switcher.on = [settings boolForOption:optionId];
		
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

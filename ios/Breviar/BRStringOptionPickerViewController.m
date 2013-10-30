//
//  BRStringOptionPickerViewController.m
//  Breviar
//
//  Created by Gyimesi Akos on 4/14/13.
//
//

#import "BRStringOptionPickerViewController.h"
#import "BRUtil.h"

@interface BRStringOptionPickerViewController ()

@end

@implementation BRStringOptionPickerViewController

- (void)viewWillAppear:(BOOL)animated
{
	[super viewWillAppear:animated];
	self.navigationBar.topItem.title = self.title;
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	return self.options.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"SelectableStringCell" forIndexPath:indexPath];
	NSString *value = [self.options objectAtIndex:indexPath.row];
	NSString *valueId = [NSString stringWithFormat:@"%@.%@", self.optionId, value];
	cell.textLabel.text = BREVIAR_STR(valueId);
	cell.accessoryType = ([value isEqualToString:self.currentValue] ? UITableViewCellAccessoryCheckmark : UITableViewCellAccessoryNone);
    
    return cell;
}

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
	// Remove checkmark from old cell
	NSInteger oldIndex = [self.options indexOfObject:self.currentValue];
	NSIndexPath *oldIndexPath = [NSIndexPath indexPathForRow:oldIndex inSection:0];
	UITableViewCell *oldCell = [tableView cellForRowAtIndexPath:oldIndexPath];
	oldCell.accessoryType = UITableViewCellAccessoryNone;
	
	// Add checkmark to new cell
	UITableViewCell *newCell = [tableView cellForRowAtIndexPath:indexPath];
	newCell.accessoryType = UITableViewCellAccessoryCheckmark;
	
	// Store new value and call delegate
	self.currentValue = [self.options objectAtIndex:indexPath.row];
	[self.delegate stringOptionPicker:self didPickOption:self.currentValue];

	[tableView deselectRowAtIndexPath:indexPath animated:YES];
}

- (IBAction)doneButtonPressed:(id)sender
{
	[self dismissViewControllerAnimated:YES completion:nil];
}

@end

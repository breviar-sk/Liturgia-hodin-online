//
//  BRFontPickerViewController.m
//  Breviar
//
//  Created by Gyimesi Akos on 9/8/12.
//
//

#import "BRFontPickerViewController.h"
#import "BRFontHelper.h"

typedef enum {
	BRFontFamilyComponent = 0,
	BRFontSizeComponent = 1
} BRFontPickerComponent;

static CGFloat componentSizes[] = {
	200,
	80
};

@interface BRFontPickerViewController ()

@end

@implementation BRFontPickerViewController
@synthesize webView;

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

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void)viewWillAppear:(BOOL)animated
{
	[super viewWillAppear:animated];
	
	// Select current font in picker
	NSUInteger familyIndex = [[BRFontHelper instance].availableFonts indexOfObject:self.fontFamily];
	if (familyIndex != NSNotFound) {
		[self.pickerView selectRow:familyIndex inComponent:BRFontFamilyComponent animated:NO];
	}
	NSUInteger sizeIndex = [[BRFontHelper instance].availableSizes indexOfObject:[NSNumber numberWithInt:self.fontSize]];
	if (sizeIndex != NSNotFound) {
		[self.pickerView selectRow:sizeIndex inComponent:BRFontSizeComponent animated:NO];
	}
	
	[self updatePreview];
}

#pragma mark -
#pragma mark UIPickerViewDataSource

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
	return 2;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
	if (component == BRFontFamilyComponent) {
		return [BRFontHelper instance].availableFonts.count;
	}
	else if (component == BRFontSizeComponent) {
		return [BRFontHelper instance].availableSizes.count;
	}
	return 0;
}

#pragma mark -
#pragma mark UIPickerViewDelegate

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component {
	BRFontHelper *fontHelper = [BRFontHelper instance];
	
	if (component == BRFontFamilyComponent) {
		NSString *fontFamily = [fontHelper.availableFonts objectAtIndex:row];
		NSString *fontName = [fontHelper fontNameForFamily:fontFamily];
		return fontName;
	}
	else if (component == BRFontSizeComponent) {
		return [NSString stringWithFormat:@"%@ px", [fontHelper.availableSizes objectAtIndex:row]];
	}
	return nil;
}

- (CGFloat)pickerView:(UIPickerView *)pickerView widthForComponent:(NSInteger)component {
	return componentSizes[component];
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component {
	BRFontHelper *fontHelper = [BRFontHelper instance];
	
	if (component == BRFontFamilyComponent) {
		self.fontFamily = [fontHelper.availableFonts objectAtIndex:row];
	}
	else if (component == BRFontSizeComponent) {
		self.fontSize = [[fontHelper.availableSizes objectAtIndex:row] intValue];
	}
	
	UIFont *font = [UIFont fontWithName:self.fontFamily size:self.fontSize];
	[self.delegate fontPicker:self didPickFont:font];
	[self updatePreview];
}

#pragma mark -
#pragma mark Preview

- (void)updatePreview {
	NSString *html = [NSString stringWithFormat:
					  @"<!DOCTYPE html>\n"
					  "<html><body>"
					  "<body style='font: %dpx %@'>"
					  "<p>Te Deum laudamus:<br>te Dominum confitemur.<br>Te aeternum Patrem<br>omnis terra veneratur.<br>Tibi omnes Angeli; tibi caeli et universae Potestates;<br>Tibi Cherubim et Seraphim<br>incessabili voce proclamant:<br>Sanctus, Sanctus, Sanctus, Dominus Deus Sabaoth.</p>"
					  "</body></html>",
					  self.fontSize, self.fontFamily];
	[self.webView loadHTMLString:html baseURL:[NSURL URLWithString:@"http://breviar.sk"]];
}

#pragma mark -
#pragma mark Actions

- (IBAction)donePressed:(id)sender
{
	[self dismissViewControllerAnimated:YES completion:nil];
}

@end

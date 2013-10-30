//
//  BRCelebration.h
//  Breviar
//
//  Created by Gyimesi Akos on 10/17/12.
//
//

#import <Foundation/Foundation.h>

// See LIT_FARBA_... constants in liturgia.h
typedef enum {
	BRColorUnknown       = 0,
	BRColorRed           = 1,
	BRColorWhite         = 2,
	BRColorGreen         = 3,
	BRColorViolet        = 4,
	BRColorRose          = 5,
	BRColorBlack         = 6,
	BRColorVioletOrBlack = 7,
	BRColorVioletOrWhite = 8,
	BRColorRoseOrViolet  = 9
} BRLiturgicalColor;

@interface BRCelebration : NSObject

@property NSInteger celebrationId;
@property(strong) NSString *title;
@property(strong) NSString *subtitle;
@property(strong) NSArray *prayers;
@property(assign) BRLiturgicalColor liturgicalColor;

@end

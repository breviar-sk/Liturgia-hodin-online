//
//  BRUtil.h
//  Breviar
//
//  Created by Gyimesi Akos on 4/14/13.
//
//

#ifndef Breviar_BRUtil_h
#define Breviar_BRUtil_h

#define DEBUG_SETTINGS 0

#if DEBUG_SETTINGS
#define BREVIAR_STR(s) ([NSString stringWithFormat:@"%@ [%@]", [[NSBundle mainBundle] localizedStringForKey:(s) value:@"" table:@"Breviar"], s])
#else
#define BREVIAR_STR(s) ([[NSBundle mainBundle] localizedStringForKey:(s) value:@"" table:@"Breviar"])
#endif

#endif

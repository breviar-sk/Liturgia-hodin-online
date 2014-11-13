/***************************************************************/
/*                                                             */
/* mystring.h                                                  */
/* (c)1999-2014 | Juraj Vidéky | videky@breviar.sk             */
/*                                                             */
/* description |                                               */
/* document history                                            */
/*   31/03/2000A.D. | created                                  */
/*   06/09/2001A.D. | tento popis                              */
/*   2003-08-13a.D. | pridane definicie STR_EMPTY a STR_UNDEF  */
/*   2009-08-05a.D. | pridaná funkcia substring()              */
/*   2011-04-13a.D. | sem presunuté reťazcové funkcie equals() */
/*                                                             */
/***************************************************************/

#include "vstudio.h"

#ifndef __MYSTRING_H_
#define __MYSTRING_H_

#include <string.h>

#define STR_EMPTY ""
#define STR_UNDEF "(undef)"

// funkcia mystrcpy()
// 1. zisti velkost dest -- sizeof(dest)
// 2. kopiruje nanajvys count - 1 znakov z src do dest (pomocou strncpy)
// 3. v kazdom pripade prida na koniec v dest '\0' (terminating null)
char *mystrcpy(char *dest, char *src, short int count);
char *mystrcpy(char *dest, const char *src, short int count);
int substring(char *str1, char *str2);

// string comparator -- pre vsetky kombinacie dvojic [const] char, [const] char
short int equals(char *, char *);
short int equals(const char *, const char *);
short int equals(const char *, char *);
short int equals(char *, const char *);
// string comparator without case sensitivity  -- pre vsetky kombinacie dvojic [const] char, [const] char
short int equalsi(char *, char *);
short int equalsi(const char *, const char *);
short int equalsi(const char *, char *);
short int equalsi(char *, const char *);

// funkcia mystr_replace() nahradí všetky výskyty podreťazca substr v reťazci string reťazcom replacement
char *mystr_replace ( const char *string, const char *substr, const char *replacement );

// funkcia mystr_first_lower() aplikuje tolower() na prvý znak reťazca
char *mystr_first_lower ( const char *string );
// funkcia mystr_first_upper() aplikuje toupper() na prvý znak reťazca
char *mystr_first_upper ( const char *string );

#endif // __MYSTRING_H_

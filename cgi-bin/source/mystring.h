/***************************************************************/
/*                                                             */
/* mystring.h                                                  */
/* (c)1999-2016 | Juraj Vidéky | videky@breviar.sk             */
/*                                                             */
/* description | proprietary string manipulation methods       */
/*                                                             */
/***************************************************************/

#include "vstudio.h"

#ifndef __MYSTRING_H_
#define __MYSTRING_H_

#include "common.h"
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
// string comparator without case sensitivity -- pre vsetky kombinacie dvojic [const] char, [const] char
short int equalsi(char *, char *);
short int equalsi(const char *, const char *);
short int equalsi(const char *, char *);
short int equalsi(char *, const char *);

char *mystr_replace(const char *string, const char *substr, const char *replacement);

char *mystr_first_lower(const char *string);
char *mystr_first_upper(const char *string);

// detecting whether base is starts with str
short int startsWith(char* base, char* str);
// detecting whether base is ends with str
short int endsWith(char* base, char* str);

#endif // __MYSTRING_H_

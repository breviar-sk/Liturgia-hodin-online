/***************************************************************/
/*                                                             */
/* mystring.h                                                  */
/* (c)1999-2026 | Juraj Vidéky | videky@breviar.sk             */
/*                                                             */
/* description | proprietary string manipulation methods       */
/*                                                             */
/***************************************************************/

#ifndef __MYSTRING_H_
#define __MYSTRING_H_

#include <string>
#include <stdio.h>
#include <stdarg.h>

#include "common.h"
#include <string.h>

#define STR_EMPTY ""
#define STR_UNDEF "(undef)"

// Bounded formatting for fixed-size buffers. Array references prevent accidentally
// using sizeof(pointer) as the capacity. Like snprintf, return the required length;
// overlong output is truncated and NUL-terminated. Source and destination must not overlap.
template <size_t N>
#if defined(__GNUC__) || defined(__clang__)
__attribute__((format(printf, 2, 3)))
#endif
int mysnprintf(char (&dest)[N], const char* format, ...) {
	va_list args;
	va_start(args, format);
	int result = vsnprintf(dest, N, format, args);
	va_end(args);
	dest[N - 1] = '\0';
	return result;
}

// funkcia mystrcpy()
// 1. zisti velkost dest -- sizeof(dest)
// 2. kopiruje nanajvys count - 1 znakov z src do dest (pomocou strncpy)
// 3. v kazdom pripade prida na koniec v dest '\0' (terminating null)
char *mystrcpy(char *dest, char *src, short int count);
char *mystrcpy(char *dest, const char* src, short int count);
int substring(char *str1, char *str2);

extern char* _global_pom_str; // pomocny string pre velke/male pismena (konverzie)
extern short int _global_override_thin_nbsp;

// string comparator -- pre vsetky kombinacie dvojic [const] char, [const] char
short int equals(char *, char *);
short int equals(const char* , const char* );
short int equals(const char* , char *);
short int equals(char *, const char* );
// string comparator without case sensitivity -- pre vsetky kombinacie dvojic [const] char, [const] char
short int equalsi(char *, char *);
short int equalsi(const char* , const char* );
short int equalsi(const char* , char *);
short int equalsi(char *, const char* );

std::string mystr_replace(const char* string, const char* substr, const char* replacement);
std::string mystr_replace_char(const char* string, const char orig_char, const char replacement);
std::string mystr_remove_char(const char* string, const char char_to_remove);
std::string mystr_remove_letters_and_parentheses(const char* string);

char* mystr_UPPERCASE(const char* input);
char* mystr_remove_diacritics(const char* input);
char* convert_nonbreaking_spaces(const char* input);

std::string mystr_first_lower(const char* string);
std::string mystr_first_upper(const char* string);

void convertToRoman(int val, char *res);

// detecting whether base is starts with str
short int startsWith(char* base, char* str);
// detecting whether base is ends with str
short int endsWith(char* base, char* str);

// validate the HTML hexadecimal color code (without starting # character)
bool isValidHexaCode(char* str);

unsigned long long atoui64(const char* szUnsignedInt);

#endif // __MYSTRING_H_

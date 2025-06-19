/***************************************************************/
/*                                                             */
/* mystring.cpp                                                */
/* (c)1999-2025 | Juraj Vidéky | videky@breviar.sk             */
/*                                                             */
/* description | proprietary string manipulation methods       */
/*                                                             */
/***************************************************************/

#include "vstudio.h"

#ifndef __MYSTRING_CPP_
#define __MYSTRING_CPP_

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <wctype.h>
#include "utf8-utils.h"
#include "mystring.h"
#include "mysystem.h"
#include "mysysdef.h"

// funkcia mystrcpy()
// 1. zisti velkost dest -- sizeof(dest)
// 2. kopiruje nanajvys count - 1 znakov z src do dest (pomocou strncpy)
// 3. v kazdom pripade prida na koniec v dest '\0' (terminating null)
char *mystrcpy(char *dest, char *src, short int count) {
	// do nothing is src is NULL
	if (src == NULL) {
		return dest;
	}

	char *ret;
	/* sizeof(dest) nefunguje pre char *dest */
	ret = strncpy(dest, src, count - 1);
	dest[count - 1] = '\0';
	return ret;
}

char *mystrcpy(char *dest, const char* src, short int count) {
	// do nothing is src is NULL
	if (src == NULL) {
		return dest;
	}

	char *ret;
	/* sizeof(dest) nefunguje pre char *dest */
	ret = strncpy(dest, src, count - 1);
	dest[count - 1] = '\0';
	return ret;
}
// The strncpy function copies the initial count characters of strSource to strDest 
// and returns strDest. If count is less than or equal to the length of strSource, 
// a null character is not appended automatically to the copied string. 
// If count is greater than the length of strSource, the destination string is padded 
// with null characters up to length count. 
// The behavior of strncpy is undefined if the source and destination strings overlap.
// This function returns strDest. No return value is reserved to indicate an error.

int substring(char *str1, char *str2) {
	// vráti true, ak str2 je substring v reťazci str1
	return (strstr(str1, str2) != NULL);
}

// string comparator -- pre vsetky kombinacie dvojic [const] char, [const] char
short int equals(char *s1, char *s2) {
	if (strcmp(s1, s2) == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

short int equals(const char* s1, char *s2) {
	if (strcmp(s1, s2) == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

short int equals(const char* s1, const char* s2) {
	if (strcmp(s1, s2) == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

short int equals(char *s1, const char* s2) {
	if (strcmp(s1, s2) == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

// string comparator without case sensitivity -- pre vsetky kombinacie dvojic [const] char, [const] char
short int equalsi(char *is1, char *is2) {
#if defined(DEFINED_strcmpi)
	if (strcmpi(is1, is2) == 0) {
		return 1;
	}
	else {
		return 0;
	}
#else
	long i, length;
	char s1[MAX_STR], s2[MAX_STR];
	mystrcpy(s1, is1, MAX_STR);
	mystrcpy(s2, is2, MAX_STR);
	length = strlen(s1);
	for (i = 0; i < length; i++) {
		s1[i] = (char)tolower(s1[i]);
	}
	length = strlen(s2);
	for (i = 0; i < length; i++) {
		s2[i] = (char)tolower(s2[i]);
	}
	return equals(s1, s2);
#endif
}

short int equalsi(const char* is1, char *is2) {
#if defined(DEFINED_strcmpi)
	if (strcmpi(is1, is2) == 0) {
		return 1;
	}
	else {
		return 0;
	}
#else
	long i, length;
	char s1[MAX_STR], s2[MAX_STR];
	mystrcpy(s1, is1, MAX_STR);
	mystrcpy(s2, is2, MAX_STR);
	length = strlen(s1);
	for (i = 0; i < length; i++) {
		s1[i] = (char)tolower(s1[i]);
	}
	length = strlen(s2);
	for (i = 0; i < length; i++) {
		s2[i] = (char)tolower(s2[i]);
	}
	return equals(s1, s2);
#endif
}

short int equalsi(const char* is1, const char* is2) {
#if defined(DEFINED_strcmpi)
	if (strcmpi(is1, is2) == 0) {
		return 1;
	}
	else {
		return 0;
	}
#else
	long i, length;
	char s1[MAX_STR], s2[MAX_STR];
	mystrcpy(s1, is1, MAX_STR);
	mystrcpy(s2, is2, MAX_STR);
	length = strlen(s1);
	for (i = 0; i < length; i++) {
		s1[i] = (char)tolower(s1[i]);
	}
	length = strlen(s2);
	for (i = 0; i < length; i++) {
		s2[i] = (char)tolower(s2[i]);
	}
	return equals(s1, s2);
#endif
}

short int equalsi(char *is1, const char* is2) {
#if defined(DEFINED_strcmpi)
	if (strcmpi(is1, is2) == 0) {
		return 1;
	}
	else {
		return 0;
	}
#else
	long i, length;
	char s1[MAX_STR], s2[MAX_STR];
	mystrcpy(s1, is1, MAX_STR);
	mystrcpy(s2, is2, MAX_STR);
	length = strlen(s1);
	for(i = 0; i < length; i++) {
		s1[i] = (char)tolower(s1[i]);
	}
	length = strlen(s2);
	for(i = 0; i < length; i++) {
		s2[i] = (char)tolower(s2[i]);
	}
	return equals(s1, s2);
#endif
}

// funkcia mystr_replace() nahradí všetky výskyty podreťazca substr v reťazci string reťazcom replacement
// http://coding.debuntu.org/c-implementing-str_replace-replace-all-occurrences-substring | 2013-01-11
std::string mystr_replace(const char* string, const char* substr, const char* replacement) {
	char *tok = NULL;
	char *newstr = NULL;
	char *oldstr = NULL;
	char *head = NULL;

	/* if either substr or replacement is NULL, duplicate string a let caller handle it */
	if (substr == NULL || replacement == NULL) return std::string(string);

	newstr = strdup(string);
	head = newstr;
	while ((tok = strstr(head, substr))) {
		oldstr = newstr;
		newstr = (char *)malloc(strlen(oldstr) - strlen(substr) + strlen(replacement) + 1);
		/* failed to alloc mem, free old string and return NULL */
		if (newstr == NULL) {
			free(oldstr);
			free(newstr);
			return "";
		}
		memcpy(newstr, oldstr, tok - oldstr);
		memcpy(newstr + (tok - oldstr), replacement, strlen(replacement));
		memcpy(newstr + (tok - oldstr) + strlen(replacement), tok + strlen(substr), strlen(oldstr) - strlen(substr) - (tok - oldstr));
		memset(newstr + strlen(oldstr) - strlen(substr) + strlen(replacement), 0, 1);
		/* move back head right after the last replacement */
		head = newstr + (tok - oldstr) + strlen(replacement);
		free(oldstr);
	}
	std::string val(newstr);
	free(newstr);
	return val;
}// mystr_replace()

std::string mystr_replace_char(const char* string, const char orig_char, const char replacement) {
	/* if either substr or replacement is NULL, duplicate string a let caller handle it */
	if (orig_char == 0 || replacement == 0) return strdup(string);

	char *newstr = strdup(string);

	int i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == orig_char)
		{
			newstr[i] = replacement;
		}
		i++;
	}
	std::string val(newstr);
	free(newstr);
	return val;
}// mystr_replace_char()

std::string mystr_remove_char(const char* string, const char char_to_remove) {
	/* if substr is NULL, duplicate string a let caller handle it */
	if (char_to_remove == 0) return std::string(string);

	char *newstr = NULL;
	newstr = strdup(string);

	int i = 0, j = 0;

	while (string[i] != '\0')
	{
		if (string[i] != char_to_remove)
		{
			newstr[j] = string[i];
			j++;
		}
		i++;
	}
	newstr[j] = '\0';

	std::string val(newstr);
	free(newstr);
	return val;
}// mystr_remove_char()

std::string mystr_remove_letters_and_parentheses(const char* string) {
	/* if substr is NULL, duplicate string a let caller handle it */

	char *newstr = NULL;
	newstr = strdup(string);

	short int i = 0, j = 0;
	short int skip = NIE;

	while (string[i] != '\0')
	{
		// remove everything in parentheses [CZ: alternative numbering of Psalms]
		if (string[i] == '(') {
			skip = ANO;
		}
		else if (string[i] == ')') {
			skip = NIE;
		}
		else if (skip != ANO) {
			// test character
			if ((string[i] < 'a' && string[i] > 'Z') || (string[i] < 'A') || (string[i] > 'z'))
			{
				newstr[j] = string[i];
				j++;
			}
		}
		i++;
	}
	newstr[j] = '\0';

	std::string val(newstr);
	free(newstr);
	return val;
}// mystr_remove_letters()

//---------------------------------------------------------------------
// converts UTF-8 string to UPPERCASE
// nesmie pritom v HTML stringoch upravovať kódové mená, napr. &mdash; na veľké písmená
char* mystr_UPPERCASE(const char* input) {
	short int ok = TRUE;
	const char* in = input;
	char* out = _global_pom_str;
	while (out - _global_pom_str < MAX_STR - 5 && *in) {
		int c = DecodeWchar(&in);
		if ((c == '&') && (ok == TRUE)) {
			ok = FALSE;
		}
		if ((c == ';') && (ok == FALSE)) {
			ok = TRUE;
		}
		// ToDo: ešte by bolo potrebné ošetriť aj to, že za & nenasleduje regulérny znak pre špeciálny HTML kód, t. j. niečo iné ako upper+lowercase ascii abeceda + # a číslice
		if (ok == TRUE) {
			c = WcharToUppercase(c);
		}// ok == TRUE
		EncodeWchar(c, &out);
	}
	*out = 0;
	return (_global_pom_str);
}// mystr_UPPERCASE()

 //---------------------------------------------------------------------
 // odstráni diakritiku
 // nesmie pritom v HTML stringoch upravovať kódové mená, napr. &mdash;
 // zmení aj dlhé pomlčky na obyčajný spojovník (znak mínus)
char* mystr_remove_diacritics(const char* input) {
	short int ok = TRUE;
	const char* in = input;
	char* out = _global_pom_str;
	while (out - _global_pom_str < MAX_STR - 5 && *in) {
		int c = DecodeWchar(&in);
		if ((c == '&') && (ok == TRUE)) {
			ok = FALSE;
		}
		if ((c == ';') && (ok == FALSE)) {
			ok = TRUE;
		}
		// ToDo: ešte by bolo potrebné ošetriť aj to, že za & nenasleduje regulérny znak pre špeciálny HTML kód, t. j. niečo iné ako upper+lowercase ascii abeceda + # a číslice
		if (ok == TRUE) {
			c = RemoveDiacriticsFromWchar(c);
		}// ok == TRUE
		EncodeWchar(c, &out);
	}
	*out = 0;
	return (_global_pom_str);
}// mystr_remove_diacritics()

//---------------------------------------------------------------------
// konvertuje underscore na nezlomiteľné medzery
// (char sa musí najprv konvertovať na char * a až potom appendovať strcat)
char* convert_nonbreaking_spaces(const char* input) {
	// Log("convert_nonbreaking_spaces() -- začiatok...\n");
	const char* in = input;
	char* out = _global_pom_str;
	while (out - _global_pom_str < MAX_STR - 7 && *in) {
		int c = DecodeWchar(&in);
		if ((c == CHAR_NONBREAKING_THIN_SPACE) || ((_global_override_thin_nbsp == ANO) && (c == CHAR_NONBREAKING_SPACE))) {
			strcpy(out, HTML_NONBREAKING_THIN_SPACE);
			out += strlen(HTML_NONBREAKING_THIN_SPACE);
		}// c == CHAR_NONBREAKING_THIN_SPACE or special override of CHAR_NONBREAKING_SPACE
		else if (c == CHAR_NONBREAKING_SPACE) {
			strcpy(out, HTML_NONBREAKING_SPACE);
			out += strlen(HTML_NONBREAKING_SPACE);
		}// c == CHAR_NONBREAKING_SPACE
		else {
			EncodeWchar(c, &out);
		}
	}
	*out = 0;
	// Log("convert_nonbreaking_spaces() -- koniec, returning `%s'.\n", _global_pom_str);
	return (_global_pom_str);
}// convert_nonbreaking_spaces()

std::string mystr_first_lower(const char* string) {
	char *newstr = NULL;
	char c;
	newstr = strdup(string);
	c = newstr[0];
	if (isupper(c)) {
		c = tolower(c);
		newstr[0] = c;
	}
	std::string val(newstr);
	free(newstr);
	return val;
}// mystr_first_lower()

std::string mystr_first_upper(const char* string) {
	char *newstr = NULL;
	char c;
	newstr = strdup(string);
	c = newstr[0];
	if (islower(c)) {
		c = toupper(c);
		newstr[0] = c;
	}
	std::string val(newstr);
	free(newstr);
	return val;
}// mystr_first_upper()

// convert integer value to Roman numeral string; caller is responsible for buffer size
// http://stackoverflow.com/questions/4986521/how-to-convert-integer-value-to-roman-numeral-string | 2016-08-16
void convertToRoman(int val, char *res) {
	const char* huns[] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
	const char* tens[] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
	const char* ones[] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
	int         size[] = { 0,   1,    2,     3,    2,   1,    2,     3,      4,    2 };

	//  Add 'M' until we drop below 1000.
	while (val >= 1000) {
		*res++ = 'M';
		val -= 1000;
	}

	// Add each of the correct elements, adjusting as we go.
	strcpy(res, huns[val / 100]); res += size[val / 100]; val = val % 100;
	strcpy(res, tens[val / 10]);  res += size[val / 10];  val = val % 10;
	strcpy(res, ones[val]);     res += size[val];

	// Finish string off.

	*res = '\0';
}// convertToRoman()

// Custom function for detecting whether base is starts with str
short int startsWith(char* base, char* str) {
	return (0 == (strstr(base, str) - base));
}

// Custom function for detecting whether base is ends with str
short int endsWith(char* base, char* str) {
	long blen = strlen(base);
	long slen = strlen(str);
	if (slen <= blen)
	{
		return (0 == strcmp(base + blen - slen, str));
	}
	return 0;
}

// function to validate the HTML hexadecimal color code (without starting # character)
bool isValidHexaCode(char* str)
{
	if (!(strlen(str) == 3 || strlen(str) == 6)) {
		return false;
	}
	short int i = 0;
	while (str[i] != '\0') {
		if (!((str[i] >= '0' && str[i] <= 9)
			|| (str[i] >= 'a' && str[i] <= 'f')
			|| (str[i] >= 'A' || str[i] <= 'F')))
		{
			return false;
		}
		i++;
	}
	return true;
}

unsigned long long atoui64(const char* szUnsignedInt) {
#ifdef OS_linux
	return strtoull(szUnsignedInt, NULL, 10);
#else
	return _strtoui64(szUnsignedInt, NULL, 10);
#endif
}

#endif // __MYSTRING_CPP_

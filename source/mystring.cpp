/***************************************************************/
/*                                                             */
/* mystring.cpp                                                */
/* (c)1999-2026 | Juraj Vidéky | videky@breviar.sk             */
/*                                                             */
/* description | proprietary string manipulation methods       */
/*                                                             */
/***************************************************************/

#ifndef __MYSTRING_CPP_
#define __MYSTRING_CPP_

#ifdef _MSC_VER
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
// avoid Visual Studio warnings: 
// warning C4996: 'strncpy': This function or variable may be unsafe. Consider using strncpy_s instead.
// warning C4996: 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead.
#endif

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include "utf8-utils.h"
#include "mystring.h"

#ifdef _WIN32
	// Windows už má _strdup, netreba robiť nič
	// Windows už _strtoui64 pozná
#else
	// Na Linuxe/macOS premenujeme _strdup na štandardný strdup
	#define _strdup strdup
	// Na Linuxe premapujeme Windows názov na štandardný strtoull
	#define _strtoui64 strtoull
#endif

// funkcia mystrcpy()
// 1. zisti velkost dest -- sizeof(dest)
// 2. kopiruje nanajvys count - 1 znakov z src do dest (pomocou strncpy)
// 3. v kazdom pripade prida na koniec v dest '\0' (terminating null)
char *mystrcpy(char *dest, char *src, short int count) {
	return mystrcpy(dest, static_cast<const char*>(src), count);
}

char *mystrcpy(char *dest, const char* src, short int count) {
	// Nothing to copy without input or writable capacity.
	if (dest == NULL || src == NULL || count <= 0) {
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

	newstr = _strdup(string);
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
	if (orig_char == 0 || replacement == 0) return _strdup(string);

	char *newstr = _strdup(string);

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
	newstr = _strdup(string);

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
	newstr = _strdup(string);

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

// Convert only the first UTF-8 code point using the same locale-independent
// tables as the rest of the renderer. This also avoids wchar_t width differences.
static std::string first_character_case(const char* string, bool uppercase) {
	if (!string || string[0] == '\0') return std::string();

	const unsigned char lead = static_cast<unsigned char>(string[0]);
	const int length = lead < 0x80 ? 1 : (lead >= 0xC2 && lead <= 0xDF) ? 2 :
		(lead >= 0xE0 && lead <= 0xEF) ? 3 : (lead >= 0xF0 && lead <= 0xF4) ? 4 : 0;
	// Preserve malformed input rather than throwing or reading past its terminator.
	if (length == 0) return string;
	for (int i = 1; i < length; ++i) {
		if ((static_cast<unsigned char>(string[i]) & 0xC0) != 0x80) return string;
	}
	const char* rest = string;
	int codepoint = DecodeWchar(&rest);
	if ((length == 3 && codepoint < 0x800) || (length == 4 && codepoint < 0x10000) ||
		(codepoint >= 0xD800 && codepoint <= 0xDFFF) || codepoint > 0x10FFFF) {
		return string;
	}
	codepoint = uppercase ? WcharToUppercase(codepoint) : WcharToLowercase(codepoint);
	char first[4];
	char* end = first;
	EncodeWchar(codepoint, &end);
	return std::string(first, end) + rest;
}

std::string mystr_first_lower(const char* string) {
	return first_character_case(string, false);
}

std::string mystr_first_upper(const char* string) {
	return first_character_case(string, true);
}

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
	return strncmp(base, str, strlen(str)) == 0;
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
	if (str == NULL || !(strlen(str) == 3 || strlen(str) == 6)) {
		return false;
	}
	short int i = 0;
	while (str[i] != '\0') {
		if (!((str[i] >= '0' && str[i] <= '9')
			|| (str[i] >= 'a' && str[i] <= 'f')
			|| (str[i] >= 'A' && str[i] <= 'F')))
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

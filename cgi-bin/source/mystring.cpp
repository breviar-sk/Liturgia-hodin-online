/***************************************************************/
/*                                                             */
/* mystring.cpp                                                */
/* (c)1999-2016 | Juraj Vidéky | videky@breviar.sk             */
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
#include "mystring.h"
#include "mysystem.h"
#include "mysysdef.h"

// funkcia mystrcpy()
// 1. zisti velkost dest -- sizeof(dest)
// 2. kopiruje nanajvys count - 1 znakov z src do dest (pomocou strncpy)
// 3. v kazdom pripade prida na koniec v dest '\0' (terminating null)
char *mystrcpy(char *dest, char *src, short int count){
	char *ret;
	/* sizeof(dest) nefunguje pre char *dest */
	ret = strncpy(dest, src, count - 1);
	dest[count - 1] = '\0';
	return ret;
}

char *mystrcpy(char *dest, const char *src, short int count){
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

int substring(char *str1, char *str2){
	// vráti true, ak str2 je substring v reťazci str1
	return (strstr(str1, str2) != NULL);
}

// string comparator -- pre vsetky kombinacie dvojic [const] char, [const] char
short int equals(char *s1, char *s2){
	if (strcmp(s1, s2) == 0){
		return 1;
	}
	else{
		return 0;
	}
}

short int equals(const char *s1, char *s2){
	if (strcmp(s1, s2) == 0){
		return 1;
	}
	else{
		return 0;
	}
}

short int equals(const char *s1, const char *s2){
	if (strcmp(s1, s2) == 0){
		return 1;
	}
	else{
		return 0;
	}
}

short int equals(char *s1, const char *s2){
	if (strcmp(s1, s2) == 0){
		return 1;
	}
	else{
		return 0;
	}
}

// string comparator without case sensitivity -- pre vsetky kombinacie dvojic [const] char, [const] char
short int equalsi(char *is1, char *is2){
#if defined(DEFINED_strcmpi)
	if (strcmpi(is1, is2) == 0){
		return 1;
	}
	else{
		return 0;
	}
#else
	int i, length;
	char s1[MAX_STR], s2[MAX_STR];
	mystrcpy(s1, is1, MAX_STR);
	mystrcpy(s2, is2, MAX_STR);
	length = strlen(s1);
	for (i = 0; i < length; i++){
		s1[i] = (char)tolower(s1[i]);
	}
	length = strlen(s2);
	for (i = 0; i < length; i++){
		s2[i] = (char)tolower(s2[i]);
	}
	return equals(s1, s2);
#endif
}

short int equalsi(const char *is1, char *is2){
#if defined(DEFINED_strcmpi)
	if (strcmpi(is1, is2) == 0){
		return 1;
	}
	else{
		return 0;
	}
#else
	int i, length;
	char s1[MAX_STR], s2[MAX_STR];
	mystrcpy(s1, is1, MAX_STR);
	mystrcpy(s2, is2, MAX_STR);
	length = strlen(s1);
	for (i = 0; i < length; i++){
		s1[i] = (char)tolower(s1[i]);
	}
	length = strlen(s2);
	for (i = 0; i < length; i++){
		s2[i] = (char)tolower(s2[i]);
	}
	return equals(s1, s2);
#endif
}

short int equalsi(const char *is1, const char *is2){
#if defined(DEFINED_strcmpi)
	if (strcmpi(is1, is2) == 0){
		return 1;
	}
	else{
		return 0;
	}
#else
	int i, length;
	char s1[MAX_STR], s2[MAX_STR];
	mystrcpy(s1, is1, MAX_STR);
	mystrcpy(s2, is2, MAX_STR);
	length = strlen(s1);
	for (i = 0; i < length; i++){
		s1[i] = (char)tolower(s1[i]);
	}
	length = strlen(s2);
	for (i = 0; i < length; i++){
		s2[i] = (char)tolower(s2[i]);
	}
	return equals(s1, s2);
#endif
}

short int equalsi(char *is1, const char *is2){
#if defined(DEFINED_strcmpi)
	if (strcmpi(is1, is2) == 0){
		return 1;
	}
	else{
		return 0;
	}
#else
	int i, length;
	char s1[MAX_STR], s2[MAX_STR];
	mystrcpy(s1, is1, MAX_STR);
	mystrcpy(s2, is2, MAX_STR);
	length = strlen(s1);
	for(i = 0; i < length; i++){
		s1[i] = (char)tolower(s1[i]);
	}
	length = strlen(s2);
	for(i = 0; i < length; i++){
		s2[i] = (char)tolower(s2[i]);
	}
	return equals(s1, s2);
#endif
}

// funkcia mystr_replace() nahradí všetky výskyty podreťazca substr v reťazci string reťazcom replacement
// http://coding.debuntu.org/c-implementing-str_replace-replace-all-occurrences-substring | 2013-01-11
char *mystr_replace(const char *string, const char *substr, const char *replacement){
	char *tok = NULL;
	char *newstr = NULL;
	char *oldstr = NULL;
	char *head = NULL;
	/* if either substr or replacement is NULL, duplicate string a let caller handle it */
	if (substr == NULL || replacement == NULL) return strdup(string);
	newstr = strdup(string);
	head = newstr;
	while ((tok = strstr(head, substr))){
		oldstr = newstr;
		newstr = (char *)malloc(strlen(oldstr) - strlen(substr) + strlen(replacement) + 1);
		/* failed to alloc mem, free old string and return NULL */
		if (newstr == NULL){
			free(oldstr);
			return NULL;
		}
		memcpy(newstr, oldstr, tok - oldstr);
		memcpy(newstr + (tok - oldstr), replacement, strlen(replacement));
		memcpy(newstr + (tok - oldstr) + strlen(replacement), tok + strlen(substr), strlen(oldstr) - strlen(substr) - (tok - oldstr));
		memset(newstr + strlen(oldstr) - strlen(substr) + strlen(replacement), 0, 1);
		/* move back head right after the last replacement */
		head = newstr + (tok - oldstr) + strlen(replacement);
		free(oldstr);
	}
	return newstr;
}

char *mystr_first_lower(const char *string){
	char *newstr = NULL;
	char c;
	newstr = strdup(string);
	c = newstr[0];
	if (isupper(c)){
		c = tolower(c);
		newstr[0] = c;
	}
	return newstr;
}

char *mystr_first_upper(const char *string){
	char *newstr = NULL;
	char c;
	newstr = strdup(string);
	c = newstr[0];
	if (islower(c)){
		c = toupper(c);
		newstr[0] = c;
	}
	return newstr;
}

// Custom function for detecting whether base is starts with str
short int startsWith(char* base, char* str) {
	return (0 == (strstr(base, str) - base));
}

// Custom function for detecting whether base is ends with str
short int endsWith(char* base, char* str){
	int blen = strlen(base);
	int slen = strlen(str);
	if (slen <= blen)
	{
		return (0 == strcmp(base + blen - slen, str));
	}
	return 0;
}

#endif // __MYSTRING_CPP_

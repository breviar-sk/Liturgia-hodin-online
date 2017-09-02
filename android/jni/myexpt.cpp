/**************************************************************/
/*                                                            */
/* myexpt.cpp                                                 */
/* (c)1999-2017 | Juraj Vidéky | videky@breviar.sk            */
/*                                                            */
/* description | export routines for exporting HTML pages     */
/*               to file FILE_EXPORT or to stdout             */
/*                                                            */
/**************************************************************/

#include "vstudio.h"

#ifndef __MYEXPT_CPP_
#define __MYEXPT_CPP_

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "myexpt.h"
#include "mysysdef.h"

char FILE_EXPORT[MAX_STR] = DEFAULT_FILE_EXPORT;

short int isbothExports = NIE;

void bothExports(void){
	isbothExports = ANO;
}

short int exptused;
FILE *exportfile;

char *exptstr = NULL;
int exptstrlen = 0;

short int initExport(void){
#if defined(EXPORT_TO_FILE)
	if(FILE_EXPORT[strlen(FILE_EXPORT) - 1] == '+'){
		FILE_EXPORT[strlen(FILE_EXPORT) - 1] = '\0'; /* zrusime '+' na konci */
		exportfile = fopen(FILE_EXPORT, "a+t");
	}
	else{
		exportfile = fopen(FILE_EXPORT, "wt");
	}
	exptused = (exportfile == NULL)? FAILURE: SUCCESS;
	if(exportfile == NULL)
		exportfile = stdout;
#elif defined(EXPORT_TO_STDOUT)
	exportfile = stdout;
	exptused = SUCCESS;
#elif defined(EXPORT_TO_STRING)
	free(exptstr);
	exptstr = NULL;
	exptstrlen = 0;
	exptused = SUCCESS;
#else
#error Unsupported export model (use _EXPORT_TO_STDOUT or _EXPORT_TO_FILE)
#endif
	return exptused;
}

short int initExport(const char *expt_filename){
	if (exptused == SUCCESS){
		closeExport();
	}
	strcpy(FILE_EXPORT, expt_filename);
	return initExport();
}

short int closeExport(void){
	short int ret = 0;
#if defined(EXPORT_TO_FILE)
	ret = EOF;  /* error closing file */
	if(exptused == SUCCESS){
		ret = fclose(exportfile);
	}
#endif
	return ret;
}

void dumpFile(char *fname){
	short int c;
	FILE *input_file = fopen(fname, "rb");
	if (input_file != NULL){
		while ((c = fgetc(input_file)) != EOF)
			fputc(c, exportfile);
	}
}

// used from http://bytes.com/topic/c/answers/215169-va_copy-implementation | similar answer at http://stackoverflow.com/questions/558223/va-copy-porting-to-visual-c
#ifndef va_copy
// #ifdef _MSC_VER 
// WARNING - DANGER - ASSUMES TYPICAL STACK MACHINE
#define va_copy(dst, src) ((void)((dst) = (src)))
#endif

short int Export_to_string(const char *fmt, va_list argptr) {
	short int cnt;
	va_list argptr2;

	va_copy(argptr2, argptr);
	cnt = vsnprintf(NULL, 0, fmt, argptr2);
	va_end(argptr2);

	exptstr = (char *)realloc(exptstr, exptstrlen + cnt + 1);
	if (!exptstr) {
		exptstrlen = 0;
		return 0;
	}

	cnt = vsnprintf(exptstr + exptstrlen, cnt + 1, fmt, argptr);
	exptstrlen += cnt;

	return cnt;
}

/* vsetko sa posiela do suboru (handle == exportfile),
 * ak premenna exptused je 0,
 *    naviac ak isbothExports, tak sa posiela vystup aj na konzolu (stdout),
 * ak premenna exptused je 1,  tak sa posiela vystup iba na konzolu (stdout)
 */
short int Export(const char *fmt, ...){
	va_list argptr;
	short int cnt;

	va_start(argptr, fmt);
#ifdef EXPORT_TO_STRING
	cnt = Export_to_string(fmt, argptr);
#else
	if (exptused == SUCCESS){
		cnt = vfprintf(exportfile, fmt, argptr);
		if (isbothExports){
			cnt = vprintf(fmt, argptr);
		}
	}
	else{
		cnt = vprintf(fmt, argptr);
	}
#endif /* EXPORT_TO_STRING */
	va_end(argptr);

	return(cnt);
}

short int ExportHtmlComment(const char *fmt, ...){
	
	va_list argptr;
	short int cnt = Export("\n" HTML_COMMENT_BEGIN);

	va_start(argptr, fmt);
#ifdef EXPORT_TO_STRING
	cnt += Export_to_string(fmt, argptr);
#else
	if (exptused == SUCCESS){
		cnt += vfprintf(exportfile, fmt, argptr);
		if (isbothExports){
			cnt += vprintf(fmt, argptr);
		}
	}
	else{
		cnt += vprintf(fmt, argptr);
	}
#endif /* EXPORT_TO_STRING */
	va_end(argptr);

	cnt += Export(HTML_COMMENT_END"\n");
	return(cnt);
}

short int Export_to_file(FILE * expt, const char *fmt, ...){
	va_list argptr;
	short int cnt;

	// klasické volanie ako Export
	if ((expt == NULL) && (exptused == SUCCESS)){
		expt = exportfile;
	}

	va_start(argptr, fmt);
	if (expt != NULL){
		cnt = vfprintf(expt, fmt, argptr);
		if (isbothExports){
			cnt = vprintf(fmt, argptr);
		}
	}
	else{
#ifdef EXPORT_TO_STRING
		cnt = Export_to_string(fmt, argptr);
#else
		cnt = vprintf(fmt, argptr);
#endif /* EXPORT_TO_STRING */
	}
	va_end(argptr);

	return(cnt);
}

char *getExportedString(void) {
	return exptstr;
}

// Converts wide char into utf8 string and exports it.
void ExportRawWchar(int c) {
	char buf[5];
	char *out = buf;
	EncodeWchar(c, &out);
	*out = 0;
	Export("%s", buf);
}// ExportRawWchar()

void ExportChar(int c, short int skip_chars_for_blind_friendly_version /* = NIE */) {
	// ToDo: consider special behaviour for 'plain' text export

	// blind-friendly export
	if (skip_chars_for_blind_friendly_version == ANO) {
		if ((c == CHAR_PRAYER_ASTERISK) || (c == CHAR_PRAYER_CROSS) || (c == CHAR_PRAYER_CROSS_ALT) || (c == CHAR_PRAYER_TRIANGLE)) {
			; // skip special characters for blind-friendly version
		}
		else if (c == CHAR_NONBREAKING_SPACE) {
			Export("%c", CHAR_SPACE);
		}
		else {
			ExportRawWchar(c);
		}
		return;
	}

	// ordinary behaviour
	if (c == CHAR_NONBREAKING_SPACE) {
		Export(HTML_NONBREAKING_SPACE);
	}
	else {
		ExportRawWchar(c);
	}
	return;
}// ExportChar()

void ExportStringCharByChar(const char * input, short int skip_chars_for_blind_friendly_version /* = NIE */) {
	short int ok = TRUE;
	const char* in = input;

	while (*in) {
		int c = DecodeWchar(&in);
		if ((c == '&') && (ok == TRUE)) {
			ok = FALSE;
		}
		if ((c == ';') && (ok == FALSE)) {
			ok = TRUE;
		}

		if (ok == TRUE) {
			ExportChar(c, skip_chars_for_blind_friendly_version);
		}// ok == TRUE
	}
	return;
}// ExportStringCharByChar()

#define YYdefault() { { \
	fprintf(exportfile, "%c", c); \
	if(isbothExports) \
		printf("%c", c); \
	} }

#define YYcharHTML(Kam, Lat2, ASCII, HTML, TeX, IBM)	{ { \
	fprintf(exportfile, "%s", HTML); \
	if(isbothExports) \
		printf("%s", HTML); \
	} }

#define YYcharASCII(Kam, Lat2, ASCII, HTML, TeX, IBM)	{ { \
	fprintf(exportfile, "%c", ASCII); \
	if(isbothExports) \
		printf("%c", ASCII); \
	} }

#endif /*__MYEXPT_CPP_*/


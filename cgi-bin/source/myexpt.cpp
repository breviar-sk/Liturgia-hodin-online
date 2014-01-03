/***********************************************************************/
/*                                                                     */
/* myexpt.cpp                                                          */
/* (c)1999-2014 | Juraj Vidéky | videky@breviar.sk                     */
/*                                                                     */
/* description | obsahuje exportne rutinky na export                   */
/*               do suboru FILE_EXPORT alebo stdout                    */
/* document history                                                    */
/*   14/11/1999A.D. | created                                          */
/*   10/02/2000A.D. | zmenena definicia FILE_EXPORT                    */
/*   24/02/2000A.D. | zmenil som if defined: povodne tam bolo          */
/*                    DEBUG, teraz EXPORT_TO_FILE,                     */
/*                    pridal som EXPORT_TO_STDOUT                      */
/*   06/09/2001A.D. | tento popis                                      */
/*   2003-07-08a.D. | pridany append pre export (podla switchu)        */
/*   2003-07-15a.D. | odstraneny #include "mybase.h"                   */
/*   2011-05-18a.D. | odstránené ExpL2HTML(), pridané Export_to_file() */
/*                                                                     */
/***********************************************************************/

#include "vstudio.h"

#ifndef __MYEXPT_CPP_
#define __MYEXPT_CPP_

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "mydefs.h"
#include "myexpt.h"

/* #define FILE_EXPORT -- v myexpt.h */
/* povodne to bolo #define, avsak kvoli tomu, aby sa to dalo menit,
 * v myexpt.h je deklarovane
 *
 * extern char FILE_EXPORT[MAX_STR];
 *
 * a to je definovane nasledovne:
 *
 */
char FILE_EXPORT[MAX_STR] = DEFAULT_FILE_EXPORT;

/* navratove hodnoty su prerobene na int-y; vysledok SUCCESS resp. FAILURE */

short int isbothExports = NIE;
/* inicialna hodnota true;
 * ci pri debuggovacom zapisovani do fajlu pisat aj na obrazovku */

void bothExports(void){
	isbothExports = ANO;
}

short int exptused;
FILE *exportfile;

char *exptstr = NULL;
int exptstrlen = 0;

short int initExport(void){
#if defined(EXPORT_TO_FILE)
	/* zapisovanie vyslednej stranky do suboru; pozor na nazvy suborov "" (STR_EMPTY) a "+" */
	if(FILE_EXPORT[strlen(FILE_EXPORT) - 1] == '+'){
		/* append, nie novy fajl; 13/03/2000A.D. */
		FILE_EXPORT[strlen(FILE_EXPORT) - 1] = '\0'; /* zrusime '+' na konci */
		exportfile = fopen(FILE_EXPORT, "a+t");
	}
	else{
		/* 2003-07-08 ani som netusil, ze som to spravil kedysi aj na append...
		 * ale teraz som korektne pridal switch `a'
		 */
		/* novy fajl */
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

short int initExport(const char *expt_filename){ /* pridane, 13/03/2000A.D. */
	if(exptused == SUCCESS){
		closeExport();
	}
	strcpy(FILE_EXPORT, expt_filename);
	return initExport();
}

short int closeExport(void){ /* pridane, urobi fclose(); 13/03/2000A.D. */
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
	if(input_file != NULL){
		while((c = fgetc(input_file)) != EOF)
			fputc(c, exportfile);
	}
}

// used from http://bytes.com/topic/c/answers/215169-va_copy-implementation | similar answer at http://stackoverflow.com/questions/558223/va-copy-porting-to-visual-c
// #ifndef va_copy
#ifdef _MSC_VER 
// WARNING - DANGER - ASSUMES TYPICAL STACK MACHINE
#define va_copy(dst, src) ((void)((dst) = (src)))
#endif

short int Export_to_string(const char *fmt, va_list argptr) {
	short int cnt;
	va_list argptr2;
	
	va_copy(argptr2, argptr);
	cnt = vsnprintf(NULL, 0, fmt, argptr2);
	va_end(argptr2);

	exptstr = (char *)realloc(exptstr, exptstrlen+cnt+1);
	if (!exptstr) {
		exptstrlen = 0;
		return 0;
	}
	
	cnt = vsnprintf(exptstr + exptstrlen, cnt+1, fmt, argptr);
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
	if(exptused == SUCCESS){
		cnt = vfprintf(exportfile, fmt, argptr);
		if(isbothExports)
			cnt = vprintf(fmt, argptr);
	}
	else{
		cnt = vprintf(fmt, argptr);
	}
#endif /* EXPORT_TO_STRING */
	va_end(argptr);

	return(cnt);
}

short int Export_to_file(FILE * expt, const char *fmt, ...){
	va_list argptr;
	short int cnt;

	// klasické volanie ako Export
	if((expt == NULL) && (exptused == SUCCESS)){
		expt = exportfile;
	}

	va_start(argptr, fmt);
	if(expt != NULL){
		cnt = vfprintf(expt, fmt, argptr);
		if(isbothExports)
			cnt = vprintf(fmt, argptr);
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


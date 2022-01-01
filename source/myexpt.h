/**************************************************************/
/*                                                            */
/* myexpt.h                                                   */
/* (c)1999-2022 | Juraj Vidéky | videky@breviar.sk            */
/*                                                            */
/* description | export routines for exporting HTML pages     */
/*               to file FILE_EXPORT or to stdout             */
/*                                                            */
/**************************************************************/

#include "vstudio.h"

#ifndef __MYEXPT_H_
#define __MYEXPT_H_

#include <stdio.h>
#include "common.h"
#include "utf8-utils.h"

#define DEFAULT_FILE_EXPORT "export.htm"
#define DEFAULT_HTML_EXPORT "zoznam.htm" // "export2.htm"
#define DEFAULT_MONTH_EXPORT "index.htm" // "^ hore"

short int Export(const char* fmt, ...);
short int ExportHtmlComment(const char* fmt, ...);
short int ExportXmlError(const char* fmt, ...);
short int Export_to_file(FILE * expt, const char* fmt, ...);

void ExportRawWchar(int c);
void ExportChar(int c, short int skip_chars_for_voice_output = NIE);
void ExportStringCharByChar(const char*  string, short int skip_chars_for_voice_output = NIE);

void bothExports(void);
void dumpFile(char *fname);

extern char FILE_EXPORT[MAX_STR];

extern short int exptused;
extern FILE *exportfile;

short int initExport(void);
short int initExport(const char* expt_filename);
short int closeExport(void);

char *getExportedString(void);

#endif /*__MYEXPT_H_*/


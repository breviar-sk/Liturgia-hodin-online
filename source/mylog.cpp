/***************************************************************/
/*                                                             */
/* mylog.cpp                                                   */
/* (c)1999-2011 | Juraj Videky | videky@breviar.sk             */
/*                                                             */
/* description | pomocne vypisovanie (logovanie) na obrazovku  */
/*               a/alebo do suboru                             */
/* document history                                            */
/*   07/12/1997A.D. | created                                  */
/*   13/10/1998A.D. | prerobeny                                */
/*   27/10/1998A.D. | male zmeny                               */
/*   01/12/1999A.D. | pridany NoLog (emptyLog)                 */
/*                    LOGGING ponechane (v takom pripade sa    */
/*                    loguje)                                  */
/*   24/02/2000A.D. |  pridane LOG_TO_FILE / LOG_TO_STDOUT     */
/*   06/09/2001A.D. | tento popis                              */
/*   2003-08-07a.D. | closeLog-dorobene #ifdef (LOG_TO_STDOUT) */
/*   2005-03-28a.D. | Log - dorobene #ifdef                    */
/*                                                             */
/* notes |                                                     */
/*   * ked je v materskom programe definovane LOG_TO_FILE, bude*/
/*     sa logovat do suboru, ktory treba dat ako vstup fname   */
/*     v initLog                                               */
/*   * v opacnom pripade sa nebude logovat do suboru           */
/*                                                             */
/***************************************************************/

#include "vstudio.h"

#ifndef __MYLOG_CPP_
#define __MYLOG_CPP_

#include <stdio.h>
#include <stdarg.h>
#include "mydefs.h" /* tu su deklarovane vecicky ako sa ma __Log-ovat */
#include "mylog.h"

short int both;

void bothLogs(void){ both = (0 == 0); }
void fileLog(void){ both = (0 != 0); }
short int isbothLogs(void){ return both; }

#ifdef LOGGING

FILE *logfile;
short int used;

/* popis: otvori logovaci subor; globalna premenna logfile obsahuje handle
 * vracia: on success, returns 0
 *         on error, returns 1
 */
short int initLog(const char *fname){
	fileLog();
#if defined(LOG_TO_FILE)
	logfile = fopen(fname, "wt");
	used = (logfile == NULL)? 1: 0;
#elif defined(LOG_TO_STDOUT)
	logfile = stdout;
	used = 0;
#else
	#error Unsupported logging model (use _LOG_TO_STDOUT or _LOG_TO_FILE)
#endif
	return used; // 1: failure, 0: success
}

/* popis: zatvori logovaci subor
 * vracia: on success, returns 0
 *         on error, returns EOF; presne ako fclose()
 * 2003-08-07: dorobene, ze ked LOG_TO_STDOUT, tak ina hlaska, nie error
 */
short int closeLog(void){
	short int ret;
	if(used == 0){
#if defined(LOG_TO_FILE)
		if((ret = fclose(logfile)) == EOF)
			fprintf(stderr, "Cannot close log file\n");
#elif defined(LOG_TO_STDOUT)
		fprintf(stderr, "Log finished, I do not close log file (stdout)\n");
#else
	#error Unsupported logging model (use _LOG_TO_STDOUT or _LOG_TO_FILE)
#endif
	}
	else{
		fprintf(stderr, "Log file not opened\n");
		ret = EOF;
	}
	return ret;
}

short int __Log(const char *fmt, ...)
{
	va_list argptr;
	short int cnt;

/* 2005-03-28; odkomentované a upravené 2006-08-19: Ak logujeme na stdout (teda zrejme do HTML), vypiseme HTML <p> */
#if defined(LOG_TO_STDOUT)
	fprintf(logfile, "\n<!-- Log: ");
#endif

	va_start(argptr, fmt);
	if(used == 0){
		cnt = vfprintf(logfile, fmt, argptr);
		if(both)
			cnt = vprintf(fmt, argptr);
	}
	else
		cnt = vprintf(fmt, argptr);
	va_end(argptr);

#if defined(LOG_TO_STDOUT)
	fprintf(logfile, "-->");
#endif

	return(cnt);
}

/* popis: zapise do logfile ciferne (po cifrach) int c
 * priklad: pre c==234 napise znaky '2', '3', '4'
 */
void Logint(short int c){
	short int d = 10000;
	if(used == 0){ // iba ak je pouzivany logfile
		if(c < 0){
			fputc('-', logfile);
			if(both)
				fputc('-', stdout);
			c = -c;
		}
		while(d > 1){
			if(c >= d){
				fputc(48 + (c/d), logfile);
				if(both)
					fputc(48 + (c/d), stdout);
				c = c - d * (c/d);
			}
			d = d/10;
		}
		fputc(48 + c, logfile);
		if(both)
			fputc(48 + c, stdout);
	}
}

/*
 * Nasleduje len atrapa modulu mylog.cpp
 * pouzije sa vtedy, ak sa nedebuguje
 *
 * staci v materskom programe nedefinovat #define LOGGING
 */

#else /* nie LOGGING */

short int initLog(const char *fname){return 0;}
/* void bothLogs(void){} */
/* void fileLog(void){} */
short int closeLog(void){return 0;}
short int __Log(const char *fmt, ...){return 0;}
void Logint(short int c){};

#endif /* LOGGING */

/* ------------------------------------------------------------------- */
/* empty log - nerobi nic, ale ma vstup (...) */
short int NoLog(const char *fmt, ...){
	return(fmt == 0); /* aby nehlasilo param `fmt' not used */
}


#endif /* __MYLOG_CPP_ */


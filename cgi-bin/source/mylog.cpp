/***************************************************************/
/*                                                             */
/* mylog.cpp                                                   */
/* (c)1999-2015 | Juraj Vidéky | videky@breviar.sk             */
/*                                                             */
/* description | logging to file LOG_TO_FILE or to stdout      */
/*                                                             */
/* notes |                                                     */
/*   * if LOG_TO_FILE is defined, logging will be written to   */
/*     file which must be as an input 'fname' in initLog       */
/*   * otherwise, logging will not written to file             */
/*                                                             */
/***************************************************************/

#include "vstudio.h"

#ifndef __MYLOG_CPP_
#define __MYLOG_CPP_

#include <stdio.h>
#include <stdarg.h>
#include "mydefs.h"
#include "mylog.h"

short int both;

void bothLogs(void){ both = (0 == 0); }
void fileLog(void){ both = (0 != 0); }
short int isbothLogs(void){ return both; }

#ifdef LOGGING

#ifdef LOG_TO_ANDROID
#include <android/log.h>
#endif //LOG_TO_ANDROID

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
#elif defined(LOG_TO_ANDROID)
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
#elif defined(LOG_TO_ANDROID)
		// nothing to do
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

#if defined(LOG_TO_STDOUT)
	fprintf(logfile, "\n<!-- Log: ");
#endif

	va_start(argptr, fmt);
#ifdef LOG_TO_ANDROID
	__android_log_vprint(ANDROID_LOG_VERBOSE, "Breviar", fmt, argptr);

#else // not LOG_TO_ANDROID
	if(used == 0){
		cnt = vfprintf(logfile, fmt, argptr);
		if (both){
			cnt = vprintf(fmt, argptr);
		}
	}
	else
		cnt = vprintf(fmt, argptr);
#endif // LOG_TO_ANDROID
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

#else /* nie LOGGING */

short int initLog(const char *fname){
	Q_UNUSED(fname);
	return 0;
}

short int closeLog(void){
	return 0;
}

short int __Log(const char *fmt, ...){
	Q_UNUSED(fmt);
	return 0;
}

void Logint(short int c){
	Q_UNUSED(c);
};

#endif /* LOGGING */

//---------------------------------------------------------------------
short int NoLog(const char *fmt, ...){
	return(fmt == 0);
}

#endif /* __MYLOG_CPP_ */


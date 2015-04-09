/***************************************************************/
/*                                                             */
/* mylog.h                                                     */
/* (c)1999-2015 | Juraj Vidéky | videky@breviar.sk             */
/*                                                             */
/* description | logging to file LOG_TO_FILE or to stdout      */
/*                                                             */
/***************************************************************/

#include "vstudio.h"

#ifndef __MYLOG_H_
#define __MYLOG_H_

#define EmptyLog NoLog
#define emptyLog NoLog
short int NoLog(const char *fmt, ...);

short int initLog(const char *fname);

void bothLogs(void);
void fileLog(void);

short int isbothLogs(void);
short int closeLog(void);

short int __Log(const char *fmt, ...);
void Logint(int c);

#endif // __MYLOG_H_

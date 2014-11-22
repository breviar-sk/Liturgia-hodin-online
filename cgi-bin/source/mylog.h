/***************************************************************/
/*                                                             */
/* mylog.h                                                     */
/* (c)1999-2014 | Juraj Vidéky | videky@breviar.sk             */
/*                                                             */
/* description | logging to file LOG_TO_FILE or to stdout      */
/*                                                             */
/***************************************************************/

#include "vstudio.h"

#ifndef __MYLOG_H_
#define __MYLOG_H_

#define EmptyLog NoLog
#define emptyLog NoLog
short int NoLog(const char *fmt, ...); /* empty log - nerobi nic, ale ma vstup (...) */

short int initLog(const char *fname);
void bothLogs(void); /* prepne na oboje logovanie */
void fileLog(void); /* prepne na logovanie do fajlu */
short int isbothLogs(void); /* vrati 1, ak su oba logy, inak vrati 0 */
short int closeLog(void);
/* Log() premenovana na __Log() -- 24/02/2000A.D. */
short int __Log(const char *fmt, ...);
void Logint(int c);

#endif // __MYLOG_H_

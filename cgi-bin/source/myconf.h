/***************************************************************/
/*                                                             */
/* myconf.h                                                    */
/* (c)1999-2012 | Juraj Videky | videky@breviar.sk             */
/*                                                             */
/* description | poskytuje rozhranie na konfiguraciu,          */
/*               subor CONFIG_FILE                             */
/* document history                                            */
/*   30/03/2000A.D. | created                                  */
/*   06/09/2001A.D. | tento popis                              */
/*   2003-07-15a.D. | #include "mybase.h" nahradeny "mydefs.h" */
/*   2004-03-17a.D. | pridany INCLUDE_DIR                      */
/*   2011-01-31a.D. | pridané CFG_OPTION1_DEFAULT (1 až 5)     */
/*   2011-04-11a.D. | CONFIG_FILE sa nastavuje pod¾a "OS"      */
/*                                                             */
/***************************************************************/

#include "vstudio.h"

#ifndef __MYCONF_H_
#define __MYCONF_H_

#include "mysystem.h"
#include "mysysdef.h"

#define MAX_HTTP_STR	80
#define MAX_MAIL_STR	50
#define MAX_INCD_STR	50
#define MAX_OPTION_LENGTH	40
#define MAX_VALUE_LENGTH	80

#ifdef OS_Windows_Ruby
#define CONFIG_FILE "breviar-local.cfg"
#elif defined(BEHAVIOUR_CMDLINE)
#define CONFIG_FILE "breviar-cmdline.cfg"
#else // defined(BEHAVIOUR_WEB)
#define CONFIG_FILE "breviar-web.cfg"
#endif

#ifdef OS_Windows_Ruby
#define DEFAULT_FONT_FAMILY_SERIF "Cambria, Constantia, Georgia, Liberation, Gentium, Garamond, Serif"
#define DEFAULT_FONT_FAMILY_SANS_SERIF "Candara, Tahoma, Verdana, Helvetica, Sans-Serif"
#else
#define DEFAULT_FONT_FAMILY_SERIF "Serif"
#define DEFAULT_FONT_FAMILY_SANS_SERIF "Sans-Serif"
#endif
#define DEFAULT_FONT_FAMILY_INHERIT "inherit"
#define DEFAULT_FONT_SIZE_INHERIT "inherit"

extern char cfg_INCLUDE_DIR_default [MAX_INCD_STR];

extern short int cfg_option_default[POCET_GLOBAL_OPT][POCET_JAZYKOV + 1];

#define POCET_DALSICH_CONF 3

extern char cfg_http_address_default[POCET_JAZYKOV + 1][MAX_HTTP_STR];
extern char cfg_http_display_address_default[POCET_JAZYKOV + 1][MAX_HTTP_STR];
extern char cfg_mail_address_default[POCET_JAZYKOV + 1][MAX_MAIL_STR];

#define CFG_OPTION_DEFAULT(i) cfg_option_default[i][_global_jazyk]

const short int cfg_option_default_PROG[POCET_GLOBAL_OPT] = 
#ifdef OS_Windows_Ruby
{3, 64, 0, 0, 0};
#else
{0, 31, 0, 0, 0};
#endif

void readConfig(void);
void printConfig(void);

#endif /* __MYCONF_H_ */


/*********************************************************/
/*                                                       */
/* mydefs.cpp                                            */
/* (c)1999-2017 | Juraj Vidéky | videky@breviar.sk       */
/*                                                       */
/* description | some basic define's                     */
/*                                                       */
/*********************************************************/

#include "vstudio.h"

#ifndef __MYDEFS_CPP_
#define __MYDEFS_CPP_

#include "mydefs.h"
#include <string.h>
#include "mystring.h"
#include "myconf.h"
#include "breviar.h"

char script_name[MAX_STR] = STR_EMPTY;
char uncgi_name[MAX_STR] = STR_EMPTY;

void updateScriptName(void){
	strcpy(script_name, cfg_http_address_default[_global_jazyk]);
	strcat(script_name, SCRIPT_PATH(SCRIPT_NAME));
}

void updateUnCGIName(void){
	strcpy(uncgi_name, cfg_http_address_default[_global_jazyk]);
	strcat(uncgi_name, UNCGI_SCRIPT_NAME);
}

#endif /* __MYDEFS_CPP_ */


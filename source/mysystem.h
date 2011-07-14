/***************************************************************/
/*                                                             */
/* mysystem.h                                                  */
/* (c)1999-2011 | Juraj Videky | videky@breviar.sk             */
/*                                                             */
/* NOTE: popis nižšie -- for description see below             */
/*                                                             */
/***************************************************************/
#include "vstudio.h"

#ifndef __MYSYSTEM_H_
#define __MYSYSTEM_H_

#undef USE_UNCGI

#ifndef MODEL_SELECTED_IN_MAKEFILE

#undef MODEL_linux
#undef MODEL_linux_commandline
#undef MODEL_android
#undef MODEL_Windows_RUBY
#undef MODEL_Windows_commandline

#undef MODEL_DEBUG_linux
#undef MODEL_DEBUG_linux_commandline
#undef MODEL_DEBUG_Windows_RUBY
#undef MODEL_DEBUG_Windows_commandline

/* Modely pre Windows */

/* Modely pre ostré použitie -- for release */
#define MODEL_Windows_RUBY
//#define MODEL_Windows_commandline

/* Modely pre debugovanie -- for debug */
//#define MODEL_DEBUG_Windows_RUBY
//#define MODEL_DEBUG_Windows_commandline

/* Modely pre linux */

/* Modely pre ostré použitie -- for release */
//#define MODEL_linux
//#define MODEL_linux_commandline

/* Modely pre debugovanie -- for debug */
//#define MODEL_DEBUG_linux
//#define MODEL_DEBUG_linux_commandline

#endif // MODEL_SELECTED_IN_MAKEFILE

#endif // __MYSYSTEM_H_

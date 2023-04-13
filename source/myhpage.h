/************************************************************************/
/*                                                                      */
/* myhpage.h                                                            */
/* (c)1999-2023 | Juraj Vidéky | videky@breviar.sk                      */
/*                                                                      */
/* description | HTML document dynamically generated header and footer  */
/*                                                                      */
/************************************************************************/

#include "vstudio.h"
#include "myexpt.h"

#ifndef __MYHPAGE_H_
#define __MYHPAGE_H_

#define HTML_TOP "p-top"
#define HTML_ANAME_TOP "<div id=\"contentRoot\"><a name=\"" HTML_TOP "\"></a>"

#ifdef IO_ANDROID
#define HTML_TRANSPARENT_NAV_RIGHT "<div id=\"nav-arrow-up\" class=\"nav-arrow-right\" onclick=\"bridge.pageUp()\"></div>\n" \
  "<div id=\"nav-arrow-down\" class=\"nav-arrow-right\" onclick=\"bridge.pageDown()\"></div>\n"
#else
#define HTML_TRANSPARENT_NAV_RIGHT "<div id=\"nav-arrow-up\" class=\"nav-arrow-right\" onclick=\"window.scrollBy(0, -0.95*window.innerHeight)\"></div>\n" \
  "<div id=\"nav-arrow-down\" class=\"nav-arrow-right\" onclick=\"window.scrollBy(0, 0.95*window.innerHeight)\"></div>\n"
#endif

#ifdef IO_ANDROID
#define HTML_TRANSPARENT_NAV_LEFT "<div id=\"nav-arrow-up\" class=\"nav-arrow-left\" onclick=\"bridge.pageUp()\"></div>\n" \
  "<div id=\"nav-arrow-down\" class=\"nav-arrow-left\" onclick=\"bridge.pageDown()\"></div>\n"
#else
#define HTML_TRANSPARENT_NAV_LEFT "<div id=\"nav-arrow-up\" class=\"nav-arrow-left\" onclick=\"window.scrollBy(0, -0.95*window.innerHeight)\"></div>\n" \
  "<div id=\"nav-arrow-down\" class=\"nav-arrow-left\" onclick=\"window.scrollBy(0, 0.95*window.innerHeight)\"></div>\n"
#endif

#define HTML_BOTTOM "p-bottom"
#define HTML_ANAME_BOTTOM "<a name=\"" HTML_BOTTOM "\"></a></div>"

#define HTML_P_PATKA "p class=\"patka\""

// header
void hlavicka(char* title, short int level = 0, short int spec = 0);
void hlavicka(char* title, FILE* expt, short int level = 0, short int spec = 0);

// XML header
void xml_hlavicka(void);
void xml_hlavicka(FILE* expt);

// footer
void patka(void);
void patka(FILE* expt);

// XML footer
void xml_patka(void);
void xml_patka(FILE* expt);

void myhpage_init_globals(void);

#endif // __MYHPAGE_H_


/************************************************************************/
/*                                                                      */
/* myhpage.h                                                            */
/* (c)1999-2024 | Juraj Vidéky | videky@breviar.sk                      */
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

#define HTML_SIDE_NAVIGATION_SIDEBAR "<div id=\"mySidebar\" class=\"sidebar\">\n" \
	"\t<a href=\"javascript:void(0)\" class=\"closebtn\" onclick=\"closeNav()\">×</a>"

#define HTML_SIDE_NAVIGATION_COPYRIGHT "<p class=\"small\">©&nbsp;Juraj&nbsp;Vidéky</p>"

#define HTML_SIDE_NAVIGATION_MAIN "<div id=\"main\">\n" \
	"\t<div class=\"openbtn\" onclick=\"openNav()\">☰</div>\n" \
	"</div>"

#define HTML_SIDE_NAVIGATION_WEB_THEME "<a href=\"javascript:void(0)\" onclick=\"switchNightMode()\">"
#define HTML_SIDE_NAVIGATION_WEB_THEME_SPAN "<span id=\"themesign\"></span>"

#define HTML_SIDE_NAVIGATION_SCRIPT "<script>" \
"\nfunction openNav() {" \
"\n\tdocument.getElementById(\"mySidebar\").style.width = \"240px\";" \
"\n}" \
"\n" \
"\nfunction closeNav() {" \
"\n\tdocument.getElementById(\"mySidebar\").style.width = \"0\";" \
"\n}" \
"\n</script>"

#define HTML_NAVIGATION_DROPDOWN_BTN "<div class=\"dropdown-btn\">"

#define HTML_NAVIGATION_DROPDOWN_BTN_2 "<span id=\"trianglesign\" style=\"font-size: 50%%;\">&#9660;</span>"

#define HTML_NAVIGATION_DROPDOWN_CONTAINER "<div class=\"dropdown-container\">"

#define HTML_NAVIGATION_DROPDOWN_ITEM ""

#define HTML_BOTTOM "p-bottom"
#define HTML_ANAME_BOTTOM "<a name=\"" HTML_BOTTOM "\"></a></div>"

#define HTML_P_PATKA "p class=\"patka\""

// header
void hlavicka(char* title, short int level = 0, short int spec = 0);
void hlavicka(char* title, FILE* expt, short int level = 0, short int spec = 0);

void hlavicka_sidemenu();
void hlavicka_sidemenu(FILE* expt);

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


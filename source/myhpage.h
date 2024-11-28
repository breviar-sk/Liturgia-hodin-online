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
#define HTML_TRANSPARENT_NAV_UP_RIGHT "<div id=\"nav-arrow-up\" class=\"nav-arrow-right\" onclick=\"bridge.pageUp()\"></div>\n"
#define HTML_TRANSPARENT_NAV_DOWN_RIGHT "<div id=\"nav-arrow-down\" class=\"nav-arrow-right\" onclick=\"bridge.pageDown()\"></div>\n"
#define HTML_TRANSPARENT_NAV_UP_LEFT "<div id=\"nav-arrow-up\" class=\"nav-arrow-left\" onclick=\"bridge.pageUp()\"></div>\n"
#define HTML_TRANSPARENT_NAV_DOWN_LEFT "<div id=\"nav-arrow-down\" class=\"nav-arrow-left\" onclick=\"bridge.pageDown()\"></div>\n"
#else
#define HTML_TRANSPARENT_NAV_UP_RIGHT "<div id=\"nav-arrow-up\" class=\"nav-arrow-right\" onclick=\"window.scrollBy(0, -0.95*window.innerHeight)\"></div>\n"
#define HTML_TRANSPARENT_NAV_DOWN_RIGHT "<div id=\"nav-arrow-down\" class=\"nav-arrow-right\" onclick=\"window.scrollBy(0, 0.95*window.innerHeight)\"></div>\n"
#define HTML_TRANSPARENT_NAV_UP_LEFT "<div id=\"nav-arrow-up\" class=\"nav-arrow-left\" onclick=\"window.scrollBy(0, -0.95*window.innerHeight)\"></div>\n"
#define HTML_TRANSPARENT_NAV_DOWN_LEFT "<div id=\"nav-arrow-down\" class=\"nav-arrow-left\" onclick=\"window.scrollBy(0, 0.95*window.innerHeight)\"></div>\n"
#endif

#define HTML_TRANSPARENT_NAV_RIGHT HTML_TRANSPARENT_NAV_UP_RIGHT HTML_TRANSPARENT_NAV_DOWN_RIGHT
#define HTML_TRANSPARENT_NAV_LEFT HTML_TRANSPARENT_NAV_UP_LEFT HTML_TRANSPARENT_NAV_DOWN_LEFT

#define HTML_SIDE_NAVIGATION_SIDEBAR "<div id=\"mySidebar\" class=\"sidebar\" onload=\"removeSessionStorageSidemenuRight()\">\n" \
	"\t<a href=\"javascript:void(0)\" class=\"closebtn\" onclick=\"closeNav()\">×</a>"

#define HTML_SIDE_NAVIGATION_SIDEBAR_RIGHT "<div id=\"mySidebarR\" class=\"sidebarR\" onload=\"setSessionStorageSidemenuRight()\">\n" \
	"\t<a href=\"javascript:void(0)\" class=\"closebtnR\" onclick=\"closeNavR()\">×</a>"

#define HTML_SIDE_NAVIGATION_COPYRIGHT "<p class=\"small\">©&nbsp;Juraj&nbsp;Vidéky</p>"

#define HTML_SIDE_NAVIGATION_MAIN "<div id=\"main\">\n" \
	"\t<div id=\"myOpenbtnL\" class=\"openbtn\" onclick=\"openNav()\">☰</div>\n" \
	"</div>"

#define HTML_SIDE_NAVIGATION_MAIN_RIGHT "<div id=\"main\">\n" \
	"\t<div id=\"myOpenbtnR\" class=\"openbtnR\" onclick=\"openNavR()\">☰</div>\n" \
	"</div>"

#define HTML_SIDE_NAVIGATION_TO_LEFT "<a href=\"javascript:void(0)\" class=\"small\" onclick=\"switchMenuLocation()\">⚟&nbsp;%s</span></a>"
#define HTML_SIDE_NAVIGATION_TO_RIGHT "<a href=\"javascript:void(0)\" class=\"small\" onclick=\"switchMenuLocation()\">%s&nbsp;⚞</span></a>"

#define HTML_SIDE_NAVIGATION_WEB_THEME "<a href=\"javascript:void(0)\" onclick=\"switchNightMode()\">"
#define HTML_SIDE_NAVIGATION_WEB_THEME_SPAN "<span id=\"themesign\"></span>"
#define HTML_SIDE_NAVIGATION_WEB_THEME_SPAN_RIGHT "<span id=\"themesignR\"></span>"

// ToDo: maybe add another JS methods from sidemenu.js
#define HTML_SIDE_NAVIGATION_SCRIPT "<script>" \
"\nfunction openNav() {" \
"\n\tdocument.getElementById(\"mySidebar\").style.width = \"220px\";" \
"\n}" \
"\n" \
"\nfunction closeNav() {" \
"\n\tdocument.getElementById(\"mySidebar\").style.width = \"0\";" \
"\n}" \
"\n" \
"\nfunction openNavR() {" \
"\n\tdocument.getElementById(\"mySidebarR\").style.width = \"220px\";" \
"\n}" \
"\n" \
"\nfunction closeNavR() {" \
"\n\tdocument.getElementById(\"mySidebarR\").style.width = \"0\";" \
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


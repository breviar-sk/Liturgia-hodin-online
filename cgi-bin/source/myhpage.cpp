/************************************************************************/
/*                                                                      */
/* myhpage.cpp                                                          */
/* (c)1999-2014 | Juraj VidÈky | videky@breviar.sk                      */
/*                                                                      */
/* description | obsahuje vypis hlavicky a patky HTML dokumentu         */
/* document history                                                     */
/*   28/10/1999A.D. | created                                           */
/*   25/02/2000A.D. | zrusena funkcia linky()                           */
/*   12/04/2000A.D. | pridana stranka cfg_HTTP_ADDRESS_default          */
/*   06/09/2001A.D. | tento popis                                       */
/*   2003-06-30a.D. | pridane vypisovanie BUILD_DATE (mybase.h)         */
/*                  - tiez zapoznamkovane Kodovanie w-1250.             */
/*   2003-07-01a.D. | citanie hlavicky zo suboru                        */
/*   2003-07-02a.D. | trosku zmenena patka                              */
/*   2003-07-15a.D. | trosku zmenena hlavicka (ako _header.htm)         */
/*   2004-03-16a.D. | funkcie hlavicka a patka aj do suboru             */
/*   2006-07-31a.D. | prvÈ kroky k jazykov˝m mut·ci·m                   */
/*   2008-01-23a.D. | upravenÈ funkcie patka()                          */
/*   2008-08-08a.D. | upravenÈ funkcie hlavicka() kvÙli css             */
/*   2008-09-26a.D. | pridanÈ pouûitie nazov_mesiaca()                  */
/*   2008-12-22a.D. | upravenÈ exportovanie p‰tky (Ëas)                 */
/*   2009-08-05a.D. | upravenÈ exportovanie hlaviËky                    */
/*   2010-02-15a.D. | upravenÈ hlaviËky aj p‰tky (navig·cia)            */
/*   2011-05-13a.D. | doplnen· aj veækosù fontu                         */
/*   2011-05-18a.D. | doplnenÈ pouûitie charset_jazyka[]                */
/*   2011-05-18a.D. | upraven· a zjednoten· hlaviËka a p‰tka,           */
/*                    _hlavicka() a _patka() pouûÌvaj˙ Export_to_file() */
/*                                                                      */
/*                                                                      */
/************************************************************************/

#include "vstudio.h"

#ifndef __MYHPAGE_CPP_
#define __MYHPAGE_CPP_

#include <stdio.h>
#include <string.h>
#include <time.h> // kvoli time_t a time();
#include "myconf.h" // kvoli cfg_MAIL_ADDRESS_default a cfg_HTTP_ADDRESS_default; pridane 30/03/2000A.D.
#include "myhpage.h"
#include "mydefs.h" // kvoli #ifdef DEBUG; a tiez HTML_ - pridane 2003-07-02
#include "myexpt.h"
#include "mystring.h" // kvoli mystrcpy, 2003-07-01
#include "mylog.h"
#include "breviar.h" // 2006-07-31 kvÙli jazyku a css (2008-08-08)
#include "liturgia.h" // 2006-07-31 kvÙli jazyku
#include "mybuild.h" // 2011-07-11: pridanÈ, kvÙli BUILD_DATE

short int bol_content_type_text_html = NIE;
short int bol_content_type_text_xml = NIE;

#ifndef __MYHPAGE_CPP_HTML_CONST
#define __MYHPAGE_CPP_HTML_CONST

// obsahuje %s
const char *html_header_1 =
// Android KitKat nevie javascriptom zalamovat text, ak je specifikovany tento doctype.
#ifndef MODEL_android
//    "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"\n\t\"http://www.w3.org/TR/html4/loose.dtd\">\n"
	"<!DOCTYPE html>\n"
#endif
    "<html>\n<head>\n\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=%s\">\n\t<meta name=\"Author\" content=\"Juraj VidÈky\">\n";
const char *html_header_css = "\t<link rel=\"stylesheet\" type=\"text/css\" href=\"";
const char *html_footer_1 = STR_EMPTY; // "<p><center>______</center>"; // "<hr>";

const char *xml_header = "<?xml version=\"1.0\" encoding=\"%s\"?>\n\n";

#endif // __MYHPAGE_CPP_HTML_CONST

#define MAX_MAIL_LABEL 20
#define MAX_EXT 5
char html_mail_label[MAX_MAIL_LABEL];
char pismeno_modlitby;
char pismeno_prev[1];
char pismeno_next[1];
char ext[MAX_EXT];
char file_name_pom[MAX_STR];
char *ptr;
short int _local_modlitba;

void myhpage_init_globals() {
	bol_content_type_text_html = NIE;
	bol_content_type_text_xml = NIE;
}

void _header_css(FILE* expt, short int level, const char* nazov_css_suboru) {
	Export_to_file(expt, html_header_css);
#ifdef	EXPORT_CMDLINE_CSS
	// pre command-line pouûitie (aj pre batch mÛd): "./breviar.css" resp. ".\breviar.css"
	// 2009-08-03: level oznaËuje poËet adres·rov, o ktorÈ je treba Ìsù "hore" (pre mesaËn˝ export)
	if(level == 0 && _global_opt_batch_monthly == ANO)
		level = 1;
	if(level < 0 || level > 5)
		level = 0;
	if(level == 0)
		Export_to_file(expt, ".");
	else{
		while(level > 1){
			Export_to_file(expt, "..");
			Export_to_file(expt, STR_PATH_SEPARATOR_HTML);
			level--;
		}
		Export_to_file(expt, "..");
	}
	Export_to_file(expt, STR_PATH_SEPARATOR_HTML);
#else
	Q_UNUSED(level);
	// pre web-pouûitie (aj pre ruby): "/breviar.css"
	Export_to_file(expt, "/");
#endif
	Export_to_file(expt, "%s\">\n", nazov_css_suboru); // n·zov css s˙boru
}

// exportuje hlavicku HTML dokumentu, kam pojde vysledok query
void _hlavicka(char *title, FILE * expt, short int level, short int spec){
	Log("_hlavicka() -- zaËiatok...\n");

	_local_modlitba = _global_modlitba;
	if((_local_modlitba == MODL_PRVE_VESPERY) || (_local_modlitba == MODL_DRUHE_VESPERY))
		_local_modlitba = MODL_VESPERY;
	if((_local_modlitba == MODL_PRVE_KOMPLETORIUM) || (_local_modlitba == MODL_DRUHE_KOMPLETORIUM))
		_local_modlitba = MODL_KOMPLETORIUM;

	// 2009-08-04: viackr·t sa pri exporte modlitby do HTML exportovala hlaviËka; pridan· kontrola
	if(_global_hlavicka_Export > 0){
		Log("return... (_global_hlavicka_Export > 0)\n");
		return;
	}
	_global_hlavicka_Export++;

	// 2013-12-09: inÈ CSS bud˙ len "doplnky" (overrides) k hlavnÈmu CSS
	if(_global_css != CSS_breviar_sk){
		Log("ako prv˝ bude exportovan˝ nazov_css_suboru == %s...\n", nazov_css[CSS_breviar_sk]);
	}
	const char *nazov_css_suboru;
	if(_global_css == CSS_UNDEF){
		nazov_css_suboru = nazov_css[CSS_breviar_sk];
	}// _global_css == CSS_UNDEF
	else{
		nazov_css_suboru = nazov_css[_global_css];
	}// else
	Log("nazov_css_suboru == %s...\n", nazov_css_suboru);

	// 2011-05-05: nastavenie font-family
	//             zatiaæ len pevnÈ reùazce; Ëasom moûno bude premenn· pre n·zov fontu
	// 2011-05-06: doplnenÈ: najprv sa testuje nastavenie _global_font; n·sledne sa prÌpadne nastavia defaulty
	if((_global_font == FONT_UNDEF) || (_global_font == FONT_CHECKBOX)){
		Log("(_global_font == FONT_UNDEF) || (_global_font == FONT_CHECKBOX)...\n");
		if((_global_opt[OPT_2_HTML_EXPORT] & BIT_OPT_2_FONT_FAMILY) == BIT_OPT_2_FONT_FAMILY){
			Log("_global_opt[OPT_2_HTML_EXPORT] & BIT_OPT_2_FONT_FAMILY...\n");
			mystrcpy(_global_css_font_family, DEFAULT_FONT_FAMILY_SANS_SERIF, SMALL);
		}
		else{
			Log("NOT _global_opt[OPT_2_HTML_EXPORT] & BIT_OPT_2_FONT_FAMILY...\n");
			mystrcpy(_global_css_font_family, DEFAULT_FONT_FAMILY_SERIF, SMALL);
		}
	}// (_global_font == FONT_UNDEF)  || (_global_font == FONT_CHECKBOX)
	else if(_global_font == FONT_CSS){
		Log("_global_font == FONT_CSS...\n");
		mystrcpy(_global_css_font_family, DEFAULT_FONT_FAMILY_INHERIT, SMALL);
	}// (_global_font == FONT_CSS)
	else{
		Log("_global_font != FONT_CSS...\n");
		mystrcpy(_global_css_font_family, nazov_fontu[_global_font], SMALL);
	}// else
	Log("_global_css_font_family == %s...\n", _global_css_font_family);

	// 2011-05-13: doplnenÈ: nastavenie font-size
	if(_global_font_size == FONT_SIZE_UNDEF){
		mystrcpy(_global_css_font_size, STR_EMPTY, SMALL);
	}// (_global_font_size == FONT_SIZE_UNDEF)
	else if(_global_font_size == FONT_SIZE_CSS){
		mystrcpy(_global_css_font_size, DEFAULT_FONT_SIZE_INHERIT, SMALL);
	}// (_global_font_size == FONT_SIZE_CSS)
	else{
		mystrcpy(_global_css_font_size, nazov_font_size_css[_global_font_size], SMALL);
	}// else
	Log("_global_css_font_size == %s...\n", _global_css_font_size);

	if(bol_content_type_text_html == NIE){
#if defined(BEHAVIOUR_WEB)
		Export_to_file(expt, "Content-type: text/html\n");
		Export_to_file(expt, "\n");
#endif
		bol_content_type_text_html = ANO;
	}
	Log("creating header...\n");
	// 2003-07-15, zmenene na hlavicku pre css-ko; zrusene <style>
	// 2008-08-08: pridanÈ dynamicky css-ko
	// 2010-02-15: statickÈ texty do konöt·nt
	// 2011-05-18: charset sa nastavÌ podæa jazyka
	Log("element <head>...\n");
	Export_to_file(expt, (char *)html_header_1, charset_jazyka[_global_jazyk]);

	// CSS (1 resp. 2)
	if(_global_css != CSS_breviar_sk){
		_header_css(expt, level, nazov_css[CSS_breviar_sk]);
	}
    _header_css(expt, level, nazov_css_suboru);
	// CSS override night mode
    if ((_global_opt[OPT_2_HTML_EXPORT] & BIT_OPT_2_NOCNY_REZIM) == BIT_OPT_2_NOCNY_REZIM) {
        _header_css(expt, level, nazov_css_invert_colors);
    }
	// CSS override normal font (no bold)
    if ((_global_opt[OPT_0_SPECIALNE] & BIT_OPT_0_FONT_NORMAL) == BIT_OPT_0_FONT_NORMAL) {
        _header_css(expt, level, nazov_css_normal_font_weight);
    }

	Export_to_file(expt, "\t<meta name=\"viewport\" content=\"width=device-width, user-scalable=yes, initial-scale=1.0\" />\n");
	Export_to_file(expt, "<title>%s</title>\n", title);
	Export_to_file(expt, "</head>\n\n");
	Log("element </head>...\n");

	Log("element <body>...\n");
	// 2011-05-05: pridanie font-family 
	// 2011-05-06: font sa neprid·va vûdy
	Export_to_file(expt, "<body");
	if((_global_font != FONT_CSS) || (_global_font_size != FONT_SIZE_CSS)){
		Export_to_file(expt, " style=\"");
		if(_global_font != FONT_CSS){
			Export_to_file(expt, "font-family: %s", _global_css_font_family);
		}
		if(_global_font_size != FONT_SIZE_CSS){
			if(_global_font != FONT_CSS){
				Export_to_file(expt, "; ");
			}
			Export_to_file(expt, "font-size: %s", _global_css_font_size);
		}
		Export_to_file(expt, "\"");
	}
	// 2010-02-15: kvÙli öpeci·lnemu "zoznam.htm"
	if(spec == 1){
		Export_to_file(expt, " onLoad=\"fn_aktualne(0,0,0)\"");
	}
	Export_to_file(expt, ">\n");

	Export_to_file(expt, HTML_ANAME_TOP"\n");

	// 2010-02-15: doplnenÈ predoöl· a nasledovn· modlitba
	if(_global_opt_batch_monthly == ANO && query_type != PRM_BATCH_MODE){
		Export_to_file(expt, "<center>\n");
		pismeno_modlitby = CHAR_MODL_NEURCENA;
		if((_local_modlitba < MODL_NEURCENA) && (_local_modlitba >= MODL_INVITATORIUM)){
			// 2013-07-29: generovanie n·zvu s˙boru s pÌsmenkom modlitby (default) alebo s ID modlitby
			if((_global_opt[OPT_4_OFFLINE_EXPORT] & BIT_OPT_4_FNAME_MODL_ID) != BIT_OPT_4_FNAME_MODL_ID){
				pismeno_modlitby = char_modlitby[_local_modlitba];
			}
			else{
				pismeno_modlitby = _local_modlitba + '0';
			}
		}
		sprintf(ext, "%c", pismeno_modlitby);
		strcat(ext, ".htm");
		Export_to_file(expt, HTML_NEW_PARAGRAPH);
		// << prev
		mystrcpy(file_name_pom, FILE_EXPORT, MAX_STR);
		ptr = strstr(file_name_pom, ext);
		if((_local_modlitba < MODL_NEURCENA) && (_local_modlitba > MODL_INVITATORIUM)){
			if(ptr != NULL){
				// 2013-07-29: generovanie n·zvu s˙boru s pÌsmenkom modlitby (default) alebo s ID modlitby
				if((_global_opt[OPT_4_OFFLINE_EXPORT] & BIT_OPT_4_FNAME_MODL_ID) != BIT_OPT_4_FNAME_MODL_ID){
					sprintf(pismeno_prev, "%c", char_modlitby[_local_modlitba - 1]);
				}
				else{
					sprintf(pismeno_prev, "%d", _local_modlitba - 1);
				}
				strncpy(ptr, pismeno_prev, 1);
			}
			Export_to_file(expt, "<a href=\"%s\" "HTML_CLASS_BUTTON">", file_name_pom);
			Export_to_file(expt, (char *)html_text_batch_Prev[_global_jazyk]);
			Export_to_file(expt, " ");
			Export_to_file(expt, (char *)nazov_modlitby(_local_modlitba - 1));
			Export_to_file(expt, "</a>");
		}
		// |
		Export_to_file(expt, " | ");
		// ^ hore
		Export_to_file(expt, "<a href=\".%s%s\" "HTML_CLASS_BUTTON">", STR_PATH_SEPARATOR_HTML, _global_export_navig_hore); // v tom istom adres·ri
		Export_to_file(expt, (char *)html_text_batch_Back[_global_jazyk]);
		Export_to_file(expt, "</a>");
		// |
		Export_to_file(expt, " | ");
		// >> next
		mystrcpy(file_name_pom, FILE_EXPORT, MAX_STR);
		ptr = strstr(file_name_pom, ext);
		if((_local_modlitba != MODL_NEURCENA) && (_local_modlitba < MODL_KOMPLETORIUM)){
			if(ptr != NULL){
				// 2013-07-29: generovanie n·zvu s˙boru s pÌsmenkom modlitby (default) alebo s ID modlitby
				if((_global_opt[OPT_4_OFFLINE_EXPORT] & BIT_OPT_4_FNAME_MODL_ID) != BIT_OPT_4_FNAME_MODL_ID){
					sprintf(pismeno_next, "%c", char_modlitby[_local_modlitba + 1]);
				}
				else{
					sprintf(pismeno_next, "%d", _local_modlitba + 1);
				}
				strncpy(ptr, pismeno_next, 1);
			}
			Export_to_file(expt, "<a href=\"%s\" "HTML_CLASS_BUTTON">", file_name_pom);
			Export_to_file(expt, (char *)nazov_modlitby(_local_modlitba + 1));
			Export_to_file(expt, " ");
			Export_to_file(expt, (char *)html_text_batch_Next[_global_jazyk]);
			Export_to_file(expt, "</a>");
		}
		Export_to_file(expt, "</p>");
		Export_to_file(expt, "</center>\n");
	}// << predoöl· | ^ hore | nasledovn· >>
	Log("_hlavicka() -- koniec.\n");
	return;
}// _hlavicka()

void hlavicka(char *title, short int level, short int spec){
	_hlavicka(title, NULL, level, spec);
}
void hlavicka(char *title, FILE * expt, short int level, short int spec){
	_hlavicka(title, expt, level, spec);
}

// exportuje hlavicku XML dokumentu

void _xml_hlavicka(FILE * expt){
	Log("_xml_hlavicka() -- zaËiatok...\n");
	if(bol_content_type_text_xml == NIE){
#if defined(OS_linux)
		Export_to_file(expt, "Content-type: text/xml\n");
		Export_to_file(expt, "\n");
#elif defined(OS_Windows_Ruby)
		Export_to_file(expt, "Content-type: text/xml\n");
		Export_to_file(expt, "\n");
#endif
		bol_content_type_text_xml = ANO;
	}
	Export_to_file(expt, (char *)xml_header, charset_jazyka[_global_jazyk]);
	Export_to_file(expt, ELEM_BEGIN(XML_MAIN)"\n");
	Log("_xml_hlavicka() -- koniec.\n");
	return;
}// _xml_hlavicka()

void xml_hlavicka(void){
	_xml_hlavicka(NULL);
}
void xml_hlavicka(FILE * expt){
	_xml_hlavicka(expt);
}

//const char *gpage[] = {"Generovan· str·nka", "Str·nky jsou generov·ny", "Generated page", "Generated"};
const char *gpage[POCET_JAZYKOV + 1] = {"GenerovanÈ: ", "Generov·no: ", "Generated: ", "Generated: ", "Generated: ", "Generov·no: ", "Gener·lva: "};
// GenerovanÈ + d·tum: "%d. %s %d, %02d:%02d:%02d" -- pÙvodne to bolo v z·tvork·ch
const char *datum_cas_template[POCET_JAZYKOV + 1] = {"%d. %s %d, %02d:%02d", "%d. %s %d, %02d:%02d", "%d. %s %d, %02d:%02d", "%d. %s %d, %02d:%02d", "%d. %s %d, %02d:%02d", "%d. %s %d, %02d:%02d", "%d. %s %d, %02d:%02d"};
// Build: "Build: %s. "
const char *build_template[POCET_JAZYKOV + 1] = {"<!--Verzia: %s -->", "<!--Verze: %s -->", "<!--Build: %s -->", "<!--Build: %s -->", "<!--Build: %s -->", "<!--Verze: %s -->", "<!--Build: %s -->"};
// GenerovanÈ + d·tum (bez Ëasu - pre batch mÛd, aby sa æahko porovn·vali vygenerovanÈ modlitby): "%d. %s %d"
const char *datum_template[POCET_JAZYKOV + 1] = {"%d. %s %d", "%d. %s %d", "%d. %s %d", "%d. %s %d", "%d. %s %d", "%d. %s %d", "%d. %s %d"};

const char *html_mail_label_long = "Juraj VidÈky";
const char *html_mail_label_short = "J. V.";

#define ROK 5

// exportuje patku HTML dokumentu (vysledok query)
void _patka(FILE * expt){
	char mail_addr[MAX_MAIL_STR] = "";
	Log("_patka() -- zaËiatok...\n");
	_local_modlitba = _global_modlitba;
	if((_local_modlitba == MODL_PRVE_VESPERY) || (_local_modlitba == MODL_DRUHE_VESPERY)){
		_local_modlitba = MODL_VESPERY;
	}
	if((_local_modlitba == MODL_PRVE_KOMPLETORIUM) || (_local_modlitba == MODL_DRUHE_KOMPLETORIUM)){
		_local_modlitba = MODL_KOMPLETORIUM;
	}

	// 2011-07-01: viackr·t sa pri exporte modlitby do HTML exportovala p‰tka; pridan· kontrola
	if(_global_patka_Export > 0)
		return;
	_global_patka_Export++;

	time_t t;
	struct tm dnes;
	int baserok = 1999;
	char rok[ROK];

	time(&t);

	// konvertuje date/time na strukturu
	dnes = *localtime(&t);
	// upravenie time_check structure with the data
	dnes.tm_year = dnes.tm_year + 1900;
	dnes.tm_yday = dnes.tm_yday + 1;
	mystrcpy(rok, STR_EMPTY, ROK);
	if(dnes.tm_year > baserok){
		sprintf(rok, "-%d", dnes.tm_year);
	}

	// 2010-02-15: vloûenÈ "^ hore" podæa hlavicka(); doplnenÈ predoöl· a nasledovn· modlitba
	if(_global_opt_batch_monthly == ANO && query_type != PRM_BATCH_MODE){
		Export_to_file(expt, "<center>\n");
		pismeno_modlitby = CHAR_MODL_NEURCENA;
		if((_local_modlitba < MODL_NEURCENA) && (_local_modlitba >= MODL_INVITATORIUM))
			pismeno_modlitby = char_modlitby[_local_modlitba];
		sprintf(ext, "%c", pismeno_modlitby);
		strcat(ext, ".htm");
		Export_to_file(expt, HTML_NEW_PARAGRAPH);
		// << prev
		mystrcpy(file_name_pom, FILE_EXPORT, MAX_STR);
		ptr = strstr(file_name_pom, ext);
		if((_local_modlitba < MODL_NEURCENA) && (_local_modlitba > MODL_INVITATORIUM)){
			if(ptr != NULL){
				sprintf(pismeno_prev, "%c", char_modlitby[_local_modlitba - 1]);
				strncpy(ptr, pismeno_prev, 1);
			}
			Export_to_file(expt, "<a href=\"%s\" "HTML_CLASS_BUTTON">", file_name_pom);
			Export_to_file(expt, (char *)html_text_batch_Prev[_global_jazyk]);
			Export_to_file(expt, " ");
			Export_to_file(expt, (char *)nazov_modlitby(_local_modlitba - 1));
			Export_to_file(expt, "</a>");
		}
		// |
		Export_to_file(expt, " | ");
		// ^ hore
		Export_to_file(expt, "<a href=\".%s%s\" "HTML_CLASS_BUTTON">", STR_PATH_SEPARATOR_HTML, _global_export_navig_hore); // v tom istom adres·ri
		Export_to_file(expt, (char *)html_text_batch_Back[_global_jazyk]);
		Export_to_file(expt, "</a>");
		// |
		Export_to_file(expt, " | ");
		// >> next
		mystrcpy(file_name_pom, FILE_EXPORT, MAX_STR);
		ptr = strstr(file_name_pom, ext);
		if((_local_modlitba != MODL_NEURCENA) && (_local_modlitba < MODL_KOMPLETORIUM)){
			if(ptr != NULL){
				sprintf(pismeno_next, "%c", char_modlitby[_local_modlitba + 1]);
				strncpy(ptr, pismeno_next, 1);
			}
			Export_to_file(expt, "<a href=\"%s\" "HTML_CLASS_BUTTON">", file_name_pom);
			Export_to_file(expt, (char *)nazov_modlitby(_local_modlitba + 1));
			Export_to_file(expt, " ");
			Export_to_file(expt, (char *)html_text_batch_Next[_global_jazyk]);
			Export_to_file(expt, "</a>");
		}
		Export_to_file(expt, "</p>");
		Export_to_file(expt, "</center>\n");
	}// << predoöl· | ^ hore | nasledovn· >>

	Export_to_file(expt, (char *)html_footer_1);

	if(_global_opt_batch_monthly == ANO && query_type != PRM_BATCH_MODE){
		mystrcpy(html_mail_label, html_mail_label_short, MAX_MAIL_LABEL);
	}
	else
	{
		mystrcpy(html_mail_label, html_mail_label_long, MAX_MAIL_LABEL);
	}

	Export("\n");
	// 2010-02-15: celÈ zapozn·mkovanÈ 
	// 2011-07-01: pre web sa exportuje
	Export_to_file(expt, "<"HTML_P_PATKA">\n");
#ifdef BEHAVIOUR_WEB
	if(_global_opt_batch_monthly == ANO && query_type != PRM_BATCH_MODE){
		Export_to_file(expt, "%s\n", gpage[_global_jazyk]);
		// Export_to_file(expt, "(%s). ", ctime(&t) + 4);
		// 2008-12-22: odvetvenÈ - pre commandline export (do s˙boru) sa netlaËÌ Ëasov· zloûka, kedy bolo HTML generovanÈ
#if defined(EXPORT_TO_FILE) && !defined(IO_ANDROID)
		Export_to_file(expt, (char *)datum_template[_global_jazyk],
			dnes.tm_mday,
			nazov_mesiaca(dnes.tm_mon), // nm[dnes.tm_mon]
			dnes.tm_year
			);
#else
		Export_to_file(expt, (char *)datum_cas_template[_global_jazyk],
			dnes.tm_mday,
			nazov_mesiaca(dnes.tm_mon), // nm[dnes.tm_mon]
			dnes.tm_year,
			dnes.tm_hour,
			dnes.tm_min
			// , dnes.tm_sec
			);
#endif
		Export_to_file(expt, ". ");
	}
	// nezabudni zmenit #define BUILD_DATE v mydefs.h (2003-07-15)
	Export_to_file(expt, (char *)build_template[_global_jazyk], BUILD_DATE);

	// Export_to_file(expt, "KÛdovanie Windows-1250 (Central European).\n"); // zapoznamkovane, 2003-06-30
	// Export_to_file(expt, HTML_LINE_BREAK"\n"); // commented, 2013-11-12
#endif

	// pridana stranka cfg_HTTP_ADDRESS_default, 12/04/2000A.D.
	Export_to_file(expt, "<"HTML_LINK_NORMAL" href=\"%s\" target=\"_top\">%s</a>\n", cfg_http_address_default[_global_jazyk], cfg_http_display_address_default[_global_jazyk]);
	Log("cfg_mail_address_default[%s] == %s\n", cfg_mail_address_default[_global_jazyk], skratka_jazyka[_global_jazyk]);
	mystrcpy(mail_addr, cfg_mail_address_default[_global_jazyk], MAX_MAIL_STR);
	Log("mail_addr == %s\n", mail_addr);
	Export_to_file(expt, "&#169; %d%s <"HTML_LINK_NORMAL" href=\"mailto:%s\">%s</a>\n", baserok, rok, mail_addr, html_mail_label);

	Export_to_file(expt, "</p>\n"); // pridane kvoli tomu, ze cele to bude <p class="patka">, 2003-07-02

	Export_to_file(expt, HTML_ANAME_BOTTOM"\n");

	Export_to_file(expt, "</body>\n</html>\n");
	Log("_patka() -- koniec.\n");
	return;
}// _patka()

void patka(void){
	_patka(NULL);
}
void patka(FILE * expt){
	_patka(expt);
}

// exportuje patku XML dokumentu
void _xml_patka(FILE * expt){
	Log("_xml_patka() -- zaËiatok...\n");

	// aby sa p‰tka neexportovala viackr·t
	if(_global_patka_Export > 0)
		return;
	_global_patka_Export++;

	time_t t;
	struct tm dnes;

	time(&t);

	// konvertuje date/time na strukturu
	dnes = *localtime(&t);
	// upravenie time_check structure with the data
	dnes.tm_year = dnes.tm_year + 1900;
	dnes.tm_yday = dnes.tm_yday + 1;

	Export_to_file(expt, ELEM_BEGIN(XML_INFO)"\n");
	Export_to_file(expt, ELEM_BEGIN(XML_COPYRIGHT)"%s"ELEM_END(XML_COPYRIGHT)"\n", TEXT_COPYRIGHT);
	Export_to_file(expt, ELEM_BEGIN(XML_ADDRESS)"%s"ELEM_END(XML_ADDRESS)"\n", TEXT_EMAIL);
	Export_to_file(expt, ELEM_BEGIN(XML_GENERATED)""HTML_ISO_FORMAT""ELEM_END(XML_GENERATED)"\n", dnes.tm_year, dnes.tm_mon + 1, dnes.tm_mday);
	Export_to_file(expt, ELEM_BEGIN(XML_BUILD_DATE)"%s"ELEM_END(XML_BUILD_DATE)"\n", BUILD_DATE);
	Export_to_file(expt, ELEM_END(XML_INFO)"\n\n");

	Export_to_file(expt, ELEM_END(XML_MAIN)"\n\n");

	Log("_xml_patka() -- koniec.\n");
	return;
}// _xml_patka()

void xml_patka(void){
	_xml_patka(NULL);
}
void xml_patka(FILE * expt){
	_xml_patka(expt);
}

#endif // __MYHPAGE_CPP_

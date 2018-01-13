/************************************************************************/
/*                                                                      */
/* myhpage.cpp                                                          */
/* (c)1999-2018 | Juraj Vidéky | videky@breviar.sk                      */
/*                                                                      */
/* description | HTML document dynamically generated header and footer  */
/*                                                                      */
/************************************************************************/

#include "vstudio.h"

#ifndef __MYHPAGE_CPP_
#define __MYHPAGE_CPP_

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "myconf.h"
#include "myhpage.h"
#include "mydefs.h"
#include "myexpt.h"
#include "mystring.h"
#include "mylog.h"
#include "breviar.h"
#include "liturgia.h"
#include "mybuild.h"

short int bol_content_type_text_html = NIE;
short int bol_content_type_text_xml = NIE;

#ifndef __MYHPAGE_CPP_HTML_CONST
#define __MYHPAGE_CPP_HTML_CONST

// obsahuje %s
const char *html_header_1 =
// Android KitKat nevie javascriptom zalamovat text, ak je specifikovany tento doctype.
#ifndef MODEL_android
//    "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"\n\t\"http://www.w3.org/TR/html4/loose.dtd\">\n"
//	"<!DOCTYPE html>\n"
    "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"\n\t\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n"
#endif
//    "<html>\n<head>\n\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=%s\">\n\t<meta name=\"Author\" content=\"Juraj Videky\">\n";
    "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=%s\" />\n\t<meta name=\"Author\" content=\"Juraj Videky\" />\n";
const char *html_header_css = "\t<link rel=\"stylesheet\" type=\"text/css\" href=\"";

const char *xml_header = "<?xml version=\"1.0\" encoding=\"%s\"?>\n\n";

const char *generated[POCET_JAZYKOV + 1] = { "Generované: ", "Generováno: ", "Generated: ", "Generated: ", "Generated: ", "Generováno: ", "Generálva: ", "ru_text", "by_text", /* STRING_1_FOR_NEW_LANGUAGE */ };

// Generované + dátum: "%d. %s %d, %02d:%02d:%02d" -- pôvodne to bolo v zátvorkách
const char *datum_cas_template[POCET_JAZYKOV + 1] = { "%d. %s %d, %02d:%02d", "%d. %s %d, %02d:%02d", "%d. %s %d, %02d:%02d", "%d. %s %d, %02d:%02d", "%d. %s %d, %02d:%02d", "%d. %s %d, %02d:%02d", "%d. %s %d, %02d:%02d", "%d. %s %d, %02d:%02d", "by_text", /* STRING_1_FOR_NEW_LANGUAGE */ };

// Build: "Build: %s. "
const char *build_template[POCET_JAZYKOV + 1] = { "<!--Verzia: %s -->", "<!--Verze: %s -->", "<!--Build: %s -->", "<!--Build: %s -->", "<!--Build: %s -->", "<!--Verze: %s -->", "<!--Build: %s -->", "<!--Build: %s -->", "by_text", /* STRING_1_FOR_NEW_LANGUAGE */ };

// Generované + dátum (bez času - pre batch mód, aby sa ľahko porovnávali vygenerované modlitby): "%d. %s %d"
const char *datum_template[POCET_JAZYKOV + 1] = { "%d. %s %d", "%d. %s %d", "%d. %s %d", "%d. %s %d", "%d. %s %d", "%d. %s %d", "%d. %s %d", "%d. %s %d", "by_text", /* STRING_1_FOR_NEW_LANGUAGE */ };

const char *HTML_MAIL_LABEL_LONG = "Juraj Vidéky";
const char *HTML_MAIL_LABEL_SHORT = "J. Vidéky";

#define STR_YEAR_LENGTH 10

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
	Export_to_file(expt, "/");
#endif
	Export_to_file(expt, "%s\" />\n", nazov_css_suboru);
}

// exportuje buttony pre predchádzajúcu a nasledujúcu modlitbu | bolo v _hlavicka() aj _patka()
void _buttons_prev_up_next(FILE * expt){
	short int _local_modlitba_prev, _local_modlitba_next;
	_local_modlitba_prev = modlitba_predchadzajuca(_local_modlitba, (isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_EXCLUDE_MCD_KOMPLET)));
	_local_modlitba_next = modlitba_nasledujuca(_local_modlitba, (isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_EXCLUDE_MCD_KOMPLET)));

	Export_to_file(expt, "\n<div class=\"nav\">");
	pismeno_modlitby = CHAR_MODL_NEURCENA;
	if ((_local_modlitba < MODL_NEURCENA) && (_local_modlitba >= MODL_INVITATORIUM)){
		if (!isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_FNAME_MODL_ID)){
			pismeno_modlitby = char_modlitby[_local_modlitba];
		}
		else{
			pismeno_modlitby = _local_modlitba + '0';
		}
	}
	sprintf(ext, "%c", pismeno_modlitby);
	strcat(ext, ".htm");
	Export_to_file(expt, HTML_P_BEGIN);
	// << prev
	mystrcpy(file_name_pom, FILE_EXPORT, MAX_STR);
	ptr = strstr(file_name_pom, ext);
	if ((_local_modlitba < MODL_NEURCENA) && (_local_modlitba > MODL_INVITATORIUM) && (_local_modlitba_prev < MODL_NEURCENA)){
		if (ptr != NULL){
			if (!isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_FNAME_MODL_ID)){
				sprintf(pismeno_prev, "%c", char_modlitby[_local_modlitba_prev]);
			}
			else{
				sprintf(pismeno_prev, "%d", _local_modlitba_prev);
			}
			strncpy(ptr, pismeno_prev, 1);
		}
		Export_to_file(expt, HTML_A_HREF_BEGIN "\"%s\"%s>", file_name_pom, optional_html_class_button);
		Export_to_file(expt, optional_html_button_begin);
		Export_to_file(expt, (char *)html_text_batch_Prev[_global_jazyk]);
		Export_to_file(expt, " ");
		Export_to_file(expt, (char *)nazov_modlitby(_local_modlitba_prev));
		Export_to_file(expt, optional_html_button_end);
		Export_to_file(expt, HTML_A_END);
		// |
		Export_to_file(expt, STR_VERTICAL_BAR_WITH_SPACES);
	}
	// ^ hore
	Export_to_file(expt, HTML_A_HREF_BEGIN "\".%s%s\"%s>", STR_PATH_SEPARATOR_HTML, _global_export_navig_hore, optional_html_class_button); // v tom istom adresári
	Export_to_file(expt, optional_html_button_begin);
	Export_to_file(expt, (char *)html_text_batch_Back[_global_jazyk]);
	Export_to_file(expt, optional_html_button_end);
	Export_to_file(expt, HTML_A_END);
	// >> next
	mystrcpy(file_name_pom, FILE_EXPORT, MAX_STR);
	ptr = strstr(file_name_pom, ext);
	if ((_local_modlitba != MODL_NEURCENA) && (_local_modlitba < MODL_KOMPLETORIUM) && (_local_modlitba_next < MODL_NEURCENA)){
		if (ptr != NULL){
			if (!isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_FNAME_MODL_ID)){
				sprintf(pismeno_next, "%c", char_modlitby[_local_modlitba_next]);
			}
			else{
				sprintf(pismeno_next, "%d", _local_modlitba_next);
			}
			strncpy(ptr, pismeno_next, 1);
		}
		// |
		Export_to_file(expt, STR_VERTICAL_BAR_WITH_SPACES);
		Export_to_file(expt, HTML_A_HREF_BEGIN "\"%s\"%s>", file_name_pom, optional_html_class_button);
		Export_to_file(expt, optional_html_button_begin);
		Export_to_file(expt, (char *)nazov_modlitby(_local_modlitba_next));
		Export_to_file(expt, " ");
		Export_to_file(expt, (char *)html_text_batch_Next[_global_jazyk]);
		Export_to_file(expt, optional_html_button_end);
		Export_to_file(expt, HTML_A_END);
	}
	Export_to_file(expt, HTML_P_END);
	Export_to_file(expt, HTML_DIV_END"\n");
}

// exportuje hlavicku HTML dokumentu, kam pojde vysledok query
void _hlavicka(char *title, FILE * expt, short int level, short int spec) {
	Log("_hlavicka() -- begin...\n");

	_local_modlitba = _global_modlitba;
	if ((_local_modlitba == MODL_PRVE_VESPERY) || (_local_modlitba == MODL_DRUHE_VESPERY)) {
		_local_modlitba = MODL_VESPERY;
	}
	if ((_local_modlitba == MODL_PRVE_KOMPLETORIUM) || (_local_modlitba == MODL_DRUHE_KOMPLETORIUM)) {
		_local_modlitba = MODL_KOMPLETORIUM;
	}

	if (_global_hlavicka_Export > 0) {
		Log("_hlavicka() -- _global_hlavicka_Export == %d > 0; end.\n", _global_hlavicka_Export);
		return;
	}
	_global_hlavicka_Export++;

	// iné CSS sú len "doplnky" (overrides) k hlavnému CSS
	if (_global_css != CSS_breviar_sk) {
		Log("first, export CSS filename: nazov_css_suboru == %s...\n", nazov_css[CSS_breviar_sk]);
	}
	const char *nazov_css_suboru;
	if (_global_css == CSS_UNDEF) {
		nazov_css_suboru = nazov_css[CSS_breviar_sk];
	}// _global_css == CSS_UNDEF
	else {
		nazov_css_suboru = nazov_css[_global_css];
	}// else
	Log("nazov_css_suboru == %s...\n", nazov_css_suboru);

	// nastavenie font-family
	// zatiaľ len pevné reťazce; časom možno bude premenná pre názov fontu
	// najprv sa testuje nastavenie _global_font; následne sa prípadne nastavia defaulty
	if ((_global_font == FONT_UNDEF) || (_global_font == FONT_CHECKBOX)) {
		Log("(_global_font == FONT_UNDEF) || (_global_font == FONT_CHECKBOX)...\n");
		if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_FONT_FAMILY)) {
			Log("_global_opt[OPT_2_HTML_EXPORT] & BIT_OPT_2_FONT_FAMILY...\n");
			mystrcpy(_global_css_font_family, DEFAULT_FONT_FAMILY_SANS_SERIF, SMALL);
		}
		else {
			Log("NOT _global_opt[OPT_2_HTML_EXPORT] & BIT_OPT_2_FONT_FAMILY...\n");
			mystrcpy(_global_css_font_family, DEFAULT_FONT_FAMILY_SERIF, SMALL);
		}
	}// (_global_font == FONT_UNDEF)  || (_global_font == FONT_CHECKBOX)
	else if (_global_font == FONT_CSS) {
		Log("_global_font == FONT_CSS...\n");
		mystrcpy(_global_css_font_family, DEFAULT_FONT_FAMILY_INHERIT, SMALL);
	}// (_global_font == FONT_CSS)
	else {
		Log("_global_font != FONT_CSS...\n");
		mystrcpy(_global_css_font_family, nazov_fontu[_global_font], SMALL);
	}// else
	Log("_global_css_font_family == %s...\n", _global_css_font_family);

	// nastavenie font-size
	if (_global_font_size == FONT_SIZE_UNDEF) {
		mystrcpy(_global_css_font_size, STR_EMPTY, SMALL);
	}// (_global_font_size == FONT_SIZE_UNDEF)
	else if (_global_font_size == FONT_SIZE_CSS) {
		mystrcpy(_global_css_font_size, DEFAULT_FONT_SIZE_INHERIT, SMALL);
	}// (_global_font_size == FONT_SIZE_CSS)
	else {
		mystrcpy(_global_css_font_size, nazov_font_size_css[_global_font_size], SMALL);
	}// else
	Log("_global_css_font_size == %s...\n", _global_css_font_size);

	if (bol_content_type_text_html == NIE) {
#if defined(BEHAVIOUR_WEB)
		Export_to_file(expt, "Content-type: text/html\n");
		Export_to_file(expt, "\n");
#endif
		bol_content_type_text_html = ANO;
	}
	Log("creating header...\n");

	Log("element <head>...\n");
	Export_to_file(expt, (char *)html_header_1, nazov_charset[charset_jazyka[_global_jazyk]]);

	// CSS (one or more)
	if (_global_css != CSS_breviar_sk) {
		_header_css(expt, level, nazov_css[CSS_breviar_sk]);
	}
	_header_css(expt, level, nazov_css_suboru);
	// CSS override night mode
	if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_NOCNY_REZIM)) {
		_header_css(expt, level, nazov_css_invert_colors);
	}
	// CSS override normal font (no bold)
	if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_FONT_NORMAL)) {
		_header_css(expt, level, nazov_css_normal_font_weight);
	}
	// blind-friendly CSS (no red text)
	if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_BLIND_FRIENDLY)) {
		_header_css(expt, level, nazov_css_blind_friendly);
	}

#if defined(IO_ANDROID)
	Export_to_file(expt, "\t<meta name=\"viewport\" content=\"width=device-width, user-scalable=no, initial-scale=1.0\" />\n");
#else
	Export_to_file(expt, "\t<meta name=\"viewport\" content=\"width=device-width, user-scalable=yes, initial-scale=1.0\" />\n");
#endif

	Log("element <title>...</title>...\n");
	Export_to_file(expt, "<title>%s</title>\n", title);

	Log("element </head>...\n");
	Export_to_file(expt, "</head>\n\n");

	Log("element <body>...\n");
	Export_to_file(expt, "<body");

	if ((_global_font != FONT_CSS) || (_global_font_size != FONT_SIZE_CSS) || (_global_style_margin != 0)) {
		Export_to_file(expt, " style=\"");
		if (_global_font != FONT_CSS) {
			Export_to_file(expt, "font-family: %s; ", _global_css_font_family);
		}
		if (_global_font_size != FONT_SIZE_CSS) {
			Export_to_file(expt, "font-size: %s; ", _global_css_font_size);
		}
		if (_global_style_margin != 0) {
			Export_to_file(expt, "margin-left: %dpx; margin-right: %dpx; ", _global_style_margin, _global_style_margin);
		}
		Export_to_file(expt, "\"");
	}

	// kvôli špeciálnemu "zoznam.htm"
	if (spec == 1) {
		Export_to_file(expt, " onLoad=\"fn_aktualne(0,0,0)\"");
	}
	Export_to_file(expt, ">\n");

	// display transparent navigation (up/down arrows)
	if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_TRANSPARENT_NAV)) {
		Export_to_file(expt, HTML_TRANSPARENT_NAV "\n");
	}

#ifdef BEHAVIOUR_WEB
	Export_to_file(expt, HTML_ANAME_TOP "\n");
#else
	Export_to_file(expt, HTML_DIV_BEGIN "\n");
#endif

	// predošlá a nasledovná modlitba
	if (_global_opt_batch_monthly == ANO && query_type != PRM_BATCH_MODE) {
		_buttons_prev_up_next(expt);
	}// << predošlá | ^ hore | nasledovná >>

	Log("_hlavicka() -- end.\n");
	return;
}// _hlavicka()

void hlavicka(char *title, short int level, short int spec) {
	_hlavicka(title, NULL, level, spec);
}

void hlavicka(char *title, FILE * expt, short int level, short int spec) {
	_hlavicka(title, expt, level, spec);
}

// exportuje hlavicku XML dokumentu
void _xml_hlavicka(FILE * expt) {
	Log("_xml_hlavicka() -- begin...\n");

	if (bol_content_type_text_xml == NIE) {
#if defined(OS_linux)
		Export_to_file(expt, "Content-type: text/xml\n");
		Export_to_file(expt, "\n");
#elif defined(OS_Windows_Ruby)
		Export_to_file(expt, "Content-type: text/xml\n");
		Export_to_file(expt, "\n");
#endif
		bol_content_type_text_xml = ANO;
	}

	Export_to_file(expt, (char *)xml_header, nazov_charset[charset_jazyka[_global_jazyk]]);
	Export_to_file(expt, ELEM_BEGIN(XML_MAIN) "\n");

	Log("_xml_hlavicka() -- end.\n");
	return;
}// _xml_hlavicka()

void xml_hlavicka(void) {
	_xml_hlavicka(NULL);
}

void xml_hlavicka(FILE * expt) {
	_xml_hlavicka(expt);
}

void _patka_body_html_end(FILE * expt) {
	Log("_patka_body_html_end() -- begin...\n");

#ifdef BEHAVIOUR_WEB
	Export_to_file(expt, HTML_ANAME_BOTTOM "\n");
#else
	Export_to_file(expt, HTML_DIV_END "\n");
#endif

#ifdef IO_ANDROID
	Export_to_file(expt, "<script src='/zoom.js'></script>\n");
#endif
	Export_to_file(expt, "</body>\n</html>\n");

	Log("_patka_body_html_end() -- end.\n");
}

// exportuje patku HTML dokumentu (vysledok query)
void _patka(FILE * expt) {
	char mail_addr[MAX_MAIL_STR] = "";
	Log("_patka() -- begin...\n");

	_local_modlitba = _global_modlitba;
	if ((_local_modlitba == MODL_PRVE_VESPERY) || (_local_modlitba == MODL_DRUHE_VESPERY)) {
		_local_modlitba = MODL_VESPERY;
	}
	if ((_local_modlitba == MODL_PRVE_KOMPLETORIUM) || (_local_modlitba == MODL_DRUHE_KOMPLETORIUM)) {
		_local_modlitba = MODL_KOMPLETORIUM;
	}

	// prepare year "to" from current timestamp as string with dash
	time_t t;
	struct tm dnes;
	int baserok = 1999;
	char rok[STR_YEAR_LENGTH];

	time(&t);

	// konvertuje date/time na strukturu
	dnes = *localtime(&t);
	// upravenie time_check structure with the data
	dnes.tm_year = dnes.tm_year + 1900;
	dnes.tm_yday = dnes.tm_yday + 1;
	mystrcpy(rok, STR_EMPTY, STR_YEAR_LENGTH);
	if (dnes.tm_year > baserok) {
		sprintf(rok, "-%d", dnes.tm_year);
	}

	// 2010-02-15: vložené "^ hore" podľa hlavicka(); doplnené predošlá a nasledovná modlitba
	if (_global_opt_batch_monthly == ANO && query_type != PRM_BATCH_MODE) {
		_buttons_prev_up_next(expt);
	}// << predošlá | ^ hore | nasledovná >>

	// prepare display name (label) for e-mail address
	if (_global_opt_batch_monthly == ANO && query_type != PRM_BATCH_MODE) {
		mystrcpy(html_mail_label, (char *)HTML_MAIL_LABEL_SHORT, MAX_MAIL_LABEL);
	}
	else
	{
		mystrcpy(html_mail_label, (char *)HTML_MAIL_LABEL_LONG, MAX_MAIL_LABEL);
	}

	Export("\n");

	Export_to_file(expt, "<" HTML_P_PATKA ">\n");

	// export build timestamp (not for mobile apps)
#if defined(BEHAVIOUR_WEB) && !(defined(IO_ANDROID) || defined(__APPLE__))
	if (_global_opt_batch_monthly == ANO && query_type != PRM_BATCH_MODE) {
		Export_to_file(expt, "%s\n", generated[_global_jazyk]);

		// print without or with timestamp
#if defined(EXPORT_TO_FILE)
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

		Export_to_file(expt, ". "); // final dot at the end of sentence (Generated...)
	}

	Export_to_file(expt, (char *)build_template[_global_jazyk], BUILD_DATE);
#endif

#ifndef BEHAVIOUR_CMDLINE
	// navigation to main page (URL breviar.sk) before (c) info
	Export_to_file(expt, "<" HTML_LINK_NORMAL " href=\"%s\" " HTML_TARGET_TOP ">%s" HTML_A_END "\n", cfg_http_address_default[_global_jazyk], cfg_http_display_address_default[_global_jazyk]);
#endif

	Log("cfg_mail_address_default[%d] (language: %s) == %s\n", _global_jazyk, skratka_jazyka[_global_jazyk], cfg_mail_address_default[_global_jazyk]);
	mystrcpy(mail_addr, cfg_mail_address_default[_global_jazyk], MAX_MAIL_STR);

	Log("mail_addr == %s\n", mail_addr);
	if (strlen(mail_addr) < 6) {
		mystrcpy(mail_addr, (char *)MAIL_ADDRESS_DEFAULT, MAX_MAIL_STR);
	}

	Log("mail_addr == %s\n", mail_addr);
	Export_to_file(expt, "&#169; %d%s <" HTML_LINK_NORMAL " href=\"mailto:%s\">%s" HTML_A_END "\n", baserok, rok, mail_addr, html_mail_label);

	Export_to_file(expt, HTML_P_END "\n");

	Log("_patka() -- end.\n");
	return;
}// _patka()

void patka(void) {
	Log("patka(void) -- begin...\n");

	// aby sa pätka neexportovala viackrát
	if (_global_patka_Export > 0) {
		Log("patka(void) -- _global_patka_Export == %d > 0; end.\n", _global_patka_Export);
		return;
	}
	_global_patka_Export++;

	if (!(isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_BLIND_FRIENDLY))) {
		_patka(NULL);
	}
	_patka_body_html_end(NULL);

	Log("patka(void) -- end.\n");
}

void patka(FILE * expt) {
	Log("patka(FILE) -- begin...\n");

	// aby sa pätka neexportovala viackrát
	if (_global_patka_Export > 0) {
		Log("patka(FILE) -- _global_patka_Export == %d > 0; end.\n", _global_patka_Export);
		return;
	}
	_global_patka_Export++;

	if (!(isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_BLIND_FRIENDLY))) {
		_patka(expt);
	}
	_patka_body_html_end(expt);

	Log("patka(FILE) -- end.\n");
}

// exportuje patku XML dokumentu
void _xml_patka(FILE * expt) {
	Log("_xml_patka() -- begin...\n");

	// aby sa pätka neexportovala viackrát
	if (_global_patka_Export > 0) {
		Log("_xml_patka() -- _global_patka_Export == %d > 0; end.\n", _global_patka_Export);
		return;
	}
	_global_patka_Export++;

	time_t t;
	struct tm dnes;

	time(&t);

	// konvertuje date/time na strukturu
	dnes = *localtime(&t);
	// upravenie time_check structure with the data
	dnes.tm_year = dnes.tm_year + 1900;
	dnes.tm_yday = dnes.tm_yday + 1;

	short int c;

	// element XML_SUPPORTED_LANGUAGES
	Export_to_file(expt, ELEM_BEGIN_NAME(XML_SUPPORTED_LANGUAGES) "\n", STR_JAZYK);

	for (c = 0; c <= POCET_JAZYKOV; c++) {
		if (supported_languages[c]) {
			Export_to_file(expt, ELEM_BEGIN_ID_VALUE(XML_LANGUAGE) "%s" ELEM_END(XML_LANGUAGE) "\n", c, skratka_jazyka[c], nazov_jazyka_native_jazyk(c));
		}
	}

	// end of element XML_SUPPORTED_LANGUAGES
	Export_to_file(expt, ELEM_END(XML_SUPPORTED_LANGUAGES) "\n\n");

	// element XML_SUPPORTED_VALUES with sub-elements
	Export_to_file(expt, ELEM_BEGIN(XML_SUPPORTED_VALUES) "\n");

	// sub-element XML_LIT_CALENDAR_VALUES
	Export_to_file(expt, ELEM_BEGIN_NAME(XML_LIT_CALENDAR_VALUES) "\n", STR_KALENDAR);
	
	for (c = 0; c < supported_calendars_count[_global_jazyk]; c++) {
		if (equalsi(skratka_kalendara[c], STR_EMPTY)) {
			Export_to_file(expt, ELEM_BEGIN_ID(XML_LIT_CALENDAR) "%s" ELEM_END(XML_LIT_CALENDAR) "\n", c, nazov_kalendara_vyber[supported_calendars(c)]);
		}
		else {
			Export_to_file(expt, ELEM_BEGIN_ID_VALUE(XML_LIT_CALENDAR) "%s" ELEM_END(XML_LIT_CALENDAR) "\n", c, skratka_kalendara[c], nazov_kalendara_vyber[supported_calendars(c)]);
		}
	}

	Export_to_file(expt, ELEM_END(XML_LIT_CALENDAR_VALUES) "\n\n");

	// sub-element XML_LIT_YEAR_LETTER_VALUES
	Export_to_file(expt, ELEM_BEGIN_NAME(XML_LIT_YEAR_LETTER_VALUES) "\n", STR_LIT_ROK);

	for (c = 0; c < POCET_NEDELNY_CYKLUS; c++) {
		Export_to_file(expt, ELEM_BEGIN_ID_CHARVALUE(XML_LIT_YEAR_LETTER) "%s" ELEM_END(XML_LIT_YEAR_LETTER) "\n", c, char_nedelny_cyklus[c], string_nedelny_cyklus[alphabet_jayzka[_global_jazyk]][c]);
	}

	Export_to_file(expt, ELEM_END(XML_LIT_YEAR_LETTER_VALUES) "\n\n");

	// sub-element XML_LIT_SEASON_VALUES
	Export_to_file(expt, ELEM_BEGIN_NAME(XML_LIT_SEASON_VALUES) "\n", STR_LIT_OBD);

	for (c = 0; c <= POCET_OBDOBI; c++) {
		Export_to_file(expt, ELEM_BEGIN_ID_VALUE(XML_LIT_SEASON) "%s" ELEM_END(XML_LIT_SEASON) "\n", c, nazov_obdobia_ext(c), nazov_obdobia(c));
	}

	Export_to_file(expt, ELEM_END(XML_LIT_SEASON_VALUES) "\n\n");

	// sub-element XML_LIT_COMMUNIA_VALUES
	Export_to_file(expt, ELEM_BEGIN_NAME(XML_LIT_COMMUNIA_VALUES) "\n", STR_FORCE_OPT_3);

	for (c = 0; c <= POCET_SPOL_CASTI; c++) {
		Export_to_file(expt, ELEM_BEGIN_ID(XML_LIT_COMMUNIA) "%s" ELEM_END(XML_LIT_COMMUNIA) "\n", c, nazov_spolc(c));
	}

	Export_to_file(expt, ELEM_END(XML_LIT_COMMUNIA_VALUES) "\n\n");

	// sub-element XML_LIT_TYPE_VALUES
	Export_to_file(expt, ELEM_BEGIN(XML_LIT_TYPE_VALUES) "\n");

	for (c = 0; c <= POCET_SLAVENI; c++) {
		Export_to_file(expt, ELEM_BEGIN_ID(XML_LIT_TYPE) "%s" ELEM_END(XML_LIT_TYPE) "\n", c, nazov_slavenia(c));
	}

	Export_to_file(expt, ELEM_END(XML_LIT_TYPE_VALUES) "\n\n");

	// sub-element XML_LIT_COLOR_VALUES
	Export_to_file(expt, ELEM_BEGIN(XML_LIT_COLOR_VALUES) "\n");

	for (c = 1; c <= POCET_FARIEB_REALNYCH; c++) {
		// do not export color "0" = N/A
		Export_to_file(expt, ELEM_BEGIN_ID(XML_LIT_COLOR) "%s" ELEM_END(XML_LIT_COLOR) "\n", c, nazov_farby(c));
	}

	Export_to_file(expt, ELEM_END(XML_LIT_COLOR_VALUES) "\n\n");

	// end of element XML_SUPPORTED_VALUES
	Export_to_file(expt, ELEM_END(XML_SUPPORTED_VALUES) "\n\n");

	// element XML_INFO with sub-elements
	Export_to_file(expt, ELEM_BEGIN(XML_INFO) "\n");

	Export_to_file(expt, ELEM_BEGIN(XML_COPYRIGHT) "%s" ELEM_END(XML_COPYRIGHT) "\n", TEXT_COPYRIGHT);
	Export_to_file(expt, ELEM_BEGIN(XML_ADDRESS) "%s" ELEM_END(XML_ADDRESS) "\n", TEXT_EMAIL);
	Export_to_file(expt, ELEM_BEGIN(XML_GENERATED) "" HTML_ISO_FORMAT "" ELEM_END(XML_GENERATED) "\n", dnes.tm_year, dnes.tm_mon + 1, dnes.tm_mday);
	Export_to_file(expt, ELEM_BEGIN(XML_BUILD_DATE) "%s" ELEM_END(XML_BUILD_DATE) "\n", BUILD_DATE);

	Export_to_file(expt, ELEM_END(XML_INFO) "\n\n");

	Export_to_file(expt, ELEM_END(XML_MAIN) "\n\n");

	Log("_xml_patka() -- end.\n");
	return;
}// _xml_patka()

void xml_patka(void) {
	_xml_patka(NULL);
}

void xml_patka(FILE * expt) {
	_xml_patka(expt);
}

#endif // __MYHPAGE_CPP_

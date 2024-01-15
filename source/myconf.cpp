/*********************************************************/
/*                                                       */
/* myconf.cpp                                            */
/* (c)1999-2024 | Juraj Vidéky | videky@breviar.sk       */
/*                                                       */
/* description | interface to config file CONFIG_FILE    */
/*                                                       */
/*********************************************************/

#include "vstudio.h"

#ifndef __MYCONF_CPP_
#define __MYCONF_CPP_

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "myconf.h"
#include "mystring.h"
#include "mylog.h"
#include "mydefs.h"
#include "mystring.h"
#include "liturgia.h"

#undef LOG_READCONFIG
#define LOG_CONFIG

#if defined(LOG_CONFIG) && defined(LOGGING)
#define LogConfig Log
#else
#define LogConfig emptyLog
#endif

short int local_run_once = 0; // avoid update sidemenu items mre than once

char cfg_HTTP_ADDRESS_default[MAX_HTTP_STR] = "/";
char cfg_HTTP_DISPLAY_ADDRESS_default[MAX_HTTP_STR] = "breviar.sk";
char cfg_MAIL_ADDRESS_default[MAX_MAIL_STR] = "videky@breviar.sk";
char cfg_HTTP_BIBLE_COM_REFERENCES_default[MAX_HTTP_STR] = "https://www.bible.com/bible/";

#if !defined(IO_ANDROID)
#define INCLUDE_PATH_PREFIX   "../"
#else
#define INCLUDE_PATH_PREFIX   ""
#endif

char cfg_INCLUDE_DIR_default[MAX_INCD_STR] = INCLUDE_PATH_PREFIX "include/";

unsigned long long cfg_option_default[POCET_GLOBAL_OPT][POCET_JAZYKOV + 1];

char cfg_http_address_default[POCET_JAZYKOV + 1][MAX_HTTP_STR];
char cfg_http_display_address_default[POCET_JAZYKOV + 1][MAX_HTTP_STR];
char cfg_mail_address_default[POCET_JAZYKOV + 1][MAX_MAIL_STR];
char cfg_http_bible_references_default[POCET_JAZYKOV + 1][MAX_HTTP_STR];
char cfg_http_bible_com_references_default[POCET_JAZYKOV + 1][MAX_HTTP_STR];
char cfg_bible_com_version_id_default[POCET_JAZYKOV + 1][MAX_SMALL_STR];

char cfg_sidemenu_item[POCET_SIDEMENU_ITEMS][POCET_JAZYKOV + 1][MAX_VALUE_LENGTH];
char cfg_sidemenu_item_link[POCET_SIDEMENU_ITEMS][POCET_JAZYKOV + 1][MAX_VALUE_LENGTH];

const char* cfg_option_prefix[POCET_GLOBAL_OPT + POCET_DALSICH_CONF] =
{ "specialne", "casti_modlitby", "html_export", "", "offline_export", "alternatives", "alternatives_multi", 
  "http_adresa", "http_zobraz_adr", "mail_adresa", "http_bible_references", "http_bible_com_references", "bible_com_version_id" };
#define ODDELOVAC_CFG_OPTION_PREFIX_POSTFIX "_"

const char* cfg_sidemenu_items_prefix[POCET_SIDEMENU_ITEMS] =
{ "sidemenu_item_top", "sidemenu_item_docs", "sidemenu_item_info", "sidemenu_item_download", "sidemenu_item_about" };

const char* cfg_sidemenu_items_link_prefix[POCET_SIDEMENU_ITEMS] =
{ "sidemenu_item_link_top", "sidemenu_item_link_docs", "sidemenu_item_link_info", "sidemenu_item_link_download", "sidemenu_item_link_about" };

const char* cfg_option_postfix[POCET_JAZYKOV + 1] =
{ "def", "cz", "en", "la", "", "czop", "hu", "ru", "by", "is", /* STRING_1_FOR_NEW_LANGUAGE */ };

void printConfigOptions(void) {
#ifdef LOG_CONFIG
	short int j = 0, o = 0;
	for(j = 0; j <= POCET_JAZYKOV; j++) {
		LogConfig("=== Jazyk `%s' (%s): Default hodnoty option parametrov (konfiguračný súbor %s) ===\n", skratka_jazyka[j], nazov_jazyka(j), CONFIG_FILE);
		for(o = 0; o < POCET_GLOBAL_OPT + POCET_DALSICH_CONF; o++) {
			if (o < POCET_GLOBAL_OPT) {
				LogConfig("cfg_option_default[%d][%d] == `%llu'\n", o, j, cfg_option_default[o][j]);
			}
			else {
				switch(o - POCET_GLOBAL_OPT) {
					case 0: LogConfig("http address: %s\n", cfg_http_address_default[j]); break;
					case 1: LogConfig("http display address: %s\n", cfg_http_display_address_default[j]); break;
					case 2: LogConfig("mail address: %s\n", cfg_mail_address_default[j]); break;
					case 3: LogConfig("http bible references: %s\n", cfg_http_bible_references_default[j]); break;
					case 4: LogConfig("http bible.com references: %s\n", cfg_http_bible_com_references_default[j]); break;
					case 5: LogConfig("bible.com version id: %s\n", cfg_bible_com_version_id_default[j]); break;
				} // switch()
			}
		}// for o
		// config for sidemenu items
		for (o = 0; o < POCET_SIDEMENU_ITEMS; o++) {
			LogConfig("cfg_sidemenu_item[%d][%d] == `%s'\n", o, j, cfg_sidemenu_item[o][j]);
			LogConfig("cfg_sidemenu_item_link[%d][%d] == `%s'\n", o, j, cfg_sidemenu_item_link[o][j]);
		}// for o
	}// for j
#endif
}// printConfigOptions()

void setConfigDefaultsOther(short int j) {
	Log("setConfigDefaultsOther(%d): begin...", j);

	if (j > POCET_JAZYKOV) {
		return;
	}

	LogConfig("=== Jazyk `%s' (%s):\n", skratka_jazyka[j], nazov_jazyka(j));

	LogConfig("http address: %s\n", cfg_http_address_default[j]);
	if (equals(cfg_http_address_default[j], STR_EMPTY)) {
		strcpy(cfg_http_address_default[j], cfg_HTTP_ADDRESS_default);
		LogConfig("value CHANGED: %s\n", cfg_http_address_default[j]);
	}

	LogConfig("http display address: %s\n", cfg_http_display_address_default[j]);
	if (equals(cfg_http_display_address_default[j], STR_EMPTY)) {
		strcpy(cfg_http_display_address_default[j], cfg_HTTP_DISPLAY_ADDRESS_default);
		LogConfig("value CHANGED: %s\n", cfg_http_display_address_default[j]);
	}

	LogConfig("mail address: %s\n", cfg_mail_address_default[j]);
	if (equals(cfg_mail_address_default[j], STR_EMPTY)) {
		strcpy(cfg_mail_address_default[j], cfg_MAIL_ADDRESS_default);
		LogConfig("value CHANGED: %s\n", cfg_mail_address_default[j]);
	}

	LogConfig("http bible references: %s\n", cfg_http_bible_references_default[j]);
	if (equals(cfg_http_bible_references_default[j], STR_EMPTY)) {
		strcpy(cfg_http_bible_references_default[j], bible_references_default[j]);
		LogConfig("value CHANGED: %s\n", cfg_http_bible_references_default[j]);
	}

	LogConfig("http bible.com references: %s\n", cfg_http_bible_com_references_default[j]);
	if (equals(cfg_http_bible_com_references_default[j], STR_EMPTY)) {
		strcpy(cfg_http_bible_com_references_default[j], cfg_HTTP_BIBLE_COM_REFERENCES_default);
		LogConfig("value CHANGED: %s\n", cfg_http_bible_com_references_default[j]);
	}

	LogConfig("bible.com version id: %s\n", cfg_bible_com_version_id_default[j]);
	if (equals(cfg_bible_com_version_id_default[j], STR_EMPTY)) {
		strcpy(cfg_bible_com_version_id_default[j], bible_version_id_default[j]);
		LogConfig("value CHANGED: %s\n", cfg_bible_com_version_id_default[j]);
	}

	Log("setConfigDefaultsOther(%d): end.", j);
}// setConfigDefaultsOther()

void setConfigDefaultsSideMenu(short int j) {
	Log("setConfigDefaultsSideMenu(%d): begin...", j);

	char pom[MAX_VALUE_LENGTH];

	if (j > POCET_JAZYKOV) {
		return;
	}

	LogConfig("=== Jazyk `%s' (%s):\n", skratka_jazyka[j], nazov_jazyka(j));

	// no need for defaults for sidemenu items -- they MUST BE defined without defaults

	Log("local_run_once == %d...\n", local_run_once);

	if (local_run_once <= 1) {
		// config for sidemenu items links: if empty, take from default language (due to slashes, skipping for SK)
		if (j != JAZYK_SK) {
			for (short int o = 0; o < POCET_SIDEMENU_ITEMS; o++) {
				mystrcpy(pom, cfg_sidemenu_item_link[o][j], MAX_VALUE_LENGTH);
				LogConfig("cfg_sidemenu_item_link[%d][%d] == `%s'\n", o, j, cfg_sidemenu_item_link[o][j]);
				if (equals(cfg_sidemenu_item_link[o][j], STR_EMPTY)) {
					strcpy(pom, cfg_sidemenu_item_link[o][JAZYK_SK]);
					LogConfig("value CHANGED: %s\n", cfg_sidemenu_item_link[o][j]);

					sprintf(cfg_sidemenu_item_link[o][j], "%s%s", cfg_http_address_default[j], pom);
					LogConfig("value UPDATED: %s\n", cfg_sidemenu_item_link[o][j]);
				}
			}// for o
		}// not for SK; will be fixed later in updateConfigDefaultsMenuDefault()
	}

	Log("setConfigDefaultsSideMenu(%d): end.", j);
}// setConfigDefaultsSideMenu()

void updateConfigDefaultsMenuDefault() {
	Log("updateConfigDefaultsMenuDefault(): begin...");

	char pom[MAX_VALUE_LENGTH];

	Log("local_run_once == %d...\n", local_run_once);

	// adding cfg_http_address_default for SK sidemenu items links

	for (short int o = 0; o < POCET_SIDEMENU_ITEMS; o++) {
		mystrcpy(pom, cfg_sidemenu_item_link[o][JAZYK_SK], MAX_VALUE_LENGTH);
		sprintf(cfg_sidemenu_item_link[o][JAZYK_SK], "%s%s", cfg_http_address_default[JAZYK_SK], pom);
		LogConfig("value UPDATED: %s\n", cfg_sidemenu_item_link[o][JAZYK_SK]);
	}// for o

	Log("updateConfigDefaultsMenuDefault(): end.");
}// updateConfigDefaultsMenuDefault()

void readConfig(void)
{
	FILE* subor = NULL;
	char option[MAX_OPTION_LENGTH];
	char hodnota[MAX_VALUE_LENGTH];
	int znak = '\0';
	short int i = 0, j = 0, o = 0;
	char nazov_option[MAX_STR];

	Log("readConfig() -- začiatok...\n");
	LogConfig("============================ súbor `%s' ============================\n", CONFIG_FILE);

	LogConfig("Naplním všetky defaulty hodnotou GLOBAL_OPTION_NULL.\n");
	for(o = 0; o < POCET_GLOBAL_OPT; o++) {
		for(j = 0; j <= POCET_JAZYKOV; j++) {
			cfg_option_default[o][j] = GLOBAL_OPTION_NULL;
		}// for j
	}// for o

	if (! (subor = fopen(CONFIG_FILE, "r")) ) {
		LogConfig("Nemôžem otvoriť súbor `%s'.\n", CONFIG_FILE);
#ifdef MODEL_LH_commandline
		LogConfig("Pokúsim sa nájsť ho o level vyššie...\n");
		if (! (subor = fopen(".." STR_PATH_SEPARATOR "" CONFIG_FILE, "r")) ) {
			LogConfig("Nemôžem otvoriť súbor `%s'.\n", ".." STR_PATH_SEPARATOR "" CONFIG_FILE);
			return;
		}
		else {
			LogConfig("Súbor `%s' otvorený.\n", ".." STR_PATH_SEPARATOR "" CONFIG_FILE);
		}
#else
		return;
#endif
	}
	else {
		LogConfig("Súbor `%s' otvorený.\n", CONFIG_FILE);
	}

	for (; (znak = fgetc(subor)) != EOF;)
	{
		if (znak == '#') {
#ifdef LOG_READCONFIG
			LogConfig("Parsujem poznámku...\n");
#endif
			while((znak = fgetc(subor)) != EOF && (znak != '\n') ); // parsuj poznámku do konca riadka
			if (znak == EOF) { 
				LogConfig("EOF... break.\n");
				break; 
			}
			continue;
		}

		if (isspace(znak)) {
			continue;
		}

		mystrcpy(option, STR_EMPTY, MAX_OPTION_LENGTH);
		// načíta maximálne MAX_OPTION_LENGTH znakov (mínus medzery, ktoré ignoruje)
		for(i = 0; (znak != EOF) && (znak != '\n') && (znak != '=') && (i < (MAX_OPTION_LENGTH - 1)); znak = fgetc(subor), ++i)
		{
#ifdef LOG_READCONFIG
			LogConfig("znak == `%c'\n", znak);
#endif
			if (znak == CHAR_SPACE) // v prípade medzery preskoč, čítaj ďalej
				// aby tu mohlo byť znak = fgetc(subor); je potrebné, aby sme skontrolovali, či nie sme na konci
				i--;
			else {
#ifdef  _READCONFIG
				LogConfig("i == %d\n", i);
#endif
				option[i] = znak;
			}
		}
		option[i] = '\0';

		if (znak != '=') {continue;}
		if (znak == EOF) {
			LogConfig("EOF... break.\n");
			break;
		}

		if ((znak = fgetc(subor)) == '"') {
			znak = fgetc(subor);
		}
		else if (znak == EOF) {
			LogConfig("EOF... break.\n");
			break;
		}

		mystrcpy(hodnota, STR_EMPTY, MAX_VALUE_LENGTH);
		// načíta maximálne MAX_OPTION_LENGTH znakov (mínus medzery, ktoré ignoruje)
		for(i = 0; (znak != EOF) && (znak != '\n') && (znak != '"') && (i < (MAX_HTTP_STR - 1)); znak = fgetc(subor), ++i)
		{
#ifdef LOG_READCONFIG
			LogConfig("znak == `%c'\n", znak);
#endif
			if (znak == CHAR_SPACE) // v prípade medzery preskoč, čítaj ďalej
				// aby tu mohlo byť znak = fgetc(subor); je potrebné, aby sme skontrolovali, či nie sme na konci
				i--;
			else {
#ifdef LOG_READCONFIG
				LogConfig("i == %d\n", i);
#endif
				hodnota[i] = znak;
			}
		}
		hodnota[i] = '\0';

#ifdef LOG_CONFIG
		LogConfig("Parsovaná option  == `%s'\n", option);
		LogConfig("Parsovaná hodnota == `%s'\n", hodnota);
#endif
/*		if (!strcmp(option, "http_adresa_def")) {
			strncpy(cfg_HTTP_ADDRESS_default, hodnota, MAX_HTTP_STR);
		}
		else if (!strcmp(option, "http_zobraz_adr_def")) {
			strcpy(cfg_HTTP_DISPLAY_ADDRESS_default, hodnota);
		}
		else if (!strcmp(option, "mail_adresa_def")) {
			strcpy(cfg_MAIL_ADDRESS_default, hodnota);
		}
*/
		if (!strcmp(option, "incldir_def")) {
			strcpy(cfg_INCLUDE_DIR_default, hodnota);
		}
		else {
			// global options + config options
			for(o = 0; o < POCET_GLOBAL_OPT + POCET_DALSICH_CONF; o++) {
				for(j = 0; j <= POCET_JAZYKOV; j++) {
					if (!equals(cfg_option_prefix[o], STR_EMPTY) && !equals(cfg_option_postfix[j], STR_EMPTY)) {
						// vyskladaj názov option pre jazyk j a option o (natvrdo definované možnosti)
						mystrcpy(nazov_option, cfg_option_prefix[o], MAX_STR);
						strcat(nazov_option, ODDELOVAC_CFG_OPTION_PREFIX_POSTFIX);
						strcat(nazov_option, cfg_option_postfix[j]);
						if (!strcmp(option, nazov_option)) {
							if (o < POCET_GLOBAL_OPT) {
								if (!strcmp(option, nazov_option)) {
									if (isdigit(hodnota[0])) {
										cfg_option_default[o][j] = atoui64(hodnota);
									}
								}// if (!strcmp(option, nazov_option))
							}// if -- štandardná option
							else {
								switch(o - POCET_GLOBAL_OPT) {
									case 0: mystrcpy(cfg_http_address_default[j], hodnota, MAX_HTTP_STR); break;
									case 1: mystrcpy(cfg_http_display_address_default[j], hodnota, MAX_HTTP_STR); break;
									case 2: mystrcpy(cfg_mail_address_default[j], hodnota, MAX_MAIL_STR); break;
									case 3: mystrcpy(cfg_http_bible_references_default[j], hodnota, MAX_HTTP_STR); break;
									case 4: mystrcpy(cfg_http_bible_com_references_default[j], hodnota, MAX_HTTP_STR); break;
									case 5: mystrcpy(cfg_bible_com_version_id_default[j], hodnota, MAX_SMALL_STR); break;
								} // switch()
							}// else -- natvrdo definovaná option
						}// if (!strcmp(option, nazov_option))
					}// if
				}// for j
			}// for o
			// config for sidemenu items + links
			for (o = 0; o < POCET_SIDEMENU_ITEMS; o++) {
				for (j = 0; j <= POCET_JAZYKOV; j++) {
					if (!equals(cfg_sidemenu_items_prefix[o], STR_EMPTY) && !equals(cfg_option_postfix[j], STR_EMPTY)) {
						// vyskladaj názov sidemenu item pre jazyk j a item o (natvrdo definované možnosti)
						mystrcpy(nazov_option, cfg_sidemenu_items_prefix[o], MAX_STR);
						strcat(nazov_option, ODDELOVAC_CFG_OPTION_PREFIX_POSTFIX);
						strcat(nazov_option, cfg_option_postfix[j]);
						if (!strcmp(option, nazov_option)) {
							mystrcpy(cfg_sidemenu_item[o][j], hodnota, MAX_VALUE_LENGTH);
							LogConfig("sidemenu item: %d == `%s`...\n", o, cfg_sidemenu_item[o][j]);
						}// if (!strcmp(option, nazov_option))
					}// if
					if (!equals(cfg_sidemenu_items_link_prefix[o], STR_EMPTY) && !equals(cfg_option_postfix[j], STR_EMPTY)) {
						// vyskladaj názov sidemenu item pre jazyk j a item o (natvrdo definované možnosti)
						mystrcpy(nazov_option, cfg_sidemenu_items_link_prefix[o], MAX_STR);
						strcat(nazov_option, ODDELOVAC_CFG_OPTION_PREFIX_POSTFIX);
						strcat(nazov_option, cfg_option_postfix[j]);
						if (!strcmp(option, nazov_option)) {
							mystrcpy(cfg_sidemenu_item_link[o][j], hodnota, MAX_VALUE_LENGTH);
							LogConfig("sidemenu item: %d == `%s`...\n", o, cfg_sidemenu_item_link[o][j]);
						}// if (!strcmp(option, nazov_option))
					}// if
				}// for j
			}// for o
		}
		for(; (znak != EOF) && (znak != '\n'); znak = fgetc(subor) );

		if (znak == EOF) {
			LogConfig("EOF... break.\n");
			break;
		}
	}
	fclose(subor);

	LogConfig("============================ súbor `%s' ============================\n", CONFIG_FILE);

	if (equalsi(cfg_MAIL_ADDRESS_default, STR_EMPTY)) {
		mystrcpy(cfg_MAIL_ADDRESS_default, MAIL_ADDRESS_DEFAULT, MAX_MAIL_STR);
	}
	LogConfig("cfg_MAIL_ADDRESS_default == %s\n", cfg_MAIL_ADDRESS_default);

	local_run_once++;

	Log("local_run_once == %d...\n", local_run_once);

	for (j = 0; j <= POCET_JAZYKOV; j++) {
		setConfigDefaultsOther(j);
		setConfigDefaultsSideMenu(j);
	}

	if (local_run_once <= 1) {
		updateConfigDefaultsMenuDefault();
	}

	// pôvodne pre Ruby || Android, teraz pre všetky platformy, upravené defaulty pre zobrazovanie
	LogConfig("defaults update (originally only for Ruby || Android)...\n");
	for(j = 0; j <= POCET_JAZYKOV; j++) {
		if (cfg_option_default[OPT_2_HTML_EXPORT][j] != GLOBAL_OPTION_NULL) {
			LogConfig("=== Jazyk `%s' (%s):\n", skratka_jazyka[j], nazov_jazyka(j));

			// nastavenie parametrov OPT_2_HTML_EXPORT: pridáme bity pre nastavenie
			if ((cfg_option_default[OPT_2_HTML_EXPORT][j] & BIT_OPT_2_NAVIGATION) != BIT_OPT_2_NAVIGATION) {
				LogConfig("Pre option %d nastavujem bit pre '%llu'\n", OPT_2_HTML_EXPORT, BIT_OPT_2_NAVIGATION);
				cfg_option_default[OPT_2_HTML_EXPORT][j] += BIT_OPT_2_NAVIGATION;
			}
			if ((cfg_option_default[OPT_2_HTML_EXPORT][j] & BIT_OPT_2_BUTTONY_USPORNE) != BIT_OPT_2_BUTTONY_USPORNE) {
				LogConfig("Pre option %d nastavujem bit pre '%llu'\n", OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTONY_USPORNE);
				cfg_option_default[OPT_2_HTML_EXPORT][j] += BIT_OPT_2_BUTTONY_USPORNE;
			}
			if ((cfg_option_default[OPT_2_HTML_EXPORT][j] & BIT_OPT_2_ROZNE_MOZNOSTI) != BIT_OPT_2_ROZNE_MOZNOSTI) {
				LogConfig("Pre option %d nastavujem bit pre '%llu'\n", OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI);
				cfg_option_default[OPT_2_HTML_EXPORT][j] += BIT_OPT_2_ROZNE_MOZNOSTI;
			}
			/*
			// 2017-09-12, JUV: commented
			if ((cfg_option_default[OPT_2_HTML_EXPORT][j] & BIT_OPT_2_HIDE_NAVIG_BUTTONS) != BIT_OPT_2_HIDE_NAVIG_BUTTONS) {
				LogConfig("Pre option %d nastavujem bit pre '%llu'\n", OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_NAVIG_BUTTONS);
				cfg_option_default[OPT_2_HTML_EXPORT][j] += BIT_OPT_2_HIDE_NAVIG_BUTTONS;
			}
			if ((cfg_option_default[OPT_2_HTML_EXPORT][j] & BIT_OPT_2_HIDE_KALENDAR) != BIT_OPT_2_HIDE_KALENDAR) {
				LogConfig("Pre option %d nastavujem bit pre '%llu'\n", OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_KALENDAR);
				cfg_option_default[OPT_2_HTML_EXPORT][j] += BIT_OPT_2_HIDE_KALENDAR;
			}
			*/
			if ((cfg_option_default[OPT_2_HTML_EXPORT][j] & BIT_OPT_2_HIDE_OPTIONS1) != BIT_OPT_2_HIDE_OPTIONS1) {
				LogConfig("Pre option %d nastavujem bit pre '%llu'\n", OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_OPTIONS1);
				cfg_option_default[OPT_2_HTML_EXPORT][j] += BIT_OPT_2_HIDE_OPTIONS1;
			}
			if ((cfg_option_default[OPT_2_HTML_EXPORT][j] & BIT_OPT_2_HIDE_OPTIONS2) != BIT_OPT_2_HIDE_OPTIONS2) {
				LogConfig("Pre option %d nastavujem bit pre '%llu'\n", OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_OPTIONS2);
				cfg_option_default[OPT_2_HTML_EXPORT][j] += BIT_OPT_2_HIDE_OPTIONS2;
			}
			if ((cfg_option_default[OPT_2_HTML_EXPORT][j] & BIT_OPT_2_ALTERNATIVES) != BIT_OPT_2_ALTERNATIVES) {
				LogConfig("Pre option %d nastavujem bit pre '%llu'\n", OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES);
				cfg_option_default[OPT_2_HTML_EXPORT][j] += BIT_OPT_2_ALTERNATIVES;
			}
		}
		else {
			LogConfig("=== Jazyk `%s' (%s): option je %d\n", skratka_jazyka[j], nazov_jazyka(j), GLOBAL_OPTION_NULL);
		}
	}// for j

	Log("readConfig() -- koniec.\n");

	return;
}// readConfig()

void printConfig(void) {
#ifdef LOG_CONFIG
	LogConfig("\n");
	LogConfig("=== BEGIN:configuration (%s) ===\n", CONFIG_FILE);

	// 2004-03-17 pridane cfg_INCLUDE_DIR_default
	LogConfig("cfg_INCLUDE_DIR_default == `%s'\n", cfg_INCLUDE_DIR_default);
	// 2007-06-01: nasleduju nové parametre
	printConfigOptions();
	LogConfig("=== END:configuration (%s) ===\n", CONFIG_FILE);
	LogConfig("\n");
#else
	Log("printConfig(): LOG_CONFIG is undefined, no LogConfig() printed...\n");
#endif
}// printConfig()

#endif // __MYCONF_CPP_


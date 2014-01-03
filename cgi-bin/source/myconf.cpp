/******************************************************************/
/*                                                                */
/* myconf.cpp                                                     */
/* (c)1999-2014 | Juraj Vidéky | videky@breviar.sk                */
/*                                                                */
/*                                                                */
/* description | poskytuje rozhranie na konfiguraciu,             */
/*               subor CONFIG_FILE                                */
/* document history                                               */
/*   30/03/2000A.D. | created                                     */
/*   06/09/2001A.D. | tento popis                                 */
/*   2003-07-08a.D. | MAIL_ADDRESS zmenena na videky@breviar.sk   */
/*   2003-08-13a.D. | pridany #include "mystring.h"               */
/*   2004-03-17a.D. | pridany INCLUDE_DIR                         */
/*   2006-07-13a.D. | prve kroky k jazykovym mutaciam             */
/*   2007-05-24a.D. | Marek Elias (MEL): pouzitie libconfuse      */
/*   2007-06-01a.D. | prepracovanie konfigurovatelnych premennych */
/*   2007-06-19a.D. | odstránené použitie libconfuse (MEL, JUV)   */
/*                                                                */
/*                                                                */
/******************************************************************/

#undef LOG_READCONFIG

#include "vstudio.h"

#ifndef __MYCONF_CPP_
#define __MYCONF_CPP_

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "myconf.h"
#include "mystring.h"
#include "mysystem.h"
#include "mysysdef.h"
#include "mylog.h"
#include "mydefs.h"
#include "mystring.h"
#include "liturgia.h"

#define MAIL_ADDRESS_DEFAULT "videky@breviar.sk"

char cfg_HTTP_ADDRESS_default[MAX_HTTP_STR] = "http://breviar.sk/";
char cfg_HTTP_DISPLAY_ADDRESS_default[MAX_HTTP_STR] = "http://breviar.sk/";
char cfg_MAIL_ADDRESS_default[MAX_MAIL_STR] = STR_EMPTY;
char cfg_INCLUDE_DIR_default[MAX_INCD_STR] = "../include/";

short int cfg_option_default[POCET_GLOBAL_OPT][POCET_JAZYKOV + 1];

char cfg_http_address_default[POCET_JAZYKOV + 1][MAX_HTTP_STR];
char cfg_http_display_address_default[POCET_JAZYKOV + 1][MAX_HTTP_STR];
char cfg_mail_address_default[POCET_JAZYKOV + 1][MAX_MAIL_STR];

const char *cfg_option_prefix[POCET_GLOBAL_OPT + POCET_DALSICH_CONF] = 
{"specialne", "casti_modlitby", "html_export", "", "offline_export", "alternatives", "http_adresa", "http_zobraz_adr", "mail_adresa"};
#define ODDELOVAC_CFG_OPTION_PREFIX_POSTFIX "_"
const char *cfg_option_postfix[POCET_JAZYKOV + 1] = 
{"def", "cz", "en", "la", "", "czop", "hu"};

void printConfigOptions(void){
	short int j = 0, o = 0;
	for(j = 0; j <= POCET_JAZYKOV; j++){
		Log("=== Jazyk `%s' (%s): Default hodnoty option parametrov (konfiguraèný súbor %s) ===\n", skratka_jazyka[j], nazov_jazyka[j], CONFIG_FILE);
		for(o = 0; o < POCET_GLOBAL_OPT + POCET_DALSICH_CONF; o++){
			if(o < POCET_GLOBAL_OPT){
				Log("cfg_option_default[%d][%d] == `%d'\n", o, j, cfg_option_default[o][j]);
			}
			else{
				switch(o - POCET_GLOBAL_OPT){
					case 0: Log("http address: %s\n", cfg_http_address_default[j]); break;
					case 1: Log("http display address: %s\n", cfg_http_display_address_default[j]); break;
					case 2: Log("mail address: %s\n", cfg_mail_address_default[j]); break;
				}// switch()
			}
		}// for o
	}// for j
}// printConfigOptions()

void readConfig(void)
{
	FILE* subor = NULL;
	char option[MAX_OPTION_LENGTH];
	char hodnota[MAX_VALUE_LENGTH];
	int znak = '\0';
	short int i = 0, j = 0, o = 0;
	char nazov_option[MAX_STR];

	Log("readConfig() -- zaèiatok...\n");
	Log("============================ súbor `%s' ============================\n", CONFIG_FILE);

	Log("Naplním všetky defaulty hodnotou GLOBAL_OPTION_NULL.\n");
	for(o = 0; o < POCET_GLOBAL_OPT; o++){
		for(j = 0; j <= POCET_JAZYKOV; j++){
			cfg_option_default[o][j] = GLOBAL_OPTION_NULL;
		}// for j
	}// for o

	if(! (subor = fopen(CONFIG_FILE, "r")) ){
		Log("Nemôžem otvori súbor `%s'.\n", CONFIG_FILE);
		return;
	}
	else{
		Log("Súbor `%s' otvorený.\n", CONFIG_FILE);
	}

	for (; (znak = fgetc(subor)) != EOF;)
	{
		if (znak == '#'){
#ifdef LOG_READCONFIG
			Log("Parsujem poznámku...\n");
#endif
			while((znak = fgetc(subor)) != EOF && (znak != '\n') ); // parsuj poznámku do konca riadka
			if(znak == EOF){ 
				Log("EOF... break.\n");
				break; 
			}
			continue;
		}

		if (isspace(znak)){
			continue;
		}

		mystrcpy(option, STR_EMPTY, MAX_OPTION_LENGTH);
		// naèíta maximálne MAX_OPTION_LENGTH znakov (mínus medzery, ktoré ignoruje)
		for(i = 0; (znak != EOF) && (znak != '\n') && (znak != '=') && (i < (MAX_OPTION_LENGTH - 1)); znak = fgetc(subor), ++i)
		{
#ifdef LOG_READCONFIG
			Log("znak == `%c'\n", znak);
#endif
			if(znak == ' ') // v prípade medzery preskoè, èítaj ïalej
				// aby tu mohlo by znak = fgetc(subor); je potrebné, aby sme skontrolovali, èi nie sme na konci
				i--;
			else{
#ifdef LOG_READCONFIG
				Log("i == %d\n", i);
#endif
				option[i] = znak;
			}
		}
		option[i] = '\0';

		if (znak != '='){continue;}
		if (znak == EOF){
			Log("EOF... break.\n");
			break;
		}

		if ((znak = fgetc(subor)) == '"'){
			znak = fgetc(subor);
		}
		else if(znak == EOF){
			Log("EOF... break.\n");
			break;
		}

		mystrcpy(hodnota, STR_EMPTY, MAX_VALUE_LENGTH);
		// naèíta maximálne MAX_OPTION_LENGTH znakov (mínus medzery, ktoré ignoruje)
		for(i = 0; (znak != EOF) && (znak != '\n') && (znak != '"') && (i < (MAX_HTTP_STR - 1)); znak = fgetc(subor), ++i)
		{
#ifdef LOG_READCONFIG
			Log("znak == `%c'\n", znak);
#endif
			if(znak == ' ') // v prípade medzery preskoè, èítaj ïalej
				// aby tu mohlo by znak = fgetc(subor); je potrebné, aby sme skontrolovali, èi nie sme na konci
				i--;
			else{
#ifdef LOG_READCONFIG
				Log("i == %d\n", i);
#endif
				hodnota[i] = znak;
			}
		}
		hodnota[i] = '\0';

		Log("Parsovaná option  == `%s'\n", option);
		Log("Parsovaná hodnota == `%s'\n", hodnota);
/*		if (!strcmp(option, "http_adresa_def")){
			strncpy(cfg_HTTP_ADDRESS_default, hodnota, MAX_HTTP_STR);
		}
		else if (!strcmp(option, "http_zobraz_adr_def")){
			strcpy(cfg_HTTP_DISPLAY_ADDRESS_default, hodnota);
		}
		else if (!strcmp(option, "mail_adresa_def")){
			strcpy(cfg_MAIL_ADDRESS_default, hodnota);
		}
*/
		if (!strcmp(option, "incldir_def")){
			strcpy(cfg_INCLUDE_DIR_default, hodnota);
		}
		else{
			for(o = 0; o < POCET_GLOBAL_OPT + POCET_DALSICH_CONF; o++){
				for(j = 0; j <= POCET_JAZYKOV; j++){
					if(!equals(cfg_option_prefix[o], STR_EMPTY) && !equals(cfg_option_postfix[j], STR_EMPTY)){
						// vyskladaj názov option pre jazyk j a option o (natvrdo definované možnosti)
						mystrcpy(nazov_option, cfg_option_prefix[o], MAX_STR);
						strcat(nazov_option, ODDELOVAC_CFG_OPTION_PREFIX_POSTFIX);
						strcat(nazov_option, cfg_option_postfix[j]);
						if(!strcmp(option, nazov_option)){
							if(o < POCET_GLOBAL_OPT){
								if(!strcmp(option, nazov_option)){
									if(isdigit(hodnota[0])){
										cfg_option_default[o][j] = atoi(hodnota);
									}
								}// if(!strcmp(option, nazov_option))
							}// if -- štandardná option
							else{
								switch(o - POCET_GLOBAL_OPT){
									case 0: mystrcpy(cfg_http_address_default[j], hodnota, MAX_HTTP_STR); break;
									case 1: mystrcpy(cfg_http_display_address_default[j], hodnota, MAX_HTTP_STR); break;
									case 2: mystrcpy(cfg_mail_address_default[j], hodnota, MAX_MAIL_STR); break;
								}// switch()
							}// else -- natvrdo definovaná option
						}// if(!strcmp(option, nazov_option))
					}// if
				}// for j
			}// for o
		}
		for(; (znak != EOF) && (znak != '\n'); znak = fgetc(subor) );

		if(znak == EOF){
			Log("EOF... break.\n");
			break;
		}

	}
	fclose(subor);

	Log("============================ súbor `%s' ============================\n", CONFIG_FILE);
	if(equalsi(cfg_MAIL_ADDRESS_default, STR_EMPTY)){
		mystrcpy(cfg_MAIL_ADDRESS_default, MAIL_ADDRESS_DEFAULT, MAX_MAIL_STR);
	}
	Log("cfg_MAIL_ADDRESS_default == %s\n", cfg_MAIL_ADDRESS_default);
	for(j = 0; j <= POCET_JAZYKOV; j++){
		Log("=== Jazyk `%s' (%s):\n", skratka_jazyka[j], nazov_jazyka[j]);
		Log("http address: %s\n", cfg_http_address_default[j]);
		if(equals(cfg_http_address_default[j], STR_EMPTY)){
			strcpy(cfg_http_address_default[j], cfg_HTTP_ADDRESS_default);
			Log("http address CHANGED: %s\n", cfg_http_address_default[j]);
		}
		Log("http display address: %s\n", cfg_http_display_address_default[j]);
		if(equals(cfg_http_display_address_default[j], STR_EMPTY)){
			strcpy(cfg_http_display_address_default[j], cfg_HTTP_DISPLAY_ADDRESS_default);
			Log("http display address CHANGED: %s\n", cfg_http_display_address_default[j]);
		}
		Log("mail address: %s\n", cfg_mail_address_default[j]);
		if(equals(cfg_mail_address_default[j], STR_EMPTY)){
			strcpy(cfg_mail_address_default[j], cfg_MAIL_ADDRESS_default);
			Log("mail address CHANGED: %s\n", cfg_mail_address_default[j]);
		}
	}

#if defined(OS_Windows_Ruby) || defined(IO_ANDROID)
	// 2012-10-03: pre android upravené defaulty pre zobrazovanie
	Log("android...\n");
	for(j = 0; j <= POCET_JAZYKOV; j++){
		if(cfg_option_default[OPT_2_HTML_EXPORT][j] != GLOBAL_OPTION_NULL){
			Log("=== Jazyk `%s' (%s):\n", skratka_jazyka[j], nazov_jazyka[j]);
			// nastavenie parametrov OPT_2_HTML_EXPORT: pridáme bity pre nastavenie
			if((cfg_option_default[OPT_2_HTML_EXPORT][j] & BIT_OPT_2_NAVIGATION) != BIT_OPT_2_NAVIGATION){
				Log("Pre option %d nastavujem bit pre '%d'\n", OPT_2_HTML_EXPORT, BIT_OPT_2_NAVIGATION);
				cfg_option_default[OPT_2_HTML_EXPORT][j] += BIT_OPT_2_NAVIGATION;
			}
			if((cfg_option_default[OPT_2_HTML_EXPORT][j] & BIT_OPT_2_BUTTONY_USPORNE) != BIT_OPT_2_BUTTONY_USPORNE){
				Log("Pre option %d nastavujem bit pre '%d'\n", OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTONY_USPORNE);
				cfg_option_default[OPT_2_HTML_EXPORT][j] += BIT_OPT_2_BUTTONY_USPORNE;
			}
			if((cfg_option_default[OPT_2_HTML_EXPORT][j] & BIT_OPT_2_ROZNE_MOZNOSTI) != BIT_OPT_2_ROZNE_MOZNOSTI){
				Log("Pre option %d nastavujem bit pre '%d'\n", OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI);
				cfg_option_default[OPT_2_HTML_EXPORT][j] += BIT_OPT_2_ROZNE_MOZNOSTI;
			}
			if((cfg_option_default[OPT_2_HTML_EXPORT][j] & BIT_OPT_2_HIDE_NAVIG_BUTTONS) != BIT_OPT_2_HIDE_NAVIG_BUTTONS){
				Log("Pre option %d nastavujem bit pre '%d'\n", OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_NAVIG_BUTTONS);
				cfg_option_default[OPT_2_HTML_EXPORT][j] += BIT_OPT_2_HIDE_NAVIG_BUTTONS;
			}
			if((cfg_option_default[OPT_2_HTML_EXPORT][j] & BIT_OPT_2_HIDE_KALENDAR) != BIT_OPT_2_HIDE_KALENDAR){
				Log("Pre option %d nastavujem bit pre '%d'\n", OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_KALENDAR);
				cfg_option_default[OPT_2_HTML_EXPORT][j] += BIT_OPT_2_HIDE_KALENDAR;
			}
			if((cfg_option_default[OPT_2_HTML_EXPORT][j] & BIT_OPT_2_HIDE_OPTIONS1) != BIT_OPT_2_HIDE_OPTIONS1){
				Log("Pre option %d nastavujem bit pre '%d'\n", OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_OPTIONS1);
				cfg_option_default[OPT_2_HTML_EXPORT][j] += BIT_OPT_2_HIDE_OPTIONS1;
			}
			if((cfg_option_default[OPT_2_HTML_EXPORT][j] & BIT_OPT_2_HIDE_OPTIONS2) != BIT_OPT_2_HIDE_OPTIONS2){
				Log("Pre option %d nastavujem bit pre '%d'\n", OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_OPTIONS2);
				cfg_option_default[OPT_2_HTML_EXPORT][j] += BIT_OPT_2_HIDE_OPTIONS2;
			}
			if((cfg_option_default[OPT_2_HTML_EXPORT][j] & BIT_OPT_2_ALTERNATIVES) != BIT_OPT_2_ALTERNATIVES){
				Log("Pre option %d nastavujem bit pre '%d'\n", OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES);
				cfg_option_default[OPT_2_HTML_EXPORT][j] += BIT_OPT_2_ALTERNATIVES;
			}
		}
		else{
			Log("=== Jazyk `%s' (%s): option je %d\n", skratka_jazyka[j], nazov_jazyka[j], GLOBAL_OPTION_NULL);
		}
	}// for j
#endif
	Log("readConfig() -- koniec.\n");

	return;
}// readConfig()

// 2007-06-01: keïže pribúda mnoho konfiguraèných parametrov, treba funkciu na ich výpis
void printConfig(void){
	Log("\n");
	Log("=== BEGIN:configuration (%s) ===\n", CONFIG_FILE);

	// 2004-03-17 pridane cfg_INCLUDE_DIR_default
	Log("cfg_INCLUDE_DIR_default == `%s'\n", cfg_INCLUDE_DIR_default);
	// 2007-06-01: nasleduju nové parametre
	printConfigOptions();
	Log("=== END:configuration (%s) ===\n", CONFIG_FILE);
	Log("\n");
}// printConfig()

#endif // __MYCONF_CPP_


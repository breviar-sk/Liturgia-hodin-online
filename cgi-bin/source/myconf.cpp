/******************************************************************/
/*                                                                */
/* myconf.cpp                                                     */
/* (c)1999-2012 | Juraj Videky | videky@breviar.sk                */
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
#define MAIL_ADDRESS_DEFAULT_HU "videky-hu@breviar.sk"

char cfg_HTTP_ADDRESS_default[MAX_HTTP_STR] = "http://www.breviar.sk/";
char cfg_HTTP_DISPLAY_ADDRESS_default[MAX_HTTP_STR] = "http://www.breviar.sk/";
char cfg_MAIL_ADDRESS_default[MAX_MAIL_STR] = STR_EMPTY;
char cfg_MAIL_ADDRESS_default_HU[MAX_MAIL_STR] = STR_EMPTY;
char cfg_INCLUDE_DIR_default[MAX_INCD_STR] = "../include/";

short int cfg_option_default[POCET_GLOBAL_OPT][POCET_JAZYKOV + 1];

const char *cfg_option_prefix[POCET_GLOBAL_OPT] = 
{"specialne", "casti_modlitby", "html_export", "", "offline_export"};
#define ODDELOVAC_CFG_OPTION_PREFIX_POSTFIX "_"
const char *cfg_option_postfix[POCET_JAZYKOV + 1] = 
{"def", "cz", "en", "la", "", "czop", "hu"};

void printConfigOptions(void){
	short int j = 0, o = 0;
	for(j = 0; j <= POCET_JAZYKOV; j++){
		Log("=== Jazyk `%s' (%s): Default hodnoty option parametrov (konfiguraèný súbor %s) ===\n", skratka_jazyka[j], nazov_jazyka[j], CONFIG_FILE);
		for(o = 0; o < POCET_GLOBAL_OPT; o++){
			Log("cfg_option_default[%d][%d] == `%d'\n", o, j, cfg_option_default[o][j]);
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
		if (!strcmp(option, "http_adresa_def")){
			strncpy(cfg_HTTP_ADDRESS_default, hodnota, MAX_HTTP_STR);
		}
		else if (!strcmp(option, "http_zobraz_adr_def")){
			strcpy(cfg_HTTP_DISPLAY_ADDRESS_default, hodnota);
		}
		else if (!strcmp(option, "mail_adresa_def")){
			strcpy(cfg_MAIL_ADDRESS_default, hodnota);
		}
		else if (!strcmp(option, "incldir_def")){
			strcpy(cfg_INCLUDE_DIR_default, hodnota);
		}
		else {
			for(o = 0; o < POCET_GLOBAL_OPT; o++){
				for(j = 0; j <= POCET_JAZYKOV; j++){
					if(!equals(cfg_option_prefix[o], STR_EMPTY) && !equals(cfg_option_postfix[j], STR_EMPTY)){
						// vyskladaj názov option pre jazyk j a option o
						mystrcpy(nazov_option, cfg_option_prefix[o], MAX_STR);
						strcat(nazov_option, ODDELOVAC_CFG_OPTION_PREFIX_POSTFIX);
						strcat(nazov_option, cfg_option_postfix[j]);
						if(!strcmp(option, nazov_option)){
							if(isdigit(hodnota[0])){
								cfg_option_default[o][j] = atoi(hodnota);
							}
						}/* if(!strcmp(option, nazov_option)) */
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
	mystrcpy(cfg_MAIL_ADDRESS_default_HU, MAIL_ADDRESS_DEFAULT_HU, MAX_MAIL_STR);
	Log("cfg_MAIL_ADDRESS_default_HU == %s\n", cfg_MAIL_ADDRESS_default_HU);

	Log("readConfig() -- koniec.\n");

	return;
}// readConfig()

// 2007-06-01: kedze pribuda mnoho konfiguracnych parametrov, je uzitocne spravit funkciu na ich vypis
void printConfig(void){
	Log("\n");
	Log("=== BEGIN:configuration (%s) ===\n", CONFIG_FILE);

	// 2007-06-01: niekolko prvych parametrov: prevzate z breviar.cpp::main()
	Log("cfg_HTTP_ADDRESS_default == `%s'\n", cfg_HTTP_ADDRESS_default);
	Log("cfg_HTTP_DISPLAY_ADDRESS_default == `%s'\n", cfg_HTTP_DISPLAY_ADDRESS_default); // 2007-05-24, JUV: pridane
	Log("cfg_MAIL_ADDRESS_default == `%s'\n", cfg_MAIL_ADDRESS_default);
	// 2004-03-17 pridane cfg_INCLUDE_DIR_default
	Log("cfg_INCLUDE_DIR_default == `%s'\n", cfg_INCLUDE_DIR_default);
	// 2007-06-01: nasleduju nové parametre
	printConfigOptions();
	Log("=== END:configuration (%s) ===\n", CONFIG_FILE);
	Log("\n");
}// printConfig()

#endif /* __MYCONF_CPP_ */


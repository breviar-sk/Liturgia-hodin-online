/***************************************************************************/
/*                                                                         */
/* breviar.cpp                                                             */
/* (c)1999-2024 | Juraj Vidéky | videky@breviar.sk                         */
/*                                                                         */
/*                http://www.breviar.sk                                    */
/*                                                                         */
/* description | master source code containing main() :-)                  */
/*             | most of description available in comments and Git log     */
/*                                                                         */
/* notes |  how to compile & link & build                                  */
/*          -- do not forget to update #define BUILD_DATE in mydefs.h      */
/*                                                                         */
/* DOS & Windows: Project (Solution) for MS Visual Studio contains all     */
/* .cpp and .h files                                                       */
/*                                                                         */
/* linux & other platforms: file `urob' (plays function of makefile)       */
/* ------------------------(begin of file `urob')
date
chmod u=rwx *.*
g++ -Wall -W breviar.cpp dbzaltar.cpp liturgia.cpp mygetopt.cpp mylog.cpp myhpage.cpp myexpt.cpp cgiutils.cpp myconf.cpp mydefs.cpp mystring.cpp citania.cpp utf8-utils.cpp
mv a.out l.cgi
chmod u=rw *.cpp
chmod u=rw *.h
chmod oa+x *.cgi
gzip -c -v l.cgi > l.cgi.gz
date
 * ------------------------(end of file `urob')                           */
/*                                                                         */
/*   * unfinished parts: marked by ToDo or [ToDo]                          */
/*                                                                         */
/***************************************************************************/

/*
Debugging in Visual Studio: 
Debug > breviar Properties, or, in Solution Explorer, right click on your project and choose "Properties" from the drop down menu.
Then, go to: Configuration Properties > Debugging
You can pass command line arguments in on the line titled by Command Arguments
   
Examples:
-i..\..\breviar.sk\include\ -qpsqs -s"qt=pdnes"
-qpbm -d1 -m1 -r2000 -f2 -g2 -p2001 -ba.txt
-i..\..\breviar.sk\include\ -qpsqs -s"qt=pcr&dvt=pondelok&t=2&p=mpc"
-qpdt -d30 -m4 -r2002 -pmrch -ic:\temp\breviar\ -emoja.htm
-qpsqs -s"qt=pdt&d=26&m=5&r=2010&p=mrch&ds=1"
-s"of5vnv=0&of5hpo=0&of0bf=0&ds=0&of1t=0&of5psps=0&of2tw=0&of2nr=0&of1vkp=0&of1sp=0&of0fn=1&of0tkne=0&of5ps29=0&of0zjvne=0&of1v=0&of5vnpc=0&of1pr=1&of5ps71=0&of1prz=1&of1o=0&of1zspc=1&of0r=0&d=12&of1spspc=0&of5hpred=0&of5ps69=0&of1dps=0&j=sk&k=sk&of1ps3=0&qt=pdt&of2id=0&of5vnhrch=0&of1z95=0&m=10&of5hk=0&o0=65&p=mpc&of5czh=1&o1=5440&of0nanne=0&of5hna=0&r=2015&of1c=0&o2=16384&of1r=0&of0cit=0&of2btnu=1&o3=0&of3=1&of5h1v=0&of2nav=0&of5hpc=1&o4=0&o5=0&of2a=1&of1s=0&of0v=0" -i"D:\personal\breviar\breviar.sk\include"

2017-11-08 value:
-s"qt=pdt&d=15&m=7&r=2016&p=mrch&ds=1&o0=2691&o1=202048&o2=25274&o3=5&o4=0&o5=2" -i"D:\personal\breviar\breviar.sk\include"
*/

#include "vstudio.h"

#ifndef __BREVIAR_CPP_
#define __BREVIAR_CPP_

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "mystring.h"
#include "myconf.h"
#include "mysystem.h"
#include "mysysdef.h"

#include "hodin.h"
#include "liturgia.h"
#include "cgiutils.h"
#include "mygetopt.h"
#include "utf8-utils.h"
#include "dbzaltar.h"
#include "mydefs.h"
#include "mylog.h"
#include "myexpt.h"
#include "myhpage.h"
#include "mybuild.h"

short int isAndroid = NIE;

#ifdef IO_ANDROID
#include "android.h"
#endif // IO_ANDROID

#ifdef LITURGICKE_CITANIA_ANDROID
#include "citania.h"
#endif // LITURGICKE_CITANIA_ANDROID

#undef LOG_UNCGI

#if defined(LOG_UNCGI) && defined(LOGGING)
#define LogUncgi Log
#else
#define LogUncgi emptyLog
#endif

// full logging for parameters manipulation
#if defined(DEBUG)
#define LOG_PARAMS
#else
#undef LOG_PARAMS
#endif

#if defined(LOG_PARAMS) && defined(LOGGING)
#define LogParams Log
#else
#define LogParams emptyLog
#endif

char *_global_buf;
char *_global_buf2;

#define ishex(x) (((x) >= '0' && (x) <= '9') || ((x) >= 'a' && (x) <= 'f') || ((x) >= 'A' && (x) <= 'F'))

#define READ_BUFFER 4096

#define ANCHOR_VYSVETLIVKY "VYSVETLIVKY"
#define FILE_VYSVETLIVKY "vysvetl.htm"

#define ANCHOR_VYSVETLIVKY_TABULKA "VYSVETL_TABULKA"
#define FILE_VYSVETLIVKY_TABULKA "vysvetlt.htm"

#define LOG_ciara Log("_____________________________________________________________\n");

#define FILE_LOG "breviar-log.log"

#define _main_LOG_to_Export Log
#define _main_LOG Log

// #ifndef OS_linux
#include "breviar.h"
// #endif

#ifdef IO_ANDROID
#define STDIN_FILE stdin_pipe
#else
#define STDIN_FILE stdin
#endif

#undef _BREVIAR_ENV

#if defined(__APPLE__)
#ifndef LIBC_BIONIC

#define ENV_K_SIZE 64
#define ENV_V_SIZE 256
#define ENV_ENTRIES 128

struct _breviar_env_entry {
    char k[ENV_K_SIZE];
    char v[ENV_V_SIZE];
};
static struct _breviar_env_entry _breviar_env[ENV_ENTRIES];
#define _BREVIAR_ENV

// Overwrite getenv() and putenv() for two reasons:
//
// 1. It causes crashes if breviar_main() is called multiple times: unlike
// setenv(), the argument of putenv() is not copied (at least not on BSD), so
// getenv() is likely to crash after the buffers are freed / reused.
//
// 2. We don't want to save the environment varibles between subsequent
// breviar_main() calls as this would cause unexpected behavior.
//
// Android libc (bionic) has no such problems, putenv copies the values as
// well. On the other hand, setenv seems to be not working properly there, so
// we disable this logic for android.
static int _breviar_putenv(char* s) {
	char* key = strdup(s);
	int i;

	if (!key) {
		return -1;
	}

	char* val = strchr(key, '=');
	if (!val) {
		free(key);
		return -1;
	}
	*(val++) = 0;

	if (strlen(key) >= ENV_K_SIZE) {
		Log("Too long key in _breviar_putenv(): '%s'\n", key);
		free(key);
		return -1;
	}
	if (strlen(val) >= ENV_V_SIZE) {
		Log("Too long value in _breviar_putenv(): '%s'\n", val);
		free(key);
		return -1;
	}

	for (i = 0; i < ENV_ENTRIES; i++) {
		if (_breviar_env[i].k[0] == 0 || strcmp(_breviar_env[i].k, key) == 0) {
			strcpy(_breviar_env[i].k, key);
			strcpy(_breviar_env[i].v, val);
			break;
		}
	}

	free(key);

	if (i == ENV_ENTRIES) {
		Log("Cannot add key '%s' to environment: env is full\n", key);
		return -1;
	}

	return 0;
}

static char* _breviar_getenv(const char* k) {
	int i;
	if (strlen(k) >= ENV_K_SIZE) {
		Log("Environment key too long: '%s'\n", k);
		return NULL;
	}

	for (i = 0; i < ENV_ENTRIES && _breviar_env[i].k[0]; i++) {
		if (strcmp(k, _breviar_env[i].k) == 0) {
			return _breviar_env[i].v;
		}
	}
	return NULL;
}

#undef getenv
#define getenv _breviar_getenv
#define putenv _breviar_putenv
#endif /* LIBC_BIONIC */
#elif defined(__linux) || defined(__unix) || defined(__posix)
// code before # a98c4029 copied here
#ifndef LIBC_BIONIC
// Overwrite putenv() because it causes crashes if breviar_main() is called multiple times:
// unlike setenv(), the argument of putenv() is not copied (at least not on BSD), so
// getenv() is likely to crash after the buffers are freed / reused.
//
// Android libc (bionic) has no such problems, putenv copies the values as
// well. On the other hand, setenv seems to be not working properly there, so
// we disable this logic for android.
static int my_putenv(char* s) {
	char* key = strdup(s);
	if (!key) {
		return 0;
	}

	char* val = strchr(key, '=');
	if (!val) {
		free(key);
		return 0;
	}

	*(val++) = 0;
	int res = setenv(key, val, 1);

	free(key);
	return res;
}
#define putenv my_putenv
#endif /* LIBC_BIONIC */
#endif /* apple | unix */

#ifdef IO_ANDROID
#define putenv android_putenv
#define getenv android_getenv
#endif

short int query_type; // premenna obsahujuca PRM_..., deklarovana v mydefs.h

// globalna premenna, do ktorej sa ukladaju info o analyzovanom dni
_struct_dm *_global_den_ptr;
// _struct_dm _global_den;
#define _global_den (*_global_den_ptr)

// globalne premenne, do ktorych sa ukladaju info o analyzovanom dni o sviatkoch svatych
_struct_dm* _global_svaty_ptr[MAX_POCET_SVATY]; // an array of '_struct_dm' pointers
#define _global_svaty(i) (*(_global_svaty_ptr[i - 1]))

// globalna premenna, ktora obsahuje data o spomienke panny marie v sobotu

_struct_dm *_global_pm_sobota_ptr;
// _struct_dm _global_pm_sobota;
#define _global_pm_sobota (*_global_pm_sobota_ptr)

// globalne premenne obsahujuce data modlitbach

_type_1vespery     *_global_modl_prve_vespery_ptr;
#define _global_modl_prve_vespery (*_global_modl_prve_vespery_ptr)

_type_1kompletorium *_global_modl_1kompletorium_ptr;
#define _global_modl_prve_kompletorium (*_global_modl_1kompletorium_ptr)

_type_invitatorium *_global_modl_invitatorium_ptr;
#define _global_modl_invitatorium (*_global_modl_invitatorium_ptr)

_type_posv_citanie *_global_modl_posv_citanie_ptr;
#define _global_modl_posv_citanie (*_global_modl_posv_citanie_ptr)

_type_ranne_chvaly *_global_modl_ranne_chvaly_ptr;
#define _global_modl_ranne_chvaly (*_global_modl_ranne_chvaly_ptr)

_type_cez_den_9     *_global_modl_cez_den_9_ptr;
#define _global_modl_cez_den_9 (*_global_modl_cez_den_9_ptr)
_type_cez_den_12     *_global_modl_cez_den_12_ptr;
#define _global_modl_cez_den_12 (*_global_modl_cez_den_12_ptr)
_type_cez_den_3     *_global_modl_cez_den_3_ptr;
#define _global_modl_cez_den_3 (*_global_modl_cez_den_3_ptr)

_type_vespery      *_global_modl_vespery_ptr;
#define _global_modl_vespery (*_global_modl_vespery_ptr)

_type_kompletorium *_global_modl_kompletorium_ptr;
#define _global_modl_kompletorium (*_global_modl_kompletorium_ptr)

_struct_anchor_and_file *_global_include_static_text_ptr;
#define _global_include_static_text (*_global_include_static_text_ptr)

// globalna premenna, ktora obsahuje MODL_...
short int _global_modlitba = MODL_NEURCENA;

// globalna premenna, do ktorej ukladaju funkcie vytvor_query_string_... linku tvaru SCRIPT_PATH(script_name) ++ "?param1=val&param2=val&..." | 2003-07-09 prerobeny & v linkach na HTML_AMPERSAND
char *_global_link_ptr;
#define _global_link _global_link_ptr

char *_global_pom_str; // pomocný string: návratová hodnota viacerých funkcií (hľadaj "return (_global_pom_str);")

// globalna premenna, do ktorej sa ukladaju info o jednotlivych vyznacnych liturgickych dni, pouzivaju void _dm_...() funkcie a void analyzuj_rok() funkcia
_struct_dm *_global_result_ptr;
#define _global_result (*_global_result_ptr)

// globalna premenna, do ktorej sa uklada info o liturgickom roku pouziva void analyzuj_rok() funkcia
_struct_lrok *_global_r_ptr;
#define _global_r (*_global_r_ptr)

// globálna premenná, ktorú je potrebné na miestach, kde by sme potrebovali zistiť v runtime #define a kombinovať ho s podmienkou z runtime (2011-04-20)
short int _global_system;

// globalna premenna, do ktorej sviatky_svatych() uklada pocet sviatkov (de facto lubovolnych spomienok), ktore pripadaju na dany den
// -- v podstate neuklada do nej, ale v _rozbor_dna() sa do nej priradi vysledok (navratova hodnota) z sviatky_svatych()
short int _global_pocet_svatych;

// globálna premenná -- pole -- obsahujúca options; pôvodne to boli globálne premenné _global_opt 1..9 atď., obsahujú pom_OPT...
unsigned long long _global_opt[POCET_GLOBAL_OPT];
// globálna premenná -- pole -- obsahujúca force options; pôvodne to boli globálne premenné _global_force_opt 1..9 atď., obsahujú pom_FORCE_OPT...
unsigned long long _global_force_opt[POCET_GLOBAL_OPT];

// globálne premenné -- polia -- obsahujúce jednotlivé bity pre force option 0, 1, 2, 4, 5, 6
unsigned long long _global_opt_0_specialne[POCET_OPT_0_SPECIALNE];
unsigned long long _global_opt_1_casti_modlitby[POCET_OPT_1_CASTI_MODLITBY];      
unsigned long long _global_opt_2_html_export[POCET_OPT_2_HTML_EXPORT];
unsigned long long _global_opt_4_offline_export[POCET_OPT_4_OFFLINE_EXPORT];
unsigned long long _global_opt_5_alternatives[POCET_OPT_5_ALTERNATIVES];
unsigned long long _global_opt_6_alternatives_multi[POCET_OPT_6_ALTERNATIVES_MULTI];

short int _global_opt_append = NIE;
short int _global_opt_tedeum = NIE;
short int _global_pocet_slava_otcu = 0; // pridaná 2007-05-18; 2011-04-28: zrušil som porovnanie pri kontrole chválospevu Dan 3, 57-88. 56; asi je táto premenná zbytočná, ale možno sa ešte zíde :)

short int _global_ant_mcd_rovnake = NIE;
short int _global_opt_export_date_format = EXPORT_DATE_SIMPLE;
short int _global_opt_batch_monthly = NIE;
short int _global_hlavicka_Export = 0;
short int _global_patka_Export = 0;

char *_global_string;
char *_global_string2;
char *_global_string_farba;

char _global_string_modlitba[SMALL];
char _global_string_podnadpis[SMALL];
char _global_string_spol_cast[MAX_GLOBAL_STR2];
char _global_string_spol_cast_full[MAX_GLOBAL_STR];

// 2012-08-16: doplnené kvôli návratovej hodnote z funkcie init_global_string_spol_cast()
short int ret_sc = MODL_SPOL_CAST_NULL;

short int _global_linky;

short int _global_jazyk;
short int _global_kalendar;
short int _global_ritus;

short int _global_css;

short int _global_font; // for value FONT_CUSTOM, we use pom_FONT as global variable unless empty
short int _global_font_size;
short int _global_font_size_pt;
short int _global_style_margin;
short int _global_line_height_perc;

short int _global_pocet_zalmov_kompletorium;

char _special_anchor_prefix[SMALL]; // used for CZ hymns
char _special_anchor_postfix[SMALL]; // used for CZ hymns in Per Annum
char _special_anchor_prefix2[SMALL]; // used for CZ 2nd readings

char _global_export_navig_hore[SMALL] = DEFAULT_MONTH_EXPORT;
char _global_export_navig_hore_month[SMALL] = DEFAULT_MONTH_EXPORT;
char _global_export_navig_hore_day[SMALL] = DEFAULT_MONTH_EXPORT;

char _global_css_font_family[SMALL] = DEFAULT_FONT_FAMILY_SERIF;
char _global_css_font_size[SMALL] = STR_EMPTY;
short int _global_override_thin_nbsp = NIE; // whether to override ALL nbsp with thin nbsp

short int _global_vstup_den = 0;
short int _global_vstup_mesiac = 0;
short int _global_vstup_rok = 0;
short int _global_poradie_svaty = 0;

short int _global_rok_from = 0;
short int _global_rok_to = 0;

short int _global_pocet_navigacia = 0; // počet prejdených/spracovaných parametrov PARAM_NAVIGACIA

short int _global_pocet_volani_interpretTemplate = 0; // počet volaní _global_pocet_volani_interpretTemplate()

//---------------------------------------------------------------------

#define DEBUG_GET_FORM 	Log("getForm(): ");Log
#define DEBUG_GET_ARGV	Log("getArgv(): ");Log

// globalna premenna, ktora hovori, ci preskakovat <!--{ ... }--> tagy pri preskakovani Magnifikat / Benediktus (ak je _global_opt 1 == ANO)
short int _global_skip_in_prayer = NIE;
short int _global_skip_in_prayer_2 = NIE; // 2011-04-07: kvôli číslovaniu veršov v častiach, kde sa používa _global_skip_in_prayer
short int _global_skip_in_prayer_vnpc = NIE; // 2011-05-03: kvôli veľkonočnej nedeli, posvätné čítanie
short int _global_som_vo_vigilii = NIE;

short int params; 
// odkial su brane parametre; hodnoty
// SCRIPT_PARAM_FROM_FORM
// SCRIPT_PARAM_FROM_ARGV
// SCRIPT_PARAM_FROM_QS
char *query_string; // QUERY_STRING environment variable

char pom_QUERY_TYPE [MAX_POM_QUERY_TYPE] = STR_EMPTY; // typ dotazu, retazec
char pom_DEN        [SMALL] = STR_EMPTY; // sluzi aj ako pom_DEN_V_TYZDNI a pom_SVIATOK
#define pom_DEN_V_TYZDNI	pom_DEN
#define pom_SVIATOK			pom_DEN

char pom_MESIAC     [SMALL] = STR_EMPTY; // sluzi aj ako pom_TYZDEN aj ako mesiac roka
#define pom_TYZDEN		pom_MESIAC

char pom_ROK        [SMALL] = STR_EMPTY; // sluzi aj ako pom_ANALYZA_ROKU
#define pom_ANALYZA_ROKU	pom_ROK
#define pom_STATIC_TEXT     pom_ROK

char pom_MODLITBA   [SMALL] = STR_EMPTY;
#define pom_MODL_ORDINARIUM	pom_MODLITBA

char pom_OPT[POCET_GLOBAL_OPT][SMALL];
char pom_FORCE_OPT[POCET_GLOBAL_OPT][SMALL];
// reťazcové polia pre force option 0, 1, 2, 4 (jednotlivé bit-komponenty), 6 (decimal-place-components)
char pom_FORCE_OPT_0_SPECIALNE[POCET_OPT_0_SPECIALNE][SMALL];
char pom_FORCE_OPT_1_CASTI_MODLITBY[POCET_OPT_1_CASTI_MODLITBY][SMALL];
char pom_FORCE_OPT_2_HTML_EXPORT[POCET_OPT_2_HTML_EXPORT][SMALL];
char pom_FORCE_OPT_4_OFFLINE_EXPORT[POCET_OPT_4_OFFLINE_EXPORT][SMALL];
char pom_FORCE_OPT_5_ALTERNATIVES[POCET_OPT_5_ALTERNATIVES][SMALL];
char pom_FORCE_OPT_6_ALTERNATIVES_MULTI[POCET_OPT_6_ALTERNATIVES_MULTI][SMALL];

char pom_OPT_APPEND[SMALL] = STR_EMPTY;
char pom_DALSI_SVATY[SMALL] = STR_EMPTY;

char pom_ROK_FROM[SMALL] = STR_EMPTY;
char pom_ROK_TO[SMALL] = STR_EMPTY;

char pom_LINKY[SMALL] = STR_EMPTY;

char pom_JAZYK[SMALL] = STR_EMPTY;
char pom_KALENDAR[SMALL] = STR_EMPTY;

char pom_CSS[SMALL] = STR_EMPTY;

char pom_FONT[SMALL] = STR_EMPTY;
char pom_FONT_SIZE[VERY_SMALL] = STR_EMPTY;
char pom_FONT_SIZE_PT[VERY_SMALL] = STR_EMPTY;
char pom_STYLE_MARGIN[VERY_SMALL] = STR_EMPTY;
char pom_LINE_HEIGHT_PERC[VERY_SMALL] = STR_EMPTY;

char pom_OPT_DATE_FORMAT[SMALL] = STR_EMPTY;

char pom_EXPORT_MONTHLY [SMALL] = STR_EMPTY;
// pre batch mód po mesiacoch; 0 = doterajší spôsob (riadok s dátumom a potom linky na modlitby)
short int export_monthly_druh = 0;

short int export_month_zaciatok = NIE;
short int export_month_nova_modlitba = NIE;

char pom_LIT_OBD [SMALL] = STR_EMPTY;
char pom_LIT_ROK [SMALL] = STR_EMPTY;

char bad_param_str[MAX_STR] = STR_EMPTY;

urlvariable param[MAX_VARIABLES];
// struktura oznacujuca dvojice <meno, hodnota> z query stringu, napr. QUERY_STRING=QUERY_TYPE=PRM_DATUM&DEN=7&MESIAC=5&ROK=1976...
// je to i-tica (tuple)
//
// <WWW_QUERY_TYPE, PRM_DATUM>,
// <WWW_DEN, 7>,
// <WWW_MESIAC, 5>,
// <WWW_ROK, 1976>,
// <WWW_MODLITBA, ...>

char file_export[SMALL] = STR_EMPTY; 
// nazov suboru, do ktoreho sa mozno exportuje v pripade pouzitia switchu `e' pri getArgv();
// ak je na jeho konci '+', tak sa appenduje; vyuzite pre switch -a (append), pozri dolu 
// pre case SCRIPT_PARAM_FROM_ARGV

char include_dir[MAX_STR] = STR_EMPTY;

char name_binary_executable[MAX_STR] = STR_EMPTY;
char name_batch_file[MAX_STR] = STR_EMPTY;
FILE *batch_file = NULL;

char name_batch_html_file[MAX_STR] = STR_EMPTY;
FILE *batch_html_file = NULL;

char dir_name[MAX_STR] = STR_EMPTY;

FILE *batch_month_file = NULL;
char name_batch_month_file[MAX_STR] = STR_EMPTY;

char system_command[MAX_STR] = STR_EMPTY;

short int index_pre_mesiac_otvoreny = NIE;

char optional_html_line_break[MAX_STR] = STR_EMPTY;
char optional_html_class_button[MAX_STR] = STR_EMPTY;
char optional_html_button_begin[MAX_STR] = STR_EMPTY;
char optional_html_button_prayer_begin[MAX_STR] = STR_EMPTY;
char optional_html_button_end[MAX_STR] = STR_EMPTY;

// -------------------------------------------------------------------

short int _smer_override(short int smer, short int typslav) {
	if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OVERRIDE_STUP_SLAV)) {
		if (typslav == SLAV_SVIATOK) {
			return 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		}
		else if (typslav == SLAV_SPOMIENKA) {
			return ((isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_STUP_SVIATOK_SLAVNOST)) ? 3 : 7); // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári resp. sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		}
		else if (typslav == SLAV_LUB_SPOMIENKA) {
			return ((isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_STUP_SVIATOK_SLAVNOST)) ? 4 : 8); // miestne slávnosti resp. miestne sviatky
		}
		else {
			return smer;
		}
	}
	else {
		return smer;
	}
} // _smer_override()

short int _typslav_override(short int typslav) {
	if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OVERRIDE_STUP_SLAV)) {
		if (_global_poradie_svaty == PORADIE_PM_SOBOTA) {
			// override sa neaplikuje na spomienku Panny Márie v sobotu
			return typslav;
		}
		else if (typslav == SLAV_SVIATOK) {
			return SLAV_SLAVNOST;
		}
		else if ((typslav == SLAV_SPOMIENKA) || (typslav == SLAV_LUB_SPOMIENKA)) {
			return ((isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_STUP_SVIATOK_SLAVNOST)) ? SLAV_SLAVNOST : SLAV_SVIATOK);
		}
		else {
			return typslav;
		}
	}
	else {
		return typslav;
	}
} // _typslav_override()

short int useWhenGlobalOption(short opt_i, unsigned long long bit_opt_i_component_j) {
	if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT)) {
		// behave as if these were switched OFF for voice output
		if ((opt_i == OPT_0_SPECIALNE) && (
			(bit_opt_i_component_j == BIT_OPT_0_VERSE)
			|| (bit_opt_i_component_j == BIT_OPT_0_REFERENCIE)
			|| (bit_opt_i_component_j == BIT_OPT_0_CITANIA)
			|| (bit_opt_i_component_j == BIT_OPT_0_FOOTNOTES)
			|| (bit_opt_i_component_j == BIT_OPT_0_TRANSPARENT_NAV)
			// || (bit_opt_i_component_j == BIT_OPT_0_ZALMY_FULL_TEXT) // read also psalm omissions (for TTS)
			)) {
			return NIE;
		}
		else if ((opt_i == OPT_1_CASTI_MODLITBY) && (
			(bit_opt_i_component_j == BIT_OPT_1_ZOBRAZ_SPOL_CAST)
			)) {
			return NIE;
		}
		else if ((opt_i == OPT_2_HTML_EXPORT) && (
			(bit_opt_i_component_j == BIT_OPT_2_TEXT_WRAP)
			|| (bit_opt_i_component_j == BIT_OPT_2_ROZNE_MOZNOSTI)
			)) {
			return NIE;
		}
		else if ((opt_i == OPT_5_ALTERNATIVES) && (
			(bit_opt_i_component_j == BIT_OPT_5_ZAVER_KNAZ_DIAKON)
			)) {
			return NIE;
		}
		// behave as if these were switched ON for voice output
		else if ((opt_i == OPT_0_SPECIALNE) && (
			(bit_opt_i_component_j == BIT_OPT_0_FONT_NORMAL)
			)) {
			return ANO;
		}
		else if ((opt_i == OPT_1_CASTI_MODLITBY) && (
			(bit_opt_i_component_j == BIT_OPT_1_TEDEUM)
			|| (bit_opt_i_component_j == BIT_OPT_1_CHVALOSPEVY)
			|| (bit_opt_i_component_j == BIT_OPT_1_SLAVA_OTCU)
			|| (bit_opt_i_component_j == BIT_OPT_1_OTCENAS)
			|| (bit_opt_i_component_j == BIT_OPT_1_PLNE_RESP)
			|| (bit_opt_i_component_j == BIT_OPT_1_PROSBY_ZVOLANIE)
			|| (bit_opt_i_component_j == BIT_OPT_1_ZAVER)
			|| (bit_opt_i_component_j == BIT_OPT_1_SKRY_POPIS)
			|| (bit_opt_i_component_j == BIT_OPT_1_KOMPL_MARIA_ANT)
			)) {
			return ANO;
		}
		else if ((opt_i == OPT_2_HTML_EXPORT) && (
			(bit_opt_i_component_j == BIT_OPT_2_ALTERNATIVES)
			)) {
			return ANO;
		}
		return isGlobalOption(opt_i, bit_opt_i_component_j);
	}
	return isGlobalOption(opt_i, bit_opt_i_component_j);
} // useWhenGlobalOption()

void setGlobalOption(short opt_i, unsigned long long bit_opt_i_component_j, short value) {
	if (opt_i == OPT_6_ALTERNATIVES_MULTI) {
		// OPT 6 uses decimal-place logic; value should be between 0 and 9
		short current_value = (short)((_global_opt[opt_i] DIV bit_opt_i_component_j) MOD 10);
		if (current_value != value && value >= 0 && value <= 9) {
			_global_opt[opt_i] = _global_opt[opt_i] + bit_opt_i_component_j * (value - current_value);
		}
	}
	else {
		// bitwise logic
		if (((_global_opt[opt_i] & bit_opt_i_component_j) == bit_opt_i_component_j) && (value == NIE)) {
			_global_opt[opt_i] -= bit_opt_i_component_j;
		}
		else if (((_global_opt[opt_i] & bit_opt_i_component_j) != bit_opt_i_component_j) && (value == ANO)) {
			_global_opt[opt_i] += bit_opt_i_component_j;
		}
	}
} // setGlobalOption()

short int getGlobalOption(short opt_i, unsigned long long bit_opt_i_component_j) {
	if (opt_i == OPT_6_ALTERNATIVES_MULTI) {
		// OPT 6 uses decimal-place logic; value should be between 0 and 9
		return ((_global_opt[opt_i] DIV bit_opt_i_component_j) MOD 10);
	}
	else {
		// bitwise logic
		return isGlobalOption(opt_i, bit_opt_i_component_j);
	}
} // getGlobalOption()

// -------------------------------------------------------------------

// Read a POST query from standard input into a dynamic buffer. Terminate it with a null character.
short int postread(void) {
	char *buf = NULL;
	long size = 0, sofar = 0, got;

	LogUncgi("uncgi::postread() -- zaciatok\n");
	buf = getenv("CONTENT_TYPE");
	if (buf == NULL || strcmp(buf, "application/x-www-form-urlencoded")) {
		LogUncgi("uncgi::No content type was passed.\n");
		return FAILURE;
	}

	buf = getenv("CONTENT_LENGTH");
	if (buf == NULL) {
		LogUncgi("uncgi::The server did not tell uncgi how long the request was.\n");
		return FAILURE;
	}

	size = atoi(buf);
	buf = (char *)malloc(size + 1);
	if (buf == NULL) {
		LogUncgi("uncgi::Error: postread\n");
		return FAILURE;
	}
	do
	{
		got = fread(buf + sofar, 1, size - sofar, STDIN_FILE);
		sofar += got;
	} while (got && sofar < size);

	buf[sofar] = '\0';

	_global_buf = buf;
	LogUncgi("uncgi::postread() -- koniec; výstupný buffer == %s\n", _global_buf);
	return SUCCESS;
} // postread();

// Convert two hex digits to a value.
static short int htoi(/* unsigned */ char *s) {
	short int value;
	char c;

	c = s[0];
	if (isupper(c)) {
		c = tolower(c);
	}
	value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;

	c = s[1];
	if (isupper(c)) {
		c = tolower(c);
	}
	value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;

	return (value);
} // htoi();

// Get rid of all the URL escaping in a string.  Modify it in place, since the result will always be equal in length or smaller.
static void url_unescape(/* unsigned */ char *str) {
	/* unsigned */ char *dest = str;

	while (str[0])
	{
		if (str[0] == '+') {
			dest[0] = ' ';
		}
		else if (str[0] == '%' && ishex(str[1]) && ishex(str[2]))
		{
			dest[0] = (/* unsigned */ char)htoi(str + 1);
			str += 2;
		}
		else {
			dest[0] = str[0];
		}

		str++;
		dest++;
	}

	dest[0] = '\0';
} // url_unescape();

// Stuff a URL-unescaped variable, with the prefix on its name, into the environment. Uses the "=" from the CGI arguments.
// Putting an "=" in a field name is probably a bad idea.
// If the variable is already defined, append a '#' to it along with the new value.
// If the variable name begins with an underline, strip whitespace from the start and end and normalize end-of-line characters.
static void stuffenv(char *var) {
	char *buf, *c, *s, *t, *oldval, *newval;
	short int despace = 0, got_cr = 0;
	int putenv_ret;

#ifdef DEBUG
	LogUncgi("Before unescape: %s\n", var);
#endif

	url_unescape(var);

#ifdef DEBUG
	LogUncgi("After unescape: %s\n", var);
#endif

	if (strlen(_global_buf2) > 0) {
		strcat(_global_buf2, "&");
	}
	strcat(_global_buf2, var);
#ifdef DEBUG
	LogUncgi("Nabaľujem _global_buf2 == %s\n", _global_buf2);
#endif

	// Allocate enough memory for the variable name and its value.
	buf = (char *)malloc(strlen(var) + sizeof(WWW_PREFIX) + 2);
	if (buf == NULL) {
		Log("  Not enough memory to allocate buffer for `buf'\n");
		return;
	}
	strcpy(buf, WWW_PREFIX);
	if (var[0] == '_')
	{
		strcpy(buf + sizeof(WWW_PREFIX) - 1, var + 1);
		despace = 1;
	}
	else {
		strcpy(buf + sizeof(WWW_PREFIX) - 1, var);
	}

	// If, for some reason, there wasn't an = in the query string, add one so the environment will be valid.
	// Also, change periods to underscores so folks can get at "image" input fields from the shell, which has trouble with periods in variable names.
	for (c = buf; *c != '\0'; c++)
	{
		if (*c == '.') {
			*c = '_';
		}
		if (*c == '=') {
			break;
		}
	}
	if (*c == '\0') {
		c[1] = '\0';
	}
	*c = '\0';

	// Do whitespace stripping, if applicable.  Since this can only ever shorten the value, it's safe to do in place.
	if (despace && c[1])
	{
#ifdef DEBUG
		LogUncgi("  Stripping whitespace.\n");
#endif
		for (s = c + 1; *s && isspace(*s); s++)
			;
		t = c + 1;
		while (*s)
		{
			if (*s == '\r')
			{
				got_cr = 1;
				s++;
				continue;
			}
			if (got_cr)
			{
				if (*s != '\n') {
					*t++ = '\n';
				}
				got_cr = 0;
			}
			*t++ = *s++;
		}

		// Strip trailing whitespace if we copied anything.
		while (t > c && isspace(*--t))
			;
		t[1] = '\0';
	}

	// Check for the presence of the variable.
	if ((oldval = getenv(buf))) // priradenie do oldval a následný test, či nie je pointer NULL
	{
#ifdef DEBUG
		LogUncgi("  Variable %s exists with value %s\n", buf, oldval);
#endif
		newval = (char *)malloc(strlen(oldval) + strlen(buf) + strlen(c + 1) + 3);
		if (newval == NULL) {
			Log("  Not enough memory to allocate buffer for `buf'\n");
			return;
		}
		*c = '=';
		sprintf(newval, "%s#%s", buf, oldval); // pôvodne tu bolo toto; zapoznámkované 2011-04-13 (pokus)
		// sprintf(newval, "%s", buf);
		*c = '\0';

		// Set up to free the entire old environment variable -- there really ought to be a library function for this.
		// It's safe to free it since the only place these variables come from is a previous call to this function; we can never be freeing a system-supplied environment variable.
		oldval -= strlen(buf) + 1; // skip past VAR=
	}
	else
	{
#ifdef DEBUG
		LogUncgi("  Variable %s doesn't exist yet.\n", buf);
#endif
		*c = '=';
		newval = buf;
	}

#ifdef DEBUG
	LogUncgi("  putenv %s\n", newval);
#endif
	putenv_ret = putenv(newval);
	if (putenv_ret != 0) {
		LogUncgi("  putenv vrátila chybu! (%s)\n", newval);
	}
	else {
		LogUncgi("  putenv OK (%s, %s)\n", buf, newval);
	}

	if (oldval)
	{
		// Do the actual freeing of the old value after it's not being referred to any more.
		// Log("free oldval (%s)...\n", oldval);
		// free(oldval);
		// Log("free buf (%s)...\n", buf);
		// free(buf);
	}// if (oldval)
} // stuffenv();

// Scan a query string, stuffing variables into the environment. This should ideally just use strtok(), but that's not available everywhere.
static void scanquery(char *q) {
	char	*next = q;

	LogUncgi("uncgi::scanquery() -- začiatok\n");
	do {
		next = strchr(next, '&');
		if (next) {
			*next = '\0';
		}

		stuffenv(q);
		if (next) {
			*next++ = '&';
		}
		q = next;
		LogUncgi("uncgi::scanquery(): \n\tq == %s\n\t_global_buf == %s\n", q, _global_buf);
	} while (q != NULL);
	LogUncgi("uncgi::scanquery() -- koniec\n");
} // scanquery();

// naplni premenne WWW_... hodnotami z QS, t.j. akoby to vratilo uncgi.c
// return: on success, returns SUCCESS
//         on error,   returns FAILURE
short int setForm(void) {
	char local_str[SMALL] = STR_EMPTY;
	short int ret;
	short int i; // kvôli prilep_request_options

	Log("setForm() -- begin\n");

#ifndef LOG_PARAMS
	Log("setForm(): LOG_PARAMS is undefined, no LogParams() printed...\n");
#endif

	// pri simulácii z qs je pom_QUERY_TYPE = psqs => upravujem, aby bola hodnota parametra param[x].name == qt resp. berieme z query_type
	mystrcpy(local_str, STR_EMPTY, SMALL);
	if (!equals(pom_QUERY_TYPE, STR_EMPTY)) {
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_QUERY_TYPE), SMALL);
		strcat(local_str, "=");
		if (equals(pom_QUERY_TYPE, STR_PRM_SIMULACIA_QS)) {
			LogParams("\tpre simuláciu priraďujem hodnotu z query_type (%s)...\n", param[0].val);
			// ak je simulácia, nastav hodnotu podľa query_type
			strcat(local_str, param[0].val);
		}
		else {
			strcat(local_str, pom_QUERY_TYPE);
		}
		LogParams("--- setForm: putenv(%s); ... ", local_str);
		ret = putenv(local_str);
		LogParams("--- setForm: putenv returned %d.\n", ret);
	}

	// deň
	mystrcpy(local_str, STR_EMPTY, SMALL);
	if (!equals(pom_DEN, STR_EMPTY)) {
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_DEN), SMALL);
		strcat(local_str, "=");
		strcat(local_str, pom_DEN);
		LogParams("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		LogParams("--- setForm: putenv returned %d.\n", ret);
	}

	// mesiac
	mystrcpy(local_str, STR_EMPTY, SMALL);
	if (!equals(pom_MESIAC, STR_EMPTY)) {
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MESIAC), SMALL);
		strcat(local_str, "=");
		strcat(local_str, pom_MESIAC);
		LogParams("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		LogParams("--- setForm: putenv returned %d.\n", ret);
	}

	// rok
	mystrcpy(local_str, STR_EMPTY, SMALL);
	if (!equals(pom_ROK, STR_EMPTY)) {
		if (query_type == PRM_ANALYZA_ROKU) {
			mystrcpy(local_str, ADD_WWW_PREFIX_(STR_ANALYZA_ROKU), SMALL);
		}
		else if (query_type == PRM_STATIC_TEXT) {
			mystrcpy(local_str, ADD_WWW_PREFIX_(STR_STATIC_TEXT), SMALL);
		}
		else {
			mystrcpy(local_str, ADD_WWW_PREFIX_(STR_ROK), SMALL);
		}
		strcat(local_str, "=");
		strcat(local_str, pom_ROK);
		LogParams("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		LogParams("--- setForm: putenv returned %d.\n", ret);
	}

	// modlitba
	mystrcpy(local_str, STR_EMPTY, SMALL);
	if (!equals(pom_MODLITBA, STR_EMPTY)) {
		if (query_type == PRM_STATIC_TEXT) {
			mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_ORDINARIUM), SMALL);
		}
		else {
			mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODLITBA), SMALL);
		}
		strcat(local_str, "=");
		strcat(local_str, pom_MODLITBA);
		LogParams("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		LogParams("--- setForm: putenv returned %d.\n", ret);
	}
	// pom_DALSI_SVATY
	mystrcpy(local_str, STR_EMPTY, SMALL);
	if (!equals(pom_DALSI_SVATY, STR_EMPTY)) {
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_DALSI_SVATY), SMALL);
		strcat(local_str, "=");
		strcat(local_str, pom_DALSI_SVATY);
		LogParams("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		LogParams("--- setForm: putenv returned %d.\n", ret);
	}

	// options
	for (i = 0; i < POCET_GLOBAL_OPT; i++) {
		mystrcpy(local_str, STR_EMPTY, SMALL);
		if (!equals(pom_OPT[i], STR_EMPTY)) {
			mystrcpy(local_str, WWW_PREFIX, SMALL);

			strcat_str_opt_bit_order(local_str, i, USE_STR_OPT);

			strcat(local_str, "=");
			strcat(local_str, pom_OPT[i]);
			LogParams("--- setForm: putenv(%s); ...\n", local_str);
			ret = putenv(local_str);
			LogParams("--- setForm: putenv returned %d.\n", ret);
		}
	}// for i

	// force options
	for (i = 0; i < POCET_GLOBAL_OPT; i++) {
		mystrcpy(local_str, STR_EMPTY, SMALL);
		if (!equals(pom_FORCE_OPT[i], STR_EMPTY)) {
			mystrcpy(local_str, WWW_PREFIX, SMALL);

			strcat_str_opt_bit_order(local_str, i, USE_STR_FORCE_OPT);

			strcat(local_str, "=");
			strcat(local_str, pom_FORCE_OPT[i]);
			LogParams("--- setForm: putenv(%s); ...\n", local_str);
			ret = putenv(local_str);
			LogParams("--- setForm: putenv returned %d.\n", ret);
		}
	}// for i

	// force option 0, jednotlivé bit-komponenty
	LogParams("force option %d, jednotlivé bit-komponenty...(setForm)\n", OPT_0_SPECIALNE);
	for (i = 0; i < POCET_OPT_0_SPECIALNE; i++) {
		mystrcpy(local_str, STR_EMPTY, SMALL);
		if (!equals(pom_FORCE_OPT_0_SPECIALNE[i], STR_EMPTY)) {
			mystrcpy(local_str, WWW_PREFIX, SMALL);

			strcat_str_opt_bit_order(local_str, OPT_0_SPECIALNE, i);

			strcat(local_str, "=");
			strcat(local_str, pom_FORCE_OPT_0_SPECIALNE[i]);
			LogParams("--- setForm: putenv(%s); ...\n", local_str);
			ret = putenv(local_str);
			LogParams("--- setForm: putenv returned %d.\n", ret);
		}
	}// for i

	// force option 1, jednotlivé bit-komponenty
	LogParams("force option %d, jednotlivé bit-komponenty...(setForm)\n", OPT_1_CASTI_MODLITBY);
	for (i = 0; i < POCET_OPT_1_CASTI_MODLITBY; i++) {
		mystrcpy(local_str, STR_EMPTY, SMALL);
		if (!equals(pom_FORCE_OPT_1_CASTI_MODLITBY[i], STR_EMPTY)) {
			mystrcpy(local_str, WWW_PREFIX, SMALL);

			strcat_str_opt_bit_order(local_str, OPT_1_CASTI_MODLITBY, i);

			strcat(local_str, "=");
			strcat(local_str, pom_FORCE_OPT_1_CASTI_MODLITBY[i]);
			LogParams("--- setForm: putenv(%s); ...\n", local_str);
			ret = putenv(local_str);
			LogParams("--- setForm: putenv returned %d.\n", ret);
		}
	}// for i

	// force option 2, jednotlivé bit-komponenty
	LogParams("force option %d, jednotlivé bit-komponenty...(setForm)\n", OPT_2_HTML_EXPORT);
	for (i = 0; i < POCET_OPT_2_HTML_EXPORT; i++) {
		mystrcpy(local_str, STR_EMPTY, SMALL);
		if (!equals(pom_FORCE_OPT_2_HTML_EXPORT[i], STR_EMPTY)) {
			mystrcpy(local_str, WWW_PREFIX, SMALL);

			strcat_str_opt_bit_order(local_str, OPT_2_HTML_EXPORT, i);

			strcat(local_str, "=");
			strcat(local_str, pom_FORCE_OPT_2_HTML_EXPORT[i]);
			LogParams("--- setForm: putenv(%s); ...\n", local_str);
			ret = putenv(local_str);
			LogParams("--- setForm: putenv returned %d.\n", ret);
		}
	}// for i

	 // force option 5, jednotlivé bit-komponenty
	LogParams("force option %d, jednotlivé bit-komponenty...(setForm)\n", OPT_5_ALTERNATIVES);
	for (i = 0; i < POCET_OPT_5_ALTERNATIVES; i++) {
		mystrcpy(local_str, STR_EMPTY, SMALL);
		if (!equals(pom_FORCE_OPT_5_ALTERNATIVES[i], STR_EMPTY)) {
			mystrcpy(local_str, WWW_PREFIX, SMALL);

			strcat_str_opt_bit_order(local_str, OPT_5_ALTERNATIVES, i);

			strcat(local_str, "=");
			strcat(local_str, pom_FORCE_OPT_5_ALTERNATIVES[i]);
			LogParams("--- setForm: putenv(%s); ...\n", local_str);
			ret = putenv(local_str);
			LogParams("--- setForm: putenv returned %d.\n", ret);
		}
	}// for i

	 // force option 6, jednotlivé decimal-place-komponenty
	LogParams("force option %d, jednotlivé decimal-place-komponenty...(setForm)\n", OPT_6_ALTERNATIVES_MULTI);
	for (i = 0; i < POCET_OPT_6_ALTERNATIVES_MULTI; i++) {
		mystrcpy(local_str, STR_EMPTY, SMALL);
		if (!equals(pom_FORCE_OPT_6_ALTERNATIVES_MULTI[i], STR_EMPTY)) {
			mystrcpy(local_str, WWW_PREFIX, SMALL);

			strcat_str_opt_bit_order(local_str, OPT_6_ALTERNATIVES_MULTI, i);

			strcat(local_str, "=");
			strcat(local_str, pom_FORCE_OPT_6_ALTERNATIVES_MULTI[i]);
			LogParams("--- setForm: putenv(%s); ...\n", local_str);
			ret = putenv(local_str);
			LogParams("--- setForm: putenv returned %d.\n", ret);
		}
	}// for i

	mystrcpy(local_str, STR_EMPTY, SMALL);
	if (!equals(pom_JAZYK, STR_EMPTY)) {
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_JAZYK), SMALL);
		strcat(local_str, "=");
		strcat(local_str, pom_JAZYK);
		LogParams("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		LogParams("--- setForm: putenv returned %d.\n", ret);
	}

	mystrcpy(local_str, STR_EMPTY, SMALL);
	if (!equals(pom_KALENDAR, STR_EMPTY)) {
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_KALENDAR), SMALL);
		strcat(local_str, "=");
		strcat(local_str, pom_KALENDAR);
		LogParams("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		LogParams("--- setForm: putenv returned %d.\n", ret);
	}

	mystrcpy(local_str, STR_EMPTY, SMALL);
	if (!equals(pom_CSS, STR_EMPTY)) {
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_CSS), SMALL);
		strcat(local_str, "=");
		strcat(local_str, pom_CSS);
		LogParams("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		LogParams("--- setForm: putenv returned %d.\n", ret);
	}

	mystrcpy(local_str, STR_EMPTY, SMALL);
	if (!equals(pom_FONT, STR_EMPTY)) {
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_FONT_NAME), SMALL);
		strcat(local_str, "=");
		strcat(local_str, pom_FONT);
		LogParams("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		LogParams("--- setForm: putenv returned %d.\n", ret);
	}

	mystrcpy(local_str, STR_EMPTY, SMALL);
	if (!equals(pom_FONT_SIZE, STR_EMPTY)) {
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_FONT_SIZE), SMALL);
		strcat(local_str, "=");
		strcat(local_str, pom_FONT_SIZE);
		LogParams("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		LogParams("--- setForm: putenv returned %d.\n", ret);
	}

	mystrcpy(local_str, STR_EMPTY, SMALL);
	if (!equals(pom_FONT_SIZE_PT, STR_EMPTY)) {
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_FONT_SIZE_PT), SMALL);
		strcat(local_str, "=");
		strcat(local_str, pom_FONT_SIZE_PT);
		LogParams("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		LogParams("--- setForm: putenv returned %d.\n", ret);
	}

	mystrcpy(local_str, STR_EMPTY, SMALL);
	if (!equals(pom_STYLE_MARGIN, STR_EMPTY)) {
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_STYLE_MARGIN), SMALL);
		strcat(local_str, "=");
		strcat(local_str, pom_STYLE_MARGIN);
		LogParams("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		LogParams("--- setForm: putenv returned %d.\n", ret);
	}

	mystrcpy(local_str, STR_EMPTY, SMALL);
	if (!equals(pom_LINE_HEIGHT_PERC, STR_EMPTY)) {
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_LINE_HEIGHT_PERC), SMALL);
		strcat(local_str, "=");
		strcat(local_str, pom_LINE_HEIGHT_PERC);
		LogParams("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		LogParams("--- setForm: putenv returned %d.\n", ret);
	}

	Log("setForm() -- end, returning SUCCESS\n");
	return SUCCESS;
} // setForm();

// zisti, odkial sa citaju argumenty (vstupy);
// return:
//
// 	SCRIPT_PARAM_FROM_FORM (z formulara, t.j. syst. premennych WWW_...)
// 	SCRIPT_PARAM_FROM_ARGV (z argumentov dialogoveho riadka)
// 	SCRIPT_PARAM_FROM_QS   (zo systemovej premennej QUERY_STRING)
//
short int getSrciptParamFrom(int argc) {

	// najprv zistime, ci existuje systemova premenna QUERY_STRING
	char *qs;
	char *method;
	short int ret;

	Log("--- getSrciptParamFrom(): begin\n");

	qs = getenv("QUERY_STRING");

	if (qs != NULL) {
		// znamená to, že existuje query string - či už klasický GET, alebo časť poslaná POST linkou
		Log("qs (query_string) == %s\n", qs);

		Log("trying to unescape &amp; characters...\n");
		mystrcpy(query_string, mystr_replace(qs, HTML_AMPERSAND, "&").c_str(), MAX_QUERY_STR);
	}
	else {
		mystrcpy(query_string, STR_EMPTY, MAX_QUERY_STR);
	}

	if (query_string != NULL) {
		Log("query_string == %s\n", query_string);
	}
	else {
		Log("query_string is NULL\n");
	}

	// get request method (POST vs. GET)
	method = getenv("REQUEST_METHOD");
	if (method != NULL) {
		Log("method == %s\n", method);
	}
	else {
		Log("method is NULL\n");
	}

	if (method != NULL && !strcmp(method, "POST")) {
		ret = postread();
		if (ret == SUCCESS) {
			Log("OK. Pokracujem skenovanim query...\n");
			if ((_global_buf != NULL) && (_global_buf[0] != '\0')) {
				scanquery(_global_buf);

				Log("POST::Vysledok == %s\n", _global_buf2);

				if (query_string != NULL && !equals(query_string, STR_EMPTY)) {
					Log("2006-08-01: Experiment - prilepujem _global_buf2 na koniec query_stringu...\n");
					strcat(query_string, "&");
					strcat(query_string, _global_buf2);
					Log("query_string == %s...\n", query_string);
				}
			}
		}
		else {
			Log("Chyba.\n");
		}
	}// POST

	Log("--- getSrciptParamFrom(): end...\n");

	// systemova premenna QUERY_STRING existuje prave vtedy, ked query_string nie je prazdny retazec
	if ((query_string != NULL) && (strlen(query_string) > 0)) {
		// existuje, teda budeme pekne parsovat
		Log("returning SCRIPT_PARAM_FROM_QS.\n");
		return SCRIPT_PARAM_FROM_QS;
	}
	else if (argc == 1) {
		// query_string bud neexistuje alebo je "", pritom program nema vstupne argumenty (z dial. riadka)
		Log("returning SCRIPT_PARAM_FROM_FORM (argc == %d).\n", argc);
		return SCRIPT_PARAM_FROM_FORM;
	}
	else {// program ma vstupne argumenty, argc > 1
		Log("returning SCRIPT_PARAM_FROM_ARGV -- nothing else matched.\n");
		return SCRIPT_PARAM_FROM_ARGV;
	}
} // getSrciptParamFrom();

void ExportTableCell(const char html_class[MAX_STR]) {
	Export("<");
	Export(html_class);
	Export(">\n");
} // ExportTableCell()

// exports empty table cell
void ExportEmptyCell(short begin = ANO, short end = ANO) {
	if (begin == ANO) {
		ExportTableCell(HTML_TABLE_CELL);
	}

	if (begin == ANO || end == ANO) {
		Export("<" HTML_SPAN_HIDDEN ">." HTML_SPAN_END); // empty table cell
	}

	if (end == ANO) {
		Export(HTML_TABLE_CELL_END "\n");
	}
} // ExportEmptyCell()

// exportuje heading velkosti size;
// jednotne exportovanie. <h2> pre Liturgiu hodin, <h3> pre detailnejsi vypis
void _export_heading(/* int size, */const char* string) {
	short int size = 2;
	Export("\n<h%d>Kontrola údajov</h%d>\n\n", size, size);

	size = 4;
	Export("\n<h%d " HTML_CLASS_BLUE ">%s</h%d>\n\n", size, string, size);
} // _export_heading()

void _export_heading_center(short int typ, const char* string) {
	short int size = 2;
	if (typ == PRM_XML) {
		Export("\n" ELEM_BEGIN(XML_TITLE) "\n");
	}
	else {
		ExportHtmlComment("BEGIN:heading");
		Export("\n<h%d>", size);
	}
	Export("%s", string);
	if (typ == PRM_XML) {
		Export("\n" ELEM_END(XML_TITLE) "\n");
	}
	else {
		Export("</h%d>\n", size);
		ExportHtmlComment("END:heading");
	}
} // _export_heading_center()

// helper for _export_link_show_hide(), _export_link_multi()
void _export_link_helper(char pom[MAX_STR], char pom2[MAX_STR], char pom3[MAX_STR], char popis[MAX_STR], char html_tag_begin[SMALL], char html_class[SMALL], char specific_string_before[SMALL], char specific_string_after[SMALL], char anchor[SMALL], char html_tag_end[SMALL], char left_parenthesis = '(', char right_parenthesis = ')') {
	Log("_export_link_helper(): začiatok...\n");

	char pom_den[VERY_SMALL];
	mystrcpy(pom_den, STR_EMPTY, VERY_SMALL);
	if (_global_den.den == VSETKY_DNI) {
		mystrcpy(pom_den, STR_VSETKY_DNI, VERY_SMALL);
	}
	else {
		sprintf(pom_den, "%d", _global_den.den);
	}

	char pom_mesiac[VERY_SMALL];
	mystrcpy(pom_mesiac, STR_EMPTY, VERY_SMALL);
	if (_global_den.mesiac >= MES_JAN && _global_den.mesiac <= MES_DEC) {
		sprintf(pom_mesiac, "%d", _global_den.mesiac);
	}
	else {
		mystrcpy(pom_mesiac, STR_VSETKY_MESIACE, VERY_SMALL);
	}

	// prilepenie poradia svätca
	if (_global_poradie_svaty > 0) {
		sprintf(pom2, HTML_AMPERSAND"%s=%d", STR_DALSI_SVATY, _global_poradie_svaty);
	}// _global_poradie_svaty > 0
	else {
		mystrcpy(pom2, STR_EMPTY, MAX_STR);
	}// !(_global_poradie_svaty > 0)

	// teraz vytvoríme reťazec s options
	prilep_request_options(pom2, pom3);

	// prilepíme modlitbu
	if (_global_modlitba != MODL_NEURCENA) {
		sprintf(pom3, HTML_LINK_CALL_PARAM, STR_MODLITBA, str_modlitby[_global_modlitba]);
		strcat(pom2, pom3);
		Log("_export_link_helper(): pom2 == %s...\n", pom2);
	}

	// napokon prilepíme #anchor
	if (!equals(anchor, STR_EMPTY)) {
		sprintf(pom3, "#%s", anchor);
		strcat(pom2, pom3);
	}

	// export hyperlinku
	if (query_type == PRM_DNES) {
		sprintf(pom, "%s?%s=%s%s",
			script_name,
			STR_QUERY_TYPE, STR_PRM_DNES,
			pom2);
	}
	else if (query_type == PRM_DATUM) {
		sprintf(pom, "%s?%s=%s" HTML_AMPERSAND "%s=%s" HTML_AMPERSAND "%s=%s" HTML_AMPERSAND "%s=%d%s",
			script_name,
			STR_QUERY_TYPE, STR_PRM_DATUM,
			STR_DEN, pom_den /* _global_den.den */,
			STR_MESIAC, pom_mesiac /* _global_den.mesiac */,
			STR_ROK, _global_den.rok,
			pom2);
	}
	else if (query_type == PRM_LIT_OBD) {
		sprintf(pom, "%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%c%s",
			script_name,
			STR_QUERY_TYPE, STR_PRM_LIT_OBD,
			STR_DEN_V_TYZDNI, _global_den.denvt,
			STR_TYZDEN, _global_den.tyzden,
			STR_LIT_OBD, _global_den.litobd,
			STR_LIT_ROK, _global_den.litrok,
			pom2);
	}
	else if (query_type == PRM_ANALYZA_ROKU) {
		sprintf(pom, "%s?%s=%s" HTML_AMPERSAND "%s=%d%s",
			script_name,
			STR_QUERY_TYPE, STR_PRM_ANALYZA_ROKU,
			STR_ANALYZA_ROKU, _global_den.rok,
			pom2);
	}
	else if (query_type == PRM_TABULKA) {
		sprintf(pom, "%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d%s",
			script_name,
			STR_QUERY_TYPE, STR_PRM_TABULKA,
			STR_ROK_FROM, _global_rok_from,
			STR_ROK_TO, _global_rok_to,
			STR_TABULKA_LINKY, _global_den.mesiac, /* whether to display dates as hyperlinks | hack: usage of _global_den.mesiac */
			pom2);
	}
	else if (query_type == PRM_STATIC_TEXT) {
		sprintf(pom, "%s?%s=%s" HTML_AMPERSAND "%s=%s%s",
			script_name,
			STR_QUERY_TYPE, STR_PRM_STATIC_TEXT,
			STR_STATIC_TEXT, skratka_static_text[_global_den.mesiac], /* type of static texts | hack: usage of _global_den.mesiac */
			pom2);
	}

	if (!equals(specific_string_before, STR_EMPTY) && (strlen(specific_string_before) > 0)) {
		Export("%s", specific_string_before);
	}

	if (!equals(html_tag_begin, STR_EMPTY) && (strlen(html_tag_begin) > 0)) {
		Export("<%s>", html_tag_begin);
	}

	// exporting hyperlink
	Export(HTML_A_HREF_BEGIN "\"%s\"", pom);
	if (!equals(html_class, STR_EMPTY) && (strlen(html_class) > 0)) {
		Export(" %s", html_class);
	}
	Export(">");
	if (left_parenthesis > 0) {
		Export("%c", left_parenthesis);
	}
	Export("%s", popis);
	if (right_parenthesis > 0) {
		Export("%c", right_parenthesis);
	}
	Export(HTML_A_END);

	if (!equals(html_tag_end, STR_EMPTY) && (strlen(html_tag_end) > 0)) {
		Export("%s", html_tag_end);
	}

	if (!equals(specific_string_after, STR_EMPTY) && (strlen(specific_string_after) > 0)) {
		Export("%s", specific_string_after);
	}

	Log("_export_link_helper(): koniec.\n");
} // _export_link_helper()

void _export_link_menu_dnes() {
	Log("_export_link_menu_dnes(): začiatok...\n");
	char popis[MAX_STR];

	char pom[MAX_STR];
	mystrcpy(pom, STR_EMPTY, MAX_STR);
	char pom2[MAX_STR];
	mystrcpy(pom2, STR_EMPTY, MAX_STR);
	char pom3[MAX_STR];
	mystrcpy(pom3, STR_EMPTY, MAX_STR);

	// backup of some parameters
	short int local_query_type = query_type;
	short int local_modlitba = _global_modlitba;

	query_type = PRM_DNES;
	_global_modlitba = MODL_NEURCENA;

	mystrcpy(popis, (char*)html_button_Dnes[_global_jazyk], MAX_STR);

	prilep_request_options(pom2, pom3);

	_export_link_helper(pom, pom2, pom3, popis, 
		(char*)STR_EMPTY /* html_tag_begin */, 
		(char*)STR_EMPTY /* html_class */, 
		(char*)STR_EMPTY /* specific_string_before */,
		(char*)STR_EMPTY /* specific_string_after */,
		(char*)STR_EMPTY /* anchor */,
		(char*)STR_EMPTY /* html_tag_end */,
		CHAR_EMPTY /* left_parenthesis */,
		CHAR_EMPTY /* right_parenthesis */
	);

	// restore of some parameters
	query_type = local_query_type;
	_global_modlitba = local_modlitba;

	Log("_export_link_menu_dnes(): koniec.\n");
} // _export_link_menu_dnes()

// funkcia vyexportuje link pre (skryť) / (zobraziť) podľa rozličných nastavení
// kvôli nastaveniam, čo sú formulované "default = zobrazené"; treba vždy zvážiť správne nastavenie vstupných parametrov!
void _export_link_show_hide(short int opt, unsigned long long bit_opt, char popis_show[MAX_STR], char popis_hide[MAX_STR], char html_tag_begin[SMALL], char html_class[SMALL], char specific_string_before[SMALL], char specific_string_after[SMALL], char anchor[SMALL], char html_tag_end[SMALL], char left_parenthesis, char right_parenthesis) {
	Log("_export_link_show_hide(): začiatok...\n");
	char popis[MAX_STR];

	char pom[MAX_STR];
	mystrcpy(pom, STR_EMPTY, MAX_STR);
	char pom2[MAX_STR];
	mystrcpy(pom2, STR_EMPTY, MAX_STR);
	char pom3[MAX_STR];
	mystrcpy(pom3, STR_EMPTY, MAX_STR);

	prilep_request_options(pom2, pom3);

	unsigned long long _global_opt_backup = _global_opt[opt];

	if (isGlobalOption(opt, bit_opt)) {
		mystrcpy(popis, popis_show, MAX_STR);
	}
	else {
		mystrcpy(popis, popis_hide, MAX_STR);

		// špeciálne nastavenia pre BIT_OPT_1_STUP_SVIATOK_SLAVNOST
		if ((opt == OPT_1_CASTI_MODLITBY) && (bit_opt == BIT_OPT_1_STUP_SVIATOK_SLAVNOST) && (!isGlobalOption(opt, BIT_OPT_1_OVERRIDE_STUP_SLAV))) {
			Log("Pre option %d nastavujem bit pre '%ld'\n", opt, BIT_OPT_1_OVERRIDE_STUP_SLAV);
			_global_opt[opt] += BIT_OPT_1_OVERRIDE_STUP_SLAV;
		}
	}

	if (strlen(popis) < 1) {
		Log("_export_link_show_hide(): predčasný koniec (reťazec popis je prázdny).\n");
		return;
	}

	// nastavenie parametra o_opt: pridáme bit pre nastavenie
	if (!isGlobalOption(opt, bit_opt)) {
		Log("Pre option %d nastavujem bit pre '%llu'\n", opt, bit_opt);
		_global_opt[opt] += bit_opt;
	}// zmena: použitie nastavenia
	else {
		Log("Pre option %d ruším bit pre '%llu'\n", opt, bit_opt);
		_global_opt[opt] -= bit_opt;
	}// zmena: zrušenie nastavenia

	_export_link_helper(pom, pom2, pom3, popis, html_tag_begin, html_class, specific_string_before, specific_string_after, anchor, html_tag_end, left_parenthesis, right_parenthesis);

	_global_opt[opt] = _global_opt_backup;

	Log("_export_link_show_hide(): koniec.\n");
} // _export_link_show_hide()

 // funkcia vyexportuje link pre (skryť) / (zobraziť) podľa rozličných nastavení
 // kvôli nastaveniam, čo sú formulované "default = zobrazené"; treba vždy zvážiť správne nastavenie vstupných parametrov!
void _export_link_multi(short int opt, unsigned long long bit_opt, short int count, char popis[MAX_STR], char html_tag_begin[SMALL], char html_class[SMALL], char specific_string_before[SMALL], char specific_string_after[SMALL], char anchor[SMALL], char html_tag_end[SMALL], char left_parenthesis = '(', char right_parenthesis = ')', short int new_value = -1) {
	Log("_export_link_multi(): začiatok...\n");

	char pom[MAX_STR];
	mystrcpy(pom, STR_EMPTY, MAX_STR);
	char pom2[MAX_STR];
	mystrcpy(pom2, STR_EMPTY, MAX_STR);
	char pom3[MAX_STR];
	mystrcpy(pom3, STR_EMPTY, MAX_STR);

	prilep_request_options(pom2, pom3);

	unsigned long long _global_opt_backup = _global_opt[opt];

	if (strlen(popis) < 1) {
		Log("_export_link_multi(): predčasný koniec (reťazec popis je prázdny).\n");
		return;
	}

	if (opt != OPT_6_ALTERNATIVES_MULTI) {
		Log("_export_link_multi(): predčasný koniec (pracuje len pre OPT_6_ALTERNATIVES_MULTI).\n");
		return;
	}

	// get value starting from bit-component bit_opt
	short current_value = isGlobalOption(opt, bit_opt);

	Log("_global_opt(6) == %llu; current value == %d; opt == %d, bit == %llu\n", _global_opt[OPT_6_ALTERNATIVES_MULTI], current_value, opt, bit_opt);

	if ((new_value == -1) || (new_value >= count)) {
		// nastavenie novej hodnoty pre hyperlink (len plus 1)
		current_value = (current_value + 1) MOD count;
	}
	else {
		current_value = new_value;
	}

	setGlobalOption(opt, bit_opt, current_value);

	Log("current value == %d\n", current_value);

	_export_link_helper(pom, pom2, pom3, popis, html_tag_begin, html_class, specific_string_before, specific_string_after, anchor, html_tag_end, left_parenthesis, right_parenthesis);

	_global_opt[opt] = _global_opt_backup;

	Log("_export_link_multi(): koniec.\n");
} // _export_link_multi()

 // funkcia vyexportuje link pre zmenu spoločných textov podľa rozličných nastavení
// kvôli nastaveniam, čo sú formulované "default = zobrazené"; treba vždy zvážiť správne nastavenie vstupných parametrov!
void _export_link_communia(short int spol_cast, char html_tag_begin[SMALL], char html_class[SMALL], char specific_string_before[SMALL], char specific_string_after[SMALL], char anchor[SMALL], char html_tag_end[SMALL]) {
	Log("_export_link_communia(%d) -- začiatok...\n", spol_cast);
	static short int opt = OPT_3_SPOLOCNA_CAST;
	unsigned long long _global_opt_backup = _global_opt[opt];

	char pom[MAX_STR] = STR_EMPTY;
	char pom2[MAX_STR];
	mystrcpy(pom2, STR_EMPTY, MAX_STR);
	char pom3[MAX_STR];
	mystrcpy(pom3, STR_EMPTY, MAX_STR);

	if (spol_cast < 0) {
		Log("ToDo | warning! should not happen!\n");
	}

	// nastavíme spoločnú časť
	if (_global_opt[opt] != (unsigned)spol_cast) {
		Log("Pre option %d nastavujem spoločnú časť na '%d'\n", opt, spol_cast);
		_global_opt[opt] = (unsigned)spol_cast;
	}

	prilep_request_options(pom2, pom3);

	// prilepenie poradia svätca
	if (_global_poradie_svaty > 0) {
		sprintf(pom2, HTML_AMPERSAND"%s=%d", STR_DALSI_SVATY, _global_poradie_svaty);
	}// _global_poradie_svaty > 0
	else {
		mystrcpy(pom2, STR_EMPTY, MAX_STR);
	}// !(_global_poradie_svaty > 0)

	// vytvoríme reťazec s options
	prilep_request_options(pom2, pom3);

	// prilepíme modlitbu
	if (_global_modlitba != MODL_NEURCENA) {
		sprintf(pom3, HTML_LINK_CALL_PARAM, STR_MODLITBA, str_modlitby[_global_modlitba]);
		strcat(pom2, pom3);
	}

	// napokon prilepíme #anchor
	if (!equals(anchor, STR_EMPTY)) {
		sprintf(pom3, "#%s", anchor);
		strcat(pom2, pom3);
	}

	// export hyperlinku
	if (query_type == PRM_DNES) {
		sprintf(pom, "%s?%s=%s%s",
			script_name,
			STR_QUERY_TYPE, STR_PRM_DNES,
			pom2);
	}
	else if (query_type == PRM_DATUM) {
		sprintf(pom, "%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d%s",
			script_name,
			STR_QUERY_TYPE, STR_PRM_DATUM,
			STR_DEN, _global_den.den,
			STR_MESIAC, _global_den.mesiac,
			STR_ROK, _global_den.rok,
			pom2);
	}
	else if (query_type == PRM_LIT_OBD) {
		sprintf(pom, "%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%c%s",
			script_name,
			STR_QUERY_TYPE, STR_PRM_LIT_OBD,
			STR_DEN_V_TYZDNI, _global_den.denvt,
			STR_TYZDEN, _global_den.tyzden,
			STR_LIT_OBD, _global_den.litobd,
			STR_LIT_ROK, _global_den.litrok,
			pom2);
	}
	/* these following query types probably are not used; if used, please check setting of parameters used for sprintf() */
	else if (query_type == PRM_ANALYZA_ROKU) {
		sprintf(pom, "%s?%s=%s" HTML_AMPERSAND "%s=%d%s",
			script_name,
			STR_QUERY_TYPE, STR_PRM_ANALYZA_ROKU,
			STR_ANALYZA_ROKU, _global_den.rok,
			pom2);
	}
	else if (query_type == PRM_TABULKA) {
		sprintf(pom, "%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d%s",
			script_name,
			STR_QUERY_TYPE, STR_PRM_TABULKA,
			STR_ROK_FROM, _global_rok_from,
			STR_ROK_TO, _global_rok_to,
			STR_TABULKA_LINKY, _global_den.mesiac, /* whether to display dates as hyperlinks | hack: usage of _global_den.mesiac */
			pom2);
	}
	else if (query_type == PRM_STATIC_TEXT) {
		sprintf(pom, "%s?%s=%s" HTML_AMPERSAND "%s=%s%s",
			script_name,
			STR_QUERY_TYPE, STR_PRM_STATIC_TEXT,
			STR_STATIC_TEXT, skratka_static_text[_global_den.mesiac], /* type of static texts | hack: usage of _global_den.mesiac */
			pom2);
	}

	Export("%s\n", specific_string_before);
	if (!equals(html_tag_begin, STR_EMPTY)) {
		Export("<%s>\n", html_tag_begin);
	}

	Export(HTML_A_HREF_BEGIN "\"%s\" %s>", pom, html_class);
	Export("(%s)", lowered_nazov_spolc(spol_cast));
	Export(HTML_A_END);

	if (!equals(html_tag_end, STR_EMPTY)) {
		Export("%s\n", html_tag_end);
	}
	Export("%s\n", specific_string_after);

	_global_opt[opt] = _global_opt_backup;
	Log("_export_link_communia(%d) -- koniec.\n", spol_cast);
} // _export_link_communia()

// vypise hlasky o tom, ze je prazdny formular resp. skript bol spusteny bez vstupnych hodnot
void _main_prazdny_formular(void) {
	if (query_type == PRM_XML) {
		ExportXmlError((char*)html_error_no_args[_global_jazyk]);
	}
	else {
		ALERT;
		Export((char *)html_error_no_args[_global_jazyk]);
	}
} // _main_prazdny_formular()

#define DetailLog emptyLog

void export_div_to_continue_tts_voice_output(short int export_comment_begin = ANO) {
	// used both in includeFile() and interpretParameter()
	Export(HTML_P_END "\n"); // end of first verse of psalm/canticle which started <p class="verse...">
	Export(HTML_DIV_END "\n"); // end of <div class="psalm"> which is in each psalm/canticle
	Export(HTML_DIV_END "\n"); // end of HTML_DIV_RUBRIC added above
	Export("<" HTML_DIV_PSALM ">" "\n" HTML_P_VERSE_CONT "\n"); // synthetic begin of psalm + verse
	if (export_comment_begin == ANO) {
		Export(HTML_COMMENT_BEGIN);
	}
}// export_div_to_continue_tts_voice_output()

void export_tts_pause(short int tts_pause_type = TTS_PAUSE) {
	DetailLog("exporting TTS pause...\n");

	Export("\n");

	if (tts_pause_type == TTS_PAUSE) {
		Export("<" HTML_SPAN_TTS_PAUSE ">");
	}
	else if (tts_pause_type == TTS_PAUSE_SHORT) {
		Export("<" HTML_SPAN_TTS_PAUSE_SHORT ">");
	}
	else if (tts_pause_type == TTS_PAUSE_LONG) {
		Export("<" HTML_SPAN_TTS_PAUSE_LONG ">");
	}

	Export(HTML_SPAN_END "\n");
}// export_tts_pause()

#define MAX_ZAKONCENIE 200

#define EXPORT_FOOTNOTES ANO
#define EXPORT_FULL_TEXT (!vnutri_full_text || useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZALMY_FULL_TEXT))
#define EXPORT_REFERENCIA ((!vnutri_myslienky || je_myslienka) && (!vnutri_nadpisu || je_nadpis) && (!(vnutri_footnote || vnutri_note) || useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_FOOTNOTES)))
// export red and normal stuff = export asterisks & crosses (psalmody, responsories)
#define EXPORT_RED_AND_NORMAL_STUFF(modlitba) (!(isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT)) && (write == ANO))
#define EXPORT_RED_TRIANGLE ((!(isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT))) && (!(isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_SLAVA_OTCU))))
#define EXPORT_VERSE_NUMBER (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VERSE) && (EXPORT_FULL_TEXT))
#define EXPORT_TTS_PAUSES (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT) && (write == ANO))
#define EXPORT_TTS_SECTIONS (_global_skip_in_prayer == NIE)

#define je_velkonocna_nedela_posv_cit (((equals(paramname, PARAM_CITANIE1)) || (equals(paramname, PARAM_CITANIE2))) && (_global_den.denvr = VELKONOCNA_NEDELA) && (_global_modlitba == MODL_POSV_CITANIE))

short int antifona_pocet = 0; // počet antifón (ant1, ant2, ant3 pre psalmódiu a ant. na benediktus/magnifikat kvôli krížikom)
char rest_krizik[MAX_BUFFER] = STR_EMPTY; // pre to, čo je za krížikom v antifóne
char rest_zakoncenie[MAX_BUFFER] = STR_EMPTY;
short int ant_invitat_krizik = 0; // antifóna pre invitatórium s krížikom

struct ReadBuffer {
	ReadBuffer() : pos(0), size(0) {}

	size_t pos;
	size_t size;
	char data[READ_BUFFER];
};

bool LoadToBuffer(FILE* stream, struct ReadBuffer* buffer) {
	while (buffer->pos >= buffer->size) {
		size_t new_size = fread(buffer->data, 1, sizeof(buffer->data), stream);
		if (new_size <= 0) {
			if (errno == EINTR) continue;
			return false;
		}
		buffer->pos = 0;
		buffer->size = new_size;
	}
	return true;
}

// Assumes that buffer is loaded.
char ConsumeFromBuffer(struct ReadBuffer* buffer) {
  return buffer->data[buffer->pos++];
}

#define ExportHtmlOnly(a) { if (typ != PRM_XML) { Export(a); } }

#define ExportHtmlOnlyFormat(a, b) { if (typ != PRM_XML) { Export(a, b); } }

void includeFile(short int typ, short int modlitba, const char* paramname, const char* fname, const char* modlparam) {
	int c, buff_index = 0, fnref_index = 0, fn_index = 0, ref_index = 0, kat_index = 0, z95_index = 0;
	char strbuff[MAX_BUFFER];
	char rest[MAX_BUFFER];
	char isbuff = 0;
	short int write = NIE;
	short int je_antifona = NIE;
	short int write_krizik = NIE;
	short int je_modlitba = NIE;

	char vnutri_inkludovaneho = 0; // kvôli "V.O. Aleluja" v inkludovaných napr. antifónach
	char zakoncenie[MAX_ZAKONCENIE]; // zakončenie s veľkým písmenkom na začiatku, následne sa prípadne mení 1. písmeno na malé

	short int vnutri_referencie = NIE; // PARAM_REFERENCIA... | kvôli biblickým referenciám v inkludovaných súboroch
	short int vnutri_katechezy = NIE; // PARAM_KATECHEZA... | kvôli odkazom na katechézy v inkludovaných súboroch
	short int vnutri_z95 = NIE; // PARAM_LINK_ZALM95... | kvôli odkazu na modlitbu so žalmom 95
	short int vnutri_footnote_ref = NIE; // PARAM_FOOTNOTE_REF...
	short int vnutri_footnote = NIE; // PARAM_FOOTNOTE...
	short int vnutri_note = NIE; // PARAM_NOTE...
	short int vnutri_full_text = NIE;

	short int vnutri_myslienky = NIE; // kvôli myšlienkam k žalmom, ktoré v sebe vnútri môžu obsahovať biblickú referenciu
	short int vnutri_nadpisu = NIE; // kvôli nadpisu pre psalmódiu
	short int je_myslienka = NIE; // či sa má myšlienka vkladať alebo nie
	short int je_nadpis = NIE; // či sa má nadpis pre psalmódiu vkladať alebo nie

	char fnrefbuff[MAX_BUFFER]; // buffer for footnote reference
	char fnrefrest[MAX_BUFFER];

	char fnbuff[MAX_BUFFER]; // buffer for footnote reference
	char fnrest[MAX_BUFFER];

	char refbuff[MAX_BUFFER]; // buffer pre referenciu
	char refrest[MAX_BUFFER]; // 'rest' uložené zo začiatku referencie (používa sa až pri parsovaní konca referencie)
	char reference[MAX_BUFFER]; // full reference

	char katbuff[MAX_BUFFER]; // buffer pre odkaz na katechézu
	char katrest[MAX_BUFFER]; // 'rest' uložené zo začiatku odkazu na katechézu (používa sa až pri parsovaní konca odkazu na katechézu)

	char z95buff[MAX_BUFFER]; // buffer pre odkaz na ž95
	char z95rest[MAX_BUFFER]; // 'rest' uložené zo začiatku odkazu na ž 95

	Log("--includeFile(%d, %d, %s, %s, %s): begin,\n", typ, modlitba, paramname, fname, modlparam);

	short int isMobileOS;

#if defined(IO_ANDROID) || defined (__APPLE__)
	isMobileOS = 1;
#else
	isMobileOS = 0;
#endif

	// nasledovné sú potrebné pre hyperlink v texte modlitby s prípadne upravenými parametrami
#ifdef BEHAVIOUR_WEB
	unsigned long long _global_opt_1_casti_modlitby_orig; // parameter o1 (_global_opt 1) pre modlitbu cez deň (doplnková psalmódia)
#endif

	char pom[MAX_STR];
	mystrcpy(pom, STR_EMPTY, MAX_STR);
	char pompom[MAX_STR];
	mystrcpy(pompom, STR_EMPTY, MAX_STR);

	Log("  replacing {%s} with %s from file `%s':\n", paramname, modlparam, fname);

	if ((_global_skip_in_prayer >= ANO) || (_global_skip_in_prayer_vnpc == ANO)) {
		Log("--includeFile(): end (because _global_skip_in_prayer >= ANO || _global_skip_in_prayer_vnpc == ANO)\n");
		return;
	}

	// init
	mystrcpy(strbuff, STR_EMPTY, MAX_BUFFER);
	mystrcpy(rest, STR_EMPTY, MAX_BUFFER);
	mystrcpy(refbuff, STR_EMPTY, MAX_BUFFER);
	mystrcpy(refrest, STR_EMPTY, MAX_BUFFER);
	mystrcpy(reference, STR_EMPTY, MAX_BUFFER);
	mystrcpy(katbuff, STR_EMPTY, MAX_BUFFER);
	mystrcpy(katrest, STR_EMPTY, MAX_BUFFER);
	mystrcpy(z95buff, STR_EMPTY, MAX_BUFFER);
	mystrcpy(z95rest, STR_EMPTY, MAX_BUFFER);

	ant_invitat_krizik = 0;

	FILE *body = fopen(fname, "r");

	if (body == NULL) {
		// printf("error `%s'\n", sys_errlist[errno]);
		Log("  file `%s' not found\n", fname);
#if defined(EXPORT_HTML_FILENAME_ANCHOR)
		Export("file `%s' not found (anchor `%s')", fname, modlparam);
#elif defined(EXPORT_HTML_FILENAME)
		Export("file `%s' not found", fname);
#else
		Export("file not found");
#endif
		Log("--includeFile(): end (because of no body)\n");
		return;
	}

#if defined(EXPORT_HTML_FILENAME_ANCHOR)
	Export("(file `%s', anchor `%s')", fname, modlparam);
#elif defined(EXPORT_HTML_FILENAME)
	Export("(file `%s')", fname);
#elif defined(EXPORT_HTML_ANCHOR)
	Export("(anchor `%s')", modlparam);
#endif

	// nastavenie toho, či sa má zobrazovať myšlienka k žalmom/chválospevom | doplnené aj nastavenie pre zobrazenie nadpisu pre žalm/chválospev (zatiaľ rovnako ako pre myšlienku)
	// orig: if ((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT)) || _je_global_den_slavnost || _je_global_den_sviatok || (_global_den.typslav == SLAV_VLASTNE) || (_global_den.litobd == OBD_VELKONOCNA_OKTAVA) || (_global_den.smer == 1) && (_global_den.spolcast != _encode_spol_cast(MODL_SPOL_CAST_NEURCENA))) {
	// last part was commented
	// 2017-10-13: nevidím dôvod, prečo by sa to nemalo zobrazovať vždy OKREM výstupu pre TTS (voice output)
	if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT)) {
		je_myslienka = NIE;
		je_nadpis = NIE;
	}
	else {
		je_myslienka = ANO;
		je_nadpis = ANO;
	}
	Log("nastavil som je_myslienka == %d\n", je_myslienka);
	Log("nastavil som je_nadpis == %d\n", je_nadpis);

	// 2011-09-30: bod č. 114 všeobecných smerníc: "V ofíciu v Cezročnom období, ak sa nespievajú, možno namiesto týchto antifón použiť — ak je to vhodné — myšlienky pripojené k žalmom."
	/* zatiaľ zapoznámkované, lebo jedna vec je zobrazovať to, druhá vec možnosť použiť ako antifónu -- zobrazujeme podľa tlačenej LH
	if (_global_den.litobd != OBD_CEZ_ROK) {
		je_myslienka = NIE;
		Log("upravil som je_myslienka == %d (nie je cezročné obdobie)\n", je_myslienka);
	}
	*/

	struct ReadBuffer readbuff;
	struct Utf8DecoderState state;
	InitUtf8DecoderState(&state);

	while (1) {
		if (!LoadToBuffer(body, &readbuff)) break;
		if (!Utf8StreamingDecoder(ConsumeFromBuffer(&readbuff), &state)) continue;
		c = state.result;
		// Export("inside[%c]...", c);
		switch (c) {

		case CHAR_KEYWORD_BEGIN:

			// ak sa nachádza znak CHAR_KEYWORD_BEGIN (t. j. '{') len tak voľne v texte, program zblbol; nevedel zistiť, či ide o keyword alebo nie; pokus o opravu
			DetailLog("CHAR_KEYWORD_BEGIN");

			isbuff = 1;
			buff_index = 0;

			continue;

		case CHAR_KEYWORD_END:

			DetailLog("CHAR_KEYWORD_END");

			isbuff = 0;
			strbuff[buff_index] = '\0';
			DetailLog("\nFile %s, \n\tparam {%s} found\n", fname, strbuff);
			mystrcpy(rest, strbuff, MAX_BUFFER);
			splitword(strbuff, rest, CHAR_KEYWORD_DIVIDER);
			DetailLog("\tstrbuff  == %s\n", strbuff);
			DetailLog("\trest     == %s\n", rest);
			DetailLog("\tmodlparam== %s\n", modlparam);

			// Export("[INPUT:paramname=%s|fname=%s|modlparam=%s|READ:strbuff=%s|rest=%s]", paramname, fname, modlparam, strbuff, rest);

			if (equalsi(rest, modlparam)) {
#if defined(EXPORT_HTML_SPECIALS)
				Export("[%s|%s:%s]", fname, strbuff, modlparam);
#endif
				if (equals(strbuff, INCLUDE_BEGIN)) {
					write = ANO;
					vnutri_inkludovaneho = ANO;
				}// INCLUDE_BEGIN
				else if (equals(strbuff, INCLUDE_END)) {
					write = NIE;
					vnutri_inkludovaneho = NIE;
					// multiple includes
					Export("--><!--");
					// ak to aj je posledny inklude, potom v nadradenom subore, do ktoreho "inkludujeme", sa vypise "-->"
				}// INCLUDE_END
				Log("[%s|%s:%s]", fname, strbuff, modlparam);
			}// equalsi(rest, modlparam)

			else if (equals(strbuff, PARAM_KRIZIK)) {

				if ((vnutri_inkludovaneho == ANO) && (write == ANO)) {

					// Export("[INPUT:paramname=%s|fname=%s|modlparam=%s|READ:strbuff=%s|rest=%s]", paramname, fname, modlparam, strbuff, rest);
					if (equals(paramname, PARAM_ANTIFONA1) || equals(paramname, PARAM_ANTIFONA2) || equals(paramname, PARAM_ANTIFONA3) || equals(paramname, PARAM_ANTRCHVAL) || equals(paramname, PARAM_ANTVCHVAL) || equals(paramname, PARAM_ANTIFONA1x) || equals(paramname, PARAM_ANTIFONA3x)) {
						je_antifona = ANO;
						if (/* rest != NULL && */ strlen(rest) > 0) {
							mystrcpy(rest_krizik, rest, MAX_BUFFER);
						}
						// Export("antifóna[%d] -> zapamätám, ku ktorému žalmu/chválospevu patrí...\n", antifona_pocet);
					}// krížik v antifóne

					// ToDo odlíšiť, že ide o invitatórium
					if (equals(paramname, PARAM_ANTIFONA1)) {
						ant_invitat_krizik = 1;
					}

#if defined(EXPORT_HTML_SPECIALS)
					Export("[%s:%s|rest_krizik=%s]", strbuff, modlparam, (rest_krizik == NULL) ? STR_EMPTY : rest_krizik);
#endif

					// krížik v texte includovaného žalmu/chválospevu
					if ((je_antifona == ANO) || (equals(paramname, PARAM_ZALM1) || equals(paramname, PARAM_ZALM2) || equals(paramname, PARAM_ZALM3) || equals(paramname, PARAM_RCHVALOSPEV) || equals(paramname, PARAM_VCHVALOSPEV))) {
						write_krizik = ANO;
						if ((je_antifona == ANO) && ((antifona_pocet MOD 2) == 0)) {
							// krížik sa vypisuje len v počiatočných (nepárnych) antifónach (pre modlitbu cez deň sa nevyskytuje, ani v silných obdobiach)
							Log("-párna antifóna-");
							write_krizik = NIE;
						}
						if ((je_antifona == ANO) && (antifona_pocet > 1) && (_global_modlitba == MODL_INVITATORIUM)) {
							// pre invitatórium sa antifóna opakuje... krížik sa vypisuje len na začiatku
							Log("-párna antifóna-");
							write_krizik = NIE;
						}
						/*
						 * môže nastať situácia, že antifóna má v sebe krížik, ale nasleduje taký žalm/chválospev, ktorý tam ten verš nemá?
						 * pre žaltár sa to asi nemôže stať, ale pre voliteľné napr. spomienky (keď si vezme iné žalmy), by sa to teoreticky stať mohlo...
						 * potom treba vyšpecifikovať podmienku, ktorá bude kontrolovať: ak je to antifóna 1, treba porovnať, či equals(rest_krizik, "_global_modl_...".zalm1.anchor) a pod.
						 * case pre danú modlitbu: pre MODL_RANNE_CHVALY: _global_modl_ranne_chvaly.zalm1.anchor; pre iné modlitby iný "_global_modl_..."

						 if ((je_antifona == ANO) && ((antifona_pocet MOD 2) == 1) && (-- zložitá podmienka --)) {
							 // krížik sa vypisuje v počiatočných (nepárnych) antifónach len vtedy, ak nasledujúci žalm/chválospev je ten zodpovedajúci
							 Log("-nepárna antifóna/iný žalm-");
							 write_krizik = NIE;
						 }
						 */
						if ((je_antifona == NIE) && !equals(modlparam, rest_krizik)) {
							// krížik sa v žalmoch/chválospevoch vypisuje len v prípade, že predtým (v načítanej antifóne) bolo správne uvedené, ku ktorému žalmu sa to vzťahuje
							Log("-iný žalm-");
							write_krizik = NIE;
						}
						if (write_krizik == ANO) {
							Export(HTML_COMMENT_END);
							if (je_antifona == ANO) {
								ExportNonbreakingSpace(); // pre krížik na začiatku žalmu/chválospevu medzeru netreba
							}
							Export("<" HTML_SPAN_RED ">" STR_CROSS "" HTML_SPAN_END);
							if (je_antifona != ANO) {
								ExportNonbreakingSpace(); // pre krížik na konci chválospevu medzeru netreba
							}
							Export(HTML_COMMENT_BEGIN);
						}

						if ((write_krizik == ANO) && (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT))) {

							Export(HTML_COMMENT_END "\n");

							if (je_antifona == ANO) {
								// stop exporting text for TTS (voice output); add TTS pause
								Export((_global_jazyk == JAZYK_HU) ? HTML_DIV_END : HTML_P_END); // HU uses <div class="antiphon ...">; end of antiphone

								export_tts_pause();

								Export(HTML_DIV_RUBRIC "\n"); // hide the rest of antiphone with beginning of psalm/canticle until the first verse's red cross

								Export((_global_jazyk == JAZYK_HU) ? HTML_DIV_BEGIN : HTML_P_BEGIN); // HU uses <div class="antiphon ...">; synthetic begin of antiphone

								Export(HTML_COMMENT_BEGIN); // must be added because 'end of antiphone' include follows
							}
							else {
								// continue exporting text for TTS (voice output)
								export_div_to_continue_tts_voice_output();
							}
						}//  do not repeat the same text for voice output (TTS)
					}// krížik v texte includovaného žalmu/chválospevu
				}// vypísať krížik, nakoľko antifóna nastavila, že má byť; ináč nerob nič
			}// PARAM_KRIZIK

			// doplnková psalmódia, alternatívne žalmy
			else if ((equals(strbuff, PARAM_DOPLNK_PSALM_122_129)) || (equals(strbuff, PARAM_DOPLNK_PSALM_127_131)) || (equals(strbuff, PARAM_DOPLNK_PSALM_126_129)) || (equals(strbuff, PARAM_OFF_DEF_PSALM_146_150))) {
				if ((vnutri_inkludovaneho == ANO) && (write == ANO)) {
					Log("(if ((equals(strbuff, PARAM_DOPLNK_PSALM_...)): _global_opt[OPT_2_HTML_EXPORT] & BIT_OPT_2_ROZNE_MOZNOSTI == %ld: (doplnková psalmódia, alternatívne žalmy)\n", _global_opt[OPT_2_HTML_EXPORT] & BIT_OPT_2_ROZNE_MOZNOSTI);

					long bit;
					short int opt = OPT_5_ALTERNATIVES;
					short int nastavene = NIE;

					char popis_show[SMALL];
					char popis_hide[SMALL];
					mystrcpy(popis_show, html_text_option_zobrazit[_global_jazyk], SMALL);
					mystrcpy(popis_hide, html_text_option_skryt[_global_jazyk], SMALL);

					char specific_string[SMALL];
					mystrcpy(specific_string, STR_EMPTY, SMALL);

					char anchor[SMALL];
					mystrcpy(anchor, STR_EMPTY, SMALL);

					short int podmienka = (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI)); // len ak je táto možnosť (zobrazovanie všeličoho) zvolená
					podmienka = podmienka && (_global_skip_in_prayer == NIE);

					if (equals(strbuff, PARAM_DOPLNK_PSALM_122_129)) {
						podmienka = podmienka && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES)); // len ak je táto možnosť (zobrazovanie alternatívy) zvolená
						podmienka = podmienka && (je_alternativa_doplnkova_psalmodia_z122_129(_global_modlitba));
						mystrcpy(specific_string, HTML_P_BEGIN, SMALL);
						bit = BIT_OPT_5_DOPLNK_PSALM_122_129;
						sprintf(popis_show, "%s", html_text_opt_5_DPsalmZ122_NORMAL[_global_jazyk]);
						sprintf(popis_hide, "%s", html_text_opt_5_DPsalmZ122_129[_global_jazyk]);
						mystrcpy(anchor, (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_DOPLNK_PSALM_122_129)) ? PARAM_ZALM122 : PARAM_ZALM129, SMALL);
						nastavene = ANO;
					}
					if (!nastavene && equals(strbuff, PARAM_DOPLNK_PSALM_126_129)) {
						podmienka = podmienka && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES)); // len ak je táto možnosť (zobrazovanie alternatívy) zvolená
						podmienka = podmienka && (je_alternativa_doplnkova_psalmodia_z126_129(_global_modlitba));
						mystrcpy(specific_string, HTML_P_BEGIN, SMALL);
						bit = BIT_OPT_5_DOPLNK_PSALM_126_129;
						sprintf(popis_show, "%s", html_text_opt_5_DPsalmZ126_NORMAL[_global_jazyk]);
						sprintf(popis_hide, "%s", html_text_opt_5_DPsalmZ126_129[_global_jazyk]);
						mystrcpy(anchor, (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_DOPLNK_PSALM_126_129)) ? PARAM_ZALM126 : PARAM_ZALM129, SMALL);
						nastavene = ANO;
					}
					if (!nastavene && equals(strbuff, PARAM_DOPLNK_PSALM_127_131)) {
						podmienka = podmienka && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES)); // len ak je táto možnosť (zobrazovanie alternatívy) zvolená
						podmienka = podmienka && (je_alternativa_doplnkova_psalmodia_z127_131(_global_modlitba));
						mystrcpy(specific_string, HTML_P_BEGIN, SMALL);
						bit = BIT_OPT_5_DOPLNK_PSALM_127_131;
						sprintf(popis_show, "%s", html_text_opt_5_DPsalmZ127_NORMAL[_global_jazyk]);
						sprintf(popis_hide, "%s", html_text_opt_5_DPsalmZ127_131[_global_jazyk]);
						mystrcpy(anchor, (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_DOPLNK_PSALM_127_131)) ? PARAM_ZALM127 : PARAM_ZALM131, SMALL);
						nastavene = ANO;
					}
					if (!nastavene && equals(strbuff, PARAM_OFF_DEF_PSALM_146_150)) {
						podmienka = podmienka && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES)); // len ak je táto možnosť (zobrazovanie alternatívy) zvolená
						podmienka = podmienka && (je_alternativa_off_def_z146_150(_global_modlitba));
						mystrcpy(specific_string, HTML_P_BEGIN, SMALL);
						bit = BIT_OPT_5_OFF_DEF_PSALM_146_150;
						sprintf(popis_show, "%s", html_text_opt_5_OffDefZ146_150_NORMAL[_global_jazyk]);
						sprintf(popis_hide, "%s", html_text_opt_5_OffDefZ146_150[_global_jazyk]);
						mystrcpy(anchor, (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_OFF_DEF_PSALM_146_150)) ? PARAM_ZALM146 : PARAM_ZALM150, SMALL);
						nastavene = ANO;
					}

					// má zmysel len ak platí daná podmienka
					if (podmienka) {
						Log("includeFile: including %s\n", paramname);
						Export("%s:begin-->", paramname);

						char before[SMALL] = STR_EMPTY;
						sprintf(before, HTML_P_CENTER_SMALL);
						char after[SMALL] = STR_EMPTY;
						mystrcpy(after, HTML_P_END, SMALL);
						_export_link_show_hide(opt, bit, popis_show, popis_hide, (char *)HTML_SPAN_RED_SMALL, (char *)HTML_CLASS_QUIET, specific_string, (char *)STR_EMPTY, anchor, (char *)HTML_SPAN_END);

						Export("<!--%s:end", paramname);
					}
					else {
						ExportHtmlOnlyFormat("[skipping %s]", paramname);
						Log("skipping %s\n", paramname);
					}
				}// ináč nerob nič
			}// PARAM_DOPLNK_PSALM_122_129 || PARAM_DOPLNK_PSALM_127_131 || PARAM_DOPLNK_PSALM_126_129 || PARAM_OFF_DEF_PSALM_146_150

			// zakončenie v texte includovanej modlitby
			else if (equals(strbuff, PARAM_ZAKONCENIE)) {
				if ((vnutri_inkludovaneho == ANO) && (write == ANO)) {
					// Export("[INPUT:paramname=%s|fname=%s|modlparam=%s|READ:strbuff=%s|rest=%s]", paramname, fname, modlparam, strbuff, rest);
					if ((equals(paramname, PARAM_MODLITBA)) || (equals(paramname, PARAM_MODL_SPOMPRIVILEG)) || (je_velkonocna_nedela_posv_cit)) {

						// pre ranné chvály a vešpery, ak sa pridáva 'modlitba' pre spomienku v privilegované dni, tak zakončenie sa dáva až pre PARAM_MODL_SPOMPRIVILEG
						if ((equals(paramname, PARAM_MODLITBA)) && (je_modl_spomprivileg)) {
							je_modlitba = !(_global_modlitba == MODL_RANNE_CHVALY || _global_modlitba == MODL_VESPERY);
						}
						else if (equals(paramname, PARAM_MODL_SPOMPRIVILEG)) {
							je_modlitba = ANO;
						}
						else {
							je_modlitba = ANO;
						}

						if (/* rest != NULL && */ strlen(rest) > 0) {
							mystrcpy(rest_zakoncenie, rest, MAX_BUFFER);
						}
					}
#if defined(EXPORT_HTML_SPECIALS)
					Export("[%s:%s|rest_zakoncenie=%s]", strbuff, modlparam, (rest_zakoncenie == NULL) ? STR_EMPTY : rest_zakoncenie);
#endif
					if ((je_modlitba == ANO) && ((equals(paramname, PARAM_MODLITBA)) || (equals(paramname, PARAM_MODL_SPOMPRIVILEG)) || (je_velkonocna_nedela_posv_cit))) {
						Export("%s--> ", /* (rest_zakoncenie == NULL) ? STR_EMPTY : */ rest_zakoncenie);
						if (equals(rest_zakoncenie, PARAM_ZAKONCENIE_SKRZE) || equals(rest_zakoncenie, PARAM_ZAKONCENIE_SKRZE_MALE)) {
							if (je_modlitba_cez_den(_global_modlitba) || je_kompletorium12(_global_modlitba) || (je_velkonocna_nedela_posv_cit)) {
								mystrcpy(zakoncenie, text_ZAKONCENIE_SKRZE_kratke[_global_jazyk], MAX_ZAKONCENIE);
							}
							else {
								mystrcpy(zakoncenie, text_ZAKONCENIE_SKRZE_dlhe[_global_jazyk], MAX_ZAKONCENIE);
							}
						} // ZAKONCENIE_SKRZE
						else if (equals(rest_zakoncenie, PARAM_ZAKONCENIE_LEBO_TY) || equals(rest_zakoncenie, PARAM_ZAKONCENIE_LEBO_TY_MALE)) {
							if (je_modlitba_cez_den(_global_modlitba) || je_kompletorium12(_global_modlitba) || (je_velkonocna_nedela_posv_cit)) {
								mystrcpy(zakoncenie, text_ZAKONCENIE_LEBO_TY_kratke[_global_jazyk], MAX_ZAKONCENIE);
							}
							else {
								mystrcpy(zakoncenie, text_ZAKONCENIE_LEBO_TY_dlhe[_global_jazyk], MAX_ZAKONCENIE);
							}
						} // ZAKONCENIE_LEBO_TY
						else if (equals(rest_zakoncenie, PARAM_ZAKONCENIE_LEBO_ON) || equals(rest_zakoncenie, PARAM_ZAKONCENIE_LEBO_ON_MALE)) {
							if (je_modlitba_cez_den(_global_modlitba) || je_kompletorium12(_global_modlitba) || (je_velkonocna_nedela_posv_cit)) {
								mystrcpy(zakoncenie, text_ZAKONCENIE_LEBO_ON_kratke[_global_jazyk], MAX_ZAKONCENIE);
							}
							else {
								mystrcpy(zakoncenie, text_ZAKONCENIE_LEBO_ON_dlhe[_global_jazyk], MAX_ZAKONCENIE);
							}
						} // ZAKONCENIE_LEBO_ON
						else if (equals(rest, PARAM_ZAKONCENIE_ON_JE) && _global_jazyk == JAZYK_SK) {
							if (je_modlitba_cez_den(_global_modlitba) || je_kompletorium12(_global_modlitba) || (je_velkonocna_nedela_posv_cit)) {
								mystrcpy(zakoncenie, text_SK_ZAKONCENIE_ON_JE_kratke, MAX_ZAKONCENIE);
							}
							else {
								mystrcpy(zakoncenie, text_SK_ZAKONCENIE_ON_JE_dlhe, MAX_ZAKONCENIE);
							}
						} // SK: ZAKONCENIE_ON_JE
						else if ((equals(rest, PARAM_ZAKONCENIE_KTORY_JE) || equals(rest_zakoncenie, PARAM_ZAKONCENIE_KTORY_JE_MALE))
							&& (_global_jazyk == JAZYK_SK || _global_jazyk == JAZYK_IS)) {
							if (je_modlitba_cez_den(_global_modlitba) || je_kompletorium12(_global_modlitba) || (je_velkonocna_nedela_posv_cit)) {
								mystrcpy(zakoncenie, (_global_jazyk == JAZYK_SK) ? text_SK_ZAKONCENIE_KTORY_JE_kratke : text_IS_ZAKONCENIE_KTORY_JE_kratke, MAX_ZAKONCENIE);
							}
							else {
								mystrcpy(zakoncenie, (_global_jazyk == JAZYK_SK) ? text_SK_ZAKONCENIE_KTORY_JE_dlhe : text_IS_ZAKONCENIE_KTORY_JE_dlhe, MAX_ZAKONCENIE);
							}
						} // SK + IS: ZAKONCENIE_KTORY_JE
						else if (equals(rest, PARAM_ZAKONCENIE_KTORY_ZIJES) && _global_jazyk == JAZYK_IS) {
							if (je_modlitba_cez_den(_global_modlitba) || je_kompletorium12(_global_modlitba) || (je_velkonocna_nedela_posv_cit)) {
								mystrcpy(zakoncenie, text_IS_ZAKONCENIE_KTORY_ZIJES_kratke, MAX_ZAKONCENIE);
							}
							else {
								mystrcpy(zakoncenie, text_IS_ZAKONCENIE_KTORY_ZIJES_dlhe, MAX_ZAKONCENIE);
							}
						} // IS: ZAKONCENIE_KTORY_ZIJES
						else if (equals(rest_zakoncenie, PARAM_ZAKONCENIE_O_TO_TA_PROSIME)) {
							mystrcpy(zakoncenie, text_ZAKONCENIE_O_TO_TA_PROSIME[_global_jazyk], MAX_ZAKONCENIE);
						} // PARAM_ZAKONCENIE_O_TO_TA_PROSIME

						if (equals(rest_zakoncenie, PARAM_ZAKONCENIE_SKRZE_MALE) || equals(rest_zakoncenie, PARAM_ZAKONCENIE_LEBO_TY_MALE) || equals(rest_zakoncenie, PARAM_ZAKONCENIE_LEBO_ON_MALE) || equals(rest_zakoncenie, PARAM_ZAKONCENIE_KTORY_JE_MALE)) {
							FirstToLower(zakoncenie, sizeof(zakoncenie));  // posun z veľkého písmena na malé
						}
						// nezlomiteľné medzery
						Export("%s", convert_nonbreaking_spaces(zakoncenie));
						Export("<!--%s", /* (rest_zakoncenie == NULL) ? STR_EMPTY : */ rest_zakoncenie);
						je_modlitba = NIE;
					}
				}// vypísať zakončenie
			}// PARAM_ZAKONCENIE

			else {
				// !equalsi(rest, modlparam)
				// write = NIE; -- aby mohli byt nestovane viacere :-)
				DetailLog("parameter does not match: %s != %s; vnutri_inkludovaneho == %d\n", rest, modlparam, vnutri_inkludovaneho);

// stuff in texts: TTS pause
				if ((equals(strbuff, PARAM_PAUSE)
					|| equals(strbuff, PARAM_PAUSE_SHORT)
					) && (vnutri_inkludovaneho == ANO))
				{
					if (EXPORT_TTS_PAUSES) {
						export_tts_pause(equals(strbuff, PARAM_PAUSE) ? TTS_PAUSE : TTS_PAUSE_SHORT); // ToDo: TTS_PAUSE_LONG
					}
				}// normal (black) stuff

// normal (black) stuff in psalmody (cross, asterisk)
				if ((equals(strbuff, PARAM_NORMAL_ASTERISK)
					|| equals(strbuff, PARAM_NORMAL_CROSS)
					) && (vnutri_inkludovaneho == ANO))
				{
					DetailLog("exporting normal stuff with nbsp before...\n");

					if (EXPORT_RED_AND_NORMAL_STUFF(_global_modlitba)) {
						ExportNonbreakingSpace();
					}

					if (equals(strbuff, PARAM_NORMAL_ASTERISK)) {
						if (EXPORT_TTS_PAUSES) {
							Export("<" HTML_SPAN_TTS_PAUSE ">");
						}
						if (EXPORT_RED_AND_NORMAL_STUFF(_global_modlitba)) {
							Export(STR_ASTERISK);
						}
					}
					else if (equals(strbuff, PARAM_NORMAL_CROSS)) {
						if (EXPORT_TTS_PAUSES) {
							Export("<" HTML_SPAN_TTS_PAUSE_SHORT ">");
						}
						if (EXPORT_RED_AND_NORMAL_STUFF(_global_modlitba)) {
							Export(STR_CROSS);
						}
					}

					if (EXPORT_TTS_PAUSES) {
						Export(HTML_SPAN_END);
					}
				}// normal (black) stuff

// red asterisk, red cross, other "red stuff"
				if ((equals(strbuff, PARAM_RED_ASTERISK)
					|| equals(strbuff, PARAM_RED_CROSS)
					) && (vnutri_inkludovaneho == ANO))
				{
					DetailLog("exporting red stuff...\n");
					if (EXPORT_RED_AND_NORMAL_STUFF(_global_modlitba)) {
						Export("<" HTML_SPAN_TTS_PAUSE_RED ">%s" HTML_SPAN_END, strbuff);
					}
				}// red stuff

// red triangle (end of psalm/canticle when doxology is not displayed)
				if (equals(strbuff, PARAM_RED_TRIANGLE) && (vnutri_inkludovaneho == ANO)) {
					DetailLog("exporting red triangle with nbsp before...\n");
					if (EXPORT_RED_TRIANGLE) {
						ExportNonbreakingSpace();
						Export("<" HTML_SPAN_TTS_PAUSE_RED ">%s" HTML_SPAN_END, strbuff);
					}
				}// PARAM_RED_TROJUHOLNIK

// footnote references
				// upraviť footnote referencie na hyperlinky
				if (equals(strbuff, PARAM_FOOTNOTE_REF_BEGIN) && (vnutri_inkludovaneho == ANO)) {
					vnutri_footnote_ref = ANO;
					write = NIE;
					fnref_index = 0;
					if (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_FOOTNOTES)) {
						/* if (rest != NULL) */ mystrcpy(fnrefrest, rest, MAX_BUFFER);
						DetailLog("\trest      == %s\n", rest);
						DetailLog("\tfnrefrest == %s\n", fnrefrest);
					}
				}// upraviť footnote referencie na hyperlinky -- PARAM_FOOTNOTE_REF_BEGIN
				if (equals(strbuff, PARAM_FOOTNOTE_REF_END) && (vnutri_inkludovaneho == ANO)) {
					fnrefbuff[fnref_index] = '\0';

					if (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_FOOTNOTES)) {
						if (EXPORT_FOOTNOTES) {
							Export(HTML_A_HREF_BEGIN "\"#fn");
						}
						DetailLog("\trest      == %s\n", rest);
						DetailLog("\tfnrefrest == %s\n", fnrefrest);
						if (/* (fnrefrest != NULL) &&  */!(equals(fnrefrest, STR_EMPTY))) {
							if (EXPORT_FOOTNOTES) {
								Export("%s", convert_nonbreaking_spaces(fnrefrest));
							}
						}
						if (EXPORT_FOOTNOTES) {
							Export("%s\" " HTML_CLASS_WITHOUT_BORDER ">", fnrefbuff);
							Export("<sup>%s</sup>", fnrefbuff);
							Export(HTML_A_END);
						}
					}
					vnutri_footnote_ref = NIE;

					if (EXPORT_FOOTNOTES) {
						write = ANO;
					}
					strcpy(fnrefrest, STR_EMPTY);
				}// zobraziť a upraviť footnote referencie na hyperlinky -- PARAM_FOOTNOTE_REF_END

// footnotes (footnote text)

				// upraviť footnotes na aname
				if (equals(strbuff, PARAM_FOOTNOTE_BEGIN) && (vnutri_inkludovaneho == ANO)) {
					vnutri_footnote = ANO;
					write = NIE;
					fn_index = 0;
					if (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_FOOTNOTES)) {
						/* if (rest != NULL) */ mystrcpy(fnrest, rest, MAX_BUFFER);
						DetailLog("\trest     == %s\n", rest);
						DetailLog("\tfnrest   == %s\n", fnrest);
					}
				}// upraviť footnotes na aname -- PARAM_FOOTNOTE_BEGIN
				if (equals(strbuff, PARAM_FOOTNOTE_END) && (vnutri_inkludovaneho == ANO)) {
					fnbuff[fn_index] = '\0';

					if (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_FOOTNOTES) && (write == NIE)) { // podmienka na write kvôli tomu, že write mohlo byť na ANO nastavené napr. vnorenou biblickou referenciou

						DetailLog("\trest     == %s\n", rest);
						DetailLog("\tfnrest   == %s\n", fnrest);
						DetailLog("\tfnbuff   == %s\n", fnbuff);

						if (!(equals(fnrest, STR_EMPTY))) {
							if (EXPORT_FOOTNOTES) {
								Export(HTML_A_NAME_BEGIN"\"fn%s\">", fnrest);
								Export(HTML_A_END);
								Export("<sup>%s</sup>", fnrest);
								ExportNonbreakingSpace();
							}
						}
						if (EXPORT_FOOTNOTES) {
							Export("%s", convert_nonbreaking_spaces(fnbuff));
						}

					}
					vnutri_footnote = NIE;

					if (EXPORT_FOOTNOTES) {
						write = ANO;
					}
					strcpy(fnrest, STR_EMPTY);
				}// zobraziť a upraviť footnotes na aname -- PARAM_FOOTNOTE_END

// notes (note text)

				// notes in parentheses
				if (equals(strbuff, PARAM_NOTE_BEGIN) && (vnutri_inkludovaneho == ANO)) {

					if (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_FOOTNOTES)) {
						Export(" ");
						Export("<" HTML_SPAN_TEXTNOTE ">");
						Export("(");
					}
					else {
						write = NIE;
					}

					vnutri_note = ANO;

					fn_index = 0;

					if (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_FOOTNOTES)) {
						/* if (rest != NULL) */ mystrcpy(fnrest, rest, MAX_BUFFER);
						DetailLog("\trest     == %s\n", rest);
						DetailLog("\tfnrest   == %s\n", fnrest);
					}
				}// upraviť notes -- PARAM_NOTE_BEGIN
				if (equals(strbuff, PARAM_NOTE_END) && (vnutri_inkludovaneho == ANO)) {

					fnbuff[fn_index] = '\0';

					if (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_FOOTNOTES) && (write == NIE)) { // podmienka na write kvôli tomu, že write mohlo byť na ANO nastavené napr. vnorenou biblickou referenciou

						DetailLog("\trest     == %s\n", rest);
						DetailLog("\tfnrest   == %s\n", fnrest);
						DetailLog("\tfnbuff   == %s\n", fnbuff);

						if (EXPORT_FOOTNOTES) {
							if (!(equals(fnrest, STR_EMPTY))) {
								Export("%s ", fnrest);
							}
							Export("%s", convert_nonbreaking_spaces(fnbuff));
						}
					}

					vnutri_note = NIE;

					if (EXPORT_FOOTNOTES) {
						write = ANO;
					}
					strcpy(fnrest, STR_EMPTY);

					if (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_FOOTNOTES)) {
						Export(")");
						Export(HTML_SPAN_END);
					}
				}// zobraziť a upraviť notes -- PARAM_NOTE_END

// full text of psalms

				if ((equals(strbuff, PARAM_PSALM_FULL_TEXT_BEGIN) || equals(strbuff, PARAM_PSALM_FULL_TEXT_SOFT_BEGIN)) && (vnutri_inkludovaneho == ANO)) {

					vnutri_full_text = ANO;
					write = write && (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZALMY_FULL_TEXT));

					if (write && equals(strbuff, PARAM_PSALM_FULL_TEXT_BEGIN)) {
						Export("<" HTML_DIV_PSALM_INDENT ">");
					}
				}
				if ((equals(strbuff, PARAM_PSALM_FULL_TEXT_END) || equals(strbuff, PARAM_PSALM_FULL_TEXT_SOFT_END)) && (vnutri_inkludovaneho == ANO)) {

					if (write && equals(strbuff, PARAM_PSALM_FULL_TEXT_END)) {
						Export(HTML_DIV_END);
					}

					vnutri_full_text = NIE;
					write = ANO;
					strcpy(fnrest, STR_EMPTY);
				}

// full text of other text [e.g. readings]

				if (equals(strbuff, PARAM_PSALM_FULL_TEXT_TXT_BEGIN) && (vnutri_inkludovaneho == ANO)) {

					vnutri_full_text = ANO;
					write = write && (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZALMY_FULL_TEXT));

					if (write && equals(strbuff, PARAM_PSALM_FULL_TEXT_TXT_BEGIN)) {
						Export("<" HTML_SPAN_SMALL ">");
					}
				}
				if (equals(strbuff, PARAM_PSALM_FULL_TEXT_TXT_END) && (vnutri_inkludovaneho == ANO)) {

					if (write) {
						Export(HTML_SPAN_END);
					}

					vnutri_full_text = NIE;
					write = ANO;
					strcpy(fnrest, STR_EMPTY);
				}

// biblical references

				// upraviť referencie na hyperlinky
				if (equals(strbuff, PARAM_REFERENCIA_BEGIN) && (vnutri_inkludovaneho == ANO)) {

					// spracujeme prípadný buffer, ak to bolo vnorené v rámci footnote alebo note
					if (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_FOOTNOTES) && EXPORT_FOOTNOTES && ((vnutri_footnote == ANO) || (vnutri_note == ANO))) {

						DetailLog("\tfnbuff   == %s\n", fnbuff);

						if (!(equals(fnrest, STR_EMPTY))) {
							if (vnutri_footnote == ANO) {
								Export(HTML_A_NAME_BEGIN "\"fn%s\">", fnrest);
								Export(HTML_A_END);
								Export("<sup>%s</sup>", fnrest);
								ExportNonbreakingSpace();
							}
							else if (vnutri_note == ANO) {
								Export("%s ", fnrest);
							}

							fnbuff[fn_index] = '\0';
							Export("%s", convert_nonbreaking_spaces(fnbuff));

							strcpy(fnrest, STR_EMPTY);
							strcpy(fnbuff, STR_EMPTY);
							fn_index = 0;
						}
					}

					vnutri_referencie = ANO;
					write = NIE;
					ref_index = 0;
					if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_REFERENCIE)) {
						/* if (rest != NULL) */ mystrcpy(refrest, rest, MAX_BUFFER);
						DetailLog("\trest     == %s\n", rest);
						DetailLog("\trefrest  == %s\n", refrest);
					}
				}// upraviť referencie na hyperlinky -- PARAM_REFERENCIA_BEGIN
				if (equals(strbuff, PARAM_REFERENCIA_END) && (vnutri_inkludovaneho == ANO)) {

					refbuff[ref_index] = '\0';
					if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_REFERENCIE)) {

						if (EXPORT_REFERENCIA) {
							if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_REF_BIBLE_COM)) {
								Export(HTML_A_HREF_BEGIN "\"%s", cfg_http_bible_com_references_default[_global_jazyk]);
								// add default version id
								Export("%s" STR_SLASH, cfg_bible_com_version_id_default[_global_jazyk]);
							}
							else {
								Export(HTML_A_HREF_BEGIN "\"%s", cfg_http_bible_references_default[_global_jazyk]);
							}
						}

						DetailLog("\trest     == %s\n", rest);
						DetailLog("\trefrest  == %s\n", refrest);
						DetailLog("\trefbuff  == %s\n", refbuff);

						// Example A: {r:Iz}6, 1-13{/r}
						// Example B: {r}Iz 6, 3{/r}
						// Example C: {r:Ž 102,}18{/r}

						// refrest: rest of the string within reference | A: "Iz" | B: empty | C: "Ž 102,"
						// refbuff: buffer (inner content of reference) | A: "6, 1-13" | B: "Iz 6, 3" | C: "18"

						// first, clean reference
						strcpy(reference, STR_EMPTY);

						// second, copy refrest to the beginning of reference (if not empty)
						if (!(equals(refrest, STR_EMPTY))) {
							// [ToDo]: doplniť nevypisovanie refbuff, ak refrest obsahuje medzeru
							if (EXPORT_REFERENCIA) {
								mystrcpy(reference, refrest, MAX_BUFFER);
								strcat(reference, STR_SPACE);
							}
						}

						// third, append refbuff to the end of refrest to create full reference
						strcat(reference, refbuff);

						// now, the reference is complete (but it may contain diacritics and/or special characters (Unicode long dashes etc.)
						if (EXPORT_REFERENCIA) {
							if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_REF_BIBLE_COM)) {
								Export("%s", mystr_bible_com(mystr_replace(reference, STR_EM_DASH, STR_EN_DASH).c_str())); // no need to remove diacritics for bible.com even on Android
							}
							else {
#ifdef IO_ANDROID
								// diacritics removal left only for Android
								Export("%s", mystr_remove_diacritics(mystr_replace(reference, STR_EM_DASH, STR_EN_DASH).c_str()));
#else
								// replace em-dash with en-dash
								Export("%s", mystr_replace(reference, STR_EM_DASH, STR_EN_DASH).c_str());
#endif
							}
						}

						if (EXPORT_REFERENCIA) {
							Export("\" " HTML_TARGET_BLANK " " HTML_CLASS_QUIET ">");
						}
					}
					if (EXPORT_REFERENCIA) {
						Export("%s", convert_nonbreaking_spaces(refbuff));
					}
					if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_REFERENCIE)) {
						if (EXPORT_REFERENCIA) {
							Export(HTML_A_END);
						}
					}
					vnutri_referencie = NIE;

					if (EXPORT_REFERENCIA) {
						write = ANO;
					}
					strcpy(refrest, STR_EMPTY);
					strcpy(reference, STR_EMPTY); // cleanup

					// spracujeme prípadný buffer ak to bolo vnorené v rámci footnote alebo note
					if (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_FOOTNOTES) && EXPORT_FOOTNOTES && ((vnutri_footnote == ANO) || (vnutri_note == ANO))) {
						if (/* (fnrest != NULL) && */ !(equals(fnrest, STR_EMPTY))) {
							fnbuff[fn_index] = '\0';

							strcpy(fnrest, STR_EMPTY);
							strcpy(fnbuff, STR_EMPTY);
							fn_index = 0;
						}
					}

				}// upraviť referencie na hyperlinky -- PARAM_REFERENCIA_END

#if defined(BEHAVIOUR_WEB)
				// upraviť odkazy na katechézy (zatiaľ napojené na BIT_OPT_0_REFERENCIE a EXPORT_REFERENCIA ako referencie)
				if (equals(strbuff, PARAM_KATECHEZA_BEGIN) && (vnutri_inkludovaneho == 1)) {
					vnutri_katechezy = ANO;
					write = NIE;
					kat_index = 0;
					if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_REFERENCIE)) {
						/* if (rest != NULL) */ mystrcpy(katrest, rest, MAX_BUFFER);
						DetailLog("\trest     == %s\n", rest);
						DetailLog("\tkatrest  == %s\n", katrest);
					}
				}// upraviť odkazy na katechézy na hyperlinky -- PARAM_KATECHEZA_BEGIN
				if (equals(strbuff, PARAM_KATECHEZA_END) && (vnutri_inkludovaneho == 1)) {
					katbuff[kat_index] = '\0';
					if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_REFERENCIE)) {
						// ToDo: časom dynamicky
						if (EXPORT_REFERENCIA) {
							Export(HTML_A_HREF_BEGIN "\"/include/");
						}
						DetailLog("\trest     == %s\n", rest);
						DetailLog("\tkatrest  == %s\n", katrest);
						if (/* (katrest != NULL) && */ !(equals(katrest, STR_EMPTY))) {
							// [ToDo]: doplniť nevypisovanie katbuff, ak katrest obsahuje medzeru (prevzaté z časti pre referencie)
							if (EXPORT_REFERENCIA) {
								Export("%s", convert_nonbreaking_spaces(katrest));
							}
						}// načítanie na začiatok referencie
						if (EXPORT_REFERENCIA) {
							Export("\" " HTML_TARGET_BLANK " " HTML_CLASS_QUIET ">");
						}
					}
					if (EXPORT_REFERENCIA) {
						// nezlomiteľné medzery
						Export("%s", convert_nonbreaking_spaces(katbuff));
					}
					if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_REFERENCIE)) {
						if (EXPORT_REFERENCIA) {
							Export(HTML_A_END);
						}
					}
					vnutri_katechezy = NIE;

					// prevzaté z časti pre referencie: 2011-05-02: doplnené kvôli referenciám, ktoré sú v rámci myšlienok, čo sa nemajú zobrazovať
					if (EXPORT_REFERENCIA) {
						write = ANO;
					}
					strcpy(katrest, STR_EMPTY);
				}// upraviť odkazy na katechézy na hyperlinky -- PARAM_KATECHEZA_END
#endif

				// upraviť odkaz na žalm 95 (zatiaľ napojené na BEHAVIOUR_WEB)
				if (equals(strbuff, PARAM_LINK_ZALM95_BEGIN) && (vnutri_inkludovaneho == 1)) {
					vnutri_z95 = ANO;
					write = NIE;
					z95_index = 0;
#ifdef BEHAVIOUR_WEB
					/* if (rest != NULL) */ mystrcpy(z95rest, rest, MAX_BUFFER);
					DetailLog("\trest     == %s\n", rest);
					DetailLog("\tz95rest  == %s\n", z95rest);
#endif
				}// upraviť odkaz na žalm 95 na hyperlink -- PARAM_LINK_ZALM95_BEGIN
				if (equals(strbuff, PARAM_LINK_ZALM95_END) && (vnutri_inkludovaneho == 1)) {
					Log("(if (equals(strbuff, PARAM_LINK_ZALM95_END)): _global_opt[OPT_2_HTML_EXPORT] & BIT_OPT_2_ROZNE_MOZNOSTI == %ld: \n", _global_opt[OPT_2_HTML_EXPORT] & BIT_OPT_2_ROZNE_MOZNOSTI);
					char specific_string[SMALL];
					mystrcpy(specific_string, HTML_P_BEGIN, SMALL);
					if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI)) { // len ak je táto možnosť (zobrazovanie všeličoho) zvolená
						z95buff[z95_index] = '\0';
#ifdef BEHAVIOUR_WEB
						// najprv upravíme o1
						_global_opt_1_casti_modlitby_orig = _global_opt[OPT_1_CASTI_MODLITBY]; // backup pôvodnej hodnoty

						// nastavenie parametra o1: pridáme bit pre alternatívnu psalmódiu
						if (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALM95)) {
							Log("Pre option 1 odstraňujem bit pre ž95 (pôvodnú hodnotu som si zapamätal)\n");
							_global_opt[OPT_1_CASTI_MODLITBY] += BIT_OPT_1_ZALM95;
						}
						else {
							Log("Pre option 1 pridávam bit pre ž95 (pôvodnú hodnotu som si zapamätal)\n");
							_global_opt[OPT_1_CASTI_MODLITBY] -= BIT_OPT_1_ZALM95;
						}

						// prilepenie poradia svätca
						if (_global_poradie_svaty > 0) {
							sprintf(pom, HTML_AMPERSAND"%s=%d", STR_DALSI_SVATY, _global_poradie_svaty);
						}// _global_poradie_svaty > 0
						else {
							mystrcpy(pom, STR_EMPTY, MAX_STR);
						}// !(_global_poradie_svaty > 0)

						// teraz vytvoríme reťazec s options
						prilep_request_options(pom, pompom);

						// v hyperlinku prilepíme aj #ZALM95 (do z95.htm a ostatných sme doplnili <a name...>) // napokon prilepíme #anchor
						sprintf(pompom, "#%s", PARAM_ZALM95);
						strcat(pom, pompom);

						// export hyperlinku
						if (query_type == PRM_DATUM) {
							Export("%s\n<" HTML_SPAN_RED_SMALL ">\n" HTML_A_HREF_BEGIN "\"%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%s%s\"",
								specific_string,
								script_name,
								STR_QUERY_TYPE, STR_PRM_DATUM,
								STR_DEN, _global_den.den,
								STR_MESIAC, _global_den.mesiac,
								STR_ROK, _global_den.rok,
								STR_MODLITBA, str_modlitby[_global_modlitba],
								pom);
						}
						else if (query_type == PRM_LIT_OBD) {
							Export("%s\n<" HTML_SPAN_RED_SMALL ">\n" HTML_A_HREF_BEGIN "\"%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%c" HTML_AMPERSAND "%s=%s%s\"",
								specific_string,
								script_name,
								STR_QUERY_TYPE, STR_PRM_LIT_OBD,
								STR_DEN_V_TYZDNI, _global_den.denvt,
								STR_TYZDEN, _global_den.tyzden,
								STR_LIT_OBD, _global_den.litobd,
								STR_LIT_ROK, _global_den.litrok,
								STR_MODLITBA, str_modlitby[_global_modlitba],
								pom);
						}
						// napokon o1 vrátime späť
						_global_opt[OPT_1_CASTI_MODLITBY] = _global_opt_1_casti_modlitby_orig; // restore pôvodnej hodnoty

						Export(" " HTML_CLASS_QUIET ">");
#endif
						Export("%s", convert_nonbreaking_spaces(z95buff));
#ifdef BEHAVIOUR_WEB
						Export(HTML_A_END);
						Export(HTML_SPAN_END"\n");
#endif
					}
					else {
#if defined(EXPORT_HTML_SPECIALS)
						ExportHtmlComment(PARAM_LINK_ZALM95_BEGIN);
#endif
					}
					vnutri_z95 = NIE;
					write = ANO;
					strcpy(z95rest, STR_EMPTY);
				}// upraviť odkaz na žalm 95 na hyperlink -- PARAM_LINK_ZALM95_END

				// zobraziť/nezobraziť zalomenie veršov podľa tlačenej LH | ignore this switch (as if it would OFF) for mobile OS (Android, iOS) and voice output
				if (equals(strbuff, PARAM_ZALOMENIE) && (vnutri_inkludovaneho == 1)) {
#if defined(EXPORT_HTML_SPECIALS)
					if (!write) {
						// kvôli vnutri_full_text == ANO
						Export("<!--");
					}

					Export("[%s:%s|rest=%s]", strbuff, modlparam, (rest == NULL) ? STR_EMPTY : rest);
#endif
					if (useWhenGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_TEXT_WRAP) && (isMobileOS == 0) && EXPORT_FULL_TEXT) {
						// MAX_BUFFER bol zvýšený, lebo strbuff bol v tomto prípade veľmi dlhý
						Export("zalomenie-->%s<!--zalomenie", rest);
					}
					else {
#if defined(EXPORT_HTML_SPECIALS)
						Export("zalomenie-nie");

						if (!write) {
							// kvôli vnutri_full_text == ANO
							Export("-->");
						}
#endif
					}
				}// zobraziť/nezobraziť zalomenie veršov podľa tlačenej LH -- PARAM_ZALOMENIE

				// zobraziť/nezobraziť číslovanie veršov
				if (equals(strbuff, PARAM_CISLO_VERSA_BEGIN) && (vnutri_inkludovaneho == 1)) {
					if (EXPORT_VERSE_NUMBER) {
						Export("<sup>");
					}
					else {
						write = NIE;
#if defined(EXPORT_HTML_SPECIALS)
						Export("<!--č.verša:zač.");
#endif
						Log("  ruším writing to export file, kvôli PARAM_CISLO_VERSA_BEGIN...\n");
					}
				}// zobraziť/nezobraziť číslovanie veršov
				if (equals(strbuff, PARAM_CISLO_VERSA_END) && (vnutri_inkludovaneho == 1)) {
					if (EXPORT_VERSE_NUMBER) {
						Export("</sup>");
					}
					else {
						write = EXPORT_FULL_TEXT;
#if defined(EXPORT_HTML_SPECIALS)
						Export("č.verša:end-->");
#endif
						Log("  opäť writing to export file, PARAM_CISLO_VERSA_END...\n");
					}
				}// zobraziť/nezobraziť číslovanie veršov

				// zobraziť/nezobraziť text kurzívou
				if (equals(strbuff, PARAM_ITALICS_COND_BEGIN) && (vnutri_inkludovaneho == 1)) {
					if (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ITALICS_CONDITIONAL)) {
						Export("<i>");
					}
					else {
#if defined(EXPORT_HTML_SPECIALS)
						// Export("<!--it.cond.:zač.-->");
#endif
						Log("  ruším writing to export file, kvôli PARAM_ITALICS_COND_BEGIN...\n");
					}
				}// zobraziť/nezobraziť text kurzívou
				if (equals(strbuff, PARAM_ITALICS_COND_END) && (vnutri_inkludovaneho == 1)) {
					if (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ITALICS_CONDITIONAL)) {
						Export("</i>");
					}
					else {
#if defined(EXPORT_HTML_SPECIALS)
						// Export("<!--it.cond.:end-->");
#endif
						Log("  opäť writing to export file, PARAM_ITALICS_COND_END...\n");
					}
				}// zobraziť/nezobraziť číslovanie veršov

				if ((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT)) && (equals(rest, PARAM_HIDE_FOR_VOICE_OUTPUT))) {

					if (equals(strbuff, INCLUDE_BEGIN) && (vnutri_inkludovaneho == 1)) {

						_global_skip_in_prayer += ANO; // increment

						write = NIE;
#if defined(EXPORT_HTML_SPECIALS)
						Export("(stop)hide-for-voice-output");
#endif
						Log("  rusim writing to export file, kvoli hide-for-voice-output...\n");
					}
					else if (equals(strbuff, INCLUDE_END) && (vnutri_inkludovaneho == 1)) {
#if defined(EXPORT_HTML_SPECIALS)
						Export("hide-for-voice-output(start)");
#endif
						write = ANO;

						_global_skip_in_prayer -= ANO; // decrement

						Log("  opat writing to export file, end of hide-for-voice-output.\n");
					}
				}// hide passage for voice output

				if ((!(je_velka_noc)) && (equals(rest, PARAM_ALELUJA_VO_VELKONOCNOM))) {
					if (equals(strbuff, INCLUDE_BEGIN) && (vnutri_inkludovaneho == 1)) {
						write = NIE;
#if defined(EXPORT_HTML_SPECIALS)
						Export("(stop)nie je v.o.");
#endif
						Log("  rusim writing to export file, kvoli V.O. Aleluja...\n");
					}
					else if (equals(strbuff, INCLUDE_END) && (vnutri_inkludovaneho == 1)) {
#if defined(EXPORT_HTML_SPECIALS)
						Export("nie je v.o.(start)");
#endif
						write = ANO;
						Log("  opat writing to export file, end of V.O. Aleluja.\n");
					}
				}// aleluja vo veľkonočnom období

				// aleluja mimo pôstneho obdobia - doteraz fungovala len pre templáty -- interpretParameter()
				if ((je_post) && (equals(rest, PARAM_ALELUJA_NIE_V_POSTE))) {
					if (equals(strbuff, INCLUDE_BEGIN) && (vnutri_inkludovaneho == 1)) {
						write = NIE;
#if defined(EXPORT_HTML_SPECIALS)
						Export("(stop)je post");
#endif
						Log("  rusim writing to export file, kvoli Aleluja...\n");
					}
					else if (equals(strbuff, INCLUDE_END) && (vnutri_inkludovaneho == 1)) {
#if defined(EXPORT_HTML_SPECIALS)
						Export("nie je post(start)");
#endif
						write = ANO;
						Log("  opat writing to export file, end of Aleluja.\n");
					}
				}// aleluja mimo pôstneho obdobia

				// plné responzórium...
				if ((equals(rest, PARAM_PLNE_RESP)) || (equals(rest, PARAM_PLNE_RESP_BODKA))) {
					if (equals(strbuff, INCLUDE_BEGIN) && (vnutri_inkludovaneho == 1)) {
#if defined(EXPORT_HTML_SPECIALS)
						Export("(start)dlhe-resp.");
#endif
						if (useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PLNE_RESP)) {
							;
						}
						else {
							write = NIE;
							Log("  ruším writing to export file, kvôli PARAM_PLNE_RESP...\n");
						}
					}// INCLUDE_BEGIN
					else if (equals(strbuff, INCLUDE_END) && (vnutri_inkludovaneho == 1)) {
#if defined(EXPORT_HTML_SPECIALS)
						Export("dlhe-resp.(stop)");
#endif
						if (useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PLNE_RESP)) {
							;
						}
						else {
							write = ANO;
							Log("  opäť writing to export file, PARAM_PLNE_RESP...\n");
							// ak končí iným znakom ako bodkou (napr. ?!), pri skrátenom výpise (indikovaný iným parametrom) je treba vypísať bodku
							if (equals(rest, PARAM_PLNE_RESP_BODKA)) {
								Export("-->.<!--");
							}
						}
						Log("dlhe-resp-koniec.\n");
					}// INCLUDE_END
				}// plné responzórium...

				// OPAK plné responzórium...
				if (equals(rest, PARAM_NIE_PLNE_RESP)) {
					if (equals(strbuff, INCLUDE_BEGIN) && (vnutri_inkludovaneho == 1)) {
#if defined(EXPORT_HTML_SPECIALS)
						Export("(start)NIE-dlhe-resp.");
#endif
						if (!(useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PLNE_RESP))) {
							;
						}
						else {
							write = NIE;
							Log("  ruším writing to export file, kvôli PARAM_NIE_PLNE_RESP...\n");
						}
					}// INCLUDE_BEGIN
					else if (equals(strbuff, INCLUDE_END) && (vnutri_inkludovaneho == 1)) {
#if defined(EXPORT_HTML_SPECIALS)
						Export("NIE-dlhe-resp.(stop)");
#endif
						if (!(useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PLNE_RESP))) {
							;
						}
						else {
							write = ANO;
							Log("  opäť writing to export file, PARAM_NIE_PLNE_RESP...\n");
						}
						Log("NIE-dlhe-resp-koniec.\n");
					}// INCLUDE_END
				}// OPAK plné responzórium...

				// zvolanie v prosbách...
				if (equals(rest, PARAM_ZVOLANIE)) {
					if (equals(strbuff, INCLUDE_BEGIN) && (vnutri_inkludovaneho == 1)) {
#if defined(EXPORT_HTML_SPECIALS)
						Export("(start)zvolanie");
#endif
						if (useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PROSBY_ZVOLANIE)) {
							;
						}
						else {
							write = NIE;
							Log("  ruším writing to export file, kvôli PARAM_ZVOLANIE...\n");
						}
					}// INCLUDE_BEGIN
					else if (equals(strbuff, INCLUDE_END) && (vnutri_inkludovaneho == 1)) {
#if defined(EXPORT_HTML_SPECIALS)
						Export("zvolanie(stop)");
#endif
						if (useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PROSBY_ZVOLANIE)) {
							;
						}
						else {
							write = ANO;
							Log("  opäť writing to export file, PARAM_ZVOLANIE...\n");
						}
						Log("zvolanie-koniec.\n");
					}// INCLUDE_END
				}// zvolanie v prosbách...

				// rubriky
				if (equals(rest, PARAM_RUBRIKA)) {
					if (equals(strbuff, INCLUDE_BEGIN) && (vnutri_inkludovaneho == 1)) {
#if defined(EXPORT_HTML_SPECIALS)
						Export("(start)rubrika");
#endif
						if (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_RUBRIKY) || isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT)) {
							;
						}
						else {
							write = NIE;
							Log("  ruším writing to export file, kvôli PARAM_RUBRIKA...\n");
						}
					}// INCLUDE_BEGIN
					else if (equals(strbuff, INCLUDE_END) && (vnutri_inkludovaneho == 1)) {
#if defined(EXPORT_HTML_SPECIALS)
						Export("rubrika(stop)");
#endif
						if (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_RUBRIKY) || isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT)) {
							;
						}
						else {
							write = ANO;
							Log("  opäť writing to export file, PARAM_RUBRIKA...\n");
						}
						Log("rubrika-koniec.\n");
					}// INCLUDE_END
				}// rubriky

				// voliteľné zobrazovanie/skrývanie alternatívnej antifóny pre žalmy/chválospevy 
				// upravené tak, aby sa nezobrazovalo len pre spomienky svätých [tam spadajú aj liturgické slávenia 1.1. a pod.]
				// upravené tak, že sa nezobrazuje len pre slávnosti a sviatky; pre spomienky sa zobrazuje (smer < 5: pre trojdnie)
				// doplnené, aby sa nezobrazovalo vo Veľkonočnej oktáve
				// upravené, aby sa nastavovalo vnutri_myslienky kvôli tomu, že z viacerých miest sa nastavovalo write
				if (equals(rest, PARAM_PSALMODIA_MYSLIENKA)) {
					if (je_myslienka) {
#if defined(EXPORT_HTML_SPECIALS)
						Export("myslienka");
#endif
					}
					else {
						if (equals(strbuff, INCLUDE_BEGIN)) {
							vnutri_myslienky = ANO;
							if (vnutri_inkludovaneho == 1) {
								write = NIE;
#if defined(EXPORT_HTML_SPECIALS)
								Export("(stop)nie je myslienka");
#endif
								Log("  rusim writing to export file, kvoli myslienka-k-zalmu...\n");
							}// vnutri_inkludovaneho == 1
						}// INCLUDE_BEGIN
						else if (equals(strbuff, INCLUDE_END)) {
							vnutri_myslienky = NIE;
							if (vnutri_inkludovaneho == 1) {
#if defined(EXPORT_HTML_SPECIALS)
								Export("nie je myslienka(start)");
#endif
								write = ANO;
								Log("  opat writing to export file, end of myslienka-k-zalmu.\n");
							}// vnutri_inkludovaneho == 1
						}// INCLUDE_END
					}
				}// voliteľné zobrazovanie/skrývanie alternatívnej antifóny pre žalmy/chválospevy

				// voliteľné zobrazovanie/skrývanie nadpisu pre žalmy/chválospevy podľa myšlienky
				if (equals(rest, PARAM_PSALMODIA_NADPIS)) {
					if (je_nadpis) {
#if defined(EXPORT_HTML_SPECIALS)
						Export("nadpis");
#endif
					}
					else {
						if (equals(strbuff, INCLUDE_BEGIN)) {
							vnutri_nadpisu = ANO;
							if (vnutri_inkludovaneho == 1) {
								write = NIE;
#if defined(EXPORT_HTML_SPECIALS)
								Export("(stop)nie je nadpis");
#endif
								Log("  rusim writing to export file, kvoli psalmodia-nadpis...\n");
							}// vnutri_inkludovaneho == 1
						}// INCLUDE_BEGIN
						else if (equals(strbuff, INCLUDE_END)) {
							vnutri_nadpisu = NIE;
							if (vnutri_inkludovaneho == 1) {
#if defined(EXPORT_HTML_SPECIALS)
								Export("nie je nadpis(start)");
#endif
								write = ANO;
								Log("  opat writing to export file, end of psalmodia-nadpis.\n");
							}// vnutri_inkludovaneho == 1
						}// INCLUDE_END
					}
				}// voliteľné zobrazovanie/skrývanie nadpisu pre žalmy/chválospevy

			}// !equalsi(rest, modlparam)
			continue;
		} // switch(c)

		if (!isbuff) {
			// bez ohľadu na to, ako je nastavené write
			if (vnutri_footnote_ref == ANO) {
				AppendWchar(c, sizeof(fnrefbuff), fnrefbuff, &fnref_index);
			}
			if (((vnutri_footnote == ANO) || (vnutri_note == ANO)) && !(vnutri_referencie == ANO)) {
				// nečítam, ak som zároveň vnorený v rámci biblickej referencie
				AppendWchar(c, sizeof(fnbuff), fnbuff, &fn_index);
			}
			if (vnutri_referencie == ANO) {
				AppendWchar(c, sizeof(refbuff), refbuff, &ref_index);
			}
			if (vnutri_katechezy == ANO) {
				AppendWchar(c, sizeof(katbuff), katbuff, &kat_index);
			}
			if (vnutri_z95 == ANO) {
				AppendWchar(c, sizeof(z95buff), z95buff, &z95_index);
			}
			if (write == ANO && _global_skip_in_prayer == NIE) {
				// nezlomiteľné medzery; v DetailLog logujeme 1:1 presne znak bez transformácie
				ExportChar(c, isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT));
				// DetailLog("%c", c);
			}
			else {
				; //skip
			}
		}// if (!isbuff)
		else {
			AppendWchar(c, sizeof(strbuff), strbuff, &buff_index);

			// 2011-03-29: doplnená kontrola, či nejde o osamotený znak '{'
			if (((isbuff == 1) && (strlen(strbuff) > MAX_BUFFER - 2)) || (buff_index > MAX_BUFFER - 2)) {
				Log("pravdepodobne osamotený znak '{'...\n");
				isbuff = 0;
				if (write == ANO && _global_skip_in_prayer == NIE) {
					// nezlomiteľné medzery; v DetailLog logujeme 1:1 presne reťazec bez transformácie
					Export("%s", convert_nonbreaking_spaces(strbuff));
					// DetailLog("%s", strbuff);
				}
				// vyčistenie buffra
				buff_index = 0;
				strbuff[buff_index] = '\0';
			}// osamotený znak '{'
		}// else if (!isbuff)
	}// while((c = fgetc(body)) != EOF)
	fclose(body);
	Log("--includeFile(): end\n");
} // includeFile()

void _export_rozbor_dna_navig_top_bottom_simple(char* target, const char* text, const char* arrow) {
	Export(HTML_A_HREF_BEGIN "\"#%s\" " HTML_CLASS_QUIET ">%s %s" HTML_A_END, target, arrow, text);
} // _export_rozbor_dna_navig_top_bottom_simple()

void _export_rozbor_dna_navig_top_bottom(char* target, const char* text, const char* arrow) {
	ExportHtmlComment("p-navigation:begin");

	Export(HTML_P_CENTER_SMALL);

	_export_rozbor_dna_navig_top_bottom_simple(target, text, arrow);

	Export(HTML_P_END "\n");

	ExportHtmlComment("p-navigation:end");
} // _export_rozbor_dna_navig_top_bottom()

void init_marianske_anfifony_file(_struct_anchor_and_file &af) {
	mystrcpy(af.anchor, ANCHOR_MARIANSKE_ANTIFONY, MAX_STR_AF_ANCHOR);
#ifdef MODEL_LH_commandline
	mystrcpy(af.file, ".." STR_PATH_SEPARATOR_HTML, MAX_STR_AF_FILE);
	strcat(af.file, DOCS_FOLDER"" STR_PATH_SEPARATOR_HTML);
	strcat(af.file, FILE_MARIANSKE_ANTIFONY);
#else
	mystrcpy(af.file, FILE_MARIANSKE_ANTIFONY, MAX_STR_AF_FILE);
#endif
	Log_filename_anchor(af);
	return;
} // init_marianske_anfifony_file()

void init_ordinarium_file(_struct_anchor_and_file &af, short int modlitba) {
	mystrcpy(af.anchor, ANCHOR_ORDINARIUM, MAX_STR_AF_ANCHOR);

	if ((modlitba < MODL_INVITATORIUM) || (modlitba > MODL_DRUHE_KOMPLETORIUM)) {
		modlitba = MODL_RANNE_CHVALY;
	}
	mystrcpy(af.file, FILE_ORDINARIUM[modlitba], MAX_STR_AF_FILE);

	Log_filename_anchor(af);
	return;
} // init_ordinarium_file()

void init_info_file(_struct_anchor_and_file &af, short int id) {
	Log("init_info_file(id == %d): begin...\n", id);

	mystrcpy(af.anchor, ANCHOR_INFO, MAX_STR_AF_ANCHOR);

	if ((id < INFO_ABOUT) || (id > POCET_INFO_TEXTOV)) {
		id = INFO_ABOUT;
	}
	mystrcpy(af.file, FILE_INFO[id], MAX_STR_AF_FILE);
	
	Log_filename_anchor(af);
	Log("init_info_file(id == %d): end.\n", id);

	return;
} // init_info_file()

// funkcia vyexportuje (vrátane formátovania) reťazec napr. "Zo spoločnej časti na sviatky duchovných pastierov: pre biskupov" s prípadným dovetkom "pri slávení spomienky vziať časti zo dňa podľa Všeobecných smerníc, č. 235 písm. b" do reťazca _global_string_spol_cast_full
// parameter aj_vslh_235b: 
// ANO == použitie v konkrétnej modlitbe, funkcia interpretParameter()
// NIE == použitie v prehľade pre daný dátum, funkcia _export_rozbor_dna_buttons()
// note that variable ret_sc must be initialized before this method was called
void init_global_string_spol_cast_full(short int aj_vslh_235b) {
	char pom[MAX_STR], pom_main[MAX_STR];
	mystrcpy(pom, STR_EMPTY, MAX_STR);
	Log("-- init_global_string_spol_cast_full(aj_vslh_235b == %d): začiatok...\n", aj_vslh_235b);
	Log("pôvodná hodnota: %s\n", _global_string_spol_cast_full);
	mystrcpy(_global_string_spol_cast_full, STR_EMPTY, MAX_GLOBAL_STR);

	if (!equals(_global_string_spol_cast, STR_EMPTY)) {
		Log("-- init_global_string_spol_cast_full(): vytváram reťazec `%s'...\n", _global_string_spol_cast);

		// text o VSLH č. 235 b (pôvodne sa pridávalo do reťazca _global_string_spol_cast vo funkcii init_global_string_spol_cast()
		if ((aj_vslh_235b == ANO) && ((_global_den.smer > 9) && ((_global_den.typslav == SLAV_SPOMIENKA) || (_global_den.typslav == SLAV_LUB_SPOMIENKA)))) {
			if (!pouzit_na_spomienky_casti_zo_spolocnych_casti) {
				strcat(pom, " (");
				strcat(pom, nazov_bit_opt_1_spomienka_spol_cast_jazyk[_global_jazyk]);
				strcat(pom, ")");
			}// nebrať časti zo spol. časti
		}// ide nanajvýš o spomienku (ak je to slávenie s vyšším stupňom, nemá zmysel voľba BIT_OPT_1_SPOMIENKA_SPOL_CAST)

		// (aj_vslh_235b == ANO) means function is called from the generated prayer (for voice output is not necessary to export it at all) -- use different CSS style
		if (aj_vslh_235b == ANO) {
			strcat(_global_string_spol_cast_full, HTML_DIV_BEGIN);
		}
		strcat(_global_string_spol_cast_full, "<" HTML_SPAN_RED_SUBTITLE ">");

		// pre HU iný slovosled
		if (_global_jazyk == JAZYK_HU) {
			sprintf(pom_main, "%s %s %s%s.",
				(ret_sc != MODL_SPOL_CAST_ZA_ZOSNULYCH) ? ((ret_sc == MODL_SPOL_CAST_POSVIACKA_CHRAMU) ? nazov_spolc_vyrocie_jazyk[_global_jazyk] : nazov_spolc_sviatky_jazyk[_global_jazyk]) : STR_EMPTY,
				mystr_first_upper(_global_string_spol_cast).c_str(),
				(ret_sc == MODL_SPOL_CAST_ZA_ZOSNULYCH) ? nazov_spolc_oficiumza_jazyk[_global_jazyk] : nazov_spolc_zospolc_jazyk[_global_jazyk],
				pom);
		}
		else {
			sprintf(pom_main, "%s %s %s%s.",
				(ret_sc == MODL_SPOL_CAST_ZA_ZOSNULYCH) ? nazov_spolc_oficiumza_jazyk[_global_jazyk] : nazov_spolc_zospolc_jazyk[_global_jazyk],
				(ret_sc != MODL_SPOL_CAST_ZA_ZOSNULYCH) ? ((ret_sc == MODL_SPOL_CAST_POSVIACKA_CHRAMU) ? nazov_spolc_vyrocie_jazyk[_global_jazyk] : nazov_spolc_sviatky_jazyk[_global_jazyk]) : STR_EMPTY,
				_global_string_spol_cast,
				pom);
		}
		strcat(_global_string_spol_cast_full, pom_main);

		strcat(_global_string_spol_cast_full, HTML_SPAN_END);
		if (aj_vslh_235b == ANO) {
			strcat(_global_string_spol_cast_full, HTML_DIV_END);
		}

		strcat(_global_string_spol_cast_full, "\n");
	}
	else {
		Log("-- init_global_string_spol_cast_full(): prázdny reťazec.\n");
	}
	Log("-- init_global_string_spol_cast_full(aj_vslh_235b == %d): koniec.\n", aj_vslh_235b);
} // init_global_string_spol_cast_full()

void _export_global_string_spol_cast(short int aj_vslh_235b) {
	init_global_string_spol_cast_full(aj_vslh_235b);
	Export(_global_string_spol_cast_full);
} // _export_global_string_spol_cast()

#define _global_modl_hymnus_anchor (modlitba == MODL_RANNE_CHVALY) ? _global_modl_ranne_chvaly.hymnus.anchor : ((modlitba == MODL_PREDPOLUDNIM) ? _global_modl_cez_den_9.hymnus.anchor : ((modlitba == MODL_NAPOLUDNIE) ? _global_modl_cez_den_12.hymnus.anchor : ((modlitba == MODL_POPOLUDNI) ? _global_modl_cez_den_3.hymnus.anchor : ((modlitba == MODL_POSV_CITANIE) ? _global_modl_posv_citanie.hymnus.anchor : ((modlitba == MODL_VESPERY) ? _global_modl_vespery.hymnus.anchor : ((modlitba == MODL_KOMPLETORIUM) ? _global_modl_kompletorium.hymnus.anchor : ((modlitba == MODL_PRVE_VESPERY) ? _global_modl_prve_vespery.hymnus.anchor : _global_modl_prve_kompletorium.hymnus.anchor)))))))

#define _global_modl_modlitba_anchor (modlitba == MODL_RANNE_CHVALY) ? _global_modl_ranne_chvaly.modlitba.anchor : ((modlitba == MODL_PREDPOLUDNIM) ? _global_modl_cez_den_9.modlitba.anchor : ((modlitba == MODL_NAPOLUDNIE) ? _global_modl_cez_den_12.modlitba.anchor : ((modlitba == MODL_POPOLUDNI) ? _global_modl_cez_den_3.modlitba.anchor : ((modlitba == MODL_POSV_CITANIE) ? _global_modl_posv_citanie.modlitba.anchor : ((modlitba == MODL_VESPERY) ? _global_modl_vespery.modlitba.anchor : ((modlitba == MODL_KOMPLETORIUM) ? _global_modl_kompletorium.modlitba.anchor : ((modlitba == MODL_PRVE_VESPERY) ? _global_modl_prve_vespery.modlitba.anchor : _global_modl_prve_kompletorium.modlitba.anchor)))))))

#define _global_modl_kcit_anchor (modlitba == MODL_RANNE_CHVALY) ? _global_modl_ranne_chvaly.kcitanie.anchor : ((modlitba == MODL_PREDPOLUDNIM) ? _global_modl_cez_den_9.kcitanie.anchor : ((modlitba == MODL_NAPOLUDNIE) ? _global_modl_cez_den_12.kcitanie.anchor : ((modlitba == MODL_POPOLUDNI) ? _global_modl_cez_den_3.kcitanie.anchor : ((modlitba == MODL_VESPERY) ? _global_modl_vespery.kcitanie.anchor : ((modlitba == MODL_KOMPLETORIUM) ? _global_modl_kompletorium.kcitanie.anchor : ((modlitba == MODL_PRVE_VESPERY) ? _global_modl_prve_vespery.kcitanie.anchor : _global_modl_prve_kompletorium.kcitanie.anchor))))))

#define _global_modl_kresp_anchor (modlitba == MODL_RANNE_CHVALY) ? _global_modl_ranne_chvaly.kresponz.anchor : ((modlitba == MODL_PREDPOLUDNIM) ? _global_modl_cez_den_9.kresponz.anchor : ((modlitba == MODL_NAPOLUDNIE) ? _global_modl_cez_den_12.kresponz.anchor : ((modlitba == MODL_POPOLUDNI) ? _global_modl_cez_den_3.kresponz.anchor : ((modlitba == MODL_POSV_CITANIE) ? _global_modl_posv_citanie.kresponz.anchor : ((modlitba == MODL_VESPERY) ? _global_modl_vespery.kresponz.anchor : ((modlitba == MODL_KOMPLETORIUM) ? _global_modl_kompletorium.kresponz.anchor : ((modlitba == MODL_PRVE_VESPERY) ? _global_modl_prve_vespery.kresponz.anchor : _global_modl_prve_kompletorium.kresponz.anchor)))))))

#define _global_modl_prosby_anchor (modlitba == MODL_RANNE_CHVALY) ? _global_modl_ranne_chvaly.prosby.anchor : ((modlitba == MODL_VESPERY) ? _global_modl_vespery.prosby.anchor : ((modlitba == MODL_PRVE_VESPERY) ? _global_modl_prve_vespery.prosby.anchor : ((modlitba == MODL_KOMPLETORIUM) ? _global_modl_kompletorium.ukonkaj.anchor : _global_modl_prve_kompletorium.ukonkaj.anchor)))

#define _global_modl_otcenas_uvod_anchor (modlitba == MODL_RANNE_CHVALY) ? _global_modl_ranne_chvaly.otcenas_uvod.anchor : ((modlitba == MODL_VESPERY) ? _global_modl_vespery.otcenas_uvod.anchor : _global_modl_prve_vespery.otcenas_uvod.anchor)

#define _global_modl_antifona_anchor (modlitba == MODL_INVITATORIUM) ? _global_modl_invitatorium.antifona1.anchor : ((modlitba == MODL_RANNE_CHVALY) ? _global_modl_ranne_chvaly.benediktus.anchor : ((modlitba == MODL_VESPERY) ? _global_modl_vespery.magnifikat.anchor : _global_modl_prve_vespery.magnifikat.anchor))

#define _global_modl_maria_ant_anchor (modlitba == MODL_KOMPLETORIUM) ? _global_modl_kompletorium.maria_ant.anchor : _global_modl_prve_kompletorium.maria_ant.anchor

void ExportFileAnchor(short int typ, short int modlitba, char paramname[MAX_BUFFER], _struct_anchor_and_file anchor_and_file) {
	// this is the endpoint where anchor & file are sent either to XML output or to method which includes them into HTML result

	Log("ExportFileAnchor(): typ == %d, modlitba == %d, paramname == %s, file == %s, anchor == %s...\n", typ, modlitba, paramname, anchor_and_file.file, anchor_and_file.anchor);

	// when "use printed-edition text" option is switched ON, check whether anchor is listed in special arrays; in such case add special postfix
	if ((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_PRINTED_EDITION)) && (is_printed_edition_text(anchor_and_file.anchor, paramname) == TRUE)) {

		strcat(anchor_and_file.anchor, PRINTED_EDITION_POSTFIX);
		
		Log("ExportFileAnchor(): BIT_OPT_0_PRINTED_EDITION == true + anchor exists in the list with possibility to ask printed edition text, so changing the anchor to: %s...\n", anchor_and_file.anchor);
	}

	if (typ == PRM_XML) {
		Export(ELEM_BEGIN(XML_INDEX) "\n");
		Export(ELEM_BEGIN(XML_FILENAME) "%s" ELEM_END(XML_FILENAME) "\n", anchor_and_file.file);
		Export(ELEM_BEGIN(XML_ANCHOR) "%s" ELEM_END(XML_ANCHOR) "\n", anchor_and_file.anchor);
		Export(ELEM_BEGIN(XML_LOCATION_ID) "%s:%s" ELEM_END(XML_LOCATION_ID) "\n", anchor_and_file.file, anchor_and_file.anchor);
		Export(ELEM_END(XML_INDEX) "\n\n");
	}
	else {
		char path[MAX_STR] = STR_EMPTY;
		mystrcpy(path, include_dir, MAX_STR);
		strcat(path, anchor_and_file.file);

		includeFile(typ, modlitba, paramname, path, anchor_and_file.anchor);
	}
}// ExportFileAnchor()

// dostane vstup to, co sa pri parsovani templatu nachadza medzi znakmi CHAR_KEYWORD_BEGIN a CHAR_KEYWORD_END;
// zrejme ide o parameter; podla neho inkluduje subor (alebo cast suboru)
// 27/04/2000A.D.: pozmenene (pridane #definy):
//    -- je_post(): odpoved je kladna, ak je niektore z nasledujucich
//                 * OBD_POSTNE_I
//                 * OBD_POSTNE_II_VELKY_TYZDEN
//                 * OBD_VELKONOCNE_TROJDNIE && (den == piatok || sobota)
//    -- je_velka_noc(): odpoved je kladna, ak je niektore z nasledujucich
//                 * OBD_VELKONOCNE_I
//                 * OBD_VELKONOCNE_II
//                 * OBD_VELKONOCNE_TROJDNIE && (den == nedela)
//    -- je_aleluja_aleluja(): odpoved je kladna, ak je splnene niektore z nasledovnych
//                 * OBD_VELKONOCNA_OKTAVA
//                 * OBD_VELKONOCNE_TROJDNIE && (den == nedela)
//                 * _ZOSLANIE_DUCHA_SV && MODL_VESPERY
// 2007-04-10: Doplnené: Te Deum je vo veľkonočnej oktáve; nie je počas pôstu (ani len pre nedele)
// 2009-01-06: Doplnené: Te Deum je aj v oktáve narodenia Pána (vianočná oktáva)
// 2009-01-28: jednotlivé define presunuté na začiatok súboru, nakoľko ich používa nielen interpretParameter(), ale aj includeFile()

// 2007-11-20: doplnené @ifdef EXPORT_HTML_SPECIALS
void interpretParameter(short int typ, short int modlitba, char paramname[MAX_BUFFER], short int aj_navigacia = ANO) {
	short int zobrazit = NIE;
	short int je_sviatok_alebo_slavnost = NIE;
	short int podmienka = NIE;
	short int je_begin, je_end = NIE;
	short int exportovat_html_note = NIE;
	short int exportovat_html_tag = NIE;
	short int write = ANO; // due to #define EXPORT_RED_AND_NORMAL_STUFF()
	short int current_value = 0;

	char anchor[SMALL] = STR_EMPTY;

	char before[SMALL] = STR_EMPTY;
	char after[SMALL] = STR_EMPTY;

	char tag_to_export_begin[SMALL] = STR_EMPTY;
	char tag_to_export_end[SMALL] = STR_EMPTY;

	char popis_show[SMALL];
	char popis_hide[SMALL];

	_struct_sc sc;

	Log("interpretParameter(%s): Dumping by %s\n", paramname, paramname);

	// verse numbering
	if (equals(paramname, PARAM_CISLO_VERSA_BEGIN)) {
		if (_global_skip_in_prayer == NIE) {
			if (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VERSE)) {
				Export("<sup>");
			}
			else {
				// Log("  ruším writing to export file, kvôli PARAM_CISLO_VERSA_BEGIN...\n");
				_global_skip_in_prayer_2 = ANO;
			}
		}
	}// zobraziť/nezobraziť číslovanie veršov
	else if (equals(paramname, PARAM_CISLO_VERSA_END)) {
		if (_global_skip_in_prayer == NIE) {
			if (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VERSE)) {
				Export("</sup>");
			}
			else {
				// Log("  opäť writing to export file, PARAM_CISLO_VERSA_END...\n");
				_global_skip_in_prayer_2 = NIE;
			}
		}
	}// zobraziť/nezobraziť číslovanie veršov

	// verse numbering
	else if (equals(paramname, PARAM_ITALICS_COND_BEGIN)) {
		if (_global_skip_in_prayer == NIE) {
			if (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ITALICS_CONDITIONAL)) {
				Export("<i>");
			}
			else {
				// just print what follows
			}
		}
	}// zobraziť/nezobraziť číslovanie veršov
	else if (equals(paramname, PARAM_ITALICS_COND_END)) {
		if (_global_skip_in_prayer == NIE) {
			if (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ITALICS_CONDITIONAL)) {
				Export("</i>");
			}
			else {
				// nothing to do
			}
		}
	}// zobraziť/nezobraziť číslovanie veršov

	else if (equals(paramname, PARAM_KRIZIK)) {
		if (_global_skip_in_prayer == NIE) {
			// only when antiphone contained red cross
			if (ant_invitat_krizik > 0) {
				if (useWhenGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT)) {

					Export(HTML_COMMENT_END);

					DetailLog("exporting end of DIV for hiding part because of voice output...\n");
					// continue exporting text for TTS (voice output)
					export_div_to_continue_tts_voice_output(NIE);

					Export(HTML_COMMENT_BEGIN);
				}
				else {
					DetailLog("exporting red cross with nbsp after...\n");

					Export(HTML_COMMENT_END);
					ExportNonbreakingSpace(); // pre krížik na začiatku žalmu/chválospevu medzeru netreba
					Export("<" HTML_SPAN_RED ">" STR_CROSS "" HTML_SPAN_END);
					ExportNonbreakingSpace(); // pre krížik na konci chválospevu medzeru netreba
					Export(HTML_COMMENT_BEGIN);
				}
			}
		}
	}// zobraziť/nezobraziť krížik: should be used in invitatory prayer, Psalm 95, only

	// stuff in texts: TTS pause
	else if (equals(paramname, PARAM_PAUSE)
		|| equals(paramname, PARAM_PAUSE_SHORT))
	{
		if (_global_skip_in_prayer == NIE) {
			DetailLog("exporting TTS pause...\n");

			if (equals(paramname, PARAM_PAUSE)) {
				if (EXPORT_TTS_PAUSES) {
					Export("<" HTML_SPAN_TTS_PAUSE ">");
				}
			}
			else if (equals(paramname, PARAM_PAUSE_SHORT)) {
				if (EXPORT_TTS_PAUSES) {
					Export("<" HTML_SPAN_TTS_PAUSE_SHORT ">");
				}
			}

			if (EXPORT_TTS_PAUSES) {
				Export(HTML_SPAN_END "\n");
			}
		}
	}// stuff in texts: TTS pause

	// normal (black) stuff in psalmody (cross, asterisk)
	else if (equals(paramname, PARAM_NORMAL_ASTERISK)
		|| equals(paramname, PARAM_NORMAL_CROSS))
	{
		if (_global_skip_in_prayer == NIE) {
			DetailLog("exporting normal stuff with nbsp before...\n");

			if (EXPORT_RED_AND_NORMAL_STUFF(_global_modlitba)) {
				ExportNonbreakingSpace();
			}

			if (equals(paramname, PARAM_NORMAL_ASTERISK)) {
				if (EXPORT_TTS_PAUSES) {
					Export("<" HTML_SPAN_TTS_PAUSE ">");
				}
				if (EXPORT_RED_AND_NORMAL_STUFF(_global_modlitba)) {
					Export(STR_ASTERISK);
				}
			}
			else if (equals(paramname, PARAM_NORMAL_CROSS)) {
				if (EXPORT_TTS_PAUSES) {
					Export("<" HTML_SPAN_TTS_PAUSE_SHORT ">");
				}
				if (EXPORT_RED_AND_NORMAL_STUFF(_global_modlitba)) {
					Export(STR_CROSS);
				}
			}

			if (EXPORT_TTS_PAUSES) {
				Export(HTML_SPAN_END);
			}
		}
	}// normal (black) stuff

	// red asterisk, other "red stuff" (normal characters)
	else if (equals(paramname, PARAM_RED_ASTERISK)) {
		if (_global_skip_in_prayer == NIE) {
			DetailLog("exporting red stuff...\n");
			if (EXPORT_RED_AND_NORMAL_STUFF(_global_modlitba)) {
				Export("<" HTML_SPAN_RED ">%s" HTML_SPAN_END, paramname);
			}
		}
	}// show red asterisk, other "red stuff" (normal characters)

	// red triangle (end of psalm/canticle when doxology is not displayed), red cross (Unicode special characters)
	else if (equals(paramname, PARAM_RED_CROSS) || equals(paramname, PARAM_RED_CROSS_TXT)) {
		if (_global_skip_in_prayer == NIE) {
			DetailLog("exporting red cross with nbsp before...\n");
			if (EXPORT_RED_TRIANGLE) {
				ExportNonbreakingSpace();
				Export("<" HTML_SPAN_RED ">%s" HTML_SPAN_END, PARAM_RED_CROSS);
			}
		}
	}// show red cross
	else if (equals(paramname, PARAM_RED_TRIANGLE) || equals(paramname, PARAM_RED_TRIANGLE_TXT)) {
		if (_global_skip_in_prayer == NIE) {
			DetailLog("exporting red triangle with nbsp before...\n");
			if (EXPORT_RED_TRIANGLE) {
				ExportNonbreakingSpace();
				Export("<" HTML_SPAN_RED ">%s" HTML_SPAN_END, PARAM_RED_TRIANGLE);
			}
		}
	}// show red triangle

	else if (
		(equals(paramname, PARAM_CHVALOSPEV_BEGIN)) || (equals(paramname, PARAM_CHVALOSPEV_END))
		|| (equals(paramname, PARAM_TEDEUM_BEGIN)) || (equals(paramname, PARAM_TEDEUM_END))
		|| (equals(paramname, PARAM_JE_TEDEUM_BEGIN)) || (equals(paramname, PARAM_JE_TEDEUM_END))
		|| (equals(paramname, PARAM_OTCENAS_BEGIN)) || (equals(paramname, PARAM_OTCENAS_END))
		|| (equals(paramname, PARAM_ZOBRAZ_OTCENAS_UVOD_BEGIN)) || (equals(paramname, PARAM_ZOBRAZ_OTCENAS_UVOD_END))
		|| (equals(paramname, PARAM_ALELUJA_ALELUJA_BEGIN)) || (equals(paramname, PARAM_ALELUJA_ALELUJA_END))
		|| (equals(paramname, PARAM_ALELUJA_VO_VELKONOCNOM_BEGIN)) || (equals(paramname, PARAM_ALELUJA_VO_VELKONOCNOM_END))
		|| (equals(paramname, PARAM_ALELUJA_NIE_V_POSTE_BEGIN)) || (equals(paramname, PARAM_ALELUJA_NIE_V_POSTE_END))
		|| (equals(paramname, PARAM_JE_VIGILIA_BEGIN)) || (equals(paramname, PARAM_JE_VIGILIA_END))
		|| (equals(paramname, PARAM_KOMPLETORIUM_DVA_ZALMY_BEGIN)) || (equals(paramname, PARAM_KOMPLETORIUM_DVA_ZALMY_END))
		|| (equals(paramname, PARAM_RUBRIKA_BEGIN)) || (equals(paramname, PARAM_RUBRIKA_END))
		|| (equals(paramname, PARAM_VN_VYNECHAJ_BEGIN)) || (equals(paramname, PARAM_VN_VYNECHAJ_END))
		|| (equals(paramname, PARAM_COPYRIGHT_BEGIN)) || (equals(paramname, PARAM_COPYRIGHT_END))
		|| (equals(paramname, PARAM_SKRY_ANTIFONU_BEGIN)) || (equals(paramname, PARAM_SKRY_ANTIFONU_END))
		|| (equals(paramname, PARAM_ZOBRAZ_ANTIFONU_BEGIN)) || (equals(paramname, PARAM_ZOBRAZ_ANTIFONU_END))
		|| (equals(paramname, PARAM_SPOMIENKA_PRIVILEG_BEGIN)) || (equals(paramname, PARAM_SPOMIENKA_PRIVILEG_END))
		|| (equals(paramname, PARAM_ZAVER_BEGIN)) || (equals(paramname, PARAM_ZAVER_END))
		|| (equals(paramname, PARAM_ZAVER_KNAZ_DIAKON_BEGIN)) || (equals(paramname, PARAM_ZAVER_KNAZ_DIAKON_END))
		|| (equals(paramname, PARAM_ZAVER_OSTATNI_BEGIN)) || (equals(paramname, PARAM_ZAVER_OSTATNI_END))
		|| (equals(paramname, PARAM_MARIANSKE_ANTIFONY_BEGIN)) || (equals(paramname, PARAM_MARIANSKE_ANTIFONY_END))
		|| (equals(paramname, PARAM_TTS_HEADING_BEGIN)) || (equals(paramname, PARAM_TTS_HEADING_END))
		|| (equals(paramname, PARAM_INVITAT_COMMON_BEGIN)) || (equals(paramname, PARAM_INVITAT_COMMON_END))
		|| (equals(paramname, PARAM_INVITAT_PSALM_BEGIN("0"))) || (equals(paramname, PARAM_INVITAT_PSALM_END("0")))
		|| (equals(paramname, PARAM_INVITAT_PSALM_BEGIN("1"))) || (equals(paramname, PARAM_INVITAT_PSALM_END("1")))
		|| (equals(paramname, PARAM_INVITAT_PSALM_BEGIN("2"))) || (equals(paramname, PARAM_INVITAT_PSALM_END("2")))
		|| (equals(paramname, PARAM_INVITAT_PSALM_BEGIN("3"))) || (equals(paramname, PARAM_INVITAT_PSALM_END("3")))
		) {
		Log("_global_opt[OPT_1_CASTI_MODLITBY == %d] == %llu\n", OPT_1_CASTI_MODLITBY, _global_opt[OPT_1_CASTI_MODLITBY]);
		
		je_begin = (endsWith(paramname, (char *)KEYWORD_BEGIN));
		je_end = (endsWith(paramname, (char *)KEYWORD_END));

		podmienka = ANO;
		exportovat_html_note = NIE;
		exportovat_html_tag = NIE; // considered only when exportovat_html_note == ANO
		mystrcpy(tag_to_export_begin, STR_EMPTY, SMALL);
		mystrcpy(tag_to_export_end, STR_EMPTY, SMALL);

		if (startsWith(paramname, (char *)KEYWORD_PARAM_CHVALOSPEV)) {
			podmienka = podmienka && (useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_CHVALOSPEVY));
		}
		else if (startsWith(paramname, (char *)KEYWORD_TEDEUM)) {
			podmienka = podmienka && (useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_TEDEUM) && (_global_opt_tedeum == ANO) && (_global_skip_in_prayer == NIE));
		}
		else if (startsWith(paramname, (char *)KEYWORD_JE_TEDEUM)) {
			podmienka = podmienka && (_global_opt_tedeum == ANO);
		}
		else if (startsWith(paramname, (char *)KEYWORD_OTCENAS)) {
			podmienka = podmienka && (useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OTCENAS));
			exportovat_html_note = ANO;
		}
		else if (startsWith(paramname, (char*)KEYWORD_MARIANSKE_ANTIFONY)) {
			podmienka = podmienka && (useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_KOMPL_MARIA_ANT));
			exportovat_html_note = ANO;
		}
		else if (startsWith(paramname, (char*)KEYWORD_ZOBRAZ_OTCENAS_UVOD)) {
			podmienka = podmienka && (useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZOBRAZ_OTCENAS_UVOD));
			exportovat_html_note = ANO;
		}
		else if (startsWith(paramname, (char *)KEYWORD_INVITAT_COMMON)) {
			podmienka = podmienka && !(_global_skip_in_prayer >= ANO);
			exportovat_html_note = ANO;

			if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES)) {
				podmienka = NIE;
			}
		}
		else if (startsWith(paramname, (char *)KEYWORD_INVITAT_PSALM_SIMPLE)) {
			podmienka = podmienka && !(_global_skip_in_prayer >= ANO);
			exportovat_html_note = ANO;

			if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES)) {
				short int ktory = getGlobalOption(OPT_6_ALTERNATIVES_MULTI, BASE_OPT_6_PSALM_MULTI);

				switch (ktory) {
				case 0: podmienka = podmienka && startsWith(paramname, (char *)KEYWORD_INVITAT_PSALM("0"));
					break;
				case 1: podmienka = podmienka && startsWith(paramname, (char *)KEYWORD_INVITAT_PSALM("1"));
					break;
				case 2: podmienka = podmienka && startsWith(paramname, (char *)KEYWORD_INVITAT_PSALM("2"));
					break;
				case 3: podmienka = podmienka && startsWith(paramname, (char *)KEYWORD_INVITAT_PSALM("3"));
					break;
				} // switch (ktory)
			}
		}
		else if (startsWith(paramname, (char *)KEYWORD_ALELUJA_ALELUJA)) {
			podmienka = podmienka && !(_global_skip_in_prayer >= ANO) && (je_aleluja_aleluja);
			exportovat_html_note = ANO;
		}
		else if (startsWith(paramname, (char *)KEYWORD_ALELUJA_VO_VELKONOCNOM)) {
			podmienka = podmienka && (je_velka_noc);
			exportovat_html_note = ANO;
		}
		else if (startsWith(paramname, (char *)KEYWORD_ALELUJA_NIE_V_POSTE)) {
			podmienka = podmienka && (!je_post);
			exportovat_html_note = ANO;
		}
		else if (startsWith(paramname, (char *)KEYWORD_JE_VIGILIA)) {
			podmienka = podmienka && (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PC_VIGILIA) && (je_vigilia));
			_global_som_vo_vigilii = (je_begin);
		}
		else if (startsWith(paramname, (char *)KEYWORD_KOMPLETORIUM_DVA_ZALMY)) {
			Log("interpretParameter(): _global_modl_kompletorium.pocet_zalmov == %d...\n", _global_modl_kompletorium.pocet_zalmov);
			Log("interpretParameter(): _global_modl_prve_kompletorium.pocet_zalmov == %d...\n", _global_modl_prve_kompletorium.pocet_zalmov);
			Log("_global_modl_kompletorium.alternativy == %d; _global_modl_prve_kompletorium.alternativy == %d...\n", _global_modl_kompletorium.alternativy, _global_modl_prve_kompletorium.alternativy);
			podmienka = podmienka && (_global_pocet_zalmov_kompletorium > 1);
		}
		else if (startsWith(paramname, (char *)KEYWORD_RUBRIKA)) {
			podmienka = podmienka && (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_RUBRIKY) && !isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT));
			exportovat_html_note = ANO;
		}
		else if (startsWith(paramname, (char *)KEYWORD_VN_VYNECHAJ)) {
			Log("podmienka == %d; _global_den.denvr == %d, VELKONOCNA_NEDELA == %d...\n", podmienka, _global_den.denvr, VELKONOCNA_NEDELA);
			podmienka = podmienka && (_global_den.denvr != VELKONOCNA_NEDELA);
			Log("podmienka == %d...\n", podmienka);
			exportovat_html_note = ANO;
			_global_skip_in_prayer_vnpc = (!podmienka) && (je_begin);
		}
		else if (startsWith(paramname, (char *)KEYWORD_COPYRIGHT)) {
			podmienka = podmienka && !(isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT));
			podmienka = podmienka && ((query_type != PRM_STATIC_TEXT) || (_global_pocet_svatych <= STATIC_TEXT_ORDINARIUM)); // display (c) only for some static texts
			exportovat_html_note = ANO;
		}
		else if (startsWith(paramname, (char *)KEYWORD_SKRY_ANTIFONU)) {
			podmienka = podmienka && (_global_ant_mcd_rovnake == NIE);
			exportovat_html_note = ANO;
		}
		else if (startsWith(paramname, (char *)KEYWORD_ZOBRAZ_ANTIFONU)) {
			podmienka = podmienka && (_global_ant_mcd_rovnake == ANO);
			exportovat_html_note = ANO;
		}
		else if (startsWith(paramname, (char *)KEYWORD_SPOMIENKA_PRIVILEG)) {
			podmienka = podmienka && (je_privileg && je_modl_spomprivileg);
			exportovat_html_note = ANO;
		}
		else if (startsWith(paramname, (char *)KEYWORD_ZAVER_OSTATNI)) {
			podmienka = podmienka && (useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZAVER) && !useWhenGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_ZAVER_KNAZ_DIAKON));
			exportovat_html_note = ANO;
		}
		else if (startsWith(paramname, (char *)KEYWORD_ZAVER_KNAZ_DIAKON)) {
			podmienka = podmienka && (useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZAVER) && useWhenGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_ZAVER_KNAZ_DIAKON));
			exportovat_html_note = ANO;
		}
		else if (startsWith(paramname, (char *)KEYWORD_ZAVER)) {
			// must be after two previous! (the same prefix)
			podmienka = podmienka && (useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZAVER));
			exportovat_html_note = ANO;
		}
		else if (startsWith(paramname, (char *)KEYWORD_TTS_HEADING)) {
			exportovat_html_note = ANO;
			exportovat_html_tag = ANO;
			mystrcpy(tag_to_export_begin, "<" HTML_DIV_TTS_HEADING ">", SMALL);
			mystrcpy(tag_to_export_end, HTML_DIV_END, SMALL);
		}

		if (podmienka) {
			// show
			if (exportovat_html_note) {
				if (je_begin) {
#if defined(EXPORT_HTML_SPECIALS)
					Export("show %s", paramname);
#endif
					Export(HTML_COMMENT_END);

					if (exportovat_html_tag) {
						Export(tag_to_export_begin);
						Export(HTML_COMMENT_BEGIN);
					}
				}
				else if (je_end) {
					if (exportovat_html_tag) {
						Export(HTML_COMMENT_END);
						Export(tag_to_export_end);
					}

					Export(HTML_COMMENT_BEGIN);
#if defined(EXPORT_HTML_SPECIALS)
					Export("show %s", paramname);
#endif
				}
			}
			Log("  `%s': %s\n", paramname, (je_begin) ? "..." : "copied.");
		}
		else {
			// do not show
			if (je_begin) {
				_global_skip_in_prayer += ANO; // increment
			}
			else if (je_end) {
				_global_skip_in_prayer -= ANO; // decrement
			}
#if defined(EXPORT_HTML_SPECIALS)
			Export("do not show %s", paramname);
#endif
			Log("  `%s' %s\n", paramname, (je_begin) ? "skipping..." : "skipped.");
		}
	}

	// podmienka zosilnená kvôli sláva otcu vo vigíliách (vtedy preskakujeme)
	else if ((equals(paramname, PARAM_SLAVAOTCU_BEGIN) || equals(paramname, PARAM_SLAVAOTCU_SPEC_BEGIN)) && (!((_global_som_vo_vigilii == ANO) && ((!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PC_VIGILIA)) || !(je_vigilia))))) {
		_global_pocet_slava_otcu = _global_pocet_slava_otcu + 1;
		// 2007-05-18: zosilnená podmienka, aby Sláva Otcu nebolo pre špeciálne prípady 
		// 2007-12-04: opravená podmienka, pretože nefungovala pre modlitby odlišné od ranných chvál
		// 2011-04-28: doplnením ďalších "Sláva Otcu", ktoré sa rozbaľujú, sa posunulo číslovanie, a tak radšej podmienku "_global_pocet_slava_otcu == 2" zrušíme
		// 2011-04-29: doplnené Sláva Otcu "špeciálne" pre účely chválospevu Dan 3, 57-88. 56, kde nie je "Sláva Otcu" (pôvodne to bolo dané poradím, ale templáty pre rôzne jazyky majú rozličné poradie tohto "Sláva Otcu")
		if (useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_SLAVA_OTCU) && (
			_global_modlitba != MODL_RANNE_CHVALY
			|| (_global_modlitba == MODL_RANNE_CHVALY
				&& !(equals(paramname, PARAM_SLAVAOTCU_SPEC_BEGIN) && equals(_global_modl_ranne_chvaly.zalm2.anchor, "CHVAL_DAN3,57-88.56"))
				)
			)) {
			// zobrazit Slava Otcu
#if defined(EXPORT_HTML_SPECIALS)
			Export("zobraziť Sláva Otcu(%d)", _global_pocet_slava_otcu);
#endif
			Export(HTML_COMMENT_END);
			Log("  `Slava Otcu': begin...\n");
		}
		else {
			// nezobrazovat Slava Otcu
			_global_skip_in_prayer += ANO; // increment
#if defined(EXPORT_HTML_SPECIALS)
			Export("nezobraziť Sláva Otcu (%d)", _global_pocet_slava_otcu);
#endif
			Log("  `Slava Otcu' skipping...\n");
		}
	}
	// podmienka zosilnená kvôli sláva otcu vo vigíliách (vtedy preskakujeme)
	else if ((equals(paramname, PARAM_SLAVAOTCU_END) || equals(paramname, PARAM_SLAVAOTCU_SPEC_END)) && (!((_global_som_vo_vigilii == ANO) && ((!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PC_VIGILIA)) || !(je_vigilia))))) {
		// 2007-05-18: zosilnená podmienka, aby Sláva Otcu nebolo pre špeciálne prípady 
		// 2007-12-04: opravená podmienka, pretože nefungovala pre modlitby odlišné od ranných chvál
		// 2011-04-28: doplnením ďalších "Sláva Otcu", ktoré sa rozbaľujú, sa posunulo číslovanie, a tak radšej podmienku "_global_pocet_slava_otcu == 2" zrušíme
		// 2011-04-29: doplnené Sláva Otcu "špeciálne" pre účely chválospevu Dan 3, 57-88. 56, kde nie je "Sláva Otcu" (pôvodne to bolo dané poradím, ale templáty pre rôzne jazyky majú rozličné poradie tohto "Sláva Otcu")
		if (useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_SLAVA_OTCU) && (
			_global_modlitba != MODL_RANNE_CHVALY
			|| (_global_modlitba == MODL_RANNE_CHVALY
				&& !(equals(paramname, PARAM_SLAVAOTCU_SPEC_END) && equals(_global_modl_ranne_chvaly.zalm2.anchor, "CHVAL_DAN3,57-88.56"))
				)
			)) {
			Export(HTML_COMMENT_BEGIN);
#if defined(EXPORT_HTML_SPECIALS)
			Export("zobraziť Sláva Otcu(%d)", _global_pocet_slava_otcu);
#endif
			Log("  `Slava Otcu': copied.\n");
		}
		else {
			// nezobrazovat Slava Otcu
			_global_skip_in_prayer -= ANO; // decrement | was: _global_skip_in_prayer = NIE;
			Log("  `Slava Otcu' (%d) skipped.\n", _global_pocet_slava_otcu);
		}
	}

	else if (equals(paramname, PARAM_NADPIS)) {
		ExportHtmlOnly("nadpis:begin-->");
		Export(_global_string_modlitba);
		ExportHtmlOnly("<!--nadpis:end");
	} // PARAM_NADPIS

	else if (equals(paramname, PARAM_PODNADPIS)) {
		ExportHtmlOnly("podnadpis:begin-->");
		Export(_global_string_podnadpis);
		ExportHtmlOnly("<!--podnadpis:end");
	} // PARAM_PODNADPIS

	else if (equals(paramname, PARAM_SPOL_CAST)) {
		Log("  _global_opt[OPT_1_CASTI_MODLITBY] & BIT_OPT_1_ZOBRAZ_SPOL_CAST: %d: (voice output: %d)\n", isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZOBRAZ_SPOL_CAST), isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT));
		Log("  _global_den.typslav == %d (%s)...\n", _global_den.typslav, nazov_slavenia(_global_den.typslav));

		zobrazit = (useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZOBRAZ_SPOL_CAST));

		if (zobrazit == ANO) {
			// ďalšie rozhodovanie
			Log("_global_poradie_svaty == %d...\n", _global_poradie_svaty);
			// pre ľubovoľné aj záväzné spomienky nemá význam | č. 236 VSLH: V modlitbe cez deň, čiže predpoludním, napoludnie a popoludní, a v kompletóriu sa neberie nič z ofícia o svätom, všetko je zo všedného dňa.
			if (_global_poradie_svaty == 0) {
				zobrazit = (((_global_den.typslav != SLAV_LUB_SPOMIENKA) && (_global_den.typslav != SLAV_SPOMIENKA)) || ((_global_modlitba != MODL_PREDPOLUDNIM) && (_global_modlitba != MODL_NAPOLUDNIE) && (_global_modlitba != MODL_POPOLUDNI) && (_global_modlitba != MODL_KOMPLETORIUM) && (_global_modlitba != MODL_PRVE_KOMPLETORIUM) && (_global_modlitba != MODL_DRUHE_KOMPLETORIUM)));
				Log("_global_den.spolcast == %d\n", _global_den.spolcast);
				Log("zobrazit == %d...\n", zobrazit);
				// napokon rozkódujeme, čo je v _global_den.spolcast
				sc = _decode_spol_cast(_global_den.spolcast);
				Log("sc.a1 == %d (%s)...\n", sc.a1, nazov_spolc(sc.a1));
				zobrazit = zobrazit && je_spolocna_cast_urcena(sc.a1);
				Log("zobrazit == %d...\n", zobrazit);
				// je_sviatok_alebo_slavnost = (je_global_den_slavnost || je_global_den_sviatok);
			}
			// pre miestne sviatky má zmysel pre MCD (nie pre kompletórium)
			else {
				// _global_poradie_svaty > 0
				zobrazit = zobrazit && ((_global_modlitba != MODL_KOMPLETORIUM) && (_global_modlitba != MODL_PRVE_KOMPLETORIUM) && (_global_modlitba != MODL_DRUHE_KOMPLETORIUM));
				if (zobrazit == ANO) {
					if (JE_PORADIE_SVATY_OK(_global_poradie_svaty)) {
						zobrazit = (((_global_svaty(_global_poradie_svaty).typslav != SLAV_LUB_SPOMIENKA) && (_global_svaty(_global_poradie_svaty).typslav != SLAV_SPOMIENKA)) || ((_global_modlitba != MODL_PREDPOLUDNIM) && (_global_modlitba != MODL_NAPOLUDNIE) && (_global_modlitba != MODL_POPOLUDNI) && (_global_modlitba != MODL_KOMPLETORIUM) && (_global_modlitba != MODL_PRVE_KOMPLETORIUM) && (_global_modlitba != MODL_DRUHE_KOMPLETORIUM)));
						zobrazit = zobrazit || ((MIESTNE_SLAVENIE_LOKAL_SVATY(_global_poradie_svaty)) && (je_modlitba_cez_den(_global_modlitba)));
						// napokon rozkódujeme, čo je v _global_svaty(_global_poradie_svaty).spolcast
						sc = _decode_spol_cast(_global_svaty(_global_poradie_svaty).spolcast);
						je_sviatok_alebo_slavnost = (_je_global_svaty_i_slavnost(_global_poradie_svaty)) || (_je_global_svaty_i_sviatok(_global_poradie_svaty));
					}
					else if (_global_poradie_svaty == PORADIE_PM_SOBOTA) {
						zobrazit = (((_global_pm_sobota.typslav != SLAV_LUB_SPOMIENKA) && (_global_pm_sobota.typslav != SLAV_SPOMIENKA)) || ((_global_modlitba != MODL_PREDPOLUDNIM) && (_global_modlitba != MODL_NAPOLUDNIE) && (_global_modlitba != MODL_POPOLUDNI) && (_global_modlitba != MODL_KOMPLETORIUM) && (_global_modlitba != MODL_PRVE_KOMPLETORIUM) && (_global_modlitba != MODL_DRUHE_KOMPLETORIUM)));
						// zobrazit = zobrazit || ((MIESTNE_SLAVENIE_LOKAL_SVATY(_global_poradie_svaty)) && (je_modlitba_cez_den(_global_modlitba)));
						// napokon rozkódujeme, čo je v _global_pm_sobota.spolcast
						sc = _decode_spol_cast(_global_pm_sobota.spolcast);
					}
					zobrazit = zobrazit && je_spolocna_cast_urcena(sc.a1);
				}// ináč nemá zmysel komplikované rozhodovanie (pre kompletórium)
			}
		}// ináč nemá zmysel komplikované rozhodovanie (ak nie je zvolený BIT_OPT_1_ZOBRAZ_SPOL_CAST)
		if (zobrazit == ANO) {
			Log("including SPOL_CAST\n");

			Export("spol_cast:begin-->");

			_export_global_string_spol_cast(ANO);

			if (pouzit_na_spomienky_casti_zo_spolocnych_casti || je_sviatok_alebo_slavnost) {
				Log("pouzit_na_spomienky_casti_zo_spolocnych_casti || je_sviatok_alebo_slavnost...\n");
				if (je_spolocna_cast_urcena(sc.a2)) {
					Log("je_spolocna_cast_urcena(sc.a2)...\n");
					Export(HTML_DIV_BEGIN);
					_export_link_communia((sc.a2 != odfiltrujSpolCast(modlitba, _global_opt[OPT_3_SPOLOCNA_CAST])) ? sc.a2 : sc.a1, (char *)HTML_SPAN_RED_SMALL, (char *)HTML_CLASS_QUIET, (char *)STR_EMPTY, (char *)STR_EMPTY, /* anchor */ (char *)PARAM_SPOL_CAST, (char *)HTML_SPAN_END);
					if (je_spolocna_cast_urcena(sc.a3)) {
						Log("je_spolocna_cast_urcena(sc.a3)...\n");
						_export_link_communia((sc.a3 != odfiltrujSpolCast(modlitba, _global_opt[OPT_3_SPOLOCNA_CAST])) ? sc.a3 : sc.a1, (char *)HTML_SPAN_RED_SMALL, (char *)HTML_CLASS_QUIET, (char *)STR_EMPTY, (char *)STR_EMPTY, /* anchor */ (char *)PARAM_SPOL_CAST, (char *)HTML_SPAN_END);
					}
					Export(HTML_DIV_END);
				}
			}

			ExportHtmlOnly("<!--spol_cast:end");
		}
		else {
			ExportHtmlOnly("[skipping SPOL_CAST]");
			Log("skipping SPOL_CAST\n");
		}
	} // PARAM_SPOL_CAST

	/* must not be "else" before this if due to repeatance of PARAM_NADPIS */

	if ((equals(paramname, PARAM_CHVALOSPEV))
		|| (equals(paramname, PARAM_ZAVER))
		|| (equals(paramname, PARAM_ZAVER_KNAZ_DIAKON))
		|| (equals(paramname, PARAM_ZAVER_OSTATNI))
		|| (equals(paramname, PARAM_OTCENAS))
		|| (equals(paramname, PARAM_ZOBRAZ_OTCENAS_UVOD))
		|| (equals(paramname, PARAM_TEDEUM))
		|| (equals(paramname, PARAM_DOPLNKOVA_PSALMODIA))
		|| (equals(paramname, PARAM_PSALMODIA))
		|| (equals(paramname, PARAM_PSALMODIA_TRI_TYZDNE))
		|| (equals(paramname, PARAM_ZVOLANIA))
		|| (equals(paramname, PARAM_POPIS))
		|| (equals(paramname, PARAM_SLAVAOTCU))
		|| (equals(paramname, PARAM_RESPONZ))
		|| (equals(paramname, PARAM_NADPIS))
		|| (equals(paramname, PARAM_KRATSIE_PROSBY))
		|| (equals(paramname, PARAM_VAR_CITANIE2))
		|| (equals(paramname, PARAM_VIGILIA))
		|| (equals(paramname, PARAM_ALT_HYMNUS))
		|| (equals(paramname, PARAM_ALT_HYMNUS_OCR_34))
		|| (equals(paramname, PARAM_ALT_HYMNUS_MULTI))
		|| (equals(paramname, PARAM_ALT_CITANIE2_MULTI))
		|| (equals(paramname, PARAM_ALT_CITANIE1_MULTI))
		|| (equals(paramname, PARAM_ALT_ANTIFONA_MULTI))
		|| (equals(paramname, PARAM_ALT_MODLITBA_MULTI))
		|| (equals(paramname, PARAM_ALT_OTCENAS_UVOD_MULTI))
		|| (equals(paramname, PARAM_ALT_PROSBY_MULTI))
		|| (equals(paramname, PARAM_ALT_UKONKAJ_MULTI))
		|| (equals(paramname, PARAM_ALT_KCIT_RESP_MULTI))
		|| (equals(paramname, PARAM_ALT_KRESP_MULTI))
		|| (equals(paramname, PARAM_ALT_PSALM_MULTI))
		|| (equals(paramname, PARAM_ALT_MARIA_ANT_MULTI))
		|| (equals(paramname, PARAM_SPOL_CAST_SPOM))
		|| (equals(paramname, PARAM_OVERRIDE_STUPEN_SLAVENIA))
		|| (equals(paramname, PARAM_STUPEN_SLAVENIA_SVI_SLAV))
		|| (equals(paramname, PARAM_MARIANSKE_ANTIFONY))
		|| (equals(paramname, PARAM_OKTAVA_PRVE_DRUHE_KOMPL))
		) {

		// Log("(if ((equals(paramname == %s)): _global_opt[OPT_2_HTML_EXPORT] & BIT_OPT_2_ROZNE_MOZNOSTI == %llu: \n", paramname, _global_opt[OPT_2_HTML_EXPORT] & BIT_OPT_2_ROZNE_MOZNOSTI);

		unsigned long long bit;
		short int opt = OPT_1_CASTI_MODLITBY; // for some options must be changed e. g. to OPT_5_ALTERNATIVES
		short int multi = NIE; // multi == 0 => only on/off (show/hide, two values, one bit) setting; multi == 1 => multiple alternatives
		short int multi_count = 0;

		// note that in some cases must be set vice-versa; see function _export_link_show_hide()
		mystrcpy(popis_show, html_text_option_skryt[_global_jazyk], SMALL);
		mystrcpy(popis_hide, html_text_option_zobrazit[_global_jazyk], SMALL);

		// these are used for multi-value choces switching (hymns, 1st reading, 2nd reading,...); PARAM_ALT_..._MULTI
		char new_anchor[MAX_STR_AF_ANCHOR];
		char new_anchor2[MAX_STR_AF_ANCHOR];
		mystrcpy(new_anchor, STR_EMPTY, MAX_STR_AF_ANCHOR);
		mystrcpy(new_anchor2, STR_EMPTY, MAX_STR_AF_ANCHOR);

		short int specific_string = HTML_SEQUENCE_NONE;

		mystrcpy(anchor, paramname, SMALL);

		podmienka = (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI));
		podmienka = podmienka && (_global_skip_in_prayer == NIE);
		podmienka = podmienka && (typ != PRM_XML);

		if (equals(paramname, PARAM_OTCENAS)) {
			bit = BIT_OPT_1_OTCENAS;
			if (_global_jazyk == JAZYK_HU) {
				mystrcpy(popis_show, HTML_TEXT_HU_OPTION_SKRYT, SMALL);
				mystrcpy(popis_hide, HTML_TEXT_HU_OPTION_ZOBRAZIT, SMALL);
			}
		}
		else if (equals(paramname, PARAM_ZOBRAZ_OTCENAS_UVOD)) {
			bit = BIT_OPT_1_ZOBRAZ_OTCENAS_UVOD;
			sprintf(popis_show, "%s %s", html_text_option_skryt[_global_jazyk], html_text_opt_1_otcenas_uvod[_global_jazyk]);
			sprintf(popis_hide, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_1_otcenas_uvod[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_MARIANSKE_ANTIFONY)) {
			bit = BIT_OPT_1_KOMPL_MARIA_ANT;
			if (_global_jazyk == JAZYK_HU) {
				mystrcpy(popis_show, HTML_TEXT_HU_OPTION_SKRYT, SMALL);
				mystrcpy(popis_hide, HTML_TEXT_HU_OPTION_ZOBRAZIT, SMALL);
			}
		}
		else if (equals(paramname, PARAM_ZAVER)) {
			bit = BIT_OPT_1_ZAVER;
			if (_global_jazyk == JAZYK_HU) {
				mystrcpy(popis_show, HTML_TEXT_HU_OPTION1_ZAVER_HIDE, SMALL);
				mystrcpy(popis_hide, HTML_TEXT_HU_OPTION1_ZAVER_SHOW, SMALL);
			}
			else {
				sprintf(popis_show, "%s %s", html_text_option_skryt[_global_jazyk], html_text_opt_1_zaver[_global_jazyk]);
				sprintf(popis_hide, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_1_zaver[_global_jazyk]);
			}
		}
		// ToDo: for PARAM_ZAVER_OSTATNI and PARAM_ZAVER_KNAZ_DIAKON, respect (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES)) to show both conclusions
		else if (equals(paramname, PARAM_ZAVER_OSTATNI)) {
			opt = OPT_5_ALTERNATIVES;
			bit = BIT_OPT_5_ZAVER_KNAZ_DIAKON;
			podmienka = podmienka && (!isGlobalOption(opt, bit));
			mystrcpy(popis_show, html_text_opt_5_zaver_knaz_diakon_NORMAL[_global_jazyk], SMALL); // not used
			mystrcpy(popis_hide, html_text_opt_5_zaver_knaz_diakon[_global_jazyk], SMALL);
		}
		else if (equals(paramname, PARAM_ZAVER_KNAZ_DIAKON)) {
			opt = OPT_5_ALTERNATIVES;
			bit = BIT_OPT_5_ZAVER_KNAZ_DIAKON;
			podmienka = podmienka && (isGlobalOption(opt, bit));
			mystrcpy(popis_show, html_text_opt_5_zaver_knaz_diakon_NORMAL[_global_jazyk], SMALL);
			mystrcpy(popis_hide, html_text_opt_5_zaver_knaz_diakon[_global_jazyk], SMALL); // not used
		}
		else if (equals(paramname, PARAM_CHVALOSPEV)) {
			bit = BIT_OPT_1_CHVALOSPEVY;
			if (_global_jazyk == JAZYK_HU) {
				mystrcpy(popis_show, HTML_TEXT_HU_OPTION_SKRYT, SMALL);
				mystrcpy(popis_hide, HTML_TEXT_HU_OPTION_ZOBRAZIT, SMALL);
			}
		}
		else if (equals(paramname, PARAM_TEDEUM)) {
			bit = BIT_OPT_1_TEDEUM;
			if (_global_jazyk == JAZYK_HU) {
				mystrcpy(popis_show, HTML_TEXT_HU_OPTION_SKRYT, SMALL);
				mystrcpy(popis_hide, HTML_TEXT_HU_OPTION_ZOBRAZIT, SMALL);
			}
		}
		else if (equals(paramname, PARAM_ZVOLANIA)) {
			bit = BIT_OPT_1_PROSBY_ZVOLANIE;
			mystrcpy(popis_show, html_text_option_skryt_zvolania[_global_jazyk], SMALL);
			mystrcpy(popis_hide, html_text_option_zobrazit_zvolania[_global_jazyk], SMALL);
			podmienka = podmienka && (!(((_global_modlitba == MODL_VESPERY) || (_global_modlitba == MODL_PRVE_VESPERY)) && (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_VESP_KRATSIE_PROSBY)))); // ak sú zvolené kratšie prosby, tam sa neopakuje zvolanie (zatiaľ)
		}
		else if (equals(paramname, PARAM_KRATSIE_PROSBY)) {
			bit = BIT_OPT_1_VESP_KRATSIE_PROSBY;
			mystrcpy(popis_show, html_text_option_skryt_kratsie_prosby[_global_jazyk], SMALL);
			mystrcpy(popis_hide, html_text_option_zobrazit_kratsie_prosby[_global_jazyk], SMALL);
		}
		else if (equals(paramname, PARAM_VAR_CITANIE2)) {
			opt = OPT_0_SPECIALNE;
			bit = BIT_OPT_0_ALTERNATIVE_READINGS;
			podmienka = podmienka && (_global_jazyk == JAZYK_CZ) && (je_post_I_a_II); // (isGlobalOption(opt, bit));

			// slávnosť sv. Jozefa nemá vlastné alternatívne čítanie
			if (je_slavnost_sv_Jozefa_prekladana_na_20MAR || je_slavnost_sv_Jozefa_prekladana_pred_Kvetnu_nedenu) {
				podmienka = NIE;
			}
			else {
				podmienka = podmienka && !((_global_den.den == 19) && (_global_den.mesiac == MES_MAR + 1) && (_global_den.typslav == SLAV_SLAVNOST));
			}

			// slávnosť Zvestovania Pána nemá vlastné alternatívne čítanie
			if (je_slavnost_Zvestovania_prekladana_na_26MAR || je_slavnost_Zvestovania_prekladana_po_Velkonocnej_oktave_MAR || je_slavnost_Zvestovania_prekladana_po_Velkonocnej_oktave_APR) {
				podmienka = NIE;
			}
			else {
				podmienka = podmienka && !((_global_den.den == 25) && (_global_den.mesiac == MES_MAR + 1) && (_global_den.typslav == SLAV_SLAVNOST));
			}

			mystrcpy(popis_show, html_text_opt_0_alternative_readings_NORMAL[_global_jazyk], SMALL);
			mystrcpy(popis_hide, html_text_opt_0_alternative_readings[_global_jazyk], SMALL);
		}
		else if (equals(paramname, PARAM_DOPLNKOVA_PSALMODIA)) {
			bit = BIT_OPT_1_MCD_DOPLNKOVA;
			Log("  _global_den.typslav == %d (%s)...\n", _global_den.typslav, nazov_slavenia(_global_den.typslav));
			Log("  _global_den.smer == %d...\n", _global_den.smer);
			podmienka = podmienka && (!(je_len_doplnkova_psalmodia(_global_modlitba)));
			podmienka = podmienka && (je_modlitba_cez_den(_global_modlitba));
			mystrcpy(popis_show, html_text_opt_1_mcd_zalmy_nie_ine_short[_global_jazyk], SMALL);
			mystrcpy(popis_hide, html_text_opt_1_mcd_zalmy_ine_short[_global_jazyk], SMALL);
		}
		else if (equals(paramname, PARAM_PSALMODIA_TRI_TYZDNE)) {
			bit = BIT_OPT_1_MCD_ZALTAR_TRI;
			Log("  _global_den.typslav == %d (%s)...\n", _global_den.typslav, nazov_slavenia(_global_den.typslav));
			Log("  _global_den.smer == %d...\n", _global_den.smer);
			podmienka = podmienka && (!(je_len_doplnkova_psalmodia(_global_modlitba)));
			podmienka = podmienka && (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA));
			podmienka = podmienka && (je_modlitba_cez_den(_global_modlitba));
			mystrcpy(popis_show, html_text_opt_1_mcd_zalmy_nie_tri_short[_global_jazyk], SMALL);
			mystrcpy(popis_hide, html_text_opt_1_mcd_zalmy_tri_short[_global_jazyk], SMALL);
		}
		else if (equals(paramname, PARAM_POPIS)) {
			bit = BIT_OPT_1_SKRY_POPIS;
			mystrcpy(popis_show, html_text_option_zobrazit[_global_jazyk], SMALL);
			mystrcpy(popis_hide, html_text_option_skryt[_global_jazyk], SMALL);
			podmienka = podmienka && (je_popis);
		}
		else if (equals(paramname, PARAM_SLAVAOTCU)) {
			bit = BIT_OPT_1_SLAVA_OTCU;
			sprintf(popis_show, "%s %s", html_text_option_skryt[_global_jazyk], html_text_opt_1_slava_otcu[_global_jazyk]);
			sprintf(popis_hide, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_1_slava_otcu[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_RESPONZ)) {
			bit = BIT_OPT_1_PLNE_RESP;
			podmienka = podmienka && ((_global_modlitba == MODL_POSV_CITANIE) || (_global_modlitba == MODL_RANNE_CHVALY) || (_global_modlitba == MODL_VESPERY) || (_global_modlitba == MODL_PRVE_VESPERY) || (_global_modlitba == MODL_DRUHE_VESPERY) || (_global_modlitba == MODL_KOMPLETORIUM) || (_global_modlitba == MODL_PRVE_KOMPLETORIUM) || (_global_modlitba == MODL_DRUHE_KOMPLETORIUM));
			if (_global_modlitba == MODL_POSV_CITANIE) {
				specific_string = HTML_SEQUENCE_PARAGRAPH; // HTML_P_BEGIN
			}
			sprintf(popis_show, "%s %s", html_text_option_skryt[_global_jazyk], html_text_opt_1_plne_resp[_global_jazyk]);
			sprintf(popis_hide, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_1_plne_resp[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_NADPIS)) {
			bit = BIT_OPT_1_RUBRIKY;
			specific_string = HTML_SEQUENCE_LINE_BREAK; // HTML_LINE_BREAK
			sprintf(popis_show, "%s %s", html_text_option_skryt[_global_jazyk], html_text_opt_1_rubriky[_global_jazyk]);
			sprintf(popis_hide, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_1_rubriky[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_SPOL_CAST_SPOM)) {
			bit = BIT_OPT_1_SPOMIENKA_SPOL_CAST;
			podmienka = podmienka && ((_global_den.typslav == SLAV_SPOMIENKA) || (_global_den.typslav == SLAV_LUB_SPOMIENKA));
			sc = _decode_spol_cast(_global_den.spolcast);
			podmienka = podmienka && je_spolocna_cast_urcena(sc.a1);
			Log("podmienka == %d [_global_den.spolcast == %d; sc.a1 = %d]\n", podmienka, _global_den.spolcast, sc.a1);
			podmienka = podmienka && !isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OVERRIDE_STUP_SLAV);
			Log("podmienka == %d [isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OVERRIDE_STUP_SLAV) == %d]\n", podmienka, isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OVERRIDE_STUP_SLAV));
			specific_string = HTML_SEQUENCE_DIV;
			sprintf(popis_show, "%s", html_text_opt_1_spomienka_spolcast_NIE[_global_jazyk]);
			sprintf(popis_hide, "%s", html_text_opt_1_spomienka_spolcast[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_OVERRIDE_STUPEN_SLAVENIA)) {
			bit = BIT_OPT_1_OVERRIDE_STUP_SLAV;
			podmienka = podmienka && ((_global_den.typslav == SLAV_SVIATOK) || (_global_den.typslav == SLAV_SPOMIENKA) || (_global_den.typslav == SLAV_LUB_SPOMIENKA));
			Log("podmienka == %d [_global_den.typslav == %d, override == %d]\n", podmienka, _global_den.typslav, _typslav_override(_global_den.typslav));
			podmienka = podmienka && (_global_poradie_svaty != PORADIE_PM_SOBOTA);
			Log("podmienka == %d [_global_poradie_svaty == %d, PORADIE_PM_SOBOTA == %d]\n", podmienka, _global_poradie_svaty, PORADIE_PM_SOBOTA);
			sprintf(popis_show, "%s", html_text_opt_1_override_stupen_slavenia_NIE[_global_jazyk]);
			sprintf(popis_hide, "%s – %s", html_text_opt_1_override_stupen_slavenia[_global_jazyk], ((_global_den.typslav == SLAV_SVIATOK) || (_typslav_override(_global_den.typslav) == SLAV_SLAVNOST) || isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_STUP_SVIATOK_SLAVNOST) ? html_text_opt_1_slavit_ako_slavnost[_global_jazyk] : html_text_opt_1_slavit_ako_sviatok[_global_jazyk]));
		}
		else if (equals(paramname, PARAM_STUPEN_SLAVENIA_SVI_SLAV)) {
			bit = BIT_OPT_1_STUP_SVIATOK_SLAVNOST;
			podmienka = podmienka && ((_global_den.typslav == SLAV_SPOMIENKA) || (_global_den.typslav == SLAV_LUB_SPOMIENKA));
			Log("podmienka == %d [_global_den.typslav == %d, override == %d]\n", podmienka, _global_den.typslav, _typslav_override(_global_den.typslav));
			podmienka = podmienka && (_global_poradie_svaty != PORADIE_PM_SOBOTA);
			Log("podmienka == %d [_global_poradie_svaty == %d, PORADIE_PM_SOBOTA == %d]\n", podmienka, _global_poradie_svaty, PORADIE_PM_SOBOTA);
			sprintf(popis_show, "%s", html_text_opt_1_slavit_ako_sviatok[_global_jazyk]);
			sprintf(popis_hide, "%s", html_text_opt_1_slavit_ako_slavnost[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_OKTAVA_PRVE_DRUHE_KOMPL)) {
			opt = OPT_5_ALTERNATIVES;
			bit = BIT_OPT_5_KOMPLETORIUM_OKTAVA;
			podmienka = podmienka && ((_global_den.litobd == OBD_VELKONOCNA_OKTAVA) || (_global_den.litobd == OBD_OKTAVA_NARODENIA));
			Log("podmienka == %d [_global_den.litobd == %d]\n", podmienka, _global_den.litobd);
			sprintf(popis_show, "%s %s", html_text_option_pouzit[_global_jazyk], html_text_opt_5_KomplOkt1[_global_jazyk]);
			sprintf(popis_hide, "%s %s", html_text_option_pouzit[_global_jazyk], html_text_opt_5_KomplOkt2[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_VIGILIA)) {
			bit = BIT_OPT_1_PC_VIGILIA;
			Log("podmienka == %d; _global_modlitba == %d; _je_global_den_slavnost == %d; _je_global_den_sviatok == %d; ant_chval.anchor == %s; ant_chval.file == %s; chval1.anchor == %s; chval1.file == %s; evanjelium.anchor == %s; evanjelium.file == %s\n",
				podmienka, _global_modlitba, _je_global_den_slavnost, _je_global_den_sviatok, _global_modl_posv_citanie.ant_chval.anchor, _global_modl_posv_citanie.ant_chval.file, _global_modl_posv_citanie.chval1.anchor, _global_modl_posv_citanie.chval1.file, _global_modl_posv_citanie.evanjelium.anchor, _global_modl_posv_citanie.evanjelium.file);
			podmienka = podmienka && (je_vigilia);
			Log("podmienka after & je_vigilia == %d\n", podmienka);
			specific_string = HTML_SEQUENCE_PARAGRAPH; // HTML_P_BEGIN
			sprintf(popis_show, "%s %s", html_text_option_skryt[_global_jazyk], html_text_opt_1_vigilia[_global_jazyk]);
			sprintf(popis_hide, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_1_vigilia[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_ALT_CITANIE1_MULTI)) {
			opt = OPT_6_ALTERNATIVES_MULTI;
			bit = BASE_OPT_6_CITANIE1_MULTI;
			multi = ANO;

			mystrcpy(new_anchor, _global_modl_posv_citanie.citanie1.anchor, MAX_STR_AF_ANCHOR);

			podmienka = podmienka && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES));

			multi_count = pocet_multi(new_anchor, bit);
			Log("podmienka == %d pred kontrolou počtu multi_count == %d [anchor '%s']...\n", podmienka, multi_count, new_anchor);

			podmienka = podmienka && (multi_count > 0);

			sprintf(popis_show, "%s", html_text_opt_6_alternatives_multi_citanie[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_ALT_CITANIE2_MULTI)) {
			opt = OPT_6_ALTERNATIVES_MULTI;
			bit = BASE_OPT_6_CITANIE2_MULTI;
			multi = ANO;

			mystrcpy(new_anchor, _global_modl_posv_citanie.citanie2.anchor, MAX_STR_AF_ANCHOR);

			podmienka = podmienka && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES));

			multi_count = pocet_multi(new_anchor, bit);
			Log("podmienka == %d pred kontrolou počtu multi_count == %d [anchor '%s']...\n", podmienka, multi_count, new_anchor);

			podmienka = podmienka && (multi_count > 0);

			sprintf(popis_show, "%s", html_text_opt_6_alternatives_multi_citanie[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_ALT_HYMNUS_MULTI)) {
			opt = OPT_6_ALTERNATIVES_MULTI;
			bit = BASE_OPT_6_HYMNUS_MULTI;
			multi = ANO;

			mystrcpy(new_anchor, _global_modl_hymnus_anchor, MAX_STR_AF_ANCHOR);

			podmienka = podmienka && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES));
			Log(_global_modl_hymnus_anchor);

			multi_count = pocet_multi(new_anchor, bit);
			Log("podmienka == %d pred kontrolou počtu multi_count == %d [anchor '%s']...\n", podmienka, multi_count, new_anchor);

			podmienka = podmienka && (multi_count > 0);

			sprintf(popis_show, "%s", html_text_opt_6_alternatives_multi_hymnus[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_ALT_PSALM_MULTI)) {
			opt = OPT_6_ALTERNATIVES_MULTI;
			bit = BASE_OPT_6_PSALM_MULTI;
			multi = ANO;

			podmienka = podmienka && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES));
			Log(_global_modl_hymnus_anchor);

			multi_count = 4; // psalms 0--3 for invitatory prayer

			podmienka = podmienka && (multi_count > 0);

			sprintf(popis_show, "%s", html_text_opt_6_alternatives_multi_psalm[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_ALT_PROSBY_MULTI) || equals(paramname, PARAM_ALT_UKONKAJ_MULTI)) {
			opt = OPT_6_ALTERNATIVES_MULTI;
			bit = BASE_OPT_6_PROSBY_MULTI;
			multi = ANO;

			mystrcpy(new_anchor, _global_modl_prosby_anchor, MAX_STR_AF_ANCHOR);

			podmienka = podmienka && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES));
			Log(_global_modl_prosby_anchor);

			multi_count = pocet_multi(new_anchor, bit);
			Log("podmienka == %d pred kontrolou počtu multi_count == %d [anchor '%s']...\n", podmienka, multi_count, new_anchor);

			podmienka = podmienka && (multi_count > 0);

			if (equals(paramname, PARAM_ALT_PROSBY_MULTI)) {
				sprintf(popis_show, "%s", html_text_opt_6_alternatives_multi_prosby[_global_jazyk]);
			}
			else {
				sprintf(popis_show, "%s", html_text_opt_6_alternatives_multi_ukonkaj[_global_jazyk]);
			}
		}// PARAM_ALT_PROSBY_MULTI, PARAM_ALT_UKONKAJ_MULTI
		else if (equals(paramname, PARAM_ALT_KCIT_RESP_MULTI)) {
			opt = OPT_6_ALTERNATIVES_MULTI;
			bit = BASE_OPT_6_KCIT_RESP_MULTI;
			multi = ANO;

			mystrcpy(new_anchor, _global_modl_kcit_anchor, MAX_STR_AF_ANCHOR);
			mystrcpy(new_anchor2, _global_modl_kresp_anchor, MAX_STR_AF_ANCHOR);

			podmienka = podmienka && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES));

			multi_count = pocet_multi(new_anchor, bit); // should be the same for new_anchor2
			Log("podmienka == %d pred kontrolou počtu multi_count == %d [anchor '%s']... (malo by byť rovnako aj pre '%s')\n", podmienka, multi_count, new_anchor, new_anchor2);

			podmienka = podmienka && (multi_count > 0);

			sprintf(popis_show, "%s", html_text_opt_6_alternatives_multi_kcit_resp[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_ALT_MARIA_ANT_MULTI)) {
			opt = OPT_6_ALTERNATIVES_MULTI;
			bit = BASE_OPT_6_MARIA_ANT_MULTI;
			multi = ANO;

			mystrcpy(new_anchor, _global_modl_maria_ant_anchor, MAX_STR_AF_ANCHOR);

			podmienka = podmienka && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES));

			multi_count = pocet_multi(new_anchor, bit); // should be the same for new_anchor2
			Log("podmienka == %d pred kontrolou počtu multi_count == %d [anchor '%s']...\n", podmienka, multi_count, new_anchor);

			podmienka = podmienka && (multi_count > 0);

			sprintf(popis_show, "%s", html_text_opt_6_alternatives_multi_maria_ant[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_ALT_KRESP_MULTI)) {
			opt = OPT_6_ALTERNATIVES_MULTI;
			bit = BASE_OPT_6_KRESP_MULTI;
			multi = ANO;

			mystrcpy(new_anchor, _global_modl_kresp_anchor, MAX_STR_AF_ANCHOR);

			podmienka = podmienka && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES));

			multi_count = pocet_multi(new_anchor, bit); // should be the same for new_anchor2
			Log("podmienka == %d pred kontrolou počtu multi_count == %d [anchor '%s']...\n", podmienka, multi_count, new_anchor);

			podmienka = podmienka && (multi_count > 0);

			sprintf(popis_show, "%s", html_text_opt_6_alternatives_multi_kresp[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_ALT_OTCENAS_UVOD_MULTI)) {
			opt = OPT_6_ALTERNATIVES_MULTI;
			bit = BASE_OPT_6_OTCENAS_UVOD_MULTI;
			multi = ANO;

			mystrcpy(new_anchor, _global_modl_otcenas_uvod_anchor, MAX_STR_AF_ANCHOR);

			podmienka = podmienka && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES));
			Log(_global_modl_otcenas_uvod_anchor);

			multi_count = pocet_multi(new_anchor, bit);
			Log("podmienka == %d pred kontrolou počtu multi_count == %d [anchor '%s']...\n", podmienka, multi_count, new_anchor);

			podmienka = podmienka && (multi_count > 0);

			sprintf(popis_show, "%s", html_text_opt_6_alternatives_multi_otcenas_uvod[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_ALT_MODLITBA_MULTI)) {
			opt = OPT_6_ALTERNATIVES_MULTI;
			bit = BASE_OPT_6_MODLITBA_MULTI;
			multi = ANO;

			mystrcpy(new_anchor, _global_modl_modlitba_anchor, MAX_STR_AF_ANCHOR);

			podmienka = podmienka && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES));
			Log(_global_modl_modlitba_anchor);

			multi_count = pocet_multi(new_anchor, bit);
			Log("podmienka == %d pred kontrolou počtu multi_count == %d [anchor '%s']...\n", podmienka, multi_count, new_anchor);

			podmienka = podmienka && (multi_count > 0);

			sprintf(popis_show, "%s", html_text_opt_6_alternatives_multi_modlitba[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_ALT_ANTIFONA_MULTI)) {
			opt = OPT_6_ALTERNATIVES_MULTI;
			bit = BASE_OPT_6_ANTIFONA_MULTI;
			multi = ANO;

			mystrcpy(new_anchor, _global_modl_antifona_anchor, MAX_STR_AF_ANCHOR);

			podmienka = podmienka && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES));

			multi_count = pocet_multi(new_anchor, bit);
			Log("podmienka == %d pred kontrolou počtu multi_count == %d [anchor '%s']...\n", podmienka, multi_count, new_anchor);

			podmienka = podmienka && (multi_count > 0);

			sprintf(popis_show, "%s", html_text_opt_6_alternatives_multi_antifona[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_ALT_HYMNUS_OCR_34)) {
			opt = OPT_5_ALTERNATIVES;
			bit = BIT_OPT_5_OCR_34_HYMNS;

			podmienka = podmienka && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES));

			Log("podmienka == %d pred kontrolou je_34_ocr [_global_modlitba == %d]...\n", podmienka, _global_modlitba);

			podmienka = podmienka && je_34_ocr;

			Log("podmienka == %d pred kontrolou _global_modlitba == %s... [PARAM_ALT_HYMNUS_OCR_34]\n", podmienka, nazov_modlitby(_global_modlitba));

			if (_global_jazyk == JAZYK_CZ) {
				// CZ has special hymn also for prayer during the day
				Log("CZ has special hymn also for prayer during the day...\n");
				podmienka = podmienka && (!(_global_modlitba == MODL_KOMPLETORIUM));
			}
			else {
				Log("except CZ: special hymn only for mpc, mrch, mv...\n");
				podmienka = podmienka && ((_global_modlitba == MODL_POSV_CITANIE) || (_global_modlitba == MODL_RANNE_CHVALY) || (_global_modlitba == MODL_VESPERY));
			}

			Log("podmienka == %d po kontrole _global_modlitba == %s v závislosti od jazyka... [PARAM_ALT_HYMNUS_OCR_34]\n", podmienka, nazov_modlitby(_global_modlitba));

			podmienka = podmienka && !su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(_global_modlitba);

			sprintf(popis_show, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_5_OCR34Hymns_ordinary[_global_jazyk]);
			sprintf(popis_hide, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_5_OCR34Hymns[_global_jazyk]);
		}
		else if (equals(paramname, PARAM_ALT_HYMNUS)) {
			opt = OPT_5_ALTERNATIVES;
			podmienka = podmienka && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES));
			Log("podmienka == %d pred kontrolou je_alternativa_hymnus_ocr/je_alternativa_hymnus_vn [_global_modlitba == %d]...\n", podmienka, _global_modlitba);

			podmienka = podmienka && ((je_alternativa_hymnus_ocr) || ((je_alternativa_hymnus_vn) && (_global_den.litobd == OBD_VELKONOCNE_I)));
			specific_string = HTML_SEQUENCE_PARAGRAPH; // HTML_P_BEGIN

			Log("podmienka == %d pred kontrolou _global_modlitba == %s... [PARAM_ALT_HYMNUS]\n", podmienka, nazov_modlitby(_global_modlitba));

			if (_global_jazyk == JAZYK_CZ) {
				podmienka = (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI));
				bit = BIT_OPT_5_CZ_HYMNY_VYBER;
				sprintf(popis_show, "%s %s", html_text_option_pouzit[_global_jazyk], html_text_opt_5_CZHymnus_ordinary[_global_jazyk]);
				sprintf(popis_hide, "%s %s", html_text_option_pouzit[_global_jazyk], html_text_opt_5_CZHymnus_extra[_global_jazyk]);

				Log("podmienka == %d (_global_jazyk == JAZYK_CZ) pred kontrolou je_34_ocr... [PARAM_ALT_HYMNUS]\n", podmienka);

				if (je_34_ocr && isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_OCR_34_HYMNS) 
					&& (!(_global_modlitba == MODL_KOMPLETORIUM)) // NOT for compline
					&& (!((_je_global_den_slavnost || _je_global_den_sviatok) && ((_global_modlitba == MODL_POSV_CITANIE) || (_global_modlitba == MODL_RANNE_CHVALY) || (_global_modlitba == MODL_VESPERY)))) // NOT for St. Andrew; proper hymn variants for mpc, mrch, mv
					) {
					// do not display this switch for 34. week per annum (when BIT_OPT_5_OCR_34_HYMNS is switched ON; NOT for compline -- still display for compline)
					podmienka = NIE;
				}
			}
			// kontrola na prvé resp. druhé nedeľné kompletórium, aby hymnus bolo v Cezročnom období možné voliť aj pre nedele
			else if ((_global_modlitba == MODL_KOMPLETORIUM) || (_global_modlitba == MODL_PRVE_KOMPLETORIUM) || (_global_modlitba == MODL_DRUHE_KOMPLETORIUM)) {
				bit = BIT_OPT_5_HYMNUS_KOMPL;
				sprintf(popis_show, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_5_KomplHymnusA[_global_jazyk]);
				sprintf(popis_hide, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_5_KomplHymnusB[_global_jazyk]);
			}
			else if (_global_modlitba == MODL_POSV_CITANIE) {
				bit = (je_alternativa_hymnus_ocr) ? BIT_OPT_5_HYMNUS_PC : BIT_OPT_5_HYMNUS_VN_PC;
				sprintf(popis_show, "%s %s", html_text_option_zobrazit[_global_jazyk], (je_alternativa_hymnus_ocr) ? html_text_opt_5_PCHymnusI[_global_jazyk] : html_text_opt_5_PCHymnusVNferia[_global_jazyk]);
				sprintf(popis_hide, "%s %s", html_text_option_zobrazit[_global_jazyk], (je_alternativa_hymnus_ocr) ? html_text_opt_5_PCHymnusII[_global_jazyk] : html_text_opt_5_PCHymnusVNnedela[_global_jazyk]);

				if (je_34_ocr && isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_OCR_34_HYMNS)) {
					// do not display this switch for 34. week per annum (when BIT_OPT_5_OCR_34_HYMNS is switched ON)
					podmienka = NIE;
				}
			}
			else if (_global_modlitba == MODL_PREDPOLUDNIM) {
				bit = BIT_OPT_5_HYMNUS_MCD_PREDPOL;
				sprintf(popis_show, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_5_MCDPredHymnus1[_global_jazyk]);
				sprintf(popis_hide, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_5_MCDPredHymnus2[_global_jazyk]);
			}
			else if (_global_modlitba == MODL_NAPOLUDNIE) {
				bit = BIT_OPT_5_HYMNUS_MCD_NAPOL;
				sprintf(popis_show, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_5_MCDNaHymnus1[_global_jazyk]);
				sprintf(popis_hide, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_5_MCDNaHymnus2[_global_jazyk]);
			}
			else if (_global_modlitba == MODL_POPOLUDNI) {
				bit = BIT_OPT_5_HYMNUS_MCD_POPOL;
				sprintf(popis_show, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_5_MCDPoHymnus1[_global_jazyk]);
				sprintf(popis_hide, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_5_MCDPoHymnus2[_global_jazyk]);
			}
			else if (_global_modlitba == MODL_RANNE_CHVALY) {
				bit = BIT_OPT_5_HYMNUS_VN_RCH;
				sprintf(popis_show, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_5_RChHymnusVNferia[_global_jazyk]);
				sprintf(popis_hide, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_5_RChHymnusVNnedela[_global_jazyk]);
			}
			else if ((_global_modlitba == MODL_PRVE_VESPERY) || (_global_modlitba == MODL_VESPERY)) {
				if ((je_alternativa_hymnus_vn) && (_global_den.litobd == OBD_VELKONOCNE_I)) {
					bit = BIT_OPT_5_HYMNUS_VN_VESP;
					sprintf(popis_show, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_5_VespHymnusVNferia[_global_jazyk]);
					sprintf(popis_hide, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_5_VespHymnusVNnedela[_global_jazyk]);
				}
				else if (je_alternativa_hymnus_ocr) {
					bit = BIT_OPT_5_HYMNUS_1VESP;
					sprintf(popis_show, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_5_1VHymnusNe[_global_jazyk]);
					sprintf(popis_hide, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_opt_5_1VHymnusPC[_global_jazyk]);
				}
			}
			else {
				podmienka = NIE;
			}

			Log("podmienka == %d po kontrole _global_modlitba == %s; bit == %llu...\n", podmienka, nazov_modlitby(_global_modlitba), bit);
		}
		else if (equals(paramname, PARAM_PSALMODIA)) {

			opt = OPT_5_ALTERNATIVES;
			podmienka = podmienka && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES));

			if (_global_modlitba == MODL_RANNE_CHVALY) {
				bit = BIT_OPT_5_POPOL_STREDA_PSALMODIA;

				podmienka = podmienka && (_global_den.denvr == POPOLCOVA_STREDA);

				sprintf(popis_show, "%s", html_text_opt_5_PopolStrPsalm_4STR[_global_jazyk]);
				sprintf(popis_hide, "%s", html_text_opt_5_PopolStrPsalm_3PI[_global_jazyk]);
			}
			else if (_global_modlitba == MODL_POSV_CITANIE) {
				bit = BIT_OPT_5_ZELENY_STVRTOK_PSALMODIA;

				podmienka = podmienka && (_global_den.denvr == ZELENY_STVRTOK);

				sprintf(popis_show, "%s", html_text_opt_5_ZelStvPsalm_2STV[_global_jazyk]);
				sprintf(popis_hide, "%s", html_text_opt_5_ZelStvPsalm_3PI[_global_jazyk]);
			}
			else {
				podmienka = NIE;
			}
		}

		// má zmysel, len ak platí daná podmienka
		if (podmienka) {
			Log("interpretParameter: including %s\n", paramname);
			Export("%s:begin-->", paramname);

			mystrcpy(before, STR_EMPTY, SMALL);
			mystrcpy(after, STR_EMPTY, SMALL);

			if (specific_string == HTML_SEQUENCE_PARAGRAPH) {
				sprintf(before, HTML_P_BEGIN);
				sprintf(after, HTML_P_END);
			}
			else if (specific_string == HTML_SEQUENCE_LINE_BREAK) {
				sprintf(before, HTML_LINE_BREAK);
			}
			else if (specific_string == HTML_SEQUENCE_DIV) {
				sprintf(before, HTML_DIV_BEGIN);
				sprintf(after, HTML_DIV_END);
			}

			if (multi == NIE) {
				_export_link_show_hide(opt, bit, popis_show, popis_hide, (char *)HTML_SPAN_RED_SMALL, (char *)HTML_CLASS_QUIET, before, after, anchor, (char *)HTML_SPAN_END);
			}
			else {
				current_value = isGlobalOption(opt, bit);

				if (current_value >= multi_count) {
					current_value = 0;
					setGlobalOption(opt, bit, current_value);
				}

				// use popis_hide as temp variable
				sprintf(popis_hide, "_%d", current_value);

				strcat(new_anchor, popis_hide);
				strcat(new_anchor2, popis_hide); // only used if (bit == BASE_OPT_6_KCIT_RESP_MULTI)

				if (bit == BASE_OPT_6_HYMNUS_MULTI) {
					_set_hymnus(modlitba, NULL, new_anchor);
				}
				else if (bit == BASE_OPT_6_CITANIE2_MULTI) {
					_set_citanie2(modlitba, NULL, new_anchor);
				}
				else if (bit == BASE_OPT_6_CITANIE1_MULTI) {
					_set_citanie1(modlitba, NULL, new_anchor);
				}
				else if (bit == BASE_OPT_6_ANTIFONA_MULTI) {
					if (_global_modlitba == MODL_RANNE_CHVALY) {
						_set_benediktus(modlitba, NULL, new_anchor);
					}
					else if (_global_modlitba == MODL_INVITATORIUM) {
						_set_antifona1(modlitba, NULL, new_anchor);
					}
					else {
						// vešepry, prvé vešpery
						_set_magnifikat(modlitba, NULL, new_anchor);
					}
				}
				else if (bit == BASE_OPT_6_MARIA_ANT_MULTI) {
					_set_maria_ant(modlitba, NULL, new_anchor);
				}
				else if (bit == BASE_OPT_6_MODLITBA_MULTI) {
					_set_modlitba(modlitba, NULL, new_anchor);
				}
				else if (bit == BASE_OPT_6_PROSBY_MULTI) {
					_set_prosby(modlitba, NULL, new_anchor);
				}
				else if (bit == BASE_OPT_6_KCIT_RESP_MULTI) {
					_set_kcitanie(modlitba, NULL, new_anchor);
					_set_kresponz(modlitba, NULL, new_anchor2);
				}
				else if (bit == BASE_OPT_6_KRESP_MULTI) {
					_set_kresponz(modlitba, NULL, new_anchor);
				}
				else if (bit == BASE_OPT_6_OTCENAS_UVOD_MULTI) {
					_set_otcenas_uvod(modlitba, NULL, new_anchor);
				}
				// no atcion for BASE_OPT_6_PSALM_MULTI

				// use popis_hide as temp variable
				sprintf(popis_hide, " (%d/%d) %s", ((current_value + 1) MOD multi_count) + 1, multi_count, (char *)HTML_RIGHT_ARROW);
				strcat(popis_show, popis_hide);

				_export_link_multi(opt, bit, multi_count, popis_show, (char *)HTML_SPAN_RED_SMALL, (char *)HTML_CLASS_QUIET, before, after, anchor, (char *)HTML_SPAN_END);
			}

			ExportHtmlOnlyFormat("<!--%s:end", paramname);
		}
		else {
			ExportHtmlOnlyFormat("[skipping %s]", paramname);
			Log("skipping %s\n", paramname);
		}
	} // PARAM_CHVALOSPEV, PARAM_ZAVER, PARAM_OTCENAS, PARAM_TEDEUM, PARAM_DOPLNKOVA_PSALMODIA, PARAM_PSALMODIA, PARAM_POPIS, PARAM_SLAVAOTCU, PARAM_RESPONZ, PARAM_NADPIS, PARAM_KRATSIE_PROSBY, PARAM_VIGILIA, PARAM_ALT_HYMNUS, PARAM_SPOL_CAST_SPOM

	else if (equals(paramname, PARAM_TTS_SECTION)) {
		// export for voice output, never show; CSS defines display: none;
		if (EXPORT_TTS_SECTIONS) {
			ExportHtmlOnly("tts:section:begin-->\n");

			if (EXPORT_TTS_PAUSES) {
				Export("<" HTML_SPAN_TTS_PAUSE ">");

				Export(HTML_SPAN_END "\n");
			}

			Export("<" HTML_DIV_TTS_SECTION ">");

			Export(HTML_DIV_END "\n");

			ExportHtmlOnly("<!--tts:section:end");
		}
		else {
			ExportHtmlOnly("[skipping TTS_SECTION]");
			Log("skipping TTS_SECTION\n");
		}
	} // PARAM_TTS_SECTION

	else if (equals(paramname, PARAM_NAVIGACIA_SIMPLE)) {
		if ((aj_navigacia == ANO) && (!(_global_skip_in_prayer >= ANO))) {
#ifdef BEHAVIOUR_WEB
			if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_NAVIGATION)) {
				ExportHtmlOnly("navigácia:begin-->\n");

				Export(HTML_P_CENTER_SMALL);
				_export_rozbor_dna_navig_top_bottom_simple((char *)HTML_TOP, html_text_top[_global_jazyk], HTML_UP_ARROW_CLASSIC);

				Export(STR_VERTICAL_BAR_WITH_SPACES);

				_export_rozbor_dna_navig_top_bottom_simple((char *)HTML_BOTTOM, html_text_bottom[_global_jazyk], HTML_DOWN_ARROW_CLASSIC);
				Export(HTML_P_END "\n");

				ExportHtmlOnly("<!--navigácia:end");
			}
			else {
				ExportHtmlOnly("[skipping NAVIGACIA]");
				Log("skipping NAVIGACIA\n");
			}
#endif
		}
	} // PARAM_NAVIGACIA_SIMPLE

	else if (equals(paramname, PARAM_NAVIGACIA)) {
		if (aj_navigacia == ANO) {
#ifdef BEHAVIOUR_WEB
			// možnosť zobrazenia navigácie v texte modlitieb 
			_global_pocet_navigacia++;
			if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_NAVIGATION)) {
				ExportHtmlOnly("navigácia:begin-->\n");
				ExportHtmlComment("navigácia %d", _global_pocet_navigacia);
				if ((_global_pocet_navigacia <= 1) && (_global_pocet_volani_interpretTemplate < 2)) {

					_export_rozbor_dna_navig_top_bottom((char *)HTML_BOTTOM, html_text_bottom[_global_jazyk], HTML_DOWN_ARROW_CLASSIC);

					_export_rozbor_dna_buttons_dni(EXPORT_DNA_JEDEN_DEN, NIE, aj_navigacia);

					// najprv dni, potom modlitby

					Export("<" HTML_TABLE ">\n");
					Export("<" HTML_TABLE_ROW ">\n");
					ExportTableCell(HTML_TABLE_CELL);

					_export_rozbor_dna_buttons(EXPORT_DNA_JEDEN_DEN, _global_poradie_svaty, NIE);

					Export(HTML_TABLE_CELL_END "\n");
					Export(HTML_TABLE_ROW_END "\n");
					Export(HTML_TABLE_END "\n");

				}// if ((_global_pocet_navigacia <= 1) && (_global_pocet_volani_interpretTemplate < 2))
				else {

					_export_rozbor_dna_navig_top_bottom((char *)HTML_TOP, html_text_top[_global_jazyk], HTML_UP_ARROW_CLASSIC);

					Export("<" HTML_TABLE ">\n");
					Export("<" HTML_TABLE_ROW ">\n");
					ExportTableCell(HTML_TABLE_CELL);

					_export_rozbor_dna_buttons(EXPORT_DNA_JEDEN_DEN, _global_poradie_svaty, NIE);

					Export(HTML_TABLE_CELL_END "\n");
					Export(HTML_TABLE_ROW_END "\n");
					Export(HTML_TABLE_END "\n");

					// najprv modlitby, potom dni

					_export_rozbor_dna_buttons_dni(EXPORT_DNA_JEDEN_DEN, NIE, aj_navigacia);

				}// _global_pocet_navigacia > 1 || (_global_pocet_volani_interpretTemplate >= 2)
				ExportHtmlOnly("<!--navigácia:end");
			}
			else {
				ExportHtmlOnly("[skipping NAVIGACIA]");
				Log("skipping NAVIGACIA\n");
			}
#endif
		} // if (aj_navigacia == ANO)
		else if (aj_navigacia == CIASTOCNE) {
			ExportHtmlOnly("navigácia:begin-->\n");
			_export_rozbor_dna_buttons_dni(EXPORT_DNA_JEDEN_DEN, NIE, aj_navigacia);
			ExportHtmlOnly("<!--navigácia:end");
		} // if (aj_navigacia == CIASTOCNE)
	} // PARAM_NAVIGACIA

	// pokracuju dalsie klasicke `tagy' v modlitbach (teda templatoch)

	/* must not be "else" before this if due to repeatance of PARAM_POPIS */
	if (equals(paramname, PARAM_POPIS)) {
		Log("  _global_opt[OPT_1_CASTI_MODLITBY] & BIT_OPT_1_SKRY_POPIS == %ld: ", _global_opt[OPT_1_CASTI_MODLITBY] & BIT_OPT_1_SKRY_POPIS);
		Log("  _global_opt[OPT_0_SPECIALNE] & BIT_OPT_0_VOICE_OUTPUT == %ld: ", _global_opt[OPT_0_SPECIALNE] & BIT_OPT_0_VOICE_OUTPUT);

		if (!(useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_SKRY_POPIS)) && (je_popis)) {
			Log("interpretParameter: PARAM_POPIS: including POPIS...\n");
			switch (modlitba) {
			case MODL_INVITATORIUM:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_invitatorium.popis);
				break;
			case MODL_RANNE_CHVALY:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_ranne_chvaly.popis);
				break;
			case MODL_VESPERY:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_vespery.popis);
				break;
			case MODL_POSV_CITANIE:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_posv_citanie.popis);
				break;
				// pre modlitbu cez deň zobrazovať popis len pre sviatky a slávnosti -- vyriešené v set_popis_svaty_rch_mcd_pc_vesp()
			case MODL_CEZ_DEN_9:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_9.popis);
				break;
			case MODL_CEZ_DEN_12:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_12.popis);
				break;
			case MODL_CEZ_DEN_3:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_3.popis);
				break;
			case MODL_KOMPLETORIUM:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_kompletorium.popis);
				break;
			case MODL_PRVE_VESPERY:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_vespery.popis);
				break;
			case MODL_PRVE_KOMPLETORIUM:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_kompletorium.popis);
				break;
			default:
				// tieto modlitby nemajú popis
				break;
			} // switch
		}
		else {
			if (typ != PRM_XML) {
				Export("[skipping POPIS]");
			}
			Log("skipping POPIS...\n");
		}
	} // PARAM_POPIS

	else if ((equals(paramname, PARAM_INVITAT_PSALM_24))
		|| (equals(paramname, PARAM_INVITAT_PSALM_67))
		|| (equals(paramname, PARAM_INVITAT_PSALM_95))
		|| (equals(paramname, PARAM_INVITAT_PSALM_100))) {

		mystrcpy(before, STR_EMPTY, SMALL);
		mystrcpy(after, STR_EMPTY, SMALL);
		mystrcpy(anchor, STR_EMPTY, SMALL);

		current_value = 0;
		short int psalm = 0;

		if (equals(paramname, PARAM_INVITAT_PSALM_24)) {
			// psalm 24 is 4th alternative (4/4); zero-based # 3
			psalm = 24;
			current_value = 3;
		}
		else if (equals(paramname, PARAM_INVITAT_PSALM_67)) {
			// psalm 67 is 3rd alternative (3/4); zero-based # 2
			psalm = 67;
			current_value = 2;
		}
		else if (equals(paramname, PARAM_INVITAT_PSALM_95)) {
			// psalm 95 is 1st alternative (1/4); zero-based # 0
			psalm = 95;
			current_value = 0;
		}
		else if (equals(paramname, PARAM_INVITAT_PSALM_100)) {
			// psalm 100 is 2nd alternative (2/4); zero-based # 1
			psalm = 100;
			current_value = 1;
		}

		// we use these variables here even though their names are a little bit confusing :)
		sprintf(popis_hide, "z%d", psalm);

		sprintf(anchor, HTML_A_HREF_BEGIN "\"#%s\">%s" HTML_A_END, popis_hide, html_text_invitatory_psalm(current_value));

		if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES) && isGlobalOption(OPT_6_ALTERNATIVES_MULTI, BASE_OPT_6_PSALM_MULTI) != (unsigned)current_value) {
			_export_link_multi(OPT_6_ALTERNATIVES_MULTI, BASE_OPT_6_PSALM_MULTI, 4, (char *)html_text_invitatory_psalm(current_value), (char *)HTML_SPAN_NORMAL, (char *)HTML_CLASS_QUIET, before, after, popis_hide, (char *)HTML_SPAN_END, CHAR_EMPTY, CHAR_EMPTY, current_value);
		}
		else {
			Export(anchor);
		}
	} // PARAM_INVITAT_PSALM_...

	else if (equals(paramname, PARAM_HYMNUS)) {
		switch (modlitba) {
		case MODL_RANNE_CHVALY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_ranne_chvaly.hymnus);
			break;
		case MODL_CEZ_DEN_9:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_9.hymnus);
			break;
		case MODL_CEZ_DEN_12:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_12.hymnus);
			break;
		case MODL_CEZ_DEN_3:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_3.hymnus);
			break;
		case MODL_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_vespery.hymnus);
			break;
		case MODL_POSV_CITANIE:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_posv_citanie.hymnus);
			break;
		case MODL_KOMPLETORIUM:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_kompletorium.hymnus);
			break;
		case MODL_PRVE_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_vespery.hymnus);
			break;
		case MODL_PRVE_KOMPLETORIUM:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_kompletorium.hymnus);
			break;
		default:
			// tieto modlitby nemajú hymnus
			break;
		} // switch
	} // PARAM_HYMNUS
	else if (equals(paramname, PARAM_ANTIFONA1)) {
		antifona_pocet++;
		switch (modlitba) {
		case MODL_INVITATORIUM:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_invitatorium.antifona1);
			break;
		case MODL_RANNE_CHVALY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_ranne_chvaly.antifona1);
			break;
		case MODL_CEZ_DEN_9:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_9.antifona1);
			break;
		case MODL_CEZ_DEN_12:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_12.antifona1);
			break;
		case MODL_CEZ_DEN_3:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_3.antifona1);
			break;
		case MODL_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_vespery.antifona1);
			break;
		case MODL_KOMPLETORIUM:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_kompletorium.antifona1);
			break;
		case MODL_POSV_CITANIE:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_posv_citanie.antifona1);
			break;
		case MODL_PRVE_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_vespery.antifona1);
			break;
		case MODL_PRVE_KOMPLETORIUM:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_kompletorium.antifona1);
			break;
		default:
			// tieto modlitby nemaju antifonu1
			break;
		} // switch
	} // PARAM_ANTIFONA1
	else if (equals(paramname, PARAM_ANTIFONA1x)) {
		antifona_pocet++;
		switch (modlitba) {
		case MODL_CEZ_DEN_9:
			if (_global_ant_mcd_rovnake == NIE) {
				ExportFileAnchor(typ, modlitba, (char*)PARAM_ANTIFONA1, _global_modl_cez_den_9.antifona1);
			}
			break;
		case MODL_CEZ_DEN_12:
			if (_global_ant_mcd_rovnake == NIE) {
				ExportFileAnchor(typ, modlitba, (char*)PARAM_ANTIFONA1, _global_modl_cez_den_12.antifona1);
			}
			break;
		case MODL_CEZ_DEN_3:
			if (_global_ant_mcd_rovnake == NIE) {
				ExportFileAnchor(typ, modlitba, (char*)PARAM_ANTIFONA1, _global_modl_cez_den_3.antifona1);
			}
			break;
		case MODL_KOMPLETORIUM:
			if (_global_ant_mcd_rovnake == NIE) {
				// no need to force the condition by: (_global_modl_kompletorium.pocet_zalmov == 2)
				ExportFileAnchor(typ, modlitba, (char*)PARAM_ANTIFONA1, _global_modl_kompletorium.antifona1);
			}
			break;
		case MODL_PRVE_KOMPLETORIUM:
			if (_global_ant_mcd_rovnake == NIE) {
				// no need to force the condition by: (_global_modl_kompletorium.pocet_zalmov == 2)
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_kompletorium.antifona1);
			}
			break;
		default:
			// tieto modlitby nemajú antifonu1x (má to len mcd)
			break;
		} // switch
	} // PARAM_ANTIFONA1x
	else if (equals(paramname, PARAM_ANTIFONA2)) {
		antifona_pocet++;
		switch (modlitba) {
			// ranné chvály nie
		case MODL_CEZ_DEN_9:
			if (_global_ant_mcd_rovnake == NIE) {
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_9.antifona2);
			}
			break;
		case MODL_CEZ_DEN_12:
			if (_global_ant_mcd_rovnake == NIE) {
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_12.antifona2);
			}
			break;
		case MODL_CEZ_DEN_3:
			if (_global_ant_mcd_rovnake == NIE) {
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_3.antifona2);
			}
			break;
		case MODL_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_vespery.antifona2);
			break;
		case MODL_POSV_CITANIE:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_posv_citanie.antifona2);
			break;
		case MODL_KOMPLETORIUM:
			// 2008-04-03: pridaná podmienka, aby sa preskakovalo v modlitbe kompletória pre veľkonočné obdobie - vnorená kotva
			Log("interpretParameter(): _global_modl_kompletorium.pocet_zalmov == %d...\n", _global_modl_kompletorium.pocet_zalmov);
			Log("_global_modl_kompletorium.alternativy == %d...\n", _global_modl_kompletorium.alternativy);
			if ((_global_modl_kompletorium.pocet_zalmov == 2) && (_global_skip_in_prayer == NIE)) {
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_kompletorium.antifona2);
			}
			break;
		case MODL_PRVE_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_vespery.antifona2);
			break;
		case MODL_PRVE_KOMPLETORIUM:
			// podmienka, aby sa preskakovalo v modlitbe kompletória pre veľkonočné obdobie - vnorená kotva
			Log("interpretParameter(): _global_modl_prve_kompletorium.pocet_zalmov == %d...\n", _global_modl_prve_kompletorium.pocet_zalmov);
			Log("_global_modl_prve_kompletorium.alternativy == %d...\n", _global_modl_prve_kompletorium.alternativy);
			if ((_global_modl_prve_kompletorium.pocet_zalmov == 2) && (_global_skip_in_prayer == NIE)) {
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_kompletorium.antifona2);
			}
			break;
			// zneužitie parametra "ANTIFONA2" pre zobrazenie "záverečnej" antifóny v prípade, že sa tlačí aj Sláva Otcu 
			// funguje tak, že ak chce zobraziť Sláva Otcu (if (_global_opt 1 == ANO)), nastaví sa interpretovanie podľa ANTIFONA1; ináč sa nič nevykoná
		case MODL_INVITATORIUM:
			if (useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_SLAVA_OTCU)) {
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_invitatorium.antifona1);
			}
			else {
				// only print when exporting
				if (!(_global_skip_in_prayer >= ANO)) {
					Export(HTML_COMMENT_END);
					Export(HTML_P_RUBRIC);
					Export((char *)html_text_inv_slavaotcu[_global_jazyk]);
					Export(HTML_P_END);
					Export(HTML_COMMENT_BEGIN);
				}
			}
			break;
		default:
			// tieto modlitby nemajú antifonu2
			break;
		} // switch
	} // PARAM_ANTIFONA2
	else if (equals(paramname, PARAM_ANTIFONA3)) {
		antifona_pocet++;
		switch (modlitba) {
		case MODL_RANNE_CHVALY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_ranne_chvaly.antifona3);
			break;
		case MODL_CEZ_DEN_9:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_9.antifona3);
			break;
		case MODL_CEZ_DEN_12:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_12.antifona3);
			break;
		case MODL_CEZ_DEN_3:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_3.antifona3);
			break;
			/*
		case MODL_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_vespery.antifona3);
			break;
			*/
		case MODL_POSV_CITANIE:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_posv_citanie.antifona3);
			break;
		default:
			// tieto modlitby nemajú antifonu3
			break;
		} // switch
	} // PARAM_ANTIFONA3
	else if (equals(paramname, PARAM_ANTIFONA3x)) {
		antifona_pocet++;
		switch (modlitba) {
		case MODL_CEZ_DEN_9:
			if (_global_ant_mcd_rovnake == NIE) {
				ExportFileAnchor(typ, modlitba, (char*)PARAM_ANTIFONA3, _global_modl_cez_den_9.antifona3);
			}
			break;
		case MODL_CEZ_DEN_12:
			if (_global_ant_mcd_rovnake == NIE) {
				ExportFileAnchor(typ, modlitba, (char*)PARAM_ANTIFONA3, _global_modl_cez_den_12.antifona3);
			}
			break;
		case MODL_CEZ_DEN_3:
			if (_global_ant_mcd_rovnake == NIE) {
				ExportFileAnchor(typ, modlitba, (char*)PARAM_ANTIFONA3, _global_modl_cez_den_3.antifona3);
			}
			break;
		default:
			// tieto modlitby nemajú antifonu3x (má to len mcd)
			break;
		} // switch
	} // PARAM_ANTIFONA3x
	else if (equals(paramname, PARAM_ANTIFONA1k)) {
		// pridané kvôli kompletóriu vo veľkonočnom období, či pri druhej antifóne zobraziť dvojku alebo nie 
		if ((((modlitba == MODL_KOMPLETORIUM) && (_global_modl_kompletorium.pocet_zalmov == 2)) || ((modlitba == MODL_PRVE_KOMPLETORIUM) && (_global_modl_prve_kompletorium.pocet_zalmov == 2))) && (_global_ant_mcd_rovnake == NIE)) {
			Export(HTML_COMMENT_END);
			if ((_global_jazyk == JAZYK_HU) || (_global_jazyk == JAZYK_CZ)) {
				Export("1. ant.");
			}
			else {
				Export("1");
			}
			Export(HTML_COMMENT_BEGIN);
		}
		else {
			if ((_global_jazyk == JAZYK_HU) || (_global_jazyk == JAZYK_CZ)) {
				Export(HTML_COMMENT_END);
				Export("Ant.");
				Export(HTML_COMMENT_BEGIN);
			}
			else {
#if defined(EXPORT_HTML_SPECIALS)
				Export("nie je 1. antifona v kompletku");
#endif
			}
			Log("nie je 1. antifona v kompletku");
		}
	} // ANTIFONA1_KOMPLET
	else if (equals(paramname, PARAM_ANTIFONA2k)) {
		// pridané kvôli kompletóriu vo veľkonočnom období, či pri druhej antifóne zobraziť dvojku alebo nie 
		if ((((modlitba == MODL_KOMPLETORIUM) && (_global_modl_kompletorium.pocet_zalmov == 2)) || ((modlitba == MODL_PRVE_KOMPLETORIUM) && (_global_modl_prve_kompletorium.pocet_zalmov == 2))) && (_global_ant_mcd_rovnake == NIE)) {
			Export("-->2<!--");
		}
		else {
#if defined(EXPORT_HTML_SPECIALS)
			Export("nie je 2. antifona v kompletku");
#endif
			Log("nie je 2. antifona v kompletku");
		}
	} // ANTIFONA2_KOMPLET
	else if (equals(paramname, PARAM_ZALM1)) {
		switch (modlitba) {
		case MODL_INVITATORIUM:
			// hoci nie je zapoznámkované, nepoužíva sa: invitatórium nemá žalm / resp. má fixný žalm 95 a alternatívy
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_invitatorium.zalm1);
			break;
		case MODL_RANNE_CHVALY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_ranne_chvaly.zalm1);
			break;
		case MODL_CEZ_DEN_9:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_9.zalm1);
			break;
		case MODL_CEZ_DEN_12:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_12.zalm1);
			break;
		case MODL_CEZ_DEN_3:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_3.zalm1);
			break;
		case MODL_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_vespery.zalm1);
			break;
		case MODL_KOMPLETORIUM:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_kompletorium.zalm1);
			break;
		case MODL_POSV_CITANIE:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_posv_citanie.zalm1);
			break;
		case MODL_PRVE_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_vespery.zalm1);
			break;
		case MODL_PRVE_KOMPLETORIUM:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_kompletorium.zalm1);
			break;
		default:
			// tieto modlitby nemajú zalm1
			break;
		} // switch
	} // PARAM_ZALM1
	else if (equals(paramname, PARAM_ZALM2)) {
		switch (modlitba) {
			// ranné chvály nie
		case MODL_CEZ_DEN_9:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_9.zalm2);
			break;
		case MODL_CEZ_DEN_12:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_12.zalm2);
			break;
		case MODL_CEZ_DEN_3:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_3.zalm2);
			break;
		case MODL_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_vespery.zalm2);
			break;
		case MODL_POSV_CITANIE:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_posv_citanie.zalm2);
			break;
		case MODL_KOMPLETORIUM:
			if (_global_modl_kompletorium.pocet_zalmov == 2) {
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_kompletorium.zalm2);
			}
			break;
		case MODL_PRVE_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_vespery.zalm2);
			break;
		case MODL_PRVE_KOMPLETORIUM:
			if (_global_modl_prve_kompletorium.pocet_zalmov == 2) {
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_kompletorium.zalm2);
			}
			break;
		default:
			// tieto modlitby nemajú zalm2
			break;
		} // switch
	} // PARAM_ZALM2
	else if (equals(paramname, PARAM_ZALM3)) {
		switch (modlitba) {
		case MODL_RANNE_CHVALY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_ranne_chvaly.zalm3);
			break;
		case MODL_CEZ_DEN_9:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_9.zalm3);
			break;
		case MODL_CEZ_DEN_12:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_12.zalm3);
			break;
		case MODL_CEZ_DEN_3:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_3.zalm3);
			break;
			// vešpery nie
		case MODL_POSV_CITANIE:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_posv_citanie.zalm3);
			break;
		default:
			// tieto modlitby nemajú zalm3
			break;
		} // switch
	} // PARAM_ZALM3
	else if (equals(paramname, PARAM_KCITANIE)) {
		switch (modlitba) {
		case MODL_RANNE_CHVALY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_ranne_chvaly.kcitanie);
			break;
		case MODL_CEZ_DEN_9:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_9.kcitanie);
			break;
		case MODL_CEZ_DEN_12:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_12.kcitanie);
			break;
		case MODL_CEZ_DEN_3:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_3.kcitanie);
			break;
		case MODL_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_vespery.kcitanie);
			break;
		case MODL_KOMPLETORIUM:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_kompletorium.kcitanie);
			break;
		case MODL_PRVE_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_vespery.kcitanie);
			break;
		case MODL_PRVE_KOMPLETORIUM:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_kompletorium.kcitanie);
			break;
		default:
			// tieto modlitby nemajú kcitanie
			break;
		} // switch
	} // PARAM_KCITANIE
	else if (equals(paramname, PARAM_KRESPONZ)) {
		switch (modlitba) {
		case MODL_RANNE_CHVALY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_ranne_chvaly.kresponz);
			break;
		case MODL_CEZ_DEN_9:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_9.kresponz);
			break;
		case MODL_CEZ_DEN_12:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_12.kresponz);
			break;
		case MODL_CEZ_DEN_3:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_3.kresponz);
			break;
		case MODL_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_vespery.kresponz);
			break;
		case MODL_KOMPLETORIUM:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_kompletorium.kresponz);
			break;
		case MODL_POSV_CITANIE:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_posv_citanie.kresponz);
			break;
		case MODL_PRVE_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_vespery.kresponz);
			break;
		case MODL_PRVE_KOMPLETORIUM:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_kompletorium.kresponz);
			break;
		default:
			// tieto modlitby nemajú kresponz
			break;
		} // switch
	} // PARAM_KRESPONZ
	else if (equals(paramname, PARAM_CITANIE1)) {
		if (modlitba == MODL_POSV_CITANIE) {
			Log("interpretParameter(): equals(paramname, PARAM_CITANIE1). idem spustiť includeFile()...\n");
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_posv_citanie.citanie1);
			Log("interpretParameter(): equals(paramname, PARAM_CITANIE1), po spustení includeFile().\n");
		}
		else {
			; // ostatné modlitby 1. čítanie nemajú
		}
	} // PARAM_CITANIE1
	else if (equals(paramname, PARAM_CITANIE2)) {
		if (modlitba == MODL_POSV_CITANIE) {
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_posv_citanie.citanie2);
		}
		else {
			; // ostatné modlitby 2. čítanie nemajú
		}
	} // PARAM_CITANIE2
	else if (equals(paramname, PARAM_MAGNIFIKAT)) {
		// ak _global_skip_in_prayer je >= ANO, tak preskoc Magnifikat
		if (((modlitba == MODL_VESPERY) || (modlitba == MODL_PRVE_VESPERY)) && (_global_skip_in_prayer == NIE)) {
			if (modlitba == MODL_VESPERY) {
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_vespery.magnifikat);
			}
			else {
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_vespery.magnifikat);
			}
		}
		else {
			; // ostatné modlitby nemajú večerný chválospev
		}
	} // PARAM_MAGNIFIKAT
	else if (equals(paramname, PARAM_ANTVCHVAL)) {
		antifona_pocet++;
		if (modlitba == MODL_VESPERY) {
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_vespery.antifona3);
		}
		else if (modlitba == MODL_PRVE_VESPERY) {
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_vespery.antifona3);
		}
		else {
			; // ostatné modlitby nemajú večerný chválospev
		}
	} // PARAM_ANTVCHVAL
	else if (equals(paramname, PARAM_VCHVALOSPEV)) {
		if (modlitba == MODL_VESPERY) {
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_vespery.zalm3);
		}
		else if (modlitba == MODL_PRVE_VESPERY) {
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_vespery.zalm3);
		}
		else {
			; // ostatné modlitby nemajú večerný chválospev
		}
	} // PARAM_VCHVALOSPEV
	else if (equals(paramname, PARAM_BENEDIKTUS)) {
		// ak _global_skip_in_prayer je >= ANO, tak preskoc Benediktus
		if ((modlitba == MODL_RANNE_CHVALY) && (_global_skip_in_prayer == NIE)) {
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_ranne_chvaly.benediktus);
		}
		else {
			; // ostatné modlitby nemajú ranný chválospev
		}
	} // PARAM_BENEDIKTUS
	else if (equals(paramname, PARAM_ANTRCHVAL)) {
		antifona_pocet++;
		if (modlitba == MODL_RANNE_CHVALY) {
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_ranne_chvaly.antifona2);
		}
		else {
			; // ostatné modlitby nemajú ranný chválospev
		}
	} // PARAM_ANTRCHVAL
	else if (equals(paramname, PARAM_RCHVALOSPEV)) {
		if (modlitba == MODL_RANNE_CHVALY) {
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_ranne_chvaly.zalm2);
		}
		else {
			; // ostatné modlitby nemajú ranný chválospev
		}
	} // PARAM_RCHVALOSPEV
	else if (equals(paramname, PARAM_NUNC_DIMITTIS)) {
		if ((je_kompletorium12(modlitba)) && (_global_skip_in_prayer == NIE)) {
			if (modlitba == MODL_KOMPLETORIUM) {
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_kompletorium.nunc_dimittis);
			}
			else {
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_kompletorium.nunc_dimittis);
			}
		}
		else {
			; // ostatné modlitby nemajú Nunc dimittis
		}
	} // PARAM_NUNC_DIMITTIS
	else if (equals(paramname, PARAM_UKON_KAJ)) {
		if ((je_kompletorium12(modlitba)) && (_global_skip_in_prayer == NIE)) {
			if (modlitba == MODL_KOMPLETORIUM) {
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_kompletorium.ukonkaj);
			}
			else {
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_kompletorium.ukonkaj);
			}
		}
		else {
			; // ostatné modlitby nemajú úkon kajúcnosti
		}
	} // PARAM_UKON_KAJ
	else if (equals(paramname, PARAM_MARIA_ANT)) {
		if ((je_kompletorium12(modlitba)) && (_global_skip_in_prayer == NIE)) {
			if (modlitba == MODL_KOMPLETORIUM) {
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_kompletorium.maria_ant);
			}
			else {
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_kompletorium.maria_ant);
			}
		}
		else {
			; // ostatné modlitby nemajú mariánske antifóny
		}
	} // PARAM_MARIA_ANT
	else if (equals(paramname, PARAM_PROSBY)) {
		switch (modlitba) {
		case MODL_RANNE_CHVALY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_ranne_chvaly.prosby);
			break;
		case MODL_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_vespery.prosby);
			break;
		case MODL_PRVE_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_vespery.prosby);
			break;
		default:
			// tieto modlitby nemajú prosby
			break;
		} // switch
	} // PARAM_PROSBY
	else if (equals(paramname, PARAM_OTCENAS_UVOD)) {
		switch (modlitba) {
		case MODL_RANNE_CHVALY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_ranne_chvaly.otcenas_uvod);
			break;
		case MODL_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_vespery.otcenas_uvod);
			break;
		case MODL_PRVE_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_vespery.otcenas_uvod);
			break;
		default:
			// tieto modlitby nemajú Otčenáš
			break;
		} // switch
	} // PARAM_OTCENAS_UVOD
	else if (equals(paramname, PARAM_MODLITBA)) {
		switch (modlitba) {
		case MODL_RANNE_CHVALY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_ranne_chvaly.modlitba);
			break;
		case MODL_CEZ_DEN_9:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_9.modlitba);
			break;
		case MODL_CEZ_DEN_12:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_12.modlitba);
			break;
		case MODL_CEZ_DEN_3:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_cez_den_3.modlitba);
			break;
		case MODL_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_vespery.modlitba);
			break;
		case MODL_KOMPLETORIUM:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_kompletorium.modlitba);
			break;
		case MODL_POSV_CITANIE:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_posv_citanie.modlitba);
			break;
		case MODL_PRVE_VESPERY:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_vespery.modlitba);
			break;
		case MODL_PRVE_KOMPLETORIUM:
			ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_kompletorium.modlitba);
			break;
		default:
			// tieto modlitby nemaju antifonu1
			break;
		} // switch
	} // PARAM_MODLITBA
	else if (equals(paramname, PARAM_ANT_SPOMPRIVILEG)) {
		// kvôli spomienkam a ľubovoľným spomienkam v pôstnom období (zobrazenie po modlitbe dňa pôstnej férie); zovšeobecnené v zmysle VSLH č. 238 (Spomienky pripadajúce na privilegované dni)
		if (_global_skip_in_prayer == NIE) {
			switch (modlitba) {
			case MODL_RANNE_CHVALY:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_ranne_chvaly.ant_spomprivileg);
				break;
			case MODL_VESPERY:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_vespery.ant_spomprivileg);
				break;
			case MODL_PRVE_VESPERY:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_vespery.ant_spomprivileg);
				break;
			default:
				// tieto modlitby nemajú možnosť spomienky na svätca v pôstnom období
				break;
			} // switch
		}
	} // PARAM_ANT_SPOMPRIVILEG
	else if (equals(paramname, PARAM_MODL_SPOMPRIVILEG)) {
		// kvôli spomienkam a ľubovoľným spomienkam v pôstnom období (zobrazenie po modlitbe dňa pôstnej férie); zovšeobecnené v zmysle VSLH č. 238 (Spomienky pripadajúce na privilegované dni)
		if (_global_skip_in_prayer == NIE) {
			switch (modlitba) {
			case MODL_RANNE_CHVALY:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_ranne_chvaly.modlitba_spomprivileg);
				break;
			case MODL_VESPERY:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_vespery.modlitba_spomprivileg);
				break;
			case MODL_PRVE_VESPERY:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_prve_vespery.modlitba_spomprivileg);
				break;
			default:
				// tieto modlitby nemajú možnosť spomienky na svätca v pôstnom období
				break;
			} // switch
		}
	} // PARAM_MODL_SPOMPRIVILEG
	else if (equals(paramname, PARAM_CITANIE2_SPOMPRIVILEG)) { // 2011-03-16: pridané kvôli spomienkam a ľubovoľným spomienkam v pôstnom období (zobrazenie po 2. čítaní)
		if (_global_skip_in_prayer == NIE) {
			switch (modlitba) {
			case MODL_POSV_CITANIE:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_posv_citanie.citanie_spomprivileg);
				break;
			default:
				// tieto modlitby nemajú možnosť spomienky na svätca v pôstnom období
				break;
			} // switch
		}
	} // PARAM_CITANIE2_SPOMPRIVILEG
	// predĺžené slávenie vigílií v rámci posvätných čítaní
	else if (equals(paramname, PARAM_ANTIFONA_VIG)) {
		if (_global_skip_in_prayer == NIE) {
			switch (modlitba) {
			case MODL_POSV_CITANIE:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_posv_citanie.ant_chval);
				break;
			default:
				// tieto modlitby nemajú možnosť predĺženého slávenia vigílie
				break;
			} // switch
		}
	} // PARAM_ANTIFONA_VIG
	else if (equals(paramname, PARAM_CHVALOSPEV1)) {
		if (_global_skip_in_prayer == NIE) {
			switch (modlitba) {
			case MODL_POSV_CITANIE:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_posv_citanie.chval1);
				break;
			default:
				// tieto modlitby nemajú možnosť predĺženého slávenia vigílie
				break;
			} // switch
		}
	} // PARAM_CHVALOSPEV1
	else if (equals(paramname, PARAM_CHVALOSPEV2)) {
		if (_global_skip_in_prayer == NIE) {
			switch (modlitba) {
			case MODL_POSV_CITANIE:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_posv_citanie.chval2);
				break;
			default:
				// tieto modlitby nemajú možnosť predĺženého slávenia vigílie
				break;
			} // switch
		}
	} // PARAM_CHVALOSPEV2
	else if (equals(paramname, PARAM_CHVALOSPEV3)) {
		if (_global_skip_in_prayer == NIE) {
			switch (modlitba) {
			case MODL_POSV_CITANIE:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_posv_citanie.chval3);
				break;
			default:
				// tieto modlitby nemajú možnosť predĺženého slávenia vigílie
				break;
			} // switch
		}
	} // PARAM_CHVALOSPEV3
	else if (equals(paramname, PARAM_EVANJELIUM)) {
		if (_global_skip_in_prayer == NIE) {
			switch (modlitba) {
			case MODL_POSV_CITANIE:
				ExportFileAnchor(typ, modlitba, paramname, _global_modl_posv_citanie.evanjelium);
				break;
			default:
				// tieto modlitby nemajú možnosť predĺženého slávenia vigílie
				break;
			} // switch
		}
	} // PARAM_EVANJELIUM

	else if (equals(paramname, PARAM_TEXT)) {
		// bez ohľadu na modlitba, ktorý nie je nastavený, sa includuje nastavený súbor
		Log("volám includeFile(%d, %s, file = %s, anchor = %s)...\n", modlitba, paramname, _global_include_static_text.file, _global_include_static_text);
		ExportFileAnchor(typ, modlitba, paramname, _global_include_static_text);
	} // PARAM_TEXT

	Log("interpretParameter(%s): Dumped by %s - OK.\n", paramname, paramname);
} // interpretParameter()

// uz ma presnu cestu k suboru s templatom (vzorom) pre danu modlitbu, potom tento templat interpretuje citajuc znak po znaku nasledovne:
// -- normalne kopiruje a exportuje,
// -- ak narazi na znak CHAR_KEYWORD_BEGIN, do buffra uklada vsetko az po znak CHAR_KEYWORD_END, pototm zavola interpretParameter(strbuff) a po skonceni pokracuje dalej az do EOF.
//
// CHAR_KEYWORD_BEGIN a CHAR_KEYWORD_END su #define'ovane v liturgia.h | exportfile je definovane v myexpt.[h|c]
// 2011-05-02: znak '_' používame ako zástupný pre nezlomiteľnú medzeru (exportuje sa ako &nbsp;)
void interpretTemplate(short int typ, short int modlitba, char *tempfile, short int aj_navigacia = ANO) {
	short buff_index = 0;
	char strbuff[MAX_BUFFER];
	char isbuff = 0;

	_global_pocet_slava_otcu = 0; // pre každý súbor templátu individuálne počítame sláva otcu; 2007-05-18
	_global_pocet_navigacia = 0; // podobne aj počet parametrov navigácie; 2011-07-03 | 2012-04-19: avšak treba aj počítať počty volania interpretTemplate()
	_global_pocet_volani_interpretTemplate++;
	antifona_pocet = 0; // počet antifón (ant1, ant2, ant3 pre psalmódiu a ant. na benediktus/magnifikat kvôli krížikom)
	ant_invitat_krizik = 0; // antifóna pre invitatórium s krížikom
	mystrcpy(rest_krizik, STR_EMPTY, MAX_BUFFER); // 2011-07-08: pre to, čo je za krížikom v antifóne

	FILE *ftemplate = fopen(tempfile, "rb");

	Log("interpretTemplate(%s): Interpreting template %s\n", tempfile, tempfile);

	if (ftemplate == NULL) {
		if (typ == PRM_XML) {
			ExportXmlError((char *)html_error_template[_global_jazyk], tempfile);
		}
		else {
			ALERT;
			Export((char *)html_error_template[_global_jazyk], tempfile);
			Export("\n");
		}
		return;
	}// chyba -- šablóna sa nenašla

	struct ReadBuffer readbuff;
	Utf8DecoderState c;
	InitUtf8DecoderState(&c);

	while (1) {
		if (!LoadToBuffer(ftemplate, &readbuff)) break;
		if (!Utf8StreamingDecoder(ConsumeFromBuffer(&readbuff), &c)) continue;
		switch (c.result) {
		case CHAR_KEYWORD_BEGIN:
			isbuff = 1;
			buff_index = 0;
			continue;
		case CHAR_KEYWORD_END:
			isbuff = 0;
			strbuff[buff_index] = '\0';
			interpretParameter(typ, modlitba, strbuff, aj_navigacia);
			continue;
		} // switch(c)
		if (!isbuff) {
			if ((_global_skip_in_prayer == NIE) && (_global_skip_in_prayer_2 != ANO) && (_global_skip_in_prayer_vnpc != ANO)) {
				ExportChar(c.result, isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT));
			}// _global_skip_in_prayer == NIE && !_global_skip_in_prayer_2
		}// if (!isbuff)
		else {
			strbuff[buff_index++] = (char)c.result;
		}// else if (!isbuff)
	}
	fclose(ftemplate);
	Log("interpretTemplate(): end.\n");
} // interpretTemplate()

// podla typu modlitby pripravi templat a spusti interpretTemplate()
//
// ak je vstupom typ vespery resp. kompletorium, a v _global_modlitba je nieco ine (t.j. prve/druhe), vtedy predpokladam, ze v premennych _global_[prve_]kompletorium/vespery su spravne data
void showPrayer(short int typ, short int modlitba, short int ktore_templaty = SHOW_TEMPLAT_MODLITBA, short int aj_navigacia = ANO) {
	char templat[SMALL] = STR_EMPTY;
	char path[MAX_STR] = STR_EMPTY;
	mystrcpy(path, include_dir, MAX_STR);
	short int i = 0;

	if (modlitba == MODL_NEURCENA) {
		Log("/* teraz nasleduje zobrazenie textu (type == MODL_NEURCENA) */\n");
	}
	else {
		Log("/* teraz nasleduje zobrazenie modlitby %d */\n", modlitba);
	}
	Log("showPrayer(): begin\n");
	Log("showPrayer(), modlitba == %d, _global_modlitba == %d...\n", modlitba, _global_modlitba);

	Log("2006-10-18: _global_pocet_zalmov_kompletorium == %d\n", _global_pocet_zalmov_kompletorium);

	// ak je potrebné vytlačiť Te Deum, tak zmeníme atribút
	if (je_tedeum) {
		Log("JE tedeum...\n");
		_global_opt_tedeum = ANO;
	}
	else {
		Log("NIE JE tedeum...\n");
		_global_opt_tedeum = NIE;
	}

	Log("showPrayer: jazyk == `%s' (%d)\n", pom_JAZYK, _global_jazyk);
	Log("showPrayer: opt tedeum == %d\n", _global_opt_tedeum);

	// log options parametrov
	for (i = 0; i < POCET_GLOBAL_OPT; i++) {
		Log("showPrayer: opt %d == `%s' (%ld)\n", i, pom_OPT[i], _global_opt[i]);
	}// Log pom_OPT[i]

	// log force options parametrov
	for (i = 0; i < POCET_GLOBAL_OPT; i++) {
		Log("showPrayer: force_opt %d == `%s' (%ld)\n", i, pom_FORCE_OPT[i], _global_force_opt[i]);
	}// Log pom_FORCE_OPT[i]

	// force options parametre
	for (i = 0; i < POCET_GLOBAL_OPT; i++) {
		if (_global_opt[i] != _global_force_opt[i]) {
			Log("showPrayer: používam _global_force_opt[%d] (force)...\n", i);
			_global_opt[i] = _global_force_opt[i];
		}
	}// override pre _global_opt[i] z _global_force_opt[i]

	// log option 0
	Log("option 0 == %ld, čo znamená: \n", _global_opt[OPT_0_SPECIALNE]);
	Log("\t BIT_OPT_0_VERSE == %ld (áno == %ld)\n", _global_opt[OPT_0_SPECIALNE] & BIT_OPT_0_VERSE, BIT_OPT_0_VERSE);
	Log("\t BIT_OPT_0_REFERENCIE == %ld (áno == %ld)\n", _global_opt[OPT_0_SPECIALNE] & BIT_OPT_0_REFERENCIE, BIT_OPT_0_REFERENCIE);
	Log("\t BIT_OPT_0_REF_BIBLE_COM == %ld (áno == %ld)\n", _global_opt[OPT_0_SPECIALNE] & BIT_OPT_0_REF_BIBLE_COM, BIT_OPT_0_REF_BIBLE_COM);

	// log option 1
	Log("option 1 == %ld, čo znamená: \n", _global_opt[OPT_1_CASTI_MODLITBY]);
	Log("\t BIT_OPT_1_PROSBY_ZVOLANIE == %ld (áno == %ld)\n", _global_opt[OPT_1_CASTI_MODLITBY] & BIT_OPT_1_PROSBY_ZVOLANIE, BIT_OPT_1_PROSBY_ZVOLANIE);
	Log("\t BIT_OPT_1_SLAVA_OTCU == %ld (áno == %ld)\n", _global_opt[OPT_1_CASTI_MODLITBY] & BIT_OPT_1_SLAVA_OTCU, BIT_OPT_1_SLAVA_OTCU);

	// samotne vypisanie, o aku modlitbu ide
	Log("showPrayer(type %d, %s), _global_modlitba == %s\n", modlitba, nazov_modlitby(modlitba), nazov_modlitby(_global_modlitba));

	// umožníme aj MODL_NEURCENA -- pre statické texty
	if (((modlitba > MODL_PRVE_KOMPLETORIUM) || (modlitba < MODL_INVITATORIUM))) {
		if (query_type == PRM_XML) {
			ExportXmlError((char*)html_error_unknown_prayer[_global_jazyk]);
		}
		else {
			ALERT;
			Export((char*)html_error_unknown_prayer[_global_jazyk]);
		}
		return;
	}// neznámy typ modlitby

	if (_global_modlitba != modlitba) {

		Log("_global_modlitba != modlitba...\n");

		// zrejme ide o prvé/druhé vešpery či kompletórium
		if ((_global_modlitba == MODL_PRVE_VESPERY) && (modlitba == MODL_VESPERY)) {
			_global_modl_vespery = _global_modl_prve_vespery;
		}
		else if ((_global_modlitba == MODL_PRVE_KOMPLETORIUM) && (modlitba == MODL_KOMPLETORIUM)) {
			_global_modl_kompletorium = _global_modl_prve_kompletorium;
		}
		else if ((_global_modlitba == MODL_DRUHE_VESPERY) && (modlitba == MODL_VESPERY)) {
			// v poriadku: všetko je v _global_modl_vespery
		}
		else if ((_global_modlitba == MODL_DRUHE_KOMPLETORIUM) && (modlitba == MODL_KOMPLETORIUM)) {
			// v poriadku: všetko je v _global_modl_kompletorium
		}
		else {
			Log("_global_modlitba (%s) != type (%s), showPrayer()\n", _global_modlitba, modlitba);
			ALERT;
			Export("Nastala chyba programu (type != _global_modlitba).\n");
			return;
		}// chyba
	}// _global_modlitba != type

	// podľa parametra ktore_templaty sa rozhodneme, ktorý templát použiť
	if (ktore_templaty == SHOW_TEMPLAT_MODLITBA) {
		if (typ == PRM_XML) {
			mystrcpy(templat, TEMPLATE_XML[modlitba], SMALL);
		}
		else {
			mystrcpy(templat, TEMPLATE_HTML[modlitba], SMALL);
		}
	}
	else if (ktore_templaty == SHOW_TEMPLAT_STATIC_TEXT) {
		if (typ == PRM_XML) {
			mystrcpy(templat, TEMPLATE_XML_STATIC_TEXT, SMALL);
		}
		else {
			mystrcpy(templat, TEMPLATE_HTML_STATIC_TEXT, SMALL);
		}
	}
	Log("showPrayer: používam šablónu %s...\n", templat);
	strcat(path, templat);
	Log("showPrayer: po prilepení cesty: %s...\n", path);

	// nezobrazovanie rovnakej antifóny v modlitbe cez deň; keďže je daný jediný typ modlitby, nie je potrebné pole pre jednotlivé modlitby (aj pre kompletórium vo veľkonočnej oktáve a celom veľkonočnom období)
	if (
		(
		(modlitba == MODL_CEZ_DEN_9)
			&& (equals(_global_modl_cez_den_9.antifona1.file, _global_modl_cez_den_9.antifona2.file) && equals(_global_modl_cez_den_9.antifona1.file, _global_modl_cez_den_9.antifona3.file))
			&& (equals(_global_modl_cez_den_9.antifona1.anchor, _global_modl_cez_den_9.antifona2.anchor) && equals(_global_modl_cez_den_9.antifona1.anchor, _global_modl_cez_den_9.antifona3.anchor))
			) ||
			(
		(modlitba == MODL_CEZ_DEN_12)
				&& (equals(_global_modl_cez_den_12.antifona1.file, _global_modl_cez_den_12.antifona2.file) && equals(_global_modl_cez_den_12.antifona1.file, _global_modl_cez_den_12.antifona3.file))
				&& (equals(_global_modl_cez_den_12.antifona1.anchor, _global_modl_cez_den_12.antifona2.anchor) && equals(_global_modl_cez_den_12.antifona1.anchor, _global_modl_cez_den_12.antifona3.anchor))
				) ||
				(
		(modlitba == MODL_CEZ_DEN_3)
					&& (equals(_global_modl_cez_den_3.antifona1.file, _global_modl_cez_den_3.antifona2.file) && equals(_global_modl_cez_den_3.antifona1.file, _global_modl_cez_den_3.antifona3.file))
					&& (equals(_global_modl_cez_den_3.antifona1.anchor, _global_modl_cez_den_3.antifona2.anchor) && equals(_global_modl_cez_den_3.antifona1.anchor, _global_modl_cez_den_3.antifona3.anchor))
					)
		||
		(
		(modlitba == MODL_KOMPLETORIUM) && (_global_modl_kompletorium.pocet_zalmov == 2)
			&& (equals(_global_modl_kompletorium.antifona1.file, _global_modl_kompletorium.antifona2.file))
			&& (equals(_global_modl_kompletorium.antifona1.anchor, _global_modl_kompletorium.antifona2.anchor))
			)
		||
		(
		(modlitba == MODL_PRVE_KOMPLETORIUM) && (_global_modl_prve_kompletorium.pocet_zalmov == 2)
			&& (equals(_global_modl_prve_kompletorium.antifona1.file, _global_modl_prve_kompletorium.antifona2.file))
			&& (equals(_global_modl_prve_kompletorium.antifona1.anchor, _global_modl_prve_kompletorium.antifona2.anchor))
			)
		) {
		_global_ant_mcd_rovnake = ANO;
	}
	else {
		_global_ant_mcd_rovnake = NIE;
	}
	Log("showPrayer: _global_ant_mcd_rovnake == %d\n", _global_ant_mcd_rovnake);

	interpretTemplate(typ, modlitba, path, aj_navigacia);

	Log("showPrayer(): end\n");
} // showPrayer();

void vysvetlivky(void) {
	char fname[MAX_STR] = STR_EMPTY;
	mystrcpy(fname, include_dir, MAX_STR);
	strcat(fname, FILE_VYSVETLIVKY);
	Export(HTML_COMMENT_BEGIN); // simulacia toho, ze replacujeme nejaky anchor
	includeFile(PRM_DATUM, 0, ANCHOR_VYSVETLIVKY, fname, ANCHOR_VYSVETLIVKY); // first parameter should be anything else except PRM_XML
	Export(HTML_COMMENT_END); // simulacia toho, ze replacujeme nejaky anchor
} // vysvetlivky()

void vysvetlivky_tabulka(void) {
	char fname[MAX_STR] = STR_EMPTY;
	mystrcpy(fname, include_dir, MAX_STR);
	strcat(fname, FILE_VYSVETLIVKY_TABULKA);
	Export(HTML_COMMENT_BEGIN); // simulacia toho, ze replacujeme nejaky anchor
	includeFile(PRM_DATUM, 0, ANCHOR_VYSVETLIVKY_TABULKA, fname, ANCHOR_VYSVETLIVKY_TABULKA); // first parameter should be anything else except PRM_XML
	Export(HTML_COMMENT_END); // simulacia toho, ze replacujeme nejaky anchor
} // vysvetlivky_tabulka()

// skontroluje dátum, či je správne zadaný,
// return: on success, returns SUCCESS
//         on error,   returns FAILURE
#define ExportKONTROLA _export_heading("Kontrola dňa"); Export
short int kontrola_den_mesiac_rok(short int den, short int mesiac, short int rok) {
	if ((mesiac < 1) || (mesiac > 12)) {
		ExportKONTROLA("Takýto mesiac nepoznám (%d).\n", mesiac);
		return FAILURE;
	}

	if (prestupny(rok)) {
		pocet_dni[MES_FEB] = 29;
	}
	else {
		pocet_dni[MES_FEB] = 28;
	}

	if ((den < 1) || (den > pocet_dni[mesiac - 1])) {
		if ((mesiac == 2) && (pocet_dni[MES_FEB] == 29)) {
			ExportKONTROLA("Rok %d je síce prestupný, ale aj tak má %s len 29 dní.\n", rok, nazov_mesiaca(MES_FEB));
		}
		else if (mesiac == 2) {
			ExportKONTROLA("Rok %d nie je prestupný, takže %s má len 28 dní.\n", rok, nazov_mesiaca(MES_FEB));
		}
		else {
			ExportKONTROLA("Mesiac %s má %d dní.\n", nazov_mesiaca(mesiac - 1), pocet_dni[mesiac - 1]);
		}
		return FAILURE;
	}
	return SUCCESS;
} // kontrola_den_mesiac_rok()

// popis: vráti číslo liturgického obdobia (0--6), ak sa lo == cezročné atď...
//        inak vráti OBD_CEZ_ROK (cezročné obdobie)
short int atolitobd(char *lo) {
	short int i = 0;
	Log("lo == '%s'\n", lo);
	do {
		// Log("nazov_obdobia_ext(%d) == %s...\n", i, nazov_obdobia_ext(i));
		if (equals(lo, nazov_obdobia_ext(i))) {
			Log("atolitobd: returning %d\n", i);
			return i;
		}
		if (equals(lo, nazov_obdobia_short(i))) {
			Log("atolitobd: returning %d\n", i);
			return i;
		}
		i++;
	} while (i <= POCET_OBDOBI);
	// 2011-05-11: ak sa nenašlo obdobie porovnaním s reťazcom, skúsim prekonvertovať na číslo
	i = atoi(lo);
	i = ((i < OBD_ADVENTNE_I) || (i > OBD_VELKONOCNE_II)) ? OBD_CEZ_ROK : i;
	Log("atolitobd: returning %d\n", i);
	return i;
	// return OBD_CEZ_ROK;
} // atolitobd()

// popis: vráti číslo dňa (0--6), ak sa den == pondelok...
//        inak vráti UNKNOWN_DEN
short int atodenvt(char *den) {
	short int i = 0;
	do {
		if (equals(den, nazov_dna(i)) || equals(den, nazov_dna_asci(i))) {
			return i;
		}
		i++;
	} while (i < DEN_UNKNOWN);
	// 2011-05-11: ak sa nenašiel deň v týždni porovnaním s reťazcom, skúsim prekonvertovať na číslo
	i = atoi(den);
	return ((i < DEN_NEDELA) || (i > DEN_SOBOTA)) ? DEN_UNKNOWN : i;
	// return DEN_UNKNOWN;
} // atodenvt()

// popis: vráti int (číslo dňa 1--31), ak sa den == 1,2...
//        alebo (ako den == STR_VSETKY_DNI) vráti VSETKY_DNI;
//        v pripade iných údajov vráti 0
short int atoden(char *den) {
	short int d;
	if (equals(den, STR_VSETKY_DNI))
		return VSETKY_DNI;
	else {
		d = atoi(den);
		return ((d < 0) || (d > 31)) ? 0 : d;
	}
} // atoden()

// popis: vráti číslo mesiaca (0--11), ak sa den == januar...
//        alebo vráti VSETKY_MESIACE, ak den == STR_VSETKY_MESIACE;
//        inak vráti UNKNOWN_MESIAC
short int atomes(char *mesiac) {
	// sprintf(pom_MESIAC, "%d", cislo_mesiaca(pom_MESIAC));
	if (equals(mesiac, STR_VSETKY_MESIACE))
		return VSETKY_MESIACE;
	// mesiac moze byt string "1" -- "12" alebo nazov_mesiaca(0 -- 11)
	short int i = atoi(mesiac) - 1;
	if ((i >= MES_JAN) && (i <= MES_DEC))
		return i;
	i = 0;
	do {
		if (equals(mesiac, nazov_mesiaca(i)) || equals(mesiac, nazov_mesiaca_asci(i))) {
			return i;
		}
		i++;
	} while (i < UNKNOWN_MESIAC);
	// ešte jeden pokus pre ostatné jazyky
	int j = -1;
	if (i == UNKNOWN_MESIAC) {
		do {
			++j;
			if ((j != JAZYK_UNDEF) && (j != _global_jazyk)) {
				i = 0;
				do {
					if (equals(mesiac, nazov_mesiaca_jazyk[i][j])) {
						return i;
					}
					i++;
				} while (i < UNKNOWN_MESIAC);
			}
		} while (j <= POCET_JAZYKOV);
	}
	return UNKNOWN_MESIAC;
} // atomes()

// popis: vráti číslo jazyka 
//        inak vráti JAZYK_UNDEF
short int atojazyk(char *jazyk) {
	short int i = 0;
	short int j = 0;
	do {
		if (equalsi(jazyk, skratka_jazyka[i]) || equalsi(jazyk, nazov_jazyka(i)) || equalsi(jazyk, nazov_jazyka_native_jazyk(i))) {
			return i;
		}
		for (j = 0; j <= POCET_JAZYKOV; j++) {
			if (equalsi(jazyk, nazov_jazyka_native_jazyk[i][j])) {
				return i;
			}
		}
		i++;
	} while (i <= POCET_JAZYKOV);
	return JAZYK_UNDEF;
} // atojazyk()

// popis: vráti číslo kalendára, napr. rehoľný
//        inak vráti KALENDAR_NEURCENY
short int atokalendar(char *kalendar) {
	if (_global_jazyk == JAZYK_CZ_OP) {
		// for JAZYK_CZ_OP, only one special kalendar available
		return KALENDAR_CZ_OP;
	}
	short int i = 0;
	do {
		if (equalsi(kalendar, skratka_kalendara[i]) || equalsi(kalendar, nazov_kalendara_short[i]) || equalsi(kalendar, nazov_kalendara_smart[i]) || equalsi(kalendar, nazov_kalendara_long[i])) {
			return i;
		}
		i++;
	} while (i <= POCET_KALENDAROV);
	return KALENDAR_NEURCENY;
} // atokalendar()

// popis: vráti číslo css-ka
//        inak vráti CSS_UNDEF
short int atocss(char *css) {
	short int i = 0;
	do {
		if (equalsi(css, skratka_css[i]) || equalsi(css, nazov_css[i])) {
			return i;
		}
		i++;
	} while (i <= POCET_CSS);
	return CSS_UNDEF;
} // atocss()

// popis: vráti číslo fontu
//        inak vráti FONT_CUSTOM
short int atofont(char *font) {
	short int i = 0;
	do {
		if (equalsi(font, nazov_fontu[i])) {
			return i;
		}
		if ((i == FONT_CSS) && equalsi(font, nazov_fontu_CSS[_global_jazyk])) {
			return i;
		}
		if ((i == FONT_CHECKBOX) && equalsi(font, nazov_fontu_CHECKBOX[_global_jazyk])) {
			return i;
		}
		i++;
	} while (i <= POCET_FONTOV);
	return FONT_CUSTOM;
} // atofont()

// popis: vráti index veľkosti fontu
//        inak vráti FONT_SIZE_UNDEF
short int atofontsize(char *font) {
	short int i = 0;
	do {
		if (equalsi(font, nazov_font_size(i))) {
			return i;
		}
		if (equalsi(font, nazov_font_size_css[i])) {
			return i;
		}
		i++;
	} while (i <= POCET_FONT_SIZE);
	return FONT_SIZE_UNDEF;
} // atofontsize()

// popis: vráti číslo statického textu
//        inak vráti STATIC_TEXT_UNDEF
short int atoStaticText(char *css) {
	short int i = 0;
	do {
		if (equalsi(css, skratka_static_text[i])) {
			return i;
		}
		i++;
	} while (i <= POCET_STATIC_TEXTOV);
	return STATIC_TEXT_UNDEF;
} // atoStaticText()

// popis: vráti číslo modlitby
//        inak vráti MODL_NEURCENA
short int atomodlitba(char *modlitba) {
	short int p = MODL_NEURCENA;
	// rozparsovanie parametra modlitba
	Log("atomodlitba(%s): rozparsovanie parametra modlitba...\n", modlitba);
	if (equals(modlitba, STR_EMPTY) || strlen(modlitba) < 1)
		p = MODL_NEURCENA;
	else if (equals(modlitba, STR_MODL_VSETKY))
		p = MODL_VSETKY;
	else if (equals(modlitba, STR_MODL_DETAILY))
		p = MODL_DETAILY;
	else if (equals(modlitba, STR_MODL_INVITATORIUM))
		p = MODL_INVITATORIUM;
	else if (equals(modlitba, STR_MODL_RANNE_CHVALY))
		p = MODL_RANNE_CHVALY;
	else if (equals(modlitba, STR_MODL_POSV_CITANIE))
		p = MODL_POSV_CITANIE;
	else if (equals(modlitba, STR_MODL_PREDPOLUDNIM))
		p = MODL_PREDPOLUDNIM;
	else if (equals(modlitba, STR_MODL_NAPOLUDNIE))
		p = MODL_NAPOLUDNIE;
	else if (equals(modlitba, STR_MODL_POPOLUDNI))
		p = MODL_POPOLUDNI;
	else if (equals(modlitba, STR_MODL_VESPERY))
		p = MODL_VESPERY;
	else if (equals(modlitba, STR_MODL_KOMPLETORIUM))
		p = MODL_KOMPLETORIUM;
	else if (equals(modlitba, STR_MODL_PRVE_VESPERY))
		p = MODL_PRVE_VESPERY;
	else if (equals(modlitba, STR_MODL_PRVE_KOMPLETORIUM))
		p = MODL_PRVE_KOMPLETORIUM;
	else
		p = MODL_NEURCENA;

	// este treba skontrolovat, ci nazov modlitby nie je string ...azov_modlitby[...]
	if ((p == MODL_NEURCENA) && strlen(modlitba) > 0) {
		int pom_i = atoi(modlitba);
		// atoi() vracia hodnotu 0 (naša hodnota MODL_INVITATORIUM) pre každý reťazec, ktorý nie je konvertovateľný na číslo, 
		// preto sme vyššie porovnali s "0" špeciálne a tu značí pom_i == 0 nie MODL_INVITATORIUM, ale chybu
		Log("atomodlitba(): pokus určenia modlitby konverziou reťazca `%s' na číslo (%d)...\n", modlitba, pom_i);
		// for strings, atoi()'s behavior: zero is returned
		if ((pom_i == 0) || (pom_i < MODL_INVITATORIUM) || (pom_i > MODL_VSETKY)) {
			// postupne porovnavame s troma konstantami, nazov_[modlitby|Modlitby|MODLITBY], a to pre konstanty MODL_INVITATORIUM -- MODL_VSETKY (vratane)
			Log("atomodlitba(): pokus určenia modlitby podľa jazykovo závislých reťazcov pre modlitba == `%s'...\n", modlitba);
			for (pom_i = MODL_INVITATORIUM; pom_i <= MODL_VSETKY; pom_i++) {
				Log("\tstep: %d `%s'...\n", pom_i, nazov_modlitby(pom_i));
				if (equals(modlitba, nazov_modlitby(pom_i)) ||
					equals(modlitba, nazov_modlitby_short(pom_i)) ||
					equals(modlitba, nazov_Modlitby(pom_i))) {
					// ak je zhoda, potom prirad do p a ukonci `for'
					p = pom_i;
					break;
				}
			}// for pom_i
		}
		else {
			p = pom_i;
		}
	}
	Log("atomodlitba(): returning %d...\n", p);
	return p;
} // atomodlitba()

void _rozbor_dna_base(_struct_den_mesiac datum, short int rok) {
	Log("_rozbor_dna_base(): begin...\n");

	_global_den.den = datum.den;
	_global_den.mesiac = datum.mesiac;
	_global_den.rok = rok;
	_global_den.denvr = poradie(datum.den, datum.mesiac, rok);
	_global_den.denvt = den_v_tyzdni(datum.den, datum.mesiac, rok);

	Log("_rozbor_dna_base(): end.\n");
}// _rozbor_dna_base()

// predpokoladam, ze pred jeho volanim bolo pouzite analyzuj_rok(rok); ktore da vysledok do _global_r
// dostane {den, mesiac} a rok
// navratova hodnota je SUCCESS alebo FAILURE
#define _rozbor_dna_LOG Log("-- _rozbor_dna({%d, %d}, %d, %d): ", datum.den, datum.mesiac, rok, poradie_svaty); Log

short int _rozbor_dna(_struct_den_mesiac datum, short int rok, short int poradie_svaty) {
	Log("_rozbor_dna(): 3 parametre -- begin\n");
	_rozbor_dna_LOG("begin\n");

	if (poradie_svaty == UNKNOWN_PORADIE_SVATEHO) {
		Log("spustam pre poradie_svaty == UNKNOWN_PORADIE_SVATEHO\n");
	}

	short int NARODENIE_PANA = poradie(25, 12, rok); // narodenie pana
	// slavnosti
	short int BOHORODICKY_PANNY_MARIE = poradie(1, 1, rok); // panny marie bohorodicky
	short int ZJAVENIE_PANA; // zjavenie Pána
	char nedelne_pismenko = _global_r.p1;
	if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA)) {
		if (nedelne_pismenko == 'A') {
			nedelne_pismenko = 'h'; // aby vyšla nedeľa Zjavenia Pána na 8.1.
		}
		Log("Zjavenie Pána sa slávi v nedeľu; %c/%c\n", _global_r.p1, nedelne_pismenko);
		ZJAVENIE_PANA = poradie((nedelne_pismenko - 'a') + 1, 1, rok); // nedeľa medzi 2. a 8. januárom
	}
	else {
		ZJAVENIE_PANA = poradie(6, 1, rok);
	}
	// ak padne Zjavenia Pána na nedeľu 7. alebo 8.1., treba upraviť slávenie sviatku Krstu Krista Pána (SK LH, zv. I, str. 377) -- realizované v _dm_krst_krista_pana()
	short int DECEMBER_16 = poradie(16, 12, rok); // 16. december, prelom v adventnom období
	short int TELAKRVI; // štvrtok po Trojici: Kristovho tela a krvi (alebo: v krajinách, kde sa presúva na nedeľu)
	if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_TELAKRVI_NEDELA)) {
		Log("Najsv. Kristovho tela a krvi sa slávi v nedeľu\n");
		TELAKRVI = (ZOSLANIE_DUCHA_SV + 14);
	}
	else {
		TELAKRVI = (ZOSLANIE_DUCHA_SV + 11);
	}

	// 2006-02-06: pomocná premenná kvôli eventuálnemu prednastaveniu _global_opt 3
	_struct_sc sc;
	sc.a1 = MODL_SPOL_CAST_NEURCENA;
	sc.a2 = MODL_SPOL_CAST_NEURCENA;
	sc.a3 = MODL_SPOL_CAST_NEURCENA;

	// určenie "občianskych" (civilných) záležitostí dňa:
	// den, mesiac, rok, denvr, denvt
	Log("urcenie 'obcianskych' zalezitosti dna:\n");
	_rozbor_dna_base(datum, rok);
	_rozbor_dna_LOG("denvr == %d, denvt == %d...\n", _global_den.denvr, _global_den.denvt);

	// určenie všeobecnych "liturgických" záležitostí dňa:
	if (_global_den.denvr < PRVA_ADVENTNA_NEDELA) {
		_global_den.litrok = _global_r._POPOLCOVA_STREDA.litrok;
		_rozbor_dna_LOG("pred prvou adventnou nedelou v roku\n");
	}
	else {
		_global_den.litrok = _global_r._SVATEJ_RODINY.litrok;
		_rozbor_dna_LOG("po prvej adventnej nedeli v roku (vratane)\n");
	}
	_global_den.tyzzal = 0;
	_global_den.tyzden = 0;
	_global_den.smer = 14; // undefined
	_global_den.typslav = SLAV_NEURCENE;
	_global_den.prik = NIE_JE_PRIKAZANY_SVIATOK;
	_global_den.typslav_lokal = LOKAL_SLAV_NEURCENE;
	mystrcpy(_global_den.meno, STR_EMPTY, MENO_SVIATKU);
	_global_den.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA);
	_global_den.farba = LIT_FARBA_NEURCENA;
	_global_den.kalendar = KALENDAR_NEURCENY;
	mystrcpy(_global_den.lc_str_id, STR_EMPTY, MAX_LC_STR_ID);

	_rozbor_dna_LOG("určenie ostatných špecifických 'liturgických' záležitostí...\n");
	// tyzzal, litobd, tyzden, smer, typslav, prip. meno
	if (_global_den.denvr < VELKONOCNA_NEDELA) {
		// pred velkou nocou
		_rozbor_dna_LOG("/* pred velkou nocou */\n");
		if (_global_den.denvr >= POPOLCOVA_STREDA) {
			// postne obdobie
			_global_den.farba = LIT_FARBA_FIALOVA;
			_global_den.kalendar = KALENDAR_VSEOBECNY;
			_rozbor_dna_LOG("/* postne obdobie */\n");
			_global_den.litobd = OBD_POSTNE_I; // do soboty v 5. post.tyzdni
			_global_den.smer = 9; // vsedne dni v poste

			if (_global_den.denvr == POPOLCOVA_STREDA) {
				// _global_den.denvr == POPOLCOVA_STREDA
				_rozbor_dna_LOG("/* _global_den.denvr == POPOLCOVA_STREDA */\n");
				_global_den = _global_r._POPOLCOVA_STREDA;
			}
			else if (_global_den.denvr <= POPOLCOVA_STREDA + 3) {
				// stvrtok, piatok, sobota po popolcovej strede
				_rozbor_dna_LOG("/* stvrtok, piatok, sobota po popolcovej strede */\n");
				/* mystrcpy(_global_den.meno, nazov_dna(_global_den.denvt));
				strcat(_global_den.meno, " po popolcovej strede"); */
				_global_den.tyzden = 0; // pridane 06/03/2000A.D. namiesto tohto: // _global_den.tyzzal = 4;
			}
			else if (_global_den.denvr <= BIELA_SOBOTA) {
				// pred a vratane bielej soboty
				_rozbor_dna_LOG("/* pred a vratane bielej soboty */\n");

				// urcuje postny tyzden
				_rozbor_dna_LOG("/* urcuje postny tyzden */\n");
				_global_den.tyzden = ((_global_den.denvr - POPOLCOVA_STREDA - 4) DIV 7) + 1;

				if (_global_den.denvr < KVETNA_NEDELA) {
					// pred kvetnou nedelou
					_rozbor_dna_LOG("/* pred kvetnou nedelou */\n");
					if (_global_den.denvt == DEN_NEDELA) {
						_rozbor_dna_LOG("/* nedela v postnom obdobi */\n");
						_global_den.smer = 2; // nedele adventné, pôstne a veľkonočné

						if (_global_den.denvr == STVRTA_POSTNA_NEDELA) {
							// pre 4. pôstnu nedeľu je ružová farbe rúcha
							_global_den.farba = LIT_FARBA_RUZOVA_FIALOVA;
						}
					}
					else {
						_rozbor_dna_LOG("/* vsedny den v poste */\n");
						_global_den.smer = 9; // všedné dni v pôste
					}
				}
				else if (_global_den.denvr == KVETNA_NEDELA) {
					// kvetna nedela
					_rozbor_dna_LOG("/* kvetna nedela */\n");
					_global_den.farba = LIT_FARBA_CERVENA;
					_global_den.litobd = OBD_POSTNE_II_VELKY_TYZDEN;
					_global_den.smer = 2; // nedele adventné, pôstne a veľkonočné
					mystrcpy(_global_den.meno, text_KVETNA_NEDELA[_global_jazyk], MENO_SVIATKU);
				}
				else if (_global_den.denvr <= ZELENY_STVRTOK) {
					// po kvetnej nedeli, vo velkom tyzdni
					_rozbor_dna_LOG("/* po kvetnej nedeli, vo velkom tyzdni */\n");
					_global_den.litobd = OBD_POSTNE_II_VELKY_TYZDEN;
					_global_den.smer = 2; // nedele adventné, pôstne a veľkonočné
					// vsedne dni velkeho tyzdna od pondelka do stvrtka vratane
					if (_global_den.denvr == ZELENY_STVRTOK) {
						mystrcpy(_global_den.meno, text_ZELENY_STVRTOK[_global_jazyk], MENO_SVIATKU);
						_global_den.farba = LIT_FARBA_FIALOVA_BIELA;
					}
				}
				else {
					_global_den.litobd = OBD_VELKONOCNE_TROJDNIE;
					_global_den.smer = 1;
					_global_den.typslav = SLAV_VLASTNE;
					// velkonocne trojdnie umucenia a zmrtvychvstania
					_rozbor_dna_LOG("/* velkonocne trojdnie umucenia a zmrtvychvstania */\n");
					if (_global_den.denvr == VELKY_PIATOK) {
						mystrcpy(_global_den.meno, text_VELKY_PIATOK[_global_jazyk], MENO_SVIATKU);
						_global_den.farba = LIT_FARBA_CERVENA;
					}
					else if (_global_den.denvr == BIELA_SOBOTA) {
						mystrcpy(_global_den.meno, text_BIELA_SOBOTA[_global_jazyk], MENO_SVIATKU);
						// farba ostáva nastavená ako pre celý pôst - fialová
						// pridaná poznámka: Svätá sobota (Biela sobota) má fialovú farbu; len pre vigíliu je biela
						// _global_den.farba = LIT_FARBA_BIELA;
					}
				}
			}// if (_global_den.denvr <= BIELA_SOBOTA)

			// 2014-03-21: nastavenie lc_str_id pre pôstne obdobie -- iba ak nebolo nastavené vyššie
			if (equals(_global_den.lc_str_id, STR_EMPTY)) {
				if (_global_den.denvt == DEN_NEDELA) {
					sprintf(_global_den.lc_str_id, "%dP", _global_den.tyzden);
				}
				else {
					sprintf(_global_den.lc_str_id, "%dP%d", _global_den.tyzden, _global_den.denvt);
				}
			}
		}// if (_global_den.denvr >= POPOLCOVA_STREDA)
		else if (_global_den.denvr < POPOLCOVA_STREDA) {
			// od 1.1. po post, teda bud vianocne obdobie alebo obdobie cez rok
			_rozbor_dna_LOG("/* od 1.1. po post, teda bud vianocne obdobie alebo obdobie cez rok */\n");
			if (_global_den.denvr == BOHORODICKY_PANNY_MARIE) {
				// slavnost panny marie bohorodicky
				_rozbor_dna_LOG("/* slavnost panny marie bohorodicky */\n");
				_global_den.tyzden = 1; // overoval som, či to nemôže padnúť na iný týždeň (nemôže)
				_global_den.farba = LIT_FARBA_BIELA;
				_global_den.kalendar = KALENDAR_VSEOBECNY;
				_set_slavenie_typslav_smer(0, SLAV_SLAVNOST, 3); // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
				_global_den.litobd = OBD_OKTAVA_NARODENIA;
				_global_den.prik = PRIKAZANY_SVIATOK;
				// 2011-02-01: pre SJ odlišný názov; ináč je všetko rovnaké
				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)) {
					mystrcpy(_global_den.meno, text_JAN_01_SJ[_global_jazyk], MENO_SVIATKU);
					_global_den.kalendar = KALENDAR_SK_SJ;
				}
				else {
					mystrcpy(_global_den.meno, text_JAN_01[_global_jazyk], MENO_SVIATKU);
				}
				// substring (koniec Oktávy narodenia Pána) podobne ako (2. veľkonočná nedeľa) riešený pomocou "typslav_lokal" -> text_KONIEC_OKTAVY_NARODENIA_PANA[]
				_global_den.typslav_lokal = LOKAL_SLAV_KONIEC_OKTAVY_NAR;

				sprintf(_global_den.lc_str_id, "%d.%d.", _global_den.den, _global_den.mesiac);
			}
			else if (_global_den.denvr == ZJAVENIE_PANA) {
				// slavnost zjavenia pana
				_rozbor_dna_LOG("/* slavnost zjavenia pana */\n");
				_dm_zjavenie_pana(_global_den.rok, _global_den.denvr);
				_global_den = _global_result;
				/*
				_global_den.farba = LIT_FARBA_BIELA;
				_global_den.kalendar = KALENDAR_VSEOBECNY;
				_global_den.smer = 2; // zjavenie Pána
				_global_den.typslav = SLAV_SLAVNOST;
				_global_den.litobd = OBD_VIANOCNE_II;
				_global_den.tyzden = 2;
				_global_den.prik = PRIKAZANY_SVIATOK;
				mystrcpy(_global_den.meno, text_JAN_06[_global_jazyk], MENO_SVIATKU);
				sprintf(_global_den.lc_str_id, "%d.%d.", _global_den.den, _global_den.mesiac);
				*/
			}
			else if ((_global_den.denvt == DEN_NEDELA) && (_global_den.denvr >= 2) && (_global_den.denvr <= 5)) {
				// druha nedela po narodeni pana medzi 2. a 5. januarom; v krajinach, kde sa slavnost zjavenia pana slavi 6. januara
				_rozbor_dna_LOG("/* druha nedela po narodeni pana medzi 2. a 5. januarom; v krajinach, kde sa slavnost zjavenia pana slavi 6. januara */\n");
				_global_den.farba = LIT_FARBA_BIELA;
				_global_den.kalendar = KALENDAR_VSEOBECNY;
				_global_den.smer = 6; // nedele vianočné (a cezročné)
				_global_den.litobd = OBD_VIANOCNE_I;
				mystrcpy(_global_den.meno, text_DRUHA_NEDELA_PO_NAR_PANA[_global_jazyk], MENO_SVIATKU);
				_global_den.tyzden = 2; // doplnené, keďže v časti nižšie sme (správne) zapoznámkovali natvrdo nastavenie týždňa na 2
				mystrcpy(_global_den.lc_str_id, "2NP", MAX_LC_STR_ID);
			}
			else if (_global_den.denvr < KRST) {
				// vianočné obdobie
				_rozbor_dna_LOG("/* vianocne obdobie */\n");
				_global_den.farba = LIT_FARBA_BIELA;
				_global_den.kalendar = KALENDAR_VSEOBECNY;
				// všedné dni vianočného obdobia od 2. januára do soboty po zjavení pána
				_global_den.smer = 13; // všedné dni vianočné
				// zistíme, či je pred alebo po zjavení pána
				if (_global_den.denvr < ZJAVENIE_PANA) {
					_global_den.litobd = OBD_VIANOCNE_I;
					_rozbor_dna_LOG("/* pred zjavenim Pana */\n");
				}
				else {
					_global_den.litobd = OBD_VIANOCNE_II;
					_rozbor_dna_LOG("/* po zjaveni Pana (vratane) */\n");
				}
				// keďže KRST je poradové číslo dňa v roku, ale je to vždy január, je to vlastne aj dátum
				// opravené; podľa smerníc (č. 133) -- "prvý týždeň sa začína na Prvú adventnú nedeľu, v prvý týždeň v Cezročnom období, na Prvú pôstnu nedeľu a na Prvú veľkonočnú nedeľu."
				if (KRST == 8) {
					if ((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA))) {
						// v krajinách, kde sa Zjavenie Pána slávi v nedeľu: ak Krst Krista Pána padne na 8.1. (pondelok), potom pred nedeľou Zjavenia Pána 7.1. sú všedné dni 1. týždeň žaltára (8.1. ako Krst Krista Pána nemôže padnúť na nedeľu; 8.1. ak je nedeľa, je to Zjavenie Pána a Krst Krista Pána je v pondelok 9.1.)
						_global_den.tyzden = 1;
					}
					else {
						// v krajinách, kde sa Zjavenie Pána slávi 6.1.: ak Krst Krista Pána pripadne na 8.1., všedné dni od 2. do 5. januára majú mať 1. týždeň žaltára (v tomto prípade 2. nedeľa po narodení Pána nie je, ale jej úlohu akoby zohráva 1.1.)
						_global_den.tyzden = 2;
					}// napr. SK rok 2012
				}
				else if (KRST == 7) {
					// ak Krst Krista Pána pripadne na 7.1., všedné dni od 2. do 5. januára majú mať 1. týždeň žaltára (v týchto prípadoch 2. nedeľa po narodení Pána nie je)
					_global_den.tyzden = 1;
				}
				else {
					// keď Krst Krista Pána pripadne na 9.-13.1., závisí týždeň žaltára od toho, či deň je pred alebo po 2. nedeli po narodení Pána (jej dátum je vlastne KRST - 7)
					if (KRST - 7 > _global_den.denvr) {
						_global_den.tyzden = 1;
					}
					else {
						_global_den.tyzden = 2;
					}
					// podmienka je pre krajiny, kde sa slávnosť Zjavenia Pána slávi 6.1., ekvivalentná nasledovnej:
					// _global_den.tyzden = _global_den.denvr < "_global_r.p1" + 1)? 1 : 2; // pritom "_global_r.p1" je 'A' = 0, 'b' = 1, 'c' = 2, 'd' = 3..., 'g' = 6
				}
			}// vianočné obdobie od KRST
			else if (_global_den.denvr > KRST) {
				// obdobie cez rok po vianociach do popolcovej stredy
				_rozbor_dna_LOG("/* obdobie cez rok po vianociach do popolcovej stredy */\n");
				_global_den.farba = LIT_FARBA_ZELENA;
				_global_den.kalendar = KALENDAR_VSEOBECNY;
				_global_den.litobd = OBD_CEZ_ROK;
				// určenie týždňa v cezročnom období (v období "cez rok")
				// 2012-01-13: oprava pre prípady, kedy KRST padol na pondelok (po nedeli Zjavenia Pána v krajinách, kde sa Zjavenie Pána slávi v nedeľu, napr. HU)
				_global_den.tyzden = ((_global_den.denvr - KRST + _global_r._KRST_KRISTA_PANA.denvt) DIV 7) + 1; // nedeľa = 0, teda ako doteraz
				if (_global_den.denvt == DEN_NEDELA) {
					// nedela v obdobi cez rok
					_rozbor_dna_LOG("/* nedela v obdobi cez rok */\n");
					_global_den.smer = 6; // nedele cezročné (a vianočné)
				}
				else {
					// vsedny den v obdobi cez rok
					_rozbor_dna_LOG("/* vsedny den v obdobi cez rok */\n");
					_global_den.smer = 13; // všedné dni cezročné
				}

				// 2014-03-21: nastavenie lc_str_id pre cezročné obdobie -- iba ak nebolo nastavené vyššie
				if (equals(_global_den.lc_str_id, STR_EMPTY)) {
					if (_global_den.denvt == DEN_NEDELA) {
						sprintf(_global_den.lc_str_id, "%dC", _global_den.tyzden);
					}
					else {
						sprintf(_global_den.lc_str_id, "%dC%d", _global_den.tyzden, _global_den.denvt);
					}
				}
			}// if (_global_den.denvr > KRST)
			else if (_global_den.denvr == KRST) {
				// sviatok krstu krista pana, nedela po 6. januari
				_rozbor_dna_LOG("/* sviatok krstu krista pana, nedela po 6. januari */\n");
				_global_den = _global_r._KRST_KRISTA_PANA;
			}// if (_global_den.denvr == KRST)
		}// if (_global_den.denvr < POPOLCOVA_STREDA)
	}// if (_global_den.denvr < VELKONOCNA_NEDELA)
	else if (_global_den.denvr >= VELKONOCNA_NEDELA) {
		// po velkej noci
		_rozbor_dna_LOG("/* po veľkej noci vrátane veľkonočnej nedele (t.j. _global_den.denvr >= VELKONOCNA_NEDELA) */\n");
		if (_global_den.denvr <= ZOSLANIE_DUCHA_SV) {
			// velkonocne obdobie (po zoslanie d.s.)
			_rozbor_dna_LOG("/* velkonocne obdobie (po zoslanie d.s.) */\n");
			_global_den.farba = LIT_FARBA_BIELA;
			_global_den.kalendar = KALENDAR_VSEOBECNY;
			_global_den.tyzden = ((_global_den.denvr - VELKONOCNA_NEDELA) DIV 7) + 1;

			if (_global_den.denvr == ZOSLANIE_DUCHA_SV) {
				// zoslanie ducha svateho
				_rozbor_dna_LOG("/* zoslanie ducha svateho */\n");
				_global_den = _global_r._ZOSLANIE_DUCHA_SV;
			}
			else if (_global_den.denvr <= DRUHA_VELKONOCNA_NEDELA) {
				// velkonocna oktava
				_rozbor_dna_LOG("/* velkonocna oktava */\n");
				_global_den.litobd = OBD_VELKONOCNA_OKTAVA;
				_global_den.smer = 2; // dni velkonocnej oktavy
				if (_global_den.denvr == VELKONOCNA_NEDELA) {
					// velkonocna nedela
					_rozbor_dna_LOG("/* velkonocna nedela */\n");
					_global_den = _global_r._VELKONOCNA_NEDELA;
				}
				else {
					// velkonocna oktava
					_rozbor_dna_LOG("/* velkonocna oktava */\n");
					_global_den.litobd = OBD_VELKONOCNA_OKTAVA;
					if (_global_den.denvr == DRUHA_VELKONOCNA_NEDELA) {
						// 2. velkonocna nedela
						_rozbor_dna_LOG("/* 2. velkonocna nedela */\n");
						mystrcpy(_global_den.meno, text_NEDELA_VO_VELKONOCNEJ_OKTAVE[_global_jazyk], MENO_SVIATKU);
						// substring (2. veľkonočná nedeľa) riešený pomocou "typslav_lokal" -> text_NEDELA_VO_VELKONOCNEJ_OKTAVE_SUBSTRING[]
						_global_den.typslav_lokal = LOKAL_SLAV_DRUHA_VELK_NEDELA;
					}
					else {
						// veľkonočná oktáva - 'všedný deň' vo veľkonočnej oktáve
						_rozbor_dna_LOG("/* veľkonočná oktáva - 'všedný deň' vo veľkonočnej oktáve */\n");
						// if (_global_jazyk == JAZYK_SK) pôvodne: sprintf(_global_den.meno, text_DEN_VO_VELKONOCNEJ_OKTAVE[_global_jazyk], koncovka_dna(_global_den.denvt), nazov_dna(_global_den.denvt));
						if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)) {
							sprintf(_global_den.meno, text_DEN_VO_VELKONOCNEJ_OKTAVE[_global_jazyk], nazov_Dna(_global_den.denvt));
						}
						else if ((_global_jazyk == JAZYK_HU) || (_global_jazyk == JAZYK_IS)) {
							if (_global_den.denvt == DEN_PONDELOK) {
								// veľkonočný pondelok ináč
								mystrcpy(_global_den.meno, text_VELKONOCNY_PONDELOK[_global_jazyk], MENO_SVIATKU);
							}
							else {
								sprintf(_global_den.meno, text_DEN_VO_VELKONOCNEJ_OKTAVE[_global_jazyk], nazov_dna(_global_den.denvt));
							}
						}
						else { // default, also for JAZYK_SK
							sprintf(_global_den.meno, text_DEN_VO_VELKONOCNEJ_OKTAVE[_global_jazyk], nazov_dna(_global_den.denvt));
						}
					}
				}
			}// if (_global_den.denvr <= DRUHA_VELKONOCNA_NEDELA)
			else if (_global_den.denvr == NANEBOVSTUPENIE) {
				// _global_den.denvr == NANEBOVSTUPENIE, nanebovstupenie Pana
				_rozbor_dna_LOG("/* nanebovstupenie Pana */\n");
				_global_den = _global_r._NANEBOVSTUPENIE_PANA;
			}// if (_global_den.denvr == NANEBOVSTUPENIE)
			else {
				if (_global_den.denvr < NANEBOVSTUPENIE) {
					// velkonocne obdobie do nanebovstupenia
					_rozbor_dna_LOG("/* velkonocne obdobie do nanebovstupenia */\n");
					_global_den.litobd = OBD_VELKONOCNE_I;
				}
				else {
					// velkonocne obdobie po nanebovstupeni do zoslania ducha
					_rozbor_dna_LOG("/* velkonocne obdobie po nanebovstupeni do zoslania ducha */\n");
					_global_den.litobd = OBD_VELKONOCNE_II;
				}
				if (_global_den.denvt == DEN_NEDELA) {
					_rozbor_dna_LOG("/* nedela */\n");
					_global_den.smer = 2; // nedele adventné, pôstne a veľkonočné
				}// nedela
				else {
					_rozbor_dna_LOG("/* vsedne dni velkonocneho obdobia od pondelka po velkonocnej oktave az do soboty pred zoslanim ducha svateho vcitane */\n");
					_global_den.smer = 13; // všedné dni veľkonočné od pondelka po veľkonočnej oktáve až do soboty pred Zoslaním Ducha Svätého včítane
				}// nie nedela
			}// if (_global_den.denvr != NANEBOVSTUPENIE)

			// 2014-03-21: nastavenie lc_str_id pre veľkonočné obdobie
			if (_global_den.denvt == DEN_NEDELA) {
				sprintf(_global_den.lc_str_id, "%dV", _global_den.tyzden);
			}
			else {
				sprintf(_global_den.lc_str_id, "%dV%d", _global_den.tyzden, _global_den.denvt);
			}
		}// if (_global_den.denvr >= VELKONOCNA_NEDELA)
		else if (_global_den.denvr > ZOSLANIE_DUCHA_SV) {
			// obdobie cez rok po velkej noci a dalej (advent, vianocne obdobie do 31.12.)
			_rozbor_dna_LOG("/* obdobie cez rok po velkej noci a dalej (advent, vianocne obdobie do 31.12.) */\n");
			if (_global_den.denvr < PRVA_ADVENTNA_NEDELA) {
				// obdobie cez rok po velkej noci do prvej adventnej nedele
				_rozbor_dna_LOG("/* obdobie cez rok po velkej noci do prvej adventnej nedele */\n");
				_global_den.farba = LIT_FARBA_ZELENA;
				_global_den.kalendar = KALENDAR_VSEOBECNY;
				_global_den.litobd = OBD_CEZ_ROK;
				// urcim tyzden v obdobi "cez rok"
				_global_den.tyzden = POCET_NEDIEL_CEZ_ROK -
					((PRVA_ADVENTNA_NEDELA - _global_den.denvr - 1) DIV 7);
				_rozbor_dna_LOG("/* %d. tyzden v obdobi cez rok */\n", _global_den.tyzden);

				// slávnosť najsv. Kristovho tela a krvi predsunutá pred rozhodovanie, či je nedeľa (pretože v niektorých krajinách nie je ZOSLANIE_DUCHA_SV + 11 (teda vo štvrtok), ale presúva sa na nedeľu)
				if (_global_den.denvr == TELAKRVI) {
					// najsv. Kristovho tela a krvi == ZOSLANIE_DUCHA_SV + 11
					_rozbor_dna_LOG("/* najsv. krist. tela a krvi */\n");
					_global_den.farba = LIT_FARBA_BIELA;
					_set_slavenie_typslav_smer(0, SLAV_SLAVNOST, 3); // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
					_global_den.prik = PRIKAZANY_SVIATOK;
					mystrcpy(_global_den.meno, text_NAJSV_KRISTOVHO_TELA_A_KRVI[_global_jazyk], MENO_SVIATKU);
					mystrcpy(_global_den.lc_str_id, "9V4", MAX_LC_STR_ID);
				}// TELAKRVI
				else if (_global_den.denvt == DEN_NEDELA) {
					// i.-ta nedela v obdobi cez rok
					_rozbor_dna_LOG("/* nedela v ocr */\n");
					if (_global_den.denvr == TROJICA) {
						// najsv. trojice == ZOSLANIE_DUCHA_SV + 7
						_rozbor_dna_LOG("/* najsv. trojice */\n");
						_global_den.farba = LIT_FARBA_BIELA;
						_set_slavenie_typslav_smer(0, SLAV_SLAVNOST, 3); // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
						mystrcpy(_global_den.meno, text_NAJSVATEJSEJ_TROJICE[_global_jazyk], MENO_SVIATKU);
						mystrcpy(_global_den.lc_str_id, "9V", MAX_LC_STR_ID);
					}
					else if (_global_den.tyzden == KRISTA_KRALA) {
						// krista krala
						_rozbor_dna_LOG("/* krista krala */\n");
						_global_den.farba = LIT_FARBA_BIELA;
						_set_slavenie_typslav_smer(0, SLAV_SLAVNOST, 3); // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
						mystrcpy(_global_den.meno, text_KRISTA_KRALA[_global_jazyk], MENO_SVIATKU);
						// _global_den.lc_str_id je nastavené nižšie, štandardne
					}
					// pre redemptoristov: 3. nedeľa v júli
					else if ((((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_CSSR)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_CSSR))) && (_global_den.mesiac - 1 == MES_JUL) && (_global_den.den > 14) && (_global_den.den <= 21)) {
						// pre redemptoristov: 3. nedeľa v júli
						_rozbor_dna_LOG("/* pre redemptoristov: 3. nedeľa v júli */\n");
						_global_den.farba = LIT_FARBA_BIELA;
						_set_slavenie_typslav_smer(0, SLAV_SLAVNOST, 3); // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
						mystrcpy(_global_den.meno, text_CSSR_TITUL_KONGREGACIE[_global_jazyk], MENO_SVIATKU);
						_global_den.kalendar = _global_kalendar;
					}// kalendár pre KALENDAR_SK_CSSR a KALENDAR_CZ_CSSR
					else {
						_global_den.smer = 6; // nedele cezročné (a vianočné)
					}
				}// DEN_NEDELA
				else {
					// den v i.-tom tyzdni obdobia cez rok
					_rozbor_dna_LOG("/* den v %d. tyzdni obdobia cez rok */\n", _global_den.tyzden);

					if (_global_den.denvr == MARIE_MATKY_CIRKVI) {
						// MARIE_MATKY_CIRKVI (ZOSLANIE_DUCHA_SV + 1)
						_global_den.farba = LIT_FARBA_BIELA;
						_rozbor_dna_LOG("/* P. Márie Matky Cirkvi */\n");

						_set_slavenie_typslav_smer(0, SLAV_SPOMIENKA, 10); // povinné spomienky podľa všeobecného kalendára
						
						mystrcpy(_global_den.meno, text_MARIE_MATKY_CIRKVI[_global_jazyk], MENO_SVIATKU);

						_global_den.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
						Log("setting _global_opt[OPT_3_SPOLOCNA_CAST]...\n");
						_global_opt[OPT_3_SPOLOCNA_CAST] = MODL_SPOL_CAST_PANNA_MARIA;

						/*
						// pôvodne tradične slávené ako Svätodušný pondelok -- kvôli liturgickým čítaniam
						mystrcpy(_global_den.lc_str_id, "8V1", MAX_LC_STR_ID);
						_global_den.smer = 13; // všedné dni cezročné
						_rozbor_dna_LOG("-- všedné dni cezročné -- Svätodušný pondelok --\n");
						*/
					}
					else if (_global_den.denvr == SRDCA) {
						// srdca jezisovho == ZOSLANIE_DUCHA_SV + 19
						_rozbor_dna_LOG("/* srdca jezisovho */\n");
						_global_den.farba = LIT_FARBA_BIELA;
						_set_slavenie_typslav_smer(0, SLAV_SLAVNOST, 3); // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
						mystrcpy(_global_den.meno, text_NAJSV_SRDCA_JEZISOVHO[_global_jazyk], MENO_SVIATKU);
						mystrcpy(_global_den.lc_str_id, "10V5", MAX_LC_STR_ID);
					}
					else if (_global_den.denvr == KRISTA_KNAZA) {
						// KRISTA_KNAZA (ZOSLANIE_DUCHA_SV + 4) = Thursday after Lent
						_global_den.farba = LIT_FARBA_BIELA;
						_rozbor_dna_LOG("/* Krista kňaza */\n");
						_set_slavenie_typslav_smer(0, SLAV_SVIATOK, 5); // sviatky Pána uvedené vo všeobecnom kalendári
						mystrcpy(_global_den.meno, text_NPJK_NAJ_KNAZA[_global_jazyk], MENO_SVIATKU);
					}
					else if (_global_den.denvr == SRDPM) {
						// srdca prebl. panny marie == ZOSLANIE_DUCHA_SV + 20
						_global_den.farba = LIT_FARBA_BIELA;
						_rozbor_dna_LOG("/* srdca prebl. panny marie */\n");

						_set_slavenie_typslav_smer(0, SLAV_SPOMIENKA, 10); // povinné spomienky podľa všeobecného kalendára

						if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)) {
							_global_den.kalendar = KALENDAR_SK_OFM;
							_global_den.typslav_lokal = LOKAL_SLAV_SVIATOK_OFMCAP;
							mystrcpy(_global_den.meno, text_NEPOSKVRNENEHO_SRDCA_PM_OFM[_global_jazyk], MENO_SVIATKU);
						}
						else {
							mystrcpy(_global_den.meno, text_NEPOSKVRNENEHO_SRDCA_PM[_global_jazyk], MENO_SVIATKU);
						}
						_global_den.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
						Log("setting _global_opt[OPT_3_SPOLOCNA_CAST]...\n");
						_global_opt[OPT_3_SPOLOCNA_CAST] = MODL_SPOL_CAST_PANNA_MARIA;
						// 2003-06-30: porov. pasaz venovanu srdcu pm vo funkcii dbzaltar.cpp::sviatky_svatych(); -- 2 vstupy

						// nemá popis; 2013-02-04: doplnené
						if ((_global_jazyk != JAZYK_CZ) && (_global_jazyk != JAZYK_CZ_OP)) {
							set_popis_dummy();
						}
					}
					else {
						_global_den.smer = 13; // všedné dni cezročné
						_rozbor_dna_LOG("/* všedné dni cezročné */\n");
					}
				}// všedný deň, nie nedeľa

				// 2014-03-21: nastavenie lc_str_id pre cezročné obdobie -- iba ak nebolo nastavené vyššie
				if (equals(_global_den.lc_str_id, STR_EMPTY)) {
					if (_global_den.denvt == DEN_NEDELA) {
						sprintf(_global_den.lc_str_id, "%dC", _global_den.tyzden);
					}
					else {
						sprintf(_global_den.lc_str_id, "%dC%d", _global_den.tyzden, _global_den.denvt);
					}
				}
			}// if (_global_den.denvr < PRVA_ADVENTNA_NEDELA)
			else if (_global_den.denvr >= PRVA_ADVENTNA_NEDELA) {
				// adventne obdobie resp. vianocne
				_rozbor_dna_LOG("/* adventne obdobie resp. vianocne */\n");

				if (_global_den.denvr < NARODENIE_PANA) {
					// adventne obdobie
					_rozbor_dna_LOG("/* adventne obdobie */\n");
					_global_den.farba = LIT_FARBA_FIALOVA;
					_global_den.kalendar = KALENDAR_VSEOBECNY;
					_global_den.tyzden = ((_global_den.denvr - PRVA_ADVENTNA_NEDELA) DIV 7) + 1;
					if (_global_den.denvr <= DECEMBER_16) {
						// do 16. decembra
						_rozbor_dna_LOG("/* do 16. decembra */\n");
						_global_den.litobd = OBD_ADVENTNE_I;
						if (_global_den.denvt == DEN_NEDELA) {
							_global_den.smer = 2; // nedele adventné, pôstne a veľkonočné
							_rozbor_dna_LOG("/* nedela */\n");
							sprintf(_global_den.lc_str_id, "%dA", _global_den.tyzden);
						}
						else {
							_global_den.smer = 13; // všedné dni adventné do 16. decembra
							_rozbor_dna_LOG("/* vsedny den */\n");
							sprintf(_global_den.lc_str_id, "%dA%d", _global_den.tyzden, _global_den.denvt);
						}
					}
					else {
						// po 16. decembri
						_rozbor_dna_LOG("/* po 16. decembri */\n");
						_global_den.litobd = OBD_ADVENTNE_II;
						if (_global_den.denvt == DEN_NEDELA) {
							_global_den.smer = 2; // nedele adventné, pôstne a veľkonočné
							_rozbor_dna_LOG("/* nedela */\n");
							sprintf(_global_den.lc_str_id, "%dA", _global_den.tyzden);
						}
						else {
							_global_den.smer = 9; // všedné dni adventné od 17. do 24. decembra
							_rozbor_dna_LOG("/* vsedny den od 17. do 24. decembra vratane */\n");
							sprintf(_global_den.lc_str_id, "%d.%d.", _global_den.den, _global_den.mesiac);
						}
					}
					// 2006-08-22: pre 3. adventnú nedeľu je ružová farba rúcha
					if (_global_den.denvr == TRETIA_ADVENTNA_NEDELA) {
						_global_den.farba = LIT_FARBA_RUZOVA_FIALOVA;
					}
				}// if (_global_den.denvr < NARODENIE_PANA)
				else if (_global_den.denvr >= NARODENIE_PANA) {
					// vianocne obdobie
					_rozbor_dna_LOG("/* vianocne obdobie */\n");
					_global_den.farba = LIT_FARBA_BIELA;
					_global_den.kalendar = KALENDAR_VSEOBECNY;
					_global_den.litobd = OBD_OKTAVA_NARODENIA; // pretoze do 31.12.
					// 2008-01-05: podľa smerníc, č. 133, nie je 1. týždeň žaltára;  pokračuje sa v týždňoch od 1. adventnej nedele
					// upozornil Vlado Kiš (napr. 29. december 2007 al. 2012 = 4. týždeň žaltára)
					// kedysi tu bolo: _global_den.tyzden = 1; 
					// 2011-01-27: keďže sa to používa na určenie týždňa žaltára, môžeme tam pokojne dať "MOD 4", pretože "5. týždeň" nemá zmysel
					_global_den.tyzden = (((_global_den.denvr - PRVA_ADVENTNA_NEDELA) DIV 7) MOD 4) + 1;
					if (_global_den.denvr == NARODENIE_PANA) {
						// narodenie pana
						_rozbor_dna_LOG("/* narodenie pana */\n");
						_global_den.typslav = SLAV_SLAVNOST;
						_global_den.smer = 2; // narodenie pana
						_global_den.prik = PRIKAZANY_SVIATOK;
						mystrcpy(_global_den.meno, text_NARODENIE_PANA[_global_jazyk], MENO_SVIATKU);
						sprintf(_global_den.lc_str_id, "%d.%d.", _global_den.den, _global_den.mesiac);
					}
					else if (_global_den.denvr == SV_RODINY) {
						// nedela/sviatok sv. rodiny
						_rozbor_dna_LOG("/* nedela/sviatok sv. rodiny */\n");
						// ked padne NARODENIE_PANA na nedelu, sviatok sv. rodiny sa slavi 30. dec a nema prve vespery
						_global_den = _global_r._SVATEJ_RODINY;
					}
					else {
						_global_den.smer = 9; // dni v oktave narodenia pana
						_rozbor_dna_LOG("/* dni v oktave narodenia pana */\n");
						sprintf(_global_den.lc_str_id, "%d.%d.", _global_den.den, _global_den.mesiac);
					}
				}// if (_global_den.denvr >= NARODENIE_PANA)
			}// if (_global_den.denvr >= PRVA_ADVENTNA_NEDELA)
		}// if (_global_den.denvr > ZOSLANIE_DUCHA_SV)
	}// if (_global_den.denvr >= VELKONOCNA_NEDELA)

	if (_global_den.tyzzal == 0) {
		// neurčili sme týždeň v žaltári, urobíme tak teraz
		_rozbor_dna_LOG("/* neurčili sme týždeň v žaltári, urobíme tak teraz */\n");
		_rozbor_dna_LOG("/* _global_den.tyzden == %d */\n", _global_den.tyzden);
		_global_den.tyzzal = TYZZAL(_global_den.tyzden); // ((_global_den.tyzden + 3) MOD 4) + 1; // povodne tu bolo: (_global_den.tyzden - 1) MOD 4
		_rozbor_dna_LOG("tyzzal == %d\n", _global_den.tyzzal);
	}
	else {
		_rozbor_dna_LOG("/* týždeň žaltára už bol určený, tyzzal == %d */\n", _global_den.tyzzal);
	}

	_rozbor_dna_LOG("Nasleduje porovnanie so sviatkami svätých (môže ich byť viacero):\n");
	// nasleduje porovnanie so sviatkami svatych; berieme do uvahy, ze moze byt viac lubovolnych spomienok
	_rozbor_dna_LOG("_global_den.smer == %d\n", _global_den.smer);
	_rozbor_dna_LOG("_global_den.spolcast == %d\n", _global_den.spolcast);

	_rozbor_dna_LOG("spustam sviatky_svatych(%d, %d);...\n", _global_den.den, _global_den.mesiac);

	_global_pocet_svatych = sviatky_svatych(_global_den.den, _global_den.mesiac);

	_rozbor_dna_LOG("sviatky_svatych(%d, %d) skončila, výsledok: _global_pocet_svatych == %d; nasleduje rozhodovanie a kontroly...\n", _global_den.den, _global_den.mesiac, _global_pocet_svatych);

	// kontrola: ak bolo požadované väčšie číslo (poradie svätého), ako je v _global_pocet_svatych, resp. keď nie je sobota a je požadované PORADIE_PM_SOBOTA (spomienka P. Márie v sobotu)
	if ((_global_pocet_svatych == 0) && (_global_pocet_svatych < poradie_svaty) && (poradie_svaty != PORADIE_PM_SOBOTA)) {
		_rozbor_dna_LOG("returning from _rozbor_dna(), because: (_global_pocet_svatych == 0) && (_global_pocet_svatych < poradie_svaty) && (poradie_svaty != %d)\n", PORADIE_PM_SOBOTA);
		if (query_type == PRM_XML) {
			ExportXmlError((char*)html_error_saint[_global_jazyk], poradie_svaty);
		}
		else {
			ALERT;
			Export((char *)html_error_saint[_global_jazyk], poradie_svaty);
		}
		return FAILURE;
	}
	else if ((_global_pocet_svatych < poradie_svaty) && (poradie_svaty != PORADIE_PM_SOBOTA)) {
		_rozbor_dna_LOG("returning from _rozbor_dna(), because: (_global_pocet_svatych < poradie_svaty) && (poradie_svaty != %d)\n", PORADIE_PM_SOBOTA);
		if (query_type == PRM_XML) {
			ExportXmlError((char*)html_error_saints[_global_jazyk], _global_pocet_svatych, poradie_svaty);
		}
		else {
			ALERT;
			Export((char*)html_error_saints[_global_jazyk], _global_pocet_svatych, poradie_svaty);
		}
		return FAILURE;
	}
	else if ((_global_den.denvt != DEN_SOBOTA) && (poradie_svaty == PORADIE_PM_SOBOTA)) {
		_rozbor_dna_LOG("returning from _rozbor_dna(), because: (_global_den.denvt != DEN_SOBOTA) && (poradie_svaty == %d)\n", PORADIE_PM_SOBOTA);
		if (query_type == PRM_XML) {
			ExportXmlError((char*)html_error_saturday_VM[_global_jazyk], nazov_dna(_global_den.denvt));
		}
		else {
			ALERT;
			Export((char*)html_error_saturday_VM[_global_jazyk], nazov_dna(_global_den.denvt));
		}
		return FAILURE;
	}

	// ak predošlé kontroly sú OK, ideme porovnávať "dôležitosť" sviatku určeného v sviatky_svatych() s "bežným" dňom určeným vyššie
	_rozbor_dna_LOG("ak predošlé kontroly sú OK, ideme porovnávať `dôležitosť' sviatku určeného v sviatky_svatych() s `bežným' dňom určeným vyššie; _global_pocet_svatych() == %d\n", _global_pocet_svatych);
	if (_global_pocet_svatych > 0) {

		// treba pamatat na to, ze v poste sa vsetky spomienky stavaju lubovolnymi (c. 14 vseob. smernic)
		// 2012-03-21: doplnené: aj _global_svaty(i) pre i > 1 môže maž v sebe "spomienku" (miestnu), preto treba opraviť aj toto
		for (short int i = 0; i < MAX_POCET_SVATY; i++) {
			if ((_global_den.litobd == OBD_POSTNE_I) && (_global_pocet_svatych > i) &&
				(_global_svaty(i + 1).typslav == SLAV_SPOMIENKA)) {
				_rozbor_dna_LOG("je pôstne obdobie, tak mením `spomienku' na `ľubovoľnú spomienku' aj pre _global_svaty(%d)\n", i + 1);

				// 2006-01-20: doplnené, lebo nezobrazovalo tieto ľubovoľné spomienky
				if (_global_svaty(i + 1).smer < 12) {
					_set_slavenie_typslav_smer(i + 1, SLAV_LUB_SPOMIENKA, 12); // ľubovoľné spomienky
				}
			}
			else {
				_rozbor_dna_LOG("nie je pôstne obdobie, nie je potrebné meniť spomienku na ľubovoľnú spomienku (_global_svaty(%d))...\n", i + 1);
			}
		}

		short int podmienka_svaty_vedie = NIE;
		short int podmienka_svaty_vedie_pom = NIE;
		short int smer_override = 14; // undefined
		Log("_global_den.smer == %d...\n", _global_den.smer);

		for (short int i = 0; i < MAX_POCET_SVATY; i++) {

			smer_override = _global_svaty_i_smer_override(i + 1);
			Log("_global_svaty(%d).smer == %d...\n", i + 1, _global_svaty(i + 1).smer);
			Log("_global_svaty(%d).smer override == %d...\n", i + 1, smer_override);

			if ((_global_den.smer > smer_override) && !MIESTNE_SLAVENIE_LOKAL_SVATY(i + 1)) {
				podmienka_svaty_vedie = ANO;
			}
			if (_global_den.smer > smer_override) {
				podmienka_svaty_vedie_pom = ANO;
			}
		}
		Log("podmienka_svaty_vedie == %d\n", podmienka_svaty_vedie);
		Log("podmienka_svaty_vedie_pom == %d\n", podmienka_svaty_vedie_pom);

		// c. 12 v c. 59 vseob. smernic: "lubovolne spomienky, ktore sa mozu slavit aj v dnoch uvedenych pod c. 9 [...] tak isto v omsi a oficiu
		// na sposob lubovolnych spomienok mozno slavit tie povinne spomienky, ktore obcas pripadnu na vsedne dni v poste." ...
		// ... alebo c. 60: "ak na jeden den pripadnu viacere slavenia, uprednostni sa to, ktore ma v tabulke liturgickych dni vyssi stupen [t.j. .smer].
		if (((_global_den.smer == 9) && (_global_svaty(1).typslav == SLAV_LUB_SPOMIENKA)) || (podmienka_svaty_vedie == ANO)) {

			_rozbor_dna_LOG("svaty ma prednost pred dnom (SVATY_VEDIE)\n");
			_rozbor_dna_LOG("_global_den.smer == %d, _global_svaty(1).smer == %d, _global_svaty(1).prik == %d\n", _global_den.smer, _global_svaty(1).smer, _global_svaty(1).prik);

			_rozbor_dna_LOG("modlitba == %d (%s)...\n", _global_modlitba, nazov_modlitby(_global_modlitba));
			if ((_global_modlitba != MODL_NEURCENA) &&
				(
				(poradie_svaty != UNKNOWN_PORADIE_SVATEHO) ||
					((poradie_svaty == UNKNOWN_PORADIE_SVATEHO)
						// a je to alebo slávnosť, alebo sviatok Pána v Cezročnom období, ktorý padne na nedeľu (2013-02-03: opravené) -- napr. kvôli Obetovaniu Pána 2.2.2003/2014, prvé vešpery
						&& (
						(_global_svaty(1).smer < 5) ||
							((_global_svaty(1).smer == 5) && (_global_den.denvt == DEN_NEDELA) && ((_global_den.litobd == OBD_CEZ_ROK) || je_vianocne(_global_den.litobd)))
							)
						// a neplatí, že ide o MIESTNE_SLAVENIE_LOKAL_SVATY(i): nesmie prebiť všedný deň resp. nemá prebíjať "globálne" slávenie v danom kalendári
						&& !MIESTNE_SLAVENIE_LOKAL_SVATY(1)
						) // slavnosti
					)
				) {
				short int poradie_svaty_pom = 1;
				if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO) {
					poradie_svaty_pom = poradie_svaty;
				}
				_rozbor_dna_LOG("bola splnená podmienka...\n");

				_rozbor_dna_LOG("\tporadie_svaty == %d; poradie_svaty_pom == %d\n", poradie_svaty, poradie_svaty_pom);
				_rozbor_dna_LOG("\t_global_den.denvt == %d (%s), _global_den.litobd == %d (%s)...\n", _global_den.denvt, nazov_dna(_global_den.denvt), _global_den.litobd, nazov_obdobia_ext(_global_den.litobd));
				// menim, lebo svaty ma prednost
				_rozbor_dna_LOG("mením, lebo svätý `%d'/`%d' má prednosť...\n", poradie_svaty, poradie_svaty_pom);

				if (poradie_svaty_pom != PORADIE_PM_SOBOTA) {
					_rozbor_dna_LOG("\t_global_svaty(%d).smer == %d...\n", poradie_svaty_pom, _global_svaty(poradie_svaty_pom).smer);

					Log("do _global_den priraďujem _global_svaty(%d)... (`%s')\n", poradie_svaty_pom, _global_svaty(poradie_svaty_pom).meno);

					_global_den = _global_svaty(poradie_svaty_pom);

				}
				else {
					Log("do _global_den by som mal priradiť _global_pm_sobota (%d)... (`%s') -- PRESKAKUJEM, ANI DOTERAZ SA TO NEROBILO!\n", poradie_svaty_pom, _global_pm_sobota.meno);
				}
			}// koniec menenia pre _global_modlitba != MODL_NEURCENA a svaty > 0 resp. slavnost
		}
		else {
			// neuprednostnujeme svatych pred dnom
			_rozbor_dna_LOG("neuprednostňujeme svätých pred dňom (alternatíva k SVATY_VEDIE)\n");
			// 2010-10-06: upravené; v tejto vetve rozhodovania treba riešiť to, že nebola splnená vyššie uvedená novo-upravená podmienka o "prebití" nedele napr. lokálnou slávnosťou
			if (podmienka_svaty_vedie_pom == ANO) {
				_rozbor_dna_LOG("HOCI neuprednostňujeme svätých pred dňom (alternatíva k SVATY_VEDIE), keďže je tu lokálna slávnosť, ponechávame nastavené _global_pocet_svatych == %d\n", _global_pocet_svatych);
			}
			else {
				_rozbor_dna_LOG("setting _global_pocet_svatych = 0;...\n");
				_global_pocet_svatych = 0;
			}
		}
	}// (_global_pocet_svatych > 0)

	// prípadné zohľadnenie resp. ignorovanie _global_opt[OPT_3_SPOLOCNA_CAST]
	if ((_global_pocet_svatych > 0) || (poradie_svaty == PORADIE_PM_SOBOTA)) {
		// treba nastaviť podľa toho, ktorý svätý je (môže byť 0 -- MAX_POCET_SVATY) a zároveň brať do úvahy eventuálne prednastavenie od používateľa
		// doplnený case 0 vo switch-i, spôsobovalo problémy pre slávnosti, ktoré majú nastavenú spoločnú časť priamo v _global_den (napr. 15. septembra) | upozornil Vlado Kiš
		_rozbor_dna_LOG("Premenná _global_opt[OPT_3_SPOLOCNA_CAST] pred úpravou == %ld (%s)...(poradie_svaty == %d)\n", _global_opt[OPT_3_SPOLOCNA_CAST], _global_opt[OPT_3_SPOLOCNA_CAST] <= MODL_SPOL_CAST_NEBRAT ? nazov_spolc(_global_opt[OPT_3_SPOLOCNA_CAST]) : STR_EMPTY, poradie_svaty);
		switch (poradie_svaty) {
		case 0:
			sc = _decode_spol_cast(_global_den.spolcast);
			break;
		case PORADIE_PM_SOBOTA:
			sc.a1 = MODL_SPOL_CAST_NEBRAT;
			break;
		default:
			sc = _decode_spol_cast(_global_svaty(poradie_svaty).spolcast);
			break;
		} // switch(poradie_svaty)
		_rozbor_dna_LOG("\tNastavil som do premennej sc == (%d) %s, (%d) %s, (%d) %s\n", sc.a1, nazov_spolc(sc.a1), sc.a2, nazov_spolc(sc.a2), sc.a3, nazov_spolc(sc.a3));
		if (sc.a1 != MODL_SPOL_CAST_NEURCENA) {
			if (sc.a2 != MODL_SPOL_CAST_NEURCENA) {
				if (sc.a3 != MODL_SPOL_CAST_NEURCENA) {
					if ((_global_opt[OPT_3_SPOLOCNA_CAST] != (unsigned)(sc.a1))
						&& (_global_opt[OPT_3_SPOLOCNA_CAST] != (unsigned)(sc.a2))
						&& (_global_opt[OPT_3_SPOLOCNA_CAST] != (unsigned)(sc.a3))) {
						Log("setting _global_opt[OPT_3_SPOLOCNA_CAST]...\n");
						_global_opt[OPT_3_SPOLOCNA_CAST] = sc.a1; // iba ak nie je ani podľa jednej z nenullovývch, zmením
					}
				}
				else {
					if ((_global_opt[OPT_3_SPOLOCNA_CAST] != (unsigned)(sc.a1))
						&& (_global_opt[OPT_3_SPOLOCNA_CAST] != (unsigned)(sc.a2))) {
						Log("setting _global_opt[OPT_3_SPOLOCNA_CAST]...\n");
						_global_opt[OPT_3_SPOLOCNA_CAST] = sc.a1; // iba ak nie je ani podľa jednej z nenullovývch, zmením
					}
				}
			}
			else {
				if (_global_opt[OPT_3_SPOLOCNA_CAST] != (unsigned)(sc.a1)) {
					Log("setting _global_opt[OPT_3_SPOLOCNA_CAST]...\n");
					_global_opt[OPT_3_SPOLOCNA_CAST] = sc.a1; // iba ak nie je ani podľa jednej z nenullovývch, zmením
				}
			}
		}
		else {
			_rozbor_dna_LOG("\tHmmm, pre svätca nie je nastavená spoločná časť, nechávam _global_opt[OPT_3_SPOLOCNA_CAST] tak ako je...\n");
		}

		_rozbor_dna_LOG("\tNastavil som _global_opt[OPT_3_SPOLOCNA_CAST] == %ld (%s)...\n",
			_global_opt[OPT_3_SPOLOCNA_CAST],
			_global_opt[OPT_3_SPOLOCNA_CAST] <= MODL_SPOL_CAST_NEBRAT ? nazov_spolc(_global_opt[OPT_3_SPOLOCNA_CAST]) : STR_EMPTY);
	}// prípadné zohľadnenie resp. ignorovanie _global_opt[OPT_3_SPOLOCNA_CAST]

	// inicializujem spomienku panny marie v sobotu
	_rozbor_dna_LOG("inicializujem spomienku panny márie v sobotu... (realizuje sa vždy napevno)\n");
	init_global_pm_sobota(); // v liturgia.cpp
	// _rozbor_dna_LOG("init_global_pm_sobota(): _global_pm_sobota:\n"); Log(_global_pm_sobota); // pridane 27/04/2000A.D.

	_rozbor_dna_LOG("end\n", datum.den, datum.mesiac, rok, poradie_svaty);
	// export -- je inde: _export_rozbor_dna() a v _rozbor_dna_s_modlitbou();

	Log("_rozbor_dna(): 3 parametre -- returning SUCCESS...\n");
	return SUCCESS;
} // _rozbor_dna()

short int _rozbor_dna(_struct_den_mesiac datum, short int rok) {
	short int ret;
	Log("_rozbor_dna(): 2 parametre -- begin (spúšťame s tretím parametrom == UNKNOWN_PORADIE_SVATEHO [%d])\n", UNKNOWN_PORADIE_SVATEHO);
	ret = _rozbor_dna(datum, rok, UNKNOWN_PORADIE_SVATEHO);
	Log("_rozbor_dna(): 2 parametre -- returning %d\n", ret);
	return ret;
} // _rozbor_dna()

#define CASE_VERZALKY  6
#define CASE_KAPITALKY 5
#define CASE_NORMALNE  4
#define COLOR_RED      3
#define COLOR_BLACK    2

_struct_dm _local_den; // povodne lokalna premenna, do ktorej sa ukladaju info o analyzovanom dni
// liturgical colors - due to XML export must be global variables
short int liturgicka_farba = LIT_FARBA_NEURCENA;
short int liturgicka_farba_alt = LIT_FARBA_NEURCENA;
short int export_farby = ANO;

// vstup: typ (o aky sposob vypisu ide)
//        poradie_svateho
//        modlitba
//        aj_citanie -- či prilepiť odkaz na liturgické čítanie
//
// vystup: do _global_string da string (spolu s HTML tagmi) s nazvom slavenia;
//
// navratova hodnota: SUCCESS/FAILURE
short int init_global_string(short int typ, short int poradie_svateho, short int modlitba, short int aj_citanie = NIE) {
	_INIT_DM(_local_den);

	char pom[MAX_STR], pom2[MAX_STR], pom3[SMALL];
	char popisok_lokal[MAX_STR];
	char popisok_kalendar[MAX_STR];
	mystrcpy(pom, STR_EMPTY, MAX_STR); mystrcpy(pom2, STR_EMPTY, MAX_STR); mystrcpy(pom3, STR_EMPTY, SMALL);
	mystrcpy(popisok_lokal, STR_EMPTY, MAX_STR);
	mystrcpy(popisok_kalendar, STR_EMPTY, MAX_STR);

	char _local_string[MAX_GLOBAL_STR];
	mystrcpy(_local_string, STR_EMPTY, MAX_GLOBAL_STR);

	mystrcpy(_global_string, STR_EMPTY, MAX_GLOBAL_STR);
	mystrcpy(_global_string2, STR_EMPTY, MAX_GLOBAL_STR2);
	mystrcpy(_global_string_farba, STR_EMPTY, MAX_GLOBAL_STR_FARBA);
	mystrcpy(_global_string_modlitba, STR_EMPTY, SMALL);
	mystrcpy(_global_string_podnadpis, STR_EMPTY, SMALL);

	short int farba = COLOR_BLACK;
	short int velkost = CASE_NORMALNE;
	short int obyc = NIE;

	short int html_span_bold_it = NIE;
	short int html_span_bold = NIE;
	short int html_span_red_title_append = NIE;
	short int html_span_capitalization = NIE;
#ifdef LITURGICKE_CITANIA_ANDROID
	struct citanie *cit = NULL;
#endif // LITURGICKE_CITANIA_ANDROID

	// these variables moved to be global due to XML export -- method xml_export_liturgicka_farba()
	liturgicka_farba = LIT_FARBA_NEURCENA;
	liturgicka_farba_alt = LIT_FARBA_NEURCENA;
	export_farby = ANO;

	Log("-- init_global_string(EXPORT_DNA_%d, %d, %s, %d) -- začiatok\n", typ, poradie_svateho, nazov_modlitby(modlitba), aj_citanie);
	Log("   (inicializuje všetky _global_string* premenné)\n");

	// ____________________________________________________________
	// initialization of _global_string

	// --------------------------------------------------------------------
	// najprv priradime do _local_den to, co tam ma byt

	Log("poradie_svateho == %d\n", poradie_svateho);
	// sviatky (spomienky, ls) svatych

	if (poradie_svateho == PORADIE_PM_SOBOTA) {
		// do _local_den priradim slavenie pm v sobotu v dalsom
		if (_global_den.denvt != DEN_SOBOTA) {
			Log("Tento den nie je sobota, preto nemoze mat spomienku P. Marie v sobotu!\n");
			if (query_type == PRM_XML) {
				ExportXmlError((char*)html_error_saturday_VM[_global_jazyk], nazov_dna(_global_den.denvt));
			}
			else {
				ALERT;
				Export((char*)html_error_saturday_VM[_global_jazyk], nazov_dna(_global_den.denvt));
			}
			return FAILURE;
		}
		else {
			// do _local_den priradim dane slavenie
			_local_den = _global_pm_sobota;
			Log("priradujem _local_den = _global_pm_sobota;\n");
		}
	}// poradie_svateho == PORADIE_PM_SOBOTA
	else if (JE_PORADIE_SVATY_OK(poradie_svateho)) {
		if (_global_pocet_svatych > poradie_svateho - 1) {
			// do _local_den priradim dane slavenie
			_local_den = _global_svaty(poradie_svateho);
#ifdef LITURGICKE_CITANIA_ANDROID
			cit = najdiCitanie(getCode(&_global_svaty(poradie_svateho)));
#endif // LITURGICKE_CITANIA_ANDROID
			Log("priradujem _local_den = _global_svaty(%d);\n", poradie_svateho);
		}
		else {
			// sice chce svateho c. 'poradie_svateho', ale máme ich menej
			Log("-- Error: _global_svaty(%d) not assigned (init_global_string)\n", poradie_svateho);
			ALERT;
			sprintf(pom, "Error: _global_svaty(%d) not assigned (init_global_string)", poradie_svateho);
			strcat(_local_string, pom);
			Export("%s\n", _local_string);
			return FAILURE;
		}
	}// poradie_svateho = 1, 2, 3... až MAX_POCET_SVATY
	else if (poradie_svateho > PORADIE_PM_SOBOTA) {
		Log("-- Error/init_global_string: poradie_svateho == %d (max.: %d)\n", poradie_svateho, PORADIE_PM_SOBOTA);
		ALERT;
		Export("Error/init_global_string: poradie_svateho == %d (max.: %d)\n", poradie_svateho, PORADIE_PM_SOBOTA);
		return FAILURE;
	}// poradie_svateho > PORADIE_PM_SOBOTA
	else {
		// poradie_svateho == UNKNOWN_PORADIE_SVATEHO
		// odvetvené kvôli tým prípadom, keď na nedeľu padne sviatok pána, ale používa sa poradie_svaty == UNKNOWN_PORADIE_SVATEHO == 0 
		// časť prevzatá z: liturgicke_obdobie(), začiatok funkcie; hoci tu sa použije len pre smer == 5 (sviatky pána); slávnosti sa riešia samostatne
		Log("_global_den.smer == %d\n", _global_den.smer);
		Log("_global_svaty(1).smer == %d\n", _global_svaty(1).smer);
		// presunuté do #define PODMIENKA_SVIATKY_PANA_SVATYCH_PREDNOST_PRED_NEDELOU_OCR | sviatky Pána a svätých, ktoré majú prednosť pred Cezročnou nedeľou a majú (ak padnú na nedeľu) svoje vlastné prvé vešpery
		if ((_global_svaty(1).smer == 5) && (PODMIENKA_SVIATKY_PANA_SVATYCH_PREDNOST_PRED_NEDELOU_OCR)) {
			// do _local_den priradim dane slavenie
			_local_den = _global_svaty(1);
#ifdef LITURGICKE_CITANIA_ANDROID
			cit = najdiCitanie(getCode(&_global_svaty(1)));
#endif // LITURGICKE_CITANIA_ANDROID
			Log("priradujem _local_den = _global_svaty(1);\n");
		}
		else {
			// bezny den
			Log("/* bezny den */\n");
			obyc = ANO;
			_local_den = _global_den;
		}
	}// poradie_svateho == UNKNOWN_PORADIE_SVATEHO

	int ma_nazov = 0;
#ifdef LITURGICKE_CITANIA_ANDROID
	if (!cit) {
		Log("nepodarilo sa načítať cit, preto použijem default...\n");
		cit = najdiCitanie(getCode(&_global_den));
		if (!cit) {
			Log("nepodarilo sa načítať ani len default pre cit.\n");
		}// if (!cit); 2. pokus
	}// if (!cit)
#endif // LITURGICKE_CITANIA_ANDROID

	Log("1:_local_den.meno == %s\n", _local_den.meno);

	// spomienka panny márie v sobotu
	// este spomienka panny marie v sobotu, cl. 15
	// pridané posv. čítania a upravené; keďže smer == 11 používame pre lokálne povinné spomienky, upravili sme kontrolu z 12 na 11
	// porovnávame klasicky, resp. špeciálne pre body 4, 8, 11 [Miestne slávnosti, Miestne sviatky, Miestne povinné spomienky] pred touto úpravou tu bola kontrola (_global_svaty(1).smer >= 11)
	// MIESTNE_SLAVENIE_LOKAL_SVATY(i) použité pre lokálne slávenia, aby sa zjednodušila podmienka
	if ((_global_den.litobd == OBD_CEZ_ROK) &&
		(_global_den.denvt == DEN_SOBOTA) &&
		(
		((_global_den.smer >= 11) && (_global_pocet_svatych == 0)) ||
			(((_global_svaty(1).smer >= 12) || MIESTNE_SLAVENIE_LOKAL_SVATY(1)) && (_global_pocet_svatych > 0))) &&
			(poradie_svateho == PORADIE_PM_SOBOTA)) {
		// teraz do _global_den priradim dane slavenie
		_local_den = _global_pm_sobota;
		Log("priradujem _local_den = _global_pm_sobota;\n");
	}

	Log("2:_local_den.meno == %s\n", _local_den.meno);

	// skontrolujeme ešte pondelok -- štvrtok svätého týždňa (nastavenie názvu aj pre export na viac dní)
	if (_local_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN) {
		// aj kompletórium pre zelený štvrtok má svoj vlastný názov, tak isto ako doteraz vešpery
		if (!((_local_den.denvt == DEN_NEDELA) || ((_local_den.denvt == DEN_STVRTOK) && ((typ != EXPORT_DNA_VIAC_DNI) && ((modlitba == MODL_VESPERY) || (modlitba == MODL_KOMPLETORIUM)))))) {
			if (_global_jazyk == JAZYK_HU) {
				// pre HU sú aj dni pondelok až streda (štvrtok sa rieši inde) s vlastnými názvami
				mystrcpy(_local_den.meno, text_HU_VELKY_TYZDEN_PREFIX, MENO_SVIATKU);
				strcat(_local_den.meno, nazov_dna(_local_den.denvt));
			}// HU only
			else {
				if (_local_den.denvt == DEN_STVRTOK) {
					mystrcpy(_local_den.meno, text_ZELENY_STVRTOK[_global_jazyk], MENO_SVIATKU);
				}
				else {
					mystrcpy(_local_den.meno, nazov_dna(_local_den.denvt), MENO_SVIATKU);
					strcat(_local_den.meno, " ");
					strcat(_local_den.meno, nazov_obdobia_v(_local_den.litobd));
				}
			}
		}
		else {
			if (_local_den.denvt == DEN_STVRTOK) {
				mystrcpy(_local_den.meno, text_ZELENY_STVRTOK_VESPERY[_global_jazyk], MENO_SVIATKU);
			}
		}

		// override for BY: special naming of days in Great (Holy) Week (Mo, Tue, We)
		if ((_global_jazyk == JAZYK_BY) && ((_local_den.denvt == DEN_PONDELOK) || (_local_den.denvt == DEN_UTOROK) || (_local_den.denvt == DEN_STREDA) || (_local_den.denvt == DEN_STVRTOK))) {
			Log("special naming of days in Great (Holy) Week (Mo, Tue, We)\n");

			switch (_local_den.denvt)
			{
			case DEN_PONDELOK:
				mystrcpy(_local_den.meno, text_VELKY_PONDELOK[_global_jazyk], MENO_SVIATKU);
				break;
			case DEN_UTOROK:
				mystrcpy(_local_den.meno, text_VELKY_UTOROK[_global_jazyk], MENO_SVIATKU);
				break;
			case DEN_STREDA:
				mystrcpy(_local_den.meno, text_VELKA_STREDA[_global_jazyk], MENO_SVIATKU);
				break;
			case DEN_STVRTOK:
				mystrcpy(_local_den.meno, text_ZELENY_STVRTOK[_global_jazyk], MENO_SVIATKU);
				break;
			default:
				break;
			}
		}// if ((_global_jazyk == JAZYK_BY) && ((_local_den.denvt == DEN_PONDELOK) || (_local_den.denvt == DEN_UTOROK) || (_local_den.denvt == DEN_STREDA) || (_local_den.denvt == DEN_STVRTOK)))
	}// if (_local_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)

	Log("3:_local_den.meno == %s\n", _local_den.meno);
	// --------------------------------------------------------------------
	// teraz podla toho, co je v _local_den, vytvorime _local_string

	// capitalization?
	if ((_local_den.smer < 5) || ((_je_local_den_slavnost) && (poradie_svateho != PORADIE_PM_SOBOTA))) {
		// slávnosti
		Log("_local_den.smer < 5 or SLAV_SLAVNOST");
		velkost = CASE_VERZALKY;
	}
	else if ((_je_local_den_sviatok) && (poradie_svateho != PORADIE_PM_SOBOTA)) {
		// sviatky
		Log("SLAV_SVIATOK");
		if ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_CZ_OP) || (_global_jazyk == JAZYK_IS) || (_global_jazyk == JAZYK_SK)) {
			velkost = CASE_KAPITALKY; // use small caps
		}
		else if (_global_jazyk == JAZYK_BY) {
			velkost = CASE_VERZALKY; // use all caps
		}
	}
	else {
		velkost = CASE_NORMALNE;
	}

	// Log("3:velkost == %d", velkost);

	// red color?
	Log("_local_den.denvt == DEN_NEDELA || _local_den.prik == PRIKAZANY_SVIATOK -- ");
	if ((_local_den.denvt == DEN_NEDELA) ||
		(_local_den.prik == PRIKAZANY_SVIATOK)) {
		// prikazane sviatky a nedele
		farba = COLOR_RED;
		Log("COLOR_RED: ano\n");
	}
	else {
		Log("COLOR_RED: nie\n");
	}

	// najprv názov; ak ide o ľubovoľnú spomienku na blahoslaveného (napr. SK OP), zobrazí sa názov kurzívou
	if (_local_den.prik == VOLNA_LUBOVOLNA_SPOMIENKA) {
		html_span_bold_it = ANO;
		// mystrcpy(_local_string, "<" HTML_SPAN_BOLD_IT ">", MAX_GLOBAL_STR);
	}
	else if (typ != EXPORT_DNA_VIAC_DNI_TXT) {
		html_span_bold = ANO;
		// mystrcpy(_local_string, "<" HTML_SPAN_BOLD ">", MAX_GLOBAL_STR);
	}

	if ((farba == COLOR_RED) && (typ != EXPORT_DNA_VIAC_DNI_TXT)) {
		html_span_red_title_append = ANO;
		// strcat(_local_string, "<" HTML_SPAN_RED_TITLE ">");
	}
	Log("4:_local_den.meno == %s\n", _local_den.meno);

	if (equals(_local_den.meno, STR_EMPTY)) {
		Log("slávenie nemá vlastný názov...\n");
		if (_local_den.denvt == DEN_NEDELA) {
			Log("nedeľa, ktorá nemá vlastný názov... (_local_string == %s)\n", _local_string);
			// nedeľa bez vlastného názvu
			if (_global_jazyk == JAZYK_BY) {
				convertToRoman(_local_den.tyzden, pom2); // poradie_SLOVOM(_local_den.tyzden - 1)
				if (!((_local_den.litobd == OBD_VELKONOCNE_I) || (_local_den.litobd == OBD_VELKONOCNE_II))) {
					sprintf(pom, "%s %s %s", pom2, nazov_Dna(_local_den.denvt), nazov_obdobia_v(_local_den.litobd));
				}
				else {
					sprintf(pom, "%s %s %s", pom2, nazov_Obdobia_aka(_local_den.litobd), nazov_Dna(_local_den.denvt));
				}
			}// BY only
			else if (_global_jazyk == JAZYK_LA) {
				if (_local_den.litobd == OBD_CEZ_ROK) {
					// Dominica II per annum (LA LH, vol. III, p. 60)
					convertToRoman(_local_den.tyzden, pom2);
					sprintf(pom, "%s %s %s", nazov_Dna(_local_den.denvt), pom2, nazov_Obdobia_aka(_local_den.litobd));
				}
				else {
					// Dominica quinta Quadragesimae
					sprintf(pom, "%s %s %s", nazov_Dna(_local_den.denvt), poradie_Slovom(_local_den.tyzden - 1), nazov_Obdobia_aka(_local_den.litobd));
				}
			}// LA only
			else if (
				(_local_den.litobd == OBD_ADVENTNE_I) || (_local_den.litobd == OBD_ADVENTNE_II)
				|| (_local_den.litobd == OBD_POSTNE_I)
				|| (_local_den.litobd == OBD_VELKONOCNE_I) || (_local_den.litobd == OBD_VELKONOCNE_II)
				) {
				if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)) {
					sprintf(pom, "%s %s %s", poradie_Slovom(_local_den.tyzden - 1), nazov_Dna(_local_den.denvt), nazov_Obdobia_aka(_local_den.litobd));
				}
				else if (_global_jazyk == JAZYK_HU) {
					sprintf(pom, "%s %s %s%s", nazov_Obdobia_aka(_local_den.litobd), poradie_Slovom(_local_den.tyzden - 1), nazov_dna(_local_den.denvt), KONCOVKA_DNA_HU_SMALL);
				}
				else if (_global_jazyk == JAZYK_LA) {
					// Dominica quinta Quadragesimae
					sprintf(pom, "%s %s %s", nazov_Dna(_local_den.denvt), poradie_Slovom(_local_den.tyzden - 1), nazov_Obdobia_aka(_local_den.litobd));
				}
				else {
					// úprava názvov nedieľ v štýle "3. NEDEĽA V ADVENTNOM OBDOBÍ" -> "Tretia adventná nedeľa"
					sprintf(pom, "%s %s %s", poradie_Slovom(_local_den.tyzden - 1), nazov_Obdobia_aka(_local_den.litobd), nazov_Dna(_local_den.denvt));
				}
			}// špeciálne nedele slovom
			else {
				// _local_den.litobd == OBD_CEZ_ROK; pre cezročné ostáva poradové číslo
				if (_global_jazyk == JAZYK_HU) {
					sprintf(pom, "%s %d. %s", nazov_Obdobia_aka(_local_den.litobd), _local_den.tyzden, nazov_dna(_local_den.denvt));
				}
				else {
					sprintf(pom, "%d. %s %s", _local_den.tyzden, nazov_Dna(_local_den.denvt), nazov_obdobia_v(_local_den.litobd));
				}
			}// ostatné nedele číslom

			if (strlen(pom) > 0) {

				mystrcpy(_local_string, STR_EMPTY, MAX_GLOBAL_STR);

				if (html_span_bold_it == ANO) {
					strcat(_local_string, "<" HTML_SPAN_BOLD_IT ">");
				}
				else if (html_span_bold == ANO) {
					strcat(_local_string, "<" HTML_SPAN_BOLD ">");
				}
				if (html_span_red_title_append == ANO) {
					strcat(_local_string, "<" HTML_SPAN_RED_TITLE ">");
				}

				strcat(_local_string, "<" HTML_SPAN_UPPERCASE ">");

				strcat(_local_string, pom);

				strcat(_local_string, HTML_SPAN_END); // end of HTML_SPAN_UPPERCASE

				if (html_span_red_title_append == ANO) {
					strcat(_local_string, HTML_SPAN_END); // end of HTML_SPAN_RED_TITLE
				}
				if (html_span_bold_it == ANO) {
					strcat(_local_string, HTML_SPAN_END); // end of HTML_SPAN_BOLD_IT
				}
				else if (html_span_bold == ANO) {
					strcat(_local_string, HTML_SPAN_END); // end of HTML_SPAN_BOLD
				}

				strcat(_local_string, HTML_LINE_BREAK);
			}

			// special cases

			// ak padne toto slávenie na nedeľu, berie sa nedeľné ofícium pre Liturgiu hodín (hoci v direktóriu by malo byť uvedené, že je Všetkých zosnulých a omša je zo zosnulých)
			if (je_Spomienka_na_zosnulych_02NOV_nedela) {
				sprintf(pom, "<" HTML_SPAN_SMALL ">");
				sprintf(pom2, "(");
				strcat(pom, pom2);
				sprintf(pom2, "%s", mystr_UPPERCASE((char *)text_NOV_02[_global_jazyk]));
				strcat(pom, pom2);
				sprintf(pom2, ")");
				strcat(pom, pom2);
				strcat(pom, HTML_SPAN_END);

				strcat(_local_string, pom);

				strcat(_local_string, HTML_LINE_BREAK);
			}

			// prilepenie "týždňa žaltára" aj pre nedele
			if ((typ != EXPORT_DNA_VIAC_DNI) && (typ != EXPORT_DNA_VIAC_DNI_SIMPLE) && (typ != EXPORT_DNA_VIAC_DNI_TXT)) {
				sprintf(pom, "<" HTML_SPAN_SMALL ">");
				sprintf(pom2, html_text_tyzden_zaltara_cislo[_global_jazyk], tyzden_zaltara(_local_den.tyzden));
				strcat(pom, pom2);
				strcat(pom, HTML_SPAN_END);

				strcat(_local_string, pom);
			}

			ma_nazov = 1;
		} // nedeľa
		else { // nie nedeľa
			Log("deň iný ako nedeľa, ktorý nemá vlastný názov... (_local_string == %s)\n", _local_string);
			// doplnené zátvorky, kvôli span-ovačkám na konci
			if (obyc == ANO) {

				if ((typ != EXPORT_DNA_VIAC_DNI) && (typ != EXPORT_DNA_VIAC_DNI_SIMPLE)) {
					Log("(typ != EXPORT_DNA_VIAC_DNI) && (typ != EXPORT_DNA_VIAC_DNI_SIMPLE)\n");

					// dni po popolcovej strede na začiatku pôstneho obdobia - "nultý" týždeň pôstneho obdobia
					if ((_local_den.tyzden == 0) && (_local_den.litobd == OBD_POSTNE_I)) {
						Log("dni po popolcovej strede na začiatku pôstneho obdobia - 'nultý' týždeň pôstneho obdobia\n");

						if (typ != EXPORT_DNA_VIAC_DNI_TXT) {
							sprintf(pom2, HTML_SPAN_END "" HTML_LINE_BREAK "<" HTML_SPAN_SMALL ">");
						}
						else {
							mystrcpy(pom2, STR_EMPTY, MAX_STR);
						}
						sprintf(pom, "%s %s, %s", nazov_Dna(_local_den.denvt), (char *)text_PO_POPOLCOVEJ_STREDE[_global_jazyk], nazov_obdobia(_local_den.litobd));
						strcat(pom, pom2);
						if (typ != EXPORT_DNA_VIAC_DNI_TXT) {
							sprintf(pom2, html_text_tyzden_zaltara_cislo[_global_jazyk], tyzden_zaltara(_local_den.tyzden));
							strcat(pom, pom2);
						}
					}// ((_local_den.tyzden == 0) && (_local_den.litobd == OBD_POSTNE_I))

					// dni po narodení pána pred nedeľou v oktáve narodenia pána (ak je) majú žaltár zo 4. týždňa
					else if (_local_den.litobd == OBD_OKTAVA_NARODENIA) {
						Log("_local_den.litobd == OBD_OKTAVA_NARODENIA\n");
						if (typ != EXPORT_DNA_VIAC_DNI_TXT) {
							sprintf(pom2, HTML_SPAN_END "" HTML_LINE_BREAK "<" HTML_SPAN_SMALL ">");
						}
						else {
							mystrcpy(pom2, STR_EMPTY, MAX_STR);
						}
						if (_global_jazyk == JAZYK_HU) {
							sprintf(pom, "%s alatti %d. nap", (char *)text_V_OKTAVE_NARODENIA[_global_jazyk], (_local_den.den - 24));
						}
						else {
							sprintf(pom, "%s %s", nazov_Dna(_local_den.denvt), (char *)text_V_OKTAVE_NARODENIA[_global_jazyk]);
						}
						strcat(pom, pom2);
						if (typ != EXPORT_DNA_VIAC_DNI_TXT) {
							sprintf(pom2, html_text_tyzden_zaltara_cislo[_global_jazyk], tyzden_zaltara(_local_den.tyzden));
							strcat(pom, pom2);
						}
					}// (_local_den.litobd == OBD_OKTAVA_NARODENIA)

					// dni 17.-23. decembra (obdobie OBD_ADVENTNE_II)
					else if ((_local_den.litobd == OBD_ADVENTNE_II) && (typ != EXPORT_DNA_VIAC_DNI)) {
						Log("(_local_den.litobd == OBD_ADVENTNE_II) && (typ != EXPORT_DNA_VIAC_DNI)\n");

						// najprv názov dňa (pondelok, utorok...)...
						sprintf(pom, "%s, ", nazov_Dna(_local_den.denvt));

						// ...potom dátum + genitív mesiaca... | ale iba v takom prípade, že mesiac je december (pre použitie "liturgické obdobie" je dátum neinicializovaný, teda 1. januára)
						if ((_local_den.mesiac == MES_DEC) && (_local_den.den >= 16) && (_local_den.den <= 24)) {
							mystrcpy(pom2, _vytvor_string_z_datumu(_local_den.den, _local_den.mesiac, _local_den.rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN) || (_global_jazyk == JAZYK_HU)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_GEN, NIE), MAX_STR);
							strcat(pom, pom2);
							mystrcpy(pom2, ", ", MAX_STR);
							strcat(pom, pom2);
						}

						// ...liturgické obdobie (adventné)...
						sprintf(pom2, "%s, ", nazov_obdobia(_local_den.litobd));
						strcat(pom, pom2);

						// ...a napokon týždeň žaltára
						if (typ != EXPORT_DNA_VIAC_DNI_TXT) {
							sprintf(pom2, HTML_SPAN_END);
						}
						else {
							mystrcpy(pom2, STR_EMPTY, MAX_STR);
						}
						strcat(pom, pom2);
						sprintf(pom2, html_text_tyzden_cislo[_global_jazyk], _local_den.tyzden);
						strcat(pom, pom2);
						if (typ != EXPORT_DNA_VIAC_DNI_TXT) {
							sprintf(pom2, HTML_LINE_BREAK "<" HTML_SPAN_SMALL ">");
						}
						else {
							mystrcpy(pom2, STR_EMPTY, MAX_STR);
						}
						strcat(pom, pom2);
						if (typ != EXPORT_DNA_VIAC_DNI_TXT) {
							sprintf(pom2, html_text_tyzden_zaltara_cislo[_global_jazyk], tyzden_zaltara(_local_den.tyzden));
							strcat(pom, pom2);
						}
					}// ((_local_den.litobd == OBD_ADVENTNE_II) && (typ != EXPORT_DNA_VIAC_DNI))

					else {
						Log("else...\n");
						if (typ != EXPORT_DNA_VIAC_DNI_TXT) {
							sprintf(pom2, HTML_SPAN_END);
						}
						else {
							mystrcpy(pom2, STR_EMPTY, MAX_STR);
						}
						sprintf(pom, "%s, %s, ", nazov_Dna(_local_den.denvt), nazov_obdobia(_local_den.litobd));
						sprintf(pom3, html_text_tyzden_cislo[_global_jazyk], _local_den.tyzden);
						strcat(pom, pom3);
						strcat(pom, pom2);
						if (typ != EXPORT_DNA_VIAC_DNI_TXT) {
							sprintf(pom2, HTML_LINE_BREAK "<" HTML_SPAN_SMALL ">");
							sprintf(pom3, html_text_tyzden_zaltara_cislo[_global_jazyk], tyzden_zaltara(_local_den.tyzden));
							strcat(pom2, pom3);
							strcat(pom, pom2);
						}
					}// default, cezročné obdobie a ostatné "obyčajné" dni

					ma_nazov = 1;
				}// nie export na viac dní

				if (typ == EXPORT_DNA_VIAC_DNI_SIMPLE) {
					sprintf(pom, "%s, %s" HTML_SPAN_END ", ", nazov_Dna(_local_den.denvt), nazov_obdobia(_local_den.litobd));
					sprintf(pom2, html_text_tyzden_zaltara_cislo[_global_jazyk], _local_den.tyzden);
					strcat(pom, pom2);

					ma_nazov = 1;
				}
				// inak ostane string prazdny | otherwise leaves pom empty (thus, ma_nazov == 0)

				if (ma_nazov == 1) {
					if (html_span_bold_it == ANO) {
						mystrcpy(_local_string, "<" HTML_SPAN_BOLD_IT ">", MAX_GLOBAL_STR);
					}
					else if (html_span_bold == ANO) {
						mystrcpy(_local_string, "<" HTML_SPAN_BOLD ">", MAX_GLOBAL_STR);
					}
					if (html_span_red_title_append == ANO) {
						strcat(_local_string, "<" HTML_SPAN_RED_TITLE ">");
					}

					strcat(_local_string, pom);

					if (html_span_red_title_append == ANO) {
						strcat(_local_string, HTML_SPAN_END);
					}
					if (html_span_bold_it == ANO) {
						strcat(_local_string, HTML_SPAN_END);
					}
					else if (html_span_bold == ANO) {
						strcat(_local_string, HTML_SPAN_END);
					}
				}
			}
			else {
				Log("-- Error: _local_den.meno == \"\", avsak obyc != ANO\n");
			}
		}// nie je to nedeľa, teda iba obyčajný deň, ktorý nemá vlastný názov
	}// if (equals(_local_den.meno, STR_EMPTY))
	else {
		Log("pridávam vlastný názov...\n");
		// vlastny nazov | proper celebration's name; respecting selected 'case' style
		if (_local_den.denvt == DEN_NEDELA) {
			// nedela co ma vlastny nazov | Sunday with proper name
			strcat(pom, mystr_UPPERCASE(_local_den.meno));
		}
		else if (velkost == CASE_VERZALKY) {
			// STACK OVERFLOW | uppercase
			strcat(pom, mystr_UPPERCASE(_local_den.meno));
		}
		else {
			if (velkost == CASE_KAPITALKY) {
				// Sᴛᴀᴄᴋ Oᴠᴇʀғʟᴏᴡ | small case
				strcat(pom, "<" HTML_SPAN_SMALLCAPS ">");
			}

			// Stack Overflow | normal
			strcat(pom, _local_den.meno);

			if (velkost == CASE_KAPITALKY) {
				strcat(pom, HTML_SPAN_END);
			}
		}
		ma_nazov = 1;

		if (strlen(pom) > 0) {
			if (html_span_bold_it == ANO) {
				mystrcpy(_local_string, "<" HTML_SPAN_BOLD_IT ">", MAX_GLOBAL_STR);
			}
			else if (html_span_bold == ANO) {
				mystrcpy(_local_string, "<" HTML_SPAN_BOLD ">", MAX_GLOBAL_STR);
			}
			if (html_span_red_title_append == ANO) {
				strcat(_local_string, "<" HTML_SPAN_RED_TITLE ">");
			}

			strcat(_local_string, pom);

			if (html_span_red_title_append == ANO) {
				strcat(_local_string, HTML_SPAN_END);
			}
			if (html_span_bold_it == ANO) {
				strcat(_local_string, HTML_SPAN_END);
			}
			else if (html_span_bold == ANO) {
				strcat(_local_string, HTML_SPAN_END);
			}
		}
	}// _local_den.meno != STR_EMPTY

	// teraz typ slávenia; nevypisuje sa, ak ide o ľubovoľnú spomienku na blahoslaveného (napr. SK OP), kedy sa zobrazí názov kurzívou
	if ((_local_den.typslav != SLAV_NEURCENE) && (_local_den.typslav != SLAV_VLASTNE) && ((_local_den.prik != VOLNA_LUBOVOLNA_SPOMIENKA) /* || (typ != EXPORT_DNA_VIAC_DNI) */)) {
		// možnosť zalomenia (Igor Galád)
		if (typ != EXPORT_DNA_VIAC_DNI_TXT) {
#define TYPSLAV_NOVY_RIADOK
#if defined(TYPSLAV_NOVY_RIADOK_CIARKA)
			sprintf(pom, ", " HTML_LINE_BREAK);
#elif defined(TYPSLAV_NOVY_RIADOK)
			sprintf(pom, " " HTML_LINE_BREAK);
#else
			sprintf(pom, ", ");
#endif
		}
		else {
			sprintf(pom, ", ");
		}
		strcat(_local_string, pom);

		if (typ != EXPORT_DNA_VIAC_DNI_TXT) {
			sprintf(pom, "<" HTML_SPAN_RED_TITLE ">");
		}
		else {
			mystrcpy(pom, STR_EMPTY, MAX_STR);
		}

		if (_global_jazyk == JAZYK_CZ_OP) {
			// for CZ OP, also the celebration's name is for "svátek" in small caps

			// respect CASE_ of celebration proper name
			if (velkost == CASE_VERZALKY) {
				html_span_capitalization = ANO;
				sprintf(pom2, "<" HTML_SPAN_UPPERCASE ">");
			}
			else if (velkost == CASE_KAPITALKY) {
				html_span_capitalization = ANO;
				sprintf(pom2, "<" HTML_SPAN_SMALLCAPS ">");
			}

			if (html_span_capitalization == ANO) {
				strcat(pom, pom2);
			}
		}

		// pre spomienku na privilegované dni (VSLH č. 238-239) sa exportuje iný názov slávenia
		if ((_local_den.typslav == SLAV_LUB_SPOMIENKA) && (je_privileg)) {
			sprintf(pom2, "%s", nazov_slavenia_na_spomienku_jazyk[_global_jazyk]);
		}
		else {
			if ((_local_den.typslav != SLAV_VLASTNE) && (_local_den.typslav != SLAV_NEURCENE)) {
				sprintf(pom2, "%s", nazov_slavenia(_local_den.typslav));
			}
			// v podstate netreba túto podmienku, lebo je to vylúčené už vyššie
			else {
				sprintf(pom2, "%s", (char *)STR_EMPTY);
			}
		}

		strcat(pom, pom2);

		// celebration level override
		if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OVERRIDE_STUP_SLAV) && (_typslav_override(_local_den.typslav) < _local_den.typslav) && (poradie_svateho != PORADIE_PM_SOBOTA)) {
			sprintf(pom2, " – %s", (_typslav_override(_local_den.typslav) == SLAV_SLAVNOST) ? html_text_opt_1_slavit_ako_slavnost[_global_jazyk] : html_text_opt_1_slavit_ako_sviatok[_global_jazyk]);

			strcat(pom, pom2);
		}

		if (html_span_capitalization == ANO) {
			strcat(pom, HTML_SPAN_END);
		}

		if (typ != EXPORT_DNA_VIAC_DNI_TXT) {
			strcat(pom, HTML_SPAN_END);
		}

		Log("pridávam typ slávenia: %s\n", pom);

		strcat(_local_string, pom);
	}

	if (typ != EXPORT_DNA_VIAC_DNI_TXT) {
		// condition to display calendar info in prayer subtitle: either condition PODMIENKA_EXPORTOVAT_KALENDAR holds (and calendar is not default national calendar) or explicitly requested
		if (((PODMIENKA_EXPORTOVAT_KALENDAR) && (_local_den.kalendar != default_kalendar[_global_jazyk])) || (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_SHOW_DEFAULT_CALENDAR))) {
			mystrcpy(popisok_kalendar, nazov_kalendara_long[_local_den.kalendar], MAX_STR);
			Log("podmienka OK, popisok_kalendar == %s (_local_den.kalendar == %d)\n", popisok_kalendar, _local_den.kalendar);
		}// otherwise empty

		mystrcpy(popisok_lokal, STR_EMPTY, MAX_STR);
		// teraz lokalizácia slavenia resp. poznámku o lokálnom kalendári
		if (_local_den.typslav_lokal != LOKAL_SLAV_NEURCENE) {
			mystrcpy(popisok_lokal, NAZOV_SLAVENIA_LOKAL_LOCAL_DEN_TYPSLAV_LOKAL, MAX_STR);
		}

		long strlen_popisok_kalendar = 0, strlen_popisok_lokal = 0;
		strlen_popisok_kalendar = strlen(popisok_kalendar);
		strlen_popisok_lokal = strlen(popisok_lokal);

		if (strlen_popisok_kalendar + strlen_popisok_lokal > 0) {
			if ((strlen_popisok_kalendar > 0) && (strlen_popisok_lokal > 0)) {
				// before both strings were in parentheses respectively divided by STR_VERTICAL_BAR_WITH_SPACES
				strcat(popisok_kalendar, STR_SPACE);
			}

			sprintf(pom, "\n" HTML_LINE_BREAK "<" HTML_SPAN_RED_SUBTITLE ">");

			if (strlen_popisok_kalendar > 0) {
				strcat(pom, popisok_kalendar);
			}
			if (strlen_popisok_lokal > 0) {
				strcat(pom, "(");
				strcat(pom, popisok_lokal);
				strcat(pom, ")");
			}

			strcat(pom, HTML_SPAN_END "\n");

			Log("pridávam lokalizáciu slávenia resp. poznámku o lokálnom kalendári: %s\n", pom);
			strcat(_local_string, pom);
		}

#ifdef OS_Windows_Ruby
		if (typ != EXPORT_DNA_XML) {
			// typ kalendára ako poznámka
			if ((_local_den.kalendar >= KALENDAR_NEURCENY) && (_local_den.kalendar <= POCET_KALENDAROV)) {
				sprintf(pom, "<!-- kalendár: %s -->", nazov_kalendara_short[_local_den.kalendar]);
				Log("pridávam ako poznámku typ kalendára: %s\n", pom);
				strcat(_local_string, pom);
			}
			else {
				sprintf(pom, "<!-- kalendár nie je určený správne -->");
				strcat(_local_string, pom);
			}
		}
#endif

		// odkaz na liturgické čítanie sa doplní, iba ak je aj_citanie == ANO
		if ((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_CITANIA)) && aj_citanie) {
#ifdef LITURGICKE_CITANIA_ANDROID
			if (cit && aj_citanie && su_liturgicke_citania_offline) {
				if (typ == EXPORT_DNA_DNES || typ == EXPORT_DNA_JEDEN_DEN || typ == EXPORT_DNA_VIAC_DNI) {
					if (ma_nazov) {
						strcat(_local_string, HTML_LINE_BREAK);
					}
					sprintf(pom, HTML_A_HREF_BEGIN "\"svpismo://svpismo.riso.ksp.sk/?d=%d&amp;m=%d&amp;y=%d&amp;c=", _local_den.den, _local_den.mesiac, _local_den.rok);
					strcat(_local_string, pom);
					strcat(_local_string, StringEncode(cit->citania));
					sprintf(pom, "&amp;zalm=");
					strcat(_local_string, pom);
					strcat(_local_string, StringEncode(cit->zalm));
					//
					sprintf(pom, "&amp;aleluja=");
					strcat(_local_string, pom);
					strcat(_local_string, StringEncode(cit->aleluja));
					sprintf(pom, "\">%s" HTML_A_END, HtmlEncode(cit->citania));
					strcat(_local_string, pom);
				}
			}// if (cit && aj_citanie && su_liturgicke_citania_offline)
#elif defined(BEHAVIOUR_WEB)
			sprintf(pom, HTML_LINE_BREAK "<" HTML_SPAN_SMALLCAPS ">" HTML_A_HREF_BEGIN "\"");
			strcat(_local_string, pom);

			if (_global_jazyk == JAZYK_SK) {
				sprintf(pom, "http://lc.kbs.sk/?den=%04d%02d%02d", _local_den.rok, _local_den.mesiac, _local_den.den);
			}
			else if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)) {
				sprintf(pom, "http://www.katolik.cz/kalendar/kalendar.asp?d=%d&m=%d&r=%d", _local_den.den, _local_den.mesiac, _local_den.rok);
			}
			else if (_global_jazyk == JAZYK_HU) {
				sprintf(pom, "http://www.katolikus.hu/igenaptar/%04d%02d%02d.html", _local_den.rok, _local_den.mesiac, _local_den.den);
			}
			else {
				sprintf(pom, "%04d-%02d-%02d", _local_den.rok, _local_den.mesiac, _local_den.den);
			}
			Log("pridávam odkaz na liturgické čítania (1): %s\n", pom);
			strcat(_local_string, pom);

			sprintf(pom, "\"" HTML_TARGET_BLANK ">%s" HTML_A_END, (char *)html_text_opt_0_citania[_global_jazyk]);
			Log("pridávam odkaz na liturgické čítania (2): %s\n", pom);
			strcat(_local_string, pom);

			sprintf(pom, HTML_SPAN_END);
			Log("pridávam odkaz na liturgické čítania (3): %s\n", pom);
			strcat(_local_string, pom);
#endif // not LITURGICKE_CITANIA_ANDROID // BEHAVIOUR_WEB
		}// if ((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_CITANIA)) && aj_citanie)
	}// lokalizácia slávenia a kalendár
	else {
		sprintf(pom, " (%s)", _local_den.lc_str_id);
		Log("pridávam odkaz na liturgické čítania (lc.kbs.sk): %s\n", pom);
		strcat(_local_string, pom);
	}// typ == EXPORT_DNA_VIAC_DNI_TXT

	Log("  -- _local_string == %s\n", _local_string);
	mystrcpy(_global_string, _local_string, MAX_GLOBAL_STR);
	Log("  -- _global_string == %s\n", _global_string);

	// ____________________________________________________________
	// initialization of _global_string2
	if ((
			((_global_r._POPOLCOVA_STREDA.den == _local_den.den) && (_global_r._POPOLCOVA_STREDA.mesiac == _local_den.mesiac)) || // Popolcová streda
			((_local_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN) && (_local_den.denvt != DEN_NEDELA) && (_local_den.denvt != DEN_STVRTOK)) || // pondelok -- streda Svätého týždňa
			(_local_den.smer > 7) // nie špeciálne dni: Trojdnie (1), Narodenie, Zjavenie, Nanebovstúpenie, ZDS (2), nedele (2, 6), slávnosti (3), 01NOV, sviatky Pána (5)
		)
		&& (_local_den.litobd != OBD_OKTAVA_NARODENIA) // nie Oktáva Narodenia Pána
	) {
		mystrcpy(_global_string2, rimskymi_tyzden_zaltara[tyzden_zaltara(_global_den.tyzden)], MAX_GLOBAL_STR2);
	}
	else if (_local_den.denvt == DEN_NEDELA) {
		// aj nedele majú týždeň žaltára; ak ide o špeciálne nedele, vypíšeme rok (A, B, C) a "V"
		sprintf(_global_string2, "%c, %s", _local_den.litrok, rimskymi_tyzden_zaltara[(_je_local_den_vlastne_slavenie_pismV) ? 5 : tyzden_zaltara(_global_den.tyzden)]);
	}
	else {
		mystrcpy(_global_string2, rimskymi_tyzden_zaltara[5], MAX_GLOBAL_STR2);
	}

	Log("  -- _global_string2 == %s\n", _global_string2);

	// ____________________________________________________________
	// initialization of _global_string_farba

	liturgicka_farba = _local_den.farba;

	// zložené farby
	//	LIT_FARBA_FIALOVA_CIERNA	== LIT_FARBA_FIALOVA a LIT_FARBA_CIERNA
	//	LIT_FARBA_FIALOVA_BIELA		== LIT_FARBA_FIALOVA a LIT_FARBA_BIELA
	//	LIT_FARBA_RUZOVA_FIALOVA	== LIT_FARBA_RUZOVA a LIT_FARBA_FIALOVA
	if ((liturgicka_farba == LIT_FARBA_FIALOVA_CIERNA) || (liturgicka_farba == LIT_FARBA_FIALOVA_BIELA) || (liturgicka_farba == LIT_FARBA_RUZOVA_FIALOVA)) {
		if (liturgicka_farba == LIT_FARBA_RUZOVA_FIALOVA) {
			liturgicka_farba_alt = LIT_FARBA_FIALOVA;
			liturgicka_farba = LIT_FARBA_RUZOVA;
		}
		else {
			liturgicka_farba_alt = (liturgicka_farba == LIT_FARBA_FIALOVA_CIERNA) ? LIT_FARBA_CIERNA : LIT_FARBA_BIELA;
			liturgicka_farba = LIT_FARBA_FIALOVA;
		}
	}
	else {
		liturgicka_farba_alt = LIT_FARBA_NEURCENA;
	}

	// pre spomienku na privilegované dni (VSLH č. 238-239 -- commemoratio) sa farba neexportuje
	if ((_local_den.typslav == SLAV_LUB_SPOMIENKA) && (je_privileg)) {
		if ((typ != EXPORT_DNA_VIAC_DNI) && (typ != EXPORT_DNA_VIAC_DNI_SIMPLE) && (typ != EXPORT_DNA_VIAC_DNI_TXT)) {
			// farba sa neexportuje
			export_farby = NIE;
			sprintf(_global_string_farba, "<!-- %s %s -->", (char *)nazov_farby(liturgicka_farba), (liturgicka_farba_alt != LIT_FARBA_NEURCENA) ? (char *)nazov_farby(liturgicka_farba_alt) : STR_EMPTY);
		}
		else {
			// exportuje sa liturgická farba privilegovaných dní (VSLH, č. 238-239)
			export_farby = ANO;
			liturgicka_farba = (_local_den.litobd == OBD_OKTAVA_NARODENIA) ? LIT_FARBA_BIELA : LIT_FARBA_FIALOVA;
			liturgicka_farba_alt = LIT_FARBA_NEURCENA;
		}
	}// ľubovoľná spomienka v privilegované dni

	if (export_farby) {
		if (PODMIENKA_JE_BATCH_MODE_MONTHLY__AND__PLAIN_EXPORT) {
			sprintf(_global_string_farba, "\n" HTML_NONBREAKING_SPACE_LONG "\n<span style=\"font-size: " HTML_FONT_SIZE_FARBA "; background-color: %s; color: %s;\">(%s)" HTML_SPAN_END "\n",
				(char *)html_farba_pozadie[liturgicka_farba],
				(char *)html_farba_popredie[liturgicka_farba],
				(char *)nazov_farby(liturgicka_farba));
			if (liturgicka_farba_alt != LIT_FARBA_NEURCENA) {
				// oddeľovač
				sprintf(pom, "/");
				strcat(_global_string_farba, pom);
				// druhá farba
				sprintf(pom, "<span style=\"background-color: %s; color: %s\">(%s)" HTML_SPAN_END "\n",
					(char *)html_farba_pozadie[liturgicka_farba_alt],
					(char *)html_farba_popredie[liturgicka_farba_alt],
					(char *)nazov_farby(liturgicka_farba_alt));
				strcat(_global_string_farba, pom);
			}// liturgicka_farba_alt != LIT_FARBA_NEURCENA
			sprintf(pom, HTML_LINE_BREAK);
			strcat(_global_string_farba, pom);
		}// if (PODMIENKA_JE_BATCH_MODE_MONTHLY__AND__PLAIN_EXPORT)
		else {
			sprintf(_global_string_farba, "\n<" HTML_TABLE ">\n<" HTML_TABLE_ROW ">\n");
			sprintf(pom, "<" HTML_TABLE_CELL " style=\"background: %s; border: 1px solid %s;\"><span style=\"color: %s; font-size: " HTML_FONT_SIZE_FARBA ";\">%s" HTML_SPAN_END "" HTML_TABLE_CELL_END "\n",
				(char *)html_farba_pozadie[liturgicka_farba],
				(char *)html_farba_okraj[liturgicka_farba],
				(char *)html_farba_popredie[liturgicka_farba],
				(char *)nazov_farby(liturgicka_farba));
			strcat(_global_string_farba, pom);
			if (liturgicka_farba_alt != LIT_FARBA_NEURCENA) {
				// oddeľovač
				sprintf(pom, "<" HTML_TABLE_CELL ">/" HTML_TABLE_CELL_END "\n");
				strcat(_global_string_farba, pom);
				// druhá farba
				sprintf(pom, "<" HTML_TABLE_CELL " style=\"background: %s; border: 1px solid %s;\"><span style =\"color: %s; font-size: " HTML_FONT_SIZE_FARBA ";\">%s" HTML_SPAN_END "" HTML_TABLE_CELL_END "\n",
					(char *)html_farba_pozadie[liturgicka_farba_alt],
					(char *)html_farba_okraj[liturgicka_farba_alt],
					(char *)html_farba_popredie[liturgicka_farba_alt],
					(char *)nazov_farby(liturgicka_farba_alt));
				strcat(_global_string_farba, pom);
			}// liturgicka_farba_alt != LIT_FARBA_NEURCENA
			sprintf(pom, HTML_TABLE_ROW_END "\n" HTML_TABLE_END "\n");
			strcat(_global_string_farba, pom);
		}// else (PODMIENKA_JE_BATCH_MODE_MONTHLY__AND__PLAIN_EXPORT)
	}// export farby
	else {
		Log("export_farby is false.\n");
	}

	Log("  -- _global_string_farba == %s\n", _global_string_farba);

	Log("-- init_global_string(EXPORT_DNA_%d, %d, %s, %d) -- returning SUCCESS\n", typ, poradie_svateho, nazov_modlitby(modlitba), aj_citanie);
	return SUCCESS;
} // init_global_string();

void init_global_string_modlitba(short int modlitba) {
	short int _local_modlitba = _global_modlitba;
	// reťazec modlitby do premennej _global_string_modlitba
	Log("-- init_global_string_modlitba(%d, %s) -- začiatok\n", modlitba, nazov_modlitby(modlitba));
	Log("pôvodná hodnota: %s\n", _global_string_modlitba);
	if (modlitba != _global_modlitba) {
		if (query_type != PRM_XML) {
			ExportHtmlComment("modlitba == %d, _global_modlitba == %d", modlitba, _global_modlitba);
		}
	}
	if ((_global_den.den == 2) && (_global_den.mesiac - 1 == MES_NOV) && ((_global_modlitba == MODL_DRUHE_VESPERY) || (_global_modlitba == MODL_DRUHE_KOMPLETORIUM))) {
		Log("Spomienka vsetkych vernych zosnulych -- nevypisem, ze su druhe vespery (resp. kompletórium po nich)...\n");
		_global_modlitba -= 5; // MODL_DRUHE_VESPERY -> MODL_VESPERY; MODL_DRUHE_KOMPLETORIUM -> MODL_KOMPLETORIUM
	}

	if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT)) {
		mystrcpy(_global_string_modlitba, nazov_Modlitby(_global_modlitba), SMALL);
	}
	else {
		sprintf(_global_string_modlitba, "<" HTML_SPAN_UPPERCASE ">%s" HTML_SPAN_END, nazov_Modlitby(_global_modlitba));
	}

	Log("nová hodnota: %s\n", _global_string_modlitba);
	_global_modlitba = _local_modlitba;
	Log("-- init_global_string_modlitba(%d, %s) -- koniec\n", modlitba, nazov_modlitby(modlitba));
} // init_global_string_modlitba()

void init_global_string_podnadpis(short int modlitba) {
	Log("-- init_global_string_podnadpis(%d, %s) -- začiatok\n", modlitba, nazov_modlitby(modlitba));
	Log("pôvodná hodnota: %s\n", _global_string_podnadpis);

	if (modlitba != _global_modlitba) {
		if (query_type != PRM_XML) {
			ExportHtmlComment("modlitba == %d, _global_modlitba == %d", modlitba, _global_modlitba);
		}
	}

	// pre modlitbu cez deň dáme do nadpisu informáciu o tom, že ide o doplnkovú psalmódiu
	if ((je_modlitba_cez_den(modlitba))
		&& (je_len_doplnkova_psalmodia(modlitba)) // nie vtedy, keď je predpísaná iba doplnková psalmódia (na slávnosti);
		&& !(isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI)) // ani vtedy nie, keď sú jednotlivé možnosti priamo v textoch modlitieb
		) {
		if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA)) {
			mystrcpy(_global_string_podnadpis, HTML_LINE_BREAK "\n(", SMALL);
			strcat(_global_string_podnadpis, str_doplnkova_psalmodia[_global_jazyk]);
			strcat(_global_string_podnadpis, ")");
		}// doplnková psalmódia
		else {
			mystrcpy(_global_string_podnadpis, STR_EMPTY, SMALL);
		}// nie je doplnková psalmódia
	}// MCD

	Log("nová hodnota: %s\n", _global_string_podnadpis);
	Log("-- init_global_string_podnadpis(%d, %s) -- koniec\n", modlitba, nazov_modlitby(modlitba));
} // init_global_string_podnadpis()

short int init_global_string_spol_cast(short int sc_jedna, short int poradie_svateho) {

	short int ret_sc = sc_jedna; // obsahuje nejakú hodnotu MODL_SPOL_CAST_...: buď spol. časť na vstupe alebo ak bol MODL_SPOL_CAST_NULL (-1), tak prvú zo zoznamu

	Log("-- init_global_string_spol_cast(%d, %s) -- začiatok\n", sc_jedna, (sc_jedna == MODL_SPOL_CAST_NULL) ? STR_UNDEF : nazov_spolc(sc_jedna));
	Log("pôvodná hodnota: %s\n", _global_string_spol_cast);

	if (sc_jedna == MODL_SPOL_CAST_NULL) {
		mystrcpy(_global_string_spol_cast, STR_EMPTY, MAX_GLOBAL_STR2);

		// najprv si rozkódujeme, čo je v "_global_den".spolcast podľa poradie_svateho
		_struct_sc sc = _decode_spol_cast(MODL_SPOL_CAST_NEURCENA);
		switch (poradie_svateho) {
		case 0: sc = _decode_spol_cast(_global_den.spolcast);
			break;
		case PORADIE_PM_SOBOTA: sc = _decode_spol_cast(_global_pm_sobota.spolcast);
			break;
		default:
			sc = _decode_spol_cast(_global_svaty(poradie_svateho).spolcast);
			break;
		}

		if (je_spolocna_cast_urcena(sc.a1)) {
			ret_sc = sc.a1;
			strcat(_global_string_spol_cast, lowered_nazov_spolc(sc.a1));
			if (je_spolocna_cast_urcena(sc.a2)) {
				strcat(_global_string_spol_cast, ", ");
				strcat(_global_string_spol_cast, HTML_LINE_BREAK);
				strcat(_global_string_spol_cast, nazov_spolc_alebo_jazyk[_global_jazyk]);
				strcat(_global_string_spol_cast, " ");
				strcat(_global_string_spol_cast, lowered_nazov_spolc(sc.a2));
				if (je_spolocna_cast_urcena(sc.a3)) {
					strcat(_global_string_spol_cast, ", ");
					strcat(_global_string_spol_cast, HTML_LINE_BREAK);
					strcat(_global_string_spol_cast, nazov_spolc_alebo_jazyk[_global_jazyk]);
					strcat(_global_string_spol_cast, " ");
					strcat(_global_string_spol_cast, lowered_nazov_spolc(sc.a3));
				}
			}
		}
	}
	else if (je_spolocna_cast_urcena(sc_jedna)) {
		sprintf(_global_string_spol_cast, "%s", lowered_nazov_spolc(sc_jedna));
	}
	else {
		mystrcpy(_global_string_spol_cast, STR_EMPTY, SMALL);
	}

	Log("nová hodnota: %s\n", _global_string_spol_cast);
	Log("-- init_global_string_spol_cast(%d, %s) -- koniec\n", sc_jedna, (sc_jedna == MODL_SPOL_CAST_NULL) ? STR_UNDEF : nazov_spolc(sc_jedna));

	return ret_sc;
} // init_global_string_spol_cast()

void xml_export_liturgicka_farba() {
	Log("-- xml_export_liturgicka_farba() -- začiatok\n");

	Export(ELEM_BEGIN_ID(XML_LIT_COLOR), _local_den.farba);

	if (export_farby) {
		Export(nazov_farby(liturgicka_farba));
		if (liturgicka_farba_alt != LIT_FARBA_NEURCENA) {
			Export(STR_VERTICAL_BAR);
			Export(nazov_farby(liturgicka_farba_alt));
		}
	}

	Export(ELEM_END(XML_LIT_COLOR) "\n");

	Log("-- xml_export_liturgicka_farba() -- koniec\n");
} // xml_export_liturgicka_farba()

void xml_export_spol_cast(short int poradie_svateho) {
	Log("-- xml_export_spol_cast(%d) -- začiatok\n", poradie_svateho);
	// rozkódujeme si, čo je v "_global_den".spolcast podľa poradie_svateho
	_struct_sc sc = _decode_spol_cast(MODL_SPOL_CAST_NEURCENA);
	// dalo by sa možno použiť aj globálna premenná _local_den; takto je to istejšie
	switch (poradie_svateho) {
	case 0:
		sc = _decode_spol_cast(_global_den.spolcast);
		break;
	case PORADIE_PM_SOBOTA:
		sc = _decode_spol_cast(_global_pm_sobota.spolcast);
		break;
	default:
		sc = _decode_spol_cast(_global_svaty(poradie_svateho).spolcast);
		break;
	}

	if (je_spolocna_cast_urcena(sc.a1)) {
		Export(ELEM_BEGIN_ID(XML_LIT_COMMUNIA) "%s" ELEM_END(XML_LIT_COMMUNIA) "\n", sc.a1, nazov_spolc(sc.a1));
		if (je_spolocna_cast_urcena(sc.a2)) {
			Export(ELEM_BEGIN_ID(XML_LIT_COMMUNIA) "%s" ELEM_END(XML_LIT_COMMUNIA) "\n", sc.a2, nazov_spolc(sc.a2));
			if (je_spolocna_cast_urcena(sc.a3)) {
				Export(ELEM_BEGIN_ID(XML_LIT_COMMUNIA) "%s" ELEM_END(XML_LIT_COMMUNIA) "\n", sc.a3, nazov_spolc(sc.a3));
			}
		}
	}

	Log("-- xml_export_spol_cast() -- koniec\n");
} // xml_export_spol_cast()

void xml_export_options(void) {
	short int i, j;
	Log("-- xml_export_options() -- začiatok\n");

	Export(ELEM_BEGIN(XML_OPTIONS) "\n");

	for (i = 0; i < POCET_GLOBAL_OPT; i++) {
		switch (i) {
		case OPT_0_SPECIALNE:
			Export(ELEM_BEGIN_VALUE_NAME_FORCENAME_TEXT(XML_OPT_0_SPECIALNE) "\n", _global_opt[OPT_0_SPECIALNE], STR_OPT_0, STR_FORCE_OPT_0, html_text_opt_0_kalendar[_global_jazyk]);
			Log("option %d, jednotlivé bit-komponenty...(xml_export_options)\n", OPT_0_SPECIALNE);
			for (j = 0; j < POCET_OPT_0_SPECIALNE; j++) {
				switch (j) {
				case 0: // BIT_OPT_0_VERSE
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_VERSE)"%ld" ELEM_END(XML_BIT_OPT_0_VERSE) "\n", BIT_OPT_0_VERSE, STR_FORCE_BIT_OPT_0_VERSE, html_text_opt_0_verse[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VERSE)));
					break;
				case 1: // BIT_OPT_0_REFERENCIE
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_REFERENCIE)"%ld" ELEM_END(XML_BIT_OPT_0_REFERENCIE) "\n", BIT_OPT_0_REFERENCIE, STR_FORCE_BIT_OPT_0_REF, html_text_opt_0_referencie[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_REFERENCIE)));
					break;
				case 2: // BIT_OPT_0_CITANIA
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_CITANIA)"%ld" ELEM_END(XML_BIT_OPT_0_CITANIA) "\n", BIT_OPT_0_CITANIA, STR_FORCE_BIT_OPT_0_CIT, html_text_opt_0_citania[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_CITANIA)));
					break;
				case 3: // BIT_OPT_0_ZJAVENIE_PANA_NEDELA
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_ZJAVENIE_PANA_NEDELA)"%ld" ELEM_END(XML_BIT_OPT_0_ZJAVENIE_PANA_NEDELA) "\n", BIT_OPT_0_ZJAVENIE_PANA_NEDELA, STR_FORCE_BIT_OPT_0_ZJAV_NED, html_text_opt_0_zjv_ne[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA)));
					break;
				case 4: // BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA)"%ld" ELEM_END(XML_BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA) "\n", BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA, STR_FORCE_BIT_OPT_0_NAN_NED, html_text_opt_0_nan_ne[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA)));
					break;
				case 5: // BIT_OPT_0_TELAKRVI_NEDELA
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_TELAKRVI_NEDELA)"%ld" ELEM_END(XML_BIT_OPT_0_TELAKRVI_NEDELA) "\n", BIT_OPT_0_TELAKRVI_NEDELA, STR_FORCE_BIT_OPT_0_TK_NED, html_text_opt_0_tk_ne[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_TELAKRVI_NEDELA)));
					break;
				case 6: // BIT_OPT_0_FONT_NORMAL
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_FONT_NORMAL)"%ld" ELEM_END(XML_BIT_OPT_0_FONT_NORMAL) "\n", BIT_OPT_0_FONT_NORMAL, STR_FORCE_BIT_OPT_0_FONT_NORMAL, html_text_opt_0_font_normal[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_FONT_NORMAL)));
					break;
				case 7: // BIT_OPT_0_BUTTONS_ORDER
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_BUTTONS_ORDER)"%ld" ELEM_END(XML_BIT_OPT_0_BUTTONS_ORDER) "\n", BIT_OPT_0_BUTTONS_ORDER, STR_FORCE_BIT_OPT_0_BUTTONS_ORDER, html_text_opt_0_buttons_order[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_BUTTONS_ORDER)));
					break;
				case 8: // BIT_OPT_0_VOICE_OUTPUT
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_VOICE_OUTPUT)"%ld" ELEM_END(XML_BIT_OPT_0_VOICE_OUTPUT) "\n", BIT_OPT_0_VOICE_OUTPUT, STR_FORCE_BIT_OPT_0_VOICE_OUTPUT, html_text_opt_0_voice_output[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT)));
					break;
				case 9: // BIT_OPT_0_FOOTNOTES
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_FOOTNOTES)"%ld" ELEM_END(XML_BIT_OPT_0_FOOTNOTES) "\n", BIT_OPT_0_FOOTNOTES, STR_FORCE_BIT_OPT_0_FOOTNOTES, html_text_opt_0_footnotes[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_FOOTNOTES)));
					break;
				case 10: // BIT_OPT_0_TRANSPARENT_NAV
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_TRANSPARENT_NAV)"%ld" ELEM_END(XML_BIT_OPT_0_TRANSPARENT_NAV) "\n", BIT_OPT_0_TRANSPARENT_NAV, STR_FORCE_BIT_OPT_0_TRANSPARENT_NAV, html_text_opt_0_transparent_nav[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_TRANSPARENT_NAV)));
					break;
				case 11: // BIT_OPT_0_ZALMY_FULL_TEXT
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_ZALMY_FULL_TEXT)"%ld" ELEM_END(XML_BIT_OPT_0_ZALMY_FULL_TEXT) "\n", BIT_OPT_0_ZALMY_FULL_TEXT, STR_FORCE_BIT_OPT_0_ZALMY_FULL_TEXT, html_text_opt_0_zalmy_full_text[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZALMY_FULL_TEXT)));
					break;
				case 12: // BIT_OPT_0_REF_BIBLE_COM
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_REF_BIBLE_COM)"%ld" ELEM_END(XML_BIT_OPT_0_REF_BIBLE_COM) "\n", BIT_OPT_0_REF_BIBLE_COM, STR_FORCE_BIT_OPT_0_REF_BIBLE_COM, html_text_opt_0_ref_bible_com[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_REF_BIBLE_COM)));
					break;
				case 13: // BIT_OPT_0_ITALICS_CONDITIONAL
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_ITALICS_CONDITIONAL)"%ld" ELEM_END(XML_BIT_OPT_0_ITALICS_CONDITIONAL) "\n", BIT_OPT_0_ITALICS_CONDITIONAL, STR_FORCE_BIT_OPT_0_ITALICS_CONDITIONAL, html_text_opt_0_italics_cond[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ITALICS_CONDITIONAL)));
					break;
				case 14: // BIT_OPT_0_PRINTED_EDITION
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_PRINTED_EDITION)"%ld" ELEM_END(XML_BIT_OPT_0_PRINTED_EDITION) "\n", BIT_OPT_0_PRINTED_EDITION, STR_FORCE_BIT_OPT_0_PRINTED_EDITION, html_text_opt_0_printed_edition[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_PRINTED_EDITION)));
					break;
				case 15: // BIT_OPT_0_USE_TWO_YEARS_CYCLE
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_USE_TWO_YEARS_CYCLE)"%ld" ELEM_END(XML_BIT_OPT_0_USE_TWO_YEARS_CYCLE) "\n", BIT_OPT_0_USE_TWO_YEARS_CYCLE, STR_FORCE_BIT_OPT_0_USE_TWO_YEARS_CYCLE, html_text_opt_0_use_two_years_cycle[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_USE_TWO_YEARS_CYCLE)));
					break;
				case 16: // BIT_OPT_0_TWO_YEARS_CYCLE_ID
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_TWO_YEARS_CYCLE_ID)"%ld" ELEM_END(XML_BIT_OPT_0_TWO_YEARS_CYCLE_ID) "\n", BIT_OPT_0_TWO_YEARS_CYCLE_ID, STR_FORCE_BIT_OPT_0_TWO_YEARS_CYCLE_ID, html_text_opt_0_two_years_cycle_id[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_TWO_YEARS_CYCLE_ID)));
					break;
				case 17: // BIT_OPT_0_ALTERNATIVE_READINGS
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_ALTERNATIVE_READINGS)"%ld" ELEM_END(XML_BIT_OPT_0_ALTERNATIVE_READINGS) "\n", BIT_OPT_0_ALTERNATIVE_READINGS, STR_FORCE_BIT_OPT_0_TWO_YEARS_CYCLE_ID, html_text_opt_0_alternative_readings[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ALTERNATIVE_READINGS)));
					break;
				case 18: // BIT_OPT_0_TRANSPARENT_NAV_LEFT
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_TRANSPARENT_NAV_LEFT)"%ld" ELEM_END(XML_BIT_OPT_0_TRANSPARENT_NAV_LEFT) "\n", BIT_OPT_0_TRANSPARENT_NAV_LEFT, STR_FORCE_BIT_OPT_0_TRANSPARENT_NAV_LEFT, html_text_opt_0_transparent_nav_left[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_TRANSPARENT_NAV_LEFT)));
					break;
				case 19: // BIT_OPT_0_SIDE_NAVIGATION
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_0_SIDE_NAVIGATION)"%ld" ELEM_END(XML_BIT_OPT_0_SIDE_NAVIGATION) "\n", BIT_OPT_0_SIDE_NAVIGATION, STR_FORCE_BIT_OPT_0_SIDE_NAVIGATION, html_text_opt_0_side_navigation[_global_jazyk], (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_SIDE_NAVIGATION)));
					break;
				} // switch(j)
			}// for j
			Export(ELEM_END(XML_OPT_0_SPECIALNE) "\n");
			break;
		case OPT_1_CASTI_MODLITBY:
			Export(ELEM_BEGIN_VALUE_NAME_FORCENAME_TEXT(XML_OPT_1_CASTI_MODLITBY) "\n", _global_opt[OPT_1_CASTI_MODLITBY], STR_OPT_1, STR_FORCE_OPT_1, html_text_opt_1_dalsie_prepinace[_global_jazyk]);
			Log("option %d, jednotlivé bit-komponenty...(xml_export_options)\n", OPT_1_CASTI_MODLITBY);
			for (j = 0; j < POCET_OPT_1_CASTI_MODLITBY; j++) {
				switch (j) {
				case 0: // BIT_OPT_1_TEDEUM
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_TEDEUM)"%ld" ELEM_END(XML_BIT_OPT_1_TEDEUM) "\n", BIT_OPT_1_TEDEUM, STR_FORCE_BIT_OPT_1_TD, html_text_opt_1_tedeum[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_TEDEUM)));
					break;
				case 1: // BIT_OPT_1_RUBRIKY
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_RUBRIKY)"%ld" ELEM_END(XML_BIT_OPT_1_RUBRIKY) "\n", BIT_OPT_1_RUBRIKY, STR_FORCE_BIT_OPT_1_RUB, html_text_opt_1_rubriky[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_RUBRIKY)));
					break;
				case 2: // BIT_OPT_1_CHVALOSPEVY
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_CHVALOSPEVY)"%ld" ELEM_END(XML_BIT_OPT_1_CHVALOSPEVY) "\n", BIT_OPT_1_CHVALOSPEVY, STR_FORCE_BIT_OPT_1_CHV, html_text_opt_1_chvalospevy[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_CHVALOSPEVY)));
					break;
				case 3: // BIT_OPT_1_SLAVA_OTCU
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_SLAVA_OTCU)"%ld" ELEM_END(XML_BIT_OPT_1_SLAVA_OTCU) "\n", BIT_OPT_1_SLAVA_OTCU, STR_FORCE_BIT_OPT_1_SL, html_text_opt_1_slava_otcu[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_SLAVA_OTCU)));
					break;
				case 4: // BIT_OPT_1_OTCENAS
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_OTCENAS)"%ld" ELEM_END(XML_BIT_OPT_1_OTCENAS) "\n", BIT_OPT_1_OTCENAS, STR_FORCE_BIT_OPT_1_OT, html_text_opt_1_otcenas[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OTCENAS)));
					break;
				case 5: // BIT_OPT_1_MCD_DOPLNKOVA
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_MCD_DOPLNKOVA)"%ld" ELEM_END(XML_BIT_OPT_1_MCD_DOPLNKOVA) "\n", BIT_OPT_1_MCD_DOPLNKOVA, STR_FORCE_BIT_OPT_1_MCD_DOPLNKOVA, html_text_opt_1_mcd_zalmy_ine[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA)));
					break;
				case 6: // BIT_OPT_1_PC_VIGILIA
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_PC_VIGILIA)"%ld" ELEM_END(XML_BIT_OPT_1_PC_VIGILIA) "\n", BIT_OPT_1_PC_VIGILIA, STR_FORCE_BIT_OPT_1_VIGILIA, html_text_opt_1_vigilia[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PC_VIGILIA)));
					break;
				case 7: // BIT_OPT_1_SPOMIENKA_SPOL_CAST
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_SPOMIENKA_SPOL_CAST)"%ld" ELEM_END(XML_BIT_OPT_1_SPOMIENKA_SPOL_CAST) "\n", BIT_OPT_1_SPOMIENKA_SPOL_CAST, STR_FORCE_BIT_OPT_1_SPOMIENKA_SPOL_CAST, html_text_opt_1_spomienka_spolcast[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_SPOMIENKA_SPOL_CAST)));
					break;
				case 8: // BIT_OPT_1_PLNE_RESP
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_PLNE_RESP)"%ld" ELEM_END(XML_BIT_OPT_1_PLNE_RESP) "\n", BIT_OPT_1_PLNE_RESP, STR_FORCE_BIT_OPT_1_PLNE_RESP, html_text_opt_1_plne_resp[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PLNE_RESP)));
					break;
				case 9: // BIT_OPT_1_ZALM95
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_ZALM95)"%ld" ELEM_END(XML_BIT_OPT_1_ZALM95) "\n", BIT_OPT_1_ZALM95, STR_FORCE_BIT_OPT_1_ZALM95, html_text_opt_1_zalm95[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALM95)));
					break;
				case 10: // BIT_OPT_1_PROSBY_ZVOLANIE
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_PROSBY_ZVOLANIE)"%ld" ELEM_END(XML_BIT_OPT_1_PROSBY_ZVOLANIE) "\n", BIT_OPT_1_PROSBY_ZVOLANIE, STR_FORCE_BIT_OPT_1_PROSBY_ZVOLANIE, html_text_opt_1_prosby_zvolanie[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PROSBY_ZVOLANIE)));
					break;
				case 11: // BIT_OPT_1_SKRY_POPIS
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_SKRY_POPIS)"%ld" ELEM_END(XML_BIT_OPT_1_SKRY_POPIS) "\n", BIT_OPT_1_SKRY_POPIS, STR_FORCE_BIT_OPT_1_SKRY_POPIS, html_text_opt_1_skryt_popis_svaty[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_SKRY_POPIS)));
					break;
				case 12: // BIT_OPT_1_ZOBRAZ_SPOL_CAST
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_ZOBRAZ_SPOL_CAST)"%ld" ELEM_END(XML_BIT_OPT_1_ZOBRAZ_SPOL_CAST) "\n", BIT_OPT_1_ZOBRAZ_SPOL_CAST, STR_FORCE_BIT_OPT_1_ZOBRAZ_SPOL_CAST, html_text_opt_1_spolc_svaty[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZOBRAZ_SPOL_CAST)));
					break;
				case 13: // BIT_OPT_1_VESP_KRATSIE_PROSBY
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_VESP_KRATSIE_PROSBY)"%ld" ELEM_END(XML_BIT_OPT_1_VESP_KRATSIE_PROSBY) "\n", BIT_OPT_1_VESP_KRATSIE_PROSBY, STR_FORCE_BIT_OPT_1_VESP_KRATSIE_PROSBY, html_text_opt_1_vesp_kratsie_prosby[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_VESP_KRATSIE_PROSBY)));
					break;
				case 14: // BIT_OPT_1_MCD_ZALTAR_TRI
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_MCD_ZALTAR_TRI)"%ld" ELEM_END(XML_BIT_OPT_1_MCD_ZALTAR_TRI) "\n", BIT_OPT_1_MCD_ZALTAR_TRI, STR_FORCE_BIT_OPT_1_MCD_ZALTAR_TRI, html_text_opt_1_mcd_zalmy_tri[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_ZALTAR_TRI)));
					break;
				case 15: // BIT_OPT_1_ZAVER
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_ZAVER)"%ld" ELEM_END(XML_BIT_OPT_1_ZAVER) "\n", BIT_OPT_1_ZAVER, STR_FORCE_BIT_OPT_1_ZAVER, html_text_opt_1_zaver[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZAVER)));
					break;
				case 16: // BIT_OPT_1_OVERRIDE_STUP_SLAV
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_OVERRIDE_STUP_SLAV)"%ld" ELEM_END(XML_BIT_OPT_1_OVERRIDE_STUP_SLAV) "\n", BIT_OPT_1_OVERRIDE_STUP_SLAV, STR_FORCE_BIT_OPT_1_OVERRIDE_STUP_SLAV, html_text_opt_1_override_stupen_slavenia[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OVERRIDE_STUP_SLAV)));
					break;
				case 17: // BIT_OPT_1_STUP_SVIATOK_SLAVNOST
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_STUP_SVIATOK_SLAVNOST)"%ld" ELEM_END(XML_BIT_OPT_1_STUP_SVIATOK_SLAVNOST) "\n", BIT_OPT_1_STUP_SVIATOK_SLAVNOST, STR_FORCE_BIT_OPT_1_STUP_SVIATOK_SLAVNOST, html_text_opt_1_slavit_ako_slavnost[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_STUP_SVIATOK_SLAVNOST)));
					break;
				case 18: // BIT_OPT_1_KOMPL_MARIA_ANT
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_KOMPL_MARIA_ANT)"%ld" ELEM_END(XML_BIT_OPT_1_KOMPL_MARIA_ANT) "\n", BIT_OPT_1_KOMPL_MARIA_ANT, STR_FORCE_BIT_OPT_1_KOMPL_MARIA_ANT, html_text_opt_1_maria_ant[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_KOMPL_MARIA_ANT)));
					break;
				case 19: // BIT_OPT_1_ZOBRAZ_OTCENAS_UVOD
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_1_ZOBRAZ_OTCENAS_UVOD)"%ld" ELEM_END(XML_BIT_OPT_1_ZOBRAZ_OTCENAS_UVOD) "\n", BIT_OPT_1_ZOBRAZ_OTCENAS_UVOD, STR_FORCE_BIT_OPT_1_ZOBRAZ_OTCENAS_UVOD, html_text_opt_1_otcenas_uvod[_global_jazyk], (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZOBRAZ_OTCENAS_UVOD)));
					break;
				} // switch(j)
			}// for j
			Export(ELEM_END(XML_OPT_1_CASTI_MODLITBY) "\n");
			break;
		case OPT_2_HTML_EXPORT:
			Export(ELEM_BEGIN_VALUE_NAME_FORCENAME_TEXT(XML_OPT_2_HTML_EXPORT) "\n", _global_opt[OPT_2_HTML_EXPORT], STR_OPT_2, STR_FORCE_OPT_2, html_text_opt_2_html_export[_global_jazyk]);
			Log("option %d, jednotlivé bit-komponenty...(xml_export_options)\n", OPT_2_HTML_EXPORT);
			for (j = 0; j < POCET_OPT_2_HTML_EXPORT; j++) {
				switch (j) {
				case 0: // BIT_OPT_2_ISO_DATUM
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_2_ISO_DATUM)"%ld" ELEM_END(XML_BIT_OPT_2_ISO_DATUM) "\n", BIT_OPT_2_ISO_DATUM, STR_FORCE_BIT_OPT_2_ISO_DATUM, html_text_opt_2_iso_datum[_global_jazyk], (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ISO_DATUM)));
					break;
				case 1: // BIT_OPT_2_BUTTON_PRVE_VESPERY
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_2_BUTTON_PRVE_VESPERY)"%ld" ELEM_END(XML_BIT_OPT_2_BUTTON_PRVE_VESPERY) "\n", BIT_OPT_2_BUTTON_PRVE_VESPERY, STR_FORCE_BIT_OPT_2_PRVE_VESPERY, html_text_opt_2_prve_vespery[_global_jazyk], (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY)));
					break;
				case 2: // BIT_OPT_2_FONT_FAMILY
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_2_FONT_FAMILY)"%ld" ELEM_END(XML_BIT_OPT_2_FONT_FAMILY) "\n", BIT_OPT_2_FONT_FAMILY, STR_FORCE_BIT_OPT_2_FONT_FAMILY, html_text_opt_2_font_family[_global_jazyk], (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_FONT_FAMILY)));
					break;
				case 3: // BIT_OPT_2_FONT_NAME_CHOOSER
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_2_FONT_NAME_CHOOSER)"%ld" ELEM_END(XML_BIT_OPT_2_FONT_NAME_CHOOSER) "\n", BIT_OPT_2_FONT_NAME_CHOOSER, STR_FORCE_BIT_OPT_2_FONT_NAME_CHOOSER, html_text_font_name_simple[_global_jazyk], (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_FONT_NAME_CHOOSER)));
					break;
				case 4: // BIT_OPT_2_FONT_SIZE_CHOOSER
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_2_FONT_SIZE_CHOOSER)"%ld" ELEM_END(XML_BIT_OPT_2_FONT_SIZE_CHOOSER) "\n", BIT_OPT_2_FONT_SIZE_CHOOSER, STR_FORCE_BIT_OPT_2_FONT_SIZE, html_text_font_size[_global_jazyk], (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_FONT_SIZE_CHOOSER)));
					break;
				case 5: // BIT_OPT_2_NAVIGATION
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_2_NAVIGATION)"%ld" ELEM_END(XML_BIT_OPT_2_NAVIGATION) "\n", BIT_OPT_2_NAVIGATION, STR_FORCE_BIT_OPT_2_NAVIGATION, html_text_opt_2_navigation[_global_jazyk], (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_NAVIGATION)));
					break;
				case 6: // BIT_OPT_2_TEXT_WRAP
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_2_TEXT_WRAP)"%ld" ELEM_END(XML_BIT_OPT_2_TEXT_WRAP) "\n", BIT_OPT_2_TEXT_WRAP, STR_FORCE_BIT_OPT_2_TEXT_WRAP, html_text_opt_2_textwrap[_global_jazyk], (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_TEXT_WRAP)));
					break;
				case 7: // BIT_OPT_2_BUTTONY_USPORNE
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_2_BUTTONY_USPORNE)"%ld" ELEM_END(XML_BIT_OPT_2_BUTTONY_USPORNE) "\n", BIT_OPT_2_BUTTONY_USPORNE, STR_FORCE_BIT_OPT_2_BUTTONY_USPORNE, html_text_opt_2_buttons_usporne[_global_jazyk], (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTONY_USPORNE)));
					break;
				case 8: // BIT_OPT_2_NOCNY_REZIM
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_2_NOCNY_REZIM)"%ld" ELEM_END(XML_BIT_OPT_2_NOCNY_REZIM) "\n", BIT_OPT_2_NOCNY_REZIM, STR_FORCE_BIT_OPT_2_NOCNY_REZIM, html_text_opt_2_nocny_rezim[_global_jazyk], (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_NOCNY_REZIM)));
					break;
				case 9: // BIT_OPT_2_ROZNE_MOZNOSTI
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_2_ROZNE_MOZNOSTI)"%ld" ELEM_END(XML_BIT_OPT_2_ROZNE_MOZNOSTI) "\n", BIT_OPT_2_ROZNE_MOZNOSTI, STR_FORCE_BIT_OPT_2_ROZNE_MOZNOSTI, html_text_opt_2_moznosti[_global_jazyk], (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI)));
					break;
				case 10: // BIT_OPT_2_HIDE_NAVIG_BUTTONS
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_2_HIDE_NAVIG_BUTTONS)"%ld" ELEM_END(XML_BIT_OPT_2_HIDE_NAVIG_BUTTONS) "\n", BIT_OPT_2_HIDE_NAVIG_BUTTONS, STR_FORCE_BIT_OPT_2_HIDE_NAVIG_BUTTONS, STR_EMPTY, (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_NAVIG_BUTTONS)));
					break;
				case 11: // BIT_OPT_2_HIDE_KALENDAR
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_2_HIDE_KALENDAR)"%ld" ELEM_END(XML_BIT_OPT_2_HIDE_KALENDAR) "\n", BIT_OPT_2_HIDE_KALENDAR, STR_FORCE_BIT_OPT_2_HIDE_KALENDAR, STR_EMPTY, (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_KALENDAR)));
					break;
				case 12: // BIT_OPT_2_HIDE_OPTIONS1
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_2_HIDE_OPTIONS1)"%ld" ELEM_END(XML_BIT_OPT_2_HIDE_OPTIONS1) "\n", BIT_OPT_2_HIDE_OPTIONS1, STR_FORCE_BIT_OPT_2_HIDE_OPTIONS1, STR_EMPTY, (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_OPTIONS1)));
					break;
				case 13: // BIT_OPT_2_HIDE_OPTIONS2
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_2_HIDE_OPTIONS2)"%ld" ELEM_END(XML_BIT_OPT_2_HIDE_OPTIONS2) "\n", BIT_OPT_2_HIDE_OPTIONS2, STR_FORCE_BIT_OPT_2_HIDE_OPTIONS2, STR_EMPTY, (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_OPTIONS2)));
					break;
				case 14: // BIT_OPT_2_ALTERNATIVES
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_2_ALTERNATIVES)"%ld" ELEM_END(XML_BIT_OPT_2_ALTERNATIVES) "\n", BIT_OPT_2_ALTERNATIVES, STR_FORCE_BIT_OPT_2_ALTERNATIVES, html_text_opt_2_alternatives[_global_jazyk], (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES)));
					break;
				case 15: // BIT_OPT_2_SHOW_DEFAULT_CALENDAR
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_2_SHOW_DEFAULT_CALENDAR)"%ld" ELEM_END(XML_BIT_OPT_2_SHOW_DEFAULT_CALENDAR) "\n", BIT_OPT_2_SHOW_DEFAULT_CALENDAR, STR_FORCE_BIT_OPT_2_SHOW_DEFAULT_CALENDAR, html_text_opt_2_show_defalut_calendar[_global_jazyk], (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_SHOW_DEFAULT_CALENDAR)));
					break;
				case 16: // BIT_OPT_2_ROUNDED_CORNERS
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_2_ROUNDED_CORNERS)"%ld" ELEM_END(XML_BIT_OPT_2_ROUNDED_CORNERS) "\n", BIT_OPT_2_ROUNDED_CORNERS, STR_FORCE_BIT_OPT_2_SHOW_DEFAULT_CALENDAR, html_text_opt_2_rounded_corners[_global_jazyk], (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ROUNDED_CORNERS)));
					break;
				} // switch(j)
			}// for j
			Export(ELEM_END(XML_OPT_2_HTML_EXPORT) "\n");
			break;
		case OPT_3_SPOLOCNA_CAST:
			Export(ELEM_BEGIN_VALUE_NAME_FORCENAME_TEXT(XML_OPT_3_SPOLOCNA_CAST), _global_opt[OPT_3_SPOLOCNA_CAST], STR_OPT_3, STR_FORCE_OPT_3, html_text_spol_casti_vziat_zo[_global_jazyk]);
			Log("option %d...\n", OPT_3_SPOLOCNA_CAST);
			Export("%s", _global_opt[OPT_3_SPOLOCNA_CAST] <= MODL_SPOL_CAST_NEBRAT ? nazov_spolc(_global_opt[OPT_3_SPOLOCNA_CAST]) : STR_EMPTY);
			Export(ELEM_END(XML_OPT_3_SPOLOCNA_CAST) "\n");
			break;
		case OPT_4_OFFLINE_EXPORT:
			break;
		case OPT_5_ALTERNATIVES:
			Export(ELEM_BEGIN_VALUE_NAME_FORCENAME_TEXT(XML_OPT_5_ALTERNATIVES) "\n", _global_opt[OPT_5_ALTERNATIVES], STR_OPT_5, STR_FORCE_OPT_5, html_text_opt_2_alternatives[_global_jazyk]);
			Log("option %d, jednotlivé bit-komponenty...(xml_export_options)\n", OPT_5_ALTERNATIVES);
			for (j = 0; j < POCET_OPT_5_ALTERNATIVES; j++) {
				switch (j) {
				case 0: // BIT_OPT_5_HYMNUS_KOMPL
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT_SLASH(XML_BIT_OPT_5_HYMNUS_KOMPL)"%ld" ELEM_END(XML_BIT_OPT_5_HYMNUS_KOMPL) "\n", BIT_OPT_5_HYMNUS_KOMPL, STR_FORCE_BIT_OPT_5_HYMNUS_KOMPL, html_text_opt_5_KomplHymnusA[_global_jazyk], html_text_opt_5_KomplHymnusB[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_KOMPL)));
					break;
				case 1: // BIT_OPT_5_HYMNUS_PC
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT_SLASH(XML_BIT_OPT_5_HYMNUS_PC)"%ld" ELEM_END(XML_BIT_OPT_5_HYMNUS_PC) "\n", BIT_OPT_5_HYMNUS_PC, STR_FORCE_BIT_OPT_5_HYMNUS_PC, html_text_opt_5_PCHymnusI[_global_jazyk], html_text_opt_5_PCHymnusII[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_PC)));
					break;
				case 2: // BIT_OPT_5_HYMNUS_MCD_PREDPOL
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT_SLASH(XML_BIT_OPT_5_HYMNUS_MCD_PREDPOL)"%ld" ELEM_END(XML_BIT_OPT_5_HYMNUS_MCD_PREDPOL) "\n", BIT_OPT_5_HYMNUS_MCD_PREDPOL, STR_FORCE_BIT_OPT_5_HYMNUS_MCD_PREDPOL, html_text_opt_5_MCDPredHymnus1[_global_jazyk], html_text_opt_5_MCDPredHymnus2[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_MCD_PREDPOL)));
					break;
				case 3: // BIT_OPT_5_HYMNUS_MCD_PREDPOL
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT_SLASH(XML_BIT_OPT_5_HYMNUS_MCD_NAPOL)"%ld" ELEM_END(XML_BIT_OPT_5_HYMNUS_MCD_NAPOL) "\n", BIT_OPT_5_HYMNUS_MCD_NAPOL, STR_FORCE_BIT_OPT_5_HYMNUS_MCD_NAPOL, html_text_opt_5_MCDNaHymnus1[_global_jazyk], html_text_opt_5_MCDNaHymnus2[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_MCD_NAPOL)));
					break;
				case 4: // BIT_OPT_5_HYMNUS_MCD_POPOL
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT_SLASH(XML_BIT_OPT_5_HYMNUS_MCD_POPOL)"%ld" ELEM_END(XML_BIT_OPT_5_HYMNUS_MCD_POPOL) "\n", BIT_OPT_5_HYMNUS_MCD_POPOL, STR_FORCE_BIT_OPT_5_HYMNUS_MCD_POPOL, html_text_opt_5_MCDPoHymnus1[_global_jazyk], html_text_opt_5_MCDPoHymnus2[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_MCD_POPOL)));
					break;
				case 5: // BIT_OPT_5_DOPLNK_PSALM_122_129
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_5_DOPLNK_PSALM_122_129)"%ld" ELEM_END(XML_BIT_OPT_5_DOPLNK_PSALM_122_129) "\n", BIT_OPT_5_DOPLNK_PSALM_122_129, STR_FORCE_BIT_OPT_5_DOPLNK_PSALM_122_129, html_text_opt_5_DPsalmZ122_129[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_DOPLNK_PSALM_122_129)));
					break;
				case 6: // BIT_OPT_5_DOPLNK_PSALM_127_131
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_5_DOPLNK_PSALM_127_131)"%ld" ELEM_END(XML_BIT_OPT_5_DOPLNK_PSALM_127_131) "\n", BIT_OPT_5_DOPLNK_PSALM_127_131, STR_FORCE_BIT_OPT_5_DOPLNK_PSALM_127_131, html_text_opt_5_DPsalmZ127_131[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_DOPLNK_PSALM_127_131)));
					break;
				case 7: // BIT_OPT_5_DOPLNK_PSALM_126_129
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_5_DOPLNK_PSALM_126_129)"%ld" ELEM_END(XML_BIT_OPT_5_DOPLNK_PSALM_126_129) "\n", BIT_OPT_5_DOPLNK_PSALM_126_129, STR_FORCE_BIT_OPT_5_DOPLNK_PSALM_126_129, html_text_opt_5_DPsalmZ126_129[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_DOPLNK_PSALM_126_129)));
					break;
				case 8: // BIT_OPT_5_HYMNUS_VN_PC
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT_SLASH(XML_BIT_OPT_5_HYMNUS_VN_PC)"%ld" ELEM_END(XML_BIT_OPT_5_HYMNUS_VN_PC) "\n", BIT_OPT_5_HYMNUS_VN_PC, STR_FORCE_BIT_OPT_5_HYMNUS_VN_PC, html_text_opt_5_PCHymnusVNnedela[_global_jazyk], html_text_opt_5_PCHymnusVNferia[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_VN_PC)));
					break;
				case 9: // BIT_OPT_5_HYMNUS_VN_RCH
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT_SLASH(XML_BIT_OPT_5_HYMNUS_VN_RCH)"%ld" ELEM_END(XML_BIT_OPT_5_HYMNUS_VN_RCH) "\n", BIT_OPT_5_HYMNUS_VN_RCH, STR_FORCE_BIT_OPT_5_HYMNUS_VN_RCH, html_text_opt_5_RChHymnusVNnedela[_global_jazyk], html_text_opt_5_RChHymnusVNferia[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_VN_RCH)));
					break;
				case 10: // BIT_OPT_5_HYMNUS_VN_VESP
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT_SLASH(XML_BIT_OPT_5_HYMNUS_VN_VESP)"%ld" ELEM_END(XML_BIT_OPT_5_HYMNUS_VN_VESP) "\n", BIT_OPT_5_HYMNUS_VN_VESP, STR_FORCE_BIT_OPT_5_HYMNUS_VN_VESP, html_text_opt_5_VespHymnusVNnedela[_global_jazyk], html_text_opt_5_VespHymnusVNferia[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_VN_VESP)));
					break;
				case 11: // BIT_OPT_5_HYMNUS_1VESP
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT_SLASH(XML_BIT_OPT_5_HYMNUS_1VESP)"%ld" ELEM_END(XML_BIT_OPT_5_HYMNUS_1VESP) "\n", BIT_OPT_5_HYMNUS_1VESP, STR_FORCE_BIT_OPT_5_HYMNUS_1VESP, html_text_opt_5_1VHymnusNe[_global_jazyk], html_text_opt_5_1VHymnusPC[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_1VESP)));
					break;
				case 12: // BIT_OPT_5_POPOL_STREDA_PSALMODIA
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT_SLASH(XML_BIT_OPT_5_POPOL_STREDA_PSALMODIA)"%ld" ELEM_END(XML_BIT_OPT_5_POPOL_STREDA_PSALMODIA) "\n", BIT_OPT_5_POPOL_STREDA_PSALMODIA, STR_FORCE_BIT_OPT_5_POPOL_STREDA_PSALMODIA, html_text_opt_5_PopolStrPsalm_4STR[_global_jazyk], html_text_opt_5_PopolStrPsalm_3PI[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_POPOL_STREDA_PSALMODIA)));
					break;
				case 13: // BIT_OPT_5_CZ_HYMNY_VYBER
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT_SLASH(XML_BIT_OPT_5_CZ_HYMNY_VYBER)"%ld" ELEM_END(XML_BIT_OPT_5_CZ_HYMNY_VYBER) "\n", BIT_OPT_5_CZ_HYMNY_VYBER, STR_FORCE_BIT_OPT_5_CZ_HYMNY_VYBER, html_text_opt_5_CZhymnyNORMAL[_global_jazyk], html_text_opt_5_CZhymnyRENC[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_CZ_HYMNY_VYBER)));
					break;
				case 14: // BIT_OPT_5_OFF_DEF_PSALM_146_150
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_5_OFF_DEF_PSALM_146_150)"%ld" ELEM_END(XML_BIT_OPT_5_OFF_DEF_PSALM_146_150) "\n", BIT_OPT_5_OFF_DEF_PSALM_146_150, STR_FORCE_BIT_OPT_5_OFF_DEF_PSALM_146_150, html_text_opt_5_OffDefZ146_150[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_OFF_DEF_PSALM_146_150)));
					break;
				case 15: // BIT_OPT_5_OFF_DEF_PSALM_146_150
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_5_ZAVER_KNAZ_DIAKON)"%ld" ELEM_END(XML_BIT_OPT_5_ZAVER_KNAZ_DIAKON) "\n", BIT_OPT_5_ZAVER_KNAZ_DIAKON, STR_FORCE_BIT_OPT_5_ZAVER_KNAZ_DIAKON, html_text_opt_5_zaver_knaz_diakon[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_ZAVER_KNAZ_DIAKON)));
					break;
				case 16: // BIT_OPT_5_INVITATORIUM_ANT
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_5_INVITATORIUM_ANT)"%ld" ELEM_END(XML_BIT_OPT_5_INVITATORIUM_ANT) "\n", BIT_OPT_5_INVITATORIUM_ANT, STR_FORCE_BIT_OPT_5_INVITATORIUM_ANT, /* ToDo: nazov_modlitby(MODL_INVITATORIUM) + ": " */ html_text_opt_6_alternatives_multi_antifona[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_INVITATORIUM_ANT)));
					break;
				case 17: // BIT_OPT_5_OCR_34_HYMNS
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_BIT_OPT_5_OCR_34_HYMNS)"%ld" ELEM_END(XML_BIT_OPT_5_OCR_34_HYMNS) "\n", BIT_OPT_5_OCR_34_HYMNS, STR_FORCE_BIT_OPT_5_OCR_34_HYMNS, html_text_opt_5_OCR34Hymns[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_OCR_34_HYMNS)));
					break;
				case 18: // BIT_OPT_5_KOMPLETORIUM_OKTAVA
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT_SLASH(XML_BIT_OPT_5_KOMPLETORIUM_OKTAVA)"%ld" ELEM_END(XML_BIT_OPT_5_KOMPLETORIUM_OKTAVA) "\n", BIT_OPT_5_KOMPLETORIUM_OKTAVA, STR_FORCE_BIT_OPT_5_KOMPLETORIUM_OKTAVA, html_text_opt_5_KomplOkt1[_global_jazyk], html_text_opt_5_KomplOkt2[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_KOMPLETORIUM_OKTAVA)));
					break;
				case 19: // BIT_OPT_5_ZELENY_STVRTOK_PSALMODIA
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT_SLASH(XML_BIT_OPT_5_ZELENY_STVRTOK_PSALMODIA)"%ld" ELEM_END(XML_BIT_OPT_5_ZELENY_STVRTOK_PSALMODIA) "\n", BIT_OPT_5_ZELENY_STVRTOK_PSALMODIA, STR_FORCE_BIT_OPT_5_ZELENY_STVRTOK_PSALMODIA, html_text_opt_5_ZelStvPsalm_2STV[_global_jazyk], html_text_opt_5_ZelStvPsalm_3PI[_global_jazyk], (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_ZELENY_STVRTOK_PSALMODIA)));
					break;
				} // switch(j)
			}// for j
			Export(ELEM_END(XML_OPT_5_ALTERNATIVES) "\n");
			break;
		case OPT_6_ALTERNATIVES_MULTI:
			Export(ELEM_BEGIN_VALUE_NAME_FORCENAME_TEXT(XML_OPT_6_ALTERNATIVES_MULTI) "\n", _global_opt[OPT_6_ALTERNATIVES_MULTI], STR_OPT_6, STR_FORCE_OPT_6, html_text_opt_6_alternatives_multi[_global_jazyk]);
			Log("option %d, jednotlivé decimal-places-komponenty...(xml_export_options)\n", OPT_6_ALTERNATIVES_MULTI);
			for (j = 1; j <= POCET_OPT_6_ALTERNATIVES_MULTI; j++) {
				switch (j) {
				case 1: // BASE_OPT_6_HYMNUS_MULTI
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_PLACE_OPT_6_HYMNUS_MULTI)"%ld" ELEM_END(XML_PLACE_OPT_6_HYMNUS_MULTI) "\n", BASE_OPT_6_HYMNUS_MULTI, STR_FORCE_PLACE_OPT_6_HYMNUS_MULTI, html_text_opt_6_alternatives_multi_hymnus[_global_jazyk], (isGlobalOption(OPT_6_ALTERNATIVES_MULTI, BASE_OPT_6_HYMNUS_MULTI)));
					break;
				case 2: // BASE_OPT_6_CITANIE2_MULTI
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_PLACE_OPT_6_CITANIE2_MULTI)"%ld" ELEM_END(XML_PLACE_OPT_6_CITANIE2_MULTI) "\n", BASE_OPT_6_CITANIE2_MULTI, STR_FORCE_PLACE_OPT_6_CITANIE2_MULTI, html_text_opt_6_alternatives_multi_citanie[_global_jazyk], (isGlobalOption(OPT_6_ALTERNATIVES_MULTI, BASE_OPT_6_CITANIE2_MULTI)));
					break;
				case 3: // BASE_OPT_6_CITANIE1_MULTI
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_PLACE_OPT_6_CITANIE1_MULTI)"%ld" ELEM_END(XML_PLACE_OPT_6_CITANIE1_MULTI) "\n", BASE_OPT_6_CITANIE1_MULTI, STR_FORCE_PLACE_OPT_6_CITANIE1_MULTI, html_text_opt_6_alternatives_multi_citanie[_global_jazyk], (isGlobalOption(OPT_6_ALTERNATIVES_MULTI, BASE_OPT_6_CITANIE1_MULTI)));
					break;
				case 4: // BASE_OPT_6_ANTIFONA_MULTI
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_PLACE_OPT_6_ANTIFONA_MULTI)"%ld" ELEM_END(XML_PLACE_OPT_6_ANTIFONA_MULTI) "\n", BASE_OPT_6_ANTIFONA_MULTI, STR_FORCE_PLACE_OPT_6_ANTIFONA_MULTI, html_text_opt_6_alternatives_multi_antifona[_global_jazyk], (isGlobalOption(OPT_6_ALTERNATIVES_MULTI, BASE_OPT_6_ANTIFONA_MULTI)));
					break;
				case 5: // BASE_OPT_6_MODLITBA_MULTI
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_PLACE_OPT_6_MODLITBA_MULTI)"%ld" ELEM_END(XML_PLACE_OPT_6_MODLITBA_MULTI) "\n", BASE_OPT_6_MODLITBA_MULTI, STR_FORCE_PLACE_OPT_6_MODLITBA_MULTI, html_text_opt_6_alternatives_multi_modlitba[_global_jazyk], (isGlobalOption(OPT_6_ALTERNATIVES_MULTI, BASE_OPT_6_MODLITBA_MULTI)));
					break;
				case 6: // BASE_OPT_6_PROSBY_MULTI
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_PLACE_OPT_6_PROSBY_MULTI)"%ld" ELEM_END(XML_PLACE_OPT_6_PROSBY_MULTI) "\n", BASE_OPT_6_PROSBY_MULTI, STR_FORCE_PLACE_OPT_6_PROSBY_MULTI, html_text_opt_6_alternatives_multi_prosby[_global_jazyk] /* ToDo: prekompletórium: html_text_opt_6_alternatives_multi_ukonkaj[_global_jazyk] */, (isGlobalOption(OPT_6_ALTERNATIVES_MULTI, BASE_OPT_6_PROSBY_MULTI)));
					break;
				case 7: // BASE_OPT_6_KCIT_RESP_MULTI
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_PLACE_OPT_6_KCIT_RESP_MULTI)"%ld" ELEM_END(XML_PLACE_OPT_6_KCIT_RESP_MULTI) "\n", BASE_OPT_6_KCIT_RESP_MULTI, STR_FORCE_PLACE_OPT_6_KCIT_RESP_MULTI, html_text_opt_6_alternatives_multi_kcit_resp[_global_jazyk], (isGlobalOption(OPT_6_ALTERNATIVES_MULTI, BASE_OPT_6_KCIT_RESP_MULTI)));
					break;
				case 8: // BASE_OPT_6_KRESP_MULTI
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_PLACE_OPT_6_KRESP_MULTI)"%ld" ELEM_END(XML_PLACE_OPT_6_KRESP_MULTI) "\n", BASE_OPT_6_KRESP_MULTI, STR_FORCE_PLACE_OPT_6_KRESP_MULTI, html_text_opt_6_alternatives_multi_kresp[_global_jazyk], (isGlobalOption(OPT_6_ALTERNATIVES_MULTI, BASE_OPT_6_KRESP_MULTI)));
					break;
				case 9: // BASE_OPT_6_PSALM_MULTI
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_PLACE_OPT_6_PSALM_MULTI)"%ld" ELEM_END(XML_PLACE_OPT_6_PSALM_MULTI) "\n", BASE_OPT_6_PSALM_MULTI, STR_FORCE_PLACE_OPT_6_PSALM_MULTI, html_text_opt_6_alternatives_multi_psalm[_global_jazyk], (isGlobalOption(OPT_6_ALTERNATIVES_MULTI, BASE_OPT_6_PSALM_MULTI)));
					break;
				case 10: // BASE_OPT_6_MARIA_ANT_MULTI
					Export(ELEM_BEGIN_ID_FORCENAME_TEXT(XML_PLACE_OPT_6_MARIA_ANT_MULTI)"%ld" ELEM_END(XML_PLACE_OPT_6_MARIA_ANT_MULTI) "\n", BASE_OPT_6_MARIA_ANT_MULTI, STR_FORCE_PLACE_OPT_6_MARIA_ANT_MULTI, html_text_opt_6_alternatives_multi_maria_ant[_global_jazyk], (isGlobalOption(OPT_6_ALTERNATIVES_MULTI, BASE_OPT_6_MARIA_ANT_MULTI)));
					break;
				} // switch(j)
			}// for j
			Export(ELEM_END(XML_OPT_6_ALTERNATIVES_MULTI) "\n");
			break;
		} // switch(i)
	}// for i

	Export(ELEM_END(XML_OPTIONS)"\n\n");

	Log("-- xml_export_options() -- koniec\n");
} // xml_export_options()

char* get_data_for_menu_item_app_specific(short int menu_group, short int menu_item) {
	if (menu_item_type[menu_group][menu_item] != MENU_ITEM_TYPE_APP_SPECIFIC) {
		return (char*)STR_EMPTY;
	}
	switch (menu_group) {
	case MENU_0_GENERAL:
		switch (menu_item) {
		case MENU_0_ITEM_WHEN_ONLINE:
			return (char*)menu_text_mode[_global_jazyk];
			break;
		case GLOBAL_NULL:
		default:
			break;
		} // switch (menu_item)
		break;
	case MENU_1_DEVICE:
		switch (menu_item) {
		case MENU_1_ITEM_VOLUME_BUTTONS:
			return (char*)menu_text_volume_buttons[_global_jazyk];
			break;
		case MENU_1_ITEM_SCREEN_ALWAYS:
			return (char*)menu_text_do_not_dim_screen[_global_jazyk];
			break;
		case MENU_1_ITEM_DO_NOT_DISTURB:
			return (char*)menu_text_do_not_disturb[_global_jazyk];
			break;
		case MENU_1_ITEM_LOCK_FONT_SIZE:
			return (char*)menu_text_lock_font_size[_global_jazyk];
			break;
		case GLOBAL_NULL:
		default:
			break;
		} // switch (menu_item)
		break;
	case MENU_2_LOOK:
		switch (menu_item) {
		case MENU_2_ITEM_ALT_BACKGROUND:
			return (char*)menu_text_alt_background[_global_jazyk];
			break;
		case GLOBAL_NULL:
		default:
			break;
		} // switch (menu_item)
		break;
	case MENU_3_TEXT_CONTENT:
		switch (menu_item) {
		case GLOBAL_NULL:
		default:
			break;
		} // switch (menu_item)
		break;
	case MENU_4_CALENDAR:
		switch (menu_item) {
		case GLOBAL_NULL:
		default:
			break;
		} // switch (menu_item)
		break;
	case MENU_5_TTS:
		switch (menu_item) {
		case GLOBAL_NULL:
		default:
			break;
		} // switch (menu_item)
		break;
	}// switch (menu_group)

	return (char*)STR_EMPTY;
}// get_data_for_menu_item_app_specific()

// returns switch for menu items (those of type MENU_ITEM_TYPE_MAIN_SWITCH)
menu_item_switch_str_name get_data_for_menu_item_switch(short int menu_group, short int menu_item) {
	menu_item_switch_str_name output;
	mystrcpy(output.switch_str, STR_EMPTY, SMALL);
	mystrcpy(output.switch_xml, STR_EMPTY, SMALL);
	mystrcpy(output.switch_name, STR_EMPTY, SMALL);

	if (menu_item_type[menu_group][menu_item] != MENU_ITEM_TYPE_MAIN_SWITCH) {
		return output;
	}
	switch (menu_group) {
	case MENU_0_GENERAL:
		switch (menu_item) {
		case MENU_0_ITEM_LANGUAGE:
			mystrcpy(output.switch_str, STR_JAZYK, SMALL);
			mystrcpy(output.switch_xml, XML_SUPPORTED_LANGUAGES, SMALL);
			mystrcpy(output.switch_name, html_text_Jazyk[_global_jazyk], SMALL);
			break;
		case MENU_0_ITEM_CALENDAR:
			mystrcpy(output.switch_str, STR_KALENDAR, SMALL);
			mystrcpy(output.switch_xml, XML_LIT_CALENDAR_VALUES, SMALL);
			mystrcpy(output.switch_name, html_text_Kalendar[_global_jazyk], SMALL);
			break;
		case GLOBAL_NULL:
		default:
			break;
		} // switch (menu_item)
		break;
	case MENU_1_DEVICE:
		switch (menu_item) {
		case GLOBAL_NULL:
		default:
			break;
		} // switch (menu_item)
		break;
	case MENU_2_LOOK:
		switch (menu_item) {
		case MENU_2_ITEM_FONT:
			mystrcpy(output.switch_str, STR_FONT_NAME, SMALL);
			// no specific XML element
			mystrcpy(output.switch_name, mystr_first_upper(html_text_font_name[_global_jazyk]).c_str(), SMALL);
			break;
		case GLOBAL_NULL:
		default:
			break;
		} // switch (menu_item)
		break;
	case MENU_3_TEXT_CONTENT:
		switch (menu_item) {
		case GLOBAL_NULL:
		default:
			break;
		} // switch (menu_item)
		break;
	case MENU_4_CALENDAR:
		switch (menu_item) {
		case GLOBAL_NULL:
		default:
			break;
		} // switch (menu_item)
		break;
	case MENU_5_TTS:
		switch (menu_item) {
		case GLOBAL_NULL:
		default:
			break;
		} // switch (menu_item)
		break;
	}// switch (menu_group)

	return output;
}// get_switch_for_menu_item()

// returns option and bit opt force for menu items (those of type MENU_ITEM_TYPE_BIT_OPTION)
menu_item_option_str_name get_data_for_menu_item_option(short int menu_group, short int menu_item) {
	menu_item_option_str_name output;
	mystrcpy(output.option_str, STR_EMPTY, SMALL);
	mystrcpy(output.option_force, STR_EMPTY, SMALL);
	mystrcpy(output.option_xml, STR_EMPTY, SMALL);
	mystrcpy(output.option_name, STR_EMPTY, SMALL);

	if (menu_item_type[menu_group][menu_item] != MENU_ITEM_TYPE_BIT_OPTION) {
		return output;
	}
	switch (menu_group) {
	case MENU_0_GENERAL:
		switch (menu_item) {
		case GLOBAL_NULL:
		default:
			break;
		} // switch (menu_item)
		break;
	case MENU_1_DEVICE:
		switch (menu_item) {
		case GLOBAL_NULL:
		default:
			break;
		} // switch (menu_item)
		break;
	case MENU_2_LOOK:
		switch (menu_item) {
		case MENU_2_ITEM_COLOR_SCHEMA:
			mystrcpy(output.option_str, STR_OPT_2, SMALL);
			mystrcpy(output.option_force, STR_FORCE_BIT_OPT_2_NOCNY_REZIM, SMALL);
			mystrcpy(output.option_xml, XML_BIT_OPT_2_NOCNY_REZIM, SMALL);
			mystrcpy(output.option_name, mystr_first_upper(html_text_opt_2_nocny_rezim[_global_jazyk]).c_str(), SMALL);
			break;
		case MENU_2_ITEM_NORMAL_FONT:
			mystrcpy(output.option_str, STR_OPT_0, SMALL);
			mystrcpy(output.option_force, STR_FORCE_BIT_OPT_0_FONT_NORMAL, SMALL);
			mystrcpy(output.option_xml, XML_BIT_OPT_0_FONT_NORMAL, SMALL);
			mystrcpy(output.option_name, mystr_first_upper(html_text_opt_0_font_normal[_global_jazyk]).c_str(), SMALL);
			break;
		case MENU_2_ITEM_ROUNDED_CORNERS:
			mystrcpy(output.option_str, STR_OPT_2, SMALL);
			mystrcpy(output.option_force, STR_FORCE_BIT_OPT_2_ROUNDED_CORNERS, SMALL);
			mystrcpy(output.option_xml, XML_BIT_OPT_2_ROUNDED_CORNERS, SMALL);
			mystrcpy(output.option_name, mystr_first_upper(html_text_opt_2_rounded_corners[_global_jazyk]).c_str(), SMALL);
			break;
		case MENU_2_ITEM_NAVIGATION_ARROWS:
			mystrcpy(output.option_str, STR_OPT_0, SMALL);
			mystrcpy(output.option_force, STR_FORCE_BIT_OPT_0_TRANSPARENT_NAV, SMALL);
			mystrcpy(output.option_xml, XML_BIT_OPT_0_TRANSPARENT_NAV, SMALL);
			mystrcpy(output.option_name, mystr_first_upper(html_text_opt_0_transparent_nav[_global_jazyk]).c_str(), SMALL);
			break;
		case MENU_2_ITEM_NAVIGATION_ARROWS_LEFT:
			mystrcpy(output.option_str, STR_OPT_0, SMALL);
			mystrcpy(output.option_force, STR_FORCE_BIT_OPT_0_TRANSPARENT_NAV_LEFT, SMALL);
			mystrcpy(output.option_xml, XML_BIT_OPT_0_TRANSPARENT_NAV_LEFT, SMALL);
			mystrcpy(output.option_name, mystr_first_upper(html_text_opt_0_transparent_nav_left[_global_jazyk]).c_str(), SMALL);
			break;
		case MENU_2_ITEM_BUTTONS_CONDENSED:
			mystrcpy(output.option_str, STR_OPT_2, SMALL);
			mystrcpy(output.option_force, STR_FORCE_BIT_OPT_2_BUTTONY_USPORNE, SMALL);
			mystrcpy(output.option_xml, XML_BIT_OPT_2_BUTTONY_USPORNE, SMALL);
			mystrcpy(output.option_name, mystr_first_upper(html_text_opt_2_buttons_usporne[_global_jazyk]).c_str(), SMALL);
			break;
		case MENU_2_ITEM_BUTTONS_ORDERING:
			mystrcpy(output.option_str, STR_OPT_0, SMALL);
			mystrcpy(output.option_force, STR_FORCE_BIT_OPT_0_BUTTONS_ORDER, SMALL);
			mystrcpy(output.option_xml, XML_BIT_OPT_0_BUTTONS_ORDER, SMALL);
			mystrcpy(output.option_name, mystr_first_upper(html_text_opt_0_buttons_order[_global_jazyk]).c_str(), SMALL);
			break;
		case MENU_2_ITEM_NAVIGATION_IN_PRAYER:
			mystrcpy(output.option_str, STR_OPT_2, SMALL);
			mystrcpy(output.option_force, STR_FORCE_BIT_OPT_2_NAVIGATION, SMALL);
			mystrcpy(output.option_xml, XML_BIT_OPT_2_NAVIGATION, SMALL);
			mystrcpy(output.option_name, mystr_first_upper(html_text_opt_2_navigation[_global_jazyk]).c_str(), SMALL);
			break;
		case GLOBAL_NULL:
		default:
			break;
		} // switch (menu_item)
		break;
	case MENU_3_TEXT_CONTENT:
		switch (menu_item) {
		case GLOBAL_NULL:
		default:
			break;
		} // switch (menu_item)
		break;
	case MENU_4_CALENDAR:
		switch (menu_item) {
		case GLOBAL_NULL:
		default:
			break;
		} // switch (menu_item)
		break;
	case MENU_5_TTS:
		switch (menu_item) {
		case GLOBAL_NULL:
		default:
			break;
		} // switch (menu_item)
		break;
	}// switch (menu_group)

	return output;
}// get_data_for_menu_item_option()

void xml_export_menu(void) {
	short int i, j, mit;
	menu_item_switch_str_name output1;
	menu_item_option_str_name output2;
	char output3[SMALL];

	Log("-- xml_export_menu() -- začiatok\n");

	Export(ELEM_BEGIN(XML_MENU) "\n");

	for (i = 0; i < POCET_MENU_GROUPS; i++) {
		Export(ELEM_BEGIN_ID_VALUE(XML_MENU_GROUP) "\n", i, text_menu_group(i));
		for (j = 0; j < pocet_menu_items[i]; j++) {

			mit = menu_item_type[i][j];

			switch (mit) {

			case MENU_ITEM_TYPE_MAIN_SWITCH:
				output1 = get_data_for_menu_item_switch(i, j);
				Export(ELEM_BEGIN_ID_TYPE_VALUE_ELEMENT(XML_MENU_ITEM)"%s" ELEM_END(XML_MENU_ITEM) "\n", j, menu_item_type_name[mit], output1.switch_str, output1.switch_xml, output1.switch_name);
				break;

			case MENU_ITEM_TYPE_BIT_OPTION:
				output2 = get_data_for_menu_item_option(i, j);
				Export(ELEM_BEGIN_ID_TYPE_OPTION_VALUE_ELEMENT(XML_MENU_ITEM)"%s" ELEM_END(XML_MENU_ITEM) "\n", j, menu_item_type_name[mit], output2.option_str, output2.option_force, output2.option_xml, output2.option_name);
				break;

			case MENU_ITEM_TYPE_APP_SPECIFIC:
				mystrcpy(output3, get_data_for_menu_item_app_specific(i, j), SMALL);
				Export(ELEM_BEGIN_ID_TYPE(XML_MENU_ITEM)"%s" ELEM_END(XML_MENU_ITEM) "\n", j, menu_item_type_name[mit], output3);
				break;

				// for MENU_ITEM_TYPE_UNDEFINED, do nothing
			}// switch()
		}// for j
		Export(ELEM_END(XML_MENU_GROUP) "\n");
	}// for i

	Export(ELEM_END(XML_MENU)"\n\n");

	Log("-- xml_export_menu() -- koniec\n");
}// xml_export_menu()

void xml_export_options_and_menu(void) {
#ifdef OS_Windows_Ruby
	// ToDo: not yet finished
	xml_export_menu();
#endif
	xml_export_options();
}// xml_export_options_and_menu()

// predpokoladam, ze pred jeho volanim bolo pouzite analyzuj_rok(rok); ktore da vysledok do _global_r
// dostane {den, mesiac} a rok
short int _rozbor_dna_s_modlitbou(_struct_den_mesiac datum, short int rok, short int modlitba, short int poradie_svateho) {
	short int ret;
	Log("-- _rozbor_dna_s_modlitbou(_struct_den_mesiac, int, int, int): begin ({%d, %d}, %d, %s, %d)\n", datum.den, datum.mesiac, rok, nazov_modlitby(modlitba), poradie_svateho);

	Log("vo funkcii _rozbor_dna_s_modlitbou() spustam set_popis_dummy();\n");
	set_popis_dummy();
	Log("set_popis_dummy() skoncila.\n");

	Log("vo funkcii _rozbor_dna_s_modlitbou() spustam _rozbor_dna();\n");
	ret = _rozbor_dna(datum, rok, poradie_svateho);
	if (ret == FAILURE) {
		Log("_rozbor_dna() returned FAILURE, so returning FAILURE...\n");
		return FAILURE;
	}
	Log("_rozbor_dna() skoncila.\n");

	if ((poradie_svateho == PORADIE_PM_SOBOTA) && (_global_den.denvt != DEN_SOBOTA)) {
		Log("(poradie_svateho == %d) && (_global_den.denvt != DEN_SOBOTA), so returning FAILURE...\n", PORADIE_PM_SOBOTA);
		if (query_type == PRM_XML) {
			ExportXmlError((char*)html_error_saturday_VM[_global_jazyk], nazov_dna(_global_den.denvt));
		}
		else {
			ALERT;
			Export((char*)html_error_saturday_VM[_global_jazyk], nazov_dna(_global_den.denvt));
		}
		return FAILURE;
	}
	else if ((poradie_svateho == PORADIE_PM_SOBOTA) && (_global_den.denvt == DEN_SOBOTA) && ((modlitba == MODL_VESPERY) || (modlitba == MODL_KOMPLETORIUM))) {
		// experimentally set poradie_svateho to 0
		// formerly returned FAILURE
		/*
		Log("(poradie_svateho == %d) && (_global_den.denvt != DEN_SOBOTA), so returning FAILURE...\n", PORADIE_PM_SOBOTA);
		ALERT;
		Export("Nemôžete požadovať túto modlitbu, pretože `Spomienka Panny Márie v sobotu' nemá vešpery ani kompletórium.\n");
		return FAILURE;
		*/
		poradie_svateho = 0;
	}
	else if ((poradie_svateho != PORADIE_PM_SOBOTA) && (_global_pocet_svatych < poradie_svateho)) {
		Log("(poradie_svateho != %d) && (_global_pocet_svatych < poradie_svateho), so returning FAILURE...\n", PORADIE_PM_SOBOTA);
		if (query_type == PRM_XML) {
			ExportXmlError((char*)html_error_saints[_global_jazyk], _global_pocet_svatych, poradie_svateho);
		}
		else {
			ALERT;
			Export((char*)html_error_saints[_global_jazyk], _global_pocet_svatych, poradie_svateho);
		}
		return FAILURE;
	}

	// teraz nasleduje niečo, čo nahrádza export -- avšak dáta ukladá do stringu _global_string
	Log("1:spustam init_global_string(EXPORT_DNA_JEDEN_DEN, svaty == %d, modlitba == %s)...\n", poradie_svateho, nazov_modlitby(modlitba));
	ret = init_global_string(EXPORT_DNA_JEDEN_DEN, poradie_svateho, modlitba, /* aj_citanie */ NIE);

	if (ret == FAILURE) {
		Log("init_global_string() returned FAILURE, so returning FAILURE...\n");
		return FAILURE;
	}

	Log("nastavujem _global_string_modlitba... _rozbor_dna_s_modlitbou()\n");
	init_global_string_modlitba(_global_modlitba);
	Log("nastavujem _global_string_podnadpis... _rozbor_dna_s_modlitbou()\n");
	init_global_string_podnadpis(_global_modlitba);
	Log("nastavujem _global_string_spol_cast... _rozbor_dna_s_modlitbou()\n");
	ret_sc = init_global_string_spol_cast(odfiltrujSpolCast(modlitba, _global_opt[OPT_3_SPOLOCNA_CAST]), poradie_svateho);

	// určenie dát k modlitbe
	Log("spustam liturgicke_obdobie(%s, %d. tyzden, %s, %d. tyzden zaltara; svaty: %d)...\n", nazov_obdobia_ext(_global_den.litobd), _global_den.tyzden, nazov_dna(_global_den.denvt), _global_den.tyzzal, poradie_svateho);

	Log("PRED:\t%d. %s %d\n", _global_den.den, nazov_mesiaca(_global_den.mesiac - 1), _global_den.rok);

	liturgicke_obdobie(_global_den.litobd, _global_den.tyzden, _global_den.denvt, _global_den.tyzzal, poradie_svateho);

	Log("PO:\t%d. %s %d\n", _global_den.den, nazov_mesiaca(_global_den.mesiac - 1), _global_den.rok);

	Log("-- _rozbor_dna_s_modlitbou:\n");
	Log("\t%d. %s %d, %s\n", _global_den.den, nazov_mesiaca(_global_den.mesiac - 1), _global_den.rok, _global_string);

	Log("prípadné upravenie _global_opt[OPT_3_SPOLOCNA_CAST] sa realizovalo vo funkcii _rozbor_dna()...\n");

	Log("-- _rozbor_dna_s_modlitbou(_struct_den_mesiac, int, int, int): returning SUCCESS\n");
	return SUCCESS;
} // _rozbor_dna_s_modlitbou()

void Export_HtmlFormGET(char* action) {
	char action_changed[MAX_STR];
	// 1. replace HTML_AMPERSAND "&amp;" to simple "&" char
	mystrcpy(action_changed, mystr_replace(action, HTML_AMPERSAND, "&").c_str(), MAX_STR);
	// 2. export
	Export(HTML_FORM_METHOD_GET, action_changed);
} // Export_HtmlFormGET()

void Export_HtmlFormPOST(char* action) {
	// 1. not necessary to replace HTML_AMPERSAND "&amp;" to simple "&" char
	// 2. export
	Export(HTML_FORM_METHOD_POST, action);
} // Export_HtmlFormPOST()

#ifdef BEHAVIOUR_CMDLINE
#define Export_HtmlForm Export_HtmlFormGET
#else
#define Export_HtmlForm Export_HtmlFormPOST
#endif

void _export_rozbor_dna_button_modlitba(short int typ, short int poradie_svateho, short int modl, char pom[MAX_STR], short int doplnkova_psalmodia, short int som_v_tabulke, short int modl_visible = MODL_NEURCENA) {
	char action[MAX_STR];
	mystrcpy(action, STR_EMPTY, MAX_STR);
	short int orig_doplnkova_psalmodia = doplnkova_psalmodia;
	if (orig_doplnkova_psalmodia == MODL_CEZ_DEN_DOPLNKOVA_PSALMODIA) {
		doplnkova_psalmodia = MODL_CEZ_DEN_ZALMY_ZO_DNA;
	}
	char export_fname_modl_str[SMALL] = STR_EMPTY; // reťazec pre identifikáciu modlitby v názve súboru (ID modlitby alebo char_modlitby[i])

	// generovanie názvu súboru s písmenkom modlitby (default) alebo s ID modlitby
	if (!isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_FNAME_MODL_ID)) {
		sprintf(export_fname_modl_str, "%c", char_modlitby[modl]);
	}
	else {
		sprintf(export_fname_modl_str, "%d", modl);
	}

	// ak nie je nastavená modlitba pre zobrazenie (napr. druhé vešpery), použije sa vstup modl (default správanie)
	if (modl_visible == MODL_NEURCENA) {
		modl_visible = modl;
		Log("modl_visible zmenená (default na modl == %s)...\n", nazov_modlitby(modl));
	}
	else {
		Log("modl_visible == %s...\n", nazov_modlitby(modl_visible));
	}

	if (query_type == PRM_LIT_OBD) {
		Log("pre query_type == PRM_LIT_OBD sa buttony pre modlitby tlačia ináč (nemám nastavený dátum)...\n");
		// predpokladáme, že máme _global_linky == ANO
		sprintf(action, "%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%c" HTML_AMPERSAND "%s=%s%s",
			script_name,
			STR_QUERY_TYPE, STR_PRM_LIT_OBD,
			STR_DEN_V_TYZDNI, _global_den.denvt,
			STR_TYZDEN, _global_den.tyzden,
			STR_LIT_OBD, _global_den.litobd,
			STR_LIT_ROK, _global_den.litrok,
			STR_MODLITBA, str_modlitby[modl],
			pom);
		Export_HtmlForm(action);
	}// query_type == PRM_LIT_OBD
	else {
		if (_global_linky == ANO) {
			sprintf(action, "%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%s%s",
				script_name,
				STR_QUERY_TYPE, STR_PRM_DATUM,
				STR_DEN, _global_den.den,
				STR_MESIAC, _global_den.mesiac,
				STR_ROK, _global_den.rok,
				STR_MODLITBA, str_modlitby[modl],
				pom);
			Export_HtmlForm(action);
		}
		else {
			if (typ == EXPORT_DNA_JEDEN_DEN_LOCAL) {
				sprintf(pom, "#m-%c", char_modlitby[modl_visible]);
			}
			else if (_global_opt_batch_monthly == ANO) {
				if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
					sprintf(pom, FILENAME_EXPORT_DATE_SIMPLE"_%d%s%s", _global_den.rok % 100, _global_den.mesiac, _global_den.den, poradie_svateho, export_fname_modl_str /* char_modlitby[modl] */, doplnkova_psalmodia == MODL_CEZ_DEN_ZALMY_ZO_DNA ? ".htm" : "d.htm");
				}
				else {
					sprintf(pom, FILENAME_EXPORT_DATE_FULL"_%d%s%s", _global_den.rok, _global_den.mesiac, _global_den.den, poradie_svateho, export_fname_modl_str /* char_modlitby[modl] */, doplnkova_psalmodia == MODL_CEZ_DEN_ZALMY_ZO_DNA ? ".htm" : "d.htm");
				}
			}
			Log("\treťazec pom == %s; doplnkova_psalmodia == %d\n", pom, doplnkova_psalmodia);

			if ((doplnkova_psalmodia != MODL_CEZ_DEN_DOPLNKOVA_PSALMODIA)) {
				if ((som_v_tabulke == ANO) && (typ != EXPORT_DNA_JEDEN_DEN_LOCAL)) {
					Export_HtmlForm(pom);
				}
				else {
					Export("%s" HTML_A_HREF_BEGIN "\"%s\"%s>\n", optional_html_line_break, pom, optional_html_class_button);
					Export("%s", optional_html_button_prayer_begin);
				}
			}
		}
	}// !(query_type == PRM_LIT_OBD)

	if ((som_v_tabulke == ANO) && (typ != EXPORT_DNA_JEDEN_DEN_LOCAL)) {
		Export(HTML_FORM_INPUT_SUBMIT_PRAYER" title=\"%s\" value=\"", nazov_modlitby(modl_visible));
		ExportStringCharByChar(mystr_replace_char((char *)html_button_nazov_modlitby(modl_visible), CHAR_SPACE, CHAR_NONBREAKING_SPACE).c_str(), isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT));
		Export("\"" HTML_FORM_INPUT_END "\n");
		Export("</form>\n");
	}
	else {
		if (typ == EXPORT_DNA_JEDEN_DEN_LOCAL) {
			ExportStringCharByChar(mystr_replace_char((char *)html_button_nazov_modlitby(modl_visible), CHAR_SPACE, CHAR_NONBREAKING_SPACE).c_str(), isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT));
		}
		else {
			Export("%s", nazov_modlitby(modl_visible));
		}
		Export("%s", optional_html_button_end);
		Export(HTML_A_END"\n");
	}

	// only for command-line export (BEHAVIOUR_CMDLINE)
#ifndef BEHAVIOUR_WEB
	if (orig_doplnkova_psalmodia == MODL_CEZ_DEN_DOPLNKOVA_PSALMODIA) {
		doplnkova_psalmodia = orig_doplnkova_psalmodia;
		if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA)) {
			if (typ == EXPORT_DNA_JEDEN_DEN_LOCAL) {
				sprintf(pom, "#m-%c", char_modlitby[modl_visible]);
			}
			else if (_global_opt_batch_monthly == ANO) {
				if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
					sprintf(pom, FILENAME_EXPORT_DATE_SIMPLE"_%d%s%s", _global_den.rok % 100, _global_den.mesiac, _global_den.den, poradie_svateho, export_fname_modl_str /* char_modlitby[modl] */, doplnkova_psalmodia == MODL_CEZ_DEN_ZALMY_ZO_DNA ? ".htm" : "d.htm");
				}
				else {
					sprintf(pom, FILENAME_EXPORT_DATE_FULL"_%d%s%s", _global_den.rok, _global_den.mesiac, _global_den.den, poradie_svateho, export_fname_modl_str /* char_modlitby[modl] */, doplnkova_psalmodia == MODL_CEZ_DEN_ZALMY_ZO_DNA ? ".htm" : "d.htm");
				}
			}
			Log("\treťazec pom == %s; doplnkova_psalmodia == %d\n", pom, doplnkova_psalmodia);

			if ((som_v_tabulke == ANO) && (typ != EXPORT_DNA_JEDEN_DEN_LOCAL)) {
				Export_HtmlForm(pom);
			}
			else {
				Export("%s" HTML_A_HREF_BEGIN "\"%s\"%s>\n", optional_html_line_break, pom, optional_html_class_button);
				Export("%s", optional_html_button_prayer_begin);
			}

			if ((som_v_tabulke == ANO) && (typ != EXPORT_DNA_JEDEN_DEN_LOCAL)) {
				Export(HTML_FORM_INPUT_SUBMIT" title=\"%s (%s)\" value=\"", nazov_modlitby(modl), str_doplnkova_psalmodia[_global_jazyk]);
				Export("(alt)"); // alternatíva s doplnkovou psalmódiou [prípadne neskôr doriešiť krajšie]
				Export("\"" HTML_FORM_INPUT_END "\n");
				Export("</form>\n");
			}
			else {
				Export("(alt)"); // alternatíva s doplnkovou psalmódiou [prípadne neskôr doriešiť krajšie]
				Export("%s", optional_html_button_end);
				Export(HTML_A_END"\n");
			}
		}// alternatíva s doplnkovou psalmódiou
	}// orig_doplnkova_psalmodia == MODL_CEZ_DEN_DOPLNKOVA_PSALMODIA
#endif
} // _export_rozbor_dna_button_modlitba();

void _export_rozbor_dna_button_modlitba2(short int modl, char pom[MAX_STR]) {
	char action[MAX_STR];
	mystrcpy(action, STR_EMPTY, MAX_STR);
	if ((query_type == PRM_LIT_OBD) && (modl == MODL_VSETKY)) {
		Log("pre query_type == PRM_LIT_OBD button pre všetky modlitby ešte nie je implementovaný | button for all prayers is not implemented yet\n");
		// ToDo
		return;
	}
	// kvôli buttonom "Detaily..." a "všetky" (všetky modlitby)
	if (query_type == PRM_LIT_OBD) {
		Log("pre query_type == PRM_LIT_OBD sa buttony pre modlitby tlačia ináč (nemám nastavený dátum)...\n");
		// predpokladáme, že máme _global_linky == ANO
		sprintf(action, "%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%c" HTML_AMPERSAND "%s=%s%s",
			script_name,
			STR_QUERY_TYPE, STR_PRM_LIT_OBD,
			STR_DEN_V_TYZDNI, _global_den.denvt,
			STR_TYZDEN, _global_den.tyzden,
			STR_LIT_OBD, _global_den.litobd,
			STR_LIT_ROK, _global_den.litrok,
			STR_MODLITBA, str_modlitby[modl],
			pom);
	}// query_type == PRM_LIT_OBD
	else {
		Log("query_type != PRM_LIT_OBD, buttony sa teda pre modlitby tlačia klasicky (STR_PRM_DETAILY alebo STR_PRM_DATUM)...\n");
		sprintf(action, "%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%s%s",
			script_name,
			STR_QUERY_TYPE, (modl == MODL_DETAILY) ? STR_PRM_DETAILY : STR_PRM_DATUM,
			STR_DEN, _global_den.den,
			STR_MESIAC, _global_den.mesiac,
			STR_ROK, _global_den.rok,
			STR_MODLITBA, str_modlitby[modl],
			pom);
	}// !(query_type == PRM_LIT_OBD)
	Export_HtmlForm(action);
	Export(HTML_FORM_INPUT_SUBMIT2" title=\"%s\" value=\"", nazov_modlitby(modl));
	ExportStringCharByChar(mystr_replace_char((char *)html_button_nazov_modlitby(modl), CHAR_SPACE, CHAR_NONBREAKING_SPACE).c_str(), isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT));
	Export("\"" HTML_FORM_INPUT_END "\n");
	Export("</form>\n");
}// _export_rozbor_dna_button_modlitba2

short int ma_na_vyber_spolocne_casti(short int poradie_svateho) {
	// 2011-10-03: vytvorené
	short int ret = NIE;
	_struct_sc sc;
	sc.a1 = MODL_SPOL_CAST_NEURCENA;
	sc.a2 = MODL_SPOL_CAST_NEURCENA;
	sc.a3 = MODL_SPOL_CAST_NEURCENA;

	Log("ma_na_vyber_spolocne_casti(%d) -- začiatok...\n", poradie_svateho);

	if (poradie_svateho == PORADIE_PM_SOBOTA) {
		sc.a1 = MODL_SPOL_CAST_PANNA_MARIA;
	}
	else if (poradie_svateho > 0) {
		sc = _decode_spol_cast(_global_svaty(poradie_svateho).spolcast);
	}

	if (je_spolocna_cast_urcena(sc.a1)) { // stačí, že má jednu spoločnú časť nastavenú
		ret = ANO;
	}
	Log("ma_na_vyber_spolocne_casti(%d) -- koniec: %d.\n", poradie_svateho, ret);
	return ret;
} // ma_na_vyber_spolocne_casti();

// typ - ako v _export_rozbor_dna()
//
// exportuje buttony pre _export_rozbor_dna()
// int poradie_svateho: ak je 2 alebo 3, znamena to, ze ide o druheho resp. tretieho svateho (ked je viac ako 1 lubovolna spomienka) -- v takom pripade este pridavame premennu STR_DALSI_SVATY s hodnotou 2 resp. 3
// 2011-07-03: pridaný parameter, či chce tlačiť liturgickú farbu (použitie v navigácii)
void _export_rozbor_dna_buttons(short int typ, short int poradie_svateho, short int den_zoznam, short int zobrazit_mcd) {
	// 2005-03-21: Pridany dalsi typ exportu 
	// 2009-08-11: pre tento typ exportu berieme do úvahy parameter 'M'
	// 2011-10-03: predsunutá časť, ktorá bola súčasťou #define BUTTONS
	Log("--- _export_rozbor_dna_buttons(typ == %d) -- begin\n", typ);
#ifdef OS_Windows_Ruby
	if ((typ != EXPORT_DNA_VIAC_DNI_TXT) && (typ != EXPORT_DNA_XML)) {
		ExportHtmlComment("buttons:begin");
	}
#endif

	short int i = MODL_NEURCENA;
	short int smer = SLAV_NEURCENE;
	char pom[MAX_STR];
	char pom2[MAX_STR];

	mystrcpy(pom, STR_EMPTY, MAX_STR);
	mystrcpy(pom2, STR_EMPTY, MAX_STR);

	short int som_v_tabulke = ANO; // či sa používa tabuľka; bežne pre web áno, pre export pre mobilné zariadenia [export_monthly_druh >= 3] netreba tabuľku

	short int _pom_den = _global_den.den;
	short int _pom_mesiac = _global_den.mesiac;
	short int _pom_rok = _global_den.rok;

	short int su_prve_vespery = NIE; // pomocná premenná, do ktorej sa uloží, či sa exportovali aj buttony pre prvé vešpery a prvé kompletórium; podľa toho sa potom zmení label pre druhé vešpery

	// XML export -- začiatok daného slávenia
	if (typ == EXPORT_DNA_XML) {
		Export(ELEM_BEGIN_ID(XML_CELEBRATION) "\n", poradie_svateho);
		Export(ELEM_BEGIN(XML_CELEBRATION_ID)"%d" ELEM_END(XML_CELEBRATION_ID) "\n", poradie_svateho); // pre istotu duplikovanie :)
	}

	// BEGIN: časť podľa #define BUTTONS (len pre volania, kde bolo použité BUTTONS, t. j. den_zoznam == ANO)
	if (den_zoznam == ANO) {

		if ((typ != EXPORT_DNA_VIAC_DNI_TXT) && (typ != EXPORT_DNA_XML)) {
			Export("\n"); // presunuté sem z nasledujúceho if-u
		}
		if (typ == EXPORT_DNA_XML) {
			Export(ELEM_BEGIN(XML_STRING_TITLE));
		}
		else {
			ExportHtmlComment("BEGIN:_global_string");
		}

		init_global_string(typ, poradie_svateho, MODL_NEURCENA, /* aj_citanie */ ((den_zoznam == ANO) && ((typ == EXPORT_DNA_JEDEN_DEN) || (typ == EXPORT_DNA_JEDEN_DEN_LOCAL) || (typ == EXPORT_DNA_DNES))) ? ANO : NIE);

		if (typ == EXPORT_DNA_VIAC_DNI_TXT) {
			Export("\"");
		}

		Export("%s", _global_string);

		if (typ == EXPORT_DNA_XML) {
			Export(ELEM_END(XML_STRING_TITLE));
		}
		else {
			ExportHtmlComment("END:_global_string");
		}

		if (typ == EXPORT_DNA_VIAC_DNI_TXT) {
			Export("\"; ");
		}
		else {
			Export("\n"); // presunuté sem z predošlého if-u
		}

		if (typ != EXPORT_DNA_VIAC_DNI_TXT) {
			Log("  _global_opt[OPT_1_CASTI_MODLITBY] & BIT_OPT_1_ZOBRAZ_SPOL_CAST: %d: (voice output: %d)\n", isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZOBRAZ_SPOL_CAST), isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT));

			if (useWhenGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZOBRAZ_SPOL_CAST)) {
				ret_sc = init_global_string_spol_cast(MODL_SPOL_CAST_NULL, poradie_svateho);
				Log("including SPOL_CAST\n");
				if (!equals(_global_string_spol_cast, STR_EMPTY)) {
					Export(HTML_LINE_BREAK);
					if (typ == EXPORT_DNA_XML) {
						Export(ELEM_BEGIN(XML_STRING_COMMUNIA));
					}
					else {
						ExportHtmlComment("BEGIN:_global_string_spol_cast");
					}
					_export_global_string_spol_cast(NIE);
					if (typ == EXPORT_DNA_XML) {
						Export(ELEM_END(XML_STRING_COMMUNIA) "\n");
					}
					else {
						ExportHtmlComment("END:_global_string_spol_cast");
					}
				}// if (!equals(_global_string_spol_cast, STR_EMPTY))
			}// if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZOBRAZ_SPOL_CAST))
		}
	}// if (den_zoznam == ANO)
	// END: časť podľa #define BUTTONS

	if (typ == EXPORT_DNA_XML) {
		som_v_tabulke = NIE;
		// ďalšie vlastnosti z "_global_den"; používa sa globálne definovaná _struct_dm _local_den; nastavená vo funkcii init_global_string()
		Export(ELEM_BEGIN(XML_LIT_YEAR_LETTER)"%c" ELEM_END(XML_LIT_YEAR_LETTER) "\n", _local_den.litrok);
		Export(ELEM_BEGIN(XML_LIT_WEEK)"%d" ELEM_END(XML_LIT_WEEK) "\n", _local_den.tyzden);
		Export(ELEM_BEGIN(XML_LIT_WEEK_PSALT)"%d" ELEM_END(XML_LIT_WEEK_PSALT) "\n", _local_den.tyzzal);
		Export(ELEM_BEGIN_ID(XML_LIT_SEASON)"%s" ELEM_END(XML_LIT_SEASON) "\n", _local_den.litobd, nazov_obdobia(_local_den.litobd));
		Export(ELEM_BEGIN_ID(XML_LIT_TYPE)"%s" ELEM_END(XML_LIT_TYPE) "\n", _local_den.typslav, nazov_slavenia(_local_den.typslav));
		Export(ELEM_BEGIN(XML_LIT_TYPE_LOCAL)"%s" ELEM_END(XML_LIT_TYPE_LOCAL) "\n", NAZOV_SLAVENIA_LOKAL_LOCAL_DEN_TYPSLAV_LOKAL);
		Export(ELEM_BEGIN(XML_LIT_LEVEL)"%d" ELEM_END(XML_LIT_LEVEL) "\n", _local_den.smer);
		Export(ELEM_BEGIN(XML_LIT_REQUIRED)"%d" ELEM_END(XML_LIT_REQUIRED) "\n", _local_den.prik);
		xml_export_spol_cast(poradie_svateho);
		Export(ELEM_BEGIN(XML_LIT_NAME)"%s" ELEM_END(XML_LIT_NAME) "\n", _local_den.meno);
		xml_export_liturgicka_farba();
		if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_CZ)) {
			Export(ELEM_BEGIN(XML_LIT_CALENDAR)"%s" ELEM_END(XML_LIT_CALENDAR) "\n", nazov_kalendara_short[_local_den.kalendar]);
		}
		Export(ELEM_BEGIN(XML_LIT_READINGS)"%s" ELEM_END(XML_LIT_READINGS) "\n", _local_den.lc_str_id);
	}

	if (den_zoznam != ANO) {
		// pre tlačidlá predošlého a nasledujúceho dňa pre navigáciu v modlitbe treba použiť iný dátum ako _global_den, nakoľko pre vešpery v predvečer nedele resp. slávnosti sa dátum posunul o jeden deň...
		// ExportHtmlComment("úprava _global_den na: den %d | mesiac %d | rok %d", _global_vstup_den, _global_vstup_mesiac, _global_vstup_rok);
		_global_den.den = _global_vstup_den;
		_global_den.mesiac = _global_vstup_mesiac;
		_global_den.rok = _global_vstup_rok;
	}

	if (PODMIENKA_JE_BATCH_MODE_MONTHLY__AND__PLAIN_EXPORT) {
		som_v_tabulke = NIE;
		Log("-- _export_rozbor_dna_buttons(typ == %d): keďže sme v _global_opt_batch_monthly == ANO a export_monthly_druh (%d) > 2, nebudeme exportovať tabuľku...\n", typ, export_monthly_druh);
	}

	if (typ == EXPORT_DNA_VIAC_DNI_TXT) {
		som_v_tabulke = NIE;
		Log("-- _export_rozbor_dna_buttons(typ == %d): kvôli typu nebudeme exportovať tabuľku...\n", typ);
	}

	if ((typ != EXPORT_DNA_VIAC_DNI) && (typ != EXPORT_DNA_VIAC_DNI_SIMPLE) && (typ != EXPORT_DNA_VIAC_DNI_TXT) && (typ != EXPORT_DNA_XML)) {
		Log("--- _export_rozbor_dna_buttons(): idem tlačiť buttony...\n");

		Export("\n");

		if (_global_opt_batch_monthly == NIE) {
			// tlacidla niekedy linkuju iba subor, nie linku: podla _global_linky
			if (_global_linky == ANO) {
				if (poradie_svateho > 0) {
					sprintf(pom, HTML_AMPERSAND"%s=%d", STR_DALSI_SVATY, poradie_svateho);
				}// poradie_svateho > 0
				else {
					mystrcpy(pom, STR_EMPTY, MAX_STR);
				}// !(poradie_svateho > 0)
			}
			else {// nezobrazovat linky
				if ((poradie_svateho >= UNKNOWN_PORADIE_SVATEHO) && (poradie_svateho < 5)) { // snáď OK: UNKNOWN_PORADIE_SVATEHO (bolo tu: poradie_svateho >= 0)
					sprintf(pom, "%s%d.htm", FILE_NAME_POKEC, poradie_svateho);
				}
				else {
					mystrcpy(pom, FILE_NAME_CHYBA, MAX_STR);
				}
			}

			prilep_request_options(pom, pom2);

		}// if (_global_opt_batch_monthly == NIE)
		else {
			mystrcpy(pom, STR_EMPTY, MAX_STR);
			// bude sa nastavovať na príslušnom mieste
		}// else if (_global_opt_batch_monthly == NIE)

		if (den_zoznam == ANO) {
			// liturgická farba - pre buttons je treba v každom riadku; je možnosť explicitne neeexportovať farbu
			if (som_v_tabulke == ANO) {
				Export(HTML_TABLE_CELL_END "\n");

				ExportEmptyCell();

				ExportTableCell(HTML_TABLE_CELL);

				ExportHtmlComment("_global_string_farba(1)");
			}

			Export("%s", _global_string_farba);

			if (som_v_tabulke == ANO) {
				Export(HTML_TABLE_CELL_END "\n");

				ExportEmptyCell(ANO, NIE); // empty table cell... ended below in "oddelenie (1)"
			}
		}// den_zoznam == ANO

		// oddelenie (1)
		if (som_v_tabulke == ANO) {
			Export(HTML_TABLE_CELL_END "\n");
		}

		if (den_zoznam == ANO) {
			ExportHtmlComment("buttony/tabuľka s buttonmi pre jednotlivé modlitby riadka v rámci dňa");
		}
		else {
			ExportHtmlComment("buttony/tabuľka s buttonmi pre jednotlivé modlitby zvoleného slávenia dňa");
		}

		// oddelenie (2)
		if (som_v_tabulke == ANO) {
			ExportTableCell(HTML_TABLE_CELL);
		}

		// nový element (ďalšia tabuľka)
		if ((som_v_tabulke == ANO) && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTONY_USPORNE))) {
			// ukončenie riadka
			Export(HTML_TABLE_CELL_END "\n");
			Export(HTML_TABLE_ROW_END "\n");

			ExportHtmlComment("table-end-1");
			Export(HTML_TABLE_END "\n");

			Export("<" HTML_TABLE ">\n");

			// nový riadok, v ktorom bude jediná bunka s tabuľkou // was colspan="6" | ToDo solve with sophisticated <div> structure
			Export("<" HTML_TABLE_ROW ">\n");
			ExportTableCell(HTML_TABLE_CELL);

			// tabuľka -- začiatok
			ExportHtmlComment("BEGIN:úsporné zobrazenie v tabuľke");
			Export("<" HTML_TABLE ">\n");
		}

		// doplnené "prvé vešpery"; môžu byť pre smer < 5 ale nie pre všetky dni, preto táto podmienka...
		// ToDo: doriešiť pre všelijaké špeciálne "konflikty", napr. 8. apríl 2013 (presunutá slávnosť Zvestovania Pána na pondelok po Veľkonočnej oktáve) -- má mať prvé vešpery? a pod.
		if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY)) {

			Log("isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY)...\n");

			smer = _global_den_smer_override;

			if (JE_PORADIE_SVATY_OK(poradie_svateho)) {
				smer = (smer > _global_svaty_i_smer_override(poradie_svateho)) ? _global_svaty_i_smer_override(poradie_svateho) : smer;
			}

			if ((
				// č. 11: slávnosti su zvlášť význačnými dňami. ich slávenie sa začína prvými vešperami v predchádzajúci deň
				(smer < 5)
				// č. 13: sviatky sa slávia v rozsahu jedného dňa, a preto nemajú prvé vešpery, ak len nejde o sviatky Pána, ktoré pripadajú na Cezročnú neďelu a na nedeľu vo Vianočnom období a nahradzujú nedeľňajšiu liturgiu hodín
				|| ((smer == 5) && (_global_den.denvt == DEN_NEDELA) && ((_global_den.litobd == OBD_CEZ_ROK) || je_vianocne(_global_den.litobd)))
				// nedeľa
				|| (_global_den.denvt == DEN_NEDELA)
				// č. 61
				|| (
				((_global_den.litobd == OBD_VELKONOCNA_OKTAVA) && (_global_den.denvt == DEN_SOBOTA)) // 2. velkonocna nedela
					|| ((_global_den.mesiac - 1 == MES_DEC) && (_global_den.den == 25)) // ked narodenie pana pripadne na pondelok, tak prve vespery maju prednost pred 4. adventnou nedelou; napr. rok 2000
					)
				)
				&& !(
					// a nie je to špeciálny deň
					((_global_den.denvr <= VELKONOCNA_NEDELA + 6) && (_global_den.denvr >= KVETNA_NEDELA + 1)) // všedné dni svätého týždňa počnúc pondelkom, veľkonočné trojdnie od veľkého piatka do veľkonočnej oktávy, soboty
					|| (_global_den.denvr == POPOLCOVA_STREDA) // Popolcová streda
					|| ((_global_den.denvt != DEN_NEDELA) && (_global_den.den == 2) && (_global_den.mesiac == MES_NOV + 1)) // 02NOV: Spomienka na všetkých verných zosnulých, ktorá nepadla na nedeľu
					|| (_global_den.denvr == SV_RODINY && (_global_den.den == 26))	// pre sviatky Pána vo Vianočnom období treba doriešiť prípad, že Nedeľa Svätej rodiny padne na 26.12., teda na deň bezprostredne nasledujúci po slávnosti Narodenia Pána
				)
			) {
				// oddelenie riadka
				if ((som_v_tabulke == ANO) && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTONY_USPORNE))) {
					ExportHtmlComment("table-row");

					Export("<" HTML_TABLE_ROW ">\n");
					ExportTableCell(HTML_TABLE_CELL_PRAYER);
				}

				// prvé vešpery, len pre tie modlitby, ktoré môžu mať prvé vešpery
				// prvé vešpery -- button
				i = MODL_PRVE_VESPERY;
				_export_rozbor_dna_button_modlitba(typ, poradie_svateho, i, pom, /* doplnkova_psalmodia */ NIE, som_v_tabulke);

				// oddelenie
				if (som_v_tabulke == ANO) {
					Export(HTML_TABLE_CELL_END "\n");
					ExportTableCell(HTML_TABLE_CELL_PRAYER);
				}

				// kompletórium po prvých vešperách -- button
				i = MODL_PRVE_KOMPLETORIUM;
				_export_rozbor_dna_button_modlitba(typ, poradie_svateho, i, pom, /* doplnkova_psalmodia */ NIE, som_v_tabulke);

				// oddelenie riadka
				if ((som_v_tabulke == ANO) && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTONY_USPORNE))) {
					Export(HTML_TABLE_CELL_END "\n");
					Export(HTML_TABLE_ROW_END "\n");
				}

				su_prve_vespery = ANO; // aby sa pri normálnych vešperách (v ďalšom) vedelo, že to sú "druhé vešpery"

			}// if (_global_den.smer -> smer < 5)...
			else {
				Log("nemôžu byť prvé vešpery (smer == %d, denvt == %d, denvr == %d, VELKONOCNA_NEDELA == %d, KVETNA_NEDELA == %d, POPOLCOVA_STREDA == %d)...\n", _global_den.smer, _global_den.denvt, _global_den.denvr, VELKONOCNA_NEDELA, KVETNA_NEDELA, POPOLCOVA_STREDA);
				// oddelenie
				if (som_v_tabulke == ANO) {
					if (!isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTONY_USPORNE)) {
						Export(HTML_TABLE_CELL_END "\n");
						ExportTableCell(HTML_TABLE_CELL_PRAYER);
					}
				}
			}
		}// isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY)

		// oddelenie
		if (som_v_tabulke == ANO) {
			if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTONY_USPORNE)) {
				ExportHtmlComment("table-row");

				Export("<" HTML_TABLE_ROW ">\n");
			}
			else {
				Export(HTML_TABLE_CELL_END "\n");
			}
			ExportTableCell(HTML_TABLE_CELL_PRAYER);
		}

		// invitatórium -- button
		i = MODL_INVITATORIUM;
		_export_rozbor_dna_button_modlitba(typ, poradie_svateho, i, pom, /* doplnkova_psalmodia */ NIE, som_v_tabulke);

		// oddelenie
		if (som_v_tabulke == ANO) {
			Export(HTML_TABLE_CELL_END "\n");
			ExportTableCell(HTML_TABLE_CELL_PRAYER);
		}

		// modlitba posvätného čítania -- button
		i = MODL_POSV_CITANIE;
		_export_rozbor_dna_button_modlitba(typ, poradie_svateho, i, pom, /* doplnkova_psalmodia */ NIE, som_v_tabulke);
		// posvätné čítanie predsunuté pred ranné chvály

		// oddelenie
		if (som_v_tabulke == ANO) {
			Export(HTML_TABLE_CELL_END "\n");
			ExportTableCell(HTML_TABLE_CELL_PRAYER);
		}

		// ranné chvály -- button
		i = MODL_RANNE_CHVALY;
		_export_rozbor_dna_button_modlitba(typ, poradie_svateho, i, pom, /* doplnkova_psalmodia */ NIE, som_v_tabulke);

		// oddelenie
		if (som_v_tabulke == ANO) {
			Export(HTML_TABLE_CELL_END "\n");

			if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTONY_USPORNE)) {
				Export(HTML_TABLE_ROW_END "\n");

				ExportHtmlComment("table-row");

				Export("<" HTML_TABLE_ROW ">\n");
			}

			ExportTableCell(HTML_TABLE_CELL_PRAYER);
		}

		// zobraziť buttony pre modlitbu cez deň + kompletórium len ak nejde o ľubovoľnú spomienku (vtedy nemajú význam)
		if ((zobrazit_mcd == ANO) || (poradie_svateho == 0)) {

			// modlitba cez deň (predpoludním) -- button
			i = MODL_PREDPOLUDNIM;
			_export_rozbor_dna_button_modlitba(typ, poradie_svateho, i, pom, /* doplnkova_psalmodia */ ANO, som_v_tabulke);

			// oddelenie
			if (som_v_tabulke == ANO) {
				Export(HTML_TABLE_CELL_END "\n");
				ExportTableCell(HTML_TABLE_CELL_PRAYER);
			}

			// modlitba cez deň (napoludnie) -- button
			i = MODL_NAPOLUDNIE;
			_export_rozbor_dna_button_modlitba(typ, poradie_svateho, i, pom, /* doplnkova_psalmodia */ ANO, som_v_tabulke);

			// oddelenie
			if (som_v_tabulke == ANO) {
				Export(HTML_TABLE_CELL_END "\n");
				ExportTableCell(HTML_TABLE_CELL_PRAYER);
			}

			// modlitba cez deň (popoludní) -- button
			i = MODL_POPOLUDNI;
			_export_rozbor_dna_button_modlitba(typ, poradie_svateho, i, pom, /* doplnkova_psalmodia */ ANO, som_v_tabulke);

			// oddelenie
			if (som_v_tabulke == ANO) {
				Export(HTML_TABLE_CELL_END "\n");

				if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTONY_USPORNE)) {
					Export(HTML_TABLE_ROW_END "\n");

					ExportHtmlComment("table-row");

					Export("<" HTML_TABLE_ROW ">\n");
				}

				ExportTableCell(HTML_TABLE_CELL_PRAYER);
			}

		}// zobraziť buttony pre modlitbu cez deň + kompletórium
		else {
			// pre "neúsporné" zobrazenie treba kvôli zarovnaniu doplniť prázdne 3 bunky tabuľky
			if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTONY_USPORNE)) {
				ExportHtmlComment("nezobraziť MCD");
			}
			else {
				if (som_v_tabulke == ANO) {
					ExportEmptyCell(NIE, ANO); // empty table cell (just content & end)

					ExportEmptyCell();

					ExportEmptyCell();

					ExportTableCell(HTML_TABLE_CELL_PRAYER);
				}
			}
		}// NEzobraziť buttony pre modlitbu cez deň + kompletórium

		Log("poradie_svateho == %d...\n", poradie_svateho);
		if (JE_PORADIE_SVATY_OK(poradie_svateho)) {
			Log("_je_global_svaty_i_slavnost(poradie_svateho) == %d...\n", _je_global_svaty_i_slavnost(poradie_svateho));
		}
		Log("isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY) == %d...\n", isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY));
		Log("PODMIENKA_SVIATKY_PANA_SVATYCH_PREDNOST_PRED_NEDELOU_OCR == %d...\n", PODMIENKA_SVIATKY_PANA_SVATYCH_PREDNOST_PRED_NEDELOU_OCR);
		Log("nie_su_vespery == %d...\n", nie_su_vespery);

		// spomienka Panny Márie v sobotu nemá vešpery (ani kompletórium po nich)
		// ak je isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY), zobrazujú sa prvé vešpery pre nedele a slávnosti priamo pre tie dni
		// vešpery a kompletórium nemá zmysel zobrazovať, ak ide o sobotu a ďalšieho svätého (pri viacerých ľubovoľných spomienkach) -- iba ak by šlo o lokálnu slávnosť
		// zavedené "nie_su_vespery" kvôli Bielej (veľkej) sobote
		// (druhé) vešpery sa musia zobrazovať pre sviatky Pána mimo nedele
		if (
			(poradie_svateho != PORADIE_PM_SOBOTA) // odlišná modlitba ako spomienka panny márie v sobotu

			&& !(
				// neplatí žiadna podmienka nižšie
				(isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY)) // zobrazuj prvé vešpery + prvé kompletórium v deň slávenia
				&& (nie_su_vespery) // nie sú vešpery -- špecialita pre Svätú sobotu (Bielu sobotu)
				&& !(PODMIENKA_SVIATKY_PANA_SVATYCH_PREDNOST_PRED_NEDELOU_OCR || _je_global_svaty_i_slavnost(poradie_svateho)) // nie je to sviatok Pána, čo má prednosť pred OCR nedeľou, alebo to nie je lokálna slávnosť
				)

			&& (
				(zobrazit_mcd == ANO) // majú sa zobrazovať mcd
				|| _je_global_svaty_i_slavnost(poradie_svateho) // je to (hoci lokálna) slávnosť
				|| (_global_den.denvt != DEN_SOBOTA) // nie je to sobota
				|| (poradie_svateho == 0)) // alebo je to základné slávenie
			) {
			// vešpery -- button
			i = MODL_VESPERY;
			_export_rozbor_dna_button_modlitba(typ, poradie_svateho, i, pom, /* doplnkova_psalmodia */ NIE, som_v_tabulke, (su_prve_vespery == ANO) ? MODL_DRUHE_VESPERY : i);

			// oddelenie
			if (som_v_tabulke == ANO) {
				Export(HTML_TABLE_CELL_END "\n");
				ExportTableCell(HTML_TABLE_CELL_PRAYER);
			}

			// zobraziť buttony pre modlitbu cez deň + kompletórium len ak nejde o ľubovoľnú spomienku (vtedy nemajú význam)
			if ((zobrazit_mcd == ANO) || (poradie_svateho == 0)) {
				// kompletórium -- button
				i = MODL_KOMPLETORIUM;
				_export_rozbor_dna_button_modlitba(typ, poradie_svateho, i, pom, /* doplnkova_psalmodia */ NIE, som_v_tabulke, (su_prve_vespery == ANO) ? MODL_DRUHE_KOMPLETORIUM : i);
			}// zobraziť buttony pre modlitbu cez deň + kompletórium
			else {
				ExportHtmlComment("nezobraziť kompletórium");
			}// NEzobraziť buttony pre modlitbu cez deň + kompletórium
		}// if (poradie_svateho != PORADIE_PM_SOBOTA) &&...
		else {
			if (som_v_tabulke == ANO) {
				Export(HTML_TABLE_CELL_END "\n");
				ExportTableCell(HTML_TABLE_CELL_PRAYER);
			}
		}// prázdne odsadenie

#define ZOBRAZ_BUTTON_VSETKY_MODLITBY
#ifdef ZOBRAZ_BUTTON_VSETKY_MODLITBY
		// oddelenie
		if (som_v_tabulke == ANO) {
			Export(HTML_TABLE_CELL_END "\n");

			if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTONY_USPORNE)) {
				Export(HTML_TABLE_ROW_END "\n");

				ExportHtmlComment("table-row");

				Export("<" HTML_TABLE_ROW ">\n");
			}

			ExportTableCell(HTML_TABLE_CELL_PRAYER);
		}

		// button 'Všetky modlitby...'
		i = MODL_VSETKY;
		if (_global_linky == ANO) {
			_export_rozbor_dna_button_modlitba2(i, pom);
		}
#endif

#define ZOBRAZ_BUTTON_DETAILY
#ifdef ZOBRAZ_BUTTON_DETAILY
		// nezobrazujú sa pre sobotnú spomienku panny márie
		if (ma_na_vyber_spolocne_casti(poradie_svateho) && (poradie_svateho != PORADIE_PM_SOBOTA)) {

			Log("ma_na_vyber_spolocne_casti(poradie_svateho == %d) vrátilo ANO...\n", poradie_svateho);

			// oddelenie
			if (som_v_tabulke == ANO) {
				// was colspan="2" | ToDo solve with sophisticated <div> structure
				Export(HTML_TABLE_CELL_END "\n");
				ExportTableCell(HTML_TABLE_CELL_PRAYER);
			}

			// button 'Detaily...'
			i = MODL_DETAILY;
			if (_global_linky == ANO) {
				_export_rozbor_dna_button_modlitba2(i, pom);
			}// ak nie zobrazovat linky na internet (2009-08-11: teda napr. pre batch mód), tlacidlo `Detaily...' je zbytocne
		}// ma_na_vyber_spolocne_casti(poradie_svateho)
		else {
			Log("nemá na výber spoločné časti...\n");
		}
#endif

		// nový element (ďalšia tabuľka)
		if ((som_v_tabulke == ANO) && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTONY_USPORNE))) {
			Export(HTML_TABLE_CELL_END "\n");
			Export(HTML_TABLE_ROW_END "\n");
			Export(HTML_TABLE_END "\n");
			// tabuľka -- koniec
			ExportHtmlComment("END:úsporné zobrazenie v tabuľke");
		}

	}// if (typ)
	else {
		// inak (pre ostatné typy exportu) buttony neexportujem
		Log("--- _export_rozbor_dna_buttons_dni(): buttony nedávam...\n");
		if (typ == EXPORT_DNA_VIAC_DNI) {
			// 2006-08-19: pridaná liturgická farba - pre buttons je treba v každom riadku
			if (som_v_tabulke == ANO) {
				Export(HTML_TABLE_CELL_END "\n");

				ExportEmptyCell();

				ExportTableCell(HTML_TABLE_CELL);

				ExportHtmlComment("_global_string_farba(2)");

				Export("%s", _global_string_farba);
				Export(HTML_TABLE_CELL_END "\n");

				ExportTableCell(HTML_TABLE_CELL);
			}
		}// (typ == EXPORT_DNA_VIAC_DNI)
	}

	// späť pôvodné nastavenia (pre den_zoznam != ANO boli zmenené)
	_global_den.den = _pom_den;
	_global_den.mesiac = _pom_mesiac;
	_global_den.rok = _pom_rok;
#ifdef OS_Windows_Ruby
	if ((typ != EXPORT_DNA_VIAC_DNI_TXT) && (typ != EXPORT_DNA_XML)) {
		ExportHtmlComment("buttons:end");
	}
#endif

	// XML export -- koniec daného slávenia
	if (typ == EXPORT_DNA_XML) {
		Export(ELEM_END(XML_CELEBRATION) "\n");
	}

	Log("--- _export_rozbor_dna_buttons(typ == %d) -- end\n", typ);
} // _export_rozbor_dna_buttons()

void _export_rozbor_dna_buttons_dni_dnes(short int dnes_dnes, short int som_v_tabulke, char pom2[MAX_STR], short int zobraz_odkaz_na_skrytie) {
	Log("_export_rozbor_dna_buttons_dni_dnes(): začiatok\n");
#ifdef OS_Windows_Ruby
	ExportHtmlComment("buttons/dni/dnes:begin");
	// Log("_global_den.denvt == %d\n", _global_den.denvt);
#endif

	char action[MAX_STR];
	mystrcpy(action, STR_EMPTY, MAX_STR);

	// for TTS, mute whole table
	Export("<" HTML_DIV_TTS_MUTE ">\n");

#ifdef BEHAVIOUR_WEB
	if (som_v_tabulke == NIE) {
		// table begin
		Export("<" HTML_TABLE ">\n");
		Export("<" HTML_TABLE_ROW ">\n");
	}
#endif

	// tlačidlo pre dnešok sa pre 'M' (batch módový export) nezobrazuje
	if (_global_opt_batch_monthly == NIE) {

		// table cell begin
		ExportTableCell(HTML_TABLE_CELL);

		if (dnes_dnes >= EXPORT_DNES_DNES_ANO) {
			sprintf(action, "%s?%s=%s%s", script_name, STR_QUERY_TYPE, STR_PRM_DNES, pom2);
			// Export("<form action=\"%s?%s=%s%s\" method=\"post\">\n", script_name, STR_QUERY_TYPE, STR_PRM_DNES, pom2);
			Export_HtmlForm(action);
			Export(HTML_FORM_INPUT_SUBMIT1" title=\"%s\" value=\"", html_button_dnes[_global_jazyk]);
		}
		else if (dnes_dnes > EXPORT_DNES_DNES_NULL) {
			sprintf(action, HTML_LINK_CALL1, script_name, STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, _global_den.den, STR_MESIAC, _global_den.mesiac, STR_ROK, _global_den.rok, pom2);
			Export_HtmlForm(action);
			Export(HTML_FORM_INPUT_SUBMIT1" title=\"%s\" value=\"", _vytvor_string_z_datumu(_global_den.den, _global_den.mesiac, _global_den.rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
		}

		if (dnes_dnes == EXPORT_DNES_DNES_ANO_SPEC) {
			Export(HTML_LEFT_ARROW_CLASSIC);
			ExportNonbreakingSpace();
			Export((char *)html_button_tento_den[_global_jazyk]);
		}
		else if (dnes_dnes == EXPORT_DNES_DNES_ANO) {
			Export((char *)html_button_dnes[_global_jazyk]);
		}
		else if (dnes_dnes > EXPORT_DNES_DNES_NULL) {
			Export(HTML_UP_ARROW_CLASSIC "" STR_SPACE);
#if defined(OS_Windows_Ruby) || defined(IO_ANDROID)
			Export((char *)html_button_tento_den[_global_jazyk]);
#else
			Export(_vytvor_string_z_datumu(_global_den.den, _global_den.mesiac, _global_den.rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
#endif
		}
		
		if (dnes_dnes > EXPORT_DNES_DNES_NULL) {
			Export("\"" HTML_FORM_INPUT_END "\n");
		}

		// show-hide navigation
		if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI)) {
			if (zobraz_odkaz_na_skrytie == ANO) {
				char show[MAX_STR] = STR_EMPTY;
				char hide[MAX_STR] = STR_EMPTY;
				sprintf(show, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_navig_buttons[_global_jazyk]);
				sprintf(hide, "%s %s", html_text_option_skryt[_global_jazyk], html_text_navig_buttons[_global_jazyk]);
				_export_link_show_hide(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_NAVIG_BUTTONS, show, hide, (char *)HTML_DIV_SMALL_INLINE, (char *)HTML_CLASS_QUIET, (char *)STR_EMPTY, (char *)STR_EMPTY, (char *)STR_EMPTY, (char *)HTML_DIV_END);
			}
		}
		Export("</form>\n");

		// table cell end
		Export(HTML_TABLE_CELL_END "\n");

	}// _global_opt_batch_monthly == NIE

#ifdef BEHAVIOUR_WEB
	if (som_v_tabulke == NIE) {
		// table end
		Export(HTML_TABLE_ROW_END "\n");
		Export(HTML_TABLE_END "\n");
	}
#endif

	Export(HTML_DIV_END);

#ifdef OS_Windows_Ruby
	ExportHtmlComment("buttons/dni/dnes:end");
#endif
	Log("_export_rozbor_dna_buttons_dni_dnes(): koniec.\n");
} // _export_rozbor_dna_buttons_dni_dnes()

// typ - ako v _export_rozbor_dna()
//
// exportuje buttony pre _export_rozbor_dna() a to button predosleho a nasledujuceho dna
// možnosť zmeniť default look (tlačidlo "dnes" pre navigáciu v modlitbe nebude mať popis "dnes" a iné zmeny pre navigáciu)
void _export_rozbor_dna_buttons_dni(short int typ, short int dnes_dnes, short int aj_navigacia) {
	Log("_export_rozbor_dna_buttons_dni(): začiatok\n");

#ifdef OS_Windows_Ruby
	ExportHtmlComment("buttons/dni:begin");
#endif

	short int podmienka = -1;

	// current behaviour for normal mode (not voice output)
	if (!isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT)) {
		// zobrazujeme, iba ak nie je explicitne vyžiadané skrývanie
		if (!isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_NAVIG_BUTTONS)) {
			podmienka = 1; // zobraziť: _export_rozbor_dna_buttons_dni_call(typ, dnes_dnes);
		}
		else {
			podmienka = 0; // nezobraziť: hide buttons (only hyperlink enabling to display them back is exported)
		}
	}
	else {
		if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_NAVIGATION)) {

			if ((!isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_NAVIG_BUTTONS)) && ((aj_navigacia == ANO) || (aj_navigacia == CIASTOCNE))) {
				podmienka = 2; // zobraziť pre voice output
			}
			else {
				podmienka = 0;
			}
		}
		else {
			ExportHtmlComment("no navigation for voice output (hide navigation)");
		}
	}

	char pom2[MAX_STR];
	mystrcpy(pom2, STR_EMPTY, MAX_STR);
	char pom3[MAX_STR];
	mystrcpy(pom3, STR_EMPTY, MAX_STR);

	switch (podmienka)
	{
	case 0:
	{
#ifdef OS_Windows_Ruby
		ExportHtmlComment("hide buttons");
#endif
		/*
		char show[SMALL] = STR_EMPTY;
		char hide[SMALL] = STR_EMPTY;
		sprintf(show, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_navig_buttons[_global_jazyk]);
		sprintf(hide, "%s %s", html_text_option_skryt[_global_jazyk], html_text_navig_buttons[_global_jazyk]);
		char before[SMALL] = STR_EMPTY;
		sprintf(before, HTML_P_CENTER_SMALL);
		char after[SMALL] = STR_EMPTY;
		mystrcpy(after, HTML_P_END, SMALL);
		_export_link_show_hide(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_NAVIG_BUTTONS, show, hide, (char *)HTML_DIV_TTS_MUTE, (char *)HTML_CLASS_QUIET, before, after, (char *)STR_EMPTY, (char *)HTML_DIV_END);
		*/
		prilep_request_options(pom2, pom3);

		_export_rozbor_dna_buttons_dni_dnes(EXPORT_DNES_DNES_NULL, NIE, pom2, ANO);
	}
	break;
	case 1:
	{
		_export_rozbor_dna_buttons_dni_call(typ, dnes_dnes);
	}
	break;
	case 2:
	{
		// pre voice output zobrazujeme len "hore" pre daný deň
		prilep_request_options(pom2, pom3);

		_export_rozbor_dna_buttons_dni_dnes(dnes_dnes, NIE, pom2, ANO);
	}
	break;
	default:
		break;
	} // switch(podmienka)

#ifdef OS_Windows_Ruby
	ExportHtmlComment("buttons/dni:end");
#endif
	Log("_export_rozbor_dna_buttons_dni(): koniec.\n");
} // _export_rozbor_dna_buttons_dni()

void _export_rozbor_dna_buttons_dni_orig(short int typ, short int dnes_dnes) {
	Log("--- _export_rozbor_dna_buttons_dni_orig(typ == %d) -- begin\n", typ);
#ifdef OS_Windows_Ruby
	ExportHtmlComment("buttons/dni/orig:begin");
#endif
	char str_month[SMALL] = STR_EMPTY;
	short int zmena_mesiaca = NIE;
	short int som_v_tabulke = ANO; // 2009-08-26: či sa používa tabuľka; bežne pre web áno, pre export pre mobilné zariadenia [export_monthly_druh >= 3] netreba tabuľku

	short int _orig_den = _global_den.den;
	short int _orig_mesiac = _global_den.mesiac;
	short int _orig_rok = _global_den.rok;

	_struct_den_mesiac datum;

	char pom[MAX_STR] = STR_EMPTY;
	char pom2[MAX_STR];
	mystrcpy(pom2, STR_EMPTY, MAX_STR);
	char pom3[MAX_STR];
	mystrcpy(pom3, STR_EMPTY, MAX_STR);
	char pom2_no_override[MAX_STR];
	mystrcpy(pom2_no_override, STR_EMPTY, MAX_STR);

	if (_global_opt_batch_monthly == NIE) {
		prilep_request_options(pom2, pom3);

		// cleanup of pom3 and generate different pom2
		mystrcpy(pom3, STR_EMPTY, MAX_STR);
		Log("creating pom2_no_override with removal of BIT_OPT_1_OVERRIDE_STUP_SLAV...\n");
		prilep_request_options(pom2_no_override, pom3, 1 /* special_handling: remove BIT_OPT_1_OVERRIDE_STUP_SLAV */);
	}// if (_global_opt_batch_monthly == NIE)

	if (query_type == PRM_LIT_OBD) {
		Log("pre query_type == PRM_LIT_OBD sa dni netlačia (nemám nastavený dátum), iba 'dnes'...\n");

		_export_rozbor_dna_buttons_dni_dnes(EXPORT_DNES_DNES_ANO, NIE /* som_v_tabulke */, pom2, ANO /* zobraz_odkaz_na_skrytie */);

		return;
	}// query_type == PRM_LIT_OBD

	if ((_global_pocet_navigacia <= 1) && (_global_pocet_volani_interpretTemplate < 2)) {
		// najprv dnes, potom ostatné
		if ((query_type == PRM_DATUM) && (_global_modlitba != MODL_NEURCENA)) {

			_export_rozbor_dna_buttons_dni_dnes(EXPORT_DNES_DNES_ANO, NIE /* som_v_tabulke */, pom2, ANO /* zobraz_odkaz_na_skrytie */);

		}
	}// if ((_global_pocet_navigacia <= 1) && (_global_pocet_volani_interpretTemplate < 2))

	if (dnes_dnes != EXPORT_DNES_DNES_ANO) {
		// pre tlačidlá predošlého a nasledujúceho dňa pre navigáciu v modlitbe treba použiť iný dátum ako _global_den, nakoľko pre vešpery v predvečer nedele resp. slávnosti sa dátum posunul o jeden deň...
		// ExportHtmlComment("úprava _global_den na: den %d | mesiac %d | rok %d", _global_vstup_den, _global_vstup_mesiac, _global_vstup_rok);
		_global_den.den = _global_vstup_den;
		_global_den.mesiac = _global_vstup_mesiac;
		_global_den.rok = _global_vstup_rok;
	}

	if (PODMIENKA_JE_BATCH_MODE_MONTHLY__AND__PLAIN_EXPORT) {
		som_v_tabulke = NIE;
		Log("-- _export_rozbor_dna_buttons(typ == %d): keďže sme v _global_opt_batch_monthly == ANO a export_monthly_druh (%d) > 2, nebudeme exportovať tabuľku...\n", typ, export_monthly_druh);
	}

	if (typ == EXPORT_DNA_VIAC_DNI_TXT) {
		som_v_tabulke = NIE;
		Log("-- _export_rozbor_dna_buttons(typ == %d): kvôli typu nebudeme exportovať tabuľku...\n", typ);
	}

	if ((typ != EXPORT_DNA_VIAC_DNI) && (typ != EXPORT_DNA_VIAC_DNI_SIMPLE) && (typ != EXPORT_DNA_VIAC_DNI_TXT)) {
		Log("--- _export_rozbor_dna_buttons_dni(): idem tlacit buttony...\n");
		short int _local_rok;

		if (dnes_dnes == EXPORT_DNES_DNES_ANO) {
			ExportHtmlComment("tabuľka s buttonmi predošlý, nasledovný rok/mesiac/deň presunutá pred rozbor daného dňa (teda navrch stránky) (orig)");
		}
		else {
			ExportHtmlComment("tabuľka s buttonmi predošlý, nasledovný deň (orig)");
		}

		// tabuľka pre buttony Predchádzajúci/Nasledujúci deň/mesiac/rok a Dnes
		if (som_v_tabulke == ANO) {
			Export("<" HTML_TABLE ">\n");
			Export("<" HTML_TABLE_ROW ">\n");
		}
		else {
			Export("\n<div class=\"navd\">");
			Export(HTML_P_BEGIN"\n");
		}

		if (dnes_dnes == EXPORT_DNES_DNES_ANO) {
			// vypočítanie toho istého dňa v predošlom roku
			datum.den = _global_den.den;
			datum.mesiac = _global_den.mesiac;
			_local_rok = _global_den.rok - 1;
			if ((_global_den.den == 29) && (_global_den.mesiac - 1 == MES_FEB)) { // 29FEB
				if (!prestupny(_local_rok)) {
					datum.den = 28;
				}
			}

			// << predošlý rok -- button
			if (_global_opt_batch_monthly == NIE) {
				sprintf(pom, HTML_LINK_CALL1, script_name, STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, datum.den, STR_MESIAC, datum.mesiac, STR_ROK, _local_rok, pom2_no_override);
			}// if (_global_opt_batch_monthly == NIE)
			else {
				mystrcpy(pom, STR_EMPTY, MAX_STR); // 2009-08-12: možno v budúcnosti by sa mohol dať odkaz na adresár s rok+mesiacom predošlého roka
			}
			if (_global_opt_batch_monthly == NIE) {
				if (som_v_tabulke == ANO) {
					ExportTableCell(HTML_TABLE_CELL);
					Export_HtmlForm(pom);
					// 2003-07-16; << zmenene na &lt;&lt; 2007-03-19: zmenené na HTML_LEFT_ARROW; 2011-01-26: zmenené na HTML_LEFT_ARROW_HUGE
					Export(HTML_FORM_INPUT_SUBMIT0 " title=\"%s %s %d\" value=\"" HTML_LEFT_ARROW_HUGE " ", html_button_predchadzajuci_[_global_jazyk], html_text_rok[_global_jazyk], _local_rok);
					Export((char *)html_text_rok[_global_jazyk]);
					Export(" \"" HTML_FORM_INPUT_END "\n");
					Export("</form>\n");
					Export(HTML_TABLE_CELL_END "\n");
				}
				else {
					Export(HTML_A_HREF_BEGIN "\"%s\">" HTML_LEFT_ARROW_HUGE " %s %s %d" HTML_A_END "\n", pom, html_button_predchadzajuci_[_global_jazyk], html_text_rok[_global_jazyk], _local_rok);
					ExportNonbreakingSpace(); Export(STR_VERTICAL_BAR); ExportNonbreakingSpace(); Export("\n");
				}
			}

			// << predošlý mesiac
			if ((_global_den.mesiac - 1) == MES_JAN) {
				datum.mesiac = MES_DEC + 1;
				_local_rok = _global_den.rok - 1;
			}
			else {
				datum.mesiac = _global_den.mesiac - 1;
				_local_rok = _global_den.rok;
			}
			if (_global_den.den > pocet_dni[datum.mesiac - 1]) {
				datum.den = pocet_dni[datum.mesiac - 1];
			}
			else {
				datum.den = _global_den.den;
			}

			// predošlý mesiac -- button
			if (_global_opt_batch_monthly == NIE) {
				sprintf(pom, HTML_LINK_CALL1, script_name, STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, datum.den, STR_MESIAC, datum.mesiac, STR_ROK, _local_rok, pom2_no_override);
			}// if (_global_opt_batch_monthly == NIE)
			else {
				mystrcpy(pom, STR_EMPTY, MAX_STR);
			}
			if (_global_opt_batch_monthly == NIE) {
				if (som_v_tabulke == ANO) {
					ExportTableCell(HTML_TABLE_CELL);
					Export_HtmlForm(pom);
					Export(HTML_FORM_INPUT_SUBMIT0 " title=\"%s %s %s\" value=\"" HTML_LEFT_ARROW " ", html_button_predchadzajuci_[_global_jazyk], html_text_mesiac[_global_jazyk], _vytvor_string_z_datumu(VSETKY_DNI, datum.mesiac, _local_rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
					Export((char *)html_text_mesiac[_global_jazyk]);
					Export(" \"" HTML_FORM_INPUT_END "\n");
					Export("</form>\n");
					Export(HTML_TABLE_CELL_END "\n");
				}
				else {
					Export(HTML_A_HREF_BEGIN "\"%s\">" HTML_LEFT_ARROW " %s %s %s" HTML_A_END "\n", pom, html_button_predchadzajuci_[_global_jazyk], html_text_mesiac[_global_jazyk], _vytvor_string_z_datumu(VSETKY_DNI, datum.mesiac, _local_rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
					ExportNonbreakingSpace(); Export(STR_VERTICAL_BAR); ExportNonbreakingSpace(); Export("\n");
				}
			}
		}// predošlý rok, mesiac -- len pre "dnes"

		// vypočítanie predošlého dňa
		zmena_mesiaca = NIE;
		_local_rok = _global_den.rok;
		if (_global_den.den == 1) {
			zmena_mesiaca = ANO;
			if (_global_den.mesiac - 1 == MES_JAN) { // 01JAN
				datum.mesiac = 12;
				_local_rok = _global_den.rok - 1;
			}
			else {
				datum.mesiac = _global_den.mesiac - 1;
			}
			datum.den = pocet_dni[datum.mesiac - 1];
		}
		else {
			datum.den = _global_den.den - 1;
			datum.mesiac = _global_den.mesiac;
		}

		if (zmena_mesiaca == ANO) {
			if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
				sprintf(str_month, ".." STR_PATH_SEPARATOR_HTML "" DIRNAME_EXPORT_MONTH_SIMPLE "" STR_PATH_SEPARATOR_HTML, _local_rok % 100, datum.mesiac, nazov_mes[datum.mesiac - 1]);
			}
			else {
				// EXPORT_DATE_FULL
				sprintf(str_month, ".." STR_PATH_SEPARATOR_HTML "" DIRNAME_EXPORT_MONTH_FULL "" STR_PATH_SEPARATOR_HTML, _local_rok, datum.mesiac, nazov_mesiaca_asci(datum.mesiac - 1));
			}
		}// if (zmena_mesiaca == ANO)
		else {
			mystrcpy(str_month, STR_EMPTY, SMALL);
		}
		Log("str_month == %s\n", str_month);

		// << predošlý deň -- button
		if (_global_opt_batch_monthly == NIE) {
			sprintf(pom, HTML_LINK_CALL1, script_name, STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, datum.den, STR_MESIAC, datum.mesiac, STR_ROK, _local_rok, pom2_no_override);
		}// if (_global_opt_batch_monthly == NIE)
		else {
			if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
				sprintf(pom, "%s" FILENAME_EXPORT_DATE_SIMPLE ".htm", str_month, _local_rok % 100, datum.mesiac, datum.den);
			}
			else {
				sprintf(pom, "%s" FILENAME_EXPORT_DATE_FULL ".htm", str_month, _local_rok, datum.mesiac, datum.den);
			}
		}
		Log("\treťazec pom == %s\n", pom);
		if (som_v_tabulke == ANO) {
			ExportTableCell(HTML_TABLE_CELL);
			Export_HtmlForm(pom);
			// 2003-07-16; < zmenene na &lt; 2007-03-19: zmenené na HTML_LEFT_ARROW; 2011-01-26: zmenené na HTML_LEFT_ARROW_SINGLE
			Export(HTML_FORM_INPUT_SUBMIT0 " title=\"%s %s %s\" value=\"" HTML_LEFT_ARROW_SINGLE " ", html_button_predchadzajuci_[_global_jazyk], html_text_den[_global_jazyk], _vytvor_string_z_datumu(datum.den, datum.mesiac, _local_rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
			if (dnes_dnes == EXPORT_DNES_DNES_ANO) {
				Export((char *)html_text_den[_global_jazyk]);
			}
			else {
				Export(_vytvor_string_z_datumu(datum.den, datum.mesiac, _local_rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
			}
			Export(" \"" HTML_FORM_INPUT_END "\n");
			Export("</form>\n");
			Export(HTML_TABLE_CELL_END "\n");
		}
		else {
			if (_global_jazyk == JAZYK_HU) {
				Export(HTML_A_HREF_BEGIN "\"%s\">" HTML_LEFT_ARROW_SINGLE " %s %s" HTML_A_END "\n", pom, html_button_predchadzajuci_[_global_jazyk], html_text_den[_global_jazyk]);
			}
			else {
				Export(HTML_A_HREF_BEGIN "\"%s\">" HTML_LEFT_ARROW_SINGLE " %s %s %s" HTML_A_END "\n", pom, html_button_predchadzajuci_[_global_jazyk], html_text_den[_global_jazyk], _vytvor_string_z_datumu(datum.den, datum.mesiac, _local_rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
			}
			ExportNonbreakingSpace(); Export(STR_VERTICAL_BAR); ExportNonbreakingSpace(); Export("\n");
		}

		// tlačidlo pre dnešok
		_export_rozbor_dna_buttons_dni_dnes(dnes_dnes, som_v_tabulke, pom2, NIE);

		// vypočítanie nasledujúceho dňa
		zmena_mesiaca = NIE;
		_local_rok = _global_den.rok;
		if (_global_den.den == pocet_dni[_global_den.mesiac - 1]) {
			zmena_mesiaca = ANO;
			datum.den = 1;
			if (_global_den.mesiac - 1 == MES_DEC) {
				datum.mesiac = 1;
				_local_rok = _global_den.rok + 1;
			}
			else {
				datum.mesiac = _global_den.mesiac + 1;
			}
		}
		else {
			datum.den = _global_den.den + 1;
			datum.mesiac = _global_den.mesiac;
		}

		if (zmena_mesiaca == ANO) {
			if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
				sprintf(str_month, ".." STR_PATH_SEPARATOR_HTML "" DIRNAME_EXPORT_MONTH_SIMPLE "" STR_PATH_SEPARATOR_HTML, _local_rok % 100, datum.mesiac, nazov_mes[datum.mesiac - 1]);
			}
			else {
				// EXPORT_DATE_FULL
				sprintf(str_month, ".." STR_PATH_SEPARATOR_HTML "" DIRNAME_EXPORT_MONTH_FULL "" STR_PATH_SEPARATOR_HTML, _local_rok, datum.mesiac, nazov_mesiaca_asci(datum.mesiac - 1));
			}
		}// if (zmena_mesiaca == ANO)
		else {
			mystrcpy(str_month, STR_EMPTY, SMALL);
		}
		Log("str_month == %s\n", str_month);

		// >> nasledujúci deň -- button
		if (_global_opt_batch_monthly == NIE) {
			sprintf(pom, HTML_LINK_CALL1, script_name, STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, datum.den, STR_MESIAC, datum.mesiac, STR_ROK, _local_rok, pom2_no_override);
		}// if (_global_opt_batch_monthly == NIE)
		else {
			if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
				sprintf(pom, "%s" FILENAME_EXPORT_DATE_SIMPLE ".htm", str_month, _local_rok % 100, datum.mesiac, datum.den);
			}
			else {
				sprintf(pom, "%s" FILENAME_EXPORT_DATE_FULL ".htm", str_month, _local_rok, datum.mesiac, datum.den);
			}
		}
		Log("\treťazec pom == %s\n", pom);
		if (som_v_tabulke == ANO) {
			ExportTableCell(HTML_TABLE_CELL);
			Export_HtmlForm(pom);
			Export(HTML_FORM_INPUT_SUBMIT0 " title=\"%s %s %s\" value=\"", html_button_nasledujuci_[_global_jazyk], html_text_den[_global_jazyk], _vytvor_string_z_datumu(datum.den, datum.mesiac, _local_rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));

			if (dnes_dnes == EXPORT_DNES_DNES_ANO) {
				Export((char *)html_text_den[_global_jazyk]);
			}
			else {
				Export(_vytvor_string_z_datumu(datum.den, datum.mesiac, _local_rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
			}
			Export(" " HTML_RIGHT_ARROW_SINGLE "\"" HTML_FORM_INPUT_END "\n");
			Export("</form>\n");
			Export(HTML_TABLE_CELL_END "\n");
		}
		else {
			if (_global_jazyk == JAZYK_HU) {
				Export(HTML_A_HREF_BEGIN "\"%s\">%s %s " HTML_RIGHT_ARROW_SINGLE "" HTML_A_END "\n", pom, html_button_nasledujuci_[_global_jazyk], html_text_den[_global_jazyk]);
			}
			else {
				Export(HTML_A_HREF_BEGIN "\"%s\">%s %s %s " HTML_RIGHT_ARROW_SINGLE "" HTML_A_END "\n", pom, html_button_nasledujuci_[_global_jazyk], html_text_den[_global_jazyk], _vytvor_string_z_datumu(datum.den, datum.mesiac, _local_rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
			}
		}

		if (dnes_dnes == EXPORT_DNES_DNES_ANO) {
			// >> nasledovný mesiac
			if ((_global_den.mesiac - 1) == MES_DEC) {
				datum.mesiac = MES_JAN + 1;
				_local_rok = _global_den.rok + 1;
			}
			else {
				datum.mesiac = _global_den.mesiac + 1;
				_local_rok = _global_den.rok;
			}
			if (_global_den.den > pocet_dni[datum.mesiac - 1]) {
				datum.den = pocet_dni[datum.mesiac - 1];
			}
			else {
				datum.den = _global_den.den;
			}

			// >> nasledovný mesiac -- button
			if (_global_opt_batch_monthly == NIE) {
				sprintf(pom, HTML_LINK_CALL1, script_name, STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, datum.den, STR_MESIAC, datum.mesiac, STR_ROK, _local_rok, pom2_no_override);
			}// if (_global_opt_batch_monthly == NIE)
			else {
				mystrcpy(pom, STR_EMPTY, MAX_STR);
			}
			if (_global_opt_batch_monthly == NIE) {
				if (som_v_tabulke == ANO) {
					ExportTableCell(HTML_TABLE_CELL);
					Export_HtmlForm(pom);
					Export(HTML_FORM_INPUT_SUBMIT0 " title=\"%s %s %s\" value=\"", html_button_nasledujuci_[_global_jazyk], html_text_mesiac[_global_jazyk], _vytvor_string_z_datumu(VSETKY_DNI, datum.mesiac, _local_rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
					Export((char *)html_text_mesiac[_global_jazyk]);
					Export(" " HTML_RIGHT_ARROW "\"" HTML_FORM_INPUT_END "\n");
					Export("</form>\n");
					Export(HTML_TABLE_CELL_END "\n");
				}
				else {
					Export(HTML_A_HREF_BEGIN "\"%s\">" HTML_LEFT_ARROW " %s %s %s" HTML_A_END "\n", pom, html_button_nasledujuci_[_global_jazyk], html_text_mesiac[_global_jazyk], _vytvor_string_z_datumu(VSETKY_DNI, datum.mesiac, _local_rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
					ExportNonbreakingSpace(); Export(STR_VERTICAL_BAR); ExportNonbreakingSpace(); Export("\n");
				}
			}

			// vypočítanie toho istého dňa v nasledujúcom roku
			datum.den = _global_den.den;
			datum.mesiac = _global_den.mesiac;
			_local_rok = _global_den.rok + 1;
			if ((_global_den.den == 29) && (_global_den.mesiac - 1 == MES_FEB)) { // 29FEB
				if (!prestupny(_local_rok)) {
					datum.den = 28;
				}
			}
			// nasledujúci rok -- button
			if (_global_opt_batch_monthly == NIE) {
				sprintf(pom, HTML_LINK_CALL1, script_name, STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, datum.den, STR_MESIAC, datum.mesiac, STR_ROK, _local_rok, pom2_no_override);
			}// if (_global_opt_batch_monthly == NIE)
			else {
				mystrcpy(pom, STR_EMPTY, MAX_STR);
			}
			if (_global_opt_batch_monthly == NIE) {
				if (som_v_tabulke == ANO) {
					ExportTableCell(HTML_TABLE_CELL);
					Export_HtmlForm(pom);
					Export(HTML_FORM_INPUT_SUBMIT0 " title=\"%s %s %d\" value=\"", html_button_nasledujuci_[_global_jazyk], html_text_rok[_global_jazyk], _local_rok);
					Export((char *)html_text_rok[_global_jazyk]);
					Export(" " HTML_RIGHT_ARROW_HUGE "\"" HTML_FORM_INPUT_END "\n");
					Export("</form>");
					Export(HTML_TABLE_CELL_END "\n");
				}
				else {
					Export(HTML_A_HREF_BEGIN "\"%s\">%s %s %d " HTML_RIGHT_ARROW_HUGE "" HTML_A_END "\n", pom, html_button_nasledujuci_[_global_jazyk], html_text_rok[_global_jazyk], _local_rok);
					ExportNonbreakingSpace(); Export(STR_VERTICAL_BAR); ExportNonbreakingSpace(); Export("\n");
				}
			}
		}// nasledovný mesiac, rok -- len pre "dnes"

		if (som_v_tabulke == ANO) {
			Export(HTML_TABLE_ROW_END "\n");
			Export(HTML_TABLE_END "\n");
		}
	}// if (typ)
	else {
		// inak buttony nedávam
		Log("--- _export_rozbor_dna_buttons_dni(): buttony nedávam...\n");
	}

	if ((_global_pocet_navigacia > 1) || (_global_pocet_volani_interpretTemplate >= 2)) {
		// najprv ostatné, potom dnes
		if ((query_type == PRM_DATUM) && (_global_modlitba != MODL_NEURCENA)) {

			_export_rozbor_dna_buttons_dni_dnes(EXPORT_DNES_DNES_ANO, NIE /* som_v_tabulke */, pom2, ANO /* zobraz_odkaz_na_skrytie */);

		}
	}// if ((_global_pocet_navigacia > 1) || (_global_pocet_volani_interpretTemplate >= 2))

	// späť pôvodné nastavenia (pre dnes_dnes != ANO boli zmenené)
	_global_den.den = _orig_den;
	_global_den.mesiac = _orig_mesiac;
	_global_den.rok = _orig_rok;
#ifdef OS_Windows_Ruby
	ExportHtmlComment("buttons/dni/orig:end");
#endif
	Log("--- _export_rozbor_dna_buttons_dni_orig(typ == %d) -- end\n", typ);
} // _export_rozbor_dna_buttons_dni_orig()

void _export_rozbor_dna_buttons_dni_compact(short int typ, short int dnes_dnes) {
	Log("--- _export_rozbor_dna_buttons_dni_compact(typ == %d) -- begin\n", typ);
#ifdef OS_Windows_Ruby
	ExportHtmlComment("buttons/dni/compact:begin");
#endif
	char str_month[SMALL] = STR_EMPTY;
	short int zmena_mesiaca = NIE;
	short int som_v_tabulke = ANO; // či sa používa tabuľka; bežne pre web áno, pre export pre mobilné zariadenia [export_monthly_druh >= 3] netreba tabuľku

	short int _orig_den = _global_den.den;
	short int _orig_mesiac = _global_den.mesiac;
	short int _orig_rok = _global_den.rok;

	unsigned long long _global_opt_orig;

	_struct_den_mesiac datum;

	char pom[MAX_STR] = STR_EMPTY;
	char pom2[MAX_STR];
	mystrcpy(pom2, STR_EMPTY, MAX_STR);
	char pom3[MAX_STR];
	mystrcpy(pom3, STR_EMPTY, MAX_STR);
	char pom2_no_override[MAX_STR];
	mystrcpy(pom2_no_override, STR_EMPTY, MAX_STR);

	if (_global_opt_batch_monthly == NIE) {
		prilep_request_options(pom2, pom3);

		// cleanup of pom3 and generate different pom2
		mystrcpy(pom3, STR_EMPTY, MAX_STR);
		Log("creating pom2_no_override with removal of BIT_OPT_1_OVERRIDE_STUP_SLAV...\n");
		prilep_request_options(pom2_no_override, pom3, 1 /* special_handling: remove BIT_OPT_1_OVERRIDE_STUP_SLAV */);
	}// if (_global_opt_batch_monthly == NIE)

	if (query_type == PRM_LIT_OBD) {
		Log("pre query_type == PRM_LIT_OBD sa dni netlačia (nemám nastavený dátum), iba 'dnes'...\n");

		_export_rozbor_dna_buttons_dni_dnes(EXPORT_DNES_DNES_ANO, NIE /* som_v_tabulke */, pom2, ANO /* zobraz_odkaz_na_skrytie */);

		return;
	}// query_type == PRM_LIT_OBD

	if ((_global_pocet_navigacia <= 1) && (_global_pocet_volani_interpretTemplate < 2)) {
		// najprv dnes, potom ostatné
		if ((query_type == PRM_DATUM) && (_global_modlitba != MODL_NEURCENA)) {

			_export_rozbor_dna_buttons_dni_dnes(EXPORT_DNES_DNES_ANO, NIE /* som_v_tabulke */, pom2, ANO /* zobraz_odkaz_na_skrytie */);

		}
	}// if ((_global_pocet_navigacia <= 1) && (_global_pocet_volani_interpretTemplate < 2))

	if (dnes_dnes != EXPORT_DNES_DNES_ANO) {
		_global_den.den = _global_vstup_den;
		_global_den.mesiac = _global_vstup_mesiac;
		_global_den.rok = _global_vstup_rok;
	}

	if (PODMIENKA_JE_BATCH_MODE_MONTHLY__AND__PLAIN_EXPORT) {
		som_v_tabulke = NIE;
		Log("-- _export_rozbor_dna_buttons(typ == %d): keďže sme v _global_opt_batch_monthly == ANO a export_monthly_druh (%d) > 2, nebudeme exportovať tabuľku...\n", typ, export_monthly_druh);
	}

	if (typ == EXPORT_DNA_VIAC_DNI_TXT) {
		som_v_tabulke = NIE;
		Log("-- _export_rozbor_dna_buttons(typ == %d): kvôli typu nebudeme exportovať tabuľku...\n", typ);
	}

	if ((typ != EXPORT_DNA_VIAC_DNI) && (typ != EXPORT_DNA_VIAC_DNI_SIMPLE) && (typ != EXPORT_DNA_VIAC_DNI_TXT)) {
		Log("--- _export_rozbor_dna_buttons_dni(): idem tlacit buttony...\n");
		short int _local_rok;

		if (dnes_dnes == EXPORT_DNES_DNES_ANO) {
			ExportHtmlComment("tabuľka s buttonmi predošlý, nasledovný rok/mesiac/deň presunutá pred rozbor daného dňa (teda navrch stránky) (compact)");
		}
		else {
			ExportHtmlComment("tabuľka s buttonmi predošlý, nasledovný deň (compact)");
		}

		// tabuľka pre buttony Predchádzajúci/Nasledujúci deň/mesiac/rok a Dnes
		if (som_v_tabulke == ANO) {
			Export("<" HTML_TABLE ">\n");
			Export("<" HTML_TABLE_ROW ">\n");
		}
		else {
			Export("\n" HTML_P_BEGIN "\n");
			ExportNonbreakingSpace(); Export(STR_VERTICAL_BAR); ExportNonbreakingSpace(); Export("\n");
		}

		// ---------------------------------------------------

		// vypočítanie predošlého dňa
		zmena_mesiaca = NIE;
		_local_rok = _global_den.rok;
		if (_global_den.den == 1) {
			zmena_mesiaca = ANO;
			if (_global_den.mesiac - 1 == MES_JAN) { // 01JAN
				datum.mesiac = 12;
				_local_rok = _global_den.rok - 1;
			}
			else {
				datum.mesiac = _global_den.mesiac - 1;
			}
			datum.den = pocet_dni[datum.mesiac - 1];
		}
		else {
			datum.den = _global_den.den - 1;
			datum.mesiac = _global_den.mesiac;
		}

		if (zmena_mesiaca == ANO) {
			if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
				sprintf(str_month, ".." STR_PATH_SEPARATOR_HTML "" DIRNAME_EXPORT_MONTH_SIMPLE "" STR_PATH_SEPARATOR_HTML, _local_rok % 100, datum.mesiac, nazov_mes[datum.mesiac - 1]);
			}
			else {
				// EXPORT_DATE_FULL
				sprintf(str_month, ".." STR_PATH_SEPARATOR_HTML "" DIRNAME_EXPORT_MONTH_FULL "" STR_PATH_SEPARATOR_HTML, _local_rok, datum.mesiac, nazov_mesiaca_asci(datum.mesiac - 1));
			}
		}// if (zmena_mesiaca == ANO)
		else {
			mystrcpy(str_month, STR_EMPTY, SMALL);
		}
		Log("str_month == %s\n", str_month);

		// << predošlý deň -- button
		if (_global_opt_batch_monthly == NIE) {
			sprintf(pom, HTML_LINK_CALL1, script_name, STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, datum.den, STR_MESIAC, datum.mesiac, STR_ROK, _local_rok, pom2_no_override);
		}// if (_global_opt_batch_monthly == NIE)
		else {
			if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
				sprintf(pom, "%s" FILENAME_EXPORT_DATE_SIMPLE ".htm", str_month, _local_rok % 100, datum.mesiac, datum.den);
			}
			else {
				sprintf(pom, "%s" FILENAME_EXPORT_DATE_FULL ".htm", str_month, _local_rok, datum.mesiac, datum.den);
			}
		}
		Log("\treťazec pom == %s\n", pom);

		if (som_v_tabulke == ANO) {
			ExportTableCell(HTML_TABLE_CELL);
			Export_HtmlForm(pom);
			Export(HTML_FORM_INPUT_SUBMIT0 " title=\"%s %s %s\" value=\"" HTML_LEFT_ARROW_SINGLE " ", html_button_predchadzajuci_[_global_jazyk], html_text_den[_global_jazyk], _vytvor_string_z_datumu(datum.den, datum.mesiac, _local_rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
			// použijeme vždy, nielen keď if (dnes_dnes == EXPORT_DNES_DNES_ANO)
			Export((char *)html_text_den[_global_jazyk]);
			Export(" \"" HTML_FORM_INPUT_END "\n");
			Export("</form>\n");
			Export(HTML_TABLE_CELL_END "\n");
		}
		else {
			Export(HTML_A_HREF_BEGIN "\"%s\">" HTML_LEFT_ARROW_SINGLE " %s %s %s" HTML_A_END "\n", pom, html_button_predchadzajuci_[_global_jazyk], html_text_den[_global_jazyk], _vytvor_string_z_datumu(datum.den, datum.mesiac, _local_rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
			ExportNonbreakingSpace(); Export(STR_VERTICAL_BAR); ExportNonbreakingSpace(); Export("\n");
		}

		// ---------------------------------------------------

		// tlačidlo pre dnešok
		_export_rozbor_dna_buttons_dni_dnes(dnes_dnes, som_v_tabulke, pom2, NIE);

		// ---------------------------------------------------

		// vypočítanie nasledujúceho dňa
		zmena_mesiaca = NIE;
		_local_rok = _global_den.rok;
		if (_global_den.den == pocet_dni[_global_den.mesiac - 1]) {
			zmena_mesiaca = ANO;
			datum.den = 1;
			if (_global_den.mesiac - 1 == MES_DEC) {
				datum.mesiac = 1;
				_local_rok = _global_den.rok + 1;
			}
			else {
				datum.mesiac = _global_den.mesiac + 1;
			}
		}
		else {
			datum.den = _global_den.den + 1;
			datum.mesiac = _global_den.mesiac;
		}

		if (zmena_mesiaca == ANO) {
			if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
				sprintf(str_month, ".." STR_PATH_SEPARATOR_HTML "" DIRNAME_EXPORT_MONTH_SIMPLE "" STR_PATH_SEPARATOR_HTML, _local_rok % 100, datum.mesiac, nazov_mes[datum.mesiac - 1]);
			}
			else {
				// EXPORT_DATE_FULL
				sprintf(str_month, ".." STR_PATH_SEPARATOR_HTML "" DIRNAME_EXPORT_MONTH_FULL "" STR_PATH_SEPARATOR_HTML, _local_rok, datum.mesiac, nazov_mesiaca_asci(datum.mesiac - 1));
			}
		}// if (zmena_mesiaca == ANO)
		else {
			mystrcpy(str_month, STR_EMPTY, SMALL);
		}
		Log("str_month == %s\n", str_month);

		// >> nasledujúci deň -- button
		if (_global_opt_batch_monthly == NIE) {
			sprintf(pom, HTML_LINK_CALL1, script_name, STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, datum.den, STR_MESIAC, datum.mesiac, STR_ROK, _local_rok, pom2_no_override);
		}// if (_global_opt_batch_monthly == NIE)
		else {
			if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
				sprintf(pom, "%s" FILENAME_EXPORT_DATE_SIMPLE ".htm", str_month, _local_rok % 100, datum.mesiac, datum.den);
			}
			else {
				sprintf(pom, "%s" FILENAME_EXPORT_DATE_FULL ".htm", str_month, _local_rok, datum.mesiac, datum.den);
			}
		}
		Log("\treťazec pom == %s\n", pom);

		if (som_v_tabulke == ANO) {
			ExportTableCell(HTML_TABLE_CELL);
			Export_HtmlForm(pom);
			Export(HTML_FORM_INPUT_SUBMIT0 " title=\"%s %s %s\" value=\"", html_button_nasledujuci_[_global_jazyk], html_text_den[_global_jazyk], _vytvor_string_z_datumu(datum.den, datum.mesiac, _local_rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));

			Export((char *)html_text_den[_global_jazyk]);
			Export(" " HTML_RIGHT_ARROW_SINGLE "\"" HTML_FORM_INPUT_END "\n");
			Export("</form>\n");
			Export(HTML_TABLE_CELL_END "\n");
			Export(HTML_TABLE_ROW_END "\n");
		}
		else {
			Export(HTML_A_HREF_BEGIN "\"%s\">%s %s %s " HTML_RIGHT_ARROW_SINGLE "" HTML_A_END "\n", pom, html_button_nasledujuci_[_global_jazyk], html_text_den[_global_jazyk], _vytvor_string_z_datumu(datum.den, datum.mesiac, _local_rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
			ExportNonbreakingSpace(); Export(STR_VERTICAL_BAR); ExportNonbreakingSpace(); Export("\n");
		}

		// first triplet was finished (table row)

		if (dnes_dnes == EXPORT_DNES_DNES_ANO) {
			// ---------------------------------------------------

			// << predošlý mesiac
			if ((_global_den.mesiac - 1) == MES_JAN) {
				datum.mesiac = MES_DEC + 1;
				_local_rok = _global_den.rok - 1;
			}
			else {
				datum.mesiac = _global_den.mesiac - 1;
				_local_rok = _global_den.rok;
			}
			if (_global_den.den > pocet_dni[datum.mesiac - 1]) {
				datum.den = pocet_dni[datum.mesiac - 1];
			}
			else {
				datum.den = _global_den.den;
			}

			// predošlý mesiac -- button
			if (_global_opt_batch_monthly == NIE) {
				sprintf(pom, HTML_LINK_CALL1, script_name, STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, datum.den, STR_MESIAC, datum.mesiac, STR_ROK, _local_rok, pom2_no_override);
			}// if (_global_opt_batch_monthly == NIE)
			else {
				mystrcpy(pom, STR_EMPTY, MAX_STR);
			}
			if (_global_opt_batch_monthly == NIE) {
				if (som_v_tabulke == ANO) {
					Export("<" HTML_TABLE_ROW ">\n");
					ExportTableCell(HTML_TABLE_CELL);
					Export_HtmlForm(pom);
					Export(HTML_FORM_INPUT_SUBMIT0 " title=\"%s %s %s\" value=\"" HTML_LEFT_ARROW " ", html_button_predchadzajuci_[_global_jazyk], html_text_mesiac[_global_jazyk], _vytvor_string_z_datumu(VSETKY_DNI, datum.mesiac, _local_rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
					Export((char *)html_text_mesiac[_global_jazyk]);
					Export(" \"" HTML_FORM_INPUT_END "\n");
					Export("</form>\n");
					Export(HTML_TABLE_CELL_END "\n");
				}
				else {
					Export(HTML_A_HREF_BEGIN "\"%s\">" HTML_LEFT_ARROW " %s %s %s" HTML_A_END "\n", pom, html_button_predchadzajuci_[_global_jazyk], html_text_mesiac[_global_jazyk], _vytvor_string_z_datumu(VSETKY_DNI, datum.mesiac, _local_rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
					ExportNonbreakingSpace(); Export(STR_VERTICAL_BAR); ExportNonbreakingSpace(); Export("\n");
				}
			}

			// možnosť skryť všetky tlačidlá (celý komponent s navigáciou)

			// obnovenie na "dnes"
			datum.den = _global_den.den;
			datum.mesiac = _global_den.mesiac;
			_local_rok = _global_den.rok;

			if (_global_opt_batch_monthly == NIE) {
				// najprv upravíme o2
				_global_opt_orig = _global_opt[OPT_2_HTML_EXPORT]; // backup pôvodnej hodnoty
				// nastavenie parametra o1: pridáme BIT_OPT_2_HIDE_NAVIG_BUTTONS pre alternatívnu psalmódiu
				if (!isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_NAVIG_BUTTONS)) {
					Log("Pre option %d nastavujem bit pre '%ld'\n", OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_NAVIG_BUTTONS);
					_global_opt[OPT_2_HTML_EXPORT] += BIT_OPT_2_HIDE_NAVIG_BUTTONS;
				}// zmena: použitie doplnkovej psalmódie
				else {
					Log("Pre option %d ruším bit pre '%ld'\n", OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_NAVIG_BUTTONS);
					_global_opt[OPT_2_HTML_EXPORT] -= BIT_OPT_2_HIDE_NAVIG_BUTTONS;
				}

				mystrcpy(pom2, STR_EMPTY, MAX_STR);
				mystrcpy(pom3, STR_EMPTY, MAX_STR);
				// teraz vytvoríme reťazec s options
				prilep_request_options(pom2, pom3);

				sprintf(pom, HTML_LINK_CALL1, script_name, STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, datum.den, STR_MESIAC, datum.mesiac, STR_ROK, _local_rok, pom2);

				Export("<" HTML_TABLE_CELL_CENTER ">\n");
				Export(HTML_A_HREF_BEGIN "\"%s\" " HTML_CLASS_SMALL ">(%s)" HTML_A_END, pom, html_text_option_skryt[_global_jazyk]);
				Export("\n");
				Export(HTML_TABLE_CELL_END "\n");

				// napokon o2 vrátime späť
				_global_opt[OPT_2_HTML_EXPORT] = _global_opt_orig; // restore pôvodnej hodnoty

				mystrcpy(pom2, STR_EMPTY, MAX_STR);
				mystrcpy(pom3, STR_EMPTY, MAX_STR);
				// teraz vytvoríme reťazec s options (revert)
				prilep_request_options(pom2, pom3);
			}// if (_global_opt_batch_monthly == NIE)
			else {
				mystrcpy(pom, STR_EMPTY, MAX_STR);
			}

			// ---------------------------------------------------

			// >> nasledovný mesiac
			if ((_global_den.mesiac - 1) == MES_DEC) {
				datum.mesiac = MES_JAN + 1;
				_local_rok = _global_den.rok + 1;
			}
			else {
				datum.mesiac = _global_den.mesiac + 1;
				_local_rok = _global_den.rok;
			}
			if (_global_den.den > pocet_dni[datum.mesiac - 1]) {
				datum.den = pocet_dni[datum.mesiac - 1];
			}
			else {
				datum.den = _global_den.den;
			}

			// >> nasledovný mesiac -- button
			if (_global_opt_batch_monthly == NIE) {
				sprintf(pom, HTML_LINK_CALL1, script_name, STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, datum.den, STR_MESIAC, datum.mesiac, STR_ROK, _local_rok, pom2_no_override);
			}// if (_global_opt_batch_monthly == NIE)
			else {
				mystrcpy(pom, STR_EMPTY, MAX_STR);
			}
			if (_global_opt_batch_monthly == NIE) {
				if (som_v_tabulke == ANO) {
					ExportTableCell(HTML_TABLE_CELL);
					Export_HtmlForm(pom);
					Export(HTML_FORM_INPUT_SUBMIT0 " title=\"%s %s %s\" value=\"", html_button_nasledujuci_[_global_jazyk], html_text_mesiac[_global_jazyk], _vytvor_string_z_datumu(VSETKY_DNI, datum.mesiac, _local_rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
					Export((char *)html_text_mesiac[_global_jazyk]);
					Export(" " HTML_RIGHT_ARROW "\"" HTML_FORM_INPUT_END "\n");
					Export("</form>\n");
					Export(HTML_TABLE_CELL_END "\n");
					Export(HTML_TABLE_ROW_END "\n");
				}
				else {
					Export(HTML_A_HREF_BEGIN "\"%s\">" HTML_LEFT_ARROW " %s %s %s" HTML_A_END "\n", pom, html_button_nasledujuci_[_global_jazyk], html_text_mesiac[_global_jazyk], _vytvor_string_z_datumu(VSETKY_DNI, datum.mesiac, _local_rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
					ExportNonbreakingSpace(); Export(STR_VERTICAL_BAR); ExportNonbreakingSpace(); Export("\n");
				}
			}

		}// predošlý, nasledovný rok -- len pre "dnes" (second triplet)

		if (dnes_dnes == EXPORT_DNES_DNES_ANO) {
			// ---------------------------------------------------

			// vypočítanie toho istého dňa v predošlom roku
			datum.den = _global_den.den;
			datum.mesiac = _global_den.mesiac;
			_local_rok = _global_den.rok - 1;
			if ((_global_den.den == 29) && (_global_den.mesiac - 1 == MES_FEB)) { // 29FEB
				if (!prestupny(_local_rok)) {
					datum.den = 28;
				}
			}

			// << predošlý rok -- button
			if (_global_opt_batch_monthly == NIE) {
				sprintf(pom, HTML_LINK_CALL1, script_name, STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, datum.den, STR_MESIAC, datum.mesiac, STR_ROK, _local_rok, pom2_no_override);
			}// if (_global_opt_batch_monthly == NIE)
			else {
				mystrcpy(pom, STR_EMPTY, MAX_STR);
			}
			if (_global_opt_batch_monthly == NIE) {
				if (som_v_tabulke == ANO) {
					Export("<" HTML_TABLE_ROW ">\n");
					ExportTableCell(HTML_TABLE_CELL);
					Export_HtmlForm(pom);
					Export(HTML_FORM_INPUT_SUBMIT0 " title=\"%s %s %d\" value=\"" HTML_LEFT_ARROW_HUGE " ", html_button_predchadzajuci_[_global_jazyk], html_text_rok[_global_jazyk], _local_rok);
					Export((char *)html_text_rok[_global_jazyk]);
					Export(" \"" HTML_FORM_INPUT_END "\n");
					Export("</form>\n");
					Export(HTML_TABLE_CELL_END "\n");
				}
				else {
					Export(HTML_A_HREF_BEGIN "\"%s\">" HTML_LEFT_ARROW_HUGE " %s %s %d" HTML_A_END "\n", pom, html_button_predchadzajuci_[_global_jazyk], html_text_rok[_global_jazyk], _local_rok);
					ExportNonbreakingSpace(); Export(STR_VERTICAL_BAR); ExportNonbreakingSpace(); Export("\n");
				}
			}

			if (som_v_tabulke == ANO) {
				ExportEmptyCell();
			}

			// ---------------------------------------------------

			// vypočítanie toho istého dňa v nasledujúcom roku
			datum.den = _global_den.den;
			datum.mesiac = _global_den.mesiac;
			_local_rok = _global_den.rok + 1;
			if ((_global_den.den == 29) && (_global_den.mesiac - 1 == MES_FEB)) { // 29FEB
				if (!prestupny(_local_rok)) {
					datum.den = 28;
				}
			}
			// nasledujúci rok -- button
			if (_global_opt_batch_monthly == NIE) {
				sprintf(pom, HTML_LINK_CALL1, script_name, STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, datum.den, STR_MESIAC, datum.mesiac, STR_ROK, _local_rok, pom2_no_override);
			}// if (_global_opt_batch_monthly == NIE)
			else {
				mystrcpy(pom, STR_EMPTY, MAX_STR);
			}
			if (_global_opt_batch_monthly == NIE) {
				if (som_v_tabulke == ANO) {
					ExportTableCell(HTML_TABLE_CELL);
					Export_HtmlForm(pom);
					Export(HTML_FORM_INPUT_SUBMIT0 " title=\"%s %s %d\" value=\"", html_button_nasledujuci_[_global_jazyk], html_text_rok[_global_jazyk], _local_rok);
					Export((char *)html_text_rok[_global_jazyk]);
					Export(" " HTML_RIGHT_ARROW_HUGE "\"" HTML_FORM_INPUT_END "\n");
					Export("</form>\n");
					Export(HTML_TABLE_CELL_END "\n");
					Export(HTML_TABLE_ROW_END "\n");
				}
				else {
					Export(HTML_A_HREF_BEGIN "\"%s\">%s %s %d " HTML_RIGHT_ARROW_HUGE "" HTML_A_END "\n", pom, html_button_nasledujuci_[_global_jazyk], html_text_rok[_global_jazyk], _local_rok);
					ExportNonbreakingSpace(); Export(STR_VERTICAL_BAR); ExportNonbreakingSpace(); Export("\n");
				}
			}
		}// predošlý, nasledovný rok -- len pre "dnes" (last triplet)

		if (som_v_tabulke == ANO) {
			// row was closed for each of triplet
			Export(HTML_TABLE_END "\n");
		}

	}// if (typ)
	else {
		// inak buttony nedávam
		Log("--- _export_rozbor_dna_buttons_dni(): buttony nedávam...\n");
	}

	if ((_global_pocet_navigacia > 1) || (_global_pocet_volani_interpretTemplate >= 2)) {
		// najprv ostatné, potom dnes
		if ((query_type == PRM_DATUM) && (_global_modlitba != MODL_NEURCENA)) {

			_export_rozbor_dna_buttons_dni_dnes(EXPORT_DNES_DNES_ANO, NIE /* som_v_tabulke */, pom2, ANO /* zobraz_odkaz_na_skrytie */);

		}
	}// if ((_global_pocet_navigacia > 1) || (_global_pocet_volani_interpretTemplate >= 2))

	// späť pôvodné nastavenia (pre dnes_dnes != EXPORT_DNES_DNES_ANO boli zmenené)
	_global_den.den = _orig_den;
	_global_den.mesiac = _orig_mesiac;
	_global_den.rok = _orig_rok;
#ifdef OS_Windows_Ruby
	ExportHtmlComment("buttons/dni/compact:end");
#endif
	Log("--- _export_rozbor_dna_buttons_dni_compact(typ == %d) -- end\n", typ);
} // _export_rozbor_dna_buttons_dni_compact()

// enable to display date-navigation buttons in compact mode also for online web
void _export_rozbor_dna_buttons_dni_call(short int typ, short int dnes_dnes) {
#ifdef OS_Windows_Ruby
	ExportHtmlComment("buttons/dni/call:begin");
#endif
	if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTONY_USPORNE)) {
		_export_rozbor_dna_buttons_dni_compact(typ, dnes_dnes);
	}
	else {
		_export_rozbor_dna_buttons_dni_orig(typ, dnes_dnes);
	}
#ifdef OS_Windows_Ruby
	ExportHtmlComment("buttons/dni/call:end");
#endif
} // _export_rozbor_dna_buttons_dni_call()

// typ - ako v _export_rozbor_dna()
//
// exportuje kalendárik
void _export_rozbor_dna_kalendar(short int typ) {
	// 2012-10-01: zobrazujeme, iba ak nie je explicitne vyžiadané skrývanie
	if (!isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_KALENDAR)) {
		_export_rozbor_dna_kalendar_core(typ);
	}
	else {
		char show[SMALL] = STR_EMPTY;
		char hide[SMALL] = STR_EMPTY;
		sprintf(show, "%s %s", html_text_option_zobrazit[_global_jazyk], html_text_kalendar[_global_jazyk]);
		sprintf(hide, "%s %s", html_text_option_skryt[_global_jazyk], html_text_kalendar[_global_jazyk]);
		char before[SMALL] = STR_EMPTY;
		sprintf(before, HTML_P_CENTER_SMALL);
		char after[SMALL] = STR_EMPTY;
		mystrcpy(after, HTML_P_END, SMALL);
		_export_link_show_hide(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_KALENDAR, show, hide, (char *)STR_EMPTY, (char *)HTML_CLASS_QUIET, before, after, (char *)STR_EMPTY, (char *)STR_EMPTY);
	}
} // _export_rozbor_dna_kalendar()

void _export_rozbor_dna_kalendar_core(short int typ) {
	Log("--- _export_rozbor_dna_kalendar_core(typ == %d) -- begin\n", typ);
	ExportHtmlComment("kalendar");

	if ((typ != EXPORT_DNA_VIAC_DNI) && (typ != EXPORT_DNA_VIAC_DNI_SIMPLE) && (typ != EXPORT_DNA_VIAC_DNI_TXT)) {
		Log("--- _export_rozbor_dna_kalendar_core(): idem tlacit kalendar...\n");
		short int i, j, k;

		// hypertextový odkaz "(skryť)" sa neexportuje pre batch mód; nestačí porovnanie query_type != PRM_BATCH_MODE, pretože sa volá napr. "..\breviar.exe -i..\..\..\breviar.sk\include\ -qpdt -d6 -m1 -r2013 -u0 -e130106.htm -00 -15184 -2224 -30 -40 -jsk -M2 -I1301.htm"
		if (_global_opt_batch_monthly != ANO && query_type != PRM_BATCH_MODE) {
			char before[SMALL] = STR_EMPTY;
			sprintf(before, HTML_P_CENTER_SMALL);
			char after[SMALL] = STR_EMPTY;
			mystrcpy(after, HTML_P_END, SMALL);
			_export_link_show_hide(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_KALENDAR, (char *)html_text_option_zobrazit[_global_jazyk], (char *)html_text_option_skryt[_global_jazyk], (char *)STR_EMPTY, (char *)HTML_CLASS_QUIET, before, after, (char *)STR_EMPTY, (char *)STR_EMPTY);
		}

		Export("\n<div " HTML_CLASS_CALENDAR ">\n");
		// zoznam dní vo forme kalendárika
		Export("<" HTML_TABLE ">\n");

		// ---------------- table caption begin
		// was colspan="7" | nadpis tabuľky v tvare: << mesiac rok >>
		Export("<" HTML_TABLE_CAPTION ">\n");

		// << predošlý mesiac
		if ((_global_den.mesiac - 1) == MES_JAN) {
			j = MES_DEC + 1;
			k = _global_den.rok - 1;
		}
		else {
			j = _global_den.mesiac - 1;
			k = _global_den.rok;
		}
		if (_global_den.den > pocet_dni[j - 1]) {
			i = pocet_dni[j - 1];
		}
		else {
			i = _global_den.den;
		}
		Vytvor_global_link(i, j, k, LINK_DEN_MESIAC_PREDOSLY, NIE);
		Export("<" HTML_CALENDAR_HEADING ">%s" HTML_SPAN_END "\n", _global_link);

		ExportNonbreakingSpace(); // oddelenie << a mesiaca

		// názov mesiaca
		Vytvor_global_link(VSETKY_DNI, _global_den.mesiac, _global_den.rok, LINK_DEN_MESIAC, NIE);
		Export("<" HTML_CALENDAR_HEADING ">%s" HTML_SPAN_END "\n", _global_link);

		ExportNonbreakingSpace(); // oddelenie mesiaca a roka

		// rok
		if (_global_opt_batch_monthly == NIE) {
			Vytvor_global_link(VSETKY_DNI, VSETKY_MESIACE, _global_den.rok, LINK_DEN_MESIAC, NIE);
		}// if (_global_opt_batch_monthly == NIE)
		else {
			sprintf(_global_link, "%d", _global_den.rok);
		}// else if (_global_opt_batch_monthly == NIE)
		Export("<" HTML_CALENDAR_HEADING ">%s" HTML_SPAN_END "\n", _global_link);

		ExportNonbreakingSpace(); // oddelenie roka a >>

		// >> nasledovný mesiac
		if ((_global_den.mesiac - 1) == MES_DEC) {
			j = MES_JAN + 1;
			k = _global_den.rok + 1;
		}
		else {
			j = _global_den.mesiac + 1;
			k = _global_den.rok;
		}
		if (_global_den.den > pocet_dni[j - 1]) {
			i = pocet_dni[j - 1];
		}
		else {
			i = _global_den.den;
		}
		Vytvor_global_link(i, j, k, LINK_DEN_MESIAC_NASLEDOVNY, NIE);
		Export("<" HTML_CALENDAR_HEADING ">%s" HTML_SPAN_END "\n", _global_link);

		Export(HTML_TABLE_CAPTION_END "\n");
		// ---------------- table caption end

		// prvý riadok tabuľky "hlavička" so skratkami dní v týždni
		Export("<" HTML_TABLE_ROW ">\n");
		ExportHtmlComment("(header)");

		for (k = DEN_NEDELA; k <= DEN_SOBOTA; k++) {
			Export("<" HTML_TABLE_CELL "><" HTML_CALENDAR_DAYS ">%s" HTML_SPAN_END "" HTML_TABLE_CELL_END "\n", (char *)nazov_Dn(k));
		}
		Export(HTML_TABLE_ROW_END "\n");

		Export("<" HTML_TABLE_ROW ">\n");
		ExportHtmlComment("(line-1)");

		// prípadné prázdne bunky
		j = ((1 + _global_den.denvt - _global_den.den) MOD 7);
		if (j < 0) {
			j += 7;
		}
		if (j > 0) {
			for (k = 0; k < j; k++) {
				Export("<" HTML_TABLE_CELL ">");
				ExportNonbreakingSpace();
				Export(HTML_COMMENT_BEGIN "_(%s)_" HTML_COMMENT_END "" HTML_TABLE_CELL_END, (char*)nazov_Dn(k));
			}
		}

		// jednotlivé dni mesiaca
		for (i = 1; i <= pocet_dni[_global_den.mesiac - 1]; i++) {
			if (i == _global_den.den) {
				if (((i + _global_den.denvt - _global_den.den) MOD 7) == 0) {
					Export(HTML_TABLE_ROW_END "\n");

					Export("<" HTML_TABLE_ROW ">\n");
					ExportHtmlComment("(line-next)");

					// nedeľa
					Export("<" HTML_TABLE_CELL "><" HTML_CALENDAR_TODAY_SUNDAY ">%d" HTML_SPAN_END "" HTML_TABLE_CELL_END "\n", i);
				}
				else {
					Export("<" HTML_TABLE_CELL "><" HTML_CALENDAR_TODAY ">%d" HTML_SPAN_END "" HTML_TABLE_CELL_END "\n", i);
				}
			}
			else {
				if (((i + _global_den.denvt - _global_den.den) MOD 7) == 0) {
					vytvor_global_link_class(i, _global_den.mesiac, _global_den.rok, LINK_DEN, NIE, (char *)HTML_CLASS_NAME_CALENDAR_SUNDAY);
					Export(HTML_TABLE_ROW_END "\n");

					Export("<" HTML_TABLE_ROW ">\n");
					ExportHtmlComment("(line-next)");

					// nedeľa
					Export("<" HTML_TABLE_CELL ">%s" HTML_TABLE_CELL_END "\n", _global_link);
				}
				else {
					vytvor_global_link_class(i, _global_den.mesiac, _global_den.rok, LINK_DEN, NIE, (char *)HTML_CLASS_NAME_CALENDAR_DAY);
					Export("<" HTML_TABLE_CELL ">%s" HTML_TABLE_CELL_END "\n", _global_link);
				}
			}
		}

		// prípadné prázdne bunky
		j = ((pocet_dni[_global_den.mesiac - 1] + _global_den.denvt - _global_den.den) MOD 7);
		if (j < 0) {
			j += 7;
		}
		if (j < 6) {
			for (k = j + 1; k < 7; k++) {
				Export("<" HTML_TABLE_CELL ">");
				ExportNonbreakingSpace(); 
				Export("" HTML_COMMENT_BEGIN "_(%s)_" HTML_COMMENT_END "" HTML_TABLE_CELL_END, (char*)nazov_Dn(k));
			}
		}

		Export(HTML_TABLE_ROW_END "\n");
		Export(HTML_TABLE_END "\n");

		Export(HTML_DIV_END"\n");
	}// if (typ)
	else {
		// inak kalendar nedavam
		Log("--- _export_rozbor_dna_kalendar(): kalendár nedávam...\n");
	}

	Export("\n");
	Log("--- _export_rozbor_dna_kalendar_core(typ == %d) -- end\n", typ);
} // _export_rozbor_dna_kalendar_core()

void _export_main_formular_checkbox(short int opt, unsigned long long bit_opt, const char* str_modl_force_opt, const char* html_text_opt_description, const char* html_text_opt_description_explain, short int line_break_before = ANO) {
	Log("_export_main_formular_checkbox(%d, %llu, %s, %s, %s) -- begin...\n", opt, bit_opt, str_modl_force_opt, html_text_opt_description, html_text_opt_description_explain);
	char html_label[MAX_STR];
	mystrcpy(html_label, html_text_opt_description, MAX_STR);
#if defined(OS_Windows_Ruby) || defined(DEBUG)
	char html_label_debug[SMALL];
	sprintf(html_label_debug, " [%s]", str_modl_force_opt);
	strcat(html_label, html_label_debug);
#endif

	// pole (checkbox) WWW_/str_modl_force_opt
	if (line_break_before == ANO) {
		Export(HTML_CRLF_LINE_BREAK);
	}

	Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", str_modl_force_opt, NIE);

	Export(HTML_FORM_INPUT_CHECKBOX" name=\"%s\" value=\"%d\" title=\"%s\"%s" HTML_FORM_INPUT_END "\n", str_modl_force_opt, ANO, html_text_opt_description_explain, ((_global_force_opt[opt] & bit_opt) == bit_opt) ? html_option_checked : STR_EMPTY);

	Export("<" HTML_SPAN_TOOLTIP ">", html_text_opt_description_explain);

	_export_link_show_hide(opt, bit_opt, (char*)html_label, (char*)html_label, (char*)STR_EMPTY, (char*)STR_EMPTY, (char*)STR_EMPTY, (char*)STR_EMPTY, (char*)STR_EMPTY, (char*)STR_EMPTY, 0, 0); // Export("%s", html_label);

	Export(HTML_SPAN_END);

	Log("_export_main_formular_checkbox(%d, %llu, %s, %s, %s) -- end.\n", opt, bit_opt, str_modl_force_opt, html_text_opt_description, html_text_opt_description_explain);
} // _export_main_formular_checkbox()

void _export_main_formular_checkbox_slash(short int opt, long bit_opt, const char* str_modl_force_opt, const char* html_text_opt_description1, const char* html_text_opt_description2, short int line_break_before = ANO) {
	Log("_export_main_formular_checkbox(%d, %ld, %s, %s / %s) -- begin...\n", opt, bit_opt, str_modl_force_opt, html_text_opt_description1, html_text_opt_description2);
	char html_label[MAX_STR];
	sprintf(html_label, "%s%s%s", html_text_opt_description1, (line_break_before == ANO) ? HTML_SLASH_SPACE_LOONG_LINE_BREAK : HTML_SLASH_SPACE_LOONG, html_text_opt_description2);

	_export_main_formular_checkbox(opt, bit_opt, str_modl_force_opt, html_label, STR_EMPTY, line_break_before);

	Log("_export_main_formular_checkbox(%d, %ld, %s, %s / %s) -- end.\n", opt, bit_opt, str_modl_force_opt, html_text_opt_description1, html_text_opt_description2);
} // _export_main_formular_checkbox()

// generuje celý formulár, dolnú časť, ktorá pôvodne bola v _main_dnes(), ktorý obsahuje:
// -- okienka pre deň, mesiac, rok; 
// -- okienko pre (analýzu) rok;
// -- okienko pre sviatok,
// -- okienko pre liturgický kalendár,
// atď. a to kvôli tomu, aby sa to eventuálne dalo použiť aj pre iný deň ako "dnes".
void _export_main_formular(short int den, short int mesiac, short int rok, short int denvt) {
	struct tm dnes;
	short int month, day;
	short int lo; // liturgické obdobie
	short int font;

	dnes.tm_mday = den;
	dnes.tm_mon  = mesiac;
	dnes.tm_year = rok;
	dnes.tm_wday = denvt;

	char pom2[MAX_STR];
	mystrcpy(pom2, STR_EMPTY, MAX_STR);
	char pom3[MAX_STR];
	mystrcpy(pom3, STR_EMPTY, MAX_STR);

	prilep_request_options(pom2, pom3);

	char action[MAX_STR];
	mystrcpy(action, STR_EMPTY, MAX_STR);

	// before, after -- kvôli (skryť), (zobraziť)
	char before[SMALL] = STR_EMPTY;
	sprintf(before, "<" HTML_SPAN_SMALL ">");
	char after[SMALL] = STR_EMPTY;
	sprintf(after, HTML_SPAN_END);

	short int zobrazit_moznosti1 = (!isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_OPTIONS1));
	short int zobrazit_moznosti2 = (!isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_OPTIONS2));

#if defined(OS_Windows_Ruby)
	// ---------------- language selection begin
	Export("<" HTML_TABLE ">\n");
	Export("<" HTML_TABLE_ROW ">\n");
	Export("<" HTML_TABLE_CELL_CENTER ">\n");

	sprintf(action, "%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d%s", script_name, STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, _global_den.den, STR_MESIAC, _global_den.mesiac, STR_ROK, _global_den.rok, pom2);
	Export_HtmlFormPOST(action);

	ExportHtmlComment("language selection combobox");

	Export(HTML_DIV_BEGIN);

	Export("<" HTML_SPAN_TOOLTIP ">%s:" HTML_SPAN_END, html_text_jazyk_explain[_global_jazyk], html_text_jazyk_verzia[_global_jazyk]);

	Export(HTML_LINE_BREAK);

	// drop-down list pre výber jazyka
	// pole WWW_JAZYK
	Export(HTML_FORM_SELECT"name=\"%s\" title=\"%s\">\n", STR_JAZYK, html_text_jazyk_explain[_global_jazyk]);

	for (int i = 0; i <= POCET_JAZYKOV; i++) {
		// supported languages explicitly defined
		if (supported_languages[i]) {
			Export("<option%s>%s</option>\n", (i != _global_jazyk) ? STR_EMPTY : html_option_selected, nazov_jazyka_native_jazyk(i));
		}
	}
	Export("</select>");

	ExportHtmlComment("submit button (language)");

	// button Nastaviť/Potvrdiť
	Export(HTML_FORM_INPUT_SUBMIT" value=\"");
	Export((char *)HTML_BUTTON_DNES_APPLY_SETTINGS);
	Export("\"" HTML_FORM_INPUT_END "\n");

	Export(HTML_DIV_END);

	Export("</form>\n");

	Export(HTML_TABLE_CELL_END "\n");
	Export(HTML_TABLE_ROW_END "\n");
	Export(HTML_TABLE_END "\n");
	// ---------------- language selection end
#endif

	// ---------------- calendar selection begin
	if (supported_calendars_count[_global_jazyk] > 1) {
		Log("exporting calendars (count for this language == %d)...", supported_calendars_count[_global_jazyk]);

		Export("<" HTML_TABLE ">\n");
		Export("<" HTML_TABLE_ROW ">\n");
		Export("<" HTML_TABLE_CELL_CENTER ">\n");

		sprintf(action, "%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d%s", script_name, STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, _global_den.den, STR_MESIAC, _global_den.mesiac, STR_ROK, _global_den.rok, pom2);
		Export_HtmlFormPOST(action);

		ExportHtmlComment("calendar selection combobox");

		Export(HTML_DIV_BEGIN);

		Export("<" HTML_SPAN_TOOLTIP ">%s%s" HTML_SPAN_END, html_text_kalendar_miestny_explain[_global_jazyk], html_text_kalendar_miestny[_global_jazyk], (equals(html_text_kalendar_miestny_text_after_combo[_global_jazyk], STR_EMPTY) ? ": " : ""));

		Export(HTML_LINE_BREAK);

		// drop-down list pre výber kalendára (propriá)
		// pole WWW_KALENDAR
		Export(HTML_FORM_SELECT"name=\"%s\" title=\"%s\">\n", STR_KALENDAR, html_text_kalendar_miestny_explain[_global_jazyk]);

		short int local_kalendar = _global_kalendar;
		if ((_global_kalendar == KALENDAR_NEURCENY) || (_global_kalendar == KALENDAR_VSEOBECNY)) {
			local_kalendar = default_kalendar[_global_jazyk];
		}

		for (short int c = 0; c < supported_calendars_count[_global_jazyk]; c++) {
			Log("exporting calendars: c == %d, supported_calendars(c) == %d, nazov_kalendara_vyber[supported_calendars(c)] == %s...", c, supported_calendars(c), nazov_kalendara_vyber[supported_calendars(c)]);

			Export("<option%s>%s</option>\n", (local_kalendar == supported_calendars(c)) ? html_option_selected : STR_EMPTY, nazov_kalendara_vyber[supported_calendars(c)]);
		}

		Export("</select>\n");

		// for HU: 
		if (!equals(html_text_kalendar_miestny_text_after_combo[_global_jazyk], STR_EMPTY))
		{
			Export(html_text_kalendar_miestny_text_after_combo[_global_jazyk]);
		}

		ExportHtmlComment("submit button (calendar)");

		// button Nastaviť/Potvrdiť
		Export(HTML_FORM_INPUT_SUBMIT" value=\"");
		Export((char *)HTML_BUTTON_DNES_APPLY_SETTINGS);
		Export("\"" HTML_FORM_INPUT_END "\n");

		Export(HTML_DIV_END);

		Export("</form>\n");

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");
		Export(HTML_TABLE_END "\n");
	}
	// ---------------- calendar selection end

	ExportHtmlComment("TABLE:BEGIN(options)");
	Export("<" HTML_TABLE ">\n");

	// print form with options; export <form> only conditionally
	if (zobrazit_moznosti1) {
		sprintf(action, "%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d%s", script_name, STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, _global_den.den, STR_MESIAC, _global_den.mesiac, STR_ROK, _global_den.rok, pom2);
		// Export("<form action=\"%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d%s\" method=\"post\">\n", script_name, STR_QUERY_TYPE, STR_PRM_DATUM, STR_DEN, _global_den.den, STR_MESIAC, _global_den.mesiac, STR_ROK, _global_den.rok, pom2);
		Export_HtmlFormPOST(action);
	}

	// -------------------------------------------

	Export("<" HTML_TABLE_ROW ">\n");
	ExportTableCell(HTML_TABLE_CELL);

	ExportHtmlComment("heading");

	_export_link_show_hide(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_OPTIONS1, (char *)html_text_option_zobrazit[_global_jazyk], (char *)html_text_option_skryt[_global_jazyk], (char *)STR_EMPTY, (char *)HTML_CLASS_QUIET, before, after, (char *)STR_EMPTY, (char *)STR_EMPTY);

	Export("<" HTML_SPAN_BOLD_IT ">\n");
	Export((char *)html_text_dalsie_moznosti_1[_global_jazyk]);
	Export(HTML_SPAN_END"\n");

	Export(HTML_TABLE_CELL_END "\n");
	Export(HTML_TABLE_ROW_END "\n");

	if (zobrazit_moznosti1) {
		// len ak NIE JE možnosť (skrytie options1) zvolená

#if defined(IO_ANDROID)
		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		Export("<" HTML_SPAN_SMALL ">%s" HTML_SPAN_END "\n", html_text_android_native_menu[_global_jazyk]);

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");
#endif

		// zobrazenie neviditeľných checkboxov, aby sa po submite zmenených nastavení neresetovalo skrytie/zobrazenie kalendára, navigácie a časti "Ďalšie zobrazenia"
		Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_2_HIDE_NAVIG_BUTTONS, (isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_NAVIG_BUTTONS)) ? ANO : NIE);
		Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_2_HIDE_KALENDAR, (isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_KALENDAR)) ? ANO : NIE);
		Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_2_HIDE_OPTIONS1, (isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_OPTIONS1)) ? ANO : NIE);
		Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_2_HIDE_OPTIONS2, (isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_OPTIONS2)) ? ANO : NIE);

		//---------------------------------------------------------------------

#ifdef EXPORT_RITUS_IN_SETTINGS
		// ritus could not be changed (depends on "language"); just print it
		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		Export("%s: %s\n", html_text_ritus[_global_jazyk], nazov_ritu(_global_ritus));

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");
#endif

#if !defined(IO_ANDROID)
		// for Android it is not necessary; version 2.0 implements natively nice menu (though it was in settings earlier)
		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		Export("<" HTML_TABLE_LEFT ">\n"); // main options

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_PRINTED_EDITION
		_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_PRINTED_EDITION, STR_FORCE_BIT_OPT_0_PRINTED_EDITION, html_text_opt_0_printed_edition[_global_jazyk], html_text_opt_0_printed_edition_explain[_global_jazyk], NIE);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_2_ROZNE_MOZNOSTI
		_export_main_formular_checkbox(OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI, STR_FORCE_BIT_OPT_2_ROZNE_MOZNOSTI, html_text_opt_2_moznosti[_global_jazyk], html_text_opt_2_moznosti_explain[_global_jazyk]);

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		Export(HTML_TABLE_END "\n"); // main options

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");
#endif

		// -------------------------------------------

		if (!isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI)) {
			// len ak NIE JE táto možnosť (zobrazovanie všeličoho) zvolená
	
			Export("<" HTML_TABLE_ROW ">\n");
			ExportTableCell(HTML_TABLE_CELL);

			ExportHtmlComment("options-1");

			Export("<" HTML_TABLE_LEFT ">\n"); // option 1 (1/2)

			Export("<" HTML_TABLE_ROW ">\n");
			ExportTableCell(HTML_TABLE_CELL);

			// formular pre options...

			// option 1: zobraziť nasledovné (nemenné, pevné) súčasti modlitby (používame force opt_1)...
			Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s" HTML_SPAN_END, html_text_opt_1_nemenne_sucasti_explain[_global_jazyk], html_text_opt_1_nemenne_sucasti[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_CHV
			_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_CHVALOSPEVY, STR_FORCE_BIT_OPT_1_CHV, html_text_opt_1_chvalospevy[_global_jazyk], html_text_opt_1_chvalospevy_explain[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_SL
			_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_SLAVA_OTCU, STR_FORCE_BIT_OPT_1_SL, html_text_opt_1_slava_otcu[_global_jazyk], html_text_opt_1_slava_otcu_explain[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_RUB
			_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_RUBRIKY, STR_FORCE_BIT_OPT_1_RUB, html_text_opt_1_rubriky[_global_jazyk], html_text_opt_1_rubriky_explain[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_OT
			_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OTCENAS, STR_FORCE_BIT_OPT_1_OT, html_text_opt_1_otcenas[_global_jazyk], html_text_opt_1_otcenas_explain[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_TD
			_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_TEDEUM, STR_FORCE_BIT_OPT_1_TD, html_text_opt_1_tedeum[_global_jazyk], html_text_opt_1_tedeum_explain[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_PLNE_RESP
			_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PLNE_RESP, STR_FORCE_BIT_OPT_1_PLNE_RESP, html_text_opt_1_plne_resp[_global_jazyk], html_text_opt_1_plne_resp_explain[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_ZAVER
			_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZAVER, STR_FORCE_BIT_OPT_1_ZAVER, html_text_opt_1_zaver[_global_jazyk], html_text_opt_1_zaver_explain[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_KOMPL_MARIA_ANT
			_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_KOMPL_MARIA_ANT, STR_FORCE_BIT_OPT_1_KOMPL_MARIA_ANT, html_text_opt_1_maria_ant[_global_jazyk], html_text_opt_1_maria_ant_explain[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_ZOBRAZ_OTCENAS_UVOD
			_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZOBRAZ_OTCENAS_UVOD, STR_FORCE_BIT_OPT_1_ZOBRAZ_OTCENAS_UVOD, html_text_opt_1_otcenas_uvod[_global_jazyk], html_text_opt_1_otcenas_uvod_explain[_global_jazyk]);

			Export(HTML_TABLE_CELL_END "\n");
			Export(HTML_TABLE_ROW_END "\n");

			Export(HTML_TABLE_END "\n"); // option 1 (1/2)

			Export(HTML_TABLE_CELL_END "\n");
			Export(HTML_TABLE_ROW_END "\n");
		} // tabuľka pre checkboxy 1 (options pre modlitbu)
		else {
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_1_CHV, (isGlobalOptionForce(OPT_1_CASTI_MODLITBY, BIT_OPT_1_CHVALOSPEVY)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_1_SL, (isGlobalOptionForce(OPT_1_CASTI_MODLITBY, BIT_OPT_1_SLAVA_OTCU)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_1_RUB, (isGlobalOptionForce(OPT_1_CASTI_MODLITBY, BIT_OPT_1_RUBRIKY)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_1_OT, (isGlobalOptionForce(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OTCENAS)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_1_TD, (isGlobalOptionForce(OPT_1_CASTI_MODLITBY, BIT_OPT_1_TEDEUM)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_1_PLNE_RESP, (isGlobalOptionForce(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PLNE_RESP)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_1_ZAVER, (isGlobalOptionForce(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZAVER)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_1_KOMPL_MARIA_ANT, (isGlobalOptionForce(OPT_1_CASTI_MODLITBY, BIT_OPT_1_KOMPL_MARIA_ANT)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_1_ZOBRAZ_OTCENAS_UVOD, (isGlobalOptionForce(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZOBRAZ_OTCENAS_UVOD)) ? ANO : NIE);
		} // else: treba nastaviť hidden pre všetky options pre _global_force_opt

		//---------------------------------------------------------------------

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		ExportHtmlComment("options-2");

		Export("<" HTML_TABLE_LEFT ">\n"); // option 1 (2/2)

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		// formular pre options...

		if ((isAndroid == NIE) || (!isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI))) {
			// for Android, diplay ONLY when BIT_OPT_2_ROZNE_MOZNOSTI is switched OFF

			// option 1: ďalšie bity ovplyvňujúce vygenerovanú modlitbu (používame force opt_1)...
			Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s" HTML_SPAN_END, html_text_opt_1_dalsie_prepinace_explain[_global_jazyk], html_text_opt_1_dalsie_prepinace[_global_jazyk]);
		}

#if !defined(IO_ANDROID)
		// for Android it is not necessary since 1.11.2 (setting moved to native menu)
		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_ZOBRAZ_SPOL_CAST
		_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZOBRAZ_SPOL_CAST, STR_FORCE_BIT_OPT_1_ZOBRAZ_SPOL_CAST, html_text_opt_1_spolc_svaty[_global_jazyk], html_text_opt_1_spolc_svaty_explain[_global_jazyk]);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_OVERRIDE_STUP_SLAV
		_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OVERRIDE_STUP_SLAV, STR_FORCE_BIT_OPT_1_OVERRIDE_STUP_SLAV, html_text_opt_1_override_stupen_slavenia[_global_jazyk], html_text_opt_1_override_stupen_slavenia_explain[_global_jazyk]);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_STUP_SVIATOK_SLAVNOST
		Export(HTML_CRLF_LINE_BREAK);
		Export(HTML_NONBREAKING_SPACE_LOOONG);
		_export_main_formular_checkbox_slash(OPT_1_CASTI_MODLITBY, BIT_OPT_1_STUP_SVIATOK_SLAVNOST, STR_FORCE_BIT_OPT_1_STUP_SVIATOK_SLAVNOST, html_text_opt_1_slavit_ako_sviatok[_global_jazyk], html_text_opt_1_slavit_ako_slavnost[_global_jazyk], NIE);
#endif

		if (!isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI)) {
			// len ak NIE JE táto možnosť (zobrazovanie všeličoho) zvolená

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_SPOMIENKA_SPOL_CAST
			_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_SPOMIENKA_SPOL_CAST, STR_FORCE_BIT_OPT_1_SPOMIENKA_SPOL_CAST, html_text_opt_1_spomienka_spolcast[_global_jazyk], html_text_opt_1_spomienka_spolcast_explain[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_SKRY_POPIS
			_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_SKRY_POPIS, STR_FORCE_BIT_OPT_1_SKRY_POPIS, html_text_opt_1_skryt_popis_svaty[_global_jazyk], html_text_opt_1_skryt_popis_svaty_explain[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_MCD_DOPLNKOVA
			_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA, STR_FORCE_BIT_OPT_1_MCD_DOPLNKOVA, html_text_opt_1_mcd_zalmy_ine[_global_jazyk], html_text_opt_1_mcd_zalmy_ine_explain[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_MCD_ZALTAR_TRI
			_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_ZALTAR_TRI, STR_FORCE_BIT_OPT_1_MCD_ZALTAR_TRI, html_text_opt_1_mcd_zalmy_tri[_global_jazyk], html_text_opt_1_mcd_zalmy_tri_explain[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_ZALM95
			_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALM95, STR_FORCE_BIT_OPT_1_ZALM95, html_text_opt_1_zalm95[_global_jazyk], html_text_opt_1_zalm95_explain[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_PROSBY_ZVOLANIE
			_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PROSBY_ZVOLANIE, STR_FORCE_BIT_OPT_1_PROSBY_ZVOLANIE, html_text_opt_1_prosby_zvolanie[_global_jazyk], html_text_opt_1_prosby_zvolanie_explain[_global_jazyk]);

			// pole (checkbox) FORCE_BIT_OPT_1_VESP_KRATSIE_PROSBY
			_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_VESP_KRATSIE_PROSBY, STR_FORCE_BIT_OPT_1_VESP_KRATSIE_PROSBY, html_text_opt_1_vesp_kratsie_prosby[_global_jazyk], html_text_opt_1_vesp_kratsie_prosby_explain[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_1_VIGILIA
			_export_main_formular_checkbox(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PC_VIGILIA, STR_FORCE_BIT_OPT_1_VIGILIA, html_text_opt_1_vigilia[_global_jazyk], html_text_opt_1_vigilia_explain[_global_jazyk]);
		}
		else {
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_1_SPOMIENKA_SPOL_CAST, (isGlobalOptionForce(OPT_1_CASTI_MODLITBY, BIT_OPT_1_SPOMIENKA_SPOL_CAST)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_1_SKRY_POPIS, (isGlobalOptionForce(OPT_1_CASTI_MODLITBY, BIT_OPT_1_SKRY_POPIS)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_1_MCD_DOPLNKOVA, (isGlobalOptionForce(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_1_MCD_ZALTAR_TRI, (isGlobalOptionForce(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_ZALTAR_TRI)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_1_ZALM95, (isGlobalOptionForce(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALM95)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_1_PROSBY_ZVOLANIE, (isGlobalOptionForce(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PROSBY_ZVOLANIE)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_1_VESP_KRATSIE_PROSBY, (isGlobalOptionForce(OPT_1_CASTI_MODLITBY, BIT_OPT_1_VESP_KRATSIE_PROSBY)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_1_VIGILIA, (isGlobalOptionForce(OPT_1_CASTI_MODLITBY, BIT_OPT_1_PC_VIGILIA)) ? ANO : NIE);
		} // else: treba nastaviť hidden pre všetky options pre _global_force_opt

#if !defined(IO_ANDROID)
		// for Android it is not necessary; version 2.0 implements natively nice menu (though it was in settings earlier)
		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_2_ALTERNATIVES
		_export_main_formular_checkbox(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES, STR_FORCE_BIT_OPT_2_ALTERNATIVES, html_text_opt_2_alternatives[_global_jazyk], html_text_opt_2_alternatives_explain[_global_jazyk]);
#endif
		
		if (!isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI)) {
			// len ak NIE JE táto možnosť (zobrazovanie všeličoho) zvolená | display only when BIT_OPT_2_ROZNE_MOZNOSTI is on

			// doplnková psalmódia
			Export(HTML_CRLF_LINE_BREAK);
			Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s" HTML_SPAN_END, str_doplnkova_psalmodia[_global_jazyk], str_doplnkova_psalmodia[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_DOPLNK_PSALM_122_129
			_export_main_formular_checkbox(OPT_5_ALTERNATIVES, BIT_OPT_5_DOPLNK_PSALM_122_129, STR_FORCE_BIT_OPT_5_DOPLNK_PSALM_122_129, html_text_opt_5_DPsalmZ122_129[_global_jazyk], html_text_opt_5_DPsalmZ122_129_explain[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_DOPLNK_PSALM_126_129
			_export_main_formular_checkbox(OPT_5_ALTERNATIVES, BIT_OPT_5_DOPLNK_PSALM_126_129, STR_FORCE_BIT_OPT_5_DOPLNK_PSALM_126_129, html_text_opt_5_DPsalmZ126_129[_global_jazyk], html_text_opt_5_DPsalmZ126_129_explain[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_DOPLNK_PSALM_127_131
			_export_main_formular_checkbox(OPT_5_ALTERNATIVES, BIT_OPT_5_DOPLNK_PSALM_127_131, STR_FORCE_BIT_OPT_5_DOPLNK_PSALM_127_131, html_text_opt_5_DPsalmZ127_131[_global_jazyk], html_text_opt_5_DPsalmZ127_131_explain[_global_jazyk]);

			// posvätné čítanie
			Export(HTML_CRLF_LINE_BREAK);
			Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s" HTML_SPAN_END, nazov_modlitby(MODL_POSV_CITANIE), nazov_modlitby(MODL_POSV_CITANIE));

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_USE_TWO_YEARS_CYCLE
			_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_USE_TWO_YEARS_CYCLE, STR_FORCE_BIT_OPT_0_USE_TWO_YEARS_CYCLE, html_text_opt_0_use_two_years_cycle[_global_jazyk], html_text_opt_0_use_two_years_cycle_explain[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_TWO_YEARS_CYCLE_ID
			Export(HTML_CRLF_LINE_BREAK);
			Export(HTML_NONBREAKING_SPACE_LOOONG);
			_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_TWO_YEARS_CYCLE_ID, STR_FORCE_BIT_OPT_0_TWO_YEARS_CYCLE_ID, html_text_opt_0_two_years_cycle_id[_global_jazyk], html_text_opt_0_two_years_cycle_id_explain[_global_jazyk], NIE);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_ALTERNATIVE_READINGS
			_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_ALTERNATIVE_READINGS, STR_FORCE_BIT_OPT_0_ALTERNATIVE_READINGS, html_text_opt_0_alternative_readings[_global_jazyk], html_text_opt_0_alternative_readings_explain[_global_jazyk]);

			if (_global_jazyk != JAZYK_CZ) {

				// posvätné čítanie
				Export(HTML_CRLF_LINE_BREAK);
				Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s (%s)" HTML_SPAN_END, nazov_modlitby(MODL_POSV_CITANIE), nazov_modlitby(MODL_POSV_CITANIE), nazov_obdobia(OBD_CEZ_ROK));

				// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_HYMNUS_PC
				_export_main_formular_checkbox_slash(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_PC, STR_FORCE_BIT_OPT_5_HYMNUS_PC, html_text_opt_5_PCHymnusI[_global_jazyk], html_text_opt_5_PCHymnusII[_global_jazyk]);

				// predpoludním
				Export(HTML_CRLF_LINE_BREAK);
				Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s" HTML_SPAN_END, nazov_modlitby(MODL_PREDPOLUDNIM), nazov_modlitby(MODL_PREDPOLUDNIM));

				// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_HYMNUS_MCD_PREDPOL
				_export_main_formular_checkbox_slash(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_MCD_PREDPOL, STR_FORCE_BIT_OPT_5_HYMNUS_MCD_PREDPOL, html_text_opt_5_MCDPredHymnus1[_global_jazyk], html_text_opt_5_MCDPredHymnus2[_global_jazyk]);

				// napoludnie
				Export(HTML_CRLF_LINE_BREAK);
				Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s" HTML_SPAN_END, nazov_modlitby(MODL_NAPOLUDNIE), nazov_modlitby(MODL_NAPOLUDNIE));

				// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_HYMNUS_MCD_NAPOL
				_export_main_formular_checkbox_slash(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_MCD_NAPOL, STR_FORCE_BIT_OPT_5_HYMNUS_MCD_NAPOL, html_text_opt_5_MCDNaHymnus1[_global_jazyk], html_text_opt_5_MCDNaHymnus2[_global_jazyk]);

				// popoludní
				Export(HTML_CRLF_LINE_BREAK);
				Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s" HTML_SPAN_END, nazov_modlitby(MODL_POPOLUDNI), nazov_modlitby(MODL_POPOLUDNI));

				// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_HYMNUS_MCD_POPOL
				_export_main_formular_checkbox_slash(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_MCD_POPOL, STR_FORCE_BIT_OPT_5_HYMNUS_MCD_POPOL, html_text_opt_5_MCDPoHymnus1[_global_jazyk], html_text_opt_5_MCDPoHymnus2[_global_jazyk]);

				// prvé vešpery
				Export(HTML_CRLF_LINE_BREAK);
				Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s (%s/%s)" HTML_SPAN_END, nazov_modlitby(MODL_PRVE_VESPERY), nazov_modlitby(MODL_PRVE_VESPERY), nazov_dna(DEN_NEDELA), nazov_obdobia(OBD_CEZ_ROK));

				// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_HYMNUS_1VESP
				_export_main_formular_checkbox_slash(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_1VESP, STR_FORCE_BIT_OPT_5_HYMNUS_1VESP, html_text_opt_5_1VHymnusNe[_global_jazyk], html_text_opt_5_1VHymnusPC[_global_jazyk]);

				// kompletórium
				Export(HTML_CRLF_LINE_BREAK);
				Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s" HTML_SPAN_END, nazov_modlitby(MODL_KOMPLETORIUM), nazov_modlitby(MODL_KOMPLETORIUM));

				// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_HYMNUS_KOMPL
				_export_main_formular_checkbox_slash(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_KOMPL, STR_FORCE_BIT_OPT_5_HYMNUS_KOMPL, html_text_opt_5_KomplHymnusA[_global_jazyk], html_text_opt_5_KomplHymnusB[_global_jazyk]);

				// kompletórium v oktávach
				Export(HTML_CRLF_LINE_BREAK);
				Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s (%s, %s)" HTML_SPAN_END, nazov_modlitby(MODL_KOMPLETORIUM), nazov_modlitby(MODL_KOMPLETORIUM), nazov_obdobia(OBD_VELKONOCNA_OKTAVA), nazov_obdobia(OBD_OKTAVA_NARODENIA));

				// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_KOMPLETORIUM_OKTAVA
				_export_main_formular_checkbox_slash(OPT_5_ALTERNATIVES, BIT_OPT_5_KOMPLETORIUM_OKTAVA, STR_FORCE_BIT_OPT_5_KOMPLETORIUM_OKTAVA, html_text_opt_5_KomplOkt1[_global_jazyk], html_text_opt_5_KomplOkt2[_global_jazyk]);

				// hymny vo Veľkonočnom období

				// posvätné čítanie
				Export(HTML_CRLF_LINE_BREAK);
				Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s (%s)" HTML_SPAN_END, nazov_modlitby(MODL_POSV_CITANIE), nazov_modlitby(MODL_POSV_CITANIE), nazov_obdobia(OBD_VELKONOCNE_I));

				// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_HYMNUS_VN_PC
				_export_main_formular_checkbox_slash(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_VN_PC, STR_FORCE_BIT_OPT_5_HYMNUS_VN_PC, html_text_opt_5_PCHymnusVNferia[_global_jazyk], html_text_opt_5_PCHymnusVNnedela[_global_jazyk]);

				// ranné chvály
				Export(HTML_CRLF_LINE_BREAK);
				Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s (%s)" HTML_SPAN_END, nazov_modlitby(MODL_RANNE_CHVALY), nazov_modlitby(MODL_RANNE_CHVALY), nazov_obdobia(OBD_VELKONOCNE_I));

				// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_HYMNUS_VN_RCH
				_export_main_formular_checkbox_slash(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_VN_RCH, STR_FORCE_BIT_OPT_5_HYMNUS_VN_RCH, html_text_opt_5_RChHymnusVNferia[_global_jazyk], html_text_opt_5_RChHymnusVNnedela[_global_jazyk]);

				// vešpery
				Export(HTML_CRLF_LINE_BREAK);
				Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s (%s)" HTML_SPAN_END, nazov_modlitby(MODL_VESPERY), nazov_modlitby(MODL_VESPERY), nazov_obdobia(OBD_VELKONOCNE_I));

				// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_HYMNUS_VN_VESP
				_export_main_formular_checkbox_slash(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_VN_VESP, STR_FORCE_BIT_OPT_5_HYMNUS_VN_VESP, html_text_opt_5_VespHymnusVNferia[_global_jazyk], html_text_opt_5_VespHymnusVNnedela[_global_jazyk]);

				// Cezročné obdobie, 34. týždeň
				Export(HTML_CRLF_LINE_BREAK);
				sprintf(pom3, html_text_tyzden_cislo[_global_jazyk], 34); // pom2 bolo nastavené funkciou prilep_request_options() a používa sa v ďalšom; použiť môžeme pom3
				Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s, %s" HTML_SPAN_END, nazov_obdobia(OBD_CEZ_ROK), nazov_obdobia(OBD_CEZ_ROK), pom3);

				// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_OCR_34_HYMNS
				_export_main_formular_checkbox(OPT_5_ALTERNATIVES, BIT_OPT_5_OCR_34_HYMNS, STR_FORCE_BIT_OPT_5_OCR_34_HYMNS, html_text_opt_5_OCR34Hymns[_global_jazyk], html_text_opt_5_OCR34Hymns_explain[_global_jazyk]);
			}
			else
			{
				// hymny
				Export(HTML_CRLF_LINE_BREAK);
				Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s" HTML_SPAN_END, html_text_opt_5_CZhymny_explain[_global_jazyk], html_text_opt_5_CZhymny[_global_jazyk]);

				// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_CZ_HYMNY_VYBER
				_export_main_formular_checkbox_slash(OPT_5_ALTERNATIVES, BIT_OPT_5_CZ_HYMNY_VYBER, STR_FORCE_BIT_OPT_5_CZ_HYMNY_VYBER, html_text_opt_5_CZhymnyNORMAL[_global_jazyk], html_text_opt_5_CZhymnyRENC[_global_jazyk]);
			} // CZ only

			// ranné chvály na Popolcovú stredu
			Export(HTML_CRLF_LINE_BREAK);
			Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s (%s)" HTML_SPAN_END, nazov_modlitby(MODL_RANNE_CHVALY), nazov_modlitby(MODL_RANNE_CHVALY), text_POPOLCOVA_STREDA[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_POPOL_STREDA_PSALMODIA
			_export_main_formular_checkbox_slash(OPT_5_ALTERNATIVES, BIT_OPT_5_POPOL_STREDA_PSALMODIA, STR_FORCE_BIT_OPT_5_POPOL_STREDA_PSALMODIA, html_text_opt_5_PopolStrPsalm_4STR[_global_jazyk], html_text_opt_5_PopolStrPsalm_3PI[_global_jazyk]);

			// posvätné čítanie na Zelený štvrtok
			Export(HTML_CRLF_LINE_BREAK);
			Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s (%s)" HTML_SPAN_END, nazov_modlitby(MODL_RANNE_CHVALY), nazov_modlitby(MODL_RANNE_CHVALY), text_ZELENY_STVRTOK[_global_jazyk]);

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_ZELENY_STVRTOK_PSALMODIA
			_export_main_formular_checkbox_slash(OPT_5_ALTERNATIVES, BIT_OPT_5_ZELENY_STVRTOK_PSALMODIA, STR_FORCE_BIT_OPT_5_ZELENY_STVRTOK_PSALMODIA, html_text_opt_5_ZelStvPsalm_2STV[_global_jazyk], html_text_opt_5_ZelStvPsalm_3PI[_global_jazyk]);

			// ranné chvály Ofícia za zosnulých
			Export(HTML_CRLF_LINE_BREAK);
			Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s (%s %s)" HTML_SPAN_END, nazov_modlitby(MODL_RANNE_CHVALY), nazov_modlitby(MODL_RANNE_CHVALY), nazov_spolc_oficiumza_jazyk[_global_jazyk], nazov_spolc(MODL_SPOL_CAST_ZA_ZOSNULYCH));

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_OFF_DEF_PSALM_146_150
			_export_main_formular_checkbox(OPT_5_ALTERNATIVES, BIT_OPT_5_OFF_DEF_PSALM_146_150, STR_FORCE_BIT_OPT_5_OFF_DEF_PSALM_146_150, html_text_opt_5_OffDefZ146_150[_global_jazyk], html_text_opt_5_OffDefZ146_150_explain[_global_jazyk]);

			// ranné chvály a vešpery - záver
			Export(HTML_CRLF_LINE_BREAK);
			Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s, %s" HTML_SPAN_END, STR_EMPTY, nazov_modlitby(MODL_RANNE_CHVALY), nazov_modlitby(MODL_VESPERY));

			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_5_OFF_DEF_PSALM_146_150
			_export_main_formular_checkbox(OPT_5_ALTERNATIVES, BIT_OPT_5_ZAVER_KNAZ_DIAKON, STR_FORCE_BIT_OPT_5_ZAVER_KNAZ_DIAKON, html_text_opt_5_zaver_knaz_diakon[_global_jazyk], html_text_opt_5_zaver_knaz_diakon_explain[_global_jazyk]);
		}
		else {
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_5_DOPLNK_PSALM_122_129, (isGlobalOptionForce(OPT_5_ALTERNATIVES, BIT_OPT_5_DOPLNK_PSALM_122_129)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_5_DOPLNK_PSALM_126_129, (isGlobalOptionForce(OPT_5_ALTERNATIVES, BIT_OPT_5_DOPLNK_PSALM_126_129)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_5_DOPLNK_PSALM_127_131, (isGlobalOptionForce(OPT_5_ALTERNATIVES, BIT_OPT_5_DOPLNK_PSALM_127_131)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_5_HYMNUS_PC, (isGlobalOptionForce(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_PC)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_5_HYMNUS_MCD_PREDPOL, (isGlobalOptionForce(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_MCD_PREDPOL)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_5_HYMNUS_MCD_NAPOL, (isGlobalOptionForce(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_MCD_NAPOL)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_5_HYMNUS_MCD_POPOL, (isGlobalOptionForce(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_MCD_POPOL)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_5_HYMNUS_KOMPL, (isGlobalOptionForce(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_KOMPL)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_5_HYMNUS_VN_PC, (isGlobalOptionForce(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_VN_PC)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_5_HYMNUS_VN_RCH, (isGlobalOptionForce(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_VN_RCH)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_5_HYMNUS_VN_VESP, (isGlobalOptionForce(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_VN_VESP)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_5_HYMNUS_1VESP, (isGlobalOptionForce(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_1VESP)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_5_POPOL_STREDA_PSALMODIA, (isGlobalOptionForce(OPT_5_ALTERNATIVES, BIT_OPT_5_POPOL_STREDA_PSALMODIA)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_5_ZELENY_STVRTOK_PSALMODIA, (isGlobalOptionForce(OPT_5_ALTERNATIVES, BIT_OPT_5_ZELENY_STVRTOK_PSALMODIA)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_5_OFF_DEF_PSALM_146_150, (isGlobalOptionForce(OPT_5_ALTERNATIVES, BIT_OPT_5_OFF_DEF_PSALM_146_150)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_5_CZ_HYMNY_VYBER, (isGlobalOptionForce(OPT_5_ALTERNATIVES, BIT_OPT_5_CZ_HYMNY_VYBER)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_5_ZAVER_KNAZ_DIAKON, (isGlobalOptionForce(OPT_5_ALTERNATIVES, BIT_OPT_5_ZAVER_KNAZ_DIAKON)) ? ANO : NIE);
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_5_INVITATORIUM_ANT, (isGlobalOptionForce(OPT_5_ALTERNATIVES, BIT_OPT_5_INVITATORIUM_ANT)) ? ANO : NIE); // not used
		} // else: treba nastaviť hidden pre všetky options pre _global_force_opt

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		Export(HTML_TABLE_END "\n"); // option 1 (2/2)
		
		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		//---------------------------------------------------------------------

#if !defined(IO_ANDROID)
		// for Android it is not necessary since 1.11.2 (setting moved to native menu)

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		ExportHtmlComment("options-3");

		Export("<" HTML_TABLE_LEFT ">\n"); // option 0

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		// formular pre options...

		// option 0: ďalšie bity ovplyvňujúce vygenerovanú modlitbu (číslovanie veršov, biblické referencie...) (používame force opt_0)...
		Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s" HTML_SPAN_END, html_text_opt_0_specialne_explain[_global_jazyk], html_text_opt_0_specialne[_global_jazyk]);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_VERSE
		_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_VERSE, STR_FORCE_BIT_OPT_0_VERSE, html_text_opt_0_verse[_global_jazyk], html_text_opt_0_verse_explain[_global_jazyk]);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_REF
		_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_REFERENCIE, STR_FORCE_BIT_OPT_0_REF, html_text_opt_0_referencie[_global_jazyk], html_text_opt_0_referencie_explain[_global_jazyk]);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_REF_BIBLE_COM
		Export(HTML_CRLF_LINE_BREAK);
		Export(HTML_NONBREAKING_SPACE_LOOONG);
		_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_REF_BIBLE_COM, STR_FORCE_BIT_OPT_0_REF_BIBLE_COM, html_text_opt_0_ref_bible_com[_global_jazyk], html_text_opt_0_ref_bible_com_explain[_global_jazyk], NIE);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_FOOTNOTES
		_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_FOOTNOTES, STR_FORCE_BIT_OPT_0_FOOTNOTES, html_text_opt_0_footnotes[_global_jazyk], html_text_opt_0_footnotes_explain[_global_jazyk]);

#ifdef BEHAVIOUR_WEB
		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_CIT
		_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_CITANIA, STR_FORCE_BIT_OPT_0_CIT, html_text_opt_0_citania[_global_jazyk], html_text_opt_0_citania_explain[_global_jazyk]);
#else
		// else: treba nastaviť hidden pre všetky options pre _global_force_opt
		Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_0_CIT, (isGlobalOptionForce(OPT_0_SPECIALNE, BIT_OPT_0_CITANIA))? ANO: NIE);
#endif

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_TRANSPARENT_NAV
		_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_TRANSPARENT_NAV, STR_FORCE_BIT_OPT_0_TRANSPARENT_NAV, html_text_opt_0_transparent_nav[_global_jazyk], html_text_opt_0_transparent_nav_explain[_global_jazyk]);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_TRANSPARENT_NAV_LEFT
		Export(HTML_CRLF_LINE_BREAK);
		Export(HTML_NONBREAKING_SPACE_LOOONG);
		_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_TRANSPARENT_NAV_LEFT, STR_FORCE_BIT_OPT_0_TRANSPARENT_NAV_LEFT, html_text_opt_0_transparent_nav_left[_global_jazyk], html_text_opt_0_transparent_nav_left_explain[_global_jazyk], NIE);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_SIDE_NAVIGATION
		_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_SIDE_NAVIGATION, STR_FORCE_BIT_OPT_0_SIDE_NAVIGATION, html_text_opt_0_side_navigation[_global_jazyk], html_text_opt_0_side_navigation[_global_jazyk]);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_ZALMY_FULL_TEXT
		_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_ZALMY_FULL_TEXT, STR_FORCE_BIT_OPT_0_ZALMY_FULL_TEXT, html_text_opt_0_zalmy_full_text[_global_jazyk], html_text_opt_0_zalmy_full_text_explain[_global_jazyk]);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_ITALICS_CONDITIONAL
		_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_ITALICS_CONDITIONAL, STR_FORCE_BIT_OPT_0_ITALICS_CONDITIONAL, html_text_opt_0_italics_cond[_global_jazyk], html_text_opt_0_italics_cond_explain[_global_jazyk]);

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		Export(HTML_TABLE_END "\n"); // option 0

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

#endif

		//---------------------------------------------------------------------

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		ExportHtmlComment("options-4");

		Export("<" HTML_TABLE_LEFT ">\n"); // option 2

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		// formular pre options...

#if !defined(IO_ANDROID)
		// Android: this whole section was moved to native menu
		// option 2: bity ovplyvňujúce HTML export -- vygenerované stránky, nie vygenerované modlitby (ISO dátum, button prvé vešpery...) (používame force opt_2)...
		Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s" HTML_SPAN_END, html_text_opt_2_html_export_explain[_global_jazyk], html_text_opt_2_html_export[_global_jazyk]);
#endif

#ifdef OS_Windows_Ruby
		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_2_ISO_DATUM
		_export_main_formular_checkbox(OPT_2_HTML_EXPORT, BIT_OPT_2_ISO_DATUM, STR_FORCE_BIT_OPT_2_ISO_DATUM, html_text_opt_2_iso_datum[_global_jazyk], html_text_opt_2_iso_datum_explain[_global_jazyk]);
#else
		// else: treba nastaviť hidden pre všetky options pre _global_force_opt
		Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_2_ISO_DATUM, (isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_ISO_DATUM))? ANO: NIE);
#endif

#if !defined(IO_ANDROID)
		// Android it is not necessary since 1.13.3 (added to native menu)
		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_2_PRVE_VESPERY
		_export_main_formular_checkbox(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY, STR_FORCE_BIT_OPT_2_PRVE_VESPERY, html_text_opt_2_prve_vespery[_global_jazyk], html_text_opt_2_prve_vespery_explain[_global_jazyk]);
		// Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_2_PRVE_VESPERY, (isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY)) ? ANO : NIE); // else: treba nastaviť hidden pre všetky options pre _global_force_opt

		// font settings moved to native menu for Android app 4.9 and higher
		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_2_FONT_FAMILY
		_export_main_formular_checkbox(OPT_2_HTML_EXPORT, BIT_OPT_2_FONT_FAMILY, STR_FORCE_BIT_OPT_2_FONT_FAMILY, html_text_opt_2_font_family[_global_jazyk], html_text_opt_2_font_family_explain[_global_jazyk]);
		// drop-down list pre výber názvu písma, len ak je nastavená OPT_2_HTML_EXPORT.BIT_OPT_2_FONT_NAME_CHOOSER
		if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_FONT_NAME_CHOOSER)) {
			Export(HTML_CRLF_LINE_BREAK);
			Export(HTML_NONBREAKING_SPACE_LOOONG);
			Export("<" HTML_SPAN_TOOLTIP ">%s" HTML_SPAN_END "\n", html_text_font_name_simple_explain[_global_jazyk], html_text_font_name_simple[_global_jazyk]);

			// pole WWW_/STR_FORCE_BIT_OPT_2_FONT_NAME_CHOOSER
			Export(HTML_FORM_SELECT"name=\"%s\" title=\"%s\">\n", STR_FONT_NAME, html_text_font_name_simple_explain[_global_jazyk]);
			// FONT_CUSTOM neexportujeme do drop-down listu
			for (font = FONT_CUSTOM + 1; font <= POCET_FONTOV; font++) {
				// pom2 bolo nastavené funkciou prilep_request_options() a používa sa v ďalšom; použiť môžeme pom3
				mystrcpy(pom3, nazov_fontu[font], MAX_STR);
				if ((_global_jazyk != JAZYK_SK) && ((font == FONT_CSS) || (font == FONT_CHECKBOX))) {
					if (font == FONT_CSS) {
						mystrcpy(pom3, nazov_fontu_CSS[_global_jazyk], MAX_STR);
					}
					else if (font == FONT_CHECKBOX) {
						mystrcpy(pom3, nazov_fontu_CHECKBOX[_global_jazyk], MAX_STR);
					}
				}
				Export("<option%s>%s</option>\n", (font == _global_font) ? html_option_selected : STR_EMPTY, pom3 /* nazov_fontu[font] */);
			}
			Export("</select>\n");
		}// if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_FONT_NAME_CHOOSER))

		// drop-down list pre výber veľkosti písma WWW_FORCE_BIT_OPT_2_FONT_SIZE, len ak je nastavená OPT_2_HTML_EXPORT.BIT_OPT_2_FONT_NAME_CHOOSER
		if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_FONT_SIZE_CHOOSER)) {
			Export(HTML_CRLF_LINE_BREAK);
			Export(HTML_NONBREAKING_SPACE_LOOONG);
			Export("<" HTML_SPAN_TOOLTIP ">%s" HTML_SPAN_END "\n", html_text_font_size_explain[_global_jazyk], html_text_font_size[_global_jazyk]);

			// pole WWW_/STR_FORCE_BIT_OPT_2_FONT_SIZE
			Export(HTML_FORM_SELECT"name=\"%s\" title=\"%s\">\n", STR_FONT_SIZE, html_text_font_size_explain[_global_jazyk]);
			// FONT_SIZE_UNDEF neexportujeme
			for (font = FONT_SIZE_UNDEF + 1; font <= POCET_FONT_SIZE; font++) {
				Export("<option%s>%s</option>\n", (font == _global_font_size) ? html_option_selected : STR_EMPTY, nazov_font_size(font));
			}
			Export("</select>\n");
		}// if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_FONT_SIZE_CHOOSER))

		// for Android it is not necessary since 1.11 or 1.11.2 (settings moved to native menu)
		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_2_NAVIGATION
		_export_main_formular_checkbox(OPT_2_HTML_EXPORT, BIT_OPT_2_NAVIGATION, STR_FORCE_BIT_OPT_2_NAVIGATION, html_text_opt_2_navigation[_global_jazyk], html_text_opt_2_navigation_explain[_global_jazyk]);

		if ((_global_system == SYSTEM_RUBY) || (_global_jazyk == JAZYK_SK)) {
			// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_2_TEXT_WRAP
			_export_main_formular_checkbox(OPT_2_HTML_EXPORT, BIT_OPT_2_TEXT_WRAP, STR_FORCE_BIT_OPT_2_TEXT_WRAP, html_text_opt_2_textwrap[_global_jazyk], html_text_opt_2_textwrap_explain[_global_jazyk]);
		}
		else {
			Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_2_TEXT_WRAP, (isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_TEXT_WRAP)) ? ANO : NIE);
		}// else: treba nastaviť hidden pre všetky options pre _global_force_opt

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_2_BUTTONY_USPORNE
		_export_main_formular_checkbox(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTONY_USPORNE, STR_FORCE_BIT_OPT_2_BUTTONY_USPORNE, html_text_opt_2_buttons_usporne[_global_jazyk], html_text_opt_2_buttons_usporne_explain[_global_jazyk]);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_2_NOCNY_REZIM
		_export_main_formular_checkbox(OPT_2_HTML_EXPORT, BIT_OPT_2_NOCNY_REZIM, STR_FORCE_BIT_OPT_2_NOCNY_REZIM, html_text_opt_2_nocny_rezim[_global_jazyk], html_text_opt_2_nocny_rezim_explain[_global_jazyk]);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_FONT_NORMAL
		_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_FONT_NORMAL, STR_FORCE_BIT_OPT_0_FONT_NORMAL, html_text_opt_0_font_normal[_global_jazyk], html_text_opt_0_font_normal_explain[_global_jazyk]);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_2_ROUNDED_CORNERS
		_export_main_formular_checkbox(OPT_2_HTML_EXPORT, BIT_OPT_2_ROUNDED_CORNERS, STR_FORCE_BIT_OPT_2_ROUNDED_CORNERS, html_text_opt_2_rounded_corners[_global_jazyk], html_text_opt_2_rounded_corners_explain[_global_jazyk]);
#endif

#if !defined(IO_ANDROID)
		// for Android it is not necessary since 2.0 (TTS implemented natively)
		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_VOICE_OUTPUT
		_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT, STR_FORCE_BIT_OPT_0_VOICE_OUTPUT, html_text_opt_0_voice_output[_global_jazyk], html_text_opt_0_voice_output_explain[_global_jazyk]);
#endif

#if !defined(IO_ANDROID)
		// for Android it is not necessary since 1.11.2 (setting moved to native menu)
		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_BUTTONS_ORDER
		_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_BUTTONS_ORDER, STR_FORCE_BIT_OPT_0_BUTTONS_ORDER, html_text_opt_0_buttons_order[_global_jazyk], html_text_opt_0_buttons_order_explain[_global_jazyk]);
#endif

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		Export(HTML_TABLE_END "\n"); // option 2
		
		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		//---------------------------------------------------------------------

		// for Android it is not necessary since 1.11.2 (settings moved to native menu)
#if !defined(IO_ANDROID)
		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		ExportHtmlComment("option-0");

		Export("<" HTML_TABLE_LEFT ">\n"); // option 0 (1/2)

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		// formular pre options...

		// option 0: bity ovplyvňujúce liturgický kalendár (používame force opt_0)...
		Export("<" HTML_SPAN_BOLD_TOOLTIP ">%s" HTML_SPAN_END, html_text_opt_0_kalendar_explain[_global_jazyk], html_text_opt_0_kalendar[_global_jazyk]);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_ZJAV_NED
		_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA, STR_FORCE_BIT_OPT_0_ZJAV_NED, html_text_opt_0_zjv_ne[_global_jazyk], html_text_opt_0_zjv_ne_explain[_global_jazyk]);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_NAN_NED
		_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA, STR_FORCE_BIT_OPT_0_NAN_NED, html_text_opt_0_nan_ne[_global_jazyk], html_text_opt_0_nan_ne_explain[_global_jazyk]);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_0_TK_NED
		_export_main_formular_checkbox(OPT_0_SPECIALNE, BIT_OPT_0_TELAKRVI_NEDELA, STR_FORCE_BIT_OPT_0_TK_NED, html_text_opt_0_tk_ne[_global_jazyk], html_text_opt_0_tk_ne_explain[_global_jazyk]);

		// pole (checkbox) WWW_/STR_FORCE_BIT_OPT_2_SHOW_DEFAULT_CALENDAR
		_export_main_formular_checkbox(OPT_2_HTML_EXPORT, BIT_OPT_2_SHOW_DEFAULT_CALENDAR, STR_FORCE_BIT_OPT_2_SHOW_DEFAULT_CALENDAR, html_text_opt_2_show_defalut_calendar[_global_jazyk], html_text_opt_2_show_defalut_calendar_explain[_global_jazyk]);

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		Export(HTML_TABLE_END "\n"); // option 0

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");
#endif

		//---------------------------------------------------------------------
		if ((isAndroid == NIE) || (!isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI))) {
			// for Android, diplay ONLY when BIT_OPT_2_ROZNE_MOZNOSTI is switched OFF
			ExportHtmlComment("riadok pre button Nastaviť/Potvrdiť (options)");

			Export("<" HTML_TABLE_ROW ">\n");
			ExportTableCell(HTML_TABLE_CELL);

			Export("<" HTML_TABLE ">\n");

			Export("<" HTML_TABLE_ROW ">\n");
			ExportTableCell(HTML_TABLE_CELL);

			// submit button (1)
			Export(HTML_FORM_INPUT_SUBMIT" value=\"");
			Export((char*)HTML_BUTTON_DNES_APPLY_CHOICES);
			Export("\"" HTML_FORM_INPUT_END "\n");

			Export(HTML_TABLE_CELL_END "\n");
			Export(HTML_TABLE_ROW_END "\n");

			Export(HTML_TABLE_END "\n");

			Export(HTML_TABLE_CELL_END "\n");
			Export(HTML_TABLE_ROW_END "\n");
		}

		Export("</form>\n");
	}

	ExportHtmlComment("TABLE:END(options)");

	Export(HTML_TABLE_END "\n");

	// -------------------------------------------

	ExportHtmlComment("TABLE:BEGIN(choices)");

	Export("<" HTML_TABLE ">\n");

	// export <form> only conditionally
	if (zobrazit_moznosti2) {
		sprintf(action, "%s?%s", uncgi_name, pom2);
		Export_HtmlFormPOST(action);
	}

	Export("<" HTML_TABLE_ROW ">\n");
	ExportTableCell(HTML_TABLE_CELL);

	ExportHtmlComment("heading");

	_export_link_show_hide(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_OPTIONS2, (char *)html_text_option_zobrazit[_global_jazyk], (char *)html_text_option_skryt[_global_jazyk], (char *)STR_EMPTY, (char *)HTML_CLASS_QUIET, before, after, (char *)STR_EMPTY, (char *)STR_EMPTY);

	Export("<" HTML_SPAN_BOLD_IT ">\n");
	Export((char *)html_text_dalsie_moznosti_2[_global_jazyk]);
	Export(HTML_SPAN_END"\n");

	Export(HTML_TABLE_CELL_END "\n");
	Export(HTML_TABLE_ROW_END "\n");

	if (zobrazit_moznosti2) {
		// len ak NIE JE možnosť (skrytie options2) zvolená

		// zobrazenie neviditeľných checkboxov, aby sa po submite zmenených nastavení neresetovalo skrytie/zobrazenie kalendára, navigácie a časti "Ďalšie zobrazenia"
		Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_2_HIDE_NAVIG_BUTTONS, (isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_NAVIG_BUTTONS)) ? ANO : NIE);
		Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_2_HIDE_KALENDAR, (isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_KALENDAR)) ? ANO : NIE);
		Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_2_HIDE_OPTIONS1, (isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_OPTIONS1)) ? ANO : NIE);
		Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_FORCE_BIT_OPT_2_HIDE_OPTIONS2, (isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_HIDE_OPTIONS2)) ? ANO : NIE);

		// -------------------------------------------
		
		short int radio_checked = NIE;

#if defined(OS_Windows_Ruby) || defined(IO_ANDROID)
	// nothing for Android
#else
		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		ExportHtmlComment("TABLE:BEGIN(PRM_DATUM)");

		Export("<" HTML_TABLE_LEFT ">\n");

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		// formular pre PRM_DATUM
		Export(HTML_FORM_INPUT_RADIO" name=\"%s\" value=\"%s\"%s" HTML_FORM_INPUT_END "\n", STR_QUERY_TYPE, STR_PRM_DATUM, radio_checked? html_option_checked: STR_EMPTY);
		radio_checked = NIE;
		Export(HTML_TABLE_CELL_END "\n");
	
		ExportTableCell(HTML_TABLE_CELL);
	
		if (strlen(html_text_modlitby_pre_den[_global_jazyk]) > 0) {
			Export((char *)html_text_modlitby_pre_den[_global_jazyk]);
			Export(" \n");
		}

		if (format_datumu[_global_jazyk] == FORMAT_DATUMU_ROK_MESIAC_DEN) {
			// pole WWW_ROK
			Export(HTML_FORM_INPUT_TEXT_ROK" name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_ROK, dnes.tm_year);

			// pole WWW_MESIAC
			Export(HTML_FORM_SELECT"name=\"%s\">\n", STR_MESIAC);
			for(month = 1; month < 13; month++) {
				Export("<option%s>%s</option>\n", (month == dnes.tm_mon)? html_option_selected: STR_EMPTY, nazov_mesiaca(month - 1));
			}
			Export("\n</select>\n");

			// pole WWW_DEN
			Export(HTML_FORM_SELECT"name=\"%s\">\n", STR_DEN);
			for(day = 1; day < 32; day++) {
				Export("<option%s>%d</option>\n", (day == dnes.tm_mday)? html_option_selected: STR_EMPTY, day);
			}
			Export("\n</select>.\n");

		}// FORMAT_DATUMU_ROK_MESIAC_DEN
		else if (format_datumu[_global_jazyk] == FORMAT_DATUMU_MESIAC_DEN_ROK) {
			// pole WWW_MESIAC
			Export(HTML_FORM_SELECT"name=\"%s\">\n", STR_MESIAC);
			for(month = 1; month < 13; month++) {
				Export("<option%s>%s</option>\n", (month == dnes.tm_mon)? html_option_selected: STR_EMPTY, nazov_mesiaca(month - 1));
			}
			Export("\n</select>\n");

			// pole WWW_DEN
			Export(HTML_FORM_SELECT"name=\"%s\">\n", STR_DEN);
			for(day = 1; day < 32; day++) {
				Export("<option%s>%d</option>\n", (day == dnes.tm_mday)? html_option_selected: STR_EMPTY, day);
			}
			Export("\n</select>.\n");

			// pole WWW_ROK
			Export(HTML_FORM_INPUT_TEXT_ROK" name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_ROK, dnes.tm_year);
		}// FORMAT_DATUMU_MESIAC_DEN_ROK
		else { // if (format_datumu[_global_jazyk] == FORMAT_DATUMU_DEN_MESIAC_ROK) {
			// pole WWW_DEN
			Export(HTML_FORM_SELECT"name=\"%s\">\n", STR_DEN);
			for(day = 1; day < 32; day++) {
				Export("<option%s>%d</option>\n", (day == dnes.tm_mday)? html_option_selected: STR_EMPTY, day);
			}
			Export("\n</select>.\n");

			// pole WWW_MESIAC
			Export(HTML_FORM_SELECT"name=\"%s\">\n", STR_MESIAC);
			for(month = 1; month < 13; month++) {
				Export("<option%s>%s</option>\n", (month == dnes.tm_mon)? html_option_selected: STR_EMPTY, nazov_mesiaca(month - 1));
			}
			Export("\n</select>\n");

			// pole WWW_ROK
			Export(HTML_FORM_INPUT_TEXT_ROK" name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_ROK, dnes.tm_year);
		}// FORMAT_DATUMU_DEN_MESIAC_ROK

		ExportNonbreakingSpace();
		Export((char *)html_text_alebo_pre[_global_jazyk]);
		Export(" ");
		Export(HTML_A_HREF_BEGIN "\"%s?%s=%s" HTML_AMPERSAND "%s\">\n", script_name, STR_QUERY_TYPE, STR_PRM_DNES, pom2); // 2006-08-01: pridaný jazyk; 2011-05-12: bolo nastavené funkciou prilep_request_options()
		Export((char *)html_text_dnesok[_global_jazyk]);
		Export(HTML_A_END"\n");

		Export(HTML_TABLE_CELL_END "\n");

		Export(HTML_TABLE_ROW_END "\n");

		Export(HTML_TABLE_END "\n");

		ExportHtmlComment("TABLE:END(PRM_DATUM)");

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");
#endif

#ifdef FORMULAR_PRE_PRM_SVIATOK
	// -------------------------------------------
		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		Export("<" HTML_TABLE_LEFT ">\n");

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		// formular pre PRM_SVIATOK
		Export(HTML_FORM_INPUT_RADIO" name=\"%s\" value=\"%s\"%s" HTML_FORM_INPUT_END "\n", STR_QUERY_TYPE, STR_PRM_SVIATOK, radio_checked? html_option_checked: STR_EMPTY);
		radio_checked = NIE;

		Export(HTML_TABLE_CELL_END "\n");

		ExportTableCell(HTML_TABLE_CELL);

		// sviatky --- [ToDo]
		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		Export(HTML_TABLE_END "\n");

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");
#endif
		// -------------------------------------------

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		Export("<" HTML_TABLE_LEFT ">\n");

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		// formular pre PRM_ANALYZA_ROKU
		Export(HTML_FORM_INPUT_RADIO" name=\"%s\" value=\"%s\"%s" HTML_FORM_INPUT_END "\n", STR_QUERY_TYPE, STR_PRM_ANALYZA_ROKU, radio_checked ? html_option_checked : STR_EMPTY);
		radio_checked = NIE;

		Export(HTML_TABLE_CELL_END "\n");

		ExportTableCell(HTML_TABLE_CELL);

		Export((char *)html_text_prik_sviatky_atd[_global_jazyk]);
		Export("\n");
		// pole WWW_ANALYZA_ROKU
		Export(HTML_FORM_INPUT_TEXT_ROK" name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_ANALYZA_ROKU, dnes.tm_year);

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		Export(HTML_TABLE_END "\n");

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		// -------------------------------------------
		
		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		Export("<" HTML_TABLE_LEFT ">\n");

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		// formular pre PRM_MESIAC_ROKA
		Export(HTML_FORM_INPUT_RADIO" name=\"%s\" value=\"%s\"%s" HTML_FORM_INPUT_END "\n", STR_QUERY_TYPE, STR_PRM_MESIAC_ROKA, radio_checked ? html_option_checked : STR_EMPTY);
		radio_checked = NIE;

		Export(HTML_TABLE_CELL_END "\n");

		ExportTableCell(HTML_TABLE_CELL);

		Export((char *)html_text_lit_kalendar[_global_jazyk]);
		Export(" \n");
		// pole WWW_MESIAC_ROKA
		Export(HTML_FORM_SELECT"name=\"%s\">\n", STR_MESIAC_ROKA);
		for(month = 1; month < 13; month++) {
			Export("<option%s>%s</option>\n", (month == dnes.tm_mon)? html_option_selected: STR_EMPTY, nazov_mesiaca(month - 1));
		}
		Export("\n</select>\n");

		Export((char *)html_text_roku[_global_jazyk]);
		Export(" \n"); // 2003-07-16; povodne tu bolo "v roku"
		// pole WWW_ROK_ROKA
		Export(HTML_FORM_INPUT_TEXT_ROK" name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_ROK_ROKA, dnes.tm_year);

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		Export(HTML_TABLE_END "\n");

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		// -------------------------------------------

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		Export("<" HTML_TABLE_LEFT ">\n");

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		// formular pre PRM_TABULKA
		Export(HTML_FORM_INPUT_RADIO" name=\"%s\" value=\"%s\"%s" HTML_FORM_INPUT_END "\n", STR_QUERY_TYPE, STR_PRM_TABULKA, radio_checked ? html_option_checked : STR_EMPTY);
		radio_checked = NIE;

		Export(HTML_TABLE_CELL_END "\n");

		ExportTableCell(HTML_TABLE_CELL);

		Export((char *)html_text_tabulka_pohyblive_od[_global_jazyk]);
		ExportNonbreakingSpace();
		// pole WWW_ROK_FROM
		Export(HTML_FORM_INPUT_TEXT_ROK" name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_ROK_FROM, dnes.tm_year - 12);
		ExportNonbreakingSpace();
		Export((char *)html_text_do_roku[_global_jazyk]);
		ExportNonbreakingSpace();
		Export("\n");
		// pole WWW_ROK_TO
		Export(HTML_FORM_INPUT_TEXT_ROK" name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_ROK_TO, dnes.tm_year + 12);

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		Export(HTML_TABLE_CELL_END "\n");

		ExportTableCell(HTML_TABLE_CELL);

		// pole WWW_TABULKA_LINKY
		Export(HTML_NONBREAKING_SPACE_LONG);
		Export(HTML_FORM_INPUT_CHECKBOX" name=\"%s\" value=\"%d\"" HTML_FORM_INPUT_END "\n", STR_TABULKA_LINKY, 1); // ked bude zaskrtnuty, tak vrati hodnotu 1
		ExportNonbreakingSpace();

		Export("<" HTML_SPAN_EXPLAIN ">");
		Export((char *)html_text_zobrazit_linky[_global_jazyk]);
		Export(HTML_SPAN_END);

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		Export(HTML_TABLE_END "\n");

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		// -------------------------------------------

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		Export("<" HTML_TABLE_LEFT ">\n");

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		// formulár pre PRM_STATIC_TEXT, parameter 
		radio_checked = ANO;
		Export(HTML_FORM_INPUT_RADIO" name=\"%s\" value=\"%s\"%s" HTML_FORM_INPUT_END "\n", STR_QUERY_TYPE, STR_PRM_STATIC_TEXT, radio_checked ? html_option_checked : STR_EMPTY);
		radio_checked = NIE;

		Export(HTML_TABLE_CELL_END "\n");

		ExportTableCell(HTML_TABLE_CELL);

		Export((char *)html_text_ordinarium[_global_jazyk]);
		ExportNonbreakingSpace();
		Export((char *)html_text_pre[_global_jazyk]);
		ExportNonbreakingSpace();
		Export(HTML_FORM_INPUT_HIDDEN " name=\"%s\" value=\"%s\"" HTML_FORM_INPUT_END "\n", STR_STATIC_TEXT, skratka_static_text[STATIC_TEXT_ORDINARIUM]);

		Export(HTML_TABLE_CELL_END "\n");

		ExportTableCell(HTML_TABLE_CELL);

		// pole WWW_MODL_ORDINARIUM
		Export(HTML_FORM_SELECT"name=\"%s\">\n", STR_MODL_ORDINARIUM);
		Export("<option>%s</option>\n", nazov_modlitby_short(MODL_INVITATORIUM));
		Export("<option>%s</option>\n", nazov_modlitby_short(MODL_POSV_CITANIE));
		Export("<option%s>%s</option>\n", html_option_selected, nazov_modlitby_short(MODL_RANNE_CHVALY));
		Export("<option>%s</option>\n", nazov_modlitby_short(MODL_PREDPOLUDNIM));
		Export("<option>%s</option>\n", nazov_modlitby_short(MODL_NAPOLUDNIE));
		Export("<option>%s</option>\n", nazov_modlitby_short(MODL_POPOLUDNI));
		Export("<option>%s</option>\n", nazov_modlitby_short(MODL_VESPERY));
		Export("<option>%s</option>\n", nazov_modlitby_short(MODL_KOMPLETORIUM));
		Export("</select>\n");

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		Export(HTML_TABLE_END "\n");

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		// -------------------------------------------
		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		Export("<" HTML_TABLE_LEFT ">\n");

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		// formulár pre PRM_LIT_OBD
		radio_checked = ANO;
		Export(HTML_FORM_INPUT_RADIO" name=\"%s\" value=\"%s\"%s" HTML_FORM_INPUT_END "\n", STR_QUERY_TYPE, STR_PRM_LIT_OBD, radio_checked ? html_option_checked : STR_EMPTY);
		radio_checked = NIE;

		Export(HTML_TABLE_CELL_END "\n");

		ExportTableCell(HTML_TABLE_CELL);

		// pole WWW_MODLITBA
		Export(HTML_FORM_SELECT"name=\"%s\">\n", STR_MODLITBA);
		Export("<option>%s</option>\n", nazov_modlitby_short(MODL_PRVE_VESPERY));
		Export("<option>%s</option>\n", nazov_modlitby_short(MODL_PRVE_KOMPLETORIUM));
		Export("<option>%s</option>\n", nazov_modlitby_short(MODL_INVITATORIUM));
		Export("<option%s>%s</option>\n", html_option_selected, nazov_modlitby_short(MODL_POSV_CITANIE));
		Export("<option>%s</option>\n", nazov_modlitby_short(MODL_RANNE_CHVALY));
		Export("<option>%s</option>\n", nazov_modlitby_short(MODL_PREDPOLUDNIM));
		Export("<option>%s</option>\n", nazov_modlitby_short(MODL_NAPOLUDNIE));
		Export("<option>%s</option>\n", nazov_modlitby_short(MODL_POPOLUDNI));
		Export("<option>%s</option>\n", nazov_modlitby_short(MODL_DRUHE_VESPERY));
		Export("<option>%s</option>\n", nazov_modlitby_short(MODL_DRUHE_KOMPLETORIUM));
		Export("</select>\n");

#if defined(OS_Windows_Ruby) || defined(IO_ANDROID)
		Export(HTML_CRLF_LINE_BREAK);
#else
		ExportNonbreakingSpace();
#endif
		Export((char *)html_text_den[_global_jazyk]);
		ExportNonbreakingSpace();

		// pole WWW_DEN_V_TYZDNI
		Export(HTML_FORM_SELECT"name=\"%s\">\n", STR_DEN_V_TYZDNI);
		for(day = DEN_NEDELA; day <= DEN_SOBOTA; day++) {
			Export("<option%s>%s</option>\n", (day == dnes.tm_wday)? html_option_selected: STR_EMPTY, nazov_dna(day));
		}
		Export("\n</select>\n");

		Export(",\n");
#if defined(OS_Windows_Ruby) || defined(IO_ANDROID)
		Export(HTML_CRLF_LINE_BREAK);
#else
		Export(STR_SPACE);
#endif
		Export((char *)html_text_liturgicky_rok[_global_jazyk]);
		ExportNonbreakingSpace();

		// pole WWW_LIT_ROK
		Export(HTML_FORM_SELECT"name=\"%s\">\n", STR_LIT_ROK);
		for(lo = 'A'; lo <= 'C'; lo++) {
			Export("<option%s>%c</option>\n", (lo == _global_den.litrok)? html_option_selected: STR_EMPTY, lo);
		}
		Export("\n</select>\n");
		Export(", " HTML_LINE_BREAK);

		// pole WWW_TYZDEN
		if (_global_jazyk == JAZYK_LA) {
			Export((char *)html_text_tyzden[_global_jazyk]);
		}
		Export(HTML_FORM_SELECT"name=\"%s\">\n", STR_TYZDEN);
		for(day = 0; day <= POCET_NEDIEL_CEZ_ROK; day++) {
			Export("<option%s>%d</option>\n", (day == _global_den.tyzden)? html_option_selected: STR_EMPTY, day);
		}
		Export("\n</select>");
		ExportNonbreakingSpace();

		if (_global_jazyk != JAZYK_LA) {
			Export((char *)html_text_tyzden[_global_jazyk]);
		}
		Export(",\n");
#if defined(OS_Windows_Ruby) || defined(IO_ANDROID)
		Export(HTML_CRLF_LINE_BREAK);
#else
		Export(STR_SPACE);
#endif

		// pole WWW_LIT_OBD
		Export(HTML_FORM_SELECT"name=\"%s\">\n", STR_LIT_OBD);
		for(lo = 0; lo <= POCET_OBDOBI; lo++) {
			Export("<option%s>%s</option>\n", (lo == _global_den.litobd)? html_option_selected: STR_EMPTY, nazov_obdobia_short(lo));
		}
		Export("\n</select>\n");
		Export(", " HTML_LINE_BREAK);

		// option 3: časti modlitby zo spoločnej časti
		// formulár pre výber preferovanej spoločnej časti
		Export("<" HTML_SPAN_TOOLTIP ">%s" HTML_SPAN_END, /* html_text_spol_casti_vziat_zo_explain[_global_jazyk] */ STR_EMPTY, html_text_spol_casti_vziat_zo[_global_jazyk]);
		Export("\n");

		Export(HTML_CRLF_LINE_BREAK);

		Export(HTML_FORM_SELECT"name=\"%s\" title=\"%s\">\n", STR_FORCE_OPT_3, html_text_spol_casti_vziat_zo_explain[_global_jazyk]);
		for (int i = 0; i <= POCET_SPOL_CASTI; i++) {
			if (poradie_spol_cast[i] == MODL_SPOL_CAST_NEURCENA) {
				continue;
			}
			Export("<option%s>%s</option>\n", ((unsigned)(poradie_spol_cast[i]) != _global_opt[OPT_3_SPOLOCNA_CAST]) ? STR_EMPTY : html_option_selected, nazov_spolc(poradie_spol_cast[i]));
		}
		Export("</select>\n");

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		Export(HTML_TABLE_END "\n");

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		// -------------------------------------------
		ExportHtmlComment("riadok pre button Zobraziť/Vyčistiť (choices)");

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		Export("<" HTML_TABLE ">\n");

		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		// submit button (2)
		Export(HTML_FORM_INPUT_SUBMIT" value=\"");
		Export((char *)HTML_BUTTON_DNES_SHOW);
		Export("\"" HTML_FORM_INPUT_END "\n");

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		Export(HTML_TABLE_END "\n");

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");

		Export("</form>\n\n");
	}

	ExportHtmlComment("TABLE:END(choices)");

	Export(HTML_TABLE_END "\n");

} // _export_main_formular()

// exportuje udaje, ktore nacitala _rozbor_dna() zalozene na _export_rozbor_dna(); 2003-07-07
// ale tento ich exportuje do batch suboru (pre dalsie davkove spracovanie)

// BATCH_COMMAND vygeneruje do batch suboru prikazy, ktore sa pri dalsom behu spustia;
// 2006-02-06: upravené: negenerovať vešpery pre ľubovoľnú spomienku PM (a != PORADIE_PM_SOBOTA)
// 2007-09-25: iba poznámka - možno by bolo dobré tie stringy vytvárať dynamicky pre jednotlivé modlitby (ktoré by sa dali parametrizovať)
// 2008-04-09: makro upravené na funkciu, BATCH_COMMAND() -> execute_batch_command()
void execute_batch_command(short int a, char batch_command[MAX_STR], short int zobrazit_mcd, short int modlitba = MODL_NEURCENA, short int d_from_m_from_r_from = 0) {
	short int i;
	// ak je nastaveny _global_opt_append, tak vsetko do 1 suboru, 2003-07-08
	// 2003-08-11 -Wall upozornila na too many arguments for format
	// 2004-03-11 pridane niektore dalsie parametre
	// 2004-03-16 pridany vypis do batch_html_file
	// 2006-01-31 pridaný zápis modlitby cez deň a posv. čítania
	// 2008-04-09 pridaný zápis modlitby cez deň (predpoludním a popoludní), invitatórium a kompletórium; doplnený jazyk
	// 2008-08-08: bolo kedysi nedokončené: ostáva prilepiť info o css
	// 2009-09-03: podľa nastavenia exportujeme do odlišných súborov odlišné veci
	// 2009-08-04: rozšírené o nepovinný vstupný parameter 'modlitba', ktorý hovorí, či sa majú exportovať všetky modlitby (ako doteraz) alebo len táto modlitba (pre export_monthly_druh >= 1)
	// 2011-03-14: doplnené vyplnenie parametra o5 (_global_opt 5) pre modlitbu cez deň [doteraz sme generovali pre všetky 3 modlitby MCD žalmy "vlastné", teraz pre 2 z nich budeme dávať doplnkovú psalmódiu]
	// 2011-03-18: doplnené exportovanie parametra k (_global_kalendar)
	// 2011-03-23: upravené: negenerovať vešpery pre soboty, ak je nastavené isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY) (hoci sa parameter o8 zatiaľ neexportuje)
	// 2011-04-12: keďže _global_opt 5 sa stáva súčasťou _global_opt 1, nie je potrebné nastaviť o5; je však potrebné správne upraviť o1
	// 2011-04-13: doplnené exportovanie chýbajúcich option 0 až 4
	// 2012-12-12: oprava pre append batch mód; export_fname_pattern
	FILE *batch_export_file = NULL;
	char parameter_M[SMALL] = STR_EMPTY; // parametre pre výsledné HTML (parameter 'M' a parametre pre odkazy na súbory, napr. 'I')
	char parameter_I[SMALL] = STR_EMPTY;
	char poradie_svateho[SMALL] = STR_EMPTY; // pre export_monthly_druh >= 1
	char _local_export_navig_hore[SMALL] = STR_EMPTY;
	unsigned long long _global_opt_1_casti_modlitby_orig; // parameter o1 (_global_opt 1) pre modlitbu cez deň (doplnková psalmódia)
	char export_doplnkova_psalmodia[SMALL] = STR_EMPTY; // reťazec pre alternatívny súbor modlitby cez deň obsahujúci doplnkovú psalmódiu
	char pom[SMALL] = STR_EMPTY; // pomocný reťazec (priliepanie parametrov do export_dalsie_parametre)
	char export_dalsie_parametre[SMALL] = STR_EMPTY; // reťazec pre kalendár (export_kalendar); 2011-11-30: pridaný do toho istého reťazca aj font
	char export_fname_pattern[MAX_STR] = STR_EMPTY; // reťazec, ktorý sa prilepuje na koniec názvu súboru pre ne-append mód // 2013-01-27: rozšírené; pôvodne bolo SMALL, čo ale niekedy nepostačovalo (upozornil peter.chodelka@gmail.com)
	char export_fname_modl_str[SMALL] = STR_EMPTY; // reťazec pre identifikáciu modlitby v názve súboru (ID modlitby alebo char_modlitby[i])

	Log("execute_batch_command(): začiatok...\n");

	_global_opt_1_casti_modlitby_orig = _global_opt[OPT_1_CASTI_MODLITBY]; // backup pôvodnej hodnoty
	// 2011-04-12: nastavenie parametra o1 pre bežnú a doplnkovú psalmódiu; parameter o1 očistíme a _global_opt_1_casti_modlitby_orig bude obsahovať aj bit pre doplnkovú psalmódiu
	// 2011-09-06: neriešime otázku žalmu 95 pre ranné chvály resp. vešpery, kde je použitý žalm 24, 67, 100
	if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA)) {
		Log("Pre option 1 odstraňujem bit pre 'doplnkovú psalmódiu', pomocná premenná to bude obsahovať\n");
		_global_opt[OPT_1_CASTI_MODLITBY] -= BIT_OPT_1_MCD_DOPLNKOVA;
		_global_opt_1_casti_modlitby_orig = _global_opt[OPT_1_CASTI_MODLITBY] + BIT_OPT_1_MCD_DOPLNKOVA;
	}
	// 2010-08-04: pridané odovzdanie parametra pre kalendár; 2011-11-30: pridaný do toho istého reťazca aj font
	// 2010-09-14: podmienka opravená; ak nie je kalendár určený resp. je všeobecný pre daný jazyk, nie je potrebné ho exportovať
	strcpy(export_dalsie_parametre, STR_EMPTY);
	// 2011-03-18: použité z iných miest aj v execute_batch_command() -- exportovanie parametra k (_global_kalendar)
	if (PODMIENKA_EXPORTOVAT_KALENDAR) {
		sprintf(pom, " -k%s", skratka_kalendara[_global_kalendar]);
	}
	else {
		Log("\tNetreba prilepiť kalendár (jazyk == %s, kalendár == %s)\n", skratka_jazyka[_global_jazyk], skratka_kalendara[_global_kalendar]);
		strcpy(pom, STR_EMPTY);
	}
	strcat(export_dalsie_parametre, pom);
	Log("Exportujem kalendár: export_dalsie_parametre == `%s'\n", export_dalsie_parametre);

	// 2011-11-30, 2021-03-05: exportovanie parametra F (_global_font)
	if (PODMIENKA_EXPORTOVAT_CUSTOM_FONT) {
		Log("\tPrilepujem custom font (font == %s)\n", pom_FONT);
		sprintf(pom, " -F%s", pom_FONT);
	}
	else if (PODMIENKA_EXPORTOVAT_STATIC_FONT) {
		Log("\tPrilepujem static font (font == %s)\n", nazov_fontu[_global_font]);
		sprintf(pom, " -F%s", nazov_fontu[_global_font]);
	}
	else {
		Log("\tNetreba prilepiť font...\n");
		strcpy(pom, STR_EMPTY);
	}
	strcat(export_dalsie_parametre, pom);
	Log("Exportujem font: export_dalsie_parametre == `%s'\n", export_dalsie_parametre);

	// 2011-11-30: exportovanie parametra S (_global_font_size)
	if (PODMIENKA_EXPORTOVAT_FONTSIZE) {
		sprintf(pom, " -S%s", nazov_font_size_css[_global_font_size]);
	}
	else {
		Log("\tNetreba prilepiť font size (font size == %s)\n", nazov_font_size_css[_global_font_size]);
		strcpy(pom, STR_EMPTY);
	}
	strcat(export_dalsie_parametre, pom);
	Log("Exportujem font size: export_dalsie_parametre == `%s'\n", export_dalsie_parametre);

	// 2015-01-08: exportovanie parametra G (_global_style_margin)
	if (PODMIENKA_EXPORTOVAT_STYLE_MARGIN) {
		sprintf(pom, " -G%d", _global_style_margin);
	}
	else {
		Log("\tNetreba prilepiť style margin (style margin == %d)\n", _global_style_margin);
		strcpy(pom, STR_EMPTY);
	}
	strcat(export_dalsie_parametre, pom);
	Log("Exportujem style margin: export_dalsie_parametre == `%s'\n", export_dalsie_parametre);

	// 2023-03-11: exportovanie parametra L (_global_line_height_perc)
	if (PODMIENKA_EXPORTOVAT_LINE_HEIGHT_PERC) {
		sprintf(pom, " -L%d", _global_line_height_perc);
	}
	else {
		Log("\tNetreba prilepiť line height (line height == %d)\n", _global_line_height_perc);
		strcpy(pom, STR_EMPTY);
	}
	strcat(export_dalsie_parametre, pom);
	Log("Exportujem line height: export_dalsie_parametre == `%s'\n", export_dalsie_parametre);

	// 2013-12-12: exportovanie parametra c (_global_css)
	if (PODMIENKA_EXPORTOVAT_CSS) {
		sprintf(pom, " -c%s", skratka_css[_global_css]); // nazov_css[_global_css]
	}
	else {
		Log("\tNetreba prilepiť css (css == %s/%s)\n", skratka_css[_global_css], nazov_css[_global_css]);
		strcpy(pom, STR_EMPTY);
	}
	strcat(export_dalsie_parametre, pom);
	Log("Exportujem css: export_dalsie_parametre == `%s'\n", export_dalsie_parametre);

	// 2009-08-03: exportovanie do adresárov po mesiacoch
	if (_global_opt_batch_monthly == ANO) {
		Log("_global_opt_batch_monthly == ANO\n");
		if (export_monthly_druh >= 2) {
			mystrcpy(_local_export_navig_hore, _global_export_navig_hore_day, SMALL);
		}
		else {
			mystrcpy(_local_export_navig_hore, _global_export_navig_hore, SMALL);
		}
		if (index_pre_mesiac_otvoreny == ANO) {
			Log("index_pre_mesiac_otvoreny == ANO\n");
			// najskôr do zoznamu mesiacov vyprintujeme odkaz na index.htm daného mesiaca (ak bolo prvého resp. začiatok exportu)...
			if ((_global_den.den == 1 && ((export_monthly_druh >= 1 && modlitba == MODL_INVITATORIUM) || export_monthly_druh != 1)) || export_month_zaciatok == ANO) {
				// sem sa už name_batch_month_file dostane s upraveným oddeľovačom STR_PATH_SEPARATOR_HTML; upravené v _main_batch_mode()
				if (_global_jazyk == JAZYK_HU) {
					fprintf(batch_html_file, "<li>" HTML_A_HREF_BEGIN "\"%s\">%d. %s" HTML_A_END "</li>\n", name_batch_month_file, _global_den.rok, nazov_mesiaca(_global_den.mesiac - 1));
				}
				else {
					fprintf(batch_html_file, "<li>" HTML_A_HREF_BEGIN "\"%s\">%s %d" HTML_A_END "</li>\n", name_batch_month_file, nazov_mesiaca(_global_den.mesiac - 1), _global_den.rok);
				}
				export_month_zaciatok = NIE;
			}
			// ... a presmerujeme výstup pre daný deň do index.htm daného mesiaca; potrebujeme si poslať názov, kam má pre jednotlivú modlitbu ukazovať ^ hore
			batch_export_file = batch_month_file;
		}// if (index_pre_mesiac_otvoreny == ANO)
		else {
			// 2009-08-05: netreba; pretože DEFAULT_MONTH_EXPORT sa zatiaľ nedá meniť
			batch_export_file = batch_html_file;
		}// else if (index_pre_mesiac_otvoreny == ANO)

		// 2009-08-12: doplnená premenná _global_export_navig_hore; pôvodne bolo: // mystrcpy(parameter_M, " -M", SMALL);
		// 2013-01-07: táto časť bola v predošlom "else"; nefungovalo to správne (napr. pri command-line príkaze: breviar.exe -qpbm -d1 -m1 -r2013 -f31 -g12 -p2013 -brobSK.bat -jsk -nbreviar.exe -i..\..\breviar.sk\include\ -usimple -M2 -00 -15184 -2224)
		Log("2:parameter_M...\n");
		sprintf(parameter_M, " -M%d", export_monthly_druh);
		Log("parameter_M == `%s'...\n", parameter_M);
		if (!(equals(_local_export_navig_hore, STR_EMPTY) || equals(_local_export_navig_hore, DEFAULT_MONTH_EXPORT))) {
			sprintf(parameter_I, " -I%s", _local_export_navig_hore);
			Log("parameter_I == `%s'...\n", parameter_I);
			strcat(parameter_M, parameter_I);
			Log("parameter_M == `%s'...\n", parameter_M);
		}
	}// if (_global_opt_batch_monthly == ANO)
	else {
		batch_export_file = batch_html_file;
		mystrcpy(parameter_M, STR_EMPTY, SMALL);
	}// else if (_global_opt_batch_monthly == ANO)

	// 2009-08-04: iný export
	if (export_monthly_druh >= 1 && modlitba != MODL_NEURCENA) {
		i = modlitba;
		Log("/* generujem len modlitbu i == %d `%s' (export_monthly_druh >= 1)...*/\n", i, nazov_modlitby(i));

		// 2013-07-29: generovanie názvu súboru s písmenkom modlitby (default) alebo s ID modlitby
		if (!isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_FNAME_MODL_ID)) {
			sprintf(export_fname_modl_str, "%c", char_modlitby[i]);
		}
		else {
			sprintf(export_fname_modl_str, "%d", i);
		}
		Log("export_fname_modl_str == %s...\n", export_fname_modl_str);

		Log("a == %d, i == %d, zobrazit_mcd == %d; nie_su_vespery == %d...\n", a, i, zobrazit_mcd, nie_su_vespery);

		// 2012-08-23: generovať modlitbu cez deň + kompletórium len ak nejde o ľubovoľnú spomienku (vtedy nemajú význam)
		if (!((zobrazit_mcd == ANO) || (a == 0)) && (je_modlitba_cez_den(i) || je_kompletorium12(i))) {
			Log("(generovať modlitbu cez deň + kompletórium len ak nejde o ľubovoľnú spomienku -- vtedy nemajú význam)\n");
		}
		else {
			Log("execute_batch_command(): else vetva, nasleduje rozhodovanie, či generovať modlitbu: ...\n");

			if ((_global_den.den == 1 || d_from_m_from_r_from == 1) && export_month_nova_modlitba == 1 && export_monthly_druh == 1) {
				// pre prvého (resp. prvého v prvom mesiaci, ktorý nezačal prvého) musím vypísať aj názov modlitby
				fprintf(batch_export_file, "\n" HTML_P_BEGIN "<b>%s</b>" HTML_LINE_BREAK, nazov_modlitby(i));
				export_month_nova_modlitba = 0;
			}

			// 2011-03-23: upravené: negenerovať vešpery pre soboty, ak je nastavené isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY)
			// 2012-08-27: vešpery a kompletórium nemá zmysel zobrazovať, ak ide o sobotu a ďalšieho svätého (pri viacerých ľubovoľných spomienkach)
			// 2013-06-27: pridané zátvorky okolo prvej podmienky, aby && v druhom riadku viazalo sa na obe "||" možnosti s "a"-čkom | breviar.cpp:9804: warning: suggest parentheses around '&&' within '||'
			// 2013-09-30: namiesto prostej podmienky B:(zobrazit_mcd == ANO) použitá podmienená implikácia A => B (A:modlitba cez deň) vo forme (non A) OR B
			// 2018-02-26: fix for generating prayers except vespers & compline for option BIT_OPT_2_BUTTON_PRVE_VESPERY
			if (((a != PORADIE_PM_SOBOTA) || (a == PORADIE_PM_SOBOTA && (i != MODL_VESPERY && i != MODL_KOMPLETORIUM)))
				&& ((i != MODL_VESPERY && i != MODL_KOMPLETORIUM) || !((isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY)) && (nie_su_vespery) && !(PODMIENKA_SVIATKY_PANA_SVATYCH_PREDNOST_PRED_NEDELOU_OCR)))
				&& (
				(/*non A*/ !(je_modlitba_cez_den(i)) || /*B*/(zobrazit_mcd == ANO))
					|| (_global_den.denvt != DEN_SOBOTA)
					|| (a == 0)
					)
				) {
				if (((_global_opt_1_casti_modlitby_orig & BIT_OPT_1_MCD_DOPLNKOVA) == BIT_OPT_1_MCD_DOPLNKOVA) && (je_modlitba_cez_den(i))) {
					if (_global_opt_append == YES) {
						sprintf(export_fname_pattern, "%s", batch_command);
					}
					else {
						sprintf(export_fname_pattern, "%s%d%sd.htm", batch_command, a, export_fname_modl_str /* char_modlitby[i] */);
					}
					Log("1:parameter_M == `%s'...\n", parameter_M);
					fprintf(batch_file, "%s -0%llu -1%llu -2%llu -3%llu -4%llu -5%llu -x%d -p%s -j%s%s%s\n", export_fname_pattern,
						_global_opt[OPT_0_SPECIALNE], _global_opt_1_casti_modlitby_orig /* _global_opt[OPT_1_CASTI_MODLITBY] */, _global_opt[OPT_2_HTML_EXPORT], _global_opt[OPT_3_SPOLOCNA_CAST], _global_opt[OPT_4_OFFLINE_EXPORT], _global_opt[OPT_5_ALTERNATIVES],
						a, str_modlitby[i], skratka_jazyka[_global_jazyk], parameter_M, export_dalsie_parametre); // modlitba `i'
					if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
						sprintf(export_doplnkova_psalmodia, " (" HTML_A_HREF_BEGIN "\"" FILENAME_EXPORT_DATE_SIMPLE "_%d%sd.htm\">alt" HTML_A_END ")", _global_den.rok % 100, _global_den.mesiac, _global_den.den, a, export_fname_modl_str /*char_modlitby[i] */);
					}
					else {
						// EXPORT_DATE_FULL
						sprintf(export_doplnkova_psalmodia, " (" HTML_A_HREF_BEGIN "\"" FILENAME_EXPORT_DATE_FULL "_%d%sd.htm\">alt" HTML_A_END ")", _global_den.rok, _global_den.mesiac, _global_den.den, a, export_fname_modl_str /* char_modlitby[i] */);
					}
				}
				else {
					strcpy(export_doplnkova_psalmodia, STR_EMPTY);
				}
				if (_global_opt_append == YES) {
					sprintf(export_fname_pattern, "%s", batch_command);
				}
				else {
					sprintf(export_fname_pattern, "%s%d%s.htm", batch_command, a, export_fname_modl_str /* char_modlitby[i] */);
				}
				Log("2:parameter_M == `%s'...\n", parameter_M);
				fprintf(batch_file, "%s -0%llu -1%llu -2%llu -3%llu -4%llu -5%llu -x%d -p%s -j%s%s%s\n", export_fname_pattern,
					_global_opt[OPT_0_SPECIALNE], _global_opt[OPT_1_CASTI_MODLITBY], _global_opt[OPT_2_HTML_EXPORT], _global_opt[OPT_3_SPOLOCNA_CAST], _global_opt[OPT_4_OFFLINE_EXPORT], _global_opt[OPT_5_ALTERNATIVES],
					a, str_modlitby[i], skratka_jazyka[_global_jazyk], parameter_M, export_dalsie_parametre); // modlitba `i'
				if (export_monthly_druh == 1) {
					Log("mY: export_monthly_druh == 1...\n");
					if (a > 0) {
						sprintf(poradie_svateho, "/%d", a);
					}
					else {
						mystrcpy(poradie_svateho, STR_EMPTY, SMALL);
					}
					if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
						fprintf(batch_export_file, HTML_A_HREF_BEGIN "\"" FILENAME_EXPORT_DATE_SIMPLE "_%d%s.htm\">%d%s" HTML_A_END "%s | ", _global_den.rok % 100, _global_den.mesiac, _global_den.den, a, export_fname_modl_str /* char_modlitby[i] */, _global_den.den, /* char */ poradie_svateho, export_doplnkova_psalmodia);
					}
					else {
						// EXPORT_DATE_FULL
						fprintf(batch_export_file, HTML_A_HREF_BEGIN "\"" FILENAME_EXPORT_DATE_FULL "_%d%s.htm\">%d%s" HTML_A_END "%s | ", _global_den.rok, _global_den.mesiac, _global_den.den, a, export_fname_modl_str /* char_modlitby[i] */, _global_den.den, /* char */ poradie_svateho, export_doplnkova_psalmodia);
					}
				}// if (export_monthly_druh == 1)
			}
			else {
				Log("nič sa nedeje.\n");
			}
		}// generovať modlitbu
	}
	else {
		Log("mY: modlitba určená...\n");
		Log("execute_batch_command(): pre všetky modlitby...\n");
		fprintf(batch_export_file, "<li>%d. %s %d: \n", _global_den.den, nazov_mesiaca(_global_den.mesiac - 1), _global_den.rok);
		for (i = MODL_INVITATORIUM; i < MODL_NEURCENA; i++) {

			// 2013-07-29: generovanie názvu súboru s písmenkom modlitby (default) alebo s ID modlitby
			if (!isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_FNAME_MODL_ID)) {
				sprintf(export_fname_modl_str, "%c", char_modlitby[i]);
			}
			else {
				sprintf(export_fname_modl_str, "%d", i);
			}

			// 2012-08-23: generovať modlitbu cez deň + kompletórium len ak nejde o ľubovoľnú spomienku (vtedy nemajú význam)
			if (!((zobrazit_mcd == ANO) || (a == 0)) && (je_modlitba_cez_den(i) || je_kompletorium12(i))) {
				continue;
			}

			Log("/* generujem: %d `%s'... */\n", i, nazov_modlitby(i));

			// 2011-03-23: upravené: negenerovať vešpery pre soboty, ak je nastavené isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY)
			// 2012-08-27: vešpery a kompletórium nemá zmysel zobrazovať, ak ide o sobotu a ďalšieho svätého (pri viacerých ľubovoľných spomienkach)
			// 2013-04-05: zavedené "nie_su_vespery" kvôli Bielej (veľkej) sobote
			// 2013-09-30: namiesto prostej podmienky B:(zobrazit_mcd == ANO) použitá podmienená implikácia A => B (A:modlitba cez deň) vo forme (non A) OR B
			// 2018-02-26: fix for generating prayers except vespers & compline for option BIT_OPT_2_BUTTON_PRVE_VESPERY
			if (((a != PORADIE_PM_SOBOTA) || (a == PORADIE_PM_SOBOTA && (i != MODL_VESPERY && i != MODL_KOMPLETORIUM)))
				&& ((i != MODL_VESPERY && i != MODL_KOMPLETORIUM) || !((isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY)) && (nie_su_vespery) && !(PODMIENKA_SVIATKY_PANA_SVATYCH_PREDNOST_PRED_NEDELOU_OCR)))
				&& (
				(/*non A*/ !(je_modlitba_cez_den(i)) || /*B*/(zobrazit_mcd == ANO))
					|| (_global_den.denvt != DEN_SOBOTA)
					|| (a == 0)
					)
				) {
				if (_global_opt_append == YES) {
					fprintf(batch_file, "%s -0%llu -1%llu -2%llu -3%llu -4%llu -5%llu -x%d -p%s -j%s%s\n", batch_command,
						_global_opt[OPT_0_SPECIALNE], _global_opt[OPT_1_CASTI_MODLITBY], _global_opt[OPT_2_HTML_EXPORT], _global_opt[OPT_3_SPOLOCNA_CAST], _global_opt[OPT_4_OFFLINE_EXPORT], _global_opt[OPT_5_ALTERNATIVES],
						a, str_modlitby[i], skratka_jazyka[_global_jazyk], export_dalsie_parametre); // modlitba `i'
				}// endif _global_opt_append == YES
				else {
					if (((_global_opt_1_casti_modlitby_orig & BIT_OPT_1_MCD_DOPLNKOVA) == BIT_OPT_1_MCD_DOPLNKOVA) && (je_modlitba_cez_den(i))) {
						Log("3:parameter_M == `%s'...\n", parameter_M);
						fprintf(batch_file, "%s%d%sd.htm -0%llu -1%llu -2%llu -3%llu -4%llu -5%llu -x%d -p%s -j%s%s%s\n", batch_command, a, export_fname_modl_str /* char_modlitby[i] */,
							_global_opt[OPT_0_SPECIALNE], _global_opt_1_casti_modlitby_orig /* _global_opt[OPT_1_CASTI_MODLITBY] */, _global_opt[OPT_2_HTML_EXPORT], _global_opt[OPT_3_SPOLOCNA_CAST], _global_opt[OPT_4_OFFLINE_EXPORT], _global_opt[OPT_5_ALTERNATIVES],
							a, str_modlitby[i], skratka_jazyka[_global_jazyk], parameter_M, export_dalsie_parametre); // modlitba `i'
						if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
							sprintf(export_doplnkova_psalmodia, " (" HTML_A_HREF_BEGIN "\"" FILENAME_EXPORT_DATE_SIMPLE "_%d%sd.htm\">alt" HTML_A_END ")", _global_den.rok % 100, _global_den.mesiac, _global_den.den, a, export_fname_modl_str /* char_modlitby[i] */);
						}
						else { // EXPORT_DATE_FULL
							sprintf(export_doplnkova_psalmodia, " (" HTML_A_HREF_BEGIN "\"" FILENAME_EXPORT_DATE_FULL "_%d%sd.htm\">alt" HTML_A_END ")", _global_den.rok, _global_den.mesiac, _global_den.den, a, export_fname_modl_str /* char_modlitby[i] */);
						}
					}
					else {
						strcpy(export_doplnkova_psalmodia, STR_EMPTY);
					}
					// 2009-08-03: doplnená možnosť exportovať parameter -M ak exportuje batch mód pre jednotlivé mesiace kvôli hlavičke jednotlivej modlitby
					Log("4:parameter_M == `%s'...\n", parameter_M);
					fprintf(batch_file, "%s%d%s.htm -0%llu -1%llu -2%llu -3%llu -4%llu -5%llu -x%d -p%s -j%s%s%s\n", batch_command, a, export_fname_modl_str /* char_modlitby[i] */,
						_global_opt[OPT_0_SPECIALNE], _global_opt[OPT_1_CASTI_MODLITBY], _global_opt[OPT_2_HTML_EXPORT], _global_opt[OPT_3_SPOLOCNA_CAST], _global_opt[OPT_4_OFFLINE_EXPORT], _global_opt[OPT_5_ALTERNATIVES],
						a, str_modlitby[i], skratka_jazyka[_global_jazyk], parameter_M, export_dalsie_parametre); // modlitba `i'
					// 2008-11-29: rozličný export
					if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
						fprintf(batch_export_file, "\t" HTML_A_HREF_BEGIN "\"" FILENAME_EXPORT_DATE_SIMPLE "_%d%s.htm\">%s" HTML_A_END "%s, \n", _global_den.rok % 100, _global_den.mesiac, _global_den.den, a, export_fname_modl_str /* char_modlitby[i] */, nazov_modlitby(i), export_doplnkova_psalmodia);
					}
					else { // EXPORT_DATE_FULL
						fprintf(batch_export_file, "\t" HTML_A_HREF_BEGIN "\"" FILENAME_EXPORT_DATE_FULL "_%d%s.htm\">%s" HTML_A_END "%s, \n", _global_den.rok, _global_den.mesiac, _global_den.den, a, export_fname_modl_str /* char_modlitby[i] */, nazov_modlitby(i), export_doplnkova_psalmodia);
					}
				}
			}
		}
		fprintf(batch_export_file, "</li>\n");
	}// else if (export_monthly_druh >= 1)

	// napokon o1 vrátime späť
	_global_opt[OPT_1_CASTI_MODLITBY] = _global_opt_1_casti_modlitby_orig; // restore pôvodnej hodnoty

	Log("execute_batch_command(): koniec.\n");
} // execute_batch_command()

// exportuje udaje, ktore nacitala _rozbor_dna()

// zoznam[0] značí počet; zoznam[1] = _global_den; zoznam[2] až [MAX_POCET_SVATY+1] = _global_svaty(1)..._global_svaty(MAX_POCET_SVATY); zoznam[POCET_ZOZNAM-1] = _global_pm_sobota
#define POCET_ZOZNAM (MAX_POCET_SVATY + 3)
#define PORADIE_SVATY_NULL -1
short int zoznam[POCET_ZOZNAM]; 
// prvá hodnota, t. j. zoznam[0], určuje počet; ak je číslo > 10, znamená to, že ide o * 10 kvôli informácii o tom, že sa neexportuje modlitba cez deň a kompletórium pre ľubovoľné spomienky
// od druhej hodnoty reprezentuje: _global_den, _global_svaty(1)..._global_svaty(MAX_POCET_SVATY), _global_pm_sobota

void init_zoznam(void) {
	zoznam[0] = 0;
	for (int i = 1; i < POCET_ZOZNAM; i++) {
		zoznam[i] = PORADIE_SVATY_NULL;
	}
} // init_zoznam()

void Log_zoznam(void) {
	for (int i = 0; i < POCET_ZOZNAM; i++) {
		Log("zoznam[%d] == %d\n", i, zoznam[i]);
		// Export("zoznam[%d] == %d" HTML_LINE_BREAK, i, zoznam[i]);
	}
} // Log_zoznam()

#define LOG_ZOZNAM /* zoznam[0] = pocet; */ Log_zoznam();

void _export_rozbor_dna_zoznam(short int typ) {
	short int pocet = 1; // počet záznamov, ktoré sa exportujú (či už riadky tabuľky alebo len zoznam)
	short int poradie_svaty = PORADIE_SVATY_NULL, poradie_svaty_vedie = PORADIE_SVATY_NULL;
	short int aj_feria = NIE;

	Log("_export_rozbor_dna_zoznam(): začiatok...\n");
#ifdef OS_Windows_Ruby
	if (typ != EXPORT_DNA_XML) {
		ExportHtmlComment("_export_rozbor_dna_zoznam:begin");
	}
#endif

	init_zoznam();

	short int podmienka_svaty_vedie = NIE;
	short int podmienka_svaty_vedie_pom = NIE;
	short int smer_override = 14; // undefined
	Log("_global_den.smer == %d...\n", _global_den.smer);

	for (short int i = 0; i < MAX_POCET_SVATY; i++) {

		smer_override = _global_svaty_i_smer_override(i + 1);
		Log("_global_svaty(%d).smer == %d...\n", i + 1, _global_svaty(i + 1).smer);
		Log("_global_svaty(%d).smer override == %d...\n", i + 1, smer_override);

		if ((_global_den.smer > smer_override) && !MIESTNE_SLAVENIE_LOKAL_SVATY(i + 1)) {
			podmienka_svaty_vedie = ANO;
			poradie_svaty_vedie = i + 1; // vyberie posledný!!!
		}
		if (_global_den.smer > smer_override) {
			podmienka_svaty_vedie_pom = ANO;
			poradie_svaty_vedie = i + 1; // vyberie posledný!!!
		}
	}
	Log("podmienka_svaty_vedie == %d\n", podmienka_svaty_vedie);
	Log("podmienka_svaty_vedie_pom == %d\n", podmienka_svaty_vedie_pom);
	Log("poradie_svaty_vedie == %d\n", poradie_svaty_vedie);

	Log("počet == %d\n", pocet);
	// pozor, hoci je nedela, predsa na nu mohlo pripadnut slavenie s vyssou prioritou
	if ((_global_den.denvt == DEN_NEDELA) ||
		(_global_den.prik == PRIKAZANY_SVIATOK) ||
		(_global_den.smer < 5)) {

		Log("nedele a prikázané sviatky...\n");
		// nedele a prikazane sviatky - cervenou, velkymi pismenami
		// slavnosti - velkymi pismenami

		// 23/02/2000A.D. -- teraz este testujeme, ci nema nahodou pred nedelou (trebars v obdobi cez rok, smer == 6) prednost napr. sviatok Pana (smer == 5); dalsia cast je skopirovana podla casti v _rozbor_dna, v poznamke SVATY_VEDIE
		// ... alebo c. 60: "ak na jeden den pripadnu viacere slavenia, uprednostni sa to, ktore ma v tabulke liturgickych dni vyssi stupen [t.j. .smer].

		// 2006-12-07: slávnosti svätých (k fixným dátumom: napr. 8.12., 29.6., 5.7., 15.8.), ktoré nepripadnú na nedeľu, neboli správne zobrazované
		// 2010-07-28: doplnené alternatívne porovnanie aj s _global_svaty(2).smer (kvôli dominikánskej slávnosti 8.8.)
		// 2010-10-06: upravené; nesmie ísť o lokálnu slávnosť (smer == 4) lebo nemá prebíjať "globálnu" v danom kalendári [napr. czop pre 22.10.]
		// 2011-02-02: zadefinované MIESTNE_SLAVENIE_CZOP_SVATY(i), aby sa zjednodušila podmienka (platí len pre CZOP)
		// 2011-03-07: MIESTNE_SLAVENIE_CZOP_SVATY(i) použité aj pre iné lokálne slávenia ako MIESTNE_SLAVENIE_LOKAL_SVATY(i)
		if (podmienka_svaty_vedie == ANO) {
			Log("podmienka_svaty_vedie == ANO...\n");
			poradie_svaty = poradie_svaty_vedie;
			zoznam[pocet] = poradie_svaty;
			LOG_ZOZNAM;
		}
		else {
			Log("podmienka_svaty_vedie == NIE...\n");
			poradie_svaty = 0;
			zoznam[pocet] = poradie_svaty;
			LOG_ZOZNAM;
			// 2010-10-06: upravené; v tejto vetve rozhodovania treba riešiť to, že je splnená základná podmienka (nedeľa alebo prikázaný sviatok alebo smer < 5),
			//             avšak nebola splnená vyššie uvedená novo-upravená podmienka o "prebití" nedele napr. lokálnou slávnosťou
			if (podmienka_svaty_vedie_pom == ANO) {
				Log("podmienka_svaty_vedie_pom == ANO...\n");
				pocet = 2; // možno by bolo lepšie, keby tu bolo: pocet++;
				poradie_svaty = poradie_svaty_vedie;
				zoznam[pocet] = poradie_svaty;
				LOG_ZOZNAM;
			}
		}
	}// if ((_global_den.denvt == DEN_NEDELA) || (_global_den.prik == PRIKAZANY_SVIATOK) || (_global_den.smer < 5))
	else if (_global_pocet_svatych > 0) {
		Log("NIE nedele a prikázané sviatky; _global_pocet_svatych (%d) > 0...\n", _global_pocet_svatych);
		// sviatky (spomienky, ls) svatych
		// 2010-07-28: doplnené alternatívne porovnanie aj s _global_svaty(2).smer (kvôli dominikánskej slávnosti 8.8.)
		// 2014-03-22: v skutočnosti môže byť podmienka_svaty_vedie_pom == ANO, a pritom podmienka_svaty_vedie == NIE
		if ((podmienka_svaty_vedie_pom == ANO) ||
			((_global_den.smer == 9) && (_global_svaty(1).smer == 12))) {
			Log("svätý má prednosť...\n");
			// svaty
			// 2009-01-05: Vlado K. ma upozornil, že ak je smer svätý == 12, ale deň je 9 (bod 59. smerníc o LH a kalendári, č. 12), bolo by lepšie ponúknuť najprv deň a až potom ostatné slávenia 
			// 2010-05-21: Rastislav Hamráček SDB <rastohamracek@sdb.sk> upozornil defacto na to isté ako Vlado: aby to bolo podľa direktória
			// ----------------------------------------------------------------------------
			// 2005-08-22: pôvodne sa tu porovnávalo s 12, ale aj pre 11 (lokálne slávenia) by mal systém ponúknuť všedný deň - keď je to napr. v inej diecéze
			// 2009-11-26: porovnávame klasicky, resp. špeciálne pre body 4, 8, 11 [Miestne slávnosti, Miestne sviatky, Miestne povinné spomienky] pred touto úpravou tu bolo: if ((_global_svaty(1).smer >= 11) && atď.
			// 2010-05-21: sem presunuté potenciálne vypisovanie (export) všedného dňa pred prvého svätca, ak je ľubovoľná spomienka teraz vlastne obe vetvy vyzerajú rovnako, asi to zjednotím časom...
			// 2010-05-24: zjednotené; bolo odvetvené "if (_global_den.smer > _global_svaty(1).smer)"; 
			//             else vetva mala napísané: "ľubovoľná spomienka svätého/svätých, pričom všedný deň má vyššiu prioritu slávenia"
			//             a ešte: "2010-05-21: odtiaľto presunuté potenciálne vypisovanie (export) všedného dňa pred prvého svätca, ak je ľubovoľná spomienka"
			// 2011-02-02: zadefinované MIESTNE_SLAVENIE_CZOP_SVATY(i), aby sa zjednodušila podmienka (platí len pre CZOP)
			// 2011-03-07: MIESTNE_SLAVENIE_CZOP_SVATY(i) použité aj pre iné lokálne slávenia ako MIESTNE_SLAVENIE_LOKAL_SVATY(i)
			// 2012-08-21: cdoplnená premenná (kvôli tomu, či sa majú pre svätca 1 zobraziť buttons modlitba cez deň)
			aj_feria = NIE;
			if (((_global_svaty(1).smer >= 12) || MIESTNE_SLAVENIE_LOKAL_SVATY(1)) && (typ != EXPORT_DNA_VIAC_DNI)) {
				Log("nastavujem: aj féria...\n");
				// ak je to iba lubovolna spomienka, tak vsedny den
				aj_feria = ANO;
			}
			if (aj_feria == ANO) {
				Log("spracúvam, keďže je aj féria (pocet == %d)...\n", pocet);
				// ak je to iba lubovolna spomienka, tak vsedny den
				poradie_svaty = 0;
				zoznam[pocet] = poradie_svaty;
				pocet++;
				LOG_ZOZNAM;
			}
			// 2010-05-21: pôvodne bolo: "sviatok, spomienka alebo ľubovoľná spomienka svätého/svätých, ide prv ako všedný deň"; dnes ide prv len ak je to sviatok alebo spomienka 
			// (a vlastne vtedy sa všedný deň vypisuje len pre lokálne sviatky resp. spomienky) 
			for (short int i = 0; i < MAX_POCET_SVATY; i++) {
				Log("i == %d; pocet == %d...\n", i, pocet);
				if (_global_pocet_svatych > i) {
					Log("_global_pocet_svatych (%d) > i (%d)...\n", _global_pocet_svatych, i);
					poradie_svaty = i + 1;
					Log("poradie_svaty == %d...\n", poradie_svaty);
					if (poradie_svaty == 1) {
						// podmienka pre 1. svätého je iná ako pre 2. a ďalšieho
						if ((aj_feria) && (!MIESTNE_SLAVENIE_LOKAL_SVATY(poradie_svaty)) && (!_je_global_svaty_i_sviatok_alebo_slavnost(poradie_svaty))) {
							poradie_svaty *= 10;
						}
					}
					else {
						if ((!MIESTNE_SLAVENIE_LOKAL_SVATY(poradie_svaty)) && (!_je_global_svaty_i_sviatok_alebo_slavnost(poradie_svaty))) {
							poradie_svaty *= 10;
						}
					}
					if ((poradie_svaty != 1) && (poradie_svaty != 10)) {
						pocet++;
					}
					zoznam[pocet] = poradie_svaty;
					LOG_ZOZNAM;
				}
			}
		}// svaty ma prednost
		else {
			Log("prednosť má deň...\n");
			// prednost ma den
			poradie_svaty = 0;
			zoznam[pocet] = poradie_svaty;
			LOG_ZOZNAM;
		}// prednost ma den
	}// if (_global_pocet_svatych > 0)
	else {
		Log("NIE nedele a prikázané sviatky; obyčajný deň | _global_pocet_svatych (%d) == 0...\n", _global_pocet_svatych);
		// obycajne dni, nie sviatok
		poradie_svaty = 0;
		zoznam[pocet] = poradie_svaty;
		LOG_ZOZNAM;
	}// if (equals(_global_den.meno, STR_EMPTY))

	Log("počet == %d (pred kontrolou PM v sobotu; POCET_ZOZNAM == %d)\n", pocet, POCET_ZOZNAM);

	// Log("PM v sobotu: _global_den.smer == %d, _global_pocet_svatych == %d, _global_svaty(1).smer == %d, _global_svaty(1).spolcast == %d, \n", _global_den.smer, _global_pocet_svatych, _global_svaty(1).smer, _global_svaty(1).spolcast);

	// este spomienka panny marie v sobotu, cl. 15 (nemôže byť ani vtedy, ak je iná ľubovoľná spomienka PM; napr. 16JUL, 12SEP)
	if ((PODMIENKA_MOZE_BYT_SPOMIENKA_PM_V_SOBOTU) && (typ != EXPORT_DNA_VIAC_DNI)) {
		Log("je aj spomienka PM v sobotu...\n");

		poradie_svaty = PORADIE_PM_SOBOTA;
		poradie_svaty *= 10;
		pocet++;
		zoznam[pocet] = poradie_svaty;
		LOG_ZOZNAM;
	}
	zoznam[0] = pocet;
	Log("počet == %d\n", pocet);

#ifdef OS_Windows_Ruby
	if (typ != EXPORT_DNA_XML) {
		ExportHtmlComment("_export_rozbor_dna_zoznam:end");
	}
#endif
	Log("_export_rozbor_dna_zoznam(): koniec.\n");
	LOG_ZOZNAM;
} // _export_rozbor_dna_zoznam()

void _export_rozbor_dna_interpretuj_zoznam(short int export_typ, short int typ, short int som_v_tabulke, char batch_command[MAX_STR], short int modlitba, short int d_from_m_from_r_from) {
	short int poradie_svaty;
	short int zobrazit_mcd = ANO;
	short int pocet = zoznam[0];
	unsigned long long _global_opt_orig; // pre o4

	Log("_export_rozbor_dna_interpretuj_zoznam(): začiatok (pocet == %d)...\n", pocet);
#ifdef OS_Windows_Ruby
	if (typ != EXPORT_DNA_XML) {
		ExportHtmlComment("_export_rozbor_dna_interpretuj_zoznam:begin");
	}
#endif

	if (pocet > POCET_ZOZNAM - 1) {
		pocet = POCET_ZOZNAM - 1;
	}
	for (int i = 1; i <= pocet; i++) {
		poradie_svaty = zoznam[i];
		zobrazit_mcd = ANO;

		Log("_export_rozbor_dna_interpretuj_zoznam(): i == %d, poradie_svaty == zoznam[i] == %d...\n", i, poradie_svaty);

		if (poradie_svaty <= PORADIE_SVATY_NULL) {
			continue;
		}

		if (poradie_svaty >= 10) {
			poradie_svaty /= 10;
			zobrazit_mcd = NIE;
		}

		Log("_export_rozbor_dna_interpretuj_zoznam(): option %d = %ld\n", OPT_4_OFFLINE_EXPORT, _global_opt[OPT_4_OFFLINE_EXPORT]);

		// úprava o4 pre indikovanie, že sa nemajú exportovať buttony pre niektoré modlitby
		_global_opt_orig = _global_opt[OPT_4_OFFLINE_EXPORT]; // backup pôvodnej hodnoty

		// this should not be applied in some cases (o4 value remains set up even if it should not be changed) -- "else" added experimentally
		if (!((zobrazit_mcd == ANO) || (poradie_svaty == 0))) {
			// nastavenie parametra o4: pridáme BIT_OPT_4_EXCLUDE_MCD_KOMPLET pre indikovanie, že sa nemajú exportovať buttony pre niektoré modlitby
			if (!isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_EXCLUDE_MCD_KOMPLET)) {
				Log("Pre option %d nastavujem bit pre '%d'\n", OPT_4_OFFLINE_EXPORT, BIT_OPT_4_EXCLUDE_MCD_KOMPLET);
				_global_opt[OPT_4_OFFLINE_EXPORT] += BIT_OPT_4_EXCLUDE_MCD_KOMPLET;
				Log("option %d = %ld\n", OPT_4_OFFLINE_EXPORT, _global_opt[OPT_4_OFFLINE_EXPORT]);
			}// zmena: indikovanie, že sa nemajú exportovať buttony pre niektoré modlitby
		}
		else {
			if (isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_EXCLUDE_MCD_KOMPLET)) {
				Log("Pre option %d ODnastavujem bit pre '%d'\n", OPT_4_OFFLINE_EXPORT, BIT_OPT_4_EXCLUDE_MCD_KOMPLET);
				_global_opt[OPT_4_OFFLINE_EXPORT] -= BIT_OPT_4_EXCLUDE_MCD_KOMPLET;
				Log("option %d = %ld\n", OPT_4_OFFLINE_EXPORT, _global_opt[OPT_4_OFFLINE_EXPORT]);
			}
		}

		if (export_typ == EXPORT_TYP_BATCH_MODE) {
			execute_batch_command(poradie_svaty, batch_command, zobrazit_mcd, modlitba, d_from_m_from_r_from);
		}
		else if (export_typ == EXPORT_TYP_WEB_MODE) {
			if ((i > 1) && (typ != EXPORT_DNA_XML)) {
				if (typ == EXPORT_DNA_VIAC_DNI_SIMPLE) {
					Export("; ");
				}
				else if (som_v_tabulke == NIE) {
					if (typ == EXPORT_DNA_VIAC_DNI) {
						Export("\n" HTML_LINE_BREAK "" HTML_NONBREAKING_SPACE_LONG "%s:\n", html_text_alebo[_global_jazyk]);
					}
					else {
						if (typ != EXPORT_DNA_VIAC_DNI_TXT) {
							Export(HTML_P_END);
							Export("\n\n");
							Export(HTML_P_BEGIN);
						}
					}
				}
				else {
					Export(HTML_TABLE_CELL_END "\n");
					Export(HTML_TABLE_ROW_END "\n");

					if (((typ == EXPORT_DNA_DNES) || (typ == EXPORT_DNA_JEDEN_DEN) || (typ == EXPORT_DNA_JEDEN_DEN_LOCAL)) && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTONY_USPORNE))) {
						ExportHtmlComment("table-end-2");

						Export(HTML_TABLE_END "\n");
						Export("<" HTML_TABLE ">\n");
					}

					ExportHtmlComment("row-iz");

					Export("<" HTML_TABLE_ROW ">\n");

					ExportTableCell(HTML_TABLE_CELL);
					Export(HTML_TABLE_CELL_END "\n");

					ExportTableCell(HTML_TABLE_CELL);
				}
			}
#ifdef OS_Windows_Ruby
			if (typ != EXPORT_DNA_XML) {
				ExportHtmlComment("_export_rozbor_dna_interpretuj_zoznam:_export_rozbor_dna_buttons");
			}
#endif
			_export_rozbor_dna_buttons(typ, poradie_svaty, ANO, zobrazit_mcd);
		}
		else {
			// unsupported export type
		}

		_global_opt[OPT_4_OFFLINE_EXPORT] = _global_opt_orig; // restore pôvodnej hodnoty
	}

#ifdef OS_Windows_Ruby
	if (typ != EXPORT_DNA_XML) {
		ExportHtmlComment("_export_rozbor_dna_interpretuj_zoznam:end");
	}
#endif
	Log("_export_rozbor_dna_interpretuj_zoznam(): koniec.\n");
} // _export_rozbor_dna_interpretuj_zoznam()

void _exportXmlDay() {
	Export(ELEM_BEGIN(XML_DATE_ISO) "" HTML_ISO_FORMAT "" ELEM_END(XML_DATE_ISO) "\n", _global_den.rok, _global_den.mesiac, _global_den.den);
	Export(ELEM_BEGIN(XML_DATE_DAY) "%d" ELEM_END(XML_DATE_DAY) "\n", _global_den.den);
	Export(ELEM_BEGIN(XML_DATE_MONTH) "%d" ELEM_END(XML_DATE_MONTH) "\n", _global_den.mesiac);
	Export(ELEM_BEGIN(XML_DATE_YEAR) "%d" ELEM_END(XML_DATE_YEAR) "\n", _global_den.rok);
	Export(ELEM_BEGIN(XML_DAY_OF_YEAR) "%d" ELEM_END(XML_DAY_OF_YEAR) "\n", _global_den.denvr);
	Export(ELEM_BEGIN_ID(XML_DAY_OF_WEEK) "%s" ELEM_END(XML_DAY_OF_WEEK) "\n", _global_den.denvt, nazov_dna(_global_den.denvt));
	// _export_rozbor_dna_interpretuj_zoznam() produces XML_CELEBRATION structures
} // _exportXmlDay()

void _exportXmlDay2() {
	// _global_string2 initialized in init_global_string(); called from _export_rozbor_dna_buttons(); _rozbor_dna_s_modlitbou() and _main_liturgicke_obdobie() -- this method _exportXmlDay2() must be called after that initialization
	Export(ELEM_BEGIN(XML_STRING_VOLUME) "%s" ELEM_END(XML_STRING_VOLUME) "\n", _global_string2);
}// _exportXmlDay2()

void _export_rozbor_dna(short int typ) {
	// treba brat do uvahy:
	// 1. ked ma sviatok prioritu, tak ide on (ulozeny v _global_den, ak pocet_svatych == 0; resp. v _global_svaty(1), ak pocet_svatych > 0;)
	// 2. ked su lubovolne spomienky, su ulozene v premennych
	//    _global_svaty(i), i > 0
	//    naviac treba napisat _global_den (ako vsedny den)
	// 3. ak ide o sobotu v OBD_CEZ_ROK, treba ponuknut moznost _global_pm_sobota (spomienka panny marie v sobotu)
	short int i;
	char pom1[SMALL] = STR_EMPTY;
	char pom2[SMALL] = STR_EMPTY;
	char pom3[SMALL] = STR_EMPTY;
	short int som_v_tabulke = ANO; // či sa používa tabuľka; bežne pre web áno, pre export pre mobilné zariadenia [export_monthly_druh >= 3] netreba tabuľku

	Log("-- _export_rozbor_dna(typ == %d): začiatok...\n", typ);

	if (!(isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_BUTTONS_ORDER))) {
		if ((typ != EXPORT_DNA_VIAC_DNI) && (typ != EXPORT_DNA_VIAC_DNI_TXT) && (typ != EXPORT_DNA_XML)) {
			_export_rozbor_dna_buttons_dni(typ);
			Export(HTML_P_END "" HTML_DIV_END "\n\n<div class=\"daily\">");
			Export(HTML_P_BEGIN"\n");
		}
	}

	if (PODMIENKA_JE_BATCH_MODE_MONTHLY__AND__PLAIN_EXPORT) {
		som_v_tabulke = NIE;
		Log("-- _export_rozbor_dna(typ == %d): keďže sme v _global_opt_batch_monthly == ANO a export_monthly_druh (%d) > 2, nebudeme exportovať tabuľku...\n", typ, export_monthly_druh);
	}
	if ((typ == EXPORT_DNA_VIAC_DNI_TXT) || (typ == EXPORT_DNA_XML)) {
		som_v_tabulke = NIE;
		Log("-- _export_rozbor_dna_buttons(typ == %d): kvôli typu nebudeme exportovať tabuľku...\n", typ);
	}

	// XML export -- začiatok pre daný deň (dátum)
	if (typ == EXPORT_DNA_XML) {
		som_v_tabulke = NIE;
	}

	if (typ != EXPORT_DNA_VIAC_DNI && som_v_tabulke == ANO) {
		// pre export pre mobilné zariadenia [export_monthly_druh >= 3] netreba tabuľku
		ExportHtmlComment("tabuľka obsahujúca jednotlivé slávenia pre daný dátum s odkazmi na modlitby (buttons)");
		Export("<" HTML_TABLE ">\n");
	}
	// vytvorenie linku
	if (typ == EXPORT_DNA_VIAC_DNI) {
		if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ISO_DATUM)) {
			i = LINK_ISO_8601;
		}
		else {
			i = LINK_DEN;
		}
		mystrcpy(pom1, "<" HTML_SPAN_BOLD "> ", SMALL);
		mystrcpy(pom2, HTML_SPAN_END, SMALL);
		mystrcpy(pom3, nazov_Dn(_global_den.denvt), SMALL);
	}// typ == EXPORT_DNA_VIAC_DNI
	else if (typ == EXPORT_DNA_VIAC_DNI_SIMPLE) {
		if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ISO_DATUM)) {
			i = LINK_ISO_8601;
		}
		else {
			i = LINK_DEN;
		}
		mystrcpy(pom3, nazov_Dn(_global_den.denvt), SMALL);
	}// typ == EXPORT_DNA_VIAC_DNI_SIMPLE
	else if (typ == EXPORT_DNA_VIAC_DNI_TXT) {
		i = LINK_DEN_MESIAC_NIE;
	}// typ == EXPORT_DNA_VIAC_DNI_TXT
	else {
		i = LINK_DEN_MESIAC_NIE;
	}// typ != EXPORT_DNA_VIAC_DNI ani EXPORT_DNA_VIAC_DNI_SIMPLE ani EXPORT_DNA_VIAC_DNI_TXT

	if (i == LINK_DEN_MESIAC_NIE) {
		mystrcpy(_global_link, STR_EMPTY, MAX_STR);
	}
	else if (PODMIENKA_JE_BATCH_MODE_MONTHLY__AND__PLAIN_EXPORT) {
		vytvor_global_link_class_new(_global_den.den, _global_den.mesiac, _global_den.rok, i, NIE, STR_EMPTY, pom3);
	}
	else {
		vytvor_global_link_class_new(_global_den.den, _global_den.mesiac, _global_den.rok, i, NIE, HTML_CLASS_NAME_CALENDAR_DAY, pom3); // this method fills the following global string variables: _global_string, _global_string2 and _global_string_farba
	}

	// export vytvoreného linku
	if (som_v_tabulke == ANO) {
		Export("\n<" HTML_TABLE_ROW ">\n");
	}

	Log("-- _export_rozbor_dna(typ == %d): pomocné výpisy...\n", typ);

	Log("pom1 == %s\n", pom1);
	Log("_global_link == %s\n", _global_link);
	Log("pom2 == %s\n", pom2);
	Log("_global_opt_batch_monthly == %d\n", _global_opt_batch_monthly);
	Log("export_monthly_druh == %d\n", export_monthly_druh);

	// prvy stlpec: cislo dna
	if (typ != EXPORT_DNA_XML) {
		ExportHtmlComment("col:day_number");
	}

	if (som_v_tabulke == ANO) {
		Export("<" HTML_TABLE_CELL_VALIGN_TOP ">");
	}
	else if (typ == EXPORT_DNA_VIAC_DNI) {
#ifndef BEHAVIOUR_CMDLINE
		Export(HTML_P_INLINE);
#else
		Export(HTML_P_BEGIN);
#endif
	}
	if (typ != EXPORT_DNA_XML) {
		Export("%s%s%s", pom1, _global_link, pom2);
	}
	if (som_v_tabulke == ANO) {
		Export(HTML_TABLE_CELL_END "\n");
	}

	// ďalší stĺpec: buttons (tlačidlá), podľa typu výpisu
	if (typ != EXPORT_DNA_XML) {
		ExportHtmlComment("col:buttons");
	}

	if (som_v_tabulke == ANO) {
		ExportTableCell(HTML_TABLE_CELL);
	}

#ifdef OS_Windows_Ruby
	if (typ != EXPORT_DNA_XML) {
		ExportHtmlComment("_export_rozbor_dna_zoznam:follows");
	}
#endif
	_export_rozbor_dna_zoznam(typ);

	// XML export -- začiatok pre daný deň (dátum)
	if (typ == EXPORT_DNA_XML) {
		som_v_tabulke = NIE;
		Export(ELEM_BEGIN(XML_DAY) "\n");
		_exportXmlDay();
	}

#ifdef OS_Windows_Ruby
	if (typ != EXPORT_DNA_XML) {
		ExportHtmlComment("_export_rozbor_dna_interpretuj_zoznam:follows");
	}
#endif
	_export_rozbor_dna_interpretuj_zoznam(EXPORT_TYP_WEB_MODE, typ, som_v_tabulke, (char *)STR_EMPTY, 0, 0);

	// ToDo: # c6e031537b removed this funcionality, # a675c94dfb recovered it only for Windows/Ruby + fixed for XML export; ToDo: enable if user wants (create new bit-component option to show Roman letter)
#ifdef OS_Windows_Ruby
	if (typ == EXPORT_DNA_VIAC_DNI) {
		// ďalší stĺpec: rímske číslo podľa týždňa žaltára, pre nedele aj liturgický rok A, B resp. C; _global_string2 set above within call of _export_rozbor_dna_interpretuj_zoznam(); for XML export see below -- exported by _exportXmlDay2();
		if (som_v_tabulke == ANO) {
			Export(HTML_TABLE_CELL_END "\n");

			ExportHtmlComment("col:roman_number");

			Export("<" HTML_TABLE_CELL_VALIGN_TOP ">");
		}
		else {
			ExportNonbreakingSpace();
		}
		Export("\n");
		// vypisanie rimskeho cisla (citanie)
		Export("%s", _global_string2);
	}// (typ == EXPORT_DNA_VIAC_DNI)
#endif

	if (som_v_tabulke == ANO) {
		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");
	}
	else {
		if ((typ != EXPORT_DNA_VIAC_DNI) && (typ != EXPORT_DNA_VIAC_DNI_TXT) && (typ != EXPORT_DNA_XML)) {
			Export(HTML_P_END "" HTML_DIV_END "\n");
		}
		if (typ == EXPORT_DNA_VIAC_DNI) {
			Export(HTML_P_END "\n");
		}
	}
	// EXPORT_DNA_VIAC_DNI: predpoklada, ze sme v tabulke
	if (typ != EXPORT_DNA_VIAC_DNI && som_v_tabulke == ANO) {
		// pre export pre mobilné zariadenia [export_monthly_druh >= 3] netreba tabuľku
		Export(HTML_TABLE_END "\n");
	}

	if ((typ != EXPORT_DNA_VIAC_DNI) && (typ != EXPORT_DNA_VIAC_DNI_SIMPLE) && (typ != EXPORT_DNA_VIAC_DNI_TXT) && (typ != EXPORT_DNA_XML)) {

		if ((_global_linky == ANO) || (PODMIENKA_JE_BATCH_MODE_MONTHLY__AND__PLAIN_EXPORT)) {

			// vložené vypísanie kalendára a hlavného formulára 
			if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_BUTTONS_ORDER)) {
				Export(HTML_P_BEGIN"" HTML_P_END "\n");
				if ((typ != EXPORT_DNA_VIAC_DNI_TXT) && (typ != EXPORT_DNA_XML)) {
					_export_rozbor_dna_buttons_dni(typ);
				}
			}

			ExportHtmlComment("BEGIN: kalendárik");
			if (PODMIENKA_JE_BATCH_MODE_MONTHLY__AND__PLAIN_EXPORT) {
				Log("pre tento typ exportu sa kalendárik negeneruje\n");
			}
			else {
				_export_rozbor_dna_kalendar(typ);
			}
			ExportHtmlComment("END: kalendárik");

			ExportHtmlComment("BEGIN: veľká tabuľka s kalendárom a hlavným formulárom");

			Log("_global_opt_batch_monthly == %d [2011-04-13]\n", _global_opt_batch_monthly);
			Log("export_monthly_druh == %d [2011-04-13]\n", export_monthly_druh);

			if (_global_linky == ANO) {

				ExportHtmlComment("nasleduje formulár");
				_export_main_formular(_global_den.den, _global_den.mesiac, _global_den.rok, _global_den.denvt);

			}// if (_global_linky == ANO)

			ExportHtmlComment("END: veľká tabuľka s kalendárom a hlavným formulárom");
		}
	}// (typ != EXPORT_DNA_VIAC_DNI) && (typ != EXPORT_DNA_VIAC_DNI_TXT)
	else {
		Log("-- _export_rozbor_dna(): skip...\n");
	}

	// XML export -- koniec pre daný deň (dátum)
	if (typ == EXPORT_DNA_XML) {
		_exportXmlDay2();
		Export(ELEM_END(XML_DAY) "\n\n");
	}

	Log("-- _export_rozbor_dna(typ == %d): koniec.\n", typ);
} // _export_rozbor_dna()

void _export_rozbor_dna_batch(short int typ, short int modlitba = MODL_NEURCENA, short int d_from_m_from_r_from = 0) {
	// poznamky bez uvedenia datumu su prevzate z _export_rozbor_dna; 2003-07-07

	// treba brat do uvahy:
	// 1. ked ma sviatok prioritu, tak ide on (ulozeny v _global_den, ak pocet_svatych == 0; resp. v _global_svaty(1), ak pocet_svatych > 0;)
	// 2. ked su lubovolne spomienky, su ulozene v premennych _global_svaty(i) (i > 0 && i <= _global_pocet_svatych),
	//    naviac treba napisat _global_den (ako vsedny den)
	// 3. ak ide o sobotu v OBD_CEZ_ROK, treba ponuknut moznost _global_pm_sobota (spomienka panny marie v sobotu)
	// 4. ak ide o ľubovoľné spomienky, odkaz na modlitbu cez deň má byť pre všedný deň (== 0) [2014-10-03, Laci Dvornik]

	// 2009-08-04: rozšírené o nepovinný vstupný parameter 'modlitba', ktorý hovorí, či sa majú exportovať všetky modlitby (ako doteraz) alebo len táto modlitba (pre export_monthly_druh >= 1)
	char batch_command[MAX_STR] = STR_EMPTY;
	// ak vypisovat do jednotlivych suborov, 2003-07-08
	if (_global_opt_append != YES) {
		// pripravime si command line string pre dany datum
		// 2008-11-29: rozličný export
		if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE)
			sprintf(batch_command, "%s -i%s -qpdt -d%d -m%d -r%d -u%d -e" FILENAME_EXPORT_DATE_SIMPLE "_",
				name_binary_executable, include_dir,
				_global_den.den, _global_den.mesiac, _global_den.rok,
				_global_opt_export_date_format,
				_global_den.rok % 100, _global_den.mesiac, _global_den.den);
		else // EXPORT_DATE_FULL
			sprintf(batch_command, "%s -i%s -qpdt -d%d -m%d -r%d -u%d -e" FILENAME_EXPORT_DATE_FULL "_",
				name_binary_executable, include_dir,
				_global_den.den, _global_den.mesiac, _global_den.rok,
				_global_opt_export_date_format,
				_global_den.rok, _global_den.mesiac, _global_den.den);
	}
	// v opacnom pripade je furt ten isty fajl, 2003-07-08, pridame tam aj "-a1" = append
	else {
		sprintf(batch_command, "%s -i%s -qpdt -d%d -m%d -r%d -a1 -e%s.htm",
			name_binary_executable, include_dir,
			_global_den.den, _global_den.mesiac, _global_den.rok,
			_global_string); // _global_string sa nastavi v _main_batch_mode();
	}
	Log("_export_rozbor_dna_batch(): batch_command == %s...\n", batch_command);

	Log("vo funkcii _export_rozbor_dna_batch() volám _export_rozbor_dna_zoznam()...\n");

	ExportHtmlComment("_export_rozbor_dna_zoznam-from-batch-follows");
	_export_rozbor_dna_zoznam(typ);

	// Log_zoznam();
	Log("vo funkcii _export_rozbor_dna_batch() volám _export_rozbor_dna_interpretuj_zoznam()...\n");
	_export_rozbor_dna_interpretuj_zoznam(EXPORT_TYP_BATCH_MODE, typ, 0, batch_command, modlitba, d_from_m_from_r_from);

} // _export_rozbor_dna_batch()

void _export_rozbor_dna_mesiaca_batch(short int d, short int m, short int r) {
	Log("_export_rozbor_dna_mesiaca_batch() -- začiatok\n");
	// časť podľa _export_rozbor_dna_batch() 
	char batch_command[MAX_STR] = STR_EMPTY;
	char str_den[SMALL] = STR_EMPTY;
	char str_subor[SMALL] = STR_EMPTY;
	char str_month[SMALL] = STR_EMPTY;
	char _local_export_navig_hore[SMALL] = STR_EMPTY;
	char pom[SMALL] = STR_EMPTY; // pomocný reťazec (priliepanie parametrov do export_dalsie_parametre)
	char export_dalsie_parametre[SMALL] = STR_EMPTY; // reťazec pre kalendár (export_kalendar); 2011-11-30: pridaný do toho istého reťazca aj font

	// 2010-08-04: pridané odovzdanie parametra pre kalendár 
	// 2010-09-14: podmienka opravená; ak nie je kalendár určený resp. je všeobecný pre daný jazyk, nie je potrebné ho exportovať
	// 2011-03-18: použité z iných miest aj v _export_rozbor_dna_mesiaca_batch() -- exportovanie parametra k (_global_kalendar)
	strcpy(export_dalsie_parametre, STR_EMPTY);
	// 2011-03-18: použité z iných miest aj v execute_batch_command() -- exportovanie parametra k (_global_kalendar)
	if (PODMIENKA_EXPORTOVAT_KALENDAR) {
		sprintf(pom, " -k%s", skratka_kalendara[_global_kalendar]);
	}
	else {
		Log("\tNetreba prilepiť kalendár (jazyk == %s, kalendár == %s)\n", skratka_jazyka[_global_jazyk], skratka_kalendara[_global_kalendar]);
		strcpy(pom, STR_EMPTY);
	}
	strcat(export_dalsie_parametre, pom);
	Log("Exportujem kalendár: export_dalsie_parametre == `%s'\n", export_dalsie_parametre);

	// 2011-11-30, 2021-03-05: exportovanie parametra F (_global_font)
	if (PODMIENKA_EXPORTOVAT_CUSTOM_FONT) {
		Log("\tPrilepujem custom font (font == %s)\n", pom_FONT);
		sprintf(pom, " -F%s", pom_FONT);
	}
	else if (PODMIENKA_EXPORTOVAT_STATIC_FONT) {
		Log("\tPrilepujem static font (font == %s)\n", nazov_fontu[_global_font]);
		sprintf(pom, " -F%s", nazov_fontu[_global_font]);
	}
	else {
		Log("\tNetreba prilepiť font...\n");
		strcpy(pom, STR_EMPTY);
	}
	strcat(export_dalsie_parametre, pom);
	Log("Exportujem font: export_dalsie_parametre == `%s'\n", export_dalsie_parametre);

	// 2011-11-30: exportovanie parametra S (_global_font_size)
	if (PODMIENKA_EXPORTOVAT_FONTSIZE) {
		sprintf(pom, " -S%s", nazov_font_size_css[_global_font_size]);
	}
	else {
		Log("\tNetreba prilepiť font size (size == %s)\n", nazov_font_size_css[_global_font_size]);
		strcpy(pom, STR_EMPTY);
	}
	strcat(export_dalsie_parametre, pom);
	Log("Exportujem font size: export_dalsie_parametre == `%s'\n", export_dalsie_parametre);

	// 2015-01-08: exportovanie parametra G (_global_style_margin)
	if (PODMIENKA_EXPORTOVAT_STYLE_MARGIN) {
		sprintf(pom, " -G%d", _global_style_margin);
	}
	else {
		Log("\tNetreba prilepiť style margin (style margin == %d)\n", _global_style_margin);
		strcpy(pom, STR_EMPTY);
	}
	strcat(export_dalsie_parametre, pom);
	Log("Exportujem style margin: export_dalsie_parametre == `%s'\n", export_dalsie_parametre);

	// 2023-03-11: exportovanie parametra L (_global_line_height_perc)
	if (PODMIENKA_EXPORTOVAT_LINE_HEIGHT_PERC) {
		sprintf(pom, " -L%d", _global_line_height_perc);
	}
	else {
		Log("\tNetreba prilepiť line height (line height == %d)\n", _global_line_height_perc);
		strcpy(pom, STR_EMPTY);
	}
	strcat(export_dalsie_parametre, pom);
	Log("Exportujem line height: export_dalsie_parametre == `%s'\n", export_dalsie_parametre);

	// 2013-12-12: exportovanie parametra c (_global_css)
	if (PODMIENKA_EXPORTOVAT_CSS) {
		sprintf(pom, " -c%s", skratka_css[_global_css]); // nazov_css[_global_css]
	}
	else {
		Log("\tNetreba prilepiť css (css == %s/%s)\n", skratka_css[_global_css], nazov_css[_global_css]);
		strcpy(pom, STR_EMPTY);
	}
	strcat(export_dalsie_parametre, pom);
	Log("Exportujem css: export_dalsie_parametre == `%s'\n", export_dalsie_parametre);

	// reťazec pre deň a pre názov súboru
	if (d != VSETKY_DNI) {
		LOG_ciara;
		Log("deň d == %d...\n", d);
		sprintf(str_den, "%d", d);
		if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE)
			sprintf(str_subor, FILENAME_EXPORT_DATE_SIMPLE, r % 100, m, d);
		else // EXPORT_DATE_FULL
			sprintf(str_subor, FILENAME_EXPORT_DATE_FULL, r, m, d);
		mystrcpy(_local_export_navig_hore, _global_export_navig_hore_month, SMALL);
	}
	else {
		// d == VSETKY_DNI
		Log("deň d == VSETKY_DNI...\n");
		mystrcpy(str_den, STR_VSETKY_DNI, SMALL);
		if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE)
			sprintf(str_subor, FILENAME_EXPORT_MONTH_SIMPLE, r % 100, m);
		else // EXPORT_DATE_FULL
			sprintf(str_subor, FILENAME_EXPORT_MONTH_FULL, r, m);
		// mystrcpy(_local_export_navig_hore, _global_export_navig_hore, SMALL);
		sprintf(_local_export_navig_hore, "..%s%s", STR_PATH_SEPARATOR_HTML, name_batch_html_file);
		// vypísanie linku do zoznamu mesiacov (len v prípade d == VSETKY_DNI) -- ten istý adresár
		if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE)
			sprintf(str_month, "." STR_PATH_SEPARATOR_HTML "" DIRNAME_EXPORT_MONTH_SIMPLE "" STR_PATH_SEPARATOR_HTML, r % 100, m, nazov_mes[m - 1]);
		else // EXPORT_DATE_FULL
			sprintf(str_month, "." STR_PATH_SEPARATOR_HTML "" DIRNAME_EXPORT_MONTH_FULL "" STR_PATH_SEPARATOR_HTML, r, m, nazov_mesiaca_asci(m - 1));
		Log("str_month == %s\n", str_month);
		if (_global_jazyk == JAZYK_HU) {
			fprintf(batch_html_file, "<li>" HTML_A_HREF_BEGIN "\"%s%s.htm\">%d. %s" HTML_A_END "</li>\n", str_month, str_subor, r, nazov_mesiaca(m - 1));
		}
		else {
			fprintf(batch_html_file, "<li>" HTML_A_HREF_BEGIN "\"%s%s.htm\">%s %d" HTML_A_END "</li>\n", str_month, str_subor, nazov_mesiaca(m - 1), r);
		}
	}
	if (_global_opt_append != YES) {
		Log("pripravíme si command-line string pre daný mesiac...\n");
		// pripravíme si command-line string pre daný mesiac
		sprintf(batch_command, "%s -i%s -qpdt -d%s -m%d -r%d -u%d -e%s.htm", name_binary_executable, include_dir, str_den, m, r, _global_opt_export_date_format, str_subor);
		Log("batch_command == `%s'...\n", batch_command);
	}

	// časť podľa execute_batch_command() 
	char parameter_M[SMALL] = STR_EMPTY; // parametre pre výsledné HTML (parameter 'M' a parametre pre odkazy na súbory, napr. 'I')
	char parameter_I[SMALL] = STR_EMPTY;
	if (_global_opt_batch_monthly == ANO) {
		Log("1:parameter_M...\n");
		sprintf(parameter_M, " -M%d", export_monthly_druh);
		Log("parameter_M == `%s'...\n", parameter_M);
		if (!(equals(_local_export_navig_hore, STR_EMPTY) || equals(_local_export_navig_hore, DEFAULT_MONTH_EXPORT))) {
			Log("parameter_I...\n");
			sprintf(parameter_I, " -I%s", _local_export_navig_hore);
			Log("parameter_I == `%s'...\n", parameter_I);
			strcat(parameter_M, parameter_I);
			Log("parameter_M == `%s'...\n", parameter_M);
		}
	}// if (_global_opt_batch_monthly == ANO)
	else {
		mystrcpy(parameter_M, STR_EMPTY, SMALL);
	}// else if (_global_opt_batch_monthly == ANO)

	// samotné vytlačenie príkazu
	// exportovanie chýbajúcich option 0 až 5
	// nie pre append (mohla by tam byť celá časť kódu od prípravy batch_command)
	if (_global_opt_append != YES) {
		Log("zapisujem do batch_file...\n");
		Log("5:parameter_M == `%s'...\n", parameter_M);
		fprintf(batch_file, "%s -0%llu -1%llu -2%llu -3%llu -4%llu -5%llu -j%s%s%s\n", batch_command,
			_global_opt[OPT_0_SPECIALNE], _global_opt[OPT_1_CASTI_MODLITBY], _global_opt[OPT_2_HTML_EXPORT], _global_opt[OPT_3_SPOLOCNA_CAST], _global_opt[OPT_4_OFFLINE_EXPORT], _global_opt[OPT_5_ALTERNATIVES],
			skratka_jazyka[_global_jazyk], parameter_M, export_dalsie_parametre);
	}
	Log("_export_rozbor_dna_mesiaca_batch() -- koniec\n");
} // _export_rozbor_dna_mesiaca_batch()

short int je_mozne_spol_cast_nebrat(short int poradie_svaty) {
	Log("je_mozne_spol_cast_nebrat(%d): ", poradie_svaty);
	short int ret;
	ret = TRUE; // default

	if (poradie_svaty == 0) {
		if (_je_global_den_slavnost || _je_global_den_sviatok) {
			ret = FALSE;
		}
	}
	else if (poradie_svaty < PORADIE_PM_SOBOTA) {
		if ((_global_svaty(poradie_svaty).typslav == SLAV_SLAVNOST) || (_global_svaty(poradie_svaty).typslav == SLAV_SVIATOK)) {
			ret = FALSE;
		}
	}
	// netreba else if poradie_svaty == PORADIE_PM_SOBOTA | 2012-10-22: spomienka PM v sobotu je vždy ľubovoľná spomienka

	if ((_global_den.den == 2) && (_global_den.mesiac - 1 == MES_NOV)) {
		ret = FALSE;
	}// NOV02 == 02NOV
	Log("%d\n", ret);
	return ret;
} // je_mozne_spol_cast_nebrat()

// ked stlaci button 'Detaily...' pri konretnej modlitbe, zavola sa z funkcie rozbor_dna_s_modlitbou() toto vypisanie detailov (options) pre konretnu modlitbu
// vela z jadra je prevzateho z funkcie _main_dnes()
void showDetails(short int den, short int mesiac, short int rok, short int poradie_svaty) {
	Log("showDetails(%d, %s, %d, %d) -- začiatok...\n", den, nazov_mesiaca(mesiac - 1), rok, poradie_svaty);
	Log("_global_den: \n");
	Log(_global_den);

	char pom2[MAX_STR];
	mystrcpy(pom2, STR_EMPTY, MAX_STR);
	char pom3[MAX_STR];
	mystrcpy(pom3, STR_EMPTY, MAX_STR);

	prilep_request_options(pom2, pom3);

	char action[MAX_STR];
	mystrcpy(action, STR_EMPTY, MAX_STR);

	// úvodná navigácia
	if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_NAVIGATION)) {
		ExportHtmlComment("navigácia začiatok");

		_export_rozbor_dna_buttons_dni(EXPORT_DNA_JEDEN_DEN, NIE);

		// najprv dni, potom modlitby
		Export("<" HTML_TABLE ">\n");
		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		_export_rozbor_dna_buttons(EXPORT_DNA_JEDEN_DEN, _global_poradie_svaty, NIE, ANO);

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");
		Export(HTML_TABLE_END "\n");
	}

	// začiatok formulára
	Export(HTML_P_BEGIN);
	Export((char *)html_text_detaily_uvod[_global_jazyk]);
	Export(HTML_P_END "\n");
	sprintf(action, "%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d%s",
		uncgi_name,
		STR_QUERY_TYPE, STR_PRM_DATUM,
		STR_DEN, den,
		STR_MESIAC, mesiac,
		STR_ROK, rok,
		STR_DALSI_SVATY, poradie_svaty,
		pom2);
	Export_HtmlFormPOST(action);

	Export("<ul>\n");

	Export("<li>");
	Export((char *)html_text_modlitba[_global_jazyk]);
	Export(" \n");

	// pole WWW_MODLITBA
	// ToDo: zvážiť pre slávnosti zobraziť aj prvé vešpery s kompletóriom...
	Export(HTML_FORM_SELECT"name=\"%s\">\n", STR_MODLITBA);
	Export("<option>%s</option>\n", nazov_modlitby(MODL_INVITATORIUM));
	Export("<option%s>%s</option>\n", html_option_selected, nazov_modlitby(MODL_POSV_CITANIE));
	Export("<option>%s</option>\n", nazov_modlitby(MODL_RANNE_CHVALY));
	Export("<option>%s</option>\n", nazov_modlitby(MODL_PREDPOLUDNIM));
	Export("<option>%s</option>\n", nazov_modlitby(MODL_NAPOLUDNIE));
	Export("<option>%s</option>\n", nazov_modlitby(MODL_POPOLUDNI));
	// spomienka P. Márie v sobotu nemá vešpery ani kompletórium
	if (poradie_svaty != PORADIE_PM_SOBOTA) {
		Export("<option>%s</option>\n", nazov_modlitby(MODL_VESPERY));
		Export("<option>%s</option>\n", nazov_modlitby(MODL_KOMPLETORIUM));
	}
	Export("<option>%s</option>\n", nazov_modlitby(MODL_VSETKY));
	Export("</select>\n");

	Export("</li>\n");

	if (JE_PORADIE_SVATY_OK(poradie_svaty)) {

		// najprv si rozkodujeme, co je v _global_den.spolcast
		_struct_sc sc = _decode_spol_cast(_global_den.spolcast);
		// WWW_OPT_3 changed to WWW_FORCE_OPT_3
		Export("<li>");
		Export((char *)html_text_spol_casti_vziat_zo[_global_jazyk]);
		Export(" \n");
		Export(HTML_FORM_SELECT"name=\"%s\">\n", STR_FORCE_OPT_3);
		if (je_spolocna_cast_urcena(sc.a1)) {
			Export("<option%s>%s</option>\n", html_option_selected, nazov_spolc(sc.a1));
			if (je_spolocna_cast_urcena(sc.a2)) {
				Export("<option%s>%s</option>\n", ((unsigned)(sc.a2) != _global_opt[OPT_3_SPOLOCNA_CAST]) ? STR_EMPTY : html_option_selected, nazov_spolc(sc.a2));
				if (je_spolocna_cast_urcena(sc.a3)) {
					Export("<option%s>%s</option>\n", ((unsigned)(sc.a3) != _global_opt[OPT_3_SPOLOCNA_CAST]) ? STR_EMPTY : html_option_selected, nazov_spolc(sc.a3));
				}
			}
			if (je_mozne_spol_cast_nebrat(poradie_svaty)) {
				Export("<option>%s</option>\n", nazov_spolc(MODL_SPOL_CAST_NEBRAT));
			}
		}
		else {
			Export("<option%s>%s</option>\n", html_option_selected, nazov_spolc(MODL_SPOL_CAST_NEBRAT));
		}
		Export("</select>\n");
		Export(HTML_LINE_BREAK"<" HTML_SPAN_EXPLAIN ">");
		Export((char *)html_text_spol_casti_vziat_zo_explain[_global_jazyk]);
		Export(HTML_SPAN_END);
		Export("</li>\n");
	}// if (poradie svateho == 1, 2, 3... až MAX_POCET_SVATY)

	Export("</ul>\n");

	// 2011-10-03: toto by tu v konečnom dôsledku nejako malo byť... ale nie je to skĺbené s pôvodnými detailami (lebo celé detaily sú jeden <form>)
	// _export_main_formular(den, mesiac, rok, _global_den.denvt);

	// explanation
	Export(HTML_P_BEGIN"\n");
	Export((char *)html_text_detaily_explain[_global_jazyk]);
	Export(HTML_P_END "\n");

	Export(HTML_DIV_CENTER"\n");

	// button "Zobraz modlitbu"
	ExportHtmlComment("button Show");
	Export(HTML_FORM_INPUT_SUBMIT" value=\"");
	Export((char *)HTML_BUTTON_DET_SHOW);
	Export("\"" HTML_FORM_INPUT_END "\n");

	// button "Vyčisti"
	ExportHtmlComment("button Clear");
	Export(HTML_NONBREAKING_SPACE_LONG "\n");
	Export(HTML_FORM_INPUT_RESET2" value=\"");
	Export((char *)HTML_BUTTON_DET_DEFAULTS);
	Export("\"" HTML_FORM_INPUT_END "\n");

	Export(HTML_DIV_END"\n");

	// koniec formulára
	Export("</form>\n");

	Log("showDetails(%d, %s, %d, %d) -- koniec\n", den, nazov_mesiaca(mesiac - 1), rok, poradie_svaty);
} // showDetails();

void _nastav_global_pocet_zalmov_kompletorium(short int modlitba) {
	Log("_nastav_global_pocet_zalmov_kompletorium(modlitba == %d): začiatok...\n", modlitba);
	if ((modlitba == MODL_KOMPLETORIUM) || (modlitba == MODL_DRUHE_KOMPLETORIUM)) {
		_global_pocet_zalmov_kompletorium = _global_modl_kompletorium.pocet_zalmov;
	}
	else if (modlitba == MODL_PRVE_KOMPLETORIUM) {
		_global_pocet_zalmov_kompletorium = _global_modl_prve_kompletorium.pocet_zalmov;
	}
	else {
		_global_pocet_zalmov_kompletorium = 1;
	}
	Log("SET: _global_pocet_zalmov_kompletorium == %d...\n", _global_pocet_zalmov_kompletorium);
	Log("_nastav_global_pocet_zalmov_kompletorium(): koniec\n");
} // _nastav_global_pocet_zalmov_kompletorium()

// skoro ako rozbor_dna(), avsak dostane este int, ktory oznacuje modlitbu; a int, ktory oznacuje poradie svateho, ak je ich viac (2,3).
// pracuje takto:
//
// -- kvoli prvym vesperam nasledujuceho dna spusti analyzuj_rok(rok + 1);
// -- spusti _rozbor_dna(datum + 1, X) (kde X je rok alebo rok + 1, podla dna)
// -- ulozi vysledok do lokalnej premennej _local_den, _local_svaty...
// -- spusti analyzuj_rok(rok);
// -- spusti _rozbor_dna(datum, rok);
// -- porovna, ci (ked su modlitbou vespery) budu prve vespery z dalsieho dna alebo nie,
// -- napokon spusti vytvorenie modlitby
//
// POZOR! Na rozdiel od rozbor dna, pred samotnym spustenim generovania modlitby je vysledok (co sa presne bude modlit) v premennej _global_den;
void rozbor_dna_s_modlitbou(short int typ, short int den, short int mesiac, short int rok, short int modlitba, short int poradie_svaty, short int aj_navigacia = ANO, short int force_neanalyzuj_rok = NIE) {
	short int ret = SUCCESS;

	short int backup_global_modlitba = _global_modlitba;

	_struct_dm _local_den;
	_INIT_DM(_local_den);

	_type_1vespery      *_local_modl_prve_vespery_ptr;
#define _local_modl_prve_vespery (*_local_modl_prve_vespery_ptr)
	_type_1kompletorium *_local_modl_1kompletorium_ptr;
#define _local_modl_prve_kompletorium (*_local_modl_1kompletorium_ptr)
	_type_vespery       *_local_modl_vespery_ptr;
#define _local_modl_vespery (*_local_modl_vespery_ptr)
	_type_kompletorium *_local_modl_kompletorium_ptr;
#define _local_modl_kompletorium (*_local_modl_kompletorium_ptr)

	short int _local_spol_cast = MODL_SPOL_CAST_NEURCENA;
	short int _local_opt_3_spol_cast = MODL_SPOL_CAST_NEURCENA;

	short int label_zmena_vynimky = NIE; // špeciálne výnimky, kedy sa tiež berie pre vešpery modlitba z nasledujúceho dňa; pozri časť VYNIMKY

	Log("Allocating memory...\n");
	// _local_modl_prve_vespery_ptr
	if ((_local_modl_prve_vespery_ptr = (_type_1vespery*)malloc(sizeof(_type_1vespery))) == NULL) {
		Log("  Not enough memory to allocate buffer for `_local_modl_prve_vespery_ptr'\n");
		return;
	}
	else {
		Log("  %d bytes for `_local_modl_prve_vespery_ptr'\n", sizeof(_type_1vespery));
		_INIT_TMODLITBA1(_local_modl_prve_vespery);
	}

	// _local_modl_1kompletorium_ptr
	if ((_local_modl_1kompletorium_ptr = (_type_1kompletorium*)malloc(sizeof(_type_1kompletorium))) == NULL) {
		Log("  Not enough memory to allocate buffer for `_local_modl_1kompletorium_ptr'\n");
		return;
	}
	else {
		Log("  %d bytes for `_local_modl_1kompletorium_ptr'\n", sizeof(_type_1kompletorium));
		_INIT_TMODLITBA3(_local_modl_prve_kompletorium);
	}
	// _local_modl_vespery_ptr
	if ((_local_modl_vespery_ptr = (_type_vespery*)malloc(sizeof(_type_vespery))) == NULL) {
		Log("  Not enough memory to allocate buffer for `_local_modl_vespery_ptr'\n");
		return;
	}
	else {
		Log("  %d bytes for `_local_modl_vespery_ptr'\n", sizeof(_type_vespery));
		_INIT_TMODLITBA1(_local_modl_vespery);
	}

	// _local_modl_kompletorium_ptr
	if ((_local_modl_kompletorium_ptr = (_type_kompletorium*)malloc(sizeof(_type_kompletorium))) == NULL) {
		Log("  Not enough memory to allocate buffer for `_local_modl_kompletorium_ptr'\n");
		return;
	}
	else {
		Log("  %d bytes for `_local_modl_kompletorium_ptr'\n", sizeof(_type_kompletorium));
		_INIT_TMODLITBA3(_local_modl_kompletorium);
	}

	Log("...done.\n");

	// lokalna kopia roka; ak treba analyzovat dalsi rok
	short int _local_rok = -1;

	// when running more times from showAllPrayers()
	if (force_neanalyzuj_rok == ANO) {
		_local_rok = rok;
	}

	// lokálna premenná, čo obsahuje string vypísaný na obrazovku -- je to kópia _global_string (preto veľkosť 2011-09-27 opravená)
	char _local_string[MAX_GLOBAL_STR];

	_global_modlitba = modlitba;

	Log("-- rozbor_dna_s_modlitbou(int, int, int, int, int): begin (%d.%d %d, %d; %d)\n", den, mesiac, rok, modlitba, poradie_svaty);
	_struct_den_mesiac datum;

	short int svaty_dalsi_den = UNKNOWN_PORADIE_SVATEHO;

	if ((modlitba == MODL_VESPERY) || (modlitba == MODL_KOMPLETORIUM)) {
		// najprv analyzujem nasledujuci den - kvoli prvym vesperam resp. kompletoriu
		Log("kedze modlitba je vespery alebo kompletorium, robim tuto cast... (naplnenie _local_den)\n");
		_local_rok = rok;
		// do premennej datum dame datum nasledujuceho dna
		if (den == pocet_dni[mesiac - 1]) {
			datum.den = 1;
			if (mesiac == 12) {
				datum.mesiac = 1;
				_local_rok = rok + 1;
			}
			else {
				datum.mesiac = mesiac + 1;
			}
		}
		else {
			datum.den = den + 1;
			datum.mesiac = mesiac;
		}
		Log("spúšťam analýzu roka (rok %d)...\n", _local_rok);
		analyzuj_rok(_local_rok); // výsledok dá do _global_r
		LOG_ciara;

		Log("rozbor_dna_s_modlitbou(): spúšťam analýzu nasledujúceho dňa (%d. %s %d), poradie_svaty == %d...\n", datum.den, nazov_mesiaca(datum.mesiac - 1), _local_rok, svaty_dalsi_den);
		ret = _rozbor_dna_s_modlitbou(datum, _local_rok, modlitba, svaty_dalsi_den);
		if (ret == FAILURE) {
			Log("_rozbor_dna_s_modlitbou() pre nasledujuci den returned FAILURE, so...\n");
			Log("-- rozbor_dna_s_modlitbou(int, int, int, int): uncomplete end\n");
			goto LABEL_s_modlitbou_DEALLOCATE;
		}// ret == FAILURE
		Log("rozbor_dna_s_modlitbou(): analýza nasledujúceho dňa (%d. %s %d) skončila.\n", datum.den, nazov_mesiaca(datum.mesiac - 1), rok);

		_local_den = _global_den;
		_local_spol_cast = _global_den.spolcast;
		_local_opt_3_spol_cast = (short int)_global_opt[OPT_3_SPOLOCNA_CAST];
		_local_modl_prve_vespery = _global_modl_prve_vespery;
		_local_modl_prve_kompletorium = _global_modl_prve_kompletorium;
		_local_modl_vespery = _global_modl_vespery;
		_local_modl_kompletorium = _global_modl_kompletorium;

		mystrcpy(_local_string, _global_string, MAX_GLOBAL_STR); // veľkosť 2011-09-27 opravená podľa _global_string

		Log("_local_spol_cast obsahuje: %d\n", _local_spol_cast);
		Log("_local_opt_3_spol_cast obsahuje: %d\n", _local_opt_3_spol_cast);
		Log("_local_string obsahuje: %s\n", _local_string);
		// Log("_local_modl_vespery obsahuje:\n"); Log(_local_modl_vespery);
		// Log("_local_modl_prve_vespery obsahuje:\n"); Log(_local_modl_prve_vespery);
		// Log("_global_modl_kompletorium obsahuje:\n"); Log(_global_modl_kompletorium);
		// Log("_global_modl_prve_kompletorium obsahuje:\n"); Log(_global_modl_prve_kompletorium);
		// Log("_local_modl_prve_kompletorium obsahuje:\n"); Log(_local_modl_prve_kompletorium);

		// cleanup kvôli tomu, že sa idú nastavovať (kompletórium pre ZDS - nasledujúci deň je OCR s alternatívami hymnov A/B, ale ZDS to nemá ponúkať; ostalo nastavenie v member premennej alternativy)
		Log("running cleanup pre _global_modl_* premenné...\n");

		_INIT_TMODLITBA1(_global_modl_vespery);
		_INIT_TMODLITBA3(_global_modl_kompletorium);
		_INIT_TMODLITBA1(_global_modl_prve_vespery);
		_INIT_TMODLITBA3(_global_modl_prve_kompletorium);

		LOG_ciara;
	}// kompletorium alebo vespery

	// teraz analyzujem dnesny den
	Log("teraz analyzujem dnešný (ten vyžiadaný) deň...\n");
	datum.den = den;
	datum.mesiac = mesiac;
	if (_local_rok != rok) {
		Log("spúšťam analýzu roka (rok %d)...\n", rok);
		analyzuj_rok(rok); // výsledok dá do _global_r
	}
	Log("rozbor_dna_s_modlitbou(): spúšťam analýzu tohto dňa (%d. %s %d)...\n", datum.den, nazov_mesiaca(datum.mesiac - 1), rok);
	ret = _rozbor_dna_s_modlitbou(datum, rok, modlitba, poradie_svaty);
	if (ret == FAILURE) {
		Log("_rozbor_dna_s_modlitbou() returned FAILURE, so...\n");
		Log("-- rozbor_dna_s_modlitbou(int, int, int, int): uncomplete end\n");
		goto LABEL_s_modlitbou_DEALLOCATE;
	}// ret == FAILURE
	Log("analyza tohto dna (%d. %s %d) skoncila.\n", datum.den, nazov_mesiaca(datum.mesiac - 1), rok);
	LOG_ciara;
	// teraz mam vsetky data v _global_den, _global_modl_...
	Log("teraz mam vsetky data v _global_den, _global_modl_...\n");

	// keďže test napr. na je_alternativa_doplnkova_psalmodia_z122_129 sa používal iba v _set_zalmy_mcd_doplnkova_psalmodia() volanej z zaltar_zvazok(), dávno predtým, ako sa pre obyčajnú spomienku nastaví napr. cez vlastnú časť, kalendár, v metóde _set_zalmy_sviatok_marie(), _set_mcd_doplnkova_psalmodia_z122_129()...
	Log("nedokonalý fix pre alternatívne žalmy v modlitbe cez deň, ak boli nastavené až neskôr, ako sa už predtým nastavila pre mcd doplnková psalmódia (napr. 15SEP pre ne-SK kalendár)...\n");
	__skus_zohladnit_set_zalmy_mcd_doplnkova_psalmodia_alternativy(modlitba);

	Log("nastavujem _global_string_modlitba...\n");
	init_global_string_modlitba(modlitba);
	Log("nastavujem _global_string_podnadpis...\n");
	init_global_string_podnadpis(modlitba);
	Log("nastavujem _global_string_spol_cast...\n");
	ret_sc = init_global_string_spol_cast(odfiltrujSpolCast(modlitba, _global_opt[OPT_3_SPOLOCNA_CAST]), poradie_svaty);

	// pre explicitne vyžiadané prvé vešpery resp. kompletórium po prvých vešperách
	if ((modlitba == MODL_PRVE_VESPERY) || (modlitba == MODL_PRVE_KOMPLETORIUM)) {
		Log("-- explicitne vyžiadané MODL_PRVE_VESPERY || MODL_PRVE_KOMPLETORIUM\n");
	}// if ((modlitba == MODL_PRVE_VESPERY) || (modlitba == MODL_PRVE_KOMPLETORIUM))

	// ak ma nasledujuci den prioritu pred dnesnym dnom
	if ((modlitba == MODL_VESPERY) || (modlitba == MODL_KOMPLETORIUM)) {
		Log("teraz uvidime, ci vespery/kompletorium nasledovneho dna nemaju nahodou prioritu...\n");

		// netyka sa to zeleneho stvrtka, velkeho tyzdna, velkonocneho trojdnia
		if (((_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN) && (_global_den.denvt != DEN_NEDELA)) || (_global_den.denvr == ZELENY_STVRTOK)) {
			Log("netyka sa to Svätého týždňa (okrem druhých vešpier Kvetnej nedele), ani Zeleného štvrtka\n");
			goto LABEL_NIE_INE_VESPERY;
		}
		else if (_global_den.litobd == OBD_VELKONOCNE_TROJDNIE) {
			Log("netyka sa to velkonocneho trojdnia\n");
			goto LABEL_NIE_INE_VESPERY;
		}
		// ...a tiez sa to netyka popolcovej stredy, 09/03/2000A.D.
		if ((_global_den.denvr == POPOLCOVA_STREDA) || ((_global_den.denvr == (POPOLCOVA_STREDA - 1)))) {
			// preto aj POPOLCOVA_STREDA aj POPOLCOVA_STREDA - 1, lebo prve aj druhe vespery
			Log("netyka sa to popolcovej stredy\n");
			goto LABEL_NIE_INE_VESPERY;
		}
		// ...a tiez sa to netyka dni velkonocnej oktavy okrem nedele
		if ((_global_den.litobd == OBD_VELKONOCNA_OKTAVA) && (_global_den.denvt != DEN_SOBOTA) && (_global_den.denvt != DEN_NEDELA)) {
			// sobota kvoli prvym vesperam
			Log("netyka sa to vsednych dni velkonocnej oktavy\n");
			goto LABEL_NIE_INE_VESPERY;
		}

		Log("ďalší deň (%d.%d.): _local_den.smer == %d, _local_den.denvt == %s, _local_den.litobd == %s (%d)\n",
			_local_den.den, _local_den.mesiac,
			_local_den.smer, nazov_dna(_local_den.denvt), nazov_obdobia_ext(_local_den.litobd), _local_den.smer);
		// Log(_local_den);
		// Log("_local_modl_prve_vespery obsahuje:\n"); Log(_local_modl_prve_vespery);
		// Log("_local_modl_prve_kompletorium obsahuje:\n"); Log(_local_modl_prve_kompletorium);

		Log("tento deň (%d.%d.): _global_den.smer == %d, prípadný override: _global_den_smer_override == %d, _global_den.denvt == %s, _global_den.litobd == %s (%d/%d)\n",
			_global_den.den, _global_den.mesiac,
			_global_den.smer, _global_den_smer_override, nazov_dna(_global_den.denvt), nazov_obdobia_ext(_global_den.litobd), _global_den.smer, _global_den_smer_override);

		// Log(_global_den);
		// Log("(3) _global_modl_prve_vespery obsahuje:\n"); Log(_global_modl_prve_vespery);
		// Log("(3) _global_modl_prve_kompletorium obsahuje:\n"); Log(_global_modl_prve_kompletorium);

		// časť: nastavenie VYNIMKY
		if (
			((_global_den.litobd == OBD_VELKONOCNA_OKTAVA) && (_global_den.denvt == DEN_SOBOTA)) // 2. velkonocna nedela
			|| ((_local_den.mesiac - 1 == MES_DEC) && (_local_den.den == 25)) // ked narodenie pana pripadne na pondelok, tak prve vespery maju prednost pred 4. adventnou nedelou; napr. rok 2000
			|| ((_local_den.denvr == SRDCA) && (_local_den.mesiac - 1 == MES_JUN) && (_local_den.den == 24)) // keď Najsv. Srdca Ježišovho padne na 24. júna, napr. rok 2022, tak prvé vešpery nasledujúceho dňa (Najsv. Srdca Ježišovho) majú prednosť pred druhými vešperami slávnosti sv. Jána Krstiteľa, ktorá sa špeciálne preložila na 23.6.
			|| ((_local_den.denvr == SRDCA) && (_local_den.mesiac - 1 == MES_JUN) && (_local_den.den == 29)) // analogicky, keď Najsv. Srdca Ježišovho padne na 29. júna, napr. rok 2057, tak prvé vešpery nasledujúceho dňa (Najsv. Srdca Ježišovho) majú prednosť pred druhými vešperami slávnosti sv. Petra a Pavla, ktorá sa zrejme špeciálne bude prekladať na 28.6.
			) {
			Log("VYNIMKY...\n");
			label_zmena_vynimky = ANO;
		}

		// časť: test VYNIMKY; it is necessary for "current" day take into account potentially required override (celebration of higher level)
		if ((/* _global_den.smer */ _global_den_smer_override > _local_den.smer) ||
			((/* _global_den.smer */ _global_den_smer_override == _local_den.smer) && (label_zmena_vynimky == ANO))
		) {
			Log("jumping to LABEL_ZMENA...\n");
			goto LABEL_ZMENA;
		}

		if (
			// č. 11: slávnosti su zvlášť význačnými dňami. ich slávenie sa začína prvými vešperami v predchádzajúci deň
			(/* _global_den.smer */ _global_den_smer_override < 5)
			// č. 13: sviatky sa slávia v rozsahu jedného dňa, a preto nemajú prvé vešpery, ak len nejde o sviatky Pána, ktoré pripadajú na Cezročnú neďelu a na nedeľu vo vianočnom období a nahradzujú nedeľňajšiu liturgiu hodín
			|| ((/* _global_den.smer */ _global_den_smer_override == 5) && (_global_den.denvt == DEN_NEDELA) && ((_global_den.litobd == OBD_CEZ_ROK) || je_vianocne(_global_den.litobd)))
			// nedeľa
			|| (_global_den.denvt == DEN_NEDELA)
			) {
			// č. 61: ak na ten isty den pripadnu vespery bezneho dna a prve vespery nasledujuceho dna, maju prednost vespery slavenia,
			// ktore ma v tabulke liturgickych dni vyssi stupen. v pripade rovnosti sa beru vespery bezneho dna.

			if (modlitba == MODL_VESPERY) {
				_global_modlitba = MODL_DRUHE_VESPERY;
				Log("-- MODL_DRUHE_VESPERY\n");
			}
			else if (modlitba == MODL_KOMPLETORIUM) {
				_global_modlitba = MODL_DRUHE_KOMPLETORIUM;
				Log("-- MODL_DRUHE_KOMPLETORIUM\n");
			}
			// Spomienka vsetkych vernych zosnulych -- nevypisem, ze su druhe vespery -- zapracované do init_global_string_modlitba()

			Log("nastavujem _global_string_modlitba... if ((_global_den.smer -> _global_den_smer_override < 5) || ...\n");
			init_global_string_modlitba(modlitba);

			Log("nastavujem _global_string_podnadpis... if ((_global_den.smer -> _global_den_smer_override < 5) || ...\n");
			init_global_string_podnadpis(modlitba);

			// this is not necessary (in fact, it causes problems: wrong description for http://localhost:2000/cgi-bin/l.cgi?qt=pdt&d=25&m=10&r=2015&p=mv&ds=1&j=cz&o0=134&o1=5376&o2=29432&o3=6)
			// introduced by commit # c48527f0d3 but now hopefully not necessary
			/*
			Log("kontrolujem _global_opt[OPT_3_SPOLOCNA_CAST]... if ((_global_den.smer -> _global_den_smer_override < 5) || : ");
			if (_local_spol_cast != MODL_SPOL_CAST_NEURCENA) {
				Log("setting _global_opt[OPT_3_SPOLOCNA_CAST]...\n");
				_global_opt[OPT_3_SPOLOCNA_CAST] = _local_spol_cast;
				Log("upravené podľa _local_spol_cast na %s (%d)\n", nazov_spolc(_local_spol_cast), _local_spol_cast);
			}
			else {
				Log("bez úpravy.\n");
			}
			*/

			Log("nastavujem _global_string_spol_cast... if ((_global_den.smer -> _global_den_smer_override < 5) || ...\n");
			ret_sc = init_global_string_spol_cast(odfiltrujSpolCast(modlitba, _global_opt[OPT_3_SPOLOCNA_CAST]), poradie_svaty);
		}// _global_den ma dvoje vespery/kompletorium, teda musime brat DRUHE

		else
			LABEL_ZMENA:
		if (
			// č. 11: slávnosti su zvlášť význačnými dňami. ich slávenie sa začína prvými vešperami v predchádzajúci deň
			(_local_den.smer < 5)
			|| ((_local_den.smer == 5) && (_local_den.denvt == DEN_NEDELA) && ((_local_den.litobd == OBD_CEZ_ROK) || je_vianocne(_local_den.litobd)))
			// č. 13: sviatky sa slávia v rozsahu jedného dňa, a preto nemajú prvé vešpery, ak len nejde o sviatky Pána, ktoré pripadajú na Cezročnú neďelu a na nedeľu vo vianočnom období a nahradzujú nedeľňajšiu liturgiu hodín
			|| (_local_den.denvt == DEN_NEDELA)
			// nedeľa
			) {
			Log("LABEL_ZMENA:...\n");
			// č. 61: ak na ten isty den pripadnu vespery bezneho dna a prve vespery nasledujuceho dna, maju prednost vespery slavenia,
			// ktore ma v tabulke liturgickych dni vyssi stupen. v pripade rovnosti sa beru vespery bezneho dna. sú tu špeciálne výnimky
			// časť: test VYNIMKY
			if ((/* _global_den.smer */ _global_den_smer_override > _local_den.smer)
				|| ((/* _global_den.smer */ _global_den_smer_override == _local_den.smer) && (label_zmena_vynimky == ANO))
			) {
				if ((/* _global_den.smer */ _global_den_smer_override == _local_den.smer) && (label_zmena_vynimky == ANO)) {
					Log("slávenia síce majú rovnaký stupeň, ale ide o špeciálne výnimky... see: VYNIMKY\n");
				}
				else {
					Log("čl. 61 VSLH: beriem vešpery z nasledujúceho dňa...\n");
				}

				short int d, m, r;
				d = _global_den.den;
				m = _global_den.mesiac;
				r = _global_den.rok;

				Log("LABEL_ZMENA: den == %d (d == %d), mesiac == %d (m == %d), rok == %d (r == %d)...\n", den, d, mesiac, m, rok, r); // it should be the same: d == den, m == mesiac, r == rok

				_global_den = _local_den; // note that also date is overriden! we have to back up day, month and year

				Log("LABEL_ZMENA: _global_den.den == %d, _global_den.mesiac == %d, _global_den.rok == %d...\n", _global_den.den, _global_den.mesiac, _global_den.rok);

				Log("isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY) == %d...\n", isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY));

				if (!isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY)) {
					// we do this ONLY when special option [display buttons for 1st vespers & 1st compline within the celebration] is NOT selected; in such case it is safer to CHANGE the date!
					_global_den.den = d; // den;
					_global_den.mesiac = m; // mesiac;
					_global_den.rok = r; // rok;

					Log("LABEL_ZMENA: _global_den.den == %d, _global_den.mesiac == %d, _global_den.rok == %d...\n", _global_den.den, _global_den.mesiac, _global_den.rok);

					// note that den, mesiac and rok have not been changed
				}
				else {
					// we will change the date (no backup used); this is the only special case we override input date values (_global_vstup_... values)
					_global_vstup_den = den = _global_den.den;
					_global_vstup_mesiac = mesiac = _global_den.mesiac;
					_global_vstup_rok = rok = _global_den.rok;

					Log("LABEL_ZMENA: The date HAS BEEN CHANGED!!! Also _global_vstup_... variables has been changed. (This is intentional behaviour. Example: Slovak calendar, May 12th, 2021.)\n");
					Log("LABEL_ZMENA: den == %d (d == %d), mesiac == %d (m == %d), rok == %d (r == %d)...\n", den, d, mesiac, m, rok, r);
				}

				if (su_vespery12(modlitba)) {
					Log("su_vespery12(); priraďujem %s z ďalšieho dňa:\n", nazov_modlitby(modlitba));
					_global_modl_prve_vespery = _local_modl_prve_vespery;
					_global_modl_vespery = _local_modl_prve_vespery;
				}

				if (je_kompletorium12(modlitba)) {
					Log("je_kompletorium12(); priraďujem %s z ďalšieho dňa (do „dnešného“ kompletória dávam prvé kompletórium z ďalšieho dňa...\n", nazov_modlitby(modlitba));
					// if (_local_den.smer < 5) { // introduced by # 7fc3d1a41306d9acb1254519db303561d9e27b00 (worked until # bad8fa0f0906472f4) // Log("priraďujem %s z ďalšieho dňa, ale iba ak ide o slávnosť (presnejšie, smer < 5)...\n", nazov_modlitby(modlitba));
					_global_modl_prve_kompletorium = _local_modl_prve_kompletorium;
					_global_modl_kompletorium = _local_modl_prve_kompletorium;
				}

				// 2012-11-20: doplnené priradenie, lebo sa zmenila premenná _global_den
				_global_poradie_svaty = svaty_dalsi_den;

				// 2012-11-08: pretože slávnosť alebo nedeľa má pre prvé vešpery nastvené vlastné prosby, je potrebné opätovne nastaviť pre vešpery, ak je zvolená táto možnosť, kratšie prosby z dodatku (možno ich použiť v ktorýkoľvek deň v roku)
				if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_VESP_KRATSIE_PROSBY)) {
					Log("(kvôli prvým vešperám) pre vešpery nastavujem kratšie prosby z dodatku -- možno ich použiť v ktorýkoľvek deň v roku (je zvolená táto možnosť)\n");
					_set_prosby_dodatok(_global_den.denvt, ANO);
				}

				// Log
				if (su_vespery12(modlitba)) {
					Log("CURRENT: prvé vešpery:\n");
					Log(_global_modl_prve_vespery);
					Log("CURRENT: vešpery:\n");
					Log(_global_modl_vespery);
				}
				else if (je_kompletorium12(modlitba)) {
					Log("CURRENT: prvé kompletórium:\n");
					Log(_global_modl_prve_kompletorium);
					Log("CURRENT: kompletórium:\n");
					Log(_global_modl_kompletorium);
				}

				// naplnenie _global_modl_...
				if (modlitba == MODL_VESPERY) {
					_global_modlitba = MODL_PRVE_VESPERY;
					Log("-- MODL_PRVE_VESPERY\n");
					_global_modl_vespery = _global_modl_prve_vespery;
					_global_modl_kompletorium = _global_modl_prve_kompletorium;
				}
				else if (modlitba == MODL_KOMPLETORIUM) {
					_global_modlitba = MODL_PRVE_KOMPLETORIUM;
					Log("-- MODL_PRVE_KOMPLETORIUM\n");
					_global_modl_vespery = _global_modl_prve_vespery;
					_global_modl_kompletorium = _global_modl_prve_kompletorium;
				}

				Log("v časti LABEL_ZMENA nastavujem _global_string...\n");
				mystrcpy(_global_string, _local_string, MAX_GLOBAL_STR); // veľkosť 2011-09-27 opravená podľa _global_string

				Log("v časti LABEL_ZMENA nastavujem _global_string_modlitba...\n");
				init_global_string_modlitba(modlitba);

				Log("v časti LABEL_ZMENA nastavujem _global_string_podnadpis...\n");
				init_global_string_podnadpis(modlitba);

				Log("v časti LABEL_ZMENA kontrolujem _global_opt[OPT_3_SPOLOCNA_CAST]: ");
				if (_local_spol_cast != MODL_SPOL_CAST_NEURCENA) {
					Log("setting _global_opt[OPT_3_SPOLOCNA_CAST]...\n");
					_global_opt[OPT_3_SPOLOCNA_CAST] = _local_spol_cast;
					Log("upravené podľa _local_spol_cast na %s (%d)\n", nazov_spolc(_local_spol_cast), _local_spol_cast);
				}
				else {
					Log("bez úpravy.\n");
				}

				Log("v časti LABEL_ZMENA nastavujem _global_string_spol_cast...\n"); // potrebné použiť svaty_dalsi_den
				ret_sc = init_global_string_spol_cast(odfiltrujSpolCast(modlitba, _global_opt[OPT_3_SPOLOCNA_CAST]), _global_poradie_svaty /* svaty_dalsi_den */);
			}
			else {
				Log("nič sa nedeje...\n");
			}
		}// _local_den ma dvoje vespery/kompletorium, teda musime brat PRVE
	}// vespery alebo kompletorium, zistovanie priority

	// predosla pasaz, kedy sa kontroluje priorita nasledujuceho dna, preskakujeme pre ostatne modlitby okrem vespier a kompletoria; poznamka pridana 2003-08-13

LABEL_NIE_INE_VESPERY:

	// special cases
	if (je_Spomienka_na_zosnulych_02NOV_nedela) {
		set_popis_svaty_rch_mcd_pc_vesp_den_mesiac(2, MES_NOV + 1);
	}

	LOG_ciara;
	Log("/* vypisanie udajov, podla ktorych vlastne budem generovat modlitbu */\n");
	Log("/* datum bol vypisany uz predtym, preto teraz (pri prvych vesperach) \n");
	Log(" * moze byt iny - o jeden den vacsi */\n");
	Log("_global_string: %s\n", _global_string);
	Log("modlitba = `%s' (%d)\n", nazov_modlitby(modlitba), modlitba);
	switch (modlitba) {
	case MODL_RANNE_CHVALY:
		Log(_global_modl_ranne_chvaly);
		break;
	case MODL_POSV_CITANIE:
		Log(_global_modl_posv_citanie);
		break;
	case MODL_PREDPOLUDNIM:
		Log(_global_modl_predpol);
		break;
	case MODL_NAPOLUDNIE:
		Log(_global_modl_napol);
		break;
	case MODL_POPOLUDNI:
		Log(_global_modl_popol);
		break;
	case MODL_VESPERY:
		Log(_global_modl_vespery);
		break;
	case MODL_PRVE_VESPERY:
		Log(_global_modl_prve_vespery);
		break;
	case MODL_INVITATORIUM:
		Log(_global_modl_invitatorium);
		break;
	case MODL_KOMPLETORIUM:
		Log(_global_modl_kompletorium);
		break;
	case MODL_PRVE_KOMPLETORIUM:
		Log(_global_modl_prve_kompletorium);
		break;
	}
	// Log("_global_den:\n"); Log(_global_den);

	Log("nastavujem do _global_pocet_zalmov_kompletorium počet žalmov...\n");
	_nastav_global_pocet_zalmov_kompletorium(modlitba);
	Log("_global_pocet_zalmov_kompletorium == %d...\n", _global_pocet_zalmov_kompletorium);

	if (typ != PRM_TXT) {
		// ToDo: maybe not necessary for typ == PRM_XML because it is already exported within _export_rozbor_dna_buttons()
		_export_heading_center(typ, _global_string);
	}

	// produce XML_DAY structure except XML_CELEBRATION structures -- difference with _export_rozbor_dna()
	if (typ == PRM_XML) {
		Export(ELEM_BEGIN(XML_DAY) "\n");
		_exportXmlDay();
		_export_rozbor_dna_buttons(EXPORT_DNA_XML, poradie_svaty, ANO, NIE);
		_exportXmlDay2();
		Export(ELEM_END(XML_DAY) "\n\n");
	}

	// úprava aj_navigacia pre TTS = voice output
	if ((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT)) && (modlitba != MODL_NEURCENA)) {
		Log("pre voice output upravujem aj_navigacia na NIE (lebo modlitba == %d)...\n", modlitba);
		aj_navigacia = CIASTOCNE;
	}

	if (_global_modlitba == MODL_DETAILY) {
		if (typ != PRM_TXT && typ != PRM_XML) {
			Log("spustam showDetails(%d, %s, %d, %d) z funkcie rozbor_dna_s_modlitbou():\n", den, nazov_mesiaca(mesiac - 1), rok, poradie_svaty);
			LOG_ciara;
			showDetails(den, mesiac, rok, poradie_svaty);
			LOG_ciara;
			Log("...po návrate zo showDetails(%d, %s, %d, %d) vo funkcii rozbor_dna_s_modlitbou().\n", den, nazov_mesiaca(mesiac - 1), rok, poradie_svaty);
		}
		// ignoring for TXT and XML export
	}// _global_modlitba == MODL_DETAILY
	else {
		Log("spustam showPrayer(_global_modlitba == %s; modlitba == %s) z funkcie rozbor_dna_s_modlitbou()...\n", nazov_modlitby(_global_modlitba), nazov_modlitby(modlitba));

		if (!isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY)) {
			Log("changing _global_modlitba to backup_global_modlitba...\n");
			// 2017-11-15: historical note: predpokladam, ze aj _global_modlitba je prve/druhe vespery, v _global_prve_vespery su spravne udaje (podobne kompletorium)
			// currently changed due to fixing problems of hyperlinks in first vespers
			_global_modlitba = backup_global_modlitba; // restore this value due to generating hyperlinks in _export_link_helper()
			// maybe also restoring value for _global_poradie_svaty would be necessary
		}
		else {
			Log("no change of _global_modlitba\n...");
		}

		LOG_ciara;
		showPrayer(typ, modlitba, SHOW_TEMPLAT_MODLITBA, aj_navigacia);
		LOG_ciara;
		Log("...po návrate zo showPrayer(_global_modlitba == %s) vo funkcii rozbor_dna_s_modlitbou().\n", nazov_modlitby(_global_modlitba));
	}// pre konkrétnu modlitbu

LABEL_s_modlitbou_DEALLOCATE:
	Log("Deallocating memory...\n");
	Log("_local_modl_prve_vespery_ptr\n"); free(_local_modl_prve_vespery_ptr);
	Log("_local_modl_1kompletorium_ptr\n"); free(_local_modl_1kompletorium_ptr);
	Log("_local_modl_vespery_ptr\n"); free(_local_modl_vespery_ptr);
	Log("_local_modl_kompletorium_ptr\n"); free(_local_modl_kompletorium_ptr);
	Log("...done.\n");
	Log("-- rozbor_dna_s_modlitbou(int, int, int, int): ret == %d\n", ret);
} // rozbor_dna_s_modlitbou()

void showAllPrayers(short int typ, short int den, short int mesiac, short int rok, short int poradie_svaty) {
	// v cykle volám showPrayer() pre všetky modlitby
	short int modlitba, _local_modlitba = _global_modlitba, _local_linky = _global_linky;
	short int opt_3 = (short int)_global_opt[OPT_3_SPOLOCNA_CAST]; // can be short due to OPT_3_SPOLOCNA_CAST does not contain bitwise options
	static unsigned long long opt_1 = _global_opt[OPT_1_CASTI_MODLITBY]; // backup pôvodnej hodnoty; parameter o1 (_global_opt 1) pre modlitbu cez deň (doplnková psalmódia)
	short int modlitba_max = MODL_KOMPLETORIUM; // až po ktorú modlitbu zobraziť

	Log("showAllPrayers(%d, %s, %d, %d) -- začiatok...\n", den, nazov_mesiaca(mesiac - 1), rok, poradie_svaty);
	// Log("_global_den: \n");
	// Log(_global_den);

	// top stránky
	Export("\n" HTML_A_NAME_BEGIN "\"top\">" HTML_A_END);

	// úvodná navigácia
	if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_NAVIGATION)) {
		ExportHtmlComment("navigácia začiatok");

		_export_rozbor_dna_buttons_dni(EXPORT_DNA_JEDEN_DEN_LOCAL, NIE);

		// najprv dni, potom modlitby
		Export("<" HTML_TABLE ">\n");
		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		_global_linky = NIE;
		_export_rozbor_dna_buttons(EXPORT_DNA_JEDEN_DEN_LOCAL, _global_poradie_svaty, NIE, ANO);
		_global_linky = _local_linky;

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");
		Export(HTML_TABLE_END "\n");
	}

	// pre sobotnú spomienku panny márie nezobrazuj vešpery ani kompletórium -- ináč to hádzalo chybu v _rozbor_dna_s_modlitbou(); if ((poradie_svateho == PORADIE_PM_SOBOTA) && (_global_den.denvt == DEN_SOBOTA) && ((modlitba == MODL_VESPERY) || (modlitba == MODL_KOMPLETORIUM)))
	if (poradie_svaty == PORADIE_PM_SOBOTA) {
		modlitba_max = MODL_POPOLUDNI;
	}
	else {
		modlitba_max = POCET_PORADIE_MODLITIEB_SHORT;
	}

	Log("showAllPrayers().isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY) == %d...\n", isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY));

	if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTON_PRVE_VESPERY)) {

		short int smer = _global_den_smer_override;

		Log("showAllPrayers().smer == %d...\n", smer);

		if (JE_PORADIE_SVATY_OK(poradie_svaty)) {
			smer = (smer > _global_svaty_i_smer_override(poradie_svaty)) ? _global_svaty_i_smer_override(poradie_svaty) : smer;

			Log("showAllPrayers().smer == %d...\n", smer);
		}

		if ((
			// č. 11: slávnosti su zvlášť význačnými dňami. ich slávenie sa začína prvými vešperami v predchádzajúci deň
			(smer < 5)
			// č. 13: sviatky sa slávia v rozsahu jedného dňa, a preto nemajú prvé vešpery, ak len nejde o sviatky Pána, ktoré pripadajú na Cezročnú neďelu a na nedeľu vo vianočnom období a nahradzujú nedeľňajšiu liturgiu hodín
			|| ((smer == 5) && (_global_den.denvt == DEN_NEDELA) && ((_global_den.litobd == OBD_CEZ_ROK) || je_vianocne(_global_den.litobd)))
			// nedeľa
			|| (_global_den.denvt == DEN_NEDELA)
			// č. 61
			|| (
			((_global_den.litobd == OBD_VELKONOCNA_OKTAVA) && (_global_den.denvt == DEN_SOBOTA)) // 2. velkonocna nedela
				|| ((_global_den.mesiac - 1 == MES_DEC) && (_global_den.den == 25)) // ked narodenie pana pripadne na pondelok, tak prve vespery maju prednost pred 4. adventnou nedelou; napr. rok 2000
				)
			)
			&& !(
				// a nie je to špeciálny deň
			((_global_den.denvr <= VELKONOCNA_NEDELA + 6) && (_global_den.denvr >= KVETNA_NEDELA + 1)) // všedné dni svätého týždňa počnúc pondelkom, veľkonočné trojdnie od veľkého piatka do veľkonočnej oktávy, soboty
				|| (_global_den.denvr == POPOLCOVA_STREDA) // Popolcová streda
				|| ((_global_den.denvt != DEN_NEDELA) && (_global_den.den == 2) && (_global_den.mesiac == MES_NOV + 1)) // 02NOV: Spomienka na všetkých verných zosnulých, ktorá nepadla na nedeľu
				)
			) {
			modlitba_max = POCET_PORADIE_MODLITIEB_LONG;
		}
	}

	Log("showAllPrayers().modlitba_max == %d...\n", modlitba_max);

	// cyklus pre všetky modlitby podľa poradie_modlitieb_short[] resp. poradie_modlitieb_long[]
	for (int i = 0; i <= modlitba_max; i++) {
		modlitba = (modlitba_max == POCET_PORADIE_MODLITIEB_LONG) ? poradie_modlitieb_long[i] : poradie_modlitieb_short[i];

		_global_modlitba = modlitba;

		Log("setting _global_opt[OPT_3_SPOLOCNA_CAST]...\n");
		_global_opt[OPT_3_SPOLOCNA_CAST] = opt_3; // potrebné nastaviť pôvodnú hodnotu, lebo sa niekde v rozbor_dna_s_modlitbou() upravuje

		if (je_modlitba_cez_den(modlitba)) {
			Log("<!-- MCD (%d, %llu) -->", modlitba, opt_1);
			if (((opt_1 & BIT_OPT_1_MCD_DOPLNKOVA) != BIT_OPT_1_MCD_DOPLNKOVA) && /* delenie trojkou so zvyškom */ (((_global_den.denvr + rok + modlitba) MOD 3) != 0)) {
				Log("<!-- MCD (%d): doplnková psalmódia -->", modlitba);
				Log("Pre option 1 nastavujem bit pre 'doplnkovú psalmódiu'\n");
				_global_opt[OPT_1_CASTI_MODLITBY] += BIT_OPT_1_MCD_DOPLNKOVA;
			}// zmena: použitie doplnkovej psalmódie
		}// mcd

		Log("spúšťam showPrayer(%s)->rozbor_dna_s_modlitbou() z funkcie showAllPrayers()...\n", nazov_modlitby(_global_modlitba));

		LOG_ciara;

		if (i > 0) {
			// odkaz na vrch stránky
			Export(HTML_P_CENTER);
			Export(HTML_A_HREF_BEGIN "\"#top\"%s>", optional_html_class_button);
			Export("%s", optional_html_button_begin);
			Export(HTML_UP_ARROW_CLASSIC "" STR_SPACE);
			Export((char *)html_text_batch_Back[_global_jazyk]);
			Export("%s", optional_html_button_end);
			Export(HTML_A_END);
			Export(HTML_P_END "\n");
			// oddelenie
			Export("\n" HTML_HR "\n");
		}

		rozbor_dna_s_modlitbou(typ, den, mesiac, rok, modlitba, poradie_svaty, /* aj_navigacia */ NIE, /* force_neanalyzuj_rok */ ANO);

		LOG_ciara;

		Log("...po návrate zo showPrayer(%s)->rozbor_dna_s_modlitbou() vo funkcii showAllPrayers().\n", nazov_modlitby(_global_modlitba));

		if (_global_opt[OPT_1_CASTI_MODLITBY] != opt_1) {
			_global_opt[OPT_1_CASTI_MODLITBY] = opt_1; // restore pôvodnej hodnoty
		}// obnovenie opt_1
	}// for(modlitba)

	// záverečná navigácia
	if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_NAVIGATION)) {
		ExportHtmlComment("navigácia koniec");

		Export("<" HTML_TABLE ">\n");
		Export("<" HTML_TABLE_ROW ">\n");
		ExportTableCell(HTML_TABLE_CELL);

		_global_linky = NIE;

		_export_rozbor_dna_buttons(EXPORT_DNA_JEDEN_DEN_LOCAL, _global_poradie_svaty, NIE, ANO);

		_global_linky = _local_linky;

		Export(HTML_TABLE_CELL_END "\n");
		Export(HTML_TABLE_ROW_END "\n");
		Export(HTML_TABLE_END "\n");

		// najprv modlitby, potom dni

		_export_rozbor_dna_buttons_dni(EXPORT_DNA_JEDEN_DEN_LOCAL, NIE);
	}

	_global_modlitba = _local_modlitba;
	Log("showAllPrayers(%d, %s, %d, %d) -- koniec\n", den, nazov_mesiaca(mesiac - 1), rok, poradie_svaty);
} // showAllPrayers();

// dostane 3 inty, spusti analyzuj_rok(); potom spusti _export_rozbor_dna();
void rozbor_dna(short int den, short int mesiac, short int rok) {
	short int ret;
	Log("-- rozbor_dna(int, int, int): begin (%d. %d. %d)\n", den, mesiac, rok);
	_struct_den_mesiac datum;
	datum.den = den;
	datum.mesiac = mesiac;
	Log("-- rozbor_dna(): spúšťam analyzuj_rok()...\n");
	analyzuj_rok(rok); // výsledok dá do _global_r
	Log("-- rozbor_dna(): analyzuj_rok() skončila.\n");

	Log("-- rozbor_dna(): spúšťam _rozbor_dna(s dvoma parametrami)...\n");
	ret = _rozbor_dna(datum, rok);
	if (ret == FAILURE) {
		Log("_rozbor_dna() returned FAILURE, so...\n");
		Log("-- rozbor_dna(int, int, int): uncomplete end\n");
		return;
	}
	Log("-- rozbor_dna(): _rozbor_dna(s dvoma parametrami) skončila.\n");

	Log("-- rozbor_dna(): spúšťam _export_rozbor_dna(EXPORT_DNA_JEDEN_DEN)...\n");
	_export_rozbor_dna(EXPORT_DNA_JEDEN_DEN);
	Log("-- rozbor_dna(): _export_rozbor_dna(EXPORT_DNA_JEDEN_DEN) skončila.\n");

	Log("-- rozbor_dna(int, int, int): end (%d. %d. %d)\n", den, mesiac, rok);
} // rozbor_dna()

// dostane cislo mesiaca (1--12) a rok, spusti analyzuj_rok(); potom pre vsetky dni spusti _rozbor_dna();
void rozbor_mesiaca(short int mesiac, short int rok, short int typ_exportu = EXPORT_DNA_VIAC_DNI) {
	Log("-- rozbor_mesiaca(%d/%d): začiatok\n", mesiac, rok);
	_struct_den_mesiac datum;
	datum.mesiac = mesiac;
	short int som_v_tabulke = ANO; // či sa používa tabuľka; bežne pre web áno, pre export pre mobilné zariadenia [export_monthly_druh >= 3] netreba tabuľku
	short int typ;

	if ((typ_exportu != EXPORT_DNA_VIAC_DNI_TXT) && (typ_exportu != EXPORT_DNA_XML)) {
		if (!isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_MESIAC_RIADOK)) {
			Log("-- EXPORT_DNA_VIAC_DNI --\n");
			typ = EXPORT_DNA_VIAC_DNI;
		}
		else {
			Log("-- EXPORT_DNA_VIAC_DNI_SIMPLE --\n");
			typ = EXPORT_DNA_VIAC_DNI_SIMPLE;
		}
	}
	else {
		typ = typ_exportu;
	}

	if (PODMIENKA_JE_BATCH_MODE_MONTHLY__AND__PLAIN_EXPORT) {
		som_v_tabulke = NIE;
		Log("-- rozbor_mesiaca: keďže sme v _global_opt_batch_monthly == ANO a export_monthly_druh (%d) > 2, nebudeme exportovať tabuľku...\n", export_monthly_druh);
	}
	if ((typ == EXPORT_DNA_VIAC_DNI_TXT) || (typ == EXPORT_DNA_XML)) {
		som_v_tabulke = NIE;
		Log("-- _export_rozbor_dna_buttons(typ == %d): kvôli typu nebudeme exportovať tabuľku...\n", typ);
	}

	analyzuj_rok(rok); // výsledok dá do _global_r

	if (som_v_tabulke == ANO) {
		Export("\n" HTML_LINE_BREAK);
		Export("<" HTML_TABLE ">\n");
	}

	for (datum.den = 1; datum.den <= pocet_dni[mesiac - 1]; datum.den++) {
		Log("-- rozbor_mesiaca: volám _rozbor_dna() pre deň %d...\n", datum.den);
		if (typ == EXPORT_DNA_VIAC_DNI_TXT) {
			Export("\n");
#ifdef NIELEN_PRE_PETA_ZIMENA
			Export((char *)html_text_mesiac[_global_jazyk]);
			Export(" == %d, ", mesiac);
			Export((char *)html_text_den[_global_jazyk]);
			Export(" == %d ", datum.den);
#endif
			Export("expt"); // PZ: $rkc // 2011-02-03
			Export("[%02d%02d]", datum.den, mesiac);
			Export("=");
		}

		_rozbor_dna(datum, rok);

		Log("-- rozbor_mesiaca: nasleduje _export_rozbor_dna() pre deň %d...\n", datum.den);

		_export_rozbor_dna(typ);

		Log("-- rozbor_mesiaca: deň %d skončil.\n", datum.den);
	}// for datum.den

	if (som_v_tabulke == ANO) {
		Export("\n");
		Export(HTML_TABLE_END "\n");
	}

	Log("-- rozbor_mesiaca(%d/%d): koniec\n", mesiac, rok);
} // rozbor_mesiaca();

void log_pom_OPT(void) {
	short int i;
	for (i = 0; i < POCET_GLOBAL_OPT; i++) {
		Log("opt %d == `%s' (%llu)\n", i, pom_OPT[i], _global_opt[i]);
	}
} // log_pom_OPT()

void log_pom_FORCE_OPT(void) {
	short int i;
	for (i = 0; i < POCET_GLOBAL_OPT; i++) {
		Log("force_opt %d == `%s' (%llu)\n", i, pom_FORCE_OPT[i], _global_force_opt[i]);
	}
	for (i = 0; i < POCET_OPT_0_SPECIALNE; i++) {
		Log("force_opt[%d] %d == `%s'\n", OPT_0_SPECIALNE, i, pom_FORCE_OPT_0_SPECIALNE[i]);
	}
	for (i = 0; i < POCET_OPT_1_CASTI_MODLITBY; i++) {
		Log("force_opt[%d] %d == `%s'\n", OPT_1_CASTI_MODLITBY, i, pom_FORCE_OPT_1_CASTI_MODLITBY[i]);
	}
} // log_pom_FORCE_OPT()

void _rozparsuj_parametre_OPT_force(int option_opt, char pom_FORCE_OPT_opt[MAX_POCET_OPT][SMALL], unsigned long long _global_option_opt[MAX_POCET_OPT]) {
	short int i;
	short int aspon_jedna_nenulova;
	unsigned long long bit_value; // for option 6, decimal-place value
	double base = 2.0;

	if (option_opt == OPT_6_ALTERNATIVES_MULTI) {
		base = 10.0;
	}

	Log("_rozparsuj_parametre_OPT_force(%d) -- začiatok...\n", option_opt);

#ifndef LOG_PARAMS
	Log("_rozparsuj_parametre_OPT_force(): LOG_PARAMS is undefined, no LogParams() printed...\n");
#endif

	// option_opt force j (0, 1, 2, 4, 5, 6)
	// option_opt force j -- jednotlivé komponenty
	_global_force_opt[option_opt] = GLOBAL_OPTION_NULL;
	aspon_jedna_nenulova = NIE;
	for (i = 0; i < pocet_opt[option_opt]; i++) {
		if ((pom_FORCE_OPT_opt[i] == NULL) || (strlen(pom_FORCE_OPT_opt[i]) < 1)) {
			_global_option_opt[i] = GLOBAL_OPTION_NULL;
		}
		else {
			_global_option_opt[i] = atoi(pom_FORCE_OPT_opt[i]);
			aspon_jedna_nenulova = ANO;
		}
		LogParams("force_opt[%d][%d] == `%s' (%d)\n", option_opt, i, pom_FORCE_OPT_opt[i], _global_option_opt[i]);
	}// for i
	if (aspon_jedna_nenulova == ANO) {
		_global_force_opt[option_opt] = 0;
		// nastavenie _global_force_opt[option_opt] podľa jednotlivých bit-komponentov, ktoré sú nastavené v _global_option_opt[]
		for (i = 0; i < pocet_opt[option_opt]; i++) {
			bit_value = (long long)pow(base, i);
			LogParams("option_opt %d, i == %d; bit_value == %llu...\n", option_opt, i, bit_value);
			if (_global_option_opt[i] != GLOBAL_OPTION_NULL) {
				_global_force_opt[option_opt] += bit_value * _global_option_opt[i];
			}
			else if ((_global_opt[option_opt] & bit_value) == bit_value) {
				// ináč použi nastavenie z _global_opt (nie force)
				LogParams("použijem nastavenie z _global_opt[%d] (nie force)...\n", option_opt);
				_global_force_opt[option_opt] += bit_value;
			}
		}// for i
		LogParams("force_opt[%d] vyskladaná == %ld\n", option_opt, _global_force_opt[option_opt]);
	}
	LogParams("force_opt %d == `%s' (%d)\n", option_opt, pom_FORCE_OPT[option_opt], _global_force_opt[option_opt]);

	Log("_rozparsuj_parametre_OPT_force(%d) -- koniec.\n", option_opt);
} // _rozparsuj_parametre_OPT_force()

void _rozparsuj_parametre_OPT(void) {
	// rozparsovanie option parametrov
	short int i;
	short int opt_2_fn /* font name chooser */, opt_2_fs /* font size chooser */;

	Log("_rozparsuj_parametre_OPT() -- začiatok...\n");

#ifndef LOG_PARAMS
	Log("_rozparsuj_parametre_OPT(): LOG_PARAMS is undefined, no LogParams() printed...\n");
#endif

	LogParams("options...\n");

	// option 0
	if ((pom_OPT[OPT_0_SPECIALNE] == NULL) || (strlen(pom_OPT[OPT_0_SPECIALNE]) < 1)) {
		_global_opt[OPT_0_SPECIALNE] = GLOBAL_OPTION_NULL;
	}
	else {
		_global_opt[OPT_0_SPECIALNE] = atoui64(pom_OPT[OPT_0_SPECIALNE]);
	}
	LogParams("opt %d == `%s' (%llu)\n", OPT_0_SPECIALNE, pom_OPT[OPT_0_SPECIALNE], _global_opt[OPT_0_SPECIALNE]);

	// option 1
	if ((pom_OPT[OPT_1_CASTI_MODLITBY] == NULL) || (strlen(pom_OPT[OPT_1_CASTI_MODLITBY]) < 1)) {
		_global_opt[OPT_1_CASTI_MODLITBY] = GLOBAL_OPTION_NULL;
	}
	else {
		_global_opt[OPT_1_CASTI_MODLITBY] = atoui64(pom_OPT[OPT_1_CASTI_MODLITBY]);
	}
	LogParams("opt %d == `%s' (%llu)\n", OPT_1_CASTI_MODLITBY, pom_OPT[OPT_1_CASTI_MODLITBY], _global_opt[OPT_1_CASTI_MODLITBY]);

	// option 2
	if ((pom_OPT[OPT_2_HTML_EXPORT] == NULL) || (strlen(pom_OPT[OPT_2_HTML_EXPORT]) < 1)) {
		_global_opt[OPT_2_HTML_EXPORT] = GLOBAL_OPTION_NULL;
	}
	else {
		_global_opt[OPT_2_HTML_EXPORT] = atoui64(pom_OPT[OPT_2_HTML_EXPORT]);
	}
	LogParams("opt %d == `%s' (%llu)\n", OPT_2_HTML_EXPORT, pom_OPT[OPT_2_HTML_EXPORT], _global_opt[OPT_2_HTML_EXPORT]);

	// option 3
	i = atoi(pom_OPT[OPT_3_SPOLOCNA_CAST]);
	// predpokladam, ze tento parameter moze byt zadany eventualne cislom (teda retazcom, kt. hodnota pri konverzii na int je int, urcujuci opt_3
	if ((i > MODL_SPOL_CAST_NEBRAT) || (i <= 0)) {
		i = 0;
		// ide o znakovy retazec nekonvertovatelny na cislo
	}
	else {
		mystrcpy(pom_OPT[OPT_3_SPOLOCNA_CAST], nazov_spolc(i), SMALL);
		// ak je zadane cislo spravne, tak i bude spravny int a pom_OPT[OPT_3_SPOLOCNA_CAST] bude spravny char*
	}
	LogParams("opt %d: i == %d\n", OPT_3_SPOLOCNA_CAST, i);
	// make sense only if any string was set (because some language constants in nazov_spolc() may be empty
	if (strlen(pom_OPT[OPT_3_SPOLOCNA_CAST]) > 0) {
		while (i <= MODL_SPOL_CAST_NEBRAT) {
			if (equals(pom_OPT[OPT_3_SPOLOCNA_CAST], nazov_spolc(i))) {
				Log("setting _global_opt[OPT_3_SPOLOCNA_CAST]...\n");
				_global_opt[OPT_3_SPOLOCNA_CAST] = i;
				break;
			}
			i++;
		}
	}
	else {
		i = MODL_SPOL_CAST_NEBRAT + 1; // simulation of overflow in while
	}
	if (i > MODL_SPOL_CAST_NEBRAT) {
		Log("setting _global_opt[OPT_3_SPOLOCNA_CAST]...\n");
		_global_opt[OPT_3_SPOLOCNA_CAST] = MODL_SPOL_CAST_NEURCENA;
	}
	LogParams("opt %d == `%s' (%llu)\n", OPT_3_SPOLOCNA_CAST, pom_OPT[OPT_3_SPOLOCNA_CAST], _global_opt[OPT_3_SPOLOCNA_CAST]);

	// option 4
	if ((pom_OPT[OPT_4_OFFLINE_EXPORT] == NULL) || (strlen(pom_OPT[OPT_4_OFFLINE_EXPORT]) < 1)) {
		_global_opt[OPT_4_OFFLINE_EXPORT] = GLOBAL_OPTION_NULL;
	}
	else {
		_global_opt[OPT_4_OFFLINE_EXPORT] = atoui64(pom_OPT[OPT_4_OFFLINE_EXPORT]);
	}
	LogParams("opt %d == `%s' (%llu)\n", OPT_4_OFFLINE_EXPORT, pom_OPT[OPT_4_OFFLINE_EXPORT], _global_opt[OPT_4_OFFLINE_EXPORT]);

	// option 5
	if ((pom_OPT[OPT_5_ALTERNATIVES] == NULL) || (strlen(pom_OPT[OPT_5_ALTERNATIVES]) < 1)) {
		_global_opt[OPT_5_ALTERNATIVES] = GLOBAL_OPTION_NULL;
	}
	else {
		_global_opt[OPT_5_ALTERNATIVES] = atoui64(pom_OPT[OPT_5_ALTERNATIVES]);
	}
	LogParams("opt %d == `%s' (%llu)\n", OPT_5_ALTERNATIVES, pom_OPT[OPT_5_ALTERNATIVES], _global_opt[OPT_5_ALTERNATIVES]);

	// option 6
	if ((pom_OPT[OPT_6_ALTERNATIVES_MULTI] == NULL) || (strlen(pom_OPT[OPT_6_ALTERNATIVES_MULTI]) < 1)) {
		_global_opt[OPT_6_ALTERNATIVES_MULTI] = GLOBAL_OPTION_NULL;
	}
	else {
		_global_opt[OPT_6_ALTERNATIVES_MULTI] = atoui64(pom_OPT[OPT_6_ALTERNATIVES_MULTI]);
	}
	LogParams("opt %d == `%s' (%llu)\n", OPT_6_ALTERNATIVES_MULTI, pom_OPT[OPT_6_ALTERNATIVES_MULTI], _global_opt[OPT_6_ALTERNATIVES_MULTI]);

	// force options
	Log("force options...\n");
	// postupne prechádzam jednotlivé bitové komponenty force a vyskladávam z nich celkovú jednu hodnotu; ak daná bitová hodnota nie je naplnená, použijem hodnotu z ne-force option-bitového komponentu

	// option force 0
	_rozparsuj_parametre_OPT_force(OPT_0_SPECIALNE, pom_FORCE_OPT_0_SPECIALNE, _global_opt_0_specialne);

	// option force 1
	_rozparsuj_parametre_OPT_force(OPT_1_CASTI_MODLITBY, pom_FORCE_OPT_1_CASTI_MODLITBY, _global_opt_1_casti_modlitby);

	// option force 2
	_rozparsuj_parametre_OPT_force(OPT_2_HTML_EXPORT, pom_FORCE_OPT_2_HTML_EXPORT, _global_opt_2_html_export);

	// option force 3
	i = atoi(pom_FORCE_OPT[OPT_3_SPOLOCNA_CAST]);
	// predpokladam, ze tento parameter moze byt zadany eventualne cislom (teda retazcom, kt. hodnota pri konverzii na int je int, urcujuci opt_3
	if ((i > MODL_SPOL_CAST_NEBRAT) || (i <= 0)) {
		i = 0;
		// ide o znakovy retazec nekonvertovatelny na cislo
	}
	else {
		mystrcpy(pom_FORCE_OPT[OPT_3_SPOLOCNA_CAST], nazov_spolc(i), SMALL);
		// ak je zadane cislo spravne, tak i bude spravny int a pom_FORCE_OPT[OPT_3_SPOLOCNA_CAST] bude spravny char*
	}
	LogParams("opt %d: i == %d\n", OPT_3_SPOLOCNA_CAST, i);
	// make sense only if any string was set (because some language constants in nazov_spolc() may be empty
	if (strlen(pom_FORCE_OPT[OPT_3_SPOLOCNA_CAST]) > 0) {
		while (i <= MODL_SPOL_CAST_NEBRAT) {
			LogParams("force_opt %d: (in while)i == %d; %s\n", OPT_3_SPOLOCNA_CAST, i, nazov_spolc(i));
			if (equals(pom_FORCE_OPT[OPT_3_SPOLOCNA_CAST], nazov_spolc(i))) {
				_global_force_opt[OPT_3_SPOLOCNA_CAST] = i;
				break;
			}
			i++;
		}
	}
	else {
		i = MODL_SPOL_CAST_NEBRAT + 1; // simulation of overflow in while
	}
	if (i > MODL_SPOL_CAST_NEBRAT) {
		_global_force_opt[OPT_3_SPOLOCNA_CAST] = GLOBAL_OPTION_NULL;
	}
	LogParams("force_opt %d == `%s' (%ld)\n", OPT_3_SPOLOCNA_CAST, pom_FORCE_OPT[OPT_3_SPOLOCNA_CAST], _global_force_opt[OPT_3_SPOLOCNA_CAST]);

	// option force 4
	_rozparsuj_parametre_OPT_force(OPT_4_OFFLINE_EXPORT, pom_FORCE_OPT_4_OFFLINE_EXPORT, _global_opt_4_offline_export);

	// option force 5
	_rozparsuj_parametre_OPT_force(OPT_5_ALTERNATIVES, pom_FORCE_OPT_5_ALTERNATIVES, _global_opt_5_alternatives);

	// option force 6
	_rozparsuj_parametre_OPT_force(OPT_6_ALTERNATIVES_MULTI, pom_FORCE_OPT_6_ALTERNATIVES_MULTI, _global_opt_6_alternatives_multi);

	// kontrolujeme, či niektoré z options nie sú GLOBAL_OPTION_NULL a zároveň prípadne nastaví na default podľa jazyka
	// doplnené opt_0 až opt_4 force (okrem opt_3); default sa nastavuje podľa "ne-force" verzií; CFG_OPTION1_DEFAULT..CFG_OPTION5_DEFAULT doplnené v myconf.h
	// aj pre hodnotu 3 sa vykonáva
	LogParams("pre všetky _global_opt[] kontrolujem, či nie sú GLOBAL_OPTION_NULL => ak áno, nastavím príslušnú hodnotu na CFG_OPTION_DEFAULT()...\n");
	for (i = 0; i < POCET_GLOBAL_OPT; i++) {
		LogParams("i == %d...\n", i);
		if (_global_opt[i] == GLOBAL_OPTION_NULL) {
			_global_opt[i] = CFG_OPTION_DEFAULT(i);
			LogParams("Keďže bolo _global_opt[%d] == GLOBAL_OPTION_NULL, nastavujem na CFG_OPTION_DEFAULT(%d) == `%llu'...\n", i, i, CFG_OPTION_DEFAULT(i));
		}
	}// for i

	LogParams("pre všetky _global_force_opt[] kontrolujem, či nie sú GLOBAL_OPTION_NULL => ak áno, nastavím príslušnú hodnotu na _global_opt[]...\n");
	for (i = 0; i < POCET_GLOBAL_OPT; i++) {
		LogParams("i == %d...\n", i);
		if (_global_force_opt[i] == GLOBAL_OPTION_NULL) {
			_global_force_opt[i] = _global_opt[i];
			LogParams("Keďže bolo _global_force_opt[%d] == GLOBAL_OPTION_NULL, nastavujem na _global_opt[%d] == `%llu'...\n", i, i, _global_force_opt[i]);
		}
		else {
			_global_opt[i] = _global_force_opt[i];
			LogParams("Force; do _global_opt[%d] priraďujem _global_force_opt[%d] (`%ld')...\n", i, i, _global_force_opt[i]);
		}
		// špeciálna úprava: zohľadnenie defaultu z config súboru pre 4. bit (BIT_OPT_2_FONT_NAME_CHOOSER)
		if (i == OPT_2_HTML_EXPORT) {
			// teraz platí, že _global_opt[i] == _global_force_opt[i], takže stačí testovať jednu z nich, ale upraviť treba obe hodnoty

			// špeciálne: pre 4. bit (BIT_OPT_2_FONT_NAME_CHOOSER)
			LogParams("špeciálna úprava: zohľadnenie defaultu z config súboru pre 4. bit (BIT_OPT_2_FONT_NAME_CHOOSER)\n");
			opt_2_fn = ((CFG_OPTION_DEFAULT(i) & BIT_OPT_2_FONT_NAME_CHOOSER) == BIT_OPT_2_FONT_NAME_CHOOSER) ? ANO : NIE;
			if ((isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_FONT_NAME_CHOOSER)) && (opt_2_fn == NIE)) {
				LogParams("odstraňujem z _global_opt aj _global_force_opt[%d] bit pre BIT_OPT_2_FONT_NAME_CHOOSER\n...", i);
				_global_force_opt[i] -= BIT_OPT_2_FONT_NAME_CHOOSER;
				_global_opt[i] -= BIT_OPT_2_FONT_NAME_CHOOSER;
			}
			else if ((!isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_FONT_NAME_CHOOSER)) && (opt_2_fn == ANO)) {
				LogParams("pridávam do _global_force_opt[%d] bit pre BIT_OPT_2_FONT_NAME_CHOOSER\n...", i);
				_global_force_opt[i] += BIT_OPT_2_FONT_NAME_CHOOSER;
				_global_opt[i] += BIT_OPT_2_FONT_NAME_CHOOSER;
			}
			else {
				LogParams("nie je potrebné upravovať ani _global_opt ani _global_force_opt[%d].\n", i);
			}
			LogParams("po potenciálnej úprave: _global_opt aj _global_force_opt[%d] == `%ld'...\n", i, _global_force_opt[i]);

			// špeciálne: pre 5. bit (BIT_OPT_2_FONT_SIZE_CHOOSER)
			LogParams("špeciálna úprava: zohľadnenie defaultu z config súboru pre 5. bit (BIT_OPT_2_FONT_SIZE_CHOOSER)\n");
			opt_2_fs = ((CFG_OPTION_DEFAULT(i) & BIT_OPT_2_FONT_SIZE_CHOOSER) == BIT_OPT_2_FONT_SIZE_CHOOSER) ? ANO : NIE;
			if ((isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_FONT_SIZE_CHOOSER)) && (opt_2_fs == NIE)) {
				LogParams("odstraňujem z _global_opt aj _global_force_opt[%d] bit pre BIT_OPT_2_FONT_SIZE_CHOOSER\n...", i);
				_global_force_opt[i] -= BIT_OPT_2_FONT_SIZE_CHOOSER;
				_global_opt[i] -= BIT_OPT_2_FONT_SIZE_CHOOSER;
			}
			else if ((!isGlobalOptionForce(OPT_2_HTML_EXPORT, BIT_OPT_2_FONT_SIZE_CHOOSER)) && (opt_2_fs == ANO)) {
				LogParams("pridávam do _global_force_opt[%d] bit pre BIT_OPT_2_FONT_SIZE_CHOOSER\n...", i);
				_global_force_opt[i] += BIT_OPT_2_FONT_SIZE_CHOOSER;
				_global_opt[i] += BIT_OPT_2_FONT_SIZE_CHOOSER;
			}
			else {
				LogParams("nie je potrebné upravovať ani _global_opt ani _global_force_opt[%d].\n", i);
			}
			LogParams("po potenciálnej úprave: _global_opt aj _global_force_opt[%d] == `%llu'...\n", i, _global_force_opt[i]);

		}// (i == OPT_2_HTML_EXPORT)
	}// for i

	LogParams("=== Po potenciálnych úpravách (nastavenie default hodnôt podľa jazyka) ===\n");

#ifdef LOG_PARAMS
	log_pom_OPT();
	log_pom_FORCE_OPT();
#endif

	// setting up global strings for HTML export
	if ((isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_DO_NOT_USE_BUTTON)) || PODMIENKA_JE_BATCH_MODE_MONTHLY__AND__PLAIN_EXPORT) {
		// use old behaviour with <a class="button"> for 'plain export' (batch mode) or when explicitly requested (BIT_OPT_4_DO_NOT_USE_BUTTON)
		mystrcpy(optional_html_button_begin, STR_EMPTY, MAX_STR);
		mystrcpy(optional_html_button_prayer_begin, STR_EMPTY, MAX_STR);
		mystrcpy(optional_html_button_end, STR_EMPTY, MAX_STR);
		mystrcpy(optional_html_class_button, STR_EMPTY, MAX_STR); // mystrcpy(optional_html_class_button, " " HTML_CLASS_BUTTON, MAX_STR);
		mystrcpy(optional_html_line_break, HTML_LINE_BREAK, MAX_STR);
	}
	else {
		// use new behaviour - display <a> element like button
		mystrcpy(optional_html_button_begin, HTML_BUTTON_BEGIN, MAX_STR);
		mystrcpy(optional_html_button_prayer_begin, HTML_BUTTON_PRAYER_BEGIN, MAX_STR);
		mystrcpy(optional_html_button_end, HTML_BUTTON_END, MAX_STR);
		mystrcpy(optional_html_class_button, STR_EMPTY, MAX_STR);
		mystrcpy(optional_html_line_break, STR_EMPTY, MAX_STR);
	}

	Log("_rozparsuj_parametre_OPT() -- koniec.\n");
} // _rozparsuj_parametre_OPT()

void _rozparsuj_parametre_DEN_MESIAC_ROK(char *den, char *mesiac, char *rok, char *modlitba, short int &local_den, short int &local_mesiac, short int &local_rok, short int& local_modlitba) {
	// rozparsovanie parametrov pre deň, mesiac a rok
	Log("_rozparsuj_parametre_DEN_MESIAC_ROK(%s, %s, %s, %s): begin...\n", den, mesiac, rok, modlitba);

	local_den = atoden(den); // vrati VSETKY_DNI, resp. atoi(den)
	Log("den == `%s' (%d)\n", den, local_den);
	local_mesiac = atomes(mesiac); // bude to 0--11, resp. VSETKY_MESIACE resp. UNKNOWN_MESIAC
	Log("mes == `%s' (%d)\n", mesiac, local_mesiac);
	local_rok = atoi(rok); // vrati 0 v pripade chyby; alebo int
	Log("rok == `%s' (%d)\n", rok, local_rok);

	if (query_type == PRM_STATIC_TEXT) {
		// rozparsovanie parametra static_text
		Log("volanie atoStaticText() z _rozparsuj_parametre_DEN_MESIAC_ROK()...\n");
		local_rok = atoStaticText(rok);
		Log("st == `%s' (%d)\n", rok, local_rok);
	}

	// rozparsovanie parametra modlitba
	Log("volanie atomodlitba() z _main_rozbor_dna()...\n");
	local_modlitba = atomodlitba(modlitba);

	_global_modlitba = local_modlitba;
	Log("modl == %s (%d, %s) -- priradene do _global_modlitba\n", modlitba, local_modlitba, nazov_modlitby(local_modlitba));

	Log("_rozparsuj_parametre_DEN_MESIAC_ROK(): end.\n");
} // _rozparsuj_parametre_DEN_MESIAC_ROK()

void _export_buttons_rok_prev_next(short int r, char action[MAX_STR], char pom2[MAX_STR]) {
	Log("_export_buttons_rok_prev_next(%d, %s, %s) -- začiatok\n", r, action, pom2);

	Export("<" HTML_TABLE ">\n");
	Export("<" HTML_TABLE_ROW ">\n");
	// << predošlý rok -- button
	Export("<" HTML_TABLE_CELL ">");
	sprintf(action, "%s?%s=%s" HTML_AMPERSAND "%s=%s" HTML_AMPERSAND "%s=%s" HTML_AMPERSAND "%s=%d%s",
		script_name,
		STR_QUERY_TYPE, STR_PRM_DATUM,
		STR_DEN, STR_VSETKY_DNI,
		STR_MESIAC, STR_VSETKY_MESIACE,
		STR_ROK, r - 1,
		pom2);
	Export_HtmlForm(action);
	Export(HTML_FORM_INPUT_SUBMIT0 " title=\"%s %s %d\" value=\"" HTML_LEFT_ARROW " %d", html_button_predchadzajuci_[_global_jazyk], html_text_rok[_global_jazyk], r - 1, r - 1);

#ifdef DISPLAY_TEXT_PREV_NEXT_YEAR
	Export(" (");
	Export((char *)html_button_predchadzajuci_[_global_jazyk]);
	Export(" ");
	Export((char *)html_text_rok[_global_jazyk]);
	Export(")");
#endif

	Export("\"" HTML_FORM_INPUT_END "\n");
	Export("</form>\n");
	Export(HTML_TABLE_CELL_END "\n");

	// nasledujúci rok >> -- button
	Export("<" HTML_TABLE_CELL ">");
	sprintf(action, "%s?%s=%s" HTML_AMPERSAND "%s=%s" HTML_AMPERSAND "%s=%s" HTML_AMPERSAND "%s=%d%s",
		script_name,
		STR_QUERY_TYPE, STR_PRM_DATUM,
		STR_DEN, STR_VSETKY_DNI,
		STR_MESIAC, STR_VSETKY_MESIACE,
		STR_ROK, r + 1,
		pom2);
	Export_HtmlForm(action);
	Export(HTML_FORM_INPUT_SUBMIT0 " title=\"%s %s %d\" value=\"", html_button_nasledujuci_[_global_jazyk], html_text_rok[_global_jazyk], r + 1);

#ifdef DISPLAY_TEXT_PREV_NEXT_YEAR
	Export("(");
	Export((char *)html_button_nasledujuci_[_global_jazyk]);
	Export(" ");
	Export((char *)html_text_rok[_global_jazyk]);
	Export(") ");
#endif

	Export("%d " HTML_RIGHT_ARROW "\"" HTML_FORM_INPUT_END "\n", r + 1);
	Export("</form>\n");
	Export(HTML_TABLE_CELL_END "\n");

	// koniec buttonov
	Export(HTML_TABLE_ROW_END "\n");
	Export(HTML_TABLE_END "\n");

	Log("_export_buttons_rok_prev_next(%d, %s, %s) -- koniec\n", r, action, pom2);
}// _export_buttons_rok_prev_next()

void _export_buttons_mesiac_rok_prev_next(short int m, short int r, char pom2[MAX_STR], short int som_v_tabulke, char pom[MAX_STR]) {

	short int pm, pr; // pomocny mesiac, pomocny rok
	char str_month[SMALL] = STR_EMPTY;

	if (som_v_tabulke == ANO)
		Export("\n<" HTML_TABLE ">\n");
	else {
		Export("\n<div class=\"navm\">\n");
		Export(HTML_P_BEGIN"\n");
	}

	// nasledujú tlačidlá; doplnený "ten istý mesiac pred rokom", "ten istý mesiac o rok"
	if (som_v_tabulke == ANO) {
		Export("<" HTML_TABLE_ROW ">\n");
	}

	// predosly mesiac -- button
	pm = m; pr = r;
	if (m == 1) {
		pm = 12;
		pr = r - 1;
	}
	else {
		pm = m - 1;
	}
	if (_global_opt_batch_monthly == NIE) {
		sprintf(pom, HTML_LINK_CALL2,
			script_name,
			STR_QUERY_TYPE, STR_PRM_DATUM,
			STR_DEN, STR_VSETKY_DNI,
			STR_MESIAC, pm,
			STR_ROK, pr,
			pom2);
	}// if (_global_opt_batch_monthly == NIE)
	else {
		// najprv treba predlepiť adresár...
		if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE)
			sprintf(str_month, ".." STR_PATH_SEPARATOR_HTML "" DIRNAME_EXPORT_MONTH_SIMPLE "" STR_PATH_SEPARATOR_HTML, pr % 100, pm, nazov_mes[pm - 1]);
		else // EXPORT_DATE_FULL
			sprintf(str_month, ".." STR_PATH_SEPARATOR_HTML "" DIRNAME_EXPORT_MONTH_FULL "" STR_PATH_SEPARATOR_HTML, pr, pm, nazov_mesiaca_asci(pm - 1));
		// ... a potom celý reťazec s názvom súboru pre daný mesiac
		if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
			sprintf(pom, "%s" FILENAME_EXPORT_MONTH_SIMPLE ".htm", str_month, pr % 100, pm);
		}
		else {
			sprintf(pom, "%s" FILENAME_EXPORT_MONTH_FULL ".htm", str_month, pr, pm);
		}
	}
	Log("\treťazec pom == %s\n", pom);

	if (som_v_tabulke == ANO) {
		Export("<" HTML_TABLE_CELL ">");
		Export_HtmlForm(pom);
		Export(HTML_FORM_INPUT_SUBMIT0 " value=\"" HTML_LEFT_ARROW " %s\"" HTML_FORM_INPUT_END "\n", _vytvor_string_z_datumu(VSETKY_DNI, pm, pr, (_global_jazyk == JAZYK_HU) ? CASE_case : CASE_Case, LINK_DEN_MESIAC_ROK, NIE));
		Export("</form>\n");
		Export(HTML_TABLE_CELL_END "\n");
	}
	else {
		Export(HTML_A_HREF_BEGIN "\"%s\">" HTML_LEFT_ARROW " %s" HTML_A_END "\n", pom, _vytvor_string_z_datumu(VSETKY_DNI, pm, pr, (_global_jazyk == JAZYK_HU) ? CASE_case : CASE_Case, LINK_DEN_MESIAC_ROK, NIE));

		ExportNonbreakingSpace(); Export(STR_VERTICAL_BAR); ExportNonbreakingSpace(); Export("\n");
	}

	// nasledujuci mesiac -- button
	pm = m; pr = r;
	if (m == 12) {
		pm = 1;
		pr = r + 1;
	}
	else {
		pm = m + 1;
	}
	if (_global_opt_batch_monthly == NIE) {
		sprintf(pom, HTML_LINK_CALL2,
			script_name,
			STR_QUERY_TYPE, STR_PRM_DATUM,
			STR_DEN, STR_VSETKY_DNI,
			STR_MESIAC, pm,
			STR_ROK, pr,
			pom2);
	}// if (_global_opt_batch_monthly == NIE)
	else {
		// najprv treba predlepiť adresár...
		if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
			sprintf(str_month, ".." STR_PATH_SEPARATOR_HTML "" DIRNAME_EXPORT_MONTH_SIMPLE "" STR_PATH_SEPARATOR_HTML, pr % 100, pm, nazov_mes[pm - 1]);
		}
		else {
			// EXPORT_DATE_FULL
			sprintf(str_month, ".." STR_PATH_SEPARATOR_HTML "" DIRNAME_EXPORT_MONTH_FULL "" STR_PATH_SEPARATOR_HTML, pr, pm, nazov_mesiaca_asci(pm - 1));
		}
		// ... a potom celý reťazec s názvom súboru pre daný mesiac
		if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
			sprintf(pom, "%s" FILENAME_EXPORT_MONTH_SIMPLE ".htm", str_month, pr % 100, pm);
		}
		else {
			sprintf(pom, "%s" FILENAME_EXPORT_MONTH_FULL ".htm", str_month, pr, pm);
		}
	}
	Log("\treťazec pom == %s\n", pom);

	if (som_v_tabulke == ANO) {
		Export("<" HTML_TABLE_CELL ">");
		Export_HtmlForm(pom);
		Export(HTML_FORM_INPUT_SUBMIT0 " value=\"%s " HTML_RIGHT_ARROW "\"" HTML_FORM_INPUT_END "\n", _vytvor_string_z_datumu(VSETKY_DNI, pm, pr, (_global_jazyk == JAZYK_HU) ? CASE_case : CASE_Case, LINK_DEN_MESIAC_ROK, NIE));
		Export("</form>\n");
		Export(HTML_TABLE_CELL_END "\n");
	}
	else {
		Export(HTML_A_HREF_BEGIN "\"%s\">%s " HTML_RIGHT_ARROW "" HTML_A_END "\n", pom, _vytvor_string_z_datumu(VSETKY_DNI, pm, pr, (_global_jazyk == JAZYK_HU) ? CASE_case : CASE_Case, LINK_DEN_MESIAC_ROK, NIE));
	}

	if (som_v_tabulke == ANO) {
		Export(HTML_TABLE_ROW_END "\n");
	}
	else {
		Export(HTML_P_END "" HTML_DIV_END);
	}

	// ten istý mesiac pred rokom -- button
	pm = m;
	pr = r - 1;
	if (_global_opt_batch_monthly == NIE) {
		sprintf(pom, HTML_LINK_CALL2,
			script_name,
			STR_QUERY_TYPE, STR_PRM_DATUM,
			STR_DEN, STR_VSETKY_DNI,
			STR_MESIAC, pm,
			STR_ROK, pr,
			pom2);
	}// if (_global_opt_batch_monthly == NIE)
	else {
		mystrcpy(pom, STR_EMPTY, MAX_STR);
	}
	if (_global_opt_batch_monthly == NIE) {
		if (som_v_tabulke == ANO) {
			Export("<" HTML_TABLE_ROW ">\n");

			Export("<" HTML_TABLE_CELL ">\n");
			Export_HtmlForm(pom);
			Export(HTML_FORM_INPUT_SUBMIT0 " value=\"" HTML_LEFT_ARROW " %s\"" HTML_FORM_INPUT_END "\n", _vytvor_string_z_datumu(VSETKY_DNI, pm, pr, (_global_jazyk == JAZYK_HU) ? CASE_case : CASE_Case, LINK_DEN_MESIAC_ROK, NIE));

			Export("</form>\n");
			Export(HTML_TABLE_CELL_END "\n");
		}
		else {
			ExportNonbreakingSpace(); Export(STR_VERTICAL_BAR); ExportNonbreakingSpace(); Export("\n");
			//
			Export(HTML_A_HREF_BEGIN "\"%s\">" HTML_LEFT_ARROW " %s" HTML_A_END "\n", pom, _vytvor_string_z_datumu(VSETKY_DNI, pm, pr, (_global_jazyk == JAZYK_HU) ? CASE_case : CASE_Case, LINK_DEN_MESIAC_ROK, NIE));

			ExportNonbreakingSpace(); Export(STR_VERTICAL_BAR); ExportNonbreakingSpace(); Export("\n");
		}
	}

	// ten istý mesiac o rok -- button
	pm = m;
	pr = r + 1;
	if (_global_opt_batch_monthly == NIE) {
		sprintf(pom, HTML_LINK_CALL2,
			script_name,
			STR_QUERY_TYPE, STR_PRM_DATUM,
			STR_DEN, STR_VSETKY_DNI,
			STR_MESIAC, pm,
			STR_ROK, pr,
			pom2);
	}// if (_global_opt_batch_monthly == NIE)
	else {
		mystrcpy(pom, STR_EMPTY, MAX_STR);
	}
	if (_global_opt_batch_monthly == NIE) {
		if (som_v_tabulke == ANO) {
			Export("<" HTML_TABLE_CELL ">");
			Export_HtmlForm(pom);
			Export(HTML_FORM_INPUT_SUBMIT0 " value=\"%s " HTML_RIGHT_ARROW "\"" HTML_FORM_INPUT_END "\n", _vytvor_string_z_datumu(VSETKY_DNI, pm, pr, (_global_jazyk == JAZYK_HU) ? CASE_case : CASE_Case, LINK_DEN_MESIAC_ROK, NIE));

			Export("</form>\n");
			Export(HTML_TABLE_CELL_END "\n");
		}
		else {
			Export(HTML_A_HREF_BEGIN "\"%s\">%s " HTML_RIGHT_ARROW "" HTML_A_END "\n", pom, _vytvor_string_z_datumu(VSETKY_DNI, pm, pr, (_global_jazyk == JAZYK_HU) ? CASE_case : CASE_Case, LINK_DEN_MESIAC_ROK, NIE));

			ExportNonbreakingSpace(); Export(STR_VERTICAL_BAR); ExportNonbreakingSpace(); Export("\n");
		}
	}

	if (som_v_tabulke == ANO) {
		Export(HTML_TABLE_ROW_END "\n");
	}

	// koniec buttonov
	if (som_v_tabulke == ANO) {
		Export(HTML_TABLE_END "\n");
	}
} // _export_buttons_mesiac_rok_prev_next()

// dostane stringy (datum) + mozno dalsie striny (modlitba, dalsi_svaty), prekonvertuje ich a skontroluje ak je vsetko ok, 
// vykona _main_rozbor_dna(int, int, int) resp. _main_rozbor_mesiaca(int) resp. cely rok, 12krat rozbor_mesiaca(int)
#define ExportUDAJE	result = FAILURE; hlavicka_sidemenu(); if (!heading_written) {_export_heading("Rozbor dňa"); heading_written = 1;} Log("error: Nevhodne udaje\n"); Export("Nevhodné údaje: "); Export
void _main_rozbor_dna(short int typ, short int d, short int m, short int r, short int p, char *poradie_svaty) {
	short int heading_written = 0;
	char pom[MAX_STR];
	Log("-- _main_rozbor_dna(short int, short int, short int, short int, char *): begin (%d, %d, %d, %d, %s)\n", d, m, r, p, poradie_svaty);
	short int s;

	char pom2[MAX_STR];
	mystrcpy(pom, STR_EMPTY, MAX_STR);
	mystrcpy(pom2, STR_EMPTY, MAX_STR);
	char pom3[MAX_STR];
	mystrcpy(pom3, STR_EMPTY, MAX_STR);

	char action[MAX_STR];
	mystrcpy(action, STR_EMPTY, MAX_STR);

	short int som_v_tabulke = ANO; // či sa používa tabuľka; bežne pre web áno, pre export pre mobilné zariadenia [export_monthly_druh >= 3] netreba tabuľku

	if (PODMIENKA_JE_BATCH_MODE_MONTHLY__AND__PLAIN_EXPORT) {
		som_v_tabulke = NIE;
		Log("-- _main_rozbor_dna: keďže sme v _global_opt_batch_monthly == ANO a export_monthly_druh (%d) > 2, nebudeme exportovať tabuľku...\n", export_monthly_druh);
	}

	prilep_request_options(pom2, pom3);

	// rozparsovanie parametrov den, mesiac, rok, modlitba, svaty -- _rozparsuj_parametre_DEN_MESIAC_ROK()
	Log("/* rozparsovanie parametrov den, mesiac, rok, modlitba, svaty -- partially _rozparsuj_parametre_DEN_MESIAC_ROK() */\n");
	s = atoi(poradie_svaty); // ak je viac svatych, ktory z nich (1--MAX_POCET_SVATY)
	// zmysel majú len vstupy 1--MAX_POCET_SVATY
	if (s < 1) {
		s = UNKNOWN_PORADIE_SVATEHO;
	}
	if (s > PORADIE_PM_SOBOTA) {
		s = UNKNOWN_PORADIE_SVATEHO;
	}
	Log("sv == `%s' (upravené na %d)\n", poradie_svaty, s);

	_global_modlitba = p;
	Log("modl == %d (%s) -- priradene do _global_modlitba\n", p, nazov_modlitby(p));

	// kontrola údajov
	short int result = SUCCESS;
	// deň
	if (d < 0) {
		ExportUDAJE("chýba údaj o dni." HTML_LINE_BREAK);
	}
	else if (d == 0) {
		ExportUDAJE("deň = <" HTML_SPAN_BOLD ">%d" HTML_SPAN_END "." HTML_LINE_BREAK, d);
	}
	// mesiac
	if (m < 0) {
		ExportUDAJE("chýba údaj o mesiaci." HTML_LINE_BREAK);
	}
	else if (m == UNKNOWN_MESIAC) {
		ExportUDAJE("taký mesiac nepoznám (%d)." HTML_LINE_BREAK, m);
	}
	// rok
	if (r < 0) {
		ExportUDAJE("chýba údaj o roku." HTML_LINE_BREAK);
	}
	else if (r == 0) {
		ExportUDAJE("rok = <" HTML_SPAN_BOLD ">%d" HTML_SPAN_END "." HTML_LINE_BREAK, r);
	}

	// kontrola údajov ukončená, podľa nej pokračujeme ďalej
	if (result == FAILURE) {
		Log("/* teraz result == FAILURE */\n");
		if (query_type == PRM_XML) {
			// nothing to do
		}
		else {
			ALERT;
		}
		return;
	}

	// settings for sidemenu
	_struct_den_mesiac datum;
	datum.den = d;
	datum.mesiac = m + 1; // note that m is between 0--11

	_rozbor_dna_base(datum, r);

	hlavicka_sidemenu();

	Log("/* teraz result == SUCCESS */\n");

	if (m == VSETKY_MESIACE) {
		if (p != MODL_NEURCENA) {
			ExportUDAJE("pre viacero mesiacov zobrazenie modlitby nie je podporované\n");
			return;
		}// p != MODL_NEURCENA

		if (!isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_MESIAC_RIADOK)) {
			Log("/* teraz vypisujem heading, rok %d */\n", r);
			sprintf(pom, (char *)html_text_Rok_x[_global_jazyk], r);
			_export_heading_center(typ, pom);

			_export_buttons_rok_prev_next(r, action, pom2);

			Export(HTML_A_NAME_BEGIN"\"rok\">" HTML_A_END "\n");
			Export(HTML_P_CENTER"\n");
			// najprv vygenerujem zoznam liniek (mesiace)
			for (m = MES_JAN; m <= MES_DEC; m++) {
				Export(HTML_A_HREF_BEGIN "\"#mesiac%d\"><" HTML_SPAN_SMALLCAPS ">%s" HTML_SPAN_END "" HTML_A_END "" STR_SPACE "", m, nazov_Mesiaca(m));
				ExportNonbreakingSpace();
				Export("\n");
			}
			// teraz linku na #explain -- vysvetlivky

			Export(HTML_LINE_BREAK"<" HTML_SPAN_SMALL ">" HTML_A_HREF_BEGIN "\"#explain\">%s" HTML_A_END "" HTML_SPAN_END "\n", html_text_Vysvetlivky[_global_jazyk]);
			// napokon ciaru (kedysi tu bol element hr)
			Export(HTML_P_END "\n");
			Export(HTML_P_BEGIN"\n");
		}

		// teraz generujem jednotlive mesiace so vsetkymi dnami
		for (m = MES_JAN; m <= MES_DEC; m++) {
			if (!isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_MESIAC_RIADOK)) {
				Export("\n\n" HTML_A_NAME_BEGIN "\"mesiac%d\">" HTML_A_END, m);
				Export("\n" HTML_P_CENTER "<" HTML_SPAN_RED_BOLD "><" HTML_SPAN_SMALLCAPS ">%s" HTML_SPAN_END "" HTML_SPAN_END, nazov_Mesiaca(m));
				Export(" (" HTML_A_HREF_BEGIN "\"#rok\" " HTML_CLASS_SMALL ">%s %s" HTML_A_END ")" HTML_P_END "\n", HTML_UP_ARROW_CLASSIC, html_text_zoznam_mesiacov[_global_jazyk]);
			}
			rozbor_mesiaca(m + 1, r);
		}// for(m)

		vysvetlivky();

		if ((_global_linky == ANO) && (!isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_MESIAC_RIADOK))) {

			Export("\n");
			Export(HTML_LINE_BREAK);

			_export_buttons_rok_prev_next(r, action, pom2);
		}
	}// m == VSETKY_MESIACE
	else {// m != VSETKY_MESIACE
		// note that m is between 0--11 | for XML export heading is not produced
		m++;
		if (d == VSETKY_DNI) {
			if (p != MODL_NEURCENA) {
				ExportUDAJE("pre viacej dní zobrazenie modlitby nie je podporované\n");
				return;
			}
			Log("/* teraz vypisujem heading 1, mesiac %s, rok %d */\n", nazov_mesiaca(m - 1), r);

			if (prestupny(r)) {
				pocet_dni[MES_FEB] = 29;
			}
			else {
				pocet_dni[MES_FEB] = 28;
			}

			if (_global_opt_batch_monthly == NIE) {
				vytvor_global_link(VSETKY_DNI, VSETKY_MESIACE, r, LINK_DEN_MESIAC_ROK, NIE);
			}// if (_global_opt_batch_monthly == NIE)
			else {
				sprintf(_global_link, "%d", r);
			}// else if (_global_opt_batch_monthly == NIE)
			if (format_datumu[_global_jazyk] == FORMAT_DATUMU_ROK_MESIAC_DEN) {
				sprintf(pom, "%s. %s", _global_link, nazov_mesiaca(m - 1));
			}
			else {
				sprintf(pom, "%s %s", nazov_Mesiaca(m - 1), _global_link);
			}
			_export_heading_center(typ, pom);

			if (((_global_linky == ANO) && (!isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_MESIAC_RIADOK))) || ((_global_opt_batch_monthly == ANO) && (export_monthly_druh >= 2))) {
				_export_buttons_mesiac_rok_prev_next(m, r, pom2, som_v_tabulke, pom);
			}

			rozbor_mesiaca(m, r);

			vysvetlivky();

			if (((_global_linky == ANO) && (!isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_MESIAC_RIADOK))) || ((_global_opt_batch_monthly == ANO) && (export_monthly_druh >= 2))) {

				Export("\n");
				Export(HTML_LINE_BREAK);

				_export_buttons_mesiac_rok_prev_next(m, r, pom2, som_v_tabulke, pom);

			}
		}// d == VSETKY_DNI
		else {// d != VSETKY_DNI
			if (!kontrola_den_mesiac_rok(d, m, r)) {
				Log("/* teraz vypisujem heading 1, datum %d. %s %d */\n", d, nazov_mesiaca(m - 1), r);

				strcpy(pom, _vytvor_string_z_datumu(d, m, r, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
				_export_heading_center(typ, pom);

				if (p == MODL_NEURCENA) {

					rozbor_dna(d, m, r);

				}
				else {
					if (p == MODL_VSETKY) {

						analyzuj_rok(r);

						_rozbor_dna(datum, r, s);

						_global_vstup_den = d;
						_global_vstup_mesiac = m;
						_global_vstup_rok = r;
						_global_poradie_svaty = s;
						Log("_global_poradie_svaty == %d\n", _global_poradie_svaty);

						showAllPrayers(typ, d, m, r, s);
					}
					else {
						_global_vstup_den = d;
						_global_vstup_mesiac = m;
						_global_vstup_rok = r;
						_global_poradie_svaty = s;
						Log("_global_poradie_svaty == %d\n", _global_poradie_svaty);

						rozbor_dna_s_modlitbou(typ, d, m, r, p, s);
					}
				}
			}
		}// d != VSETKY_DNI
	}// m != VSETKY_MESIACE

	Log("-- _main_rozbor_dna(short int, short int, short int, short int, char *): end\n");
} // _main_rozbor_dna()

void _main_rozbor_dna_txt_xml(short int typ, short int d, short int m, short int r, short int p, char* poradie_svaty) {
	// na základe _main_rozbor_dna; textový export len pre RKC; XML napr. pre iOS
	short int heading_written = 0;
	char pom[MAX_STR];
	Log("-- _main_rozbor_dna_txt_xml(short int, short int, short int, short int, char *): begin (%d, %d, %d, %d, %s)\n", d, m, r, p, poradie_svaty);
	short int s;
	short int mi, t = EXPORT_DNA_DNES;

	char pom2[MAX_STR];
	mystrcpy(pom, STR_EMPTY, MAX_STR);
	mystrcpy(pom2, STR_EMPTY, MAX_STR);
	char pom3[MAX_STR];
	mystrcpy(pom3, STR_EMPTY, MAX_STR);

	// rozparsovanie parametrov den, mesiac, rok, modlitba, svaty -- _rozparsuj_parametre_DEN_MESIAC_ROK()
	Log("/* rozparsovanie parametrov den, mesiac, rok, modlitba, svaty -- partially _rozparsuj_parametre_DEN_MESIAC_ROK() */\n");
	s = atoi(poradie_svaty); // ak je viac svatych, ktory z nich (1--MAX_POCET_SVATY)
	// zmysel majú len vstupy 1--MAX_POCET_SVATY
	if (s < 1) {
		s = UNKNOWN_PORADIE_SVATEHO;
	}
	if (s > PORADIE_PM_SOBOTA) {
		s = UNKNOWN_PORADIE_SVATEHO;
	}
	Log("sv == `%s' (upravené na %d)\n", poradie_svaty, s);

	_global_modlitba = p;
	Log("modl == %d (%s) -- priradene do _global_modlitba\n", p, nazov_modlitby(p));

	// kontrola údajov, len pre TXT export (pre XML deň, mesiac, rok netreba)
	short int result = SUCCESS;
	if (typ == PRM_TXT) {
		// deň
		if (d < 0) {
			ExportUDAJE("chýba údaj o dni.\n");
		}
		else if (d == 0) {
			ExportUDAJE("deň = %d.\n", d);
		}
		// mesiac
		if (m < 0) {
			ExportUDAJE("chýba údaj o mesiaci.\n");
		}
		else if (m == UNKNOWN_MESIAC) {
			ExportUDAJE("taký mesiac nepoznám (%d).\n", m);
		}
		// rok
		if (r < 0) {
			ExportUDAJE("chýba údaj o roku.\n");
		}
		else if (r == 0) {
			ExportUDAJE("rok = %d.\n", r);
		}
	}

	// modlitba -> typ exportu
	if (typ == PRM_TXT) {
		t = EXPORT_DNA_VIAC_DNI_TXT;
	}
	else if (typ == PRM_XML) {
		t = EXPORT_DNA_XML;
	}

	// kontrola údajov ukončená, podľa nej pokračujeme ďalej
	if (result == FAILURE) {
		Log("/* teraz result == FAILURE */\n");
		if (query_type == PRM_XML) {
			// nothing to do
		}
		else {
			ALERT;
		}
		return;
	}

	Log("/* teraz result == SUCCESS */\n");

	if (m != UNKNOWN_MESIAC) {
		// note that m is between 0--11 | for XML export heading is not produced
		if (t != EXPORT_DNA_XML) {

			Export("<h2>");
			Export((char *)html_text_txt_export[_global_jazyk]);
			Export(": ");
			Export((char *)html_text_lit_kalendar[_global_jazyk]);
			Export(" ");

			if (m == VSETKY_MESIACE) {
				Export((char *)html_text_rok[_global_jazyk]);
				Export(" %d", r);
			}// if (m == VSETKY_MESIACE)
			else {
				if (d == VSETKY_DNI) {
					Export((char *)html_text_mesiac[_global_jazyk]);
				}
				else {
					Export((char *)html_text_den[_global_jazyk]);
					Export(" %d.", d);
					if (t != EXPORT_DNA_JEDEN_DEN) {
						t = EXPORT_DNA_JEDEN_DEN;
					}
				}
				Export(" %s", nazov_mesiaca(m));
				Export(" %d", r);
			}// else (m != VSETKY_MESIACE)
			Export("</h2>");
		}

		Export("\n");

		if (t == EXPORT_DNA_VIAC_DNI_TXT) {
			Export("<pre>");
		}

		// teraz generujem jednotlivé mesiace so všetkými dňami
		if (m == VSETKY_MESIACE) {
			for (mi = MES_JAN; mi <= MES_DEC; mi++) {
#ifdef NIELEN_PRE_PETA_ZIMENA
				Export("\n\n");
				Export((char *)html_text_mesiac[_global_jazyk]);
				Export(" == %d ", mi + 1);
				Export("(%s)\n", nazov_mesiaca(m));
#endif
				rozbor_mesiaca(mi + 1, r, t); // tam sa volá _rozbor_dna() a potom _export_rozbor_dna()
			}// for mi
		}// m == VSETKY_MESIACE
		else {// m != VSETKY_MESIACE
			// note that m is between 0--11 | for XML export heading is not produced
			m++;
			if (d == VSETKY_DNI) {
				if (prestupny(r)) {
					pocet_dni[MES_FEB] = 29;
				}
				else {
					pocet_dni[MES_FEB] = 28;
				}

				rozbor_mesiaca(m, r, t); // tam sa volá _rozbor_dna() a potom _export_rozbor_dna()
			}// d == VSETKY_DNI
			else {// d != VSETKY_DNI
				if (!kontrola_den_mesiac_rok(d, m, r)) {

					_struct_den_mesiac datum;
					datum.den = d;
					datum.mesiac = m;

					if (p == MODL_NEURCENA || p == MODL_VSETKY) {
						// ignore p == MODL_VSETKY

						// najprv, kopírujúc rozbor_dna(), musíme predplniť údaje o roku...
						Log("-- _main_rozbor_dna_txt_xml(): nasleduje analyzuj_rok() pre rok %d...\n", r);
						analyzuj_rok(r); // výsledok dá do _global_r
						Log("-- _main_rozbor_dna_txt_xml(): analyzuj_rok() pre rok %d skončil.\n", r);

						// teraz rozbor samotného dňa...
						_rozbor_dna(datum, r);

						Log("-- _main_rozbor_dna_txt_xml(): nasleduje _export_rozbor_dna() pre deň %d...\n", datum.den);
						_export_rozbor_dna(t);
						Log("-- _main_rozbor_dna_txt_xml(): deň %d skončil.\n", datum.den);

					}
					else {
						_global_vstup_den = d;
						_global_vstup_mesiac = m;
						_global_vstup_rok = r;
						_global_poradie_svaty = s;
						Log("_global_poradie_svaty == %d\n", _global_poradie_svaty);

						rozbor_dna_s_modlitbou(typ, d, m, r, p, s);
					}
				}
			}// d != VSETKY_DNI
		}// m != VSETKY_MESIACE

		// XML export -- export options
		if (t == EXPORT_DNA_XML) {
			xml_export_options_and_menu();
		}
		else {
			Export("\n");
		}
		if (t == EXPORT_DNA_VIAC_DNI_TXT) {
			Export("</pre>\n");
		}

	}// m != UNKNOWN_MESIAC
	else {// m == UNKNOWN_MESIAC

		if (typ == PRM_TXT) {
			Export("Číslo mesiaca: nezadaný alebo nepodporovaný vstup.\n");
		}
		// XML export -- export options (when no month's number was supplied)
		else if (t == EXPORT_DNA_XML) {
			xml_export_options_and_menu();
		}

	}// m != VSETKY_MESIACE

	Log("-- _main_rozbor_dna_txt_xml(short int, short int, short int, short int, char *): end\n");
}// _main_rozbor_dna_txt_xml()

struct tm _get_dnes(void) {
	time_t timer;
	struct tm dnes;

	// get current timestamp (date + time)
	// 2009-05-22: originaly here was: timer = time(NULL); 
	// some people use breviary also after midnight for the "previous" day (they want to complete the day prayers even after the midnight) => we are shifting the "real" date approx. 2 hours later
	// Pavel Kučera <teni@volny.cz> však poprosil, aby aj po polnoci ešte chvíľu bolo možné modliť sa kompletórium
	// posunuté na pol tretiu: má to hlbokú logiku: pravdepodobne nik sa -- hoci aj po polnoci -- nemodlí ofícium z nasledovného dňa => predsa opravené na 2.01
	// invitatórium by malo byť prvou rannou modlitbou po zobudení. 
	// myslím, že sú výnimočné prípady, že ľuda regulérne modliaci sa breviár vstávajú o jednej, o druhej v noci (čím začne ich nový deň).
	timer = time(NULL) - (time_t)(2.01 * 60 * 60);

	// converts date/time to structure
	dnes = *localtime(&timer);

	// modifiyng time_check structure with the data
	dnes.tm_mon = dnes.tm_mon + 1;
	dnes.tm_year = dnes.tm_year + 1900;
	dnes.tm_yday = dnes.tm_yday + 1;

	// !!! tmp if you want to simulate that TODAY is another date (from the past or future), simply modify this method
	// dnes.tm_mon = 5;
	// dnes.tm_mday = 13;

	return dnes;
} // _get_dnes()

// vypluje cely objednavaci formular, ktory obsahuje dnesny den, udaje o nom, linku nan, okienka pre den, mesiac, rok; okienko pre (analyzu) rok; okienko pre sviatok, ... a tak.
// pridaná možnosť priamo generovať modlitbu, preto sú vstupom aj dve premenné podobne ako je to v _main_rozbor_dna
void _main_dnes(char *modlitba, char *poradie_svaty) {
	short int s, p;
	// time_t timer;
	struct tm dnes;
	long jd_dnes;
	char pom[MAX_STR];

	Log("-- _main_dnes(char *, char *): begin (%s, %s)\n", modlitba, poradie_svaty);

	dnes = _get_dnes();

	// juliansky datum
	jd_dnes = JD(dnes.tm_mday, dnes.tm_mon, dnes.tm_year);

	// dnes.tm_wday == 0--6 (0==sunday, nedela)

	// settings for sidemenu
	// dalej rozoberiem den a vypisem vysledok
	_struct_den_mesiac datum;
	datum.den = dnes.tm_mday;
	datum.mesiac = dnes.tm_mon;
	analyzuj_rok(dnes.tm_year); // výsledok dá do _global_r

	_rozbor_dna_base(datum, dnes.tm_year);

	hlavicka_sidemenu();

	s = atoi(poradie_svaty); // ak je viac svatych, ktory z nich (1--MAX_POCET_SVATY)
	// zmysel majú len vstupy 1--MAX_POCET_SVATY
	if (s < 1) {
		s = UNKNOWN_PORADIE_SVATEHO;
	}
	if (s > PORADIE_PM_SOBOTA) {
		s = UNKNOWN_PORADIE_SVATEHO;
	}
	Log("sv == `%s' (upravené na %d)\n", poradie_svaty, s);

	// rozparsovanie parametra modlitba
	Log("volanie atomodlitba() z _main_dnes()...\n");
	p = atomodlitba(modlitba);

	_global_modlitba = p;
	Log("modl == %s (%d, %s) -- priradene do _global_modlitba\n", modlitba, p, nazov_modlitby(p));

	// vypis
	Log("now printing heading 1, date %d. %s %d [note: struct tm has tm_mon 1..12 while our constants are 0..11]\n", dnes.tm_mday, nazov_mesiaca(dnes.tm_mon - 1), dnes.tm_year);
	strcpy(pom, _vytvor_string_z_datumu(dnes.tm_mday, dnes.tm_mon, dnes.tm_year, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, LINK_DEN_MESIAC_ROK, NIE));
	_export_heading_center(query_type, pom);

	// výpis juliánskeho dátumu, len ak nie je určená modlitba 
	// výpis "Dnes je..." sa zobrazí len pri nastavení HTML_ZOBRAZIT_DNES_JE == 1
	if (_global_modlitba == MODL_NEURCENA) {
		if (HTML_ZOBRAZIT_DNES_JE == ANO) {
			Export((char *)html_text_dnes_je_atd[_global_jazyk],
				dnes.tm_yday,
#undef ZOBRAZ_JULIANSKY_DATUM
#ifdef ZOBRAZ_JULIANSKY_DATUM
				(char *)STR_EMPTY,
#else
				(char *)HTML_COMMENT_BEGIN,
#endif
				(_global_linky == ANO) ? cfg_http_address_default[_global_jazyk] : MESSAGE_FOLDER,
				FILE_JULIANSKY_DATUM,
				jd_dnes,
#ifdef ZOBRAZ_JULIANSKY_DATUM
				(char *)STR_EMPTY
#else
				(char *)HTML_COMMENT_END
#endif
			);
		}// if (HTML_ZOBRAZIT_DNES_JE == ANO)

		analyzuj_rok(dnes.tm_year);

		_rozbor_dna(datum, dnes.tm_year);

		_export_rozbor_dna(EXPORT_DNA_DNES);
	}
	else if (p == MODL_VSETKY) {

		analyzuj_rok(dnes.tm_year);

		_rozbor_dna(datum, dnes.tm_year);

		_global_vstup_den = datum.den;
		_global_vstup_mesiac = datum.mesiac;
		_global_vstup_rok = dnes.tm_year;
		_global_poradie_svaty = s;
		Log("_global_poradie_svaty = %d\n", _global_poradie_svaty);

		showAllPrayers(query_type, datum.den, datum.mesiac, dnes.tm_year, s);
	}
	else {
		// ak je určená modlitba, postupujeme rovnako ako v _main_rozbor_dna
		_global_vstup_den = datum.den;
		_global_vstup_mesiac = datum.mesiac;
		_global_vstup_rok = dnes.tm_year;
		_global_poradie_svaty = s;
		Log("_global_poradie_svaty = %d\n", _global_poradie_svaty);

		rozbor_dna_s_modlitbou(query_type, datum.den, datum.mesiac, dnes.tm_year, p, s);
	}

	Log("-- _main_dnes(char *, char *): end\n");

}// _main_dnes();

void _main_zaltar(char *den, char *tyzden, char *modlitba) {
	short int aj_navigacia = ANO;

	short int d, t, p;
	d = atodenvt(den);
	t = atoi(tyzden);
	if ((d < 0) || (d > 6) || (t < 1) || (t > 4)) {
		ALERT;
		Export("Nevhodné údaje:" HTML_LINE_BREAK "\n<ul>");
		// den
		if (equals(den, STR_EMPTY))
			Export("<li>chýba údaj o dni</li>\n");
		else if (d == DEN_UNKNOWN)
			Export("<li>deň = <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END "</li>\n", den);
		// tyzden
		if (equals(tyzden, STR_EMPTY))
			Export("<li>chýba údaj o týždni</li>\n");
		else if ((t < 1) || (t > 4))
			Export("<li>týždeň = <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END "</li>\n", tyzden);
		Export("</ul>\n");
		return;
	}
	p = atomodlitba(modlitba);
	if ((p == MODL_NEURCENA) || (p < MODL_INVITATORIUM) || (p > MODL_DRUHE_KOMPLETORIUM)) {
		Export("Nevhodné údaje: nie je určená modlitba (%s).\n", modlitba);
		return;
	}
	_global_modlitba = p;
	// vstupom pre showPrayer() je iba zakladny typ modlitby; zvysna informacia (ci ide o prve/druhe vespery/kompl.) sa uchova v premennej _global_modlitba
	if ((p == MODL_PRVE_VESPERY) || (p == MODL_DRUHE_VESPERY)) {
		p = MODL_VESPERY;
	}
	if ((p == MODL_PRVE_KOMPLETORIUM) || (p == MODL_DRUHE_KOMPLETORIUM)) {
		p = MODL_KOMPLETORIUM;
	}
	// ked nejde o nedelu, nema zmysel rozlisovat prve/druhe vespery/kompl.
	if (d != DEN_NEDELA) {
		if (p == MODL_VESPERY) {
			_global_modlitba = MODL_VESPERY;
		}
		if (p == MODL_KOMPLETORIUM) {
			_global_modlitba = MODL_KOMPLETORIUM;
		}
	}// nie je to nedela

	zaltar(d, t);

	Log("spustam showPrayer(%s)...\n", nazov_modlitby(_global_modlitba));

	// úprava aj_navigacia pre TTS = voice output
	if ((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT)) && (p != MODL_NEURCENA)) {
		Log("pre voice output upravujem aj_navigacia na NIE (lebo modlitba == %d)...\n", p);
		aj_navigacia = CIASTOCNE;
	}

	// predpokladam, ze aj _global_modlitba je prve/druhe vespery, v _global_prve_vespery su spravne udaje (podobne kompletorium)
	showPrayer(query_type, p, SHOW_TEMPLAT_MODLITBA, aj_navigacia);
}// _main_zaltar()

short int _main_liturgicke_obdobie(char *den, char *tyzden, char *modlitba, char *litobd, char *litrok) {
	short int aj_navigacia = ANO;

	short int d, t, p, lo, tz, poradie_svateho = 0, ret;
	char lr;
	short int jeSpolocnaCast = NIE;
	_struct_sc sc;

	Log("_main_liturgicke_obdobie(): začiatok...\n");

	lr = litrok[0];
	lo = atolitobd(litobd);
	d = atodenvt(den);
	t = atoi(tyzden);
	tz = TYZZAL(t); // ((t + 3) MOD 4) + 1;
	Log("lr == %c, lo == %d, d == %d, t == %d, tz == %d...\n", lr, lo, d, t, tz);

	// do budúcnosti treba riešiť niektoré špeciality, napr. adv. obd. II alebo vian. obd. II (dni určené dátumom); triduum a pod.

	if (lr > 'C' || lr < 'A') {
		ALERT;
		Export("Nevhodné údaje:" HTML_LINE_BREAK "\n<ul>");
		// tyzden
		if (equals(tyzden, STR_EMPTY)) {
			Export("<li>taký liturgický rok nemožno žiadať</li>\n");
		}
		else if ((t < 1) || (t > 4)) {
			Export("<li>týždeň = <" HTML_SPAN_BOLD ">%c" HTML_SPAN_END "</li>\n", lr);
		}
		Export("</ul>\n");
		return FAILURE;
	}

	Log("nastavenie p (modlitba == %s)...\n", modlitba);
	p = atomodlitba(modlitba);
	if ((p == MODL_NEURCENA) || (p < MODL_INVITATORIUM) || (p > MODL_DRUHE_KOMPLETORIUM)) {
		Export("Nevhodné údaje: nie je určená modlitba (%s).\n", modlitba);
		return FAILURE;
	}

	Log("nastavenie do _global_modlitba I. ...\n");
	_global_modlitba = p;
	// vstupom pre showPrayer() je iba zakladny typ modlitby; zvysna informacia (ci ide o prve/druhe vespery/kompl.) sa uchova v premennej _global_modlitba
	if ((p == MODL_PRVE_VESPERY) || (p == MODL_DRUHE_VESPERY)) {
		p = MODL_VESPERY;
	}
	if ((p == MODL_PRVE_KOMPLETORIUM) || (p == MODL_DRUHE_KOMPLETORIUM)) {
		p = MODL_KOMPLETORIUM;
	}

	// ak je to sobota a požadujú sa vešpery alebo kompletórium, zmeň nastavenia na nedeľu, prvé vešpery resp. prvé kompletórium (2013-02-03)
	if ((d == DEN_SOBOTA) && ((p == MODL_VESPERY) || (p == MODL_KOMPLETORIUM))) {
		Log("ak je to sobota a požadujú sa vešpery alebo kompletórium, zmeň nastavenia na nedeľu, prvé vešpery resp. prvé kompletórium...\n");
		d = DEN_NEDELA;
		p = (p == MODL_VESPERY) ? MODL_PRVE_VESPERY : MODL_PRVE_KOMPLETORIUM;
		Log("nastavenie do _global_modlitba II. ...\n");
		_global_modlitba = p;
		t += 1;
		tz = TYZZAL(t); // ((t + 3) MOD 4) + 1;
	}

	// setting of chosen common part (communia) | použitie zvolenej spoločnej časti
	_global_den.spolcast = (int)_global_opt[OPT_3_SPOLOCNA_CAST];
	Log("setting of chosen common part (communia): %ld\n", _global_opt[OPT_3_SPOLOCNA_CAST]);
	// it is always safe to test de-composed member spolcast with je_spolocna_cast_urcena()
	sc = _decode_spol_cast(_global_den.spolcast);
	if (je_spolocna_cast_urcena(sc.a1)) {
		jeSpolocnaCast = ANO;
	}

	// ked nejde o nedelu, nema zmysel rozlisovat prve/druhe vespery/kompl. | ToDo: slávnosti, sviatky Pána
	// ofícium za zosnulých nemá prvé vešpery
	if ((d != DEN_NEDELA) && ((jeSpolocnaCast == NIE) || (_global_den.spolcast == MODL_SPOL_CAST_ZA_ZOSNULYCH))) {
		if (p == MODL_VESPERY) {
			Log("nastavenie do _global_modlitba III. ...\n");
			_global_modlitba = MODL_VESPERY;
		}
		if (p == MODL_KOMPLETORIUM) {
			Log("nastavenie do _global_modlitba IV. ...\n");
			_global_modlitba = MODL_KOMPLETORIUM;
		}
	}// nie je to nedela

	Log("p == %d (%s); _global_modlitba == %d (%s)...\n", p, nazov_modlitby(p), _global_modlitba, nazov_modlitby(_global_modlitba));

	// pôstne obdobie nezačína nedeľou, ale popolcovou stredou; technicky ide o 0. týždeň pôstneho obdobia
	if ((d < DEN_NEDELA) || (d > DEN_SOBOTA) || ((t < 0) || ((t == 0) && ((lo != OBD_POSTNE_I) && (d < DEN_STREDA)))) || (t > POCET_NEDIEL_CEZ_ROK)) {
		ALERT;
		Export("Nevhodné údaje:" HTML_LINE_BREAK "\n<ul>");
		// deň
		if (equals(den, STR_EMPTY)) {
			Export("<li>chýba údaj o dni</li>\n");
		}
		else if (d == DEN_UNKNOWN) {
			Export("<li>deň = <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END " (neznámy)</li>\n", den);
		}
		else {
			Export("<li>deň = <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END "</li>\n", den);
		}
		// tyzden
		if (equals(tyzden, STR_EMPTY))
			Export("<li>chýba údaj o týždni</li>\n");
		else if ((t < 0) || ((t == 0) && ((lo != OBD_POSTNE_I) && (d < DEN_STREDA)))) {
			Export("<li>týždeň = <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END "</li>\n", tyzden);
		}
		else {
			Export("<li>týždeň = <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END "</li>\n", tyzden);
		}
		Export("</ul>\n");
		return FAILURE;
	}

	// kontrola, či týždeň daného liturgického obdobia neprekračuje počet týždňov daného obdobia | 2013-02-03: presunutá sem
	Log("kontrola, či týždeň daného liturgického obdobia neprekračuje počet týždňov daného obdobia...\n");
	// pre OBD_VELKONOCNE_II je týždeň 6 resp. 7, preto treba samostatne kontrolovať, ale neupravovať premennú t
	if (((lo != OBD_VELKONOCNE_II) && (lo != OBD_POSTNE_II_VELKY_TYZDEN) && (lo != OBD_VELKONOCNE_TROJDNIE) && (lo != OBD_VIANOCNE_II) && (lo != OBD_ADVENTNE_II) && (t > lit_obd_pocet_tyzdnov[lo]))
		|| ((lo == OBD_VELKONOCNE_II) && (t - 6 > lit_obd_pocet_tyzdnov[lo]))
		|| ((lo == OBD_VELKONOCNE_II) && (t - 6 == lit_obd_pocet_tyzdnov[lo] && d > DEN_NEDELA))
		|| (((lo == OBD_POSTNE_II_VELKY_TYZDEN) || (lo == OBD_VELKONOCNE_TROJDNIE)) && (t - 6 > lit_obd_pocet_tyzdnov[lo]))
		|| ((lo == OBD_VIANOCNE_II) && (t - 1 > lit_obd_pocet_tyzdnov[lo]))
		|| ((lo == OBD_ADVENTNE_II) && (t - 3 > lit_obd_pocet_tyzdnov[lo]))
		) {
		ALERT;
		Export("Nevhodné údaje:" HTML_LINE_BREAK "\n<ul>");
		// tyzden
		if (equals(tyzden, STR_EMPTY)) {
			Export("<li>taký týždeň nemožno žiadať</li>\n");
		}
		else {
			Export("<li>týždeň = <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END "; taký týždeň nemožno žiadať pre dané liturgické obdobie: %s</li>\n", tyzden, nazov_obdobia_ext(lo));
		}
		Export("</ul>\n");
		return FAILURE;
	}

	// setting up some basic data about liturgical year
	_global_den.rok = NULL_YEAR;
	analyzuj_rok(_global_den.rok);
	// Log(_global_r);

	// nastavenie niektorých atribútov pre _global_den
	_global_den.denvt = d;
	_global_den.litobd = lo;
	_global_den.tyzzal = tz;
	_global_den.tyzden = t;
	_global_den.litrok = lr; // default: litrok  = (char)('A' + nedelny_cyklus(den, mesiac, rok));

	// Log("_global_den.denvt == %d\n", _global_den.denvt);

	mystrcpy(_global_den.meno, STR_EMPTY, MENO_SVIATKU);
	// špeciálne nastavenie hodnoty smer
	Log("špeciálne nastavenie hodnoty smer... switch(%d | %s):\n", lo, nazov_obdobia_ext(lo));
	switch (lo) {

	case OBD_VELKONOCNE_TROJDNIE:
		_global_den.smer = 1; // trojdnie
		_global_den.farba = LIT_FARBA_BIELA;
		if (d == DEN_NEDELA) {
			_global_den.denvr = NULL_VELKONOCNA_NEDELA;
		}
		break;

	case OBD_ADVENTNE_I:
		if (d == DEN_NEDELA) {
			_global_den.smer = 2; // nedele adventné
			if (t == 1) {
				_global_den.denvr = NULL_PRVA_ADVENTNA_NEDELA;
			}
		}
		else {
			_global_den.smer = 13; // všedné dni adventné do 16. decembra
		}
		_global_den.farba = LIT_FARBA_FIALOVA;
		break;

	case OBD_ADVENTNE_II:
		if (d == DEN_NEDELA) {
			_global_den.smer = 2; // nedele adventné
		}
		else {
			_global_den.smer = 9; // všedné dni adventné od 17. do 24. decembra
		}
		_global_den.farba = LIT_FARBA_FIALOVA;
		break;

	case OBD_VELKONOCNA_OKTAVA:
		_global_den.smer = 2; // veľkonočná oktáva
		break;

	case OBD_POSTNE_I:
		if (d == DEN_NEDELA) {
			_global_den.smer = 2; // nedele pôstne
		}
		else {
			if ((d == DEN_STREDA) && (t == 0)) {
				_global_den.smer = 2; // popolcová streda
				_global_den.denvr = NULL_POPOLCOVA_STREDA;
			}
			else {
				_global_den.smer = 9; // všedné dni v pôste
			}
		}
		_global_den.farba = LIT_FARBA_FIALOVA;
		break;

	case OBD_POSTNE_II_VELKY_TYZDEN:
		_global_den.smer = 2;
		_global_den.farba = LIT_FARBA_FIALOVA;
		break;

	case OBD_VELKONOCNE_I:
		if (d == DEN_NEDELA) {
			_global_den.smer = 2; // nedele veľkonočné
			if (t == 1) {
				_global_den.denvr = NULL_VELKONOCNA_NEDELA; // netreba; je nastavené v case OBD_VELKONOCNE_TROJDNIE
			}
			if ((t == 7) && (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA))) {
				_global_den.denvr = NULL_NANEBOVSTUPENIE_PANA;
			}
		}
		else {
			_global_den.smer = 13; // všedné dni veľkonočné od pondelka po veľkonočnej oktáve až do soboty pred Zoslaním Ducha Svätého včítane
			if ((!isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA)) && (t == 6) && (d == DEN_STVRTOK)) {
				_global_den.denvr = NULL_NANEBOVSTUPENIE_PANA;
			}
		}
		_global_den.farba = LIT_FARBA_BIELA;
		break;

	case OBD_VELKONOCNE_II:
		if (d == DEN_NEDELA) {
			_global_den.smer = 2; // nedele veľkonočné
		}
		else {
			_global_den.smer = 13; // všedné dni veľkonočné od pondelka po veľkonočnej oktáve až do soboty pred Zoslaním Ducha Svätého včítane
		}
		if ((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA) && (t == 7) && (d == DEN_NEDELA))
			|| (!isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA) && (t == 6) && (d == DEN_STVRTOK))) {
			_global_den.denvr = NULL_NANEBOVSTUPENIE_PANA;
		}
		if ((t == 8) && (d == DEN_NEDELA)) {
			_global_den.denvr = NULL_ZOSLANIE_DUCHA_SV;
		}
		_global_den.farba = LIT_FARBA_BIELA;
		break;

	case OBD_VIANOCNE_I:
		if (d == DEN_NEDELA) {
			_global_den.smer = 6; // nedele vianočné (a cezročné)
		}
		else {
			_global_den.smer = 13; // všedné dni vianočné
		}
		_global_den.farba = LIT_FARBA_BIELA;
		break;

	case OBD_VIANOCNE_II:
		if (d == DEN_NEDELA) {
			_global_den.smer = 6; // nedele vianočné (a cezročné)
			if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA)) {
				_global_den.denvr = NULL_ZJAVENIE_PANA;
			}
		}
		else {
			_global_den.smer = 13; // všedné dni vianočné
			if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA) && (_global_den.denvt == DEN_PONDELOK)) {
				_global_den.denvr = NULL_KRST_KRISTA_PANA;
			}
		}
		_global_den.farba = LIT_FARBA_BIELA;
		break;

	case OBD_OKTAVA_NARODENIA:
		_global_den.smer = 9; // vianočná oktáva
		_global_den.farba = LIT_FARBA_BIELA;
		break;

	case OBD_CEZ_ROK:
		if (d == DEN_NEDELA) {
			_global_den.smer = 6; // nedele cezročné (a vianočné)
		}
		else {
			_global_den.smer = 13; // všedné dni cezročné
		}
		_global_den.farba = LIT_FARBA_ZELENA;
		break;

	default:
		_global_den.smer = 13;
		_global_den.farba = LIT_FARBA_ZELENA;
		break;
	} // switch(lo)

	if (_global_den.denvr < 0) {
		switch (_global_den.denvr) {
		case NULL_KRST_KRISTA_PANA:
			_global_den = _global_r._KRST_KRISTA_PANA;
			break;
		case NULL_POPOLCOVA_STREDA:
			_global_den = _global_r._POPOLCOVA_STREDA;
			break;
		case NULL_VELKONOCNA_NEDELA:
			_global_den = _global_r._VELKONOCNA_NEDELA;
			break;
		case NULL_NANEBOVSTUPENIE_PANA:
			_global_den = _global_r._NANEBOVSTUPENIE_PANA;
			break;
		case NULL_ZOSLANIE_DUCHA_SV:
			_global_den = _global_r._ZOSLANIE_DUCHA_SV;
			break;
		case NULL_PRVA_ADVENTNA_NEDELA:
			_global_den = _global_r._PRVA_ADVENTNA_NEDELA;
			break;
		case NULL_SVATEJ_RODINY:
			_global_den = _global_r._SVATEJ_RODINY;
			break;
		case NULL_ZJAVENIE_PANA:
			_global_den.den = 6;
			_global_den.mesiac = MES_JAN;
			_dm_zjavenie_pana(_global_den.rok, _global_den.denvr);
			_global_den = _global_result;
			break;
		}
	}

	// settings for sidemenu: above
	hlavicka_sidemenu();

	liturgicke_obdobie(lo, t, d, tz, poradie_svateho);

	// usage of chosen common part (communia) | použitie zvolenej spoločnej časti
	if (jeSpolocnaCast == ANO) {
		Log("_main_liturgicke_obdobie(): spoločná časť == %s...\n", nazov_spolc(_global_den.spolcast));
		_struct_sc sc = _decode_spol_cast(_global_den.spolcast);
		set_spolocna_cast(sc, poradie_svateho, FORCE_BRAT_VSETKO);
		set_popis_dummy(); // force
	}

	// skopírované podľa funkcie _rozbor_dna_s_modlitbou(); ukladá heading do stringu _global_string
	Log("spúšťam init_global_string(EXPORT_DNA_JEDEN_DEN, svaty == %d, modlitba == %s)...\n", poradie_svateho, nazov_modlitby(_global_modlitba));
	ret = init_global_string(EXPORT_DNA_JEDEN_DEN, poradie_svateho, _global_modlitba, /* aj_citanie */ NIE);

	if (ret == FAILURE) {
		Log("init_global_string() returned FAILURE, so returning FAILURE...\n");
		Log("_main_liturgicke_obdobie(): koniec (%d)\n", ret);
		return ret;
	}

	Log("nastavujem _global_string_modlitba...\n");
	init_global_string_modlitba(_global_modlitba);
	Log("nastavujem _global_string_podnadpis...\n");
	init_global_string_podnadpis(_global_modlitba);
	Log("nastavujem _global_string_spol_cast...\n");
	ret_sc = init_global_string_spol_cast(odfiltrujSpolCast(_global_modlitba, _global_den.spolcast), poradie_svateho);

	// experimentally added description of common part (communia)
	init_global_string_spol_cast_full(NIE);
	strcat(_global_string, HTML_LINE_BREAK);
	strcat(_global_string, _global_string_spol_cast_full);

	// doplnené; bolo len v rozbor_dna_s_modlitbou()
	Log("nastavujem do _global_pocet_zalmov_kompletorium počet žalmov...\n");
	_nastav_global_pocet_zalmov_kompletorium(p);
	Log("_global_pocet_zalmov_kompletorium == %d...\n", _global_pocet_zalmov_kompletorium);
	_export_heading_center(query_type, _global_string);

	// úprava aj_navigacia pre TTS = voice output
	if ((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_VOICE_OUTPUT)) && (p != MODL_NEURCENA)) {
		Log("pre voice output upravujem aj_navigacia na NIE (lebo modlitba == %d)...\n", p);
		aj_navigacia = CIASTOCNE;
	}

	Log("spustam showPrayer(%s) z funkcie _main_liturgicke_obdobie()...\n", nazov_modlitby(_global_modlitba));
	// predpokladam, ze aj _global_modlitba je prve/druhe vespery, v _global_prve_vespery su spravne udaje (podobne kompletorium)
	LOG_ciara;
	showPrayer(query_type, p, SHOW_TEMPLAT_MODLITBA, aj_navigacia);
	LOG_ciara;
	Log("...po návrate zo showPrayer(%s) vo funkcii _main_liturgicke_obdobie().\n", nazov_modlitby(_global_modlitba));

	Log("_main_liturgicke_obdobie(): koniec (%d)\n", SUCCESS);
	return SUCCESS;
} // _main_liturgicke_obdobie()

short int _main_static_text(short int st, short int p) {

	short int ret = FAILURE;
	_struct_anchor_and_file af;
	_INIT_ANCHOR_AND_FILE(af);
	mystrcpy(_global_include_static_text.anchor, STR_EMPTY, MAX_STR_AF_ANCHOR);
	mystrcpy(_global_include_static_text.file, STR_EMPTY, MAX_STR_AF_FILE);

	char pom[MAX_STR];
	char pom2[MAX_STR];
	mystrcpy(pom, STR_EMPTY, MAX_STR);
	mystrcpy(pom2, STR_EMPTY, MAX_STR);
	char pom3[MAX_STR];
	mystrcpy(pom3, STR_EMPTY, MAX_STR);

	char action[MAX_STR];
	mystrcpy(action, STR_EMPTY, MAX_STR);

	Log("-- _main_static_text(): begin...\n");

	// init of global variables
	_global_modlitba = MODL_NEURCENA;
	_global_pocet_svatych = 0;

	// rozparsovanie parametra static_text -- already done in _rozparsuj_parametre_DEN_MESIAC_ROK()
	Log("st == `%s' (%d)\n", pom_STATIC_TEXT, st);
	_global_pocet_svatych = st; // use this global variable because of check in interpretParameter() -- show/hide (c) info

	// rozparsovanie parametra modlitba -- already done in _rozparsuj_parametre_DEN_MESIAC_ROK()
	Log("p == `%s' (%d)\n", pom_MODLITBA, p);
	_global_modlitba = p; // p will be checked when needed (for example, for STATIC_TEXT_MARIANSKE_ANTIFONY not necessary)

	if ((st <= STATIC_TEXT_UNDEF) || (st > POCET_STATIC_TEXTOV)) {
		ALERT;
		_export_heading("Statické texty");
		Export("Nevhodný údaj: ");
		Export("chybné číslo %d (%s).\n", st, pom_STATIC_TEXT);
		return ret;
	}

	// treba nastaviť premennú _global_include_static_text

	// ToDo (enhancement): use array instead of if-else for multiple texts
	if (st == STATIC_TEXT_MARIANSKE_ANTIFONY) {
		_main_LOG_to_Export("STATIC_TEXT_MARIANSKE_ANTIFONY...\n");
		init_marianske_anfifony_file(_global_include_static_text);
		_global_modlitba = p = MODL_NEURCENA; // ak aj bola určená, vymažeme ju
	}
	else if (st == STATIC_TEXT_ORDINARIUM) {
		_main_LOG_to_Export("STATIC_TEXT_ORDINARIUM...\n");
		init_ordinarium_file(_global_include_static_text, p);
	}
	else if (st == STATIC_TEXT_INFO) {
		_main_LOG_to_Export("STATIC_TEXT_INFO...\n");
		init_info_file(_global_include_static_text, p);
	}

	_main_LOG_to_Export("\t_global_include_static_text: \n");
	Log_filename_anchor(_global_include_static_text);

	// settings for sidemenu
	_global_den.mesiac = st; // hack: usage of _global_den.mesiac */

	hlavicka_sidemenu();

	LOG_ciara;
	showPrayer(query_type, _global_modlitba, SHOW_TEMPLAT_STATIC_TEXT);
	LOG_ciara;

	ret = SUCCESS;

	Log("_main_static_text(): koniec (%d)\n", ret);
	return ret;
} // _main_static_text()

void _main_sviatok(char *sviatok) {
	// [ToDo]
	if (equals(sviatok, STR_EMPTY)) {
		ALERT;
		Export("Nevhodné údaje: chýba údaj o sviatku");
		return;
	}
	// unfinished
	Export("Chces %s? Este nejde...\n", sviatok);
} // _main_sviatok()

#define LOG  Log("analyza_roku(): "); Log

#define NewlineExport	Export(HTML_LINE_BREAK); Export

void ExportAnalyzaRokuRow(char* _global_link, const char* description) {
	Export("<" HTML_TABLE_ROW ">\n");
	ExportTableCell(HTML_TABLE_CELL);
	Export("%s", _global_link);
	Export(HTML_TABLE_CELL_END "\n");

	ExportTableCell(HTML_TABLE_CELL);
	Export("%s", description);
	Export(HTML_TABLE_CELL_END "\n");
	Export(HTML_TABLE_ROW_END "\n");
} // ExportAnalyzaRokuRow()

void _main_analyza_roku_prev_next(short int year, char pom2[MAX_STR]) {
	Log("_main_analyza_roku_prev_next(): begin...\n");

	char action[MAX_STR];
	mystrcpy(action, STR_EMPTY, MAX_STR);

	if ((_global_linky == ANO) && (!isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_MESIAC_RIADOK))) {
		Export(HTML_LINE_BREAK);
		Export("<" HTML_TABLE ">\n");

		Export("<" HTML_TABLE_ROW ">\n");

		// predošlý rok -- button
		ExportTableCell(HTML_TABLE_CELL);
		sprintf(action, "%s?%s=%s" HTML_AMPERSAND "%s=%d%s",
			script_name,
			STR_QUERY_TYPE, STR_PRM_ANALYZA_ROKU,
			STR_ANALYZA_ROKU, year - 1,
			pom2);
		Export_HtmlForm(action);
		Export(HTML_FORM_INPUT_SUBMIT0 " title=\"%s %s %d\" value=\"" HTML_LEFT_ARROW " %d", html_button_predchadzajuci_[_global_jazyk], html_text_rok[_global_jazyk], year - 1, year - 1);

#ifdef DISPLAY_TEXT_PREV_NEXT_YEAR
		Export(" (");
		Export((char*)html_button_predchadzajuci_[_global_jazyk]);
		Export(" ");
		Export((char*)html_text_rok[_global_jazyk]);
		Export(")");
#endif

		Export("\"" HTML_FORM_INPUT_END "\n");
		Export("</form>\n");
		Export(HTML_TABLE_CELL_END "\n");

		// nasledujúci rok -- button
		ExportTableCell(HTML_TABLE_CELL);
		sprintf(action, "%s?%s=%s" HTML_AMPERSAND "%s=%d%s",
			script_name,
			STR_QUERY_TYPE, STR_PRM_ANALYZA_ROKU,
			STR_ANALYZA_ROKU, year + 1,
			pom2);
		Export_HtmlForm(action);
		Export(HTML_FORM_INPUT_SUBMIT0 " title=\"%s %s %d\" value=\"", html_button_nasledujuci_[_global_jazyk], html_text_rok[_global_jazyk], year + 1);

#ifdef DISPLAY_TEXT_PREV_NEXT_YEAR
		Export("(");
		Export((char*)html_button_nasledujuci_[_global_jazyk]);
		Export(" ");
		Export((char*)html_text_rok[_global_jazyk]);
		Export(") ");
#endif

		Export("%d " HTML_RIGHT_ARROW "\"" HTML_FORM_INPUT_END "\n", year + 1);
		Export("</form>\n");
		Export(HTML_TABLE_CELL_END "\n");

		// koniec buttonov
		Export(HTML_TABLE_ROW_END "\n");

		Export(HTML_TABLE_END "\n");
	}

	Log("_main_analyza_roku_prev_next(): end.\n");
}// _main_analyza_roku_prev_next()

// dostane char *, najprv ho skontroluje a potom ak je vsetko v poriadku, exportuje stranku s jednotlivymi vyznacnymi dnami roka a linkami na vsetky mesiace
void _main_analyza_roku(char *rok) {
	_struct_den_mesiac datum;
	short int i;
	short int year;

	char pom[MAX_STR];
	mystrcpy(pom, STR_EMPTY, MAX_STR);
	char pom2[MAX_STR];
	mystrcpy(pom2, STR_EMPTY, MAX_STR);
	char pom3[MAX_STR];
	mystrcpy(pom3, STR_EMPTY, MAX_STR);

	Log("-- _main_analyza_roku(): zaciatok\n");

	year = atoi(rok);
	if (year <= 0) {
		ALERT;
		_export_heading("Analýza roku");
		Export("Nevhodný údaj: ");
		if (equals(rok, STR_EMPTY)) {
			Export("nezadaný rok.\n");
		}
		else if (equals(rok, STR_VALUE_ZERO)) {
			Export("nepoznám rok <" HTML_SPAN_BOLD ">" STR_VALUE_ZERO "" HTML_SPAN_END ".\n");
		}
		else {
			Export("chybné číslo (%s).\n", rok);
		}
		return;
	}

	// settings for sidemenu
	datum.den = VSETKY_DNI;
	datum.mesiac = VSETKY_MESIACE;

	_rozbor_dna_base(datum, year);

	hlavicka_sidemenu();

	prilep_request_options(pom2, pom3, 1 /* special_handling: remove BIT_OPT_1_OVERRIDE_STUP_SLAV */);

	sprintf(pom, (char *)html_text_Rok_x[_global_jazyk], year);
	_export_heading_center(query_type, pom);

	LOG("vchadzam do analyzuj_rok()...\n");
	analyzuj_rok(year); // výsledok dá do _global_r
	LOG("analyzuj_rok() ukoncena.\n");

	_main_analyza_roku_prev_next(year, pom2);

	Export("<" HTML_SPAN_RED ">");
	Export((char *)html_text_zakladne_info[_global_jazyk]);
	Export(":" HTML_SPAN_END "\n");
	Export(HTML_LINE_BREAK);

	// jazyk
	Export("<" HTML_SPAN_BOLD_IT ">");
	Export((char *)html_text_jazyk_verzia[_global_jazyk]);
	Export(":" HTML_SPAN_END "\n");
	Export((char *)nazov_jazyka(_global_jazyk));
	Export(HTML_LINE_BREAK);

	// rítus
	Export("<" HTML_SPAN_BOLD_IT ">");
	Export((char *)html_text_ritus[_global_jazyk]);
	Export(":" HTML_SPAN_END "\n");
	Export((char *)nazov_ritu(_global_ritus));
	Export(HTML_LINE_BREAK);

	// kalendár
	Export("<" HTML_SPAN_BOLD_IT ">");
	Export((char *)html_text_kalendar[_global_jazyk]);
	Export(":" HTML_SPAN_END "\n");
	Export((char *)nazov_kalendara(_global_kalendar)); // always display; regardless to condition PODMIENKA_EXPORTOVAT_KALENDAR
	Export(HTML_LINE_BREAK);

	vytvor_global_link(VSETKY_DNI, VSETKY_MESIACE, year, LINK_DEN_MESIAC_ROK, NIE);

	if (_global_linky == ANO) {
		mystrcpy(pom, cfg_http_address_default[_global_jazyk], MAX_STR);
	}
	else {
		mystrcpy(pom, MESSAGE_FOLDER, MAX_STR);
	}

	if (_global_jazyk != JAZYK_HU) {
		// 2011-05-16: v maďarčine sa tam slovo 'rok' (év) vôbec nehodí. Ak by si ho tam chcel mať, tak by muselo byť  za číslovkou a k číslovke by bolo treba pridať ešte koncovku. (mamedv)
		NewlineExport((char *)html_text_Rok[_global_jazyk]);
	}
	else {
		Export(HTML_LINE_BREAK);
	}
	Export(" %s <" HTML_SPAN_BOLD ">", _global_link);
	if (_global_r.prestupny == YES) {
		Export((char *)html_text_je[_global_jazyk]);
	}
	else {
		Export((char *)html_text_nie_je[_global_jazyk]);
	}
	Export(HTML_SPAN_END" " HTML_A_HREF_BEGIN "\"%s%s\">", pom, FILE_PRESTUPNY_ROK);
	Export((char *)html_text_prestupny[_global_jazyk]);
	Export(HTML_A_END".\n");

	NewlineExport(HTML_A_HREF_BEGIN "\"%s%s\">", pom, FILE_NEDELNE_PISMENO);
	if (_global_r.prestupny == YES) {
		Export((char *)html_text_Nedelne_pismena[_global_jazyk]);
		Export(HTML_A_END": <" HTML_SPAN_BOLD ">%s %s" HTML_SPAN_END "\n", string_nedelne_pismeno[alphabet_jayzka[_global_jazyk]][index_nedelne_pismeno(_global_r.p1)], string_nedelne_pismeno[alphabet_jayzka[_global_jazyk]][index_nedelne_pismeno(_global_r.p2)]);
	}
	else {
		Export((char *)html_text_Nedelne_pismeno[_global_jazyk]);
		Export(HTML_A_END": <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END "\n", string_nedelne_pismeno[alphabet_jayzka[_global_jazyk]][index_nedelne_pismeno(_global_r.p1)]);
	}

	datum = prva_adventna_nedela(year - 1);
	vytvor_global_link(datum.den, datum.mesiac, year - 1, LINK_DEN_MESIAC, NIE);
	// vytvor_global_link nastavi _global_link
	Export(HTML_P_BEGIN);
	if (_global_jazyk == JAZYK_HU) {
		// iné poradie vypisovaných reťazcov
		Export((char *)html_text_Od_prvej_adv_atd[_global_jazyk],
			year - 1,
			_global_link,
			string_nedelny_cyklus[alphabet_jayzka[_global_jazyk]][nedelny_cyklus(datum.den, datum.mesiac, year - 1)],
			pom,
			FILE_LITURGICKY_ROK
		);
	}
	else {
		Export((char *)html_text_Od_prvej_adv_atd[_global_jazyk],
			year - 1,
			_global_link,
			pom,
			FILE_LITURGICKY_ROK,
			string_nedelny_cyklus[alphabet_jayzka[_global_jazyk]][nedelny_cyklus(datum.den, datum.mesiac, year - 1)]
		);
	}

	Export(HTML_LINE_BREAK);

	Export("<" HTML_TABLE_LEFT ">\n");

	for (i = 0; i < POCET_ALIASOV; i++) {
		vytvor_global_link(_global_r._den[i].den, _global_r._den[i].mesiac, _global_r._den[i].rok, LINK_DEN_MESIAC, NIE);
		if (i == VELKONOCNA_NEDELA) {
			mystrcpy(_global_r._den[i].meno, text_VELKONOCNA_NEDELA[_global_jazyk], MENO_SVIATKU);
		}

		Export("<" HTML_TABLE_ROW ">\n");

		ExportTableCell(HTML_TABLE_CELL);
		Export("%s", _global_r._den[i].meno);
		Export(HTML_TABLE_CELL_END "\n");

		ExportTableCell(HTML_TABLE_CELL);
		Export("%s", _global_link);
		Export(HTML_TABLE_CELL_END "\n");

		ExportTableCell(HTML_TABLE_CELL);
		Export("(%s, ", nazov_dna(_global_r._den[i].denvt));

		Export((char *)html_text_den_v_roku[_global_jazyk], _global_r._den[i].denvr);
		Export(")");
		if (i == PRVA_ADVENTNA_NEDELA) {
			Export(", ");
			Export((char *)html_text_zacina[_global_jazyk]);
			Export(" " HTML_A_HREF_BEGIN "\"%s%s\">", pom, FILE_LITURGICKY_ROK);
			Export((char *)html_text_liturgicky_rok[_global_jazyk]);
			Export(HTML_A_END" <" HTML_SPAN_BOLD ">%c" HTML_SPAN_END ".", _global_r._den[i].litrok);
		}
		Export(HTML_TABLE_CELL_END "\n");

		Export(HTML_TABLE_ROW_END "\n");
	}

	Export(HTML_TABLE_END "\n");

	NewlineExport((char *)html_text_Po_Velkej_noci_atd[_global_jazyk], _global_r.tyzden_ocr_po_vn + 1, nazov_dna(DEN_NEDELA));

	vytvor_global_link(VSETKY_DNI, VSETKY_MESIACE, year, LINK_DEN_MESIAC_ROK, NIE);

	Export(HTML_P_BEGIN);
	Export("<" HTML_SPAN_RED ">");
	Export((char *)html_text_Prikazane_sviatky_v_roku[_global_jazyk], _global_link);
	Export(":" HTML_SPAN_END "\n");
	Export(HTML_LINE_BREAK);

	Export("<" HTML_TABLE_LEFT ">\n");

	// 1. januara
	vytvor_global_link(1, 1, year, LINK_DEN_MESIAC, NIE);
	ExportAnalyzaRokuRow(_global_link, text_JAN_01[_global_jazyk]);

	// 6. januara
	vytvor_global_link(6, 1, year, LINK_DEN_MESIAC, NIE);
	ExportAnalyzaRokuRow(_global_link, text_JAN_06[_global_jazyk]);

	// nanebovstúpenie pana
	vytvor_global_link(_global_r._NANEBOVSTUPENIE_PANA.den, _global_r._NANEBOVSTUPENIE_PANA.mesiac, year, LINK_DEN_MESIAC, NIE);
	ExportAnalyzaRokuRow(_global_link, text_NANEBOVSTUPENIE_PANA[_global_jazyk]);

	// najsv. kristovho tela a krvi; odvetvené 2011-11-07
	// kedze nie je v strukture _global_r, treba ho spocitat podla zoslania ducha sv. ide vlastne o datum (cislo v roku) pre ZOSLANIE_DUCHA_SV + 11, ako je definovany TELAKRVI, vyuzijeme parameter datum na zistenie dna a mesiaca
	if (!isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_TELAKRVI_NEDELA)) {
		datum = por_den_mesiac((ZOSLANIE_DUCHA_SV + 11), year);
		vytvor_global_link(datum.den, datum.mesiac, year, LINK_DEN_MESIAC, NIE);
		ExportAnalyzaRokuRow(_global_link, text_NAJSV_KRISTOVHO_TELA_A_KRVI[_global_jazyk]);
	}// BIT_OPT_0_TELAKRVI_NEDELA

	// 29. juna
	vytvor_global_link(29, 6, year, LINK_DEN_MESIAC, NIE);
	ExportAnalyzaRokuRow(_global_link, text_JUN_29[_global_jazyk]);

	// 15. augusta
	vytvor_global_link(15, 8, year, LINK_DEN_MESIAC, NIE);
	ExportAnalyzaRokuRow(_global_link, text_AUG_15[_global_jazyk]);

	// 1. novembra
	vytvor_global_link(1, 11, year, LINK_DEN_MESIAC, NIE);
	ExportAnalyzaRokuRow(_global_link, text_NOV_01[_global_jazyk]);

	// 8. decembra
	vytvor_global_link(8, 12, year, LINK_DEN_MESIAC, NIE);
	ExportAnalyzaRokuRow(_global_link, text_DEC_08[_global_jazyk]);

	// 25. decembra
	vytvor_global_link(25, 12, year, LINK_DEN_MESIAC, NIE);
	ExportAnalyzaRokuRow(_global_link, text_NARODENIE_PANA[_global_jazyk]);

	Export(HTML_TABLE_END "\n");

	// teraz nasleduju jednotlive mesiace roku s linkami na ne
	vytvor_global_link(VSETKY_DNI, VSETKY_MESIACE, year, LINK_DEN_MESIAC_ROK, NIE);

	Export(HTML_P_BEGIN);
	Export("<" HTML_SPAN_RED ">");
	Export((char *)html_text_Jednotlive_mesiace_roku[_global_jazyk], _global_link);
	Export(":" HTML_SPAN_END "\n");
	Export(HTML_LINE_BREAK);

	Export(HTML_LINE_BREAK"\n" HTML_P_CENTER "\n");
	// teraz zoznam mesiacov -- podla casti pre analyzu dna
	for (i = 1; i <= 12; i++) {
		Vytvor_global_link_class(VSETKY_DNI, i, year, LINK_DEN_MESIAC, NIE, HTML_CLASS_NAME_SMALLCAPS);
		Export("%s", _global_link);
		ExportNonbreakingSpace();
	}
	Export("\n" HTML_P_END "\n");

	_main_analyza_roku_prev_next(year, pom2);

	Log("-- _main_analyza_roku(): koniec\n");
} // _main_analyza_roku()

void _main_tabulka_shift_back_fwd(short int rfrom, short int rto, short int hl, char pom2[MAX_STR]) {
	Log("_main_tabulka_shift_back_fwd(): begin...\n");

	char action[MAX_STR];
	mystrcpy(action, STR_EMPTY, MAX_STR);

	if ((_global_linky == ANO) && (!isGlobalOption(OPT_4_OFFLINE_EXPORT, BIT_OPT_4_MESIAC_RIADOK))) {
		Export(HTML_LINE_BREAK);
		Export("<" HTML_TABLE ">\n");

		Export("<" HTML_TABLE_ROW ">\n");

		// posun k predošlým rokom -- button
		ExportTableCell(HTML_TABLE_CELL);
		sprintf(action, "%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d%s",
			script_name,
			STR_QUERY_TYPE, STR_PRM_TABULKA,
			STR_ROK_FROM, rfrom - 1,
			STR_ROK_TO, rto - 1,
			STR_TABULKA_LINKY, hl,
			pom2);
		Export_HtmlForm(action);
		Export(HTML_FORM_INPUT_SUBMIT0 " title=\"%d%s%d\" value=\"" HTML_LEFT_ARROW " (%d%s%d)", rfrom - 1, STR_EN_DASH_WITH_SPACES, rto - 1, rfrom - 1, STR_EN_DASH_WITH_SPACES, rto - 1);

		Export("\"" HTML_FORM_INPUT_END "\n");
		Export("</form>\n");
		Export(HTML_TABLE_CELL_END "\n");

		// posun k nasledujúcim rokom -- button
		ExportTableCell(HTML_TABLE_CELL);
		sprintf(action, "%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d%s",
			script_name,
			STR_QUERY_TYPE, STR_PRM_TABULKA,
			STR_ROK_FROM, rfrom + 1,
			STR_ROK_TO, rto + 1,
			STR_TABULKA_LINKY, hl,
			pom2);
		Export_HtmlForm(action);
		Export(HTML_FORM_INPUT_SUBMIT0 " title=\"%d%s%d\" value=\" (%d%s%d) " HTML_RIGHT_ARROW, rfrom + 1, STR_EN_DASH_WITH_SPACES, rto + 1, rfrom + 1, STR_EN_DASH_WITH_SPACES, rto + 1);

		Export("\"" HTML_FORM_INPUT_END "\n");
		Export("</form>\n");
		Export(HTML_TABLE_CELL_END "\n");

		// koniec buttonov
		Export(HTML_TABLE_ROW_END "\n");

		Export(HTML_TABLE_END "\n");
	}

	Log("_main_tabulka_shift_back_fwd(): end.\n");
}// _main_tabulka_shift_back_fwd()

// dostane char *, char * (a pripadne char *); najprv ich skontroluje a potom
// ak je vsetko v poriadku, exportuje stranku s tabulkou datumov pohyblivych slaveni
// rokov FROM -- TO a pripadne linkami na vsetky slavenia (podla TABULKA_LINKY)
void _main_tabulka(char *rok_from, char *rok_to, char *tab_linky) {
	_struct_den_mesiac datum;
	short int i;
	short int rfrom, rto, year, linky;

	char pom2[MAX_STR];
	mystrcpy(pom2, STR_EMPTY, MAX_STR);
	char pom3[MAX_STR];
	mystrcpy(pom3, STR_EMPTY, MAX_STR);

	Log("-- _main_tabulka(): zaciatok\n");

	rfrom = atoi(rok_from);
	rto = atoi(rok_to);
	linky = atoi(tab_linky);
	if ((rfrom <= 0) || (rto <= 0) || (rfrom > rto)) {
		ALERT;
		_export_heading("Analýza rokov");
		Export("Nevhodný údaj: ");
		if (equals(rok_from, STR_EMPTY)) {
			Export("nezadaný východzí rok.\n");
		}
		if (equals(rok_to, STR_EMPTY)) {
			Export("nezadaný koncový rok.\n");
		}
		else if ((equals(rok_from, STR_VALUE_ZERO)) || (equals(rok_to, "0"))) {
			Export("nepoznám rok <" HTML_SPAN_BOLD ">" STR_VALUE_ZERO "" HTML_SPAN_END ".\n");
		}
		else {
			Export("chybné číslo (%s, %s).\n", rok_from, rok_to);
		}
		return;
	}

	// settings for sidemenu
	_global_rok_from = rfrom;
	_global_rok_to = rto;
	_global_den.mesiac = linky; // hack: usage of _global_den.mesiac */

	hlavicka_sidemenu();

	_export_heading_center(query_type, (char *)html_text_datumy_pohyblivych_slaveni[_global_jazyk]);

	prilep_request_options(pom2, pom3, 1 /* special_handling: remove BIT_OPT_1_OVERRIDE_STUP_SLAV */);

	_main_tabulka_shift_back_fwd(rfrom, rto, linky, pom2);

	Export("<" HTML_TABLE ">\n");

	Export("<" HTML_TABLE_ROW ">\n");

	for (short int i = 0; i <= POCET_HTML_TEXT_POHYBLIVE; i++) {
		if ((i == HTML_TEXT_POHYBLIVE_ZJAVENIE_PANA) && ((_global_opt[OPT_0_SPECIALNE] & BIT_OPT_0_ZJAVENIE_PANA_NEDELA) != BIT_OPT_0_ZJAVENIE_PANA_NEDELA)) {
			continue;
		}// nezobrazuj pre krajiny, kde NIE JE Zjavenie Pána pohyblivé
		Export("<" HTML_TABLE_CELL_BORDER ">\n");
		Export((char *)html_text_pohyblive[i][_global_jazyk]);
		Export(HTML_TABLE_CELL_BORDER_END "\n");
	}
	Export(HTML_TABLE_ROW_END "\n");

	for (year = rfrom; year <= rto; year++) {
		LOG("-- _main_tabulka(): vchadzam do analyzuj_rok()...\n");
		analyzuj_rok(year); // výsledok dá do _global_r
		LOG("-- _main_tabulka(): analyzuj_rok() ukoncena.\n");

		Export("<" HTML_TABLE_ROW ">\n");

		// rok
		Export("<" HTML_TABLE_CELL_BORDER ">\n");
		if (linky == ANO) {
			// aj linka musi obsahovat 'prestupnost', podla toho ma farbu
			if (_global_r.prestupny == YES) {
				vytvor_global_link(VSETKY_DNI, VSETKY_MESIACE, year, LINK_DEN_MESIAC_ROK_PRESTUP, NIE);
			}
			else {
				vytvor_global_link(VSETKY_DNI, VSETKY_MESIACE, year, LINK_DEN_MESIAC_ROK, NIE);
			}
		}
		else {
			sprintf(_global_link, "%d", year);
		}

		if (_global_r.prestupny == YES) {
			Export("<" HTML_SPAN_RED ">%s" HTML_SPAN_END, _global_link);
		}
		else {
			Export("%s", _global_link);
		}
		Export(HTML_TABLE_CELL_BORDER_END "\n");

		// nedeľné litery
		Export("<" HTML_TABLE_CELL_BORDER ">\n");
		if (_global_r.prestupny == YES) {
			Export("%s %s", string_nedelne_pismeno[alphabet_jayzka[_global_jazyk]][index_nedelne_pismeno(_global_r.p1)], string_nedelne_pismeno[alphabet_jayzka[_global_jazyk]][index_nedelne_pismeno(_global_r.p2)]);
		}
		else {
			Export("%s", string_nedelne_pismeno[alphabet_jayzka[_global_jazyk]][index_nedelne_pismeno(_global_r.p1)]);
		}
		Export(HTML_TABLE_CELL_BORDER_END "\n");

		// nedeľný cyklus
		Export("<" HTML_TABLE_CELL_BORDER ">\n");
		datum = prva_adventna_nedela(year - 1);
		i = nedelny_cyklus(datum.den, datum.mesiac, year - 1);
		Export("%s-%s",
			string_nedelny_cyklus[alphabet_jayzka[_global_jazyk]][i],
			string_nedelny_cyklus[alphabet_jayzka[_global_jazyk]][(i + 1) MOD 3]);
		Export(HTML_TABLE_CELL_BORDER_END "\n");

		// aliasy -- význačné dni liturgického roka
		for (i = 0; i < POCET_ALIASOV; i++) {
			if ((i == idx_KRST_KRISTA_PANA) && ((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA)))) {
				// pre krajiny, kde je Zjavenie Pána pohyblivé: pred Krstom Pána ešte dátum Zjavenia Pána
				if (linky == ANO) {
					vytvor_global_link(zjavenie_pana(_global_r._den[i].rok), MES_JAN + 1, _global_r._den[i].rok, LINK_DEN_MESIAC, ANO);
				}
				else {
					strcpy(_global_link, _vytvor_string_z_datumu(zjavenie_pana(_global_r._den[i].rok), MES_JAN + 1, _global_r._den[i].rok, CASE_case, LINK_DEN_MESIAC, ANO));
				}
				Export("<" HTML_TABLE_CELL_BORDER ">\n");
				Export("%s", _global_link);
				Export(HTML_TABLE_CELL_BORDER_END "\n");
			}
			if (i == idx_PRVA_ADVENTNA_NEDELA) {
				// pred prvou adv. nedelou, po zoslani ducha sv. ide vypis, aky tyzden obdobia cez rok ide po velkej noci
				Export("<" HTML_TABLE_CELL_BORDER ">\n");
				Export("%d.", _global_r.tyzden_ocr_po_vn);
				Export(HTML_TABLE_CELL_BORDER_END "\n");
			}
			else if (i == idx_POPOLCOVA_STREDA) {
				// pred popolcovou stredou, aky tyzden obdobia cez rok ide pred pôstom
				Export("<" HTML_TABLE_CELL_BORDER ">\n");
				Export("%d", _global_r.tyzden_ocr_pred_po);
				Export(HTML_TABLE_CELL_BORDER_END "\n");
			}

			Export("<" HTML_TABLE_CELL_BORDER ">\n");
			if (linky == ANO) {
				vytvor_global_link(_global_r._den[i].den, _global_r._den[i].mesiac, _global_r._den[i].rok, LINK_DEN_MESIAC, ANO);
			}
			else {
				strcpy(_global_link, _vytvor_string_z_datumu(_global_r._den[i].den, _global_r._den[i].mesiac, _global_r._den[i].rok, CASE_case, LINK_DEN_MESIAC, ANO));
			}
			Export("%s", _global_link);
			Export(HTML_TABLE_CELL_BORDER_END "\n");
		}// for -- pre aliasy

		Export(HTML_TABLE_ROW_END "\n");
	}// for

	Export(HTML_TABLE_END "\n");

	vysvetlivky_tabulka();

	_main_tabulka_shift_back_fwd(rfrom, rto, linky, pom2);

	Log("-- _main_tabulka(): koniec\n");
} // _main_tabulka()

void dumpFile(char *fname, FILE *expt) {
	short int c;
	FILE *input_file = fopen(fname, "rb");
	if (input_file != NULL) {
		while ((c = fgetc(input_file)) != EOF) {
			fputc(c, expt);
		}
	}
} // dumpFile()

void _batch_mode_header(short mesiac, short rok) {
	// vynulovanie podľa vynulovania pred batch_html_file
	_global_hlavicka_Export = 0;
	_global_patka_Export = 0;
	myhpage_init_globals();
	hlavicka((char *)html_title_batch_mode[_global_jazyk], batch_month_file, 1);
	fprintf(batch_month_file, "\n");

	// začiatok hlavičky
	fprintf(batch_month_file, "<h2>");
	fprintf(batch_month_file, (char *)html_text_batch_Zoznam2[_global_jazyk], nazov_mesiaca(mesiac), rok);
	fprintf(batch_month_file, "</h2>");
	// ^ hore
	fprintf(batch_month_file, HTML_P_CENTER "" HTML_A_HREF_BEGIN "\"..%s%s\"%s>", STR_PATH_SEPARATOR_HTML, name_batch_html_file, optional_html_class_button);
	fprintf(batch_month_file, "%s", optional_html_button_begin);
	fprintf(batch_month_file, "%s", HTML_UP_ARROW_CLASSIC "" STR_SPACE);
	fprintf(batch_month_file, "%s", (char *)html_text_batch_Back[_global_jazyk]);
	fprintf(batch_month_file, "%s", optional_html_button_end);
	fprintf(batch_month_file, HTML_A_END "" HTML_P_END);
	// koniec hlavičky
}// _batch_mode_header()

#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
#define system(arg)
#elif TARGET_OS_MAC
#else
#   error "Unknown Apple platform"
#endif
#else
// nothing for Windows & unices
#endif

// dostane vela char *; najprv ich skontroluje a potom ak je vsetko v poriadku, do export fajlu generuje command-line prikazy pre vytvorenie modlitby na jednotlive dni dane obdobim
void _main_batch_mode(
	char *den_from, char *mesiac_from, char *rok_from,
	char *den_to, char *mesiac_to, char *rok_to,
	char *nieco, char *tab_linky) {

	short int heading_written = 0; // je tu kvoli ExportUDAJE definovane pred _main_rozbor_dna
	Log("-- _main_batch_mode(char * -- 7x): begin (%s, %s, %s, %s, %s, %s, %s, %s)\n",
		den_from, mesiac_from, rok_from, den_to, mesiac_to, rok_to, nieco, tab_linky);
	short int d_from, m_from, r_from, d_to, m_to, r_to;
	long jd_from, jd_to;
	short int i; // doplnené kvôli presunutiu čítania opt_0...opt_4 do _rozparsuj_parametre_OPT
	short int som_dnu = NIE; // či som "cd" príkazom vnútri adresára jednotlivého mesiaca pre 'M' -- mesačný export v batch móde
	_struct_den_mesiac d_a_m;
	short int d, m, r, p, pocet_dni_v_mes;
	short int prveho_v_mesiaci = NIE;
	short int max_modlitba = MODL_NEURCENA;

	// rozparsovanie parametrov den, mesiac, rok
	Log("--start(from)--\n");
	// --from--
	Log("/* rozparsovanie parametrov den, mesiac, rok FROM */\n");
	d_from = atoden(den_from); // vrati VSETKY_DNI, resp. atoi(den_from)
	Log("den_from == `%s' (%d)\n", den_from, d_from);
	m_from = atomes(mesiac_from); // bude to 0--11, resp. VSETKY_MESIACE resp. UNKNOWN_MESIAC
	Log("mes_from == `%s' (%d)\n", mesiac_from, m_from);
	r_from = atoi(rok_from); // vrati 0 v pripade chyby; alebo int
	Log("rok_from == `%s' (%d)\n", rok_from, r_from);

	Log("--end(to)--\n");
	// --to--
	Log("/* rozparsovanie parametrov den, mesiac, rok TO */\n");
	d_to = atoden(den_to); // vrati VSETKY_DNI, resp. atoi(den_to)
	Log("den_to == `%s' (%d)\n", den_to, d_to);
	m_to = atomes(mesiac_to); // bude to 0--11, resp. VSETKY_MESIACE resp. UNKNOWN_MESIAC
	Log("mes_to == `%s' (%d)\n", mesiac_to, m_to);
	r_to = atoi(rok_to); // vrati 0 v pripade chyby; alebo int
	Log("rok_to == `%s' (%d)\n", rok_to, r_to);

	Log("Ruším nastavenie pre parameter _global_modlitba (doteraz == %d/%s)...\n", _global_modlitba, nazov_modlitby(_global_modlitba));
	_global_modlitba = MODL_NEURCENA;

	// kontrola udajov
	short int result = SUCCESS;

	// --from--

	// deň
	if (equals(den_from, STR_EMPTY)) {
		ExportUDAJE("chýba údaj o počiatočnom dni." HTML_LINE_BREAK);
	}
	else if (d_from == 0) {
		ExportUDAJE("deň = <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END "." HTML_LINE_BREAK, den_from);
	}
	// mesiac
	if (equals(mesiac_from, STR_EMPTY)) {
		ExportUDAJE("chýba údaj o počiatočnom mesiaci." HTML_LINE_BREAK);
	}
	else if (m_from == UNKNOWN_MESIAC) {
		ExportUDAJE("taký mesiac nepoznám (%s)." HTML_LINE_BREAK, mesiac_from);
	}
	// rok
	if (equals(rok_from, STR_EMPTY)) {
		ExportUDAJE("chýba údaj o počiatočnom roku." HTML_LINE_BREAK);
	}
	else if (r_from == 0) {
		ExportUDAJE("rok = <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END "." HTML_LINE_BREAK, rok_from);
	}

	// --to--

	// deň
	if (equals(den_to, STR_EMPTY)) {
		ExportUDAJE("chýba údaj o koncovom dni." HTML_LINE_BREAK);
	}
	else if (d_to == 0) {
		ExportUDAJE("deň = <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END "." HTML_LINE_BREAK, den_to);
	}
	// mesiac
	if (equals(mesiac_to, STR_EMPTY)) {
		ExportUDAJE("chýba údaj o koncovom mesiaci." HTML_LINE_BREAK);
	}
	else if (m_to == UNKNOWN_MESIAC) {
		ExportUDAJE("taký mesiac nepoznám (%s)." HTML_LINE_BREAK, mesiac_to);
	}
	// rok
	if (equals(rok_to, STR_EMPTY)) {
		ExportUDAJE("chýba údaj o koncovom roku." HTML_LINE_BREAK);
	}
	else if (r_to == 0) {
		ExportUDAJE("rok = <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END "." HTML_LINE_BREAK, rok_to);
	}

	// juliansky datum dna _from musi byt <= ako dna _to
	// mesiac (int) je 0-11! juliansky_datum() ocakava 1-12
	jd_from = JD(d_from, m_from + 1, r_from);
	jd_to = JD(d_to, m_to + 1, r_to);
	if (jd_from > jd_to) {
		Log("JD_from = %ld > JD_to = %ld\n", jd_from, jd_to);
		ExportUDAJE("Zlé časové obdobie (dátum `od' (%s.%s.%s) nasleduje po dátume `do' (%s.%s.%s))." HTML_LINE_BREAK, den_from, mesiac_from, rok_from, den_to, mesiac_to, rok_to);
	}// datum _to je casovo _pred_ datumom _from!
	else {
		Log("julianske datumy: v poriadku\n");
	}// datumy su v spravnom vztahu

	// udaje su skontrolovane
	if (result == FAILURE) {
		Log("/* teraz result == FAILURE */\n");
		if (query_type == PRM_XML) {
			// nothing to do
		}
		else {
			ALERT;
		}
		return;
	}
	else {
		Log("/* teraz result == SUCCESS */\n");
		// kontrola name_batch_file - ci sa do suboru da zapisovat
		// na zapisovanie do batch_file nevyuzivame Export()
		if (strcmp(name_batch_file, STR_EMPTY) != 0) {
			batch_file = fopen(name_batch_file, "wt");
			if (batch_file != NULL) {
				Log("batch mode: File `%s' opened for writing... (batch_file)\n", name_batch_file);
				// teraz zacina cela sranda :)) ...
				// vystupny zoznam sa pripadne zapisuje aj ako HTML do suboru na zapisovanie do batch_html_file nevyuzivame Export()
				if (strcmp(name_batch_html_file, STR_EMPTY) == 0) {
					mystrcpy(name_batch_html_file, DEFAULT_HTML_EXPORT, MAX_STR);
				}
				batch_html_file = fopen(name_batch_html_file, "wt");
				if (batch_html_file != NULL) {
					Log("batch mode: File `%s' opened for writing... (batch_html_file)\n", name_batch_html_file);
					_global_hlavicka_Export = 0;
					_global_patka_Export = 0;
					myhpage_init_globals();
					hlavicka((char *)html_title_batch_mode[_global_jazyk], batch_html_file, -1 /* t. j. bez úprav linky */, _global_opt_batch_monthly /* element <body> špeciálne */);
					// doplnené "zrýchlené voľby" | fix of JavaScript functions
					if (_global_opt_batch_monthly == ANO) {
						fprintf(batch_html_file, "<h1>%s</h1>\n", (char *)html_text_batch_mode_h1[_global_jazyk]);
						if (PODMIENKA_EXPORTOVAT_KALENDAR) {
							fprintf(batch_html_file, HTML_P_CENTER "%s: \n", (char *)html_text_Kalendar[_global_jazyk]);
							fprintf(batch_html_file, "<" HTML_SPAN_RED ">%s" HTML_SPAN_END "\n", (char *)nazov_kalendara_long[_global_kalendar]);
							fprintf(batch_html_file, HTML_P_END "\n");
						}
						fprintf(batch_html_file, "<h2>%s</h2>\n", (char *)html_text_Breviar_dnes[_global_jazyk]);
						fprintf(batch_html_file, "<!-- SK: Odkazy na dnešný deň (Dnešné modlitby) a Prehľad mesiaca vyžadujú JavaScript. JavaScript funkcia (c) 2009 Peter Sahajda; upravil (c) 2010 Juraj Vidéky -->\n");
						fprintf(batch_html_file, "\n");
						fprintf(batch_html_file, "<script language=\"javascript\" type=\"text/javascript\">\n");
						fprintf(batch_html_file, "var dnes=new Date();\n");
						fprintf(batch_html_file, "var den=dnes.getDate();\n");
						fprintf(batch_html_file, "var mesiac_text = [\"jan\",\"feb\",\"mar\",\"apr\",\"maj\",\"jun\",\"jul\",\"aug\",\"sep\",\"okt\",\"nov\",\"dec\"]; \n");
						fprintf(batch_html_file, "var mesiac=dnes.getMonth() + 1;\n"); // mesiac je od 0 po 11
						fprintf(batch_html_file, "var mesiac_text1=mesiac_text[dnes.getMonth()];\n");
						fprintf(batch_html_file, "// var rok=dnes.getFullYear();\n");
						fprintf(batch_html_file, "var rok = dnes.getYear();\n");
						fprintf(batch_html_file, "if (rok < 2000) { rok = rok + 1900; }\n");
						fprintf(batch_html_file, "rok = rok.toString().slice(2);\n");
						fprintf(batch_html_file, "\n");
						fprintf(batch_html_file, "if (mesiac <= 9) {mesiac = '0' + mesiac;}\n");
						fprintf(batch_html_file, "if (den <= 9 ) {den = '0' + den;}\n");
						fprintf(batch_html_file, "\n");
						fprintf(batch_html_file, "var cestax = rok.toString()+mesiac.toString()+'-'+mesiac_text1+'/'+rok.toString()+''+mesiac.toString()+''+den.toString()+'.htm';\n");
						fprintf(batch_html_file, "var cesta_mesiac = rok.toString()+mesiac.toString()+'-'+mesiac_text1+'/'+rok.toString()+''+mesiac.toString()+'.htm';\n");
						fprintf(batch_html_file, "\n");
						fprintf(batch_html_file, "var tag1 = '" HTML_A_HREF_BEGIN "./';\n");
						fprintf(batch_html_file, "\n");
						fprintf(batch_html_file, "var tag2 = '" HTML_A_END "';\n");
						fprintf(batch_html_file, "tag2+='" HTML_LINE_BREAK_PURE "';\n");
						fprintf(batch_html_file, "\n");
						fprintf(batch_html_file, "var output='';\n");
						fprintf(batch_html_file, "\n");
						if (_global_jazyk == JAZYK_HU) {
							fprintf(batch_html_file, "output = output + '<ul><li> '+tag1+cestax+'>%s (20'+rok+'. '+mesiac+'. '+den+'.)'+tag2+'" HTML_LINE_BREAK_PURE "</li>';\n", (char *)html_text_Dnesne_modlitby[_global_jazyk]);
						}
						else {
							fprintf(batch_html_file, "output = output + '<ul><li> '+tag1+cestax+'>%s ('+den+'. '+mesiac+'. 20'+rok+')'+tag2+'" HTML_LINE_BREAK_PURE "</li>';\n", (char *)html_text_Dnesne_modlitby[_global_jazyk]);
						}
						fprintf(batch_html_file, "\n");
						if (_global_jazyk == JAZYK_HU) {
							fprintf(batch_html_file, "output = output + '<li>'+tag1+cesta_mesiac+'>%s (20'+rok+'/'+mesiac+')'+tag2+'</li></ul>';\n", (char*)html_text_Prehlad_mesiaca[_global_jazyk]);
						}
						else {
							fprintf(batch_html_file, "output = output + '<li>'+tag1+cesta_mesiac+'>%s ('+mesiac+'/20'+rok+')'+tag2+'</li></ul>';\n", (char*)html_text_Prehlad_mesiaca[_global_jazyk]);
						}
						fprintf(batch_html_file, "\n");
						fprintf(batch_html_file, "document.write(output);\n");
						fprintf(batch_html_file, "</script>\n");
					}

					fprintf(batch_html_file, "\n");
					fprintf(batch_html_file, "<h2>");
					if (_global_opt_batch_monthly == ANO) {
						fprintf(batch_html_file, "%s", (char *)html_text_batch_Zoznam1m[_global_jazyk]);
					}
					else {
						fprintf(batch_html_file, "%s", (char *)html_text_batch_Zoznam1[_global_jazyk]);
					}
					fprintf(batch_html_file, "</h2>\n");

					if (_global_opt_batch_monthly == ANO) {
						fprintf(batch_html_file, "<h4>");
						if (_global_jazyk == JAZYK_HU) {
							fprintf(batch_html_file, (const char*)html_text_batch_obdobie1m[_global_jazyk], r_from, nazov_mesiaca_gen(m_from), d_from, r_to, nazov_mesiaca_gen(m_to), d_to);
						}
						else {
							fprintf(batch_html_file, (const char*)html_text_batch_obdobie1m[_global_jazyk], d_from, nazov_mesiaca_gen(m_from), r_from, d_to, nazov_mesiaca_gen(m_to), r_to);
						}
						fprintf(batch_html_file, "</h4>\n");
					}
					fprintf(batch_html_file, "<ul>\n");
					LOG_ciara;
					Log("batch mode: teraz začínam prechádzať celé zadané obdobie...\n");

					// 1. ak r_from < r_to:
					//    (i)   od poradie(d_from, m_from, r_from) do poradie(31, MES_DEC, r_from);
					//    (ii)  pre roky i = (r_from + 1) do (r_to - 1):
					//          od poradie(1, MES_JAN, i) do poradie(31, MES_DEC, i);
					//    (iii) pre posledny rok: od poradie(1, MES_JAN, r_to) do poradie(d_to, m_to, r_to);
					// 2. ak je to r_from == r_to, tak len
					//    pre poradie(d_from, m_from, r_from) do poradie(d_to, m_to, r_from==r_to)
					//
					// co sa tam vlastne bude robit?
					// 1. analyzuj_rok() daneho roku (r_from, i, r_to) -- ale len 1x!
					// 2. pre vsetky potrebne dni: rozbor_dna() -- ale printovat to  nie Exportom do `export.htm', ale printf(name_batch_file)!
					// 3. that's all
					//
					// popritom pri prepínači _global_opt_batch_monthly == ANO je potrebné vždy vytvoriť adresár pre daný mesiac,
					// prepnúť sa doňho a následne (pre ďalší nový mesiac) z neho vyjsť a zas vytvoriť adresár (2009-08-02)

					// _global_string vyuzijeme na to, aby sme si medzi jednotlivymi dnami posielali nazov suboru v pripade, ze chce vsetky modlitby do 1 suboru (pouzil "-a1" = append)
					if (_global_opt_append == YES) {
						mystrcpy(_global_string, STR_EMPTY, MAX_GLOBAL_STR); // inicializacia
						mystrcpy(_global_string_modlitba, STR_EMPTY, SMALL);
						mystrcpy(_global_string_podnadpis, STR_EMPTY, SMALL);
						mystrcpy(_global_string_spol_cast, STR_EMPTY, MAX_GLOBAL_STR2);
						mystrcpy(_global_string_spol_cast_full, STR_EMPTY, MAX_GLOBAL_STR);

						if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
							sprintf(_global_string, FILENAME_EXPORT_DATE_SIMPLE "_" FILENAME_EXPORT_DATE_SIMPLE, r_from % 100, m_from + 1, d_from, r_to % 100, m_to + 1, d_to);
						}
						else { // EXPORT_DATE_FULL
							sprintf(_global_string, FILENAME_EXPORT_DATE_FULL "_" FILENAME_EXPORT_DATE_FULL, r_from, m_from + 1, d_from, r_to, m_to + 1, d_to);
						}
						// m_to resp. m_from: sú hodnoty 0--11, resp. VSETKY_MESIACE resp. UNKNOWN_MESIAC
					}

					export_month_zaciatok = ANO;
					export_month_nova_modlitba = ANO;

					Log("podľa týchto dvoch sa bude rozhodovať o type exportu...\n");
					Log("_global_opt_batch_monthly == %d\n", _global_opt_batch_monthly);
					Log("export_monthly_druh == %d\n", export_monthly_druh);

					// nový druh exportu po mesiacoch -- aby jednotlivé mesiace mali sekcie podľa modlitieb; deň je len číslo
					if ((_global_opt_batch_monthly == ANO) && (export_monthly_druh >= 1)) {
						Log("batch mode: iný druh exportu pre mesiace\n");
						if (export_monthly_druh < 2) {
							Log("\tv rámci jednoho mesiaca pôjdeme v hlavnom cykle po modlitbách, nie po dňoch\n");
						}
						// iný druh exportu pre mesiace; v rámci jednoho mesiaca pôjdeme v hlavnom cykle po modlitbách, nie po dňoch
						for (r = r_from; r <= r_to; r++) {
							Log("batch mode: rok %d...\n", r);
							analyzuj_rok(r);
							// m je 0--11 čiže MES_JAN až MES_DEC
							for (m = (r == r_from ? m_from : MES_JAN); m <= (r == r_to ? m_to : MES_DEC); m++) {

								Log("batch mode: rok %d, mesiac %d [%s]...\n", r, m + 1, nazov_mesiaca_asci(m));

								// 2012-12-12: nie pre append (netreba vytvárať adresáre [mkdir] ani po nich chodiť [cd])
								if (_global_opt_append != YES) {
									if (som_dnu == ANO) {
										fprintf(batch_file, "cd ..\n");
										Log("cd ..\n");
										som_dnu = NIE;
									}
									if (/* r != r_from && m != m_from && */ index_pre_mesiac_otvoreny == ANO) {
										fprintf(batch_month_file, "</ul>\n");
										patka(batch_month_file);
										fclose(batch_month_file);
										Log("batch mode: export pre mesiac `%d' skončený, súbor %s zatvorený.\n", m, name_batch_month_file);
										index_pre_mesiac_otvoreny = NIE;
									}
									// názov executable resp. include dir sme zmenili hneď v getArgv() (lebo budeme meniť adresár)
									if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
										sprintf(dir_name, DIRNAME_EXPORT_MONTH_SIMPLE, r % 100, m + 1, nazov_mes[m]);
									}
									else {
										// EXPORT_DATE_FULL
										sprintf(dir_name, DIRNAME_EXPORT_MONTH_FULL, r, m + 1, nazov_mesiaca_asci(m));
									}
									sprintf(system_command, CMD_MKDIR" \"%s\"\n", dir_name);
									Log(CMD_MKDIR" \"%s\"\n", dir_name);
									// fprintf(batch_file, system_command);
									system(system_command);
									fprintf(batch_file, "cd \"%s\"\n", dir_name);
									Log("cd \"%s\"\n", dir_name);
								}// if (_global_opt_append != YES) -- nie pre append

								som_dnu = ANO;

								if (export_monthly_druh >= 2) {
									Log("rozbor mesiaca pre export (%s %d)...\n", nazov_mesiaca(m), r);
									// bez ohľadu na to, čo pre tento typ exportu bolo nastavené, použije sa z mesiaca vytvorený súbor; až teraz, keď je vygenerovaný príkaz pre vytvorenie mesiaca
									if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
										sprintf(_global_export_navig_hore_month, FILENAME_EXPORT_MONTH_SIMPLE".htm", r % 100, m + 1);
									}
									else {
										// EXPORT_DATE_FULL
										sprintf(_global_export_navig_hore_month, FILENAME_EXPORT_MONTH_FULL".htm", r, m + 1);
									}
									_export_rozbor_dna_mesiaca_batch(VSETKY_DNI, m + 1, r);
									// vytvorenie názvu súboru pre mesiac
									mystrcpy(name_batch_month_file, dir_name, MAX_STR);
									strcat(name_batch_month_file, STR_PATH_SEPARATOR);
									strcat(name_batch_month_file, _global_export_navig_hore_month);
									Log("rozbor mesiaca pre export (súbor %s)...\n", name_batch_month_file);
								}// if (export_monthly_druh >= 2)
								else {
									// vytvorenie názvu súboru pre mesiac
									mystrcpy(name_batch_month_file, dir_name, MAX_STR);
									strcat(name_batch_month_file, STR_PATH_SEPARATOR);
									strcat(name_batch_month_file, _global_export_navig_hore /* DEFAULT_MONTH_EXPORT */);
									// otvorím aj súbor pre jednotlivý mesiac
									batch_month_file = fopen(name_batch_month_file, "wt");
									if (batch_month_file != NULL) {
										Log("batch mode: File `%s' opened for writing... (batch_month_file/1)\n", name_batch_month_file);
										// môžeme upraviť názov tak, ako ho budeme printovať do dokumentov -- aby obsahoval STR_PATH_SEPARATOR_HTML namiesto STR_PATH_SEPARATOR
										// pre použitie vo funkcii execute_batch_command()
										mystrcpy(name_batch_month_file, dir_name, MAX_STR);
										strcat(name_batch_month_file, STR_PATH_SEPARATOR_HTML);
										strcat(name_batch_month_file, _global_export_navig_hore /* DEFAULT_MONTH_EXPORT */);
										Log("batch mode: názov súboru upravený na '%s' (súbor je už otvorený)...\n", name_batch_month_file);

										_batch_mode_header(m, r_from);

										// začiatok zoznamu
										fprintf(batch_month_file, "<ul>\n");
										index_pre_mesiac_otvoreny = ANO;
									}
								}// else if (export_monthly_druh >= 2)

								if (export_monthly_druh >= 2) {
									// v rámci daného mesiaca ideme podľa dní, vnútri podľa modlitieb
									// d je číslo 1 až max
									d_a_m.mesiac = m + 1; // totiž _struct_den_mesiac má mesiace 1--12, zatiaľ čo m je 0--11
									pocet_dni_v_mes = pocet_dni[m];
									if (prestupny(r) && m == MES_FEB)
										pocet_dni_v_mes = 29;
									for (d = ((r == r_from && m == m_from) ? d_from : 1); d <= ((r == r_to && m == m_to) ? d_to : pocet_dni_v_mes); d++) {
										d_a_m.den = d;
										Log("batch mode: rok %d, mesiac %d [%s], den %d...\n", r, m + 1, nazov_mesiaca_asci(m), d);
										// bez ohľadu na to, čo pre tento typ exportu bolo nastavené, použije sa zo dňa a mesiaca vytvorený súbor; až teraz, keď je vygenerovaný príkaz pre vytvorenie dňa
										if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
											sprintf(_global_export_navig_hore_day, FILENAME_EXPORT_DATE_SIMPLE".htm", r % 100, m + 1, d);
										}
										else {
											// EXPORT_DATE_FULL
											sprintf(_global_export_navig_hore_day, FILENAME_EXPORT_DATE_FULL".htm", r, m + 1, d);
										}

										_export_rozbor_dna_mesiaca_batch(d, m + 1, r);

										_rozbor_dna(d_a_m, r);

										max_modlitba = MODL_KOMPLETORIUM;

										// ToDo: this condition should be more precise
										if ((_global_den.denvt == DEN_NEDELA) || (_global_den.typslav == SLAV_SLAVNOST)) {
											max_modlitba = MODL_PRVE_VESPERY;
										}

										for (p = MODL_INVITATORIUM; p <= max_modlitba; p++) {

											if (p == MODL_NEURCENA) {
												continue;
											}

											Log("batch mode: rok %d, mesiac %d [%s], modlitba %s (%d), den %d...\n", r, m + 1, nazov_mesiaca_asci(m), nazov_modlitby(p), p, d);
											_export_rozbor_dna_batch(EXPORT_DNA_JEDEN_DEN, p, (r == r_from && m == m_from && d == d_from) ? 1 : 0);
										} // for p
									}// for d
								}// if (export_monthly_druh >= 2)
								else {
									// v rámci daného mesiaca ideme podľa modlitieb, až vnútri podľa dní
									for (p = MODL_INVITATORIUM; p <= MODL_PRVE_VESPERY; p++) {

										if (p == MODL_NEURCENA) {
											continue;
										}

										Log("batch mode: rok %d, mesiac %d [%s], modlitba %s (%d)...\n", r, m + 1, nazov_mesiaca_asci(m), nazov_modlitby(p), p);
										export_month_nova_modlitba = ANO; // toto je potrebné kvôli zmene podmienky vo funkcii execute_batch_command()
										// d je číslo 1 až max
										d_a_m.mesiac = m + 1; // totiž _struct_den_mesiac má mesiace 1--12, zatiaľ čo m je 0--11
										pocet_dni_v_mes = pocet_dni[m];
										if (prestupny(r) && m == MES_FEB) {
											pocet_dni_v_mes = 29;
										}
										for (d = ((r == r_from && m == m_from) ? d_from : 1); d <= ((r == r_to && m == m_to) ? d_to : pocet_dni_v_mes); d++) {
											d_a_m.den = d;
											Log("batch mode: rok %d, mesiac %d [%s], modlitba %s (%d), den %d...\n", r, m + 1, nazov_mesiaca_asci(m), nazov_modlitby(p), p, d);

											_rozbor_dna(d_a_m, r);

											// ToDo: this condition should be more precise
											if ((p < MODL_NEURCENA) || ((_global_den.denvt == DEN_NEDELA) || (_global_den.typslav == SLAV_SLAVNOST))) {
												_export_rozbor_dna_batch(EXPORT_DNA_JEDEN_DEN, p, (r == r_from && m == m_from && d == d_from) ? 1 : 0);
											}
										}// for d
									}
								}// else if (export_monthly_druh >= 2)
							}// for m
						}// for r
						Log("batch mode: iný druh exportu pre mesiace: koniec\n");
					}// if (_global_opt_batch_monthly == ANO && export_monthly_druh >= 1)
					else {
						Log("batch mode: klasický export 'zaradom' alebo po mesiacoch s tým, že hlavný cyklus ide po dňoch (čo deň, to riadok s odkazom na modlitby)\n");
						// klasický export 'zaradom' alebo po mesiacoch s tým, že hlavný cyklus ide po dňoch (čo deň, to riadok s odkazom na modlitby)
						// exportovanie do adresárov po mesiacoch
						if (_global_opt_batch_monthly == ANO) {
							// nie pre append (netreba vytvárať adresáre [mkdir] ani po nich chodiť [cd])
							if (_global_opt_append != YES) {
								// názov executable resp. include dir sme zmenili hneď v getArgv() (lebo budeme meniť adresár)
								if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
									sprintf(dir_name, DIRNAME_EXPORT_MONTH_SIMPLE, r_from % 100, m_from + 1, nazov_mes[m_from]);
								}
								else {
									// EXPORT_DATE_FULL
									sprintf(dir_name, DIRNAME_EXPORT_MONTH_FULL, r_from, m_from + 1, nazov_mesiaca_asci(m_from));
								}
								// m_to resp. m_from: sú hodnoty 0--11, resp. VSETKY_MESIACE resp. UNKNOWN_MESIAC
								Log("začínam pre adresár %s...\n", dir_name);
								sprintf(system_command, CMD_MKDIR" \"%s\"\n", dir_name);
								Log(CMD_MKDIR" \"%s\"\n", dir_name);
								// fprintf(batch_file, system_command);
								system(system_command);
								fprintf(batch_file, "cd \"%s\"\n", dir_name);
								Log("cd \"%s\"\n", dir_name);
							}// if (_global_opt_append != YES) -- nie pre append
							som_dnu = ANO;
							// ak je začiatok obdobia prvého v mesiaci, nastavím
							if (d_from == 1) {
								prveho_v_mesiaci = ANO;
							}
							// otvorím aj súbor pre jednotlivý mesiac
							mystrcpy(name_batch_month_file, dir_name, MAX_STR);
							strcat(name_batch_month_file, STR_PATH_SEPARATOR);
							strcat(name_batch_month_file, _global_export_navig_hore /* DEFAULT_MONTH_EXPORT */);
							batch_month_file = fopen(name_batch_month_file, "wt");
							if (batch_month_file != NULL) {
								Log("batch mode: File `%s' opened for writing... (batch_month_file/2)\n", name_batch_month_file);
								_batch_mode_header(m_from, r_from);

								// začiatok zoznamu
								fprintf(batch_month_file, "<ul>\n");
								index_pre_mesiac_otvoreny = ANO;
							}
						}
						if (r_from < r_to) {
							Log("batch mode: viacero rokov (%d-%d)...\n", r_from, r_to);
							// analyzujem prvy rok (r_from). potom pre jednotlive dni az do konca roka robim: _rozbor_dna a _export_rozbor_dna_batch
							Log("rok %d...\n", r_from);
							analyzuj_rok(r_from);
							for (i = poradie(d_from, m_from + 1, r_from); i <= poradie(31, MES_DEC + 1, r_from); i++) {
								Log("%d. den v roku %d...\n", i, r_from);
								// doplnenie nastavenia premenných kvôli tomu, že v batch móde používame viackrát
								Log("setting _global_opt[OPT_3_SPOLOCNA_CAST]...\n");
								_global_opt[OPT_3_SPOLOCNA_CAST] = MODL_SPOL_CAST_NEURCENA;
								d_a_m = por_den_mesiac(i, r_from);
								d = d_a_m.den;
								m = d_a_m.mesiac;
								if (_global_opt_batch_monthly == ANO && d == 1) { // ak je prvého, treba vytvoriť nový adresár
									LOG_ciara;
									Log("batch mode (viacero rokov): nový mesiac -- %s %d...\n", nazov_mesiaca(m - 1), r_from);
									// nie pre append (netreba vytvárať adresáre [mkdir] ani po nich chodiť [cd])
									if (_global_opt_append != YES) {
										// exportovanie do adresárov po mesiacoch
										if (som_dnu == ANO) {
											fprintf(batch_file, "cd ..\n");
											Log("cd ..\n");
											som_dnu = NIE;
										}
										// zatvorenie súboru (index.htm) pre jednotlivý mesiac
										if (index_pre_mesiac_otvoreny == ANO) {
											fprintf(batch_month_file, "</ul>\n");
											patka(batch_month_file);
											fclose(batch_month_file);
											Log("batch mode: export pre predošlý mesiac skončený, súbor %s zatvorený.\n", name_batch_month_file);
											index_pre_mesiac_otvoreny = NIE;
										}
										// názov executable resp. include dir sme zmenili hneď v getArgv() (lebo budeme meniť adresár)
										if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
											sprintf(dir_name, DIRNAME_EXPORT_MONTH_SIMPLE, r_from % 100, m, nazov_mes[m - 1]);
										}
										else {
											// EXPORT_DATE_FULL
											sprintf(dir_name, DIRNAME_EXPORT_MONTH_FULL, r_from, m, nazov_mesiaca_asci(m - 1));
										}
										sprintf(system_command, CMD_MKDIR" \"%s\"\n", dir_name);
										Log(CMD_MKDIR" \"%s\"\n", dir_name);
										// fprintf(batch_file, system_command);
										system(system_command);
										fprintf(batch_file, "cd \"%s\"\n", dir_name);
										Log("cd \"%s\"\n", dir_name);
									}// if (_global_opt_append != YES) -- nie pre append
									som_dnu = ANO;
									// otvorím aj súbor pre jednotlivý mesiac
									mystrcpy(name_batch_month_file, dir_name, MAX_STR);
									strcat(name_batch_month_file, STR_PATH_SEPARATOR);
									strcat(name_batch_month_file, _global_export_navig_hore /* DEFAULT_MONTH_EXPORT */);
									batch_month_file = fopen(name_batch_month_file, "wt");
									if (batch_month_file != NULL) {
										Log("batch mode: File `%s' opened for writing... (batch_month_file/3)\n", name_batch_month_file);
										_batch_mode_header(m - 1, r_from);

										// začiatok zoznamu
										fprintf(batch_month_file, "<ul>\n");
										index_pre_mesiac_otvoreny = ANO;
									}
								}// if (_global_opt_batch_monthly == ANO && d == 1)
								_rozbor_dna(d_a_m, r_from); // _struct_den_mesiac je typ, ktory vrati _rozbor_dna();
								_export_rozbor_dna_batch(EXPORT_DNA_JEDEN_DEN);
							}// for i

							// teraz pre roky (r_from + 1) az (r_to - 1) robim to, co predtym, cize analyzujem rok a pre vsetky dni - tentokrat pre cele roky, 
							// od 1.1. do 31.12. - robim _rozbor_dna a _export_rozbor_dna_batch
							for (short int y = (r_from + 1); y < r_to; y++) {
								Log("rok %d...\n", y);
								analyzuj_rok(y);
								for (i = poradie(1, MES_JAN + 1, y); i <= poradie(31, MES_DEC + 1, y); i++) {
									Log("%d. den v roku %d...\n", i, y);
									// doplnenie nastavenia premenných kvôli tomu, že v batch móde používame viackrát
									Log("setting _global_opt[OPT_3_SPOLOCNA_CAST]...\n");
									_global_opt[OPT_3_SPOLOCNA_CAST] = MODL_SPOL_CAST_NEURCENA;
									d_a_m = por_den_mesiac(i, y);
									d = d_a_m.den;
									m = d_a_m.mesiac;
									if (_global_opt_batch_monthly == ANO && d == 1) { // ak je prvého, treba vytvoriť nový adresár
										LOG_ciara;
										Log("batch mode (vnútorné celé roky): nový mesiac -- %s %d...\n", nazov_mesiaca(m - 1), y);
										// nie pre append (netreba vytvárať adresáre [mkdir] ani po nich chodiť [cd])
										if (_global_opt_append != YES) {
											// exportovanie do adresárov po mesiacoch
											if (som_dnu == ANO) {
												fprintf(batch_file, "cd ..\n");
												Log("cd ..\n");
												som_dnu = NIE;
											}
											// 2009-08-03: zatvorenie súboru (index.htm) pre jednotlivý mesiac
											if (index_pre_mesiac_otvoreny == ANO) {
												fprintf(batch_month_file, "</ul>\n");
												patka(batch_month_file);
												fclose(batch_month_file);
												Log("batch mode: export pre predošlý mesiac skončený, súbor %s zatvorený.\n", name_batch_month_file);
												index_pre_mesiac_otvoreny = NIE;
											}
											// názov executable resp. include dir sme zmenili hneď v getArgv() (lebo budeme meniť adresár)
											if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
												sprintf(dir_name, DIRNAME_EXPORT_MONTH_SIMPLE, y % 100, m, nazov_mes[m - 1]);
											}
											else {
												// EXPORT_DATE_FULL
												sprintf(dir_name, DIRNAME_EXPORT_MONTH_FULL, y, m, nazov_mesiaca_asci(m - 1));
											}
											sprintf(system_command, CMD_MKDIR" \"%s\"\n", dir_name);
											Log(CMD_MKDIR" \"%s\"\n", dir_name);
											// fprintf(batch_file, system_command);
											system(system_command);
											fprintf(batch_file, "cd \"%s\"\n", dir_name);
											Log("cd \"%s\"\n", dir_name);
										}// if (_global_opt_append != YES) -- nie pre append
										som_dnu = ANO;
										// otvorím aj súbor pre jednotlivý mesiac
										mystrcpy(name_batch_month_file, dir_name, MAX_STR);
										strcat(name_batch_month_file, STR_PATH_SEPARATOR);
										strcat(name_batch_month_file, _global_export_navig_hore /* DEFAULT_MONTH_EXPORT */);
										batch_month_file = fopen(name_batch_month_file, "wt");
										if (batch_month_file != NULL) {
											Log("batch mode: File `%s' opened for writing... (batch_month_file/4)\n", name_batch_month_file);
											_batch_mode_header(m - 1, y);

											// začiatok zoznamu
											fprintf(batch_month_file, "<ul>\n");
											index_pre_mesiac_otvoreny = ANO;
										}
									}
									_rozbor_dna(d_a_m, y);
									_export_rozbor_dna_batch(EXPORT_DNA_JEDEN_DEN);
								}// for i
								Log("...(rok %d) skoncil.\n", y);
							}// for y

							// napokon analyzujem posledny rok (r_to). pre jednotlive dni az do dna (d_to, m_to) robim: _rozbor_dna a _export_rozbor_dna_batch
							Log("rok %d...\n", r_to);
							analyzuj_rok(r_to);
							for (i = poradie(1, MES_JAN + 1, r_to); i <= poradie(d_to, m_to + 1, r_to); i++) {
								Log("%d. den v roku %d...\n", i, r_to);
								// doplnenie nastavenia premenných kvôli tomu, že v batch móde používame viackrát
								Log("setting _global_opt[OPT_3_SPOLOCNA_CAST]...\n");
								_global_opt[OPT_3_SPOLOCNA_CAST] = MODL_SPOL_CAST_NEURCENA;
								d_a_m = por_den_mesiac(i, r_to);
								d = d_a_m.den;
								m = d_a_m.mesiac;
								if (_global_opt_batch_monthly == ANO && d == 1) { // ak je prvého, treba vytvoriť nový adresár
									LOG_ciara;
									Log("batch mode (od začiatku roka): nový mesiac -- %s %d...\n", nazov_mesiaca(m - 1), r_to);
									// nie pre append (netreba vytvárať adresáre [mkdir] ani po nich chodiť [cd])
									if (_global_opt_append != YES) {
										// exportovanie do adresárov po mesiacoch
										if (som_dnu == ANO) {
											fprintf(batch_file, "cd ..\n");
											Log("cd ..\n");
											som_dnu = NIE;
										}
										// zatvorenie súboru (index.htm) pre jednotlivý mesiac
										if (index_pre_mesiac_otvoreny == ANO) {
											fprintf(batch_month_file, "</ul>\n");
											patka(batch_month_file);
											fclose(batch_month_file);
											Log("batch mode: export pre predošlý mesiac skončený, súbor %s zatvorený.\n", name_batch_month_file);
											index_pre_mesiac_otvoreny = NIE;
										}
										// názov executable resp. include dir sme zmenili hneď v getArgv() (lebo budeme meniť adresár)
										if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
											sprintf(dir_name, DIRNAME_EXPORT_MONTH_SIMPLE, r_to % 100, m, nazov_mes[m - 1]);
										}
										else {
											// EXPORT_DATE_FULL
											sprintf(dir_name, DIRNAME_EXPORT_MONTH_FULL, r_to, m, nazov_mesiaca_asci(m - 1));
										}
										sprintf(system_command, CMD_MKDIR" \"%s\"\n", dir_name);
										Log(CMD_MKDIR" \"%s\"\n", dir_name);
										// fprintf(batch_file, system_command);
										system(system_command);
										fprintf(batch_file, "cd \"%s\"\n", dir_name);
										Log("cd \"%s\"\n", dir_name);
									}// if (_global_opt_append != YES) -- nie pre append
									som_dnu = ANO;
									// otvorím aj súbor pre jednotlivý mesiac
									mystrcpy(name_batch_month_file, dir_name, MAX_STR);
									strcat(name_batch_month_file, STR_PATH_SEPARATOR);
									strcat(name_batch_month_file, DEFAULT_MONTH_EXPORT);
									batch_month_file = fopen(name_batch_month_file, "wt");
									if (batch_month_file != NULL) {
										Log("batch mode: File `%s' opened for writing... (batch_month_file/5)\n", name_batch_month_file);
										_batch_mode_header(m - 1, r_to);

										// začiatok zoznamu
										fprintf(batch_month_file, "<ul>\n");
										index_pre_mesiac_otvoreny = ANO;
									}
								}
								_rozbor_dna(d_a_m, r_to);
								_export_rozbor_dna_batch(EXPORT_DNA_JEDEN_DEN);
							}// for i
						}// r_from < r_to -- viacero rokov
						else {
							Log("batch mode: v rámci jedného roka (%d)...\n", r_from);
							// analyzujem ten jeden rok. potom pre jednotlive dni robim: _rozbor_dna a _export_rozbor_dna_batch
							analyzuj_rok(r_from);
							for (i = poradie(d_from, m_from + 1, r_from); i <= poradie(d_to, m_to + 1, r_to); i++) {
								Log("%d. den v roku %d...\n", i, r_from);
								// doplnenie nastavenia premenných kvôli tomu, že v batch móde používame viackrát
								Log("setting _global_opt[OPT_3_SPOLOCNA_CAST]...\n");
								_global_opt[OPT_3_SPOLOCNA_CAST] = MODL_SPOL_CAST_NEURCENA;
								d_a_m = por_den_mesiac(i, r_from);
								d = d_a_m.den;
								m = d_a_m.mesiac;
								if (_global_opt_batch_monthly == ANO && d == 1 && prveho_v_mesiaci == NIE) { // ak je prvého, treba vytvoriť nový adresár; 2011-09-30: nevytvárame vtedy, ak už bol vyššie vytvorený
									LOG_ciara;
									Log("batch mode (v rámci jedného roka): nový mesiac -- %s %d...\n", nazov_mesiaca(m - 1), r_from /* == r_to */);
									// nie pre append (netreba vytvárať adresáre [mkdir] ani po nich chodiť [cd])
									if (_global_opt_append != YES) {
										// exportovanie do adresárov po mesiacoch
										if (som_dnu == ANO) {
											fprintf(batch_file, "cd ..\n");
											Log("cd ..\n");
											som_dnu = NIE;
										}
										// zatvorenie súboru (index.htm) pre jednotlivý mesiac
										if (index_pre_mesiac_otvoreny == ANO) {
											fprintf(batch_month_file, "</ul>\n");
											patka(batch_month_file);
											fclose(batch_month_file);
											Log("batch mode: export pre predošlý mesiac skončený, súbor %s zatvorený.\n", name_batch_month_file);
											index_pre_mesiac_otvoreny = NIE;
										}
										// názov executable resp. include dir sme zmenili hneď v getArgv() (lebo budeme meniť adresár)
										if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE) {
											sprintf(dir_name, DIRNAME_EXPORT_MONTH_SIMPLE, r_from % 100, m, nazov_mes[m - 1]);
										}
										else {
											// EXPORT_DATE_FULL
											sprintf(dir_name, DIRNAME_EXPORT_MONTH_FULL, r_from, m, nazov_mesiaca_asci(m - 1));
										}
										sprintf(system_command, CMD_MKDIR" \"%s\"\n", dir_name);
										Log(CMD_MKDIR" \"%s\"\n", dir_name);
										// fprintf(batch_file, system_command);
										system(system_command);
										fprintf(batch_file, "cd \"%s\"\n", dir_name);
										Log("cd \"%s\"\n", dir_name);
									}// if (_global_opt_append != YES) -- nie pre append
									som_dnu = ANO;
									// otvorím aj súbor pre jednotlivý mesiac
									mystrcpy(name_batch_month_file, dir_name, MAX_STR);
									strcat(name_batch_month_file, STR_PATH_SEPARATOR);
									strcat(name_batch_month_file, _global_export_navig_hore /* DEFAULT_MONTH_EXPORT */);
									batch_month_file = fopen(name_batch_month_file, "wt");
									if (batch_month_file != NULL) {
										Log("batch mode: File `%s' opened for writing... (batch_month_file/6)\n", name_batch_month_file);
										_batch_mode_header(m - 1, r_from);

										// začiatok zoznamu
										fprintf(batch_month_file, "<ul>\n");
										index_pre_mesiac_otvoreny = ANO;
									}
								}// _global_opt_batch_monthly == ANO && d == 1 && prveho_v_mesiaci == NIE
								prveho_v_mesiaci = NIE;
								_rozbor_dna(d_a_m, r_from);
								_export_rozbor_dna_batch(EXPORT_DNA_JEDEN_DEN);
							}// for i
						}// r_from == r_to
					}// else if (_global_opt_batch_monthly == ANO && export_monthly_druh >= 1)
					if (_global_opt_batch_monthly == ANO) {
						// zatvorenie súboru (index.htm) pre jednotlivý mesiac
						if (index_pre_mesiac_otvoreny == ANO) {
							fprintf(batch_month_file, "</ul>\n");
							patka(batch_month_file);
							fclose(batch_month_file);
							Log("batch mode: export pre posledný mesiac skončený, súbor zatvorený; toto bol posledný súbor %s.\n", _global_export_navig_hore /* DEFAULT_MONTH_EXPORT */);
							index_pre_mesiac_otvoreny = NIE;
						}
						// nie pre append (netreba vytvárať adresáre [mkdir] ani po nich chodiť [cd])
						if (_global_opt_append != YES) {
							// exportovanie do adresárov po mesiacoch -- vrátime sa späť
							if (som_dnu == ANO) {
								fprintf(batch_file, "cd ..\n");
								Log("cd ..\n");
								som_dnu = NIE;
							}
						}// if (_global_opt_append != YES) -- nie pre append
					}// if (_global_opt_batch_monthly == ANO)

					// koniec zoznamu
					fprintf(batch_html_file, "</ul>\n");

					// prilepenie pätky
					patka(batch_html_file);

					// zatvorenie súboru
					fclose(batch_html_file);
					Log("batch mode: ...celé zadané obdobie je spracované; súbor %s zatvorený.\n", name_batch_html_file);
					LOG_ciara;
				}// batch_html_file != NULL
				else {
					Export("Nemôžem písať do súboru `%s'.\n", name_batch_html_file);
					Log("batch mode: Cannot open file `%s' for writing.\n", name_batch_html_file);
				}// batch_html_file == NULL)
				// ...a sranda skoncila
				fclose(batch_file);
			}// ok, batch_file != NULL
			else {
				Export("Nemôžem písať do súboru `%s'.\n", name_batch_file);
				Log("Cannot open file `%s' for writing.\n", name_batch_file);
			}// batch_file == NULL
		}// name_batch_file != STR_EMPTY
		else {
			Export("Nezadané meno batch súboru (použite parameter `%s').\n", STR_PRM_BATCH_MODE);
			Log("Batch filename empty (use `%s' parameter).\n", STR_PRM_BATCH_MODE);
		}
	}// result == SUCCESS
}// _main_batch_mode()

#ifdef OS_linux
extern char **environ;
#endif
void write(void) {
	short int i = 0;
	while (environ[i]) {
		// if (strstr(environ[i], "WWW_") != NULL)
		Log(HTML_P_BEGIN"%d: %s" HTML_LINE_BREAK "__________" HTML_LINE_BREAK, i, environ[i]);
		i++;
	}
}

// popis: zisti, ktory z parametrov je pouzity; ostatne sa zisti z WWW_...
// vracia: on error, returns PRM_NONE or PRM_UNKNOWN
//         on success, returns PRM_DATUM, PRM_SVIATOK or PRM_CEZ_ROK | (09/02/2000A.D.: pridane PRM_DETAILY) | 2011-01-25: pridane PRM_LIT_OBD
// return values #define'd in mydefs.h
short int getQueryTypeFrom_QS(char *qs) {
	Log("getQueryTypeFrom_QS() -- begin\n");
	Log("  qs == %s\n", qs);

	if (strstr(qs, STR_PRM_DATUM) != NULL) {
		// parameter STR_PRM_DATUM
		Log("getQueryTypeFrom_QS() -- end, returning PRM_DATUM\n");
		return PRM_DATUM;
	}
	else if (strstr(qs, STR_PRM_DETAILY) != NULL) {
		// parameter STR_PRM_DETAILY
		Log("getQueryTypeFrom_QS() -- end, returning PRM_DETAILY\n");
		return PRM_DETAILY; // pridane kvoli formularu 'Detaily...'
	}
	else if (strstr(qs, STR_PRM_CEZ_ROK) != NULL) {
		// parameter STR_PRM_CEZ_ROK
		Log("getQueryTypeFrom_QS() -- end, returning PRM_CEZ_ROK\n");
		return PRM_CEZ_ROK;
	}
	else if (strstr(qs, STR_PRM_LIT_OBD) != NULL) {
		// parameter STR_PRM_LIT_OBD
		Log("getQueryTypeFrom_QS() -- end, returning PRM_LIT_OBD\n");
		return PRM_LIT_OBD;
	}
	else if (strstr(qs, STR_PRM_SVIATOK) != NULL) {
		// parameter STR_PRM_SVIATOK
		Log("getQueryTypeFrom_QS() -- end, returning PRM_SVIATOK\n");
		return PRM_SVIATOK;
	}
	else if (strstr(qs, STR_PRM_ANALYZA_ROKU) != NULL) {
		// parameter STR_PRM_ANALYZA_ROKU
		Log("getQueryTypeFrom_QS() -- end, returning PRM_ANALYZA_ROKU\n");
		return PRM_ANALYZA_ROKU;
	}
	else if (strstr(qs, STR_PRM_DNES) != NULL) {
		// parameter STR_PRM_DNES
		Log("getQueryTypeFrom_QS() -- end, returning PRM_DNES\n");
		return PRM_DNES;
	}
	else if (strstr(qs, STR_PRM_MESIAC_ROKA) != NULL) {
		// parameter STR_PRM_MESIAC_ROKA
		Log("getQueryTypeFrom_QS() -- end, returning PRM_MESIAC_ROKA\n");
		return PRM_MESIAC_ROKA;
	}
	else if (strstr(qs, STR_PRM_TABULKA) != NULL) {
		// parameter STR_PRM_TABULKA
		Log("getQueryTypeFrom_QS() -- end, returning PRM_TABULKA\n");
		return PRM_TABULKA;
	}
	else if (strstr(qs, STR_PRM_BATCH_MODE) != NULL) {
		// parameter STR_PRM_BATCH_MODE
		Log("getQueryTypeFrom_QS() -- end, returning PRM_BATCH_MODE\n");
		return PRM_BATCH_MODE;
	}
	else if (strstr(qs, STR_PRM_STATIC_TEXT) != NULL) {
		// parameter STR_PRM_STATIC_TEXT
		Log("getQueryTypeFrom_QS() -- end, returning PRM_STATIC_TEXT\n");
		return PRM_STATIC_TEXT;
	}
	else {
		Log("getQueryTypeFrom_QS() -- end, returning PRM_UNKNOWN\n");
		return PRM_UNKNOWN; // argumenty neobsahuju STR_PRM_...
	}
}// getQueryTypeFrom_QS()

short int getQueryTypeFrom_WWW(void) {
	char *ptr;
	short int ret;

	Log("getQueryTypeFrom_WWW() -- begin\n");
	ptr = getenv(ADD_WWW_PREFIX_(STR_QUERY_TYPE)); // zistim, ci je to z formulara

	if (ptr == NULL) {
		// nie, dotaz nie je spusteny z formulara
		Log("getQueryTypeFrom_WWW() -- end, returning PRM_NONE\n");
		ret = PRM_NONE; // aj bez parametrov WWW_...
	}
	// v tomto pripade existuje premenna WWW_QUERY_TYPE
	else if (equals(ptr, STR_PRM_DATUM)) {
		Log("getQueryTypeFrom_WWW() -- end, returning PRM_DATUM\n");
		ret = PRM_DATUM;
	}
	// toto tu nemusi byt, lebo PRM_DETAILY sa pouziva len pre tlacidlo 'Detaily...', aby sa dalo odlisit od uvodneho formulara 
	// -- kedysi sa tam miesala modlitba (pole WWW_MODLITBA) z option 'PRM_CEZ_ROK', ktora sa aplikovala aj na option 'PRM_DATUM'
	else if (equals(ptr, STR_PRM_DETAILY)) {
		Log("getQueryTypeFrom_WWW() -- end, returning PRM_DETAILY\n");
		ret = PRM_DETAILY;
	}
	else if (equals(ptr, STR_PRM_CEZ_ROK)) {
		Log("getQueryTypeFrom_WWW() -- end, returning PRM_CEZ_ROK\n");
		ret = PRM_CEZ_ROK;
	}
	else if (equals(ptr, STR_PRM_LIT_OBD)) {
		Log("getQueryTypeFrom_WWW() -- end, returning PRM_LIT_OBD\n");
		ret = PRM_LIT_OBD;
	}
	else if (equals(ptr, STR_PRM_SVIATOK)) {
		Log("getQueryTypeFrom_WWW() -- end, returning PRM_SVIATOK\n");
		ret = PRM_SVIATOK;
	}
	else if (equals(ptr, STR_PRM_ANALYZA_ROKU)) {
		Log("getQueryTypeFrom_WWW() -- end, returning PRM_ANALYZA_ROKU\n");
		ret = PRM_ANALYZA_ROKU;
	}
	else if (equals(ptr, STR_PRM_DNES)) {
		Log("getQueryTypeFrom_WWW() -- end, returning PRM_DNES\n");
		ret = PRM_DNES;
	}
	else if (equals(ptr, STR_PRM_MESIAC_ROKA)) {
		Log("getQueryTypeFrom_WWW() -- end, returning PRM_MESIAC_ROKA\n");
		ret = PRM_MESIAC_ROKA;
	}
	else if (equals(ptr, STR_PRM_TABULKA)) {
		Log("getQueryTypeFrom_WWW() -- end, returning PRM_TABULKA\n");
		ret = PRM_TABULKA;
	}
	// nie je tu PRM_BATCH_MODE, pretoze batch mode nie je urceny pre web, 2003-07-04
	else {
		Log("getQueryTypeFrom_WWW() -- end, returning PRM_UNKNOWN\n");
		ret = PRM_UNKNOWN; // failure
	}
	return ret;
}// getQueryTypeFrom_WWW();

// popis: naplni premenne pom_... hodnotami, ktore boli dodane ako sucast argumentu
//        napriklad "-q PRM_DATUM -1 7 -2 5 -3 1976" vrati query_type == PRM_DATUM; pom_DEN == 7; pom_MESIAC == 5; pom_ROK == 1976
// vracia: on success, returns SUCCESS
//         on error,   returns FAILURE
// popritom: nastavi do query_type to, co by malo byt po switchi -q
short int getArgv(int argc, const char** argv) {
	short int c;
	optind = 0; // pokial tu toto nebolo, tak getopt sa neinicializovala pri dalsich volaniach
	char* option_string;
	char pom_name_binary_executable[MAX_STR] = STR_EMPTY; // 2009-08-02: doplnené pre prilepenie ..\ pred názov name_binary_executable
	char pom_include_dir[MAX_STR] = STR_EMPTY; // 2009-08-02: doplnené pre prilepenie ..\ pred názov include_dir

	Log("allocating memory for option_string...\n");
	// allocate memory for string
	if ((option_string = (char*)malloc(MAX_STR)) == NULL) {
		Log("Not enough memory to allocate buffer, so returning FAILURE\n");
		//printf("Not enough memory to allocate buffer (getArgv(), char *option_string)\n");
		// exit(1); -- terminate program if out of memory
		return FAILURE;
	}

	// option_string obsahuje options (case sensitive)
	// 24/02/2000A.D.: odstranil som `e' switch -- sposoboval problemy;
	// pismeno `s' je pouzite na debuggovacie ucely pre zadanie uplneho query stringu;
	// 13/03/2000A.D.: znova som pridal `e' switch; tentokrat uz prirobene closeExport() a initExport(char*) v myexpt.[h|cpp]
	// 15/03/2000A.D.: pridal som parametre
	//  `f' (rok from), `g' (rok to), `l' (hyperlinky) pre -qptab
	// 05/06/2000A.D.: pridany parameter `i' (include directory)
	// 2003-07-04: pridane nasledovne parametre:
	//            `n' (name of binary executable) -> name_binary_executable
	//            `b' (name of generated batch file, analogia exportu, `e') -> name_batch_file
	// 2003-07-08: pridany nasledovny parameter:
	//            `a' (append) aby pri exportovani do suboru (-e) appendoval, nie prepisal subor
	// 2004-03-16: pridany nasledovny parameter:
	//            `k' (hyperteKst) aby pri exportovani v batch mode pisal do HTML suboru zoznam modlitieb
	// 2010-08-04: význam parametra `k' zmenený; pre pôvodný význam sa používa `o' (Output)
	// 2006-07-12: pridaný nasledovný parameter:
	//            `j' (Jazyk) jazyková mutácia, zatiaľ sk, cz
	// 2008-08-08: pridaný nasledovný parameter:
	//            `c' (css) použité css
	// 2008-11-29: pridaný nasledovný parameter:
	//            `u' (dátUm) spôsob zapisovania dátumu pre súbory v batch móde
	// 2009-08-02: pridaný nasledovný parameter:
	//            `M' (Monthly) spôsob zapisovania v batch móde do adresárov po mesiacoch
	// 2010-08-04: pridaný nasledovný parameter:
	//            `k' (Kalendár) špecifikácia prípadného lokálneho (rehoľného) kalendára, súvisí s parametrom 'j' (jazyk)
	// 2010-11-29: pridané nasledovné parametre:
	//            `H' (header) špeciálne správanie pre 2. až predposledný súbor generovaný append režimom (-a1): includovanie hlavičky
	//            `F' (footer) špeciálne správanie pre 2. až predposledný súbor generovaný append režimom (-a1): includovanie pätky
	// 2011-04-13: upravené (pridaná option 0 a odstránené od čísla 5 až po 9)
	// 2011-05-06: upravené (hodnota `F' ani `H' sa nepoužívali)
	//            `F' (font): možnosť zvoliť font pre override CSS
	// 2012-09-07: 'H' (header) disables header and footer
	// 2021-07-13: 'T' (font size pT) force font size in pt

	// 2021-07-13: 'y', 'v' and 'w' are still available :)
	mystrcpy(option_string, "?q::d::m::r::p::x::s::t::0::1::2::3::4::5::a::h::e::f::g::l::i::\?::b::n::o::k::j::c::u::M::I::H::F::S::T::G::L", MAX_STR);
	// tie options, ktore maju za sebou : maju povinny argument; ak maju :: tak maju volitelny

	Log("-- getArgv(): begin\n");
	DEBUG_GET_ARGV("argc == %d\n", argc);

	if (argc == 1) {
		// bud nie su zadane ziadne hodnoty alebo cerpam z premennych WWW_
		// sem sa to nemalo dostat, pretoze najprv sme pouzili get_query_type()

		// keby sa to sem vsak predsalen dostalo, dame sem nasledujucu pasaz, aby sme mohli exportovat, pretoze pred pouzitim getArgv nie je otvoreny fajl FILE_EXPORT
		DEBUG_GET_ARGV("Nezadane ziadne argumenty (argc == 1).\n");
		ALERT;
		Export("Obslužnému programu neboli zadané žiadne argumenty.\n");
		Export(HTML_P_BEGIN"getArgv();\n");
		return FAILURE; // nie su argumenty
	}
	else {
		Log("option_string == %s\n", option_string);
		for (c = 0; c < argc; c++)
			Log("argv[%d] == %s\n", c, argv[c]);
		// hodnoty su v dialogovom riadku
		// zistujeme ich cez standardne mygetopt.c
		while (1) {
			// this_option_optind = optind ? optind : 1;
			c = getopt(argc, argv, option_string);
			if (c == -1) // uz nie je option, vyskoc z while(1)
				break;
			switch (c) {
			case 'c':
				if (optarg != NULL) {
					mystrcpy(pom_CSS, optarg, SMALL);
				}
				Log("option %c with value `%s' -- `%s' used for css\n", c, optarg, optarg); break;

			case 'j':
				if (optarg != NULL) {
					mystrcpy(pom_JAZYK, optarg, SMALL);
				}
				Log("option %c with value `%s' -- `%s' used for language mutation\n", c, optarg, optarg); break;
			case 'k':
				if (optarg != NULL) {
					mystrcpy(pom_KALENDAR, optarg, SMALL);
				}
				Log("option %c with value `%s' -- `%s' used for calendar mutation\n", c, optarg, optarg); break;
			case 'o':
				if (optarg != NULL) {
					mystrcpy(name_batch_html_file, optarg, SMALL);
				}
				Log("option %c with value `%s' -- batch file HTML name `%s' used for batch mode\n", c, optarg, optarg); break;
			case 'b':
				if (optarg != NULL) {
					mystrcpy(name_batch_file, optarg, SMALL);
				}
				Log("option %c with value `%s' -- batch file name `%s' used for batch mode\n", c, optarg, optarg); break;
			case 'n':
				if (optarg != NULL) {
					mystrcpy(name_binary_executable, optarg, SMALL);
				}
				Log("option %c with value `%s' -- binary executable name `%s' used for batch mode\n", c, optarg, optarg); break;
			case 'i':
				if (optarg != NULL) {
					mystrcpy(include_dir, optarg, MAX_STR); // 2012-09-08: This string can be quite long on iOS
				}
				Log("option %c with value `%s' -- including files from `%s'\n", c, optarg, optarg /* 2004-03-17 zapoznamkovane FILE_PATH */); break;
			case 'f': // tabulka - rok from; pre batch mode je to DEN DO
				if (optarg != NULL) {
					mystrcpy(pom_ROK_FROM, optarg, SMALL);
				}
				Log("option %c with value `%s'\n", c, optarg); break;
			case 'F':
				if (optarg != NULL) {
					mystrcpy(pom_FONT, optarg, SMALL);
				}
				Log("option %c with value `%s'\n", c, optarg); break;
			case 'S':
				if (optarg != NULL) {
					mystrcpy(pom_FONT_SIZE, optarg, VERY_SMALL);
				}
				Log("option %c with value `%s'\n", c, optarg); break;
			case 'T':
				if (optarg != NULL) {
					mystrcpy(pom_FONT_SIZE_PT, optarg, VERY_SMALL);
				}
				Log("option %c with value `%s'\n", c, optarg); break;
			case 'G':
				if (optarg != NULL) {
					mystrcpy(pom_STYLE_MARGIN, optarg, VERY_SMALL);
				}
				Log("option %c with value `%s'\n", c, optarg); break;
			case 'L':
				if (optarg != NULL) {
					mystrcpy(pom_LINE_HEIGHT_PERC, optarg, VERY_SMALL);
				}
				Log("option %c with value `%s'\n", c, optarg); break;
			case 'g': // tabulka - rok to; pre batch mode je to MESIAC DO
				if (optarg != NULL) {
					mystrcpy(pom_ROK_TO, optarg, SMALL);
				}
				Log("option %c with value `%s'\n", c, optarg); break;
			case 'l': // tabulka - [hyper]linky
				if (optarg != NULL) {
					mystrcpy(pom_LINKY, optarg, SMALL);
				}
				Log("option %c with value `%s'\n", c, optarg); break;
			case 'e': // export filename
				if (optarg != NULL) {
					mystrcpy(file_export, optarg, SMALL);
				}
				Log("option %c with value `%s'\n", c, optarg); break;
			case 's': // debuggovanie, query string
				if (optarg != NULL) {
					Log("--copying `%s' to query_string...", optarg);
					mystrcpy(query_string, optarg, MAX_QUERY_STR);
					// to mozeme urobit; predtym, ked sme este nealokovali pre query_string miesto, bolo by lepsie urobit nejaku lokalnu premennu, na ktoru by potom query_string ukazoval
					mystrcpy(pom_QUERY_TYPE, STR_PRM_SIMULACIA_QS, MAX_POM_QUERY_TYPE);
					query_type = PRM_SIMULACIA_QS;
				}
				Log("option %c with value `%s'\n", c, optarg); break;
			case 'd':
				if (optarg != NULL) {
					mystrcpy(pom_DEN, optarg, SMALL);
				}
				Log("option %c with value `%s' -- den\n", c, optarg); break;
			case 'm':
			case 't':
				if (optarg != NULL) {
					mystrcpy(pom_MESIAC, optarg, SMALL);
				}
				Log("option %c with value `%s' -- mesiac/tyzden\n", c, optarg); break;
			case 'r':
				if (optarg != NULL) {
					mystrcpy(pom_ROK, optarg, SMALL);
				}
				Log("option %c with value `%s' -- rok\n", c, optarg); break;
			case 'p':
				if (optarg != NULL) {
					mystrcpy(pom_MODLITBA, optarg, SMALL);
				}
				Log("option %c with value `%s' -- modlitba\n", c, optarg); break;
			case 'x':
				if (optarg != NULL) {
					mystrcpy(pom_DALSI_SVATY, optarg, SMALL);
				}
				Log("option %c with value `%s' -- poradie svateho\n", c, optarg); break;

				// OPT 0..5
			case '0':
				if (optarg != NULL) {
					mystrcpy(pom_OPT[OPT_0_SPECIALNE], optarg, SMALL);
				}
				Log("option %c with value `%s'\n", c, optarg); break;
			case '1':
				if (optarg != NULL) {
					mystrcpy(pom_OPT[OPT_1_CASTI_MODLITBY], optarg, SMALL);
				}
				Log("option %c with value `%s'\n", c, optarg); break;
			case '2':
				if (optarg != NULL) {
					mystrcpy(pom_OPT[OPT_2_HTML_EXPORT], optarg, SMALL);
				}
				Log("option %c with value `%s'\n", c, optarg); break;
			case '3':
				if (optarg != NULL) {
					mystrcpy(pom_OPT[OPT_3_SPOLOCNA_CAST], optarg, SMALL);
				}
				Log("option %c with value `%s'\n", c, optarg); break;
			case '4':
				if (optarg != NULL) {
					mystrcpy(pom_OPT[OPT_4_OFFLINE_EXPORT], optarg, SMALL);
				}
				Log("option %c with value `%s'\n", c, optarg); break;
			case '5':
				if (optarg != NULL) {
					mystrcpy(pom_OPT[OPT_5_ALTERNATIVES], optarg, SMALL);
				}
				Log("option %c with value `%s'\n", c, optarg); break;

			case 'a': // OPT_APPEND
				if (optarg != NULL) {
					mystrcpy(pom_OPT_APPEND, optarg, SMALL);
				}
				if (equals(pom_OPT_APPEND, STR_ANO) || equals(pom_OPT_APPEND, STR_VALUE_TRUE)) {
					_global_opt_append = ANO;
				}
				else if (equals(pom_OPT_APPEND, STR_NIE) || equals(pom_OPT_APPEND, STR_VALUE_FALSE)) {
					_global_opt_append = NIE;
				}
				Log("opt_append == `%s' (%d)\n", pom_OPT_APPEND, _global_opt_append);
				Log("option %c with value `%s'\n", c, optarg); break;

				// parameter `u' (dátUm) spôsob zapisovania dátumu pre súbory v batch móde
			case 'u': // OPT_APPEND
				if (optarg != NULL) {
					mystrcpy(pom_OPT_DATE_FORMAT, optarg, SMALL);
				}
				if (equals(pom_OPT_DATE_FORMAT, STR_FULL) || equals(pom_OPT_DATE_FORMAT, STR_VALUE_TRUE)) {
					_global_opt_export_date_format = EXPORT_DATE_FULL;
				}
				else if (equals(pom_OPT_DATE_FORMAT, STR_SIMPLE) || equals(pom_OPT_DATE_FORMAT, STR_VALUE_FALSE)) {
					_global_opt_export_date_format = EXPORT_DATE_SIMPLE;
				}
				Log("opt_append == `%s' (%d)\n", pom_OPT_DATE_FORMAT, _global_opt_export_date_format);
				Log("option %c with value `%s'\n", c, optarg); break;

			case 'q': // QUERY_TYPE
				if (optarg != NULL) {
					mystrcpy(pom_QUERY_TYPE, optarg, MAX_POM_QUERY_TYPE);
				}
				Log("option %c with value `%s'\n", c, optarg); break;

			case 'M': // typ exportu pre batch mód
				if (optarg != NULL) {
					mystrcpy(pom_EXPORT_MONTHLY, optarg, SMALL); // premenná pom_EXPORT_MONTHLY sa parsuje priamo v _main()
				}
				_global_opt_batch_monthly = ANO;
				Log("option %c with value `%s'\n", c, optarg); break;

			case 'I': // odkaz "^ hore" / index.htm (pre batch mód)
				if (optarg != NULL) {
					mystrcpy(_global_export_navig_hore, optarg, SMALL);
				}
				else {
					mystrcpy(_global_export_navig_hore, DEFAULT_MONTH_EXPORT, SMALL);
				}
				Log("option %c with value `%s'\n", c, optarg); break;

			case 'H':
				_global_hlavicka_Export = 1;
				_global_patka_Export = 1;
				Log("option '%c'\n", c); break;

			case '?':
			case 'h':
				printf("\n");
				printf("lh - command-line verzia on-line breviara (http://breviar.sk)\n");
				printf("\tProgram vytvara stranky (HTML vystup) pre Liturgiu hodin.\n");
				printf("\tBuild: %s\n", BUILD_DATE);
				printf("\t" TEXT_COPYRIGHT " <" TEXT_EMAIL ">\n");
				printf("\n");
				printf("\npouzitie:\n");
				printf("\tlh [prepinac [hodnota]...]\n");
				printf("\nprepinace:\n");
				printf("\tq  query type (napr. %s, %s, %s, %s, %s, %s...)\n",
					STR_PRM_DNES, STR_PRM_DATUM, STR_PRM_DETAILY, STR_PRM_TABULKA, STR_PRM_SIMULACIA_QS, STR_PRM_BATCH_MODE);
				printf("\ts  query string (tak ako je na webe)\n");
				printf("\td  den (%s|%s) (1--31, po--ne)\n", STR_DEN, STR_DEN_V_TYZDNI);
				// printf("\ts  SVIATOK \n");
				printf("\tm  mesiac (%s) (1--12, jan--dec)\n", STR_MESIAC);
				printf("\tt  tyzden zaltara (1--4) \n");
				printf("\tr  rok (napr. 2000)\n");
				printf("\tp  modlitba (%s): %s, %s, %s, %s, %s, %s, %s, %s, %s...) \n",
					STR_MODLITBA, STR_MODL_RANNE_CHVALY, STR_MODL_VESPERY, STR_MODL_POSV_CITANIE, STR_MODL_PREDPOLUDNIM, STR_MODL_NAPOLUDNIE, STR_MODL_POPOLUDNI, STR_MODL_DETAILY, STR_MODL_INVITATORIUM, STR_MODL_KOMPLETORIUM);
				printf("\t\t resp. rok do pre davkove spracovanie\n");
				printf("\tx  dalsi svaty (%s): 1--%d resp. %d pre lubovolnu spomienku PM v sobotu\n", STR_DALSI_SVATY, MAX_POCET_SVATY, PORADIE_PM_SOBOTA);
				printf("\t0  specialne casti modlitby (verse, referencie)\n");
				printf("\t1  prepinace pre zobrazovanie casti modlitby\n");
				printf("\t2  prepinace pre html export\n");
				printf("\t3  ktoru spolocnu cast brat, ak je ich viac (0, 1, 2, 3) \n");
				printf("\t4  prepinace pre offline export\n");
				printf("\tf  rok from (resp. den do pre davkove spracovanie)\n");
				printf("\tg  rok to (resp. mesiac do pre davkove spracovanie)\n");
				printf("\tl  ci zobrazovat linky \n");
				printf("\te  export filename (default: export.htm)\n");
				printf("\ti  include folder\n");
				printf("\tb  batch mode (davkove spracovanie), nazov vystupneho davkoveho suboru\n");
				printf("\tn  nazov binarky (tohto suboru, napr. breviar.exe) pre batch mode\n");
				printf("\to  nazov (HTML) suboru pre vysledny zoznam modlitieb, batch mode\n");
				printf("\ta  (append) pri exportovani do suboru (-e) neprepisuje subor\n");
				printf("\tj  jazyk (jazykova mutacia), zatial: sk, cz\n");
				printf("\tk  kalendar (napr. reholny)\n");
				printf("\tc  css filename (pouzite CSS)\n");
				printf("\tu  batch mode dates in file name format (0 = simple, 1 = full)\n");
				printf("\tM  pre batch mode: jednotlive mesiace su v samostatnych suboroch\n");
				printf("\t   M0 = v mesiaci dni pod sebou, modlitby pre kazdy den v riadku\n");
				printf("\t   M1 = v mesiaci podla modlitieb su dni len ako cislice\n");
				printf("\t   M2 = generovanie funkcnej offline verzie (kopie) webu\n");
				printf("\t   M3 = ako M2, ale prisposobene pre mobilne zariadenia\n");
				printf("\tI  pre batch mode: subor, kam ma odkazovat link '^ hore'\n");
				printf("\n\t   pri prepinacoch ano = 1, nie = 0\n");
				printf("\npriklady pouzitia:\n\n");
				printf("breviar.exe -i..\\..\\..\\ -qpsqs -s\"qt=pdt&d=12&m=7&r=2003\"\n");
				printf("breviar -qpdt -d30 -m4 -r2002 -pmrch -ic:\\temp\\breviar\\ -emoja.htm\n");
				printf("breviar.exe -i..\\..\\..\\ -d28 -m6 -r2003 -qpdt -pmrch -x1\n");
				printf("breviar -qpbm -d1 -m1 -r2000 -f2 -g2 -p2000 -ba.bat -nbrev.exe -ic:\\breviar\\\n");
				printf("breviar.exe -qpbm -d1 -m8 -r2009 -f30 -g9 -p2009 -11 -brob.bat -jsk -nbreviar.exe -i..\\..\\www.breviar.sk\\include\\ -ufull -M3\n");
				printf("\nviac informacii:\n");
				printf("\thttp://breviar.sk - hlavna stranka\n");
				printf("\thttp://breviar.sk/info/parametre.htm - o parametroch\n");
				printf("\thttp://breviar.sk/info/batchmode.htm - o davkovom mode (batch mode)\n");

				Log("option %c (without value)\n", c, optarg);
				break;
			default:
				// znamena option uvedenu v optionstringu, pre ktoru nebolo definovane case vyssie
				Log("?? getopt returned character `%c' ??\n", c);
				break;
			} // switch
		}// while
		if (optind < argc) {
			Log("non-option ARGV-elements: ");
			while (optind < argc)
				Log("%s ", argv[optind++]);
			Log("\n");
		}

		// dokoncili sme parsovanie options (switchov apod), a teraz rozoberieme, co sme zistili

		// najprv nakopirujeme chybovu hlasku do bad_param_str
		if (equals(pom_QUERY_TYPE, STR_EMPTY)) {
			mystrcpy(bad_param_str, "<" HTML_SPAN_BOLD ">nijaký parameter PRM_..." HTML_SPAN_END, MAX_STR);
		}
		else {
			mystrcpy(bad_param_str, pom_QUERY_TYPE, MAX_STR);
			strcat(bad_param_str, " (switch <" HTML_SPAN_BOLD ">-q" HTML_SPAN_END ")");
		}
		// a teraz vydolujeme typ dotazu
		// vynecham to v pripade, ze pom_QUERY_TYPE == STR_PRM_SIMULACIA_QS, t.j. query_type == PRM_SIMULACIA_QS
		if (query_type != PRM_SIMULACIA_QS) {
			Log("query_type != PRM_SIMULACIA_QS, so running getQueryTypeFrom_QS(%s)...\n", pom_QUERY_TYPE);
			query_type = getQueryTypeFrom_QS(pom_QUERY_TYPE);
		}

		// ak je query type OK, tak vymažeme chybový oznam
		if (query_type != PRM_UNKNOWN) {
			Log("query_type OK, čistím bad_param_str...\n");
			mystrcpy(bad_param_str, STR_EMPTY, MAX_STR);
		}

		// pri exportovaní do adresárov po mesiacoch je potrebné upraviť name_binary_executable resp. include_dir, ale len v batch móde (teda nie pre jednotlivú generovanú modlitbu) -- preto presunuté až sem, za zistenie query_type
		if (query_type == PRM_BATCH_MODE && _global_opt_batch_monthly == ANO) {
			mystrcpy(pom_name_binary_executable, STR_EMPTY, MAX_STR);
			mystrcpy(pom_include_dir, STR_EMPTY, MAX_STR);
			// 2012-12-12: nie pre append (netreba vytvárať adresáre [mkdir] ani po nich chodiť [cd])
			if (_global_opt_append != YES) {
				// musíme upraviť názov executable, lebo budeme meniť adresár v _main_batch_mode()
				mystrcpy(pom_name_binary_executable, ".." STR_PATH_SEPARATOR, MAX_STR);
				// musíme upraviť názov adresára s include, lebo budeme meniť adresár v _main_batch_mode()
				mystrcpy(pom_include_dir, ".." STR_PATH_SEPARATOR, MAX_STR);
			}
			strcat(pom_name_binary_executable, name_binary_executable);
			mystrcpy(name_binary_executable, pom_name_binary_executable, MAX_STR);
			strcat(pom_include_dir, include_dir);
			mystrcpy(include_dir, pom_include_dir, MAX_STR);
		}// len pre batch mód, mesačne
	}// else vetva podmienky if (argc == 1)

	Log("deallocating memory for option_string...\n");
	free(option_string);

	Log("-- getArgv(): end, query_type == %d, query_string == %s, bad_param_str == %s\n", query_type, query_string, bad_param_str);

	return SUCCESS;
}// getArgv();

// popis: naplni premenne pom_... hodnotami z environmentu, t.j. premennymi WWW_ ktore vrati uncgi.c
// vracia: on success, returns SUCCESS
//         on error,   returns FAILURE
// 2005-03-30: Upravene. 
// Ak hodnoty su v pom_ premennych, nepotrebujem citat z WWW_ premennych.
// V opacnom pripade to na linux::apache vypisovalo pre tlacidla (Dalsi den >>) ze nie su vytvorene premenne WWW_d a podobne, hoci boli v query stringu.
// Mozno je to cele nejak dosachovane tym, ze som preniesol uncgi sem do kodu. Ale hlavne ze to chodi :))
short int getForm(void) {
	char *ptr;
	short int i = 0;
	char local_str[SMALL] = STR_EMPTY;
	short int ret; // návratová hodnota
	char errmsg[SMALL] = STR_EMPTY;

	Log("getForm(): begin\n");

	ptr = getenv(ADD_WWW_PREFIX_(STR_JAZYK));
	if (ptr != NULL) {
		if (strcmp(ptr, STR_EMPTY) != 0) {
			mystrcpy(pom_JAZYK, ptr, SMALL);
		}
	}

	ptr = getenv(ADD_WWW_PREFIX_(STR_KALENDAR));
	if (ptr != NULL) {
		if (strcmp(ptr, STR_EMPTY) != 0) {
			mystrcpy(pom_KALENDAR, ptr, SMALL);
		}
	}

	ptr = getenv(ADD_WWW_PREFIX_(STR_CSS));
	if (ptr != NULL) {
		if (strcmp(ptr, STR_EMPTY) != 0) {
			mystrcpy(pom_CSS, ptr, SMALL);
		}
	}

	ptr = getenv(ADD_WWW_PREFIX_(STR_FONT_NAME));
	if (ptr != NULL) {
		if (strcmp(ptr, STR_EMPTY) != 0) {
			mystrcpy(pom_FONT, ptr, SMALL);
		}
	}

	ptr = getenv(ADD_WWW_PREFIX_(STR_FONT_SIZE));
	if (ptr != NULL) {
		if (strcmp(ptr, STR_EMPTY) != 0) {
			mystrcpy(pom_FONT_SIZE, ptr, VERY_SMALL);
		}
	}

	ptr = getenv(ADD_WWW_PREFIX_(STR_FONT_SIZE_PT));
	if (ptr != NULL) {
		if (strcmp(ptr, STR_EMPTY) != 0) {
			mystrcpy(pom_FONT_SIZE_PT, ptr, VERY_SMALL);
		}
	}

	ptr = getenv(ADD_WWW_PREFIX_(STR_STYLE_MARGIN));
	if (ptr != NULL) {
		if (strcmp(ptr, STR_EMPTY) != 0) {
			mystrcpy(pom_STYLE_MARGIN, ptr, VERY_SMALL);
		}
	}

	ptr = getenv(ADD_WWW_PREFIX_(STR_LINE_HEIGHT_PERC));
	if (ptr != NULL) {
		if (strcmp(ptr, STR_EMPTY) != 0) {
			mystrcpy(pom_LINE_HEIGHT_PERC, ptr, VERY_SMALL);
		}
	}

	// options
	for (i = 0; i < POCET_GLOBAL_OPT; i++) {
		// premenná WWW_OPT_i
		mystrcpy(local_str, WWW_PREFIX, SMALL);

		strcat_str_opt_bit_order(local_str, i, USE_STR_OPT);

		ptr = getenv(local_str);
		if (ptr != NULL) {
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_OPT[i], ptr, SMALL);
			}
		}
	}// for i

	// force options
	for (i = 0; i < POCET_GLOBAL_OPT; i++) {
		// premenná WWW_FORCE_OPT_i
		mystrcpy(local_str, WWW_PREFIX, SMALL);

		strcat_str_opt_bit_order(local_str, i, USE_STR_FORCE_OPT);

		ptr = getenv(local_str);
		if (ptr != NULL) {
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_FORCE_OPT[i], ptr, SMALL);
			}
		}
	}// for i

	// force option 0 premenné -- jednotlivé bit-komponenty
	Log("force option %d, jednotlivé bit-komponenty...(getForm)\n", OPT_0_SPECIALNE);
	for (i = 0; i < POCET_OPT_0_SPECIALNE; i++) {
		// premenná WWW_FORCE_BIT_OPT_0_...
		mystrcpy(local_str, WWW_PREFIX, SMALL);

		strcat_str_opt_bit_order(local_str, OPT_0_SPECIALNE, i);

		ptr = getenv(local_str);
		if (ptr != NULL) {
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_FORCE_OPT_0_SPECIALNE[i], ptr, SMALL);
			}
		}
	}// for i

	// force option 1 premenné -- jednotlivé bit-komponenty
	Log("force option %d, jednotlivé bit-komponenty...(getForm)\n", OPT_1_CASTI_MODLITBY);
	for (i = 0; i < POCET_OPT_1_CASTI_MODLITBY; i++) {
		// premenná WWW_FORCE_BIT_OPT_1_...
		mystrcpy(local_str, WWW_PREFIX, SMALL);

		strcat_str_opt_bit_order(local_str, OPT_1_CASTI_MODLITBY, i);

		ptr = getenv(local_str);
		if (ptr != NULL) {
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_FORCE_OPT_1_CASTI_MODLITBY[i], ptr, SMALL);
			}
		}
	}// for i

	// force option 2, jednotlivé bit-komponenty
	Log("force option %d, jednotlivé bit-komponenty...(getForm)\n", OPT_2_HTML_EXPORT);
	for (i = 0; i < POCET_OPT_2_HTML_EXPORT; i++) {
		// premenná WWW_FORCE_BIT_OPT_2_...
		mystrcpy(local_str, WWW_PREFIX, SMALL);

		strcat_str_opt_bit_order(local_str, OPT_2_HTML_EXPORT, i);

		ptr = getenv(local_str);
		if (ptr != NULL) {
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_FORCE_OPT_2_HTML_EXPORT[i], ptr, SMALL);
			}
		}
	}// for i

	 // force option 5, jednotlivé bit-komponenty
	Log("force option %d, jednotlivé bit-komponenty...(getForm)\n", OPT_5_ALTERNATIVES);
	for (i = 0; i < POCET_OPT_5_ALTERNATIVES; i++) {
		// premenná WWW_FORCE_BIT_OPT_5_...
		mystrcpy(local_str, WWW_PREFIX, SMALL);

		strcat_str_opt_bit_order(local_str, OPT_5_ALTERNATIVES, i);

		ptr = getenv(local_str);
		if (ptr != NULL) {
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_FORCE_OPT_5_ALTERNATIVES[i], ptr, SMALL);
			}
		}
	}// for i

	 // force option 6, jednotlivé decimal-place-komponenty
	Log("force option %d, jednotlivé decimal-place-komponenty...(getForm)\n", OPT_6_ALTERNATIVES_MULTI);
	for (i = 0; i < POCET_OPT_6_ALTERNATIVES_MULTI; i++) {
		// premenná WWW_FORCE_PLACE_OPT_6_...
		mystrcpy(local_str, WWW_PREFIX, SMALL);

		strcat_str_opt_bit_order(local_str, OPT_6_ALTERNATIVES_MULTI, i);

		ptr = getenv(local_str);
		if (ptr != NULL) {
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_FORCE_OPT_6_ALTERNATIVES_MULTI[i], ptr, SMALL);
			}
		}
	}// for i

	// according to query_type, get params from forms using getenv()
	if ((query_type == PRM_DATUM) || (query_type == PRM_DETAILY) || (query_type == PRM_TXT) || (query_type == PRM_XML)) {

		Log("(query_type == PRM_DATUM) || (query_type == PRM_DETAILY) || (query_type == PRM_TXT) || (query_type == PRM_XML)...\n");
		// datum: treba nacitat den, mesiac a rok

		// premenna WWW_DEN
		// ak je naplnena pom_DEN, znamena to, ze uz bola naplnena, preto nemusi existovat
		if (equals(pom_DEN, STR_EMPTY)) {
			ptr = getenv(ADD_WWW_PREFIX_(STR_DEN));
			if (ptr == NULL) {
				DEBUG_GET_FORM("%s neexistuje.\n", ADD_WWW_PREFIX_(STR_DEN));
				
				if (query_type != PRM_XML) {
					sprintf(errmsg, "Nebola vytvorená systémová premenná %s.\n", ADD_WWW_PREFIX_(STR_DEN));
					strcat(bad_param_str, errmsg);
					ret = FAILURE;
					goto END_getForm;
				}
				else {
					mystrcpy(pom_DEN, STR_EMPTY, SMALL);
				}
			}
			else {
				if (strcmp(ptr, STR_EMPTY) != 0) {
					mystrcpy(pom_DEN, ptr, SMALL);
				}
			}
		}
		else {
			Log("Premenná pom_DEN je už naplnená (%s). Nečítam z %s...\n", pom_DEN, ADD_WWW_PREFIX_(STR_DEN));
		}

		// premenna WWW_MESIAC
		// ak je naplnena pom_MESIAC, znamena to, ze uz bola naplnena, preto nemusi existovat
		if (equals(pom_MESIAC, STR_EMPTY)) {
			ptr = getenv(ADD_WWW_PREFIX_(STR_MESIAC));
			if (ptr == NULL) {
				DEBUG_GET_FORM("%s neexistuje.\n", ADD_WWW_PREFIX_(STR_MESIAC));

				if (query_type != PRM_XML) {
					sprintf(errmsg, "Nebola vytvorená systémová premenná %s.\n", ADD_WWW_PREFIX_(STR_MESIAC));
					strcat(bad_param_str, errmsg);
					ret = FAILURE;
					goto END_getForm;
				}
				else {
					mystrcpy(pom_MESIAC, STR_EMPTY, SMALL);
				}
			}
			else {
				if (strcmp(ptr, STR_EMPTY) != 0) {
					mystrcpy(pom_MESIAC, ptr, SMALL);
				}
			}
		}
		else {
			Log("Premenná pom_MESIAC je už naplnená (%s). Nečítam z %s...\n", pom_MESIAC, ADD_WWW_PREFIX_(STR_MESIAC));
		}

		// premenna WWW_ROK
		// ak je naplnena pom_ROK, znamena to, ze uz bola naplnena, preto nemusi existovat
		if (equals(pom_ROK, STR_EMPTY)) {
			ptr = getenv(ADD_WWW_PREFIX_(STR_ROK));
			if (ptr == NULL) {
				DEBUG_GET_FORM("%s neexistuje.\n", ADD_WWW_PREFIX_(STR_ROK));

				if (query_type != PRM_XML) {
					sprintf(errmsg, "Nebola vytvorená systémová premenná %s.\n", ADD_WWW_PREFIX_(STR_ROK));
					strcat(bad_param_str, errmsg);
					ret = FAILURE;
					goto END_getForm;
				}
				else {
					mystrcpy(pom_ROK, STR_EMPTY, SMALL);
				}
			}
			else {
				if (strcmp(ptr, STR_EMPTY) != 0) {
					mystrcpy(pom_ROK, ptr, SMALL);
				}
			}
		}
		else {
			Log("Premenná pom_ROK je už naplnená (%s). Nečítam z %s...\n", pom_ROK, ADD_WWW_PREFIX_(STR_ROK));
		}

		// nasledujuce sa zistuju kvoli 'Detaily...', formular vytvorila funckia showDetails(); v normalnom formulari (vytvori ho _main_dnes();) nie su

		// premenna WWW_MODLITBA
		ptr = getenv(ADD_WWW_PREFIX_(STR_MODLITBA));
		if (ptr != NULL) {
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_MODLITBA, ptr, SMALL);
			}
		}

		// premenna WWW_MESIAC_ROKA -- len testovo, aby sme odlisili prvy od druheho formulara
		ptr = getenv(ADD_WWW_PREFIX_(STR_MESIAC_ROKA));
		if (ptr != NULL) { // povodne if (query_type == PRM_DATUM)
			// nie je NULL, ide teda o prvy vstupny formular
			mystrcpy(pom_MODLITBA, STR_EMPTY, SMALL);
		}

		// premenna WWW_DALSI_SVATY
		ptr = getenv(ADD_WWW_PREFIX_(STR_DALSI_SVATY));
		if (ptr != NULL) {
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_DALSI_SVATY, ptr, SMALL);
			}
		}
	}// (query_type == PRM_DATUM) || (query_type == PRM_DETAILY) || (query_type == PRM_TXT) || (query_type == PRM_XML)

	else if (query_type == PRM_CEZ_ROK) {
		// cez rok: treba nacitat den v tyzdni a cislo tyzdna

		// premenna WWW_DEN_V_TYZDNI
		// ak je naplnena pom_DEN_V_TYZDNI, znamena to, ze uz bola naplnena, preto nemusi existovat
		if (equals(pom_DEN_V_TYZDNI, STR_EMPTY)) {
			ptr = getenv(ADD_WWW_PREFIX_(STR_DEN_V_TYZDNI));
			if (ptr == NULL) {
				DEBUG_GET_FORM("%s neexistuje.\n", ADD_WWW_PREFIX_(STR_DEN_V_TYZDNI));
				sprintf(errmsg, "Nebola vytvorená systémová premenná %s.\n", ADD_WWW_PREFIX_(STR_DEN_V_TYZDNI));
				strcat(bad_param_str, errmsg);
				ret = FAILURE;
				goto END_getForm;
			}
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_DEN_V_TYZDNI, ptr, SMALL);
			}
		}
		else {
			Log("Premenná pom_DEN_V_TYZDNI je už naplnená (%s). Nečítam z %s...\n", pom_DEN_V_TYZDNI, ADD_WWW_PREFIX_(STR_DEN_V_TYZDNI));
		}

		// premenna WWW_TYZDEN
		// ak je naplnena pom_TYZDEN, znamena to, ze uz bola naplnena, preto nemusi existovat
		if (equals(pom_TYZDEN, STR_EMPTY)) {
			ptr = getenv(ADD_WWW_PREFIX_(STR_TYZDEN));
			if (ptr == NULL) {
				DEBUG_GET_FORM("%s neexistuje.\n", ADD_WWW_PREFIX_(STR_TYZDEN));
				sprintf(errmsg, "Nebola vytvorená systémová premenná %s.\n", ADD_WWW_PREFIX_(STR_TYZDEN));
				strcat(bad_param_str, errmsg);
				ret = FAILURE;
				goto END_getForm;
			}
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_TYZDEN, ptr, SMALL);
			}
		}
		else {
			Log("Premenná pom_TYZDEN je už naplnená (%s). Nečítam z %s...\n", pom_TYZDEN, ADD_WWW_PREFIX_(STR_TYZDEN));
		}

		// premenna WWW_MODLITBA
		// ak je naplnena pom_MODLITBA, znamena to, ze uz bola naplnena, preto nemusi existovat
		if (equals(pom_MODLITBA, STR_EMPTY)) {
			ptr = getenv(ADD_WWW_PREFIX_(STR_MODLITBA));
			if (ptr == NULL) {
				DEBUG_GET_FORM("%s neexistuje.\n", ADD_WWW_PREFIX_(STR_MODLITBA));
				sprintf(errmsg, "Nebola vytvorená systémová premenná %s.\n", ADD_WWW_PREFIX_(STR_MODLITBA));
				strcat(bad_param_str, errmsg);
				ret = FAILURE;
				goto END_getForm;
			}
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_MODLITBA, ptr, SMALL);
			}
		}
		else {
			Log("Premenná pom_MODLITBA je už naplnená (%s). Nečítam z %s...\n", pom_MODLITBA, ADD_WWW_PREFIX_(STR_MODLITBA));
		}
	}// query_type == PRM_CEZ_ROK

	else if (query_type == PRM_LIT_OBD) {
		// 2011-01-25: doplnené | liturgické obdobie: treba načítať liturgické obdobie, deň v týždni a číslo týždňa v danom liturgickom období 

		// premenna WWW_DEN_V_TYZDNI
		// ak je naplnena pom_DEN_V_TYZDNI, znamena to, ze uz bola naplnena, preto nemusi existovat
		if (equals(pom_DEN_V_TYZDNI, STR_EMPTY)) {
			ptr = getenv(ADD_WWW_PREFIX_(STR_DEN_V_TYZDNI));
			if (ptr == NULL) {
				DEBUG_GET_FORM("%s neexistuje.\n", ADD_WWW_PREFIX_(STR_DEN_V_TYZDNI));
				sprintf(errmsg, "Nebola vytvorená systémová premenná %s.\n", ADD_WWW_PREFIX_(STR_DEN_V_TYZDNI));
				strcat(bad_param_str, errmsg);
				ret = FAILURE;
				goto END_getForm;
			}
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_DEN_V_TYZDNI, ptr, SMALL);
			}
		}
		else {
			Log("Premenná pom_DEN_V_TYZDNI je už naplnená (%s). Nečítam z %s...\n", pom_DEN_V_TYZDNI, ADD_WWW_PREFIX_(STR_DEN_V_TYZDNI));
		}

		// premenna WWW_TYZDEN
		// ak je naplnena pom_TYZDEN, znamena to, ze uz bola naplnena, preto nemusi existovat
		if (equals(pom_TYZDEN, STR_EMPTY)) {
			ptr = getenv(ADD_WWW_PREFIX_(STR_TYZDEN));
			if (ptr == NULL) {
				DEBUG_GET_FORM("%s neexistuje.\n", ADD_WWW_PREFIX_(STR_TYZDEN));
				sprintf(errmsg, "Nebola vytvorená systémová premenná %s.\n", ADD_WWW_PREFIX_(STR_TYZDEN));
				strcat(bad_param_str, errmsg);
				ret = FAILURE;
				goto END_getForm;
			}
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_TYZDEN, ptr, SMALL);
			}
		}
		else {
			Log("Premenná pom_TYZDEN je už naplnená (%s). Nečítam z %s...\n", pom_TYZDEN, ADD_WWW_PREFIX_(STR_TYZDEN));
		}

		// premenna WWW_MODLITBA
		// ak je naplnena pom_MODLITBA, znamena to, ze uz bola naplnena, preto nemusi existovat
		if (equals(pom_MODLITBA, STR_EMPTY)) {
			ptr = getenv(ADD_WWW_PREFIX_(STR_MODLITBA));
			if (ptr == NULL) {
				DEBUG_GET_FORM("%s neexistuje.\n", ADD_WWW_PREFIX_(STR_MODLITBA));
				sprintf(errmsg, "Nebola vytvorená systémová premenná %s.\n", ADD_WWW_PREFIX_(STR_MODLITBA));
				strcat(bad_param_str, errmsg);
				ret = FAILURE;
				goto END_getForm;
			}
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_MODLITBA, ptr, SMALL);
			}
		}
		else {
			Log("Premenná pom_MODLITBA je už naplnená (%s). Nečítam z %s...\n", pom_MODLITBA, ADD_WWW_PREFIX_(STR_MODLITBA));
		}

		// premenna WWW_LIT_OBD
		// ak je naplnena pom_LIT_OBD, znamena to, ze uz bola naplnena, preto nemusi existovat
		if (equals(pom_LIT_OBD, STR_EMPTY)) {
			ptr = getenv(ADD_WWW_PREFIX_(STR_LIT_OBD));
			if (ptr == NULL) {
				DEBUG_GET_FORM("%s neexistuje.\n", ADD_WWW_PREFIX_(STR_LIT_OBD));
				sprintf(errmsg, "Nebola vytvorená systémová premenná %s.\n", ADD_WWW_PREFIX_(STR_LIT_OBD));
				strcat(bad_param_str, errmsg);
				ret = FAILURE;
				goto END_getForm;
			}
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_LIT_OBD, ptr, SMALL);
			}
		}
		else {
			Log("Premenná pom_LIT_OBD je už naplnená (%s). Nečítam z %s...\n", pom_LIT_OBD, ADD_WWW_PREFIX_(STR_LIT_OBD));
		}

		// premenna WWW_LIT_ROK
		// ak je naplnena pom_LIT_ROK, znamena to, ze uz bola naplnena, preto nemusi existovat
		if (equals(pom_LIT_ROK, STR_EMPTY)) {
			ptr = getenv(ADD_WWW_PREFIX_(STR_LIT_ROK));
			if (ptr == NULL) {
				DEBUG_GET_FORM("%s neexistuje.\n", ADD_WWW_PREFIX_(STR_LIT_ROK));
				sprintf(errmsg, "Nebola vytvorená systémová premenná %s.\n", ADD_WWW_PREFIX_(STR_LIT_ROK));
				strcat(bad_param_str, errmsg);
				ret = FAILURE;
				goto END_getForm;
			}
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_LIT_ROK, ptr, SMALL);
			}
		}
		else {
			Log("Premenná pom_LIT_ROK je už naplnená (%s). Nečítam z %s...\n", pom_LIT_ROK, ADD_WWW_PREFIX_(STR_LIT_ROK));
		}
	}// query_type == PRM_LIT_OBD

	else if (query_type == PRM_SVIATOK) {
		// cez rok: treba nacitat nazov sviatku

		// premenna WWW_NAZOV_SVIATOK
		// ak je naplnena pom_SVIATOK, znamena to, ze uz bola naplnena, preto nemusi existovat
		if (equals(pom_SVIATOK, STR_EMPTY)) {
			ptr = getenv(ADD_WWW_PREFIX_(STR_NAZOV_SVIATOK));
			if (ptr == NULL) {
				DEBUG_GET_FORM("%s neexistuje.\n", ADD_WWW_PREFIX_(STR_NAZOV_SVIATOK));
				sprintf(errmsg, "Nebola vytvorená systémová premenná %s.\n", ADD_WWW_PREFIX_(STR_NAZOV_SVIATOK));
				strcat(bad_param_str, errmsg);
				ret = FAILURE;
				goto END_getForm;
			}
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_SVIATOK, ptr, SMALL);
			}
		}
		else {
			Log("Premenná pom_SVIATOK je už naplnená (%s). Nečítam z %s...\n", pom_SVIATOK, ADD_WWW_PREFIX_(STR_NAZOV_SVIATOK));
		}
	}// query_type == PRM_SVIATOK

	else if (query_type == PRM_STATIC_TEXT) {

		Log("getForm(): query_type == PRM_STATIC_TEXT...\n");

		// premenna WWW_STATIC_TEXT
		// ak je naplnena pom_STATIC_TEXT, znamena to, ze uz bola naplnena, preto nemusi existovat
		if (equals(pom_STATIC_TEXT, STR_EMPTY)) {
			ptr = getenv(ADD_WWW_PREFIX_(STR_STATIC_TEXT));
			if (ptr == NULL) {
				DEBUG_GET_FORM("%s neexistuje.\n", ADD_WWW_PREFIX_(STR_STATIC_TEXT));
				sprintf(errmsg, "Nebola vytvorená systémová premenná %s.\n", ADD_WWW_PREFIX_(STR_STATIC_TEXT));
				strcat(bad_param_str, errmsg);
				ret = FAILURE;
				goto END_getForm;
			}
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_STATIC_TEXT, ptr, SMALL);
			}
		}
		else {
			Log("Premenná pom_STATIC_TEXT je už naplnená (%s). Nečítam z %s...\n", pom_STATIC_TEXT, ADD_WWW_PREFIX_(STR_STATIC_TEXT));
		}

		// premenna WWW_MODL_ORDINARIUM
		// ak je naplnena MODL_ORDINARIUM, znamena to, ze uz bola naplnena, preto nemusi existovat
		if (equals(pom_MODL_ORDINARIUM, STR_EMPTY)) {

			ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_ORDINARIUM));
			if (ptr != NULL) {
				if (strcmp(ptr, STR_EMPTY) != 0) {
					mystrcpy(pom_MODL_ORDINARIUM, ptr, SMALL);
				}
			}

			Log("getForm(): pom_MODL_ORDINARIUM == `%s'...\n", pom_MODL_ORDINARIUM);

			// if still empty, try to use STR_MODLITBA instead of STR_MODL_ORDINARIUM
			if (equals(pom_MODL_ORDINARIUM, STR_EMPTY)) {
				ptr = getenv(ADD_WWW_PREFIX_(STR_MODLITBA));
				if (ptr != NULL) {
					if (strcmp(ptr, STR_EMPTY) != 0) {
						mystrcpy(pom_MODL_ORDINARIUM, ptr, SMALL);
					}
				}
			}

			Log("getForm(): pom_MODL_ORDINARIUM == `%s'...\n", pom_MODL_ORDINARIUM);
		}
		else {
			Log("Premenná pom_MODL_ORDINARIUM je už naplnená (%s). Nečítam z %s...\n", pom_MODL_ORDINARIUM, ADD_WWW_PREFIX_(STR_MODL_ORDINARIUM));
		}
	}// query_type == PRM_STATIC_TEXT

	else if (query_type == PRM_ANALYZA_ROKU) {
		// cez rok: treba nacitat nazov sviatku

		// premenna WWW_ANALYZA_ROKU
		// ak je naplnena pom_ANALYZA_ROKU, znamena to, ze uz bola naplnena, preto nemusi existovat
		if (equals(pom_ANALYZA_ROKU, STR_EMPTY)) {
			ptr = getenv(ADD_WWW_PREFIX_(STR_ANALYZA_ROKU));
			if (ptr == NULL) {
				DEBUG_GET_FORM("%s neexistuje.\n", ADD_WWW_PREFIX_(STR_ANALYZA_ROKU));
				sprintf(errmsg, "Nebola vytvorená systémová premenná %s.\n", ADD_WWW_PREFIX_(STR_ANALYZA_ROKU));
				strcat(bad_param_str, errmsg);
				ret = FAILURE;
				goto END_getForm;
			}
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_ANALYZA_ROKU, ptr, SMALL);
			}
		}
		else {
			Log("Premenná pom_ANALYZA_ROKU je už naplnená (%s). Nečítam z %s...\n", pom_ANALYZA_ROKU, ADD_WWW_PREFIX_(STR_ANALYZA_ROKU));
		}
	}// query_type == PRM_ANALYZA_ROKU

	else if (query_type == PRM_MESIAC_ROKA) {
		// 2005-03-21: novy typ exportu liturgickeho kalendara: 
		// ak je hodnota premennej option "1" = 0 (default), tak klasicky pre web, inak rozlicny sposob vystupu ("1" = 1 pre www.kbs.sk liturgicky kalendar)
		// 2005-03-22: novy typ exportu liturgickeho kalendara: ak je hodnota premennej option "2" = 1 (default), tak datum ako ISO-8601, inak len datum

		// treba nacitat mesiac a rok
		// premenna WWW_MESIAC_ROKA
		// ak je naplnena pom_MESIAC (vynimocne nie pom_MESIAC_ROKA), znamena to, ze uz bola naplnena, preto nemusi existovat
		if (equals(pom_MESIAC, STR_EMPTY)) {
			ptr = getenv(ADD_WWW_PREFIX_(STR_MESIAC_ROKA));
			if (ptr == NULL) {
				DEBUG_GET_FORM("%s neexistuje.\n", ADD_WWW_PREFIX_(STR_MESIAC_ROKA));
				sprintf(errmsg, "Nebola vytvorená systémová premenná %s.\n", ADD_WWW_PREFIX_(STR_MESIAC_ROKA));
				strcat(bad_param_str, errmsg);
				ret = FAILURE;
				goto END_getForm;
			}
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_MESIAC, ptr, SMALL);
			}
		}
		else {
			Log("Premenná pom_MESIAC je už naplnená (%s). Nečítam z %s...\n", pom_MESIAC, ADD_WWW_PREFIX_(STR_MESIAC_ROKA));
		}

		// premenna WWW_ROK
		// ak je naplnena pom_ROK (vynimocne nie pom_ROK_ROKA), znamena to, ze uz bola naplnena, preto nemusi existovat
		if (equals(pom_ROK, STR_EMPTY)) {
			ptr = getenv(ADD_WWW_PREFIX_(STR_ROK_ROKA));
			if (ptr == NULL) {
				DEBUG_GET_FORM("%s neexistuje.\n", ADD_WWW_PREFIX_(STR_ROK_ROKA));
				sprintf(errmsg, "Nebola vytvorená systémová premenná %s.\n", ADD_WWW_PREFIX_(STR_ROK_ROKA));
				strcat(bad_param_str, errmsg);
				ret = FAILURE;
				goto END_getForm;
			}
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_ROK, ptr, SMALL);
			}
		}
		else {
			Log("Premenná pom_ROK je už naplnená (%s). Nečítam z %s...\n", pom_ROK, ADD_WWW_PREFIX_(STR_ROK_ROKA));
		}
	}// query_type == PRM_MESIAC_ROKA

	else if (query_type == PRM_TABULKA) {
		// PRM_TABULKA: treba nacitat from a to; ak chyba linka, tak automaticky == NIE

		// premenna WWW_ROK_FROM
		// ak je naplnena pom_ROK_FROM, znamena to, ze uz bola naplnena, preto nemusi existovat
		if (equals(pom_ROK_FROM, STR_EMPTY)) {
			ptr = getenv(ADD_WWW_PREFIX_(STR_ROK_FROM));
			if (ptr == NULL) {
				DEBUG_GET_FORM("%s neexistuje.\n", ADD_WWW_PREFIX_(STR_ROK_FROM));
				sprintf(errmsg, "Nebola vytvorená systémová premenná %s.\n", ADD_WWW_PREFIX_(STR_ROK_FROM));
				strcat(bad_param_str, errmsg);
				ret = FAILURE;
				goto END_getForm;
			}
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_ROK_FROM, ptr, SMALL);
			}
		}
		else {
			Log("Premenná pom_ROK_FROM je už naplnená (%s). Nečítam z %s...\n", pom_ROK_FROM, ADD_WWW_PREFIX_(STR_ROK_FROM));
		}

		// premenna WWW_ROK_TO
		// ak je naplnena pom_ROK_TO, znamena to, ze uz bola naplnena, preto nemusi existovat
		// 2005-05-24 Opravena copy-paste chyba: bolo mylne if (equals(pom_ROK_FROM, STR_EMPTY))
		if (equals(pom_ROK_TO, STR_EMPTY)) {
			ptr = getenv(ADD_WWW_PREFIX_(STR_ROK_TO));
			if (ptr == NULL) {
				DEBUG_GET_FORM("%s neexistuje.\n", ADD_WWW_PREFIX_(STR_ROK_TO));
				sprintf(errmsg, "Nebola vytvorená systémová premenná %s.\n", ADD_WWW_PREFIX_(STR_ROK_TO));
				strcat(bad_param_str, errmsg);
				ret = FAILURE;
				goto END_getForm;
			}
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_ROK_TO, ptr, SMALL);
			}
		}
		else {
			Log("Premenná pom_ROK_TO je už naplnená (%s). Nečítam z %s...\n", pom_ROK_TO, ADD_WWW_PREFIX_(STR_ROK_TO));
		}

		// premenna WWW_TABULKA_LINKY
		ptr = getenv(ADD_WWW_PREFIX_(STR_TABULKA_LINKY));
		if (ptr != NULL) {
			if (strcmp(ptr, STR_EMPTY) != 0) {
				mystrcpy(pom_LINKY, ptr, SMALL);
			}
		}
	}// query_type == PRM_TABULKA

	else if (query_type == PRM_DNES) {
		// 2005-03-28: Pridane, aby nevracalo FAILURE
		Log("getForm(): no need to read anything :)\n");
	}

	else {
		Log("getForm(): end, returning FAILURE (neznamy typ dotazu qt)\n");
		sprintf(errmsg, "Neznámy typ dotazu (qt).\n");
		strcat(bad_param_str, errmsg);
		ret = FAILURE;
		goto END_getForm;
	}
	ret = SUCCESS;

END_getForm:
	Log("getForm(): end, returning %d.\n", ret);
	return ret;
}// getForm();

// popis: naplni premenne pom_... hodnotami z environmentu, t.j. premennymi zo stringu QUERY_STRING (systemova premenna)
// napriklad retazec "QUERY_TYPE=PRM_DATUM&DEN=7&MESIAC=5&ROK=1976"
// vracia: on success, returns SUCCESS
//         on error,   returns FAILURE
short int parseQueryString(void) {
	// totiz spustenie skriptu
	// /cgi-bin/script_name?QUERY_TYPE=PRM_DATUM&DEN=7&MESIAC=5&ROK=1976
	// funguje tak, ze vytvori systemovu premennu QUERY_STRING takze vlastne treba simulovat uncgi (parsovanie QUERY_STRING systemovej premennej)
	// (keby sme to este prehnali cez uncgi, teda spustili /cgi-bin/uncgi.cgi/script_name?QUERY_TYPE=PRM_DATUM&DEN=7&MESIAC=5&ROK=1976 
	// tak to funguje ako POST hodnoty z formulara - urobi systemove premenne WWW_QUERY_TYPE=PRM_DATUM, WWW_DATUM, WWW_MESIAC, WWW_ROK)

	short int i, pocet, ok;
	char local_str[SMALL] = STR_EMPTY;
	short int j; // kvôli prilep_request_options
	short int ret = FAILURE; // návratová hodnota
	char errmsg[SMALL] = STR_EMPTY;

	Log("parseQueryString() -- begin\n");
	if (query_string != NULL) {
		Log("query_string == %s, lenght == %d\n", query_string, strlen(query_string));
	}
	else {
		Log("query_string is NULL, something is wrong...\n");
		return ret;
	}

#ifndef LOG_PARAMS
	Log("parseQueryString(): LOG_PARAMS is undefined, no LogParams() printed...\n");
#endif

	// get parameters
	i = 0;
	while ((strlen(query_string) > 0) && (i < MAX_VARIABLES)) {
		mystrcpy(param[i].name, STR_EMPTY, MAX_NAME_CGI_UTILS);
		mystrcpy(param[i].val, STR_EMPTY, MAX_VAL_CGI_UTILS);
		splitword(param[i].val, query_string, '&');
		unescape_url(param[i].val);
		splitword(param[i].name, param[i].val, '=');
		LogParams("--- param[%d].name == %s, .val == %s\n", i, param[i].name, param[i].val);
		i++;
	}
	pocet = i; // od 0 po i - 1
	LogParams("pocet == %d\n", pocet);

	// 2006-08-01: doplnená podmienka, aby nepretieklo napĺňanie premenných, ak je ich viac
	if ((strlen(query_string) > 0) && (pocet >= MAX_VARIABLES)) {
		ALERT;
		Export("Program nedokáže obslúžiť viac parametrov (maximum: %d). Ostatné budú ignorované.\n", MAX_VARIABLES);
	}

	// Pre POST query sa tam jazyk priliepa aj na začiatok (Ruby), aj sa číta z form-ulára (t. j. pri výbere z qt=pdnes), 
	// preto čítam "odzadu", "zozadu" (backwards)
	// ak by sa nešlo smerom "dolu" (t. j. k prvému parametru od konca), nefungovalo by "override" z tabuľky "Voľby vybraných detailov", ak už v query stringu nejaká hodnota je
	// pôvodná poznámka pre while cyklus resp. inicializáciu i: param[0] by mal síce obsahovať typ akcie, ale radšej kontrolujeme aj 0
	i = pocet;
	LogParams("pokúšam sa zistiť jazyk (od posledného parametra k prvému, t. j. odzadu)...\n");
	while ((equalsi(pom_JAZYK, STR_EMPTY)) && (i > 0)) {
		--i;
		LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if (equals(param[i].name, STR_JAZYK)) {
			// ide o parameter STR_JAZYK
			mystrcpy(pom_JAZYK, param[i].val, SMALL);
			LogParams("jazyk zistený (%s).\n", pom_JAZYK);
		}
	}

	// 2010-10-11: Pre POST query sa tam kalendár priliepa aj na začiatok, aj sa číta z form-ulára (t. j. pri výbere z qt=pdnes), 
	//             preto čítam "odzadu", "zozadu" (backwards)
	//             ak by sa nešlo smerom "dolu" (t. j. k prvému parametru od konca), nefungovalo by "override" z tabuľky "Voľby vybraných detailov", ak už v query stringu nejaká hodnota je
	// 2011-04-07: keďže počet parametrov je "pocet", indexované sú 0 až pocet - 1, a preto opravené: najprv znížime --i;
	i = pocet;
	LogParams("pokúšam sa zistiť kalendár (od posledného parametra k prvému, t. j. odzadu)...\n");
	while ((equalsi(pom_KALENDAR, STR_EMPTY)) && (i > 0)) {
		--i;
		LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if (equals(param[i].name, STR_KALENDAR)) {
			// ide o parameter STR_KALENDAR
			mystrcpy(pom_KALENDAR, param[i].val, SMALL);
			LogParams("kalendár zistený (%s).\n", pom_KALENDAR);
		}
	}

	i = 0; // param[0] by mal síce obsahovať typ akcie, ale radšej kontrolujeme od 0
	LogParams("pokúšam sa zistiť css...\n");
	while ((equalsi(pom_CSS, STR_EMPTY)) && (i < pocet)) {
		LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if (equals(param[i].name, STR_CSS)) {
			// ide o parameter STR_CSS
			mystrcpy(pom_CSS, param[i].val, SMALL);
			LogParams("css zistené (%s).\n", pom_CSS);
		}
		i++;
	}
	if ((i >= pocet) && (equalsi(pom_CSS, STR_EMPTY))) {
		mystrcpy(pom_CSS, nazov_css[CSS_breviar_sk], SMALL);
		LogParams("css zistené (%s) (i >= pocet).\n", pom_CSS);
	}

	// Pre POST query sa tam font priliepa aj na začiatok (rovnako ako kalendár), aj sa číta z form-ulára (t. j. pri výbere z qt=pdnes), 
	// preto čítam "odzadu", "zozadu" (backwards) (rovnako ako kalendár), ak by sa nešlo smerom "dolu" (t. j. k prvému parametru od konca), 
	// nefungovalo by "override" z tabuľky "Voľby vybraných detailov", ak už v query stringu nejaká hodnota je
	i = pocet;
	LogParams("pokúšam sa zistiť font (od posledného parametra k prvému, t. j. odzadu)...\n");
	while ((equalsi(pom_FONT, STR_EMPTY)) && (i > 0)) {
		--i;
		LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if (equals(param[i].name, STR_FONT_NAME)) {
			// ide o parameter STR_FONT_NAME
			mystrcpy(pom_FONT, param[i].val, SMALL);
			LogParams("font zistený (%s).\n", pom_FONT);
		}
	}

	// Pre POST query sa tam font priliepa aj na začiatok (rovnako ako kalendár), aj sa číta z form-ulára (t. j. pri výbere z qt=pdnes), 
	// preto čítam "odzadu", "zozadu" (backwards) (rovnako ako kalendár), ak by sa nešlo smerom "dolu" (t. j. k prvému parametru od konca), 
	// nefungovalo by "override" z tabuľky "Voľby vybraných detailov", ak už v query stringu nejaká hodnota je
	i = pocet;
	LogParams("pokúšam sa zistiť font size (od posledného parametra k prvému, t. j. odzadu)...\n");
	while ((equalsi(pom_FONT_SIZE, STR_EMPTY)) && (i > 0)) {
		--i;
		LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if (equals(param[i].name, STR_FONT_SIZE)) {
			// ide o parameter STR_FONT_SIZE
			mystrcpy(pom_FONT_SIZE, param[i].val, VERY_SMALL);
			LogParams("font size zistená (%s).\n", pom_FONT_SIZE);
		}
	}

	i = pocet;
	LogParams("pokúšam sa zistiť font size pt (od posledného parametra k prvému, t. j. odzadu)...\n");
	while ((equalsi(pom_FONT_SIZE_PT, STR_EMPTY)) && (i > 0)) {
		--i;
		LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if (equals(param[i].name, STR_FONT_SIZE_PT)) {
			// ide o parameter STR_FONT_SIZE_PT
			mystrcpy(pom_FONT_SIZE_PT, param[i].val, VERY_SMALL);
			LogParams("font size pt zistená (%s).\n", pom_FONT_SIZE_PT);
		}
	}

	i = pocet;
	LogParams("pokúšam sa zistiť style margin (od posledného parametra k prvému, t. j. odzadu)...\n");
	while ((equalsi(pom_STYLE_MARGIN, STR_EMPTY)) && (i > 0)) {
		--i;
		LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if (equals(param[i].name, STR_STYLE_MARGIN)) {
			// ide o parameter STR_STYLE_MARGIN
			mystrcpy(pom_STYLE_MARGIN, param[i].val, VERY_SMALL);
			LogParams("style margin zistený (%s).\n", pom_STYLE_MARGIN);
		}
	}

	i = pocet;
	LogParams("pokúšam sa zistiť line height (od posledného parametra k prvému, t. j. odzadu)...\n");
	while ((equalsi(pom_LINE_HEIGHT_PERC, STR_EMPTY)) && (i > 0)) {
		--i;
		LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if (equals(param[i].name, STR_LINE_HEIGHT_PERC)) {
			// ide o parameter STR_LINE_HEIGHT_PERC
			mystrcpy(pom_LINE_HEIGHT_PERC, param[i].val, VERY_SMALL);
			LogParams("line height zistená (%s).\n", pom_LINE_HEIGHT_PERC);
		}
	}

	ok = NIE;
	query_type = PRM_UNKNOWN;
	i = 0; // od param[0]
	LogParams("pokúšam sa zistiť query type...\n");
	while ((ok != ANO) && (i < pocet)) {
		LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if (equals(param[i].name, STR_QUERY_TYPE)) { // zistíme typ akcie, lebo ide o dobrý parameter
			if (equals(param[i].val, STR_PRM_DATUM)) {
				// ide o parameter STR_PRM_DATUM
				query_type = PRM_DATUM;
			}
			else if (equals(param[i].val, STR_PRM_TXT)) {
				// ide o parameter STR_PRM_TXT; pridané 2011-02-02
				query_type = PRM_TXT;
			}
			else if (equals(param[i].val, STR_PRM_XML)) {
				// ide o parameter STR_PRM_XML; pridané 2012-10-16
				query_type = PRM_XML;
			}
			else if (equals(param[i].val, STR_PRM_STATIC_TEXT)) {
				// ide o parameter STR_PRM_STATIC_TEXT; pridané 2014-10-09
				query_type = PRM_STATIC_TEXT;
			}
			else if (equals(param[i].val, STR_PRM_DETAILY)) {
				// ide o parameter STR_PRM_DETAILY | alternativa k PRM_DATUM
				query_type = PRM_DETAILY;
			}
			else if (equals(param[i].val, STR_PRM_CEZ_ROK)) {
				// ide o parameter STR_PRM_CEZ_ROK
				query_type = PRM_CEZ_ROK;
			}
			else if (equals(param[i].val, STR_PRM_LIT_OBD)) {
				// ide o parameter STR_PRM_LIT_OBD
				query_type = PRM_LIT_OBD;
			}
			else if (equals(param[i].val, STR_PRM_SVIATOK)) {
				// ide o parameter STR_PRM_SVIATOK
				query_type = PRM_SVIATOK;
			}
			else if (equals(param[i].val, STR_PRM_DNES)) {
				// ide o parameter STR_PRM_DNES
				query_type = PRM_DNES;
			}
			else if (equals(param[i].val, STR_PRM_ANALYZA_ROKU)) {
				// ide o parameter STR_PRM_ANALYZA_ROKU
				query_type = PRM_ANALYZA_ROKU;
			}
			else if (equals(param[i].val, STR_PRM_MESIAC_ROKA)) {
				// ide o parameter STR_PRM_MESIAC_ROKA
				query_type = PRM_MESIAC_ROKA;
			}
			else if (equals(param[i].val, STR_PRM_TABULKA)) {
				// ide o parameter STR_PRM_TABULKA
				query_type = PRM_TABULKA;
			}
			else {
				// názov parametra je OK, ale neurčuje žiadnu správnu akciu
				Export("Chybná hodnota parametra %s: %s\n", param[i].name, param[i].val);
				query_type = PRM_UNKNOWN;
			}
			LogParams("query type parameter prítomný (%s), hodnota zistená (%s).\n", param[i].name, param[i].val);
		}// if (equals(param[i].name, STR_QUERY_TYPE))
		if (query_type != PRM_UNKNOWN)
			ok = ANO;
		i++;
	}// while

	for (j = 0; j < POCET_GLOBAL_OPT; j++) {
		LogParams("j == %d...\n", j);
		mystrcpy(local_str, STR_EMPTY, SMALL);

		strcat_str_opt_bit_order(local_str, j, USE_STR_OPT);

		// premenná OPT_j (nepovinná), j = 0 až POCET_GLOBAL_OPT - 1
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s... parseQueryString()\n", local_str);
		while ((equalsi(pom_OPT[j], STR_EMPTY)) && (i < pocet)) {
			// LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, local_str)) {
				// ide o parameter STR_OPT_j
				mystrcpy(pom_OPT[j], param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", local_str, pom_OPT[j]);
			}
			i++;
		}
		if (equalsi(pom_OPT[j], STR_EMPTY)) {
			LogParams("Nebola zadaná premenná %s (nevadí).\n", local_str);
		}
	}// for j

	// FORCE options
	for (j = 0; j < POCET_GLOBAL_OPT; j++) {
		LogParams("j == %d...\n", j);
		mystrcpy(local_str, STR_EMPTY, SMALL);

		strcat_str_opt_bit_order(local_str, j, USE_STR_FORCE_OPT);

		// premenná FORCE_OPT_j (nepovinná)
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s... parseQueryString(), force\n", local_str);
		while ((equalsi(pom_FORCE_OPT[j], STR_EMPTY)) && (i < pocet)) {
			// LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, local_str)) {
				// ide o parameter STR_FORCE_OPT_j
				mystrcpy(pom_FORCE_OPT[j], param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", local_str, pom_FORCE_OPT[j]);
			}
			i++;
		}
		if (equalsi(pom_FORCE_OPT[j], STR_EMPTY)) {
			LogParams("Nebola zadaná premenná %s (nevadí).\n", local_str);
		}
	}// for j

	// force option 0 premenné -- jednotlivé bit-komponenty
	// Pre POST query sa tam hodnota priliepa pre jednotlivý check-box zo začiatku (rovnako ako kalendár), aj sa číta z form-ulára (t. j. pri výbere z qt=pdnes), 
	// preto čítam "odzadu", "zozadu" (backwards) (rovnako ako kalendár), ak by sa nešlo smerom "dolu" (t. j. k prvému parametru od konca), 
	// nefungovalo by "override" z tabuľky "Voľby vybraných detailov", ak už v query stringu nejaká hodnota je
	LogParams("force option %d, jednotlivé bit-komponenty...(parseQuery)\n", OPT_0_SPECIALNE);
	for (j = 0; j < POCET_OPT_0_SPECIALNE; j++) {
		LogParams("j == %d...\n", j);
		mystrcpy(local_str, STR_EMPTY, SMALL);

		strcat_str_opt_bit_order(local_str, OPT_0_SPECIALNE, j);

		// premenná WWW_FORCE_BIT_OPT_0_... (nepovinná), j = 0 až POCET_OPT_0_SPECIALNE
		i = pocet; // backwards; param[0] by mal síce obsahovať query type, ale radšej kontrolujeme až po 0
		LogParams("attempt to get value of param %s... parseQueryString(), force, bit-komponenty 0 / pom_FORCE_OPT_0_SPECIALNE[%d] = %s\n", local_str, j, pom_FORCE_OPT_0_SPECIALNE[j]);
		while ((equalsi(pom_FORCE_OPT_0_SPECIALNE[j], STR_EMPTY)) && (i > 0)) {
			--i;
			// LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, local_str)) {
				// ide o parameter STR_FORCE_OPT_j
				mystrcpy(pom_FORCE_OPT_0_SPECIALNE[j], param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", local_str, pom_FORCE_OPT_0_SPECIALNE[j]);
			}
		}
		if (equalsi(pom_FORCE_OPT_0_SPECIALNE[j], STR_EMPTY)) {
			LogParams("Nebola zadaná premenná %s (nevadí).\n", local_str);
		}
	}// for j

	// force option 1 premenné -- jednotlivé bit-komponenty
	// Pre POST query sa tam hodnota priliepa pre jednotlivý check-box zo začiatku (rovnako ako kalendár), aj sa číta z form-ulára (t. j. pri výbere z qt=pdnes), 
	// preto čítam "odzadu", "zozadu" (backwards) (rovnako ako kalendár), ak by sa nešlo smerom "dolu" (t. j. k prvému parametru od konca), 
	// nefungovalo by "override" z tabuľky "Voľby vybraných detailov", ak už v query stringu nejaká hodnota je
	LogParams("force option %d, jednotlivé bit-komponenty...(parseQuery)\n", OPT_1_CASTI_MODLITBY);
	for (j = 0; j < POCET_OPT_1_CASTI_MODLITBY; j++) {
		LogParams("j == %d...\n", j);
		mystrcpy(local_str, STR_EMPTY, SMALL);

		strcat_str_opt_bit_order(local_str, OPT_1_CASTI_MODLITBY, j);

		// premenná WWW_FORCE_BIT_OPT_1_... (nepovinná), j = 0 až POCET_OPT_1_CASTI_MODLITBY
		i = pocet; // backwards; param[0] by mal síce obsahovať query type, ale radšej kontrolujeme až po 0
		LogParams("attempt to get value of param %s... parseQueryString(), force, bit-komponenty 1 / pom_FORCE_OPT_1_CASTI_MODLITBY[%d] == %s\n", local_str, j, pom_FORCE_OPT_1_CASTI_MODLITBY[j]);
		while ((equalsi(pom_FORCE_OPT_1_CASTI_MODLITBY[j], STR_EMPTY)) && (i > 0)) {
			--i;
			// LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, local_str)) {
				// ide o parameter STR_FORCE_OPT_j
				mystrcpy(pom_FORCE_OPT_1_CASTI_MODLITBY[j], param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", local_str, pom_FORCE_OPT_1_CASTI_MODLITBY[j]);
			}
		}
		if (equalsi(pom_FORCE_OPT_1_CASTI_MODLITBY[j], STR_EMPTY)) {
			LogParams("Nebola zadaná premenná %s (nevadí).\n", local_str);
		}
	}// for j

	// force option 2 premenné -- jednotlivé bit-komponenty
	// Pre POST query sa tam hodnota priliepa pre jednotlivý check-box zo začiatku (rovnako ako kalendár), aj sa číta z form-ulára (t. j. pri výbere z qt=pdnes), 
	// preto čítam "odzadu", "zozadu" (backwards) (rovnako ako kalendár), ak by sa nešlo smerom "dolu" (t. j. k prvému parametru od konca), 
	// nefungovalo by "override" z tabuľky "Voľby vybraných detailov", ak už v query stringu nejaká hodnota je
	LogParams("force option %d, jednotlivé bit-komponenty...(parseQuery)\n", OPT_2_HTML_EXPORT);
	for (j = 0; j < POCET_OPT_2_HTML_EXPORT; j++) {
		LogParams("j == %d...\n", j);
		mystrcpy(local_str, STR_EMPTY, SMALL);

		strcat_str_opt_bit_order(local_str, OPT_2_HTML_EXPORT, j);

		// premenná WWW_OPT_2_... (nepovinná), j = 0 až POCET_OPT_2_HTML_EXPORT
		i = pocet; // backwards; param[0] by mal síce obsahovať query type, ale radšej kontrolujeme až po 0
		LogParams("attempt to get value of param %s... parseQueryString(), force, bit-komponenty 2 / pom_FORCE_OPT_2_HTML_EXPORT[%d] = %s\n", local_str, j, pom_FORCE_OPT_2_HTML_EXPORT[j]);
		while ((equalsi(pom_FORCE_OPT_2_HTML_EXPORT[j], STR_EMPTY)) && (i > 0)) {
			--i;
			// LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, local_str)) {
				// ide o parameter STR_FORCE_OPT_j
				mystrcpy(pom_FORCE_OPT_2_HTML_EXPORT[j], param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", local_str, pom_FORCE_OPT_2_HTML_EXPORT[j]);
			}
		}
		if (equalsi(pom_FORCE_OPT_2_HTML_EXPORT[j], STR_EMPTY)) {
			LogParams("Nebola zadaná premenná %s (nevadí).\n", local_str);
		}
	}// for j

	// force option 5 premenné -- jednotlivé bit-komponenty
	// Pre POST query sa tam hodnota priliepa pre jednotlivý check-box zo začiatku (rovnako ako kalendár), aj sa číta z form-ulára (t. j. pri výbere z qt=pdnes), 
	// preto čítam "odzadu", "zozadu" (backwards) (rovnako ako kalendár), ak by sa nešlo smerom "dolu" (t. j. k prvému parametru od konca), 
	// nefungovalo by "override" z tabuľky "Voľby vybraných detailov", ak už v query stringu nejaká hodnota je
	LogParams("force option %d, jednotlivé bit-komponenty...(parseQuery)\n", OPT_5_ALTERNATIVES);
	for (j = 0; j < POCET_OPT_5_ALTERNATIVES; j++) {
		LogParams("j == %d...\n", j);
		mystrcpy(local_str, STR_EMPTY, SMALL);

		strcat_str_opt_bit_order(local_str, OPT_5_ALTERNATIVES, j);

		// premenná WWW_FORCE_BIT_OPT_5_... (nepovinná), j = 0 až POCET_OPT_5_ALTERNATIVES
		i = pocet; // backwards; param[0] by mal síce obsahovať query type, ale radšej kontrolujeme až po 0
		LogParams("attempt to get value of param %s... parseQueryString(), force, bit-komponenty 5 / pom_FORCE_OPT_5_ALTERNATIVES[%d] = %s\n", local_str, j, pom_FORCE_OPT_5_ALTERNATIVES[j]);
		while ((equalsi(pom_FORCE_OPT_5_ALTERNATIVES[j], STR_EMPTY)) && (i > 0)) {
			--i;
			// LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, local_str)) {
				// ide o parameter STR_FORCE_OPT_j
				mystrcpy(pom_FORCE_OPT_5_ALTERNATIVES[j], param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", local_str, pom_FORCE_OPT_5_ALTERNATIVES[j]);
			}
		}
		if (equalsi(pom_FORCE_OPT_5_ALTERNATIVES[j], STR_EMPTY)) {
			LogParams("Nebola zadaná premenná %s (nevadí).\n", local_str);
		}
	}// for j

	// force option 6 premenné -- jednotlivé decimal-place-komponenty
	LogParams("force option %d, jednotlivé decimal-place-komponenty...(parseQuery)\n", OPT_6_ALTERNATIVES_MULTI);
	for (j = 0; j < POCET_OPT_6_ALTERNATIVES_MULTI; j++) {
		LogParams("j == %d...\n", j);
		mystrcpy(local_str, STR_EMPTY, SMALL);

		strcat_str_opt_bit_order(local_str, OPT_6_ALTERNATIVES_MULTI, j);

		// premenná WWW_FORCE_PLACE_OPT_6_... (nepovinná), j = 0 až POCET_OPT_6_ALTERNATIVES_MULTI
		i = pocet; // backwards; param[0] by mal síce obsahovať query type, ale radšej kontrolujeme až po 0
		LogParams("attempt to get value of param %s... parseQueryString(), force, bit-komponenty 6 / pom_FORCE_OPT_6_ALTERNATIVES_MULTI[%d] = %s\n", local_str, j, pom_FORCE_OPT_6_ALTERNATIVES_MULTI[j]);
		while ((equalsi(pom_FORCE_OPT_6_ALTERNATIVES_MULTI[j], STR_EMPTY)) && (i > 0)) {
			--i;
			// LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, local_str)) {
				// ide o parameter STR_FORCE_OPT_j
				mystrcpy(pom_FORCE_OPT_6_ALTERNATIVES_MULTI[j], param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", local_str, pom_FORCE_OPT_6_ALTERNATIVES_MULTI[j]);
			}
		}
		if (equalsi(pom_FORCE_OPT_6_ALTERNATIVES_MULTI[j], STR_EMPTY)) {
			LogParams("Nebola zadaná premenná %s (nevadí).\n", local_str);
		}
	}// for j

	// presunuté sem spred parsovania option premenných
	if (ok != ANO) {
		// samotné vypísanie niečoho presunuté do hlavnej funkcie
		// ani jeden z parametrov neobsahuje query type alebo obsahuje neznámy qt
		if (i >= pocet) {
			mystrcpy(errmsg, "Chýbajúci parameter pre query type.\n", SMALL);
		}
		else {
			// síce bol query type parameter, ale hodnota je chybná
			sprintf(errmsg, "Chybný parameter: %s\n", param[i - 1].name);
		}
		strcat(bad_param_str, errmsg);
		ret = FAILURE;
		goto END_parseQueryString;
	}

	LogParams("\tswitch(query_type)...\n");
	switch (query_type) {
	case PRM_DNES: {
		// doplnené kvôli tomu, aby aj pre PRM_DNES mohla byť modlitba resp. svätec
		LogParams("\tcase PRM_DNES...\n");
		// nasledujúca pasáž prevzatá a upravená podľa PRM_DATUM; opätovne 2006-08-01

		// premenná MODLITBA (nepovinná)
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_MODLITBA);
		while ((equalsi(pom_MODLITBA, STR_EMPTY)) && (i < pocet)) {
			// LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_MODLITBA)) {
				// ide o parameter STR_MODLITBA
				mystrcpy(pom_MODLITBA, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_MODLITBA, pom_MODLITBA);
			}
			i++;
		}
		if (equalsi(pom_MODLITBA, STR_EMPTY)) {
			LogParams("Nebola zadaná premenná %s (nevadí).\n", STR_MODLITBA);
		}

		// premenná DALSI_SVATY (nepovinná)
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_DALSI_SVATY);
		while ((equalsi(pom_DALSI_SVATY, STR_EMPTY)) && (i < pocet)) {
			// LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_DALSI_SVATY)) {
				// ide o parameter STR_DALSI_SVATY
				mystrcpy(pom_DALSI_SVATY, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_DALSI_SVATY, pom_DALSI_SVATY);
			}
			i++;
		}
		if (equalsi(pom_DALSI_SVATY, STR_EMPTY)) {
			LogParams("Nebola zadaná premenná %s (nevadí).\n", STR_DALSI_SVATY);
		}

		break; // case
	}// PRM_DNES

	case PRM_STATIC_TEXT: {
		// doplnené kvôli možnosti includovať statický text/ordinárium
		LogParams("\tcase PRM_STATIC_TEXT...\n");

		// premenná STATIC_TEXT
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_STATIC_TEXT);
		while ((equalsi(pom_STATIC_TEXT, STR_EMPTY)) && (i < pocet)) {
			LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_STATIC_TEXT)) {
				// ide o parameter STR_NAZOV_SVIATOK
				mystrcpy(pom_STATIC_TEXT, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_STATIC_TEXT, pom_STATIC_TEXT);
			}
			i++;
		}
		if (equalsi(pom_STATIC_TEXT, STR_EMPTY)) {
			// samotné vypísanie niečoho presunuté do hlavnej funkcie
			sprintf(errmsg, "Nebola zadaná premenná %s.\n", STR_STATIC_TEXT);
			strcat(bad_param_str, errmsg);
			ret = FAILURE;
			goto END_parseQueryString;
		}

		// premenná MODL_ORDINARIUM (nepovinná)
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_MODL_ORDINARIUM);
		while ((equalsi(pom_MODL_ORDINARIUM, STR_EMPTY)) && (i < pocet)) {
			LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_MODL_ORDINARIUM)) {
				// ide o parameter STR_NAZOV_SVIATOK
				mystrcpy(pom_MODL_ORDINARIUM, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_MODL_ORDINARIUM, pom_MODL_ORDINARIUM);
			}
			i++;
		}

		// if still empty, try to use STR_MODLITBA instead of STR_MODL_ORDINARIUM
		if (equalsi(pom_MODL_ORDINARIUM, STR_EMPTY)) {
			i = 0;
			LogParams("attempt to get value of param %s using %s...\n", STR_MODL_ORDINARIUM, STR_MODLITBA);
			while ((equalsi(pom_MODL_ORDINARIUM, STR_EMPTY)) && (i < pocet)) {
				LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
				if (equals(param[i].name, STR_MODLITBA)) {
					// ide o parameter STR_NAZOV_SVIATOK
					mystrcpy(pom_MODL_ORDINARIUM, param[i].val, SMALL);
					LogParams("hodnota parametra %s je %s.\n", STR_MODLITBA, pom_MODL_ORDINARIUM);
				}
				i++;
			}
		}

		if (equalsi(pom_MODL_ORDINARIUM, STR_EMPTY)) {
			// 2013-07-31: samotné vypísanie niečoho presunuté do hlavnej funkcie
			sprintf(errmsg, "Nebola zadaná premenná %s (nevadí).\n", STR_MODL_ORDINARIUM);
		}

		break; // case
	}// PRM_STATIC_TEXT

	case PRM_DETAILY:
		// presne to iste co PRM_DATUM s jedinkym rozdielom: co sa tyka formularov, prvy (uvodny) formular pre PRM_DATUM vycisti modlitbu 
		// (premenna pom_MODLITBA, ktora sa nacita zo systemovej premennej WWW_MODLITBA) -- pretoze z inej casti fomrulara sa tam nieco dostane...
	case PRM_TXT:
		// 2011-02-02: doplnené
	case PRM_XML:
		// 2012-10-16: doplnené
	case PRM_DATUM: {
		// pripad, ze ide o datum

		// treba dodrzat presne poradie v query stringu;
		//   '()' znaci optional,
		//   '[]' znaci vyssie uvedeny typ dotazu.
		// ----------------------------------------------
		// 2005-03-22: pridane dalsie vyznamy opt_1 a opt_2
		// ----------------------------------------------
		// 0: [query type]
		// 1: den          / rok from
		// 2: mesiac       / rok to
		// 3: rok          / (linky) -- tieto tri `alternativne' parametre pre typ dotazu case PRM_TABULKA:, vid nizsie
		// 4: (modlitba)
		// 5: (dalsi svaty) - poradie svateho
		// 6 a viac: options
		// ---------------------------------------------
		// 2006-02-10: pridané možnosti vymeneného poradia a nezadania niektorých options
		// ----------------------------------------------
		// na základe dodania case-u pre PRM_DNES
		// ---------------------------------------------
		// 2006-08-01: dynamické zisťovanie hodnôt parametrov
		// ----------------------------------------------

		// premenná DEN
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_DEN);
		while ((equalsi(pom_DEN, STR_EMPTY)) && (i < pocet)) {
			// LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_DEN)) {
				// ide o parameter STR_DEN
				mystrcpy(pom_DEN, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_DEN, pom_DEN);
			}
			i++;
		}
		if (equalsi(pom_DEN, STR_EMPTY) && (query_type != PRM_XML)) {
			sprintf(errmsg, "Nebola zadaná premenná %s.\n", STR_DEN);
			strcat(bad_param_str, errmsg);
			ret = FAILURE;
			goto END_parseQueryString;
		}

		// premenná MESIAC 
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_MESIAC);
		while ((equalsi(pom_MESIAC, STR_EMPTY)) && (i < pocet)) {
			// LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_MESIAC)) {
				// ide o parameter STR_MESIAC
				mystrcpy(pom_MESIAC, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_MESIAC, pom_MESIAC);
			}
			i++;
		}
		if (equalsi(pom_MESIAC, STR_EMPTY) && (query_type != PRM_XML)) {
			sprintf(errmsg, "Nebola zadaná premenná %s.\n", STR_MESIAC);
			strcat(bad_param_str, errmsg);
			ret = FAILURE;
			goto END_parseQueryString;
		}

		// premenná ROK
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_ROK);
		while ((equalsi(pom_ROK, STR_EMPTY)) && (i < pocet)) {
			// LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_ROK)) {
				// ide o parameter STR_ROK
				mystrcpy(pom_ROK, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_ROK, pom_ROK);
			}
			i++;
		}
		if (equalsi(pom_ROK, STR_EMPTY) && (query_type != PRM_XML)) {
			sprintf(errmsg, "Nebola zadaná premenná %s.\n", STR_ROK);
			strcat(bad_param_str, errmsg);
			ret = FAILURE;
			goto END_parseQueryString;
		}

		// premenná MODLITBA (nepovinná)
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_MODLITBA);
		while ((equalsi(pom_MODLITBA, STR_EMPTY)) && (i < pocet)) {
			// LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_MODLITBA)) {
				// ide o parameter STR_MODLITBA
				mystrcpy(pom_MODLITBA, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_MODLITBA, pom_MODLITBA);
			}
			i++;
		}
		if (equalsi(pom_MODLITBA, STR_EMPTY)) {
			Log("Nebola zadaná premenná %s (nevadí).\n", STR_MODLITBA);
		}

		// premenná DALSI_SVATY (nepovinná)
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_DALSI_SVATY);
		while ((equalsi(pom_DALSI_SVATY, STR_EMPTY)) && (i < pocet)) {
			// LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_DALSI_SVATY)) {
				// ide o parameter STR_DALSI_SVATY
				mystrcpy(pom_DALSI_SVATY, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_DALSI_SVATY, pom_DALSI_SVATY);
			}
			i++;
		}
		if (equalsi(pom_DALSI_SVATY, STR_EMPTY)) {
			LogParams("Nebola zadaná premenná %s (nevadí).\n", STR_DALSI_SVATY);
		}

		/*
		// if day, month and/or year is not supplied, for XML export use current timestamp
		if ((query_type == PRM_XML) && (equalsi(pom_DEN, STR_EMPTY) || equalsi(pom_MESIAC, STR_EMPTY) || equalsi(pom_ROK, STR_EMPTY))) {
			struct tm dnes = _get_dnes();
			sprintf(pom_DEN, "%d", dnes.tm_mday);
			sprintf(pom_MESIAC, "%d", dnes.tm_mon);
			sprintf(pom_ROK, "%d", dnes.tm_year);
		}
		*/

		break; // case
	}// PRM_DETAILY | PRM_TXT | PRM_XML | PRM_DATUM

	case PRM_CEZ_ROK: {
		// pripad, ze ide o tyzden cez rok

		// premenná DEN_V_TYZDNI 
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_DEN_V_TYZDNI);
		while ((equalsi(pom_DEN_V_TYZDNI, STR_EMPTY)) && (i < pocet)) {
			LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_DEN_V_TYZDNI)) {
				// ide o parameter STR_DEN_V_TYZDNI
				mystrcpy(pom_DEN_V_TYZDNI, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_DEN_V_TYZDNI, pom_DEN_V_TYZDNI);
			}
			i++;
		}
		if (equalsi(pom_DEN_V_TYZDNI, STR_EMPTY)) {
			sprintf(errmsg, "Nebola zadaná premenná %s.\n", STR_DEN_V_TYZDNI);
			strcat(bad_param_str, errmsg);
			ret = FAILURE;
			goto END_parseQueryString;
		}

		// premenná TYZDEN 
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_TYZDEN);
		while ((equalsi(pom_TYZDEN, STR_EMPTY)) && (i < pocet)) {
			LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_TYZDEN)) {
				// ide o parameter STR_TYZDEN
				mystrcpy(pom_TYZDEN, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_TYZDEN, pom_TYZDEN);
			}
			i++;
		}
		if (equalsi(pom_TYZDEN, STR_EMPTY)) {
			sprintf(errmsg, "Nebola zadaná premenná %s.\n", STR_TYZDEN);
			strcat(bad_param_str, errmsg);
			ret = FAILURE;
			goto END_parseQueryString;
		}

		// premenná MODLITBA 
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_MODLITBA);
		while ((equalsi(pom_MODLITBA, STR_EMPTY)) && (i < pocet)) {
			LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_MODLITBA)) {
				// ide o parameter STR_MODLITBA
				mystrcpy(pom_MODLITBA, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_MODLITBA, pom_MODLITBA);
			}
			i++;
		}
		if (equalsi(pom_MODLITBA, STR_EMPTY)) {
			// 2013-07-31: samotné vypísanie niečoho presunuté do hlavnej funkcie
			sprintf(errmsg, "Nebola zadaná premenná %s.\n", STR_MODLITBA);
			strcat(bad_param_str, errmsg);
			ret = FAILURE;
			goto END_parseQueryString;
		}

		break; // case
	}// PRM_CEZ_ROK

	case PRM_LIT_OBD: {

		// premenná DEN_V_TYZDNI
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_DEN_V_TYZDNI);
		while ((equalsi(pom_DEN_V_TYZDNI, STR_EMPTY)) && (i < pocet)) {
			LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_DEN_V_TYZDNI)) {
				// ide o parameter STR_DEN_V_TYZDNI
				mystrcpy(pom_DEN_V_TYZDNI, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_DEN_V_TYZDNI, pom_DEN_V_TYZDNI);
			}
			i++;
		}
		if (equalsi(pom_DEN_V_TYZDNI, STR_EMPTY)) {
			sprintf(errmsg, "Nebola zadaná premenná %s.\n", STR_DEN_V_TYZDNI);
			strcat(bad_param_str, errmsg);
			ret = FAILURE;
			goto END_parseQueryString;
		}

		// premenná TYZDEN 
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_TYZDEN);
		while ((equalsi(pom_TYZDEN, STR_EMPTY)) && (i < pocet)) {
			LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_TYZDEN)) {
				// ide o parameter STR_TYZDEN
				mystrcpy(pom_TYZDEN, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_TYZDEN, pom_TYZDEN);
			}
			i++;
		}
		if (equalsi(pom_TYZDEN, STR_EMPTY)) {
			sprintf(errmsg, "Nebola zadaná premenná %s.\n", STR_TYZDEN);
			strcat(bad_param_str, errmsg);
			ret = FAILURE;
			goto END_parseQueryString;
		}

		// premenná MODLITBA 
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_MODLITBA);
		while ((equalsi(pom_MODLITBA, STR_EMPTY)) && (i < pocet)) {
			LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_MODLITBA)) {
				// ide o parameter STR_MODLITBA
				mystrcpy(pom_MODLITBA, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_MODLITBA, pom_MODLITBA);
			}
			i++;
		}
		if (equalsi(pom_MODLITBA, STR_EMPTY)) {
			// samotné vypísanie niečoho presunuté do hlavnej funkcie
			sprintf(errmsg, "Nebola zadaná premenná %s.\n", STR_MODLITBA);
			strcat(bad_param_str, errmsg);
			ret = FAILURE;
			goto END_parseQueryString;
		}

		// premenná LIT_OBD 
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_LIT_OBD);
		while ((equalsi(pom_LIT_OBD, STR_EMPTY)) && (i < pocet)) {
			LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_LIT_OBD)) {
				// ide o parameter STR_LIT_OBD
				mystrcpy(pom_LIT_OBD, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_LIT_OBD, pom_LIT_OBD);
			}
			i++;
		}
		if (equalsi(pom_LIT_OBD, STR_EMPTY)) {
			// samotné vypísanie niečoho presunuté do hlavnej funkcie
			sprintf(errmsg, "Nebola zadaná premenná %s.\n", STR_LIT_OBD);
			strcat(bad_param_str, errmsg);
			ret = FAILURE;
			goto END_parseQueryString;
		}

		// premenná LIT_ROK
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_LIT_ROK);
		while ((equalsi(pom_LIT_ROK, STR_EMPTY)) && (i < pocet)) {
			LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_LIT_ROK)) {
				// ide o parameter STR_LIT_ROK
				mystrcpy(pom_LIT_ROK, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_LIT_ROK, pom_LIT_ROK);
			}
			i++;
		}
		if (equalsi(pom_LIT_ROK, STR_EMPTY)) {
			// samotné vypísanie niečoho presunuté do hlavnej funkcie
			sprintf(errmsg, "Nebola zadaná premenná %s.\n", STR_LIT_ROK);
			strcat(bad_param_str, errmsg);
			ret = FAILURE;
			goto END_parseQueryString;
		}

		break; // case
	}// PRM_LIT_OBD

	case PRM_SVIATOK: {

		// premenná NAZOV_SVIATOK 
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_NAZOV_SVIATOK);
		while ((equalsi(pom_SVIATOK, STR_EMPTY)) && (i < pocet)) {
			LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_NAZOV_SVIATOK)) {
				// ide o parameter STR_NAZOV_SVIATOK
				mystrcpy(pom_SVIATOK, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_NAZOV_SVIATOK, pom_SVIATOK);
			}
			i++;
		}
		if (equalsi(pom_SVIATOK, STR_EMPTY)) {
			// samotné vypísanie niečoho presunuté do hlavnej funkcie
			sprintf(errmsg, "Nebola zadaná premenná %s.\n", STR_NAZOV_SVIATOK);
			strcat(bad_param_str, errmsg);
			ret = FAILURE;
			goto END_parseQueryString;
		}

		break; // case
	}// PRM_SVIATOK

	case PRM_ANALYZA_ROKU: {

		// premenná ANALYZA_ROKU 
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_ANALYZA_ROKU);
		while ((equalsi(pom_ANALYZA_ROKU, STR_EMPTY)) && (i < pocet)) {
			LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_ANALYZA_ROKU)) {
				// ide o parameter STR_ANALYZA_ROKU
				mystrcpy(pom_ANALYZA_ROKU, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_ANALYZA_ROKU, pom_ANALYZA_ROKU);
			}
			i++;
		}
		if (equalsi(pom_ANALYZA_ROKU, STR_EMPTY)) {
			sprintf(errmsg, "Nebola zadaná premenná %s.\n", STR_ANALYZA_ROKU);
			strcat(bad_param_str, errmsg);
			ret = FAILURE;
			goto END_parseQueryString;
		}

		break; // case
	}// PRM_ANALYZA_ROKU

	case PRM_MESIAC_ROKA: {

		// premenná MESIAC
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_MESIAC_ROKA);
		while ((equalsi(pom_MESIAC, STR_EMPTY)) && (i < pocet)) {
			LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_MESIAC_ROKA)) {
				// ide o parameter STR_MESIAC_ROKA
				mystrcpy(pom_MESIAC, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_MESIAC_ROKA, pom_MESIAC);
			}
			i++;
		}
		if (equalsi(pom_MESIAC, STR_EMPTY)) {
			sprintf(errmsg, "Nebola zadaná premenná %s.\n", STR_MESIAC_ROKA);
			strcat(bad_param_str, errmsg);
			ret = FAILURE;
			goto END_parseQueryString;
		}

		// premenná ROK
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_ROK_ROKA);
		while ((equalsi(pom_ROK, STR_EMPTY)) && (i < pocet)) {
			LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_ROK_ROKA)) {
				// ide o parameter STR_ROK_ROKA
				mystrcpy(pom_ROK, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_ROK_ROKA, pom_ROK);
			}
			i++;
		}
		if (equalsi(pom_ROK, STR_EMPTY)) {
			sprintf(errmsg, "Nebola zadaná premenná %s.\n", STR_ROK_ROKA);
			strcat(bad_param_str, errmsg);
			ret = FAILURE;
			goto END_parseQueryString;
		}

		break; // case
	}// PRM_MESIAC_ROKA

	case PRM_TABULKA: {

		// premenná ROK_FROM
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_ROK_FROM);
		while ((equalsi(pom_ROK_FROM, STR_EMPTY)) && (i < pocet)) {
			LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_ROK_FROM)) {
				// ide o parameter STR_ROK_FROM
				mystrcpy(pom_ROK_FROM, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_ROK_FROM, pom_ROK_FROM);
			}
			i++;
		}
		if (equalsi(pom_ROK_FROM, STR_EMPTY)) {
			// samotné vypísanie niečoho presunuté do hlavnej funkcie
			sprintf(errmsg, "Nebola zadaná premenná %s.\n", STR_ROK_FROM);
			strcat(bad_param_str, errmsg);
			ret = FAILURE;
			goto END_parseQueryString;
		}

		// premenná ROK_TO
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_ROK_TO);
		while ((equalsi(pom_ROK_TO, STR_EMPTY)) && (i < pocet)) {
			LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_ROK_TO)) {
				// ide o parameter STR_ROK_TO
				mystrcpy(pom_ROK_TO, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_ROK_TO, pom_ROK_TO);
			}
			i++;
		}
		if (equalsi(pom_ROK_TO, STR_EMPTY)) {
			// 2013-07-31: samotné vypísanie niečoho presunuté do hlavnej funkcie
			sprintf(errmsg, "Nebola zadaná premenná %s.\n", STR_ROK_TO);
			strcat(bad_param_str, errmsg);
			ret = FAILURE;
			goto END_parseQueryString;
		}

		// premenná TABULKA_LINKY (nepovinná)
		i = 0; // param[0] by mal síce obsahovať query type, ale radšej kontrolujeme od 0
		LogParams("attempt to get value of param %s...\n", STR_TABULKA_LINKY);
		while ((equalsi(pom_LINKY, STR_EMPTY)) && (i < pocet)) {
			LogParams("...parameter %d (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
			if (equals(param[i].name, STR_TABULKA_LINKY)) {
				// ide o parameter STR_TABULKA_LINKY
				mystrcpy(pom_LINKY, param[i].val, SMALL);
				LogParams("hodnota parametra %s je %s.\n", STR_TABULKA_LINKY, pom_LINKY);
			}
			i++;
		}
		if (equalsi(pom_LINKY, STR_EMPTY)) {
			LogParams("Nebola zadaná premenná %s (nevadí).\n", STR_TABULKA_LINKY);
		}

		break; // case
	}// PRM_TABULKA
	}
	ret = SUCCESS;

END_parseQueryString:
	Log("parseQueryString() -- end, returning %d.\n", ret);
	return ret;
}// parseQueryString();

#define _main_LOG_to_Export_PARAMS {\
	_main_LOG_to_Export("\tparam1 == %s (pom_DEN/pom_SVIATOK/pom_DEN_V_TYZDNI), param1 == %s (pom_ROK_FROM resp. DEN DO pre batch mode)\n", pom_DEN, pom_ROK_FROM);\
	_main_LOG_to_Export("\tparam2 == %s (pom_MESIAC/pom_TYZDEN), param2 == %s (pom_ROK_TO resp. MESIAC DO pre batch mode)\n", pom_MESIAC, pom_ROK_TO);\
	_main_LOG_to_Export("\tparam3 == %s (pom_ROK/pom_ANALYZA_ROKU), param3 == %s (pom_LINKY)\n", pom_ROK, pom_LINKY);\
	_main_LOG_to_Export("\tparam4 == %s (pom_MODLITBA resp. ROK DO pre batch mode)\n", pom_MODLITBA);\
	_main_LOG_to_Export("\tparam5 == %s (pom_DALSI_SVATY)\n", pom_DALSI_SVATY);\
	_main_LOG_to_Export("\tparam11== %s (pom_OPT_APPEND)\n", pom_OPT_APPEND);\
	_main_LOG_to_Export("\tparam12== %s (pom_JAZYK)\n", pom_JAZYK);\
	_main_LOG_to_Export("\tparam  == %s (pom_KALENDAR)\n", pom_KALENDAR);\
	_main_LOG_to_Export("\tparam  == %s (pom_CSS)\n", pom_CSS);\
	_main_LOG_to_Export("\tparam  == %s (pom_FONT)\n", pom_FONT);\
	_main_LOG_to_Export("\tparam  == %s (pom_FONT_SIZE)\n", pom_FONT_SIZE);\
	_main_LOG_to_Export("\tparam  == %s (pom_FONT_SIZE_PT)\n", pom_FONT_SIZE_PT);\
	_main_LOG_to_Export("\tparam  == %s (pom_STYLE_MARGIN)\n", pom_STYLE_MARGIN);\
	_main_LOG_to_Export("\tparam  == %s (pom_LINE_HEIGHT_PERC)\n", pom_LINE_HEIGHT_PERC);\
	_main_LOG_to_Export("\tparam  == %s (pom_OPT_DATE_FORMAT)\n", pom_OPT_DATE_FORMAT);\
	_main_LOG_to_Export("\tparam  == %s (pom_EXPORT_MONTHLY)\n", pom_EXPORT_MONTHLY);\
	for(i = 0; i < POCET_GLOBAL_OPT; i++) {\
		_main_LOG_to_Export("\tparam  == %s (pom_OPT[%d])\n", pom_OPT[i], i);\
	}\
	for(i = 0; i < POCET_GLOBAL_OPT; i++) {\
		_main_LOG_to_Export("\tparam  == %s (pom_FORCE_OPT[%d])\n", pom_FORCE_OPT[i], i);\
	}\
}

short int counter_setConfigDefaults = 0;

void setConfigDefaults(short int jazyk) {
	unsigned long long sk_default;
	short int i;
	counter_setConfigDefaults++;
	Log("setConfigDefaults(%d) -- začiatok (%d. volanie)...\n", jazyk, counter_setConfigDefaults);

	for (i = 0; i < POCET_GLOBAL_OPT; i++) {
		if (jazyk != JAZYK_SK) {
			sk_default = cfg_option_default[i][JAZYK_SK];
		}
		else {
			sk_default = GLOBAL_OPTION_NULL;
		}
		if (cfg_option_default[i][jazyk] == GLOBAL_OPTION_NULL) {
			cfg_option_default[i][jazyk] = (sk_default == GLOBAL_OPTION_NULL) ? cfg_option_default_PROG[i] : sk_default;
			Log("keďže cfg_option_default[%d][%d] bolo GLOBAL_OPTION_NULL, nastavujem podľa program defaults na %ld...\n", i, jazyk, cfg_option_default[i][jazyk]);
		}
	}// for i

	setConfigDefaultsOther(_global_jazyk);

	Log("setConfigDefaults(%d) -- koniec (%d. volanie).\n", jazyk, counter_setConfigDefaults);
}// setConfigDefaults()

void init_global_string_as_html_title(short int den, short int mesiac, short int rok, short int modlitba) {
	Log("init_global_string_as_html_title(%d, %d, %d, %d): begin...\n", den, mesiac, rok, modlitba);

	mystrcpy(_global_string, STR_EMPTY, MAX_GLOBAL_STR); // inicializácia

	short int use_numbers_instead_month_names = NIE;
	char delimiter_dash[SMALL] = STR_EMPTY;
	char delimiter_bar[SMALL] = STR_EMPTY;

	mystrcpy(delimiter_dash, STR_EN_DASH_WITH_SPACES, SMALL);
	mystrcpy(delimiter_bar, STR_VERTICAL_BAR_WITH_SPACES, SMALL);

	struct tm dnes = _get_dnes();
	Log("dnes/today: tm_mday == %d, tm_mon == %d, tm_year == %d [note: struct tm has tm_mon 1..12 while our constants are 0..11]...\n", dnes.tm_mday, dnes.tm_mon, dnes.tm_year);

	short int input_date_is_today = NIE; // whether input parameters form current timestamp's day

	if ((den == dnes.tm_mday) && (mesiac == dnes.tm_mon - 1) && (rok == dnes.tm_year)) {
		// note: struct tm has tm_mon 1..12 while our constants are 0..11
		input_date_is_today = ANO;
		Log("chosen day is the same as current timestamp's day (today).\n");
	}

#if defined(IO_ANDROID) || defined (__APPLE__)
	// no prefix for mobile apps ["app name" as title will be added in special cases]
	// force using month numbers due to small space on action bar
	use_numbers_instead_month_names = ANO;

	mystrcpy(delimiter_dash, STR_VERTICAL_BAR_WITH_SPACES, SMALL);
#elif defined(OS_Windows_Ruby) || defined(OS_Windows)
	// for debugging & testing: language + calendar shortcuts, e. g. "SK SVD | " or "CZ OFMCap. | "
	mystrcpy(_global_string, skratka_jazyka_title[_global_jazyk], MAX_STR);

	if ((_global_kalendar != default_kalendar[_global_jazyk]) && (strlen(nazov_kalendara_propria_only[_global_kalendar]) > 0)) {
		Log("_global_kalendar == %d (%s)...\n", _global_kalendar, nazov_kalendara_propria_only[_global_kalendar]);
		strcat(_global_string, STR_SPACE);
		strcat(_global_string, nazov_kalendara_propria_only[_global_kalendar]);
	}

	strcat(_global_string, delimiter_bar);
#else
	// for web, add "website name" as title
	mystrcpy(_global_string, html_title[_global_jazyk], MAX_GLOBAL_STR); // inicializácia

	strcat(_global_string, delimiter_bar);
#endif

	// add string/date for selected day, year, prayer (fits for most cases)
	if ((query_type == PRM_DNES) || (input_date_is_today == ANO)) {
		strcat(_global_string, html_button_Dnes[_global_jazyk]);
	}
	else if (query_type == PRM_STATIC_TEXT) {
		Log("init_global_string_as_html_title(): query_type == PRM_STATIC_TEXT, rok == %d...\n", rok);
		if ((rok <= STATIC_TEXT_UNDEF) || (rok > POCET_STATIC_TEXTOV)) {
			rok = STATIC_TEXT_INFO;
		}
		strcat(_global_string, html_title_static_text[rok][_global_jazyk]);
	}
	else if ((query_type == PRM_DATUM) || (query_type == PRM_TXT) || (query_type == PRM_ANALYZA_ROKU)) {
		strcat(_global_string, _vytvor_string_z_datumu_ext(den, mesiac + 1, rok, ((_global_jazyk == JAZYK_LA) || (_global_jazyk == JAZYK_EN)) ? CASE_Case : CASE_case, NIE, use_numbers_instead_month_names));
	}

	// no additional text for Mary's antiphones & incorrect info text numbers
	if (query_type == PRM_STATIC_TEXT) {
		if (rok == STATIC_TEXT_MARIANSKE_ANTIFONY) {
			modlitba = MODL_NEURCENA;
		}
		if ((rok == STATIC_TEXT_INFO) && !((modlitba >= INFO_ABOUT) && (modlitba <= POCET_INFO_TEXTOV))) {
			modlitba = MODL_NEURCENA;
		}
	}

	if (modlitba != MODL_NEURCENA) {
		// if anything is in _global_string, add dashes + prayer name...
		if (strlen(_global_string) > 0) {
			strcat(_global_string, delimiter_dash);

			if ((query_type == PRM_STATIC_TEXT) && (rok == STATIC_TEXT_INFO)) {
				if ((modlitba >= INFO_ABOUT) && (modlitba <= POCET_INFO_TEXTOV)) {
					strcat(_global_string, html_subtitle_static_text_info[modlitba][_global_jazyk]);
				}
				// otherwise, nothing (eventhough delimiter_dash might be already exported)
			}
			else {
				// for query_type == PRM_STATIC_TEXT: case STATIC_TEXT_ORDINARIUM; all other values of query_type
				strcat(_global_string, nazov_modlitby(modlitba));
			}
		}
		else {
			// ...otherwise, add prayer only...
			if (modlitba != MODL_NEURCENA) {
				strcat(_global_string, nazov_Modlitby(modlitba));
			}
			else {
				// ...or just website/application name
#if defined(IO_ANDROID) || defined (__APPLE__)
				mystrcpy(_global_string, html_app_name[_global_jazyk], MAX_GLOBAL_STR);
#else
				mystrcpy(_global_string, html_title[_global_jazyk], MAX_GLOBAL_STR);
#endif
			}
		}
	}
	Log("init_global_string_as_html_title(%d, %d, %d, %d): end.\n", den, mesiac, rok, modlitba);
}// init_global_string_as_html_title()

void normalize_calendar_for_language() {
	Log("normalize_calendar_for_language(): begin...\n");

	// check whether desired calendar is possible for selected language
	_main_LOG_to_Export("kontrola kalendár (%s | %s) vs. jazyk (%s | %s)...\n", nazov_kalendara_short[_global_kalendar], skratka_kalendara[_global_kalendar], nazov_jazyka(_global_jazyk), skratka_jazyka[_global_jazyk]);

#ifdef DEBUG
	// this special change is just for debugging reasons (for Czech language, behave as if CZ OP would be another calendar though it is not listed among supported_calendars[] for JAZYK_CZ
	if (_global_jazyk == JAZYK_CZ && _global_kalendar == KALENDAR_CZ_OP) {
		Log("normalize_calendar_for_language(): special case for CZ language and CZOP calendar...\n");
		_global_jazyk = JAZYK_CZ_OP;
	}
#endif

	short int c = 0;

	for (c = 0; c < supported_calendars_count[_global_jazyk]; c++) {
		if (supported_calendars(c) == _global_kalendar) {
			Log("...OK.\n");
			break;
		}
	}

	if (c >= supported_calendars_count[_global_jazyk]) {
		_global_kalendar = default_kalendar[_global_jazyk];
		Log("kalendár zmenený na default pre daný jazyk (%d teda %s | %s).", _global_kalendar, nazov_kalendara_short[_global_kalendar], skratka_kalendara[_global_kalendar]);
	}

	Log("normalize_calendar_for_language(): end.\n");
}

// main
int breviar_main(int argc, const char** argv) {
	short int i;
	short int local_den, local_mesiac, local_rok, local_modlitba;

	// naplnenie _global_system
#if defined(OS_linux)
	_global_system = SYSTEM_LINUX;
#elif defined(OS_Windows_Ruby)
	_global_system = SYSTEM_RUBY;
#else
	_global_system = SYSTEM_WINDOWS;
#endif

#ifdef IO_ANDROID
	isAndroid = ANO;
#else
	isAndroid = NIE;
#endif // IO_ANDROID

	// pretoze pocas behu win32-release verzie on-line breviara sa spusta main() viackrat bez zrusenia programu,
	// je potrebne inicializovat globalne premenne pri kazdom pusteni jej behu
	// prerobenie čítania jazyka (skopírované ešte na jedno vyššie miesto); už by sa <title> malo vypisovať pri generovaní inojazyčných modlitieb správne
	myhpage_init_globals();

	// for _breviar_env, must be included within if-def
#if defined(_BREVIAR_ENV)
	memset(_breviar_env, 0, sizeof(_breviar_env));
#endif /* _BREVIAR_ENV */
	memset(_global_opt, 0, sizeof(_global_opt));
	_global_opt[OPT_0_SPECIALNE] = GLOBAL_OPTION_NULL;
	_global_opt[OPT_1_CASTI_MODLITBY] = GLOBAL_OPTION_NULL;
	_global_opt[OPT_3_SPOLOCNA_CAST] = MODL_SPOL_CAST_NEURCENA;
	_global_opt[OPT_4_OFFLINE_EXPORT] = GLOBAL_OPTION_NULL;
	_global_opt[OPT_2_HTML_EXPORT] = GLOBAL_OPTION_NULL;
	counter_setConfigDefaults = 0;

	_global_opt_append = NIE;
	_global_opt_tedeum = NIE;
	_global_pocet_slava_otcu = 0;
	_global_ant_mcd_rovnake = NIE;
	_global_opt_export_date_format = EXPORT_DATE_SIMPLE;
	_global_opt_batch_monthly = NIE;
	_global_hlavicka_Export = 0;
	_global_patka_Export = 0;
	export_monthly_druh = 0;
	export_month_zaciatok = NIE;
	export_month_nova_modlitba = NIE;

	strcpy(pom_LIT_OBD, STR_EMPTY);
	strcpy(pom_LIT_ROK, STR_EMPTY);

	strcpy(pom_QUERY_TYPE, STR_EMPTY);
	strcpy(pom_DEN, STR_EMPTY);
	strcpy(pom_MESIAC, STR_EMPTY);
	strcpy(pom_ROK, STR_EMPTY);
	strcpy(pom_MODLITBA, STR_EMPTY);
	strcpy(pom_DALSI_SVATY, STR_EMPTY);
	strcpy(pom_ROK_FROM, STR_EMPTY);
	strcpy(pom_ROK_TO, STR_EMPTY);
	strcpy(pom_LINKY, STR_EMPTY);
	strcpy(pom_JAZYK, STR_EMPTY);
	strcpy(pom_CSS, STR_EMPTY);
	strcpy(pom_FONT, STR_EMPTY);
	strcpy(pom_FONT_SIZE, STR_EMPTY);
	strcpy(pom_FONT_SIZE_PT, STR_EMPTY);
	strcpy(pom_STYLE_MARGIN, STR_EMPTY);
	strcpy(pom_LINE_HEIGHT_PERC, STR_EMPTY);
	strcpy(pom_OPT_DATE_FORMAT, STR_EMPTY);
	strcpy(pom_EXPORT_MONTHLY, STR_EMPTY); // 2009-08-03: Pridané kvôli rôznym spôsobom exportu po mesiacoch, prepínač -M
	_global_modlitba = MODL_NEURCENA;

	memset(_global_opt, 0, sizeof(_global_opt));
	memset(_global_force_opt, 0, sizeof(_global_force_opt));
	memset(_global_opt_0_specialne, 0, sizeof(_global_opt_0_specialne));
	memset(_global_opt_1_casti_modlitby, 0, sizeof(_global_opt_1_casti_modlitby));
	memset(_global_opt_2_html_export, 0, sizeof(_global_opt_2_html_export));
	memset(_global_opt_4_offline_export, 0, sizeof(_global_opt_4_offline_export));
	memset(_global_opt_5_alternatives, 0, sizeof(_global_opt_5_alternatives));
	memset(_global_opt_6_alternatives_multi, 0, sizeof(_global_opt_6_alternatives_multi));

	_global_jazyk = 0;
	_global_kalendar = 0;
	_global_ritus = 0;
	_global_css = 0;
	_global_font = 0;
	_global_font_size = 0;
	_global_style_margin = DEF_STYLE_MARGIN;
	_global_line_height_perc = DEF_LINE_HEIGHT_PERC;
	_global_override_thin_nbsp = NIE;

	_global_pocet_navigacia = 0;
	_global_pocet_volani_interpretTemplate = 0;

	_global_pocet_zalmov_kompletorium = 0;

	strcpy(_global_export_navig_hore, DEFAULT_MONTH_EXPORT);
	strcpy(_global_export_navig_hore_month, DEFAULT_MONTH_EXPORT);
	strcpy(_global_export_navig_hore_day, DEFAULT_MONTH_EXPORT);
	strcpy(_global_css_font_family, DEFAULT_FONT_FAMILY_SERIF);
	strcpy(_global_css_font_size, STR_EMPTY);

	_global_skip_in_prayer = NIE;
	_global_skip_in_prayer_2 = NIE;
	_global_skip_in_prayer_vnpc = NIE;
	_global_som_vo_vigilii = NIE;

	params = 0;

	strcpy(pom_OPT_APPEND, STR_EMPTY);
	strcpy(pom_KALENDAR, STR_EMPTY);

	memset(pom_OPT, 0, sizeof(pom_OPT));
	memset(pom_FORCE_OPT, 0, sizeof(pom_FORCE_OPT));
	memset(pom_FORCE_OPT_0_SPECIALNE, 0, sizeof(pom_FORCE_OPT_0_SPECIALNE));
	memset(pom_FORCE_OPT_1_CASTI_MODLITBY, 0, sizeof(pom_FORCE_OPT_1_CASTI_MODLITBY));
	memset(pom_FORCE_OPT_2_HTML_EXPORT, 0, sizeof(pom_FORCE_OPT_2_HTML_EXPORT));
	memset(pom_FORCE_OPT_4_OFFLINE_EXPORT, 0, sizeof(pom_FORCE_OPT_4_OFFLINE_EXPORT));
	memset(pom_FORCE_OPT_5_ALTERNATIVES, 0, sizeof(pom_FORCE_OPT_5_ALTERNATIVES));
	memset(pom_FORCE_OPT_6_ALTERNATIVES_MULTI, 0, sizeof(pom_FORCE_OPT_6_ALTERNATIVES_MULTI));

	strcpy(bad_param_str, STR_EMPTY);
	strcpy(file_export, STR_EMPTY);
	strcpy(include_dir, STR_EMPTY);
	strcpy(name_binary_executable, STR_EMPTY);
	strcpy(name_batch_file, STR_EMPTY);
	strcpy(name_batch_html_file, STR_EMPTY);
	strcpy(dir_name, STR_EMPTY);
	strcpy(name_batch_month_file, STR_EMPTY);
	strcpy(system_command, STR_EMPTY);

	memset(param, 0, sizeof(param));
	batch_file = NULL;
	batch_html_file = NULL;
	batch_month_file = NULL;
	index_pre_mesiac_otvoreny = NIE;

	_INIT_DM(_local_den);

#if defined(BEHAVIOUR_WEB)
	_global_linky = 1; // zobrazovať linky (pre batch mód: použiť URL)
#elif defined(BEHAVIOUR_CMDLINE)
	_global_linky = 0; // nezobrazovať linky (pre batch mód: použiť filenames)
#else
#error Unsupported behaviour (not defined in mysystem.h/mysysdef.h)
#endif

	short int ret, ret_pom = FAILURE; // návratová hodnota
	long len; // dĺžka

	initLog(FILE_LOG);

	_main_LOG("Content-type: text/html\n");
	_main_LOG("\n");

	_main_LOG("-- log file programu pre Liturgiu hodín " TEXT_COPYRIGHT " --\n");

	_main_LOG("inicializácia poľa pom_OPT[]...\n");
	for (i = 0; i < POCET_GLOBAL_OPT; i++) {
		mystrcpy(pom_OPT[i], STR_EMPTY, SMALL);
		// _main_LOG("pom_OPT[%d] == `%s'...\n", i, pom_OPT[i]);
	}// nastavenie pom_OPT[i]

	_main_LOG("inicializácia poľa pom_FORCE_OPT[]...\n");
	for (i = 0; i < POCET_GLOBAL_OPT; i++) {
		mystrcpy(pom_FORCE_OPT[i], STR_EMPTY, SMALL);
		// _main_LOG("pom_FORCE_OPT[%d] == `%s'...\n", i, pom_FORCE_OPT[i]);
	}// nastavenie pom_FORCE_OPT[i]

	// config
	_main_LOG("first, reading configuration (file %s)...\n", CONFIG_FILE);

	_main_LOG("spúšťam readConfig();...\n");
	readConfig();

	_main_LOG("spúšťam printConfig();...\n");
	printConfig();

	_main_LOG("spúšťam updateScriptName();...\n");
	updateScriptName();
	_main_LOG("script_name == %s\n", script_name);

	_main_LOG("spúšťam updateUnCGIName();...\n");
	updateUnCGIName();
	_main_LOG("uncgi_name == %s\n", uncgi_name);

	_main_LOG("spúšťam initExport();...\n");
	initExport();

	// basic check for MAX_POCET_OPT contant
	if ((MAX_POCET_OPT < POCET_OPT_0_SPECIALNE) || (MAX_POCET_OPT < POCET_OPT_1_CASTI_MODLITBY) || (MAX_POCET_OPT < POCET_OPT_2_HTML_EXPORT) || (MAX_POCET_OPT < POCET_OPT_4_OFFLINE_EXPORT) || (MAX_POCET_OPT < POCET_OPT_5_ALTERNATIVES) || (MAX_POCET_OPT < POCET_OPT_6_ALTERNATIVES_MULTI)) {
		_main_LOG("Incorrect setting of value for `MAX_POCET_OPT'.\n");
		goto _main_end;
	}

	// pre query_string musime alokovat pamat
	_main_LOG("/* pre query_string musime alokovat pamat */\n");
	_main_LOG("now allocating memory (1)...\n");

	// query_string
	if ((query_string = (char*)malloc(MAX_QUERY_STR)) == NULL) {
		_main_LOG("  Not enough memory to allocate buffer for `query_string'\n");
		goto _main_end;
	}
	else {
		_main_LOG("  %d bytes for `query_string'\n", MAX_QUERY_STR);
	}
	_main_LOG("...done.\n");

	// _global_buf
	if ((_global_buf = (char*)malloc(MAX_GLOBAL_STR)) == NULL) {
		Log("  Not enough memory to allocate buffer for `_global_buf'\n");
		goto _main_end;
	}
	else {
		_main_LOG("  %d bytes for `_global_buf'\n", MAX_GLOBAL_STR);
		mystrcpy(_global_buf, STR_EMPTY, MAX_GLOBAL_STR);
	}

	// _global_buf2
	if ((_global_buf2 = (char*)malloc(MAX_GLOBAL_STR)) == NULL) {
		Log("  Not enough memory to allocate buffer for `_global_buf2'\n");
		goto _main_end;
	}
	else {
		_main_LOG("  %d bytes for `_global_buf2'\n", MAX_GLOBAL_STR);
		mystrcpy(_global_buf2, STR_EMPTY, MAX_GLOBAL_STR);
	}

	// _global_pom_str
	if ((_global_pom_str = (char*)malloc(MAX_STR)) == NULL) {
		Log("  Not enough memory to allocate buffer for `_global_pom_str'\n");
		ret = FAILURE;
	}
	else {
		Log("  %d bytes for `_global_pom_str'\n", MAX_STR);
		mystrcpy(_global_pom_str, STR_UNDEF, MAX_STR);
	}

	_main_LOG("spustatm getSrciptParamFrom(argc == %d)...\n", argc);
	params = getSrciptParamFrom(argc);

	// vysledok je, ze sa do params nacita bud
	// SCRIPT_PARAM_FROM_FORM alebo
	// SCRIPT_PARAM_FROM_QS alebo
	// SCRIPT_PARAM_FROM_ARGV;
	//
	// ak vsak pouzivam aj query string, aj vysledky z formulara, vysledok bude predsa SCRIPT_PARAM_FROM_QS, lebo QS je neprazdny retazec; 
	// taku strategiu umoznuje uncgi.c:
	//        First, get the query string, wherever it is, and stick its component parts into the environment.
	//        Allow combination GET and POST queries, even though that's a bit strange.
	// takze v pripade, ze query string je neprazdny, treba
	// 1. zistit systemove premenne WWW_...
	// 2. zistit (a rozparsovat) QUERY_STRING

	ret = NO_RESULT;
	ret_pom = FAILURE;
	switch (params) {
		// v tomto switch() naplnime premennu query_type a naviac (ak su) premenne pom_...
	case SCRIPT_PARAM_FROM_FORM: {
		_main_LOG_to_Export("params == SCRIPT_PARAM_FROM_FORM\n");
		// neboli zadane ziadne parametre, teda citam z formulara

		query_type = getQueryTypeFrom_WWW();
		// zistili sme, aky je typ dotazu
		if (query_type == PRM_NONE) {
			// spusteny bez parametrov
			_main_LOG_to_Export("query_type == PRM_NONE\n");
			_main_LOG_to_Export("spustam _main_prazdny_formular();\n");
			_main_prazdny_formular();
			_main_LOG_to_Export("spat po skonceni _main_prazdny_formular()\n");
			goto _main_end;
		}
		else {
			_main_LOG_to_Export("spustam getForm();\n");
			ret_pom = ret = getForm();
			_main_LOG_to_Export("spat po skonceni getForm()\n");
		}
		break;
	}// SCRIPT_PARAM_FROM_FORM
	case SCRIPT_PARAM_FROM_ARGV: {
		_main_LOG("params == SCRIPT_PARAM_FROM_ARGV\n");
		_main_LOG("spustam getArgv();\n");
		// query_type sa nastavi priamo vovnutri
		ret_pom = ret = getArgv(argc, argv);
		if (ret == SUCCESS) {

			// parsovanie jazyka kvôli jazykovým mutáciám 
			_main_LOG_to_Export("zisťujem jazyk (pom_JAZYK == %s)...\n", pom_JAZYK);
			_global_jazyk = atojazyk(pom_JAZYK);
			if (_global_jazyk == JAZYK_UNDEF) {
				_global_jazyk = JAZYK_SK;
				_main_LOG_to_Export("\t(vzhľadom k neurčenému jazyku používam default)\n");
			}
			_main_LOG_to_Export("...jazyk (%s) = %d, teda %s (%s)\n", pom_JAZYK, _global_jazyk, nazov_jazyka(_global_jazyk), skratka_jazyka[_global_jazyk]);

			_main_LOG_to_Export("spúšťam setConfigDefaults()...\n");
			setConfigDefaults(_global_jazyk); // 2011-04-13: doplnené

			Log("volám _rozparsuj_parametre_OPT()... | breviar_main(), case SCRIPT_PARAM_FROM_ARGV\n");
			_rozparsuj_parametre_OPT();

			// parsovanie jazyka kvôli jazykovým mutáciám -- kalendár, napr. rehoľný (dané aj nižše, ako jazyk)
			_main_LOG_to_Export("zisťujem kalendár (pom_KALENDAR == %s)...\n", pom_KALENDAR);
			_global_kalendar = atokalendar(pom_KALENDAR);
			if (_global_kalendar == KALENDAR_NEURCENY) {
				_global_kalendar = KALENDAR_VSEOBECNY;
				_main_LOG_to_Export("\t(vzhľadom k neurčenému kalendáru používam default -- všeobecný kalendár)\n");
			}
			_main_LOG_to_Export("...kalendár (%s) = %d, teda %s (%s)\n", pom_KALENDAR, _global_kalendar, nazov_kalendara_short[_global_kalendar], skratka_kalendara[_global_kalendar]);

			normalize_calendar_for_language();

			// načítanie názvu fontu kvôli rôznym fontom
			_main_LOG_to_Export("zisťujem font...\n");
			_global_font = atofont(pom_FONT);
			_main_LOG_to_Export("...font (%s) = %d, teda %s\n", pom_FONT, _global_font, nazov_fontu[_global_font]);
			// for FONT_CUSTOM, we still use pom_FONT as global variable unless empty

			// načítanie veľkosti fontu
			_main_LOG_to_Export("zisťujem font size...\n");
			_global_font_size = atofontsize(pom_FONT_SIZE);
			if (_global_font_size == FONT_SIZE_UNDEF) {
				_global_font_size = FONT_SIZE_CSS;
				_main_LOG_to_Export("\t(vzhľadom k neurčenej font size používam default -- brať font size z CSS)\n");
			}
			_main_LOG_to_Export("...font size (%s) = %d, teda %s\n", pom_FONT_SIZE, _global_font_size, nazov_font_size(_global_font_size));

			// načítanie veľkosti fontu v pt (override)
			_main_LOG_to_Export("zisťujem font size pt...\n");
			_global_font_size_pt = atoi(pom_FONT_SIZE_PT);
			if (_global_font_size_pt == FONT_SIZE_UNDEF) {
				_global_font_size_pt = FONT_SIZE_PT_DEFAULT;
				_main_LOG_to_Export("\t(vzhľadom k neurčenej font size používam default)\n");
			}
			_main_LOG_to_Export("...font size pt (%s) = %d\n", pom_FONT_SIZE_PT, _global_font_size_pt);

			// reading of style margin
			_main_LOG_to_Export("zisťujem style margin...\n");
			_global_style_margin = atoi(pom_STYLE_MARGIN);
			if (_global_style_margin > MAX_STYLE_MARGIN) {
				_global_style_margin = MAX_STYLE_MARGIN;
				_main_LOG_to_Export("\t(more than max... style margin set to %d)\n", _global_style_margin);
			}
			if (_global_style_margin < MIN_STYLE_MARGIN) {
				_global_style_margin = MIN_STYLE_MARGIN;
				_main_LOG_to_Export("\t(less than min... style margin set to %d)\n", _global_style_margin);
			}
			_main_LOG_to_Export("...style margin (%s) = %d (interpreted in HTML/CSS as px)\n", pom_STYLE_MARGIN, _global_style_margin);

			// reading of line height
			_main_LOG_to_Export("zisťujem line height...\n");
			_global_line_height_perc = atoi(pom_LINE_HEIGHT_PERC);
			if (_global_line_height_perc > MAX_LINE_HEIGHT_PERC) {
				_global_line_height_perc = MAX_LINE_HEIGHT_PERC;
				_main_LOG_to_Export("\t(more than max... line height set to %d)\n", _global_line_height_perc);
			}
			if (_global_line_height_perc < MIN_LINE_HEIGHT_PERC) {
				_global_line_height_perc = MIN_LINE_HEIGHT_PERC;
				_main_LOG_to_Export("\t(less than min... line height set to %d)\n", _global_line_height_perc);
			}
			_main_LOG_to_Export("...line height (%s) = %d (interpreted in HTML/CSS as percent)\n", pom_LINE_HEIGHT_PERC, _global_line_height_perc);

			// načítanie css
			_main_LOG_to_Export("zisťujem css...\n");
			_global_css = atocss(pom_CSS);
			if (_global_css == CSS_UNDEF) {
				// default CSS pre daný jazyk
				_global_css = default_css_jazyk[_global_jazyk];
				if (_global_css == CSS_UNDEF) {
					_global_css = CSS_breviar_sk;
					_main_LOG_to_Export("\t(vzhľadom k neurčenému CSS používam default)\n");
				}
				else {
					_main_LOG_to_Export("\t(vzhľadom k neurčenému CSS používam default pre daný jazyk)\n");
				}
			}
			_main_LOG_to_Export("...css (%s) = %d, teda %s (%s)\n", pom_CSS, _global_css, nazov_css[_global_css], skratka_css[_global_css]);

			Log("file_export == `%s'...\n", file_export);
			if (equals(file_export, STR_EMPTY) || equals(file_export, "+")) {
				// "+" -- error, chce pridavat do nicoho
				Log("continuing to export in FILE_EXPORT (`%s')...\n", FILE_EXPORT);
			}
			else {
				// rozparsovanie parametra modlitba
				Log("volanie atomodlitba() z main()... [1]\n");
				_global_modlitba = atomodlitba(pom_MODLITBA);
				if (_global_opt_append == YES) {
					// pridame na koniec nazvu suboru "+" aby to vedel initExport()
					strcat(file_export, "+");
					Log("budem appendovat (_global_opt_append == YES)...\n");
				}

				if (initExport(file_export) == SUCCESS) {
					Log("initExport(`%s'): success\n", file_export);
					_main_LOG_to_Export("_global_jazyk == %s\n", nazov_jazyka(_global_jazyk));
				}
				else {
					Log("initExport(`%s'): failure, \n", file_export);
					Log("continuing to export into DEFAULT_FILE_EXPORT (`%s')\n", DEFAULT_FILE_EXPORT);
					initExport(DEFAULT_FILE_EXPORT);
					_main_LOG_to_Export("_global_jazyk == %s\n", nazov_jazyka(_global_jazyk));
				}
				_main_LOG_to_Export("volám hlavicka(); ... [case SCRIPT_PARAM_FROM_ARGV]\n");
				// hlavicka((char *)html_title[_global_jazyk]);
			}
		}
		_main_LOG("spat po skonceni getArgv(); exporting to file `%s'...\n", FILE_EXPORT);

		if (query_type == PRM_SIMULACIA_QS) {
			Log("jumping to _main_SIMULACIA_QS (query_string == %s)...\n", query_string);
			goto _main_SIMULACIA_QS;
		}

		break;
	}// SCRIPT_PARAM_FROM_ARGV
	case SCRIPT_PARAM_FROM_QS: {

		_main_LOG_to_Export("params == SCRIPT_PARAM_FROM_QS\n");
		// nasledujuca pasaz je tu preto, ze mozno bolo pouzite kombinovane aj query string, aj formular (teda treba citat aj systemove premenne WWW_...)

	_main_SIMULACIA_QS:
		_main_LOG_to_Export("---getting query type from query string (query_string == %s):\n", query_string);
		query_type = getQueryTypeFrom_QS(query_string);
		_main_LOG_to_Export("---getting query type from query string: finished.\n");

		_main_LOG_to_Export("---parsing query string:\n");
		ret_pom = parseQueryString();
		_main_LOG_to_Export("---parsing query string: finished.\n");

		_main_LOG_to_Export("---query_type == %d\n", query_type);

		_main_LOG_to_Export("---scanning for system variables WWW_...: started...\n");

		// historical note: to enable `mixed' queries (both GET & POST => both inputs from query string and form (system variables WWW_...), first read WWW_... variables and then parse query string

		// POST queries are handled above using 'uncgi'
		_main_LOG_to_Export("spustam setForm();\n");
		ret = setForm();
		_main_LOG_to_Export("spat po skonceni setForm()\n");

		// query_type = getQueryTypeFrom_WWW();
		// zistili sme, aky je typ dotazu podla formulara
		if ((ret == SUCCESS) && (query_type != PRM_NONE) && (query_type != PRM_UNKNOWN)) {
			// znamena to teda, ze existuje systemova premenna, oznacujuca typ dotazu ==> treba nacitat z formulara resp. systemovych premennych WWW_...
			_main_LOG_to_Export("spustam getForm();\n");
			ret = getForm();
			_main_LOG_to_Export("params from system variables WWW_...:\n");
			_main_LOG_to_Export_PARAMS;
			_main_LOG_to_Export("spat po skonceni getForm()\n");
			_main_LOG_to_Export("2006-12-14: pom_MODLITBA == `%s'\n", pom_MODLITBA);
		}
		_main_LOG_to_Export("---scanning for system variables WWW_...:finished.\n");

		// Default jazyk chceme nastavit az po volani getForm, WWW_j sa pouziva na prepinanie jazyka v Androide.
		if (equalsi(pom_JAZYK, STR_EMPTY)) {
			mystrcpy(pom_JAZYK, nazov_jazyka(JAZYK_SK), SMALL);
			Log("default jazyk (%s).\n", pom_JAZYK);
		}

		break;
	}// SCRIPT_PARAM_FROM_QS
	} // switch(params)

	_main_LOG_to_Export("query_type == ");
	switch (query_type) {
	case PRM_UNKNOWN:		_main_LOG_to_Export("PRM_UNKNOWN\n"); break;
	case PRM_TABULKA:		_main_LOG_to_Export("PRM_TABULKA\n"); break;
	case PRM_TXT:			_main_LOG_to_Export("PRM_TXT\n"); break;
	case PRM_XML:			_main_LOG_to_Export("PRM_XML\n"); break;
	case PRM_STATIC_TEXT:	_main_LOG_to_Export("PRM_STATIC_TEXT\n"); break;
	case PRM_NONE:			_main_LOG_to_Export("PRM_NONE\n"); break;
	case PRM_DATUM:			_main_LOG_to_Export("PRM_DATUM\n"); break;
	case PRM_DETAILY:		_main_LOG_to_Export("PRM_DETAILY\n"); break;
	case PRM_CEZ_ROK:		_main_LOG_to_Export("PRM_CEZ_ROK\n"); break;
	case PRM_LIT_OBD:		_main_LOG_to_Export("PRM_LIT_OBD\n"); break;
	case PRM_ANALYZA_ROKU:	_main_LOG_to_Export("PRM_ANALYZA_ROKU\n"); break;
	case PRM_SVIATOK:		_main_LOG_to_Export("PRM_SVIATOK\n"); break;
	case PRM_MESIAC_ROKA:	_main_LOG_to_Export("PRM_MESIAC_ROKA\n"); break;
	case PRM_DNES:			_main_LOG_to_Export("PRM_DNES\n"); break;
	case PRM_BATCH_MODE:	_main_LOG_to_Export("PRM_BATCH_MODE\n"); break;
	default:				_main_LOG_to_Export("(sem by sa to nemalo dostať)\n"); break;
	}

	_main_LOG_to_Export("_main_LOG_to_Export_PARAMS...\n");
	_main_LOG_to_Export_PARAMS;

	if (query_type == PRM_MESIAC_ROKA) {
		mystrcpy(pom_DEN, STR_VSETKY_DNI, SMALL);
		query_type = PRM_DATUM;
	}

	// parsovanie jazyka kvôli jazykovým mutáciám 
	_main_LOG_to_Export("zisťujem jazyk (pom_JAZYK == %s)...\n", pom_JAZYK);
	_global_jazyk = atojazyk(pom_JAZYK);
	if (_global_jazyk == JAZYK_UNDEF) {
		_global_jazyk = JAZYK_SK;
		_main_LOG_to_Export("\t(vzhľadom k neurčenému jazyku používam default)\n");
	}
	_main_LOG_to_Export("...jazyk (%s) = %d, teda %s (%s)\n", pom_JAZYK, _global_jazyk, nazov_jazyka(_global_jazyk), skratka_jazyka[_global_jazyk]);

	_global_ritus = ritus_jazyka[_global_jazyk];

	_main_LOG_to_Export("spúšťam setConfigDefaults()...\n");
	setConfigDefaults(_global_jazyk);

	Log("volám _rozparsuj_parametre_OPT()  | breviar_main()...\n");
	_rozparsuj_parametre_OPT();

	// parsovanie jazyka kvôli jazykovým mutáciám -- kalendár, napr. rehoľný (dané aj vyššie, ako jazyk)
	_main_LOG_to_Export("zisťujem kalendár (pom_KALENDAR == %s)...\n", pom_KALENDAR);
	_global_kalendar = atokalendar(pom_KALENDAR);
	if (_global_kalendar == KALENDAR_NEURCENY) {
		_global_kalendar = KALENDAR_VSEOBECNY;
		_main_LOG_to_Export("\t(vzhľadom k neurčenému kalendáru používam default -- všeobecný kalendár)\n");
	}
	_main_LOG_to_Export("...kalendár (%s) = %d, teda %s (%s)\n", pom_KALENDAR, _global_kalendar, nazov_kalendara_short[_global_kalendar], skratka_kalendara[_global_kalendar]);

	normalize_calendar_for_language();

	// načítanie názvu fontu kvôli rôznym fontom
	_main_LOG_to_Export("zisťujem font...\n");
	_global_font = atofont(pom_FONT);
	_main_LOG_to_Export("...font (%s) = %d, teda %s\n", pom_FONT, _global_font, nazov_fontu[_global_font]);
	// for FONT_CUSTOM, we still use pom_FONT as global variable unless empty

	// načítanie veľkosti fontu
	_main_LOG_to_Export("zisťujem font size...\n");
	_global_font_size = atofontsize(pom_FONT_SIZE);
	if (_global_font_size == FONT_SIZE_UNDEF) {
		_global_font_size = FONT_SIZE_CSS;
		_main_LOG_to_Export("\t(vzhľadom k neurčenej font size používam default -- brať font size z CSS)\n");
	}
	_main_LOG_to_Export("...font size (%s) = %d, teda %s\n", pom_FONT_SIZE, _global_font_size, nazov_font_size(_global_font_size));

	// reading of font size in pt (override)
	_main_LOG_to_Export("zisťujem font size pt...\n");
	_global_font_size_pt = atoi(pom_FONT_SIZE_PT);
	if (_global_font_size_pt == FONT_SIZE_UNDEF) {
		_global_font_size_pt = FONT_SIZE_PT_DEFAULT;
		_main_LOG_to_Export("\t(vzhľadom k neurčenej font size pt používam default)\n");
	}
	_main_LOG_to_Export("...font size pt (%s) = %d\n", pom_FONT_SIZE_PT, _global_font_size_pt);

	// reading of style margin
	_main_LOG_to_Export("zisťujem style margin...\n");
	_global_style_margin = atoi(pom_STYLE_MARGIN);
	if (_global_style_margin > MAX_STYLE_MARGIN) {
		_global_style_margin = MAX_STYLE_MARGIN;
		_main_LOG_to_Export("\t(more than max... style margin set to %d)\n", _global_style_margin);
	}
	if (_global_style_margin < MIN_STYLE_MARGIN) {
		_global_style_margin = MIN_STYLE_MARGIN;
		_main_LOG_to_Export("\t(less than min... style margin set to %d)\n", _global_style_margin);
	}
	_main_LOG_to_Export("...style margin (%s) = %d (interpreted in HTML/CSS as px)\n", pom_STYLE_MARGIN, _global_style_margin);

	// reading of line height
	_main_LOG_to_Export("zisťujem line height...\n");
	_global_line_height_perc = atoi(pom_LINE_HEIGHT_PERC);
	if (_global_line_height_perc > MAX_LINE_HEIGHT_PERC) {
		_global_line_height_perc = MAX_LINE_HEIGHT_PERC;
		_main_LOG_to_Export("\t(more than max... line height set to %d)\n", _global_line_height_perc);
	}
	if (_global_line_height_perc < MIN_LINE_HEIGHT_PERC) {
		_global_line_height_perc = MIN_LINE_HEIGHT_PERC;
		_main_LOG_to_Export("\t(less than min... line height set to %d)\n", _global_line_height_perc);
	}
	_main_LOG_to_Export("...line height (%s) = %d (interpreted in HTML/CSS as percents)\n", pom_LINE_HEIGHT_PERC, _global_line_height_perc);

	// načítanie css kvôli rôznym css
	_main_LOG_to_Export("zisťujem css...\n");
	_global_css = atocss(pom_CSS);
	if (_global_css == CSS_UNDEF) {
		// default CSS pre daný jazyk
		_global_css = default_css_jazyk[_global_jazyk];
		if (_global_css == CSS_UNDEF) {
			_global_css = CSS_breviar_sk;
			_main_LOG_to_Export("\t(vzhľadom k neurčenému CSS používam default)\n");
		}
		else {
			_main_LOG_to_Export("\t(vzhľadom k neurčenému CSS používam default pre daný jazyk)\n");
		}
	}
	_main_LOG_to_Export("...css (%s) = %d, teda %s (%s)\n", pom_CSS, _global_css, nazov_css[_global_css], skratka_css[_global_css]);

	LOG_ciara;

	if (ret_pom != SUCCESS) {
		ALERT;
		Export("Neboli zadané vhodné parametre (1; params == %d).\n", params);
		Export(HTML_P_BEGIN"Chyba: %s\n", bad_param_str);
	}

	if (query_type != PRM_UNKNOWN) {

		if (ret == SUCCESS) {

			_main_LOG_to_Export("now allocating memory (2)...\n");
			if (_allocate_global_var() == FAILURE) {
				goto _main_end;
			}

			LOG_ciara;

			// inicializácia _global_linky
			_main_LOG_to_Export("pom_LINKY == `%s'\n", pom_LINKY);
#if defined(OS_linux) || defined(OS_Windows_Ruby)
#if defined(BEHAVIOUR_WEB)
			_global_linky = 1; // zobrazovať linky (pre batch mód: použiť URL)
#elif defined(BEHAVIOUR_CMDLINE)
			_global_linky = 0; // nezobrazovať linky (pre batch mód: použiť filenames)
#else
#error Unsupported behaviour (not defined in mysystem.h/mysysdef.h)
#endif
			_main_LOG_to_Export("/* linux resp. Windows/Ruby: teraz som nastavil _global_linky == %d */\n", _global_linky);
#elif defined(OS_Windows) || defined(OS_DOS)
			if ((pom_LINKY != NULL) && (!equals(pom_LINKY, STR_EMPTY))) {
				_global_linky = atoi(pom_LINKY);
				_main_LOG_to_Export("/* Windows resp. DOS: teraz som nastavil _global_linky == %d */\n", _global_linky);
			}
#else
#error Unsupported operating system (not defined in mysystem.h)
#endif
			// inak ostane default hodnoty nastavene na zaciatku pre kazdy operacny system zvlast

			_main_LOG_to_Export("úprava include adresára...\n");
			// dokončenie úpravy include adresára podľa jazyka

			// uprava ciest: cfg_INCLUDE_DIR_default a include_dir | tzv. miesto 2004-03-17_TUTOLA
			_main_LOG_to_Export("\tcfg_INCLUDE_DIR_default = `%s'\n\tinclude_dir = `%s'\n", cfg_INCLUDE_DIR_default, include_dir);
			if (strcmp(include_dir, STR_EMPTY) == 0) {
				_main_LOG_to_Export("\tberiem cfg_INCLUDE_DIR_default...\n");
				mystrcpy(include_dir, cfg_INCLUDE_DIR_default, MAX_STR);
			}
			else {
				_main_LOG_to_Export("\tberiem include_dir...\n");
			}

			// prvá kontrola, či include_dir končí na backslash resp. slash
			len = strlen(include_dir) - 1;
			_main_LOG_to_Export("prvá kontrola include adresára (či končí oddeľovačom `%c' [dĺžka %ld])...\n", PATH_SEPARATOR, len);
			if (include_dir[len] != (short int)PATH_SEPARATOR) {
				include_dir[len + 1] = PATH_SEPARATOR;
				len++;
				_main_LOG_to_Export("\tupravené (pridané na koniec reťazca): %s\n", include_dir);
			}
			else {
				_main_LOG_to_Export("\tok.\n");
			}

			_main_LOG_to_Export("kontrola, či include adresár končí reťazcom `%s'...\n", postfix_jazyka[_global_jazyk]);
			// treba najskôr skontrolovať, či include dir už náhodou neobsahuje aj prilepený postfix jazyka; include_dir[len] alebo include_dir[len + 1] obsahuje PATH_SEPARATOR
			// teda znaky jeden a dva pred by mali obsahovať postfix_jazyka[_global_jazyk][0] a [1] | nemožno kontrolovať fixne 2 znaky, pretože postfix_jazyka môže byť dlhší (napr. pre "czop")
			char* include_dir_pom;
			long len_postfix_jazyka = strlen(postfix_jazyka[_global_jazyk]);
			short int kontrola_prilepenia_postfix_jazyka = NIE;
			include_dir_pom = strstr(include_dir, postfix_jazyka[_global_jazyk]);
			if (include_dir_pom != NULL) {
				_main_LOG_to_Export("len_postfix_jazyka = %ld; include_dir_pom = %s\n", len_postfix_jazyka, include_dir_pom);
				if (include_dir[len] == (short int)PATH_SEPARATOR) {
					_main_LOG_to_Export("include_dir[len] == (short int)PATH_SEPARATOR\n");
					if ((short int)strlen(include_dir_pom) == len_postfix_jazyka + 1) {
						kontrola_prilepenia_postfix_jazyka = ANO;
					}
				}
				else if (include_dir[len + 1] == (short int)PATH_SEPARATOR) {
					_main_LOG_to_Export("include_dir[len + 1] == (short int)PATH_SEPARATOR\n");
					if ((short int)strlen(include_dir_pom) == len_postfix_jazyka) {
						kontrola_prilepenia_postfix_jazyka = ANO;
					}
				}
				else
					_main_LOG_to_Export("include_dir[len/len + 1] != (short int)PATH_SEPARATOR\n");
			}// if (include_dir_pom != NULL)
			else {
				_main_LOG_to_Export("include_dir_pom == NULL (teda include_dir[] neobsahuje postfix_jazyka (%s))\n", postfix_jazyka[_global_jazyk]);
			}

			if (kontrola_prilepenia_postfix_jazyka == ANO)
			{
				_main_LOG_to_Export("include adresár končí reťazcom `%s' - nie je potrebné pridávať\n", postfix_jazyka[_global_jazyk]);
			}
			else {
				_main_LOG_to_Export("include adresára NEkončí reťazcom `%s' - je potrebné pridávať (aktuálne include_dir == %s; lenght == %d; len == %ld): ", postfix_jazyka[_global_jazyk], include_dir, strlen(include_dir), len);
				// doplnenie jazyka kvôli jazykovým mutáciám
				_main_LOG_to_Export("upravujem include adresár podľa jazyka (%d - %s)...\n", _global_jazyk, nazov_jazyka(_global_jazyk));

				// dokončenie úpravy include adresára podľa jazyka
				if (strlen(postfix_jazyka[_global_jazyk]) > 0) {
					// pôvodne sme uvažovali, že include_dir bude napr. include/cz, incluce/en; teraz bude radšej include_cz, include_en t.j. nahraď backslash resp. slash znakom underscore
					include_dir[len] = UNDERSCORE;
					strcat(include_dir, postfix_jazyka[_global_jazyk]);
					_main_LOG_to_Export("\tupravené (pridané na koniec reťazca): %s\n", include_dir);
				}
			}

			// druhá kontrola, či include_dir končí na backslash resp. slash
			len = strlen(include_dir) - 1;
			_main_LOG_to_Export("druhá kontrola include adresára (či končí oddeľovačom `%c' [dĺžka %d])...\n", PATH_SEPARATOR, len);
			if (include_dir[len] != (short int)PATH_SEPARATOR) {
				include_dir[len + 1] = PATH_SEPARATOR;
				_main_LOG_to_Export("\tupravené (pridané na koniec reťazca): %s\n", include_dir);
			}
			else {
				_main_LOG_to_Export("\tok.\n");
			}

			_main_LOG_to_Export("include súbory budú z adresára include_dir = `%s'\n", include_dir);

			LOG_ciara;

			Log("_global_opt_batch_monthly == %d\n", _global_opt_batch_monthly);
			// rozparsovanie premennej pom_EXPORT_MONTHLY, nastavenej v getArgv() [pôvodne bolo až v _main_batch_mode()]
			if (_global_opt_batch_monthly == ANO) {
				// rozparsovanie premennej pom_EXPORT_MONTHLY, nastavenej v getArgv()
				Log("rozparsovanie premennej pom_EXPORT_MONTHLY, nastavenej v getArgv()\n");
				export_monthly_druh = atoi(pom_EXPORT_MONTHLY);
				if (export_monthly_druh <= 0) {
					export_monthly_druh = 0; // možno ide o znakový reťazec nekonvertovateľný na číslo; berieme to ako default správanie
				}
				Log("export_monthly_druh == %d\n", export_monthly_druh);
			}// _global_opt_batch_monthly == ANO

			_main_LOG_to_Export("_global_jazyk == %s\n", nazov_jazyka(_global_jazyk));
			// rozparsovanie parametra modlitba
			Log("volanie atomodlitba() z main()... [2]\n");
			_global_modlitba = atomodlitba(pom_MODLITBA);

			// rozparsovanie parametrov opt...; v prípade nenastavenia sa nastaví hodnota GLOBAL_OPTION_NULL
			Log("volám _rozparsuj_parametre_OPT z main() | breviar_main()...\n");
			_rozparsuj_parametre_OPT();
			Log("_rozparsuj_parametre_OPT z main() | breviar_main(): hotovo.\n");

			// setting global variable used for CZ hymns
			if (je_CZ_hymny_k_volnemu_vyberu) {
				sprintf(_special_anchor_prefix, "%s", CZ_HYMNUS_PREFIX);
				sprintf(_special_anchor_postfix, "%s", CZ_HYMNUS_POSTFIX);
			}
			else {
				mystrcpy(_special_anchor_prefix, STR_EMPTY, SMALL);
				mystrcpy(_special_anchor_postfix, STR_EMPTY, SMALL);
			}
			Log("_special_anchor_prefix == %s\n", _special_anchor_prefix);
			Log("_special_anchor_postfix == %s\n", _special_anchor_postfix);

			// setting gloval variable used for CZ alternative 2nd readings
			if (je_alternativne_2citanie) {
				sprintf(_special_anchor_prefix2, "%s", ALT_TEXT_PREFIX);
			}
			else {
				mystrcpy(_special_anchor_prefix2, STR_EMPTY, SMALL);
			}
			Log("_special_anchor_prefix2 == %s\n", _special_anchor_prefix2);

			Log("export_monthly_druh == %d\n", export_monthly_druh);

			// rozparsovanie parametrov kvôli hlavičke
			_main_LOG_to_Export("volám _rozparsuj_parametre_DEN_MESIAC_ROK(); ...\n");
			local_den = local_mesiac = local_rok = local_modlitba = 0;
			_rozparsuj_parametre_DEN_MESIAC_ROK(pom_DEN, pom_MESIAC, pom_ROK, pom_MODLITBA, local_den, local_mesiac, local_rok, local_modlitba);

			LOG_ciara;

			// nastavenie titulku pre hlavičku
			if (query_type != PRM_XML) {
				init_global_string_as_html_title(local_den, local_mesiac, local_rok, local_modlitba);
			}

			// export hlavičky
			_main_LOG_to_Export("[pred volaním _main_... funkcií v switch(query_type)]: ");
			if (query_type == PRM_XML) {
				_main_LOG_to_Export("volám xml_hlavicka(); ...\n");
				xml_hlavicka();
			}
			else {
				_main_LOG_to_Export("volám hlavicka(_global_string == `%s'); ...\n", _global_string);
				hlavicka(_global_string);
			}

			// main switch
			Log("export_monthly_druh == %d\n", export_monthly_druh);

			LOG_ciara;

			_main_LOG_to_Export("teraz nasleduje vykonanie jadra programu podla parametrov: switch podla query_type...\n");
			switch (query_type) {
			case PRM_DETAILY:
				// presne to iste co PRM_DATUM s jedinkym rozdielom: co sa tyka formularov, prvy (uvodny) formular pre PRM_DATUM vycisti modlitbu 
				// (premenna pom_MODLITBA, ktora sa nacita zo systemovej premennej WWW_MODLITBA) -- pretoze z inej casti fomrulara sa tam nieco dostane...
			case PRM_DATUM:
				_main_LOG_to_Export("spustam _main_rozbor_dna(d = %d, m = %d, r = %d, p = %d; stringy: pom_DEN = %s, pom_MESIAC = %s, pom_ROK = %s, pom_MODLITBA = %s, pom_DALSI_SVATY = %s);\n", local_den, local_mesiac, local_rok, local_modlitba, pom_DEN, pom_MESIAC, pom_ROK, pom_MODLITBA, pom_DALSI_SVATY);
				_main_rozbor_dna(query_type, local_den, local_mesiac, local_rok, local_modlitba, pom_DALSI_SVATY);
				_main_LOG_to_Export("po skonceni _main_rozbor_dna();\n");
				break;
			case PRM_TXT: // export do TXT pre RKC
			case PRM_XML: // XML export
				_main_LOG_to_Export("spustam _main_rozbor_dna_txt_xml(typ == %d; d = %d, m = %d, r = %d; stringy: pom_DEN = %s, pom_MESIAC = %s, pom_ROK = %s, pom_MODLITBA = %s, pom_DALSI_SVATY = %s);\n", local_den, local_mesiac, local_rok, local_modlitba, pom_DEN, pom_MESIAC, pom_ROK, pom_MODLITBA, pom_DALSI_SVATY);
				_main_rozbor_dna_txt_xml(query_type, local_den, local_mesiac, local_rok, local_modlitba, pom_DALSI_SVATY);
				_main_LOG_to_Export("po skonceni _main_rozbor_dna_txt_xml();\n");
				break;
			case PRM_STATIC_TEXT: // includovanie statického textu
				_main_LOG_to_Export("spustam _main_static_text(pom_STATIC_TEXT = %s, pom_MODL_ORDINARIUM = %s);\n", pom_STATIC_TEXT, pom_MODL_ORDINARIUM);
				_main_static_text(local_rok, local_modlitba);
				_main_LOG_to_Export("po skonceni _main_static_text();\n");
				break;
			case PRM_CEZ_ROK:
				_main_LOG_to_Export("spustam _main_zaltar(%s, %s, %s);\n", pom_DEN_V_TYZDNI, pom_TYZDEN, pom_MODLITBA);
				_main_zaltar(pom_DEN_V_TYZDNI, pom_TYZDEN, pom_MODLITBA);
				_main_LOG_to_Export("po skonceni _main_zaltar();\n");
				break;
			case PRM_LIT_OBD: // výber dňa v liturgickom období
				_main_LOG_to_Export("spustam _main_liturgicke_obdobie(%s, %s, %s, %s, %s);\n", pom_DEN_V_TYZDNI, pom_TYZDEN, pom_MODLITBA, pom_LIT_OBD, pom_LIT_ROK);
				_main_liturgicke_obdobie(pom_DEN_V_TYZDNI, pom_TYZDEN, pom_MODLITBA, pom_LIT_OBD, pom_LIT_ROK);
				_main_LOG_to_Export("po skonceni _main_liturgicke_obdobie();\n");
				break;
			case PRM_SVIATOK:
				_main_LOG_to_Export("spustam sviatok(%s);\n", pom_SVIATOK);
				_main_sviatok(pom_SVIATOK);
				_main_LOG_to_Export("po skonceni sviatok();\n");
				break;
			case PRM_ANALYZA_ROKU:
				_main_LOG_to_Export("spustam analyza_roku(%s);\n", pom_ANALYZA_ROKU);
				_main_analyza_roku(pom_ANALYZA_ROKU);
				_main_LOG_to_Export("po skonceni analyza_roku();\n");
				break;
			case PRM_DNES:
				_main_LOG_to_Export("spustam _main_dnes(%s, %s);\n", pom_MODLITBA, pom_DALSI_SVATY);
				_main_dnes(pom_MODLITBA, pom_DALSI_SVATY);
				_main_LOG_to_Export("po skonceni _main_dnes();\n");
				break;
			case PRM_TABULKA:
				_main_LOG_to_Export("spustam _main_tabulka();\n");
				_main_tabulka(pom_ROK_FROM, pom_ROK_TO, pom_LINKY);
				_main_LOG_to_Export("po skonceni _main_tabulka();\n");
				break;
			case PRM_BATCH_MODE:
				_main_LOG_to_Export("spustam _main_batch_mode();\n");
				Export("<h2>Batch mode (dávkové použitie)</h2>\n");
				// vyuzivam parametre, ktore boli nastavene
				_main_batch_mode(// vyuzite parametre sa sice volaju haluzne, ale sluzia pre den from (prve tri), den to (dalsie tri), este jedno mam reserved; 2003-07-04
					pom_DEN, pom_MESIAC, pom_ROK,
					pom_ROK_FROM, pom_ROK_TO, pom_MODLITBA,
					pom_DALSI_SVATY, pom_LINKY);
				_main_LOG_to_Export("po skonceni _main_batch_mode();\n");

				Export(HTML_P_BEGIN"Výsledný batch skript (dávkový súbor) sa nachádza v súbore " HTML_A_HREF_BEGIN "\"%s\">%s" HTML_A_END "." HTML_LINE_BREAK, name_batch_file, name_batch_file);
				Export("Po spustení tento skript vygeneruje modlitby pre dané obdobie \n");
				Export("do súborov <span " HTML_CLASS_TT ">yyyy-mm-dd_xp.htm" HTML_SPAN_END ", kde význam \n");
				Export("jednotlivých častí mena súboru je nasledovný:\n");
				Export("<ul " HTML_CLASS_LEVEL1 ">\n");
				Export("<li><" HTML_SPAN_PARAMETER ">yyyy" HTML_SPAN_END " | rok</li>\n");
				Export("<li><" HTML_SPAN_PARAMETER ">mm" HTML_SPAN_END " | mesiac (napr. <" HTML_SPAN_VALUE ">05" HTML_SPAN_END " pre máj)</li>\n");
				Export("<li><" HTML_SPAN_PARAMETER ">dd" HTML_SPAN_END " | deň (napr. <" HTML_SPAN_VALUE ">07" HTML_SPAN_END ")</li>\n");
				Export("<li><" HTML_SPAN_PARAMETER ">x" HTML_SPAN_END " | poradie svätého (<" HTML_SPAN_VALUE ">0" HTML_SPAN_END " až <" HTML_SPAN_VALUE ">%d" HTML_SPAN_END ")</li>\n", PORADIE_PM_SOBOTA);
				Export("<li><" HTML_SPAN_PARAMETER ">p" HTML_SPAN_END " | modlitba (<" HTML_SPAN_VALUE ">r" HTML_SPAN_END " = ranné chvály, <" HTML_SPAN_VALUE ">v" HTML_SPAN_END " = vešpery)</li>\n");
				Export("</ul>\n");
				Export(HTML_P_BEGIN"V prípade, že je použitý parameter <" HTML_SPAN_PARAMETER ">a" HTML_SPAN_END " (append), \n");
				Export("bude vytvorený iba jeden súbor s nasledovným menom:\n");
				Export("<span " HTML_CLASS_TT ">yyyy-mm-dd_YYYY-MM-DD.htm" HTML_SPAN_END ", kde význam \n");
				Export("jednotlivých častí mena súboru je nasledovný:\n");
				Export("<ul " HTML_CLASS_LEVEL1 ">\n");
				Export("<li><" HTML_SPAN_PARAMETER ">yyyy" HTML_SPAN_END " | rok počiatočného dátumu</li>\n");
				Export("<li><" HTML_SPAN_PARAMETER ">mm" HTML_SPAN_END " | mesiac počiatočného dátumu</li>\n");
				Export("<li><" HTML_SPAN_PARAMETER ">dd" HTML_SPAN_END " | deň počiatočného dátumu</li>\n");
				Export("<li><" HTML_SPAN_PARAMETER ">YYYY" HTML_SPAN_END " | rok koncového dátumu</li>\n");
				Export("<li><" HTML_SPAN_PARAMETER ">MM" HTML_SPAN_END " | mesiac koncového dátumu</li>\n");
				Export("<li><" HTML_SPAN_PARAMETER ">DD" HTML_SPAN_END " | deň koncového dátumu</li>\n");
				Export("</ul>\n");
				break;
			default:
				ALERT;
				Export("Interná chyba programu.\n");
				Export(HTML_LINE_BREAK"(switch(query_type); case == default)\n");
				break;
			} // switch(query_type)

			_main_LOG_to_Export("volám patka(); ... [po volaní _main_... funkcií v switch(query_type)...]\n");
			if (query_type == PRM_XML) {
				xml_patka();
			}

			else {
				patka(); // doplnené (ešte pred dealokovanie premenných)
			}

#ifndef MODEL_linux_citania
			_deallocate_global_var();
#endif

		}// if (ret == SUCCESS)
		else if (ret == FAILURE) {
			// uz sa vyriesilo vyssie, dufam :-)
			_main_LOG_to_Export("ret == FAILURE\n");
		}
		else if (ret == NO_RESULT) {
			// vtedy, ked
			// - case SCRIPT_PARAM_FROM_FORM
			// - query_type == PRM_NONE
			// - historicka poznamka: povodne spustilo sa prazdny_formular();
			// - v skutocnosti _main_prazdny_formular();
			_main_LOG_to_Export("ret == NO_RESULT\n");
		}
	}// if (query_type != PRM_UNKNOWN)
	else {
		if (ret_pom != SUCCESS) {
			ALERT;
			Export("Neboli zadané vhodné parametre (2; params == %d).\n", params);
			Export(HTML_P_BEGIN"Chyba: %s\n", bad_param_str);
		}
		// else: netreba vypisovať, lebo sa vypísalo už vyššie
	}

	_main_LOG_to_Export("Deallocating memory...\n");
	_main_LOG_to_Export("query_string\n"); free(query_string);
	_main_LOG_to_Export("_global_buf\n"); free(_global_buf);
	_main_LOG_to_Export("_global_buf2\n"); free(_global_buf2);
	_main_LOG_to_Export("...done.\n");

_main_end:

	_main_LOG_to_Export("volám patka(); ... [_main_end:...]\n");
	if (query_type == PRM_XML) {
		xml_patka();
	}
	else {
		patka();
	}

	if (closeExport() == EOF) {
		Log("closeExport(): error closing file (return == EOF)\n");
	}
	else {
		Log("closeExport(): success.\n");
	}
	closeLog();

	return 0;
}// breviar_main()

#ifndef SKIP_MAIN
int main(int argc, const char** argv) {
	int ret = breviar_main(argc, argv);

#ifdef EXPORT_TO_STRING
	char* result = getExportedString();
	int resultLength = strlen(result);
	fwrite(result, resultLength, 1, stdout);
#endif

	return ret;
}
#endif

#endif // __BREVIAR_CPP_

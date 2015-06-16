/*********************************************************/
/*                                                       */
/* mydefs.h                                              */
/* (c)1999-2015 | Juraj Vidéky | videky@breviar.sk       */
/*                                                       */
/* description | core basic define's                     */
/*                                                       */
/*********************************************************/

#include "vstudio.h"

#ifndef __MYDEFS_H_
#define __MYDEFS_H_

#include "mysystem.h"
#include "mysysdef.h"
#include "myconf.h"

#if defined(OS_linux)
#elif defined(OS_Windows)
#elif defined(OS_Windows_Ruby)
#else
	#error Unsupported operating system (not defined in mysystem.h)
#endif

#include <stdio.h>

#define Q_UNUSED(arg) (void)arg;

#define SMALL 160
#define VERY_SMALL 16

// navratova hodnota funkcii
#define NO_RESULT 2
#define FAILURE 1
#define SUCCESS 0

// true -- false
#define TRUE  1
#define FALSE 0
#define ANO   1
#define NIE   0
#define CIASTOCNE 2

#define MAX_GLOBAL_STR		2048 // _global_string; 31/03/2000A.D.; 2010-12-07: rozšírené; 2011-01-31: rozšírené kvôli text_JAN_31_SDB[]; 2011-02-02: rozšírené kvôli text_FEB_04_SJ[];
#define MAX_GLOBAL_STR2		200 // _global_string2, pridané 2006-08-19
#define MAX_GLOBAL_STR_FARBA 3500 // _global_string_farba, pridané 2006-08-19; 2011-03-24: rozšírené kvôli dvojkombináciám
#define MAX_QUERY_STR		2000 // query_string
#define MAX_POM_QUERY_TYPE	2000 // pom_QUERY_TYPE
#define MAX_GLOBAL_LINK		2000 // maximalna dlzka retazca _global_link
#define MAX_VARIABLES		600 // maximalny pocet syst. premennych WWW_..., zvyseny 2003-08-07 a opätovne 2006-08-01 a opäť 2011-01-26 a zas 2011-04-11 a 2011-04-12 (na 50)
#define MAX_GLOBAL_BUFFER	4000 // _global_buf, pridané 2005-08-01

#define MAX_POCET_SVATY 5
#define PORADIE_PM_SOBOTA  (MAX_POCET_SVATY + 1)

#define SCRIPT_NAME          "l.cgi"
#define SCRIPT_PATH(a)       "cgi-bin/"a

#if defined(USE_UNCGI)
#define UNCGI_PATH(a)        SCRIPT_PATH("uncgi.cgi/")a
#else
#define UNCGI_PATH(a)        SCRIPT_PATH(a)
#endif

#define UNCGI_SCRIPT_NAME    UNCGI_PATH(SCRIPT_NAME)
#define PATH_CGI(a) "cgi-bin/"a

extern char script_name[MAX_STR]; // = cfg_HTTP_ADDRESS_default + SCRIPT_PATH(SCRIPT_NAME)
extern char uncgi_name[MAX_STR];  // = cfg_HTTP_ADDRESS_default + UNCGI_SCRIPT_NAME
void updateScriptName(void);
void updateUnCGIName(void);

#define DOCS_FOLDER "docs"

#define MESSAGE_FOLDER "msg"
#define FILE_PRESTUPNY_ROK		MESSAGE_FOLDER""STR_PATH_SEPARATOR_HTML"prestupn.htm"
#define FILE_JULIANSKY_DATUM	MESSAGE_FOLDER""STR_PATH_SEPARATOR_HTML"juldat.htm"
#define FILE_NEDELNE_PISMENO	MESSAGE_FOLDER""STR_PATH_SEPARATOR_HTML"nedpism.htm"
#define FILE_LITURGICKY_ROK	    MESSAGE_FOLDER""STR_PATH_SEPARATOR_HTML"lr-pism.htm"
#define FILE_NAME_POKEC         MESSAGE_FOLDER""STR_PATH_SEPARATOR_HTML"xxx"
#define FILE_NAME_CHYBA         MESSAGE_FOLDER""STR_PATH_SEPARATOR_HTML"chyba.htm"

extern short int query_type; // contains constants PRM_...

// meno skriptu nasleduje zoznam parametrov, alebo sa precitaju z form
#define 	SCRIPT_PARAM_FROM_FORM     200 // z formulara
#define 	SCRIPT_PARAM_FROM_QS	   201 // z query string (sys variable)
#define 	SCRIPT_PARAM_FROM_ARGV	   202 // z argumentov

// nasleduju typy dotazov
#define PRM_UNKNOWN		 190
#define PRM_NONE		 191

#define PRM_SIMULACIA_QS 12
#ifdef LONG_PARAM_NAMES
	#define STR_PRM_SIMULACIA_QS "PRM_SIMULACIA_QS"
#else
	#define STR_PRM_SIMULACIA_QS "psqs"
#endif

#define PRM_TABULKA 13
#ifdef LONG_PARAM_NAMES
	#define STR_PRM_TABULKA "PRM_TABULKA"
#else
	#define STR_PRM_TABULKA "ptab"
#endif

#define PRM_DATUM   	0 // dotaz na konkretny datum
#ifdef LONG_PARAM_NAMES
	#define STR_PRM_DATUM "PRM_DATUM"
#else
	#define STR_PRM_DATUM "pdt"
#endif

#define PRM_CEZ_ROK 	1    // dotaz na napr. piatok v tretom tyzdni
#ifdef LONG_PARAM_NAMES
	#define STR_PRM_CEZ_ROK "PRM_CEZ_ROK"
#else
	#define STR_PRM_CEZ_ROK "pcr"
#endif

#define PRM_SVIATOK 	2    // dotaz na konkretny sviatok
#ifdef LONG_PARAM_NAMES
	#define STR_PRM_SVIATOK "PRM_SVIATOK"
#else
	#define STR_PRM_SVIATOK "psv"
#endif

#define PRM_ANALYZA_ROKU	3   // dotaz na sviatky v roku
#ifdef LONG_PARAM_NAMES
	#define STR_PRM_ANALYZA_ROKU "PRM_ANALYZA_ROKU"
#else
	#define STR_PRM_ANALYZA_ROKU "par"
#endif

#define PRM_DNES		4 // to, co bolo kedysi bez parametra - info o dnesnom dni
#ifdef LONG_PARAM_NAMES
	#define STR_PRM_DNES "PRM_DNES"
#else
	#define STR_PRM_DNES "pdnes"
#endif

#define PRM_LIT_OBD 	5    // podľa pôvodného PRM_CEZ_ROK
#ifdef LONG_PARAM_NAMES
	#define STR_PRM_CEZ_ROK "PRM_LIT_OBD"
#else
	#define STR_PRM_LIT_OBD "plo"
#endif

#define PRM_MESIAC_ROKA 17
#ifdef LONG_PARAM_NAMES
	#define STR_PRM_MESIAC_ROKA "PRM_MESIAC_ROKA"
#else
	#define STR_PRM_MESIAC_ROKA "pmr"
#endif

#define PRM_BATCH_MODE 21
#ifdef LONG_PARAM_NAMES
	#define STR_PRM_BATCH_MODE "PRM_BATCH_MODE"
#else
	#define STR_PRM_BATCH_MODE "pbm"
#endif

#define PRM_TXT 	20
#ifdef LONG_PARAM_NAMES
	#define STR_PRM_TXT "PRM_TXT_EXPORT"
#else
	#define STR_PRM_TXT "ptxt"
#endif

#define PRM_XML 	19
#ifdef LONG_PARAM_NAMES
	#define STR_PRM_XML "PRM_XML_EXPORT"
#else
	#define STR_PRM_XML "pxml"
#endif

#define PRM_STATIC_TEXT 	22
#ifdef LONG_PARAM_NAMES
	#define STR_PRM_STATIC_TEXT "PRM_STATIC_TEXT"
#else
	#define STR_PRM_STATIC_TEXT "pst"
#endif

// ----------------------------------------------------
#define WWW_PREFIX "WWW_"
#define ADD_WWW_PREFIX_(a) ("WWW_"a)

// nasleduju parametre z formularov pre dotaz PRM_DATUM
#define DEN 3 // dotaz na konkretny datum
#ifdef LONG_PARAM_NAMES
	#define STR_DEN "DEN"
#else
	#define STR_DEN "d"
#endif

#define MESIAC 4 // dotaz na konkretny datum
#ifdef LONG_PARAM_NAMES
	#define STR_MESIAC "MESIAC"
#else
	#define STR_MESIAC "m"
#endif

#define ROK 5 // dotaz na konkretny datum
#ifdef LONG_PARAM_NAMES
	#define STR_ROK "ROK"
#else
	#define STR_ROK "r"
#endif

#define MODLITBA 15
#ifdef LONG_PARAM_NAMES
	#define STR_MODLITBA "MODLITBA"
#else
	#define STR_MODLITBA "p"
#endif

#define DALSI_SVATY 16
#ifdef LONG_PARAM_NAMES
	#define STR_DALSI_SVATY "DALSI_SVATY"
#else
	#define STR_DALSI_SVATY "ds"
#endif

// nasledujú parametre z formulárov pre dotaz PRM_CEZ_ROK -- používa ich aj PRM_LIT_OBD
#define DEN_V_TYZDNI 6         // dotaz na konkretny den
#ifdef LONG_PARAM_NAMES
	#define STR_DEN_V_TYZDNI "DEN_V_TYZDNI"
#else
	#define STR_DEN_V_TYZDNI "dvt"
#endif

#define TYZDEN	7               // dotaz na konkretny tyzden
#ifdef LONG_PARAM_NAMES
	#define STR_TYZDEN "TYZDEN"
#else
	#define STR_TYZDEN "t"
#endif

// nasleduju parametre z formularov pre dotaz PRM_SVIATOK
#define NAZOV_SVIATOK 8
#ifdef LONG_PARAM_NAMES
	#define STR_NAZOV_SVIATOK "SVIATOK"
#else
	#define STR_NAZOV_SVIATOK "sv"
#endif

// nasleduju parametre z formularov pre dotaz PRM_ANALYZA_ROKU
#define ANALYZA_ROKU 9
#ifdef LONG_PARAM_NAMES
	#define STR_ANALYZA_ROKU "ANALYZA_ROKU"
#else
	#define STR_ANALYZA_ROKU "ar"
#endif

// nasledujú parametre z formulárov pre dotaz PRM_LIT_OBD
#define LIT_OBD 10
#ifdef LONG_PARAM_NAMES
	#define STR_LIT_OBD "LIT_OBD"
#else
	#define STR_LIT_OBD "lo"
#endif

#define LIT_ROK 11
#ifdef LONG_PARAM_NAMES
	#define STR_LIT_ROK "LIT_ROK"
#else
	#define STR_LIT_ROK "lr"
#endif

// nasleduju parametre z formularov pre dotaz PRM_MESIAC_ROKA
#define MESIAC_ROKA 17
#ifdef LONG_PARAM_NAMES
	#define STR_MESIAC_ROKA "MESIAC_ROKA"
#else
	#define STR_MESIAC_ROKA "mr"
#endif

#define ROK_ROKA 18
#ifdef LONG_PARAM_NAMES
	#define STR_ROK_ROKA "ROK_ROKA"
#else
	#define STR_ROK_ROKA "rr"
#endif

// nasleduju parametre z formularov pre dotaz PRM_TABULKA
#define ROK_FROM 40
#ifdef LONG_PARAM_NAMES
	#define STR_ROK_FROM "ROK_FROM"
#else
	#define STR_ROK_FROM "rfrom"
#endif

#define ROK_TO 41
#ifdef LONG_PARAM_NAMES
	#define STR_ROK_TO "ROK_TO"
#else
	#define STR_ROK_TO "rto"
#endif

#define TABULKA_LINKY 42
#ifdef LONG_PARAM_NAMES
	#define STR_TABULKA_LINKY "TABULKA_LINKY"
#else
	#define STR_TABULKA_LINKY "hl" // od 'hyperlinks'
#endif

// nasleduju parametre z formularov pre dotaz PRM_STATIC_TEXT
#define STATIC_TEXT 14
#ifdef LONG_PARAM_NAMES
	#define STR_STATIC_TEXT "STATIC_TEXT"
#else
	#define STR_STATIC_TEXT "st"
#endif

#define MODL_ORDINARIUM 39
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_ORDINARIUM "MODL_ORDINARIUM"
#else
	#define STR_MODL_ORDINARIUM "pp"
#endif

//

#define PRM_DETAILY 30 // dotaz na konkretny datum, to iste ako PRM_DATUM
#ifdef LONG_PARAM_NAMES
	#define STR_PRM_DETAILY "PRM_DETAILY"
#else
	#define STR_PRM_DETAILY "pdet"
#endif

// nasleduju parametre pre modlitbu (PRM_DATUM, PRM_DETAILY)
#define MODL_OPT_0 38
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPT_0 "MODL_OPT_0"
#else
	#define STR_MODL_OPT_0 "o0"
#endif

#define MODL_OPT_1 31
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPT_1 "MODL_OPT_1"
#else
	#define STR_MODL_OPT_1 "o1"
#endif

#define MODL_OPT_2 32
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPT_2 "MODL_OPT_2"
#else
	#define STR_MODL_OPT_2 "o2"
#endif

#define MODL_OPT_3 33
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPT_3 "MODL_OPT_3"
#else
	#define STR_MODL_OPT_3 "o3"
#endif

#define MODL_OPT_4 34
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPT_4 "MODL_OPT_4"
#else
	#define STR_MODL_OPT_4 "o4"
#endif

#define MODL_OPT_5 35
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPT_5 "MODL_OPT_5"
#else
	#define STR_MODL_OPT_5 "o5"
#endif

// append pridany 2003-07-08, bude v _global_opt_append; nemal by byt pouzity na webe
#define MODL_OPT_APPEND 36
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPT_APPEND "MODL_OPT_APPEND"
#else
	#define STR_MODL_OPT_APPEND "a"
#endif

// 2006-07-11: Pridané kvôli jazykovým mutáciám
#define JAZYK 37
#ifdef LONG_PARAM_NAMES
	#define STR_JAZYK "JAZYK"
#else
	#define STR_JAZYK "j"
#endif

// --- force verzie pre option 0 až 4 ---
#define MODL_OPTF_0 50
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_0 "MODL_OPTF_0"
#else
	#define STR_MODL_OPTF_0 "of0"
#endif

#define MODL_OPTF_1 51
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1 "MODL_OPTF_1"
#else
	#define STR_MODL_OPTF_1 "of1"
#endif

#define MODL_OPTF_2 52
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2 "MODL_OPTF_2"
#else
	#define STR_MODL_OPTF_2 "of2"
#endif

#define MODL_OPTF_3 53
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_3 "MODL_OPTF_3"
#else
	#define STR_MODL_OPTF_3 "of3"
#endif

#define MODL_OPTF_4 54
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_4 "MODL_OPTF_4"
#else
	#define STR_MODL_OPTF_4 "of4"
#endif

#define MODL_OPTF_5 55
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_5 "MODL_OPTF_5"
#else
	#define STR_MODL_OPTF_5 "of5"
#endif

// pre force option 0 jednotlivé bit-komponenty (parciálne voľby)

// číslovanie (čísla) veršov
#define MODL_OPTF_0_VERSE 61
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_0_VERSE "MODL_OPTF_0_VERSE"
#else
	#define STR_MODL_OPTF_0_VERSE "of0v"
#endif

// referencie (biblické odkazy)
#define MODL_OPTF_0_REF 62
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_0_REF "MODL_OPTF_0_REF"
#else
	#define STR_MODL_OPTF_0_REF "of0r"
#endif

// liturgické čítania
#define MODL_OPTF_0_CIT 63
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_0_CIT "MODL_OPTF_0_CIT"
#else
	#define STR_MODL_OPTF_0_CIT "of0cit"
#endif

// zjavenie pána -- či sláviť 6.1. alebo v nedeľu
#define MODL_OPTF_0_ZJAV_NED 64
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_0_ZJAV_NED "MODL_OPTF_0_ZJAV_NED"
#else
	#define STR_MODL_OPTF_0_ZJAV_NED "of0zjvne"
#endif

// nanebovstúpenie pána -- či sláviť vo štvrtok (40. deň po VN) alebo v nedeľu
#define MODL_OPTF_0_NAN_NED 65
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_0_NAN_NED "MODL_OPTF_0_NANV_NED"
#else
	#define STR_MODL_OPTF_0_NAN_NED "of0nanne"
#endif

// najsv. kristovho tela a krvi -- či sláviť vo štvrtok (11. deň po ZDS) alebo v nedeľu
#define MODL_OPTF_0_TK_NED 66
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_0_TK_NED "MODL_OPTF_0_TK_NED"
#else
	#define STR_MODL_OPTF_0_TK_NED "of0tkne"
#endif

// force usage of normal font (no bold)
#define MODL_OPTF_0_FONT_NORMAL 67
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_0_FONT_NORMAL "MODL_OPTF_0_FONT_NORMAL"
#else
	#define STR_MODL_OPTF_0_FONT_NORMAL "of0fn"
#endif

// buttons order: 0 = date navigation BEFORE info on day (default for web); 1 = day details first (with prayer buttons) (default for mobile apps)
#define MODL_OPTF_0_BUTTONS_ORDER 68
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_0_BUTTONS_ORDER "MODL_OPTF_0_BUTTONS_ORDER"
#else
	#define STR_MODL_OPTF_0_BUTTONS_ORDER "of0bo"
#endif

// blind-friendly mode
#define MODL_OPTF_0_BLIND_FRIENDLY 69
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_0_BLIND_FRIENDLY "MODL_OPTF_0_BLIND_FRIENDLY"
#else
	#define STR_MODL_OPTF_0_BLIND_FRIENDLY "of0bf"
#endif

// pre force option 1 jednotlivé bit-komponenty (parciálne voľby)

// evanjeliové chválospevy (benediktus, magnifikat, nunk dimittis)
#define MODL_OPTF_1_CHV 71
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_CHV "MODL_OPTF_1_CHV"
#else
	#define STR_MODL_OPTF_1_CHV "of1c"
#endif

// sláva otcu na konci žalmov a chválospevov
#define MODL_OPTF_1_SL 72
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_SL "MODL_OPTF_1_SL"
#else
	#define STR_MODL_OPTF_1_SL "of1s"
#endif

// rubriky
#define MODL_OPTF_1_RUB 73
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_RUB "MODL_OPTF_1_RUB"
#else
	#define STR_MODL_OPTF_1_RUB "of1r"
#endif

// Otčenáš
#define MODL_OPTF_1_OT 74
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_OT "MODL_OPTF_1_OT"
#else
	#define STR_MODL_OPTF_1_OT "of1o"
#endif

// Te Deum
#define MODL_OPTF_1_TD 75
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_TD "MODL_OPTF_1_TD"
#else
	#define STR_MODL_OPTF_1_TD "of1t"
#endif

// doplnková psalmódia pre modlitbu cez deň
#define MODL_OPTF_1_MCD_DOPLNKOVA 76
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_MCD_DOPLNKOVA "MODL_OPTF_1_MCD_DOPLNKOVA"
#else
	#define STR_MODL_OPTF_1_MCD_DOPLNKOVA "of1dps"
#endif

// vigília v posvätnom čítaní
#define MODL_OPTF_1_VIGILIA 77
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_VIGILIA "MODL_OPTF_1_VIGILIA"
#else
	#define STR_MODL_OPTF_1_VIGILIA "of1v"
#endif

// popis (životopis) pre modlitbu svätého
#define MODL_OPTF_1_SKRY_POPIS 78
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_SKRY_POPIS "MODL_OPTF_1_SKRY_POPIS"
#else
	#define STR_MODL_OPTF_1_SKRY_POPIS "of1sp"
#endif

// zobraziť rubriku s textom, odkiaľ sa berú spoločné časti
#define MODL_OPTF_1_ZOBRAZ_SPOL_CAST 80
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_ZOBRAZ_SPOL_CAST "MODL_OPTF_1_ZOBRAZ_SPOL_CAST"
#else
	#define STR_MODL_OPTF_1_ZOBRAZ_SPOL_CAST "of1zspc"
#endif

// použiť (pre ktorýkoľvek deň v roku) kratšie prosby k vešperám
#define MODL_OPTF_1_VESP_KRATSIE_PROSBY 99
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_VESP_KRATSIE_PROSBY "MODL_OPTF_1_VESP_KRATSIE_PROSBY"
#else
	#define STR_MODL_OPTF_1_VESP_KRATSIE_PROSBY "of1vkp"
#endif

// psalmódia pre modlitbu cez deň z troch týždňov žaltára (aktuálny, predchádzajúci, nasledujúci)
#define MODL_OPTF_1_MCD_ZALTAR_TRI 112
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_MCD_ZALTAR_TRI "MODL_OPTF_1_MCD_ZALTAR_TRI"
#else
	#define STR_MODL_OPTF_1_MCD_ZALTAR_TRI "of1ps3"
#endif


// žalmy zo sviatku
#define MODL_OPTF_1_SPOMIENKA_SPOL_CAST 79
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_SPOMIENKA_SPOL_CAST "MODL_OPTF_1_SPOMIENKA_SPOL_CAST"
#else
	#define STR_MODL_OPTF_1_SPOMIENKA_SPOL_CAST "of1spspc"
#endif

// dlhšie zakončenie responzória
#define MODL_OPTF_1_PLNE_RESP 90
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_PLNE_RESP "MODL_OPTF_1_PLNE_RESP"
#else
	#define STR_MODL_OPTF_1_PLNE_RESP "of1pr"
#endif

// žalm 95 pre ranné chvály/vešpery namiesto ž 24, 67, 100
#define MODL_OPTF_1_ZALM95 91
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_ZALM95 "MODL_OPTF_1_ZALM95"
#else
	#define STR_MODL_OPTF_1_ZALM95 "of1z95"
#endif

// zvolanie v prosbách zobraziť (opakovať) po každej prosbe
#define MODL_OPTF_1_PROSBY_ZVOLANIE 92
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_PROSBY_ZVOLANIE "MODL_OPTF_1_PROSBY_ZVOLANIE"
#else
	#define STR_MODL_OPTF_1_PROSBY_ZVOLANIE "of1prz"
#endif

// pre force option 2 jednotlivé bit-komponenty (parciálne voľby)

// ISO formát dátumu
#define MODL_OPTF_2_ISO_DATUM 81
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_ISO_DATUM "MODL_OPTF_2_ISO_DATUM"
#else
	#define STR_MODL_OPTF_2_ISO_DATUM "of2id"
#endif

// zobrazovať button "prvé vešpery" v rámci daného slávenia (teda "ignorujúc dátum")
#define MODL_OPTF_2_PRVE_VESPERY 82
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_PRVE_VESPERY "MODL_OPTF_2_PRVE_VESPERY"
#else
	#define STR_MODL_OPTF_2_PRVE_VESPERY "of2pv"
#endif

// Serif vs. Sans Serif font family
#define MODL_OPTF_2_FONT_FAMILY 83
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_FONT_FAMILY "MODL_OPTF_2_FONT_FAMILY"
#else
	#define STR_MODL_OPTF_2_FONT_FAMILY "of2ff"
#endif

// font family chooser (drop-down list)
#define MODL_OPTF_2_FONT_NAME_CHOOSER 84
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_FONT_NAME_CHOOSER "MODL_OPTF_2_FONT_NAME_CHOOSER"
#else
	#define STR_MODL_OPTF_2_FONT_NAME_CHOOSER "of2fc"
#endif

// font size
#define MODL_OPTF_2_FONT_SIZE 85
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_FONT_SIZE "MODL_OPTF_2_FONT_SIZE"
#else
	#define STR_MODL_OPTF_2_FONT_SIZE "of2fs"
#endif

// zobrazovať navigáciu v textoch modlitieb
#define MODL_OPTF_2_NAVIGATION 86
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_NAVIGATION "MODL_OPTF_2_NAVIGATION"
#else
	#define STR_MODL_OPTF_2_NAVIGATION "of2nav"
#endif

// zobrazovať zalomenie v textoch modlitieb podľa tlačenej LH
#define MODL_OPTF_2_TEXT_WRAP 87
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_TEXT_WRAP "MODL_OPTF_2_TEXT_WRAP"
#else
	#define STR_MODL_OPTF_2_TEXT_WRAP "of2tw"
#endif

// zobraziť buttony pre modlitby v úspornej podobe (tabuľka) kvôli mobilným zariadeniam
#define MODL_OPTF_2_BUTTONY_USPORNE 88
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_BUTTONY_USPORNE "MODL_OPTF_2_BUTTONY_USPORNE"
#else
	#define STR_MODL_OPTF_2_BUTTONY_USPORNE "of2btnu"
#endif

// nocny rezim - svetly text na tmavom pozadi
#define MODL_OPTF_2_NOCNY_REZIM 89
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_NOCNY_REZIM "MODL_OPTF_2_NOCNY_REZIM"
#else
	#define STR_MODL_OPTF_2_NOCNY_REZIM "of2nr"
#endif

// rôzne možnosti zobrazovať priamo v texte modlitieb (najmä pre android)
#define MODL_OPTF_2_ROZNE_MOZNOSTI 93
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_ROZNE_MOZNOSTI "MODL_OPTF_2_ROZNE_MOZNOSTI"
#else
	#define STR_MODL_OPTF_2_ROZNE_MOZNOSTI "of2rm"
#endif

// skryť navigáciu -- BIT_OPT_2_HIDE_NAVIG_BUTTONS
#define MODL_OPTF_2_HIDE_NAVIG_BUTTONS 94
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_HIDE_NAVIG_BUTTONS "MODL_OPTF_2_HIDE_NAVIG_BUTTONS"
#else
	#define STR_MODL_OPTF_2_HIDE_NAVIG_BUTTONS "of2hnb"
#endif

// skryť kalendár -- BIT_OPT_2_HIDE_KALENDAR
#define MODL_OPTF_2_HIDE_KALENDAR 95
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_HIDE_KALENDAR "MODL_OPTF_2_HIDE_KALENDAR"
#else
	#define STR_MODL_OPTF_2_HIDE_KALENDAR "of2hk"
#endif

// skryť options, prvá časť -- BIT_OPT_2_HIDE_OPTIONS1
#define MODL_OPTF_2_HIDE_OPTIONS1 96
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_HIDE_OPTIONS1 "MODL_OPTF_2_HIDE_OPTIONS1"
#else
	#define STR_MODL_OPTF_2_HIDE_OPTIONS1 "of2ho1"
#endif

// skryť options, druhá časť -- BIT_OPT_2_HIDE_OPTIONS2
#define MODL_OPTF_2_HIDE_OPTIONS2 97
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_HIDE_OPTIONS2 "MODL_OPTF_2_HIDE_OPTIONS2"
#else
	#define STR_MODL_OPTF_2_HIDE_OPTIONS2 "of2ho2"
#endif

// zobrazovať jednu alternatívu -- BIT_OPT_2_ALTERNATIVES
#define MODL_OPTF_2_ALTERNATIVES 98
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_ALTERNATIVES "MODL_OPTF_2_ALTERNATIVES"
#else
	#define STR_MODL_OPTF_2_ALTERNATIVES "of2a"
#endif

// zobrazovať v podnadpise národný kalendár -- BIT_OPT_2_SHOW_DEFAULT_CALENDAR
#define MODL_OPTF_2_SHOW_DEFAULT_CALENDAR 114
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_SHOW_DEFAULT_CALENDAR "MODL_OPTF_2_SHOW_DEFAULT_CALENDAR"
#else
	#define STR_MODL_OPTF_2_SHOW_DEFAULT_CALENDAR "of2sdc"
#endif

// pre force option 5 jednotlivé bit-komponenty (parciálne voľby)

#define MODL_OPTF_5_HYMNUS_KOMPL 101
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_5_HYMNUS_KOMPL "MODL_OPTF_5_HYMNUS_KOMPL"
#else
	#define STR_MODL_OPTF_5_HYMNUS_KOMPL "of5hk"
#endif

#define MODL_OPTF_5_HYMNUS_PC 102
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_5_HYMNUS_PC "MODL_OPTF_5_HYMNUS_PC"
#else
	#define STR_MODL_OPTF_5_HYMNUS_PC "of5hpc"
#endif

#define MODL_OPTF_5_HYMNUS_MCD_PREDPOL 103
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_5_HYMNUS_MCD_PREDPOL "MODL_OPTF_5_HYMNUS_MCD_PREDPOL"
#else
	#define STR_MODL_OPTF_5_HYMNUS_MCD_PREDPOL "of5hpred"
#endif

#define MODL_OPTF_5_HYMNUS_MCD_NAPOL 104
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_5_HYMNUS_MCD_NAPOL "MODL_OPTF_5_HYMNUS_MCD_NAPOL"
#else
	#define STR_MODL_OPTF_5_HYMNUS_MCD_NAPOL "of5hna"
#endif

#define MODL_OPTF_5_HYMNUS_MCD_POPOL 105
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_5_HYMNUS_MCD_POPOL "MODL_OPTF_5_HYMNUS_MCD_POPOL"
#else
	#define STR_MODL_OPTF_5_HYMNUS_MCD_POPOL "of5hpo"
#endif

#define MODL_OPTF_5_DOPLNK_PSALM_122_129 106
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_5_DOPLNK_PSALM_122_129 "MODL_OPTF_5_DOPLNK_PSALM_122_129"
#else
	#define STR_MODL_OPTF_5_DOPLNK_PSALM_122_129 "of5ps29"
#endif

#define MODL_OPTF_5_DOPLNK_PSALM_127_131 107
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_5_DOPLNK_PSALM_127_131 "MODL_OPTF_5_DOPLNK_PSALM_127_131"
#else
	#define STR_MODL_OPTF_5_DOPLNK_PSALM_127_131 "of5ps71"
#endif

#define MODL_OPTF_5_DOPLNK_PSALM_126_129 108
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_5_DOPLNK_PSALM_126_129 "MODL_OPTF_5_DOPLNK_PSALM_126_129"
#else
	#define STR_MODL_OPTF_5_DOPLNK_PSALM_126_129 "of5ps69"
#endif

#define MODL_OPTF_5_HYMNUS_VN_PC 109
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_5_HYMNUS_VN_PC "MODL_OPTF_5_HYMNUS_VN_PC"
#else
	#define STR_MODL_OPTF_5_HYMNUS_VN_PC "of5vnpc"
#endif

#define MODL_OPTF_5_HYMNUS_VN_RCH 110
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_5_HYMNUS_VN_RCH "MODL_OPTF_5_HYMNUS_VN_RCH"
#else
	#define STR_MODL_OPTF_5_HYMNUS_VN_RCH "of5vnhrch"
#endif

#define MODL_OPTF_5_HYMNUS_VN_VESP 111
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_5_HYMNUS_VN_VESP "MODL_OPTF_5_HYMNUS_VN_VESP"
#else
	#define STR_MODL_OPTF_5_HYMNUS_VN_VESP "of5vnv"
#endif

#define MODL_OPTF_5_HYMNUS_1VESP 113
#ifdef LONG_PARAM_NAMES
#define STR_MODL_OPTF_5_HYMNUS_1VESP "MODL_OPTF_5_HYMNUS_1VESP"
#else
#define STR_MODL_OPTF_5_HYMNUS_1VESP "of5h1v"
#endif

#define MODL_OPTF_5_POPOL_STREDA_PSALMODIA 115
#ifdef LONG_PARAM_NAMES
#define STR_MODL_OPTF_5_POPOL_STREDA_PSALMODIA "MODL_OPTF_5_POPOL_STREDA_PSALMODIA"
#else
#define STR_MODL_OPTF_5_POPOL_STREDA_PSALMODIA "of5psps"
#endif

#define MODL_OPTF_5_CZ_HYMNY_VYBER 116
#ifdef LONG_PARAM_NAMES
#define STR_MODL_OPTF_5_CZ_HYMNY_VYBER "MODL_OPTF_5_CZ_HYMNY_VYBER"
#else
#define STR_MODL_OPTF_5_CZ_HYMNY_VYBER "of5czh"
#endif

#define CSS 40
#ifdef LONG_PARAM_NAMES
	#define STR_CSS "CSS"
#else
	#define STR_CSS "c"
#endif

#define MODL_OPT_DATE_FORMAT 41
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPT_DATE_FORMAT "MODL_OPT_DATE_FORMAT"
#else
	#define STR_MODL_OPT_DATE_FORMAT "u"
#endif

#define KALENDAR 42
#ifdef LONG_PARAM_NAMES
	#define STR_KALENDAR "KALENDAR"
#else
	#define STR_KALENDAR "k"
#endif

#define FONT_NAME 43
#ifdef LONG_PARAM_NAMES
	#define STR_FONT_NAME "FONT_NAME"
#else
	#define STR_FONT_NAME "f"
#endif

#define FONT_SIZE 44
#ifdef LONG_PARAM_NAMES
	#define STR_FONT_SIZE "FONT_SIZE"
#else
	#define STR_FONT_SIZE "s"
#endif

// margin, value to 255
#define STYLE_MARGIN 45
#ifdef LONG_PARAM_NAMES
	#define STR_STYLE_MARGIN "STYLE_MARGIN"
#else
	#define STR_STYLE_MARGIN "mm"
#endif

// query type
#define QUERY_TYPE	20
#ifdef LONG_PARAM_NAMES
	#define STR_QUERY_TYPE "QUERY_TYPE"
#else
	#define STR_QUERY_TYPE "qt"
#endif

#define ALERT	{\
	Log("ALERT\n");\
	hlavicka((char *)html_title[_global_jazyk]);\
	char pom2[MAX_STR];\
	mystrcpy(pom2, STR_EMPTY, MAX_STR);\
	char pom3[MAX_STR];\
	mystrcpy(pom3, STR_EMPTY, MAX_STR);\
	prilep_request_options(pom2, pom3);\
	_export_rozbor_dna_buttons_dni_dnes(2 /* dnes_dnes */, NIE /* som_v_tabulke */, pom2, NIE /* zobraz_odkaz_na_skrytie */);\
	}

// HTML stringy - casti stringov sustredene na tomto mieste
#define HTML_FORM_INPUT_SUBMIT   "input type=\"submit\" class=\"button\""
#define HTML_FORM_INPUT_RESET    "input type=\"reset\" class=\"reset\""
#define HTML_FORM_INPUT_RADIO    "input type=\"radio\" class=\"radio\""
#define HTML_FORM_INPUT_TEXT     "input type=\"text\" class=\"text\""
#define HTML_FORM_INPUT_TEXT_ROK "input type=\"text\" class=\"text\" size=\"4\" maxlength=\"4\" style=\"font-family:monospace\""
#define HTML_FORM_INPUT_CHECKBOX "input type=\"checkbox\" class=\"checkbox\""

// buttons (0. level: pre predošlý/nasledovný; 1. level: button "dnes"; 2. level: použité pre menej dôležité buttony)
#define HTML_FORM_INPUT_SUBMIT0  "input type=\"submit\" class=\"button0\""
#define HTML_FORM_INPUT_RESET0   "input type=\"reset\" class=\"reset0\""
#define HTML_FORM_INPUT_SUBMIT1  "input type=\"submit\" class=\"button1\""
#define HTML_FORM_INPUT_RESET1   "input type=\"reset\" class=\"reset1\""
#define HTML_FORM_INPUT_SUBMIT2  "input type=\"submit\" class=\"button2\""
#define HTML_FORM_INPUT_RESET2   "input type=\"reset\" class=\"reset2\""
#define HTML_FORM_INPUT_HIDDEN   "input type=\"hidden\""

#define HTML_FORM_METHOD_GET     "<form action=\"%s\" method=\"get\">\n"
#define HTML_FORM_METHOD_POST    "<form action=\"%s\" method=\"post\">\n"

#define HTML_LINK_RED    "a class=\"red\""
#define HTML_LINK_NORMAL "a"
#define HTML_LINK_CLASS_B "a class=\""
#define HTML_LINK_CLASS_E "\""

#define HTML_NONBREAKING_SPACE "&nbsp;"
#define HTML_SPACE " "
#define HTML_VERTICAL_BAR "|"
#define HTML_CROSS "†"
#define HTML_LINE_BREAK "<br/>"
#define HTML_CRLF_LINE_BREAK "\n<br/>"
#define HTML_SLASH "/"
#define HTML_NONBREAKING_SPACE_LOOONG "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
#define HTML_LINE_BREAK_SPACE_LOONG ((_global_jazyk != JAZYK_CZ)?(HTML_NONBREAKING_SPACE""HTML_SLASH""HTML_NONBREAKING_SPACE""HTML_LINE_BREAK""HTML_NONBREAKING_SPACE_LOOONG):(HTML_NONBREAKING_SPACE""HTML_SLASH""HTML_NONBREAKING_SPACE))

#define HTML_DIV_TABLE "div class=\"table\""
#define HTML_DIV_TABLE_CAPTION "div class=\"table-caption\""
#define HTML_DIV_TABLE_ROW "div class=\"table-row\""
#define HTML_DIV_TABLE_CELL "div class=\"table-cell\""
#define HTML_DIV_TABLE_CELL_VALIGN_TOP "div class=\"table-cell-valign-top\""

#define HTML_DIV_TABLE_LEFT "div class=\"table-left\""
#define HTML_DIV_TABLE_CELL_BORDER "div class=\"table-cell-bordered\""

#define HTML_DIV_TABLE_END HTML_DIV_END""HTML_COMMENT_BEGIN"table"HTML_COMMENT_END
#define HTML_DIV_TABLE_ROW_END HTML_DIV_END""HTML_COMMENT_BEGIN"row"HTML_COMMENT_END
#define HTML_DIV_TABLE_CELL_END HTML_DIV_END""HTML_COMMENT_BEGIN"cell"HTML_COMMENT_END

#define HTML_P_BEGIN "<p>"
#define HTML_P_END "</p>"

#define HTML_P_CENTER "<p "HTML_ALIGN_CENTER">"
#define HTML_P_CENTER_SMALL "<p "HTML_ALIGN_CENTER" "HTML_CLASS_SMALL">"

#define HTML_A_HREF_BEGIN "<a href=" // NOTE: ">" must be used manually
#define HTML_A_END "</a>"

#define HTML_DIV_BEGIN           "<div>"
#define HTML_DIV_END             "</div>"

#define HTML_DIV_RED_SMALL       "div class=\"redsmall\""
#define HTML_DIV_RED_SUBTITLE    "div class=\"redsubtitle\""

#define HTML_TABLE			HTML_DIV_TABLE // "table"
#define HTML_TABLE_CAPTION	HTML_DIV_TABLE_CAPTION // "th"
#define HTML_TABLE_ROW		HTML_DIV_TABLE_ROW // "tr"
#define HTML_TABLE_CELL		HTML_DIV_TABLE_CELL // "td"
#define HTML_TABLE_END		HTML_DIV_END""HTML_COMMENT_BEGIN"table"HTML_COMMENT_END // "</table>"
#define HTML_TABLE_CAPTION_END	HTML_DIV_END""HTML_COMMENT_BEGIN"caption"HTML_COMMENT_END // "</th>"
#define HTML_TABLE_ROW_END	HTML_DIV_END""HTML_COMMENT_BEGIN"row"HTML_COMMENT_END // "</tr>"
#define HTML_TABLE_CELL_END	HTML_DIV_END""HTML_COMMENT_BEGIN"cell"HTML_COMMENT_END // "</td>"

#define HTML_TABLE_LEFT			HTML_DIV_TABLE_LEFT // "table" left-aligned
#define HTML_TABLE_CELL_BORDER		HTML_DIV_TABLE_CELL_BORDER // "td" with borders
#define HTML_TABLE_CELL_BORDER_END	HTML_TABLE_CELL_END

#define HTML_SPAN_END            "</span>"

#define HTML_SPAN_NORMAL         "span class=\"normal\""
#define HTML_SPAN_ITALIC         "span class=\"it\""
#define HTML_SPAN_BOLD           "span class=\"bold\""
#define HTML_SPAN_BOLD_IT        "span class=\"boldit\""
#define HTML_SPAN_RED_TITLE      "span class=\"redtitle\""
#define HTML_SPAN_RED            "span class=\"red\""
#define HTML_SPAN_RED_BOLD       "span class=\"redbold\""
#define HTML_SPAN_BLUE           "span class=\"blue\""
#define HTML_SPAN_BLUE_BOLD      "span class=\"bluebold\""
#define HTML_SPAN_RED_SMALL      "span class=\"redsmall\""
#define HTML_SPAN_RED_SUBTITLE   "span class=\"redsubtitle\""
#define HTML_SPAN_SMALL          "span class=\"small\""
#define HTML_SPAN_EXPLAIN        "span class=\"explain\""
#define HTML_SPAN_PARAMETER      "span class=\"parameter\""
#define HTML_SPAN_VALUE          "span class=\"value\""
#define HTML_SPAN_SMALLCAPS      "span class=\"smallcaps\""
#define HTML_SPAN_XS_CAPS        "span class=\"xsmallcaps\""

#define HTML_CLASS_CALENDAR "class=\"calendar\""

#define HTML_CALENDAR_HEADING "span class=\"calendar heading\""
#define HTML_CALENDAR_DAYS   "span class=\"calendar day_name\""
#define HTML_CALENDAR_TODAY_SUNDAY   "span class=\"calendar today bold\""
#define HTML_CALENDAR_TODAY   "span class=\"calendar today\""

#define HTML_CLASS_NAME_CALENDAR_TODAY_SUNDAY "calendar today bold"
#define HTML_CLASS_NAME_CALENDAR_TODAY "calendar today"
#define HTML_CLASS_NAME_CALENDAR_SUNDAY "calendar day bold"
#define HTML_CLASS_NAME_CALENDAR_DAY "calendar day"

#define HTML_SPAN_TOOLTIP   "span title=\"%s\"" // obsahuje %s
#define HTML_SPAN_BOLD_TOOLTIP   "span class=\"bold\" title=\"%s\"" // obsahuje %s
#define HTML_SPAN_NORMAL_TOOLTIP   "span class=\"normal\" title=\"%s\"" // obsahuje %s

#define HTML_SUP_RED        "sup class=\"red\""

#define HTML_CLASS_BLUE     "class=\"blue\""
#define HTML_CLASS_QUIET    "class=\"quiet\""
#define HTML_CLASS_BOLD_IT  "class=\"boldit\""
#define HTML_CLASS_LEVEL1   "class=\"level1\""
#define HTML_CLASS_TT       "class=\"tt\""
#define HTML_CLASS_BUTTON   "class=\"button\""
#define HTML_CLASS_SMALL    "class=\"small\""

#define HTML_CLASS_QUIET_SMALL    "class=\"quiet small\""

#define HTML_ALIGN_CENTER   "align=\"center\""
#define HTML_ALIGN_LEFT     "align=\"left\""
#define HTML_ALIGN_RIGHT    "align=\"right\""
#define HTML_VALIGN_MIDDLE  "valign=\"middle\""
#define HTML_VALIGN_TOP     "valign=\"top\""
#define HTML_VALIGN_BASE    "valign=\"baseline\""

#define HTML_BUTTON_BEGIN	"<button type=\"button\" "HTML_CLASS_BUTTON">" // wrapping <a> element to look like button
#define HTML_BUTTON_END		"</button>"

#define HTML_AMPERSAND          "&amp;"

#define HTML_COMMENT_BEGIN		"<!--"
#define HTML_COMMENT_END		"-->"
#define HTML_FONT_SIZE_FARBA	"2"

#define HTML_LEFT_ARROW			"&laquo;"
#define HTML_RIGHT_ARROW		"&raquo;"

#define HTML_LEFT_ARROW_WIDE	"&nbsp;&laquo;&nbsp;"
#define HTML_RIGHT_ARROW_WIDE	"&nbsp;&raquo;&nbsp;"

#define HTML_LINK_CALL1         "%s?%s=%s"HTML_AMPERSAND"%s=%d"HTML_AMPERSAND"%s=%d"HTML_AMPERSAND"%s=%d%s"
#define HTML_LINK_CALL2         "%s?%s=%s"HTML_AMPERSAND"%s=%s"HTML_AMPERSAND"%s=%d"HTML_AMPERSAND"%s=%d%s"
#define HTML_LINK_CALL3         "%s?%s=%s"HTML_AMPERSAND"%s=%s%s"
#define HTML_LINK_CALL_PARAM    HTML_AMPERSAND"%s=%s"

#define HTML_LEFT_ARROW_SINGLE	"&lsaquo;"
#define HTML_RIGHT_ARROW_SINGLE	"&rsaquo;"

#define HTML_LEFT_ARROW_HUGE	"&lsaquo;&laquo;"
#define HTML_RIGHT_ARROW_HUGE	"&raquo;&rsaquo;"

// 2007-03-19: výpis "Dnes je..." sa zobrazí len pri tomto nastavení, ak je 1
#define HTML_ZOBRAZIT_DNES_JE	0

#define MODL_ZALMY_ZO_DNA 0
#define MODL_ZALMY_ZO_SV  1

#define MODL_CEZ_DEN_ZALMY_ZO_DNA         0
#define MODL_CEZ_DEN_DOPLNKOVA_PSALMODIA  1

#define	EXPORT_DATE_SIMPLE 0
#define	EXPORT_DATE_FULL   1

#define STR_SIMPLE "simple"
#define STR_FULL   "full"

// názov súboru (jeho začiatok) pre dátum
#define FILENAME_EXPORT_DATE_SIMPLE "%.2d%.2d%.2d"
#define FILENAME_EXPORT_DATE_FULL   "%.4d-%.2d-%.2d"
// názov adresára pre mesiac
#define DIRNAME_EXPORT_MONTH_SIMPLE "%.2d%.2d-%s"
#define DIRNAME_EXPORT_MONTH_FULL   "%.4d-%.2d-%s"
// názov súboru (jeho začiatok) pre mesiac
#define FILENAME_EXPORT_MONTH_SIMPLE "%.2d%.2d"
#define FILENAME_EXPORT_MONTH_FULL   "%.4d-%.2d"

#define HTML_ISO_FORMAT      "%04d-%02d-%02d"

#define TEXT_COPYRIGHT       "(c)1999-2015 Juraj Vidéky"
#define TEXT_EMAIL           "videky@breviar.sk"

// main XML element
#define XML_MAIN             "LHData"

// element XML_DAY with sub-elements
#define XML_DAY              "CalendarDay"
#define XML_CELEBRATION      "Celebration"
#define XML_CELEBRATION_ID   "Id"
#define XML_DATE_ISO         "DateISO"
#define XML_DATE_DAY         "DateDay"
#define XML_DATE_MONTH       "DateMonth"
#define XML_DATE_YEAR        "DateYear"
#define XML_DAY_OF_YEAR      "DayOfYear"
#define XML_DAY_OF_WEEK      "DayOfWeek"
#define XML_STRING_TITLE     "StringTitle"
#define XML_STRING_COMMUNIA  "StringCommunia"
#define XML_STRING_VOLUME    "StringVolume"
#define XML_LIT_YEAR_LETTER  "LiturgicalYearLetter"
#define XML_LIT_SEASON       "LiturgicalSeason"
#define XML_LIT_WEEK         "LiturgicalWeek"
#define XML_LIT_WEEK_PSALT   "LiturgicalWeekOfPsalter"
#define XML_LIT_TYPE         "LiturgicalCelebrationType"
#define XML_LIT_TYPE_LOCAL   "LiturgicalCelebrationTypeLocal"
#define XML_LIT_LEVEL        "LiturgicalCelebrationLevel"
#define XML_LIT_REQUIRED     "LiturgicalCelebrationRequired"
#define XML_LIT_COMMUNIA     "LiturgicalCelebrationCommunia"
#define XML_LIT_NAME         "LiturgicalCelebrationName"
#define XML_LIT_COLOR        "LiturgicalCelebrationColor"
#define XML_LIT_CALENDAR     "LiturgicalCalendar"
#define XML_LIT_READINGS     "LiturgicalReadingsId"

// element XML_INFO with sub-elements
#define XML_INFO             "Info"
#define XML_COPYRIGHT        "Copyright"
#define XML_ADDRESS          "Address"
#define XML_BUILD_DATE       "BuildDate"
#define XML_GENERATED        "Generated"

// element XML_OPTIONS with sub-elements
#define XML_OPTIONS          "Options"

// POCET_GLOBAL_OPT
#define XML_OPT_0_SPECIALNE                     "Opt0Special"
#define XML_OPT_1_CASTI_MODLITBY                "Opt1PrayerPortions"
#define XML_OPT_2_HTML_EXPORT                   "Opt2Export"
#define XML_OPT_3_SPOLOCNA_CAST                 "Opt3Communia"
#define XML_OPT_4_OFFLINE_EXPORT                "Opt4OfflineExport"
#define XML_OPT_5_ALTERNATIVES                  "Opt5Alternatives"

// POCET_OPT_0_SPECIALNE
#define XML_BIT_OPT_0_VERSE                     "BitOpt0VerseNumbers"
#define XML_BIT_OPT_0_REFERENCIE                "BitOpt0References"
#define XML_BIT_OPT_0_CITANIA                   "BitOpt0Readings"
#define XML_BIT_OPT_0_ZJAVENIE_PANA_NEDELA      "BitOpt0EpiphanyOnSunday"
#define XML_BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA   "BitOpt0AssumptionOnSunday"
#define XML_BIT_OPT_0_TELAKRVI_NEDELA           "BitOpt0CorpusChristiOnSunday"
#define XML_BIT_OPT_0_FONT_NORMAL               "BitOpt0ForceNormalFontWeight"
#define XML_BIT_OPT_0_BUTTONS_ORDER             "BitOpt0ButtonsOrder"
#define XML_BIT_OPT_0_BLIND_FRIENDLY            "BitOpt0BlindFriendly"

// POCET_OPT_1_CASTI_MODLITBY
#define XML_BIT_OPT_1_TEDEUM                    "BitOpt1TeDeum"
#define XML_BIT_OPT_1_RUBRIKY                   "BitOpt1Rubrics"
#define XML_BIT_OPT_1_CHVALOSPEVY               "BitOpt1Canticles"
#define XML_BIT_OPT_1_SLAVA_OTCU                "BitOpt1GloryPrayer"
#define XML_BIT_OPT_1_OTCENAS                   "BitOpt1OurFatherPrayer"
#define XML_BIT_OPT_1_MCD_DOPLNKOVA             "BitOpt1SupplPsalmodyDuringDay"
#define XML_BIT_OPT_1_PC_VIGILIA                "BitOpt1VigilAfterReadings"
#define XML_BIT_OPT_1_SPOMIENKA_SPOL_CAST       "BitOpt1MemoriesTakeFromCommunia"
#define XML_BIT_OPT_1_PLNE_RESP                 "BitOpt1FullResponses"
#define XML_BIT_OPT_1_ZALM95                    "BitOpt1InvitatoryUsePsalm95"
#define XML_BIT_OPT_1_PROSBY_ZVOLANIE           "BitOpt1Repeat"
#define XML_BIT_OPT_1_SKRY_POPIS                "BitOpt1HideDescription"
#define XML_BIT_OPT_1_ZOBRAZ_SPOL_CAST          "BitOpt1ShowCommuniaDescription"
#define XML_BIT_OPT_1_VESP_KRATSIE_PROSBY       "BitOpt1UseVespShortenPrayers"
#define XML_BIT_OPT_1_MCD_ZALTAR_TRI            "BitOpt1PsalmsDuringDayPsalt3Weeks"

// POCET_OPT_2_HTML_EXPORT
#define XML_BIT_OPT_2_ISO_DATUM                 "BitOpt2ISOFormat"
#define XML_BIT_OPT_2_BUTTON_PRVE_VESPERY       "BitOpt2FirstVespersButton"
#define XML_BIT_OPT_2_FONT_FAMILY               "BitOpt2FontFamily"
#define XML_BIT_OPT_2_FONT_NAME_CHOOSER         "BitOpt2FontNameChooser"
#define XML_BIT_OPT_2_FONT_SIZE_CHOOSER         "BitOpt2FontSizeChooser"
#define XML_BIT_OPT_2_NAVIGATION                "BitOpt2Navigation"
#define XML_BIT_OPT_2_TEXT_WRAP                 "BitOpt2TextWrap"
#define XML_BIT_OPT_2_BUTTONY_USPORNE           "BitOpt2ButtonsCondensed"
#define XML_BIT_OPT_2_NOCNY_REZIM               "BitOpt2NightMode"
#define XML_BIT_OPT_2_ROZNE_MOZNOSTI            "BitOpt2OptionsWithinPrayer"
#define XML_BIT_OPT_2_HIDE_NAVIG_BUTTONS        "BitOpt2HideNavigationButtons"
#define XML_BIT_OPT_2_HIDE_KALENDAR             "BitOpt2HideCalendar"
#define XML_BIT_OPT_2_HIDE_OPTIONS1             "BitOpt2HideOptionsPart1"
#define XML_BIT_OPT_2_HIDE_OPTIONS2             "BitOpt2HideOptionsPart2"
#define XML_BIT_OPT_2_ALTERNATIVES              "BitOpt2Alternatives"
#define XML_BIT_OPT_2_SHOW_DEFAULT_CALENDAR     "BitOpt2ShowDefaultCalendar"

// POCET_OPT_5_ALTERNATIVES
#define XML_BIT_OPT_5_HYMNUS_KOMPL              "BitOpt5HymnCompl"
#define XML_BIT_OPT_5_HYMNUS_PC                 "BitOpt5HymnRead"
#define XML_BIT_OPT_5_HYMNUS_MCD_PREDPOL        "BitOpt5Hymn9h"
#define XML_BIT_OPT_5_HYMNUS_MCD_NAPOL          "BitOpt5Hymn12h"
#define XML_BIT_OPT_5_HYMNUS_MCD_POPOL          "BitOpt5Hymn15h"
#define XML_BIT_OPT_5_DOPLNK_PSALM_122_129      "BitOpt5Psalm122or129"
#define XML_BIT_OPT_5_DOPLNK_PSALM_126_129      "BitOpt5Psalm126or129"
#define XML_BIT_OPT_5_DOPLNK_PSALM_127_131      "BitOpt5Psalm127or131"
#define XML_BIT_OPT_5_HYMNUS_VN_PC              "BitOpt5HymnTPRead"
#define XML_BIT_OPT_5_HYMNUS_VN_RCH             "BitOpt5HymnTPLaud"
#define XML_BIT_OPT_5_HYMNUS_VN_VESP            "BitOpt5HymnTPVesp"
#define XML_BIT_OPT_5_HYMNUS_1VESP              "BitOpt5Hymn1Vesp"
#define XML_BIT_OPT_5_POPOL_STREDA_PSALMODIA    "BitOpt5AshWednPsalmody"
#define XML_BIT_OPT_5_CZ_HYMNY_VYBER            "BitOpt5CZhymnsAlt"

// starting, closing element (XML, HTML)
#define ELEM_BEGIN(elem)     "<"elem">"
#define ELEM_END(elem)       "</"elem">"

#define ELEMID_BEGIN(elem)   "<"elem" Id=\"%d\">"
#define ELEMVAL_BEGIN(elem)  "<"elem" Value=\"%d\" Name=\"%s\" ForceName=\"%s\" Text=\"%s\">"
#define ELEMOPT_BEGIN(elem)  "<"elem" Id=\"%d\" ForceName=\"%s\" Text=\"%s\">" // Id napr. BIT_OPT_0_VERSE; Name napr. STR_MODL_OPTF_0_VERSE
#define ELEMOPT_SLASH_BEGIN(elem)  "<"elem" Id=\"%d\" ForceName=\"%s\" Text=\"%s/%s\">"

#endif // __MYDEFS_H_


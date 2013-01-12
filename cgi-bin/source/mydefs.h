/***************************************************************/
/*                                                             */
/* mydefs.h                                                    */
/* (c)1999-2013 | Juraj VidÈky | videky@breviar.sk             */
/*                                                             */
/* description | obsahuje zakladne define'y                    */
/* document history                                            */
/*   12/11/1999A.D. | created                                  */
/*   01/02/2000A.D. | modifikovane                             */
/*   09/02/2000A.D. | pridane PRM_DETAILY                      */
/*   06/09/2001A.D. | zmenene SCRIPT_PATH(a) UNCGI_PATH(a),    */
/*                    tento popis                              */
/*   2003-07-02a.D. | pridane HTML konstanty (casti stringov)  */
/*   2003-07-04a.D. | pridane konstanty pre batch mode         */
/*   2003-07-08a.D. | pridana konstanta MODL_OPT_APPEND        */
/*   2003-07-09a.D. | pridane #define HTML_AMPERSAND "&amp;"   */
/*   2003-07-15a.D. | zluceny s mybase.h, vycistene komentare  */
/*                  - pridane HTML_BUTTON_                     */
/*   2003-07-16a.D. | zmena WWW_ na ADD_WWW_PREFIX_            */
/*   2004-03-17a.D. | FILE_PATH sa nepouziva                   */
/*   2004-08-14a.D. | zmena definicie ADD_WWW_PREFIX_          */
/*   2005-03-28a.D. | zmena definicie UNCGI_PATH               */
/*   2005-07-27a.D. | pridane HTML_SPAN_RED_SMALL              */
/*   2006-07-11a.D. | prvÈ kroky k jazykov˝m mut·ci·m          */
/*   2006-08-18a.D. | zmena int na short int (staËÌ 32tis.)    */
/*   2008-11-29a.D. | pridanÈ rÙzne moûnosti batch exportu     */
/*   2009-08-12a.D. | pridanÈ Ôalöie moûnosti batch exportu    */
/*   2010-08-04a.D. | pridanÈ KALENDAR a STR_KALENDAR          */
/*   2011-04-13a.D. | definovanÈ HTML_FORM_INPUT_TEXT_ROK      */
/*                                                             */
/*                                                             */
/***************************************************************/

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

/***************************************************************/
/*                                                             */
/* mybase.h                                                    */
/* (c)1999-2013 | Juraj VidÈky | videky@breviar.sk             */
/*                                                             */
/* description | obsahuje zakladne vecicky                     */
/* document history                                            */
/*   29/10/1999A.D. | created                                  */
/*   06/09/2001A.D. | tento popis                              */
/*   2003-06-30a.D. | build (priliepa sa do hlavicky)          */
/*   2003-07-15a.D. | RUN_MODLITBA_CEZ_DEN definovane          */
/*   2003-07-15a.D. | vlozeny do mydefs.h                      */
/*   2003-08-13a.D. | odstranenie RUN_MODLITBA_CEZ_DEN         */
/*   2011-07-11a.D. | BUILD_DATE presunut˝ do mybuild.h        */
/*                                                             */
/***************************************************************/
#include <stdio.h>

#define BYTES 250
#define SMALL 80
#define VERY_SMALL 8

// navratova hodnota funkcii
#define NO_RESULT 2
#define FAILURE 1
#define SUCCESS 0

// true -- false
#define TRUE  1
#define FALSE 0
#define ANO   1
#define NIE   0

#define MAX_GLOBAL_STR		2048 // _global_string; 31/03/2000A.D.; 2010-12-07: rozöÌrenÈ; 2011-01-31: rozöÌrenÈ kvÙli text_JAN_31_SDB[]; 2011-02-02: rozöÌrenÈ kvÙli text_FEB_04_SJ[];
#define MAX_GLOBAL_STR2		200 // _global_string2, pridanÈ 2006-08-19
#define MAX_GLOBAL_STR_FARBA 3500 // _global_string_farba, pridanÈ 2006-08-19; 2011-03-24: rozöÌrenÈ kvÙli dvojkombin·ci·m
#define MAX_QUERY_STR		2000 // query_string
#define MAX_POM_QUERY_TYPE	2000 // pom_QUERY_TYPE
#define MAX_GLOBAL_LINK		2000 // maximalna dlzka retazca _global_link
//#define MAX_ENV	100 // maximalna dlzka environmentalnej premennej | 2006-08-01: nepouûÌva sa
#define MAX_VARIABLES		600 // maximalny pocet syst. premennych WWW_..., zvyseny 2003-08-07 a op‰tovne 2006-08-01 a op‰ù 2011-01-26 a zas 2011-04-11 a 2011-04-12 (na 50)
#define MAX_GLOBAL_BUFFER	4000 // _global_buf, pridanÈ 2005-08-01
//***************************************************************
//* EOF of former file mybase.h                                 *
//***************************************************************

// Nazvy programov, suborov, skriptov...
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

// tu kedysi bolo aj #define PATH(a) zvacsa a, ale nebolo to treba; vyhodene 2003-07-02

/* 2004-03-17
 * FILE_PATH nie je potrebne; citame to z myconf.cpp::readConfig() (config file)
extern char FILE_PATH[MAX_STR]; // inicializovane v breviar.cpp
 */

#define MESSAGE_FOLDER "msg/"
#define FILE_PRESTUPNY_ROK		MESSAGE_FOLDER"prestupn.htm"
#define FILE_JULIANSKY_DATUM	MESSAGE_FOLDER"juldat.htm"
#define FILE_NEDELNE_PISMENO	MESSAGE_FOLDER"nedpism.htm"
#define FILE_LITURGICKY_ROK	    MESSAGE_FOLDER"lr-pism.htm"
#define FILE_NAME_POKEC         MESSAGE_FOLDER"xxx"
#define FILE_NAME_CHYBA         MESSAGE_FOLDER"chyba.htm"

extern short int query_type; // premenna obsahujuca PRM_...

// meno skriptu nasleduje zoznam parametrov, alebo sa precitaju z form
#define 	SCRIPT_PARAM_FROM_FORM     200 // z formulara
#define 	SCRIPT_PARAM_FROM_QS	   201 // z query string (sys variable)
#define 	SCRIPT_PARAM_FROM_ARGV	   202 // z argumentov

// nasleduju typy dotazov
#define PRM_UNKNOWN		 100
#define PRM_NONE		 110

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

#define PRM_LIT_OBD 	5    // podæa pÙvodnÈho PRM_CEZ_ROK
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

// pridana konstanta pre batch mode; 2003-07-04
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

// nasleduju parametre z formularov pre vsetky typy dotazov,
// kedysi bolo pre kazdy STR_... definovane WWW_STR_..., teraz ADD_WWW_PREFIX_(STR_...) 
// 2004-08-14: 
// definicia ADD_WWW_PREFIX_(a) ("WWW_"##a) ktora bola OK na g++ (gcc version 2.95.4 20011002)
// sposobovala problemy na g++ (gcc version 3.3.3 20040412)
// preto zmenene na ADD_WWW_PREFIX_(a) ("WWW_"a)
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

// nasleduj˙ parametre z formul·rov pre dotaz PRM_CEZ_ROK -- pouûÌva ich aj PRM_LIT_OBD
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

// nasleduj˙ parametre z formul·rov pre dotaz PRM_LIT_OBD
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

#define PRM_DETAILY 30 // dotaz na konkretny datum, to iste ako PRM_DATUM
#ifdef LONG_PARAM_NAMES
	#define STR_PRM_DETAILY "PRM_DETAILY"
#else
	#define STR_PRM_DETAILY "pdet"
#endif

/* nasleduju parametre pre modlitbu (PRM_DATUM, PRM_DETAILY)
 * -- specialne options, ktore platia rovnako pre oboje, ale
 * de facto sa vyuzivaju len pre PRM_DETAILY 
 * 2011-01-26: doplnenÈ aj verzie "force" pre formul·r; pouûÌvaj˙ sa totiû aj na PRM_DNES hlavnom okne
 */
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

// append pridany 2003-07-08, bude v _global_opt_append; nemal by byt pouzity na webe
#define MODL_OPT_APPEND 35
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPT_APPEND "MODL_OPT_APPEND"
#else
	#define STR_MODL_OPT_APPEND "a"
#endif

// 2006-07-11: PridanÈ kvÙli jazykov˝m mut·ci·m
#define JAZYK 37
#ifdef LONG_PARAM_NAMES
	#define STR_JAZYK "JAZYK"
#else
	#define STR_JAZYK "j"
#endif

// --- force verzie pre option 0 aû 4 ---
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

// pre force option 0 jednotlivÈ bit-komponenty (parci·lne voæby)

// ËÌslovanie (ËÌsla) veröov
#define MODL_OPTF_0_VERSE 61
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_0_VERSE "MODL_OPTF_0_VERSE"
#else
	#define STR_MODL_OPTF_0_VERSE "of0v"
#endif

// referencie (biblickÈ odkazy)
#define MODL_OPTF_0_REF 62
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_0_REF "MODL_OPTF_0_REF"
#else
	#define STR_MODL_OPTF_0_REF "of0r"
#endif

// liturgickÈ ËÌtania
#define MODL_OPTF_0_CIT 63
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_0_CIT "MODL_OPTF_0_CIT"
#else
	#define STR_MODL_OPTF_0_CIT "of0cit"
#endif

// zjavenie p·na -- Ëi sl·viù 6.1. alebo v nedeæu
#define MODL_OPTF_0_ZJAV_NED 64
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_0_ZJAV_NED "MODL_OPTF_0_ZJAV_NED"
#else
	#define STR_MODL_OPTF_0_ZJAV_NED "of0zjvne"
#endif

// nanebovst˙penie p·na -- Ëi sl·viù vo ötvrtok (40. deÚ po VN) alebo v nedeæu
#define MODL_OPTF_0_NAN_NED 65
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_0_NAN_NED "MODL_OPTF_0_NANV_NED"
#else
	#define STR_MODL_OPTF_0_NAN_NED "of0nanne"
#endif

// najsv. kristovho tela a krvi -- Ëi sl·viù vo ötvrtok (11. deÚ po ZDS) alebo v nedeæu
#define MODL_OPTF_0_TK_NED 66
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_0_TK_NED "MODL_OPTF_0_TK_NED"
#else
	#define STR_MODL_OPTF_0_TK_NED "of0tkne"
#endif

// pre force option 1 jednotlivÈ bit-komponenty (parci·lne voæby)

// evanjeliovÈ chv·lospevy (benediktus, magnifikat, nunk dimittis)
#define MODL_OPTF_1_CHV 71
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_CHV "MODL_OPTF_1_CHV"
#else
	#define STR_MODL_OPTF_1_CHV "of1c"
#endif

// sl·va otcu na konci ûalmov a chv·lospevov
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

// OtËen·ö
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

// doplnkov· psalmÛdia pre modlitbu cez deÚ
#define MODL_OPTF_1_MCD_ZALMY_INE 76
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_MCD_ZALMY_INE "MODL_OPTF_1_MCD_ZALMY_INE"
#else
	#define STR_MODL_OPTF_1_MCD_ZALMY_INE "of1dps"
#endif

// vigÌlia v posv‰tnom ËÌtanÌ
#define MODL_OPTF_1_VIGILIA 77
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_VIGILIA "MODL_OPTF_1_VIGILIA"
#else
	#define STR_MODL_OPTF_1_VIGILIA "of1v"
#endif

// popis (ûivotopis) pre modlitbu sv‰tÈho
#define MODL_OPTF_1_SKRY_POPIS 78
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_SKRY_POPIS "MODL_OPTF_1_SKRY_POPIS"
#else
	#define STR_MODL_OPTF_1_SKRY_POPIS "of1sp"
#endif

// zobraziù rubriku s textom, odkiaæ sa ber˙ spoloËnÈ Ëasti
#define MODL_OPTF_1_ZOBRAZ_SPOL_CAST 80
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_ZOBRAZ_SPOL_CAST "MODL_OPTF_1_ZOBRAZ_SPOL_CAST"
#else
	#define STR_MODL_OPTF_1_ZOBRAZ_SPOL_CAST "of1zspc"
#endif

// pouûiù (pre ktor˝koævek deÚ v roku) kratöie prosby k veöper·m
#define MODL_OPTF_1_VESP_KRATSIE_PROSBY 98
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_VESP_KRATSIE_PROSBY "MODL_OPTF_1_VESP_KRATSIE_PROSBY"
#else
	#define STR_MODL_OPTF_1_VESP_KRATSIE_PROSBY "of1vkp"
#endif

// ûalmy zo sviatku
#define MODL_OPTF_1_SPOMIENKA_SPOL_CAST 79
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_SPOMIENKA_SPOL_CAST "MODL_OPTF_1_SPOMIENKA_SPOL_CAST"
#else
	#define STR_MODL_OPTF_1_SPOMIENKA_SPOL_CAST "of1spspc"
#endif

// dlhöie zakonËenie responzÛria
#define MODL_OPTF_1_PLNE_RESP 90
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_PLNE_RESP "MODL_OPTF_1_PLNE_RESP"
#else
	#define STR_MODL_OPTF_1_PLNE_RESP "of1pr"
#endif

// ûalm 95 pre rannÈ chv·ly/veöpery namiesto û 24, 67, 100
#define MODL_OPTF_1_ZALM95 91
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_ZALM95 "MODL_OPTF_1_ZALM95"
#else
	#define STR_MODL_OPTF_1_ZALM95 "of1z95"
#endif

// zvolanie v prosb·ch zobraziù (opakovaù) po kaûdej prosbe
#define MODL_OPTF_1_PROSBY_ZVOLANIE 92
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_1_PROSBY_ZVOLANIE "MODL_OPTF_1_PROSBY_ZVOLANIE"
#else
	#define STR_MODL_OPTF_1_PROSBY_ZVOLANIE "of1prz"
#endif

// pre force option 2 jednotlivÈ bit-komponenty (parci·lne voæby)

// ISO form·t d·tumu
#define MODL_OPTF_2_ISO_DATUM 81
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_ISO_DATUM "MODL_OPTF_2_ISO_DATUM"
#else
	#define STR_MODL_OPTF_2_ISO_DATUM "of2id"
#endif

// zobrazovaù button "prvÈ veöpery" v r·mci danÈho sl·venia (teda "ignoruj˙c d·tum")
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

// zobrazovaù navig·ciu v textoch modlitieb
#define MODL_OPTF_2_NAVIGATION 86
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_NAVIGATION "MODL_OPTF_2_NAVIGATION"
#else
	#define STR_MODL_OPTF_2_NAVIGATION "of2nav"
#endif

// zobrazovaù zalomenie v textoch modlitieb podæa tlaËenej LH
#define MODL_OPTF_2_TEXT_WRAP 87
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_TEXT_WRAP "MODL_OPTF_2_TEXT_WRAP"
#else
	#define STR_MODL_OPTF_2_TEXT_WRAP "of2tw"
#endif

// zobraziù buttony pre modlitby v ˙spornej podobe (tabuæka) kvÙli mobiln˝m zariadeniam
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

// rÙzne moûnosti zobrazovaù priamo v texte modlitieb (najm‰ pre android)
#define MODL_OPTF_2_ROZNE_MOZNOSTI 93
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_ROZNE_MOZNOSTI "MODL_OPTF_2_ROZNE_MOZNOSTI"
#else
	#define STR_MODL_OPTF_2_ROZNE_MOZNOSTI "of2rm"
#endif

// skryù navig·ciu -- BIT_OPT_2_HIDE_NAVIG_BUTTONS
#define MODL_OPTF_2_HIDE_NAVIG_BUTTONS 94
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_HIDE_NAVIG_BUTTONS "MODL_OPTF_2_HIDE_NAVIG_BUTTONS"
#else
	#define STR_MODL_OPTF_2_HIDE_NAVIG_BUTTONS "of2hnb"
#endif

// skryù kalend·r -- BIT_OPT_2_HIDE_KALENDAR
#define MODL_OPTF_2_HIDE_KALENDAR 95
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_HIDE_KALENDAR "MODL_OPTF_2_HIDE_KALENDAR"
#else
	#define STR_MODL_OPTF_2_HIDE_KALENDAR "of2hk"
#endif

// skryù options, prv· Ëasù -- BIT_OPT_2_HIDE_OPTIONS1
#define MODL_OPTF_2_HIDE_OPTIONS1 96
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_HIDE_OPTIONS1 "MODL_OPTF_2_HIDE_OPTIONS1"
#else
	#define STR_MODL_OPTF_2_HIDE_OPTIONS1 "of2ho1"
#endif

// skryù options, druh· Ëasù -- BIT_OPT_2_HIDE_OPTIONS2
#define MODL_OPTF_2_HIDE_OPTIONS2 97
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPTF_2_HIDE_OPTIONS2 "MODL_OPTF_2_HIDE_OPTIONS2"
#else
	#define STR_MODL_OPTF_2_HIDE_OPTIONS2 "of2ho2"
#endif

// 2008-08-08: PridanÈ kvÙli rÙznym css
#define CSS 40
#ifdef LONG_PARAM_NAMES
	#define STR_CSS "CSS"
#else
	#define STR_CSS "c"
#endif

// 2008-11-29: PridanÈ: spÙsob zapisovania d·tumu pre s˙bory v batch mÛde
#define MODL_OPT_DATE_FORMAT 41
#ifdef LONG_PARAM_NAMES
	#define STR_MODL_OPT_DATE_FORMAT "MODL_OPT_DATE_FORMAT"
#else
	#define STR_MODL_OPT_DATE_FORMAT "u"
#endif

// 2010-08-04: PridanÈ kvÙli jazykov˝m mut·ci·m -- kalend·r (napr. rehoæn˝)
#define KALENDAR 42
#ifdef LONG_PARAM_NAMES
	#define STR_KALENDAR "KALENDAR"
#else
	#define STR_KALENDAR "k"
#endif

// n·zov fontu
#define FONT_NAME 43
#ifdef LONG_PARAM_NAMES
	#define STR_FONT_NAME "FONT_NAME"
#else
	#define STR_FONT_NAME "f"
#endif

// n·zov veækosti fontu
#define FONT_SIZE 44
#ifdef LONG_PARAM_NAMES
	#define STR_FONT_SIZE "FONT_SIZE"
#else
	#define STR_FONT_SIZE "s"
#endif

// global
#define QUERY_TYPE	20
#ifdef LONG_PARAM_NAMES
	#define STR_QUERY_TYPE "QUERY_TYPE"
#else
	#define STR_QUERY_TYPE "qt"
#endif

// 2012-10-16: upraven˝ tento define tak, ûe vûdy musÌ byù pred volanÌm funkcie Export(); doÚho dovn˙tra som dal volanie hlaviËky
#define ALERT	{\
	hlavicka((char *)html_title[_global_jazyk]);\
	Export("<p>Ak probl&eacute;my pretrv&aacute;vaj&uacute;, kontaktujte pros&iacute;m <a href=\"mailto:%s\">autora str&aacute;nky</a>.</p>\n", cfg_mail_address_default[_global_jazyk]);\
	}

// HTML stringy - casti stringov sustredene na tomto mieste; pridane 2003-07-02; rozöÌrenÈ 2011-01-27
#define HTML_FORM_INPUT_SUBMIT   "input type=\"submit\" class=\"button\""
#define HTML_FORM_INPUT_RESET    "input type=\"reset\" class=\"reset\""
#define HTML_FORM_INPUT_RADIO    "input type=\"radio\" class=\"radio\""
#define HTML_FORM_INPUT_TEXT     "input type=\"text\" class=\"text\""
#define HTML_FORM_INPUT_TEXT_ROK "input type=\"text\" class=\"text\" size=\"4\" maxlength=\"4\" style=\"font-family:monospace\""
#define HTML_FORM_INPUT_CHECKBOX "input type=\"checkbox\" class=\"checkbox\""
// 2011-01-27: pridanÈ buttony (0. level: pre predoöl˝/nasledovn˝; 1. level: button "dnes"; 2. level: pouûitÈ pre menej dÙleûitÈ buttony)
#define HTML_FORM_INPUT_SUBMIT0  "input type=\"submit\" class=\"button0\""
#define HTML_FORM_INPUT_RESET0   "input type=\"reset\" class=\"reset0\""
#define HTML_FORM_INPUT_SUBMIT1  "input type=\"submit\" class=\"button1\""
#define HTML_FORM_INPUT_RESET1   "input type=\"reset\" class=\"reset1\""
#define HTML_FORM_INPUT_SUBMIT2  "input type=\"submit\" class=\"button2\""
#define HTML_FORM_INPUT_RESET2   "input type=\"reset\" class=\"reset2\""
#define HTML_FORM_INPUT_HIDDEN   "input type=\"hidden\""

// #define HTML_FORM_METHOD_GET  "<form action=\"%s\">\n"
#define HTML_FORM_METHOD_GET     "<form action=\"%s\" method=\"get\">\n"
#define HTML_FORM_METHOD_POST    "<form action=\"%s\" method=\"post\">\n"

#define HTML_LINK_RED    "a class=\"red\""
#define HTML_LINK_NORMAL "a"

#define HTML_NONBREAKING_SPACE "&nbsp;"
#define HTML_SPACE " "
#define HTML_VERTICAL_BAR "|"
#define HTML_LINE_BREAK "<br/>"
#define HTML_NEW_PARAGRAPH "<p>"

#define HTML_SPAN_NORMAL    "span class=\"normal\""
#define HTML_SPAN_ITALIC    "span class=\"it\""
#define HTML_SPAN_BOLD      "span class=\"bold\""
#define HTML_SPAN_BOLD_IT   "span class=\"boldit\""
#define HTML_SPAN_RED       "span class=\"red\""
#define HTML_SPAN_RED_BOLD  "span class=\"redbold\""
#define HTML_SPAN_BLUE      "span class=\"blue\""
#define HTML_SPAN_BLUE_BOLD "span class=\"bluebold\""
#define HTML_SPAN_RED_SMALL "span class=\"redsmall\""
#define HTML_SPAN_SMALL     "span class=\"small\""
#define HTML_SPAN_EXPLAIN   "span class=\"explain\""
#define HTML_SPAN_PARAMETER "span class=\"parameter\""
#define HTML_SPAN_VALUE     "span class=\"value\""
#define HTML_SPAN_SMALLCAPS "span class=\"smallcaps\""
#define HTML_SPAN_XS_CAPS   "span class=\"xsmallcaps\""

#define HTML_SPAN_TOOLTIP   "span title=\"%s\"" // obsahuje %s
#define HTML_SPAN_BOLD_TOOLTIP   "span class=\"bold\" title=\"%s\"" // obsahuje %s

#define HTML_SUP_RED        "sup class=\"red\""

#define HTML_CLASS_BLUE     "class=\"blue\""
#define HTML_CLASS_QUIET    "class=\"quiet\""
#define HTML_CLASS_BOLD_IT  "class=\"boldit\""
#define HTML_CLASS_LEVEL1   "class=\"level1\""
#define HTML_CLASS_TT       "class=\"tt\""
#define HTML_CLASS_BUTTON   "class=\"button\""
#define HTML_CLASS_SMALL    "class=\"small\""

#define HTML_ALIGN_CENTER   "align=\"center\""
#define HTML_ALIGN_LEFT     "align=\"left\""
#define HTML_ALIGN_RIGHT    "align=\"right\""
#define HTML_VALIGN_MIDDLE  "valign=\"middle\""
#define HTML_VALIGN_TOP     "valign=\"top\""
#define HTML_VALIGN_BASE    "valign=\"baseline\""

// pridane 2003-07-09, zmenene v cestach pre skript
#define HTML_AMPERSAND          "&amp;"

#define HTML_COMMENT_BEGIN		"<!--"
#define HTML_COMMENT_END		"-->"
#define HTML_FONT_SIZE_FARBA	"2"
// 2007-03-19: pridanÈ namiesto gt a lt html znakov
#define HTML_LEFT_ARROW			"&laquo;"
#define HTML_RIGHT_ARROW		"&raquo;"

#define HTML_LINK_CALL1         "%s?%s=%s"HTML_AMPERSAND"%s=%d"HTML_AMPERSAND"%s=%d"HTML_AMPERSAND"%s=%d%s"
#define HTML_LINK_CALL2         "%s?%s=%s"HTML_AMPERSAND"%s=%s"HTML_AMPERSAND"%s=%d"HTML_AMPERSAND"%s=%d%s"
#define HTML_LINK_CALL_PARAM    HTML_AMPERSAND"%s=%s"
// 2011-01-26: pridanÈ jednoduchÈ öÌpky væavo/vpravo
#define HTML_LEFT_ARROW_SINGLE	"&lsaquo;"
#define HTML_RIGHT_ARROW_SINGLE	"&rsaquo;"
// 2011-01-26: pridanÈ "trojitÈ" öÌpky væavo/vpravo
#define HTML_LEFT_ARROW_HUGE	"&lsaquo;&laquo;"
#define HTML_RIGHT_ARROW_HUGE	"&raquo;&rsaquo;"

// 2007-03-19: v˝pis "Dnes je..." sa zobrazÌ len pri tomto nastavenÌ, ak je 1
#define HTML_ZOBRAZIT_DNES_JE	0

// 2007-06-01: niektorÈ definy presunutÈ z liturgia.h

// option 2
#define MODL_ZALMY_ZO_DNA 0
#define MODL_ZALMY_ZO_SV  1

// option 5, 2003-08-06, upravena 2003-08-13
#define MODL_CEZ_DEN_ZALMY_ZO_DNA         0
#define MODL_CEZ_DEN_DOPLNKOVA_PSALMODIA  1

// 2008-11-29: pridanÈ rÙzne moûnosti batch exportu
#define	EXPORT_DATE_SIMPLE 0
#define	EXPORT_DATE_FULL   1

#define STR_SIMPLE "simple"
#define STR_FULL   "full"

// n·zov s˙boru (jeho zaËiatok) pre d·tum
#define FILENAME_EXPORT_DATE_SIMPLE "%.2d%.2d%.2d"
#define FILENAME_EXPORT_DATE_FULL   "%.4d-%.2d-%.2d"
// n·zov adres·ra pre mesiac
#define DIRNAME_EXPORT_MONTH_SIMPLE "%.2d%.2d-%s"
#define DIRNAME_EXPORT_MONTH_FULL   "%.4d-%.2d-%s"
// n·zov s˙boru (jeho zaËiatok) pre mesiac
#define FILENAME_EXPORT_MONTH_SIMPLE "%.2d%.2d"
#define FILENAME_EXPORT_MONTH_FULL   "%.4d-%.2d"

#define HTML_ISO_FORMAT      "%04d-%02d-%02d"

#define TEXT_COPYRIGHT       "(c) 1999-2013 Juraj VidÈky"
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

// POCET_OPT_0_SPECIALNE
#define XML_BIT_OPT_0_VERSE                     "BitOpt0VerseNumbers"
#define XML_BIT_OPT_0_REFERENCIE                "BitOpt0References"
#define XML_BIT_OPT_0_CITANIA                   "BitOpt0Readings"
#define XML_BIT_OPT_0_ZJAVENIE_PANA_NEDELA      "BitOpt0EpiphanyOnSunday"
#define XML_BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA   "BitOpt0AssumptionOnSunday"
#define XML_BIT_OPT_0_TELAKRVI_NEDELA           "BitOpt0CorpusChristiOnSunday"

// POCET_OPT_1_CASTI_MODLITBY
#define XML_BIT_OPT_1_TEDEUM                    "BitOpt1TeDeum"
#define XML_BIT_OPT_1_RUBRIKY                   "BitOpt1Rubrics"
#define XML_BIT_OPT_1_CHVALOSPEVY               "BitOpt1Canticles"
#define XML_BIT_OPT_1_SLAVA_OTCU                "BitOpt1GloryPrayer"
#define XML_BIT_OPT_1_OTCENAS                   "BitOpt1OurFatherPrayer"
#define XML_BIT_OPT_1_MCD_ZALMY_INE             "BitOpt1SupplPsalmodyDuringDay"
#define XML_BIT_OPT_1_PC_VIGILIA                "BitOpt1VigilAfterReadings"
#define XML_BIT_OPT_1_SPOMIENKA_SPOL_CAST       "BitOpt1MemoriesTakeFromCommunia"
#define XML_BIT_OPT_1_PLNE_RESP                 "BitOpt1FullResponses"
#define XML_BIT_OPT_1_ZALM95                    "BitOpt1InvitatoryUsePsalm95"
#define XML_BIT_OPT_1_PROSBY_ZVOLANIE           "BitOpt1Repeat"
#define XML_BIT_OPT_1_SKRY_POPIS                "BitOpt1HideDescription"
#define XML_BIT_OPT_1_ZOBRAZ_SPOL_CAST          "BitOpt1ShowCommuniaDescription"
#define XML_BIT_OPT_1_VESP_KRATSIE_PROSBY       "BitOpt1UseVespShortenPrayers"

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

// POCET_OPT_4_OFFLINE_EXPORT
#define XML_BIT_OPT_4_MESIAC_RIADOK             "BitOpt4MonthAtLine"

// starting, closing element (XML, HTML)
#define ELEM_BEGIN(elem)     "<"elem">"
#define ELEM_END(elem)       "</"elem">"

#define ELEMID_BEGIN(elem)   "<"elem" Id=\"%d\">"
#define ELEMVAL_BEGIN(elem)  "<"elem" Value=\"%d\" Name=\"%s\" ForceName=\"%s\">"
#define ELEMOPT_BEGIN(elem)  "<"elem" Id=\"%d\" ForceName=\"%s\">" // Id napr. BIT_OPT_0_VERSE; Name napr. STR_MODL_OPTF_0_VERSE

#endif // __MYDEFS_H_


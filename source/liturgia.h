/************************************************************/
/*                                                          */
/* liturgia.h                                               */
/* (c)1999-2025 | Juraj Vidéky | videky@breviar.sk          */
/*                                                          */
/* description | basic 'liturgical' constants, defines      */
/*               and structures                             */
/*                                                          */
/*                                                          */
/*   WARNING: NEVER REMOVE COMMENTS FOR ADDING NEW VALUES   */
/*                                                          */
/*   STRING_1_FOR_NEW_LANGUAGE etc.                         */
/*                                                          */
/************************************************************/

#include "vstudio.h"

#ifndef __LITURGIA_H_
#define __LITURGIA_H_

#include "mysystem.h"
#include "mysysdef.h"
#include "mydefs.h"
#include "common.h"
#include "mylog.h"
#include "myconf.h"
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define MENO_SVIATKU 260
#define MAX_LC_STR_ID 50

// "null" year, month, day
#define NULL_YEAR 0
#define NULL_MONTH -1
#define NULL_DAY 0

// "null" day order within year; special "null" values for special solemnities and feasts of the Lord
#define NULL_DAY_OF_THE_YEAR 0
#define NULL_KRST_KRISTA_PANA -1
#define NULL_POPOLCOVA_STREDA -2
#define NULL_VELKONOCNA_NEDELA -3
#define NULL_NANEBOVSTUPENIE_PANA -4
#define NULL_ZOSLANIE_DUCHA_SV -5
#define NULL_PRVA_ADVENTNA_NEDELA -6
#define NULL_SVATEJ_RODINY -7
#define NULL_ZJAVENIE_PANA 6 // pretend as if date was Jan 6th

// liturgical rites
#define RITUS_RIM_KAT   0
#define RITUS_GR_KAT    1

// language IDs (constants) according to ISO 3166-1 alpha-2
#define JAZYK_SK	0
#define JAZYK_CZ	1
#define JAZYK_EN	2
#define JAZYK_LA    3
#define JAZYK_UNDEF 4
#define JAZYK_CZ_OP 5
#define JAZYK_HU    6
#define JAZYK_RU    7
#define JAZYK_BY    8
#define JAZYK_IS    9
#define JAZYK_ES   10
#define JAZYK_AZ   11
/* ADD_VALUE_FOR_NEW_LANGUAGE */

// rite for languages
const short int ritus_jazyka[POCET_JAZYKOV + 1] =
{
	RITUS_RIM_KAT,
	RITUS_RIM_KAT,
	RITUS_RIM_KAT,
	RITUS_RIM_KAT,
	RITUS_RIM_KAT,
	RITUS_RIM_KAT,
	RITUS_RIM_KAT,
	RITUS_RIM_KAT,
	RITUS_RIM_KAT,
	RITUS_RIM_KAT,
	RITUS_RIM_KAT,
	RITUS_RIM_KAT,
	/* ADD_VALUE_FOR_NEW_LANGUAGE */
};

// formats of date (HU, EN...)
#define FORMAT_DATUMU_DEN_MESIAC_ROK 0 // DD. MM RRRR
#define FORMAT_DATUMU_MESIAC_DEN_ROK 1 // MM DD RRRR
#define FORMAT_DATUMU_ROK_MESIAC_DEN 2 // RRRR. MM DD

extern const short int format_datumu[POCET_JAZYKOV + 1];

// usage of dot for indicating ordinal numbers
#define FORMAT_DATE_DO_NOT_USE_DOT_FOR_ORDINALS 0
#define FORMAT_DATE_USE_DOT_FOR_ORDINALS        1

extern const short int use_dot_for_ordinals[POCET_JAZYKOV + 1];

// themes
#define THEME_UNDEF	 -1
#define THEME_LIGHT  0
#define THEME_DARK   1

// background color
#define THEME_BACKGROUND_COLOR_UNDEF ""

// sidemenu locations
#define SIDEMENU_LOCATION_UNDEF	-1
#define SIDEMENU_LOCATION_LEFT	0
#define SIDEMENU_LOCATION_RIGHT	1

// static texts
#define POCET_STATIC_TEXTOV               3

#define STATIC_TEXT_UNDEF                 0
#define STATIC_TEXT_MARIANSKE_ANTIFONY    1
#define STATIC_TEXT_ORDINARIUM            2
#define STATIC_TEXT_INFO                  3

// info files (used for mobile applications: about, version history...)
#define POCET_INFO_TEXTOV       1

#define INFO_ABOUT              0
#define INFO_VERSION_HISTORY    1

// number of fonts
#define	POCET_FONTOV    10

// fonts used in drop-down list
#define FONT_CUSTOM      0
#define FONT_CSS         1
#define FONT_CHECKBOX    2
#define FONT_CAMBRIA     3
#define FONT_CANDARA     4
#define FONT_GEORGIA     5
#define FONT_TAHOMA	     6
#define FONT_HELVETICA   7
#define FONT_VERDANA     8
#define FONT_SERIF	     9
#define FONT_SANS_SERIF 10

// number of font-sizes
#define	POCET_FONT_SIZE  8

// font-sizes in drop-down list
#define FONT_SIZE_UNDEF		0
#define FONT_SIZE_CSS		1 // inherit
#define FONT_SIZE_XX_SMALL	2
#define FONT_SIZE_X_SMALL 	3
#define FONT_SIZE_SMALL   	4
#define FONT_SIZE_MEDIUM  	5
#define FONT_SIZE_LARGE   	6
#define FONT_SIZE_X_LARGE 	7
#define FONT_SIZE_XX_LARGE	8

// font size in pt, default
// #define FONT_SIZE_PT_DEFAULT  12

// style margin, in pixels (px)
#define MIN_STYLE_MARGIN      0
#define MAX_STYLE_MARGIN   1024
#define DEF_STYLE_MARGIN      5

// line height, in percents (%)
#define MIN_LINE_HEIGHT_PERC      0
#define MAX_LINE_HEIGHT_PERC    512
#define DEF_LINE_HEIGHT_PERC    130

// alternatives for some parts of prayers
#define BIT_ALT_HYMNUS                  1
#define BIT_ALT_ANTCHVAL                2
#define BIT_ALT_LEN_DOPLNKOVA_PSALMODIA 4
#define BIT_ALT_DOPLNK_PSALM_122_129    8
#define BIT_ALT_DOPLNK_PSALM_127_131   16
#define BIT_ALT_DOPLNK_PSALM_126_129   32
#define BIT_ALT_HYMNUS_VN              64
#define BIT_ALT_OFF_DEF_PSALM_146_150 128
#define BIT_ALT_ANT_INVITATORIUM      256

#define MAX_STR_AF_FILE   64
#define MAX_STR_AF_ANCHOR 32

struct _anchor_and_file {
	char file[MAX_STR_AF_FILE];
	char anchor[MAX_STR_AF_ANCHOR];
};
typedef struct _anchor_and_file _struct_anchor_and_file;

struct _anchor_and_file_mapping {
	_struct_anchor_and_file source;
	_struct_anchor_and_file dest;
};
typedef struct _anchor_and_file_mapping _struct_anchor_and_file_mapping;

#define rchvalospev  zalm2
#define vchvalospev  zalm3
#define magnifikat   benediktus

struct tmodlitba1 {
	short int alternativy; // bitové komponenty hovoria, ktoré časti môžu mať alternatívy
	_struct_anchor_and_file popis;
	_struct_anchor_and_file hymnus;
	_struct_anchor_and_file antifona1;
	_struct_anchor_and_file zalm1;
	_struct_anchor_and_file antifona2;
	_struct_anchor_and_file zalm2;
	_struct_anchor_and_file antifona3;
	_struct_anchor_and_file zalm3;
	_struct_anchor_and_file kcitanie;
	_struct_anchor_and_file kresponz;
	_struct_anchor_and_file benediktus; // antifona na benediktus/magnifikat
	_struct_anchor_and_file prosby; // pre posvatne citanie nedefinovane; 2011-03-16: "zneužité" (použité) pre hagiografické čítanie (ľubovoľnej) spomienky svätca v pôste
	_struct_anchor_and_file modlitba;
	_struct_anchor_and_file ant_spomprivileg; // 2010-05-21: pridané kvôli spomienkam a ľubovoľným spomienkam v pôstnom období (zobrazenie po modlitbe dňa pôstnej férie) // 2012-02-09: zovšeobecnené v zmysle VSLH č. 238 (Spomienky pripadajúce na privilegované dni)
	_struct_anchor_and_file modlitba_spomprivileg; // 2010-05-21: pridané kvôli spomienkam a ľubovoľným spomienkam v pôstnom období (zobrazenie po modlitbe dňa pôstnej férie) // 2012-02-09: zovšeobecnené v zmysle VSLH č. 238 (Spomienky pripadajúce na privilegované dni)
	_struct_anchor_and_file otcenas_uvod; // 2020-08-27: intro for Pater noster
};
typedef struct tmodlitba1 _type_ranne_chvaly;
typedef struct tmodlitba1 _type_vespery;
typedef struct tmodlitba1 _type_1vespery;

struct tmodlitba2 {
	short int alternativy; // bitové komponenty hovoria, ktoré časti môžu mať alternatívy
	_struct_anchor_and_file popis;
	_struct_anchor_and_file hymnus;
	_struct_anchor_and_file antifona1;
	_struct_anchor_and_file zalm1;
	_struct_anchor_and_file antifona2;
	_struct_anchor_and_file zalm2;
	_struct_anchor_and_file antifona3;
	_struct_anchor_and_file zalm3;
	_struct_anchor_and_file kcitanie;
	_struct_anchor_and_file kresponz;
	_struct_anchor_and_file modlitba;
};
typedef struct tmodlitba2 _type_cez_den_9;
typedef struct tmodlitba2 _type_cez_den_12;
typedef struct tmodlitba2 _type_cez_den_3;

// alternate typenames for prayer during the day
typedef struct tmodlitba2 _type_cez_den_pred;
typedef struct tmodlitba2 _type_cez_den_na;
typedef struct tmodlitba2 _type_cez_den_po;

struct tmodlitba3 {
	short int alternativy; // bitové komponenty hovoria, ktoré časti môžu mať alternatívy
	short int pocet_zalmov; // pridané 2006-10-18; niekedy sú až 2 žalmy
	_struct_anchor_and_file popis;
	_struct_anchor_and_file ukonkaj; // added 2018-03-06; act of repentance
	_struct_anchor_and_file hymnus;
	_struct_anchor_and_file antifona1;
	_struct_anchor_and_file zalm1;
	_struct_anchor_and_file antifona2;
	_struct_anchor_and_file zalm2;
	_struct_anchor_and_file kcitanie;
	_struct_anchor_and_file kresponz;
	_struct_anchor_and_file nunc_dimittis; // antifóna na nunc dimittis; pridané 2013-04-03 (kvôli OPRAEM, 08dec)
	_struct_anchor_and_file modlitba;
	_struct_anchor_and_file maria_ant; // added 2018-03-23; Mary antiphone
};
typedef struct tmodlitba3 _type_kompletorium;
typedef struct tmodlitba3 _type_1kompletorium;

struct tmodlitba4 {
	short int alternativy; // bitové komponenty hovoria, ktoré časti môžu mať alternatívy
	_struct_anchor_and_file popis;
	_struct_anchor_and_file antifona1;
	_struct_anchor_and_file zalm1;
};
typedef struct tmodlitba4 _type_invitatorium;

struct tmodlitba5 {
	short int alternativy; // bitové komponenty hovoria, ktoré časti môžu mať alternatívy
	_struct_anchor_and_file popis;
	_struct_anchor_and_file hymnus;
	_struct_anchor_and_file antifona1;
	_struct_anchor_and_file zalm1;
	_struct_anchor_and_file antifona2;
	_struct_anchor_and_file zalm2;
	_struct_anchor_and_file antifona3;
	_struct_anchor_and_file zalm3;
	_struct_anchor_and_file kresponz;
	_struct_anchor_and_file citanie1; // 1. citanie pre posvatne citanie
	_struct_anchor_and_file citanie2; // 2. citanie pre posvatne citanie
	_struct_anchor_and_file citanie_spomprivileg; // 2011-03-16: "zneužité" (použité) pre hagiografické čítanie (ľubovoľnej) spomienky svätca v pôste; 2011-03-25: nový typ -> nové meno
	_struct_anchor_and_file ant_chval; // vigília: antifóna pre chválospevy
	_struct_anchor_and_file chval1; // vigília: chválospev I
	_struct_anchor_and_file chval2; // vigília: chválospev II
	_struct_anchor_and_file chval3; // vigília: chválospev III
	_struct_anchor_and_file evanjelium; // vigília: evanjelium
	_struct_anchor_and_file modlitba;
};
typedef struct tmodlitba5 _type_posv_citanie;

struct den_mesiac {
	short int den;    // cislo dna mesiaca (1--31)
	short int mesiac; // cislo mesiaca (1--12) - ináč ako je potrebné pre väčšinu polí, kde je mesiac 0--11
};
typedef struct den_mesiac _struct_den_mesiac;

// number of prayers
#define POCET_MODLITIEB         14

// prayers IDs
#define MODL_INVITATORIUM       0
#define MODL_POSV_CITANIE       1
#define MODL_RANNE_CHVALY       2
#define MODL_CEZ_DEN_9          3
#define MODL_CEZ_DEN_12         4
#define MODL_CEZ_DEN_3          5
#define MODL_VESPERY            6
#define MODL_KOMPLETORIUM       7
#define MODL_NEURCENA           8

#define MODL_PRVE_VESPERY       9
#define MODL_PRVE_KOMPLETORIUM  10
#define MODL_DRUHE_VESPERY      11
#define MODL_DRUHE_KOMPLETORIUM 12

#define MODL_DETAILY            13

#define MODL_VSETKY             14

// alternate constants for prayer during the day
#define MODL_PREDPOLUDNIM       3
#define MODL_NAPOLUDNIE         4
#define MODL_POPOLUDNI          5

// all prayers during the day
#define MODL_CEZ_DEN_VSETKY     20

#define POCET_PORADIE_MODLITIEB_SHORT	7
const short int poradie_modlitieb_short[POCET_PORADIE_MODLITIEB_SHORT + 1] = {
	MODL_INVITATORIUM, MODL_POSV_CITANIE, MODL_RANNE_CHVALY, MODL_CEZ_DEN_9, MODL_CEZ_DEN_12, MODL_CEZ_DEN_3, MODL_VESPERY, MODL_KOMPLETORIUM
};

#define POCET_PORADIE_MODLITIEB_LONG	9
const short int poradie_modlitieb_long[POCET_PORADIE_MODLITIEB_LONG + 1] = {
	MODL_PRVE_VESPERY, MODL_PRVE_KOMPLETORIUM, MODL_INVITATORIUM, MODL_POSV_CITANIE, MODL_RANNE_CHVALY, MODL_CEZ_DEN_9, MODL_CEZ_DEN_12, MODL_CEZ_DEN_3, MODL_VESPERY, MODL_KOMPLETORIUM
};

// kvôli modlitbe kompletória, funkcia _set_kompletorium_nedela()
#define MODL_KOMPLETORIUM_NEDELNA	0
#define MODL_KOMPLETORIUM_SLAVNOSTI	1
#define MODL_KOMPLETORIUM_TROJDNIE	2

// strings for prayers (used in URLs)
#ifdef LONG_PARAM_NAMES
	#define		STR_MODL_INVITATORIUM	"MODL_INVITATORIUM"
	#define		STR_MODL_POSV_CITANIE	"MODL_POSV_CITANIE"
	#define		STR_MODL_RANNE_CHVALY	"MODL_RANNE_CHVALY"
	#define		STR_MODL_VESPERY		"MODL_VESPERY"
	#define		STR_MODL_PREDPOLUDNIM	"MODL_PREDPOLUDNIM"
	#define		STR_MODL_NAPOLUDNIE		"MODL_NAPOLUDNIE"
	#define		STR_MODL_POPOLUDNI		"MODL_POPOLUDNI"
	#define		STR_MODL_DETAILY		"MODL_DETAILY"
	#define		STR_MODL_KOMPLETORIUM	"MODL_KOMPLETORIUM"
	#define		STR_MODL_PRVE_VESPERY	"MODL_PRVE_VESPERY"
	#define		STR_MODL_PRVE_KOMPLETORIUM	"MODL_PRVE_KOMPLETORIUM"
	#define		STR_MODL_VSETKY            "MODL_VSETKY"
#else
	#define		STR_MODL_INVITATORIUM      "mi"
	#define		STR_MODL_POSV_CITANIE	   "mpc"
	#define		STR_MODL_RANNE_CHVALY      "mrch"
	#define		STR_MODL_VESPERY           "mv"
	#define		STR_MODL_PREDPOLUDNIM      "mpred"
	#define		STR_MODL_NAPOLUDNIE        "mna"
	#define		STR_MODL_POPOLUDNI         "mpo"
	#define		STR_MODL_DETAILY           "mdet"
	#define		STR_MODL_KOMPLETORIUM      "mk"
	#define		STR_MODL_PRVE_VESPERY      "mpv"
	#define		STR_MODL_PRVE_KOMPLETORIUM "mpk"
	#define		STR_MODL_VSETKY            "*"
#endif

// character for prayer used in anchors
#define CHAR_MODL_INVITATORIUM       'i'
#define CHAR_MODL_POSV_CITANIE       'c'
#define CHAR_MODL_RANNE_CHVALY       'r'
#define CHAR_MODL_CEZ_DEN_9          '9'
#define CHAR_MODL_CEZ_DEN_12         '2'
#define CHAR_MODL_CEZ_DEN_3          '3'
#define CHAR_MODL_VESPERY            'v'
#define CHAR_MODL_KOMPLETORIUM       'k'
#define CHAR_MODL_NEURCENA           '_' // not to be used
#define CHAR_MODL_PRVE_VESPERY       '1'
#define CHAR_MODL_PRVE_KOMPLETORIUM  'p'
#define CHAR_MODL_DRUHE_VESPERY      'w' // not to be used
#define CHAR_MODL_DRUHE_KOMPLETORIUM 'm' // not to be used
#define CHAR_MODL_VSETKY             '*'

// added for batch mode
extern const char char_modlitby[POCET_MODLITIEB + 1];
extern const char* str_modlitby[POCET_MODLITIEB + 1];

extern const char* nazov_modlitby_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1];
#define		nazov_modlitby(a)	nazov_modlitby_jazyk[a][_global_jazyk]

extern const char* nazov_Modlitby_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1];
#define		nazov_Modlitby(a)	nazov_Modlitby_jazyk[a][_global_jazyk]

#define TEMPLATE_PREFIX_HTML	"m"
#define TEMPLATE_PREFIX_XML		"../m"

#define TEMPLATE_POSTFIX_HTML	"htm"
#define TEMPLATE_POSTFIX_XML	"xml"

#define TEMPLATE_SEPARATOR		"_"
#define TEMPLATE_EXTENSION_SEPARATOR	"."

// base filenames for templates for prayers
#define TEMPLATE_BASE_INVITATORIUM     "invitat"
#define TEMPLATE_BASE_POSV_CITANIE     "posvcit"
#define TEMPLATE_BASE_RANNE_CHVALY     "rchvaly"
#define TEMPLATE_BASE_CEZ_DEN_9        "predpol"
#define TEMPLATE_BASE_CEZ_DEN_12       "napol"
#define TEMPLATE_BASE_CEZ_DEN_3        "popol"
#define TEMPLATE_BASE_VESPERY          "vespery"
#define TEMPLATE_BASE_KOMPLETORIUM     "komplet"
#define TEMPLATE_BASE_STATIC_TEXT      "text" // MODL_NEURCENA
#define TEMPLATE_BASE_EMPTY            STR_EMPTY

// HTML file templates for prayers
#define TEMPLATE_HTML_INVITATORIUM     TEMPLATE_PREFIX_HTML "" TEMPLATE_SEPARATOR "" TEMPLATE_BASE_INVITATORIUM "" TEMPLATE_EXTENSION_SEPARATOR "" TEMPLATE_POSTFIX_HTML
#define TEMPLATE_HTML_POSV_CITANIE     TEMPLATE_PREFIX_HTML "" TEMPLATE_SEPARATOR "" TEMPLATE_BASE_POSV_CITANIE	"" TEMPLATE_EXTENSION_SEPARATOR "" TEMPLATE_POSTFIX_HTML
#define TEMPLATE_HTML_RANNE_CHVALY     TEMPLATE_PREFIX_HTML "" TEMPLATE_SEPARATOR "" TEMPLATE_BASE_RANNE_CHVALY	"" TEMPLATE_EXTENSION_SEPARATOR "" TEMPLATE_POSTFIX_HTML
#define TEMPLATE_HTML_CEZ_DEN_9        TEMPLATE_PREFIX_HTML "" TEMPLATE_SEPARATOR "" TEMPLATE_BASE_CEZ_DEN_9    "" TEMPLATE_EXTENSION_SEPARATOR "" TEMPLATE_POSTFIX_HTML
#define TEMPLATE_HTML_CEZ_DEN_12       TEMPLATE_PREFIX_HTML "" TEMPLATE_SEPARATOR "" TEMPLATE_BASE_CEZ_DEN_12  	"" TEMPLATE_EXTENSION_SEPARATOR "" TEMPLATE_POSTFIX_HTML
#define TEMPLATE_HTML_CEZ_DEN_3        TEMPLATE_PREFIX_HTML "" TEMPLATE_SEPARATOR "" TEMPLATE_BASE_CEZ_DEN_3   	"" TEMPLATE_EXTENSION_SEPARATOR "" TEMPLATE_POSTFIX_HTML
#define TEMPLATE_HTML_VESPERY          TEMPLATE_PREFIX_HTML "" TEMPLATE_SEPARATOR "" TEMPLATE_BASE_VESPERY      "" TEMPLATE_EXTENSION_SEPARATOR "" TEMPLATE_POSTFIX_HTML
#define TEMPLATE_HTML_KOMPLETORIUM     TEMPLATE_PREFIX_HTML "" TEMPLATE_SEPARATOR "" TEMPLATE_BASE_KOMPLETORIUM	"" TEMPLATE_EXTENSION_SEPARATOR "" TEMPLATE_POSTFIX_HTML
#define TEMPLATE_HTML_STATIC_TEXT      TEMPLATE_PREFIX_HTML "" TEMPLATE_SEPARATOR "" TEMPLATE_BASE_STATIC_TEXT 	"" TEMPLATE_EXTENSION_SEPARATOR "" TEMPLATE_POSTFIX_HTML
#define TEMPLATE_HTML_EMPTY            STR_EMPTY

// HTML file templates for prayers
#define TEMPLATE_XML_INVITATORIUM     TEMPLATE_PREFIX_XML "" TEMPLATE_SEPARATOR "" TEMPLATE_BASE_INVITATORIUM "" TEMPLATE_EXTENSION_SEPARATOR "" TEMPLATE_POSTFIX_XML
#define TEMPLATE_XML_POSV_CITANIE     TEMPLATE_PREFIX_XML "" TEMPLATE_SEPARATOR "" TEMPLATE_BASE_POSV_CITANIE "" TEMPLATE_EXTENSION_SEPARATOR "" TEMPLATE_POSTFIX_XML
#define TEMPLATE_XML_RANNE_CHVALY     TEMPLATE_PREFIX_XML "" TEMPLATE_SEPARATOR "" TEMPLATE_BASE_RANNE_CHVALY "" TEMPLATE_EXTENSION_SEPARATOR "" TEMPLATE_POSTFIX_XML
#define TEMPLATE_XML_CEZ_DEN_9        TEMPLATE_PREFIX_XML "" TEMPLATE_SEPARATOR "" TEMPLATE_BASE_CEZ_DEN_9    "" TEMPLATE_EXTENSION_SEPARATOR "" TEMPLATE_POSTFIX_XML
#define TEMPLATE_XML_CEZ_DEN_12       TEMPLATE_PREFIX_XML "" TEMPLATE_SEPARATOR "" TEMPLATE_BASE_CEZ_DEN_12   "" TEMPLATE_EXTENSION_SEPARATOR "" TEMPLATE_POSTFIX_XML
#define TEMPLATE_XML_CEZ_DEN_3        TEMPLATE_PREFIX_XML "" TEMPLATE_SEPARATOR "" TEMPLATE_BASE_CEZ_DEN_3    "" TEMPLATE_EXTENSION_SEPARATOR "" TEMPLATE_POSTFIX_XML
#define TEMPLATE_XML_VESPERY          TEMPLATE_PREFIX_XML "" TEMPLATE_SEPARATOR "" TEMPLATE_BASE_VESPERY      "" TEMPLATE_EXTENSION_SEPARATOR "" TEMPLATE_POSTFIX_XML
#define TEMPLATE_XML_KOMPLETORIUM     TEMPLATE_PREFIX_XML "" TEMPLATE_SEPARATOR "" TEMPLATE_BASE_KOMPLETORIUM "" TEMPLATE_EXTENSION_SEPARATOR "" TEMPLATE_POSTFIX_XML
#define TEMPLATE_XML_STATIC_TEXT      TEMPLATE_PREFIX_XML "" TEMPLATE_SEPARATOR "" TEMPLATE_BASE_STATIC_TEXT  "" TEMPLATE_EXTENSION_SEPARATOR "" TEMPLATE_POSTFIX_XML
#define TEMPLATE_XML_EMPTY            STR_EMPTY

// compline in Ordinary time
#define nazov_obd_KOMPLETORIUM   "cezrok_k.htm"

extern const char* TEMPLAT[POCET_MODLITIEB + 1];

#define ORDINARIUM_INVITATORIUM     "ord_invitat.htm"
#define ORDINARIUM_POSV_CITANIE     "ord_posvcit.htm"
#define ORDINARIUM_RANNE_CHVALY     "ord_rchvaly.htm"
#define ORDINARIUM_CEZ_DEN          "ord_mcd.htm"
#define ORDINARIUM_VESPERY          "ord_vespery.htm"
#define ORDINARIUM_KOMPLETORIUM     "ord_komplet.htm"
#define ORDINARIUM_EMPTY            STR_EMPTY // MODL_VSETKY + MODL_DETAILY

extern const char* FILE_ORDINARIUM[POCET_MODLITIEB + 1];

extern const char* FILE_INFO[POCET_INFO_TEXTOV + 1];

#define FILE_INFO_ABOUT            "about.htm"
#if defined(IO_ANDROID)
#define FILE_VERSION_HISTORY       "version-android.htm"
#elif defined (__APPLE__)
#define FILE_VERSION_HISTORY       "version-ios.htm"
#else
#define FILE_VERSION_HISTORY       "version-web.htm"
#endif

#define SHOW_TEMPLAT_MODLITBA      1 // use TEMPLAT[]
#define SHOW_TEMPLAT_STATIC_TEXT   2 // use ORDINARIUM[]

// parameter identifiers
#define PARAM_POPIS         "POPIS"
#define PARAM_HYMNUS        "HYMNUS"
#define PARAM_ANTIFONA1     "ANTIFONA1"
#define PARAM_ANTIFONA2     "ANTIFONA2"
#define PARAM_ANTIFONA3     "ANTIFONA3"
#define PARAM_ZALM1         "ZALM1"
#define PARAM_ZALM2         "ZALM2"
#define PARAM_ZALM3         "ZALM3"
#define PARAM_ANTRCHVAL     "ANTRCHVAL" // vlastne ANTIFONA2
#define PARAM_ANTVCHVAL     "ANTVCHVAL" // vlastne ANTIFONA3
#define PARAM_RCHVALOSPEV   "RCHVALOSPEV" // vlastne ZALM2
#define PARAM_VCHVALOSPEV   "VCHVALOSPEV" // vlastne ZALM3
#define PARAM_KCITANIE      "KCITANIE"
#define PARAM_KRESPONZ      "KRESPONZ"
#define PARAM_MAGNIFIKAT    "MAGNIFIKAT" // antifóna na Magnifikat
#define PARAM_BENEDIKTUS    "BENEDIKTUS" // antifóna na Benediktus
#define PARAM_NUNC_DIMITTIS "NUNCDIMITTIS" // antifóna na Nunc dimittis
#define PARAM_PROSBY        "PROSBY"
#define PARAM_MODLITBA      "MODLITBA"
#define PARAM_CITANIE1      "CITANIE1" // vlastne KCITANIE
#define PARAM_CITANIE2      "CITANIE2" // vlastne BENEDIKTUS
#define PARAM_UKON_KAJ      "UKONKAJ" // úkon kajúcnosti -- act of repentance
#define PARAM_MARIA_ANT     "MARIA_ANT" // mariánske antifóny -- Mary antiphone

#define PARAM_ANTIFONA1x    "ANTIFONA1_DRUHA"
#define PARAM_ANTIFONA3x    "ANTIFONA3_PRVA"

#define PARAM_ANTIFONA1k    "ANTIFONA1_KOMPLET"
#define PARAM_ANTIFONA2k    "ANTIFONA2_KOMPLET"
// VSLH č. 238 (Spomienky pripadajúce na privilegované dni)
#define PARAM_ANT_SPOMPRIVILEG  "ANT_SPOMPRIVILEG"
#define PARAM_MODL_SPOMPRIVILEG "MODL_SPOMPRIVILEG"
#define PARAM_CITANIE2_SPOMPRIVILEG "CITANIE2_SPOMPRIVILEG"

#define PARAM_NAVIGACIA     "NAVIGACIA"
#define PARAM_NAVIGACIA_SIMPLE "NAVIGACIA_SIMPLE" // just top & bottom links

#define PARAM_NADPIS        "NADPIS"
#define PARAM_PODNADPIS     "PODNADPIS" // podnadpis v modlitbe (napr. pre MCD: doplnková psalmódia)
#define PARAM_SPOL_CAST     "SPOL-CAST"

#define PARAM_ANTIFONA_VIG  "ANTIFONA_VIG"
#define PARAM_CHVALOSPEV1   "CHVALOSPEV1"
#define PARAM_CHVALOSPEV2   "CHVALOSPEV2"
#define PARAM_CHVALOSPEV3   "CHVALOSPEV3"
#define PARAM_EVANJELIUM    "EVANJELIUM"

#define PARAM_TEXT          "TEXT" // static text included into single file

// these are used also for <a name...> -- do not use underscore in these names :)
#define PARAM_DOPLNKOVA_PSALMODIA      "DOPLNKOVA-PSALMODIA" // supplementary psalmody (for daily prayers: 9h, 12h, 15h)
#define PARAM_PSALMODIA                "PSALMODIA" // alternative psalmody (e. g. for morning prayer, Ash Wednesday)

#define PARAM_PSALMODIA_TRI_TYZDNE     "PSALMODIA-TRI-TYZDNE" // v zmysle De Liturgia Horarum; Notitiae 8 (1972) p. 254-264

#define PARAM_ZAVER                    "ZAVER"
#define PARAM_ZAVER_KNAZ_DIAKON        "ZAVER-KNAZ-DIAKON"
#define PARAM_ZAVER_OSTATNI            "ZAVER-OSTATNI"
#define PARAM_CHVALOSPEV               "CHVALOSPEV"
#define PARAM_TEDEUM		           "TEDEUM"
#define PARAM_OTCENAS                  "OTCENAS"
#define PARAM_OTCENAS_UVOD             "OTCENAS-UVOD"
#define PARAM_ZOBRAZ_OTCENAS_UVOD      "ZOBRAZ-OTCENAS-UVOD"
#define PARAM_ZVOLANIA                 "ZVOLANIA"
#define PARAM_SLAVAOTCU	               "SLAVAOTCU"
#define PARAM_RESPONZ                  "RESPONZ"
#define PARAM_KRATSIE_PROSBY           "KRATSIE-PROSBY"
#define PARAM_ZALM95                   "ZALM95"
#define PARAM_VIGILIA                  "VIGILIA"
#define PARAM_SPOL_CAST_SPOM           "SPOL-CAST-SPOM"
#define PARAM_OVERRIDE_STUPEN_SLAVENIA "OVERRIDE-STUPEN-SLAVENIA"
#define PARAM_STUPEN_SLAVENIA_SVI_SLAV "STUPEN-SLAVENIA-SVIATOK-SLAVNOST"
#define PARAM_ALT_HYMNUS               "ALT-HYMNUS"
#define PARAM_ZALM122                  "ZALM122"
#define PARAM_ZALM126                  "ZALM126"
#define PARAM_ZALM127                  "ZALM127"
#define PARAM_ZALM129                  "ZALM129"
#define PARAM_ZALM131                  "ZALM131"
#define PARAM_ZALM146                  "ZALM146"
#define PARAM_ZALM150                  "ZALM150"
#define PARAM_MARIANSKE_ANTIFONY       "MARIANSKE-ANTIFONY" // Maria antiphones at the end of compline
#define PARAM_OKTAVA_PRVE_DRUHE_KOMPL  "OKTAVA-PRVE-DRUHE-KOMPLETORIUM"

// these are used in template for invitatory (m_invitat.htm) for hyperlinks
#define PARAM_INVITAT_PSALM_24        "INVITAT-PS-24"
#define PARAM_INVITAT_PSALM_67        "INVITAT-PS-67"
#define PARAM_INVITAT_PSALM_95        "INVITAT-PS-95"
#define PARAM_INVITAT_PSALM_100       "INVITAT-PS-100"

// keywords
#define KEYWORD_BEGIN   "BEGIN"
#define KEYWORD_END     "END"
#define KEYWORD_MULTI   "MULTI"
#define KEYWORD_OCR_34  "OCR-34"
#define KEYWORD_INVITAT_COMMON          "INVITAT-COMMON"
#define KEYWORD_INVITAT_PSALM_SIMPLE    "INVITAT-PSALM"
#define KEYWORD_INVITAT_PSALM(i)        KEYWORD_INVITAT_PSALM_SIMPLE i

#define KEYWORD_ALELUJA_ALELUJA         "ALELUJA_ALELUJA"
#define KEYWORD_ALELUJA_NIE_V_POSTE     "ALELUJA_NIE_V_POSTE"
#define KEYWORD_ALELUJA_VO_VELKONOCNOM  "V_O_ALELUJA"
#define KEYWORD_OTCENAS                 "OTCENAS"
#define KEYWORD_PARAM_CHVALOSPEV        "CHVALOSPEV"
#define KEYWORD_KOMPLETORIUM_DVA_ZALMY	"KOMPLETORIUM_DVA_ZALMY"
#define KEYWORD_SLAVAOTCU               "SLAVAOTCU"
#define KEYWORD_SLAVAOTCU_SPEC          "SLAVAOTCU_SPEC"
#define KEYWORD_TEDEUM                  "TEDEUM"
#define KEYWORD_JE_TEDEUM               "JE_TEDEUM"
#define KEYWORD_COPYRIGHT               "COPYRIGHT"
#define KEYWORD_SKRY_ANTIFONU           "SKRY_ANTIFONU"
#define KEYWORD_ZOBRAZ_ANTIFONU         "ZOBRAZ_ANTIFONU"
#define KEYWORD_JE_VIGILIA              "JE_VIGILIA"
#define KEYWORD_SPOMIENKA_PRIVILEG      "SPOMIENKA_PRIVILEG"
#define KEYWORD_RUBRIKA                 "RUBRIKA"
#define KEYWORD_VN_VYNECHAJ             "VELK_NEDELA_VYNECHAJ"
#define KEYWORD_ZAVER                   "ZAVER"
#define KEYWORD_ZAVER_KNAZ_DIAKON       "ZAVER_KNAZ_DIAKON"
#define KEYWORD_ZAVER_OSTATNI           "ZAVER_OSTATNI"
#define KEYWORD_HIDE_FOR_VOICE_OUTPUT   "HIDE_FOR_VOICE_OUTPUT"
#define KEYWORD_TTS_HEADING             "TTS:HEADING"
#define KEYWORD_TTS_SECTION             "TTS:SECTION"
#define KEYWORD_MARIANSKE_ANTIFONY      "MARIANSKE-ANTIFONY" // Maria antiphones at the end of compline
#define KEYWORD_ZOBRAZ_OTCENAS_UVOD     "UVOD-OTCENAS" // must not start with already used "OTCENAS" keyword because startsWith() is used

#define SYMBOL_END "/"

// parameters
#define PARAM_INVITAT_COMMON_BEGIN          KEYWORD_INVITAT_COMMON "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_INVITAT_COMMON_END            KEYWORD_INVITAT_COMMON "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_INVITAT_PSALM_BEGIN(i)        KEYWORD_INVITAT_PSALM(i) "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_INVITAT_PSALM_END(i)          KEYWORD_INVITAT_PSALM(i) "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_ALELUJA_ALELUJA_BEGIN         KEYWORD_ALELUJA_ALELUJA "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_ALELUJA_ALELUJA_END           KEYWORD_ALELUJA_ALELUJA "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_ALELUJA_NIE_V_POSTE           KEYWORD_ALELUJA_NIE_V_POSTE
#define PARAM_ALELUJA_NIE_V_POSTE_BEGIN     KEYWORD_ALELUJA_NIE_V_POSTE "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_ALELUJA_NIE_V_POSTE_END       KEYWORD_ALELUJA_NIE_V_POSTE "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_ALELUJA_VO_VELKONOCNOM        KEYWORD_ALELUJA_VO_VELKONOCNOM
#define PARAM_ALELUJA_VO_VELKONOCNOM_BEGIN  KEYWORD_ALELUJA_VO_VELKONOCNOM "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_ALELUJA_VO_VELKONOCNOM_END    KEYWORD_ALELUJA_VO_VELKONOCNOM "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_OTCENAS_BEGIN                 KEYWORD_OTCENAS "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_OTCENAS_END                   KEYWORD_OTCENAS "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_ZOBRAZ_OTCENAS_UVOD_BEGIN     KEYWORD_ZOBRAZ_OTCENAS_UVOD "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_ZOBRAZ_OTCENAS_UVOD_END       KEYWORD_ZOBRAZ_OTCENAS_UVOD "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_CHVALOSPEV_BEGIN              KEYWORD_PARAM_CHVALOSPEV "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_CHVALOSPEV_END                KEYWORD_PARAM_CHVALOSPEV "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_KOMPLETORIUM_DVA_ZALMY_BEGIN	KEYWORD_KOMPLETORIUM_DVA_ZALMY "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_KOMPLETORIUM_DVA_ZALMY_END	KEYWORD_KOMPLETORIUM_DVA_ZALMY "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_SLAVAOTCU_BEGIN               KEYWORD_SLAVAOTCU "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_SLAVAOTCU_END                 KEYWORD_SLAVAOTCU "" STR_UNDERSCORE "" KEYWORD_END
// special case: Sláva Otcu "špeciálne" pre účely chválospevu Dan 3, 57-88. 56, kde nie je "Sláva Otcu" (pôvodne to bolo dané poradím, ale templáty pre rôzne jazyky majú rozličné poradie tohto "Sláva Otcu")
#define PARAM_SLAVAOTCU_SPEC_BEGIN          KEYWORD_SLAVAOTCU_SPEC "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_SLAVAOTCU_SPEC_END            KEYWORD_SLAVAOTCU_SPEC "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_ZAVER_BEGIN                   KEYWORD_ZAVER "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_ZAVER_END                     KEYWORD_ZAVER "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_ZAVER_KNAZ_DIAKON_BEGIN       KEYWORD_ZAVER_KNAZ_DIAKON "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_ZAVER_KNAZ_DIAKON_END         KEYWORD_ZAVER_KNAZ_DIAKON "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_ZAVER_OSTATNI_BEGIN           KEYWORD_ZAVER_OSTATNI "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_ZAVER_OSTATNI_END             KEYWORD_ZAVER_OSTATNI "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_MARIANSKE_ANTIFONY_BEGIN      KEYWORD_MARIANSKE_ANTIFONY "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_MARIANSKE_ANTIFONY_END        KEYWORD_MARIANSKE_ANTIFONY "" STR_UNDERSCORE "" KEYWORD_END

#define PARAM_HIDE_FOR_VOICE_OUTPUT         KEYWORD_HIDE_FOR_VOICE_OUTPUT

#define PARAM_COPYRIGHT_BEGIN               KEYWORD_COPYRIGHT "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_COPYRIGHT_END                 KEYWORD_COPYRIGHT "" STR_UNDERSCORE "" KEYWORD_END
// JE_TEDEUM_BEGIN a END hovoria, či v danej modlitbe má vôbec byť zobrazená čo i len zmienka o Te Deum (riadené podmienkou je_tedeum);
// TEDEUM_BEGIN a END hovoria, že ak má byť Te Deum (je_tedeum), tak ak chce používateľ zobraziť plný text, ohraničujú ho
#define PARAM_TEDEUM_BEGIN                  KEYWORD_TEDEUM "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_TEDEUM_END                    KEYWORD_TEDEUM "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_JE_TEDEUM_BEGIN               KEYWORD_JE_TEDEUM "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_JE_TEDEUM_END                 KEYWORD_JE_TEDEUM "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_RUBRIKA_BEGIN                 KEYWORD_RUBRIKA "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_RUBRIKA_END                   KEYWORD_RUBRIKA "" STR_UNDERSCORE "" KEYWORD_END
// posvätné čítanie na veľkonočnú nedeľu
#define PARAM_VN_VYNECHAJ_BEGIN             KEYWORD_VN_VYNECHAJ "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_VN_VYNECHAJ_END               KEYWORD_VN_VYNECHAJ "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_SKRY_ANTIFONU_BEGIN           KEYWORD_SKRY_ANTIFONU "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_SKRY_ANTIFONU_END             KEYWORD_SKRY_ANTIFONU "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_ZOBRAZ_ANTIFONU_BEGIN         KEYWORD_ZOBRAZ_ANTIFONU "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_ZOBRAZ_ANTIFONU_END           KEYWORD_ZOBRAZ_ANTIFONU "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_JE_VIGILIA_BEGIN              KEYWORD_JE_VIGILIA "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_JE_VIGILIA_END                KEYWORD_JE_VIGILIA "" STR_UNDERSCORE "" KEYWORD_END
// zobrazenie antifóny a modlitby pre spomienku svätca v pôstnom období + zovšeobecnené v zmysle VSLH č. 238 (Spomienky pripadajúce na privilegované dni)
#define PARAM_SPOMIENKA_PRIVILEG_BEGIN      KEYWORD_SPOMIENKA_PRIVILEG "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_SPOMIENKA_PRIVILEG_END        KEYWORD_SPOMIENKA_PRIVILEG "" STR_UNDERSCORE "" KEYWORD_END

// TTS parameters
#define PARAM_TTS_HEADING_BEGIN             KEYWORD_TTS_HEADING "" STR_UNDERSCORE "" KEYWORD_BEGIN
#define PARAM_TTS_HEADING_END               KEYWORD_TTS_HEADING "" STR_UNDERSCORE "" KEYWORD_END
#define PARAM_TTS_SECTION                   KEYWORD_TTS_SECTION

// zobrazenie/skrytie myšlienky k žalmu -- pre cezročné obdobie alternatívnej antifóny žalmu/chválospevu ("myšlienka k žalmu" podľa bodu 111 a 114 VSLH)
#define PARAM_PSALMODIA_MYSLIENKA           "PSALMODIA_MYSLIENKA" // 2011-08-31: zmenené; pôvodne bolo: PARAM_MYSLIENKA_K_ZALMU "MYSLIENKA_K_ZALMU"
// zobrazenie/skrytie nadpisu k žalmu/chválospevu ("nadpis k žalmu" podľa bodu 111 VSLH)
#define PARAM_PSALMODIA_NADPIS              "PSALMODIA_NADPIS"

// zobrazovanie/skrývanie dlhších záverov responzórií v posvätnom čítaní + responzóriá pre ranné chvály a vešpery po krátkom čítaní
#define PARAM_PLNE_RESP                     "PLNE_RESP"
#define PARAM_PLNE_RESP_BODKA               "PLNE_RESP_BODKA"
#define PARAM_NIE_PLNE_RESP                 "NIE_PLNE_RESP" // negácia PARAM_PLNE_RESP

// zobrazovanie/skrývanie opakovaného zvolania v prosbách (ranné chvály, vešpery)
#define PARAM_ZVOLANIE                      "ZVOLANIE"

// rubriky priamo v includovaných HTML súboroch
#define PARAM_RUBRIKA                       "RUBRIKA"

#define PARAM_ALT_HYMNUS_OCR_34             PARAM_ALT_HYMNUS "-" KEYWORD_OCR_34

// multiple alternatives
#define PARAM_ALT_HYMNUS_MULTI              PARAM_ALT_HYMNUS "-" KEYWORD_MULTI
#define PARAM_ALT_CITANIE2_MULTI            "ALT-CITANIE2-" KEYWORD_MULTI
#define PARAM_ALT_CITANIE1_MULTI            "ALT-CITANIE1-" KEYWORD_MULTI
#define PARAM_ALT_ANTIFONA_MULTI            "ALT-ANTIFONA-" KEYWORD_MULTI
#define PARAM_ALT_MODLITBA_MULTI            "ALT-MODLITBA-" KEYWORD_MULTI
#define PARAM_ALT_OTCENAS_UVOD_MULTI        "ALT-OTCENAS-UVOD-" KEYWORD_MULTI
#define PARAM_ALT_PROSBY_MULTI              "ALT-PROSBY-" KEYWORD_MULTI
#define PARAM_ALT_KCIT_RESP_MULTI           "ALT-KCIT-RESP-" KEYWORD_MULTI
#define PARAM_ALT_KRESP_MULTI               "ALT-KRESP-" KEYWORD_MULTI
#define PARAM_ALT_PSALM_MULTI               "ALT-PSALM-" KEYWORD_MULTI
#define PARAM_ALT_UKONKAJ_MULTI             "ALT-UKONKAJ-" KEYWORD_MULTI // used as acronym for PARAM_ALT_PROSBY_MULTI
#define PARAM_ALT_MARIA_ANT_MULTI           "ALT-MARIA-ANT-" KEYWORD_MULTI

// variants (other alternatives)
#define PARAM_VAR_CITANIE2                  "VAR-CITANIE2"

// zobrazenie/skrytie číslovania veršov v žalmoch, chválospevoch a biblických čítaniach
#define PARAM_CISLO_VERSA_BEGIN				"v"
#define PARAM_CISLO_VERSA_END				SYMBOL_END "" PARAM_CISLO_VERSA_BEGIN

// referencia podľa biblického odkazu na stránky dkc.kbs.sk (Biblia -- Matúš Brilla)
#define PARAM_REFERENCIA_BEGIN				"r"
#define PARAM_REFERENCIA_END				SYMBOL_END "" PARAM_REFERENCIA_BEGIN

// odkaz na katechézy
#define PARAM_KATECHEZA_BEGIN				"k"
#define PARAM_KATECHEZA_END					SYMBOL_END "" PARAM_KATECHEZA_BEGIN

// footnote reference (subscript)
#define PARAM_FOOTNOTE_REF_BEGIN			"fnr"
#define PARAM_FOOTNOTE_REF_END				SYMBOL_END "" PARAM_FOOTNOTE_REF_BEGIN

// footnote (text under main text)
#define PARAM_FOOTNOTE_BEGIN			    "fn"
#define PARAM_FOOTNOTE_END				    SYMBOL_END "" PARAM_FOOTNOTE_BEGIN

// note (text in parentheses)
#define PARAM_NOTE_BEGIN			        "n"
#define PARAM_NOTE_END				        SYMBOL_END "" PARAM_NOTE_BEGIN

// odkaz na žalm 95
#define PARAM_LINK_ZALM95_BEGIN				"z95"
#define PARAM_LINK_ZALM95_END				SYMBOL_END "" PARAM_LINK_ZALM95_BEGIN

// zobrazenie znakov kurzívou (podmienečné)
#define PARAM_ITALICS_COND_BEGIN			"i"
#define PARAM_ITALICS_COND_END				SYMBOL_END "" PARAM_ITALICS_COND_BEGIN

// full text of psalms (also verses omitted from official Latin LH)
#define PARAM_PSALM_FULL_TEXT_BEGIN         "full-text"
#define PARAM_PSALM_FULL_TEXT_END           SYMBOL_END "" PARAM_PSALM_FULL_TEXT_BEGIN
// these two have the same usage as previous two except adding div's (used within section divided due to different psalm strophes as in Ps 55)
#define PARAM_PSALM_FULL_TEXT_SOFT_BEGIN    "full-text-soft"
#define PARAM_PSALM_FULL_TEXT_SOFT_END      SYMBOL_END "" PARAM_PSALM_FULL_TEXT_SOFT_BEGIN
// full text of other text [e.g. readings] (also verses omitted from official Latin LH)
#define PARAM_PSALM_FULL_TEXT_TXT_BEGIN     "full-text-txt"
#define PARAM_PSALM_FULL_TEXT_TXT_END       SYMBOL_END "" PARAM_PSALM_FULL_TEXT_TXT_BEGIN

// pause, to be exported (in readings)
#define PARAM_PAUSE                         "p"
#define PARAM_PAUSE_SHORT                   "ps"

// normal (black) stuff in psalmody (cross, asterisk)
#define PARAM_NORMAL_CROSS                     "+"
#define PARAM_NORMAL_ASTERISK                  "x"

// red stuff in antiphones etc. (red cross, red asterisk, red triangle)
#define PARAM_RED_CROSS                     "†" // used as flexa | U+2020 DAGGER
#define PARAM_RED_CROSS_TXT                 "CROSS" // alternative due to Unicode problem when interpreting template (2017-08-14)
#define PARAM_RED_ASTERISK                  "*"
#define PARAM_RED_TRIANGLE                  "△" // 'uppercase delta': Δ (used for doxology) | U+25B3 WHITE UP-POINTING TRIANGLE
#define PARAM_RED_TRIANGLE_TXT              "TRIANGLE" // alternative due to Unicode problem when interpreting template (2017-08-14)
/*
// red stuff prepared (not yet used) as indication for singing
#define PARAM_RED_SINGLE_BAR                "|" // used for pause in antiphons & responsories (when singing)
#define PARAM_RED_DOUBLE_BAR                "||" // used for indication that chorus should join (when singing antiphons & responsories)
#define PARAM_RED_CROSS_DOUBLE_BAR          "†||"
#define PARAM_RED_SMALL_CIRCLE              "°" // used for elevation in prayer
*/

// zobrazovanie/nezobrazenie krížika (antifóna totožná s veršom žalmu/chválospevu)
#define PARAM_KRIZIK                        "KRIZIK"

// zobrazovanie/nezobrazenie zalomených textov tak, ako je v tlačenom vydaní LH (dlhé riadky-verše žalmov/chválospevov a pod.)
#define PARAM_ZALOMENIE                     "ZALOMENIE"

// zakončenie modlitieb (skrze, lebo on, lebo ty...) ináč (jednoduchšie, bez begin-end)
#define PARAM_ZAKONCENIE                    "ZAKONCENIE"

// doplnková psalmódia, alternatívne žalmy
#define PARAM_DOPLNK_PSALM_122_129          "DPSALM-122-129"
#define PARAM_DOPLNK_PSALM_126_129          "DPSALM-126-129"
#define PARAM_DOPLNK_PSALM_127_131          "DPSALM-127-131"
// alternatíva žalmov pre ranné chvály ofícia za zosnulých
#define PARAM_OFF_DEF_PSALM_146_150         "OFFDEF-146-150"

// zakončenie modlitby trojaké, krátke resp. dlhé
#define PARAM_ZAKONCENIE_SKRZE              "SKRZE"
#define PARAM_ZAKONCENIE_LEBO_TY            "LEBO_TY"
#define PARAM_ZAKONCENIE_LEBO_ON            "LEBO_ON"
// zakončenie modlitby trojaké, krátke resp. dlhé s malým písmenkom na začiatku
#define PARAM_ZAKONCENIE_SKRZE_MALE         "SKRZE_MALE"
#define PARAM_ZAKONCENIE_LEBO_TY_MALE       "LEBO_TY_MALE"
#define PARAM_ZAKONCENIE_LEBO_ON_MALE       "LEBO_ON_MALE"
// ešte jedno zakončenie modlitby pre slovenčinu, krátke resp. dlhé (POST1_MODLITBA5NE)
#define PARAM_ZAKONCENIE_ON_JE              "ON_JE"
// ešte jedno zakončenie modlitby pre slovenčinu resp. pre IS, krátke resp. dlhé
#define PARAM_ZAKONCENIE_KTORY_JE_MALE      "KTORY_JE_MALE"
#define PARAM_ZAKONCENIE_KTORY_JE           "KTORY_JE"
// zakončenia modlitby pre IS
#define PARAM_ZAKONCENIE_KTORY_ZIJES        "KTORY_ZIJES"
// predslovy k zakončeniam, ktoré sa pre férie nemajú zobraziť, ak sa slávi spomienka v privilegovaných dňoch
#define PARAM_ZAKONCENIE_O_TO_TA_PROSIME    "O_TO_TA_PROSIME"

// force pre jednotlivé časti modlitby, funkcie _set_spolocna_cast()...
#define FORCE_NEBRAT               0
#define FORCE_BRAT_ANTIFONY        1 // antifóny pre ranné chvály, posv. čítanie a vešpery
#define FORCE_BRAT_ZALMY           2 // psalmódia pre ranné chvály, posv. čítanie a vešpery; ak niekde je vlastná psalmódia len pre časť týchto modlitieb, je potrebné nastavovať ju ručne
#define FORCE_BRAT_KCIT_1CIT       4 // krátke čítanie pre rch+v a mcd; 1. čítanie pre posvätné čítanie
#define FORCE_BRAT_KRESP           8 // krátke responzórium pre ranné chvály, vešpery, posv. čítanie a mcd
#define FORCE_BRAT_2CITANIE       16 // 2. čítanie pre posvätné čítanie
#define FORCE_BRAT_ANTIFONY_MCD   32 // antifóny pre modlitbu cez deň
#define FORCE_BRAT_HYMNUS         64 // hymnus pre všetky modlitby
#define FORCE_BRAT_ANTIFONY_B_M  128 // Benediktus + Magnifikat (výnimočne aj pre na Nunc dimittis)
#define FORCE_BRAT_ANTIFONY_INV  256 // antifóny pre invitatórium
#define FORCE_BRAT_MODLITBA      512 // modlitba (používa sa pre modlitbu cez deň)
#define FORCE_BRAT_PROSBY       1024 // prosby pre ranné chvály a vešpery
// force all
#define FORCE_BRAT_VSETKO      65535 // FORCE_BRAT_ANTIFONY + FORCE_BRAT_ZALMY + ... (všetky / all)

extern const char* str_ano[POCET_JAZYKOV + 1];
#ifndef		STR_ANO
#define		STR_ANO		str_ano[_global_jazyk]
#endif

extern const char* str_nie[POCET_JAZYKOV + 1];
#ifndef		STR_NIE
#define		STR_NIE		str_nie[_global_jazyk]
#endif

extern const char* str_modl_zalmy_zo_dna[POCET_JAZYKOV + 1];
#ifndef		STR_MODL_ZALMY_ZO_DNA
#define		STR_MODL_ZALMY_ZO_DNA 	str_modl_zalmy_zo_dna[_global_jazyk]
#endif

extern const char* str_modl_zalmy_zo_sv[POCET_JAZYKOV + 1];
#ifndef		STR_MODL_ZALMY_ZO_SV
#define		STR_MODL_ZALMY_ZO_SV 	str_modl_zalmy_zo_sv[_global_jazyk]
#endif

// note that je_spolocna_cast_urcena() is not intended to use for member spolcast of dm structure!
#define je_spolocna_cast_urcena(spolcast) ((spolcast > MODL_SPOL_CAST_NEURCENA) && (spolcast < MODL_SPOL_CAST_NEBRAT))

// option 3 -- tieto nasledujuce definicie definuju to, co je sucastou _struct_dm::spolcast
#define MAX_MODL_SPOL_CAST  28
// najviac MAX_MODL_SPOL_CAST "spolocnych casti", t.j. identifikatorov MODL_SPOL_CAST_...; musi byt o jedno vacsia ako poslena, t.j. MODL_SPOL_CAST_NEBRAT

#define MODL_SPOL_CAST_NULL              -1
#define MODL_SPOL_CAST_NEURCENA           0
#define MODL_SPOL_CAST_DUCH_PAST_KNAZ     1
#define MODL_SPOL_CAST_DUCH_PAST_BISKUP   2
#define MODL_SPOL_CAST_DUCH_PAST_PAPEZ    3
#define MODL_SPOL_CAST_UCITEL_CIRKVI      4
#define MODL_SPOL_CAST_APOSTOL            5
#define MODL_SPOL_CAST_MUCENIK            6 // muz
#define MODL_SPOL_CAST_VIAC_MUCENIKOV     7
#define MODL_SPOL_CAST_PANNA_MARIA        8
#define MODL_SPOL_CAST_SV_MUZ_REHOLNIK    9
#define MODL_SPOL_CAST_SV_MUZ            10 // jeden
#define MODL_SPOL_CAST_PANNA             11 // jedna
#define MODL_SPOL_CAST_SV_ZENA_REHOLNIK  12
#define MODL_SPOL_CAST_SV_ZENA           13 // jedna
#define MODL_SPOL_CAST_DUCH_PAST_VIACERI 14
#define MODL_SPOL_CAST_MUCENICA          15 // zena
#define MODL_SPOL_CAST_SV_ZENA_VYCH      16
#define MODL_SPOL_CAST_SV_MUZ_VYCH       17
#define MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL 18
#define MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL  19
#define MODL_SPOL_CAST_SV_ZENA_VIACERE   20
#define MODL_SPOL_CAST_SV_MUZ_VIACERI    21 // viaceri
#define MODL_SPOL_CAST_PANNY_VIACERE     22 // viacere
#define MODL_SPOL_CAST_POSVIACKA_CHRAMU  23
#define MODL_SPOL_CAST_ZA_ZOSNULYCH      24
#define MODL_SPOL_CAST_SV_ZENA_MANZ      25 // pre tých, čo žili v manželstve
#define MODL_SPOL_CAST_SV_MUZ_MANZ       26 // pre tých, čo žili v manželstve
#define MODL_SPOL_CAST_NEBRAT            27 // nechce zo spol. casti // MUST BE THE LAST VALUE
#define POCET_SPOL_CASTI	MAX_MODL_SPOL_CAST - 1

const short int poradie_spol_cast[POCET_SPOL_CASTI + 1] = {
	MODL_SPOL_CAST_NEBRAT,
	MODL_SPOL_CAST_ZA_ZOSNULYCH,
	MODL_SPOL_CAST_POSVIACKA_CHRAMU,
	MODL_SPOL_CAST_PANNA_MARIA,
	MODL_SPOL_CAST_APOSTOL,
	MODL_SPOL_CAST_VIAC_MUCENIKOV,
	MODL_SPOL_CAST_MUCENIK,
	MODL_SPOL_CAST_MUCENICA,
	MODL_SPOL_CAST_DUCH_PAST_PAPEZ,
	MODL_SPOL_CAST_DUCH_PAST_BISKUP,
	MODL_SPOL_CAST_DUCH_PAST_KNAZ,
	MODL_SPOL_CAST_DUCH_PAST_VIACERI,
	MODL_SPOL_CAST_UCITEL_CIRKVI,
	MODL_SPOL_CAST_PANNA,
	MODL_SPOL_CAST_PANNY_VIACERE,
	MODL_SPOL_CAST_SV_MUZ,
	MODL_SPOL_CAST_SV_MUZ_MANZ,
	MODL_SPOL_CAST_SV_MUZ_VIACERI,
	MODL_SPOL_CAST_SV_ZENA,
	MODL_SPOL_CAST_SV_ZENA_MANZ,
	MODL_SPOL_CAST_SV_ZENA_VIACERE,
	MODL_SPOL_CAST_SV_MUZ_REHOLNIK,
	MODL_SPOL_CAST_SV_ZENA_REHOLNIK,
	MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL,
	MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL,
	MODL_SPOL_CAST_SV_MUZ_VYCH,
	MODL_SPOL_CAST_SV_ZENA_VYCH,
	MODL_SPOL_CAST_NEURCENA
};

extern const char* str_doplnkova_psalmodia[POCET_JAZYKOV + 1];

extern const char* str_modl_cez_den_zalmy_zo_dna[POCET_JAZYKOV + 1];
#ifndef		STR_MODL_CEZ_DEN_ZALMY_ZO_DNA
#define		STR_MODL_CEZ_DEN_ZALMY_ZO_DNA	str_modl_cez_den_zalmy_zo_dna[_global_jazyk]
#endif

extern const char* str_modl_cez_den_doplnkova_psalmodia[POCET_JAZYKOV + 1];
#ifndef		STR_MODL_CEZ_DEN_DOPLNKOVA_PSALMODIA
#define		STR_MODL_CEZ_DEN_DOPLNKOVA_PSALMODIA	str_modl_cez_den_doplnkova_psalmodia[_global_jazyk]
#endif

extern const char* nazov_spolc_jazyk[POCET_SPOL_CASTI + 1][POCET_JAZYKOV + 1];
#ifndef		nazov_spolc
#define		nazov_spolc(a)	nazov_spolc_jazyk[a][_global_jazyk]
#endif

extern const char* nazov_spolc_htm[MODL_SPOL_CAST_NEBRAT + 1];
extern const char* nazov_spolc_ANCHOR[MODL_SPOL_CAST_NEBRAT + 1];

#define ANCHOR_SPOL_CAST_DUCH_PAST "SCDP"

#define ANCHOR_SPOL_CAST_JEDEN_MUCENIK "SCJM"

#define ANCHOR_SPOL_CAST_PANNA_MUCENICA "SCAM"

struct sc{
	short int a1;
	short int a2;
	short int a3;
};
typedef struct sc _struct_sc;

// main structure for day (day + month + liturgical properties)
struct dm{
	short int den;        // cislo dna mesiaca (1--31)
	short int mesiac;     // cislo mesiaca (1--12)
	short int rok;        // rok
	short int denvt;      // cislo dna v tyzdni (0--6) DEN_...
	short int denvr;      // cislo dna v roku (1--365/366) -- deň v roku
	// toto boli "obcianske" zalezitosti
	char litrok;          // liturgicky rok ('A'--'C') -- nedeľný cyklus (Sunday's cycle for breviary & lectionaries)
	short int tyzden;     // tyzden v danom liturgickom obdobi
	short int tyzzal;     // tyzden v zaltari (vacsinou ((tyzden - 1) % 4) + 1)
	short int litobd;     // liturgicke obdobie, OBD_...
	short int typslav;    // typ slavenia (1--5): SLAV_...
	short int typslav_lokal; // lokálny typ slavenia : LOKAL_SLAV_...
	short int smer;       // poradove cislo z c.59 Vseobecnych smernic o liturgii hodin a kalendari
	short int prik;		  // ci je to prikazany sviatok alebo nie: PRIKAZANY_SVIATOK resp. NIE_JE_PRIKAZANY_SVIATOK
	int spolcast;		  // spolocna cast -- zakodovane data pre svatych o tom, z akej spolocnej casti sa ma modlit;
						  // obsahuje max. 3 spolocne casti vo formate spolcast == a1 + a2 * MAX + a3 * MAX * MAX,
						  // kde -- MAX je MAX_MODL_SPOL_CAST,
						  //     -- a1, a2, a3 su konstanty MODL_SPOL_CAST_... (v poradi a1, ak druhe tak a2, ak tretie tak aj a3)
						  // _encode_..., _decode_spol_cast();
	char meno[MENO_SVIATKU]; // nazov prip. sviatku
	short int farba;      // liturgická farba pre slávenie
	short int kalendar;   // špecifikácia, o aký kalendár ide: všeobecný danej cirkevnej provincie alebo nejaký rehoľný a pod.
	char lc_str_id[MAX_LC_STR_ID]; // liturgické čítania: identifikátor podľa lc.kbs.sk
	short int flags;      // special flags, e. g. indication that celebration has different collecta for some prayer etc.
};
typedef struct dm _struct_dm;

// liturgické obdobia | liturgical times/seasons
#define OBD_NEURCENE              -1 // not defined; should not be used normally; only for special cases
//OBD_ADVENTNE
#define OBD_ADVENTNE_I             0 // do 16. decembra
#define OBD_ADVENTNE_II            1 // po 16. decembri
//OBD_VIANOCNE
#define OBD_OKTAVA_NARODENIA       2 // narodenie Pana -- 1. jan.
#define OBD_VIANOCNE_I             3 // do slavnosti zjavenia pana
#define OBD_VIANOCNE_II            4 // po slavnosti zjavenia pana
//OBD_CEZ_ROK
#define OBD_CEZ_ROK                5
//OBD_POSTNE
#define OBD_POSTNE_I               6 // do soboty v piatom tyzdni
#define OBD_POSTNE_II_VELKY_TYZDEN 7 // velky tyzden
//OBD_VELKONOCNE_TROJDNIE
#define OBD_VELKONOCNE_TROJDNIE    8 // umucenia a zmrtvychvstania Pana
//OBD_VELKONOCNE
#define OBD_VELKONOCNA_OKTAVA      9 // velkonocna nedela -- 2. velk. ne
#define OBD_VELKONOCNE_I          10 // do nanebovstupenia pana
#define OBD_VELKONOCNE_II         11 // po nanebovstupeni pana

// number of liturgical times/seasons
#define	POCET_OBDOBI	11

// LH volume | zväzok breviára - zväzok, v ktorom sa nachádza dané liturgické obdobie; doplnené 2007-12-20; opravené 2008-01-23
const short int zvazok_breviara[POCET_OBDOBI + 1] = 
{1, 1, 1, 1, 1, 3, 2, 2, 2, 2, 2, 2}; // nepotrebujeme rozlíšiť 3. a 4. zväzok, ktoré obidva obsahujú OBD_CEZ_ROK

// # of weeks for season | počet týždňov pre dané liturgické obdobie
const short int lit_obd_pocet_tyzdnov[POCET_OBDOBI + 1] = 
{4, 1, 1, 2, 1, 34, 6, 1, 1, 1, 7, 2};

extern const char* nazov_obdobia_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1];
#define		nazov_obdobia(a)	nazov_obdobia_jazyk[a][_global_jazyk]

extern const char* nazov_obdobia_ext_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1];
#define		nazov_obdobia_ext(a)	nazov_obdobia_ext_jazyk[a][_global_jazyk]

extern const char* nazov_obdobia_[POCET_OBDOBI + 1];

// lokal == 6. pad, v kom/com
extern const char* nazov_obdobia_v_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1];
#define		nazov_obdobia_v(a)	nazov_obdobia_v_jazyk[a][_global_jazyk]

extern const char* nazov_Obdobia_aka_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1];
#define		nazov_Obdobia_aka(a)	nazov_Obdobia_aka_jazyk[a][_global_jazyk]

// gen[itiv] == 2. pad, koho/coho

// nazov_obdobia: string pre nazov suboru .htm liturgickeho obdobia
extern const char* nazov_obd_htm[POCET_OBDOBI + 1];
// nazov_obdobia: string pre nazov kotvy v .htm liturgickeho obdobia
extern const char* nazov_OBD[POCET_OBDOBI + 1];
// nazov_obdobia pc: string pre nazov suboru .htm liturgickeho obdobia pre posvatne citania
extern const char* nazov_obd_htm_pc[POCET_OBDOBI + 1];
// 2005-08-05: Pridané. zväzok breviára (LH) pre spoločné časti svätých v kotvách
extern const char* zvazok_OBD[POCET_OBDOBI + 1];

// celebration types
#define SLAV_NEURCENE            0
#define SLAV_SLAVNOST            1
#define SLAV_SVIATOK             2
#define SLAV_SPOMIENKA           3
#define SLAV_LUB_SPOMIENKA       4
#define SLAV_VLASTNE             5

// number of celebration types
#define	POCET_SLAVENI            5

// nazov_slavenia: string pre nazov typu slavenia
extern const char* nazov_slavenia_jazyk[POCET_SLAVENI + 1][POCET_JAZYKOV + 1];
#define		nazov_slavenia(a)	nazov_slavenia_jazyk[a][_global_jazyk]

// the name of celebration -- for memoria (in privileged days)
extern const char* nazov_slavenia_na_spomienku_jazyk[POCET_JAZYKOV + 1];

extern const char* nazov_slavenia_lokal[];

#define LOKAL_SLAV_NEURCENE							0
#define LOKAL_SLAV_ROZNAVA_SZLOVAKIA				1
#define LOKAL_SLAV_TRNAVA_PATRON					2
#define LOKAL_SLAV_ROZNAVA_HU					    3
#define LOKAL_SLAV_NITRA_PATRON						4
#define LOKAL_SLAV_KOSICE							5
#define LOKAL_SLAV_NITRA							6
#define LOKAL_SLAV_BYSTRICA							7
#define LOKAL_SLAV_SPIS								8
#define LOKAL_SLAV_ROZNAVA							9
#define LOKAL_SLAV_TRNAVA							10
#define LOKAL_SLAV_DOM_SV_MARTINA					11
#define LOKAL_SLAV_SZLOVAKIA_EMLEKNAP_HU			12
#define LOKAL_SLAV_BYSTRICA_PATRON					13
#define LOKAL_SLAV_TT_BB_NR_RO						14
#define LOKAL_SLAV_KOSICE_PATRON					15
#define LOKAL_SLAV_14_FEB_CYRIL_METOD				16
#define LOKAL_SLAV_ROZNAVA_PATRON					17
#define LOKAL_SLAV_KONSEKR_KOSTOLY					18
#define LOKAL_SLAV_DRUHA_VELK_NEDELA				19
#define LOKAL_SLAV_KONIEC_OKTAVY_NAR				20
#define LOKAL_SLAV_SVIATOK_FMA						21
#define LOKAL_SLAV_PRAHA_PATRON						22
#define LOKAL_SLAV_PRAHA							23
#define LOKAL_SLAV_BRNO								24
#define LOKAL_SLAV_MORAVA_SPOMIENKA					25
#define LOKAL_SLAV_SVIATOK_OFMCAP_PRESUN_OFM		26
#define LOKAL_SLAV_PRAHA_KATEDRALA					27
#define LOKAL_SLAV_CESKE_BUDEJOVICE					28
#define LOKAL_SLAV_OLOMOUC							29
#define LOKAL_SLAV_CECHY_SPOMIENKA					30
#define LOKAL_SLAV_PLZEN_PATRON						31
#define LOKAL_SLAV_OSTRAVA_OPAVA					32
#define LOKAL_SLAV_LITOMERICE						33
#define LOKAL_SLAV_HRADEC_KRALOVE					34
#define LOKAL_SLAV_SDB_ONLY		                    35
#define LOKAL_SLAV_PLZEN 							36
#define LOKAL_SLAV_OSTRAVA_OPAVA_SLAVNOST			37
#define LOKAL_SLAV_CESKE_BUDEJOVICE_PAMATKA			38
#define LOKAL_SLAV_SPIS_BA_PATRON					39
#define LOKAL_SLAV_BRATISLAVA						40
#define LOKAL_SLAV_LUB_SPOMIENKA_FMA_VDB			41
#define LOKAL_SLAV_SZLOVAKIA_FOPATRONAJA_HU			42
#define LOKAL_SLAV_SPOMIENKA_OFMCAP					43
#define LOKAL_SLAV_SVIATOK_OFM						44
#define LOKAL_SLAV_SPOMIENKA_OFM					45
#define LOKAL_SLAV_SVIATOK_OFMCAP					46
#define LOKAL_SLAV_SPOMIENKA_FMA					47
#define LOKAL_SLAV_SLAVNOST_FMA						48
#define LOKAL_SLAV_SVIATOK_FMA_CZ					49
#define LOKAL_SLAV_SVIATOK_VDB						50
#define LOKAL_SLAV_SVIATOK_SCSC						51
#define LOKAL_SLAV_SPOMIENKA_OFM_SLAVNOST_CONCEPT	52
#define LOKAL_SLAV_SZOMBATHELYI_EGYH				53
#define LOKAL_SLAV_NAGYSZ_PATRON					54
#define LOKAL_SLAV_NITRA_HU							55
#define LOKAL_SLAV_SVIATOK_FMA_HU					56
#define LOKAL_SLAV_PECSI_EGYH_PATRON				57
#define LOKAL_SLAV_NAGYVARADI_EGYH					58
#define LOKAL_SLAV_VESZPREMI_EGYH_PATRON			59
#define LOKAL_SLAV_GYORI_SZEKESFEH_EGYH				60
#define LOKAL_SLAV_IMRE_EMLEKNAP					61
#define LOKAL_SLAV_KOSICE_HU						62
#define LOKAL_SLAV_KAL_KECS_FOEGYH					63
#define LOKAL_SLAV_KOSICE_FOUNNEP_HU				64
#define LOKAL_SLAV_ARCI_CATHEDRAL_FOUNNEP_HU		65
#define LOKAL_SLAV_BESZTERCEBANYA_EGYH				66
#define LOKAL_SLAV_VACI_PATRON						67
#define LOKAL_SLAV_SZEGED_CSAN_PATRON2				68
#define LOKAL_SLAV_CZ_SCSC							69
#define LOKAL_SLAV_CSSR_SVIATOK						70
#define LOKAL_SLAV_ORDINARIAT_PATRON				71 
#define LOKAL_SLAV_PECS_PATRON						72
#define LOKAL_SLAV_SZOMBATHELYI_PATRON				73
#define LOKAL_SLAV_OFMCAP							74
#define LOKAL_SLAV_EGER_FOEGYH						75
#define LOKAL_SLAV_ESZTERGOM_EML					76
#define LOKAL_SLAV_GYOR_EGYH						77
#define LOKAL_SLAV_ESZTERGOM_FOEGYH					78
#define LOKAL_SLAV_BAZILIKA_ARCI_FOUNNEP_HU			79
#define LOKAL_SLAV_VESZPREM_FOEGYH_T				80
#define LOKAL_SLAV_SZATMAR							81
#define LOKAL_SLAV_CESKO_BRNO						82
#define LOKAL_SLAV_SVIATOK_OP_ZENY					83
#define LOKAL_SLAV_ZILINA							84
#define LOKAL_SLAV_OPRAEM_SVIATOK_STRAHOV			85
#define LOKAL_SLAV_OPRAEM_SLAVNOST_TEPLA			86
#define LOKAL_SLAV_OPRAEM_NOVA_RISE					87
#define LOKAL_SLAV_OPRAEM_STRAHOV_NOVA_RISE			88
#define LOKAL_SLAV_OPRAEM_ZELIV						89
#define LOKAL_SLAV_OPRAEM_STRAHOV					90
#define LOKAL_SLAV_SZ_LASZLO						91
#define LOKAL_SLAV_SLAVNOST_OSC						92
#define LOKAL_SLAV_SVIATOK_OFMCONV					93
#define LOKAL_SLAV_SVIATOK_OFS						94
#define LOKAL_SLAV_SPOMIENKA_OFMCONV_OFMCAP			95
#define LOKAL_SLAV_SPOMIENKA_OSC					96
#define LOKAL_SLAV_NEDOVOLENE_SK					97
#define LOKAL_SLAV_KATONAI_ORDINARIAT				98
#define LOKAL_SLAV_ESZTERGOM_BUD_FOEGYH				99
#define LOKAL_SLAV_OPRAEM_DOKSANY					100
#define LOKAL_SLAV_OPRAEM_DOKSANY_ZELIV				101
#define LOKAL_SLAV_OPRAEM_TEPLA						102
#define LOKAL_SLAV_KONGREGACIA_SMBM					103 // not used
#define LOKAL_SLAV_SPOMIENKA_FMA_CZ					104
#define LOKAL_SLAV_LUB_SPOMIENKA_FMA_VDB_CZ			105
#define LOKAL_SLAV_SVIATOK_VDB_CZ					106
#define LOKAL_SLAV_SLAVNOST_FMA_CZ					107
#define LOKAL_SLAV_SZEGED_CSAN_EGYH3				108
#define LOKAL_SLAV_ORDINARIAT						109
#define LOKAL_SLAV_HU_KLARISSZAKNAL_EM				110
#define LOKAL_SLAV_HU_KLARISSZAKNAL_FOU				111
#define LOKAL_SLAV_LEN_MORAVA						112
#define LOKAL_SLAV_LEN_CECHY						113
#define LOKAL_SLAV_HU_CONCEPTIONISTAK_UN			114
#define LOKAL_SLAV_OCD_BOSE_KARMEL_SPOM				115 // not used
#define LOKAL_SLAV_SLAVNOST_SDB_CZ					116
#define LOKAL_SLAV_SPOMIENKA_CM_PARIZ				117
#define LOKAL_SLAV_VICEB_SPOMIENKA					118
#define LOKAL_SLAV_POSV_K_CH_MINSK					119
#define LOKAL_SLAV_POSV_K_CH_PINSK					120
#define LOKAL_SLAV_PINSK_MINSK						121
#define LOKAL_SLAV_HRADEC_KRALOVE_SLAVNOST			122
#define LOKAL_SLAV_CESKE_BUDEJOV_SLAVNOST			123
#define LOKAL_SLAV_GRODZENSK						124
#define LOKAL_SLAV_MINSK_MAG_VICEB					125
#define LOKAL_SLAV_MINSK_SPOMIENKA					126
#define LOKAL_SLAV_GRODZENSK_SVIATOK				127
#define LOKAL_SLAV_MINSK_PINSK_GRODZENSK			128
#define LOKAL_SLAV_VICEB							129
#define LOKAL_SLAV_MINSK_PINSK_SPOMIENKA			130
#define LOKAL_SLAV_VICEB_SL_MINSK_PINSK_SV			131
#define LOKAL_SLAV_GRODZ_SL_PINSK_MINSK_SP			132
#define LOKAL_SLAV_PRAHA_OFM						133
#define LOKAL_SLAV_OP_MNISKY_PAMATKA				134 // not used
#define LOKAL_SLAV_SPOMIENKA_OFS					135
#define LOKAL_SLAV_SLAVNOST_FMA_HU					136
#define LOKAL_SLAV_SPOMIENKA_FMA_HU					137
#define LOKAL_SLAV_LUB_SPOMIENKA_FMA_VDB_HU			138
#define LOKAL_SLAV_SVIATOK_VDB_HU					139
#define LOKAL_SLAV_SPOMIENKA_POZSONYI_HU			140
#define LOKAL_SLAV_CATHERDAL_SLAVNOST_HU			141
#define LOKAL_SLAV_SZABADKAI_SLAVNOST_HU			142
#define LOKAL_SLAV_ESZTERGOM_BUD_SZLOVAK			143
#define LOKAL_SLAV_SZOMBATHELYI_PANNONHALMI			144
#define LOKAL_SLAV_MURASZOMBATI_SZLOVAKIA			145
#define LOKAL_SLAV_PANNONHALMA_HU					146
#define LOKAL_SLAV_NITRA_FOUNNEP_HU					147
#define LOKAL_SLAV_SZLOVAKIA_HU						148
#define LOKAL_SLAV_BAZILIKA_FOUNNEP_HU				149

// calendar
#define KALENDAR_NEURCENY                   0 // undefined
#define KALENDAR_VSEOBECNY                  1 // general Roman calendar
#define KALENDAR_VSEOBECNY_SK               2
#define KALENDAR_VSEOBECNY_CZ               3
#define KALENDAR_CZ_OP                      4
#define KALENDAR_SK_CSSR                    5
#define KALENDAR_VSEOBECNY_HU               6
#define KALENDAR_SK_SVD                     7
#define KALENDAR_SK_SJ                      8
#define KALENDAR_SK_SDB                     9
#define KALENDAR_SK_OFM                    10
#define KALENDAR_SK_OP                     11
#define KALENDAR_SK_CM                     12
#define KALENDAR_CZ_OPRAEM                 13
#define KALENDAR_CZ_OFMCAP                 14
#define KALENDAR_CZ_CSSR                   15
#define KALENDAR_CZ_SDB                    16
#define KALENDAR_VSEOBECNY_RU              17
#define KALENDAR_HU_OFM                    18
#define KALENDAR_SK_OCD                    19
#define KALENDAR_HU_SVD                    20
#define KALENDAR_VSEOBECNY_BY              21
#define KALENDAR_CZ_OFM                    22
#define KALENDAR_SK_CSA                    23
#define KALENDAR_SK_OSU                    24
#define KALENDAR_HU_SJ                     25
#define KALENDAR_VSEOBECNY_IS              26
#define KALENDAR_CZ_SJ                     27
#define KALENDAR_CZ_OCD                    28
#define KALENDAR_CZ_OFMCONV                29
#define KALENDAR_SK_OPRAEM                 30
#define KALENDAR_HU_SDB                    31
#define KALENDAR_SK_SCHP                   32
#define KALENDAR_HU_SCHP                   33
#define KALENDAR_CZ_OCARM                  34
#define KALENDAR_VSEOBECNY_ES              35
#define KALENDAR_VSEOBECNY_AZ              36

/* INCREMENT_FOR_NEW_CALENDAR */
#define POCET_KALENDAROV                   36
// when adding new calendar, the following comments MUST BE replaced:
// 
// few numeric/string constants [ADD_VALUE_FOR_NEW_CALENDAR]
//
// Note: always preserve "/* ADD_VALUE_FOR_NEW_CALENDAR */" (with preceding comma respectively)!

// default calendar for language (general)
const short int default_kalendar[POCET_JAZYKOV + 1] =
{
	KALENDAR_VSEOBECNY_SK,
	KALENDAR_VSEOBECNY_CZ,
	/* ToDo */ KALENDAR_VSEOBECNY,
	KALENDAR_VSEOBECNY, /* general Latin calendar */
	KALENDAR_NEURCENY,
	KALENDAR_VSEOBECNY_CZ,
	KALENDAR_VSEOBECNY_HU,
	KALENDAR_VSEOBECNY_RU,
	KALENDAR_VSEOBECNY_BY,
	KALENDAR_VSEOBECNY_IS,
	KALENDAR_VSEOBECNY_ES,
	KALENDAR_VSEOBECNY_AZ,
	/* ADD_VALUE_FOR_NEW_LANGUAGE */
};

// filenames for special calendars / názov súbora pre kalendáre
extern const char* nazov_htm_kalendar[POCET_KALENDAROV + 1];

extern const char* nazov_kalendara_smart[POCET_KALENDAROV + 1];

extern const char* nazov_kalendara_long[POCET_KALENDAROV + 1];

#if defined(OS_Windows_Ruby) || defined(IO_ANDROID)
#define nazov_kalendara_vyber nazov_kalendara_smart
#else
#define nazov_kalendara_vyber nazov_kalendara_long
#endif

const short int supported_languages[POCET_JAZYKOV + 1] =
{
	1, // JAZYK_SK
	1, // JAZYK_CZ
	0, // JAZYK_EN
	1, // JAZYK_LA
	0, // JAZYK_UNDEF
	1, // JAZYK_CZ_OP
	1, // JAZYK_HU
	0, // JAZYK_RU
	0, // JAZYK_BY
	1, // JAZYK_IS
#if defined(DEBUG) || defined(OS_Windows_Ruby)
	1, // JAZYK_ES
	1, // JAZYK_AZ
#else
	0, // JAZYK_ES
	0, // JAZYK_AZ
#endif
	/* ADD_VALUE_FOR_NEW_LANGUAGE */
};

#define SUPPORTED_CALENDARS_COUNT_MAX 13

// count of supported calendars for specified language
// note 1: KALENDAR_NEURCENY & KALENDAR_VSEOBECNY are always supported by default so these two do not count there
// note 2: for calendars not yet published use '#if defined(DEBUG) || defined(OS_Windows_Ruby)' == code to be executed only for development (new calendars are added at the end of list supported_calendars_language[][])
// note 3: ADD_VALUE_FOR_NEW_CALENDAR: change the number of supported calendars in proper language
const short int supported_calendars_count[POCET_JAZYKOV + 1] =
{
	13, // JAZYK_SK
#if defined(DEBUG) || defined(OS_Windows_Ruby)
	10, // JAZYK_CZ
#else
	9, // JAZYK_CZ
#endif
	/* ToDo */ 1, // JAZYK_EN
	/* ToDo */ 1, // JAZYK_LA
	/* ToDo */ 1, // JAZYK_UNDEF
	1, // JAZYK_CZ_OP
	6, // JAZYK_HU
	1, // JAZYK_RU
	1, // JAZYK_BY
	1, // JAZYK_IS
	1, // JAZYK_ES
	1, // JAZYK_AZ
	/* ADD_VALUE_FOR_NEW_LANGUAGE */
};

// array of supported calendars for specified language | note: pad with zeros | /* ADD_VALUE_FOR_NEW_CALENDAR */ for specified language
const short int supported_calendars_language[POCET_JAZYKOV + 1][SUPPORTED_CALENDARS_COUNT_MAX] =
{
	{ KALENDAR_VSEOBECNY_SK, KALENDAR_SK_CSSR, KALENDAR_SK_SVD, KALENDAR_SK_OFM, KALENDAR_SK_SDB, KALENDAR_SK_OP, KALENDAR_SK_SJ, KALENDAR_SK_CM, KALENDAR_SK_OCD, KALENDAR_SK_CSA, KALENDAR_SK_OSU, KALENDAR_SK_OPRAEM, KALENDAR_SK_SCHP },
	{ KALENDAR_VSEOBECNY_CZ, KALENDAR_CZ_OPRAEM, KALENDAR_CZ_OFMCAP, KALENDAR_CZ_SDB, KALENDAR_CZ_OFM, KALENDAR_CZ_SJ, KALENDAR_CZ_OCD, KALENDAR_CZ_OFMCONV, KALENDAR_CZ_OCARM, KALENDAR_CZ_CSSR, 0, 0, 0 },
	/* ToDo */ { KALENDAR_VSEOBECNY, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	/* ToDo */ { KALENDAR_VSEOBECNY, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	/* ToDo */ { KALENDAR_VSEOBECNY, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ KALENDAR_CZ_OP, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ KALENDAR_VSEOBECNY_HU, KALENDAR_HU_OFM, KALENDAR_HU_SVD, KALENDAR_HU_SJ, KALENDAR_HU_SDB, KALENDAR_HU_SCHP, 0, 0, 0, 0, 0, 0, 0 },
	{ KALENDAR_VSEOBECNY_RU, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ KALENDAR_VSEOBECNY_BY, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ KALENDAR_VSEOBECNY_IS, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ KALENDAR_VSEOBECNY_ES, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ KALENDAR_VSEOBECNY_AZ, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	/* ADD_VALUE_FOR_NEW_LANGUAGE */
};

#define supported_calendars(a)	supported_calendars_language[_global_jazyk][a]

// flags
#define FLAG_NONE							0
#define FLAG_COLLECTA_1ST_VESP_DIFFERENT	1 // collecta for 1st vespers is different (from the collecta of the day, e. g. vespers, morning prayer etc.)
#define FLAG_COLLECTA_VESP_DIFFERENT		2 // collecta for vespers is different (from the collecta of the day, e. g. morning prayer or prayer with readings etc.); used for CZ OP

// prikazany / neprikazany sviatok / ľubovoľná spomienka bez záväznosti (blahoslavení napr. pre SK_OP)
#define PRIKAZANY_SVIATOK           0
#define NIE_JE_PRIKAZANY_SVIATOK    1
#define VOLNA_LUBOVOLNA_SPOMIENKA   2 // najmä pre OP; v kalendári značené kurzívou (bez popisu "ľubovoľná spomienka"); votívne ofícium

// dodefinované rôzne správanie funkcie zaltar_zvazok();
#define	ZALTAR_VSETKO                0
#define ZALTAR_IBA_ZALMY             1
#define ZALTAR_IBA_ZALMY_HYMNUS_MCD  2
#define ZALTAR_ANT_ZALMY_HYMNUS_MCD  3

// charset constants
#define CHARSET_UTF_8               0
#define CHARSET_WINDOWS_1250        1

#define POCET_CHARSET               1

// character of alphabet
#define ALPHABET_LATIN    0
#define ALPHABET_CYRILLIC 1

#define POCET_ALPHABET    1

// liturgické farby
#define LIT_FARBA_NEURCENA			0
#define LIT_FARBA_CERVENA			1
#define LIT_FARBA_BIELA				2
#define LIT_FARBA_ZELENA			3
#define LIT_FARBA_FIALOVA			4
#define LIT_FARBA_RUZOVA			5
#define LIT_FARBA_CIERNA			6
#define LIT_FARBA_FIALOVA_CIERNA	7 // LIT_FARBA_FIALOVA a LIT_FARBA_CIERNA
#define LIT_FARBA_FIALOVA_BIELA		8 // LIT_FARBA_FIALOVA a LIT_FARBA_BIELA
#define LIT_FARBA_RUZOVA_FIALOVA	9 // LIT_FARBA_RUZOVA a LIT_FARBA_FIALOVA

#define POCET_FARIEB				9
#define POCET_FARIEB_REALNYCH		6

// nazov_farby: string pre názov liturgickej farby
extern const char* nazov_farby_jazyk[POCET_FARIEB_REALNYCH + 1][POCET_JAZYKOV + 1];
#define		nazov_farby(a)	nazov_farby_jazyk[a][_global_jazyk]

extern const char* html_farba_pozadie[POCET_FARIEB_REALNYCH + 1];
extern const char* html_farba_popredie[POCET_FARIEB_REALNYCH + 1];

#define ZVAZKY_LH 4

// tyzden zaltara (1, 2, 3, 4) podla tyzdna t
#define  tyzden_zaltara(t)  ((((t) + 3) % 4) + 1)
extern const char* rimskymi_tyzden_zaltara[ZVAZKY_LH + 2];

extern const short int prvy_den[12];

extern short int pocet_dni[12];

extern const short int alphabet_jayzka[POCET_JAZYKOV + 1];

extern const char char_nedelne_pismeno[POCET_DNI];
extern const char* string_nedelne_pismeno[POCET_ALPHABET + 1][POCET_DNI];

#define POCET_NEDELNY_CYKLUS 3
extern const char char_nedelny_cyklus[POCET_NEDELNY_CYKLUS];
extern const char* string_nedelny_cyklus[POCET_ALPHABET + 1][POCET_NEDELNY_CYKLUS];

#define	POCET_NEDIEL_CEZ_ROK	34
#define	KRISTA_KRALA	34 // 34. nedela v obdobi cez rok je sviatok K.K.

// poradie prva adventna nedela, neprestupny rok!
#define	PRVA_ADVENTNA_NEDELA_b	331

#define	OD_VELKEJ_NOCI_PO_POPOLCOVU_STR		-46
#define OD_VELKEJ_NOCI_PO_NANEBOSTUPENIE	39
#define OD_VELKEJ_NOCI_PO_NANEBOSTUPENIE_NE	42
#define	OD_VELKEJ_NOCI_PO_ZOSLANIE_DUCHA	49

// sposob pisania slov
#define CASE_case 0 // vsetky male
#define CASE_Case 1 // Prve Pismeno Velke
#define CASE_CASE 2 // VSETKO VELKE

extern const char* nazov_dna_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_dna(a)	nazov_dna_jazyk[a][_global_jazyk]

extern const char* nazov_dna_asci_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_dna_asci(a)	nazov_dna_asci_jazyk[a][_global_jazyk]

extern const char* nazov_Dna_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_Dna(a)	nazov_Dna_jazyk[a][_global_jazyk]

extern const char* nazov_Dn_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_Dn(a)	nazov_Dn_jazyk[a][_global_jazyk]

extern const char* nazov_DN_asci[POCET_DNI + 1];
extern const char* nazov_dn_asci[POCET_DNI + 1];

extern const char* nazov_mesiaca_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_mesiaca(a)	nazov_mesiaca_jazyk[a][_global_jazyk]

extern const char* nazov_mesiaca_asci_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_mesiaca_asci(a)	nazov_mesiaca_asci_jazyk[a][_global_jazyk]

extern const char* nazov_Mesiaca_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_Mesiaca(a)	nazov_Mesiaca_jazyk[a][_global_jazyk]

extern const char* nazov_mesiaca_gen_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_mesiaca_gen(a)	nazov_mesiaca_gen_jazyk[a][_global_jazyk]

extern const char* nazov_Mesiaca_gen_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_Mesiaca_gen(a)	nazov_Mesiaca_gen_jazyk[a][_global_jazyk]

extern const char* nazov_MES[POCET_MESIACOV + 1];
extern const char* nazov_mes[POCET_MESIACOV + 1];

#define		POCET_TYZDNOV 34

extern const char* poradie_Slovom_jazyk[POCET_TYZDNOV + 1][POCET_JAZYKOV + 1];
#define		poradie_Slovom(a)	poradie_Slovom_jazyk[a][_global_jazyk]

#define POCET_ALIASOV          7
// sucast struktury lrok, indexy
#define idx_KRST_KRISTA_PANA       0
#define idx_POPOLCOVA_STREDA       1
#define idx_VELKONOCNA_NEDELA      2
#define idx_NANEBOVSTUPENIE_PANA   3
#define idx_ZOSLANIE_DUCHA_SV      4
#define idx_PRVA_ADVENTNA_NEDELA   5
#define idx_SVATEJ_RODINY          6

// sucast struktury lrok, aliasy
#define _KRST_KRISTA_PANA         _den[idx_KRST_KRISTA_PANA]
#define _POPOLCOVA_STREDA         _den[idx_POPOLCOVA_STREDA]
#define _VELKONOCNA_NEDELA        _den[idx_VELKONOCNA_NEDELA]
#define _NANEBOVSTUPENIE_PANA     _den[idx_NANEBOVSTUPENIE_PANA]
#define _PRVA_ADVENTNA_NEDELA     _den[idx_PRVA_ADVENTNA_NEDELA]
#define _ZOSLANIE_DUCHA_SV        _den[idx_ZOSLANIE_DUCHA_SV]
#define _SVATEJ_RODINY            _den[idx_SVATEJ_RODINY]


#define NIJAKE_NEDELNE_PISMENO 'x'
struct lrok{
	short int prestupny;  // ci je rok prestupny (YES, NO)
	char p1, p2;          // nedelne pismeno/pismena; ak ma rok iba jedno, druhe p2 == NIJAKE_NEDELNE_PISMENO
	char litrok;          // pismeno liturgickeho roka, ktory zacina prvou adventnou nedelou v roku
	short int tyzden_ocr_po_vn; // cislo tyzdna obdobia "cez rok", ktory nasleduje po nedeli zoslania ducha svateho, teda po velkonocnom obdobi
	short int tyzden_ocr_pred_po; // cislo tyzdna obdobia cez rok, v ktorom zacina post
	struct dm _den[POCET_ALIASOV];
};
typedef struct lrok _struct_lrok;

#define LINK_DEN_MESIAC_NIE 0
#define LINK_DEN_MESIAC_ROK 1
#define LINK_DEN_MESIAC 3
#define LINK_DEN 2
#define LINK_DEN_MESIAC_ROK_PRESTUP 4
#define LINK_ISO_8601 5 // pridana kvoli SIMPLE exportu
#define LINK_DEN_MESIAC_PREDOSLY 6
#define LINK_DEN_MESIAC_NASLEDOVNY 7
#define LINK_DEN_MESIAC_GEN 8 // the same as LINK_DEN_MESIAC but the month name is in genitive form
#define LINK_DEN_MESIAC_ROK_GEN 9 // the same as LINK_DEN_MESIAC_ROK but the month name is in genitive form

#define LINK_SHIFT 50 // shift added to base LINK constant

//---------------------------------------------------------------------
// global variables

// globalna premenna, do ktorej sa ukladaju info o analyzovanom dni
extern _struct_dm *_global_den_ptr;
#define _global_den (*_global_den_ptr)

// globalna premenna, ktora obsahuje data o spomienke panny marie v sobotu
extern _struct_dm *_global_pm_sobota_ptr;
#define _global_pm_sobota (*_global_pm_sobota_ptr)

// globalne premenne, do ktorych sa ukladaju info o analyzovanom dni o sviatkoch svatych
extern _struct_dm* _global_svaty_ptr[MAX_POCET_SVATY]; // an array of '_struct_dm' pointers
#define _global_svaty(i) (*(_global_svaty_ptr[i - 1]))

// globalne premenne obsahujuce data modlitbach

extern _type_1vespery     *_global_modl_prve_vespery_ptr;
#define _global_modl_prve_vespery (*_global_modl_prve_vespery_ptr)

extern _type_1kompletorium *_global_modl_1kompletorium_ptr;
#define _global_modl_prve_kompletorium (*_global_modl_1kompletorium_ptr)

extern _type_invitatorium *_global_modl_invitatorium_ptr;
#define _global_modl_invitatorium (*_global_modl_invitatorium_ptr)

extern _type_posv_citanie *_global_modl_posv_citanie_ptr;
#define _global_modl_posv_citanie (*_global_modl_posv_citanie_ptr)

extern _type_ranne_chvaly *_global_modl_ranne_chvaly_ptr;
#define _global_modl_ranne_chvaly (*_global_modl_ranne_chvaly_ptr)

extern _type_cez_den_9     *_global_modl_cez_den_9_ptr;
#define _global_modl_cez_den_9 (*_global_modl_cez_den_9_ptr)
extern _type_cez_den_12     *_global_modl_cez_den_12_ptr;
#define _global_modl_cez_den_12 (*_global_modl_cez_den_12_ptr)
extern _type_cez_den_3     *_global_modl_cez_den_3_ptr;
#define _global_modl_cez_den_3 (*_global_modl_cez_den_3_ptr)

#define _global_modl_predpol  _global_modl_cez_den_9
#define _global_modl_napol    _global_modl_cez_den_12
#define _global_modl_popol    _global_modl_cez_den_3

extern _type_vespery      *_global_modl_vespery_ptr;
#define _global_modl_vespery (*_global_modl_vespery_ptr)

extern _type_kompletorium *_global_modl_kompletorium_ptr;
#define _global_modl_kompletorium (*_global_modl_kompletorium_ptr)

extern _struct_anchor_and_file *_global_include_static_text_ptr;
#define _global_include_static_text (*_global_include_static_text_ptr)

// globalna premenna, ktora obsahuje MODL_...
extern short int _global_modlitba;

// globalna premenna, do ktorej ukladaju funkcie vytvor_query_string_... linku tvaru SCRIPT_PATH(SCRIPT_NAME) ++ "?param1=val&param2=val&..."
extern char *_global_link_ptr;
#define _global_link _global_link_ptr

extern char *_global_pom_str; // pomocny string pre velke/male pismena (konverzie)

// globalna premenna, do ktorej sa ukladaju info o jednotlivych vyznacnych liturgickych dni, pouzivaju void _dm_...() funkcie a void analyzuj_rok() funkcia
extern _struct_dm *_global_result_ptr;
#define _global_result (*_global_result_ptr)

// globalna premenna, do ktorej sa uklada info o liturgickom roku pouziva void analyzuj_rok() funkcia
extern _struct_lrok *_global_r_ptr;
#define _global_r (*_global_r_ptr)

// globalna premenna, do ktorej sviatky_svatych() uklada pocet sviatkov (de facto lubovolnych spomienok), ktore pripadaju na dany den
// -- v podstate neuklada do nej, ale v _rozbor_dna() sa do nej priradi vysledok (navratova hodnota) z sviatky_svatych()
extern short int _global_pocet_svatych;

#define OPT_0_SPECIALNE            0
#define OPT_1_CASTI_MODLITBY       1
#define OPT_2_HTML_EXPORT          2
#define OPT_3_SPOLOCNA_CAST        3
#define OPT_4_OFFLINE_EXPORT       4
#define OPT_5_ALTERNATIVES         5
#define OPT_6_ALTERNATIVES_MULTI   6

// globálna premenná -- pole -- obsahujúca options; pôvodne to boli globálne premenné _global_opt 1..9 atď., obsahujú pom_OPT...
extern unsigned long long _global_opt[POCET_GLOBAL_OPT];
// globálna premenná -- pole -- obsahujúca force options; pôvodne to boli globálne premenné _global_force_opt 1..9 atď., obsahujú pom_FORCE_OPT...
extern unsigned long long _global_force_opt[POCET_GLOBAL_OPT];

// for function strcat_str_opt_bit_order()
#define USE_STR_OPT           -2
#define USE_STR_FORCE_OPT     -1

#define POCET_OPT_0_SPECIALNE               21 // jednotlivé komponenty option 0 -- bity pre force option 0
extern unsigned long long _global_opt_0_specialne[POCET_OPT_0_SPECIALNE];
// 2011-04-08: úprava významu (a interpretácie) option 0 ==  OPT_0_SPECIALNE (zobraziť/nezobraziť "pridanú hodnotu" oproti papierovej LH)
#define BIT_OPT_0_VERSE                       1 // export also verse numbers
#define BIT_OPT_0_REFERENCIE                  2 // export Bible references as live URLs (default: proper webpage for given language; override: BIT_OPT_0_REF_BIBLE_COM, use bible.com)
#define BIT_OPT_0_CITANIA                     4 // export also scripture readings for mass
#define BIT_OPT_0_ZJAVENIE_PANA_NEDELA        8 // či sa Zjavenie Pána slávi v nedeľu (1) alebo nie (teda 6. januára; hodnota 0 == default)
#define BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA    16 // či sa Nanebovstúpenie Pána slávi v nedeľu (1) alebo nie (teda vo štvrtok, na 40.-ty deň po Veľkonočnej nedeli; hodnota 0 == default)
#define BIT_OPT_0_TELAKRVI_NEDELA            32 // či sa Najsv. Kristovho tela a krvi slávi v nedeľu (1) alebo nie (teda vo štvrtok, 11.-ty deň po Zoslaní Ducha Sv.; hodnota 0 == default)
#define BIT_OPT_0_FONT_NORMAL                64 // force font-weight: normal; // should be logically among OPT_2_HTML_EXPORT bit-options
#define BIT_OPT_0_BUTTONS_ORDER             128 // buttons order: 0 = date navigation BEFORE info on day (default for web); 1 = day details first (with prayer buttons) (default for mobile apps)
#define BIT_OPT_0_VOICE_OUTPUT              256 // voice-output: 1 = use special CSS override to hide all red texts (rubrics) + display text for speech synthesis + do not display text which should not be heard
#define BIT_OPT_0_FOOTNOTES                 512 // display footnotes and footnote references
#define BIT_OPT_0_TRANSPARENT_NAV          1024 // transparent navigation arrow in text; default: on the right side of the screen (right-handed)
#define BIT_OPT_0_ZALMY_FULL_TEXT          2048 // display full text of psalms (also with carets from official LH edition, e. g. verse 6 in psalm 110)
#define BIT_OPT_0_REF_BIBLE_COM            4096 // precondition: BIT_OPT_0_REFERENCIE must be true; instead of standard URL, generates link to bible.com
#define BIT_OPT_0_ITALICS_CONDITIONAL      8192 // display text in italics (conditional), e. g. elisions
#define BIT_OPT_0_PRINTED_EDITION         16384 // prefer printed edition (instead of corrections in our electronical version) = force usage of printed text
#define BIT_OPT_0_USE_TWO_YEARS_CYCLE     32768 // use two-years' cycle for readings (Biblical, first readings in prayer with readings)
#define BIT_OPT_0_TWO_YEARS_CYCLE_INVERT  65536 // when use two-years' cycle for readings (BIT_OPT_0_TWO_YEARS_CYCLE is set), reverse the usage of 1st/2nd year (default: according to ferial lectionary)
#define BIT_OPT_0_ALTERNATIVE_READINGS   131072 // use alternative second readings in prayer with readings (CZ only)
#define BIT_OPT_0_TRANSPARENT_NAV_LEFT   262144 // transparent navigation arrow in text; override: on the left side of the screen (left-handed)
#define BIT_OPT_0_SIDE_NAVIGATION        524288 // side navigation using JavaScript; for web usage (instead of frames); default location on the left, can be changed via JavaScript
#define BIT_OPT_0_TRANSPARENT_NAV_DOWN_ONLY 1048576 // transparent navigation arrow in text: down arrow only (no up arrow)

#define POCET_OPT_1_CASTI_MODLITBY          20 // jednotlivé komponenty option 1 -- bity pre force option 1
extern unsigned long long _global_opt_1_casti_modlitby[POCET_OPT_1_CASTI_MODLITBY];
// 2011-04-11: úprava významu (a interpretácie) option 1 == OPT_1_CASTI_MODLITBY (zobraziť/nezobraziť najmä pevné/nemenné súčasti modlitieb, ale aj iné, čo sú/nie sú v LH)
// 2011-10-10: úprava niektorých bitov, posunutie popisu na koniec
#define BIT_OPT_1_TEDEUM                     1
#define BIT_OPT_1_RUBRIKY                    2
#define BIT_OPT_1_CHVALOSPEVY                4
#define BIT_OPT_1_SLAVA_OTCU                 8
#define BIT_OPT_1_OTCENAS                   16
#define BIT_OPT_1_MCD_DOPLNKOVA             32 // používa sa pre modlitbu cez deň -- 1 = alternatívna, doplnková psalmódia
#define BIT_OPT_1_PC_VIGILIA                64
#define BIT_OPT_1_SPOMIENKA_SPOL_CAST      128 // pri slávení spomienky možno podľa všeobecných smerníc, č. 235 b), vziať niektoré časti alebo zo spoločnej časti (1), alebo zo dňa (0)
#define BIT_OPT_1_PLNE_RESP                256
#define BIT_OPT_1_ZALM95                   512 // používa sa pre ranné chvály a vešpery -- 1 = vziať namiesto žalmov 24, 67, 100 žalm 95 (0 = brať príslušný žalm 24, 67 resp. 100)
#define BIT_OPT_1_PROSBY_ZVOLANIE         1024 // zvolanie v prosbách zobraziť (opakovať) po každej prosbe
#define BIT_OPT_1_SKRY_POPIS              2048
#define BIT_OPT_1_ZOBRAZ_SPOL_CAST        4096
#define BIT_OPT_1_VESP_KRATSIE_PROSBY     8192 // použiť (pre ktorýkoľvek deň v roku) kratšie prosby k vešperám z dodatku (0 = default, zo dňa)
#define BIT_OPT_1_MCD_ZALTAR_TRI         16384 // používa sa pre modlitbu cez deň -- 1 = psalmódia sa používa z troch týždňov žaltára (aktuálny, predchádzajúci, nasledujúci)
#define BIT_OPT_1_ZAVER                  32768 // prayer conclusions
#define BIT_OPT_1_OVERRIDE_STUP_SLAV     65536 // možnosť zvoliť vyšší stupeň slávenia (spomienku možno sláviť ako sviatok alebo slávnosť; sviatok ako slávnosť)
#define BIT_OPT_1_STUP_SVIATOK_SLAVNOST 131072 // vyšší stupeň slávenia (0 = sviatok, 1 = slávnosť); aplikuje sa iba ak BIT_OPT_1_OVERRIDE_STUP_SLAV je true
#define BIT_OPT_1_KOMPL_MARIA_ANT       262144 // pre kompletórium: či zobraziť mariánsku antifónu (jednu, ak BIT_OPT_2_ALTERNATIVES == 1)/mariánske antifóny na konci kompletória
#define BIT_OPT_1_ZOBRAZ_OTCENAS_UVOD   524288 // pre ranné chvály a vešpery: či zobraziť úvod k modlitbe Pána (Otčenás)

#define POCET_OPT_2_HTML_EXPORT             17 // jednotlivé komponenty option 2 -- bity pre force option 2
extern unsigned long long _global_opt_2_html_export[POCET_OPT_2_HTML_EXPORT];
// 2011-04-12: úprava významu (a interpretácie) option 2 (rozličné prepínače pre [online aj offline] export, napr. tlačidlá, zobrazenie dátumov a podobne)
// 2012-10-01: doplnené ďalšie komponenty najmä pre vzhľad úvodnej obrazovky
#define BIT_OPT_2_ISO_DATUM                  1 // zobrazovať dátum v ISO formáte YYYY-MM-DD (0 = iba číslo dňa)
#define BIT_OPT_2_BUTTON_PRVE_VESPERY        2 // zobrazovať prvé vešpery (a kompletórium po nich) pre ten deň, pre ktorý patria (teda pre nedeľu/slávnosť)
#define BIT_OPT_2_FONT_FAMILY                4 // 0 = Serif, 1 = Sans Serif
#define BIT_OPT_2_FONT_NAME_CHOOSER          8 // zobraziť drop-down list s možnosťou voľby font (family) name
#define BIT_OPT_2_FONT_SIZE_CHOOSER         16 // zobraziť drop-down list s možnosťou voľby veľkosti fontu
#define BIT_OPT_2_NAVIGATION                32 // zobraziť navigáciu v modlitbe (tlačidlá pre ranné chvály, vešpery a pod.) | navigation buttons in prayer text (iOS: never display; OFF); contains prayer buttons (laudes, vespers, etc.) + date/month/year navigation (in prayer text, prev/next/this day + today only)
#define BIT_OPT_2_TEXT_WRAP                 64 // zobraziť zalomenie v textoch modlitby podľa tlačenej LH
#define BIT_OPT_2_BUTTONY_USPORNE          128 // zobraziť buttony pre modlitby v úspornej podobe (tabuľka) kvôli mobilným zariadeniam
#define BIT_OPT_2_NOCNY_REZIM              256 // zobraziť invertovane farby (biele na ciernom)
#define BIT_OPT_2_ROZNE_MOZNOSTI           512 // zobraziť rozličné "hypertextové odkazy" v modlitbe (napr. pre modlitbu cez deň možnosť doplnkovej psalmódie)
#define BIT_OPT_2_HIDE_NAVIG_BUTTONS      1024 // možnosť zobraziť/skryť navigáciu (tlačidlá pre deň, mesiac, rok, dnes) v modlitbe a pre "dnes", ak je zvolený 6. bit (BIT_OPT_2_NAVIGATION)
#define BIT_OPT_2_HIDE_KALENDAR           2048 // skryť kalendárik pre "dnes" (0 = zobraziť)
#define BIT_OPT_2_HIDE_OPTIONS1           4096 // skryť html_text_dalsie_moznosti_1[] pre "dnes" (0 = zobraziť)
#define BIT_OPT_2_HIDE_OPTIONS2           8192 // skryť html_text_dalsie_moznosti_2[] pre "dnes" (0 = zobraziť)
#define BIT_OPT_2_ALTERNATIVES           16384 // ukázať iba jednu alternatívu (0 = ako doteraz; buď systém vyberie, alebo ukáže všetky možnosti)
#define BIT_OPT_2_SHOW_DEFAULT_CALENDAR  32768 // ukázať v podnadpise, metódou init_global_string(), aj default regionálny kalendár (0 = po novom, neukazovať; 1 = po starom, ukázať)
#define BIT_OPT_2_ROUNDED_CORNERS        65536 // use rounded corners for buttons in CSS

#define POCET_OPT_4_OFFLINE_EXPORT           4 // jednotlivé komponenty option 4 -- bity pre force option 4
extern unsigned long long _global_opt_4_offline_export[POCET_OPT_4_OFFLINE_EXPORT];
// 2011-04-08: úprava významu (a interpretácie) option 4 (rozličné prepínače pre offline export, napr. aj batch mód)
#define BIT_OPT_4_MESIAC_RIADOK              1 // mesiac jednoducho (default: nie jednoducho, ale HTML pekne pre web) alebo pekne "zložito"
#define BIT_OPT_4_FNAME_MODL_ID              2 // či pre názov súboru použiť (číselné) ID modlitby alebo písmenko modlitby (default)
#define BIT_OPT_4_EXCLUDE_MCD_KOMPLET        4 // či sa pri generovaní tlačidla pre predchádzajúcu/nasledujúcu modlitbu majú preskočiť odkazy na MCD a kompletórium v metóde _buttons_prev_up_next() [default: 0 = nie; treba nastavovať kvôli ľubovoľným spomienkam do batch módu]
#define BIT_OPT_4_DO_NOT_USE_BUTTON          8 // whether do not use HTML_BUTTON_BEGIN..HTML_BUTTON_END for offline HTML export

#define POCET_OPT_5_ALTERNATIVES            20 // jednotlivé komponenty option 5 -- bity pre force option 5
extern unsigned long long _global_opt_5_alternatives[POCET_OPT_5_ALTERNATIVES];
#define BIT_OPT_5_HYMNUS_KOMPL               1 // hymnus na kompletórium (Cezročné obdobie, A/B)
#define BIT_OPT_5_HYMNUS_PC                  2 // hymnus pre posvätné čítanie (Cezročné obdobie, I./II.)
#define BIT_OPT_5_HYMNUS_MCD_PREDPOL         4 // hymnus pre modlitbu cez deň, predpoludním (Cezročné obdobie)
#define BIT_OPT_5_HYMNUS_MCD_NAPOL           8 // hymnus pre modlitbu cez deň, napoludnie (Cezročné obdobie)
#define BIT_OPT_5_HYMNUS_MCD_POPOL          16 // hymnus pre modlitbu cez deň, popoludní (Cezročné obdobie)
#define BIT_OPT_5_DOPLNK_PSALM_122_129      32 // pre modlitbu cez deň v doplnkovej psalmódii namiesto žalmu 122 možno brať žalm 129
#define BIT_OPT_5_DOPLNK_PSALM_127_131      64 // pre modlitbu cez deň v doplnkovej psalmódii namiesto žalmu 127 možno brať žalm 131
#define BIT_OPT_5_DOPLNK_PSALM_126_129     128 // pre modlitbu cez deň v doplnkovej psalmódii namiesto žalmu 126 možno brať žalm 129
#define BIT_OPT_5_HYMNUS_VN_PC             256 // hymnus pre posvätné čítanie (Veľkonočné obdobie I. po Oktáve: nedeľný alebo z férie)
#define BIT_OPT_5_HYMNUS_VN_RCH            512 // hymnus pre ranné chvály (Veľkonočné obdobie I. po Oktáve: nedeľný alebo z férie)
#define BIT_OPT_5_HYMNUS_VN_VESP          1024 // hymnus pre vešpery (Veľkonočné obdobie I. po Oktáve: nedeľný alebo z férie)
#define BIT_OPT_5_HYMNUS_1VESP            2048 // hymnus pre prvé vešpery (Cezročné obdobie: nedeľný alebo z posv. čítania)
#define BIT_OPT_5_POPOL_STREDA_PSALMODIA  4096 // psalmódia pre ranné chvály popolcovej stredy (default: streda 4. týždňa žaltára; možnosť zvoliť z piatka 3. týždňa žaltára)
#define BIT_OPT_5_CZ_HYMNY_VYBER          8192 // CZ: hymny z breviáře ("písničky") nebo k volnému výběru (podle LA, "Renč")
#define BIT_OPT_5_OFF_DEF_PSALM_146_150  16384 // pre ranné chvály ofícia za zosnulých možno brať ako tretí žalm 146 resp. 150
#define BIT_OPT_5_ZAVER_KNAZ_DIAKON      32768 // prayer conclusions for morning and evening prayer: whether take when priest/diacon is present (default: 0, no)
#define BIT_OPT_5_INVITAT_ANT_WRAP_ONLY  65536 // invitatory prayer: the antiphone is NOT repeated; used only at the beginning and at the end (wraps the psalm only from outside)
#define BIT_OPT_5_OCR_34_HYMNS          131072 // different (special) hymns for 34th week per annum
#define BIT_OPT_5_KOMPLETORIUM_OKTAVA   262144 // prvé alebo druhé nedeľné kompletórium (pre Veľkonočnú oktávu a Oktávu Narodenia Pána)
#define BIT_OPT_5_ZELENY_STVRTOK_PSALMODIA  524288 // psalmódia pre posvätné čítanie štvrtka vo Svätom týždni (default: štvrtok 2. týždňa žaltára; možnosť zvoliť z piatka 3. týždňa žaltára)

#define POCET_OPT_6_ALTERNATIVES_MULTI       11 // count equals to the highest PLACE_OPT_6_... used
extern unsigned long long _global_opt_6_alternatives_multi[POCET_OPT_6_ALTERNATIVES_MULTI]; // this is not bitwise long, but simply decimal number; each decimal place representing one value (max. possibly 0--9)
#define PLACE_OPT_6_HYMNUS_MULTI                 1
#define PLACE_OPT_6_PSALM_MULTI                  2 // in fact, only for invitatory
#define PLACE_OPT_6_CITANIE2_MULTI               3
#define PLACE_OPT_6_CITANIE1_MULTI               4
#define PLACE_OPT_6_ANTIFONA_MULTI               5
#define PLACE_OPT_6_MODLITBA_MULTI               6
#define PLACE_OPT_6_PROSBY_MULTI                 7
#define PLACE_OPT_6_MARIA_ANT_MULTI              8
#define PLACE_OPT_6_KRESP_MULTI                  9
#define PLACE_OPT_6_KCIT_RESP_MULTI             10
#define PLACE_OPT_6_OTCENAS_UVOD_MULTI          11

#define BASE_OPT_6_HYMNUS_MULTI                  1
#define BASE_OPT_6_PSALM_MULTI                  10
#define BASE_OPT_6_CITANIE2_MULTI              100
#define BASE_OPT_6_CITANIE1_MULTI             1000
#define BASE_OPT_6_ANTIFONA_MULTI            10000
#define BASE_OPT_6_MODLITBA_MULTI           100000
#define BASE_OPT_6_PROSBY_MULTI            1000000
#define BASE_OPT_6_MARIA_ANT_MULTI        10000000
#define BASE_OPT_6_KRESP_MULTI           100000000
#define BASE_OPT_6_KCIT_RESP_MULTI      1000000000 // when data type was only "long", this note made sense: 'must not contain more than 3 possibilities at position 10 because long is limited to 2147483647'
#define BASE_OPT_6_OTCENAS_UVOD_MULTI  10000000000

#define MAX_POCET_OPT                           22 // must be at least maximum +1 from POCET_OPT_0_... to POCET_OPT_6_...

const short int pocet_opt[POCET_GLOBAL_OPT] = { POCET_OPT_0_SPECIALNE, POCET_OPT_1_CASTI_MODLITBY, POCET_OPT_2_HTML_EXPORT, 0 /* option 3 nemá bitové komponenty */, POCET_OPT_4_OFFLINE_EXPORT, POCET_OPT_5_ALTERNATIVES, POCET_OPT_6_ALTERNATIVES_MULTI /* decimal-places */ };

// globalna premenna, co obsahuje string vypisany na obsazovku
extern char *_global_string;
extern char *_global_string2; // obsahuje I, II, III, IV, V alebo pismeno roka
extern char *_global_string_farba;

extern char *_global_buf;
extern char *_global_buf2;

extern short int _global_linky;

extern short int _global_jazyk;

extern short int _global_kalendar;

extern short int _global_theme;
extern char _global_theme_light_background_color[SMALL]; // used for background color override for light theme
extern char _global_theme_dark_background_color[SMALL]; // used for background color override for dark theme
extern short int _global_sidemenu_location;

extern short int _global_font;
extern short int _global_font_size;
extern short int _global_font_size_pt;

extern short int _global_pocet_zalmov_kompletorium;

extern const char* nazov_jazyka_native_jazyk[POCET_JAZYKOV + 1][POCET_JAZYKOV + 1];
#define nazov_jazyka_native_jazyk(a) nazov_jazyka_native_jazyk[a][_global_jazyk]
#define nazov_jazyka(a) nazov_jazyka_native_jazyk[a][a]
extern const char* skratka_jazyka[POCET_JAZYKOV + 1];
extern const char* postfix_jazyka[POCET_JAZYKOV + 1];
extern const char* skratka_jazyka_title[POCET_JAZYKOV + 1];

extern const char* nazov_kalendara_short[POCET_KALENDAROV + 1];
extern const char* skratka_kalendara[POCET_KALENDAROV + 1];
extern const char* nazov_kalendara_propria_only[POCET_KALENDAROV + 1];
extern const char* nazov_kalendara_long[POCET_KALENDAROV + 1];

extern const char* nazov_css_default;
extern const char* nazov_css_invert_colors;
extern const char* nazov_css_normal_font_weight;
extern const char* nazov_css_voice_output;
extern const char* nazov_css_rounded_corners;

extern const char* html_lang_jazyka[POCET_JAZYKOV + 1];

extern const char* nazov_fontu[POCET_FONTOV + 1];
extern const char* nazov_fontu_CHECKBOX[POCET_JAZYKOV + 1];
extern const char* nazov_fontu_CSS[POCET_JAZYKOV + 1];

extern const char* nazov_font_size_jazyk[POCET_FONT_SIZE + 1][POCET_JAZYKOV + 1];
extern const char* nazov_font_size_css[POCET_FONT_SIZE + 1];

//---------------------------------------------------------------------

short int _allocate_global_var(void);
short int _deallocate_global_var(void);

short int cislo_mesiaca(char *mesiac);
extern char *mystr_UPPERCASE(const char* input);
extern char *mystr_remove_diacritics(const char* input);
char *mystr_bible_com(const char* input);
extern char *convert_nonbreaking_spaces(const char* input);

char *_vytvor_string_z_datumu_ext(short int den, short int mesiac, short int rok, short int _case, short int align);
char *_vytvor_string_z_datumu_ext(short int den, short int mesiac, short int rok, short int _case, short int align, short int force_month_numbers);
char *_vytvor_string_z_datumu(short int den, short int mesiac, short int rok, short int _case, short int typ, short int align);
char *_vytvor_string_z_datumu(short int den, short int mesiac, short int rok, short int _case, short int typ, short int align, short int force_month_numbers);

// podľa toho, ako sa funkcia volá, určím case (použitie veľkých/malých písmen)
#define vytvor_global_link(den, mesiac, rok, typ, align)	_vytvor_global_link(den, mesiac, rok, CASE_case, typ, align)
#define Vytvor_global_link(den, mesiac, rok, typ, align)	_vytvor_global_link(den, mesiac, rok, CASE_Case, typ, align)

#define vytvor_global_link_class_new(den, mesiac, rok, typ, align, html_class, nazov_dna)	_vytvor_global_link(den, mesiac, rok, CASE_case, typ + LINK_SHIFT, align, html_class, nazov_dna)
#define vytvor_global_link_class(den, mesiac, rok, typ, align, html_class)	_vytvor_global_link(den, mesiac, rok, CASE_case, typ, align, html_class)
#define Vytvor_global_link_class(den, mesiac, rok, typ, align, html_class)	_vytvor_global_link(den, mesiac, rok, CASE_Case, typ, align, html_class)

// parameter align -- či zarovnať jednociferné dátumy (číslovka dňa) medzerou zľava
void _vytvor_global_link(short int den, short int mesiac, short int rok, short int _case, short int typ, short int align);
void _vytvor_global_link(short int den, short int mesiac, short int rok, short int _case, short int typ, short int align, const char* html_class);
void _vytvor_global_link(short int den, short int mesiac, short int rok, short int _case, short int typ, short int align, const char* html_class, const char* nazov_dna);

#define PRILEP_REQUEST_OPTIONS_DEFAULT   0
#define PRILEP_REQUEST_OPTIONS_AJ_FORCE  1
#define PRILEP_REQUEST_OPTIONS_LEN_FORCE 2
void prilep_request_options(char pom2 [MAX_STR], char pom3 [MAX_STR], short int special_handling = 0, short int force_opt = PRILEP_REQUEST_OPTIONS_DEFAULT);

short int prestupny(short int);
short int pocet_dni_v_roku(short int);
short int poradie(short int den, short int mesiac, short int rok);
short int poradie(_struct_den_mesiac den_a_mesiac, short int rok);
short int zjavenie_pana(short int rok);
long juliansky_datum(short int por, short int rok);
long juliansky_datum(short int den, short int mesiac, short int rok);
_struct_den_mesiac velkonocna_nedela(short int R);
short int _velkonocna_nedela(short int rok);
short int den_v_tyzdni(short int por, short int rok);
short int den_v_tyzdni(short int den, short int mesiac, short int rok);
short int den_v_tyzdni(_struct_den_mesiac den_a_mesiac, short int rok);
unsigned char _nedelne_pismeno(short int rok);
char nedelne_pismeno(short int rok);
unsigned char _nedelne_pismeno(short int por, short int rok);
char nedelne_pismeno(short int por, short int rok);
char nedelne_pismeno(short int den, short int mesiac, short int rok);
unsigned char _nedelne_pismeno(short int den, short int mesiac, short int rok);
unsigned char _nedelne_pismeno(_struct_den_mesiac den_a_mesiac, short int rok);
char nedelne_pismeno(_struct_den_mesiac den_a_mesiac, short int rok);
short int index_nedelne_pismeno(char nedelne_pismeno);
short int index_nedelny_cyklus(char nedelny_cyklus);

_struct_den_mesiac por_den_mesiac(short int poradie, short int rok);

short int _zoslanie_ducha(short int rok);
short int _prva_adventna_nedela(short int rok);
_struct_den_mesiac prva_adventna_nedela(short int rok);
short int nedelny_cyklus(short int por, short int rok);
short int nedelny_cyklus(short int den, short int mesiac, short int rok);
short int nedelny_cyklus(_struct_den_mesiac den_a_mesiac, short int rok);
short int ferialny_cyklus(short int por, short int rok);
short int ferialny_cyklus(short int den, short int mesiac, short int rok);
_struct_dm por_den_mesiac_dm(short int poradie, short int rok);
short int tyzden_cez_rok_po_vn(short int rok);
short int cislo_nedele_cez_rok_po_vn(short int rok);

void init_global_pm_sobota(void);

void _dm_popolcova_streda(short int rok, short int _vn);
void _dm_nanebovstupenie(short int rok, short int _vn);
void _dm_zoslanie_ducha(short int rok, short int _vn);
void _dm_prva_adventna_nedela(short int rok, short int p2);
void _dm_svatej_rodiny(short int rok);
void _dm_krst_krista_pana(short int rok);
void _dm_velkonocna_nedela(short int rok, short int _vn);
void _dm_zjavenie_pana(short int rok, short int _zjv);

short int modlitba_predchadzajuca(short int modlitba, short int exclude_mcd_komplet = NIE);
short int modlitba_nasledujuca(short int modlitba, short int exclude_mcd_komplet = NIE);

void analyzuj_rok(short int year);

#define UNKNOWN_PORADIE_SVATEHO 0

// based on method _init_dm() 
#define _INIT_DM(a) {\
	a.den = 1;    \
	a.mesiac = 1; \
	a.rok = 1900; \
	a.denvt = 0;  \
	a.denvr = NULL_DAY_OF_THE_YEAR;  \
	a.litrok = 'A'; \
	a.tyzden = 1;   \
	a.tyzzal = 1;   \
	a.litobd = OBD_CEZ_ROK; \
	a.typslav = SLAV_NEURCENE; \
	a.typslav_lokal = LOKAL_SLAV_NEURCENE; \
	a.smer = 14; \
	a.prik = NIE_JE_PRIKAZANY_SVIATOK; \
	a.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA); \
	mystrcpy(a.meno, STR_UNDEF, MENO_SVIATKU); \
	a.farba = LIT_FARBA_NEURCENA; \
	a.kalendar = KALENDAR_NEURCENY; \
	mystrcpy(a.lc_str_id, STR_EMPTY, MAX_LC_STR_ID); \
	a.flags = FLAG_NONE; \
}

#define _INIT_ANCHOR_AND_FILE(a) {\
	mystrcpy(a.file, STR_UNDEF, MAX_STR_AF_FILE); \
	mystrcpy(a.anchor, STR_UNDEF, MAX_STR_AF_ANCHOR); \
}

#define _INIT_TMODLITBA1(a) {\
	a.alternativy = 0; \
	_INIT_ANCHOR_AND_FILE(a.popis); \
	_INIT_ANCHOR_AND_FILE(a.hymnus); \
	_INIT_ANCHOR_AND_FILE(a.antifona1); \
	_INIT_ANCHOR_AND_FILE(a.zalm1); \
	_INIT_ANCHOR_AND_FILE(a.antifona2); \
	_INIT_ANCHOR_AND_FILE(a.zalm2); \
	_INIT_ANCHOR_AND_FILE(a.antifona3); \
	_INIT_ANCHOR_AND_FILE(a.zalm3); \
	_INIT_ANCHOR_AND_FILE(a.kcitanie); \
	_INIT_ANCHOR_AND_FILE(a.kresponz); \
	_INIT_ANCHOR_AND_FILE(a.benediktus); \
	_INIT_ANCHOR_AND_FILE(a.prosby); \
	_INIT_ANCHOR_AND_FILE(a.modlitba); \
	_INIT_ANCHOR_AND_FILE(a.ant_spomprivileg); \
	_INIT_ANCHOR_AND_FILE(a.modlitba_spomprivileg); \
	_INIT_ANCHOR_AND_FILE(a.otcenas_uvod); \
};

#define _INIT_TMODLITBA2(a) {\
	a.alternativy = 0; \
	_INIT_ANCHOR_AND_FILE(a.popis); \
	_INIT_ANCHOR_AND_FILE(a.hymnus); \
	_INIT_ANCHOR_AND_FILE(a.antifona1); \
	_INIT_ANCHOR_AND_FILE(a.zalm1); \
	_INIT_ANCHOR_AND_FILE(a.antifona2); \
	_INIT_ANCHOR_AND_FILE(a.zalm2); \
	_INIT_ANCHOR_AND_FILE(a.antifona3); \
	_INIT_ANCHOR_AND_FILE(a.zalm3); \
	_INIT_ANCHOR_AND_FILE(a.kcitanie); \
	_INIT_ANCHOR_AND_FILE(a.kresponz); \
	_INIT_ANCHOR_AND_FILE(a.modlitba); \
};

#define _INIT_TMODLITBA3(a) {\
	a.alternativy = 0; \
	a.pocet_zalmov = 1;\
	_INIT_ANCHOR_AND_FILE(a.popis); \
	_INIT_ANCHOR_AND_FILE(a.ukonkaj); \
	_INIT_ANCHOR_AND_FILE(a.hymnus); \
	_INIT_ANCHOR_AND_FILE(a.antifona1); \
	_INIT_ANCHOR_AND_FILE(a.zalm1); \
	_INIT_ANCHOR_AND_FILE(a.antifona2); \
	_INIT_ANCHOR_AND_FILE(a.zalm2); \
	_INIT_ANCHOR_AND_FILE(a.kcitanie); \
	_INIT_ANCHOR_AND_FILE(a.kresponz); \
	_INIT_ANCHOR_AND_FILE(a.nunc_dimittis); \
	_INIT_ANCHOR_AND_FILE(a.modlitba); \
	_INIT_ANCHOR_AND_FILE(a.maria_ant); \
};

#define _INIT_TMODLITBA4(a) {\
	a.alternativy = 0; \
	_INIT_ANCHOR_AND_FILE(a.popis); \
	_INIT_ANCHOR_AND_FILE(a.antifona1); \
	_INIT_ANCHOR_AND_FILE(a.zalm1); \
};

#define _INIT_TMODLITBA5(a) {\
	a.alternativy = 0; \
	_INIT_ANCHOR_AND_FILE(a.popis); \
	_INIT_ANCHOR_AND_FILE(a.hymnus); \
	_INIT_ANCHOR_AND_FILE(a.antifona1); \
	_INIT_ANCHOR_AND_FILE(a.zalm1); \
	_INIT_ANCHOR_AND_FILE(a.antifona2); \
	_INIT_ANCHOR_AND_FILE(a.zalm2); \
	_INIT_ANCHOR_AND_FILE(a.antifona3); \
	_INIT_ANCHOR_AND_FILE(a.zalm3); \
	_INIT_ANCHOR_AND_FILE(a.kresponz); \
	_INIT_ANCHOR_AND_FILE(a.citanie1); \
	_INIT_ANCHOR_AND_FILE(a.citanie2); \
	_INIT_ANCHOR_AND_FILE(a.citanie_spomprivileg); \
	_INIT_ANCHOR_AND_FILE(a.ant_chval); \
	_INIT_ANCHOR_AND_FILE(a.chval1); \
	_INIT_ANCHOR_AND_FILE(a.chval2); \
	_INIT_ANCHOR_AND_FILE(a.chval3); \
	_INIT_ANCHOR_AND_FILE(a.evanjelium); \
	_INIT_ANCHOR_AND_FILE(a.modlitba); \
};

#define Log_struktura_dm Log("  <dm>"); Log
void Log(_struct_dm g);
#define Log_struktura_rok Log("  <rok>"); Log
void Log(_struct_lrok r);
#define Log_struktura_tm1 Log("  <tm1>"); Log
void Log(struct tmodlitba1);
#define Log_struktura_tm2 Log("  <tm2>"); Log
void Log(struct tmodlitba2);
#define Log_struktura_tm3 Log("  <tm3>"); Log
void Log(struct tmodlitba3);
#define Log_struktura_tm4 Log("  <tm4>"); Log
void Log(struct tmodlitba4);
#define Log_struktura_tm5 Log("  <tm5>"); Log
void Log(struct tmodlitba5);

extern void Log_filename_anchor(_struct_anchor_and_file af);

void _set_slavenie_typslav_smer(short int poradie, short int typslav, short int smer);

int _encode_spol_cast(short int, short int, short int);
int _encode_spol_cast(short int, short int);
int _encode_spol_cast(short int);
_struct_sc _decode_spol_cast(int);

void strcat_str_opt_bit_order(char str_to_append[SMALL], short opt, short bit_order);

extern const char* text_JAN_06[POCET_JAZYKOV + 1];
extern const char* text_JAN_KRST[POCET_JAZYKOV + 1];
extern const char* text_POPOLCOVA_STREDA[POCET_JAZYKOV + 1];
extern const char* text_NANEBOVSTUPENIE_PANA[POCET_JAZYKOV + 1];
extern const char* text_VELKONOCNA_NEDELA[POCET_JAZYKOV + 1];
extern const char* text_NEDELA_PANOVHO_ZMRTVYCHVSTANIA[POCET_JAZYKOV + 1];
extern const char* text_NEDELA_VO_VELKONOCNEJ_OKTAVE[POCET_JAZYKOV + 1];
extern const char* text_DEN_VO_VELKONOCNEJ_OKTAVE[POCET_JAZYKOV + 1];
extern const char* text_NAJSVATEJSEJ_TROJICE[POCET_JAZYKOV + 1];
extern const char* text_KRISTA_KRALA[POCET_JAZYKOV + 1];
extern const char* text_NAJSV_KRISTOVHO_TELA_A_KRVI[POCET_JAZYKOV + 1];
extern const char* text_NAJSV_SRDCA_JEZISOVHO[POCET_JAZYKOV + 1];
extern const char* text_MARIE_MATKY_CIRKVI[POCET_JAZYKOV + 1];
extern const char* text_NEPOSKVRNENEHO_SRDCA_PM[POCET_JAZYKOV + 1];
extern const char* text_NARODENIE_PANA[POCET_JAZYKOV + 1];
extern const char* text_ZOSLANIE_DUCHA_SVATEHO[POCET_JAZYKOV + 1];
extern const char* text_PRVA_ADVENTNA_NEDELA[POCET_JAZYKOV + 1];
extern const char* text_NEDELA_SV_RODINY[POCET_JAZYKOV + 1];
extern const char* text_SPOMIENKA_PM_V_SOBOTU[POCET_JAZYKOV + 1];
extern const char* text_ZELENY_STVRTOK[POCET_JAZYKOV + 1];
extern const char* text_ZELENY_STVRTOK_VESPERY[POCET_JAZYKOV + 1];
extern const char* text_VELKY_PIATOK[POCET_JAZYKOV + 1];
extern const char* text_BIELA_SOBOTA[POCET_JAZYKOV + 1];
extern const char* text_KVETNA_NEDELA[POCET_JAZYKOV + 1];
extern const char* text_DRUHA_NEDELA_PO_NAR_PANA[POCET_JAZYKOV + 1];
extern const char* text_PO_POPOLCOVEJ_STREDE[POCET_JAZYKOV + 1];
extern const char* text_V_OKTAVE_NARODENIA[POCET_JAZYKOV + 1];

extern const char* text_DEC_08[POCET_JAZYKOV + 1];
extern const char* text_AUG_15[POCET_JAZYKOV + 1];
extern const char* text_NOV_01[POCET_JAZYKOV + 1];

extern short int lokal_slav_slavnost_fma[POCET_JAZYKOV + 1];
extern short int lokal_slav_sviatok_fma[POCET_JAZYKOV + 1];
extern short int lokal_slav_spomienka_fma[POCET_JAZYKOV + 1];
extern short int lokal_slav_lub_spomienka_fma_vdb[POCET_JAZYKOV + 1];
extern short int lokal_slav_sviatok_vdb[POCET_JAZYKOV + 1];

extern const char* html_text_batch_Back[POCET_JAZYKOV + 1];

struct _lang_anchor_and_count {
	short int language;
	char anchor[MAX_STR_AF_ANCHOR];
	short int count;
};
typedef struct _lang_anchor_and_count _struct_lang_anchor_and_count;

struct _lang_cal_type_anchor_and_count {
	short int language;
	short int calendar;
	unsigned long long type; // e. g. BASE_OPT_6_CITANIE2_MULTI
	char anchor[MAX_STR_AF_ANCHOR];
	short int count;
};
typedef struct _lang_cal_type_anchor_and_count _struct_lang_cal_type_anchor_and_count;

struct _lang_param_and_anchor {
	short int language;
	char paramname[MAX_BUFFER];
	char anchor[MAX_STR_AF_ANCHOR];
};
typedef struct _lang_param_and_anchor _struct_lang_param_and_anchor;

struct _lang_cal_param_and_anchor {
	short int language;
	short int calendar;
	char paramname[MAX_BUFFER];
	char anchor[MAX_STR_AF_ANCHOR];
};
typedef struct _lang_cal_param_and_anchor _struct_lang_cal_param_and_anchor;

extern const char* bible_references_default[POCET_JAZYKOV + 1];

extern const char* bible_version_id_default[POCET_JAZYKOV + 1];

#define POCET_MENU_GROUPS	6

#define MAX_POCET_MENU_ITEMS	33

#define MENU_0_GENERAL			0
#define MENU_1_DEVICE			1
#define MENU_2_LOOK				2
#define MENU_3_TEXT_CONTENT 	3
#define MENU_4_CALENDAR			4
#define	MENU_5_TTS				5 // not supported for web

#define POCET_MENU_0_ITEMS	3

#define MENU_0_ITEM_LANGUAGE	0
#define MENU_0_ITEM_CALENDAR	1
#define MENU_0_ITEM_WHEN_ONLINE	2

#define POCET_MENU_1_ITEMS	4

#define MENU_1_ITEM_VOLUME_BUTTONS	0 // Android only
#define MENU_1_ITEM_SCREEN_ALWAYS	1
#define MENU_1_ITEM_DO_NOT_DISTURB	2
#define MENU_1_ITEM_LOCK_FONT_SIZE	3 // do not allow font size change by standard gestures

#define POCET_MENU_2_ITEMS	9

#define MENU_2_ITEM_FONT						0
#define MENU_2_ITEM_COLOR_SCHEMA				1 // Android: night mode
#define MENU_2_ITEM_NORMAL_FONT					2 // do not allow bold font
#define MENU_2_ITEM_ROUNDED_CORNERS				3 // for buttons
#define MENU_2_ITEM_ALT_BACKGROUND				4 // Android only
#define MENU_2_ITEM_NAVIGATION_ARROWS			5 // navigation arrows (default: on the right side); used especially for e-book readers
#define MENU_2_ITEM_NAVIGATION_ARROWS_LEFT		6 // navigation arrows on the left side; used especially for e-book readers
#define MENU_2_ITEM_NAVIGATION_ARROW_DOWN_ONLY  7 // show only left navigation arrow; used especially for presenting
#define MENU_2_ITEM_BUTTONS_CONDENSED			8 // default (Android, web): ON; historically all buttons for prayers could be displayed in single line (table row)
#define MENU_2_ITEM_BUTTONS_ORDERING			9 // ordering of buttons for prayers and buttons for date-navigation
#define MENU_2_ITEM_NAVIGATION_IN_PRAYER		10 // navigation buttons in prayer text (iOS: never display; OFF); contains prayer buttons (laudes, vespers, etc.) + date/month/year navigation (in prayer text, prev/next/this day + today only)

#define POCET_MENU_3_ITEMS	33

#define MENU_3_ITEM_SWITCHES_IN_TEXT	0 // switches as clickable hyperlinks directly in prayer texts; default: ON

#define MENU_3_ITEM_ALTERNATIVES		1

#define MENU_3_ITEM_COMMUNIA_INFO		2
#define MENU_3_ITEM_COMMUNIA_FORCE		3
#define MENU_3_ITEM_VERSE_NUMBERING		4
#define MENU_3_ITEM_PSALM_OMMISIONS		5
#define MENU_3_ITEM_ELISIONS_ITALICS	6
#define MENU_3_ITEM_TEXT_NOTES			7 // footnotes & endnotes
#define MENU_3_ITEM_SAINT_DETAILS_HIDE	8
#define MENU_3_ITEM_MCD_SUPPL_PSALMS	9
#define MENU_3_ITEM_MCD_SPECIAL_PS		10
#define MENU_3_ITEM_INV_PSALM_95		11
#define MENU_3_ITEM_PRECES_REPEAT		12
#define MENU_3_ITEM_VESPERS_SPEC_PREC	13
#define MENU_3_ITEM_VIGILIES			14
#define MENU_3_ITEM_ALT_CONCLUSION		15
#define MENU_3_ITEM_ALT_PS_122_129		16
#define MENU_3_ITEM_ALT_PS_126_129		17
#define MENU_3_ITEM_ALT_PS_127_131		18
#define MENU_3_ITEM_ALT_PA_34_HYMNS		19
#define MENU_3_ITEM_ALT_ASH_WED_PS		20
#define MENU_3_ITEM_ALT_GREEN_TH_PS		21
#define MENU_3_ITEM_ALT_DEF_PS_146_150 	22
#define MENU_3_ITEM_ALT_READ_PA_HYMNS	23
#define MENU_3_ITEM_ALT_MCD_9_HYMN		24
#define MENU_3_ITEM_ALT_MCD_12_HYMN		25
#define MENU_3_ITEM_ALT_MCD_15_HYMN		26
#define MENU_3_ITEM_LINE_BREAKS_PRINTED	27
#define MENU_3_ITEM_ALT_PA_HYMN_SUN		28
#define MENU_3_ITEM_ALT_COMPL_HYMN		29
#define MENU_3_ITEM_ALT_READ_EAST_HYMN	30
#define MENU_3_ITEM_ALT_LAUD_EAST_HYMN	31
#define MENU_3_ITEM_ALT_VESP_EAST_HYMN	32

#define POCET_MENU_4_ITEMS	4

#define MENU_4_ITEM_EPIPHANY 		0
#define MENU_4_ITEM_ASSUMPT			1
#define	MENU_4_ITEM_BODY_BLOOD 		2
#define	MENU_4_ITEM_LOCAL_CAL_EMPH 	3

#define POCET_MENU_5_ITEMS	3

#define MENU_5_ITEM_SPEED	0 // iOS only
#define MENU_5_ITEM_PAUSES	1 // special pauses for asterisks and crosses in psalmody
#define	MENU_5_ITEM_HELP	2 // Android only

const short int pocet_menu_items[POCET_MENU_GROUPS] = { POCET_MENU_0_ITEMS, POCET_MENU_1_ITEMS, POCET_MENU_2_ITEMS, POCET_MENU_3_ITEMS, POCET_MENU_4_ITEMS, POCET_MENU_5_ITEMS };

#define POCET_MENU_ITEM_TYPE	3

#define MENU_ITEM_TYPE_UNDEFINED		0 // this menu item is not defined/not used yet; similar to 0 in supported_calendars_language[][]
#define MENU_ITEM_TYPE_MAIN_SWITCH		1 // switch, like 'j' (language) or 'c' (calendar)
#define MENU_ITEM_TYPE_BIT_OPTION		2 // bit option given by option and bit-component, like OPT_2_HTML_EXPORT and BIT_OPT_2_NOCNY_REZIM
#define MENU_ITEM_TYPE_APP_SPECIFIC		3 // these are not supported by this core CGI module; apps handle them on their own

extern const char* menu_item_type_name[POCET_MENU_ITEM_TYPE + 1];

const short int menu_item_type[POCET_MENU_GROUPS][MAX_POCET_MENU_ITEMS] = {
	/*MENU_0_GENERAL*/		{ MENU_ITEM_TYPE_MAIN_SWITCH, MENU_ITEM_TYPE_MAIN_SWITCH, MENU_ITEM_TYPE_APP_SPECIFIC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	/*MENU_1_DEVICE*/		{ MENU_ITEM_TYPE_APP_SPECIFIC, MENU_ITEM_TYPE_APP_SPECIFIC, MENU_ITEM_TYPE_APP_SPECIFIC, MENU_ITEM_TYPE_APP_SPECIFIC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	/*MENU_2_LOOK*/			{ MENU_ITEM_TYPE_MAIN_SWITCH, MENU_ITEM_TYPE_BIT_OPTION, MENU_ITEM_TYPE_BIT_OPTION, MENU_ITEM_TYPE_BIT_OPTION, MENU_ITEM_TYPE_APP_SPECIFIC, MENU_ITEM_TYPE_BIT_OPTION, MENU_ITEM_TYPE_BIT_OPTION, MENU_ITEM_TYPE_BIT_OPTION, MENU_ITEM_TYPE_BIT_OPTION, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	/*MENU_3_TEXT_CONTENT*/	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	/*MENU_4_CALENDAR*/		{ MENU_ITEM_TYPE_BIT_OPTION, MENU_ITEM_TYPE_BIT_OPTION, MENU_ITEM_TYPE_BIT_OPTION, MENU_ITEM_TYPE_BIT_OPTION, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	/*MENU_5_TTS*/			{ MENU_ITEM_TYPE_APP_SPECIFIC, MENU_ITEM_TYPE_APP_SPECIFIC, MENU_ITEM_TYPE_APP_SPECIFIC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

struct menu_item_switch_str_name {
	char switch_str[SMALL];
	char switch_xml[SMALL]; // XML element name
	char switch_name[SMALL];
};

struct menu_item_option_str_name {
	char option_str[SMALL]; // option group
	char option_force[SMALL]; // bit opt force
	char option_xml[SMALL]; // XML element name
	char option_name[SMALL];
};

#endif // __LITURGIA_H_


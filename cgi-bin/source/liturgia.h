/************************************************************/
/*                                                          */
/* liturgia.h                                               */
/* (c)1999-2015 | Juraj Vidéky | videky@breviar.sk          */
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
#include "mylog.h"
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define MENO_SVIATKU 250
#define MAX_LC_STR_ID 50

// liturgical rites
#define RITUS_RIM_KAT   0
#define RITUS_GR_KAT    1

// language IDs (constants)
// 2006-07-11: created
// 2006-12-12: added JAZYK_LA
// 2008-08-15: added JAZYK_CZ_OP
// 2009-01-29: added JAZYK_HU
// 2015-04-02: added JAZYK_RU
#define JAZYK_SK	0
#define JAZYK_CZ	1
#define JAZYK_EN	2
#define JAZYK_LA    3
#define JAZYK_UNDEF 4
#define JAZYK_CZ_OP 5
#define JAZYK_HU    6
#define JAZYK_RU    7
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
	/* ADD_VALUE_FOR_NEW_LANGUAGE */
};

// formats of date (HU, EN...)
#define FORMAT_DATUMU_DEN_MESIAC_ROK 0 // DD. MM RRRR
#define FORMAT_DATUMU_MESIAC_DEN_ROK 1 // MM DD RRRR
#define FORMAT_DATUMU_ROK_MESIAC_DEN 2 // RRRR. MM DD

extern const short int format_datumu[POCET_JAZYKOV + 1];

// number of CSSs
#define POCET_CSS	4

// CSSs
#define CSS_UNDEF				0
#define CSS_breviar_sk			1
#define CSS_breviar_sk_invert	2
#define CSS_kbd_sk				3
#define CSS_ebreviar_cz			4

// static texts
#define POCET_STATIC_TEXTOV               2

#define STATIC_TEXT_UNDEF                 0
#define STATIC_TEXT_MARIANSKE_ANTIFONY    1
#define STATIC_TEXT_ORDINARIUM            2

// number of fonts
#define	POCET_FONTOV	9

// fonts used in drop-down list
#define FONT_UNDEF		0
#define FONT_CSS		1
#define FONT_CHECKBOX	2
#define FONT_CAMBRIA    3
#define FONT_CANDARA	4
#define FONT_GEORGIA	5
#define FONT_TAHOMA		6
#define FONT_HELVETICA	7
#define FONT_SERIF		8
#define FONT_SANS_SERIF	9

// number of font-sizes
#define	POCET_FONT_SIZE	8

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

#define MIN_STYLE_MARGIN      0
#define MAX_STYLE_MARGIN   1024
#define DEF_STYLE_MARGIN      5

// alternatives for some parts of prayers
#define BIT_ALT_HYMNUS                  1
#define BIT_ALT_ANTCHVAL                2
#define BIT_ALT_LEN_DOPLNKOVA_PSALMODIA 4
#define BIT_ALT_DOPLNK_PSALM_122_129    8
#define BIT_ALT_DOPLNK_PSALM_127_131   16
#define BIT_ALT_DOPLNK_PSALM_126_129   32
#define BIT_ALT_HYMNUS_VN              64

#define MAX_STR_AF_FILE   64
#define MAX_STR_AF_ANCHOR 32
struct _anchor_and_file{
	char file[MAX_STR_AF_FILE];
	char anchor[MAX_STR_AF_ANCHOR];
};
typedef struct _anchor_and_file _struct_anchor_and_file;

#define rchvalospev  zalm2
#define vchvalospev  zalm3
#define magnifikat   benediktus

struct tmodlitba1{
	short int alternativy; // bitové komponenty hovoria, ktoré časti môžu mať alternatívy
	_struct_anchor_and_file popis     ;
	_struct_anchor_and_file hymnus    ;
	_struct_anchor_and_file antifona1 ;
	_struct_anchor_and_file zalm1     ;
	_struct_anchor_and_file antifona2 ;
	_struct_anchor_and_file zalm2     ;
	_struct_anchor_and_file antifona3 ;
	_struct_anchor_and_file zalm3     ;
	_struct_anchor_and_file kcitanie  ;
	_struct_anchor_and_file kresponz  ; 
	_struct_anchor_and_file benediktus; // antifona na benediktus/magnifikat
	_struct_anchor_and_file prosby    ; // pre posvatne citanie nedefinovane; 2011-03-16: "zneužité" (použité) pre hagiografické čítanie (ľubovoľnej) spomienky svätca v pôste
	_struct_anchor_and_file modlitba  ;
	_struct_anchor_and_file ant_spomprivileg; // 2010-05-21: pridané kvôli spomienkam a ľubovoľným spomienkam v pôstnom období (zobrazenie po modlitbe dňa pôstnej férie) // 2012-02-09: zovšeobecnené v zmysle VSLH č. 238 (Spomienky pripadajúce na privilegované dni)
	_struct_anchor_and_file modlitba_spomprivileg; // 2010-05-21: pridané kvôli spomienkam a ľubovoľným spomienkam v pôstnom období (zobrazenie po modlitbe dňa pôstnej férie) // 2012-02-09: zovšeobecnené v zmysle VSLH č. 238 (Spomienky pripadajúce na privilegované dni)
};
typedef struct tmodlitba1 _type_ranne_chvaly;
typedef struct tmodlitba1 _type_vespery;
typedef struct tmodlitba1 _type_1vespery;
// typedef struct tmodlitba1 _type_posv_citanie;

struct tmodlitba2{
	short int alternativy; // bitové komponenty hovoria, ktoré časti môžu mať alternatívy
	_struct_anchor_and_file popis     ;
	_struct_anchor_and_file hymnus    ;
	_struct_anchor_and_file antifona1 ;
	_struct_anchor_and_file zalm1     ;
	_struct_anchor_and_file antifona2 ;
	_struct_anchor_and_file zalm2     ;
	_struct_anchor_and_file antifona3 ;
	_struct_anchor_and_file zalm3     ;
	_struct_anchor_and_file kcitanie  ;
	_struct_anchor_and_file kresponz  ;
	_struct_anchor_and_file modlitba  ;
};
typedef struct tmodlitba2 _type_cez_den_9;
typedef struct tmodlitba2 _type_cez_den_12;
typedef struct tmodlitba2 _type_cez_den_3;

// alternate typenames for prayer during the day
typedef struct tmodlitba2 _type_cez_den_pred;
typedef struct tmodlitba2 _type_cez_den_na;
typedef struct tmodlitba2 _type_cez_den_po;

struct tmodlitba3{
	short int alternativy; // bitové komponenty hovoria, ktoré časti môžu mať alternatívy
	short int pocet_zalmov            ; // pridané 2006-10-18; niekedy sú až 2 žalmy
	_struct_anchor_and_file popis     ; // pridané 2006-10-11; zrušené antifona2, zalm2 a modlitba
	_struct_anchor_and_file hymnus    ;
	_struct_anchor_and_file antifona1 ;
	_struct_anchor_and_file zalm1     ;
	_struct_anchor_and_file antifona2 ; // pridané 2006-10-17; niekedy sú až 2 žalmy
	_struct_anchor_and_file zalm2     ;
	_struct_anchor_and_file kcitanie  ;
	_struct_anchor_and_file kresponz  ;
	_struct_anchor_and_file nunc_dimittis; // antifóna na nunc dimittis; pridané 2013-04-03 (kvôli OPRAEM, 08dec)
	_struct_anchor_and_file modlitba  ;
};
typedef struct tmodlitba3 _type_kompletorium;
typedef struct tmodlitba3 _type_1kompletorium;

struct tmodlitba4{
	_struct_anchor_and_file popis     ;
	_struct_anchor_and_file antifona1 ;
	_struct_anchor_and_file zalm1     ;
};
typedef struct tmodlitba4 _type_invitatorium;

struct tmodlitba5{
	short int alternativy; // bitové komponenty hovoria, ktoré časti môžu mať alternatívy
	_struct_anchor_and_file popis     ;
	_struct_anchor_and_file hymnus    ;
	_struct_anchor_and_file antifona1 ;
	_struct_anchor_and_file zalm1     ;
	_struct_anchor_and_file antifona2 ;
	_struct_anchor_and_file zalm2     ;
	_struct_anchor_and_file antifona3 ;
	_struct_anchor_and_file zalm3     ;
	_struct_anchor_and_file kresponz  ; 
	_struct_anchor_and_file citanie1  ; // 1. citanie pre posvatne citanie
	_struct_anchor_and_file citanie2  ; // 2. citanie pre posvatne citanie
	_struct_anchor_and_file citanie_spomprivileg ; // 2011-03-16: "zneužité" (použité) pre hagiografické čítanie (ľubovoľnej) spomienky svätca v pôste; 2011-03-25: nový typ -> nové meno
	_struct_anchor_and_file ant_chval ; // vigília: antifóna pre chválospevy
	_struct_anchor_and_file chval1    ; // vigília: chválospev I
	_struct_anchor_and_file chval2    ; // vigília: chválospev II
	_struct_anchor_and_file chval3    ; // vigília: chválospev III
	_struct_anchor_and_file evanjelium; // vigília: evanjelium
	_struct_anchor_and_file modlitba  ;
};
typedef struct tmodlitba5 _type_posv_citanie;

struct den_mesiac{ // takto povodne vyzerala struct dm
	short int den;        // cislo dna mesiaca (1--31)
	short int mesiac;     // cislo mesiaca (1--12) - ináč ako je potrebné pre väčšinu polí, kde je mesiac 0--11
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

// 2007-12-05: doplnené kvôli modlitbe kompletória, funkcia _set_kompletorium_nedela()
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
#define CHAR_MODL_NEURCENA           '_' // toto by sa nemalo
#define CHAR_MODL_PRVE_VESPERY       '1'
#define CHAR_MODL_PRVE_KOMPLETORIUM  'p'
#define CHAR_MODL_DRUHE_VESPERY      'w' // toto by sa nemalo
#define CHAR_MODL_DRUHE_KOMPLETORIUM 'm' // toto by sa nemalo
// #define CHAR_MODL_CEZ_DEN_VSETKY     'd' // 2005-03-27: pridané
#define CHAR_MODL_VSETKY             '*' // 2011-10-03: pridané pokusne

// added for batch mode
extern const char char_modlitby[POCET_MODLITIEB + 1];
extern const char *str_modlitby[POCET_MODLITIEB + 1];

extern const char *nazov_modlitby_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1];
#define		nazov_modlitby(a)	nazov_modlitby_jazyk[a][_global_jazyk]

extern const char *nazov_Modlitby_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1];
#define		nazov_Modlitby(a)	nazov_Modlitby_jazyk[a][_global_jazyk]

extern const char *nazov_MODLITBY_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1];
#define		nazov_MODLITBY(a)	nazov_MODLITBY_jazyk[a][_global_jazyk]

// file templates for prayers
#define TEMPLAT_INVITATORIUM     "m_invitat.htm"
#define TEMPLAT_POSV_CITANIE     "m_posvcit.htm"
#define TEMPLAT_RANNE_CHVALY     "m_rchvaly.htm"
#define TEMPLAT_CEZ_DEN_9        "m_predpol.htm"
#define TEMPLAT_CEZ_DEN_12       "m_napol.htm"
#define TEMPLAT_CEZ_DEN_3        "m_popol.htm"
#define TEMPLAT_VESPERY          "m_vespery.htm"
#define TEMPLAT_KOMPLETORIUM     "m_komplet.htm"
#define TEMPLAT_EMPTY            STR_EMPTY // MODL_VSETKY + MODL_DETAILY
#define TEMPLAT_STATIC_TEXT      "m_text.htm" // MODL_NEURCENA

// compline in Ordinary time
#define nazov_obd_KOMPLETORIUM   "cezrok_k.htm"

extern const char *TEMPLAT[POCET_MODLITIEB + 1];

#define ORDINARIUM_INVITATORIUM     "ord_invitat.htm"
#define ORDINARIUM_POSV_CITANIE     "ord_posvcit.htm"
#define ORDINARIUM_RANNE_CHVALY     "ord_rchvaly.htm"
#define ORDINARIUM_CEZ_DEN          "ord_mcd.htm"
#define ORDINARIUM_VESPERY          "ord_vespery.htm"
#define ORDINARIUM_KOMPLETORIUM     "ord_komplet.htm"
#define ORDINARIUM_EMPTY            STR_EMPTY // MODL_VSETKY + MODL_DETAILY

extern const char *ORDINARIUM[POCET_MODLITIEB + 1];

#define SHOW_TEMPLAT_MODLITBA      1 // use TEMPLAT[]
#define SHOW_TEMPLAT_STATIC_TEXT   2 // use ORDINARIUM[]

// keyword (anchor) begin + end
#define CHAR_KEYWORD_BEGIN   '{'
#define CHAR_KEYWORD_END     '}'
#define CHAR_KEYWORD_DIVIDER ':'

// underscore '_' used as placeholder for non-breaking space (it will be exported as HTML_NONBREAKING_SPACE == "&nbsp;" defined in mydefs.h) 
#define CHAR_NONBREAKING_SPACE '_'

// special characters in prayer texts (some of them to be removed for blind-friendly version)
#define CHAR_SPACE             ' '
#define CHAR_PRAYER_ASTERISK   '*'
#define CHAR_PRAYER_CROSS      L'\x2020' /*†*/
#define CHAR_PRAYER_CROSS_ALT  '+'

// include parameters
#define INCLUDE_BEGIN   "BEGIN" // zaciatok
#define INCLUDE_END     "END"   // koniec

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

#define PARAM_ANTIFONA1x    "ANTIFONA1_DRUHA"
#define PARAM_ANTIFONA3x    "ANTIFONA3_PRVA"

#define PARAM_ANTIFONA1k    "ANTIFONA1_KOMPLET"
#define PARAM_ANTIFONA2k    "ANTIFONA2_KOMPLET"
// VSLH č. 238 (Spomienky pripadajúce na privilegované dni)
#define PARAM_ANT_SPOMPRIVILEG  "ANT_SPOMPRIVILEG"
#define PARAM_MODL_SPOMPRIVILEG "MODL_SPOMPRIVILEG"
#define PARAM_CITANIE2_SPOMPRIVILEG "CITANIE2_SPOMPRIVILEG"

#define PARAM_NAVIGACIA     "NAVIGACIA"
#define PARAM_NADPIS        "NADPIS"
// 2012-04-03: pridaný podnadpis v modlitbe (napr. pre MCD: doplnková psalmódia)
#define PARAM_PODNADPIS     "PODNADPIS"
#define PARAM_SPOL_CAST     "SPOL_CAST"

#define PARAM_ANTIFONA_VIG  "ANTIFONA_VIG"
#define PARAM_CHVALOSPEV1   "CHVALOSPEV1"
#define PARAM_CHVALOSPEV2   "CHVALOSPEV2"
#define PARAM_CHVALOSPEV3   "CHVALOSPEV3"
#define PARAM_EVANJELIUM    "EVANJELIUM"

#define PARAM_TEXT          "TEXT" // static text included into single file
#define PARAM_MARIANSKE_ANTIFONY_LINK "MARIANSKE_ANTIFONY_LINK" // hyperlink to Maria antiphones (static HTML text or dynamically generated URL

#define PARAM_DOPLNKOVA_PSALMODIA      "DOPLNKOVA-PSALMODIA" // supplementary psalmody (for daily prayers: 9h, 12h, 15h)
#define PARAM_PSALMODIA                "PSALMODIA" // alternative psalmody (e. g. for morning prayer, Ash Wednesday)

#define PARAM_PSALMODIA_TRI_TYZDNE     "PSALMODIA-TRI-TYZDNE"

#define PARAM_CHVALOSPEV               "CHVALOSPEV"
#define PARAM_TEDEUM		           "TEDEUM"
#define PARAM_OTCENAS                  "OTCENAS"
#define PARAM_ZVOLANIA                 "ZVOLANIA"
#define PARAM_SLAVAOTCU	               "SLAVAOTCU"
#define PARAM_RESPONZ                  "RESPONZ" // PARAM_PLNE_RESP je už obsadené...
#define PARAM_KRATSIE_PROSBY           "KRATSIE-PROSBY" // 2012-11-15: _ sa menilo na &nbsp; preto som zmenil na -
#define PARAM_ZALM95                   "ZALM95" // 2012-11-23: kvôli <a name...>
#define PARAM_VIGILIA                  "VIGILIA"
#define PARAM_SPOL_CAST_SPOM           "SPOL-CAST-SPOM"
#define PARAM_ALT_HYMNUS               "ALT-HYMNUS"
#define PARAM_ZALM122                  "ZALM122"
#define PARAM_ZALM126                  "ZALM126"
#define PARAM_ZALM127                  "ZALM127"
#define PARAM_ZALM129                  "ZALM129"
#define PARAM_ZALM131                  "ZALM131"

// Od nedele Pánovho zmŕtvychvstania až do Druhej veľkonočnej nedele vrátane, ako aj na druhé vešpery slávnosti Zoslania Ducha Svätého
#define PARAM_ALELUJA_ALELUJA_BEGIN         "ALELUJA_ALELUJA_BEGIN"
#define PARAM_ALELUJA_ALELUJA_END           "ALELUJA_ALELUJA_END"
#define PARAM_ALELUJA_NIE_V_POSTE           "ALELUJA_NIE_V_POSTE" // používa sa v inkludovaných súboroch, napr. v rámci antifón
#define PARAM_ALELUJA_NIE_V_POSTE_BEGIN     "ALELUJA_NIE_V_POSTE_BEGIN"
#define PARAM_ALELUJA_NIE_V_POSTE_END       "ALELUJA_NIE_V_POSTE_END"
#define PARAM_ALELUJA_VO_VELKONOCNOM        "V_O_ALELUJA" // používa sa v inkludovaných súboroch, napr. v rámci antifón
#define PARAM_ALELUJA_VO_VELKONOCNOM_BEGIN  "V_O_ALELUJA_BEGIN" // používajú sa v templátach
#define PARAM_ALELUJA_VO_VELKONOCNOM_END    "V_O_ALELUJA_END"
// 2005-08-15: Doplnené parametre pre voľné, iné hymny v 34. týždni OCR
#define PARAM_HYMNUS_34_OCR_INY_BEGIN       "HYMNUS_34_OCR_INY_BEGIN"
#define PARAM_HYMNUS_34_OCR_INY_END         "HYMNUS_34_OCR_INY_END"
// nasleduju casti, ktore sa mozu pri generovani modlitby vynechat alebo doplnit podla lubovole
#define PARAM_OTCENAS_BEGIN                 "OTCENAS_BEGIN"
#define PARAM_OTCENAS_END                   "OTCENAS_END"
#define PARAM_CHVALOSPEV_BEGIN              "CHVALOSPEV_BEGIN"
#define PARAM_CHVALOSPEV_END                "CHVALOSPEV_END"
#define PARAM_ZAKONCENIE_BEGIN              "ZAKONCENIE_BEGIN"
#define PARAM_ZAKONCENIE_END                "ZAKONCENIE_END"
#define PARAM_KOMPLETORIUM_DVA_ZALMY_BEGIN	"KOMPLETORIUM_DVA_ZALMY_BEGIN"
#define PARAM_KOMPLETORIUM_DVA_ZALMY_END	"KOMPLETORIUM_DVA_ZALMY_END"
#define PARAM_SLAVAOTCU_BEGIN               "SLAVAOTCU_BEGIN"
#define PARAM_SLAVAOTCU_END                 "SLAVAOTCU_END"
// special case: Sláva Otcu "špeciálne" pre účely chválospevu Dan 3, 57-88. 56, kde nie je "Sláva Otcu" (pôvodne to bolo dané poradím, ale templáty pre rôzne jazyky majú rozličné poradie tohto "Sláva Otcu")
#define PARAM_SLAVAOTCU_SPEC_BEGIN          "SLAVAOTCU_SPEC_BEGIN"
#define PARAM_SLAVAOTCU_SPEC_END            "SLAVAOTCU_SPEC_END"

// 2011-04-11: pridaný ďalší pár parametrov
//             JE_TEDEUM_BEGIN a END hovoria, či v danej modlitbe má vôbec byť zobrazená čo i len zmienka o Te Deum (riadené podmienkou je_tedeum);
//             TEDEUM_BEGIN a END hovoria, že ak má byť Te Deum (je_tedeum), tak ak chce používateľ zobraziť plný text, ohraničujú ho
#define PARAM_TEDEUM_BEGIN                  "TEDEUM_BEGIN"
#define PARAM_TEDEUM_END                    "TEDEUM_END"
#define PARAM_JE_TEDEUM_BEGIN               "JE_TEDEUM_BEGIN"
#define PARAM_JE_TEDEUM_END                 "JE_TEDEUM_END"

#define PARAM_SKRY_ANTIFONU_BEGIN           "SKRY_ANTIFONU_BEGIN"
#define PARAM_SKRY_ANTIFONU_END             "SKRY_ANTIFONU_END"

#define PARAM_ZOBRAZ_ANTIFONU_BEGIN         "ZOBRAZ_ANTIFONU_BEGIN"
#define PARAM_ZOBRAZ_ANTIFONU_END           "ZOBRAZ_ANTIFONU_END"

#define PARAM_JE_VIGILIA_BEGIN              "JE_VIGILIA_BEGIN"
#define PARAM_JE_VIGILIA_END                "JE_VIGILIA_END"

// 2010-05-21: doplnené zobrazenie antifóny a modlitby pre spomienku svätca v pôstnom období
// 2012-02-09: zovšeobecnené v zmysle VSLH č. 238 (Spomienky pripadajúce na privilegované dni)
#define PARAM_SPOMIENKA_PRIVILEG_BEGIN      "SPOMIENKA_PRIVILEG_BEGIN"
#define PARAM_SPOMIENKA_PRIVILEG_END        "SPOMIENKA_PRIVILEG_END"
// 2011-01-12: doplnené zobrazenie/skrytie myšlienky k žalmu -- pre cezročné obdobie alternatívnej antifóny žalmu/chválospevu ("myšlienka k žalmu" podľa bodu 111 a 114 VSLH)
#define PARAM_PSALMODIA_MYSLIENKA           "PSALMODIA_MYSLIENKA" // 2011-08-31: zmenené; pôvodne bolo: PARAM_MYSLIENKA_K_ZALMU "MYSLIENKA_K_ZALMU"
// 2011-08-31: doplnené zobrazenie/skrytie nadpisu k žalmu/chválospevu ("nadpis k žalmu" podľa bodu 111 VSLH)
#define PARAM_PSALMODIA_NADPIS              "PSALMODIA_NADPIS"

#define PARAM_RUBRIKA_BEGIN                 "RUBRIKA_BEGIN"
#define PARAM_RUBRIKA_END                   "RUBRIKA_END"

// 2011-05-03: doplnené kvôli posvätnému čítaniu na veľkonočnú nedeľu
#define PARAM_VN_VYNECHAJ_BEGIN             "VELK_NEDELA_VYNECHAJ_BEGIN"
#define PARAM_VN_VYNECHAJ_END               "VELK_NEDELA_VYNECHAJ_END"

// 2011-07-07: doplnené kvôli zobrazovaniu/skrývaniu dlhších záverov responzórií v posvätnom čítaní
#define PARAM_PLNE_RESP                     "PLNE_RESP"
#define PARAM_PLNE_RESP_BODKA               "PLNE_RESP_BODKA"

// 2011-10-05: doplnené kvôli zobrazovaniu/skrývaniu opakovaného zvolania v prosbách (ranné chvály, vešpery)
#define PARAM_ZVOLANIE                      "ZVOLANIE"

// 2011-10-26: doplnené rubriky priamo v includovaných HTML súboroch
#define PARAM_RUBRIKA                       "RUBRIKA"

// 2011-04-04: doplnené zobrazenie/skrytie číslovania veršov v žalmoch, chválospevoch a biblických čítaniach
#define PARAM_CISLO_VERSA_BEGIN				"v"
#define PARAM_CISLO_VERSA_END				"/v"

// 2011-04-05: doplnenie referencie podľa biblického odkazu na stránky dkc.kbs.sk (Biblia -- Matúš Brilla)
#define PARAM_REFERENCIA_BEGIN				"r"
#define PARAM_REFERENCIA_END				"/r"

// 2011-09-01: odkaz na katechézy
#define PARAM_KATECHEZA_BEGIN				"k"
#define PARAM_KATECHEZA_END					"/k"

// 2011-09-06: odkaz na žalm 95
#define PARAM_LINK_ZALM95_BEGIN				"z95"
#define PARAM_LINK_ZALM95_END				"/z95"

// 2011-07-08: zobrazovanie/nezobrazenie krížika (antifóna totožná s veršom žalmu/chválospevu)
#define PARAM_KRIZIK                        "KRIZIK"

// 2011-07-14: zobrazovanie/nezobrazenie zalomených textov tak, ako je v tlačenom vydaní LH (dlhé riadky-verše žalmov/chválospevov a pod.)
#define PARAM_ZALOMENIE                     "ZALOMENIE"

// 2011-10-07: zakončenie modlitieb (skrze, lebo on, lebo ty...) ináč (jednoduchšie, bez begin-end)
#define PARAM_ZAKONCENIE                    "ZAKONCENIE"

// 2013-02-26: doplnková psalmódia, alternatívne žalmy
#define PARAM_DOPLNK_PSALM_122_129          "DPSALM-122-129"
#define PARAM_DOPLNK_PSALM_126_129          "DPSALM-126-129"
#define PARAM_DOPLNK_PSALM_127_131          "DPSALM-127-131"

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
// ešte jedno zakončenie modlitby pre slovenčinu, krátke resp. dlhé
#define PARAM_ZAKONCENIE_KTORY_JE           "KTORY_JE"
// predslovy k zakončeniam, ktoré sa pre férie nemajú zobraziť, ak sa slávi spomienka v privilegovaných dňoch
#define PARAM_ZAKONCENIE_O_TO_TA_PROSIME    "O_TO_TA_PROSIME"

// force pre jednotlivé časti modlitby, funkcie _set_spolocna_cast()...
#define FORCE_NEBRAT               0
#define FORCE_BRAT_ANTIFONY        1 // antifóny pre ranné chvály, posv. čítanie a vešpery
#define FORCE_BRAT_ZALMY           2
#define FORCE_BRAT_KCIT_1CIT       4 // krátke čítanie pre rch+v a mcd; 1. čítanie pre posvätné čítanie
#define FORCE_BRAT_KRESP_PROSBY    8 // krátke responzórium a prosby pre ranné chvály, vešpery a mcd; krátke responzórium pre posv. čítanie
#define FORCE_BRAT_2CITANIE       16 // 2. čítanie pre posvätné čítanie
#define FORCE_BRAT_ANTIFONY_MCD   32 // antifóny pre modlitbu cez deň
#define FORCE_BRAT_HYMNUS         64 // hymnus pre všetky modlitby
#define FORCE_BRAT_ANTIFONY_B_M  128 // Benediktus + Magnifikat
#define FORCE_BRAT_ANTIFONY_INV  256 // antifóny pre invitatórium
#define FORCE_BRAT_MODLITBA      512 // modlitba (používa sa pre modlitbu cez deň)

extern const char *str_ano[POCET_JAZYKOV + 1];
#ifndef		STR_ANO
#define		STR_ANO		str_ano[_global_jazyk]
#endif

extern const char *str_nie[POCET_JAZYKOV + 1];
#ifndef		STR_NIE
#define		STR_NIE		str_nie[_global_jazyk]
#endif

extern const char *str_modl_zalmy_zo_dna[POCET_JAZYKOV + 1];
#ifndef		STR_MODL_ZALMY_ZO_DNA
#define		STR_MODL_ZALMY_ZO_DNA 	str_modl_zalmy_zo_dna[_global_jazyk]
#endif

extern const char *str_modl_zalmy_zo_sv[POCET_JAZYKOV + 1];
#ifndef		STR_MODL_ZALMY_ZO_SV
#define		STR_MODL_ZALMY_ZO_SV 	str_modl_zalmy_zo_sv[_global_jazyk]
#endif

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

extern const char *str_doplnkova_psalmodia[POCET_JAZYKOV + 1];

extern const char *str_modl_cez_den_zalmy_zo_dna[POCET_JAZYKOV + 1];
#ifndef		STR_MODL_CEZ_DEN_ZALMY_ZO_DNA
#define		STR_MODL_CEZ_DEN_ZALMY_ZO_DNA	str_modl_cez_den_zalmy_zo_dna[_global_jazyk]
#endif

extern const char *str_modl_cez_den_doplnkova_psalmodia[POCET_JAZYKOV + 1];
#ifndef		STR_MODL_CEZ_DEN_DOPLNKOVA_PSALMODIA
#define		STR_MODL_CEZ_DEN_DOPLNKOVA_PSALMODIA	str_modl_cez_den_doplnkova_psalmodia[_global_jazyk]
#endif

extern const char *nazov_spolc_jazyk[POCET_SPOL_CASTI + 1][POCET_JAZYKOV + 1];
#ifndef		nazov_spolc
#define		nazov_spolc(a)	nazov_spolc_jazyk[a][_global_jazyk]
#endif

extern const char *nazov_spolc_htm[MODL_SPOL_CAST_NEBRAT + 1];
extern const char *nazov_spolc_ANCHOR[MODL_SPOL_CAST_NEBRAT + 1];

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
	char litrok;          // liturgicky rok ('A'--'C')
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
};
typedef struct dm _struct_dm;

// week days
#define DEN_NEDELA      0
#define DEN_PONDELOK    1
#define DEN_UTOROK      2
#define DEN_STREDA      3
#define DEN_STVRTOK     4
#define DEN_PIATOK      5
#define DEN_SOBOTA      6
#define DEN_UNKNOWN     7
// number ofweek  days
#define POCET_DNI		7

// all days
#define VSETKY_DNI   32
#define STR_VSETKY_DNI  "*"

// months
#define MES_JAN 0
#define MES_FEB 1
#define MES_MAR 2
#define MES_APR 3
#define MES_MAY 4
#define MES_MAJ 4
#define MES_JUN 5
#define MES_JUL 6
#define MES_AUG 7
#define MES_SEP 8
#define MES_OCT 9
#define MES_OKT 9
#define MES_NOV 10
#define MES_DEC 11
#define UNKNOWN_MESIAC	12
// number of months
#define POCET_MESIACOV	12

// all months
#define VSETKY_MESIACE	13
#define STR_VSETKY_MESIACE  "*"

// liturgické obdobia | liturgical times/seasons
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

extern const char *nazov_obdobia_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1];
#define		nazov_obdobia(a)	nazov_obdobia_jazyk[a][_global_jazyk]

extern const char *nazov_obdobia_[POCET_OBDOBI + 1];

// lokal == 6. pad, v kom/com
extern const char *nazov_obdobia_v_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1];
#define		nazov_obdobia_v(a)	nazov_obdobia_v_jazyk[a][_global_jazyk]

extern const char *nazov_OBDOBIA_V_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1];
#define		nazov_OBDOBIA_V(a)	nazov_OBDOBIA_V_jazyk[a][_global_jazyk]

extern const char *nazov_OBDOBIA_AKA_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1];
#define		nazov_OBDOBIA_AKA(a)	nazov_OBDOBIA_AKA_jazyk[a][_global_jazyk]

// gen[itiv] == 2. pad, koho/coho

// nazov_obdobia: string pre nazov suboru .htm liturgickeho obdobia
extern const char *nazov_obd_htm[POCET_OBDOBI + 1];
// nazov_obdobia: string pre nazov kotvy v .htm liturgickeho obdobia
extern const char *nazov_OBD[POCET_OBDOBI + 1];
// nazov_obdobia pc: string pre nazov suboru .htm liturgickeho obdobia pre posvatne citania
extern const char *nazov_obd_htm_pc[POCET_OBDOBI + 1];
// 2005-08-05: Pridané. zväzok breviára (LH) pre spoločné časti svätých v kotvách
extern const char *zvazok_OBD[POCET_OBDOBI + 1];

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
extern const char *nazov_slavenia_jazyk[POCET_SLAVENI + 1][POCET_JAZYKOV + 1];
#define		nazov_slavenia(a)	nazov_slavenia_jazyk[a][_global_jazyk]

// the name of celebration -- for memoria (in privileged days)
extern const char *nazov_slavenia_na_spomienku_jazyk[POCET_JAZYKOV + 1];

extern const char *nazov_slavenia_lokal[];

#define LOKAL_SLAV_NEURCENE					0
#define LOKAL_SLAV_ROZNAVA_KATEDRALA		1
#define LOKAL_SLAV_TRNAVA_PATRON			2
#define LOKAL_SLAV_TT_BB_KE_NR_RO			3
#define LOKAL_SLAV_NITRA_PATRON				4
#define LOKAL_SLAV_KOSICE					5
#define LOKAL_SLAV_NITRA					6
#define LOKAL_SLAV_BYSTRICA					7
#define LOKAL_SLAV_SPIS						8
#define LOKAL_SLAV_ROZNAVA					9
#define LOKAL_SLAV_TRNAVA					10 // pôvodne bolo LOKAL_SLAV_TRNAVA, upravené 2007-08-31 na LOKAL_SLAV_BA_TT; naspäť na LOKAL_SLAV_TRNAVA 2008-06-23
#define LOKAL_SLAV_DOM_SV_MARTINA			11
#define LOKAL_SLAV_SPIS_PATRON				12
#define LOKAL_SLAV_BYSTRICA_PATRON			13
#define LOKAL_SLAV_TT_BB_NR_RO				14
#define LOKAL_SLAV_KOSICE_PATRON			15
#define LOKAL_SLAV_14_FEB_CYRIL_METOD		16
#define LOKAL_SLAV_ROZNAVA_PATRON			17
#define LOKAL_SLAV_KONSEKR_KOSTOLY			18
#define LOKAL_SLAV_DRUHA_VELK_NEDELA		19
#define LOKAL_SLAV_KONIEC_OKTAVY_NAR		20
#define LOKAL_SLAV_KONIEC_OKTAVY_NAR_CZ		21
#define LOKAL_SLAV_PRAHA_PATRON				22
#define LOKAL_SLAV_PRAHA					23
#define LOKAL_SLAV_BRNO						24
#define LOKAL_SLAV_MORAVA_SPOMIENKA			25
#define LOKAL_SLAV_DRUHA_VELK_NEDELA_CZ		26
#define LOKAL_SLAV_PRAHA_KATEDRALA			27
#define LOKAL_SLAV_CESKE_BUDEJOVICE			28
#define LOKAL_SLAV_OLOMOUC					29
#define LOKAL_SLAV_CECHY_SPOMIENKA			30
#define LOKAL_SLAV_PLZEN_PATRON				31
#define LOKAL_SLAV_OSTRAVA_OPAVA			32
#define LOKAL_SLAV_LITOMERICE				33
#define LOKAL_SLAV_HRADEC_KRALOVE			34
#define LOKAL_SLAV_KONSEKR_KOSTOLY_CZ 		35
#define LOKAL_SLAV_PLZEN 					36
#define LOKAL_SLAV_OSTRAVA_OPAVA_SLAVNOST	37
#define LOKAL_SLAV_CESKE_BUDEJOVICE_PAMATKA	38
#define LOKAL_SLAV_SPIS_BA_PATRON			39 // pre 11. novembra, patróna BA-arcidiecézy; 2008-06-24; nahrádza LOKAL_SLAV_SPIS_PATRON
#define LOKAL_SLAV_BRATISLAVA				40 // doplnené 2010-03-16
#define LOKAL_SLAV_KONIEC_OKTAVY_NAR_HU		41 // doplnené 2010-05-17
#define LOKAL_SLAV_KONGREGACIA_SSK			42 // doplnené 2011-01-27
#define LOKAL_SLAV_SPOMIENKA_OFMCAP			43 // nasledovné doplnené 2011-03-16
#define LOKAL_SLAV_SVIATOK_OFM				44
#define LOKAL_SLAV_SPOMIENKA_OFM			45
#define LOKAL_SLAV_SVIATOK_OFMCAP			46 // nasledovné doplnené 2011-03-17
#define LOKAL_SLAV_SPOMIENKA_FMA			47
#define LOKAL_SLAV_SLAVNOST_FMA				48
#define LOKAL_SLAV_SLAVNOST_SDB				49
#define LOKAL_SLAV_SVIATOK_VDB				50
#define LOKAL_SLAV_SVIATOK_SCSC				51
#define LOKAL_SLAV_DRUHA_VELK_NEDELA_HU		52
#define LOKAL_SLAV_SZOMBATHELYI_EGYH        53
#define LOKAL_SLAV_NAGYSZ_PATRON       54
#define LOKAL_SLAV_SZEGED_CSAN_PATRON       55
#define LOKAL_SLAV_PECSI_EGYH               56
#define LOKAL_SLAV_PECSI_EGYH_PATRON        57
#define LOKAL_SLAV_SZEGED_CSAN_EGYH         58
#define LOKAL_SLAV_VESZPREMI_EGYH_PATRON    59
#define LOKAL_SLAV_GYORI_SZEKESFEH_EGYH     60
#define LOKAL_SLAV_KAPORSVAR_FELSZ          61
#define LOKAL_SLAV_VACI_FELSZ               62
#define LOKAL_SLAV_KAL_KECS_FOEGYH          63
#define LOKAL_SLAV_ESZTERGOM_BUDA_FOEGYH    64
#define LOKAL_SLAV_KAL_KECS_FELSZ           65
#define LOKAL_SLAV_GYORI_SZEKESEGYH_FELSZ   66
#define LOKAL_SLAV_VACI_PATRON              67
#define LOKAL_SLAV_SZEGED_CSAN_PATRON2      68
#define LOKAL_SLAV_VESZPREM_FOEGYH          69
#define LOKAL_SLAV_KONSEKR_KOSTOLY_HU		70
#define LOKAL_SLAV_SZEGED_CSAN_EGYH2        71
#define LOKAL_SLAV_PECS_PATRON              72
#define LOKAL_SLAV_SZOMBATHELYI_PATRON      73
#define LOKAL_SLAV_SZEKESFEHERVAR_EGYH      74
#define LOKAL_SLAV_EGER_FOEGYH              75
#define LOKAL_SLAV_ESZTERGOM_EML            76
#define LOKAL_SLAV_GYOR_EGYH                77
#define LOKAL_SLAV_ESZTERGOM_FOEGYH         78
#define LOKAL_SLAV_EGER_FOEGYH2             79
#define LOKAL_SLAV_VESZPREM_FOEGYH_T        80
#define LOKAL_SLAV_SZATMAR                  81
#define LOKAL_SLAV_CESKO_BRNO               82
#define LOKAL_SLAV_SVIATOK_OP_ZENY          83
#define LOKAL_SLAV_ZILINA                   84
#define LOKAL_SLAV_OPRAEM_SVIATOK_STRAHOV   85
#define LOKAL_SLAV_OPRAEM_SLAVNOST_TEPLA    86
#define LOKAL_SLAV_OPRAEM_NOVA_RISE         87
#define LOKAL_SLAV_OPRAEM_STRAHOV_NOVA_RISE 88
#define LOKAL_SLAV_OPRAEM_ZELIV             89
#define LOKAL_SLAV_OPRAEM_STRAHOV           90
#define LOKAL_SLAV_SZ_LASZLO                91
#define LOKAL_SLAV_SLAVNOST_OSC             92
#define LOKAL_SLAV_SVIATOK_OFMCONV          93
#define LOKAL_SLAV_SVIATOK_OFS              94
#define LOKAL_SLAV_SPOMIENKA_OFMCONV_OFMCAP 95
#define LOKAL_SLAV_SPOMIENKA_OSC            96
#define LOKAL_SLAV_NEDOVOLENE_SK            97
#define LOKAL_SLAV_KATONAI_ORDINARIAT       98
#define LOKAL_SLAV_DEBR_NYIREGY             99
#define LOKAL_SLAV_OPRAEM_DOKSANY          100
#define LOKAL_SLAV_OPRAEM_DOKSANY_ZELIV    101
#define LOKAL_SLAV_OPRAEM_TEPLA            102
#define LOKAL_SLAV_KONGREGACIA_SMBM        103
#define LOKAL_SLAV_SPOMIENKA_FMA_CZ	       104
#define LOKAL_SLAV_LUB_SPOMIENKA_FMA_CZ    105
#define LOKAL_SLAV_SVIATOK_VDB_CZ          106
#define LOKAL_SLAV_SLAVNOST_FMA_CZ         107
#define LOKAL_SLAV_SZEGED_CSAN_EGYH3       108
#define LOKAL_SLAV_ORDINARIAT              109

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

/* INCREMENT_FOR_NEW_CALENDAR */
#define POCET_KALENDAROV                   17
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
	/* ToDo */ KALENDAR_VSEOBECNY,
	KALENDAR_NEURCENY,
	KALENDAR_CZ_OP,
	KALENDAR_VSEOBECNY_HU,
	KALENDAR_VSEOBECNY_RU,
	/* ADD_VALUE_FOR_NEW_LANGUAGE */
};

// filenames for special calendars / názov súbora pre kalendáre
extern const char *nazov_htm_kalendar[POCET_KALENDAROV + 1];

extern const char *nazov_kalendara_long[POCET_KALENDAROV + 1];

// prikazany / neprikazany sviatok / ľubovoľná spomienka bez záväznosti (blahoslavení napr. pre SK_OP)
#define PRIKAZANY_SVIATOK           0
#define NIE_JE_PRIKAZANY_SVIATOK    1
#define VOLNA_LUBOVOLNA_SPOMIENKA   2 // pre SK OP; v kalendári značené kurzívou (bez popisu "ľubovoľná spomienka"); 2012-04-01

// div, mod: delenie pre short int
#define DIV	/
#define MOD	%

// dodefinované rôzne správanie funkcie zaltar_zvazok();
#define	ZALTAR_VSETKO                0
#define ZALTAR_IBA_ZALMY             1
#define ZALTAR_IBA_ZALMY_HYMNUS_MCD  2
#define ZALTAR_ANT_ZALMY_HYMNUS_MCD  3

// charset constants
#define CHARSET_UTF_8               0
#define CHARSET_WINDOWS_1250        1

#define POCET_CHARSET               1

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
extern const char *nazov_farby_jazyk[POCET_FARIEB_REALNYCH + 1][POCET_JAZYKOV + 1];
#define		nazov_farby(a)	nazov_farby_jazyk[a][_global_jazyk]

extern const char *html_farba_pozadie[POCET_FARIEB_REALNYCH + 1];
extern const char *html_farba_popredie[POCET_FARIEB_REALNYCH + 1];

// juliansky datum, funkcia juliansky_datum, dane synonymum JD
#define	JD	juliansky_datum

#define ZVAZKY_LH 4

// tyzden zaltara (1, 2, 3, 4) podla tyzdna t
#define  tyzden_zaltara(t)  ((((t) + 3) % 4) + 1)
extern const char *rimskymi_tyzden_zaltara[ZVAZKY_LH + 1];

extern const short int prvy_den[12];

extern short int pocet_dni[12];

extern const char char_nedelne_pismeno[POCET_DNI];

#define POCET_NEDELNY_CYKLUS 3
extern const char char_nedelny_cyklus[POCET_NEDELNY_CYKLUS];

#define	ROK_1968		1968
#define	JUL_DATE_0_JAN_1968	2439856L // juliansky datum pre 0. januar 1968

#define	POCET_DNI_V_ROKU	365

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

extern const char *nazov_dna_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_dna(a)	nazov_dna_jazyk[a][_global_jazyk]

extern const char *nazov_dna_asci_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_dna_asci(a)	nazov_dna_asci_jazyk[a][_global_jazyk]

extern const char *nazov_Dna_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_Dna(a)	nazov_Dna_jazyk[a][_global_jazyk]

extern const char *nazov_DNA_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_DNA(a)	nazov_DNA_jazyk[a][_global_jazyk]

extern const char *nazov_Dn_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_Dn(a)	nazov_Dn_jazyk[a][_global_jazyk]

extern const char *nazov_DN_asci[POCET_DNI + 1];
extern const char *nazov_dn_asci[POCET_DNI + 1];

extern const char *nazov_mesiaca_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_mesiaca(a)	nazov_mesiaca_jazyk[a][_global_jazyk]

extern const char *nazov_mesiaca_asci_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_mesiaca_asci(a)	nazov_mesiaca_asci_jazyk[a][_global_jazyk]

extern const char *nazov_Mesiaca_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_Mesiaca(a)	nazov_Mesiaca_jazyk[a][_global_jazyk]

extern const char *nazov_MESIACA_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_MESIACA(a)	nazov_MESIACA_jazyk[a][_global_jazyk]

// genitív názvu mesiaca kvôli latinčine
extern const char *nazov_mesiaca_gen_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_mesiaca_gen(a)	nazov_mesiaca_gen_jazyk[a][_global_jazyk]

extern const char *nazov_Mesiaca_gen_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_Mesiaca_gen(a)	nazov_Mesiaca_gen_jazyk[a][_global_jazyk]

extern const char *nazov_MES[POCET_MESIACOV + 1];
extern const char *nazov_mes[POCET_MESIACOV + 1];

#define		POCET_TYZDNOV 34

extern const char *poradie_Slovom_jazyk[POCET_TYZDNOV + 1][POCET_JAZYKOV + 1];
#define		poradie_Slovom(a)	poradie_Slovom_jazyk[a][_global_jazyk]

extern const char *poradie_SLOVOM_jazyk[POCET_TYZDNOV + 1][POCET_JAZYKOV + 1];
#define		poradie_SLOVOM(a)	poradie_SLOVOM_jazyk[a][_global_jazyk]

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

#undef YES
#undef NO
#define YES 1
#define NO  0

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
extern _struct_dm *(_global_svaty_ptr[MAX_POCET_SVATY]); // an array of '_struct_dm' pointers
#define _global_svaty(i) (*(_global_svaty_ptr[i - 1]))
#define _global_svaty1 (*_global_svaty_ptr[0])
#define _global_svaty2 (*_global_svaty_ptr[1])
#define _global_svaty3 (*_global_svaty_ptr[2])
#define _global_svaty4 (*_global_svaty_ptr[3])
#define _global_svaty5 (*_global_svaty_ptr[4])

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

// globalna premenna, do ktorej ukladaju funkcie vytvor_query_string_... linku tvaru PATH_CGI(SCRIPT_NAME) ++ "?param1=val&param2=val&..."
extern char *_global_link_ptr;
#define _global_link _global_link_ptr

extern char *_global_pom_str; // pomocny string pre velke pismena

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

// globálna premenná -- pole -- obsahujúca options; pôvodne to boli globálne premenné _global_opt 1..9 atď., obsahujú pom_MODL_OPT...
extern int _global_opt[POCET_GLOBAL_OPT];
// globálna premenná -- pole -- obsahujúca force options; pôvodne to boli globálne premenné _global_optf 1..9 atď., obsahujú pom_MODL_OPTF...
extern int _global_optf[POCET_GLOBAL_OPT];

// for function strcat_str_modl_opt_bit_order()
#define USE_STR_MODL_OPT                   -2
#define USE_STR_MODL_OPTF                  -1

#define POCET_OPT_0_SPECIALNE               9 // jednotlivé komponenty option 0 -- bity pre force option 0
extern int _global_opt_specialne[POCET_OPT_0_SPECIALNE];
// 2011-04-08: úprava významu (a interpretácie) option 0 ==  OPT_0_SPECIALNE (zobraziť/nezobraziť "pridanú hodnotu" oproti papierovej LH)
#define BIT_OPT_0_VERSE                     1
#define BIT_OPT_0_REFERENCIE                2
#define BIT_OPT_0_CITANIA                   4
#define BIT_OPT_0_ZJAVENIE_PANA_NEDELA      8 // či sa Zjavenie Pána slávi v nedeľu (1) alebo nie (teda 6. januára; hodnota 0 == default)
#define BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA  16 // či sa Nanebovstúpenie Pána slávi v nedeľu (1) alebo nie (teda vo štvrtok, na 40.-ty deň po Veľkonočnej nedeli; hodnota 0 == default)
#define BIT_OPT_0_TELAKRVI_NEDELA          32 // či sa Najsv. Kristovho tela a krvi slávi v nedeľu (1) alebo nie (teda vo štvrtok, 11.-ty deň po Zoslaní Ducha Sv.; hodnota 0 == default)
#define BIT_OPT_0_FONT_NORMAL              64 // force font-weight: normal; // should be logically among OPT_2_HTML_EXPORT bit-options
#define BIT_OPT_0_BUTTONS_ORDER           128 // buttons order: 0 = date navigation BEFORE info on day (default for web); 1 = day details first (with prayer buttons) (default for mobile apps)
#define BIT_OPT_0_BLIND_FRIENDLY          256 // blind-friendly mode: 1 = use special CSS override to hide all red texts (rubrics)

#define POCET_OPT_1_CASTI_MODLITBY         15 // jednotlivé komponenty option 1 -- bity pre force option 1
extern int _global_opt_casti_modlitby[POCET_OPT_1_CASTI_MODLITBY];
// 2011-04-11: úprava významu (a interpretácie) option 1 == OPT_1_CASTI_MODLITBY (zobraziť/nezobraziť najmä pevné/nemenné súčasti modlitieb, ale aj iné, čo sú/nie sú v LH)
// 2011-10-10: úprava niektorých bitov, posunutie popisu na koniec
#define BIT_OPT_1_TEDEUM                    1
#define BIT_OPT_1_RUBRIKY                   2
#define BIT_OPT_1_CHVALOSPEVY               4
#define BIT_OPT_1_SLAVA_OTCU                8
#define BIT_OPT_1_OTCENAS                  16
#define BIT_OPT_1_MCD_DOPLNKOVA            32 // používa sa pre modlitbu cez deň -- 1 = alternatívna, doplnková psalmódia
#define BIT_OPT_1_PC_VIGILIA               64
#define BIT_OPT_1_SPOMIENKA_SPOL_CAST     128 // pri slávení spomienky možno podľa všeobecných smerníc, č. 235 b), vziať niektoré časti alebo zo spoločnej časti (1), alebo zo dňa (0)
#define BIT_OPT_1_PLNE_RESP               256
#define BIT_OPT_1_ZALM95                  512 // používa sa pre ranné chvály a vešpery -- 1 = vziať namiesto žalmov 24, 67, 100 žalm 95 (0 = brať príslušný žalm 24, 67 resp. 100)
#define BIT_OPT_1_PROSBY_ZVOLANIE        1024 // zvolanie v prosbách zobraziť (opakovať) po každej prosbe
#define BIT_OPT_1_SKRY_POPIS             2048
#define BIT_OPT_1_ZOBRAZ_SPOL_CAST       4096
#define BIT_OPT_1_VESP_KRATSIE_PROSBY    8192 // použiť (pre ktorýkoľvek deň v roku) kratšie prosby k vešperám z dodatku (0 = default, zo dňa)
#define BIT_OPT_1_MCD_ZALTAR_TRI        16384 // používa sa pre modlitbu cez deň -- 1 = psalmódia sa používa z troch týždňov žaltára (aktuálny, predchádzajúci, nasledujúci)

#define POCET_OPT_2_HTML_EXPORT            16 // jednotlivé komponenty option 2 -- bity pre force option 2
extern int _global_opt_html_export[POCET_OPT_2_HTML_EXPORT];
// 2011-04-12: úprava významu (a interpretácie) option 2 (rozličné prepínače pre [online aj offline] export, napr. tlačidlá, zobrazenie dátumov a podobne)
// 2012-10-01: doplnené ďalšie komponenty najmä pre vzhľad úvodnej obrazovky
#define BIT_OPT_2_ISO_DATUM                 1 // zobrazovať dátum v ISO formáte YYYY-MM-DD (0 = iba číslo dňa)
#define BIT_OPT_2_BUTTON_PRVE_VESPERY       2 // zobrazovať prvé vešpery (a kompletórium po nich) pre ten deň, pre ktorý patria (teda pre nedeľu/slávnosť)
#define BIT_OPT_2_FONT_FAMILY               4 // 0 = Serif, 1 = Sans Serif
#define BIT_OPT_2_FONT_NAME_CHOOSER         8 // zobraziť drop-down list s možnosťou voľby font (family) name
#define BIT_OPT_2_FONT_SIZE_CHOOSER        16 // zobraziť drop-down list s možnosťou voľby veľkosti fontu
#define BIT_OPT_2_NAVIGATION               32 // zobraziť navigáciu v modlitbe (predošlá, nasledovná modlitba a pod.)
#define BIT_OPT_2_TEXT_WRAP                64 // zobraziť zalomenie v textoch modlitby podľa tlačenej LH
#define BIT_OPT_2_BUTTONY_USPORNE         128 // zobraziť buttony pre modlitby v úspornej podobe (tabuľka) kvôli mobilným zariadeniam
#define BIT_OPT_2_NOCNY_REZIM             256 // zobraziť invertovane farby (biele na ciernom)
#define BIT_OPT_2_ROZNE_MOZNOSTI          512 // zobraziť rozličné "hypertextové odkazy" v modlitbe (napr. pre modlitbu cez deň možnosť doplnkovej psalmódie)
#define BIT_OPT_2_HIDE_NAVIG_BUTTONS     1024 // možnosť zobraziť/skryť navigáciu (tlačidlá) v modlitbe a pre "dnes", ak je zvolený 6. bit (BIT_OPT_2_NAVIGATION)
#define BIT_OPT_2_HIDE_KALENDAR          2048 // skryť kalendárik pre "dnes" (0 = zobraziť)
#define BIT_OPT_2_HIDE_OPTIONS1          4096 // skryť html_text_dalsie_moznosti_1[] pre "dnes" (0 = zobraziť)
#define BIT_OPT_2_HIDE_OPTIONS2          8192 // skryť html_text_dalsie_moznosti_2[] pre "dnes" (0 = zobraziť)
#define BIT_OPT_2_ALTERNATIVES          16384 // ukázať iba jednu alternatívu (0 = ako doteraz; buď systém vyberie, alebo ukáže všetky možnosti)
#define BIT_OPT_2_SHOW_DEFAULT_CALENDAR 32768 // ukázať v podnadpise, metódou init_global_string(), aj default regionálny kalendár (0 = po novom, neukazovať; 1 = po starom, ukázať)

#define POCET_OPT_4_OFFLINE_EXPORT          4 // jednotlivé komponenty option 4 -- bity pre force option 4
extern int _global_opt_offline_export[POCET_OPT_4_OFFLINE_EXPORT];
// 2011-04-08: úprava významu (a interpretácie) option 4 (rozličné prepínače pre offline export, napr. aj batch mód)
#define BIT_OPT_4_MESIAC_RIADOK             1 // mesiac jednoducho (default: nie jednoducho, ale HTML pekne pre web) alebo pekne "zložito"
#define BIT_OPT_4_FNAME_MODL_ID             2 // či pre názov súboru použiť (číselné) ID modlitby alebo písmenko modlitby (default)
#define BIT_OPT_4_EXCLUDE_MCD_KOMPLET       4 // či sa pri generovaní tlačidla pre predchádzajúcu/nasledujúcu modlitbu majú preskočiť odkazy na MCD a kompletórium v metóde _buttons_prev_up_next() [default: 0 = nie; treba nastavovať kvôli ľubovoľným spomienkam do batch módu]
#define BIT_OPT_4_DO_NOT_USE_BUTTON         8 // whether do not use HTML_BUTTON_BEGIN..HTML_BUTTON_END for offline HTML export

#define POCET_OPT_5_ALTERNATIVES           14 // jednotlivé komponenty option 5 -- bity pre force option 5
extern int _global_opt_alternatives[POCET_OPT_5_ALTERNATIVES];
#define BIT_OPT_5_HYMNUS_KOMPL              1 // hymnus na kompletórium (Cezročné obdobie, A/B)
#define BIT_OPT_5_HYMNUS_PC                 2 // hymnus pre posvätné čítanie (Cezročné obdobie, I./II.)
#define BIT_OPT_5_HYMNUS_MCD_PREDPOL        4 // hymnus pre modlitbu cez deň, predpoludním (Cezročné obdobie)
#define BIT_OPT_5_HYMNUS_MCD_NAPOL          8 // hymnus pre modlitbu cez deň, napoludnie (Cezročné obdobie)
#define BIT_OPT_5_HYMNUS_MCD_POPOL         16 // hymnus pre modlitbu cez deň, popoludní (Cezročné obdobie)
#define BIT_OPT_5_DOPLNK_PSALM_122_129     32 // pre modlitbu cez deň v doplnkovej psalmódii namiesto žalmu 122 možno brať žalm 129
#define BIT_OPT_5_DOPLNK_PSALM_127_131     64 // pre modlitbu cez deň v doplnkovej psalmódii namiesto žalmu 127 možno brať žalm 131
#define BIT_OPT_5_DOPLNK_PSALM_126_129    128 // pre modlitbu cez deň v doplnkovej psalmódii namiesto žalmu 126 možno brať žalm 129
#define BIT_OPT_5_HYMNUS_VN_PC            256 // hymnus pre posvätné čítanie (Veľkonočné obdobie I. po Oktáve: nedeľný alebo z férie)
#define BIT_OPT_5_HYMNUS_VN_RCH           512 // hymnus pre ranné chvály (Veľkonočné obdobie I. po Oktáve: nedeľný alebo z férie)
#define BIT_OPT_5_HYMNUS_VN_VESP         1024 // hymnus pre vešpery (Veľkonočné obdobie I. po Oktáve: nedeľný alebo z férie)
#define BIT_OPT_5_HYMNUS_1VESP           2048 // hymnus pre prvé vešpery (Cezročné obdobie: nedeľný alebo z posv. čítania)
#define BIT_OPT_5_POPOL_STREDA_PSALMODIA 4096 // psalmódia pre ranné chvály popolcovej stredy (default: streda 4. týždňa žaltára; možnosť zvoliť z piatka 3. týždňa žaltára)
#define BIT_OPT_5_CZ_HYMNY_VYBER         8192 // CZ: hymny z breviáře ("písničky") nebo k volnému výběru (podle LA, "Renč")

#define MAX_POCET_OPT                      16 // malo by to byť aspoň maximum z POCET_OPT_0_... až POCET_OPT_5_...

const short int pocet_opt[POCET_GLOBAL_OPT] = {POCET_OPT_0_SPECIALNE, POCET_OPT_1_CASTI_MODLITBY, POCET_OPT_2_HTML_EXPORT, 0 /* option 3 nemá bitové komponenty */, POCET_OPT_4_OFFLINE_EXPORT, POCET_OPT_5_ALTERNATIVES};

// globalna premenna, co obsahuje string vypisany na obsazovku
extern char *_global_string;
extern char *_global_string2; // obsahuje I, II, III, IV, V alebo pismeno roka
extern char *_global_string_farba; // 2006-08-19: doplnené

extern char *_global_buf; // 2006-08-01: túto premennú tiež alokujeme
extern char *_global_buf2; // 2006-08-01: túto premennú tiež alokujeme

extern short int _global_linky;

extern short int _global_jazyk;

extern short int _global_kalendar;

extern short int _global_css;

extern short int _global_font;
extern short int _global_font_size;

extern short int _global_pocet_zalmov_kompletorium;

extern const char *nazov_jazyka[POCET_JAZYKOV + 1];
extern const char *skratka_jazyka[POCET_JAZYKOV + 1];
extern const char *postfix_jazyka[POCET_JAZYKOV + 1];
extern const char *skratka_jazyka_title[POCET_JAZYKOV + 1];

extern const char *nazov_kalendara_short[POCET_KALENDAROV + 1];
extern const char *skratka_kalendara[POCET_KALENDAROV + 1];

extern const char *nazov_css[POCET_CSS + 1];
extern const char *skratka_css[POCET_CSS + 1];
extern const char *nazov_css_invert_colors;
extern const char *nazov_css_normal_font_weight;
extern const char *nazov_css_blind_friendly;

extern const short int charset_jazyka[POCET_JAZYKOV + 1];
extern const char *nazov_charset[POCET_CHARSET + 1];

extern const char *nazov_fontu[POCET_FONTOV + 1];
extern const char *nazov_fontu_CHECKBOX[POCET_JAZYKOV + 1];
extern const char *nazov_fontu_CSS[POCET_FONTOV + 1];

extern const char *nazov_font_size_jazyk[POCET_FONT_SIZE + 1][POCET_JAZYKOV + 1];
extern const char *nazov_font_size_css[POCET_FONT_SIZE + 1];

//---------------------------------------------------------------------

short int _allocate_global_var(void);
short int _deallocate_global_var(void);

short int cislo_mesiaca(char *mesiac);
char *caps_BIG(const char *input);
char *remove_diacritics(const char *input);
char *convert_nonbreaking_spaces(const char *input);

char *_vytvor_string_z_datumu(short int den, short int mesiac, short int rok, short int _case, short int typ, short int align);
// podľa toho, ako sa funkcia volá, určím case (použitie veľkých/malých písmen)
#define vytvor_global_link(den, mesiac, rok, typ, align)	_vytvor_global_link(den, mesiac, rok, CASE_case, typ, align)
#define vytvor_global_link_class_new(den, mesiac, rok, typ, align, html_class, nazov_dna)	_vytvor_global_link(den, mesiac, rok, CASE_case, typ + LINK_SHIFT, align, html_class, nazov_dna)
#define vytvor_global_link_class(den, mesiac, rok, typ, align, html_class)	_vytvor_global_link(den, mesiac, rok, CASE_case, typ, align, html_class)
#define Vytvor_global_link(den, mesiac, rok, typ, align)	_vytvor_global_link(den, mesiac, rok, CASE_Case, typ, align)
#define VYTVOR_global_link(den, mesiac, rok, typ, align)	_vytvor_global_link(den, mesiac, rok, CASE_CASE, typ, align)
// 2011-05-11: doplnený nový parameter align -- či zarovnať jednociferné dátumy (číslovka dňa) medzerou zľava
void _vytvor_global_link(short int den, short int mesiac, short int rok, short int _case, short int typ, short int align);
void _vytvor_global_link(short int den, short int mesiac, short int rok, short int _case, short int typ, short int align, const char * html_class);
void _vytvor_global_link(short int den, short int mesiac, short int rok, short int _case, short int typ, short int align, const char * html_class, const char * nazov_dna);

#define PRILEP_REQUEST_OPTIONS_DEFAULT   0
#define PRILEP_REQUEST_OPTIONS_AJ_FORCE  1
#define PRILEP_REQUEST_OPTIONS_LEN_FORCE 2
void prilep_request_options(char pom2 [MAX_STR], char pom3 [MAX_STR], short int force_opt = PRILEP_REQUEST_OPTIONS_DEFAULT); // 2013-03-07: pokus; pravdepodobne PRILEP_REQUEST_OPTIONS_LEN_FORCE je neužitočné a PRILEP_REQUEST_OPTIONS_AJ_FORCE možno trocha riskantné...

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
	a.denvr = 1;  \
	a.litrok = 'A'; \
	a.tyzden = 1;   \
	a.tyzzal = 1;   \
	a.litobd = OBD_CEZ_ROK; \
	a.typslav = SLAV_NEURCENE; \
	a.typslav_lokal = LOKAL_SLAV_NEURCENE; \
	a.smer = 99; \
	a.prik = NIE_JE_PRIKAZANY_SVIATOK; \
	a.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA); \
	mystrcpy(a.meno, STR_UNDEF, MENO_SVIATKU); \
	a.farba = LIT_FARBA_NEURCENA; \
	a.kalendar = KALENDAR_NEURCENY; \
	mystrcpy(a.lc_str_id, STR_EMPTY, MAX_LC_STR_ID); \
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
	_INIT_ANCHOR_AND_FILE(a.hymnus); \
	_INIT_ANCHOR_AND_FILE(a.antifona1); \
	_INIT_ANCHOR_AND_FILE(a.zalm1); \
	_INIT_ANCHOR_AND_FILE(a.antifona2); \
	_INIT_ANCHOR_AND_FILE(a.zalm2); \
	_INIT_ANCHOR_AND_FILE(a.kcitanie); \
	_INIT_ANCHOR_AND_FILE(a.kresponz); \
	_INIT_ANCHOR_AND_FILE(a.nunc_dimittis); \
	_INIT_ANCHOR_AND_FILE(a.modlitba); \
};

#define _INIT_TMODLITBA4(a) {\
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

int _encode_spol_cast(short int, short int, short int);
int _encode_spol_cast(short int, short int);
int _encode_spol_cast(short int);
_struct_sc _decode_spol_cast(int);

void strcat_str_modl_opt_bit_order(char str_to_append[SMALL], short opt, short bit_order);

extern const char *text_JAN_KRST[POCET_JAZYKOV + 1];
extern const char *text_POPOLCOVA_STREDA[POCET_JAZYKOV + 1];
extern const char *text_NANEBOVSTUPENIE_PANA[POCET_JAZYKOV + 1];
extern const char *text_VELKONOCNA_NEDELA[POCET_JAZYKOV + 1];
extern const char *text_NEDELA_PANOVHO_ZMRTVYCHVSTANIA[POCET_JAZYKOV + 1];
extern const char *text_NEDELA_VO_VELKONOCNEJ_OKTAVE[POCET_JAZYKOV + 1];
extern const char *text_DEN_VO_VELKONOCNEJ_OKTAVE[POCET_JAZYKOV + 1];
extern const char *text_NAJSVATEJSEJ_TROJICE[POCET_JAZYKOV + 1];
extern const char *text_KRISTA_KRALA[POCET_JAZYKOV + 1];
extern const char *text_NAJSV_KRISTOVHO_TELA_A_KRVI[POCET_JAZYKOV + 1];
extern const char *text_NAJSV_SRDCA_JEZISOVHO[POCET_JAZYKOV + 1];
extern const char *text_NEPOSKVRNENEHO_SRDCA_PM[POCET_JAZYKOV + 1];
extern const char *text_NARODENIE_PANA[POCET_JAZYKOV + 1];
extern const char *text_ZOSLANIE_DUCHA_SVATEHO[POCET_JAZYKOV + 1];
extern const char *text_PRVA_ADVENTNA_NEDELA[POCET_JAZYKOV + 1];
extern const char *text_NEDELA_SV_RODINY[POCET_JAZYKOV + 1];
extern const char *text_SPOMIENKA_PM_V_SOBOTU[POCET_JAZYKOV + 1];
extern const char *text_ZELENY_STVRTOK[POCET_JAZYKOV + 1];
extern const char *text_VELKY_PIATOK[POCET_JAZYKOV + 1];
extern const char *text_BIELA_SOBOTA[POCET_JAZYKOV + 1];
extern const char *text_KVETNA_NEDELA[POCET_JAZYKOV + 1];
extern const char *text_DRUHA_NEDELA_PO_NAR_PANA[POCET_JAZYKOV + 1];
extern const char *text_PO_POPOLCOVEJ_STREDE[POCET_JAZYKOV + 1];
extern const char *text_V_OKTAVE_NARODENIA[POCET_JAZYKOV + 1];

extern const char *text_DEC_08[POCET_JAZYKOV + 1];
extern const char *text_AUG_15[POCET_JAZYKOV + 1];
extern const char *text_NOV_01[POCET_JAZYKOV + 1];

extern const char *text_ZAKONCENIE_SKRZE_dlhe[POCET_JAZYKOV + 1];
extern const char *text_ZAKONCENIE_SKRZE_kratke[POCET_JAZYKOV + 1];
extern const char *text_ZAKONCENIE_LEBO_ON_dlhe[POCET_JAZYKOV + 1];
extern const char *text_ZAKONCENIE_LEBO_ON_kratke[POCET_JAZYKOV + 1];
extern const char *text_ZAKONCENIE_LEBO_TY_dlhe[POCET_JAZYKOV + 1];
extern const char *text_ZAKONCENIE_LEBO_TY_kratke[POCET_JAZYKOV + 1];
extern const char *text_ZAKONCENIE_ON_JE_dlhe; // len SK
extern const char *text_ZAKONCENIE_ON_JE_kratke; // len SK
extern const char *text_ZAKONCENIE_KTORY_JE_dlhe; // len SK
extern const char *text_ZAKONCENIE_KTORY_JE_kratke; // len SK
extern const char *text_ZAKONCENIE_O_TO_TA_PROSIME[POCET_JAZYKOV + 1];

extern const char *text_PRO_OP[POCET_JAZYKOV + 1];

extern const char *html_text_batch_Back[POCET_JAZYKOV + 1];
extern const char *html_text_batch_Prev[POCET_JAZYKOV + 1];
extern const char *html_text_batch_Next[POCET_JAZYKOV + 1];

#endif // __LITURGIA_H_


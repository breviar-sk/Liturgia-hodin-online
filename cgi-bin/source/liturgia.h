/***************************************************************/
/*                                                             */
/* liturgia.h                                                  */
/* (c)1999-2013 | Juraj VidÈky | videky@breviar.sk             */
/*                                                             */
/* description | obsahuje zakladne vecicky pre liturgiu hodin  */
/* document history                                            */
/*   01/11/1999A.D. | created                                  */
/*   01/02/2000A.D. | modified                                 */
/*   18/02/2000A.D. | trosku prekopane | stringove kontanty su */
/*                    tu iba deklarovane; definovane v hodin.h */
/*   06/09/2001A.D. | tento popis                              */
/*   2003-07-02a.D. | pridana LINK_DEN_MESIAC_ROK_PRESTUP      */
/*                    kvoli prestupnym rokom (iny _global_link)*/
/*   2003-07-15a.D. | rozne definicie pre modlitbu cez den     */
/*   2003-07-15a.D. | odstraneny #include "mybase.h"           */
/*   2003-08-06a.D. | rozne definicie pre posvatne citanie     */
/*   2003-08-07a.D. | pridana void _init_dm co nastavi dummy   */
/*   2003-08-11a.D. | -Wall upozornila na / * within comments  */
/*   2003-08-11a.D. | void _init_dm zapoznamkovana             */
/*   2003-08-13a.D. | pridane logy pre modlitbu cez den        */
/*                  - pridane MODL_CEZ_DEN_VSETKY              */
/*   2003-08-21a.D. | definicie pre posvatne citania           */
/*   2003-11-20a.D. | definicie pre posvatne citania zmenene   */
/*   2004-04-28a.D. | MAX_STR_AF_FILE zmenene na 16            */
/*   2004-08-14a.D. | char zmeneny na unsigned (_nedelne_p...) */
/*   2005-03-27a.D. | CHAR_MODL_* z funkcie pismenko_modlitby  */
/*   2005-07-27a.D. | pridanÈ nazov_slavenia_lokal[]           */
/*   2005-08-05a.D. | pridanÈ zvazok_OBD[]                     */
/*   2005-11-11a.D. | DoplnenÈ parametre pre Te Deum           */
/*   2006-02-07a.D. | ZALTAR_... pre funkciu zaltar_zvazok();  */
/*   2006-07-11a.D. | prvÈ kroky k jazykov˝m mut·ci·m          */
/*   2006-08-01a.D. | zmenenÈ definÌcie konöt·nt (jaz.mut·cie) */
/*   2006-08-07a.D. | pridanÈ sv. muûov/ûien, Ëo ûili v manû.  */
/*   2006-08-18a.D. | zmena int na short int (staËÌ 32tis.)    */
/*   2006-08-19a.D. | pridanie liturgickej farby               */
/*   2006-10-11a.D. | pre invitatÛrium a kompletÛrium          */
/*   2006-10-13a.D. | jazykovo z·vislÈ je aj nazov_Modlitby    */
/*   2006-12-12a.D. | doplnenie latinËiny (la)                 */
/*   2007-06-01a.D. | niektorÈ definy presunutÈ do mydefs.h    */
/*   2007-06-28a.D. | doplnenÈ: PARAM_TEDEUM_BEGIN aj _END     */
/*   2007-10-02a.D. | doplnenÈ: PARAM_SKRY_ANTIFONU_BEGIN/END  */
/*                  - tieû PARAM_ANTIFONA1x a PARAM_ANTIFONA3x */
/*   2008-01-03a.D. | doplnenÈ text_DRUHA_NEDELA_PO_NAR_PANA[] */
/*   2008-01-05a.D. | doplnenÈ text_PO_POPOLCOVEJ_STREDE[]     */
/*                  - a tieû text_V_OKTAVE_NARODENIA[]         */
/*   2008-01-23a.D. | opravenÈ pole konöt·nt zvazok_breviara[] */
/*   2008-06-24a.D. | doplnenÈ LOKAL_SLAV_SPIS_BA_PATRON       */
/*   2008-08-15a.D. | pridan˝ ÔalöÌ "jazyk" (cz-op)            */
/*   2009-01-29a.D. | pridan˝ ÔalöÌ jazyk - maÔarËina (hu)     */
/*   2009-04-08a.D. | zakonËenie modlitby trojakÈ (kr·tke/dlhÈ)*/
/*   2009-05-15a.D. | pridanÈ text_PRO_OP[]                    */
/*   2009-12-14a.D. | zakonËenie modlitby s mal˝m pÌsmenkom na zaËiatku */
/*   2010-03-16a.D. | doplnenÈ LOKAL_SLAV_BRATISLAVA           */
/*   2010-05-17a.D. | pridanÈ niektorÈ maÔarskÈ sl·venia       */
/*   2010-05-21a.D. | doplnenÈ: PARAM_SPOMIENKA_PRIVILEG_BEGIN/END */
/*   2010-08-03a.D. | do ötrukt˙ry "dm" pridan· premenn· pre   */
/*                    öpecifik·ciu, o ak˝ kalend·r ide:        */
/*                    vöeobecn˝ danej cirkevnej provincie      */
/*                    alebo nejak˝ rehoæn˝ a pod.              */
/*   2010-10-11a.D. | pridanÈ nazov_kalendara_long[]           */
/*   2011-01-25a.D. | premenovanÈ niektorÈ HTML s˙bory         */
/*   2011-04-13a.D. | reùazcovÈ funkcie equals() presunutÈ     */
/*   2011-05-11a.D. | vytvorenÈ: _vytvor_string_z_datumu()     */
/*   2011-10-07a.D. | vymenenÈ konötanty RCH <-> posv.ËÌt.     */
/*   2013-01-29a.D. | option 5 pre alternatÌvy v textoch       */
/*                                                             */
/*                                                             */
/***************************************************************/

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

// 2006-07-11: PridanÈ kvÙli jazykov˝m mut·ci·m 
// 2006-12-12: Pridan· latinËina, kÛdy s˙ podæa ISO 639-1 (aû na Ëeötinu)
// 2008-08-15: Pridan· "dominik·nska Ëeötina"; presunutÈ sem bezprostredne za definÌciu POCET_JAZYKOV
// 2009-01-29: pridan· maÔarËina
#define JAZYK_SK	0
#define JAZYK_CZ	1
#define JAZYK_EN	2
#define JAZYK_LA    3
#define JAZYK_UNDEF 4
#define JAZYK_CZ_OP 5
#define JAZYK_HU    6

// 2011-05-12: form·ty vypisovania d·tumu, kvÙli maÔarËine, angliËtine...
#define FORMAT_DATUMU_DEN_MESIAC_ROK 0 // DD. MM RRRR
#define FORMAT_DATUMU_MESIAC_DEN_ROK 1 // MM DD RRRR
#define FORMAT_DATUMU_ROK_MESIAC_DEN 2 // RRRR. MM DD

extern const short int format_datumu[POCET_JAZYKOV + 1];

// 2008-08-15: PridanÈ POCET_CSS, aby mohol byù "dolnÌk" (CSS_UNDEF) hodnota 0
#define POCET_CSS	11
// 2006-08-08: PridanÈ kvÙli rÙznym css-k·m 
// 2009-04-02: pridanÈ historickÈ css-k·
// 2010-02-25: pridanÈ css pre webstr·nky http://www.jm-krize.cz/
// 2011-05-24: pridan˝ "inverzn˝" öt˝l pre mobilnÈ zariadenia (Ëierne pozadie, biely text)
// 2011-07-26: pridan˝ vzhæad ako http://www.kbs.sk
#define CSS_UNDEF				0
#define CSS_breviar_sk			1
#define CSS_breviar_sk_invert	2
#define CSS_kbd_sk				3
#define CSS_ebreviar_cz			4
#define CSS_breviar_cz_op		5
#define CSS_breviar_hist_2003	6
#define CSS_breviar_hist_2005	7
#define CSS_breviar_hist_2007	8
#define CSS_breviar_hist_2008	9
#define CSS_jm_krize_cz			10
#define CSS_kbs_sk				11

#define	POCET_FONTOV	9

// 2011-05-06: jednotlivÈ fonty na v˝ber v drop-down liste
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

#define	POCET_FONT_SIZE	8

// 2011-05-13: jednotlivÈ fonty na v˝ber v drop-down liste
#define FONT_SIZE_UNDEF		0
#define FONT_SIZE_CSS		1 // inherit
#define FONT_SIZE_XX_SMALL	2
#define FONT_SIZE_X_SMALL 	3
#define FONT_SIZE_SMALL   	4
#define FONT_SIZE_MEDIUM  	5
#define FONT_SIZE_LARGE   	6
#define FONT_SIZE_X_LARGE 	7
#define FONT_SIZE_XX_LARGE	8

// 2013-01-29: alternatÌvy pre niektorÈ Ëasti modlitby
#define BIT_ALT_HYMNUS                  1
#define BIT_ALT_ANTCHVAL                2
#define BIT_ALT_LEN_DOPLNKOVA_PSALMODIA 4
#define BIT_ALT_DOPLNK_PSALM_122_129    8
#define BIT_ALT_DOPLNK_PSALM_127_131   16

// nasledovne 2 definovane 2003-08-13; zmenene 2004-04-28 (12->16)
#define MAX_STR_AF_FILE   16
#define MAX_STR_AF_ANCHOR 23
struct _anchor_and_file{
	char file[MAX_STR_AF_FILE];
	char anchor[MAX_STR_AF_ANCHOR];
};
typedef struct _anchor_and_file _struct_anchor_and_file;

// definicie pre ranne chvaly a vespery
#define rchvalospev  zalm2
#define vchvalospev  zalm3
#define magnifikat   benediktus

// definicie pre posvatne citania upravene 2003-08-21 a opatovne 2003-11-20

// vers po psalmodii pred citaniami - je kresponz

// prve  citanie aj s responzoriom za nim
// #define	citanie1	kcitanie

// druhe citanie aj s responzoriom za nim
// #define	citanie2	benediktus

// prosby ostavaju pre posvatne citania nedefinovane

struct tmodlitba1{
	short int alternativy; // bitovÈ komponenty hovoria, ktorÈ Ëasti mÙûu maù alternatÌvy
	_struct_anchor_and_file popis     ;
	_struct_anchor_and_file hymnus    ;
	_struct_anchor_and_file antifona1 ;
	_struct_anchor_and_file zalm1     ;
	_struct_anchor_and_file antifona2 ;
	_struct_anchor_and_file zalm2     ;
	_struct_anchor_and_file antifona3 ;
	_struct_anchor_and_file zalm3     ;
	_struct_anchor_and_file kcitanie  ; // 1. citanie pre posvatne citanie
	_struct_anchor_and_file kresponz  ; 
	_struct_anchor_and_file benediktus; // antifona na benediktus/magnifikat/nunc dimittis; 2. citanie pre posvatne citanie
	_struct_anchor_and_file prosby    ; // pre posvatne citanie nedefinovane; 2011-03-16: "zneuûitÈ" (pouûitÈ) pre hagiografickÈ ËÌtanie (æubovoænej) spomienky sv‰tca v pÙste
	_struct_anchor_and_file modlitba  ;
	_struct_anchor_and_file ant_spomprivileg; // 2010-05-21: pridanÈ kvÙli spomienkam a æubovoæn˝m spomienkam v pÙstnom obdobÌ (zobrazenie po modlitbe dÚa pÙstnej fÈrie) // 2012-02-09: zovöeobecnenÈ v zmysle VSLH Ë. 238 (Spomienky pripadaj˙ce na privilegovanÈ dni)
	_struct_anchor_and_file modlitba_spomprivileg; // 2010-05-21: pridanÈ kvÙli spomienkam a æubovoæn˝m spomienkam v pÙstnom obdobÌ (zobrazenie po modlitbe dÚa pÙstnej fÈrie) // 2012-02-09: zovöeobecnenÈ v zmysle VSLH Ë. 238 (Spomienky pripadaj˙ce na privilegovanÈ dni)
};
typedef struct tmodlitba1 _type_ranne_chvaly;
typedef struct tmodlitba1 _type_vespery;
typedef struct tmodlitba1 _type_1vespery;
// typedef struct tmodlitba1 _type_posv_citanie;

struct tmodlitba2{
	short int alternativy; // bitovÈ komponenty hovoria, ktorÈ Ëasti mÙûu maù alternatÌvy
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
// pre jednoduchsiu orientaciu pridane 2003-07-15
typedef struct tmodlitba2 _type_cez_den_pred;
typedef struct tmodlitba2 _type_cez_den_na;
typedef struct tmodlitba2 _type_cez_den_po;

struct tmodlitba3{
	short int alternativy; // bitovÈ komponenty hovoria, ktorÈ Ëasti mÙûu maù alternatÌvy
	short int pocet_zalmov            ; // pridanÈ 2006-10-18; niekedy s˙ aû 2 ûalmy
	_struct_anchor_and_file popis     ; // pridanÈ 2006-10-11; zruöenÈ antifona2, zalm2 a modlitba
	_struct_anchor_and_file hymnus    ;
	_struct_anchor_and_file antifona1 ;
	_struct_anchor_and_file zalm1     ;
	_struct_anchor_and_file antifona2 ; // pridanÈ 2006-10-17; niekedy s˙ aû 2 ûalmy
	_struct_anchor_and_file zalm2     ;
	_struct_anchor_and_file kcitanie  ;
	_struct_anchor_and_file kresponz  ;
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

// 2011-03-25: pre posv‰tnÈ ËÌtanie kvÙli sl·veniu vigÌliÌ nov˝ typ
struct tmodlitba5{
	short int alternativy; // bitovÈ komponenty hovoria, ktorÈ Ëasti mÙûu maù alternatÌvy
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
	_struct_anchor_and_file citanie_spomprivileg ; // 2011-03-16: "zneuûitÈ" (pouûitÈ) pre hagiografickÈ ËÌtanie (æubovoænej) spomienky sv‰tca v pÙste; 2011-03-25: nov˝ typ -> novÈ meno
	_struct_anchor_and_file ant_chval ; // vigÌlia: antifÛna pre chv·lospevy
	_struct_anchor_and_file chval1    ; // vigÌlia: chv·lospev I
	_struct_anchor_and_file chval2    ; // vigÌlia: chv·lospev II
	_struct_anchor_and_file chval3    ; // vigÌlia: chv·lospev III
	_struct_anchor_and_file evanjelium; // vigÌlia: evanjelium
	_struct_anchor_and_file modlitba  ;
};
typedef struct tmodlitba5 _type_posv_citanie;

struct den_mesiac{ // takto povodne vyzerala struct dm
	short int den;        // cislo dna mesiaca (1--31)
	short int mesiac;     // cislo mesiaca (1--12) - in·Ë ako je potrebnÈ pre v‰Ëöinu polÌ, kde je mesiac 0--11
};
typedef struct den_mesiac _struct_den_mesiac;

#define POCET_MODLITIEB         14 // 2006-08-02: nepouûÌvalo sa; upravenÈ na 13 (z pÙvodn˝ch 8); 2011-10-03: upravenÈ na 14 kvÙli MODL_VSETKY
// modlitby; 2011-10-05: vymenenÈ rannÈ chv·ly a posv‰tnÈ ËÌtanie, reöpektujeme usporiadanie tlaËenej LH; 2011-10-07: vymenenÈ konötanty RCH<->posv.ËÌt.
#define MODL_INVITATORIUM       0
#define MODL_POSV_CITANIE       1
#define MODL_RANNE_CHVALY       2
#define MODL_CEZ_DEN_9          3
#define MODL_CEZ_DEN_12         4
#define MODL_CEZ_DEN_3          5
#define MODL_VESPERY            6
#define MODL_KOMPLETORIUM       7
#define MODL_NEURCENA           8
// dalsie, iba docasne modlitby
#define MODL_PRVE_VESPERY       9
#define MODL_PRVE_KOMPLETORIUM  10
#define MODL_DRUHE_VESPERY      11
#define MODL_DRUHE_KOMPLETORIUM 12
// formular s detailami ohladom generovania modlitby -- 2011-10-03: odstaven˝
#define MODL_DETAILY            13
// 2011-10-03: pridanÈ pokusne
#define MODL_VSETKY             14
// pre jednoduchsiu orientaciu pridane 2003-07-15
#define MODL_PREDPOLUDNIM       3
#define MODL_NAPOLUDNIE         4
#define MODL_POPOLUDNI          5
// pre modlitbu cez den kvoli zaltaru (psalmodii) rovnake, pridane 2003-08-13
#define MODL_CEZ_DEN_VSETKY     20

// 2007-12-05: doplnenÈ kvÙli modlitbe kompletÛria, funkcia _set_kompletorium_nedela()
#define MODL_KOMPLETORIUM_NEDELNA	0
#define MODL_KOMPLETORIUM_SLAVNOSTI	1
#define MODL_KOMPLETORIUM_TROJDNIE	2

// ... a stringy pre ne
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

// 2005-03-27: Vlozene do definicnej casti z funkcie dbzaltar.cpp::pismenko_modlitby()
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
// #define CHAR_MODL_CEZ_DEN_VSETKY     'd' // 2005-03-27: pridanÈ
#define CHAR_MODL_VSETKY             '*' // 2011-10-03: pridanÈ pokusne

// 2008-04-09: doplnenÈ pre batch generovanie modlitieb
extern const char char_modlitby[POCET_MODLITIEB + 1];
extern const char *str_modlitby[POCET_MODLITIEB + 1];

//extern const char *nazov_modlitby[];
extern const char *nazov_modlitby_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1];
#define		nazov_modlitby(a)	nazov_modlitby_jazyk[a][_global_jazyk]

//extern const char *nazov_Modlitby[];
extern const char *nazov_Modlitby_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1];
#define		nazov_Modlitby(a)	nazov_Modlitby_jazyk[a][_global_jazyk]

//extern const char *nazov_MODLITBY[];
extern const char *nazov_MODLITBY_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1];
#define		nazov_MODLITBY(a)	nazov_MODLITBY_jazyk[a][_global_jazyk]

// ... a file templates (suborove vzory) pre modlitby | 2011-01-25: premenovanÈ (aby mali spoloËn˝ prefix)
#define TEMPLAT_INVITATORIUM     "m_invitat.htm"
#define TEMPLAT_POSV_CITANIE     "m_posvcit.htm"
#define TEMPLAT_RANNE_CHVALY     "m_rchvaly.htm"
#define TEMPLAT_CEZ_DEN_9        "m_predpol.htm"
#define TEMPLAT_CEZ_DEN_12       "m_napol.htm"
#define TEMPLAT_CEZ_DEN_3        "m_popol.htm"
#define TEMPLAT_VESPERY          "m_vespery.htm"
#define TEMPLAT_KOMPLETORIUM     "m_komplet.htm"
#define TEMPLAT_NEURCENY         "" // 2011-10-03: doplnenÈ kvÙli MODL_VSETKY

// pridanÈ 2006-10-24 pre kompletÛrium
#define nazov_obd_KOMPLETORIUM   "cezrok_k.htm"

extern const char *TEMPLAT[POCET_MODLITIEB + 1];

// znaky, ktore znacia (pre interpretovanie templatu) zaciatok a koniec klucoveho slova
#define CHAR_KEYWORD_BEGIN   '{'
#define CHAR_KEYWORD_END     '}'
#define CHAR_KEYWORD_DIVIDER ':'
/*
#define CHAR_KEYWORD2_BEGIN  '<'
#define CHAR_KEYWORD2_END    '>'
*/

// znak '_' pouûÌvame ako z·stupn˝ pre nezlomiteæn˙ medzeru (exportuje sa ako HTML_NONBREAKING_SPACE == "&nbsp;" definovanÈ v mydefs.h) 
// 2011-05-02: pridanÈ; nevadÌ, ûe je duplicita s UNDERSCORE resp. CHAR_MODL_NEURCENA 
#define CHAR_NONBREAKING_SPACE '_'

// include parameters (parametre v inkludovanych suboroch)
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
#define PARAM_MAGNIFIKAT    "MAGNIFIKAT" // antifona na magnifikat
#define PARAM_BENEDIKTUS    "BENEDIKTUS" // antifona na benediktus
#define PARAM_PROSBY        "PROSBY"
#define PARAM_MODLITBA      "MODLITBA"
// pridane 2003-08-06, upravene 2003-08-21
#define PARAM_CITANIE1      "CITANIE1" // vlastne KCITANIE
#define PARAM_CITANIE2      "CITANIE2" // vlastne BENEDIKTUS
// 2007-10-02: pridanÈ kvÙli rovnak˝m antifÛnam pre modlitbu cez deÚ
#define PARAM_ANTIFONA1x    "ANTIFONA1_DRUHA"
#define PARAM_ANTIFONA3x    "ANTIFONA3_PRVA"
// 2008-04-03: pridanÈ kvÙli kompletÛriu vo veækonoËnom obdobÌ, Ëi pri druhej antifÛne zobraziù dvojku alebo nie
#define PARAM_ANTIFONA1k    "ANTIFONA1_KOMPLET"
#define PARAM_ANTIFONA2k    "ANTIFONA2_KOMPLET"
// 2010-05-21: pridanÈ kvÙli spomienkam a æubovoæn˝m spomienkam v pÙstnom obdobÌ (zobrazenie po modlitbe dÚa pÙstnej fÈrie)
// 2012-02-09: zovöeobecnenÈ v zmysle VSLH Ë. 238 (Spomienky pripadaj˙ce na privilegovanÈ dni)
#define PARAM_ANT_SPOMPRIVILEG  "ANT_SPOMPRIVILEG"
#define PARAM_MODL_SPOMPRIVILEG "MODL_SPOMPRIVILEG"
// 2011-03-16: pridanÈ kvÙli spomienkam a æubovoæn˝m spomienkam v pÙstnom obdobÌ (zobrazenie po 2. ËÌtanÌ v posv. ËÌtanÌ)
// 2012-02-09: zovöeobecnenÈ v zmysle VSLH Ë. 238 (Spomienky pripadaj˙ce na privilegovanÈ dni)
#define PARAM_CITANIE2_SPOMPRIVILEG "CITANIE2_SPOMPRIVILEG"
// 2011-07-03: pridanÈ kvÙli navig·cii v modlitbe
#define PARAM_NAVIGACIA     "NAVIGACIA"
// 2011-10-04: pridan˝ nadpis v modlitbe
#define PARAM_NADPIS        "NADPIS"
// 2012-04-03: pridan˝ podnadpis v modlitbe (napr. pre MCD: doplnkov· psalmÛdia)
#define PARAM_PODNADPIS     "PODNADPIS"
// 2012-08-16: pridan˝ ÔalöÌ podnadpis v modlitbe (rubrika pre spoloËn˙ Ëasù)
#define PARAM_SPOL_CAST     "SPOL_CAST"
// 2012-05-24: doplnenÈ -- predÂûenÈ sl·venie vigÌliÌ v r·mci posv‰tn˝ch ËÌtanÌ
#define PARAM_ANTIFONA_VIG  "ANTIFONA_VIG"
#define PARAM_CHVALOSPEV1   "CHVALOSPEV1"
#define PARAM_CHVALOSPEV2   "CHVALOSPEV2"
#define PARAM_CHVALOSPEV3   "CHVALOSPEV3"
#define PARAM_EVANJELIUM    "EVANJELIUM"
// 2012-09-05: moûnosù zobraziù pre doplnkov˙ psalmÛdiu priamy URL odkaz (na prepnutie)
#define PARAM_DOPLNKOVA_PSALMODIA      "DOPLNKOVA-PSALMODIA" // 2012-10-01: _ sa menilo na &nbsp; preto som zmenil na -
// 2012-09-27: moûnosù zobraziù chv·lospev, hymnus Te Deum, OtËen·ö (na prepnutie), opakovanÈ zvolania v prosb·ach, Sl·va Otcu, plnÈ znenie responzÛriÌ pre posv‰tnÈ ËÌtania...
#define PARAM_CHVALOSPEV               "CHVALOSPEV"
#define PARAM_TEDEUM		           "TEDEUM"
#define PARAM_OTCENAS                  "OTCENAS"
#define PARAM_ZVOLANIA                 "ZVOLANIA"
#define PARAM_SLAVAOTCU	               "SLAVAOTCU"
#define PARAM_RESPONZ                  "RESPONZ" // PARAM_PLNE_RESP je uû obsadenÈ...
#define PARAM_KRATSIE_PROSBY           "KRATSIE-PROSBY" // 2012-11-15: _ sa menilo na &nbsp; preto som zmenil na -
#define PARAM_ZALM95                   "ZALM95" // 2012-11-23: kvÙli <a name...>
#define PARAM_VIGILIA                  "VIGILIA"
#define PARAM_SPOL_CAST_SPOM           "SPOL-CAST-SPOM"
#define PARAM_ALT_HYMNUS               "ALT-HYMNUS"
#define PARAM_ZALM122                  "ZALM122"
#define PARAM_ZALM127                  "ZALM127"
#define PARAM_ZALM129                  "ZALM129"
#define PARAM_ZALM131                  "ZALM131"

// dalsie parametre: specificke pre obdobie
// Od nedele P·novho zm‡tvychvstania aû do Druhej veækonoËnej nedele vr·tane, ako aj na druhÈ veöpery sl·vnosti Zoslania Ducha Sv‰tÈho
#define PARAM_ALELUJA_ALELUJA_BEGIN         "ALELUJA_ALELUJA_BEGIN"
#define PARAM_ALELUJA_ALELUJA_END           "ALELUJA_ALELUJA_END"
#define PARAM_ALELUJA_NIE_V_POSTE           "ALELUJA_NIE_V_POSTE" // pouûÌva sa v inkludovan˝ch s˙boroch, napr. v r·mci antifÛn
#define PARAM_ALELUJA_NIE_V_POSTE_BEGIN     "ALELUJA_NIE_V_POSTE_BEGIN"
#define PARAM_ALELUJA_NIE_V_POSTE_END       "ALELUJA_NIE_V_POSTE_END"
#define PARAM_ALELUJA_VO_VELKONOCNOM        "V_O_ALELUJA" // pouûÌva sa v inkludovan˝ch s˙boroch, napr. v r·mci antifÛn
#define PARAM_ALELUJA_VO_VELKONOCNOM_BEGIN  "V_O_ALELUJA_BEGIN" // pouûÌvaj˙ sa v templ·tach
#define PARAM_ALELUJA_VO_VELKONOCNOM_END    "V_O_ALELUJA_END"
// 2005-08-15: DoplnenÈ parametre pre voænÈ, inÈ hymny v 34. t˝ûdni OCR
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
// 2011-04-29: doplnenÈ Sl·va Otcu "öpeci·lne" pre ˙Ëely chv·lospevu Dan 3, 57-88. 56, kde nie je "Sl·va Otcu" (pÙvodne to bolo danÈ poradÌm, ale templ·ty pre rÙzne jazyky maj˙ rozliËnÈ poradie tohto "Sl·va Otcu")
#define PARAM_SLAVAOTCU_SPEC_BEGIN          "SLAVAOTCU_SPEC_BEGIN"
#define PARAM_SLAVAOTCU_SPEC_END            "SLAVAOTCU_SPEC_END"
// 2007-06-28: doplnenÈ Te Deum; nemÙûe sa riadiù rovnak˝mi pravidlami ako chv·lospevy 
// 2011-04-11: pridan˝ ÔalöÌ p·r parametrov
//             JE_TEDEUM_BEGIN a END hovoria, Ëi v danej modlitbe m· vÙbec byù zobrazen· Ëo i len zmienka o Te Deum (riadenÈ podmienkou je_tedeum);
//             TEDEUM_BEGIN a END hovoria, ûe ak m· byù Te Deum (je_tedeum), tak ak chce pouûÌvateæ zobraziù pln˝ text, ohraniËuj˙ ho
#define PARAM_TEDEUM_BEGIN                  "TEDEUM_BEGIN"
#define PARAM_TEDEUM_END                    "TEDEUM_END"
#define PARAM_JE_TEDEUM_BEGIN               "JE_TEDEUM_BEGIN"
#define PARAM_JE_TEDEUM_END                 "JE_TEDEUM_END"
// 2007-10-02: doplnenÈ skrytie rovnak˝ch antifÛn pre mcd
#define PARAM_SKRY_ANTIFONU_BEGIN           "SKRY_ANTIFONU_BEGIN"
#define PARAM_SKRY_ANTIFONU_END             "SKRY_ANTIFONU_END"
// 2012-05-24: doplnenÈ -- predÂûenÈ sl·venie vigÌliÌ v r·mci posv‰tn˝ch ËÌtanÌ
#define PARAM_JE_VIGILIA_BEGIN              "JE_VIGILIA_BEGIN"
#define PARAM_JE_VIGILIA_END                "JE_VIGILIA_END"

// 2010-05-21: doplnenÈ zobrazenie antifÛny a modlitby pre spomienku sv‰tca v pÙstnom obdobÌ
// 2012-02-09: zovöeobecnenÈ v zmysle VSLH Ë. 238 (Spomienky pripadaj˙ce na privilegovanÈ dni)
#define PARAM_SPOMIENKA_PRIVILEG_BEGIN      "SPOMIENKA_PRIVILEG_BEGIN"
#define PARAM_SPOMIENKA_PRIVILEG_END        "SPOMIENKA_PRIVILEG_END"
// 2011-01-12: doplnenÈ zobrazenie/skrytie myölienky k ûalmu -- pre cezroËnÈ obdobie alternatÌvnej antifÛny ûalmu/chv·lospevu ("myölienka k ûalmu" podæa bodu 111 a 114 VSLH)
#define PARAM_PSALMODIA_MYSLIENKA           "PSALMODIA_MYSLIENKA" // 2011-08-31: zmenenÈ; pÙvodne bolo: PARAM_MYSLIENKA_K_ZALMU "MYSLIENKA_K_ZALMU"
// 2011-08-31: doplnenÈ zobrazenie/skrytie nadpisu k ûalmu/chv·lospevu ("nadpis k ûalmu" podæa bodu 111 VSLH)
#define PARAM_PSALMODIA_NADPIS              "PSALMODIA_NADPIS"

#define PARAM_RUBRIKA_BEGIN                 "RUBRIKA_BEGIN"
#define PARAM_RUBRIKA_END                   "RUBRIKA_END"

// 2011-05-03: doplnenÈ kvÙli posv‰tnÈmu ËÌtaniu na veækonoËn˙ nedeæu
#define PARAM_VN_VYNECHAJ_BEGIN             "VELK_NEDELA_VYNECHAJ_BEGIN"
#define PARAM_VN_VYNECHAJ_END               "VELK_NEDELA_VYNECHAJ_END"

// 2011-07-07: doplnenÈ kvÙli zobrazovaniu/skr˝vaniu dlhöÌch z·verov responzÛriÌ v posv‰tnom ËÌtanÌ
#define PARAM_PLNE_RESP                     "PLNE_RESP"
#define PARAM_PLNE_RESP_BODKA               "PLNE_RESP_BODKA"

// 2011-10-05: doplnenÈ kvÙli zobrazovaniu/skr˝vaniu opakovanÈho zvolania v prosb·ch (rannÈ chv·ly, veöpery)
#define PARAM_ZVOLANIE                      "ZVOLANIE"

// 2011-10-26: doplnenÈ rubriky priamo v includovan˝ch HTML s˙boroch
#define PARAM_RUBRIKA                       "RUBRIKA"

// 2011-04-04: doplnenÈ zobrazenie/skrytie ËÌslovania veröov v ûalmoch, chv·lospevoch a biblick˝ch ËÌtaniach
#define PARAM_CISLO_VERSA_BEGIN				"v"
#define PARAM_CISLO_VERSA_END				"/v"

// 2011-04-05: doplnenie referencie podæa biblickÈho odkazu na str·nky dkc.kbs.sk (Biblia -- Mat˙ö Brilla)
#define PARAM_REFERENCIA_BEGIN				"r"
#define PARAM_REFERENCIA_END				"/r"

// 2011-09-01: odkaz na katechÈzy (pÙvodne v HTML zdroj·koch bola subscript hviezdiËka za nadpisom)
#define PARAM_KATECHEZA_BEGIN				"k"
#define PARAM_KATECHEZA_END					"/k"

// 2011-09-06: odkaz na ûalm 95 (pÙvodne v HTML zdroj·koch pre ûalmy 24, 67, 100 bol natvrdo <a href> odkaz)
#define PARAM_LINK_ZALM95_BEGIN				"z95"
#define PARAM_LINK_ZALM95_END				"/z95"

// 2011-07-08: zobrazovanie/nezobrazenie krÌûika (antifÛna totoûn· s veröom ûalmu/chv·lospevu)
#define PARAM_KRIZIK                        "KRIZIK"

// 2011-07-14: zobrazovanie/nezobrazenie zalomen˝ch textov tak, ako je v tlaËenom vydanÌ LH (dlhÈ riadky-veröe ûalmov/chv·lospevov a pod.)
#define PARAM_ZALOMENIE                     "ZALOMENIE"

// 2011-10-07: zakonËenie modlitieb (skrze, lebo on, lebo ty...) in·Ë (jednoduchöie, bez begin-end)
#define PARAM_ZAKONCENIE                    "ZAKONCENIE"

// 2013-02-26: doplnkov· psalmÛdia, alternatÌvne ûalmy
#define PARAM_DOPLNK_PSALM_122_129          "DPSALM-122-129"
#define PARAM_DOPLNK_PSALM_127_131          "DPSALM-127-131"

// 2009-04-08: zakonËenie modlitby trojakÈ, kr·tke resp. dlhÈ
#define PARAM_ZAKONCENIE_SKRZE              "SKRZE"
#define PARAM_ZAKONCENIE_LEBO_TY            "LEBO_TY"
#define PARAM_ZAKONCENIE_LEBO_ON            "LEBO_ON"
// 2009-12-14: zakonËenie modlitby trojakÈ, kr·tke resp. dlhÈ s mal˝m pÌsmenkom na zaËiatku
#define PARAM_ZAKONCENIE_SKRZE_MALE         "SKRZE_MALE"
#define PARAM_ZAKONCENIE_LEBO_TY_MALE       "LEBO_TY_MALE"
#define PARAM_ZAKONCENIE_LEBO_ON_MALE       "LEBO_ON_MALE"
// 2010-06-07: eöte jedno zakonËenie modlitby pre slovenËinu, kr·tke resp. dlhÈ (POST1_MODLITBA5NE)
#define PARAM_ZAKONCENIE_ON_JE              "ON_JE"
// 2010-01-14: eöte jedno zakonËenie modlitby pre slovenËinu, kr·tke resp. dlhÈ
#define PARAM_ZAKONCENIE_KTORY_JE           "KTORY_JE"
// 2012-03-16: predslovy k zakonËeniam, ktorÈ sa pre fÈrie nemaj˙ zobraziù, ak sa sl·vi spomienka v privilegovan˝ch dÚoch
#define PARAM_ZAKONCENIE_O_TO_TA_PROSIME    "O_TO_TA_PROSIME"

// 2011-08-15: force pre jednotlivÈ Ëasti modlitby, funkcie _set_spolocna_cast()...
#define FORCE_BRAT_ANTIFONY      1
#define FORCE_BRAT_ZALMY         2
#define FORCE_BRAT_KCIT_1CIT     4 // kr·tke ËÌtanie pre rch+v; 1. ËÌtanie pre posv‰tnÈ ËÌtanie
#define FORCE_BRAT_KRESP_PROSBY  8
#define FORCE_BRAT_2CITANIE     16
#define FORCE_BRAT_ANTIFONY_MCD 32

// stringy parametrov vstupu pre MODL_OPT..., ktore generovanie modlitby ovplyvnuju
// option 1
//#define STR_ANO "·no"
extern const char *str_ano[POCET_JAZYKOV + 1];
#ifndef		STR_ANO
#define		STR_ANO		str_ano[_global_jazyk]
#endif
//#define STR_NIE "nie"
extern const char *str_nie[POCET_JAZYKOV + 1];
#ifndef		STR_NIE
#define		STR_NIE		str_nie[_global_jazyk]
#endif

/* option 2 - presunutÈ do mydefs.h 
#define MODL_ZALMY_ZO_DNA 0
#define MODL_ZALMY_ZO_SV  1
*/

//#define STR_MODL_ZALMY_ZO_DNA "dÚa"
extern const char *str_modl_zalmy_zo_dna[POCET_JAZYKOV + 1];
#ifndef		STR_MODL_ZALMY_ZO_DNA
#define		STR_MODL_ZALMY_ZO_DNA 	str_modl_zalmy_zo_dna[_global_jazyk]
#endif
//#define STR_MODL_ZALMY_ZO_SV  "sviatku"
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
// MODL_SPOL_CAST_NEBRAT musi byt posledna, napr. kvoli "while" v dnes.cpp::showPrayer(); ale predsa mensia ako MAX_MODL_SPOL_CAST
#define MODL_SPOL_CAST_SV_ZENA_MANZ      25 // pre t˝ch, Ëo ûili v manûelstve
#define MODL_SPOL_CAST_SV_MUZ_MANZ       26 // pre t˝ch, Ëo ûili v manûelstve
#define MODL_SPOL_CAST_NEBRAT            27 // nechce zo spol. casti
#define POCET_SPOL_CASTI	MAX_MODL_SPOL_CAST - 1

extern const char *str_doplnkova_psalmodia[POCET_JAZYKOV + 1];
//#define STR_MODL_CEZ_DEN_ZALMY_ZO_DNA        "beûnej"
extern const char *str_modl_cez_den_zalmy_zo_dna[POCET_JAZYKOV + 1];
#ifndef		STR_MODL_CEZ_DEN_ZALMY_ZO_DNA
#define		STR_MODL_CEZ_DEN_ZALMY_ZO_DNA	str_modl_cez_den_zalmy_zo_dna[_global_jazyk]
#endif
//#define STR_MODL_CEZ_DEN_DOPLNKOVA_PSALMODIA "doplnkovej"
extern const char *str_modl_cez_den_doplnkova_psalmodia[POCET_JAZYKOV + 1];
#ifndef		STR_MODL_CEZ_DEN_DOPLNKOVA_PSALMODIA
#define		STR_MODL_CEZ_DEN_DOPLNKOVA_PSALMODIA	str_modl_cez_den_doplnkova_psalmodia[_global_jazyk]
#endif

// a pre tieto - vyssie uvedene - konstanty aj retazce... -- malo by ich byt do MAX_MODL_SPOL_CAST
//extern const char *nazov_spolc[MODL_SPOL_CAST_NEBRAT + 1];
extern const char *nazov_spolc_jazyk[POCET_SPOL_CASTI + 1][POCET_JAZYKOV + 1];
#ifndef		nazov_spolc
#define		nazov_spolc(a)	nazov_spolc_jazyk[a][_global_jazyk]
#endif

// a pre tieto konstanty aj retazce -- nazvy suborov -- malo by ich byt do MAX_MODL_SPOL_CAST
// sc_rh == spolocna cast pre reholnikov / reholnice;
// sc_skm == spolocna cast pre tych, co konali skutky milosrdenstva ;
// sc_vv == spolocna cast pre vychovavatelov;
// zosnuli == oficium za zosnulych;
extern const char *nazov_spolc_htm[MODL_SPOL_CAST_NEBRAT + 1];
// a pre tieto konstanty aj retazce -- nazvy kotiev -- malo by ich byt do MAX_MODL_SPOL_CAST
extern const char *nazov_spolc_ANCHOR[MODL_SPOL_CAST_NEBRAT + 1];

#define ANCHOR_SPOL_CAST_DUCH_PAST "SCDP"
// vacsinu veci maju duchovni pastieri spolocnych; odlisnosti: su v nazov_spolc_ANCHOR[]
#define ANCHOR_SPOL_CAST_JEDEN_MUCENIK "SCJM"
// na sviatok jedneho mucenika sa rozhoduje, ci ide o muza alebo zenu | v niektorych pripadoch; odlisnosti: su v nazov_spolc_ANCHOR[]
#define ANCHOR_SPOL_CAST_PANNA_MUCENICA "SCAM"
//  na sviatok vychovavatelov: nevieme (a je jedno), ci ide o muza alebo zenu -- ked berieme z fajlu sc_vv.htm
/*
#define ANCHOR_SPOL_CAST_VYCHOVAVATEL "SCVV"
#define FILE_SPOL_CAST_VYCHOVAVATEL "sc_vv.htm"
*/
// na sviatok tych, co konali skutky milosrdenstva: nevieme (a je jedno), ci ide o muza alebo zenu -- ked berieme z fajlu sc_skm.htm
/*
#define ANCHOR_SPOL_CAST_SKUTKYMIL "SCSKM"
#define FILE_SPOL_CAST_SKUTKYMIL "sc_skm.htm"
*/ // je to v poli... v hodin.h

struct sc{
	short int a1;
	short int a2;
	short int a3;
};
typedef struct sc _struct_sc;

// 2005-07-27: zaveden· nov· premenn· v ötrukt˙re: typslav_lokal urËen· niesù öpeci·lnu inform·ciu o tom, Ëi danÈ sl·venie je lok·lne.
// ötandardne 0 = bez öpeci·lnej lokaliz·cie.
// 2006-08-19: pridan· premenn· pre liturgick˙ farbu
// 2010-08-03: pridan· premenn· pre öpecifik·ciu, o ak˝ kalend·r ide (kalendar): vöeobecn˝ danej cirkevnej provincie alebo nejak˝ rehoæn˝ a pod.
struct dm{
	short int den;        // cislo dna mesiaca (1--31)
	short int mesiac;     // cislo mesiaca (1--12)
	short int rok;        // rok
	short int denvt;      // cislo dna v tyzdni (0--6) DEN_...
	short int denvr;      // cislo dna v roku (1--365/366) -- deÚ v roku
	// toto boli "obcianske" zalezitosti
	char litrok;          // liturgicky rok ('A'--'C')
	short int tyzden;     // tyzden v danom liturgickom obdobi
	short int tyzzal;     // tyzden v zaltari (vacsinou ((tyzden - 1) % 4) + 1)
	short int litobd;     // liturgicke obdobie, OBD_...
	short int typslav;    // typ slavenia (1--5): SLAV_...
	short int typslav_lokal; // lok·lny typ slavenia : LOKAL_SLAV_...
	short int smer;       // poradove cislo z c.59 Vseobecnych smernic o liturgii hodin a kalendari
	short int prik;		  // ci je to prikazany sviatok alebo nie: PRIKAZANY_SVIATOK resp. NIE_JE_PRIKAZANY_SVIATOK
	int spolcast;		  // spolocna cast -- zakodovane data pre svatych o tom, z akej spolocnej casti sa ma modlit;
						  // obsahuje max. 3 spolocne casti vo formate spolcast == a1 + a2 * MAX + a3 * MAX * MAX,
						  // kde -- MAX je MAX_MODL_SPOL_CAST,
						  //     -- a1, a2, a3 su konstanty MODL_SPOL_CAST_... (v poradi a1, ak druhe tak a2, ak tretie tak aj a3)
						  // _encode_..., _decode_spol_cast();
	char meno[MENO_SVIATKU]; // nazov prip. sviatku
	short int farba;      // liturgick· farba pre sl·venie
	short int kalendar;   // öpecifik·cia, o ak˝ kalend·r ide: vöeobecn˝ danej cirkevnej provincie alebo nejak˝ rehoæn˝ a pod.
};
typedef struct dm _struct_dm;

// dni
#define DEN_NEDELA      0
#define DEN_PONDELOK    1
#define DEN_UTOROK      2
#define DEN_STREDA      3
#define DEN_STVRTOK     4
#define DEN_PIATOK      5
#define DEN_SOBOTA      6
// neznamy den
#define DEN_UNKNOWN     7
#define POCET_DNI		7

// mesiace
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
// neznamy mesiac
#define UNKNOWN_MESIAC	12
#define POCET_MESIACOV	12
// vsetky mesiace
#define VSETKY_MESIACE	13
#define STR_VSETKY_MESIACE  "*"
// vsetky dni
#define VSETKY_DNI   32
#define STR_VSETKY_DNI  "*"

// liturgickÈ obdobia 
// 2011-01-26: ËÌsla konötant·m pridelenÈ tak, aby reöpektovali plynulosù liturgickÈho roka od zv‰zku I brevi·ra
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

#define	POCET_OBDOBI	11

// zv‰zok brevi·ra - zv‰zok, v ktorom sa nach·dza danÈ liturgickÈ obdobie; doplnenÈ 2007-12-20; opravenÈ 2008-01-23
const short int zvazok_breviara[POCET_OBDOBI + 1] = 
{1, 1, 1, 1, 1, 3, 2, 2, 2, 2, 2, 2}; // nepotrebujeme rozlÌöiù 3. a 4. zv‰zok, ktorÈ obidva obsahuj˙ OBD_CEZ_ROK

// poËet t˝ûdÚov pre danÈ liturgickÈ obdobie; doplnenÈ 2011-01-25
const short int lit_obd_pocet_tyzdnov[POCET_OBDOBI + 1] = 
{4, 1, 1, 2, 1, 34, 6, 1, 1, 1, 7, 2};

// nazov_obdobia: string pre nazov liturgickeho obdobia
//extern const char *nazov_obdobia[];
extern const char *nazov_obdobia_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1];
#define		nazov_obdobia(a)	nazov_obdobia_jazyk[a][_global_jazyk]

extern const char *nazov_obdobia_[POCET_OBDOBI + 1];

// lokal == 6. pad, v kom/com
//extern const char *nazov_obdobia_v[];
extern const char *nazov_obdobia_v_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1];
#define		nazov_obdobia_v(a)	nazov_obdobia_v_jazyk[a][_global_jazyk]

//extern const char *nazov_OBDOBIA_V[];
extern const char *nazov_OBDOBIA_V_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1];
#define		nazov_OBDOBIA_V(a)	nazov_OBDOBIA_V_jazyk[a][_global_jazyk]

extern const char *nazov_OBDOBIA_AKA_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1];
#define		nazov_OBDOBIA_AKA(a)	nazov_OBDOBIA_AKA_jazyk[a][_global_jazyk]

// gen[itiv] == 2. pad, koho/coho
// extern const char *nazov_obdobia_gen[];
// extern const char *nazov_Obdobia[];

// nazov_obdobia: string pre nazov suboru .htm liturgickeho obdobia
extern const char *nazov_obd_htm[POCET_OBDOBI + 1];
// nazov_obdobia: string pre nazov kotvy v .htm liturgickeho obdobia
extern const char *nazov_OBD[POCET_OBDOBI + 1];
// nazov_obdobia pc: string pre nazov suboru .htm liturgickeho obdobia pre posvatne citania
extern const char *nazov_obd_htm_pc[POCET_OBDOBI + 1];
// 2005-08-05: PridanÈ. zv‰zok brevi·ra (LH) pre spoloËnÈ Ëasti sv‰t˝ch v kotv·ch
extern const char *zvazok_OBD[POCET_OBDOBI + 1];

// typy slavenia
#define SLAV_NEURCENE            0
#define SLAV_SLAVNOST            1
#define SLAV_SVIATOK             2
#define SLAV_SPOMIENKA           3
#define SLAV_LUB_SPOMIENKA       4
#define SLAV_VLASTNE             5

#define	POCET_SLAVENI            5

// nazov_slavenia: string pre nazov typu slavenia
//extern const char *nazov_slavenia[];
extern const char *nazov_slavenia_jazyk[POCET_SLAVENI + 1][POCET_JAZYKOV + 1];
#define		nazov_slavenia(a)	nazov_slavenia_jazyk[a][_global_jazyk]

// the name of celebration -- for memoria (in privileged days)
extern const char *nazov_slavenia_na_spomienku_jazyk[POCET_JAZYKOV + 1];

// extern const char *nazov_Slavenia[];

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
#define LOKAL_SLAV_TRNAVA					10 // pÙvodne bolo LOKAL_SLAV_TRNAVA, upravenÈ 2007-08-31 na LOKAL_SLAV_BA_TT; nasp‰ù na LOKAL_SLAV_TRNAVA 2008-06-23
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
#define LOKAL_SLAV_SLEZSKO_SVATEK			37
#define LOKAL_SLAV_CESKE_BUDEJOVICE_PAMATKA	38
#define LOKAL_SLAV_SPIS_BA_PATRON			39 // pre 11. novembra, patrÛna BA-arcidiecÈzy; 2008-06-24; nahr·dza LOKAL_SLAV_SPIS_PATRON
#define LOKAL_SLAV_BRATISLAVA				40 // doplnenÈ 2010-03-16
#define LOKAL_SLAV_KONIEC_OKTAVY_NAR_HU		41 // doplnenÈ 2010-05-17
#define LOKAL_SLAV_KONGREGACIA_SSK			42 // doplnenÈ 2011-01-27
#define LOKAL_SLAV_SPOMIENKA_OFMCAP			43 // nasledovnÈ doplnenÈ 2011-03-16
#define LOKAL_SLAV_SVIATOK_OFM				44
#define LOKAL_SLAV_SPOMIENKA_OFM			45
#define LOKAL_SLAV_SVIATOK_OFMCAP			46 // nasledovnÈ doplnenÈ 2011-03-17
#define LOKAL_SLAV_SPOMIENKA_FMA			47
#define LOKAL_SLAV_SLAVNOST_FMA				48
#define LOKAL_SLAV_SLAVNOST_SDB				49
#define LOKAL_SLAV_SVIATOK_VDB				50
#define LOKAL_SLAV_SVIATOK_SCSC				51
#define LOKAL_SLAV_DRUHA_VELK_NEDELA_HU		52
#define LOKAL_SLAV_SZOMBATHELYI_EGYH        53
#define LOKAL_SLAV_POZS_NAGYSZ_PATRON       54
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

// 2010-08-03: pridan˝ kalend·r
#define KALENDAR_NEURCENY                   0
#define KALENDAR_VSEOBECNY                  1
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

#define POCET_KALENDAROV                   13

// filenames for special calendars / n·zov s˙bora pre kalend·re
extern const char *nazov_htm_kalendar[POCET_KALENDAROV + 1];

extern const char *nazov_kalendara_long[POCET_KALENDAROV + 1];

// prikazany / neprikazany sviatok / æubovoæn· spomienka bez z·v‰znosti (blahoslavenÌ napr. pre SK_OP)
#define PRIKAZANY_SVIATOK           0
#define NIE_JE_PRIKAZANY_SVIATOK    1
#define VOLNA_LUBOVOLNA_SPOMIENKA   2 // pre SK OP; v kalend·ri znaËenÈ kurzÌvou (bez popisu "æubovoæn· spomienka"); 2012-04-01

// div, mod: delenie pre short int
#define DIV	/
#define MOD	%

// 2006-02-07: dodefinovanÈ rÙzne spr·vanie funkcie zaltar_zvazok();
#define	ZALTAR_VSETKO                0
#define ZALTAR_IBA_ZALMY             1
#define ZALTAR_IBA_ZALMY_HYMNUS_MCD  2

// 2006-08-19: pridanÈ liturgickÈ farby
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

// nazov_farby: string pre n·zov liturgickej farby
extern const char *nazov_farby_jazyk[POCET_FARIEB_REALNYCH + 1][POCET_JAZYKOV + 1];
#define		nazov_farby(a)	nazov_farby_jazyk[a][_global_jazyk]

extern const char *html_farba_pozadie[POCET_FARIEB_REALNYCH + 1];
extern const char *html_farba_popredie[POCET_FARIEB_REALNYCH + 1];

// juliansky datum, funkcia juliansky_datum, dane synonymum JD
#define	JD	juliansky_datum

#define ZVAZKY_LH 4
// tyzden zaltara (1, 2, 3, 4) podla tyzdna t; 06/03/2000A.D.: namiesto "-1" prerobene na "+3"
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

// nazov_dna: string pre nazov dna; suhlasi s struct tm.tm_wday; Weekday (0--6; Sunday/nedela = 0)

//extern const char *nazov_dna[];
extern const char *nazov_dna_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_dna(a)	nazov_dna_jazyk[a][_global_jazyk]

//extern const char *nazov_dna_asci[];
extern const char *nazov_dna_asci_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_dna_asci(a)	nazov_dna_asci_jazyk[a][_global_jazyk]

//extern const char *nazov_Dna[];
extern const char *nazov_Dna_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_Dna(a)	nazov_Dna_jazyk[a][_global_jazyk]

//extern const char *nazov_DNA[];
extern const char *nazov_DNA_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_DNA(a)	nazov_DNA_jazyk[a][_global_jazyk]

//extern const char *nazov_Dn[];
extern const char *nazov_Dn_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_Dn(a)	nazov_Dn_jazyk[a][_global_jazyk]

extern const char *nazov_DN_asci[POCET_DNI + 1];
extern const char *nazov_dn_asci[POCET_DNI + 1];

// nazov_mesiaca: string pre nazov dna; suhlasi s struct tm.tm_mon; Month (0--11)

//extern const char *nazov_mesiaca[];
extern const char *nazov_mesiaca_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_mesiaca(a)	nazov_mesiaca_jazyk[a][_global_jazyk]

//extern const char *nazov_mesiaca_asci[];
extern const char *nazov_mesiaca_asci_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_mesiaca_asci(a)	nazov_mesiaca_asci_jazyk[a][_global_jazyk]

//extern const char *nazov_Mesiaca[];
extern const char *nazov_Mesiaca_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_Mesiaca(a)	nazov_Mesiaca_jazyk[a][_global_jazyk]

//extern const char *nazov_MESIACA[];
extern const char *nazov_MESIACA_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_MESIACA(a)	nazov_MESIACA_jazyk[a][_global_jazyk]

// 2007-03-20: pridan˝ genitÌv n·zvu mesiaca kvÙli latinËine
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

#define LINK_DEN_MESIAC_NIE 0 // 2008-01-22: pridanÈ, Vlado Kiö upozornil, ûe je to zbytoËnÈ
#define LINK_DEN_MESIAC_ROK 1
#define LINK_DEN_MESIAC 3
#define LINK_DEN 2
#define LINK_DEN_MESIAC_ROK_PRESTUP 4 // pridana kvoli prestupnym rokom, 2003-07-02
#define LINK_ISO_8601 5 // pridana kvoli SIMPLE exportu, 2005-03-21
#define LINK_DEN_MESIAC_PREDOSLY 6 // 2007-08-15 pridanÈ kvÙli novÈmu kalend·ru
#define LINK_DEN_MESIAC_NASLEDOVNY 7 // 2007-08-15 pridanÈ kvÙli novÈmu kalend·ru
#define LINK_DEN_MESIAC_GEN 8 // 2011-12-19: to istÈ ako LINK_DEN_MESIAC, len mesiac je v genitÌve

//---------------------------------------------------------------------
// globalne premenne -- su definovane v dnes.cpp (18/02/2000A.D.)

// globalna premenna, do ktorej sa ukladaju info o analyzovanom dni
extern _struct_dm *_global_den_ptr;
// extern _struct_dm _global_den;
#define _global_den (*_global_den_ptr)

// globalna premenna, ktora obsahuje data o spomienke panny marie v sobotu

extern _struct_dm *_global_pm_sobota_ptr;
// extern _struct_dm _global_pm_sobota;
#define _global_pm_sobota (*_global_pm_sobota_ptr)

// globalne premenne, do ktorych sa ukladaju info o analyzovanom dni o sviatkoch svatych

extern _struct_dm *_global_svaty1_ptr;
// extern _struct_dm _global_svaty1;
#define _global_svaty1 (*_global_svaty1_ptr)

extern _struct_dm *_global_svaty2_ptr;
// extern _struct_dm _global_svaty2; // v pripade, ze je viac lubovolnych spomienok
#define _global_svaty2 (*_global_svaty2_ptr)

extern _struct_dm *_global_svaty3_ptr;
// extern _struct_dm _global_svaty3; // v pripade, ze je viac lubovolnych spomienok
#define _global_svaty3 (*_global_svaty3_ptr)

// globalne premenne obsahujuce data modlitbach

extern _type_1vespery     *_global_modl_prve_vespery_ptr;
// extern _type_1vespery      _global_modl_prve_vespery;
#define _global_modl_prve_vespery (*_global_modl_prve_vespery_ptr)

extern _type_1kompletorium *_global_modl_1kompletorium_ptr;
// extern _type_1kompletorium _global_modl_prve_kompletorium;
#define _global_modl_prve_kompletorium (*_global_modl_1kompletorium_ptr)

extern _type_invitatorium *_global_modl_invitatorium_ptr;
// extern _type_invitatorium  _global_modl_invitatorium;
#define _global_modl_invitatorium (*_global_modl_invitatorium_ptr)

extern _type_posv_citanie *_global_modl_posv_citanie_ptr;
#define _global_modl_posv_citanie (*_global_modl_posv_citanie_ptr)

extern _type_ranne_chvaly *_global_modl_ranne_chvaly_ptr;
// extern _type_ranne_chvaly  _global_modl_ranne_chvaly;
#define _global_modl_ranne_chvaly (*_global_modl_ranne_chvaly_ptr)

extern _type_cez_den_9     *_global_modl_cez_den_9_ptr;
// extern _type_cez_den_9     _global_modl_cez_den_9;
#define _global_modl_cez_den_9 (*_global_modl_cez_den_9_ptr)
extern _type_cez_den_12     *_global_modl_cez_den_12_ptr;
// extern _type_cez_den_12     _global_modl_cez_den_12;
#define _global_modl_cez_den_12 (*_global_modl_cez_den_12_ptr)
extern _type_cez_den_3     *_global_modl_cez_den_3_ptr;
// extern _type_cez_den_3     _global_modl_cez_den_3;
#define _global_modl_cez_den_3 (*_global_modl_cez_den_3_ptr)

// pridane 2003-08-13 pre lahsie pouzitie
#define _global_modl_predpol  _global_modl_cez_den_9
#define _global_modl_napol    _global_modl_cez_den_12
#define _global_modl_popol    _global_modl_cez_den_3

extern _type_vespery      *_global_modl_vespery_ptr;
// extern _type_vespery       _global_modl_vespery;
#define _global_modl_vespery (*_global_modl_vespery_ptr)

extern _type_kompletorium *_global_modl_kompletorium_ptr;
// extern _type_kompletorium _global_modl_kompletorium;
#define _global_modl_kompletorium (*_global_modl_kompletorium_ptr)

// globalna premenna, ktora obsahuje MODL_...
extern short int _global_modlitba;

// globalna premenna, do ktorej ukladaju funkcie vytvor_query_string_... linku tvaru PATH_CGI(SCRIPT_NAME) ++ "?param1=val&param2=val&..."
extern char *_global_link_ptr;
// extern char _global_link[MAX_STR];
#define _global_link _global_link_ptr

extern char *_global_pom_str; // pomocny string pre velke pismena
// extern char _global_pom_str[MAX_STR];

// globalna premenna, do ktorej sa ukladaju info o jednotlivych vyznacnych liturgickych dni, pouzivaju void _dm_...() funkcie a void analyzuj_rok() funkcia
extern _struct_dm *_global_result_ptr;
// extern _struct_dm _global_result;
#define _global_result (*_global_result_ptr)

// globalna premenna, do ktorej sa uklada info o liturgickom roku pouziva void analyzuj_rok() funkcia
extern _struct_lrok *_global_r_ptr;
// extern _struct_lrok _global_r;
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

// glob·lna premenn· -- pole -- obsahuj˙ca options; pÙvodne to boli glob·lne premennÈ _global_opt 1..9 atÔ., obsahuj˙ pom_MODL_OPT...
extern short int _global_opt[POCET_GLOBAL_OPT];
// glob·lna premenn· -- pole -- obsahuj˙ca force options; pÙvodne to boli glob·lne premennÈ _global_optf 1..9 atÔ., obsahuj˙ pom_MODL_OPTF...
extern short int _global_optf[POCET_GLOBAL_OPT];

#define POCET_OPT_0_SPECIALNE               6 // jednotlivÈ komponenty option 0 -- bity pre force option 0
extern short int _global_opt_specialne[POCET_OPT_0_SPECIALNE];
// 2011-04-08: ˙prava v˝znamu (a interpret·cie) option 0 ==  OPT_0_SPECIALNE (zobraziù/nezobraziù "pridan˙ hodnotu" oproti papierovej LH)
#define BIT_OPT_0_VERSE                     1
#define BIT_OPT_0_REFERENCIE                2
#define BIT_OPT_0_CITANIA                   4
#define BIT_OPT_0_ZJAVENIE_PANA_NEDELA      8 // Ëi sa Zjavenie P·na sl·vi v nedeæu (1) alebo nie (teda 6. janu·ra; hodnota 0 == default)
#define BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA  16 // Ëi sa Nanebovst˙penie P·na sl·vi v nedeæu (1) alebo nie (teda vo ötvrtok, na 40.-ty deÚ po VeækonoËnej nedeli; hodnota 0 == default)
#define BIT_OPT_0_TELAKRVI_NEDELA          32 // Ëi sa Najsv. Kristovho tela a krvi sl·vi v nedeæu (1) alebo nie (teda vo ötvrtok, 11.-ty deÚ po ZoslanÌ Ducha Sv.; hodnota 0 == default)

#define POCET_OPT_1_CASTI_MODLITBY         14 // jednotlivÈ komponenty option 1 -- bity pre force option 1
extern short int _global_opt_casti_modlitby[POCET_OPT_1_CASTI_MODLITBY];
// 2011-04-11: ˙prava v˝znamu (a interpret·cie) option 1 == OPT_1_CASTI_MODLITBY (zobraziù/nezobraziù najm‰ pevnÈ/nemennÈ s˙Ëasti modlitieb, ale aj inÈ, Ëo s˙/nie s˙ v LH)
// 2011-10-10: ˙prava niektor˝ch bitov, posunutie popisu na koniec
#define BIT_OPT_1_TEDEUM                    1
#define BIT_OPT_1_RUBRIKY                   2
#define BIT_OPT_1_CHVALOSPEVY               4
#define BIT_OPT_1_SLAVA_OTCU                8
#define BIT_OPT_1_OTCENAS                  16
#define BIT_OPT_1_MCD_ZALMY_INE            32 // pouûÌva sa pre modlitbu cez deÚ -- 1 = alternatÌvna, doplnkov· psalmÛdia
#define BIT_OPT_1_PC_VIGILIA               64
#define BIT_OPT_1_SPOMIENKA_SPOL_CAST     128 // pri sl·venÌ spomienky moûno podæa vöeobecn˝ch smernÌc, Ë. 235 b), vziaù niektorÈ Ëasti alebo zo spoloËnej Ëasti (1), alebo zo dÚa (0)
#define BIT_OPT_1_PLNE_RESP               256
#define BIT_OPT_1_ZALM95                  512 // pouûÌva sa pre rannÈ chv·ly a veöpery -- 1 = vziaù namiesto ûalmov 24, 67, 100 ûalm 95
#define BIT_OPT_1_PROSBY_ZVOLANIE        1024 // 1 = zvolanie v prosb·ch zobraziù (opakovaù) po kaûdej prosbe
#define BIT_OPT_1_SKRY_POPIS             2048
#define BIT_OPT_1_ZOBRAZ_SPOL_CAST       4096
#define BIT_OPT_1_VESP_KRATSIE_PROSBY    8192 // 1 = pouûiù (pre ktor˝koævek deÚ v roku) kratöie prosby k veöper·m

#define POCET_OPT_2_HTML_EXPORT            15 // jednotlivÈ komponenty option 2 -- bity pre force option 2
extern short int _global_opt_html_export[POCET_OPT_2_HTML_EXPORT];
// 2011-04-12: ˙prava v˝znamu (a interpret·cie) option 2 (rozliËnÈ prepÌnaËe pre [online aj offline] export, napr. tlaËidl·, zobrazenie d·tumov a podobne)
// 2012-10-01: doplnenÈ Ôalöie komponenty najm‰ pre vzhæad ˙vodnej obrazovky
#define BIT_OPT_2_ISO_DATUM                 1
#define BIT_OPT_2_BUTTON_PRVE_VESPERY       2
#define BIT_OPT_2_FONT_FAMILY               4 // 0 = Serif, 1 = Sans Serif
#define BIT_OPT_2_FONT_NAME_CHOOSER         8 // 1 = zobraziù drop-down list s moûnosùou voæby font (family) name
#define BIT_OPT_2_FONT_SIZE_CHOOSER        16 // 1 = zobraziù drop-down list s moûnosùou voæby veækosti fontu
#define BIT_OPT_2_NAVIGATION               32 // 1 = zobraziù navig·ciu v modlitbe (predoöl·, nasledovn· modlitba a pod.)
#define BIT_OPT_2_TEXT_WRAP                64 // 1 = zobraziù zalomenie v textoch modlitby podæa tlaËenej LH
#define BIT_OPT_2_BUTTONY_USPORNE         128 // 1 = zobraziù buttony pre modlitby v ˙spornej podobe (tabuæka) kvÙli mobiln˝m zariadeniam
#define BIT_OPT_2_NOCNY_REZIM             256 // 1 = zobraziù invertovane farby (biele na ciernom)
#define BIT_OPT_2_ROZNE_MOZNOSTI          512 // 1 = zobraziù rozliËnÈ "hypertextovÈ odkazy" v modlitbe (napr. pre modlitbu cez deÚ moûnosù doplnkovej psalmÛdie)
#define BIT_OPT_2_HIDE_NAVIG_BUTTONS     1024 // 1 = moûnosù zobraziù/skryù navig·ciu (tlaËidl·) v modlitbe a pre "dnes", ak je zvolen˝ 6. bit (BIT_OPT_2_NAVIGATION)
#define BIT_OPT_2_HIDE_KALENDAR          2048 // 1 = skryù kalend·rik pre "dnes"
#define BIT_OPT_2_HIDE_OPTIONS1          4096 // 1 = skryù html_text_dalsie_moznosti_1[] pre "dnes"
#define BIT_OPT_2_HIDE_OPTIONS2          8192 // 1 = skryù html_text_dalsie_moznosti_2[] pre "dnes"
#define BIT_OPT_2_ALTERNATIVES          16384 // 1 = uk·zaù iba jednu alternatÌvu (0 = ako doteraz; buÔ systÈm vyberie, alebo uk·ûe vöetky moûnosti)

#define POCET_OPT_4_OFFLINE_EXPORT          1 // jednotlivÈ komponenty option 4 -- bity pre force option 4
extern short int _global_opt_offline_export[POCET_OPT_4_OFFLINE_EXPORT];
// 2011-04-08: ˙prava v˝znamu (a interpret·cie) option 4 (rozliËnÈ prepÌnaËe pre offline export, napr. aj batch mÛd)
#define BIT_OPT_4_MESIAC_RIADOK             1

#define POCET_OPT_5_ALTERNATIVES            7 // jednotlivÈ komponenty option 5 -- bity pre force option 5
extern short int _global_opt_alternatives[POCET_OPT_5_ALTERNATIVES];
#define BIT_OPT_5_HYMNUS_KOMPL              1 // hymnus na kompletÛrium (CezroËnÈ obdobie, A/B)
#define BIT_OPT_5_HYMNUS_PC                 2 // hymnus pre posv‰tnÈ ËÌtanie (CezroËnÈ obdobie, I./II.)
#define BIT_OPT_5_HYMNUS_MCD_PREDPOL        4 // hymnus pre modlitbu cez deÚ, predpoludnÌm (CezroËnÈ obdobie)
#define BIT_OPT_5_HYMNUS_MCD_NAPOL          8 // hymnus pre modlitbu cez deÚ, napoludnie (CezroËnÈ obdobie)
#define BIT_OPT_5_HYMNUS_MCD_POPOL         16 // hymnus pre modlitbu cez deÚ, popoludnÌ (CezroËnÈ obdobie)
#define BIT_OPT_5_DOPLNK_PSALM_122_129     32 // pre modlitbu cez deÚ v doplnkovej psalmÛdii namiesto ûalmu 122 moûno braù ûalm 129
#define BIT_OPT_5_DOPLNK_PSALM_127_131     64 // pre modlitbu cez deÚ v doplnkovej psalmÛdii namiesto ûalmu 127 moûno braù ûalm 131

#define MAX_POCET_OPT                      16 // malo by to byù aspoÚ maximum z POCET_OPT_0_... aû POCET_OPT_5_...

const short int pocet_opt[POCET_GLOBAL_OPT] = {POCET_OPT_0_SPECIALNE, POCET_OPT_1_CASTI_MODLITBY, POCET_OPT_2_HTML_EXPORT, 0 /* option 3 nem· bitovÈ komponenty */, POCET_OPT_4_OFFLINE_EXPORT, POCET_OPT_5_ALTERNATIVES};

// globalna premenna, co obsahuje string vypisany na obsazovku
extern char *_global_string;
extern char *_global_string2; // obsahuje I, II, III, IV, V alebo pismeno roka
extern char *_global_string_farba; // 2006-08-19: doplnenÈ
// 2011-10-04: pridanÈ, pre titulok modlitby (uû sa nepriliepa do _global_string)
// extern char _global_string_modlitba[SMALL];

extern char *_global_buf; // 2006-08-01: t˙to premenn˙ tieû alokujeme
extern char *_global_buf2; // 2006-08-01: t˙to premenn˙ tieû alokujeme

extern short int _global_linky;

// 2006-07-11: PridanÈ kvÙli jazykov˝m mut·ci·m (breviar.cpp) 
// 2010-08-04: zmenenÈ _global_language na _global_jazyk (doteraz bolo len pomocou #define)
extern short int _global_jazyk;
// 2010-08-04: pridanÈ kvÙli kalend·rom (napr. rehoæn˝), s˙visÌ s jazykov˝mi mut·ciami
extern short int _global_kalendar;

extern short int _global_css; // 2008-08-08: PridanÈ kvÙli rÙznym css

extern short int _global_font; // 2011-05-06: PridanÈ kvÙli rÙznym fontom
extern short int _global_font_size; // 2011-05-13: PridanÈ kvÙli rÙznym veækostiam fontov

// 2006-10-17: PridanÈ kvÙli kompletÛriu: niekedy obsahuje aû dva ûalmy
extern short int _global_pocet_zalmov_kompletorium;

extern const char *nazov_jazyka[POCET_JAZYKOV + 1];
extern const char *skratka_jazyka[POCET_JAZYKOV + 1];
extern const char *postfix_jazyka[POCET_JAZYKOV + 1];

extern const char *nazov_kalendara_short[POCET_KALENDAROV + 1];
extern const char *skratka_kalendara[POCET_KALENDAROV + 1];

extern const char *nazov_css[POCET_CSS + 1];
extern const char *skratka_css[POCET_CSS + 1];
extern const char *nazov_css_invert_colors;

extern const char *charset_jazyka[POCET_JAZYKOV + 1];

extern const char *nazov_fontu[POCET_FONTOV + 1];
extern const char *nazov_fontu_CHECKBOX[POCET_JAZYKOV + 1];
extern const char *nazov_fontu_CSS[POCET_FONTOV + 1];

extern const char *nazov_font_size_jazyk[POCET_FONT_SIZE + 1][POCET_JAZYKOV + 1];
extern const char *nazov_font_size_css[POCET_FONT_SIZE + 1];

//---------------------------------------------------------------------

//---------------------------------------------------------------------
// tu nasleduju funkcie(), ibaze by som inkludoval "liturgia.cpp"

short int _allocate_global_var(void);
short int _deallocate_global_var(void);

short int cislo_mesiaca(char *mesiac);
char *caps_BIG(const char *input);
char *remove_diacritics(const char *input);
char *convert_nonbreaking_spaces(const char *input);

char *_vytvor_string_z_datumu(short int den, short int mesiac, short int rok, short int _case, short int typ, short int align);
// podæa toho, ako sa funkcia vol·, urËÌm case (pouûitie veæk˝ch/mal˝ch pÌsmen)
#define vytvor_global_link(den, mesiac, rok, typ, align)	_vytvor_global_link(den, mesiac, rok, CASE_case, typ, align)
#define Vytvor_global_link(den, mesiac, rok, typ, align)	_vytvor_global_link(den, mesiac, rok, CASE_Case, typ, align)
#define VYTVOR_global_link(den, mesiac, rok, typ, align)	_vytvor_global_link(den, mesiac, rok, CASE_CASE, typ, align)
// 2011-05-11: doplnen˝ nov˝ parameter align -- Ëi zarovnaù jednocifernÈ d·tumy (ËÌslovka dÚa) medzerou zæava
void _vytvor_global_link(short int den, short int mesiac, short int rok, short int _case, short int typ, short int align);

#define PRILEP_REQUEST_OPTIONS_DEFAULT   0
#define PRILEP_REQUEST_OPTIONS_AJ_FORCE  1
#define PRILEP_REQUEST_OPTIONS_LEN_FORCE 2
void prilep_request_options(char pom2 [MAX_STR], char pom3 [MAX_STR], short int force_opt = PRILEP_REQUEST_OPTIONS_DEFAULT); // 2013-03-07: pokus; pravdepodobne PRILEP_REQUEST_OPTIONS_LEN_FORCE je neuûitoËnÈ a PRILEP_REQUEST_OPTIONS_AJ_FORCE moûno trocha riskantnÈ...

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
#ifdef FUNKCIE_PRE_SPECIALNE_DNI
short int _svatej_rodiny(short int rok);
short int _krst_krista_pana(short int rok);
short int _popolcova_streda(short int rok);
short int _nanebovstupenie(short int rok);
#endif
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

void analyzuj_rok(short int year);

#define UNKNOWN_PORADIE_SVATEHO 0
// 28/03/2000A.D.: naschval < 0, aby nebol problem s porovnanim s _global_pocet_svatych v _rozbor_dna() 
// 2009-03-19: presunutÈ z breviar.cpp
// 2009-03-27: po z˙fal˝ch pokusoch dnes - napokon som zistil, ûe uû je ˙plne jedno, ak˙ hodnotu bude t·to konötanta maù, preto som ju dal op‰ù na 0

// definovany 2003-08-11 na zaklade funkcie _init_dm() 
// upravenÈ 2007-08-16, pretoûe sa pouûÌva aj v _main_dnes()
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
	a.farba = LIT_FARBA_NEURCENA;\
	a.kalendar = KALENDAR_NEURCENY;\
}

// inicializacne definy pridane 2003-08-13
#define _INIT_ANCHOR_AND_FILE(a) {\
	mystrcpy(a.file, STR_UNDEF, MAX_STR_AF_FILE); \
	mystrcpy(a.anchor, STR_UNDEF, MAX_STR_AF_ANCHOR); \
}

// 2010-05-21: rozöÌrenÈ kvÙli spomienkam a æubovoæn˝m spomienkam v pÙstnom obdobÌ (zobrazenie po modlitbe dÚa pÙstnej fÈrie)
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

// 2006-10-11 doplnenÈ
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
	_INIT_ANCHOR_AND_FILE(a.modlitba); \
};

// 2006-10-11 doplnenÈ
#define _INIT_TMODLITBA4(a) {\
	_INIT_ANCHOR_AND_FILE(a.popis); \
	_INIT_ANCHOR_AND_FILE(a.antifona1); \
	_INIT_ANCHOR_AND_FILE(a.zalm1); \
};

// 2011-03-25: doplnenÈ pre posv‰tnÈ ËÌtanie
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

int _encode_spol_cast(short int, short int, short int);
int _encode_spol_cast(short int, short int);
int _encode_spol_cast(short int);
_struct_sc _decode_spol_cast(int);

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


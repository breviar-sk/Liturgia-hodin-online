/***************************************************************/
/*                                                             */
/* breviar.h                                                   */
/* (c)1999-2011 | Juraj Videky | videky@breviar.sk             */
/*                                                             */
/* description | obsahuje deklaracie globalnych premennych     */
/*               a funkciu main() z dnes.cpp kde su definovane */
/* document history                                            */
/*   30/03/2000A.D. | premenovane dnes --> breviar             */
/*   06/09/2001A.D. | tento popis                              */
/*   2003-07-01a.D. | void main je zakomentovane ak linux      */
/*   2003-07-14a.D. | zmena void main -> int main (gcc v3.2.2 )*/
/*   2003-08-07a.D. | pridane _global_opt 5                    */
/*   2003-08-13a.D. | pridane _type a _global_modl pre posv.cit*/
/*   2006-07-11a.D. | prvé kroky k jazykovým mutáciám          */
/*   2006-08-18a.D. | zmena int na short int (staèí 32tis.)    */
/*   2010-05-14a.D. | presunuté niektoré definy z breviar.cpp  */
/*   2011-02-02a.D. | zadef. MIESTNE_SLAVENIE_CZOP_SVATY1 až 3 */
/*   2011-03-07a.D. | zadef. MIESTNE_SLAVENIE_LOKAL_SVATY1..3  */
/*   2011-03-18a.D. | zadef. PODMIENKA_EXPORTOVAT_KALENDAR     */
/*   2011-03-30a.D. | zadef. prilep_request_options            */
/*                                                             */
/*                                                             */
/***************************************************************/

#include "vstudio.h"

#ifndef __BREVIAR_H_
#define __BREVIAR_H_

#include "liturgia.h"
#include "mysystem.h"
#include "mysysdef.h"

//---------------------------------------------------------------------
/* globalne premenne -- deklarovane v liturgia.h, definovane tu */
/* 18/02/2000A.D. */

extern short int _global_vstup_den;
extern short int _global_vstup_mesiac;
extern short int _global_vstup_rok;
extern short int _global_poradie_svaty;

extern short int query_type; /* premenna obsahujuca PRM_..., deklarovana v mydefs.h */

#define EXPORT_DNA_JEDEN_DEN_LOCAL 5 // 2011-10-03: pridané
#define EXPORT_DNA_VIAC_DNI_TXT 4 // 2011-02-02: pridané
#define EXPORT_DNA_VIAC_DNI_SIMPLE 3 // 2005-03-21: Pridany dalsi typ exportu; 2011-04-13: nerozumiem naèo; asi sa nepoužíva...
#define EXPORT_DNA_JEDEN_DEN 1
#define EXPORT_DNA_VIAC_DNI 2
#define EXPORT_DNA_DNES 0

extern void _export_rozbor_dna_buttons(short int typ, short int poradie_svateho, short int den_zoznam = ANO);
extern void _export_rozbor_dna_buttons_dni(short int typ, short int dnes_dnes = ANO);

extern short int _global_pocet_navigacia; /* 2011-07-03: poèet prejdených/spracovaných parametrov PARAM_NAVIGACIA */

extern short int index_pre_mesiac_otvoreny;
// extern short int export_monthly_druh;

/* globalna premenna, do ktorej sa ukladaju info o analyzovanom dni
 * pouziva ju void nove_rozbor_dna() funkcia */

extern _struct_dm *_global_den_ptr;
/*_struct_dm _global_den;*/
#define _global_den (*_global_den_ptr)

/* globalne premenne, do ktorych sa ukladaju info o analyzovanom dni
 * o sviatkoch svatych */

extern _struct_dm *_global_svaty1_ptr;
/*_struct_dm _global_svaty1;*/
#define _global_svaty1 (*_global_svaty1_ptr)

extern _struct_dm *_global_svaty2_ptr;
/*_struct_dm _global_svaty2;*/ /* v pripade, ze je viac lubovolnych spomienok */
#define _global_svaty2 (*_global_svaty2_ptr)

extern _struct_dm *_global_svaty3_ptr;
/*_struct_dm _global_svaty3;*/ /* v pripade, ze je viac lubovolnych spomienok */
#define _global_svaty3 (*_global_svaty3_ptr)

/* globalna premenna, ktora obsahuje data o spomienke panny marie v sobotu */

extern _struct_dm *_global_pm_sobota_ptr;
/*_struct_dm _global_pm_sobota;*/
#define _global_pm_sobota (*_global_pm_sobota_ptr)

/* globalne premenne obsahujuce data modlitbach */

extern _type_1vespery     *_global_modl_prve_vespery_ptr;
/*_type_1vespery      _global_modl_prve_vespery;*/
#define _global_modl_prve_vespery (*_global_modl_prve_vespery_ptr)

extern _type_1kompletorium *_global_modl_1kompletorium_ptr;
/*_type_1kompletorium _global_modl_prve_kompletorium;*/
#define _global_modl_prve_kompletorium (*_global_modl_1kompletorium_ptr)

extern _type_invitatorium *_global_modl_invitatorium_ptr;
/*_type_invitatorium  _global_modl_invitatorium;*/
#define _global_modl_invitatorium (*_global_modl_invitatorium_ptr)

/* 2003-08-13 pridane posvatne citanie */
extern _type_posv_citanie *_global_modl_posv_citanie_ptr;
#define _global_modl_posv_citanie (*_global_modl_posv_citanie_ptr)

extern _type_ranne_chvaly *_global_modl_ranne_chvaly_ptr;
/*_type_ranne_chvaly  _global_modl_ranne_chvaly;*/
#define _global_modl_ranne_chvaly (*_global_modl_ranne_chvaly_ptr)

extern _type_cez_den_9     *_global_modl_cez_den_9_ptr;
/*_type_cez_den_9     _global_modl_cez_den_9;*/
#define _global_modl_cez_den_9 (*_global_modl_cez_den_9_ptr)
extern _type_cez_den_12     *_global_modl_cez_den_12_ptr;
/*_type_cez_den_12     _global_modl_cez_den_12;*/
#define _global_modl_cez_den_12 (*_global_modl_cez_den_12_ptr)
extern _type_cez_den_3     *_global_modl_cez_den_3_ptr;
/*_type_cez_den_3     _global_modl_cez_den_3;*/
#define _global_modl_cez_den_3 (*_global_modl_cez_den_3_ptr)

extern _type_vespery      *_global_modl_vespery_ptr;
/*_type_vespery       _global_modl_vespery;*/
#define _global_modl_vespery (*_global_modl_vespery_ptr)

extern _type_kompletorium *_global_modl_kompletorium_ptr;
/*_type_kompletorium _global_modl_kompletorium;*/
#define _global_modl_kompletorium (*_global_modl_kompletorium_ptr)

/* globalna premenna, ktora obsahuje MODL_... */
extern short int _global_modlitba;

/* globalna premenna, do ktorej ukladaju funkcie vytvor_query_string_...
 * linku tvaru PATH_CGI(SCRIPT_NAME) ++ "?param1=val&param2=val&..." */
extern char *_global_link_ptr;
/*char _global_link[MAX_STR];*/
#define _global_link _global_link_ptr

extern char *_global_pom_str; /* pomocny string pre velke pismena */
/*char _global_pom_str[MAX_STR];*/

/* globalna premenna, do ktorej sa ukladaju info o jednotlivych
 * vyznacnych liturgickych dni, pouzivaju void _dm_...() funkcie
 * a void analyzuj_rok() funkcia */
extern _struct_dm *_global_result_ptr;
/*_struct_dm _global_result;*/
#define _global_result (*_global_result_ptr)

/* globalna premenna, do ktorej sa uklada info o liturgickom roku
 * pouziva void analyzuj_rok() funkcia */
extern _struct_lrok *_global_r_ptr;
/*_struct_lrok _global_r;*/
#define _global_r (*_global_r_ptr)

/* globalna premenna, do ktorej sviatky_svatych() uklada
 * pocet sviatkov (de facto lubovolnych spomienok), ktore
 * pripadaju na dany den
 * -- v podstate neuklada do nej, ale v _rozbor_dna() sa do nej priradi
 * vysledok (navratova hodnota) z sviatky_svatych()
 */
extern short int _global_pocet_svatych;

/* globálna premenná -- pole -- obsahujúca options; pôvodne to boli globálne premenné _global_opt 1..9 atï., obsahujú pom_MODL_OPT... */
extern short int _global_opt[POCET_GLOBAL_OPT];

/* globalna premenna, co obsahuje string vypisany na obsazovku */
extern char *_global_string;
extern char *_global_string2; /* obsahuje I, II, III, IV, V alebo pismeno roka */
extern char *_global_string_farba; /* 2006-08-19: doplnené */
// 2011-10-04: pridané, pre titulok modlitby (už sa nepriliepa do _global_string)
extern char _global_string_modlitba[SMALL];

extern char *_global_buf; /* 2006-08-01: túto premennú tiež alokujeme */
extern char *_global_buf2; /* 2006-08-01: túto premennú tiež alokujeme */
//---------------------------------------------------------------------

/* 2006-07-11: Pridané kvôli jazykovým mutáciám (breviar.cpp)
 * 2010-08-04: zmenené _global_language na _global_jazyk (doteraz bolo len pomocou #define)
 */
extern short int _global_jazyk;
/* 2010-08-04: pridané kvôli kalendárom (napr. reho¾ný), súvisí s jazykovými mutáciami */
extern short int _global_kalendar;

extern short int _global_css; /* 2008-08-08: Pridané kvôli rôznym css */

extern short int _global_font; /* 2011-05-06: Pridané kvôli rôznym fontom */
extern short int _global_font_size; /* 2011-05-13: Pridané kvôli rôznym ve¾kostiam fontov */

/* 2006-10-17: Pridané kvôli kompletóriu: niekedy obsahuje až dva žalmy */
extern short int _global_pocet_zalmov_kompletorium;

// 2009-08-03, pridané
extern short int _global_opt_batch_monthly;

// 2009-08-05, pridané
extern short int _global_hlavicka_Export;
// extern char name_batch_html_file[MAX_STR];
// 2011-07-01, pridané
extern short int _global_patka_Export;

/* 2011-05-05: kvôli možnosti serif/sans serif override (z css sme odstránili font-family) */
extern char _global_css_font_family[SMALL];
/* 2011-05-13: kvôli možnosti vo¾by ve¾kosti písma */
extern char _global_css_font_size[SMALL];

/* 2009-08-12, pridané */
extern char _global_export_navig_hore[SMALL];
extern short int _global_opt_export_date_format;

/*
 * 2009-01-28: jednotlivé define týkajúce sa riadenia modlitby presunuté sem na zaèiatok súboru, 
 *             nako¾ko ich používa nielen interpretParameter() alebo showPrayer(), ale aj includeFile()
 * 2009-08-11: opravená podmienka pre je_tedeum (odstránené nepotrebné 9.11.)
 * 2010-05-14: definy presunuté z breviar.cpp
 */
#define je_post ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN) || ((_global_den.litobd == OBD_VELKONOCNE_TROJDNIE) && ((_global_den.denvt == DEN_PIATOK) || (_global_den.denvt == DEN_SOBOTA))))
#define je_velka_noc ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II) || ((_global_den.litobd == OBD_VELKONOCNE_TROJDNIE) && (_global_den.denvt == DEN_NEDELA)) || (_global_den.litobd == OBD_VELKONOCNA_OKTAVA))
#define je_aleluja_aleluja ((_global_den.litobd == OBD_VELKONOCNA_OKTAVA) || ((_global_den.litobd == OBD_VELKONOCNE_TROJDNIE) && (_global_den.denvt == DEN_NEDELA)) || (equals(_global_den.meno, _global_r._ZOSLANIE_DUCHA_SV.meno) && (_global_modlitba == MODL_VESPERY)))
#define je_34_ocr ((_global_den.litobd == OBD_CEZ_ROK) && (_global_den.tyzden == 34) && (_global_den.denvt != DEN_NEDELA))
#define je_tedeum (type == MODL_POSV_CITANIE) && (((_global_den.denvt == DEN_NEDELA) && (_global_den.litobd != OBD_POSTNE_I) && (_global_den.litobd != OBD_POSTNE_II_VELKY_TYZDEN)) || (_global_den.typslav == SLAV_SLAVNOST) || (_global_den.typslav == SLAV_SVIATOK) || (_global_den.litobd == OBD_VELKONOCNA_OKTAVA) || (_global_den.litobd == OBD_OKTAVA_NARODENIA))
/* 2010-05-24: doplnené; 2011-03-16: rozšírené o posvätné èítanie */
#define je_ant_modl_spom_post (( \
(_global_modlitba == MODL_RANNE_CHVALY &&  \
	(_global_modl_ranne_chvaly.ant_spompost.anchor != NULL) && (_global_modl_ranne_chvaly.ant_spompost.file != NULL) && \
	(_global_modl_ranne_chvaly.modlitba_spompost.anchor != NULL) && (_global_modl_ranne_chvaly.modlitba_spompost.file != NULL) && \
	(!equals(_global_modl_ranne_chvaly.ant_spompost.anchor, STR_EMPTY)) && (!equals(_global_modl_ranne_chvaly.ant_spompost.anchor, STR_UNDEF)) &&  \
	(!equals(_global_modl_ranne_chvaly.modlitba_spompost.anchor, STR_EMPTY)) && (!equals(_global_modl_ranne_chvaly.modlitba_spompost.anchor, STR_UNDEF)) && \
	(!equals(_global_modl_ranne_chvaly.ant_spompost.file, STR_EMPTY)) && (!equals(_global_modl_ranne_chvaly.ant_spompost.file, STR_UNDEF)) &&  \
	(!equals(_global_modl_ranne_chvaly.modlitba_spompost.file, STR_EMPTY)) && (!equals(_global_modl_ranne_chvaly.modlitba_spompost.file, STR_UNDEF)) \
) \
||  \
(_global_modlitba == MODL_VESPERY &&  \
	(_global_modl_vespery.ant_spompost.anchor != NULL) && (_global_modl_vespery.ant_spompost.file != NULL) && \
	(_global_modl_vespery.modlitba_spompost.anchor != NULL) && (_global_modl_vespery.modlitba_spompost.file != NULL) && \
	(strcmp(_global_modl_vespery.ant_spompost.anchor, STR_EMPTY) != 0) && (strcmp(_global_modl_vespery.ant_spompost.anchor, STR_UNDEF) != 0) &&  \
	(strcmp(_global_modl_vespery.modlitba_spompost.anchor, STR_EMPTY) != 0) && (strcmp(_global_modl_vespery.modlitba_spompost.anchor, STR_UNDEF) != 0) && \
	(strcmp(_global_modl_vespery.ant_spompost.file, STR_EMPTY) != 0) && (strcmp(_global_modl_vespery.ant_spompost.file, STR_UNDEF) != 0) &&  \
	(strcmp(_global_modl_vespery.modlitba_spompost.file, STR_EMPTY) != 0) && (strcmp(_global_modl_vespery.modlitba_spompost.file, STR_UNDEF) != 0) \
) \
||  \
(_global_modlitba == MODL_POSV_CITANIE &&  \
	(_global_modl_posv_citanie.citanie_spompost.anchor != NULL) && (_global_modl_posv_citanie.citanie_spompost.file != NULL) && \
	(strcmp(_global_modl_posv_citanie.citanie_spompost.anchor, STR_EMPTY) != 0) && (strcmp(_global_modl_posv_citanie.citanie_spompost.anchor, STR_UNDEF) != 0) &&  \
	(strcmp(_global_modl_posv_citanie.citanie_spompost.file, STR_EMPTY) != 0) && (strcmp(_global_modl_posv_citanie.citanie_spompost.file, STR_UNDEF) != 0) \
) \
))

// 2011-02-02: presunuté do #define -- kontrola, ktorá zabezpeèuje, že normálne správanie sa slávení nie je prebité pre "CZOP miestne slávenia"
#define MIESTNE_SLAVENIE_CZOP_SVATY1 ((_global_svaty1.kalendar == KALENDAR_CZ_OP) && ((_global_svaty1.smer == 4) || (_global_svaty1.smer == 8) || (_global_svaty1.smer == 11)))
#define MIESTNE_SLAVENIE_CZOP_SVATY2 ((_global_svaty2.kalendar == KALENDAR_CZ_OP) && ((_global_svaty2.smer == 4) || (_global_svaty2.smer == 8) || (_global_svaty2.smer == 11)))
#define MIESTNE_SLAVENIE_CZOP_SVATY3 ((_global_svaty3.kalendar == KALENDAR_CZ_OP) && ((_global_svaty3.smer == 4) || (_global_svaty3.smer == 8) || (_global_svaty3.smer == 11)))

// 2011-03-07: MIESTNE_SLAVENIE_CZOP_SVATY1 až 3 aj pre slovenské, ktoré majú nastavené "lokálne" verzie
#define MIESTNE_SLAVENIE_LOKAL_SVATY1 (((_global_svaty1.kalendar == KALENDAR_CZ_OP) || (_global_svaty1.kalendar == KALENDAR_SK_CSSR) || (_global_svaty1.kalendar == KALENDAR_SK_SVD) || (_global_svaty1.kalendar == KALENDAR_SK_SJ) || (_global_svaty1.kalendar == KALENDAR_SK_SDB) || (_global_svaty1.kalendar == KALENDAR_SK_OFM) || (_global_svaty1.typslav_lokal != LOKAL_SLAV_NEURCENE)) && ((_global_svaty1.smer == 4) || (_global_svaty1.smer == 8) || (_global_svaty1.smer == 11)))
#define MIESTNE_SLAVENIE_LOKAL_SVATY2 (((_global_svaty1.kalendar == KALENDAR_CZ_OP) || (_global_svaty1.kalendar == KALENDAR_SK_CSSR) || (_global_svaty1.kalendar == KALENDAR_SK_SVD) || (_global_svaty1.kalendar == KALENDAR_SK_SJ) || (_global_svaty1.kalendar == KALENDAR_SK_SDB) || (_global_svaty1.kalendar == KALENDAR_SK_OFM) || (_global_svaty2.typslav_lokal != LOKAL_SLAV_NEURCENE)) && ((_global_svaty2.smer == 4) || (_global_svaty2.smer == 8) || (_global_svaty2.smer == 11)))
#define MIESTNE_SLAVENIE_LOKAL_SVATY3 (((_global_svaty1.kalendar == KALENDAR_CZ_OP) || (_global_svaty1.kalendar == KALENDAR_SK_CSSR) || (_global_svaty1.kalendar == KALENDAR_SK_SVD) || (_global_svaty1.kalendar == KALENDAR_SK_SJ) || (_global_svaty1.kalendar == KALENDAR_SK_SDB) || (_global_svaty1.kalendar == KALENDAR_SK_OFM) || (_global_svaty3.typslav_lokal != LOKAL_SLAV_NEURCENE)) && ((_global_svaty3.smer == 4) || (_global_svaty3.smer == 8) || (_global_svaty3.smer == 11)))

/* 2011-03-18: presunuté samostatne na jedno jediné miesto */
#define PODMIENKA_EXPORTOVAT_KALENDAR ( \
((_global_jazyk == JAZYK_SK) && !((_global_kalendar == KALENDAR_NEURCENY) || (_global_kalendar == KALENDAR_VSEOBECNY) || (_global_kalendar == KALENDAR_VSEOBECNY_SK) )) \
|| ((_global_jazyk == JAZYK_CZ) && !((_global_kalendar == KALENDAR_NEURCENY) || (_global_kalendar == KALENDAR_VSEOBECNY) || (_global_kalendar == KALENDAR_VSEOBECNY_CZ) )) \
|| ((_global_jazyk == JAZYK_CZ_OP) && !((_global_kalendar == KALENDAR_NEURCENY) || (_global_kalendar == KALENDAR_VSEOBECNY) || (_global_kalendar == KALENDAR_VSEOBECNY_CZ) || (_global_kalendar == KALENDAR_CZ_OP) )) \
)

#ifndef OS_linux
/* kedysi bolo void main;
 * 2003-07-14, kvoli gcc version 3.2.2 20030222 (Red Hat Linux 3.2.2-5) christ-net.sk 
 */
int main(int argc, char **argv);
#endif /* OS_linux */

#if (_MSC_VER >= 1400)       // VC8+ 2007-02-12 kvôli vc++ 2005 express edition
	#pragma warning(disable : 4996)    // disable all deprecation warnings
	#define putenv _putenv
#endif   // VC8+

#endif /* __BREVIAR_H_ */


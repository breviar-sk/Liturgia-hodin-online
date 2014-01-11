/***************************************************************/
/*                                                             */
/* breviar.h                                                   */
/* (c)1999-2014 | Juraj Vidéky | videky@breviar.sk             */
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
/*   2011-02-02a.D. | zadef. MIESTNE_SLAVENIE_CZOP_SVATY(i)    */
/*   2011-03-07a.D. | zadef. MIESTNE_SLAVENIE_LOKAL_SVATY(i)   */
/*   2011-03-18a.D. | zadef. PODMIENKA_EXPORTOVAT_KALENDAR     */
/*   2011-03-30a.D. | zadef. prilep_request_options            */
/*   2012-04-02a.D. | presunuté dôležité defines z breviar.cpp */
/*                                                             */
/*                                                             */
/***************************************************************/

#include "vstudio.h"

#ifndef __BREVIAR_H_
#define __BREVIAR_H_

#include "liturgia.h"
#include "mysystem.h"
#include "mysysdef.h"

#define TYZZAL(t)					(((t + 3) MOD 4) + 1)
#define TYZZAL_PREDCHADZAJUCI(t)	(((t + 2) MOD 4) + 1)
#define TYZZAL_NASLEDUJUCI(t)		(((t + 4) MOD 4) + 1)

#define UPRAV_TYZZAL(t, m)			( (m == MODL_NAPOLUDNIE)? TYZZAL_PREDCHADZAJUCI(t) : ((m == MODL_POPOLUDNI)? TYZZAL_NASLEDUJUCI(t) : TYZZAL(t)) )

//---------------------------------------------------------------------
// globalne premenne -- deklarovane v liturgia.h, definovane tu

extern short int _global_vstup_den;
extern short int _global_vstup_mesiac;
extern short int _global_vstup_rok;
extern short int _global_poradie_svaty;

extern short int query_type; // premenna obsahujuca PRM_..., deklarovana v mydefs.h

#define EXPORT_DNA_XML 6 // 2012-10-12: kvôli iOS
#define EXPORT_DNA_JEDEN_DEN_LOCAL 5
#define EXPORT_DNA_VIAC_DNI_TXT 4
#define EXPORT_DNA_VIAC_DNI_SIMPLE 3 // 2005-03-21: Pridany dalsi typ exportu; 2011-04-13: nerozumiem naèo; asi sa nepoužíva...
#define EXPORT_DNA_JEDEN_DEN 1
#define EXPORT_DNA_VIAC_DNI 2
#define EXPORT_DNA_DNES 0

#define EXPORT_TYP_WEB_MODE 0
#define EXPORT_TYP_BATCH_MODE 1

extern void _export_rozbor_dna_buttons(short int typ, short int poradie_svateho, short int den_zoznam = ANO, short int zobrazit_mcd = ANO);
extern void _export_rozbor_dna_buttons_dni_dnes(short int dnes_dnes, short int som_v_tabulke, char pom2[MAX_STR], short int zobraz_odkaz_na_skrytie);
extern void _export_rozbor_dna_buttons_dni(short int typ, short int dnes_dnes = ANO);
extern void _export_rozbor_dna_buttons_dni_orig(short int typ, short int dnes_dnes = ANO);
extern void _export_rozbor_dna_buttons_dni_compact(short int typ, short int dnes_dnes = ANO);
extern void _export_rozbor_dna_buttons_dni_call(short int typ, short int dnes_dnes = ANO);
extern void _export_rozbor_dna_kalendar_orig(short int typ);
extern void _export_rozbor_dna_kalendar(short int typ);

extern short int _global_pocet_navigacia; // 2011-07-03: poèet prejdených/spracovaných parametrov PARAM_NAVIGACIA

extern short int index_pre_mesiac_otvoreny;
// extern short int export_monthly_druh;

// globalna premenna, do ktorej sa ukladaju info o analyzovanom dni
extern _struct_dm *_global_den_ptr;
#define _global_den (*_global_den_ptr)

// globalne premenne, do ktorych sa ukladaju info o analyzovanom dni o sviatkoch svatych
extern _struct_dm *(_global_svaty_ptr[MAX_POCET_SVATY]); // an array of '_struct_dm' pointers
#define _global_svaty(i) (*(_global_svaty_ptr[i - 1]))
#define _global_svaty1 (*_global_svaty_ptr[0])
#define _global_svaty2 (*_global_svaty_ptr[1])
#define _global_svaty3 (*_global_svaty_ptr[2])
#define _global_svaty4 (*_global_svaty_ptr[3])
#define _global_svaty5 (*_global_svaty_ptr[4])

// globalna premenna, ktora obsahuje data o spomienke panny marie v sobotu
extern _struct_dm *_global_pm_sobota_ptr;
#define _global_pm_sobota (*_global_pm_sobota_ptr)

// globalne premenne obsahujuce data modlitbach

extern _type_1vespery     *_global_modl_prve_vespery_ptr;
// _type_1vespery      _global_modl_prve_vespery;
#define _global_modl_prve_vespery (*_global_modl_prve_vespery_ptr)

extern _type_1kompletorium *_global_modl_1kompletorium_ptr;
// _type_1kompletorium _global_modl_prve_kompletorium;
#define _global_modl_prve_kompletorium (*_global_modl_1kompletorium_ptr)

extern _type_invitatorium *_global_modl_invitatorium_ptr;
// _type_invitatorium  _global_modl_invitatorium;
#define _global_modl_invitatorium (*_global_modl_invitatorium_ptr)

extern _type_posv_citanie *_global_modl_posv_citanie_ptr;
#define _global_modl_posv_citanie (*_global_modl_posv_citanie_ptr)

extern _type_ranne_chvaly *_global_modl_ranne_chvaly_ptr;
// _type_ranne_chvaly  _global_modl_ranne_chvaly;
#define _global_modl_ranne_chvaly (*_global_modl_ranne_chvaly_ptr)

extern _type_cez_den_9     *_global_modl_cez_den_9_ptr;
// _type_cez_den_9     _global_modl_cez_den_9;
#define _global_modl_cez_den_9 (*_global_modl_cez_den_9_ptr)
extern _type_cez_den_12     *_global_modl_cez_den_12_ptr;
// _type_cez_den_12     _global_modl_cez_den_12;
#define _global_modl_cez_den_12 (*_global_modl_cez_den_12_ptr)
extern _type_cez_den_3     *_global_modl_cez_den_3_ptr;
// _type_cez_den_3     _global_modl_cez_den_3;
#define _global_modl_cez_den_3 (*_global_modl_cez_den_3_ptr)

extern _type_vespery      *_global_modl_vespery_ptr;
// _type_vespery       _global_modl_vespery;
#define _global_modl_vespery (*_global_modl_vespery_ptr)

extern _type_kompletorium *_global_modl_kompletorium_ptr;
// _type_kompletorium _global_modl_kompletorium;
#define _global_modl_kompletorium (*_global_modl_kompletorium_ptr)

// globalna premenna, ktora obsahuje MODL_...
extern short int _global_modlitba;

// globalna premenna, do ktorej ukladaju funkcie vytvor_query_string_... linku tvaru PATH_CGI(SCRIPT_NAME) ++ "?param1=val&param2=val&..."
extern char *_global_link_ptr;
// char _global_link[MAX_STR];
#define _global_link _global_link_ptr

extern char *_global_pom_str; // pomocny string pre velke pismena
// char _global_pom_str[MAX_STR];

// globalna premenna, do ktorej sa ukladaju info o jednotlivych vyznacnych liturgickych dni, pouzivaju void _dm_...() funkcie a void analyzuj_rok() funkcia
extern _struct_dm *_global_result_ptr;
// _struct_dm _global_result;
#define _global_result (*_global_result_ptr)

// globalna premenna, do ktorej sa uklada info o liturgickom roku pouziva void analyzuj_rok() funkcia
extern _struct_lrok *_global_r_ptr;
// _struct_lrok _global_r;
#define _global_r (*_global_r_ptr)

// globalna premenna, do ktorej sviatky_svatych() uklada pocet sviatkov (de facto lubovolnych spomienok), ktore pripadaju na dany den
// -- v podstate neuklada do nej, ale v _rozbor_dna() sa do nej priradi vysledok (navratova hodnota) z sviatky_svatych()
extern short int _global_pocet_svatych;

// globálna premenná -- pole -- obsahujúca options; pôvodne to boli globálne premenné _global_opt 1..9 atï., obsahujú pom_MODL_OPT...
extern short int _global_opt[POCET_GLOBAL_OPT];
// globálna premenná -- pole -- obsahujúca force options; pôvodne to boli globálne premenné _global_optf 1..9 atï., obsahujú pom_MODL_OPTF...
extern short int _global_optf[POCET_GLOBAL_OPT];

// globalna premenna, co obsahuje string vypisany na obsazovku
extern char *_global_string;
extern char *_global_string2; // obsahuje I, II, III, IV, V alebo pismeno roka
extern char *_global_string_farba;
// 2011-10-04: pridané, pre titulok modlitby (už sa nepriliepa do _global_string)
// extern char _global_string_modlitba[SMALL];

extern char *_global_buf; // 2006-08-01: túto premennú tiež alokujeme
extern char *_global_buf2; // 2006-08-01: túto premennú tiež alokujeme
//---------------------------------------------------------------------

// 2006-07-11: Pridané kvôli jazykovým mutáciám (breviar.cpp)
// 2010-08-04: zmenené _global_language na _global_jazyk (doteraz bolo len pomocou #define)
extern short int _global_jazyk;
// 2010-08-04: pridané kvôli kalendárom (napr. reho¾ný), súvisí s jazykovými mutáciami
extern short int _global_kalendar;

extern short int _global_css; // 2008-08-08: Pridané kvôli rôznym css

extern short int _global_font; // 2011-05-06: Pridané kvôli rôznym fontom
extern short int _global_font_size; // 2011-05-13: Pridané kvôli rôznym ve¾kostiam fontov

// 2006-10-17: Pridané kvôli kompletóriu: niekedy obsahuje až dva žalmy
extern short int _global_pocet_zalmov_kompletorium;

// 2009-08-03, pridané
extern short int _global_opt_batch_monthly;

// 2009-08-05, pridané
extern short int _global_hlavicka_Export;
// extern char name_batch_html_file[MAX_STR];
// 2011-07-01, pridané
extern short int _global_patka_Export;

// 2011-05-05: kvôli možnosti serif/sans serif override (z css sme odstránili font-family)
extern char _global_css_font_family[SMALL];
// 2011-05-13: kvôli možnosti vo¾by ve¾kosti písma
extern char _global_css_font_size[SMALL];

// 2009-08-12, pridané
extern char _global_export_navig_hore[SMALL];
extern short int _global_opt_export_date_format;

// 2009-01-28: jednotlivé define týkajúce sa riadenia modlitby presunuté sem na zaèiatok súboru, nako¾ko ich používa nielen interpretParameter() alebo showPrayer(), ale aj includeFile()
// 2009-08-11: opravená podmienka pre je_tedeum (odstránené nepotrebné 9.11.)
// 2010-05-14: definy presunuté z breviar.cpp
// 2012-02-09: definované je_privileg pre testovanie, èi ide o privilegované dni (VSLH è. 238-239): to isté ako je_post + december poènúc 17.-tym (všedné di od 17. do 24. decembra a Vianoèná oktáva); striktne by tu nemal by ve¾ký týždeò a ve¾konoèné trojdnie, ale nezaškodí to tu
#define je_privileg ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN) || ((_global_den.litobd == OBD_VELKONOCNE_TROJDNIE) && ((_global_den.denvt == DEN_PIATOK) || (_global_den.denvt == DEN_SOBOTA))) || ((_global_den.mesiac - 1 == MES_DEC) && (_global_den.den >= 17)))
#define je_post ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN) || ((_global_den.litobd == OBD_VELKONOCNE_TROJDNIE) && ((_global_den.denvt == DEN_PIATOK) || (_global_den.denvt == DEN_SOBOTA))))
#define je_velka_noc ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II) || ((_global_den.litobd == OBD_VELKONOCNE_TROJDNIE) && (_global_den.denvt == DEN_NEDELA)) || (_global_den.litobd == OBD_VELKONOCNA_OKTAVA))
#define je_aleluja_aleluja ((_global_den.litobd == OBD_VELKONOCNA_OKTAVA) || ((_global_den.litobd == OBD_VELKONOCNE_TROJDNIE) && (_global_den.denvt == DEN_NEDELA)) || ((_global_den.denvr == _global_r._ZOSLANIE_DUCHA_SV.denvr) && ((_global_modlitba == MODL_VESPERY) || (_global_modlitba == MODL_DRUHE_VESPERY))))
#define je_34_ocr ((_global_den.litobd == OBD_CEZ_ROK) && (_global_den.tyzden == 34) && (_global_den.denvt != DEN_NEDELA))
#define je_tedeum (type == MODL_POSV_CITANIE) && (((_global_den.denvt == DEN_NEDELA) && (_global_den.litobd != OBD_POSTNE_I) && (_global_den.litobd != OBD_POSTNE_II_VELKY_TYZDEN)) || (_global_den.typslav == SLAV_SLAVNOST) || (_global_den.typslav == SLAV_SVIATOK) || (_global_den.litobd == OBD_VELKONOCNA_OKTAVA) || (_global_den.litobd == OBD_OKTAVA_NARODENIA))
// 2010-05-24: doplnené; 2011-03-16: rozšírené o posvätné èítanie
#define je_ant_modl_spomprivileg (( \
(_global_modlitba == MODL_RANNE_CHVALY &&  \
	(_global_modl_ranne_chvaly.ant_spomprivileg.anchor != NULL) && (_global_modl_ranne_chvaly.ant_spomprivileg.file != NULL) && \
	(_global_modl_ranne_chvaly.modlitba_spomprivileg.anchor != NULL) && (_global_modl_ranne_chvaly.modlitba_spomprivileg.file != NULL) && \
	(!equals(_global_modl_ranne_chvaly.ant_spomprivileg.anchor, STR_EMPTY)) && (!equals(_global_modl_ranne_chvaly.ant_spomprivileg.anchor, STR_UNDEF)) &&  \
	(!equals(_global_modl_ranne_chvaly.modlitba_spomprivileg.anchor, STR_EMPTY)) && (!equals(_global_modl_ranne_chvaly.modlitba_spomprivileg.anchor, STR_UNDEF)) && \
	(!equals(_global_modl_ranne_chvaly.ant_spomprivileg.file, STR_EMPTY)) && (!equals(_global_modl_ranne_chvaly.ant_spomprivileg.file, STR_UNDEF)) &&  \
	(!equals(_global_modl_ranne_chvaly.modlitba_spomprivileg.file, STR_EMPTY)) && (!equals(_global_modl_ranne_chvaly.modlitba_spomprivileg.file, STR_UNDEF)) \
) \
||  \
(_global_modlitba == MODL_VESPERY &&  \
	(_global_modl_vespery.ant_spomprivileg.anchor != NULL) && (_global_modl_vespery.ant_spomprivileg.file != NULL) && \
	(_global_modl_vespery.modlitba_spomprivileg.anchor != NULL) && (_global_modl_vespery.modlitba_spomprivileg.file != NULL) && \
	(strcmp(_global_modl_vespery.ant_spomprivileg.anchor, STR_EMPTY) != 0) && (strcmp(_global_modl_vespery.ant_spomprivileg.anchor, STR_UNDEF) != 0) &&  \
	(strcmp(_global_modl_vespery.modlitba_spomprivileg.anchor, STR_EMPTY) != 0) && (strcmp(_global_modl_vespery.modlitba_spomprivileg.anchor, STR_UNDEF) != 0) && \
	(strcmp(_global_modl_vespery.ant_spomprivileg.file, STR_EMPTY) != 0) && (strcmp(_global_modl_vespery.ant_spomprivileg.file, STR_UNDEF) != 0) &&  \
	(strcmp(_global_modl_vespery.modlitba_spomprivileg.file, STR_EMPTY) != 0) && (strcmp(_global_modl_vespery.modlitba_spomprivileg.file, STR_UNDEF) != 0) \
) \
||  \
(_global_modlitba == MODL_POSV_CITANIE &&  \
	(_global_modl_posv_citanie.citanie_spomprivileg.anchor != NULL) && (_global_modl_posv_citanie.citanie_spomprivileg.file != NULL) && \
	(strcmp(_global_modl_posv_citanie.citanie_spomprivileg.anchor, STR_EMPTY) != 0) && (strcmp(_global_modl_posv_citanie.citanie_spomprivileg.anchor, STR_UNDEF) != 0) &&  \
	(strcmp(_global_modl_posv_citanie.citanie_spomprivileg.file, STR_EMPTY) != 0) && (strcmp(_global_modl_posv_citanie.citanie_spomprivileg.file, STR_UNDEF) != 0) \
) \
))
// 2012-05-24: doplnené -- predåžené slávenie vigílií v rámci posvätných èítaní
#define je_vigilia \
(_global_modlitba == MODL_POSV_CITANIE &&  \
	(_global_modl_posv_citanie.ant_chval.anchor != NULL) && (_global_modl_posv_citanie.ant_chval.file != NULL) && \
	(strcmp(_global_modl_posv_citanie.ant_chval.anchor, STR_EMPTY) != 0) && (strcmp(_global_modl_posv_citanie.ant_chval.anchor, STR_UNDEF) != 0) &&  \
	(strcmp(_global_modl_posv_citanie.ant_chval.file, STR_EMPTY) != 0) && (strcmp(_global_modl_posv_citanie.ant_chval.file, STR_UNDEF) != 0) && \
	(_global_modl_posv_citanie.chval1.anchor != NULL) && (_global_modl_posv_citanie.chval1.file != NULL) && \
	(strcmp(_global_modl_posv_citanie.chval1.anchor, STR_EMPTY) != 0) && (strcmp(_global_modl_posv_citanie.chval1.anchor, STR_UNDEF) != 0) &&  \
	(strcmp(_global_modl_posv_citanie.chval1.file, STR_EMPTY) != 0) && (strcmp(_global_modl_posv_citanie.chval1.file, STR_UNDEF) != 0) && \
	(_global_modl_posv_citanie.chval2.anchor != NULL) && (_global_modl_posv_citanie.chval2.file != NULL) && \
	(strcmp(_global_modl_posv_citanie.chval2.anchor, STR_EMPTY) != 0) && (strcmp(_global_modl_posv_citanie.chval2.anchor, STR_UNDEF) != 0) &&  \
	(strcmp(_global_modl_posv_citanie.chval2.file, STR_EMPTY) != 0) && (strcmp(_global_modl_posv_citanie.chval2.file, STR_UNDEF) != 0) && \
	(_global_modl_posv_citanie.chval3.anchor != NULL) && (_global_modl_posv_citanie.chval3.file != NULL) && \
	(strcmp(_global_modl_posv_citanie.chval3.anchor, STR_EMPTY) != 0) && (strcmp(_global_modl_posv_citanie.chval3.anchor, STR_UNDEF) != 0) &&  \
	(strcmp(_global_modl_posv_citanie.chval3.file, STR_EMPTY) != 0) && (strcmp(_global_modl_posv_citanie.chval3.file, STR_UNDEF) != 0) && \
	(_global_modl_posv_citanie.evanjelium.anchor != NULL) && (_global_modl_posv_citanie.evanjelium.file != NULL) && \
	(strcmp(_global_modl_posv_citanie.evanjelium.anchor, STR_EMPTY) != 0) && (strcmp(_global_modl_posv_citanie.evanjelium.anchor, STR_UNDEF) != 0) &&  \
	(strcmp(_global_modl_posv_citanie.evanjelium.file, STR_EMPTY) != 0) && (strcmp(_global_modl_posv_citanie.evanjelium.file, STR_UNDEF) != 0) \
)
// 2012-10-01: doplnené
#define je_popis (( \
(_global_modlitba == MODL_RANNE_CHVALY &&  \
	(_global_modl_ranne_chvaly.popis.anchor != NULL) && (_global_modl_ranne_chvaly.popis.file != NULL) && \
	!(equals(_global_modl_ranne_chvaly.popis.anchor, STR_UNDEF)) && !(equals(_global_modl_ranne_chvaly.popis.file, STR_UNDEF)) \
) \
||  \
(_global_modlitba == MODL_VESPERY &&  \
	(_global_modl_vespery.popis.anchor != NULL) && (_global_modl_vespery.popis.file != NULL) && \
	!(equals(_global_modl_vespery.popis.anchor, STR_UNDEF)) && !(equals(_global_modl_vespery.popis.file, STR_UNDEF)) \
) \
||  \
(_global_modlitba == MODL_POSV_CITANIE &&  \
	(_global_modl_posv_citanie.popis.anchor != NULL) && (_global_modl_posv_citanie.popis.file != NULL) && \
	!(equals(_global_modl_posv_citanie.popis.anchor, STR_UNDEF)) && !(equals(_global_modl_posv_citanie.popis.file, STR_UNDEF)) \
) \
||  \
(_global_modlitba == MODL_PREDPOLUDNIM &&  \
	(_global_modl_cez_den_9.popis.anchor != NULL) && (_global_modl_cez_den_9.popis.file != NULL) && \
	!(equals(_global_modl_cez_den_9.popis.anchor, STR_UNDEF)) && !(equals(_global_modl_cez_den_9.popis.file, STR_UNDEF)) \
) \
||  \
(_global_modlitba == MODL_NAPOLUDNIE &&  \
	(_global_modl_cez_den_12.popis.anchor != NULL) && (_global_modl_cez_den_12.popis.file != NULL) && \
	!(equals(_global_modl_cez_den_12.popis.anchor, STR_UNDEF)) && !(equals(_global_modl_cez_den_12.popis.file, STR_UNDEF)) \
) \
||  \
(_global_modlitba == MODL_POPOLUDNI &&  \
	(_global_modl_cez_den_3.popis.anchor != NULL) && (_global_modl_cez_den_3.popis.file != NULL) && \
	!(equals(_global_modl_cez_den_3.popis.anchor, STR_UNDEF)) && !(equals(_global_modl_cez_den_3.popis.file, STR_UNDEF)) \
) \
||  \
(_global_modlitba == MODL_INVITATORIUM &&  \
	(_global_modl_invitatorium.popis.anchor != NULL) && (_global_modl_invitatorium.popis.file != NULL) && \
	!(equals(_global_modl_invitatorium.popis.anchor, STR_UNDEF)) && !(equals(_global_modl_invitatorium.popis.file, STR_UNDEF)) \
) \
||  \
(_global_modlitba == MODL_KOMPLETORIUM &&  \
	(_global_modl_kompletorium.popis.anchor != NULL) && (_global_modl_kompletorium.popis.file != NULL) && \
	!(equals(_global_modl_kompletorium.popis.anchor, STR_UNDEF)) && !(equals(_global_modl_kompletorium.popis.file, STR_UNDEF)) \
) \
))

// 2013-04-05: doplnené -- èi sa NEMAJÚ zobrazova vešpery; doteraz sa kontrolovalo len to, èi je sobota -- opravené pre Ve¾kú (bielu) sobotu
#define nie_su_vespery ( \
	(_global_den.denvt == DEN_SOBOTA) && (!((_global_den.denvt == DEN_SOBOTA) && (_global_den.litobd == OBD_VELKONOCNE_TROJDNIE))) \
)

// 2013-05-14: doplnené aj ve¾konoèné alternatívne hymny
#define je_alternativa_hymnus ( \
(_global_modlitba == MODL_PRVE_KOMPLETORIUM && ((_global_modl_prve_kompletorium.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
||  \
(_global_modlitba == MODL_DRUHE_KOMPLETORIUM && ((_global_modl_kompletorium.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
||  \
(_global_modlitba == MODL_KOMPLETORIUM && ((_global_modl_kompletorium.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
||  \
(_global_modlitba == MODL_POSV_CITANIE && ((_global_modl_posv_citanie.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
||  \
(_global_modlitba == MODL_PREDPOLUDNIM && ((_global_modl_predpol.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
||  \
(_global_modlitba == MODL_NAPOLUDNIE && ((_global_modl_napol.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
||  \
(_global_modlitba == MODL_POPOLUDNI && ((_global_modl_popol.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
||  \
(_global_modlitba == MODL_RANNE_CHVALY && ((_global_modl_ranne_chvaly.alternativy & BIT_ALT_HYMNUS_VN) == BIT_ALT_HYMNUS_VN)) \
||  \
(_global_modlitba == MODL_POSV_CITANIE && ((_global_modl_posv_citanie.alternativy & BIT_ALT_HYMNUS_VN) == BIT_ALT_HYMNUS_VN)) \
||  \
(_global_modlitba == MODL_VESPERY && ((_global_modl_vespery.alternativy & BIT_ALT_HYMNUS_VN) == BIT_ALT_HYMNUS_VN)) \
)

#define je_alternativa_hymnus_ocr ( \
(_global_modlitba == MODL_PRVE_KOMPLETORIUM && ((_global_modl_prve_kompletorium.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
||  \
(_global_modlitba == MODL_DRUHE_KOMPLETORIUM && ((_global_modl_kompletorium.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
||  \
(_global_modlitba == MODL_KOMPLETORIUM && ((_global_modl_kompletorium.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
||  \
(_global_modlitba == MODL_POSV_CITANIE && ((_global_modl_posv_citanie.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
||  \
(_global_modlitba == MODL_PREDPOLUDNIM && ((_global_modl_predpol.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
||  \
(_global_modlitba == MODL_NAPOLUDNIE && ((_global_modl_napol.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
||  \
(_global_modlitba == MODL_POPOLUDNI && ((_global_modl_popol.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
)

#define je_alternativa_hymnus_vn ( \
(_global_modlitba == MODL_RANNE_CHVALY && ((_global_modl_ranne_chvaly.alternativy & BIT_ALT_HYMNUS_VN) == BIT_ALT_HYMNUS_VN)) \
||  \
(_global_modlitba == MODL_POSV_CITANIE && ((_global_modl_posv_citanie.alternativy & BIT_ALT_HYMNUS_VN) == BIT_ALT_HYMNUS_VN)) \
||  \
(_global_modlitba == MODL_VESPERY && ((_global_modl_vespery.alternativy & BIT_ALT_HYMNUS_VN) == BIT_ALT_HYMNUS_VN)) \
)


// 2013-02-13: doplnené
#define je_len_doplnkova_psalmodia(modlitba) (\
	((modlitba == MODL_PREDPOLUDNIM) && ((_global_modl_predpol.alternativy & BIT_ALT_LEN_DOPLNKOVA_PSALMODIA) == BIT_ALT_LEN_DOPLNKOVA_PSALMODIA)) \
||  \
	((modlitba == MODL_NAPOLUDNIE) && ((_global_modl_napol.alternativy & BIT_ALT_LEN_DOPLNKOVA_PSALMODIA) == BIT_ALT_LEN_DOPLNKOVA_PSALMODIA)) \
||  \
	((modlitba == MODL_POPOLUDNI) && ((_global_modl_popol.alternativy & BIT_ALT_LEN_DOPLNKOVA_PSALMODIA) == BIT_ALT_LEN_DOPLNKOVA_PSALMODIA)) \
)

// 2013-02-26: doplnené
// staèilo by len: modlitba predpoludním
#define je_alternativa_doplnkova_psalmodia_z122_129(modlitba) (\
	((modlitba == MODL_PREDPOLUDNIM) && ((_global_modl_predpol.alternativy & BIT_ALT_DOPLNK_PSALM_122_129) == BIT_ALT_DOPLNK_PSALM_122_129)) \
||  \
	((modlitba == MODL_NAPOLUDNIE) && ((_global_modl_napol.alternativy & BIT_ALT_DOPLNK_PSALM_122_129) == BIT_ALT_DOPLNK_PSALM_122_129)) \
||  \
	((modlitba == MODL_POPOLUDNI) && ((_global_modl_popol.alternativy & BIT_ALT_DOPLNK_PSALM_122_129) == BIT_ALT_DOPLNK_PSALM_122_129)) \
)
// staèilo by len: modlitba popoludní
#define je_alternativa_doplnkova_psalmodia_z127_131(modlitba) (\
	((modlitba == MODL_PREDPOLUDNIM) && ((_global_modl_predpol.alternativy & BIT_ALT_DOPLNK_PSALM_127_131) == BIT_ALT_DOPLNK_PSALM_127_131)) \
||  \
	((modlitba == MODL_NAPOLUDNIE) && ((_global_modl_napol.alternativy & BIT_ALT_DOPLNK_PSALM_127_131) == BIT_ALT_DOPLNK_PSALM_127_131)) \
||  \
	((modlitba == MODL_POPOLUDNI) && ((_global_modl_popol.alternativy & BIT_ALT_DOPLNK_PSALM_127_131) == BIT_ALT_DOPLNK_PSALM_127_131)) \
)
// staèilo by len: modlitba popoludní
#define je_alternativa_doplnkova_psalmodia_z126_129(modlitba) (\
	((modlitba == MODL_PREDPOLUDNIM) && ((_global_modl_predpol.alternativy & BIT_ALT_DOPLNK_PSALM_126_129) == BIT_ALT_DOPLNK_PSALM_126_129)) \
||  \
	((modlitba == MODL_NAPOLUDNIE) && ((_global_modl_napol.alternativy & BIT_ALT_DOPLNK_PSALM_126_129) == BIT_ALT_DOPLNK_PSALM_126_129)) \
||  \
	((modlitba == MODL_POPOLUDNI) && ((_global_modl_popol.alternativy & BIT_ALT_DOPLNK_PSALM_126_129) == BIT_ALT_DOPLNK_PSALM_126_129)) \
)

// 2011-02-02: presunuté do #define -- kontrola, ktorá zabezpeèuje, že normálne správanie sa slávení nie je prebité pre "CZOP miestne slávenia"
// 2011-03-07: MIESTNE_SLAVENIE_CZOP_SVATY(i) aj pre slovenské, ktoré majú nastavené "lokálne" verzie
#define MIESTNE_SLAVENIE_LOKAL_SVATY(i) (((_global_svaty(i).kalendar == KALENDAR_CZ_OFMCAP) || (_global_svaty(i).kalendar == KALENDAR_CZ_OPRAEM) || (_global_svaty(i).kalendar == KALENDAR_SK_OP) || (_global_svaty(i).kalendar == KALENDAR_CZ_OP) || (_global_svaty(i).kalendar == KALENDAR_SK_CSSR) || (_global_svaty(i).kalendar == KALENDAR_SK_SVD) || (_global_svaty(i).kalendar == KALENDAR_SK_SJ) || (_global_svaty(i).kalendar == KALENDAR_SK_SDB) || (_global_svaty(i).kalendar == KALENDAR_SK_OFM) || (_global_svaty(i).typslav_lokal != LOKAL_SLAV_NEURCENE)) && ((_global_svaty(i).smer == 4) || (_global_svaty(i).smer == 8) || (_global_svaty(i).smer == 11)))

// 2011-03-18: presunuté samostatne na jedno jediné miesto
#define PODMIENKA_EXPORTOVAT_KALENDAR ( \
((_global_jazyk == JAZYK_SK) && !((_global_kalendar == KALENDAR_NEURCENY) || (_global_kalendar == KALENDAR_VSEOBECNY) || (_global_kalendar == KALENDAR_VSEOBECNY_SK) )) \
|| ((_global_jazyk == JAZYK_CZ) && !((_global_kalendar == KALENDAR_NEURCENY) || (_global_kalendar == KALENDAR_VSEOBECNY) || (_global_kalendar == KALENDAR_VSEOBECNY_CZ) )) \
|| ((_global_jazyk == JAZYK_CZ_OP) && !((_global_kalendar == KALENDAR_NEURCENY) || (_global_kalendar == KALENDAR_VSEOBECNY) || (_global_kalendar == KALENDAR_VSEOBECNY_CZ) || (_global_kalendar == KALENDAR_CZ_OP) )) \
)

#define PODMIENKA_EXPORTOVAT_FONTSIZE ( (_global_font_size != FONT_SIZE_UNDEF) && (_global_font_size != FONT_SIZE_CSS) )

#define PODMIENKA_EXPORTOVAT_FONT ( (_global_font != FONT_UNDEF) && (_global_font != FONT_CSS) && (_global_font != FONT_CHECKBOX) )

#define PODMIENKA_EXPORTOVAT_CSS ( (_global_css != CSS_UNDEF) && (_global_css != CSS_breviar_sk) )

//---------------------------------------------------------------------
// definicie pre _rozbor_dna():
//
// obsahuju sviatky, ktore su bud pevne alebo pohyblive, v kazdom pripade su to dolezite "hranicne" dni medzi obdobiami
//
// 2011-05-03: predsunuté pred interpretParameter(), lebo sa tu používajú
// 2012-04-02: presunuté do breviar.h, lebo sa používa aj v includeFile(), tam používame VELKONOCNA_NEDELA

// 2006-08-01: pozor, koncovky sú pre každý jazyk odlišné
#define koncovka_dna_asci(denvt) ((nazov_dna((denvt))[strlen(nazov_dna((denvt))) - 1] == 'a')? 'a': 'y')
#define koncovka_dna(denvt) ((nazov_dna((denvt))[strlen(nazov_dna((denvt))) - 1] == 'a')? 'á': 'ý')
#define KRST _global_r._KRST_KRISTA_PANA.denvr                          // nede¾a po 6. januári; v krajinách, kde sa Zjavenie Pána slávi v nede¾u, a ak táto pripadne na 7. alebo 8. januára, Krst Krista Pána sa slávi nasledujúci pondelok
#define POPOLCOVA_STREDA  _global_r._POPOLCOVA_STREDA.denvr             // popolcová streda
#define VELKONOCNA_NEDELA   _global_r._VELKONOCNA_NEDELA.denvr          // ve¾konoèná nede¾a
#define KVETNA_NEDELA (VELKONOCNA_NEDELA - 7)                           // kvetná nede¾a
#define ZELENY_STVRTOK   (VELKONOCNA_NEDELA - 3)                        // zelený štvrtok
#define VELKY_PIATOK   (VELKONOCNA_NEDELA - 2)                          // ve¾ký piatok
#define BIELA_SOBOTA   (VELKONOCNA_NEDELA - 1)                          // biela sobota
#define VELKONOCNY_PONDELOK (VELKONOCNA_NEDELA + 1)                     // ve¾konoèný pondelok
#define DRUHA_VELKONOCNA_NEDELA  (VELKONOCNA_NEDELA + 7)                // nede¾a vo ve¾konoènej oktáve
#define NANEBOVSTUPENIE  _global_r._NANEBOVSTUPENIE_PANA.denvr          // nanebovstúpenie Pána (štvrtok, 40. deò po ve¾kej noci, alebo v krajinách, kde sa presúva na nasledujúcu nede¾u ("7. ve¾konoèná nede¾a")
#define PRVA_ADVENTNA_NEDELA  _global_r._PRVA_ADVENTNA_NEDELA.denvr     // prvá adventná nede¾a
#define ZOSLANIE_DUCHA_SV  _global_r._ZOSLANIE_DUCHA_SV.denvr           // zoslanie Ducha Svätého
#define SV_RODINY  _global_r._SVATEJ_RODINY.denvr                       // sviatok svätej rodiny
#define TROJICA (ZOSLANIE_DUCHA_SV + 7)                                 // prvá nede¾a po ZOSLANIE_DUCHA_SV: najsv. Trojice
// #define TELAKRVI (ZOSLANIE_DUCHA_SV + 11)                               // štvrtok po Trojici: Kristovho tela a krvi (alebo: v krajinách, kde sa presúva na nede¾u)
#define SRDCA (ZOSLANIE_DUCHA_SV + 19)                                  // piatok po druhej nedeli po ZOSLANIE_DUCHA_SV: najsv. srdca Ježišovho
#define SRDPM (ZOSLANIE_DUCHA_SV + 20)                                  // sobota po druhej nedeli po ZOSLANIE_DUCHA_SV: nepoškvrneného srdca prebl. p. márie
// 2006-08-22: kvôli ružovej farbe rúcha potrebujeme define aj pre 3. adventnú nede¾u a 4. pôstnu nede¾u
#define TRETIA_ADVENTNA_NEDELA (PRVA_ADVENTNA_NEDELA + 14)              // tretia adventná nede¾a - dva týždne po prvej adventnej nedeli (PRVA_ADVENTNA_NEDELA)
#define STVRTA_POSTNA_NEDELA (VELKONOCNA_NEDELA - 21)                   // štvrtá pôstna nede¾a - tri týždne pred VELKONOCNA_NEDELA

#ifndef OS_linux
// kedysi bolo void main; 2003-07-14, kvoli gcc version 3.2.2 20030222 (Red Hat Linux 3.2.2-5) christ-net.sk 
int main(int argc, char **argv);
#endif // OS_linux

int breviar_main(int argc, char **argv);

#if (_MSC_VER >= 1400)       // VC8+ 2007-02-12 kvôli vc++ 2005 express edition
	#pragma warning(disable : 4996)    // disable all deprecation warnings
	#define putenv _putenv
#endif   // VC8+

#endif // __BREVIAR_H_


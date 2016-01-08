/***************************************************************/
/*                                                             */
/* breviar.h                                                   */
/* (c)1999-2016 | Juraj Vidéky | videky@breviar.sk             */
/*                                                             */
/* description | contains declarations of global variables     */
/*                                                             */
/***************************************************************/

#include "vstudio.h"

#ifndef __BREVIAR_H_
#define __BREVIAR_H_

#include "liturgia.h"
#include "mysystem.h"
#include "mysysdef.h"

// week of psaltery
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

#define EXPORT_DNA_XML 6 // XML export for the day -- originally for iOS app
#define EXPORT_DNA_JEDEN_DEN_LOCAL 5
#define EXPORT_DNA_VIAC_DNI_TXT 4
#define EXPORT_DNA_VIAC_DNI_SIMPLE 3
#define EXPORT_DNA_JEDEN_DEN 1
#define EXPORT_DNA_VIAC_DNI 2
#define EXPORT_DNA_DNES 0

#define EXPORT_TYP_WEB_MODE 0
#define EXPORT_TYP_BATCH_MODE 1

extern void _export_rozbor_dna_buttons(short int typ, short int poradie_svateho, short int den_zoznam = ANO, short int zobrazit_mcd = ANO);
extern void _export_rozbor_dna_buttons_dni_dnes(short int dnes_dnes, short int som_v_tabulke, char pom2[MAX_STR], short int zobraz_odkaz_na_skrytie);
extern void _export_rozbor_dna_buttons_dni(short int typ, short int dnes_dnes = ANO, short int aj_navigacia = ANO);
extern void _export_rozbor_dna_buttons_dni_orig(short int typ, short int dnes_dnes = ANO);
extern void _export_rozbor_dna_buttons_dni_compact(short int typ, short int dnes_dnes = ANO);
extern void _export_rozbor_dna_buttons_dni_call(short int typ, short int dnes_dnes = ANO);
extern void _export_rozbor_dna_kalendar_core(short int typ);
extern void _export_rozbor_dna_kalendar(short int typ);

extern short int _global_pocet_navigacia; // 2011-07-03: počet prejdených/spracovaných parametrov PARAM_NAVIGACIA | counter of processed PARAM_NAVIGACIA params

extern short int index_pre_mesiac_otvoreny;

extern char optional_html_class_button[MAX_STR];
extern char optional_html_button_begin[MAX_STR];
extern char optional_html_button_end[MAX_STR];

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

// globálna premenná -- pole -- obsahujúca options; pôvodne to boli globálne premenné _global_opt 1..9 atď., obsahujú pom_MODL_OPT...
extern int _global_opt[POCET_GLOBAL_OPT];
// globálna premenná -- pole -- obsahujúca force options; pôvodne to boli globálne premenné _global_optf 1..9 atď., obsahujú pom_MODL_OPTF...
extern int _global_optf[POCET_GLOBAL_OPT];

// globalna premenna, co obsahuje string vypisany na obsazovku
extern char *_global_string;
extern char *_global_string2; // obsahuje I, II, III, IV, V alebo pismeno roka
extern char *_global_string_farba;
// 2011-10-04: pridané, pre titulok modlitby (už sa nepriliepa do _global_string)
// extern char _global_string_modlitba[SMALL];

extern char *_global_buf; // 2006-08-01: túto premennú tiež alokujeme
extern char *_global_buf2; // 2006-08-01: túto premennú tiež alokujeme
//---------------------------------------------------------------------

extern short int _global_jazyk;
extern short int _global_kalendar; // kalendáre (napr. rehoľné), súvisí s jazykovými mutáciami
extern short int _global_ritus;

extern short int _global_css;

extern short int _global_font;
extern short int _global_font_size;
extern short int _global_style_margin; // for usage in <body> for style margin-left & margin-right

extern short int _global_pocet_zalmov_kompletorium; // kompletórium niekedy obsahuje až dva žalmy

extern char _special_anchor_prefix[SMALL]; // used for CZ hymns
extern char _special_anchor_postfix[SMALL]; // used for CZ hymns in Per Annum

extern short int _global_opt_batch_monthly;

extern short int _global_hlavicka_Export;
// extern char name_batch_html_file[MAX_STR];
extern short int _global_patka_Export;

extern char _global_css_font_family[SMALL];
extern char _global_css_font_size[SMALL];

extern char _global_export_navig_hore[SMALL];
extern short int _global_opt_export_date_format;

#define set_tyzzal_1_2(tyzzal) ((tyzzal > 2)? (tyzzal - 2) : tyzzal)

// placeholder for checking whether option 'i' has set 'j'-th bit-component to TRUE
#define isGlobalOption(opt_i, bit_opt_i_component_j) ((_global_opt[opt_i] & bit_opt_i_component_j) == bit_opt_i_component_j)
#define isGlobalOptionForce(opt_i, bit_opt_i_component_j) ((_global_optf[opt_i] & bit_opt_i_component_j) == bit_opt_i_component_j)

// define for decide whether offline (Android) app supports hyperlinks to Bible app for liturgical readings -- currently in SK only
#define su_liturgicke_citania_offline (_global_jazyk == JAZYK_SK)

#define je_modlitba_cez_den(modlitba) ((modlitba == MODL_PREDPOLUDNIM) || (modlitba == MODL_NAPOLUDNIE) || (modlitba == MODL_POPOLUDNI))
#define je_kompletorium12(modlitba) ((modlitba == MODL_KOMPLETORIUM) || (modlitba == MODL_PRVE_KOMPLETORIUM) || (modlitba == MODL_DRUHE_KOMPLETORIUM))

#define je_modlitba_ok_buttons(modlitba) ((modlitba >= MODL_INVITATORIUM) && (modlitba < MODL_NEURCENA))

#define je_vianocne(litobd) ((litobd == OBD_VIANOCNE_I) || (litobd == OBD_VIANOCNE_II))

#define je_post ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN) || ((_global_den.litobd == OBD_VELKONOCNE_TROJDNIE) && ((_global_den.denvt == DEN_PIATOK) || (_global_den.denvt == DEN_SOBOTA))))
#define je_velka_noc ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II) || ((_global_den.litobd == OBD_VELKONOCNE_TROJDNIE) && (_global_den.denvt == DEN_NEDELA)) || (_global_den.litobd == OBD_VELKONOCNA_OKTAVA))
#define je_aleluja_aleluja ((_global_den.litobd == OBD_VELKONOCNA_OKTAVA) || ((_global_den.litobd == OBD_VELKONOCNE_TROJDNIE) && (_global_den.denvt == DEN_NEDELA)) || ((_global_den.denvr == _global_r._ZOSLANIE_DUCHA_SV.denvr) && ((_global_modlitba == MODL_VESPERY) || (_global_modlitba == MODL_DRUHE_VESPERY))))
#define je_34_ocr ((_global_den.litobd == OBD_CEZ_ROK) && (_global_den.tyzden == 34) && (_global_den.denvt != DEN_NEDELA))
#define je_tedeum (type == MODL_POSV_CITANIE) && (((_global_den.denvt == DEN_NEDELA) && (_global_den.litobd != OBD_POSTNE_I) && (_global_den.litobd != OBD_POSTNE_II_VELKY_TYZDEN)) || (_global_den.typslav == SLAV_SLAVNOST) || (_global_den.typslav == SLAV_SVIATOK) || (_global_den.litobd == OBD_VELKONOCNA_OKTAVA) || (_global_den.litobd == OBD_OKTAVA_NARODENIA))

// 2012-02-09: definované je_privileg pre testovanie, či ide o privilegované dni (VSLH č. 238-239): to isté ako je_post + december počnúc 17.-tym (všedné di od 17. do 24. decembra a Vianočná oktáva); striktne by tu nemal byť veľký týždeň a veľkonočné trojdnie, ale nezaškodí to tu
#define je_privileg ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN) || ((_global_den.litobd == OBD_VELKONOCNE_TROJDNIE) && ((_global_den.denvt == DEN_PIATOK) || (_global_den.denvt == DEN_SOBOTA))) || ((_global_den.mesiac - 1 == MES_DEC) && (_global_den.den >= 17)))

// is antiphone for privileged day?
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

// predĺžené slávenie vigílií v rámci posvätných čítaní | is vigily (for office with readings)?
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

// is description for prayer?
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

// či sa NEMAJÚ zobrazovať vešpery; doteraz sa kontrolovalo len to, či je sobota -- opravené pre Veľkú (bielu) sobotu | are NOT vespers (= should I hide button for evening prayer)?
#define nie_su_vespery ( \
	(_global_den.denvt == DEN_SOBOTA) && (!((_global_den.denvt == DEN_SOBOTA) && (_global_den.litobd == OBD_VELKONOCNE_TROJDNIE))) \
)

// are there alternate hymns? (for SK based on LA LH)
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
(_global_modlitba == MODL_PRVE_VESPERY && ((_global_modl_prve_vespery.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
||  \
(_global_modlitba == MODL_VESPERY && ((_global_modl_vespery.alternativy & BIT_ALT_HYMNUS_VN) == BIT_ALT_HYMNUS_VN)) \
)

// are there alternate hymns for Ordinary time (per annum)? (for SK based on LA LH)
#define je_alternativa_hymnus_ocr ( \
(_global_modlitba == MODL_PRVE_VESPERY && ((_global_modl_prve_vespery.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
||  \
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

// are there alternate hymns for Easter? (for SK based on LA LH)
#define je_alternativa_hymnus_vn ( \
(_global_modlitba == MODL_RANNE_CHVALY && ((_global_modl_ranne_chvaly.alternativy & BIT_ALT_HYMNUS_VN) == BIT_ALT_HYMNUS_VN)) \
||  \
(_global_modlitba == MODL_POSV_CITANIE && ((_global_modl_posv_citanie.alternativy & BIT_ALT_HYMNUS_VN) == BIT_ALT_HYMNUS_VN)) \
||  \
(_global_modlitba == MODL_VESPERY && ((_global_modl_vespery.alternativy & BIT_ALT_HYMNUS_VN) == BIT_ALT_HYMNUS_VN)) \
)

// for JAZYK_CZ, is chosen alternative for hymns of supplement?
#define je_CZ_hymny_k_volnemu_vyberu ((_global_jazyk == JAZYK_CZ) && (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_CZ_HYMNY_VYBER)))

// ToDo: before replacing anchor from file with HTML scratch, try to remove _special_anchor_prefix/postfix!!!
#define specialne_dni_bez_hymnov_k_volnemu_vyberu_CZ ((_global_den.denvr == VELKONOCNA_NEDELA) || (_global_den.denvr == SV_RODINY))

// is supplementary psalmody?
#define je_len_doplnkova_psalmodia(modlitba) (\
	((modlitba == MODL_PREDPOLUDNIM) && ((_global_modl_predpol.alternativy & BIT_ALT_LEN_DOPLNKOVA_PSALMODIA) == BIT_ALT_LEN_DOPLNKOVA_PSALMODIA)) \
||  \
	((modlitba == MODL_NAPOLUDNIE) && ((_global_modl_napol.alternativy & BIT_ALT_LEN_DOPLNKOVA_PSALMODIA) == BIT_ALT_LEN_DOPLNKOVA_PSALMODIA)) \
||  \
	((modlitba == MODL_POPOLUDNI) && ((_global_modl_popol.alternativy & BIT_ALT_LEN_DOPLNKOVA_PSALMODIA) == BIT_ALT_LEN_DOPLNKOVA_PSALMODIA)) \
)

// is psalm 122/129 in supplementary psalmody? (it would suffice: 9h prayer)
#define je_alternativa_doplnkova_psalmodia_z122_129(modlitba) (\
	((modlitba == MODL_PREDPOLUDNIM) && ((_global_modl_predpol.alternativy & BIT_ALT_DOPLNK_PSALM_122_129) == BIT_ALT_DOPLNK_PSALM_122_129)) \
||  \
	((modlitba == MODL_NAPOLUDNIE) && ((_global_modl_napol.alternativy & BIT_ALT_DOPLNK_PSALM_122_129) == BIT_ALT_DOPLNK_PSALM_122_129)) \
||  \
	((modlitba == MODL_POPOLUDNI) && ((_global_modl_popol.alternativy & BIT_ALT_DOPLNK_PSALM_122_129) == BIT_ALT_DOPLNK_PSALM_122_129)) \
)

// is psalm 127/131 in supplementary psalmody? (it would suffice: 12h prayer)
#define je_alternativa_doplnkova_psalmodia_z127_131(modlitba) (\
	((modlitba == MODL_PREDPOLUDNIM) && ((_global_modl_predpol.alternativy & BIT_ALT_DOPLNK_PSALM_127_131) == BIT_ALT_DOPLNK_PSALM_127_131)) \
||  \
	((modlitba == MODL_NAPOLUDNIE) && ((_global_modl_napol.alternativy & BIT_ALT_DOPLNK_PSALM_127_131) == BIT_ALT_DOPLNK_PSALM_127_131)) \
||  \
	((modlitba == MODL_POPOLUDNI) && ((_global_modl_popol.alternativy & BIT_ALT_DOPLNK_PSALM_127_131) == BIT_ALT_DOPLNK_PSALM_127_131)) \
)

// is psalm 126/129 in supplementary psalmody? (it would suffice: 15h prayer)
#define je_alternativa_doplnkova_psalmodia_z126_129(modlitba) (\
	((modlitba == MODL_PREDPOLUDNIM) && ((_global_modl_predpol.alternativy & BIT_ALT_DOPLNK_PSALM_126_129) == BIT_ALT_DOPLNK_PSALM_126_129)) \
||  \
	((modlitba == MODL_NAPOLUDNIE) && ((_global_modl_napol.alternativy & BIT_ALT_DOPLNK_PSALM_126_129) == BIT_ALT_DOPLNK_PSALM_126_129)) \
||  \
	((modlitba == MODL_POPOLUDNI) && ((_global_modl_popol.alternativy & BIT_ALT_DOPLNK_PSALM_126_129) == BIT_ALT_DOPLNK_PSALM_126_129)) \
)

// 2011-02-02: presunuté do #define -- kontrola, ktorá zabezpečuje, že normálne správanie sa slávení nie je prebité pre "CZOP miestne slávenia"
// 2011-03-07: MIESTNE_SLAVENIE_CZOP_SVATY(i) aj pre slovenské, ktoré majú nastavené "lokálne" verzie
// 2014-03-21: aj pre SK všeobecné kvôli 2014-10-26 | bolo: #define MIESTNE_SLAVENIE_LOKAL_SVATY(i) (((_global_svaty(i).kalendar == KALENDAR_CZ_OFMCAP) || (_global_svaty(i).kalendar == KALENDAR_CZ_OPRAEM) || (_global_svaty(i).kalendar == KALENDAR_SK_OP) || (_global_svaty(i).kalendar == KALENDAR_CZ_OP) || (_global_svaty(i).kalendar == KALENDAR_SK_CSSR) || (_global_svaty(i).kalendar == KALENDAR_SK_SVD) || (_global_svaty(i).kalendar == KALENDAR_SK_SJ) || (_global_svaty(i).kalendar == KALENDAR_SK_SDB) || (_global_svaty(i).kalendar == KALENDAR_SK_OFM) || (_global_svaty(i).typslav_lokal != LOKAL_SLAV_NEURCENE)) && ((_global_svaty(i).smer == 4) || (_global_svaty(i).smer == 8) || (_global_svaty(i).smer == 11)))
#define MIESTNE_SLAVENIE_LOKAL_SVATY(i) ((_global_svaty(i).smer == 4) || (_global_svaty(i).smer == 8) || (_global_svaty(i).smer == 11))

// 2014-04-08: presunuté do #define -- bolo na 2 rôznych miestach | sviatky Pána a svätých, ktoré majú prednosť pred Cezročnou nedeľou a majú (ak padnú na nedeľu) svoje vlastné prvé vešpery
// ------------- pôvodné poznámky ------------- 
// 2011-06-30: cyril a metod odvetvený pre SK a CZ only
// 2011-07-22: doplnené pre HU: 20AUG
// 2011-10-13: zapoznámkované 14SEP kvôli CZ // nespúšťalo sa totiž zaltar_zvazok(), a teda ani zaltar_kompletorium()
// 2012-10-22: odpoznámkované 14SEP -- napr. pre rok 2014 potom nedávalo prvé vešpery, ak padne na nedeľu!
// 2014-01-10: doplnené 02FEB (ak padne na nedeľu, má prvé vešpery)
// 2014-04-08: 14SEP platí aj pre CZ (ak padne na nedeľu, má prvé vešpery)
#define PODMIENKA_SVIATKY_PANA_SVATYCH_PREDNOST (\
((_global_den.den == 2) && (_global_den.mesiac - 1 == MES_FEB)) || \
((_global_den.den == 29) && (_global_den.mesiac - 1 == MES_JUN)) || \
((_global_den.den == 5) && (_global_den.mesiac - 1 == MES_JUL) && ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP))) || \
((_global_den.den == 6) && (_global_den.mesiac - 1 == MES_AUG)) || \
((_global_den.den == 15) && (_global_den.mesiac - 1 == MES_AUG)) || \
((_global_den.den == 20) && (_global_den.mesiac - 1 == MES_AUG) && (_global_jazyk == JAZYK_HU)) || \
((_global_den.den == 14) && (_global_den.mesiac - 1 == MES_SEP)) || \
((_global_den.den == 28) && (_global_den.mesiac - 1 == MES_SEP) && ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP))) || \
((_global_den.den == 1) && (_global_den.mesiac - 1 == MES_NOV)) \
)

// should calendar be exported?
#define PODMIENKA_EXPORTOVAT_KALENDAR (!((_global_kalendar == KALENDAR_NEURCENY) || (_global_kalendar == KALENDAR_VSEOBECNY) || (_global_kalendar == default_kalendar[_global_jazyk])))

#define PODMIENKA_EXPORTOVAT_FONTSIZE ( (_global_font_size != FONT_SIZE_UNDEF) && (_global_font_size != FONT_SIZE_CSS) )

#define PODMIENKA_EXPORTOVAT_FONT ( (_global_font != FONT_UNDEF) && (_global_font != FONT_CSS) && (_global_font != FONT_CHECKBOX) )

#define PODMIENKA_EXPORTOVAT_CSS ( (_global_css != CSS_UNDEF) && (_global_css != CSS_breviar_sk) )

#define PODMIENKA_EXPORTOVAT_STYLE_MARGIN ( (_global_style_margin > MIN_STYLE_MARGIN) && (_global_style_margin < MAX_STYLE_MARGIN) )

//---------------------------------------------------------------------
// definicie pre _rozbor_dna():
//
// obsahuju sviatky, ktore su bud pevne alebo pohyblive, v kazdom pripade su to dolezite "hranicne" dni medzi obdobiami
//
// 2011-05-03: predsunuté pred interpretParameter(), lebo sa tu používajú
// 2012-04-02: presunuté do breviar.h, lebo sa používa aj v includeFile(), tam používame VELKONOCNA_NEDELA

// 2006-08-01: pozor, koncovky sú pre každý jazyk odlišné
#define koncovka_dna_asci(denvt) ((nazov_dna((denvt))[strlen(nazov_dna((denvt))) - 1] == 'a')? 'a': 'y')
#define koncovka_dna(denvt) ((nazov_dna((denvt))[strlen(nazov_dna((denvt))) - 1] == 'a')? "á": "ý")
#define KRST _global_r._KRST_KRISTA_PANA.denvr                          // nedeľa po 6. januári; v krajinách, kde sa Zjavenie Pána slávi v nedeľu, a ak táto pripadne na 7. alebo 8. januára, Krst Krista Pána sa slávi nasledujúci pondelok
#define POPOLCOVA_STREDA  _global_r._POPOLCOVA_STREDA.denvr             // popolcová streda
#define VELKONOCNA_NEDELA   _global_r._VELKONOCNA_NEDELA.denvr          // veľkonočná nedeľa
#define KVETNA_NEDELA (VELKONOCNA_NEDELA - 7)                           // kvetná nedeľa
#define ZELENY_STVRTOK   (VELKONOCNA_NEDELA - 3)                        // zelený štvrtok
#define VELKY_PIATOK   (VELKONOCNA_NEDELA - 2)                          // veľký piatok
#define BIELA_SOBOTA   (VELKONOCNA_NEDELA - 1)                          // biela sobota
#define VELKONOCNY_PONDELOK (VELKONOCNA_NEDELA + 1)                     // veľkonočný pondelok
#define DRUHA_VELKONOCNA_NEDELA  (VELKONOCNA_NEDELA + 7)                // nedeľa vo veľkonočnej oktáve
#define NANEBOVSTUPENIE  _global_r._NANEBOVSTUPENIE_PANA.denvr          // nanebovstúpenie Pána (štvrtok, 40. deň po veľkej noci, alebo v krajinách, kde sa presúva na nasledujúcu nedeľu ("7. veľkonočná nedeľa")
#define PRVA_ADVENTNA_NEDELA  _global_r._PRVA_ADVENTNA_NEDELA.denvr     // prvá adventná nedeľa
#define ZOSLANIE_DUCHA_SV  _global_r._ZOSLANIE_DUCHA_SV.denvr           // zoslanie Ducha Svätého
#define SV_RODINY  _global_r._SVATEJ_RODINY.denvr                       // sviatok svätej rodiny
#define KRISTA_KNAZA (ZOSLANIE_DUCHA_SV + 4)                            // štvrtok po Zoslaní Ducha Svätého (ZOSLANIE_DUCHA_SV): sviatok Nášho Pána Ježiša Krista, najvyššieho a večného kňaza (http://www.tkkbs.sk/view.php?cisloclanku=20140115028)
#define TROJICA (ZOSLANIE_DUCHA_SV + 7)                                 // prvá nedeľa po ZOSLANIE_DUCHA_SV: najsv. Trojice
// #define TELAKRVI (ZOSLANIE_DUCHA_SV + 11)                               // štvrtok po Trojici: Kristovho tela a krvi (alebo: v krajinách, kde sa presúva na nedeľu)
#define SRDCA (ZOSLANIE_DUCHA_SV + 19)                                  // piatok po druhej nedeli po ZOSLANIE_DUCHA_SV: najsv. srdca Ježišovho
#define SRDPM (ZOSLANIE_DUCHA_SV + 20)                                  // sobota po druhej nedeli po ZOSLANIE_DUCHA_SV: nepoškvrneného srdca prebl. p. márie
// 2006-08-22: kvôli ružovej farbe rúcha potrebujeme define aj pre 3. adventnú nedeľu a 4. pôstnu nedeľu
#define TRETIA_ADVENTNA_NEDELA (PRVA_ADVENTNA_NEDELA + 14)              // tretia adventná nedeľa - dva týždne po prvej adventnej nedeli (PRVA_ADVENTNA_NEDELA)
#define STVRTA_POSTNA_NEDELA (VELKONOCNA_NEDELA - 21)                   // štvrtá pôstna nedeľa - tri týždne pred VELKONOCNA_NEDELA

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


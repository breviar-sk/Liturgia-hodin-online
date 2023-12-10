/***************************************************************/
/*                                                             */
/* breviar.h                                                   */
/* (c)1999-2023 | Juraj Vidéky | videky@breviar.sk             */
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

extern short int isAndroid;

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

#define EXPORT_DNES_DNES_NULL -1
#define EXPORT_DNES_DNES_NIE 0
#define EXPORT_DNES_DNES_ANO 1
#define EXPORT_DNES_DNES_ANO_SPEC 2

extern void _export_rozbor_dna_buttons(short int typ, short int poradie_svateho, short int den_zoznam = ANO, short int zobrazit_mcd = ANO);
extern void _export_rozbor_dna_buttons_dni_dnes(short int dnes_dnes, short int som_v_tabulke, char pom2[MAX_STR], short int zobraz_odkaz_na_skrytie);
extern void _export_rozbor_dna_buttons_dni(short int typ, short int dnes_dnes = EXPORT_DNES_DNES_ANO, short int aj_navigacia = ANO);
extern void _export_rozbor_dna_buttons_dni_orig(short int typ, short int dnes_dnes = EXPORT_DNES_DNES_ANO);
extern void _export_rozbor_dna_buttons_dni_compact(short int typ, short int dnes_dnes = EXPORT_DNES_DNES_ANO);
extern void _export_rozbor_dna_buttons_dni_call(short int typ, short int dnes_dnes = EXPORT_DNES_DNES_ANO);
extern void _export_rozbor_dna_kalendar_core(short int typ);
extern void _export_rozbor_dna_kalendar(short int typ);

extern short int _global_pocet_navigacia; // 2011-07-03: počet prejdených/spracovaných parametrov PARAM_NAVIGACIA | counter of processed PARAM_NAVIGACIA params

extern short int index_pre_mesiac_otvoreny;

extern char optional_html_class_button[MAX_STR];
extern char optional_html_button_begin[MAX_STR];
extern char optional_html_button_prayer_begin[MAX_STR];
extern char optional_html_button_end[MAX_STR];

// globalna premenna, do ktorej sa ukladaju info o analyzovanom dni
extern _struct_dm* _global_den_ptr;
#define _global_den (*_global_den_ptr)

// globalne premenne, do ktorych sa ukladaju info o analyzovanom dni o sviatkoch svatych
extern _struct_dm* _global_svaty_ptr[MAX_POCET_SVATY]; // an array of '_struct_dm' pointers
#define _global_svaty(i) (*(_global_svaty_ptr[i - 1]))

// globalna premenna, ktora obsahuje data o spomienke panny marie v sobotu
extern _struct_dm* _global_pm_sobota_ptr;
#define _global_pm_sobota (*_global_pm_sobota_ptr)

// globalne premenne obsahujuce data modlitbach

extern _type_1vespery* _global_modl_prve_vespery_ptr;
#define _global_modl_prve_vespery (*_global_modl_prve_vespery_ptr)

extern _type_1kompletorium* _global_modl_1kompletorium_ptr;
#define _global_modl_prve_kompletorium (*_global_modl_1kompletorium_ptr)

extern _type_invitatorium* _global_modl_invitatorium_ptr;
#define _global_modl_invitatorium (*_global_modl_invitatorium_ptr)

extern _type_posv_citanie* _global_modl_posv_citanie_ptr;
#define _global_modl_posv_citanie (*_global_modl_posv_citanie_ptr)

extern _type_ranne_chvaly* _global_modl_ranne_chvaly_ptr;
#define _global_modl_ranne_chvaly (*_global_modl_ranne_chvaly_ptr)

extern _type_cez_den_9* _global_modl_cez_den_9_ptr;
#define _global_modl_cez_den_9 (*_global_modl_cez_den_9_ptr)
extern _type_cez_den_12* _global_modl_cez_den_12_ptr;
#define _global_modl_cez_den_12 (*_global_modl_cez_den_12_ptr)
extern _type_cez_den_3* _global_modl_cez_den_3_ptr;
#define _global_modl_cez_den_3 (*_global_modl_cez_den_3_ptr)

extern _type_vespery* _global_modl_vespery_ptr;
#define _global_modl_vespery (*_global_modl_vespery_ptr)

extern _type_kompletorium* _global_modl_kompletorium_ptr;
#define _global_modl_kompletorium (*_global_modl_kompletorium_ptr)

extern _struct_anchor_and_file* _global_include_static_text_ptr;
#define _global_include_static_text (*_global_include_static_text_ptr)

// globalna premenna, ktora obsahuje MODL_...
extern short int _global_modlitba;

// globalna premenna, do ktorej ukladaju funkcie vytvor_query_string_... linku tvaru SCRIPT_PATH(SCRIPT_NAME) ++ "?param1=val&param2=val&..."
extern char* _global_link_ptr;
#define _global_link _global_link_ptr

extern char* _global_pom_str; // pomocny string pre velke pismena

// globalna premenna, do ktorej sa ukladaju info o jednotlivych vyznacnych liturgickych dni, pouzivaju void _dm_...() funkcie a void analyzuj_rok() funkcia
extern _struct_dm* _global_result_ptr;
#define _global_result (*_global_result_ptr)

// globalna premenna, do ktorej sa uklada info o liturgickom roku pouziva void analyzuj_rok() funkcia
extern _struct_lrok* _global_r_ptr;
#define _global_r (*_global_r_ptr)

// globalna premenna, do ktorej sviatky_svatych() uklada pocet sviatkov (de facto lubovolnych spomienok), ktore pripadaju na dany den
// -- v podstate neuklada do nej, ale v _rozbor_dna() sa do nej priradi vysledok (navratova hodnota) z sviatky_svatych()
extern short int _global_pocet_svatych;

// globálna premenná -- pole -- obsahujúca options; pôvodne to boli globálne premenné _global_opt 1..9 atď., obsahujú pom_OPT...
extern unsigned long long _global_opt[POCET_GLOBAL_OPT];
// globálna premenná -- pole -- obsahujúca force options; pôvodne to boli globálne premenné _global_force_opt 1..9 atď., obsahujú pom_FORCE_OPT...
extern unsigned long long _global_force_opt[POCET_GLOBAL_OPT];

// globalna premenna, co obsahuje string vypisany na obsazovku
extern char* _global_string;
extern char* _global_string2; // obsahuje I, II, III, IV, V alebo pismeno roka
extern char* _global_string_farba;
// 2011-10-04: pridané, pre titulok modlitby (už sa nepriliepa do _global_string)
// extern char _global_string_modlitba[SMALL];

extern char* _global_buf; // 2006-08-01: túto premennú tiež alokujeme
extern char* _global_buf2; // 2006-08-01: túto premennú tiež alokujeme
//---------------------------------------------------------------------

extern short int _global_jazyk;
extern short int _global_kalendar; // kalendáre (napr. rehoľné), súvisí s jazykovými mutáciami
extern short int _global_ritus;

extern short int _global_css;

extern short int _global_font;
extern short int _global_font_size;
extern short int _global_font_size_pt;
extern short int _global_style_margin; // for usage in <body> for style margin-left & margin-right
extern short int _global_line_height_perc;

extern short int _global_pocet_zalmov_kompletorium; // kompletórium niekedy obsahuje až dva žalmy

extern char _special_anchor_prefix[SMALL]; // used for CZ hymns
extern char _special_anchor_postfix[SMALL]; // used for CZ hymns in Per Annum
extern char _special_anchor_prefix2[SMALL]; // used for CZ 2nd readings

extern short int _global_opt_batch_monthly;

extern short int _global_hlavicka_Export;
// extern char name_batch_html_file[MAX_STR];
extern short int _global_patka_Export;

extern char _global_css_font_family[SMALL];
extern char _global_css_font_size[SMALL];
extern short int _global_override_thin_nbsp;

extern char _global_export_navig_hore[SMALL];
extern short int _global_opt_export_date_format;

#define set_tyzzal_1_2(tyzzal) ((tyzzal > 2)? (tyzzal - 2) : tyzzal)

// placeholder for checking whether option 'i' has set 'j'-th bit-component to TRUE | used result ANO/NIE to prevent long datatype; OPT 6 uses decimal-place logic
#define isGlobalOption(opt_i, bit_opt_i_component_j) ((opt_i == OPT_6_ALTERNATIVES_MULTI) ? ((_global_opt[opt_i] DIV bit_opt_i_component_j) MOD 10) : (((_global_opt[opt_i] & bit_opt_i_component_j) == bit_opt_i_component_j) ? ANO : NIE))
#define isGlobalOptionForce(opt_i, bit_opt_i_component_j) ((opt_i == OPT_6_ALTERNATIVES_MULTI) ? ((_global_force_opt[opt_i] DIV bit_opt_i_component_j) MOD 10) : (((_global_force_opt[opt_i] & bit_opt_i_component_j) == bit_opt_i_component_j) ? ANO : NIE))

// method for checking whether option 'i' should be applied (may be different from real setting - use isGlobalOption() for exact querying from parameters; difference caused e. g. by override for voice output)
extern short int useWhenGlobalOption(short opt_i, unsigned long long bit_opt_i_component_j);

// for setting option's 'i' 'j'-th bit-component to value (TRUE/FALSE); OPT 6 uses decimal-place logic
extern void setGlobalOption(short opt_i, unsigned long long bit_opt_i_component_j, short value);

#define odfiltrujSpolCast(modlitba, opt3) ((short int)(((modlitba == MODL_DETAILY) || (modlitba == MODL_NEURCENA)) ? MODL_SPOL_CAST_NULL : opt3))

// prvé písmeno veľké majú len názvy vlastných častí pre CZOP (pre SK chybne dávalo: "panny Márie")
#define lowered_nazov_spolc(a) ((_global_jazyk == JAZYK_CZ_OP)? mystr_first_lower(nazov_spolc(a)).c_str() : nazov_spolc(a))

// define for decide whether offline (Android) app supports hyperlinks to Bible app for liturgical readings -- currently in SK only
#define su_liturgicke_citania_offline (_global_jazyk == JAZYK_SK)

#define je_modlitba_cez_den(modlitba) ((modlitba == MODL_PREDPOLUDNIM) || (modlitba == MODL_NAPOLUDNIE) || (modlitba == MODL_POPOLUDNI))
#define je_kompletorium12(modlitba) ((modlitba == MODL_KOMPLETORIUM) || (modlitba == MODL_PRVE_KOMPLETORIUM) || (modlitba == MODL_DRUHE_KOMPLETORIUM))
#define su_vespery12(modlitba) ((modlitba == MODL_VESPERY) || (modlitba == MODL_PRVE_VESPERY) || (modlitba == MODL_DRUHE_VESPERY))

#define je_modlitba_ok_buttons(modlitba) ((modlitba >= MODL_INVITATORIUM) && (modlitba < MODL_NEURCENA))

#define je_vianocne(litobd) ((litobd == OBD_VIANOCNE_I) || (litobd == OBD_VIANOCNE_II))

#define je_post_I_a_II ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN))
#define je_post ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN) || ((_global_den.litobd == OBD_VELKONOCNE_TROJDNIE) && ((_global_den.denvt == DEN_PIATOK) || (_global_den.denvt == DEN_SOBOTA))))
#define je_velka_noc ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II) || ((_global_den.litobd == OBD_VELKONOCNE_TROJDNIE) && (_global_den.denvt == DEN_NEDELA)) || (_global_den.litobd == OBD_VELKONOCNA_OKTAVA))
#define je_aleluja_aleluja ((_global_den.litobd == OBD_VELKONOCNA_OKTAVA) || ((_global_den.litobd == OBD_VELKONOCNE_TROJDNIE) && (_global_den.denvt == DEN_NEDELA)) || ((_global_den.denvr == _global_r._ZOSLANIE_DUCHA_SV.denvr) && ((_global_modlitba == MODL_VESPERY) || (_global_modlitba == MODL_DRUHE_VESPERY))))
#define je_34_ocr ((_global_den.litobd == OBD_CEZ_ROK) && (_global_den.tyzden == 34) && (_global_den.denvt != DEN_NEDELA))
#define je_tedeum ((modlitba == MODL_POSV_CITANIE) && (((_global_den.denvt == DEN_NEDELA) && (_global_den.litobd != OBD_POSTNE_I) && (_global_den.litobd != OBD_POSTNE_II_VELKY_TYZDEN)) || _je_global_den_slavnost || _je_global_den_sviatok || (_global_den.litobd == OBD_VELKONOCNA_OKTAVA) || (_global_den.litobd == OBD_OKTAVA_NARODENIA) || ((_decode_spol_cast(_global_den.spolcast).a1 == MODL_SPOL_CAST_POSVIACKA_CHRAMU) && (_je_global_den_slavnost || _je_global_den_sviatok))))

// je_privileg -- pre zistenie, či ide o privilegované dni (VSLH č. 238-239): to isté ako je_post + december počnúc 17.-tym (všedné di od 17. do 24. decembra a Vianočná oktáva); striktne by tu nemal byť Svätý týždeň a veľkonočné trojdnie, ale nezaškodí to tu
// override stupňa slávenia prebíja je_privileg (inými slovami, v privilegované dni je možné sláviť sviatky resp. slávnosti)
#define je_privileg ((!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OVERRIDE_STUP_SLAV)) && ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN) || ((_global_den.litobd == OBD_VELKONOCNE_TROJDNIE) && ((_global_den.denvt == DEN_PIATOK) || (_global_den.denvt == DEN_SOBOTA))) || ((_global_den.mesiac - 1 == MES_DEC) && (_global_den.den >= 17))))

// is antiphone & prayer for privileged day?
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

// is prayer for privileged day? (antiphone may be undefined)
#define je_modl_spomprivileg (( \
(_global_modlitba == MODL_RANNE_CHVALY &&  \
	(_global_modl_ranne_chvaly.modlitba_spomprivileg.anchor != NULL) && (_global_modl_ranne_chvaly.modlitba_spomprivileg.file != NULL) && \
	(!equals(_global_modl_ranne_chvaly.modlitba_spomprivileg.anchor, STR_EMPTY)) && (!equals(_global_modl_ranne_chvaly.modlitba_spomprivileg.anchor, STR_UNDEF)) && \
	(!equals(_global_modl_ranne_chvaly.modlitba_spomprivileg.file, STR_EMPTY)) && (!equals(_global_modl_ranne_chvaly.modlitba_spomprivileg.file, STR_UNDEF)) \
) \
||  \
(_global_modlitba == MODL_VESPERY &&  \
	(_global_modl_vespery.modlitba_spomprivileg.anchor != NULL) && (_global_modl_vespery.modlitba_spomprivileg.file != NULL) && \
	(strcmp(_global_modl_vespery.modlitba_spomprivileg.anchor, STR_EMPTY) != 0) && (strcmp(_global_modl_vespery.modlitba_spomprivileg.anchor, STR_UNDEF) != 0) && \
	(strcmp(_global_modl_vespery.modlitba_spomprivileg.file, STR_EMPTY) != 0) && (strcmp(_global_modl_vespery.modlitba_spomprivileg.file, STR_UNDEF) != 0) \
) \
||  \
(_global_modlitba == MODL_POSV_CITANIE &&  \
	(_global_modl_posv_citanie.citanie_spomprivileg.anchor != NULL) && (_global_modl_posv_citanie.citanie_spomprivileg.file != NULL) && \
	(strcmp(_global_modl_posv_citanie.citanie_spomprivileg.anchor, STR_EMPTY) != 0) && (strcmp(_global_modl_posv_citanie.citanie_spomprivileg.anchor, STR_UNDEF) != 0) &&  \
	(strcmp(_global_modl_posv_citanie.citanie_spomprivileg.file, STR_EMPTY) != 0) && (strcmp(_global_modl_posv_citanie.citanie_spomprivileg.file, STR_UNDEF) != 0) \
) \
))

// predĺžené slávenie vigílií v rámci posvätných čítaní | is vigily (for office with readings)? | VSLH, č. 73: slávnosť, sviatok alebo nedeľa
#define je_vigilia \
(_global_modlitba == MODL_POSV_CITANIE &&  \
	(_je_global_den_slavnost || _je_global_den_sviatok || _global_den.denvt == DEN_NEDELA || _global_den.litobd == OBD_OKTAVA_NARODENIA || _global_den.litobd == OBD_VELKONOCNA_OKTAVA || _global_den.litobd == OBD_VELKONOCNE_TROJDNIE) && \
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

// či sa NEMAJÚ zobrazovať vešpery; doteraz sa kontrolovalo len to, či je sobota -- opravené pre Svätú sobotu (Bielu sobotu) | are NOT vespers (= should I hide button for evening prayer)?
// slávnosti majú (druhé) vešpery vždy | solemnities always have (second) vespers
#define nie_su_vespery ( \
	(_global_den.denvt == DEN_SOBOTA) \
	&& (!((_global_den.denvt == DEN_SOBOTA) && (_global_den.litobd == OBD_VELKONOCNE_TROJDNIE))) \
	&& (!(_global_den.smer < 5)) \
)

// či sa môže sláviť ľubovoľná spomienka Panny Márie v sobotu (prvý level kontroly)
#define je_spomienka_PM_v_sobotu ( \
	(_global_den.litobd == OBD_CEZ_ROK) && (_global_den.denvt == DEN_SOBOTA) && (_global_den.denvr != SRDPM) \
)

// či sa naozaj môže sláviť ľubovoľná spomienka Panny Márie v sobotu (druhý level kontroly)
#define PODMIENKA_MOZE_BYT_SPOMIENKA_PM_V_SOBOTU ( \
	(je_spomienka_PM_v_sobotu) && \
	( \
		((_global_den.smer >= 11) && (_global_pocet_svatych == 0)) || \
		((((_global_svaty(1).smer >= 12) && (_decode_spol_cast(_global_svaty(1).spolcast).a1 != MODL_SPOL_CAST_PANNA_MARIA)) || MIESTNE_SLAVENIE_LOKAL_SVATY(1)) && (_global_pocet_svatych > 0)) \
	) \
)

// are there alternate hymns for Ordinary time (per annum)? (for SK based on LA LH)
#define je_alternativa_hymnus_ocr ( \
((_global_modlitba == MODL_PRVE_VESPERY || (_global_modlitba == MODL_VESPERY && _global_den.denvt == DEN_SOBOTA)) && ((_global_modl_prve_vespery.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
||  \
(_global_modlitba == MODL_PRVE_KOMPLETORIUM && ((_global_modl_prve_kompletorium.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
||  \
(_global_modlitba == MODL_VESPERY && ((_global_modl_vespery.alternativy & BIT_ALT_HYMNUS) == BIT_ALT_HYMNUS)) \
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

// are there alternate hymns for Easter? (for SK based on LA LH; only for Easter I)
#define je_alternativa_hymnus_vn ( \
(_global_modlitba == MODL_RANNE_CHVALY && ((_global_modl_ranne_chvaly.alternativy & BIT_ALT_HYMNUS_VN) == BIT_ALT_HYMNUS_VN)) \
||  \
(_global_modlitba == MODL_POSV_CITANIE && ((_global_modl_posv_citanie.alternativy & BIT_ALT_HYMNUS_VN) == BIT_ALT_HYMNUS_VN)) \
||  \
(_global_modlitba == MODL_VESPERY && ((_global_modl_vespery.alternativy & BIT_ALT_HYMNUS_VN) == BIT_ALT_HYMNUS_VN)) \
)

// are chosen alternative readings for 2nd readigns? (currently CZ only)
#define je_alternativne_2citanie ((_global_jazyk == JAZYK_CZ) && (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ALTERNATIVE_READINGS)))

// for JAZYK_CZ, is chosen alternative for hymns of supplement?
#define je_CZ_hymny_k_volnemu_vyberu ((_global_jazyk == JAZYK_CZ) && (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_CZ_HYMNY_VYBER)))
#define je_CZ_nie_hymny_k_volnemu_vyberu ((_global_jazyk == JAZYK_CZ) && (!isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_CZ_HYMNY_VYBER)))

// ToDo: before replacing anchor from file with HTML scratch, try to remove _special_anchor_prefix/postfix!!!
#define specialne_dni_bez_hymnov_k_volnemu_vyberu_CZ ((_global_den.denvr == VELKONOCNA_NEDELA) || (_global_den.denvr == SV_RODINY))

// Veľká noc padne na 22.-26. marca; vtedy je 19. marca vo Svätom týždni, a preto sa prekladá na sobotu pred Kvetnou nedeľou
#define je_slavnost_sv_Jozefa_prekladana_pred_Kvetnu_nedenu ((_global_den.denvt == DEN_SOBOTA) && (_global_den.denvr == _global_r._VELKONOCNA_NEDELA.denvr - 8) && (_global_r._VELKONOCNA_NEDELA.mesiac == MES_MAR + 1) && (_global_r._VELKONOCNA_NEDELA.den >= 22) && (_global_r._VELKONOCNA_NEDELA.den <= 26))
#define je_slavnost_sv_Jozefa_prekladana_na_20MAR ((_global_den.denvt == DEN_PONDELOK) && (_global_den.den == 20) && (_global_den.mesiac == MES_MAR + 1))
// Veľká noc padne na 22.-31. marca; vtedy je 25. marca vo Svätom týždni, Trojdní resp. Veľkonočnej oktáve, a preto sa prekladá na pondelok po skončení Veľkonočnej oktávy
#define je_slavnost_Zvestovania_prekladana_po_Velkonocnej_oktave_MAR ((_global_den.denvt == DEN_PONDELOK) && (_global_den.denvr == _global_r._VELKONOCNA_NEDELA.denvr + 8) && (_global_r._VELKONOCNA_NEDELA.mesiac == MES_MAR + 1) && (_global_r._VELKONOCNA_NEDELA.den >= 22) && (_global_r._VELKONOCNA_NEDELA.den <= 31))
#define je_slavnost_Zvestovania_prekladana_po_Velkonocnej_oktave_APR ((_global_den.denvt == DEN_PONDELOK) && (_global_den.denvr == _global_r._VELKONOCNA_NEDELA.denvr + 8) && (((_global_r._VELKONOCNA_NEDELA.mesiac == MES_APR + 1) && (_global_r._VELKONOCNA_NEDELA.den >= 1) && (_global_r._VELKONOCNA_NEDELA.den <= 1)) || ((_global_r._VELKONOCNA_NEDELA.mesiac == MES_MAR + 1) && (_global_r._VELKONOCNA_NEDELA.den >= 24) && (_global_r._VELKONOCNA_NEDELA.den <= 31))))
#define je_slavnost_Zvestovania_prekladana_na_26MAR ((_global_den.denvt == DEN_PONDELOK) && (_global_den.den == 26) && (_global_den.mesiac == MES_MAR + 1))

// Spomienka na všetkých zosnulých veriacich (02NOV) padne na nedeľu
#define je_Spomienka_na_zosnulych_02NOV_nedela ((_global_den.denvt == DEN_NEDELA) && (_global_den.den == 2) && (_global_den.mesiac == MES_NOV + 1))

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

// is psalm 146/150 in Officium defunctoribus? (it would suffice: morning prayer)
#define je_alternativa_off_def_z146_150(modlitba) (\
	((modlitba == MODL_RANNE_CHVALY) && ((_global_modl_ranne_chvaly.alternativy & BIT_ALT_OFF_DEF_PSALM_146_150) == BIT_ALT_OFF_DEF_PSALM_146_150)) \
)

// 'poradie svätého' by malo byť medzi 1..PORADIE_PM_SOBOTA - 1
#define JE_PORADIE_SVATY_OK(i) ((i > 0 && i < PORADIE_PM_SOBOTA))

#define MIESTNE_SLAVENIE_LOKAL_SVATY(i) (JE_PORADIE_SVATY_OK(i) && ((_global_svaty_i_smer_override(i) == 4) || (_global_svaty_i_smer_override(i) == 8) || (_global_svaty_i_smer_override(i) == 11)))

#define _je_global_svaty_i_sviatok_alebo_slavnost(i) (JE_PORADIE_SVATY_OK(i) && ((_global_svaty(i).typslav == SLAV_SVIATOK) || (_global_svaty(i).typslav == SLAV_SLAVNOST) || ((i != PORADIE_PM_SOBOTA) && (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OVERRIDE_STUP_SLAV)))))

#define _je_global_svaty_i_sviatok(i) (JE_PORADIE_SVATY_OK(i) && ((_global_svaty(i).typslav == SLAV_SVIATOK) || ((i != PORADIE_PM_SOBOTA) && (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OVERRIDE_STUP_SLAV) && (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_STUP_SVIATOK_SLAVNOST))))))
#define _je_global_svaty_i_slavnost(i) (JE_PORADIE_SVATY_OK(i) && ((_global_svaty(i).typslav == SLAV_SLAVNOST) || ((i != PORADIE_PM_SOBOTA) && isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OVERRIDE_STUP_SLAV) && (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_STUP_SVIATOK_SLAVNOST) || (_global_svaty(i).typslav == SLAV_SVIATOK)))))

#define _je_global_den_sviatok ((_global_den.typslav == SLAV_SVIATOK) || ((_global_poradie_svaty > 0) && (_global_poradie_svaty < PORADIE_PM_SOBOTA) && isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OVERRIDE_STUP_SLAV) && (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_STUP_SVIATOK_SLAVNOST))))
#define _je_global_den_slavnost ((_global_den.typslav == SLAV_SLAVNOST) || ((_global_poradie_svaty > 0) && (_global_poradie_svaty < PORADIE_PM_SOBOTA) && isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OVERRIDE_STUP_SLAV) && (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_STUP_SVIATOK_SLAVNOST) || (_global_den.typslav == SLAV_SVIATOK))))

#define _je_local_den_sviatok ((_local_den.typslav == SLAV_SVIATOK) || (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OVERRIDE_STUP_SLAV) && (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_STUP_SVIATOK_SLAVNOST))))
#define _je_local_den_slavnost ((_local_den.typslav == SLAV_SLAVNOST) || (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OVERRIDE_STUP_SLAV) && (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_STUP_SVIATOK_SLAVNOST) || (_local_den.typslav == SLAV_SVIATOK))))

extern short int _smer_override(short int smer, short int typslav);
extern short int _typslav_override(short int typslav);

#define _global_den_smer_override _smer_override(_global_den.smer, _global_den.typslav)
#define _global_svaty_i_smer_override(i) _smer_override(_global_svaty(i).smer, _global_svaty(i).typslav)

#define pouzit_na_spomienky_casti_zo_spolocnych_casti (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_SPOMIENKA_SPOL_CAST) || (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_OVERRIDE_STUP_SLAV)))

#define NAZOV_SLAVENIA_LOKAL_LOCAL_DEN_TYPSLAV_LOKAL ((_local_den.typslav_lokal == LOKAL_SLAV_KONSEKR_KOSTOLY) ? (char *)text_LEN_V_KONSEKROVANYCH_KOSTOLOCH[_global_jazyk] : ((_local_den.typslav_lokal == LOKAL_SLAV_KONIEC_OKTAVY_NAR) ? (char *)text_KONIEC_OKTAVY_NARODENIA_PANA[_global_jazyk] : ((_local_den.typslav_lokal == LOKAL_SLAV_DRUHA_VELK_NEDELA) ? (char *)text_NEDELA_VO_VELKONOCNEJ_OKTAVE_SUBSTRING[_global_jazyk] : nazov_slavenia_lokal[_local_den.typslav_lokal])))

// should calendar be exported?
#define PODMIENKA_EXPORTOVAT_KALENDAR (!((_global_kalendar == KALENDAR_NEURCENY) || (_global_kalendar == KALENDAR_VSEOBECNY) || ((_global_kalendar == default_kalendar[_global_jazyk]) && !(_global_jazyk == JAZYK_CZ_OP))))

#define PODMIENKA_EXPORTOVAT_FONTSIZE_PT ( (_global_font_size_pt > 0) && (_global_font_size_pt != FONT_SIZE_PT_DEFAULT) )

#define PODMIENKA_EXPORTOVAT_FONTSIZE ( (_global_font_size != FONT_SIZE_UNDEF) && (_global_font_size != FONT_SIZE_CSS) )

extern char pom_FONT[SMALL];

#define PODMIENKA_EXPORTOVAT_CUSTOM_FONT ((_global_font == FONT_CUSTOM) && (!equals(pom_FONT, STR_EMPTY)))

#define PODMIENKA_EXPORTOVAT_STATIC_FONT ((_global_font != FONT_CUSTOM) && (_global_font != FONT_CSS) && (_global_font != FONT_CHECKBOX))

#define PODMIENKA_EXPORTOVAT_CSS ((_global_css != CSS_UNDEF) && (_global_css != CSS_breviar_sk))

#define PODMIENKA_EXPORTOVAT_STYLE_MARGIN ( (_global_style_margin > MIN_STYLE_MARGIN) && (_global_style_margin < MAX_STYLE_MARGIN)  && (_global_style_margin != DEF_STYLE_MARGIN) )

#define PODMIENKA_EXPORTOVAT_LINE_HEIGHT_PERC ( (_global_line_height_perc > MIN_LINE_HEIGHT_PERC) && (_global_line_height_perc < MAX_LINE_HEIGHT_PERC) && (_global_line_height_perc != DEF_LINE_HEIGHT_PERC) )

#define PODMIENKA_JE_BATCH_MODE_MONTHLY__AND__PLAIN_EXPORT ((_global_opt_batch_monthly == ANO) && (export_monthly_druh > 2))

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
#define POPOLCOVA_STREDA  _global_r._POPOLCOVA_STREDA.denvr             // Popolcová streda
#define VELKONOCNA_NEDELA   _global_r._VELKONOCNA_NEDELA.denvr          // Veľkonočná nedeľa
#define KVETNA_NEDELA (VELKONOCNA_NEDELA - 7)                           // Palmová (Kvetná) nedeľa
#define ZELENY_STVRTOK   (VELKONOCNA_NEDELA - 3)                        // Štvrtok Svätého týždňa (Zelený štvrtok)
#define VELKY_PIATOK   (VELKONOCNA_NEDELA - 2)                          // Piatok utrpenia Pána (Veľký piatok)
#define BIELA_SOBOTA   (VELKONOCNA_NEDELA - 1)                          // Svätá sobota (Biela sobota)
#define VELKONOCNY_PONDELOK (VELKONOCNA_NEDELA + 1)                     // Veľkonočný pondelok
#define DRUHA_VELKONOCNA_NEDELA  (VELKONOCNA_NEDELA + 7)                // nedeľa vo Veľkonočnej oktáve
#define NANEBOVSTUPENIE  _global_r._NANEBOVSTUPENIE_PANA.denvr          // nanebovstúpenie Pána (štvrtok, 40. deň po veľkej noci, alebo v krajinách, kde sa presúva na nasledujúcu nedeľu ("7. veľkonočná nedeľa")
#define PRVA_ADVENTNA_NEDELA  _global_r._PRVA_ADVENTNA_NEDELA.denvr     // Prvá adventná nedeľa
#define ZOSLANIE_DUCHA_SV  _global_r._ZOSLANIE_DUCHA_SV.denvr           // Zoslanie Ducha Svätého
#define SV_RODINY  _global_r._SVATEJ_RODINY.denvr                       // sviatok Svätej rodiny
#define MARIE_MATKY_CIRKVI (ZOSLANIE_DUCHA_SV + 1)                      // pondelok po Zoslaní Ducha Svätého (ZOSLANIE_DUCHA_SV): spomienka Panny Márie, Matky Cirkvi (http://press.vatican.va/content/salastampa/it/bollettino/pubblico/2018/03/03/0168/00350.html)
#define KRISTA_KNAZA (ZOSLANIE_DUCHA_SV + 4)                            // štvrtok po Zoslaní Ducha Svätého (ZOSLANIE_DUCHA_SV): sviatok Nášho Pána Ježiša Krista, najvyššieho a večného kňaza (http://www.tkkbs.sk/view.php?cisloclanku=20140115028)
#define TROJICA (ZOSLANIE_DUCHA_SV + 7)                                 // prvá nedeľa po ZOSLANIE_DUCHA_SV: najsv. Trojice
// #define TELAKRVI (ZOSLANIE_DUCHA_SV + 11)                               // štvrtok po Trojici: Kristovho tela a krvi (alebo: v krajinách, kde sa presúva na nedeľu)
#define SRDCA (ZOSLANIE_DUCHA_SV + 19)                                  // piatok po druhej nedeli po ZOSLANIE_DUCHA_SV: najsv. srdca Ježišovho
#define SRDPM (ZOSLANIE_DUCHA_SV + 20)                                  // sobota po druhej nedeli po ZOSLANIE_DUCHA_SV: nepoškvrneného srdca prebl. p. márie
// 2006-08-22: kvôli ružovej farbe rúcha potrebujeme define aj pre 3. adventnú nedeľu a 4. pôstnu nedeľu
#define TRETIA_ADVENTNA_NEDELA (PRVA_ADVENTNA_NEDELA + 14)              // tretia adventná nedeľa - dva týždne po prvej adventnej nedeli (PRVA_ADVENTNA_NEDELA)
#define STVRTA_POSTNA_NEDELA (VELKONOCNA_NEDELA - 21)                   // štvrtá pôstna nedeľa - tri týždne pred VELKONOCNA_NEDELA

#define OBETOVANIE_PANA 33

// 2014-04-08: presunuté do #define -- bolo na 2 rôznych miestach | sviatky Pána a svätých, ktoré majú prednosť pred Cezročnou nedeľou a majú (ak padnú na nedeľu) svoje vlastné prvé vešpery
// ------------- pôvodné poznámky ------------- 
// 2011-06-30: cyril a metod odvetvený pre SK a CZ only
// 2011-07-22: doplnené pre HU: 20AUG
// 2011-10-13: zapoznámkované 14SEP kvôli CZ // nespúšťalo sa totiž zaltar_zvazok(), a teda ani zaltar_kompletorium()
// 2012-10-22: odpoznámkované 14SEP -- napr. pre rok 2014 potom nedávalo prvé vešpery, ak padne na nedeľu!
// 2014-01-10: doplnené 02FEB (ak padne na nedeľu, má prvé vešpery)
// 2014-04-08: 14SEP platí aj pre CZ (ak padne na nedeľu, má prvé vešpery)
#define PODMIENKA_SVIATKY_PANA_SVATYCH_PREDNOST_PRED_NEDELOU_OCR (\
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

#define _je_local_den_vlastne_slavenie_pismV (\
(_local_den.denvr == OBETOVANIE_PANA) || \
(_local_den.denvr == KRST) || \
(_local_den.denvr == VELKONOCNA_NEDELA) || \
(_local_den.denvr == ZOSLANIE_DUCHA_SV) || \
(_local_den.denvr == TROJICA) || \
(_local_den.denvr == SV_RODINY) \
)

#ifndef OS_linux
// kedysi bolo void main; 2003-07-14, kvoli gcc version 3.2.2 20030222 (Red Hat Linux 3.2.2-5) christ-net.sk 
int main(int argc, const char** argv);
#endif // OS_linux

int breviar_main(int argc, const char** argv);

#if (_MSC_VER >= 1400)       // VC8+ 2007-02-12 kvôli vc++ 2005 express edition
#pragma warning(disable : 4996)    // disable all deprecation warnings
#define putenv _putenv
#endif   // VC8+

#endif // __BREVIAR_H_


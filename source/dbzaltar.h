/************************************************************/
/*                                                          */
/* dbzaltar.h                                               */
/* (c)1999-2023 | Juraj Vidéky | videky@breviar.sk          */
/*                                                          */
/* description | contains definitions for 'database'        */
/*               of liturgical calendars                    */
/*                                                          */
/************************************************************/

#include "vstudio.h"

#ifndef __DBZALTAR_H_
#define __DBZALTAR_H_

#include "liturgia.h"
#include "mydefs.h"
#include "common.h"

#include "myexpt.h" // export do suboru alebo na konzolu printf
#include "mylog.h"
#include <string.h>
#include "myhpage.h" // kvôli hlavicka()

short int sviatky_svatych(short int, short int);

short int sviatky_svatych(short int, short int, short int);

short int sviatky_svatych(short int, short int, short int, short int); // spustam druhykrat

extern short int modlitba;

// anchors - nazvy kotiev pre zaltar styroch tyzdnov
extern char _anchor[MAX_STR_AF_ANCHOR];
extern char _anchor_head[MAX_STR_AF_ANCHOR];
extern char _anchor_head_without_underscore[MAX_STR_AF_ANCHOR];

extern char pismenko_modlitby(short int modlitba);
extern void anchor_name_zaltar(short int den, short int tyzzal, short int modlitba, const char* anchor);
extern void anchor_name_zaltar_alt(short int den, short int tyzzal, short int modlitba, const char* anchor, short int alt);

extern char _file[MAX_STR_AF_FILE]; // nazov súboru, napr. _1ne.htm
extern char _file_pc[MAX_STR_AF_FILE]; // nazov fajlu pre posvatne citania
extern char _file_pc_tyzden[MAX_STR_AF_FILE]; // nazov fajlu pre posvatne citania v zavislosti od tyzdna (obdobie cez rok)
extern char _file_orig[MAX_STR_AF_FILE]; // nazov súboru, do ktorého sa v prípade kompletória dočasne odloží pôvodný súbor

// "funkcie" na store/restore pôvodného filename
#define file_name_zapamataj()	strcpy(_file_orig, _file);
#define file_name_obnov()		strcpy(_file, _file_orig);

extern void file_name_zaltar(short int den, short int tyzzal);
extern void file_name_litobd(short int litobd);
extern void file_name_litobd_pc(short int litobd);
extern void file_name_vlastny_kalendar(short int kalendar);
extern void file_name_kompletorium(short int litobd);
extern void file_name_litobd_pc_tyzden(short int litobd, short int tyzden);

extern void _add_special_anchor_postfix();

extern void set_hymnus_kompletorium_obd(short int den, short int tyzzal, short int modlitba, short int litobd);
extern void set_hymnus(short int den, short int tyzzal, short int modlitba);

extern void set_antifony_kompletorium_obd(short int den, short int modlitba, short int litobd, short int zvazok);
extern void set_antifony(short int den, short int tyzzal, short int zvazok, short int modlitba);
extern void set_kcitanie(short int den, short int tyzzal, short int modlitba, short int ktore = 2);

extern void set_kresponz_kompletorium_obd(short int den, short int modlitba, short int litobd);
extern void set_kresponz(short int den, short int tyzzal, short int modlitba);
extern void set_prosby(short int den, short int tyzzal, short int modlitba);
extern void _set_prosby_dodatok(short int den, short int force_prve_vespery = NIE);
extern void set_modlitba(short int den, short int tyzzal, short int modlitba, short int ktore = 2);
extern void set_benediktus(short int den, short int tyzzal, short int modlitba);
extern void set_magnifikat(short int den, short int tyzzal, short int modlitba);
extern void set_nunc_dimittis(short int modlitba);
extern void set_popis(short int modlitba, char* file, char* anchor);
extern void set_popis_dummy(void);
extern void set_popis_dummy_except_vespers(void);

extern void _set_zalmy_mcd_doplnkova_psalmodia_alternativy(short int modlitba);
extern void _set_zalmy_mcd_doplnkova_psalmodia(short int je_predpisana_povinne = ANO);
extern void _set_antifony_mcd_doplnkova_psalmodia(void);
extern void _set_zalmy_1nedele_mcd(void);
extern void _set_zalmy_2nedele_mcd(void);
extern void _set_zalmy_mcd_1nedela_or_doplnkova_psalmodia(void);
extern void _set_kompletorium_nedela_spolocne(short int modlitba);
extern void _set_kompletorium_nedela(short int modlitba);
extern void _set_kompletorium_slavnost(short int modlitba);
extern void _set_kompletorium_slavnost_oktava(short int modlitba, short int litobd, short int ktore);

extern void zaltar_kompletorium_okrem_zalmov(short int den, short int obdobie, short int specialne, short int tyzzal, short int modlitba);
extern void zaltar_kompletorium(short int den, short int obdobie, short int specialne, short int tyzzal);

extern void _set_zalmy_pc_145(short int modlitba);
extern void _set_zalmy_mcd_zaltar(short int den, short int tyzzal, short int modlitba);
extern void set_zalmy_mcd_zaltar(short int den, short int tyzzal);

extern void zaltar_zvazok(short int den, short int tyzzal, short int obdobie, short int specialne);
extern void zaltar(short int den, short int tyzzal);

extern void _set_zalmy_velky_piatok(short int modlitba);
extern void _set_zalmy_biela_sobota(short int modlitba);
extern void _set_zalmy_za_zosnulych(short int modlitba);
extern void _set_zalmy_1nedele_rch(void);
extern void _set_zalmy_1nedele_v(void);
extern void _set_zalmy_1nedele_v_pre_1v(void);
extern void _set_zalmy_1nedele_pc(void);
extern void _set_zalmy_posviacka_chramu(short int modlitba);
extern void _set_zalmy_velkonocna_nedela(short int modlitba);
extern void _set_zalmy_nanebovstupenie(short int modlitba);
extern void _set_zalmy_zoslanie_ducha_sv(short int modlitba);
extern void _set_zalmy_najsv_trojice(short int modlitba);
extern void _set_zalmy_krista_krala(short int modlitba);
extern void _set_zalmy_telakrvi(short int modlitba);
extern void _set_zalmy_srdca(short int modlitba);
extern void _set_zalmy_knaza(short int modlitba);
extern void _set_zalmy_narodenie(short int modlitba);
extern void _set_zalmy_zjv(short int modlitba);
extern void _set_zalmy_premenenie(short int modlitba);
extern void _set_zalmy_sviatok_apostolov(short int modlitba);
#define _set_zalmy_sviatok_sv_muzov(a) _set_zalmy_sviatok_duch_past(a)
extern void _set_zalmy_sviatok_duch_past(short int modlitba);
extern void _set_zalmy_sviatok_panien(short int modlitba);
extern void _set_zalmy_sviatok_marie(short int modlitba);
extern void _set_zalmy_sviatok_jana_ap(short int modlitba);
extern void _set_zalmy_sviatok_muc(short int modlitba);
extern void _set_zalmy_sviatok_muc(short int modlitba, short int su_viaceri);
extern void _set_zalmy_sviatok_krstu(short int modlitba);
extern void _set_zalmy_sviatok_obetovania(short int modlitba);
extern void _set_zalmy_slavnost_Cyrila_a_Metoda(short int modlitba);
extern void _set_zalmy_sv_kriz(short int modlitba);
extern void _set_zalmy_archanjelov(short int modlitba);
extern void _set_zalmy_anjelov_strazcov(short int modlitba);
extern void _set_zalmy_vsetkych_svatych(short int modlitba);
extern void _set_zalmy_najsv_mena_jezisovho_czop(short int modlitba);
extern void _set_zalmy_najsv_mena_jezisovho_sk_ofm(short int modlitba);
extern void _set_zalmy_cssr_titul(short int modlitba);
extern void _set_zalmy_csa_augustin_obr(short int modlitba);
extern void _set_zalmy_csa_augustin(short int modlitba);
extern void _set_zalmy_sj_ignac(short int modlitba);
extern void _set_zalmy_sj_vsetkych_svatych(short int modlitba);
extern void _set_zalmy_sj_xaver(short int modlitba);
extern void _set_zalmy_ocd_elias(short int modlitba);
extern void _set_zalmy_op_dominik(short int modlitba);
extern void _set_zalmy_ofmcap_dominik(short int modlitba);
extern void _set_zalmy_ocd_terezka(short int modlitba);
extern void _set_zalmy_ocd_terezia(short int modlitba);
extern void _set_zalmy_ocd_vsetci_svati(short int modlitba);
extern void _set_zalmy_ocd_jan_z_kriza(short int modlitba);
extern void _set_zalmy_pc_1_8_16(short int modlitba);
extern void _set_zalmy_pc_1_8_15(short int modlitba);
extern void _set_zalmy_opraem_pc_1_8_21(short int modlitba);
extern void _set_zalmy_opraem_pc_1_8_24(short int modlitba);
extern void _set_zalmy_cm_pc_1_41_84(short int modlitba);
extern void _set_zalmy_op_utrpenie(short int modlitba);
extern void _set_zalmy_op_29apr(short int modlitba);
// extern void _set_zalmy_pc_1_21_92(short int modlitba);
extern void _set_zalmy_pc_1_12_24(short int modlitba);
extern void _set_zalmy_pc_15_66(short int modlitba);
extern void _set_zalmy_pc_24_61_84(short int modlitba);
extern void _set_zalmy_pc_40_27(short int modlitba);
extern void _set_zalmy_pc_45_87(short int modlitba);
extern void _set_zalmy_vesp_110_116_ef(short int modlitba);
extern void _set_zalmy_vesp_110_122_zjv15(short int modlitba);
extern void _set_zalmy_vesp_89_98_kol(short int modlitba);
extern void _set_zalmy_vesp_113_146_ef(short int modlitba);
extern void _set_zalmy_vesp_127_111_kol(short int modlitba);
extern void _set_zalmy_osu_angela_merici(short int modlitba);
extern void _set_zalmy_ofm_frantisek(short int modlitba);
extern void _set_zalmy_sviatok_muc_ofm(short int modlitba);
extern void _set_zalmy_velk_oktava(short int den, short int modlitba);
extern void _set_zalmy_vian_oktava(short int den, short int modlitba);

extern void _set_popis(short int modlitba, const char* file, const char* anchor);

extern void _set_mcd_len_doplnkova_psalmodia(short int modlitba);
extern void _set_mcd_doplnkova_psalmodia_alternativy(short int modlitba);
extern void _set_mcd_doplnkova_psalmodia_z122_129(short int modlitba);
extern void _set_mcd_doplnkova_psalmodia_z126_129(short int modlitba);
extern void _set_mcd_doplnkova_psalmodia_z127_131(short int modlitba);

extern void _set_hymnus_alternativy(short int modlitba, short int litobd);
extern void _set_hymnus_alternativy(short int modlitba);
extern void _set_hymnus_alternativy_NO(short int modlitba, short int litobd);
extern void _set_hymnus_alternativy_NO(short int modlitba);
extern void _set_hymnus(short int modlitba, const char* file, const char* anchor);

extern void _set_antifona1(short int modlitba, const char* file, const char* anchor);
extern void _set_antifona2(short int modlitba, const char* file, const char* anchor);
extern void _set_antifona3(short int modlitba, const char* file, const char* anchor);

extern void _set_zalm1(short int modlitba, const char* file, const char* anchor);

#define _set_rchvalospev _set_zalm2
extern void _set_zalm2(short int modlitba, const char* file, const char* anchor);

#define _set_vchvalospev _set_zalm3
extern void _set_zalm3(short int modlitba, const char* file, const char* anchor);

extern void set_zalm(short int ktory, short int modlitba, const char* file, const char* anchor);

// pri posvatnom citani plati pre 1. citanie
#define _set_citanie1 _set_kcitanie

extern void _set_kcitanie(short int modlitba, const char* file, const char* anchor);
extern void _set_kresponz(short int modlitba, const char* file, const char* anchor);

// pre posvätné čítanie: 2. čítanie
#define _set_citanie2 _set_benediktus

#define _set_magnifikat _set_benediktus

// pre kompletórium: ant. na Nunc dimittis
#define _set_nunc_dimittis _set_benediktus

// pre kompletórium: úkon kajúcnosti
#define _set_ukonkaj _set_prosby

extern void _set_benediktus(short int modlitba, const char* file, const char* anchor);
extern void _set_prosby(short int modlitba, const char* file, const char* anchor);
extern void _set_modlitba(short int modlitba, const char* file, const char* anchor);
extern void _set_maria_ant(short int modlitba, const char* file, const char* anchor);
extern void _set_otcenas_uvod(short int modlitba, const char* file, const char* anchor);

extern void _set_ant_spomprivileg(short int modlitba, const char* file, const char* anchor);
extern void _set_modlitba_spomprivileg(short int modlitba, const char* file, const char* anchor);
extern void _set_2citanie_spomprivileg(short int modlitba, const char* file, const char* anchor);
extern void _set_antifona_vig(short int modlitba, const char* file, const char* anchor);
extern void _set_chvalospev1(short int modlitba, const char* file, const char* anchor);
extern void _set_chvalospev2(short int modlitba, const char* file, const char* anchor);
extern void _set_chvalospev3(short int modlitba, const char* file, const char* anchor);

extern void _set_evanjelium(short int modlitba, const char* file, const char* anchor);

extern void _set_chvalospev_vig_adv(short int modlitba);
extern void _set_chvalospev_vig_vian(short int modlitba);
extern void _set_chvalospev_vig_ocr(short int modlitba);
extern void _set_chvalospev_vig_tk(short int modlitba);
extern void _set_chvalospev_vig_srdca(short int modlitba);
extern void _set_chvalospev_vig_knaza(short int modlitba);
extern void _set_chvalospev_vig_vsetkych_svatych(short int modlitba);
extern void _set_chvalospev_vig_krkrala(short int modlitba);
extern void _set_chvalospev_vig_post(short int modlitba);
extern void _set_chvalospev_vig_vn(short int modlitba);
extern void _set_chvalospev_vig_sc_vpchr(short int modlitba);
extern void _set_chvalospev_vig_sc_pm(short int modlitba);
extern void _set_chvalospev_vig_sc_ap(short int modlitba);
extern void _set_chvalospev_vig_sc_vm(short int modlitba);
extern void _set_chvalospev_vig_sc_sm_sz(short int modlitba);
extern void _set_chvalospev_vig_sviatok_obetovania(short int modlitba);
extern void _set_chvalospev_vig_sc_pm_ocd(short int modlitba);
extern void _set_chvalospev_vig_sc_sm_ocd(short int modlitba);
extern void _set_chvalospev_vig_terezka_ocd(short int modlitba);

extern const char* html_title[POCET_JAZYKOV + 1];

extern void _vlastne_slavenie_hymnus(short int modlitba, char vlastny_anchor[SMALL], short int litobd, short int pouzit_special_anchor = ANO);

extern void _velk1_hymnus(short int den, short int modlitba, short int litobd);

/* zaltar();
 *
 * vstup: den == 0 (DEN_NEDELA) .. 6 (DEN_SOBOTA)
 *        tyzzal == 1 .. 4 (prvy az stvrty tyzzal zaltar
 *
 * nastavi do _global_modl_... (podla _global_modlitba) udaje potrebne
 * k modlitbe
 *
 *
 * 2006-01-24: žalmy pre posvätné čítanie sú v II. zväzku žaltára (pôst, veľká noc)
 *             pre niektoré dni odlišné, preto sme vytvorili aj ďalší parameter,
 *             ktorý sa používa len pri volaní za účelom konkrétnej modlitby
 *             (pre voľbu posv. čítania len pre deň a týždeň žaltára sa použije default)
 *
 */
extern void zaltar(short int den, short int tyzzal);

extern void zaltar_zvazok(short int den, short int tyzzal, short int obdobie);

extern void slavnost_srdca(short int litobd = OBD_CEZ_ROK);

extern void liturgicke_obdobie(short int litobd, short int tyzden, short int den, short int tyzzal, short int poradie_svateho);

extern short int su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(short int m);

extern short int _spol_cast_vyber_dp_pn(_struct_sc sc);
extern short int _spol_cast_je_panna(_struct_sc sc);
extern void _spolocna_cast_hymnus_rozne(short int modlitba, char *_anchor_pom, char *_anchor, char *_file, int force);
extern void _spolocna_cast_benediktus_rozne(short int modlitba, char *_anchor_pom, char *_anchor, char *_file, int force);
extern void _spolocna_cast_magnifikat_rozne(short int modlitba, char *_anchor_pom, char *_anchor, char *_file, int force);
extern void _spolocna_cast_kresponz_rozne(short int modlitba, char *_anchor_pom, char *_anchor, char *_file, int force);
extern void _spolocna_cast_2cit_rozne(short int modlitba, char *_anchor_pom, char *_anchor, char *_file);
extern void _spolocna_cast_modlitba_rozne(short int modlitba, char *_anchor_pom, char *_anchor, char *_file);
extern void _spolocna_cast_ant3_viac_ozz(char *_anchor_head, char *_anchor, char *_file);
extern void _spolocna_cast_1cit_zvazok(short int modlitba, const char* _anchor_pom, const char* _anchor_zvazok, const char* _anchor, const char* _file, int force = 0);
extern void _spolocna_cast_kresponz_zvazok(short int modlitba, char *_anchor_pom, char *_anchor_zvazok, char *_anchor, char *_file, int force);
extern void __set_spolocna_cast(short int a, short int poradie_svaty, _struct_sc sc, int force = 0);
extern void set_popis_svaty_rch_mcd_pc_vesp(short int poradie_svaty);
extern void set_popis_svaty_rch_mcd_pc_vesp_den_mesiac(short int den, short int mesiac);
extern void set_spolocna_cast(_struct_sc sc, short int poradie_svaty, int force = 0);

/* #define BEGIN -------------------------------------------------------------------------------------------------------------------- */

/* zaltar();
*
* vstup: den == 0 (DEN_NEDELA) .. 6 (DEN_SOBOTA)
*        tyzzal == 1 .. 4 (prvy az stvrty tyzzal zaltar
*
* nastavi do _global_modl_... (podla _global_modlitba) udaje potrebne k modlitbe
* nakoniec pridane porovnanie s option "ci brat zalmy z doplnkovej psalmodie pre modlitbu cez den"
*
* žalmy pre posvätné čítanie sú v II. zväzku žaltára (pôst, veľká noc) pre niektoré dni odlišné, preto vytvorený ďalší parameter, ktorý sa používa len pri volaní za účelom konkrétnej modlitby (pre voľbu posv. čítania len pre deň a týždeň žaltára sa použije default)
*
* odvetvené nastavenie vecí pre kompletórium kvôli možnosti samostatne ich nastaviť (napr. kvôli sviatku Premenenia Pána) - logovanie nastavenia žalmov
*
*/
#define _SET_SPOLOCNE_VECI_NEDELA(m) {\
	set_hymnus  (den, tyzzal, m); \
	if((isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_ZALTAR_TRI)) && (je_modlitba_cez_den(m))){ \
		set_antifony(den, UPRAV_TYZZAL(tyzzal, m), zvazok, m); \
	} \
	else{ \
		set_antifony(den, tyzzal, zvazok, m); \
	} \
	set_kcitanie(den, tyzzal, m); \
	set_kresponz(den, tyzzal, m); \
	set_prosby  (den, tyzzal, m); \
}
#define _SET_SPOLOCNE_VECI_NIE_NEDELA(m) {\
	set_hymnus  (den, tyzzal, m); \
		if((isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_ZALTAR_TRI)) && (je_modlitba_cez_den(m))){ \
			set_antifony(den, UPRAV_TYZZAL(tyzzal, m), zvazok, m); \
		} \
		else{ \
			set_antifony(den, tyzzal, zvazok, m); \
		} \
	set_kcitanie(den, tyzzal, m); \
	set_kresponz(den, tyzzal, m); \
	set_prosby  (den, tyzzal, m); \
	set_modlitba(den, tyzzal, m); \
}

#define _SET_HYMNUS_ANTINFONY_MCD(m) {\
	set_hymnus  (den, tyzzal, m); \
	if((isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_ZALTAR_TRI)) && (je_modlitba_cez_den(m))){ \
		set_antifony(den, UPRAV_TYZZAL(tyzzal, m), zvazok, m); \
		} \
	else{ \
		set_antifony(den, tyzzal, zvazok, m); \
	} \
}

#define _SET_SPOLOCNE_VECI_COMMON(m) {\
	set_otcenas_uvod(m); \
}

/* ------------------------------------------------------------------------------------------- */

#define LOG_ciara_sv Log("  -------------------------\n");

#define set_LOG_litobd Log("   set(litobd): %s: súbor `%s', kotva `%s'\n", nazov_modlitby(modlitba), _file, _anchor)
#define set_LOG_litobd_pc Log("   set(litobd): %s: súbor `%s', kotva `%s'\n", nazov_modlitby(modlitba), _file_pc, _anchor)
#define set_LOG_litobd_pc_tyzden Log("   set(litobd): %s: súbor `%s', kotva `%s'\n", nazov_modlitby(modlitba), _file_pc_tyzden, _anchor)

#define set_LOG_zaltar Log("   set(zaltar): %s: súbor `%s', kotva `%s'\n", nazov_modlitby(modlitba), _file, _anchor)

#define set_LOG_svsv Log("   set(svsv): %s: súbor `%s', kotva `%s'\n", nazov_modlitby(modlitba), _file, _anchor)

/* ked dostane strukturu sc, vrati
* MODL_SPOL_CAST_DUCH_PAST_... resp.
* MODL_SPOL_CAST_PANNA
* alebo MODL_SPOL_CAST_REHOLNIK -- vtedy priradim MODL_SPOL_CAST_SV_MUZ; 03/03/2000A.D.
* mozno je to diskriminujuce, ale napr. kvoli sv. Efremovi (9. juna),
* ak nematchuje, vrati MODL_SPOL_CAST_SV_MUZ; 03/03/2000A.D.
* (predtym som vracal MODL_SPOL_CAST_NEURCENA)
*/
#define ucitel_cirkvi__sc_duch_pastier_panna {\
	if((a == MODL_SPOL_CAST_DUCH_PAST_KNAZ) || (a == MODL_SPOL_CAST_DUCH_PAST_BISKUP) || (a == MODL_SPOL_CAST_DUCH_PAST_PAPEZ) || (a == MODL_SPOL_CAST_PANNA)){\
		Log("matches (duchovny pastier || panna). returning %s (%d)\n", nazov_spolc(a), a);\
		return a;\
		}\
		else if((a == MODL_SPOL_CAST_SV_MUZ_REHOLNIK) || (a == MODL_SPOL_CAST_SV_MUZ)){\
		Log("matches (reholnik || muz). returning %s (%d)\n", nazov_spolc(MODL_SPOL_CAST_SV_MUZ), MODL_SPOL_CAST_SV_MUZ);\
		return MODL_SPOL_CAST_SV_MUZ;\
	}\
}

#define mucenik__sc_panna { if(a == MODL_SPOL_CAST_PANNA) { Log("matches. returning ANO\n"); return ANO; } }

#define panna__sc_mucenica { if(a == MODL_SPOL_CAST_MUCENICA) { Log("matches. returning ANO\n"); return ANO; } }

/* ------------------------------------------------------------------------------------------- */

#define _vlastne_slavenie_popis(anchor) {\
	sprintf(_anchor, "%s_%s", anchor, ANCHOR_POPIS);\
	_set_popis(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

#define _vlastne_slavenie_popis_mcd(anchor) {\
	sprintf(_anchor, "%s_%s", anchor, ANCHOR_POPIS);\
	_set_popis(MODL_PREDPOLUDNIM, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%s", anchor, ANCHOR_POPIS);\
	_set_popis(MODL_NAPOLUDNIE, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%s", anchor, ANCHOR_POPIS);\
	_set_popis(MODL_POPOLUDNI, _file, _anchor);\
	set_LOG_litobd;\
}

// invitatórium použiteľné pre _bohorod, _krkrala, _krst... a pod.
#define _vlastne_slavenie_invitat(anchor) {\
	sprintf(_anchor, "%s_%c%s", anchor, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

#define _vlastne_slavenie_kresponz(vlastny_anchor) {\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

// antifóny pre modlitbu cez deň sú rovnaké, použitý anchor ANCHOR_ANTIFONY
#define _vlastne_slavenie_antifony(vlastny_anchor) {\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), (je_modlitba_cez_den(modlitba))? ANCHOR_ANTIFONY : ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), (je_modlitba_cez_den(modlitba))? ANCHOR_ANTIFONY : ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), (je_modlitba_cez_den(modlitba))? ANCHOR_ANTIFONY : ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

#define _vlastne_slavenie_modlitba(vlastny_anchor) {\
	sprintf(_anchor, "%s_%s", vlastny_anchor, ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

#define _vlastne_slavenie_modlitba_mcd(vlastny_anchor) {\
	sprintf(_anchor, "%s_%s", vlastny_anchor, ANCHOR_MODLITBA);\
	_set_modlitba(MODL_PREDPOLUDNIM, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%s", vlastny_anchor, ANCHOR_MODLITBA);\
	_set_modlitba(MODL_NAPOLUDNIE, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%s", vlastny_anchor, ANCHOR_MODLITBA);\
	_set_modlitba(MODL_POPOLUDNI, _file, _anchor);\
	set_LOG_litobd;\
}

#define _vlastne_slavenie_kcitanie(vlastny_anchor) {\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

#define _vlastne_slavenie_1citanie(vlastny_anchor) {\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_CITANIE1);\
	_set_citanie1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

#define _vlastne_slavenie_2citanie(vlastny_anchor) {\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_CITANIE2);\
	_set_citanie2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

#define _vlastne_slavenie_ine_1citanie(vlastny_anchor) {\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_CITANIE1);\
	_set_citanie1(modlitba, _file_pc, _anchor);\
	set_LOG_litobd_pc;\
}

#define _vlastne_slavenie_ine_2citanie(vlastny_anchor) {\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_CITANIE2);\
	_set_citanie2(modlitba, _file_pc, _anchor);\
	set_LOG_litobd_pc;\
}

#define _vlastne_slavenie_magnifikat(vlastny_anchor) {\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

#define _vlastne_slavenie_prosby(vlastny_anchor) {\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_PROSBY);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

#define _vlastne_slavenie_benediktus(vlastny_anchor) {\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

/* ------------------------------------------------------------------------------------------- */

// hymnus | pre Cezročné obdobie treba zrušiť možnosť brať alternatívy hymnov (posv. čítanie, I. resp. II.)
#define _vlastna_cast_hymnus(modlitba, litobd) {\
	_set_hymnus_alternativy_NO(modlitba, litobd);\
	sprintf(_anchor, "%s%s%c%s", _special_anchor_prefix, _anchor_head, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_hymnus(modlitba, _file_pc, _anchor);\
		}\
		else{\
		_set_hymnus(modlitba, _file, _anchor);\
	}\
	set_LOG_svsv;}

// hymnus (napr. pre posv. čítanie) ako na vešpery
#define _vlastna_cast_hymnus_ako_na_vespery(modlitba, litobd) {\
	_set_hymnus_alternativy_NO(modlitba, litobd);\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(MODL_VESPERY), ANCHOR_HYMNUS); \
	_set_hymnus(modlitba, _file, _anchor); \
	set_LOG_svsv;}

// hymnus (napr. pre posv. čítanie) ako na ranné chvály
#define _vlastna_cast_hymnus_ako_na_rchvaly(modlitba, litobd) {\
	_set_hymnus_alternativy_NO(modlitba, litobd);\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(MODL_RANNE_CHVALY), ANCHOR_HYMNUS); \
	_set_hymnus(modlitba, _file, _anchor); \
	set_LOG_svsv;}

// antifóny
#define _vlastna_cast_antifony {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	if(modlitba == MODL_POSV_CITANIE){_set_antifona1(modlitba, _file_pc, _anchor);}\
		else{_set_antifona1(modlitba, _file, _anchor);}\
	set_LOG_svsv;\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	if(modlitba == MODL_POSV_CITANIE){_set_antifona2(modlitba, _file_pc, _anchor);}\
		else{_set_antifona2(modlitba, _file, _anchor);}\
	set_LOG_svsv;\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	if(modlitba == MODL_POSV_CITANIE){_set_antifona3(modlitba, _file_pc, _anchor);}\
		else{_set_antifona3(modlitba, _file, _anchor);}\
	set_LOG_svsv;}

// vlastná antifóna pre invitatórium
#define _vlastna_cast_antifona_inv {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	if(modlitba == MODL_POSV_CITANIE){_set_antifona1(modlitba, _file_pc, _anchor);}\
		else{_set_antifona1(modlitba, _file, _anchor);}\
	set_LOG_svsv;}

#define _vlastna_cast_antifony_rovnake {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	if(modlitba == MODL_POSV_CITANIE){_set_antifona1(modlitba, _file_pc, _anchor);}\
		else{_set_antifona1(modlitba, _file, _anchor);}\
	set_LOG_svsv;\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	if(modlitba == MODL_POSV_CITANIE){_set_antifona2(modlitba, _file_pc, _anchor);}\
		else{_set_antifona2(modlitba, _file, _anchor);}\
	set_LOG_svsv;\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	if(modlitba == MODL_POSV_CITANIE){_set_antifona3(modlitba, _file_pc, _anchor);}\
		else{_set_antifona3(modlitba, _file, _anchor);}\
	set_LOG_svsv;}

// krátke čítanie
#define _vlastna_cast_kcitanie {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_svsv;}

// krátke responzórium
#define _vlastna_cast_kresponz {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	if(modlitba == MODL_POSV_CITANIE){_set_kresponz(modlitba, _file_pc, _anchor);}\
		else{_set_kresponz(modlitba, _file, _anchor);}\
	set_LOG_svsv;}

// benediktus
#define _vlastna_cast_benediktus {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_svsv;}

// magnifikat
#define _vlastna_cast_magnifikat {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_svsv;}

// nunc dimittis
#define _vlastna_cast_nunc_dimittis {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_NUNC_DIMITTIS);\
	_set_nunc_dimittis(modlitba, _file, _anchor);\
	set_LOG_svsv;}

// prosby
#define _vlastna_cast_prosby {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_PROSBY);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_svsv;}

// modlitba -- rovnaka rano i vecer
#define _vlastna_cast_modlitba {\
	sprintf(_anchor, "%s%s", _anchor_head, ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_svsv;}

// modlitba -- niekedy môže byť iná napr. pre prvé vešpery (odlišná od modlitby pre ranné chvály a vešpery), niekedy odlišná pre ranné chvály a vešpery
#define _vlastna_cast_modlitba_ina {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_svsv;}

// benediktus -- na spomienku svätca v pôste
#define _vlastna_cast_benediktus_spomprivileg {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS);\
	_set_ant_spomprivileg(modlitba, _file, _anchor);\
	set_LOG_svsv;}

// magnifikat -- na spomienku svätca v pôste
#define _vlastna_cast_magnifikat_spomprivileg {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT);\
	_set_ant_spomprivileg(modlitba, _file, _anchor);\
	set_LOG_svsv;}

// modlitba -- na spomienku svätca v pôste
#define _vlastna_cast_modlitba_spomprivileg {\
	sprintf(_anchor, "%s%s", _anchor_head, ANCHOR_MODLITBA);\
	_set_modlitba_spomprivileg(modlitba, _file, _anchor);\
	set_LOG_svsv;}

// modlitba -- na spomienku svätca v pôste (ak je odlišná modlitba pre ranné chvály a vešpery)
#define _vlastna_cast_modlitba_spomprivileg_ina {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_MODLITBA);\
	_set_modlitba_spomprivileg(modlitba, _file, _anchor);\
	set_LOG_svsv;}

// posvätné čítanie (2. hagiografické čítanie) -- na spomienku svätca v pôste
#define _vlastna_cast_2citanie_spomprivileg {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_CITANIE2);\
	_set_2citanie_spomprivileg(modlitba, _file_pc, _anchor);\
	set_LOG_svsv;}

// 1. čítanie
#define _vlastna_cast_1citanie {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_CITANIE1);\
	_set_citanie1(modlitba, _file_pc, _anchor);\
	set_LOG_svsv;\
}

// 2. čítanie
#define _vlastna_cast_2citanie {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_CITANIE2);\
	_set_citanie2(modlitba, _file_pc, _anchor);\
	set_LOG_svsv;\
}

// full -- vsetko (hymnus, antifony, kcitanie, kresponz, benediktus/magnifikat, prosby, modlitba
#define _vlastna_cast_full(modl) {\
	Log("_vlastna_cast_full()...\n");\
	_vlastna_cast_hymnus(modl, _global_den.litobd);\
	_vlastna_cast_antifony;\
	if(modl == MODL_POSV_CITANIE){_vlastna_cast_1citanie;}\
	else {_vlastna_cast_kcitanie;}\
	_vlastna_cast_kresponz;\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	else if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_prosby;\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_full_okrem_antifon(modl) {\
	Log("_vlastna_cast_full_okrem_antifon()...\n");\
	_vlastna_cast_hymnus(modl, _global_den.litobd);\
	if(modl == MODL_POSV_CITANIE){_vlastna_cast_1citanie;}\
	else {_vlastna_cast_kcitanie;}\
	_vlastna_cast_kresponz;\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	else if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_prosby;\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_full_okrem_prosieb(modl) {\
	Log("_vlastna_cast_full_okrem_prosieb()...\n");\
	_vlastna_cast_hymnus(modl, _global_den.litobd);\
	_vlastna_cast_antifony;\
	if(modl == MODL_POSV_CITANIE){_vlastna_cast_1citanie;}\
	else {_vlastna_cast_kcitanie;}\
	_vlastna_cast_kresponz;\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	else if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_full_okrem_benmagn_a_prosieb(modl) {\
	Log("_vlastna_cast_full_okrem_benmagn_a_prosieb()...\n");\
	_vlastna_cast_hymnus(modl, _global_den.litobd);\
	_vlastna_cast_antifony;\
	if(modl == MODL_POSV_CITANIE){_vlastna_cast_1citanie;}\
	else {_vlastna_cast_kcitanie;}\
	_vlastna_cast_kresponz;\
	if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_full_okrem_kresp_benmagn_a_prosieb(modl) {\
	Log("_vlastna_cast_full_okrem_kresp_benmagn_a_prosieb()...\n");\
	_vlastna_cast_hymnus(modl, _global_den.litobd);\
	_vlastna_cast_antifony;\
	if(modl == MODL_POSV_CITANIE){_vlastna_cast_1citanie;}\
	else {_vlastna_cast_kcitanie;}\
	if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_full_okrem_hymnu_a_prosieb(modl) {\
	Log("_vlastna_cast_full_okrem_hymnu_a_prosieb()...\n");\
	_vlastna_cast_antifony;\
	if(modl == MODL_POSV_CITANIE){_vlastna_cast_1citanie;}\
	else {_vlastna_cast_kcitanie;}\
	_vlastna_cast_kresponz;\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	else if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_full_okrem_hymnu(modl) {\
	Log("_vlastna_cast_full_okrem_hymnu()...\n");\
	_vlastna_cast_antifony;\
	if(modl == MODL_POSV_CITANIE){_vlastna_cast_1citanie;}\
	else {_vlastna_cast_kcitanie;}\
	_vlastna_cast_kresponz;\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	else if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_prosby;\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_full_okrem_hymnu_kresp_a_prosieb(modl) {\
	Log("_vlastna_cast_full_okrem_hymnu_kresp_a_prosieb()...\n");\
	_vlastna_cast_antifony;\
	if(modl == MODL_POSV_CITANIE){_vlastna_cast_1citanie;}\
	else {_vlastna_cast_kcitanie;}\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	else if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_full_okrem_antifon_a_prosieb(modl) {\
	Log("_vlastna_cast_full_okrem_antifon_a_prosieb()...\n");\
	_vlastna_cast_hymnus(modl, _global_den.litobd);\
	if(modl == MODL_POSV_CITANIE){_vlastna_cast_1citanie;}\
	else {_vlastna_cast_kcitanie;}\
	_vlastna_cast_kresponz;\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	else if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_full_okrem_antifon_a_kcit_kresp(modl) {\
	Log("_vlastna_cast_full_okrem_antifon_a_kcit_kresp()...\n");\
	_vlastna_cast_hymnus(modl, _global_den.litobd);\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	else if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_prosby;\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_full_okrem_hymnu_antifon_a_prosieb(modl) {\
	Log("_vlastna_cast_full_okrem_hymnu_antifon_a_prosieb()...\n");\
	if(modl == MODL_POSV_CITANIE){_vlastna_cast_1citanie;}\
	else {_vlastna_cast_kcitanie;}\
	_vlastna_cast_kresponz;\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	else if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_full_okrem_hymnu_a_antifon(modl) {\
	Log("_vlastna_cast_full_okrem_hymnu_a_antifon()...\n");\
	if(modl == MODL_POSV_CITANIE){_vlastna_cast_1citanie;}\
	else {_vlastna_cast_kcitanie;}\
	_vlastna_cast_kresponz;\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	else if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_prosby;\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_full_okrem_hymnu_antifon_a_benmagn(modl) {\
	Log("_vlastna_cast_full_okrem_hymnu_antifon_a_benmagn()...\n");\
	if(modl == MODL_POSV_CITANIE){_vlastna_cast_1citanie;}\
	else {_vlastna_cast_kcitanie;}\
	_vlastna_cast_kresponz;\
	if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_prosby;\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_full_okrem_hymnu_a_kcit_kresp(modl) {\
	Log("_vlastna_cast_full_okrem_hymnu_a_kcit_kresp()...\n");\
	_vlastna_cast_antifony;\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	else if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_prosby;\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_full_okrem_hymnu_a_kresp(modl) {\
	Log("_vlastna_cast_full_okrem_hymnu_a_kresp()...\n");\
	_vlastna_cast_antifony;\
	if(modl == MODL_POSV_CITANIE){_vlastna_cast_1citanie;}\
	else {_vlastna_cast_kcitanie;}\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	else if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_prosby;\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_full_okrem_kresp(modl) {\
	Log("_vlastna_cast_full_okrem_kresp()...\n");\
	_vlastna_cast_hymnus(modl, _global_den.litobd);\
	_vlastna_cast_antifony;\
	if(modl == MODL_POSV_CITANIE){_vlastna_cast_1citanie;}\
	else {_vlastna_cast_kcitanie;}\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	else if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_prosby;\
	_vlastna_cast_modlitba;\
}

// _vlastna_cast_full_okrem_kcit == _vlastna_cast_full_okrem_1cit pre MODL_POSV_CITANIE
#define _vlastna_cast_full_okrem_kcit(modl) {\
	Log("_vlastna_cast_full_okrem_kcit()...\n");\
	_vlastna_cast_hymnus(modl, _global_den.litobd);\
	_vlastna_cast_antifony;\
	_vlastna_cast_kresponz;\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	else if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_prosby;\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_full_okrem_kresp_a_prosieb(modl) {\
	Log("_vlastna_cast_full_okrem_kresp_a_prosieb()...\n");\
	_vlastna_cast_hymnus(modl, _global_den.litobd);\
	_vlastna_cast_antifony;\
	if(modl == MODL_POSV_CITANIE){_vlastna_cast_1citanie;}\
	else {_vlastna_cast_kcitanie;}\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	else if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_full_okrem_kcit_kresp_a_prosieb(modl) {\
	Log("_vlastna_cast_full_okrem_kcit_kresp_a_prosieb()...\n");\
	_vlastna_cast_hymnus(modl, _global_den.litobd);\
	_vlastna_cast_antifony;\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	else if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_full_okrem_kcit_kresp(modl) {\
	Log("_vlastna_cast_full_okrem_kcit_kresp()...\n");\
	_vlastna_cast_hymnus(modl, _global_den.litobd);\
	_vlastna_cast_antifony;\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	else if(modl == MODL_POSV_CITANIE){_vlastna_cast_2citanie;}\
	_vlastna_cast_prosby;\
	_vlastna_cast_modlitba;\
}

// full -- vsetko (hymnus, antifony, kcitanie, kresponz, benediktus/magnifikat, prosby, modlitba -- ina ako na rchv a vesp
#define _vlastna_cast_antifony_ako_na_ranne_chvaly {\
	Log("_vlastna_cast_antifony_ako_na_ranne_chvaly...\n");\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(MODL_RANNE_CHVALY), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_svsv;\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(MODL_RANNE_CHVALY), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_svsv;\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(MODL_RANNE_CHVALY), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_svsv;\
}

// rovnako tak pre spolocnu cast...
#define _spolocna_cast_kcitanie(modl)		if((je_modlitba_cez_den(modl) && su_kcit_kresp_modlitba_mcd_vlastne(modl)) || su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modl) || ((force & FORCE_BRAT_KCIT_1CIT) == FORCE_BRAT_KCIT_1CIT)){ _vlastna_cast_kcitanie; }
#define _spolocna_cast_benediktus(modl)		if(su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modl) || ((force & FORCE_BRAT_ANTIFONY_B_M) == FORCE_BRAT_ANTIFONY_B_M)){ _vlastna_cast_benediktus; }
#define _spolocna_cast_magnifikat(modl)		if(su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modl) || ((force & FORCE_BRAT_ANTIFONY_B_M) == FORCE_BRAT_ANTIFONY_B_M)){ _vlastna_cast_magnifikat; }
#define _spolocna_cast_prosby(modl)			if(su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modl) || ((force & FORCE_BRAT_PROSBY) == FORCE_BRAT_PROSBY)){ _vlastna_cast_prosby; }

#define _spolocna_cast_modlitba			_vlastna_cast_modlitba

// ... az na antifony... | removed condition: if((_global_opt[OPT_3_SPOLOCNA_CAST] != MODL_SPOL_CAST_NEBRAT)){...}
#define _spolocna_cast_antifony {\
	Log("  antifony vlastnej casti zo sviatku...\n");\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), (je_modlitba_cez_den(modlitba))? ANCHOR_ANTIFONY : ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_svsv;\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), (je_modlitba_cez_den(modlitba))? ANCHOR_ANTIFONY : ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_svsv;\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), (je_modlitba_cez_den(modlitba))? ANCHOR_ANTIFONY : ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_svsv;\
}

#define	_spolocna_cast_antifona_inv(m) {\
	if(su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(m) || ((force & FORCE_BRAT_ANTIFONY_INV) == FORCE_BRAT_ANTIFONY_INV)){\
		_vlastna_cast_antifona_inv;\
	}\
}

// 1. čítanie
#define _spolocna_cast_1citanie {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_CITANIE1);\
	_set_citanie1(modlitba, _file, _anchor);\
	set_LOG_svsv;\
}

// 2. čítanie
#define _spolocna_cast_2citanie {\
	if (su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(MODL_POSV_CITANIE) || ((force & FORCE_BRAT_2CITANIE) == FORCE_BRAT_2CITANIE)){\
		Log("_spolocna_cast_2citanie(%s)...\n", nazov_modlitby(MODL_POSV_CITANIE));\
		sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(MODL_POSV_CITANIE), ANCHOR_CITANIE2);\
		_set_citanie2(modlitba, _file, _anchor);\
		set_LOG_svsv;\
	}\
}

#define __skus_zohladnit_set_zalmy_mcd_doplnkova_psalmodia_alternativy(modl) {\
	Log("idem skúsiť zohľadniť _set_zalmy_mcd_doplnkova_psalmodia_alternativy(%s)\n", nazov_modlitby(modl));\
	if(isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA)){\
		_set_zalmy_mcd_doplnkova_psalmodia_alternativy(modlitba);\
	}\
}

// ... a spolocnu cast full 
// pre posv. čítanie sa responz medzi psalmódiou a 1. čítaním berie len v prípade, že sa berie vlastné 1. čítanie
// modlitba cez deň - modlitba sa použije zo spoločnej časti len pre slávnosti a sviatky (ináč sa MCD berie zo dňa, bod č. 236 všeobecných smerníc)
// zohľadnenie bodov 229, 232, 236 VSLH
// pre doplnkovú psalmódiu treba prípadne ponastavovať odlišné žalmy (Ž 129 resp. Ž 131 namiesto Ž 122, 126 resp. 127), pretože žalmy sa pre slávenia s nižšou prioritou nastavujú zo žaltára; doplnková psalmódia sa preto nastavuje prv, ako sa nastavilo je_alternativa_doplnkova_psalmodia_z...()
#define _spolocna_cast_full(modl) {\
	Log("_spolocna_cast_full(%s): začiatok...\n", nazov_modlitby(modl));\
	Log("_global_poradie_svaty = %d\n", _global_poradie_svaty);\
	Log("force = %d\n", force);\
	Log("_global_den.typslav = %d\n", _global_den.typslav);\
	for(short int i = 0; i < MAX_POCET_SVATY; i++){\
		Log("_global_svaty(%d).typslav = %d\n", i + 1, _global_svaty(i + 1).typslav);\
	}\
	if(!(je_modlitba_cez_den(modl))){\
		_spolocna_cast_hymnus(modl, _global_den.litobd);\
	}\
	if(su_antifony_vlastne(modl) || ((force & FORCE_BRAT_ANTIFONY) == FORCE_BRAT_ANTIFONY)){\
		Log("_spolocna_cast_antifony(%s)\n", nazov_modlitby(modl));\
		_spolocna_cast_antifony;\
	}\
	else if(je_modlitba_cez_den(modl)){\
		Log("_spolocna_cast_antifony(%s) - MCD...\n", nazov_modlitby(modl));\
		if(su_antifony_vlastne(modl) || ((force & FORCE_BRAT_ANTIFONY_MCD) == FORCE_BRAT_ANTIFONY_MCD)){\
			_spolocna_cast_antifony;\
		}\
	}\
	else {\
		Log("_spolocna_cast_antifony(%s) - NEBERÚ SA!\n", nazov_modlitby(modl));\
	}\
	if(je_modlitba_cez_den(modl)){\
		__skus_zohladnit_set_zalmy_mcd_doplnkova_psalmodia_alternativy(modl);\
		_spolocna_cast_kresponz;\
		_spolocna_cast_kcitanie(modl);\
	}\
	else{\
		if(modl != MODL_POSV_CITANIE){\
			_spolocna_cast_kcitanie(modl);\
			_spolocna_cast_kresponz;\
		}\
		if((modl == MODL_RANNE_CHVALY) || (modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){\
			_spolocna_cast_prosby(modl);\
		}\
	}\
	if(((je_1cit_vlastne(modl)) || ((force & FORCE_BRAT_KCIT_1CIT) == FORCE_BRAT_KCIT_1CIT)) && (modl == MODL_POSV_CITANIE)){\
		_spolocna_cast_kresponz;\
		_spolocna_cast_1citanie;\
	}\
	if(modl == MODL_RANNE_CHVALY){\
		_spolocna_cast_benediktus(modl);\
	}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){\
		_spolocna_cast_magnifikat(modl);\
	}\
	else if(modl == MODL_POSV_CITANIE){\
		_spolocna_cast_2citanie;\
	}\
	if(je_modlitba_cez_den(modl)){\
		if(su_kcit_kresp_modlitba_mcd_vlastne(modl) || ((force & FORCE_BRAT_MODLITBA) == FORCE_BRAT_MODLITBA)){\
			_vlastna_cast_modlitba;\
		}\
	}\
	else{\
		_vlastna_cast_modlitba;\
	}\
	Log("_spolocna_cast_full(%s): koniec.\n", nazov_modlitby(modl));\
}
// _spolocna_cast_full()

// kratke responzorium
#define _spolocna_cast_kresponz {\
	if ((je_modlitba_cez_den(modlitba) && su_kcit_kresp_modlitba_mcd_vlastne(modlitba)) || su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modlitba) || ((force & FORCE_BRAT_KRESP) == FORCE_BRAT_KRESP)){\
		sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
		_set_kresponz(modlitba, _file, _anchor);\
		set_LOG_svsv;\
	}\
}

// pre Cezročné obdobie treba zrušiť možnosť brať alternatívy hymnov (posv. čítanie, I. resp. II.)
// pridané FORCE_BRAT_HYMNUS
// doplnené podmienky su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne()
#define _spolocna_cast_hymnus(modlitba, litobd) {\
	if(su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modlitba) || ((force & FORCE_BRAT_HYMNUS) == FORCE_BRAT_HYMNUS)){\
		_set_hymnus_alternativy_NO(modlitba, litobd);\
		sprintf(_anchor, "%s%s%c%s", _special_anchor_prefix, _anchor_head, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
		_set_hymnus(modlitba, _file, _anchor);\
		set_LOG_svsv;\
	}\
}

#define _spolocna_cast_hymnus_po {\
	if(su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modlitba) || ((force & FORCE_BRAT_HYMNUS) == FORCE_BRAT_HYMNUS)){\
		sprintf(_anchor, "%s%s%c%s%s", _special_anchor_prefix, _anchor_head, pismenko_modlitby(modlitba), ANCHOR_HYMNUS, POSTNA_PRIPONA);\
		_set_hymnus(modlitba, _file, _anchor);\
		set_LOG_svsv;\
	}\
}

#define _spolocna_cast_hymnus_ve {\
	if(su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modlitba) || ((force & FORCE_BRAT_HYMNUS) == FORCE_BRAT_HYMNUS)){\
		sprintf(_anchor, "%s%s%c%s%s", _special_anchor_prefix, _anchor_head, pismenko_modlitby(modlitba), ANCHOR_HYMNUS, VELKONOCNA_PRIPONA);\
		_set_hymnus(modlitba, _file, _anchor);\
		set_LOG_svsv;\
	}\
}

#define _spolocna_cast_benediktus_ve {\
	if(su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modlitba) || ((force & FORCE_BRAT_ANTIFONY_B_M) == FORCE_BRAT_ANTIFONY_B_M)){\
		sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, VELKONOCNA_PRIPONA);\
		_set_benediktus(modlitba, _file, _anchor);\
		set_LOG_svsv;\
	}\
}

#define _spolocna_cast_magnifikat_ve {\
	if(su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modlitba) || ((force & FORCE_BRAT_ANTIFONY_B_M) == FORCE_BRAT_ANTIFONY_B_M)){\
		sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, VELKONOCNA_PRIPONA);\
		_set_magnifikat(modlitba, _file, _anchor);\
		set_LOG_svsv;\
	}\
}

// použité pre spoločnú časť jednoho mučeníka/mučenice a viacerých mučeníkov, MCD
#define _spolocna_cast_kcit_ve {\
	if((je_modlitba_cez_den(modlitba) && su_kcit_kresp_modlitba_mcd_vlastne(modlitba)) || su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modlitba) || ((force & FORCE_BRAT_KCIT_1CIT) == FORCE_BRAT_KCIT_1CIT)){\
		sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_KCITANIE, VELKONOCNA_PRIPONA);\
		_set_kcitanie(modlitba, _file, _anchor);\
		set_LOG_svsv;\
	}\
}

// specialne veci pre sviatky panien (aj pre sväté ženy a pre jednoho mučeníka na MCD)
#define _spolocna_cast_kresp_ve {\
	if((je_modlitba_cez_den(modlitba) && su_kcit_kresp_modlitba_mcd_vlastne(modlitba)) || su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modlitba) || ((force & FORCE_BRAT_KCIT_1CIT) == FORCE_BRAT_KCIT_1CIT)){\
		sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ, VELKONOCNA_PRIPONA);\
		_set_kresponz(modlitba, _file, _anchor);\
		set_LOG_svsv;\
	}\
}

// specialne veci pre sviatky jedneho mucenika
#define _spolocna_cast_kcit_kresp_chval_ve {\
	if(su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modlitba) || ((force & FORCE_BRAT_KCIT_1CIT) == FORCE_BRAT_KCIT_1CIT)){\
		sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_KCITANIE, VELKONOCNA_PRIPONA);\
		_set_kcitanie(modlitba, _file, _anchor);\
		set_LOG_svsv;\
	}\
	if(su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modlitba) || ((force & FORCE_BRAT_KRESP) == FORCE_BRAT_KRESP)){\
		sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ, VELKONOCNA_PRIPONA);\
		_set_kresponz(modlitba, _file, _anchor);\
		set_LOG_svsv;\
	}\
	if(su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modlitba) || ((force & FORCE_BRAT_ANTIFONY_B_M) == FORCE_BRAT_ANTIFONY_B_M)){\
		if(modlitba == MODL_RANNE_CHVALY){\
			sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, VELKONOCNA_PRIPONA);\
			_set_benediktus(modlitba, _file, _anchor);\
			set_LOG_svsv;\
		}\
		else if((modlitba == MODL_VESPERY) || (modlitba == MODL_PRVE_VESPERY)){\
			sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, VELKONOCNA_PRIPONA);\
			_set_magnifikat(modlitba, _file, _anchor);\
			set_LOG_svsv;\
		}\
	}\
}

#define _spolocna_cast_ant1_3_po {\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1, POSTNA_PRIPONA);\
	_set_antifona1(modlitba, _file, _anchor);\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3, POSTNA_PRIPONA);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_svsv;\
}

#define _spolocna_cast_ant_iba_3_po {\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3, POSTNA_PRIPONA);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_svsv;\
}

// specialne veci pre sviatky viacerych mucenikov
#define _spolocna_cast_ant2_po {\
	if(su_antifony_vlastne(modlitba) || ((force & FORCE_BRAT_ANTIFONY) == FORCE_BRAT_ANTIFONY)){\
		sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2, POSTNA_PRIPONA);\
		_set_antifona2(modlitba, _file, _anchor);\
		set_LOG_svsv;\
	}\
}

/* ---------------------------------------------------------------------------------------------------- */

#define _spolocna_cast_set_vig_ant_sm_sz() { \
	sprintf(_anchor, "%s_%c%s", nazov_spolc_ANCHOR[MODL_SPOL_CAST_SV_MUZ], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA_VIG); \
	_set_antifona_vig(modlitba, nazov_spolc_htm[MODL_SPOL_CAST_SV_MUZ], _anchor); \
	set_LOG_litobd_pc; \
}

#define _spolocna_cast_set_vig_ev_sm_sz() { \
	sprintf(_anchor, "%s_%c%s", nazov_spolc_ANCHOR[MODL_SPOL_CAST_SV_MUZ], pismenko_modlitby(modlitba), ANCHOR_EVANJELIUM); \
	_set_evanjelium(modlitba, nazov_spolc_htm[MODL_SPOL_CAST_SV_MUZ], _anchor); \
	set_LOG_litobd_pc; \
}

#define _spolocna_cast_set_vig_ev_jm_vm() { \
	sprintf(_anchor, "%s_%c%s", ANCHOR_SPOL_CAST_JEDEN_MUCENIK, pismenko_modlitby(modlitba), ANCHOR_EVANJELIUM); \
	_set_evanjelium(modlitba, nazov_spolc_htm[MODL_SPOL_CAST_MUCENIK], _anchor); \
	set_LOG_litobd_pc; \
}

#define _spolocna_cast_set_vig_ev_dp() { \
	sprintf(_anchor, "%s_%c%s", ANCHOR_SPOL_CAST_DUCH_PAST, pismenko_modlitby(modlitba), ANCHOR_EVANJELIUM); \
	_set_evanjelium(modlitba, nazov_spolc_htm[MODL_SPOL_CAST_DUCH_PAST_KNAZ], _anchor); \
	set_LOG_litobd_pc; \
}

#define _spolocna_cast_set_vig_ev_pm() { \
	sprintf(_anchor, "%s_%c%s", nazov_spolc_ANCHOR[MODL_SPOL_CAST_PANNA_MARIA], pismenko_modlitby(modlitba), ANCHOR_EVANJELIUM); \
	_set_evanjelium(modlitba, nazov_spolc_htm[MODL_SPOL_CAST_PANNA_MARIA], _anchor); \
	set_LOG_litobd_pc; \
}

#define _spolocna_cast_set_vig_ev_uc() { \
	sprintf(_anchor, "%s_%c%s", nazov_spolc_ANCHOR[MODL_SPOL_CAST_UCITEL_CIRKVI], pismenko_modlitby(modlitba), ANCHOR_EVANJELIUM); \
	_set_evanjelium(modlitba, nazov_spolc_htm[MODL_SPOL_CAST_UCITEL_CIRKVI], _anchor); \
	set_LOG_litobd_pc; \
}

// _anchor_head pre spoločné časti obsahuje už aj underscore; spoločné časti používajú súbor _file (nie _file_pc)
#define _spolocna_cast_set_vig_ant(vlastny_anchor) { \
	sprintf(_anchor, "%s%c%s", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA_VIG); \
	_set_antifona_vig(modlitba, _file, _anchor); \
	set_LOG_litobd_pc; \
}

#define _spolocna_cast_set_vig_ev(vlastny_anchor) { \
	sprintf(_anchor, "%s%c%s", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_EVANJELIUM); \
	_set_evanjelium(modlitba, _file, _anchor); \
	set_LOG_litobd_pc; \
}

// tak isto aj _anchor_head pre vlastné slávenie sviatkov svätých (kalendar.cpp) obsahuje underscore
#define _vlastna_cast_vig_ant(_anchor_head) { \
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA_VIG); \
	_set_antifona_vig(modlitba, _file_pc, _anchor); \
	set_LOG_litobd_pc; \
}

#define _vlastna_cast_vig_ev(_anchor_head) { \
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_EVANJELIUM); \
	_set_evanjelium(modlitba, _file_pc, _anchor); \
	set_LOG_litobd_pc; \
}

#define _vlastne_slavenie_set_vig_ant(vlastny_anchor) { \
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA_VIG); \
	_set_antifona_vig(modlitba, _file_pc, _anchor); \
	set_LOG_litobd_pc; \
}

#define _vlastne_slavenie_set_vig_ev(vlastny_anchor) { \
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_EVANJELIUM); \
	_set_evanjelium(modlitba, _file_pc, _anchor); \
	set_LOG_litobd_pc; \
}

#define _vlastne_slavenie_set_vig_ev_litrok(vlastny_anchor, litrok) { \
	sprintf(_anchor, "%s_%c%s%c", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_EVANJELIUM, litrok); \
	_set_evanjelium(modlitba, _file_pc, _anchor); \
	set_LOG_litobd_pc; \
}

#define _liturgicke_obdobie_set_vig_ant(modlitba) { \
	sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA_VIG); \
	_set_antifona_vig(modlitba, _file_pc, _anchor); \
	set_LOG_litobd_pc; \
}

#define _liturgicke_obdobie_set_vig_ev(modlitba) { \
	sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_EVANJELIUM); \
	_set_evanjelium(modlitba, _file_pc, _anchor); \
	set_LOG_litobd_pc; \
}

// 1., 2. a 3. Adventná nedeľa = 3., 4. a 5. Cezročná nedeľa
// 4. Adventná nedeľa = 6. Cezročná nedeľa
// Pôstne obdobie má svoje čítania
// 2., 3., 4., 5., 6. a 7. Veľkonočná nedeľa = 2., 3., 4., 5., 6. a 7. Cezročná nedeľa
#define _liturgicke_obdobie_set_vig_ev_tyzden(modlitba, tyzden) { \
	sprintf(_anchor, "%s%d_%c%s", ((litobd != OBD_POSTNE_I) ? nazov_OBD[OBD_CEZ_ROK] : nazov_OBD[litobd]), \
		((litobd == OBD_ADVENTNE_I) || (litobd == OBD_ADVENTNE_II)) ? tyzden + 2 : tyzden, pismenko_modlitby(modlitba), ANCHOR_EVANJELIUM); \
	_set_evanjelium(modlitba, ((litobd == OBD_POSTNE_I) ? _file_pc : nazov_obd_htm_pc[OBD_CEZ_ROK]), _anchor); \
	set_LOG_litobd_pc; \
}

/* ---------------------------------------------------------------------------------------------------- */

#define _set_antifony_velk_pc(den, tyzzal, modlitba) {\
	/* 1. antifona */\
	file_name_litobd_pc(OBD_CEZ_ROK);\
	anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA1V);\
	_set_antifona1(modlitba, _file_pc, _anchor);\
	set_LOG_litobd_pc;\
	/* 2. antifona */\
	file_name_litobd_pc(OBD_CEZ_ROK);\
	anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA2V);\
	_set_antifona2(modlitba, _file_pc, _anchor);\
	set_LOG_litobd_pc;\
	/* 3. antifona */\
	file_name_litobd_pc(OBD_CEZ_ROK);\
	anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA3V);\
	_set_antifona3(modlitba, _file_pc, _anchor);\
	set_LOG_litobd_pc;\
}

#define je_odlisny_zaltar ((zvazok == 1) || (zvazok == 2))

/* ---------------------------------------------------------------------------------------------------- */

// krátke čítanie, krátke responzórium, príp. responzórium a 1. čítanie pre modlitbu posv. čítania
#define _vlastna_cast_kcitanie_ve {\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_KCITANIE, VELKONOCNA_PRIPONA);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_svsv;}

#define _vlastna_cast_kresponz_ve {\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ, VELKONOCNA_PRIPONA);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_svsv;\
}

#define _vlastna_cast_kresponz_po {\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ, POSTNA_PRIPONA);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_svsv;\
}

#define _vlastna_cast_kresponz_po_ve {\
	if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {\
		_vlastna_cast_kresponz_ve;\
	}\
	else if ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)) {\
		_vlastna_cast_kresponz_po;\
	}\
}

#define _vlastna_cast_kresponz_ve_obd {\
	if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {\
		_vlastna_cast_kresponz_ve;\
	}\
	else {\
		_vlastna_cast_kresponz;\
	}\
}

#define _vlastna_cast_kcitanie_ve_obd {\
	if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {\
		_vlastna_cast_kcitanie_ve;\
	}\
	else {\
		_vlastna_cast_kcitanie;\
	}\
}

#define _vlastna_cast_1citanie_ve {\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_CITANIE1, VELKONOCNA_PRIPONA);\
	_set_citanie1(modlitba, _file_pc, _anchor);\
	set_LOG_svsv;\
}

#define _vlastna_cast_1citanie_ve_obd {\
	if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {\
		_vlastna_cast_1citanie_ve;\
	}\
	else {\
		_vlastna_cast_1citanie;\
	}\
}

// vlastná časť -- modlitba cez deň
#define _vlastna_cast_mcd_ant_kcitresp_modl {\
	modlitba = MODL_PREDPOLUDNIM;\
	_vlastna_cast_antifony_rovnake;\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
	modlitba = MODL_NAPOLUDNIE;\
	_vlastna_cast_antifony_rovnake;\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
	modlitba = MODL_POPOLUDNI;\
	_vlastna_cast_antifony_rovnake;\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_mcd_ant_modl {\
	modlitba = MODL_PREDPOLUDNIM;\
	_vlastna_cast_antifony_rovnake;\
	_vlastna_cast_modlitba;\
	modlitba = MODL_NAPOLUDNIE;\
	_vlastna_cast_antifony_rovnake;\
	_vlastna_cast_modlitba;\
	modlitba = MODL_POPOLUDNI;\
	_vlastna_cast_antifony_rovnake;\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_mcd_full {\
	modlitba = MODL_PREDPOLUDNIM;\
	_vlastna_cast_hymnus(modlitba, _global_den.litobd);\
	_vlastna_cast_antifony_rovnake;\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
	modlitba = MODL_NAPOLUDNIE;\
	_vlastna_cast_hymnus(modlitba, _global_den.litobd);\
	_vlastna_cast_antifony_rovnake;\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
	modlitba = MODL_POPOLUDNI;\
	_vlastna_cast_hymnus(modlitba, _global_den.litobd);\
	_vlastna_cast_antifony_rovnake;\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_mcd_full_okrem_hymnu {\
	modlitba = MODL_PREDPOLUDNIM;\
	_vlastna_cast_antifony_rovnake;\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
	modlitba = MODL_NAPOLUDNIE;\
	_vlastna_cast_antifony_rovnake;\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
	modlitba = MODL_POPOLUDNI;\
	_vlastna_cast_antifony_rovnake;\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_mcd_full_okrem_ant {\
	modlitba = MODL_PREDPOLUDNIM;\
	_vlastna_cast_hymnus(modlitba, _global_den.litobd);\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
	modlitba = MODL_NAPOLUDNIE;\
	_vlastna_cast_hymnus(modlitba, _global_den.litobd);\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
	modlitba = MODL_POPOLUDNI;\
	_vlastna_cast_hymnus(modlitba, _global_den.litobd);\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_mcd_kcitresp_modl {\
	modlitba = MODL_PREDPOLUDNIM;\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
	modlitba = MODL_NAPOLUDNIE;\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
	modlitba = MODL_POPOLUDNI;\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_mcd_kcitresp_modl_predpol {\
	modlitba = MODL_PREDPOLUDNIM;\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_mcd_modlitba {\
	modlitba = MODL_PREDPOLUDNIM;\
	_vlastna_cast_modlitba;\
	modlitba = MODL_NAPOLUDNIE;\
	_vlastna_cast_modlitba;\
	modlitba = MODL_POPOLUDNI;\
	_vlastna_cast_modlitba;\
}

#define _vlastna_cast_mcd_hymnus_kcitresp_modl {\
	modlitba = MODL_PREDPOLUDNIM;\
	_vlastna_cast_hymnus(modlitba, _global_den.litobd);\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
	modlitba = MODL_NAPOLUDNIE;\
	_vlastna_cast_hymnus(modlitba, _global_den.litobd);\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
	modlitba = MODL_POPOLUDNI;\
	_vlastna_cast_hymnus(modlitba, _global_den.litobd);\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	_vlastna_cast_modlitba;\
}

#define _set_spolocna_cast(a, poradie_svaty, force) __set_spolocna_cast(a, poradie_svaty, sc, force)

#define set_LOG_sc Log("          sc == {%s (%d), %s (%d), %s (%d)}\n",	\
	nazov_spolc(sc.a1), sc.a1, \
	nazov_spolc(sc.a2), sc.a2, \
	nazov_spolc(sc.a3), sc.a3); Log

// vlastné druhé čítanie na posvätné čítanie pre srdca PM
#define _srdca_pm_2cit {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_SRDCA_PM, pismenko_modlitby(modlitba), ANCHOR_CITANIE2);\
	_set_citanie2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

/* #define END -------------------------------------------------------------------------------------------------------------------- */

// substring for special cases (even, odd weeks in CZ)
#define CZ_WEEK_EVEN   "SUDY"
#define CZ_WEEK_ODD    "LICHY"

// prefixes for special cases (anchors)
#define CZ_HYMNUS_PREFIX    "CZ_"
#define ALT_TEXT_PREFIX     "VAR_"

// postfixes for special cases (anchors)
#define CZ_HYMNUS_POSTFIX       "_CZ"
#define VELKONOCNA_PRIPONA      "VE"
#define POSTNA_PRIPONA          "PO"
#define CEZROCNA_PRIPONA        "CR"
#define PRINTED_EDITION_POSTFIX "_PRINTED"

// anchor identifiers
#define ANCHOR_POPIS         "POPIS"
#define ANCHOR_HYMNUS        "HYMNUS"
#define ANCHOR_ANTIFONA1     "ANT1"
#define ANCHOR_ANTIFONA2     "ANT2"
#define ANCHOR_ANTIFONA3     "ANT3"
#define ANCHOR_ANTIFONY      "ANTx" // pridané 2007-10-02 pre rovnaké antifóny 1., 2. a 3. - modlitba cez deň
#define ANCHOR_ANTIFONA1V    "ANT1V"
#define ANCHOR_ANTIFONA2V    "ANT2V"
#define ANCHOR_ANTIFONA3V    "ANT3V"
#define ANCHOR_KCITANIE      "CIT"
#define ANCHOR_KRESPONZ      "RESP"
#define ANCHOR_MAGNIFIKAT    "MAGNIFIKAT" // antifóna na Magnifikat
#define ANCHOR_BENEDIKTUS    "BENEDIKTUS" // antifóna na Benediktus
#define ANCHOR_NUNC_DIMITTIS "NUNCDIMITTIS" // antifóna na Nunc dimittis
#define ANCHOR_PROSBY        "PROSBY"
#define ANCHOR_MODLITBA      "MODLITBA"
#define ANCHOR_CITANIE1      "CIT1"
#define ANCHOR_CITANIE2      "CIT2"
#define ANCHOR_ANTIFONA_VIG  "ANTVG"
#define ANCHOR_EVANJELIUM    "EV"
#define ANCHOR_UKON_KAJ      "UKONKAJ" // úkon kajúcnosti -- act of repentance

// special identifiers + filename indentifiers (tuples)
#define SPOM_PM_SOBOTA "SPMVS"
#define FILE_SPOM_PM_SOBOTA "spmvs.htm"

#define ANCHOR_NANEBOVSTUPENIE "NAN"
#define FILE_NANEBOVSTUPENIE "nan.htm" // anchors according to OBD_VELKONOCNE_I

#define ANCHOR_ZOSLANIE_DUCHA_SV "ZDS"
#define FILE_ZOSLANIE_DUCHA_SV "zds.htm" // anchors according to OBD_VELKONOCNE_II, ANCHOR_ZOSLANIE_DUCHA_SV

#define ANCHOR_NAJSV_TROJICE "TROJ"
#define FILE_NAJSV_TROJICE "troj.htm"

#define ANCHOR_KRISTA_KRALA "KRKRALA"
#define FILE_KRISTA_KRALA "krkrala.htm"

#define ANCHOR_TELA_A_KRVI "TK"
#define FILE_TELA_A_KRVI "tk.htm"

#define ANCHOR_KNAZA "KNAZA"
#define FILE_KNAZA "knaza.htm"

#define ANCHOR_SRDCA "SRDCA"
#define FILE_SRDCA "srdca.htm"

#define ANCHOR_SRDCA_PM "SRDCAPM"
#define FILE_SRDCA_PM "nspm.htm"

#define ANCHOR_MARIE_MATKY_CIRKVI "PMMC"
#define FILE_MARIE_MATKY_CIRKVI "pmmc.htm"

#define ANCHOR_PM_BOHOROD "PMB"
#define FILE_PM_BOHOROD "pmb.htm"

#define ANCHOR_2NE_PO_NAR "2NE"

#define ANCHOR_ZJAVENIE_PANA "ZJV"

#define ANCHOR_SV_RODINY "SVROD"
#define FILE_SV_RODINY "svrod.htm"

#define ANCHOR_KRST_PANA "KRST"
#define FILE_KRST_PANA "krst.htm"

#define ANCHOR_DOPLNKOVA_PSALMODIA "PSCOM"
#define FILE_DOPLNKOVA_PSALMODIA "pscom.htm"

#define FILE_DODATOK_PROSBY "dodprosby.htm"

#define ANCHOR_MARIANSKE_ANTIFONY "MARIANSKE-ANTIFONY"
#define FILE_MARIANSKE_ANTIFONY "ord_km.htm"

#define ANCHOR_OTCENAS_UVOD "OTCENAS-UVOD"
#define FILE_OTCENAS_UVOD "doduvodmp.htm"

#define ANCHOR_ORDINARIUM "ORDINARIUM"

#define ANCHOR_INFO "INFO"

#define ANCHOR_CSSR_TITUL "TITUL"

extern const char* text_POSVIACKA_KATEDRALNEHO_CHRAMU[POCET_JAZYKOV + 1];

extern const char* text_JAN_01[POCET_JAZYKOV + 1];
extern const char* text_JAN_02[POCET_JAZYKOV + 1];
extern const char* text_JAN_03[POCET_JAZYKOV + 1];
extern const char* text_JAN_06[POCET_JAZYKOV + 1];
extern const char* text_JAN_07[POCET_JAZYKOV + 1];
extern const char* text_JAN_KRST[POCET_JAZYKOV + 1];
extern const char* text_JAN_13[POCET_JAZYKOV + 1];
extern const char* text_JAN_15_HU[POCET_JAZYKOV + 1];
extern const char* text_JAN_17[POCET_JAZYKOV + 1];
extern const char* text_JAN_18[POCET_JAZYKOV + 1];
extern const char* text_JAN_18_CZ[POCET_JAZYKOV + 1];
extern const char* text_JAN_20_1[POCET_JAZYKOV + 1];
extern const char* text_JAN_20_2[POCET_JAZYKOV + 1];
extern const char* text_JAN_20_HU[POCET_JAZYKOV + 1];
extern const char* text_JAN_21[POCET_JAZYKOV + 1];
extern const char* text_JAN_22[POCET_JAZYKOV + 1];
extern const char* text_JAN_22_OFM_HU[POCET_JAZYKOV + 1];
extern const char* text_JAN_23_SK[POCET_JAZYKOV + 1];
extern const char* text_JAN_24[POCET_JAZYKOV + 1];
extern const char* text_JAN_25[POCET_JAZYKOV + 1];
extern const char* text_JAN_26[POCET_JAZYKOV + 1];
extern const char* text_JAN_27[POCET_JAZYKOV + 1];
extern const char* text_JAN_27_BY[POCET_JAZYKOV + 1];
extern const char* text_JAN_28[POCET_JAZYKOV + 1];
extern const char* text_JAN_29_BY[POCET_JAZYKOV + 1];
extern const char* text_JAN_31[POCET_JAZYKOV + 1];

extern const char* text_FEB_02[POCET_JAZYKOV + 1];
extern const char* text_FEB_03_1[POCET_JAZYKOV + 1];
extern const char* text_FEB_03_2[POCET_JAZYKOV + 1];
extern const char* text_FEB_05[POCET_JAZYKOV + 1];
extern const char* text_FEB_06[POCET_JAZYKOV + 1];
extern const char* text_FEB_08_1[POCET_JAZYKOV + 1];
extern const char* text_FEB_08_2[POCET_JAZYKOV + 1];
extern const char* text_FEB_10[POCET_JAZYKOV + 1];
extern const char* text_FEB_11[POCET_JAZYKOV + 1];
extern const char* text_FEB_14[POCET_JAZYKOV + 1];
extern const char* text_FEB_15_CZ[POCET_JAZYKOV + 1];
extern const char* text_FEB_17[POCET_JAZYKOV + 1];
extern const char* text_FEB_21[POCET_JAZYKOV + 1];
extern const char* text_FEB_22[POCET_JAZYKOV + 1];
extern const char* text_FEB_23[POCET_JAZYKOV + 1];
extern const char* text_FEB_27[POCET_JAZYKOV + 1];

extern const char* text_MAR_04[POCET_JAZYKOV + 1];
extern const char* text_MAR_04_HU[POCET_JAZYKOV + 1];
extern const char* text_MAR_07[POCET_JAZYKOV + 1];
extern const char* text_MAR_08[POCET_JAZYKOV + 1];
extern const char* text_MAR_09[POCET_JAZYKOV + 1];
extern const char* text_MAR_10_CZ[POCET_JAZYKOV + 1];
extern const char* text_MAR_10_SK[POCET_JAZYKOV + 1];
extern const char* text_MAR_17[POCET_JAZYKOV + 1];
extern const char* text_MAR_17_HU[POCET_JAZYKOV + 1];
extern const char* text_MAR_18[POCET_JAZYKOV + 1];
extern const char* text_MAR_19[POCET_JAZYKOV + 1];
extern const char* text_MAR_23[POCET_JAZYKOV + 1];
extern const char* text_MAR_25[POCET_JAZYKOV + 1];

extern const char* text_POPOLCOVA_STREDA[POCET_JAZYKOV + 1];

extern const char* text_APR_02[POCET_JAZYKOV + 1];
extern const char* text_APR_04[POCET_JAZYKOV + 1];
extern const char* text_APR_05[POCET_JAZYKOV + 1];
extern const char* text_APR_07[POCET_JAZYKOV + 1];
extern const char* text_APR_11[POCET_JAZYKOV + 1];
extern const char* text_APR_13[POCET_JAZYKOV + 1];
extern const char* text_APR_16[POCET_JAZYKOV + 1];
extern const char* text_APR_21[POCET_JAZYKOV + 1];
extern const char* text_APR_23[POCET_JAZYKOV + 1];
extern const char* text_APR_23_HU[POCET_JAZYKOV + 1];
extern const char* text_APR_24_1[POCET_JAZYKOV + 1];
extern const char* text_APR_24_2[POCET_JAZYKOV + 1];
extern const char* text_APR_25[POCET_JAZYKOV + 1];
extern const char* text_APR_28_1[POCET_JAZYKOV + 1];
extern const char* text_APR_28_2[POCET_JAZYKOV + 1];
extern const char* text_APR_29[POCET_JAZYKOV + 1];
extern const char* text_APR_30[POCET_JAZYKOV + 1];
extern const char* text_APR_30_CZ[POCET_JAZYKOV + 1];

extern const char* text_MAJ_01[POCET_JAZYKOV + 1];
extern const char* text_MAJ_02[POCET_JAZYKOV + 1];
extern const char* text_MAJ_03[POCET_JAZYKOV + 1];
extern const char* text_MAJ_04[POCET_JAZYKOV + 1];
extern const char* text_MAJ_06_CZ[POCET_JAZYKOV + 1];
extern const char* text_MAJ_07_HU_1[POCET_JAZYKOV + 1];
extern const char* text_MAJ_07_HU_2[POCET_JAZYKOV + 1];
extern const char* text_MAJ_08_CZ[POCET_JAZYKOV + 1];
extern const char* text_MAJ_10[POCET_JAZYKOV + 1];
extern const char* text_MAJ_11_SK[POCET_JAZYKOV + 1];
extern const char* text_MAJ_12_1[POCET_JAZYKOV + 1];
extern const char* text_MAJ_12_2[POCET_JAZYKOV + 1];
extern const char* text_MAJ_12_CZ[POCET_JAZYKOV + 1];
extern const char* text_MAJ_13[POCET_JAZYKOV + 1];
extern const char* text_MAJ_14[POCET_JAZYKOV + 1];
extern const char* text_MAJ_16[POCET_JAZYKOV + 1];
extern const char* text_MAJ_17_HU[POCET_JAZYKOV + 1];
extern const char* text_MAJ_18[POCET_JAZYKOV + 1];
extern const char* text_MAJ_18_IS[POCET_JAZYKOV + 1];
extern const char* text_MAJ_20_CZ[POCET_JAZYKOV + 1];
extern const char* text_MAJ_20[POCET_JAZYKOV + 1];
extern const char* text_MAJ_21_CZ[POCET_JAZYKOV + 1];
extern const char* text_MAJ_21[POCET_JAZYKOV + 1];
extern const char* text_MAJ_22[POCET_JAZYKOV + 1];
extern const char* text_MAJ_23_HU[POCET_JAZYKOV + 1];
extern const char* text_MAJ_24[POCET_JAZYKOV + 1];
extern const char* text_MAJ_25_1[POCET_JAZYKOV + 1];
extern const char* text_MAJ_25_2[POCET_JAZYKOV + 1];
extern const char* text_MAJ_25_3[POCET_JAZYKOV + 1];
extern const char* text_MAJ_26[POCET_JAZYKOV + 1];
extern const char* text_MAJ_27[POCET_JAZYKOV + 1];
extern const char* text_MAJ_29[POCET_JAZYKOV + 1];
extern const char* text_MAJ_30_CZ[POCET_JAZYKOV + 1];
extern const char* text_MAJ_30_HU[POCET_JAZYKOV + 1];
extern const char* text_MAJ_31[POCET_JAZYKOV + 1];

extern const char* text_NANEBOVSTUPENIE_PANA[POCET_JAZYKOV + 1];
extern const char* text_VELKONOCNA_NEDELA[POCET_JAZYKOV + 1];
extern const char* text_NEDELA_PANOVHO_ZMRTVYCHVSTANIA[POCET_JAZYKOV + 1];
extern const char* text_NEDELA_VO_VELKONOCNEJ_OKTAVE[POCET_JAZYKOV + 1];
extern const char* text_VELKONOCNY_PONDELOK[POCET_JAZYKOV + 1];
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

extern const char* text_JUN_01[POCET_JAZYKOV + 1];
extern const char* text_JUN_02[POCET_JAZYKOV + 1];
extern const char* text_JUN_03[POCET_JAZYKOV + 1];
extern const char* text_JUN_04_HU[POCET_JAZYKOV + 1];
extern const char* text_JUN_05[POCET_JAZYKOV + 1];
extern const char* text_JUN_05_HU[POCET_JAZYKOV + 1];
extern const char* text_JUN_06[POCET_JAZYKOV + 1];
extern const char* text_JUN_08_HU[POCET_JAZYKOV + 1];
extern const char* text_JUN_09[POCET_JAZYKOV + 1];
extern const char* text_JUN_11[POCET_JAZYKOV + 1];
extern const char* text_JUN_12_CZ[POCET_JAZYKOV + 1];
extern const char* text_JUN_12_BY[POCET_JAZYKOV + 1];
extern const char* text_JUN_13[POCET_JAZYKOV + 1];
extern const char* text_JUN_13_SK[POCET_JAZYKOV + 1];
extern const char* text_JUN_14_HU[POCET_JAZYKOV + 1];
extern const char* text_JUN_15_CZ[POCET_JAZYKOV + 1];
extern const char* text_JUN_15_HU[POCET_JAZYKOV + 1];
extern const char* text_JUN_16_SK[POCET_JAZYKOV + 1];
extern const char* text_JUN_16_HU[POCET_JAZYKOV + 1];
extern const char* text_JUN_17_IS[POCET_JAZYKOV + 1];
extern const char* text_JUN_19[POCET_JAZYKOV + 1];
extern const char* text_JUN_19_CZ[POCET_JAZYKOV + 1];
extern const char* text_JUN_21[POCET_JAZYKOV + 1];
extern const char* text_JUN_22_1[POCET_JAZYKOV + 1];
extern const char* text_JUN_22_2[POCET_JAZYKOV + 1];
extern const char* text_JUN_22_HU[POCET_JAZYKOV + 1];
extern const char* text_JUN_24[POCET_JAZYKOV + 1];
extern const char* text_JUN_27[POCET_JAZYKOV + 1];
extern const char* text_JUN_27_SK_HU[POCET_JAZYKOV + 1];
extern const char* text_JUN_28[POCET_JAZYKOV + 1];
extern const char* text_JUN_29[POCET_JAZYKOV + 1];
extern const char* text_JUN_30[POCET_JAZYKOV + 1];
extern const char* text_JUN_30_CZ[POCET_JAZYKOV + 1];

extern const char* text_JUL_02_BY[POCET_JAZYKOV + 1];
extern const char* text_JUL_03[POCET_JAZYKOV + 1];
extern const char* text_JUL_04[POCET_JAZYKOV + 1];
extern const char* text_JUL_04_CZ[POCET_JAZYKOV + 1];
extern const char* text_JUL_05_LA[POCET_JAZYKOV + 1];
extern const char* text_JUL_05_SK_CZ[POCET_JAZYKOV + 1];
extern const char* text_JUL_05_BY[POCET_JAZYKOV + 1];
extern const char* text_JUL_06[POCET_JAZYKOV + 1];
extern const char* text_JUL_08_IS[POCET_JAZYKOV + 1];
extern const char* text_JUL_09[POCET_JAZYKOV + 1];
extern const char* text_JUL_11[POCET_JAZYKOV + 1];
extern const char* text_JUL_13[POCET_JAZYKOV + 1];
extern const char* text_JUL_13_IS[POCET_JAZYKOV + 1];
extern const char* text_JUL_14[POCET_JAZYKOV + 1];
extern const char* text_JUL_14_CZ[POCET_JAZYKOV + 1];
extern const char* text_JUL_15[POCET_JAZYKOV + 1];
extern const char* text_JUL_16[POCET_JAZYKOV + 1];
extern const char* text_JUL_16_CZ[POCET_JAZYKOV + 1];
extern const char* text_JUL_17_SK[POCET_JAZYKOV + 1];
extern const char* text_JUL_17_CZ[POCET_JAZYKOV + 1];
extern const char* text_JUL_18_HU[POCET_JAZYKOV + 1];
extern const char* text_JUL_20[POCET_JAZYKOV + 1];
extern const char* text_JUL_20_IS[POCET_JAZYKOV + 1];
extern const char* text_JUL_21[POCET_JAZYKOV + 1];
extern const char* text_JUL_22[POCET_JAZYKOV + 1];
extern const char* text_JUL_23[POCET_JAZYKOV + 1];
extern const char* text_JUL_24[POCET_JAZYKOV + 1];
extern const char* text_JUL_24_HU[POCET_JAZYKOV + 1];
extern const char* text_JUL_25[POCET_JAZYKOV + 1];
extern const char* text_JUL_26[POCET_JAZYKOV + 1];
extern const char* text_JUL_27[POCET_JAZYKOV + 1];
extern const char* text_JUL_29[POCET_JAZYKOV + 1];
extern const char* text_JUL_29_IS[POCET_JAZYKOV + 1];
extern const char* text_JUL_30[POCET_JAZYKOV + 1];
extern const char* text_JUL_30_SK[POCET_JAZYKOV + 1];
extern const char* text_JUL_31[POCET_JAZYKOV + 1];

extern const char* text_AUG_01[POCET_JAZYKOV + 1];
extern const char* text_AUG_02_1[POCET_JAZYKOV + 1];
extern const char* text_AUG_02_2[POCET_JAZYKOV + 1];
extern const char* text_AUG_04[POCET_JAZYKOV + 1];
extern const char* text_AUG_05[POCET_JAZYKOV + 1];
extern const char* text_AUG_05_BY[POCET_JAZYKOV + 1];
extern const char* text_AUG_06[POCET_JAZYKOV + 1];
extern const char* text_AUG_07_1[POCET_JAZYKOV + 1];
extern const char* text_AUG_07_2[POCET_JAZYKOV + 1];
extern const char* text_AUG_08[POCET_JAZYKOV + 1];
extern const char* text_AUG_09[POCET_JAZYKOV + 1];
extern const char* text_AUG_10[POCET_JAZYKOV + 1];
extern const char* text_AUG_11[POCET_JAZYKOV + 1];
extern const char* text_AUG_12[POCET_JAZYKOV + 1];
extern const char* text_AUG_13[POCET_JAZYKOV + 1];
extern const char* text_AUG_13_HU[POCET_JAZYKOV + 1];
extern const char* text_AUG_14[POCET_JAZYKOV + 1];
extern const char* text_AUG_15[POCET_JAZYKOV + 1];
extern const char* text_AUG_16[POCET_JAZYKOV + 1];
extern const char* text_AUG_17_HU[POCET_JAZYKOV + 1];
extern const char* text_AUG_18[POCET_JAZYKOV + 1];
extern const char* text_AUG_18_HU[POCET_JAZYKOV + 1];
extern const char* text_AUG_19[POCET_JAZYKOV + 1];
extern const char* text_AUG_20[POCET_JAZYKOV + 1];
extern const char* text_AUG_21[POCET_JAZYKOV + 1];
extern const char* text_AUG_22[POCET_JAZYKOV + 1];
extern const char* text_AUG_23[POCET_JAZYKOV + 1];
extern const char* text_AUG_24[POCET_JAZYKOV + 1];
extern const char* text_AUG_25_1[POCET_JAZYKOV + 1];
extern const char* text_AUG_25_2[POCET_JAZYKOV + 1];
extern const char* text_AUG_25_CZ[POCET_JAZYKOV + 1];
extern const char* text_AUG_25_2_CZ[POCET_JAZYKOV + 1];
extern const char* text_AUG_25_HU[POCET_JAZYKOV + 1];
extern const char* text_AUG_26_BY[POCET_JAZYKOV + 1];
extern const char* text_AUG_27[POCET_JAZYKOV + 1];
extern const char* text_AUG_28[POCET_JAZYKOV + 1];
extern const char* text_AUG_29[POCET_JAZYKOV + 1];
extern const char* text_AUG_30_SK[POCET_JAZYKOV + 1];
extern const char* text_AUG_31_HU[POCET_JAZYKOV + 1];

extern const char* text_SEP_03[POCET_JAZYKOV + 1];
extern const char* text_SEP_04_BY[POCET_JAZYKOV + 1];
extern const char* text_SEP_05[POCET_JAZYKOV + 1];
extern const char* text_SEP_06_SK[POCET_JAZYKOV + 1];
extern const char* text_SEP_07[POCET_JAZYKOV + 1];
extern const char* text_SEP_08[POCET_JAZYKOV + 1];
extern const char* text_SEP_08_BY[POCET_JAZYKOV + 1];
extern const char* text_SEP_09[POCET_JAZYKOV + 1];
extern const char* text_SEP_10_CZ[POCET_JAZYKOV + 1];
extern const char* text_SEP_12[POCET_JAZYKOV + 1];
extern const char* text_SEP_13[POCET_JAZYKOV + 1];
extern const char* text_SEP_13_HU[POCET_JAZYKOV + 1];
extern const char* text_SEP_14[POCET_JAZYKOV + 1];
extern const char* text_SEP_15[POCET_JAZYKOV + 1];
extern const char* text_SEP_16_CZ[POCET_JAZYKOV + 1];
extern const char* text_SEP_16[POCET_JAZYKOV + 1];
extern const char* text_SEP_17[POCET_JAZYKOV + 1];
extern const char* text_SEP_17_2[POCET_JAZYKOV + 1];
extern const char* text_SEP_17_IS[POCET_JAZYKOV + 1];
extern const char* text_SEP_19[POCET_JAZYKOV + 1];
extern const char* text_SEP_20[POCET_JAZYKOV + 1];
extern const char* text_SEP_20_CZ[POCET_JAZYKOV + 1];
extern const char* text_SEP_21[POCET_JAZYKOV + 1];
extern const char* text_SEP_22_SK[POCET_JAZYKOV + 1];
extern const char* text_SEP_23[POCET_JAZYKOV + 1];
extern const char* text_SEP_24_SK[POCET_JAZYKOV + 1];
extern const char* text_SEP_24_HU[POCET_JAZYKOV + 1];
extern const char* text_SEP_26[POCET_JAZYKOV + 1];
extern const char* text_SEP_27[POCET_JAZYKOV + 1];
extern const char* text_SEP_28[POCET_JAZYKOV + 1];
extern const char* text_SEP_28_2[POCET_JAZYKOV + 1];
extern const char* text_SEP_29[POCET_JAZYKOV + 1];
extern const char* text_SEP_30[POCET_JAZYKOV + 1];

extern const char* text_OKT_01[POCET_JAZYKOV + 1];
extern const char* text_OKT_02[POCET_JAZYKOV + 1];
extern const char* text_OKT_04[POCET_JAZYKOV + 1];
extern const char* text_OKT_05[POCET_JAZYKOV + 1];
extern const char* text_OKT_05_HU[POCET_JAZYKOV + 1];
extern const char* text_OKT_06[POCET_JAZYKOV + 1];
extern const char* text_OKT_07[POCET_JAZYKOV + 1];
extern const char* text_OKT_08_HU[POCET_JAZYKOV + 1];
extern const char* text_OKT_09_1[POCET_JAZYKOV + 1];
extern const char* text_OKT_09_2[POCET_JAZYKOV + 1];
extern const char* text_OKT_11[POCET_JAZYKOV + 1];
extern const char* text_OKT_10_SK[POCET_JAZYKOV + 1];
extern const char* text_OKT_12_CZ[POCET_JAZYKOV + 1];
extern const char* text_OKT_14[POCET_JAZYKOV + 1];
extern const char* text_OKT_15[POCET_JAZYKOV + 1];
extern const char* text_OKT_16_1[POCET_JAZYKOV + 1];
extern const char* text_OKT_16_2[POCET_JAZYKOV + 1];
extern const char* text_OKT_16_3[POCET_JAZYKOV + 1];
extern const char* text_OKT_17[POCET_JAZYKOV + 1];
extern const char* text_OKT_18[POCET_JAZYKOV + 1];
extern const char* text_OKT_19_1[POCET_JAZYKOV + 1];
extern const char* text_OKT_19_2[POCET_JAZYKOV + 1];
extern const char* text_OKT_21_CZ[POCET_JAZYKOV + 1];
extern const char* text_OKT_22[POCET_JAZYKOV + 1];
extern const char* text_OKT_23[POCET_JAZYKOV + 1];
extern const char* text_OKT_24[POCET_JAZYKOV + 1];
extern const char* text_OKT_24_HU[POCET_JAZYKOV + 1];
extern const char* text_OKT_25_CONS[POCET_JAZYKOV + 1];
extern const char* text_OKT_25_SK[POCET_JAZYKOV + 1];
extern const char* text_OKT_25[POCET_JAZYKOV + 1];
extern const char* text_OKT_26[POCET_JAZYKOV + 1];
extern const char* text_OKT_27_SK[POCET_JAZYKOV + 1];
extern const char* text_OKT_28[POCET_JAZYKOV + 1];
extern const char* text_OKT_29_CZ[POCET_JAZYKOV + 1];
extern const char* text_OKT_30_CZ[POCET_JAZYKOV + 1];
extern const char* text_OKT_31_CZ[POCET_JAZYKOV + 1];
extern const char* text_OKT_31_HU[POCET_JAZYKOV + 1];

extern const char* text_NOV_01[POCET_JAZYKOV + 1];
extern const char* text_NOV_02[POCET_JAZYKOV + 1];
extern const char* text_NOV_03[POCET_JAZYKOV + 1];
extern const char* text_NOV_04[POCET_JAZYKOV + 1];
extern const char* text_NOV_05_SK[POCET_JAZYKOV + 1];
extern const char* text_NOV_09[POCET_JAZYKOV + 1];
extern const char* text_NOV_10[POCET_JAZYKOV + 1];
extern const char* text_NOV_11[POCET_JAZYKOV + 1];
extern const char* text_NOV_12[POCET_JAZYKOV + 1];
extern const char* text_NOV_13_CZ[POCET_JAZYKOV + 1];
extern const char* text_NOV_13_HU[POCET_JAZYKOV + 1];
extern const char* text_NOV_15[POCET_JAZYKOV + 1];
extern const char* text_NOV_16_1[POCET_JAZYKOV + 1];
extern const char* text_NOV_16_2[POCET_JAZYKOV + 1];
extern const char* text_NOV_16_BY[POCET_JAZYKOV + 1];
extern const char* text_NOV_17[POCET_JAZYKOV + 1];
extern const char* text_NOV_18[POCET_JAZYKOV + 1];
extern const char* text_NOV_20_SK[POCET_JAZYKOV + 1];
extern const char* text_NOV_20_SK_2[POCET_JAZYKOV + 1];
extern const char* text_NOV_20_BY[POCET_JAZYKOV + 1];
extern const char* text_NOV_21[POCET_JAZYKOV + 1];
extern const char* text_NOV_22[POCET_JAZYKOV + 1];
extern const char* text_NOV_23_1[POCET_JAZYKOV + 1];
extern const char* text_NOV_23_2[POCET_JAZYKOV + 1];
extern const char* text_NOV_24[POCET_JAZYKOV + 1];
extern const char* text_NOV_25[POCET_JAZYKOV + 1];
extern const char* text_NOV_25_HU[POCET_JAZYKOV + 1];
extern const char* text_NOV_28_HU[POCET_JAZYKOV + 1];
extern const char* text_NOV_30[POCET_JAZYKOV + 1];

extern const char* text_DEC_01_CZ[POCET_JAZYKOV + 1];
extern const char* text_DEC_02_CZ[POCET_JAZYKOV + 1];
extern const char* text_DEC_03[POCET_JAZYKOV + 1];
extern const char* text_DEC_04[POCET_JAZYKOV + 1];
extern const char* text_DEC_04_2[POCET_JAZYKOV + 1];
extern const char* text_DEC_06[POCET_JAZYKOV + 1];
extern const char* text_DEC_07[POCET_JAZYKOV + 1];
extern const char* text_DEC_08[POCET_JAZYKOV + 1];
extern const char* text_DEC_09[POCET_JAZYKOV + 1];
extern const char* text_DEC_10[POCET_JAZYKOV + 1];
extern const char* text_DEC_11[POCET_JAZYKOV + 1];
extern const char* text_DEC_12[POCET_JAZYKOV + 1];
extern const char* text_DEC_13[POCET_JAZYKOV + 1];
extern const char* text_DEC_14[POCET_JAZYKOV + 1];
extern const char* text_DEC_21[POCET_JAZYKOV + 1];
extern const char* text_DEC_22_CZ[POCET_JAZYKOV + 1];
extern const char* text_DEC_23[POCET_JAZYKOV + 1];
extern const char* text_DEC_23_IS[POCET_JAZYKOV + 1];
extern const char* text_DEC_26[POCET_JAZYKOV + 1];
extern const char* text_DEC_27[POCET_JAZYKOV + 1];
extern const char* text_DEC_28[POCET_JAZYKOV + 1];
extern const char* text_DEC_29[POCET_JAZYKOV + 1];
extern const char* text_DEC_31[POCET_JAZYKOV + 1];

// --------------- CSSR propriá ---------------
extern const char* text_JAN_05_CSSR[POCET_JAZYKOV + 1];
extern const char* text_JAN_14_CSSR[POCET_JAZYKOV + 1];
extern const char* text_MAR_15_CSSR[POCET_JAZYKOV + 1];
extern const char* text_JUN_27_CSSR[POCET_JAZYKOV + 1];
extern const char* text_JUN_30_CSSR[POCET_JAZYKOV + 1];
extern const char* text_CSSR_TITUL_KONGREGACIE[POCET_JAZYKOV + 1]; // JUL
extern const char* text_AUG_01_CSSR[POCET_JAZYKOV + 1];
extern const char* text_SEP_11_CSSR[POCET_JAZYKOV + 1];
extern const char* text_SEP_26_CSSR[POCET_JAZYKOV + 1];
extern const char* text_OKT_05_CSSR[POCET_JAZYKOV + 1];
extern const char* text_OKT_16_CSSR[POCET_JAZYKOV + 1];

// --------------- SVD propriá ---------------
extern const char* text_JAN_15_SVD[POCET_JAZYKOV + 1];
extern const char* text_JAN_29_SVD[POCET_JAZYKOV + 1];
extern const char* text_JUN_12_SVD[POCET_JAZYKOV + 1]; // HU

// --------------- SDB propriá ---------------
extern const char* text_JAN_08_SDB[POCET_JAZYKOV + 1];
extern const char* text_JAN_15_SDB[POCET_JAZYKOV + 1];
extern const char* text_JAN_22_SDB[POCET_JAZYKOV + 1];
extern const char* text_JAN_24_SDB[POCET_JAZYKOV + 1];
extern const char* text_JAN_30_SDB[POCET_JAZYKOV + 1];
extern const char* text_JAN_31_SDB[POCET_JAZYKOV + 1];
extern const char* text_FEB_01_SDB[POCET_JAZYKOV + 1];
extern const char* text_FEB_07_SDB[POCET_JAZYKOV + 1];
extern const char* text_FEB_09_SDB[POCET_JAZYKOV + 1];
extern const char* text_FEB_25_SDB[POCET_JAZYKOV + 1];
extern const char* text_MAJ_06_SDB[POCET_JAZYKOV + 1];
extern const char* text_MAJ_13_SDB[POCET_JAZYKOV + 1];
extern const char* text_MAJ_16_SDB[POCET_JAZYKOV + 1];
extern const char* text_MAJ_18_SDB[POCET_JAZYKOV + 1];
extern const char* text_MAJ_24_SDB[POCET_JAZYKOV + 1];
extern const char* text_MAJ_29_SDB[POCET_JAZYKOV + 1];
extern const char* text_JUN_08_SDB[POCET_JAZYKOV + 1];
extern const char* text_JUN_12_SDB[POCET_JAZYKOV + 1];
extern const char* text_JUN_23_SDB[POCET_JAZYKOV + 1];
extern const char* text_JUL_07_SDB[POCET_JAZYKOV + 1];
extern const char* text_AUG_02_SDB[POCET_JAZYKOV + 1];
extern const char* text_AUG_25_SDB[POCET_JAZYKOV + 1];
extern const char* text_AUG_26_SDB[POCET_JAZYKOV + 1];
extern const char* text_SEP_22_SDB[POCET_JAZYKOV + 1];
extern const char* text_OKT_05_SDB[POCET_JAZYKOV + 1];
extern const char* text_OKT_13_SDB[POCET_JAZYKOV + 1];
extern const char* text_OKT_24_SDB[POCET_JAZYKOV + 1];
extern const char* text_OKT_29_SDB[POCET_JAZYKOV + 1];
extern const char* text_NOV_05_SDB[POCET_JAZYKOV + 1];
extern const char* text_NOV_13_SDB[POCET_JAZYKOV + 1];
extern const char* text_NOV_15_SDB[POCET_JAZYKOV + 1];
extern const char* text_NOV_25_SDB[POCET_JAZYKOV + 1];
extern const char* text_DEC_05_SDB[POCET_JAZYKOV + 1];

// --------------- SJ propriá ---------------
extern const char* text_JAN_01_SJ[POCET_JAZYKOV + 1];
extern const char* text_JAN_03_SJ[POCET_JAZYKOV + 1];
extern const char* text_JAN_19_SJ[POCET_JAZYKOV + 1];
extern const char* text_FEB_04_SJ[POCET_JAZYKOV + 1];
extern const char* text_FEB_06_SJ[POCET_JAZYKOV + 1];
extern const char* text_FEB_15_SJ[POCET_JAZYKOV + 1];
extern const char* text_MAR_19_SJ[POCET_JAZYKOV + 1];
extern const char* text_APR_22_SJ[POCET_JAZYKOV + 1];
extern const char* text_APR_27_SJ[POCET_JAZYKOV + 1];
extern const char* text_MAJ_04_SJ[POCET_JAZYKOV + 1];
extern const char* text_MAJ_08_SJ[POCET_JAZYKOV + 1];
extern const char* text_MAJ_16_SJ[POCET_JAZYKOV + 1];
extern const char* text_MAJ_16_CZ_SJ[POCET_JAZYKOV + 1];
extern const char* text_MAJ_22_SJ[POCET_JAZYKOV + 1];
extern const char* text_MAJ_24_SJ[POCET_JAZYKOV + 1];
extern const char* text_JUN_08_SJ[POCET_JAZYKOV + 1];
extern const char* text_JUN_09_SJ[POCET_JAZYKOV + 1];
extern const char* text_JUN_21_SJ[POCET_JAZYKOV + 1];
extern const char* text_JUL_02_SJ[POCET_JAZYKOV + 1];
extern const char* text_JUL_09_SJ[POCET_JAZYKOV + 1];
extern const char* text_JUL_31_SJ[POCET_JAZYKOV + 1];
extern const char* text_AUG_02_SJ[POCET_JAZYKOV + 1];
extern const char* text_AUG_18_SJ[POCET_JAZYKOV + 1];
extern const char* text_SEP_02_SJ[POCET_JAZYKOV + 1];
extern const char* text_SEP_07_SJ[POCET_JAZYKOV + 1];
extern const char* text_SEP_09_SJ[POCET_JAZYKOV + 1];
extern const char* text_SEP_10_SJ[POCET_JAZYKOV + 1];
extern const char* text_SEP_17_SJ[POCET_JAZYKOV + 1];
extern const char* text_OKT_03_SJ[POCET_JAZYKOV + 1];
extern const char* text_OKT_12_SJ[POCET_JAZYKOV + 1];
extern const char* text_OKT_14_SJ[POCET_JAZYKOV + 1];
extern const char* text_OKT_19_SJ[POCET_JAZYKOV + 1];
extern const char* text_OKT_21_SJ[POCET_JAZYKOV + 1];
extern const char* text_OKT_30_SJ[POCET_JAZYKOV + 1];
extern const char* text_OKT_31_SJ[POCET_JAZYKOV + 1];
extern const char* text_NOV_03_SJ[POCET_JAZYKOV + 1];
extern const char* text_NOV_05_SJ[POCET_JAZYKOV + 1];
extern const char* text_NOV_06_SJ[POCET_JAZYKOV + 1];
extern const char* text_NOV_07_SJ[POCET_JAZYKOV + 1];
extern const char* text_NOV_13_SJ[POCET_JAZYKOV + 1];
extern const char* text_NOV_14_SJ[POCET_JAZYKOV + 1];
extern const char* text_NOV_16_SJ[POCET_JAZYKOV + 1];
extern const char* text_NOV_23_SJ[POCET_JAZYKOV + 1];
extern const char* text_NOV_26_SJ[POCET_JAZYKOV + 1];
extern const char* text_NOV_29_SJ[POCET_JAZYKOV + 1];
extern const char* text_DEC_01_SJ[POCET_JAZYKOV + 1];
extern const char* text_DEC_03_SJ[POCET_JAZYKOV + 1];

// --------------- OFM + OFMCap + OFMConv propriá ---------------
extern const char* text_JAN_04_OFM[POCET_JAZYKOV + 1];
extern const char* text_JAN_05_OFM[POCET_JAZYKOV + 1];
extern const char* text_JAN_12_OFM[POCET_JAZYKOV + 1];
extern const char* text_JAN_14_OFM[POCET_JAZYKOV + 1];
extern const char* text_JAN_16_OFM[POCET_JAZYKOV + 1];
extern const char* text_JAN_20_OFM[POCET_JAZYKOV + 1];
extern const char* text_JAN_29_OFMCONV[POCET_JAZYKOV + 1];
extern const char* text_JAN_30_OFM[POCET_JAZYKOV + 1];
extern const char* text_FEB_04_OFM[POCET_JAZYKOV + 1];
extern const char* text_FEB_06_OFM[POCET_JAZYKOV + 1];
extern const char* text_FEB_07_OFM[POCET_JAZYKOV + 1];
extern const char* text_FEB_09_OFMCAP[POCET_JAZYKOV + 1];
extern const char* text_FEB_19_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAR_02_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAR_12_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAR_18_OFM[POCET_JAZYKOV + 1];
extern const char* text_APR_21_OFM[POCET_JAZYKOV + 1];
extern const char* text_APR_22_OFM[POCET_JAZYKOV + 1];
extern const char* text_APR_23_OFM[POCET_JAZYKOV + 1];
extern const char* text_APR_24_OFM[POCET_JAZYKOV + 1];
extern const char* text_APR_28_OFM[POCET_JAZYKOV + 1];
extern const char* text_APR_30_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_04_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_08_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_08_2_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_08_3_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_09_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_11_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_12_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_13_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_15_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_17_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_18_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_19_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_20_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_21_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_24_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_28_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_27_OFM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_30_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUN_02_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUN_07_OFMCONV[POCET_JAZYKOV + 1];
extern const char* text_JUN_08_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUN_12_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUN_12_2_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUN_12_3_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUN_13_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUN_15_OFM_HU[POCET_JAZYKOV + 1];
extern const char* text_JUN_16_1_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUN_16_2_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUN_17_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUN_26_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUN_26_2_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUN_30_OFM[POCET_JAZYKOV + 1];
extern const char* text_NEPOSKVRNENEHO_SRDCA_PM_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUL_08_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUL_09_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUL_10_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUL_12_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUL_13_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUL_14_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUL_15_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUL_18_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUL_19_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUL_21_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUL_24_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUL_28_1_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUL_28_2_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUL_30_SK_OFM[POCET_JAZYKOV + 1];
extern const char* text_JUL_30_OFMCAP[POCET_JAZYKOV + 1];
extern const char* text_AUG_02_OFM[POCET_JAZYKOV + 1];
extern const char* text_AUG_07_OFM[POCET_JAZYKOV + 1];
extern const char* text_AUG_08_OFM[POCET_JAZYKOV + 1];
extern const char* text_AUG_11_OFM[POCET_JAZYKOV + 1];
extern const char* text_AUG_13_OFM[POCET_JAZYKOV + 1];
extern const char* text_AUG_14_OFM[POCET_JAZYKOV + 1];
extern const char* text_AUG_17_OFM[POCET_JAZYKOV + 1];
extern const char* text_AUG_18_1_OFM[POCET_JAZYKOV + 1];
extern const char* text_AUG_18_2_OFM[POCET_JAZYKOV + 1];
extern const char* text_AUG_19_OFM[POCET_JAZYKOV + 1];
extern const char* text_AUG_23_OFM[POCET_JAZYKOV + 1];
extern const char* text_AUG_25_OFM[POCET_JAZYKOV + 1];
extern const char* text_SEP_01_OFM[POCET_JAZYKOV + 1];
extern const char* text_SEP_02_1_OFM[POCET_JAZYKOV + 1];
extern const char* text_SEP_02_2_OFM[POCET_JAZYKOV + 1];
extern const char* text_SEP_04_OFM[POCET_JAZYKOV + 1];
extern const char* text_SEP_17_OFM[POCET_JAZYKOV + 1];
extern const char* text_SEP_18_OFM[POCET_JAZYKOV + 1];
extern const char* text_SEP_19_OFM[POCET_JAZYKOV + 1];
extern const char* text_SEP_22_OFM[POCET_JAZYKOV + 1];
extern const char* text_SEP_23_OFM[POCET_JAZYKOV + 1];
extern const char* text_SEP_24_OFM[POCET_JAZYKOV + 1];
extern const char* text_SEP_25_OFM[POCET_JAZYKOV + 1];
extern const char* text_SEP_26_OFM[POCET_JAZYKOV + 1];
extern const char* text_SEP_28_OFM[POCET_JAZYKOV + 1];
extern const char* text_OKT_04_OFM[POCET_JAZYKOV + 1];
extern const char* text_OKT_05_OFM[POCET_JAZYKOV + 1];
extern const char* text_OKT_06_HU_OFM[POCET_JAZYKOV + 1];
extern const char* text_OKT_10_HU_OFM[POCET_JAZYKOV + 1];
extern const char* text_OKT_11_OFM[POCET_JAZYKOV + 1];
extern const char* text_OKT_12_OFM[POCET_JAZYKOV + 1];
extern const char* text_OKT_13_OFM[POCET_JAZYKOV + 1];
extern const char* text_OKT_19_OFM[POCET_JAZYKOV + 1];
extern const char* text_OKT_20_OFM[POCET_JAZYKOV + 1];
extern const char* text_OKT_21_OFMCAP[POCET_JAZYKOV + 1];
extern const char* text_OKT_22_HU_OFM[POCET_JAZYKOV + 1];
extern const char* text_OKT_23_OFM[POCET_JAZYKOV + 1];
extern const char* text_OKT_25_OFM[POCET_JAZYKOV + 1];
extern const char* text_OKT_26_OFM[POCET_JAZYKOV + 1];
extern const char* text_OKT_30_HU_OFM[POCET_JAZYKOV + 1];
extern const char* text_OKT_31_OFMCAP[POCET_JAZYKOV + 1];
extern const char* text_NOV_03_OFM[POCET_JAZYKOV + 1];
extern const char* text_NOV_06_OFM[POCET_JAZYKOV + 1];
extern const char* text_NOV_06_1_OFMCAP[POCET_JAZYKOV + 1];
extern const char* text_NOV_06_2_OFMCAP[POCET_JAZYKOV + 1];
extern const char* text_NOV_08_OFM[POCET_JAZYKOV + 1];
extern const char* text_NOV_13_OFM[POCET_JAZYKOV + 1];
extern const char* text_NOV_14_OFM[POCET_JAZYKOV + 1];
extern const char* text_NOV_17_OFM[POCET_JAZYKOV + 1];
extern const char* text_NOV_18_OFM[POCET_JAZYKOV + 1];
extern const char* text_NOV_19_OFM[POCET_JAZYKOV + 1];
extern const char* text_NOV_26_OFM[POCET_JAZYKOV + 1];
extern const char* text_NOV_27_OFM[POCET_JAZYKOV + 1];
extern const char* text_NOV_28_OFM[POCET_JAZYKOV + 1];
extern const char* text_NOV_29_OFM[POCET_JAZYKOV + 1];
extern const char* text_DEC_02_1_OFM[POCET_JAZYKOV + 1];
extern const char* text_DEC_02_2_OFM[POCET_JAZYKOV + 1];
extern const char* text_DEC_10_OFMCAP[POCET_JAZYKOV + 1];

// --------------- OP propriá ---------------
extern const char* text_JAN_03_OP[POCET_JAZYKOV + 1];
extern const char* text_JAN_10_1_OP[POCET_JAZYKOV + 1];
extern const char* text_JAN_10_2_OP[POCET_JAZYKOV + 1];
extern const char* text_JAN_11_OP[POCET_JAZYKOV + 1];
extern const char* text_JAN_19_OP[POCET_JAZYKOV + 1];
extern const char* text_JAN_22_OP[POCET_JAZYKOV + 1];
extern const char* text_JAN_23_OP[POCET_JAZYKOV + 1];
extern const char* text_JAN_27_OP[POCET_JAZYKOV + 1];
extern const char* text_JAN_29_OP[POCET_JAZYKOV + 1];
extern const char* text_FEB_03_OP[POCET_JAZYKOV + 1];
extern const char* text_FEB_04_OP[POCET_JAZYKOV + 1];
extern const char* text_FEB_07_OP[POCET_JAZYKOV + 1];
extern const char* text_FEB_12_OP[POCET_JAZYKOV + 1];
extern const char* text_FEB_13_OP[POCET_JAZYKOV + 1];
extern const char* text_FEB_16_OP[POCET_JAZYKOV + 1];
extern const char* text_FEB_18_OP[POCET_JAZYKOV + 1];
extern const char* text_FEB_19_OP[POCET_JAZYKOV + 1];
extern const char* text_FEB_20_OP[POCET_JAZYKOV + 1];
extern const char* text_FEB_24_OP[POCET_JAZYKOV + 1];
extern const char* text_FEB_24_OP_2[POCET_JAZYKOV + 1];
extern const char* text_APR_01_OP[POCET_JAZYKOV + 1];
extern const char* text_APR_10_OP[POCET_JAZYKOV + 1];
extern const char* text_APR_13_OP[POCET_JAZYKOV + 1];
extern const char* text_APR_14_OP[POCET_JAZYKOV + 1];
extern const char* text_APR_17_1_OP[POCET_JAZYKOV + 1];
extern const char* text_APR_17_2_OP[POCET_JAZYKOV + 1];
extern const char* text_APR_19_1_OP[POCET_JAZYKOV + 1];
extern const char* text_APR_19_2_OP[POCET_JAZYKOV + 1];
extern const char* text_APR_20_OP[POCET_JAZYKOV + 1];
extern const char* text_APR_27_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_04_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_04_2_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_07_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_08_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_08_2_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_10_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_12_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_13_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_15_1_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_15_2_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_16_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_19_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_21_2_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_21_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_24_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_27_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_28_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_29_OP[POCET_JAZYKOV + 1];
extern const char* text_MAJ_30_OP[POCET_JAZYKOV + 1];
extern const char* text_JUN_02_OP[POCET_JAZYKOV + 1];
extern const char* text_JUN_04_OP[POCET_JAZYKOV + 1];
extern const char* text_JUN_08_OP[POCET_JAZYKOV + 1];
extern const char* text_JUN_10_OP[POCET_JAZYKOV + 1];
extern const char* text_JUN_12_OP[POCET_JAZYKOV + 1];
extern const char* text_JUN_18_OP[POCET_JAZYKOV + 1];
extern const char* text_JUN_20_OP[POCET_JAZYKOV + 1];
extern const char* text_JUN_23_OP[POCET_JAZYKOV + 1];
extern const char* text_JUL_04_1_OP[POCET_JAZYKOV + 1];
extern const char* text_JUL_04_2_OP[POCET_JAZYKOV + 1];
extern const char* text_JUL_07_OP[POCET_JAZYKOV + 1];
extern const char* text_JUL_08_OP[POCET_JAZYKOV + 1];
extern const char* text_JUL_09_1_OP[POCET_JAZYKOV + 1];
extern const char* text_JUL_09_2_OP[POCET_JAZYKOV + 1];
extern const char* text_JUL_13_OP[POCET_JAZYKOV + 1];
extern const char* text_JUL_17_OP[POCET_JAZYKOV + 1];
extern const char* text_JUL_18_OP[POCET_JAZYKOV + 1];
extern const char* text_JUL_24_1_OP[POCET_JAZYKOV + 1];
extern const char* text_JUL_24_2_OP[POCET_JAZYKOV + 1];
extern const char* text_JUL_27_OP[POCET_JAZYKOV + 1];
extern const char* text_AUG_02_OP[POCET_JAZYKOV + 1];
extern const char* text_AUG_03_OP[POCET_JAZYKOV + 1];
extern const char* text_AUG_08_OP[POCET_JAZYKOV + 1];
extern const char* text_AUG_09_OP[POCET_JAZYKOV + 1];
extern const char* text_AUG_12_OP[POCET_JAZYKOV + 1];
extern const char* text_AUG_13_OP[POCET_JAZYKOV + 1];
extern const char* text_AUG_14_OP[POCET_JAZYKOV + 1];
extern const char* text_AUG_17_OP[POCET_JAZYKOV + 1];
extern const char* text_AUG_18_OP[POCET_JAZYKOV + 1];
extern const char* text_AUG_19_OP[POCET_JAZYKOV + 1];
extern const char* text_AUG_26_OP[POCET_JAZYKOV + 1];
extern const char* text_SEP_02_1_OP[POCET_JAZYKOV + 1];
extern const char* text_SEP_02_2_OP[POCET_JAZYKOV + 1];
extern const char* text_SEP_04_OP[POCET_JAZYKOV + 1];
extern const char* text_SEP_05_1_OP[POCET_JAZYKOV + 1];
extern const char* text_SEP_07_OP[POCET_JAZYKOV + 1];
extern const char* text_SEP_06_1_OP[POCET_JAZYKOV + 1];
extern const char* text_SEP_06_2_OP[POCET_JAZYKOV + 1];
extern const char* text_SEP_18_OP[POCET_JAZYKOV + 1];
extern const char* text_SEP_19_OP[POCET_JAZYKOV + 1];
extern const char* text_SEP_20_1_OP[POCET_JAZYKOV + 1];
extern const char* text_SEP_20_2_OP[POCET_JAZYKOV + 1];
extern const char* text_SEP_24_OP[POCET_JAZYKOV + 1];
extern const char* text_SEP_28_2_OP[POCET_JAZYKOV + 1];
extern const char* text_SEP_28_OP[POCET_JAZYKOV + 1];
extern const char* text_OKT_03_OP[POCET_JAZYKOV + 1];
extern const char* text_OKT_04_OP[POCET_JAZYKOV + 1];
extern const char* text_OKT_05_OP[POCET_JAZYKOV + 1];
extern const char* text_OKT_06_OP[POCET_JAZYKOV + 1];
extern const char* text_OKT_08_1_OP[POCET_JAZYKOV + 1];
extern const char* text_OKT_08_2_OP[POCET_JAZYKOV + 1];
extern const char* text_OKT_09_OP[POCET_JAZYKOV + 1];
extern const char* text_OKT_11_OP[POCET_JAZYKOV + 1];
extern const char* text_OKT_13_OP[POCET_JAZYKOV + 1];
extern const char* text_OKT_14_OP[POCET_JAZYKOV + 1];
extern const char* text_OKT_19_OP[POCET_JAZYKOV + 1];
extern const char* text_OKT_21_OP[POCET_JAZYKOV + 1];
extern const char* text_OKT_22_OP[POCET_JAZYKOV + 1];
extern const char* text_OKT_25_OP[POCET_JAZYKOV + 1];
extern const char* text_OKT_26_OP[POCET_JAZYKOV + 1];
extern const char* text_OKT_27_OP[POCET_JAZYKOV + 1];
extern const char* text_OKT_30_1_OP[POCET_JAZYKOV + 1];
extern const char* text_OKT_30_2_OP[POCET_JAZYKOV + 1];
extern const char* text_NOV_05_OP[POCET_JAZYKOV + 1];
extern const char* text_NOV_06_OP[POCET_JAZYKOV + 1];
extern const char* text_NOV_07_OP[POCET_JAZYKOV + 1];
extern const char* text_NOV_08_OP[POCET_JAZYKOV + 1];
extern const char* text_NOV_14_1_OP[POCET_JAZYKOV + 1];
extern const char* text_NOV_14_2_OP[POCET_JAZYKOV + 1];
extern const char* text_NOV_19_OP[POCET_JAZYKOV + 1];
extern const char* text_NOV_19_2_OP[POCET_JAZYKOV + 1];
extern const char* text_NOV_24_OP[POCET_JAZYKOV + 1];
extern const char* text_NOV_27_OP[POCET_JAZYKOV + 1];
extern const char* text_DEC_01_OP[POCET_JAZYKOV + 1];
extern const char* text_DEC_09_OP[POCET_JAZYKOV + 1];
extern const char* text_DEC_16_OP[POCET_JAZYKOV + 1];
extern const char* text_DEC_22_OP[POCET_JAZYKOV + 1];

// --------------- OPraem propriá ---------------
extern const char* text_JAN_14_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_FEB_04_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_FEB_10_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_FEB_17_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_FEB_18_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_APR_24_AUG[POCET_JAZYKOV + 1];
extern const char* text_APR_26_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_02_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_24_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_JUN_06_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_JUN_16_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_JUL_09_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_JUL_14_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_AUG_13_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_AUG_16_2[POCET_JAZYKOV + 1];
extern const char* text_AUG_21_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_AUG_27_AUG[POCET_JAZYKOV + 1];
extern const char* text_AUG_28_AUG[POCET_JAZYKOV + 1];
extern const char* text_AUG_30_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_SEP_12_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_SEP_18_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_OKT_07_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_OKT_10_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_OKT_13_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_OKT_20_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_OKT_26_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_NOV_13_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_NOV_14_OPRAEM[POCET_JAZYKOV + 1];
extern const char* text_OPATSKY_KOSTOL_OPRAEM[POCET_JAZYKOV + 1];

// --------------- OCD propriá ---------------
extern const char* text_JAN_04_OCD[POCET_JAZYKOV + 1];
extern const char* text_JAN_08_OCD[POCET_JAZYKOV + 1];
extern const char* text_JAN_09_OCD[POCET_JAZYKOV + 1];
extern const char* text_JAN_27_OCD[POCET_JAZYKOV + 1];
extern const char* text_FEB_04_OCD[POCET_JAZYKOV + 1];
extern const char* text_FEB_24_OCD[POCET_JAZYKOV + 1];
extern const char* text_APR_17_OCD[POCET_JAZYKOV + 1];
extern const char* text_APR_18_OCD[POCET_JAZYKOV + 1];
extern const char* text_APR_24_OCD[POCET_JAZYKOV + 1];
extern const char* text_MAJ_04_OCD[POCET_JAZYKOV + 1];
extern const char* text_MAJ_17_OCD[POCET_JAZYKOV + 1];
extern const char* text_MAJ_22_OCD[POCET_JAZYKOV + 1];
extern const char* text_MAJ_25_OCD[POCET_JAZYKOV + 1];
extern const char* text_MAJ_29_OCD[POCET_JAZYKOV + 1];
extern const char* text_JUN_07_OCD[POCET_JAZYKOV + 1];
extern const char* text_JUN_12_OCD[POCET_JAZYKOV + 1];
extern const char* text_JUN_14_OCD[POCET_JAZYKOV + 1];
extern const char* text_JUN_26_OCD[POCET_JAZYKOV + 1];
extern const char* text_JUL_07_OCD[POCET_JAZYKOV + 1];
extern const char* text_JUL_12_OCD[POCET_JAZYKOV + 1];
extern const char* text_JUL_13_OCD[POCET_JAZYKOV + 1];
extern const char* text_JUL_16_OCD[POCET_JAZYKOV + 1];
extern const char* text_JUL_17_OCD[POCET_JAZYKOV + 1];
extern const char* text_JUL_20_OCD[POCET_JAZYKOV + 1];
extern const char* text_JUL_21_OCD[POCET_JAZYKOV + 1];
extern const char* text_JUL_24_OCD[POCET_JAZYKOV + 1];
extern const char* text_JUL_28_OCD[POCET_JAZYKOV + 1];
extern const char* text_AUG_07_OCD[POCET_JAZYKOV + 1];
extern const char* text_AUG_09_OCD[POCET_JAZYKOV + 1];
extern const char* text_AUG_18_OCD[POCET_JAZYKOV + 1];
extern const char* text_AUG_25_OCD[POCET_JAZYKOV + 1];
extern const char* text_AUG_26_OCD[POCET_JAZYKOV + 1];
extern const char* text_SEP_01_OCD[POCET_JAZYKOV + 1];
extern const char* text_SEP_11_OCD[POCET_JAZYKOV + 1];
extern const char* text_SEP_17_OCD[POCET_JAZYKOV + 1];
extern const char* text_OKT_01_OCD[POCET_JAZYKOV + 1];
extern const char* text_OKT_15_OCD[POCET_JAZYKOV + 1];
extern const char* text_OKT_30_OCD[POCET_JAZYKOV + 1];
extern const char* text_NOV_06_OCD[POCET_JAZYKOV + 1];
extern const char* text_NOV_07_OCD[POCET_JAZYKOV + 1];
extern const char* text_NOV_08_OCD[POCET_JAZYKOV + 1];
extern const char* text_NOV_14_OCD[POCET_JAZYKOV + 1];
extern const char* text_NOV_15_OCD[POCET_JAZYKOV + 1];
extern const char* text_NOV_19_OCD[POCET_JAZYKOV + 1];
extern const char* text_NOV_29_OCD[POCET_JAZYKOV + 1];
extern const char* text_DEC_11_OCD[POCET_JAZYKOV + 1];
extern const char* text_DEC_14_OCD[POCET_JAZYKOV + 1];
extern const char* text_DEC_16_OCD[POCET_JAZYKOV + 1];

// --------------- CM propriá ---------------
extern const char* text_JAN_04_CM[POCET_JAZYKOV + 1];
extern const char* text_JAN_25_CM[POCET_JAZYKOV + 1];
extern const char* text_FEB_01_CM[POCET_JAZYKOV + 1];
extern const char* text_FEB_18_CM[POCET_JAZYKOV + 1];
extern const char* text_APR_26_CM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_09_CM[POCET_JAZYKOV + 1];
extern const char* text_MAJ_23_CM[POCET_JAZYKOV + 1];
extern const char* text_JUN_26_CM[POCET_JAZYKOV + 1];
extern const char* text_JUL_30_CM[POCET_JAZYKOV + 1];
extern const char* text_AUG_30_CM[POCET_JAZYKOV + 1];
extern const char* text_SEP_02_CM[POCET_JAZYKOV + 1];
extern const char* text_SEP_11_CM[POCET_JAZYKOV + 1];
extern const char* text_SEP_27_CM[POCET_JAZYKOV + 1];
extern const char* text_NOV_27_CM[POCET_JAZYKOV + 1];
extern const char* text_NOV_28_CM[POCET_JAZYKOV + 1];

// --------------- CSA propriá ---------------
extern const char* text_JAN_09_CSA[POCET_JAZYKOV + 1];
extern const char* text_DEC_09_CSA[POCET_JAZYKOV + 1];

// --------------- OSU propriá ---------------
extern const char* text_JAN_27_OSU[POCET_JAZYKOV + 1];
extern const char* text_APR_26_OSU[POCET_JAZYKOV + 1];
extern const char* text_APR_30_OSU[POCET_JAZYKOV + 1];
extern const char* text_MAJ_18_OSU[POCET_JAZYKOV + 1];
extern const char* text_MAJ_29_OSU[POCET_JAZYKOV + 1];
extern const char* text_JUN_12_OSU[POCET_JAZYKOV + 1];
extern const char* text_JUL_09_OSU[POCET_JAZYKOV + 1];
extern const char* text_SEP_04_OSU[POCET_JAZYKOV + 1];
extern const char* text_OKT_21_OSU[POCET_JAZYKOV + 1];
extern const char* text_OKT_23_OSU[POCET_JAZYKOV + 1];

extern short int pocet_multi(char *_anchor, unsigned long long type);
extern short int is_printed_edition_text(char* _anchor, char* _paramname);

#endif // __DBZALTAR_H_

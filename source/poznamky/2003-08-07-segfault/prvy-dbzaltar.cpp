/***************************************************************/
/*                                                             */
/* dbzaltar.cpp                                                */
/* (c)1999-2003 | Juraj Videky | videky@breviar.sk             */
/*                                                             */
/* description | program tvoriaci stranky pre liturgiu hodin   */
/* document history                                            */
/*   09/02/2000A.D. | urobene .cpp kvoli dvojakosti funkcie    */
/*                    sviatky_svatych(); a inym veciam         */
/*   23/02/2000A.D. | ponechal som tu "stare", zle pokusy,     */
/*                    oznacene WRONG_23_02_2000                */
/*   05/04/2000A.D. | uz su dokoncene vsetky sviatky svatych.  */
/*                    odstranil som label_... pre slavnosti    */
/*                    obdobia cez rok, lebo tam nevadi, ze     */
/*                    slavnost padne na nedelu, lebo ma vyssiu */
/*                    prioritu                                 */
/*   29/03/2000A.D. | ukoncene vsetky mesiace MES_JAN - MES_DEC*/
/*   06/09/2001A.D. | tento popis                              */
/*   07/09/2001A.D. | opravene: sv. Brigity (sviatok)          */
/*   26/09/2001A.D. | opravene: sv. Terezie Benedikty (sviatok)*/
/*   2003-06-30a.D. | zmeny pre spomienku neposkvrn.srdca PM   */
/*                                                             */
/* notes |                                                     */
/*   * povodne islo o dva fajly, dbzaltar.c a dbsvaty.c        */
/*                                                             */
/***************************************************************/

//#define DETAIL_LOG_SVATY /* 22/02/2000A.D. */
//#define DETAIL_LOG_GLOBAL_DEN /* 22/02/2000A.D. */

#include "dbzaltar.h" /* 22/02/2000A.D. -- rozdelene na .h a .cpp subor */

char _anchor_head[SMALL];

#include "liturgia.h"

#include "myexpt.h" /* export do suboru alebo na konzolu printf */
/* povodne tu bolo aj include "sets.c", ale to je nizsie */
#include "mylog.h"
#include <string.h>

#define VELKONOCNA_PRIPONA  "VE"
#define POSTNA_PRIPONA      "PO"
#define CEZROCNA_PRIPONA    "CR"

/* anchor identifiers */
#define ANCHOR_POPIS        "POPIS" /* pridane 05/04/2000A.D. */
#define ANCHOR_HYMNUS       "HYMNUS"
#define ANCHOR_ANTIFONA1    "ANT1"
#define ANCHOR_ANTIFONA2    "ANT2"
#define ANCHOR_ANTIFONA3    "ANT3"
#define ANCHOR_ANTIFONA1V   "ANT1V"
#define ANCHOR_ANTIFONA2V   "ANT2V"
#define ANCHOR_ANTIFONA3V   "ANT3V"
#define ANCHOR_KCITANIE     "CIT"
#define ANCHOR_KRESPONZ     "RESP"
#define ANCHOR_MAGNIFIKAT   "MAGNIFIKAT" /* antifona na magnifikat */
#define ANCHOR_BENEDIKTUS   "BENEDIKTUS" /* antifona na benediktus */
#define ANCHOR_PROSBY       "PROSBY"
#define ANCHOR_MODLITBA     "MODLITBA"

/* special identifiers */
#define SPOM_PM_SOBOTA "SPMVS"
/* special filename indentifiers */
/* podobne ako v liturgia.h::char *nazov_obd_htm[] */
#define FILE_SPOM_PM_SOBOTA "spmvs.htm"

#define FILE_NANEBOVSTUPENIE "nan.htm" /* 10/03/2000A.D. -- kotvy v nom su podla OBD_VELKONOCNE_I */

#define ANCHOR_ZOSLANIE_DUCHA_SV "ZDS"
#define FILE_ZOSLANIE_DUCHA_SV "zds.htm" /* 10/03/2000A.D. -- kotvy v nom su podla OBD_VELKONOCNE_II, ANCHOR_ZOSLANIE_DUCHA_SV */

#define ANCHOR_NAJSV_TROJICE "TROJ"
#define FILE_NAJSV_TROJICE "troj.htm" /* 10/03/2000A.D. -- kotvy v nom su podla ANCHOR_NAJSV_TROJICE */

#define ANCHOR_KRISTA_KRALA "KRKRALA"
#define FILE_KRISTA_KRALA "krkrala.htm" /* 10/03/2000A.D. -- kotvy v nom su podla ANCHOR_KRISTA_KRALA */

#define ANCHOR_TELA_A_KRVI "TK"
#define FILE_TELA_A_KRVI "tk.htm" /* 10/03/2000A.D. -- kotvy v nom su podla ANCHOR_TELA_A_KRVI */

#define ANCHOR_SRDCA "SRDCA"
#define FILE_SRDCA "srdca.htm" /* 10/03/2000A.D. -- kotvy v nom su podla ANCHOR_SRDCA */

#define ANCHOR_SRDCA_PM "SRDCAPM"
#define FILE_SRDCA_PM "nspm.htm" /* 10/03/2000A.D. -- kotvy v nom su podla ANCHOR_SRDCA_PM */

#define ANCHOR_PM_BOHOROD "PMB"
#define FILE_PM_BOHOROD "pmb.htm" /* 14/03/2000A.D. -- kotvy v nom su podla ANCHOR_PM_BOHOROD */

#define ANCHOR_2NE_PO_NAR "2NE" /* 14/03/2000A.D. */
#define ANCHOR_ZJAVENIE_PANA "ZJV" /* 14/03/2000A.D. */

#define ANCHOR_SV_RODINY "SVROD"
#define FILE_SV_RODINY "svrod.htm" /* 14/03/2000A.D. -- kotvy v nom su podla ANCHOR_SV_RODINY */

#define ANCHOR_KRST_PANA "KRST"
#define FILE_KRST_PANA "krst.htm" /* 14/03/2000A.D. -- kotvy v nom su podla ANCHOR_KRST_PANA */

/* globalne premenne prehodene do liturgia.h, 17/02/2000A.D. */
/* ------------------------------------------------------------------- */

/* ------------------------------------------------------------------- */
/* nasledujuca pasaz bola kedysi fajl sets.c */

void _set_popis(int modlitba, const char *file, const char *anchor){ /* pridana 05/04/2000A.D. */
	switch(modlitba){
		case MODL_RANNE_CHVALY:
			strcpy(_global_modl_ranne_chvaly.popis.file, file);
			strcpy(_global_modl_ranne_chvaly.popis.anchor, anchor);
			break;
		case MODL_VESPERY:
			strcpy(_global_modl_vespery.popis.file, file);
			strcpy(_global_modl_vespery.popis.anchor, anchor);
			break;
		case MODL_PRVE_VESPERY:
			strcpy(_global_modl_prve_vespery.popis.file, file);
			strcpy(_global_modl_prve_vespery.popis.anchor, anchor);
			break;
	}/* switch(modlitba) */
}

void _set_hymnus(int modlitba, const char *file, const char *anchor){
	switch(modlitba){
		case MODL_RANNE_CHVALY:
			strcpy(_global_modl_ranne_chvaly.hymnus.file, file);
			strcpy(_global_modl_ranne_chvaly.hymnus.anchor, anchor);
			break;
#ifdef DEBUG_MODLITBA_CEZ_DEN
		case MODL_CEZ_DEN_9:
			strcpy(_global_modl_cez_den_9.hymnus.file, file);
			strcpy(_global_modl_cez_den_9.hymnus.anchor, anchor);
			break;
		case MODL_CEZ_DEN_12:
			strcpy(_global_modl_cez_den_12.hymnus.file, file);
			strcpy(_global_modl_cez_den_12.hymnus.anchor, anchor);
			break;
		case MODL_CEZ_DEN_3:
			strcpy(_global_modl_cez_den_3.hymnus.file, file);
			strcpy(_global_modl_cez_den_3.hymnus.anchor, anchor);
			break;
#endif
		case MODL_VESPERY:
			strcpy(_global_modl_vespery.hymnus.file, file);
			strcpy(_global_modl_vespery.hymnus.anchor, anchor);
			break;
		case MODL_PRVE_VESPERY:
			strcpy(_global_modl_prve_vespery.hymnus.file, file);
			strcpy(_global_modl_prve_vespery.hymnus.anchor, anchor);
			break;
	}/* switch(modlitba) */
}

void _set_antifona1(int modlitba, const char *file, const char *anchor){
	switch(modlitba){
		case MODL_RANNE_CHVALY:
			strcpy(_global_modl_ranne_chvaly.antifona1.file, file);
			strcpy(_global_modl_ranne_chvaly.antifona1.anchor, anchor);
			break;
#ifdef DEBUG_MODLITBA_CEZ_DEN
		case MODL_CEZ_DEN_9:
			strcpy(_global_modl_cez_den_9.antifona1.file, file);
			strcpy(_global_modl_cez_den_9.antifona1.anchor, anchor);
			break;
		case MODL_CEZ_DEN_12:
			strcpy(_global_modl_cez_den_12.antifona1.file, file);
			strcpy(_global_modl_cez_den_12.antifona1.anchor, anchor);
			break;
		case MODL_CEZ_DEN_3:
			strcpy(_global_modl_cez_den_3.antifona1.file, file);
			strcpy(_global_modl_cez_den_3.antifona1.anchor, anchor);
			break;
#endif
		case MODL_VESPERY:
			strcpy(_global_modl_vespery.antifona1.file, file);
			strcpy(_global_modl_vespery.antifona1.anchor, anchor);
			break;
		case MODL_PRVE_VESPERY:
			strcpy(_global_modl_prve_vespery.antifona1.file, file);
			strcpy(_global_modl_prve_vespery.antifona1.anchor, anchor);
			break;
	}/* switch(modlitba) */
}

void _set_antifona2(int modlitba, const char *file, const char *anchor){
	switch(modlitba){
		case MODL_RANNE_CHVALY:
			strcpy(_global_modl_ranne_chvaly.antifona2.file, file);
			strcpy(_global_modl_ranne_chvaly.antifona2.anchor, anchor);
			break;
#ifdef DEBUG_MODLITBA_CEZ_DEN
		case MODL_CEZ_DEN_9:
			strcpy(_global_modl_cez_den_9.antifona2.file, file);
			strcpy(_global_modl_cez_den_9.antifona2.anchor, anchor);
			break;
		case MODL_CEZ_DEN_12:
			strcpy(_global_modl_cez_den_12.antifona2.file, file);
			strcpy(_global_modl_cez_den_12.antifona2.anchor, anchor);
			break;
		case MODL_CEZ_DEN_3:
			strcpy(_global_modl_cez_den_3.antifona2.file, file);
			strcpy(_global_modl_cez_den_3.antifona2.anchor, anchor);
			break;
#endif
		case MODL_VESPERY:
			strcpy(_global_modl_vespery.antifona2.file, file);
			strcpy(_global_modl_vespery.antifona2.anchor, anchor);
			break;
		case MODL_PRVE_VESPERY:
			strcpy(_global_modl_prve_vespery.antifona2.file, file);
			strcpy(_global_modl_prve_vespery.antifona2.anchor, anchor);
			break;
	}/* switch(modlitba) */
}

void _set_antifona3(int modlitba, const char *file, const char *anchor){
	switch(modlitba){
		case MODL_RANNE_CHVALY:
			strcpy(_global_modl_ranne_chvaly.antifona3.file, file);
			strcpy(_global_modl_ranne_chvaly.antifona3.anchor, anchor);
			break;
#ifdef DEBUG_MODLITBA_CEZ_DEN
		case MODL_CEZ_DEN_9:
			strcpy(_global_modl_cez_den_9.antifona3.file, file);
			strcpy(_global_modl_cez_den_9.antifona3.anchor, anchor);
			break;
		case MODL_CEZ_DEN_12:
			strcpy(_global_modl_cez_den_12.antifona3.file, file);
			strcpy(_global_modl_cez_den_12.antifona3.anchor, anchor);
			break;
		case MODL_CEZ_DEN_3:
			strcpy(_global_modl_cez_den_3.antifona3.file, file);
			strcpy(_global_modl_cez_den_3.antifona3.anchor, anchor);
			break;
#endif
		case MODL_VESPERY:
			strcpy(_global_modl_vespery.antifona3.file, file);
			strcpy(_global_modl_vespery.antifona3.anchor, anchor);
			break;
		case MODL_PRVE_VESPERY:
			strcpy(_global_modl_prve_vespery.antifona3.file, file);
			strcpy(_global_modl_prve_vespery.antifona3.anchor, anchor);
			break;
	}/* switch(modlitba) */
}

void _set_zalm1(int modlitba, const char *file, const char *anchor){
	switch(modlitba){
		case MODL_RANNE_CHVALY:
			strcpy(_global_modl_ranne_chvaly.zalm1.file, file);
			strcpy(_global_modl_ranne_chvaly.zalm1.anchor, anchor);
			break;
#ifdef DEBUG_MODLITBA_CEZ_DEN
		case MODL_CEZ_DEN_9:
			strcpy(_global_modl_cez_den_9.zalm1.file, file);
			strcpy(_global_modl_cez_den_9.zalm1.anchor, anchor);
			break;
		case MODL_CEZ_DEN_12:
			strcpy(_global_modl_cez_den_12.zalm1.file, file);
			strcpy(_global_modl_cez_den_12.zalm1.anchor, anchor);
			break;
		case MODL_CEZ_DEN_3:
			strcpy(_global_modl_cez_den_3.zalm1.file, file);
			strcpy(_global_modl_cez_den_3.zalm1.anchor, anchor);
			break;
#endif
		case MODL_VESPERY:
			strcpy(_global_modl_vespery.zalm1.file, file);
			strcpy(_global_modl_vespery.zalm1.anchor, anchor);
			break;
		case MODL_PRVE_VESPERY:
			strcpy(_global_modl_prve_vespery.zalm1.file, file);
			strcpy(_global_modl_prve_vespery.zalm1.anchor, anchor);
			break;
	}/* switch(modlitba) */
}

#define _set_rchvalospev _set_zalm2
void _set_zalm2(int modlitba, const char *file, const char *anchor){
	switch(modlitba){
		case MODL_RANNE_CHVALY:
			strcpy(_global_modl_ranne_chvaly.zalm2.file, file);
			strcpy(_global_modl_ranne_chvaly.zalm2.anchor, anchor);
			break;
#ifdef DEBUG_MODLITBA_CEZ_DEN
		case MODL_CEZ_DEN_9:
			strcpy(_global_modl_cez_den_9.zalm2.file, file);
			strcpy(_global_modl_cez_den_9.zalm2.anchor, anchor);
			break;
		case MODL_CEZ_DEN_12:
			strcpy(_global_modl_cez_den_12.zalm2.file, file);
			strcpy(_global_modl_cez_den_12.zalm2.anchor, anchor);
			break;
		case MODL_CEZ_DEN_3:
			strcpy(_global_modl_cez_den_3.zalm2.file, file);
			strcpy(_global_modl_cez_den_3.zalm2.anchor, anchor);
			break;
#endif
		case MODL_VESPERY:
			strcpy(_global_modl_vespery.zalm2.file, file);
			strcpy(_global_modl_vespery.zalm2.anchor, anchor);
			break;
		case MODL_PRVE_VESPERY:
			strcpy(_global_modl_prve_vespery.zalm2.file, file);
			strcpy(_global_modl_prve_vespery.zalm2.anchor, anchor);
			break;
	}/* switch(modlitba) */
}

#define _set_vchvalospev _set_zalm3
void _set_zalm3(int modlitba, const char *file, const char *anchor){
	switch(modlitba){
		case MODL_RANNE_CHVALY:
			strcpy(_global_modl_ranne_chvaly.zalm3.file, file);
			strcpy(_global_modl_ranne_chvaly.zalm3.anchor, anchor);
			break;
#ifdef DEBUG_MODLITBA_CEZ_DEN
		case MODL_CEZ_DEN_9:
			strcpy(_global_modl_cez_den_9.zalm3.file, file);
			strcpy(_global_modl_cez_den_9.zalm3.anchor, anchor);
			break;
		case MODL_CEZ_DEN_12:
			strcpy(_global_modl_cez_den_12.zalm3.file, file);
			strcpy(_global_modl_cez_den_12.zalm3.anchor, anchor);
			break;
		case MODL_CEZ_DEN_3:
			strcpy(_global_modl_cez_den_3.zalm3.file, file);
			strcpy(_global_modl_cez_den_3.zalm3.anchor, anchor);
			break;
#endif
		case MODL_VESPERY:
			strcpy(_global_modl_vespery.zalm3.file, file);
			strcpy(_global_modl_vespery.zalm3.anchor, anchor);
			break;
		case MODL_PRVE_VESPERY:
			strcpy(_global_modl_prve_vespery.zalm3.file, file);
			strcpy(_global_modl_prve_vespery.zalm3.anchor, anchor);
			break;
	}/* switch(modlitba) */
}

void _set_kcitanie(int modlitba, const char *file, const char *anchor){
	switch(modlitba){
		case MODL_RANNE_CHVALY:
			strcpy(_global_modl_ranne_chvaly.kcitanie.file, file);
			strcpy(_global_modl_ranne_chvaly.kcitanie.anchor, anchor);
			break;
#ifdef DEBUG_MODLITBA_CEZ_DEN
		case MODL_CEZ_DEN_9:
			strcpy(_global_modl_cez_den_9.kcitanie.file, file);
			strcpy(_global_modl_cez_den_9.kcitanie.anchor, anchor);
			break;
		case MODL_CEZ_DEN_12:
			strcpy(_global_modl_cez_den_12.kcitanie.file, file);
			strcpy(_global_modl_cez_den_12.kcitanie.anchor, anchor);
			break;
		case MODL_CEZ_DEN_3:
			strcpy(_global_modl_cez_den_3.kcitanie.file, file);
			strcpy(_global_modl_cez_den_3.kcitanie.anchor, anchor);
			break;
#endif
		case MODL_VESPERY:
			strcpy(_global_modl_vespery.kcitanie.file, file);
			strcpy(_global_modl_vespery.kcitanie.anchor, anchor);
			break;
		case MODL_PRVE_VESPERY:
			strcpy(_global_modl_prve_vespery.kcitanie.file, file);
			strcpy(_global_modl_prve_vespery.kcitanie.anchor, anchor);
			break;
	}/* switch(modlitba) */
}

void _set_kresponz(int modlitba, const char *file, const char *anchor){
	switch(modlitba){
		case MODL_RANNE_CHVALY:
			strcpy(_global_modl_ranne_chvaly.kresponz.file, file);
			strcpy(_global_modl_ranne_chvaly.kresponz.anchor, anchor);
			break;
#ifdef DEBUG_MODLITBA_CEZ_DEN
		case MODL_CEZ_DEN_9:
			strcpy(_global_modl_cez_den_9.kresponz.file, file);
			strcpy(_global_modl_cez_den_9.kresponz.anchor, anchor);
			break;
		case MODL_CEZ_DEN_12:
			strcpy(_global_modl_cez_den_12.kresponz.file, file);
			strcpy(_global_modl_cez_den_12.kresponz.anchor, anchor);
			break;
		case MODL_CEZ_DEN_3:
			strcpy(_global_modl_cez_den_3.kresponz.file, file);
			strcpy(_global_modl_cez_den_3.kresponz.anchor, anchor);
			break;
#endif
		case MODL_VESPERY:
			strcpy(_global_modl_vespery.kresponz.file, file);
			strcpy(_global_modl_vespery.kresponz.anchor, anchor);
			break;
		case MODL_PRVE_VESPERY:
			strcpy(_global_modl_prve_vespery.kresponz.file, file);
			strcpy(_global_modl_prve_vespery.kresponz.anchor, anchor);
			break;
	}/* switch(modlitba) */
}

#define _set_magnifikat _set_benediktus
void _set_benediktus(int modlitba, const char *file, const char *anchor){
	switch(modlitba){
		case MODL_RANNE_CHVALY:
			strcpy(_global_modl_ranne_chvaly.benediktus.file, file);
			strcpy(_global_modl_ranne_chvaly.benediktus.anchor, anchor);
			break;
		case MODL_VESPERY:
			strcpy(_global_modl_vespery.benediktus.file, file);
			strcpy(_global_modl_vespery.benediktus.anchor, anchor);
			break;
		case MODL_PRVE_VESPERY:
			strcpy(_global_modl_prve_vespery.benediktus.file, file);
			strcpy(_global_modl_prve_vespery.benediktus.anchor, anchor);
			break;
	}/* switch(modlitba) */
}

void _set_prosby(int modlitba, const char *file, const char *anchor){
	switch(modlitba){
		case MODL_RANNE_CHVALY:
			strcpy(_global_modl_ranne_chvaly.prosby.file, file);
			strcpy(_global_modl_ranne_chvaly.prosby.anchor, anchor);
			break;
		case MODL_VESPERY:
			strcpy(_global_modl_vespery.prosby.file, file);
			strcpy(_global_modl_vespery.prosby.anchor, anchor);
			break;
		case MODL_PRVE_VESPERY:
			strcpy(_global_modl_prve_vespery.prosby.file, file);
			strcpy(_global_modl_prve_vespery.prosby.anchor, anchor);
			break;
	}/* switch(modlitba) */
}

void _set_modlitba(int modlitba, const char *file, const char *anchor){
	switch(modlitba){
		case MODL_RANNE_CHVALY:
			strcpy(_global_modl_ranne_chvaly.modlitba.file, file);
			strcpy(_global_modl_ranne_chvaly.modlitba.anchor, anchor);
			break;
#ifdef DEBUG_MODLITBA_CEZ_DEN
		case MODL_CEZ_DEN_9:
			strcpy(_global_modl_cez_den_9.modlitba.file, file);
			strcpy(_global_modl_cez_den_9.modlitba.anchor, anchor);
			break;
		case MODL_CEZ_DEN_12:
			strcpy(_global_modl_cez_den_12.modlitba.file, file);
			strcpy(_global_modl_cez_den_12.modlitba.anchor, anchor);
			break;
		case MODL_CEZ_DEN_3:
			strcpy(_global_modl_cez_den_3.modlitba.file, file);
			strcpy(_global_modl_cez_den_3.modlitba.anchor, anchor);
			break;
#endif
		case MODL_VESPERY:
			strcpy(_global_modl_vespery.modlitba.file, file);
			strcpy(_global_modl_vespery.modlitba.anchor, anchor);
			break;
		case MODL_PRVE_VESPERY:
			strcpy(_global_modl_prve_vespery.modlitba.file, file);
			strcpy(_global_modl_prve_vespery.modlitba.anchor, anchor);
			break;
	}/* switch(modlitba) */
}
/* koniec pasaze, co bola kedysi sets.c -- 22/02/2000A.D. */
/* ------------------------------------------------------------------- */

/* files - nazvy suborov pre zaltar styroch tyzdnov */
char _file[SMALL]; /* nazov fajlu, napr. _1ne.htm */
/* tyzzal == 1 .. 4,
 * den == 0 (DEN_NEDELA) .. 6 (DEN_SOBOTA) */
void file_name_zaltar(int den, int tyzzal){
	sprintf(_file, "_%d%s.htm", tyzzal, nazov_dn_asci[den]);
}
void file_name_litobd(int litobd){
	sprintf(_file, "%s", nazov_obd_htm[litobd]);
}

/* anchors - nazvy kotiev pre zaltar styroch tyzdnov */
char _anchor[SMALL];
/* tyzzal == 1 .. 4,
 * den == 0 (DEN_NEDELA) .. 6 (DEN_SOBOTA),
 * modlitba == MODL_...,
 * anchor == ANCHOR_... */
char pismenko_modlitby(int modlitba){
	switch(modlitba){
		case MODL_INVITATORIUM    :  return 'i';
		case MODL_RANNE_CHVALY    :  return 'r';
		case MODL_POSVATNE_CITANIE:  return 'c';
		case MODL_CEZ_DEN_9       :  return '9';
		case MODL_CEZ_DEN_12      :  return '2';
		case MODL_CEZ_DEN_3       :  return '3';
		case MODL_VESPERY         :  return 'v';
		case MODL_KOMPLETORIUM    :  return 'k';
		case MODL_NEURCENA        :  return '_';  /* toto by sa nemalo */
		case MODL_PRVE_VESPERY    :  return '1';
		case MODL_PRVE_KOMPLETORIUM: return 'p';
		case MODL_DRUHE_VESPERY   :  return '2';  /* toto by sa nemalo */
		case MODL_DRUHE_KOMPLETORIUM:return 'd';  /* toto by sa nemalo */
	}/* switch(modlitba) */
	return 0;
}/* pismenko_modlitby(); */
void anchor_name_zaltar(int den, int tyzzal, int modlitba, char *anchor){
	sprintf(_anchor, "_%d%s%c_%s",
		tyzzal, nazov_DN_asci[den], pismenko_modlitby(modlitba), anchor);
}


#define set_LOG_zaltar
//Log("   set(zaltar): %s: `%s', <!--{...:%s}-->\n", nazov_modlitby[modlitba], _file, _anchor)

void set_hymnus(int den, int tyzzal, int modlitba){
	/* prvy a treti, resp. druhy a stvrty tyzden maju rovnake */
	if(tyzzal == 3)
		tyzzal = 1;
	else if(tyzzal == 4)
		tyzzal = 2;
	file_name_zaltar(den, tyzzal);
	anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_HYMNUS);
	_set_hymnus(modlitba, _file, _anchor);
	set_LOG_zaltar;
}

void set_antifony(int den, int tyzzal, int modlitba){
	if((_global_den.litobd == OBD_VELKONOCNE_I) ||
		(_global_den.litobd == OBD_VELKONOCNE_II)){
		/* velkonocne obdobie */
		file_name_zaltar(den, tyzzal);
		anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA1V);
		_set_antifona1(modlitba, _file, _anchor);
		set_LOG_zaltar;
		anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA2V);
		_set_antifona2(modlitba, _file, _anchor);
		set_LOG_zaltar;
		/* antifona na vecerny hymnus je rovnaka pre prvy a treti,
		 * resp. druhy a stvrty tyzden zaltara */
		if((modlitba == MODL_VESPERY) || (modlitba == MODL_PRVE_VESPERY)){
			if(tyzzal == 3)
				tyzzal = 1;
			else if(tyzzal == 4)
				tyzzal = 2;
		}
		file_name_zaltar(den, tyzzal);
		anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA3V);
		_set_antifona3(modlitba, _file, _anchor);
		set_LOG_zaltar;
	}
	else{
		file_name_zaltar(den, tyzzal);
		anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA1);
		_set_antifona1(modlitba, _file, _anchor);
		set_LOG_zaltar;
		anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA2);
		_set_antifona2(modlitba, _file, _anchor);
		set_LOG_zaltar;
		/* antifona na vecerny hymnus je rovnaka pre prvy a treti,
		 * resp. druhy a stvrty tyzden zaltara */
		if((modlitba == MODL_VESPERY) || (modlitba == MODL_PRVE_VESPERY)){
			if(tyzzal == 3)
				tyzzal = 1;
			else if(tyzzal == 4)
				tyzzal = 2;
		}
		file_name_zaltar(den, tyzzal);
		anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA3);
		_set_antifona3(modlitba, _file, _anchor);
		set_LOG_zaltar;
	}
}

void set_kcitanie(int den, int tyzzal, int modlitba){
	file_name_zaltar(den, tyzzal);
	anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_KCITANIE);
	_set_kcitanie(modlitba, _file, _anchor);
	set_LOG_zaltar;
}

void set_kresponz(int den, int tyzzal, int modlitba){
	/* prvy a treti, resp. druhy a stvrty tyzden maju rovnake */
	if(tyzzal == 3)
		tyzzal = 1;
	else if(tyzzal == 4)
		tyzzal = 2;
	file_name_zaltar(den, tyzzal);
	anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_KRESPONZ);
	_set_kresponz(modlitba, _file, _anchor);
	set_LOG_zaltar;
}

void set_prosby(int den, int tyzzal, int modlitba){
	file_name_zaltar(den, tyzzal);
	anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_PROSBY);
	_set_prosby(modlitba, _file, _anchor);
	set_LOG_zaltar;
}

void set_modlitba(int den, int tyzzal, int modlitba){
	file_name_zaltar(den, tyzzal);
	anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_MODLITBA);
	_set_modlitba(modlitba, _file, _anchor);
	set_LOG_zaltar;
}

void set_benediktus(int den, int tyzzal, int modlitba){
	/* prvy a treti, resp. druhy a stvrty tyzden maju rovnake */
	if(tyzzal == 3)
		tyzzal = 1;
	else if(tyzzal == 4)
		tyzzal = 2;
	file_name_zaltar(den, tyzzal);
	anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_BENEDIKTUS);
	_set_benediktus(modlitba, _file, _anchor);
	set_LOG_zaltar;
}

void set_magnifikat(int den, int tyzzal, int modlitba){
	/* prvy a treti, resp. druhy a stvrty tyzden maju rovnake */
	if(tyzzal == 3)
		tyzzal = 1;
	else if(tyzzal == 4)
		tyzzal = 2;
	file_name_zaltar(den, tyzzal);
	anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_MAGNIFIKAT);
	_set_magnifikat(modlitba, _file, _anchor);
	set_LOG_zaltar;
}

void set_popis(int modlitba, char *file, char *anchor){
	_set_popis(modlitba, file, anchor);
	Log("   set(popis): %s: `%s', <!--{BEGIN:%s}-->\n", nazov_modlitby[modlitba], _file, _anchor);
}

void set_popis_dummy(void){
/* pridane 05/04/2000A.D. */
	Log("  teraz nastavujem POPIS (dummy)...\n");
	strcpy(_file, "dummy");
	strcpy(_anchor, "dummy");
	set_popis(MODL_RANNE_CHVALY, _file, _anchor); 
	set_popis(MODL_VESPERY, _file, _anchor);
	set_popis(MODL_PRVE_VESPERY, _file, _anchor);
}

/* zaltar();
 *
 * vstup: den == 0 (DEN_NEDELA) .. 6 (DEN_SOBOTA)
 *        tyzzal == 1 .. 4 (prvy az stvrty tyzzal zaltar
 *
 * nastavi do _global_modl_... (podla _global_modlitba) udaje potrebne
 * k modlitbe
 *
 */
void zaltar(int den, int tyzzal){
	int i, m = MODL_VESPERY;

	Log("-- zaltar(%d, %d) -- zaciatok\n", den, tyzzal);

	/* cast vseobecna pre vsetky 4 tyzdne zaltara */
	if(den == DEN_NEDELA){
		for(i = 1; i < 4; i++){
			switch(i){
				case 1:
					m = MODL_PRVE_VESPERY;
					/* set_magnifikat(den, tyzzal, m); -- vlastna */
					break;
				case 2:
					m = MODL_RANNE_CHVALY;
					/* set_benediktus(den, tyzzal, m); -- vlastna */
					break;
				case 3:
					m = MODL_VESPERY;
					/* set_magnifikat(den, tyzzal, m); -- vlastna */
					break;
			}
			set_hymnus  (den, tyzzal, m);
			set_antifony(den, tyzzal, m);
			set_kcitanie(den, tyzzal, m);
			set_kresponz(den, tyzzal, m);
			set_prosby  (den, tyzzal, m);
			/* set_modlitba(den, tyzzal, m); -- vlastna */
		}/* for */
	}
	else{/* nie nedela */
		for(i = 1; i <= 2; i++){
			switch(i){
				case 1:
					m = MODL_RANNE_CHVALY;
					set_benediktus(den, tyzzal, m);
					break;
				case 2:
					m = MODL_VESPERY;
					set_magnifikat(den, tyzzal, m);
					break;
			}
			set_hymnus  (den, tyzzal, m);
			set_antifony(den, tyzzal, m);
			set_kcitanie(den, tyzzal, m);
			set_kresponz(den, tyzzal, m);
			set_prosby  (den, tyzzal, m);
			set_modlitba(den, tyzzal, m);
		}/* for */
	}

	/* cast rovnaka pre kazdy tyzden zaltara */
	switch(den){
		case DEN_NEDELA:
			/* druhe vespery maju vzdy prvy zalm 110, 1-5.7 */
			_set_zalm1(MODL_VESPERY, "z110.htm", "ZALM110");
			/* nedelny ranny hymnus je rovnaky v prvom a tretom,
			 * resp. druhom a stvrtom tyzdni */
			if((tyzzal == 1) || (tyzzal == 3)){
				_set_zalm2(MODL_RANNE_CHVALY, "dan3_57.htm", "DAN3,57-88.56");
			}
			else{ /* if((tyzzal == 2) || (tyzzal == 4)) */
				_set_zalm1(MODL_RANNE_CHVALY, "z118.htm", "ZALM118");
				_set_zalm2(MODL_RANNE_CHVALY, "dan3_52.htm", "DAN3,52-57");
				_set_zalm3(MODL_RANNE_CHVALY, "z150.htm", "ZALM150");
			}
			/* vecerne nedelne hymny su rovnake v kazdom tyzdni */
			_set_zalm3(MODL_PRVE_VESPERY, "flp2.htm", "CHVAL_FLP2");
			if((_global_den.litobd != OBD_POSTNE_I) &&
				(_global_den.litobd != OBD_POSTNE_II_VELKY_TYZDEN)){
				_set_zalm3(MODL_VESPERY, "zjv19.htm", "CHVAL_ZJV19");
			}
			else{
				_set_zalm3(MODL_VESPERY, "1pt2.htm", "CHVAL_1PT2");
			}
			break;
		/* vecerny hymnus vsedneho dna je rovnaky v kazdom tyzdni */
		case DEN_PONDELOK:
			_set_zalm3(MODL_VESPERY, "ef1.htm", "CHVAL_EF1");
			break;
		case DEN_UTOROK:
			_set_zalm3(MODL_VESPERY, "zjv4_5.htm", "CHVAL_ZJV45");
			break;
		case DEN_STREDA:
			_set_zalm3(MODL_VESPERY, "kol1.htm", "CHVAL_KOL1");
			break;
		case DEN_STVRTOK:
			_set_zalm3(MODL_VESPERY, "zjv11.htm", "CHVAL_ZJV11");
			break;
		case DEN_PIATOK:
			/* kazdy piatok, ranne chvaly je zalm 51 */
			_set_zalm1(MODL_RANNE_CHVALY, "z51.htm", "ZALM51");
			_set_zalm3(MODL_VESPERY, "zjv15.htm", "CHVAL_ZJV15");
			break;
	}/* switch(den) */

	/* cast specificka pre kazdy tyzden zaltara */
	switch(tyzzal){
		case 1: /* prvy tyzzal zaltara */
			switch(den){
				case DEN_NEDELA:
				/* prve vespery */
					_set_zalm1(MODL_PRVE_VESPERY, "z141.htm", "ZALM141");
					_set_zalm2(MODL_PRVE_VESPERY, "z142.htm", "ZALM142");
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z63.htm", "ZALM63");
					_set_zalm3(MODL_RANNE_CHVALY, "z149.htm", "ZALM149");
				/* druhe vespery */
					_set_zalm2(MODL_VESPERY, "z114.htm", "ZALM114");
					break;

				case DEN_PONDELOK:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z5.htm", "ZALM5");
					_set_zalm2(MODL_RANNE_CHVALY, "1krn29.htm", "CHVAL_1KRN29");
					_set_zalm3(MODL_RANNE_CHVALY, "z29.htm", "ZALM29");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z11.htm", "ZALM11");
					_set_zalm2(MODL_VESPERY, "z15.htm", "ZALM15");
					break;

				case DEN_UTOROK:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z24.htm", "ZALM24");
					_set_zalm2(MODL_RANNE_CHVALY, "tob13.htm", "CHVAL_TOB13,2-8");
					_set_zalm3(MODL_RANNE_CHVALY, "z33.htm", "ZALM33");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z20.htm", "ZALM20");
					_set_zalm2(MODL_VESPERY, "z21.htm", "ZALM21");
					break;

				case DEN_STREDA:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z36.htm", "ZALM36");
					_set_zalm2(MODL_RANNE_CHVALY, "jdt16.htm", "CHVAL_JDT16");
					_set_zalm3(MODL_RANNE_CHVALY, "z47.htm", "ZALM47");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z27.htm", "ZALM27_I");
					_set_zalm2(MODL_VESPERY, "z27.htm", "ZALM27_II");
					break;

				case DEN_STVRTOK:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z57.htm", "ZALM57");
					_set_zalm2(MODL_RANNE_CHVALY, "jer31.htm", "CHVAL_JER31");
					_set_zalm3(MODL_RANNE_CHVALY, "z48.htm", "ZALM48");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z30.htm", "ZALM30");
					_set_zalm2(MODL_VESPERY, "z32.htm", "ZALM32");
					break;

				case DEN_PIATOK:
				/* ranne chvaly */
					_set_zalm2(MODL_RANNE_CHVALY, "iz45.htm", "CHVAL_IZ45");
					_set_zalm3(MODL_RANNE_CHVALY, "z100.htm", "ZALM100");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z41.htm", "ZALM41");
					_set_zalm2(MODL_VESPERY, "z46.htm", "ZALM46");
					break;

				case DEN_SOBOTA:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z119.htm", "ZALM119_KOF");
					_set_zalm2(MODL_RANNE_CHVALY, "ex15.htm", "CHVAL_EX15");
					_set_zalm3(MODL_RANNE_CHVALY, "z117.htm", "ZALM117");
					break;

				default: break;
			}; break; /* case 1 */

		case 2: /* druhy tyzzal zaltara */
			switch(den){
				case DEN_NEDELA:
				/* prve vespery */
					_set_zalm1(MODL_PRVE_VESPERY, "z119.htm", "ZALM119_NUN");
					_set_zalm2(MODL_PRVE_VESPERY, "z16.htm", "ZALM16");
				/* ranne chvaly */
				/* druhe vespery */
					_set_zalm2(MODL_VESPERY, "z115.htm", "ZALM115");
					break;

				case DEN_PONDELOK:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z42.htm", "ZALM42");
					_set_zalm2(MODL_RANNE_CHVALY, "sir36.htm", "CHVAL_SIR36");
					_set_zalm3(MODL_RANNE_CHVALY, "z19.htm", "ZALM19,2-7");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z45.htm", "ZALM45_I");
					_set_zalm2(MODL_VESPERY, "z45.htm", "ZALM45_II");
					break;

				case DEN_UTOROK:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z43.htm", "ZALM43");
					_set_zalm2(MODL_RANNE_CHVALY, "iz38.htm", "CHVAL_IZ38");
					_set_zalm3(MODL_RANNE_CHVALY, "z65.htm", "ZALM65");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z49.htm", "ZALM49_I");
					_set_zalm2(MODL_VESPERY, "z49.htm", "ZALM49_II");
					break;

				case DEN_STREDA:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z77.htm", "ZALM77");
					_set_zalm2(MODL_RANNE_CHVALY, "1sam2.htm", "CHVAL_1SAM2");
					_set_zalm3(MODL_RANNE_CHVALY, "z97.htm", "ZALM97");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z62.htm", "ZALM62");
					_set_zalm2(MODL_VESPERY, "z67.htm", "ZALM67");
					break;

				case DEN_STVRTOK:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z80.htm", "ZALM80");
					_set_zalm2(MODL_RANNE_CHVALY, "iz12.htm", "CHVAL_IZ12");
					_set_zalm3(MODL_RANNE_CHVALY, "z81.htm", "ZALM81");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z72.htm", "ZALM72_I");
					_set_zalm2(MODL_VESPERY, "z72.htm", "ZALM72_II");
					break;

				case DEN_PIATOK:
				/* ranne chvaly */
					_set_zalm2(MODL_RANNE_CHVALY, "hab3.htm", "CHVAL_HAB3");
					_set_zalm3(MODL_RANNE_CHVALY, "z147.htm", "ZALM147,12-20");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z116.htm", "ZALM116,1-9");
					_set_zalm2(MODL_VESPERY, "z121.htm", "ZALM121");
					break;

				case DEN_SOBOTA:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z92.htm", "ZALM92");
					_set_zalm2(MODL_RANNE_CHVALY, "dt32.htm", "CHVAL_DT32");
					_set_zalm3(MODL_RANNE_CHVALY, "z8.htm", "ZALM8");
					break;

				default: break;
			}; break; /* case 2 */

		case 3: /* treti tyzzal zaltara */
			switch(den){
				case DEN_NEDELA:
				/* prve vespery */
					_set_zalm1(MODL_PRVE_VESPERY, "z113.htm", "ZALM113");
					_set_zalm2(MODL_PRVE_VESPERY, "z116.htm", "ZALM116,10-19");
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z93.htm", "ZALM93");
					_set_zalm3(MODL_RANNE_CHVALY, "z148.htm", "ZALM148");
				/* druhe vespery */
					_set_zalm2(MODL_VESPERY, "z111.htm", "ZALM111");
					break;

				case DEN_PONDELOK:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z84.htm", "ZALM84");
					_set_zalm2(MODL_RANNE_CHVALY, "iz2.htm", "CHVAL_IZ2");
					_set_zalm3(MODL_RANNE_CHVALY, "z96.htm", "ZALM96");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z123.htm", "ZALM123");
					_set_zalm2(MODL_VESPERY, "z124.htm", "ZALM124");
					break;

				case DEN_UTOROK:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z85.htm", "ZALM85");
					_set_zalm2(MODL_RANNE_CHVALY, "iz26.htm", "CHVAL_IZ26");
					_set_zalm3(MODL_RANNE_CHVALY, "z67.htm", "ZALM67");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z125.htm", "ZALM125");
					_set_zalm2(MODL_VESPERY, "z131.htm", "ZALM131");
					break;

				case DEN_STREDA:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z86.htm", "ZALM86");
					_set_zalm2(MODL_RANNE_CHVALY, "iz33.htm", "CHVAL_IZ33");
					_set_zalm3(MODL_RANNE_CHVALY, "z98.htm", "ZALM98");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z126.htm", "ZALM126");
					_set_zalm2(MODL_VESPERY, "z127.htm", "ZALM127");
					break;

				case DEN_STVRTOK:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z87.htm", "ZALM87");
					_set_zalm2(MODL_RANNE_CHVALY, "iz40.htm", "CHVAL_IZ40");
					_set_zalm3(MODL_RANNE_CHVALY, "z99.htm", "ZALM99");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z132.htm", "ZALM132_I");
					_set_zalm2(MODL_VESPERY, "z132.htm", "ZALM132_II");
					break;

				case DEN_PIATOK:
				/* ranne chvaly */
					_set_zalm2(MODL_RANNE_CHVALY, "jer14.htm", "CHVAL_JER14");
					_set_zalm3(MODL_RANNE_CHVALY, "z100.htm", "ZALM100");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z135.htm", "ZALM135_I");
					_set_zalm2(MODL_VESPERY, "z135.htm", "ZALM135_II");
					break;

				case DEN_SOBOTA:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z119.htm", "ZALM119_KOF");
					_set_zalm2(MODL_RANNE_CHVALY, "mud9.htm", "CHVAL_MUD9");
					_set_zalm3(MODL_RANNE_CHVALY, "z117.htm", "ZALM117");
					break;

				default: break;
			}; break; /* case 3 */

		case 4: /* stvrty tyzzal zaltara */
			switch(den){
				case DEN_NEDELA:
				/* prve vespery */
					_set_zalm1(MODL_PRVE_VESPERY, "z122.htm", "ZALM122");
					_set_zalm2(MODL_PRVE_VESPERY, "z130.htm", "ZALM130");
				/* ranne chvaly */
				/* druhe vespery */
					_set_zalm2(MODL_VESPERY, "z112.htm", "ZALM112");
					break;

				case DEN_PONDELOK:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z90.htm", "ZALM90");
					_set_zalm2(MODL_RANNE_CHVALY, "iz42.htm", "CHVAL_IZ42");
					_set_zalm3(MODL_RANNE_CHVALY, "z135.htm", "ZALM135,1-12");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z136.htm", "ZALM136_I");
					_set_zalm2(MODL_VESPERY, "z136.htm", "ZALM136_II");
					break;

				case DEN_UTOROK:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z101.htm", "ZALM101");
					_set_zalm2(MODL_RANNE_CHVALY, "dan3_26.htm", "CHVAL_DAN3,26");
					_set_zalm3(MODL_RANNE_CHVALY, "z144.htm", "ZALM144,1-10");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z137.htm", "ZALM137");
					_set_zalm2(MODL_VESPERY, "z138.htm", "ZALM138");
					break;

				case DEN_STREDA:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z108.htm", "ZALM108");
					_set_zalm2(MODL_RANNE_CHVALY, "iz61.htm", "CHVAL_IZ61");
					_set_zalm3(MODL_RANNE_CHVALY, "z146.htm", "ZALM146");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z139.htm", "ZALM139_I");
					_set_zalm2(MODL_VESPERY, "z139.htm", "ZALM139_II");
					break;

				case DEN_STVRTOK:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z143.htm", "ZALM143");
					_set_zalm2(MODL_RANNE_CHVALY, "iz66.htm", "CHVAL_IZ66");
					_set_zalm3(MODL_RANNE_CHVALY, "z147.htm", "ZALM147,1-11");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z144.htm", "ZALM144_I");
					_set_zalm2(MODL_VESPERY, "z144.htm", "ZALM144_II");
					break;

				case DEN_PIATOK:
				/* ranne chvaly */
					_set_zalm2(MODL_RANNE_CHVALY, "tob13.htm", "CHVAL_TOB13,8-11");
					_set_zalm3(MODL_RANNE_CHVALY, "z147.htm", "ZALM147,12-20");
				/* vespery */
					_set_zalm1(MODL_VESPERY, "z145.htm", "ZALM145_I");
					_set_zalm2(MODL_VESPERY, "z145.htm", "ZALM145_II");
					break;

				case DEN_SOBOTA:
				/* ranne chvaly */
					_set_zalm1(MODL_RANNE_CHVALY, "z92.htm", "ZALM92");
					_set_zalm2(MODL_RANNE_CHVALY, "ez36.htm", "CHVAL_EZ36");
					_set_zalm3(MODL_RANNE_CHVALY, "z8.htm", "ZALM8");
					break;

				default: break;
			}; break; /* case 4 */

	}/* switch(tyzzal) */

	Log("-- zaltar(%d, %d) -- koniec\n", den, tyzzal);
}/* zaltar(); */

void _set_zalmy_velky_piatok(int modlitba){
	Log("_set_zalmy_velky_piatok(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z116.htm", "ZALM116,10-19");
		_set_zalm2(MODL_VESPERY, "z143.htm", "ZALM143");
		_set_zalm3(MODL_VESPERY, "flp2.htm", "CHVAL_FLP2");
	}
	else if(modlitba == MODL_RANNE_CHVALY){
		/* zalmy z piatka 2. tyzdna zaltara */
		Log("zalmy su z piatka 2. tyzdna zaltara...\n");
	}
	Log("_set_zalmy_velky_piatok(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_biela_sobota(int modlitba){
	Log("_set_zalmy_biela_sobota(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z116.htm", "ZALM116,10-19");
		_set_zalm2(MODL_VESPERY, "z143.htm", "ZALM143");
		_set_zalm3(MODL_VESPERY, "flp2.htm", "CHVAL_FLP2");
	}
	else if(modlitba == MODL_RANNE_CHVALY){
		_set_zalm1(MODL_RANNE_CHVALY, "z64.htm", "ZALM64");
		_set_zalm2(MODL_RANNE_CHVALY, "iz38.htm", "CHVAL_IZ38");
		_set_zalm3(MODL_RANNE_CHVALY, "z150.htm", "ZALM150");
	}
	Log("_set_zalmy_biela_sobota(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_za_zosnulych(int modlitba){
	Log("_set_zalmy_za_zosnulych(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z121.htm", "ZALM121");
		_set_zalm2(MODL_VESPERY, "z130.htm", "ZALM130");
		_set_zalm3(MODL_VESPERY, "flp2.htm", "CHVAL_FLP2");
	}
	else if(modlitba == MODL_RANNE_CHVALY){
		_set_zalm1(MODL_RANNE_CHVALY, "z51.htm", "ZALM51");
		_set_zalm2(MODL_RANNE_CHVALY, "iz38.htm", "CHVAL_IZ38");
		if(_global_den.tyzden MOD 2 == 0)
			_set_zalm3(MODL_RANNE_CHVALY, "z146.htm", "ZALM146");
		else
			_set_zalm3(MODL_RANNE_CHVALY, "z150.htm", "ZALM150");
	}
	Log("_set_zalmy_za_zosnulych(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_1nedele_rch(void){/* ranne chvaly */
	Log("_set_zalmy_1nedele_rch() -- begin\n");
	_set_zalm1(MODL_RANNE_CHVALY, "z63.htm", "ZALM63");
	_set_zalm2(MODL_RANNE_CHVALY, "dan3_57.htm", "DAN3,57-88.56");
	_set_zalm3(MODL_RANNE_CHVALY, "z149.htm", "ZALM149");
	Log("_set_zalmy_1nedele_rch() -- end\n");
}
void _set_zalmy_1nedele_v(void){/* vespery */
	Log("_set_zalmy_1nedele_v() -- begin\n");
	_set_zalm1(MODL_VESPERY, "z110.htm", "ZALM110");
	_set_zalm2(MODL_VESPERY, "z114.htm", "ZALM114");
	_set_zalm3(MODL_VESPERY, "zjv19.htm", "CHVAL_ZJV19");
	Log("_set_zalmy_1nedele_v() -- end\n");
}
void _set_zalmy_1nedele_1v(void){/* prve vespery */
	Log("_set_zalmy_1nedele_v() -- begin\n");
	_set_zalm1(MODL_PRVE_VESPERY, "z141.htm", "ZALM141");
	_set_zalm2(MODL_PRVE_VESPERY, "z142.htm", "ZALM142");
	_set_zalm3(MODL_PRVE_VESPERY, "flp2.htm", "CHVAL_FLP2");
	Log("_set_zalmy_1nedele_v() -- end\n");
}
void _set_zalmy_posviacka_chramu(int modlitba){
	Log("_set_zalmy_posviacka_chramu(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z46.htm", "ZALM46");
		_set_zalm2(MODL_VESPERY, "z122.htm", "ZALM122");
		if((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN))
			_set_zalm3(MODL_VESPERY, "zjv15.htm", "CHVAL_ZJV15");
		else
			_set_zalm3(MODL_VESPERY, "zjv19.htm", "CHVAL_ZJV19");
	}
	else if(modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	else if(modlitba == MODL_PRVE_VESPERY){
		_set_zalm1(MODL_PRVE_VESPERY, "z147.htm", "ZALM147,1-11");
		_set_zalm2(MODL_PRVE_VESPERY, "z147.htm", "ZALM147,12-20");
		if((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN))
			_set_zalm3(MODL_PRVE_VESPERY, "kol1.htm", "CHVAL_KOL1");
		else
			_set_zalm3(MODL_PRVE_VESPERY, "zjv19.htm", "CHVAL_ZJV19");
	}
	Log("_set_zalmy_posviacka_chramu(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_velkonocna_nedela(int modlitba){
	Log("_set_zalmy_velkonocna_nedela(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalmy_1nedele_v();
	}
	else if(modlitba == MODL_PRVE_VESPERY){
		_set_zalmy_1nedele_1v();
	}
	else if(modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_velkonocna_nedela(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_nanebovstupenie(int modlitba){
	Log("_set_zalmy_nanebovstupenie(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z110.htm", "ZALM110");
		_set_zalm2(MODL_VESPERY, "z47.htm", "ZALM47");
		_set_zalm3(MODL_VESPERY, "zjv11.htm", "CHVAL_ZJV11");
	}
	else if(modlitba == MODL_PRVE_VESPERY){
		_set_zalm1(MODL_PRVE_VESPERY, "z113.htm", "ZALM113");
		_set_zalm2(MODL_PRVE_VESPERY, "z117.htm", "ZALM117");
		_set_zalm3(MODL_PRVE_VESPERY, "zjv11.htm", "CHVAL_ZJV11");
	}
	else if(modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_nanebovstupenie(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_zoslanie_ducha_sv(int modlitba){
	Log("_set_zalmy_zoslanie_ducha_sv(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z110.htm", "ZALM110");
		_set_zalm2(MODL_VESPERY, "z114.htm", "ZALM114");
		_set_zalm3(MODL_VESPERY, "zjv19.htm", "CHVAL_ZJV19");
	}
	else if(modlitba == MODL_PRVE_VESPERY){
		_set_zalm1(MODL_PRVE_VESPERY, "z113.htm", "ZALM113");
		_set_zalm2(MODL_PRVE_VESPERY, "z147.htm", "ZALM147,1-11");
		_set_zalm3(MODL_PRVE_VESPERY, "zjv15.htm", "CHVAL_ZJV15");
	}
	else if(modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_zoslanie_ducha_sv(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_najsv_trojice(int modlitba){
	Log("_set_zalmy_najsv_trojice(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z110.htm", "ZALM110");
		_set_zalm2(MODL_VESPERY, "z114.htm", "ZALM114");
		_set_zalm3(MODL_VESPERY, "zjv19.htm", "CHVAL_ZJV19");
	}
	else if(modlitba == MODL_PRVE_VESPERY){
		_set_zalm1(MODL_PRVE_VESPERY, "z113.htm", "ZALM113");
		_set_zalm2(MODL_PRVE_VESPERY, "z147.htm", "ZALM147,12-20");
		_set_zalm3(MODL_PRVE_VESPERY, "ef1.htm", "CHVAL_EF1");
	}
	else if(modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_najsv_trojice(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_krista_krala(int modlitba){
	Log("_set_zalmy_krista_krala(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z110.htm", "ZALM110");
		_set_zalm2(MODL_VESPERY, "z145.htm", "ZALM145,1-13");
		_set_zalm3(MODL_VESPERY, "zjv19.htm", "CHVAL_ZJV19");
	}
	else if(modlitba == MODL_PRVE_VESPERY){
		_set_zalm1(MODL_PRVE_VESPERY, "z113.htm", "ZALM113");
		_set_zalm2(MODL_PRVE_VESPERY, "z117.htm", "ZALM117");
		_set_zalm3(MODL_PRVE_VESPERY, "zjv4_5.htm", "CHVAL_ZJV45");
	}
	else if(modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_krista_krala(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_telakrvi(int modlitba){
	Log("_set_zalmy_telakrvi(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z110.htm", "ZALM110");
		_set_zalm2(MODL_VESPERY, "z116.htm", "ZALM116,10-19");
		_set_zalm3(MODL_VESPERY, "zjv19.htm", "CHVAL_ZJV19");
	}
	else if(modlitba == MODL_PRVE_VESPERY){
		_set_zalm1(MODL_PRVE_VESPERY, "z111.htm", "ZALM111");
		_set_zalm2(MODL_PRVE_VESPERY, "z147.htm", "ZALM147,12-20");
		_set_zalm3(MODL_PRVE_VESPERY, "zjv11.htm", "CHVAL_ZJV11");
	}
	else if(modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_telakrvi(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_srdca(int modlitba){
	Log("_set_zalmy_srdca(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z110.htm", "ZALM110");
		_set_zalm2(MODL_VESPERY, "z111.htm", "ZALM111");
		_set_zalm3(MODL_VESPERY, "flp2.htm", "CHVAL_FLP2");
	}
	else if(modlitba == MODL_PRVE_VESPERY){
		_set_zalm1(MODL_PRVE_VESPERY, "z113.htm", "ZALM113");
		_set_zalm2(MODL_PRVE_VESPERY, "z146.htm", "ZALM146");
		_set_zalm3(MODL_PRVE_VESPERY, "zjv4_5.htm", "CHVAL_ZJV45");
	}
	else if(modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_srdca(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_narodenie(int modlitba){
	Log("_set_zalmy_narodenie(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z110.htm", "ZALM110");
		_set_zalm2(MODL_VESPERY, "z130.htm", "ZALM130");
		_set_zalm3(MODL_VESPERY, "kol1.htm", "CHVAL_KOL1");
	}
	else if(modlitba == MODL_PRVE_VESPERY){
		_set_zalm1(MODL_PRVE_VESPERY, "z113.htm", "ZALM113");
		_set_zalm2(MODL_PRVE_VESPERY, "z147.htm", "ZALM147,12-20");
		_set_zalm3(MODL_PRVE_VESPERY, "flp2.htm", "CHVAL_FLP2");
	}
	else if(modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_narodenie(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_zjv(int modlitba){
	Log("_set_zalmy_zjv(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z110.htm", "ZALM110");
		_set_zalm2(MODL_VESPERY, "z112.htm", "ZALM112");
		_set_zalm3(MODL_VESPERY, "zjv15.htm", "CHVAL_ZJV15");
	}
	else if(modlitba == MODL_PRVE_VESPERY){
		_set_zalm1(MODL_PRVE_VESPERY, "z135.htm", "ZALM135_I");
		_set_zalm2(MODL_PRVE_VESPERY, "z135.htm", "ZALM135_II");
		_set_zalm3(MODL_PRVE_VESPERY, "1tim3.htm", "CHVAL_1TIM3");
	}
	else if(modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_zjv(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_premenenie(int modlitba){
	Log("_set_zalmy_premenenie(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z110.htm", "ZALM110");
		_set_zalm2(MODL_VESPERY, "z121.htm", "ZALM121");
		_set_zalm3(MODL_VESPERY, "1tim3.htm", "CHVAL_1TIM3");
	}
	else if(modlitba == MODL_PRVE_VESPERY){
		_set_zalm1(MODL_PRVE_VESPERY, "z113.htm", "ZALM113");
		_set_zalm2(MODL_PRVE_VESPERY, "z117.htm", "ZALM117");
		_set_zalm3(MODL_PRVE_VESPERY, "zjv19.htm", "CHVAL_ZJV19");
	}
	else if(modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_premenenie(%s) -- end\n", nazov_modlitby[modlitba]);
}
/* vespery */
void _set_zalmy_sviatok_apostolov(int modlitba){
	Log("_set_zalmy_sviatok_apostolov(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z116.htm", "ZALM116,10-19");
		_set_zalm2(MODL_VESPERY, "z126.htm", "ZALM126");
		_set_zalm3(MODL_VESPERY, "ef1.htm", "CHVAL_EF1");
	}
	else if(modlitba == MODL_PRVE_VESPERY){
		_set_zalm1(MODL_PRVE_VESPERY, "z117.htm", "ZALM117");
		_set_zalm2(MODL_PRVE_VESPERY, "z147.htm", "ZALM147,12-20");
		_set_zalm3(MODL_PRVE_VESPERY, "ef1.htm", "CHVAL_EF1");
	}
	Log("_set_zalmy_sviatok_apostolov(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_sviatok_duch_past(int modlitba){
	Log("_set_zalmy_sviatok_duch_past(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z15.htm", "ZALM15");
		_set_zalm2(MODL_VESPERY, "z112.htm", "ZALM112");
		_set_zalm3(MODL_VESPERY, "zjv15.htm", "CHVAL_ZJV15");
	}
	else if(modlitba == MODL_PRVE_VESPERY){
		_set_zalm1(MODL_PRVE_VESPERY, "z113.htm", "ZALM113");
		_set_zalm2(MODL_PRVE_VESPERY, "z146.htm", "ZALM146");
		_set_zalm3(MODL_PRVE_VESPERY, "ef1.htm", "CHVAL_EF1");
	}
	Log("_set_zalmy_sviatok_duch_past(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_sviatok_panien(int modlitba){
	Log("_set_zalmy_sviatok_panien(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z122.htm", "ZALM122");
		_set_zalm2(MODL_VESPERY, "z127.htm", "ZALM127");
		_set_zalm3(MODL_VESPERY, "ef1.htm", "CHVAL_EF1");
	}
	else if(modlitba == MODL_PRVE_VESPERY){
		_set_zalm1(MODL_PRVE_VESPERY, "z113.htm", "ZALM113");
		_set_zalm2(MODL_PRVE_VESPERY, "z147.htm", "ZALM147,12-20");
		_set_zalm3(MODL_PRVE_VESPERY, "ef1.htm", "CHVAL_EF1");
	}
	Log("_set_zalmy_sviatok_panien(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_sviatok_muc(int modlitba){
	Log("_set_zalmy_sviatok_muc(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z116.htm", "ZALM116,1-9");
		_set_zalm2(MODL_VESPERY, "z116.htm", "ZALM116,10-19");
		_set_zalm3(MODL_VESPERY, "zjv4_5.htm", "CHVAL_ZJV45");
	}
	else if(modlitba == MODL_PRVE_VESPERY){
		_set_zalm1(MODL_PRVE_VESPERY, "z118.htm", "ZALM118_I"); /* !!! */
		_set_zalm2(MODL_PRVE_VESPERY, "z118.htm", "ZALM118_II");
		_set_zalm3(MODL_PRVE_VESPERY, "1pt2.htm", "CHVAL_1PT2");
	}
	Log("_set_zalmy_sviatok_muc(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_sviatok_krstu(int modlitba){
	Log("_set_zalmy_sviatok_krstu(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z110.htm", "ZALM110");
		_set_zalm2(MODL_VESPERY, "z130.htm", "ZALM130");
		_set_zalm3(MODL_VESPERY, "kol1.htm", "CHVAL_KOL1");
	}
	else if(modlitba == MODL_PRVE_VESPERY){
		_set_zalm1(MODL_PRVE_VESPERY, "z113.htm", "ZALM113");
		_set_zalm2(MODL_PRVE_VESPERY, "z147.htm", "ZALM147,12-20");
		_set_zalm3(MODL_PRVE_VESPERY, "flp2.htm", "CHVAL_FLP2");
	}
	Log("_set_zalmy_sviatok_krstu(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_slavnost_Cyrila_a_Metoda(int modlitba){
	Log("_set_zalmy_slavnost_Cyrila_a_Metoda(%s) -- begin\n", nazov_modlitby[modlitba]);
	_set_zalm1(modlitba, "z117.htm", "ZALM117");
	_set_zalm2(modlitba, "z146.htm", "ZALM146");
	_set_zalm3(modlitba, "ef1.htm", "CHVAL_EF1");
	Log("_set_zalmy_slavnost_Cyrila_a_Metoda(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_sv_kriz(int modlitba){
	Log("_set_zalmy_sv_kriz(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z110.htm", "ZALM110");
		_set_zalm2(MODL_VESPERY, "z116.htm", "ZALM116,10-19");
		_set_zalm3(MODL_VESPERY, "zjv4_5.htm", "CHVAL_ZJV45");
	}
	else if(modlitba == MODL_PRVE_VESPERY){
		_set_zalm1(MODL_PRVE_VESPERY, "z147.htm", "ZALM147_I");
		_set_zalm2(MODL_PRVE_VESPERY, "z147.htm", "ZALM147_II");
		_set_zalm3(MODL_PRVE_VESPERY, "flp2.htm", "CHVAL_FLP2");
	}
	else if(modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_sv_kriz(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_archanjelov(int modlitba){
	Log("_set_zalmy_archanjelov(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z8.htm", "ZALM8");
		_set_zalm2(MODL_VESPERY, "z138.htm", "ZALM138");
		_set_zalm3(MODL_VESPERY, "kol1.htm", "CHVAL_KOL1");
	}
	else if(modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_archanjelov(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_anjelov_strazcov(int modlitba){
	Log("_set_zalmy_anjelov_strazcov(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z34.htm", "ZALM34_I");
		_set_zalm2(MODL_VESPERY, "z34.htm", "ZALM34_II");
		_set_zalm3(MODL_VESPERY, "zjv11.htm", "CHVAL_ZJV11");
	}
	else if(modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_anjelov_strazcov(%s) -- end\n", nazov_modlitby[modlitba]);
}
void _set_zalmy_vsetkych_svatych(int modlitba){
	Log("_set_zalmy_vsetkych_svatych(%s) -- begin\n", nazov_modlitby[modlitba]);
	if(modlitba == MODL_VESPERY){
		_set_zalm1(MODL_VESPERY, "z110.htm", "ZALM110");
		_set_zalm2(MODL_VESPERY, "z116.htm", "ZALM116,10-19");
		_set_zalm3(MODL_VESPERY, "zjv4_5.htm", "CHVAL_ZJV45");
	}
	else if(modlitba == MODL_PRVE_VESPERY){
		_set_zalm1(MODL_PRVE_VESPERY, "z113.htm", "ZALM113");
		_set_zalm2(MODL_PRVE_VESPERY, "z147.htm", "ZALM147,12-20");
		_set_zalm3(MODL_PRVE_VESPERY, "zjv19.htm", "CHVAL_ZJV19");
	}
	else if(modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_vsetkych_svatych(%s) -- end\n", nazov_modlitby[modlitba]);
}

/* 2003-06-30 pre lahsie debugovanie obohateny vypis */
#define set_LOG_litobd Log("   set(litobd): %s: `%s', <!--{BEGIN:%s}-->\n", nazov_modlitby[modlitba], _file, _anchor)
void liturgicke_obdobie(int litobd, int tyzden, int den, int tyzzal, int poradie_svateho){
	int modlitba, t;

	Log("-- liturgicke_obdobie(%d, %d, %d, %d: svaty: %d) -- zaciatok\n",
		litobd, tyzden, den, tyzzal, poradie_svateho);


	/* 02/03/2000A.D. -- kedysi tu bolo niekedy nespustenie zaltara, ale to mozeme */
	/* if((_global_den.smer > 5) || (_global_den.smer == 2)) */
		/* najprv spustime zaltar(); */
		/* >5 -- to su [6] nedele vianocneho obdobia a nedele cez rok,
		 *             [7] sviatky panny marie a svatych,
		 *             [8] miestne sviatky,
		 *             [9] adventne vsedne dni od 17. do 24. dec. vratane, 
		 *                 dni v oktave narodenia pana, 
		 *                 vsedne dni v poste,
		 *             [10] povinne spomienky,
		 *             [11] miestne povinne spomienky,
		 *             [12] lubovolne spomienky,
		 *             [13] vsedne dni adventne do 16. decembra vratane,
		 *                  vsedne dni vianocneho obdobia 2. januarom pocnuc a sobotou po zjaveni pana konciac,
		 *                  vsedne dni cez rok.
		 */
		/* == 2:       [2] nedele adventne, postne a velkonocne,
		 *                 vsedne dni velkeho tyzdna od pondelka do stvrtka vcitane
		 */

	 /* najprv treba skontrolovat, ci nejde o nedelu, na ktoru pripadol 
	  * sviatok Premenenia Pana (6. augusta)
	  * resp. sviatok Povysenia sv. Kriza (14. septembra);
	  * ak ano, tak nenastavuj nic, lebo
	  * vsetko sa nastavilo vo funkcii sviatky_svatych()
	  * 28/03/2000A.D.
	  * rovnako tak slavnost vsetkych svatych (1. novembra) - bez ohladu na to, ci ide o nedelu,
	  * 29/03/2000A.D.
	  *
	  * 2003-06-30a.D.: rovnako tak pre slavnost sv. Petra a sv. Pavla (29. juna)
	  */
	if(
		((_global_den.denvt == DEN_NEDELA) && (_global_den.den == 6) && (_global_den.mesiac - 1 == MES_AUG)) ||
		((_global_den.denvt == DEN_NEDELA) && (_global_den.den == 29) && (_global_den.mesiac - 1 == MES_JUN)) ||
		((_global_den.denvt == DEN_NEDELA) && (_global_den.den == 14) && (_global_den.mesiac - 1 == MES_SEP)) ||
		((_global_den.den == 1) && (_global_den.mesiac - 1 == MES_NOV))
		){
		Log("premenenie pana || povysenie sv. kriza || vsetkych svatych, so return...\n");
		return;
	}

	Log("/* najprv spustime zaltar(); */\n");
	zaltar(den, tyzzal);

	file_name_litobd(litobd);
	Log("  _file == %s\n", _file);

	char c;
	/* char c sa pouziva vo vynimocnych pripadoch: napr. druha velkonocna nedela; 09/03/2000A.D. */

		/* velky switch(litobd), podla ktoreho sa priradia zakladne udaje */
	switch(litobd){
/* switch(litobd), case OBD_ADVENTNE_I -- begin ----------------------------------------------- */
		case OBD_ADVENTNE_I :/* do 16. decembra */

		/* ranne chvaly */
			/* hymnus */
			modlitba = MODL_RANNE_CHVALY;
			sprintf(_anchor, "%s%c_%s",
				nazov_OBD[litobd],
				pismenko_modlitby(modlitba),
				ANCHOR_HYMNUS);
			_set_hymnus(modlitba, _file, _anchor);
			set_LOG_litobd;
			/* kratke responzorium - rovnake pre vsetky dni okrem nedele */
			sprintf(_anchor, "%s%s%c_%s",
				nazov_OBD[litobd],
				nazov_DN_asci[DEN_UNKNOWN], /* '??' */
				pismenko_modlitby(modlitba), /* 'v' */
				ANCHOR_KRESPONZ);
			_set_kresponz(modlitba, _file, _anchor);
			set_LOG_litobd;

		/* vespery */
			/* hymnus - rovnaky pre vsetky dni */
			modlitba = MODL_VESPERY;
			sprintf(_anchor, "%s%c_%s",
				nazov_OBD[litobd],
				pismenko_modlitby(modlitba),
				ANCHOR_HYMNUS);
			_set_hymnus(modlitba, _file, _anchor);
			set_LOG_litobd;
			/* kratke responzorium - rovnake pre vsetky dni okrem nedele */
			sprintf(_anchor, "%s%s%c_%s",
				nazov_OBD[litobd],
				nazov_DN_asci[DEN_UNKNOWN], /* '??' */
				pismenko_modlitby(modlitba), /* 'v' */
				ANCHOR_KRESPONZ);
			_set_kresponz(modlitba, _file, _anchor);
			set_LOG_litobd;

			if(tyzden == 3)
				t = 1;
			else if(tyzden == 4) /* nema efekt, lebo to uz je OBD_ADVENTNE_II */
				t = 2;
			else
				t = tyzden;

			if(den == DEN_NEDELA){

			/* prve vespery */
				/* !!! sem treba zadratovat, ze 16. decembra, 1. vespery,
				 * uz maju mnohe veci z OBD_ADVENTNE_II */
				/* hymnus - rovnaky pre prve a druhe vespery */
				modlitba = MODL_PRVE_VESPERY;
				sprintf(_anchor, "%s%c_%s",
					nazov_OBD[litobd],
					pismenko_modlitby(MODL_VESPERY),
					ANCHOR_HYMNUS);
				_set_hymnus(MODL_PRVE_VESPERY, _file, _anchor);
				set_LOG_litobd;
				/* kratke responzorium - rovnaka pre prve a druhe vespery a pre vsetky nedele */
				sprintf(_anchor, "%s%s%c_%s",
					nazov_OBD[litobd],
					nazov_DN_asci[den], /* 'NE' */
					pismenko_modlitby(MODL_VESPERY), /* 'v' */
					ANCHOR_KRESPONZ);
				_set_kresponz(modlitba, _file, _anchor);
				_set_kresponz(MODL_VESPERY, _file, _anchor);
				set_LOG_litobd;
				/* antifony */
				modlitba = MODL_PRVE_VESPERY;
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_ANTIFONA1);
				_set_antifona1(modlitba, _file, _anchor);
				set_LOG_litobd;
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_ANTIFONA2);
				_set_antifona2(modlitba, _file, _anchor);
				set_LOG_litobd;
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_ANTIFONA3);
				_set_antifona3(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* kratke citanie - rovnake pre vsetky adventne nedele */
				sprintf(_anchor, "%s%s%c_%s",
					nazov_OBD[litobd],
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_KCITANIE);
				_set_kcitanie(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* magnifikat */
				sprintf(_anchor, "%s%d%s%c_%s%c",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_MAGNIFIKAT,
					_global_den.litrok);
				_set_magnifikat(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* prosby - rovnake pre prvu a tretiu, resp. druhu a stvrtu
				 * adventnu nedelu */
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					t,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_PROSBY);
				_set_prosby(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* modlitba */
				sprintf(_anchor, "%s%d%s_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					ANCHOR_MODLITBA);
				_set_modlitba(modlitba, _file, _anchor);
				set_LOG_litobd;

			/* ranne chvaly */
				/* hymnus - rovnaky pre vsetky dni */
				/* kratke responzorium - rovnake pre vsetky nedele */
				modlitba = MODL_RANNE_CHVALY;
				sprintf(_anchor, "%s%s%c_%s",
					nazov_OBD[litobd],
					nazov_DN_asci[den], /* 'NE' */
					pismenko_modlitby(modlitba), /* 'r' */
					ANCHOR_KRESPONZ);
				_set_kresponz(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* antifony */
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_ANTIFONA1);
				_set_antifona1(modlitba, _file, _anchor);
				set_LOG_litobd;
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_ANTIFONA2);
				_set_antifona2(modlitba, _file, _anchor);
				set_LOG_litobd;
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_ANTIFONA3);
				_set_antifona3(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* kratke citanie - rovnake pre vsetky adventne nedele */
				sprintf(_anchor, "%s%s%c_%s",
					nazov_OBD[litobd],
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_KCITANIE);
				_set_kcitanie(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* benediktus */
				sprintf(_anchor, "%s%d%s%c_%s%c",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_BENEDIKTUS,
					_global_den.litrok);
				_set_benediktus(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* prosby - rovnake pre prvu a tretiu, resp. druhu a stvrtu
				 * adventnu nedelu */
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					t,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_PROSBY);
				_set_prosby(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* modlitba */
				sprintf(_anchor, "%s%d%s_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					ANCHOR_MODLITBA);
				_set_modlitba(modlitba, _file, _anchor);
				set_LOG_litobd;

			/* druhe vespery */
				/* antifony */
				modlitba = MODL_VESPERY;
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_ANTIFONA1);
				_set_antifona1(modlitba, _file, _anchor);
				set_LOG_litobd;
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_ANTIFONA2);
				_set_antifona2(modlitba, _file, _anchor);
				set_LOG_litobd;
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_ANTIFONA3);
				_set_antifona3(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* kratke citanie - rovnake pre vsetky adventne nedele */
				sprintf(_anchor, "%s%s%c_%s",
					nazov_OBD[litobd],
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_KCITANIE);
				_set_kcitanie(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* magnifikat */
				sprintf(_anchor, "%s%d%s%c_%s%c",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_MAGNIFIKAT,
					_global_den.litrok);
				_set_magnifikat(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* prosby - rovnake pre prvu a tretiu, resp. druhu a stvrtu
				 * adventnu nedelu */
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					t,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_PROSBY);
				_set_prosby(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* modlitba */
				sprintf(_anchor, "%s%d%s_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					ANCHOR_MODLITBA);
				_set_modlitba(modlitba, _file, _anchor);
				set_LOG_litobd;

			}/* nedela */
			else{

			/* ranne chvaly */
				/* hymnus - rovnaky pre vsetky dni */
				/* kratke responzorium - rovnake pre vsetky vsedne dni */
				modlitba = MODL_RANNE_CHVALY;
				sprintf(_anchor, "%s%s%c_%s",
					nazov_OBD[litobd],
					nazov_DN_asci[DEN_UNKNOWN], /* '??' */
					pismenko_modlitby(modlitba), /* 'r' */
					ANCHOR_KRESPONZ);
				_set_kresponz(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* antifony - su zo vsedneho dna */
				/* kratke citanie - rovnake pre vsetky tyzdne */
				sprintf(_anchor, "%s%s%c_%s",
					nazov_OBD[litobd],
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_KCITANIE);
				_set_kcitanie(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* benediktus */
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_BENEDIKTUS);
				_set_benediktus(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* prosby - rovnake pre prvu a tretiu, resp. druhu a stvrtu
				 * adventnu nedelu */
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					t,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_PROSBY);
				_set_prosby(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* modlitba - rovnaka pre ranne chvaly aj vespery */
				sprintf(_anchor, "%s%d%s_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					ANCHOR_MODLITBA);
				_set_modlitba(modlitba, _file, _anchor);
				set_LOG_litobd;

			/* vespery */
				/* hymnus - rovnaky pre vsetky dni */
				/* kratke responzorium - rovnake pre vsetky vsedne dni */
				modlitba = MODL_VESPERY;
				sprintf(_anchor, "%s%s%c_%s",
					nazov_OBD[litobd],
					nazov_DN_asci[DEN_UNKNOWN], /* '??' */
					pismenko_modlitby(modlitba), /* 'r' */
					ANCHOR_KRESPONZ);
				_set_kresponz(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* antifony - su zo vsedneho dna */
				/* kratke citanie - rovnake pre vsetky tyzdne */
				sprintf(_anchor, "%s%s%c_%s",
					nazov_OBD[litobd],
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_KCITANIE);
				_set_kcitanie(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* magnifikat */
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_MAGNIFIKAT);
				_set_magnifikat(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* prosby - rovnake pre prvu a tretiu, resp. druhu a stvrtu
				 * adventnu nedelu */
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					t,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_PROSBY);
				_set_prosby(modlitba, _file, _anchor);
				set_LOG_litobd;
				/* modlitba - rovnaka pre ranne chvaly aj vespery */
				sprintf(_anchor, "%s%d%s_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					ANCHOR_MODLITBA);
				_set_modlitba(modlitba, _file, _anchor);
				set_LOG_litobd;

			}/* nie nedela */
			break;
/* switch(litobd), case OBD_ADVENTNE_I -- end ------------------------------------------------- */

/* switch(litobd), case OBD_ADVENTNE_II -- begin ---------------------------------------------- */
		case OBD_ADVENTNE_II:/* po 16. decembri */

			file_name_litobd(OBD_ADVENTNE_II);

		/* ranne chvaly */
			modlitba = MODL_RANNE_CHVALY;
			/* hymnus - rovnaky pre kazdy den */
			sprintf(_anchor, "%s%c_%s",
				nazov_OBD[litobd],
				pismenko_modlitby(modlitba),
				ANCHOR_HYMNUS);
			_set_hymnus(modlitba, _file, _anchor);
			set_LOG_litobd;
			/* antifony - zavisia od dna v tyzdni (PONDELOK -- SOBOTA) */
			/* kedze su rovnake na ranne chvaly aj na vespery, rozhodli sme sa
			 * dat tam 'v' */
			sprintf(_anchor, "%s%s%c_%s",
				nazov_OBD[litobd],
				nazov_DN_asci[den],
				pismenko_modlitby(MODL_VESPERY),
				ANCHOR_ANTIFONA1);
			_set_antifona1(modlitba, _file, _anchor);
			set_LOG_litobd;
			sprintf(_anchor, "%s%s%c_%s",
				nazov_OBD[litobd],
				nazov_DN_asci[den],
				pismenko_modlitby(MODL_VESPERY),
				ANCHOR_ANTIFONA2);
			_set_antifona2(modlitba, _file, _anchor);
			set_LOG_litobd;
			sprintf(_anchor, "%s%s%c_%s",
				nazov_OBD[litobd],
				nazov_DN_asci[den],
				pismenko_modlitby(MODL_VESPERY),
				ANCHOR_ANTIFONA3);
			_set_antifona3(modlitba, _file, _anchor);
			set_LOG_litobd;
			/* kratke responzorium - rovnake pre vsetky dni */
			sprintf(_anchor, "%s%s%c_%s",
				nazov_OBD[litobd],
				nazov_DN_asci[DEN_UNKNOWN],
				pismenko_modlitby(modlitba),
				ANCHOR_KRESPONZ);
			_set_kresponz(modlitba, _file, _anchor);
			set_LOG_litobd;
			/* dalsie zavisia od datumu (17. -- 24. december) */
			/* kratke citanie */
			sprintf(_anchor, "%s%d%c_%s",
				nazov_OBD[litobd],
				_global_den.den,
				pismenko_modlitby(modlitba),
				ANCHOR_KCITANIE);
			_set_kcitanie(modlitba, _file, _anchor);
			set_LOG_litobd;
			/* benediktus */
			sprintf(_anchor, "%s%d%c_%s",
				nazov_OBD[litobd],
				_global_den.den,
				pismenko_modlitby(modlitba),
				ANCHOR_BENEDIKTUS);
			_set_benediktus(modlitba, _file, _anchor);
			set_LOG_litobd;
			/* prosby */
			sprintf(_anchor, "%s%d%c_%s",
				nazov_OBD[litobd],
				_global_den.den,
				pismenko_modlitby(modlitba),
				ANCHOR_PROSBY);
			_set_prosby(modlitba, _file, _anchor);
			set_LOG_litobd;
			/* modlitba - rovnaka pre rano i vecer */
			sprintf(_anchor, "%s%d_%s",
				nazov_OBD[litobd],
				_global_den.den,
				ANCHOR_MODLITBA);
			_set_modlitba(modlitba, _file, _anchor);
			set_LOG_litobd;

		/* vespery */
			/* antifony */
			modlitba = MODL_VESPERY;
			/* hymnus - rovnaky pre kazdy den */
			sprintf(_anchor, "%s%c_%s",
				nazov_OBD[litobd],
				pismenko_modlitby(modlitba),
				ANCHOR_HYMNUS);
			_set_hymnus(modlitba, _file, _anchor);
			set_LOG_litobd;
			/* antifony - zavisia od dna v tyzdni (PONDELOK -- SOBOTA) */
			sprintf(_anchor, "%s%s%c_%s",
				nazov_OBD[litobd],
				nazov_DN_asci[den],
				pismenko_modlitby(modlitba),
				ANCHOR_ANTIFONA1);
			_set_antifona1(modlitba, _file, _anchor);
			set_LOG_litobd;
			sprintf(_anchor, "%s%s%c_%s",
				nazov_OBD[litobd],
				nazov_DN_asci[den],
				pismenko_modlitby(modlitba),
				ANCHOR_ANTIFONA2);
			_set_antifona2(modlitba, _file, _anchor);
			set_LOG_litobd;
			sprintf(_anchor, "%s%s%c_%s",
				nazov_OBD[litobd],
				nazov_DN_asci[den],
				pismenko_modlitby(modlitba),
				ANCHOR_ANTIFONA3);
			_set_antifona3(modlitba, _file, _anchor);
			set_LOG_litobd;
			/* dalsie zavisia od datumu (17. -- 24. december) */
			/* kratke responzorium - rovnake pre 17. a 18., resp.
			 * pre vsetky ostatne dni (19.-23.) */
			sprintf(_anchor, "%s%d%c_%s",
				nazov_OBD[litobd],
				(_global_den.den > 18? 19: 17),
				pismenko_modlitby(modlitba),
				ANCHOR_KRESPONZ);
			_set_kresponz(modlitba, _file, _anchor);
			set_LOG_litobd;
			/* kratke citanie */
			sprintf(_anchor, "%s%d%c_%s",
				nazov_OBD[litobd],
				_global_den.den,
				pismenko_modlitby(modlitba),
				ANCHOR_KCITANIE);
			_set_kcitanie(modlitba, _file, _anchor);
			set_LOG_litobd;
			/* magnifikat */
			sprintf(_anchor, "%s%d%c_%s",
				nazov_OBD[litobd],
				_global_den.den,
				pismenko_modlitby(modlitba),
				ANCHOR_MAGNIFIKAT);
			_set_benediktus(modlitba, _file, _anchor);
			set_LOG_litobd;
			/* prosby */
			sprintf(_anchor, "%s%d%c_%s",
				nazov_OBD[litobd],
				_global_den.den,
				pismenko_modlitby(modlitba),
				ANCHOR_PROSBY);
			_set_prosby(modlitba, _file, _anchor);
			set_LOG_litobd;
			/* modlitba - rovnaka pre rano i vecer */
			sprintf(_anchor, "%s%d_%s",
				nazov_OBD[litobd],
				_global_den.den,
				ANCHOR_MODLITBA);
			_set_modlitba(modlitba, _file, _anchor);
			set_LOG_litobd;

		/* prve vespery */
			/* antifony */
			modlitba = MODL_PRVE_VESPERY;
			/* hymnus - rovnaky ako vespery pre kazdy den */
			sprintf(_anchor, "%s%c_%s",
				nazov_OBD[litobd],
				pismenko_modlitby(MODL_VESPERY),
				ANCHOR_HYMNUS);
			_set_hymnus(modlitba, _file, _anchor);
			set_LOG_litobd;
			/* dalsie zavisia od datumu (17. -- 24. december) */
			/* magnifikat */
			sprintf(_anchor, "%s%d%c_%s",
				nazov_OBD[litobd],
				_global_den.den,
				pismenko_modlitby(MODL_VESPERY),
				ANCHOR_MAGNIFIKAT);
			_set_benediktus(modlitba, _file, _anchor);
			set_LOG_litobd;
			/* prosby */
			sprintf(_anchor, "%s%d%c_%s",
				nazov_OBD[litobd],
				_global_den.den,
				pismenko_modlitby(MODL_VESPERY),
				ANCHOR_PROSBY);
			_set_prosby(modlitba, _file, _anchor);
			set_LOG_litobd;

		/* nedela */
			/* pozor! ak tretia adventna nedela padne na 17. decembra, beru sa
			 * antifony na magnifikat, benediktus, prosby a hymny z tejto casti,
			 * avsak ostatne sa berie akoby z OBD_ADVENTNE_I, teda
			 * _file == nazov_obd_htm[OBD_ADVENTNE_I]
			 * _anchor == napr. ADV13NEr_ANT1 */
			if(den == DEN_NEDELA){
				if(tyzden == 3){/* jedine 17. decembra */

					litobd = OBD_ADVENTNE_I;
					file_name_litobd(litobd);
				/* prve vespery */
					modlitba = MODL_PRVE_VESPERY;
					/* kratke responzorium - rovnaka pre prve a druhe vespery a pre vsetky nedele */
					sprintf(_anchor, "%s%s%c_%s",
						nazov_OBD[litobd],
						nazov_DN_asci[den], /* 'NE' */
						pismenko_modlitby(MODL_VESPERY), /* 'v' */
						ANCHOR_KRESPONZ);
					_set_kresponz(modlitba, _file, _anchor);
					_set_kresponz(MODL_VESPERY, _file, _anchor);
					set_LOG_litobd;
					/* antifony */
					modlitba = MODL_PRVE_VESPERY;
					sprintf(_anchor, "%s%d%s%c_%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);
					_set_antifona1(modlitba, _file, _anchor);
					set_LOG_litobd;
					sprintf(_anchor, "%s%d%s%c_%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);
					_set_antifona2(modlitba, _file, _anchor);
					set_LOG_litobd;
					sprintf(_anchor, "%s%d%s%c_%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);
					_set_antifona3(modlitba, _file, _anchor);
					set_LOG_litobd;
					/* kratke citanie - rovnake pre vsetky adventne nedele */
					sprintf(_anchor, "%s%s%c_%s", nazov_OBD[litobd], nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_KCITANIE);
					_set_kcitanie(modlitba, _file, _anchor);
					set_LOG_litobd;
					/* modlitba */
					sprintf(_anchor, "%s%d%s_%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], ANCHOR_MODLITBA); 
					_set_modlitba(modlitba, _file, _anchor);
					set_LOG_litobd;

				/* ranne chvaly */
					/* kratke responzorium - rovnake pre vsetky nedele */
					modlitba = MODL_RANNE_CHVALY;
					sprintf(_anchor, "%s%s%c_%s", nazov_OBD[litobd], nazov_DN_asci[den], /* 'NE' */ pismenko_modlitby(modlitba), /* 'r' */ ANCHOR_KRESPONZ);
					_set_kresponz(modlitba, _file, _anchor);
					set_LOG_litobd;
					/* antifony */
					sprintf(_anchor, "%s%d%s%c_%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba),	ANCHOR_ANTIFONA1);
					_set_antifona1(modlitba, _file, _anchor);
					set_LOG_litobd;
					sprintf(_anchor, "%s%d%s%c_%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);
					_set_antifona2(modlitba, _file, _anchor);
					set_LOG_litobd;
					sprintf(_anchor, "%s%d%s%c_%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);
					_set_antifona3(modlitba, _file, _anchor);
					set_LOG_litobd;
					/* kratke citanie - rovnake pre vsetky adventne nedele */
					sprintf(_anchor, "%s%s%c_%s",
						nazov_OBD[litobd],
						nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_KCITANIE);
					_set_kcitanie(modlitba, _file, _anchor);
					set_LOG_litobd;
					/* modlitba */
					sprintf(_anchor, "%s%d%s_%s",
						nazov_OBD[litobd],
						tyzden,
						nazov_DN_asci[den],
						ANCHOR_MODLITBA);
					_set_modlitba(modlitba, _file, _anchor);
					set_LOG_litobd;

				/* druhe vespery */
					/* antifony */
					modlitba = MODL_VESPERY;
					sprintf(_anchor, "%s%d%s%c_%s",
						nazov_OBD[litobd],
						tyzden,
						nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_ANTIFONA1);
					_set_antifona1(modlitba, _file, _anchor);
					set_LOG_litobd;
					sprintf(_anchor, "%s%d%s%c_%s",
						nazov_OBD[litobd],
						tyzden,
						nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_ANTIFONA2);
					_set_antifona2(modlitba, _file, _anchor);
					set_LOG_litobd;
					sprintf(_anchor, "%s%d%s%c_%s",
						nazov_OBD[litobd],
						tyzden,
						nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_ANTIFONA3);
					_set_antifona3(modlitba, _file, _anchor);
					set_LOG_litobd;
					/* kratke citanie - rovnake pre vsetky adventne nedele */
					sprintf(_anchor, "%s%s%c_%s",
						nazov_OBD[litobd],
						nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_KCITANIE);
					_set_kcitanie(modlitba, _file, _anchor);
					set_LOG_litobd;
					/* modlitba */
					sprintf(_anchor, "%s%d%s_%s",
						nazov_OBD[litobd],
						tyzden,
						nazov_DN_asci[den],
						ANCHOR_MODLITBA);
					_set_modlitba(modlitba, _file, _anchor);
					set_LOG_litobd;

				}/* tretia adventna nedela */
				else{/* tyzden == 4, stvrta adventna nedela */

					file_name_litobd(OBD_ADVENTNE_I);
				/* prve vespery */
					/* kratke responzorium - rovnaka pre prve a druhe vespery a pre vsetky nedele */
					sprintf(_anchor, "%s%s%c_%s",
						nazov_OBD[OBD_ADVENTNE_I],
						nazov_DN_asci[den], /* 'NE' */
						pismenko_modlitby(MODL_VESPERY), /* 'v' */
						ANCHOR_KRESPONZ);
					_set_kresponz(modlitba, nazov_obd_htm[OBD_ADVENTNE_I], _anchor);
					_set_kresponz(MODL_VESPERY, _file, _anchor);
					set_LOG_litobd;
					/* antifony */
					modlitba = MODL_PRVE_VESPERY;
					sprintf(_anchor, "%s%d%s%c_%s",
						nazov_OBD[litobd],
						tyzden,
						nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_ANTIFONA1);
					_set_antifona1(modlitba, _file, _anchor);
					set_LOG_litobd;
					sprintf(_anchor, "%s%d%s%c_%s",
						nazov_OBD[litobd],
						tyzden,
						nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_ANTIFONA2);
					_set_antifona2(modlitba, _file, _anchor);
					set_LOG_litobd;
					sprintf(_anchor, "%s%d%s%c_%s",
						nazov_OBD[litobd],
						tyzden,
						nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_ANTIFONA3);
					_set_antifona3(modlitba, _file, _anchor);
					set_LOG_litobd;
					/* kratke citanie - rovnake pre vsetky adventne nedele */
					sprintf(_anchor, "%s%s%c_%s",
						nazov_OBD[OBD_ADVENTNE_I],
						nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_KCITANIE);
					_set_kcitanie(modlitba, nazov_obd_htm[OBD_ADVENTNE_I], _anchor);
					set_LOG_litobd;
					/* prosby */
					sprintf(_anchor, "%s%d%s%c_%s",
						nazov_OBD[litobd],
						4, nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_PROSBY);
					_set_prosby(modlitba, _file, _anchor);
					set_LOG_litobd;
					/* modlitba */
					sprintf(_anchor, "%s%d%s_%s",
						nazov_OBD[litobd],
						tyzden,
						nazov_DN_asci[den],
						ANCHOR_MODLITBA);
					_set_modlitba(modlitba, _file, _anchor);
					set_LOG_litobd;

				/* ak je 24. dec., vsetko pre ranne chvaly sa berie zo dna 24. */
					if(_global_den.den == 24){
						strcpy(_file, nazov_obd_htm[OBD_ADVENTNE_II]);
						/* benediktus */
						sprintf(_anchor, "%s%d%c_%s",
							nazov_OBD[litobd],
							_global_den.den,
							pismenko_modlitby(MODL_RANNE_CHVALY),
							ANCHOR_BENEDIKTUS);
						_set_benediktus(MODL_RANNE_CHVALY, _file, _anchor);
						set_LOG_litobd;
						goto label_24_DEC;
					}

				/* ranne chvaly */
					/* kratke responzorium - rovnake pre vsetky nedele */
					modlitba = MODL_RANNE_CHVALY;
					sprintf(_anchor, "%s%s%c_%s",
						nazov_OBD[OBD_ADVENTNE_I],
						nazov_DN_asci[den], /* 'NE' */
						pismenko_modlitby(modlitba), /* 'r' */
						ANCHOR_KRESPONZ);
					_set_kresponz(modlitba, nazov_obd_htm[OBD_ADVENTNE_I], _anchor);
					set_LOG_litobd;
					/* antifony */
					sprintf(_anchor, "%s%d%s%c_%s",
						nazov_OBD[litobd],
						tyzden,
						nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_ANTIFONA1);
					_set_antifona1(modlitba, _file, _anchor);
					set_LOG_litobd;
					sprintf(_anchor, "%s%d%s%c_%s",
						nazov_OBD[litobd],
						tyzden,
						nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_ANTIFONA2);
					_set_antifona2(modlitba, _file, _anchor);
					set_LOG_litobd;
					sprintf(_anchor, "%s%d%s%c_%s",
						nazov_OBD[litobd],
						tyzden,
						nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_ANTIFONA3);
					_set_antifona3(modlitba, _file, _anchor);
					set_LOG_litobd;
					/* kratke citanie - rovnake pre vsetky adventne nedele */
					sprintf(_anchor, "%s%s%c_%s",
						nazov_OBD[OBD_ADVENTNE_I],
						nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_KCITANIE);
					_set_kcitanie(modlitba, nazov_obd_htm[OBD_ADVENTNE_I], _anchor);
					set_LOG_litobd;
					/* benediktus */
					if((_global_den.den == 21) || (_global_den.den == 23)){
						/* treba brat Nebojte sa resp. Hla, splnilo sa */
					}
					else{
					  sprintf(_anchor, "%s%d%s%c_%s%c",
						  nazov_OBD[litobd],
						  tyzden,
						  nazov_DN_asci[den],
						  pismenko_modlitby(modlitba),
						  ANCHOR_BENEDIKTUS,
						  _global_den.litrok);
					  _set_benediktus(modlitba, _file, _anchor);
					}
					set_LOG_litobd;
					/* prosby */
					sprintf(_anchor, "%s%d%s%c_%s",
						nazov_OBD[litobd],
						4, nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_PROSBY);
					_set_prosby(modlitba, _file, _anchor);
					set_LOG_litobd;
					/* modlitba */
					sprintf(_anchor, "%s%d%s_%s",
						nazov_OBD[litobd],
						tyzden,
						nazov_DN_asci[den],
						ANCHOR_MODLITBA);
					_set_modlitba(modlitba, _file, _anchor);
					set_LOG_litobd;

				/* druhe vespery */
					/* antifony */
					modlitba = MODL_VESPERY;
					sprintf(_anchor, "%s%d%s%c_%s",
						nazov_OBD[litobd],
						tyzden,
						nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_ANTIFONA1);
					_set_antifona1(modlitba, _file, _anchor);
					set_LOG_litobd;
					sprintf(_anchor, "%s%d%s%c_%s",
						nazov_OBD[litobd],
						tyzden,
						nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_ANTIFONA2);
					_set_antifona2(modlitba, _file, _anchor);
					set_LOG_litobd;
					sprintf(_anchor, "%s%d%s%c_%s",
						nazov_OBD[litobd],
						tyzden,
						nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_ANTIFONA3);
					_set_antifona3(modlitba, _file, _anchor);
					set_LOG_litobd;
					/* kratke citanie - rovnake pre vsetky adventne nedele */
					sprintf(_anchor, "%s%s%c_%s",
						nazov_OBD[OBD_ADVENTNE_I],
						nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_KCITANIE);
					_set_kcitanie(modlitba, nazov_obd_htm[OBD_ADVENTNE_I], _anchor);
					set_LOG_litobd;
					/* prosby */
					sprintf(_anchor, "%s%d%s%c_%s",
						nazov_OBD[litobd],
						4, nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_PROSBY);
					_set_prosby(modlitba, _file, _anchor);
					set_LOG_litobd;
					/* modlitba */
					sprintf(_anchor, "%s%d%s_%s",
						nazov_OBD[litobd],
						tyzden,
						nazov_DN_asci[den],
						ANCHOR_MODLITBA);
					_set_modlitba(modlitba, _file, _anchor);
					set_LOG_litobd;

				}/* stvrta adventna nedela */
			}/* nedela */
			else{
				/* upravime veci pre 24. dec. */
				if(_global_den.den == 24){
label_24_DEC:
				/* iba ranne chvaly */
					modlitba = MODL_RANNE_CHVALY;
					/* hymnus - rovnaky pre kazdy den */
					/* antifony - vlastne */
					sprintf(_anchor, "%s%d%c_%s",
						nazov_OBD[litobd],
						_global_den.den,
						pismenko_modlitby(modlitba),
						ANCHOR_ANTIFONA1);
					_set_antifona1(modlitba, _file, _anchor);
					set_LOG_litobd;
					sprintf(_anchor, "%s%d%c_%s",
						nazov_OBD[litobd],
						_global_den.den,
						pismenko_modlitby(modlitba),
						ANCHOR_ANTIFONA2);
					_set_antifona2(modlitba, _file, _anchor);
					set_LOG_litobd;
					sprintf(_anchor, "%s%d%c_%s",
						nazov_OBD[litobd],
						_global_den.den,
						pismenko_modlitby(modlitba),
						ANCHOR_ANTIFONA3);
					_set_antifona3(modlitba, _file, _anchor);
					set_LOG_litobd;
					/* kratke responzorium - vlastne */
					sprintf(_anchor, "%s%d%c_%s",
						nazov_OBD[litobd],
						_global_den.den,
						pismenko_modlitby(modlitba),
						ANCHOR_KRESPONZ);
					_set_kresponz(modlitba, _file, _anchor);
					set_LOG_litobd;

				}
			}/* nie nedela -- upravenie pre 24. dec. */

			/* Vo vçedn‚ dni od 17. do 23. decembra sa ber£:
			 * invitat¢rium, hymny, Ÿ¡tania a responz¢ri , verçe, modlitba,
			 * antif¢ny a prosby na rann‚ chv ly a veçpery, ako s£ na
			 * strane 71n. Tieto Ÿasti sa potom z tretieho tì§dåa vynech vaj£.
			 * ostatne veci sa beru z predosleho */

			break;
/* switch(litobd), case OBD_ADVENTNE_II -- end ------------------------------------------------ */

/* panny marie bohorodicky */
#define _bohorod_hymnus {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	sprintf(_anchor, "%s_%c%s", ANCHOR_PM_BOHOROD, c, ANCHOR_HYMNUS);\
	_set_hymnus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _bohorod_kcitanie {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	sprintf(_anchor, "%s_%c%s", ANCHOR_PM_BOHOROD, c, ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _bohorod_kresponz {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	sprintf(_anchor, "%s_%c%s", ANCHOR_PM_BOHOROD, c, ANCHOR_KRESPONZ);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _bohorod_prosby {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_PM_BOHOROD, pismenko_modlitby(modlitba), ANCHOR_PROSBY);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _bohorod_benediktus {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_PM_BOHOROD, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _bohorod_magnifikat {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_PM_BOHOROD, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _bohorod_modlitba {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	sprintf(_anchor, "%s_%c%s", ANCHOR_PM_BOHOROD, c, ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _bohorod_antifony {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	sprintf(_anchor, "%s_%c%s", ANCHOR_PM_BOHOROD, c, ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", ANCHOR_PM_BOHOROD, c, ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", ANCHOR_PM_BOHOROD, c, ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

/* sviatok svatej rodiny */
#define _sv_rodiny_hymnus {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_SV_RODINY, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	_set_hymnus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _sv_rodiny_kcitanie {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_SV_RODINY, pismenko_modlitby(modlitba), ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _sv_rodiny_kresponz {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_SV_RODINY, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _sv_rodiny_prosby {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	sprintf(_anchor, "%s_%c%s", ANCHOR_SV_RODINY, c, ANCHOR_PROSBY);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _sv_rodiny_benediktus {\
	sprintf(_anchor, "%s_%c%s%c", ANCHOR_SV_RODINY, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, _global_den.litrok);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _sv_rodiny_magnifikat {\
	sprintf(_anchor, "%s_%c%s%c", ANCHOR_SV_RODINY, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, _global_den.litrok);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _sv_rodiny_modlitba {\
	sprintf(_anchor, "%s_%s", ANCHOR_SV_RODINY, ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _sv_rodiny_antifony {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_SV_RODINY, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", ANCHOR_SV_RODINY, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", ANCHOR_SV_RODINY, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

/* vianocne obdobie I */
#define _vian1_hymnus {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[OBD_VIANOCNE_I], c, ANCHOR_HYMNUS);\
	_set_hymnus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian1_kcitanie {\
	sprintf(_anchor, "%s_%c%s%d", nazov_OBD[OBD_VIANOCNE_I], pismenko_modlitby(modlitba), ANCHOR_KCITANIE, _global_den.den);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian1_2ne_kcitanie {\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VIANOCNE_I], ANCHOR_2NE_PO_NAR, pismenko_modlitby(modlitba), ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian1_kresponz {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	if((den == DEN_NEDELA) && (_global_den.den != 25 /* narodenie Pana */)){\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[OBD_VIANOCNE_I], c, ANCHOR_KRESPONZ, nazov_DN_asci[den]);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s", nazov_OBD[OBD_VIANOCNE_I], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	}\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian1_prosby {\
	sprintf(_anchor, "%s_%c%s%d", nazov_OBD[OBD_VIANOCNE_I], pismenko_modlitby(modlitba), ANCHOR_PROSBY, _global_den.den);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian1_2ne_prosby {\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VIANOCNE_I], ANCHOR_2NE_PO_NAR, pismenko_modlitby(modlitba), ANCHOR_PROSBY);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian1_2ne_benediktus {\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VIANOCNE_I], ANCHOR_2NE_PO_NAR, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian1_2ne_magnifikat {\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VIANOCNE_I], ANCHOR_2NE_PO_NAR, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian1_benediktus {\
	sprintf(_anchor, "%s_%c%s%d", nazov_OBD[OBD_VIANOCNE_I], pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, _global_den.den);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian1_magnifikat {\
	sprintf(_anchor, "%s_%c%s%d", nazov_OBD[OBD_VIANOCNE_I], pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, _global_den.den);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian1_2ne_modlitba {\
	sprintf(_anchor, "%s_%s%s", nazov_OBD[OBD_VIANOCNE_I], ANCHOR_2NE_PO_NAR, ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian1_2ne_antifony {\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VIANOCNE_I], ANCHOR_2NE_PO_NAR, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VIANOCNE_I], ANCHOR_2NE_PO_NAR, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VIANOCNE_I], ANCHOR_2NE_PO_NAR, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian1_modlitba {\
	if(_global_den.den == 25/* narodenie Pana */){\
		sprintf(_anchor, "%s_%c%s%d", nazov_OBD[OBD_VIANOCNE_I], pismenko_modlitby(modlitba), ANCHOR_MODLITBA, _global_den.den);\
	}\
	else{\
		sprintf(_anchor, "%s_%s%d", nazov_OBD[OBD_VIANOCNE_I], ANCHOR_MODLITBA, _global_den.den);\
	}\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _narodenie_antifony {\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[OBD_OKTAVA_NARODENIA], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[OBD_OKTAVA_NARODENIA], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[OBD_OKTAVA_NARODENIA], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

/* switch(litobd), case OBD_OKTAVA_NARODENIA -- begin ----------------------------------------- */
		case OBD_OKTAVA_NARODENIA :/* narodenie Pana -- 1. jan. */
			/* a pokracujeme ako vianocne obdobie I; 14/03/2000A.D. */
/* switch(litobd), case OBD_VIANOCNE_I -- begin ----------------------------------------------- */
		case OBD_VIANOCNE_I :/* do slavnosti zjavenia pana */

			if((_global_den.den == 26) || (_global_den.den == 27) || (_global_den.den == 28)){
				/* maju vlastnu cast zo sv. jana apostola, sv. stefana a sv. neviniatok */
			}
			else{
		/* ranne chvaly */
				modlitba = MODL_RANNE_CHVALY;
				_vian1_hymnus;
				_vian1_kcitanie;
				_vian1_kresponz;
				_vian1_benediktus;
				_vian1_prosby;
				_vian1_modlitba;
			}
		/* vespery */
			modlitba = MODL_VESPERY;
			_vian1_hymnus;
			_vian1_kcitanie;
			_vian1_kresponz;
			_vian1_magnifikat;
			_vian1_prosby;
			_vian1_modlitba;

			if(litobd == OBD_OKTAVA_NARODENIA){
				if(_global_den.den == 25){  /* narodenie Pana */
				/* prve vespery */
					modlitba = MODL_PRVE_VESPERY;
					_vian1_hymnus;
					_narodenie_antifony;
					_vian1_kcitanie;
					_vian1_kresponz;
					_vian1_magnifikat;
					_vian1_prosby;
					_vian1_modlitba;
					_set_zalmy_narodenie(modlitba);
				}
			/* ranne chvaly */
				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_narodenie(modlitba);
				_narodenie_antifony;
			/* druhe vespery */
				modlitba = MODL_VESPERY;
				_set_zalmy_narodenie(modlitba);
				_narodenie_antifony;
			}

			if((_global_den.den == 1) && (_global_den.mesiac == 1)){ /* Panny Marie Bohorodicky */
				/* panny marie bohorodicky; 14/03/2000A.D. */
				strcpy(_file, FILE_PM_BOHOROD);
				strcpy(_anchor, ANCHOR_PM_BOHOROD);
				Log("  ide o slavnost najsv. trojice.: _file = `%s', _anchor = %s...\n", _file, _anchor);
				modlitba = MODL_PRVE_VESPERY;
				_set_zalmy_sviatok_panien(modlitba);
				_bohorod_hymnus;
				_bohorod_kcitanie;
				_bohorod_kresponz;
				_bohorod_magnifikat;
				_bohorod_prosby;
				_bohorod_modlitba;
				_bohorod_antifony;
				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_1nedele_rch();
				_bohorod_hymnus;
				_bohorod_kcitanie;
				_bohorod_kresponz;
				_bohorod_benediktus;
				_bohorod_prosby;
				_bohorod_modlitba;
				_bohorod_antifony;
				modlitba = MODL_VESPERY;
				_set_zalmy_sviatok_panien(modlitba);
				_bohorod_hymnus;
				_bohorod_kcitanie;
				_bohorod_kresponz;
				_bohorod_magnifikat;
				_bohorod_prosby;
				_bohorod_modlitba;
				_bohorod_antifony;
			}
			else if((_global_den.denvt == DEN_NEDELA) && (_global_den.mesiac - 1 == MES_JAN)){ /* druha nedela po narodeni pana */
			/* prve vespery */
				modlitba = MODL_PRVE_VESPERY;
				_vian1_hymnus;
				_vian1_2ne_kcitanie;
				_vian1_kresponz;
				_vian1_2ne_magnifikat;
				_vian1_2ne_prosby;
				_vian1_2ne_modlitba;
				_vian1_2ne_antifony;
			/* ranne chvaly */
				modlitba = MODL_RANNE_CHVALY;
				_vian1_2ne_kcitanie;
				_vian1_2ne_benediktus;
				_vian1_2ne_prosby;
				_vian1_2ne_antifony;
				_vian1_2ne_modlitba;
			/* druhe vespery */
				modlitba = MODL_VESPERY;
				_vian1_2ne_kcitanie;
				_vian1_2ne_magnifikat;
				_vian1_2ne_prosby;
				_vian1_2ne_antifony;
				_vian1_2ne_modlitba;
			}
			else if(_global_den.denvr == _global_r._SVATEJ_RODINY.denvr){
				/* sviatok svatej rodiny; 14/03/2000A.D. */
				strcpy(_file, FILE_SV_RODINY);
				strcpy(_anchor, ANCHOR_SV_RODINY);
				Log("  ide o slavnost najsv. trojice.: _file = `%s', _anchor = %s...\n", _file, _anchor);
				modlitba = MODL_PRVE_VESPERY;
				_set_zalmy_sviatok_panien(modlitba);
				_sv_rodiny_hymnus;
				_sv_rodiny_kcitanie;
				_sv_rodiny_kresponz;
				_sv_rodiny_magnifikat;
				_sv_rodiny_prosby;
				_sv_rodiny_modlitba;
				_sv_rodiny_antifony;
				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_1nedele_rch();
				_sv_rodiny_hymnus;
				_sv_rodiny_kcitanie;
				_sv_rodiny_kresponz;
				_sv_rodiny_benediktus;
				_sv_rodiny_prosby;
				_sv_rodiny_modlitba;
				_sv_rodiny_antifony;
				modlitba = MODL_VESPERY;
				_set_zalmy_sviatok_panien(modlitba);
				_sv_rodiny_hymnus;
				_sv_rodiny_kcitanie;
				_sv_rodiny_kresponz;
				_sv_rodiny_magnifikat;
				_sv_rodiny_prosby;
				_sv_rodiny_modlitba;
				_sv_rodiny_antifony;
			}
			break;
/* switch(litobd), case OBD_OKTAVA_NARODENIA -- end ------------------------------------------- */
/* switch(litobd), case OBD_VIANOCNE_I -- end ------------------------------------------------- */

/* switch(litobd), case OBD_VIANOCNE_II -- begin ---------------------------------------------- */
		case OBD_VIANOCNE_II: {/* po slavnosti zjavenia pana */
/* vianocne obdobie II */
#define _vian2_hymnus {\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[OBD_VIANOCNE_II], pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	_set_hymnus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _zjv_kcitanie {\
	sprintf(_anchor, "%s_%c%s%d", nazov_OBD[OBD_VIANOCNE_II], pismenko_modlitby(modlitba), ANCHOR_KCITANIE, _global_den.den);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian2_kresponz {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[OBD_VIANOCNE_II], c, ANCHOR_KRESPONZ);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian2_prosby {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	sprintf(_anchor, "%s_%c%s%d", nazov_OBD[OBD_VIANOCNE_II], c, ANCHOR_PROSBY, _global_den.den);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian2_benediktus {\
	sprintf(_anchor, "%s_%c%s%d", nazov_OBD[OBD_VIANOCNE_II], pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, _global_den.den);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian2_magnifikat {\
	sprintf(_anchor, "%s_%c%s%d", nazov_OBD[OBD_VIANOCNE_II], pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, _global_den.den);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian2_modlitba {\
	sprintf(_anchor, "%s_%s%d", nazov_OBD[OBD_VIANOCNE_II], ANCHOR_MODLITBA, _global_den.den);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _zjv_antifony {\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VIANOCNE_II], ANCHOR_ZJAVENIE_PANA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VIANOCNE_II], ANCHOR_ZJAVENIE_PANA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VIANOCNE_II], ANCHOR_ZJAVENIE_PANA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
									 
		/* ranne chvaly */
			modlitba = MODL_RANNE_CHVALY;
			_vian2_hymnus;
			_vian2_kresponz;
			_vian2_benediktus;
			_vian2_prosby;
			_vian2_modlitba;
		/* vespery */
			modlitba = MODL_VESPERY;
			_vian2_hymnus;
			_vian2_kresponz;
			_vian2_magnifikat;
			_vian2_prosby;
			_vian2_modlitba;

			if((_global_den.den == 6) && (_global_den.mesiac == 1)){ /* zjavenie pana */
			/* prve vespery */
				modlitba = MODL_PRVE_VESPERY;
				_vian2_hymnus;
				_zjv_antifony;
				_zjv_kcitanie;
				_vian2_kresponz;
				_vian2_magnifikat;
				_vian2_prosby;
				_vian2_modlitba;
				_set_zalmy_zjv(modlitba);
			/* ranne chvaly */
				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_zjv(modlitba);
				_zjv_kcitanie;
				_zjv_antifony;
			/* druhe vespery */
				modlitba = MODL_VESPERY;
				_set_zalmy_zjv(modlitba);
				_zjv_kcitanie;
				_zjv_antifony;
			}/* zjavenie pana */
			else{
				/* vsedny den vianocneho obdobia II -- citania podla vian.obd.I */
				strcpy(_file, nazov_obd_htm[OBD_VIANOCNE_I]);
				if(_global_den.den == 8){
					modlitba = MODL_RANNE_CHVALY;
					_global_den.den = 31;
					_vian1_kcitanie;
					modlitba = MODL_VESPERY;
					_global_den.den = 28;
					_vian1_kcitanie;
				}
				else{
					if(_global_den.den == 7){
						_global_den.den = 30;
						modlitba = MODL_RANNE_CHVALY;
						_vian1_kcitanie;
						modlitba = MODL_VESPERY;
						_vian1_kcitanie;
					}
					else{/* den == 9, 10, 11, 12 */
						_global_den.den = _global_den.den - 7; /* den == 2, 3, 4, 5 */
						modlitba = MODL_RANNE_CHVALY;
						_vian1_kcitanie;
						modlitba = MODL_VESPERY;
						_vian1_kcitanie;					
					}
				}
			}/* obycajny den vian.obd. II -- priradenie citania */

			}
			break;
/* switch(litobd), case OBD_VIANOCNE_II -- end ------------------------------------------------ */

/* switch(litobd), case OBD_CEZ_ROK -- begin -------------------------------------------------- */
		case OBD_CEZ_ROK:{

/* najsv. trojice */
#define _troj_hymnus {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_NAJSV_TROJICE, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	_set_hymnus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _troj_kcitanie {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_NAJSV_TROJICE, pismenko_modlitby(modlitba), ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _troj_kresponz {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_NAJSV_TROJICE, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _troj_prosby {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_NAJSV_TROJICE, pismenko_modlitby(modlitba), ANCHOR_PROSBY);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _troj_benediktus {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_NAJSV_TROJICE, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _troj_magnifikat {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_NAJSV_TROJICE, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _troj_modlitba {\
	sprintf(_anchor, "%s_%s", ANCHOR_NAJSV_TROJICE, ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _troj_ne_antifony {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_NAJSV_TROJICE, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", ANCHOR_NAJSV_TROJICE, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", ANCHOR_NAJSV_TROJICE, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

/* krista krala */
#define _krkrala_hymnus {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_KRISTA_KRALA, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	_set_hymnus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _krkrala_kcitanie {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_KRISTA_KRALA, pismenko_modlitby(modlitba), ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _krkrala_kresponz {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_KRISTA_KRALA, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _krkrala_prosby {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_KRISTA_KRALA, pismenko_modlitby(modlitba), ANCHOR_PROSBY);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _krkrala_benediktus {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_KRISTA_KRALA, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _krkrala_magnifikat {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_KRISTA_KRALA, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _krkrala_modlitba {\
	sprintf(_anchor, "%s_%s", ANCHOR_KRISTA_KRALA, ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _krkrala_ne_antifony {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_KRISTA_KRALA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", ANCHOR_KRISTA_KRALA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", ANCHOR_KRISTA_KRALA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

/* najsv. tela a krvi jezisovej */
#define _telakrvi_hymnus {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_TELA_A_KRVI, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	_set_hymnus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _telakrvi_kcitanie {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_TELA_A_KRVI, pismenko_modlitby(modlitba), ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _telakrvi_kresponz {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_TELA_A_KRVI, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _telakrvi_prosby {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_TELA_A_KRVI, pismenko_modlitby(modlitba), ANCHOR_PROSBY);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _telakrvi_benediktus {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_TELA_A_KRVI, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _telakrvi_magnifikat {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_TELA_A_KRVI, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _telakrvi_modlitba {\
	sprintf(_anchor, "%s_%s", ANCHOR_TELA_A_KRVI, ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _telakrvi_ne_antifony {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_TELA_A_KRVI, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", ANCHOR_TELA_A_KRVI, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", ANCHOR_TELA_A_KRVI, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

/* najsv. srdca jezisovho */
#define _srdca_hymnus {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_SRDCA, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	_set_hymnus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _srdca_kcitanie {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_SRDCA, pismenko_modlitby(modlitba), ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _srdca_kresponz {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_SRDCA, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _srdca_prosby {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_SRDCA, pismenko_modlitby(modlitba), ANCHOR_PROSBY);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _srdca_benediktus {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_SRDCA, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _srdca_magnifikat {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_SRDCA, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _srdca_modlitba {\
	sprintf(_anchor, "%s_%s", ANCHOR_SRDCA, ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _srdca_ne_antifony {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_SRDCA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", ANCHOR_SRDCA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", ANCHOR_SRDCA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

/* krista krala */
#define _krst_hymnus {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_KRST_PANA, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	_set_hymnus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _krst_kcitanie {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_KRST_PANA, pismenko_modlitby(modlitba), ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _krst_kresponz {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_KRST_PANA, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _krst_prosby {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_KRST_PANA, pismenko_modlitby(modlitba), ANCHOR_PROSBY);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _krst_benediktus {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_KRST_PANA, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _krst_magnifikat {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_KRST_PANA, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _krst_modlitba {\
	sprintf(_anchor, "%s_%s", ANCHOR_KRST_PANA, ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _krst_ne_antifony {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_KRST_PANA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", ANCHOR_KRST_PANA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", ANCHOR_KRST_PANA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

					/* najprv treba skontrolovat, ci nejde o nedelu, na ktoru pripadol 
					 * sviatok Premenenia Pana (6. augusta); ak ano, tak nenastavuj nic, lebo
					 * vsetko sa nastavilo vo funkcii sviatky_svatych()
					 * 28/03/2000A.D.
					 */
				if((_global_den.denvt == DEN_NEDELA) && (_global_den.den == 6) && (_global_den.mesiac - 1 == MES_AUG)){
					Log("premenenie pana, so break...\n");
					break;
				}
				if(_global_den.denvt == DEN_NEDELA){
					/* ak je specialna, tak _file sa nastavi v dalsom, 10/03/2000A.D. */
					file_name_litobd(OBD_CEZ_ROK);
					/* benediktus */
					modlitba = MODL_RANNE_CHVALY;
					sprintf(_anchor, "_%d%s%c_%s%c", tyzden, nazov_DN_asci[den], /* 'NE', nedela */ pismenko_modlitby(MODL_RANNE_CHVALY), ANCHOR_BENEDIKTUS, _global_den.litrok);
					_set_benediktus(MODL_RANNE_CHVALY, _file, _anchor);
					set_LOG_litobd;
					/* magnifikat 1 */
					modlitba = MODL_PRVE_VESPERY;
					sprintf(_anchor, "_%d%s%c_%s%c", tyzden, nazov_DN_asci[den], /* 'NE', nedela */ pismenko_modlitby(MODL_PRVE_VESPERY), ANCHOR_MAGNIFIKAT, _global_den.litrok);
					_set_magnifikat(MODL_PRVE_VESPERY, _file, _anchor);
					set_LOG_litobd;
					/* magnifikat v */
					modlitba = MODL_VESPERY;
					sprintf(_anchor, "_%d%s%c_%s%c", tyzden, nazov_DN_asci[den], /* 'NE', nedela */ pismenko_modlitby(MODL_VESPERY), ANCHOR_MAGNIFIKAT, _global_den.litrok);
					_set_magnifikat(MODL_VESPERY, _file, _anchor);
					set_LOG_litobd;
					/* modlitba */
					sprintf(_anchor, "_%d%s_%s", tyzden, nazov_DN_asci[den], /* 'NE', nedela */ ANCHOR_MODLITBA); 
					modlitba = MODL_RANNE_CHVALY;
					_set_modlitba(MODL_RANNE_CHVALY, _file, _anchor);
					set_LOG_litobd;
					modlitba = MODL_PRVE_VESPERY;
					_set_modlitba(MODL_PRVE_VESPERY, _file, _anchor);
					set_LOG_litobd;
					modlitba = MODL_VESPERY;
					_set_modlitba(MODL_VESPERY, _file, _anchor);
					set_LOG_litobd;

					/* 10/03/2000A.D. */
					if(_global_den.denvr == (_global_r._ZOSLANIE_DUCHA_SV.denvr + 7)){
						/* najsv. trojice; 10/03/2000A.D. */
						strcpy(_file, FILE_NAJSV_TROJICE);
						strcpy(_anchor, ANCHOR_NAJSV_TROJICE);
						Log("  ide o slavnost najsv. trojice.: _file = `%s', _anchor = %s...\n", _file, _anchor);
						modlitba = MODL_PRVE_VESPERY;
						_set_zalmy_najsv_trojice(modlitba);
						_troj_hymnus;
						_troj_kcitanie;
						_troj_kresponz;
						_troj_magnifikat;
						_troj_prosby;
						_troj_modlitba;
						_troj_ne_antifony;
						modlitba = MODL_RANNE_CHVALY;
						_set_zalmy_najsv_trojice(modlitba);
						_troj_hymnus;
						_troj_kcitanie;
						_troj_kresponz;
						_troj_benediktus;
						_troj_prosby;
						_troj_modlitba;
						_troj_ne_antifony;
						modlitba = MODL_VESPERY;
						_set_zalmy_najsv_trojice(modlitba);
						_troj_hymnus;
						_troj_kcitanie;
						_troj_kresponz;
						_troj_magnifikat;
						_troj_prosby;
						_troj_modlitba;
						_troj_ne_antifony;
					}/* najsv. trojice */
					else if(tyzden == 34){
						/* krista krala -- 34. nedela obdobia `cez rok'; 10/03/2000A.D. */
						strcpy(_file, FILE_KRISTA_KRALA);
						strcpy(_anchor, ANCHOR_KRISTA_KRALA);
						Log("  ide o slavnost najsv. trojice.: _file = `%s', _anchor = %s...\n", _file, _anchor);
						modlitba = MODL_PRVE_VESPERY;
						_set_zalmy_krista_krala(modlitba);
						_krkrala_hymnus;
						_krkrala_kcitanie;
						_krkrala_kresponz;
						_krkrala_magnifikat;
						_krkrala_prosby;
						_krkrala_modlitba;
						_krkrala_ne_antifony;
						modlitba = MODL_RANNE_CHVALY;
						_set_zalmy_krista_krala(modlitba);
						_krkrala_hymnus;
						_krkrala_kcitanie;
						_krkrala_kresponz;
						_krkrala_benediktus;
						_krkrala_prosby;
						_krkrala_modlitba;
						_krkrala_ne_antifony;
						modlitba = MODL_VESPERY;
						_set_zalmy_krista_krala(modlitba);
						_krkrala_hymnus;
						_krkrala_kcitanie;
						_krkrala_kresponz;
						_krkrala_magnifikat;
						_krkrala_prosby;
						_krkrala_modlitba;
						_krkrala_ne_antifony;
					}/* krista krala */
					else if((tyzden == 1) && (_global_den.denvr == _global_r._KRST_KRISTA_PANA.denvr)){
						/* krst krista pana -- 1. nedela obdobia `cez rok'; 14/03/2000A.D. */
						strcpy(_file, FILE_KRST_PANA);
						strcpy(_anchor, ANCHOR_KRST_PANA);
						Log("  ide o slavnost najsv. trojice.: _file = `%s', _anchor = %s...\n", _file, _anchor);
						modlitba = MODL_PRVE_VESPERY;
						_set_zalmy_zjv(modlitba);
						_krst_hymnus;
						_krst_kcitanie;
						_krst_kresponz;
						_krst_magnifikat;
						_krst_prosby;
						_krst_modlitba;
						_krst_ne_antifony;
						modlitba = MODL_RANNE_CHVALY;
						_set_zalmy_zjv(modlitba);
						_krst_hymnus;
						_krst_kcitanie;
						_krst_kresponz;
						_krst_benediktus;
						_krst_prosby;
						_krst_modlitba;
						_krst_ne_antifony;
						modlitba = MODL_VESPERY;
						_set_zalmy_zjv(modlitba);
						_krst_hymnus;
						_krst_kcitanie;
						_krst_kresponz;
						_krst_magnifikat;
						_krst_prosby;
						_krst_modlitba;
						_krst_ne_antifony;
					}/* krst krista pana */
				}/* nedela v obdobi cez rok */
				else{
					if(_global_den.denvr == (_global_r._ZOSLANIE_DUCHA_SV.denvr + 11)){
						/* najsv. kristovho tela a krvi; 10/03/2000A.D. */
						strcpy(_file, FILE_TELA_A_KRVI);
						strcpy(_anchor, ANCHOR_TELA_A_KRVI);
						Log("  ide o slavnost najsv. trojice.: _file = `%s', _anchor = %s...\n", _file, _anchor);
						modlitba = MODL_PRVE_VESPERY;
						_set_zalmy_telakrvi(modlitba);
						_telakrvi_hymnus;
						_telakrvi_kcitanie;
						_telakrvi_kresponz;
						_telakrvi_magnifikat;
						_telakrvi_prosby;
						_telakrvi_modlitba;
						_telakrvi_ne_antifony;
						modlitba = MODL_RANNE_CHVALY;
						_set_zalmy_telakrvi(modlitba);
						_telakrvi_hymnus;
						_telakrvi_kcitanie;
						_telakrvi_kresponz;
						_telakrvi_benediktus;
						_telakrvi_prosby;
						_telakrvi_modlitba;
						_telakrvi_ne_antifony;
						modlitba = MODL_VESPERY;
						_set_zalmy_telakrvi(modlitba);
						_telakrvi_hymnus;
						_telakrvi_kcitanie;
						_telakrvi_kresponz;
						_telakrvi_magnifikat;
						_telakrvi_prosby;
						_telakrvi_modlitba;
						_telakrvi_ne_antifony;
					}/* tela a krvi */
					else if(_global_den.denvr == (_global_r._ZOSLANIE_DUCHA_SV.denvr + 19)){
						/* najsv. srdca jezisovho; 10/03/2000A.D. */
						strcpy(_file, FILE_SRDCA);
						strcpy(_anchor, ANCHOR_SRDCA);
						Log("  ide o slavnost najsv. trojice.: _file = `%s', _anchor = %s...\n", _file, _anchor);
						modlitba = MODL_PRVE_VESPERY;
						_set_zalmy_srdca(modlitba);
						_srdca_hymnus;
						_srdca_kcitanie;
						_srdca_kresponz;
						_srdca_magnifikat;
						_srdca_prosby;
						_srdca_modlitba;
						_srdca_ne_antifony;
						modlitba = MODL_RANNE_CHVALY;
						_set_zalmy_srdca(modlitba);
						_srdca_hymnus;
						_srdca_kcitanie;
						_srdca_kresponz;
						_srdca_benediktus;
						_srdca_prosby;
						_srdca_modlitba;
						_srdca_ne_antifony;
						modlitba = MODL_VESPERY;
						_set_zalmy_srdca(modlitba);
						_srdca_hymnus;
						_srdca_kcitanie;
						_srdca_kresponz;
						_srdca_magnifikat;
						_srdca_prosby;
						_srdca_modlitba;
						_srdca_ne_antifony;
					}/* srdca */
					else if(_global_den.denvr == (_global_r._ZOSLANIE_DUCHA_SV.denvr + 20)){
						/* neposkvrneneho srdca prebl. panny marie; 04/07/2000A.D. */
						Log("  (hoci tu nic nenastavujem) ide o spomienku neposkvrneneho srdca prebl. panny marie\n");
					}
				}/* nie nedela */
			}
			break;
/* switch(litobd), case OBD_CEZ_ROK -- end ---------------------------------------------------- */

/* switch(litobd), case OBD_POSTNE_I -- begin ------------------------------------------------- */
		case OBD_POSTNE_I:/* do soboty v piatom tyzdni */
		/* 06/03/2000A.D. */
#define _post1_hymnus {\
	if(den == DEN_NEDELA){\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), nazov_DN_asci[den], ANCHOR_HYMNUS);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	}\
	_set_hymnus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _post1_kcitanie {\
	if(tyzden != 5){\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), nazov_DN_asci[den], ANCHOR_KCITANIE);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s%s%d", nazov_OBD[litobd], pismenko_modlitby(modlitba), nazov_DN_asci[den], ANCHOR_KCITANIE, tyzden);\
	}\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _post1_kresponz {\
	if(den == DEN_NEDELA){\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ, nazov_DN_asci[den]);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	}\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _post1_prosby {\
	if((den == DEN_STREDA) && (tyzden == 0) && (modlitba == MODL_RANNE_CHVALY)){\
		sprintf(_anchor, "%s_%c%s%sPOPOL", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_PROSBY, nazov_DN_asci[den]);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_PROSBY, t, nazov_DN_asci[den]);\
	}\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _post1_benediktus {\
	if(den == DEN_NEDELA){\
		sprintf(_anchor, "%s_%c%s%d%s%c", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, tyzden, nazov_DN_asci[den], _global_den.litrok);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, tyzden, nazov_DN_asci[den]);\
	}\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _post1_magnifikat {\
	if(den == DEN_NEDELA){\
		sprintf(_anchor, "%s_%c%s%d%s%c", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, tyzden, nazov_DN_asci[den], _global_den.litrok);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, tyzden, nazov_DN_asci[den]);\
	}\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _post1_modlitba {\
	sprintf(_anchor, "%s_%s%d%s", nazov_OBD[litobd], ANCHOR_MODLITBA, tyzden, nazov_DN_asci[den]);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _post1_ne_antifony {\
	sprintf(_anchor, "%s_%d%s%c%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%d%s%c%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%d%s%c%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

			t = tyzden MOD 2;

		/* ranne chvaly */
			modlitba = MODL_RANNE_CHVALY;
			_post1_hymnus;
			_post1_kcitanie;
			_post1_kresponz;
			_post1_benediktus;
			_post1_prosby;
			_post1_modlitba;
		/* vespery */
			modlitba = MODL_VESPERY;
			_post1_hymnus;
			_post1_kcitanie;
			_post1_kresponz;
			_post1_magnifikat;
			_post1_prosby;
			_post1_modlitba;

			if(den == DEN_NEDELA){

			/* prve vespery */
				modlitba = MODL_PRVE_VESPERY;
				_post1_hymnus;
				_post1_ne_antifony;
				_post1_kcitanie;
				_post1_kresponz;
				_post1_magnifikat;
				_post1_prosby;
				_post1_modlitba;
			/* ranne chvaly */
				modlitba = MODL_RANNE_CHVALY;
				_post1_ne_antifony;
			/* druhe vespery */
				modlitba = MODL_VESPERY;
				_post1_ne_antifony;
			}/* nedela */
			else{
			}/* nie nedela */
			break;
/* switch(litobd), case OBD_POSTNE_I -- end --------------------------------------------------- */

/* switch(litobd), case OBD_POSTNE_II -- begin ------------------------------------------------ */
		case OBD_POSTNE_II_VELKY_TYZDEN:/* velky tyzden */
			/* 08/03/2000A.D. */
#define _post2_hymnus {\
	if((den == DEN_STVRTOK) && (modlitba == MODL_VESPERY)){\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), nazov_DN_asci[den], ANCHOR_HYMNUS);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	}\
	_set_hymnus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _post2_kcitanie {\
	if((den == DEN_NEDELA) && (modlitba == MODL_RANNE_CHVALY)){\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), nazov_DN_asci[den], ANCHOR_KCITANIE);\
		_set_kcitanie(modlitba, _file, _anchor);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s%s%d", nazov_OBD[OBD_POSTNE_I], pismenko_modlitby(modlitba), nazov_DN_asci[den], ANCHOR_KCITANIE, 5);\
		_set_kcitanie(modlitba, nazov_obd_htm[OBD_POSTNE_I], _anchor);\
	}\
	set_LOG_litobd;\
}
#define _post2_kresponz {\
	if(((den == DEN_STVRTOK) && (modlitba == MODL_VESPERY)) || (den == DEN_NEDELA)){\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ, nazov_DN_asci[den]);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	}\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _post2_prosby {\
	if(((den == DEN_STVRTOK) && (modlitba == MODL_VESPERY)) || (den == DEN_NEDELA)){\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_PROSBY, nazov_DN_asci[den]);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_PROSBY);\
	}\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _post2_benediktus {\
	if(den == DEN_NEDELA){\
		sprintf(_anchor, "%s_%c%s%d%s%c", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, tyzden, nazov_DN_asci[den], _global_den.litrok);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, tyzden, nazov_DN_asci[den]);\
	}\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _post2_magnifikat {\
	if(den == DEN_NEDELA){\
		sprintf(_anchor, "%s_%c%s%d%s%c", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, tyzden, nazov_DN_asci[den], _global_den.litrok);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, tyzden, nazov_DN_asci[den]);\
	}\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _post2_modlitba {\
	if(den == DEN_STVRTOK){\
		sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_MODLITBA, tyzden, nazov_DN_asci[den]);\
	}\
	else{\
		sprintf(_anchor, "%s_%s%d%s", nazov_OBD[litobd], ANCHOR_MODLITBA, tyzden, nazov_DN_asci[den]);\
	}\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _post2_antifony {\
	sprintf(_anchor, "%s_%d%s%c%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%d%s%c%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%d%s%c%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

		/* ranne chvaly */
			modlitba = MODL_RANNE_CHVALY;
			_post2_hymnus;
			_post2_antifony;
			_post2_kcitanie;
			_post2_kresponz;
			_post2_benediktus;
			_post2_prosby;
			_post2_modlitba;
		/* vespery */
			modlitba = MODL_VESPERY;
			_post2_hymnus;
			_post2_antifony;
			_post2_kcitanie;
			_post2_kresponz;
			_post2_magnifikat;
			_post2_prosby;
			_post2_modlitba;

			if(den == DEN_NEDELA){

			/* prve vespery */
				modlitba = MODL_PRVE_VESPERY;
				_post2_hymnus;
				_post2_antifony;
				_post2_kcitanie;
				_post2_kresponz;
				_post2_magnifikat;
				_post2_prosby;
				_post2_modlitba;
			}/* nedela */
			else{
			}/* nie nedela */
			break;
/* switch(litobd), case OBD_POSTNE_II -- end -------------------------------------------------- */

/* switch(litobd), case OBD_VELKONOCNE_TROJDNIE -- begin -------------------------------------- */
		case OBD_VELKONOCNE_TROJDNIE:/* umucenia a zmrtvychvstania Pana */
			/* 08/03/2000A.D. */
#define _vtroj_hymnus {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	sprintf(_anchor, "%s_%c%s%s", nazov_OBD[OBD_VELKONOCNE_TROJDNIE], c, nazov_DN_asci[den], ANCHOR_HYMNUS);\
	_set_hymnus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vtroj_kcitanie {\
	sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), nazov_DN_asci[den], ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vtroj_kresponz {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	sprintf(_anchor, "%s_%c%s%s", nazov_OBD[OBD_VELKONOCNE_TROJDNIE], c, ANCHOR_KRESPONZ, nazov_DN_asci[den]);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vtroj_prosby {\
	sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_PROSBY, nazov_DN_asci[den]);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vtroj_benediktus {\
	sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, tyzden, nazov_DN_asci[den]);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vtroj_magnifikat {\
	sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, tyzden, nazov_DN_asci[den]);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vtroj_modlitba {\
	sprintf(_anchor, "%s_%s%d%s", nazov_OBD[litobd], ANCHOR_MODLITBA, tyzden, nazov_DN_asci[den]);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vtroj_antifony {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VELKONOCNE_TROJDNIE], nazov_DN_asci[den], c, ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VELKONOCNE_TROJDNIE], nazov_DN_asci[den], c, ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VELKONOCNE_TROJDNIE], nazov_DN_asci[den], c, ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

		/* ranne chvaly */
			modlitba = MODL_RANNE_CHVALY;
			_vtroj_hymnus;
			_vtroj_antifony;
			_vtroj_kcitanie;
			_vtroj_kresponz;
			_vtroj_benediktus;
			_vtroj_prosby;
			_vtroj_modlitba;
		/* vespery */
			modlitba = MODL_VESPERY;
			_vtroj_hymnus;
			_vtroj_antifony;
			_vtroj_kcitanie;
			_vtroj_kresponz;
			_vtroj_magnifikat;
			_vtroj_prosby;
			_vtroj_modlitba;

			if(den == DEN_NEDELA){
				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_velkonocna_nedela(modlitba);
				modlitba = MODL_VESPERY;
				_set_zalmy_velkonocna_nedela(modlitba);
			}/* nedela */
			else if(den == DEN_SOBOTA){
				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_biela_sobota(modlitba);
				modlitba = MODL_VESPERY;
				_set_zalmy_biela_sobota(modlitba);
			}/* nie nedela, ale sobota */
			else if(den == DEN_PIATOK){
				modlitba = MODL_VESPERY;
				_set_zalmy_velky_piatok(modlitba);
			}/* nie nedela, ale sobota */
			break;
/* switch(litobd), case OBD_VELKONOCNE_TROJDNIE -- end ---------------------------------------- */

/* switch(litobd), case OBD_VELKONOCNE_I -- begin --------------------------------------------- */
		case OBD_VELKONOCNE_I:/* do nanebovstupenia pana */
			/* 09/03/2000A.D. */
/* zabezpecime nahodnost pri hymne vo feriu, kedy sa "podla lubovole" mozre brat nie nedelny hymnus */
/* ((_global_den.den MOD 3) == 0) */
#define _velk1_hymnus {\
	if((den == DEN_NEDELA) || ((_global_den.den MOD 3) == 0)){\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_HYMNUS, nazov_DN_asci[DEN_NEDELA]);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	}\
	_set_hymnus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _velk1_kcitanie {\
	sprintf(_anchor, "%s_%c%s%s", nazov_OBD[OBD_VELKONOCNE_I], pismenko_modlitby(modlitba), nazov_DN_asci[den], ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _velk1_kresponz {\
	if(den == DEN_NEDELA){\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ, nazov_DN_asci[den]);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	}\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _velk1_prosby {\
	sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[OBD_VELKONOCNE_I], pismenko_modlitby(modlitba), ANCHOR_PROSBY, t, nazov_DN_asci[den]);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _velk1_benediktus {\
	if(den == DEN_NEDELA){\
		sprintf(_anchor, "%s_%c%s%d%s%c", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, tyzden, nazov_DN_asci[den], _global_den.litrok);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, tyzden, nazov_DN_asci[den]);\
	}\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _velk1_magnifikat {\
	if(den == DEN_NEDELA){\
		sprintf(_anchor, "%s_%c%s%d%s%c", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, tyzden, nazov_DN_asci[den], _global_den.litrok);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, tyzden, nazov_DN_asci[den]);\
	}\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _velk1_modlitba {\
	sprintf(_anchor, "%s_%s%d%s", nazov_OBD[litobd], ANCHOR_MODLITBA, tyzden, nazov_DN_asci[den]);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _velk1_ne_antifony {\
	sprintf(_anchor, "%s_%d%s%c%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%d%s%c%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%d%s%c%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

			t = tyzden MOD 2;

			if(_global_den.denvr == _global_r._NANEBOVSTUPENIE_PANA.denvr){
				/* nanebovstupenie sice ma rovnake kotvy, ale v inom fajli; 10/03/2000A.D. */
				strcpy(_file, FILE_NANEBOVSTUPENIE);
				den = DEN_NEDELA;
				Log("  ide o nanebovstupenie Pana: _file = `%s', den = %s...\n", _file, nazov_dna[den]);
				modlitba = MODL_PRVE_VESPERY;
				_set_zalmy_nanebovstupenie(modlitba);
				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_nanebovstupenie(modlitba);
				modlitba = MODL_VESPERY;
				_set_zalmy_nanebovstupenie(modlitba);
			}

		/* ranne chvaly */
			modlitba = MODL_RANNE_CHVALY;
			_velk1_hymnus;
			_velk1_kcitanie;
			_velk1_kresponz;
			_velk1_benediktus;
			_velk1_prosby;
			_velk1_modlitba;
		/* vespery */
			modlitba = MODL_VESPERY;
			_velk1_hymnus;
			_velk1_kcitanie;
			_velk1_kresponz;
			_velk1_magnifikat;
			_velk1_prosby;
			_velk1_modlitba;

			if(den == DEN_NEDELA){
				modlitba = MODL_PRVE_VESPERY;
				_velk1_hymnus;
				_velk1_kcitanie;
				_velk1_kresponz;
				_velk1_magnifikat;
				_velk1_prosby;
				_velk1_modlitba;
				_velk1_ne_antifony;
				modlitba = MODL_RANNE_CHVALY;
				_velk1_ne_antifony;
				modlitba = MODL_VESPERY;
				_velk1_ne_antifony;
			}/* nedela */
			break;
/* switch(litobd), case OBD_VELKONOCNE_I -- end ----------------------------------------------- */

/* switch(litobd), case OBD_VELKONOCNE_II -- begin -------------------------------------------- */
		case OBD_VELKONOCNE_II:/* po nanebovstupeni pana */
			/* 10/03/2000A.D. */
#define _velk2_hymnus {\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	_set_hymnus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
/* citania ako v OBD_VELKONOCNE_I; 7. tyzden ma na vespery vlastne citanie */
#define _velk2_kcitanie {\
	if((den == DEN_NEDELA) || (modlitba == MODL_RANNE_CHVALY) || (tyzden == 6)){\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[OBD_VELKONOCNE_I], pismenko_modlitby(modlitba), nazov_DN_asci[den], ANCHOR_KCITANIE);\
		_set_kcitanie(modlitba, nazov_obd_htm[OBD_VELKONOCNE_I], _anchor);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), nazov_DN_asci[den], ANCHOR_KCITANIE);\
		_set_kcitanie(modlitba, _file, _anchor);\
	}\
	set_LOG_litobd;\
}
#define _velk2_kresponz {\
	if(den == DEN_NEDELA){\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ, nazov_DN_asci[den]);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	}\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _velk2_prosby {\
	sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[OBD_VELKONOCNE_I], pismenko_modlitby(modlitba), ANCHOR_PROSBY, t, nazov_DN_asci[den]);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _velk2_benediktus {\
	if(den == DEN_NEDELA){\
		sprintf(_anchor, "%s_%c%s%d%s%c", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, tyzden, nazov_DN_asci[den], _global_den.litrok);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, tyzden, nazov_DN_asci[den]);\
	}\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _velk2_magnifikat {\
	if(den == DEN_NEDELA){\
		sprintf(_anchor, "%s_%c%s%d%s%c", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, tyzden, nazov_DN_asci[den], _global_den.litrok);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, tyzden, nazov_DN_asci[den]);\
	}\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _velk2_modlitba {\
	sprintf(_anchor, "%s_%s%d%s", nazov_OBD[litobd], ANCHOR_MODLITBA, tyzden, nazov_DN_asci[den]);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _velk2_ne_antifony {\
	sprintf(_anchor, "%s_%d%s%c%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%d%s%c%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%d%s%c%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
/* zoslanie ducha sv. */
#define _zds_hymnus {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_ZOSLANIE_DUCHA_SV, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	_set_hymnus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _zds_kcitanie {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_ZOSLANIE_DUCHA_SV, pismenko_modlitby(modlitba), ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _zds_kresponz {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_ZOSLANIE_DUCHA_SV, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _zds_prosby {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_ZOSLANIE_DUCHA_SV, pismenko_modlitby(modlitba), ANCHOR_PROSBY);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _zds_benediktus {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_ZOSLANIE_DUCHA_SV, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _zds_magnifikat {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_ZOSLANIE_DUCHA_SV, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _zds_modlitba {\
	sprintf(_anchor, "%s_%s", ANCHOR_ZOSLANIE_DUCHA_SV, ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _zds_ne_antifony {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_ZOSLANIE_DUCHA_SV, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", ANCHOR_ZOSLANIE_DUCHA_SV, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", ANCHOR_ZOSLANIE_DUCHA_SV, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

			t = tyzden MOD 2;

			/* ranne chvaly */
			modlitba = MODL_RANNE_CHVALY;
			_velk2_hymnus;
			_velk2_kcitanie;
			_velk2_kresponz;
			_velk2_benediktus;
			_velk2_prosby;
			_velk2_modlitba;
		/* vespery */
			modlitba = MODL_VESPERY;
			_velk2_hymnus;
			_velk2_kcitanie;
			_velk2_kresponz;
			_velk2_magnifikat;
			_velk2_prosby;
			_velk2_modlitba;

			if(den == DEN_NEDELA){
				if(_global_den.denvr == _global_r._ZOSLANIE_DUCHA_SV.denvr){
					/* zoslanie ducha sv.; 10/03/2000A.D. */
					strcpy(_file, FILE_ZOSLANIE_DUCHA_SV);
					strcpy(_anchor, ANCHOR_ZOSLANIE_DUCHA_SV);
					Log("  ide o zoslanie Ducha Sv.: _file = `%s', _anchor = %s...\n", _file, _anchor);
					modlitba = MODL_PRVE_VESPERY;
					_set_zalmy_zoslanie_ducha_sv(modlitba);
					_zds_hymnus;
					_zds_kcitanie;
					_zds_kresponz;
					_zds_magnifikat;
					_zds_prosby;
					_zds_modlitba;
					_zds_ne_antifony;
					modlitba = MODL_RANNE_CHVALY;
					_set_zalmy_zoslanie_ducha_sv(modlitba);
					_zds_hymnus;
					_zds_kcitanie;
					_zds_kresponz;
					_zds_benediktus;
					_zds_prosby;
					_zds_modlitba;
					_zds_ne_antifony;
					modlitba = MODL_VESPERY;
					_set_zalmy_zoslanie_ducha_sv(modlitba);
					_zds_hymnus;
					_zds_kcitanie;
					_zds_kresponz;
					_zds_magnifikat;
					_zds_prosby;
					_zds_modlitba;
					_zds_ne_antifony;
				}
				else{
					modlitba = MODL_PRVE_VESPERY;
					_velk2_hymnus;
					_velk2_kcitanie;
					_velk2_kresponz;
					_velk2_magnifikat;
					_velk2_prosby;
					_velk2_modlitba;
					_velk2_ne_antifony;
					modlitba = MODL_RANNE_CHVALY;
					_velk2_ne_antifony;
					modlitba = MODL_VESPERY;
					_velk2_ne_antifony;
				}/* nie je zoslanie ds */
			}/* nedela */
			break;
/* switch(litobd), case OBD_VELKONOCNE_II -- end ---------------------------------------------- */

/* switch(litobd), case OBD_VELKONOCNA_OKTAVA -- begin ---------------------------------------- */
		case OBD_VELKONOCNA_OKTAVA:/* velkonocna nedela -- 2. velk. ne */
			/* velkonocna oktava: 09/03/2000A.D.
			 *    - hymnus, antifony 1 -- 3, zalmy a chvalospev su z velkonocnej nedele;
			 *    - responzorium, 'Toto je den...' ako na velkonocnu nedelu;
			 *    - citanie,  prosby: z velkonocneho obdobia I,
			 *    - ant. na benediktus/magnifikat a modlitba: vlastne;
			 */
#define _vnokt_benediktus {\
	sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, nazov_DN_asci[den]);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vnokt_magnifikat {\
	sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, nazov_DN_asci[den]);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vnokt_modlitba {\
	sprintf(_anchor, "%s_%s%s", nazov_OBD[litobd], ANCHOR_MODLITBA, nazov_DN_asci[den]);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

			t = tyzden MOD 2;

		/* teda najprv nastavime vlastne ant. na benediktus/magnifikat a modlitbu */
		/* ranne chvaly */
			modlitba = MODL_RANNE_CHVALY;
			_vnokt_benediktus;
			_vnokt_modlitba;
		/* vespery */
			modlitba = MODL_VESPERY;
			_vnokt_magnifikat;
			_vnokt_modlitba;
		/* teraz nastavime zalmy z velkonocnej nedele */
			modlitba = MODL_RANNE_CHVALY;
			_set_zalmy_velkonocna_nedela(modlitba);
			modlitba = MODL_VESPERY;
			_set_zalmy_velkonocna_nedela(modlitba);
		/* a veci pre prve vespery */
			if(den == DEN_NEDELA){
				modlitba = MODL_PRVE_VESPERY;
				_vnokt_magnifikat;
				_vnokt_modlitba;
				_set_zalmy_velkonocna_nedela(modlitba);
			}/* nedela */


		/* dalej nastavime citanie a prosby z velkonocneho obd. I */
			strcpy(_file, nazov_obd_htm[OBD_VELKONOCNE_I]); /* aby bolo z velkonocneho obd. I */
		/* ranne chvaly */
			modlitba = MODL_RANNE_CHVALY;
			_velk1_kcitanie;
			_velk1_prosby;
		/* vespery */
			modlitba = MODL_VESPERY;
			_velk1_kcitanie;
			_velk1_prosby;
		/* a veci pre prve vespery */
			if(den == DEN_NEDELA){
				modlitba = MODL_PRVE_VESPERY;
				_velk1_kcitanie;
				_velk1_prosby;
			}/* nedela */

		/* napokon nastavime hymnus, antifony a kratke resp. z velkonocnej nedele */
			strcpy(_file, nazov_obd_htm[OBD_VELKONOCNE_TROJDNIE]); /* aby bolo z velkonocnej nedele */
			den = DEN_NEDELA;
		/* ranne chvaly */
			modlitba = MODL_RANNE_CHVALY;
			_vtroj_hymnus;
			_vtroj_antifony;
			_vtroj_kresponz;
		/* vespery */
			modlitba = MODL_VESPERY;
			_vtroj_hymnus;
			_vtroj_antifony;
			_vtroj_kresponz;
		/* a veci pre prve vespery */
			if(den == DEN_NEDELA){
				modlitba = MODL_PRVE_VESPERY;
				_vtroj_hymnus;
				_vtroj_antifony;
				_vtroj_kresponz;
			}/* nedela */
			break;
/* switch(litobd), case OBD_VELKONOCNA_OKTAVA -- end ------------------------------------------ */

	}/* switch(litobd) */
	/* koniec velkeho switchu, podla ktoreho sa priradia zakladne udaje */

#ifdef DETAIL_LOG_GLOBAL_DEN
	Log("_global_den (nastavene v dbzaltar.cpp::liturgicke_obdobie() po velkom switchi, pred druhym spustanim sviatky_svatych()):\n");
	Log(_global_den);
#endif
	/* -------------------------------------------------------------------- */
	/* nasledujuca cast berie do uvahy, kedy sa ma `robit' svaty */
	/* je to cast prevzata z dnes.cpp::init_global_string(); */
	_struct_dm _local_den;
	int obyc = NIE;
	/* najprv priradime do _local_den to, co tam ma byt */
	if(poradie_svateho > 0){
		/* sviatky (spomienky, ls) svatych */
		switch(poradie_svateho){
			case 4:
				/* do _local_den priradim slavenie pm v sobotu v dalsom */
				_local_den = _global_pm_sobota;
				/* ale predsalen aspon _local_den = _global_pm_sobota; urobim tu; 04/07/2000A.D. */
				break; /* case 4: */
			case 1:
				/* do _local_den priradim dane slavenie */
				_local_den = _global_svaty1;
				Log("spustam druhykrat sviatky_svatych(), tentokrat pre %d. svateho\n", poradie_svateho);
				sviatky_svatych(_local_den.den, _local_den.mesiac, poradie_svateho, 2);
				break; /* case 1: */
			case 2:
				if(_global_pocet_svatych > 1){
					/* do _local_den priradim dane slavenie */
					_local_den = _global_svaty2;
					Log("spustam druhykrat sviatky_svatych(), tentokrat pre %d. svateho\n", poradie_svateho);
					sviatky_svatych(_local_den.den, _local_den.mesiac, poradie_svateho, 2);
				}
				else{
					/* sice chce svateho c. 2, ale mam len jedneho */
					Log("-- Error: _global_svaty2 not assigned\n");
					Export("%s\n", "Error: _global_svaty2 not assigned");
					ALERT;
				}
				break; /* case 2: */
			case 3:
				if(_global_pocet_svatych > 2){
					/* teraz do _local_den priradim dane slavenie */
					_local_den = _global_svaty3;
					Log("spustam druhykrat sviatky_svatych(), tentokrat pre %d. svateho\n", poradie_svateho);
					sviatky_svatych(_local_den.den, _local_den.mesiac, poradie_svateho, 2);
				}
				else{
					/* sice chce svateho c. 3, ale nemam troch */
					Log("-- Error: _global_svaty3 not assigned\n");
					Export("%s\n", "Error: _global_svaty3 not assigned");
					ALERT;
				}
				break; /* case 3: */
			case 5:
				Log("-- Error: poradie_svateho == 5\n");
				Export("Error: poradie_svateho == 5\n");
				ALERT;
				break;
			case 0:
				/* je smiesne, ze case 0 tu vobec je: ved toto je mrtvy kus kodu! 04/07/2000A.D. */
				/* bezny den */
				if(_global_svaty1.smer >= 12){
					/* ak je to iba lubovolna spomienka, tak vsedny den */
					obyc = ANO;
					_local_den = _global_den;
				}
				else{
					/* sice chce obycajny den, ale nemoze byt */
					Log("-- Error: _global_den not assigned\n");
					Export("%s\n", "Error: _global_den not assigned");
					ALERT;
				}
				break; /* case 0: */
		}/* switch(poradie_svateho) */
	}
	else if((_global_den.denvt == DEN_NEDELA) ||
		(_global_den.prik == PRIKAZANY_SVIATOK)){
		/* _local_den ostava _global_den */
		_local_den = _global_den;
	}
	else if((poradie_svateho > 0) && (_global_pocet_svatych > 0)){
	}/* if(_global_pocet_svatych > 0) */
	else{
		/* obycajny den */
		obyc = ANO;
		_local_den = _global_den;
	}
	/* este spomienka panny marie v sobotu, cl. 15 */
	/* najprv sa spytame tej soboty, ci nahodou nie je 
	   spomienka neposkvrneneho srdca panny marie;
	   ak je, tak uprednostnime tuto.
	   pridane 04/07/2000A.D. */
	if(_global_den.denvr == (_global_r._ZOSLANIE_DUCHA_SV.denvr + 20)){
		/* pri spusteni liturgicke_obdobie(); spomienka neposkvrneneho srdca panny marie */
		Log("/* pri spusteni liturgicke_obdobie(); spomienka neposkvrneneho srdca panny marie */\n");
		Log("spustam druhykrat sviatky_svatych(), tentokrat pre %d. svateho\n", poradie_svateho);
		_local_den = _global_den;
		sviatky_svatych(_local_den.den, _local_den.mesiac, poradie_svateho, 2);
	}
	if((_global_den.litobd == OBD_CEZ_ROK) &&
		(_global_den.denvt == DEN_SOBOTA) &&
		((_global_den.denvr != (_global_r._ZOSLANIE_DUCHA_SV.denvr + 20))) && /* pridane 04/07/2000A.D. */
		(
			((_global_den.smer >= 12) && (_global_pocet_svatych == 0)) ||
			((_global_svaty1.smer >= 12) && (_global_pocet_svatych > 0))) &&
		(poradie_svateho == 4)){
		/* teraz do _global_den priradim dane slavenie */
		_local_den = _global_pm_sobota;
		strcpy(_file, FILE_SPOM_PM_SOBOTA);
		modlitba = MODL_RANNE_CHVALY;
		/* hymnus */
		/* su tri hymny, preto ich dame podla tyzzal MOD 3 (0, 1, 2) */
		sprintf(_anchor, "%s%c_%s%d",
			SPOM_PM_SOBOTA,
			pismenko_modlitby(modlitba),
			ANCHOR_HYMNUS,
			tyzzal MOD 3);
		_set_hymnus(modlitba, _file, _anchor);
		set_LOG_litobd;
		/* kratke citanie */
		/* su tri, preto ich dame podla tyzzal MOD 3 (0, 1, 2) */
		sprintf(_anchor, "%s%c_%s%d",
			SPOM_PM_SOBOTA,
			pismenko_modlitby(modlitba),
			ANCHOR_KCITANIE,
			tyzzal MOD 3);
		_set_kcitanie(modlitba, _file, _anchor);
		set_LOG_litobd;
		/* kratke responzorium  */
		/* su tri, preto ich dame podla tyzzal MOD 3 (0, 1, 2) */
		sprintf(_anchor, "%s%c_%s%d",
			SPOM_PM_SOBOTA,
			pismenko_modlitby(modlitba),
			ANCHOR_KRESPONZ,
			tyzzal MOD 3);
		_set_kresponz(modlitba, _file, _anchor);
		set_LOG_litobd;
		/* benediktus */
		/* je ich 6, takze tyzzal MOD 6 + 1 (1 -- 6) */
		/* preto "+ 1", aby sme dodrzali povodne cislovanie */
		sprintf(_anchor, "%s%c_%s%d",
			SPOM_PM_SOBOTA,
			pismenko_modlitby(modlitba),
			ANCHOR_BENEDIKTUS,
			tyzzal MOD 6);
		_set_benediktus(modlitba, _file, _anchor);
		set_LOG_litobd;
		/* prosby */
		/* su 2, takze tyzzal MOD 2 (0, 1) */
		sprintf(_anchor, "%s%c_%s%d",
			SPOM_PM_SOBOTA,
			pismenko_modlitby(modlitba),
			ANCHOR_PROSBY,
			tyzzal MOD 2);
		_set_prosby(modlitba, _file, _anchor);
		set_LOG_litobd;
		/* modlitba */
		/* je ich 6, takze tyzzal MOD 6 + 1 (1 -- 6) */
		/* preto "+ 1", aby sme dodrzali povodne cislovanie */
		sprintf(_anchor, "%s%c_%s%d",
			SPOM_PM_SOBOTA,
			pismenko_modlitby(modlitba),
			ANCHOR_MODLITBA,
			tyzzal MOD 6);
		_set_modlitba(modlitba, _file, _anchor);
		set_LOG_litobd;
	}

	_global_den = _local_den;
#ifdef DETAIL_LOG_GLOBAL_DEN
	Log("_global_den (nastavene v dbzaltar.cpp::liturgicke_obdobie() na konci):\n");
	Log(_global_den);
#endif
	/* koniec casti podla dnes.cpp::init_global_string(); */
	Log("-- liturgicke_obdobie(%d, %d, %d, %d) -- koniec\n",
		litobd, tyzden, den, tyzzal);
}/* liturgicke_obdobie(); */

/* --------------------------------------------------------------------- */

/* obsahuje udaje o spolocnej casti, MODL_SPOL_CAST...
 * kedze ju pouzivame len pri druhom volani sviatky_svatych(),
 * mame zarucene, ze _global_den obsahuje dobre udaje -- toho spravneho
 * svateho :-)
 */
int modlitba;

/* nasleduje funkcia sviatky_svatych(); ktora bola povodne sama vo fajli
 * dbsvaty.c */

/* sviatky_svatych();
 *
 * nastavi do _global_svaty1 nasledovne udaje:
 *
 *	    typslav;    // typ slavenia (1--5): SLAV_...
 *     smer;       // poradove cislo z c.59 Vseobecnych smernic
 *                 // o liturgii hodin a kalendari
 *	    meno[MAX_MENO]; // nazov prip. sviatku
 *
 * az na konci nastavi .den a .mesiac, ostatne sa nastavia inde !!!
 *
 * 09/02/2000A.D.: tato funkcia default dostava vstup poradie_svaty == 0;
 * to sa rovna 'staremu pouzitiu'; v pripade, ze poradie_svaty != 0,
 * znamena to, ze chceme uz pri generovani modlitby nastavit konkretne
 * pre danu modlitbu (svateho) atributy.
 *
 */

/* najprv nejake define'y... */
#define LOG_ciara_sv Log("  -------------------------\n");
/* 2003-06-30 pre lahsie debugovanie obohateny vypis */
#define set_LOG_svsv Log("   set(svsv): %s: `%s', <!--{BEGIN:%s}-->\n", nazov_modlitby[modlitba], _file, _anchor)

/* ked dostane strukturu spol_cast, vrati
 * MODL_SPOL_CAST_DUCH_PAST_... resp.
 * MODL_SPOL_CAST_PANNA
 * alebo MODL_SPOL_CAST_REHOLNIK -- vtedy priradim MODL_SPOL_CAST_SV_MUZ; 03/03/2000A.D.
 * mozno je to diskriminujuce, ale napr. kvoli sv. Efremovi (9. juna), 
 * ak nematchuje, vrati MODL_SPOL_CAST_SV_MUZ; 03/03/2000A.D.
 * (predtym som vracal MODL_SPOL_CAST_NEURCENA)
 */
#define otazka_sedi_to {\
	if((a == MODL_SPOL_CAST_DUCH_PAST_KNAZ) || (a == MODL_SPOL_CAST_DUCH_PAST_BISKUP) || (a == MODL_SPOL_CAST_DUCH_PAST_PAPEZ) || (a == MODL_SPOL_CAST_PANNA)){\
		Log("matches (duchovny pastier || panna). returning %s (%d)\n", nazov_spolc[a], a);\
		return a;\
	}\
	else if((a == MODL_SPOL_CAST_SV_MUZ_REHOLNIK) || (a == MODL_SPOL_CAST_SV_MUZ)){\
		Log("matches (reholnik || muz). returning %s (%d)\n", nazov_spolc[MODL_SPOL_CAST_SV_MUZ], MODL_SPOL_CAST_SV_MUZ);\
		return MODL_SPOL_CAST_SV_MUZ;\
	}\
}	
int _spol_cast_vyber_dp_pn(_struct_sc spol_cast){
	Log("_spol_cast_vyber_dp_pn() -- skusam, co sedi...\n");
	int a;
	a = spol_cast.a1;
	Log("  spol_cast.a1 == %s (%d)\n", nazov_spolc[spol_cast.a1], spol_cast.a1);
	otazka_sedi_to;
	a = spol_cast.a2;
	Log("  spol_cast.a2 == %s (%d)\n", nazov_spolc[spol_cast.a2], spol_cast.a2);
	otazka_sedi_to;
	a = spol_cast.a3;
	Log("  spol_cast.a3 == %s (%d)\n", nazov_spolc[spol_cast.a3], spol_cast.a3);
	otazka_sedi_to;
	Log("not matches. returning %s (%d)\n", nazov_spolc[MODL_SPOL_CAST_SV_MUZ], MODL_SPOL_CAST_SV_MUZ);
	return MODL_SPOL_CAST_SV_MUZ;
}/* _spol_cast_vyber_dp_pn(); */

#define otazka_sedi_to2 if(a == MODL_SPOL_CAST_PANNA){Log("matches. returning ANO\n");return ANO;}
int _spol_cast_je_panna(_struct_sc spol_cast){
	Log("_spol_cast_je_panna() -- skusam, ci v spol_cast je panna...\n");
	int a;
	a = spol_cast.a1;
	Log("  spol_cast.a1 == %s (%d)\n", nazov_spolc[spol_cast.a1], spol_cast.a1);
	otazka_sedi_to2;
	a = spol_cast.a2;
	Log("  spol_cast.a2 == %s (%d)\n", nazov_spolc[spol_cast.a2], spol_cast.a2);
	otazka_sedi_to2;
	a = spol_cast.a3;
	Log("  spol_cast.a3 == %s (%d)\n", nazov_spolc[spol_cast.a3], spol_cast.a3);
	otazka_sedi_to2;
	Log("  returning NIE\n");
	return NIE;
}/* _spol_cast_je_panna(); */

/* tu boli _set_zalmy_..., ale su inde; 14/03/2000A.D. */

/* nastavenie jednotlivych parametrov modlitby -- predpoklad je, ze premenna
 * modlitba ma spravne nastavenu konstantu MODL_... */

/* hymnus */
#define _vlastna_cast_hymnus {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	_set_hymnus(modlitba, _file, _anchor);\
	set_LOG_svsv;}
/* antifony */
/* kedysi tam pred celym blokom bolo if(_global_opt2 == MODL_ZALMY_ZO_SV) */
#define _vlastna_cast_antifony {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_svsv;\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_svsv;\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_svsv;}
/* kratke citanie */
#define _vlastna_cast_kcitanie {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_svsv;}
/* kratke responzorium */
#define _vlastna_cast_kresponz {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_svsv;}
/* bedediktus */
#define _vlastna_cast_benediktus {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_svsv;}
/* magnifikat */
#define _vlastna_cast_magnifikat {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_svsv;}
/* prosby */
#define _vlastna_cast_prosby {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_PROSBY);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_svsv;}
/* modlitba -- rovnaka rano i vecer */
#define _vlastna_cast_modlitba {\
	sprintf(_anchor, "%s%s", _anchor_head, ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_svsv;}
/* modlitba -- ina pre prve vespery ako rano i vecer dna */
#define _vlastna_cast_modlitba_prve_vesp {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_svsv;}
/* full -- vsetko (hymnus, antifony, kcitanie, kresponz,
 * benediktus/magnifikat, prosby, modlitba */
#define _vlastna_cast_full(modl) {\
	_vlastna_cast_hymnus;\
	_vlastna_cast_antifony;\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	_vlastna_cast_prosby;\
	_vlastna_cast_modlitba;}
#define _vlastna_cast_full_okrem_prosieb(modl) {\
	_vlastna_cast_hymnus;\
	_vlastna_cast_antifony;\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	_vlastna_cast_modlitba;}
/* full -- vsetko (hymnus, antifony, kcitanie, kresponz,
 * benediktus/magnifikat, prosby, modlitba -- ina ako na rchv a vesp */
#define _vlastna_cast_antifony_ako_na_ranne_chvaly {\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(MODL_RANNE_CHVALY), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_svsv;\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(MODL_RANNE_CHVALY), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_svsv;\
	sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(MODL_RANNE_CHVALY), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_svsv;}

/* rovnako tak pre spolocnu cast... */
#define _spolocna_cast_hymnus             _vlastna_cast_hymnus
#define _spolocna_cast_kcitanie           _vlastna_cast_kcitanie
#define _spolocna_cast_kresponz           _vlastna_cast_kresponz
#define _spolocna_cast_benediktus         _vlastna_cast_benediktus
#define _spolocna_cast_magnifikat         _vlastna_cast_magnifikat
#define _spolocna_cast_prosby             _vlastna_cast_prosby
#define _spolocna_cast_modlitba           _vlastna_cast_modlitba
#define _spolocna_cast_modlitba_prve_vesp _vlastna_cast_modlitba_prve_vesp
/*#define _spolocna_cast_antifony           _vlastna_cast_antifony*/
/* ... az na antifony... */
#define _spolocna_cast_antifony {\
	if(_global_opt3 != MODL_SPOL_CAST_NEBRAT){\
		Log("  antifony vlastnej casti zo sviatku...\n");\
		sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
		_set_antifona1(modlitba, _file, _anchor);\
		set_LOG_svsv;\
		sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
		_set_antifona2(modlitba, _file, _anchor);\
		set_LOG_svsv;\
		sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
		_set_antifona3(modlitba, _file, _anchor);\
		set_LOG_svsv;}\
	}
/* ... a spolocnu cast full */
#define _spolocna_cast_full(modl) {\
	_vlastna_cast_hymnus;\
	_spolocna_cast_antifony;\
	_vlastna_cast_kcitanie;\
	_vlastna_cast_kresponz;\
	if(modl == MODL_RANNE_CHVALY){_vlastna_cast_benediktus;}\
	else if((modl == MODL_VESPERY) || (modl == MODL_PRVE_VESPERY)){_vlastna_cast_magnifikat;}\
	_vlastna_cast_prosby;\
	_vlastna_cast_modlitba;}

#define _vlastna_cast_hymnus_po {\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_HYMNUS, POSTNA_PRIPONA);\
	_set_hymnus(modlitba, _file, _anchor);\
	set_LOG_svsv;}
#define _vlastna_cast_hymnus_ve {\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_HYMNUS, VELKONOCNA_PRIPONA);\
	_set_hymnus(modlitba, _file, _anchor);\
	set_LOG_svsv;}
#define _spolocna_cast_benediktus_ve _vlastna_cast_benediktus_ve
#define _vlastna_cast_benediktus_ve {\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, VELKONOCNA_PRIPONA);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_svsv;}
#define _spolocna_cast_magnifikat_ve _vlastna_cast_magnifikat_ve
#define _vlastna_cast_magnifikat_ve {\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, VELKONOCNA_PRIPONA);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_svsv;}
#define _spolocna_cast_kresponz_ve _vlastna_cast_kresponz_ve
#define _vlastna_cast_kresponz_ve {\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ, VELKONOCNA_PRIPONA);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_svsv;}
#define _vlastna_cast_kresponz_po {\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ, POSTNA_PRIPONA);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_svsv;}
#define _vlastna_cast_kresponz_cr {\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ, CEZROCNA_PRIPONA);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_svsv;}

/* specialne veci pre sviatky duchovnych pastierov, jedneho mucenika... */
/* funguje to aj pre svatych muzov (jeden resp. viaceri -- podla toho, co je
 * v _anchor_pom); 29/02/2000A.D. */
void _spolocna_cast_hymnus_rozne(int modlitba, char *_anchor_pom, char *_anchor, char *_file){
	sprintf(_anchor, "%s%c%s", _anchor_pom, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);
	_set_hymnus(modlitba, _file, _anchor);
	set_LOG_svsv;
}

void _spolocna_cast_benediktus_rozne(int modlitba, char *_anchor_pom, char *_anchor, char *_file){
	sprintf(_anchor, "%s%c%s", _anchor_pom, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS);
	_set_benediktus(modlitba, _file, _anchor);
	set_LOG_svsv;
}

void _spolocna_cast_magnifikat_rozne(int modlitba, char *_anchor_pom, char *_anchor, char *_file){
	sprintf(_anchor, "%s%c%s", _anchor_pom, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT);
	_set_magnifikat(modlitba, _file, _anchor);
	set_LOG_svsv;
}

void _spolocna_cast_kresponz_rozne(int modlitba, char *_anchor_pom, char *_anchor, char *_file){
	sprintf(_anchor, "%s%c%s", _anchor_pom, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);
	_set_kresponz(modlitba, _file, _anchor);
	set_LOG_svsv;
}


/* specialne veci pre sviatky jedneho mucenika */
#define _spolocna_cast_kcit_kresp_chval_ve {\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_KCITANIE, VELKONOCNA_PRIPONA);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_svsv;\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ, VELKONOCNA_PRIPONA);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_svsv;\
	if(modlitba == MODL_RANNE_CHVALY){\
		sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, VELKONOCNA_PRIPONA);\
		_set_benediktus(modlitba, _file, _anchor);\
		set_LOG_svsv;\
	}\
	else if((modlitba == MODL_VESPERY) || (modlitba == MODL_PRVE_VESPERY)){\
		sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, VELKONOCNA_PRIPONA);\
		_set_magnifikat(modlitba, _file, _anchor);\
		set_LOG_svsv;\
	}}

#define _spolocna_cast_ant1_3_po {\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1, POSTNA_PRIPONA);\
	_set_antifona1(modlitba, _file, _anchor);\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3, POSTNA_PRIPONA);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_svsv;\
	}
/* specialne veci pre sviatky viacerych mucenikov */
#define _spolocna_cast_ant2_po {\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2, POSTNA_PRIPONA);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_svsv;\
	}

/* specialne veci pre sviatky panien */
#define _spolocna_cast_kresp_ve {\
	sprintf(_anchor, "%s%c%s%s", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ, VELKONOCNA_PRIPONA);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_svsv;\
	}

/* ked je viac napevov, `kolko' uvadza, z kolkych je na vyber;
 * zvacsa sa vyberie napr. podla (_global_den.den MOD kolko) + 1
 * (aby bol z intervalu 1..kolko)
 * 23/02/2000A.D.
 */
void _spolocna_cast_magnifikat_viac(int kolko, char *_anchor_head, char *_anchor, char *_file){
	sprintf(_anchor, "%s%c%s%d",
		_anchor_head, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT,
		(_global_den.den MOD kolko) + 1);
	_set_magnifikat(modlitba, _file, _anchor);
	set_LOG_svsv;
}
/* viac benediktus-ov - dorobene 01/03/2000A.D. */
void _spolocna_cast_benediktus_viac(int kolko, char *_anchor_head, char *_anchor, char *_file){
	sprintf(_anchor, "%s%c%s%d",
		_anchor_head, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS,
		(_global_den.den MOD kolko) + 1);
	_set_benediktus(modlitba, _file, _anchor);
	set_LOG_svsv;
}
/* viac prosieb -- dorobene 01/03/2000A.D., spol.casti panny marie */
void _spolocna_cast_prosby_viac(int kolko, char *_anchor_head, char *_anchor, char *_file){
	sprintf(_anchor, "%s%c%s%d",
		_anchor_head, pismenko_modlitby(modlitba), ANCHOR_PROSBY,
		(_global_den.den MOD kolko) + 1);
	_set_prosby(modlitba, _file, _anchor);
	set_LOG_svsv;
}
/* viac prosieb -- dorobene 29/03/2000A.D., oficium za zosnulych */
void _spolocna_cast_kresponz_viac(int kolko, char *_anchor_head, char *_anchor, char *_file){
	sprintf(_anchor, "%s%c%s%d",
		_anchor_head, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ,
		(_global_den.den MOD kolko) + 1);
	_set_kresponz(modlitba, _file, _anchor);
	set_LOG_svsv;
}
void _spolocna_cast_ant3_viac(int kolko, char *_anchor_head, char *_anchor, char *_file){
	sprintf(_anchor, "%s%c%s%d",
		_anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3,
		(_global_den.den MOD kolko) + 1);
	_set_antifona3(modlitba, _file, _anchor);
	set_LOG_svsv;
}
void _set_spolocna_cast(int a, _struct_sc spol_cast){
	/* anchors - nazvy kotiev pre zaltar styroch tyzdnov */
	char _anchor[SMALL];
	char _anchor_head[SMALL];
	char _anchor_pom[SMALL];
	/* files - nazvy suborov pre zaltar styroch tyzdnov */
	char _file[SMALL]; /* nazov fajlu, napr. _1ne.htm */
	int b; /* pre ucitelov cirkvi, odkial sa maju brat ine casti */

	Log("_set_spolocna_cast(%s) -- begin\n", nazov_spolc[a]);

	if(a != MODL_SPOL_CAST_NEBRAT){
		Log("/* nastavenie nazvu suboru, kotvy apod. (_set_spolocna_cast) */\n");
		/* nastavenie nazvu suboru, kotvy apod. */
		sprintf(_anchor_head, "%s_", nazov_spolc_ANCHOR[a]);
		Log("  _anchor_head == %s\n", _anchor_head);
		sprintf(_file, "%s", nazov_spolc_htm[a]);
		Log("  _file == %s\n", _file);
	}
	else{
		Log("   nebrat... takze nenastavujem kotvy ani nic\n");
	}

	/* spolocna cast na sviatky apostolov */
	if(a == MODL_SPOL_CAST_APOSTOL){
		Log("/* spolocna cast na sviatky apostolov */\n");
		modlitba = MODL_PRVE_VESPERY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			Log("  _set_zalmy_sviatok_apostolov(%s)...\n", nazov_modlitby[modlitba]);
			_set_zalmy_sviatok_apostolov(modlitba);
		}
		_spolocna_cast_full(modlitba);
		_spolocna_cast_modlitba_prve_vesp;

		/* ranne chvaly */
		modlitba = MODL_RANNE_CHVALY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			_set_zalmy_1nedele_rch();
		}
		_spolocna_cast_full(modlitba);
		if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
			_vlastna_cast_kresponz_ve;
		/* ranne chvaly na sviatky apostolov maju specialne hymny pre postne a velkonocne obdobie */
		if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
			_vlastna_cast_hymnus_ve;
		}
		else if((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)){
			_vlastna_cast_hymnus_po;
		}

		/* vespery */
		if(_global_den.litobd != OBD_OKTAVA_NARODENIA){
			modlitba = MODL_VESPERY;
			if(_global_opt2 == MODL_ZALMY_ZO_SV){
				Log("  _set_zalmy_sviatok_apostolov(%s)...\n", nazov_modlitby[modlitba]);
				_set_zalmy_sviatok_apostolov(modlitba);
			}
			_spolocna_cast_full(modlitba);
			if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
				_vlastna_cast_kresponz_ve;
			if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
				_vlastna_cast_hymnus_ve;
		}/* v OBD_OKTAVA_NARODENIA (sv. Jana, 27. dec) vespery su zo dna */

	}/* MODL_SPOL_CAST_APOSTOL */

	/* spolocna cast na sviatky duchovnych pastierov */
	else if((a == MODL_SPOL_CAST_DUCH_PAST_KNAZ) ||
		(a == MODL_SPOL_CAST_DUCH_PAST_BISKUP) ||
		(a == MODL_SPOL_CAST_DUCH_PAST_PAPEZ) ||
		(a == MODL_SPOL_CAST_DUCH_PAST_VIACERI)){

		sprintf(_anchor_head, "%s_", ANCHOR_SPOL_CAST_DUCH_PAST);
		Log("  _anchor_head == %s\n", _anchor_head);
		sprintf(_anchor_pom, "%s_", nazov_spolc_ANCHOR[a]);
		Log("  _anchor_pom == %s\n", _anchor_pom);
		Log("/* spolocna cast na sviatky duchovnych pastierov */\n");
		modlitba = MODL_PRVE_VESPERY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			Log("  _set_zalmy_sviatok_duch_past(%s)...\n", nazov_modlitby[modlitba]);
			_set_zalmy_sviatok_duch_past(modlitba);
		}
		_spolocna_cast_full(modlitba);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file);
		_spolocna_cast_modlitba_prve_vesp;

		/* ranne chvaly */
		modlitba = MODL_RANNE_CHVALY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			_set_zalmy_1nedele_rch();
		}
		_spolocna_cast_full(modlitba);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file);
		if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
			_vlastna_cast_kresponz_ve;

		/* vespery */
		if(_global_den.litobd != OBD_OKTAVA_NARODENIA){
			modlitba = MODL_VESPERY;
			if(_global_opt2 == MODL_ZALMY_ZO_SV){
				Log("  _set_zalmy_sviatok_duch_past(%s)...\n", nazov_modlitby[modlitba]);
				_set_zalmy_sviatok_duch_past(modlitba);
			}
			_spolocna_cast_full(modlitba);
			_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file);
			_spolocna_cast_magnifikat_viac(2, _anchor_head, _anchor, _file);
			if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
				_vlastna_cast_kresponz_ve;
		}/* v OBD_OKTAVA_NARODENIA -- vespery su zo dna */

	}/* MODL_SPOL_CAST_DUCH_PAST_... */

	/* spolocna cast na sviatky ucitelov cirkvi */
	else if(a == MODL_SPOL_CAST_UCITEL_CIRKVI){
		/* najprv nastavime podla spol. casti duchovnych pastierov resp.
		 * panien... */
		Log("/* spolocna cast na sviatky ucitelov cirkvi */\n");
		b = _spol_cast_vyber_dp_pn(spol_cast);
		if(b != MODL_SPOL_CAST_NEURCENA){
			Log("spustam _set_spolocna_cast(%s) druhy raz (vnorene) -- \n  kvoli castiam, ktore pre ucitelov cirkvi nie su\n", nazov_spolc[b]);
			_set_spolocna_cast(b, spol_cast);
			Log("po vnorenom spusteni _set_spolocna_cast() -- navrat.\n");
			Log("pokracujem v nastaveni veci pre spol. cast MODL_SPOL_CAST_UCITEL_CIRKVI...\n");
		}
		/* ...a teraz vlastnu cast ucitelov cirkvi */

		/* ranne chvaly */
		modlitba = MODL_RANNE_CHVALY;
		_spolocna_cast_hymnus;
		_spolocna_cast_kcitanie;
		_spolocna_cast_kresponz;
		_spolocna_cast_benediktus;
		if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
			_vlastna_cast_kresponz_ve; /* pridane 18/06/2000A.D. */

		/* vespery */
		modlitba = MODL_VESPERY;
		_spolocna_cast_hymnus;
		_spolocna_cast_kcitanie;
		_spolocna_cast_kresponz;
		_spolocna_cast_magnifikat;
		if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
			_vlastna_cast_kresponz_ve; /* pridane 18/06/2000A.D. */
	}/* MODL_SPOL_CAST_UCITEL_CIRKVI */

	/* spolocna cast na sviatky jedneho mucenika */
	else if((a == MODL_SPOL_CAST_MUCENIK) ||
		(a == MODL_SPOL_CAST_MUCENICA)){

		sprintf(_anchor_head, "%s_", ANCHOR_SPOL_CAST_JEDEN_MUCENIK);
		Log("  _anchor_head == %s\n", _anchor_head);
		sprintf(_anchor_pom, "%s_", nazov_spolc_ANCHOR[a]);
		if(_spol_cast_je_panna(spol_cast) == ANO){
			sprintf(_anchor_pom, "%s_", ANCHOR_SPOL_CAST_PANNA_MUCENICA);
		}
		Log("  _anchor_pom == %s\n", _anchor_pom);
		Log("/* spolocna cast na sviatky jedneho mucenika */\n");
		modlitba = MODL_PRVE_VESPERY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			Log("  _set_zalmy_sviatok_muc(%s)...\n", nazov_modlitby[modlitba]);
			_set_zalmy_sviatok_muc(modlitba);
		}
		_spolocna_cast_full(modlitba);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file);
		if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
			_spolocna_cast_kcit_kresp_chval_ve;
		_spolocna_cast_modlitba_prve_vesp;

		/* ranne chvaly */
		modlitba = MODL_RANNE_CHVALY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			_set_zalmy_1nedele_rch();
		}
		_spolocna_cast_full(modlitba);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file);
		if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
			_spolocna_cast_kcit_kresp_chval_ve;

		/* vespery */
		if(_global_den.litobd != OBD_OKTAVA_NARODENIA){
			modlitba = MODL_VESPERY;
			if(_global_opt2 == MODL_ZALMY_ZO_SV){
				Log("  _set_zalmy_sviatok_muc(%s)...\n", nazov_modlitby[modlitba]);
				_set_zalmy_sviatok_muc(modlitba);
			}
			_spolocna_cast_full(modlitba);
			_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file);
			if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
				_spolocna_cast_kcit_kresp_chval_ve;
		}/* v OBD_OKTAVA_NARODENIA -- vespery su zo dna */

	}/* MODL_SPOL_CAST_MUCENIK/MUCENICA */

	/* spolocna cast na sviatky viacerych mucenikov */
	else if(a == MODL_SPOL_CAST_VIAC_MUCENIKOV){

		Log("/* spolocna cast na sviatky viacerych mucenikov */\n");
		modlitba = MODL_PRVE_VESPERY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			Log("  _set_zalmy_sviatok_muc(%s)...\n", nazov_modlitby[modlitba]);
			_set_zalmy_sviatok_muc(modlitba);
		}
		_spolocna_cast_full(modlitba);
		if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
			_spolocna_cast_kcit_kresp_chval_ve;
		_spolocna_cast_modlitba_prve_vesp;

		/* ranne chvaly */
		modlitba = MODL_RANNE_CHVALY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			_set_zalmy_1nedele_rch();
		}
		_spolocna_cast_full(modlitba);
		if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
			_spolocna_cast_kcit_kresp_chval_ve;
		if((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)){
			_spolocna_cast_ant2_po;
		}

		/* vespery */
		if(_global_den.litobd != OBD_OKTAVA_NARODENIA){
			modlitba = MODL_VESPERY;
			if(_global_opt2 == MODL_ZALMY_ZO_SV){
				Log("  _set_zalmy_sviatok_muc(%s)...\n", nazov_modlitby[modlitba]);
				_set_zalmy_sviatok_muc(modlitba);
			}
			_spolocna_cast_full(modlitba);
			if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
				_spolocna_cast_kcit_kresp_chval_ve;
		}/* v OBD_OKTAVA_NARODENIA -- vespery su zo dna */

	}/* MODL_SPOL_CAST_VIAC_MUCENIKOV */

	/* spolocna cast na sviatky svatych muzov/zien -- pre vychovavatelov */
	else if((a == MODL_SPOL_CAST_SV_MUZ_VYCH) || (a == MODL_SPOL_CAST_SV_ZENA_VYCH)){
		/* najprv nastavime podla spol. casti svatych muzov/zien... */
		Log("/* spolocna cast na sviatky svatych muzov/zien -- pre vychovavatelov */\n");
		b = MODL_SPOL_CAST_NEURCENA;
		if(a == MODL_SPOL_CAST_SV_ZENA_VYCH)
			b = MODL_SPOL_CAST_SV_ZENA;
		else if(a == MODL_SPOL_CAST_SV_MUZ_VYCH)
			b = MODL_SPOL_CAST_SV_MUZ;

		if(b != MODL_SPOL_CAST_NEURCENA){
			Log("spustam _set_spolocna_cast(%s) druhy raz (vnorene) -- \n   kvoli castiam, ktore pre vychovavatelov nie su\n", nazov_spolc[b]);
			_set_spolocna_cast(b, spol_cast);
			Log("po vnorenom spusteni _set_spolocna_cast() -- navrat.\n");
			Log("pokracujem v nastaveni veci pre spol. cast MODL_SPOL_CAST_..._VYCH...\n");
		}
		/* ...a teraz vlastnu cast pre vychovavatelov */

		/* prve vespery */
		modlitba = MODL_PRVE_VESPERY;
		_spolocna_cast_magnifikat;
		_spolocna_cast_modlitba;

		/* ranne chvaly */
		modlitba = MODL_RANNE_CHVALY;
		_spolocna_cast_benediktus;
		_spolocna_cast_modlitba;

		/* vespery */
		modlitba = MODL_VESPERY;
		_spolocna_cast_magnifikat;
		_spolocna_cast_modlitba;

	}/* MODL_SPOL_CAST_SV_MUZ/ZENA_VYCH */

	/* spolocna cast na sviatky svatych muzov/zien -- pre tych, ktori konali skutky milosrdenstva */
	else if((a == MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL) || (a == MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL)){
		/* najprv nastavime podla spol. casti svatych muzov/zien... */
		Log("/* spolocna cast na sviatky svatych muzov/zien -- pre tych, co konali skutky milosrdenstva */\n");
		b = MODL_SPOL_CAST_NEURCENA;
		if(a == MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL)
			b = MODL_SPOL_CAST_SV_ZENA;
		else if(a == MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL)
			b = MODL_SPOL_CAST_SV_MUZ;

		if(b != MODL_SPOL_CAST_NEURCENA){
			Log("spustam _set_spolocna_cast(%s) druhy raz (vnorene) -- \n   kvoli castiam, ktore pre tych, co konali skutky milosrdenstva nie su\n", nazov_spolc[b]);
			_set_spolocna_cast(b, spol_cast);
			Log("po vnorenom spusteni _set_spolocna_cast() -- navrat.\n");
			Log("pokracujem v nastaveni veci pre spol. cast MODL_SPOL_CAST_..._SKUTKYMIL...\n");
		}
		/* ...a teraz vlastnu cast pre tych, co konali skutky milosrdenstva */

		/* prve vespery */
		modlitba = MODL_PRVE_VESPERY;
		_spolocna_cast_magnifikat;
		_spolocna_cast_modlitba;

		/* ranne chvaly */
		modlitba = MODL_RANNE_CHVALY;
		_spolocna_cast_benediktus;
		_spolocna_cast_modlitba;

		/* vespery */
		modlitba = MODL_VESPERY;
		_spolocna_cast_magnifikat;
		_spolocna_cast_modlitba;

	}/* MODL_SPOL_CAST_SV_MUZ/ZENA_SKUTKYMIL */

	/* spolocna cast na sviatky svatych muzov/zien -- pre reholnikov */
	else if((a == MODL_SPOL_CAST_SV_MUZ_REHOLNIK) || (a == MODL_SPOL_CAST_SV_ZENA_REHOLNIK)){
		/* najprv nastavime podla spol. casti svatych muzov/zien... */
		Log("/* spolocna cast na sviatky svatych muzov/zien -- pre reholnikov */\n");
		b = MODL_SPOL_CAST_NEURCENA;
		if(a == MODL_SPOL_CAST_SV_ZENA_REHOLNIK)
			b = MODL_SPOL_CAST_SV_ZENA;
		else if(a == MODL_SPOL_CAST_SV_MUZ_REHOLNIK)
			b = MODL_SPOL_CAST_SV_MUZ;

		if(b != MODL_SPOL_CAST_NEURCENA){
			Log("spustam _set_spolocna_cast(%s) druhy raz (vnorene) -- \n   kvoli castiam, ktore pre reholnikov nie su\n", nazov_spolc[b]);
			_set_spolocna_cast(b, spol_cast);
			Log("po vnorenom spusteni _set_spolocna_cast() -- navrat.\n");
			Log("pokracujem v nastaveni veci pre spol. cast MODL_SPOL_CAST_..._REHOLNIK...\n");
		}
		/* ...a teraz vlastnu cast reholnikov */

		/* prve vespery */
		modlitba = MODL_PRVE_VESPERY;
		_spolocna_cast_hymnus;
		_spolocna_cast_magnifikat_viac(2, _anchor_head, _anchor, _file);
		_spolocna_cast_modlitba;

		/* ranne chvaly */
		modlitba = MODL_RANNE_CHVALY;
		_spolocna_cast_hymnus;
		_spolocna_cast_benediktus_viac(2, _anchor_head, _anchor, _file);
		_spolocna_cast_modlitba;

		/* vespery */
		modlitba = MODL_VESPERY;
		_spolocna_cast_hymnus;
		_spolocna_cast_magnifikat_viac(2, _anchor_head, _anchor, _file);
		_spolocna_cast_modlitba;

	}/* MODL_SPOL_CAST_SV_MUZ/ZENA_REHOLNIK */

	/* spolocna cast na sviatky svatych muzov */
	else if((a == MODL_SPOL_CAST_SV_MUZ) ||
		(a == MODL_SPOL_CAST_SV_MUZ_VIACERI)){

		sprintf(_anchor_head, "%s_", nazov_spolc_ANCHOR[MODL_SPOL_CAST_SV_MUZ]);
		Log("  _anchor_head == %s\n", _anchor_head);
		sprintf(_anchor_pom, "%s_", nazov_spolc_ANCHOR[a]);
		Log("  _anchor_pom == %s\n", _anchor_pom);
		Log("/* spolocna cast na sviatky svatych muzov */\n");
		modlitba = MODL_PRVE_VESPERY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			Log("  _set_zalmy_sviatok_duch_past(%s)...\n", nazov_modlitby[modlitba]);
			_set_zalmy_sviatok_duch_past(modlitba);
		}
		_spolocna_cast_full(modlitba);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file);

		/* ranne chvaly */
		modlitba = MODL_RANNE_CHVALY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			_set_zalmy_1nedele_rch();
		}
		_spolocna_cast_full(modlitba);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file);
		_spolocna_cast_benediktus_rozne(modlitba, _anchor_pom, _anchor, _file);
		_spolocna_cast_kresponz_rozne(modlitba, _anchor_pom, _anchor, _file);
		if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
			_vlastna_cast_kresponz_ve;

		/* vespery */
		if(_global_den.litobd != OBD_OKTAVA_NARODENIA){
			modlitba = MODL_VESPERY;
			if(_global_opt2 == MODL_ZALMY_ZO_SV){
				Log("  _set_zalmy_sviatok_duch_past(%s)...\n", nazov_modlitby[modlitba]);
				_set_zalmy_sviatok_duch_past(modlitba);
			}
			_spolocna_cast_full(modlitba);
			_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file);
			_spolocna_cast_magnifikat_rozne(modlitba, _anchor_pom, _anchor, _file);
			if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
				_vlastna_cast_kresponz_ve; /* pridane 18/06/2000A.D. */
		}/* v OBD_OKTAVA_NARODENIA -- vespery su zo dna */

	}/* MODL_SPOL_CAST_SV_MUZ_[VIACERI]... */

	/* spolocna cast na sviatky svatych zien */
	else if((a == MODL_SPOL_CAST_SV_ZENA) ||
		(a == MODL_SPOL_CAST_SV_ZENA_VIACERE)){

		sprintf(_anchor_head, "%s_", nazov_spolc_ANCHOR[MODL_SPOL_CAST_SV_ZENA]);
		Log("  _anchor_head == %s\n", _anchor_head);
		sprintf(_anchor_pom, "%s_", nazov_spolc_ANCHOR[a]);
		Log("  _anchor_pom == %s\n", _anchor_pom);
		Log("/* spolocna cast na sviatky svatych zien */\n");
		modlitba = MODL_PRVE_VESPERY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			Log("  _set_zalmy_sviatok_panien(%s)...\n", nazov_modlitby[modlitba]);
			_set_zalmy_sviatok_panien(modlitba);
		}
		_spolocna_cast_full(modlitba);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file);

		/* ranne chvaly */
		modlitba = MODL_RANNE_CHVALY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			_set_zalmy_1nedele_rch();
		}
		_spolocna_cast_full(modlitba);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file);
		if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
			_vlastna_cast_kresponz_ve;

		/* vespery */
		if(_global_den.litobd != OBD_OKTAVA_NARODENIA){
			modlitba = MODL_VESPERY;
			if(_global_opt2 == MODL_ZALMY_ZO_SV){
				Log("  _set_zalmy_sviatok_panien(%s)...\n", nazov_modlitby[modlitba]);
				_set_zalmy_sviatok_panien(modlitba);
			}
			_spolocna_cast_full(modlitba);
			_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file);
		}/* v OBD_OKTAVA_NARODENIA -- vespery su zo dna */

	}/* MODL_SPOL_CAST_SV_ZENA_[VIACERE]... */

	/* spolocna cast na sviatky panien */
	else if((a == MODL_SPOL_CAST_PANNA) ||
		(a == MODL_SPOL_CAST_PANNY_VIACERE)){

		Log("/* spolocna cast na sviatky panien */\n");
		modlitba = MODL_PRVE_VESPERY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			Log("  _set_zalmy_sviatok_panien(%s)...\n", nazov_modlitby[modlitba]);
			_set_zalmy_sviatok_panien(modlitba);
		}
		_spolocna_cast_full(modlitba);
		//_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file);
		if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
			_spolocna_cast_kresp_ve;

		/* ranne chvaly */
		modlitba = MODL_RANNE_CHVALY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			_set_zalmy_1nedele_rch();
		}
		_spolocna_cast_full(modlitba);
		if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
			_spolocna_cast_kresp_ve;

		/* vespery */
		if(_global_den.litobd != OBD_OKTAVA_NARODENIA){
			modlitba = MODL_VESPERY;
			if(_global_opt2 == MODL_ZALMY_ZO_SV){
				Log("  _set_zalmy_sviatok_panien(%s)...\n", nazov_modlitby[modlitba]);
				_set_zalmy_sviatok_panien(modlitba);
			}
			_spolocna_cast_full(modlitba);
			if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
				_spolocna_cast_kresp_ve;
		}/* v OBD_OKTAVA_NARODENIA -- vespery su zo dna */

	}/* MODL_SPOL_CAST_PANNA/viacere */

	/* spolocna cast na sviatky Panny Marie */
	else if(a == MODL_SPOL_CAST_PANNA_MARIA){

		Log("/* spolocna cast na sviatky Panny Marie */\n");
		modlitba = MODL_PRVE_VESPERY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			Log("  _set_zalmy_sviatok_panien(%s)...\n", nazov_modlitby[modlitba]);
			_set_zalmy_sviatok_panien(modlitba);
		}
		_spolocna_cast_full(modlitba);
		_spolocna_cast_prosby_viac(2, _anchor_head, _anchor, _file);
		if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
			_spolocna_cast_kresp_ve;

		/* ranne chvaly */
		modlitba = MODL_RANNE_CHVALY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			_set_zalmy_1nedele_rch();
		}
		_spolocna_cast_full(modlitba);
		_spolocna_cast_prosby_viac(2, _anchor_head, _anchor, _file);
		if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
			_spolocna_cast_kresp_ve;

		/* vespery */
		if(_global_den.litobd != OBD_OKTAVA_NARODENIA){
			modlitba = MODL_VESPERY;
			if(_global_opt2 == MODL_ZALMY_ZO_SV){
				Log("  _set_zalmy_sviatok_panien(%s)...\n", nazov_modlitby[modlitba]);
				_set_zalmy_sviatok_panien(modlitba);
			}
			_spolocna_cast_full(modlitba);
			_spolocna_cast_prosby_viac(2, _anchor_head, _anchor, _file);
			if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
				_spolocna_cast_kresp_ve;
		}/* v OBD_OKTAVA_NARODENIA -- vespery su zo dna */

	}/* MODL_SPOL_CAST_PANNA_MARIA */

	/* spolocna cast na oficium za zosnulych */
	else if(a == MODL_SPOL_CAST_ZA_ZOSNULYCH){

		Log("/* spolocna cast na oficium za zosnulych */\n");

		/* ranne chvaly */
		modlitba = MODL_RANNE_CHVALY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			Log("  _set_zalmy_za_zosnulych(%s)...\n", nazov_modlitby[modlitba]);
			_set_zalmy_za_zosnulych(modlitba);
		}
		_spolocna_cast_full(modlitba);
		if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
			_spolocna_cast_benediktus_ve;
		_spolocna_cast_ant3_viac(2, _anchor_head, _anchor, _file);

		/* vespery */
		if(_global_den.litobd != OBD_OKTAVA_NARODENIA){
			modlitba = MODL_VESPERY;
			if(_global_opt2 == MODL_ZALMY_ZO_SV){
				Log("  _set_zalmy_za_zosnulych(%s)...\n", nazov_modlitby[modlitba]);
				_set_zalmy_za_zosnulych(modlitba);
			}
			_spolocna_cast_full(modlitba);
			_spolocna_cast_kresponz_viac(2, _anchor_head, _anchor, _file);
			if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
				_spolocna_cast_magnifikat_ve;
		}/* v OBD_OKTAVA_NARODENIA -- vespery su zo dna */

	}/* MODL_SPOL_CAST_ZA_ZOSNULYCH */

	/* spolocna cast na sviatky posviacky chramu */
	else if(a == MODL_SPOL_CAST_POSVIACKA_CHRAMU){

		Log("/* spolocna cast na sviatky posviacky chramu */\n");
		modlitba = MODL_PRVE_VESPERY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			Log("  _set_zalmy_posviacka_chramu(%s)...\n", nazov_modlitby[modlitba]);
			_set_zalmy_posviacka_chramu(modlitba);
		}
		_spolocna_cast_full(modlitba);
		if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
			_spolocna_cast_kresponz_ve;
		if((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN))
			_spolocna_cast_ant1_3_po;

		/* ranne chvaly */
		modlitba = MODL_RANNE_CHVALY;
		if(_global_opt2 == MODL_ZALMY_ZO_SV){
			Log("  _set_zalmy_posviacka_chramu(%s)...\n", nazov_modlitby[modlitba]);
			_set_zalmy_posviacka_chramu(modlitba);
		}
		_spolocna_cast_full(modlitba);
		if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
			_spolocna_cast_kresponz_ve;

		/* vespery */
		if(_global_den.litobd != OBD_OKTAVA_NARODENIA){
			modlitba = MODL_VESPERY;
			if(_global_opt2 == MODL_ZALMY_ZO_SV){
				Log("  _set_zalmy_posviacka_chramu(%s)...\n", nazov_modlitby[modlitba]);
				_set_zalmy_posviacka_chramu(modlitba);
			}
			_spolocna_cast_full(modlitba);
			if((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN))
				_spolocna_cast_ant1_3_po;
			if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
				_spolocna_cast_kresponz_ve;
		}/* v OBD_OKTAVA_NARODENIA -- vespery su zo dna */

	}/* MODL_SPOL_CAST_POSVIACKA_CHRAMU */


	Log("_set_spolocna_cast(%s) -- end\n", nazov_spolc[a]);
}/* _set_spolocna_cast(); -- dva argumenty */

#define _set_spolocna_cast(a) _set_spolocna_cast(a, spol_cast)


#define set_LOG_spol_cast Log("          spol_cast == {%s (%d), %s (%d), %s (%d)}\n",	\
	nazov_spolc[spol_cast.a1], spol_cast.a1, \
	nazov_spolc[spol_cast.a2], spol_cast.a2, \
	nazov_spolc[spol_cast.a3], spol_cast.a3); Log

void set_spolocna_cast(_struct_sc spol_cast, int poradie_svaty){
	/* poradie_svaty je vstupom iba kvoli tomu, ze ak je 0,
	 * potom nas neznepokojuju vypisy typu Error: not assigned...
	 *
	 * 22/02/2000A.D.: ked nastavi vo formulari (detaily) zalmy zo `sviatku'
	 * a spolocnu cast `nebrat', predsa sa nevyvolaju zalmy zo sviatku,
	 * lebo sa nespusti _set_spolocna_cast(); !!! -- mozno by bolo dobre
	 * oddelit nastavenie pre spolocnu cast a potom inde dat samotne zalmy...
	 * !!!
	 */
	Log("set_spolocna_cast({%s, %s, %s}) -- begin\n",
		nazov_spolc[spol_cast.a1], nazov_spolc[spol_cast.a2], nazov_spolc[spol_cast.a3]);
	Log("          _global_opt3 == %s (%d)\n",
		nazov_spolc[_global_opt3], _global_opt3);

	Log("  teraz nastavujem POPIS (pre daneho svateho)...\n");
	strcpy(_anchor, _anchor_head);
	strcat(_anchor, ANCHOR_POPIS);
	modlitba = MODL_RANNE_CHVALY;
	set_popis(modlitba, _file, _anchor); /* pridane 05/04/2000A.D. */
	modlitba = MODL_VESPERY;
	set_popis(modlitba, _file, _anchor); /* pridane 05/04/2000A.D. */
	modlitba = MODL_PRVE_VESPERY;
	set_popis(modlitba, _file, _anchor); /* pridane 05/04/2000A.D. */
	/* 2003-06-30: tento POPIS nie je dobre nastaveny pre spomienku
	 * Nepoškvrneného Srdca prebl. Panny Márie,
	 * preto je tam nastaveny este raz na dummy, vid ZNOVUNASTAVENIE_POPISU_NA_DUMMY */

	/* tu bola pasaz, nastavujuca _global_opt3 na spol_cast.a1 v pripade,
	 * ze je neurcena;
	 * je teraz v sviatky_svatych() so styrmi vstupmi,
	 * pretoze sa musi vykonat iba pri druhom spusteni funkcie
	 * sviatky_svatych() -- 18/02/2000A.D.
	 */

	/* podla _global_opt3 urcime, ktoru spolocnu cast dat */
	if(spol_cast.a1 != MODL_SPOL_CAST_NEURCENA){
		if(_global_opt3 == spol_cast.a1){
			_set_spolocna_cast(_global_opt3);
		}
		else{
			if(spol_cast.a2 != MODL_SPOL_CAST_NEURCENA){
				if(_global_opt3 == spol_cast.a2){
					_set_spolocna_cast(_global_opt3);
				}
				else{
					if(spol_cast.a3 != MODL_SPOL_CAST_NEURCENA){
						if(_global_opt3 == spol_cast.a3){
							_set_spolocna_cast(_global_opt3);
						}
						else{
							if(_global_opt3 == MODL_SPOL_CAST_NEBRAT){
								set_LOG_spol_cast("  neberiem spolocnu cast\n");
								Export("<!--neberiem spolocnu cast-->");
							}
							else
							/* sem by to nemalo prist */
							{
							set_LOG_spol_cast("-- Error: spol_cast (a1, a2, a3) su sice urcene, ale _global_opt3 sa nerovna ani jednej z nich!\n");
							Export("%s\n", "Error: _global_opt3 assigned incorectly (a1, a2, a3 -- ok)");
							ALERT;
							return;
							}
						}
					}/* spol_cast.a3 je urcena */
					else{
						if(_global_opt3 == MODL_SPOL_CAST_NEBRAT){
							set_LOG_spol_cast("  neberiem spolocnu cast\n");
							Export("<!--neberiem spolocnu cast-->");
						}
						else
						/* sem by to nemalo prist */
						if(poradie_svaty != 0){
							set_LOG_spol_cast("-- Error: spol_cast (a1, a2) su sice urcene, ale _global_opt3 sa nerovna ani jednej z nich!\n");
							Export("%s\n", "Error: _global_opt3 assigned incorectly (a1, a2 -- ok)");
							ALERT;
							return;
						}
					}
				}
			}/* spol_cast.a2 je urcena */
			else{
				if(_global_opt3 == MODL_SPOL_CAST_NEBRAT){
					set_LOG_spol_cast("  neberiem spolocnu cast\n");
					Export("<!--neberiem spolocnu cast-->");
				}
				else
				/* sem by to nemalo prist */
				if(poradie_svaty != 0){
					set_LOG_spol_cast("-- Error: spol_cast (a1) je sice urcena, ale _global_opt3 sa jej nerovna!\n");
					Export("%s\n", "Error: _global_opt3 assigned incorectly (a1 -- ok)");
					ALERT;
					return;
				}
			}
		}
	}/* spol_cast.a1 je urcene */
	else{
		/* sem by to nemalo prist */
		if(poradie_svaty != 0){
			Log("-- Error: spol_cast (a1) nie je urcene; _global_opt3 == %s\n", nazov_spolc[_global_opt3]);
			Export("%s\n", "Error: a1 (member of spol_cast) assigned incorectly");
			ALERT;
			return;
		}
	}
	Log("set_spolocna_cast(_global_opt3 == %s) -- end\n", nazov_spolc[_global_opt3]);
}/* set_spolocna_cast(); */

/* ... a teraz samotna funkcia sviatky_svatych(): */
int sviatky_svatych(int den, int mesiac, int poradie_svaty){
	/* toto priradujeme preto, aby sme nemuseli pri kazdom svatom
	 * priradovat pocet = 1; */
	int pocet = 1;
	
	Log("-- sviatky_svatych(%d, %d) -- zaciatok\n", den, mesiac);

	/* nasledujuca pasaz v pripade, ze poradie_svaty nie je dane (t.j. nie je
	 * 1, 2 alebo 3) vycisti udaje;
	 * to je vtedy, ked je tato funkcia volana poprvykrat
	 */

	if((poradie_svaty < 1) || (poradie_svaty > 3)){
		/* den */
		_global_svaty1.den = _global_svaty2.den = _global_svaty3.den = den;
		/* mesiac */
		_global_svaty1.mesiac = _global_svaty2.mesiac = _global_svaty3.mesiac = mesiac;
		/* rok */
		_global_svaty1.rok = _global_svaty2.rok = _global_svaty3.rok = _global_den.rok;
		/* denvt */
		_global_svaty1.denvt = _global_svaty2.denvt = _global_svaty3.denvt = _global_den.denvt;
		/* denvr */
		_global_svaty1.denvr = _global_svaty2.denvr = _global_svaty3.denvr = _global_den.denvr;
		/* smer */
		_global_svaty1.smer = _global_svaty2.smer = _global_svaty3.smer = _global_den.smer;
		/* litobd */
		_global_svaty1.litobd = _global_svaty2.litobd = _global_svaty3.litobd = _global_den.litobd;
		/* litrok */
		_global_svaty1.litrok = _global_svaty2.litrok = _global_svaty3.litrok = _global_den.litrok;
		/* tyzden */
		_global_svaty1.tyzden = _global_svaty2.tyzden = _global_svaty3.tyzden = _global_den.tyzden;
		/* tyzzal */
		_global_svaty1.tyzzal = _global_svaty2.tyzzal = _global_svaty3.tyzzal = _global_den.tyzzal;
		/* typslav - neurcena */
		_global_svaty1.typslav = _global_svaty2.typslav = _global_svaty3.typslav = SLAV_NEURCENE;
		/* prik - nie je prikazany */
		_global_svaty1.prik = _global_svaty2.prik = _global_svaty3.prik = NEPRIKAZANY_SVIATOK;
		/* meno - neurcene */
		strcpy(_global_svaty1.meno, "");
		strcpy(_global_svaty2.meno, "");
		strcpy(_global_svaty3.meno, "");
		/* spolcast - neurcena */
		_global_svaty1.spolcast = _global_svaty2.spolcast = _global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA);
		Log("nastavil som _global_svaty[1,2,3] na default (bud neurcene alebo z _global_den)\n");
	}
	else{
		/* povodne tu bola pasaz, ktora podla poradie_svaty nastavila
		 * do _global_den = _global_svaty[1,2,3],
		 * tato pasaz je teraz na zaciatku sviatky_svatych() so styrmi
		 * vstupmi/argumentami
		 */
		Log("   (tu bola pasaz, co je teraz v sviakty_svatych() so 4 vstupmi)\n");
	}
	/* dalsia cast v zatvorkach {, } je sice len pre pripad, ze
	 * poradie_svaty == 1, 2, 3; avsak aj pre 0 je to
	 * preto, ze aj ked nie je svaty urceny, moze ist o slavnost,
	 * ktora ma takmer najvacsiu prioritu, a preto ma aj prve
	 * vespery - a vtedy by to normalne nefungovalo
	 */
	{/* pasaz kt. ma zmysel len pre poradie_svaty == 1, 2, 3, ale
	  * v pripade slavnosti aj pre == 0 */
		Log("/* nastavenie nazvu suboru, kotvy apod. (sviatky_svatych) */\n");
		/* nastavenie nazvu suboru, kotvy apod. */
		if(poradie_svaty > 1) /* pridame cislo svateho */
			sprintf(_anchor_head, "%02d%s%d_", den, nazov_MES[mesiac - 1], poradie_svaty);
		else
			sprintf(_anchor_head, "%02d%s_", den, nazov_MES[mesiac - 1]);
		Log("  _anchor_head == %s\n", _anchor_head);

		sprintf(_file, "sv_%s.htm", nazov_mes[mesiac - 1]);
		Log("  _file == %s\n", _file);
	}

	/* LOG_ciara_sv; Log("_global_den: \n"); Log(_global_den); */

	/* az teraz, ked je v _global_den (pri druhom volani fcie)
	 * spravna hodnota z _global_svaty[1,2,3], mozem urobit toto
	 * priradenie do spol_cast
	 */
	_struct_sc spol_cast = _decode_spol_cast(_global_den.spolcast);

	/* a teraz velky switch()... 'Velky inkvizitor'... ;-) */
	switch(mesiac - 1){
		case MES_JAN:
			switch(den){
				case 2:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Bazila Ve¾kého a Gregora Nazianského, biskupov a uèite¾ov Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_VIACERI, MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 7:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Rajmunda z Peòafortu, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
					break;
				case 13:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Hilára, biskupa a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 17:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Antona, opáta");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 20:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					else if(poradie_svaty == 2){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Fabiána, pápeža a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK,
							MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
					pocet = 2;
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty2.meno, "Sv. Šebastiána, muèeníka");
					_global_svaty2.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
					break;
				case 21:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full_okrem_prosieb(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full_okrem_prosieb(modlitba);

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Agnesy, panny a muèenice");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENICA,
							MODL_SPOL_CAST_PANNA);
					break;
				case 22:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Vincenta, diakona a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
					break;
				case 24:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Františka Saleského, biskupa a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 25:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full_okrem_prosieb(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full_okrem_prosieb(modlitba);

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Obrátenie sv. Pavla, apoštola");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
					break;
				case 26:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Timoteja a Títa, biskupov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				case 27:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Angely Merici, panny");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA,
							MODL_SPOL_CAST_SV_ZENA_VYCH);
					break;
				case 28:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Tomáška Akvinského, kòaza a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_UCITEL_CIRKVI,
							MODL_SPOL_CAST_DUCH_PAST_KNAZ);
						/* ...KNAZ nie je vo vlastnej casti, avsak aby sme vedeli,
						 * co mame dat v tych castiach, ktore nie su v uciteloch
						 * cirkvi, kde sa odvolava na duchovnych pastierov
						 * 23/02/2000A.D.
						 */
					break;
				case 31:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Jána Boska, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_SV_MUZ_VYCH);
					break;
				default: break;
			}; break; /* case MES_JAN */
		case MES_FEB:
			switch(den){
				case 1:
					break;
#ifdef WRONG_23_02_2000
					if(!((_global_den.denvt == DEN_SOBOTA) && (_global_modlitba == MODL_VESPERY)))
						break;
					else{
						den++;
						sprintf(_anchor_head, "%02d%s_", den, nazov_MES[mesiac - 1]);
						Log("  _anchor_head == %s\n", _anchor_head);
					}
#endif
					/* v opacnom pripade sa ide na case 2:
					 * treba vsak upravit kotvu _anchor
					 */
				case 2:
					//if(poradie_svaty == 1){
					if((poradie_svaty == 0) || (poradie_svaty == 1)){
						/* definovanie parametrov pre modlitbu */

						if((poradie_svaty == 1) &&
						  (query_type != PRM_DETAILY))
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_PRVE_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_sviatok_krstu(modlitba);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_1nedele_rch();

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_sviatok_krstu(modlitba);

						if(poradie_svaty != 0) break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 5; /* sviatky Pana uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Obetovanie Pána");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
					break;
				case 3:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					else if(poradie_svaty == 2){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Blažeja, biskupa a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK,
							MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					pocet = 2;
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty2.meno, "Sv. Oskára, biskupa");
					_global_svaty2.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				case 5:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}

					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Agaty, panny a muèenice");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENICA,
							MODL_SPOL_CAST_PANNA);
					break;
				case 6:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}

					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Pavla Mikiho a spoloèníkov, muèeníkov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
					break;
				case 8:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Hieronyma Emilianiho");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_VYCH);
					break;
				case 10:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Školastiky, panny");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA);
					break;
				case 11:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Prebl. Panny Márie Lurdskej");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
					break;
				case 14:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					/* na Slovensku 5. jula, slavnost, v Europe sviatok */
					_global_svaty1.typslav = SLAV_SPOMIENKA; /* !!! SLAV_LUB_SPOMIENKA ??? */
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Cyrila, mnícha, a sv. Metoda, biskupa");
					_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_VIACERI);
					break;
				case 17:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Siedmich svätých zakladate¾ov rehole Služobníkov Panny Márie");
					_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 21:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Petra Damianiho, biskupa a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 22:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_antifony;
                  _vlastna_cast_kcitanie;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_antifony;
						_vlastna_cast_kcitanie;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Katedra sv. Petra, apoštola");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
					break;
				case 23:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Polykarpa, biskupa a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK,
							MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				default:
					break;
			}; break; /* case MES_FEB */
		case MES_MAR:
			switch(den){
				case 4:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Kazimíra");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
					break;
				case 7:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Perpetuy a Felicity, muèeníc");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
					break;
				case 8:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Jána z Boha, reho¾níka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK,
							MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
					break;
				case 9:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Františky Rímskej, reho¾níèky");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
					break;
				case 17:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Patrika, biskupa");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				case 18:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;
						/* nema modlitba = MODL_VESPERY, lebo su prve vespery slavnosti sv. Jozefa */
						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Cyrila Jeruzalemského, biskupa a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 19:
label_19_MAR:
					//if(poradie_svaty == 1){
					if((poradie_svaty == 0) || (poradie_svaty == 1)){
						/* definovanie parametrov pre modlitbu */

						if((poradie_svaty == 1) &&
						  (query_type != PRM_DETAILY))
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_PRVE_VESPERY;
						_vlastna_cast_full(modlitba);
						if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
							_vlastna_cast_kresponz_ve;
						}
						else if((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)){
							_vlastna_cast_kresponz_po;
						}
						_set_zalmy_sviatok_duch_past(modlitba);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);
						if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
							_vlastna_cast_kresponz_ve;
						}
						else if((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)){
							_vlastna_cast_kresponz_po;
						}
						_set_zalmy_1nedele_rch();

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);
						if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
							_vlastna_cast_kresponz_ve;
						}
						else if((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)){
							_vlastna_cast_kresponz_po;
						}
						_set_zalmy_sviatok_duch_past(modlitba);

						if(poradie_svaty != 0) break;
					}
					_global_svaty1.typslav = SLAV_SLAVNOST;
					_global_svaty1.smer = 3; /* slavnosti Pana, preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Sv. Jozefa, ženícha Panny Márie");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
					break;
				case 20:
					if(_global_den.denvt == DEN_PONDELOK){
						/* t.j. slavnost sv. Jozefa padla na nedelu */
						sprintf(_anchor_head, "%02d%s_", den - 1, nazov_MES[mesiac - 1]);
						Log("  _anchor_head == %s\n", _anchor_head);
						Log("jumping to label_19_MAR...\n");
						goto label_19_MAR;
					}
					break;
				case 23:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Turibia de Mongrovejo, biskupa");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				case 25:
label_25_MAR:
					//if(poradie_svaty == 1){
					if((poradie_svaty == 0) || (poradie_svaty == 1)){
						/* definovanie parametrov pre modlitbu */

						if((poradie_svaty == 1) &&
						  (query_type != PRM_DETAILY))
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_PRVE_VESPERY;
						_vlastna_cast_full(modlitba);
						if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
							_vlastna_cast_kresponz_ve;
						}
						else if((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)){
							_vlastna_cast_kresponz_po;
						}
						_set_zalmy_sviatok_krstu(modlitba);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);
						if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
							_vlastna_cast_kresponz_ve;
						}
						else if((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)){
							_vlastna_cast_kresponz_po;
						}
						_set_zalmy_1nedele_rch();

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);
						if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
							_vlastna_cast_kresponz_ve;
						}
						else if((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)){
							_vlastna_cast_kresponz_po;
						}
						_set_zalmy_sviatok_krstu(modlitba);

						if(poradie_svaty != 0) break;
					}
					_global_svaty1.typslav = SLAV_SLAVNOST;
					_global_svaty1.smer = 3; /* slavnosti Pana, preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Zvestovanie Pána");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
					break;
				case 26:
					if(_global_den.denvt == DEN_PONDELOK){
						/* t.j. Zvestovanie Pana padlo na nedelu */
						sprintf(_anchor_head, "%02d%s_", den - 1, nazov_MES[mesiac - 1]);
						Log("  _anchor_head == %s\n", _anchor_head);
						Log("jumping to label_25_MAR...\n");
						goto label_25_MAR;
					}
					break;
			}; break; /* case MES_MAR */
		case MES_APR:
			switch(den){
				case 2:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Františka z Pauly, pustovníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 4:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Izidora, biskupa a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 5:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Vincenta Ferrera, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
					break;
				case 7:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Jána Krstite¾a de la Salle, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_SV_MUZ_VYCH);
					break;
				case 11:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Stanislava, biskupa a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK,
							MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				case 13:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Martina I., pápeža a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK,
							MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
					break;
				case 21:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Anzelma, biskupa a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 23:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Vojtecha, biskupa a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK,
							MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				case 24:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					else if(poradie_svaty == 2){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Juraja, muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
					pocet = 2;
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty2.meno, "Sv. Fidéla zo Sigmaringenu, kòaza a muèeníka");
					_global_svaty2.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK,
							MODL_SPOL_CAST_DUCH_PAST_KNAZ);
					break;
				case 25:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Sv. Marka, evanjelistu");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
					break;
				case 28:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					else if(poradie_svaty == 2){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Petra Chanela, kòaza a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
					pocet = 2;
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty2.meno, "Sv. ¼udovíta Márie Grignion de Montfort, kòaza");
					_global_svaty2.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
					break;
				case 29:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Kataríny Sienskej, panny a uèite¾ky Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA);
					break;
				case 30:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Pia V., pápeža");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
					break;
			}; break; /* case MES_APR */
		case MES_MAY:
			switch(den){
				case 1:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_kcitanie;
						_vlastna_cast_kresponz;
						_vlastna_cast_benediktus;
						_vlastna_cast_prosby;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_kcitanie;
						_vlastna_cast_kresponz;
						_vlastna_cast_magnifikat;
						_vlastna_cast_prosby;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Jozefa, robotníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
					break;
				case 2:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Atanáza, biskupa a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 3:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_antifony;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_antifony;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Sv. Filipa a Jakuba, apoštolov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
					break;
				case 12:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					else if(poradie_svaty == 2){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Nerea a Achila, muèeníkov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
					pocet = 2;
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty2.meno, "Sv. Pankráca, muèeníka");
					_global_svaty2.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
					break;
				case 14:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;
						_vlastna_cast_benediktus;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;
						_vlastna_cast_magnifikat;

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Sv. Mateja, apoštola");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
					break;
				case 16:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);
						if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
							_vlastna_cast_kresponz_ve;
						/* inak zostane cezrocne, ale bez pripony */

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);
						if((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
							_vlastna_cast_kresponz_ve;
						/* inak zostane cezrocne, ale bez pripony */

						break;
					}
					/* v roznavskej dieceze sviatok (hlavny patron) */
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Jána Nepomuckého, kòaza a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK,
							MODL_SPOL_CAST_DUCH_PAST_KNAZ);
					break;
				case 18:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Jána I., pápeža a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK,
							MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
					break;
				case 20:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Bernardína Sienského, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 25:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					else if(poradie_svaty == 2){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					else if(poradie_svaty == 3){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Bédu Ctihodného, kòaza a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_UCITEL_CIRKVI,
							MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					pocet = 3;
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty2.meno, "Sv. Gregora VII., pápeža");
					_global_svaty2.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
					_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty3.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty3.meno, "Sv. Márie Magdalény de' Pazzi, panny");
					_global_svaty3.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA,
							MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
					break;
				case 26:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Filipa Neriho, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 27:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Augustína z Canterbury, biskupa");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				case 31:
					/* na slovensku sa slavi 2. jula */
					break;
			}; break; /* case MES_MAY */
		case MES_JUN:
			switch(den){
				case 1:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Justína, muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
					break;
				case 2:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Marcelína a Petra, muèeníkov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
					break;
				case 3:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Karola Lwangu a spoloèníkov, muèeníkov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
					break;
				case 5:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Bonifáca, biskupa a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK,
							MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				case 6:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Norberta, biskupa");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				case 9:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Efréma, diakona a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 11:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						_global_opt2 = MODL_ZALMY_ZO_DNA; /* zalmy a antifony zo dna */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_kcitanie;
						_vlastna_cast_kresponz;
						_vlastna_cast_benediktus;
						_vlastna_cast_prosby;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_kcitanie;
						_vlastna_cast_kresponz;
						_vlastna_cast_magnifikat;
						_vlastna_cast_prosby;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Barnabáša, apoštola");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
					break;
				case 13:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Antona Paduánskeho, kòaza a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_UCITEL_CIRKVI,
							MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 19:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Romualda, opáta");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 21:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Alojza Gonzágu, reho¾níka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 22:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					else if(poradie_svaty == 2){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Jána Fishera, biskupa, a sv. Tomáša Mórusa, muèeníkov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
					pocet = 2;
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty2.meno, "Sv. Pavlína z Noly, biskupa");
					_global_svaty2.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				case 24:
					//if(poradie_svaty == 1){
					if((poradie_svaty == 0) || (poradie_svaty == 1)){
						/* definovanie parametrov pre modlitbu */

						if((poradie_svaty == 1) &&
						  (query_type != PRM_DETAILY))
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_PRVE_VESPERY;
						_vlastna_cast_full(modlitba);
						_vlastna_cast_modlitba_prve_vesp;
						_set_zalmy_sviatok_duch_past(modlitba);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_1nedele_rch();

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_sviatok_duch_past(modlitba);

						if(poradie_svaty != 0) break;
					}
					_global_svaty1.typslav = SLAV_SLAVNOST;
					_global_svaty1.smer = 3; /* slavnosti Pana, preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Narodenie sv. Jána Krstite¾a");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
					break;
				case 25:
					/* hoci slavnost narodenia sv. Jana Krstitela padla na nedelu, 
					 * slavi sa v nedelu, lebo ide o nedelu v obdobi cez rok, 
					 * ktora ma nizsiu prioritu,
					 * preto to, co tu bolo 
						if(_global_den.denvt == DEN_PONDELOK){
							sprintf(_anchor_head, "%02d%s_", den - 1, nazov_MES[mesiac - 1]);
							Log("  _anchor_head == %s\n", _anchor_head);
							Log("jumping to label_24_JUN...\n");
							goto label_24_JUN;
						}
					 * nema opodstatnenie; 
					 * 21/03/2000A.D.
					 */
					break;
				case 27:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					else if(poradie_svaty == 2){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}

					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Cyrila Alexandrijského, biskupa a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					pocet = 2;
					/* v trnavskej, banskobystrickej, roznavskej a nitrianskej dieceze */
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty2.meno, "Sv. Ladislava");
					_global_svaty2.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
					break;
				case 28:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;
						/* nema vespery, lebo su 1. vespery zo sv. petra a pavla */

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Ireneja, biskupa a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK,
							MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				case 29:
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
					if((poradie_svaty == 0) || (poradie_svaty == 1)){
						/* preto 0, ze aj ked nie je svaty urceny, ide o slavnost,
						 * ktora ma takmer najvacsiu prioritu, a preto ma aj prve
						 * vespery - a vtedy by to normalne nefungovalo;
						 * nastavenie veci pre modlitbu by sa muselo diat
						 * v predoslom dni, co je neciste riesenie
						 */
						/* definovanie parametrov pre modlitbu */

						spol_cast = _decode_spol_cast(_global_svaty1.spolcast);
						Log("Peter a Pavol: spol_cast: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc[spol_cast.a1], nazov_spolc[spol_cast.a2], nazov_spolc[spol_cast.a3], poradie_svaty);

						if(/*(poradie_svaty == 1) && */ // 23/02/2000A.D.
						  (query_type != PRM_DETAILY))
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_PRVE_VESPERY;
						_vlastna_cast_full(modlitba);
						_vlastna_cast_modlitba_prve_vesp;
						_set_zalmy_sviatok_apostolov(modlitba);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_sviatok_apostolov(modlitba);

						if(poradie_svaty != 0) break;
					}
					_global_svaty1.typslav = SLAV_SLAVNOST;
					_global_svaty1.smer = 3; /* slavnosti Pana, preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					_global_svaty1.prik = PRIKAZANY_SVIATOK;
					strcpy(_global_svaty1.meno, "Sv. Petra a Pavla, apoštolov");
					break;
				case 30:
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Prvých svätých muèeníkov Cirkvi v Ríme");
					/* hoci slavnost sv. Petra a Pavla padla na nedelu, 
					 * slavi sa v nedelu, lebo ide o nedelu v obdobi cez rok, 
					 * ktora ma nizsiu prioritu,
					 * preto to, co tu bolo 
					 * "if(_global_den.denvt == DEN_PONDELOK) goto label_29_JUN;"
					 * nema opodstatnenie; porov. r. 1997
					 * 21/03/2000A.D.
					 */
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;
						_vlastna_cast_benediktus;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;
						_vlastna_cast_magnifikat;

						break;
					}
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
					break;
			}; break; /* case MES_JUN */
		case MES_JUL:
			switch(den){
				case 2:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Návšteva prebl. Panny Márie");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
					break;
				case 3:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full_okrem_prosieb(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_antifony_ako_na_ranne_chvaly;
                  _vlastna_cast_kcitanie;
						_vlastna_cast_kresponz;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Sv. Tomáša, apoštola");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
					break;
				case 4:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						/* nema vespery, lebo su 1. vespery zo sv. cyrila a metoda */

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Alžbety Portugalskej");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL);
					break;
				case 5:
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
					if((poradie_svaty == 0) || (poradie_svaty == 1)){
						/* preto 0, ze aj ked nie je svaty urceny, ide o slavnost,
						 * ktora ma takmer najvacsiu prioritu, a preto ma aj prve
						 * vespery - a vtedy by to normalne nefungovalo;
						 * nastavenie veci pre modlitbu by sa muselo diat
						 * v predoslom dni, co je neciste riesenie
						 */
						/* definovanie parametrov pre modlitbu */

						spol_cast = _decode_spol_cast(_global_svaty1.spolcast);
						Log("Cyril a Metod: spol_cast: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc[spol_cast.a1], nazov_spolc[spol_cast.a2], nazov_spolc[spol_cast.a3], poradie_svaty);

						if(/*(poradie_svaty == 1) && */ // 23/02/2000A.D. -- prevzate z Petra a Pavla, 23/03/2000A.D.
						  (query_type != PRM_DETAILY))
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_PRVE_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_slavnost_Cyrila_a_Metoda(modlitba);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_slavnost_Cyrila_a_Metoda(modlitba);

						if(poradie_svaty != 0) break;
					}
					_global_svaty1.typslav = SLAV_SLAVNOST;
					_global_svaty1.smer = 3; /* slavnosti Pana, preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Sv. Cyrila a Metoda, slovanských vierozvestov, apoštolov");
					break;
				case 6:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Márie Goretti, panny a muèenice");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENICA,
							MODL_SPOL_CAST_PANNA);
					/* hoci slavnost sv. Cyrila a Metoda padla na nedelu, 
					 * slavi sa v nedelu, lebo ide o nedelu v obdobi cez rok, 
					 * ktora ma nizsiu prioritu,
					 * preto to, co tu bolo 
					 * "if(_global_den.denvt == DEN_PONDELOK) goto label_5_JUL;"
					 * nema opodstatnenie; porov. 1998
					 * 21/03/2000A.D.
					 */
					break;
				case 7:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Antona Márie Zaccariu, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_SV_MUZ_VYCH,
							MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 11:
					/* spomienka, v Europe sviatok */
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
                  _vlastna_cast_hymnus;
						_vlastna_cast_benediktus
                  _vlastna_cast_prosby;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
                  _vlastna_cast_hymnus;
						_vlastna_cast_kresponz;
						_vlastna_cast_magnifikat;
                  _vlastna_cast_prosby;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Sv. Benedikta, opáta");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 13:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Henricha");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
					break;
				case 14:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Kamila de Lellis, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
					break;
				case 15:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Bonaventúru, biskupa a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 16:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Prebl. Panny Márie Karmelskej");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
					break;
				case 17:
					/* v Nitrianskej dieceze sviatok - hlavni patroni */
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_antifony;
                  _vlastna_cast_kresponz;
						_vlastna_cast_benediktus;
						_vlastna_cast_prosby;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_antifony;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Andreja-Svorada a Benedikta, pustovníkov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_VIACERI);
					break;
				case 21:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Vavrinca z Brindisi, kòaza a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 22:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_antifony;
                  _vlastna_cast_kresponz;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_antifony;
                  _vlastna_cast_kresponz;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Márie Magdalény");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_ZENA);
					break;
				case 23:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					/* _global_svaty1.smer = 12; */
					/* zmena, na ktoru ma mailom zo dna Monday, July 23, 2001 11:40 AM upozornil 
					 * Marian Valábek,SDB <marian.valabek@donbosco.sk>:
					 * "Prosím opravte Sv. Brigita je spolu so sv. Katarínou Sienskou a 
					 *  sv. Teréziou Benediktou z Kríza spolupatrónkou Európy a teda je 
					 *  to v Európe sviatok od 1999."
					 * 07/09/2001A.D.
					 */
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Brigity, reho¾níèky");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
					break;
				case 25:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_antifony;
                  _vlastna_cast_kcitanie;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_antifony;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Sv. Jakuba, apoštola");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
					break;
				case 26:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
                  _vlastna_cast_kcitanie;
                  _vlastna_cast_kresponz;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
                  _vlastna_cast_kcitanie;
                  _vlastna_cast_kresponz;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Joachima a Anny, rodièov Panny Márie");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
					break;
				case 27:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Gorazda a spoloèníkov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_VIACERI);
					break;
				case 29:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Marty");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_ZENA);
					break;
				case 30:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Petra Chryzológa, biskupa a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 31:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Ignáca z Loyoly, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
			}; break; /* case MES_JUL */
		case MES_AUG:
			switch(den){
				case 1:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Alfonza Márie de' Ligouri, biskupa a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 2:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					else if(poradie_svaty == 2){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Euzébia Vercellského, biskupa");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					pocet = 2;
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty2.meno, "Sv. Petra Juliána Eymard, kòaza");
					_global_svaty2.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 4:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Jána Márie Vianneya, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
					break;
				case 5:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Výroèie posviacky hlavnej mariánskej baziliky v Ríme");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
					break;
				case 6:
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
					if((poradie_svaty == 0) || (poradie_svaty == 1)){
						/* preto 0, ze aj ked nie je svaty urceny, ide o sviatok Pana,
						 * ktora ma velku prioritu, a preto ma aj - ak je nedela - prve
						 * vespery 
						 */
						/* definovanie parametrov pre modlitbu */

						spol_cast = _decode_spol_cast(_global_svaty1.spolcast);
						Log("Premenenie Pana: spol_cast: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc[spol_cast.a1], nazov_spolc[spol_cast.a2], nazov_spolc[spol_cast.a3], poradie_svaty);

						if(/*(poradie_svaty == 1) && */ // 23/02/2000A.D. -- prevzate z Petra a Pavla, 28/03/2000A.D.
						  (query_type != PRM_DETAILY))
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_PRVE_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_premenenie(modlitba);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_premenenie(modlitba); /* preto, lebo nespustame zaltar(); 28/03/2000A.D. */

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_premenenie(modlitba);

						if(poradie_svaty != 0) break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 5; /* sviatky Pana uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Premenenie Pána");
					break;
				case 7:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					else if(poradie_svaty == 2){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Sixta II., pápeža, a jeho spoloèníkov, muèeníkov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
					pocet = 2;
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty2.meno, "Sv. Kajetána, kòaza");
					_global_svaty2.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 8:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Dominika, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 9:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					/* _global_svaty1.smer = 12; */
					/* zmena, na ktoru ma mailom zo dna Monday, July 23, 2001 11:40 AM upozornil 
					 * Marian Valábek,SDB <marian.valabek@donbosco.sk>:
					 * "Prosím opravte Sv. Brigita je spolu so sv. Katarínou Sienskou a 
					 *  sv. Teréziou Benediktou z Kríza spolupatrónkou Európy a teda je 
					 *  to v Európe sviatok od 1999."
					 * 26/09/2001A.D.
					 */
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Terézie Benedikty, reho¾níèky a muèenice");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_REHOLNIK,
							MODL_SPOL_CAST_MUCENICA);
					break;
				case 10:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full_okrem_prosieb(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full_okrem_prosieb(modlitba);

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Sv. Vavrinca, diakona a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
					break;
				case 11:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Kláry, panny");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA,
							MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
					break;
				case 13:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Ponciána, pápeža, a sv. Hypolita, kòaza, muèeníkov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV,
							MODL_SPOL_CAST_DUCH_PAST_VIACERI);
					break;
				case 14:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						/* nema vespery, lebo su prve vespery nanebovzatia p. marie */
						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Maximiliána Kolbeho, kòaza a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_MUCENIK);
					break;
				case 15:
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
					if((poradie_svaty == 0) || (poradie_svaty == 1)){
						/* preto 0, ze aj ked nie je svaty urceny, ide o sviatok Pana,
						 * ktora ma velku prioritu, a preto ma aj - ak je nedela - prve
						 * vespery 
						 */
						/* definovanie parametrov pre modlitbu */

						spol_cast = _decode_spol_cast(_global_svaty1.spolcast);
						Log("Premenenie Pana: spol_cast: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc[spol_cast.a1], nazov_spolc[spol_cast.a2], nazov_spolc[spol_cast.a3], poradie_svaty);

						if(/*(poradie_svaty == 1) && */ // 23/02/2000A.D. -- prevzate z Petra a Pavla, 28/03/2000A.D.
						  (query_type != PRM_DETAILY))
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_PRVE_VESPERY;
						_vlastna_cast_full(modlitba);
						_vlastna_cast_modlitba_prve_vesp;
						_set_zalmy_sviatok_panien(modlitba);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_sviatok_panien(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_sviatok_panien(modlitba);

						if(poradie_svaty != 0) break;
					}
					_global_svaty1.typslav = SLAV_SLAVNOST;
					_global_svaty1.smer = 3; /* slavnosti Pana, preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					_global_svaty1.prik = PRIKAZANY_SVIATOK;
					strcpy(_global_svaty1.meno, "Nanebovzatie prebl. Panny Márie");
					break;
				case 16:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Štefana Uhorského");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
					break;
				case 19:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Jána Eudes, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 20:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Bernarda, opáta a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_UCITEL_CIRKVI,
							MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 21:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Pia X., pápeža");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
					break;
				case 22:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Prebl. Panny Márie Krá¾ovnej");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
					break;
				case 23:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Ruženy Limskej, panny");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA,
							MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
					break;
				case 24:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Sv. Bartolomeja, apoštola");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
					break;
				case 25:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					else if(poradie_svaty == 2){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Jozefa de Calasanz, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_VYCH,
							MODL_SPOL_CAST_DUCH_PAST_KNAZ);
					pocet = 2;
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty2.meno, "Sv. ¼udovíta");
					_global_svaty2.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
					break;
				case 27:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Moniky");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_ZENA);
					break;
				case 28:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Augustína, biskupa a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 29:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Muèenícka smr sv. Jána Krstite¾a");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
					break;
			}; break; /* case MES_AUG */
		case MES_SEP:
			switch(den){
				case 3:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Gregora Ve¾kého, pápeža a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 7:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Marka Križina, Melichara Grodzieckého a Štefana Pongrácza, kòazov a muèeníkov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
					break;
				case 8:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full_okrem_prosieb(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full_okrem_prosieb(modlitba);

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Narodenie prebl. Panny Márie");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
					break;
				case 9:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Petra Clavera, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
					break;
				case 12:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Mena prebl. Panny Márie");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
					break;
				case 13:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Jána Zlatoústeho, biskupa a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 14:
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
					if((poradie_svaty == 0) || (poradie_svaty == 1)){
						/* preto 0, ze aj ked nie je svaty urceny, ide o sviatok Pana,
						 * ktora ma velku prioritu, a preto ma aj - ak je nedela - prve
						 * vespery 
						 */
						/* definovanie parametrov pre modlitbu */

						spol_cast = _decode_spol_cast(_global_svaty1.spolcast);
						Log("Povysenie sv. Kriza: spol_cast: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc[spol_cast.a1], nazov_spolc[spol_cast.a2], nazov_spolc[spol_cast.a3], poradie_svaty);

						if(/*(poradie_svaty == 1) && */ // 23/02/2000A.D. -- prevzate z Petra a Pavla, 28/03/2000A.D.
						  (query_type != PRM_DETAILY))
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_PRVE_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_sv_kriz(modlitba);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_sv_kriz(modlitba); /* preto, lebo nespustame zaltar(); 28/03/2000A.D. */

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_sv_kriz(modlitba);

						if(poradie_svaty != 0) break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 5; /* sviatky Pana uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Povýšenie svätého kríža");
					break;
				case 15:
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
					if((poradie_svaty == 0) || (poradie_svaty == 1)){
						/* preto 0, ze aj ked nie je svaty urceny, ide o slavnost,
						 * ktora ma takmer najvacsiu prioritu, a preto ma aj prve
						 * vespery - a vtedy by to normalne nefungovalo;
						 * nastavenie veci pre modlitbu by sa muselo diat
						 * v predoslom dni, co je neciste riesenie
						 */
						/* definovanie parametrov pre modlitbu */

						spol_cast = _decode_spol_cast(_global_svaty1.spolcast);
						Log("Sedembolestnej Panny Marie, patronky Slovenska: spol_cast: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc[spol_cast.a1], nazov_spolc[spol_cast.a2], nazov_spolc[spol_cast.a3], poradie_svaty);

						if(/*(poradie_svaty == 1) && */ // 23/02/2000A.D.; zobrate z 8.dec; 28/03/2000A.D.
						  (query_type != PRM_DETAILY))
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_PRVE_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_sviatok_panien(modlitba);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_sviatok_panien(modlitba);

						if(poradie_svaty != 0) break;
					}
					_global_svaty1.typslav = SLAV_SLAVNOST;
					_global_svaty1.smer = 3; /* slavnosti Pana, preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Sedembolestnej Panny Márie, patrónky Slovenska");
					break;
				case 16:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Kornélia, pápeža, a sv. Cypriána, biskupa, muèeníkov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV,
							MODL_SPOL_CAST_DUCH_PAST_VIACERI);
					break;
				case 17:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Róberta Bellarmína, biskupa a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 19:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Januára, biskupa a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK,
							MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				case 20:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Andreja Kim Taegona, kòaza, a sv. Pavla Chong Hasanga a spoloèníkov, muèeníkov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
					break;
				case 21:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Sv. Matúša, apoštola a evanjelistu");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
					break;
				case 26:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Kozmu a Damiána, muèeníkov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
					break;
				case 27:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Vincenta de Paul, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
					break;
				case 28:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					else if(poradie_svaty == 2){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Václava, muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
					pocet = 2;
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty2.meno, "Sv. Vavrinca Ruiza a spoloèníkov, muèeníkov");
					_global_svaty2.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
					break;
				case 29:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_archanjelov(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_archanjelov(modlitba);

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Sv. Michala, Gabriela a Rafaela, archanjelov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
					break;
				case 30:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Hieronyma, kòaza a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
			}; break; /* case MES_SEP */
		case MES_OCT:
			switch(den){
				case 1:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Terézie z Lisieux, panny a uèite¾ky Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 2:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_anjelov_strazcov(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_anjelov_strazcov(modlitba);

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Svätých anjelov strážcov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
					break;
				case 4:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Františka Assiského");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 6:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Bruna, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 7:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full_okrem_prosieb(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full_okrem_prosieb(modlitba);

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Ružencovej prebl. Panny Márie");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
					break;
				case 9:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					else if(poradie_svaty == 2){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Dionýzia, biskupa, a spoloèníkov, muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
					pocet = 2;
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty2.meno, "Sv. Jána Leonardiho, kòaza");
					_global_svaty2.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
					break;
				case 14:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Kalixta I., pápeža a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK,
							MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
					break;
				case 15:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Terézie z Avily, panny a uèite¾ky Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 16:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					else if(poradie_svaty == 2){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Margity Márie Alacoque, panny");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA,
							MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
					pocet = 2;
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty2.meno, "Sv. Hedvigy, panny");
					_global_svaty2.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL,
							MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
					break;
				case 17:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Ignáca Antiochijského, biskupa a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK,
							MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				case 18:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Sv. Lukáša, evanjelistu");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
					break;
				case 19:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					else if(poradie_svaty == 2){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Jána de Brébeuf a sv. Izáka Jogues, kòazov, a ich spoloèníkov, muèeníkov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV,
							MODL_SPOL_CAST_DUCH_PAST_VIACERI);
					pocet = 2;
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty2.meno, "Sv. Pavla z Kríža, kòaza");
					_global_svaty2.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 23:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Jána Kapistránskeho, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
					break;
				case 24:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Antona Márie Clareta, biskupa");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				case 28:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Sv. Šimona a Júdu, apoštolov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
					break;
			}; break; /* case MES_OCT */
		case MES_NOV:
			switch(den){
				case 1:
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
					if((poradie_svaty == 0) || (poradie_svaty == 1)){
						/* preto 0, ze aj ked nie je svaty urceny, ide o sviatok Pana,
						 * ktora ma velku prioritu, a preto ma aj - ak je nedela - prve
						 * vespery 
						 */
						/* definovanie parametrov pre modlitbu */

						spol_cast = _decode_spol_cast(_global_svaty1.spolcast);
						Log("Premenenie Pana: spol_cast: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc[spol_cast.a1], nazov_spolc[spol_cast.a2], nazov_spolc[spol_cast.a3], poradie_svaty);

						if(/*(poradie_svaty == 1) && */ // 23/02/2000A.D. -- prevzate z Petra a Pavla, 29/03/2000A.D.
						  (query_type != PRM_DETAILY))
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_PRVE_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_vsetkych_svatych(modlitba);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_vsetkych_svatych(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_vsetkych_svatych(modlitba);

						if(poradie_svaty != 0) break;
					}
					_global_svaty1.typslav = SLAV_SLAVNOST;
					_global_svaty1.smer = 3; /* slavnosti Pana, preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					_global_svaty1.prik = PRIKAZANY_SVIATOK;
					strcpy(_global_svaty1.meno, "Všetkých svätých");
					break;
				case 2:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 3; /* vsetkych vernych zosnulych */
					strcpy(_global_svaty1.meno, "Všetkých verných zosnulých");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_ZA_ZOSNULYCH);
					break;
				case 3:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Martina de Porres, reho¾níka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 4:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Karola Borromea, biskupa");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				case 5:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Imricha");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
					break;
				case 9:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */
						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);
						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer =  5; /* sviatky Pana uvedene vo vseobecnom kalendari */
						/* povodne: 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
						/* lenze 9. NOV 1997 mal tento sviatok prednost pred 32. nedelou v ocr, takze smer == 5 */
					strcpy(_global_svaty1.meno, "Výroèie posviacky Lateránskej baziliky");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
					break;
				case 10:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Leva Ve¾kého, pápeža a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 11:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full_okrem_prosieb(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full_okrem_prosieb(modlitba);

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Martina z Tours, biskupa");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				case 12:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Jozafáta, biskupa a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK,
							MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				case 15:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Alberta Ve¾kého, biskupa a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 16:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					else if(poradie_svaty == 2){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Margity Škótskej");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL);
					pocet = 2;
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty2.meno, "Sv. Gertrúdy, panny");
					_global_svaty2.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA,
							MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
					break;
				case 17:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Alžbety Uhorskej, reho¾níèky");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL);
					break;
				case 18:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Výroèie posviacky bazilík sv. Petra a sv. Pavla, apoštolov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
					break;
				case 21:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Obetovanie prebl. Panny Márie");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
					break;
				case 22:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Cecílie, panny a muèenice");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENICA,
							MODL_SPOL_CAST_PANNA);
					break;
				case 23:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					else if(poradie_svaty == 2){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Klementa I. pápeža a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK,
							MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
					pocet = 2;
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty2.meno, "Sv. Kolumbána, opáta");
					_global_svaty2.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					break;
				case 24:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Ondreja Dung-Laca a spoloèníkov, muèeníkov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
					break;
				case 25:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Kataríny Alexandrijskej, panny");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK,
							MODL_SPOL_CAST_PANNA);
					break;
				case 30:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_antifony;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_antifony;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Sv. Ondreja, apoštola");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
					break;
			}; break; /* case MES_NOV */
		case MES_DEC:;
			switch(den){
				case 3:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Františka Xaverského, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
					break;
				case 4:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Jána Damascénskeho, kòaza a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 6:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Mikuláša, biskupa");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
					break;
				case 7:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_hymnus;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Ambróza, biskupa a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 8:
label_8_DEC:
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
					if((poradie_svaty == 0) || (poradie_svaty == 1)){
						/* preto 0, ze aj ked nie je svaty urceny, ide o slavnost,
						 * ktora ma takmer najvacsiu prioritu, a preto ma aj prve
						 * vespery - a vtedy by to normalne nefungovalo;
						 * nastavenie veci pre modlitbu by sa muselo diat
						 * v predoslom dni, co je neciste riesenie
						 */
						/* definovanie parametrov pre modlitbu */

						spol_cast = _decode_spol_cast(_global_svaty1.spolcast);
						Log("Neposkvrnene pocatie Panny Marie: spol_cast: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc[spol_cast.a1], nazov_spolc[spol_cast.a2], nazov_spolc[spol_cast.a3], poradie_svaty);

						if(/*(poradie_svaty == 1) && */ // 23/02/2000A.D.
						  (query_type != PRM_DETAILY))
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_PRVE_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_sviatok_panien(modlitba);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);
						_set_zalmy_sviatok_panien(modlitba);

						if(poradie_svaty != 0) break;
					}
					_global_svaty1.typslav = SLAV_SLAVNOST;
					_global_svaty1.smer = 3; /* slavnosti Pana, preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					_global_svaty1.prik = PRIKAZANY_SVIATOK;
					strcpy(_global_svaty1.meno, "Nepoškvrnené poèatie prebl. Panny Márie");
					break;
				case 9:
					if(_global_den.denvt == DEN_PONDELOK){
						/* 05/04/2000A.D. -- bolo to tu zle */
						/* t.j. slavnost neposkvrneneho pocatia P. Marie padla na nedelu */
						sprintf(_anchor_head, "%02d%s_", den - 1, nazov_MES[mesiac - 1]);
						Log("  _anchor_head == %s\n", _anchor_head);
						Log("jumping to label_8_DEC...\n");
						goto label_8_DEC;
					}
					break;
				case 11:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Damaza I., pápeža");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
					break;
				case 12:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Jany Františky de Chantal, reho¾níèky");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
					break;
				case 13:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Lucie, panny a muèenice");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENICA,
							MODL_SPOL_CAST_PANNA);
					break;
				case 14:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; /* povinne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Jána z Kríža, kòaza a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 21:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Petra Kanízia, kòaza a uèite¾a Cirkvi");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ,
							MODL_SPOL_CAST_UCITEL_CIRKVI);
					break;
				case 23:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Jána Kentského, kòaza");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
					break;
				case 26:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_antifony;
						_vlastna_cast_kcitanie;
						_vlastna_cast_kresponz;
						_vlastna_cast_benediktus;
						//_vlastna_cast_prosby;
						_vlastna_cast_modlitba;

						/* vespery -- vsetko je z oktavy narodenia Pana */
						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Sv. Štefana, prvého muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
					break;
				case 27:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_antifony;
						_vlastna_cast_kcitanie;
						_vlastna_cast_benediktus;
						_vlastna_cast_prosby;
						_vlastna_cast_modlitba;

						/* vespery -- vsetko je z oktavy narodenia Pana */
						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Sv. Jána, apoštola a evanjelistu");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
					break;
				case 28:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_hymnus;
						_vlastna_cast_antifony;
						_vlastna_cast_kcitanie;
						_vlastna_cast_kresponz;
						_vlastna_cast_benediktus;
						_vlastna_cast_prosby;
						_vlastna_cast_modlitba;

						/* vespery -- vsetko je z oktavy narodenia Pana */
						break;
					}
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; /* sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari */
					strcpy(_global_svaty1.meno, "Svätých Neviniatok, muèeníkov");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
					break;
				case 29:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Tomáša Becketa, biskupa a muèeníka");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP,
							MODL_SPOL_CAST_MUCENIK);
					break;
				case 31:
					if(poradie_svaty == 1){
						/* definovanie parametrov pre modlitbu */

						if(query_type != PRM_DETAILY)
							set_spolocna_cast(spol_cast, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						/* nema vespery, lebo uz su prve vespery slavnosti bohorodicky panny marie */
						break;
					}
					_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty1.smer = 12; /* lubovolne spomienky podla vseobecneho kalendara */
					strcpy(_global_svaty1.meno, "Sv. Silvestra I., pápeža");
					_global_svaty1.spolcast =
						_encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
					break;
			}; break; /* case MES_DEC */
	}/* switch(mesiac - 1) */

	/* 10/03/2000A.D.: dorobena pasaz pre spomienku neposkvrneneho srdca panny marie */
#define _srdca_pm_benediktus {\
	sprintf(_anchor, "%s_%c%s", ANCHOR_SRDCA_PM, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _srdca_pm_modlitba {\
	sprintf(_anchor, "%s_%s", ANCHOR_SRDCA_PM, ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
	if((_global_den.denvr == (_global_r._ZOSLANIE_DUCHA_SV.denvr + 20)) && 
		(_global_svaty1.smer >= 10)){
		/* neposkvrneneho srdca panny marie; 10/03/2000A.D.;
		 * vtedy som aj napisal tuto vysvetlujucu poznamku:
		       "berie sa len v takom pripade, ked to nekoliduje 
		        s inou povinnou spomienkou alebo slavenim,
		        co ma vyssiu prioritu (smer <= 10)"
		 * kedze vsak som si uvedomil, ze bolo treba nastavit smer=10,
		 * tu treba dat opravenu poznamku:
		       "berie sa v takom pripade, ked nie je slavenie s vyssou prioritou,
			    teda smer < 10"
		 * 2003-06-30a.D.
		 */
		Log(" neposkvrneneho srdca panny marie: \n");
		Log(" ...berie sa len v takom pripade, ked to nekoliduje\n");
		Log(" ...so slavenim, co ma vyssiu prioritu (smer < 10)\n");
		/* 04/07/2000A.D.: vypisanie logu, uprava */
		poradie_svaty = 1;
		if(poradie_svaty == 1){
			/* definovanie parametrov pre modlitbu */

			if(query_type != PRM_DETAILY)
			set_spolocna_cast(spol_cast, poradie_svaty);
			/* ZNOVUNASTAVENIE_POPISU_NA_DUMMY, 2003-06-30 */
			Log("vo funkcii sviatky_svatych() spustam set_popis_dummy(); - kvoli spomienke neposkvrneneho srdca panny marie...\n");
			set_popis_dummy();
			Log("set_popis_dummy() skoncila.\n");

			strcpy(_file, FILE_SRDCA_PM);
			strcpy(_anchor, ANCHOR_SRDCA_PM);
			Log("  ide o spomienku srdca panny marie...\n");
			modlitba = MODL_RANNE_CHVALY;
			_srdca_pm_benediktus;
			_srdca_pm_modlitba;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		/* 2003-06-30: kedysi tu bolo 11: "miestne povinne spomienky podla vseobecneho kalendara"
		 * zmenil som to na 10 */
		_global_svaty1.smer = 10; 
		/* vysvetlujuca poznamka z r. 2000: "zrejme pre Slovensko je tato lubovolna 
		 * spomienka povinna; aby sa nebila s inou spomienkou, dal som tam 
		 * smer == 11; 10/03/2000A.D.;" -- zmenene 2003-06-30
		 * porov. pasaz venovanu srdcu pm vo funkcii breviar.cpp::_rozbor_dna()
		 */
		strcpy(_global_svaty1.meno, "Nepoškvrneného Srdca prebl. Panny Márie");
		_global_svaty1.spolcast =
			_encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
	}/* srdca panny marie */

	if(_global_svaty1.typslav == SLAV_NEURCENE){
		Log("neurcene slavenie, t.j. pocet = 0\n");
		pocet = 0;
	}
	else{
		Log("slavenie je urcene, pocet == %d\n", pocet);

		_global_svaty1.den = den;
		_global_svaty1.mesiac = mesiac;
		Log("  %d. %d: %s (%d) [%d]\n", _global_svaty1.den,	_global_svaty1.mesiac, _global_svaty1.meno,	_global_svaty1.typslav, _global_svaty1.smer);
#ifdef DETAIL_LOG_SVATY
		Log(_global_svaty1);
#endif
		/* mozno je druha lubovolna spomienka */
		if(pocet > 1){
			_global_svaty2.den = den;
			_global_svaty2.mesiac = mesiac;
			Log("  %d. %d: %s (%d) [%d]\n", _global_svaty2.den,	_global_svaty2.mesiac, _global_svaty2.meno, _global_svaty2.typslav, _global_svaty2.smer);
#ifdef DETAIL_LOG_SVATY
			Log(_global_svaty2);
#endif
			/* este dalsi */
			if(pocet > 2){
				_global_svaty3.den = den;
				_global_svaty3.mesiac = mesiac;
				Log("  %d. %d: %s (%d) [%d]\n", _global_svaty3.den,	_global_svaty3.mesiac, _global_svaty3.meno,	_global_svaty3.typslav, _global_svaty3.smer);
#ifdef DETAIL_LOG_SVATY
				Log(_global_svaty3);
#endif
			}
		}
	}
	Log("-- sviatky_svatych(%d, %d) -- koniec (returning %d)\n",
		den, mesiac, pocet);
	return pocet;
}/* sviatky_svatych(); -- 3 vstupy */

int sviatky_svatych(int den, int mesiac){
	int ret;
	Log("-- sviatky_svatych(%d, %d) -- spustam bez tretieho parametra\n", den, mesiac);
	Log("   (poradie_svaty == 0)\n");
	ret = sviatky_svatych(den, mesiac, 0);
	Log("-- sviatky_svatych(%d, %d) -- spustene bez tretieho parametra, vysledok (pocet svatych) == %d\n", den, mesiac, ret);
	return ret;
}/* sviatky_svatych(); -- 2 vstupy */

int sviatky_svatych(int den, int mesiac, int poradie_svaty, int druhykrat){
	int ret;
	Log("-- sviatky_svatych(%d, %d, %d) -- spustam druhykrat\n", den, mesiac, poradie_svaty);
	if(druhykrat != 2){
		Log("   zle spustena, nie s 4. parametrom == 2\n");
		Log("-- sviatky_svatych(%d, %d) -- failure. Nespustila sa.\n");
		return 5;
	}

	Log("_global_svaty[1,2,3] som nemenil, lebo poradie_svaty == %d\n", poradie_svaty);
	Log("teraz priradim do _global_den vsetko z _global_svaty%d...\n", poradie_svaty);
	Log("    (tato cast bola povodne v sviatky_svatych s 3 vstupmi, ale teraz je tu)\n");
	switch(poradie_svaty){
		case 1: _global_den = _global_svaty1; break;
		case 2: _global_den = _global_svaty2; break;
		case 3: _global_den = _global_svaty3; break;
		default: /* sem by sa to nemalo dostat */
			Log("--Error: switch(poradie_svaty) nezabralo pre 1, 2, 3...\n"); break;
	}/* switch(); */
	Log("takze _global_den teraz:\n");
	Log(_global_den);
	/*
	LOG_ciara_sv; Log("_global_svaty1: \n"); Log(_global_svaty1);
	LOG_ciara_sv; Log("_global_svaty2: \n"); Log(_global_svaty2);
	LOG_ciara_sv; Log("_global_svaty3: \n"); Log(_global_svaty3);
	*/

	/* az teraz, ked je v _global_den (pri druhom volani fcie)
	 * spravna hodnota z _global_svaty[1,2,3], mozem urobit toto
	 * priradenie do spol_cast
	 */
	_struct_sc spol_cast = _decode_spol_cast(_global_den.spolcast);

	Log("a hned nastavujem _global_opt3 (ak je neurcene) na spol_cast.a1):\n");
	/* ak opt3 je MODL_SPOL_CAST_NEURCENA, tak ju urcime podla
	 * 1. spolocnej casti */
	if(_global_opt3 == MODL_SPOL_CAST_NEURCENA){
		_global_opt3 = spol_cast.a1;
		Log("          setting _global_opt3 to spol_cast.a1\n");
	}
	ret = sviatky_svatych(den, mesiac, poradie_svaty);
	Log("-- sviatky_svatych(%d, %d) -- spustene druhykrat, vysledok (pocet svatych) == %d\n", den, mesiac, ret);
	return ret;
}/* sviatky_svatych(); -- 4 vstupy; posledny == 2 */


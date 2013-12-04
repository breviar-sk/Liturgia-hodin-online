/***************************************************************/
/*                                                             */
/* hodin.h                                                     */
/* (c)1999-2013 | Juraj Vidéky | videky@breviar.sk             */
/*                                                             */
/* description | definovane stringove kontanty                 */
/* document history                                            */
/*   18/02/2000A.D. | created                                  */
/*   06/09/2001A.D. | tento popis                              */
/*   2003-08-07a.D. | pridane nazov_doplnkpsalm[]              */
/*   2003-08-13a.D. | zrusene nazov_doplnkpsalm[]              */
/*   2003-11-20a.D. | pridane nazov_obd_htm_pc[]               */
/*   2005-07-27a.D. | pridané nazov_slavenia_lokal[]           */
/*   2005-08-05a.D. | pridané zvazok_OBD[]                     */
/*   2006-07-11a.D. | prvé kroky k jazykovım mutáciám          */
/*   2006-08-01a.D. | zmenené definície konštánt (jaz.mutácie) */
/*   2006-08-07a.D. | pridané sv. muov/ien, èo ili v man.  */
/*   2006-08-18a.D. | zmena int na short int (staèí 32tis.)    */
/*   2006-08-19a.D. | pridanie liturgickej farby               */
/*   2006-09-07a.D. | dokonèená lokalizácia mesiacov JAN-AUG   */
/*   2006-09-12a.D. | dokonèená lokalizácia mesiaca SEP+opravy */
/*   2006-09-13a.D. | dokonèená lokalizácia mesiacov OKT+NOV   */
/*   2006-12-04a.D. | oprava: kompletáØ                        */
/*   2006-12-12a.D. | doplnenie latinèiny (la)                 */
/*   2008-01-03a.D. | doplnené text_DRUHA_NEDELA_PO_NAR_PANA[] */
/*   2008-01-05a.D. | doplnené text_PO_POPOLCOVEJ_STREDE[]     */
/*                  - a tie text_V_OKTAVE_NARODENIA[]         */
/*   2008-07-18a.D. | pridanı sviatok (text_JUL_24)            */
/*   2008-08-15a.D. | pridanı ïalší "jazyk" (cz-op)            */
/*   2009-01-29a.D. | pridanı ïalší jazyk - maïarèina (hu)     */
/*   2009-02-01a.D. | hungarian translation added by László    */
/*   2009-03-24a.D. | úpravy liturgického kalendára pre czop   */
/*   2009-04-08a.D. | zakonèenie modlitby (pre modlitbu cezdeò */
/*                    a komplet. sa pouíva kratšie zakonèenie)*/
/*   2009-05-15a.D. | pridané text_PRO_OP[]                    */
/*   2009-08-26a.D. | pridané html_button_nazov_modlitby()     */
/*   2010-05-17a.D. | pridané niektoré maïarské slávenia       */
/*   2010-10-11a.D. | pridané nazov_kalendara_long[]           */
/*   2011-01-14a.D. | pridané ZAKONCENIE_KTORY_JE              */
/*   2011-01-26a.D. | upravené poradie konštánt pre lit. obd.  */
/*   2011-05-18a.D. | doplnené charset_jazyka[]                */
/*                                                             */
/*                                                             */
/***************************************************************/

#include "vstudio.h"

#ifndef __HODIN_H_
#define __HODIN_H_

#include "liturgia.h"

const char *TEMPLAT[POCET_MODLITIEB + 1] =
{TEMPLAT_INVITATORIUM, TEMPLAT_POSV_CITANIE, TEMPLAT_RANNE_CHVALY,
 TEMPLAT_CEZ_DEN_9, TEMPLAT_CEZ_DEN_12, TEMPLAT_CEZ_DEN_3,
 TEMPLAT_VESPERY, TEMPLAT_KOMPLETORIUM, STR_EMPTY,
 TEMPLAT_VESPERY, TEMPLAT_KOMPLETORIUM, 
 TEMPLAT_VESPERY, TEMPLAT_KOMPLETORIUM, TEMPLAT_NEURCENY, TEMPLAT_NEURCENY};

// 2008-04-09: doplnené pre batch generovanie modlitieb
const char char_modlitby[POCET_MODLITIEB + 1] =
{CHAR_MODL_INVITATORIUM, CHAR_MODL_POSV_CITANIE, CHAR_MODL_RANNE_CHVALY, 
 CHAR_MODL_CEZ_DEN_9, CHAR_MODL_CEZ_DEN_12, CHAR_MODL_CEZ_DEN_3,
 CHAR_MODL_VESPERY, CHAR_MODL_KOMPLETORIUM, 32 /* ' ' */,
 CHAR_MODL_PRVE_VESPERY, CHAR_MODL_PRVE_KOMPLETORIUM, 
 CHAR_MODL_VESPERY, CHAR_MODL_KOMPLETORIUM, CHAR_MODL_NEURCENA, CHAR_MODL_VSETKY};

const char *str_modlitby[POCET_MODLITIEB + 1] =
{STR_MODL_INVITATORIUM, STR_MODL_POSV_CITANIE, STR_MODL_RANNE_CHVALY,
 STR_MODL_PREDPOLUDNIM, STR_MODL_NAPOLUDNIE, STR_MODL_POPOLUDNI,
 STR_MODL_VESPERY, STR_MODL_KOMPLETORIUM, STR_EMPTY,
 STR_MODL_PRVE_VESPERY, STR_MODL_PRVE_KOMPLETORIUM, 
 STR_MODL_VESPERY, STR_MODL_KOMPLETORIUM, STR_MODL_DETAILY, STR_MODL_VSETKY};

// the names of the prayers, lowercase (sample text)
const char *nazov_modlitby_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1] = 
{{"invitatórium", "uvedení do první modlitby dne", "Invitatory", "invitatorium", "", "Pozvání k modlitbì", "imádságra hívás" }
, {"posvätné èítanie", "modlitba se ètením", "Office of Readings", "officium lectionis", "", "Modlitba se ètením", "olvasmányos imaóra" }
, {"ranné chvály", "ranní chvály", "Laudes", "laudes matutinae", "", "Ranní chvály", "reggeli dicséret" }
, {"modlitba predpoludním", "modlitba dopoledne", "Terce", "tertia", "", "Tercie", "délelõtt" }
, {"modlitba napoludnie", "modlitba v poledne", "Sext", "sexta", "", "Sexta", "délben" }
, {"modlitba popoludní", "modlitba odpoledne", "None", "nona", "", "Nona", "délután" }
, {"vešpery", "nešpory", "Vesperae", "vesperae", "", "Veèerní chvály", "esti dicséret" }
, {"kompletórium", "kompletáø", "Completary", "completorio", "", "Kompletáø", "befejezõ imaóra" }
, {"neurèená", "neurèena", "not-defined", "no data", "", "neurèena", "nem azonosított"}
, {"prvé vešpery", "první nešpory", "1st Vesperae", "I vesperae", "", "První veèerní chvály", "I. esti dicséret" }
	// 2007-12-05: zmenené, kedysi bolo: "prvé kompletórium"
, {"kompletórium po prvıch vešperách", "kompletáø po prvních nešporách", "1st Completary", "I completorio", "", "Kompletáø po prvních veèerních chválách", "befejezõ imaóra I.e.d.után" }
, {"druhé vešpery", "druhé nešpory", "2nd Vesperae", "II vesperae", "", "Druhé veèerní chvály", "II. esti dicséret" }
	// 2007-12-05: zmenené, kedysi bolo: "druhé kompletórium"
, {"kompletórium po druhıch vešperách", "kompletáø po druhıch nešporách", "2nd Completary", "II completorio", "", "Kompletáø po druhıch veèerních chválách", "befejezõ imaóra II.e.d.után" }
, {"detaily", "detaily", "Details", "details", "", "detaily", "részletek" }
, {"všetky", "všechny", "all", "all", "", "všechny", "összes" }
};

#define		nazov_modlitby(a)	nazov_modlitby_jazyk[a][_global_jazyk]

// the names of the prayers, lowercase (sample text)
const char *nazov_modlitby_short_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1] = 
{{"invitatórium", "uvedení do 1. modl. dne", "Invitatory", "invitatorium", "", "Pozvání k modl.", "imádságra hívás" }
, {"posvätné èítanie", "modl. se ètením", "Office of Readings", "officium lectionis", "", "modl. se ètením", "olvasmányos imaóra" }
, {"ranné chvály", "ranní chvály", "Laudes", "laudes matutinae", "", "Ranní chvály", "reggeli dicséret" }
, {"modl. predpoludním", "modl. dopoledne", "Terce", "tertia", "", "Tercie", "délelõtt" }
, {"modl. napoludnie", "modl. v poledne", "Sext", "sexta", "", "Sexta", "délben" }
, {"modl. popoludní", "modl. odpoledne", "None", "nona", "", "Nona", "délután" }
, {"vešpery", "nešpory", "Vesperae", "vesperae", "", "Veèerní chvály", "esti dicséret" }
, {"kompletórium", "kompletáø", "Completary", "completorio", "", "Kompletáø", "befejezõ imaóra" }
, {"neurèená", "neurèena", "not-defined", "no data", "", "neurèena", "nem azonosított"}
, {"prvé vešpery", "první nešpory", "1st Vesperae", "I vesperae", "", "První veèerní chvály", "I. esti dicséret" }
	// 2007-12-05: zmenené, kedysi bolo: "prvé kompletórium"
, {"kompletórium po 1. vešp.", "kompletáø po 1. nešp.", "1st Completary", "I completorio", "", "Kompletáø po 1. v. chv.", "befejezõ imaóra I.e.d.ut." }
, {"(druhé) vešpery", "druhé nešpory", "2nd Vesperae", "II vesperae", "", "Druhé veèerní chvály", "II. esti dicséret" }
	// 2007-12-05: zmenené, kedysi bolo: "druhé kompletórium"
, {"kompletórium (po 2. vešp.)", "kompletáø po 2. nešp.", "2nd Completary", "II completorio", "", "Kompletáø po 2. v. chv.", "befejezõ imaóra II.e.d.ut." }
, {"detaily", "detaily", "Details", "details", "", "detaily", "részletek" }
, {"všetky", "všechny", "all", "all", "", "všechny", "összes" }
};

#define		nazov_modlitby_short(a)	nazov_modlitby_short_jazyk[a][_global_jazyk]

// the names of the prayers, sentence case (Sample text)
const char *nazov_Modlitby_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1] = 
{{"Invitatórium", "Uvedení do první modlitby dne", "Invitatory", "Invitatorium", "", "Pozvání k modlitbì" , "Imádságra hívás" }
, {"Posvätné èítanie", "Modlitba se ètením", "Office of Readings", "Officium lectionis", "", "Modlitba se ètením" , "Olvasmányos imaóra" }
, {"Ranné chvály", "Ranní chvály", "Laudes", "Laudes matutinae", "", "Ranní chvály" , "Reggeli dicséret" }
, {"Modlitba predpoludním", "Modlitba dopoledne", "Terce", "Tertia", "", "Tercie" , "Délelõtt" }
, {"Modlitba napoludnie", "Modlitba v poledne", "Sext", "Sexta", "", "Sexta" , "Délben" }
, {"Modlitba popoludní", "Modlitba odpoledne", "None", "Nona", "", "Nona" , "Délután" }
, {"Vešpery", "Nešpory", "Vesperae", "Vesperae", "", "Veèerní chvály" , "Esti dicséret" }
, {"Kompletórium", "Kompletáø", "Completary", "Completorio", "", "Kompletáø" , "Befejezõ imaóra" }
, {"Neurèená", "Neurèena", "not-defined", "No data", "", "Neurèená" , "Nem azonosított"}
, {"Prvé vešpery", "První nešpory", "1st Vesperae", "I Vesperae", "", "První veèerní chvály" , "I. Esti dicséret" }
, {"Kompletórium po prvıch vešperách", "Kompletáø po prvních nešporách", "1st Completary", "I Completorio", "", "Kompletáø po prvních veèerních chválách" , "Befejezõ imaóra I.e.d.után" }
, {"Druhé vešpery", "Druhé nešpory", "2nd Vesperae", "II Vesperae", "", "Druhé veèerní chvály" , "II. Esti dicséret" }
, {"Kompletórium po druhıch vešperách", "Kompletáø po druhıch nešporách", "2nd Completary", "II Completorio", "", "Kompletáø po druhıch veèerních chválách" , "Befejezõ imaóra II.e.d.után" }
, {"Detaily", "Detaily", "Details", "Details", "", "Detaily", "Részletek" }
, {"všetky", "všechny", "all", "all", "", "všechny", "összes" }
};

#define		nazov_Modlitby(a)	nazov_Modlitby_jazyk[a][_global_jazyk]

// the names of the prayers, all caps case (SAMPLE TEXT)
const char *nazov_MODLITBY_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1] = 
{{"INVITATÓRIUM", "UVEDENÍ DO PRVNÍ MODLITBY DNE", "INVITATORY", "INVITATORIUM", "", "POZVÁNÍ K MODLITBÌ" , "IMÁDSÁGRA HÍVÁS" }
, {"POSVÄTNÉ ÈÍTANIE", "MODLITBA SE ÈTENÍM", "OFFICE OF READINGS", "OFFICIUM LECTIONIS", "", "MODLITBA SE ÈTENÍM" , "OLVASMÁNYOS IMAÓRA" }
, {"RANNÉ CHVÁLY", "RANNÍ CHVÁLY", "LAUDES", "LAUDES MATUTINAE", "", "RANNÍ CHVÁLY" , "REGGELI DICSÉRET" }
, {"MODLITBA PREDPOLUDNÍM", "MODLITBA DOPOLEDNE", "TERCE", "TERTIA", "", "TERCIE" , "DÉLELÕTT" }
, {"MODLITBA NAPOLUDNIE", "MODLITBA V POLEDNE", "SEXT", "SEXTA", "", "SEXTA" , "DÉLBEN" }
, {"MODLITBA POPOLUDNÍ", "MODLITBA ODPOLEDNE", "NONE", "NONA", "", "NONA" , "DÉLUTÁN" }
, {"VEŠPERY", "NEŠPORY", "VESPERAE", "VESPERAE", "", "VEÈERNÍ CHVÁLY" , "ESTI DICSÉRET" }
, {"KOMPLETÓRIUM", "KOMPLETÁØ", "COMPLETARY", "COMPLETORIO", "", "KOMPLETÁØ" , "BEFEJEZÕ IMAÓRA" }
, {"NEURÈENÁ", "NEURÈENA", "NOT-DEFINED", "NO DATA", "", "NEURÈENÁ" , "NEM AZONOSÍTOTT"}
, {"PRVÉ VEŠPERY", "PRVNÍ NEŠPORY", "1ST VESPERAE", "I VESPERAE", "", "PRVNÍ VEÈERNÍ CHVÁLY" , "I. ESTI DICSÉRET" }
, {"KOMPLETÓRIUM PO PRVİCH VEŠPERÁCH", "KOMPLETÁØ PO PRVNÍCH NEŠPORÁCH", "1ST COMPLETARY", "I COMPLETORIO", "", "KOMPLETÁØ PO PRVNÍCH VEÈERNÍCH CHVÁLÁCH" , "BEFEJEZÕ IMAÓRA I.E.D.UTÁN" }
, {"DRUHÉ VEŠPERY", "DRUHÉ NEŠPORY", "2ND VESPERAE", "II VESPERAE", "", "DRUHÉ VEÈERNÍ CHVÁLY" , "II. ESTI DICSÉRET" }
, {"KOMPLETÓRIUM PO DRUHİCH VEŠPERÁCH", "KOMPLETÁØ PO DRUHİCH NEŠPORÁCH", "2ND COMPLETARY", "II COMPLETORIO", "", "KOMPLETÁØ PO DRUHİCH VEÈERNÍCH CHVÁLÁCH" , "BEFEJEZÕ IMAÓRA II.E.D.UTÁN" }
, {"DETAILY", "DETAILY", "DETAILS", "DETAILS", "", "DETAILY", "RÉSZLETEK" }
, {"VŠETKY", "VŠECHNY", "ALL", "ALL", "", "VŠECHNY", "ÖSSZES" }
};

#define		nazov_MODLITBY(a)	nazov_MODLITBY_jazyk[a][_global_jazyk]

// the prefix for common parts of celebration
const char *nazov_spolc_zospolc_jazyk[POCET_JAZYKOV + 1] =
{"Zo spoloènej èasti", "Spoleèné texty", "", "", "", "Spoleèné texty", "közös zsolozsmája"};

const char *nazov_spolc_oficiumza_jazyk[POCET_JAZYKOV + 1] =
{"Ofícium za", "Spoleèné texty", "", "", "", "Spoleèné texty", "közös zsolozsmája"};

// the --CELEBRATION-- for common parts of celebration
const char *nazov_spolc_sviatky_jazyk[POCET_JAZYKOV + 1] =
{"na sviatky", "na svátky", "", "", "", "na svátky", ""};

// the --ANNIVERSARY-- for common parts of celebration
const char *nazov_spolc_vyrocie_jazyk[POCET_JAZYKOV + 1] =
{"na vıroèie", "na vıroèí", "", "", "", "na vıroèí", ""};

// the --OR-- (alternative) for common parts of celebration
const char *nazov_spolc_alebo_jazyk[POCET_JAZYKOV + 1] =
{HTML_LINE_BREAK"alebo", HTML_LINE_BREAK"nebo", HTML_LINE_BREAK"or", "", "", HTML_LINE_BREAK"nebo", HTML_LINE_BREAK"vagy"};

// the names of the common texts (e.g.: for bishops, for saint men, for apostles...)
const char *nazov_spolc_jazyk[POCET_SPOL_CASTI + 1][POCET_JAZYKOV + 1] =
{{"neurèená", "neurèena", "not decided", "", "", "", ""}, 
 {"duchovnıch pastierov: pre kòazov", "o duchovních pastıøích (o knìích)", "", "", "", "O duchovních pastıøích – o knìích", "lelkipásztorok – papok"}, 
 {"duchovnıch pastierov: pre biskupov", "o duchovních pastıøích (o biskupech)", "", "", "", "O duchovních pastıøích – o biskupech", "lelkipásztorok – püspökök"}, 
 {"duchovnıch pastierov: pre pápeov", "o duchovních pastıøích (o papei)", "", "", "", "O duchovních pastıøích – o papei", "pásztorok – pápa"}, 
 {"uèite¾ov Cirkvi", "o uèitelích církve", "", "", "", "O uèitelích Církve", "egyháztanítók"}, 
 {"apoštolov", "o apoštolech", "", "", "", "O apoštolech", "apostolok"}, 
 {"jedného muèeníka", "o jednom muèedníkovi", "", "", "", "O muèedníkovi", "vértanú"}, 
 {"viacerıch muèeníkov", "o více muèednících", "", "", "", "O více muèednících", "vértanúk"}, 
 {"Panny Márie", "o Pannì Marii", "", "", "", "O Pannì Marii", "Szûz Mária"}, 
 {"svätıch muov: pre reho¾níkov", "o svatıch muech (o øeholnících)", "", "", "", "O øeholnících", "szerzetes"}, 
 {"svätıch muov", "o svatıch muích", "", "", "","O svatıch muích", "szent férfiak"}, 
 {"panien", "o pannách", "", "", "","O pannách", "szûz"}, 
 {"svätıch ien: pre reho¾nice", "o svatıch enách (o øeholnicích)", "", "", "", "O svatıch enách - o øeholnicích", "apáca"}, 
 {"svätıch ien", "o svatıch enách", "", "", "", "O svatıch enách", "szent asszonyok"}, 
 {"duchovnıch pastierov: pre viacerıch", "o duchovních pastıøích", "", "", "", "O duchovních pastıøích", "több lelkipásztor"}, 
 {"jednej muèenice", "o jedné muèednici", "", "", "", "O muèednici", "vértanú"}, 
 {"svätıch ien: pre vychovávate¾ky", "o svatıch enách (o vychovatelkách)", "", "", "", "O svatıch enách - o vychovatelkách", "egyháztanító férfiak"}, 
 {"svätıch muov: pre vychovávate¾ov", "o svatıch muích (o vychovatelích)", "", "", "", "O svatıch muích – o vychovatelích", "egyháztanító asszonyok"}, 
 {"svätıch ien: pre tie, èo konali skutky milosrdenstva", "o svatıch enách (které vynikaly milosrdnımi skutky)", "", "", "", "O svatıch enách – o enì, která vynikala milosrdnımi skutky", "jótékonykodó asszonyok"}, 
 {"svätıch muov: pre tıch, èo konali skutky milosrdenstva", "o svatıch muích (kterí vynikali milosrdnımi skutky)", "", "", "", "O svatıch muích – o mui, kterı vynikal milosrdnımi skutky", "jótékonykodó férfiak"}, 
 {"svätıch ien: pre viaceré", "o svatıch enách (o více enách)", "", "", "", "O svatıch enách", "több szent asszony"}, 
 {"svätıch muov: pre viacerıch", "o svatıch muích – o více muích", "", "", "", "O svatıch muích", "több szent férfi"}, 
 {"viacerıch panien", "o pannách", "", "", "","O pannách", "szüzek"}, 
 {"posviacky chrámu", "o posvìcení kostela", "", "", "", "Posvìcení kostela", "templomszentelés"}, 
 {"zosnulıch", "za zemøelé", "", "", "","Za zemøelé", "halottakért"}, 
 {"svätıch ien: pre tie, èo ili v manelstve", "o svatıch enách (které ily v manelství)", "", "", "", "O svatıch enách – o enì, která ila v manelství", "házas szent asszonyok"}, 
 {"svätıch muov: pre tıch, èo ili v manelstve", "o svatıch muích (kterí ili v manelství)", "", "", "", "O svatıch muích – o mui, kterı il v manelství", "házas szent férfiak"}, 
 {"nebra", "nepouít", "do not use", "", "", "nepouít", "mindent sajátból"}
};

#define		nazov_spolc(a)	nazov_spolc_jazyk[a][_global_jazyk]

const char *nazov_bit_opt_1_spomienka_spol_cast_jazyk[POCET_JAZYKOV + 1] =
{"bola zvolená monos niektoré èasti pri slávení spomienky vzia zo dòa pod¾a Všeobecnıch smerníc, è. 235 písm. b", 
 "byla zvolena monost vzít pøi slavení památky nìkteré èásti ze dne podle Všeobecnıch pokynù k denní modlitbì církve, è. 235 písm. b", 
 "", 
 "", 
 "", 
 "byla zvolena monost vzít pøi slavení památky nìkteré èásti ze dne podle Všeobecnıch pokynù k denní modlitbì Církve, è. 235 písm. b", 
 "az a lehetõség volt választva, hogy az emléknapoknál bizonyos részek vehetõk a soros köznapról; Általános Rendelkezések az Imaórák Liturgiájáról, 235 b"
};

// filenames - same for all languages (based on Slovak)
const char *nazov_spolc_htm[POCET_SPOL_CASTI + 1] =
{"000",
 "sc_dp.htm",
 "sc_dp.htm",
 "sc_dp.htm",
 "sc_uc.htm",
 "sc_ap.htm",
 "sc_jm.htm",
 "sc_vm.htm",
 "sc_pm.htm",
 "sc_rh.htm",
 "sc_sm.htm",
 "sc_pn.htm",
 "sc_rh.htm",
 "sc_sz.htm",
 "sc_dp.htm",
 "sc_jm.htm",
 "sc_vv.htm",
 "sc_vv.htm",
 "sc_skm.htm",
 "sc_skm.htm",
 "sc_sz.htm",
 "sc_sm.htm",
 "sc_pn.htm",
 "vpchr.htm",
 "ozz.htm",
 "sc_sz.htm",
 "sc_sm.htm",
 "000"
};

// anchor names in files - same for all languages (based on Slovak)
const char *nazov_spolc_ANCHOR[POCET_SPOL_CASTI + 1] =
{"000",
 "SCDPKN",
 "SCDPBS",
 "SCDPPP",
 "SCUC",
 "SCAP",
 "SCMM",
 "SCVM",
 "SCPM",
 "SCSMRH",
 "SCSM",
 "SCPN",
 "SCSZRH",
 "SCSZ",
 "SCDPVI",
 "SCZM",
 "SCVV",
 "SCVV",
 "SCSKM",
 "SCSKM",
 "SCSZV",
 "SCSMV",
 "SCPNV",
 "VPCHR",
 "OZZ",
 "SCSZM",
 "SCSMM",
 "000"
};

// the names of liturgical periods (usually lowecase) / nazov_obdobia: string pre nazov liturgickeho obdobia
const char *nazov_obdobia_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1] =
{
 {"adventné obdobie", "doba adventní", "", "tempus adventus", "", "doba adventní", "adventi idõ"},
 {"adventné obdobie", "doba adventní", "", "tempus adventus", "", "doba adventní", "adventi idõ"},
 {"oktáva Narodenia Pána", "oktáv Narození Pánì", "", "octava nativitatis", "", "oktáv Narození Pánì", "karácsony nyolcada"},
 {"vianoèné obdobie", "doba vánoèní", "", "tempus nativitatis", "", "doba vánoèní", "karácsonyi idõ"},
 {"vianoèné obdobie", "doba vánoèní", "", "tempus nativitatis", "", "doba vánoèní", "karácsonyi idõ"},
 {"cezroèné obdobie", "mezidobí", "", "tempus per annum", "", "mezidobí", "évközi idõ"},
 {"pôstne obdobie", "doba postní", "", "tempus quadragesimae", "", "doba postní", "nagyböjti idõ"},
 {"Ve¾kı tıdeò", "Svatı tıden", "", "hebdomada sancta", "", "Svatı tıden", "nagyhét"},
 {"ve¾konoèné trojdnie", "Velikonoèní triduum", "", "sacrum triduum paschale", "", "Velikonoèní triduum", "szent három nap"},
 {"ve¾konoèná oktáva", "velikonoèní oktáv", "", "octava paschae", "", "velikonoèní oktáv", "húsvét nyolcada"},
 {"ve¾konoèné obdobie", "doba velikonoèní", "", "tempus paschale", "", "doba velikonoèní", "húsvéti idõ"},
 {"ve¾konoèné obdobie", "doba velikonoèní", "", "tempus paschale", "", "doba velikonoèní", "húsvéti idõ"},
};

#define		nazov_obdobia(a)	nazov_obdobia_jazyk[a][_global_jazyk]

// the names of liturgical periods (usually lowecase) / nazov_obdobia: string pre názov liturgického obdobia, rozšírenı
const char *nazov_obdobia_ext_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1] =
{
 {"Adventné obdobie I (do 16. decembra)", "doba adventní I", "", "tempus adventus I", "", "doba adventní I", "adventi idõ I (dec.16-ig)"},
 {"Adventné obdobie II (po 16. decembri)", "doba adventní II", "", "tempus adventus II", "", "doba adventní II", "adventi idõ II (dec.16 után)"},
 {"Oktáva Narodenia Pána", "oktáv Narození Pánì", "", "octava nativitatis", "", "oktáv Narození Pánì", "karácsony nyolcada"},
 {"Vianoèné obdobie I (do Zjavenia Pána)", "doba vánoèní I", "", "tempus nativitatis I", "", "doba vánoèní II", "karácsonyi idõ I (Urunk megjelenéséig)"},
 {"Vianoèné obdobie II (po Zjavení Pána)", "doba vánoèní II", "", "tempus nativitatis II", "", "doba vánoèní II", "karácsonyi idõ II (Urunk megjelenése után)"},
 {"Cezroèné obdobie", "mezidobí", "", "tempus per annum", "", "mezidobí", "évközi idõ"},
 {"Pôstne obdobie I (do Kvetnej nedele)", "doba postní I", "", "tempus quadragesimae I", "", "doba postní I", "nagyböjti idõ I (Virágvasárnapig)"},
 {"Pôstne obdobie II (ve¾kı tıdeò)", "Svatı tıden", "", "hebdomada sancta", "", "Svatı tıden", "nagyböjti idõ II (Nagyhét)"},
 {"Ve¾konoèné trojdnie", "Velikonoèní triduum", "", "sacrum triduum paschale", "", "Velikonoèní triduum", "szent három nap"},
 {"Ve¾konoèná oktáva", "velikonoèní oktáv", "", "octava paschae", "", "velikonoèní oktáv", "húsvét nyolcada"},
 {"Ve¾konoèné obdobie I (do Nanebovstúpenia Pána)", "doba velikonoèní I", "", "tempus paschale I", "", "doba velikonoèní I", "húsvéti idõ I (Urunk mennybemeneteléig)"},
 {"Ve¾konoèné obdobie II (po Nanebovstúpení Pána)", "doba velikonoèní II", "", "tempus paschale II", "", "doba velikonoèní II", "húsvéti idõ II (Urunk mennybemenetele után)"},
};

#define		nazov_obdobia_ext(a)	nazov_obdobia_ext_jazyk[a][_global_jazyk]

// the names of liturgical periods (usually lowecase) full-shortened / nazov_obdobia: string pre názov liturgického obdobia, struènı ale plnı
const char *nazov_obdobia_short_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1] =
{
 {"Adventné obd. I", "doba adventní I", "", "tempus adventus I", "", "doba adventní I", "adventi idõ I"},
 {"Adventné obd. II", "doba adventní II", "", "tempus adventus II", "", "doba adventní II", "adventi idõ II"},
 {"Oktáva Narodenia Pána", "oktáv Narození Pánì", "", "octava nativitatis", "", "oktáv Narození Pánì", "karácsony nyolcada"},
 {"Vianoèné obd. I", "doba vánoèní I", "", "tempus nativitatis I", "", "doba vánoèní II", "karácsonyi idõ I"},
 {"Vianoèné obd. II", "doba vánoèní II", "", "tempus nativitatis II", "", "doba vánoèní II", "karácsonyi idõ II"},
 {"Cezroèné obd.", "mezidobí", "", "tempus per annum", "", "mezidobí", "évközi idõ"},
 {"Pôstne obd. I", "doba postní I", "", "tempus quadragesimae I", "", "doba postní I", "nagyböjti idõ I"},
 {"Ve¾kı tıdeò", "Svatı tıden", "", "hebdomada sancta", "", "Svatı tıden", "Nagyhét"},
 {"Ve¾konoèné trojdnie", "Velikonoèní triduum", "", "sacrum triduum paschale", "", "Velikonoèní triduum", "szent három nap"},
 {"Ve¾konoèná oktáva", "velikonoèní oktáv", "", "octava paschae", "", "velikonoèní oktáv", "húsvét nyolcada"},
 {"Ve¾konoèné obd. I", "doba velikonoèní I", "", "tempus paschale I", "", "doba velikonoèní I", "húsvéti idõ I"},
 {"Ve¾konoèné obd. II", "doba velikonoèní II", "", "tempus paschale II", "", "doba velikonoèní II", "húsvéti idõ II"},
};

#define		nazov_obdobia_short(a)	nazov_obdobia_short_jazyk[a][_global_jazyk]

// the names of liturgical periods for debugging, only in Slovak; no need to translate
const char *nazov_obdobia_[POCET_OBDOBI + 1] = // debuggovacie - preto netreba preklada; 2006-08-03
{
 "adventné obdobie I", "adventné obdobie II", "oktáva Narodenia Pána",
 "vianoèné obdobie I", "vianoèné obdobie II", "cezroèné obdobie", 
 "pôstne obdobie I", "pôstne obdobie II (Ve¾kı tıdeò)",
 "ve¾konoèné trojdnie", "ve¾konoèná oktáva", "ve¾konoèné obdobie I", "ve¾konoèné obdobie II",
};

// the names of liturgical periods in local grammatically 6.th declination? (usually lowecase); in English: "IN liturgical period" or "OF liturgical period" / lokal == 6. pad, v kom/com
const char *nazov_obdobia_v_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1] =
{
 {"v adventnom období", "v dobì adventní", "", "", "", "v dobì adventní", "adventben"},
 {"v adventnom období", "v dobì adventní", "", "", "", "v dobì adventní", "adventben"},
 {"v oktáve Narodenia Pána", "v oktávu Narození Pánì", "", "", "", "v oktávu Narození Pánì", "Karácsony nyolcadában"},
 {"vo vianoènom období", "v dobì vánoèní", "", "", "", "v dobì vánoèní", "a karácsonyi idõben"},
 {"vo vianoènom období", "v dobì vánoèní", "", "", "", "v dobì vánoèní", "a karácsonyi idõben"},
 {"v cezroènom období", "v mezidobí", "", "per annum", "", "v mezidobí", "az évközi idõben"},
 {"v pôstnom období", "v dobì postní", "", "", "", "v dobì postní", "a nagyböjti idõben"},
 {"vo Ve¾kom tıdni", "ve Svatém tıdnu", "", "", "", "ve Svatém tıdnu", "a nagyhéten"},
 {"vo ve¾konoènom trojdní", "ve velikonoèním triduu", "", "", "", "ve velikonoèním triduu", "a szent három napban"},
 {"vo ve¾konoènej oktáve", "ve velikonoèním oktávu", "", "", "", "ve velikonoèním oktávu", "húsvét nyolcadában"},
 {"vo ve¾konoènom období", "v dobì velikonoèní", "", "", "", "v dobì velikonoèní", "a húsvéti idõben"},
 {"vo ve¾konoènom období", "v dobì velikonoèní", "", "", "", "v dobì velikonoèní", "a húsvéti idõben"},
};

#define		nazov_obdobia_v(a)	nazov_obdobia_v_jazyk[a][_global_jazyk]

// the names of liturgical periods in local grammatically 6.th declination? (uppercase) / nazov_obdobia: string pre nazov liturgickeho obdobia
const char *nazov_OBDOBIA_V_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1] =
{
 {"V ADVENTNOM OBDOBÍ", "V DOBÌ ADVENTNÍ", "", "", "", "V DOBÌ ADVENTNÍ", "ADVENTBEN"},
 {"V ADVENTNOM OBDOBÍ", "V DOBÌ ADVENTNÍ", "", "", "", "V DOBÌ ADVENTNÍ", "ADVENTBEN"},
 {"V OKTÁVE NARODENIA PÁNA", "V OKTÁVU NAROZENÍ PÁNÌ", "", "", "", "V OKTÁVU NAROZENÍ PÁNÌ", "A KARÁCSONY NYOLCADÁBAN"},
 {"VO VIANOÈNOM OBDOBÍ", "V DOBÌ VÁNOÈNÍ", "", "", "", "V DOBÌ VÁNOÈNÍ", "A KARÁCSONYI IDÕBEN"},
 {"VO VIANOÈNOM OBDOBÍ", "V DOBÌ VÁNOÈNÍ", "", "", "", "V DOBÌ VÁNOÈNÍ", "A KARÁCSONYI IDÕBEN"},
 {"V CEZROÈNOM OBDOBÍ", "V MEZIDOBÍ", "", "", "", "BÌHEM ROKU", "AZ ÉVKÖZI IDÕBEN"},
 {"V PÔSTNOM OBDOBÍ", "V DOBÌ POSTNÍ", "", "", "", "V DOBÌ POSTNÍ", "A NAGYBÖJTI IDÕBEN"},
 {"VO VE¼KOM TİDNI", "VE SVATÉM TİDNU", "", "", "", "VE SVATÉM TİDNU", "A NAGYHÉTEN"},
 {"VO VE¼KONOÈNOM TROJDNÍ", "VE VELIKONOÈNÍM TRIDUU", "", "", "", "VE VELIKONOÈNÍM TRIDUU", "A SZENT HÁROM NAPBAN"},
 {"VO VE¼KONOÈNEJ OKTÁVE", "VE VELIKONOÈNÍM OKTÁVU", "", "", "", "V OKTÁVU VELIKONOÈNÍM", "HÚSVÉT NYOLCACADÁBAN"},
 {"VO VE¼KONOÈNOM OBDOBÍ", "V DOBÌ VELIKONOÈNÍ", "", "", "", "V DOBÌ VELIKONOÈNÍ", "A HÚSVÉTI IDÕBEN"},
 {"VO VE¼KONOÈNOM OBDOBÍ", "V DOBÌ VELIKONOÈNÍ", "", "", "", "V DOBÌ VELIKONOÈNÍ", "A HÚSVÉTI IDÕBEN"},
};

#define		nazov_OBDOBIA_V(a)	nazov_OBDOBIA_V_jazyk[a][_global_jazyk]

// used for Sundays - "which" Sunday for some of them, e.g. "dominica V paschae" for 5-th Sunday in that liturgical period (uppercase)
// 2008-12-20: doplnené - pouíva sa v init_global_string() pre nedele niektorıch období [zatia¾ iba v slovenèine]
const char *nazov_OBDOBIA_AKA_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1] =
{
 {"ADVENTNÁ", "ADVENTNÍ", "", "", "", "ADVENTNÍ", "ADVENT"},
 {"ADVENTNÁ", "ADVENTNÍ", "", "", "", "ADVENTNÍ", "ADVENT"},
 {"V OKTÁVE NARODENIA PÁNA", "V OKTÁVU NAROZENÍ PÁNÌ", "", "", "", "V OKTÁVU NAROZENÍ PÁNÌ", "A KARÁCSONY NYOLCADÁBAN"}, // not used / nepouíva sa
 {"VIANOÈNÁ", "VÁNOÈNÍ", "", "", "", "VÁNOÈNÍ", "KARÁCSONY"},
 {"VIANOÈNÁ", "VÁNOÈNÍ", "", "", "", "VÁNOÈNÍ", "KARÁCSONY"},
 {"CEZROÈNÁ", "V MEZIDOBÍ", "", "", "", "BÌHEM ROKU", "ÉVKÖZI"},
 {"PÔSTNA", "POSTNÍ", "", "", "", "POSTNÍ", "NAGYBÖJT"},
 {"VO VE¼KOM TİDNI", "VE SVATÉM TİDNU", "", "", "", "VE SVATÉM TİDNU", "hu_"}, // not used / nepouíva sas
 {"VO VE¼KONOÈNOM TROJDNÍ", "VE VELIKONOÈNÍM TRIDUU", "", "", "", "VE VELIKONOÈNÍM TRIDUU", "hu_"}, // not used / nepouíva sa
 {"VO VE¼KONOÈNEJ OKTÁVE", "VE VELIKONOÈNÍM OKTÁVU", "", "", "", "V OKTÁVU VELIKONOÈNÍM", "HÚSVÉT NYOLCACADÁBAN"}, // not used / nepouíva sa
 {"VE¼KONOÈNÁ", "VELIKONOÈNÍ", "", "", "", "VELIKONOÈNÍ", "HÚSVÉT"},
 {"VE¼KONOÈNÁ", "VELIKONOÈNÍ", "", "", "", "VELIKONOÈNÍ", "HÚSVÉT"},
};
#define		nazov_OBDOBIA_AKA(a)	nazov_OBDOBIA_AKA_jazyk[a][_global_jazyk]

// filenames - same for all languages (based on Slovak)
// nazov_obdobia: string pre nazov suboru .htm liturgickeho obdobia
const char *nazov_obd_htm[POCET_OBDOBI + 1] =
{"adv1.htm", "adv2.htm", "vian1.htm",
 "vian1.htm", "vian2.htm", "cezrok.htm",
 "post1.htm", "vtyz.htm",
 "vtroj.htm", "vnokt.htm", "vn1.htm", "vn2.htm"
};

// anchor names in files - same for all languages (based on Slovak)
// nazov_obdobia: string pre nazov kotvy v .htm liturgickeho obdobia
const char *nazov_OBD[POCET_OBDOBI + 1] =
{"ADV1", "ADV2", "OKTNAR",
 "VIAN1", "VIAN2", "OCR",
 "POST1", "VTYZ", 
 "VTROJ", "VNOKT", "VN1", "VN2"
};

// filenames - same for all languages (based on Slovak)
// nazov_obdobia pc: string pre nazov suboru .htm liturgickeho obdobia pre posvatne citania
const char *nazov_obd_htm_pc[POCET_OBDOBI + 1] =
{"adv1_pc.htm", "adv2_pc.htm", "vian1_pc.htm",
 "vian1_pc.htm", "vian2_pc.htm", "cezrok_pc.htm",
 "post1_pc.htm", "vtyz_pc.htm",
 "vtroj_pc.htm", "vnokt_pc.htm", "vn1_pc.htm", "vn2_pc.htm"
};

// anchor names in files used for 4 volumes of breviary - same for all languages (based on Slovak)
// 2005-08-05: Pridané. zväzok breviára (LH) pre spoloèné èasti svätıch v kotvách
const char *zvazok_OBD[POCET_OBDOBI + 1] =
{"ZVI", "ZVI", "ZVI",
 "ZVI", "ZVI", "OCR", // OCR je ZVIII aj ZVIV
 "ZVII", "ZVII",
 "ZVII", "ZVII", "ZVII", "ZVII"
};

// the name of celebration
const char *nazov_slavenia_jazyk[POCET_SLAVENI + 1][POCET_JAZYKOV + 1] =
{{"féria", "férie", "feria", "feria", "férie", "féria", "féria"}, // zmenené z "___", 2012-10-12
 {"slávnos", "slavnost", "celebration", "sollemnitas", "","SLAVNOST", "fõünnep"},
 {"sviatok", "svátek", "", "festum", "","Svátek", "ünnep"},
 {"spomienka", "památka", "", "memoria", "","Památka", "emléknap"},
 {"¾ubovo¾ná spomienka", "nezávazná památka", "", "memoria ad libitum", "","nezávazná památka", "tetszés szerinti emléknap"},
 {"vlastné slávenie", "z vlastních textù", "", "textus proprius", "", "z vlastních textù", "saját szöveg"},
};

#define		nazov_slavenia(a)	nazov_slavenia_jazyk[a][_global_jazyk]

// the name of celebration -- for memoria (in privileged days)
const char *nazov_slavenia_na_spomienku_jazyk[POCET_JAZYKOV + 1] =
{"na spomienku" /* Adam: lepšie by bolo: pripomienka */, "pro pøipomínku", "", "in memoria", "","pro pøipomínku", "megemlékezésül"};

// 2010-08-03: pridanı kalendár

// calendar codes; internal usage for HTTP requests
const char *skratka_kalendara[POCET_KALENDAROV + 1] =
{"??", "la", "sk", "cz", "czop", "cssr", "hu", "svd", "sj", "sdb", "ofm", "op", "cm", "opraem"};

// filenames for special calendars / názov súbora pre kalendáre -- "pro" == propriá
const char *nazov_htm_kalendar[POCET_KALENDAROV + 1] =
{"", "", "", "", "", "pro_cssr.htm", "", "pro_svd.htm", "pro_sj.htm", "pro_sdb.htm", "pro_ofm.htm", "pro_op.htm", "pro_cm.htm", "pro_opraem.htm"};

const char *nazov_kalendara_short[POCET_KALENDAROV + 1] =
{"neurèenı"
,"všeobecnı"
,"všeobecnı SK"
,"všeobecnı CZ"
,"CZOP"
,"SK CSSR"
,"všeobecnı HU"
,"SK SVD"
,"SK SJ"
,"SK SDB"
,"SK OFM"
,"SK OP"
,"SK CM"
,"CZ OPRAEM"
};

// doplnené 2010-10-11
const char *nazov_kalendara_long[POCET_KALENDAROV + 1] =
{""
,""
,"všeobecnı [pre Slovensko]"
,"obecnı [pro Èechy a Moravu]"
,""
,"pre Kongregáciu najsv. Vykupite¾a — redemptoristov (CSsR)" // bol ve¾mi dlhı combo-box, keï bolo: "pre Kongregáciu najsvätejšieho Vykupite¾a — redemptoristov (CSsR)"
,""
,"pre Spoloènos Boieho Slova — verbistov (SVD)"
,"pre Spoloènos Jeišovu — jezuitov (SJ)"
,"pre saleziánsku rodinu — SDB, FMA, ASC" // bolo VDB -> ASC; saleziáni spolupracovníci majú skratku ASC - Associazione dei salesiani cooperatori - teda Zdruzenie salezianov spolupravovnikov (upozornil Mao Linhart, 2012-02-13)
// ,"pre františkánsku rodinu — františkánov<!-- (OFM)-->, kapucínov<!-- (OFMCap)-->, minoritov<!-- (OFMConv.)-->" // 2011-03-21: nefungovalo porovnanie atokalendar lebo HTML odstránilo poznámky
// ,"pre františkánsku rodinu — františkánov, kapucínov, minoritov" // 2011-03-22: sú tam aj mnohé ïalšie rehole a kongregácie, take ma br. Jakub OFM poprosil, aby ostalo iba "pre františkánsku rodinu"
,"pre františkánsku rodinu"
,"pre Reho¾u kazate¾ov — dominikánov (OP)"
,"pre Misijnú spoloènos sv. Vincenta de Paul — lazaristov (CM)"
,"s vlastními texty premonstrátského øádu (OPraem)" // "pro premonstráty (OPraem)"
};

// special "local" or "partial" characteristics of various celebrations - each in one language; no need to translate; special strings will be added
// 2007-08-31: upravené TT -> BA-TT
// 2008-06-23: upravené vzh¾adom k novému usporiadaniu diecéz (intuitívne)
// 2010-03-16: doplnené BA
// 2011-07-25: doplnené názvy èíselnıch konštánt
const char *nazov_slavenia_lokal[] =
{""                                                                                                             // LOKAL_SLAV_NEURCENE
,"len v roòavskej katedrále"                                                                                   // LOKAL_SLAV_ROZNAVA_KATEDRALA
,"hlavnı patrón Trnavskej arcidiecézy"                                                                          // LOKAL_SLAV_TRNAVA_PATRON
,"v Bratislavskej, Trnavskej a Košickej arcidiecéze "HTML_LINE_BREAK"a v Banskobystrickej, Nitrianskej a Roòavskej diecéze" // LOKAL_SLAV_TT_BB_KE_NR_RO
,"v Nitrianskej diecéze sviatok hlavnıch patrónov"                                                              // LOKAL_SLAV_NITRA_PATRON
,"len v Košickej arcidiecéze"                                                                                   // LOKAL_SLAV_KOSICE
,"len v Nitrianskej diecéze"                                                                                    // LOKAL_SLAV_NITRA
,"len v Banskobystrickej diecéze"                                                                               // LOKAL_SLAV_BYSTRICA
,"len v Spišskej diecéze"                                                                                       // LOKAL_SLAV_SPIS
,"len v Roòavskej diecéze"                                                                                     // LOKAL_SLAV_ROZNAVA
,"len v Trnavskej arcidiecéze"                                                                                  // LOKAL_SLAV_TRNAVA
,"len v Dóme sv. Martina v Bratislave"                                                                          // LOKAL_SLAV_DOM_SV_MARTINA
,"v Spišskej diecéze sviatok hlavného patróna"                                                                  // LOKAL_SLAV_SPIS_PATRON
,"v Banskobystrickej diecéze sviatok hlavného patróna"                                                          // LOKAL_SLAV_BYSTRICA_PATRON
,"v Bratislavskej a Trnavskej arcidiecéze "HTML_LINE_BREAK"a v Banskobystrickej, Nitrianskej a Roòavskej diecéze"           // LOKAL_SLAV_TT_BB_NR_RO
,"v Košickej arcidiecéze sviatok hlavného patróna"                                                              // LOKAL_SLAV_KOSICE_PATRON
,"v ilinskej diecéze sviatok hlavnıch patrónov; "HTML_LINE_BREAK"na Slovensku sa slávi 5. júla, slávnos; v Európe sviatok" // LOKAL_SLAV_14_FEB_CYRIL_METOD
,"v Roòavskej diecéze sviatok hlavného patróna"                                                                // LOKAL_SLAV_ROZNAVA_PATRON
,"len v konsekrovanıch kostoloch"                                                                               // LOKAL_SLAV_KONSEKR_KOSTOLY
,"Druhá ve¾konoèná nede¾a — Boieho milosrdenstva"                                                              // LOKAL_SLAV_DRUHA_VELK_NEDELA
,"koniec Oktávy narodenia Pána"                                                                                 // LOKAL_SLAV_KONIEC_OKTAVY_NAR
,"konec Oktávu Narození Pánì"                                                                                   // LOKAL_SLAV_KONIEC_OKTAVY_NAR_CZ
,"hlavního patrona praské arcidiecéze"                                                                         // LOKAL_SLAV_PRAHA_PATRON
,"v praské arcidiecézi"                                                                                        // LOKAL_SLAV_PRAHA
,"v brnìnské diecézi"                                                                                           // LOKAL_SLAV_BRNO
,"na Moravì památka"                                                                                            // LOKAL_SLAV_MORAVA_SPOMIENKA
,"Druhá nedìle velikonoèní – Boího milosrdenství"                                                              // LOKAL_SLAV_DRUHA_VELK_NEDELA_CZ
,"v praské katedrále slavnost"                                                                                 // LOKAL_SLAV_PRAHA_KATEDRALA
,"v èeskobudìjovické diecézi"                                                                                   // LOKAL_SLAV_CESKE_BUDEJOVICE
,"v olomoucké arcidiecézi"                                                                                      // LOKAL_SLAV_OLOMOUC
,"v Èechách svátek"                                                                                             // LOKAL_SLAV_CECHY_SPOMIENKA
,"v plzeòské diecézi svátek hlavního patrona"                                                                   // LOKAL_SLAV_PLZEN_PATRON
,"v ostravsko-opavské diecézi"                                                                                  // LOKAL_SLAV_OSTRAVA_OPAVA
,"v litomìøické diecézi"                                                                                        // LOKAL_SLAV_LITOMERICE
,"v královéhradecké diecézi"                                                                                    // LOKAL_SLAV_HRADEC_KRALOVE
,"jen v posvìcenıch kostelích"                                                                                  // LOKAL_SLAV_KONSEKR_KOSTOLY_CZ 
,"v plzeòské diecézi"                                                                                           // LOKAL_SLAV_PLZEN 
,"v ostravsko-opavské diecézi slavnost"                                                                         // LOKAL_SLAV_OSTRAVA_OPAVA_SLAVNOST
,"v èeskobudìjovické diecézi památka"                                                                           // LOKAL_SLAV_CESKE_BUDEJOVICE_PAMATKA
,"v Bratislavskej arcidiecéze a v Spišskej diecéze sviatok hlavného patróna"                                    // LOKAL_SLAV_SPIS_BA_PATRON
,"v Bratislavskej arcidiecéze"                                                                                  // LOKAL_SLAV_BRATISLAVA
,"Karácsony nyolcada-Kiskarácsony"                                                                              // LOKAL_SLAV_KONIEC_OKTAVY_NAR_HU
,"len pre Inštitút milosrdnıch sestier Sv. kría"                                                               // LOKAL_SLAV_KONGREGACIA_SSK // 2013-08-12: pôvodne bolo: "len pre Kongregáciu milosrdnıch sestier Sv. kría"
,"pre OFMCap: spomienka"                                                                                        // LOKAL_SLAV_SPOMIENKA_OFMCAP
,"pre OFM: sviatok"                                                                                             // LOKAL_SLAV_SVIATOK_OFM
,"pre OFM: spomienka"                                                                                           // LOKAL_SLAV_SPOMIENKA_OFM
,"pre OFMCap: sviatok"                                                                                          // LOKAL_SLAV_SVIATOK_OFMCAP
,"pre FMA: spomienka"                                                                                           // LOKAL_SLAV_SPOMIENKA_FMA
,"pre FMA: slávnos"                                                                                            // LOKAL_SLAV_SLAVNOST_FMA
,"pre SDB: slávnos"                                                                                            // LOKAL_SLAV_SLAVNOST_SDB
,"pre ASC: sviatok"                                                                                             // LOKAL_SLAV_SVIATOK_VDB // VDB -> ASC
,"pre SCSC: sviatok"                                                                                            // LOKAL_SLAV_SVIATOK_SCSC
,"Húsvét 2. vasárnapja — Az Isteni Irgalmasság vasárnapja"                                                      // LOKAL_SLAV_DRUHA_VELK_NEDELA_HU
,"A Szombathelyi egyházmegyében"                                                                                // LOKAL_SLAV_SZOMBATHELYI_EGYH
,"Pozsonyi fõegyházmegye és a Nagyszombati egyházmegye fõpátronusa"                                             // LOKAL_SLAV_POZS_NAGYSZ_PATRON
,"A Szeged-Csanádi egyházmegye északi részében: az egyházmegye védõszentje; fõünnep"                            // LOKAL_SLAV_SZEGED_CSAN_PATRON // 2013-06-27: ??? neviem, odkia¾ sa to tu vzalo
,"A Pécsi egyházmegyében"                                                                                       // LOKAL_SLAV_PECSI_EGYH
,"A Pécsi egyházmegyében: az egyházmegye védõszentje; fõünnep"                                                  // LOKAL_SLAV_PECSI_EGYH_PATRON
,"A Szeged-Csanádi egyházmegye északi részében; ünnep"                                                          // LOKAL_SLAV_SZEGED_CSAN_EGYH
,"A Veszprémi egyházmegyében: Szent Anna, az egyházmegye védõszentje; ünnep"                                    // LOKAL_SLAV_VESZPREMI_EGYH_PATRON
,"A gyõri és székesfehérvári egyházmegyében: az egyházmegye védõszentje"                                        // LOKAL_SLAV_GYORI_SZEKESFEH_EGYH
,"A Kaposvári egyházmegyében; ünnep"                                                                            // LOKAL_SLAV_KAPORSVAR_FELSZ
,"A Váci egyházmegyében; ünnep"                                                                                 // LOKAL_SLAV_VACI_FELSZ
,"Kalocsa-Kecskemét: a fõegyházmegye védõszentje; fõünnep"                                                      // LOKAL_SLAV_KAL_KECS_FOEGYH
,"A Esztergom-Budapest, a fõszékesegyházban; fõünnep"                                                           // LOKAL_SLAV_ESZTERGOM_BUDA_FOEGYH
,"A fôszékesegyházban; fõünnep"                                                                                 // LOKAL_SLAV_KAL_KECS_FELSZ
,"A Gyõri egyházmegyében: székesegyház felszentelése; ünnep"                                                    // LOKAL_SLAV_GYORI_SZEKESEGYH_FELSZ
,"A Váci egyházmegyében: Szent Mihály fõangyal, az egyházmegye védõszentje"                                     // LOKAL_SLAV_VACI_PATRON
,"A Szeged-Csanád: az egyházmegye védõszentje; fõünnep"                                                         // LOKAL_SLAV_SZEGED_CSAN_PATRON2
,"A Veszprém, a fõszékesegyházban; fõünnep"															            // LOKAL_SLAV_VESZPREM_FOEGYH
,"csak a felszentelt templomokban"                                                                              // LOKAL_SLAV_KONSEKR_KOSTOLY_HU
,"A Szeged-Csanád: A székesegyházban; fõünnep"                                                                  // LOKAL_SLAV_SZEGED_CSAN_EGYH2
,"A Pécsi egyházmegyében: A Pécsi egyházmegye társvédõszentje; fõünnep"                                         // LOKAL_SLAV_PECS_PATRON
,"Szombathely: Az egyházmegye védõszentje; fõünnep"                                                             // LOKAL_SLAV_SZOMBATHELYI_PATRON
,"Székesfehérvár: A székesegyházban; fõünnep"                                                                   // LOKAL_SLAV_SZEKESFEHERVAR_EGYH
,"Az Egri fõegyházmegyében: A fõegyházmegye védõszentje; ünnep"                                                 // LOKAL_SLAV_EGER_FOEGYH
,"Az Esztergomi fõegyházmegyében; emléknap"                                                                     // LOKAL_SLAV_ESZTERGOM_EML
,"A Gyõri egyházmegyében"                                                                                       // LOKAL_SLAV_GYOR_EGYH
,"Az Esztergomi fõegyházmegyében"                                                                               // LOKAL_SLAV_ESZTERGOM_FOEGYH
,"Az Egri fõegyházmegyében"                                                                                     // LOKAL_SLAV_EGER_FOEGYH2
,"A Veszprém, a fõegyházmegye társvédõszentje; fõünnep"                                                         // LOKAL_SLAV_VESZPREM_FOEGYH_T
,"A Szatmári egyházmegyében; emléknap"                                                                          // LOKAL_SLAV_SZATMAR
,"v ostatních èeskıch diecézích a v brnìnské diecézi: památka; "HTML_LINE_BREAK"na Moravì mimo brnìnskou diecézi: nezávazná památka" // LOKAL_SLAV_CESKO_BRNO
,"sviatok hlavnej patrónky "HTML_LINE_BREAK"(slovenskej) Kongregácie sestier dominikánok bl. Imeldy"            // LOKAL_SLAV_SVIATOK_OP_ZENY
,"len v ilinskej diecéze"                                                                                      // LOKAL_SLAV_ZILINA
,"na Strahovì: svátek, Nová Øíše: památka"                                                                      // LOKAL_SLAV_OPRAEM_SVIATOK_STRAHOV
,"kanonie Teplá: slavnost"                                                                                      // LOKAL_SLAV_OPRAEM_SLAVNOST_TEPLA
,"jen kanonie Nová Øíše"                                                                                        // LOKAL_SLAV_OPRAEM_NOVA_RISE
,"jen kanonie Strahov a Nová Øíše"                                                                              // LOKAL_SLAV_OPRAEM_STRAHOV_NOVA_RISE
,"jen kanonie eliv"                                                                                            // LOKAL_SLAV_OPRAEM_ZELIV
,"jen kanonie Strahov"                                                                                          // LOKAL_SLAV_OPRAEM_STRAHOV
,"Debrecen-Nyíregyháza és Kaposvár: "HTML_LINE_BREAK"Az egyházmegye védõszentje; fõünnep"                       // LOKAL_SLAV_SZ_LASZLO
,"pre OSC: slávnos"                                                                                            // LOKAL_SLAV_SLAVNOST_OSC
,"pre OFMConv.: sviatok"                                                                                        // LOKAL_SLAV_SVIATOK_OFMCONV
,"pre OFS: sviatok"                                                                                             // LOKAL_SLAV_SVIATOK_OFS
,"pre OFMConv., OFMCap: spomienka"                                                                              // LOKAL_SLAV_SPOMIENKA_OFMCONV_OFMCAP
,"pre OSC: slávnos"                                                                                            // LOKAL_SLAV_SPOMIENKA_OSC
,"pre Slovensko zatia¾ nedovolené slávenie"                                                                     // LOKAL_SLAV_NEDOVOLENE
,"Katonai Ordinariátus: "HTML_LINE_BREAK"Az Ordinariátus védõszentje; fõünnep"                                  // LOKAL_SLAV_KATONAI_ORDINARIAT
,"Debrecen-Nyíregyháza: "HTML_LINE_BREAK"A székesegyház felszentelése; fõünnep"                                 // LOKAL_SLAV_DEBR_NYIREGY
};

// names of liturgical colors
const char *nazov_farby_jazyk[POCET_FARIEB_REALNYCH + 1][POCET_JAZYKOV + 1] =
{{"___", "___", "___", "___", "___", "___", "___"},
 {"èervená", "èervená", "red", "ruber", "", "èervená", "piros"},
 {"biela", "bílá", "white", "albus", "", "bílá", "fehér"},
 {"zelená", "zelená", "green", "viridis", "", "zelená", "zöld"},
 {"fialová", "fialová", "purple", "violaceus", "", "fialová", "lila"},
 {"ruová", "rùová", "rose", "rosaceus", "", "rùová", "rózsaszín"},
 {"èierna", "èerná", "black", "niger", "", "èerná", "fekete"},
};

#define		nazov_farby(a)	nazov_farby_jazyk[a][_global_jazyk]

// 2009-08-26: zmena na štandardné HTML elementy, aby sa dalo pouíva ako inline CSS style
// codes for colors - HTML specific
const char *html_farba_pozadie[POCET_FARIEB_REALNYCH + 1] =
{"#000000" /* "black" */, "#ff0000" /* "red" */, "#ffffff" /* "white" */, "#008000" /* "green" */, "#800080" /* "purple" */, "#FF6699" /* "fuchsia" */, "#000000" /* black */};

// codes for colors - HTML specific
const char *html_farba_popredie[POCET_FARIEB_REALNYCH + 1] =
{"#ffffff" /* "white" */, "#ffffff" /* "white" */, "#000000" /* "black" */, "#ffffff" /* "white" */, "#ffffff" /* "white" */, "#0000ff" /* "blue" */, "#ffffff" /* "white" */};

// codes for colors - HTML specific
const char *html_farba_okraj[POCET_FARIEB_REALNYCH + 1] =
{"#000000" /* "black" */, "#000000" /* "black" */, "#000000" /* "black" */, "#000000" /* "black" */, "#000000" /* "black" */, "#000000" /* "black" */, "#000000" /* black */};

// codes for number of the week from psaltery (psalterium per quattuor hebdomadas distributum)
const char *rimskymi_tyzden_zaltara[ZVAZKY_LH + 1] =
{"_", "I", "II", "III", "IV"};

// const: ordinal number of the first day in specific month
const short int prvy_den[12] =
	{1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};

// const: number (count) of days in specific month
short int pocet_dni[12] =
	{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// const: "the Sunday's letter" A--g
const char char_nedelne_pismeno[POCET_DNI] =
	{'b', 'c', 'd', 'e', 'f', 'g', 'A'};

// const: the Sunday's cycle A--C
const char char_nedelny_cyklus[POCET_NEDELNY_CYKLUS] =
	{'A', 'B', 'C'};

// names of the days in week, starting with Sunday (lowercase) / nazov_dna: string pre nazov dna; suhlasi s struct tm.tm_wday; 
// Weekday (0--6; Sunday/nedela = 0)
const char *nazov_dna_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1] = 
{ {"nede¾a", "nedìle", "Sunday", "dominica", "", "nedìle", "vasárnap"}
, {"pondelok" , "pondìlí", "Monday", "feria secunda", "", "pondìlí", "hétfõ"}
, {"utorok" , "úterı", "Tuesday", "feria tertia", "", "úterı", "kedd"}
, {"streda" , "støeda", "Wednesday", "feria quarta", "", "støeda", "szerda"}
, {"štvrtok" , "ètvrtek", "Thursday", "feria quinta", "", "ètvrtek", "csütörtök"}
, {"piatok" , "pátek", "Friday", "feria sexta", "", "pátek", "péntek"}
, {"sobota" , "sobota", "Saturday", "sabbatum", "", "sobota", "szombat"}
, {"neznámy" , "neznámı", "unknown", "???", "", "neznámı", "ismeretlen"}
};

#define		nazov_dna(a)	nazov_dna_jazyk[a][_global_jazyk]

// names of the days in week, starting with Sunday (lowercase without special characters - plain ASCII (0--128) only)
const char *nazov_dna_asci_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1] = 
{ {"nedela", "nedele", "Sunday", "Dominica", "", "nedele", "vasarnap"}
, {"pondelok" , "pondeli", "Monday", "Feria secunda", "", "pondeli", "hetfo"}
, {"utorok" , "utery", "Tuesday", "Feria tertia", "", "utery", "kedd"}
, {"streda" , "streda", "Wednesday", "Feria quarta", "", "streda", "szerda"}
, {"stvrtok" , "ctvrtek", "Thursday", "Feria quinta", "", "ctvrtek", "csutortok"}
, {"piatok" , "patek", "Friday", "Feria sexta", "", "patek", "pentek"}
, {"sobota" , "sobota", "Saturday", "Sabbatum", "", "sobota", "szombat"}
, {"neznamy" , "neznamy", "unknown", "???", "", "neznamy", "ismeretlen"}
};

#define		nazov_dna_asci(a)	nazov_dna_asci_jazyk[a][_global_jazyk]

// names of the days in week, starting with Sunday (sentence case)
const char *nazov_Dna_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1] = 
{ {"Nede¾a", "Nedìle", "Sunday", "Dominica", "", "Nedìle", "Vasárnap"}
, {"Pondelok" , "Pondìlí", "Monday", "Feria secunda", "", "Pondìlí", "Hétfõ"}
, {"Utorok" , "Úterı", "Tuesday", "Feria tertia", "", "Úterı", "Kedd"}
, {"Streda" , "Støeda", "Wednesday", "Feria quarta", "", "Støeda", "Szerda"}
, {"Štvrtok" , "Ètvrtek", "Thursday", "Feria quinta", "", "Ètvrtek", "Csütörtök"}
, {"Piatok" , "Pátek", "Friday", "Feria sexta", "", "Pátek", "Péntek"}
, {"Sobota" , "Sobota", "Saturday", "Sabbatum", "", "Sobota", "Szombat"}
, {"Neznámy" , "Neznámı", "unknown", "???", "", "Neznámı", "Ismeretlen"}
};

#define		nazov_Dna(a)	nazov_Dna_jazyk[a][_global_jazyk]

// names of the days in week, starting with Sunday (uppercase)
const char *nazov_DNA_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1] = 
{ {"NEDE¼A", "NEDÌLE", "SUNDAY", "DOMINICA", "", "NEDÌLE", "VASÁRNAP"}
, {"PONDELOK" , "PONDÌLÍ", "MONDAY", "FERIA SECUNDA", "", "PONDÌLÍ", "HÉTFÕ"}
, {"UTOROK" , "ÚTERİ", "TUESDAY", "FERIA TERTIA", "", "ÚTERİ", "KEDD"}
, {"STREDA" , "STØEDA", "WEDNESDAY", "FERIA QUARTA", "", "STØEDA", "SZERDA"}
, {"ŠTVRTOK" , "ÈTVRTEK", "THURSDAY", "FERIA QUINTA", "", "ÈTVRTEK", "CSÜTÖRTÖK"}
, {"PIATOK" , "PÁTEK", "FRIDAY", "FERIA SEXTA", "", "PÁTEK", "PÉNTEK"}
, {"SOBOTA" , "SOBOTA", "SATURDAY", "SABBATUM", "", "SOBOTA", "SZOMBAT"}
, {"NEZNÁMY" , "NEZNÁMİ", "UNKNOWN", "???", "", "NEZNÁMİ", "ISMERETLEN"}
};

#define		nazov_DNA(a)	nazov_DNA_jazyk[a][_global_jazyk]

// 2011-05-17: doplnené
#define KONCOVKA_DNA_HU "JA" // vasárnapja
#define KONCOVKA_DNA_HU_SMALL "ja"

// two/three-letter abbreviations of the names of the days in week, starting with Sunday (sentence case)
const char *nazov_Dn_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1] = 
{ {"Ne" , "Ne", "Sun", "Do", "", "Ne", "V"}
, {"Po" , "Po", "Mon", "F2", "", "Po", "H"}
, {"Ut" , "Út", "Tue", "F3", "", "Út", "K"}
, {"St" , "St", "Wed", "F4", "", "St", "Sze"}
, {"Št" , "Èt", "Thu", "F5", "", "Èt", "Cs"}
, {"Pi" , "Pá", "Fri", "F6", "", "Pá", "P"}
, {"So" , "So", "Sat", "Sá", "", "So", "Szo"}
, {"??" , "??", "???", "", "", "??", "??"}
};

#define		nazov_Dn(a)	nazov_Dn_jazyk[a][_global_jazyk]

// two/three-letter abbreviations of the names of the days in week, starting with Sunday used for anchors (uppercase, no need to translate; based on Slovak)
// 2006-08-01: pouíva sa pre HTML kotvy, ktoré nezávisia od jazykovej mutácie
const char *nazov_DN_asci[POCET_DNI + 1] =
{"NE", "PO", "UT", "STR", "STV", "PI", "SO", "??"};

// two/three-letter abbreviations of the names of the days in week, starting with Sunday used for debug info (lowercase, no need to translate; based on Slovak)
const char *nazov_dn_asci[POCET_DNI + 1] =
{"ne", "po", "ut", "str", "stv", "pi", "so", "??"};

// the names of the months (lowecase) / nazov_mesiaca: string pre nazov dna; suhlasi s struct tm.tm_mon;
// Month (0--11)
const char *nazov_mesiaca_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1] = 
{ {"január", "leden", "January", "ianuarius", "", "leden", "január"}
, {"február" , "únor", "February", "februarius", "", "únor", "február"}
, {"marec" , "bøezen", "March", "martius", "", "bøezen", "március"}
, {"apríl" , "duben", "April", "aprilis", "", "duben", "április"}
, {"máj" , "kvìten", "May", "maius", "", "kvìten", "május"}
, {"jún" , "èerven", "June", "iunius", "", "èerven", "június"}
, {"júl" , "èervenec", "July", "iulius", "", "èervenec", "július"}
, {"august" , "srpen", "August", "augustus", "", "srpen", "augusztus"}
, {"september" , "záøí", "September", "september", "", "záøí", "szeptember"}
, {"október" , "øíjen", "October", "october", "", "øíjen", "október"}
, {"november" , "listopad", "November", "november", "", "listopad", "november"}
, {"december" , "prosinec", "December", "december", "", "prosinec", "december"}
, {"neznámy" , "neznámı", "unknown", "___", "", "neznámı", "ismeretlen"}
};

#define		nazov_mesiaca(a)	nazov_mesiaca_jazyk[a][_global_jazyk]

// the names of the months (lowecase without special characters, plain ASCII 0--128)
const char *nazov_mesiaca_asci_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1] = 
{ {"januar", "leden", "January", "Ianuarius", "", "leden", "januar"}
, {"februar" , "unor", "February", "Februarius", "", "unor", "februar"}
, {"marec" , "brezen", "March", "Martius", "", "brezen", "marcius"}
, {"april" , "duben", "April", "Aprilis", "", "duben", "aprilis"}
, {"maj" , "kveten", "May", "Maius", "", "kveten", "majus"}
, {"jun" , "cerven", "June", "Iunius", "", "cerven", "junius"}
, {"jul" , "cervenec", "July", "Iulius", "", "cervenec", "julius"}
, {"august" , "srpen", "August", "Augustus", "", "srpen", "augusztus"}
, {"september" , "zari", "September", "September", "", "zari", "szeptember"}
, {"oktober" , "rijen", "October", "October", "", "rijen", "oktober"}
, {"november" , "listopad", "November", "November", "", "listopad", "november"}
, {"december" , "prosinec", "December", "December", "", "prosinec", "december"}
, {"neznamy" , "neznamy", "unknown", "___", "", "neznamy", "ismeretlen"}
};

#define		nazov_mesiaca_asci(a)	nazov_mesiaca_asci_jazyk[a][_global_jazyk]

// the names of the months (sentence case)
const char *nazov_Mesiaca_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1] = 
{ {"Január", "Leden", "January", "Ianuarius", "", "Leden", "Január"}
, {"Február" , "Únor", "February", "Februarius", "", "Únor", "Február"}
, {"Marec", "Bøezen", "March", "Martius", "", "Bøezen", "Március"}
, {"Apríl" , "Duben", "April", "Aprilis", "", "Duben", "Április"}
, {"Máj" , "Kvìten", "May", "Maius", "", "Kvìten", "Május"}
, {"Jún" , "Èerven", "June", "Iunius", "", "Èerven", "Június"}
, {"Júl" , "Èervenec", "July", "Iulius", "", "Èervenec", "Július"}
, {"August" , "Srpen", "August", "Augustus", "", "Srpen", "Augusztus"}
, {"September" , "Záøí", "September", "September", "", "Záøí", "Szeptember"}
, {"Október" , "Øíjen", "October", "October", "", "Øíjen", "Október"}
, {"November" , "Listopad", "November", "November", "", "Listopad", "November"}
, {"December" , "Prosinec", "December", "December", "", "Prosinec", "December"}
, {"Neznámy" , "Neznámı", "unknown", "???", "", "Neznámı", "Ismeretlen"}
};

#define		nazov_Mesiaca(a)	nazov_Mesiaca_jazyk[a][_global_jazyk]

// the names of the months (uppercase)
const char *nazov_MESIACA_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1] = 
{ {"JANUÁR", "LEDEN", "JANUARY", "IANUARIUS", "", "LEDEN", "JANUÁR"}
, {"FEBRUÁR" , "ÚNOR", "FEBRUARY", "FEBRUARIUS", "", "ÚNOR", "FEBRUÁR"}
, {"MAREC", "BØEZEN", "MARCH", "MARTIUS", "", "BØEZEN", "MÁRCIUS"}
, {"APRÍL" , "DUBEN", "APRIL", "APRILIS", "", "DUBEN", "ÁPRILIS"}
, {"MÁJ" , "KVÌTEN", "MAY", "MAIUS", "", "KVÌTEN", "MÁJUS"}
, {"JÚN" , "ÈERVEN", "JUNE", "IUNIUS", "", "ÈERVEN", "JÚNIUS"}
, {"JÚL" , "ÈERVENEC", "JULY", "IULIUS", "", "ÈERVENEC", "JÚLIUS"}
, {"AUGUST" , "SRPEN", "AUGUST", "AUGUSTUS", "", "SRPEN", "AUGUSZTUS"}
, {"SEPTEMBER" , "ZÁØÍ", "SEPTEMBER", "SEPTEMBER", "", "ZÁØÍ", "SZEPTEMBER"}
, {"OKTÓBER" , "ØÍJEN", "OCTOBER", "OCTOBER", "", "ØÍJEN", "OKTÓBER"}
, {"NOVEMBER" , "LISTOPAD", "NOVEMBER", "NOVEMBER", "", "LISTOPAD", "NOVEMBER"}
, {"DECEMBER" , "PROSINEC", "DECEMBER", "DECEMBER", "", "PROSINEC", "DECEMBER"}
, {"NEZNÁMY" , "NEZNÁMİ", "UNKNOWN", "???", "", "NEZNÁMİ", "ISMERETLEN"}
};

#define		nazov_MESIACA(a)	nazov_MESIACA_jazyk[a][_global_jazyk]

// the names of the months (lowercase) in genitive grammatically 2.th declination?; in English: "IN that month" or "OF that month" / genitív == 2. pád, koho/èoho
// usage: when generated string for date, e.g. en: "1st January 2000", sk: "1. januára 2000"
// 2007-03-20: pridanı genitív názvu mesiaca kvôli latinèine
const char *nazov_mesiaca_gen_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1] = 
{ {"januára", "ledna", "January", "ianuarii", "", "ledna", "január"}
, {"februára" , "února", "February", "februarii", "", "února", "február"}
, {"marca" , "bøezna", "March", "martii", "", "bøezna", "március"}
, {"apríla" , "dubna", "April", "aprilis", "", "dubna", "április"}
, {"mája" , "kvìtna", "May", "maii", "", "kvìtna", "május"}
, {"júna" , "èervna", "June", "iunii", "", "èervna", "június"}
, {"júla" , "èervence", "July", "iulii", "", "èervence", "július"}
, {"augusta" , "srpna", "August", "augusti", "", "srpna", "augusztus"}
, {"septembra" , "záøí", "September", "septembris", "", "záøí", "szeptember"}
, {"októbra" , "øíjna", "October", "octobris", "", "øíjna", "október"}
, {"novembra" , "listopadu", "November", "novembris", "", "listopadu", "november"}
, {"decembra" , "prosince", "December", "decembris", "", "prosince", "december"}
, {"neznámeho" , "neznámého", "unknown", "___", "", "neznámého", "ismeretlen"}
};

#define		nazov_mesiaca_gen(a)	nazov_mesiaca_gen_jazyk[a][_global_jazyk]

// 2007-03-20: pridanı genitív názvu mesiaca kvôli latinèine
const char *nazov_Mesiaca_gen_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1] = 
{ {"Januára", "Ledna", "January", "Ianuarii", "", "Ledna", "Január"}
, {"Februára" , "Února", "February", "Februarii", "", "Února", "Február"}
, {"Marca" , "Bøezna", "March", "Martii", "", "Bøezna", "Március"}
, {"Apríla" , "Dubna", "April", "Aprilis", "", "Dubna", "Április"}
, {"Mája" , "Kvìtna", "May", "Maii", "", "Kvìtna", "Május"}
, {"Júna" , "Èervna", "June", "Iunii", "", "Èervna", "Június"}
, {"Júla" , "Èervence", "July", "Iulii", "", "Èervence", "Július"}
, {"Augusta" , "Srpna", "August", "Augusti", "", "Srpna", "Augusztus"}
, {"Septembra" , "Záøí", "September", "Septembris", "", "Záøí", "Szeptember"}
, {"Októbra" , "Øíjna", "October", "Octobris", "", "Øíjna", "Október"}
, {"Novembra" , "Listopadu", "November", "Novembris", "", "Listopadu", "November"}
, {"Decembra" , "Prosince", "December", "Decembris", "", "Prosince", "December"}
, {"Neznámeho" , "Neznámého", "Unknown", "___", "", "Neznámého", "Ismeretlen"}
};

#define		nazov_Mesiaca_gen(a)	nazov_Mesiaca_gen_jazyk[a][_global_jazyk]

// three-letter abbreviations of the names of the months used for anchors (uppercase, no need to translate; based on Slovak)
const char *nazov_MES[POCET_MESIACOV + 1] =
{"JAN", "FEB", "MAR", "APR", "MAJ", "JUN", "JUL", "AUG", "SEP", "OKT", "NOV", "DEC", "___"};

// three-letter abbreviations of the names of the months used for anchors (lowercase, no need to translate; based on Slovak)
const char *nazov_mes[POCET_MESIACOV + 1] =
{"jan", "feb", "mar", "apr", "maj", "jun", "jul", "aug", "sep", "okt", "nov", "dec", "___"};

// ordinal numbers for first few Sundays (sentence case) - used for special occasions currently only in Slovak; no need to change
// 2008-12-20: pridanı reazec pre poradové èíslo - pouíva sa v init_global_string() pre nedele niektorıch období [zatia¾ iba v slovenèine]
const char *poradie_Slovom_jazyk[POCET_TYZDNOV + 1][POCET_JAZYKOV + 1] = 
{ {"Prvá", "První", "", "", "", "První", "1."}
, {"Druhá" , "Druhá", "", "", "", "Druhá", "2."}
, {"Tretia" , "Tøetí", "", "", "", "Tøetí", "3."}
, {"Štvrtá" , "Ètvrtá", "", "", "", "Ètvrtá", "4."}
, {"Piata" , "Pátá", "", "", "", "Pátá", "5."}
, {"Šiesta" , "Šestá", "", "", "", "Šestá", "6."}
, {"Siedma" , "Sedmá", "", "", "", "Sedmá", "7."}
, {"Ôsma" , "Osmá", "", "", "", "Osmá", "8."}
, {"Deviata" , "Devátá", "", "", "", "Devátá", "9."}
, {"Desiata" , "Desátá", "", "", "", "Desátá", "10."}
, {"11. ", "11", "11", "11", "11", "11", "11."}
, {"12. ", "12", "12", "12", "12", "12", "12."}
, {"13. ", "13", "13", "13", "13", "13", "13."}
, {"14. ", "14", "14", "14", "14", "14", "14."}
, {"15. ", "15", "15", "15", "15", "15", "15."}
, {"16. ", "16", "16", "16", "16", "16", "16."}
, {"17. ", "17", "17", "17", "17", "17", "17."}
, {"18. ", "18", "18", "18", "18", "18", "18."}
, {"19. ", "19", "19", "19", "19", "19", "19."}
, {"20. ", "20", "20", "20", "20", "20", "20."}
, {"21. ", "21", "21", "21", "21", "21", "21."}
, {"22. ", "22", "22", "22", "22", "22", "22."}
, {"23. ", "23", "23", "23", "23", "23", "23."}
, {"24. ", "24", "24", "24", "24", "24", "24."}
, {"25. ", "25", "25", "25", "25", "25", "25."}
, {"26. ", "26", "26", "26", "26", "26", "26."}
, {"27. ", "27", "27", "27", "27", "27", "27."}
, {"28. ", "28", "28", "28", "28", "28", "28."}
, {"29. ", "29", "29", "29", "29", "29", "29."}
, {"30. ", "30", "30", "30", "30", "30", "30."}
, {"31. ", "31", "31", "31", "31", "31", "31."}
, {"32. ", "32", "32", "32", "32", "32", "32."}
, {"33. ", "33", "33", "33", "33", "33", "33."}
, {"34. ", "34", "34", "34", "34", "34", "34."}
};

// the same as "poradie_Slovom_jazyk" ordinal numbers for first few Sundays (uppercase) - used for special occasions currently only in Slovak; no need to change
const char *poradie_SLOVOM_jazyk[POCET_TYZDNOV + 1][POCET_JAZYKOV + 1] = 
{ {"PRVÁ", "PRVNÍ", "", "", "", "PRVNÍ", "1."}
, {"DRUHÁ" , "DRUHÁ", "", "", "", "DRUHÁ", "2."}
, {"TRETIA" , "TØETÍ", "", "", "", "TØETÍ", "3."}
, {"ŠTVRTÁ" , "ÈTVRTÁ", "", "", "", "ÈTVRTÁ", "4."}
, {"PIATA" , "PÁTÁ", "", "", "", "PÁTÁ", "5."}
, {"ŠIESTA" , "ŠESTÁ", "", "", "", "ŠESTÁ", "6."}
, {"SIEDMA" , "SEDMÁ", "", "", "", "SEDMÁ", "7."}
, {"OSMA" , "OSMÁ", "", "", "", "OSMÁ", "8."}
, {"DEVIATA" , "DEVÁTÁ", "", "", "", "DEVÁTÁ", "9."}
, {"DESIATA" , "DESÁTÁ", "", "", "", "DESÁTÁ", "10."}
, {"11. ", "11", "11", "11", "11", "11", "11."}
, {"12. ", "12", "12", "12", "12", "12", "12."}
, {"13. ", "13", "13", "13", "13", "13", "13."}
, {"14. ", "14", "14", "14", "14", "14", "14."}
, {"15. ", "15", "15", "15", "15", "15", "15."}
, {"16. ", "16", "16", "16", "16", "16", "16."}
, {"17. ", "17", "17", "17", "17", "17", "17."}
, {"18. ", "18", "18", "18", "18", "18", "18."}
, {"19. ", "19", "19", "19", "19", "19", "19."}
, {"20. ", "20", "20", "20", "20", "20", "20."}
, {"21. ", "21", "21", "21", "21", "21", "21."}
, {"22. ", "22", "22", "22", "22", "22", "22."}
, {"23. ", "23", "23", "23", "23", "23", "23."}
, {"24. ", "24", "24", "24", "24", "24", "24."}
, {"25. ", "25", "25", "25", "25", "25", "25."}
, {"26. ", "26", "26", "26", "26", "26", "26."}
, {"27. ", "27", "27", "27", "27", "27", "27."}
, {"28. ", "28", "28", "28", "28", "28", "28."}
, {"29. ", "29", "29", "29", "29", "29", "29."}
, {"30. ", "30", "30", "30", "30", "30", "30."}
, {"31. ", "31", "31", "31", "31", "31", "31."}
, {"32. ", "32", "32", "32", "32", "32", "32."}
, {"33. ", "33", "33", "33", "33", "33", "33."}
, {"34. ", "34", "34", "34", "34", "34", "34."}
};

// the names of languages
// 2006-07-11: Pridané kvôli jazykovım mutáciám
const char *nazov_jazyka[POCET_JAZYKOV + 1] =
{"slovenèina", "èeština", "English", "lingua latina", "(neurèenı)", "èeština-dominikáni", "magyar"};

// language codes; internal usage for HTTP requests
const char *skratka_jazyka[POCET_JAZYKOV + 1] =
{"sk", "cz", "en", "la", "??", "c2", "hu"};

// language codes; internal usage for include directories (postfix of directory/folder name); postfix MUST NOT contain slash/backslash
// 2006-07-13 a 17: Pridané kvôli jazykovım mutáciám - postfix pre include adresár
const char *postfix_jazyka[POCET_JAZYKOV + 1] =
{"", "cz", "en", "la", "", "czop", "hu"};
// Poznámka: Postfix nesmie obsahova na zaèiatku odde¾ovaè (slash resp. backslash); musí sa jedna o podadresár pod include

const short int format_datumu[POCET_JAZYKOV + 1] = {
	/* sk */ FORMAT_DATUMU_DEN_MESIAC_ROK, /* cz */ FORMAT_DATUMU_DEN_MESIAC_ROK, /* en */ FORMAT_DATUMU_MESIAC_DEN_ROK,
	/* la */ FORMAT_DATUMU_DEN_MESIAC_ROK, /* ?? */ FORMAT_DATUMU_DEN_MESIAC_ROK, /* czop */ FORMAT_DATUMU_DEN_MESIAC_ROK,
	/* hu */ FORMAT_DATUMU_ROK_MESIAC_DEN,
};

// filename of CSS file; the number of CSS does not directly correspond to the number of languages
// 2006-08-08: Pridané kvôli rôznym css
const char *nazov_css[POCET_CSS + 1] =
{"(css neurèené)", "breviar.css", "breviar-invert.css", "breviar-kbd.css", "ebreviar-cz.css", "breviar-cz-op.css"
	, "breviar-2003-07-16.css", "breviar-2005-10-13.css", "breviar-2007-08-10.css", "breviar-2008-05-07.css"
	, "breviar-jm-krize-cz.css", "breviar-kbs.css"};

const char *skratka_css[POCET_CSS + 1] =
{"__", "def", "invert", "kbd", "cz", "czop"
	, "2003", "2005", "2007", "2008"
	, "jmkcz", "kbs"};

// 2012-04-03: Pridané kvôli jazykovım mutáciám -- default CSS pre danı jazyk | mono do budúcnosti monos default nastavenia v config (konfiguraènom súbore)
const short int default_css_jazyk[POCET_JAZYKOV + 1] =
{CSS_breviar_sk, CSS_ebreviar_cz, CSS_breviar_sk, CSS_breviar_sk, CSS_breviar_sk, CSS_breviar_cz_op, CSS_breviar_sk};

// CSS obsahujuci invertovane farby
const char *nazov_css_invert_colors = "breviar-invert-colors.css";

// CSS obsahujuci force normal font weight
const char *nazov_css_normal_font_weight = "breviar-normal-font.css";

// language charset (encoding); used for HTML heading
const char *charset_jazyka[POCET_JAZYKOV + 1] =
{"windows-1250", "windows-1250", "windows-1251", "windows-1251", "utf-8", "windows-1250", "windows-1250"};

// 2011-05-06: pridané kvôli monosti vo¾by písma
const char *nazov_fontu[POCET_FONTOV + 1] =
{"", "pod¾a CSS", "pod¾a vıberu", "Cambria", "Candara", "Georgia", "Tahoma", "Helvetica", "serif", "sans-serif"};
const char *nazov_fontu_CHECKBOX[POCET_JAZYKOV + 1] =
{"pod¾a vıberu", "podle vıbìru", "according to checkbox above", "checkbox", "", "podle vıbìru", "checkbox"};
const char *nazov_fontu_CSS[POCET_FONTOV + 1] =
{"pod¾a CSS", "podle CSS", "according to CSS", "CSS", "CSS", "podle CSS", "CSS szerint"};
// 2011-05-13: pridané kvôli monosti vo¾by ve¾kosti písma
const char *nazov_font_size_jazyk[POCET_FONT_SIZE + 1][POCET_JAZYKOV + 1] = {
{"", "", "", "", "", "", ""},
{"pod¾a CSS", "podle CSS", "according to CSS", "CSS", "", "podle CSS", "CSS szerint"},
{"malilinké", "malinkaté", "xx-small", "xx-small", "", "malinkaté", "apró"},
{"ve¾mi malé", "velmi malé", "extra small", "extra small", "", "velmi malé", "nagyon kicsi"},
{"malé", "malé", "small", "small", "", "malé", "kicsi"},
{"stredné", "støední", "medium", "medium", "", "støední", "közepes"},
{"ve¾ké", "veliké", "large", "large", "", "veliké", "nagy"},
{"ve¾mi ve¾ké", "velmi veliké", "extra large", "extra large", "", "velmi veliké", "nagyon nagy"},
{"obrovské", "obrovské", "xx-large", "xx-large", "", "obrovské", "óriási"}
};
#define nazov_font_size(a) nazov_font_size_jazyk[a][_global_jazyk]
const char *nazov_font_size_css[POCET_FONT_SIZE + 1] = 
{"", "inherit", "xx-small", "x-small", "small", "medium", "large", "x-large", "xx-large"};

// strings of buttons - abbreviations of prayer names // shortened because of usage on mobile devices (Android)
const char *html_button_nazov_modlitby_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1] = 
{ {"Inv.", "Inv.", "Inv.", "Inv.", "", "Inv.", "Imád."}
, {"Posv. èít.", "Ètení", "Reading", "Off. lect.", "", "Ètení", "Olvasm. i."}
, {"Ranné chv.", "Ranní chv.", "Morning pr.", "Laudes", "", "Ranní chv.", "Reggeli dics."}
, {"9h", "9h", "9h", "Tertia", "", "Tercie", "Délelõtt"}
, {"12h", "12h", "12h", "Sexta", "", "Sexta", "Délben"}
, {"15h", "15h", "15h", "Nona", "", "Nona", "Délután"}
, {"Vešpery", "Nešpory", "Vesperae", "Vesperae", "", "Veèerní chv.", "Esti dics."}
, {"Kompl.", "Kompl.", "Compl.", "Compl.", "", "Kompl.", "Befejezõ i."}
// táto sa pre HTML buttony nepouíva
	, {"neurèená", "neurèena", "not-defined", "no data", "", "neurèena", "nem azonosított"}
, {"Prvé vešp.", "První nešp.", "1st Vesperae", "I vesperae", "", "První v. chv.", "I. esti dics." }
, {"Prvé kompl.", "První kompl.", "Compl.", "Compl.", "", "První kompl.", "Bef. i. I.e.d.után"}
, {"Druhé vešp.", "Druhé nešpory", "2nd Vesperae", "II vesperae", "", "Druhé veèerní chv.", "II. esti dics." }
, {"Druhé kompl.", "Druhı kompl.", "2nd Completary", "II completorio", "", "Druhı kompl.", "Bef. i. II.e.d.után" }
// , {"Vo¾ba detailov...", "Podrobnìji...", "Details...", "Optiónes...", "", "Podrobnìji...", "Részletek..."} // 2011-10-03: prakticky je to teraz len o vıbere spoloènıch èastí
, {"vıber spoloènej èasti...", "vıbìr spoleèné èásti...", "common texts...", "optiónes...", "", "vıbìr spoleèné èásti...", "közös rész kiválasztása..."}
, {"všetky", "všechny", "all", "all", "", "všechny", "összes" }
};

#define		html_button_nazov_modlitby(a)	html_button_nazov_modlitby_jazyk[a][_global_jazyk]

// special button: Details...
#ifndef HTML_BUTTON_DETAILY
#define HTML_BUTTON_DETAILY	html_button_nazov_modlitby_jazyk[MODL_DETAILY][_global_jazyk]
#endif

// special button: Show prayer
const char *html_button_det_show[POCET_JAZYKOV + 1] = {"Zobraz modlitbu", "Uka modlitbu", "Show prayer", "xxx", "", "Uka modlitbu", "Mutasd az imát"};
#ifndef HTML_BUTTON_DET_SHOW
#define HTML_BUTTON_DET_SHOW	html_button_det_show[_global_jazyk]
#endif

// special button: Defaults
const char *html_button_det_defaults[POCET_JAZYKOV + 1] = {"Pôvodné hodnoty", "Pùvodní hodnoty", "Defaults", "___", "", "Pùvodní hodnoty", "Alapértelmezett"};
#ifndef HTML_BUTTON_DET_DEFAULTS
#define HTML_BUTTON_DET_DEFAULTS	html_button_det_defaults[_global_jazyk]
#endif

// special button (today): Show
const char *html_button_dnes_show[POCET_JAZYKOV + 1] = {"Zobrazi", "Uka", "Show", "___", "", "Uka", "Mutasd"};
#ifndef HTML_BUTTON_DNES_SHOW
#define HTML_BUTTON_DNES_SHOW	html_button_dnes_show[_global_jazyk]
#endif

// special button (today): Defaults (clear form)
// const char *html_button_dnes_defaults[POCET_JAZYKOV + 1] = {"Vyèisti", "Vyèisti", "Clear", "???", "", "Vyèisti", "Töröl"};
#ifndef HTML_BUTTON_DNES_DEFAULTS
#define HTML_BUTTON_DNES_DEFAULTS	HTML_BUTTON_DET_DEFAULTS
#endif

// special button (today): Apply settings/options
const char *html_button_dnes_apply[POCET_JAZYKOV + 1] = {"Potvrdi", "Potvrdit", "Apply", "___", "", "Potvrdit", "Alkalmaz"};
#ifndef HTML_BUTTON_DNES_APPLY_SETTINGS
#define HTML_BUTTON_DNES_APPLY_SETTINGS	html_button_dnes_apply[_global_jazyk]
#endif

// special button (today): Apply options 2 (various choices)
const char *html_button_dnes_apply2[POCET_JAZYKOV + 1] = {"Uloi", "Uloit", "Save", "___", "", "Uloit", "Alkalmaz"};
#ifndef HTML_BUTTON_DNES_APPLY_CHOICES
#define HTML_BUTTON_DNES_APPLY_CHOICES html_button_dnes_apply2[_global_jazyk]
#endif

// special button (today): Morning prayer with canticum of Zekariah
// doplnené, 2007-09-13
const char *html_button_ranne_chvaly_benediktus[POCET_JAZYKOV + 1] = {"Ranné chvály + Benediktus", "Ranní chvály + Zach. kantikum", "Morning prayer with Benedictus", "Laudes + Benedictus", "", "Ranní chvály + Zach. kantikum", "Reggeli dicséret Benedictusszal"};
#ifndef HTML_BUTTON_RANNE_CHVALY_BENEDIKTUS
#define HTML_BUTTON_RANNE_CHVALY_BENEDIKTUS	html_button_ranne_chvaly_benediktus[_global_jazyk]
#endif

// special button (today): Evening prayer with canticum of Mary
const char *html_button_vespery_magnifikat[POCET_JAZYKOV + 1] = {"Vešpery + Magnifikat", "Nešpory + Mariino kant.", "Vesperae + Magnificat", "Vesperae + Magnificat", "", "Veèerní chvály + kant. Panny Marie", "Esti dicséret Magnificattal"};
#ifndef HTML_BUTTON_VESPERY_MAGNIFIKAT
#define HTML_BUTTON_VESPERY_MAGNIFIKAT	html_button_vespery_magnifikat[_global_jazyk]
#endif

// special button (today): Completory prayer with canticum of Simeon; is currently used only in Slovak
// doplnené, 2008-12-20; nepouíva sa pre ostatné jazyky
const char *html_button_kompletorium_nunkdim[POCET_JAZYKOV + 1] = {"Kompletórium + Nunk dimittis", "xxx", "xxx", "xxx", "", "xxx", "hu_xxx"};
#ifndef HTML_BUTTON_KOMPLETORIUM_NUNKDIM
#define HTML_BUTTON_KOMPLETORIUM_NUNKDIM	html_button_kompletorium_nunkdim[_global_jazyk]
#endif

// html <title> element for generated pages
// doplnené, 2009-05-21
const char *html_title[POCET_JAZYKOV + 1] = {"Liturgia hodín", "Liturgie hodin", "Liturgy of Hours", "Liturgia horarum", "", "Liturgie hodin", "Az Imaórák Liturgiája"};
// 2009-08-04: upravené pre batch mód
// const char *html_title_batch_mode[POCET_JAZYKOV + 1] = {"Batch mód", "Dávkovı reim", "Batch mode", "la_", "", "Dávkovı reim", "Kötegelt mód"};
const char *html_title_batch_mode[POCET_JAZYKOV + 1] = {"Liturgia hodín - statické texty", "Liturgie hodin - statické texty", "Liturgy of Hours - static texts", "la_", "", "Liturgie hodin - statické texty", "Az Imaórák Liturgiája - állandó szövegek"};

// doplnené, 2011-05-16
const char *html_error_template[POCET_JAZYKOV + 1] = {"Šablóna pre modlitbu sa nenašla. Zrejme neexistuje súbor `%s'.", "Šablona pro modlitbu se nenašla. Patrnì neexistuje soubor `%s'.", "Template for prayer not found. File `%s' does not exist.", "Template for prayer not found. File `%s' does not exist.", "", "Šablona pro modlitbu se nenašla. Patrnì neexistuje soubor `%s'.", "Template for prayer not found. File `%s' does not exist."};

// navigation buttons/texts: previous, next, today
const char *html_button_predchadzajuci_[POCET_JAZYKOV + 1] = {"Predchádzajúci", "Pøedchozí", "Previous", "Praecedénte", "", "Pøedchozí", "Elõzõ"};
const char *html_button_nasledujuci_[POCET_JAZYKOV + 1] = {"Nasledujúci", "Následující", "Next", "Successívo", "", "Následující", "Következõ"};
const char *html_button_dnes[POCET_JAZYKOV + 1] = {"dnes", "dnes", "today", "hodie", "", "dnes", "ma"};
const char *html_button_Dnes[POCET_JAZYKOV + 1] = {"Dnes", "Dnes", "Today", "Hodie", "", "Dnes", "Ma"};
const char *html_button_hore[POCET_JAZYKOV + 1] = {"^ ", "^ ", "^ ", "^ ", "^ ", "^ ", "^ "};

const char *html_button_tento_den[POCET_JAZYKOV + 1] = {"tento deò", "tento den", "this day", "hodie", "", "tento den", "ez a nap"};

// basic words: day, month, year
const char *html_text_den[POCET_JAZYKOV + 1] = {"deò", "den", "day", "die", "", "den", "nap"};
const char *html_text_mesiac[POCET_JAZYKOV + 1] = {"mesiac", "mìsíc", "month", "mensis", "", "mìsíc", "hó"};
const char *html_text_rok[POCET_JAZYKOV + 1] = {"rok", "rok", "year", "anno", "", "rok", "év"};
const char *html_text_Rok[POCET_JAZYKOV + 1] = {"Rok", "Rok", "Year", "Anno", "", "Rok", "Év"};
// in the following: you MUST keep all %d, %c, %s etc. variables - these are replaced by numbers, characters, strings, etc. respectively
const char *html_text_Rok_x[POCET_JAZYKOV + 1] = {"Rok %d", "Rok %d", "Year %d", "Anno %d", "%d", "Rok %d", "Év %d"};

const char *html_text_zoznam_mesiacov[POCET_JAZYKOV + 1] = {"zoznam mesiacov", "seznam mìsícù", "list of months", "", "", "seznam mìsícù", "hónapok listája"};

const char *html_text_modlitba[POCET_JAZYKOV + 1] = {"modlitba", "modlitba", "prayer", "ora", "", "modlitba", "imádság"};
const char *html_text_modlitby_pre_den[POCET_JAZYKOV + 1] = {"modlitby pre deò", "modlitby pro den", "prayers for date", "", "", "modlitby pro den", ""};
const char *html_text_alebo_pre[POCET_JAZYKOV + 1] = {"alebo pre", "anebo pro", "or for", "vel per", "", "anebo pro", "vagy"};
const char *html_text_dnesok[POCET_JAZYKOV + 1] = {"dnešok", "dnešní den", "today", "hodie", "", "dnešní den", "a mai nap imaórái"};

// 2010-02-15: pridané kvôli "zoznam.htm" batch mode
const char *html_text_Breviar_dnes[POCET_JAZYKOV + 1] = {"Breviár dnes", "Breviáø dnes", "Breviary today", "Liturgia horarum hodie", "", "Breviáø dnes", "A mai nap imaórája"};
const char *html_text_Dnesne_modlitby[POCET_JAZYKOV + 1] = {"Dnešné modlitby", "Dnešní modlitby", "Today's prayers", "la_hodie", "", "Dnešní modlitby", "A mai nap imái"};
const char *html_text_Prehlad_mesiaca[POCET_JAZYKOV + 1] = {"Preh¾ad mesiaca", "Pøehled mìsíce", "Current month", "la_", "", "Pøehled mìsíce", "A hónap áttekintése"};
// 2011-03-18: pridané do "zoznam.htm" batch mode -- kalendáre a hlavnı nadpis
const char *html_text_batch_mode_h1[POCET_JAZYKOV + 1] = {"Liturgia hodín – Predgenerované modlitby", "Liturgie hodin – Pøedgenerované modlitby", "Liturgy of Hours – Pregenerated prayers", "la_", "", "Liturgie hodin – Pøedgenerované modlitby", "Az Imaórák Liturgiája – Elõre generált imák"};
const char *html_text_Kalendar[POCET_JAZYKOV + 1] = {"Kalendár", "Kalendáø", "Proprietary calendary", "Propria", "", "Kalendáø", "Naptár"};

const char *html_text_Vysvetlivky[POCET_JAZYKOV + 1] = 
{"Vysvetlivky", 
 "Vysvìtlivky", 
 "Legenda", 
 "Legenda", 
 "", 
 "Vysvìtlivky", 
 "Jelmagyarázat"};

const char *html_text_dalsie_moznosti[POCET_JAZYKOV + 1] = 
{"Vıber ïalších moností", 
 "Další monosti vıbìru ", 
 "Choose from above (buttons) or from the following options: ", 
 "", 
 "", 
 "Další monosti vıbìru", 
 "További lehetõségek választása:"};

const char *html_text_dalsie_moznosti_1[POCET_JAZYKOV + 1] = 
{"Nastavenia", 
 "Nastavení", 
 "Settings", 
 "", 
 "", 
 "Nastavení", 
 "Beállítások"};

const char *html_text_dalsie_moznosti_2[POCET_JAZYKOV + 1] = 
{"Ïalšie zobrazenia", 
 "Další zobrazení", 
 "Other options", 
 "", 
 "", 
 "Další zobrazení", 
 "Más megjelenítési lehetõségek"};

const char *html_text_prik_sviatky_atd[POCET_JAZYKOV + 1] = {"prikázané sviatky a slávnosti Pána v roku ", "zasvìcené svátky a slavnosti Pánì v roce ", "obligatory celebrations in year ", "", "", "zasvìcené svátky a slavnosti Pánì v roce", "kötelezõ ünnepek"};
const char *html_text_lit_kalendar[POCET_JAZYKOV + 1] = {"liturgickı kalendár pre", "liturgickı kalendáø pro", "liturgical calendar for", "", "", "liturgickı kalendáø pro", "liturgikus naptár"};
const char *html_text_roku[POCET_JAZYKOV + 1] = {"roku", "roku", "of year", "anno", "", "roku", ""};
const char *html_text_tabulka_pohyblive_od[POCET_JAZYKOV + 1] = {"tabu¾ka dátumov pohyblivıch slávení od roku", "tabulka s daty promìnnıch slavností od roku", "table with dates of movable celebrations from year", "", "", "tabulka s daty promìnnıch slavností od roku", "a mozgó (változó) ünnepek táblázata a következõ években"};
const char *html_text_do_roku[POCET_JAZYKOV + 1] = {"do roku", "po rok", "till year", "", "", "po rok", ""};
const char *html_text_zobrazit_linky[POCET_JAZYKOV + 1] = {"zobrazi tabu¾ku vrátane hypertextovıch odkazov na jednotlivé dni", "zobrazit tabulku s hypertextovımi odkazy pro jednotlivé dny", "display the table including hypertext links to each date", "", "", "zobrazit tabulku s hypertextovımi odkazy pro jednotlivé dny", "A táblázat megjelenítése az egyes napokhoz tartozó hiperhivatkozásokkal együtt."};
const char *html_text_pre_cezrocne_obd[POCET_JAZYKOV + 1] = {"pre cezroèné obdobie", "pro mezidobí", "for ...", "per annum", "", "pro dobu bìhem roku", ""};
const char *html_text_tyzden_zaltara_cislo[POCET_JAZYKOV + 1] = {"%d. tıdeò altára", "%d. tıden altáøe", "%d. week of Psaltary", "hebdomada %d psalterii", "%d", "%d. tıden altáøe", "%d. zsoltáros hét"};
const char *html_text_tyzden_cislo[POCET_JAZYKOV + 1] = {"%d. tıdeò", "%d. tıden", "%d. week", "hebdomada %d", "%d", "%d. tıden", "%d. hét"};
const char *html_text_tyzden[POCET_JAZYKOV + 1] = {". tıdeò", ". tıden", ". week", "hebdomada ", "", ". tıden", ". hét"};
const char *html_text_v_tyzdni_zaltara[POCET_JAZYKOV + 1] = {". tıdni altára", ". tıdnu altáøe", "week of Psaltary", "hebdomada", "", ". tıdnu altáøe", ". zsoltáros hét"};
const char *html_text_pre[POCET_JAZYKOV + 1] = {"pre", "pro", "for", "per", "", "pro", ""};
// in the following: you MUST keep all HTML elements, e.g. <a href...>, <br/> etc.
const char *html_text_dnes_je_atd[POCET_JAZYKOV + 1] = 
{"Dnes je %d. deò v roku%s, <a href=\"%s%s\">juliánsky dátum</a> JD = %ld%s.\n"HTML_LINE_BREAK"\n",
 "Dnes je %d. den v roku%s, <a href=\"%s%s\">juliánské datum</a> JD = %ld%s.\n"HTML_LINE_BREAK"\n",
 "Today is %d. day in the year%s, <a href=\"%s%s\">Julian date</a> JD = %ld%s.\n"HTML_LINE_BREAK"\n",
 "Hodie est %d. die anno %s, <a href=\"%s%s\">Iulianus datum</a> JD = %ld%s.\n"HTML_LINE_BREAK"\n",
 "%d/%s<a href=\"%s%s\">JD</a> = %ld%s.\n"HTML_LINE_BREAK"\n",
 "Dnes je %d. den v roku%s, <a href=\"%s%s\">juliánské datum</a> JD = %ld%s.\n"HTML_LINE_BREAK"\n",
 "Ma %s %d. napja van, <a href=\"%s%s\">Julián naptár</a> JD = %ld%s.\n"HTML_LINE_BREAK"\n"};

const char *html_text_alebo[POCET_JAZYKOV + 1] = {"alebo:", "nebo:", "or:", "", "", "nebo:", ""};

const char *html_text_zakladne_info[POCET_JAZYKOV + 1] = {"Základné informácie", "Základní informace", "Basic info", "__info__", "", "Základní informace", "Alapvetõ információk"};
const char *html_text_je[POCET_JAZYKOV + 1] = {"je", "je", "is", "est", "", "je", /* HU: van, ale nie pre prestupnı */ ""};
const char *html_text_nie_je[POCET_JAZYKOV + 1] = {"nie je", "není", "is not", "non est", "", "není", /* HU: nincs, ale nie pre prestupnı */ "nem"};
const char *html_text_prestupny[POCET_JAZYKOV + 1] = {"prestupnı", "pøestupnı", "...", "...", "", "pøestupnı", "szökõév"};
const char *html_text_datumy_pohyblivych_slaveni[POCET_JAZYKOV + 1] = {"Dátumy pohyblivıch slávení", "Dáta promìnlivıch slávení", "Dates for movable celebrations", "", "", "Data promìnlivıch slavení", "A mozgó (változó) ünnepek dátumai"};

const char *html_text_den_v_roku[POCET_JAZYKOV + 1] = {"%d. deò v roku", "%d. den v roce", "%d. day of the year", "%d. ", "%d. ", "%d. den v roce", "az év %d. napja"};

const char *html_text_zacina[POCET_JAZYKOV + 1] = {"zaèína", "zaèíná", "starts", "", "", "zaèíná", "kezdõdik"};
const char *html_text_liturgicky_rok[POCET_JAZYKOV + 1] = {"liturgickı rok", "liturgickı rok", "liturgical year", "anno liturgico", "", "liturgickı rok", "liturgikus év"};

const char *html_text_txt_export[POCET_JAZYKOV + 1] = {"Textovı vıstup: ", "Textovı vıstup: ", "Text export: ", "Text export:", "", "Textovı vıstup: ", "Text export: "};

const char *html_text_pohyblive1[POCET_JAZYKOV + 1] = {
	"<td "HTML_ALIGN_CENTER">Rok"HTML_LINE_BREAK"Pána</td>\n",
	"<td "HTML_ALIGN_CENTER">Léto"HTML_LINE_BREAK"Pánì</td>\n", 
	"<td "HTML_ALIGN_CENTER">Anno"HTML_LINE_BREAK"Domini</td>\n",
	"<td "HTML_ALIGN_CENTER">Anno"HTML_LINE_BREAK"Domini</td>\n",
	"",
	"<td "HTML_ALIGN_CENTER">Léto"HTML_LINE_BREAK"Pánì</td>\n",
	"<td "HTML_ALIGN_CENTER">Naptári"HTML_LINE_BREAK"év</td>\n"
};

const char *html_text_pohyblive2[POCET_JAZYKOV + 1] = {
	"<td "HTML_ALIGN_CENTER">Nede¾ná"HTML_LINE_BREAK"litera</td>\n",
	"<td "HTML_ALIGN_CENTER">Nedìlní"HTML_LINE_BREAK"písmeno</td>\n", 
	"<td "HTML_ALIGN_CENTER">Sunday"HTML_LINE_BREAK"Letter</td>\n",
	"<td "HTML_ALIGN_CENTER">Let."HTML_LINE_BREAK"Dom.</td>\n",
	"",
	"<td "HTML_ALIGN_CENTER">Nedìlní"HTML_LINE_BREAK"písmeno</td>\n",
	"<td "HTML_ALIGN_CENTER">Vasárnap"HTML_LINE_BREAK"betûje</td>\n"
};

const char *html_text_pohyblive3[POCET_JAZYKOV + 1] = {
	"<td "HTML_ALIGN_CENTER">Nede¾nı"HTML_LINE_BREAK"cyklus</td>\n",
	"<td "HTML_ALIGN_CENTER">Nedìlní"HTML_LINE_BREAK"cyklus</td>\n", 
	"<td "HTML_ALIGN_CENTER">Sunday"HTML_LINE_BREAK"cycle</td>\n",
	"<td "HTML_ALIGN_CENTER">Cycl."HTML_LINE_BREAK"Dom.</td>\n",
	"",
	"<td "HTML_ALIGN_CENTER">Nedìlní"HTML_LINE_BREAK"cyklus</td>\n",
	"<td "HTML_ALIGN_CENTER">Vasárnapi"HTML_LINE_BREAK"ciklus</td>\n"
};

const char *html_text_pohyblive3b[POCET_JAZYKOV + 1] = {
	"<td "HTML_ALIGN_CENTER">Zjavenie"HTML_LINE_BREAK"Pána</td>\n",
	"<td "HTML_ALIGN_CENTER">Zjevení"HTML_LINE_BREAK"Pánì</td>\n", 
	"<td "HTML_ALIGN_CENTER">Epiphany</td>\n",
	"<td "HTML_ALIGN_CENTER">Epiphania"HTML_LINE_BREAK"Domini</td>\n",
	"",
	"<td "HTML_ALIGN_CENTER">Zjevení"HTML_LINE_BREAK"Pánì</td>\n",
	"<td "HTML_ALIGN_CENTER">Urunk"HTML_LINE_BREAK"megjelenése"HTML_LINE_BREAK"(Vízkereszt)</td>\n"
};

const char *html_text_pohyblive4[POCET_JAZYKOV + 1] = {
	"<td "HTML_ALIGN_CENTER">Krst Krista"HTML_LINE_BREAK"Pána</td>\n",
	"<td "HTML_ALIGN_CENTER">Køest Krista"HTML_LINE_BREAK"Pánì</td>\n", 
	"<td "HTML_ALIGN_CENTER">Bapt. of"HTML_LINE_BREAK"the Lord</td>\n",
	"<td "HTML_ALIGN_CENTER">Bapt."HTML_LINE_BREAK"Domini</td>\n",
	"",
	"<td "HTML_ALIGN_CENTER">Køest Krista"HTML_LINE_BREAK"Pánì</td>\n",
	"<td "HTML_ALIGN_CENTER">Urunk"HTML_LINE_BREAK"megkeresztel-"HTML_LINE_BREAK"kedése</td>\n"
};

const char *html_text_pohyblive5[POCET_JAZYKOV + 1] = {
	"<td "HTML_ALIGN_CENTER"><a href=\"#explain\">OCR"HTML_LINE_BREAK"pred"HTML_LINE_BREAK"PO</a></td>\n",
	"<td "HTML_ALIGN_CENTER"><a href=\"#explain\">OCR"HTML_LINE_BREAK"pøed"HTML_LINE_BREAK"postem</a></td>\n", 
	"<td "HTML_ALIGN_CENTER">...</td>\n",
	"<td "HTML_ALIGN_CENTER">PA fest.</td>\n",
	"",
	"<td "HTML_ALIGN_CENTER"><a href=\"#explain\">OCR"HTML_LINE_BREAK"pøed"HTML_LINE_BREAK"postem</a></td>\n",
	"<td "HTML_ALIGN_CENTER">EK a HSZ elõtt</td>\n"
};

const char *html_text_pohyblive6[POCET_JAZYKOV + 1] = {
	"<td "HTML_ALIGN_CENTER">Popolcová"HTML_LINE_BREAK"streda</td>\n",
	"<td "HTML_ALIGN_CENTER">Popeleèní"HTML_LINE_BREAK"støeda</td>\n", 
	"<td "HTML_ALIGN_CENTER">...</td>\n",
	"<td "HTML_ALIGN_CENTER">...</td>\n",
	"",
	"<td "HTML_ALIGN_CENTER">Popeleèní"HTML_LINE_BREAK"støeda</td>\n",
	"<td "HTML_ALIGN_CENTER">Hamvazó-"HTML_LINE_BREAK"szerda</td>\n"
};

const char *html_text_pohyblive7[POCET_JAZYKOV + 1] = {
	"<td "HTML_ALIGN_CENTER">Ve¾ká"HTML_LINE_BREAK"noc</td>\n",
	"<td "HTML_ALIGN_CENTER">Veliko-"HTML_LINE_BREAK"noce</td>\n", 
	"<td "HTML_ALIGN_CENTER">Easter</td>\n",
	"<td "HTML_ALIGN_CENTER">Pascha</td>\n",
	"",
	"<td "HTML_ALIGN_CENTER">Veliko-"HTML_LINE_BREAK"noce</td>\n",
	"<td "HTML_ALIGN_CENTER">Húsvét</td>\n"
};

const char *html_text_pohyblive8[POCET_JAZYKOV + 1] = {
	"<td "HTML_ALIGN_CENTER">Nanebo-"HTML_LINE_BREAK"vstúpenie"HTML_LINE_BREAK"Pána</td>\n",
	"<td "HTML_ALIGN_CENTER">Nanebe-"HTML_LINE_BREAK"vstoupení"HTML_LINE_BREAK"Pánì</td>\n", 
	"<td "HTML_ALIGN_CENTER">...</td>\n",
	"<td "HTML_ALIGN_CENTER">...</td>\n",
	"",
	"<td "HTML_ALIGN_CENTER">Nanebe-"HTML_LINE_BREAK"vstoupení"HTML_LINE_BREAK"Pánì</td>\n",
	"<td "HTML_ALIGN_CENTER">Urunk"HTML_LINE_BREAK"menny-"HTML_LINE_BREAK"bemenetele</td>\n"
};

const char *html_text_pohyblive9[POCET_JAZYKOV + 1] = {
	"<td "HTML_ALIGN_CENTER">Zoslanie"HTML_LINE_BREAK"Ducha"HTML_LINE_BREAK"Svätého</td>\n",
	"<td "HTML_ALIGN_CENTER">Seslání"HTML_LINE_BREAK"Ducha"HTML_LINE_BREAK"Svatého</td>\n", 
	"<td "HTML_ALIGN_CENTER">...</td>\n",
	"<td "HTML_ALIGN_CENTER">...</td>\n",
	"",
	"<td "HTML_ALIGN_CENTER">Seslání"HTML_LINE_BREAK"Ducha"HTML_LINE_BREAK"Svatého</td>\n",
	"<td "HTML_ALIGN_CENTER">Pünkösd</td>\n"
};

const char *html_text_pohyblive10[POCET_JAZYKOV + 1] = {
	"<td "HTML_ALIGN_CENTER"><a href=\"#explain\">OCR"HTML_LINE_BREAK"po"HTML_LINE_BREAK"VN</a></td>\n",
	"<td "HTML_ALIGN_CENTER"><a href=\"#explain\">OCR"HTML_LINE_BREAK"po"HTML_LINE_BREAK"VN</a></td>\n", 
	"<td "HTML_ALIGN_CENTER">...</td>\n",
	"<td "HTML_ALIGN_CENTER">...</td>\n",
	"",
	"<td "HTML_ALIGN_CENTER"><a href=\"#explain\">OCR"HTML_LINE_BREAK"po"HTML_LINE_BREAK"VN</a></td>\n",
	"<td "HTML_ALIGN_CENTER">EK a HU után</td>\n"
};

const char *html_text_pohyblive11[POCET_JAZYKOV + 1] = {
	"<td "HTML_ALIGN_CENTER">Prvá"HTML_LINE_BREAK"adventná"HTML_LINE_BREAK"nede¾a</td>\n",
	"<td "HTML_ALIGN_CENTER">První"HTML_LINE_BREAK"adventní"HTML_LINE_BREAK"nedìle</td>\n", 
	"<td "HTML_ALIGN_CENTER">...</td>\n",
	"<td "HTML_ALIGN_CENTER">...</td>\n",
	"",
	"<td "HTML_ALIGN_CENTER">První"HTML_LINE_BREAK"adventní"HTML_LINE_BREAK"nedìle</td>\n",
	"<td "HTML_ALIGN_CENTER">Advent elsõ"HTML_LINE_BREAK"vasárnapja</td>\n"
};

const char *html_text_pohyblive12[POCET_JAZYKOV + 1] = {
	"<td "HTML_ALIGN_CENTER">Nede¾a Svätej"HTML_LINE_BREAK"rodiny</td></tr>\n",
	"<td "HTML_ALIGN_CENTER">Nedìle Svaté"HTML_LINE_BREAK"rodiny</td></tr>\n", 
	"<td "HTML_ALIGN_CENTER">...</td>\n",
	"<td "HTML_ALIGN_CENTER">...</td>\n",
	"",
	"<td "HTML_ALIGN_CENTER">Nedìle Svaté"HTML_LINE_BREAK"rodiny</td></tr>\n",
	"<td "HTML_ALIGN_CENTER">Szent"HTML_LINE_BREAK"Család"HTML_LINE_BREAK"ünnepe</td>\n"
};

const char *html_text_Nedelne_pismeno[POCET_JAZYKOV + 1] = {"Nede¾né písmeno", "Nedìlní písmeno", "Sunday letter", "", "", "Nedìlní písmeno", "A vasárnap betûje"};
const char *html_text_Nedelne_pismena[POCET_JAZYKOV + 1] = {"Nede¾né písmená", "Nedìlní písmena", "Sunday letters", "", "", "Nedìlní písmena", "A vasárnap betûje"};

const char *html_text_Od_prvej_adv_atd[POCET_JAZYKOV + 1] = {
	"Od prvej adventnej nedele v roku %d (%s) pokraèuje <a href=\"%s%s\">liturgickı rok</a> <"HTML_SPAN_BOLD">%c</span>.\n",
	"Od první nedìle adventní v roku %d (%s) pokraèuje <a href=\"%s%s\">liturgickı rok</a> <"HTML_SPAN_BOLD">%c</span>.\n",
	"From the 1st Advent Sunday in the year %d (%s) continues <a href=\"%s%s\">liturgical year</a> <"HTML_SPAN_BOLD">%c</span>.\n",
	"Od prvej adventnej nedele v roku %d (%s) pokraèuje <a href=\"%s%s\">liturgickı rok</a> <"HTML_SPAN_BOLD">%c</span>.\n",
	"",
	"Od první nedìle adventní v roce %d (%s) pokraèuje <a href=\"%s%s\">liturgickı rok</a> <"HTML_SPAN_BOLD">%c</span>.\n",
	"%d (%s) advent elsõ vasárnapjától az <"HTML_SPAN_BOLD">%c</span> <a href=\"%s%s\">liturgikus év</a> folytatódik.\n",
};

const char *html_text_Po_Velkej_noci_atd[POCET_JAZYKOV + 1] = {
	"Po Ve¾kej noci nasleduje %d. %s v cezroènom období.\n",
	"Po Velikonocích následuje %d. %s v mezibdobí.\n",
	"After Easter follows %d. %s per annum.\n",
	"Po Ve¾kej noci nasleduje %d. %s per annum.\n",
	"Po Ve¾kej noci nasleduje %d. %s v cezroènom období.\n", // v období „cez rok“
	"Po Velikonocích následuje %d. %s v mezibdobí.\n",
	"Húsvét után az évközi idõ %d. %sja következik.\n", // vasárnapja, nede¾a = vasárnap
};

const char *html_text_Prikazane_sviatky_v_roku[POCET_JAZYKOV + 1] = {
	"<p><"HTML_SPAN_RED">Prikázané sviatky v roku %s:</span>\n",
	"<p><"HTML_SPAN_RED">Pøikázané svátky v roce %s:</span>\n",
	"<p><"HTML_SPAN_RED">Obliged celebrations in the year %s:</span>\n",
	"<p><"HTML_SPAN_RED">Prikázané sviatky v roku %s:</span>\n",
	"<p><"HTML_SPAN_RED">Prikázané sviatky v roku %s:</span>\n",
	"<p><"HTML_SPAN_RED">Pøikázané svátky v roce %s:</span>\n",
	"<p><"HTML_SPAN_RED">%s kötelezõ ünnepei:</span>\n",
};

const char *html_text_Jednotlive_mesiace_roku[POCET_JAZYKOV + 1] = {
	"<"HTML_SPAN_RED">Jednotlivé mesiace roku %s:</span>\n",
	"<"HTML_SPAN_RED">Jednotlivé mìsíce v roce %s:</span>\n",
	"<"HTML_SPAN_RED">Individual months of the year %s:</span>\n",
	"<"HTML_SPAN_RED">Jednotlivé mesiace roku %s:</span>\n",
	"<"HTML_SPAN_RED">Jednotlivé mesiace roku %s:</span>\n",
	"<"HTML_SPAN_RED">Jednotlivé mìsíce v roce %s:</span>\n",
	"<"HTML_SPAN_RED">Egyes hónapok %s-ben(-ban):</span>\n",
};

const char *str_doplnkova_psalmodia[POCET_JAZYKOV + 1] = 
{"doplnková psalmódia", "almy z doplòovacího cyklu", "supplementary psalmody", "psalmodia complementaris", "", "doplnková psalmodie", "kiegészítõ zsoltárok" };

const char *str_modl_cez_den_zalmy_zo_dna[POCET_JAZYKOV + 1] = 
	{"benej psalmódie", "bìné psalmodie", "ordinary psalmody", "___", "", "bìné psalmodie", "soros zsoltárösszeállítást"};
#define		STR_MODL_CEZ_DEN_ZALMY_ZO_DNA 	str_modl_cez_den_zalmy_zo_dna[_global_jazyk]

const char *str_modl_cez_den_doplnkova_psalmodia[POCET_JAZYKOV + 1] = 
	{"doplnkovej psalmódie", "doplòovacího cyklu", "supplementary psalmody", "psalmodia complementaris", "", "doplòkové psalmodie", "kiegészítõ zsoltárok"};
#define		STR_MODL_CEZ_DEN_DOPLNKOVA_PSALMODIA 	str_modl_cez_den_doplnkova_psalmodia[_global_jazyk]

const char *str_modl_zalmy_zo_dna[POCET_JAZYKOV + 1] = 
	{"dòa", "dne", "day", "die", "", "dne", "naptól"};
#define		STR_MODL_ZALMY_ZO_DNA 	str_modl_zalmy_zo_dna[_global_jazyk]

const char *str_modl_zalmy_zo_sv[POCET_JAZYKOV + 1] = 
	{"sviatku", "svátku", "celebration", "___", "", "svátku", "ünneptõl"};
#define		STR_MODL_ZALMY_ZO_SV 	str_modl_zalmy_zo_sv[_global_jazyk]

#define STR_VALUE_TRUE  "1"
#define STR_VALUE_FALSE "0"
#define STR_VALUE_ZERO  "0"

const char *str_ano[POCET_JAZYKOV + 1] = 
	{"áno", "ano", "yes", "sic", "___", "ano", "igen"};
#define		STR_ANO		str_ano[_global_jazyk]

const char *str_nie[POCET_JAZYKOV + 1] = 
	{"nie", "ne", "no", "non", "___", "ne", "nem"};
#define		STR_NIE		str_nie[_global_jazyk]

const char *html_text_jazyk_android = "SK/CZ/HU:";

const char *html_text_jazyk[POCET_JAZYKOV + 1] = 
{"Jazyk:",
 "Jazyk:",
 "Language:",
 "Lingua:",
 "",
 "Jazyk:",
 "Nyelv:"
};

const char *html_text_jazyk_long[POCET_JAZYKOV + 1] = 
{"Liturgia hodín v jazyku:",
 "Liturgie hodin pro jazyk:",
 "Liturgy of hours in language:",
 "LH in lingua:",
 "",
 "Liturgie hodin pro jazyk:",
 ""
};

const char *html_text_jazyk_explain[POCET_JAZYKOV + 1] = 
{"Liturgia hodín pre inı jazyk.",
 "Liturgie hodin pro jinı jazyk.",
 "Liturgy of hours in other languages.",
 "LH in lingua...",
 "",
 "Liturgie hodin pro jinı jazyk.",
 ""
};

const char *html_text_detaily_uvod[POCET_JAZYKOV + 1] = 
{"Nasledovné monosti ovplyvnia vzh¾ad i obsah vygenerovanej modlitby.\nVyberte tie monosti, pod¾a ktorıch sa má modlitba vygenerova.", 
 "Následující monosti mají vliv na vzhled i obsah vygenerované modlitby.\nVyberte si monosti, podle kterıch má bıt modlitba vygenerována.", 
 "The following options apply to the resulting generated text of the prayer.\nChoose options which fit your needs to the resulting prayer text.", 
 "",
 "",
 "Následující monosti mají vliv na vzhled i obsah vygenerované modlitby.\nVyberte si monosti, podle kterıch má bıt modlitba vygenerována.",
 "Ez a választási lehetõség befolyásolja a megszerkesztett ima megjelenítését és tartalmát.\nVálassz a szerkeszthetõ lehetõségek közül."
};

const char *html_text_option1_kalendar[POCET_JAZYKOV + 1] = 
{"nastavenia pre liturgickı kalendár",
 "volby pro liturgickı kalendáø",
 "options for liturgical calendar",
 "", 
 "", 
 "volby pro liturgickı kalendáø",
 "a liturgikus naptár beállításai"
};

const char *html_text_option1_kalendar_explain[POCET_JAZYKOV + 1] = 
{"Liturgia hodín ponúka monos slávenia niektorıch slávení dvojakım spôsobom; závisí od danej krajiny, ako rozhodla príslušná konferencia biskupov.",
 "Volby pro liturgickı kalendáø ovlivòují datumy nìkterıch slavení.",
 "Options for liturgical calendar...",
 "", 
 "", 
 "Volby pro liturgickı kalendáø ovlivòují datumy nìkterıch slavení.",
 "Az Imaórák liturgiája megadja a lehetõséget, hogy némely ünnepek kétféle képen legyenek megünnepelve; az adott országtól függ, ahogy az adott püspöki konferencia döntött."
};

const char *html_text_option1_nemenne_sucasti[POCET_JAZYKOV + 1] = 
{"zobrazi nasledovné súèasti modlitby?",
 "zobrazit <i>nemìnné souèásti</i> modlitby?",
 "display <i>non-changeable parts</i> prayer?",
 "", 
 "", 
 "zobrazit <i>nemìnné souèásti</i> modlitby?",
 "jelenjenek meg az imaóra következõ elemei:"
};

const char *html_text_option1_nemenne_sucasti_explain[POCET_JAZYKOV + 1] = 
{"Kadé ranné chvály obsahujú Benediktus, vešpery Magnifikat, obe modlitby obsahujú Otèenáš a zakonèenie modlitby, a napokon posvätné èítanie obsahuje niekedy hymnus Te Deum; tieto èasti modlitby mono zobrazi alebo skry.", 
 "Kadé ranní chvály obsahují Zachariášovo kantikum, nešpory Mariin Magnifikat, obì modlitbu Pánì a zakonèení modlitby, a koneènì modlitba se ètením nìkdy obsahuje hymnus Te Deum; tyto èásti modliteb je moné zobrazit/skrıt.", 
 "Each morning prayer contains Benedictus, vesperae contains Magnificat, both contain the Lord's Prayer and a conclusion of the prayer; finally, the holy reading sometimes contains the Te Deum hymnus; all these parts can be shown/hidden.", 
 "",
 "", 
 "Kadé ranní chvály obsahují Zachariášovo kantikum, veèerní chvály kantikum Panny Marie, obì modlitbu Pánì a zakonèení modlitby, a koneènì modlitba se ètením nìkdy obsahuje hymnus Te Deum; tyto èásti je moné zobrazit/skrıt.",
 ""
};

const char *html_text_option1_dalsie_prepinace[POCET_JAZYKOV + 1] = 
{"monosti pre vısledné modlitby",
 "monosti pro vısledné modlitby",
 "options for generated prayers",
 "", 
 "", 
 "monosti pro vısledné modlitby",
 "egyéb választási lehetõségek:"
};

const char *html_text_option1_dalsie_prepinace_explain[POCET_JAZYKOV + 1] = 
{"Rozlièné monosti/vıbery pre vısledné modlitby.", 
 "", 
 "", 
 "",
 "", 
 "",
 ""
};

const char *html_text_zalmy_brat_zo[POCET_JAZYKOV + 1] = 
{"almy poui zo ", 
 "almy pouít ze ", 
 "take psalmody from ", 
 "", 
 "", 
 "almy pouít ze ",
 "zsoltárok a következõ helyrõl:"
};
const char *html_text_zalmy_brat_zo_okrem_mcd[POCET_JAZYKOV + 1] = 
{" (okrem modlitby cez deò)\n", 
 " (kromì modlitby pøes den)\n", 
 " (excluding the prayers during the day)\n", 
 "", 
 "", 
 " (kromì modlitby bìhem dne)\n",
 " (a Napközi imát kivéve)"
};

const char *html_text_spol_casti_vziat_zo[POCET_JAZYKOV + 1] = 
{"èasti modlitby zo spoloènej èasti ", 
 "èásti modlitby ze spoleènıch textù ", 
 "parts of prayer from the common part ", 
 "",
 "",
 "èásti modlitby ze spoleèné èásti ",
 "a közös részbõl"};
const char *html_text_spol_casti_vziat_zo_explain[POCET_JAZYKOV + 1] = 
{"Na sviatok svätca/svätice sa pod¾a liturgickıch pravidiel berú èasti, ktoré sa nenachádzajú vo vlastnej èasti altára, zo spoloènej èasti sviatku, niekedy je monos vybra si z viacerıch spoloènıch èastí; naviac je monos modli sa tieto èasti zo všedného dòa.", 
 "Na svátek ke cti svìtce/svìtice se podle liturgickıch pravidel berou èásti, které se nenachází ve vlastních textech, ze spoleènıch textù, nìkdy je moné vybrat si z více spoleènıch textù; navíc je monost modlit se tyto èásti ze všedního dne.", 
 "", 
 "",
 "",
 "O svátku ke cti svìtce/svìtice se podle liturgickıch pravidel berou èásti, které se nenachází ve vlastních textech, ze spoleènıch textù, nìkdy je moné vybrat si z více spoleènıch textù; navíc je monost modlit se tyto èásti ze všedního dne.",
 "A szentek ünnepén, a liturgikus elõírások szerint, azok az ima részek, amelyek nem találhatók meg a zsolozsma saját részében,  tetszés szerint vehetõk vagy a  közös részbõl, néha több közös részbõl lehet választani, vagy a köznapról."
};

const char *html_text_option0_specialne[POCET_JAZYKOV + 1] = 
{"v texte modlitieb zobrazi",
 "v textu modliteb zobrazit",
 "in the text of prayers display",
 "",
 "",
 "v textu modliteb zobrazit",
 "az imaóra szövegében jelenjen meg:"
};

const char *html_text_option0_specialne_explain[POCET_JAZYKOV + 1] = 
{"Monos zobrazi ïalšie údaje v texte modlitieb (èísla veršov, referencie a pod.).",
 "",
 "",
 "",
 "",
 "",
 ""
};

const char *html_text_option0_verse[POCET_JAZYKOV + 1] = 
{"èíslovanie (èísla) veršov",
 "èíslování veršù",
 "verse numbering",
 "verse numbers",
 "",
 "èíslování veršù",
 "a versek száma"
};

const char *html_text_option0_verse_explain[POCET_JAZYKOV + 1] = 
{"Liturgia hodín (latinské typické vydanie) zobrazuje èíslovanie veršov v rámci almu, chválospevu alebo dlhšieho biblického èítania; niektoré vydania tieto èísla veršov neuvádzajú.", 
 "Liturgie hodin uvádí jako horní indexy èísla veršù biblickıch textù (almù, chvalozpìvù a prvních ètení), které mùe program zobrazit.", 
 "xxx", 
 "",
 "", 
 "Liturgie hodin uvádí jako horní indexy èísla veršù biblickıch textù (almù, chvalozpìvù a prvních ètení), které mùe program zobrazit.", 
 "Az imaórák liturgiája (latin tipikus kiadás) megjeleníti a zsoltárokban, kantikumokban és hosszabb szentírási olvasmányokban a versek számozását. Egyes kiadások e számozást nem tartalmazzák."
};

const char *html_text_option0_referencie[POCET_JAZYKOV + 1] = 
{"biblické odkazy na dkc.kbs.sk",
 "biblické odkazy",
 "biblical references",
 "Bible references",
 "",
 "biblické odkazy",
 "Bibliai hivatkozások a szentiras.hu oldalon"
};

const char *html_text_option0_referencie_explain[POCET_JAZYKOV + 1] = 
{"Všetky biblické odkazy (napr. Jn 3, 16) v modlitbe budú aktívnymi odkazmi na text katolíckeho prekladu Biblie na adrese dkc.kbs.sk.", 
 "", 
 "", 
 "",
 "", 
 "", 
 "Az imák szövegében minden bibliai utalás (például Jn 3, 16) aktív linkként a szentiras.hu katolikus bibliafordításának megfellõ részére mutat. (A Szent István Társulat fordítását használjuk.)"
};

const char *html_text_option0_citania[POCET_JAZYKOV + 1] = 
{"liturgické èítania",
 "liturgická ètení",
 "liturgical readings",
 "liturgical readings",
 "",
 "liturgická ètení",
 "liturgikus olvasmányok"
};

const char *html_text_option0_citania_explain[POCET_JAZYKOV + 1] = 
{"Zobrazí odkaz na liturgické èítania (lc.kbs.sk).", 
 "Zobrazí odkaz na liturgická ètení (katolik.cz).", 
 "", 
 "",
 "", 
 "Zobrazí odkaz na liturgická ètení (katolik.cz).", 
 "Liturgikus olvasmányok (katolikus.hu)."
};

const char *html_text_option0_zjv_ne[POCET_JAZYKOV + 1] = 
{"Zjavenie Pána slávi v nede¾u medzi 2. a 8. januárom",
 "Zjevení Pánì slavit v nedìli mezi 2. a 8. lednem",
 "",
 "",
 "",
 "Zjevení Pánì slavit v nedìli mezi 2. a 8. lednem",
 "Urunk megjelenése (Vízkereszt) megünneplése vasárnap, január 2. és 8. között"
};

const char *html_text_option0_zjv_ne_explain[POCET_JAZYKOV + 1] = 
{"Zjavenie Pána sa slávi dòa 6. januára; v niektorıch krajinách sa slávi v nede¾u medzi 2. a 8. januárom.", 
 "", 
 "", 
 "",
 "", 
 "", 
 "Urunk megjelenése (Vízkereszt) január 6.-án van; egyes országokban azonban vasárnap, január 2. és 8. között ünneplik."
};

const char *html_text_option0_nan_ne[POCET_JAZYKOV + 1] = 
{"Nanebovstúpenie Pána slávi v nede¾u",
 "Nanebevstoupení Pánì slavit v nedìli",
 "",
 "",
 "",
 "Nanebevstoupení Pánì slavit v nedìli",
 "Urunk mennybemenetelét vasárnap ünnepelni"
};

const char *html_text_option0_nan_ne_explain[POCET_JAZYKOV + 1] = 
{"Nanebovstúpenie Pána sa slávi 40. deò po Ve¾kej noci (teda vo štvrtok); v niektorıch krajinách sa slávenie prekladá na najblišiu nede¾u (nahrádza 7. ve¾konoènú nede¾u).", 
 "", 
 "", 
 "",
 "", 
 "", 
 "Urunk mennybemenetele húsvét után a 40. napon van (tehát csütörtökön); egyes országokban azonban a legközelebbi vasárnapon ünneplik (vagyis Húsvét 7. vasárnapján)."
};

const char *html_text_option0_tk_ne[POCET_JAZYKOV + 1] = 
{"Najsv. Kristovho tela a krvi slávi v nede¾u",
 "Tìla a krve Pánì slavit v nedìli",
 "",
 "",
 "",
 "Tìla a krve Pánì slavit v nedìli",
 "Krisztus Szent Teste és Vére ünnepe vasárnapra téve"
};

const char *html_text_option0_tk_ne_explain[POCET_JAZYKOV + 1] = 
{"Najsv. Kristovho tela a krvi sa slávi 11. deò po Zoslaní Ducha Svätého (teda vo štvrtok po Najsv. Trojici); v niektorıch krajinách sa slávenie prekladá na najblišiu nede¾u.", 
 "", 
 "", 
 "",
 "", 
 "", 
 "Krisztus Szent Teste és Vére Pünkösd után a 11. napon van (tehát Szentháromság utáni csütörtökön); egyes országokban azonban a legközelebbi vasárnapon ünneplik."
};

const char *html_text_option0_font_normal[POCET_JAZYKOV + 1] = 
{"všade poui obyèajné písmo (nie tuèné)",
 "všude pouít obyèejné písmo (ne tuèné)",
 "force normal font weight (no bold)",
 "",
 "",
 "všude pouít obyèejné písmo (ne tuèné)",
 "normál betûtípus használata (félkövér helyett)"
};

const char *html_text_option0_font_normal_explain[POCET_JAZYKOV + 1] = 
{"Liturgia hodín pouíva tuèné písmo pre texty, ktoré sa priamo èítajú, a tie aj pre niektoré medzinadpisy. Táto vo¾ba potlaèí pouitie tuèného písma.", 
 "", 
 "", 
 "",
 "", 
 "", 
 ""
};

const char *html_text_option0_buttons_order[POCET_JAZYKOV + 1] = 
{"dátumové navigaèné tlaèidlá zobrazi a pod tlaèidlami pre modlitby",
 "navigaèní tlaèítka pro datum zobrazit a pod tlaèítky pro modlitby",
 "date buttons display after buttons for prayers",
 "",
 "",
 "navigaèní tlaèítka pro datum zobrazit a pod tlaèítky pro modlitby",
 "a dátum gombokat az imákra vonatkozó gombok után mutatni"
};

const char *html_text_option0_buttons_order_explain[POCET_JAZYKOV + 1] = 
{"Liturgia hodín pouíva tuèné písmo pre texty, ktoré sa priamo èítajú, a tie aj pre niektoré medzinadpisy. Táto vo¾ba potlaèí pouitie tuèného písma.", 
 "", 
 "", 
 "",
 "", 
 "", 
 ""
};

const char *html_text_option1_chvalospevy[POCET_JAZYKOV + 1] = 
{"evanjeliové chválospevy (Benediktus, Magnifikat, Nunk dimittis)", 
 "evangelijní kantika (Mariino, Zachariášovo, Simeonovo)", 
 "Gospel canticles (Benedictus, Magnificat, Nunc dimittis)", 
 "",
 "",
 "evangelijní chvalozpìvy (Benedictus, Magnificat, Nunc dimittis)", 
 "evangéliumi kantikumok (Benedictus, Magnificat, Nunc dimittis)"
};
const char *html_text_option1_chvalospevy_explain[POCET_JAZYKOV + 1] = 
{"Liturgia hodín štandardne tieto evanjeliové chválospevy neuvádza.", 
 "Liturgie hodin evangelijní kantika v plném znìní obvykle neuvádí.", 
 "", 
 "",
 "", 
 "Liturgie hodin evangelijní chvalozpìvy v plném znìní obvykle neuvádí.", 
 "Az imaórák liturgiája ezeket az evangéliumi kantikumokat alaphelyzetben nem mutatja."
};

const char *html_text_option1_slava_otcu[POCET_JAZYKOV + 1] = 
{"Sláva Otcu" /*[na konci almov a chválospevov]*/, 
 "Sláva Otci" /*[na konci almù a kantik]*/, 
 "Glory to the Father" /*at the end of psalms and canticles]*/, 
 "",
 "",
 "Sláva Otci" /*[na konci almù a chvalozpìvù]*/, 
 "Dicsõség az Atyának" /*[a zsoltárok és kantikumok végén]*/
};
const char *html_text_option1_slava_otcu_explain[POCET_JAZYKOV + 1] = 
{"Liturgia hodín štandardne Sláva Otcu na konci almov a chválospevov neuvádza.", 
 "Liturgie hodin modlitbu Sláva Otci na konci almù a chvalozpìvù neuvádí.", 
 "", 
 "",
 "", 
 "Liturgie hodin modlitbu Sláva Otci na konci almù a chvalozpìvù neuvádí.", 
 "Az imaórák liturgiája a Dicsõség az Atyának ... dicsõítõ verset a zsoltárok és kantikumok végén alaphelyzetben nem mutatja."
};

const char *html_text_option1_rubriky[POCET_JAZYKOV + 1] = 
{"rubriky" /*(napr. závereèné poehnanie)*/, 
 "rubriky" /*(napø. závìreèné poehnání)*/, 
 "rubrics", 
 "",
 "",
 "rubriky" /*(napø. závìreèné poehnání)*/, 
 "rubrikák" /*(pl. záró áldás)*/
};
const char *html_text_option1_rubriky_explain[POCET_JAZYKOV + 1] = 
{"Liturgia hodín zobrazuje èervenım písmom rozlièné zvyèajne vysvet¾ujúce pokyny k modlitbe (pod¾a Všeobecnıch smerníc o LH).", 
 "Liturgie hodin uvádí èervenım písmem rozlièné pokyny k modlitbì (èasto podle Všeobecnıch pokynù k denní modlitbì církve).", 
 "", 
 "",
 "", 
 "Liturgie hodin uvádí èervenım písmem rozlièné pokyny k modlitbì (èasto podle Všeobecnıch pokynù k denní modlitbì Církve).", 
 "Az imaórák liturgiája piros betûvel különbözõ többnyire magyarázó vagy az imaórát (az „Általános rendelkezések Az imaórák liturgiájáról“ szerint) szabályozó szövegeket jelenít meg. Alaphelyzetben nem mutatja."
};

const char *html_text_option1_otcenas[POCET_JAZYKOV + 1] = 
{"modlitba Pána (Otèenáš)", 
 "modlitba Pánì (Otèenáš)", 
 "Lord's Prayer (Our Father)", 
 "",
 "",
 "modlitba Pánì (Otèenáš)", 
 "az Úr imádsága (Miatyánk)"
};
const char *html_text_option1_otcenas_explain[POCET_JAZYKOV + 1] = 
{"Liturgia hodín štandardne modlitbu Pána (Otèenáš) v rannıch chválach a vešperách v plnom znení neuvádza.", 
 "Liturgie hodin modlitbu Pánì (Otèenáš) na pøíslušnıch místech v plném znìní neuvádí.", 
 "", 
 "",
 "", 
 "Liturgie hodin modlitbu Pánì (Otèenáš) na pøíslušnıch místech v plném znìní neuvádí.", 
 "Az imaórák liturgiája az Úr imádságát (Miatyánkot) a Reggeli és Esti dicséretben alaphelyzetben nem mutatja."
};

const char *html_text_option1_tedeum[POCET_JAZYKOV + 1] = 
{"hymnus Te Deum", 
 "hymnus Te Deum", 
 "hymnus Te Deum", 
 "",
 "",
 "hymnus Te Deum", 
 "Téged, Isten, dicsérünk ... himnusz"
};
const char *html_text_option1_tedeum_explain[POCET_JAZYKOV + 1] = 
{"Liturgia hodín hymnus Te Deum v posvätnom èítaní v plnom znení neuvádza.", 
 "Liturgie hodin hymnus Te Deum na pøíslušnıch místech v plném znìní neuvádí.", 
 "", 
 "",
 "", 
 "Liturgie hodin hymnus Te Deum na pøíslušnıch místech v plném znìní neuvádí.", 
 "Az imaórák liturgiája a Téged, Isten, dicsérünk ... himnuszt az Olvasmányos imaórában alaphelyzetben nem mutatja."
};

const char *html_text_option1_plne_resp[POCET_JAZYKOV + 1] = 
{"plné znenie responzórií pre posvätné èítania", 
 "plné znìní krátkıch zpìvù v modlitbì se ètením", 
 "", 
 "",
 "",
 "plné znìní responsorií v modlitbì se ètením", 
 "a válaszos énekek teljes szövege"
};
const char *html_text_option1_plne_resp_explain[POCET_JAZYKOV + 1] = 
{"Liturgia hodín responzóriá po èítaniach v posvätnom èítaní v plnom znení neuvádza (druhá, opakujúca sa èas, je v tlaèenej LH skrátená).", 
 "Liturgie hodin responsoria po èteních v modlitbe se ètením neuvádí v druhé, opakující se èásti, plné znìní.", 
 "", 
 "",
 "", 
 "Liturgie hodin responsoria po èteních v modlitbe se ètením neuvádí v druhé, opakující se èásti, plné znìní.", 
 "Az Imaórák Liturgiája az olvasmányos imaórák válaszos énekeinek teljes szövegét nem mutatja (a második ismétlõdõ rész nyomtatott kiadásban rövidített)."
};

const char *html_text_option_zobrazit[POCET_JAZYKOV + 1] = 
{"zobrazi", 
 "zobrazit", 
 "xxx", 
 "show",
 "",
 "zobrazit", 
 "megmutatni"
};
const char *html_text_option_skryt[POCET_JAZYKOV + 1] = 
{"skry", 
 "skrıt", 
 "xxx", 
 "hide",
 "",
 "skrıt", 
 "elrejtés"
};

const char *html_text_option1_mcd_zalmy_nie_ine_short[POCET_JAZYKOV + 1] = 
{"poui psalmódiu zo dòa", 
 "pouít almy z bìného dne", 
 "xxx", 
 "psalmodia from ordinary day",
 "",
 "pouít psalmodii z bìného dne", 
 "az adott napi zsoltározást venni"
};
const char *html_text_option1_mcd_zalmy_nie_ine[POCET_JAZYKOV + 1] = 
{"pre modlitbu cez deò poui psalmódiu zo dòa", 
 "pro modlitbu uprostøed dne pouít almy z bìného dne", 
 "xxx", 
 "psalmodia from ordinary day",
 "",
 "pro modlitbu uprostøed dne pouít psalmodii z bìného dne", 
 "a Napközi imaórában az adott napi zsoltározást venni"
};
const char *html_text_option1_mcd_zalmy_ine_short[POCET_JAZYKOV + 1] = 
{"poui doplnkovú psalmódiu", 
 "pouít almy z doplòovacího cyklu", 
 "xxx", 
 "supplementary psalmodia",
 "",
 "dne pouít doplòkovou psalmodii", 
 "a kiegészítõ zsoltárokat venni"
};
const char *html_text_option1_mcd_zalmy_ine[POCET_JAZYKOV + 1] = 
{"pre modlitbu cez deò poui doplnkovú psalmódiu", 
 "pro modlitbu uprostøed dne pouít almy z doplòovacího cyklu", 
 "xxx", 
 "supplementary psalmodia",
 "",
 "pro modlitbu uprostøed dne pouít doplòkovou psalmodii", 
 "a Napközi imaórában a kiegészítõ zsoltárokat venni"
};
const char *html_text_option1_mcd_zalmy_ine_explain[POCET_JAZYKOV + 1] = 
{"Pokia¾ sa niekto modlí viac modlitieb cez deò, v prvej vezme benú psalmódiu; v ostatnıch sa pouije doplnková psalmódia. Zahàòa 3 série tzv. graduálnych almov ( 120 – 129).", 
 "Doplòovací cyklus almù obsahuje 3 série tzv. graduálních almù ( 120 – 129), které je mono pouít místo almù ze altáøe.", 
 "", 
 "",
 "", 
 "Doplòovací cyklus almù obsahuje 3 série tzv. graduálních almù ( 120 – 129), které je mono pouít místo almù ze altáøe.", 
 "Aki több Napközi imaórát mond, az egyik imaórában a soros zsoltárösszeállítást veszi, a többin a kiegészítõt. Ez az úgynevezett „zarándokzsoltárokból“ vett három-három zsoltárból áll (Zsolt 119 – 127)."
};

const char *html_text_option1_mcd_zalmy_nie_tri_short[POCET_JAZYKOV + 1] = 
{"poui psalmódiu z daného tıdòa altára pre všetky tri modlitby cez deò", 
 "pouít almy daného tıdne ze altáøe pro všechny tøi modlitby uprostøed dne", 
 "", 
 "",
 "",
 "pouít psalmodii daného tıdne ze altáøe pro všechny tøi modlitby uprostøed dne", 
 "az adott hét zsoltározását alkalmazni mindhárom napközi imánál"
};
const char *html_text_option1_mcd_zalmy_nie_tri[POCET_JAZYKOV + 1] = 
{"pre modlitbu cez deò poui psalmódiu z daného tıdòa altára pre všetky tri modlitby cez deò", 
 "pro modlitbu uprostøed dne pouít almy daného tıdne ze altáøe pro všechny tøi modlitby bìhem dne", 
 "", 
 "",
 "",
 "pro modlitbu uprostøed dne pouít psalmodii daného tıdne ze altáøe pro všechny tøi modlitby bìhem dne", 
 "a Napközi imaórában az adott hét zsoltározását alkalmazni mindhárom napközi imánál"
};
const char *html_text_option1_mcd_zalmy_tri_short[POCET_JAZYKOV + 1] = 
{"poui psalmódiu z troch tıdòov altára: aktuálny, predchádzajúci, nasledujúci", 
 "pouít almy z tøí tıdnù ze altáøe: aktuální, pøedchozí, následující", 
 "", 
 "",
 "",
 "pouít psalmodii z tøí tıdnù ze altáøe: aktuální, pøedchozí, následující", 
 "a három heti [aktuális, elõzõ, következõ] zsoltározást alkalmazni"
};
const char *html_text_option1_mcd_zalmy_tri[POCET_JAZYKOV + 1] = 
{"pre modlitbu cez deò poui psalmódiu z troch tıdòov altára (aktuálny, predchádzajúci, nasledujúci)", 
 "pro modlitbu uprostøed dne pouít almy z tøí tıdnù ze altáøe (aktuální, pøedchozí, následující)", 
 "", 
 "for prayer during the day use psalmody from three weeks of psalter (current, previous, next)",
 "",
 "pro modlitbu uprostøed dne pouít psalmodii z tøí tıdnù ze altáøe (aktuální, pøedchozí, následující)", 
 "a Napközi imaórában a három heti (aktuális, elõzõ, következõ) zsoltározást alkalmazni"
};
const char *html_text_option1_mcd_zalmy_tri_explain[POCET_JAZYKOV + 1] = 
{"Pokia¾ sa niekto modlí viac modlitieb cez deò, psalmódia sa pouíva z troch tıdòov altára (aktuálny, predchádzajúci, nasledujúci tıdeò altára).\nNemá úèinok, ak je zvolená monos poui doplnkovú psalmódiu.", 
 "Pokud se nìkdo modlí více èástí modlitby uprostøed dne, mùe nejprve pouít psalmodii daného dne a potom psalmodii pøedchozího, nebo následujícího tıdne.", 
 "", 
 "",
 "", 
 "Pokud se nìkdo modlí více èástí modlitby uprostøed dne, mùe nejprve pouít psalmodii daného dne a potom psalmodii pøedchozího, nebo následujícího tıdne.", 
 "Ha valaki többször naponta mondja a napközi imát, a zsoltározás három hétbõl (aktuális, elõzõ, következõ) van alkalmazva.\nNincs hatása, ha ki van választva a kiegészítõ zsoltárok alkalmazása."
};

const char *html_text_option1_zalm95[POCET_JAZYKOV + 1] = 
{"namiesto almov 24, 67 resp. 100 poui alm 95", 
 "místo almù 24, 67 resp. 100 pouít alm 95", 
 "xxx", 
 "psalm 95",
 "",
 "místo almù 24, 67 resp. 100 pouít alm 95", 
 "a 23., 66. illetve a 99.  zsoltár helyett legyen a 94."
};
const char *html_text_option1_zalm95_explain[POCET_JAZYKOV + 1] = 
{"Ak sa v rannıch chválach, vešperách alebo posvätnom èítaní vyskytne alm 24, 67 resp. 100, ktorı bol pouitı pre invitatórium, nahradí sa v príslušnej modlitbe almom 95.", 
 "Kdy se v ranních chválách, modlitbì se ètením nebo nešporách vyskytne alm 24, 67 resp. 100, kterı se pouil pro uvedení do první modlitby dne, nahradí se v pøíslušné modlitbì almem 95.", 
 "xxx", 
 "xxx",
 "xxx", 
 "Kdy se v ranních chválách, modlitbì se ètením nebo veèerních chválách vyskytne alm 24, 67 resp. 100, kterı se pouil pro invitatorium, nahradí se v pøíslušné modlitbì almem 95.", 
 "Ha a reggeli és az esti dicséretben, vagy az olvasmányos imaórában elõfordul a 23., 66. illetve 99. zsoltár, amely az Imádságra hívásban már imádkozva volt, akkor az adott imádságban a 94. zsoltár kerül helyébe."
};

const char *html_text_option_zobrazit_zvolania[POCET_JAZYKOV + 1] = 
{"opakova zvolanie po kadej prosbe", 
 "zopakovat zvolání po kadé prosbì", 
 "xxx", 
 "repeat invocation after each appeal",
 "",
 "zopakovat zvolání po kadé prosbì", 
 "megismételni a választ minden könyörgés után"
};
const char *html_text_option_skryt_zvolania[POCET_JAZYKOV + 1] = 
{"skry zvolanie po kadej prosbe", 
 "skrıt zvolání po kadé prosbì", 
 "xxx", 
 "hide invocation after each appeal",
 "",
 "skrıt zvolání po kadé prosbì", 
 "elrejteni a választ minden könyörgés után"
};

const char *html_text_option_zobrazit_kratsie_prosby[POCET_JAZYKOV + 1] = 
{"poui kratšie prosby z dodatku", 
 "zobrazit kratší prosby z dodatku", 
 "xxx", 
 "use shorten prayers",
 "",
 "zobrazit kratší prosby z dodatku", 
 "használja a rövidebb könyörgéseket a függelékbõl"
};
const char *html_text_option_skryt_kratsie_prosby[POCET_JAZYKOV + 1] = 
{"nepoui kratšie prosby z dodatku", 
 "nezobrazit kratší prosby z dodatku", 
 "xxx", 
 "do not use shorten prayers",
 "",
 "nezobrazit kratší prosby z dodatku", 
 "ne használja a rövidebb könyörgéseket a függelékbõl"
};

const char *html_text_option1_prosby_zvolanie[POCET_JAZYKOV + 1] = 
{"zvolanie v prosbách opakova po kadej prosbe", 
 "zvolání v prosbách zopakovat po kadé prosbì", 
 "xxx", 
 "invocation repeat after each appeal",
 "",
 "zvolání v prosbách zopakovat po kadé prosbì", 
 "minden fohász után ismételni a választ"
};
const char *html_text_option1_prosby_zvolanie_explain[POCET_JAZYKOV + 1] = 
{"V rannıch chválach a vešperách opakova zvolanie v prosbách po kadej prosbe.", 
 "V ranních chválách a nešporách opakovat svolání v prosbách po kadé prosbì.", 
 "xxx", 
 "In morning and evening prayer repeat invocation after each appeal.",
 "xxx", 
 "V ranních a veèerních chválách opakovat svolání v prosbách po kadé prosbì.", 
 "A reggeli és az esti dicséretben minden fohász után ismételni a választ."
};

const char *html_text_option1_skryt_popis_svaty[POCET_JAZYKOV + 1] = 
{"nezobrazi popis k modlitbe svätého", 
 "nezobrazit popis pøi modlitbì ke cti svìtce", 
 "do not display description for prayer for the saints", 
 "", 
 "", 
 "nezobrazit popis pøi modlitbì ke cti svìtce",
 "a szent imaórájában ne mutatkozzon leírás"
};

const char *html_text_option1_skryt_popis_svaty_explain[POCET_JAZYKOV + 1] = 
{"Modlitby zväèša obsahujú pred názvom modlitby ivotopis svätého, popis sviatku alebo podobnú struènú charakteristiku, ktorú pre jednoduchos nazıvame popis.", 
 "Modlitby ke cti svatıch obsahují struènı ivotopis svatého, pøi svátku je to struènı popis svátku a podobnì. Tyto charakteristiky pro struènost nazıváme popis.", 
 "xxx", 
 "",
 "", 
 "Modlitby ke cti svatıch obsahují struènı ivotopis svatého, u svátku je to struènı popis svátku a podobnì. Tyto charakteristiky pro struènost nazıváme popis.",
 "Többnyire az imák az imaóra elnevezése elõtt a szent életrajzát, az ünnep leírását vagy más rövid jegyzetet tartalmaznak, amit az egyszerûség kedvéért leírásnak nevezünk."
};

const char *html_text_option1_spolc_svaty[POCET_JAZYKOV + 1] = 
{"zobrazi, odkia¾ sa berú spoloèné èasti k modlitbe svätého", 
 "zobrazit, odkud se berou spoleèné texty", 
 "display communia info", 
 "", 
 "", 
 "zobrazit, odkud se berou spoleèné texty",
 "megmutatni, honnan lettek véve a közös részek a szentek zsolozsmájához"
};

const char *html_text_option1_spolc_svaty_explain[POCET_JAZYKOV + 1] = 
{"Rubrika obsahujúca informáciu, odkia¾ sa berú spoloèné èasti k modlitbe svätého.", 
 "Rubrika, která pro modlitby svatıch informuje, které spoleèné texty jsou uity.", 
 "Displays communia info.", 
 "", 
 "", 
 "Rubrika, která pro modlitby svatıch informuje, které spoleèné texty jsou uity.",
 "Rubrika, amely azt az információt tartalmazza, hogy melyik közös részbõl vannak véve a szentek zsolozsmájához tartozó közös részek."
};

const char *html_text_option1_vesp_kratsie_prosby[POCET_JAZYKOV + 1] = 
{"pre vešpery poui kratšie prosby z dodatku", 
 "pro nešpory pouít kratší prosby z dodatku", 
 "use shorten prayers for vespers", 
 "", 
 "", 
 "pro veèerní chvály pouít kratší prosby z dodatku", 
 "Esti dicséretre használja a rövidebb közbenjáró fohászokat a függelékbõl"
};

const char *html_text_option1_vesp_kratsie_prosby_explain[POCET_JAZYKOV + 1] = 
{"Pre vešpery poui kratšie prosby z dodatku namiesto tıch, ktoré sú urèené pre vešpery daného dòa.", 
 "Pro nešpory pouít kratší prosby z dodatku místo urèenıch pro pøíslušnı den.", 
 "Use shorten prayers for vespers instead of those prescribed for the day.", 
 "", 
 "", 
 "Pro veèerní chvály pouít kratší prosby z dodatku místo urèenıch pro pøíslušnı den.",
 "Esti dicséretre használja a rövidebb közbenjáró fohászokat a függelékbõl, a napra meghatározott helyett."
};

const char *html_text_option1_vigilia[POCET_JAZYKOV + 1] = 
{"predåené slávenie vigílie pre posvätné èítanie" /*(na nedele, slávnosti a sviatky)*/, 
 "prodlouené slavení vigilie pro modlitbu se ètením" /*(pro nedìle, slavnosti a svátky)*/, 
 "celebrating of vigily for prayer with readings" /*(for Sundays, solemnitas and festivus)*/, 
 "",
 "",
 "prodlouené slavení vigilie pro modlitbu se ètením" /*(pro nedìle, slavnosti a svátky)*/, 
 "hosszabb vigíliás ünneplés Olvasmányos imaórával" /*(vasárnap, fõünnep és ünnep elõtt)*/
};
const char *html_text_option1_vigilia_explain[POCET_JAZYKOV + 1] = 
{"Tí, èo chcú pod¾a tradície predåi vigíliu nedele, slávnosti alebo sviatku, èo sa ve¾mi odporúèa, najprv recitujú posvätné èítanie; po oboch èítaniach, pred hymnom Te Deum, pridávajú sa chválospevy a evanjelium.", 
 "Ti, kteøí chtìjí podle tradice prodlouit vigilii nedìle, slavnosti nebo svátku, co se velmi doporuèuje, recitují nejprve ètení; po obou èteních, pøed hymnem Te Deum, se pøidávají chvalozpìvy a evangelium.", 
 "For Sundays, solemnitas and festivus: celebrating of vigily for prayer with readings.", 
 "",
 "", 
 "Ti, kteøí chtìjí podle tradice prodlouit vigilii nedìle, slavnosti nebo svátku, co se velmi doporuèuje, recitují nejprve ètení; po obou èteních, pøed hymnem Te Deum, se pøidávají chvalozpìvy a evangelium.", 
 "Akik a hagyományokhoz híven vasárnap, fõünnep és ünnep elõtt hosszabb vigíliás ünneplést akarnak tartani, elõször végezzék el az Olvasmányos imaórát, a két olvasmány után és a Téged, Isten, dicsérünk himnusz elõtt vegyék hozzá a kantikumokat és utána az evangéliumot."
};

const char *html_text_option1_spomienka_spolcast[POCET_JAZYKOV + 1] = 
{"na spomienky poui èasti zo spoloènıch èastí", 
 "na památky pouít èásti ze spoleènıch textù", 
 "take parts from celebration -- commmons", 
 "", 
 "", 
 "na památky pouít èásti ze spoleènıch èástí", 
 "emléknapon a jelzett részeket a közös részbõl venni"
};

const char *html_text_option1_spomienka_spolcast_explain[POCET_JAZYKOV + 1] = 
{"Zvoli, èi sa antifóna na invitatórium, hymnus, krátke èítanie, antifóny na Benediktus a Magnifikat a prosby, ak nie sú vlastné berú zo spoloènej èasti (ináè z beného všedného dòa); è. 235 b) všeobecnıch smerníc.", 
 "", 
 "", 
 "",
 "", 
 "",
 "Kiválasztani, hogy az imádságra hívás antifónája, himnusz, rövid olvasmány, a Benedictus és a Magnifikat antifónája és a fohászok a közös részbõl legyenek véve (egyébként a köznapról) a 235 b) általános rendelkezés szerint."
};

const char *html_text_option1_spomienka_spolcast_NIE[POCET_JAZYKOV + 1] = 
{"na spomienky poui èasti zo dòa, nie zo spoloènıch èastí", 
 "na památky pouít èásti z bìného dne, ne ze spoleènıch textù", 
 "take parts from feria -- not commmons", 
 "", 
 "", 
 "na památky pouít èásti z bìného dne, ne ze spoleènıch èástí", 
 "emléknapon a jelzett részeket az adott napról venni, nem a közös részbõl"
};

const char *html_text_option2_html_export[POCET_JAZYKOV + 1] = 
{"monosti zobrazenia stránok",
 "monosti zobrazení stránek",
 "display options",
 "",
 "",
 "monosti zobrazení stránek",
 "az oldalak megjelenítésének lehetõségei:"
};

const char *html_text_option2_html_export_explain[POCET_JAZYKOV + 1] = 
{"Tieto monosti ovplyvnia rozlièné zobrazenia, nemajú vplyv na obsah (text) modlitieb.",
 "Monosti ovlivní rozlièná zobrazení, neovlivní obsah (text) modliteb.",
 "These various options have no influence to generated text of prayers, used only for visualization.",
 "",
 "",
 "Monosti ovlivní rozlièná zobrazení, neovlivní obsah (text) modliteb.",
 "Ezek a beállítások hatással vannak a formai megjelenítésre, de az imaszöveg nem változik."
};

const char *html_text_option2_prve_vespery[POCET_JAZYKOV + 1] = 
{"zobrazi tlaèidlo pre prvé vešpery pre nedele a slávnosti v deò slávenia",
 "zobrazit tlaèítko pro první nešpory pro nedìle a slavnosti v den slavení",
 "display button for first vesperas for Sundays and solemnitas for the day of celebration",
 "",
 "",
 "zobrazit tlaèítko pro první veèerní chvály pro nedìle a slavnosti v den slavení",
 "vasárnapok és fõünnepek esetén az I. Esti dicséret gombja az ünneplés napján jelenjen meg"
};
/*
{"zobrazi tlaèidlo pre prvé vešpery <!--(a kompletórium po nich)--> pre nedele a slávnosti v deò slávenia",
 "zobrazit tlaèítko pro první nešpory <!--(a kompletáø po nich)--> pro nedìle a slavnosti v den slavení",
 "display button for first vesperas <!--(and completory after them)--> for Sundays and solemnitas for the day of celebration",
 "",
 "",
 "zobrazit tlaèítko pro první veèerní chvály <!--(a kompletáø po nich)--> pro nedìle a slavnosti v den slavení",
 "vasárnapok és fõünnepek esetén az I. Esti dicséret gombja az ünneplés napján jelenjen meg"
};
*/
const char *html_text_option2_prve_vespery_explain[POCET_JAZYKOV + 1] = 
{"Keïe základnım kritériom pre zobrazovanie modlitieb daného dòa je dátum, formálne prvé vešpery nedie¾ a slávností (a tie kompletórium po nich) nespadajú pod danı dátum, ale pre predošlı deò, kde sa zobrazujú ako bené vešpery. Pre sobotné slávenie sa nebude tlaèidlo pre vešpery (a kompletórium) zobrazova.", 
 "Jeliko základním kritériem pro zobrazování ponuky modliteb daného dne je datum, první nešpory nedìl a slavností (a také kompletáø po nich) nespadají pod danı datum, nıbr pro pøedcházející den, kde jsou zobrazeny jako bìné nešpory. Pro sobotní slavení se tlaèítko pro nešpory (a kompletáø) nebude zobrazovat.", 
 "xxx", 
 "",
 "", 
 "Jeliko základním kritériem pro zobrazování ponuky modliteb daného dne je datum, první veèerní chvály nedìl a slavností (a také kompletáø po nich) nespadají pod danı datum, nıbr pro pøedcházející den, kde jsou zobrazeny jako bìné první veèerní chvály. Pro sobotní slavení se tlaèítko pro veèerní chvály (a kompletáø) nebude zobrazovat.", 
 "Mivel az imaórák megjelenítése elsõsorban a dátumtól függ, a vasárnapok és fõünnepek I. Esti dicsérete (valamint az utánuk következõ Befejezõ imaóra) formálisan nem tartozik az adott dátumhoz, hanem az elõzõ naphoz. Itt mint köznapi Esti dicséret jelenik meg. Az I. Esti dicséret (és Befejezõ imaóra) gombja nem fog megjelenni szombati végzéshez."
};

const char *html_text_option2_iso_datum[POCET_JAZYKOV + 1] = 
{"zobrazi dátum v ISO 8601 formáte (RRRR-MM-DD)", 
 "zobrazit datum v ISO 8601 formátu (RRRR-MM-DD)", 
 "display date in ISO 8601 format (RRRR-MM-DD)", 
 "",
 "",
 "zobrazit datum v ISO 8601 formátu (RRRR-MM-DD)", 
 "a dátum ISO 8601 formátumban (ÉÉÉÉ-HH-NN) jelenjen meg"
};
const char *html_text_option2_iso_datum_explain[POCET_JAZYKOV + 1] = 
{"", 
 "", 
 "", 
 "",
 "", 
 "", 
 ""
};

const char *html_text_option2_font_family[POCET_JAZYKOV + 1] = 
{"poui bezpätkové písmo? (ináè pätkové)", 
 "pouít bezpatkové písmo? (jinak patkové)", 
 "use Sans Serif font? (otherwise, Serif is used)", 
 "",
 "",
 "pouít bezpatkové písmo? (jinak patkové)", 
 "talp nélküli betûk használata"
};
const char *html_text_option2_font_family_explain[POCET_JAZYKOV + 1] = 
{"Zvo¾te si pätkové písmo (Serif) resp. bezpätkové písmo (Sans Serif) pod¾a toho, èo vám viac vyhovuje pre komfort modlitby. Pouije sa predvolené písmo prehliadaèa.", 
 "", 
 "", 
 "",
 "", 
 "", 
 "Válasszon talpas (Serif) vagy talp nélküli (Sans Serif) betût, kényelem szerint. A böngészõ ablakban mutatott betûtípus az alapértelmezett."
};

const char *html_text_navig_buttons[POCET_JAZYKOV + 1] = 
{"navigáciu", 
 "navigaci", 
 "navigation buttons", 
 "",
 "",
 "navigaci", 
 "navigáció"
};
const char *html_text_option2_navigation[POCET_JAZYKOV + 1] = 
{"zobrazi navigáciu v textoch modlitieb",
 "zobrazit navigaci v textech modliteb", 
 "display navigation buttons in prayer", 
 "",
 "",
 "zobrazit navigaci v textech modliteb", 
 "a navigáció mutatása az imaszövegben", 
};
const char *html_text_option2_navigation_explain[POCET_JAZYKOV + 1] = 
{"Èi sa majú zobrazova hypertextové odkazy na ostatné modlitby daného dòa, príp. predošlı/nasledovnı deò priamo v texte modlitby.", 
 "Zda zobrazit hypertextové odkazy na ostatní modlitby daného dne, resp. pøedešlı/následující den pøímo v textu modlitby.", 
 "Whether hypertext links (as buttons) to other prayers of the selected celebration should be displayed.", 
 "",
 "", 
 "Zda zobrazit hypertextové odkazy na ostatní modlitby daného dne, resp. pøedešlı/následující den pøímo v textu modlitby.", 
 "Legyen-e hiperhivatkozás a nap többi imaórájára is,  illetve mutassa-e az elõzõ és következõ nap imaóráit is közvetlenül a szövegben.", 
};

const char *html_text_option2_moznosti[POCET_JAZYKOV + 1] = 
{"zobrazi rozlièné monosti priamo v textoch modlitieb",
 "zobrazit rozlièné volby v textech modliteb", 
 "display various options in prayers", 
 "",
 "",
 "zobrazit rozlièné volby v textech modliteb", 
 "az imák szövegében megmutatni a különbözõ lehetõségeket", 
};
const char *html_text_option2_moznosti_explain[POCET_JAZYKOV + 1] = 
{"Èi sa majú zobrazova hypertextové odkazy na iné zobrazenie tej istej modlitby priamo v texte modlitby (napr. pre modlitbu cez deò na verziu s doplnkovou psalmódiou).", // Vtedy nie je potrebné, aby boli zobrazené prepínaèe na titulnej stránke.
 "Zda zobrazit hypertextové odkazy na jiné zobrazení modlitby daného dne pøímo v textu modlitby (napø. pro modlitbu uprostrìd dne verzi se almy z doplòujícího cyklu).", 
 "Whether various options should be displayed directly in the prayer's texts.", 
 "",
 "", 
 "Zda zobrazit hypertextové odkazy na jiné zobrazení modlitby daného dne pøímo v textu modlitby (napø. pro modlitbu uprostrìd dne verzi se almy z doplòujícího cyklu).", 
 "Hogy mutatkozzanak-e a hipertextus utalások a jelenlegi ima másabb ábrázolására közvetlenül az ima szövegében (pld. a napközi imához a kiegészítõ zsoltárral való verzióra is.", 
};

const char *html_text_option2_textwrap[POCET_JAZYKOV + 1] = 
{"zalamova dlhé riadky ako v tlaèenom vydaní (poetické èasti)",
 "zalomit dlouhé øádky poetickıch textù jako v tištìném vydání", 
 "xxx", 
 "",
 "",
 "zalomit dlouhé øádky poetickıch textù jako v tištìném vydání", 
 "hosszú sorok tördelése, mint a nyomtatott kiadásban (versrészek)", 
};
const char *html_text_option2_textwrap_explain[POCET_JAZYKOV + 1] = 
{"Èi sa majú v texte modlitby dlhé riadky almov, chválospevov a inıch poetickıch èastí zalamova ako v tlaèenom vydaní.", 
 "Zda zalomit dlouhé øádky poetickıch textù jako v tištìném vydání (normálnì: nezalamovat).", 
 "xxx", 
 "",
 "", 
 "Zda zalomit dlouhé øádky poetickıch textù jako v tištìném vydání (normálnì: nezalamovat).", 
 "Legyenek-e tördelve az imaórák szövegében  a zsoltárok, kantikumok és más versrészek hosszú sorai, mint a nyomtatott kiadásban.", 
};

const char *html_text_option2_buttons_usporne[POCET_JAZYKOV + 1] = 
{"tlaèidlá pre modlitby zobrazi úsporne",
 "tlaèítka pro modlitby zobrazit úspornì", 
 "xxx", 
 "",
 "",
 "tlaèítka pro modlitby zobrazit úspornì", 
 "az imaórák gombjainak gazdaságos elhelyezése", 
};
const char *html_text_option2_buttons_usporne_explain[POCET_JAZYKOV + 1] = 
{"Èi sa majú tlaèidlá pre modlitby zobrazi úsporne, v tabu¾ke (menšia šírka) kvôli mobilnım zariadeniam.", 
 "Zda se mají tlaèítka pro modlitby zobrazit úspornì, v tabulce (menší šíøka) pro mobilní zaøízení.", 
 "xxx", 
 "",
 "", 
 "Zda se mají tlaèítka pro modlitby zobrazit úspornì, v tabulce (menší šíøka) pro mobilní zaøízení.", 
 "Legyenek-e az imaórák gombjai gazdaságosan elhelyezve, táblázatban (kisebb szélesség) a mobli készülékek céljából.", 
};

const char *html_text_option2_nocny_rezim[POCET_JAZYKOV + 1] = 
{"noènı reim",
 "noèní reim",
 "xxx", 
 "",
 "",
 "noèní reim",
 "éjszakai mód", 
};
const char *html_text_option2_nocny_rezim_explain[POCET_JAZYKOV + 1] = 
{"Zobrazí svetlı text na tmavom pozadí."
 "Zobrazí svìtlı text na tmavém pozadí.",
 "xxx", 
 "",
 "", 
 "Zobrazí svìtlı text na tmavém pozadí.",
 "Megmutatja világos szöveg sötét háttér.",
};

const char *html_text_option2_alternatives[POCET_JAZYKOV + 1] = 
{"alternatívy",
 "alternativy",
 "alternatives", 
 "",
 "",
 "alternativy",
 "alternatívák", 
};
const char *html_text_option2_alternatives_explain[POCET_JAZYKOV + 1] = 
{"Zobrazí v texte modlitieb iba jednu monos, napr. hymnus pre kompletórium (dá sa prepína).",
 "Zobrazí v textu modliteb jenom jedno monost (je moné pøepínat).",
 "", 
 "",
 "", 
 "Zobrazí v textu modliteb jenom jedno monost (je moné pøepínat).",
 "Megmutatja ...",
};

const char *html_text_option5_KomplHymnusA[POCET_JAZYKOV + 1] = 
{"hymnus A: Na sklonku dòa a úprimne",
 "hymnus A: Na sklonku dne tì upøímnì",
 "hymn A", 
 "",
 "",
 "hymnus A: Na sklonku dne tì upøímnì",
 "himnusz A: Immár a nap leáldozott", 
};

const char *html_text_option5_KomplHymnusB[POCET_JAZYKOV + 1] = 
{"hymnus B: Kriste, ty svetlo a náš deò",
 "hymnus B: Ty, Kriste, svìtlo, jasnı dni",
 "hymn B", 
 "",
 "",
 "hymnus B: Ty, Kriste, svìtlo, jasnı dni",
 "himnusz B: Krisztus, tündöklõ nappalunk", 
};

const char *html_text_option5_PCHymnusI[POCET_JAZYKOV + 1] = 
{"hymnus I. [Ak je posvätné èítanie v noci alebo vèasráno]",
 "hymnus I. [V noci a èasnì ráno]",
 "hymn I. [during the night and early in the morning]",
 "",
 "",
 "hymnus I. [V noci a èasnì ráno]",
 "himnusz I. [Amikor az imaórát éjszaka vagy kora hajnalban mondják]",
};

const char *html_text_option5_PCHymnusII[POCET_JAZYKOV + 1] = 
{"hymnus II. [Ak je posvätné èítanie cez deò]",
 "hymnus II. [Bìhem dne]",
 "hymn II. [during the day]",
 "",
 "",
 "hymnus II. [Bìhem dne]",
 "himnusz II. [Amikor az imaórát a nap nem reggeli órájában végzik]",
};

const char *html_text_option5_PCHymnusVNnedela[POCET_JAZYKOV + 1] = 
{"hymnus Toto je pravı Boí deò",
 "hymnus nedìlní",
 "Sunday's hymn",
 "",
 "",
 "hymnus nedìlní",
 "himnusz Urunknak áldott napja ez",
};

const char *html_text_option5_PCHymnusVNferia[POCET_JAZYKOV + 1] = 
{"hymnus Nech z vıšin neba rados znie",
 "hymnus z férie",
 "hymnus férie",
 "",
 "",
 "hymnus z férie",
 "himnusz Örvendj, ég, messzi csillagok",
};

const char *html_text_option5_RChHymnusVNnedela[POCET_JAZYKOV + 1] = 
{"hymnus Bronie sa zora na nebi",
 "hymnus nedìlní",
 "hymnus NE",
 "",
 "",
 "hymnus nedìlní",
 "himnusz Rózsálló hajnalfény ragyog",
};

const char *html_text_option5_RChHymnusVNferia[POCET_JAZYKOV + 1] = 
{"hymnus Nech novım Jeruzalemom",
 "hymnus z férie",
 "hymnus férie",
 "",
 "",
 "hymnus z férie",
 "himnusz Az új Sionnak kórusa",
};

const char *html_text_option5_VespHymnusVNnedela[POCET_JAZYKOV + 1] = 
{"hymnus Pri Baránkovej veèeri",
 "hymnus nedìlní",
 "hymnus NE",
 "",
 "",
 "hymnus nedìlní",
 "himnusz Ím, vár a Bárány asztala",
};

const char *html_text_option5_VespHymnusVNferia[POCET_JAZYKOV + 1] = 
{"hymnus Krá¾ vekov, Pane, Boí Syn",
 "hymnus z férie",
 "hymnus férie",
 "",
 "",
 "hymnus z férie",
 "himnusz Örök Királyunk, szent Urunk",
};

const char *html_text_option5_MCDPredHymnus1[POCET_JAZYKOV + 1] = 
{"hymnus Príï, Duchu Svätı",
 "hymnus K nám, Duchu Svatı, nyní spìj",
 "hymn 1",
 "",
 "",
 "hymnus K nám, Duchu Svatı, nyní spìj",
 "himnusz Most jöjj, Szentlélek, szállj közénk",
};

const char *html_text_option5_MCDPredHymnus2[POCET_JAZYKOV + 1] = 
{"hymnus Deviata je u hodina",
 "hymnus Je tøetí denní hodina",
 "hymn 2",
 "",
 "",
 "hymnus Je tøetí denní hodina",
 "himnusz Idõk rendjét megtartva most",
};

const char *html_text_option5_MCDNaHymnus1[POCET_JAZYKOV + 1] = 
{"hymnus Mocnı Vládca, vernı Boe",
 "hymnus Jsi mocnı Vládce, vìrnı Bùh",
 "hymn 1",
 "",
 "",
 "hymnus Jsi mocnı Vládce, vìrnı Bùh",
 "himnusz Urunk, felséges Istenünk",
};

const char *html_text_option5_MCDNaHymnus2[POCET_JAZYKOV + 1] = 
{"hymnus Na nebi slnko vrcholí",
 "hymnus Teï Pánu chvály zpívejme",
 "hymn 2",
 "",
 "",
 "hymnus Teï Pánu chvály zpívejme",
 "himnusz Dicsérjük dallal az Urat",
};

const char *html_text_option5_MCDPoHymnus1[POCET_JAZYKOV + 1] = 
{"hymnus Celı svet v pohyb uvádzaš",
 "hymnus Svìt celı v pohyb uvádíš",
 "hymn 1",
 "",
 "",
 "hymnus Svìt celı v pohyb uvádíš",
 "himnusz Világfenntartó Istenünk",
};

const char *html_text_option5_MCDPoHymnus2[POCET_JAZYKOV + 1] = 
{"hymnus Z Boej milosti tretí raz",
 "hymnus Hodina tøetí z poledne",
 "hymn 2",
 "",
 "",
 "hymnus Hodina tøetí z poledne",
 "himnusz Háromszor három óra már",
};

const char *html_text_option5_DPsalmZ122_129[POCET_JAZYKOV + 1] = 
{"namiesto almu 122 bra alm 129",
 "místo almu 122 vzít alm 129",
 "instead of psalm 122 use 129",
 "",
 "",
 "místo almu 122 vzít alm 129",
 "a 121. helyett vehetõ a 128. zsoltár",
};

const char *html_text_option5_DPsalmZ126_129[POCET_JAZYKOV + 1] = 
{"namiesto almu 126 bra alm 129",
 "místo almu 126 vzít alm 129",
 "instead of psalm 126 use 129",
 "",
 "",
 "místo almu 126 vzít alm 129",
 "a 125. helyett vehetõ a 128. zsoltár",
};

const char *html_text_option5_DPsalmZ127_131[POCET_JAZYKOV + 1] = 
{"namiesto almu 127 bra alm 131",
 "místo almu 127 vzít alm 131",
 "instead of psalm 127 use 131",
 "",
 "",
 "místo almu 127 vzít alm 131",
 "a 126. helyett vehetõ a 130. zsoltár",
};

const char *html_text_option5_DPsalmZ122_NORMAL[POCET_JAZYKOV + 1] = 
{"bra alm 122 z doplnkovej psalmódie",
 "vzít alm 122 z doplòovacího cyklu",
 "use psalm 122 from complementary psalmody",
 "",
 "",
 "vzít alm 122 z doplòovacího cyklu",
 "hu_take 121. zsoltár from kiegészítõ zsoltároknál",
};

const char *html_text_option5_DPsalmZ126_NORMAL[POCET_JAZYKOV + 1] = 
{"bra alm 126 z doplnkovej psalmódie",
 "vzít alm 126 z doplòovacího cyklu",
 "use psalm 126 from complementary psalmody",
 "",
 "",
 "vzít alm 126 z doplòovacího cyklu",
 "hu_take 125. zsoltár from kiegészítõ zsoltároknál",
};

const char *html_text_option5_DPsalmZ127_NORMAL[POCET_JAZYKOV + 1] = 
{"bra alm 127 z doplnkovej psalmódie",
 "vzít alm 127 z doplòovacího cyklu",
 "use psalm 127 from complementary psalmody",
 "",
 "",
 "vzít alm 127 z doplòovacího cyklu",
 "hu_take 126. zsoltár from kiegészítõ zsoltároknál",
};

const char *html_text_option5_DPsalmZ122_129_explain[POCET_JAZYKOV + 1] = 
{"V doplnkovej psalmódii namiesto almu 122 mono bra alm 129.",
 "Pro doplòovací cyklus almù místo almu 122 (121) vzít alm 129 (128).",
 "",
 "",
 "",
 "Pro doplòovací cyklus almù místo almu 122 (121) vzít alm 129 (128).",
 "A kiegészítõ zsoltároknál a 121. helyett vehetõ a 128. zsoltár.",
};

const char *html_text_option5_DPsalmZ126_129_explain[POCET_JAZYKOV + 1] = 
{"V doplnkovej psalmódii namiesto almu 126 mono bra alm 129.",
 "Pro doplòovací cyklus almù místo almu 126 (125) vzít alm 129 (128).",
 "",
 "",
 "",
 "Pro doplòovací cyklus almù místo almu 126 (125) vzít alm 129 (128).",
 "A kiegészítõ zsoltároknál a 125. helyett vehetõ a 128. zsoltár.",
};

const char *html_text_option5_DPsalmZ127_131_explain[POCET_JAZYKOV + 1] = 
{"V doplnkovej psalmódii namiesto almu 127 mono bra alm 131.",
 "Pro doplòovací cyklus almù místo almu 127 (126) vzít alm 131 (130).",
 "",
 "",
 "",
 "Pro doplòovací cyklus almù místo almu 127 (126) vzít alm 131 (130).",
 "A kiegészítõ zsoltároknál a 126. helyett vehetõ a 130. zsoltár.",
};


// 2011-05-06
const char *html_text_font_name[POCET_JAZYKOV + 1] = 
{"alebo poui písmo", 
 "nebo pouij písmo", 
 "or use font", 
 "vel font",
 "",
 "nebo pouij písmo", 
 "betûtípus választása"
};
const char *html_text_font_name_explain[POCET_JAZYKOV + 1] = 
{"Ak nie je zvolené konkrétne písmo, pouije sa predvolené písmo prehliadaèa (pätkové alebo bezpätkové pod¾a predchádzajúcej vo¾by zaškrtávacieho políèka).", 
 "", 
 "", 
 "",
 "", 
 "", 
 "Ha nem választunk betûtípust, akkor a böngészõ ablakban látható az alapértelmezett (talpas vagy talpatlan az elõzõ kiválasztás szerint)."
};

// 2011-05-13
const char *html_text_font_size[POCET_JAZYKOV + 1] = 
{"ve¾kos písma", 
 "velikost písma", 
 "font size", 
 "font size",
 "",
 "velikost písma", 
 "betûméret"
};
const char *html_text_font_size_explain[POCET_JAZYKOV + 1] = 
{"Ve¾kos písma", 
 "", 
 "", 
 "",
 "", 
 "", 
 "betûméret"
};

// 2010-10-11: HTML option selected
const char *html_option_selected = " selected";

// 2011-04-11: HTML option checked (pre checkboxy)
const char *html_option_checked = " checked";

const char *html_text_kalendar[POCET_JAZYKOV + 1] = 
{"kalendár", 
 "kalendáø", 
 "calendar", 
 "calendario",
 "",
 "kalendáø",
 "a naptárat"
};
// 2010-09-14
const char *html_text_kalendar_miestny[POCET_JAZYKOV + 1] = 
{"kalendár Liturgie hodín: ",
 "kalendáø Liturgie hodin: ",
 "local or general calendar: ", 
 "calendario per Liturgia horarum: ",
 "",
 "kalendáø Liturgie hodin: ",
 "Az imaórák liturgiája (AK SA DÁ, DA VİBER SEM) naptárát használják"
};
const char *html_text_kalendar_miestny_explain[POCET_JAZYKOV + 1] = 
{"Je moné zvoli miestny kalendár (propriá) reho¾nej rodiny, rádu, kongregácie, inštitútu...", 
 "Je moné vzít místní kalendáø øeholní rodiny, øádu, kongregace, institutu...", 
 "", 
 "",
 "", 
 "", // not applicable for CZOP
 "Lehetséges a helyi naptárt választani, szerzetesrendét, kongregációét, intézményét..."
};

const char *html_text_detaily_explain[POCET_JAZYKOV + 1] = 
{"Ostatné nastavenia sa pouijú z predchádzajúcej (hlavnej) stránky. <p>Pokia¾ sú niektoré parametre pre vybranú modlitbu nepouite¾né, neberú sa do úvahy (môu by teda nastavené ¾ubovo¾ne).", 
 "Kdy jsou nìkteré vıše uvedené volby nepouitelné pro nìjakou modlitbu, neberou se v úvahu (mohou bıt nastaveny dle libovùle).", 
 "If any of described options are not applicable for a chosen prayer, they can be set anyhow.", 
 "",
 "", 
 "Kdy jsou nìkteré vıše uvedené volby nepouitelné pro nìjakou modlitbu, neberou se v úvahu (mohou bıt nastaveny dle libovùle).",
 "A többi beállítási lehetõség a fõoldalon található. <p>Amennyiben valamelyik kiválasztott paraméter nem mûködik, figyelmen kívül kell hagyni (vagyis tetszõlegesen állíthatók)."
};

// 2010-06-04: text pre popis do invitatória
const char *html_text_inv_slavaotcu[POCET_JAZYKOV + 1] = 
{"<p>&nbsp;&nbsp;&nbsp; <"HTML_SPAN_RED_SMALL">Nasleduje</span> <span class=\"small\">Sláva Otcu</span> <"HTML_SPAN_RED_SMALL">a opakuje sa antifóna.</span>", 
 "<p>&nbsp;&nbsp;&nbsp; <"HTML_SPAN_RED_SMALL">Následuje</span> <span class=\"small\">Sláva Otci</span> <"HTML_SPAN_RED_SMALL">a opakuje se antifona.</span>", 
 "<p>&nbsp;&nbsp;&nbsp; <"HTML_SPAN_RED_SMALL">Follows</span> <span class=\"small\">Glory...</span> <"HTML_SPAN_RED_SMALL">a opakuje sa antifóna.</span>", 
 "<p>&nbsp;&nbsp;&nbsp; <"HTML_SPAN_RED_SMALL">Nasleduje</span> <span class=\"small\">Gloria Patri</span> <"HTML_SPAN_RED_SMALL">a opakuje sa antifóna.</span>", 
 "<p>&nbsp;&nbsp;&nbsp; <"HTML_SPAN_RED_SMALL">Nasleduje</span> <span class=\"small\">Sláva Otcu</span> <"HTML_SPAN_RED_SMALL">a opakuje sa antifóna.</span>", 
 "<p>&nbsp;&nbsp;&nbsp; <"HTML_SPAN_RED_SMALL">Následuje</span> <span class=\"small\">Sláva Otci</span> <"HTML_SPAN_RED_SMALL">a opakuje se antifona.</span>", 
 "<p>&nbsp;&nbsp;&nbsp; <"HTML_SPAN_RED_SMALL">Következik a</span> <span class=\"small\">Dicsõség az Atyának</span> <"HTML_SPAN_RED_SMALL">és megismételjük az antifónát.</span>", 
};

// 2013-02-22: page navigation (top, bottom)
const char *html_text_top[POCET_JAZYKOV + 1] = {"&uarr; navrch", "&uarr; nahoru", "&uarr; top", "", "", "&uarr; nahoru", "&uarr; fel"}; // HU: to up -> felfelé | up -> fel | Andy: fent | top -> eleje | to top -> elejére
const char *html_text_bottom[POCET_JAZYKOV + 1] = {"&darr; naspodok", "&darr; dolù", "&darr; bottom", "", "", "&darr; dolù", "&darr; le"}; // HU: to down -> lefelé | down -> le | Andy: lent | bottom -> vége | to bottom -> végére

// 2009-08-04: pre batch mód
const char *html_text_batch_Zoznam1[POCET_JAZYKOV + 1] = {"Zoznam modlitieb", "Seznam modliteb", "List of prayers", "", "", "Seznam modliteb", "Az imák jegyzéke"};
const char *html_text_batch_Zoznam1m[POCET_JAZYKOV + 1] = {"Zoznam modlitieb po mesiacoch", "Seznam modliteb dle mìsícù", "List of prayers by months", "", "", "Seznam modliteb dle mìsícù", "Az imák jegyzéke hónapok szerint"};
const char *html_text_batch_obdobie1m[POCET_JAZYKOV + 1] = {"("/*obdobie */"od %d. %s %d do %d. %s %d)", "(pro období od %d. %s %d do %d. %s %d)", "(%d. %s %d -- %d. %s %d)", "(%d. %s %d -- %d. %s %d)", "(%d. %s %d -- %d. %s %d)", "(pro období od %d. %s %d do %d. %s %d)", "(%d. %s %d -- %d. %s %d)"};
const char *html_text_batch_Zoznam2[POCET_JAZYKOV + 1] = {/* Zoznam modlitieb pre */"%s %d", "%s %d", "%s %d", "%s %d", "%s %d", "%s %d", "%s %d"};
const char *html_text_batch_Back[POCET_JAZYKOV + 1] = {"^ hore", "^ nahoru", "^ up", "", "", "^ nahoru", "^ felfelé"};
const char *html_text_batch_Prev[POCET_JAZYKOV + 1] = {"&lt;&lt;", "&lt;&lt;", "&lt;&lt;", "&lt;&lt;", "&lt;&lt;", "&lt;&lt;", "&lt;&lt;"};
const char *html_text_batch_Next[POCET_JAZYKOV + 1] = {"&gt;&gt;", "&gt;&gt;", "&gt;&gt;", "&gt;&gt;", "&gt;&gt;", "&gt;&gt;", "&gt;&gt;"};

// 2009-04-08: zakonèenie modlitby trojaké, krátke resp. dlhé
const char *text_ZAKONCENIE_SKRZE_dlhe[POCET_JAZYKOV + 1] = 
{"Skrze nášho Pána Jeiša Krista, tvojho Syna, ktorı je Boh a_s_tebou ije a_kra¾uje v_jednote s_Duchom Svätım po všetky veky vekov.",
 "Skrze tvého Syna Jeíše Krista, našeho Pána, nebo on s_tebou v_jednotì Ducha svatého ije a_kraluje po všechny vìky vìkù.",
 "",
 "Per Dóminum nostrum Iesum Christum, Fílium tuum, qui tecum vivit et regnat in unitáte Spíritus Sancti, Deus, per ómnia saecula saeculórum.",
 "",
 "Skrze tvého Syna Jeíše Krista, našeho Pána, nebo on s tebou v jednotì Ducha Svatého ije a kraluje po všechny vìky vìkù.",
 "A mi Urunk, Jézus Krisztus, a te Fiad által, aki veled él és uralkodik a Szentlélekkel egységben, Isten mindörökkön-örökké.",
 };
const char *text_ZAKONCENIE_SKRZE_kratke[POCET_JAZYKOV + 1] = 
{"Skrze Krista, nášho Pána.",
 "Skrze Krista, našeho Pána.",
 "",
 "Per Christum Dóminum nostrum.",
 "",
 "Skrze Krista, našeho Pána.",
 "Krisztus, a mi Urunk által.",
 };
const char *text_ZAKONCENIE_LEBO_ON_dlhe[POCET_JAZYKOV + 1] = 
{"Lebo on je Boh a_s_tebou ije a_kra¾uje v_jednote s_Duchom Svätım po všetky veky vekov.",
 "Nebo on s_tebou v_jednotì Ducha svatého ije a_kraluje po všechny vìky vìkù.",
 "",
 "Qui tecum vivit et regnat in unitáte Spíritus Sancti, Deus, per ómnia saecula saeculórum.",
 "",
 "Nebo on s tebou v jednotì Ducha Svatého ije a kraluje po všechny vìky vìkù.",
 "Aki veled él és uralkodik a Szentlélekkel egységben, Isten mindörökkön-örökké.",
 };
const char *text_ZAKONCENIE_LEBO_ON_kratke[POCET_JAZYKOV + 1] = 
{"Lebo on ije a_kra¾uje na veky vekov.",
 "Nebo on s_tebou ije a_kraluje na vìky vìkù.",
 "",
 "Qui vivit et regnat in saecula saeculórum.",
 "",
 "Nebo on s tebou ije a kraluje na vìky vìkù.",
 "Aki él és uralkodik mindörökkön-örökké.",
 };
const char *text_ZAKONCENIE_LEBO_TY_dlhe[POCET_JAZYKOV + 1] = 
{"Lebo ty si Boh a_iješ a_kra¾uješ s Bohom Otcom v_jednote s_Duchom Svätım po všetky veky vekov.",
 "Nebo ty iješ a_kraluješ s_Bohem Otcem v_jednotì Ducha svatého po všechny vìky vìkù.",
 "",
 "Qui vivis et regnas cum Deo Patre in unitáte Spíritus Sancti, Deus, per ómnia saecula saeculórum.",
 "",
 "Nebo ty iješ a kraluješ s Bohem Otcem v jednotì Ducha Svatého po všechny vìky vìkù.",
 "Aki élsz és uralkodol az Atyaistennel és a Szentlélek­kel egységben, Isten mindörökkön-örökké.",
 };
const char *text_ZAKONCENIE_LEBO_TY_kratke[POCET_JAZYKOV + 1] = 
{"Lebo ty iješ a_kra¾uješ na veky vekov.",
 "Nebo ty iješ a_kraluješ na vìky vìkù.",
 "",
 "Qui vivis et regnas in saecula saeculórum.",
 "",
 "Nebo ty iješ a kraluješ na vìky vìkù.",
 "Aki élsz és uralkodol mindörökkön-örökké.",
 };
// 2010-06-07: len pre SK (POST1_MODLITBA5NE)
const char *text_ZAKONCENIE_ON_JE_dlhe = "On je Boh a_s_tebou ije a_kra¾uje v_jednote s_Duchom Svätım po všetky veky vekov.";
const char *text_ZAKONCENIE_ON_JE_kratke = "On ije a_kra¾uje na veky vekov.";
/* 2011-01-14: pridané len pre SK 
		(04NOV_MODLITBA, 24APR2_MODLITBA, 11JUN_MODLITBA, 19OKT2_MODLITBA, VN1_MODLITBA3STR, ADV12PO_MODLITBA, ADV12STR_MODLITBA, 
		VTYZ_MODLITBA6PO, ADV12UT_MODLITBA, ADV12PI_MODLITBA, ADV13STV_MODLITBA, OZZ_MODLITBA, SCDP_MODLITBA, PMB_rMODLITBA, SCPM_MODLITBA, 
		SCSM_MODLITBA, 24APR_MODLITBA, 25APR_MODLITBA, 02AUG_MODLITBA, 05AUG_MODLITBA, 15AUG_1MODLITBA, 16JUL_MODLITBA, 30JUL2_MODLITBA, 
		24OKT_MODLITBA, VIAN2_MODLITBA11, VN1_MODLITBA4NE, SPMVSr_MODLITBA2, 24JUN_1MODLITBA, 
		VN1_MODLITBA6STV [nepouíva sa], VN1_rPROSBY6PI_pred_nan [nepouíva sa], VN1_vPROSBY6PI_pred_nan [nepouíva sa])
 */
const char *text_ZAKONCENIE_KTORY_JE_dlhe = "ktorı je Boh a_s_tebou ije a_kra¾uje v_jednote s_Duchom Svätım po všetky veky vekov.";
const char *text_ZAKONCENIE_KTORY_JE_kratke = "ktorı ije a_kra¾uje na veky vekov.";

const char *text_ZAKONCENIE_O_TO_TA_PROSIME[POCET_JAZYKOV + 1] = 
{"O_to a prosíme",
 "Prosíme o_to",
 "",
 "",
 "",
 "Prosíme o_to",
 "",
 };


// 2009-05-15: pre dominikánov
const char *text_PRO_OP[POCET_JAZYKOV + 1] = 
{"Pre dominikánov (CZ_OP): ",
"Pro dominikány (OP CZ): ",
 "",
 "",
 "",
 "Pro OP CZ: ",
 "",
 };

// nasledujú názvy liturgickıch dní -- follow the names of special liturgical celebrations

// --------------- 00 pohyblivé slávenia ---------------

const char *text_DRUHA_NEDELA_PO_NAR_PANA[POCET_JAZYKOV + 1] = 
{"2. nede¾a po Narodení Pána",
 "2. nedìle po Narození Pánì",
 "",
 "",
 "",
 "2. nedìle po Narození Pánì",
 "Karácsony Utáni 2. Vasárnap",
 };

// --------------- 01 január ---------------

const char *text_JAN_01[POCET_JAZYKOV + 1] = 
{"Panny Márie Bohorodièky",
 "Matky Boí, Panny Marie",
 "",
 "Sanctae Dei Genetricis Mariae",
 "",
 "Matky Boí, Panny Marie",
 "Szûz Mária, Isten Anyja (újév)",
 };
const char *text_JAN_01_SJ[POCET_JAZYKOV + 1] = 
{"Panny Márie Bohorodièky a Mena Jeiš "HTML_LINE_BREAK"(Titulárny sviatok Spoloènosti Jeišovej)", // titulárny sviatok Spoloènosti Jeišovej
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_02[POCET_JAZYKOV + 1] = 
{"Sv. Bazila Ve¾kého a Gregora Nazianzského,"HTML_LINE_BREAK"biskupov a uèite¾ov Cirkvi",
 "Sv. Basila Velikého a Øehoøe Naziánského,"HTML_LINE_BREAK"biskupù a uèitelù církve",
 "",
 "Ss. Basilii Magni et Gregorii Nazianzeni, ep. et Eccl. doct.",
 "",
 "Sv. Basila Velikého a Øehoøe Naziánského,"HTML_LINE_BREAK"biskupù a uèitelù Církve",
 "Nagy Szent Vazul és Nazianzi Szent Gergely püspökök és egyháztanítók",
 };
const char *text_JAN_03[POCET_JAZYKOV + 1] = 
{"Najsvätejšieho mena Jeiš",
 "Nejsvìtìjšího jména Jeíš",
 "",
 "",
 "",
 "Nejsvìtìjšího Jména Jeíš",
 "Jézus szent neve",
 };
const char *text_JAN_04_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Angely z Foligna, reho¾níèky, èlenky 3. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_05_CSSR[POCET_JAZYKOV + 1] = 
{"Sv. Jána Nepomuckého Neumanna, biskupa",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_05_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Didaka Jozefa z Cádizu, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_06[POCET_JAZYKOV + 1] = // 6. januára | alebo nede¾u medzi 2. a 8. januárom
{"Zjavenie Pána",
 "Zjevení Pánì",
 "",
 "In Epiphania Domini",
 "",
 "Zjevení Pánì",
 "Urunk megjelenése (Vízkereszt)",
 };
const char *text_JAN_07[POCET_JAZYKOV + 1] = 
{"Sv. Rajmunda z Peòafortu, kòaza",
 "Sv. Rajmunda z Penafortu, knìze",
 "",
 "S. Raimundi de Penyafort, presb.",
 "",
 "Sv. Rajmunda z Peòafortu, knìze",
 "Penyaforti Szent Rajmund áldozópap",
 };
const char *text_JAN_10_1_OP[POCET_JAZYKOV + 1] = 
{"Bl. Gundislava z Amarante, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_10_2_OP[POCET_JAZYKOV + 1] = 
{"Bl. Anny Monteagudovej, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_11_OP[POCET_JAZYKOV + 1] = 
{"Bl. Bernarda Scammaccu, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_KRST[POCET_JAZYKOV + 1] = // v nede¾u po 6. januári | (v nede¾u po Zjavení Pána) alebo: ak však táto nede¾a (zrejme Zjavenia Pána) padne na deò 7. alebo 8. januára, ofícium sa slávi v nasledujúci deò
{"Krst Krista Pána",
 "Køtu Pánì",
 "",
 "In Baptismate Domini",
 "",
 "Køtu Pánì",
 "Urunk megkeresztelkedése",
 };
const char *text_JAN_12_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Bernarda z Corleone, reho¾níka, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_13[POCET_JAZYKOV + 1] = 
{"Sv. Hilára, biskupa a uèite¾a Cirkvi",
 "Sv. Hilaria, biskupa a uèitele církve",
 "",
 "S. Hilarii, ep. et Eccl. doct.",
 "",
 "Sv. Hilaria, biskupa a uèitele Církve",
 "Szent Hiláriusz (Vidor) püspök és egyháztanító",
 };
const char *text_JAN_14_CSSR[POCET_JAZYKOV + 1] = 
{"Bl. Petra Dondersa, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_14_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Odorika z Pordenone, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_14_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Gotfrída, øeholníka z premonstrátského øádu",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_15_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Remete Szent Pál szerzetes",
 };
const char *text_JAN_15_OP[POCET_JAZYKOV + 1] = 
{"Sv. Františka Fernándeza de Capillas, kòaza, "HTML_LINE_BREAK"sv. Petra Sansa, biskupa, a spoloèníkov, muèeníkov",
 "",
 "",
 "",
 "",
 "Sv. Františka Fernándeze de Capillas, knìze, "HTML_LINE_BREAK"Petra Sanse, biskupa, a druhù, èínskıch muèedníkù",
 "",
 };
const char *text_JAN_15_SVD[POCET_JAZYKOV + 1] = 
{"Sv. Arnolda Janssena, kòaza a zakladate¾a troch misijnıch reho¾nıch spoloèností",
 "",
 "",
 "la_",
 "",
 "",
 "",
 };
const char *text_JAN_15_SDB[POCET_JAZYKOV + 1] = 
{"Bl. Alojza Variaru, kòaza",
 "",
 "",
 "la_",
 "",
 "",
 "",
 };
const char *text_JAN_16_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Berarda, kòaza, a spoloèníkov, prvıch františkánskych muèeníkov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_17[POCET_JAZYKOV + 1] = 
{"Sv. Antona, opáta",
 "Sv. Antonína, opata",
 "",
 "S. Antonii, abbatis",
 "",
 "Sv. Antonína, opata",
 "Szent Antal apát",
 };
const char *text_JAN_18_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Panny Marie, Matky jednoty køesanù",
 "",
 "",
 "",
 "Panny Marie, Matky jednoty køesanù",
 "",
 };
const char *text_JAN_18[POCET_JAZYKOV + 1] = 
{"Sv. Margity Uhorskej, panny",
 "",
 "",
 "la_",
 "",
 "Sv. Markéty Uherské, panny, mnišky", // CZOP 19. januára kvôli text_JAN_18_CZ
 "Árpádházi Szent Margit szûz",
 };
const char *text_JAN_19_OP[POCET_JAZYKOV + 1] = 
{"Bl. Andreja z Peschiera, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_19_SJ[POCET_JAZYKOV + 1] = 
{"Bl. Jakuba Sal&egrave;sa a Viliama Saultemouchea, Ignáca de Azevedo a spoloèníkov, "HTML_LINE_BREAK"Jakuba Bonnauda a spoloèníkov, muèeníkov",
 "",
 "",
 "",
 "",
 "_",
 "",
 };
const char *text_JAN_20_1[POCET_JAZYKOV + 1] = 
{"Sv. Fabiána, pápea a muèeníka",
 "Sv. Fabiána, papee a muèedníka",
 "",
 "S. Fabiani, papae et mart.",
 "",
 "Sv. Fabiána, papee a muèedníka",
 "Szent Fábián pápa év vértanú",
 };
const char *text_JAN_20_2[POCET_JAZYKOV + 1] = 
{"Sv. Šebastiána, muèeníka",
 "Sv. Šebestiána, muèedníka",
 "",
 "S. Sebastiani, mart.",
 "",
 "Sv. Šebestiána, muèedníka",
 "Szent Sebestyén vértanú",
 };
const char *text_JAN_20_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Jána Krstite¾a Triquerie, kòaza a muèeníka, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_20_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Esztergomi boldog Özséb áldozópap",
 };
const char *text_JAN_21[POCET_JAZYKOV + 1] = 
{"Sv. Agnesy, panny a muèenice",
 "Sv. Aneky, panny a muèednice",
 "",
 "S. Agnetis, virg. et mart.",
 "",
 "Sv. Aneky, panny a muèednice",
 "Szent Ágnes szûz és vértanú",
 };
const char *text_JAN_22[POCET_JAZYKOV + 1] = 
{"Sv. Vincenta, diakona a muèeníka",
 "Sv. Vincence, jáhna a muèedníka",
 "",
 "S. Vincentii, diaconi et mart.",
 "",
 "Sv. Vincence, jáhna a muèedníka",
 "Szent Vince diakónus és vértanú",
 };
const char *text_JAN_22_OP[POCET_JAZYKOV + 1] = 
{"Bl. Antona della Chiesa, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_22_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Boldog Batthyány-Stratmann László családapa",
 };
const char *text_JAN_22_SDB[POCET_JAZYKOV + 1] = 
{"Bl. Laury Vicuòovej, panny a muèenice",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_23_SK[POCET_JAZYKOV + 1] = 
{"Sv. Jána Almuníka, biskupa",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_23_OP[POCET_JAZYKOV + 1] = 
{"Bl. Henricha Suzu, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_24[POCET_JAZYKOV + 1] = 
{"Sv. Františka Saleského, biskupa a uèite¾a Cirkvi",
 "Sv. Františka Saleského, biskupa a uèitele církve",
 "",
 "S. Francisci de Sales, ep. et Eccl. doct.",
 "",
 "Sv. Františka Saleského, biskupa a uèitele Církve",
 "Szalézi Szent Ferenc püspök és egyháztanító",
 };
const char *text_JAN_24_SDB[POCET_JAZYKOV + 1] = 
{"Sv. Františka Saleského, biskupa a uèite¾a Cirkvi,"HTML_LINE_BREAK"titulárneho patróna saleziánskej rodiny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_25[POCET_JAZYKOV + 1] = 
{"Obrátenie svätého Pavla, apoštola",
 "Obrácení svatého Pavla, apoštola",
 "",
 "In Conversione S. Pauli, Apostoli",
 "",
 "Obrácení svatého Pavla, apoštola",
 "Szent Pál apostol megtérése (Pál fordulása)",
 };
const char *text_JAN_26[POCET_JAZYKOV + 1] = 
{"Sv. Timoteja a Títa, biskupov",
 "Sv. Timoteje a Tita, biskupù",
 "",
 "Ss. Timothei et Titi, ep.",
 "",
 "Sv. Timoteje a Tita, biskupù",
 "Szent Timóteus és Szent Titusz püspökök",
 };
const char *text_JAN_27[POCET_JAZYKOV + 1] = 
{"Sv. Angely Merici, panny",
 "Sv. Andìly Mericiové, panny",
 "",
 "S. Angelae Merici, virg.",
 "",
 "Sv. Andìly Mericiové, panny",
 "Merici Szent Angéla szûz",
 };
const char *text_JAN_27_OP[POCET_JAZYKOV + 1] = 
{"Bl. Markolína z Forl&#236;, kòaza", // &igrave;
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_28[POCET_JAZYKOV + 1] = 
{"Sv. Tomáša Akvinského, kòaza a uèite¾a Cirkvi",
 "Sv. Tomáše Akvinského, knìze a uèitele církve",
 "",
 "S. Thomae de Aquino, presb. et Eccl. doct.",
 "",
 "Sv. Tomáše Akvinského, knìze a uèitele Církve",
 "Aquinói Szent Tamás áldozópap és egyháztanító",
 };
const char *text_JAN_29_SVD[POCET_JAZYKOV + 1] = 
{"Sv. Jozefa Freinademetza, kòaza",
 "",
 "",
 "la_",
 "",
 "",
 "",
 };
const char *text_JAN_29_OP[POCET_JAZYKOV + 1] = 
{"Bl. Villany delle Botti, matky rodiny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_30_SDB[POCET_JAZYKOV + 1] = 
{"Bl. Bronislava Markiewicza, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_30_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Hyacinty Mariscottiovej, panny, èlenky 3. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JAN_31[POCET_JAZYKOV + 1] = 
{"Sv. Jána Boska, kòaza", // Direktórium 2012, str. 72, má: 'Bosca'
 "Sv. Jana Boska, knìze",
 "",
 "S. Ioannis Bosco, presb.",
 "",
 "Sv. Jana Boska, knìze",
 "Bosco Szent János áldozópap",
 };
const char *text_JAN_31_SDB[POCET_JAZYKOV + 1] = 
{"Sv. Jána Boska, kòaza, otca a uèite¾a mládee,"HTML_LINE_BREAK"zakladate¾a Spoloènosti svätého Františka Saleského,"HTML_LINE_BREAK"Inštitútu dcér Márie Pomocnice"HTML_LINE_BREAK"a saleziánov spolupracovníkov",
 "",
 "",
 "",
 "",
 "",
 "",
 };

// --------------- 02 február ---------------

const char *text_FEB_01_SDB[POCET_JAZYKOV + 1] = 
{"Všetkıch nebohıch èlenov Spoloènosti svätého Františka Saleského",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_02[POCET_JAZYKOV + 1] = 
{"Obetovanie Pána",
 "Uvedení Pánì do chrámu",
 "",
 "In Praesentatione Domini",
 "",
 "Uvedení Pánì do chrámu",
 "Urunk bemutatása (Gyertyaszentelõ Boldogasszony)",
 };
const char *text_FEB_03_1[POCET_JAZYKOV + 1] = 
{"Sv. Blaeja, biskupa a muèeníka",
 "Sv. Blaeje, biskupa a muèedníka",
 "",
 "S. Blasii, ep. et mart.",
 "",
 "Sv. Blaeje, biskupa a muèedníka",
 "Szent Balázs püspök és vértanú",
 };
const char *text_FEB_03_2[POCET_JAZYKOV + 1] = 
{"Sv. Oskára, biskupa",
 "Sv. Ansgara, biskupa",
 "",
 "S. Ansgarii, ep.",
 "",
 "Sv. Ansgara, biskupa",
 "Szent Anszgár (Oszkár) püspök",
 };
const char *text_FEB_03_1_OP[POCET_JAZYKOV + 1] = 
{"Bl. Petra z Ruff&#236;a, kòaza a muèeníka", // &igrave;
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_03_2_OP[POCET_JAZYKOV + 1] = 
{"Bl. Antona Pavoniho, kòaza a muèeníka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_03_3_OP[POCET_JAZYKOV + 1] = 
{"Bl. Bartolomeja Cerveriho, kòaza a muèeníka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_04_OP[POCET_JAZYKOV + 1] = 
{"Sv. Kataríny de’ Ricci, panny",
 "",
 "",
 "",
 "",
 "Sv. Kateøiny z Ricci, panny, øeholnice",
 "",
 };
const char *text_FEB_04_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Jána de Brito, kòaza, bl. Rudolfa Acquavivu, kòaza a jeho spoloèníkov; "HTML_LINE_BREAK"bl. Františka Pacheca, Karola Spinolu, kòazov a spoloèníkov, muèeníkov; "HTML_LINE_BREAK"bl. Jakuba Berthieu, kòaza, Leva Mangina, kòaza a spoloèníkov, muèeníkov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_04_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Jozefa z Leonissy, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_04_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Bedøicha, opata z premonstrátského øádu",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_05[POCET_JAZYKOV + 1] = 
{"Sv. Agáty, panny a muèenice", // direktóriá uvádzajú Agáta s dlhım "á"; LH s krátkym "a" Agata
 "Sv. Agáty, panny a muèednice",
 "",
 "S. Agathae, virg. et mart.",
 "",
 "Sv. Agáty, panny a muèednice",
 "Szent Ágota szûz és vértanú",
 };
const char *text_FEB_06[POCET_JAZYKOV + 1] = 
{"Sv. Pavla Mikiho a spoloèníkov, muèeníkov",
 "Sv. Pavla Mikiho a druhù, muèedníkù",
 "",
 "Ss. Pauli Miki et sociorum, mart.",
 "",
 "Sv. Pavla Mikiho a druhù, muèedníkù",
 "Miki Szent Pál és társai vértanúk",
 };
const char *text_FEB_06_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Pavla Mikiho, reho¾níka, a jeho spoloèníkov, muèeníkov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_06_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Petra Baptistu, kòaza, a spoloèníkov, františkánskych muèeníkov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_07_OP[POCET_JAZYKOV + 1] = 
{"Spomienka na zosnulıch otcov a matky èlenov rehole",
 "",
 "",
 "",
 "",
 "Vıroèní památka zemøelıch otcù a matek",
 "",
 };
const char *text_FEB_07_SDB[POCET_JAZYKOV + 1] = 
{"Bl. Pia IX., pápea",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_07_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Kolety z Corbie, panny, èlenky 2. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_08_1[POCET_JAZYKOV + 1] = 
{"Sv. Hieronyma Emilianiho",
 "Sv. Jeronıma Emilianiho",
 "",
 "S. Hieronymi Emiliani",
 "",
 "Sv. Jeronıma Emilianiho",
 "Emiliáni Szent Jeromos",
 };
const char *text_FEB_08_2[POCET_JAZYKOV + 1] = 
{"Sv. Jozefíny Bakhity, panny",
 "Sv. Josefiny Bakhity, panny",
 "",
 "",
 "",
 "Sv. Josefiny Bakhity, panny",
 "Bakhita Szent Jozefina szûz",
 };
const char *text_FEB_09_SDB[POCET_JAZYKOV + 1] = 
{"Bl. Euzébie Palominovej Yenes, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_10[POCET_JAZYKOV + 1] = 
{"Sv. Školastiky, panny",
 "Sv. Scholastiky, panny",
 "",
 "S. Scholasticae, virg.",
 "",
 "Sv. Scholastiky, panny",
 "Szent Skolasztika szûz",
 };
const char *text_FEB_10_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Bl. Huga, opata z premonstrátského øádu",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_11[POCET_JAZYKOV + 1] = 
{"Prebl. Panny Márie Lurdskej",
 "Panny Marie Lurdské",
 "",
 "B. Mariae Virg. de Lourdes",
 "",
 "Panny Marie Lurdské",
 "A Lourdes-i Boldogságos Szûz Mária",
 };
const char *text_FEB_12_OP[POCET_JAZYKOV + 1] = 
{"Bl. Reginalda Orleánskeho, kòaza",
 "",
 "",
 "",
 "",
 "Bl. Reginalda z Orléansu, knìze",
 "",
 };
const char *text_FEB_13_OP[POCET_JAZYKOV + 1] = 
{"Bl. Jordána Saského, kòaza",
 "",
 "",
 "",
 "",
 "Bl. Jordána Saského, knìze",
 "",
 };
const char *text_FEB_14[POCET_JAZYKOV + 1] = 
{"Sv. Cyrila, mnícha, a sv. Metoda, biskupa,"HTML_LINE_BREAK"patrónov Európy", // (na Slovensku sa slávi 5. júla)
 "(slaví se 5. èervna)",
 "",
 "Ss. Cyrilli, monachi, et Methodii, ep.",
 "",
 "",
 "Szent Cirill szerzetes és Szent Metód püspök,"HTML_LINE_BREAK"Európa társvédõszentjei",
 };
const char *text_FEB_15_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Klaudia La Colombi&egrave;ra, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_15_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Bl. Bedøicha Bachsteina a druhù, muèedníkù",
 "",
 "",
 "",
 "Bl. Bedøicha Bachsteina a druhù, muèedníkù",
 "",
 };
const char *text_FEB_16_OP[POCET_JAZYKOV + 1] = 
{"Bl. Mikuláša Pagliu, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_17[POCET_JAZYKOV + 1] = 
{"Siedmich svätıch zakladate¾ov"HTML_LINE_BREAK"rehole Sluobníkov Panny Márie",
 "Sv. Alexia a druhù, øeholníkù",
 "",
 "Ss. Septem Fundatorum Ordinis Servorum B. Mariae Virg.",
 "",
 "Sv. Alexia a druhù, øeholníkù",
 "A szervita rend hét szent alapítója",
 };
const char *text_FEB_17_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Evermoda, biskupa z premonstrátského øádu",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_18_OP[POCET_JAZYKOV + 1] = 
{"Bl. Jána (Angelika) z Fiesole, kòaza",
 "",
 "",
 "",
 "",
 "Bl. Jana z Fiesole neboli fra Angelica, knìze",
 "",
 };
const char *text_FEB_19_OP[POCET_JAZYKOV + 1] = 
{"Bl. Alvara z Kordovy, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_20_OP[POCET_JAZYKOV + 1] = 
{"Bl. Krištofa z Milána, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_21[POCET_JAZYKOV + 1] = 
{"Sv. Petra Damianiho, biskupa a uèite¾a Cirkvi",
 "Sv. Petra Damianiho, biskupa a uèitele církve",
 "",
 "S. Petri Damiani, ep. et Eccl. doct.",
 "",
 "Sv. Petra Damianiho, biskupa a uèitele Církve",
 "Damiáni Szent Péter püspök és egyháztanító",
 };
const char *text_FEB_22[POCET_JAZYKOV + 1] = 
{"Katedra sv. Petra, apoštola",
 "Stolce svatého Petra, apoštola",
 "",
 "Cathedrae S. Petri, Apostoli",
 "",
 "Stolce svatého Petra, apoštola",
 "Szent Péter apostol székfoglalása",
 };
const char *text_FEB_23[POCET_JAZYKOV + 1] = 
{"Sv. Polykarpa, biskupa a muèeníka",
 "Sv. Polykarpa, biskupa a muèedníka",
 "",
 "S. Polycarpi, ep. et mart.",
 "",
 "Sv. Polykarpa, biskupa a muèedníka",
 "Szent Polikárp püspök és vértanú",
 };
const char *text_FEB_24_OP[POCET_JAZYKOV + 1] = 
{"Bl. Konštanca z Fabriana, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_FEB_25_SDB[POCET_JAZYKOV + 1] = 
{"Sv. Alojza Versigliu, biskupa, a Kalixta Caravaria, kòaza, "HTML_LINE_BREAK"prvıch saleziánskych muèeníkov",
 "",
 "",
 "",
 "",
 "",
 "",
 };

// --------------- 00 pohyblivé slávenia ---------------

const char *text_POPOLCOVA_STREDA[POCET_JAZYKOV + 1] = 
{"Popolcová streda",
 "Popeleèní støeda",
 "",
 "",
 "",
 "Popeleèní støeda",
 "Hamvazószerda",
 };

// --------------- 03 marec ---------------

const char *text_MAR_02_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Aneky Èeskej, panny, èlenky 2. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAR_04[POCET_JAZYKOV + 1] = 
{"Sv. Kazimíra",
 "Sv. Kazimíra",
 "",
 "S. Casimiri",
 "",
 "Sv. Kazimíra",
 "Szent Kázmér",
 };
const char *text_MAR_04_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Boldog Meszlényi Zoltán püspök és vértanú",
 };
const char *text_MAR_07[POCET_JAZYKOV + 1] = 
{"Sv. Perpetuy a Felicity, muèeníc",
 "Sv. Perpetuy a Felicity, muèednic",
 "",
 "Ss. Perpetuae et Felicitatis, mart.",
 "",
 "Sv. Perpetuy a Felicity, muèednic",
 "Szent Perpétua és Felicitász vértanúk",
 };
const char *text_MAR_08[POCET_JAZYKOV + 1] = 
{"Sv. Jána z Boha, reho¾níka",
 "Sv. Jana z Boha, øeholníka",
 "",
 "S. Ioannis a Deo, relig.",
 "",
 "Sv. Jana z Boha, øeholníka",
 "Istenes Szent János szerzetes",
 };
const char *text_MAR_09[POCET_JAZYKOV + 1] = 
{"Sv. Františky Rímskej, reho¾níèky",
 "Sv. Františky Øímské, øeholnice",
 "",
 "S. Franciscae Romanae, relig.",
 "",
 "Sv. Františky Øímské, øeholnice",
 "Római Szent Franciska szerzetesnõ",
 };
const char *text_MAR_10_SK[POCET_JAZYKOV + 1] = 
{"Vıroèie posviacky katedrálneho chrámu v Bratislave", // ToDo: 'sv. Martina z Tours', pod¾a Direktória 2012, str. 93
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAR_10_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Jana Ogilvie, knìze a muèedníka",
 "",
 "",
 "",
 "Sv. Jana Ogilvie, knìze a muèedníka",
 "",
 };
const char *text_MAR_12_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Angely Salawovej, panny, èlenky 3. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAR_15_CSSR[POCET_JAZYKOV + 1] = 
{"Sv. Klementa Márie Hofbauera, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAR_17[POCET_JAZYKOV + 1] = 
{"Sv. Patrika, biskupa",
 "Sv. Patrika, biskupa",
 "",
 "S. Patricii, ep.",
 "",
 "Sv. Patrika, biskupa",
 "Szent Patrik püspök",
 };
const char *text_MAR_17_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "A Gyõri könnyezõ Szûz Mária",
 };
const char *text_MAR_18[POCET_JAZYKOV + 1] = 
{"Sv. Cyrila Jeruzalemského, biskupa a uèite¾a Cirkvi",
 "Sv. Cyrila Jeruzalémského, biskupa a uèitele církve",
 "",
 "S. Cyrilli Hierosolymitani, ep. et Eccl. doct.",
 "",
 "Sv. Cyrila Jeruzalémského, biskupa a uèitele Církve",
 "Jeruzsálemi Szent Cirill püspök és egyháztanító",
 };
const char *text_MAR_18_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Salvatora z Horty, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAR_19[POCET_JAZYKOV + 1] = 
{"Sv. Jozefa, enícha Panny Márie",
 "Sv. Josefa, Snoubence Panny Marie",
 "",
 "S. Ioseph, Sponsi B. Mariae V.",
 "",
 "Sv. Josefa, Snoubence Panny Marie",
 "Szent József, a Boldogságos Szûz Mária jegyese",
 };
const char *text_MAR_23[POCET_JAZYKOV + 1] = 
{"Sv. Turibia de Mongrovejo, biskupa",
 "Sv. Turibia z Mongroveja, biskupa",
 "",
 "S. Turibii de Mogrovejo, ep.",
 "",
 "Sv. Turibia z Mongroveja, biskupa",
 "Mongrovejói Szent Turibiusz püspök",
 };
const char *text_MAR_25[POCET_JAZYKOV + 1] = 
{"Zvestovanie Pána",
 "Zvìstování Pánì",
 "",
 "In Annuntiatione Domini",
 "",
 "Zvìstování Pánì",
 "Urunk születésének hírüladása (Gyümölcsoltó Boldogasszony)",
 };

// --------------- 04 apríl ---------------

const char *text_APR_02[POCET_JAZYKOV + 1] = 
{"Sv. Františka z Paoly, pustovníka",
 "Sv. Františka z Pauly, poustevníka",
 "",
 "S. Francisci de Paola, eremitai",
 "",
 "Sv. Františka z Pauly, poustevníka",
 "Paolai Szent Ferenc remete",
 };
const char *text_APR_04[POCET_JAZYKOV + 1] = 
{"Sv. Izidora, biskupa a uèite¾a Cirkvi",
 "Sv. Izidora, biskupa a uèitele církve",
 "",
 "S. Isidori, ep. et Eccl. doct.",
 "",
 "Sv. Izidora, biskupa a uèitele Církve",
 "Szent Izidor püspök és egyháztanító",
 };
const char *text_APR_05[POCET_JAZYKOV + 1] = 
{"Sv. Vincenta Ferrera, kòaza",
 "Sv. Vincence Ferrerského, knìze",
 "",
 "S. Vincentii Ferrer, presb.",
 "",
 "Sv. Vincence Ferrerského, knìze",
 "Ferrer Szent Vince áldozópap",
 };
const char *text_APR_07[POCET_JAZYKOV + 1] = 
{"Sv. Jána Krstite¾a de la Salle, kòaza",
 "Sv. Jana Køtitele de la Salle, knìze",
 "",
 "S. Ioannis Baptistae de la Salle, presb.",
 "",
 "Sv. Jana Køtitele de la Salle, knìze",
 "De la Salle Szent János áldozópap",
 };
const char *text_APR_10_OP[POCET_JAZYKOV + 1] = 
{"Bl. Antona Neyrota, kòaza a muèeníka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_APR_11[POCET_JAZYKOV + 1] = 
{"Sv. Stanislava, biskupa a muèeníka",
 "Sv. Stanislava, biskupa a muèedníka",
 "",
 "S. Stanislai, ep. et mart.",
 "",
 "Sv. Stanislava, biskupa a muèedníka",
 "Szent Szaniszló püspök és vértanú",
 };
const char *text_APR_13[POCET_JAZYKOV + 1] = 
{"Sv. Martina I., pápea a muèeníka",
 "Sv. Martina I., papee a muèedníka",
 "",
 "S. Martini I, papae et mart.",
 "",
 "Sv. Martina I., papee a muèedníka",
 "Szent I. Márton pápa és vértanú",
 };
const char *text_APR_13_OP[POCET_JAZYKOV + 1] = 
{"Bl. Margity z Citt&agrave; di Castello, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_APR_14_OP[POCET_JAZYKOV + 1] = 
{"Bl. Petra Gonzáleza, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_APR_16[POCET_JAZYKOV + 1] = 
{"Sv. Márie Bernadety Soubirousovej, panny",
 "Sv. Marie Bernadetty Soubirous, panny",
 "",
 "S. Marii Bernadette Soubirous, virg.",
 "",
 "Sv. Marie Bernadetty Soubirous, panny",
 "Soubirous szent Mária Bernadett szûz",
 };
const char *text_APR_17_1_OP[POCET_JAZYKOV + 1] = 
{"Bl. Kláry Gambacortovej, reho¾níèky",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_APR_17_2_OP[POCET_JAZYKOV + 1] = 
{"Bl. Márie Manciniovej, reho¾níèky",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_APR_19_1_OP[POCET_JAZYKOV + 1] = 
{"Bl. Isnarda z Chiampa, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_APR_19_2_OP[POCET_JAZYKOV + 1] = 
{"Bl. Sybiliny Biscossiovej, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_APR_20_OP[POCET_JAZYKOV + 1] = 
{"Sv. Agnesy z Montepulciana, panny",
 "",
 "",
 "",
 "",
 "Sv. Aneky z Montepulciana, panny, mnišky",
 "",
 };
const char *text_APR_21[POCET_JAZYKOV + 1] = 
{"Sv. Anzelma, biskupa a uèite¾a Cirkvi",
 "Sv. Anselma, biskupa a uèitele církve",
 "",
 "S. Anselmi, ep. et Eccl. doct.",
 "",
 "Sv. Anselma, biskupa a uèitele Církve",
 "Szent Anzelm püspök és egyháztanító",
 };
const char *text_APR_21_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Konráda z Parzhamu, reho¾níka, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_APR_22_SJ[POCET_JAZYKOV + 1] = 
{"Prebl. Panny Márie, Matky Spoloènosti Jeišovej",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_APR_23[POCET_JAZYKOV + 1] = 
{"Sv. Vojtecha, biskupa a muèeníka",
 "Sv. Vojtìcha, biskupa a muèedníka",
 "",
 "S. Adalberti, ep. et mart.",
 "",
 "Sv. Vojtìcha, biskupa a muèedníka",
 "Szent Adalbert (Béla) püspök és vértanú",
 };
const char *text_APR_23_HU[POCET_JAZYKOV + 1] = 
{"Sv. Vojtecha, biskupa a muèeníka",
 "Sv. Vojtìcha, biskupa a muèedníka",
 "",
 "S. Adalberti, ep. et mart.",
 "",
 "Sv. Vojtìcha, biskupa a muèedníka",
 "Szent Adalbert (Béla) püspök és vértanú, az Esztergomi fõegyházmegye védõszentje",
 };
const char *text_APR_23_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Egida z Assisi, reho¾níka, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_APR_24_1[POCET_JAZYKOV + 1] = 
{"Sv. Juraja, muèeníka",
 "Sv. Jiøí, muèedníka",
 "",
 "S. Georgii, mart.",
 "",
 "Sv. Jiøí, muèedníka",
 "Szent György vértanú",
 };
const char *text_APR_24_2[POCET_JAZYKOV + 1] = 
{"Sv. Fidéla zo Sigmaringenu, kòaza a muèeníka",
 "Sv. Fidela ze Sigmaringy, knìze a muèedníka",
 "",
 "S. Fidelis a Sigmaringen, presb. et mart.",
 "",
 "Sv. Fidela ze Sigmaringy, knìze a muèedníka",
 "Sigmaringeni Szent Fidél áldozópap és vértanú",
 };
const char *text_APR_24_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Fidela zo Sigmaringenu, kòaza a muèeníka, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_APR_24_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Obrácení našeho otce svatého Augustina, biskupa a uèitele církve",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_APR_25[POCET_JAZYKOV + 1] = 
{"Sv. Marka, evanjelistu",
 "Sv. Marka, evangelisty",
 "",
 "S. Marci, evangelistae",
 "",
 "Sv. Marka, evangelisty",
 "Szent Márk evangelista",
 };
const char *text_APR_26_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Ludolfa, biskupa a muèedníka "HTML_LINE_BREAK"z premonstrátského øádu",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_APR_27_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Petra Kanízia, kòaza a uèite¾a Cirkvi",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_APR_27_OP[POCET_JAZYKOV + 1] = 
{"Bl. Hosanny Kotorskej, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_APR_28_1[POCET_JAZYKOV + 1] = 
{"Sv. Petra Chanela, kòaza a muèeníka",
 "Sv. Petra Chanela, knìze a muèedníka",
 "",
 "S. Petri Chanel, presb. et mart.",
 "",
 "Sv. Petra Chanela, knìze a muèedníka",
 "Chanel Szent Péter áldozópap és vértanú",
 };
const char *text_APR_28_2[POCET_JAZYKOV + 1] = 
{"Sv. ¼udovíta Márie Grignion de Montfort, kòaza",
 "Sv. Ludvíka Marie Grignona z Montfortu, knìze",
 "",
 "S. Ludovici M. Grignion de Montfort, presb.",
 "",
 "Sv. Ludvíka Marie Grignona z Montfortu, knìze, terciáøe",
 "Montforti Grignion Szent Lajos Mária áldozópap",
 };
const char *text_APR_29[POCET_JAZYKOV + 1] = 
{"Sv. Kataríny Sienskej, panny a uèite¾ky Cirkvi,"HTML_LINE_BREAK"patrónky Európy",
 "Sv. Kateøiny Sienské, panny a uèitelky církve,"HTML_LINE_BREAK"patronky Evropy",
 "",
 "S. Catharinae Senensis, virg. et Eccl. doct.",
 "",
 "Sv. Kateøiny Sienské, panny a uèitelky Církve,"HTML_LINE_BREAK"patronky Evropy, terciáøky",
 "Sienai Szent Katalin szûz és egyháztanító",
 };
const char *text_APR_30[POCET_JAZYKOV + 1] = 
{"Sv. Pia V., pápea",
 "Sv. Pia V., papee",
 "",
 "S. Pii V, papae",
 "",
 "Sv. Pia V., papee",
 "Szent V. Piusz pápa",
 };
const char *text_APR_30_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Zikmunda, muèedníka",
 "",
 "",
 "",
 "Sv. Zikmunda, muèedníka",
 "",
 };
const char *text_APR_30_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Benedikta z Urbina, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };

// --------------- 05 máj ---------------

const char *text_MAJ_01[POCET_JAZYKOV + 1] = 
{"Sv. Jozefa, robotníka",
 "Sv. Josefa, Dìlníka",
 "",
 "S. loseph Opificis",
 "",
 "Sv. Josefa, Dìlníka",
 "Munkás Szent József",
 };
const char *text_MAJ_02[POCET_JAZYKOV + 1] = 
{"Sv. Atanáza, biskupa a uèite¾a Cirkvi",
 "Sv. Atanáše, biskupa a uèitele církve",
 "",
 "S. Athanasii, ep. et Eccl. doct.",
 "",
 "Sv. Atanáše, biskupa a uèitele Církve",
 "Szent Atanáz püspök és egyháztanító",
 };
const char *text_MAJ_02_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Pøenesení sv. Norberta, našeho otce", // iba na Stahove
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_03[POCET_JAZYKOV + 1] = 
{"Sv. Filipa a Jakuba, apoštolov",
 "Sv. Filipa a Jakuba, apoštolù",
 "",
 "Ss. Philippi et Iacobi, apostolorum",
 "",
 "Sv. Filipa a Jakuba, apoštolù",
 "Szent Fülöp és Szent Jakab apostol",
 };
const char *text_MAJ_04_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Szent Flórián vértanú",
 };
const char *text_MAJ_04_SJ[POCET_JAZYKOV + 1] = 
{"Bl. Jozefa Márie Rubia, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_04_OP[POCET_JAZYKOV + 1] = 
{"Bl. Emílie Bicchieriovej, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_06_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Jana Sarkandra, knìze a muèedníka",
 "",
 "",
 "",
 "Sv. Jana Sarkandra, knìze a muèedníka",
 "",
 };
const char *text_MAJ_06_SDB[POCET_JAZYKOV + 1] = 
{"Sv. Dominika Savia, mladíka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_07_OP[POCET_JAZYKOV + 1] = 
{"Bl. Alberta z Bergama, otca rodiny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_07_HU_1[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Boldog Gizella királyné",
 };
const char *text_MAJ_07_HU_2[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Az Egri bazilika-fõszékesegyház",
 };
const char *text_MAJ_08_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Panny Marie, Prostøednice všech milostí",
 "",
 "",
 "",
 "Panny Marie, Prostøednice všech milostí",
 "",
 };
const char *text_MAJ_08_OP[POCET_JAZYKOV + 1] = 
{"Bl. Panny Márie, patrónky Rehole kazate¾ov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_08_OFM[POCET_JAZYKOV + 1] = 
{"Preblahoslavenej Panny Márie, Matky a Sprostredkovate¾ky milostí",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_08_2_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Ulriky Nischovej, panny, reho¾níèky, èlenky 3. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_08_3_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Jeremiáša z Valašska, reho¾níka, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_09_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Kataríny z Bologne, panny, èlenky 2. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_10_OP[POCET_JAZYKOV + 1] = 
{"Sv. Antonína Florentského, biskupa",
 "",
 "",
 "",
 "",
 "Sv. Antonína Pierozziho neboli Florentského, biskupa",
 "",
 };
const char *text_MAJ_11_SK[POCET_JAZYKOV + 1] = 
{"Bl. Sáry Salkaháziovej, panny a muèenice",
 "",
 "",
 "",
 "",
 "",
 "Boldog Salkaházi Sára szûz és vértanú",
 };
const char *text_MAJ_11_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Ignáca z Laconie, reho¾níka, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_11_OP[POCET_JAZYKOV + 1] = // vo všeobecnom kalendári pre OP sa slávi 13. mája
{"Bl. Imeldy Lambertiniovej, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_12_1[POCET_JAZYKOV + 1] = 
{"Sv. Nerea a Achila, muèeníkov",
 "Sv. Nerea a Achillea, muèedníkù",
 "",
 "Ss. Nerei et Achillei, mart.",
 "",
 "Sv. Nerea a Achillea, muèedníkù",
 "Szent Néreusz és Szent Achilleusz vértanúk",
 };
const char *text_MAJ_12_2[POCET_JAZYKOV + 1] = 
{"Sv. Pankráca, muèeníka",
 "Sv. Pankráce, muèedníka",
 "",
 "S. Pancratii, mart.",
 "",
 "Sv. Pankráce, muèedníka",
 "Szent Pongrác vértanú",
 };
const char *text_MAJ_12_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Vıroèí posvìcení katedrály sv. Víta",
 "",
 "",
 "",
 "Vıroèí posvìcení katedrály sv. Víta",
 "",
 };
const char *text_MAJ_12_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Leopolda Mandiæa, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_12_OP[POCET_JAZYKOV + 1] = 
{"Bl. Jany Portugalskej, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_13[POCET_JAZYKOV + 1] = 
{"Panny Márie Fatimskej",
 "Panny Marie Fatimské",
 "",
 "",
 "",
 "Panny Marie Fatimské",
 "A Fatimai Boldogságos Szûz Mária",
 };
const char *text_MAJ_13_SDB[POCET_JAZYKOV + 1] = 
{"Sv. Márie Dominiky Mazzarellovej, panny, "HTML_LINE_BREAK"spoluzakladate¾ky Inštitútu dcér Márie Pomocnice",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_13_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Petra Regalada, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_14[POCET_JAZYKOV + 1] = 
{"Sv. Mateja, apoštola",
 "Sv. Matìje, apoštola",
 "",
 "S. Matthiae, apostoli",
 "",
 "Sv. Matìje, apoštola",
 "Szent Mátyás apostol", // v HU sa slávi 24.2.
 };
const char *text_MAJ_15_CZOP[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "Panny Marie, ochránkynì Øádu bratøí kazatelù",
 "",
 };
const char *text_MAJ_15_1_OP[POCET_JAZYKOV + 1] = 
{"Bl. Egída z Vauzela, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_15_2_OP[POCET_JAZYKOV + 1] = 
{"Bl. Andreja Abellona, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_16_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Andreja Bobolu, kòaza a muèeníka", // text_MAJ_15_SJ: na Slovensku sa slávi 15. mája
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_16[POCET_JAZYKOV + 1] = 
{"Sv. Jána Nepomuckého, kòaza a muèeníka",
 "Sv. Jana Nepomuckého, knìze a muèedníka, "HTML_LINE_BREAK"hlavního patrona Èech",
 "",
 "",
 "",
 "Sv. Jana Nepomuckého, knìze a muèedníka, "HTML_LINE_BREAK"hlavního patrona Èech",
 "Nepomuki Szent János áldozópap és vértanú",
 };
const char *text_MAJ_16_SDB[POCET_JAZYKOV + 1] = 
{"Sv. Alojza Orioneho, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_16_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Margity z Cortony, kajúcnice, èlenky 3. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_17_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Paschala Baylona, reho¾níka, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_17_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Boldog Scheffler János püspök és vértanú",
 };
const char *text_MAJ_18[POCET_JAZYKOV + 1] = 
{"Sv. Jána I., pápea a muèeníka",
 "Sv. Jana I., papee a muèedníka",
 "",
 "S. Ioannis I, papae et mart.",
 "",
 "Sv. Jana I., papee a muèedníka",
 "Szent I. János pápa és vértanú",
 };
const char *text_MAJ_18_SDB[POCET_JAZYKOV + 1] = 
{"Sv. Leonarda Murialda, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_18_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Felixa z Cantalicie, reho¾níka, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_19_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Krišpína z Viterba, reho¾níka, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_19_OP[POCET_JAZYKOV + 1] = 
{"Bl. Františka Colla Guitarta, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_20_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Klementa Marie Hofbauera, knìze",
 "",
 "",
 "",
 "Sv. Klementa Marie Hofbauera, knìze",
 "",
 };
const char *text_MAJ_20[POCET_JAZYKOV + 1] = 
{"Sv. Bernardína Sienského, kòaza",
 "Sv. Bernardina Sienského, knìze",
 "",
 "S. Bernardini Senensis, presb.",
 "",
 "Sv. Bernardina Sienského, knìze",
 "Sienai Szent Bernardin áldozópap",
 };
const char *text_MAJ_20_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Bernardína Sienského, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_20_OP[POCET_JAZYKOV + 1] = 
{"Bl. Kolumby z Rieti, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_21_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Vıroèí posvìcení katedrály sv. Petra a Pavla",
 "",
 "",
 "",
 "Vıroèí posvìcení katedrály sv. Petra a Pavla",
 "",
 };
const char *text_MAJ_21[POCET_JAZYKOV + 1] = 
{"Sv. Krištofa Magallanesa, kòaza, a spoloèníkov, muèeníkov",
 "Sv. Kryštofa Magallanese, knìze a druhù, muèedníkù",
 "",
 "",
 "",
 "Sv. Kryštofa Magallanese, knìze a druhù, muèedníkù",
 "Magallán Szent Kristóf áldozópap és társai, mexikói vértanúk",
 };
const char *text_MAJ_21_OP[POCET_JAZYKOV + 1] = 
{"Bl. Hyacinta Márie Cormiera, kòaza",
 "",
 "",
 "",
 "",
 "Bl. Hyacinta Marie Cormiera, knìze",
 "",
 };
const char *text_MAJ_22[POCET_JAZYKOV + 1] = 
{"Sv. Rity z Kassie, reho¾níèky",
 "Sv. Rity z Cascie, øeholnice",
 "",
 "",
 "",
 "Sv. Rity z Cascie, øeholnice",
 "Szent Rita szerzetesnõ",
 };
const char *text_MAJ_23_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Boldog Apor Vilmos püspök és vértanú",
 };
const char *text_MAJ_24_OP[POCET_JAZYKOV + 1] = 
{"Prenesenie pozostatkov sv. otca Dominika",
 "",
 "",
 "",
 "",
 "Pøenesení ostatkù sv. Otce Dominika",
 "",
 };
const char *text_MAJ_24_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Heømana Josefa, knìze z premonstrátského øádu",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_24_OFM[POCET_JAZYKOV + 1] = 
{"Vıroèie posviacky Baziliky sv. Františka v Assisi",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_24[POCET_JAZYKOV + 1] = 
{"Panny Márie, Pomocnice kresanov, "HTML_LINE_BREAK"hlavnej patrónky Inštitútu dcér Márie Pomocnice "HTML_LINE_BREAK"a celej saleziánskej rodiny",
 "",
 "",
 "",
 "",
 "",
 "Szûz Mária, a keresztények segítsége",
 };
const char *text_MAJ_25_1[POCET_JAZYKOV + 1] = 
{"Sv. Bédu Ctihodného, kòaza a uèite¾a Cirkvi",
 "Sv. Bedy Ctihodného, knìze a uèitele církve",
 "",
 "S. Bedae Venerdbilis, presb. et Ecci. doct.",
 "",
 "Sv. Bedy Ctihodného, knìze a uèitele Církve",
 "Tiszteletreméltó Szent Béda áldozópap és egyháztanító",
 };
const char *text_MAJ_25_2[POCET_JAZYKOV + 1] = 
{"Sv. Gregora VII., pápea",
 "Sv. Øehoøe VII., papee",
 "",
 "S. Gregorii VII, papae",
 "",
 "Sv. Øehoøe VII., papee",
 "Szent VII. Gergely pápa",
 };
const char *text_MAJ_25_3[POCET_JAZYKOV + 1] = 
{"Sv. Márie Magdalény de’ Pazzi, panny",
 "Sv. Marie Magdalény de’ Pazzi, panny",
 "",
 "S. Mariae Magdalenae de’ Pazzi, virg.",
 "",
 "Sv. Marie Magdalény de’ Pazzi, panny",
 "Pazzi Szent Mária Magdolna Szûz",
 };
const char *text_MAJ_26[POCET_JAZYKOV + 1] = 
{"Sv. Filipa Neriho, kòaza",
 "Sv. Filipa Neriho, knìze",
 "",
 "S. Philippi Neri, presb.",
 "",
 "Sv. Filipa Neriho, knìze",
 "Néri Szent Fülöp áldozópap",
 };
const char *text_MAJ_27[POCET_JAZYKOV + 1] = 
{"Sv. Augustína z Canterbury, biskupa",
 "Sv. Augustina z Canterbury, biskupa",
 "",
 "S. Augustini Cantuariensis, ep.",
 "",
 "Sv. Augustina z Canterbury, biskupa",
 "Canterbury Szent Ágoston püspök",
 };
const char *text_MAJ_27_OP[POCET_JAZYKOV + 1] = 
{"Bl. Andreja Franchiho, biskupa",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_28_OP[POCET_JAZYKOV + 1] = 
{"Bl. Márie Bartolomey Bagnesiovej, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_29_OP[POCET_JAZYKOV + 1] = 
{"Bl. Viliama Arnauda, kòaza, a spoloèníkov, muèeníkov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_29_SDB[POCET_JAZYKOV + 1] = 
{"Bl. Jozefa Kowalského, muèeníka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_30_OP[POCET_JAZYKOV + 1] = 
{"Bl. Jakuba Salomoniho, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_MAJ_30_CZ[POCET_JAZYKOV + 1] = 
{"Sv. Zdislavy, matky rodiny", // SK OP
 "Sv. Zdislavy",
 "",
 "",
 "",
 "Sv. Zdislavy z Lemberka, matky rodiny, terciáøky,"HTML_LINE_BREAK"spolupatronky provincie",
 "",
 };
const char *text_MAJ_30_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Szent István király ereklyéinek átvitele",
 };
const char *text_MAJ_31[POCET_JAZYKOV + 1] = 
{"Navštívenie prebl. Panny Márie",
 "Navštívení Panny Marie",
 "",
 "",
 "",
 "Navštívení Panny Marie",
 "Szûz Mária látogatása Erzsébetnél"HTML_LINE_BREAK"(Sarlós Boldogasszony)",
 };

// --------------- 00 pohyblivé slávenia ---------------

const char *text_NANEBOVSTUPENIE_PANA[POCET_JAZYKOV + 1] = 
{"Nanebovstúpenie Pána",
 "Nanebevstoupení Pánì",
 "",
 "",
 "",
 "Nanebevstoupení Pánì",
 "Urunk mennybemenetele",
 };
const char *text_VELKONOCNA_NEDELA[POCET_JAZYKOV + 1] = 
{"Ve¾konoèná nede¾a",
 "Nedìle Zmrtvıchvstání Pánì",
 "",
 "",
 "",
 "Nedìle Zmrtvıchvstání Pánì",
 "Húsvétvasárnap",
 };
const char *text_NEDELA_PANOVHO_ZMRTVYCHVSTANIA[POCET_JAZYKOV + 1] = // 2012-12-13: XML nepodporuje &mdash; -- pouitı èíselnı kód &#8212; http://en.wikipedia.org/wiki/List_of_XML_and_HTML_character_entity_references
{HTML_LINE_BREAK" &#8212; Nede¾a Pánovho zmàtvychvstania",
 "",
 "",
 "",
 "",
 "",
 ", Krisztus feltámadása",
 };
const char *text_NEDELA_VO_VELKONOCNEJ_OKTAVE[POCET_JAZYKOV + 1] = 
{"Nede¾a vo Ve¾konoènej oktáve",
 "Nedìle v oktávu velikonoèním",
 "",
 "",
 "",
 "Nedìle v oktávu velikonoèním",
 "Vasárnap Húsvét nyolcadában",
 };
const char *text_DEN_VO_VELKONOCNEJ_OKTAVE[POCET_JAZYKOV + 1] = 
{"Ve¾konoèn%c %s",
 "%s velikonoèní",
 "",
 "",
 "",
 "%s velikonoèní",
 "%s Húsvét nyolcadában",
 };

const char *text_HU_VELKONOCNY_PONDELOK = "Húsvéthétfõ"; // pre HU špeciálny názov ve¾konoèného pondelka

const char *text_HU_VELKY_TYZDEN_PREFIX = "Nagy"; // pre HU špeciálne názvy dní ve¾kného tıdòa (pondelok a streda)

const char *text_NAJSVATEJSEJ_TROJICE[POCET_JAZYKOV + 1] = 
{"Najsvätejšej Trojice",
 "Nejsvìtìjší Trojice",
 "",
 "",
 "",
 "Nejsvìtìjší Trojice",
 "Szentháromságvasárnap",
 };
const char *text_KRISTA_KRALA[POCET_JAZYKOV + 1] = 
{"Krista Krá¾a",
 "Jeíše Krista Krále",
 "",
 "",
 "",
 "Jeíše Krista Krále",
 "Krisztus Király",
 };
const char *text_NAJSV_KRISTOVHO_TELA_A_KRVI[POCET_JAZYKOV + 1] = 
{"Najsvätejšieho Kristovho tela a krvi",
 "Tìla a krve Pánì",
 "",
 "",
 "",
 "Tìla a krve Pánì",
 "Krisztus Szent Teste és Vére",
 };
const char *text_NAJSV_SRDCA_JEZISOVHO[POCET_JAZYKOV + 1] = 
{"Najsvätejšieho Srdca Jeišovho",
 "Nejsvìtìjšího Srdce Jeíšova",
 "",
 "",
 "",
 "Nejsvìtìjšího Srdce Jeíšova",
 "Jézus Szent Szíve",
 };
const char *text_NEPOSKVRNENEHO_SRDCA_PM[POCET_JAZYKOV + 1] = 
{"Nepoškvrneného Srdca Panny Márie", // 2010-06-16: opravenı názov pod¾a breviára i direktória
 "Neposkvrnìného Srdce Panny Marie",
 "",
 "",
 "",
 "Neposkvrnìného Srdce Panny Marie",
 "A Boldogságos Szûz Mária Szeplõtelen Szíve",
 };
const char *text_NEPOSKVRNENEHO_SRDCA_PM_OFM[POCET_JAZYKOV + 1] = 
{"Nepoškvrneného Srdca Panny Márie, "HTML_LINE_BREAK"patrónky slovenskej provincie Rádu menších bratov kapucínov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NARODENIE_PANA[POCET_JAZYKOV + 1] = 
{"Narodenie Pána",
 "Narození Pánì",
 "",
 "",
 "",
 "Narození Pánì",
 "Urunk születése (Karácsony)",
 };
const char *text_ZOSLANIE_DUCHA_SVATEHO[POCET_JAZYKOV + 1] = 
{"Zoslanie Ducha Svätého",
 "Seslání Ducha svatého",
 "",
 "",
 "",
 "Seslání Ducha Svatého",
 "Pünkösd",
 };
const char *text_PRVA_ADVENTNA_NEDELA[POCET_JAZYKOV + 1] = 
{"Prvá adventná nede¾a",
 "První nedìle adventní",
 "",
 "",
 "",
 "První nedìle adventní",
 "Advent elsõ vasárnapja",
 };
const char *text_NEDELA_SV_RODINY[POCET_JAZYKOV + 1] = 
{"Svätej rodiny Jeiša, Márie a Jozefa",
 "Sv. Rodiny Jeíše, Marie a Josefa",
 "",
 "",
 "",
 "Sv. Rodiny Jeíše, Marie a Josefa",
 "A Szent család: Jézus, Mária és József", // "Szent Család ünnepe"
 };
const char *text_SPOMIENKA_PM_V_SOBOTU[POCET_JAZYKOV + 1] = 
{"Spomienka Panny Márie v sobotu",
 "Sobotní památka Panny Marie",
 "",
 "Memoria S. Mariae in sabbato",
 "",
 "Sobotní památka Panny Marie",
 "Szûz Mária szombati emléknapja",
 };

// --------------- 06 jún ---------------

const char *text_JUN_01[POCET_JAZYKOV + 1] = 
{"Sv. Justína, muèeníka",
 "Sv. Justina, muèedníka",
 "",
 "",
 "",
 "Sv. Justina, muèedníka",
 "Szent Jusztínusz vértanú",
 };
const char *text_JUN_02[POCET_JAZYKOV + 1] = 
{"Sv. Marcelína a Petra, muèeníkov",
 "Sv. Marcelina a Petra, muèedníkù",
 "",
 "",
 "",
 "Sv. Marcelina a Petra, muèedníkù",
 "Szent Marcellínusz és Szent Péter vértanúk",
 };
const char *text_JUN_02_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Felixa z Nikózie, reho¾níka, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_02_OP[POCET_JAZYKOV + 1] = 
{"Bl. Sadoka, kòaza, a spoloèníkov, muèeníkov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_03[POCET_JAZYKOV + 1] = 
{"Sv. Karola Lwangu a spoloèníkov, muèeníkov",
 "Sv. Karla Lwangy a druhù, muèedníkù",
 "",
 "",
 "",
 "Sv. Karla Lwangy a druhù, muèedníkù",
 "Lwanga Szent Károly és társai, vértanúk",
 };
const char *text_JUN_04_OP[POCET_JAZYKOV + 1] = 
{"Sv. Petra Veronského, kòaza a muèeníka",
 "",
 "",
 "",
 "",
 "Sv. Petra Veronského, knìze a muèedníka",
 "",
 };
const char *text_JUN_04_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Szent Quirinus (Kerény) püspök és vértanú",
 };
const char *text_JUN_05[POCET_JAZYKOV + 1] = 
{"Sv. Bonifáca, biskupa a muèeníka",
 "Sv. Bonifáce, biskupa a muèedníka",
 "",
 "",
 "",
 "Sv. Bonifáce, biskupa a muèedníka",
 "Szent Bonifác püspök és vértanú",
 };
const char *text_JUN_06[POCET_JAZYKOV + 1] = 
{"Sv. Norberta, biskupa",
 "Sv. Norberta, biskupa",
 "",
 "",
 "",
 "Sv. Norberta, biskupa",
 "Szent Norbert püspök",
 };
const char *text_JUN_06_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Našeho otce sv. Norberta, biskupa "HTML_LINE_BREAK"a zakladatele premonstrátského øádu",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_08_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Prágai szent Ágnes szûz",
 };
const char *text_JUN_08_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Mikuláša z Gesturi, reho¾níka, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_08_OP[POCET_JAZYKOV + 1] = 
{"Bl. Diany a Cecílie, panien",
 "",
 "",
 "",
 "",
 "Bl. Diany Andalo a Cecílie, panen, mnišek",
 "",
 };
const char *text_JUN_09[POCET_JAZYKOV + 1] = 
{"Sv. Efréma, diakona a uèite¾a Cirkvi",
 "Sv. Efréma Syrského, jáhna a uèitele církve",
 "",
 "",
 "",
 "Sv. Efréma Syrského, jáhna a uèitele Církve",
 "Szent Efrém diakónus és egyháztanító",
 };
const char *text_JUN_09_SJ[POCET_JAZYKOV + 1] = 
{"Bl. Jozefa de Anchieta, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_10_OP[POCET_JAZYKOV + 1] = 
{"Bl. Jána Dominiciho, biskupa",
 "",
 "",
 "",
 "",
 "Bl. Jana Dominiciho, biskupa",
 "",
 };
const char *text_JUN_11[POCET_JAZYKOV + 1] = 
{"Sv. Barnabáša, apoštola",
 "Sv. Barnabáše, apoštola",
 "",
 "",
 "",
 "Sv. Barnabáše, apoštola",
 "Szent Barnabás apostol",
 };
const char *text_JUN_12_SDB[POCET_JAZYKOV + 1] = 
{"Bl. Františka K&#281;syho a spoloèníkov, muèeníkov", // Bl. Františka Kesyho a spoloèníkov, muèeníkov (small latin letter e with ogonek)
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_12_OP[POCET_JAZYKOV + 1] = 
{"Bl. Štefana Bandelliho, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_12_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Jolandy Uhorskej, reho¾níèky, èlenky 2. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_12_2_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Floridy Cevoliovej, panny, èlenky 2. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_12_3_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Antona Bajewského a spoloèníkov, muèeníkov: "HTML_LINE_BREAK"Pia Bartošika, Inocenta Guza, Achilla Puchalu, Hermana St&#281;npie&nacute;a, kòazov; "HTML_LINE_BREAK"Timoteja Trojanowského, Bonifáca &#379;ukowského, reho¾níkov, èlenov 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_13_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Antona Paduánskeho, kòaza a uèite¾a Cirkvi, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_13[POCET_JAZYKOV + 1] = 
{"Sv. Antona Paduánskeho, kòaza a uèite¾a Cirkvi",
 "Sv. Antonína z Padovy, knìze a uèitele církve",
 "",
 "",
 "",
 "Sv. Antonína z Padovy, knìze a uèitele Církve",
 "Páduai Szent Antal áldozópap és egyháztanító",
 };
const char *text_JUN_14_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "A Szombathelyi székesegyház felszentelése",
 };
const char *text_JUN_15_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Víta, muèedníka",
 "",
 "",
 "",
 "Sv. Víta, muèedníka",
 "",
 };
const char *text_JUN_15_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Árpád-házi boldog Jolán szerzetesnõ",
 };
const char *text_JUN_16_SK[POCET_JAZYKOV + 1] = 
{"Sv. Neita, muèeníka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_16_1_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Márie Terézie Schererovej, panny, reho¾níèky, èlenky 3. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_16_2_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Aniceta Koplina, kòaza, a spoloèníkov, muèeníkov, èlenov 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_16_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Bl. Marie Antoníny Kratochvílové, muèednice",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_16_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Isfrída, biskupa z premonstrátského øádu",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_16_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Tours-i szent Márton püspök ereklyéinek átvitele",
 };
const char *text_JUN_17_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Alberta Chmielowského, reho¾níka, èlena 3. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_18_OP[POCET_JAZYKOV + 1] = 
{"Bl. Hosanny z Mantovy, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_19[POCET_JAZYKOV + 1] = 
{"Sv. Romualda, opáta",
 "Sv. Romualda, opata",
 "",
 "",
 "",
 "Sv. Romualda, opata",
 "Szent Romuald apát",
 };
const char *text_JUN_19_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Jana Nepomuckého Neumanna, biskupa",
 "",
 "",
 "",
 "Sv. Jana Nepomuckého Neumanna, biskupa",
 "",
 };
const char *text_JUN_21[POCET_JAZYKOV + 1] = 
{"Sv. Alojza Gonzágu, reho¾níka",
 "Sv. Aloise Gonzagy, øeholníka",
 "",
 "",
 "",
 "Sv. Aloise Gonzagy, øeholníka",
 "Gonzága Szent Alajos szerzetes",
 };
const char *text_JUN_21_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Alojza Gonzagu, reho¾níka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_22_2[POCET_JAZYKOV + 1] = 
{"Sv. Pavlína z Noly, biskupa",
 "Sv. Paulina Nolánského, biskupa",
 "",
 "",
 "",
 "Sv. Paulina Nolánského, biskupa",
 "Nolai Szent Paulínusz püspök",
 };
const char *text_JUN_22_1[POCET_JAZYKOV + 1] = 
{"Sv. Jána Fishera, biskupa,"HTML_LINE_BREAK"a sv. Tomáša Morusa, muèeníkov", // kedysi: Mórusa; Direktórium 2012, str. 156, uvádza u iba s krátkym "o"
 "Sv. Jana Fishera, biskupa,"HTML_LINE_BREAK"a Tomáše Mora, muèedníkù",
 "",
 "",
 "",
 "Sv. Jana Fishera, biskupa,"HTML_LINE_BREAK"a Tomáše Mora, muèedníkù",
 "Fisher Szent János püspök"HTML_LINE_BREAK"és Morus Szent Tamás vértanúk",
 };
const char *text_JUN_22_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "A Pécsi székesegyház felszentelése",
 };
const char *text_JUN_23_SDB[POCET_JAZYKOV + 1] = 
{"Sv. Jozefa Cafassa, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_23_OP[POCET_JAZYKOV + 1] = 
{"Bl. Inocenta V., pápea",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_24[POCET_JAZYKOV + 1] = 
{"Narodenie sv. Jána Krstite¾a",
 "Narození svatého Jana Køtitele",
 "",
 "",
 "",
 "Narození svatého Jana Køtitele",
 "Keresztelõ Szent János születése",
 };
const char *text_JUN_26_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Andreja Hyacinta Longina, biskupa, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_27[POCET_JAZYKOV + 1] = 
{"Sv. Cyrila Alexandrijského, biskupa a uèite¾a Cirkvi",
 "Sv. Cyrila Alexandrijského, biskupa a uèitele církve",
 "",
 "",
 "",
 "Sv. Cyrila Alexandrijského, biskupa a uèitele církve",
 "Alexandriai szent Cirill püspök és egyháztanító", // HU: 26JUN
 };
const char *text_JUN_27_SK_HU[POCET_JAZYKOV + 1] = 
{"Sv. Ladislava",
 "",
 "",
 "",
 "",
 "",
 "Szent László király",
 };
const char *text_JUN_27_CSSR[POCET_JAZYKOV + 1] = 
{"Panny Márie, Matky ustaviènej pomoci",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUN_28[POCET_JAZYKOV + 1] = 
{"Sv. Ireneja, biskupa a muèeníka",
 "Sv. Ireneje, biskupa a muèedníka",
 "",
 "",
 "",
 "Sv. Ireneje, biskupa a muèedníka",
 "Szent Iréneusz püspök és vértanú",
 };
const char *text_JUN_29[POCET_JAZYKOV + 1] = 
{"Sv. Petra a Pavla, apoštolov",
 "Sv. Petra a Pavla, apoštolù",
 "",
 "",
 "",
 "Sv. Petra a Pavla, apoštolù",
 "Szent Péter és Szent Pál apostolok",
 };
const char *text_JUN_30[POCET_JAZYKOV + 1] = 
{"Prvıch svätıch muèeníkov Cirkvi v Ríme",
 "Svatıch prvomuèedníkù øímskıch",
 "",
 "",
 "",
 "Svatıch prvomuèedníkù øímskıch",
 "A római Egyház elsõ szent vértanúi",
 };
const char *text_JUN_30_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Vıroèí posvìcení katedrály sv. Václava",
 "",
 "",
 "",
 "Vıroèí posvìcení katedrály sv. Václava",
 "",
 };
const char *text_JUN_30_CSSR[POCET_JAZYKOV + 1] = 
{"Bl. Januára Márie Sarnelliho, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };

// --------------- 07 júl ---------------

const char *text_JUL_02_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Bernardína Realina, sv. Jána Františka Régisa, sv. Františka de Geronimo, "HTML_LINE_BREAK"bl. Juliána Maunoira, bl. Antona Baldinucciho, kòazov", // text_JUL_01_SJ: na Slovensku sa slávi 1. júla
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_03[POCET_JAZYKOV + 1] = 
{"Sv. Tomáša, apoštola",
 "Sv. Tomáše, apoštola",
 "",
 "",
 "",
 "Sv. Tomáše, apoštola",
 "Szent Tamás apostol",
 };
const char *text_JUL_04[POCET_JAZYKOV + 1] = 
{"Sv. Albety Portugalskej",
 "Sv. Albìty Portugalské",
 "",
 "",
 "",
 "Sv. Albìty Portugalské",
 "Portugáliai Szent Erzsébet",
 };
const char *text_JUL_04_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Prokopa, opata",
 "",
 "",
 "",
 "Sv. Prokopa, opata",
 "",
 };
const char *text_JUL_04_1_OP[POCET_JAZYKOV + 1] = 
{"Bl. Kataríny Jarrigeovej, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_04_2_OP[POCET_JAZYKOV + 1] = 
{"Bl. Petra Juraja Frassatiho, laika",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_05[POCET_JAZYKOV + 1] = 
{"Sv. Cyrila a Metoda, slovanskıch vierozvestov",
 "Sv. Cyrila, mnicha, a Metodìje, biskupa, "HTML_LINE_BREAK"patronù Evropy, hlavních patronù Moravy",
 "",
 "",
 "",
 "Sv. Cyrila, mnicha, a Metodìje, biskupa, "HTML_LINE_BREAK"patronù Evropy, hlavních patronù Moravy",
 "",
 };
const char *text_JUL_06[POCET_JAZYKOV + 1] = 
{"Sv. Márie Goretti, panny a muèenice",
 "Sv. Marie Gorettiové, panny a muèednice",
 "",
 "",
 "",
 "Sv. Marie Gorettiové, panny a muèednice",
 "Goretti Szent Mária szûz és vértanú",
 };
const char *text_JUL_06_CZOP[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "Blaholaveného Pier Giorgio Frassatiho, laika OP",
 "",
 };
const char *text_JUL_07_SK[POCET_JAZYKOV + 1] = // vo všeobecnom kalendári sa slávi 5. júla
{"Sv. Antona Márie Zaccariu, kòaza",
 "",
 "",
 "",
 "",
 "",
 "Zaccaria szent Antal Mária áldozópap",
 };
const char *text_JUL_07_SDB[POCET_JAZYKOV + 1] = 
{"Bl. Márie Romerovej Meneses, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_07_OP[POCET_JAZYKOV + 1] = 
{"Bl. Benedikta XI., pápea",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_08_OP[POCET_JAZYKOV + 1] = 
{"Bl. Hadriána Fortescuea, otca rodiny a muèeníka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_08_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "A Székesegyház felszentelése",
 };
const char *text_JUL_09[POCET_JAZYKOV + 1] = 
{"Sv. Augustína Zhao Rong, kòaza,"HTML_LINE_BREAK"a spoloèníkov, muèeníkov",
 "Sv. Augustina ao Ronga, knìze"HTML_LINE_BREAK"a jeho druhù, muèedníkù",
 "",
 "",
 "",
 "Sv. Augustina ao Ronga, knìze"HTML_LINE_BREAK"a jeho druhù, muèedníkù",
 "Szent Zhao Rong Ágoston áldozópap és társai, kínai vértanúk",
 };
const char *text_JUL_09_OP[POCET_JAZYKOV + 1] = 
{"Sv. Jána Kolínskeho, kòaza, a spoloèníkov, muèeníkov",
 "",
 "",
 "",
 "",
 "Sv. Jana Kolínského, knìze, a druhù, muèedníkù",
 "",
 };
const char *text_JUL_09_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Mikuláša Picka, Antona von Willehada a spoloèníkov, "HTML_LINE_BREAK"muèeníkov v Holandsku, èlenov 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_09_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Adriána a Jakuba, knìí premonstrátského øádu, "HTML_LINE_BREAK"a jejich druhù, muèedníkù Gorkumskıch",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_10_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Veroniky Giulianiovej, panny, èlenky 2. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_11[POCET_JAZYKOV + 1] = 
{"Sv. Benedikta, opáta,"HTML_LINE_BREAK"patróna Európy",
 "Sv. Benedikta, opata,"HTML_LINE_BREAK"patrona Evropy",
 "",
 "",
 "",
 "Sv. Benedikta, opata,"HTML_LINE_BREAK"patrona Evropy",
 "Szent Benedek apát,"HTML_LINE_BREAK"Európa fõvédõszentje",
 };
const char *text_JUL_13[POCET_JAZYKOV + 1] = 
{"Sv. Henricha",
 "Sv. Jindøicha",
 "",
 "",
 "",
 "Sv. Jindøicha",
 "Szent Henrik",
 };
const char *text_JUL_13_OP[POCET_JAZYKOV + 1] = 
{"Bl. Jakuba z Varazze, biskupa",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_14[POCET_JAZYKOV + 1] = 
{"Sv. Kamila de Lellis, kòaza",
 "Sv. Kamila de Lellis, knìze",
 "",
 "",
 "",
 "Sv. Kamila de Lellis, knìze",
 "Lellisi Szent Kamill áldozópap",
 };
const char *text_JUL_14_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Františka Solanského, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_14_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Bl. Hroznaty, muèedníka",
 "",
 "",
 "",
 "Bl. Hroznaty, muèedníka",
 "",
 };
const char *text_JUL_14_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Bl. Hroznaty, muèedníka z premonstrátského øádu",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_15[POCET_JAZYKOV + 1] = 
{"Sv. Bonaventúru, biskupa a uèite¾a Cirkvi",
 "Sv. Bonaventury, biskupa a uèitele církve",
 "",
 "",
 "",
 "Sv. Bonaventury, biskupa a uèitele Církve",
 "Szent Bonaventura püspök és egyháztanító",
 };
const char *text_JUL_15_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Bonaventúru z Bagnoregia, biskupa a uèite¾a Cirkvi, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_16[POCET_JAZYKOV + 1] = 
{"Prebl. Panny Márie Karmelskej",
 "Panny Marie Karmelské",
 "",
 "",
 "",
 "Panny Marie Karmelské",
 "Kármel-hegyi Boldogasszony",
 };
const char *text_JUL_16_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Vıroèí posvìcení katedrály Boského Spasitele",
 "",
 "",
 "",
 "Vıroèí posvìcení katedrály Boského Spasitele",
 "",
 };
const char *text_JUL_17_SK[POCET_JAZYKOV + 1] = 
{"Sv. Andreja-Svorada a Benedikta, pustovníkov",
 "",
 "",
 "",
 "",
 "",
 "Szent Zoerárd-András és Benedek remeték",
 };
const char *text_JUL_17_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Bl. Èeslava a sv. Hyacinta, knìí",
 "",
 "",
 "",
 "Bl. Èeslava a sv. Hyacinta, knìí",
 "",
 };
const char *text_JUL_17_OP[POCET_JAZYKOV + 1] = 
{"Bl. Èeslava Po¾ského, kòaza",
 "",
 "",
 "",
 "",
 "Bl. Èeslava z Polska, knìze",
 "",
 };
const char *text_JUL_18_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Szent Hedvig királyné",
 };
const char *text_JUL_18_OP[POCET_JAZYKOV + 1] = 
{"Bl. Bartolomeja od Muèeníkov, biskupa",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_18_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Šimona z Lipnice, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_19_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Jána z Dukly, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_20[POCET_JAZYKOV + 1] = 
{"Sv. Apolinára, biskupa a muèeníka",
 "Sv. Apolináøe, biskupa a muèedníka",
 "",
 "",
 "",
 "Sv. Apolináøe, biskupa a muèedníka",
 "Szent Apollinaris püspök és vértanú",
 };
const char *text_JUL_21[POCET_JAZYKOV + 1] = 
{"Sv. Vavrinca z Brindisi, kòaza a uèite¾a Cirkvi",
 "Sv. Vavøince z Brindisi, knìze a uèitele církve",
 "",
 "",
 "",
 "Sv. Vavøince z Brindisi, knìze a uèitele Církve",
 "Brindisi Szent Lõrinc Áldozópap és egyháztanító",
 };
const char *text_JUL_21_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Vavrinca z Brindisi, kòaza a uèite¾a Cirkvi, èlena 1. rádu",
 "Sv. Vavøince z Brindisi, knìze a uèitele církve, èlena 1. øádu",
 "",
 "",
 "",
 "Sv. Vavøince z Brindisi, knìze a uèitele Církve, èlena 1. øádu",
 "Brindisi Szent Lõrinc Áldozópap és egyháztanító",
 };
const char *text_JUL_22[POCET_JAZYKOV + 1] = 
{"Sv. Márie Magdalény",
 "Sv. Marie Magdalény",
 "",
 "",
 "",
 "Sv. Marie Magdalény",
 "Szent Mária Magdolna",
 };
const char *text_JUL_23[POCET_JAZYKOV + 1] = 
{"Sv. Brigity, reho¾níèky,"HTML_LINE_BREAK"patrónky Európy",
 "Sv. Brigity, øeholnice,"HTML_LINE_BREAK"patronky Evropy",
 "",
 "",
 "",
 "Sv. Brigity, øeholnice,"HTML_LINE_BREAK"patronky Evropy",
 "Szent Brigitta szerzetesnõ",
 };
const char *text_JUL_24[POCET_JAZYKOV + 1] = 
{"Sv. Sarbela Makhlufa, kòaza", // 2009-07-15: direktórium (2012, str. 171) má "Sarbel", predtım bolo "Charbel" a zrejme sa èíta "Šarbel"
 "Sv. Šarbela Makhlúfa, knìze",
 "",
 "",
 "",
 "Sv. Šarbela Makhlúfa, knìze",
 "Szent Charbel Makhlouf áldozópap",
 };
const char *text_JUL_24_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Árpád-házi szent Kinga szûz", // 2011-07-05: sv. Sarbela v HU majú 27. júla
 };
const char *text_JUL_24_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Antona Lucciho, biskupa, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_24_1_OP[POCET_JAZYKOV + 1] = 
{"Bl. Jany z Orvieta, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_24_2_OP[POCET_JAZYKOV + 1] = 
{"Bl. Augustína z Biella, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_25[POCET_JAZYKOV + 1] = 
{"Sv. Jakuba, apoštola",
 "Sv. Jakuba, apoštola",
 "",
 "",
 "",
 "Sv. Jakuba, apoštola",
 "Szent Jakab apostol",
 };
const char *text_JUL_26[POCET_JAZYKOV + 1] = 
{"Sv. Joachima a Anny, rodièov Panny Márie",
 "Sv. Jáchyma a Anny, rodièù Panny Marie",
 "",
 "",
 "",
 "Sv. Jáchyma a Anny, rodièù Panny Marie",
 "Szent Joakim és Szent Anna, a Boldogságos Szûz Mária szülei",
 };
const char *text_JUL_27[POCET_JAZYKOV + 1] = 
{"Sv. Gorazda a spoloèníkov",
 "Sv. Gorazda a druhù",
 "",
 "",
 "",
 "Sv. Gorazda a druhù",
 "",
 };
const char *text_JUL_27_OP[POCET_JAZYKOV + 1] = // SK OP: 28JUL
{"Bl. Róberta Nuttera, kòaza a muèeníka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_27_OFM[POCET_JAZYKOV + 1] =
{"Bl. Márie Magdalény Martinengovej, panny, èlenky 2. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_28_OFM[POCET_JAZYKOV + 1] =
{"Bl. Márie Terézie Kowalskej, panny a muèenice, èlenky 2. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_29[POCET_JAZYKOV + 1] = 
{"Sv. Marty",
 "Sv. Marty",
 "",
 "",
 "",
 "Sv. Marty",
 "Szent Márta",
 };
const char *text_JUL_30[POCET_JAZYKOV + 1] = 
{"Sv. Petra Chryzológa, biskupa a uèite¾a Cirkvi",
 "Sv. Petra Chryzologa, biskupa a uèitele církve",
 "",
 "",
 "",
 "Sv. Petra Chryzologa, biskupa a uèitele církve",
 "Aranyszavú (Krizologosz) Szent Péter püspök és egyháztanító",
 };
const char *text_JUL_30_SK[POCET_JAZYKOV + 1] = 
{"Bl. Zdenky, panny a muèenice", // Direktórium 2012, str. 173, neuvádza priezvisko ('Schelingovej')
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_30_SK_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Zdenky Schelingovej, panny a muèenice,"HTML_LINE_BREAK"reho¾níèky, èlenky 3. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_JUL_31[POCET_JAZYKOV + 1] = 
{"Sv. Ignáca z Loyoly, kòaza",
 "Sv. Ignáce z Loyoly, knìze",
 "",
 "",
 "",
 "Sv. Ignáce z Loyoly, knìze",
 "Loyolai Szent Ignác áldozópap",
 };
const char *text_JUL_31_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Ignáca Loyolského, kòaza a zakladate¾a Spoloènosti Jeišovej",
 "",
 "",
 "",
 "",
 "",
 "",
 };

// --------------- 00 pohyblivé slávenia ---------------

const char *text_CSSR_TITUL_KONGREGACIE[POCET_JAZYKOV + 1] = 
{"Najsvätejšieho Vykupite¾a, titul Kongregácie", // 3. nede¾a v júli
 "",
 "",
 "",
 "",
 "",
 "",
 };

// --------------- 08 august ---------------

const char *text_AUG_01[POCET_JAZYKOV + 1] = 
{"Sv. Alfonza Márie de’ Liguori, biskupa a uèite¾a Cirkvi",
 "Sv. Alfonsa z Liguori, biskupa a uèitele církve",
 "",
 "",
 "",
 "Sv. Alfonsa z Liguori, biskupa a uèitele Církve",
 "Liguori Szent Alfonz Mária püspök és egyháztanító",
 };
const char *text_AUG_01_CSSR[POCET_JAZYKOV + 1] = 
{"Sv. Alfonza Márie de’ Liguori, biskupa a uèite¾a Cirkvi, zakladate¾a kongregácie",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_02_1[POCET_JAZYKOV + 1] = 
{"Sv. Euzébia Vercellského, biskupa",
 "Sv. Eusebia z Vercelli, biskupa",
 "",
 "",
 "",
 "Sv. Eusebia z Vercelli, biskupa",
 "Vercelli Szent Özséb püspök",
 };
const char *text_AUG_02_2[POCET_JAZYKOV + 1] = 
{"Sv. Petra Juliána Eymarda, kòaza",
 "Sv. Petra Juliána Eymarda, knìze",
 "",
 "",
 "",
 "Sv. Petra Juliána Eymarda, knìze",
 "Szent Eymard Julián Péter áldozópap",
 };
const char *text_AUG_02_OFM[POCET_JAZYKOV + 1] = 
{"Preblahoslavenej Panny Márie Anjelskej v Porciunkule",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_02_OP[POCET_JAZYKOV + 1] = 
{"Bl. Jany z Azy, matky sv. otca Dominika",
 "",
 "",
 "",
 "",
 "Bl. Jany, matky sv. Otce Dominika",
 "",
 };
const char *text_AUG_03_OP[POCET_JAZYKOV + 1] = 
{"Bl. Augustína Kazotiæa, biskupa",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_02_SDB[POCET_JAZYKOV + 1] = 
{"Bl. Augustína Czartoryského, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_02_SJ[POCET_JAZYKOV + 1] = 
{"Bl. Petra Favra, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_04[POCET_JAZYKOV + 1] = 
{"Sv. Jána Márie Vianneyho, kòaza", // 'Vianneyho' pod¾a Direktória 2012, str. 176
 "Sv. Jana Marie Vianneye, knìze",
 "",
 "",
 "",
 "Sv. Jana Marie Vianneye, knìze",
 "Vianney Szent János Mária áldozópap",
 };
const char *text_AUG_05[POCET_JAZYKOV + 1] = 
{"Vıroèie posviacky Hlavnej mariánskej baziliky v Ríme",
 "Posvìcení øímské baziliky Panny Marie",
 "",
 "",
 "",
 "Posvìcení øímské baziliky Panny Marie",
 "Szûz Mária római fõtemplomának felszentelése (Havas Boldogasszony)",
 };
const char *text_AUG_06[POCET_JAZYKOV + 1] = 
{"Premenenie Pána",
 "Promìnìní Pánì",
 "",
 "",
 "",
 "Promìnìní Pánì",
 "Urunk Színeváltozása",
 };
const char *text_AUG_07_1[POCET_JAZYKOV + 1] = 
{"Sv. Sixta II., pápea, a jeho spoloèníkov, muèeníkov",
 "Sv. Sixta II., papee, a druhù, muèedníkù",
 "",
 "",
 "",
 "Sv. Sixta II., papee, a druhù, muèedníkù",
 "Szent II. Szixtusz pápa és társai vértanúk",
 };
const char *text_AUG_07_2[POCET_JAZYKOV + 1] = 
{"Sv. Kajetána, kòaza",
 "Sv. Kajetána, knìze",
 "",
 "",
 "",
 "Sv. Kajetána, knìze",
 "Szent Kajetán áldozópap",
 };
const char *text_AUG_07_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Agatangela a Kasiána, kòazov a muèeníkov,"HTML_LINE_BREAK"èlenov 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_08[POCET_JAZYKOV + 1] = 
{"Sv. Dominika, kòaza",
 "Sv. Dominika, knìze",
 "",
 "",
 "",
 "Sv. Otce Dominika, knìze",
 "Szent Domonkos áldozópap",
 };
const char *text_AUG_08_OP[POCET_JAZYKOV + 1] = 
{"Sv. Dominika, kòaza, zakladate¾a rehole",
 "Sv. Dominika, knìze",
 "",
 "",
 "",
 "Sv. Otce Dominika, knìze",
 "Szent Domonkos áldozópap",
 };
const char *text_AUG_08_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Dominika, kòaza,"HTML_LINE_BREAK"zakladate¾a Rádu dominikánov",
 "Sv. Dominika, knìze",
 "",
 "",
 "",
 "Sv. Otce Dominika, knìze",
 "Szent Domonkos áldozópap",
 };
const char *text_AUG_09[POCET_JAZYKOV + 1] = 
{"Sv. Terézie Benedikty z Kría"HTML_LINE_BREAK"(Edity Steinovej), panny a muèenice,"HTML_LINE_BREAK"patrónky Európy", // pod¾a Direktória 2012, str. 178
 "Sv. Terezie Benedikty, panny a muèednice,"HTML_LINE_BREAK"patronky Evropy",
 "",
 "",
 "",
 "Sv. Terezie Benedikty, panny a muèednice,"HTML_LINE_BREAK"patronky Evropy",
 "A keresztrõl nevezett Szent Teréz Benedikta (Edith Stein) "HTML_LINE_BREAK"szûz és vértanú, Európa társvédõszentje",
 };
const char *text_AUG_10[POCET_JAZYKOV + 1] = 
{"Sv. Vavrinca, diakona a muèeníka",
 "Sv. Vavøince, muèedníka",
 "",
 "",
 "",
 "Sv. Vavøince, muèedníka",
 "Szent Lõrinc diakónus és vértanú",
 };
const char *text_AUG_11[POCET_JAZYKOV + 1] = 
{"Sv. Kláry, panny",
 "Sv. Kláry, panny",
 "",
 "",
 "",
 "Sv. Kláry, panny",
 "Szent Klára szûz",
 };
const char *text_AUG_11_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Kláry z Assisi, panny, èlenky 2. rádu",
 "Sv. Kláry, panny",
 "",
 "",
 "",
 "Sv. Kláry, panny",
 "Szent Klára szûz",
 };
const char *text_AUG_12[POCET_JAZYKOV + 1] = 
{"Sv. Jany Františky de Chantal, reho¾níèky", // kedysi sa slávil 12. decembra
 "Sv. Jany Františky de Chantal, øeholnice",
 "",
 "",
 "",
 "Sv. Jany Františky de Chantal, øeholnice",
 "Chantal szent Johanna Franciska szerzetesnõ",
 };
const char *text_AUG_12_1_OP[POCET_JAZYKOV + 1] = 
{"Bl. Jána zo Salerna, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_12_2_OP[POCET_JAZYKOV + 1] = 
{"Bl. Aimona Taparelliho, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_12_3_OP[POCET_JAZYKOV + 1] = 
{"Bl. Jána Juraja Rehma, kòaza a muèeníka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_13[POCET_JAZYKOV + 1] = 
{"Sv. Ponciána, pápea, a sv. Hypolita, kòaza, muèeníkov",
 "Sv. Ponciána, papee, a Hippolyta, knìze, muèedníkù",
 "",
 "",
 "",
 "Sv. Ponciána, papee, a Hippolyta, knìze, muèedníkù",
 "Szent Ponciánusz pápa és szent Hippolitusz áldozópap és vértanúk", // HU: 16AUG
 };
const char *text_AUG_13_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Boldog XI. Ince pápa", // HU
 };
const char *text_AUG_13_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Bl. Gertrudy, panny z premonstrátského øádu",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_13_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Marka z Aviana, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_14[POCET_JAZYKOV + 1] = 
{"Sv. Maximiliána Márie Kolbeho, kòaza a muèeníka", // pod¾a Direktória 2012, str. 180
 "Sv. Maxmiliána Marie Kolbeho, knìze a muèedníka",
 "",
 "",
 "",
 "Sv. Maxmiliána Marie Kolbeho, knìze a muèedníka",
 "Szent Maximilián Mária Kolbe áldozópap és vértanú",
 };
const char *text_AUG_14_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Maximiliána Márie Kolbeho,"HTML_LINE_BREAK"kòaza a muèeníka, èlena 1. rádu",
 "Sv. Maxmiliána Marie Kolbeho, knìze a muèedníka",
 "",
 "",
 "",
 "Sv. Maxmiliána Marie Kolbeho, knìze a muèedníka",
 "Szent Maximilián Mária Kolbe áldozópap és vértanú",
 };
const char *text_AUG_15[POCET_JAZYKOV + 1] = 
{"Nanebovzatie prebl. Panny Márie",
 "Nanebevzetí Panny Marie",
 "",
 "",
 "",
 "Nanebevzetí Panny Marie",
 "Szûz Mária mennybevétele (Nagyboldogasszony)",
 };
const char *text_AUG_16[POCET_JAZYKOV + 1] = 
{"Sv. Štefana Uhorského",
 "Sv. Štìpána Uherského",
 "",
 "",
 "",
 "Sv. Štìpána Uherského",
 "Szent István király, Magyarország fõvédõszentje",
 };
const char *text_AUG_17_OP[POCET_JAZYKOV + 1] = 
{"Sv. Hyacinta Po¾ského, kòaza",
 "",
 "",
 "",
 "",
 "Sv. Hyacinta z Polska, knìze",
 "",
 };
const char *text_AUG_17_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Beatrix de Silva, panny, zakladate¾ky"HTML_LINE_BREAK"koncepcionistiek, èlenky 2. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_17_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Kaposvár: A székesegyház felszentelése",
 };
const char *text_AUG_18_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Vác: A székesegyház felszentelése",
 };
const char *text_AUG_18_SJ[POCET_JAZYKOV + 1] = 
{"Bl. Alberta Hurtada Cruchagu, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_18_OP[POCET_JAZYKOV + 1] = 
{"Bl. Manesa, kòaza, brata sv. otca Dominika",
 "",
 "",
 "",
 "",
 "Bl. Mannesa neboli Mamesa, knìze, bratra sv. Otce Dominika",
 "",
 };
const char *text_AUG_18_1_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Alojza Adama a Mikuláša Savoureta,"HTML_LINE_BREAK"kòazov a muèeníkov, èlenov 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_18_2_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Jána, Protáza a Sebastiána, kòazov,"HTML_LINE_BREAK"èlenov 1. rádu, a spoloèníkov, muèeníkov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_19[POCET_JAZYKOV + 1] = 
{"Sv. Jána Eudes, kòaza",
 "Sv. Jana Eudese, knìze",
 "",
 "",
 "",
 "Sv. Jana Eudese, knìze",
 "Eudes Szent János áldozópap",
 };
const char *text_AUG_19_OP[POCET_JAZYKOV + 1] = 
{"Bl. Jordána z Pisy, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_19_OFM[POCET_JAZYKOV + 1] = 
{"Sv. ¼udovíta, biskupa, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_20[POCET_JAZYKOV + 1] = 
{"Sv. Bernarda, opáta a uèite¾a Cirkvi",
 "Sv. Bernarda, opata a uèitele církve",
 "",
 "",
 "",
 "Sv. Bernarda, opata a uèitele Církve",
 "Szent Bernát apát és egyháztanító", // HU 19AUG
 };
const char *text_AUG_21[POCET_JAZYKOV + 1] = 
{"Sv. Pia X., pápea",
 "Sv. Pia X., papee",
 "",
 "",
 "",
 "Sv. Pia X., papee",
 "Szent X. Piusz pápa",
 };
const char *text_AUG_22[POCET_JAZYKOV + 1] = 
{"Panny Márie Krá¾ovnej", // pod¾a Direktória 2012, str. 183, tam nie je 'Prebl.'
 "Panny Marie Královny",
 "",
 "",
 "",
 "Panny Marie Královny",
 "Boldogságos Szûz Mária Királynõ",
 };
const char *text_AUG_23[POCET_JAZYKOV + 1] = 
{"Sv. Rueny Limskej, panny",
 "Sv. Rùeny z Limy, panny",
 "",
 "",
 "",
 "Sv. Rùeny Floresové neboli z Limy, panny, terciáøky",
 "Limai Szent Róza szûz",
 };
const char *text_AUG_23_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Bernarda z Offidy, reho¾níka, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_24[POCET_JAZYKOV + 1] = 
{"Sv. Bartolomeja, apoštola",
 "Sv. Bartolomìje, apoštola",
 "",
 "",
 "",
 "Sv. Bartolomìje, apoštola",
 "Szent Bertalan apostol",
 };
const char *text_AUG_25_1[POCET_JAZYKOV + 1] = 
{"Sv. Jozefa de Calasanz, kòaza",
 "Sv. Josefa Kalasanského, knìze",
 "",
 "",
 "",
 "Sv. Josefa Kalasanského, knìze",
 "Kalazanci Szent József áldozópap",
 };
const char *text_AUG_25_2[POCET_JAZYKOV + 1] = 
{"Sv. ¼udovíta",
 "Sv. Ludvíka",
 "",
 "",
 "",
 "Sv. Ludvíka",
 "Szent Lajos",
 };
const char *text_AUG_25_OFM[POCET_JAZYKOV + 1] = 
{"Sv. ¼udovíta IX., krá¾a, èlena 3. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_25_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Benedikta, Jana, Matouše, Izáka a Kristina, muèedníkù",
 "",
 "",
 "",
 "Sv. Benedikta, Jana, Matouše, Izáka a Kristina, muèedníkù",
 "",
 };
const char *text_AUG_25_2_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Bl. Metodìje Dominika Trèky, muèedníka",
 "",
 "",
 "",
 "Bl. Metodìje Dominika Trèky, muèedníka",
 "",
 };
const char *text_AUG_25_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Kalocsa-Kecskemét: A fõszékesegyház felszentelése",
 };
const char *text_AUG_26_SDB[POCET_JAZYKOV + 1] = 
{"Bl. Zefirína Namuncurá, mladíka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_26_OP[POCET_JAZYKOV + 1] = 
{"Bl. Jakuba z Bevagna, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_27[POCET_JAZYKOV + 1] = 
{"Sv. Moniky",
 "Sv. Moniky",
 "",
 "",
 "",
 "Sv. Moniky",
 "Szent Mónika",
 };
const char *text_AUG_27_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Moniky, matky našeho otce sv. Augustina",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_28_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Našeho otce sv. Augustina, biskupa a uèitele církve",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_28[POCET_JAZYKOV + 1] = 
{"Sv. Augustína, biskupa a uèite¾a Cirkvi",
 "Sv. Augustina, biskupa a uèitele církve",
 "",
 "",
 "",
 "Sv. Augustina, biskupa a uèitele Církve",
 "Szent Ágoston püspök és egyháztanító",
 };
const char *text_AUG_29[POCET_JAZYKOV + 1] = 
{"Muèenícka smr sv. Jána Krstite¾a",
 "Umuèení svatého Jana Køtitele",
 "",
 "",
 "",
 "Umuèení svatého Jana Køtitele",
 "Keresztelõ Szent János vértanúsága",
 };
const char *text_AUG_30_SK[POCET_JAZYKOV + 1] = 
{"Vıroèie posviacky katedrálneho chrámu v Trnave", // ToDo: 'sv. Jána Krstite¾a', pod¾a Direktória 2012, str. 186
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_AUG_31_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Esztergom-Budapest: A prímási bazilika-"HTML_LINE_BREAK"fõszékesegyház felszentelése",
 };
const char *text_AUG_30_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Bl. Bronislavy, panny z premonstrátského øádu",
 "",
 "",
 "",
 "",
 "",
 };

// --------------- 09 september ---------------

const char *text_SEP_02_1_OP[POCET_JAZYKOV + 1] = 
{"Bl. Gualu z Bergama, biskupa",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_02_2_OP[POCET_JAZYKOV + 1] = 
{"Bl. Ingridy zo Skänninge, reho¾níèky",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_02_1_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Jána Františka Burtého, kòaza a muèeníka,"HTML_LINE_BREAK"èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_02_2_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Apolinára z Posatu, kòaza, èlena 1. rádu,"HTML_LINE_BREAK"a spoloèníkov, muèeníkov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_03[POCET_JAZYKOV + 1] = 
{"Sv. Gregora Ve¾kého, pápea a uèite¾a Cirkvi",
 "Sv. Øehoøe Velikého, papee a uèitele církve",
 "",
 "",
 "",
 "Sv. Øehoøe Velikého, papee a uèitele Církve",
 "Nagy Szent Gergely pápa és egyháztanító",
 };
const char *text_SEP_04_OP[POCET_JAZYKOV + 1] = 
{"Bl. Kataríny z Racconigi, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_04_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Rueny z Viterba, panny, èlenky 3. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_05[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Kalkuttai Boldog Teréz szûz",
 };
const char *text_SEP_06_SK[POCET_JAZYKOV + 1] = 
{"Vıroèie posviacky katedrálneho chrámu v Košiciach", // ToDo: 'sv. Albety', pod¾a Direktória 2012, str. 190
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_06_1_OP[POCET_JAZYKOV + 1] = 
{"Bl. Bertranda z Garrigue, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_06_2_OP[POCET_JAZYKOV + 1] = 
{"Bl. Michala (Jána Františka) Czartoryského, kòaza,"HTML_LINE_BREAK"a bl. Júlie (Stanislavy) Rodziñskej, panny a reho¾níèky,"HTML_LINE_BREAK"muèeníkov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_07[POCET_JAZYKOV + 1] = 
{"Sv. Marka Kriina, Melichara Grodzieckého"HTML_LINE_BREAK"a Štefana Pongrácza, kòazov a muèeníkov",
 "Sv. Melichara Grodeckého, knìze a muèedníka",
 "",
 "",
 "",
 "Sv. Melichara Grodeckého, knìze a muèedníka",
 "Szent Márk, István és Menyhért áldozópapok, kassai vértanúk",
 };
const char *text_SEP_07_SJ[POCET_JAZYKOV + 1] = 
{"Sv. košickıch muèeníkov: Štefana Pongrácza a Melichara Grodzieckého, kòazov Spoloènosti Jeišovej; "HTML_LINE_BREAK"Marka Kriina, ostrihomského kanonika, patrónov Slovenskej provincie Spoloènosti Jeišovej",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_08[POCET_JAZYKOV + 1] = 
{"Narodenie Panny Márie", // pod¾a Direktória 2012, str. 191, tam nie je 'prebl.'
 "Narození Panny Marie",
 "",
 "",
 "",
 "Narození Panny Marie",
 "Szûz Mária Születése (Kisboldogasszony)",
 };
const char *text_SEP_09[POCET_JAZYKOV + 1] = 
{"Sv. Petra Clavera, kòaza",
 "Sv. Petra Klavera, knìze",
 "",
 "",
 "",
 "Sv. Petra Klavera, knìze",
 "Claver Szent Péter áldozópap",
 };
const char *text_SEP_09_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Petra Clavera, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_10_SJ[POCET_JAZYKOV + 1] = 
{"Bl. Františka Gárateho, reho¾níka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_10_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Bl. Karla Spinoly, knìze a muèedníka",
 "",
 "",
 "",
 "Bl. Karla Spinoly, knìze a muèedníka",
 "",
 };
const char *text_SEP_11_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Vıroèí posvìcení opatského kostela",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_12[POCET_JAZYKOV + 1] = 
{"Najsv. mena Panny Márie", // pod¾a Direktória 2012, str. 192; pôvodne bolo: 'Mena prebl. Panny Márie'
 "Jména Panny Marie",
 "",
 "",
 "",
 "Jména Panny Marie",
 "Szûz Mária Szent Neve",
 };
const char *text_SEP_12_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Nejsvìtìjšího jména Panny Marie",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_13[POCET_JAZYKOV + 1] = 
{"Sv. Jána Zlatoústeho, biskupa a uèite¾a Cirkvi",
 "Sv. Jana Zlatoústého, biskupa a uèitele církve",
 "",
 "",
 "",
 "Sv. Jana Zlatoústého, biskupa a uèitele církve",
 "Aranyszájú (Krizosztomosz) Szent János püspök és egyháztanító",
 };
const char *text_SEP_13_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Gyõr: A székesegyház felszentelése",
 };
const char *text_SEP_14[POCET_JAZYKOV + 1] = 
{"Povıšenie svätého kría",
 "Povıšení svatého køíe",
 "",
 "",
 "",
 "Povıšení svatého køíe",
 "A Szent Kereszt felmagasztalása",
 };
const char *text_SEP_15[POCET_JAZYKOV + 1] = 
{"Sedembolestnej Panny Márie, patrónky Slovenska",
 "Panny Marie Bolestné",
 "",
 "",
 "",
 "Panny Marie Bolestné",
 "A Fájdalmas Szûzanya",
 };
const char *text_SEP_16_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Ludmily, muèednice",
 "",
 "",
 "",
 "Sv. Ludmily, muèednice",
 "",
 };
const char *text_SEP_16[POCET_JAZYKOV + 1] = 
{"Sv. Kornélia, pápea, a sv. Cypriána, biskupa, muèeníkov",
 "Sv. Kornélia, papee, a Cypriána, biskupa, muèedníkù",
 "",
 "",
 "",
 "Sv. Kornélia, papee, a Cypriána, biskupa, muèedníkù",
 "Szent Kornél pápa és Szent Ciprián püspök és vértanúk",
 };
const char *text_SEP_17[POCET_JAZYKOV + 1] = 
{"Sv. Róberta Bellarmína, biskupa a uèite¾a Cirkvi",
 "Sv. Roberta Bellarmina, biskupa a uèitele církve",
 "",
 "",
 "",
 "Sv. Roberta Bellarmina, biskupa a uèitele Církve",
 "Bellarmin Szent Róbert püspök és egyháztanító",
 };
const char *text_SEP_17_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Róberta Bellarmina, biskupa a uèite¾a Cirkvi",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_17_OFM[POCET_JAZYKOV + 1] = 
{"Stigmatizácia nášho otca sv. Františka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_18_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Jozefa Kupertínskeho, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_18_OP[POCET_JAZYKOV + 1] = 
{"Sv. Jána Macíasa, reho¾níka",
 "",
 "",
 "",
 "",
 "Sv. Jana Maciase, øeholníka",
 "",
 };
const char *text_SEP_19[POCET_JAZYKOV + 1] = 
{"Sv. Januára, biskupa a muèeníka",
 "Sv. Januária, biskupa a muèedníka",
 "",
 "",
 "",
 "Sv. Januária, biskupa a muèedníka",
 "Szent Januáriusz püspök és vértanú",
 };
const char *text_SEP_19_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Františka Márie z Camporossa,"HTML_LINE_BREAK"reho¾níka, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_20[POCET_JAZYKOV + 1] = 
{"Sv. Andreja Kim Taegona, kòaza,"HTML_LINE_BREAK"a sv. Pavla Chong Hasanga a spoloèníkov, muèeníkov",
 "Sv. Ondøeje Kim Taegona, knìze, Pavla Chong Hasanga a druhù, muèedníkù",
 "",
 "",
 "",
 "Sv. Ondøeje Kim Taegona, knìze, Pavla Chong Hasanga a druhù, muèedníkù",
 "Kim Taegon Szent András áldozópap, Csong Haszang Szent Pál és társaik, vértanúk",
 };
const char *text_SEP_20_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Vıroèí posvìcení katedrály sv. Štìpána",
 "",
 "",
 "",
 "Vıroèí posvìcení katedrály sv. Štìpána",
 "",
 };
const char *text_SEP_21[POCET_JAZYKOV + 1] = 
{"Sv. Matúša, apoštola a evanjelistu",
 "Sv. Matouše, apoštola a evangelisty",
 "",
 "",
 "",
 "Sv. Matouše, apoštola a evangelisty",
 "Szent Máté apostol és evangelista",
 };
const char *text_SEP_22[POCET_JAZYKOV + 1] = 
{"Sv. Emeráma, biskupa a muèeníka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_22_1_OP[POCET_JAZYKOV + 1] = 
{"Bl. Františka de Posadas, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_22_2_OP[POCET_JAZYKOV + 1] = 
{"Bl. Hyacinta Serrana Lópeza, kòaza, a spoloèníkov, muèeníkov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_22_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Ignáca zo Santhie, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_22_SDB[POCET_JAZYKOV + 1] = 
{"Bl. Jozefa Calasanza a Enrica Saiz Aparicio, kòazov, "HTML_LINE_BREAK"a 93 spoloèníkov, muèeníkov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_23[POCET_JAZYKOV + 1] = 
{"Sv. Pia z Pietrelèiny, kòaza",
 "Sv. Pia z Pietrelciny, knìze",
 "",
 "",
 "",
 "Sv. Pia z Pietrelciny, knìze",
 "Pietrelcinai Szent Pio áldozópap",
 };
const char *text_SEP_23_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Pia z Pietrelciny, kòaza, èlena 1. rádu",
 "Sv. Pia z Pietrelciny, knìze",
 "",
 "",
 "",
 "Sv. Pia z Pietrelciny, knìze",
 "Pietrelcinai Szent Pio áldozópap",
 };
const char *text_SEP_24_SK[POCET_JAZYKOV + 1] = 
{"Vıroèie posviacky katedrálneho chrámu v Banskej Bystrici", // ToDo: 'sv. Františka Xaverského', pod¾a Direktória 2012, str. 198
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_24_OP[POCET_JAZYKOV + 1] = 
{"Bl. Dalmáca Monera, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_24_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Szent Gellért püspök és vértanú",
 };
const char *text_SEP_25_OP[POCET_JAZYKOV + 1] = 
{"Bl. Dalmáca Monera, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_26[POCET_JAZYKOV + 1] = 
{"Sv. Kozmu a Damiána, muèeníkov",
 "Sv. Kosmy a Damiána, muèedníkù",
 "",
 "",
 "",
 "Sv. Kosmy a Damiána, muèedníkù",
 "Szent Kozma és Damján vértanúk",
 };
const char *text_SEP_26_CSSR[POCET_JAZYKOV + 1] = 
{"Bl. Gašpara Stanggassingera, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_26_OP[POCET_JAZYKOV + 1] = 
{"Bl. Vavrinca z Ripafratta, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_26_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Aurélia z Vinalesy, kòaza, a spoloèníkov,"HTML_LINE_BREAK"muèeníkov, èlenov 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_27[POCET_JAZYKOV + 1] = 
{"Sv. Vincenta de Paul, kòaza",
 "Sv. Vincence z Paula, knìze",
 "",
 "",
 "",
 "Sv. Vincence z Paula, knìze",
 "Páli Szent Vince áldozópap",
 };
const char *text_SEP_28[POCET_JAZYKOV + 1] = 
{"Sv. Václava, muèeníka",
 "Sv. Václava, muèedníka, hlavního patrona èeského národa",
 "",
 "",
 "",
 "Sv. Václava, muèedníka, hlavního patrona èeského národa,"HTML_LINE_BREAK"hlavního patrona provincie",
 "Szent Vencel vértanú",
 };
const char *text_SEP_28_2[POCET_JAZYKOV + 1] = 
{"Sv. Vavrinca Ruiza a spoloèníkov, muèeníkov",
 "",
 "",
 "",
 "",
 "",
 "Ruiz Szent Lõrinc és társai, Fülöp-szigeteki vértanúk",
 };
const char *text_SEP_28_OP[POCET_JAZYKOV + 1] = 
{"Sv. Vavrinca Ruiza z Manily, laika, a spoloèníkov, muèeníkov",
 "",
 "",
 "",
 "",
 "Sv. Dominika Ibanìze z Erquicia, Jakuba Kyušei Tomonagy, knìí,"HTML_LINE_BREAK"Vavøince Ruize, otce rodiny, a druhù, japonskıch muèedníkù", // CZOP kvôli sv. Václavovi slávia 26SEP
 "",
 };
const char *text_SEP_28_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Inocenta z Berza, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_SEP_29[POCET_JAZYKOV + 1] = 
{"Sv. Michala, Gabriela a Rafaela, archanjelov",
 "Sv. Michaela, Gabriela a Rafaela, archandìlù",
 "",
 "",
 "",
 "Sv. Michaela, Gabriela a Rafaela, archandìlù",
 "Szent Mihály, Szent Gábor és Szent Rafael fõangyalok",
 };
const char *text_SEP_30[POCET_JAZYKOV + 1] = 
{"Sv. Hieronyma, kòaza a uèite¾a Cirkvi",
 "Sv. Jeronıma, knìze a uèitele církve",
 "",
 "",
 "",
 "Sv. Jeronıma, knìze a uèitele Církve",
 "Szent Jeromos áldozópap és egyháztanító",
 };

// --------------- 10 október ---------------

const char *text_OKT_01[POCET_JAZYKOV + 1] = 
{"Sv. Terézie z Lisieux, panny a uèite¾ky Cirkvi",
 "Sv. Terezie od Dítìte Jeíše, panny",
 "",
 "",
 "",
 "Sv. Terezie od Dítìte Jeíše, panny",
 "A Gyermek Jézusról nevezett (Lisieux-i) Szent Teréz Szûz",
 };
const char *text_OKT_02[POCET_JAZYKOV + 1] = 
{"Svätıch anjelov strácov",
 "Svatıch andìlù stránıch",
 "",
 "",
 "",
 "Svatıch andìlù stránıch",
 "Szent Õrzõangyalok",
 };
const char *text_OKT_03_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Františka de Borja, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_03_OP[POCET_JAZYKOV + 1] = 
{"Bl. Dominika Spadaforu, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_04[POCET_JAZYKOV + 1] = 
{"Sv. Františka Assiského",
 "Sv. Františka z Assisi",
 "",
 "",
 "",
 "Sv. Františka z Assisi, jáhna",
 "Assisi Szent Ferenc",
 };
const char *text_OKT_04_OFM[POCET_JAZYKOV + 1] = 
{"Nášho otca sv. Františka, diakona,"HTML_LINE_BREAK"zakladate¾a troch rádov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_04_OP[POCET_JAZYKOV + 1] = 
{"Sv. Františka Assiského, diakona",
 "",
 "",
 "",
 "",
 "Sv. Františka z Assisi, jáhna",
 "",
 };
const char *text_OKT_05_SDB[POCET_JAZYKOV + 1] = 
{"Bl. Alberta Marvelliho",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_05_CSSR[POCET_JAZYKOV + 1] = 
{"Bl. Františka Xaverského Seelosa, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_05_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Veszprém: A bazilika-fõszékesegyház felszentelése",
 };
const char *text_OKT_05_OP[POCET_JAZYKOV + 1] = 
{"Bl. Rajmunda z Kapuy, kòaza",
 "",
 "",
 "",
 "",
 "Bl. Rajmunda delle Vigne neboli z Kapuy, knìze",
 "",
 };
const char *text_OKT_06[POCET_JAZYKOV + 1] = 
{"Sv. Bruna, kòaza",
 "Sv. Bruna, knìze",
 "",
 "",
 "",
 "Sv. Bruna, knìze",
 "Szent Brúnó áldozópap",
 };
const char *text_OKT_06_SJ[POCET_JAZYKOV + 1] = 
{"Bl. Diega Alojza de san Vitores, kòaza a muèeníka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_06_OP[POCET_JAZYKOV + 1] = 
{"Bl. Bartolomeja Longu, laika",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_07[POCET_JAZYKOV + 1] = 
{"Ruencovej Panny Márie", // pod¾a Direktória 2012, str. 206, nie je 'prebl.'
 "Panny Marie Rùencové",
 "",
 "",
 "",
 "Panny Marie Rùencové",
 "Rózsafüzér Királynõje",
 };
const char *text_OKT_07_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Vıroèí posvìcení opatského kostela",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_08_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Szûz Mária, Magyarok nagyaszszonya, Magyarország fõpátronája",
 };
const char *text_OKT_08_1_OP[POCET_JAZYKOV + 1] = 
{"Bl. Ambróza Sansedoniho, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_08_2_OP[POCET_JAZYKOV + 1] = 
{"Bl. Matúša Carreriho, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_09_1[POCET_JAZYKOV + 1] = 
{"Sv. Dionıza, biskupa, a spoloèníkov, muèeníkov",
 "Sv. Dionısia, biskupa, a druhù, muèedníkù",
 "",
 "",
 "",
 "Sv. Dionısia, biskupa, a druhù, muèedníkù",
 "Szent Dénes püspök és társai vértanúk",
 };
const char *text_OKT_09_2[POCET_JAZYKOV + 1] = 
{"Sv. Jána Leonardiho, kòaza",
 "Sv. Jana Leonardiho, knìze",
 "",
 "",
 "",
 "Sv. Jana Leonardiho, knìze",
 "Leonardi Szent János áldozópap",
 };
const char *text_OKT_09_OP[POCET_JAZYKOV + 1] = 
{"Sv. ¼udovíta Bertrána, kòaza",
 "",
 "",
 "",
 "",
 "Sv. Ludvíka Bertrána, knìze",
 "",
 };
const char *text_OKT_10_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Gereona a druhù, muèedníkù",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_11[POCET_JAZYKOV + 1] = 
{"Bl. Jána XXIII., pápea",
 "",
 "",
 "",
 "",
 "",
 "Boldog XXIII. János pápa",
 };
const char *text_OKT_11_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Jána XXIII., pápea, èlena 3. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_11_SK[POCET_JAZYKOV + 1] = 
{"Vıroèie posviacky katedrálneho chrámu v iline", // ToDo: 'Najsvätejšej Trojice', pod¾a Direktória 2012, str. 207
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_11_OP[POCET_JAZYKOV + 1] = 
{"Bl. Jakuba z Ulmu, reho¾níka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_12_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Radima, biskupa",
 "",
 "",
 "",
 "Sv. Radima, biskupa",
 "",
 };
const char *text_OKT_12_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Serafína z Montegranara, reho¾níka, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_13_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Honoráta Ko¿miñského, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_13_OP[POCET_JAZYKOV + 1] = 
{"Bl. Magdalény Panatieriovej, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_13_SDB[POCET_JAZYKOV + 1] = 
{"Bl. Alexandry Márie da Costovej",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_13_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Bl. Petra Adriána Toulorge, knìze a muèedníka"HTML_LINE_BREAK"z premonstrátského øádu",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_14[POCET_JAZYKOV + 1] = 
{"Sv. Kalixta I., pápea a muèeníka",
 "Sv. Kalista I., papee a muèedníka",
 "",
 "",
 "",
 "Sv. Kalista I., papee a muèedníka",
 "Szent I. Kallixtusz pápa és vértanú",
 };
const char *text_OKT_14_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Jána Ogilvieho, kòaza a muèeníka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_14_OP[POCET_JAZYKOV + 1] = 
{"Bl. Márie Poussepinovej, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_15[POCET_JAZYKOV + 1] = 
{"Sv. Terézie od Jeiša, panny a uèite¾ky Cirkvi", // 'z Avily' upravené pod¾a Direktória 2012, str. 209
 "Sv. Terezie od Jeíše, panny a uèitelky církve",
 "",
 "",
 "",
 "Sv. Terezie od Jeíše, panny a uèitelky Církve",
 "A Jézusról nevezett (Avilai) Szent Teréz szûz és egyháztanító",
 };
const char *text_OKT_16_1[POCET_JAZYKOV + 1] = 
{"Sv. Margity Márie Alacoque, panny",
 "Sv. Markéty Marie Alacoque, panny",
 "",
 "",
 "",
 "Sv. Markéty Marie Alacoque, panny",
 "Alacoque Szent Margit Mária szûz",
 };
const char *text_OKT_16_2[POCET_JAZYKOV + 1] = 
{"Sv. Hedvigy, reho¾níèky",
 "Sv. Hedviky, øeholnice, hlavní patronky Slezska",
 "",
 "",
 "",
 "Sv. Hedviky, øeholnice, hlavní patronky Slezska",
 "Szent Hedvig szerzetesnõ",
 };
const char *text_OKT_16_CSSR[POCET_JAZYKOV + 1] = 
{"Sv. Gerarda Majellu, reho¾níka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_17[POCET_JAZYKOV + 1] = 
{"Sv. Ignáca Antiochijského, biskupa a muèeníka",
 "Sv. Ignáce Antiochijského, biskupa a muèedníka",
 "",
 "",
 "",
 "Sv. Ignáce Antiochijského, biskupa a muèedníka",
 "Antiochiai Szent Ignác püspök és vértanú",
 };
const char *text_OKT_18[POCET_JAZYKOV + 1] = 
{"Sv. Lukáša, evanjelistu",
 "Sv. Lukáše, evangelisty",
 "",
 "",
 "",
 "Sv. Lukáše, evangelisty",
 "Szent Lukács evangelista",
 };
const char *text_OKT_19_1[POCET_JAZYKOV + 1] = 
{"Sv. Jána de Brébeuf a Izáka Jogues, kòazov,"HTML_LINE_BREAK"a spoloèníkov, muèeníkov", //  // 'sv. Izáka', pod¾a Direktória 2012, str. 210 nie je 'sv.'
 "Sv. Jana de Brébeuf a Izáka Joguese, knìí, a druhù, muèedníkù",
 "",
 "",
 "",
 "Sv. Jana de Brébeuf a Izáka Joguese, knìí, a druhù, muèedníkù",
 "De Brébeuf Szent János és Jogues Szent Izsák áldozópap és társaik vértanúk",
 };
const char *text_OKT_19_2[POCET_JAZYKOV + 1] = 
{"Sv. Pavla z Kría, kòaza",
 "Sv. Pavla od Køíe, knìze",
 "",
 "",
 "",
 "Sv. Pavla od Køíe, knìze",
 "Keresztes Szent Pál áldozópap",
 };
const char *text_OKT_19_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Jána de Brébeuf, Izáka Joguesa, kòazov, a spoloèníkov, muèeníkov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_19_OP[POCET_JAZYKOV + 1] = 
{"Bl. Agnesy Galandovej de Langeac, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_19_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Petra z Alcantary, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_20_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Jakuba Strepu, biskupa, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_20_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Jakuba Kerna, knìze z premonstrátského øádu",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_21_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Bl. Karla Rakouského",
 "",
 "",
 "",
 "Bl. Karla Rakouského",
 "",
 };
const char *text_OKT_21_OP[POCET_JAZYKOV + 1] = 
{"Bl. Petra z Citt&agrave; di Castello, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_22_OP[POCET_JAZYKOV + 1] = 
{"Vıroèie posviacky konventného kostola,"HTML_LINE_BREAK"ktorého deò posviacky nie je známy",
 "",
 "",
 "",
 "",
 "Vıroèí posvìcení klášterního kostela",
 "",
 };
const char *text_OKT_22[POCET_JAZYKOV + 1] = 
{"Bl. Jána Pavla II., pápea",
 "Bl. Jana Pavla II., papee",
 "",
 "",
 "",
 "Bl. Jana Pavla II., papee",
 "Boldog II. János Pál pápa",
 };
const char *text_OKT_23[POCET_JAZYKOV + 1] = 
{"Sv. Jána Kapistránskeho, kòaza",
 "Sv. Jana Kapistránského, knìze",
 "",
 "",
 "",
 "Sv. Jana Kapistránského, knìze",
 "Kapisztrán Szent János áldozópap",
 };
const char *text_OKT_23_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Jána Kapistránskeho, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_24[POCET_JAZYKOV + 1] = 
{"Sv. Antona Márie Clareta, biskupa",
 "Sv. Antonína Marie Klareta, biskupa",
 "",
 "",
 "",
 "Sv. Antonína Marie Klareta, biskupa",
 "Claret Szent Antal Mária püspök",
 };
const char *text_OKT_24_SDB[POCET_JAZYKOV + 1] = 
{"Bl. Alojza Guanellu, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_24_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "A Székesegyház felszentelése",
 };
const char *text_OKT_25_SK[POCET_JAZYKOV + 1] = 
{"Vıroèie posviacky katedrálneho chrámu v Spišskom Podhradí", // ToDo: 'sv. Martina z Tours', pod¾a Direktória 2012, str. 213
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_25_SDB[POCET_JAZYKOV + 1] = 
{"Vıroèie posviacky vlastného chrámu (keï sa nepozná dátum posviacky)",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_25_OP[POCET_JAZYKOV + 1] = 
{"Bl. Petra Geremiu, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_25_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Márie od Jeiša Masie Ferragutovej a spoloèníc,"HTML_LINE_BREAK"panien a muèeníc, èleniek 2. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_25_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Szent Mór püspök",
 };
const char *text_OKT_26[POCET_JAZYKOV + 1] = 
{"Vıroèie posviacky chrámov,"HTML_LINE_BREAK"ktorıch deò posviacky nie je známy",  // 'je neznámy' opravené pod¾a Direktória 2012, str. 214
 "Vıroèí posvìcení chrámu,"HTML_LINE_BREAK"jejich den dedikace není známı",
 "",
 "",
 "",
 "Vıroèí posvìcení chrámu,"HTML_LINE_BREAK"jejich den dedikace není známı",
 "A saját templom felszentelése "HTML_LINE_BREAK"(amennyiben annak napja nem ismeretes)", // A felszentelt templomokban: A saját templom felszentelése
 };
const char *text_OKT_26_OP[POCET_JAZYKOV + 1] = 
{"Bl. Damiána z Finale, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_26_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Gilberta, opata z premonstrátského øádu",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_26_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Bonaventúru z Potenzy, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_27_SK[POCET_JAZYKOV + 1] = 
{"Vıroèie posviacky katedrálneho chrámu v Roòave", // ToDo: 'Nanebovzatia Panny Márie', pod¾a Direktória 2012, str. 214
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_27_OP[POCET_JAZYKOV + 1] = 
{"Bl. Bartolomeja z Vicenze, biskupa",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_28[POCET_JAZYKOV + 1] = 
{"Sv. Šimona a Júdu, apoštolov",
 "Sv. Šimona a Judy, apoštolù",
 "",
 "",
 "",
 "Sv. Šimona a Judy, apoštolù",
 "Szent Simon és Szent Júdás apostol",
 };
const char *text_OKT_29_SDB[POCET_JAZYKOV + 1] = 
{"Bl. Michala Ruu, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_29_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Bl. Marie Restituty Kafkové, panny a muèednice",
 "",
 "",
 "",
 "Bl. Marie Restituty Kafkové, panny a muèednice",
 "",
 };
const char *text_OKT_30_SJ[POCET_JAZYKOV + 1] = 
{"Bl. Dominika Collinsa, muèeníka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_30_1_OP[POCET_JAZYKOV + 1] = 
{"Bl. Benvenuty Boianiovej, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_30_2_OP[POCET_JAZYKOV + 1] = 
{"Bl. Terenca Alberta O’Brien, biskupa,"HTML_LINE_BREAK"a bl. Petra Higginsa, kòaza, muèeníkov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_30_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Vıroèí posvìcení katedrály Svatého Ducha",
 "",
 "",
 "",
 "Vıroèí posvìcení katedrály Svatého Ducha",
 "",
 };
const char *text_OKT_31_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Alfonza Rodrígueza, reho¾níka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_31_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Angela z Acri, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_OKT_31_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Wolfganga, biskupa",
 "",
 "",
 "",
 "Sv. Wolfganga, biskupa",
 "",
 };
const char *text_OKT_31_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Boldog Romzsa Tódor püspök és vértanú",
 };

// --------------- 11 november ---------------

const char *text_NOV_01[POCET_JAZYKOV + 1] = 
{"Všetkıch svätıch",
 "Všech svatıch",
 "",
 "",
 "",
 "Všech svatıch",
 "Mindenszentek",
 };
const char *text_NOV_02[POCET_JAZYKOV + 1] = 
{"Spomienka na všetkıch vernıch zosnulıch", // pod¾a Direktória 2012, str. 218
 "Vzpomínka na všechny vìrné zemøelé",
 "",
 "",
 "",
 "Vzpomínka na všechny vìrné zemøelé",
 "Halottak napja",
 };
const char *text_NOV_03[POCET_JAZYKOV + 1] = 
{"Sv. Martina Porres, reho¾níka", // 'de Porres': pod¾a Direktória 2012, str. 218, nie je 'de'
 "Sv. Martina de Porres, øeholníka",
 "",
 "",
 "",
 "Sv. Martina de Porres, øeholníka",
 "Porres Szent Márton szerzetes",
 };
const char *text_NOV_03_SJ[POCET_JAZYKOV + 1] = 
{"Bl. Ruperta Mayera, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_03_OFM[POCET_JAZYKOV + 1] = 
{"Spomienka na všetkıch zosnulıch"HTML_LINE_BREAK"troch františkánskych rádov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_04[POCET_JAZYKOV + 1] = 
{"Sv. Karola Borromea, biskupa",
 "Sv. Karla Boromejského, biskupa",
 "",
 "",
 "",
 "Sv. Karla Boromejského, biskupa",
 "Borromeo Szent Károly püspök",
 };
const char *text_NOV_05_SK[POCET_JAZYKOV + 1] = 
{"Sv. Imricha",
 "",
 "",
 "",
 "",
 "",
 "Szent Imre herceg",
 };
const char *text_NOV_05_SJ[POCET_JAZYKOV + 1] = 
{"Všetkıch svätıch a blahoslavenıch zo Spoloènosti Jeišovej",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_05_SDB[POCET_JAZYKOV + 1] = 
{"Všetkıch zomrelıch dobrodincov Saleziánskej rodiny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_05_OP[POCET_JAZYKOV + 1] = 
{"Bl. Šimona Ballacchiho, reho¾níka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_06_OP[POCET_JAZYKOV + 1] = 
{"Bl. Alfonza de Navarrete, kòaza, a spoloèníkov, muèeníkov",
 "",
 "",
 "",
 "",
 "Sv. Alfonse Navarrety, knìze a druhù, japonskıch muèedníkù",
 "",
 };
const char *text_NOV_06_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Alfonza Lopeza a spoloèníkov, muèeníkov, èlenov 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_07_OP[POCET_JAZYKOV + 1] = 
{"Všetkıch svätıch Rehole kazate¾ov",
 "",
 "",
 "",
 "",
 "Všech svatıch Øádu bratøí kazatelù",
 "",
 };
const char *text_NOV_08_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Jána Dunsa Scota, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_08_OP[POCET_JAZYKOV + 1] = 
{"Spomienka na všetkıch zosnulıch"HTML_LINE_BREAK"bratov a sestry Rehole kazate¾ov",
 "",
 "",
 "",
 "",
 "Všech zemøelıch bratøí a sester"HTML_LINE_BREAK"Øádu bratøí kazatelù",
 "",
 };
const char *text_NOV_08_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Všech svatıch premonstrátského øádu "HTML_LINE_BREAK"a všech svatıch z øádù øeholních kanovníkù",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_09[POCET_JAZYKOV + 1] = 
{"Vıroèie posviacky Lateránskej baziliky",
 "Posvìcení lateránské baziliky",
 "",
 "",
 "",
 "Posvìcení lateránské baziliky",
 "A lateráni-bazilika felszentelése",
 };
const char *text_NOV_10[POCET_JAZYKOV + 1] = 
{"Sv. Leva Ve¾kého, pápea a uèite¾a Cirkvi",
 "Sv. Lva Velikého, papee a uèitele církve",
 "",
 "",
 "",
 "Sv. Lva Velikého, papee a uèitele církve",
 "Nagy Szent Leó pápa és egyháztanító",
 };
const char *text_NOV_11[POCET_JAZYKOV + 1] = 
{"Sv. Martina z Tours, biskupa",
 "Sv. Martina, biskupa",
 "",
 "",
 "",
 "Sv. Martina, biskupa",
 "Tours-i Szent Márton püspök",
 };
const char *text_NOV_12[POCET_JAZYKOV + 1] = 
{"Sv. Jozafáta, biskupa a muèeníka",
 "Sv. Josafata, biskupa a muèedníka",
 "",
 "",
 "",
 "Sv. Josafata, biskupa a muèedníka",
 "Szent Jozafát püspök és vértanú",
 };
const char *text_NOV_13_SDB[POCET_JAZYKOV + 1] = 
{"Bl. Artemida Zattiho",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_13_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Stanislava Kostku, reho¾níka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_13_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Didaka z Alcaly, reho¾níka, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_13_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Aneky Èeské, panny",
 "",
 "",
 "",
 "Sv. Aneky Èeské, panny",
 "",
 };
const char *text_NOV_13_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "Magyar szentek és boldogok",
 };
const char *text_NOV_14_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Jozefa Pignatelliho, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_14_OPRAEM[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Siarda, opata z premonstrátského øádu",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_14_1_OP[POCET_JAZYKOV + 1] = 
{"Bl. Jána Licciu, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_14_2_OP[POCET_JAZYKOV + 1] = 
{"Bl. Lucie z Narni, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_14_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Mikuláša Taveliæa a spoloèníkov,"HTML_LINE_BREAK"kòazov a muèeníkov, èlenov 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_15[POCET_JAZYKOV + 1] = 
{"Sv. Alberta Ve¾kého, biskupa a uèite¾a Cirkvi",
 "Sv. Alberta Velikého, biskupa a uèitele církve",
 "",
 "",
 "",
 "Sv. Alberta Velikého, biskupa a uèitele Církve",
 "Nagy Szent Albert püspök és egyháztanító",
 };
const char *text_NOV_15_SDB[POCET_JAZYKOV + 1] = 
{"Bl. Magdalény Moranovej, panny",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_16_1[POCET_JAZYKOV + 1] = 
{"Sv. Margity Škótskej",
 "Sv. Markéty Skotské",
 "",
 "",
 "",
 "Sv. Markéty Skotské",
 "Skóciai Szent Margit",
 };
const char *text_NOV_16_2[POCET_JAZYKOV + 1] = 
{"Sv. Gertrúdy, panny",
 "Sv. Gertrudy, panny",
 "",
 "",
 "",
 "Sv. Gertrudy, panny",
 "Nagy Szent Gertrúd szûz", // HU 17NOV
 };
const char *text_NOV_16_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Rocha Gonzáleza, Alfonza Rodrígueza"HTML_LINE_BREAK"a Jána del Castillo, kòazov a muèeníkov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_17[POCET_JAZYKOV + 1] = 
{"Sv. Albety Uhorskej, reho¾níèky",
 "Sv. Albìty Uherské, øeholnice",
 "",
 "",
 "",
 "Sv. Albìty Uherské, øeholnice",
 "Árpád-házi Szent Erzsébet", // HU 19NOV
 };
const char *text_NOV_17_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Albety Uhorskej, reho¾níèky,"HTML_LINE_BREAK"patrónky františkánskeho svetského rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_18[POCET_JAZYKOV + 1] = 
{"Vıroèie posviacky bazilík sv. Petra a sv. Pavla, apoštolov",
 "Posvìcení øímskıch bazilik svatıch apoštolù Petra a Pavla",
 "",
 "",
 "",
 "Posvìcení øímskıch bazilik svatıch apoštolù Petra a Pavla",
 "Szent Péter- és Szent Pál-bazilikák felszentelése",
 };
const char *text_NOV_18_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Salome z Krakova, panny, èlenky 2. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_19_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Agnesy z Assisi, panny, èlenky 2. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_19_OP[POCET_JAZYKOV + 1] = 
{"Bl. Jakuba Benfattiho, biskupa",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_20_SK[POCET_JAZYKOV + 1] = 
{"Vıroèie posviacky katedrálneho chrámu v Nitre", // ToDo: 'sv. Emeráma', pod¾a Direktória 2012, str. 226
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_21[POCET_JAZYKOV + 1] = 
{"Obetovanie Panny Márie", // pod¾a Direktória 2012, str. 226, nie je 'prebl.'
 "Zasvìcení Panny Marie v Jeruzalémì",
 "",
 "",
 "",
 "Zasvìcení Panny Marie v Jeruzalémì",
 "A Boldogságos Szûz Mária bemutatása a templomban",
 };
const char *text_NOV_22[POCET_JAZYKOV + 1] = 
{"Sv. Cecílie, panny a muèenice",
 "Sv. Cecilie, panny a muèednice",
 "",
 "",
 "",
 "Sv. Cecilie, panny a muèednice",
 "Szent Cecília szûz és vértanú",
 };
const char *text_NOV_23_1[POCET_JAZYKOV + 1] = 
{"Sv. Klementa I. pápea a muèeníka",
 "Sv. Klementa I., papee a muèedníka",
 "",
 "",
 "",
 "Sv. Klementa I., papee a muèedníka",
 "Szent I. Kelemen pápa és vértanú",
 };
const char *text_NOV_23_2[POCET_JAZYKOV + 1] = 
{"Sv. Kolumbána, opáta",
 "Sv. Kolumbána, opata",
 "",
 "",
 "",
 "Sv. Kolumbána, opata",
 "Szent Kolumbán apát",
 };
const char *text_NOV_23_SJ[POCET_JAZYKOV + 1] = 
{"Bl. Michala Augustína Pro, kòaza a muèeníka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_24[POCET_JAZYKOV + 1] = 
{"Sv. Ondreja Dung-Laka, kòaza,"HTML_LINE_BREAK"a spoloèníkov, muèeníkov",
 "Sv. Ondøeje Dung-Laca, knìze, a druhù, muèedníkù",
 "",
 "",
 "",
 "Sv. Ignáce Delgada, biskupa, Vincence Liema, knìze, "HTML_LINE_BREAK"Dominika An-Khama, otce rodiny, a druhù, vietnamskıch muèedníkù",
 "Dung-Lac Szent András áldozópap és társai vértanúk",
 };
const char *text_NOV_24_OP[POCET_JAZYKOV + 1] = 
{"Sv. Ignáca Klementa Delgadu, biskupa, "HTML_LINE_BREAK"Vincenta Le Quang Liem a Pace, kòaza, "HTML_LINE_BREAK"Dominika Pham Trong (An) Khama, laika, "HTML_LINE_BREAK"a spoloèníkov, muèeníkov",
 "Sv. Ignáce Delgada, biskupa, Vincence Liema, knìze, "HTML_LINE_BREAK"Dominika An-Khama, otce rodiny, a druhù, vietnamskıch muèedníkù",
 "",
 "",
 "",
 "Sv. Ignáce Delgada, biskupa, Vincence Liema, knìze, "HTML_LINE_BREAK"Dominika An-Khama, otce rodiny, a druhù, vietnamskıch muèedníkù",
 "",
 };
const char *text_NOV_25[POCET_JAZYKOV + 1] = 
{"Sv. Kataríny Alexandrijskej, panny a muèenice",
 "Sv. Kateøiny Alexandrijské, panny a muèednice",
 "",
 "",
 "",
 "Sv. Kateøiny Alexandrijské, panny a muèednice",
 "Alexandriai Szent Katalin szûz és vértanú",
 };
const char *text_NOV_25_HU[POCET_JAZYKOV + 1] = 
{"",
 "",
 "",
 "",
 "",
 "",
 "A bazilika-székesegyház felszentelése",
 };
const char *text_NOV_25_SDB[POCET_JAZYKOV + 1] = 
{"Všetkıch zomrelıch rodièov saleziánov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_26_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Jána Berchmansa, reho¾níka",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_26_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Leonarda z Porto Mauricia, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_27_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Františka Antona Fasaniho, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_27_OP[POCET_JAZYKOV + 1] = 
{"Bl. Margity Savojskej, matky rodiny a reho¾níèky",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_28_OFM[POCET_JAZYKOV + 1] = 
{"Sv. Jakuba z Marky, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_29_OFM[POCET_JAZYKOV + 1] = 
{"Všetkıch svätıch troch františkánskych rádov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_NOV_30[POCET_JAZYKOV + 1] = 
{"Sv. Ondreja, apoštola",
 "Sv. Ondøeje, apoštola",
 "",
 "",
 "",
 "Sv. Ondøeje, apoštola",
 "Szent András apostol",
 };

// --------------- 12 december ---------------

const char *text_DEC_01_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Edmunda Campiona, Róberta Southwella a ich spoloèníkov, muèeníkov",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_DEC_01_OP[POCET_JAZYKOV + 1] = 
{"Bl. Jána Vercellského, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_DEC_01_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Sv. Edmunda Kampiána, knìze a muèedníka",
 "",
 "",
 "",
 "Sv. Edmunda Kampiána, knìze a muèedníka",
 "",
 };
const char *text_DEC_02_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Vıroèí posvìcení katedrály sv. Bartolomìje",
 "",
 "",
 "",
 "Vıroèí posvìcení katedrály sv. Bartolomìje",
 "",
 };
const char *text_DEC_02_1_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Rafaela Chyliñského, kòaza, èlena 1. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_DEC_02_2_OFM[POCET_JAZYKOV + 1] = 
{"Bl. Angely Márie Astorchovej, panny, èlenky 2. rádu",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_DEC_03[POCET_JAZYKOV + 1] = 
{"Sv. Františka Xaverského, kòaza",
 "Sv. Františka Xaverského, knìze",
 "",
 "",
 "",
 "Sv. Františka Xaverského, knìze",
 "Xavéri Szent Ferenc áldozópap",
 };
const char *text_DEC_03_SJ[POCET_JAZYKOV + 1] = 
{"Sv. Františka Xavérskeho, misionára",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_DEC_04[POCET_JAZYKOV + 1] = 
{"Sv. Jána Damascénskeho, kòaza a uèite¾a Cirkvi",
 "Sv. Jana Damašského, knìze a uèitele církve",
 "",
 "",
 "",
 "Sv. Jana Damašského, knìze a uèitele Církve",
 "Damaszkuszi Szent János áldozópap és egyháztanító",
 };
const char *text_DEC_05_SDB[POCET_JAZYKOV + 1] = 
{"Bl. Filipa Rinaldiho, kòaza, "HTML_LINE_BREAK"zakladate¾a Sekulárneho inštitútu dobrovo¾níèok dona Bosca",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_DEC_06[POCET_JAZYKOV + 1] = 
{"Sv. Mikuláša, biskupa",
 "Sv. Mikuláše, biskupa",
 "",
 "",
 "",
 "Sv. Mikuláše, biskupa",
 "Szent Miklós püspök",
 };
const char *text_DEC_07[POCET_JAZYKOV + 1] = 
{"Sv. Ambróza, biskupa a uèite¾a Cirkvi",
 "Sv. Ambroe, biskupa a uèitele církve",
 "",
 "",
 "",
 "Sv. Ambroe, biskupa a uèitele Církve",
 "Szent Ambrus püspök és egyháztanító",
 };
const char *text_DEC_08[POCET_JAZYKOV + 1] = 
{"Nepoškvrnené poèatie Panny Márie",
 "Panny Marie, poèaté bez poskvrny prvotního høíchu",
 "",
 "",
 "",
 "Neposkvrnìného poèetí Panny Marie",
 "A Boldogságos Szûz Mária szeplõtelen fogantatása",
 };
const char *text_DEC_09[POCET_JAZYKOV + 1] = 
{"Sv. Jána Didaka Cuauhtlatoatzin",
 "Sv. Jana Didaka Cuauhtlatoatzina",
 "",
 "",
 "",
 "Sv. Jana Didaka Cuauhtlatoatzina",
 "Szent Juan Diego Cuauhtlatoatzin, Guadalupei látnok",
 };
const char *text_DEC_11[POCET_JAZYKOV + 1] = 
{"Sv. Damaza I., pápea",
 "Sv. Damasa I., papee",
 "",
 "",
 "",
 "Sv. Damasa I., papee",
 "Szent I. Damazusz pápa",
 };
const char *text_DEC_12[POCET_JAZYKOV + 1] = 
{"Panny Márie Guadalupskej", // pod¾a Direktória 2012, str. 232, nie je 'Prebl.'
 "Panny Marie Guadalupské",
 "",
 "",
 "",
 "Panny Marie Guadalupské",
 "A Guadalupei Boldogságos Szûz Mária",
 };
const char *text_DEC_13[POCET_JAZYKOV + 1] = 
{"Sv. Lucie, panny a muèenice",
 "Sv. Lucie, panny a muèednice",
 "",
 "",
 "",
 "Sv. Lucie, panny a muèednice",
 "Szent Lúcia szûz és vértanú",
 };
const char *text_DEC_14[POCET_JAZYKOV + 1] = 
{"Sv. Jána z Kría, kòaza a uèite¾a Cirkvi",
 "Sv. Jana od Køíe, knìze a uèitele církve",
 "",
 "",
 "",
 "Sv. Jana od Køíe, knìze a uèitele Církve",
 "Keresztes Szent János áldozópap és egyháztanító",
 };
const char *text_DEC_16_OP[POCET_JAZYKOV + 1] = 
{"Bl. Šebastiána Maggiho, kòaza",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_DEC_21[POCET_JAZYKOV + 1] = 
{"Sv. Petra Kanízia, kòaza a uèite¾a Cirkvi",
 "Sv. Petra Kanisia, knìze a uèitele církve",
 "",
 "",
 "",
 "Sv. Petra Kanisia, knìze a uèitele Církve",
 "Kaníziusz Szent Péter áldozópap és egyháztaíntó",
 };
const char *text_DEC_22_CZ[POCET_JAZYKOV + 1] = 
{"",
 "Vıroèí posvìcení katedrály Sv. Mikuláše",
 "",
 "",
 "",
 "Vıroèí posvìcení katedrály Sv. Mikuláše",
 "",
 };
const char *text_DEC_22_OP[POCET_JAZYKOV + 1] = 
{"Vıroèie potvrdenia Rehole kazate¾ov (1216)",
 "",
 "",
 "",
 "",
 "",
 "",
 };
const char *text_DEC_23[POCET_JAZYKOV + 1] = 
{"Sv. Jána Kentského, kòaza",
 "Sv. Jana Kentského, knìze",
 "",
 "",
 "",
 "Sv. Jana Kentského, knìze",
 "K&#281;ty Szent János áldozópap",
 };
const char *text_DEC_26[POCET_JAZYKOV + 1] = 
{"Sv. Štefana, prvého muèeníka",
 "Sv. Štìpána, prvomuèedníka",
 "",
 "",
 "",
 "Sv. Štìpána, prvomuèedníka",
 "Szent István elsõ vértanú",
 };
const char *text_DEC_27[POCET_JAZYKOV + 1] = 
{"Sv. Jána, apoštola a evanjelistu",
 "Sv. Jana, apoštola a evangelisty",
 "",
 "",
 "",
 "Sv. Jana, apoštola a evangelisty",
 "Szent János apostol és evangelista",
 };
const char *text_DEC_28[POCET_JAZYKOV + 1] = 
{"Svätıch Neviniatok, muèeníkov",
 "Svatıch Mláïátek, muèedníkù",
 "",
 "",
 "",
 "Svatıch Mláïátek, muèedníkù",
 "Aprószentek",
 };
const char *text_DEC_29[POCET_JAZYKOV + 1] = 
{"Sv. Tomáša Becketa, biskupa a muèeníka",
 "Sv. Tomáše Becketa, biskupa a muèedníka",
 "",
 "",
 "",
 "Sv. Tomáše Becketa, biskupa a muèedníka",
 "Becket Szent Tamás püspök és vértanú",
 };
const char *text_DEC_31[POCET_JAZYKOV + 1] = 
{"Sv. Silvestra I., pápea",
 "Sv. Silvestra I., papee",
 "",
 "",
 "",
 "Sv. Silvestra I., papee",
 "Szent I. Szilveszter pápa",
 };

// --------------- 00 pohyblivé slávenia ---------------

const char *text_ZELENY_STVRTOK[POCET_JAZYKOV + 1] = 
{"Zelenı (ve¾kı) štvrtok – Pamiatka Pánovej veèere",
 "Zelenı ètvrtek - Památka Veèeøe Pánì",
 "",
 "",
 "",
 "Zelenı ètvrtek - Památka Veèeøe Pánì",
 "Nagycsütörtök",
 };
const char *text_VELKY_PIATOK[POCET_JAZYKOV + 1] = 
{"Ve¾kı piatok",
 "Velkı pátek",
 "",
 "",
 "",
 "Velkı pátek",
 "Nagypéntek",
 };
const char *text_BIELA_SOBOTA[POCET_JAZYKOV + 1] = 
{"Biela (ve¾ká) sobota",
 "Bílá sobota",
 "",
 "",
 "",
 "Bílá sobota",
 "Nagyszombat",
 };
const char *text_KVETNA_NEDELA[POCET_JAZYKOV + 1] = 
{"Kvetná nede¾a",
 "Kvìtná nedìle",
 "",
 "",
 "",
 "Kvìtná nedìle",
 "Virágvasárnap, vagyis az Úr szenvedésének vasárnapja",
 };
const char *text_PO_POPOLCOVEJ_STREDE[POCET_JAZYKOV + 1] = 
{"po Popolcovej strede",
 "po Popeleèní støedì",
 "",
 "",
 "",
 "po Popeleèní støedì",
 "Hamvazószerda után",
 };
const char *text_V_OKTAVE_NARODENIA[POCET_JAZYKOV + 1] = 
{"v oktáve Narodenia Pána",
 "v oktávu Narození Pánì",
 "",
 "",
 "",
 "v oktávu Narození Pánì",
 "Karácsony nyolcadában",
 };

#endif // __HODIN_H_

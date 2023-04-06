/**************************************************************/
/*                                                            */
/* dbzaltar.cpp                                               */
/* (c)1999-2023 | Juraj Vidéky | videky@breviar.sk            */
/*                                                            */
/* description | contains 'database' of liturgical calendars  */
/*                                                            */
/**************************************************************/

#include "vstudio.h"

#ifndef __DBZALTAR_CPP_
#define __DBZALTAR_CPP_

#include "dbzaltar.h"
#include "liturgia.h"
#include "myexpt.h"
#include "mylog.h"
#include <string.h>
#include "mystring.h"
#include "breviar.h"

char _anchor_head[MAX_STR_AF_ANCHOR];
char _anchor_head_without_underscore[MAX_STR_AF_ANCHOR];

// has celebration its own psalmody? cf. General Instrucions, n. 134
short int su_zalmy_vlastne(short int m) {
	Log("su_zalmy_vlastne(%d): ", m);
	short int ret;
	ret = FALSE;
	if (!(je_modlitba_cez_den(m))) {
		if (_global_poradie_svaty == 0) {
			if (_je_global_den_slavnost || _je_global_den_sviatok) {
				ret = TRUE;
			}
		}
		else if (_global_poradie_svaty != PORADIE_PM_SOBOTA) {
			if ((_je_global_svaty_i_slavnost(_global_poradie_svaty)) || (_je_global_svaty_i_sviatok(_global_poradie_svaty))) {
				ret = TRUE;
			}
		}
		if (_global_den.denvt == DEN_NEDELA) {
			ret = TRUE;
		}// DEN_NEDELA
	}// nie mcd
	// pre 2.11. sa berú žalmy vlastné
	if ((_global_den.den == 2) && (_global_den.mesiac - 1 == MES_NOV)) {
		ret = TRUE;
	}// NOV02 == 02NOV
	Log("%d\n", ret);
	return ret;
}// su_zalmy_vlastne()

// has celebration its own psalmody for 1st vespers?
short int su_zalmy_prve_vespery_vlastne(short int m) {
	Log("su_zalmy_prve_vespery_vlastne(%d): ", m);
	short int ret;
	ret = FALSE;
	if ((m == MODL_PRVE_VESPERY) || (m == MODL_VESPERY)) {
		if (_global_poradie_svaty == 0) {
			if (_je_global_den_slavnost) {
				ret = TRUE;
			}
		}
		else if (_global_poradie_svaty != PORADIE_PM_SOBOTA) {
			if (_je_global_svaty_i_slavnost(_global_poradie_svaty)) {
				ret = TRUE;
			}
		}
		if (_global_den.denvt == DEN_NEDELA) {
			ret = TRUE;
		}// DEN_NEDELA
		if ((_global_den.den == 2) && (_global_den.mesiac - 1 == MES_NOV)) {
			ret = TRUE;
		}// NOV02 == 02NOV
	}// nie mcd
	Log("%d\n", ret);
	return ret;
}// su_zalmy_prve_vespery_vlastne()

// aj pre spomienky možno brať zo spoločnej časti tieto časti; všeob. smernice č. 235 b)
// rešpektujeme bod č. 235 všeobecných smerníc: "V posvätnom čítaní, v ranných chválach a vo vešperách: b) antifóna na invitatórium, hymnus, krátke čítanie, antifóny na Benediktus a Magnifikat a prosby, ak sú vlastné, musia sa recitovať o príslušnom svätcovi, ináč sa berú buď zo spoločnej časti, alebo z bežného všedného dňa;"
short int su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(short int m) {
	Log("su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(%d): ", m);
	short int ret;
	ret = FALSE;
	if (!(je_modlitba_cez_den(m))) {
		if (_global_poradie_svaty == 0) {
			if (_je_global_den_slavnost || _je_global_den_sviatok || (((_global_den.typslav == SLAV_SPOMIENKA) || (_global_den.typslav == SLAV_LUB_SPOMIENKA)) && (pouzit_na_spomienky_casti_zo_spolocnych_casti))) {
				ret = TRUE;
			}
		}
		else if (_global_poradie_svaty != PORADIE_PM_SOBOTA) {
			if ((_je_global_svaty_i_slavnost(_global_poradie_svaty)) || (_je_global_svaty_i_sviatok(_global_poradie_svaty)) || (((_global_svaty(_global_poradie_svaty).typslav == SLAV_SPOMIENKA) || (_global_svaty(_global_poradie_svaty).typslav == SLAV_LUB_SPOMIENKA)) && (pouzit_na_spomienky_casti_zo_spolocnych_casti))) {
				ret = TRUE;
			}
		}
	}// nie mcd
	// pre 2.11. sa vlastný hymnus berie aj pre modlitbu cez deň
	if ((_global_den.den == 2) && (_global_den.mesiac - 1 == MES_NOV)) {
		ret = TRUE;
	}// NOV02 == 02NOV
	Log("%d\n", ret);
	return ret;
}// su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne()

short int je_1cit_vlastne(short int m) {
	Log("je_1cit_vlastne(%d): ", m);
	short int ret;
	ret = FALSE;
	if (m == MODL_POSV_CITANIE) {
		if (_global_poradie_svaty == 0) {
			if (_je_global_den_slavnost || _je_global_den_sviatok)
				ret = TRUE;
		}
		else if (_global_poradie_svaty != PORADIE_PM_SOBOTA) {
			if ((_je_global_svaty_i_slavnost(_global_poradie_svaty)) || (_je_global_svaty_i_sviatok(_global_poradie_svaty)))
				ret = TRUE;
		}
		if ((_global_den.den == 2) && (_global_den.mesiac - 1 == MES_NOV)) {
			ret = TRUE;
		}// NOV02 == 02NOV
	}// pc
	Log("%d\n", ret);
	return ret;
}// je_1cit_vlastne()

// su_antifony_vlastne aj vtedy, ak je to spomienka a explicitne si vyberie žalmy+antifóny zo spoločnej časti
// rešpektujeme bod č. 235 všeobecných smerníc: "V posvätnom čítaní, v ranných chválach a vo vešperách: a) žalmy s antifónami sa berú z bežného všedného dňa, ak nie sú antifóny a žalmy vlastné, uvedené na príslušných miestach;"
short int su_antifony_vlastne(short int m) {
	Log("su_antifony_vlastne(%d): ", m);
	short int ret;
	ret = FALSE;
	Log("_global_poradie_svaty == %d...\n", _global_poradie_svaty);
	if (_global_poradie_svaty == 0) {
		if (_je_global_den_slavnost) {
			ret = TRUE;
		}
	}
	else if (_global_poradie_svaty != PORADIE_PM_SOBOTA) {
		if (_je_global_svaty_i_slavnost(_global_poradie_svaty)) {
			ret = TRUE;
		}
	}
	if ((m == MODL_RANNE_CHVALY) || (m == MODL_POSV_CITANIE) || (m == MODL_VESPERY)) {
		if (_global_poradie_svaty == 0) {
			if (_je_global_den_sviatok) {
				ret = TRUE;
			}
		}
		else if (_global_poradie_svaty != PORADIE_PM_SOBOTA) {
			if ((_je_global_svaty_i_sviatok(_global_poradie_svaty)) /* || ((_global_svaty(_global_poradie_svaty).typslav == SLAV_SPOMIENKA) && (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU))) */) {
				ret = TRUE;
			}
		}
	}// rch, pc, v
	// pre 2.11. sa vlastné antifóny berú aj pre modlitbu cez deň
	if ((_global_den.den == 2) && (_global_den.mesiac - 1 == MES_NOV)) {
		ret = TRUE;
	}// NOV02 == 02NOV
	Log("%d\n", ret);
	return ret;
}// su_antifony_vlastne()

// zohľadnenie bodov 229, 232, 236 všeobecných smerníc
// 229. V modlitbe cez deň, čiže predpoludním, napoludnie a popoludní (tercia, sexta a nóna), sa berie, ak nie je uvedené inak, hymnus dňa. Žalmy sú z doplnkového cyklu s vlastnou antifónou; v nedeľu sa však berú žalmy z nedele prvého týždňa zo žaltára; krátke čítanie a záverečná modlitba sú vlastné.
//      Na niektoré slávnosti Pána sa uvádzajú osobitné žalmy.
// 232. V modlitbe cez deň, čiže predpoludním, napoludnie a popoludní (tercia, sexta a nóna), sa berie hymnus dňa; žalmy s antifónami sa berú z férie, ak si osobitný dôvod alebo tradícia nevyžaduje v modlitbe cez deň vlastnú antifónu, čo sa uvedie na príslušnom mieste. Krátke čítanie a záverečná modlitba sú vlastné.
// 236. V modlitbe cez deň, čiže predpoludním, napoludnie a popoludní, a v kompletóriu sa neberie nič z ofícia o svätom, všetko je zo všedného dňa.
short int su_kcit_kresp_modlitba_mcd_vlastne(short int m) {
	Log("su_kcit_kresp_modlitba_mcd_vlastne(%d): ", m);
	short int ret;
	ret = FALSE;
	if (je_modlitba_cez_den(m)) {
		if (_global_poradie_svaty == 0) {
			if (_je_global_den_slavnost || _je_global_den_sviatok) {
				ret = TRUE;
			}
		}
		else if (_global_poradie_svaty != PORADIE_PM_SOBOTA) {
			if ((_je_global_svaty_i_slavnost(_global_poradie_svaty)) || (_je_global_svaty_i_sviatok(_global_poradie_svaty))) {
				ret = TRUE;
			}
		}
	}// mcd
	// pre 2.11. sa pre modlitbu cez deň berú vlastné časti
	if ((_global_den.den == 2) && (_global_den.mesiac - 1 == MES_NOV)) {
		ret = TRUE;
	}// NOV02 == 02NOV
	Log("%d\n", ret);
	return ret;
}// su_kcit_kresp_modlitba_mcd_vlastne()

/* priraďovanie spoločnej časti; berie sa iba v prípade slávností resp. sviatkov, pre spomienky a ľubovoľné spomienky by malo ostať to, čo je zo dňa
 * porov. všeobecné smernice, body 
 * o posvätnom čítaní:
 *		62. Nasleduje psalmódia skladajúca sa z troch žalmov (alebo z ich častí, ak príslušné žalmy sú dlhšie). Vo Veľkonočnom trojdní, v dňoch Veľkonočnej oktávy a vo Vianočnej oktáve, ako aj na slávnosti a sviatky sú žalmy vlastné s vlastnými antifónami.
 *		66. Spravidla treba čítať biblické čítanie, ktoré je z vlastnej časti liturgického obdobia, a to podľa Smerníc č. 140-155.
 *		    No na slávnosti a sviatky sa berie biblické čítanie z vlastnej časti alebo zo spoločnej časti.
 *		67. Druhé čítanie s responzóriom sa berie buď z knihy liturgie hodín, alebo z osobitného lekcionára, ktorý poskytuje väčší výber týchto čítaní (o ňom je reč v č. 161). Zvyčajne to býva čítanie, ktoré sa nachádza vo vlastnej časti liturgického obdobia.
 *		    Na slávnosti a sviatky svätých sa berie vlastné hagiografické čítanie, ak také nie je, číta sa druhé čítanie z príslušnej spoločnej časti na sviatky svätých. Na spomienky svätých, keď ich sláveniu nič neprekáža, berie sa druhé čítanie hagiografické, a to namiesto druhého čítania, ktoré na ten deň pripadá (porov. č. 166, 235).
 *		154. Slávnosti a sviatky majú vlastné čítania; ak ich niet, berú sa zo spoločnej časti na sviatky svätých.
 * o antifónach:
 *		117. Na slávnosti sú vlastné antifóny na posvätné čítanie, na ranné chvály, na terciu, sextu a nónu a na vešpery; ak nie sú, berú sa zo spoločnej časti. To isté platí pre sviatky na posvätné čítanie, na ranné chvály a na vešpery.
 *		119. Antifóny na Benediktus a Magnifikat v ofíciu určitého liturgického obdobia sa berú z vlastnej časti liturgického obdobia, ak sú; ináč z bežného žaltára. Na slávnosti a sviatky sa berú z vlastnej časti, ak sú; ináč zo spoločnej časti. Na spomienky, ktoré nemajú vlastnú antifónu, berie sa antifóna zo spoločnej časti alebo z bežného všedného dňa.
 * o žalmoch:
 *		134. Na slávnosti a sviatky, vo Veľkonočnom trojdní a v dňoch Veľkonočnej a Vianočnej oktávy sú pre posvätné čítanie určené vlastné žalmy v súlade s tradíciou; ich vhodnosť osvetľuje zvyčajne antifóna. 
 *		     Tak je to aj pri modlitbe cez deň na niektoré slávnosti Pána a vo Veľkonočnej oktáve.
 *		     Na ranné chvály sa berú žalmy a chválospev z nedele prvého týždňa v žaltári.
 *		     Na prvé vešpery slávností sa berú žalmy podľa starodávneho zvyku zo série Laudáte.
 *		     Druhé vešpery slávností a vešpery sviatkov majú žalmy i chválospev vlastné.
 *		     Na modlitbu cez deň slávností, okrem tých, o ktorých sa už hovorilo, a ak nepripadnú na nedeľu, berú sa žalmy z doplnkového cyklu (graduálne).
 *		     Na sviatky sa na modlitbu cez deň berú žalmy z príslušného dňa v týždni.
 *		135. V ostatných prípadoch sa berú žalmy z bežného žaltára, ibaže by boli určené vlastné antifóny alebo vlastné žalmy.
 * o krátkom čítaní:
 *		157. Zostavené sú teda štyri týždenné série krátkych čítaní v Období „cez rok“, ktoré sú vložené do žaltára, takže sa čítanie počas štyroch týždňov denne mení. Okrem toho sú týždenné série pre Adventné, Vianočné, Pôstne a Veľkonočné obdobie.
 *		     Osobitné vlastné čítania sú na slávnosti a sviatky a pre niektoré spomienky.
 *		     Pre kompletórium je séria čítaní na jeden týždeň.
 * na krátke čítanie nadväzuje krátke responzórium; treba sa k nemu zrejme správať rovnako ako ku krátkemu čítaniu
 * o prosbách (č. 179-193): -- doplnené 2007-10-23
 *		182. Výrazom „prosby“ sa označujú jednak príhovory vo vešperách a jednak vzývania na zasvätenie dňa Bohu pri ranných chválach.
 *		183. Pre väčšiu pestrosť, ale najmä preto, aby sa lepšie vyjadrili mnohoraké potreby Cirkvi aj ľudí podľa rozličných stavov, skupín, osôb, okolností a čias, uvádzajú sa rozličné formuly prosieb na jednotlivé dni žaltárového cyklu v Období „cez rok“, na ostatné posvätné obdobia liturgického roka a na niektoré sviatočné príležitosti.
 *			 
 * o záverečnej modlitbe:
 *		199. Na ranné chvály a vešpery sa táto modlitba berie z própria v nedele, v adventné, vianočné, pôstne a veľkonočné všedné dni, ďalej na slávnosti, sviatky a spomienky. Vo všedné dni v Období „cez rok“ sa táto modlitba berie zo žaltára, aby vyjadrila vlastnú povahu týchto posvätných hodín.
 *		200. V modlitbe cez deň (predpoludním, napoludnie a popoludní) sa táto modlitba berie z própria v nedele, v adventné, vianočné, pôstne a veľkonočné všedné dni, ďalej na slávnosti a sviatky. V ostatné dni sa používajú modlitby, ktoré vystihujú povahu každej z týchto posvätných hodín a sú uvedené v žaltári.
 * a napokon celá časť v závere smerníc, body 218-240
 *			 
 * slávenie slávností, sviatkov a spomienok resp. ľubovoľných spomienok
 * --- slávnosti ---
 *		225. Slávnosti majú prvé vešpery večer predchádzajúceho dňa.
 *		226. Pri prvých i druhých vešperách je vlastný hymnus, antifóny, krátke čítanie s responzóriom a záverečná modlitba; ak nie sú vlastné, berú sa zo spoločnej časti. 
 *			 Obidva žalmy v prvých vešperách sa berú zvyčajne zo série žalmov Laudáte (t. j. žalmy 113, 117, 135, 146, 147, 1-11, 147, 12-20), podľa starodávnej tradície; chválospev z Nového zákona je vyznačený na príslušnom mieste. Pri druhých vešperách sú žalmy a chválospev vlastné. Prosby sú vlastné alebo zo spoločnej časti.
 *		227. V ranných chválach je vlastný hymnus, antifóna, krátke čítanie s responzóriom a záverečná modlitba. Ak nie sú vlastné, berú sa zo spoločnej časti. Žalmy však treba vziať z nedele prvého týždňa zo žaltára. Prosby sú vlastné alebo zo spoločnej časti.
 *		228. V posvätnom čítaní je všetko vlastné: hymnus, antimóny a žalmy, čítania i responzóriá. Prvé čítanie je biblické, druhé hagiografické. Ak ide o svätého, ktorý má iba lokálnu úctu a nemá v própriu osobitné časti, všetko sa berie zo spoločnej časti.
 *			 Na konci posvätného čítania je hymnus Teba, Bože, chválime a vlastná modlitba.
 *		229. V modlitbe cez deň, čiže predpoludním, napoludnie a popoludní (tercia, sexta a nóna), sa berie, ak nie je uvedené inak, hymnus dňa. Žalmy sú z doplnkového cyklu s vlastnou antifónou; v nedeľu sa však berú žalmy z nedele prvého týždňa zo žaltára; krátke čítanie a záverečná modlitba sú vlastné.
 *			 Na niektoré slávnosti Pána sa uvádzajú osobitné žalmy.
 *		230. V kompletóriu je všetko z nedele, a to po prvých i druhých vešperách. 
 * --- sviatky ---
 *		231. Sviatky nemajú prvé vešpery, ak nejde o sviatky Pána, ktoré pripadnú na nedeľu. V posvätnom čítaní, v ranných chválach a vo vešperách je všetko ako na slávnosti.
 *		232. V modlitbe cez deň, čiže predpoludním, napoludnie a popoludní (tercia, sexta a nóna), sa berie hymnus dňa; žalmy s antifónami sa berú z férie, ak si osobitný dôvod alebo tradícia nevyžaduje v modlitbe cez deň vlastnú antifónu, čo sa uvedie na príslušnom mieste. Krátke čítanie a záverečná modlitba sú vlastné.
 *		233. Kompletórium sa recituje ako v obyčajné dni. 
 * --- spomienky a ľubovoľné spomienky ---
 *		234.    Medzi spomienkami záväznými a ľubovoľnými, ak sa slávia, nie je nijaký rozdiel, pokiaľ ide o usporiadanie ofícia; netýka sa to ľubovoľných spomienok, ktoré sa prípadne vyskytnú v privilegovaných obdobiach. 
 *	--- a) Spomienky pripadajúce na obyčajné dni ---
 *		235. V posvätnom čítaní, v ranných chválach a vo vešperách: 
 *				* žalmy s antifónami sa berú z bežného všedného dňa, ak nie sú antifóny a žalmy vlastné, uvedené na príslušných miestach; 
 *				* antifóna na invitatórium, hymnus, krátke čítanie, antifóny na Benediktus a Magnifikat a prosby, ak sú vlastné, musia sa recitovať o príslušnom svätcovi, ináč sa berú buď zo spoločnej časti, alebo z bežného všedného dňa; 
 *				* záverečná modlitba je vždy o svätcovi; 
 *				* v posvätnom čítaní je biblické čítanie s responzóriom z Písma, pripadajúce na bežný deň. Druhé čítanie je hagiografické s vlastným responzóriom alebo zo spoločnej časti. Ak nie je vlastné čítanie, berie sa z textu Otcov z príslušného dňa. 
 *		Vynecháva sa hymnus Teba, Bože, chválime.
 *		236. V modlitbe cez deň, čiže predpoludním, napoludnie a popoludní, a v kompletóriu sa neberie nič z ofícia o svätom, všetko je zo všedného dňa.
 *	--- b) Spomienky pripadajúce na privilegované dni ---
 *		237. V nedele, na slávnosti a na sviatky, ďalej na Popolcovú stredu, vo Svätom týždni a vo Veľkonočnej oktáve sa vynechávajú všetky spomienky, ak by pripadli na tieto dni.
 *		238. Vo všedných dňoch od 17. do 24. decembra, vo Vianočnej oktáve a vo všedných dňoch v Pôstnom období sa neslávi nijaká záväzná spomienka, a to ani v partikulárnych kalendároch. Tie spomienky, ktoré azda na Pôstne obdobie pripadajú, sa v tom roku považujú za ľubovoľné spomienky.
 *		239. Ak by niekto chcel v tých obdobiach osláviť svätého, ktorého spomienka pripadá na ten deň: 
 *				* v posvätnom čítaní po čítaní z Otcov a po responzóriu z vlastnej časti liturgického obdobia pripojí vlastné hagiografické čítanie s responzóriom a uzavrie modlitbou o svätom; 
 *				* okrem toho môže v ranných chválach a vo vešperách po záverečnej modlitbe — jej konklúzia sa vynechá — pripojiť antifónu (vlastnú alebo zo spoločnej časti) a modlitbu o svätom. 
 *	--- c) Sobotná spomienka o Panne Márii ---
 *		240. V soboty v Období „cez rok“, keď sú dovolené ľubovoľné spomienky, môže sa tým istým spôsobom sláviť ľubovoľná spomienka o Panne Márii s vlastným čítaním. 
 * 
 * teda treba upraviť, aby krátke responzórium (rch, v) bolo vždy rovnako pridávané ako krátke čítanie,
 * napokon aby prosby boli na slávnosti a sviatky vlastné resp. zo spoločnej časti a na (ľub.) spomienky primárne zo dňa
 * 
 */

void _set_popis(short int modlitba, const char* file, const char* anchor){
	switch (modlitba){
	case MODL_INVITATORIUM:
		mystrcpy(_global_modl_invitatorium.popis.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_invitatorium.popis.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_KOMPLETORIUM:
		mystrcpy(_global_modl_prve_kompletorium.popis.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_kompletorium.popis.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_KOMPLETORIUM:
		mystrcpy(_global_modl_kompletorium.popis.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_kompletorium.popis.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_RANNE_CHVALY:
		mystrcpy(_global_modl_ranne_chvaly.popis.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_ranne_chvaly.popis.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_POSV_CITANIE:
		mystrcpy(_global_modl_posv_citanie.popis.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_posv_citanie.popis.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_9:
		mystrcpy(_global_modl_cez_den_9.popis.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_9.popis.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_12:
		mystrcpy(_global_modl_cez_den_12.popis.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_12.popis.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_3:
		mystrcpy(_global_modl_cez_den_3.popis.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_3.popis.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_VESPERY:
		mystrcpy(_global_modl_vespery.popis.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_vespery.popis.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_VESPERY:
		mystrcpy(_global_modl_prve_vespery.popis.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_vespery.popis.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
}

// nastav bitový príznak "je LEN doplnková psalmódia" (t. j. je predpísaná doplnková psalmódia)
void _set_mcd_len_doplnkova_psalmodia(short int modlitba){
	switch (modlitba){
	case MODL_CEZ_DEN_9:
		_global_modl_cez_den_9.alternativy += ((_global_modl_cez_den_9.alternativy & BIT_ALT_LEN_DOPLNKOVA_PSALMODIA) != BIT_ALT_LEN_DOPLNKOVA_PSALMODIA) ? BIT_ALT_LEN_DOPLNKOVA_PSALMODIA : 0;
		break;
	case MODL_CEZ_DEN_12:
		_global_modl_cez_den_12.alternativy += ((_global_modl_cez_den_12.alternativy & BIT_ALT_LEN_DOPLNKOVA_PSALMODIA) != BIT_ALT_LEN_DOPLNKOVA_PSALMODIA) ? BIT_ALT_LEN_DOPLNKOVA_PSALMODIA : 0;
		break;
	case MODL_CEZ_DEN_3:
		_global_modl_cez_den_3.alternativy += ((_global_modl_cez_den_3.alternativy & BIT_ALT_LEN_DOPLNKOVA_PSALMODIA) != BIT_ALT_LEN_DOPLNKOVA_PSALMODIA) ? BIT_ALT_LEN_DOPLNKOVA_PSALMODIA : 0;
		break;
	} // switch(modlitba)
}// _set_mcd_len_doplnkova_psalmodia()

// odstráň bitový príznak "je LEN doplnková psalmódia" (t. j. nie je predpísaná doplnková psalmódia)
void _set_mcd_doplnkova_psalmodia_alternativy(short int modlitba){
	switch (modlitba){
	case MODL_CEZ_DEN_9:
		_global_modl_cez_den_9.alternativy -= ((_global_modl_cez_den_9.alternativy & BIT_ALT_LEN_DOPLNKOVA_PSALMODIA) == BIT_ALT_LEN_DOPLNKOVA_PSALMODIA) ? BIT_ALT_LEN_DOPLNKOVA_PSALMODIA : 0;
		break;
	case MODL_CEZ_DEN_12:
		_global_modl_cez_den_12.alternativy -= ((_global_modl_cez_den_12.alternativy & BIT_ALT_LEN_DOPLNKOVA_PSALMODIA) == BIT_ALT_LEN_DOPLNKOVA_PSALMODIA) ? BIT_ALT_LEN_DOPLNKOVA_PSALMODIA : 0;
		break;
	case MODL_CEZ_DEN_3:
		_global_modl_cez_den_3.alternativy -= ((_global_modl_cez_den_3.alternativy & BIT_ALT_LEN_DOPLNKOVA_PSALMODIA) == BIT_ALT_LEN_DOPLNKOVA_PSALMODIA) ? BIT_ALT_LEN_DOPLNKOVA_PSALMODIA : 0;
		break;
	} // switch(modlitba)
}// _set_mcd_doplnkova_psalmodia_alternativy()

// nastav bitový príznak "je možné brať žalm 129 namiesto žalmu 122 v doplnkovej psalmódii"
void _set_mcd_doplnkova_psalmodia_z122_129(short int modlitba){
	Log("_set_mcd_doplnkova_psalmodia_z122_129(%d): nastavujem možnosť brať žalm 129 namiesto ž 122...\n", modlitba);
	// stačilo by len pre modlitbu predpoludním
	switch (modlitba){
	case MODL_CEZ_DEN_9:
		_global_modl_cez_den_9.alternativy += ((_global_modl_cez_den_9.alternativy & BIT_ALT_DOPLNK_PSALM_122_129) != BIT_ALT_DOPLNK_PSALM_122_129) ? BIT_ALT_DOPLNK_PSALM_122_129 : 0;
		break;
	case MODL_CEZ_DEN_12:
		_global_modl_cez_den_12.alternativy += ((_global_modl_cez_den_12.alternativy & BIT_ALT_DOPLNK_PSALM_122_129) != BIT_ALT_DOPLNK_PSALM_122_129) ? BIT_ALT_DOPLNK_PSALM_122_129 : 0;
		break;
	case MODL_CEZ_DEN_3:
		_global_modl_cez_den_3.alternativy += ((_global_modl_cez_den_3.alternativy & BIT_ALT_DOPLNK_PSALM_122_129) != BIT_ALT_DOPLNK_PSALM_122_129) ? BIT_ALT_DOPLNK_PSALM_122_129 : 0;
		break;
	} // switch(modlitba)
}// _set_mcd_doplnkova_psalmodia_z122_129()

// nastav bitový príznak "je možné brať žalm 129 namiesto žalmu 126 v doplnkovej psalmódii"
void _set_mcd_doplnkova_psalmodia_z126_129(short int modlitba){
	Log("_set_mcd_doplnkova_psalmodia_z126_129(%d): nastavujem možnosť brať žalm 129 namiesto ž 126...\n", modlitba);
	// stačilo by len pre modlitbu predpoludním
	switch (modlitba){
	case MODL_CEZ_DEN_9:
		_global_modl_cez_den_9.alternativy += ((_global_modl_cez_den_9.alternativy & BIT_ALT_DOPLNK_PSALM_126_129) != BIT_ALT_DOPLNK_PSALM_126_129) ? BIT_ALT_DOPLNK_PSALM_126_129 : 0;
		break;
	case MODL_CEZ_DEN_12:
		_global_modl_cez_den_12.alternativy += ((_global_modl_cez_den_12.alternativy & BIT_ALT_DOPLNK_PSALM_126_129) != BIT_ALT_DOPLNK_PSALM_126_129) ? BIT_ALT_DOPLNK_PSALM_126_129 : 0;
		break;
	case MODL_CEZ_DEN_3:
		_global_modl_cez_den_3.alternativy += ((_global_modl_cez_den_3.alternativy & BIT_ALT_DOPLNK_PSALM_126_129) != BIT_ALT_DOPLNK_PSALM_126_129) ? BIT_ALT_DOPLNK_PSALM_126_129 : 0;
		break;
	} // switch(modlitba)
}// _set_mcd_doplnkova_psalmodia_z126_129()

// nastav bitový príznak "je možné brať žalm 131 namiesto žalmu 127 v doplnkovej psalmódii"
void _set_mcd_doplnkova_psalmodia_z127_131(short int modlitba){
	Log("_set_mcd_doplnkova_psalmodia_z127_131(%d): nastavujem možnosť brať žalm 131 namiesto ž 127...\n", modlitba);
	// stačilo by len pre modlitbu popoludní
	switch (modlitba){
	case MODL_CEZ_DEN_9:
		_global_modl_cez_den_9.alternativy += ((_global_modl_cez_den_9.alternativy & BIT_ALT_DOPLNK_PSALM_127_131) != BIT_ALT_DOPLNK_PSALM_127_131) ? BIT_ALT_DOPLNK_PSALM_127_131 : 0;
		break;
	case MODL_CEZ_DEN_12:
		_global_modl_cez_den_12.alternativy += ((_global_modl_cez_den_12.alternativy & BIT_ALT_DOPLNK_PSALM_127_131) != BIT_ALT_DOPLNK_PSALM_127_131) ? BIT_ALT_DOPLNK_PSALM_127_131 : 0;
		break;
	case MODL_CEZ_DEN_3:
		_global_modl_cez_den_3.alternativy += ((_global_modl_cez_den_3.alternativy & BIT_ALT_DOPLNK_PSALM_127_131) != BIT_ALT_DOPLNK_PSALM_127_131) ? BIT_ALT_DOPLNK_PSALM_127_131 : 0;
		break;
	} // switch(modlitba)
}// _set_mcd_doplnkova_psalmodia_z122_129()

// nastav bitový príznak "je možné brať žalm 150 namiesto žalmu 146 v ranných chválach pre ofícium za zosnulých"
void _set_rchvaly_z146_150(short int modlitba) {
	Log("_set_rchvaly_z146_150(%d): nastavujem možnosť brať žalm 150 namiesto žalmu 146...\n", modlitba);
	switch (modlitba) {
	case MODL_RANNE_CHVALY:
		_global_modl_ranne_chvaly.alternativy += ((_global_modl_ranne_chvaly.alternativy & BIT_ALT_OFF_DEF_PSALM_146_150) != BIT_ALT_OFF_DEF_PSALM_146_150) ? BIT_ALT_OFF_DEF_PSALM_146_150 : 0;
		break;
	} // switch(modlitba)
} // _set_rchvaly_z146_150()

void _set_hymnus_alternativy(short int modlitba, short int litobd) {
	Log("_set_hymnus_alternativy(%s, %s): begin...\n", nazov_modlitby(modlitba), nazov_obdobia(litobd));
	short int bit = 0;

	switch (litobd)
	{
	case OBD_CEZ_ROK:
		bit = BIT_ALT_HYMNUS;
		break;
	case OBD_VELKONOCNE_I:
		bit = BIT_ALT_HYMNUS_VN;
		break;
	} // switch(litobd)

	if (bit > 0) {
		switch (modlitba) {
		case MODL_PRVE_KOMPLETORIUM:
			_global_modl_prve_kompletorium.alternativy += ((_global_modl_prve_kompletorium.alternativy & bit) != bit) ? bit : 0;
			break;
		case MODL_KOMPLETORIUM:
		case MODL_DRUHE_KOMPLETORIUM:
			_global_modl_kompletorium.alternativy += ((_global_modl_kompletorium.alternativy & bit) != bit) ? bit : 0;
			break;
		case MODL_RANNE_CHVALY:
			_global_modl_ranne_chvaly.alternativy += ((_global_modl_ranne_chvaly.alternativy & bit) != bit) ? bit : 0;
			break;
		case MODL_POSV_CITANIE:
			_global_modl_posv_citanie.alternativy += ((_global_modl_posv_citanie.alternativy & bit) != bit) ? bit : 0;
			break;
		case MODL_CEZ_DEN_9:
			_global_modl_cez_den_9.alternativy += ((_global_modl_cez_den_9.alternativy & bit) != bit) ? bit : 0;
			break;
		case MODL_CEZ_DEN_12:
			_global_modl_cez_den_12.alternativy += ((_global_modl_cez_den_12.alternativy & bit) != bit) ? bit : 0;
			break;
		case MODL_CEZ_DEN_3:
			_global_modl_cez_den_3.alternativy += ((_global_modl_cez_den_3.alternativy & bit) != bit) ? bit : 0;
			break;
		case MODL_VESPERY:
			_global_modl_vespery.alternativy += ((_global_modl_vespery.alternativy & bit) != bit) ? bit : 0;
			break;
		case MODL_PRVE_VESPERY:
			_global_modl_prve_vespery.alternativy += ((_global_modl_prve_vespery.alternativy & bit) != bit) ? bit : 0;
			break;
		} // switch(modlitba)
	}
	Log("_set_hymnus_alternativy(): end; bit == %d\n", bit);
} // _set_hymnus_alternativy() -- dva parametre

// pre Cezročné obdobie | per annum
void _set_hymnus_alternativy(short int modlitba){
	_set_hymnus_alternativy(modlitba, OBD_CEZ_ROK);
}// _set_hymnus_alternativy()

void _set_hymnus_alternativy_NO(short int modlitba, short int litobd){
	Log("_set_hymnus_alternativy_NO(%s, %s): begin...\n", nazov_modlitby(modlitba), nazov_obdobia(litobd));
	short int bit = 0;

	switch (litobd)
	{
	case OBD_CEZ_ROK:
		bit = BIT_ALT_HYMNUS;
		break;
	case OBD_VELKONOCNE_I:
		bit = BIT_ALT_HYMNUS_VN;
		break;
	} // switch(litobd)

	if (bit > 0){
		switch (modlitba){
		case MODL_PRVE_KOMPLETORIUM:
			_global_modl_prve_kompletorium.alternativy -= ((_global_modl_prve_kompletorium.alternativy & bit) == bit) ? bit : 0;
			break;
		case MODL_KOMPLETORIUM:
			_global_modl_kompletorium.alternativy -= ((_global_modl_kompletorium.alternativy & bit) == bit) ? bit : 0;
			break;
		case MODL_RANNE_CHVALY:
			_global_modl_ranne_chvaly.alternativy -= ((_global_modl_ranne_chvaly.alternativy & bit) == bit) ? bit : 0;
			break;
		case MODL_POSV_CITANIE:
			_global_modl_posv_citanie.alternativy -= ((_global_modl_posv_citanie.alternativy & bit) == bit) ? bit : 0;
			break;
		case MODL_CEZ_DEN_9:
			_global_modl_cez_den_9.alternativy -= ((_global_modl_cez_den_9.alternativy & bit) == bit) ? bit : 0;
			break;
		case MODL_CEZ_DEN_12:
			_global_modl_cez_den_12.alternativy -= ((_global_modl_cez_den_12.alternativy & bit) == bit) ? bit : 0;
			break;
		case MODL_CEZ_DEN_3:
			_global_modl_cez_den_3.alternativy -= ((_global_modl_cez_den_3.alternativy & bit) == bit) ? bit : 0;
			break;
		case MODL_VESPERY:
			_global_modl_vespery.alternativy -= ((_global_modl_vespery.alternativy & bit) == bit) ? bit : 0;
			break;
		case MODL_PRVE_VESPERY:
			_global_modl_prve_vespery.alternativy -= ((_global_modl_prve_vespery.alternativy & bit) == bit) ? bit : 0;
			break;
		} // switch(modlitba)
	}
	Log("_set_hymnus_alternativy_NO(): end; bit == %d\n", bit);
}// _set_hymnus_alternativy_NO() -- dva parametre

// pre Cezročné obdobie | per annum
void _set_hymnus_alternativy_NO(short int modlitba){
	_set_hymnus_alternativy_NO(modlitba, OBD_CEZ_ROK);
}// _set_hymnus_alternativy_NO()

void _set_hymnus(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_PRVE_KOMPLETORIUM:
		mystrcpy(_global_modl_prve_kompletorium.hymnus.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_kompletorium.hymnus.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_KOMPLETORIUM:
		mystrcpy(_global_modl_kompletorium.hymnus.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_kompletorium.hymnus.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_RANNE_CHVALY:
		mystrcpy(_global_modl_ranne_chvaly.hymnus.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_ranne_chvaly.hymnus.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_POSV_CITANIE:
		mystrcpy(_global_modl_posv_citanie.hymnus.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_posv_citanie.hymnus.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_9:
		mystrcpy(_global_modl_cez_den_9.hymnus.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_9.hymnus.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_12:
		mystrcpy(_global_modl_cez_den_12.hymnus.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_12.hymnus.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_3:
		mystrcpy(_global_modl_cez_den_3.hymnus.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_3.hymnus.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_VESPERY:
		mystrcpy(_global_modl_vespery.hymnus.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_vespery.hymnus.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_VESPERY:
		mystrcpy(_global_modl_prve_vespery.hymnus.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_vespery.hymnus.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_hymnus()

void _set_antifona1(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_INVITATORIUM:
		mystrcpy(_global_modl_invitatorium.antifona1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_invitatorium.antifona1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_KOMPLETORIUM:
		mystrcpy(_global_modl_prve_kompletorium.antifona1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_kompletorium.antifona1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_KOMPLETORIUM:
		mystrcpy(_global_modl_kompletorium.antifona1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_kompletorium.antifona1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_RANNE_CHVALY:
		mystrcpy(_global_modl_ranne_chvaly.antifona1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_ranne_chvaly.antifona1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_9:
		mystrcpy(_global_modl_cez_den_9.antifona1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_9.antifona1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_12:
		mystrcpy(_global_modl_cez_den_12.antifona1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_12.antifona1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_3:
		mystrcpy(_global_modl_cez_den_3.antifona1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_3.antifona1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_VESPERY:
		mystrcpy(_global_modl_vespery.antifona1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_vespery.antifona1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_VESPERY:
		mystrcpy(_global_modl_prve_vespery.antifona1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_vespery.antifona1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_POSV_CITANIE:
		mystrcpy(_global_modl_posv_citanie.antifona1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_posv_citanie.antifona1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_antifona1()

void _set_antifona2(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_PRVE_KOMPLETORIUM:
		mystrcpy(_global_modl_prve_kompletorium.antifona2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_kompletorium.antifona2.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_KOMPLETORIUM:
		mystrcpy(_global_modl_kompletorium.antifona2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_kompletorium.antifona2.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_RANNE_CHVALY:
		mystrcpy(_global_modl_ranne_chvaly.antifona2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_ranne_chvaly.antifona2.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_9:
		mystrcpy(_global_modl_cez_den_9.antifona2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_9.antifona2.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_12:
		mystrcpy(_global_modl_cez_den_12.antifona2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_12.antifona2.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_3:
		mystrcpy(_global_modl_cez_den_3.antifona2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_3.antifona2.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_VESPERY:
		mystrcpy(_global_modl_vespery.antifona2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_vespery.antifona2.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_VESPERY:
		mystrcpy(_global_modl_prve_vespery.antifona2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_vespery.antifona2.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_POSV_CITANIE:
		mystrcpy(_global_modl_posv_citanie.antifona2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_posv_citanie.antifona2.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_antifona2()

void _set_antifona3(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_RANNE_CHVALY:
		mystrcpy(_global_modl_ranne_chvaly.antifona3.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_ranne_chvaly.antifona3.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_9:
		mystrcpy(_global_modl_cez_den_9.antifona3.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_9.antifona3.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_12:
		mystrcpy(_global_modl_cez_den_12.antifona3.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_12.antifona3.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_3:
		mystrcpy(_global_modl_cez_den_3.antifona3.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_3.antifona3.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_VESPERY:
		mystrcpy(_global_modl_vespery.antifona3.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_vespery.antifona3.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_VESPERY:
		mystrcpy(_global_modl_prve_vespery.antifona3.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_vespery.antifona3.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_POSV_CITANIE:
		mystrcpy(_global_modl_posv_citanie.antifona3.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_posv_citanie.antifona3.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_antifona3()

void _set_zalm1(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_INVITATORIUM:
		mystrcpy(_global_modl_invitatorium.zalm1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_invitatorium.zalm1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_KOMPLETORIUM:
		mystrcpy(_global_modl_prve_kompletorium.zalm1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_kompletorium.zalm1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_KOMPLETORIUM:
		mystrcpy(_global_modl_kompletorium.zalm1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_kompletorium.zalm1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_RANNE_CHVALY:
		mystrcpy(_global_modl_ranne_chvaly.zalm1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_ranne_chvaly.zalm1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
		// modlitby cez den maju spolocnu psalmodiu, pokial si pouzivatel nevyziada doplnkovu psalmodiu (seria 1-3), preto nastavujem aj spolocne pre vsetky modlitby
	case MODL_CEZ_DEN_VSETKY:
	case MODL_PREDPOLUDNIM:
		// predpoludnim
		mystrcpy(_global_modl_cez_den_9.zalm1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_9.zalm1.anchor, anchor, MAX_STR_AF_ANCHOR);
		if (modlitba != MODL_CEZ_DEN_VSETKY) break;
		// [[fallthrough]];
	case MODL_NAPOLUDNIE:
		// napoludnie
		mystrcpy(_global_modl_cez_den_12.zalm1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_12.zalm1.anchor, anchor, MAX_STR_AF_ANCHOR);
		if (modlitba != MODL_CEZ_DEN_VSETKY) break;
		// [[fallthrough]];
	case MODL_POPOLUDNI:
		// popoludni
		mystrcpy(_global_modl_cez_den_3.zalm1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_3.zalm1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break; // also for MODL_CEZ_DEN_VSETKY
	case MODL_VESPERY:
		mystrcpy(_global_modl_vespery.zalm1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_vespery.zalm1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_VESPERY:
		mystrcpy(_global_modl_prve_vespery.zalm1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_vespery.zalm1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_POSV_CITANIE:
		mystrcpy(_global_modl_posv_citanie.zalm1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_posv_citanie.zalm1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_zalm1()

void _set_zalm2(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_PRVE_KOMPLETORIUM:
		mystrcpy(_global_modl_prve_kompletorium.zalm2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_kompletorium.zalm2.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_KOMPLETORIUM:
		mystrcpy(_global_modl_kompletorium.zalm2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_kompletorium.zalm2.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_RANNE_CHVALY:
		mystrcpy(_global_modl_ranne_chvaly.zalm2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_ranne_chvaly.zalm2.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
		// modlitby cez den maju spolocnu psalmodiu, pokial si pouzivatel nevyziada doplnkovu psalmodiu (seria 1-3), preto nastavujem aj spolocne pre vsetky modlitby
	case MODL_CEZ_DEN_VSETKY:
	case MODL_PREDPOLUDNIM:
		// predpoludnim
		mystrcpy(_global_modl_cez_den_9.zalm2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_9.zalm2.anchor, anchor, MAX_STR_AF_ANCHOR);
		if (modlitba != MODL_CEZ_DEN_VSETKY) break;
		// [[fallthrough]];
	case MODL_NAPOLUDNIE:
		// napoludnie
		mystrcpy(_global_modl_cez_den_12.zalm2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_12.zalm2.anchor, anchor, MAX_STR_AF_ANCHOR);
		if (modlitba != MODL_CEZ_DEN_VSETKY) break;
		// [[fallthrough]];
	case MODL_POPOLUDNI:
		// popoludni
		mystrcpy(_global_modl_cez_den_3.zalm2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_3.zalm2.anchor, anchor, MAX_STR_AF_ANCHOR);
		break; // also for MODL_CEZ_DEN_VSETKY
	case MODL_VESPERY:
		mystrcpy(_global_modl_vespery.zalm2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_vespery.zalm2.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_VESPERY:
		mystrcpy(_global_modl_prve_vespery.zalm2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_vespery.zalm2.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_POSV_CITANIE:
		mystrcpy(_global_modl_posv_citanie.zalm2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_posv_citanie.zalm2.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_zalm2()

void _set_zalm3(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_RANNE_CHVALY:
		mystrcpy(_global_modl_ranne_chvaly.zalm3.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_ranne_chvaly.zalm3.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
		// modlitby cez den maju spolocnu psalmodiu, pokial si pouzivatel nevyziada doplnkovu psalmodiu (seria 1-3), preto nastavujem aj spolocne pre vsetky modlitby
	case MODL_CEZ_DEN_VSETKY:
	case MODL_PREDPOLUDNIM:
		// predpoludnim
		mystrcpy(_global_modl_cez_den_9.zalm3.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_9.zalm3.anchor, anchor, MAX_STR_AF_ANCHOR);
		if (modlitba != MODL_CEZ_DEN_VSETKY) break;
		// [[fallthrough]];
	case MODL_NAPOLUDNIE:
		// napoludnie
		mystrcpy(_global_modl_cez_den_12.zalm3.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_12.zalm3.anchor, anchor, MAX_STR_AF_ANCHOR);
		if (modlitba != MODL_CEZ_DEN_VSETKY) break;
		// [[fallthrough]];
	case MODL_POPOLUDNI:
		// popoludni
		mystrcpy(_global_modl_cez_den_3.zalm3.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_3.zalm3.anchor, anchor, MAX_STR_AF_ANCHOR);
		break; // also for MODL_CEZ_DEN_VSETKY
	case MODL_VESPERY:
		mystrcpy(_global_modl_vespery.zalm3.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_vespery.zalm3.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_VESPERY:
		mystrcpy(_global_modl_prve_vespery.zalm3.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_vespery.zalm3.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_POSV_CITANIE:
		mystrcpy(_global_modl_posv_citanie.zalm3.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_posv_citanie.zalm3.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_zalm3()

void set_zalm(short int ktory, short int modlitba, const char* file, const char* anchor) {
	switch (ktory) {
	case 1:
		_set_zalm1(modlitba, file, anchor);
		break;
	case 2:
		_set_zalm2(modlitba, file, anchor);
		break;
	case 3:
		_set_zalm3(modlitba, file, anchor);
		break;
	} // switch(ktory)
	Log("_set_zalm%d: %s: súbor `%s', kotva `%s' [volanie set_zalm()]\n", ktory, (modlitba == MODL_CEZ_DEN_VSETKY) ? "MCD-all" : ((modlitba <= POCET_MODLITIEB) ? nazov_modlitby(modlitba) : STR_EMPTY), file, anchor);
} // set_zalm()

void _set_kcitanie(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_PRVE_KOMPLETORIUM:
		mystrcpy(_global_modl_prve_kompletorium.kcitanie.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_kompletorium.kcitanie.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_KOMPLETORIUM:
		mystrcpy(_global_modl_kompletorium.kcitanie.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_kompletorium.kcitanie.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_RANNE_CHVALY:
		mystrcpy(_global_modl_ranne_chvaly.kcitanie.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_ranne_chvaly.kcitanie.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_9:
		mystrcpy(_global_modl_cez_den_9.kcitanie.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_9.kcitanie.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_12:
		mystrcpy(_global_modl_cez_den_12.kcitanie.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_12.kcitanie.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_3:
		mystrcpy(_global_modl_cez_den_3.kcitanie.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_3.kcitanie.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_VESPERY:
		mystrcpy(_global_modl_vespery.kcitanie.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_vespery.kcitanie.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_VESPERY:
		mystrcpy(_global_modl_prve_vespery.kcitanie.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_vespery.kcitanie.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_POSV_CITANIE:
		mystrcpy(_global_modl_posv_citanie.citanie1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_posv_citanie.citanie1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_kcitanie()

// pri posvatnom citani plati pre responz _pred_ citaniami
void _set_kresponz(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_PRVE_KOMPLETORIUM:
		mystrcpy(_global_modl_prve_kompletorium.kresponz.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_kompletorium.kresponz.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_KOMPLETORIUM:
		mystrcpy(_global_modl_kompletorium.kresponz.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_kompletorium.kresponz.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_RANNE_CHVALY:
		mystrcpy(_global_modl_ranne_chvaly.kresponz.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_ranne_chvaly.kresponz.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_9:
		mystrcpy(_global_modl_cez_den_9.kresponz.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_9.kresponz.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_12:
		mystrcpy(_global_modl_cez_den_12.kresponz.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_12.kresponz.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_3:
		mystrcpy(_global_modl_cez_den_3.kresponz.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_3.kresponz.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_VESPERY:
		mystrcpy(_global_modl_vespery.kresponz.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_vespery.kresponz.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_VESPERY:
		mystrcpy(_global_modl_prve_vespery.kresponz.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_vespery.kresponz.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_POSV_CITANIE:
		mystrcpy(_global_modl_posv_citanie.kresponz.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_posv_citanie.kresponz.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_kresponz()

// the same: _set_magnifikat
void _set_benediktus(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_RANNE_CHVALY:
		mystrcpy(_global_modl_ranne_chvaly.benediktus.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_ranne_chvaly.benediktus.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_VESPERY:
		mystrcpy(_global_modl_vespery.benediktus.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_vespery.benediktus.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_VESPERY:
		mystrcpy(_global_modl_prve_vespery.benediktus.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_vespery.benediktus.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_POSV_CITANIE:
		mystrcpy(_global_modl_posv_citanie.citanie2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_posv_citanie.citanie2.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_KOMPLETORIUM:
		mystrcpy(_global_modl_kompletorium.nunc_dimittis.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_kompletorium.nunc_dimittis.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_KOMPLETORIUM:
		mystrcpy(_global_modl_prve_kompletorium.nunc_dimittis.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_kompletorium.nunc_dimittis.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_benediktus()

// the same: _set_ukonkaj
void _set_prosby(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_RANNE_CHVALY:
		mystrcpy(_global_modl_ranne_chvaly.prosby.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_ranne_chvaly.prosby.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_VESPERY:
		mystrcpy(_global_modl_vespery.prosby.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_vespery.prosby.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_VESPERY:
		mystrcpy(_global_modl_prve_vespery.prosby.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_vespery.prosby.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_KOMPLETORIUM:
		mystrcpy(_global_modl_kompletorium.ukonkaj.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_kompletorium.ukonkaj.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_KOMPLETORIUM:
		mystrcpy(_global_modl_prve_kompletorium.ukonkaj.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_kompletorium.ukonkaj.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_prosby()

void _set_maria_ant(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_KOMPLETORIUM:
		mystrcpy(_global_modl_kompletorium.maria_ant.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_kompletorium.maria_ant.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_KOMPLETORIUM:
		mystrcpy(_global_modl_prve_kompletorium.maria_ant.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_kompletorium.maria_ant.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_maria_ant()

void _set_otcenas_uvod(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_RANNE_CHVALY:
		mystrcpy(_global_modl_ranne_chvaly.otcenas_uvod.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_ranne_chvaly.otcenas_uvod.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_VESPERY:
		mystrcpy(_global_modl_vespery.otcenas_uvod.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_vespery.otcenas_uvod.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_VESPERY:
		mystrcpy(_global_modl_prve_vespery.otcenas_uvod.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_vespery.otcenas_uvod.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_otcenas_uvod()

void _set_modlitba(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_RANNE_CHVALY:
		mystrcpy(_global_modl_ranne_chvaly.modlitba.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_ranne_chvaly.modlitba.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_POSV_CITANIE:
		mystrcpy(_global_modl_posv_citanie.modlitba.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_posv_citanie.modlitba.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_9:
		mystrcpy(_global_modl_cez_den_9.modlitba.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_9.modlitba.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_12:
		mystrcpy(_global_modl_cez_den_12.modlitba.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_12.modlitba.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_CEZ_DEN_3:
		mystrcpy(_global_modl_cez_den_3.modlitba.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_cez_den_3.modlitba.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_VESPERY:
		mystrcpy(_global_modl_vespery.modlitba.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_vespery.modlitba.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_VESPERY:
		mystrcpy(_global_modl_prve_vespery.modlitba.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_vespery.modlitba.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_PRVE_KOMPLETORIUM:
		mystrcpy(_global_modl_prve_kompletorium.modlitba.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_prve_kompletorium.modlitba.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_KOMPLETORIUM:
		mystrcpy(_global_modl_kompletorium.modlitba.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_kompletorium.modlitba.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_modlitba()

// VSLH č. 238 (Spomienky pripadajúce na privilegované dni)
void _set_ant_spomprivileg(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_RANNE_CHVALY:
		mystrcpy(_global_modl_ranne_chvaly.ant_spomprivileg.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_ranne_chvaly.ant_spomprivileg.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_VESPERY:
		mystrcpy(_global_modl_vespery.ant_spomprivileg.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_vespery.ant_spomprivileg.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_ant_spomprivileg()

// VSLH č. 238 (Spomienky pripadajúce na privilegované dni)
void _set_modlitba_spomprivileg(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_RANNE_CHVALY:
		mystrcpy(_global_modl_ranne_chvaly.modlitba_spomprivileg.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_ranne_chvaly.modlitba_spomprivileg.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	case MODL_VESPERY:
		mystrcpy(_global_modl_vespery.modlitba_spomprivileg.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_vespery.modlitba_spomprivileg.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_modlitba_spomprivileg()

// VSLH č. 238 (Spomienky pripadajúce na privilegované dni)
void _set_2citanie_spomprivileg(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_POSV_CITANIE:
		mystrcpy(_global_modl_posv_citanie.citanie_spomprivileg.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_posv_citanie.citanie_spomprivileg.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_2citanie_spomprivileg()

void _set_antifona_vig(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_POSV_CITANIE:
		mystrcpy(_global_modl_posv_citanie.ant_chval.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_posv_citanie.ant_chval.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_antifona_vig()

void _set_chvalospev1(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_POSV_CITANIE:
		mystrcpy(_global_modl_posv_citanie.chval1.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_posv_citanie.chval1.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_chvalospev1()

void _set_chvalospev2(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_POSV_CITANIE:
		mystrcpy(_global_modl_posv_citanie.chval2.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_posv_citanie.chval2.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_chvalospev2()

void _set_chvalospev3(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_POSV_CITANIE:
		mystrcpy(_global_modl_posv_citanie.chval3.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_posv_citanie.chval3.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_chvalospev3()

void _set_evanjelium(short int modlitba, const char* file, const char* anchor) {
	switch (modlitba) {
	case MODL_POSV_CITANIE:
		mystrcpy(_global_modl_posv_citanie.evanjelium.file, file, MAX_STR_AF_FILE);
		mystrcpy(_global_modl_posv_citanie.evanjelium.anchor, anchor, MAX_STR_AF_ANCHOR);
		break;
	} // switch(modlitba)
} // _set_evanjelium()

// chválospevy pre predĺžené slávenie vigílií

void _set_chvalospev_vig_adv(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_iz40.htm", "CHVAL_IZ40VG");
	_set_chvalospev2(modlitba, "ch_iz42.htm", "CHVAL_IZ42VG");
	_set_chvalospev3(modlitba, "ch_iz49.htm", "CHVAL_IZ49VG");
} // _set_chvalospev_vig_adv()

void _set_chvalospev_vig_vian(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_iz26.htm", "CHVAL_IZ26VG");
	_set_chvalospev2(modlitba, "ch_iz40.htm", "CHVAL_IZ40VG2");
	_set_chvalospev3(modlitba, "ch_iz66.htm", "CHVAL_IZ66VG");
} // _set_chvalospev_vig_vian()

void _set_chvalospev_vig_ocr(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_iz33.htm", "CHVAL_IZ33VG2");
	_set_chvalospev2(modlitba, "ch_iz33.htm", "CHVAL_IZ33VG");
	_set_chvalospev3(modlitba, "ch_sir36.htm", "CHVAL_SIR36VG");
} // _set_chvalospev_vig_ocr()

void _set_chvalospev_vig_tk(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_pris9.htm", "CHVAL_PRIS9VG");
	_set_chvalospev2(modlitba, "ch_jer31.htm", "CHVAL_JER31VG");
	_set_chvalospev3(modlitba, "ch_mud16.htm", "CHVAL_MUD16VG");
} // _set_chvalospev_vig_tk()

void _set_chvalospev_vig_srdca(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_iz12.htm", "CHVAL_IZ12VG");
	_set_chvalospev2(modlitba, "ch_1sam2.htm", "CHVAL_1SAM2VG1");
	_set_chvalospev3(modlitba, "ch_1sam2.htm", "CHVAL_1SAM2VG2");
} // _set_chvalospev_vig_srdca()

void _set_chvalospev_vig_knaza(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_iz61.htm", "CHVAL_IZ61VG0"); // sc_ap
	_set_chvalospev2(modlitba, "ch_ez36.htm", "CHVAL_EZ36VG"); // post
	_set_chvalospev3(modlitba, "ch_mud16.htm", "CHVAL_MUD16VG"); // tk
} // _set_chvalospev_vig_srdca()

void _set_chvalospev_vig_vsetkych_svatych(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_tob13.htm", "CHVAL_TOB13,2-8VG");
	_set_chvalospev2(modlitba, "ch_tob13.htm", "CHVAL_TOB13,9-11VG");
	_set_chvalospev3(modlitba, "ch_tob13.htm", "CHVAL_TOB13,13-18VG");
} // _set_chvalospev_vig_vsetkych_svatych()

void _set_chvalospev_vig_krkrala(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_1krn29.htm", "CHVAL_1KRN29VG");
	_set_chvalospev2(modlitba, "ch_iz12.htm", "CHVAL_IZ12VG2");
	_set_chvalospev3(modlitba, "ch_iz61.htm", "CHVAL_IZ61VG");
} // _set_chvalospev_vig_krkrala()

void _set_chvalospev_vig_post(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_jer14.htm", "CHVAL_JER14VG");
	_set_chvalospev2(modlitba, "ch_ez36.htm", "CHVAL_EZ36VG");
	_set_chvalospev3(modlitba, "ch_nar5.htm", "CHVAL_NAR5VG");
} // _set_chvalospev_vig_post()

void _set_chvalospev_vig_vn(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_iz63.htm", "CHVAL_IZ63VG");
	_set_chvalospev2(modlitba, "ch_oz6.htm", "CHVAL_OZ6VG");
	_set_chvalospev3(modlitba, "ch_sof3.htm", "CHVAL_SOF3VG");
} // _set_chvalospev_vig_vn()

void _set_chvalospev_vig_sc_vpchr(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_tob13.htm", "CHVAL_TOB13,8-16VG");
	_set_chvalospev2(modlitba, "ch_iz2.htm", "CHVAL_IZ2VG");
	_set_chvalospev3(modlitba, "ch_jer7.htm", "CHVAL_JER7VG");
} // _set_chvalospev_vig_sc_vpchr()

void _set_chvalospev_vig_sc_pm(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_iz61.htm", "CHVAL_IZ61VG1");
	_set_chvalospev2(modlitba, "ch_iz61.htm", "CHVAL_IZ62VG");
	_set_chvalospev3(modlitba, "ch_sir39.htm", "CHVAL_SIR39VG");
} // _set_chvalospev_vig_sc_pm()

void _set_chvalospev_vig_sc_ap(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_iz61.htm", "CHVAL_IZ61VG0");
	_set_chvalospev2(modlitba, "ch_mud3.htm", "CHVAL_MUD3VG");
	_set_chvalospev3(modlitba, "ch_mud10.htm", "CHVAL_MUD10VG");
} // _set_chvalospev_vig_sc_ap()

void _set_chvalospev_vig_sc_vm(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_mud3.htm", "CHVAL_MUD3VG1");
	_set_chvalospev2(modlitba, "ch_mud3.htm", "CHVAL_MUD3VG");
	_set_chvalospev3(modlitba, "ch_mud10.htm", "CHVAL_MUD10VG");
} // _set_chvalospev_vig_sc_vm()

// pre svätých mužov a sväté ženy, aj pre jedného mučeníka, aj pre panny
void _set_chvalospev_vig_sc_sm_sz(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_jer17.htm", "CHVAL_JER17VG");
	_set_chvalospev2(modlitba, "ch_sir14.htm", "CHVAL_SIR14VG");
	_set_chvalospev3(modlitba, "ch_sir31.htm", "CHVAL_SIR31VG");
} // _set_chvalospev_vig_sc_sm_sz()

void _set_chvalospev_vig_sviatok_obetovania(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_iz9.htm", "CHVAL_IZ9VG");
	_set_chvalospev2(modlitba, "ch_iz26.htm", "CHVAL_IZ26VG2");
	_set_chvalospev3(modlitba, "ch_iz66.htm", "CHVAL_IZ66VG");
} // _set_chvalospev_vig_sviatok_obetovania()

void _set_chvalospev_vig_sc_pm_ocd(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_iz2.htm", "CHVAL_IZ2VG1");
	_set_chvalospev2(modlitba, "ch_iz61.htm", "CHVAL_IZ61VG2");
	_set_chvalospev3(modlitba, "ch_iz61.htm", "CHVAL_IZ62VG3");
} // _set_chvalospev_vig_sc_pm()

void _set_chvalospev_vig_sc_sm_ocd(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_jer17.htm", "CHVAL_JER17VG");
	_set_chvalospev2(modlitba, "ch_sir14.htm", "CHVAL_SIR14VG");
	_set_chvalospev3(modlitba, "ch_sir51.htm", "CHVAL_SIR51VG");
} // _set_chvalospev_vig_sc_sm_ocd()

void _set_chvalospev_vig_terezka_ocd(short int modlitba) {
	_set_chvalospev1(modlitba, "ch_dt32.htm", "CHVAL_DT32VG");
	_set_chvalospev2(modlitba, "ch_pies.htm", "CHVAL_PIES1VG");
	_set_chvalospev3(modlitba, "ch_pies.htm", "CHVAL_PIES4VG");
} // _set_chvalospev_vig_terezka_ocd()


// files - nazvy suborov pre zaltar styroch tyzdnov
char _file[MAX_STR_AF_FILE]; // nazov súboru, napr. _1ne.htm
char _file_pc[MAX_STR_AF_FILE]; // nazov fajlu pre posvatne citania
char _file_pc_tyzden[MAX_STR_AF_FILE]; // nazov fajlu pre posvatne citania v zavislosti od tyzdna (obdobie cez rok)
char _file_orig[MAX_STR_AF_FILE]; // nazov súboru, do ktorého sa v prípade kompletória dočasne odloží pôvodný súbor

// tyzzal == 1 .. 4, den == 0 (DEN_NEDELA) .. 6 (DEN_SOBOTA)
void file_name_zaltar(short int den, short int tyzzal) {
	sprintf(_file, "_%d%s.htm", tyzzal, nazov_dn_asci[den]);
}

void file_name_litobd(short int litobd) {
	sprintf(_file, "%s", nazov_obd_htm[litobd]);
}

void file_name_litobd_pc(short int litobd) {
	sprintf(_file_pc, "%s", nazov_obd_htm_pc[litobd]);
}

// note: use function file_name_vlastny_kalendar() carefully [not in mixed cases: when only language is queried and another language with calendar is queried] because it will destroy celebrations from national calendar when propria are chosen
void file_name_vlastny_kalendar(short int kalendar) {
	// do not use for JAZYK_CZ_OP even if called; do not use for general calendars even if called
	if ((_global_jazyk != JAZYK_CZ_OP) && (_global_kalendar != default_kalendar[_global_jazyk])) {
		sprintf(_file, "%s", nazov_htm_kalendar[kalendar]);
		sprintf(_file_pc, "%s", nazov_htm_kalendar[kalendar]);
	}
}

void file_name_kompletorium(short int litobd) {
	if (litobd == OBD_CEZ_ROK) {
		sprintf(_file, "%s", nazov_obd_KOMPLETORIUM);
	}
	else {
		sprintf(_file, "%s", nazov_obd_htm[litobd]);
	}
}

void file_name_litobd_pc_tyzden(short int litobd, short int tyzden) {
	sprintf(_file_pc_tyzden, "%02d%s", tyzden, nazov_obd_htm_pc[litobd]);
}

// anchors - nazvy kotiev pre zaltar styroch tyzdnov
char _anchor[MAX_STR_AF_ANCHOR];

// tyzzal == 1 .. 4, den == 0 (DEN_NEDELA) .. 6 (DEN_SOBOTA), modlitba == MODL_..., anchor == ANCHOR_...
char pismenko_modlitby(short int modlitba) {
	switch (modlitba) {
	case MODL_INVITATORIUM: return CHAR_MODL_INVITATORIUM;
	case MODL_RANNE_CHVALY: return CHAR_MODL_RANNE_CHVALY;
	case MODL_POSV_CITANIE: return CHAR_MODL_POSV_CITANIE;
	case MODL_CEZ_DEN_9: return CHAR_MODL_CEZ_DEN_9;
	case MODL_CEZ_DEN_12: return CHAR_MODL_CEZ_DEN_12;
	case MODL_CEZ_DEN_3: return CHAR_MODL_CEZ_DEN_3;
	case MODL_VESPERY: return CHAR_MODL_VESPERY;
	case MODL_KOMPLETORIUM: return CHAR_MODL_KOMPLETORIUM;
	case MODL_NEURCENA: return CHAR_MODL_NEURCENA; // toto by sa nemalo
	case MODL_PRVE_VESPERY: return CHAR_MODL_PRVE_VESPERY;
	case MODL_PRVE_KOMPLETORIUM: return CHAR_MODL_PRVE_KOMPLETORIUM;
	case MODL_DRUHE_VESPERY: return CHAR_MODL_DRUHE_VESPERY; // toto by sa nemalo
	case MODL_DRUHE_KOMPLETORIUM: return CHAR_MODL_DRUHE_KOMPLETORIUM; // toto by sa nemalo
	} // switch(modlitba)
	return 0;
} // pismenko_modlitby();

void anchor_name_zaltar(short int den, short int tyzzal, short int modlitba, const char* anchor) {
	sprintf(_anchor, "_%d%s_%c%s", tyzzal, nazov_DN_asci[den], pismenko_modlitby(modlitba), anchor);
}

void anchor_name_zaltar_alt(short int den, short int tyzzal, short int modlitba, const char* anchor, short int alt) {
	sprintf(_anchor, "_%d%s_%c%s%d", tyzzal, nazov_DN_asci[den], pismenko_modlitby(modlitba), anchor, alt);
}

void _add_special_anchor_postfix() {
	strcat(_anchor, _special_anchor_postfix);
}

// hymn for compline
void set_hymnus_kompletorium_obd(short int den, short int tyzzal, short int modlitba, short int litobd) {
	Log("set_hymnus_kompletorium_obd(): začiatok\n");
	short int ktory; // 0 or 1
	// CZ OP: hymnus pre kompletórium i MCD sa strieda po týždňoch: "V naší provincii se vžil zvyk pro obojí - pro kompletář i pro modlitbu během dne, že se používá hymnus "A" pro liché a hymnus "B" pro sudé týdny."
	char _anchor_pom[SMALL];

	// hymnusy sú rovnaké v pôstnom období ako pre cezročné obdobie; hymnus pre veľkonočné obdobie je jediný, odlišný
	short int pom_litobd = litobd;
	file_name_zapamataj();
	// veľkonočné obdobie má jeden hymnus (rovnaký): "Ježišu, Vykupiteľ náš"
	if ((litobd == OBD_VELKONOCNE_I) || (litobd == OBD_VELKONOCNE_II) || (litobd == OBD_VELKONOCNA_OKTAVA) || ((litobd == OBD_VELKONOCNE_TROJDNIE) && (_global_den.denvr == VELKONOCNA_NEDELA))) { // pre celé trojdnie sa berie nedeľné kompletórium, preto sa treba spýtať priamo na VELKONOCNA_NEDELA
		pom_litobd = OBD_VELKONOCNE_I;
	}
	else if ((litobd == OBD_POSTNE_II_VELKY_TYZDEN) && (den != DEN_STVRTOK) && (_global_jazyk == JAZYK_CZ)) {
		// pre český breviář sa nepoužívajú vo svätom týždni iné hymny; pre zelený štvrtok je samostatný hymnus
		pom_litobd = OBD_CEZ_ROK;
	}
	else if ((litobd == OBD_POSTNE_II_VELKY_TYZDEN) && (den == DEN_STVRTOK) && (_global_jazyk == JAZYK_CZ)) {
		// pre český breviář sa nepoužívajú vo svätom týždni iné hymny; pre zelený štvrtok je samostatný hymnus
		; // ponechá pom_litobd, ako je
	}
	else {
		// default
		pom_litobd = OBD_CEZ_ROK;
	}
	file_name_kompletorium(pom_litobd);

	short int dva_hymny = 1; // určuje, či v danom období sú dva hymny (1) alebo nie (0); ak je len jediný, má index 0
	if (pom_litobd == OBD_VELKONOCNE_I) {
		dva_hymny = 0;
	}

	if ((_global_jazyk == JAZYK_CZ) && (!isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_CZ_HYMNY_VYBER))) {
		sprintf(_anchor, "%c_%s_%s", pismenko_modlitby(modlitba), ANCHOR_HYMNUS, nazov_DN_asci[den]);
	}
	else {
		// pre CZOP (český dominikánsky) rovnako ako pre slovenský, teda jeden hymnus VELKONOCNA_NEDELA
		if ((litobd == OBD_ADVENTNE_I)
			|| (litobd == OBD_VIANOCNE_I)
			|| (litobd == OBD_OKTAVA_NARODENIA)
			) { // predpísaný hymnus "Na sklonku dňa ťa úprimne"
			Log("set_hymnus_kompletorium_obd(): predpísaný hymnus A...\n");
			ktory = 0;
		}
		else if ((litobd == OBD_ADVENTNE_II)
			|| (litobd == OBD_VIANOCNE_II)
			|| (litobd == OBD_POSTNE_II_VELKY_TYZDEN)
			|| (litobd == OBD_VELKONOCNE_TROJDNIE)
			) { // predpísaný hymnus "Kriste, ty svetlo a náš deň"; 2008-12-20: aj pre vian. II. a Svätý týždeň
			Log("set_hymnus_kompletorium_obd(): predpísaný hymnus B...\n");
			ktory = 1;
		}
		else if (litobd == OBD_POSTNE_I) {
			// v skutočnosti netreba, používa sa set_hymnus_kompletorium_obd()
			// predpísaný v 1., 3. a 5. týždni "Na sklonku dňa", pre 2. a 4. týždeň hymnus "Kriste, ty svetlo"
			Log("set_hymnus_kompletorium_obd(): predpísaný hymnus v pôste...\n");
			ktory = (tyzzal + 1) % 2;
		}
		else {
			Log("set_hymnus_kompletorium_obd(else/else)...\n");

			if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES) && !(je_CZ_hymny_k_volnemu_vyberu)) {

				// podľa nastavenia _global_opt[OPT_5_ALTERNATIVES]
				ktory = (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_KOMPL)) ? 1 : 0;
				Log("set_hymnus_kompletorium_obd(): ktory == %d...\n", ktory);
			}
			else {
				ktory = 2; // obidva!
			}
		}

		// úprava kotvy pre český breviář, ignorovať aj nastavenie ktory, aj dva_hymny
		if (_global_jazyk == JAZYK_CZ) {
			sprintf(_anchor, "%c_%s", pismenko_modlitby(modlitba), ANCHOR_HYMNUS);
		}
		else {
			sprintf(_anchor, "%c_%s_%d", pismenko_modlitby(modlitba), ANCHOR_HYMNUS, ktory * dva_hymny);
		}

		_add_special_anchor_postfix();
	}

	// úprava kotvy pre český breviář, VN1 (HVV obsahujú o jeden viac ako v mezidobí)
	if ((_global_jazyk == JAZYK_CZ) && (pom_litobd == OBD_VELKONOCNE_I)) {
		mystrcpy(_anchor_pom, _anchor, MAX_STR_AF_ANCHOR);
		sprintf(_anchor, "%s" STR_UNDERSCORE "%s", nazov_OBD[pom_litobd], _anchor_pom);
	}

	_set_hymnus(modlitba, _file, _anchor);
	set_LOG_zaltar;
	file_name_obnov();
	Log("set_hymnus_kompletorium_obd(): koniec.\n");
} // set_hymnus_kompletorium_obd()

void set_hymnus(short int den, short int tyzzal, short int modlitba) {
	Log("set_hymnus(%d, %d, %d): začiatok\n", den, tyzzal, modlitba);
	short int ktory; // 0 alebo 1
	short int bit;

	// kompletórium presunuté do set_hymnus_kompletorium_obd()
	if (je_kompletorium12(modlitba)) {
		set_hymnus_kompletorium_obd(den, tyzzal, modlitba, _global_den.litobd);
	}
	else if (je_modlitba_cez_den(modlitba)) {
		// modlitba cez den ma hymny rovnake pre cele obdobie cez rok 
		// CZ: pre mcd v českom breviári je pre cezročné obdobie možné brať buď hymnus zo žaltára, alebo pre 1./3. (1) resp. 2./4. (2) týždeň žaltára z "vlastnej časti"

		switch (modlitba) {
		case MODL_PREDPOLUDNIM: bit = BIT_OPT_5_HYMNUS_MCD_PREDPOL; break;
		case MODL_NAPOLUDNIE:   bit = BIT_OPT_5_HYMNUS_MCD_NAPOL; break;
		case MODL_POPOLUDNI:    bit = BIT_OPT_5_HYMNUS_MCD_POPOL; break;
		} // switch(modlitba)

		file_name_litobd(OBD_CEZ_ROK);

		if (_global_jazyk == JAZYK_CZ) {
			Log("set_hymnus(): modlitba cez deň: CZ...\n");

			if (!isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_CZ_HYMNY_VYBER)) {
				// hymny ze žaltáře (sudý, lichý)
				sprintf(_anchor, "%c_%s_%s_%s", pismenko_modlitby(modlitba), ANCHOR_HYMNUS, ((tyzzal % 2) == 0) ? CZ_WEEK_EVEN : CZ_WEEK_ODD, nazov_DN_asci[den]);
			}
			else {
				// hymny k volnému výběru
				sprintf(_anchor, "%c_%s", pismenko_modlitby(modlitba), ANCHOR_HYMNUS);
			}
		}
		else {
			Log("set_hymnus(): modlitba cez deň...\n");

			if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES)) {
				// podľa nastavenia _global_opt[OPT_5_ALTERNATIVES]
				ktory = (isGlobalOption(OPT_5_ALTERNATIVES, (unsigned)bit)) ? 1 : 0;
				Log("set_hymnus() [1]: ktory == %d...\n", ktory);
			}
			else {
				ktory = 2; // obidva!
			}
			sprintf(_anchor, "%c_%s_%d", pismenko_modlitby(modlitba), ANCHOR_HYMNUS, ktory);
		}

		_set_hymnus(modlitba, _file, _anchor);
		set_LOG_zaltar;
	}// mcd
	else { // nie modlitba cez deň ani kompletórium
		// prvý a tretí, resp. druhý a štvrtý týždeň majú rovnaké hymny | pre tyzzal == 3 dá tyzzal = 1; pre tyzzal == 4 dá tyzzal = 2
		tyzzal = set_tyzzal_1_2(tyzzal);

		// odvetvenie pre posvatne citania
		if (modlitba == MODL_POSV_CITANIE) {
			Log("set_hymnus(): posv. čítanie...\n");
			file_name_litobd_pc(OBD_CEZ_ROK);
			// pre českú LH nie sú štandardné hymny
			if ((_global_jazyk != JAZYK_CZ) && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES))) {
				// podľa nastavenia _global_opt[OPT_5_ALTERNATIVES]
				ktory = (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_PC)) ? 1 : 0;
				Log("set_hymnus() [2]: ktory == %d...\n", ktory);
				anchor_name_zaltar_alt(den, tyzzal, modlitba, ANCHOR_HYMNUS, ktory);
			}
			else {
				ktory = 2; // obidva (neprilepuje sa, ostáva pôvodná kotva bez čísla)
				anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_HYMNUS);
			}
			_add_special_anchor_postfix();
			_set_hymnus(modlitba, _file_pc, _anchor);
			set_LOG_litobd_pc;
		}
		// odvetvenie pre prvé vešpery
		else if (modlitba == MODL_PRVE_VESPERY) {
			Log("set_hymnus(): prvé vešpery...\n");
			file_name_litobd_pc(OBD_CEZ_ROK);
			// pre českú LH nie sú štandardné hymny
			if ((_global_jazyk != JAZYK_CZ) && (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES))) {
				// podľa nastavenia _global_opt[OPT_5_ALTERNATIVES]
				ktory = (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_HYMNUS_1VESP)) ? 1 : 0;
				Log("set_hymnus() [3]: ktory == %d...\n", ktory);
				if (ktory == 0) {
					// hymnus pre prvé vešpery zo žaltára
					anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_HYMNUS);
					_add_special_anchor_postfix();
					_set_hymnus(modlitba, _file, _anchor);
				}
				else {
					// hymnus pre prvé vešpery ako pre posv. čítanie (cez deň)
					anchor_name_zaltar_alt(DEN_NEDELA, tyzzal, MODL_POSV_CITANIE, ANCHOR_HYMNUS, 1);
					_add_special_anchor_postfix();
					_set_hymnus(modlitba, _file_pc, _anchor);
				}
				anchor_name_zaltar_alt(den, tyzzal, modlitba, ANCHOR_HYMNUS, ktory);
			}
			else {
				ktory = 2; // obidva (neprilepuje sa, ostáva pôvodná kotva bez čísla)
				anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_HYMNUS);
				_add_special_anchor_postfix();
				_set_hymnus(modlitba, _file, _anchor);
			}
			set_LOG_litobd_pc;
		}
		else {
			file_name_zaltar(den, tyzzal);
			anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_HYMNUS);
			_add_special_anchor_postfix();
			_set_hymnus(modlitba, _file, _anchor);
			set_LOG_zaltar;
		}
	}
	Log("set_hymnus(): koniec\n");
} // set_hymnus();

// odlišné antifóny pre Veľkonočné obdobie: Vo Veľkonočnom období: Psalmódia má jedinú antifónu: Aleluja, aleluja, aleluja. (rešpektovaná rovnaká antifóna pre veľkonočné obdobie)
// keďže pre kompletórium je potrebné niekedy nastaviť pre modlitbu "kompletórium" antifóny z modlitby "prvé kompletórium" - pozri _set_kompletorium_slavnost_oktava() - používame na to parameter "zvazok"
// ak zvazok == 9, znamená to špeciálny prípad, že modlitba == MODL_KOMPLETORIUM, ale do stringu treba dať pismenko_modlitby(MODL_PRVE_KOMPLETORIUM)
void set_antifony_kompletorium_obd(short int den, short int modlitba, short int litobd, short int zvazok) {
	Log("set_antifony_kompletorium_obd(%d, %d, %d): začiatok...\n", den, modlitba, zvazok);

	// rovnaké responzórium pre všetky časti veľkonočného obdobia
	if (_je_global_den_slavnost && ((den != DEN_NEDELA) && (den != DEN_SOBOTA))) {
		den = DEN_UNKNOWN; // slávnosť mimo nedieľ
	}

	short int force_prve_nedelne_kompletorium = NIE;
	if ((den == DEN_SOBOTA) && (modlitba == MODL_KOMPLETORIUM)) {
		force_prve_nedelne_kompletorium = ANO;
	}
	short int den_pom = den;
	if (den == DEN_SOBOTA) {
		den_pom = DEN_NEDELA;
		zvazok = 9;
	}

	short int pom_litobd = litobd;
	file_name_zapamataj();
	if ((litobd == OBD_VELKONOCNE_I) || (litobd == OBD_VELKONOCNE_II) || (litobd == OBD_VELKONOCNA_OKTAVA) || ((litobd == OBD_VELKONOCNE_TROJDNIE) && (_global_den.denvr == VELKONOCNA_NEDELA))) { // pre celé trojdnie sa berie nedeľné kompletórium, preto sa treba spýtať priamo na VELKONOCNA_NEDELA
		pom_litobd = OBD_VELKONOCNE_I;
	}
	else {
		// default
		pom_litobd = OBD_CEZ_ROK;
	}
	// file_name_kompletorium((litobd == OBD_VELKONOCNA_OKTAVA || litobd == OBD_VELKONOCNE_II)? OBD_VELKONOCNE_I : litobd);
	file_name_kompletorium(pom_litobd);

	// antifóna 1
	sprintf(_anchor, "_%s%c_%s", nazov_DN_asci[den_pom], (zvazok == 9) ? pismenko_modlitby(MODL_PRVE_KOMPLETORIUM) : pismenko_modlitby(modlitba),
		(pom_litobd == OBD_VELKONOCNE_I) ? ANCHOR_ANTIFONY : ANCHOR_ANTIFONA1);
	_set_antifona1(modlitba, _file, _anchor);
	set_LOG_zaltar;

	// antifóna 2
	if (
		((modlitba == MODL_KOMPLETORIUM) && (_global_modl_kompletorium.pocet_zalmov == 2))
		|| ((modlitba == MODL_PRVE_KOMPLETORIUM) && (_global_modl_prve_kompletorium.pocet_zalmov == 2))
		|| (force_prve_nedelne_kompletorium == ANO)
		) {
		sprintf(_anchor, "_%s%c_%s", nazov_DN_asci[den_pom], (zvazok == 9) ? pismenko_modlitby(MODL_PRVE_KOMPLETORIUM) : pismenko_modlitby(modlitba),
			(pom_litobd == OBD_VELKONOCNE_I) ? ANCHOR_ANTIFONY : ANCHOR_ANTIFONA2);
		_set_antifona2(modlitba, _file, _anchor);
		set_LOG_zaltar;
	}
	file_name_obnov();

	Log("set_antifony_kompletorium_obd(): koniec.\n");
} // set_antifony_kompletorium_obd()

void set_antifony(short int den, short int tyzzal, short int zvazok, short int modlitba) {
	Log("set_antifony(%d, %d, %d, %d): začiatok...\n", den, tyzzal, zvazok, modlitba);

	// keďže pre obyčajné dni veľkonočného obdobia (2.-7. týždeň) možno brať antifóny pre posvätné čítania z cezročného obdobia -> pôvodná podmienka zosilnená
	// pridaný ďalší parameter; pre niektoré dni v II. zväzku sú iné žalmy aj antifóny
	// podmienka zmenená: aj pre nedeľné posv. čítanie sú antifóny v file_name_litobd_pc(OBD_CEZ_ROK);
	short int povodny_tyzzal = tyzzal;

	// pridané časti pre kompletórium
	if (je_kompletorium12(modlitba)) {
		set_antifony_kompletorium_obd(den, modlitba, _global_den.litobd, zvazok);
	}
	else if (
		((_global_den.litobd == OBD_VELKONOCNE_I) ||
		(_global_den.litobd == OBD_VELKONOCNE_II))
		&&
		(modlitba != MODL_POSV_CITANIE)
		) {
		// velkonocne obdobie
		file_name_zaltar(den, tyzzal);
		anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA1V);
		_set_antifona1(modlitba, _file, _anchor);
		set_LOG_zaltar;
		anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA2V);
		_set_antifona2(modlitba, _file, _anchor);
		set_LOG_zaltar;
		// antifona na vecerny hymnus je rovnaka pre prvy a treti, resp. druhy a stvrty tyzden zaltara
		if ((modlitba == MODL_VESPERY) || (modlitba == MODL_PRVE_VESPERY)) {
			tyzzal = set_tyzzal_1_2(tyzzal);
		}
		file_name_zaltar(den, tyzzal);
		anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA3V);
		_set_antifona3(modlitba, _file, _anchor);
		set_LOG_zaltar;
	}
	// Pre posv. čítania nedieľ veľkonočného obdobia samostatne nastavíme, hoci sme si vedomí, že pre 5., 6. a 7. veľkonočnú nedeľu to bude potrebné zmeniť
	else if (
		((_global_den.litobd == OBD_VELKONOCNE_I) ||
		(_global_den.litobd == OBD_VELKONOCNE_II))
		&&
		(modlitba == MODL_POSV_CITANIE)
		&&
		(den == DEN_NEDELA)
		) {
		_set_antifony_velk_pc(den, tyzzal, modlitba);
	}
	else {

		// 1. antifona
		if (modlitba == MODL_POSV_CITANIE) {
			file_name_litobd_pc(OBD_CEZ_ROK);
			anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA1);
			_set_antifona1(modlitba, _file_pc, _anchor);
			set_LOG_litobd_pc;
		}
		else if (modlitba == MODL_INVITATORIUM) {
			// antifóna pre invitatórium je rovnaká pre prvý a tretí, resp. druhý a štvrtý týždeň žaltára
			tyzzal = set_tyzzal_1_2(tyzzal);
			file_name_zaltar(den, tyzzal);
			anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA1);
			_set_antifona1(modlitba, _file, _anchor);
			set_LOG_zaltar;
		}
		else {
			file_name_zaltar(den, tyzzal);
			anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA1);
			_set_antifona1(modlitba, _file, _anchor);
			set_LOG_zaltar;
		}

		// 2. antifona
		if (modlitba == MODL_POSV_CITANIE) {
			file_name_litobd_pc(OBD_CEZ_ROK);
			anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA2);
			_set_antifona2(modlitba, _file_pc, _anchor);
			set_LOG_litobd_pc;
		}
		else if (modlitba != MODL_INVITATORIUM) {
			file_name_zaltar(den, tyzzal);
			anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA2);
			_set_antifona2(modlitba, _file, _anchor);
			set_LOG_zaltar;
		}

		// 3. antifona
		// antifona na vecerny hymnus je rovnaka pre prvy a treti, resp. druhy a stvrty tyzden zaltara
		if ((modlitba == MODL_VESPERY) || (modlitba == MODL_PRVE_VESPERY)) {
			tyzzal = set_tyzzal_1_2(tyzzal);
		}
		if (modlitba == MODL_POSV_CITANIE) {
			file_name_litobd_pc(OBD_CEZ_ROK);
			anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA3);
			_set_antifona3(modlitba, _file_pc, _anchor);
			set_LOG_litobd_pc;
		}
		else if (modlitba != MODL_INVITATORIUM) {
			file_name_zaltar(den, tyzzal);
			anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_ANTIFONA3);
			_set_antifona3(modlitba, _file, _anchor);
			set_LOG_zaltar;
		}
	}
	// 2006-01-24: napokon upravíme niektoré antifóny pre II. zväzok, posvätné čítanie
	if ((je_odlisny_zaltar) && (modlitba == MODL_POSV_CITANIE)) {
		// ide o nasledovné:
		// 1. týždeň: sobota
		// 2. týždeň: sobota
		// 4. týždeň: piatok (asi chceli, aby to bola vždy sobota, ale tento žalm nadväzuje)
		// 4. týždeň: sobota
		if (
			((den == DEN_SOBOTA) && ((povodny_tyzzal == 1) || (povodny_tyzzal == 2) || (povodny_tyzzal == 4)))
			||
			((den == DEN_PIATOK) && (povodny_tyzzal == 4))
			) {
			Log("-- upravujeme antifóny (týždeň + 4), lebo v II. zväzku breviára sú pre tento deň iné...\n");
			file_name_litobd_pc(OBD_CEZ_ROK);
			anchor_name_zaltar(den, 4 + tyzzal, modlitba, ANCHOR_ANTIFONA1);
			_set_antifona1(modlitba, _file_pc, _anchor);
			set_LOG_litobd_pc;
			anchor_name_zaltar(den, 4 + tyzzal, modlitba, ANCHOR_ANTIFONA2);
			_set_antifona2(modlitba, _file_pc, _anchor);
			set_LOG_litobd_pc;
			anchor_name_zaltar(den, 4 + tyzzal, modlitba, ANCHOR_ANTIFONA3);
			_set_antifona3(modlitba, _file_pc, _anchor);
			set_LOG_litobd_pc;
		}
	}

	Log("set_antifony(): koniec.\n");
} // set_antifony()

void set_kcitanie(short int den, short int tyzzal, short int modlitba, short int ktore /* default ktore = 2 */) {
	// doplnené pre veľkonočnú oktávu (parameter "ktore")
	char pismenko_modlitby_pom = pismenko_modlitby(modlitba);
	// Log("set_kcitanie() -- začiatok...\n");
	// Log("den == %d, tyzzal == %d, modlitba == %d, ktore == %d...\n", den, tyzzal, modlitba, ktore);
	if (je_kompletorium12(modlitba)) {
		file_name_zapamataj();
		file_name_kompletorium(OBD_CEZ_ROK);
		if (_je_global_den_slavnost && ((den != DEN_NEDELA) && (den != DEN_SOBOTA))) {
			den = DEN_UNKNOWN; // slávnosť mimo nedieľ
		}
		if ((modlitba == MODL_KOMPLETORIUM) && (ktore == 1)) {
			// ToDo: škaredý drát, ak požaduje explicitne kompletórium po prvých vešperách pre oktávu
			pismenko_modlitby_pom = pismenko_modlitby(MODL_PRVE_KOMPLETORIUM);
		}
		sprintf(_anchor, "_%s%c_%s", nazov_DN_asci[den], pismenko_modlitby_pom, ANCHOR_KCITANIE);
		_set_kcitanie(modlitba, _file, _anchor);
		set_LOG_zaltar;
		file_name_obnov();
	}
	else {
		file_name_zaltar(den, tyzzal);
		anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_KCITANIE);
		_set_kcitanie(modlitba, _file, _anchor);
		set_LOG_zaltar;
	}
	// Log("set_kcitanie() -- koniec.\n");
} // set_kcitanie()

// odlišné pre pôst a veľkonočné obdobie: Vo Veľkonočnej oktáve namiesto responzória sa hovorí antifóna: Toto je deň. Vo Veľkonočnom období: R. Do tvojich rúk, Pane, porúčam svojho ducha, * Aleluja, aleluja. Do tvojich. atď.
void set_kresponz_kompletorium_obd(short int den, short int modlitba, short int litobd) {
	// rovnaké responzórium pre všetky časti veľkonočného obdobia
	file_name_zapamataj();
	// vo veľkonočnej oktáve je také isté krátke resp. ako vo veľkonočnú nedeľu; zmena v nastavení filename
	if (litobd == OBD_VELKONOCNA_OKTAVA) {
		file_name_kompletorium(OBD_VELKONOCNE_TROJDNIE);
	}
	else if ((litobd == OBD_VELKONOCNE_I) || (litobd == OBD_VELKONOCNE_II) || (litobd == OBD_VELKONOCNE_TROJDNIE) || ((litobd == OBD_POSTNE_II_VELKY_TYZDEN) && (den == DEN_STVRTOK))) {
		file_name_kompletorium((litobd == OBD_VELKONOCNE_II) ? OBD_VELKONOCNE_I : litobd);
	}
	else {
		file_name_kompletorium(OBD_CEZ_ROK);
	}
	// vo veľkonočnej oktáve je také isté krátke resp. ako vo veľkonočnú nedeľu; zmena v nastavení anchor
	if ((litobd == OBD_VELKONOCNA_OKTAVA) || (litobd == OBD_VELKONOCNE_TROJDNIE)) {
		sprintf(_anchor, "_%s%c_%s", nazov_DN_asci[(litobd == OBD_VELKONOCNA_OKTAVA) ? DEN_NEDELA : den], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);
	}
	else {
		sprintf(_anchor, "_%c_%s", pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);
	}
	_set_kresponz(modlitba, _file, _anchor);
	set_LOG_zaltar;
	file_name_obnov();
} // set_kresponz_kompletorium_obd()

void set_kresponz(short int den, short int tyzzal, short int modlitba) {
	if (je_kompletorium12(modlitba)) {
		set_kresponz_kompletorium_obd(den, modlitba, _global_den.litobd);
	}
	else {
		if (modlitba == MODL_POSV_CITANIE) {
			file_name_litobd_pc(OBD_CEZ_ROK);
			anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_KRESPONZ);
			_set_kresponz(modlitba, _file_pc, _anchor);
			set_LOG_litobd_pc;
		}
		else {
			if ((modlitba != MODL_PREDPOLUDNIM) && (modlitba != MODL_NAPOLUDNIE) && (modlitba != MODL_POPOLUDNI)) {
				// pre modlitbu cez den to neplati: prvy a treti, resp. druhy a stvrty tyzden maju rovnake
				tyzzal = set_tyzzal_1_2(tyzzal);
			}
			file_name_zaltar(den, tyzzal);
			anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_KRESPONZ);
			_set_kresponz(modlitba, _file, _anchor);
			set_LOG_zaltar;
		}
	}
} // set_kresponz()

void set_prosby(short int den, short int tyzzal, short int modlitba) {
	file_name_zaltar(den, tyzzal);
	anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_PROSBY);
	_set_prosby(modlitba, _file, _anchor);
	set_LOG_zaltar;
} // set_prosby()

void _set_prosby_dodatok(short int den, short int force_prve_vespery /* default = NIE */) {
	Log("_set_prosby_dodatok(den == %d, %s%s) -- begin\n", den, nazov_dna(den), (force_prve_vespery == ANO) ? " force" : "");

	char file[SMALL];
	char anchor[SMALL];
	short int modlitba;

	mystrcpy(file, FILE_DODATOK_PROSBY, MAX_STR_AF_FILE);
	modlitba = MODL_VESPERY;

	sprintf(anchor, "%s%c_%s", nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_PROSBY);
	_set_prosby(modlitba, file, anchor);
	Log("_set_prosby_dodatok(): %s: súbor `%s', kotva `%s'\n", nazov_modlitby(modlitba), file, anchor);

	if ((den == DEN_NEDELA) || (force_prve_vespery == ANO)) {
		den = (den == DEN_NEDELA) ? DEN_SOBOTA : den - 1;
		sprintf(anchor, "%s%c_%s", nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_PROSBY);
		_set_prosby(MODL_PRVE_VESPERY, file, anchor);
		Log("_set_prosby_dodatok(): %s: súbor `%s', kotva `%s'\n", nazov_modlitby(modlitba), file, anchor);
	}

	Log("_set_prosby_dodatok() -- end\n");
} // _set_prosby_dodatok()

void set_modlitba(short int den, short int tyzzal, short int modlitba, short int ktore /* default ktore = 2 */) {
	char pismenko_modlitby_pom = pismenko_modlitby(modlitba);
	Log("set_modlitba() -- začiatok...\n");
	Log("den == %d, tyzzal == %d, modlitba == %d, ktore == %d...\n", den, tyzzal, modlitba, ktore);

	if (je_kompletorium12(modlitba)) {
		file_name_zapamataj();
		file_name_kompletorium(OBD_CEZ_ROK);
		if (_je_global_den_slavnost && ((den != DEN_NEDELA) && (den != DEN_SOBOTA))) {
			den = DEN_UNKNOWN; // slávnosť mimo nedieľ
		}
		if ((modlitba == MODL_KOMPLETORIUM) && (ktore == 1)) {
			// 2011-04-28: škaredý drát, ak požaduje explicitne kompletórium po prvých vešperách pre oktávu
			pismenko_modlitby_pom = pismenko_modlitby(MODL_PRVE_KOMPLETORIUM);
		}
		sprintf(_anchor, "_%s%c_%s", nazov_DN_asci[den], pismenko_modlitby_pom, ANCHOR_MODLITBA);
		_set_modlitba(modlitba, _file, _anchor);
		set_LOG_zaltar;
		file_name_obnov();
	}
	else {
		if (je_modlitba_cez_den(modlitba)) {
			// pre modlitbu cez deň: prvý a tretí, resp. druhý a štvrtý týždeň majú rovnaké
			tyzzal = set_tyzzal_1_2(tyzzal);
		}
		file_name_zaltar(den, tyzzal);
		anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_MODLITBA);
		_set_modlitba(modlitba, _file, _anchor);
		set_LOG_zaltar;
	}
	// Log("set_modlitba() -- koniec.\n");
} // set_modlitba()

void set_benediktus(short int den, short int tyzzal, short int modlitba) {
	// prvý a tretí, resp. druhý a štvrtý týždeň majú rovnaké
	tyzzal = set_tyzzal_1_2(tyzzal);
	file_name_zaltar(den, tyzzal);
	anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_BENEDIKTUS);
	_set_benediktus(modlitba, _file, _anchor);
	set_LOG_zaltar;
} // set_benediktus();

void set_magnifikat(short int den, short int tyzzal, short int modlitba) {
	// prvý a tretí, resp. druhý a štvrtý týždeň majú rovnaké
	tyzzal = set_tyzzal_1_2(tyzzal);
	file_name_zaltar(den, tyzzal);
	anchor_name_zaltar(den, tyzzal, modlitba, ANCHOR_MAGNIFIKAT);
	_set_magnifikat(modlitba, _file, _anchor);
	set_LOG_zaltar;
} // set_magnifikat();

void set_nunc_dimittis(short int modlitba) {
	file_name_zapamataj();
	file_name_kompletorium(OBD_CEZ_ROK);
	sprintf(_anchor, "_%c_%s", pismenko_modlitby(modlitba), ANCHOR_NUNC_DIMITTIS);
	_set_nunc_dimittis(modlitba, _file, _anchor);
	set_LOG_zaltar;
	file_name_obnov();
} // set_nunc_dimittis();

void set_ukonkaj(short int modlitba) {
	file_name_zapamataj();
	file_name_kompletorium(OBD_CEZ_ROK);
	sprintf(_anchor, "_%c_%s", pismenko_modlitby(modlitba), ANCHOR_UKON_KAJ);
	_set_ukonkaj(modlitba, _file, _anchor);
	set_LOG_zaltar;
	file_name_obnov();
} // set_ukonkaj();

void set_maria_ant(short int modlitba) {
	file_name_zapamataj();
	sprintf(_file, "%s", FILE_MARIANSKE_ANTIFONY);
	sprintf(_anchor, "_%c_%s%s", pismenko_modlitby(MODL_KOMPLETORIUM), ANCHOR_MARIANSKE_ANTIFONY, (je_velka_noc) ? VELKONOCNA_PRIPONA : STR_EMPTY);
	_set_maria_ant(modlitba, _file, _anchor);
	set_LOG_zaltar;
	file_name_obnov();
} // set_maria_ant();

void set_otcenas_uvod(short int modlitba) {
	Log("set_otcenas_uvod(): začiatok...\n");
	if ((modlitba == MODL_RANNE_CHVALY) || (modlitba == MODL_PRVE_VESPERY) || (modlitba == MODL_DRUHE_VESPERY) || (modlitba == MODL_VESPERY)) {
		file_name_zapamataj();
		sprintf(_file, "%s", FILE_OTCENAS_UVOD);
		sprintf(_anchor, "_%s", ANCHOR_OTCENAS_UVOD);
		_set_otcenas_uvod(modlitba, _file, _anchor);
		set_LOG_zaltar;
		file_name_obnov();
	}
	else {
		Log("set_otcenas_uvod(): skipped...\n");
	}
	Log("set_otcenas_uvod(): koniec.\n");
} // set_otcenas_uvod();

void set_popis(short int modlitba, char *file, char *anchor) {
	_set_popis(modlitba, file, anchor);
	Log("   set(popis): %s: súbor `%s', kotva `%s'\n", nazov_modlitby(modlitba), file, anchor);
} // set_popis();

void set_popis_dummy(void) {
	Log("  teraz nastavujem POPIS (dummy)...\n");
	char _file[MAX_STR_AF_FILE];
	char _anchor[MAX_STR_AF_ANCHOR];
	mystrcpy(_file, STR_UNDEF, MAX_STR_AF_FILE);
	mystrcpy(_anchor, STR_UNDEF, MAX_STR_AF_ANCHOR);
	set_popis(MODL_RANNE_CHVALY, _file, _anchor);
	set_popis(MODL_POSV_CITANIE, _file, _anchor);
	set_popis(MODL_VESPERY, _file, _anchor);
	set_popis(MODL_PRVE_VESPERY, _file, _anchor);
	set_popis(MODL_PREDPOLUDNIM, _file, _anchor);
	set_popis(MODL_NAPOLUDNIE, _file, _anchor);
	set_popis(MODL_POPOLUDNI, _file, _anchor);
	set_popis(MODL_INVITATORIUM, _file, _anchor);
	set_popis(MODL_KOMPLETORIUM, _file, _anchor);
	set_popis(MODL_PRVE_KOMPLETORIUM, _file, _anchor);
} // set_popis_dummy();

void set_popis_dummy_except_vespers(void) {
	Log("  teraz nastavujem POPIS (dummy) okrem vešpier...\n");
	char _file[MAX_STR_AF_FILE];
	char _anchor[MAX_STR_AF_ANCHOR];
	mystrcpy(_file, STR_UNDEF, MAX_STR_AF_FILE);
	mystrcpy(_anchor, STR_UNDEF, MAX_STR_AF_ANCHOR);
	set_popis(MODL_RANNE_CHVALY, _file, _anchor);
	set_popis(MODL_POSV_CITANIE, _file, _anchor);
	// set_popis(MODL_VESPERY, _file, _anchor);
	// set_popis(MODL_PRVE_VESPERY, _file, _anchor);
	set_popis(MODL_PREDPOLUDNIM, _file, _anchor);
	set_popis(MODL_NAPOLUDNIE, _file, _anchor);
	set_popis(MODL_POPOLUDNI, _file, _anchor);
	set_popis(MODL_INVITATORIUM, _file, _anchor);
	set_popis(MODL_KOMPLETORIUM, _file, _anchor);
	set_popis(MODL_PRVE_KOMPLETORIUM, _file, _anchor);
} // set_popis_dummy_except_vespers();

void _set_zalmy_mcd_doplnkova_psalmodia_alternativy(short int modlitba) {
	Log("_set_zalmy_mcd_doplnkova_psalmodia_alternativy %s: ...\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_PREDPOLUDNIM) {
		// nastaviť: ak je možnosť v doplnkovej psalmódii nahradiť žalm 122 žalmom 129
		Log("je_alternativa_doplnkova_psalmodia_z122_129 == %d...\n", je_alternativa_doplnkova_psalmodia_z122_129(modlitba));
		Log("(_global_opt[OPT_5_ALTERNATIVES] & BIT_OPT_5_DOPLNK_PSALM_122_129) == %ld (BIT_OPT_5_DOPLNK_PSALM_122_129 == %ld)...\n", (_global_opt[OPT_5_ALTERNATIVES] & BIT_OPT_5_DOPLNK_PSALM_122_129), BIT_OPT_5_DOPLNK_PSALM_122_129);
		if ((je_alternativa_doplnkova_psalmodia_z122_129(modlitba)) && (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_DOPLNK_PSALM_122_129))) {
			Log("nastavujem namiesto žalmu 122 žalm 129...\n");
			set_zalm(3, modlitba, "z129.htm", "ZALM129");
		}
	}
	else if (modlitba == MODL_NAPOLUDNIE) {
		;
	}
	else if (modlitba == MODL_POPOLUDNI) {
		// nastaviť: ak je možnosť v doplnkovej psalmódii nahradiť žalm 126 žalmom 129
		Log("je_alternativa_doplnkova_psalmodia_z126_129 == %d...\n", je_alternativa_doplnkova_psalmodia_z126_129(modlitba));
		Log("(_global_opt[OPT_5_ALTERNATIVES] & BIT_OPT_5_DOPLNK_PSALM_126_129) == %ld (BIT_OPT_5_DOPLNK_PSALM_126_129 == %ld)...\n", (_global_opt[OPT_5_ALTERNATIVES] & BIT_OPT_5_DOPLNK_PSALM_126_129), BIT_OPT_5_DOPLNK_PSALM_126_129);
		if ((je_alternativa_doplnkova_psalmodia_z126_129(modlitba)) && (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_DOPLNK_PSALM_126_129))) {
			Log("nastavujem namiesto žalmu 126 žalm 129...\n");
			set_zalm(1, modlitba, "z129.htm", "ZALM129");
		}
		// nastaviť: ak je možnosť v doplnkovej psalmódii nahradiť žalm 127 žalmom 131
		Log("je_alternativa_doplnkova_psalmodia_z127_131 == %d...\n", je_alternativa_doplnkova_psalmodia_z127_131(modlitba));
		Log("(_global_opt[OPT_5_ALTERNATIVES] & BIT_OPT_5_DOPLNK_PSALM_127_131) == %ld (BIT_OPT_5_DOPLNK_PSALM_127_131 == %ld)...\n", (_global_opt[OPT_5_ALTERNATIVES] & BIT_OPT_5_DOPLNK_PSALM_127_131), BIT_OPT_5_DOPLNK_PSALM_127_131);
		if ((je_alternativa_doplnkova_psalmodia_z127_131(modlitba)) && (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_DOPLNK_PSALM_127_131))) {
			Log("nastavujem namiesto žalmu 127 žalm 131...\n");
			set_zalm(2, modlitba, "z131.htm", "ZALM131");
		}
	}
} // _set_zalmy_mcd_doplnkova_psalmodia_alternativy()

void _set_zalmy_mcd_doplnkova_psalmodia(short int je_predpisana_povinne /* = ANO */) {
	// default vstupný parameter, ktorý hovorí, či je doplnková psalmódia predpísaná pre dané slávenie (napr. pre slávnosť), alebo nie (teda NIE == bola zvolená ako alternatíva k psalmódii z bežného dňa)
	Log("_set_zalmy_mcd_doplnkova_psalmodia(je_predpisana_povinne == %d) -- begin\n", je_predpisana_povinne);
	short int modlitba;
	modlitba = MODL_PREDPOLUDNIM;
	// ak sa berie len doplnková psalmódia (t. j. ak je predpísaná), nemá zmysel dať možnosť vziať žalmy z doplnkovej psalmódie
	if (je_predpisana_povinne == ANO) {
		_set_mcd_len_doplnkova_psalmodia(modlitba);
	}
	// modlitba predpoludnim, 1. séria doplnkovej psalmódie
	set_zalm(1, modlitba, "z120.htm", "ZALM120");
	set_zalm(2, modlitba, "z121.htm", "ZALM121");
	set_zalm(3, modlitba, "z122.htm", "ZALM122");
	_set_zalmy_mcd_doplnkova_psalmodia_alternativy(modlitba);

	modlitba = MODL_NAPOLUDNIE;
	// ak sa berie len doplnková psalmódia (t. j. ak je predpísaná), nemá zmysel dať možnosť vziať žalmy z doplnkovej psalmódie
	if (je_predpisana_povinne == ANO) {
		_set_mcd_len_doplnkova_psalmodia(modlitba);
	}
	// modlitba napoludnie, 2. séria doplnkovej psalmódie
	set_zalm(1, modlitba, "z123.htm", "ZALM123");
	set_zalm(2, modlitba, "z124.htm", "ZALM124");
	set_zalm(3, modlitba, "z125.htm", "ZALM125");

	modlitba = MODL_POPOLUDNI;
	// ak sa berie len doplnková psalmódia (t. j. ak je predpísaná), nemá zmysel dať možnosť vziať žalmy z doplnkovej psalmódie
	if (je_predpisana_povinne == ANO) {
		_set_mcd_len_doplnkova_psalmodia(modlitba);
	}
	// modlitba popoludni, 3. séria doplnkovej psalmódie
	set_zalm(1, modlitba, "z126.htm", "ZALM126");
	set_zalm(2, modlitba, "z127.htm", "ZALM127");
	set_zalm(3, modlitba, "z128.htm", "ZALM128");
	_set_zalmy_mcd_doplnkova_psalmodia_alternativy(modlitba);

	Log("_set_zalmy_mcd_doplnkova_psalmodia() -- end\n");
	// antifóny nastavuje funkcia _set_antifony_mcd_doplnkova_psalmodia() -- ale len pre cezročné obdobie; pre vlastné sa používa define _vlastna_cast_mcd_ant_kcitresp_modl;
} // _set_zalmy_mcd_doplnkova_psalmodia()

void _set_antifony_mcd_doplnkova_psalmodia(void) {
	Log("_set_antifony_mcd_doplnkova_psalmodia() -- begin\n");
	char file[SMALL]; // nazov súboru, napr. _1ne.htm
	char anchor[SMALL];
	short int modlitba;
	mystrcpy(file, FILE_DOPLNKOVA_PSALMODIA, MAX_STR_AF_FILE);
	for (modlitba = MODL_PREDPOLUDNIM; modlitba <= MODL_POPOLUDNI; modlitba++) {
		// modlitba predpoludnim -- napoludnie -- popoludní, 1. až 3. séria doplnkovej psalmódie
		sprintf(anchor, "%s%c_%s", ANCHOR_DOPLNKOVA_PSALMODIA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);
		_set_antifona1(modlitba, file, anchor);
		set_LOG_zaltar;
		sprintf(anchor, "%s%c_%s", ANCHOR_DOPLNKOVA_PSALMODIA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);
		_set_antifona2(modlitba, file, anchor);
		set_LOG_zaltar;
		sprintf(anchor, "%s%c_%s", ANCHOR_DOPLNKOVA_PSALMODIA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);
		_set_antifona3(modlitba, file, anchor);
		set_LOG_zaltar;
	}// for
	Log("_set_antifony_mcd_doplnkova_psalmodia() -- end\n");
} // _set_antifony_mcd_doplnkova_psalmodia()

// žalmy nedele 1. týždňa kvôli modlitbe cez deň
void _set_zalmy_1nedele_mcd(void) {// modlitba cez deň; rovnaké žalmy sú pre nedeľu 3. týždňa; 2007-01-11
	Log("_set_zalmy_1nedele_mcd() -- begin\n");
	// modlitba cez deň
	set_zalm(1, MODL_CEZ_DEN_VSETKY, "z118.htm", "ZALM118_I");
	set_zalm(2, MODL_CEZ_DEN_VSETKY, "z118.htm", "ZALM118_II");
	set_zalm(3, MODL_CEZ_DEN_VSETKY, "z118.htm", "ZALM118_III");
	Log("_set_zalmy_1nedele_mcd() -- end\n");
} // _set_zalmy_1nedele_mcd()

// žalmy nedele 2. týždňa kvôli modlitbe cez deň
void _set_zalmy_2nedele_mcd(void) {// modlitba cez deň; rovnaké žalmy sú pre nedeľu 4. týždňa; 2007-01-11
	Log("_set_zalmy_2nedele_mcd() -- begin\n");
	// modlitba cez deň
	set_zalm(1, MODL_CEZ_DEN_VSETKY, "z23.htm", "ZALM23");
	set_zalm(2, MODL_CEZ_DEN_VSETKY, "z76.htm", "ZALM76_I");
	set_zalm(3, MODL_CEZ_DEN_VSETKY, "z76.htm", "ZALM76_II");
	Log("_set_zalmy_2nedele_mcd() -- end\n");
} // _set_zalmy_2nedele_mcd()

void _set_zalmy_mcd_1nedela_or_doplnkova_psalmodia(void) {
	// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
	if (_global_den.denvt != DEN_NEDELA) {
		if (_je_global_den_slavnost) {
			_set_zalmy_mcd_doplnkova_psalmodia();
		}
		// pre sviatok sa použije bežná psalmódia t férie
	}
	else if (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA)) {
		_set_zalmy_1nedele_mcd();
	}
}// _set_zalmy_mcd_1nedela_or_doplnkova_psalmodia() -- ak sviatok/slávnosť padne na nedeľu, berú sa žalmy z nedele 1. týždňa (s možnosťou prepnúť na doplnkovú psalmódiu), v opačnom prípade (pre slávenie mimo nedele) je predpísaná doplnková psalmódia

void _set_kompletorium_nedela_spolocne(short int modlitba) {
	Log("_set_kompletorium_nedela_spolocne(%d - %s) -- begin\n", modlitba, nazov_modlitby(modlitba));
	if (modlitba == MODL_PRVE_KOMPLETORIUM) {
		_global_modl_prve_kompletorium.pocet_zalmov = 2;
		set_zalm(1, modlitba, "z4.htm", "ZALM4");
		set_zalm(2, modlitba, "z134.htm", "ZALM134");
	}
	else {
		// modlitba == MODL_KOMPLETORIUM
		_global_modl_kompletorium.pocet_zalmov = 1;
		set_zalm(1, modlitba, "z91.htm", "ZALM91");
	}
	// hymnus pre CZ: pre prvé kompletórium bude kotva 'p_HYMNUS_NE' = 'k_HYMNUS_SO', pre druhé kompletórium kotva 'k_HYMNUS_NE'
	set_hymnus(DEN_NEDELA, _global_den.tyzzal, modlitba); // set_hymnus() v skutočnosti volá pre kompletórium funkciu set_hymnus_kompletorium_obd()
	set_antifony(DEN_NEDELA, _global_den.tyzzal, 2 /* zvazok - pre kompletórium sa nepoužíva, len kvôli posv. čítaniu */, modlitba);
	set_nunc_dimittis(modlitba); // 2013-06-28: doplnené podľa zaltar_kompletorium()
	set_ukonkaj(modlitba);
	set_maria_ant(modlitba);
	Log("_set_kompletorium_nedela_spolocne(%d) -- end\n", modlitba);
} // _set_kompletorium_nedela_spolocne()

// nedeľné kompletórium (používa sa aj pre špeciálne dni, napr. zelený štvrtok)
void _set_kompletorium_nedela(short int modlitba) {
	Log("_set_kompletorium_nedela(%d - %s) -- begin\n", modlitba, nazov_modlitby(modlitba));
	_set_kompletorium_nedela_spolocne(modlitba);
	set_kcitanie(DEN_NEDELA, _global_den.tyzzal, modlitba);
	set_kresponz(DEN_NEDELA, _global_den.tyzzal, modlitba);
	set_modlitba(DEN_NEDELA, _global_den.tyzzal, modlitba);
	Log("_set_kompletorium_nedela(%d) -- end\n", modlitba);
} // _set_kompletorium_nedela()

// ak je slávnosť, berie sa iná modlitba ako na nedeľné kompletórium
void _set_kompletorium_slavnost(short int modlitba) {
	Log("_set_kompletorium_slavnost(%d - %s) -- begin\n", modlitba, nazov_modlitby(modlitba));

	// ak padne slávnosť resp. sviatok Pána na sobotu, vtedy je tiež nedeľné kompletórium (po druhých vešperách) -- ??? neplatí pre Všetkých svätých, 2014
	if (_global_den.denvt == DEN_NEDELA) {
		Log("=> ak slávnosť padne na nedeľu, berie sa nedeľné kompletórium\n");
		_set_kompletorium_nedela(modlitba);
	}
	else {
		_set_kompletorium_nedela_spolocne(modlitba);
		set_modlitba(DEN_UNKNOWN, _global_den.tyzzal, modlitba); // je to jeden konkrétny deň mimo nedele
		// nasledujúce závisia od liturgického obdobia, preto nastavíme inú kotvu (pevne z nedele)
		set_kcitanie(DEN_NEDELA, _global_den.tyzzal, modlitba);
		set_kresponz(DEN_NEDELA, _global_den.tyzzal, modlitba);
	}
	Log("_set_kompletorium_slavnost(%d) -- end\n", modlitba);
} // _set_kompletorium_slavnost()

// vo veľkonočnej a vianočnej oktáve sa pre bežné dni berie 1. alebo 2. nedeľné kompletórium
void _set_kompletorium_slavnost_oktava(short int modlitba, short int litobd, short int ktore) {
	//	"ktore" určuje, či ide o kompletórium po prvých vešperách slávnosti (1) alebo po druhých vešperách (2); vstupom je parameter "modlitba"
	Log("_set_kompletorium_slavnost_oktava(%d - %s), %d -- begin\n", modlitba, nazov_modlitby(modlitba), ktore);
	if (_global_den.denvt == DEN_NEDELA) {
		// 2008-12-20: ak slávnosť padne na nedeľu, berie sa nedeľné kompletórium
		Log("=> ak slávnosť padne na nedeľu, berie sa nedeľné kompletórium\n");
		_set_kompletorium_nedela(modlitba);
	}
	else if (ktore == 2) { // normálne nedeľné kompletórium po 2. vešperách
		_set_kompletorium_slavnost(modlitba);
		// modlitba pre veľkonočnú oktávu aj pre vianočnú oktávu
		if (litobd == OBD_VELKONOCNA_OKTAVA) {
			set_modlitba(DEN_NEDELA, _global_den.tyzzal, modlitba); // vo veľkonočnej oktáve sa berie modlitba z nedele
		}
	}
	else { // ktore = 1
		// nastavujeme ako pre nedeľné kompletórium po prvých vešperách, porov. _set_kompletorium_nedela_spolocne()
		_global_modl_kompletorium.pocet_zalmov = 2;
		set_zalm(1, modlitba, "z4.htm", "ZALM4");
		set_zalm(2, modlitba, "z134.htm", "ZALM134");
		// keďže funkcia sa používa napevno s modlitba == MODL_KOMPLETORIUM, pre prvé kompletórium je kvôli CZ hymnom potrebné nastaviť deň na sobotu / alebo modlitbu na prvé kompletórium | upozornil Václav Slouk <slouk@biskupstvi.cz>
		// hymnus pre CZ: pre prvé kompletórium bude kotva 'p_HYMNUS_NE' = 'k_HYMNUS_SO', pre druhé kompletórium kotva 'k_HYMNUS_NE'
		set_hymnus(DEN_SOBOTA, _global_den.tyzzal, modlitba); // set_hymnus() v skutočnosti volá pre kompletórium funkciu set_hymnus_kompletorium_obd()
		set_antifony(DEN_NEDELA, _global_den.tyzzal, 9 /* zvazok - pre kompletórium sa nepoužívalo, využité na špeciálne nastavenie */, modlitba);
		// modlitba pre veľkonočnú oktávu aj pre vianočnú oktávu
		if (litobd == OBD_VELKONOCNA_OKTAVA) {
			set_modlitba(DEN_NEDELA, _global_den.tyzzal, modlitba, ktore /* == 1 */); // vo veľkonočnej oktáve sa berie modlitba z nedele
		}
		else {
			set_modlitba(DEN_UNKNOWN, _global_den.tyzzal, modlitba); // je to jeden konkrétny deň mimo nedele
		}
		// nasledujúce závisia od liturgického obdobia, preto nastavíme inú kotvu (pevne z nedele)
		set_kcitanie(DEN_NEDELA, _global_den.tyzzal, modlitba, ktore /* == 1 */);
		set_kresponz(DEN_NEDELA, _global_den.tyzzal, modlitba);
	}
	Log("_set_kompletorium_slavnost_oktava(%d) -- end\n", modlitba);
} // _set_kompletorium_slavnost_oktava()

void zaltar_kompletorium_okrem_zalmov(short int den, short int obdobie, short int specialne, short int tyzzal, short int modlitba) {
	Log("-- zaltar_kompletorium_okrem_zalmov(%d, %d, %d, %d, %d) -- začiatok\n", den, obdobie, specialne, tyzzal, modlitba);

	short int den_pom = den;
	short int ktore = 2;
	if (den == DEN_SOBOTA) {
		den_pom = DEN_NEDELA;
		ktore = 1; /* (den == DEN_SOBOTA)? 1: 2 */
	}

	set_hymnus(den, tyzzal, modlitba); // set_hymnus() v skutočnosti volá pre kompletórium funkciu set_hymnus_kompletorium_obd()
	set_antifony(den, 1 /* tyzzal */, 1 /* zvazok */, modlitba);
	set_kcitanie(den_pom, 1 /* tyzzal */, modlitba, ktore);
	set_kresponz(den, 1 /* tyzzal */, modlitba);
	set_nunc_dimittis(modlitba);
	set_ukonkaj(modlitba);
	set_maria_ant(modlitba);
	set_modlitba(den_pom, 1 /* tyzzal */, modlitba, ktore);

	Log("-- zaltar_kompletorium_okrem_zalmov(%d, %d, %d, %d, %d) -- koniec\n", den, obdobie, specialne, tyzzal, modlitba);
} // zaltar_kompletorium_okrem_zalmov()

void zaltar_kompletorium(short int den, short int obdobie, short int specialne, short int tyzzal) {
	Log("-- zaltar_kompletorium(%d, %d, %d, %d) -- začiatok\n", den, obdobie, specialne, tyzzal);

	if (den == DEN_SOBOTA) {
		Log("keďže je sobota, budeme nastavovať kompletórium po prvých nedeľných vešperách...\n");
	}

	Log("nastavujem počet žalmov pre kompletórium v závislosti od dňa v týždni (%d - %s)...\n", den, nazov_dna(den));
	// Doplnené kvôli rôznemu počtu žalmov pre kompletórium
	if (den == DEN_STREDA) {
		_global_modl_kompletorium.pocet_zalmov = 2;
	}
	else if (den == DEN_NEDELA) {
		_global_modl_prve_kompletorium.pocet_zalmov = 2;
		_global_modl_kompletorium.pocet_zalmov = 1;
	}
	else if (den == DEN_SOBOTA) {
		_global_modl_kompletorium.pocet_zalmov = 2;
	}
	else {
		_global_modl_kompletorium.pocet_zalmov = 1;
	}
	Log("_global_modl_kompletorium.pocet_zalmov == %d; _global_modl_prve_kompletorium.pocet_zalmov == %d...\n", _global_modl_kompletorium.pocet_zalmov, _global_modl_prve_kompletorium.pocet_zalmov);

	if (specialne == ZALTAR_VSETKO) {
		Log("ZALTAR_VSETKO -- takže nastavujem všetko zo žaltára... (zaltar_kompletorium)\n");
		if (den == DEN_NEDELA) {
			zaltar_kompletorium_okrem_zalmov(den, obdobie, specialne, tyzzal, MODL_PRVE_KOMPLETORIUM);
		}
		zaltar_kompletorium_okrem_zalmov(den, obdobie, specialne, tyzzal, MODL_KOMPLETORIUM);
	}
	else {
		Log("nebolo ZALTAR_VSETKO ani ZALTAR_IBA_ZALMY_HYMNUS_MCD -- takže nastavujem len žalmy...\n");
	}

	switch (den) {
	case DEN_NEDELA:
		set_zalm(1, MODL_PRVE_KOMPLETORIUM, "z4.htm", "ZALM4");
		set_zalm(2, MODL_PRVE_KOMPLETORIUM, "z134.htm", "ZALM134");
		set_zalm(1, MODL_KOMPLETORIUM, "z91.htm", "ZALM91");
		break;
	case DEN_PONDELOK:
		set_zalm(1, MODL_KOMPLETORIUM, "z86.htm", "ZALM86");
		break;
	case DEN_UTOROK:
		set_zalm(1, MODL_KOMPLETORIUM, "z143.htm", "ZALM143");
		break;
	case DEN_STREDA:
		set_zalm(1, MODL_KOMPLETORIUM, "z31.htm", "ZALM31,1-6");
		set_zalm(2, MODL_KOMPLETORIUM, "z130.htm", "ZALM130");
		break;
	case DEN_STVRTOK:
		set_zalm(1, MODL_KOMPLETORIUM, "z16.htm", "ZALM16");
		break;
	case DEN_PIATOK:
		set_zalm(1, MODL_KOMPLETORIUM, "z88.htm", "ZALM88");
		break;
	case DEN_SOBOTA:
		set_zalm(1, MODL_KOMPLETORIUM, "z4.htm", "ZALM4");
		set_zalm(2, MODL_KOMPLETORIUM, "z134.htm", "ZALM134");
		break;
	} // switch(den)
	Log("-- zaltar_kompletorium(%d, %d, %d, %d) -- koniec\n", den, obdobie, specialne, tyzzal);
} // zaltar_kompletorium()

void _set_zalmy_pc_145(short int modlitba) {
	Log("_set_zalmy_pc_145(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z145.htm", "ZALM145pc_I");
		set_zalm(2, modlitba, "z145.htm", "ZALM145pc_II");
		set_zalm(3, modlitba, "z145.htm", "ZALM145pc_III");
	}
	Log("_set_zalmy_pc_145(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_pc_145()

void _set_zalmy_mcd_zaltar(short int den, short int tyzzal, short int modlitba) {
	Log("_set_zalmy_mcd_zaltar(%d [%s], %d. týždeň žaltára, %d [%s]) -- begin\n", den, nazov_dna(den), tyzzal, modlitba, (modlitba == MODL_CEZ_DEN_VSETKY) ? "MCD-all" : ((modlitba <= POCET_MODLITIEB) ? nazov_modlitby(modlitba) : STR_EMPTY));

	Log("nastavujem žalmy pre MCD (pre jednotlivý týždeň žaltára a konkrétnu modlitbu (hodinku) z modlitby cez deň)...\n");
	switch (tyzzal) {
	case 1: // 1. týždeň žaltára -- začiatok
		switch (den) {
		case DEN_NEDELA: // 1
			_set_zalmy_1nedele_mcd();
			break;
		case DEN_PONDELOK: // 1
			set_zalm(1, modlitba, "z19.htm", "ZALM19,8-15");
			set_zalm(2, modlitba, "z7.htm", "ZALM7_I");
			set_zalm(3, modlitba, "z7.htm", "ZALM7_II");
			break;
		case DEN_UTOROK: // 1
			set_zalm(1, modlitba, "z119.htm", "ZALM119_ALEF");
			set_zalm(2, modlitba, "z13.htm", "ZALM13");
			set_zalm(3, modlitba, "z14.htm", "ZALM14");
			break;
		case DEN_STREDA: // 1
			set_zalm(1, modlitba, "z119.htm", "ZALM119_BET");
			set_zalm(2, modlitba, "z17.htm", "ZALM17_I");
			set_zalm(3, modlitba, "z17.htm", "ZALM17_II");
			break;
		case DEN_STVRTOK: // 1
			set_zalm(1, modlitba, "z119.htm", "ZALM119_GIMEL");
			set_zalm(2, modlitba, "z25.htm", "ZALM25_I");
			set_zalm(3, modlitba, "z25.htm", "ZALM25_II");
			break;
		case DEN_PIATOK: // 1
			set_zalm(1, modlitba, "z119.htm", "ZALM119_DALET");
			set_zalm(2, modlitba, "z26.htm", "ZALM26");
			set_zalm(3, modlitba, "z28.htm", "ZALM28,1-3.6-9");
			break;
		case DEN_SOBOTA: // 1
			set_zalm(1, modlitba, "z119.htm", "ZALM119_HE");
			set_zalm(2, modlitba, "z34.htm", "ZALM34_I");
			set_zalm(3, modlitba, "z34.htm", "ZALM34_II");
			break;
		}// 1. týždeň žaltára -- koniec
		break;
	case 2: // 2. týždeň žaltára -- začiatok
		switch (den) {
		case DEN_NEDELA: // 2
			_set_zalmy_2nedele_mcd();
			break;
		case DEN_PONDELOK: // 2
			set_zalm(1, modlitba, "z119.htm", "ZALM119_VAU");
			set_zalm(2, modlitba, "z40.htm", "ZALM40_I");
			set_zalm(3, modlitba, "z40.htm", "ZALM40_II");
			break;
		case DEN_UTOROK: // 2
			set_zalm(1, modlitba, "z119.htm", "ZALM119_ZAJIN");
			set_zalm(2, modlitba, "z53.htm", "ZALM53");
			set_zalm(3, modlitba, "z54.htm", "ZALM54");
			break;
		case DEN_STREDA: // 2
			set_zalm(1, modlitba, "z119.htm", "ZALM119_CHET");
			set_zalm(2, modlitba, "z55.htm", "ZALM55_I");
			set_zalm(3, modlitba, "z55.htm", "ZALM55_II");
			break;
		case DEN_STVRTOK: // 2
			set_zalm(1, modlitba, "z119.htm", "ZALM119_TET");
			set_zalm(2, modlitba, "z56.htm", "ZALM56");
			set_zalm(3, modlitba, "z57.htm", "ZALM57");
			break;
		case DEN_PIATOK: // 2
			set_zalm(1, modlitba, "z119.htm", "ZALM119_JOD");
			set_zalm(2, modlitba, "z59.htm", "ZALM59");
			set_zalm(3, modlitba, "z60.htm", "ZALM60");
			break;
		case DEN_SOBOTA: // 2
			set_zalm(1, modlitba, "z119.htm", "ZALM119_KAF");
			set_zalm(2, modlitba, "z61.htm", "ZALM61");
			set_zalm(3, modlitba, "z64.htm", "ZALM64");
			break;
		}// 2. týždeň žaltára -- koniec
		break;
	case 3: // 3. týždeň žaltára -- začiatok
		switch (den) {
		case DEN_NEDELA: // 3
			_set_zalmy_1nedele_mcd();
			break;
		case DEN_PONDELOK: // 3
			set_zalm(1, modlitba, "z119.htm", "ZALM119_LAMED");
			set_zalm(2, modlitba, "z71.htm", "ZALM71_I");
			set_zalm(3, modlitba, "z71.htm", "ZALM71_II");
			break;
		case DEN_UTOROK: // 3
			set_zalm(1, modlitba, "z119.htm", "ZALM119_MEM");
			set_zalm(2, modlitba, "z74.htm", "ZALM74_I");
			set_zalm(3, modlitba, "z74.htm", "ZALM74_II");
			break;
		case DEN_STREDA: // 3
			set_zalm(1, modlitba, "z119.htm", "ZALM119_NUN");
			set_zalm(2, modlitba, "z70.htm", "ZALM70");
			set_zalm(3, modlitba, "z75.htm", "ZALM75");
			break;
		case DEN_STVRTOK: // 3
			set_zalm(1, modlitba, "z119.htm", "ZALM119_SAMECH");
			set_zalm(2, modlitba, "z79.htm", "ZALM79");
			set_zalm(3, modlitba, "z80.htm", "ZALM80");
			break;
		case DEN_PIATOK: // 3
			set_zalm(1, modlitba, "z22.htm", "ZALM22_I");
			set_zalm(2, modlitba, "z22.htm", "ZALM22_II");
			set_zalm(3, modlitba, "z22.htm", "ZALM22_III");
			break;
		case DEN_SOBOTA: // 3
			set_zalm(1, modlitba, "z119.htm", "ZALM119_AIN");
			set_zalm(2, modlitba, "z34.htm", "ZALM34_I");
			set_zalm(3, modlitba, "z34.htm", "ZALM34_II");
			break;
		}// 3. týždeň žaltára -- koniec
		break;
	case 4: // 4. týždeň žaltára -- začiatok
		switch (den) {
		case DEN_NEDELA: // 4
			_set_zalmy_2nedele_mcd();
			break;
		case DEN_PONDELOK: // 4
			set_zalm(1, modlitba, "z119.htm", "ZALM119_PE");
			set_zalm(2, modlitba, "z82.htm", "ZALM82");
			set_zalm(3, modlitba, "z120.htm", "ZALM120");
			break;
		case DEN_UTOROK: // 4
			set_zalm(1, modlitba, "z119.htm", "ZALM119_SADE");
			set_zalm(2, modlitba, "z88.htm", "ZALM88_I");
			set_zalm(3, modlitba, "z88.htm", "ZALM88_II");
			break;
		case DEN_STREDA: // 4
			set_zalm(1, modlitba, "z119.htm", "ZALM119_KOF");
			set_zalm(2, modlitba, "z94.htm", "ZALM94_I");
			set_zalm(3, modlitba, "z94.htm", "ZALM94_II");
			break;
		case DEN_STVRTOK: // 4
			set_zalm(1, modlitba, "z119.htm", "ZALM119_RES");
			set_zalm(2, modlitba, "z128.htm", "ZALM128");
			set_zalm(3, modlitba, "z129.htm", "ZALM129");
			break;
		case DEN_PIATOK: // 4
			set_zalm(1, modlitba, "z119.htm", "ZALM119_SIN");
			set_zalm(2, modlitba, "z133.htm", "ZALM133");
			set_zalm(3, modlitba, "z140.htm", "ZALM140");
			break;
		case DEN_SOBOTA: // 4
			set_zalm(1, modlitba, "z119.htm", "ZALM119_TAU");
			set_zalm(2, modlitba, "z45.htm", "ZALM45_I");
			set_zalm(3, modlitba, "z45.htm", "ZALM45_II");
			break;
		}// 4. týždeň žaltára -- koniec
		break;
	} // switch(tyzzal)

	Log("_set_zalmy_mcd_zaltar(%d, %d, %d) -- end\n", den, tyzzal, modlitba);
} // _set_zalmy_mcd_zaltar()

// podľa prepínača BIT_OPT_1_MCD_ZALTAR_TRI sa nastavuje psalmódia zo dňa pre všetky tri hodinky, alebo sa nastavuje podľa BIT_OPT_1_MCD_ZALTAR_TRI
void set_zalmy_mcd_zaltar(short int den, short int tyzzal) {
	Log("set_zalmy_mcd_zaltar(%d, %d) -- begin\n", den, tyzzal);
	if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_ZALTAR_TRI)) {
		_set_zalmy_mcd_zaltar(den, UPRAV_TYZZAL(tyzzal, MODL_PREDPOLUDNIM), MODL_PREDPOLUDNIM);
		_set_zalmy_mcd_zaltar(den, UPRAV_TYZZAL(tyzzal, MODL_NAPOLUDNIE), MODL_NAPOLUDNIE);
		_set_zalmy_mcd_zaltar(den, UPRAV_TYZZAL(tyzzal, MODL_POPOLUDNI), MODL_POPOLUDNI);
	}
	else {
		_set_zalmy_mcd_zaltar(den, tyzzal, MODL_CEZ_DEN_VSETKY);
	}
	Log("set_zalmy_mcd_zaltar(%d, %d) -- end\n", den, tyzzal);
} // set_zalmy_mcd_zaltar()

void set_spolocne_veci_common() {
	// currently suffices for morning and evening prayer
	_SET_SPOLOCNE_VECI_COMMON(MODL_PRVE_VESPERY);
	_SET_SPOLOCNE_VECI_COMMON(MODL_RANNE_CHVALY);
	_SET_SPOLOCNE_VECI_COMMON(MODL_VESPERY);
}// set_spolocne_veci_common()

void zaltar_zvazok(short int den, short int tyzzal, short int obdobie, short int specialne) {
	Log("zaltar_zvazok(%d, %d, %d, %d) -- begin\n", den, tyzzal, obdobie, specialne);
	short int zvazok = zvazok_breviara[obdobie];
	Log("liturgické obdobie: `%s'...\n", nazov_obdobia_[obdobie]);
	Log("toto liturgické obdobie sa nachádza v zväzku %d breviára (cezročné obdobie evidujeme ako jeden, 3. zväzok)...\n", zvazok);

	Log("nastavujem veci pre kompletórium...\n");
	zaltar_kompletorium(den, obdobie, specialne, tyzzal);

	Log("nastavujem spoločné veci (nateraz pre ranné chvály a vešpery)...\n");
	set_spolocne_veci_common(); // ToDo: zvážiť | možno časom by aj nastavenie pre kompletórium mohlo ísť sem dovnútra... potom by nebolo treba špeciálne nastavovať napr. pre slávnosti

	if (specialne == ZALTAR_VSETKO) {
		Log("ZALTAR_VSETKO -- takže nastavujem všetko zo žaltára... (zaltar_zvazok)\n");

		set_antifony(den, tyzzal, zvazok, MODL_INVITATORIUM);

		if (den == DEN_NEDELA) {
			_SET_SPOLOCNE_VECI_NEDELA(MODL_PRVE_VESPERY);
			_SET_SPOLOCNE_VECI_NEDELA(MODL_RANNE_CHVALY);
			_SET_SPOLOCNE_VECI_NEDELA(MODL_POSV_CITANIE);
			_SET_SPOLOCNE_VECI_NEDELA(MODL_PREDPOLUDNIM);
			_SET_SPOLOCNE_VECI_NEDELA(MODL_NAPOLUDNIE);
			_SET_SPOLOCNE_VECI_NEDELA(MODL_POPOLUDNI);
			_SET_SPOLOCNE_VECI_NEDELA(MODL_VESPERY);
		}// den == DEN_NEDELA
		else {// nie nedeľa
			_SET_SPOLOCNE_VECI_NIE_NEDELA(MODL_RANNE_CHVALY);
			_SET_SPOLOCNE_VECI_NIE_NEDELA(MODL_VESPERY);
			_SET_SPOLOCNE_VECI_NIE_NEDELA(MODL_POSV_CITANIE);
			_SET_SPOLOCNE_VECI_NIE_NEDELA(MODL_PREDPOLUDNIM);
			_SET_SPOLOCNE_VECI_NIE_NEDELA(MODL_NAPOLUDNIE);
			_SET_SPOLOCNE_VECI_NIE_NEDELA(MODL_POPOLUDNI);
			set_benediktus(den, tyzzal, MODL_RANNE_CHVALY);
			set_magnifikat(den, tyzzal, MODL_VESPERY);
		}// den != DEN_NEDELA
	}// len ak if(specialne == ZALTAR_VSETKO)
	else if (specialne == ZALTAR_IBA_ZALMY_HYMNUS_MCD) {
		Log("ZALTAR_IBA_ZALMY_HYMNUS_MCD -- takže nastavujem len hymny pre mcd...\n");
		set_hymnus(den, tyzzal, MODL_PREDPOLUDNIM);
		set_hymnus(den, tyzzal, MODL_NAPOLUDNIE);
		set_hymnus(den, tyzzal, MODL_POPOLUDNI);
	}// len ak if(specialne == ZALTAR_IBA_ZALMY_HYMNUS_MCD)
	else if (specialne == ZALTAR_ANT_ZALMY_HYMNUS_MCD) {
		Log("ZALTAR_ANT_ZALMY_HYMNUS_MCD -- takže nastavujem hymny a antifóny pre mcd...\n");
		_SET_HYMNUS_ANTINFONY_MCD(MODL_PREDPOLUDNIM);
		_SET_HYMNUS_ANTINFONY_MCD(MODL_NAPOLUDNIE);
		_SET_HYMNUS_ANTINFONY_MCD(MODL_POPOLUDNI);
	}// len ak if(specialne == ZALTAR_IBA_ZALMY_HYMNUS_MCD)
	else {
		Log("nebolo ZALTAR_VSETKO ani ZALTAR_IBA_ZALMY_HYMNUS_MCD, ani ZALTAR_ANT_ZALMY_HYMNUS_MCD -- takže nastavujem len žalmy...\n");
	}

	Log("ďalej nastavujem žalmy (špecialitky spoločné pre niektoré týždne žaltára)...\n");
	// cast rovnaka pre kazdy tyzden zaltara
	switch (den) {
	case DEN_NEDELA:
		// druhe vespery maju vzdy prvy zalm 110, 1-5.7
		set_zalm(1, MODL_VESPERY, "z110.htm", "ZALM110");
		// nedelny ranny hymnus je rovnaky v prvom a tretom, resp. druhom a stvrtom tyzdni
		if ((tyzzal == 1) || (tyzzal == 3)) {
			set_zalm(2, MODL_RANNE_CHVALY, "ch_dan3_57.htm", "CHVAL_DAN3,57-88.56");
			// modlitba cez deň
			_set_zalmy_1nedele_mcd();
		}
		else { // if((tyzzal == 2) || (tyzzal == 4))
			set_zalm(1, MODL_RANNE_CHVALY, "z118.htm", "ZALM118");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_dan3_52.htm", "CHVAL_DAN3,52-57");
			set_zalm(3, MODL_RANNE_CHVALY, "z150.htm", "ZALM150");
			// modlitba cez deň
			_set_zalmy_2nedele_mcd();
		}
		// vecerne nedelne hymny su rovnake v kazdom tyzdni
		set_zalm(3, MODL_PRVE_VESPERY, "ch_flp2.htm", "CHVAL_FLP2");
		if ((_global_den.litobd != OBD_POSTNE_I) &&
			(_global_den.litobd != OBD_POSTNE_II_VELKY_TYZDEN)) {
			set_zalm(3, MODL_VESPERY, "ch_zjv19.htm", "CHVAL_ZJV19");
		}
		else {
			set_zalm(3, MODL_VESPERY, "ch_1pt2.htm", "CHVAL_1PT2");
		}
		break;
		// vecerny hymnus vsedneho dna je rovnaky v kazdom tyzdni
	case DEN_PONDELOK:
		set_zalm(3, MODL_VESPERY, "ch_ef1.htm", "CHVAL_EF1");
		break;
	case DEN_UTOROK:
		set_zalm(3, MODL_VESPERY, "ch_zjv4_5.htm", "CHVAL_ZJV45");
		break;
	case DEN_STREDA:
		set_zalm(3, MODL_VESPERY, "ch_kol1.htm", "CHVAL_KOL1");
		break;
	case DEN_STVRTOK:
		set_zalm(3, MODL_VESPERY, "ch_zjv11.htm", "CHVAL_ZJV11");
		break;
	case DEN_PIATOK:
		// kazdy piatok, ranne chvaly je zalm 51 */
		set_zalm(1, MODL_RANNE_CHVALY, "z51.htm", "ZALM51");
		set_zalm(3, MODL_VESPERY, "ch_zjv15.htm", "CHVAL_ZJV15");
		break;
	case DEN_SOBOTA:
		break;
	} // switch(den)

	Log("ďalej nastavujem žalmy (pre jednotlivý týždeň žaltára)...\n");
	// cast specificka pre kazdy tyzden zaltara
	switch (tyzzal) {
	case 1: // prvy tyzden zaltara
		switch (den) {
		case DEN_NEDELA: // 1
			// prvé vešpery
			set_zalm(1, MODL_PRVE_VESPERY, "z141.htm", "ZALM141");
			set_zalm(2, MODL_PRVE_VESPERY, "z142.htm", "ZALM142");
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z63.htm", "ZALM63");
			set_zalm(3, MODL_RANNE_CHVALY, "z149.htm", "ZALM149");
			// modlitba cez deň
			// druhé vešpery
			set_zalm(2, MODL_VESPERY, "z114.htm", "ZALM114");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z1.htm", "ZALM1");
			set_zalm(2, MODL_POSV_CITANIE, "z2.htm", "ZALM2");
			set_zalm(3, MODL_POSV_CITANIE, "z3.htm", "ZALM3");
			break;

		case DEN_PONDELOK: // 1
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z5.htm", "ZALM5");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_1krn29.htm", "CHVAL_1KRN29");
			set_zalm(3, MODL_RANNE_CHVALY, "z29.htm", "ZALM29");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z11.htm", "ZALM11");
			set_zalm(2, MODL_VESPERY, "z15.htm", "ZALM15");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z6.htm", "ZALM6");
			set_zalm(2, MODL_POSV_CITANIE, "z9.htm", "ZALM9_I");
			set_zalm(3, MODL_POSV_CITANIE, "z9.htm", "ZALM9_II");
			break;

		case DEN_UTOROK: // 1
			// ranné chvály
			// 2011-09-06: možnosť zvoliť žalm 95
			if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALM95)) {
				set_zalm(1, MODL_RANNE_CHVALY, "z95.htm", "ZALM95");
			}
			else {
				set_zalm(1, MODL_RANNE_CHVALY, "z24.htm", "ZALM24");
			}
			set_zalm(2, MODL_RANNE_CHVALY, "ch_tob13.htm", "CHVAL_TOB13,2-8");
			set_zalm(3, MODL_RANNE_CHVALY, "z33.htm", "ZALM33");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z20.htm", "ZALM20");
			set_zalm(2, MODL_VESPERY, "z21.htm", "ZALM21");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z10.htm", "ZALM10_I");
			set_zalm(2, MODL_POSV_CITANIE, "z10.htm", "ZALM10_II");
			set_zalm(3, MODL_POSV_CITANIE, "z12.htm", "ZALM12");
			break;

		case DEN_STREDA: // 1
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z36.htm", "ZALM36");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_jdt16.htm", "CHVAL_JDT16");
			set_zalm(3, MODL_RANNE_CHVALY, "z47.htm", "ZALM47");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z27.htm", "ZALM27_I");
			set_zalm(2, MODL_VESPERY, "z27.htm", "ZALM27_II");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z18.htm", "ZALM18_I");
			set_zalm(2, MODL_POSV_CITANIE, "z18.htm", "ZALM18_II");
			set_zalm(3, MODL_POSV_CITANIE, "z18.htm", "ZALM18_III");
			break;

		case DEN_STVRTOK: // 1
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z57.htm", "ZALM57");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_jer31.htm", "CHVAL_JER31");
			set_zalm(3, MODL_RANNE_CHVALY, "z48.htm", "ZALM48");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z30.htm", "ZALM30");
			set_zalm(2, MODL_VESPERY, "z32.htm", "ZALM32");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z18.htm", "ZALM18_IV");
			set_zalm(2, MODL_POSV_CITANIE, "z18.htm", "ZALM18_V");
			set_zalm(3, MODL_POSV_CITANIE, "z18.htm", "ZALM18_VI");
			break;

		case DEN_PIATOK: // 1
			// ranné chvály
			set_zalm(2, MODL_RANNE_CHVALY, "ch_iz45.htm", "CHVAL_IZ45");
			// 2011-09-06: možnosť zvoliť žalm 95
			if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALM95)) {
				set_zalm(3, MODL_RANNE_CHVALY, "z95.htm", "ZALM95");
			}
			else {
				set_zalm(3, MODL_RANNE_CHVALY, "z100.htm", "ZALM100");
			}
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z41.htm", "ZALM41");
			set_zalm(2, MODL_VESPERY, "z46.htm", "ZALM46");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z35.htm", "ZALM35_I");
			set_zalm(2, MODL_POSV_CITANIE, "z35.htm", "ZALM35_II");
			set_zalm(3, MODL_POSV_CITANIE, "z35.htm", "ZALM35_III");
			break;

		case DEN_SOBOTA: // 1
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z119.htm", "ZALM119_KOF");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_ex15.htm", "CHVAL_EX15");
			set_zalm(3, MODL_RANNE_CHVALY, "z117.htm", "ZALM117");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// posvätné čítanie
			if (je_odlisny_zaltar) {
				set_zalm(1, MODL_POSV_CITANIE, "z105.htm", "ZALM105_I");
				set_zalm(2, MODL_POSV_CITANIE, "z105.htm", "ZALM105_II");
				set_zalm(3, MODL_POSV_CITANIE, "z105.htm", "ZALM105_III");
			}
			else {
				set_zalm(1, MODL_POSV_CITANIE, "z131.htm", "ZALM131");
				set_zalm(2, MODL_POSV_CITANIE, "z132.htm", "ZALM132_I");
				set_zalm(3, MODL_POSV_CITANIE, "z132.htm", "ZALM132_II");
			}
			break;

		default: break;
		}; break; // case 1

	case 2: // druhy tyzden zaltara
		switch (den) {
		case DEN_NEDELA: // 2
			// prvé vešpery
			set_zalm(1, MODL_PRVE_VESPERY, "z119.htm", "ZALM119_NUN");
			set_zalm(2, MODL_PRVE_VESPERY, "z16.htm", "ZALM16");
			// ranné chvály
			// modlitba cez deň
			// druhé vešpery
			set_zalm(2, MODL_VESPERY, "z115.htm", "ZALM115");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z104.htm", "ZALM104_I");
			set_zalm(2, MODL_POSV_CITANIE, "z104.htm", "ZALM104_II");
			set_zalm(3, MODL_POSV_CITANIE, "z104.htm", "ZALM104_III");
			break;

		case DEN_PONDELOK: // 2
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z42.htm", "ZALM42");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_sir36.htm", "CHVAL_SIR36");
			set_zalm(3, MODL_RANNE_CHVALY, "z19.htm", "ZALM19,2-7");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z45.htm", "ZALM45_I");
			set_zalm(2, MODL_VESPERY, "z45.htm", "ZALM45_II");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z31.htm", "ZALM31_I");
			set_zalm(2, MODL_POSV_CITANIE, "z31.htm", "ZALM31_II");
			set_zalm(3, MODL_POSV_CITANIE, "z31.htm", "ZALM31_III");
			break;

		case DEN_UTOROK: // 2
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z43.htm", "ZALM43");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_iz38.htm", "CHVAL_IZ38");
			set_zalm(3, MODL_RANNE_CHVALY, "z65.htm", "ZALM65");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z49.htm", "ZALM49_I");
			set_zalm(2, MODL_VESPERY, "z49.htm", "ZALM49_II");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z37.htm", "ZALM37_I");
			set_zalm(2, MODL_POSV_CITANIE, "z37.htm", "ZALM37_II");
			set_zalm(3, MODL_POSV_CITANIE, "z37.htm", "ZALM37_III");
			break;

		case DEN_STREDA: // 2
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z77.htm", "ZALM77");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_1sam2.htm", "CHVAL_1SAM2");
			set_zalm(3, MODL_RANNE_CHVALY, "z97.htm", "ZALM97");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z62.htm", "ZALM62");
			// 2011-09-06: možnosť zvoliť žalm 95
			if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALM95)) {
				set_zalm(2, MODL_VESPERY, "z95.htm", "ZALM95");
			}
			else {
				set_zalm(2, MODL_VESPERY, "z67.htm", "ZALM67");
			}
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z39.htm", "ZALM39_I");
			set_zalm(2, MODL_POSV_CITANIE, "z39.htm", "ZALM39_II");
			set_zalm(3, MODL_POSV_CITANIE, "z52.htm", "ZALM52");
			break;

		case DEN_STVRTOK: // 2
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z80.htm", "ZALM80");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_iz12.htm", "CHVAL_IZ12");
			set_zalm(3, MODL_RANNE_CHVALY, "z81.htm", "ZALM81");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z72.htm", "ZALM72_I");
			set_zalm(2, MODL_VESPERY, "z72.htm", "ZALM72_II");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z44.htm", "ZALM44_I");
			set_zalm(2, MODL_POSV_CITANIE, "z44.htm", "ZALM44_II");
			set_zalm(3, MODL_POSV_CITANIE, "z44.htm", "ZALM44_III");
			break;

		case DEN_PIATOK: // 2
			// ranné chvály
			set_zalm(2, MODL_RANNE_CHVALY, "ch_hab3.htm", "CHVAL_HAB3");
			set_zalm(3, MODL_RANNE_CHVALY, "z147.htm", "ZALM147,12-20");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z116.htm", "ZALM116,1-9");
			set_zalm(2, MODL_VESPERY, "z121.htm", "ZALM121");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z38.htm", "ZALM38_I");
			set_zalm(2, MODL_POSV_CITANIE, "z38.htm", "ZALM38_II");
			set_zalm(3, MODL_POSV_CITANIE, "z38.htm", "ZALM38_III");
			break;

		case DEN_SOBOTA: // 2
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z92.htm", "ZALM92");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_dt32.htm", "CHVAL_DT32");
			set_zalm(3, MODL_RANNE_CHVALY, "z8.htm", "ZALM8");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// posvätné čítanie
			if (je_odlisny_zaltar) {
				set_zalm(1, MODL_POSV_CITANIE, "z106.htm", "ZALM106_I");
				set_zalm(2, MODL_POSV_CITANIE, "z106.htm", "ZALM106_II");
				set_zalm(3, MODL_POSV_CITANIE, "z106.htm", "ZALM106_III");
			}
			else {
				set_zalm(1, MODL_POSV_CITANIE, "z136.htm", "ZALM136_I");
				set_zalm(2, MODL_POSV_CITANIE, "z136.htm", "ZALM136_II_PC");
				set_zalm(3, MODL_POSV_CITANIE, "z136.htm", "ZALM136_III_PC"); // inak je Ž 136 cleneny pre pondelok 4. tyzdna, vespery
			}
			break;

		default: break;
		}; break; // case 2 */

	case 3: // treti tyzden zaltara
		switch (den) {
		case DEN_NEDELA: // 3
			// prvé vešpery
			set_zalm(1, MODL_PRVE_VESPERY, "z113.htm", "ZALM113");
			set_zalm(2, MODL_PRVE_VESPERY, "z116.htm", "ZALM116,10-19");
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z93.htm", "ZALM93");
			set_zalm(3, MODL_RANNE_CHVALY, "z148.htm", "ZALM148");
			// modlitba cez deň
			// druhé vešpery
			set_zalm(2, MODL_VESPERY, "z111.htm", "ZALM111");
			// posvätné čítanie
			_set_zalmy_pc_145(MODL_POSV_CITANIE);
			break;

		case DEN_PONDELOK: // 3
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z84.htm", "ZALM84");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_iz2.htm", "CHVAL_IZ2");
			set_zalm(3, MODL_RANNE_CHVALY, "z96.htm", "ZALM96");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z123.htm", "ZALM123");
			set_zalm(2, MODL_VESPERY, "z124.htm", "ZALM124");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z50.htm", "ZALM50_I");
			set_zalm(2, MODL_POSV_CITANIE, "z50.htm", "ZALM50_II");
			set_zalm(3, MODL_POSV_CITANIE, "z50.htm", "ZALM50_III");
			break;

		case DEN_UTOROK: // 3
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z85.htm", "ZALM85");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_iz26.htm", "CHVAL_IZ26");
			// možnosť zvoliť žalm 95
			if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALM95)) {
				set_zalm(3, MODL_RANNE_CHVALY, "z95.htm", "ZALM95");
			}
			else {
				set_zalm(3, MODL_RANNE_CHVALY, "z67.htm", "ZALM67");
			}
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z125.htm", "ZALM125");
			set_zalm(2, MODL_VESPERY, "z131.htm", "ZALM131");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z68.htm", "ZALM68_I");
			set_zalm(2, MODL_POSV_CITANIE, "z68.htm", "ZALM68_II");
			set_zalm(3, MODL_POSV_CITANIE, "z68.htm", "ZALM68_III");
			break;

		case DEN_STREDA: // 3
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z86.htm", "ZALM86");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_iz33.htm", "CHVAL_IZ33");
			set_zalm(3, MODL_RANNE_CHVALY, "z98.htm", "ZALM98");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z126.htm", "ZALM126");
			set_zalm(2, MODL_VESPERY, "z127.htm", "ZALM127");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z89.htm", "ZALM89_I");
			set_zalm(2, MODL_POSV_CITANIE, "z89.htm", "ZALM89_II");
			set_zalm(3, MODL_POSV_CITANIE, "z89.htm", "ZALM89_III");
			break;

		case DEN_STVRTOK: // 3
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z87.htm", "ZALM87");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_iz40.htm", "CHVAL_IZ40");
			set_zalm(3, MODL_RANNE_CHVALY, "z99.htm", "ZALM99");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z132.htm", "ZALM132_I");
			set_zalm(2, MODL_VESPERY, "z132.htm", "ZALM132_II");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z89.htm", "ZALM89_IV");
			set_zalm(2, MODL_POSV_CITANIE, "z89.htm", "ZALM89_V");
			set_zalm(3, MODL_POSV_CITANIE, "z90.htm", "ZALM90");
			break;

		case DEN_PIATOK: // 3
			// ranné chvály
			set_zalm(2, MODL_RANNE_CHVALY, "ch_jer14.htm", "CHVAL_JER14");
			// možnosť zvoliť žalm 95
			if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALM95)) {
				set_zalm(3, MODL_RANNE_CHVALY, "z95.htm", "ZALM95");
			}
			else {
				set_zalm(3, MODL_RANNE_CHVALY, "z100.htm", "ZALM100");
			}
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z135.htm", "ZALM135_I");
			set_zalm(2, MODL_VESPERY, "z135.htm", "ZALM135_II");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z69.htm", "ZALM69_I");
			set_zalm(2, MODL_POSV_CITANIE, "z69.htm", "ZALM69_II");
			set_zalm(3, MODL_POSV_CITANIE, "z69.htm", "ZALM69_III");
			break;

		case DEN_SOBOTA: // 3
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z119.htm", "ZALM119_KOF");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_mud9.htm", "CHVAL_MUD9");
			set_zalm(3, MODL_RANNE_CHVALY, "z117.htm", "ZALM117");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z107.htm", "ZALM107_I");
			set_zalm(2, MODL_POSV_CITANIE, "z107.htm", "ZALM107_II");
			set_zalm(3, MODL_POSV_CITANIE, "z107.htm", "ZALM107_III");
			break;

		default: break;
		}; break; // case 3

	case 4: // stvrty tyzden zaltara
		switch (den) {
		case DEN_NEDELA: // 4
			// prvé vešpery
			set_zalm(1, MODL_PRVE_VESPERY, "z122.htm", "ZALM122");
			set_zalm(2, MODL_PRVE_VESPERY, "z130.htm", "ZALM130");
			// ranné chvály
			// modlitba cez deň
			// druhé vešpery
			set_zalm(2, MODL_VESPERY, "z112.htm", "ZALM112");
			// posvätné čítanie
			// možnosť zvoliť žalm 95
			if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALM95)) {
				set_zalm(1, MODL_POSV_CITANIE, "z95.htm", "ZALM95");
			}
			else {
				set_zalm(1, MODL_POSV_CITANIE, "z24.htm", "ZALM24");
			}
			set_zalm(2, MODL_POSV_CITANIE, "z66.htm", "ZALM66_I");
			set_zalm(3, MODL_POSV_CITANIE, "z66.htm", "ZALM66_II");
			break;

		case DEN_PONDELOK: // 4
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z90.htm", "ZALM90");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_iz42.htm", "CHVAL_IZ42");
			set_zalm(3, MODL_RANNE_CHVALY, "z135.htm", "ZALM135,1-12");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z136.htm", "ZALM136_I");
			set_zalm(2, MODL_VESPERY, "z136.htm", "ZALM136_II"); // inak je Ž 136 cleneny pre sobotu 2. tyzdna, posvatne citanie
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z73.htm", "ZALM73_I");
			set_zalm(2, MODL_POSV_CITANIE, "z73.htm", "ZALM73_II");
			set_zalm(3, MODL_POSV_CITANIE, "z73.htm", "ZALM73_III");
			break;

		case DEN_UTOROK: // 4
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z101.htm", "ZALM101");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_dan3_26.htm", "CHVAL_DAN3,26");
			set_zalm(3, MODL_RANNE_CHVALY, "z144.htm", "ZALM144,1-10");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z137.htm", "ZALM137");
			set_zalm(2, MODL_VESPERY, "z138.htm", "ZALM138");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z102.htm", "ZALM102_I");
			set_zalm(2, MODL_POSV_CITANIE, "z102.htm", "ZALM102_II");
			set_zalm(3, MODL_POSV_CITANIE, "z102.htm", "ZALM102_III");
			break;

		case DEN_STREDA: // 4
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z108.htm", "ZALM108");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_iz61.htm", "CHVAL_IZ61");
			set_zalm(3, MODL_RANNE_CHVALY, "z146.htm", "ZALM146");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z139.htm", "ZALM139_I");
			set_zalm(2, MODL_VESPERY, "z139.htm", "ZALM139_II");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z103.htm", "ZALM103_I");
			set_zalm(2, MODL_POSV_CITANIE, "z103.htm", "ZALM103_II");
			set_zalm(3, MODL_POSV_CITANIE, "z103.htm", "ZALM103_III");
			break;

		case DEN_STVRTOK: // 4
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z143.htm", "ZALM143");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_iz66.htm", "CHVAL_IZ66");
			set_zalm(3, MODL_RANNE_CHVALY, "z147.htm", "ZALM147,1-11");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z144.htm", "ZALM144_I");
			set_zalm(2, MODL_VESPERY, "z144.htm", "ZALM144_II");
			// posvätné čítanie
			set_zalm(1, MODL_POSV_CITANIE, "z44.htm", "ZALM44_I");
			set_zalm(2, MODL_POSV_CITANIE, "z44.htm", "ZALM44_II");
			set_zalm(3, MODL_POSV_CITANIE, "z44.htm", "ZALM44_III");
			break;

		case DEN_PIATOK: // 4
			// ranné chvály
			set_zalm(2, MODL_RANNE_CHVALY, "ch_tob13.htm", "CHVAL_TOB13,8-16");
			set_zalm(3, MODL_RANNE_CHVALY, "z147.htm", "ZALM147,12-20");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// vešpery
			set_zalm(1, MODL_VESPERY, "z145.htm", "ZALM145_I");
			set_zalm(2, MODL_VESPERY, "z145.htm", "ZALM145_II");
			// posvätné čítanie
			if (je_odlisny_zaltar) {
				set_zalm(1, MODL_POSV_CITANIE, "z78.htm", "ZALM78_I");
				set_zalm(2, MODL_POSV_CITANIE, "z78.htm", "ZALM78_II");
				set_zalm(3, MODL_POSV_CITANIE, "z78.htm", "ZALM78_III");
			}
			else {
				set_zalm(1, MODL_POSV_CITANIE, "z55.htm", "ZALM55_I_PC");
				set_zalm(2, MODL_POSV_CITANIE, "z55.htm", "ZALM55_II_PC");
				set_zalm(3, MODL_POSV_CITANIE, "z55.htm", "ZALM55_III_PC"); // inak clenene pre modlitbu cez den, streda v 2. tyzdni
			}
			break;

		case DEN_SOBOTA: // 4
			// ranné chvály
			set_zalm(1, MODL_RANNE_CHVALY, "z92.htm", "ZALM92");
			set_zalm(2, MODL_RANNE_CHVALY, "ch_ez36.htm", "CHVAL_EZ36");
			set_zalm(3, MODL_RANNE_CHVALY, "z8.htm", "ZALM8");
			// modlitba cez deň
			set_zalmy_mcd_zaltar(den, tyzzal);
			// posvätné čítanie
			if (je_odlisny_zaltar) {
				set_zalm(1, MODL_POSV_CITANIE, "z78.htm", "ZALM78_IV");
				set_zalm(2, MODL_POSV_CITANIE, "z78.htm", "ZALM78_V");
				set_zalm(3, MODL_POSV_CITANIE, "z78.htm", "ZALM78_VI");
			}
			else {
				set_zalm(1, MODL_POSV_CITANIE, "z50.htm", "ZALM50_I");
				set_zalm(2, MODL_POSV_CITANIE, "z50.htm", "ZALM50_II");
				set_zalm(3, MODL_POSV_CITANIE, "z50.htm", "ZALM50_III");
			}
			break;

		default: break;
		}; break; // case 4

	} // switch(tyzzal)

	Log("napokon idem pre modlitbu cez deň skontrolovať, či netreba brať doplnkovú psalmódiu...\n");
	// nastavenie žalm 95 ako alternatívy k ž 24, 67, 100 pre ranné chvály resp. vešpery sa robí na inom mieste
	if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA)) {
		Log("-- áno, beriem doplnkovú psalmódiu.\n");
		_set_zalmy_mcd_doplnkova_psalmodia(NIE);
		if (_global_den.litobd == OBD_CEZ_ROK) {
			_set_antifony_mcd_doplnkova_psalmodia();
		}// pre cezročné obdobie nastavíme aj antifóny
	}// isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA)
	else {
		Log("-- nie, doplnkovú psalmódiu neberiem.\n");
	}
	Log("zaltar_zvazok(%d, %d, %d, %d) -- end\n", den, tyzzal, obdobie, specialne);
} // zaltar_zvazok();

void zaltar(short int den, short int tyzzal) {
	// kvôli spätnej kompatibilite ponechaná aj funkcia s 2 parametrami
	Log("-- zaltar(%d, %d) -- zaciatok\n", den, tyzzal);
	zaltar_zvazok(den, tyzzal, OBD_CEZ_ROK, ZALTAR_VSETKO);
	Log("-- zaltar(%d, %d) -- koniec\n", den, tyzzal);
} // zaltar();

void _set_zalmy_velky_piatok(short int modlitba) {
	Log("_set_zalmy_velky_piatok(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z116.htm", "ZALM116,10-19");
		set_zalm(2, modlitba, "z143.htm", "ZALM143");
		set_zalm(3, modlitba, "ch_flp2.htm", "CHVAL_FLP2");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		// zalmy z piatka 2. tyzdna zaltara
		Log("zalmy su z piatka 2. tyzdna zaltara...\n");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z2.htm", "ZALM2");
		set_zalm(2, modlitba, "z22.htm", "ZALM22_CELY");
		set_zalm(3, modlitba, "z38.htm", "ZALM38_CELY");
	}
	else if ((je_modlitba_cez_den(modlitba)) && (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA))) {
		// na ostatné hodiny sa berie doplnková psalmódia
		set_zalm(1, modlitba, "z40.htm", "ZALM40");
		set_zalm(2, modlitba, "z54.htm", "ZALM54");
		set_zalm(3, modlitba, "z88.htm", "ZALM88");
	}
	Log("_set_zalmy_velky_piatok(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_velky_piatok()

void _set_zalmy_biela_sobota(short int modlitba) {
	Log("_set_zalmy_biela_sobota(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z116.htm", "ZALM116,10-19");
		set_zalm(2, modlitba, "z143.htm", "ZALM143");
		set_zalm(3, modlitba, "ch_flp2.htm", "CHVAL_FLP2");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		set_zalm(1, modlitba, "z64.htm", "ZALM64");
		set_zalm(2, modlitba, "ch_iz38.htm", "CHVAL_IZ38");
		set_zalm(3, modlitba, "z150.htm", "ZALM150");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z4.htm", "ZALM4");
		set_zalm(2, modlitba, "z16.htm", "ZALM16");
		// možnosť zvoliť žalm 95
		if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALM95)) {
			set_zalm(3, modlitba, "z95.htm", "ZALM95");
		}
		else {
			set_zalm(3, modlitba, "z24.htm", "ZALM24");
		}
	}
	else if ((je_modlitba_cez_den(modlitba)) && (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA))) {
		// na ostatné hodiny sa berie doplnková psalmódia
		set_zalm(1, modlitba, "z27.htm", "ZALM27");
		set_zalm(2, modlitba, "z30.htm", "ZALM30");
		set_zalm(3, modlitba, "z76.htm", "ZALM76");
	}
	Log("_set_zalmy_biela_sobota(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_biela_sobota()

void _set_zalmy_za_zosnulych(short int modlitba) {
	Log("_set_zalmy_za_zosnulych(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z121.htm", "ZALM121");
		set_zalm(2, modlitba, "z130.htm", "ZALM130");
		set_zalm(3, modlitba, "ch_flp2.htm", "CHVAL_FLP2");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		set_zalm(1, modlitba, "z51.htm", "ZALM51");
		set_zalm(2, modlitba, "ch_iz38.htm", "CHVAL_IZ38");
		if (!isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_OFF_DEF_PSALM_146_150)) {
			set_zalm(3, modlitba, "z146.htm", "ZALM146");
		}
		else {
			set_zalm(3, modlitba, "z150.htm", "ZALM150");
		}
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z40.htm", "ZALM40_I");
		set_zalm(2, modlitba, "z40.htm", "ZALM40_II");
		set_zalm(3, modlitba, "z42.htm", "ZALM42");
	}
	else if ((je_modlitba_cez_den(modlitba)) && (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA))) {
		// na ostatné hodiny sa berie doplnková psalmódia
		set_zalm(1, modlitba, "z70.htm", "ZALM70");
		set_zalm(2, modlitba, "z85.htm", "ZALM85");
		set_zalm(3, modlitba, "z86.htm", "ZALM86");
	}
	Log("_set_zalmy_za_zosnulych(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_za_zosnulych()

void _set_zalmy_1nedele_rch(void) {// ranné chvály
	Log("_set_zalmy_1nedele_rch() -- begin\n");
	set_zalm(1, MODL_RANNE_CHVALY, "z63.htm", "ZALM63");
	set_zalm(2, MODL_RANNE_CHVALY, "ch_dan3_57.htm", "CHVAL_DAN3,57-88.56");
	set_zalm(3, MODL_RANNE_CHVALY, "z149.htm", "ZALM149");
	Log("_set_zalmy_1nedele_rch() -- end\n");
} // _set_zalmy_1nedele_rch()

void _set_zalmy_1nedele_v(void) {// vešpery
	Log("_set_zalmy_1nedele_v() -- begin\n");
	set_zalm(1, MODL_VESPERY, "z110.htm", "ZALM110");
	set_zalm(2, MODL_VESPERY, "z114.htm", "ZALM114");
	set_zalm(3, MODL_VESPERY, "ch_zjv19.htm", "CHVAL_ZJV19");
	Log("_set_zalmy_1nedele_v() -- end\n");
} // _set_zalmy_1nedele_v()

void _set_zalmy_1nedele_v_pre_1v(void) {// žalmy a chválospev z vešpier pre prvé vešpery -- kvôli druhej veľkonočnej nedeli
	Log("_set_zalmy_1nedele_v_pre_1v() -- begin\n");
	set_zalm(1, MODL_PRVE_VESPERY, "z110.htm", "ZALM110");
	set_zalm(2, MODL_PRVE_VESPERY, "z114.htm", "ZALM114");
	set_zalm(3, MODL_PRVE_VESPERY, "ch_zjv19.htm", "CHVAL_ZJV19");
	Log("_set_zalmy_1nedele_v_pre_1v() -- end\n");
} // _set_zalmy_1nedele_v_pre_1v()

// žalmy nedele 1. týždňa kvôli posv. čítaniam (napr. druhá nedeľa vo veľk. oktáve)
void _set_zalmy_1nedele_pc(void) {// prvé vešpery
	Log("_set_zalmy_1nedele_pc() -- begin\n");
	// modlitba cez deň
	set_zalm(1, MODL_POSV_CITANIE, "z1.htm", "ZALM1");
	set_zalm(2, MODL_POSV_CITANIE, "z2.htm", "ZALM2");
	set_zalm(3, MODL_POSV_CITANIE, "z3.htm", "ZALM3");
	Log("_set_zalmy_1nedele_pc() -- end\n");
} // _set_zalmy_1nedele_pc()

void _set_zalmy_posviacka_chramu(short int modlitba) {
	Log("_set_zalmy_posviacka_chramu(%s) -- begin\n", nazov_modlitby(modlitba));

	// pre MCD nastavíme info, že v predpísanej psalmódii môže dôjsť k opakovaniu žalmov, a preto je možnosť alternatívy (vyňaté mimo konkrétnej modlitby)
	_set_mcd_doplnkova_psalmodia_z122_129(MODL_PREDPOLUDNIM);

	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z46.htm", "ZALM46");
		set_zalm(2, modlitba, "z122.htm", "ZALM122");
		if ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)) {
			set_zalm(3, modlitba, "ch_zjv15.htm", "CHVAL_ZJV15");
		}
		else {
			set_zalm(3, modlitba, "ch_zjv19.htm", "CHVAL_ZJV19");
		}
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z147.htm", "ZALM147,1-11");
		set_zalm(2, modlitba, "z147.htm", "ZALM147,12-20");
		if ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)) {
			set_zalm(3, modlitba, "ch_kol1.htm", "CHVAL_KOL1");
		}
		else {
			set_zalm(3, modlitba, "ch_zjv19.htm", "CHVAL_ZJV19");
		}
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		// možnosť zvoliť žalm 95
		if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALM95)) {
			set_zalm(1, modlitba, "z95.htm", "ZALM95");
		}
		else {
			set_zalm(1, modlitba, "z24.htm", "ZALM24");
		}
		set_zalm(2, modlitba, "z84.htm", "ZALM84");
		set_zalm(3, modlitba, "z87.htm", "ZALM87");
	}
	else if (je_modlitba_cez_den(modlitba)) {
		_set_zalmy_mcd_1nedela_or_doplnkova_psalmodia();
	}

	Log("_set_zalmy_posviacka_chramu(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_posviacka_chramu()

void _set_zalmy_velkonocna_nedela(short int modlitba) {
	Log("_set_zalmy_velkonocna_nedela(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		_set_zalmy_1nedele_v();
	}
	// aj na prvé vešpery druhej veľkonočnej nedele sú žalmy z (druhých) vešpier veľkonočnej nedele; (prvá) veľkonočná nedeľa nemá prvé vešpery
	// (Svätá sobota (Biela sobota) má svoje vešpery); pôvodne tu bolo: _set_zalmy_1nedele_1v();
	else if (modlitba == MODL_PRVE_VESPERY) {
		_set_zalmy_1nedele_v_pre_1v();
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		_set_zalmy_1nedele_pc();
	}
	else if ((je_modlitba_cez_den(modlitba)) && (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA))) {
		// na ostatné hodiny sa berie doplnková psalmódia
		_set_zalmy_1nedele_mcd();
	}
	Log("_set_zalmy_velkonocna_nedela(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_velkonocna_nedela()

void _set_zalmy_nanebovstupenie(short int modlitba) {
	Log("_set_zalmy_nanebovstupenie(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z110.htm", "ZALM110");
		set_zalm(2, modlitba, "z47.htm", "ZALM47");
		set_zalm(3, modlitba, "ch_zjv11.htm", "CHVAL_ZJV11");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z117.htm", "ZALM117");
		set_zalm(3, modlitba, "ch_zjv11.htm", "CHVAL_ZJV11");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z68.htm", "ZALM68_I");
		set_zalm(2, modlitba, "z68.htm", "ZALM68_II");
		set_zalm(3, modlitba, "z68.htm", "ZALM68_III");
	}
	else if ((je_modlitba_cez_den(modlitba)) && (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA))) {
		// na ostatné hodiny sa berie doplnková psalmódia
		set_zalm(1, modlitba, "z8.htm", "ZALM8");
		set_zalm(2, modlitba, "z19.htm", "ZALM19_I");
		set_zalm(3, modlitba, "z19.htm", "ZALM19_II");
	}
	Log("_set_zalmy_nanebovstupenie(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_nanebovstupenie()

void _set_zalmy_zoslanie_ducha_sv(short int modlitba) {
	Log("_set_zalmy_zoslanie_ducha_sv(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z110.htm", "ZALM110");
		set_zalm(2, modlitba, "z114.htm", "ZALM114");
		set_zalm(3, modlitba, "ch_zjv19.htm", "CHVAL_ZJV19");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z147.htm", "ZALM147,1-11");
		set_zalm(3, modlitba, "ch_zjv15.htm", "CHVAL_ZJV15");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z104.htm", "ZALM104_I");
		set_zalm(2, modlitba, "z104.htm", "ZALM104_II");
		set_zalm(3, modlitba, "z104.htm", "ZALM104_III");
	}
	else if ((je_modlitba_cez_den(modlitba)) && (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA))) {
		// na ostatné hodiny sa berie doplnková psalmódia
		_set_zalmy_1nedele_mcd();
	}
	Log("_set_zalmy_zoslanie_ducha_sv(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_zoslanie_ducha_sv()

void _set_zalmy_najsv_trojice(short int modlitba) {
	Log("_set_zalmy_najsv_trojice(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z110.htm", "ZALM110");
		set_zalm(2, modlitba, "z114.htm", "ZALM114");
		set_zalm(3, modlitba, "ch_zjv19.htm", "CHVAL_ZJV19");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z147.htm", "ZALM147,12-20");
		set_zalm(3, modlitba, "ch_ef1.htm", "CHVAL_EF1");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z8.htm", "ZALM8");
		set_zalm(2, modlitba, "z33.htm", "ZALM33_I");
		set_zalm(3, modlitba, "z33.htm", "ZALM33_II");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	else if ((je_modlitba_cez_den(modlitba)) && (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA))) {
		// na ostatné hodiny sa berie doplnková psalmódia
		_set_zalmy_1nedele_mcd();
	}
	Log("_set_zalmy_najsv_trojice(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_najsv_trojice()

void _set_zalmy_krista_krala(short int modlitba) {
	Log("_set_zalmy_krista_krala(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z110.htm", "ZALM110");
		set_zalm(2, modlitba, "z145.htm", "ZALM145,1-13");
		set_zalm(3, modlitba, "ch_zjv19.htm", "CHVAL_ZJV19");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z117.htm", "ZALM117");
		set_zalm(3, modlitba, "ch_zjv4_5.htm", "CHVAL_ZJV45");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z2.htm", "ZALM2");
		set_zalm(2, modlitba, "z72.htm", "ZALM72_I");
		set_zalm(3, modlitba, "z72.htm", "ZALM72_II");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	else if ((je_modlitba_cez_den(modlitba)) && (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA))) {
		// na ostatné hodiny sa berie doplnková psalmódia
		_set_zalmy_1nedele_mcd();
	}
	Log("_set_zalmy_krista_krala(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_krista_krala()

void _set_zalmy_telakrvi(short int modlitba) {
	Log("_set_zalmy_telakrvi(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z110.htm", "ZALM110");
		set_zalm(2, modlitba, "z116.htm", "ZALM116,10-19");
		set_zalm(3, modlitba, "ch_zjv19.htm", "CHVAL_ZJV19");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z111.htm", "ZALM111");
		set_zalm(2, modlitba, "z147.htm", "ZALM147,12-20");
		set_zalm(3, modlitba, "ch_zjv11.htm", "CHVAL_ZJV11");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z23.htm", "ZALM23");
		set_zalm(2, modlitba, "z42.htm", "ZALM42");
		set_zalm(3, modlitba, "z81.htm", "ZALM81");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	// "Doplnková psalmódia. Keď sa slávnosť koná v nedeľu, žalmy sa berú z nedele prvého týždňa." SK LH, zv. III, str. 618
	else if (je_modlitba_cez_den(modlitba)) {
		_set_zalmy_mcd_1nedela_or_doplnkova_psalmodia();
	}
	Log("_set_zalmy_telakrvi(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_telakrvi()

void _set_zalmy_srdca(short int modlitba) {
	Log("_set_zalmy_srdca(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z110.htm", "ZALM110");
		set_zalm(2, modlitba, "z111.htm", "ZALM111");
		set_zalm(3, modlitba, "ch_flp2.htm", "CHVAL_FLP2");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z146.htm", "ZALM146");
		set_zalm(3, modlitba, "ch_zjv4_5.htm", "CHVAL_ZJV45");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z36.htm", "ZALM36");
		set_zalm(2, modlitba, "z61.htm", "ZALM61");
		set_zalm(3, modlitba, "z98.htm", "ZALM98");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	else if (je_modlitba_cez_den(modlitba)) {
		_set_zalmy_mcd_1nedela_or_doplnkova_psalmodia();
	}
	Log("_set_zalmy_srdca(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_srdca()

void _set_zalmy_knaza(short int modlitba) {
	Log("_set_zalmy_knaza(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z110.htm", "ZALM110");
		set_zalm(2, modlitba, "z111.htm", "ZALM111");
		set_zalm(3, modlitba, "ch_kol1.htm", "CHVAL_KOL1");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z2.htm", "ZALM2");
		set_zalm(2, modlitba, "z40.htm", "ZALM40,2-9");
		set_zalm(3, modlitba, "z85.htm", "ZALM85");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_knaza(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_knaza()

void _set_zalmy_narodenie(short int modlitba) {
	Log("_set_zalmy_narodenie(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z110.htm", "ZALM110");
		set_zalm(2, modlitba, "z130.htm", "ZALM130");
		set_zalm(3, modlitba, "ch_kol1.htm", "CHVAL_KOL1");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z147.htm", "ZALM147,12-20");
		set_zalm(3, modlitba, "ch_flp2.htm", "CHVAL_FLP2");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z2.htm", "ZALM2");
		set_zalm(2, modlitba, "z19.htm", "ZALM19,2-7");
		set_zalm(3, modlitba, "z45.htm", "ZALM45");
	}
	else if ((je_modlitba_cez_den(modlitba)) && (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA))) {
		// na ostatné hodiny sa berie doplnková psalmódia
		set_zalm(1, modlitba, "z19.htm", "ZALM19,8-15");
		set_zalm(2, modlitba, "z47.htm", "ZALM47");
		set_zalm(3, modlitba, "z48.htm", "ZALM48");
	}
	Log("_set_zalmy_narodenie(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_narodenie()

void _set_zalmy_zjv(short int modlitba) {
	Log("_set_zalmy_zjv(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z110.htm", "ZALM110");
		set_zalm(2, modlitba, "z112.htm", "ZALM112");
		set_zalm(3, modlitba, "ch_zjv15.htm", "CHVAL_ZJV15");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z135.htm", "ZALM135_I");
		set_zalm(2, modlitba, "z135.htm", "ZALM135_II");
		set_zalm(3, modlitba, "ch_1tim3.htm", "CHVAL_1TIM3");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z72.htm", "ZALM72");
		set_zalm(2, modlitba, "z96.htm", "ZALM96");
		set_zalm(3, modlitba, "z97.htm", "ZALM97");
	}
	else if ((je_modlitba_cez_den(modlitba)) && (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA))) {
		// na ostatné hodiny sa berie doplnková psalmódia
		set_zalm(1, modlitba, "z47.htm", "ZALM47");
		set_zalm(2, modlitba, "z86.htm", "ZALM86,1-10");
		set_zalm(3, modlitba, "z98.htm", "ZALM98");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_zjv(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_zjv()

void _set_zalmy_premenenie(short int modlitba) {
	Log("_set_zalmy_premenenie(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z110.htm", "ZALM110");
		set_zalm(2, modlitba, "z121.htm", "ZALM121");
		set_zalm(3, modlitba, "ch_1tim3.htm", "CHVAL_1TIM3");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z117.htm", "ZALM117");
		set_zalm(3, modlitba, "ch_zjv19.htm", "CHVAL_ZJV19");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z84.htm", "ZALM84");
		set_zalm(2, modlitba, "z97.htm", "ZALM97");
		set_zalm(3, modlitba, "z99.htm", "ZALM99");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	// modlitba cez deň: žalmy sú z bežného dňa
	Log("_set_zalmy_premenenie(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_premenenie()

void _set_zalmy_sviatok_apostolov(short int modlitba) {
	Log("_set_zalmy_sviatok_apostolov(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z116.htm", "ZALM116,10-19");
		set_zalm(2, modlitba, "z126.htm", "ZALM126");
		set_zalm(3, modlitba, "ch_ef1.htm", "CHVAL_EF1");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z117.htm", "ZALM117");
		set_zalm(2, modlitba, "z147.htm", "ZALM147,12-20");
		set_zalm(3, modlitba, "ch_ef1.htm", "CHVAL_EF1");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z19.htm", "ZALM19,2-7");
		set_zalm(2, modlitba, "z64.htm", "ZALM64");
		set_zalm(3, modlitba, "z97.htm", "ZALM97");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	else if (je_modlitba_cez_den(modlitba)) {
		_set_zalmy_mcd_doplnkova_psalmodia(!je_len_doplnkova_psalmodia(modlitba)); // toto je potrebné z technického dôvodu, pretože doplnková psalmódia bola nastavená ešte pri nastavovaní žaltára (pred vlastnými časťami svätých)
	}
	_set_mcd_doplnkova_psalmodia_z126_129(MODL_POPOLUDNI); // vyňaté mimo konkrétnej modlitby
	Log("_set_zalmy_sviatok_apostolov(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_sviatok_apostolov()

void _set_zalmy_sviatok_duch_past(short int modlitba) {
	Log("_set_zalmy_sviatok_duch_past(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z15.htm", "ZALM15");
		set_zalm(2, modlitba, "z112.htm", "ZALM112");
		set_zalm(3, modlitba, "ch_zjv15.htm", "CHVAL_ZJV15");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z146.htm", "ZALM146");
		set_zalm(3, modlitba, "ch_ef1.htm", "CHVAL_EF1");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z21.htm", "ZALM21");
		set_zalm(2, modlitba, "z92.htm", "ZALM92_I");
		set_zalm(3, modlitba, "z92.htm", "ZALM92_II");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_sviatok_duch_past(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_sviatok_duch_past()

void _set_zalmy_sviatok_panien(short int modlitba) {
	// používa sa aj pre sviatky svätých žien
	Log("_set_zalmy_sviatok_panien(%s) -- begin [používa sa aj pre sviatky svätých žien]\n", nazov_modlitby(modlitba));

	// pre MCD nastavíme info, že v predpísanej psalmódii môže dôjsť k opakovaniu žalmov, a preto je možnosť alternatívy (vyňaté mimo konkrétnej modlitby)
	_set_mcd_doplnkova_psalmodia_z122_129(MODL_PREDPOLUDNIM);
	_set_mcd_doplnkova_psalmodia_z127_131(MODL_POPOLUDNI);

	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z122.htm", "ZALM122");
		set_zalm(2, modlitba, "z127.htm", "ZALM127");
		set_zalm(3, modlitba, "ch_ef1.htm", "CHVAL_EF1");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z147.htm", "ZALM147,12-20");
		set_zalm(3, modlitba, "ch_ef1.htm", "CHVAL_EF1");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z19.htm", "ZALM19,2-7");
		set_zalm(2, modlitba, "z45.htm", "ZALM45_I");
		set_zalm(3, modlitba, "z45.htm", "ZALM45_II");
	}
	else if (je_modlitba_cez_den(modlitba)) {
		_set_zalmy_mcd_doplnkova_psalmodia(!je_len_doplnkova_psalmodia(modlitba)); // toto je potrebné z technického dôvodu, pretože doplnková psalmódia bola nastavená ešte pri nastavovaní žaltára (pred vlastnými časťami svätých)
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}

	Log("_set_zalmy_sviatok_panien(%s) -- end [používa sa aj pre sviatky svätých žien]\n", nazov_modlitby(modlitba));
} // _set_zalmy_sviatok_panien()

// Sviatky Panny Márie majú pre ranné chvály a vešpery rovnaké žalmy ako sviatky panien, ale pre posvätné čítania sú iné žalmy.
void _set_zalmy_sviatok_marie(short int modlitba) {
	Log("_set_zalmy_sviatok_marie(%s) -- begin\n", nazov_modlitby(modlitba));

	// pre MCD nastavíme info, že v predpísanej psalmódii môže dôjsť k opakovaniu žalmov, a preto je možnosť alternatívy (vyňaté mimo konkrétnej modlitby)
	_set_mcd_doplnkova_psalmodia_z122_129(MODL_PREDPOLUDNIM);
	_set_mcd_doplnkova_psalmodia_z127_131(MODL_POPOLUDNI);

	if ((modlitba == MODL_VESPERY) || (modlitba == MODL_PRVE_VESPERY)) {
		_set_zalmy_sviatok_panien(modlitba);
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		// 2011-09-06: možnosť zvoliť žalm 95
		if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALM95)) {
			set_zalm(1, modlitba, "z95.htm", "ZALM95");
		}
		else {
			set_zalm(1, modlitba, "z24.htm", "ZALM24");
		}
		set_zalm(2, modlitba, "z46.htm", "ZALM46");
		set_zalm(3, modlitba, "z87.htm", "ZALM87");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}

	Log("_set_zalmy_sviatok_marie(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_sviatok_marie()

// Sviatok sv. Jána apoštola-evanjelistu má pre posvätné čítania sú iné žalmy (namiesto 3. žalmu 97 má Ž 99)
void _set_zalmy_sviatok_jana_ap(short int modlitba) {
	Log("_set_zalmy_sviatok_jana_ap(%s) -- begin\n", nazov_modlitby(modlitba));
	// nemá ani prvé vešpery, ani "normálne" vešpery
	if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z19.htm", "ZALM19,2-7");
		set_zalm(2, modlitba, "z64.htm", "ZALM64");
		set_zalm(3, modlitba, "z99.htm", "ZALM99");
	}
	Log("_set_zalmy_sviatok_jana_ap(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_sviatok_jana_ap()

void _set_zalmy_sviatok_muc(short int modlitba) {
	Log("_set_zalmy_sviatok_muc(%s) (pre jedného mučeníka resp. spoločné) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z116.htm", "ZALM116,1-9");
		set_zalm(2, modlitba, "z116.htm", "ZALM116,10-19");
		set_zalm(3, modlitba, "ch_zjv4_5.htm", "CHVAL_ZJV45");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z118.htm", "ZALM118_muc_I");
		set_zalm(2, modlitba, "z118.htm", "ZALM118_muc_II");
		set_zalm(3, modlitba, "ch_1pt2.htm", "CHVAL_1PT2");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z2.htm", "ZALM2");
		// viacero muč.:  ZALM33_I, ZALM33_2 - riešení osobitne
		// jeden mučeník: ZALM11, ZALM17
		set_zalm(2, modlitba, "z11.htm", "ZALM11");
		set_zalm(3, modlitba, "z17.htm", "ZALM17");
	}
	Log("_set_zalmy_sviatok_muc(%s) (pre jedného mučeníka resp. spoločné) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_sviatok_muc()

// odlišné žalmy pre jedného resp. viacerých mučeníkov
void _set_zalmy_sviatok_muc(short int modlitba, short int su_viaceri) {
	Log("_set_zalmy_sviatok_muc(%s) (pre viacerých mučeníkov) -- begin\n", nazov_modlitby(modlitba));
	_set_zalmy_sviatok_muc(modlitba);
	if ((su_viaceri > 0) && (modlitba == MODL_POSV_CITANIE)) {
		// viacero muč.:  ZALM33_I, ZALM33_2
		// jeden mučeník: ZALM11, ZALM17 - riešený vyššie
		set_zalm(2, modlitba, "z33.htm", "ZALM33_I");
		set_zalm(3, modlitba, "z33.htm", "ZALM33_II");
	}
	Log("_set_zalmy_sviatok_muc(%s) (pre viacerých mučeníkov) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_sviatok_muc()

void _set_zalmy_sviatok_krstu(short int modlitba) {
	Log("_set_zalmy_sviatok_krstu(%s) -- begin\n", nazov_modlitby(modlitba));
	// prvé vešpery a vešpery sú rovnaké ako na sviatok Zjavenia Pána
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z110.htm", "ZALM110");
		set_zalm(2, modlitba, "z112.htm", "ZALM112");
		set_zalm(3, modlitba, "ch_zjv15.htm", "CHVAL_ZJV15");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z135.htm", "ZALM135_I");
		set_zalm(2, modlitba, "z135.htm", "ZALM135_II");
		set_zalm(3, modlitba, "ch_1tim3.htm", "CHVAL_1TIM3");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z29.htm", "ZALM29");
		set_zalm(2, modlitba, "z66.htm", "ZALM66_I");
		set_zalm(3, modlitba, "z66.htm", "ZALM66_II");
	}
	// pre mcd žalmy z nedele 2. týždňa (7.1.) alebo z nedele 3. týždňa podľa roka
	else if ((je_modlitba_cez_den(modlitba)) && (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA))) {
		// na ostatné hodiny sa berie doplnková psalmódia
		if (_global_den.denvr == 7) {
			// ak je to 7.1.
			_set_zalmy_2nedele_mcd();
		}
		else {
			// inak: z nedele 3. týždňa - rovnaké ako z nedele 1. týždňa
			_set_zalmy_1nedele_mcd();
		}
	}
	Log("_set_zalmy_sviatok_krstu(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_sviatok_krstu()

void _set_zalmy_sviatok_obetovania(short int modlitba) {
	Log("_set_zalmy_sviatok_obetovania(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z110.htm", "ZALM110");
		set_zalm(2, modlitba, "z130.htm", "ZALM130");
		set_zalm(3, modlitba, "ch_kol1.htm", "CHVAL_KOL1");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z2.htm", "ZALM2");
		set_zalm(2, modlitba, "z19.htm", "ZALM19,2-7");
		set_zalm(3, modlitba, "z45.htm", "ZALM45");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z147.htm", "ZALM147,12-20");
		set_zalm(3, modlitba, "ch_flp2.htm", "CHVAL_FLP2");
	}
	Log("_set_zalmy_sviatok_obetovania(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_sviatok_obetovania()

void _set_zalmy_slavnost_Cyrila_a_Metoda(short int modlitba) {
	Log("_set_zalmy_slavnost_Cyrila_a_Metoda(%s) -- begin\n", nazov_modlitby(modlitba));
	if ((modlitba == MODL_VESPERY) || (modlitba == MODL_PRVE_VESPERY)) {
		set_zalm(1, modlitba, "z117.htm", "ZALM117");
		set_zalm(2, modlitba, "z146.htm", "ZALM146");
		set_zalm(3, modlitba, "ch_ef1.htm", "CHVAL_EF1");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z19.htm", "ZALM19,2-7");
		set_zalm(2, modlitba, "z33.htm", "ZALM33_I");
		set_zalm(3, modlitba, "z33.htm", "ZALM33_II");
	}
	Log("_set_zalmy_slavnost_Cyrila_a_Metoda(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_slavnost_Cyrila_a_Metoda()

void _set_zalmy_sv_kriz(short int modlitba) {
	Log("_set_zalmy_sv_kriz(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z110.htm", "ZALM110");
		set_zalm(2, modlitba, "z116.htm", "ZALM116,10-19");
		set_zalm(3, modlitba, "ch_zjv4_5.htm", "CHVAL_ZJV45");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z147.htm", "ZALM147_I");
		set_zalm(2, modlitba, "z147.htm", "ZALM147_II");
		set_zalm(3, modlitba, "ch_flp2.htm", "CHVAL_FLP2");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z2.htm", "ZALM2");
		set_zalm(2, modlitba, "z8.htm", "ZALM8");
		set_zalm(3, modlitba, "z96.htm", "ZALM96");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_sv_kriz(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_sv_kriz()

void _set_zalmy_archanjelov(short int modlitba) {
	Log("_set_zalmy_archanjelov(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z8.htm", "ZALM8");
		set_zalm(2, modlitba, "z138.htm", "ZALM138");
		set_zalm(3, modlitba, "ch_kol1.htm", "CHVAL_KOL1");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z97.htm", "ZALM97");
		set_zalm(2, modlitba, "z103.htm", "ZALM103_I_ANJ");
		set_zalm(3, modlitba, "z103.htm", "ZALM103_II_ANJ");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_archanjelov(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_archanjelov()

void _set_zalmy_anjelov_strazcov(short int modlitba) {
	Log("_set_zalmy_anjelov_strazcov(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z34.htm", "ZALM34_I");
		set_zalm(2, modlitba, "z34.htm", "ZALM34_II");
		set_zalm(3, modlitba, "ch_zjv11.htm", "CHVAL_ZJV11");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_anjelov_strazcov(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_anjelov_strazcov()

void _set_zalmy_vsetkych_svatych(short int modlitba) {
	Log("_set_zalmy_vsetkych_svatych(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z110.htm", "ZALM110");
		set_zalm(2, modlitba, "z116.htm", "ZALM116,10-19");
		set_zalm(3, modlitba, "ch_zjv4_5.htm", "CHVAL_ZJV45");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z147.htm", "ZALM147,12-20");
		set_zalm(3, modlitba, "ch_zjv19.htm", "CHVAL_ZJV19");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z8.htm", "ZALM8");
		set_zalm(2, modlitba, "z15.htm", "ZALM15");
		set_zalm(3, modlitba, "z16.htm", "ZALM16");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_vsetkych_svatych(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_vsetkych_svatych()

// CZ OP
void _set_zalmy_najsv_mena_jezisovho_czop(short int modlitba) {
	Log("_set_zalmy_najsv_mena_jezisovho_czop(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z135.htm", "ZALM135_CELY");
		set_zalm(3, modlitba, "ch_flp2.htm", "CHVAL_FLP2");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_najsv_mena_jezisovho_czop(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_najsv_mena_jezisovho_czop()

// SK OFM
void _set_zalmy_najsv_mena_jezisovho_sk_ofm(short int modlitba) {
	Log("_set_zalmy_najsv_mena_jezisovho_sk_ofm(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z46.htm", "ZALM46");
		set_zalm(2, modlitba, "z116.htm", "ZALM116,10-19");
		set_zalm(3, modlitba, "ch_flp2.htm", "CHVAL_FLP2");
	}
	if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z8.htm", "ZALM8");
		if ((_global_jazyk == JAZYK_CZ) && ((_global_kalendar == KALENDAR_CZ_OFMCAP) || (_global_kalendar == KALENDAR_CZ_OFM) || (_global_kalendar == KALENDAR_CZ_OFMCONV))) {
			set_zalm(2, modlitba, "z19.htm", "ZALM19");
		}
		else {
			set_zalm(2, modlitba, "z19.htm", "ZALM19,2-7");
		}
		// 2011-09-06: možnosť zvoliť žalm 95
		if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALM95)) {
			set_zalm(3, modlitba, "z95.htm", "ZALM95");
		}
		else {
			set_zalm(3, modlitba, "z24.htm", "ZALM24");
		}
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_najsv_mena_jezisovho_sk_ofm(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_najsv_mena_jezisovho_sk_ofm()

// SK CSsR; hlavný titul kongregácie
void _set_zalmy_cssr_titul(short int modlitba) {
	Log("_set_zalmy_cssr_titul(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z111.htm", "ZALM111");
		set_zalm(2, modlitba, "z138.htm", "ZALM138");
		set_zalm(3, modlitba, "ch_kol1.htm", "CHVAL_KOL1");
	}
	else if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z116.htm", "ZALM116,10-19");
		set_zalm(2, modlitba, "z130.htm", "ZALM130");
		set_zalm(3, modlitba, "ch_zjv4_5.htm", "CHVAL_ZJV45");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z8.htm", "ZALM8");
		set_zalm(2, modlitba, "z145.htm", "ZALM145_I");
		set_zalm(3, modlitba, "z145.htm", "ZALM145_II");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_cssr_titul(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_cssr_titul()

// SK CSA (24APR)
void _set_zalmy_csa_augustin_obr(short int modlitba) {
	Log("_set_zalmy_csa_augustin_obr(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z112.htm", "ZALM112");
		set_zalm(2, modlitba, "z130.htm", "ZALM130");
		set_zalm(3, modlitba, "ch_kol1.htm", "CHVAL_KOL1");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z139.htm", "ZALM139");
		set_zalm(2, modlitba, "z141.htm", "ZALM141");
		set_zalm(3, modlitba, "z16.htm", "ZALM16");
	}
	Log("_set_zalmy_csa_augustin_obr(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_csa_augustin_obr()

// SK CSA (28AUG)
void _set_zalmy_csa_augustin(short int modlitba) {
	Log("_set_zalmy_csa_augustin(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z15.htm", "ZALM15");
		set_zalm(2, modlitba, "z112.htm", "ZALM112");
		set_zalm(3, modlitba, "ch_zjv15.htm", "CHVAL_ZJV15");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z71.htm", "ZALM71,9-19");
		set_zalm(2, modlitba, "z32.htm", "ZALM32");
		set_zalm(3, modlitba, "ch_zjv15.htm", "CHVAL_ZJV15");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z27.htm", "ZALM27");
		set_zalm(2, modlitba, "z34.htm", "ZALM34");
		set_zalm(3, modlitba, "z133.htm", "ZALM133");
	}
	else if ((modlitba == MODL_PREDPOLUDNIM) || (modlitba == MODL_NAPOLUDNIE) || (modlitba == MODL_POPOLUDNI)) {
		set_zalm(1, modlitba, "z8.htm", "ZALM8");
		set_zalm(2, modlitba, "z19.htm", "ZALM19,2-7");
		set_zalm(3, modlitba, "z19.htm", "ZALM19,8-15");
	}
	Log("_set_zalmy_csa_augustin(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_csa_augustin()

// SK SJ (31JUL)
void _set_zalmy_sj_ignac(short int modlitba) {
	Log("_set_zalmy_sj_ignac(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z117.htm", "ZALM117");
		set_zalm(2, modlitba, "z27.htm", "ZALM27,1-6");
		set_zalm(3, modlitba, "ch_ef1.htm", "CHVAL_EF1");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z147.htm", "ZALM147,1-11");
		set_zalm(3, modlitba, "ch_kol1.htm", "CHVAL_KOL1");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z110.htm", "ZALM110");
		set_zalm(2, modlitba, "z47.htm", "ZALM47");
		set_zalm(3, modlitba, "z145.htm", "ZALM145,1-13");
	}
	Log("_set_zalmy_sj_ignac(%s) -- end\n", nazov_modlitby(modlitba));
} // _set_zalmy_sj_ignac()

// SK SJ (05NOV)
void _set_zalmy_sj_vsetkych_svatych(short int modlitba) {
	Log("_set_zalmy_sj_vsetkych_svatych(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z112.htm", "ZALM112");
		set_zalm(3, modlitba, "ch_zjv4_5.htm", "CHVAL_ZJV45");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z22.htm", "ZALM22,24-32");
		set_zalm(2, modlitba, "z70.htm", "ZALM70");
		set_zalm(3, modlitba, "z15.htm", "ZALM15");
	}
	Log("_set_zalmy_sj_vsetkych_svatych(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_sj_vsetkych_svatych()

// SK SJ (03DEC)
void _set_zalmy_sj_xaver(short int modlitba) {
	Log("_set_zalmy_sj_xaver(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z84.htm", "ZALM84");
		set_zalm(3, modlitba, "ch_ef1.htm", "CHVAL_EF1");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z19.htm", "ZALM19,2-7");
		set_zalm(2, modlitba, "z97.htm", "ZALM97");
		set_zalm(3, modlitba, "z66.htm", "ZALM66,1-12");
	}
	Log("_set_zalmy_sj_xaver(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_sj_xaver()

 // SK OCD (20JUL)
void _set_zalmy_ocd_elias(short int modlitba){
	Log("_set_zalmy_ocd_elias(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY){
		set_zalm(1, modlitba, "z111.htm", "ZALM111");
		set_zalm(2, modlitba, "z115.htm", "ZALM115");
		set_zalm(3, modlitba, "ch_zjv11.htm", "CHVAL_ZJV11");
	}
	else if (modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	else if (modlitba == MODL_POSV_CITANIE){
		set_zalm(1, modlitba, "z11.htm", "ZALM11");
		set_zalm(2, modlitba, "z28.htm", "ZALM28,1-3.6-9");
		set_zalm(3, modlitba, "z30.htm", "ZALM30");
	}
	Log("_set_zalmy_ocd_elias(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_ocd_elias()

// CZ OP (08AUG)
void _set_zalmy_op_dominik(short int modlitba){
	Log("_set_zalmy_op_dominik(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY){
		set_zalm(1, modlitba, "z116.htm", "ZALM116,10-19");
		set_zalm(2, modlitba, "z126.htm", "ZALM126");
		set_zalm(3, modlitba, "ch_ef1.htm", "CHVAL_EF1");
	}
	else if (modlitba == MODL_PRVE_VESPERY){
		set_zalm(1, modlitba, "z96.htm", "ZALM96");
		set_zalm(2, modlitba, "z98.htm", "ZALM98");
		set_zalm(3, modlitba, "ch_ef1.htm", "CHVAL_EF1");
	}
	else if (modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	else if (modlitba == MODL_POSV_CITANIE){
		set_zalm(1, modlitba, "z42.htm", "ZALM42");
		set_zalm(2, modlitba, "z77.htm", "ZALM77");
		set_zalm(3, modlitba, "z145.htm", "ZALM145,1-9");
	}
	else if (je_modlitba_cez_den(modlitba)){
		if (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA)){
			set_zalm(1, modlitba, "z34.htm", "ZALM34_I");
			set_zalm(2, modlitba, "z34.htm", "ZALM34_II");
			set_zalm(3, modlitba, "z19.htm", "ZALM19,8-15");
		}
		_set_mcd_doplnkova_psalmodia_alternativy(modlitba);
	}
	Log("_set_zalmy_op_dominik(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_op_dominik()

// OFMCap. (08AUG)
void _set_zalmy_ofmcap_dominik(short int modlitba){
	Log("_set_zalmy_ofmcap_dominik(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY){ // ako _set_zalmy_sviatok_duch_past()
		set_zalm(1, modlitba, "z15.htm", "ZALM15");
		set_zalm(2, modlitba, "z112.htm", "ZALM112");
		set_zalm(3, modlitba, "ch_zjv15.htm", "CHVAL_ZJV15");
	}
	else if (modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	else if (modlitba == MODL_POSV_CITANIE){
		set_zalm(1, modlitba, "z1.htm", "ZALM1");
		set_zalm(2, modlitba, "z21.htm", "ZALM21");
		set_zalm(3, modlitba, "z24.htm", "ZALM24");
	}
	Log("_set_zalmy_ofmcap_dominik(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_ofmcap_dominik()

// SK OCD (01OKT)
void _set_zalmy_ocd_terezka(short int modlitba){
	Log("_set_zalmy_ocd_terezka(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY){
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z131.htm", "ZALM131");
		set_zalm(3, modlitba, "ch_flp2.htm", "CHVAL_FLP2");
	}
	else if (modlitba == MODL_POSV_CITANIE){
		set_zalm(1, modlitba, "z23.htm", "ZALM23");
		set_zalm(2, modlitba, "z103.htm", "ZALM103_I_OCD");
		set_zalm(3, modlitba, "z103.htm", "ZALM103_II_OCD");
	}
	else if (modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_ocd_terezka(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_ocd_terezka()

// SK OCD (15OKT)
void _set_zalmy_ocd_terezia(short int modlitba){
	Log("_set_zalmy_ocd_terezia(%s) -- begin\n", nazov_modlitby(modlitba));

	// pre MCD nastavíme info, že v predpísanej psalmódii môže dôjsť k opakovaniu žalmov, a preto je možnosť alternatívy (vyňaté mimo konkrétnej modlitby)
	_set_mcd_doplnkova_psalmodia_z122_129(MODL_PREDPOLUDNIM);
	_set_mcd_doplnkova_psalmodia_z127_131(MODL_POPOLUDNI);

	if (modlitba == MODL_VESPERY){
		set_zalm(1, modlitba, "z122.htm", "ZALM122");
		set_zalm(2, modlitba, "z127.htm", "ZALM127");
		set_zalm(3, modlitba, "ch_kol1.htm", "CHVAL_KOL1");
	}
	else if (modlitba == MODL_PRVE_VESPERY){
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z146.htm", "ZALM146");
		set_zalm(3, modlitba, "ch_ef1.htm", "CHVAL_EF1");
	}
	else if (modlitba == MODL_POSV_CITANIE){
		set_zalm(1, modlitba, "z42.htm", "ZALM42");
		set_zalm(2, modlitba, "z145.htm", "ZALM145_I");
		set_zalm(3, modlitba, "z145.htm", "ZALM145_II");
	}
	else if (modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	else if (je_modlitba_cez_den(modlitba)){
		_set_zalmy_mcd_doplnkova_psalmodia(!je_len_doplnkova_psalmodia(modlitba)); // toto je potrebné z technického dôvodu, pretože doplnková psalmódia bola nastavená ešte pri nastavovaní žaltára (pred vlastnými časťami svätých)
	}

	Log("_set_zalmy_ocd_terezia(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_ocd_terezia()

// SK OCD (14NOV)
void _set_zalmy_ocd_vsetci_svati(short int modlitba){
	Log("_set_zalmy_ocd_vsetci_svati(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY){
		set_zalm(1, modlitba, "z15.htm", "ZALM15");
		set_zalm(2, modlitba, "z112.htm", "ZALM112");
		set_zalm(3, modlitba, "ch_zjv4_5.htm", "CHVAL_ZJV45");
	}
	else if (modlitba == MODL_POSV_CITANIE){
		set_zalm(1, modlitba, "z1.htm", "ZALM1");
		set_zalm(2, modlitba, "z61.htm", "ZALM61");
		set_zalm(3, modlitba, "z84.htm", "ZALM84");
	}
	else if (modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	Log("_set_zalmy_ocd_vsetci_svati(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_ocd_vsetci_svati()

// SK OCD (14DEC)
void _set_zalmy_ocd_jan_z_kriza(short int modlitba) {
	Log("_set_zalmy_ocd_jan_z_kriza(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z15.htm", "ZALM15");
		set_zalm(2, modlitba, "z112.htm", "ZALM112");
		set_zalm(3, modlitba, "ch_ef1.htm", "CHVAL_EF1");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z146.htm", "ZALM146");
		set_zalm(3, modlitba, "ch_zjv4_5.htm", "CHVAL_ZJV45");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z16.htm", "ZALM16");
		set_zalm(2, modlitba, "z34.htm", "ZALM34_I");
		set_zalm(3, modlitba, "z34.htm", "ZALM34_II");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	else if (je_modlitba_cez_den(modlitba)) {
		_set_zalmy_mcd_doplnkova_psalmodia(!je_len_doplnkova_psalmodia(modlitba)); // toto je potrebné z technického dôvodu, pretože doplnková psalmódia bola nastavená ešte pri nastavovaní žaltára (pred vlastnými časťami svätých)
	}

	Log("_set_zalmy_ocd_jan_z_kriza(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_ocd_jan_z_kriza()

void _set_zalmy_op_utrpenie(short int modlitba) {
	Log("_set_zalmy_op_utrpenie(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z22.htm", "ZALM22,2-23");
		set_zalm(2, modlitba, "z22.htm", "ZALM22,24-32");
		set_zalm(3, modlitba, "ch_1pt2.htm", "CHVAL_1PT2");
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z69.htm", "ZALM69,2-13");
		set_zalm(2, modlitba, "z69.htm", "ZALM69,14-22.30-37");
		set_zalm(3, modlitba, "z88.htm", "ZALM88");
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		set_zalm(1, modlitba, "z57.htm", "ZALM57");
		set_zalm(2, modlitba, "ch_iz12.htm", "CHVAL_IZ12");
		set_zalm(3, modlitba, "z147.htm", "ZALM147,12-20");
	}
	else if (modlitba == MODL_NAPOLUDNIE) {
		set_zalm(1, modlitba, "z40.htm", "ZALM40_I");
		set_zalm(2, modlitba, "z40.htm", "ZALM40_II");
		set_zalm(3, modlitba, "z54.htm", "ZALM54");
	}

	Log("_set_zalmy_op_utrpenie(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_op_utrpenie()

 // CZ OP (04OKT), používa ich aj 07NOV pre CZOP; používa ich aj sv. František (04OKT pre OFM)
void _set_zalmy_pc_1_8_16(short int modlitba){
	Log("_set_zalmy_pc_1_8_16(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_POSV_CITANIE){
		set_zalm(1, modlitba, "z1.htm", "ZALM1");
		set_zalm(2, modlitba, "z8.htm", "ZALM8");
		set_zalm(3, modlitba, "z16.htm", "ZALM16");
	}
	Log("_set_zalmy_pc_1_8_16(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_pc_1_8_16()

void _set_zalmy_pc_1_8_15(short int modlitba){
	Log("_set_zalmy_pc_1_8_15(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_POSV_CITANIE){
		set_zalm(1, modlitba, "z1.htm", "ZALM1");
		set_zalm(2, modlitba, "z8.htm", "ZALM8");
		set_zalm(3, modlitba, "z15.htm", "ZALM15");
	}
	Log("_set_zalmy_pc_1_8_15(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_pc_1_8_15()

// OPRAEM (10FEB)
void _set_zalmy_opraem_pc_1_8_21(short int modlitba){
	Log("_set_zalmy_opraem_pc_1_8_21(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_POSV_CITANIE){
		set_zalm(1, modlitba, "z1.htm", "ZALM1");
		set_zalm(2, modlitba, "z8.htm", "ZALM8");
		set_zalm(3, modlitba, "z21.htm", "ZALM21");
	}
	Log("_set_zalmy_opraem_pc_1_8_21(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_opraem_pc_1_8_21()

// OPRAEM (02MAJ)
void _set_zalmy_opraem_pc_1_8_24(short int modlitba) {
	Log("_set_zalmy_opraem_pc_1_8_24(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z1.htm", "ZALM1");
		set_zalm(2, modlitba, "z8.htm", "ZALM8");
		set_zalm(3, modlitba, "z24.htm", "ZALM24");
	}
	Log("_set_zalmy_opraem_pc_1_8_24(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_opraem_pc_1_8_24()

// CM (27SEP)
void _set_zalmy_cm_pc_1_41_84(short int modlitba) {
	Log("_set_zalmy_cm_pc_1_41_84(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z1.htm", "ZALM1");
		set_zalm(2, modlitba, "z41.htm", "ZALM41");
		set_zalm(3, modlitba, "z84.htm", "ZALM84");
	}
	Log("_set_zalmy_cm_pc_1_41_84(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_cm_pc_1_41_84()

// OFM (18MAJ)
void _set_zalmy_pc_1_12_24(short int modlitba){
	Log("_set_zalmy_pc_1_12_24(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_POSV_CITANIE){
		set_zalm(1, modlitba, "z1.htm", "ZALM1");
		set_zalm(2, modlitba, "z12.htm", "ZALM12");
		// možnosť zvoliť žalm 95
		if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALM95)){
			set_zalm(3, modlitba, "z95.htm", "ZALM95");
		}
		else{
			set_zalm(3, modlitba, "z24.htm", "ZALM24");
		}
	}
	Log("_set_zalmy_pc_1_12_24(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_pc_1_12_24()

// SK OP (07NOV)
void _set_zalmy_pc_15_66(short int modlitba){
	Log("_set_zalmy_pc_15_66(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_POSV_CITANIE){
		set_zalm(1, modlitba, "z15.htm", "ZALM15");
		set_zalm(2, modlitba, "z66.htm", "ZALM66_I");
		set_zalm(3, modlitba, "z66.htm", "ZALM66_II");
	}
	Log("_set_zalmy_pc_15_66(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_pc_15_66()

// SK OP (29APR)
void _set_zalmy_op_29apr(short int modlitba) {
	Log("_set_zalmy_op_29apr(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z138.htm", "ZALM138_OP");
		set_zalm(2, modlitba, "z25.htm", "ZALM25_CELY");
		set_zalm(3, modlitba, "z67.htm", "ZALM67_OP");
	}
	else if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z31.htm", "ZALM31,20-25");
		set_zalm(2, modlitba, "z84.htm", "ZALM84_OP");
		set_zalm(3, modlitba, "ch_zjv4_5.htm", "CHVAL_ZJV45");
	}
	Log("_set_zalmy_op_29apr(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_op_29apr()

// SK+CZ OP (28JAN)
void _set_zalmy_pc_40_27(short int modlitba) {
	Log("_set_zalmy_pc_40_27(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z40.htm", "ZALM40_I");
		set_zalm(2, modlitba, "z40.htm", "ZALM40_II");
		set_zalm(3, modlitba, "z27.htm", "ZALM27,1-6");
	}
	Log("_set_zalmy_pc_40_27(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_pc_40_27()

/*
void _set_zalmy_pc_1_21_92(short int modlitba) {
	Log("_set_zalmy_pc_1_21_92(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z1.htm", "ZALM1");
		set_zalm(2, modlitba, "z21.htm", "ZALM21");
		set_zalm(3, modlitba, "z92.htm", "ZALM92");
	}
	Log("_set_zalmy_pc_1_21_92(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_pc_1_21_92()
*/

// HU 05NOV
void _set_zalmy_pc_24_61_84(short int modlitba) {
	Log("_set_zalmy_pc_24_61_84(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z24.htm", "ZALM24");
		set_zalm(2, modlitba, "z61.htm", "ZALM61");
		set_zalm(3, modlitba, "z84.htm", "ZALM84");
	}
	Log("_set_zalmy_pc_24_61_84(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_pc_24_61_84()

// HU OFM (19NOV)
void _set_zalmy_pc_45_87(short int modlitba){
	Log("_set_zalmy_pc_45_87(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_POSV_CITANIE){
		set_zalm(1, modlitba, "z45.htm", "ZALM45_I");
		set_zalm(2, modlitba, "z45.htm", "ZALM45_II");
		set_zalm(3, modlitba, "z87.htm", "ZALM87");
	}
	Log("_set_zalmy_pc_45_87(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_pc_45_87()

// CZOP (07NOV)
void _set_zalmy_vesp_110_116_ef(short int modlitba) {
	Log("_set_zalmy_vesp_110_116_ef(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z110.htm", "ZALM110");
		set_zalm(2, modlitba, "z116.htm", "ZALM116,10-19");
		set_zalm(3, modlitba, "ch_ef1.htm", "CHVAL_EF1");
	}
	Log("_set_zalmy_vesp_110_116_ef(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_vesp_110_116_ef()

 // SK OFM (21JUL)
void _set_zalmy_vesp_110_122_zjv15(short int modlitba) {
	Log("_set_zalmy_vesp_110_122_zjv15(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z110.htm", "ZALM110");
		set_zalm(2, modlitba, "z122.htm", "ZALM122");
		set_zalm(3, modlitba, "ch_zjv15.htm", "CHVAL_ZJV15");
	}
	Log("_set_zalmy_vesp_110_122_zjv15(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_vesp_110_122_zjv15()

// SK OP (07NOV)
void _set_zalmy_vesp_89_98_kol(short int modlitba){
	Log("_set_zalmy_vesp_89_98_kol(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY){
		set_zalm(1, modlitba, "z89.htm", "ZALM89,2-19");
		set_zalm(2, modlitba, "z98.htm", "ZALM98");
		set_zalm(3, modlitba, "ch_kol1.htm", "CHVAL_KOL1");
	}
	Log("_set_zalmy_vesp_89_98_kol(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_vesp_89_98_kol()

// HU OFM (18MAJ)
void _set_zalmy_vesp_113_146_ef(short int modlitba){
	Log("_set_zalmy_vesp_113_146_ef(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY){
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z146.htm", "ZALM146");
		set_zalm(3, modlitba, "ch_ef1.htm", "CHVAL_EF1");
	}
	Log("_set_zalmy_vesp_113_146_ef(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_vesp_113_146_ef()

// OSU (27JAN)
void _set_zalmy_osu_angela_merici(short int modlitba) {
	Log("_set_zalmy_osu_angela_merici(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_POSV_CITANIE) {
		set_zalm(1, modlitba, "z19.htm", "ZALM19,8-15");
		set_zalm(2, modlitba, "z45.htm", "ZALM45_I");
		set_zalm(3, modlitba, "z45.htm", "ZALM45_II");
	}
	else if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z110.htm", "ZALM110");
		set_zalm(2, modlitba, "z122.htm", "ZALM122");
		set_zalm(3, modlitba, "ch_zjv19.htm", "CHVAL_ZJV19");
	}
	Log("_set_zalmy_osu_angela_merici(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_osu_angela_merici()

// CZ OFMCAP (11AUG); CZ OP (28JAN)
void _set_zalmy_vesp_127_111_kol(short int modlitba){
	Log("_set_zalmy_vesp_127_111_kol(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY){
		set_zalm(1, modlitba, "z127.htm", "ZALM127");
		set_zalm(2, modlitba, "z111.htm", "ZALM111");
		set_zalm(3, modlitba, "ch_kol1.htm", "CHVAL_KOL1");
	}
	Log("_set_zalmy_vesp_127_111_kol(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_vesp_127_111_kol()

// OFM (04OKT)
void _set_zalmy_ofm_frantisek(short int modlitba) {
	Log("_set_zalmy_ofm_frantisek(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY) {
		set_zalm(1, modlitba, "z113.htm", "ZALM113");
		set_zalm(2, modlitba, "z146.htm", "ZALM146");
		set_zalm(3, modlitba, "ch_ef1.htm", "CHVAL_EF1");
	}
	else if (modlitba == MODL_PRVE_VESPERY) {
		set_zalm(1, modlitba, "z112.htm", "ZALM112");
		set_zalm(2, modlitba, "z147.htm", "ZALM147,12-20");
		set_zalm(3, modlitba, "z142.htm", "ZALM142"); // !!! sic, p. 512
	}
	else if (modlitba == MODL_RANNE_CHVALY) {
		_set_zalmy_1nedele_rch();
	}
	else if (modlitba == MODL_POSV_CITANIE) {
		if (_global_jazyk == JAZYK_CZ) {
			_set_zalmy_pc_1_8_15(modlitba); // Žl 15 (14) (CZ)
		}
		else {
			_set_zalmy_pc_1_8_16(modlitba); // Ž 16 (SK, HU)
		}
	}
	Log("_set_zalmy_ofm_frantisek(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_ofm_frantisek()

// OFM, 24APR; podľa _set_zalmy_sviatok_muc();
void _set_zalmy_sviatok_muc_ofm(short int modlitba){
	Log("_set_zalmy_sviatok_muc_ofm(%s) -- begin\n", nazov_modlitby(modlitba));
	if (modlitba == MODL_VESPERY){
		set_zalm(1, modlitba, "z116.htm", "ZALM116,1-9");
		set_zalm(2, modlitba, "z116.htm", "ZALM116,10-19");
		set_zalm(3, modlitba, "ch_zjv4_5.htm", "CHVAL_ZJV45");
	}
	else if (modlitba == MODL_PRVE_VESPERY){
		set_zalm(1, modlitba, "z118.htm", "ZALM118_muc_I");
		set_zalm(2, modlitba, "z118.htm", "ZALM118_muc_II");
		set_zalm(3, modlitba, "ch_1pt2.htm", "CHVAL_1PT2");
	}
	else if (modlitba == MODL_RANNE_CHVALY){
		_set_zalmy_1nedele_rch();
	}
	else if (modlitba == MODL_POSV_CITANIE){
		// posvätné čítanie
		set_zalm(1, modlitba, "z35.htm", "ZALM35_I");
		set_zalm(2, modlitba, "z35.htm", "ZALM35_II");
		set_zalm(3, modlitba, "z35.htm", "ZALM35_III");
	}
	Log("_set_zalmy_sviatok_muc_ofm(%s) -- end\n", nazov_modlitby(modlitba));
}// _set_zalmy_sviatok_muc_ofm()

void _set_zalmy_velk_oktava(short int den, short int modlitba){
	Log("_set_zalmy_velk_oktava(%d, %s) -- begin\n", den, nazov_modlitby(modlitba));
	if (modlitba == MODL_POSV_CITANIE){
		// posvätné čítanie
		switch (den){
		case DEN_NEDELA:
		case DEN_PONDELOK:
			set_zalm(1, modlitba, "z1.htm", "ZALM1");
			set_zalm(2, modlitba, "z2.htm", "ZALM2");
			set_zalm(3, modlitba, "z3.htm", "ZALM3");
			break;
		case DEN_UTOROK:
			// možnosť zvoliť žalm 95
			if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALM95)){
				set_zalm(1, modlitba, "z95.htm", "ZALM95");
			}
			else{
				set_zalm(1, modlitba, "z24.htm", "ZALM24");
			}
			set_zalm(2, modlitba, "z66.htm", "ZALM66_I");
			set_zalm(3, modlitba, "z66.htm", "ZALM66_II");
			break;
		case DEN_STREDA:
			set_zalm(1, modlitba, "z104.htm", "ZALM104_I");
			set_zalm(2, modlitba, "z104.htm", "ZALM104_II");
			set_zalm(3, modlitba, "z104.htm", "ZALM104_III");
			break;
		case DEN_STVRTOK:
			set_zalm(1, modlitba, "z118.htm", "ZALM118_I");
			set_zalm(2, modlitba, "z118.htm", "ZALM118_II");
			set_zalm(3, modlitba, "z118.htm", "ZALM118_III");
			break;
		case DEN_PIATOK:
			set_zalm(1, modlitba, "z136.htm", "ZALM136_I");
			set_zalm(2, modlitba, "z136.htm", "ZALM136_II_PC");
			set_zalm(3, modlitba, "z136.htm", "ZALM136_III_PC");
			break;
		case DEN_SOBOTA:
			_set_zalmy_pc_145(modlitba);
			break;
		} // switch(den)
	}
	else if ((je_modlitba_cez_den(modlitba)) && (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA))){
		// na ostatné hodiny sa berie doplnková psalmódia
		// modlitba cez deň
		switch (den){
		case DEN_NEDELA:
			set_zalm(1, MODL_CEZ_DEN_VSETKY, "z118.htm", "ZALM118_I");
			set_zalm(2, MODL_CEZ_DEN_VSETKY, "z118.htm", "ZALM118_II");
			set_zalm(3, MODL_CEZ_DEN_VSETKY, "z118.htm", "ZALM118_III");
			break;
		case DEN_PONDELOK:
			set_zalm(1, MODL_CEZ_DEN_VSETKY, "z8.htm", "ZALM8");
			set_zalm(2, MODL_CEZ_DEN_VSETKY, "z19.htm", "ZALM19_I");
			set_zalm(3, MODL_CEZ_DEN_VSETKY, "z19.htm", "ZALM19_II");
			break;
		case DEN_UTOROK:
			set_zalm(1, MODL_CEZ_DEN_VSETKY, "z119.htm", "ZALM119_ALEF");
			set_zalm(2, MODL_CEZ_DEN_VSETKY, "z16.htm", "ZALM16");
			set_zalm(3, MODL_CEZ_DEN_VSETKY, "z23.htm", "ZALM23");
			break;
		case DEN_STREDA:
			set_zalm(1, MODL_CEZ_DEN_VSETKY, "z119.htm", "ZALM119_BET");
			set_zalm(2, MODL_CEZ_DEN_VSETKY, "z28.htm", "ZALM28,1-3.6-9");
			set_zalm(3, MODL_CEZ_DEN_VSETKY, "z116.htm", "ZALM116,10-19");
			break;
		case DEN_STVRTOK:
			set_zalm(1, MODL_CEZ_DEN_VSETKY, "z119.htm", "ZALM119_GIMEL");
			set_zalm(2, MODL_CEZ_DEN_VSETKY, "z30.htm", "ZALM30_I");
			set_zalm(3, MODL_CEZ_DEN_VSETKY, "z30.htm", "ZALM30_II");
			break;
		case DEN_PIATOK:
			set_zalm(1, MODL_CEZ_DEN_VSETKY, "z119.htm", "ZALM119_DALET");
			set_zalm(2, MODL_CEZ_DEN_VSETKY, "z76.htm", "ZALM76_I");
			set_zalm(3, MODL_CEZ_DEN_VSETKY, "z76.htm", "ZALM76_II");
			break;
		case DEN_SOBOTA:
			set_zalm(1, MODL_CEZ_DEN_VSETKY, "z119.htm", "ZALM119_HE");
			set_zalm(2, MODL_CEZ_DEN_VSETKY, "z96.htm", "ZALM96_I");
			set_zalm(3, MODL_CEZ_DEN_VSETKY, "z96.htm", "ZALM96_II");
			break;
		} // switch(den)
	}
	Log("_set_zalmy_velk_oktava(%d, %s) -- end\n", den, nazov_modlitby(modlitba));
}// _set_zalmy_velk_oktava()

// žalmy pre posvätné čítania vianočnej oktávy okrem narodenia Pána
void _set_zalmy_vian_oktava(short int den, short int modlitba){
	Log("_set_zalmy_vian_oktava(%d, %s) -- begin\n", den, nazov_modlitby(modlitba));
	if (modlitba == MODL_POSV_CITANIE){
		// posvätné čítanie
		switch (den){
		case 25:
			set_zalm(1, modlitba, "z2.htm", "ZALM2");
			set_zalm(2, modlitba, "z19.htm", "ZALM19,2-7");
			set_zalm(3, modlitba, "z45.htm", "ZALM45");
			break;
		case 29:
			set_zalm(1, modlitba, "z46.htm", "ZALM46");
			set_zalm(2, modlitba, "z72.htm", "ZALM72_I");
			set_zalm(3, modlitba, "z72.htm", "ZALM72_II");
			break;
		case 30:
			set_zalm(1, modlitba, "z85.htm", "ZALM85");
			set_zalm(2, modlitba, "z89.htm", "ZALM89_I_30DEC");
			set_zalm(3, modlitba, "z89.htm", "ZALM89_II_30DEC");
			break;
		case 31:
			set_zalm(1, modlitba, "z96.htm", "ZALM96");
			set_zalm(2, modlitba, "z97.htm", "ZALM97");
			set_zalm(3, modlitba, "z98.htm", "ZALM98");
			break;
		case 1:
			// 2011-09-06: možnosť zvoliť žalm 95
			if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALM95)){
				set_zalm(1, modlitba, "z95.htm", "ZALM95");
			}
			else{
				set_zalm(1, modlitba, "z24.htm", "ZALM24");
			}
			set_zalm(2, modlitba, "z87.htm", "ZALM87");
			set_zalm(3, modlitba, "z99.htm", "ZALM99");
			break;
		} // switch(den)
	}
	Log("_set_zalmy_vian_oktava(%d, %s) -- end\n", den, nazov_modlitby(modlitba));
}// _set_zalmy_vian_oktava()

// pre Cezročné obdobie treba zrušiť možnosť brať alternatívy hymnov (I. resp. II.)
void _vlastne_slavenie_hymnus(short int modlitba, char vlastny_anchor[SMALL], short int litobd, short int pouzit_special_anchor /* = ANO */) {
	_set_hymnus_alternativy_NO(modlitba, litobd);
	if(pouzit_special_anchor == ANO){
		sprintf(_anchor, "%s%s_%c%s", _special_anchor_prefix, vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);
	}
	else{
		sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);
	}
	_set_hymnus(modlitba, _file, _anchor);
	set_LOG_litobd;
}// _vlastne_slavenie_hymnus()

void _velk1_hymnus(short int den, short int modlitba, short int litobd) {
	Log("_velk1_hymnus(): začiatok\n");
	short int ktory; // 0 alebo 1 (2 = obidve alternatívy; -1 = do not use this variable for generating anchor)
	short int bit = BIT_OPT_5_HYMNUS_VN_RCH; // necessary to initialize
	char _anchor_tmp[MAX_STR_AF_ANCHOR];
	short int je_nanebovstupenie = (_global_den.denvr == NANEBOVSTUPENIE || litobd < 0);

	if (je_nanebovstupenie == ANO) {
		mystrcpy(_anchor_tmp, ANCHOR_NANEBOVSTUPENIE, MAX_STR_AF_ANCHOR);
	}
	else {
		mystrcpy(_anchor_tmp, nazov_OBD[litobd], MAX_STR_AF_ANCHOR);
	}

	switch (modlitba) {
	case MODL_POSV_CITANIE: bit = BIT_OPT_5_HYMNUS_VN_PC; break;
	case MODL_RANNE_CHVALY: bit = BIT_OPT_5_HYMNUS_VN_RCH; break;
	case MODL_VESPERY:      bit = BIT_OPT_5_HYMNUS_VN_VESP; break;
	} // switch(modlitba)

	// do not use 'ktory' for CZ anchors at all; regardless of (je_CZ_hymny_k_volnemu_vyberu)
	if (_global_jazyk == JAZYK_CZ) {
		ktory = -1;
	}
	else if (je_modlitba_cez_den(modlitba)) {
		// pre vn1.htm je len jeden hymnus pre modlitbu cez deň; používa sa aj vo vn2.htm
		ktory = -1;
	}
	else if (je_nanebovstupenie == ANO){
		ktory = -1;
	}
	else if (den == DEN_NEDELA) {
		ktory = 1;
	}
	else if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES)) {
		// podľa nastavenia _global_opt[OPT_5_ALTERNATIVES]
		ktory = (isGlobalOption(OPT_5_ALTERNATIVES, (unsigned)bit)) ? 1 : 0;
		Log("_velk1_hymnus(): ktory == %d...\n", ktory);
	}
	else {
		// pôvodne bol náhodný výber
		ktory = 2; // obidva!
	}

	if (ktory < 0) {
		sprintf(_anchor, "%s%s_%c%s", _special_anchor_prefix, _anchor_tmp, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);
	}
	else {
		// upravené kotvy, aby bolo použiteľné zjednodušene toto:
		sprintf(_anchor, "%s%s_%c%s%d", _special_anchor_prefix, _anchor_tmp, pismenko_modlitby(modlitba), ANCHOR_HYMNUS, ktory);
	}

	if (modlitba == MODL_POSV_CITANIE) {
		_set_hymnus(modlitba, _file_pc, _anchor);
		set_LOG_litobd_pc;
	}
	else {
		_set_hymnus(modlitba, _file, _anchor);
		set_LOG_litobd;
	}
}// _velk1_hymnus()

void _obd_invitat_viac(short litobd, short modlitba) {
	short int ktory; // currently 0 or 1
	short int bit = BIT_ALT_ANT_INVITATORIUM;

	if (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ALTERNATIVES)) {
		// podľa nastavenia _global_opt[OPT_5_ALTERNATIVES]
		ktory = (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_INVITATORIUM_ANT)) ? 1 : 0;
		Log("_obd_invitat_viac(): ktory == %d...\n", ktory);

		_global_modl_invitatorium.alternativy += ((_global_modl_invitatorium.alternativy & bit) != bit) ? bit : 0;
	}
	else {
		// pôvodne bol náhodný výber
		ktory = 2; // obidva!
	}

	if (ktory < 2) {
		sprintf(_anchor, "%s_%c%s_%d", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1, ktory);
	}
	else {
		sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);
	}
	_set_antifona1(modlitba, _file, _anchor);
	set_LOG_litobd;
}// _obd_invitat_viac()

void _set_hymnus_alternativy_obdobie(short litobd, short len_kompletorium = NIE) {
	Log("_set_hymnus_alternativy_ocr(): začiatok...\n");

	if (litobd == OBD_CEZ_ROK) {
		Log("_set_hymnus_alternativy_ocr(): OBD_CEZ_ROK...\n");

		if ((_global_jazyk != JAZYK_CZ) || (je_CZ_hymny_k_volnemu_vyberu)) {
			Log("setting _set_hymnus_alternativy()...\n");

			_set_hymnus_alternativy(MODL_PRVE_KOMPLETORIUM);
			_set_hymnus_alternativy(MODL_KOMPLETORIUM);

			if (len_kompletorium == NIE) {
				_set_hymnus_alternativy(MODL_PREDPOLUDNIM);
				_set_hymnus_alternativy(MODL_NAPOLUDNIE);
				_set_hymnus_alternativy(MODL_POPOLUDNI);
				_set_hymnus_alternativy(MODL_POSV_CITANIE);
				_set_hymnus_alternativy(MODL_PRVE_VESPERY);
			}
		}
	}
	else {
		Log("_set_hymnus_alternativy_ocr(): nie je OBD_CEZ_ROK...\n");
	}

	Log("_set_hymnus_alternativy_ocr(): koniec.\n");
}// _set_hymnus_alternativy_ocr()

void slavnost_srdca(short int litobd /* = OBD_CEZ_ROK */) {
	Log("slavnost_srdca(): začiatok...\n");

	char _anchor_vlastne_slavenie[SMALL];

	// Najsv. Srdca Ježišovho
	mystrcpy(_file, FILE_SRDCA, MAX_STR_AF_FILE);
	mystrcpy(_file_pc, FILE_SRDCA, MAX_STR_AF_FILE); // kvôli define _vlastne_slavenie_set_vig_ant()
	mystrcpy(_anchor, ANCHOR_SRDCA, MAX_STR_AF_ANCHOR);
	mystrcpy(_anchor_vlastne_slavenie, ANCHOR_SRDCA, MAX_STR_AF_ANCHOR);
	Log("  ide o slávnosť Najsv. srdca Ježišovho: _file = `%s', _anchor = %s...\n", _file, _anchor);

	// kompletórium
	modlitba = MODL_PRVE_KOMPLETORIUM;
	_set_kompletorium_slavnost(modlitba);

	modlitba = MODL_KOMPLETORIUM;
	_set_kompletorium_slavnost(modlitba);

	// prvé vešpery
	modlitba = MODL_PRVE_VESPERY;
	_set_zalmy_srdca(modlitba);
	_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
	_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
	_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
	_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
	_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
	_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
	_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

	// invitatórium
	modlitba = MODL_INVITATORIUM;
	_vlastne_slavenie_invitat(_anchor_vlastne_slavenie);

	modlitba = MODL_RANNE_CHVALY;
	_set_zalmy_srdca(modlitba);
	_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
	_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
	_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
	_vlastne_slavenie_benediktus(_anchor_vlastne_slavenie);
	_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
	_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
	_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

	modlitba = MODL_VESPERY;
	_set_zalmy_srdca(modlitba);
	_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
	_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
	_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
	_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
	_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
	_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
	_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

	modlitba = MODL_POSV_CITANIE;
	_set_zalmy_srdca(modlitba);
	_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
	_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
	_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
	_vlastne_slavenie_1citanie(_anchor_vlastne_slavenie);
	_vlastne_slavenie_2citanie(_anchor_vlastne_slavenie);
	_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
	// posvätné čítanie -- predĺžené slávenie vigílie
	modlitba = MODL_POSV_CITANIE;
	_vlastne_slavenie_set_vig_ant(_anchor_vlastne_slavenie);
	_set_chvalospev_vig_srdca(modlitba);
	_vlastne_slavenie_set_vig_ev(_anchor_vlastne_slavenie);

	modlitba = MODL_PREDPOLUDNIM;
	_set_zalmy_srdca(modlitba);
	_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
	_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
	_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
	_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
	modlitba = MODL_NAPOLUDNIE;
	_set_zalmy_srdca(modlitba);
	_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
	_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
	_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
	_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
	modlitba = MODL_POPOLUDNI;
	_set_zalmy_srdca(modlitba);
	_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
	_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
	_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
	_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);

	Log("slavnost_srdca(): koniec.\n");
}

void liturgicke_obdobie(short int litobd, short int tyzden, short int den, short int tyzzal, short int poradie_svateho){
	short int modlitba, t, tyzden_pom, litobd_pom;
	char _anchor_vlastne_slavenie[SMALL];

	// uchovanie pôvodných hodnôt (občas sa upravujú)
	short int _pom_den = _global_den.den;
	short int _pom_mesiac = _global_den.mesiac;
	short int _pom_rok = _global_den.rok;

	short int skip_big_switch = NIE;

	Log("-- liturgicke_obdobie(%d, %d, %d, %d: svaty: %d) -- začiatok\n", litobd, tyzden, den, tyzzal, poradie_svateho);

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

	// najprv treba skontrolovat, ci nejde o sviatky Pana a svatych, ktore maju prednost pred nedelou -- SVIATKY_PANA_SVATYCH_PREDNOST
	// ak ano, tak nenastavuj nic, lebo vsetko sa nastavilo vo funkcii sviatky_svatych()
	Log("PODMIENKA_SVIATKY_PANA_SVATYCH_PREDNOST_PRED_NEDELOU_OCR: najprv treba skontrolovať, či nejde o deň [pôvodne nedeľu], na ktorú pripadol sviatok premenenia pána a podobné... (ak áno, nenastavuj nič)\n");

	if (PODMIENKA_SVIATKY_PANA_SVATYCH_PREDNOST_PRED_NEDELOU_OCR) {
		Log("PODMIENKA_SVIATKY_PANA_SVATYCH_PREDNOST_PRED_NEDELOU_OCR: BEGIN (napr. premenenie pána || obetovanie pána || petra a pavla || povýšenie sv. kríža || všetkých svätých || nanebovzatia PM)...\n");

		// pre sviatky Pána (svätých), ktoré padnú na nedeľu (a majú prednosť pred Cezročnou nedeľou), je potrebné nastaviť prvé aj druhé nedeľné kompletórium
		if ((_global_den.denvt == DEN_NEDELA) && (_global_svaty(1).smer >= 5)) {
			Log("pre sviatky Pána (svätých), ktoré padnú na nedeľu (a majú prednosť pred Cezročnou nedeľou), je potrebné nastaviť prvé aj druhé nedeľné kompletórium...\n");
			_set_kompletorium_nedela(MODL_PRVE_KOMPLETORIUM);
			_set_kompletorium_nedela(MODL_KOMPLETORIUM);
		}

		if ((_global_modlitba != MODL_PREDPOLUDNIM) && (_global_modlitba != MODL_NAPOLUDNIE) && (_global_modlitba != MODL_POPOLUDNI)) {
			Log("keďže nejde o modlitbu cez deň, preskakujeme nastavenia (všetky boli nastavené z vlastnej časti): (return)...\n");

			Log("jediné, čo nastavíme, je nastavenie kvôli kompletóriu v OCR...\n");
			_set_hymnus_alternativy_obdobie(litobd, ANO); // podmienka na liturgické obdobie je vnútri

			skip_big_switch = ANO;
			// 2018-10-04, JUV: instead of this hard-coded return, skip the big switch
			// Log("-- liturgicke_obdobie(%d, %d, %d, %d: svaty: %d) -- predčasný koniec\n", litobd, tyzden, den, tyzzal, poradie_svateho);
			// return;
		}
		else {
			if (_global_den.denvt == DEN_NEDELA) {
				Log("keďže ide o modlitbu cez deň, nastavujeme žalmy z nedele pre MCD a hoci použijeme ostatné nastavenia, všetky ostatné budú (snáď) nastavené z vlastnej časti...\n");

				if ((_global_den.den == 2) && (_global_den.mesiac - 1 == MES_FEB)) {
					Log(" pre modlitbu cez deň 02FEB nastavujeme aj antifóny k psalmódii zo dňa...\n");
					zaltar_zvazok(den, tyzzal, _global_den.litobd, ZALTAR_ANT_ZALMY_HYMNUS_MCD);
				}
				else {
					zaltar_zvazok(den, tyzzal, _global_den.litobd, ZALTAR_IBA_ZALMY_HYMNUS_MCD);
				}
			}
			else {
				Log("keďže ide o modlitbu cez deň MIMO nedele, nastavujeme všetky časti ako nasleduje - zo dňa...\n");
			}
		}

		Log("PODMIENKA_SVIATKY_PANA_SVATYCH_PREDNOST_PRED_NEDELOU_OCR: END\n");
	}
	else {
		Log("PODMIENKA_SVIATKY_PANA_SVATYCH_PREDNOST_PRED_NEDELOU_OCR: ELSE | NEjde o: premenenie pána || obetovanie pána || petra a pavla || povýšenie sv. kríža || všetkých svätých || nanebovzatia PM...\n");
	}

	Log("...a pre ranné chvály resp. vešpery ešte úvod k Otčenášu...\n");
	set_spolocne_veci_common();

	if (skip_big_switch == NIE) {
		// this also must not be run for PODMIENKA_SVIATKY_PANA_SVATYCH_PREDNOST_PRED_NEDELOU_OCR; prayers other than during the day (see above); before # 6dbb2650 was returned (exited) above
		Log("teraz spustíme zaltar_zvazok(); - pôvodne sa púšťala s dvoma parametrami, pridaný parameter pre zväzok breviára (voláme s hodnotou ZALTAR_VSETKO)\n");
		zaltar_zvazok(den, tyzzal, _global_den.litobd, ZALTAR_VSETKO);

		Log("následne odlišný súbor pre posvätné čítania...\n");
		file_name_litobd(litobd);
		Log("  _file == %s\n", _file);

		// Log(_global_modl_posv_citanie);

		file_name_litobd_pc(litobd);
		Log("  _file_pc == %s\n", _file_pc);

		mystrcpy(_file_pc_tyzden, STR_EMPTY, MAX_STR_AF_FILE);
		Log("  _file_pc_tyzden bude nastavene na prislusnom mieste (teraz == `%s').\n", _file_pc_tyzden);
	}

	char c; // používa sa vo výnimočných prípadoch: napr. druha velkonocna nedela

	Log("skip_big_switch == `%d'...\n", skip_big_switch);

	if (skip_big_switch == NIE) {
	
	// velky switch(litobd), podla ktoreho sa priradia zakladne udaje
	LOG_ciara_sv;
	Log("Začiatok veľkého switch()-u podľa liturgických období\nTeraz nasleduje veľký switch() podľa liturgických období...\n");
	switch(litobd) {

// invitatórium
// použiteľné pre adventné obdobie, vianočné...
#define _obd_invitat {\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _adv_invitat_24DEC {\
	sprintf(_anchor, "%s_24_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

#define _adv_hymnus {\
	sprintf(_anchor, "%s%s%c_%s", _special_anchor_prefix, nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_hymnus(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_hymnus(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
}
#define _adv1_kresponz {\
	sprintf(_anchor, "%s%s%c_%s", nazov_OBD[litobd], nazov_DN_asci[DEN_UNKNOWN], /* '??' */ 	pismenko_modlitby(modlitba), /* 'v' */ ANCHOR_KRESPONZ);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

// antifóny pre modlitbu cez deň sú rovnaké, použitý anchor ANCHOR_ANTIFONY
#define _adv_antifony_mcd {\
	/* 1. antifóna */\
	sprintf(_anchor, "%s%c_%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	/* 2. antifóna */\
	sprintf(_anchor, "%s%c_%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	/* 3. antifóna */\
	sprintf(_anchor, "%s%c_%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _adv1_kcitanie {\
	sprintf(_anchor, "%s%s%c_%s", nazov_OBD[litobd], nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _adv1_kresp_mcd {\
	sprintf(_anchor, "%s%s%c_%s", nazov_OBD[litobd], nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _adv1_modlitba {\
	sprintf(_anchor, "%s%d%s_%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _adv1_prosby {\
	sprintf(_anchor, "%s%d%s%c_%s", nazov_OBD[litobd], t, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_PROSBY);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _adv1_antifony {\
	sprintf(_anchor, "%s%d%s%c_%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_antifona1(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_antifona1(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
	sprintf(_anchor, "%s%d%s%c_%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_antifona2(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_antifona2(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
	sprintf(_anchor, "%s%d%s%c_%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_antifona3(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_antifona3(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
}

// switch(litobd), case OBD_ADVENTNE_I -- begin -----------------------------------------------
	case OBD_ADVENTNE_I :// do 16. decembra
			Log("OBD_ADVENTNE_I\n");

			// spoločné časti bez ohľadu na to, či je alebo nie je nedeľa

			// invitatórium
			modlitba = MODL_INVITATORIUM;
			if (_global_jazyk == JAZYK_CZ) {
				_obd_invitat_viac(litobd, modlitba);
			}
			else {
				_obd_invitat;
			}

			// ranné chvály
			modlitba = MODL_RANNE_CHVALY;
			_adv_hymnus; // hymnus
			_adv1_kresponz; // krátke responzórium - rovnake pre vsetky dni okrem nedele

			// vešpery
			modlitba = MODL_VESPERY;
			_adv_hymnus; // hymnus - rovnaky pre vsetky dni
			_adv1_kresponz; // krátke responzórium - rovnake pre vsetky dni okrem nedele

			// modlitba cez deň
			modlitba = MODL_PREDPOLUDNIM;
			_adv_hymnus; // hymnus
			_adv_antifony_mcd; // antifóny
			_adv1_kcitanie; // krátke čítanie - rovnaké pre všetky adventné týždne
			_adv1_kresp_mcd; // krátke responzórium - rovnaké pre všetky adventné týždne
			_adv1_modlitba; // modlitba ako na ranné chvály

			modlitba = MODL_NAPOLUDNIE;
			_adv_hymnus; // hymnus
			_adv_antifony_mcd; // antifóny
			_adv1_kcitanie; // krátke čítanie - rovnaké pre všetky adventné týždne
			_adv1_kresp_mcd; // krátke responzórium - rovnaké pre všetky adventné týždne
			_adv1_modlitba; // modlitba ako na ranné chvály

			modlitba = MODL_POPOLUDNI;
			_adv_hymnus; // hymnus
			_adv_antifony_mcd; // antifóny
			_adv1_kcitanie; // krátke čítanie - rovnaké pre všetky adventné týždne
			_adv1_kresp_mcd; // krátke responzórium - rovnaké pre všetky adventné týždne
			_adv1_modlitba; // modlitba ako na ranné chvály

			// posvätné čítanie
			modlitba = MODL_POSV_CITANIE;
			_adv_hymnus; // hymnus
			_adv1_modlitba;  // modlitba - rovnaka ako cez den

			// 1. čítanie
			sprintf(_anchor, "%s%d%s%c_%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_CITANIE1);
			_set_citanie1(modlitba, _file_pc, _anchor);
			set_LOG_litobd_pc;

			// 2. čítanie
			sprintf(_anchor, "%s%d%s%c_%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_CITANIE2);
			_set_citanie2(modlitba, _file_pc, _anchor);
			set_LOG_litobd_pc;

			t = set_tyzzal_1_2(tyzzal); // nema efekt pre tyzden == 4, lebo to uz je OBD_ADVENTNE_II

			if (den == DEN_NEDELA) { // nedeľa: 1.-3. adventná nedeľa
				// predĺžené slávenie vigílií v rámci posvätných čítaní | modlitba = MODL_POSV_CITANIE;
				_liturgicke_obdobie_set_vig_ant(modlitba);
				_set_chvalospev_vig_adv(modlitba);
				_liturgicke_obdobie_set_vig_ev_tyzden(modlitba, tyzden);

				// prvé vešpery
				/* pre všepery 16. decembra (ak je to sobota, ako napr. v roku 2006) sa jednak vezme všedný deň (sobota), jednak nasledujúci deň, teda 17. decembra,
				 * a prvé vešpery sú už z adventného obdobia II., väčšina vecí z 3. adventnej nedele je podľa OBD_ADVENTNE_II, niektoré z OBD_ADVENTNE_I
				 */

				 // hymnus - rovnaky pre prve a druhe vespery
				modlitba = MODL_PRVE_VESPERY;
				sprintf(_anchor, "%s%s%c_%s", _special_anchor_prefix,
					nazov_OBD[litobd],
					pismenko_modlitby(MODL_VESPERY),
					ANCHOR_HYMNUS);
				_set_hymnus(MODL_PRVE_VESPERY, _file, _anchor);
				set_LOG_litobd;

				// krátke responzórium - rovnake pre prve a druhe vespery a pre vsetky nedele
				sprintf(_anchor, "%s%s%c_%s",
					nazov_OBD[litobd],
					nazov_DN_asci[den],
					pismenko_modlitby(MODL_VESPERY),
					ANCHOR_KRESPONZ);
				_set_kresponz(modlitba, _file, _anchor);
				_set_kresponz(MODL_VESPERY, _file, _anchor);
				set_LOG_litobd;

				modlitba = MODL_PRVE_VESPERY;
				_adv1_antifony; // antifóny
				_adv1_kcitanie; // krátke čítanie - rovnake pre vsetky tyzdne
				// magnifikat
				sprintf(_anchor, "%s%d%s_%c%s%c",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_MAGNIFIKAT,
					_global_den.litrok);
				_set_magnifikat(modlitba, _file, _anchor);
				set_LOG_litobd;
				_adv1_prosby; // prosby - rovnake pre prvu a tretiu, resp. druhu a stvrtu adventnu nedelu
				_adv1_modlitba; // modlitba

				// posvätné čítanie
				modlitba = MODL_POSV_CITANIE;
				// hymnus - rovnaky pre vsetky nedele
				// krátke responzórium
				sprintf(_anchor, "%s%s%c_%s",
					nazov_OBD[litobd],
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_KRESPONZ);
				_set_kresponz(modlitba, _file_pc, _anchor);
				set_LOG_litobd;
				_adv1_antifony; // antifóny

				// ranné chvály
				// hymnus - rovnaky pre vsetky dni
				// krátke responzórium - rovnake pre vsetky nedele
				modlitba = MODL_RANNE_CHVALY;
				sprintf(_anchor, "%s%s%c_%s",
					nazov_OBD[litobd],
					nazov_DN_asci[den], // 'NE'
					pismenko_modlitby(modlitba), // 'r'
					ANCHOR_KRESPONZ);
				_set_kresponz(modlitba, _file, _anchor);
				set_LOG_litobd;
				_adv1_antifony; // antifóny
				_adv1_kcitanie; // krátke čítanie - rovnake pre vsetky tyzdne
				// benediktus
				sprintf(_anchor, "%s%d%s_%c%s%c",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_BENEDIKTUS,
					_global_den.litrok);
				_set_benediktus(modlitba, _file, _anchor);
				set_LOG_litobd;
				_adv1_prosby; // prosby - rovnake pre prvu a tretiu, resp. druhu a stvrtu adventnu nedelu
				_adv1_modlitba; // modlitba

				// druhé vešpery
				modlitba = MODL_VESPERY;
				_adv1_antifony; // antifóny
				_adv1_kcitanie; // krátke čítanie - rovnake pre vsetky tyzdne
				// magnifikat
				sprintf(_anchor, "%s%d%s_%c%s%c",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_MAGNIFIKAT,
					_global_den.litrok);
				_set_magnifikat(modlitba, _file, _anchor);
				set_LOG_litobd;
				_adv1_prosby; // prosby - rovnake pre prvu a tretiu, resp. druhu a stvrtu adventnu nedelu
				_adv1_modlitba; // modlitba
				// modlitbu cez deň nie je potrebné špeciálne riešiť
			}// nedeľa: 1.-3. adventná nedeľa
			else { // nie nedeľa, teda obyčajný deň adventného obdobia I.
				// posvätné čítanie
				modlitba = MODL_POSV_CITANIE;
				// hymnus - rovnaky pre vsetky dni
				// krátke responzórium
				sprintf(_anchor, "%s%s%c_%s",
					nazov_OBD[litobd],
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_KRESPONZ);
				_set_kresponz(modlitba, _file_pc, _anchor);
				set_LOG_litobd;
				// antifony - sú ako pre obdobie cez rok, z bežného žaltára

				// ranné chvály
				// hymnus - rovnaky pre vsetky dni
				// krátke responzórium - rovnake pre vsetky vsedne dni
				modlitba = MODL_RANNE_CHVALY;
				sprintf(_anchor, "%s%s%c_%s",
					nazov_OBD[litobd],
					nazov_DN_asci[DEN_UNKNOWN], // '??'
					pismenko_modlitby(modlitba), // 'r'
					ANCHOR_KRESPONZ);
				_set_kresponz(modlitba, _file, _anchor);
				set_LOG_litobd;
				// antifony - su zo vsedneho dna
				_adv1_kcitanie; // krátke čítanie - rovnake pre vsetky tyzdne
				// benediktus
				sprintf(_anchor, "%s%d%s_%c%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_BENEDIKTUS);
				_set_benediktus(modlitba, _file, _anchor);
				set_LOG_litobd;
				_adv1_prosby; // prosby - rovnake pre prvu a tretiu, resp. druhu a stvrtu adventnu nedelu
				_adv1_modlitba; // modlitba - rovnaka pre ranne chvaly aj vespery

				// vešpery
				// hymnus - rovnaky pre vsetky dni
				// krátke responzórium - rovnake pre vsetky vsedne dni
				modlitba = MODL_VESPERY;
				sprintf(_anchor, "%s%s%c_%s",
					nazov_OBD[litobd],
					nazov_DN_asci[DEN_UNKNOWN], // '??'
					pismenko_modlitby(modlitba), // 'r'
					ANCHOR_KRESPONZ);
				_set_kresponz(modlitba, _file, _anchor);
				set_LOG_litobd;
				// antifony - su zo vsedneho dna
				_adv1_kcitanie; // krátke čítanie - rovnake pre vsetky tyzdne
				// magnifikat
				sprintf(_anchor, "%s%d%s_%c%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_MAGNIFIKAT);
				_set_magnifikat(modlitba, _file, _anchor);
				set_LOG_litobd;
				_adv1_prosby; // prosby - rovnake pre prvu a tretiu, resp. druhu a stvrtu adventnu nedelu
				_adv1_modlitba; // modlitba - rovnaka pre ranne chvaly aj vespery
			}// nie nedeľa
			break;
// switch(litobd), case OBD_ADVENTNE_I -- end -------------------------------------------------

#define _adv2_kcitanie {\
	sprintf(_anchor, "%s%d%c_%s", nazov_OBD[litobd], _global_den.den, pismenko_modlitby(modlitba), ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _adv2_kcitanie_ne {\
	sprintf(_anchor, "%s%d%c_%s", nazov_OBD[litobd], (_global_den.den == 24) ? 24 : 18, /* len pre nedeľu 24. dec. berie sa 24. dec, inak (pre ostatné nedele) ako keby bolo 18. dec. */ pismenko_modlitby(modlitba), ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _adv2_kcitanie_adv1 {\
	sprintf(_anchor, "%s%s%c_%s", nazov_OBD[OBD_ADVENTNE_I], nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, nazov_obd_htm[OBD_ADVENTNE_I], _anchor);\
	set_LOG_litobd;\
}
#define _adv2_kresponz {\
	sprintf(_anchor, "%s%d%c_%s", nazov_OBD[litobd], (_global_den.den == 24) ? 24 : 18, /* len pre nedeľu 24. dec. berie sa 24. dec, inak (pre ostatné nedele) ako keby bolo 18. dec. */ pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _adv2_kresponz_mcd {\
	sprintf(_anchor, "%s%d%c_%s", nazov_OBD[litobd], _global_den.den, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	_set_kresponz(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _adv2_modlitba {\
	sprintf(_anchor, "%s%d_%s", nazov_OBD[litobd], _global_den.den, ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _adv2_modlitba_ne {\
	sprintf(_anchor, "%s%d%s_%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _adv2_prosby {\
	sprintf(_anchor, "%s%d%c_%s", nazov_OBD[litobd], _global_den.den, pismenko_modlitby(modlitba), ANCHOR_PROSBY);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _adv2_prosby_4advne {\
	sprintf(_anchor, "%s%d%s%c_%s", nazov_OBD[litobd], 4, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_PROSBY);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _adv2_antifony_vesp {\
	sprintf(_anchor, "%s%s%c_%s", nazov_OBD[litobd], nazov_DN_asci[den], pismenko_modlitby(MODL_VESPERY), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s%s%c_%s", nazov_OBD[litobd], nazov_DN_asci[den], pismenko_modlitby(MODL_VESPERY), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s%s%c_%s", nazov_OBD[litobd], nazov_DN_asci[den], pismenko_modlitby(MODL_VESPERY), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _adv2_antifony {\
	sprintf(_anchor, "%s%d%c_%s", nazov_OBD[litobd], _global_den.den, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_antifona1(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_antifona1(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
	sprintf(_anchor, "%s%d%c_%s", nazov_OBD[litobd], _global_den.den, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_antifona2(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_antifona2(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
	sprintf(_anchor, "%s%d%c_%s", nazov_OBD[litobd], _global_den.den, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_antifona3(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_antifona3(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
}

// switch(litobd), case OBD_ADVENTNE_II -- begin ----------------------------------------------
		case OBD_ADVENTNE_II: // po 16. decembri
			Log("OBD_ADVENTNE_II\n");

			file_name_litobd(OBD_ADVENTNE_II);

			// invitatórium
			modlitba = MODL_INVITATORIUM;
			if(_global_den.den != 24){
				_obd_invitat;
			}
			else{
				_adv_invitat_24DEC;
			}

			// ranné chvály
			modlitba = MODL_RANNE_CHVALY;
			// hymnus - rovnaky pre kazdy den
			_adv_hymnus;
			// antifony - zavisia od dna v tyzdni (PONDELOK -- SOBOTA)
			// kedze su rovnake na ranne chvaly aj na vespery, rozhodli sme sa dat tam 'v'
			_adv2_antifony_vesp;
			// krátke responzórium - rovnake pre vsetky dni
			sprintf(_anchor, "%s%s%c_%s",
				nazov_OBD[litobd],
				nazov_DN_asci[DEN_UNKNOWN],
				pismenko_modlitby(modlitba),
				ANCHOR_KRESPONZ);
			_set_kresponz(modlitba, _file, _anchor);
			set_LOG_litobd;
			// ďalšie závisia od dátumu (17. -- 24. december)
			_adv2_kcitanie; // krátke čítanie
			// benediktus
			sprintf(_anchor, "%s%d_%c%s",
				nazov_OBD[litobd],
				_global_den.den,
				pismenko_modlitby(modlitba),
				ANCHOR_BENEDIKTUS);
			_set_benediktus(modlitba, _file, _anchor);
			set_LOG_litobd;
			_adv2_prosby; // prosby
			_adv2_modlitba; // modlitba - rovnaka pre rano i vecer

			// vešpery
			// antifóny
			modlitba = MODL_VESPERY;
			// hymnus - rovnaky pre kazdy den
			_adv_hymnus;
			// antifony - zavisia od dna v tyzdni (PONDELOK -- SOBOTA)
			_adv2_antifony_vesp;
			// ďalšie závisia od dátumu (17. -- 24. december)
			// krátke responzórium - rovnake pre 17. a 18., resp. pre vsetky ostatne dni (19.-23.)
			sprintf(_anchor, "%s%d%c_%s",
				nazov_OBD[litobd],
				(_global_den.den > 18? 19: 17),
				pismenko_modlitby(modlitba),
				ANCHOR_KRESPONZ);
			_set_kresponz(modlitba, _file, _anchor);
			set_LOG_litobd;
			_adv2_kcitanie; // krátke čítanie
			// magnifikat
			sprintf(_anchor, "%s%d_%c%s",
				nazov_OBD[litobd],
				_global_den.den,
				pismenko_modlitby(modlitba),
				ANCHOR_MAGNIFIKAT);
			_set_benediktus(modlitba, _file, _anchor);
			set_LOG_litobd;
			_adv2_prosby; // prosby
			_adv2_modlitba; // modlitba - rovnaka pre rano i vecer

			// modlitba cez deň, pridané 2005-12-17 trochu podľa ADV.I.
			modlitba = MODL_PREDPOLUDNIM;
			_adv_hymnus; // hymnus
			_adv_antifony_mcd; // antifóny
			// ďalšie závisia od dátumu (17. -- 24. december)
			_adv2_kcitanie; // krátke čítanie
			_adv2_kresponz_mcd; // krátke responzórium - rovnaké pre všetky adventné týždne
			_adv2_modlitba; // modlitba ako na ranné chvály aj vešpery

			modlitba = MODL_NAPOLUDNIE;
			_adv_hymnus; // hymnus
			_adv_antifony_mcd; // antifóny
			// ďalšie závisia od dátumu (17. -- 24. december)
			_adv2_kcitanie; // krátke čítanie
			_adv2_kresponz_mcd; // krátke responzórium - rovnaké pre všetky adventné týždne
			_adv2_modlitba; // modlitba ako na ranné chvály aj vešpery

			modlitba = MODL_POPOLUDNI;
			_adv_hymnus; // hymnus
			_adv_antifony_mcd; // antifóny
			// ďalšie závisia od dátumu (17. -- 24. december)
			_adv2_kcitanie; // krátke čítanie
			_adv2_kresponz_mcd; // krátke responzórium - rovnaké pre všetky adventné týždne
			_adv2_modlitba; // modlitba ako na ranné chvály aj vešpery

			modlitba = MODL_POSV_CITANIE;
			_adv_hymnus; // hymnus
			// _adv2_antifony; // antifóny: len pre 4. adventnú nedeľu; ináč sa berú zo žaltára z bežného dňa

			// ďalšie závisia od dátumu (17. -- 24. december)
			// 1. čítanie
			sprintf(_anchor, "%s%d%c_%s",
				nazov_OBD[litobd],
				_global_den.den,
				pismenko_modlitby(modlitba),
				ANCHOR_CITANIE1);
			_set_citanie1(modlitba, _file_pc, _anchor);
			set_LOG_litobd;

			// 2. čítanie
			sprintf(_anchor, "%s%d%c_%s",
				nazov_OBD[litobd],
				_global_den.den,
				pismenko_modlitby(modlitba),
				ANCHOR_CITANIE2);
			_set_citanie2(modlitba, _file_pc, _anchor);
			set_LOG_litobd;

			// krátke responzórium
			sprintf(_anchor, "%s%d%c_%s",
				nazov_OBD[litobd],
				_global_den.den,
				pismenko_modlitby(modlitba),
				ANCHOR_KRESPONZ);
			_set_kresponz(modlitba, _file_pc, _anchor);
			set_LOG_litobd;

			_adv2_modlitba; // modlitba - rovnaka pre rano i vecer

			// nedeľa: 3. adventná nedeľa (len 17. decembra, ako napr. v roku 2006), inak 4. adventná nedeľa

			// ak tretia adventna nedela padne na 17. decembra, beru sa antifony na magnifikat, benediktus, prosby a hymny z tejto casti,
			// avsak ostatne sa berie akoby z OBD_ADVENTNE_I, teda _file == nazov_obd_htm[OBD_ADVENTNE_I] |  _anchor == napr. ADV13NEr_ANT1 
			// antifóna na magnifikat pre prvé vešpery 16. decembra (napr. rok 2006) sa vezme z 3. adventnej nedele
			if (den == DEN_NEDELA) {

				// predĺžené slávenie vigílií v rámci posvätných čítaní | modlitba = MODL_POSV_CITANIE;
				_liturgicke_obdobie_set_vig_ant(modlitba);
				_set_chvalospev_vig_adv(modlitba);
				// _liturgicke_obdobie_set_vig_ev_tyzden(modlitba, tyzden);

				// prvé vešpery - presunuté len pre nedeľu
				modlitba = MODL_PRVE_VESPERY;
				// hymnus
				sprintf(_anchor, "%s%s%c_%s",
					_special_anchor_prefix,
					nazov_OBD[litobd],
					pismenko_modlitby(MODL_VESPERY),
					ANCHOR_HYMNUS);
				_set_hymnus(modlitba, _file, _anchor);
				set_LOG_litobd;
				// antifóna na magnifikat a prosby závisia od toho, či je 3. alebo 4. adventná nedeľa, preto presunuté nižšie

				if ((tyzden == 3) && (_global_den.den == 17)) {
					// jedine 17. decembra, preto doplnené aj o dátum (Tretia adventná nedeľa)
					litobd = OBD_ADVENTNE_I;
					file_name_litobd(litobd);
					file_name_litobd_pc(litobd);

					// prvé vešpery
					modlitba = MODL_PRVE_VESPERY;
					// hymnus pre obdobie OBD_ADVENTNE_II, teda tak, ako bol nastavený vyššie
					_adv1_antifony; // antifóny - z tretej adventnej nedele, OBD_ADVENTNE_I
					_adv1_kcitanie; // pozor, používame z adv. obdobia I.
					_adv1_modlitba; // modlitba
					// krátke responzórium - z tretej adventnej nedele, OBD_ADVENTNE_I
					sprintf(_anchor, "%s%s%c_%s",
						nazov_OBD[litobd],
						nazov_DN_asci[den],
						pismenko_modlitby(MODL_VESPERY),
						ANCHOR_KRESPONZ);
					_set_kresponz(modlitba, _file, _anchor);
					_set_kresponz(MODL_VESPERY, _file, _anchor);
					set_LOG_litobd;
					// magnifikat
					sprintf(_anchor, "%s%d%s_%c%s%c",
						nazov_OBD[litobd],
						tyzden,
						nazov_DN_asci[den],
						pismenko_modlitby(modlitba),
						ANCHOR_MAGNIFIKAT,
						_global_den.litrok);
					_set_magnifikat(modlitba, _file, _anchor);
					set_LOG_litobd;
					// 2007-12-04: kvôli prosbám je potrebné nastaviť parameter t
					t = set_tyzzal_1_2(tyzzal); // nema efekt pre tyzden == 4, lebo to uz je OBD_ADVENTNE_II
					_adv1_prosby; // prosby - rovnake pre prvu a tretiu, resp. druhu a stvrtu adventnu nedelu

					// posvätné čítanie
					modlitba = MODL_POSV_CITANIE;
					_liturgicke_obdobie_set_vig_ev_tyzden(modlitba, tyzden);
					_adv1_modlitba; // modlitba má byť z 3. adventnej nedele
					tyzden_pom = tyzden;
					tyzden = 3; // nie je treba; pre istotu
					_adv1_antifony; // antifóny -- rovnaké pre všetky 4 adventné nedele, preto berieme z 3. adventnej nedele
					tyzden = tyzden_pom;

					// ranné chvály
					// krátke responzórium - rovnaké pre všetky nedele
					modlitba = MODL_RANNE_CHVALY;
					sprintf(_anchor, "%s%s%c_%s", nazov_OBD[litobd], nazov_DN_asci[den], /* 'NE' */ pismenko_modlitby(modlitba), /* 'r' */ ANCHOR_KRESPONZ);
					_set_kresponz(modlitba, _file, _anchor);
					set_LOG_litobd;
					_adv1_antifony; // antifóny
					// krátke čítanie - rovnaké pre všetky adventné nedele
					_adv1_kcitanie; // pozor, používame z adv. obdobia I.
					_adv1_modlitba; // modlitba

					// druhé vešpery
					modlitba = MODL_VESPERY;
					_adv1_antifony; // antifóny
					// krátke čítanie - rovnake pre vsetky adventne nedele
					_adv1_kcitanie; // pozor, používame z adv. obdobia I.
					_adv1_modlitba; // modlitba
					// antifóna na magnifikat pre druhé vešpery nastavená vyššie, podľa dátumu, ako pre bežný deň

					// modlitba cez deň, podľa ADV.I. okrem hymnov
					modlitba = MODL_PREDPOLUDNIM;
					_adv_antifony_mcd; // antifóny
					_adv1_kcitanie; // krátke čítanie - rovnaké pre všetky adventné týždne
					_adv1_kresp_mcd; // krátke responzórium - rovnaké pre všetky adventné týždne
					_adv1_modlitba; // modlitba ako na ranné chvály

					modlitba = MODL_NAPOLUDNIE;
					_adv_antifony_mcd; // antifóny
					_adv1_kcitanie; // krátke čítanie - rovnaké pre všetky adventné týždne
					_adv1_kresp_mcd; // krátke responzórium - rovnaké pre všetky adventné týždne
					_adv1_modlitba; // modlitba ako na ranné chvály

					modlitba = MODL_POPOLUDNI;
					_adv_antifony_mcd; // antifóny
					_adv1_kcitanie; // krátke čítanie - rovnaké pre všetky adventné týždne
					_adv1_kresp_mcd; // krátke responzórium - rovnaké pre všetky adventné týždne
					_adv1_modlitba; // modlitba ako na ranné chvály

				}// tretia adventná nedeľa
				else {// tyzden == 4, štvrtá adventná nedeľa

					// prvé vešpery
					modlitba = MODL_PRVE_VESPERY;
					// magnifikat -- pre 18.-24. decembra pre prvé vešpery sú vždy z predošlého dňa; 
					// výnimka je 17. decembra, kedy sa použije na prvé vešpery antifóna z 3. adventnej nedele, čo je zabezpečené vyššie

					// tieto závisia od dátumu (17. -- 24. december)
					// antifóna na magnifikat
					sprintf(_anchor, "%s%d_%c%s",
						nazov_OBD[litobd],
						_global_den.den - 1,
						pismenko_modlitby(MODL_VESPERY),
						ANCHOR_MAGNIFIKAT);
					_set_benediktus(modlitba, _file, _anchor);
					set_LOG_litobd;
					// prosby
					sprintf(_anchor, "%s%d%c_%s",
						nazov_OBD[litobd],
						_global_den.den,
						pismenko_modlitby(MODL_VESPERY),
						ANCHOR_PROSBY);
					_set_prosby(modlitba, _file, _anchor);
					set_LOG_litobd;

					file_name_litobd(OBD_ADVENTNE_I);

					// krátke responzórium - rovnake pre prve a druhe vespery a pre vsetky nedele
					sprintf(_anchor, "%s%s%c_%s",
						nazov_OBD[OBD_ADVENTNE_I],
						nazov_DN_asci[den],
						pismenko_modlitby(MODL_VESPERY),
						ANCHOR_KRESPONZ);
					_set_kresponz(modlitba, nazov_obd_htm[OBD_ADVENTNE_I], _anchor);
					_set_kresponz(MODL_VESPERY, _file, _anchor);
					set_LOG_litobd;

					// posvätné čítanie; presunuté na koniec kvôli zmene súboru
					modlitba = MODL_POSV_CITANIE;
					_liturgicke_obdobie_set_vig_ev_tyzden(modlitba, tyzden);
					_adv2_modlitba_ne; // modlitba
					file_name_litobd_pc(OBD_ADVENTNE_I); // kvôli antifónam pre posv. čítanie
					litobd_pom = litobd;
					tyzden_pom = tyzden;
					litobd = OBD_ADVENTNE_I;
					tyzden = 3;
					_adv1_antifony; // antifóny -- rovnaké pre všetky 4 adventné nedele, preto berieme z 3. adventnej nedele
					tyzden = tyzden_pom;
					litobd = litobd_pom;

					modlitba = MODL_PRVE_VESPERY;
					_adv1_antifony; // antifóny
					_adv2_kcitanie_adv1; // krátke čítanie - rovnake pre vsetky adventne nedele
					_adv2_prosby_4advne; // prosby
					_adv2_modlitba_ne; // modlitba

					// modlitba cez deň, trochu podľa ADV.I. okrem hymnov a antifón; predsunuté sem, aby sme neodskočili pre 24. dec.
					modlitba = MODL_PREDPOLUDNIM;
					_adv2_modlitba_ne; // modlitba

					modlitba = MODL_NAPOLUDNIE;
					_adv2_modlitba_ne; // modlitba

					modlitba = MODL_POPOLUDNI;
					_adv2_modlitba_ne; // modlitba

					file_name_litobd(OBD_ADVENTNE_II);

					modlitba = MODL_PREDPOLUDNIM;
					// ďalšie závisia od dátumu (18. dec. pre nedele okrem 24. decembra)
					_adv2_kcitanie_ne; // krátke čítanie
					_adv2_kresponz; // krátke responzórium - rovnaké pre všetky adventné týždne

					modlitba = MODL_NAPOLUDNIE;
					// ďalšie závisia od dátumu (18. dec. pre nedele okrem 24. decembra)
					_adv2_kcitanie_ne; // krátke čítanie
					_adv2_kresponz; // krátke responzórium - rovnaké pre všetky adventné týždne

					modlitba = MODL_POPOLUDNI;
					// ďalšie závisia od dátumu (18. dec. pre nedele okrem 24. decembra)
					_adv2_kcitanie_ne; // krátke čítanie
					_adv2_kresponz; // krátke responzórium - rovnaké pre všetky adventné týždne

					// ak je 24. dec., vsetko pre ranne chvaly sa berie zo dna 24.
					if (_global_den.den == 24) {
						file_name_litobd(OBD_ADVENTNE_II);
						// benediktus
						sprintf(_anchor, "%s%d_%c%s",
							nazov_OBD[litobd],
							_global_den.den,
							pismenko_modlitby(MODL_RANNE_CHVALY),
							ANCHOR_BENEDIKTUS);
						_set_benediktus(MODL_RANNE_CHVALY, _file, _anchor);
						set_LOG_litobd;
						goto label_24_DEC;
					}
					else {
						file_name_litobd(OBD_ADVENTNE_I);
					}

					// ranné chvály
					// krátke responzórium - rovnake pre vsetky nedele
					modlitba = MODL_RANNE_CHVALY;
					sprintf(_anchor, "%s%s%c_%s",
						nazov_OBD[OBD_ADVENTNE_I],
						nazov_DN_asci[den], // 'NE'
						pismenko_modlitby(modlitba), // 'r'
						ANCHOR_KRESPONZ);
					_set_kresponz(modlitba, nazov_obd_htm[OBD_ADVENTNE_I], _anchor);
					set_LOG_litobd;
					_adv1_antifony; // antifóny
					_adv2_kcitanie_adv1; // krátke čítanie - rovnake pre vsetky adventne nedele
					// benediktus
					if ((_global_den.den == 21) || (_global_den.den == 23) || (_global_jazyk == JAZYK_HU)) {
						// treba brať ant. Nebojte sa resp. Hľa, splnilo sa; pre maďarskú LH je explicitne uvedené, že sa má brať ant. z príslušného dňa (HU LH, vol. I, p. 261)
					}
					else {
						sprintf(_anchor, "%s%d%s_%c%s%c",
							nazov_OBD[litobd],
							tyzden,
							nazov_DN_asci[den],
							pismenko_modlitby(modlitba),
							ANCHOR_BENEDIKTUS,
							_global_den.litrok);
						_set_benediktus(modlitba, _file, _anchor);
					}
					set_LOG_litobd;
					_adv2_prosby_4advne; // prosby
					_adv2_modlitba_ne; // modlitba

					// druhé vešpery
					modlitba = MODL_VESPERY;
					_adv1_antifony; // antifóny
					_adv2_kcitanie_adv1; // krátke čítanie - rovnake pre vsetky adventne nedele
					_adv2_prosby_4advne; // prosby
					_adv2_modlitba_ne; // modlitba

				}// štvrtá adventná nedeľa
			}// nedeľa
			else {
				// upravime veci pre 24. dec.
				if (_global_den.den == 24) {
				label_24_DEC:
					// iba ranne chvaly
					modlitba = MODL_RANNE_CHVALY;
					// hymnus - rovnaky pre kazdy den
					_adv2_antifony; // antifony - vlastne
					// krátke responzórium - vlastne
					sprintf(_anchor, "%s%d%c_%s",
						nazov_OBD[litobd],
						_global_den.den,
						pismenko_modlitby(modlitba),
						ANCHOR_KRESPONZ);
					_set_kresponz(modlitba, _file, _anchor);
					set_LOG_litobd;
				}
			}// nie nedela -- upravenie pre 24. dec.

			// Vo všedné dni od 17. do 23. decembra sa berú:
			// invitatórium, hymny, čítania a responzóriá, verše, modlitba, antifóny a prosby na ranné chvály a vešpery, ako sú na strane 71n. 
			// Tieto časti sa potom z tretieho týždňa vynechávajú. ostatne veci sa beru z predosleho

			break;
// switch(litobd), case OBD_ADVENTNE_II -- end ------------------------------------------------

// panny marie bohorodicky
#define _bohorod_hymnus(vlastny_anchor) {\
	c = pismenko_modlitby(modlitba);\
	sprintf(_anchor, "%s%s_%c%s", _special_anchor_prefix, vlastny_anchor, c, ANCHOR_HYMNUS);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_hymnus(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_hymnus(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
}
#define _bohorod_kcitanie(vlastny_anchor) {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, c, ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _bohorod_kresponz(vlastny_anchor) {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, c, ANCHOR_KRESPONZ);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_kresponz(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_kresponz(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
}
#define _bohorod_modlitba {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY){\
		c = pismenko_modlitby(MODL_VESPERY);\
	}\
	if(je_modlitba_cez_den(modlitba) || (modlitba == MODL_POSV_CITANIE)){\
		c = pismenko_modlitby(MODL_RANNE_CHVALY);\
	}\
	sprintf(_anchor, "%s_%c%s", ANCHOR_PM_BOHOROD, c, ANCHOR_MODLITBA);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _bohorod_antifony {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY){\
		c = pismenko_modlitby(MODL_VESPERY);\
	}\
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

// sviatok svatej rodiny
#define _sv_rodiny_hymnus(vlastny_anchor) {\
	sprintf(_anchor, "%s%s_%c%s", _special_anchor_prefix, vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_hymnus(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_hymnus(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
}
#define _sv_rodiny_kresponz(vlastny_anchor) {\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_kresponz(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_kresponz(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
}
#define _sv_rodiny_prosby(vlastny_anchor) {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, c, ANCHOR_PROSBY);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _sv_rodiny_benediktus(vlastny_anchor) {\
	sprintf(_anchor, "%s_%c%s%c", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, _global_den.litrok);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _sv_rodiny_magnifikat(vlastny_anchor) {\
	sprintf(_anchor, "%s_%c%s%c", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, _global_den.litrok);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _sv_rodiny_antifony(vlastny_anchor) {\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", vlastny_anchor, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

// vianocne obdobie I

// pre český breviár a prvé vešpery narodenia pána je iný hymnus
#define _vian1_hymnus {\
	c = pismenko_modlitby(modlitba);\
	if((modlitba == MODL_PRVE_VESPERY) && (_global_den.den != 25))\
		c = pismenko_modlitby(MODL_VESPERY);\
	sprintf(_anchor, "%s%s_%c%s", _special_anchor_prefix, nazov_OBD[OBD_VIANOCNE_I], c, ANCHOR_HYMNUS);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_hymnus(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_hymnus(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
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

// pre český breviár a prvé vešpery narodenia pána je iný zpěv po krátkém čtení
#define _vian1_kresponz {\
	c = pismenko_modlitby(modlitba);\
	if((modlitba == MODL_PRVE_VESPERY) && (_global_den.den != 25))\
		c = pismenko_modlitby(MODL_VESPERY);\
	if((den == DEN_NEDELA) && (_global_den.den != 25 /* narodenie Pana */)\
		&& (modlitba != MODL_POSV_CITANIE) && (modlitba != MODL_VESPERY) && (modlitba != MODL_PRVE_VESPERY)){ /* pre prvé aj druhé vešpery 2. nedele po narodení Pána kresp. rovnako ako mimo nedele */\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[OBD_VIANOCNE_I], c, ANCHOR_KRESPONZ, nazov_DN_asci[den]);\
	}\
	else if(modlitba != MODL_POSV_CITANIE){\
		sprintf(_anchor, "%s_%c%s", nazov_OBD[OBD_VIANOCNE_I], c, ANCHOR_KRESPONZ);\
	}\
	else {\
		sprintf(_anchor, "%s_%c%s_%d", nazov_OBD[OBD_VIANOCNE_I], c, ANCHOR_KRESPONZ, _global_den.den);\
	}\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_kresponz(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_kresponz(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
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
// pre popis prvého kompletória Narodenia Pána // tam sa dá litobd == OBD_OKTAVA_NARODENIA
#define _vian1_popis {\
	sprintf(_anchor, "%s_%c%s%d", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_POPIS, _global_den.den);\
	if(modlitba == MODL_POSV_CITANIE){\
		set_popis(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		set_popis(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
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
#define _vian1_citanie1 {\
	sprintf(_anchor, "%s_%c%s_%d", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_CITANIE1, _global_den.den);\
	_set_citanie1(modlitba, _file_pc, _anchor);\
	set_LOG_litobd_pc;\
}
#define _vian1_citanie2 {\
	sprintf(_anchor, "%s_%c%s_%d", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_CITANIE2, _global_den.den);\
	_set_citanie2(modlitba, _file_pc, _anchor);\
	set_LOG_litobd_pc;\
}
#define _vian_okt_antifony_pc {\
	sprintf(_anchor, "%s_%c%s_%d", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1, _global_den.den);\
	_set_antifona1(modlitba, _file_pc, _anchor);\
	set_LOG_litobd_pc;\
	sprintf(_anchor, "%s_%c%s_%d", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2, _global_den.den);\
	_set_antifona2(modlitba, _file_pc, _anchor);\
	set_LOG_litobd_pc;\
	sprintf(_anchor, "%s_%c%s_%d", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3, _global_den.den);\
	_set_antifona3(modlitba, _file_pc, _anchor);\
	set_LOG_litobd_pc;\
}

// vytvorené pre modlitbu cez deň podľa _post1_mcd_antifony; porov. _adv_antifony_mcd
// antifóny pre modlitbu cez deň sú rovnaké, použitý anchor ANCHOR_ANTIFONY
#define _vian1_mcd_antifony {\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[OBD_VIANOCNE_I], pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[OBD_VIANOCNE_I], pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[OBD_VIANOCNE_I], pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

// switch(litobd), case OBD_OKTAVA_NARODENIA -- begin -----------------------------------------

		// narodenie Pana -- 1. jan.
		case OBD_OKTAVA_NARODENIA: {

			// tu v skutočnosti začína VIANOČNÁ OKTÁVA = OKTÁVA NARODENIA PÁNA

			Log("OBD_OKTAVA_NARODENIA - nastavujem kompletórium z nedele po 1. resp. 2. vešperách...\n");
			// kompletórium vo vianočnej aj veľkonočnej oktáve je z nedele po prvých resp. druhých vešperách
			modlitba = MODL_KOMPLETORIUM;
			// možnosť použiť prvé alebo druhé nedeľné kompletórium podľa toho, či používať alternatívy; ináč použité napevno podľa modula dňa
			_set_kompletorium_slavnost_oktava(modlitba, litobd, (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI) ? isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_KOMPLETORIUM_OKTAVA) : (_global_den.den MOD 2)) + 1);

			Log("OBD_OKTAVA_NARODENIA - pokračujeme ako vianočné obdobie I...\n");
			// a pokracujeme ako vianocne obdobie I
		}
		// [[fallthrough]];

// switch(litobd), case OBD_VIANOCNE_I -- begin -----------------------------------------------
		// do slavnosti zjavenia pana
		case OBD_VIANOCNE_I: {
			Log("OBD_VIANOCNE_I\n");

			// tu v skutočnosti začína VIANOČNÉ OBDOBIE I.

			if ((_global_den.den == 26) || (_global_den.den == 27) || (_global_den.den == 28)) {
				// maju vlastnu cast zo sv. jana apostola, sv. stefana a sv. neviniatok
				// modlitba cez deň je z oktávy narodenia Pána, preto bola vyňatá z "else" vetvy až za tento "if"
			}
			else {
				// invitatórium
				modlitba = MODL_INVITATORIUM;
				_obd_invitat;

				// ranné chvály
				modlitba = MODL_RANNE_CHVALY;
				_vian1_hymnus;
				_vian1_kcitanie;
				_vian1_kresponz;
				_vian1_benediktus;
				_vian1_prosby;
				_vian1_modlitba;

				// posvätné čítanie
				modlitba = MODL_POSV_CITANIE;
				_vian1_hymnus;
				_set_zalmy_vian_oktava(_global_den.den, modlitba);
				if (_global_den.den >= 25) {
					// antifóny sú samostatné len pre vianočnú oktávu; inak zo žaltára
					_vian_okt_antifony_pc;
				}
				_vian1_kresponz;
				_vian1_citanie1;
				_vian1_citanie2;
				_vian1_modlitba;

				// modlitba cez deň je z oktávy narodenia Pána, preto bola vyňatá z "else" vetvy až za tento "if"
			}

			if ((_global_svaty_i_smer_override(1) <= 4) && ((_global_den.den == 26) || (_global_den.den == 27) || (_global_den.den == 28))) {
				// ak sa slávia ako slávnosť, tak majú svoje vlastné texty
			}
			else {
				// modlitba cez deň
				modlitba = MODL_PREDPOLUDNIM;
				_vian1_hymnus; // hymnus
				_vian1_mcd_antifony; // antifóny
				_vian1_kcitanie; // krátke čítanie
				_vian1_kresponz; // krátke responzórium
				_vian1_modlitba; // modlitba ako na ranné chvály

				modlitba = MODL_NAPOLUDNIE;
				_vian1_hymnus; // hymnus
				_vian1_mcd_antifony; // antifóny
				_vian1_kcitanie; // krátke čítanie
				_vian1_kresponz; // krátke responzórium
				_vian1_modlitba; // modlitba ako na ranné chvály

				modlitba = MODL_POPOLUDNI;
				_vian1_hymnus; // hymnus
				_vian1_mcd_antifony; // antifóny
				_vian1_kcitanie; // krátke čítanie
				_vian1_kresponz; // krátke responzórium
				_vian1_modlitba; // modlitba ako na ranné chvály

				// vešpery
				modlitba = MODL_VESPERY;
				_vian1_hymnus;
				_vian1_kcitanie;
				_vian1_kresponz;
				_vian1_magnifikat;
				_vian1_prosby;
				_vian1_modlitba;
			}

			if (litobd == OBD_OKTAVA_NARODENIA) {
				if (_global_den.den == 25) {  // Narodenie Pána
					Log("Narodenie Pána...\n");
					// predĺžené slávenie vigílií v rámci posvätných čítaní | modlitba = MODL_POSV_CITANIE;
					modlitba = MODL_POSV_CITANIE;
					_liturgicke_obdobie_set_vig_ant(modlitba);
					_set_chvalospev_vig_vian(modlitba);
					sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_EVANJELIUM);
					_set_evanjelium(modlitba, _file_pc, _anchor);
					set_LOG_litobd_pc;

					// kompletórium
					modlitba = MODL_PRVE_KOMPLETORIUM;
					_set_kompletorium_slavnost(modlitba);
					// popis k prvému kompletóriu Narodenia Pána
					_vian1_popis;

					modlitba = MODL_KOMPLETORIUM;
					_set_kompletorium_slavnost(modlitba);

					// prvé vešpery
					modlitba = MODL_PRVE_VESPERY;
					_vian1_hymnus;
					_narodenie_antifony;
					_vian1_kcitanie;
					_vian1_kresponz;
					_vian1_magnifikat;
					_vian1_prosby;
					_vian1_modlitba;
					_set_zalmy_narodenie(modlitba);

					// modlitba cez deň
					modlitba = MODL_PREDPOLUDNIM;
					_set_zalmy_narodenie(modlitba);
					modlitba = MODL_NAPOLUDNIE;
					_set_zalmy_narodenie(modlitba);
					modlitba = MODL_POPOLUDNI;
					_set_zalmy_narodenie(modlitba);
				} // 25. 12. | 25DEC
				else {
					Log("Oktáva Narodenia Pána...\n");
					modlitba = MODL_POSV_CITANIE;
					// predĺžené slávenie vigílií v rámci posvätných čítaní | modlitba = MODL_POSV_CITANIE;
					_liturgicke_obdobie_set_vig_ant(modlitba);
					_set_chvalospev_vig_vian(modlitba);
					_liturgicke_obdobie_set_vig_ev(modlitba);
				}// ostatné dni v Oktáve Narodenia Pána

				// ranné chvály
				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_narodenie(modlitba);
				_narodenie_antifony;

				// druhé vešpery
				modlitba = MODL_VESPERY;
				_set_zalmy_narodenie(modlitba);
				_narodenie_antifony;
			}

			if ((_global_den.den == 1) && (_global_den.mesiac - 1 == MES_JAN)) { // Panny Márie Bohorodičky | BOHORODICKY_PANNY_MARIE | 01JAN
				mystrcpy(_file, FILE_PM_BOHOROD, MAX_STR_AF_FILE);
				mystrcpy(_file_pc, FILE_PM_BOHOROD, MAX_STR_AF_FILE);
				mystrcpy(_anchor, ANCHOR_PM_BOHOROD, MAX_STR_AF_ANCHOR);
				mystrcpy(_anchor_vlastne_slavenie, ANCHOR_PM_BOHOROD, MAX_STR_AF_ANCHOR);
				Log("  ide o slavnost panny marie bohorodicky: _file = `%s', _anchor = %s...\n", _file, _anchor);

				modlitba = MODL_PRVE_VESPERY;
				_set_zalmy_sviatok_panien(modlitba);
				_bohorod_hymnus(_anchor_vlastne_slavenie);
				_bohorod_kcitanie(_anchor_vlastne_slavenie);
				_bohorod_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
				_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
				_bohorod_modlitba;
				_bohorod_antifony;

				// kompletórium
				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				// invitatórium
				modlitba = MODL_INVITATORIUM;
				_vlastne_slavenie_invitat(_anchor_vlastne_slavenie);

				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_1nedele_rch();
				_bohorod_hymnus(_anchor_vlastne_slavenie);
				_bohorod_kcitanie(_anchor_vlastne_slavenie);
				_bohorod_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_benediktus(_anchor_vlastne_slavenie);
				_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
				_bohorod_modlitba;
				_bohorod_antifony;

				modlitba = MODL_VESPERY;
				_set_zalmy_sviatok_panien(modlitba);
				_bohorod_hymnus(_anchor_vlastne_slavenie);
				_bohorod_kcitanie(_anchor_vlastne_slavenie);
				_bohorod_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
				_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
				_bohorod_modlitba;
				_bohorod_antifony;

				// posvätné čítanie
				modlitba = MODL_POSV_CITANIE;
				_bohorod_hymnus(_anchor_vlastne_slavenie);
				_set_zalmy_vian_oktava(_global_den.den, modlitba);
				_bohorod_antifony;
				_bohorod_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_ine_1citanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_ine_2citanie(_anchor_vlastne_slavenie);
				_bohorod_modlitba;
				// predĺžené slávenie vigílií v rámci posvätných čítaní | modlitba = MODL_POSV_CITANIE;
				_vlastne_slavenie_set_vig_ant(_anchor_vlastne_slavenie);
				_set_chvalospev_vig_vian(modlitba);
				_spolocna_cast_set_vig_ev_pm(); // čítanie z omšového lekcionára na sviatky Panny Márie; netreba _vlastne_slavenie_set_vig_ev(_anchor_vlastne_slavenie);

				// doplnené modlitby cez deň
				modlitba = MODL_PREDPOLUDNIM;
				_bohorod_kcitanie(_anchor_vlastne_slavenie);
				_bohorod_modlitba;
				modlitba = MODL_NAPOLUDNIE;
				_bohorod_kcitanie(_anchor_vlastne_slavenie);
				_bohorod_modlitba;
				modlitba = MODL_POPOLUDNI;
				_bohorod_kcitanie(_anchor_vlastne_slavenie);
				_bohorod_modlitba;

				_set_zalmy_mcd_1nedela_or_doplnkova_psalmodia();

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)) {
					file_name_vlastny_kalendar(_global_kalendar);
					Log("  pre SJ: ide o slávnosť, TITULÁRNY SVIATOK SJ: _file = `%s', _anchor = %s...\n", _file, _anchor);

					modlitba = MODL_PRVE_VESPERY;
					_vlastne_slavenie_popis(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);

					modlitba = MODL_POSV_CITANIE;
					_vlastne_slavenie_popis(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);

					modlitba = MODL_RANNE_CHVALY;
					_vlastne_slavenie_popis(_anchor_vlastne_slavenie);
					_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);

					_vlastne_slavenie_popis_mcd(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba_mcd(_anchor_vlastne_slavenie);

					modlitba = MODL_VESPERY;
					_vlastne_slavenie_popis(_anchor_vlastne_slavenie);
					_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				}// kalendár pre KALENDAR_SK_SJ
			}// Panny Marie Bohorodicky

			// druha nedela po narodeni pana - 2. NEDEĽA PO NARODENÍ PÁNA | nie pre krajiny, kde sa Zjavenie Pána slávi v nedeľu medzi 2. a 8. januárom | BIT_OPT_0_ZJAVENIE_PANA_NEDELA
			else if ((_global_den.denvt == DEN_NEDELA) && (_global_den.mesiac - 1 == MES_JAN) && (!(isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA)))) {
				// prvé vešpery
				modlitba = MODL_PRVE_VESPERY;
				_vian1_hymnus;
				_vian1_kresponz;
				_vian1_2ne_kcitanie;
				_vian1_2ne_magnifikat;
				_vian1_2ne_prosby;
				_vian1_2ne_modlitba;
				_vian1_2ne_antifony;
				// ranné chvály
				modlitba = MODL_RANNE_CHVALY;
				_vian1_2ne_kcitanie;
				_vian1_2ne_benediktus;
				_vian1_2ne_prosby;
				_vian1_2ne_antifony;
				_vian1_2ne_modlitba;
				// druhé vešpery
				modlitba = MODL_VESPERY;
				_vian1_2ne_kcitanie;
				_vian1_2ne_magnifikat;
				_vian1_2ne_prosby;
				_vian1_2ne_antifony;
				_vian1_2ne_modlitba;

				// posvätné čítanie je zo dňa podľa dátumu

				// modlitba cez deň
				modlitba = MODL_PREDPOLUDNIM;
				_vian1_2ne_kcitanie;
				_vian1_kresponz;
				_vian1_2ne_modlitba;
				modlitba = MODL_NAPOLUDNIE;
				_vian1_2ne_kcitanie;
				_vian1_kresponz;
				_vian1_2ne_modlitba;
				modlitba = MODL_POPOLUDNI;
				_vian1_2ne_kcitanie;
				_vian1_kresponz;
				_vian1_2ne_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vian1_2ne_modlitba;
				// predĺžené slávenie vigílií v rámci posvätných čítaní | modlitba = MODL_POSV_CITANIE;
				_liturgicke_obdobie_set_vig_ant(modlitba);
				_set_chvalospev_vig_vian(modlitba);
				_liturgicke_obdobie_set_vig_ev(modlitba);

			}// druha nedela po narodeni pana - 2. NEDEĽA PO NARODENÍ PÁNA

			else if (_global_den.denvr == _global_r._SVATEJ_RODINY.denvr) {
				// sviatok svatej rodiny
				mystrcpy(_file, FILE_SV_RODINY, MAX_STR_AF_FILE);
				mystrcpy(_file_pc, FILE_SV_RODINY, MAX_STR_AF_FILE);
				mystrcpy(_anchor, ANCHOR_SV_RODINY, MAX_STR_AF_ANCHOR);
				mystrcpy(_anchor_vlastne_slavenie, ANCHOR_SV_RODINY, MAX_STR_AF_ANCHOR);
				Log("  ide o sviatok svatej rodiny: _file = `%s', _anchor = %s...\n", _file, _anchor);

				modlitba = MODL_PRVE_VESPERY;
				_set_zalmy_sviatok_panien(modlitba);
				_sv_rodiny_hymnus(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_sv_rodiny_kresponz(_anchor_vlastne_slavenie);
				_sv_rodiny_magnifikat(_anchor_vlastne_slavenie);
				_sv_rodiny_prosby(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				_sv_rodiny_antifony(_anchor_vlastne_slavenie);

				// invitatórium
				modlitba = MODL_INVITATORIUM;
				_vlastne_slavenie_invitat(_anchor_vlastne_slavenie);

				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_1nedele_rch();
				_sv_rodiny_hymnus(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_sv_rodiny_kresponz(_anchor_vlastne_slavenie);
				_sv_rodiny_benediktus(_anchor_vlastne_slavenie);
				_sv_rodiny_prosby(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				_sv_rodiny_antifony(_anchor_vlastne_slavenie);

				modlitba = MODL_VESPERY;
				_set_zalmy_sviatok_panien(modlitba);
				_sv_rodiny_hymnus(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_sv_rodiny_kresponz(_anchor_vlastne_slavenie);
				_sv_rodiny_magnifikat(_anchor_vlastne_slavenie);
				_sv_rodiny_prosby(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				_sv_rodiny_antifony(_anchor_vlastne_slavenie);

				// posvätné čítanie
				modlitba = MODL_POSV_CITANIE;
				_sv_rodiny_hymnus(_anchor_vlastne_slavenie);
				_set_zalmy_sviatok_marie(modlitba);
				_sv_rodiny_antifony(_anchor_vlastne_slavenie);
				_sv_rodiny_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_ine_1citanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_ine_2citanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				// predĺžené slávenie vigílií v rámci posvätných čítaní | modlitba = MODL_POSV_CITANIE;
				_vlastne_slavenie_set_vig_ant(_anchor_vlastne_slavenie);
				_set_chvalospev_vig_vian(modlitba);
				_vlastne_slavenie_set_vig_ev_litrok(_anchor_vlastne_slavenie, _global_den.litrok);

				// modlitba cez deň
				_set_zalmy_mcd_1nedela_or_doplnkova_psalmodia();

				modlitba = MODL_PREDPOLUDNIM;
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_sv_rodiny_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				// hoci sú vo vlastnej časti uvedené aj antifóny pre modlitbu cez deň, sú rovnaké ako pre vianočné obdobie, preto netreba nastavovať

				modlitba = MODL_NAPOLUDNIE;
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_sv_rodiny_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				// hoci sú vo vlastnej časti uvedené aj antifóny pre modlitbu cez deň, sú rovnaké ako pre vianočné obdobie, preto netreba nastavovať

				modlitba = MODL_POPOLUDNI;
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_sv_rodiny_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				// hoci sú vo vlastnej časti uvedené aj antifóny pre modlitbu cez deň, sú rovnaké ako pre vianočné obdobie, preto netreba nastavovať

			}// _global_den.denvr == _global_r._SVATEJ_RODINY.denvr
		}
		break;
// switch(litobd), case OBD_OKTAVA_NARODENIA -- end -------------------------------------------
// switch(litobd), case OBD_VIANOCNE_I -- end -------------------------------------------------

// switch(litobd), case OBD_VIANOCNE_II -- begin ----------------------------------------------

		// po slavnosti zjavenia pana
		case OBD_VIANOCNE_II: {
			Log("OBD_VIANOCNE_II\n");
// vianočné obdobie II
#define _vian2_hymnus {\
	sprintf(_anchor, "%s%s_%c%s", _special_anchor_prefix, nazov_OBD[OBD_VIANOCNE_II], pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_hymnus(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
		}\
				else{\
		_set_hymnus(modlitba, _file, _anchor);\
		set_LOG_litobd;\
				}\
			}
#define _zjv_hymnus {\
	sprintf(_anchor, "%s%s_%s%c%s", _special_anchor_prefix, nazov_OBD[OBD_VIANOCNE_II], ANCHOR_ZJAVENIE_PANA, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_hymnus(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
		}\
		else{\
		_set_hymnus(modlitba, _file, _anchor);\
		set_LOG_litobd;\
				}\
			}
#define _zjv_kcitanie {\
	sprintf(_anchor, "%s_%c%s%d", nazov_OBD[OBD_VIANOCNE_II], pismenko_modlitby(modlitba), ANCHOR_KCITANIE, 6 /* (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA))? 6: _global_den.den */); \
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian2_kresponz {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	if(modlitba != MODL_POSV_CITANIE){\
		sprintf(_anchor, "%s_%c%s", nazov_OBD[OBD_VIANOCNE_II], c, ANCHOR_KRESPONZ);\
	}\
	else {\
		sprintf(_anchor, "%s_%c%s_%d", nazov_OBD[OBD_VIANOCNE_II], c, ANCHOR_KRESPONZ, (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA))? (_global_den.denvr - zjavenie_pana(_global_den.rok) + 6): _global_den.den);\
	}\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_kresponz(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_kresponz(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
}
#define _vian2_prosby {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	sprintf(_anchor, "%s_%c%s%d", nazov_OBD[OBD_VIANOCNE_II], c, ANCHOR_PROSBY, (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA))? (_global_den.denvr - zjavenie_pana(_global_den.rok) + 6): _global_den.den);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian2_benediktus {\
	sprintf(_anchor, "%s_%c%s%d", nazov_OBD[OBD_VIANOCNE_II], pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA))? (_global_den.denvr - zjavenie_pana(_global_den.rok) + 6): _global_den.den);\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian2_magnifikat {\
	sprintf(_anchor, "%s_%c%s%d", nazov_OBD[OBD_VIANOCNE_II], pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA))? (_global_den.denvr - zjavenie_pana(_global_den.rok) + 6): _global_den.den);\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _vian2_modlitba {\
	sprintf(_anchor, "%s_%s%d", nazov_OBD[OBD_VIANOCNE_II], ANCHOR_MODLITBA, (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA))? (_global_den.denvr - zjavenie_pana(_global_den.rok) + 6): _global_den.den);\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
#define _zjv_antifony {\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VIANOCNE_II], ANCHOR_ZJAVENIE_PANA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_antifona1(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_antifona1(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VIANOCNE_II], ANCHOR_ZJAVENIE_PANA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_antifona2(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_antifona2(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VIANOCNE_II], ANCHOR_ZJAVENIE_PANA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_antifona3(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_antifona3(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
}
#define _vian2_citanie1 {\
	sprintf(_anchor, "%s_%c%s_%d", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_CITANIE1, (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA))? (_global_den.denvr - zjavenie_pana(_global_den.rok) + 6): _global_den.den);\
	_set_citanie1(modlitba, _file_pc, _anchor);\
	set_LOG_litobd_pc;\
}
#define _vian2_citanie2 {\
	sprintf(_anchor, "%s_%c%s_%d", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_CITANIE2, (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA))? (_global_den.denvr - zjavenie_pana(_global_den.rok) + 6): _global_den.den);\
	_set_citanie2(modlitba, _file_pc, _anchor);\
	set_LOG_litobd_pc;\
}

// vytvorené pre modlitbu cez deň podľa _vian1_mcd_antifony (to podľa _post1_mcd_antifony; porov. _adv_antifony_mcd)
// antifóny pre modlitbu cez deň sú rovnaké, použitý anchor ANCHOR_ANTIFONY
#define _vian2_mcd_antifony {\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[OBD_VIANOCNE_II], pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[OBD_VIANOCNE_II], pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[OBD_VIANOCNE_II], pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

			// tu v skutočnosti začína VIANOČNÉ OBDOBIE II.

			// invitatórium
			modlitba = MODL_INVITATORIUM;
			_obd_invitat;

			// ranné chvály
			modlitba = MODL_RANNE_CHVALY;
			_vian2_hymnus;
			// krátke čítanie nastavené neskôr podľa vian1
			_vian2_kresponz;
			_vian2_benediktus;
			_vian2_prosby;
			_vian2_modlitba;

			// vešpery
			modlitba = MODL_VESPERY;
			_vian2_hymnus;
			// krátke čítanie nastavené neskôr podľa vian1
			_vian2_kresponz;
			_vian2_magnifikat;
			_vian2_prosby;
			_vian2_modlitba;

			// posvätné čítanie
			modlitba = MODL_POSV_CITANIE;
			_vian2_hymnus;
			_vian2_kresponz;
			_vian2_citanie1;
			_vian2_citanie2;
			_vian2_modlitba;

			// modlitba cez deň
			modlitba = MODL_PREDPOLUDNIM;
			_vian2_hymnus;
			_vian2_mcd_antifony;
			// krátke čítanie nastavené neskôr podľa vian1
			_vian2_kresponz;
			_vian2_modlitba;

			modlitba = MODL_NAPOLUDNIE;
			_vian2_hymnus;
			_vian2_mcd_antifony;
			// krátke čítanie nastavené neskôr podľa vian1
			_vian2_kresponz;
			_vian2_modlitba;

			modlitba = MODL_POPOLUDNI;
			_vian2_hymnus;
			_vian2_mcd_antifony;
			// krátke čítanie nastavené neskôr podľa vian1
			_vian2_kresponz;
			_vian2_modlitba;

			if(_global_den.denvr == zjavenie_pana(_global_den.rok)){ // zjavenie Pána; bolo tu kedysi: if((_global_den.den == 6) && (_global_den.mesiac - 1 == MES_JAN))

				// odlišné nastavenie kotiev na príslušnom mieste pre krajiny, kde sa Zjavenie Pána slávi v nedeľu medzi 2. a 8. januárom | BIT_OPT_0_ZJAVENIE_PANA_NEDELA

				// prvé vešpery
				modlitba = MODL_PRVE_VESPERY;
				if (je_CZ_hymny_k_volnemu_vyberu){
					_zjv_hymnus;
				}
				else{
					_vian2_hymnus;
				}
				_zjv_antifony;
				_zjv_kcitanie;
				_vian2_kresponz;
				_vian2_magnifikat;
				_vian2_prosby;
				_vian2_modlitba;
				_set_zalmy_zjv(modlitba);

				// kompletórium
				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				// invitatórium netreba, nakoľko antifóna je rovnaká pre celé obdobie po zjavení pána

				// ranné chvály
				modlitba = MODL_RANNE_CHVALY;
				if (je_CZ_hymny_k_volnemu_vyberu){
					_zjv_hymnus;
				}
				_set_zalmy_zjv(modlitba);
				_zjv_kcitanie;
				_zjv_antifony;

				// druhé vešpery
				modlitba = MODL_VESPERY;
				if (je_CZ_hymny_k_volnemu_vyberu){
					_zjv_hymnus;
				}
				_set_zalmy_zjv(modlitba);
				_zjv_kcitanie;
				_zjv_antifony;

				// posvätné čítanie
				modlitba = MODL_POSV_CITANIE;
				if (je_CZ_hymny_k_volnemu_vyberu){
					_zjv_hymnus;
				}
				_set_zalmy_zjv(modlitba);
				_zjv_antifony;
				// predĺžené slávenie vigílií v rámci posvätných čítaní | modlitba = MODL_POSV_CITANIE;
				_liturgicke_obdobie_set_vig_ant(modlitba);
				_set_chvalospev_vig_vian(modlitba);
				_liturgicke_obdobie_set_vig_ev(modlitba);

				// modlitby cez deň
				modlitba = MODL_PREDPOLUDNIM;
				_set_zalmy_zjv(modlitba);
				_zjv_kcitanie;
				modlitba = MODL_NAPOLUDNIE;
				_set_zalmy_zjv(modlitba);
				_zjv_kcitanie;
				modlitba = MODL_POPOLUDNI;
				_set_zalmy_zjv(modlitba);
				_zjv_kcitanie;

			}// zjavenie pana

			// pôvodne bolo v cezročnom období; presunuté sem
			else if (_global_den.denvr == _global_r._KRST_KRISTA_PANA.denvr) {
				// no need to force the condition with: (tyzden == 1) && 
				// krst krista pana -- 1. nedela obdobia `cez rok'
				// niekedy môže padnúť aj na pondelok (ak sa Zjavenie Pána slávi v nedeľu, ktorá padne na 7. alebo 8. januára)
				mystrcpy(_file, FILE_KRST_PANA, MAX_STR_AF_FILE);
				mystrcpy(_file_pc, FILE_KRST_PANA, MAX_STR_AF_FILE); // kvôli vigílii
				// _file_pc ostáva nastavené pre OCR | kvôli define _vlastne_slavenie_set_vig_ant()
				mystrcpy(_anchor, ANCHOR_KRST_PANA, MAX_STR_AF_ANCHOR);
				mystrcpy(_anchor_vlastne_slavenie, ANCHOR_KRST_PANA, MAX_STR_AF_ANCHOR);
				Log("  ide o sviatok Krstu Krista Pána: _file = `%s', _anchor = %s...\n", _file, _anchor);

				modlitba = MODL_PRVE_VESPERY;
				_set_zalmy_sviatok_krstu(modlitba);
				_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
				_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

				// invitatórium
				modlitba = MODL_INVITATORIUM;
				_vlastne_slavenie_invitat(_anchor_vlastne_slavenie);

				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_sviatok_krstu(modlitba);
				_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_benediktus(_anchor_vlastne_slavenie);
				_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

				modlitba = MODL_VESPERY;
				_set_zalmy_sviatok_krstu(modlitba);
				_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
				_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_sviatok_krstu(modlitba);
				_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
				// hoci by mohli byť nastavené ako 1. nedeľa cezročného obdobia vyššie, predsa použijeme samostatný súbor a samostatne ich nastavíme; 2006-02-07
				_vlastne_slavenie_1citanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_2citanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				// predĺžené slávenie vigílií v rámci posvätných čítaní | modlitba = MODL_POSV_CITANIE;
				_vlastne_slavenie_set_vig_ant(_anchor_vlastne_slavenie);
				_set_chvalospev_vig_vian(modlitba);
				if (_global_jazyk == JAZYK_CZ) {
					_liturgicke_obdobie_set_vig_ev(modlitba);
				}
				else {
					_liturgicke_obdobie_set_vig_ev_tyzden(modlitba, ((tyzden MOD 8) == 0) ? 8 : (tyzden MOD 8)); // ako 1. cezročná nedeľa; zatiaľ nie je možnosť evanjelia, ktoré sa nečítalo v omši
				}

				modlitba = MODL_PREDPOLUDNIM;
				_set_zalmy_sviatok_krstu(modlitba);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				modlitba = MODL_NAPOLUDNIE;
				_set_zalmy_sviatok_krstu(modlitba);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				modlitba = MODL_POPOLUDNI;
				_set_zalmy_sviatok_krstu(modlitba);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
			}// krst krista pana

			else{
				// vsedny den vianocneho obdobia II -- citania podla vian.obd.I 
				// presne takto isto sa správajú aj krátke čítania pre modlitbu cez deň (ako pre krátke čítanie na ranné chvály)
				file_name_litobd(OBD_VIANOCNE_I);

				// odlišná úprava dátumu podľa toho, či sa ZJV slávi v nedeľu alebo 6.1.
				// pre ZJV on Sunday: den == 7 (pondelok), 8 (utorok), 9 (streda), 10 (štvrtok), 11 (piatok), 12 (sobota)
				// pre ZJV on 6.1.: den == 7 (7.1.), 8 (8.1.), 9 (9.1.), 10, 11, 12 (znamená daný 'den' v januári)
				_global_den.den = ((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA)) ? (_global_den.denvr - zjavenie_pana(_global_den.rok) + 6) : _global_den.den);

				// táto úprava _global_den.den sa ukázala ako nebezpečná -- po zmene treba vrátiť pôvodnú hodnotu
				if(_global_den.den == 8){
					modlitba = MODL_RANNE_CHVALY;
					_global_den.den = 31;
					_vian1_kcitanie;
					modlitba = MODL_PREDPOLUDNIM;
					_vian1_kcitanie;
					modlitba = MODL_NAPOLUDNIE;
					_vian1_kcitanie;
					modlitba = MODL_POPOLUDNI;
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
						modlitba = MODL_PREDPOLUDNIM;
						_vian1_kcitanie;
						modlitba = MODL_NAPOLUDNIE;
						_vian1_kcitanie;
						modlitba = MODL_POPOLUDNI;
						_vian1_kcitanie;
						modlitba = MODL_VESPERY;
						_vian1_kcitanie;
					}
					else{// den == 9, 10, 11, 12
						_global_den.den = _global_den.den - 7; // den == 2, 3, 4, 5
						modlitba = MODL_RANNE_CHVALY;
						_vian1_kcitanie;
						modlitba = MODL_PREDPOLUDNIM;
						_vian1_kcitanie;
						modlitba = MODL_NAPOLUDNIE;
						_vian1_kcitanie;
						modlitba = MODL_POPOLUDNI;
						_vian1_kcitanie;
						modlitba = MODL_VESPERY;
						_vian1_kcitanie;
					}
				}
			}// obycajny den vian. obd. II -- priradenie citania

			// restore/späť pôvodné nastavenia (pre niektoré dni vianočného obdobia boli zmenené); upozornil lamborghini2003@gmail.com
			_global_den.den = _pom_den;
			_global_den.mesiac = _pom_mesiac;
			_global_den.rok = _pom_rok;
		}
		break;
// switch(litobd), case OBD_VIANOCNE_II -- end ------------------------------------------------

// switch(litobd), case OBD_CEZ_ROK -- begin --------------------------------------------------
		case OBD_CEZ_ROK: {
			Log("OBD_CEZ_ROK\n");

			// tu v skutočnosti začína CEZROČNÉ OBDOBIE

			// nastavenie možnosti alternatívnych hymnov pre posv. čítanie a kompletórium
			_set_hymnus_alternativy_obdobie(litobd);

			// najprv treba skontrolovat, ci nejde o nedelu, na ktoru pripadol sviatok Pana/svatych; ak ano, tak nenastavuj nic, lebo vsetko sa nastavilo vo funkcii sviatky_svatych()
			if((_global_den.denvt == DEN_NEDELA) && (PODMIENKA_SVIATKY_PANA_SVATYCH_PREDNOST_PRED_NEDELOU_OCR)){
				Log("PODMIENKA_SVIATKY_PANA_SVATYCH_PREDNOST_PRED_NEDELOU_OCR, so break...\n");
				break;
			}

			// Krst Krista Pána je zvyčajne nedeľa, ale môže pripadnúť na pondelok 8. alebo 9. januára (v krajinách, kde sa Zjavenie Pána slávi v nedeľu, ak táto pripadne na 7. alebo 8. januára) -- presunuté do vianočného obdobia (OBD_VIANOCNE_II)

			// Najsv. Kristovho tela a krvi je zvyčajne štvrtok (11.-ty deň po ZDS), ale v krajinách, kde nie je prikázaným sviatkom, slávi sa v nedeľu; v breviar.cpp sa používa define TELAKRVI
			if(_global_den.denvr == (_global_r._ZOSLANIE_DUCHA_SV.denvr + ((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_TELAKRVI_NEDELA))? 14: 11))){
				// najsv. kristovho tela a krvi
				mystrcpy(_file, FILE_TELA_A_KRVI, MAX_STR_AF_FILE);
				mystrcpy(_file_pc, FILE_TELA_A_KRVI, MAX_STR_AF_FILE); // kvôli define _vlastne_slavenie_set_vig_ant()
				mystrcpy(_anchor, ANCHOR_TELA_A_KRVI, MAX_STR_AF_ANCHOR);
				mystrcpy(_anchor_vlastne_slavenie, ANCHOR_TELA_A_KRVI, MAX_STR_AF_ANCHOR);
				Log("  ide o slavnost najsv. kristovho tela a krvi: _file = `%s', _anchor = %s...\n", _file, _anchor);

				// kompletórium
				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				// prvé vešpery
				modlitba = MODL_PRVE_VESPERY;
				_set_zalmy_telakrvi(modlitba);
				_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
				_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

				// invitatórium
				modlitba = MODL_INVITATORIUM;
				_vlastne_slavenie_invitat(_anchor_vlastne_slavenie);

				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_telakrvi(modlitba);
				_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_benediktus(_anchor_vlastne_slavenie);
				_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

				modlitba = MODL_VESPERY;
				_set_zalmy_telakrvi(modlitba);
				_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
				_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_telakrvi(modlitba);
				_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
				_vlastne_slavenie_1citanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_2citanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				// predĺžené slávenie vigílií v rámci posvätných čítaní | modlitba = MODL_POSV_CITANIE;
				_vlastne_slavenie_set_vig_ant(_anchor_vlastne_slavenie);
				_set_chvalospev_vig_tk(modlitba);
				_vlastne_slavenie_set_vig_ev(_anchor_vlastne_slavenie);

				modlitba = MODL_PREDPOLUDNIM;
				_set_zalmy_telakrvi(modlitba);
				if ((_global_jazyk == JAZYK_CZ) && (!isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_CZ_HYMNY_VYBER))){
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
				}
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				modlitba = MODL_NAPOLUDNIE;
				_set_zalmy_telakrvi(modlitba);
				if ((_global_jazyk == JAZYK_CZ) && (!isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_CZ_HYMNY_VYBER))){
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
				}
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				modlitba = MODL_POPOLUDNI;
				_set_zalmy_telakrvi(modlitba);
				if ((_global_jazyk == JAZYK_CZ) && (!isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_CZ_HYMNY_VYBER))){
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
				}
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
			}// tela a krvi
			// nedeľa v Cezročnom období
			else if(_global_den.denvt == DEN_NEDELA){
				Log("--- nedela OCR, nastavujem modlitbu dna...\n");
				// ak je specialna, tak _file sa nastavi v dalsom
				file_name_litobd(OBD_CEZ_ROK);
				// benediktus
				modlitba = MODL_RANNE_CHVALY;
				sprintf(_anchor, "_%d%s_%c%s%c", tyzden, nazov_DN_asci[den], /* 'NE', nedela */ pismenko_modlitby(MODL_RANNE_CHVALY), ANCHOR_BENEDIKTUS, _global_den.litrok);
				_set_benediktus(MODL_RANNE_CHVALY, _file, _anchor);
				set_LOG_litobd;
				// magnifikat 1
				modlitba = MODL_PRVE_VESPERY;
				sprintf(_anchor, "_%d%s_%c%s%c", tyzden, nazov_DN_asci[den], /* 'NE', nedela */ pismenko_modlitby(MODL_PRVE_VESPERY), ANCHOR_MAGNIFIKAT, _global_den.litrok);
				_set_magnifikat(MODL_PRVE_VESPERY, _file, _anchor);
				set_LOG_litobd;
				// magnifikat v
				modlitba = MODL_VESPERY;
				sprintf(_anchor, "_%d%s_%c%s%c", tyzden, nazov_DN_asci[den], /* 'NE', nedela */ pismenko_modlitby(MODL_VESPERY), ANCHOR_MAGNIFIKAT, _global_den.litrok);
				_set_magnifikat(MODL_VESPERY, _file, _anchor);
				set_LOG_litobd;
				// modlitba
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
				// modlitba pre posvatne citania a modlitbu cez den
				modlitba = MODL_PREDPOLUDNIM;
				_set_modlitba(MODL_PREDPOLUDNIM, _file, _anchor);
				set_LOG_litobd;
				modlitba = MODL_NAPOLUDNIE;
				_set_modlitba(MODL_NAPOLUDNIE, _file, _anchor);
				set_LOG_litobd;
				modlitba = MODL_POPOLUDNI;
				_set_modlitba(MODL_POPOLUDNI, _file, _anchor);
				set_LOG_litobd;
				modlitba = MODL_POSV_CITANIE;
				_set_modlitba(MODL_POSV_CITANIE, _file, _anchor);
				set_LOG_litobd;

				// posvatne citanie presunuté sem a do časti "nie nedeľa" kvôli napr. Najsv. Trojici
				Log("posvatne citanie...\n");

				// idem nastavit _file_pc_tyzden podla tyzdna
				file_name_litobd_pc_tyzden(litobd, tyzden);
				Log("  _file_pc_tyzden == %s\n", _file_pc_tyzden);

				modlitba = MODL_POSV_CITANIE;

				// 1. čítanie
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_CITANIE1);
				_set_citanie1(modlitba, _file_pc_tyzden, _anchor);
				set_LOG_litobd_pc_tyzden;
				// Log(_global_modl_posv_citanie);

				// 2. čítanie
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_CITANIE2);
				// Log("docasne - %s\n", _file_pc_tyzden);
				// Log("docasne - %s\n", _anchor);
				_set_citanie2(modlitba, _file_pc_tyzden, _anchor);
				set_LOG_litobd_pc_tyzden;
				// Log(_global_modl_posv_citanie);

				// predĺžené slávenie vigílií v rámci posvätných čítaní | modlitba = MODL_POSV_CITANIE;
				_liturgicke_obdobie_set_vig_ant(modlitba);
				_set_chvalospev_vig_ocr(modlitba);
				_liturgicke_obdobie_set_vig_ev_tyzden(modlitba, ((tyzden MOD 8) == 0) ? 8 : (tyzden MOD 8));

				if(_global_den.denvr == TROJICA){
					// najsv. trojice
					mystrcpy(_file, FILE_NAJSV_TROJICE, MAX_STR_AF_FILE);
					mystrcpy(_file_pc, FILE_NAJSV_TROJICE, MAX_STR_AF_FILE); // kvôli define _vlastne_slavenie_set_vig_ant()
					mystrcpy(_anchor, ANCHOR_NAJSV_TROJICE, MAX_STR_AF_ANCHOR);
					mystrcpy(_anchor_vlastne_slavenie, ANCHOR_NAJSV_TROJICE, MAX_STR_AF_ANCHOR);
					Log("  ide o slavnost najsv. trojice: _file = `%s', _anchor = %s...\n", _file, _anchor);

					modlitba = MODL_PRVE_VESPERY;
					_set_zalmy_najsv_trojice(modlitba);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
					_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

					// invitatórium
					modlitba = MODL_INVITATORIUM;
					_vlastne_slavenie_invitat(_anchor_vlastne_slavenie);

					modlitba = MODL_RANNE_CHVALY;
					_set_zalmy_najsv_trojice(modlitba);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_benediktus(_anchor_vlastne_slavenie);
					_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

					modlitba = MODL_VESPERY;
					_set_zalmy_najsv_trojice(modlitba);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
					_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

					modlitba = MODL_POSV_CITANIE;
					_set_zalmy_najsv_trojice(modlitba);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					_vlastne_slavenie_1citanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_2citanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					// predĺžené slávenie vigílií v rámci posvätných čítaní | modlitba = MODL_POSV_CITANIE;
					_vlastne_slavenie_set_vig_ant(_anchor_vlastne_slavenie);
					// ToDo chválospevy
					_vlastne_slavenie_set_vig_ev(_anchor_vlastne_slavenie);

					modlitba = MODL_PREDPOLUDNIM;
					_set_zalmy_najsv_trojice(modlitba);
					if (je_CZ_nie_hymny_k_volnemu_vyberu) {
						_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					}
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					modlitba = MODL_NAPOLUDNIE;
					_set_zalmy_najsv_trojice(modlitba);
					if (je_CZ_nie_hymny_k_volnemu_vyberu) {
						_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					}
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					modlitba = MODL_POPOLUDNI;
					_set_zalmy_najsv_trojice(modlitba);
					if (je_CZ_nie_hymny_k_volnemu_vyberu) {
						_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					}
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				}// najsv. trojice
				// pre redemptoristov: 3. nedeľa v júli
				else if((((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_CSSR)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_CSSR))) && (_global_den.mesiac - 1 == MES_JUL) && (_global_den.den > 14) && (_global_den.den <= 21)){
					file_name_vlastny_kalendar(_global_kalendar);
					mystrcpy(_anchor, ANCHOR_CSSR_TITUL, MAX_STR_AF_ANCHOR);
					mystrcpy(_anchor_vlastne_slavenie, ANCHOR_CSSR_TITUL, MAX_STR_AF_ANCHOR);
					Log("  pre CSSR: ide o slávnosť NAJSVÄTEJŠIEHO VYKUPITEĽA, TITULÁRNY SVIATOK KONGREGÁCIE: _file = `%s', _anchor = %s...\n", _file, _anchor);

					modlitba = MODL_PRVE_VESPERY;
					_set_zalmy_cssr_titul(modlitba);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
					_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

					modlitba = MODL_INVITATORIUM;
					_vlastne_slavenie_invitat(_anchor_vlastne_slavenie);

					modlitba = MODL_POSV_CITANIE;
					_set_zalmy_cssr_titul(modlitba);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_1citanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_2citanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

					modlitba = MODL_RANNE_CHVALY;
					_set_zalmy_cssr_titul(modlitba);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_benediktus(_anchor_vlastne_slavenie);
					_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

					modlitba = MODL_VESPERY;
					_set_zalmy_cssr_titul(modlitba);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
					_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

					modlitba = MODL_PREDPOLUDNIM;
					_set_zalmy_1nedele_mcd();
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					modlitba = MODL_NAPOLUDNIE;
					_set_zalmy_1nedele_mcd();
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					modlitba = MODL_POPOLUDNI;
					_set_zalmy_1nedele_mcd();
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);

				}// pre redemptoristov: 3. nedeľa v júli

				else if (tyzden == 34) {
					// krista krala -- 34. nedela obdobia `cez rok'
					mystrcpy(_file, FILE_KRISTA_KRALA, MAX_STR_AF_FILE);
					mystrcpy(_anchor, ANCHOR_KRISTA_KRALA, MAX_STR_AF_ANCHOR);
					mystrcpy(_anchor_vlastne_slavenie, ANCHOR_KRISTA_KRALA, MAX_STR_AF_ANCHOR);
					Log("  ide o slavnost krista krala: _file = `%s', _anchor = %s...\n", _file, _anchor);

					modlitba = MODL_PRVE_VESPERY;
					_set_zalmy_krista_krala(modlitba);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
					_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

					// invitatórium
					modlitba = MODL_INVITATORIUM;
					_vlastne_slavenie_invitat(_anchor_vlastne_slavenie);

					modlitba = MODL_RANNE_CHVALY;
					_set_zalmy_krista_krala(modlitba);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_benediktus(_anchor_vlastne_slavenie);
					_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

					// posvätné čítanie
					modlitba = MODL_POSV_CITANIE;
					_set_zalmy_krista_krala(modlitba);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					// bolo tu síce uvedené "sú nastavené ako 34. nedeľa cezročného obdobia vyššie", ale nastavovali sa z cezročného obdobia; Vlado Kiš ma upozornil, že krátke responzórium má byť zo slávnosti Krista Kráľa
					// _vlastne_slavenie_1citanie(_anchor_vlastne_slavenie);
					// _vlastne_slavenie_2citanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					// posvätné čítanie -- predĺžené slávenie vigílie
					modlitba = MODL_POSV_CITANIE;
					_vlastne_slavenie_set_vig_ant(_anchor_vlastne_slavenie);
					_set_chvalospev_vig_krkrala(modlitba);
					_vlastne_slavenie_set_vig_ev(_anchor_vlastne_slavenie);

					modlitba = MODL_VESPERY;
					_set_zalmy_krista_krala(modlitba);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
					_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

					modlitba = MODL_PREDPOLUDNIM;
					if (_global_jazyk == JAZYK_CZ) {
						_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					}
					_set_zalmy_krista_krala(modlitba);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					modlitba = MODL_NAPOLUDNIE;
					if (_global_jazyk == JAZYK_CZ) {
						_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					}
					_set_zalmy_krista_krala(modlitba);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					modlitba = MODL_POPOLUDNI;
					if (_global_jazyk == JAZYK_CZ) {
						_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					}
					_set_zalmy_krista_krala(modlitba);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				}// krista krala
			}// nedeľa v období cez rok (cezročnom období)

			// féria v Cezročnom období
			else{
				// nie je nedela, ale len bezny den - feria - v obdobi cez rok
				Log("--- obdobie cez rok, nie nedela...\n");

				// posvatne citanie presunuté sem (aj do nedele)
				Log("posvatne citanie...\n");

				// idem nastavit _file_pc_tyzden podla tyzdna
				file_name_litobd_pc_tyzden(litobd, tyzden);
				Log("  _file_pc_tyzden == %s\n", _file_pc_tyzden);

				modlitba = MODL_POSV_CITANIE;

				// 1. čítanie
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_CITANIE1);
				_set_citanie1(modlitba, _file_pc_tyzden, _anchor);
				set_LOG_litobd_pc_tyzden;
				// Log(_global_modl_posv_citanie);

				// 2. čítanie
				sprintf(_anchor, "%s%d%s%c_%s",
					nazov_OBD[litobd],
					tyzden,
					nazov_DN_asci[den],
					pismenko_modlitby(modlitba),
					ANCHOR_CITANIE2);
				// Log("docasne - %s\n", _file_pc_tyzden);
				// Log("docasne - %s\n", _anchor);
				_set_citanie2(modlitba, _file_pc_tyzden, _anchor);
				set_LOG_litobd_pc_tyzden;
				// Log(_global_modl_posv_citanie);

				if (tyzden == 34) {
					// 34. týždeň Cezročného obdobia; využijeme nastavenie _file_pc_tyzden
					if (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_OCR_34_HYMNS)) {

						// nastavenie hymnov

						modlitba = MODL_RANNE_CHVALY;

						sprintf(_anchor, "%s%d%c_%s", nazov_OBD[litobd], tyzden, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);
						_set_hymnus(modlitba, _file_pc_tyzden, _anchor);
						set_LOG_litobd;

						modlitba = MODL_VESPERY;

						sprintf(_anchor, "%s%d%c_%s", nazov_OBD[litobd], tyzden, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);
						_set_hymnus(modlitba, _file_pc_tyzden, _anchor);
						set_LOG_litobd;

						modlitba = MODL_POSV_CITANIE;

						sprintf(_anchor, "%s%d%c_%s", nazov_OBD[litobd], tyzden, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);
						_set_hymnus(modlitba, _file_pc_tyzden, _anchor);
						set_LOG_litobd;

						if (_global_jazyk == JAZYK_CZ) {
							// CZ has special hymn also for prayer during the day

							modlitba = MODL_PREDPOLUDNIM;

							sprintf(_anchor, "%s%d%c_%s", nazov_OBD[litobd], tyzden, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);
							_set_hymnus(modlitba, _file_pc_tyzden, _anchor);
							set_LOG_litobd;

							modlitba = MODL_NAPOLUDNIE;

							sprintf(_anchor, "%s%d%c_%s", nazov_OBD[litobd], tyzden, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);
							_set_hymnus(modlitba, _file_pc_tyzden, _anchor);
							set_LOG_litobd;

							modlitba = MODL_POPOLUDNI;

							sprintf(_anchor, "%s%d%c_%s", nazov_OBD[litobd], tyzden, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);
							_set_hymnus(modlitba, _file_pc_tyzden, _anchor);
							set_LOG_litobd;
						}
					}
				}

				if (_global_den.denvr == SRDCA) {
					slavnost_srdca(litobd);
				}// srdca
				else if (_global_den.denvr == KRISTA_KNAZA) {
					// Nášho Pána Ježiša Krista, najvyššieho a večného kňaza
					mystrcpy(_file, FILE_KNAZA, MAX_STR_AF_FILE);
					mystrcpy(_anchor, ANCHOR_KNAZA, MAX_STR_AF_ANCHOR);
					mystrcpy(_anchor_vlastne_slavenie, ANCHOR_KNAZA, MAX_STR_AF_ANCHOR);
					Log("  ide o sviatok Nášho Pána Ježiša Krista, najvyššieho a večného kňaza: _file = `%s', _anchor = %s...\n", _file, _anchor);

					// invitatórium
					modlitba = MODL_INVITATORIUM;
					_vlastne_slavenie_invitat(_anchor_vlastne_slavenie);

					modlitba = MODL_RANNE_CHVALY;
					_set_zalmy_knaza(modlitba);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_benediktus(_anchor_vlastne_slavenie);
					_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

					modlitba = MODL_VESPERY;
					_set_zalmy_knaza(modlitba);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
					_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

					modlitba = MODL_POSV_CITANIE;
					_set_zalmy_knaza(modlitba);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					_vlastne_slavenie_1citanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_2citanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					// posvätné čítanie -- predĺžené slávenie vigílie
					modlitba = MODL_POSV_CITANIE;
					_vlastne_slavenie_set_vig_ant(_anchor_vlastne_slavenie);
					_set_chvalospev_vig_knaza(modlitba);
					_vlastne_slavenie_set_vig_ev(_anchor_vlastne_slavenie);

					modlitba = MODL_PREDPOLUDNIM;
					// psalmódia zo všedného dňa okrem antifón
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					modlitba = MODL_NAPOLUDNIE;
					// psalmódia zo všedného dňa okrem antifón
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
					modlitba = MODL_POPOLUDNI;
					// psalmódia zo všedného dňa okrem antifón
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				}// knaza
				else if (_global_den.denvr == SRDPM) {
					// neposkvrneneho srdca prebl. panny marie
					Log("  (hoci tu nic nenastavujem) ide o spomienku neposkvrneneho srdca prebl. panny marie\n");
				}
				else if (_global_den.denvr == MARIE_MATKY_CIRKVI) {
					// panny marie matky cirkvi
					Log("  (hoci tu nic nenastavujem) ide o spomienku panny marie matky cirkvi\n");
				}
				else {
					// posvatne citania doplnena modlitba - je z prislusnej nedele OCR
					Log("--- modlitba dna pre bezne dni OCR je z prislusnej nedele...\n");
					modlitba = MODL_POSV_CITANIE;
					// modlitba
					sprintf(_anchor, "_%d%s_%s", tyzden, nazov_DN_asci[DEN_NEDELA], ANCHOR_MODLITBA);
					modlitba = MODL_POSV_CITANIE;
					_set_modlitba(MODL_POSV_CITANIE, _file, _anchor);
					set_LOG_litobd;
				}
			}// nie nedeľa
		}// case OBD_CEZ_ROK
		break;
// switch(litobd), case OBD_CEZ_ROK -- end ----------------------------------------------------

// switch(litobd), case OBD_POSTNE_I -- begin -------------------------------------------------

		// do soboty v piatom tyzdni
		case OBD_POSTNE_I:
			Log("OBD_POSTNE_I\n");

// pre modlitbu cez deň aj pre nedeľu hymnus ako pre všedný deň.
#define _post1_hymnus {\
	if((den == DEN_NEDELA)\
		&& (modlitba != MODL_PREDPOLUDNIM) && (modlitba != MODL_NAPOLUDNIE) && (modlitba != MODL_POPOLUDNI)){\
		sprintf(_anchor, "%s%s_%c%s%s", _special_anchor_prefix, nazov_OBD[litobd], pismenko_modlitby(modlitba), nazov_DN_asci[den], ANCHOR_HYMNUS);\
	}\
	else{\
		sprintf(_anchor, "%s%s_%c%s", _special_anchor_prefix, nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	}\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_hymnus(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_hymnus(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
}

#define _post1_citanie1 {\
	sprintf(_anchor, "%s_%c%s_%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_CITANIE1, tyzden, nazov_DN_asci[den]);\
	_set_citanie1(modlitba, _file_pc, _anchor);\
	set_LOG_litobd_pc;\
}
// use _special_anchor_prefix2 prefix according to BIT_OPT_0_ALTERNATIVE_READINGS
#define _post1_citanie2 {\
	sprintf(_anchor, "%s%s_%c%s_%d%s", _special_anchor_prefix2, nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_CITANIE2, tyzden, nazov_DN_asci[den]);\
	_set_citanie2(modlitba, _file_pc, _anchor);\
	set_LOG_litobd_pc;\
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

// pre modlitbu cez deň platí to isté čo pre bežný deň, t.j. responzá sú rovnaké. | jediná zmena: aj pre nedeľu pre mcd platí to, čo pre všedný deň.
#define _post1_kresponz {\
	if((den == DEN_NEDELA) && (modlitba == MODL_POSV_CITANIE)){\
		sprintf(_anchor, "%s_%c%s%s%d", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ, nazov_DN_asci[den], tyzden);\
	}\
	else if(((den == DEN_NEDELA) || (modlitba == MODL_POSV_CITANIE))\
		&& (modlitba != MODL_PREDPOLUDNIM) && (modlitba != MODL_NAPOLUDNIE) && (modlitba != MODL_POPOLUDNI)){\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ, nazov_DN_asci[den]);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	}\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_kresponz(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_kresponz(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
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

// antifóny pre modlitbu cez deň - sú rovnaké, použitý anchor ANCHOR_ANTIFONY
#define _post1_mcd_antifony {\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

			// tu v skutočnosti začína POSTNE OBDOBIE I.

			t = tyzden MOD 2;

			// kompletórium v pôstnom období
			modlitba = MODL_KOMPLETORIUM;
			set_hymnus_kompletorium_obd(den, tyzzal, modlitba, litobd);

			// invitatórium
			modlitba = MODL_INVITATORIUM;
			if (_global_jazyk == JAZYK_CZ_OP) {
				_obd_invitat;
			}
			else {
				_obd_invitat_viac(litobd, modlitba);
			}

			// ranné chvály
			modlitba = MODL_RANNE_CHVALY;
			_post1_hymnus;
			_post1_kcitanie;
			_post1_kresponz;
			_post1_benediktus;
			_post1_prosby;
			_post1_modlitba;

			// vešpery
			modlitba = MODL_VESPERY;
			_post1_hymnus;
			_post1_kcitanie;
			_post1_kresponz;
			_post1_magnifikat;
			_post1_prosby;
			_post1_modlitba;

			// posvätné čítanie
			modlitba = MODL_POSV_CITANIE;
			_post1_hymnus;
			_post1_citanie1;
			_post1_citanie2;
			_post1_kresponz;
			_post1_modlitba;

			// modlitba cez deň MODL_PREDPOLUDNIM + MODL_NAPOLUDNIE + MODL_POPOLUDNI
			modlitba = MODL_PREDPOLUDNIM;
			_post1_hymnus;
			_post1_mcd_antifony;
			_post1_kcitanie;
			_post1_kresponz;
			_post1_modlitba;
			modlitba = MODL_NAPOLUDNIE;
			_post1_hymnus;
			_post1_mcd_antifony;
			_post1_kcitanie;
			_post1_kresponz;
			_post1_modlitba;
			modlitba = MODL_POPOLUDNI;
			_post1_hymnus;
			_post1_mcd_antifony;
			_post1_kcitanie;
			_post1_kresponz;
			_post1_modlitba;

			if (den == DEN_NEDELA) {

				// prvé vešpery
				modlitba = MODL_PRVE_VESPERY;
				_post1_hymnus;
				_post1_ne_antifony;
				_post1_kcitanie;
				_post1_kresponz;
				_post1_magnifikat;
				_post1_prosby;
				_post1_modlitba;
				// ranné chvály
				modlitba = MODL_RANNE_CHVALY;
				_post1_ne_antifony;
				// druhé vešpery
				modlitba = MODL_VESPERY;
				_post1_ne_antifony;
				// posvätné čítanie -- predĺžené slávenie vigílie
				modlitba = MODL_POSV_CITANIE;
				_liturgicke_obdobie_set_vig_ant(modlitba);
				_set_chvalospev_vig_post(modlitba);
				_liturgicke_obdobie_set_vig_ev_tyzden(modlitba, tyzden);

			}// nedeľa
			else {
				// špeciálne pre Popolcovú stredu
				if (_global_den.denvr == POPOLCOVA_STREDA) {

					Log("liturgicke_obdobie(): POPOLCOVA_STREDA\n...");
					// Log("_global_den.denvt == %d\n", _global_den.denvt);

					if (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_POPOL_STREDA_PSALMODIA)) {
						set_antifony(DEN_PIATOK, 3, zvazok_breviara[litobd], MODL_RANNE_CHVALY);
						set_zalm(1, MODL_RANNE_CHVALY, "z51.htm", "ZALM51");
						set_zalm(2, MODL_RANNE_CHVALY, "ch_jer14.htm", "CHVAL_JER14");
						// možnosť zvoliť žalm 95
						if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALM95)) {
							set_zalm(3, MODL_RANNE_CHVALY, "z95.htm", "ZALM95");
						}
						else {
							set_zalm(3, MODL_RANNE_CHVALY, "z100.htm", "ZALM100");
						}
					}
				}
			}// nie nedeľa
			break;
// switch(litobd), case OBD_POSTNE_I -- end ---------------------------------------------------

// switch(litobd), case OBD_POSTNE_II -- begin ------------------------------------------------

		// velky tyzden
		case OBD_POSTNE_II_VELKY_TYZDEN:
			Log("OBD_POSTNE_II_VELKY_TYZDEN\n");

// pre modlitbu cez deň (okrem nedele) je hymnus ako pre pôstne obdobie I.
// pre Kvetnú nedeľu sa berie vlastný hymnus len pre jednu z hodiniek; zvolíme tú, pre ktorú sa neberie doplnková psalmódia
// pre český breviář sa na Kvetnú nedeľu kvôli hymnu "Každá neděle je vlastně neděle Květná" berie vlastná kotva
#define _post2_hymnus {\
	if(((den == DEN_STVRTOK) && (modlitba == MODL_VESPERY))\
	|| ((den == DEN_NEDELA) && (((!(isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA))) && (je_modlitba_cez_den(modlitba))) || (_global_jazyk == JAZYK_CZ)))){\
		sprintf(_anchor, "%s%s_%c%s%s", _special_anchor_prefix, nazov_OBD[litobd], pismenko_modlitby(modlitba), nazov_DN_asci[den], ANCHOR_HYMNUS);\
	}\
	else{\
		sprintf(_anchor, "%s%s_%c%s", _special_anchor_prefix, nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	}\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_hymnus(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_hymnus(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
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
// doplnené posvätné čítanie 
// modlitba cez deň aj posv. čítanie majú responzórium rovnaké, či je alebo nie je nedeľa
#define _post2_kresponz {\
	if(((den == DEN_STVRTOK) && (modlitba == MODL_VESPERY)) || ((den == DEN_NEDELA) && (modlitba != MODL_PREDPOLUDNIM) && (modlitba != MODL_NAPOLUDNIE) && (modlitba != MODL_POPOLUDNI) && (modlitba != MODL_POSV_CITANIE))){\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ, nazov_DN_asci[den]);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	}\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_kresponz(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_kresponz(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
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
// odlišná modlitba je len pre vešpery na Zelený štvrtok
#define _post2_modlitba {\
	if((den == DEN_STVRTOK) && (modlitba == MODL_VESPERY)){\
		sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_MODLITBA, tyzden, nazov_DN_asci[den]);\
	}\
	else{\
		sprintf(_anchor, "%s_%s%d%s", nazov_OBD[litobd], ANCHOR_MODLITBA, tyzden, nazov_DN_asci[den]);\
	}\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
// doplnené posvätné čítanie
#define _post2_antifony {\
	sprintf(_anchor, "%s_%d%s%c%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_antifona1(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_antifona1(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
	sprintf(_anchor, "%s_%d%s%c%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_antifona2(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_antifona2(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
	sprintf(_anchor, "%s_%d%s%c%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_antifona3(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_antifona3(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
}
// posvätné čítanie
#define _post2_citanie1 {\
	sprintf(_anchor, "%s_%c%s_%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_CITANIE1, tyzden, nazov_DN_asci[den]);\
	_set_citanie1(modlitba, _file_pc, _anchor);\
	set_LOG_litobd_pc;\
}
// use _special_anchor_prefix2 prefix according to BIT_OPT_0_ALTERNATIVE_READINGS
#define _post2_citanie2 {\
	sprintf(_anchor, "%s%s_%c%s_%d%s", _special_anchor_prefix2, nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_CITANIE2, tyzden, nazov_DN_asci[den]);\
	_set_citanie2(modlitba, _file_pc, _anchor);\
	set_LOG_litobd_pc;\
}

// antifóny pre modlitbu cez deň - sú rovnaké, použitý anchor ANCHOR_ANTIFONY
#define _post2_mcd_antifony {\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
// pre popis vešpier veľkonočného trojdnia (vrátane zeleného štvrtka)
#define _vtroj_popis {\
	sprintf(_anchor, "%s_%c%s_%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_POPIS, nazov_DN_asci[den]);\
	if(modlitba == MODL_POSV_CITANIE){\
		set_popis(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		set_popis(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
}
#define _vtroj_prosby {\
	sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_PROSBY, nazov_DN_asci[den]);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

			// tu v skutočnosti začína POSTNE OBDOBIE II. (Svätý týždeň)

			// kompletórium vo Svätom týždni
			modlitba = MODL_KOMPLETORIUM;

			// Štvrtok Svätého týždňa (Zelený štvrtok) má modlitbu a krátky responz z nedeľného 2. kompletória (ako na slávnosti)
			if(den == DEN_STVRTOK){
				_vtroj_popis;
				_set_kompletorium_slavnost(modlitba);
				set_hymnus_kompletorium_obd(den, tyzzal, modlitba, litobd);
				set_kresponz_kompletorium_obd(den, modlitba, litobd);
			}
			else{
				set_hymnus_kompletorium_obd(den, tyzzal, modlitba, litobd);
			}

			// invitatórium
			modlitba = MODL_INVITATORIUM;
			_obd_invitat;

			// ranné chvály
			modlitba = MODL_RANNE_CHVALY;
			_post2_hymnus;
			_post2_antifony;
			_post2_kcitanie;
			_post2_kresponz;
			_post2_benediktus;
			_post2_prosby;
			_post2_modlitba;

			// vešpery
			modlitba = MODL_VESPERY;
			_post2_hymnus;
			_post2_antifony;
			_post2_kcitanie;
			_post2_kresponz;
			_post2_magnifikat;
			_post2_prosby;
			_post2_modlitba;

			// posvätné čítanie
			modlitba = MODL_POSV_CITANIE;
			_post2_hymnus;
			_post2_citanie1;
			_post2_citanie2;
			_post2_kresponz;
			_post2_modlitba;

			// špeciálne pre Štvrtok Svätého týždňa (Zelený štvrtok)
			if (_global_den.denvr == ZELENY_STVRTOK) {

				Log("liturgicke_obdobie(): ZELENY_STVRTOK\n...");
				// Log("_global_den.denvt == %d\n", _global_den.denvt);

				if (isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_ZELENY_STVRTOK_PSALMODIA)) {
					set_antifony(DEN_PIATOK, 3, zvazok_breviara[litobd], MODL_POSV_CITANIE);
					set_zalm(1, MODL_POSV_CITANIE, "z69.htm", "ZALM69_I");
					set_zalm(2, MODL_POSV_CITANIE, "z69.htm", "ZALM69_II");
					set_zalm(3, MODL_POSV_CITANIE, "z69.htm", "ZALM69_III");
				}
			}

			// modlitba cez deň MODL_PREDPOLUDNIM + MODL_NAPOLUDNIE + MODL_POPOLUDNI
			modlitba = MODL_PREDPOLUDNIM;
			_post2_hymnus;
			_post2_mcd_antifony;
			_post2_kcitanie;
			_post2_kresponz;
			_post2_modlitba;
			modlitba = MODL_NAPOLUDNIE;
			_post2_hymnus;
			_post2_mcd_antifony;
			_post2_kcitanie;
			_post2_kresponz;
			_post2_modlitba;
			modlitba = MODL_POPOLUDNI;
			_post2_hymnus;
			_post2_mcd_antifony;
			_post2_kcitanie;
			_post2_kresponz;
			_post2_modlitba;

			if(den == DEN_NEDELA){
				// Palmová (Kvetná) nedeľa

				// prvé vešpery
				modlitba = MODL_PRVE_VESPERY;
				_post2_hymnus;
				_post2_antifony;
				_post2_kcitanie;
				_post2_kresponz;
				_post2_magnifikat;
				_post2_prosby;
				_post2_modlitba;

				// posvätné čítanie
				modlitba = MODL_POSV_CITANIE;
				_post2_antifony;

				// posvätné čítanie -- predĺžené slávenie vigílie
				_liturgicke_obdobie_set_vig_ant(modlitba);
				_set_chvalospev_vig_post(modlitba);
				sprintf(_anchor, "%s%d_%c%s", nazov_OBD[litobd], tyzden, pismenko_modlitby(modlitba), ANCHOR_EVANJELIUM);
				_set_evanjelium(modlitba, _file_pc, _anchor);
				set_LOG_litobd_pc;

			}// nedeľa
			else if(den == DEN_STVRTOK){
				// LH má pre ranné chvály odlišný úvod k prosbám
				modlitba = MODL_RANNE_CHVALY;
				_vtroj_prosby;

				// popis
				set_popis_dummy_except_vespers();

				modlitba = MODL_VESPERY;
				_vtroj_popis;

				// kompletórium je z nedele po druhých vešperách -- ako na slávnosti; nastavenie je vyššie
			}// nie nedeľa, ale Štvrtok Svätého týždňa (Zelený štvrtok)
			break;
// switch(litobd), case OBD_POSTNE_II -- end --------------------------------------------------

// switch(litobd), case OBD_VELKONOCNE_TROJDNIE -- begin --------------------------------------
		case OBD_VELKONOCNE_TROJDNIE:// umucenia a zmrtvychvstania Pana
			Log("OBD_VELKONOCNE_TROJDNIE\n");
// antifóny pre invitatórium
#define _vtroj_invitat {\
	sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), nazov_DN_asci[den], ANCHOR_ANTIFONA1);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
// pre Trojdnie nie je použitý _special_anchor_prefix pre CZ (nie sú hymny k volnému výběru) -- okrem nedele, kedy môžeme vziať z OBD_VELKONOCNE_I (treba zmeniť _file resp. _file_pc a potom vrátiť späť: nepoužiť litobd, ale napevno OBD_VELKONOCNE_TROJDNIE, aj keď je volané s OBD_VELKONOCNA_OKTAVA -- kde sa to používa s nastavením DEN_NEDELA)
#define _vtroj_hymnus {\
	if((den == DEN_NEDELA) && (je_CZ_hymny_k_volnemu_vyberu)){\
		if(modlitba == MODL_POSV_CITANIE){\
			file_name_litobd_pc(OBD_VELKONOCNE_I);\
		}\
		else{\
			file_name_litobd(OBD_VELKONOCNE_I);\
		}\
		_velk1_hymnus(den, modlitba, OBD_VELKONOCNE_I);\
		if(modlitba == MODL_POSV_CITANIE){\
			file_name_litobd_pc(OBD_VELKONOCNE_TROJDNIE);\
		}\
		else{\
			file_name_litobd(OBD_VELKONOCNE_TROJDNIE);\
		}\
	}\
	else{\
		c = pismenko_modlitby(modlitba);\
		if(modlitba == MODL_PRVE_VESPERY){\
			c = pismenko_modlitby(MODL_VESPERY);\
		}\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[OBD_VELKONOCNE_TROJDNIE], c, nazov_DN_asci[den], ANCHOR_HYMNUS);\
		if(modlitba == MODL_POSV_CITANIE){\
			_set_hymnus(modlitba, _file_pc, _anchor);\
			set_LOG_litobd_pc;\
		}\
		else{\
			_set_hymnus(modlitba, _file, _anchor);\
			set_LOG_litobd;\
		}\
	}\
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
	if(modlitba == MODL_POSV_CITANIE){\
		_set_kresponz(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_kresponz(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
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

// antifóny pre modlitbu cez deň sú rovnaké, použitý anchor ANCHOR_ANTIFONY
#define _vtroj_antifony {\
	c = pismenko_modlitby(modlitba);\
	if(modlitba == MODL_PRVE_VESPERY)\
		c = pismenko_modlitby(MODL_VESPERY);\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VELKONOCNE_TROJDNIE], nazov_DN_asci[den], c, (je_modlitba_cez_den(modlitba))? ANCHOR_ANTIFONY : ANCHOR_ANTIFONA1);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_antifona1(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_antifona1(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VELKONOCNE_TROJDNIE], nazov_DN_asci[den], c, (je_modlitba_cez_den(modlitba))? ANCHOR_ANTIFONY : ANCHOR_ANTIFONA2);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_antifona2(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_antifona2(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
	sprintf(_anchor, "%s_%s%c%s", nazov_OBD[OBD_VELKONOCNE_TROJDNIE], nazov_DN_asci[den], c, (je_modlitba_cez_den(modlitba))? ANCHOR_ANTIFONY : ANCHOR_ANTIFONA3);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_antifona3(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_antifona3(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
}

#define _vtroj_citanie1 {\
	sprintf(_anchor, "%s_%c%s_%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_CITANIE1, nazov_DN_asci[den]);\
	_set_citanie1(modlitba, _file_pc, _anchor);\
	set_LOG_litobd_pc;\
}
#define _vtroj_citanie2 {\
	sprintf(_anchor, "%s_%c%s_%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_CITANIE2, nazov_DN_asci[den]);\
	_set_citanie2(modlitba, _file_pc, _anchor);\
	set_LOG_litobd_pc;\
}
			// OBD_VELKONOCNE_TROJDNIE

			// kompletórium vo Veľkonočnom trojdní: až na krátky responz je z nedele po druhých vešperách
			modlitba = MODL_KOMPLETORIUM;

			// opravené, aby Piatok utrpenia Pána (Veľký piatok) mal správnu modlitbu
			if(den == DEN_PIATOK){
				_set_kompletorium_slavnost(modlitba);
			}
			else{
				// aj pre Svätú sobotu (Bielu sobotu) je predpísané nedeľné kompletórium po druhých vešperách
				_set_kompletorium_nedela(modlitba);
			}

			set_kresponz_kompletorium_obd(den, modlitba, litobd);

			if ((den != DEN_PIATOK) && (den != DEN_SOBOTA)) {
				// pre Piatok utrpenia Pána (Veľký piatok) aj Svätú sobotu (Bielu sobotu) je hymnus ako vo svätom týždni, teda "Kriste, ty svetlo a náš deň"
				set_hymnus_kompletorium_obd(den, tyzzal, modlitba, litobd);
			}

			// invitatórium
			modlitba = MODL_INVITATORIUM;
			_vtroj_invitat;

			// ranné chvály
			modlitba = MODL_RANNE_CHVALY;
			_vtroj_hymnus;
			_vtroj_antifony;
			_vtroj_kcitanie;
			_vtroj_kresponz;
			_vtroj_benediktus;
			_vtroj_prosby;
			_vtroj_modlitba;

			// vešpery
			modlitba = MODL_VESPERY;
			_vtroj_hymnus;
			_vtroj_antifony;
			_vtroj_kcitanie;
			_vtroj_kresponz;
			_vtroj_magnifikat;
			_vtroj_prosby;
			_vtroj_modlitba;

			// posvätné čítanie
			modlitba = MODL_POSV_CITANIE;
			_vtroj_hymnus;
			_vtroj_antifony;
			_vtroj_citanie1;
			_vtroj_citanie2;
			_vtroj_kresponz;
			_vtroj_modlitba;

			// modlitba cez deň MODL_PREDPOLUDNIM + MODL_NAPOLUDNIE + MODL_POPOLUDNI
			modlitba = MODL_PREDPOLUDNIM;
			_vtroj_hymnus;
			_vtroj_antifony;
			_vtroj_kcitanie;
			_vtroj_kresponz;
			_vtroj_modlitba;
			modlitba = MODL_NAPOLUDNIE;
			_vtroj_hymnus;
			_vtroj_antifony;
			_vtroj_kcitanie;
			_vtroj_kresponz;
			_vtroj_modlitba;
			modlitba = MODL_POPOLUDNI;
			_vtroj_hymnus;
			_vtroj_antifony;
			_vtroj_kcitanie;
			_vtroj_kresponz;
			_vtroj_modlitba;

			if (den == DEN_NEDELA) {
				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_velkonocna_nedela(modlitba);
				modlitba = MODL_VESPERY;
				_set_zalmy_velkonocna_nedela(modlitba);
				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_velkonocna_nedela(modlitba);
				// popis k posv. čítaniu veľkonočnej nedele
				_vtroj_popis;
				if (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA)) {
					// na ostatné hodiny sa berie doplnková psalmódia (realizované aj v _set_zalmy_velkonocna_nedela()...)
					modlitba = MODL_PREDPOLUDNIM;
					_set_zalmy_velkonocna_nedela(modlitba);
					modlitba = MODL_NAPOLUDNIE;
					_set_zalmy_velkonocna_nedela(modlitba);
					modlitba = MODL_POPOLUDNI;
					_set_zalmy_velkonocna_nedela(modlitba);
				}
			}// nedeľa
			else if (den == DEN_SOBOTA) {
				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_biela_sobota(modlitba);
				modlitba = MODL_VESPERY;
				_set_zalmy_biela_sobota(modlitba);
				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_biela_sobota(modlitba);

				// posvätné čítanie -- predĺžené slávenie vigílie
				modlitba = MODL_POSV_CITANIE;
				sprintf(_anchor, "%s_%c%s_%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA_VIG, nazov_DN_asci[den]);
				_set_antifona_vig(modlitba, _file_pc, _anchor);
				set_LOG_litobd_pc;
				_set_chvalospev_vig_post(modlitba);
				sprintf(_anchor, "%s_%c%s_%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_EVANJELIUM, nazov_DN_asci[den]);
				_set_evanjelium(modlitba, _file_pc, _anchor);
				set_LOG_litobd_pc;

				if (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA)) {
					// na ostatné hodiny sa berie doplnková psalmódia (realizované aj v _set_zalmy_biela_sobota()...)
					modlitba = MODL_PREDPOLUDNIM;
					_set_zalmy_biela_sobota(modlitba);
					modlitba = MODL_NAPOLUDNIE;
					_set_zalmy_biela_sobota(modlitba);
					modlitba = MODL_POPOLUDNI;
					_set_zalmy_biela_sobota(modlitba);
				}
				modlitba = MODL_KOMPLETORIUM;
				// popis ku kompletóriu bielej soboty
				_vtroj_popis;
			}// nie nedeľa, ale Svätá sobota (Biela sobota)
			else if (den == DEN_PIATOK) {
				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_velky_piatok(modlitba);

				// posvätné čítanie -- predĺžené slávenie vigílie
				modlitba = MODL_POSV_CITANIE;
				sprintf(_anchor, "%s_%c%s_%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA_VIG, nazov_DN_asci[den]);
				_set_antifona_vig(modlitba, _file_pc, _anchor);
				set_LOG_litobd_pc;
				_set_chvalospev_vig_post(modlitba);
				sprintf(_anchor, "%s_%c%s_%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_EVANJELIUM, nazov_DN_asci[den]);
				_set_evanjelium(modlitba, _file_pc, _anchor);
				set_LOG_litobd_pc;

				if (!isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_MCD_DOPLNKOVA)) {
					// na ostatné hodiny sa berie doplnková psalmódia (realizované aj v _set_zalmy_velky_piatok()...)
					modlitba = MODL_PREDPOLUDNIM;
					_set_zalmy_velky_piatok(modlitba);
					modlitba = MODL_NAPOLUDNIE;
					_set_zalmy_velky_piatok(modlitba);
					modlitba = MODL_POPOLUDNI;
					_set_zalmy_velky_piatok(modlitba);
				}

				modlitba = MODL_VESPERY;
				_set_zalmy_velky_piatok(modlitba);
				// popis k vešperám veľkého piatka
				_vtroj_popis;
				/* do budúcnosti: ak by mali jednotlivé modlitby svoju farbu, tak vigília má mať bielu; bežná Svätá sobota (Biela sobota): fialová
				_global_den.farba = LIT_FARBA_BIELA;
				*/
			}// nie nedeľa, ani sobota, ale Piatok utrpenia Pána (Veľký piatok)
			break;
// switch(litobd), case OBD_VELKONOCNE_TROJDNIE -- end ----------------------------------------

// switch(litobd), case OBD_VELKONOCNE_I -- begin ---------------------------------------------

		// do nanebovstupenia pana
		case OBD_VELKONOCNE_I:
			Log("OBD_VELKONOCNE_I\n");

#define _velk1_kcitanie {\
	sprintf(_anchor, "%s_%c%s%s", nazov_OBD[OBD_VELKONOCNE_I], pismenko_modlitby(modlitba), nazov_DN_asci[den], ANCHOR_KCITANIE);\
	_set_kcitanie(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

// upravené pre krajiny, kde sa slávnosť Nanebovstúpenia Pána prenáša na nasledujúcu nedeľu (štvrtok, piatok, sobota v 6. veľkonočnom týždni)
#define _velk1_kresponz {\
	if(((den == DEN_NEDELA) || (modlitba == MODL_POSV_CITANIE))\
		&& (modlitba != MODL_PREDPOLUDNIM) && (modlitba != MODL_NAPOLUDNIE) && (modlitba != MODL_POPOLUDNI)){\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ, nazov_DN_asci[den]);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);\
	}\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_kresponz(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_kresponz(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
	if((modlitba == MODL_POSV_CITANIE) && ((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA)) && ((_global_r._NANEBOVSTUPENIE_PANA.denvr - _global_den.denvr) < 4) && ((_global_r._NANEBOVSTUPENIE_PANA.denvr - _global_den.denvr) > 0))){\
		Log("upravené pre krajiny, kde sa slávnosť Nanebovstúpenia Pána prenáša na nasledujúcu nedeľu\n");\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[OBD_VELKONOCNE_II], pismenko_modlitby(modlitba), ANCHOR_KRESPONZ, nazov_DN_asci[den + 1]);\
		_set_kresponz(modlitba, nazov_obd_htm_pc[OBD_VELKONOCNE_II], _anchor);\
		set_LOG_litobd_pc;\
	}\
}

// upravené pre krajiny, kde sa slávnosť Nanebovstúpenia Pána prenáša na nasledujúcu nedeľu (štvrtok, piatok, sobota v 6. veľkonočnom týždni)
#define _velk1_citanie1 {\
	if((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA)) && ((_global_r._NANEBOVSTUPENIE_PANA.denvr - _global_den.denvr) < 4) && ((_global_r._NANEBOVSTUPENIE_PANA.denvr - _global_den.denvr) > 0)){\
		sprintf(_anchor, "%s_%c%s_%d%s", nazov_OBD[OBD_VELKONOCNE_II], pismenko_modlitby(modlitba), ANCHOR_CITANIE1, tyzden, nazov_DN_asci[den + 1]);\
		_set_citanie1(modlitba, nazov_obd_htm_pc[OBD_VELKONOCNE_II], _anchor);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s_%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_CITANIE1, tyzden, nazov_DN_asci[den]);\
		_set_citanie1(modlitba, _file_pc, _anchor);\
	}\
	set_LOG_litobd_pc;\
}
#define _velk1_citanie2 {\
	if((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA)) && ((_global_r._NANEBOVSTUPENIE_PANA.denvr - _global_den.denvr) < 4) && ((_global_r._NANEBOVSTUPENIE_PANA.denvr - _global_den.denvr) > 0)){\
		sprintf(_anchor, "%s_%c%s_%d%s", nazov_OBD[OBD_VELKONOCNE_II], pismenko_modlitby(modlitba), ANCHOR_CITANIE2, tyzden, nazov_DN_asci[den + 1]);\
		_set_citanie2(modlitba, nazov_obd_htm_pc[OBD_VELKONOCNE_II], _anchor);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s_%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_CITANIE2, tyzden, nazov_DN_asci[den]);\
		_set_citanie2(modlitba, _file_pc, _anchor);\
	}\
	set_LOG_litobd_pc;\
}
#define _velk1_prosby {\
	sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[OBD_VELKONOCNE_I], pismenko_modlitby(modlitba), ANCHOR_PROSBY, t, nazov_DN_asci[den]);\
	_set_prosby(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}
// upravené pre krajiny, kde sa slávnosť Nanebovstúpenia Pána prenáša na nasledujúcu nedeľu (piatok, sobota v 6. veľkonočnom týždni)
#define _velk1_benediktus {\
	if(den == DEN_NEDELA){\
		sprintf(_anchor, "%s_%c%s%d%s%c", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, tyzden, nazov_DN_asci[den], _global_den.litrok);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, tyzden, nazov_DN_asci[den]);\
	}\
	_set_benediktus(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	if((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA)) && ((_global_r._NANEBOVSTUPENIE_PANA.denvr - _global_den.denvr) < 3) && ((_global_r._NANEBOVSTUPENIE_PANA.denvr - _global_den.denvr) > 0)){\
		sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[OBD_VELKONOCNE_II], pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS, tyzden, nazov_DN_asci[den]);\
		_set_benediktus(modlitba, nazov_obd_htm[OBD_VELKONOCNE_II], _anchor);\
		set_LOG_litobd;\
	}\
}
// upravené pre krajiny, kde sa slávnosť Nanebovstúpenia Pána prenáša na nasledujúcu nedeľu (piatok, sobota v 6. veľkonočnom týždni)
#define _velk1_magnifikat {\
	if(den == DEN_NEDELA){\
		sprintf(_anchor, "%s_%c%s%d%s%c", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, tyzden, nazov_DN_asci[den], _global_den.litrok);\
	}\
	else{\
		sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, tyzden, nazov_DN_asci[den]);\
	}\
	_set_magnifikat(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	if((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA)) && ((_global_r._NANEBOVSTUPENIE_PANA.denvr - _global_den.denvr) < 3) && ((_global_r._NANEBOVSTUPENIE_PANA.denvr - _global_den.denvr) > 0)){\
		sprintf(_anchor, "%s_%c%s%d%s", nazov_OBD[OBD_VELKONOCNE_II], pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT, tyzden, nazov_DN_asci[den]);\
		_set_magnifikat(modlitba, nazov_obd_htm[OBD_VELKONOCNE_II], _anchor);\
		set_LOG_litobd;\
	}\
}
// upravené pre krajiny, kde sa slávnosť Nanebovstúpenia Pána prenáša na nasledujúcu nedeľu (piatok, sobota v 6. veľkonočnom týždni)
#define _velk1_modlitba {\
	sprintf(_anchor, "%s_%s%d%s", nazov_OBD[litobd], ANCHOR_MODLITBA, tyzden, nazov_DN_asci[den]);\
	if((isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA)) && ((_global_r._NANEBOVSTUPENIE_PANA.denvr - _global_den.denvr) < 3) && ((_global_r._NANEBOVSTUPENIE_PANA.denvr - _global_den.denvr) > 0)){\
		_set_modlitba(modlitba, nazov_obd_htm[OBD_VELKONOCNE_II], _anchor);\
	}\
	else{\
		_set_modlitba(modlitba, _file, _anchor);\
	}\
	set_LOG_litobd;\
}
// antifóny pre posvätné čítania
#define _velk1_ne_antifony {\
	sprintf(_anchor, "%s_%d%s%c%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_antifona1(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_antifona1(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
	sprintf(_anchor, "%s_%d%s%c%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA2);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_antifona2(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_antifona2(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
	sprintf(_anchor, "%s_%d%s%c%s", nazov_OBD[litobd], tyzden, nazov_DN_asci[den], pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_antifona3(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_antifona3(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
}

// antifóny pre modlitbu cez deň sú rovnaké, použitý anchor ANCHOR_ANTIFONY
#define _velk1_mcd_antifony {\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	_set_antifona1(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	_set_antifona2(modlitba, _file, _anchor);\
	set_LOG_litobd;\
	sprintf(_anchor, "%s_%c%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_ANTIFONY);\
	_set_antifona3(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

			// tu v skutočnosti začína VEĽKONOČNÉ OBDOBIE I.

			// nastavenie možnosti alternatívnych hymnov pre ranné chvály, posv. čítanie a vešpery -- pre férie
			if((_global_den.denvt != DEN_NEDELA) && (_global_den.denvr != NANEBOVSTUPENIE) && (_global_jazyk != JAZYK_CZ)){
				_set_hymnus_alternativy(MODL_POSV_CITANIE, litobd);
				_set_hymnus_alternativy(MODL_RANNE_CHVALY, litobd);
				_set_hymnus_alternativy(MODL_VESPERY, litobd);
			}
			else {
				// kvôli vešperám, keď sa najprv potenciálne nastaví pre predchádzajúci deň
				_set_hymnus_alternativy_NO(MODL_POSV_CITANIE, litobd);
				_set_hymnus_alternativy_NO(MODL_RANNE_CHVALY, litobd);
				_set_hymnus_alternativy_NO(MODL_VESPERY, litobd);
			}

			t = tyzden MOD 2;

			// kompletórium vo Veľkonočnom období
			modlitba = MODL_KOMPLETORIUM;
			set_hymnus_kompletorium_obd(den, tyzzal, modlitba, litobd);
			set_kresponz_kompletorium_obd(den, modlitba, litobd);
			set_antifony_kompletorium_obd(den, modlitba, litobd, zvazok_breviara[litobd]);

			if(_global_den.denvr == _global_r._NANEBOVSTUPENIE_PANA.denvr){ // ToDo: refaktor source\dbzaltar.cpp lines 8403--8520 (use proper anchor NAN instead of VN1_NE6)
				// nanebovstupenie sice ma rovnake kotvy, ale v inom súbore
				// odčlenené samostatne, lebo sa tu škaredo natvrdo pre ranné chvály a vešpery nastavuje den = DEN_NEDELA
				mystrcpy(_file, FILE_NANEBOVSTUPENIE, MAX_STR_AF_FILE);
				mystrcpy(_file_pc, FILE_NANEBOVSTUPENIE, MAX_STR_AF_FILE);
				mystrcpy(_anchor, ANCHOR_NANEBOVSTUPENIE, MAX_STR_AF_ANCHOR);
				mystrcpy(_anchor_vlastne_slavenie, ANCHOR_NANEBOVSTUPENIE, MAX_STR_AF_ANCHOR);
				Log("  ide o nanebovstupenie Pana: _file = `%s', den = %s...\n", _file, nazov_dna(den));
				Log("_anchor_vlastne_slavenie == %s...\n", _anchor_vlastne_slavenie);

				// kompletórium po prvých aj druhých vešperách
				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);
				set_hymnus_kompletorium_obd(den, tyzzal, modlitba, litobd);
				set_antifony_kompletorium_obd(den, modlitba, litobd, zvazok_breviara[litobd]);
				set_kresponz_kompletorium_obd(den, modlitba, litobd);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);
				set_hymnus_kompletorium_obd(den, tyzzal, modlitba, litobd);
				set_antifony_kompletorium_obd(den, modlitba, litobd, zvazok_breviara[litobd]);
				set_kresponz_kompletorium_obd(den, modlitba, litobd);

				// invitatórium
				modlitba = MODL_INVITATORIUM;
				_vlastne_slavenie_invitat(_anchor_vlastne_slavenie);

				// ranné chvály
				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_nanebovstupenie(modlitba);
				_velk1_hymnus(den, modlitba, OBD_NEURCENE);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_benediktus(_anchor_vlastne_slavenie);
				_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

				// vešpery
				modlitba = MODL_VESPERY;
				_set_zalmy_nanebovstupenie(modlitba);
				_velk1_hymnus(den, modlitba, OBD_NEURCENE);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
				_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

				// pridané posvätné čítanie
				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_nanebovstupenie(modlitba);
				_velk1_hymnus(den, modlitba, OBD_NEURCENE);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
				_vlastne_slavenie_ine_1citanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_ine_2citanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				// posvätné čítanie -- predĺžené slávenie vigílie
				modlitba = MODL_POSV_CITANIE;
				_vlastne_slavenie_set_vig_ant(_anchor_vlastne_slavenie);
				_set_chvalospev_vig_vn(modlitba);
				_vlastne_slavenie_set_vig_ev(_anchor_vlastne_slavenie);

				modlitba = MODL_PRVE_VESPERY;
				_set_zalmy_nanebovstupenie(modlitba);
				_velk1_hymnus(den, modlitba, OBD_NEURCENE);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
				_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

				// modlitba cez deň
				modlitba = MODL_PREDPOLUDNIM;
				_set_zalmy_nanebovstupenie(modlitba);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
				_velk1_hymnus(den, modlitba, OBD_NEURCENE);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				modlitba = MODL_NAPOLUDNIE;
				_set_zalmy_nanebovstupenie(modlitba);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
				_velk1_hymnus(den, modlitba, OBD_NEURCENE);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
				modlitba = MODL_POPOLUDNI;
				_set_zalmy_nanebovstupenie(modlitba);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
				_velk1_hymnus(den, modlitba, OBD_NEURCENE);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);

			}// je nanebovstúpenie
			else{
				// invitatórium
				modlitba = MODL_INVITATORIUM;
				_obd_invitat;

				// ranné chvály
				modlitba = MODL_RANNE_CHVALY;
				_velk1_hymnus(den, modlitba, litobd);
				_velk1_kcitanie;
				_velk1_kresponz;
				_velk1_benediktus;
				_velk1_prosby;
				_velk1_modlitba;

				// vešpery
				modlitba = MODL_VESPERY;
				_velk1_hymnus(den, modlitba, litobd);
				_velk1_kcitanie;
				_velk1_kresponz;
				_velk1_magnifikat;
				_velk1_prosby;
				_velk1_modlitba;

				// modlitba cez deň a posvätné čítania
				modlitba = MODL_POSV_CITANIE;
				_velk1_hymnus(den, modlitba, litobd);
				_velk1_citanie1;
				_velk1_citanie2;
				_velk1_kresponz;
				_velk1_modlitba;

				modlitba = MODL_PREDPOLUDNIM;
				_velk1_hymnus(den, modlitba, litobd);
				_velk1_mcd_antifony;
				_velk1_kresponz;
				_velk1_kcitanie;
				_velk1_modlitba;
				modlitba = MODL_NAPOLUDNIE;
				_velk1_hymnus(den, modlitba, litobd);
				_velk1_mcd_antifony;
				_velk1_kresponz;
				_velk1_kcitanie;
				_velk1_modlitba;
				modlitba = MODL_POPOLUDNI;
				_velk1_hymnus(den, modlitba, litobd);
				_velk1_mcd_antifony;
				_velk1_kresponz;
				_velk1_kcitanie;
				_velk1_modlitba;

				if(den == DEN_NEDELA){
					// posvätné čítanie -- predĺžené slávenie vigílie
					modlitba = MODL_POSV_CITANIE;
					_liturgicke_obdobie_set_vig_ant(modlitba);
					_set_chvalospev_vig_vn(modlitba);
					_liturgicke_obdobie_set_vig_ev_tyzden(modlitba, tyzden);

					// kompletórium po prvých vešperách
					modlitba = MODL_PRVE_KOMPLETORIUM;
					set_hymnus_kompletorium_obd(den, tyzzal, modlitba, litobd);
					set_kresponz_kompletorium_obd(den, modlitba, litobd);
					set_antifony_kompletorium_obd(den, modlitba, litobd, zvazok_breviara[litobd]);

					// prvé vešpery
					modlitba = MODL_PRVE_VESPERY;
					_velk1_hymnus(den, modlitba, litobd);
					_velk1_kcitanie;
					_velk1_kresponz;
					_velk1_magnifikat;
					_velk1_prosby;
					_velk1_modlitba;
					_velk1_ne_antifony;

					// antifóny pre ranné chvály
					modlitba = MODL_RANNE_CHVALY;
					_velk1_ne_antifony;

					// antifóny pre vešpery
					modlitba = MODL_VESPERY;
					_velk1_ne_antifony;

					// posvätné čítanie
					modlitba = MODL_POSV_CITANIE;
					_set_antifony_velk_pc(den, tyzden, modlitba); // toto sa musí urobiť nakoniec, lebo sa tam mení súbor _file_pc
				}// nedeľa
			}// nie je nanebovstúpenie
			break;
// switch(litobd), case OBD_VELKONOCNE_I -- end -----------------------------------------------

// switch(litobd), case OBD_VELKONOCNE_II -- begin --------------------------------------------

		// po nanebovstupeni pana
		case OBD_VELKONOCNE_II:
			Log("OBD_VELKONOCNE_II\n");

#define _velk2_hymnus {\
	sprintf(_anchor, "%s%s_%c%s", _special_anchor_prefix, nazov_OBD[litobd], pismenko_modlitby(modlitba), ANCHOR_HYMNUS);\
	if(modlitba == MODL_POSV_CITANIE){\
		_set_hymnus(modlitba, _file_pc, _anchor);\
		set_LOG_litobd_pc;\
	}\
	else{\
		_set_hymnus(modlitba, _file, _anchor);\
		set_LOG_litobd;\
	}\
}

// citania ako v OBD_VELKONOCNE_I; 7. tyzden ma na vespery vlastne citanie
#define _velk2_kcitanie {\
	Log("\n\n _velk2_kcitanie \n\n");\
	if(((den == DEN_NEDELA) || (modlitba == MODL_RANNE_CHVALY) || (tyzden == 6))\
		/* modlitba cez deň */\
		|| je_modlitba_cez_den(modlitba)){\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[OBD_VELKONOCNE_I], pismenko_modlitby(modlitba), nazov_DN_asci[den], ANCHOR_KCITANIE);\
		_set_kcitanie(modlitba, nazov_obd_htm[OBD_VELKONOCNE_I], _anchor);\
	}\
	else /* if((modlitba == MODL_VESPERY) && (tyzden == 7)) alebo posv. čítanie mimo nedele */{\
		sprintf(_anchor, "%s_%c%s%s", nazov_OBD[litobd], pismenko_modlitby(modlitba), nazov_DN_asci[den], ANCHOR_KCITANIE);\
		_set_kcitanie(modlitba, _file, _anchor);\
	}\
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
// zoslanie ducha sv. | prvé vešpery majú inú modlitbu ako ostatné hodinky; inú modlitbu má aj modlitba cez deň
#define _zds_modlitba {\
	c = pismenko_modlitby(modlitba);\
	if(je_modlitba_cez_den(modlitba)){\
		c = pismenko_modlitby(MODL_NAPOLUDNIE);\
	}\
	if((modlitba == MODL_PRVE_VESPERY) || je_modlitba_cez_den(modlitba)){\
		sprintf(_anchor, "%s_%c%s", ANCHOR_ZOSLANIE_DUCHA_SV, c, ANCHOR_MODLITBA);\
	}\
	else{\
		sprintf(_anchor, "%s_%s", ANCHOR_ZOSLANIE_DUCHA_SV, ANCHOR_MODLITBA);\
	}\
	_set_modlitba(modlitba, _file, _anchor);\
	set_LOG_litobd;\
}

			// tu v skutočnosti začína VEĽKONOČNÉ OBDOBIE II.

			t = tyzden MOD 2;

			// kompletórium vo veľkonočnom období
			modlitba = MODL_KOMPLETORIUM;
			set_hymnus_kompletorium_obd(den, tyzzal, modlitba, litobd);
			set_kresponz_kompletorium_obd(den, modlitba, litobd);
			set_antifony_kompletorium_obd(den, modlitba, litobd, zvazok_breviara[litobd]);

			// invitatórium
			modlitba = MODL_INVITATORIUM;
			_obd_invitat;

			// ranné chvály
			modlitba = MODL_RANNE_CHVALY;
			_velk2_hymnus;
			_velk2_kcitanie;
			_velk1_kresponz;
			_velk2_benediktus;
			_velk2_prosby;
			_velk2_modlitba;

			// vešpery
			modlitba = MODL_VESPERY;
			_velk2_hymnus;
			_velk2_kcitanie;
			_velk1_kresponz;
			_velk2_magnifikat;
			_velk2_prosby;
			_velk2_modlitba;

			// modlitba cez deň a posvätné čítania
			modlitba = MODL_POSV_CITANIE;
			_velk2_hymnus;
			_velk1_citanie1;
			_velk1_citanie2;
			_velk1_kresponz;
			_velk2_modlitba;

			modlitba = MODL_PREDPOLUDNIM;
			_velk1_hymnus(den, modlitba, litobd);
			_velk1_mcd_antifony;
			_velk1_kresponz;
			_velk2_kcitanie;
			_velk2_modlitba;
			modlitba = MODL_NAPOLUDNIE;
			_velk1_hymnus(den, modlitba, litobd);
			_velk1_mcd_antifony;
			_velk1_kresponz;
			_velk2_kcitanie;
			_velk2_modlitba;
			modlitba = MODL_POPOLUDNI;
			_velk1_hymnus(den, modlitba, litobd);
			_velk1_mcd_antifony;
			_velk1_kresponz;
			_velk2_kcitanie;
			_velk2_modlitba;

			if(den == DEN_NEDELA){
				if(_global_den.denvr == _global_r._ZOSLANIE_DUCHA_SV.denvr){

					// kompletórium po prvých vešperách
					modlitba = MODL_PRVE_KOMPLETORIUM;
					set_hymnus_kompletorium_obd(den, tyzzal, modlitba, litobd);
					set_kresponz_kompletorium_obd(den, modlitba, litobd);
					set_antifony_kompletorium_obd(den, modlitba, litobd, zvazok_breviara[litobd]);

					// zoslanie ducha sv.
					mystrcpy(_file, FILE_ZOSLANIE_DUCHA_SV, MAX_STR_AF_FILE);
					mystrcpy(_file_pc, FILE_ZOSLANIE_DUCHA_SV, MAX_STR_AF_FILE);
					mystrcpy(_anchor, ANCHOR_ZOSLANIE_DUCHA_SV, MAX_STR_AF_ANCHOR);
					mystrcpy(_anchor_vlastne_slavenie, ANCHOR_ZOSLANIE_DUCHA_SV, MAX_STR_AF_ANCHOR);
					Log("  ide o zoslanie Ducha Sv.: _file = `%s', _anchor = %s...\n", _file, _anchor);

					// prvé vešpery
					modlitba = MODL_PRVE_VESPERY;
					_set_zalmy_zoslanie_ducha_sv(modlitba);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
					_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
					_zds_modlitba;
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

					// invitatórium
					modlitba = MODL_INVITATORIUM;
					_vlastne_slavenie_invitat(_anchor_vlastne_slavenie);

					// ranné chvály
					modlitba = MODL_RANNE_CHVALY;
					_set_zalmy_zoslanie_ducha_sv(modlitba);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_benediktus(_anchor_vlastne_slavenie);
					_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
					_zds_modlitba;
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

					modlitba = MODL_VESPERY;
					_set_zalmy_zoslanie_ducha_sv(modlitba);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_magnifikat(_anchor_vlastne_slavenie);
					_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);
					_zds_modlitba;
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);

					// posvätné čítanie
					modlitba = MODL_POSV_CITANIE;
					_set_zalmy_zoslanie_ducha_sv(modlitba);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd);
					_vlastne_slavenie_ine_1citanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_ine_2citanie(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_zds_modlitba;
					// posvätné čítanie -- predĺžené slávenie vigílie
					modlitba = MODL_POSV_CITANIE;
					_vlastne_slavenie_set_vig_ant(_anchor_vlastne_slavenie);
					_set_chvalospev_vig_vn(modlitba);
					_vlastne_slavenie_set_vig_ev(_anchor_vlastne_slavenie);

					// modlitba cez deň
					modlitba = MODL_PREDPOLUDNIM;
					_set_zalmy_zoslanie_ducha_sv(modlitba);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd, NIE);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_zds_modlitba;
					modlitba = MODL_NAPOLUDNIE;
					_set_zalmy_zoslanie_ducha_sv(modlitba);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd, NIE);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_zds_modlitba;
					modlitba = MODL_POPOLUDNI;
					_set_zalmy_zoslanie_ducha_sv(modlitba);
					_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
					_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, litobd, NIE);
					_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
					_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
					_zds_modlitba;

				}// Zoslanie Ducha Svätého
				else{ // nedeľa vo veľkonočnom období II.
					// posvätné čítanie -- predĺžené slávenie vigílie
					modlitba = MODL_POSV_CITANIE;
					_liturgicke_obdobie_set_vig_ant(modlitba);
					_set_chvalospev_vig_vn(modlitba);
					_liturgicke_obdobie_set_vig_ev_tyzden(modlitba, tyzden);

					// kompletórium po prvých vešperách
					modlitba = MODL_PRVE_KOMPLETORIUM;
					set_hymnus_kompletorium_obd(den, tyzzal, modlitba, litobd);
					set_kresponz_kompletorium_obd(den, modlitba, litobd);
					set_antifony_kompletorium_obd(den, modlitba, litobd, zvazok_breviara[litobd]);

					// prvé vešpery
					modlitba = MODL_PRVE_VESPERY;
					_velk2_hymnus;
					_velk2_kcitanie;
					_velk1_kresponz;
					_velk2_magnifikat;
					_velk2_prosby;
					_velk2_modlitba;
					_velk2_ne_antifony;

					// antifóny pre ranné chvály
					modlitba = MODL_RANNE_CHVALY;
					_velk2_ne_antifony;

					// antifóny pre vešpery
					modlitba = MODL_VESPERY;
					_velk2_ne_antifony;

					// posvätné čítanie
					modlitba = MODL_POSV_CITANIE;
					_set_antifony_velk_pc(den, tyzden, modlitba); // toto sa musí urobiť nakoniec, lebo sa tam mení súbor _file_pc
				}// nedeľa; nie Zoslanie Ducha Svätého
			}// nedeľa
			break;
// switch(litobd), case OBD_VELKONOCNE_II -- end ----------------------------------------------

// switch(litobd), case OBD_VELKONOCNA_OKTAVA -- begin ----------------------------------------

		// velkonocna nedela -- 2. velk. ne
		case OBD_VELKONOCNA_OKTAVA:
			Log("OBD_VELKONOCNA_OKTAVA\n");
			// velkonocna oktava
			// -- hymnus, antifony 1 -- 3, zalmy a chvalospev su z velkonocnej nedele;
			// -- responzorium, 'Toto je den...' ako na velkonocnu nedelu;
			// -- citanie,  prosby: z velkonocneho obdobia I,
			// -- ant. na benediktus/magnifikat a modlitba: vlastne;

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

			// tu v skutočnosti začína VEĽKONOČNÁ OKTÁVA

			t = tyzden MOD 2;

			Log("OBD_VELKONOCNA_OKTAVA - nastavujem kompletórium z nedele po 1. resp. 2. vešperách...\n");
			// kompletórium vo vianočnej aj veľkonočnej oktáve je z nedele po prvých resp. druhých vešperách
			modlitba = MODL_KOMPLETORIUM;
			// možnosť použiť prvé alebo druhé nedeľné kompletórium podľa toho, či používať alternatívy; ináč použité napevno podľa modula dňa
			_set_kompletorium_slavnost_oktava(modlitba, litobd, (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_ROZNE_MOZNOSTI) ? isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_KOMPLETORIUM_OKTAVA) : (_global_den.den MOD 2)) + 1);

			if (_global_jazyk == JAZYK_CZ) {
				set_hymnus_kompletorium_obd((_global_den.den MOD 2) == 0 ? DEN_SOBOTA : DEN_NEDELA, tyzzal, modlitba, litobd); // den nastavený na DEN_NEDELA; kvôli JAZYK_CZ -- v oktáve sa berie nedeľný hymnus
			}

			set_kresponz_kompletorium_obd(den, modlitba, litobd);
			set_antifony_kompletorium_obd(DEN_NEDELA, modlitba, litobd, zvazok_breviara[litobd]); // keďže sa berie nedeľné kompletórium; beztak je to pre každý deň Aleluja, Aleluja, Aleluja

			// teda najprv nastavime vlastne ant. na benediktus/magnifikat a modlitbu
			// ranné chvály
			modlitba = MODL_RANNE_CHVALY;
			_vnokt_benediktus;
			_vnokt_modlitba;

			// invitatórium
			modlitba = MODL_INVITATORIUM;
			_obd_invitat;

			// vešpery
			modlitba = MODL_VESPERY;
			_vnokt_magnifikat;
			_vnokt_modlitba;

			// teraz nastavime zalmy z velkonocnej nedele
			modlitba = MODL_RANNE_CHVALY;
			_set_zalmy_velkonocna_nedela(modlitba);
			modlitba = MODL_VESPERY;
			_set_zalmy_velkonocna_nedela(modlitba);

			// a veci pre prve vespery
			if (den == DEN_NEDELA) { // v skutočnosti platí aj: (_global_den.denvr == DRUHA_VELKONOCNA_NEDELA)
				// kompletórium po prvých vešperách
				modlitba = MODL_PRVE_KOMPLETORIUM;
				set_hymnus_kompletorium_obd(den, tyzzal, modlitba, litobd);
				set_kresponz_kompletorium_obd(den, modlitba, litobd);
				set_antifony_kompletorium_obd(den, modlitba, litobd, zvazok_breviara[litobd]);

				// prvé vešpery
				modlitba = MODL_PRVE_VESPERY;
				_vnokt_magnifikat;
				_vnokt_modlitba;
				_set_zalmy_velkonocna_nedela(modlitba);

				// posvätné čítanie -- predĺžené slávenie vigílie
				modlitba = MODL_POSV_CITANIE;
				_liturgicke_obdobie_set_vig_ant(modlitba);
				_set_chvalospev_vig_vn(modlitba);
				_liturgicke_obdobie_set_vig_ev_tyzden(modlitba, tyzden);

			}// nedeľa

			// žalmy pre modlitbu cez deň a posvätné čítania (pč-antifóny)
			modlitba = MODL_POSV_CITANIE;
			_set_zalmy_velk_oktava(den, modlitba);
			_vnokt_modlitba;
			_velk1_ne_antifony;
			_velk1_kresponz;
			_velk1_citanie1;
			_velk1_citanie2;

			modlitba = MODL_PREDPOLUDNIM;
			_set_zalmy_velk_oktava(den, modlitba);
			_vnokt_modlitba;
			modlitba = MODL_NAPOLUDNIE;
			_set_zalmy_velk_oktava(den, modlitba);
			_vnokt_modlitba;
			modlitba = MODL_POPOLUDNI;
			_set_zalmy_velk_oktava(den, modlitba);
			_vnokt_modlitba;

			// dalej nastavime citanie a prosby z velkonocneho obd. I
			file_name_litobd(OBD_VELKONOCNE_I); // aby bolo z velkonocneho obd. I
			// ranné chvály
			modlitba = MODL_RANNE_CHVALY;
			_velk1_kcitanie;
			_velk1_prosby;
			// vešpery
			modlitba = MODL_VESPERY;
			_velk1_kcitanie;
			_velk1_prosby;
			// a veci pre prve vespery
			if (den == DEN_NEDELA) {
				modlitba = MODL_PRVE_VESPERY;
				_velk1_kcitanie;
				_velk1_prosby;
			}// nedeľa

			// krátke čítanie pre modlitbu cez deň
			modlitba = MODL_PREDPOLUDNIM;
			_velk1_kcitanie;
			modlitba = MODL_NAPOLUDNIE;
			_velk1_kcitanie;
			modlitba = MODL_POPOLUDNI;
			_velk1_kcitanie;

			// override hymnov v prípade je_CZ_hymny_k_volnemu_vyberu sa deje priamo v _vtroj_hymnus

			// napokon nastavime hymnus, antifony a kratke resp. z velkonocnej nedele
			file_name_litobd(OBD_VELKONOCNE_TROJDNIE); // aby bolo z velkonocnej nedele
			mystrcpy(_file_pc, nazov_obd_htm_pc[OBD_VELKONOCNE_TROJDNIE], MAX_STR_AF_FILE); // aby bolo z velkonocnej nedele
			den = DEN_NEDELA;

			// ranné chvály
			modlitba = MODL_RANNE_CHVALY;
			_vtroj_hymnus;
			_vtroj_antifony;
			_vtroj_kresponz;

			// vešpery
			modlitba = MODL_VESPERY;
			_vtroj_hymnus;
			_vtroj_antifony;
			_vtroj_kresponz;

			// modlitba cez deň a posvätné čítania
			modlitba = MODL_POSV_CITANIE;
			_vtroj_hymnus;
			modlitba = MODL_PREDPOLUDNIM;
			_vtroj_hymnus;
			_vtroj_antifony;
			_vtroj_kresponz;
			modlitba = MODL_NAPOLUDNIE;
			_vtroj_hymnus;
			_vtroj_antifony;
			_vtroj_kresponz;
			modlitba = MODL_POPOLUDNI;
			_vtroj_hymnus;
			_vtroj_antifony;
			_vtroj_kresponz;

			// prvé vešpery
			if (den == DEN_NEDELA) {
				modlitba = MODL_PRVE_VESPERY;
				_vtroj_hymnus;
				_vtroj_antifony;
				_vtroj_kresponz;
			}// nedeľa

			break;
// switch(litobd), case OBD_VELKONOCNA_OKTAVA -- end ------------------------------------------

	} // switch(litobd)
	Log("DBZ:Koniec veľkého switch()-u podľa liturgických období.\n");
	LOG_ciara_sv;
	// koniec velkeho switchu, podla ktoreho sa priradia zakladne udaje

	}// if (skip_big_switch == NIE)

#ifdef DETAIL_LOG_GLOBAL_DEN
	Log("_global_den (nastavene v dbzaltar.cpp::liturgicke_obdobie() po velkom switchi, pred druhym spustanim sviatky_svatych()):\n");
	Log(_global_den);
#endif
	// --------------------------------------------------------------------
	// nasledujuca cast berie do uvahy, kedy sa ma `robit' svaty | je to cast prevzata z dnes.cpp::init_global_string();
	// ToDo: bolo by dobré, aby sa to robilo iba na jedinom mieste (2012-10-12)
	_struct_dm _local_den;
	_INIT_DM(_local_den);

	// najprv priradime do _local_den to, co tam ma byt
	if (poradie_svateho > 0) {
		// sviatky (spomienky, ls) svatych
		if (poradie_svateho == PORADIE_PM_SOBOTA) {
			// do _local_den priradim slavenie pm v sobotu v dalsom
			_local_den = _global_pm_sobota;
			// ale predsalen aspon _local_den = _global_pm_sobota; urobim tu
		}// poradie_svateho = PORADIE_PM_SOBOTA
		else if (poradie_svateho < PORADIE_PM_SOBOTA) {
			if (_global_pocet_svatych > poradie_svateho - 1) {
				// do _local_den priradim dane slavenie
				_local_den = _global_svaty(poradie_svateho);
				Log("spúšťam druhýkrát sviatky_svatych(), tentokrát pre %d. svätého\n", poradie_svateho);
				sviatky_svatych(_local_den.den, _local_den.mesiac, poradie_svateho, 2 /* druhýkrát */);
			}
			else {
				// sice chce svateho c. 'poradie_svateho', ale máme ich menej
				Log("-- Error: _global_svaty(%d) not assigned (liturgicke_obdobie)\n", poradie_svateho);
				ALERT;
				Export("Error: _global_svaty(%d) not assigned (liturgicke_obdobie)\n", poradie_svateho);
			}
		}// poradie_svateho < PORADIE_PM_SOBOTA
		else {
			Log("-- Error/liturgicke_obdobie: poradie_svateho == %d (max.: %d)\n", poradie_svateho, PORADIE_PM_SOBOTA);
			ALERT;
			Export("Error/liturgicke_obdobie: poradie_svateho == %d (max.: %d)\n", poradie_svateho, PORADIE_PM_SOBOTA);
		}// poradie_svateho > PORADIE_PM_SOBOTA
	}// if(poradie_svateho > 0)
	// v ďalších častiach 'else' platí, že poradie_svateho == 0 (UNKNOWN_PORADIE_SVATEHO)
	// ak poradie_svateho bolo UNKNOWN_PORADIE_SVATEHO, znamená to, že sa chcelo volanie možno pre nasledovný deň; problém sv. Jozefa - antifóny pre kompletórium nastavené pri prvom spustení volania "sviatky svätých" prekrylo nastavenie z liturgického obdobia...
	else if ((poradie_svateho == UNKNOWN_PORADIE_SVATEHO) && (_global_pocet_svatych > 0)
		&& (_global_den.smer >= _global_svaty(1).smer) && (_je_global_svaty_i_slavnost(1))
		// a neplatí, že ide o lokálnu slávnosť: tá nesmie prebiť všedný deň
		// 2010-10-06: upravené; nesmie ísť o lokálnu slávnosť (smer == 4) lebo nemá prebíjať "globálnu" v danom kalendári [napr. czop pre 22.10.]
		// 2011-02-02: zadefinované MIESTNE_SLAVENIE_CZOP_SVATY(i), aby sa zjednodušila podmienka (platí len pre CZOP)
		// 2011-03-07: MIESTNE_SLAVENIE_CZOP_SVATY(i) použité aj pre iné lokálne slávenia ako MIESTNE_SLAVENIE_LOKAL_SVATY(i)
		&& !MIESTNE_SLAVENIE_LOKAL_SVATY(1)) {
		// bolo to volanie pre nasledujúci deň, treba ošetriť napr. kompletórium po prvých vešperách, aby sa nepriradilo zo žaltára
		Log("poradie_svateho == UNKNOWN_PORADIE_SVATEHO...\n");
		Log("_global_pocet_svatych == %d\n", _global_pocet_svatych);
		Log("_global_den.smer == %d\n", _global_den.smer);
		Log("_global_svaty(1).smer == %d\n", _global_svaty(1).smer);
		// do _local_den priradim dane slavenie
		_local_den = _global_svaty(1);
		poradie_svateho = 1;
		Log("spustam druhykrat sviatky_svatych(), tentokrat pre %d. svateho\n", poradie_svateho);
		sviatky_svatych(_local_den.den, _local_den.mesiac, poradie_svateho, 2 /* druhýkrát */);
		Log("po druhom spustení sviatky_svatych(), pre %d. svätého (nastavené natvrdo)\n", poradie_svateho);
		// pravedpodobne nie je potrebný clean-up: poradie_svateho = UNKNOWN_PORADIE_SVATEHO;
	}
	else if ((_global_den.denvt == DEN_NEDELA) ||
		(_global_den.prik == PRIKAZANY_SVIATOK)) {
		// _local_den ostava _global_den
		_local_den = _global_den;
	}
	else {
		// obyčajný deň
		_local_den = _global_den;
	}

	if (_global_den.denvr == MARIE_MATKY_CIRKVI) {
		// pri spusteni liturgicke_obdobie(); spomienka panny marie matky cirkvi
		Log("pri spusteni liturgicke_obdobie(); spomienka panny marie matky cirkvi\n");
		Log("spustam druhýkrát sviatky_svatych(), tentokrat pre %d. svateho\n", poradie_svateho);
		_local_den = _global_den;
		sviatky_svatych(_local_den.den, _local_den.mesiac, poradie_svateho, 2);
	}

	// ešte spomienka panny márie v sobotu, cl. 15

	// najprv sa spytame tej soboty, ci nahodou nie je spomienka neposkvrneneho srdca panny marie; ak je, tak uprednostnime tuto
	// pridané posv. čítania a upravené; keďže smer == 11 používame pre lokálne povinné spomienky, upravili sme kontrolu z 12 na 11
	if (_global_den.denvr == SRDPM) {
		// pri spusteni liturgicke_obdobie(); spomienka neposkvrneneho srdca panny marie
		Log("pri spusteni liturgicke_obdobie(); spomienka neposkvrneneho srdca panny marie\n");
		Log("spustam druhýkrát sviatky_svatych(), tentokrat pre %d. svateho\n", poradie_svateho);
		_local_den = _global_den;
		sviatky_svatych(_local_den.den, _local_den.mesiac, poradie_svateho, 2);
	}

	// spomienka panny márie v sobotu
	if ((PODMIENKA_MOZE_BYT_SPOMIENKA_PM_V_SOBOTU) && (poradie_svateho == PORADIE_PM_SOBOTA)) {
		// teraz do _global_den priradim dane slavenie
		_local_den = _global_pm_sobota;
		mystrcpy(_file, FILE_SPOM_PM_SOBOTA, MAX_STR_AF_FILE);

		// invitatórium
		modlitba = MODL_INVITATORIUM;
		sprintf(_anchor, "%s_%c%s", SPOM_PM_SOBOTA, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA1);
		_set_antifona1(modlitba, _file, _anchor);
		set_LOG_litobd;

		// ranné chvály
		modlitba = MODL_RANNE_CHVALY;
		// hymnus
		sprintf(_anchor, "%s%s%c_%s", _special_anchor_prefix, SPOM_PM_SOBOTA, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);
		_set_hymnus(modlitba, _file, _anchor);
		set_LOG_litobd;
		// krátke čítanie
		sprintf(_anchor, "%s%c_%s", SPOM_PM_SOBOTA, pismenko_modlitby(modlitba), ANCHOR_KCITANIE);
		_set_kcitanie(modlitba, _file, _anchor);
		set_LOG_litobd;
		// krátke responzórium
		sprintf(_anchor, "%s%c_%s", SPOM_PM_SOBOTA, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);
		_set_kresponz(modlitba, _file, _anchor);
		set_LOG_litobd;
		// benediktus
		sprintf(_anchor, "%s_%c%s", SPOM_PM_SOBOTA, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS);
		_set_benediktus(modlitba, _file, _anchor);
		set_LOG_litobd;
		// prosby
		sprintf(_anchor, "%s%c_%s", SPOM_PM_SOBOTA, pismenko_modlitby(modlitba), ANCHOR_PROSBY);
		_set_prosby(modlitba, _file, _anchor);
		set_LOG_litobd;
		// modlitba
		sprintf(_anchor, "%s%c_%s", SPOM_PM_SOBOTA, pismenko_modlitby(modlitba), ANCHOR_MODLITBA);
		_set_modlitba(modlitba, _file, _anchor);
		set_LOG_litobd;

		// posvätné čítanie | antifóny, žalmy, verš a prvé čítanie s responzóriom sa berie z príslušnej soboty
		modlitba = MODL_POSV_CITANIE;
		// hymnus
		sprintf(_anchor, "%s%s%c_%s", _special_anchor_prefix, SPOM_PM_SOBOTA, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);
		_set_hymnus(modlitba, _file, _anchor);
		set_LOG_litobd;
		_set_hymnus_alternativy_NO(modlitba, _global_den.litobd);
		// druhé čítanie
		sprintf(_anchor, "%s%c_%s", SPOM_PM_SOBOTA, pismenko_modlitby(modlitba), ANCHOR_CITANIE2);
		_set_citanie2(modlitba, _file, _anchor);
		set_LOG_litobd;
		// modlitba -- ako na ranné chvály
		sprintf(_anchor, "%s%c_%s", SPOM_PM_SOBOTA, pismenko_modlitby(MODL_RANNE_CHVALY), ANCHOR_MODLITBA);
		_set_modlitba(modlitba, _file, _anchor);
		set_LOG_litobd;

	}// spomienka panny márie v sobotu

	// pre vešpery, ak je zvolená táto možnosť, treba nastaviť kratšie prosby z dodatku (možno ich použiť v ktorýkoľvek deň v roku)
	if (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_VESP_KRATSIE_PROSBY)) {
		Log("pre vešpery nastavujem kratšie prosby z dodatku -- možno ich použiť v ktorýkoľvek deň v roku (je zvolená táto možnosť)\n");
		_set_prosby_dodatok(_global_den.denvt);
	}

	Log("do _global_den nastavujem _local_den...\n");
	_global_den = _local_den;
#ifdef DETAIL_LOG_GLOBAL_DEN
	Log("_global_den (nastavene v dbzaltar.cpp::liturgicke_obdobie() na konci):\n");
	Log(_global_den);
#endif

	Log("-- liturgicke_obdobie(%d, %d, %d, %d: svaty: %d) -- koniec\n", litobd, tyzden, den, tyzzal, poradie_svateho);
}// liturgicke_obdobie();

// obsahuje udaje o spolocnej casti, MODL_SPOL_CAST...
// kedze ju pouzivame len pri druhom volani sviatky_svatych(), mame zarucene, ze _global_den obsahuje dobre udaje -- toho spravneho svateho :-)
short int modlitba;

/* sviatky_svatych();
 *
 * nastavi do _global_svaty(1) nasledovne udaje:
 *
 *	   typslav;    // typ slavenia (1--5): SLAV_...
 *     smer;       // poradove cislo z c.59 Vseobecnych smernic
 *                 // o liturgii hodin a kalendari
 *	   meno[MAX_MENO]; // nazov prip. sviatku
 *
 * az na konci nastavi .den a .mesiac, ostatne sa nastavia inde
 *
 * tato funkcia default dostava vstup poradie_svaty == 0 (resp. UNKNOWN_PORADIE_SVATEHO); to sa rovna 'staremu pouzitiu'; v pripade, ze poradie_svaty != 0 (resp. UNKNOWN_PORADIE_SVATEHO), znamena to, ze chceme uz pri generovani modlitby nastavit konkretne pre danu modlitbu (svateho) atributy.
 *
 */


// v spoločnej časti na sviatky učiteľov cirkvi je uvedené: "zo spoločnej časti na sviatky duchovných pastierov okrem toho, čo nasleduje"
// preto opravené (nevrátim default MODL_SPOL_CAST_SV_MUZ, ale MODL_SPOL_CAST_DUCH_PAST_KNAZ)
// skontrolované: len 3 slávenia majú uvedené MODL_SPOL_CAST_UCITEL_CIRKVI bez doplnenia, či to bol (diakon,) kňaz, biskup, pápež, panna: sv. Efrém, sv. Hieronym, sv. Ján z Kríža
short int _spol_cast_vyber_dp_pn(_struct_sc sc){
	Log("_spol_cast_vyber_dp_pn() -- skúšam, čo sa zhoduje...\n");
	short int a;
	a = sc.a1;
	Log("  sc.a1 == %s (%d)\n", nazov_spolc(a), a);
	ucitel_cirkvi__sc_duch_pastier_panna;
	a = sc.a2;
	Log("  sc.a2 == %s (%d)\n", nazov_spolc(sc.a2), sc.a2);
	ucitel_cirkvi__sc_duch_pastier_panna;
	a = sc.a3;
	Log("  sc.a3 == %s (%d)\n", nazov_spolc(sc.a3), sc.a3);
	ucitel_cirkvi__sc_duch_pastier_panna;
	Log("not matches. returning %s (%d)\n", nazov_spolc(MODL_SPOL_CAST_DUCH_PAST_KNAZ), MODL_SPOL_CAST_DUCH_PAST_KNAZ);
	return MODL_SPOL_CAST_DUCH_PAST_KNAZ;
}// _spol_cast_vyber_dp_pn();

short int _spol_cast_je_panna(_struct_sc sc) {
	Log("_spol_cast_je_panna() -- skúšam, či v sc je panna...\n");
	short int a;
	a = sc.a1;
	Log("  sc.a1 == %s (%d)\n", nazov_spolc(sc.a1), sc.a1);
	mucenik__sc_panna;
	a = sc.a2;
	Log("  sc.a2 == %s (%d)\n", nazov_spolc(sc.a2), sc.a2);
	mucenik__sc_panna;
	a = sc.a3;
	Log("  sc.a3 == %s (%d)\n", nazov_spolc(sc.a3), sc.a3);
	mucenik__sc_panna;
	Log("  returning NIE\n");
	return NIE;
}// _spol_cast_je_panna();

short int _spol_cast_je_mucenica(_struct_sc sc) {
	Log("_spol_cast_je_mucenica() -- skúšam, či v sc je mučenica...\n");
	short int a;
	a = sc.a1;
	Log("  sc.a1 == %s (%d)\n", nazov_spolc(sc.a1), sc.a1);
	panna__sc_mucenica;
	a = sc.a2;
	Log("  sc.a2 == %s (%d)\n", nazov_spolc(sc.a2), sc.a2);
	panna__sc_mucenica;
	a = sc.a3;
	Log("  sc.a3 == %s (%d)\n", nazov_spolc(sc.a3), sc.a3);
	panna__sc_mucenica;
	Log("  returning NIE\n");
	return NIE;
}// _spol_cast_je_mucenica();

 // specialne veci pre sviatky duchovnych pastierov, jedneho mucenika...
// funguje to aj pre svatych muzov (jeden resp. viaceri -- podla toho, co je v _anchor_pom)
void _spolocna_cast_hymnus_rozne(short int modlitba, char *_anchor_pom, char *_anchor, char *_file, int force){
	if (su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modlitba) || ((force & FORCE_BRAT_HYMNUS) == FORCE_BRAT_HYMNUS)){
		sprintf(_anchor, "%s%s%c%s", _special_anchor_prefix, _anchor_pom, pismenko_modlitby(modlitba), ANCHOR_HYMNUS);
		_set_hymnus(modlitba, _file, _anchor);
		set_LOG_svsv;
	}
}

void _spolocna_cast_benediktus_rozne(short int modlitba, char *_anchor_pom, char *_anchor, char *_file, int force){
	if (su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modlitba) || ((force & FORCE_BRAT_ANTIFONY_B_M) == FORCE_BRAT_ANTIFONY_B_M)){
		sprintf(_anchor, "%s%c%s", _anchor_pom, pismenko_modlitby(modlitba), ANCHOR_BENEDIKTUS);
		_set_benediktus(modlitba, _file, _anchor);
		set_LOG_svsv;
	}
}

void _spolocna_cast_magnifikat_rozne(short int modlitba, char *_anchor_pom, char *_anchor, char *_file, int force){
	if (su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modlitba) || ((force & FORCE_BRAT_ANTIFONY_B_M) == FORCE_BRAT_ANTIFONY_B_M)){
		sprintf(_anchor, "%s%c%s", _anchor_pom, pismenko_modlitby(modlitba), ANCHOR_MAGNIFIKAT);
		_set_magnifikat(modlitba, _file, _anchor);
		set_LOG_svsv;
	}
}

void _spolocna_cast_kresponz_rozne(short int modlitba, char *_anchor_pom, char *_anchor, char *_file, int force){
	if (su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modlitba) || ((force & FORCE_BRAT_KRESP) == FORCE_BRAT_KRESP)){
		sprintf(_anchor, "%s%c%s", _anchor_pom, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);
		_set_kresponz(modlitba, _file, _anchor);
		set_LOG_svsv;
	}
}

// kvôli 2. čítaniu pre duchovných pastierov; používame aj pre odlišné čítanie pre sväté ženy - čo žili v manželstve
void _spolocna_cast_2cit_rozne(short int modlitba, char *_anchor_pom, char *_anchor, char *_file){
	sprintf(_anchor, "%s%c%s", _anchor_pom, pismenko_modlitby(modlitba), ANCHOR_CITANIE2);
	_set_citanie2(modlitba, _file, _anchor);
	set_LOG_svsv;
}

// kvôli modlitbe pre pannu-mučenicu
void _spolocna_cast_modlitba_rozne(short int modlitba, char *_anchor_pom, char *_anchor, char *_file){
	sprintf(_anchor, "%s%s", _anchor_pom, ANCHOR_MODLITBA);
	_set_modlitba(modlitba, _file, _anchor);
	set_LOG_svsv;
}

// pre ofícium za zosnulých je potrebné vyberať žalm (146, 150 na RCH) spolu s antifónou rovnakým kritériom; to je uvedené priamo v _set_zalmy_za_zosnulych()
void _spolocna_cast_ant3_viac_ozz(char *_anchor_head, char *_anchor, char *_file){
	sprintf(_anchor, "%s%c%s%d", _anchor_head, pismenko_modlitby(modlitba), ANCHOR_ANTIFONA3, (!isGlobalOption(OPT_5_ALTERNATIVES, BIT_OPT_5_OFF_DEF_PSALM_146_150)) ? 1 : 2);
	_set_antifona3(modlitba, _file, _anchor);
	set_LOG_svsv;
}

// 1. čítanie je zväčša odlišné pre spoločné časti sviatkov svätých nasledovne:
// - I. zväzok (advent, vianoce) a II. zväzok (pôst),
// - II. zväzok (veľká noc),
// - III. a IV. zväzok (obdobie cez rok).
void _spolocna_cast_1cit_zvazok(short int modlitba, const char* _anchor_pom, const char* _anchor_zvazok, const char* _anchor, const char* _file, int force /* = 0 */){
	char _anchor_lokal[SMALL]; // 2005-08-08: lokálna premenná
	Log("_spolocna_cast_1cit_zvazok: začiatok\n");
	Log("\tmodlitba == %s\n", nazov_modlitby(modlitba));
	Log("\tanchor_pom == %s\n", _anchor_pom);
	Log("\tanchor_zvazok == %s\n", _anchor_zvazok);
	Log("\tanchor == %s\n", _anchor);
	Log("\tfile == %s\n", _file);

	if (je_1cit_vlastne(modlitba) || ((force & FORCE_BRAT_KCIT_1CIT) == FORCE_BRAT_KCIT_1CIT)){
		if (!equals(_anchor_pom, STR_EMPTY)){
			sprintf(_anchor_lokal, "%s%s%s%c%s", _anchor, _anchor_pom, _anchor_zvazok, pismenko_modlitby(modlitba), ANCHOR_CITANIE1);
		}
		else {
			sprintf(_anchor_lokal, "%s%s%c%s", _anchor, _anchor_zvazok, pismenko_modlitby(modlitba), ANCHOR_CITANIE1);
		}
		_set_citanie1(modlitba, _file, _anchor_lokal);

		Log("   set(svsv): %s: `%s', kotva `%s'\n", nazov_modlitby(modlitba), _file, _anchor_lokal);
	}
	else{
		Log("podľa smerníc nie je vlastné čítanie, nenastavujem.\n");
	}
	Log("_spolocna_cast_1cit_zvazok: koniec.\n");
}

// krátke responzórium na posvätné čítanie pre vlastné časti je 
// zväčša rovnaké, ale pre sviatky prebl. panny márie je odlišné (porov. 1. čítanie vyššie):
// - I. zväzok (advent, vianoce),
// - II. zväzok (pôst), II. zväzok (veľká noc), III. a IV. zväzok (obdobie cez rok).
void _spolocna_cast_kresponz_zvazok(short int modlitba, char *_anchor_pom, char *_anchor_zvazok, char *_anchor, char *_file, int force){
	char _anchor_lokal[SMALL];
	Log("_spolocna_cast_kresp_zvazok: \n");
	Log("\tmodlitba == %s\n", nazov_modlitby(modlitba));
	Log("\tanchor_pom == %s\n", _anchor_pom);
	Log("\tanchor_zvazok == %s\n", _anchor_zvazok);
	Log("\tanchor == %s\n", _anchor);
	Log("\tfile == %s\n", _file);

	if (((modlitba != MODL_POSV_CITANIE) && (su_inv_hymnus_kcit_kresp_benmagn_prosby_vlastne(modlitba)))
		||
		(((je_1cit_vlastne(modlitba)) || ((force & FORCE_BRAT_KCIT_1CIT) == FORCE_BRAT_KCIT_1CIT)) && (modlitba == MODL_POSV_CITANIE))
		){
		if (!equals(_anchor_pom, STR_EMPTY)){
			sprintf(_anchor_lokal, "%s%s%s%c%s", _anchor, _anchor_pom, _anchor_zvazok, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);
		}
		else {
			sprintf(_anchor_lokal, "%s%s%c%s", _anchor, _anchor_zvazok, pismenko_modlitby(modlitba), ANCHOR_KRESPONZ);
		}
		_set_kresponz(modlitba, _file, _anchor_lokal);

		Log("   set(svsv): %s: `%s', kotva `%s'\n", nazov_modlitby(modlitba), _file, _anchor_lokal);
	}
	else{
		Log("podľa smerníc nie je vlastné čítanie, nenastavujem.\n");
	}
	Log("_spolocna_cast_kresponz_zvazok: koniec.\n");
}

/* podľa všeobecných smerníc, č. 134:

"Na slávnosti a sviatky, vo Veľkonočnom trojdní a v dňoch Veľkonočnej a Vianočnej oktávy 
sú pre posvätné čítanie určené vlastné žalmy v súlade s tradíciou; ich vhodnosť osvetľuje 
zvyčajne antifóna. Tak je to aj pri modlitbe cez deň na niektoré slávnosti Pána 
a vo Veľkonočnej oktáve. Na ranné chvály sa berú žalmy a chválospev z nedele prvého týždňa 
v žaltári. 

Na prvé vešpery slávností sa berú žalmy podľa starodávneho zvyku zo série Laudáte. 

Druhé vešpery slávností a vešpery sviatkov majú žalmy i chválospev vlastné. 

Na modlitbu cez deň slávností, okrem tých, o ktorých sa už hovorilo, a ak nepripadnú na nedeľu, 
berú sa žalmy z doplnkového cyklu (graduálne).

Na sviatky sa na modlitbu cez deň berú žalmy z príslušného dňa v týždni."
 */

void __set_spolocna_cast(short int a, short int poradie_svaty, _struct_sc sc, int force /* = 0 */){
	// 2005-07-22: pokus o doplnenie udajov k posvatnym citaniam
	// 2005-08-05: 1. čítanie je zväčša odlišné pre spoločné časti sviatkov svätých nasledovne:
	// - I. zväzok (advent, vianoce) a II. zväzok (pôst),
	// - II. zväzok (veľká noc),
	// - III. a IV. zväzok (obdobie cez rok).
	// -- preto sa používa _spolocna_cast_1cit_zvazok(modlitba, _anchor_pom, _anchor_zvazok, _anchor_head, _file, force);
	// 2009-09-18: doplnený nepovinný tretí parameter, ktorým sa dajú vynútiť antifóny zo spoločnej časti, aj ak je to len spomienka alebo ľubovoľná spomienka
	// 2011-08-15: "force" parametre, či napriek všetkému explicitne brať nasledovné časti zo spol. časti (boli pôvodne viaceré; bitovo použité ako jediný vstup)
	// 2013-07-04: upravené poradie modlitieb na správne; technicky potrebné kvôli tomu, že niektoré nastavenia psalmódie (pre posv. čítanie) musia prebehnúť prv, ako sa nastavuje modlitba cez deň | kvôli použitiu Ž 129 resp. Ž 131 namiesto Ž 122, 126 resp. 127 pre doplnkovú psalmódiu

	// anchors - nazvy kotiev pre zaltar styroch tyzdnov
	char _anchor[MAX_STR_AF_ANCHOR];
	char _anchor_head[MAX_STR_AF_ANCHOR];
	char _anchor_pom[MAX_STR_AF_ANCHOR]; // ďalší pomocný anchor, ktorý pojednáva o zväzku breviára kvôli posv. čítaniam
	char _anchor_zvazok[MAX_STR_AF_ANCHOR]; // files - nazvy suborov pre zaltar styroch tyzdnov
	char _file[MAX_STR_AF_FILE]; // nazov fajlu, napr. _1ne.htm
	short int b; // pre ucitelov cirkvi, odkial sa maju brat ine casti
	short int podmienka = NIE;

	Log("__set_spolocna_cast(%s) -- begin\n", nazov_spolc(a));

	Log("poradie_svaty = %d\n", poradie_svaty);
	Log("_global_poradie_svaty = %d\n", _global_poradie_svaty);

	Log("ak je slávnosť alebo sviatok, žalmy z nedele 1. týždňa pre ranné chvály...\n");
	// ranné chvály
	modlitba = MODL_RANNE_CHVALY;
	if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
		_set_zalmy_1nedele_rch();
	}
	// netreba nastavovať, ak (a == MODL_SPOL_CAST_ZA_ZOSNULYCH) || (a == MODL_SPOL_CAST_POSVIACKA_CHRAMU)

	// ToDo: consider to set psalms for prayer during the day for solemnities; in such case use _set_zalmy_mcd_1nedela_or_doplnkova_psalmodia();

	if (je_spolocna_cast_urcena(a)){
		Log("/* nastavenie nazvu suboru, kotvy apod. (_set_spolocna_cast) */\n");
		// nastavenie nazvu suboru, kotvy apod.
		sprintf(_anchor_head, "%s_", nazov_spolc_ANCHOR[a]);
		Log("  _anchor_head == %s\n", _anchor_head);
		sprintf(_file, "%s", nazov_spolc_htm[a]);
		Log("  _file == %s\n", _file);
	}
	else{
		Log("   nebrať... takže nenastavujem kotvy ani nič (iba, ak je slávnosť alebo sviatok, žalmy z nedele 1. týždňa pre ranné chvály)\n");

		Log("__set_spolocna_cast(%s) -- end\n", nazov_spolc(a));
		return;
	}

	// spolocna cast na sviatky apostolov
	if (a == MODL_SPOL_CAST_APOSTOL) {

		Log("/* spolocna cast na sviatky apostolov */\n");

		// ďalší pomocný anchor, ktorý pojednáva o zväzku breviára kvôli posv. čítaniam
		sprintf(_anchor_pom, "%s", STR_EMPTY);
		Log("  _anchor_pom == %s\n", _anchor_pom);
		sprintf(_anchor_zvazok, "%s_", zvazok_OBD[_global_den.litobd]);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			strcat(_anchor_zvazok, VELKONOCNA_PRIPONA);
		}
		Log("  _anchor_zvazok == %s\n", _anchor_zvazok);

		// prvé vešpery
		modlitba = MODL_PRVE_VESPERY;
		if (su_zalmy_prve_vespery_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_sviatok_apostolov(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_sviatok_apostolov(modlitba);
		}
		_spolocna_cast_full(modlitba);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_hymnus_ve;
			_spolocna_cast_kresp_ve;
		}

		// invitatórium
		modlitba = MODL_INVITATORIUM;
		_spolocna_cast_antifona_inv(modlitba);

		// posvätné čítanie
		modlitba = MODL_POSV_CITANIE;
		if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_sviatok_apostolov(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_sviatok_apostolov(modlitba);
		}
		_spolocna_cast_full(modlitba);

		_spolocna_cast_1cit_zvazok(modlitba, _anchor_pom, _anchor_zvazok, _anchor_head, _file, force);

		// predĺžené slávenie vigílií
		_spolocna_cast_set_vig_ant(_anchor_head);
		_set_chvalospev_vig_sc_ap(modlitba);
		_spolocna_cast_set_vig_ev(_anchor_head);

		// ranné chvály
		modlitba = MODL_RANNE_CHVALY;
		_spolocna_cast_full(modlitba);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kresp_ve;
		}
		// ranne chvaly na sviatky apostolov maju specialne hymny pre postne a velkonocne obdobie
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_hymnus_ve;
		}
		else if ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)) {
			_spolocna_cast_hymnus_po;
		}

		// modlitba cez deň
		modlitba = MODL_PREDPOLUDNIM;
		_spolocna_cast_full(modlitba);
		modlitba = MODL_NAPOLUDNIE;
		_spolocna_cast_full(modlitba);
		modlitba = MODL_POPOLUDNI;
		_spolocna_cast_full(modlitba);

		// vešpery
		if ((_global_den.litobd != OBD_OKTAVA_NARODENIA) || (_global_svaty_i_smer_override(1) <= 4)) {
			modlitba = MODL_VESPERY;
			if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
				Log("  _set_zalmy_sviatok_apostolov(%s)...\n", nazov_modlitby(modlitba));
				_set_zalmy_sviatok_apostolov(modlitba);
			}
			_spolocna_cast_full(modlitba);
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
				_spolocna_cast_kresp_ve;
			}
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
				_spolocna_cast_hymnus_ve;
			}
		}// v OBD_OKTAVA_NARODENIA -- vešpery sú zo dňa, pokiaľ sa neslávi ako slávnosť

	}// MODL_SPOL_CAST_APOSTOL

	// spolocna cast na sviatky duchovnych pastierov
	else if ((a == MODL_SPOL_CAST_DUCH_PAST_KNAZ) || (a == MODL_SPOL_CAST_DUCH_PAST_BISKUP) || (a == MODL_SPOL_CAST_DUCH_PAST_PAPEZ) || (a == MODL_SPOL_CAST_DUCH_PAST_VIACERI)) {

		Log("/* spolocna cast na sviatky duchovnych pastierov */\n");

		sprintf(_anchor_head, "%s_", ANCHOR_SPOL_CAST_DUCH_PAST);
		Log("  _anchor_head == %s\n", _anchor_head);
		sprintf(_anchor_pom, "%s_", nazov_spolc_ANCHOR[a]);
		Log("  _anchor_pom == %s\n", _anchor_pom);
		// ďalší pomocný anchor, ktorý pojednáva o zväzku breviára kvôli posv. čítaniam
		sprintf(_anchor_zvazok, "%s_", zvazok_OBD[_global_den.litobd]);
		if (
			((a == MODL_SPOL_CAST_DUCH_PAST_BISKUP) || (a == MODL_SPOL_CAST_DUCH_PAST_PAPEZ))
			&& ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II))
			) {
			strcat(_anchor_zvazok, VELKONOCNA_PRIPONA);
		}
		Log("  _anchor_zvazok == %s\n", _anchor_zvazok);

		// prvé vešpery
		modlitba = MODL_PRVE_VESPERY;
		if (su_zalmy_prve_vespery_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_sviatok_duch_past(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_sviatok_duch_past(modlitba);
		}
		_spolocna_cast_full(modlitba);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file, force);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kresp_ve;
		}
		_spolocna_cast_magnifikat_rozne(modlitba, _anchor_pom, _anchor, _file, force);

		// invitatórium
		modlitba = MODL_INVITATORIUM;
		_spolocna_cast_antifona_inv(modlitba);

		// posvätné čítanie
		modlitba = MODL_POSV_CITANIE;
		if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_sviatok_duch_past(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_sviatok_duch_past(modlitba);
		}
		_spolocna_cast_full(modlitba);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file, force);

		_spolocna_cast_1cit_zvazok(modlitba, _anchor_pom, _anchor_zvazok, STR_EMPTY /* 2005-08-08: _anchor netreba*/, _file, force);
		_spolocna_cast_2cit_rozne(modlitba, _anchor_pom, _anchor, _file);

		// predĺžené slávenie vigílií
		_spolocna_cast_set_vig_ant_sm_sz();
		_set_chvalospev_vig_sc_sm_sz(modlitba);
		if (_global_jazyk == JAZYK_CZ) {
			_spolocna_cast_set_vig_ev_dp();
		}
		else {
			_spolocna_cast_set_vig_ev_sm_sz();
		}

		// ranné chvály
		modlitba = MODL_RANNE_CHVALY;
		_spolocna_cast_full(modlitba);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file, force);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kresp_ve;
		}

		// modlitba cez deň
		modlitba = MODL_PREDPOLUDNIM;
		_spolocna_cast_full(modlitba);
		modlitba = MODL_NAPOLUDNIE;
		_spolocna_cast_full(modlitba);
		modlitba = MODL_POPOLUDNI;
		_spolocna_cast_full(modlitba);

		// vešpery
		if ((_global_den.litobd != OBD_OKTAVA_NARODENIA) || (_global_svaty_i_smer_override(1) <= 4)) {
			modlitba = MODL_VESPERY;
			if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
				Log("  _set_zalmy_sviatok_duch_past(%s)...\n", nazov_modlitby(modlitba));
				_set_zalmy_sviatok_duch_past(modlitba);
			}
			_spolocna_cast_full(modlitba);
			_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file, force);
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
				_spolocna_cast_kresp_ve;
			}
		}// v OBD_OKTAVA_NARODENIA -- vešpery sú zo dňa, pokiaľ sa neslávi ako slávnosť

	}// MODL_SPOL_CAST_DUCH_PAST_...

	// spolocna cast na sviatky ucitelov cirkvi
	else if (a == MODL_SPOL_CAST_UCITEL_CIRKVI) {
		// najprv nastavime podla spol. casti duchovnych pastierov resp. panien...

		Log("/* spolocna cast na sviatky ucitelov cirkvi */\n");

		b = _spol_cast_vyber_dp_pn(sc);
		if (b != MODL_SPOL_CAST_NEURCENA) {
			Log("spustam _set_spolocna_cast(%s) druhy raz (vnorene) -- kvoli castiam, ktore pre ucitelov cirkvi nie su\n", nazov_spolc(b));
			__set_spolocna_cast(b, poradie_svaty, sc, force);
			Log("po vnorenom spusteni _set_spolocna_cast() -- navrat.\n");
			Log("pokracujem v nastaveni veci pre spol. cast MODL_SPOL_CAST_UCITEL_CIRKVI...\n");
		}
		// ...a teraz vlastnu cast ucitelov cirkvi

		// prvé vešpery
		modlitba = MODL_PRVE_VESPERY;
		_spolocna_cast_hymnus(modlitba, _global_den.litobd);
		_spolocna_cast_kcitanie(modlitba);
		_spolocna_cast_kresponz;
		_spolocna_cast_magnifikat(modlitba);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kresp_ve;
		}
		_spolocna_cast_modlitba;

		// invitatórium
		modlitba = MODL_INVITATORIUM;
		_spolocna_cast_antifona_inv(modlitba);

		// posvätné čítanie
		modlitba = MODL_POSV_CITANIE;
		_spolocna_cast_hymnus(modlitba, _global_den.litobd);

		sprintf(_anchor_pom, "%s_", nazov_spolc_ANCHOR[a]);
		Log("  _anchor_pom == %s\n", _anchor_pom);
		// ďalší pomocný anchor, ktorý pojednáva o zväzku breviára kvôli posv. čítaniam
		sprintf(_anchor_zvazok, "%s_", zvazok_OBD[_global_den.litobd]);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			strcat(_anchor_zvazok, VELKONOCNA_PRIPONA);
		}
		Log("  _anchor_zvazok == %s\n", _anchor_zvazok);

		_spolocna_cast_1cit_zvazok(modlitba, _anchor_pom, _anchor_zvazok, STR_EMPTY /* 2005-08-08: _anchor netreba*/, _file, force);
		_spolocna_cast_2citanie;
		_spolocna_cast_modlitba;

		// predĺžené slávenie vigílií
		if (_global_jazyk == JAZYK_CZ) {
			_spolocna_cast_set_vig_ev_uc();
		}

		// ranné chvály
		modlitba = MODL_RANNE_CHVALY;
		_spolocna_cast_hymnus(modlitba, _global_den.litobd);
		_spolocna_cast_kcitanie(modlitba);
		_spolocna_cast_kresponz;
		_spolocna_cast_benediktus(modlitba);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kresp_ve;
		}
		_spolocna_cast_modlitba;

		// modlitba cez deň

		// vešpery
		if ((_global_den.litobd != OBD_OKTAVA_NARODENIA) || (_global_svaty_i_smer_override(1) <= 4)) {
			modlitba = MODL_VESPERY;
			_spolocna_cast_hymnus(modlitba, _global_den.litobd);
			_spolocna_cast_kcitanie(modlitba);
			_spolocna_cast_kresponz;
			_spolocna_cast_magnifikat(modlitba);
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
				_spolocna_cast_kresp_ve;
			}
			_spolocna_cast_modlitba;
		}// v OBD_OKTAVA_NARODENIA -- vešpery sú zo dňa, pokiaľ sa neslávi ako slávnosť

	}// MODL_SPOL_CAST_UCITEL_CIRKVI

	// spolocna cast na sviatky jedneho mucenika
	else if ((a == MODL_SPOL_CAST_MUCENIK) || (a == MODL_SPOL_CAST_MUCENICA)) {

		Log("/* spolocna cast na sviatky jedneho mucenika */\n");
		// doplnená možnosť brať modlitbu pre pannu-mučenicu (doteraz bol takto iba hymnus)

		sprintf(_anchor_head, "%s_", ANCHOR_SPOL_CAST_JEDEN_MUCENIK);
		Log("  _anchor_head == %s\n", _anchor_head);
		sprintf(_anchor_pom, "%s_", nazov_spolc_ANCHOR[a]);
		if (_spol_cast_je_panna(sc) == ANO) {
			sprintf(_anchor_pom, "%s_", ANCHOR_SPOL_CAST_PANNA_MUCENICA);
			podmienka = ANO;
		}
		Log("  _anchor_pom == %s\n", _anchor_pom);
		// ďalší pomocný anchor, ktorý pojednáva o zväzku breviára kvôli posv. čítaniam
		sprintf(_anchor_zvazok, "%s_", zvazok_OBD[_global_den.litobd]);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			strcat(_anchor_zvazok, VELKONOCNA_PRIPONA);
		}
		Log("  _anchor_zvazok == %s\n", _anchor_zvazok);

		// prvé vešpery
		modlitba = MODL_PRVE_VESPERY;
		if (su_zalmy_prve_vespery_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_sviatok_muc(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_sviatok_muc(modlitba);
		}
		_spolocna_cast_full(modlitba);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file, force);
		// _spolocna_cast_modlitba_rozne(modlitba, _anchor_pom, _anchor, _file);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kcit_kresp_chval_ve;
			if (podmienka == ANO) {
				// ANCHOR_SPOL_CAST_PANNA_MUCENICA
				_spolocna_cast_magnifikat_rozne(modlitba, _anchor_pom, _anchor, _file, force);
			}
		}
		else {
			_spolocna_cast_kresponz_rozne(modlitba, _anchor_pom, _anchor, _file, force);
			_spolocna_cast_magnifikat_rozne(modlitba, _anchor_pom, _anchor, _file, force);
		}

		// invitatórium
		modlitba = MODL_INVITATORIUM;
		_spolocna_cast_antifona_inv(modlitba);

		// posvätné čítanie
		modlitba = MODL_POSV_CITANIE;
		if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_sviatok_muc(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_sviatok_muc(modlitba);
		}
		_spolocna_cast_full(modlitba);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file, force);
		// _spolocna_cast_modlitba_rozne(modlitba, _anchor_pom, _anchor, _file);
		_spolocna_cast_1cit_zvazok(modlitba, _anchor_head, _anchor_zvazok, STR_EMPTY /* _anchor netreba*/, _file, force);

		// predĺžené slávenie vigílií
		_spolocna_cast_set_vig_ant(_anchor_head);
		_set_chvalospev_vig_sc_sm_sz(modlitba);
		_spolocna_cast_set_vig_ev(_anchor_head);

		// ranné chvály
		modlitba = MODL_RANNE_CHVALY;
		_spolocna_cast_full(modlitba);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file, force);
		// _spolocna_cast_modlitba_rozne(modlitba, _anchor_pom, _anchor, _file);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kcit_kresp_chval_ve;
		}
		if (podmienka == ANO) {
			// ANCHOR_SPOL_CAST_PANNA_MUCENICA
			_spolocna_cast_benediktus_rozne(modlitba, _anchor_pom, _anchor, _file, force);
		}

		// modlitba cez deň
		modlitba = MODL_PREDPOLUDNIM;
		_spolocna_cast_full(modlitba);
		// čítanie odlišné pre veľkonočné obdobie; napr. pre CZ 16MAJ 2014
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kcit_ve;
		}
		modlitba = MODL_NAPOLUDNIE;
		_spolocna_cast_full(modlitba);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kcit_ve;
		}
		modlitba = MODL_POPOLUDNI;
		_spolocna_cast_full(modlitba);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kcit_ve;
		}

		// vešpery
		if ((_global_den.litobd != OBD_OKTAVA_NARODENIA) || (_global_svaty_i_smer_override(1) <= 4)) {
			modlitba = MODL_VESPERY;
			if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
				Log("  _set_zalmy_sviatok_muc(%s)...\n", nazov_modlitby(modlitba));
				_set_zalmy_sviatok_muc(modlitba);
			}
			_spolocna_cast_full(modlitba);
			_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file, force);
			// _spolocna_cast_modlitba_rozne(modlitba, _anchor_pom, _anchor, _file);
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
				_spolocna_cast_kcit_kresp_chval_ve;
			}
			if (podmienka == ANO) {
				// ANCHOR_SPOL_CAST_PANNA_MUCENICA
				_spolocna_cast_magnifikat_rozne(modlitba, _anchor_pom, _anchor, _file, force);
			}
		}// v OBD_OKTAVA_NARODENIA -- vešpery sú zo dňa, pokiaľ sa neslávi ako slávnosť

	}// MODL_SPOL_CAST_MUCENIK/MUCENICA

	// spolocna cast na sviatky viacerych mucenikov
	else if (a == MODL_SPOL_CAST_VIAC_MUCENIKOV) {

		Log("/* spolocna cast na sviatky viacerych mucenikov */\n");

		sprintf(_anchor_pom, "%s_", nazov_spolc_ANCHOR[a]);
		Log("  _anchor_pom == %s\n", _anchor_pom);
		// ďalší pomocný anchor, ktorý pojednáva o zväzku breviára kvôli posv. čítaniam
		sprintf(_anchor_zvazok, "%s_", zvazok_OBD[_global_den.litobd]);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			strcat(_anchor_zvazok, VELKONOCNA_PRIPONA);
		}
		Log("  _anchor_zvazok == %s\n", _anchor_zvazok);

		// prvé vešpery
		modlitba = MODL_PRVE_VESPERY;
		if (su_zalmy_prve_vespery_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_sviatok_muc(%s, 2)...\n", nazov_modlitby(modlitba));
			_set_zalmy_sviatok_muc(modlitba, 2);
		}
		_spolocna_cast_full(modlitba);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kcit_kresp_chval_ve;
		}

		// invitatórium
		modlitba = MODL_INVITATORIUM;
		_spolocna_cast_antifona_inv(modlitba);

		// posvätné čítanie
		modlitba = MODL_POSV_CITANIE;
		if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_sviatok_muc(%s, 2)...\n", nazov_modlitby(modlitba));
			_set_zalmy_sviatok_muc(modlitba, 2);
		}
		_spolocna_cast_full(modlitba);

		_spolocna_cast_1cit_zvazok(modlitba, STR_EMPTY /* 2005-08-16: _anchor_pom netreba */, _anchor_zvazok, _anchor_pom, _file, force);

		// predĺžené slávenie vigílií
		_spolocna_cast_set_vig_ant(_anchor_head);
		_set_chvalospev_vig_sc_vm(modlitba);
		_spolocna_cast_set_vig_ev_jm_vm(); // rovnaké ako pre jedného mučeníka; netreba _spolocna_cast_set_vig_ev(_anchor_head);

		// ranné chvály
		modlitba = MODL_RANNE_CHVALY;
		_spolocna_cast_full(modlitba);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kcit_kresp_chval_ve;
		}
		if (_global_jazyk == JAZYK_HU) {
			// 2018-09-11: HU breviary has an error; we have to "simulate" that (ant. 2 for Easter season should be taken also for volumes I, III, IV ("per annum" & Advent); in HU breviary, volumes I, III, IV use ant. 2 for Fast season)
			if ((_global_den.litobd != OBD_VELKONOCNE_I) && (_global_den.litobd != OBD_VELKONOCNE_II)) {
				_spolocna_cast_ant2_po;
			}
		}
		else {
			if ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)) {
				_spolocna_cast_ant2_po;
			}
		}

		// modlitba cez deň
		modlitba = MODL_PREDPOLUDNIM;
		_spolocna_cast_full(modlitba);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kcit_ve;
		}
		modlitba = MODL_NAPOLUDNIE;
		_spolocna_cast_full(modlitba);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kcit_ve;
		}
		modlitba = MODL_POPOLUDNI;
		_spolocna_cast_full(modlitba);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kcit_ve;
		}

		// vešpery
		if ((_global_den.litobd != OBD_OKTAVA_NARODENIA) || (_global_svaty_i_smer_override(1) <= 4)) {
			modlitba = MODL_VESPERY;
			if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
				Log("  _set_zalmy_sviatok_muc(%s, 2)...\n", nazov_modlitby(modlitba));
				_set_zalmy_sviatok_muc(modlitba, 2);
			}
			_spolocna_cast_full(modlitba);
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
				_spolocna_cast_kcit_kresp_chval_ve;
			}
		}// v OBD_OKTAVA_NARODENIA -- vešpery sú zo dňa, pokiaľ sa neslávi ako slávnosť

	}// MODL_SPOL_CAST_VIAC_MUCENIKOV

	// spoločná časť na sviatky svätých mužov/žien -- pre tých, čo žili v manželstve
	else if ((a == MODL_SPOL_CAST_SV_MUZ_MANZ) || (a == MODL_SPOL_CAST_SV_ZENA_MANZ)) {
		// najprv nastavíme podľa spol. časti svätých mužov/žien...

		Log("/* spoločná časť na sviatky svätých mužov/žien -- pre tých, čo žili v manželstve */\n");

		b = MODL_SPOL_CAST_NEURCENA;
		if (a == MODL_SPOL_CAST_SV_ZENA_MANZ) {
			b = MODL_SPOL_CAST_SV_ZENA;
		}
		else if (a == MODL_SPOL_CAST_SV_MUZ_MANZ) {
			b = MODL_SPOL_CAST_SV_MUZ;
		}

		if (b != MODL_SPOL_CAST_NEURCENA) {
			Log("spúšťam _set_spolocna_cast(%s) druhý raz (vnorené) -- kvôli častiam, ktoré pre tých, čo žili v manželstve nie sú\n", nazov_spolc(b));
			__set_spolocna_cast(b, poradie_svaty, sc, force);
			Log("po vnorenom spustení _set_spolocna_cast() -- navrat.\n");
			Log("pokračujem v nastavení vecí pre spol. čast MODL_SPOL_CAST_..._MANZ...\n");
		}
		// ...a teraz vlastná časť pre tých, čo žili v manželstve

		// posvätné čítanie
		modlitba = MODL_POSV_CITANIE;

		sprintf(_anchor_pom, "%s_", nazov_spolc_ANCHOR[a]);
		Log("  _anchor_pom == %s\n", _anchor_pom);

		// ďalší pomocný anchor, ktorý pojednáva o zväzku breviára kvôli posv. čítaniam
		if (a == MODL_SPOL_CAST_SV_ZENA_MANZ) {
			// mulierum: LA LH (vol. I, p. 1242-1244; vol. II, p. 1733-1735; vol. III, p. 1616-1619; vol. IV, p. 1606-1609) have the same two readings; no need for _global_den.litobd
			sprintf(_anchor_zvazok, "%s_", zvazok_OBD[OBD_CEZ_ROK]);
		}
		else {
			// virorum: different readings for vol. I+II and vol. III+IV
			sprintf(_anchor_zvazok, "%s_", zvazok_OBD[_global_den.litobd]);
			/*
			// we do not take reading from LA LH, vol. II, p. 1706-1708, because there is special rubric "pro sancto qui in matrimonio vixit" on p. 1708-1709, also with special case for T. P. (allelúia)
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
				strcat(_anchor_zvazok, VELKONOCNA_PRIPONA);
			}
			*/
		}
		Log("  _anchor_zvazok == %s\n", _anchor_zvazok);

		_spolocna_cast_1cit_zvazok(modlitba, STR_EMPTY, _anchor_zvazok, _anchor_pom, _file, force);

		// 2006-08-07: bude treba otestovať, pretože zatiaľ to nemá asi žiadny svätec nastavené
		if (a == MODL_SPOL_CAST_SV_ZENA_MANZ) {
			_spolocna_cast_2cit_rozne(modlitba, _anchor_pom, _anchor, _file);
		}

	}// MODL_SPOL_CAST_SV_MUZ/ZENA_MANZ

	// spolocna cast na sviatky svatych muzov/zien -- pre vychovavatelov
	else if ((a == MODL_SPOL_CAST_SV_MUZ_VYCH) || (a == MODL_SPOL_CAST_SV_ZENA_VYCH)) {
		// najprv nastavime podla spol. casti svatych muzov/zien...

		Log("/* spolocna cast na sviatky svatych muzov/zien -- pre vychovavatelov */\n");

		b = MODL_SPOL_CAST_NEURCENA;
		if (a == MODL_SPOL_CAST_SV_ZENA_VYCH) {
			b = MODL_SPOL_CAST_SV_ZENA;
		}
		else if (a == MODL_SPOL_CAST_SV_MUZ_VYCH) {
			b = MODL_SPOL_CAST_SV_MUZ;
		}

		if (b != MODL_SPOL_CAST_NEURCENA) {
			Log("spustam _set_spolocna_cast(%s) druhy raz (vnorene) -- kvoli castiam, ktore pre vychovavatelov nie su\n", nazov_spolc(b));
			__set_spolocna_cast(b, poradie_svaty, sc, force);
			Log("po vnorenom spusteni _set_spolocna_cast() -- navrat.\n");
			Log("pokracujem v nastaveni veci pre spol. cast MODL_SPOL_CAST_..._VYCH...\n");
		}
		// ...a teraz vlastnu cast pre vychovávateľov

		// prvé vešpery
		modlitba = MODL_PRVE_VESPERY;
		_spolocna_cast_magnifikat(modlitba);
		_spolocna_cast_modlitba;

		// posvätné čítanie
		modlitba = MODL_POSV_CITANIE;

		sprintf(_anchor_pom, "%s_", nazov_spolc_ANCHOR[a]);
		Log("  _anchor_pom == %s\n", _anchor_pom);

		// vychovávatelia nemajú samostatné 1. čítanie
		_spolocna_cast_2cit_rozne(modlitba, _anchor_pom, _anchor, _file);
		// vychovávatelia majú rovnaké 2. čítanie

		// ranné chvály
		modlitba = MODL_RANNE_CHVALY;
		_spolocna_cast_benediktus(modlitba);
		_spolocna_cast_modlitba;

		// modlitba cez deň

		// vešpery
		modlitba = MODL_VESPERY;
		_spolocna_cast_magnifikat(modlitba);
		_spolocna_cast_modlitba;

	}// MODL_SPOL_CAST_SV_MUZ/ZENA_VYCH

	// spolocna cast na sviatky svatych muzov/zien -- pre tych, ktori konali skutky milosrdenstva
	else if ((a == MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL) || (a == MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL)) {
		// najprv nastavime podla spol. casti svatych muzov/zien...

		Log("/* spolocna cast na sviatky svatych muzov/zien -- pre tych, co konali skutky milosrdenstva */\n");

		b = MODL_SPOL_CAST_NEURCENA;
		if (a == MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL) {
			b = MODL_SPOL_CAST_SV_ZENA;
		}
		else if (a == MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL) {
			b = MODL_SPOL_CAST_SV_MUZ;
		}

		if (b != MODL_SPOL_CAST_NEURCENA) {
			Log("spustam _set_spolocna_cast(%s) druhy raz (vnorene) -- kvoli castiam, ktore pre tych, co konali skutky milosrdenstva nie su\n", nazov_spolc(b));
			__set_spolocna_cast(b, poradie_svaty, sc, force);
			Log("po vnorenom spusteni _set_spolocna_cast() -- navrat.\n");
			Log("pokracujem v nastaveni veci pre spol. cast MODL_SPOL_CAST_..._SKUTKYMIL...\n");
		}
		// ...a teraz vlastnu cast pre tych, co konali skutky milosrdenstva

		// prvé vešpery
		modlitba = MODL_PRVE_VESPERY;
		_spolocna_cast_magnifikat(modlitba);
		_spolocna_cast_modlitba;

		// posvätné čítanie
		modlitba = MODL_POSV_CITANIE;

		sprintf(_anchor_pom, "%s_", nazov_spolc_ANCHOR[a]);
		Log("  _anchor_pom == %s\n", _anchor_pom);
		// ďalší pomocný anchor, ktorý pojednáva o zväzku breviára kvôli posv. čítaniam
		sprintf(_anchor_zvazok, "%s_", zvazok_OBD[_global_den.litobd]);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			strcat(_anchor_zvazok, VELKONOCNA_PRIPONA);
		}
		Log("  _anchor_zvazok == %s\n", _anchor_zvazok);

		_spolocna_cast_1cit_zvazok(modlitba, STR_EMPTY, _anchor_zvazok, _anchor_pom, _file, force);
		// tí, čo konali skutky milosrdenstva, majú v I. a II. zväzku rovnaké 1. čítanie; v III. a IV. iné rovnaké 1. čítanie
		_spolocna_cast_2cit_rozne(modlitba, _anchor_pom, _anchor, _file);
		// tí, čo konali skutky milosrdenstva, majú rovnaké 2. čítanie

		// ranné chvály
		modlitba = MODL_RANNE_CHVALY;
		_spolocna_cast_benediktus(modlitba);
		_spolocna_cast_modlitba;

		// modlitba cez deň

		// vešpery
		modlitba = MODL_VESPERY;
		_spolocna_cast_magnifikat(modlitba);
		_spolocna_cast_modlitba;

	}// MODL_SPOL_CAST_SV_MUZ/ZENA_SKUTKYMIL

	// spolocna cast na sviatky svatych muzov/zien -- pre reholnikov
	else if ((a == MODL_SPOL_CAST_SV_MUZ_REHOLNIK) || (a == MODL_SPOL_CAST_SV_ZENA_REHOLNIK)) {
		// najprv nastavime podla spol. casti svatych muzov/zien...

		Log("/* spolocna cast na sviatky svatych muzov/zien -- pre reholnikov */\n");

		b = MODL_SPOL_CAST_NEURCENA;
		if (a == MODL_SPOL_CAST_SV_ZENA_REHOLNIK) {
			b = MODL_SPOL_CAST_SV_ZENA;
		}
		else if (a == MODL_SPOL_CAST_SV_MUZ_REHOLNIK) {
			b = MODL_SPOL_CAST_SV_MUZ;
		}

		if (b != MODL_SPOL_CAST_NEURCENA) {
			Log("spustam _set_spolocna_cast(%s) druhy raz (vnorene) -- kvoli castiam, ktore pre reholnikov nie su\n", nazov_spolc(b));
			__set_spolocna_cast(b, poradie_svaty, sc, force);
			Log("po vnorenom spusteni _set_spolocna_cast() -- navrat.\n");
			Log("pokracujem v nastaveni veci pre spol. cast MODL_SPOL_CAST_..._REHOLNIK...\n");
		}
		// ...a teraz vlastnu cast reholnikov

		// prvé vešpery
		modlitba = MODL_PRVE_VESPERY;
		_spolocna_cast_hymnus(modlitba, _global_den.litobd);
		_spolocna_cast_magnifikat(modlitba);
		_spolocna_cast_modlitba;

		// invitatórium
		modlitba = MODL_INVITATORIUM;
		_spolocna_cast_antifona_inv(modlitba);

		// posvätné čítanie
		modlitba = MODL_POSV_CITANIE;

		sprintf(_anchor_pom, "%s_", nazov_spolc_ANCHOR[a]);
		Log("  _anchor_pom == %s\n", _anchor_pom);
		// ďalší pomocný anchor, ktorý pojednáva o zväzku breviára kvôli posv. čítaniam
		sprintf(_anchor_zvazok, "%s_", zvazok_OBD[_global_den.litobd]);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			strcat(_anchor_zvazok, VELKONOCNA_PRIPONA);
		}
		Log("  _anchor_zvazok == %s\n", _anchor_zvazok);

		_spolocna_cast_1cit_zvazok(modlitba, STR_EMPTY, _anchor_zvazok, _anchor_pom, _file, force);
		// rehoľníci majú v I. a II. zväzku rovnaké 1. čítanie; v III. a IV. iné rovnaké 1. čítanie
		_spolocna_cast_2cit_rozne(modlitba, _anchor_pom, _anchor, _file);
		// rehoľníci majú rovnaké 2. čítanie

		// ranné chvály
		modlitba = MODL_RANNE_CHVALY;
		_spolocna_cast_hymnus(modlitba, _global_den.litobd);
		_spolocna_cast_benediktus(modlitba);
		_spolocna_cast_modlitba;

		// modlitba cez deň

		// vešpery
		modlitba = MODL_VESPERY;
		_spolocna_cast_hymnus(modlitba, _global_den.litobd);
		_spolocna_cast_magnifikat(modlitba);
		_spolocna_cast_modlitba;

	}// MODL_SPOL_CAST_SV_MUZ/ZENA_REHOLNIK

	// spolocna cast na sviatky svatych muzov
	else if ((a == MODL_SPOL_CAST_SV_MUZ) || (a == MODL_SPOL_CAST_SV_MUZ_VIACERI)) {

		Log("/* spolocna cast na sviatky svatych muzov */\n");

		sprintf(_anchor_head, "%s_", nazov_spolc_ANCHOR[MODL_SPOL_CAST_SV_MUZ]);
		Log("  _anchor_head == %s\n", _anchor_head);
		sprintf(_anchor_pom, "%s_", nazov_spolc_ANCHOR[a]);
		Log("  _anchor_pom == %s\n", _anchor_pom);

		// prvé vešpery
		modlitba = MODL_PRVE_VESPERY;
		if (su_zalmy_prve_vespery_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_sviatok_duch_past(%s)... - pretože pre svätých mužov sa berú tie isté žalmy\n", nazov_modlitby(modlitba));
			_set_zalmy_sviatok_duch_past(modlitba);
		}
		_spolocna_cast_full(modlitba);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file, force);

		// invitatórium
		modlitba = MODL_INVITATORIUM;
		_spolocna_cast_antifona_inv(modlitba);

		// posvätné čítanie
		modlitba = MODL_POSV_CITANIE;
		if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_sviatok_duch_past(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_sviatok_duch_past(modlitba);
		}

		// ďalší pomocný anchor, ktorý pojednáva o zväzku breviára kvôli posv. čítaniam
		sprintf(_anchor_zvazok, "%s_", zvazok_OBD[_global_den.litobd]);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			strcat(_anchor_zvazok, VELKONOCNA_PRIPONA);
		}
		Log("  _anchor_zvazok == %s\n", _anchor_zvazok);

		_spolocna_cast_full(modlitba);

		_spolocna_cast_1cit_zvazok(modlitba, STR_EMPTY /* 2005-08-16: _anchor_pom netreba */, _anchor_zvazok, _anchor_head, _file, force);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file, force);

		// predĺžené slávenie vigílií
		_spolocna_cast_set_vig_ant(_anchor_head);
		_set_chvalospev_vig_sc_sm_sz(modlitba);
		_spolocna_cast_set_vig_ev(_anchor_head);

		// ranné chvály
		modlitba = MODL_RANNE_CHVALY;
		_spolocna_cast_full(modlitba);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file, force);
		_spolocna_cast_benediktus_rozne(modlitba, _anchor_pom, _anchor, _file, force);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kresp_ve;
		}
		else {
			_spolocna_cast_kresponz_rozne(modlitba, _anchor_pom, _anchor, _file, force);
		}

		// modlitba cez deň
		modlitba = MODL_PREDPOLUDNIM;
		_spolocna_cast_full(modlitba);
		modlitba = MODL_NAPOLUDNIE;
		_spolocna_cast_full(modlitba);
		modlitba = MODL_POPOLUDNI;
		_spolocna_cast_full(modlitba);

		// vešpery
		if ((_global_den.litobd != OBD_OKTAVA_NARODENIA) || (_global_svaty_i_smer_override(1) <= 4)) {
			modlitba = MODL_VESPERY;
			if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
				Log("  _set_zalmy_sviatok_duch_past(%s)...\n", nazov_modlitby(modlitba));
				_set_zalmy_sviatok_duch_past(modlitba);
			}
			_spolocna_cast_full(modlitba);
			_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file, force);
			_spolocna_cast_magnifikat_rozne(modlitba, _anchor_pom, _anchor, _file, force);
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
				_spolocna_cast_kresp_ve;
			}
		}// v OBD_OKTAVA_NARODENIA -- vešpery sú zo dňa, pokiaľ sa neslávi ako slávnosť

	}// MODL_SPOL_CAST_SV_MUZ_[VIACERI]...

	// spolocna cast na sviatky svatych zien
	else if ((a == MODL_SPOL_CAST_SV_ZENA) || (a == MODL_SPOL_CAST_SV_ZENA_VIACERE)) {

		Log("/* spolocna cast na sviatky svatych zien */\n");

		sprintf(_anchor_head, "%s_", nazov_spolc_ANCHOR[MODL_SPOL_CAST_SV_ZENA]);
		Log("  _anchor_head == %s\n", _anchor_head);
		sprintf(_anchor_pom, "%s_", nazov_spolc_ANCHOR[a]);
		Log("  _anchor_pom == %s\n", _anchor_pom);

		// prvé vešpery
		modlitba = MODL_PRVE_VESPERY;
		if (su_zalmy_prve_vespery_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_sviatok_panien(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_sviatok_panien(modlitba);
		}
		_spolocna_cast_full(modlitba);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file, force);

		// invitatórium
		modlitba = MODL_INVITATORIUM;
		_spolocna_cast_antifona_inv(modlitba);

		// posvätné čítanie
		modlitba = MODL_POSV_CITANIE;
		if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_sviatok_panien(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_sviatok_panien(modlitba);
		}

		// ďalší pomocný anchor, ktorý pojednáva o zväzku breviára kvôli posv. čítaniam
		sprintf(_anchor_zvazok, "%s_", zvazok_OBD[_global_den.litobd]);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			strcat(_anchor_zvazok, VELKONOCNA_PRIPONA);
		}
		Log("  _anchor_zvazok == %s\n", _anchor_zvazok);

		_spolocna_cast_full(modlitba);

		_spolocna_cast_1cit_zvazok(modlitba, STR_EMPTY /* 2005-08-16: _anchor_pom netreba */, _anchor_zvazok, _anchor_head, _file, force);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file, force);

		// predĺžené slávenie vigílií
		_spolocna_cast_set_vig_ant(_anchor_head);
		_set_chvalospev_vig_sc_sm_sz(modlitba);
		if (_global_jazyk == JAZYK_CZ) {
			_spolocna_cast_set_vig_ev_sm_sz();
		}
		else {
			_spolocna_cast_set_vig_ev(_anchor_head);
		}

		// ranné chvály
		modlitba = MODL_RANNE_CHVALY;
		_spolocna_cast_full(modlitba);
		_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file, force);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kresp_ve;
		}
		else {
			_spolocna_cast_kresponz_rozne(modlitba, _anchor_pom, _anchor, _file, force);
		}

		// modlitba cez deň
		modlitba = MODL_PREDPOLUDNIM;
		_spolocna_cast_full(modlitba);
		modlitba = MODL_NAPOLUDNIE;
		_spolocna_cast_full(modlitba);
		modlitba = MODL_POPOLUDNI;
		_spolocna_cast_full(modlitba);

		// vešpery
		if ((_global_den.litobd != OBD_OKTAVA_NARODENIA) || (_global_svaty_i_smer_override(1) <= 4)) {
			modlitba = MODL_VESPERY;
			if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
				Log("  _set_zalmy_sviatok_panien(%s)...\n", nazov_modlitby(modlitba));
				_set_zalmy_sviatok_panien(modlitba);
			}
			_spolocna_cast_full(modlitba);
			_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file, force);
			// odlišné krátke resp. pre veľkonočné obdobie
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
				_spolocna_cast_kresp_ve;
			}
		}// v OBD_OKTAVA_NARODENIA -- vešpery sú zo dňa, pokiaľ sa neslávi ako slávnosť

	}// MODL_SPOL_CAST_SV_ZENA_[VIACERE]...

	// spolocna cast na sviatky panien
	else if ((a == MODL_SPOL_CAST_PANNA) || (a == MODL_SPOL_CAST_PANNY_VIACERE)) {

		Log("/* spolocna cast na sviatky panien */\n");

		if (_spol_cast_je_mucenica(sc) == ANO) {
			sprintf(_anchor_pom, "%s_", ANCHOR_SPOL_CAST_PANNA_MUCENICA);
			podmienka = ANO;
		}
		Log("  _anchor_pom == %s\n", _anchor_pom);

		// prvé vešpery
		modlitba = MODL_PRVE_VESPERY;
		if (su_zalmy_prve_vespery_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_sviatok_panien(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_sviatok_panien(modlitba);
		}
		_spolocna_cast_full(modlitba);
		//_spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file, force);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kresp_ve;
		}
		if (podmienka == ANO) {
			// ANCHOR_SPOL_CAST_PANNA_MUCENICA
			_spolocna_cast_magnifikat_rozne(modlitba, _anchor_pom, _anchor, _file, force);
		}

		// invitatórium
		modlitba = MODL_INVITATORIUM;
		_spolocna_cast_antifona_inv(modlitba);

		// posvätné čítanie
		modlitba = MODL_POSV_CITANIE;
		if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_sviatok_panien(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_sviatok_panien(modlitba);
		}
		_spolocna_cast_full(modlitba);
		// _spolocna_cast_hymnus_rozne(modlitba, _anchor_pom, _anchor, _file, force);
		// 1. čítanie je rovnaké pre všetky obdobia a zväzky žaltára :-)

		// predĺžené slávenie vigílií
		_spolocna_cast_set_vig_ant(_anchor_head);
		_set_chvalospev_vig_sc_sm_sz(modlitba);
		_spolocna_cast_set_vig_ev(_anchor_head);

		// ranné chvály
		modlitba = MODL_RANNE_CHVALY;
		_spolocna_cast_full(modlitba);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kresp_ve;
		}
		if (podmienka == ANO) {
			// ANCHOR_SPOL_CAST_PANNA_MUCENICA
			_spolocna_cast_benediktus_rozne(modlitba, _anchor_pom, _anchor, _file, force);
		}

		// modlitba cez deň
		modlitba = MODL_PREDPOLUDNIM;
		_spolocna_cast_full(modlitba);
		modlitba = MODL_NAPOLUDNIE;
		_spolocna_cast_full(modlitba);
		modlitba = MODL_POPOLUDNI;
		_spolocna_cast_full(modlitba);

		// vešpery
		if ((_global_den.litobd != OBD_OKTAVA_NARODENIA) || (_global_svaty_i_smer_override(1) <= 4)) {
			modlitba = MODL_VESPERY;
			if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
				Log("  _set_zalmy_sviatok_panien(%s)...\n", nazov_modlitby(modlitba));
				_set_zalmy_sviatok_panien(modlitba);
			}
			_spolocna_cast_full(modlitba);
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
				_spolocna_cast_kresp_ve;
			}
			if (podmienka == ANO) {
				// ANCHOR_SPOL_CAST_PANNA_MUCENICA
				_spolocna_cast_magnifikat_rozne(modlitba, _anchor_pom, _anchor, _file, force);
			}
		}// v OBD_OKTAVA_NARODENIA -- vešpery sú zo dňa, pokiaľ sa neslávi ako slávnosť

	}// MODL_SPOL_CAST_PANNA/viacere

	// spolocna cast na sviatky Panny Marie
	else if (a == MODL_SPOL_CAST_PANNA_MARIA) {

		Log("/* spolocna cast na sviatky Panny Marie */\n");

		// prvé vešpery
		modlitba = MODL_PRVE_VESPERY;
		if (su_zalmy_prve_vespery_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_sviatok_marie(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_sviatok_marie(modlitba);
		}
		_spolocna_cast_full(modlitba);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kresp_ve;
		}

		// invitatórium
		modlitba = MODL_INVITATORIUM;
		_spolocna_cast_antifona_inv(modlitba);

		// ďalší pomocný anchor, ktorý pojednáva o zväzku breviára kvôli posv. čítaniam
		sprintf(_anchor_pom, "%s", STR_EMPTY);
		Log("  _anchor_pom == %s\n", _anchor_pom);
		sprintf(_anchor_zvazok, "%s_", zvazok_OBD[_global_den.litobd]);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			strcat(_anchor_zvazok, VELKONOCNA_PRIPONA);
		}
		Log("  _anchor_zvazok == %s\n", _anchor_zvazok);

		// posvätné čítanie
		modlitba = MODL_POSV_CITANIE;
		if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_sviatok_marie(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_sviatok_marie(modlitba);
		}
		_spolocna_cast_full(modlitba);
		// 1. čítanie je zväčša odlišné pre spoločné časti sviatkov svätých takto:
		// - I. zväzok (advent, vianoce) a II. zväzok (pôst),
		// - II. zväzok (veľká noc),
		// - III. a IV. zväzok (obdobie cez rok).
		_spolocna_cast_1cit_zvazok(modlitba, _anchor_pom, _anchor_zvazok, _anchor_head, _file, force);
		_spolocna_cast_kresponz_zvazok(modlitba, _anchor_pom, _anchor_zvazok, _anchor_head, _file, force);
		// 2011-02-09: opravené _spolocna_cast_2cit_rozne -> _spolocna_cast_2citanie
		_spolocna_cast_2citanie; // _spolocna_cast_2cit_rozne(modlitba, _anchor_pom, _anchor, _file);

		// predĺžené slávenie vigílií
		_spolocna_cast_set_vig_ant(_anchor_head);
		_set_chvalospev_vig_sc_pm(modlitba);
		_spolocna_cast_set_vig_ev(_anchor_head);

		// ranné chvály
		modlitba = MODL_RANNE_CHVALY;
		_spolocna_cast_full(modlitba);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kresp_ve;
		}

		// modlitba cez deň
		modlitba = MODL_PREDPOLUDNIM;
		_spolocna_cast_full(modlitba);
		modlitba = MODL_NAPOLUDNIE;
		_spolocna_cast_full(modlitba);
		modlitba = MODL_POPOLUDNI;
		_spolocna_cast_full(modlitba);

		// vešpery
		if ((_global_den.litobd != OBD_OKTAVA_NARODENIA) || (_global_svaty_i_smer_override(1) <= 4)) {
			modlitba = MODL_VESPERY;
			if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
				Log("  _set_zalmy_sviatok_marie(%s)...\n", nazov_modlitby(modlitba));
				_set_zalmy_sviatok_marie(modlitba);
			}
			_spolocna_cast_full(modlitba);
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
				_spolocna_cast_kresp_ve;
			}
		}// v OBD_OKTAVA_NARODENIA -- vešpery sú zo dňa, pokiaľ sa neslávi ako slávnosť

	}// MODL_SPOL_CAST_PANNA_MARIA

	// spolocna cast na oficium za zosnulych
	else if (a == MODL_SPOL_CAST_ZA_ZOSNULYCH) {

		Log("/* spolocna cast na oficium za zosnulych */\n");
		// 2010-07-12: upravené tak, že spoločná časť na ofícium za zosnulých vždy berie vlastné žalmy 
		// 2011-04-12: keďže _global_opt 2 je časťou _global_opt 1 (BIT_OPT_1_ZALMY_ZO_SVIATKU), upravené
		// 2011-10-10: nie je potrebné; žalmy sa berú podľa pravidiel všeobecných smerníc

		// invitatórium
		modlitba = MODL_INVITATORIUM;
		_spolocna_cast_antifona_inv(modlitba);

		// ďalší pomocný anchor, ktorý pojednáva o zväzku breviára kvôli posv. čítaniam
		sprintf(_anchor_pom, "%s", STR_EMPTY);
		Log("  _anchor_pom == %s\n", _anchor_pom);
		sprintf(_anchor_zvazok, "%s_", zvazok_OBD[_global_den.litobd]);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			strcat(_anchor_zvazok, VELKONOCNA_PRIPONA);
		}
		Log("  _anchor_zvazok == %s\n", _anchor_zvazok);

		// posvätné čítanie
		modlitba = MODL_POSV_CITANIE;
		if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_za_zosnulych(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_za_zosnulych(modlitba);
		}
		_spolocna_cast_full(modlitba);
		// nemá predĺžené slávenie vigílií!

		// ranné chvály
		modlitba = MODL_RANNE_CHVALY;
		if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_za_zosnulych(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_za_zosnulych(modlitba);
			_set_rchvaly_z146_150(modlitba);
		}
		_spolocna_cast_full(modlitba);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_benediktus_ve;
		}
		_spolocna_cast_ant3_viac_ozz(_anchor_head, _anchor, _file);

		// modlitba cez deň
		// doplnené žalmy; hoci opravené su_zalmy_vlastne(), nie je potrebné to tu odvetviť pre 2.11.
		modlitba = MODL_PREDPOLUDNIM;
		_spolocna_cast_hymnus(modlitba, _global_den.litobd);
		if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_za_zosnulych(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_za_zosnulych(modlitba);
		}
		_spolocna_cast_full(modlitba);
		modlitba = MODL_NAPOLUDNIE;
		_spolocna_cast_hymnus(modlitba, _global_den.litobd);
		if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_za_zosnulych(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_za_zosnulych(modlitba);
		}
		_spolocna_cast_full(modlitba);
		modlitba = MODL_POPOLUDNI;
		_spolocna_cast_hymnus(modlitba, _global_den.litobd);
		if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_za_zosnulych(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_za_zosnulych(modlitba);
		}
		_spolocna_cast_full(modlitba);

		// vešpery
		if ((_global_den.litobd != OBD_OKTAVA_NARODENIA) || (_global_svaty_i_smer_override(1) <= 4)) {
			modlitba = MODL_VESPERY;
			if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
				Log("  _set_zalmy_za_zosnulych(%s)...\n", nazov_modlitby(modlitba));
				_set_zalmy_za_zosnulych(modlitba);
			}
			_spolocna_cast_full(modlitba);
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
				_spolocna_cast_magnifikat_ve;
			}
		}// v OBD_OKTAVA_NARODENIA -- vešpery sú zo dňa, pokiaľ sa neslávi ako slávnosť

		// kompletórium z nedele
		modlitba = MODL_KOMPLETORIUM;
		if (_global_den.den != DEN_NEDELA) {
			_set_kompletorium_slavnost(modlitba);
		}
		else {
			_set_kompletorium_nedela(modlitba);
		}
	}// MODL_SPOL_CAST_ZA_ZOSNULYCH

	// spolocna cast na sviatky posviacky chramu
	else if (a == MODL_SPOL_CAST_POSVIACKA_CHRAMU) {

		Log("/* spolocna cast na sviatky posviacky chramu */\n");

		// prvé vešpery
		modlitba = MODL_PRVE_VESPERY;
		if (su_zalmy_prve_vespery_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_posviacka_chramu(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_posviacka_chramu(modlitba);
		}
		_spolocna_cast_full(modlitba);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kresp_ve;
		}
		if ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)) {
			_spolocna_cast_ant1_3_po;
		}

		// invitatórium
		modlitba = MODL_INVITATORIUM;
		_spolocna_cast_antifona_inv(modlitba);

		// ďalší pomocný anchor, ktorý pojednáva o zväzku breviára kvôli posv. čítaniam
		sprintf(_anchor_pom, "%s", STR_EMPTY);
		Log("  _anchor_pom == %s\n", _anchor_pom);
		sprintf(_anchor_zvazok, "%s_", zvazok_OBD[_global_den.litobd]);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			strcat(_anchor_zvazok, VELKONOCNA_PRIPONA);
		}
		Log("  _anchor_zvazok == %s\n", _anchor_zvazok);

		// posvätné čítanie
		modlitba = MODL_POSV_CITANIE;
		if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_posviacka_chramu(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_posviacka_chramu(modlitba);
		}
		_spolocna_cast_full(modlitba);
		// 1. čítanie je zväčša odlišné pre spoločné časti sviatkov svätých takto:
		// - I. zväzok (advent, vianoce) a II. zväzok (pôst),
		// - II. zväzok (veľká noc),
		// - III. a IV. zväzok (obdobie cez rok).
		_spolocna_cast_1cit_zvazok(modlitba, _anchor_pom, _anchor_zvazok, _anchor_head, _file, force);

		// predĺžené slávenie vigílií
		_spolocna_cast_set_vig_ant(_anchor_head);
		_set_chvalospev_vig_sc_vpchr(modlitba);
		_spolocna_cast_set_vig_ev(_anchor_head);

		// ranné chvály
		modlitba = MODL_RANNE_CHVALY;
		if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
			Log("  _set_zalmy_posviacka_chramu(%s)...\n", nazov_modlitby(modlitba));
			_set_zalmy_posviacka_chramu(modlitba);
		}
		_spolocna_cast_full(modlitba);
		if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
			_spolocna_cast_kresp_ve;
		}

		// žalmy sa berú ako vo všedný deň, antifóny z vlastnej časti
		// vyriešené aj pre výročie posviacky Lateránskej baziliky (sviatok; nemajú sa vziať antifóny a žalmy zo spoločnej časti, ale zo dňa)

		// modlitba cez deň
		modlitba = MODL_PREDPOLUDNIM;
		_spolocna_cast_full(modlitba);
		modlitba = MODL_NAPOLUDNIE;
		_spolocna_cast_full(modlitba);
		modlitba = MODL_POPOLUDNI;
		_spolocna_cast_full(modlitba);

		// vešpery
		if ((_global_den.litobd != OBD_OKTAVA_NARODENIA) || (_global_svaty_i_smer_override(1) <= 4)) {
			modlitba = MODL_VESPERY;
			if (su_zalmy_vlastne(modlitba) || /* (isGlobalOption(OPT_1_CASTI_MODLITBY, BIT_OPT_1_ZALMY_ZO_SVIATKU)) || */ ((force & FORCE_BRAT_ZALMY) == FORCE_BRAT_ZALMY)) {
				Log("  _set_zalmy_posviacka_chramu(%s)...\n", nazov_modlitby(modlitba));
				_set_zalmy_posviacka_chramu(modlitba);
			}
			_spolocna_cast_full(modlitba);
			if ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)) {
				_spolocna_cast_ant_iba_3_po;
			}
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)) {
				_spolocna_cast_kresp_ve;
			}
		}// v OBD_OKTAVA_NARODENIA -- vešpery sú zo dňa, pokiaľ sa neslávi ako slávnosť

	}// MODL_SPOL_CAST_POSVIACKA_CHRAMU

	if (_je_global_den_slavnost) {
		modlitba = MODL_KOMPLETORIUM;
		if (_global_den.den != DEN_NEDELA) {
			// kompletórium zo slávnosti mimo nedieľ
			_set_kompletorium_slavnost(modlitba);
		}
		else {
			// kompletórium z nedele
			_set_kompletorium_nedela(modlitba);
		}
	}

	Log("__set_spolocna_cast(%s) -- end\n", nazov_spolc(a));
}// __set_spolocna_cast(); -- dva argumenty

void set_popis_svaty_rch_mcd_pc_vesp_den_mesiac(short int den, short int mesiac) {
	Log("set_popis_svaty_rch_mcd_pc_vesp_den_mesiac(den: %d; mesiac: %d) -- začiatok...\n", den, mesiac);
	Log("  teraz nastavujem POPIS (pre daný dátum)...\n");

	char local_anchor[MAX_STR_AF_ANCHOR];
	char local_file[MAX_STR_AF_FILE]; // nazov súboru, napr. _1ne.htm

	sprintf(local_anchor, "%02d%s_", den, nazov_MES[mesiac - 1]);
	Log("  local_anchor == %s\n", local_anchor);
	sprintf(local_file, "sv_%s.htm", nazov_mes[mesiac - 1]);
	Log("  local_file == %s\n", local_file);

	strcat(local_anchor, ANCHOR_POPIS);

	set_popis(MODL_PRVE_VESPERY, local_file, local_anchor);
	set_popis(MODL_RANNE_CHVALY, local_file, local_anchor);
	set_popis(MODL_VESPERY, local_file, local_anchor);
	set_popis(MODL_POSV_CITANIE, local_file, local_anchor);
	// popisy pre modlitby cez deň: pre ľubovoľné aj záväzné spomienky nemá význam | č. 236 VSLH: V modlitbe cez deň, čiže predpoludním, napoludnie a popoludní, a v kompletóriu sa neberie nič z ofícia o svätom, všetko je zo všedného dňa.
	if ((_global_den.typslav != SLAV_LUB_SPOMIENKA) && (_global_den.typslav != SLAV_SPOMIENKA)) {
		set_popis(MODL_PREDPOLUDNIM, local_file, local_anchor);
		set_popis(MODL_NAPOLUDNIE, local_file, local_anchor);
		set_popis(MODL_POPOLUDNI, local_file, local_anchor);
	}
	Log("set_popis_svaty_rch_mcd_pc_vesp_den_mesiac(den, mesiac) -- koniec.\n");
}// set_popis_svaty_rch_mcd_pc_vesp_den_mesiac()


void set_popis_svaty_rch_mcd_pc_vesp(short int poradie_svaty){
	// poradie_svaty sa tu vlastne vôbec nepoužíva
	Log("set_popis_svaty_rch_mcd_pc_vesp(%d) -- začiatok...\n", poradie_svaty);
	Log("  teraz nastavujem POPIS (pre daneho svateho)...\n");
	mystrcpy(_anchor, _anchor_head, MAX_STR_AF_ANCHOR);
	strcat(_anchor, ANCHOR_POPIS);
	set_popis(MODL_PRVE_VESPERY, _file, _anchor);
	set_popis(MODL_RANNE_CHVALY, _file, _anchor);
	set_popis(MODL_VESPERY, _file, _anchor);
	set_popis(MODL_POSV_CITANIE, _file, _anchor);
	// popisy pre modlitby cez deň: pre ľubovoľné aj záväzné spomienky nemá význam | č. 236 VSLH: V modlitbe cez deň, čiže predpoludním, napoludnie a popoludní, a v kompletóriu sa neberie nič z ofícia o svätom, všetko je zo všedného dňa.
	if ((_global_den.typslav != SLAV_LUB_SPOMIENKA) && (_global_den.typslav != SLAV_SPOMIENKA)){
		set_popis(MODL_PREDPOLUDNIM, _file, _anchor);
		set_popis(MODL_NAPOLUDNIE, _file, _anchor);
		set_popis(MODL_POPOLUDNI, _file, _anchor);
	}
	Log("set_popis_svaty_rch_mcd_pc_vesp() -- koniec.\n");
}// set_popis_svaty_rch_mcd_pc_vesp()

void set_spolocna_cast(_struct_sc sc, short int poradie_svaty, int force /* = 0 */) {
	// poradie_svaty je vstupom iba kvoli tomu, ze ak je 0 -> UNKNOWN_PORADIE_SVATEHO, potom nas neznepokojuju vypisy typu Error: not assigned...
	// ked nastavi vo formulari (detaily) zalmy zo `sviatku' a spolocnu cast `nebrat', predsa sa nevyvolaju zalmy zo sviatku, lebo sa nespusti _set_spolocna_cast(); 
	// [ToDo] -- mozno by bolo dobre oddelit nastavenie pre spolocnu cast a potom inde dat samotne zalmy...
	// doplnený nepovinný tretí parameter, ktorým sa dajú vynútiť antifóny zo spoločnej časti, aj ak je to len spomienka alebo ľubovoľná spomienka
	Log("set_spolocna_cast({%s, %s, %s}) -- begin\n", nazov_spolc(sc.a1), nazov_spolc(sc.a2), nazov_spolc(sc.a3));
	Log("_global_opt[OPT_3_SPOLOCNA_CAST] == %s (%ld)\n", nazov_spolc(_global_opt[OPT_3_SPOLOCNA_CAST]), _global_opt[OPT_3_SPOLOCNA_CAST]);

	Log("teraz nastavujem POPIS (pre daného svätého) -- volám set_popis_svaty_rch_mcd_pc_vesp()...\n");
	set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

	// tento POPIS nie je dobre nastaveny pre spomienku
	// "Nepoškvrneného Srdca prebl. Panny Márie" -> "Nepoškvrneného Srdca Panny Márie", preto je tam nastaveny este raz na dummy, vid ZNOVUNASTAVENIE_POPISU_NA_DUMMY

	// pokusne aj _global_svaty(1).typslav
	if (_je_global_den_slavnost || (_je_global_svaty_i_slavnost(1))) {
		Log("	teraz nastavujem žalmy pre modlitbu cez deň slávností...\n");
		if (_global_den.denvt != DEN_NEDELA) {
			Log("  _set_zalmy_mcd_doplnkova_psalmodia()...\n");
			_set_zalmy_mcd_doplnkova_psalmodia();
		}
		else {
			// nedeľa - žalmy pre modlitbu cez deň sú z nedele; nemením ich, ibaže by boli podľa bodu 135 smerníc nastavené vlastné
			Log("  žalmy ostávajú z nedele (nemením ich)...\n");
		}
	}
	else {
		Log("	nie je slávnosť (kvôli nastaveniu žalmov pre modlitbu cez deň)...\n");
	}

	Log("sc == {%d, %d, %d} == {%s, %s, %s}\n", sc.a1, sc.a2, sc.a3, nazov_spolc(sc.a1), nazov_spolc(sc.a2), nazov_spolc(sc.a3));
	Log("_global_opt[OPT_3_SPOLOCNA_CAST] == %s (%ld)\n", nazov_spolc(_global_opt[OPT_3_SPOLOCNA_CAST]), _global_opt[OPT_3_SPOLOCNA_CAST]);

	// podla _global_opt[OPT_3_SPOLOCNA_CAST] urcime, ktoru spolocnu cast dat
	if (sc.a1 != MODL_SPOL_CAST_NEURCENA) {
		if (_global_opt[OPT_3_SPOLOCNA_CAST] == (unsigned)(sc.a1)) {
			Log("	vstupujem do _set_spolocna_cast()...(_global_opt[OPT_3_SPOLOCNA_CAST] == sc.a1)\n");
			_set_spolocna_cast((short int)_global_opt[OPT_3_SPOLOCNA_CAST], poradie_svaty, force);
		}
		else {
			Log("	neplatí _global_opt[OPT_3_SPOLOCNA_CAST] == sc.a1 ...\n");
			if (sc.a2 != MODL_SPOL_CAST_NEURCENA) {
				if (_global_opt[OPT_3_SPOLOCNA_CAST] == (unsigned)(sc.a2)) {
					Log("	vstupujem do _set_spolocna_cast()...(_global_opt[OPT_3_SPOLOCNA_CAST] == sc.a2)\n");
					_set_spolocna_cast((short int)_global_opt[OPT_3_SPOLOCNA_CAST], poradie_svaty, force);
				}
				else {
					if (sc.a3 != MODL_SPOL_CAST_NEURCENA) {
						if (_global_opt[OPT_3_SPOLOCNA_CAST] == (unsigned)(sc.a3)) {
							Log("	vstupujem do _set_spolocna_cast()...(_global_opt[OPT_3_SPOLOCNA_CAST] == sc.a3)\n");
							_set_spolocna_cast((short int)_global_opt[OPT_3_SPOLOCNA_CAST], poradie_svaty, force);
						}
						else {
							if (_global_opt[OPT_3_SPOLOCNA_CAST] == MODL_SPOL_CAST_NEBRAT) {
								set_LOG_sc("  neberiem spolocnu cast\n");
								ExportHtmlComment("neberiem spolocnu cast");
							}
							else {
								// sem by to nemalo prísť
								set_LOG_sc("-- Error: sc (a1, a2, a3) su sice urcene, ale _global_opt[OPT_3_SPOLOCNA_CAST] sa nerovna ani jednej z nich!\n");
#if defined(DEBUG) || defined(OS_Windows_Ruby)
								ALERT;
								Export("Error: _global_opt[OPT_3_SPOLOCNA_CAST] assigned incorectly (a1, a2, a3 -- ok)\n");
#endif
								return;
							}
						}
					}// sc.a3 je urcena
					else {
						if (_global_opt[OPT_3_SPOLOCNA_CAST] == MODL_SPOL_CAST_NEBRAT) {
							set_LOG_sc("  neberiem spolocnu cast\n");
							ExportHtmlComment("neberiem spolocnu cast");
						}
						else {
							// sem by to nemalo prísť
							if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO) {
								set_LOG_sc("-- Error: sc (a1, a2) su sice urcene, ale _global_opt[OPT_3_SPOLOCNA_CAST] sa nerovna ani jednej z nich!\n");
#if defined(DEBUG) || defined(OS_Windows_Ruby)
								ALERT;
								Export("Error: _global_opt[OPT_3_SPOLOCNA_CAST] assigned incorectly (a1, a2 -- ok)\n");
#endif
								return;
							}
						}
					}
				}
			}// sc.a2 je urcena
			else {
				if (_global_opt[OPT_3_SPOLOCNA_CAST] == MODL_SPOL_CAST_NEBRAT) {
					set_LOG_sc("  neberiem spolocnu cast\n");
					ExportHtmlComment("neberiem spolocnu cast");
				}
				else {
					// sem by to nemalo prísť
					if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO) {
						set_LOG_sc("-- Error: sc (a1) je sice urcena, ale _global_opt[OPT_3_SPOLOCNA_CAST] sa jej nerovna!\n");
#if defined(DEBUG) || defined(OS_Windows_Ruby)
						ALERT;
						Export("Error: _global_opt[OPT_3_SPOLOCNA_CAST] assigned incorectly (a1 -- ok)\n");
#endif
						return;
					}
				}
			}
		}
	}// sc.a1 je urcene
	else {
		// sem by to nemalo prísť
		if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO) {
			Log("-- Error: sc (a1) nie je urcene; _global_opt[OPT_3_SPOLOCNA_CAST] == %s\n", nazov_spolc(_global_opt[OPT_3_SPOLOCNA_CAST]));
#if defined(DEBUG) || defined(OS_Windows_Ruby)
			ALERT;
			Export("Error: a1 (member of sc) unassigned | _global_opt[OPT_3_SPOLOCNA_CAST] == %s\n", nazov_spolc(_global_opt[OPT_3_SPOLOCNA_CAST]));
#endif
			return;
		}
	}
	Log("set_spolocna_cast(_global_opt[OPT_3_SPOLOCNA_CAST] == %s) -- end\n", nazov_spolc(_global_opt[OPT_3_SPOLOCNA_CAST]));
}// set_spolocna_cast();

// NOTE: each item in the following arrays must not have 'count' more than 10 (values 0--9) because only one decimal place within option 6 value is dedicated

_struct_lang_anchor_and_count pocet_hymnus_multi_anchor_count[] = {
	{ JAZYK_CZ, "CZ_PMB_rHYMNUS", 3 },
	{ JAZYK_CZ, "CZ_PMB_vHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_PMB_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_PMB_1HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_ADV1v_HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_ADV1r_HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_ADV19_HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_ADV12_HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_ADV13_HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_ADV2v_HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_ADV2r_HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_ADV29_HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_ADV22_HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_ADV23_HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_KRKRALA_9HYMNUS", 3 },
	{ JAZYK_CZ, "CZ_KRKRALA_2HYMNUS", 3 },
	{ JAZYK_CZ, "CZ_KRKRALA_3HYMNUS", 3 },
	{ JAZYK_CZ, "CZ_KRST_rHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_18JAN_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_05JUL_1HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_05JUL_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_05JUL_rHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_05JUL_vHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_26JUL_rHYMNUS", 3 },
	{ JAZYK_CZ, "CZ_26JUL_vHYMNUS", 3 },
	{ JAZYK_CZ, "CZ_26JUL_cHYMNUS", 3 },
	{ JAZYK_CZ, "CZ_16MAJ_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_25MAR_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_01NOV_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_15SEP_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_16SEP_cHYMNUS", 2 },
	{ JAZYK_CZ, "25APR_cHYMNUS", 2 },
	{ JAZYK_CZ, "21SEP_cHYMNUS", 2 },
	{ JAZYK_CZ, "18OKT_cHYMNUS", 2 },
	{ JAZYK_UNDEF, "SPMVSr_HYMNUS", 3 },
	{ JAZYK_UNDEF, "SPMVSc_HYMNUS", 3 },
	{ JAZYK_CZ, "CZ_SPMVSr_HYMNUS", 6 },
	{ JAZYK_CZ, "CZ_SPMVSc_HYMNUS", 6 },
	{ JAZYK_CZ, "05JUL_1HYMNUS", 2 },
	{ JAZYK_SK, "05JUL_1HYMNUS", 2 },
	{ JAZYK_SK, "05JUL_vHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_OZZ_cHYMNUS", 5 },
	{ JAZYK_CZ, "CZ_OZZ_rHYMNUS", 5 },
	{ JAZYK_CZ, "CZ_OZZ_vHYMNUS", 5 },
	{ JAZYK_CZ, "CZ_OZZ_9HYMNUS", 4 },
	{ JAZYK_CZ, "CZ_OZZ_2HYMNUS", 4 },
	{ JAZYK_CZ, "CZ_OZZ_3HYMNUS", 4 },
	{ JAZYK_CZ, "POST1_cHYMNUS", 2 },
	{ JAZYK_CZ, "POST1_rHYMNUS", 2 },
	{ JAZYK_CZ, "POST1_9HYMNUS", 2 },
	{ JAZYK_CZ, "POST1_2HYMNUS", 2 },
	{ JAZYK_CZ, "POST1_3HYMNUS", 2 },
	{ JAZYK_CZ, "POST1_vHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_POST1_rHYMNUS", 4 },
	{ JAZYK_CZ, "CZ_POST1_rNEHYMNUS", 4 },
	{ JAZYK_CZ, "VTYZ_9HYMNUS", 2 },
	{ JAZYK_CZ, "VTYZ_2HYMNUS", 2 },
	{ JAZYK_CZ, "VTYZ_3HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VTYZ_1NEHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VTYZ_rNEHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VTYZ_cNEHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VTYZ_vNEHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VTYZ_9NEHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VTYZ_2NEHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VTYZ_3NEHYMNUS", 2 },
	{ JAZYK_CZ, "VTROJ_9NEHYMNUS", 2 },
	{ JAZYK_CZ, "VTROJ_2NEHYMNUS", 2 },
	{ JAZYK_CZ, "VTROJ_3NEHYMNUS", 2 },
	{ JAZYK_CZ, "VN1_9HYMNUS", 2 },
	{ JAZYK_CZ, "VN1_2HYMNUS", 2 },
	{ JAZYK_CZ, "VN1_3HYMNUS", 2 },
	{ JAZYK_CZ, "p_HYMNUS_NE", 2 },
	{ JAZYK_CZ, "k_HYMNUS_SO", 2 },
	{ JAZYK_CZ, "k_HYMNUS_NE", 2 },
	{ JAZYK_CZ, "k_HYMNUS_CZ", 6 },
	{ JAZYK_CZ, "p_HYMNUS_CZ", 6 },
	{ JAZYK_CZ, "VN1_p_HYMNUS_NE", 2 },
	{ JAZYK_CZ, "VN1_k_HYMNUS_SO", 2 },
	{ JAZYK_CZ, "VN1_k_HYMNUS_NE", 2 },
	{ JAZYK_CZ, "VN1_k_HYMNUS_PO", 2 },
	{ JAZYK_CZ, "VN1_k_HYMNUS_UT", 2 },
	{ JAZYK_CZ, "VN1_k_HYMNUS_STR", 2 },
	{ JAZYK_CZ, "VN1_k_HYMNUS_STV", 2 },
	{ JAZYK_CZ, "VN1_k_HYMNUS_PI", 2 },
	{ JAZYK_CZ, "VN1_k_HYMNUS_CZ", 7 },
	{ JAZYK_CZ, "VN1_p_HYMNUS_CZ", 7 },
	{ JAZYK_CZ, "_2NE_1HYMNUS_CZ", 3 },
	{ JAZYK_CZ, "_2NE_rHYMNUS_CZ", 2 },
	{ JAZYK_CZ, "_2NE_vHYMNUS_CZ", 2 },
	{ JAZYK_CZ, "_2PO_vHYMNUS_CZ", 2 },
	{ JAZYK_CZ, "_2UT_vHYMNUS_CZ", 2 },
	{ JAZYK_CZ, "_2STR_rHYMNUS_CZ", 2 },
	{ JAZYK_CZ, "_2STR_vHYMNUS_CZ", 2 },
	{ JAZYK_CZ, "_2STV_vHYMNUS_CZ", 2 },
	{ JAZYK_CZ, "_2PI_rHYMNUS_CZ", 2 },
	{ JAZYK_CZ, "_2PI_vHYMNUS_CZ", 2 },
	{ JAZYK_CZ, "_2PO_cHYMNUS_CZ", 2 },
	{ JAZYK_CZ, "_2UT_cHYMNUS_CZ", 2 },
	{ JAZYK_CZ, "_2STV_cHYMNUS_CZ", 2 },
	{ JAZYK_CZ, "_2SO_cHYMNUS_CZ", 2 },
	{ JAZYK_CZ, "CZ_SCVM_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_SCMM_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_SCZM_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_SCAM_cHYMNUS", 2 },
	{ JAZYK_CZ, "SCPM_vHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_SCPM_1HYMNUS", 6 },
	{ JAZYK_CZ, "CZ_SCPM_cHYMNUS", 6 },
	{ JAZYK_CZ, "CZ_SCPM_rHYMNUS", 6 },
	{ JAZYK_CZ, "CZ_SCPM_vHYMNUS", 6 },
	{ JAZYK_CZ, "CZ_SCPN_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_SCPNV_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_SCSZ_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_SCSZV_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_22JUL_cHYMNUS", 2 },
	{ JAZYK_SK, "KNAZA_cHYMNUS", 2 }, // ad experimendum
	{ JAZYK_SK, "KNAZA_rHYMNUS", 2 }, // ad experimendum
	{ JAZYK_SK, "KNAZA_vHYMNUS", 2 }, // ad experimendum
	{ JAZYK_SK, "TK_1HYMNUS", 2 },
	{ JAZYK_SK, "TK_cHYMNUS", 2 },
	{ JAZYK_SK, "TK_rHYMNUS", 2 },
	{ JAZYK_SK, "TK_vHYMNUS", 2 },
	{ JAZYK_HU, "TK_1HYMNUS", 2 },
	{ JAZYK_HU, "TK_cHYMNUS", 2 },
	{ JAZYK_HU, "TK_rHYMNUS", 2 },
	{ JAZYK_HU, "TK_vHYMNUS", 2 },
	{ JAZYK_CZ_OP, "TK_1HYMNUS", 2 },
	{ JAZYK_CZ_OP, "TK_cHYMNUS", 2 },
	{ JAZYK_CZ_OP, "TK_rHYMNUS", 2 },
	{ JAZYK_CZ_OP, "TK_vHYMNUS", 2 },
	{ JAZYK_SK, "21NOV_cHYMNUS", 2 },
	{ JAZYK_HU, "21NOV_cHYMNUS", 2 },
	{ JAZYK_CZ, "04JUL_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_ZDS_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_ZDS_rHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_ZDS_1HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_ZDS_vHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_TK_rHYMNUS", 2 },
	{ JAZYK_CZ, "TROJ_9HYMNUS", 2 }, // nedáváme možnost vzít hymny podle sudého/lichého týdne
	{ JAZYK_CZ, "TROJ_2HYMNUS", 2 },
	{ JAZYK_CZ, "TROJ_3HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_SRDCA_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_SRDCA_rHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_SRDCA_1HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_SRDCA_vHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_SVROD_cHYMNUS", 6 },
	{ JAZYK_CZ, "CZ_SVROD_rHYMNUS", 6 },
	{ JAZYK_CZ, "CZ_15AUG_rHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_15SEP_rHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_15SEP_vHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_16SEP_rHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_16SEP_vHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_28SEP_rHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_01NOV_1HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_01NOV_rHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_01NOV_vHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_13NOV_rHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_13NOV_vHYMNUS", 2 },
	{ JAZYK_SK, "PMMC_vHYMNUS", 2 },
	{ JAZYK_CZ, "PMMC_vHYMNUS", 2 },
	{ JAZYK_CZ_OP, "PMMC_vHYMNUS", 2 },
		// CZ mezidobí, modlitba uprostřed dne, hymny ze žaltáře
		// liché týdny
	{ JAZYK_CZ, "9_HYMNUS_LICHY_NE", 2 },
	{ JAZYK_CZ, "2_HYMNUS_LICHY_NE", 2 },
	{ JAZYK_CZ, "3_HYMNUS_LICHY_NE", 2 },
	{ JAZYK_CZ, "9_HYMNUS_LICHY_PO", 2 },
	{ JAZYK_CZ, "2_HYMNUS_LICHY_PO", 2 },
	{ JAZYK_CZ, "3_HYMNUS_LICHY_PO", 2 },
	{ JAZYK_CZ, "9_HYMNUS_LICHY_UT", 2 },
	{ JAZYK_CZ, "2_HYMNUS_LICHY_UT", 2 },
	{ JAZYK_CZ, "3_HYMNUS_LICHY_UT", 2 },
	{ JAZYK_CZ, "9_HYMNUS_LICHY_STR", 2 },
	{ JAZYK_CZ, "2_HYMNUS_LICHY_STR", 2 },
	{ JAZYK_CZ, "3_HYMNUS_LICHY_STR", 2 },
	{ JAZYK_CZ, "9_HYMNUS_LICHY_STV", 2 },
	{ JAZYK_CZ, "2_HYMNUS_LICHY_STV", 2 },
	{ JAZYK_CZ, "3_HYMNUS_LICHY_STV", 2 },
	{ JAZYK_CZ, "9_HYMNUS_LICHY_PI", 2 },
	{ JAZYK_CZ, "2_HYMNUS_LICHY_PI", 2 },
	{ JAZYK_CZ, "3_HYMNUS_LICHY_PI", 2 },
	{ JAZYK_CZ, "9_HYMNUS_LICHY_SO", 2 },
	{ JAZYK_CZ, "2_HYMNUS_LICHY_SO", 2 },
	{ JAZYK_CZ, "3_HYMNUS_LICHY_SO", 2 },
		// sudé týdny
	{ JAZYK_CZ, "9_HYMNUS_SUDY_NE", 2 },
	{ JAZYK_CZ, "2_HYMNUS_SUDY_NE", 2 },
	{ JAZYK_CZ, "3_HYMNUS_SUDY_NE", 2 },
	{ JAZYK_CZ, "9_HYMNUS_SUDY_PO", 2 },
	{ JAZYK_CZ, "2_HYMNUS_SUDY_PO", 2 },
	{ JAZYK_CZ, "3_HYMNUS_SUDY_PO", 2 },
	{ JAZYK_CZ, "9_HYMNUS_SUDY_UT", 2 },
	{ JAZYK_CZ, "2_HYMNUS_SUDY_UT", 2 },
	{ JAZYK_CZ, "3_HYMNUS_SUDY_UT", 2 },
	{ JAZYK_CZ, "9_HYMNUS_SUDY_STR", 2 },
	{ JAZYK_CZ, "2_HYMNUS_SUDY_STR", 2 },
	{ JAZYK_CZ, "3_HYMNUS_SUDY_STR", 2 },
	{ JAZYK_CZ, "9_HYMNUS_SUDY_STV", 2 },
	{ JAZYK_CZ, "2_HYMNUS_SUDY_STV", 2 },
	{ JAZYK_CZ, "3_HYMNUS_SUDY_STV", 2 },
	{ JAZYK_CZ, "9_HYMNUS_SUDY_PI", 2 },
	{ JAZYK_CZ, "2_HYMNUS_SUDY_PI", 2 },
	{ JAZYK_CZ, "3_HYMNUS_SUDY_PI", 2 },
	{ JAZYK_CZ, "9_HYMNUS_SUDY_SO", 2 },
	{ JAZYK_CZ, "2_HYMNUS_SUDY_SO", 2 },
	{ JAZYK_CZ, "3_HYMNUS_SUDY_SO", 2 },
	// CZ mezidobí, modlitba uprostřed dne, hymny k volnému výběru
	{ JAZYK_CZ, "9_HYMNUS", 3 },
	{ JAZYK_CZ, "2_HYMNUS", 3 },
	{ JAZYK_CZ, "3_HYMNUS", 3 },
	// CZ doba adventní, modlitba uprostřed dne, hymny ze žaltáře
	{ JAZYK_CZ, "ADV19_HYMNUS", 2 },
	{ JAZYK_CZ, "ADV12_HYMNUS", 2 },
	{ JAZYK_CZ, "ADV13_HYMNUS", 2 },
	{ JAZYK_CZ, "ADV29_HYMNUS", 2 },
	{ JAZYK_CZ, "ADV22_HYMNUS", 2 },
	{ JAZYK_CZ, "ADV23_HYMNUS", 2 },
	// CZ doba vánoční, modlitba uprostřed dne, hymny ze žaltáře
	{ JAZYK_CZ, "VIAN1_9HYMNUS", 2 },
	{ JAZYK_CZ, "VIAN1_2HYMNUS", 2 },
	{ JAZYK_CZ, "VIAN1_3HYMNUS", 2 },
	{ JAZYK_CZ, "VIAN2_9HYMNUS", 2 },
	{ JAZYK_CZ, "VIAN2_2HYMNUS", 2 },
	{ JAZYK_CZ, "VIAN2_3HYMNUS", 2 },
	// CZ doba vánoční, hymny k volnému výběru
	{ JAZYK_CZ, "CZ_VIAN1_cHYMNUS", 6 },
	{ JAZYK_CZ, "CZ_VIAN1_1HYMNUS", 6 },
	{ JAZYK_CZ, "CZ_VIAN1_rHYMNUS", 6 },
	{ JAZYK_CZ, "CZ_VIAN1_vHYMNUS", 6 },
	{ JAZYK_CZ, "CZ_VIAN1_9HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VIAN1_2HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VIAN1_3HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VIAN2_cHYMNUS", 6 },
	{ JAZYK_CZ, "CZ_VIAN2_1HYMNUS", 7 },
	{ JAZYK_CZ, "CZ_VIAN2_rHYMNUS", 8 },
	{ JAZYK_CZ, "CZ_VIAN2_vHYMNUS", 7 },
	{ JAZYK_CZ, "CZ_VIAN2_9HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VIAN2_2HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VIAN2_3HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VIAN2_ZJVrHYMNUS", 2 },
	// CZ doba velikonoční, hymny k volnému výběru
	{ JAZYK_CZ, "CZ_VN1_1HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VN1_vHYMNUS", 4 },
	{ JAZYK_CZ, "CZ_VN1_rHYMNUS", 4 },
	{ JAZYK_CZ, "CZ_VN1_cHYMNUS", 4 },
	{ JAZYK_CZ, "CZ_VN2_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VN2_1HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VN2_rHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VN2_9HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VN2_2HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_VN2_3HYMNUS", 2 },
	// CZ doba velikonoční: Nanebevstoupení Páně, hymny k volnému výběru
	{ JAZYK_CZ, "CZ_NAN_1HYMNUS", 2 },
	{ JAZYK_CZ, "CZ_NAN_rHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_NAN_cHYMNUS", 2 },
	{ JAZYK_CZ, "CZ_NAN_vHYMNUS", 2 },
	// špeciálne hymny pre 34. týždeň Cezročného obdobia; not fot CZ
	{ JAZYK_SK, "OCR34c_HYMNUS", 2 },
	{ JAZYK_SK, "OCR34r_HYMNUS", 2 },
	{ JAZYK_SK, "OCR34v_HYMNUS", 2 },
};

_struct_lang_anchor_and_count pocet_citanie1_multi_anchor_count[] = {
	{ JAZYK_UNDEF, "OZZ_cCIT1", 3 },
	{ JAZYK_UNDEF, "SCPM_OCR_cCIT1", 2 },
	{ JAZYK_UNDEF, "SCSM_ZVI_cCIT1", 2 },
	{ JAZYK_UNDEF, "SCSM_ZVII_cCIT1", 2 },
	{ JAZYK_UNDEF, "SCSM_OCR_cCIT1", 2 },
	{ JAZYK_UNDEF, "SCSMV_OCR_cCIT1", 2 },
	{ JAZYK_UNDEF, "SCSZ_ZVI_cCIT1", 2 },
	{ JAZYK_UNDEF, "SCSZ_ZVII_cCIT1", 2 },
	{ JAZYK_UNDEF, "SCSZV_OCR_cCIT1", 2 },
	{ JAZYK_UNDEF, "SCSZ_OCR_cCIT1", 2 },
	{ JAZYK_UNDEF, "SCSZM_OCR_cCIT1", 2 },
	{ JAZYK_CZ_OP, "04MAJ_cCIT1", 2 },
};

_struct_lang_anchor_and_count pocet_citanie2_multi_anchor_count[] = {
	{ JAZYK_UNDEF, "SPMVSc_CIT2", 4 },
	{ JAZYK_SK, "05JUL_cCIT2", 3 },
	{ JAZYK_UNDEF, "OZZ_cCIT2", 2 },
	{ JAZYK_UNDEF, "SCPN_cCIT2", 2 },
	{ JAZYK_UNDEF, "SCPNV_cCIT2", 2 },
	{ JAZYK_UNDEF, "SCPM_cCIT2", 3 },
	{ JAZYK_CZ, "06MAJ_cCIT2", 2 },
	{ JAZYK_UNDEF, "SCSM_cCIT2", 2 },
	{ JAZYK_UNDEF, "SCSMV_cCIT2", 2 },
	{ JAZYK_UNDEF, "SCSZ_cCIT2", 2 },
	{ JAZYK_UNDEF, "SCSZV_cCIT2", 2 },
	{ JAZYK_UNDEF, "SCUC_cCIT2", 2 },
	{ JAZYK_SK, "05OKT_cCIT2", 2 },
	{ JAZYK_SK, "15SEP_cCIT2", 2 },
	{ JAZYK_UNDEF, "VPCHR_cCIT2", 2 },
	{ JAZYK_SK, "25NOV_cCIT2", 2 },
	{ JAZYK_CZ_OP, "03JAN2_cCIT2", 2 },
	{ JAZYK_CZ_OP, "07JAN2_cCIT2", 2 },
	{ JAZYK_CZ_OP, "19JAN_cCIT2", 2 },
	{ JAZYK_CZ_OP, "28JAN2_cCIT2", 3 },
	{ JAZYK_CZ_OP, "04FEB_cCIT2", 2 },
	{ JAZYK_CZ_OP, "20APR_cCIT2", 2 },
	{ JAZYK_CZ_OP, "29APR2_cCIT2", 3 },
	{ JAZYK_CZ_OP, "30APR3_cCIT2", 2 },
	{ JAZYK_CZ_OP, "04MAJ_cCIT2", 3 },
	{ JAZYK_CZ_OP, "05MAJ_cCIT2", 2 },
	{ JAZYK_CZ_OP, "08MAJ_cCIT2", 3 },
	{ JAZYK_CZ_OP, "10MAJ_cCIT2", 2 },
	{ JAZYK_CZ_OP, "30MAJ2_cCIT2", 4 },
	{ JAZYK_CZ_OP, "04JUN_cCIT2", 2 },
	{ JAZYK_CZ_OP, "04JUL3_cCIT2", 2 },
	{ JAZYK_CZ_OP, "09JUL_cCIT2", 2 },
	{ JAZYK_CZ_OP, "09JUL2_cCIT2", 2 },
	{ JAZYK_CZ_OP, "17JUL2_cCIT2", 2 },
	{ JAZYK_CZ_OP, "22JUL2_cCIT2", 2 },
	{ JAZYK_CZ_OP, "08AUG2_cCIT2", 4 },
	{ JAZYK_CZ_OP, "15AUG_cCIT2", 2 },
	{ JAZYK_CZ_OP, "17AUG_cCIT2", 2 },
	{ JAZYK_CZ_OP, "23AUG2_cCIT2", 2 },
	{ JAZYK_CZ_OP, "28AUG2_cCIT2", 3 },
	{ JAZYK_SK, "16SEP_cCIT2", 2 },
	{ JAZYK_LA, "16SEP_cCIT2", 2 },
	{ JAZYK_HU, "16SEP_cCIT2", 2 },
	{ JAZYK_CZ, "16SEP2_cCIT2", 2 },
	{ JAZYK_CZ, "17SEP3_cCIT2", 2 },
	{ JAZYK_CZ_OP, "16SEP2_cCIT2", 2 },
	{ JAZYK_CZ_OP, "17SEP3_cCIT2", 2 },
	{ JAZYK_CZ_OP, "18SEP_cCIT2", 2 },
	{ JAZYK_CZ_OP, "26SEP2_cCIT2", 2 },
	{ JAZYK_CZ_OP, "04OKT2_cCIT2", 3 },
	{ JAZYK_CZ_OP, "07OKT2_cCIT2", 4 },
	{ JAZYK_CZ_OP, "03NOV2_cCIT2", 4 },
	{ JAZYK_CZ_OP, "07NOV_cCIT2", 4 },
	{ JAZYK_CZ_OP, "08NOV_cCIT2", 4 },
	{ JAZYK_CZ_OP, "15NOV2_cCIT2", 3 },
	{ JAZYK_CZ_OP, "24NOV2_cCIT2", 2 },
	{ JAZYK_HU, "24OKT2_cCIT2", 2 },
	{ JAZYK_LA, "29JUL_cCIT2", 2 }, // added new reading (old reading left as second alternative)
};

_struct_lang_anchor_and_count pocet_antifona_multi_anchor_count[] = {
	{ JAZYK_UNDEF, "SCSZ_iANT1", 2 },
	{ JAZYK_UNDEF, "SCPN_iANT1", 2 },
	{ JAZYK_UNDEF, "SCPNV_iANT1", 2 },
	{ JAZYK_UNDEF, "VPCHR_iANT1", 2 },
	{ JAZYK_UNDEF, "SPMVS_rBENEDIKTUS", 6 },
	{ JAZYK_UNDEF, "SPMVS_iANT1", 2 },
	{ JAZYK_UNDEF, "SCPM_iANT1", 2 },
	{ JAZYK_UNDEF, "SCPM_1MAGNIFIKAT", 2 },
	{ JAZYK_UNDEF, "SCDP_vMAGNIFIKAT", 2 },
	{ JAZYK_UNDEF, "SCSM_iANT1", 2 },
	{ JAZYK_UNDEF, "SCSZRH_iANT1", 2 },
	{ JAZYK_UNDEF, "SCSMRH_iANT1", 2 },
	{ JAZYK_UNDEF, "SCSZRH_1MAGNIFIKAT", 2 },
	{ JAZYK_UNDEF, "SCSMRH_1MAGNIFIKAT", 2 },
	{ JAZYK_UNDEF, "SCSZRH_rBENEDIKTUS", 2 },
	{ JAZYK_UNDEF, "SCSMRH_rBENEDIKTUS", 2 },
	{ JAZYK_UNDEF, "SCSZRH_vMAGNIFIKAT", 2 },
	{ JAZYK_UNDEF, "SCSMRH_vMAGNIFIKAT", 2 },
	{ JAZYK_CZ_OP, "15AUG_rBENEDIKTUS", 2 },
};

_struct_lang_anchor_and_count pocet_maria_ant_multi_anchor_count[] = {
	{ JAZYK_SK, "_k_MARIANSKE-ANTIFONY", 6 }, // including special case for OFM family
	{ JAZYK_CZ, "_k_MARIANSKE-ANTIFONY", 7 }, // including two alternative cases
	{ JAZYK_CZ_OP, "_k_MARIANSKE-ANTIFONY", 6 }, // including Latin Salve Regina
	{ JAZYK_HU, "_k_MARIANSKE-ANTIFONY", 10 }, // including alternative translations
	{ JAZYK_HU, "_k_MARIANSKE-ANTIFONYVE", 2 }, // including alternative translations
	{ JAZYK_IS, "_k_MARIANSKE-ANTIFONY", 5 }, 
};

_struct_lang_anchor_and_count pocet_modlitba_multi_anchor_count[] = {
	{ JAZYK_UNDEF, "SPMVSr_MODLITBA", 6 },
	{ JAZYK_SK, "SRDCA_MODLITBA", 2 },
	{ JAZYK_SK, "NAN_MODLITBA", 2 },
	{ JAZYK_SK, "ZDS_1MODLITBA", 2 },
	{ JAZYK_SK, "23APR_MODLITBA", 2 },
};

_struct_lang_anchor_and_count pocet_otcenas_uvod_multi_anchor_count[] = {
	{ JAZYK_SK, "_OTCENAS-UVOD", 10 },
	{ JAZYK_LA, "_OTCENAS-UVOD", 10 },
	{ JAZYK_CZ_OP, "_OTCENAS-UVOD", 10 },
	{ JAZYK_CZ, "_OTCENAS-UVOD", 7 },
	{ JAZYK_HU, "_OTCENAS-UVOD", 10 }, // they have 12 intros (according to vol. I & II of first Latin editio) but technically we can support max. 10 options
	{ JAZYK_IS, "_OTCENAS-UVOD", 10 },
};

_struct_lang_anchor_and_count pocet_prosby_multi_anchor_count[] = {
	{ JAZYK_UNDEF, "SPMVSr_PROSBY", 2 },
	{ JAZYK_UNDEF, "SCPM_1PROSBY", 2 },
	{ JAZYK_UNDEF, "SCPM_rPROSBY", 2 },
	{ JAZYK_UNDEF, "SCPM_vPROSBY", 2 },
	{ JAZYK_SK, "_p_UKONKAJ", 3 },
	{ JAZYK_SK, "_k_UKONKAJ", 3 },
	{ JAZYK_CZ, "_p_UKONKAJ", 4 },
	{ JAZYK_CZ, "_k_UKONKAJ", 4 },
	{ JAZYK_CZ_OP, "_p_UKONKAJ", 4 },
	{ JAZYK_CZ_OP, "_k_UKONKAJ", 4 },
};

_struct_lang_anchor_and_count pocet_kcit_resp_multi_anchor_count[] = {
	{ JAZYK_UNDEF, "SPMVSr_CIT", 3 },
	{ JAZYK_UNDEF, "SPMVSr_RESP", 3 },
	{ JAZYK_UNDEF, "OZZ_vRESP", 2 },
};

// override for propria
_struct_lang_cal_type_anchor_and_count pocet_multi_lang_cal_type_anchor_count[] = {
	{ JAZYK_CZ, KALENDAR_CZ_OPRAEM, BASE_OPT_6_CITANIE2_MULTI, "04FEB_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OPRAEM, BASE_OPT_6_CITANIE2_MULTI, "28AUG_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OPRAEM, BASE_OPT_6_HYMNUS_MULTI, "06JUN_vHYMNUS", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OPRAEM, BASE_OPT_6_HYMNUS_MULTI, "02MAJ2_vHYMNUS", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OFM, BASE_OPT_6_CITANIE2_MULTI, "08NOV_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OFMCAP, BASE_OPT_6_CITANIE2_MULTI, "25SEP_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OFMCAP, BASE_OPT_6_CITANIE2_MULTI, "13OKT_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OFMCAP, BASE_OPT_6_CITANIE2_MULTI, "08NOV_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OCD, BASE_OPT_6_HYMNUS_MULTI, "16JUL_1HYMNUS", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OCD, BASE_OPT_6_HYMNUS_MULTI, "16JUL_rHYMNUS", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OCD, BASE_OPT_6_HYMNUS_MULTI, "16JUL_vHYMNUS", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OCD, BASE_OPT_6_CITANIE2_MULTI, "16JUL_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OCD, BASE_OPT_6_CITANIE2_MULTI, "20JUL_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OCD, BASE_OPT_6_CITANIE2_MULTI, "09AUG_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OCD, BASE_OPT_6_HYMNUS_MULTI, "09AUG_vHYMNUS", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OCD, BASE_OPT_6_CITANIE2_MULTI, "01OKT_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OCD, BASE_OPT_6_HYMNUS_MULTI, "01OKT_rHYMNUS", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OCD, BASE_OPT_6_HYMNUS_MULTI, "01OKT_vHYMNUS", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OCD, BASE_OPT_6_HYMNUS_MULTI, "15OKT_cHYMNUS", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OCD, BASE_OPT_6_CITANIE2_MULTI, "15OKT_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OCD, BASE_OPT_6_HYMNUS_MULTI, "15OKT_vHYMNUS", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OCD, BASE_OPT_6_HYMNUS_MULTI, "14DEC_1HYMNUS", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OCD, BASE_OPT_6_HYMNUS_MULTI, "14DEC_cHYMNUS", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OCD, BASE_OPT_6_CITANIE2_MULTI, "14DEC_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OCD, BASE_OPT_6_HYMNUS_MULTI, "14DEC_rHYMNUS", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_OCD, BASE_OPT_6_HYMNUS_MULTI, "14DEC_vHYMNUS", 2 },
	{ JAZYK_SK, KALENDAR_SK_OCD, BASE_OPT_6_HYMNUS_MULTI, "16JUL_1HYMNUS", 2 },
	{ JAZYK_SK, KALENDAR_SK_OCD, BASE_OPT_6_HYMNUS_MULTI, "16JUL_rHYMNUS", 2 },
	{ JAZYK_SK, KALENDAR_SK_OCD, BASE_OPT_6_HYMNUS_MULTI, "16JUL_vHYMNUS", 2 },
	{ JAZYK_SK, KALENDAR_SK_OCD, BASE_OPT_6_CITANIE2_MULTI, "16JUL_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OCD, BASE_OPT_6_CITANIE1_MULTI, "20JUL_cCIT1", 2 },
	{ JAZYK_SK, KALENDAR_SK_OCD, BASE_OPT_6_CITANIE2_MULTI, "21JUL2_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OCD, BASE_OPT_6_CITANIE2_MULTI, "24JUL2_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OCD, BASE_OPT_6_CITANIE2_MULTI, "09AUG_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OCD, BASE_OPT_6_HYMNUS_MULTI, "14DEC_1HYMNUS", 2 },
	{ JAZYK_SK, KALENDAR_SK_OCD, BASE_OPT_6_CITANIE2_MULTI, "14DEC_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_SDB, BASE_OPT_6_CITANIE2_MULTI, "22JAN2_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_SDB, BASE_OPT_6_CITANIE2_MULTI, "24JAN_cCIT2", 3 },
	{ JAZYK_CZ, KALENDAR_CZ_SDB, BASE_OPT_6_CITANIE2_MULTI, "31JAN_cCIT2", 3 },
	{ JAZYK_CZ, KALENDAR_CZ_SDB, BASE_OPT_6_CITANIE2_MULTI, "01FEB_cCIT2", 3 },
	{ JAZYK_CZ, KALENDAR_CZ_SDB, BASE_OPT_6_CITANIE2_MULTI, "25FEB_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_SDB, BASE_OPT_6_CITANIE2_MULTI, "06MAJ_cCIT2", 3 },
	{ JAZYK_CZ, KALENDAR_CZ_SDB, BASE_OPT_6_CITANIE2_MULTI, "13MAJ_cCIT2", 3 },
	{ JAZYK_CZ, KALENDAR_CZ_SDB, BASE_OPT_6_CITANIE2_MULTI, "18MAJ2_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_SDB, BASE_OPT_6_CITANIE1_MULTI, "24MAJ_cCIT1", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_SDB, BASE_OPT_6_CITANIE2_MULTI, "24MAJ_cCIT2", 3 },
	{ JAZYK_CZ, KALENDAR_CZ_SDB, BASE_OPT_6_CITANIE2_MULTI, "23JUN_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_SDB, BASE_OPT_6_CITANIE2_MULTI, "24OKT2_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_SDB, BASE_OPT_6_CITANIE2_MULTI, "29OKT_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_SDB, BASE_OPT_6_CITANIE2_MULTI, "15NOV2_cCIT2", 2 },
	{ JAZYK_CZ, KALENDAR_CZ_SJ, BASE_OPT_6_HYMNUS_MULTI, "16MAJ_cHYMNUS", 0 }, // !!! override language-default (not use multiple hymns)
	{ JAZYK_CZ, KALENDAR_CZ_SJ, BASE_OPT_6_HYMNUS_MULTI, "CZ_16MAJ_cHYMNUS", 0 }, // !!! override language-default (not use multiple hymns)
	{ JAZYK_SK, KALENDAR_SK_CSSR, BASE_OPT_6_CITANIE1_MULTI, "TITUL_cCIT1", 2 },
	{ JAZYK_SK, KALENDAR_SK_SDB, BASE_OPT_6_CITANIE2_MULTI, "24JAN_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_SDB, BASE_OPT_6_CITANIE2_MULTI, "31JAN_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_SDB, BASE_OPT_6_CITANIE2_MULTI, "06MAJ_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_SDB, BASE_OPT_6_CITANIE2_MULTI, "13MAJ_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_SDB, BASE_OPT_6_CITANIE2_MULTI, "24MAJ_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_SDB, BASE_OPT_6_CITANIE2_MULTI, "29OKT_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OFM, BASE_OPT_6_CITANIE2_MULTI, "22JAN2_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_CM, BASE_OPT_6_CITANIE2_MULTI, "09MAJ_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_CM, BASE_OPT_6_CITANIE2_MULTI, "27NOV_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "07JAN_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "18JAN_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "28JAN_cCIT2", 3 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "04FEB_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "25MAR_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "20APR_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "29APR_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "30APR_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "08MAJ_cCIT2", 3 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "10MAJ_cCIT2", 3 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "30MAJ_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "04JUN_cCIT2", 3 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "10JUN_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "04JUL2_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "09JUL_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "09JUL2_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "18JUL_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "22JUL_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "02AUG3_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "08AUG_cCIT2", 3 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "17AUG_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "18AUG2_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "23AUG_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "28AUG_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "18SEP_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "04OKT_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "05OKT2_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "07OKT_cCIT2", 3 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "09OKT_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "22OKT2_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "03NOV_cCIT2", 3 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "07NOV_cCIT2", 4 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "08NOV_cCIT2", 4 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "15NOV_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OP, BASE_OPT_6_CITANIE2_MULTI, "24NOV_cCIT2", 3 },
	{ JAZYK_SK, KALENDAR_SK_OPRAEM, BASE_OPT_6_CITANIE2_MULTI, "04FEB_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OPRAEM, BASE_OPT_6_CITANIE2_MULTI, "28AUG_cCIT2", 2 },
	{ JAZYK_SK, KALENDAR_SK_OPRAEM, BASE_OPT_6_HYMNUS_MULTI, "06JUN_vHYMNUS", 2 },
	{ JAZYK_SK, KALENDAR_SK_OPRAEM, BASE_OPT_6_HYMNUS_MULTI, "02MAJ_vHYMNUS", 2 },
	{ JAZYK_HU, KALENDAR_HU_SDB, BASE_OPT_6_CITANIE2_MULTI, "24MAJ_cCIT2", 2 },
};

short int pocet_multi(char* _anchor, unsigned long long type) {
	short int count = 0;
	short int i = 0;
	short int lang = JAZYK_UNDEF;
	short int cal = KALENDAR_NEURCENY;

	short int size = 0;

	// first, check propria override

	_struct_lang_cal_type_anchor_and_count* ptr_propria = NULL;
	_struct_lang_cal_type_anchor_and_count* orig_propria = pocet_multi_lang_cal_type_anchor_count;
	size = sizeof(pocet_multi_lang_cal_type_anchor_count);

	_struct_lang_cal_type_anchor_and_count* endPtr_propria = ptr_propria + size / sizeof(orig_propria[0]);

	i = 0;

	while (ptr_propria < endPtr_propria) {
		lang = orig_propria[i].language;
		cal = orig_propria[i].calendar;
		if (equals(_anchor, orig_propria[i].anchor) && (lang == _global_jazyk) && (cal == _global_kalendar) && (type == orig_propria[i].type)) {
			count = orig_propria[i].count;
			return count;
		}
		ptr_propria++;
		i++;
	}

	// now, check ordinary arrays

	size = 0;

	_struct_lang_anchor_and_count* ptr = NULL;
	_struct_lang_anchor_and_count* orig = NULL;

	if (type == BASE_OPT_6_HYMNUS_MULTI) {
		ptr = pocet_hymnus_multi_anchor_count;
		size = sizeof(pocet_hymnus_multi_anchor_count);
	}
	else if (type == BASE_OPT_6_CITANIE2_MULTI) {
		ptr = pocet_citanie2_multi_anchor_count;
		size = sizeof(pocet_citanie2_multi_anchor_count);
	}
	else if (type == BASE_OPT_6_CITANIE1_MULTI) {
		ptr = pocet_citanie1_multi_anchor_count;
		size = sizeof(pocet_citanie1_multi_anchor_count);
	}
	else if (type == BASE_OPT_6_ANTIFONA_MULTI) {
		ptr = pocet_antifona_multi_anchor_count;
		size = sizeof(pocet_antifona_multi_anchor_count);
	}
	else if (type == BASE_OPT_6_MODLITBA_MULTI) {
		ptr = pocet_modlitba_multi_anchor_count;
		size = sizeof(pocet_modlitba_multi_anchor_count);
	}
	else if (type == BASE_OPT_6_PROSBY_MULTI) {
		ptr = pocet_prosby_multi_anchor_count;
		size = sizeof(pocet_prosby_multi_anchor_count);
	}
	else if (type == BASE_OPT_6_OTCENAS_UVOD_MULTI) {
		ptr = pocet_otcenas_uvod_multi_anchor_count;
		size = sizeof(pocet_otcenas_uvod_multi_anchor_count);
	}
	else if (type == BASE_OPT_6_MARIA_ANT_MULTI) {
		ptr = pocet_maria_ant_multi_anchor_count;
		size = sizeof(pocet_maria_ant_multi_anchor_count);
	}
	else if ((type == BASE_OPT_6_KCIT_RESP_MULTI) || (type == BASE_OPT_6_KRESP_MULTI)) {
		ptr = pocet_kcit_resp_multi_anchor_count;
		size = sizeof(pocet_kcit_resp_multi_anchor_count);
	}
	// here, PLACE_OPT_6_PSALM_MULTI is not used

	i = 0;
	orig = ptr; // preserve original pointer to array due to dereferencing by [i]

	_struct_lang_anchor_and_count* endPtr = ptr + size / sizeof(orig[0]);

	while (ptr < endPtr) {
		lang = orig[i].language;
		if (equals(_anchor, orig[i].anchor) && (lang == JAZYK_UNDEF || lang == _global_jazyk)) {
			count = orig[i].count;
			break;
		}
		ptr++;
		i++;
	}

	return count;
}

// explicitly listed anchors which may have "printed edition text" equivalent
_struct_lang_param_and_anchor printed_edition_lang_text_anchor[] = {
	{ JAZYK_SK, PARAM_KRESPONZ, "POST1_rRESP" },
	{ JAZYK_SK, PARAM_CITANIE1, "OCR19PIc_CIT1" },
	{ JAZYK_SK, PARAM_PROSBY, "_1PO_vPROSBY" },
	{ JAZYK_SK, PARAM_PROSBY, "_2UT_vPROSBY" },
	{ JAZYK_SK, PARAM_PROSBY, "_3STV_vPROSBY" },
	{ JAZYK_SK, PARAM_PROSBY, "ADV11PIv_PROSBY" },
	{ JAZYK_SK, PARAM_PROSBY, "VTYZ_rPROSBYSTV" },
	{ JAZYK_SK, PARAM_PROSBY, "SCAP_rPROSBY" },
	{ JAZYK_SK, PARAM_HYMNUS, "p_HYMNUS_0" },
	{ JAZYK_SK, PARAM_HYMNUS, "k_HYMNUS_0" },
};

// override for propria
_struct_lang_cal_param_and_anchor printed_edition_lang_cal_text_anchor[] = {
	{ JAZYK_SK, KALENDAR_CZ_CSSR, PARAM_KRESPONZ, "POST1_rRESP" }, // this is nonsense only for example; remove when first real record will be added!!!
};

short int is_printed_edition_text(char* _anchor, char* _paramname) {
	// Log("is_printed_edition_text: %s %s...\n", _anchor, _paramname);

	short int i = 0;
	short int lang = JAZYK_UNDEF;
	short int cal = KALENDAR_NEURCENY;

	short int size = 0;

	// first, check propria override

	_struct_lang_cal_param_and_anchor* ptr_propria = NULL;
	_struct_lang_cal_param_and_anchor* orig_propria = printed_edition_lang_cal_text_anchor;
	size = sizeof(printed_edition_lang_cal_text_anchor);

	_struct_lang_cal_param_and_anchor* endPtr_propria = ptr_propria + size / sizeof(orig_propria[0]);

	i = 0;

	while (ptr_propria < endPtr_propria) {
		lang = orig_propria[i].language;
		cal = orig_propria[i].calendar;
		if (equals(_anchor, orig_propria[i].anchor) && (lang == _global_jazyk) && (cal == _global_kalendar) && equals(_paramname, orig_propria[i].paramname)) {
			return TRUE;
		}
		ptr_propria++;
		i++;
	}

	// now, check ordinary arrays

	size = 0;

	_struct_lang_param_and_anchor* ptr = NULL;
	_struct_lang_param_and_anchor* orig = NULL;

	ptr = printed_edition_lang_text_anchor;
	size = sizeof(printed_edition_lang_text_anchor);

	i = 0;
	orig = ptr; // preserve original pointer to array due to dereferencing by [i]

	_struct_lang_param_and_anchor* endPtr = ptr + size / sizeof(orig[0]);

	while (ptr < endPtr) {
		lang = orig[i].language;
		if (equals(_anchor, orig[i].anchor) && (lang == JAZYK_UNDEF || lang == _global_jazyk) && equals(_paramname, orig[i].paramname)) {
			return TRUE;
		}
		ptr++;
		i++;
	}

	return FALSE;
}

#endif // __DBZALTAR_CPP_


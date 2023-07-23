/************************************************************/
/*                                                          */
/* hodin.h                                                  */
/* (c)1999-2023 | Juraj Vidéky | videky@breviar.sk          */
/*                                                          */
/* description | originally used for string constants       */
/*                                                          */
/*                                                          */
/*   WARNING: NEVER REMOVE COMMENTS FOR ADDING NEW VALUES   */
/*                                                          */
/*   STRING_1_FOR_NEW_LANGUAGE etc.                         */
/*                                                          */
/************************************************************/

#include "vstudio.h"

#ifndef __HODIN_H_
#define __HODIN_H_

#include "liturgia.h"
#include "mydefs.h"
#include "common.h"

const char* TEMPLATE_HTML[POCET_MODLITIEB + 1] =
{ TEMPLATE_HTML_INVITATORIUM, TEMPLATE_HTML_POSV_CITANIE, TEMPLATE_HTML_RANNE_CHVALY,
TEMPLATE_HTML_CEZ_DEN_9, TEMPLATE_HTML_CEZ_DEN_12, TEMPLATE_HTML_CEZ_DEN_3,
TEMPLATE_HTML_VESPERY, TEMPLATE_HTML_KOMPLETORIUM, TEMPLATE_HTML_STATIC_TEXT,
TEMPLATE_HTML_VESPERY, TEMPLATE_HTML_KOMPLETORIUM,
TEMPLATE_HTML_VESPERY, TEMPLATE_HTML_KOMPLETORIUM, TEMPLATE_HTML_EMPTY, TEMPLATE_HTML_EMPTY };

const char* TEMPLATE_XML[POCET_MODLITIEB + 1] =
{ TEMPLATE_XML_INVITATORIUM, TEMPLATE_XML_POSV_CITANIE, TEMPLATE_XML_RANNE_CHVALY,
TEMPLATE_XML_CEZ_DEN_9, TEMPLATE_XML_CEZ_DEN_12, TEMPLATE_XML_CEZ_DEN_3,
TEMPLATE_XML_VESPERY, TEMPLATE_XML_KOMPLETORIUM, TEMPLATE_XML_STATIC_TEXT,
TEMPLATE_XML_VESPERY, TEMPLATE_XML_KOMPLETORIUM,
TEMPLATE_XML_VESPERY, TEMPLATE_XML_KOMPLETORIUM, TEMPLATE_XML_EMPTY, TEMPLATE_XML_EMPTY };

const char* FILE_ORDINARIUM[POCET_MODLITIEB + 1] =
{ ORDINARIUM_INVITATORIUM, ORDINARIUM_POSV_CITANIE, ORDINARIUM_RANNE_CHVALY,
ORDINARIUM_CEZ_DEN, ORDINARIUM_CEZ_DEN, ORDINARIUM_CEZ_DEN,
ORDINARIUM_VESPERY, ORDINARIUM_KOMPLETORIUM, ORDINARIUM_EMPTY,
ORDINARIUM_VESPERY, ORDINARIUM_KOMPLETORIUM,
ORDINARIUM_VESPERY, ORDINARIUM_KOMPLETORIUM, ORDINARIUM_EMPTY, ORDINARIUM_EMPTY };

const char* FILE_INFO[POCET_INFO_TEXTOV + 1] =
{ FILE_INFO_ABOUT, FILE_VERSION_HISTORY };

// 2008-04-09: doplnené pre batch generovanie modlitieb
const char char_modlitby[POCET_MODLITIEB + 1] =
{ CHAR_MODL_INVITATORIUM, CHAR_MODL_POSV_CITANIE, CHAR_MODL_RANNE_CHVALY,
CHAR_MODL_CEZ_DEN_9, CHAR_MODL_CEZ_DEN_12, CHAR_MODL_CEZ_DEN_3,
CHAR_MODL_VESPERY, CHAR_MODL_KOMPLETORIUM, CHAR_SPACE,
CHAR_MODL_PRVE_VESPERY, CHAR_MODL_PRVE_KOMPLETORIUM,
CHAR_MODL_VESPERY, CHAR_MODL_KOMPLETORIUM, CHAR_MODL_NEURCENA, CHAR_MODL_VSETKY };

const char* str_modlitby[POCET_MODLITIEB + 1] =
{ STR_MODL_INVITATORIUM, STR_MODL_POSV_CITANIE, STR_MODL_RANNE_CHVALY,
STR_MODL_PREDPOLUDNIM, STR_MODL_NAPOLUDNIE, STR_MODL_POPOLUDNI,
STR_MODL_VESPERY, STR_MODL_KOMPLETORIUM, STR_EMPTY,
STR_MODL_PRVE_VESPERY, STR_MODL_PRVE_KOMPLETORIUM,
STR_MODL_VESPERY, STR_MODL_KOMPLETORIUM, STR_MODL_DETAILY, STR_MODL_VSETKY };

// the names of the prayers, lowercase (sample text)
const char* nazov_modlitby_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1] =
{
	{ "invitatórium", "uvedení do první modlitby dne", "Invitatory", "invitatorium", "", "Pozvání k modlitbě", "imádságra hívás", "ru_text", "заклік", "inngöngusöngur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "posvätné čítanie", "modlitba se čtením", "Office of Readings", "officium lectionis", "", "Modlitba se čtením", "olvasmányos imaóra", "ru_text", "гадзіна чытанняў", "óttusöngur hinn fyrri", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "ranné chvály", "ranní chvály", "Laudes", "laudes matutinæ", "", "Ranní chvály", "reggeli dicséret", "ru_text", "ютрань", "efri óttusöngur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "modlitba predpoludním", "modlitba dopoledne", "Terce", "tertia", "", "Tercie", "délelőtt", "ru_text", "малітва перад поўднем", "miðdegisbæn fyrir hádegi", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "modlitba napoludnie", "modlitba v poledne", "Sext", "sexta", "", "Sexta", "délben", "ru_text", "малітва апоўдні", "miðdegisbæn", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "modlitba popoludní", "modlitba odpoledne", "None", "nona", "", "Nona", "délután", "ru_text", "малітва пасля поўдня", "miðdegisbæn eftir hádegi", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "vešpery", "nešpory", "Vesperæ", "vesperæ", "", "Večerní chvály", "esti dicséret", "вечерня", "нешпары", "aftansöngur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "kompletórium", "kompletář", "Completary", "completorium", "", "Kompletář", "befejező imaóra", "ru_text", "камплета", "náttsöngur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "neurčená", "neurčena", "not-defined", "no data", "", "neurčena", "nem azonosított", "ru_text", "by_text", "án fyrirmæla", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "prvé vešpery", "první nešpory", "1st Vesperæ", "I vesperæ", "", "První večerní chvály", "I. esti dicséret", "ru_text", "I нешпары", "fyrsti aftansöngur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "kompletórium po prvých vešperách", "kompletář po prvních nešporách", "1st Completary", "I completorium", "", "Kompletář po prvních večerních chválách", "befejező imaóra I. e. d. után", "ru_text", "камплета пасля I нешпараў", "náttsöngur eftir Fyrsta aftansöng", /* STRING_1_FOR_NEW_LANGUAGE */ } // 2007-12-05: zmenené, kedysi bolo: "prvé kompletórium"
	, { "druhé vešpery", "druhé nešpory", "2nd Vesperæ", "II vesperæ", "", "Druhé večerní chvály", "II. esti dicséret", "ru_text", "II нешпары", "annar aftansöngur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "kompletórium po druhých vešperách", "kompletář po druhých nešporách", "2nd Completary", "II completorium", "", "Kompletář po druhých večerních chválách", "befejező imaóra II. e. d. után", "ru_text", "камплета пасля II нешпараў", "náttsöngur eftir Annan aftansöng", /* STRING_1_FOR_NEW_LANGUAGE */ } // 2007-12-05: zmenené, kedysi bolo: "druhé kompletórium"
	, { "detaily", "detaily", "Details", "details", "", "detaily", "részletek", "ru_text", "дэталі", "smáatriði", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "všetky", "všechny", "all", "omnia", "", "všechny", "összes", "ru_text", "усе", "allar", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

#define		nazov_modlitby(a)	nazov_modlitby_jazyk[a][_global_jazyk]

// the names of the prayers, lowercase (sample text)
const char* nazov_modlitby_short_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1] =
{
	{ "invitatórium", "uvedení do 1. modl. dne", "Invitatory", "invitatorium", "", "Pozvání k modl.", "imádságra hívás", "предначинание", "заклік", "inngöngusöngur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "posvätné čítanie", "modl. se čtením", "Office of Readings", "officium lectionis", "", "modl. se čtením", "olvasmányos imaóra", "час чтений", "гадзіна чытанняў", "óttusöngur hinn fyrri", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "ranné chvály", "ranní chvály", "Laudes", "laudes matutinæ", "", "Ranní chvály", "reggeli dicséret", "утреня", "ютрань", "efri óttusöngur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "modl. predpoludním", "modl. dopoledne", "Terce", "tertia", "", "Tercie", "délelőtt", "ru_text", "м. перад поўднем", "mið. fyrir hád.", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "modl. napoludnie", "modl. v poledne", "Sext", "sexta", "", "Sexta", "délben", "ru_text", "м. апоўдні", "miðdegisbæn", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "modl. popoludní", "modl. odpoledne", "None", "nona", "", "Nona", "délután", "ru_text", "м. пасля поўдня", "mið. eftir hád.", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "vešpery", "nešpory", "Vesperæ", "vesperæ", "", "Večerní chvály", "esti dicséret", "вечерня", "нешпары", "aftansöngur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "kompletórium", "kompletář", "Compline", "completorium", "", "Kompletář", "befejező imaóra", "повечерие", "камплета", "náttsöngur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "neurčená", "neurčena", "not-defined", "no data", "", "neurčena", "nem azonosított", "ru_text", "by_text", "án fyrirmæla", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "prvé vešpery", "první nešpory", "1st Vesperæ", "I vesperæ", "", "První večerní chvály", "I. esti dicséret", "ru_text", "I нешпары", "fyrsti aftansöngur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "kompletórium po 1. vešp.", "kompletář po 1. nešp.", "1st Completary", "I completorium", "", "Kompletář po 1. v. ch.", "befejező imaóra I. e. d. ut.", "ru_text", "кампл. пасля І нешп.", "náttsöngur eftir Fyrsta aftansöng", /* STRING_1_FOR_NEW_LANGUAGE */ } // 2007-12-05: zmenené, kedysi bolo: "prvé kompletórium"
	, { "(druhé) vešpery", "druhé nešpory", "2nd Vesperæ", "II vesperæ", "", "Druhé večerní chvály", "II. esti dicséret", "ru_text", "II нешпары", "annar aftansöngur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "kompletórium (po 2. vešp.)", "kompletář po 2. nešp.", "2nd Completary", "II completorium", "", "Kompletář po 2. v. ch.", "befejező imaóra II. e. d. ut.", "ru_text", "кампл. пасля IІ нешп.", "náttsöngur eftir Annan aftansöng", /* STRING_1_FOR_NEW_LANGUAGE */ } // 2007-12-05: zmenené, kedysi bolo: "druhé kompletórium"
	, { "detaily", "detaily", "Details", "details", "", "detaily", "részletek", "ru_text", "дэталі", "smáatriði", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "všetky", "všechny", "all", "omnia", "", "všechny", "összes", "ru_text", "усе", "allar", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

#define		nazov_modlitby_short(a)	nazov_modlitby_short_jazyk[a][_global_jazyk]

// the names of the prayers, sentence case (Sample text)
const char* nazov_Modlitby_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1] =
{
	{ "Invitatórium", "Uvedení do první modlitby dne", "Invitatory", "Invitatorium", "", "Pozvání k modlitbě", "Imádságra hívás", "Предначинание", "Заклік", "Inngöngusöngur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Posvätné čítanie", "Modlitba se čtením", "Office of Readings", "Officium lectionis", "", "Modlitba se čtením", "Olvasmányos imaóra", "Час чтений", "Гадзіна чытанняў", "Óttusöngur hinn fyrri", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Ranné chvály", "Ranní chvály", "Laudes", "Laudes matutinæ", "", "Ranní chvály", "Reggeli dicséret", "Утреня", "Ютрань", "Efri óttusöngur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Modlitba predpoludním", "Modlitba dopoledne", "Terce", "Tertia", "", "Tercie", "Délelőtt", "ru_text", "Малітва перад поўднем", "Miðdegisbæn fyrir hádegi", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Modlitba napoludnie", "Modlitba v poledne", "Sext", "Sexta", "", "Sexta", "Délben", "ru_text", "Малітва апоўдні", "Miðdegisbæn", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Modlitba popoludní", "Modlitba odpoledne", "None", "Nona", "", "Nona", "Délután", "ru_text", "Малітва пасля поўдня", "Miðdegisbæn eftir hádegi", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Vešpery", "Nešpory", "Vesperæ", "Vesperæ", "", "Večerní chvály", "Esti dicséret", "Вечерня", "Нешпары", "Aftansöngur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Kompletórium", "Kompletář", "Completary", "Completorium", "", "Kompletář", "Befejező imaóra", "Повечерие", "Камплета", "Náttsöngur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Neurčená", "Neurčena", "not-defined", "No data", "", "Neurčená", "Nem azonosított", "ru_text", "by_text", "Án fyrirmæla", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Prvé vešpery", "První nešpory", "1st Vesperæ", "I Vesperæ", "", "První večerní chvály", "I. Esti dicséret", "ru_text", "I Нешпары", "Fyrsti aftansöngur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Kompletórium po prvých vešperách", "Kompletář po prvních nešporách", "1st Completary", "I Completorium", "", "Kompletář po prvních večerních chválách", "Befejező imaóra I. e. d. után", "ru_text", "Камплета пасля І Нешпараў", "Náttsöngur eftir Fyrsta aftansöng", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Druhé vešpery", "Druhé nešpory", "2nd Vesperæ", "II Vesperæ", "", "Druhé večerní chvály", "II. Esti dicséret", "ru_text", "II Нешпары", "Annar aftansöngur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Kompletórium po druhých vešperách", "Kompletář po druhých nešporách", "2nd Completary", "II Completorium", "", "Kompletář po druhých večerních chválách", "Befejező imaóra II. e. d. után", "ru_text", "Камплета пасля IІ Нешпараў", "Náttsöngur eftir Annan aftansöng", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Detaily", "Detaily", "Details", "Details", "", "Detaily", "Részletek", "ru_text", "Дэталі", "Smáatriði", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "všetky", "všechny", "all", "omnia", "", "všechny", "összes", "ru_text", "усе", "allar", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

#define		nazov_Modlitby(a)	nazov_Modlitby_jazyk[a][_global_jazyk]

// strings of buttons - abbreviations of prayer names // shortened because of usage on mobile devices (Android)
const char* html_button_nazov_modlitby_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1] =
{
	{ "Inv.", "Inv.", "Inv.", "Inv.", "", "Inv.", "Imád.", "Пред.", "Заклік", "Inng.", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Posv. čít.", "Čtení", "Reading", "Off. lect.", "", "Čtení", "Olvasm. i.", "Ч. чт.", "Гадз. чыт.", "Ótt. fyrri", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Ranné ch.", "Ranní ch.", "Morning pr.", "Laudes", "", "Ranní ch.", "Reggeli dics.", "Утреня", "Ютрань", "Efri ótt.", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "9h", "9h", "9h", "Tertia", "", "Tercie", "Délelőtt", "ru_text", "9 г.", "9 kl.", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "12h", "12h", "12h", "Sexta", "", "Sexta", "Délben", "ru_text", "12 г.", "12 kl.", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "15h", "15h", "15h", "Nona", "", "Nona", "Délután", "ru_text", "15 г.", "15 kl.", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Vešpery", "Nešpory", "Vesperæ", "Vesperæ", "", "Večerní ch.", "Esti dics.", "Вечерня", "Нешпары", "Aftans.", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Kompl.", "Kompl.", "Compl.", "Compl.", "", "Kompl.", "Befejező i.", "Повеч.", "Кампл.", "Nátts.", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "neurčená", "neurčena", "not-defined", "no data", "", "neurčena", "nem azonosított", "ru_text", "by_text", "án fyrirmæla", /* STRING_1_FOR_NEW_LANGUAGE */ } // táto sa pre HTML buttony nepoužíva
	, { "Prvé vešp.", "První nešp.", "1st Vesperæ", "I vesperæ", "", "1. večerní ch.", "I. esti dics.", "ru_text", "I Нешпары", "Fyrsti aftans.", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Prvé kompl.", "První kompl.", "Compl.", "Compl.", "", "1. kompl.", "Bef. i. I. e. d. után", "ru_text", "Кампл. пас. І Нешп.", "Nátts. eft. Fyrsta aftans.", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Druhé vešp.", "Druhé nešpory", "2nd Vesperæ", "II vesperæ", "", "2. večerní ch.", "II. esti dics.", "ru_text", "II Нешпары", "Annar aftans.", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Druhé kompl.", "Druhý kompl.", "2nd Completary", "II completorium", "", "2. kompl.", "Bef. i. II. e. d. után", "ru_text", "Кампл. пас. IІ Нешп.", "Nátts. eft. Annan aftans.", /* STRING_1_FOR_NEW_LANGUAGE */ }
	// JUV: temporarily disabled due to lack of colspan functionality in display: table etc. elements | , { "výber spoločnej časti...", "výběr společné části...", "common texts...", "optiónes...", "", "výběr společné části...", "közös rész kiválasztása...", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "výber...", "výběr...", "common texts...", "optiones...", "", "výběr...", "közös...", "ru_text", "by_text", "val...", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "všetky", "všechny", "all", "omnia", "", "všechny", "összes", "ru_text", "усе", "allar", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

#define		html_button_nazov_modlitby(a)	html_button_nazov_modlitby_jazyk[a][_global_jazyk]

// the prefix for common parts of celebration
const char* nazov_spolc_zospolc_jazyk[POCET_JAZYKOV + 1] =
{ "Zo spoločnej časti", "Společné texty", "Common texts", "Communia", "", "Společné texty", "közös zsolozsmája", "ru_text", "Агульныя тэксты", "Frá almennum textum", /* STRING_1_FOR_NEW_LANGUAGE */ };

const char* nazov_spolc_oficiumza_jazyk[POCET_JAZYKOV + 1] =
{ "Ofícium za", "Společné texty", "Common texts", "Communia", "", "Společné texty", "közös zsolozsmája", "ru_text", "Агульныя тэксты", "Tíðabænir", /* STRING_1_FOR_NEW_LANGUAGE */ };

// the --CELEBRATION-- for common parts of celebration
const char* nazov_spolc_sviatky_jazyk[POCET_JAZYKOV + 1] =
{ "na sviatky", /*"na svátky"*/"", "", "", "", /*"na svátky"*/"", "", "ru_text", "пра", /*"á hátíðardögum"*/"", /* STRING_1_FOR_NEW_LANGUAGE */};

// the --ANNIVERSARY-- for common parts of celebration
const char* nazov_spolc_vyrocie_jazyk[POCET_JAZYKOV + 1] =
{ "na výročie", "na výročí", "", "ad anniversarium", "", "na výročí", "", "ru_text", "на", "fyrir árlegan minningardag", /* STRING_1_FOR_NEW_LANGUAGE */ };

// the --OR-- (alternative) for common parts of celebration
const char* nazov_spolc_alebo_jazyk[POCET_JAZYKOV + 1] =
{ "alebo", "nebo", "or", "vel", "", "nebo", "vagy", "или", "або", "eða", /* STRING_1_FOR_NEW_LANGUAGE */ };

// the names of the common texts (e.g.: for bishops, for saint men, for apostles...)
const char* nazov_spolc_jazyk[POCET_SPOL_CASTI + 1][POCET_JAZYKOV + 1] =
{
	{ "neurčená", "neurčena", "not decided", "non definitæ", "", "", "", "ru_text", "by_text", "ótilgreint", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "duchovných pastierov: pre kňazov", "o duchovních pastýřích (o kněžích)", "", "pastorum: pro presbytero", "", "O duchovních pastýřích – o kněžích", "lelkipásztorok – papok", "ru_text", "пастыраў: пра прэзбітэраў", "fyrir hirða: prestar", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "duchovných pastierov: pre biskupov", "o duchovních pastýřích (o biskupech)", "", "pastorum: pro episcopo", "", "O duchovních pastýřích – o biskupech", "lelkipásztorok – püspökök", "ru_text", "пастыраў: пра біскупаў", "fyrir hirða: biskupar", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "duchovných pastierov: pre pápežov", "o duchovních pastýřích (o papeži)", "", "pastorum: pro papa", "", "O duchovních pastýřích – o papeži", "lelkipásztorok – pápa", "ru_text", "пастыраў: пра папу", "fyrir hirða: páfar", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "učiteľov Cirkvi", "o učitelích církve", "", "doctorum Ecclesiæ", "", "O učitelích církve", "egyháztanítók", "ru_text", "доктараў Касцёла", "fyrir kirkjufræðara", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "apoštolov", "o apoštolech", "", "Apostolorum", "", "O apoštolech", "apostolok", "ru_text", "Апосталаў", "fyrir postula", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "jedného mučeníka", "o jednom mučedníkovi", "", "unius martyris", "", "O mučedníkovi", "vértanú férfi", "ru_text", /* аднаго */ "мучаніка", "fyrir eins píslarvotts", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "viacerých mučeníkov", "o více mučednících", "", "plurimorum martyrum", "", "O více mučednících", "több vértanú", "ru_text", "некалькіх мучанікаў", "fyrir fleiri en eins píslarvotts", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Panny Márie", "o Panně Marii", "", "Beatæ Mariæ Virginis", "", "O Panně Marii", "Szűz Mária", "ru_text", "Найсвяцейшую Панну Марыю", "fyrir sællar Maríu meyjar", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "svätých mužov: pre rehoľníkov", "o svatých mužích (o řeholnících)", "", "sanctorum virorum: pro religiosis", "", "O svatých mužích – o řeholnících", "szerzetes", "ru_text", "святых мужчын: пра законнікаў", "fyrir heilagra manna: klaustur- og reglufólk", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "svätých mužov", "o svatých mužích", "", "sanctorum virorum", "", "O svatých mužích", "szent férfiak", "ru_text", "святых мужчын", "fyrir heilagra manna", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "panien", "o pannách", "", "virginum", "", "O pannách", "szüzek", "ru_text", "паннаў", "fyrir meyja", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "svätých žien: pre rehoľnice", "o svatých ženách (o řeholnicích)", "", "sanctarum mulierum: pro religiosis", "", "O svatých ženách – o řeholnicích", "apáca", "ru_text", "святых жанчын: пра законніц", "fyrir heilagra kvenna: nunnur", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "svätých žien", "o svatých ženách", "", "sanctarum mulierum", "", "O svatých ženách", "szent asszonyok", "ru_text", "святых жанчын", "fyrir heilagra kvenna", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "duchovných pastierov: pre viacerých", "o více duchovních pastýřích", "", "plurium pastorum", "", "O více duchovních pastýřích", "több lelkipásztor", "ru_text", "некалькіх пастыраў", "fyrir hirða: fleiri en einn hirði", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "jednej mučenice", "o jedné mučednici", "", "unius martyris", "", "O mučednici", "vértanú nő", "ru_text", "мyчаніцy", "fyrir píslarvotts úr röðum heilagra kvenna", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "svätých žien: pre vychovávateľky", "o svatých ženách (o vychovatelkách)", "", "sanctarum mulierum: pro educatoribus", "", "O svatých ženách – o vychovatelkách", "nevelő asszonyok", "ru_text", "святых жанчын: пра выхавацеляў", "fyrir heilagra kvenna: uppalendur", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "svätých mužov: pre vychovávateľov", "o svatých mužích (o vychovatelích)", "", "sanctorum virorum: pro educatoribus", "", "O svatých mužích – o vychovatelích", "nevelő férfiak", "ru_text", "святых мужчын: пра выхавацеляў", "fyrir heilagra karla: uppalendur", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "svätých žien: pre tie, čo konali skutky milosrdenstva", "o svatých ženách (které vynikaly milosrdnými skutky)", "", "sanctarum mulierum: pro iis qui opera misericordiæ exercuerunt", "", "O svatých ženách – o ženě, která vynikala milosrdnými skutky", "jótékonykodó asszonyok", "ru_text", "святых жанчын, якія здзяйснялі ўчынкі міласэрнасці", "fyrir heilagra kvenna: þær sem vinna miskunnarverk", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "svätých mužov: pre tých, čo konali skutky milosrdenstva", "o svatých mužích (kteří vynikali milosrdnými skutky)", "", "sanctorum virorum: pro iis qui opera misericordiæ exercuerunt", "", "O svatých mužích – o muži, který vynikal milosrdnými skutky", "jótékonykodó férfiak", "ru_text", "святых мужчын, якія здзяйснялі ўчынкі міласэрнасці", "fyrir heilaga karla: þeir sem vinna miskunnarverk", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "svätých žien: pre viaceré", "o svatých ženách (o více svatých)", "", "plurium mulierum", "", "O svatých ženách – o více svatých", "több szent asszony", "ru_text", "некалькіх святых жанчын", "fyrir heilagra kvenna:  fleiri en ein", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "svätých mužov: pre viacerých", "o svatých mužích (o více svatých)", "", "plurium virorum", "", "O svatých mužích – o více svatých", "több szent férfi", "ru_text", "некалькіх святых мужчын", "fyrir heilagra karla: fleiri en einn ", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "viacerých panien", "o pannách – o více pannách", "", "plurium virginum", "", "O pannách – o více pannách", "több szűz", "ru_text", "некалькіх паннаў", "fyrir margra meyja", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "posviacky chrámu", "o posvěcení kostela", "", "dedicationis ecclesiæ", "", "Posvěcení kostela", "templomszentelés", "ru_text", "пасвячэнне касцёла", "fyrir vígsluafmæli kirkjunnar", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "zosnulých", "za zemřelé", "", "defunctorum", "", "Za zemřelé", "halottakért", "ru_text", "за памерлых", "fyrir framliðinna", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "svätých žien: pre tie, čo žili v manželstve", "o svatých ženách (které žily v manželství)", "", "sanctarum mulierum: pro iis quæ in matrimonio vixit", "", "O svatých ženách – o ženě, která žila v manželství", "házas szent asszonyok", "ru_text", "святых жанчын: ", "fyrir heilagra kvenna: sem lifðu í hjónabandi", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "svätých mužov: pre tých, čo žili v manželstve", "o svatých mužích (kterí žili v manželství)", "", "sanctorum virorum: pro iis qui in matrimonio vixit", "", "O svatých mužích – o muži, který žil v manželství", "házas szent férfiak", "ru_text", "святых мужчын: ", "fyrir heilagra karla: sem lifðu í hjónabandi", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "nebrať", "nepoužít", "do not use", "non sumere", "", "nepoužít", "mindent sajátból", "ru_text", "by_text", "taka ekki", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

#define		nazov_spolc(a)	nazov_spolc_jazyk[a][_global_jazyk]

const char* nazov_bit_opt_1_spomienka_spol_cast_jazyk[POCET_JAZYKOV + 1] =
{
	"bola zvolená možnosť niektoré časti pri slávení spomienky vziať zo dňa podľa Všeobecných smerníc, č. 235 písm. b",
	"byla zvolena možnost vzít při slavení památky některé části ze dne podle Všeobecných pokynů k denní modlitbě církve, č. 235 písm. b",
	"",
	"delectum est in memoriis partes aliquas de feria sumere secundum Institutionem generalem de Liturgia horarum",
	"",
	"byla zvolena možnost vzít při slavení památky některé části ze dne podle Všeobecných pokynů k denní modlitbě církve, č. 235 písm. b",
	"az a lehetőség volt választva, hogy az emléknapoknál bizonyos részek vehetők a soros köznapról; Általános Rendelkezések az Imaórák Liturgiájáról, 235 b",
	"ru_text",
	"ён быў абраны, некаторыя часткі ў святкаванні успамінаў ўзяць з агульнымі кіруючымі прынцыпамі, няма. 235 пункт. б",
	"á minningardögum var valinn möguleiki að taka nokkra hluti af venjulegum degi eftir almennum reglum nr. 225, stafur B",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// filenames - language independent (based on Slovak)
const char* nazov_spolc_htm[POCET_SPOL_CASTI + 1] =
{
	"000",
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
const char* nazov_spolc_ANCHOR[POCET_SPOL_CASTI + 1] =
{
	"000",
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
const char* nazov_obdobia_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1] =
{
	{ "Adventné obdobie", "doba adventní", "", "tempus Adventus", "", "doba adventní", "adventi idő", "ru_text", "перыяд Адвэнту", "Aðventutíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Adventné obdobie", "doba adventní", "", "tempus Adventus", "", "doba adventní", "adventi idő", "ru_text", "перыяд Адвэнту", "Aðventutíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Oktáva Narodenia Pána", "oktáv Narození Páně", "", "octava Nativitatis", "", "oktáv Narození Páně", "karácsony nyolcada", "ru_text", "актава Божага Нараджэння", "Áttund Fæðingar Drottins", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Vianočné obdobie", "doba vánoční", "", "tempus Nativitatis", "", "doba vánoční", "karácsonyi idő", "ru_text", "перыяд Божага Нараджэння", "Jólatíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Vianočné obdobie", "doba vánoční", "", "tempus Nativitatis", "", "doba vánoční", "karácsonyi idő", "ru_text", "перыяд Божага Нараджэння", "Jólatíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Cezročné obdobie", "mezidobí", "", "tempus per annum", "", "mezidobí", "évközi idő", "ru_text", "звычайны перыяд", "Innan ársins", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Pôstne obdobie", "doba postní", "", "tempus Quadragesimæ", "", "doba postní", "nagyböjti idő", "ru_text", "перыяд Вялікага посту", "Föstutíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Svätý týždeň", "Svatý týden", "", "Hebdomada sancta", "", "Svatý týden", "nagyhét", "ru_text", "Вялікі тыдзень", "Dymbilvika", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Veľkonočné trojdnie", "Velikonoční triduum", "", "Sacrum Triduum paschale", "", "Velikonoční triduum", "szent három nap", "ru_text", "Святы Пасхальны Трыдуум", "Heilagir bænadagar", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Veľkonočná oktáva", "velikonoční oktáv", "", "octava Paschæ", "", "velikonoční oktáv", "húsvét nyolcada", "ru_text", "актава Пасхі", "Páskaáttund", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Veľkonočné obdobie", "doba velikonoční", "", "tempus paschale", "", "doba velikonoční", "húsvéti idő", "ru_text", "Велікодны перыяд", "Páskatíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Veľkonočné obdobie", "doba velikonoční", "", "tempus paschale", "", "doba velikonoční", "húsvéti idő", "ru_text", "Велікодны перыяд", "Páskatíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
};

#define		nazov_obdobia(a)	nazov_obdobia_jazyk[a][_global_jazyk]

// the names of liturgical periods (usually lowecase) / nazov_obdobia: string pre názov liturgického obdobia, rozšírený
const char* nazov_obdobia_ext_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1] =
{
	{ "Adventné obdobie I (do 16. decembra)", "doba adventní I", "", "tempus Adventus I", "", "doba adventní I", "adventi idő I (dec. 16-ig)", "ru_text", "перыяд Адвэнту I", "Aðventutíð I (til 16. desember)", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Adventné obdobie II (po 16. decembri)", "doba adventní II", "", "tempus Adventus II", "", "doba adventní II", "adventi idő II (dec. 16 után)", "ru_text", "перыяд Адвэнту II", "Aðventutíð II (eftir 16. desember)", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Oktáva Narodenia Pána", "oktáv Narození Páně", "", "octava Nativitatis", "", "oktáv Narození Páně", "karácsony nyolcada", "ru_text", "актава Божага Нараджэння", "Áttund Fæðingar Drottins", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Vianočné obdobie I (do Zjavenia Pána)", "doba vánoční I", "", "tempus Nativitatis I", "", "doba vánoční II", "karácsonyi idő I (Urunk megjelenéséig)", "ru_text", "перыяд Божага Нараджэння I", "Jólatíð I (til Birtingar Drottins)", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Vianočné obdobie II (po Zjavení Pána)", "doba vánoční II", "", "tempus Nativitatis II", "", "doba vánoční II", "karácsonyi idő II (Urunk megjelenése után)", "ru_text", "перыяд Божага Нараджэння II", "Jólatíð II (eftir Birtingu Drottins)", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Cezročné obdobie", "mezidobí", "", "tempus per annum", "", "mezidobí", "évközi idő", "ru_text", "звычайны перыяд", "Innan ársins", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Pôstne obdobie I (do Kvetnej nedele)", "doba postní I", "", "tempus Quadragesimæ I", "", "doba postní I", "nagyböjti idő I (Virágvasárnapig)", "ru_text", "перыяд Вялікага посту", "Föstutíð I (til Pálmasunnudags)", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Pôstne obdobie II (Svätý týždeň)", "Svatý týden", "", "Hebdomada sancta", "", "Svatý týden", "nagyböjti idő II (Nagyhét)", "ru_text", "Вялікі тыдзень", "Föstutíð II (Dymbilvika)", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Veľkonočné trojdnie", "Velikonoční triduum", "", "Sacrum Triduum paschale", "", "Velikonoční triduum", "szent három nap", "ru_text", "Святы Пасхальны Трыдуум", "Heilagir bænadagar", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Veľkonočná oktáva", "velikonoční oktáv", "", "octava Paschæ", "", "velikonoční oktáv", "húsvét nyolcada", "ru_text", "актава Пасхі", "Páskaáttund", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Veľkonočné obdobie I (do Nanebovstúpenia Pána)", "doba velikonoční I", "", "tempus paschale I", "", "doba velikonoční I", "húsvéti idő I (Urunk mennybemeneteléig)", "ru_text", "Велікодны перыяд I", "Páskatíð I (til Uppstigningar Drottins)", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Veľkonočné obdobie II (po Nanebovstúpení Pána)", "doba velikonoční II", "", "tempus paschale II", "", "doba velikonoční II", "húsvéti idő II (Urunk mennybemenetele után)", "ru_text", "Велікодны перыяд II", "Páskatíð II (eftir Uppstigningu Drottins)", /* STRING_1_FOR_NEW_LANGUAGE */ },
};

#define		nazov_obdobia_ext(a)	nazov_obdobia_ext_jazyk[a][_global_jazyk]

// the names of liturgical periods (usually lowecase) full-shortened / nazov_obdobia: string pre názov liturgického obdobia, stručný ale plný
const char* nazov_obdobia_short_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1] =
{
	{ "Adventné obd. I", "doba adventní I", "", "tempus Adventus I", "", "doba adventní I", "adventi idő I", "ru_text", "перыяд Адвэнту I", "Aðventutíð I (til 16. desember)", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Adventné obd. II", "doba adventní II", "", "tempus Adventus II", "", "doba adventní II", "adventi idő II", "ru_text", "перыяд Адвэнту II", "Aðventutíð II (eftir 16. desember)", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Oktáva Narodenia Pána", "oktáv Narození Páně", "", "octava Nativitatis", "", "oktáv Narození Páně", "karácsony nyolcada", "ru_text", "актава Божага Нараджэння", "Áttund Fæðingar Drottins", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Vianočné obd. I", "doba vánoční I", "", "tempus Nativitatis I", "", "doba vánoční II", "karácsonyi idő I", "ru_text", "перыяд Божага Нараджэння I", "Jólatíð I (til Birtingar Drottins)", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Vianočné obd. II", "doba vánoční II", "", "tempus Nativitatis II", "", "doba vánoční II", "karácsonyi idő II", "ru_text", "перыяд Божага Нараджэння II", "Jólatíð II (eftir Birtingu Drottins)", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Cezročné obd.", "mezidobí", "", "tempus per annum", "", "mezidobí", "évközi idő", "ru_text", "звычайны перыяд", "Innan ársins", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Pôstne obd. I", "doba postní I", "", "tempus Quadragesimæ I", "", "doba postní I", "nagyböjti idő I", "ru_text", "перыяд Вялікага посту", "Föstutíð I", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Svätý týždeň", "Svatý týden", "", "Hebdomada sancta", "", "Svatý týden", "Nagyhét", "ru_text", "Вялікі тыдзень", "Dymbilvikaext", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Veľkonočné trojdnie", "Velikonoční triduum", "", "Sacrum Triduum paschale", "", "Velikonoční triduum", "szent három nap", "ru_text", "Святы Пасхальны Трыдуум", "Heilagir bænadagar", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Veľkonočná oktáva", "velikonoční oktáv", "", "octava Paschæ", "", "velikonoční oktáv", "húsvét nyolcada", "ru_text", "актава Пасхі", "Páskaáttund", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Veľkonočné obd. I", "doba velikonoční I", "", "tempus paschale I", "", "doba velikonoční I", "húsvéti idő I", "ru_text", "Велікодны перыяд I", "Páskatíð I (til Uppstigningar Drottins)", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Veľkonočné obd. II", "doba velikonoční II", "", "tempus paschale II", "", "doba velikonoční II", "húsvéti idő II", "ru_text", "Велікодны перыяд II", "Páskatíð II (eftir Uppstigningu Drottins)", /* STRING_1_FOR_NEW_LANGUAGE */ },
};

#define		nazov_obdobia_short(a)	nazov_obdobia_short_jazyk[a][_global_jazyk]

// the names of liturgical periods for debugging, only in Slovak; no need to translate
const char* nazov_obdobia_[POCET_OBDOBI + 1] = // debuggovacie - preto netreba prekladať; 2006-08-03
{
	"adventné obdobie I", "adventné obdobie II", "oktáva Narodenia Pána",
	"vianočné obdobie I", "vianočné obdobie II", "cezročné obdobie",
	"pôstne obdobie I", "pôstne obdobie II (Svätý týždeň)",
	"veľkonočné trojdnie", "veľkonočná oktáva", "veľkonočné obdobie I", "veľkonočné obdobie II",
};

// the names of liturgical periods in local grammatically 6.th declination? (usually lowecase); in English: "IN liturgical period" or "OF liturgical period" / lokal == 6. pad, v kom/com
const char* nazov_obdobia_v_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1] =
{
	{ "v Adventnom období", "v době adventní", "", "tempore Adventus", "", "v době adventní", "adventben", "ru_text", "by_text", "Á aðventutíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "v Adventnom období", "v době adventní", "", "tempore Adventus", "", "v době adventní", "adventben", "ru_text", "by_text", "Á aðventutíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "v Oktáve Narodenia Pána", "v oktávu Narození Páně", "", "infra octavam Nativitatis", "", "v oktávu Narození Páně", "Karácsony nyolcadában", "ru_text", "by_text", "Á áttund Fæðingar Drottins", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "vo Vianočnom období", "v době vánoční", "", "tempore Nativitatis", "", "v době vánoční", "a karácsonyi időben", "ru_text", "by_text", "Á jólatíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "vo Vianočnom období", "v době vánoční", "", "tempore Nativitatis", "", "v době vánoční", "a karácsonyi időben", "ru_text", "by_text", "Á jólatíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "v Cezročnom období", "v mezidobí", "", "per annum", "", "v mezidobí", "az évközi időben", "ru_text", "by_text", "Innan ársins", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "v Pôstnom období", "v době postní", "", "tempore Quadragesimæ", "", "v době postní", "a nagyböjti időben", "ru_text", "by_text", "Á föstutíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Svätého týždňa", "ve Svatém týdnu", "", "in Hebdomada sancta", "", "ve Svatém týdnu", "a nagyhéten", "ru_text", "by_text", "Í Dymbilviku", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "vo Veľkonočnom Trojdní", "ve velikonočním triduu", "", "in Triduo Paschali", "", "ve velikonočním triduu", "a szent három napban", "ru_text", "by_text", "Á heilögum bænadögum", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "vo Veľkonočnej oktáve", "ve velikonočním oktávu", "", "infra octavam Paschæ", "", "ve velikonočním oktávu", "húsvét nyolcadában", "ru_text", "у актаве Пасхі", "á páskaáttund", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "vo Veľkonočnom období", "v době velikonoční", "", "tempore Paschæ", "", "v době velikonoční", "a húsvéti időben", "ru_text", "by_text", "Á páskatíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "vo Veľkonočnom období", "v době velikonoční", "", "tempore Paschæ", "", "v době velikonoční", "a húsvéti időben", "ru_text", "by_text", "Á páskatíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
};

#define		nazov_obdobia_v(a)	nazov_obdobia_v_jazyk[a][_global_jazyk]

// used for Sundays - "which" Sunday for some of them, e.g. "dominica V paschae" for 5-th Sunday in that liturgical period (uppercase)
// 2008-12-20: doplnené - používa sa v init_global_string() pre nedele niektorých období [zatiaľ iba v slovenčine]
const char* nazov_Obdobia_aka_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1] =
{
	{ "Adventná", "adventní", "", "Adventus", "", "adventní", "Advent", "ru_text", "by_text", "á aðventu", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Adventná", "adventní", "", "Adventus", "", "adventní", "Advent", "ru_text", "by_text", "á aðventu", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "V Oktáve Narodenia Pána", "v oktávu narození páně", "", "infra octavam Nativitatis", "", "v oktávu narození páně", "A karácsony nyolcadában", "ru_text", "by_text", "á áttund Fæðingar Drottins", /* STRING_1_FOR_NEW_LANGUAGE */ }, // not used / nepoužíva sa
	{ "Vianočná", "vánoční", "", "post Nativitatem", "", "vánoční", "Karácsony", "ru_text", "by_text", "á jólatíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Vianočná", "vánoční", "", "post Nativitatem", "", "vánoční", "Karácsony", "ru_text", "by_text", "á jólatíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Cezročná", "v mezidobí", "", "per annum", "", "během roku", "Évközi", "ru_text", "by_text", "innan ársins", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Pôstna", "postní", "", "Quadragesimæ", "", "postní", "Nagyböjt", "ru_text", "by_text", "á föstutíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Svätého týždňa", "ve Svatém týdnu", "", "in Hebdomada sancta", "", "ve Svatém týdnu", "hu_", "ru_text", "by_text", "í Dymbilviku", /* STRING_1_FOR_NEW_LANGUAGE */ }, // not used / nepoužíva sas
	{ "Vo Veľkonočnom Trojdní", "ve velikonočním triduu", "", "in Triduo Paschali", "", "ve velikonočním triduu", "hu_", "ru_text", "by_text", "á heilögum bænadögum", /* STRING_1_FOR_NEW_LANGUAGE */ }, // not used / nepoužíva sa
	{ "Vo Veľkonočnej oktáve", "ve velikonočním oktávu", "", "infra octavam Paschalis", "", "v oktávu velikonočním", "Húsvét nyolcacadában", "ru_text", "у актаве пасхі", "á páskaáttund", /* STRING_1_FOR_NEW_LANGUAGE */ }, // not used / nepoužíva sa
	{ "Veľkonočná", "velikonoční", "", "Paschæ", "", "velikonoční", "Húsvét", "ru_text", "велікодная", "á páskatíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Veľkonočná", "velikonoční", "", "Paschæ", "", "velikonoční", "Húsvét", "ru_text", "велікодная", "á páskatíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
};
#define		nazov_Obdobia_aka(a)	nazov_Obdobia_aka_jazyk[a][_global_jazyk]

// filenames - same for all languages (based on Slovak)
// nazov_obdobia: string pre nazov suboru .htm liturgickeho obdobia
const char* nazov_obd_htm[POCET_OBDOBI + 1] =
{
	"adv1.htm", "adv2.htm", "vian1.htm",
	"vian1.htm", "vian2.htm", "cezrok.htm",
	"post1.htm", "vtyz.htm",
	"vtroj.htm", "vnokt.htm", "vn1.htm", "vn2.htm"
};

// anchor names in files - same for all languages (based on Slovak)
// nazov_obdobia: string pre nazov kotvy v .htm liturgickeho obdobia
const char* nazov_OBD[POCET_OBDOBI + 1] =
{
	"ADV1", "ADV2", "OKTNAR",
	"VIAN1", "VIAN2", "OCR",
	"POST1", "VTYZ",
	"VTROJ", "VNOKT", "VN1", "VN2"
};

// filenames - same for all languages (based on Slovak)
// nazov_obdobia pc: string pre nazov suboru .htm liturgickeho obdobia pre posvatne citania
const char* nazov_obd_htm_pc[POCET_OBDOBI + 1] =
{
	"adv1_pc.htm", "adv2_pc.htm", "vian1_pc.htm",
	"vian1_pc.htm", "vian2_pc.htm", "cezrok_pc.htm",
	"post1_pc.htm", "vtyz_pc.htm",
	"vtroj_pc.htm", "vnokt_pc.htm", "vn1_pc.htm", "vn2_pc.htm"
};

// anchor names in files used for 4 volumes of breviary - same for all languages (based on Slovak)
// 2005-08-05: Pridané. zväzok breviára (LH) pre spoločné časti svätých v kotvách
const char* zvazok_OBD[POCET_OBDOBI + 1] =
{
	"ZVI", "ZVI", "ZVI",
	"ZVI", "ZVI", "OCR", // OCR je ZVIII aj ZVIV
	"ZVII", "ZVII",
	"ZVII", "ZVII", "ZVII", "ZVII"
};

// the name of celebration
const char* nazov_slavenia_jazyk[POCET_SLAVENI + 1][POCET_JAZYKOV + 1] =
{
	{ "féria", "férie", "feria", "feria", "férie", "féria", "féria", "ru_text", "будзень", "almennur tími", /* STRING_1_FOR_NEW_LANGUAGE */ }, // zmenené z "___", 2012-10-12
	{ "slávnosť", "slavnost", "celebration", "sollemnitas", "", "Slavnost", "főünnep", "ru_text", "урачыстасць", "stórhátíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "sviatok", "svátek", "", "festum", "", "Svátek", "ünnep", "ru_text", "свята", "hátíð", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "spomienka", "památka", "", "memoria", "", "Památka", "emléknap", "ru_text", "успамін", "M minning", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "ľubovoľná spomienka", "nezávazná památka", "", "memoria ad libitum", "", "nezávazná památka", "tetszés szerinti emléknap", "ru_text", "неабавязковы ўспамін", "* minning" /*"minningardagur að frjálsu vali"*/, /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "vlastné slávenie", "z vlastních textů", "", "textus proprius", "", "z vlastních textů", "saját szöveg", "ru_text", "by_text", "eigið hátíðarhald", /* STRING_1_FOR_NEW_LANGUAGE */ },
};

#define		nazov_slavenia(a)	nazov_slavenia_jazyk[a][_global_jazyk]

// the name of celebration -- for memoria (in privileged days)
const char* nazov_slavenia_na_spomienku_jazyk[POCET_JAZYKOV + 1] =
{ "na spomienku" /* Adam: lepšie by bolo: pripomienka */, "pro připomínku", "", "pro commemoratione", "", "pro připomínku", "megemlékezésül", "ru_text", "на ўспамін", "til minningar", /* STRING_1_FOR_NEW_LANGUAGE */ };

// calendar codes; internal usage for HTTP requests
const char* skratka_kalendara[POCET_KALENDAROV + 1] =
{ "", "la", "sk", "cz", "czop", "cssr", "hu", "svd", "sj", "sdb", "ofm", "op", "cm", "opraem", "ofmcap", "czcssr", "czsdb", "ru", "huofm", "ocd", "husvd", "by", "czofm", "csa", "osu", "husj", "is", "czsj", "czocd", "czofmconv", "skopraem", "husdb", "schp", /* ADD_VALUE_FOR_NEW_CALENDAR */};

// filenames for special calendars / názov súbora pre kalendáre -- "pro" == propriá
const char* nazov_htm_kalendar[POCET_KALENDAROV + 1] =
{ "", "", "", "", "", "pro_cssr.htm", "", "pro_svd.htm", "pro_sj.htm", "pro_sdb.htm", "pro_ofm.htm", "pro_op.htm", "pro_cm.htm", "pro_opraem.htm", "pro_ofmcap.htm", "pro_cssr.htm", "pro_sdb.htm", "", "pro_ofm.htm", "pro_ocd.htm", "pro_svd.htm", "", "pro_ofm.htm", "pro_csa.htm", "pro_osu.htm", "pro_sj.htm", "", "pro_sj.htm", "pro_ocd.htm", "pro_ofmconv.htm", "pro_opraem.htm", "pro_sdb.htm", "pro_schp.htm", /* ADD_VALUE_FOR_NEW_CALENDAR */};

const char* nazov_kalendara_short[POCET_KALENDAROV + 1] =
{
	"neurčený"
	, "všeobecný"
	, "všeobecný SK"
	, "obecný CZ"
	, "CZ OP"
	, "SK CSSR"
	, "általános HU"
	, "SK SVD"
	, "SK SJ"
	, "SK SDB"
	, "SK OFM"
	, "SK OP"
	, "SK CM"
	, "CZ OPRAEM"
	, "CZ OFMCAP"
	, "CZ CSSR"
	, "CZ SDB"
	, "všeobecný RU"
	, "HU OFM"
	, "SK OCD"
	, "HU SVD"
	, "агульны BY"
	, "CZ OFM"
	, "SK CSA"
	, "SK OSU"
	, "HU SJ"
	, "almennur IS"
	, "CZ SJ"
	, "CZ OCD"
	, "CZ OFMCONV"
	, "SK OPRAEM"
	, "HU SVD"
	, "SK SCHP"
	, /* ADD_VALUE_FOR_NEW_CALENDAR */
};

const char* nazov_kalendara_propria_only[POCET_KALENDAROV + 1] =
{
	"-"
	, ""
	, ""
	, ""
	, "OP"
	, "CSsR"
	, " HU"
	, "SVD"
	, "SJ"
	, "SDB"
	, "OFM"
	, "OP"
	, "CM"
	, "OPRaem"
	, "OFMcap."
	, "CSSR"
	, "SDB"
	, " RU"
	, "OFM"
	, "OCD"
	, "SVD"
	, " BY"
	, "OFM"
	, "CSA"
	, "OSU"
	, "SJ"
	, " IS"
	, "SJ"
	, "OCD"
	, "OFMconv"
	, "OPRaem"
	, "SDB"
	, "SchP"
	, /* ADD_VALUE_FOR_NEW_CALENDAR */
};

const char* nazov_kalendara_long[POCET_KALENDAROV + 1] =
{
	""
	, ""
	, "všeobecný [pre Slovensko]"
	, "obecný [pro Čechy a Moravu]"
	, "pro dominikány (OP)"
	, "pre Kongregáciu najsv. Vykupiteľa — redemptoristov (CSsR)" // bol veľmi dlhý combo-box, keď bolo: "pre Kongregáciu najsvätejšieho Vykupiteľa — redemptoristov (CSsR)"
	, "általános [Magyarország]"
	, "pre Spoločnosť Božieho Slova — verbistov (SVD)"
	, "pre Spoločnosť Ježišovu — jezuitov (SJ)"
	, "pre saleziánsku rodinu — SDB, FMA, VDB"
	// ,"pre františkánsku rodinu — františkánov<!-- (OFM)-->, kapucínov<!-- (OFMCap.)-->, minoritov<!-- (OFMConv.)-->" // 2011-03-21: nefungovalo porovnanie atokalendar lebo HTML odstránilo poznámky
	// ,"pre františkánsku rodinu — františkánov, kapucínov, minoritov" // 2011-03-22: sú tam aj mnohé ďalšie rehole a kongregácie, takže ma br. Jakub OFM poprosil, aby ostalo iba "pre františkánsku rodinu"
	, "pre františkánsku rodinu"
	, "pre Rehoľu kazateľov — dominikánov (OP)"
	, "pre Misijnú spoločnosť sv. Vincenta de Paul — lazaristov (CM)"
	, "s vlastními texty premonstrátského řádu (OPraem)" // "pro premonstráty (OPraem)"
	, "s vlastními kapucínskými texty (OFMCap.)"
	, "s vlastními texty Kongregace nejsv. Vykupitele — redemptoristů (CSsR)"
	, "s vlastními texty pro salesiánskou rodinu" // (SDB, FMA, VDB)
	, "general [Russia]"
	, "ferences szentek és ünnepek zsolozsmája"
	, "pre bosých karmelitánov (OCD)"
	, "verbiták zsolozsmája"
	, "агульны [Belarus]"
	, "s vlastními františkánskými texty (OFM)"
	, "pre kanonisky sv. Augustína Notre Dame (CSA)"
	, "pre uršulínky Rímskej únie (OSU)"
	, "jezsuiták zsolozsmája (SJ)"
	, "general [Iceland]"
	, "s vlastními texty jezuitského řádu (SJ)"
	, "s vlastními texty bosých karmelitánů (OCD)"
	, "s vlastními minoritskými texty (OFMConv.)"
	, "pre premonštrátov (OPraem)"
	, "szalézi zsolozsma"
	, "pre rehoľu Piaristov (SchP)"
	, /* ADD_VALUE_FOR_NEW_CALENDAR */
};

#define nazov_kalendara(kalendar) ((kalendar == KALENDAR_NEURCENY) || (kalendar == KALENDAR_VSEOBECNY) || (equals(nazov_kalendara_long[kalendar], STR_EMPTY))? nazov_kalendara_long[default_kalendar[_global_jazyk]] : nazov_kalendara_long[kalendar])

const char* nazov_kalendara_smart[POCET_KALENDAROV + 1] =
{
	""
	, ""
	, "všeobecný [pre Slovensko]"
	, "obecný [pro Čechy a Moravu]"
	, "dominikánský"
	, "pre redemptoristov (CSsR)" // bol veľmi dlhý combo-box, keď bolo: "pre Kongregáciu najsvätejšieho Vykupiteľa — redemptoristov (CSsR)"
	, "általános [Magyarország]"
	, "pre verbistov (SVD)"
	, "pre jezuitov (SJ)"
	, "pre saleziánsku rodinu"
	, "pre františkánsku rodinu"
	, "pre dominikánov (OP)"
	, "pre lazaristov (CM)"
	, "pro premonstráty (OPraem)"
	, "pro kapucíny (OFMCap.)"
	, "pro redemptoristy (CSsR)"
	, "pro salesiánskou rodinu"
	, "general [Russia]"
	, "ferences zsolozsmája"
	, "pre bosých karmelitánov (OCD)"
	, "verbiták zsolozsmája"
	, "агульны [Belarus]"
	, "pro františkány (OFM)"
	, "pre kanonisky Notre Dame (CSA)"
	, "pre uršulínky (OSU)"
	, "jezsuiták zsolozsmája (SJ)"
	, "general [Iceland]"
	, "pro jezuity (SJ)"
	, "pro bosé karmelitány (OCD)"
	, "pro minority (OFMConv)"
	, "pre premonštrátov (OPraem)"
	, "szalézi zsolozsma"
	, "pre piaristov (SchP)"
	, /* ADD_VALUE_FOR_NEW_CALENDAR */
};

// special "local" or "partial" characteristics of various celebrations - each in one language; no need to translate; special strings will be added
const char* nazov_slavenia_lokal[] =
{
  ""                                                                                                             // LOKAL_SLAV_NEURCENE
, "len v rožňavskej katedrále"                                                                                   // LOKAL_SLAV_ROZNAVA_KATEDRALA
, "hlavný patrón Trnavskej arcidiecézy"                                                                          // LOKAL_SLAV_TRNAVA_PATRON
, "v Bratislavskej, Trnavskej a Košickej arcidiecéze " HTML_LINE_BREAK "a v Banskobystrickej, Nitrianskej a Rožňavskej diecéze" // LOKAL_SLAV_TT_BB_KE_NR_RO | not used
, "v Nitrianskej diecéze sviatok hlavných patrónov"                                                              // LOKAL_SLAV_NITRA_PATRON
, "len v Košickej arcidiecéze"                                                                                   // LOKAL_SLAV_KOSICE
, "len v Nitrianskej diecéze"                                                                                    // LOKAL_SLAV_NITRA
, "len v Banskobystrickej diecéze"                                                                               // LOKAL_SLAV_BYSTRICA
, "len v Spišskej diecéze"                                                                                       // LOKAL_SLAV_SPIS
, "len v Rožňavskej diecéze"                                                                                     // LOKAL_SLAV_ROZNAVA
, "len v Trnavskej arcidiecéze"                                                                                  // LOKAL_SLAV_TRNAVA
, "len v Dóme sv. Martina v Bratislave"                                                                          // LOKAL_SLAV_DOM_SV_MARTINA
, "v Spišskej diecéze sviatok hlavného patróna"                                                                  // LOKAL_SLAV_SPIS_PATRON
, "v Banskobystrickej diecéze sviatok hlavného patróna"                                                          // LOKAL_SLAV_BYSTRICA_PATRON
, "v Trnavskej arcidiecéze a v Banskobystrickej, " HTML_LINE_BREAK "Nitrianskej a Rožňavskej diecéze"            // LOKAL_SLAV_TT_BB_NR_RO
, "v Košickej arcidiecéze sviatok hlavného patróna"                                                              // LOKAL_SLAV_KOSICE_PATRON
, "len v Žilinskej diecéze — sviatok hlavných patrónov; " HTML_LINE_BREAK "v Európe sviatok patrónov Európy"     // LOKAL_SLAV_14_FEB_CYRIL_METOD | odstránený popis "na Slovensku sa slávi 5. júla, slávnosť"
, "v Rožňavskej diecéze sviatok hlavného patróna"                                                                // LOKAL_SLAV_ROZNAVA_PATRON
, "len v konsekrovaných kostoloch"                                                                               // LOKAL_SLAV_KONSEKR_KOSTOLY
, "Druhá veľkonočná nedeľa — Božieho milosrdenstva"                                                              // LOKAL_SLAV_DRUHA_VELK_NEDELA
, "koniec Oktávy narodenia Pána"                                                                                 // LOKAL_SLAV_KONIEC_OKTAVY_NAR | string here: text_KONIEC_OKTAVY_NARODENIA_PANA[]
, "len v provinciách Talianska"                                                                                  // LOKAL_SLAV_OCD_IT
, "hlavního patrona pražské arcidiecéze"                                                                         // LOKAL_SLAV_PRAHA_PATRON
, "v pražské arcidiecézi"                                                                                        // LOKAL_SLAV_PRAHA
, "v brněnské diecézi"                                                                                           // LOKAL_SLAV_BRNO
, "na Moravě památka"                                                                                            // LOKAL_SLAV_MORAVA_SPOMIENKA
, "pre OFMCap.: sviatok; pre OFM: najbližší voľný deň"                                                           // LOKAL_SLAV_SVIATOK_OFMCAP_PRESUN_OFM
, "v pražské katedrále slavnost"                                                                                 // LOKAL_SLAV_PRAHA_KATEDRALA
, "v českobudějovické diecézi"                                                                                   // LOKAL_SLAV_CESKE_BUDEJOVICE
, "v olomoucké arcidiecézi"                                                                                      // LOKAL_SLAV_OLOMOUC
, "v Čechách závazná památka"                                                                                    // LOKAL_SLAV_CECHY_SPOMIENKA
, "v plzeňské diecézi svátek hlavního patrona"                                                                   // LOKAL_SLAV_PLZEN_PATRON
, "v ostravsko-opavské diecézi"                                                                                  // LOKAL_SLAV_OSTRAVA_OPAVA
, "v litoměřické diecézi"                                                                                        // LOKAL_SLAV_LITOMERICE
, "v královéhradecké diecézi"                                                                                    // LOKAL_SLAV_HRADEC_KRALOVE
, "len pre SDB"																					                 // LOKAL_SLAV_SDB_ONLY
, "v plzeňské diecézi"                                                                                           // LOKAL_SLAV_PLZEN 
, "v ostravsko-opavské diecézi: slavnost"                                                                        // LOKAL_SLAV_OSTRAVA_OPAVA_SLAVNOST
, "v českobudějovické diecézi: památka"                                                                          // LOKAL_SLAV_CESKE_BUDEJOVICE_PAMATKA
, "v Bratislavskej arcidiecéze a v Spišskej diecéze sviatok hlavného patróna"                                    // LOKAL_SLAV_SPIS_BA_PATRON
, "v Bratislavskej arcidiecéze"                                                                                  // LOKAL_SLAV_BRATISLAVA
, "pre FMA a VDB: ľubovoľná spomienka"                                                                           // LOKAL_SLAV_LUB_SPOMIENKA_FMA_VDB
, "len pre Inštitút milosrdných sestier Sv. kríža"                                                               // LOKAL_SLAV_KONGREGACIA_SSK // 2013-08-12: pôvodne bolo: "len pre Kongregáciu milosrdných sestier Sv. kríža"
, "pre OFMCap.: spomienka"                                                                                       // LOKAL_SLAV_SPOMIENKA_OFMCAP
, "pre OFM: sviatok"                                                                                             // LOKAL_SLAV_SVIATOK_OFM
, "pre OFM: spomienka"                                                                                           // LOKAL_SLAV_SPOMIENKA_OFM
, "pre OFMCap.: sviatok"                                                                                         // LOKAL_SLAV_SVIATOK_OFMCAP
, "pre FMA: spomienka"                                                                                           // LOKAL_SLAV_SPOMIENKA_FMA
, "pre FMA: slávnosť"                                                                                            // LOKAL_SLAV_SLAVNOST_FMA
, "pre SDB: slávnosť"                                                                                            // LOKAL_SLAV_SLAVNOST_SDB
, "pre VDB: sviatok"                                                                                             // LOKAL_SLAV_SVIATOK_VDB
, "pre SCSC: sviatok"                                                                                            // LOKAL_SLAV_SVIATOK_SCSC
, "pre OFM: spomienka; pre koncepcionistky: slávnosť"                                                            // LOKAL_SLAV_SPOMIENKA_OFM_SLAVNOST_CONCEPT
, "A Szombathelyi egyházmegyében"                                                                                // LOKAL_SLAV_SZOMBATHELYI_EGYH
, "A Nagyszombati főegyházmegyében: a főegyházmegye fővédőszentje"                                               // LOKAL_SLAV_NAGYSZ_PATRON
, "A Szeged-Csanádi egyházmegye északi részében: az egyházmegye védőszentje; főünnep"                            // LOKAL_SLAV_SZEGED_CSAN_PATRON // 2013-06-27: ??? neviem, odkiaľ sa to tu vzalo
, "A Pécsi egyházmegyében"                                                                                       // LOKAL_SLAV_PECSI_EGYH
, "A Pécsi egyházmegyében: az egyházmegye védőszentje; főünnep"                                                  // LOKAL_SLAV_PECSI_EGYH_PATRON
, "A Szeged-Csanádi egyházmegye északi részében; ünnep"                                                          // LOKAL_SLAV_SZEGED_CSAN_EGYH
, "A Veszprémi főegyházmegyében: Szent Anna, a főegyházmegye védőszentje; főünnep"                               // LOKAL_SLAV_VESZPREMI_EGYH_PATRON
, "A Győri és Székesfehérvári egyházmegyében: az egyházmegye védőszentje"                                        // LOKAL_SLAV_GYORI_SZEKESFEH_EGYH
, "A Kaposvári egyházmegyében; ünnep"                                                                            // LOKAL_SLAV_KAPORSVAR_FELSZ
, "A Váci egyházmegyében; ünnep"                                                                                 // LOKAL_SLAV_VACI_FELSZ
, "A Kalocsa-Kecskeméti főegyházmegyében: a főegyházmegye védőszentje; főünnep"                                  // LOKAL_SLAV_KAL_KECS_FOEGYH
, "A Esztergom-Budapesti főegyházmegyében: a főszékesegyházban; főünnep"                                         // LOKAL_SLAV_ESZTERGOM_BUDA_FOEGYH
, "A főszékesegyházban; főünnep"                                                                                 // LOKAL_SLAV_KAL_KECS_FELSZ
, "A Győri egyházmegyében: a székesegyház felszentelése; ünnep"                                                  // LOKAL_SLAV_GYORI_SZEKESEGYH_FELSZ
, "A Váci egyházmegyében: Szent Mihály főangyal, az egyházmegye védőszentje; főünnep"                            // LOKAL_SLAV_VACI_PATRON
, "A Szeged-Csanádi egyházmegyében: az egyházmegye védőszentje; főünnep"                                         // LOKAL_SLAV_SZEGED_CSAN_PATRON2
, "A Veszprémi főegyházmegyében: a főszékesegyházban; főünnep"													 // LOKAL_SLAV_VESZPREM_FOEGYH
, "pre Rehoľu najsvätejšieho Vykupiteľa – redemptoristky: sviatok"                                               // LOKAL_SLAV_CSSR_SVIATOK
, "A Szeged-Csanádi egyházmegyében: a székesegyházban; főünnep"                                                  // LOKAL_SLAV_SZEGED_CSAN_EGYH2
, "A Pécsi egyházmegyében: a Pécsi egyházmegye társvédőszentje; főünnep"                                         // LOKAL_SLAV_PECS_PATRON
, "A Szombathelyi egyházmegyébe: az egyházmegye védőszentje; főünnep"                                            // LOKAL_SLAV_SZOMBATHELYI_PATRON
, "Székesfehérvár: a székesegyházban; főünnep"                                                                   // LOKAL_SLAV_SZEKESFEHERVAR_EGYH
, "Az Egri főegyházmegyében: a főegyházmegye védőszentje; főünnep"                                               // LOKAL_SLAV_EGER_FOEGYH
, "Az Esztergomi főegyházmegyében; emléknap"                                                                     // LOKAL_SLAV_ESZTERGOM_EML
, "A Győri egyházmegyében"                                                                                       // LOKAL_SLAV_GYOR_EGYH
, "Az Esztergomi főegyházmegyében"                                                                               // LOKAL_SLAV_ESZTERGOM_FOEGYH
, "Az Egri főegyházmegyében"                                                                                     // LOKAL_SLAV_EGER_FOEGYH2
, "A Veszprémi főegyházmegyében: a főegyházmegye társvédőszentje; főünnep"                                       // LOKAL_SLAV_VESZPREM_FOEGYH_T
, "A Szatmári egyházmegyében; emléknap"                                                                          // LOKAL_SLAV_SZATMAR
, "v ostatních českých diecézích a v brněnské diecézi: památka; " HTML_LINE_BREAK "na Moravě mimo brněnskou diecézi: nezávazná památka" // LOKAL_SLAV_CESKO_BRNO
, "sviatok hlavnej patrónky " HTML_LINE_BREAK "(slovenskej) Kongregácie sestier dominikánok bl. Imeldy"          // LOKAL_SLAV_SVIATOK_OP_ZENY
, "len v Žilinskej diecéze"                                                                                      // LOKAL_SLAV_ZILINA
, "na Strahově: svátek, Nová Říše: památka"                                                                      // LOKAL_SLAV_OPRAEM_SVIATOK_STRAHOV
, "kanonie Teplá: slavnost"                                                                                      // LOKAL_SLAV_OPRAEM_SLAVNOST_TEPLA
, "jen kanonie Nová Říše"                                                                                        // LOKAL_SLAV_OPRAEM_NOVA_RISE
, "jen kanonie Strahov a Nová Říše"                                                                              // LOKAL_SLAV_OPRAEM_STRAHOV_NOVA_RISE
, "jen kanonie Želiv"                                                                                            // LOKAL_SLAV_OPRAEM_ZELIV
, "jen kanonie Strahov"                                                                                          // LOKAL_SLAV_OPRAEM_STRAHOV
, "Debrecen-Nyíregyháza és Kaposvár: " HTML_LINE_BREAK "Az egyházmegye védőszentje; főünnep"                     // LOKAL_SLAV_SZ_LASZLO
, "pre OSC: slávnosť"                                                                                            // LOKAL_SLAV_SLAVNOST_OSC
, "pre OFMConv.: sviatok"                                                                                        // LOKAL_SLAV_SVIATOK_OFMCONV
, "pre OFS: sviatok"                                                                                             // LOKAL_SLAV_SVIATOK_OFS
, "pre OFMConv., OFMCap.: spomienka"                                                                             // LOKAL_SLAV_SPOMIENKA_OFMCONV_OFMCAP
, "pre OSC: slávnosť"                                                                                            // LOKAL_SLAV_SPOMIENKA_OSC
, "pre Slovensko zatiaľ nedovolené slávenie"                                                                     // LOKAL_SLAV_NEDOVOLENE_SK
, "Katonai Ordinariátus: " HTML_LINE_BREAK "Az Ordinariátus védőszentje; főünnep"                                // LOKAL_SLAV_KATONAI_ORDINARIAT
, "Debrecen-Nyíregyháza: " HTML_LINE_BREAK "A székesegyház felszentelése; főünnep"                               // LOKAL_SLAV_DEBR_NYIREGY
, "jen kanonie Doksany"                                                                                          // LOKAL_SLAV_OPRAEM_DOKSANY
, "jen kanonie Doksany a Želiv"                                                                                  // LOKAL_SLAV_OPRAEM_DOKSANY_ZELIV
, "jen kanonie Teplá"                                                                                            // LOKAL_SLAV_OPRAEM_TEPLA
, "len pre len pre Kongregáciu sestier Matky Božieho Milosrdenstva"                                              // LOKAL_SLAV_KONGREGACIA_SMBM
, "pro FMA památka"                                                                                              // LOKAL_SLAV_SPOMIENKA_FMA_CZ
, "pro FMA a VDB nezávazná památka"                                                                              // LOKAL_SLAV_LUB_SPOMIENKA_FMA_VDB_CZ
, "pro VDB svátek"                                                                                               // LOKAL_SLAV_SVIATOK_VDB_CZ
, "pro FMA slavnost"                                                                                             // LOKAL_SLAV_SLAVNOST_FMA_CZ
, "A Szeged-Csanádi egyházmegyében"                                                                              // LOKAL_SLAV_SZEGED_CSAN_EGYH3
, "len pre Ordinariát ozbrojených síl a ozbrojených zborov SR"                                                   // LOKAL_SLAV_ORDINARIAT
, "A Klarisszáknál: Emléknap"                                                                                    // LOKAL_SLAV_HU_KLARISSZAKNAL_EM
, "A Klarisszáknál: Főünnep"                                                                                     // LOKAL_SLAV_HU_KLARISSZAKNAL_FOU
, "jen na Moravě"                                                                                                // LOKAL_SLAV_LEN_MORAVA
, "jen v Čechách"                                                                                                // LOKAL_SLAV_LEN_CECHY
, "A Conceptionistáknál: Ünnep"                                                                                  // LOKAL_SLAV_HU_CONCEPTIONISTAK_UN
, "v kláštoroch bosých karmelitánok – spomienka"                                                                 // LOKAL_SLAV_OCD_BOSE_KARMEL_SPOM
, "pro SDB: slavnost"                                                                                            // LOKAL_SLAV_SLAVNOST_SDB_CZ
, "v dome sv. Lazára v Paríži: spomienka"                                                                        // LOKAL_SLAV_SPOMIENKA_CM_PARIZ
, "у Віцебскай дыяцэзіі: успамін"                                                                                // LOKAL_SLAV_VICEB_SPOMIENKA
, "у Мінска-Магілёўскай архідыяцэзіі"                                                                            // LOKAL_SLAV_POSV_K_CH_MINSK
, "у Пінскай дыяцэзіі"                                                                                           // LOKAL_SLAV_POSV_K_CH_PINSK
, "у Пінскай дыяцэзіі: урачыстасць; " HTML_LINE_BREAK "у Мінска-Магілёўскай архідыяцэзіі і Віцебскай дыяцэзіі: успамін" // LOKAL_SLAV_PINSK_MINSK
, "v královéhradecké diecézi: slavnost"                                                                          // LOKAL_SLAV_HRADEC_KRALOVE_SLAVNOST
, "v českobudějovické diecézi: slavnost"                                                                         // LOKAL_SLAV_CESKE_BUDEJOV_SLAVNOST
, "у Гродзенскай дыяцэзіі"                                                                                       // LOKAL_SLAV_GRODZENSK
, "у Мінска-Магілёўскай архідыяцэзіі: урачыстасць; " HTML_LINE_BREAK "у Віцебскай дыяцэзіі: свята"               // LOKAL_SLAV_MINSK_MAG_VICEB
, "у Мінска-Магілёўскай архідыяцэзіі: успамін"                                                                   // LOKAL_SLAV_MINSK_SPOMIENKA
, "у Гродзенскай дыяцэзіі: свята"                                                                                // LOKAL_SLAV_GRODZENSK_SVIATOK
, "У Мінска-Магілёўскай архідыяцэзіі, Пінскай дыяцэзіі і Гродзенскай дыяцэзіі"                                   // LOKAL_SLAV_MINSK_PINSK_GRODZENSK
, "у Віцебскай дыяцэзіі"                                                                                         // LOKAL_SLAV_VICEB
, "у Мінска-Магілёўскай архідыяцэзіі і Пінскай дыяцэзіі: успамін"                                                // LOKAL_SLAV_MINSK_PINSK_SPOMIENKA
, "у Віцебскай дыяцэзіі: урачыстасць, " HTML_LINE_BREAK "у Мінска-Магілёўскай архідыяцэзіі і Пінскай дыяцэзіі: свята" // LOKAL_SLAV_VICEB_SL_MINSK_PINSK_SV
, "у Гродзенскай дыяцэзіі: урачыстасць; " HTML_LINE_BREAK "у Мінска-Магілёўскай архідыяцэзіі і Пінскай дыяцэзіі: успамін" // LOKAL_SLAV_GRODZ_SL_PINSK_MINSK_SP
, "v pražském klášteře u Panny Marie Sněžné: slavnost"                                                           // LOKAL_SLAV_PRAHA_OFM
, "pro mnišky: památka"                                                                                          // LOKAL_SLAV_OP_MNISKY_PAMATKA
, "pre OFS: spomienka"                                                                                           // LOKAL_SLAV_SPOMIENKA_OFS
, "az FMA számára: Főünnep"                                                                                      // LOKAL_SLAV_SLAVNOST_FMA_HU
, "az FMA számára: Emléknap"                                                                                     // LOKAL_SLAV_SPOMIENKA_FMA_HU
, "az FMA és VDB számára: tetszés szerinti emléknap"                                                             // LOKAL_SLAV_LUB_SPOMIENKA_FMA_VDB_HU
, "a VDB számára: Ünnep"                                                                                         // LOKAL_SLAV_SVIATOK_VDB_HU
};

// names of liturgical colors
const char* nazov_farby_jazyk[POCET_FARIEB_REALNYCH + 1][POCET_JAZYKOV + 1] =
{
	{ "___", "___", "___", "___", "___", "___", "___", "___", "___", "___", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "červená", "červená", "red", "ruber", "", "červená", "piros", "ru_text", "чырвоны", "rauður", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "biela", "bílá", "white", "albus", "", "bílá", "fehér", "ru_text", "белы", "hvítur", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "zelená", "zelená", "green", "viridis", "", "zelená", "zöld", "ru_text", "зялёны", "grænn", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "fialová", "fialová", "purple", "violaceus", "", "fialová", "lila", "ru_text", "фіялетавы", "fjólublár", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "ružová", "růžová", "rose", "rosaceus", "", "růžová", "rózsaszín", "ru_text", "ружовы", "bleikur", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "čierna", "černá", "black", "niger", "", "černá", "fekete", "ru_text", "чорны", "svartur", /* STRING_1_FOR_NEW_LANGUAGE */ },
};

#define		nazov_farby(a)	nazov_farby_jazyk[a][_global_jazyk]

// color codes as standard HTML elements (possibility to use them as inline CSS style)

// codes for colors - HTML specific
const char* html_farba_pozadie[POCET_FARIEB_REALNYCH + 1] =
{ "#000000" /* "black" */, "#ff0000" /* "red" */, "#ffffff" /* "white" */, "#008000" /* "green" */, "#800080" /* "purple" */, "#FF6699" /* "fuchsia" */, "#000000" /* black */ };

// codes for colors - HTML specific
const char* html_farba_popredie[POCET_FARIEB_REALNYCH + 1] =
{ "#ffffff" /* "white" */, "#ffffff" /* "white" */, "#000000" /* "black" */, "#ffffff" /* "white" */, "#ffffff" /* "white" */, "#0000ff" /* "blue" */, "#ffffff" /* "white" */ };

// codes for colors - HTML specific
const char* html_farba_okraj[POCET_FARIEB_REALNYCH + 1] =
{ "#000000" /* "black" */, "#000000" /* "black" */, "#000000" /* "black" */, "#000000" /* "black" */, "#000000" /* "black" */, "#000000" /* "black" */, "#000000" /* black */ };

// codes for number of the week from psaltery (psalterium per quattuor hebdomadas distributum)
const char* rimskymi_tyzden_zaltara[ZVAZKY_LH + 2] =
{ "_", "I", "II", "III", "IV", "V" }; // 5 == vlastné slávenie

// const: ordinal number of the first day in specific month
const short int prvy_den[12] =
{ 1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };

// const: number (count) of days in specific month
short int pocet_dni[12] =
{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// type of alhpabet for language
const short int alphabet_jayzka[POCET_JAZYKOV + 1] =
{ ALPHABET_LATIN, ALPHABET_LATIN, ALPHABET_LATIN, ALPHABET_LATIN, ALPHABET_LATIN, ALPHABET_LATIN, ALPHABET_LATIN, ALPHABET_CYRILLIC, ALPHABET_CYRILLIC, ALPHABET_LATIN, /* ADD_VALUE_FOR_NEW_LANGUAGE */ };

// const: "the Sunday's letter" A--g
const char char_nedelne_pismeno[POCET_DNI] =
{ 'b', 'c', 'd', 'e', 'f', 'g', 'A' };

const char* string_nedelne_pismeno[POCET_ALPHABET + 1][POCET_DNI] =
{
	{ "b", "c", "d", "e", "f", "g", "A" },
	{ "б", "в", "г", "д", "е", "ж", "А" },
};

// const: the Sunday's cycle A--C
const char char_nedelny_cyklus[POCET_NEDELNY_CYKLUS] =
{ 'A', 'B', 'C' };

const char* string_nedelny_cyklus[POCET_ALPHABET + 1][POCET_NEDELNY_CYKLUS] =
{
	{ "A", "B", "C" },
	{ "А", "Б", "В" },
};

// names of the days in week, starting with Sunday (lowercase) / nazov_dna: string pre nazov dna; suhlasi s struct tm.tm_wday; 
// Weekday (0--6; Sunday/nedela = 0)
const char* nazov_dna_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1] =
{
	{ "nedeľa", "neděle", "Sunday", "dominica", "", "neděle", "vasárnap", "воскресенье", "нядзеля", "sunnudagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "pondelok", "pondělí", "Monday", "feria secunda", "", "pondělí", "hétfő", "понедельник", "панядзелак", "mánudagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "utorok", "úterý", "Tuesday", "feria tertia", "", "úterý", "kedd", "вторник", "аўторак", "þriðjudagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "streda", "středa", "Wednesday", "feria quarta", "", "středa", "szerda", "среда", "серада", "miðvikudagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "štvrtok", "čtvrtek", "Thursday", "feria quinta", "", "čtvrtek", "csütörtök", "четверг", "чацвер", "fimmtudagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "piatok", "pátek", "Friday", "feria sexta", "", "pátek", "péntek", "пятница", "пятніца", "föstudagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "sobota", "sobota", "Saturday", "sabbatum", "", "sobota", "szombat", "суббота", "субота", "laugardagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "neznámy", "neznámý", "unknown", "ignotus", "", "neznámý", "ismeretlen", "неизвестный", "невядомы", "óþekktur", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

#define		nazov_dna(a)	nazov_dna_jazyk[a][_global_jazyk]

// names of the days in week, starting with Sunday (sentence case)
const char* nazov_Dna_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1] =
{
	{ "Nedeľa", "Neděle", "Sunday", "Dominica", "", "Neděle", "Vasárnap", "Воскресенье", "Нядзеля", "Sunnudagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Pondelok", "Pondělí", "Monday", "Feria secunda", "", "Pondělí", "Hétfő", "Понедельник", "Панядзелак", "Mánudagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Utorok", "Úterý", "Tuesday", "Feria tertia", "", "Úterý", "Kedd", "Вторник", "Аўторак", "Þriðjudagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Streda", "Středa", "Wednesday", "Feria quarta", "", "Středa", "Szerda", "Среда", "Серада", "Miðvikudagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Štvrtok", "Čtvrtek", "Thursday", "Feria quinta", "", "Čtvrtek", "Csütörtök", "Четверг", "Чацвер", "Fimmtudagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Piatok", "Pátek", "Friday", "Feria sexta", "", "Pátek", "Péntek", "Пятница", "Пятніца", "Föstudagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Sobota", "Sobota", "Saturday", "Sabbatum", "", "Sobota", "Szombat", "Суббота", "Субота", "Laugardagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Neznámy", "Neznámý", "unknown", "ignotus", "", "Neznámý", "Ismeretlen", "Неизвестный", "Невядомы", "Óþekktur", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

#define		nazov_Dna(a)	nazov_Dna_jazyk[a][_global_jazyk]

// names of the days in week, starting with Sunday (lowercase without special characters - plain ASCII (0--128) only)
const char* nazov_dna_asci_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1] =
{
	{ "nedela", "nedele", "Sunday", "Dominica", "", "nedele", "vasarnap", "Sunday", "нядзеля", "sunnudagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "pondelok", "pondeli", "Monday", "Feria secunda", "", "pondeli", "hetfo", "Monday", "панядзелак", "manudagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "utorok", "utery", "Tuesday", "Feria tertia", "", "utery", "kedd", "Tuesday", "аўторак", "þriðjudagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "streda", "streda", "Wednesday", "Feria quarta", "", "streda", "szerda", "Wednesday", "серада", "miðvikudagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "stvrtok", "ctvrtek", "Thursday", "Feria quinta", "", "ctvrtek", "csutortok", "Thursday", "чацвер", "fimmtudagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "piatok", "patek", "Friday", "Feria sexta", "", "patek", "pentek", "Friday", "пятніца", "föstudagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "sobota", "sobota", "Saturday", "Sabbatum", "", "sobota", "szombat", "Saturday", "субота", "laugardagur", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "neznamy", "neznamy", "unknown", "ignotus", "", "neznamy", "ismeretlen", "unknown", "невядомы", "óþekktur", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

#define		nazov_dna_asci(a)	nazov_dna_asci_jazyk[a][_global_jazyk]

#define KONCOVKA_DNA_HU "JA" // vasárnapJA
#define KONCOVKA_DNA_HU_SMALL "ja" // vasárnapja

// two/three-letter abbreviations of the names of the days in week, starting with Sunday (sentence case)
const char* nazov_Dn_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1] =
{
	{ "Ne", "Ne", "Sun", "Do", "", "Ne", "V", "Вс", "Нд", "Sun", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Po", "Po", "Mon", "F2", "", "Po", "H", "Пн", "Пн", "Mán", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Ut", "Út", "Tue", "F3", "", "Út", "K", "Вт", "Ат", "Þri", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "St", "St", "Wed", "F4", "", "St", "Sze", "Ср", "Ср", "Mið", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Št", "Čt", "Thu", "F5", "", "Čt", "Cs", "Чт", "Чц", "Fim", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Pi", "Pá", "Fri", "F6", "", "Pá", "P", "Пт", "Пт", "Fös", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "So", "So", "Sat", "Sa", "", "So", "Szo", "Сб", "Сб", "Lau", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "??", "??", "???", "", "", "??", "??", "??", "??", "??", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

#define		nazov_Dn(a)	nazov_Dn_jazyk[a][_global_jazyk]

// two/three-letter abbreviations of the names of the days in week, starting with Sunday used for anchors (uppercase, no need to translate; based on Slovak)
// 2006-08-01: používa sa pre HTML kotvy, ktoré nezávisia od jazykovej mutácie
const char* nazov_DN_asci[POCET_DNI + 1] =
{ "NE", "PO", "UT", "STR", "STV", "PI", "SO", "??" };

// two/three-letter abbreviations of the names of the days in week, starting with Sunday used for debug info (lowercase, no need to translate; based on Slovak)
const char* nazov_dn_asci[POCET_DNI + 1] =
{ "ne", "po", "ut", "str", "stv", "pi", "so", "??" };

// the names of the months (lowecase) / nazov_mesiaca: string pre nazov dna; suhlasi s struct tm.tm_mon;
// Month (0--11)
const char* nazov_mesiaca_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1] =
{
	{ "január", "leden", "January", "ianuarius", "", "leden", "január", "январь", "студзень", "janúar", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "február", "únor", "February", "februarius", "", "únor", "február", "февраль", "люты", "febrúar", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "marec", "březen", "March", "martius", "", "březen", "március", "март", "сакавік", "mars", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "apríl", "duben", "April", "aprilis", "", "duben", "április", "апреля", "красавік", "apríl", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "máj", "květen", "May", "maius", "", "květen", "május", "мая", "май", "maí", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "jún", "červen", "June", "iunius", "", "červen", "június", "июнь", "чэрвень", "júní", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "júl", "červenec", "July", "iulius", "", "červenec", "július", "июль", "ліпень", "júlí", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "august", "srpen", "August", "augustus", "", "srpen", "augusztus", "август", "жнівень", "ágúst", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "september", "září", "September", "september", "", "září", "szeptember", "сентябрь", "верасень", "september", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "október", "říjen", "October", "october", "", "říjen", "október", "октября", "кастрычнік", "október", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "november", "listopad", "November", "november", "", "listopad", "november", "ноябрь", "лістапад", "nóvember", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "december", "prosinec", "December", "december", "", "prosinec", "december", "декабрь", "снежань", "desember", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "neznámy", "neznámý", "unknown", "ignotus", "", "neznámý", "ismeretlen", "неизвестный", "невядомы", "óþekktur", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

#define		nazov_mesiaca(a)	nazov_mesiaca_jazyk[a][_global_jazyk]

// the names of the months (sentence case)
const char* nazov_Mesiaca_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1] =
{
	{ "Január", "Leden", "January", "Ianuarius", "", "Leden", "Január", "Январь", "Студзень", "Janúar", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Február", "Únor", "February", "Februarius", "", "Únor", "Február", "Февраль", "Люты", "Febrúar", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Marec", "Březen", "March", "Martius", "", "Březen", "Március", "Март", "Сакавік", "Mars", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Apríl", "Duben", "April", "Aprilis", "", "Duben", "Április", "Апреля", "Красавік", "Apríl", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Máj", "Květen", "May", "Maius", "", "Květen", "Május", "Мая", "Май", "Maí", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Jún", "Červen", "June", "Iunius", "", "Červen", "Június", "Июнь", "Чэрвень", "Júní", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Júl", "Červenec", "July", "Iulius", "", "Červenec", "Július", "Июль", "Ліпень", "Júlí", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "August", "Srpen", "August", "Augustus", "", "Srpen", "Augusztus", "Август", "Жнівень", "Ágúst", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "September", "Září", "September", "September", "", "Září", "Szeptember", "Сентябрь", "Верасень", "September", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Október", "Říjen", "October", "October", "", "Říjen", "Október", "Октября", "Кастрычнік", "Október", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "November", "Listopad", "November", "November", "", "Listopad", "November", "Ноябрь", "Лістапад", "Nóvember", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "December", "Prosinec", "December", "December", "", "Prosinec", "December", "Декабрь", "Снежань", "Desember", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Neznámy", "Neznámý", "unknown", "ignotus", "", "Neznámý", "Ismeretlen", "Неизвестный", "Невядомы", "Óþekktur", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

#define		nazov_Mesiaca(a)	nazov_Mesiaca_jazyk[a][_global_jazyk]

// the names of the months (lowecase without special characters, plain ASCII 0--128)
const char* nazov_mesiaca_asci_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1] =
{
	{ "januar", "leden", "January", "Ianuarius", "", "leden", "januar", "January", "студзень", "januar", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "februar", "unor", "February", "Februarius", "", "unor", "februar", "February", "люты", "februar", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "marec", "brezen", "March", "Martius", "", "brezen", "marcius", "March", "сакавік", "mars", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "april", "duben", "April", "Aprilis", "", "duben", "aprilis", "April", "красавік", "april", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "maj", "kveten", "May", "Maius", "", "kveten", "majus", "May", "май", "mai", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "jun", "cerven", "June", "Iunius", "", "cerven", "junius", "June", "чэрвень", "juni", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "jul", "cervenec", "July", "Iulius", "", "cervenec", "julius", "July", "ліпень", "juli", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "august", "srpen", "August", "Augustus", "", "srpen", "augusztus", "August", "жнівень", "agust", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "september", "zari", "September", "September", "", "zari", "szeptember", "September", "верасень", "september", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "oktober", "rijen", "October", "October", "", "rijen", "oktober", "October", "кастрычнік", "oktober", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "november", "listopad", "November", "November", "", "listopad", "november", "November", "лістапад", "november", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "december", "prosinec", "December", "December", "", "prosinec", "december", "December", "снежань", "desember", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "neznamy", "neznamy", "unknown", "ignotus", "", "neznamy", "ismeretlen", "unknown", "невядомы", "óþekktur", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

#define		nazov_mesiaca_asci(a)	nazov_mesiaca_asci_jazyk[a][_global_jazyk]

// the names of the months (lowercase) in genitive grammatically 2.th declination?; in English: "IN that month" or "OF that month" / genitív == 2. pád, koho/čoho
// usage: when generated string for date, e.g. en: "1st January 2000", sk: "1. januára 2000"
// genitív názvu mesiaca
const char* nazov_mesiaca_gen_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1] =
{
	{ "januára", "ledna", "January", "ianuarii", "", "ledna", "január", "ru_text", "студзеня", "janúar", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "februára", "února", "February", "februarii", "", "února", "február", "ru_text", "лютага", "febrúar", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "marca", "března", "March", "martii", "", "března", "március", "ru_text", "сакавіка", "mars", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "apríla", "dubna", "April", "aprilis", "", "dubna", "április", "ru_text", "красавіка", "apríl", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "mája", "května", "May", "maii", "", "května", "május", "ru_text", "мая", "maí", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "júna", "června", "June", "iunii", "", "června", "június", "ru_text", "чэрвеня", "júní", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "júla", "července", "July", "iulii", "", "července", "július", "ru_text", "ліпеня", "júlí", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "augusta", "srpna", "August", "augusti", "", "srpna", "augusztus", "ru_text", "жніўня", "ágúst", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "septembra", "září", "September", "septembris", "", "září", "szeptember", "ru_text", "верасня", "september", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "októbra", "října", "October", "octobris", "", "října", "október", "ru_text", "кастрычніка", "október", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "novembra", "listopadu", "November", "novembris", "", "listopadu", "november", "ru_text", "лістапада", "nóvember", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "decembra", "prosince", "December", "decembris", "", "prosince", "december", "ru_text", "снежня", "desember", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "neznámeho", "neznámého", "unknown", "ignotus", "", "neznámého", "ismeretlen", "ru_text", "by_text", "óþekktur", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

#define		nazov_mesiaca_gen(a)	nazov_mesiaca_gen_jazyk[a][_global_jazyk]

// 2007-03-20: pridaný genitív názvu mesiaca kvôli latinčine
const char* nazov_Mesiaca_gen_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1] =
{
	{ "Januára", "Ledna", "January", "Ianuarii", "", "Ledna", "Január", "ru_text", "Студзеня", "Janúar", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Februára", "Února", "February", "Februarii", "", "Února", "Február", "ru_text", "Лютага", "Febrúar", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Marca", "Března", "March", "Martii", "", "Března", "Március", "ru_text", "Сакавіка", "Mars", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Apríla", "Dubna", "April", "Aprilis", "", "Dubna", "Április", "ru_text", "Красавіка", "Apríl", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Mája", "Května", "May", "Maii", "", "Května", "Május", "ru_text", "Мая", "Maí", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Júna", "Června", "June", "Iunii", "", "Června", "Június", "ru_text", "Чэрвеня", "Júní", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Júla", "Července", "July", "Iulii", "", "Července", "Július", "ru_text", "Ліпеня", "Júlí", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Augusta", "Srpna", "August", "Augusti", "", "Srpna", "Augusztus", "ru_text", "Жніўня", "Ágúst", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Septembra", "Září", "September", "Septembris", "", "Září", "Szeptember", "ru_text", "Верасня", "September", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Októbra", "Října", "October", "Octobris", "", "Října", "Október", "ru_text", "Кастрычніка", "Október", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Novembra", "Listopadu", "November", "Novembris", "", "Listopadu", "November", "ru_text", "Лістапада", "Nóvember", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Decembra", "Prosince", "December", "Decembris", "", "Prosince", "December", "ru_text", "Снежня", "Desember", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Neznámeho", "Neznámého", "Unknown", "ignotus", "", "Neznámého", "Ismeretlen", "ru_text", "by_text", "Óþekktur", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

#define		nazov_Mesiaca_gen(a)	nazov_Mesiaca_gen_jazyk[a][_global_jazyk]

// three-letter abbreviations of the names of the months used for anchors (uppercase, no need to translate; based on Slovak)
const char* nazov_MES[POCET_MESIACOV + 1] =
{ "JAN", "FEB", "MAR", "APR", "MAJ", "JUN", "JUL", "AUG", "SEP", "OKT", "NOV", "DEC", "___" };

// three-letter abbreviations of the names of the months used for anchors (lowercase, no need to translate; based on Slovak)
const char* nazov_mes[POCET_MESIACOV + 1] =
{ "jan", "feb", "mar", "apr", "maj", "jun", "jul", "aug", "sep", "okt", "nov", "dec", "___" };

// ordinal numbers for first few Sundays (sentence case) - used for special occasions currently only in Slovak; no need to change
// 2008-12-20: pridaný reťazec pre poradové číslo - používa sa v init_global_string() pre nedele niektorých období [zatiaľ iba v slovenčine]
const char* poradie_Slovom_jazyk[POCET_TYZDNOV + 1][POCET_JAZYKOV + 1] =
{
	{ "Prvá", "První", "", "Prima", "", "První", "1.", "ru_text", "Першая", "Fyrsti", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "Druhá", "Druhá", "", "Secunda", "", "Druhá", "2.", "ru_text", "Другая", "Annar", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "Tretia", "Třetí", "", "Tertia", "", "Třetí", "3.", "ru_text", "Трэцяя", "Þriðji", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "Štvrtá", "Čtvrtá", "", "Quarta", "", "Čtvrtá", "4.", "ru_text", "Чацвёртая", "Fjórði", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "Piata", "Pátá", "", "Quinta", "", "Pátá", "5.", "ru_text", "Пятая", "Fimmti", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "Šiesta", "Šestá", "", "Sexta", "", "Šestá", "6.", "ru_text", "Шостая", "Sjötti", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "Siedma", "Sedmá", "", "Septima", "", "Sedmá", "7.", "ru_text", "Сёмая", "Sjöundi", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "Ôsma", "Osmá", "", "VIII", "", "Osmá", "8.", "ru_text", "Восьмая", "Áttundi", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "Deviata", "Devátá", "IX", "", "", "Devátá", "9.", "ru_text", "Дзевятая", "Níundi", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "Desiata", "Desátá", "X", "", "", "Desátá", "10.", "ru_text", "Дзясятая", "Tíundi", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "11. ", "11", "11", "XI", "11", "11", "11.", "11.", "11.", "Ellefti", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "12. ", "12", "12", "XII", "12", "12", "12.", "12.", "12.", "Tólfti", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "13. ", "13", "13", "XIII", "13", "13", "13.", "13.", "13.", "Þrettándi", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "14. ", "14", "14", "XIV", "14", "14", "14.", "14.", "14.", "Fjórtándi", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "15. ", "15", "15", "XV", "15", "15", "15.", "15.", "15.", "Fimmtándi", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "16. ", "16", "16", "XVI", "16", "16", "16.", "16.", "16.", "Sextándi", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "17. ", "17", "17", "XVII", "17", "17", "17.", "17.", "17.", "Sautjándi", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "18. ", "18", "18", "XVIII", "18", "18", "18.", "18.", "18.", "Átjándi", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "19. ", "19", "19", "XIX", "19", "19", "19.", "19.", "19.", "Nítjándi",  /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "20. ", "20", "20", "XX", "20", "20", "20.", "20.", "20.", "Tuttugasti", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "21. ", "21", "21", "XXI", "21", "21", "21.", "21.", "21.", "Tuttugasti og fyrsti", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "22. ", "22", "22", "XXII", "22", "22", "22.", "22.", "22.", "Tuttugasti og annar", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "23. ", "23", "23", "XXIII", "23", "23", "23.", "23.", "23.", "Tuttugasti og þriðji", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "24. ", "24", "24", "XXIV", "24", "24", "24.", "24.", "24.", "Tuttugasti og fjórði", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "25. ", "25", "25", "XXV", "25", "25", "25.", "25.", "25.", "Tuttugasti og fimmti", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "26. ", "26", "26", "XXVI", "26", "26", "26.", "26.", "26.", "Tuttugasti og sjötti", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "27. ", "27", "27", "XXVII", "27", "27", "27.", "27.", "27.", "Tuttugasti og sjöundi", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "28. ", "28", "28", "XXVIII", "28", "28", "28.", "28.", "28.", "Tuttugasti og áttundi", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "29. ", "29", "29", "XXIX", "29", "29", "29.", "29.", "29.", "Tuttugasti og níundi", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "30. ", "30", "30", "XXX", "30", "30", "30.", "30.", "30.", "Þrítugasti", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "31. ", "31", "31", "XXXI", "31", "31", "31.", "31.", "31.", "Þrítugasti og fyrsti", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "32. ", "32", "32", "XXXII", "32", "32", "32.", "32.", "32.", "Þrítugasti og annar", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "33. ", "33", "33", "XXXIII", "33", "33", "33.", "33.", "33.", "Þrítugasti og þriðji", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "34. ", "34", "34", "XXXIV", "34", "34", "34.", "34.", "34.", "Þrítugasti og fjórði", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

// the names of rites
const char* nazov_ritu_jazyka[POCET_RITOV + 1][POCET_JAZYKOV + 1] =
{
	{
		"rímsky",
		"římský",
		"Roman",
		"Romanus",
		"Roman",
		"římský",
		"római",
		"ru_text",
		"by_text",
		"Rómverskur",
	/* STRING_2_FOR_NEW_LANGUAGE */
	},
	{
		"byzantský",
		"řecký",
		"Byzantine",
		"Byzantinus",
		"Byzantine",
		"řecký",
		"görög",
		"ru_text",
		"by_text",
		"Býsanskur",
	/* STRING_2_FOR_NEW_LANGUAGE */
	},
};
#define nazov_ritu(a) nazov_ritu_jazyka[a][_global_jazyk]

// the names of languages
// native names in respective languages
// 2006-07-11: Pridané kvôli jazykovým mutáciám
const char* nazov_jazyka_native_jazyk[POCET_JAZYKOV + 1][POCET_JAZYKOV + 1] =
{
	{ "slovenčina", "slovenština", "Slovak", "Slovaca", "___", "slovenština", "Szlovák", "ru_text", "by_text", "Slóvakíska", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "čeština", "čeština", "Czech", "Bohemica", "___", "čeština", "Czeh", "ru_text", "by_text", "Tékkneska", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "angličtina", "angličtina", "English", "Anglica", "___", "angličtina", "Angol", "ru_text", "by_text", "Enska", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "latičtina", "latina", "Latin", "Latina", "___", "latina", "Latin", "ru_text", "by_text", "Latneska", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "(neurčený)", "(neurčen)", "(not defined)", "(___)", "___", "(neurčen)", "hu_text", "ru_text", "by_text", "Óákveðið", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "čeština/dominikánsky", "čeština/dominikánský", "Czech/OP", "Bohemica/OP", "___", "čeština/dominikánský", "Czeh/OP", "ru_text", "by_text", "Tékkneska/dóminíkönsk tíðabænabók", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "maďarčina", "maďarština", "Hungarian", "Hungarica", "___", "maďarština", "Magyar", "ru_text", "by_text", "Ungverska", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "ruština", "ruština", "Russian", "Rusica", "___", "ruština", "Orosz", "русский", "by_text", "Rússneska", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "bieloruština", "běloruština", "Belarus", "Belarusica", "___", "běloruština", "Belorusz", "беларускі", "беларускі", "Hvítrússneska", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "islandčina", "islandština", "Iceland", "Icelandica", "___", "islandština", "Izlandi", "ru_text", "by_text", "Íslenska", /* STRING_1_FOR_NEW_LANGUAGE */ }
	/* ADD_VALUE_FOR_NEW_LANGUAGE */
};

#define nazov_jazyka_native_jazyk(a) nazov_jazyka_native_jazyk[a][_global_jazyk]

#define nazov_jazyka(a) nazov_jazyka_native_jazyk[a][a]
// { "slovenčina", "čeština", "English", "lingua latina", "(neurčený)", "čeština/dominikánský", "magyar", "русский", "беларускі", "Íslenska", /* STRING_1_FOR_NEW_LANGUAGE */ };

// language codes; internal usage for HTTP requests
const char* skratka_jazyka[POCET_JAZYKOV + 1] =
{ "sk", "cz", "en", "la", "??", "c2", "hu", "ru", "by", "is", /* STRING_1_FOR_NEW_LANGUAGE */ };

// language codes; internal usage for include directories (postfix of directory/folder name); postfix MUST NOT contain slash/backslash
// 2006-07-13 a 17: Pridané kvôli jazykovým mutáciám - postfix pre include adresár
const char* postfix_jazyka[POCET_JAZYKOV + 1] =
{ "", "cz", "en", "la", "", "czop", "hu", "ru", "by", "is", /* STRING_1_FOR_NEW_LANGUAGE */ };
// Poznámka: Postfix nesmie obsahovať na začiatku oddeľovač (slash resp. backslash); musí sa jednať o podadresár pod include

// language codes; internal usage for HTML page title
const char* skratka_jazyka_title[POCET_JAZYKOV + 1] =
{ "SK", "CZ", "EN", "LA", "??", "CZOP", "HU", "RU", "BY", "IS", /* STRING_1_FOR_NEW_LANGUAGE */ };

const short int format_datumu[POCET_JAZYKOV + 1] = {
	/* sk */ FORMAT_DATUMU_DEN_MESIAC_ROK,
	/* cz */ FORMAT_DATUMU_DEN_MESIAC_ROK,
	/* en */ FORMAT_DATUMU_MESIAC_DEN_ROK,
	/* la */ FORMAT_DATUMU_DEN_MESIAC_ROK,
	/* ?? */ FORMAT_DATUMU_DEN_MESIAC_ROK,
	/* czop */ FORMAT_DATUMU_DEN_MESIAC_ROK,
	/* hu */ FORMAT_DATUMU_ROK_MESIAC_DEN,
	/* ru */ FORMAT_DATUMU_DEN_MESIAC_ROK,
	/* by */ FORMAT_DATUMU_DEN_MESIAC_ROK,
	/* is */ FORMAT_DATUMU_DEN_MESIAC_ROK,
	/* ADD_VALUE_FOR_NEW_LANGUAGE */
};

const short int use_dot_for_ordinals[POCET_JAZYKOV + 1] = {
	/* sk */ FORMAT_DATE_USE_DOT_FOR_ORDINALS,
	/* cz */ FORMAT_DATE_USE_DOT_FOR_ORDINALS,
	/* en */ FORMAT_DATE_DO_NOT_USE_DOT_FOR_ORDINALS,
	/* la */ FORMAT_DATE_USE_DOT_FOR_ORDINALS,
	/* ?? */ FORMAT_DATE_USE_DOT_FOR_ORDINALS,
	/* czop */ FORMAT_DATE_USE_DOT_FOR_ORDINALS,
	/* hu */ FORMAT_DATE_USE_DOT_FOR_ORDINALS,
	/* ru */ FORMAT_DATE_USE_DOT_FOR_ORDINALS,
	/* by */ FORMAT_DATE_DO_NOT_USE_DOT_FOR_ORDINALS,
	/* is */ FORMAT_DATE_USE_DOT_FOR_ORDINALS,
	/* ADD_VALUE_FOR_NEW_LANGUAGE */
};

// Filename of CSS file; the number of CSS does not directly correspond to the number of languages
// Always use "breviar.css" plus override eventually
const char* nazov_css[POCET_CSS + 1] =
{ "(css neurčené)", "breviar.css", "breviar-invert-colors.css", "breviar-kbd.css" };

const char* skratka_css[POCET_CSS + 1] =
{ "__", "def", "invert", "kbd" };

// Language mutations
const short int default_css_jazyk[POCET_JAZYKOV + 1] =
{ CSS_breviar_sk, CSS_breviar_sk, CSS_breviar_sk, CSS_breviar_sk, CSS_breviar_sk, CSS_breviar_sk, CSS_breviar_sk, CSS_breviar_sk, CSS_breviar_sk, CSS_breviar_sk, /* ADD_VALUE_FOR_NEW_LANGUAGE */ };

// CSS obsahujuci invertovane farby | CSS for "night mode" (inverted colors) - includes ONLY ammendment to base css (breviar.css)
const char* nazov_css_invert_colors = "breviar-invert-colors.css";

// CSS obsahujuci force normal font weight | CSS for "no-bold mode" (only normal font) - includes ONLY ammendment to base css (breviar.css)
const char* nazov_css_normal_font_weight = "breviar-normal-font.css";

// voice output CSS | includes ONLY ammendment to base css (breviar.css)
const char* nazov_css_voice_output = "breviar-voice-output.css";

// CSS for rounded corners of buttons | includes ONLY ammendment to base css (breviar.css)
const char* nazov_css_rounded_corners = "breviar-rounded-corners.css";

// language charset (encoding); used for HTML heading | use CHARSET_UTF_8
const short int charset_jazyka[POCET_JAZYKOV + 1] =
{ CHARSET_UTF_8, CHARSET_UTF_8, CHARSET_UTF_8, CHARSET_UTF_8, CHARSET_UTF_8, CHARSET_UTF_8, CHARSET_UTF_8, CHARSET_UTF_8, CHARSET_UTF_8, CHARSET_UTF_8, /* ADD_VALUE_FOR_NEW_LANGUAGE */ };

const char* nazov_charset[POCET_CHARSET + 1] =
{ "utf-8", "windows-1250" };

const char* skratka_static_text[POCET_STATIC_TEXTOV + 1] =
{ "", "ma", "ord", "i" };

const char* html_title_static_text[POCET_STATIC_TEXTOV + 1][POCET_JAZYKOV + 1] =
{
	{ "", "", "", "", "", "", "", "", "", "", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Mariánske antifóny", "Mariánské zpěvy", "Mary antiphones", "Antiphonæ B. M. V.", "", "Mariánské antifóny", "Szűz Mária záró-antifónái", "ru_text", "by_text", "Andstef Maríu meyjar", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Ordinárium", "Uspořádání", "Ordinary", "Ordinarium", "", "Ordinárium", "Általános rész", "ru_text", "by_text", "Fastir liðir", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Info", "Info", "Info", "Info", "", "Info", "Info", "ru_text", "by_text", "Info", /* STRING_1_FOR_NEW_LANGUAGE */ },
};

const char* html_subtitle_static_text_info[POCET_INFO_TEXTOV + 1][POCET_JAZYKOV + 1] =
{
	{ "O aplikácii", "O aplikaci", "", "De applicationem progressione", "", "O aplikaci", "Névjegy...", "ru_text", "by_text", "Um forrit", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "Zmeny vo verziách", "Změny ve verzích", "Changelog", "Commutationes in versionibus", "", "Změny ve verzích", "Újdonságok", "ru_text", "by_text", "Breytingar í útgáfum", /* STRING_1_FOR_NEW_LANGUAGE */ },
};

const char* nazov_fontu[POCET_FONTOV + 1] =
{ "", "podľa CSS", "podľa výberu", "Cambria", "Candara", "Georgia", "Tahoma", "Verdana", "Helvetica", "serif", "sans-serif" };

const char* nazov_fontu_CHECKBOX[POCET_JAZYKOV + 1] =
{ "podľa výberu", "podle výběru", "according to checkbox above", "checkbox", "", "podle výběru", "checkbox", "ru_text", "by_text", "eftir vali", /* STRING_1_FOR_NEW_LANGUAGE */ };

const char* nazov_fontu_CSS[POCET_JAZYKOV + 1] =
{ "podľa CSS", "podle CSS", "according to CSS", "CSS", "CSS", "podle CSS", "CSS szerint", "ru_text", "by_text", "eftir CSS", /* STRING_1_FOR_NEW_LANGUAGE */ };

const char* nazov_font_size_jazyk[POCET_FONT_SIZE + 1][POCET_JAZYKOV + 1] =
{
	{ "", "", "", "", "", "", "", "", "", "", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "podľa CSS", "podle CSS", "according to CSS", "iuxta CSS", "", "podle CSS", "CSS szerint", "ru_text", "by_text", "eftir CSS", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "malilinké", "malinkaté", "xx-small", "minimum", "", "malinkaté", "apró", "ru_text", "by_text", "pínulítið", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "veľmi malé", "velmi malé", "extra small", "minus", "", "velmi malé", "nagyon kicsi", "ru_text", "by_text", "mjög lítill", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "malé", "malé", "small", "parvum", "", "malé", "kicsi", "ru_text", "by_text", "lítill", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "stredné", "střední", "medium", "mediocre", "", "střední", "közepes", "ru_text", "by_text", "miðlungs", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "veľké", "veliké", "large", "grande", "", "veliké", "nagy", "ru_text", "by_text", "stór", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "veľmi veľké", "velmi veliké", "grandissimum", "extra large", "", "velmi veliké", "nagyon nagy", "ru_text", "by_text", "mjög stór", /* STRING_1_FOR_NEW_LANGUAGE */ },
	{ "obrovské", "obrovské", "xx-large", "immane", "", "obrovské", "óriási", "ru_text", "by_text", "risastór", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

#define nazov_font_size(a) nazov_font_size_jazyk[a][_global_jazyk]

const char* nazov_font_size_css[POCET_FONT_SIZE + 1] =
{ "", "inherit", "xx-small", "x-small", "small", "medium", "large", "x-large", "xx-large" };

// special button: Details...
#ifndef HTML_BUTTON_DETAILY
#define HTML_BUTTON_DETAILY	html_button_nazov_modlitby_jazyk[MODL_DETAILY][_global_jazyk]
#endif

// special button: Show prayer
const char* html_button_det_show[POCET_JAZYKOV + 1] =
{ "Zobraz modlitbu", "Ukaž modlitbu", "Show prayer", "Ostende orationem", "", "Ukaž modlitbu", "Ima megjelenítése", "ru_text", "by_text", "Sýndu bæn", /* STRING_1_FOR_NEW_LANGUAGE */ };
#ifndef HTML_BUTTON_DET_SHOW
#define HTML_BUTTON_DET_SHOW	html_button_det_show[_global_jazyk]
#endif

// special button: Defaults
const char* html_button_det_defaults[POCET_JAZYKOV + 1] =
{ "Pôvodné hodnoty", "Původní hodnoty", "Defaults", "Prædefinita", "", "Původní hodnoty", "Alapértelmezett", "ru_text", "by_text", "Upprunaleg gildi", /* STRING_1_FOR_NEW_LANGUAGE */ };
#ifndef HTML_BUTTON_DET_DEFAULTS
#define HTML_BUTTON_DET_DEFAULTS	html_button_det_defaults[_global_jazyk]
#endif

// special button (today): Show
const char* html_button_dnes_show[POCET_JAZYKOV + 1] =
{ "Zobraziť", "Ukaž", "Show", "Ostende", "", "Ukaž", "Megjelenítés", "Показ", "by_text", "Sýna", /* STRING_1_FOR_NEW_LANGUAGE */ };
#ifndef HTML_BUTTON_DNES_SHOW
#define HTML_BUTTON_DNES_SHOW	html_button_dnes_show[_global_jazyk]
#endif

// special button (today): Defaults (clear form)
// const char* html_button_dnes_defaults[POCET_JAZYKOV + 1] = 
// { "Vyčisti", "Vyčisti", "Clear", "???", "", "Vyčisti", "Töröl", "ru_text", "by_text", "Hreinsaðu til", /* STRING_1_FOR_NEW_LANGUAGE */ };
#ifndef HTML_BUTTON_DNES_DEFAULTS
#define HTML_BUTTON_DNES_DEFAULTS	HTML_BUTTON_DET_DEFAULTS
#endif

// special button (today): Apply settings/options
const char* html_button_dnes_apply[POCET_JAZYKOV + 1] =
{ "Potvrdiť", "Potvrdit", "Apply", "Confirmare", "", "Potvrdit", "Alkalmaz", "ru_text", "by_text", "Staðfesta", /* STRING_1_FOR_NEW_LANGUAGE */ };
#ifndef HTML_BUTTON_DNES_APPLY_SETTINGS
#define HTML_BUTTON_DNES_APPLY_SETTINGS	html_button_dnes_apply[_global_jazyk]
#endif

// special button (today): Apply options 2 (various choices)
const char* html_button_dnes_apply2[POCET_JAZYKOV + 1] =
{ "Uložiť", "Uložit", "Save", "Condere", "", "Uložit", "Alkalmaz", "ru_text", "by_text", "Vista", /* STRING_1_FOR_NEW_LANGUAGE */ };
#ifndef HTML_BUTTON_DNES_APPLY_CHOICES
#define HTML_BUTTON_DNES_APPLY_CHOICES html_button_dnes_apply2[_global_jazyk]
#endif

// html <title> element for apps (application name)
const char* html_app_name[POCET_JAZYKOV + 1] =
{ "Breviár", "Breviář", "Breviary", "Breviarium", "", "Breviář", "Zsolozsma", "Литургия часов", "Літургія гадзінаў", "Tíðabænabók", /* STRING_1_FOR_NEW_LANGUAGE */ };

// html <title> element for generated pages
const char* html_title[POCET_JAZYKOV + 1] =
{ "Liturgia hodín", "Liturgie hodin", "Liturgy of Hours", "Liturgia horarum", "", "Liturgie hodin", "Az Imaórák Liturgiája", "Литургия часов", "Літургія гадзінаў", "Helgisiðalestrabók", /* STRING_1_FOR_NEW_LANGUAGE */ };

// html <title> element for pages generated for batch mode
const char* html_title_batch_mode[POCET_JAZYKOV + 1] =
{
	"Liturgia hodín – statické texty",
	"Liturgie hodin – statické texty",
	"Liturgy of Hours – static texts",
	"Liturgia horarum – scripta statica",
	"",
	"Liturgie hodin – statické texty",
	"Az Imaórák Liturgiája – állandó szövegek",
	"Литургия часов – статическиe тексты",
	"Літургія гадзінаў – by_text",
	"Helgisiðalestrabók – kyrrstæðir textar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_error_template[POCET_JAZYKOV + 1] =
{
	"Šablóna pre modlitbu sa nenašla. Zrejme neexistuje súbor `%s'.",
	"Šablona pro modlitbu se nenašla. Patrně neexistuje soubor `%s'.",
	"Template for prayer not found. File `%s' does not exist.",
	"Template for prayer not found. File `%s' does not exist.",
	"Template for prayer not found. File `%s' does not exist.",
	"Šablona pro modlitbu se nenašla. Patrně neexistuje soubor `%s'.",
	"Nem található sablon az imához. %s' fájl nem létezik.",
	"Template for prayer not found. File `%s' does not exist.",
	"by_text %s",
	"Sniðmát fyrir bæn fannst ekki. Skráin `%s' er ekki til.",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_error_saint[POCET_JAZYKOV + 1] =
{
	"V tento deň nie je sviatok žiadneho svätého, preto nemôžete požadovať svätého č. %d.",
	"V tento den nemá svátek žádný svatý, proto nemůžete požadovat svatého č. %d.",
	"For this date you cannot require saint nr. %d.",
	"For this date you cannot require saint nr. %d.",
	"For this date you cannot require saint nr. %d.",
	"V tento den nemá svátek žádný svatý, proto nemůžete požadovat svatého č. %d.",
	"hu_text %d.",
	"For this date you cannot require saint nr. %d.",
	"by_text %d",
	"Fyrir þessa dagsetningu er ekki hægt að krefjast heilags nr. %d.",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_error_saints[POCET_JAZYKOV + 1] =
{
	"Nie je viac ako %d sviatkov svätých v tento deň, preto nemôžete požadovať svätého č. %d.",
	"Není více slavení svatých jako %d, proto nemůžete požadovat svatého č. %d.",
	"For this date is not more saints than %d so you cannot require saint nr. %d.",
	"For this date is not more saints than %d so you cannot require saint nr. %d.",
	"For this date is not more saints than %d so you cannot require saint nr. %d.",
	"Není více slavení svatých jako %d, proto nemůžete požadovat svatého č. %d.",
	"hu_text %d; %d.",
	"For this date is not more saints than %d so you cannot require saint nr. %d.",
	"by_text %d; %d",
	"Fyrir þessa dagsetningu er ekki fleiri heilög en %d svo þú getur ekki krafist heilags nr. %d.",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_error_saturday_VM[POCET_JAZYKOV + 1] =
{
	"Tento deň je %s, a nie je sobota, takže nemôžete požadovať modlitbu `Spomienka Panny Márie v sobotu'.",
	"Tento den je %s, a není sobota, proto nemůžete požadovat modlitbu `Sobotní památka Panny Marie'.",
	"This day is %s, and is not Saturday, so you cannot require prayer `Saturday's memory of Virgin Mary'.",
	"This day is %s, and is not Saturday, so you cannot require prayer `Saturday's memory of Virgin Mary'.",
	"This day is %s, and is not Saturday, so you cannot require prayer `Saturday's memory of Virgin Mary'.",
	"Tento den je %s, a není sobota, proto nemůžete požadovat modlitbu `Sobotní památka Panny Marie'.",
	"hu_text %s.",
	"This day is %s, and is not Saturday, so you cannot require prayer `Saturday's memory of Virgin Mary'.",
	"by_text %s",
	"Þessi dagur er %s og er ekki laugardagur, þannig að þú getur ekki krafist bænar `Laugardagsminning Maríu mey`.",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_error_no_args[POCET_JAZYKOV + 1] =
{
	"Neboli zadané vstupné argumenty.",
	"Nebyli zadané vstupní argumenty.",
	"No input arguments.",
	"No input arguments.",
	"No input arguments.",
	"Nebyli zadané vstupní argumenty.",
	"No input arguments.",
	"No input arguments.",
	"by_text",
	"Það voru ekki settar inngöngu fyrirskipanir.",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_error_unknown_prayer[POCET_JAZYKOV + 1] =
{
	"Neznámy typ modlitby.",
	"Neznámý typ modlitby.",
	"Unknown prayer type.",
	"Unknown prayer type.",
	"Unknown prayer type.",
	"Neznámý typ modlitby.",
	"Unknown prayer type.",
	"Unknown prayer type.",
	"by_text",
	"Óþekkt tegund bæna.",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// navigation buttons/texts: previous, next, today
const char* html_button_predchadzajuci_[POCET_JAZYKOV + 1] = { "Predchádzajúci", "Předchozí", "Previous", "Præcedens", "", "Předchozí", "Előző", "Предыдущий", "папярэдні", "Fyrri", /* STRING_1_FOR_NEW_LANGUAGE */ };
const char* html_button_nasledujuci_[POCET_JAZYKOV + 1] = { "Nasledujúci", "Následující", "Next", "Sequens", "", "Následující", "Következő", "Следующий", "наступны", "Næst", /* STRING_1_FOR_NEW_LANGUAGE */ };
const char* html_button_dnes[POCET_JAZYKOV + 1] = { "dnes", "dnes", "today", "hodie", "", "dnes", "ma", "сегодня", "сёння", "í dag", /* STRING_1_FOR_NEW_LANGUAGE */ };
const char* html_button_Dnes[POCET_JAZYKOV + 1] = { "Dnes", "Dnes", "Today", "Hodie", "", "Dnes", "Ma", "Cегодня", "Сёння", "Í dag", /* STRING_1_FOR_NEW_LANGUAGE */ };

const char* html_button_tento_den[POCET_JAZYKOV + 1] = { "tento deň", "tento den", "this day", "hic dies" /* "hodie" */, "", "tento den", "ez a nap", "ru_text", "гэты дзень", "þessi dagur", /* STRING_1_FOR_NEW_LANGUAGE */ };

// basic words: day, month, year
const char* html_text_den[POCET_JAZYKOV + 1] = { "deň", "den", "day", "dies", "", "den", "nap", "день", "дзень", "dagur", /* STRING_1_FOR_NEW_LANGUAGE */ };
const char* html_text_mesiac[POCET_JAZYKOV + 1] = { "mesiac", "měsíc", "month", "mensis", "", "měsíc", "hó", "месяц", "месяц", "mánuður", /* STRING_1_FOR_NEW_LANGUAGE */ };
const char* html_text_rok[POCET_JAZYKOV + 1] = { "rok", "rok", "year", "annus", "", "rok", "év", "год", "год", "ár", /* STRING_1_FOR_NEW_LANGUAGE */ };
const char* html_text_Rok[POCET_JAZYKOV + 1] = { "Rok", "Rok", "Year", "Annus", "", "Rok", "Év", "Год", "Год", "Ár", /* STRING_1_FOR_NEW_LANGUAGE */ };
// in the following: you MUST keep all %d, %c, %s etc. variables - these are replaced by numbers, characters, strings, etc. respectively
const char* html_text_Rok_x[POCET_JAZYKOV + 1] = { "Rok %d", "Rok %d", "Year %d", "Anno %d", "%d", "Rok %d", "%.d év", "%d. годa", "%d год", "Ár %d", /* STRING_1_FOR_NEW_LANGUAGE */ };

const char* html_text_zoznam_mesiacov[POCET_JAZYKOV + 1] = { "zoznam mesiacov", "seznam měsíců", "list of months", "index mensium", "", "seznam měsíců", "hónapok listája", "список месяцев", "спіс месяцаў", "lista yfir mánuði", /* STRING_1_FOR_NEW_LANGUAGE */ };

const char* html_text_modlitba[POCET_JAZYKOV + 1] = { "modlitba", "modlitba", "prayer", "oratio", "", "modlitba", "imádság", "молитва", "малітва", "bæn", /* STRING_1_FOR_NEW_LANGUAGE */ };
const char* html_text_modlitby_pre_den[POCET_JAZYKOV + 1] = { "modlitby pre deň", "modlitby pro den", "prayers for date", "orationes pro die", "", "modlitby pro den", "", "молитвы за день", "малітвы на дату", "bænir fyrir daginn", /* STRING_1_FOR_NEW_LANGUAGE */ };
const char* html_text_alebo_pre[POCET_JAZYKOV + 1] = { "alebo pre", "anebo pro", "or for", "vel pro", "", "anebo pro", "vagy", "или для", "ці на", "eða fyrir", /* STRING_1_FOR_NEW_LANGUAGE */ };
const char* html_text_dnesok[POCET_JAZYKOV + 1] = { "dnešok", "dnešní den", "today", "hodie", "", "dnešní den", "a mai nap imaórái", "сегодня", "сёння", "í dag", /* STRING_1_FOR_NEW_LANGUAGE */ };

// 2010-02-15: pridané kvôli "zoznam.htm" batch mode
const char* html_text_Breviar_dnes[POCET_JAZYKOV + 1] = { "Breviár dnes", "Breviář dnes", "Breviary today", "Liturgia horarum hodie", "", "Breviář dnes", "A mai nap imaórája", "ru_text", "by_text", "Breviary í dag", /* STRING_1_FOR_NEW_LANGUAGE */ };
const char* html_text_Dnesne_modlitby[POCET_JAZYKOV + 1] = { "Dnešné modlitby", "Dnešní modlitby", "Today's prayers", "Orationes hodiernæ", "", "Dnešní modlitby", "A mai nap imái", "ru_text", "by_text", "Bænir dagsins", /* STRING_1_FOR_NEW_LANGUAGE */ };
const char* html_text_Prehlad_mesiaca[POCET_JAZYKOV + 1] = { "Prehľad mesiaca", "Přehled měsíce", "Month overview", "Index mensis", "", "Přehled měsíce", "A hónap áttekintése", "ru_text", "Прагляд месяца", "Mánaðaryfirlit", /* STRING_1_FOR_NEW_LANGUAGE */ };

// 2011-03-18: pridané do "zoznam.htm" batch mode -- kalendáre a hlavný nadpis
const char* html_text_batch_mode_h1[POCET_JAZYKOV + 1] = { "Liturgia hodín – Predgenerované modlitby", "Liturgie hodin – Předgenerované modlitby", "Liturgy of Hours – Pregenerated prayers", "Liturgia horarum – Orationes prægeneratæ", "", "Liturgie hodin – Předgenerované modlitby", "Az Imaórák Liturgiája – Előre generált imák", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ };
const char* html_text_Kalendar[POCET_JAZYKOV + 1] = { "Kalendár", "Kalendář", "Proprietary calendary", "Propria", "", "Kalendář", "Naptár", "ru_text", "Каляндар", "Dagatal", /* STRING_1_FOR_NEW_LANGUAGE */ };

const char* html_text_Vysvetlivky[POCET_JAZYKOV + 1] =
{
	"Vysvetlivky",
	"Vysvětlivky",
	"Legenda",
	"Legenda",
	"",
	"Vysvětlivky",
	"Jelmagyarázat",
	"ru_text",
	"Легенда",
	"Skýringar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_dalsie_moznosti[POCET_JAZYKOV + 1] =
{
	"Výber ďalších možností",
	"Další možnosti výběru ",
	"Choose from above (buttons) or from the following options: ",
	"Selectio delectus ceteri",
	"",
	"Další možnosti výběru",
	"További lehetőségek választása:",
	"ru_text",
	"Іншыя опцыі",
	"Valkostur fyrir aðra möguleika",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_dalsie_moznosti_1[POCET_JAZYKOV + 1] =
{
	"Nastavenia",
	"Nastavení",
	"Settings",
	"Instrumenta",
	"",
	"Nastavení",
	"Beállítások",
	"ru_text",
	"Налады",
	"Stillingar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_dalsie_moznosti_2[POCET_JAZYKOV + 1] =
{
	"Ďalšie zobrazenia",
	"Další zobrazení",
	"Other facilities",
	"Præsentationes aliæ",
	"",
	"Další zobrazení",
	"Más megjelenítési lehetőségek",
	"ru_text",
	"by_text",
	"Fleiri birtingarform",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_prik_sviatky_atd[POCET_JAZYKOV + 1] = {
	"prikázané sviatky a slávnosti Pána v roku ",
	"zasvěcené svátky a slavnosti Páně v roce ",
	"obligatory celebrations in year ",
	"sollemnitates de præcepto et sollemnitates Domini in anno",
	"",
	"zasvěcené svátky a slavnosti Páně v roce",
	"kötelező ünnepek",
	"ru_text",
	"by_text",
	"Skyldugir helgidagar og hátíðir Drottins á ári",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_lit_kalendar[POCET_JAZYKOV + 1] = {
	"liturgický kalendár pre",
	"liturgický kalendář pro",
	"liturgical calendar for",
	"calendarium liturgicum pro",
	"",
	"liturgický kalendář pro",
	"liturgikus naptár",
	"ru_text",
	"by_text",
	"Litúrgískt dagatal fyrir",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_roku[POCET_JAZYKOV + 1] = {
	"roku",
	"roku",
	"of year",
	"anni",
	"",
	"roku",
	"",
	"ru_text",
	"by_text",
	"ár",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_tabulka_pohyblive_od[POCET_JAZYKOV + 1] = {
	"tabuľka dátumov pohyblivých slávení od roku",
	"pohyblivé dny liturgického roku od",
	"table with dates of movable celebrations from year",
	"tabella temporaria festorum mobilium ab anno",
	"",
	"pohyblivé dny liturgického roku od",
	"a mozgó (változó) ünnepek táblázata a következő években",
	"ru_text",
	"by_text",
	"tafla dagsetninga hreyfanlegra hátíða frá ári",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_do_roku[POCET_JAZYKOV + 1] = {
	"do roku",
	"do",
	"till year",
	"usque ad annum",
	"",
	"do",
	"",
	"ru_text",
	"by_text",
	"til ársins",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_zobrazit_linky[POCET_JAZYKOV + 1] = {
	"zobraziť tabuľku vrátane hypertextových odkazov na jednotlivé dni",
	"zobrazit tabulku s hypertextovými odkazy pro jednotlivé dny",
	"display the table including hypertext links to each date",
	"ostende tabellam pro diebus singulis nexibus hypertextualibus inclusis",
	"",
	"zobrazit tabulku s hypertextovými odkazy pro jednotlivé dny",
	"A táblázat megjelenítése az egyes napokhoz tartozó hiperhivatkozásokkal együtt.",
	"ru_text",
	"by_text",
	"sýna töflu stiklutextatengla fyrir hvern dag",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_pre_cezrocne_obd[POCET_JAZYKOV + 1] = {
	"pre cezročné obdobie",
	"pro mezidobí",
	"for ...",
	"per annum",
	"",
	"pro dobu během roku",
	"",
	"ru_text",
	"by_text",
	"fyrir tíma innan ársins",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_tyzden_zaltara_cislo[POCET_JAZYKOV + 1] = {
	"%d. týždeň žaltára",
	"%d. týden žaltáře",
	"%d. week of Psaltary",
	"hebdomada %d psalterii",
	"%d",
	"%d. týden žaltáře",
	"%d. zsoltáros hét",
	"%d. ru_text",
	"%d. by_text",
	"%d. vika saltara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_tyzden_cislo[POCET_JAZYKOV + 1] = {
	"%d. týždeň",
	"%d. týden",
	"%d. week",
	"hebdomada %d",
	"%d",
	"%d. týden",
	"%d. hét",
	"%d ru_text",
	"%d by_text",
	"%d. vika",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_tyzden[POCET_JAZYKOV + 1] = {
	". týždeň",
	". týden",
	". week",
	"hebdomada ",
	"",
	". týden",
	". hét",
	"ru_text",
	"by_text",
	". vika",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_v_tyzdni_zaltara[POCET_JAZYKOV + 1] = {
	". týždni žaltára",
	". týdnu žaltáře",
	"week of Psaltary",
	"hebdomada",
	"",
	". týdnu žaltáře",
	". zsoltáros hét",
	"ru_text",
	"by_text",
	". vika saltara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_pre[POCET_JAZYKOV + 1] = {
	"pre",
	"pro",
	"for",
	"pro",
	"",
	"pro",
	"",
	"ru_text",
	"by_text",
	"fyrir",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_ordinarium[POCET_JAZYKOV + 1] = {
	"ordinárium",
	"uspořádání",
	"ordinary",
	"ordinarium",
	"",
	"ordinárium",
	"általános rész:",
	"ru_text",
	"by_text",
	"fastir liðir",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// in the following: you MUST keep all HTML elements, e.g. <a href...>, <br/> etc.
const char* html_text_dnes_je_atd[POCET_JAZYKOV + 1] =
{
	"Dnes je %d. deň v roku%s, " HTML_A_HREF_BEGIN "\"%s%s\">juliánsky dátum" HTML_A_END " JD = %ld%s.\n" HTML_LINE_BREAK,
	"Dnes je %d. den v roku%s, " HTML_A_HREF_BEGIN "\"%s%s\">juliánské datum" HTML_A_END " JD = %ld%s.\n" HTML_LINE_BREAK,
	"Today is %d. day in the year%s, " HTML_A_HREF_BEGIN "\"%s%s\">Julian date" HTML_A_END " JD = %ld%s.\n" HTML_LINE_BREAK,
	"Hodie est %d. die anno %s, " HTML_A_HREF_BEGIN "\"%s%s\">Iulianus datum" HTML_A_END " JD = %ld%s.\n" HTML_LINE_BREAK,
	"%d/%s" HTML_A_HREF_BEGIN "\"%s%s\">JD" HTML_A_END " = %ld%s.\n" HTML_LINE_BREAK,
	"Dnes je %d. den v roku%s, " HTML_A_HREF_BEGIN "\"%s%s\">juliánské datum" HTML_A_END " JD = %ld%s.\n" HTML_LINE_BREAK,
	"Ma %s %d. napja van, " HTML_A_HREF_BEGIN "\"%s%s\">Julián naptár" HTML_A_END " JD = %ld%s.\n" HTML_LINE_BREAK,
	"%d / %s ru_text, " HTML_A_HREF_BEGIN "\"%s%s\">ru_text" HTML_A_END " JD = %ld%s.\n" HTML_LINE_BREAK,
	"%d / %s by_text, " HTML_A_HREF_BEGIN "\"%s%s\">by_text" HTML_A_END " JD = %ld%s.\n" HTML_LINE_BREAK,
	"Í dag er %d. dagur ársins %s, " HTML_A_HREF_BEGIN "\"%s%s\">júlíönsk dagsetning" HTML_A_END " JD = %ld%s.\n" HTML_LINE_BREAK,
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_alebo[POCET_JAZYKOV + 1] = {
	"alebo",
	"nebo",
	"or",
	"vel",
	"",
	"nebo",
	"",
	"ru_text",
	"by_text",
	"eða",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_zakladne_info[POCET_JAZYKOV + 1] = {
	"Základné informácie",
	"Základní informace",
	"Basic info",
	"Informationes primæ",
	"",
	"Základní informace",
	"Alapvető információk",
	"ru_text",
	"Асноўная інфармацыя",
	"Grunnupplýsingar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_je[POCET_JAZYKOV + 1] = {
	"je",
	"je",
	"is",
	"est",
	"",
	"je",
	/* HU: van, ale nie pre prestupný */ "",
	"ru_text",
	"by_text",
	"er",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_nie_je[POCET_JAZYKOV + 1] = {
	"nie je",
	"není",
	"is not",
	"non est",
	"",
	"není",
	/* HU: nincs, ale nie pre prestupný */ "nem",
	"ru_text",
	"by_text",
	"er ekki",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_prestupny[POCET_JAZYKOV + 1] = {
	"priestupný",
	"přestupný",
	"en_text",
	"bisextilis",
	"",
	"přestupný",
	"szökőév",
	"ru_text",
	"by_text",
	"hlaupár",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_datumy_pohyblivych_slaveni[POCET_JAZYKOV + 1] = {
	"Dátumy pohyblivých slávení",
	"Pohyblivé dny liturgického roku",
	"Dates for movable celebrations",
	"Dies festorum mobilium",
	"",
	"Pohyblivé dny liturgického roku",
	"A mozgó (változó) ünnepek dátumai",
	"ru_text",
	"by_text",
	"Dagsetning hreyfanlegra hátíða",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_ritus[POCET_JAZYKOV + 1] = {
	"Rítus",
	"Obřad",
	"Ritus",
	"Ritus",
	"",
	"Ritus",
	"Szertartás",
	"ru_text",
	"by_text",
	"Siður",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_android_native_menu[POCET_JAZYKOV + 1] = {
	"Pre zmenu nastavení použite menu aplikácie. Do menu sa dostanete ťuknutím na ikonu troch vodorovných čiar umiestnenú vľavo na hornej lište aplikácie (tzv. „hamburger“ ikona ☰). Ak máte aktivovaný režim „na celú obrazovku“ (fullscreen mode), stačí ho deaktivovať gestom dvojitého ťuknutia – tak zobrazíte hornú lištu. Menu sa dá štandardne vysunúť aj gestom posunutia od ľavého okraja obrazovky k stredu (vodorovný posun). Od Android 10 je potrebné pri ľavom okraji obrazovky chvíľu podržať a až následne posunúť (ináč sa aktivuje akcia „späť“, čo zväčša vedie k zatvoreniu appky a návratu na hlavnú obrazovku zariadenia).",
	"Pro nastavení použijte menu aplikace. Do menu se dostanete klepnutím na ikonu tří vodorovných čar umístěnou vlevo na horní liště aplikace (tzv. „hamburger“ ikona ☰). Pokud máte aktivovaný režim „na celou obrazovku“ (fullscreen mode), stačí jej deaktivovat gestem dvojitého ťuknutí – tak zobrazíte horní lištu. Menu lze standardně vysunout i gestem posunutí od levého okraje obrazovky ke středu (vodorovný posun). Od Android 10 je třeba při levém okraji obrazovky chvíli podržet a až následně posunout (jinak se aktivuje akce „zpět“, což většinou vede k zavření appky a návratu na hlavní obrazovku zařízení).",
	"Use app native menu for settings. You can open the menu by tapping the icon of three horizontal lines located on the left of the top bar of the application (so-called “hamburger” icon ☰). If you have activated the fullscreen mode just deactivate it with a double-tap gesture - this will display the top bar. By default, the menu can also be extended by swiping from the left edge of the screen to the center (horizontal swipte). From Android 10, you need to hold the left edge of the screen for a moment and then move (otherwise the “back” action is activated, which usually leads to closing the app and returning to the main device screen).",
	"Utere app indigena menu pro occasus. Menu aperire potes, iconem trium linearum horizontalium in sinistro summo vectis applicationis positas (ut vocant «hamburger» iconem ☰). Si modum fullscreen modo reduxisti, illum cum duplici gestu deprime - hoc vectem summo ostendet. Defalta, menu etiam trahi potest ab ora sinistra screen ad centrum (swipte horizontalis). Ex Android 10, sinistram partem screen tenere debes ad momentum et tunc movere (aliter actio «terga» excitatur, quæ solet claudere ad app claudendum et ad principale tegumentum rediens).",
	"",
	"Pro nastavení použijte menu aplikace. Do menu se dostanete klepnutím na ikonu tří vodorovných čar umístěnou vlevo na horní liště aplikace (tzv. „hamburger“ ikona ☰). Pokud máte aktivovaný režim „na celou obrazovku“ (fullscreen mode), stačí jej deaktivovat gestem dvojitého ťuknutí – tak zobrazíte horní lištu. Menu lze standardně vysunout i gestem posunutí od levého okraje obrazovky ke středu (vodorovný posun). Od Android 10 je třeba při levém okraji obrazovky chvíli podržet a až následně posunout (jinak se aktivuje akce „zpět“, což většinou vede k zavření appky a návratu na hlavní obrazovku zařízení).",
	"A beállításokhoz használja az alkalmazás menüt. A menüt az alkalmazás felső sávjának bal oldalán található három vízszintes vonal ikonjának megérintésével érheti el (ún. „hamburger” ikon ☰). Ha be van kapcsolva a „teljes képernyős” mód, egyszerűen kapcsolja ki egy dupla érintéssel – ekkor megjelenik a felső sáv. Alapértelmezés szerint a menü a képernyő bal szélétől a közepéig görgetéssel is bővíthető (vízszintes görgetés). Android 10-től egy pillanatig meg kell tartani a képernyő bal szélét, majd mozogni (ellenkező esetben a „vissza” művelet aktiválódik, ami általában az alkalmazás bezárásához és az eszköz főképernyőjére való visszatéréshez vezet).",
	"",
	"",
	"Notaðu forritavalmyndina fyrir stillingar. Þú kemst í valmyndina með því að smella á táknið með þremur láréttum línum sem staðsettar eru vinstra megin á efstu stikunni í forritinu (svokallað „hamborgara“ tákn ☰). Ef þú ert með „fullan skjá“ stillingu virkan, slökktu bara á henni með tvisvar snertibending - þetta mun birta efstu stikuna. Sjálfgefið er að einnig er hægt að stækka valmyndina með því að fletta frá vinstri brún skjásins að miðju (lárétt flun). Frá Android 10 þarftu að halda í augnablik á vinstri brún skjásins og hreyfa þig svo (annars er „til baka“ aðgerðin virkjuð, sem venjulega leiðir til þess að appinu er lokað og farið aftur á aðalskjá tækisins).",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_den_v_roku[POCET_JAZYKOV + 1] = {
	"%d. deň v roku",
	"%d. den v roce",
	"%d. day of the year",
	"%d. dies per annum",
	"%d. ",
	"%d. den v roce",
	"az év %d. napja",
	"%d. ru_text",
	"%d. by_text",
	"%d. dagur í ári",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_zacina[POCET_JAZYKOV + 1] = {
	"začína",
	"začíná",
	"starts",
	"incipit",
	"",
	"začíná",
	"kezdődik",
	"ru_text",
	"by_text",
	"byrjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_liturgicky_rok[POCET_JAZYKOV + 1] = {
	"liturgický rok",
	"liturgický rok",
	"liturgical year",
	"annus liturgicus",
	"",
	"liturgický rok",
	"liturgikus év",
	"ru_text",
	"by_text",
	"helgisiðaár",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_txt_export[POCET_JAZYKOV + 1] = {
	"Textový výstup",
	"Textový výstup",
	"Text export",
	"Export textuum",
	"",
	"Textový výstup",
	"Szöveg exportálása",
	"ru_text",
	"by_text",
	"Textagerð",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

#define POCET_HTML_TEXT_POHYBLIVE 12
#define HTML_TEXT_POHYBLIVE_ZJAVENIE_PANA 3

const char* html_text_pohyblive[POCET_HTML_TEXT_POHYBLIVE + 1][POCET_JAZYKOV + 1] = {
{
	"Rok" HTML_LINE_BREAK "Pána",
	"Léto" HTML_LINE_BREAK "Páně",
	"Anno" HTML_LINE_BREAK "Domini",
	"Anno" HTML_LINE_BREAK "Domini",
	"",
	"Léto" HTML_LINE_BREAK "Páně",
	"Naptári" HTML_LINE_BREAK "év",
	"ru_text",
	"by_text",
	"Anno" HTML_LINE_BREAK "Domini",
	/* STRING_2_FOR_NEW_LANGUAGE */
},
{
	"Nedeľná" HTML_LINE_BREAK "litera",
	"Nedělní" HTML_LINE_BREAK "písmeno",
	"Sunday" HTML_LINE_BREAK "Letter",
	"Literæ" HTML_LINE_BREAK "Domin.",
	"",
	"Nedělní" HTML_LINE_BREAK "písmeno",
	"Vasár-" HTML_LINE_BREAK "nap" HTML_LINE_BREAK "betűje",
	"ru_text",
	"by_text",
	"Sunnudags-" HTML_LINE_BREAK "stafur",
	/* STRING_2_FOR_NEW_LANGUAGE */
},
{
	"Nedeľný" HTML_LINE_BREAK "cyklus",
	"Nedělní" HTML_LINE_BREAK "cyklus",
	"Sunday" HTML_LINE_BREAK "cycle",
	"Cycl." HTML_LINE_BREAK "Dom.",
	"",
	"Nedělní" HTML_LINE_BREAK "cyklus",
	"Vasár-" HTML_LINE_BREAK "napi" HTML_LINE_BREAK "ciklus",
	"ru_text",
	"by_text",
	"Sunnudags-" HTML_LINE_BREAK "hringrás",
	/* STRING_2_FOR_NEW_LANGUAGE */
},
{
	"Zjavenie" HTML_LINE_BREAK "Pána",
	"Zjevení" HTML_LINE_BREAK "Páně",
	"Epiphany",
	"Epiphania" HTML_LINE_BREAK "Domini",
	"",
	"Zjevení" HTML_LINE_BREAK "Páně",
	"Urunk" HTML_LINE_BREAK "megjelenése" HTML_LINE_BREAK "(Vízkereszt)",
	"ru_text",
	"by_text",
	"Birting" HTML_LINE_BREAK "Drottins",
	/* STRING_2_FOR_NEW_LANGUAGE */
},
{
	// see also: text_JAN_KRST[]
	"Krst" HTML_LINE_BREAK "Pána",
	"Křtu" HTML_LINE_BREAK "Páně",
	"Bapt. of" HTML_LINE_BREAK "the Lord",
	"Bapt." HTML_LINE_BREAK "Domini",
	"",
	"Křtu" HTML_LINE_BREAK "Páně",
	"Urunk" HTML_LINE_BREAK "megkeresztel-" HTML_LINE_BREAK "kedése",
	"ru_text",
	"by_text",
	"Skírn" HTML_LINE_BREAK "Drottins",
	/* STRING_2_FOR_NEW_LANGUAGE */
},
{
	HTML_A_HREF_BEGIN "\"#explain\">OCR" HTML_LINE_BREAK "pred" HTML_LINE_BREAK "PO" HTML_A_END,
	HTML_A_HREF_BEGIN "\"#explain\">LM" HTML_LINE_BREAK "před" HTML_LINE_BREAK "DP" HTML_A_END,
	"...",
	HTML_A_HREF_BEGIN "\"#explain\">HPA" HTML_LINE_BREAK "ante" HTML_LINE_BREAK "Quadr." HTML_A_END,
	"",
	HTML_A_HREF_BEGIN "\"#explain\">LM" HTML_LINE_BREAK "před" HTML_LINE_BREAK "DP" HTML_A_END,
	"EK" HTML_LINE_BREAK "a HSZ" HTML_LINE_BREAK "előtt",
	"ru_text",
	"by_text",
	HTML_A_HREF_BEGIN "\"#explain\">HPA" HTML_LINE_BREAK "ante" HTML_LINE_BREAK "Quadr." HTML_A_END,
	/* STRING_2_FOR_NEW_LANGUAGE */
},
{
	// see also: text_POPOLCOVA_STREDA[]
	"Popolcová" HTML_LINE_BREAK "streda",
	"Popeleční" HTML_LINE_BREAK "středa",
	"Ash" HTML_LINE_BREAK "Wednesday",
	"Dies" HTML_LINE_BREAK "cinerum",
	"",
	"Popeleční" HTML_LINE_BREAK "středa",
	"Hamvazó-" HTML_LINE_BREAK "szerda",
	"ru_text",
	"Папяльцовая" HTML_LINE_BREAK "серада",
	"Öskudagur",
	/* STRING_2_FOR_NEW_LANGUAGE */
},
{
	"Veľká" HTML_LINE_BREAK "noc",
	"Zmrtvých-" HTML_LINE_BREAK "vstání" HTML_LINE_BREAK "Páně",
	"Easter",
	"Pascha",
	"",
	"Zmrtvých-" HTML_LINE_BREAK "vstání" HTML_LINE_BREAK "Páně",
	"Húsvét",
	"ru_text",
	"by_text",
	"Páskadagur",
	/* STRING_2_FOR_NEW_LANGUAGE */
},
{
	"Nanebo-" HTML_LINE_BREAK "vstúpenie" HTML_LINE_BREAK "Pána",
	"Nanebe-" HTML_LINE_BREAK "vstoupení" HTML_LINE_BREAK "Páně",
	"...",
	"Ascensio",
	"",
	"Nanebe-" HTML_LINE_BREAK "vstoupení" HTML_LINE_BREAK "Páně",
	"Urunk" HTML_LINE_BREAK "menny-" HTML_LINE_BREAK "bemenetele",
	"ru_text",
	"by_text",
	"Uppstigning" HTML_LINE_BREAK "Drottins",
	/* STRING_2_FOR_NEW_LANGUAGE */
},
{
	// see also: text_ZOSLANIE_DUCHA_SVATEHO[]
	"Zoslanie" HTML_LINE_BREAK "Ducha" HTML_LINE_BREAK "Svätého",
	"Seslání" HTML_LINE_BREAK "Ducha" HTML_LINE_BREAK "Svatého",
	"...",
	"Pentecostes",
	"",
	"Seslání" HTML_LINE_BREAK "Ducha" HTML_LINE_BREAK "Svatého",
	"Pünkösd",
	"ru_text",
	"Нядзеля" HTML_LINE_BREAK "Спаслання" HTML_LINE_BREAK "Святога" HTML_LINE_BREAK "Духа",
	"Hvítasunna",
	/* STRING_2_FOR_NEW_LANGUAGE */
},
{
	HTML_A_HREF_BEGIN "\"#explain\">OCR" HTML_LINE_BREAK "po" HTML_LINE_BREAK "VN" HTML_A_END,
	HTML_A_HREF_BEGIN "\"#explain\">LM" HTML_LINE_BREAK "po" HTML_LINE_BREAK "DV" HTML_A_END,
	"...",
	HTML_A_HREF_BEGIN "\"#explain\">HPA" HTML_LINE_BREAK "post" HTML_LINE_BREAK "temp. pasch." HTML_A_END,
	"",
	HTML_A_HREF_BEGIN "\"#explain\">LM" HTML_LINE_BREAK "po" HTML_LINE_BREAK "DV" HTML_A_END,
	"EK" HTML_LINE_BREAK "a HU" HTML_LINE_BREAK "után",
	"ru_text",
	"by_text",
	HTML_A_HREF_BEGIN "\"#explain\">HPA" HTML_LINE_BREAK "post" HTML_LINE_BREAK "temp. pasch." HTML_A_END,
	/* STRING_2_FOR_NEW_LANGUAGE */
},
{
	"Prvá" HTML_LINE_BREAK "adventná" HTML_LINE_BREAK "nedeľa",
	"První" HTML_LINE_BREAK "neděle" HTML_LINE_BREAK "adventní",
	"...",
	"Dominica" HTML_LINE_BREAK "prima" HTML_LINE_BREAK "Adventus",
	"",
	"První" HTML_LINE_BREAK "neděle" HTML_LINE_BREAK "adventní",
	"Advent" HTML_LINE_BREAK "első" HTML_LINE_BREAK "vasárnapja",
	"ru_text",
	"by_text",
	"Fyrsti" HTML_LINE_BREAK "sunnudagur" HTML_LINE_BREAK "í aðventu",
	/* STRING_2_FOR_NEW_LANGUAGE */
},
{
	"Sviatok" HTML_LINE_BREAK "Svätej" HTML_LINE_BREAK "rodiny",
	"Svátek" HTML_LINE_BREAK "Svaté" HTML_LINE_BREAK "rodiny",
	"...",
	"Festum" HTML_LINE_BREAK "Sanctæ" HTML_LINE_BREAK "Familiæ",
	"",
	"Svátek" HTML_LINE_BREAK "Svaté" HTML_LINE_BREAK "rodiny",
	"Szent" HTML_LINE_BREAK "Család" HTML_LINE_BREAK "ünnepe",
	"ru_text",
	"Святой Сям'і:" HTML_LINE_BREAK "Езуса, Марыі і Юзафа",
	"Hátíð" HTML_LINE_BREAK "hinnar heilögu" HTML_LINE_BREAK "fjölskyldu",
	/* STRING_2_FOR_NEW_LANGUAGE */
}
};

const char* html_text_Nedelne_pismeno[POCET_JAZYKOV + 1] = { "Nedeľné písmeno", "Nedělní písmeno", "Sunday letter", "Littera dominicæ", "", "Nedělní písmeno", "A vasárnap betűje", "ru_text", "Нядзельны цыкл", "Sunnudagsstafur", /* STRING_1_FOR_NEW_LANGUAGE */ };
const char* html_text_Nedelne_pismena[POCET_JAZYKOV + 1] = { "Nedeľné písmená", "Nedělní písmena", "Sunday letters", "Litteræ dominicæ", "", "Nedělní písmena", "A vasárnap betűje", "ru_text", "Нядзельныя цыклы", "Sunnudagsstafir", /* STRING_1_FOR_NEW_LANGUAGE */ };

const char* html_text_Od_prvej_adv_atd[POCET_JAZYKOV + 1] = {
	"Od Prvej adventnej nedele v roku %d (%s) pokračuje " HTML_A_HREF_BEGIN "\"%s%s\">liturgický rok" HTML_A_END " <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END ".",
	"Od první neděle adventní v roku %d (%s) pokračuje " HTML_A_HREF_BEGIN "\"%s%s\">liturgický rok" HTML_A_END " <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END ".",
	"From the 1st Advent Sunday in the year %d (%s) continues " HTML_A_HREF_BEGIN "\"%s%s\">liturgical year" HTML_A_END " <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END ".",
	"Anno Domini %d (%s) a Dominica I Adventus pergit " HTML_A_HREF_BEGIN "\"%s%s\">annus liturgicus" HTML_A_END " <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END ".",
	"",
	"Od první neděle adventní v roce %d (%s) pokračuje " HTML_A_HREF_BEGIN "\"%s%s\">liturgický rok" HTML_A_END " <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END ".",
	"%d (%s) advent első vasárnapjától az <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END " " HTML_A_HREF_BEGIN "\"%s%s\">liturgikus év" HTML_A_END " folytatódik.",
	"ru_text | From the 1st Advent Sunday in the year %d (%s) continues " HTML_A_HREF_BEGIN "\"%s%s\">liturgical year" HTML_A_END " <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END ".",
	"by_text | From the 1st Advent Sunday in the year %d (%s) continues " HTML_A_HREF_BEGIN "\"%s%s\">liturgical year" HTML_A_END " <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END ".",
	"Frá fyrsta sunnudegi í aðventu í ári %d (%s) heldur áfram " HTML_A_HREF_BEGIN "\"%s%s\">litúrgískt ár" HTML_A_END " <" HTML_SPAN_BOLD ">%s" HTML_SPAN_END ".",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_Po_Velkej_noci_atd[POCET_JAZYKOV + 1] = {
	"Po Veľkej noci nasleduje %d. %s v cezročnom období.",
	"Po Velikonocích následuje %d. %s v mezibdobí.",
	"After Easter follows %d. %s per annum.",
	"Post Pacham pergit %d. %s per annum.",
	"Po Veľkej noci nasleduje %d. %s v cezročnom období.", // v období „cez rok“
	"Po Velikonocích následuje %d. %s v mezibdobí.",
	"Húsvét után az évközi idő %d. %sja következik.", // vasárnapja, nedeľa = vasárnap
	"ru_text %d. %s",
	"by_text %d. %s",
	"Eftir páska kemur %d. %s innan ársins.",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_Prikazane_sviatky_v_roku[POCET_JAZYKOV + 1] = {
	"Prikázané sviatky v roku %s",
	"Zasvěcené svátky v roce %s",
	"Holy days of obligation in the year %s",
	"Festa de præcepto anno Domini %s",
	"Prikázané sviatky v roku %s",
	"Zasvěcené svátky v roce %s",
	"%s kötelező ünnepei",
	"ru_text %s",
	"by_text %s",
	"Fyrirskipaðar hátíðir ársins %s",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_Jednotlive_mesiace_roku[POCET_JAZYKOV + 1] = {
	"Jednotlivé mesiace roku %s",
	"Jednotlivé měsíce v roce %s",
	"Individual months of the year %s",
	"Menses individuales anni Domini %s",
	"Jednotlivé mesiace roku %s",
	"Jednotlivé měsíce v roce %s",
	"Egyes hónapok %s-ben(-ban)",
	"ru_text %s",
	"by_text %s",
	"Einstakir mánuðir ársins %s",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* str_doplnkova_psalmodia[POCET_JAZYKOV + 1] =
{ "doplnková psalmódia", "žalmy z doplňovacího cyklu", "supplementary psalmody", "psalmodia complementaris", "", "doplňková psalmodie", "kiegészítő zsoltárok", "ru_text", "дадатковая псальмодыя", "aukasálmar", /* STRING_1_FOR_NEW_LANGUAGE */ };

const char* str_modl_cez_den_zalmy_zo_dna[POCET_JAZYKOV + 1] =
{ "bežnej psalmódie", "běžné psalmodie", "ordinary psalmody", "psalmodiæ ordinariæ", "", "běžné psalmodie", "soros zsoltárösszeállítást", "ru_text", "са звычайнай псальмодыі", "almennum sálmasöngvum", /* STRING_1_FOR_NEW_LANGUAGE */ };
#define		STR_MODL_CEZ_DEN_ZALMY_ZO_DNA 	str_modl_cez_den_zalmy_zo_dna[_global_jazyk]

const char* str_modl_cez_den_doplnkova_psalmodia[POCET_JAZYKOV + 1] =
{ "doplnkovej psalmódie", "doplňovacího cyklu", "supplementary psalmody", "psalmodiæ complementaris", "", "doplňkové psalmodie", "kiegészítő zsoltárok", "ru_text", "з дадатковай псальмодыі", "viðbótarsálmasöngvum", /* STRING_1_FOR_NEW_LANGUAGE */ };
#define		STR_MODL_CEZ_DEN_DOPLNKOVA_PSALMODIA 	str_modl_cez_den_doplnkova_psalmodia[_global_jazyk]

const char* str_modl_zalmy_zo_dna[POCET_JAZYKOV + 1] =
{ "dňa", "dne", "day", "die", "", "dne", "naptól", "ru_text", "з дня", "dagsins", /* STRING_1_FOR_NEW_LANGUAGE */ };
#define		STR_MODL_ZALMY_ZO_DNA 	str_modl_zalmy_zo_dna[_global_jazyk]

const char* str_modl_zalmy_zo_sv[POCET_JAZYKOV + 1] =
{ "sviatku", "svátku", "celebration", "festi", "", "svátku", "ünneptől", "ru_text", "з цэлебрацыі", "hátíðar", /* STRING_1_FOR_NEW_LANGUAGE */ };
#define		STR_MODL_ZALMY_ZO_SV 	str_modl_zalmy_zo_sv[_global_jazyk]

#define STR_VALUE_TRUE  "1"
#define STR_VALUE_FALSE "0"
#define STR_VALUE_ZERO  "0"

const char* str_ano[POCET_JAZYKOV + 1] =
{ "áno", "ano", "yes", "sic", "___", "ano", "igen", "ru_text", "так", "já", /* STRING_1_FOR_NEW_LANGUAGE */ };
#define		STR_ANO		str_ano[_global_jazyk]

const char* str_nie[POCET_JAZYKOV + 1] =
{ "nie", "ne", "no", "non", "___", "ne", "nem", "ru_text", "не", "nei", /* STRING_1_FOR_NEW_LANGUAGE */ };
#define		STR_NIE		str_nie[_global_jazyk]

const char* html_text_Jazyk[POCET_JAZYKOV + 1] =
{
	"Jazyk",
	"Jazyk",
	"Language",
	"Lingua",
	"Language",
	"Jazyk",
	"Nyelv",
	"ru_text",
	"Мова",
	"Tungumál",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_jazyk_verzia[POCET_JAZYKOV + 1] =
{
	"Jazyk/verzia breviára",
	"Jazyk/verze breviáře",
	"Language/Breviary version",
	"Lingua/versio Breviarii",
	"Language/Breviary version",
	"Jazyk/verze breviáře",
	"Nyelv/zsolozsma verzió",
	"ru_text",
	"Мова/Версія літургіі гадзінаў",
	"Tungumál",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_jazyk_long[POCET_JAZYKOV + 1] =
{
	"Liturgia hodín v jazyku:",
	"Liturgie hodin pro jazyk:",
	"Liturgy of hours in language:",
	"LH in lingua:",
	"",
	"Liturgie hodin pro jazyk:",
	"",
	"ru_text",
	"by_text",
	"Tíðabænabók í tungumáli:",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_jazyk_explain[POCET_JAZYKOV + 1] =
{
	"Liturgia hodín pre iný jazyk.",
	"Liturgie hodin pro jiný jazyk.",
	"Liturgy of hours in other languages.",
	"LH in lingua cetera",
	"",
	"Liturgie hodin pro jiný jazyk.",
	"",
	"ru_text",
	"by_text",
	"Tíðabænabók fyrir annað tungumál.",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_detaily_uvod[POCET_JAZYKOV + 1] =
{
	"Nasledovné možnosti ovplyvnia vzhľad i obsah vygenerovanej modlitby.\nVyberte tie možnosti, podľa ktorých sa má modlitba vygenerovať.",
	"Následující možnosti mají vliv na vzhled i obsah vygenerované modlitby.\nVyberte si možnosti, podle kterých má být modlitba vygenerována.",
	"The following options apply to the resulting generated text of the prayer.\nChoose options which fit your needs to the resulting prayer text.",
	"Possibilitates sequentes ad aspectum Officii ingenerati et quod continetur momentum habent.\nDeligite possibilitates illas, secundum quas Officium ingenerandum est.",
	"",
	"Následující možnosti mají vliv na vzhled i obsah vygenerované modlitby.\nVyberte si možnosti, podle kterých má být modlitba vygenerována.",
	"Ez a választási lehetőség befolyásolja a megszerkesztett ima megjelenítését és tartalmát.\nVálasszon a szerkeszthető lehetőségek közül.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_kalendar[POCET_JAZYKOV + 1] =
{
	"nastavenia pre liturgický kalendár",
	"volby pro liturgický kalendář",
	"settings for liturgical calendar",
	"occasiones pro calendario liturgico",
	"",
	"volby pro liturgický kalendář",
	"a liturgikus naptár beállításai",
	"ru_text",
	"налады літургічнага календара",
	"stillingar fyrir litúrgískt dagatal",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_kalendar_explain[POCET_JAZYKOV + 1] =
{
	"Liturgia hodín ponúka možnosť slávenia niektorých slávení dvojakým spôsobom; závisí od danej krajiny, ako rozhodla príslušná konferencia biskupov.",
	"Volby pro liturgický kalendář ovlivňují datumy některých slavení.",
	"Options for liturgical calendar...",
	"In Liturgia horarum proponitur modus duplex persolvendi celebrationum aliquarum; id pendet ex Conferentia episcoporum.",
	"",
	"Volby pro liturgický kalendář ovlivňují datumy některých slavení.",
	"Az Imaórák liturgiája megadja a lehetőséget, hogy némely ünnepek kétféleképpen legyenek megünnepelve; az adott országtól függ, ahogy az adott püspöki konferencia döntött.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_nemenne_sucasti[POCET_JAZYKOV + 1] =
{
	"zobraziť nasledovné súčasti modlitby?",
	"zobrazit <i>neměnné součásti</i> modlitby?",
	"display <i>non-changeable parts</i> of prayer?",
	"partes Officii sequentes ostende?",
	"",
	"zobrazit <i>neměnné součásti</i> modlitby?",
	"jelenjenek meg az imaóra következő elemei:",
	"ru_text",
	"паказваць <i>нязменныя часткі</i> малітвы?",
	"sýna eftirfarandi hluta bænar?",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_nemenne_sucasti_explain[POCET_JAZYKOV + 1] =
{
	"Každé ranné chvály obsahujú Benediktus, vešpery Magnifikat, obe modlitby obsahujú Otčenáš a zakončenie modlitby, a napokon posvätné čítanie obsahuje niekedy hymnus Te Deum; tieto časti modlitby možno zobraziť alebo skryť.",
	"Každé ranní chvály obsahují Zachariášovo kantikum, nešpory kantikum Panny Marie, obě modlitbu Páně a zakončení modlitby, a konečně modlitba se čtením někdy obsahuje hymnus Te Deum; tyto části modliteb je možné zobrazit/skrýt.",
	"Each morning prayer contains Benedictus, vespers contain Magnificat, both contain the Lord's Prayer and a conclusion of the prayer; finally, the Office of readings sometimes contains the hymn Te Deum; all these parts can be shown/hidden.",
	"Laudes matutines continent canticum Benedictus, Vesperæ canticum Magnificat, utræque Horas orationem dominica et conclusionem Horæ, et Officium lectionis hymnum Te Deum; omnes hæ partes abscondi potest.",
	"",
	"Každé ranní chvály obsahují Zachariášovo kantikum, večerní chvály kantikum Panny Marie, obě modlitbu Páně a zakončení modlitby, a konečně modlitba se čtením někdy obsahuje hymnus Te Deum; tyto části je možné zobrazit/skrýt.",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_dalsie_prepinace[POCET_JAZYKOV + 1] =
{
	"možnosti pre výsledné modlitby",
	"možnosti pro výsledné modlitby",
	"options for generated prayers",
	"possibilitates pro Officium finale",
	"",
	"možnosti pro výsledné modlitby",
	"egyéb választási lehetőségek:",
	"ru_text",
	"опцыі для генераваных малітваў",
	"valmöguleika fyrir bænirnar sem afleiddar eru",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// for other language: use ""
const char* html_text_opt_1_dalsie_prepinace_explain[POCET_JAZYKOV + 1] =
{
	"Rozličné možnosti/výbery pre výsledné modlitby.",
	"",
	"",
	"Possibilitates variæ pro Officium finale.",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_zalmy_brat_zo[POCET_JAZYKOV + 1] =
{
	"žalmy použiť zo ",
	"žalmy použít ze ",
	"take psalmody from ",
	"psalmodia secundum ",
	"",
	"žalmy použít ze ",
	"zsoltárok a következő helyről: ",
	"ru_text",
	"узяць псальмодыю з ",
	"nota sálma ",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_zalmy_brat_zo_okrem_mcd[POCET_JAZYKOV + 1] =
{
	" (okrem modlitby cez deň)\n",
	" (kromě modlitby uprostřed dne)\n",
	" (excluding the prayers during the day)\n",
	" (præter horam mediam)\n",
	"",
	" (kromě modlitby během dne)\n",
	" (a Napközi imát kivéve)\n",
	"ru_text",
	"by_text",
	" (nema miðdegisbæn)",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_spol_casti_vziat_zo[POCET_JAZYKOV + 1] =
{
	"časti modlitby zo spoločnej časti ",
	"části modlitby ze společných textů ",
	"parts of prayer from the common part ",
	"partes orationis de communæ",
	"",
	"části modlitby ze společné části ",
	"a közös részből",
	"ru_text",
	"часткі малітвы з агульнай часткі ",
	"hluti bænanna frá almennum textum",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_spol_casti_vziat_zo_explain[POCET_JAZYKOV + 1] =
{
	"Na sviatok svätca/svätice sa podľa liturgických pravidiel berú časti, ktoré sa nenachádzajú vo vlastnej časti žaltára, zo spoločnej časti sviatku, niekedy je možnosť vybrať si z viacerých spoločných častí; naviac je možnosť modliť sa tieto časti zo všedného dňa.",
	"Na svátek ke cti světce/světice se podle liturgických pravidel berou části, které se nenachází ve vlastních textech, ze společných textů, někdy je možné vybrat si z více společných textů; navíc je možnost modlit se tyto části ze všedního dne.",
	"",
	"In festis sanctorum partes Officii, quæ in Propria absunt, ex Commune festo sumuntur, aliquando et ex pluribus Communis delegi possunt; item hæ partes e feria sumi possunt",
	"",
	"O svátku ke cti světce/světice se podle liturgických pravidel berou části, které se nenachází ve vlastních textech, ze společných textů, někdy je možné vybrat si z více společných textů; navíc je možnost modlit se tyto části ze všedního dne.",
	"A szentek ünnepén, a liturgikus előírások szerint, azok az imarészek, amelyek nem találhatók meg a zsolozsma saját részében, tetszés szerint vehetők vagy a közös részből, néha több közös részből lehet választani, vagy a köznapról.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_specialne[POCET_JAZYKOV + 1] =
{
	"v texte modlitieb zobraziť",
	"v textu modliteb zobrazit",
	"in the text of prayers display",
	"in textu orationis ostende",
	"",
	"v textu modliteb zobrazit",
	"az imaóra szövegében jelenjen meg:",
	"ru_text",
	"паказваць у тэксце малітваў",
	"birta í texta bænanna",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// for other languages use: ""
const char* html_text_opt_0_specialne_explain[POCET_JAZYKOV + 1] =
{
	"Možnosť zobraziť ďalšie údaje v texte modlitieb (číslovanie veršov, referencie a pod.).",
	"",
	"",
	"Possibilitas nuntiationes ceteræ in textu Officii ostende (numeratio versorum, etc.).",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_verse[POCET_JAZYKOV + 1] =
{
	"číslovanie veršov",
	"číslování veršů",
	"verse numbering",
	"numeratio versorum",
	"",
	"číslování veršů",
	"a versek száma",
	"ru_text",
	"нумерацыя вершаў",
	"tölusetning versa",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_verse_explain[POCET_JAZYKOV + 1] =
{
	"Liturgia hodín (latinské typické vydanie) zobrazuje číslovanie veršov v rámci žalmu, chválospevu alebo dlhšieho biblického čítania; niektoré vydania tieto čísla veršov neuvádzajú.",
	"Liturgie hodin uvádí jako horní indexy čísla veršů biblických textů (žalmů, chvalozpěvů a prvních čtení), které může program zobrazit.",
	"Printed editions of Liturgy of the Hours shows also verse numbers (in psalms, canticles and long biblical readings). This option forces to display them.",
	"In Liturgia horarum (editio typica) numeratio psalmorum inscriptum est in psalmis, canticis, vel longiore lectione; in editionibus aliquibus numerationem hac non continent.",
	"",
	"Liturgie hodin uvádí jako horní indexy čísla veršů biblických textů (žalmů, chvalozpěvů a prvních čtení), které může program zobrazit.",
	"Az imaórák liturgiája (latin tipikus kiadás) megjeleníti a zsoltárokban, kantikumokban és hosszabb szentírási olvasmányokban a versek számozását. Egyes kiadások e számozást nem tartalmazzák.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_referencie[POCET_JAZYKOV + 1] =
{
	"biblické odkazy na dkc.kbs.sk",
	"biblické odkazy",
	"biblical references",
	"indices biblicæ",
	"",
	"biblické odkazy",
	"Bibliai hivatkozások a szentiras.hu oldalon",
	"ru_text",
	"біблійныя спасылкі",
	"Biblíutenglar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_referencie_explain[POCET_JAZYKOV + 1] =
{
	"Všetky biblické odkazy (napr. Jn 3, 16) v modlitbe budú aktívnymi odkazmi na text katolíckeho prekladu Biblie na adrese dkc.kbs.sk.",
	"",
	"",
	"Omnes indices biblicæ (e.g. Io 3, 16) in Officio electronica sunt nexus ad Novam Vulgatam apud URL vatican.va.",
	"",
	"",
	"Az imák szövegében minden bibliai utalás (például Jn 3, 16) aktív linkként a szentiras.hu katolikus bibliafordításának megfelelő részére mutat. (A Szent István Társulat fordítását használjuk.)",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_ref_bible_com[POCET_JAZYKOV + 1] =
{
	"biblické odkazy na bible.com",
	"biblické odkazy na bible.com",
	"biblical references to bible.com",
	"indices biblicæ ad bible.com",
	"",
	"biblické odkazy na bible.com",
	"Bibliai hivatkozások a bible.com oldalon",
	"ru_text",
	"біблійныя спасылкі",
	"Biblíutenglar á bible.com",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_ref_bible_com_explain[POCET_JAZYKOV + 1] =
{
	"Všetky biblické odkazy (napr. Jn 3, 16) v modlitbe budú aktívnymi odkazmi na preklady Biblie na adrese bible.com.",
	"",
	"",
	"Omnes indices biblicæ (e.g. Io 3, 16) in Officio electronica sunt nexus ad Novam Vulgatam apud URL bible.com.",
	"",
	"",
	"Az imák szövegében minden bibliai utalás (például Jn 3, 16) aktív linkként a bible.com bibliafordításának megfelelő részére mutat.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_italics_cond[POCET_JAZYKOV + 1] =
{
	"niektoré texty (elízie) kurzívou",
	"některé texty (elize) kurzívou",
	"special texts (elisions) in italics",
	"elisiones in hymnis italice notantur",
	"",
	"některé texty (elize) kurzívou",
	"néhány szöveg (elizálva) dőlt betűvel",
	"ru_text",
	"by_text",
	"einhverjir textar (aukatextar) með skáletri",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_italics_cond_explain[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_printed_edition[POCET_JAZYKOV + 1] =
{
	"použiť texty podľa tlačeného vydania",
	"vzít texty podle tištěného vydání",
	"use texts according to printed edition",
	"la_text",
	"",
	"vzít texty podle tištěného vydání",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_printed_edition_explain[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_use_two_years_cycle[POCET_JAZYKOV + 1] =
{
	"použiť dvojročný cyklus pre posvätné čítanie (biblické čítania)",
	"vzít dvouroční cyklus pro modlitbu se čtením (biblická čtení)",
	"use two years cycle for prayer with readings (Biblical readings)",
	"la_text",
	"",
	"vzít dvouroční cyklus pro modlitbu se čtením (biblická čtení)",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_use_two_years_cycle_explain[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_two_years_cycle_id[POCET_JAZYKOV + 1] =
{
	"pre dvojročný cyklus vziať prvý resp. druhý rok",
	"pro dvouroční cyklus vzít první nebo druhý rok",
	"for two years cycle use first or second year",
	"",
	"",
	"pro dvouroční cyklus vzít první nebo druhý rok",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_two_years_cycle_id_explain[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_alternative_readings_NORMAL[POCET_JAZYKOV + 1] =
{
	"použiť štandardné čítania pre posvätné čítanie",
	"vzít standardní čtení pro modlitbu se čtením",
	"use standard readings for prayer with readings",
	"la_text",
	"",
	"vzít standardní čtení pro modlitbu se čtením",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_alternative_readings[POCET_JAZYKOV + 1] =
{
	"použiť alternatívne čítania pre posvätné čítanie",
	"vzít alternativní čtení pro modlitbu se čtením",
	"use alternative readings for prayer with readings",
	"la_text",
	"",
	"vzít alternativní čtení pro modlitbu se čtením",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_alternative_readings_explain[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_citania[POCET_JAZYKOV + 1] =
{
	"čítania v omši",
	"mešní čtení",
	"mass readings",
	"lectiones missæ",
	"",
	"mešní čtení",
	"liturgikus olvasmányok",
	"ru_text",
	"літургічныя чытанні",
	"messulestrar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_citania_explain[POCET_JAZYKOV + 1] =
{
	"Zobrazí odkaz na čítania v omši (lc.kbs.sk).",
	"Zobrazí odkaz na mešní čtení (katolik.cz).",
	"",
	"Ostendit nexum ad lectiones missæ.",
	"",
	"Zobrazí odkaz na mešní čtení (katolik.cz).",
	"Liturgikus olvasmányok (katolikus.hu).",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_zjv_ne[POCET_JAZYKOV + 1] =
{
	"Zjavenie Pána sláviť v nedeľu medzi 2. a 8. januárom",
	"Zjevení Páně slavit v neděli mezi 2. a 8. lednem",
	"celebrate Epiphany on Sunday between Jan 2nd & 8th",
	"Epiphaniam ad dominicam transferre",
	"",
	"Zjevení Páně slavit v neděli mezi 2. a 8. lednem",
	"Urunk megjelenése (Vízkereszt) megünneplése vasárnap, január 2. és 8. között",
	"ru_text",
	"адзначаць Аб'яўленне Пана ў нядзелю паміж 2 і 8 студзеня",
	"Hátíð Birtingar Drottins skal halda á sunnudegi á milli 2. og 8. janúar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_zjv_ne_explain[POCET_JAZYKOV + 1] =
{
	"Zjavenie Pána sa slávi dňa 6. januára; v niektorých krajinách sa slávi v nedeľu medzi 2. a 8. januárom.",
	"",
	"",
	"Epiphania Domini celebratur die 6 ianuarii; in aliquibus regionibus ea celebratur dominica a die 2 ad diem 8 ianuarii occurrente.",
	"",
	"",
	"Urunk megjelenése (Vízkereszt) január 6-án van; egyes országokban azonban vasárnap, január 2. és 8. között ünneplik.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_nan_ne[POCET_JAZYKOV + 1] =
{
	"Nanebovstúpenie Pána sláviť v nedeľu",
	"Nanebevstoupení Páně slavit v neděli",
	"celebrate Ascension of the Lord on Sunday",
	"Ascensionem Domini ad dominicam transferre",
	"",
	"Nanebevstoupení Páně slavit v neděli",
	"Urunk mennybemenetelét vasárnap ünnepelni",
	"ru_text",
	"адзначаць Унебаўшэсце Пана ў нядзелю",
	"Hátíð Uppstigningar Drottins skal halda á sunnudegi",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_nan_ne_explain[POCET_JAZYKOV + 1] =
{
	"Nanebovstúpenie Pána sa slávi 40. deň po Veľkej noci (teda vo štvrtok); v niektorých krajinách sa slávenie prekladá na najbližšiu nedeľu (nahrádza 7. veľkonočnú nedeľu).",
	"",
	"",
	"Ascensio Domini celebratur die XL post Pascham (ergo feria V); in aliquibus regionibus ea transfertur ad dominicam sequentem (dominica VII Paschæ).",
	"",
	"",
	"Urunk mennybemenetele húsvét után a 40. napon van (tehát csütörtökön); egyes országokban azonban a legközelebbi vasárnapon ünneplik (vagyis Húsvét 7. vasárnapján).",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_tk_ne[POCET_JAZYKOV + 1] =
{
	"Najsv. Kristovho tela a krvi sláviť v nedeľu",
	"Těla a krve Páně slavit v neděli",
	"celebrate The Most Holy Body and Blood of Christ on Sunday",
	"Ss.mi Corporis et Sanguinis Christi ad dominicam transferre",
	"",
	"Těla a krve Páně slavit v neděli",
	"Krisztus Szent Teste és Vére ünnepe vasárnapra téve",
	"ru_text",
	"адзначаць Божае Цела ў нядзелю",
	"Dýradag, Stórhátíð Líkama og blóðs Krists skal halda á sunnudegi",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_tk_ne_explain[POCET_JAZYKOV + 1] =
{
	"Najsv. Kristovho tela a krvi sa slávi 11. deň po Zoslaní Ducha Svätého (teda vo štvrtok po Najsv. Trojici); v niektorých krajinách sa slávenie prekladá na najbližšiu nedeľu.",
	"",
	"",
	"Ss.mi Corporis et Sanguinis Christi celebratur feria V post Ss.mam Trinitatem; in aliquibus regionibus hæc celebratio transfertur ad dominicam sequentem.",
	"",
	"",
	"Krisztus Szent Teste és Vére Pünkösd után a 11. napon van (tehát Szentháromság utáni csütörtökön); egyes országokban azonban a legközelebbi vasárnapon ünneplik.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_font_normal[POCET_JAZYKOV + 1] =
{
	"všade použiť obyčajné písmo (nie tučné)",
	"všude použít obyčejné písmo (ne tučné)",
	"force normal font weight (no bold)",
	"ostende ubique litteras formæ normalis (non crassas)",
	"",
	"všude použít obyčejné písmo (ne tučné)",
	"normál betűtípus használata (félkövér helyett)",
	"ru_text",
	"зрабіць шрыфт нармальным (не тоўстым)",
	"allstaðar skal nota venjulegt letur (ekki feitt letur)",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// for other languages use: ""
const char* html_text_opt_0_font_normal_explain[POCET_JAZYKOV + 1] =
{
	"Liturgia hodín používa tučné písmo pre texty, ktoré sa priamo čítajú, a tiež aj pre niektoré medzinadpisy. Táto voľba potlačí použitie tučného písma.",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_buttons_order[POCET_JAZYKOV + 1] =
{
	"dátumové navigačné tlačidlá pod tlačidlami pre modlitby",
	"navigační tlačítka pro datum pod tlačítky pro modlitby",
	"date buttons after buttons for prayers",
	"pulsabulas navigatorias sub pulsabulis pro orationes",
	"",
	"navigační tlačítka pro datum pod tlačítky pro modlitby",
	"a fejlécben a dátumválasztó gombok legyenek az imaóra választó gombok után",
	"ru_text",
	"кнопкі з датай пасля кнопак з малітвамі",
	"dagsetninga- og bendihnappa eru undir hnöppum fyrir bænir",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// for other languages use: ""
const char* html_text_opt_0_buttons_order_explain[POCET_JAZYKOV + 1] =
{
	"Štandardne sa dátumové navigačné tlačidlá (deň dozadu, deň dopredu a pod.) zobrazujú prvé, pod nimi sú zobrazené tlačidlá pre modlitby jednotlivých slávení. Toto nastavenie spôsobí presunutie navigačných tlačidiel až pod tlačidlami pre modlitby.",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_voice_output[POCET_JAZYKOV + 1] =
{
	"iba text modlitieb pre hlasový výstup",
	"jenom text modliteb pro hlasový výstup",
	"only text for voice output",
	"solum textum orationum, pro exitu vocale",
	"",
	"jenom text modliteb pro hlasový výstup",
	"csak szöveg a hangkimenethez",
	"ru_text",
	"тэкст для невідушчых(без рубрык), для пераводу ў аўдыё",
	"bara bænatextar fyrir raddúttak",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// for other languages use: ""
const char* html_text_opt_0_voice_output_explain[POCET_JAZYKOV + 1] =
{
	"Vo výslednej modlitbe bude zobrazený len ten text, ktorý sa číta; nebudú zobrazené žiadne rubriky alebo názvy častí modlitieb. Toto je vhodné pre hlasový výstup napr. pre nevidiacich a slabozrakých.",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_footnotes[POCET_JAZYKOV + 1] =
{
	"poznámky (v texte, pod čiarou)",
	"poznámky (v textu, pod čarou)",
	"notes and footnotes",
	"notas (in textu, sub lineam)",
	"",
	"poznámky (v textu, pod čarou)",
	"jegyzetek, lábjegyzetek",
	"ru_text",
	"паказваць зноскі",
	"glósur (í texta, undirstrikað)",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// for other languages use: ""
const char* html_text_opt_0_footnotes_explain[POCET_JAZYKOV + 1] =
{
	"Vo výslednej modlitbe (najmä posvätné čítania) budú zobrazené aj poznámky (v texte resp. pod čiarou vrátane odkazov na ne).",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_transparent_nav[POCET_JAZYKOV + 1] =
{
	"zobraziť navigačné šípky (vpravo)",
	"zobrazit navigační šipky (vpravo)",
	"show navigation arrows (on the right)",
	"ostende sagittas navigationis (in dextro)",
	"",
	"zobrazit navigační šipky (vpravo)",
	"navigációs nyilak mutatása (jobb oldalon)",
	"ru_text",
	"паказваць стрэлкі навігацыі",
	"sýna leiðsöguörvar (hægra megin)",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// for other languages use: ""
const char* html_text_opt_0_transparent_nav_explain[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_transparent_nav_left[POCET_JAZYKOV + 1] =
{
	"navigačné šípky vľavo",
	"navigační šipky nalevo",
	"navigation arrows on the left",
	"pharetra sagittis a sinistris",
	"",
	"navigační šipky nalevo",
	"navigációs nyilak a bal oldalon",
	"ru_text",
	"паказваць стрэлкі навігацыі",
	"leiðsöguörvar til vinstri",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// for other languages use: ""
const char* html_text_opt_0_transparent_nav_explain_left[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_0_zalmy_full_text[POCET_JAZYKOV + 1] =
{
	"vynechané pasáže zo žalmov a chválospevov",
	"vynechávky ze žalmů a kantik",
	"psalms and canticles omissions",
	"partes omissas psalmorum",
	"",
	"vynechávky ze žalmů a kantik",
	"a zsoltárok kihagyott részeit",
	"ru_text",
	"пропускі ў псальмах",
	"undanteknir þættir frá sálmum og lofsöngvum",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// for other languages use: ""
const char* html_text_opt_0_zalmy_full_text_explain[POCET_JAZYKOV + 1] =
{
	"Liturgia hodín vynecháva niektoré pasáže zo žalmov a chválospevov (napr. verš 6 v žalme 110). Je možné tieto vynechané pasáže zobraziť.",
	"",
	"Liturgy of hours omits parts of some psalms and canticles (e. g. Ps 110, verse 6). It is possible to show also these omissions.",
	"In Liturgia horarum omittuntur aliquæ partes psalmorum (e.g. versus 6 in psalmo 110 (109)). Has partes ostendi possunt.",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_chvalospevy[POCET_JAZYKOV + 1] =
{
	"evanjeliové chválospevy (Benediktus, Magnifikat, Nunk dimittis)",
	"evangelijní kantika (Mariino, Zachariášovo, Simeonovo)",
	"Gospel canticles (Benedictus, Magnificat, Nunc dimittis)",
	"cantica evangelica (Benedictus, Magnificat, Nunc dimittis)",
	"",
	"evangelijní chvalozpěvy (Benedictus, Magnificat, Nunc dimittis)",
	"evangéliumi kantikumok (Benedictus, Magnificat, Nunc dimittis)",
	"ru_text",
	"евангельскія песні (Benedictus, Magnificat, Nunc dimittis)",
	"guðspjalla lofsöngvar (Benedictus, Magnificat, Nunc dimittis)",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_chvalospevy_explain[POCET_JAZYKOV + 1] =
{
	"Liturgia hodín štandardne tieto evanjeliové chválospevy neuvádza.",
	"Liturgie hodin evangelijní kantika v plném znění obvykle neuvádí.",
	"en_text",
	"In Liturgia horarum hæc cantica evangelica usitate non indicatur.",
	"",
	"Liturgie hodin evangelijní chvalozpěvy v plném znění obvykle neuvádí.",
	"Az imaórák liturgiája ezeket az evangéliumi kantikumokat alaphelyzetben nem mutatja.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_slava_otcu[POCET_JAZYKOV + 1] =
{
	"Sláva Otcu", // [na konci žalmov a chválospevov]
	"Sláva Otci", // [na konci žalmů a kantik]
	"Glory to the Father", // at the end of psalms and canticles]
	"Gloria Patri",
	"",
	"Sláva Otci", // [na konci žalmů a chvalozpěvů]
	"Dicsőség az Atyának", // [a zsoltárok és kantikumok végén]
	"ru_text",
	"Хвала Айцу",
	"Lofgerðarbæn",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_slava_otcu_explain[POCET_JAZYKOV + 1] =
{
	"Liturgia hodín štandardne Sláva Otcu na konci žalmov a chválospevov neuvádza.",
	"Liturgie hodin modlitbu Sláva Otci na konci žalmů a chvalozpěvů neuvádí.",
	"",
	"In Liturgia horarum Gloria Patri in fine psalmorum et canticorum usitate non indicatur.",
	"",
	"Liturgie hodin modlitbu Sláva Otci na konci žalmů a chvalozpěvů neuvádí.",
	"Az imaórák liturgiája a Dicsőség az Atyának… dicsőítő verset a zsoltárok és kantikumok végén alaphelyzetben nem mutatja.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_rubriky[POCET_JAZYKOV + 1] =
{
	"rubriky", // (napr. záverečné požehnanie)
	"rubriky", // (např. závěrečné požehnání)
	"rubrics",
	"rubricas",
	"",
	"rubriky", // (např. závěrečné požehnání)
	"rubrikák", // (pl. záró áldás)
	"ru_text",
	"рубрыкі",
	"bænareglur",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_rubriky_explain[POCET_JAZYKOV + 1] =
{
	"Liturgia hodín zobrazuje červeným písmom rozličné zvyčajne vysvetľujúce pokyny k modlitbe (podľa Všeobecných smerníc o LH).",
	"Liturgie hodin uvádí červeným písmem rozličné pokyny k modlitbě (často podle Všeobecných pokynů k denní modlitbě církve).",
	"en_text",
	"In Liturgia horarum describuntur usitate textus interpretationis ad Officium (secundum Institutionem generalem de Liturgia Horarum).",
	"",
	"Liturgie hodin uvádí červeným písmem rozličné pokyny k modlitbě (často podle Všeobecných pokynů k denní modlitbě církve).",
	"Az imaórák liturgiája piros betűvel különböző többnyire magyarázó vagy az imaórát (az „Általános rendelkezések Az imaórák liturgiájáról“ szerint) szabályozó szövegeket jelenít meg. Alaphelyzetben nem mutatja.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_otcenas[POCET_JAZYKOV + 1] =
{
	"modlitba Pána (Otčenáš)",
	"modlitba Páně (Otčenáš)",
	"Lord's Prayer (Our Father)",
	"Pater noster",
	"",
	"modlitba Páně (Otčenáš)",
	"az Úr imádsága (Miatyánk)",
	"ru_text",
	"малітва Панская (Ойча наш)",
	"Drottinleg bæn (Faðirvorið)",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_otcenas_explain[POCET_JAZYKOV + 1] =
{
	"Liturgia hodín štandardne modlitbu Pána (Otčenáš) v ranných chválach a vešperách v plnom znení neuvádza.",
	"Liturgie hodin modlitbu Páně (Otčenáš) na příslušných místech v plném znění neuvádí.",
	"en_text",
	"In Liturgia horarum versio integra orationis dominicæ in Laudibus et Vesperis usitate non indicatur.",
	"",
	"Liturgie hodin modlitbu Páně (Otčenáš) na příslušných místech v plném znění neuvádí.",
	"Az imaórák liturgiája az Úr imádságát (Miatyánkot) a Reggeli és Esti dicséretben alaphelyzetben nem mutatja.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_tedeum[POCET_JAZYKOV + 1] =
{
	"hymnus Te Deum",
	"hymnus Te Deum",
	"hymnus Te Deum",
	"hymnus Te Deum",
	"",
	"hymnus Te Deum",
	"Téged, Isten, dicsérünk… himnusz",
	"ru_text",
	"гімн Цябе, Бога, праслаўляем",
	"hymni Drottinn Guð",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_tedeum_explain[POCET_JAZYKOV + 1] =
{
	"Liturgia hodín hymnus Te Deum v posvätnom čítaní v plnom znení neuvádza.",
	"Liturgie hodin hymnus Te Deum na příslušných místech v plném znění neuvádí.",
	"en_text",
	"In Liturgia horarum versio integra hymni Te Deum in Officio lectionis non indicatur.",
	"",
	"Liturgie hodin hymnus Te Deum na příslušných místech v plném znění neuvádí.",
	"Az imaórák liturgiája a Téged, Isten, dicsérünk… himnuszt az Olvasmányos imaórában alaphelyzetben nem mutatja.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_plne_resp[POCET_JAZYKOV + 1] =
{
	"plné znenie responzórií",
	"plné znění krátkých zpěvů",
	"full version of short responsories",
	"versionem integram responsoriorum brevium",
	"",
	"plné znění responsorií",
	"a válaszos énekek teljes szövege",
	"ru_text",
	"поўная версія кароткіх рэспансорыяў",
	"óstytt svarvers",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_plne_resp_explain[POCET_JAZYKOV + 1] =
{
	"Liturgia hodín responzóriá po krátkom čítaní v ranných chválach, vešperách a po čítaniach v posvätnom čítaní v plnom znení neuvádza.",
	"Liturgie hodin responsoria po krátkém čtení v ranních chválách, nešporách a po čteních v modlitbe se čtením neuvádí plné znění.",
	"en_text",
	"In Liturgia horarum versio integra responsoriorum post lectionem brevem in Laudibus et Vesperis et post lectiones in Officio lectionis non indicatur.",
	"",
	"Liturgie hodin responsoria po krátkém čtení v ranních a večerních chválách a po čteních v modlitbe se čtením neuvádí plné znění.",
	"Az Imaórák Liturgiája a válaszos énekeket a reggeli és esti dicséret rövid olvasmánya és az olvasmányos imaóra olvasmányai után nem mutatja teljes formában.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_option_zobrazit[POCET_JAZYKOV + 1] =
{
	"zobraziť",
	"zobrazit",
	"show",
	"ostende",
	"",
	"zobrazit",
	"megjelenítés: ",
	"показ",
	"паказаць",
	"að sýna",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

#define HTML_TEXT_HU_OPTION_ZOBRAZIT "a teljes szöveg megjelenítése"

const char* html_text_option_skryt[POCET_JAZYKOV + 1] =
{
	"skryť",
	"skrýt",
	"hide",
	"abscondere",
	"",
	"skrýt",
	"elrejtés: ",
	"скрывать",
	"схаваць",
	"að fela",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

#define HTML_TEXT_HU_OPTION_SKRYT "a szöveg elrejtése"

const char* html_text_option_pouzit[POCET_JAZYKOV + 1] =
{
	"použiť",
	"použít",
	"use",
	"sumere",
	"",
	"použít",
	"használat",
	"ru_text",
	"выкарыстаць",
	"að nota",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_mcd_zalmy_nie_ine_short[POCET_JAZYKOV + 1] =
{
	"použiť psalmódiu zo dňa",
	"použít žalmy z běžného dne",
	"psalmodia from ordinary day",
	"psalmodiam de feria sumere",
	"",
	"použít psalmodii z běžného dne",
	"zsoltárok a soros köznapról",
	"ru_text",
	"псальмодыя з дня",
	"nota sálmasöngva dagsins",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_mcd_zalmy_nie_ine[POCET_JAZYKOV + 1] =
{
	"pre modlitbu cez deň použiť psalmódiu zo dňa",
	"pro modlitbu uprostřed dne použít žalmy z běžného dne",
	"psalmodia from ordinary day",
	"ad Horam mediam psalmodiam de feria sumere",
	"",
	"pro modlitbu během dne použít psalmodii z běžného dne",
	"a Napközi imaórában zsoltárok a soros köznapról",
	"ru_text",
	"by_text",
	"fyrir miðdegisbæn skal nota sálma dagsins",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_mcd_zalmy_ine_short[POCET_JAZYKOV + 1] =
{
	"použiť doplnkovú psalmódiu",
	"použít žalmy z doplňovacího cyklu",
	"supplementary psalmodia",
	"psalmodiam complementarem sumere",
	"",
	"použít doplňkovou psalmodii",
	"kiegészítő zsoltárok",
	"ru_text",
	"дадатковая псальмодыя",
	"nota viðbótarsálmasöngva",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_mcd_zalmy_ine[POCET_JAZYKOV + 1] =
{
	"pre modlitbu cez deň použiť doplnkovú psalmódiu",
	"pro modlitbu uprostřed dne použít žalmy z doplňovacího cyklu",
	"supplementary psalmodia",
	"ad Horam mediam psalmodiam complementarem sumere",
	"",
	"pro modlitbu během dne použít doplňkovou psalmodii",
	"vegye a napközi imaórákban a kiegészítő zsoltárokat",
	"ru_text",
	"by_text",
	"fyrir miðdegisbæn skal nota aukasálma",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_mcd_zalmy_ine_explain[POCET_JAZYKOV + 1] =
{
	"Pokiaľ sa niekto modlí viac modlitieb cez deň, v prvej vezme bežnú psalmódiu; v ostatných sa použije doplnková psalmódia. Zahŕňa 3 série tzv. graduálnych žalmov (Ž 120 – 129).",
	"Doplňovací cyklus žalmů obsahuje 3 série tzv. graduálních žalmů (Ž 120 – 129), které je možno použít místo žalmů ze žaltáře.",
	"en_text",
	"Qui plures Horas dicit, in una Hora psalmodiam currentem sumat, in ceteris complementarem, quæ tenet tres series psalmorum gradualium.",
	"",
	"Doplňovací cyklus žalmů obsahuje 3 série tzv. graduálních žalmů (Ž 120 – 129), které je možno použít místo žalmů ze žaltáře.",
	"Aki több Napközi imaórát mond, az egyik imaórában a soros zsoltárösszeállítást veszi, a többin a kiegészítőt. Ez az úgynevezett „zarándokzsoltárokból“ vett három-három zsoltárból áll (Zsolt 119 – 127).",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_mcd_zalmy_nie_tri_short[POCET_JAZYKOV + 1] =
{
	"použiť psalmódiu z daného týždňa žaltára pre všetky tri modlitby cez deň",
	"použít žalmy daného týdne ze žaltáře pro všechny tři modlitby uprostřed dne",
	"en_text",
	"psalmodiam secundum hebdomadam Psalterii in omnibus tribus Horis mediis sumere",
	"",
	"použít psalmodii daného týdne ze žaltáře pro všechny tři modlitby během dne",
	"a soros köznap zsoltárainak használata mindhárom napközi imaórához",
	"ru_text",
	"by_text",
	"nota skal sálma frá ákveðinni viku fyrir allar þrjár miðdegisbænir",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_mcd_zalmy_nie_tri[POCET_JAZYKOV + 1] =
{
	"pre modlitbu cez deň použiť psalmódiu z daného týždňa žaltára pre všetky tri modlitby cez deň",
	"pro modlitbu uprostřed dne použít žalmy daného týdne ze žaltáře pro všechny tři modlitby uprostřed dne",
	"en_text",
	"ad Horam mediam psalmodiam psalmodiam secundum hebdomadam Psalterii in omnibus tribus Horis mediis sumere",
	"",
	"pro modlitbu uprostřed dne použít psalmodii daného týdne ze žaltáře pro všechny tři modlitby během dne",
	"a Napközi imaórában a soros köznap zsoltárainak használata mindhárom napközi imaórához",
	"ru_text",
	"by_text",
	"fyrir miðdegisbæn skal nota sálma frá ákveðinni viku saltara fyrir allar þrjár miðdegisbænir",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_mcd_zalmy_tri_short[POCET_JAZYKOV + 1] =
{
	"použiť psalmódiu z troch týždňov žaltára: aktuálny, predchádzajúci, nasledujúci",
	"použít žalmy z tří týdnů ze žaltáře: aktuální, předchozí, následující",
	"",
	"psalmodiam secundum tres hebdomadas Psalterii sumere: currentem, præcedentem, succedentem",
	"",
	"použít psalmodii z tří týdnů ze žaltáře: aktuální, předchozí, následující",
	"a három [aktuális, előző, következő] heti zsoltárok használata",
	"ru_text",
	"by_text",
	"nota sálma úr þremur vikum saltara: núverandi, undanfarandi, eftirkomandi",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_mcd_zalmy_tri[POCET_JAZYKOV + 1] =
{
	"pre modlitbu cez deň použiť psalmódiu z troch týždňov žaltára (aktuálny, predchádzajúci, nasledujúci)",
	"pro modlitbu uprostřed dne použít žalmy z tří týdnů ze žaltáře (aktuální, předchozí, následující)",
	"for prayer during the day use psalmody from three weeks of psalter (current, previous, next)",
	"ad Horam mediam psalmodiam secundum tres hebdomadas Psalterii sumere (currentem, præcedentem, succedentem)",
	"",
	"pro modlitbu během dne použít psalmodii z tří týdnů ze žaltáře (aktuální, předchozí, následující)",
	"a napközi imaórákban vegye az aktuális, az előző és a következő heti zsoltározást",
	"ru_text",
	"by_text",
	"fyrir miðdegisbæn skal nota sálma af þremur vikum saltara (núverandi, undanfarandi, eftirkomandi)",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_mcd_zalmy_tri_explain[POCET_JAZYKOV + 1] =
{
	"Pokiaľ sa niekto modlí viac modlitieb cez deň, psalmódia sa používa z troch týždňov žaltára (aktuálny, predchádzajúci, nasledujúci týždeň žaltára).\nNemá účinok, ak je zvolená možnosť použiť doplnkovú psalmódiu.",
	"Pokud se někdo modlí více částí modlitby uprostřed dne, může nejprve použít psalmodii daného dne a potom psalmodii předchozího, nebo následujícího týdne.",
	"en_text",
	"Si quis plus Horas minores persolvat, psalmodia sumitur ex tribus Hebdomadis Psalterii (currenti, præcedenti, succedenti).\nSi delectum est psalmodiam complementarem adhibere, nihil valet.",
	"",
	"Pokud se někdo modlí více částí modlitby během dne, může nejprve použít psalmodii daného dne a potom psalmodii předchozího, nebo následujícího týdne.",
	"Ha valaki többször naponta mondja a napközi imát, a zsoltározás három hétből (aktuális, előző, következő) van alkalmazva.\nNincs hatása, ha ki van választva a kiegészítő zsoltárok alkalmazása.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

#define HTML_TEXT_HU_OPTION1_ZAVER_SHOW "Az imaóra befejezésének megjelenítése"
#define HTML_TEXT_HU_OPTION1_ZAVER_HIDE "Az imaóra befejezésének elrejtése"

const char* html_text_opt_1_zaver[POCET_JAZYKOV + 1] =
{
	"zakončenie",
	"zakončení",
	"conclusion",
	"conclusionem",
	"",
	"zakončení",
	"befejezést",
	"ru_text",
	"завяршэнне",
	"bænalok",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_zaver_explain[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_maria_ant[POCET_JAZYKOV + 1] =
{
	"mariánske antifóny",
	"mariánské antifony",
	"Mary antiphones",
	"Antophonæ B. M. V.",
	"",
	"mariánské antifony",
	"hu_text",
	"ru_text",
	"завяршэнне",
	"Andstef Maríu meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_maria_ant_explain[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_otcenas_uvod[POCET_JAZYKOV + 1] =
{
	"úvod k modlitbe Pána",
	"úvod k modlitbě Páně",
	"intro to Our Father",
	"formula introductoria in orationem Dominicam",
	"",
	"úvod k modlitbě Páně",
	"bevezető a Miatyánkhoz",
	"",
	"by_text",
	"inngangur að bæn Drottins",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_otcenas_uvod_explain[POCET_JAZYKOV + 1] =
{
	"úvod k modlitbe Pána",
	"úvod k modlitbě Páně",
	"intro to Our Father",
	"formula introductoria in orationem Dominicam",
	"",
	"úvod k modlitbě Páně",
	"bevezető a Miatyánkhoz",
	"",
	"by_text",
	"inngangur að bæn Drottins",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_zalm95[POCET_JAZYKOV + 1] =
{
	"namiesto žalmov 24, 67 resp. 100 použiť žalm 95",
	"místo žalmů 24, 67 resp. 100 použít žalm 95",
	"psalm 95",
	"psalmos 100, 67, et 24 psalmo 95 substituere",
	"",
	"místo žalmů 24, 67 resp. 100 použít žalm 95",
	"a 23., 66. illetve a 99.  zsoltár helyett legyen a 94.",
	"ru_text",
	"псальм 95 (94)",
	"í stað sálma 24, 67 eða 100 skal nota sálm 95",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_zalm95_explain[POCET_JAZYKOV + 1] =
{
	"Ak sa v ranných chválach, vešperách alebo posvätnom čítaní vyskytne žalm 24, 67 resp. 100, ktorý bol použitý pre invitatórium, nahradí sa v príslušnej modlitbe žalmom 95.",
	"Když se v ranních chválách, modlitbě se čtením nebo nešporách vyskytne žalm 24, 67 resp. 100, který se použil pro uvedení do první modlitby dne, nahradí se v příslušné modlitbě žalmem 95.",
	"If morning prayer, vespers of prayer with readings contains psalms 24, 67, or 100, which was used for invitatory, it is replaced by psalm 95.",
	"Si in Vesperis, Laudibus vel Officio lectionis psalmus 23, vel 66, vel 99 adhibitus ad Invitatorium occurrit, eius loco dicitur psalmus 94.",
	"",
	"Když se v ranních chválách, modlitbě se čtením nebo večerních chválách vyskytne žalm 24, 67 resp. 100, který se použil pro invitatorium, nahradí se v příslušné modlitbě žalmem 95.",
	"Ha a reggeli és az esti dicséretben, vagy az olvasmányos imaórában előfordul a 23., 66. illetve 99. zsoltár, amely az Imádságra hívásban már imádkozva volt, akkor az adott imádságban a 94. zsoltár kerül helyébe.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// the names of the prayers, lowercase (sample text)
const char* html_text_invitatory_psalm_jazyk[4][POCET_JAZYKOV + 1] =
{
	{ "95", "95 (94)", "95", "95", "95", "94 (95)", "94.", "ru_text", "by_text", "95", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "100", "100 (99)", "100", "100", "100", "99 (100)", "99.", "ru_text", "by_text", "100", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "67", "67 (66)", "67", "67", "67", "66 (67)", "66.", "ru_text", "by_text", "67", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ "24", "24 (23)", "24", "24", "24", "23 (24)", "23.", "ru_text", "by_text", "24", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

#define		html_text_invitatory_psalm(a)	html_text_invitatory_psalm_jazyk[a][_global_jazyk]

const char* html_text_option_zobrazit_zvolania[POCET_JAZYKOV + 1] =
{
	"opakovať zvolanie po každej prosbe",
	"zopakovat zvolání po každé prosbě",
	"repeat invocation after each appeal",
	"responsum post quamque precem ostende",
	"",
	"zopakovat zvolání po každé prosbě",
	"a válasz megismétlése minden fohász után",
	"ru_text",
	"паўтараць заклік пасля кожнай просьбы",
	"endurtaka svar eftir hverja fyrirbæn",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_option_skryt_zvolania[POCET_JAZYKOV + 1] =
{
	"skryť zvolanie po každej prosbe",
	"skrýt zvolání po každé prosbě",
	"hide invocation after each appeal",
	"responsum post quamque precem abscondere",
	"",
	"skrýt zvolání po každé prosbě",
	"a válasz megjelenítése csak a rövid felszólítás után",
	"ru_text",
	"схаваць заклік пасля кожнай просьбы",
	"að fela svar eftir hverja fyrirbæn",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_option_zobrazit_kratsie_prosby[POCET_JAZYKOV + 1] =
{
	"použiť kratšie prosby z dodatku",
	"zobrazit kratší prosby z dodatku",
	"use shorten prayers",
	"intercessiones breviores ex appendice adhibere",
	"",
	"zobrazit kratší prosby z dodatku",
	"a rövidebb közbenjáró fohászok használata a függelékből",
	"ru_text",
	"выкарыстоўваць карацейшыя малітвы",
	"nota styttri fyrirbænir úr viðaukahluta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_option_skryt_kratsie_prosby[POCET_JAZYKOV + 1] =
{
	"nepoužiť kratšie prosby z dodatku",
	"nezobrazit kratší prosby z dodatku",
	"do not use shorten prayers",
	"intercessiones breviores ex appendice non adhibere",
	"",
	"nezobrazit kratší prosby z dodatku",
	"a hosszabb fohászok használata",
	"ru_text",
	"не выкарыстоўваць карацейшыя малітвы",
	"ekki nota styttri bænir úr viðaukahluta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_prosby_zvolanie[POCET_JAZYKOV + 1] =
{
	"zvolanie v prosbách opakovať po každej prosbe",
	"zvolání v prosbách zopakovat po každé prosbě",
	"repeat the invocation after each intercession",
	"in precibus responsum post quamque precem iterare",
	"",
	"zvolání v prosbách zopakovat po každé prosbě",
	"minden fohász után ismételje a választ",
	"ru_text",
	"паўтор закліка пасля кожнай просьбы",
	"ákall í fyrirbænum endurtekið eftir hverja fyrirbæn",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_prosby_zvolanie_explain[POCET_JAZYKOV + 1] =
{
	"V ranných chválach a vešperách opakovať zvolanie v prosbách po každej prosbe.",
	"V ranních chválách a nešporách opakovat svolání v prosbách po každé prosbě.",
	"In morning and evening prayer repeat the invocation after each intercession.",
	"In Laudibus et Vesperis responsum post quamque precem iterare.",
	"",
	"V ranních a večerních chválách opakovat svolání v prosbách po každé prosbě.",
	"A reggeli és az esti dicséretben minden fohász után ismételni a választ.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_skryt_popis_svaty[POCET_JAZYKOV + 1] =
{
	"nezobraziť popis k modlitbe svätého",
	"nezobrazit popis při modlitbě ke cti světce",
	"do not display description for prayer for the saints",
	"non ostendere commentarium historicum",
	"",
	"nezobrazit popis při modlitbě ke cti světce",
	"ne mutassa a leírást a szentről az imaórában",
	"ru_text",
	"не паказваць інфармацыю пра святых",
	"ekki sýna lýsingu til bænar heilags manns",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_skryt_popis_svaty_explain[POCET_JAZYKOV + 1] =
{
	"Modlitby zväčša obsahujú pred názvom modlitby životopis svätého, popis sviatku alebo podobnú stručnú charakteristiku, ktorú pre jednoduchosť nazývame popis.",
	"Modlitby ke cti svatých obsahují stručný životopis svatého, při svátku je to stručný popis svátku a podobně. Tyto charakteristiky pro stručnost nazýváme popis.",
	"For saints, rubrics usually contains few sentences about that saint (or celebration). This option forces to display this description.",
	"",
	"",
	"Modlitby ke cti svatých obsahují stručný životopis svatého, u svátku je to stručný popis svátku a podobně. Tyto charakteristiky pro stručnost nazýváme popis.",
	"Többnyire az imák az imaóra elnevezése előtt a szent életrajzát, az ünnep leírását vagy más rövid jegyzetet tartalmaznak, amit az egyszerűség kedvéért leírásnak nevezünk.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_spolc_svaty[POCET_JAZYKOV + 1] =
{
	"spoločné časti k modlitbe svätého",
	"společné texty pro světce",
	"display communia info",
	"communia pro Officium sanctorum",
	"",
	"společné texty pro světce",
	"mutassa meg, hogy a közös részek honnan lettek véve a szentek zsolozsmájához",
	"ru_text",
	"паказваць інфармацыю пра агульныя тэксты пра святых",
	"almennir hlutir til bænar heilags manns",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_spolc_svaty_explain[POCET_JAZYKOV + 1] =
{
	"Rubrika obsahujúca informáciu, odkiaľ sa berú spoločné časti k modlitbe svätého.",
	"Rubrika, která pro modlitby svatých informuje, které společné texty jsou užity.",
	"Displays communia info.",
	"Rubrica informans, quæ Communia sumantur pro Officium sanctis.",
	"",
	"Rubrika, která pro modlitby svatých informuje, které společné texty jsou užity.",
	"Rubrika, amely azt az információt tartalmazza, hogy melyik közös részből vannak véve a szentek zsolozsmájához tartozó közös részek.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_vesp_kratsie_prosby[POCET_JAZYKOV + 1] =
{
	"pre vešpery použiť kratšie prosby z dodatku",
	"pro nešpory použít kratší prosby z dodatku",
	"use shorten prayers for vespers",
	"ad Vesperas intercessiones breviores ex appendice adhibere",
	"",
	"pro večerní chvály použít kratší prosby z dodatku",
	"Esti dicséretben használja a függelékből a rövidebb, közbenjáró fohászokat",
	"ru_text",
	"выкарыстоўваць карацейшыя малітвы ў Нешпарах",
	"fyrir aftansöng eru notaðar styttri fyrirbænir úr viðauka",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_vesp_kratsie_prosby_explain[POCET_JAZYKOV + 1] =
{
	"Pre vešpery použiť kratšie prosby z dodatku namiesto tých, ktoré sú určené pre vešpery daného dňa.",
	"Pro nešpory použít kratší prosby z dodatku místo určených pro příslušný den.",
	"Use shorten prayers for vespers instead of those prescribed for the day.",
	"Ad Vesperas incercessiones breviores ex appendice adhibere pro destinatis ad vesperas diei.",
	"",
	"Pro večerní chvály použít kratší prosby z dodatku místo určených pro příslušný den.",
	"Esti dicséretben használja a rövidebb közbenjáró fohászokat a függelékből, a napra meghatározott helyett.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_vigilia[POCET_JAZYKOV + 1] =
{
	"predĺžené slávenie vigílie pre posvätné čítanie", //(na nedele, slávnosti a sviatky)
	"prodloužené slavení vigilie pro modlitbu se čtením", // (pro neděle, slavnosti a svátky)
	"celebrating of vigil for prayer with readings", // (for Sundays, solemnitas and festivus)
	"protractam celebrationem vigiliæ ad Officium lectionis",
	"",
	"prodloužené slavení vigilie pro modlitbu se čtením", // (pro neděle, slavnosti a svátky)
	"hosszabb vigíliás ünneplés Olvasmányos imaórával", // (vasárnap, főünnep és ünnep előtt)
	"ru_text",
	"цэлебрацыя вігіліі для Гадзіны чытанняў",
	"framlengt hátíðahald vigilíu fyrir Óttusöng hinn fyrri",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_vigilia_explain[POCET_JAZYKOV + 1] =
{
	"Tí, čo chcú podľa tradície predĺžiť vigíliu nedele, slávnosti alebo sviatku, čo sa veľmi odporúča, najprv recitujú posvätné čítanie; po oboch čítaniach, pred hymnom Te Deum, pridávajú sa chválospevy a evanjelium.",
	"Ti, kteří chtějí podle tradice prodloužit vigilii neděle, slavnosti nebo svátku, což se velmi doporučuje, recitují nejprve čtení; po obou čteních, před hymnem Te Deum, se přidávají chvalozpěvy a evangelium.",
	"For Sundays, solemnitas and festivus: celebrating of vigil for prayer with readings.",
	"Ii, qui celebrationem vigiliæ dominicalis, sollemnitatum et festorum protrahere, iuxta traditiam, cupiant, primo Officium lectionis celebretur; post vero ambas lectiones et ante Te Deum addantur cantica et Evangelium.",
	"",
	"Ti, kteří chtějí podle tradice prodloužit vigilii neděle, slavnosti nebo svátku, což se velmi doporučuje, recitují nejprve čtení; po obou čteních, před hymnem Te Deum, se přidávají chvalozpěvy a evangelium.",
	"Akik a hagyományokhoz híven vasárnap, főünnep és ünnep előtt hosszabb vigíliás ünneplést akarnak tartani, először végezzék el az Olvasmányos imaórát, a két olvasmány után és a Téged, Isten, dicsérünk himnusz előtt vegyék hozzá a kantikumokat és utána az evangéliumot.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_spomienka_spolcast[POCET_JAZYKOV + 1] =
{
	"na spomienky použiť časti zo spoločných častí",
	"na památky použít části ze společných textů",
	"take parts from celebration — commmons",
	"in memoriis partes Officii de Communi sumere",
	"",
	"na památky použít části ze společných částí",
	"emléknapon vegye a jelzett részeket a közös részből",
	"ru_text",
	"браць часткі з цэлебрацыі",
	"fyrir minningardaga er hægt að nota hluti frá almennum textum",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_spomienka_spolcast_explain[POCET_JAZYKOV + 1] =
{
	"Zvoliť, či sa antifóna na invitatórium, hymnus, krátke čítanie, antifóny na Benediktus a Magnifikat a prosby, ak nie sú vlastné, berú zo spoločnej časti (ináč z bežného všedného dňa); č. 235 b) všeobecných smerníc.",
	"",
	"",
	"",
	"",
	"",
	"Kiválasztani, hogy az imádságra hívás antifónája, himnusz, rövid olvasmány, a Benedictus és a Magnifikat antifónája és a fohászok a közös részből legyenek véve (egyébként a köznapról) a 235 b) általános rendelkezés szerint.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_spomienka_spolcast_NIE[POCET_JAZYKOV + 1] =
{
	"na spomienky použiť časti zo dňa, nie zo spoločných častí",
	"na památky použít části z běžného dne, ne ze společných textů",
	"take parts from feria — not commmons",
	"in memoriis partes Officii de feria, non de Communi, sumere",
	"",
	"na památky použít části z běžného dne, ne ze společných částí",
	"emléknapon a jelzett részeket az adott napról vegye, ne a közös részből",
	"ru_text",
	"браць часткі з дня",
	"fyrir minningardaga skal nota hluti af deginum, ekki frá almennum textum",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_override_stupen_slavenia[POCET_JAZYKOV + 1] =
{
	"sláviť s vyšším stupňom slávenia",
	"slavit s vyšším stupněm slavení",
	"celebrate with higher level",
	"gradu superiore celebrare",
	"",
	"slavit s vyšším stupněm slavení",
	"magasabb fokú ünneplést venni",
	"ru_text",
	"павысіць узровень цэлебрацыі",
	"halda með hærra stigi hátíðarhalds",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_override_stupen_slavenia_explain[POCET_JAZYKOV + 1] =
{
	"Možnosť sláviť (ľubovoľnú) spomienku ako sviatok alebo slávnosť, podobne možnosť sláviť sviatok ako slávnosť.",
	"Možnost slavit (nezávaznou) památku jako svátek nebo slavnost, resp. možnost slavit svátek jako slavnost.",
	"Possibility to celebrate (free) memory as a feast or a solemnity; likewise the possibility to celebrate the feast as a solemnity.",
	"Possibilitas memoriam (ad libitum) ut festum vel sollemnitas celebrare, sive festum ut sollemnitas celebrare.",
	"",
	"Možnost slavit (nezávaznou) památku jako svátek nebo slavnost, resp. možnost slavit svátek jako slavnost.",
	"Lehetséges a (tetszés szerinti) emléknapot, mint ünnepet vagy főünnepet venni, hasonlóan az ünnepet mint főünnepet venni (hejbéli ünnep/főünnep).",
	"ru_text",
	"Магчымасць цэлебраваць успамін як свята альбо ўрачыстасць; таксама магчымасць цэлебраваць свята як урачыстасць.",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_override_stupen_slavenia_NIE[POCET_JAZYKOV + 1] =
{
	"sláviť s predpísaným stupňom slávenia",
	"slavit s předepsaným stupněm slavení",
	"celebrate with prescribed liturgical level",
	"gradu præscripto celebrare",
	"",
	"slavit s předepsaným stupněm slavení",
	"az előírt fokú ünneplést venni",
	"ru_text",
	"цэлебраваць на прадпісанай літургічнай ступені",
	"halda með fyrirmæltu stigi hátíðarhalds",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_slavit_ako_sviatok[POCET_JAZYKOV + 1] =
{
	"sláviť ako sviatok",
	"slavit jako svátek",
	"celebrate as feast",
	"ut festum celebrare",
	"",
	"slavit jako svátek",
	"mint ünnepet venni",
	"ru_text",
	"цэлебраваць як свята",
	"halda eins og hátíð",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_1_slavit_ako_slavnost[POCET_JAZYKOV + 1] =
{
	"sláviť ako slávnosť",
	"slavit jako slavnost",
	"celebrate as solemnity",
	"ut sollemnitas celebrare",
	"",
	"slavit jako slavnost",
	"mint főünnepet venni",
	"ru_text",
	"цэлебраваць як урачыстасць",
	"halda eins og stórhátíð",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_html_export[POCET_JAZYKOV + 1] =
{
	"možnosti zobrazenia stránok",
	"možnosti zobrazení stránek",
	"display options",
	"possibilitates præsentationis paginarum",
	"",
	"možnosti zobrazení stránek",
	"az oldalak megjelenítésének lehetőségei:",
	"ru_text",
	"паказаць опцыі",
	"valmöguleikar fyrir birtingu síðunnar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_html_export_explain[POCET_JAZYKOV + 1] =
{
	"Tieto možnosti ovplyvnia rozličné zobrazenia, nemajú vplyv na obsah (text) modlitieb.",
	"Možnosti ovlivní rozličná zobrazení, neovlivní obsah (text) modliteb.",
	"These various options have no influence to content of generated prayer texts, they are used only for visualization.",
	"Hæ possibilitates ad aspectum, non quod continetur (textum) momentum habent.",
	"",
	"Možnosti ovlivní rozličná zobrazení, neovlivní obsah (text) modliteb.",
	"Ezek a beállítások hatással vannak a formai megjelenítésre, de az imaszöveg nem változik.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_prve_vespery[POCET_JAZYKOV + 1] =
{
	"tlačidlo pre prvé vešpery pre nedele a slávnosti v deň slávenia",
	"tlačítko pro první nešpory pro neděle a slavnosti v den slavení",
	"button for first vespers for Sundays and solemnitas for the day of celebration",
	"pulsabula pro I Vesperas dominicarum et sollemnitatum die celebrationis",
	"",
	"tlačítko pro první večerní chvály pro neděle a slavnosti v den slavení",
	"vasárnapok és főünnepek esetén az I. Esti dicséret gombja az ünneplés napján jelenjen meg",
	"ru_text",
	"кнопку з першымі Нешпарамі для нядзеляў і ўрачыстасцяў",
	"hnappur fyrir fyrsta aftansöng fyrir sunnudaga og stórhátíð á hátíðardeginum",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_prve_vespery_explain[POCET_JAZYKOV + 1] =
{
	"Keďže základným kritériom pre zobrazovanie modlitieb daného dňa je dátum, formálne prvé vešpery nedieľ a slávností (a tiež kompletórium po nich) nespadajú pod daný dátum, ale pre predošlý deň, kde sa zobrazujú ako bežné vešpery. Pre sobotné slávenie sa nebude tlačidlo pre vešpery (a kompletórium) zobrazovať.",
	"Jelikož základním kritériem pro zobrazování nabídky modliteb daného dne je datum, první nešpory neděl a slavností (a také kompletář po nich) nespadají pod dané datum, nýbrž pro předcházející den, kde jsou zobrazeny jako běžné nešpory. Pro sobotní slavení se tlačítko pro nešpory (a kompletář) nebude zobrazovat.",
	"For Sundays and solemnities, display also button for first vespers. (For Saturdays, vespers button will not be displayed.)",
	"Dominica, non sabbato pulsabula pro Vesperas I et Completorium non ostendetur.",
	"",
	"Jelikož základním kritériem pro zobrazování nabídky modliteb daného dne je datum, první večerní chvály neděl a slavností (a také kompletář po nich) nespadají pod dané datum, nýbrž pro předcházející den, kde jsou zobrazeny jako běžné první večerní chvály. Pro sobotní slavení se tlačítko pro večerní chvály (a kompletář) nebude zobrazovat.",
	"Mivel az imaórák megjelenítése elsősorban a dátumtól függ, a vasárnapok és főünnepek I. Esti dicsérete (valamint az utánuk következő Befejező imaóra) formálisan nem tartozik az adott dátumhoz, hanem az előző naphoz. Itt mint köznapi Esti dicséret jelenik meg. Az I. Esti dicséret (és Befejező imaóra) gombja nem fog megjelenni szombati végzéshez.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_iso_datum[POCET_JAZYKOV + 1] =
{
	"dátum v ISO 8601 formáte (RRRR-MM-DD)",
	"datum v ISO 8601 formátu (RRRR-MM-DD)",
	"date in ISO 8601 format (RRRR-MM-DD)",
	"datum in ISO 8601 (AAAA-MM-DD)",
	"",
	"datum v ISO 8601 formátu (RRRR-MM-DD)",
	"a dátum ISO 8601 formátumban (ÉÉÉÉ-HH-NN) jelenjen meg",
	"ru_text",
	"дату ў фармаце ISO 8601 (ГГГГ-ММ-ДД)",
	"ISO 8601 format (RRRR-MM-DD)",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// for any language: use ""
const char* html_text_opt_2_iso_datum_explain[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_font_family[POCET_JAZYKOV + 1] =
{
	"použiť bezpätkové písmo? (ináč pätkové)",
	"použít bezpatkové písmo? (jinak patkové)",
	"use Sans Serif font? (otherwise, Serif is used)",
	"ostende litteras forma computerica (aliud typis)",
	"",
	"použít bezpatkové písmo? (jinak patkové)",
	"talp nélküli betűk használata",
	"ru_text",
	"выкарыстоўваць шрыфт без засечак?",
	"nota leturgerð (aðra gerð)",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_font_family_explain[POCET_JAZYKOV + 1] =
{
	"Zvoľte si pätkové písmo (Serif) resp. bezpätkové písmo (Sans Serif) podľa toho, čo vám viac vyhovuje pre komfort modlitby. Použije sa predvolené písmo prehliadača.",
	"",
	"",
	"la_text",
	"",
	"",
	"Válasszon talpas (Serif) vagy talp nélküli (Sans Serif) betűt, kényelem szerint. A böngészőablakban mutatott betűtípus az alapértelmezett.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// accusative form or word 'navigation'
const char* html_text_navig_buttons[POCET_JAZYKOV + 1] =
{
	"navigáciu",
	"navigaci",
	"navigation buttons",
	"tabellam nexuum",
	"",
	"navigaci",
	"navigáció",
	"ru_text",
	"кнопкі навігацыі",
	"leiðsögn",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_navigation[POCET_JAZYKOV + 1] =
{
	"zobraziť navigáciu v textoch modlitieb",
	"zobrazit navigaci v textech modliteb",
	"display navigation buttons in prayer",
	"ostende navigationem in textibus orationum",
	"",
	"zobrazit navigaci v textech modliteb",
	"a navigáció mutatása az imaszövegben",
	"ru_text",
	"паказваць кнопкі навігацыі ў малітве",
	"að sýna leiðbeiningar í bænatextum",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_navigation_explain[POCET_JAZYKOV + 1] =
{
	"Či sa majú zobrazovať hypertextové odkazy na ostatné modlitby daného dňa, príp. predošlý/nasledovný deň priamo v texte modlitby.",
	"Zda zobrazit hypertextové odkazy na ostatní modlitby daného dne, resp. předešlý/následující den přímo v textu modlitby.",
	"Whether hypertext links (as buttons) to other prayers of the selected celebration should be displayed.",
	"Ostendendine sunt nexus hypertextuales ad ceteras horas diei, vel ad præcedentem/sequentem diem directe in textu Officii.",
	"",
	"Zda zobrazit hypertextové odkazy na ostatní modlitby daného dne, resp. předešlý/následující den přímo v textu modlitby.",
	"Legyen-e hiperhivatkozás a nap többi imaórájára is,  illetve mutassa-e az előző és következő nap imaóráit is közvetlenül a szövegben.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_moznosti[POCET_JAZYKOV + 1] =
{
	"zobraziť rozličné možnosti priamo v textoch modlitieb",
	"zobrazit rozličné volby v textech modliteb",
	"display various options in prayers",
	"ostende varia possibilitates directe in textibus orationum",
	"",
	"zobrazit rozličné volby v textech modliteb",
	"mutassa meg az imák szövegében a különböző lehetőségeket",
	"ru_text",
	"паказваць розныя опцыі ў малітвах",
	"að sýna leiðbeiningar beint í bænatextum",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_moznosti_explain[POCET_JAZYKOV + 1] =
{
	"Či sa majú zobrazovať hypertextové odkazy na iné zobrazenie tej istej modlitby priamo v texte modlitby (napr. pre modlitbu cez deň na verziu s doplnkovou psalmódiou).", // Vtedy nie je potrebné, aby boli zobrazené prepínače na titulnej stránke.
	"Zda zobrazit hypertextové odkazy na jiné zobrazení modlitby daného dne přímo v textu modlitby (např. pro modlitbu uprostrěd dne verzi se žalmy z doplňujícího cyklu).",
	"Whether various options should be displayed directly in the prayer's texts.",
	"Ostendendine sunt nexus hypertextuales pro alias possibilitates eiusdem Officii directe in textu Officii (e.g. in Horam mediam ad versionem cum psalmodia complementari).",
	"",
	"Zda zobrazit hypertextové odkazy na jiné zobrazení modlitby daného dne přímo v textu modlitby (např. pro modlitbu uprostrěd dne verzi se žalmy z doplňujícího cyklu).",
	"Megjelenjenek-e közvetlenül különböző lehetőségek az ima szövegében (pl. napközi imaóránál a kiegészítő zsoltár).",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_textwrap[POCET_JAZYKOV + 1] =
{
	"zalamovať dlhé riadky ako v tlačenom vydaní (poetické časti)",
	"zalomit dlouhé řádky poetických textů jako v tištěném vydání",
	"wrap long lines according to printed edition",
	"colloca lineas longas sicut in editione impressa (partes poeticæ)",
	"",
	"zalomit dlouhé řádky poetických textů jako v tištěném vydání",
	"hosszú sorok tördelése, mint a nyomtatott kiadásban (versrészek)",
	"ru_text",
	"скарачаць даўгія радкі, як у друкаваным выданні",
	"skipta löngum línum eins og í prentútgáfu (ljóðrænir hlutar)",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_textwrap_explain[POCET_JAZYKOV + 1] =
{
	"Či sa majú v texte modlitby dlhé riadky žalmov, chválospevov a iných poetických častí zalamovať ako v tlačenom vydaní.",
	"Zda zalomit dlouhé řádky poetických textů jako v tištěném vydání (normálně: nezalamovat).",
	"Whether long lines should be wrapped as in printed edition.",
	"Disponendine sunt versus longi psalmorum, canticorum et aliorum textorum poeticorum in paginas ut in editione typis impressa.",
	"",
	"Zda zalomit dlouhé řádky poetických textů jako v tištěném vydání (normálně: nezalamovat).",
	"Legyenek-e tördelve az imaórák szövegében a zsoltárok, kantikumok és más versrészek hosszú sorai, mint a nyomtatott kiadásban.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_buttons_usporne[POCET_JAZYKOV + 1] =
{
	"úsporné zobrazenie tlačidiel pre modlitby",
	"úsporné zobrazení tlačítek pro modlitby",
	"tight display of buttons for prayers",
	"ostende pulsabulas pro orationibus cum parsimonia",
	"",
	"úsporné zobrazení tlačítek pro modlitby",
	"az imaórák gombjainak gazdaságos elhelyezése",
	"ru_text",
	"меншыя кнопкі ў малітвах",
	"minni birting hnappa fyrir bænir",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_buttons_usporne_explain[POCET_JAZYKOV + 1] =
{
	"Či sa majú tlačidlá pre modlitby zobraziť úsporne, v tabuľke (menšia šírka) kvôli mobilným zariadeniam.",
	"Zda se mají tlačítka pro modlitby zobrazit úsporně, v tabulce (menší šířka) pro mobilní zařízení.",
	"Whether buttons for prayers should be displayed economically for mobile devices.",
	"Ostendanturne pulsabulæ pro Horas parce, in tabellam (latitudo minor) machinarum mobilium causa.",
	"",
	"Zda se mají tlačítka pro modlitby zobrazit úsporně, v tabulce (menší šířka) pro mobilní zařízení.",
	"Legyenek-e az imaórák gombjai gazdaságosan elhelyezve, táblázatban (kisebb szélesség) mobilkészülékekhez.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_nocny_rezim[POCET_JAZYKOV + 1] =
{
	"nočný režim",
	"noční režim",
	"night mode",
	"modus nocturnus",
	"",
	"noční režim",
	"éjszakai mód",
	"ночной режим",
	"начны рэжым",
	"nátthamur",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_nocny_rezim_explain[POCET_JAZYKOV + 1] =
{
	"Zobrazí svetlý text na tmavom pozadí.",
	"Zobrazí světlý text na tmavém pozadí.",
	"Displays dark background with light text for night usage.",
	"Scriptum lucidum in reductioris obscuris ostendit.",
	"",
	"Zobrazí světlý text na tmavém pozadí.",
	"Világos szöveg megjelenítése sötét háttéren.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_rounded_corners[POCET_JAZYKOV + 1] =
{
	"zaoblené rohy tlačidiel",
	"zaoblené rohy tlačítek",
	"rounded corners of buttons",
	"angulis rotundatis",
	"",
	"zaoblené rohy tlačítek",
	"lekerekített sarok",
	"закругленные углы",
	"закругленыя куты",
	"ávöl horn",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_rounded_corners_explain[POCET_JAZYKOV + 1] =
{
	"Zobrazí zaoblené rohy tlačidiel.",
	"Zobrazí zaoblené rohy tlačítek.",
	"Displays rounded corners of buttons.",
	"",
	"",
	"Zobrazí zaoblené rohy tlačítek.",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_alternatives[POCET_JAZYKOV + 1] =
{
	"alternatívy",
	"alternativy",
	"alternatives",
	"optiones",
	"",
	"alternativy",
	"lehetőségek",
	"ru_text",
	"альтэрнатывы",
	"valkostur",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_alternatives_explain[POCET_JAZYKOV + 1] =
{
	"Zobrazí v texte modlitieb iba jednu možnosť, napr. hymnus pre kompletórium (dá sa prepínať).",
	"Zobrazí v textu modliteb jenom jednu možnost (je možné přepínat).",
	"In the prayer text, displays only one option (e.g. hymn for compline; user can switch options).",
	"Ostendit in textu Officii unam solam possibilitatem, e.g. hymnum ad Completorium (mutarier potest).",
	"",
	"Zobrazí v textu modliteb jenom jednu možnost (je možné přepínat).",
	"Megmutatja…",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_show_defalut_calendar[POCET_JAZYKOV + 1] =
{
	"zvýrazniť slávenia v národnom kalendári",
	"zvýraznit slavení v národním kalendáři",
	"mark celebrations in local (national) calendar",
	"exprime celebrationes in calendario nationale",
	"",
	"zvýraznit slavení v národním kalendáři",
	"kijelölni az ünnepeket a nemzeti naptárban",
	"ru_text",
	"пазначаць цэлебрацыі лакальнага календара",
	"feitletra helgihald í þjóðardagatali",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_show_defalut_calendar_explain[POCET_JAZYKOV + 1] =
{
	"V podnadpise modlitby zobrazí informáciu, že slávenie je v národnom kalendári (teda nie vo všeobecnom kalendári).",
	"V podnadpisu modlitby zobrazí informaci, že slávení je v národním kalendáři (tedy ne v obecním kalendáři).",
	"",
	"In subtitulo ostendit celebrationem in calendario proprio esse (non in calendario universali).",
	"",
	"V podnadpisu modlitby zobrazí informaci, že slávení je v národním kalendáři (tedy ne v obecním kalendáři).",
	"Az ima felirata alatt megmutatja az információt, hogy az ünnep a nemzeti naptárban van (tehát nem az általánosban).",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_background_override[POCET_JAZYKOV + 1] =
{
	"použiť bielu/čiernu farbu pozadia (projektor/AMOLED displej)",
	"použít bílou/černou barvu pozadí (projektor/AMOLED displej)",
	"use white/black background color (beamer/AMOLED display)",
	"applica colorem album/nigrum areæ posterioris (proiector/AMOLED display)",
	"",
	"použít bílou/černou barvu pozadí (projektor/AMOLED displej)",
	"fehér/fekete háttért alkalmazni (vetítő/AMOLED kijelző)",
	"ru_text",
	"Выкарыстоўваць белы / чорны фон (праектар / дысплэі AMOLED)",
	"nota hvítan / svartan bakgrunn (skjávarpi / AMOLED skjár)",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_2_background_override_explain[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"la_text",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_KomplHymnusA[POCET_JAZYKOV + 1] =
{
	"hymnus A: Na sklonku dňa ťa úprimne",
	"hymnus A: Na sklonku dne tě upřímně",
	"hymn A",
	"hymnus A: Te lucis ante términum",
	"",
	"hymnus A: Na sklonku dne tě upřímně",
	"Immár a nap leáldozott",
	"ru_text",
	"гімн A",
	"hymni A: Ó, Drottinn hjá mér dvel í nótt",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_KomplHymnusB[POCET_JAZYKOV + 1] =
{
	"hymnus B: Kriste, ty svetlo a náš deň",
	"hymnus B: Ty, Kriste, světlo, jasný dni",
	"hymn B",
	"hymnus B: Christe, qui, splendor et dies",
	"",
	"hymnus B: Ty, Kriste, světlo, jasný dni",
	"Krisztus, tündöklő nappalunk",
	"ru_text",
	"гімн Б",
	"hymni B: Þú, Jesús, lífsins lindin best",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_KomplOkt1[POCET_JAZYKOV + 1] =
{
	"prvé nedeľné kompletórium",
	"první nedělní kompletář",
	"1st Sunday Compline",
	"I Completorium Dominicæ",
	"",
	"první nedělní kompletář",
	"befejező imaóra I. e. d. után",
	"ru_text",
	"by_text",
	"fyrsti náttsöngur sunnudags",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_KomplOkt2[POCET_JAZYKOV + 1] =
{
	"druhé nedeľné kompletórium",
	"druhý nedělní kompletář",
	"2nd Sunday Compline",
	"II Completorium Dominicæ",
	"",
	"druhý nedělní kompletář",
	"befejező imaóra II. e. d. után",
	"ru_text",
	"by_text",
	"annar náttsöngur sunnudags",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_PCHymnusI[POCET_JAZYKOV + 1] =
{
	"hymnus I. [Ak je posvätné čítanie v noci alebo včasráno]",
	"hymnus I. [V noci a časně ráno]",
	"hymn I. [during the night and early in the morning]",
	"hymnum I. [Quando Officium lectionis dicitur noctu vel summo mane]",
	"",
	"hymnus I. [V noci a časně ráno]",
	"himnusz I. [Amikor az imaórát éjszaka vagy kora hajnalban mondják]",
	"ru_text",
	"гімн I",
	"Hymni I. [Ef óttusöngur hinn fyrri er um nótt eða snemma um morgun]",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_PCHymnusII[POCET_JAZYKOV + 1] =
{
	"hymnus II. [Ak je posvätné čítanie cez deň]",
	"hymnus II. [uprostřed dne]",
	"hymn II. [during the day]",
	"hymnum II. [Quando Officium lectionis dicitur diurno tempore]",
	"",
	"hymnus II. [Během dne]",
	"himnusz II. [Amikor az imaórát a nap nem reggeli órájában végzik]",
	"ru_text",
	"гімн II",
	"hymni II. [Ef óttusöngur hinn fyrri er um daginn]",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_PCHymnusVNnedela[POCET_JAZYKOV + 1] =
{
	"hymnus Toto je pravý Boží deň",
	"hymnus nedělní",
	"Sunday's hymn",
	"hymnum dominicalem",
	"",
	"hymnus nedělní",
	"Urunknak áldott napja ez",
	"ru_text",
	"гімн ...",
	"hymni Lofum þann sem lífið gefur",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_PCHymnusVNferia[POCET_JAZYKOV + 1] =
{
	"hymnus Nech z výšin neba radosť znie",
	"hymnus z férie",
	"ferial hymn",
	"hymnum ferialem",
	"",
	"hymnus z férie",
	"Örvendj, ég, messzi csillagok",
	"ru_text",
	"гімн ...",
	"hymni Guð helgur andi himni af",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_RChHymnusVNnedela[POCET_JAZYKOV + 1] =
{
	"hymnus Bronie sa zora na nebi",
	"hymnus nedělní",
	"Sunday's hymn",
	"hymnum dominicalem",
	"",
	"hymnus nedělní",
	"Rózsálló hajnalfény ragyog",
	"ru_text",
	"гімн ...",
	"hymni Kristur, þig kallar á",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_RChHymnusVNferia[POCET_JAZYKOV + 1] =
{
	"hymnus Nech novým Jeruzalemom",
	"hymnus z férie",
	"hymnus férie",
	"hymnum ferialem",
	"",
	"hymnus z férie",
	"Az új Sionnak kórusa",
	"ru_text",
	"гімн ...",
	"hymni Guðs föður dýrðar dásöm mynd",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_VespHymnusVNnedela[POCET_JAZYKOV + 1] =
{
	"hymnus Pri Baránkovej večeri",
	"hymnus nedělní",
	"hymnus NE",
	"hymnum dominicalem",
	"",
	"hymnus nedělní",
	"Ím, vár a Bárány asztala",
	"ru_text",
	"гімн ...",
	"hymni Nú vil eg enn í nafni þínu",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_VespHymnusVNferia[POCET_JAZYKOV + 1] =
{
	"hymnus Kráľ vekov, Pane, Boží Syn",
	"hymnus z férie",
	"hymnus férie",
	"hymnum ferialem",
	"",
	"hymnus z férie",
	"Örök Királyunk, szent Urunk",
	"ru_text",
	"гімн ...",
	"hymni Hann sagði við þá: Sjá, ég kem í skýjum",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_MCDPredHymnus1[POCET_JAZYKOV + 1] =
{
	"hymnus Príď, Duchu Svätý",
	"hymnus K nám, Duchu Svatý, nyní spěj",
	"hymn 1",
	"hymnum Nunc, Sancte, nobis, Spíritus",
	"",
	"hymnus K nám, Duchu Svatý, nyní spěj",
	"Most jöjj, Szentlélek, szállj közénk",
	"ru_text",
	"гімн 1",
	"hymni Þú, Jesús, ert vegur til himinsins heim",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_MCDPredHymnus2[POCET_JAZYKOV + 1] =
{
	"hymnus Deviata je už hodina",
	"hymnus Je třetí denní hodina",
	"hymn 2",
	"hymnum Certum tenéntes órdinem",
	"",
	"hymnus Je třetí denní hodina",
	"Idők rendjét megtartva most",
	"ru_text",
	"гімн 2",
	"hymni Almáttugur Guð, allra stétta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_MCDNaHymnus1[POCET_JAZYKOV + 1] =
{
	"hymnus Mocný Vládca, verný Bože",
	"hymnus Jsi mocný Vládce, věrný Bůh",
	"hymn 1",
	"hymnum Rector potens, verax Deus",
	"",
	"hymnus Jsi mocný Vládce, věrný Bůh",
	"Urunk, felséges Istenünk",
	"ru_text",
	"гімн 1",
	"hymni Þinn andi, Guð, til Jesú Krists mig kalli",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_MCDNaHymnus2[POCET_JAZYKOV + 1] =
{
	"hymnus Na nebi slnko vrcholí",
	"hymnus Teď Pánu chvály zpívejme",
	"hymn 2",
	"hymnum Dicámus laudes Dómino",
	"",
	"hymnus Teď Pánu chvály zpívejme",
	"Dicsérjük dallal az Urat",
	"ru_text",
	"гімн 2",
	"hymni Vér stöndum á bjargi, sem bifast ei má",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_MCDPoHymnus1[POCET_JAZYKOV + 1] =
{
	"hymnus Celý svet v pohyb uvádzaš",
	"hymnus Svět celý v pohyb uvádíš",
	"hymn 1",
	"hymnum Rerum, Deus, tenax vigor",
	"",
	"hymnus Svět celý v pohyb uvádíš",
	"Világfenntartó Istenünk",
	"ru_text",
	"гімн 1",
	"hymni Í bljúgri bæn og þökk til þín",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_MCDPoHymnus2[POCET_JAZYKOV + 1] =
{
	"hymnus Z Božej milosti tretí raz",
	"hymnus Hodina třetí z poledne",
	"hymn 2",
	"hymnum Ternis horárum términis",
	"",
	"hymnus Hodina třetí z poledne",
	"Háromszor három óra már",
	"ru_text",
	"гімн 2",
	"hymni Hygg að, því barni mest er mjúkt",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_1VHymnusNe[POCET_JAZYKOV + 1] =
{
	"hymnus pre prvé vešpery",
	"hymnus pro první nešpory",
	"hymn for first vespers",
	"hymnum de I Vesperis",
	"",
	"hymnus pro první večerní chvály",
	"I. Esti dicséret himnusza",
	"ru_text",
	"гімн ...",
	"hymni fyrir fyrsta aftansöng",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_1VHymnusPC[POCET_JAZYKOV + 1] =
{
	"hymnus ako je pre posvätné čítanie [cez deň]",
	"hymnus pro čtení [uprostřed dne]",
	"hymn from readings [during the day]",
	"hymnum de Officio lectionis [diurno tempore]",
	"",
	"hymnus pro čtení [během dne]",
	"Olvasmányos imaóra himnusza [napközben]",
	"ru_text",
	"гімн ...",
	"hymni er eins og í óttusöng hinn fyrri [um daginn]",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_OCR34Hymns_ordinary[POCET_JAZYKOV + 1] =
{
	"hymny zo žaltára",
	"hymny ze žaltáře",
	"",
	"hymnos de psalterio",
	"",
	"hymny ze žaltáře",
	"a zsoltáros rész himnusza",
	"ru_text",
	"by_text",
	"hymnar úr sálmabók",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_OCR34Hymns[POCET_JAZYKOV + 1] =
{
	"hymny pre 34. týždeň Cezročného obdobia",
	"hymny pro 34. týden mezidobí",
	"",
	"hymnos pro Hebdomada XXXIV per annum",
	"",
	"hymny pro 34. týden mezidobí",
	"az évközi idő 34. hetében vehető himnusz",
	"ru_text",
	"by_text",
	"hymnar fyrir 34. viku innan ársins",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_OCR34Hymns_explain[POCET_JAZYKOV + 1] =
{
	"Vo férie 34. týždňa Cezročného obdobia možno použiť špeciálne hymny.",
	"",
	"",
	"In feriis hebdomadæ XXXIV per annum sumi possunt hymni proprii.",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_CZHymnus_ordinary[POCET_JAZYKOV + 1] =
// used only for CZ
{
	"hymny z breviára",
	"hymny z breviáře",
	"",
	"hymnos de breviario",
	"",
	"hymny z breviáře",
	"",
	"ru_text",
	"by_text",
	"hymnar úr Tíðabænabókinni",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_CZHymnus_extra[POCET_JAZYKOV + 1] =
// used only for CZ
{
	"hymny z voľného výberu",
	"hymny k volnému výběru",
	"",
	"hymnos ad libitum adhibendos",
	"",
	"hymny k volnému výběru",
	"",
	"ru_text",
	"by_text",
	"hymnar að frjáls vali",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_PopolStrPsalm_4STR[POCET_JAZYKOV + 1] =
{
	"psalmódia pre Popolcovú stredu zo stredy 4. týždňa žaltára",
	"žalmy pro Popeleční středu ze středy 4. týdne žaltáře",
	"for Ash Wednesday take psalmody from Wednesday, 4th week of Psalter",
	"psalmodia pro Feria IV Cinerum de Feria IV hebdomadæ IV Psaltarii",
	"",
	"žalmy pro Popeleční středu ze středy 4. týdne žaltáře",
	"Hamvazószerdán vegye a zsoltározást a 4. zsoltáros hét szerdájáról",
	"ru_text",
	"by_text",
	"sálmar fyrir öskudag er teknir frá miðvikudegi 4. viku saltara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_PopolStrPsalm_3PI[POCET_JAZYKOV + 1] =
{
	"psalmódia pre Popolcovú stredu z piatka 3. týždňa žaltára",
	"žalmy pro Popeleční středu z pátku 3. týdne žaltáře",
	"for Ash Wednesday take psalmody from Friday, 3rd week of Psalter",
	"psalmodia pro Feria IV Cinerum de Feria IV hebdomadæ III Psaltarii",
	"",
	"žalmy pro Popeleční středu z pátku 3. týdne žaltáře",
	"Hamvazószerdán vegye a zsoltározást a 3. zsoltáros hét péntekjéről",
	"ru_text",
	"by_text",
	"sálmar fyrir öskudag er teknir frá föstudegi 3. viku saltara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_ZelStvPsalm_2STV[POCET_JAZYKOV + 1] =
{
	"psalmódia pre Štvrtok Svätého týždňa (Zelený štvrtok) zo štvrtka 2. týždňa žaltára",
	"žalmy pro Zelený čtvrtek ze čtvrtka 2. týdne žaltáře",
	"for Maundy Thursday take psalmody from Thursday, 2th week of Psalter",
	"psalmodia pro Feria V Hebdomadæ sanctæ de Feria V hebdomadæ II Psaltarii",
	"",
	"žalmy pro Zelený čtvrtek ze čtvrtka 2. týdne žaltáře",
	"Nagycsütörtök vegye a zsoltározást a 2. zsoltáros hét csütörtökjáról",
	"ru_text",
	"by_text",
	"sálmar fyrir skírdag er teknir frá fimmtudegi 2. viku saltara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_ZelStvPsalm_3PI[POCET_JAZYKOV + 1] =
{
	"psalmódia pre Štvrtok Svätého týždňa (Zelený štvrtok) z piatka 3. týždňa žaltára",
	"žalmy pro Zelený čtvrtek z pátku 3. týdne žaltáře",
	"for Maundy Thursday take psalmody from Friday, 3rd week of Psalter",
	"psalmodia pro Feria V Hebdomadæ sanctæ de Feria IV hebdomadæ III Psaltarii",
	"",
	"žalmy pro Zelený čtvrtek z pátku 3. týdne žaltáře",
	"Nagycsütörtök vegye a zsoltározást a 3. zsoltáros hét péntekjéről",
	"ru_text",
	"by_text",
	"sálmar fyrir skírdag er teknir frá föstudegi 3. viku saltara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_CZhymny[POCET_JAZYKOV + 1] =
// used only for CZ
{
	"hymny",
	"hymny",
	"hymns",
	"hymni",
	"",
	"",
	"",
	"ru_text",
	"by_text",
	"hymnar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_CZhymny_explain[POCET_JAZYKOV + 1] =
// used only for CZ
{
	"",
	"Zobrazí v textu modliteb hymny z breviáře nebo k volnému výběru (je možné přepínat).",
	"",
	"Ostendit hymnos ex Breviario, vel ad libitum adhibendos, in textu Officii.",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_CZhymnyNORMAL[POCET_JAZYKOV + 1] =
// used only for CZ
{
	"hymny z breviára",
	"hymny z breviáře",
	"hymns from breviary",
	"hymni ex Breviario",
	"",
	"",
	"",
	"ru_text",
	"by_text",
	"hymnar úr Tíðabænabókinni",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_CZhymnyRENC[POCET_JAZYKOV + 1] =
// used only for CZ
{
	"hymny z voľného výberu",
	"hymny k volnému výběru (Renč)",
	"hymns for free use (ad libitum)",
	"hymni adhibendi ad libitum (Renč)",
	"",
	"",
	"",
	"ru_text",
	"by_text",
	"hymnar að frjáls vali",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_DPsalmZ122_129[POCET_JAZYKOV + 1] =
{
	"namiesto žalmu 122 brať žalm 129",
	"místo žalmu 122 vzít žalm 129",
	"instead of psalm 122 use 129",
	"loco psalmi 121 (122) psalmum 128 (129) adhibere",
	"",
	"místo žalmu 121 (122) vzít žalm 128 (129)",
	"a 121. helyett vehető a 128. zsoltár",
	"ru_text",
	"выкарыстоўваць псальм 129 (128) замест 122 (121)",
	"í stað sálms 122 er tekinn sálmur 129",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_DPsalmZ126_129[POCET_JAZYKOV + 1] =
{
	"namiesto žalmu 126 brať žalm 129",
	"místo žalmu 126 vzít žalm 129",
	"instead of psalm 126 use 129",
	"loco psalmi 125 (126) psalmum 128 (129) adhibere",
	"",
	"místo žalmu 125 (126) vzít žalm 128 (129)",
	"a 125. helyett vehető a 128. zsoltár",
	"ru_text",
	"выкарыстоўваць псальм 129 (128) замест 126 (125)",
	"á stað sálms 126 er tekinn sálmur 129",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_DPsalmZ127_131[POCET_JAZYKOV + 1] =
{
	"namiesto žalmu 127 brať žalm 131",
	"místo žalmu 127 vzít žalm 131",
	"instead of psalm 127 use 131",
	"loco psalmi 126 (127) psalmum 130 (131) adhibere",
	"",
	"místo žalmu 126 (127) vzít žalm 130 (131)",
	"a 126. helyett vehető a 130. zsoltár",
	"ru_text",
	"выкарыстоўваць псальм 131 (130) замест 127 (126)",
	"á stað sálms 127 er tekinn sálmur 131",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_DPsalmZ122_NORMAL[POCET_JAZYKOV + 1] =
{
	"brať žalm 122 z doplnkovej psalmódie",
	"vzít žalm 122 z doplňovacího cyklu",
	"use psalm 122 from complementary psalmody",
	"psalmum 121 (122) de psalmodia complementari sumere",
	"",
	"vzít žalm 121 (122) z doplňovacího cyklu",
	"hu_take 121. zsoltár from kiegészítő zsoltároknál",
	"ru_text",
	"выкарыстоўваць псальм 122 (121) з дадатковай псальмодыі",
	"sálmur 122 er tekinn frá aukasálmum",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_DPsalmZ126_NORMAL[POCET_JAZYKOV + 1] =
{
	"brať žalm 126 z doplnkovej psalmódie",
	"vzít žalm 126 z doplňovacího cyklu",
	"use psalm 126 from complementary psalmody",
	"psalmum 125 (126) de psalmodia complementari sumere",
	"",
	"vzít žalm 125 (126) z doplňovacího cyklu",
	"hu_take 125. zsoltár from kiegészítő zsoltároknál",
	"ru_text",
	"выкарыстоўваць псальм 126 (125) з дадатковай псальмодыі",
	"sálmur 126 er tekinn frá aukasálmum",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_DPsalmZ127_NORMAL[POCET_JAZYKOV + 1] =
{
	"brať žalm 127 z doplnkovej psalmódie",
	"vzít žalm 127 z doplňovacího cyklu",
	"use psalm 127 from complementary psalmody",
	"psalmum 126 (127) de psalmodia complementari sumere",
	"",
	"vzít žalm 126 (127) z doplňovacího cyklu",
	"hu_take 126. zsoltár from kiegészítő zsoltároknál",
	"ru_text",
	"выкарыстоўваць псальм 127 (126) з дадатковай псальмодыі",
	"sálmur 127 er tekinn frá aukasálmum",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_DPsalmZ122_129_explain[POCET_JAZYKOV + 1] =
{
	"V doplnkovej psalmódii namiesto žalmu 122 možno brať žalm 129.",
	"Pro doplňovací cyklus žalmů místo žalmu 122 (121) vzít žalm 129 (128).",
	"",
	"In psalmodia complementari pro psalmo 121 (122) psalmum 128 (129) sumere.",
	"",
	"Pro doplňovací cyklus žalmů místo žalmu 121 (122) vzít žalm 128 (129).",
	"A kiegészítő zsoltároknál a 121. helyett vehető a 128. zsoltár.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_DPsalmZ126_129_explain[POCET_JAZYKOV + 1] =
{
	"V doplnkovej psalmódii namiesto žalmu 126 možno brať žalm 129.",
	"Pro doplňovací cyklus žalmů místo žalmu 126 (125) vzít žalm 129 (128).",
	"",
	"In psalmodia complementari pro psalmo 125 (126) psalmum 128 (129) sumere.",
	"",
	"Pro doplňovací cyklus žalmů místo žalmu 125 (126) vzít žalm 128 (129).",
	"A kiegészítő zsoltároknál a 125. helyett vehető a 128. zsoltár.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_DPsalmZ127_131_explain[POCET_JAZYKOV + 1] =
{
	"V doplnkovej psalmódii namiesto žalmu 127 možno brať žalm 131.",
	"Pro doplňovací cyklus žalmů místo žalmu 127 (126) vzít žalm 131 (130).",
	"",
	"In psalmodia complementari pro psalmo 126 (127) psalmum 130 (131) sumere.",
	"",
	"Pro doplňovací cyklus žalmů místo žalmu 126 (127) vzít žalm 130 (131).",
	"A kiegészítő zsoltároknál a 126. helyett vehető a 130. zsoltár.",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_OffDefZ146_150[POCET_JAZYKOV + 1] =
{
	"namiesto žalmu 146 brať žalm 150",
	"místo žalmu 146 (145) vzít žalm 150",
	"instead of psalm 146 use psalm 150",
	"pro psalmo 145 (146) psalmum 150 sumere",
	"",
	"místo žalmu 145 (146) vzít žalm 150",
	"a 145. helyett vehető a 150. zsoltár",
	"ru_text",
	"выкарыстоўваць псальм 150 замест 146 (145)",
	"í stað sálms 146 er tekinn sálmur 150    ",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_OffDefZ146_150_explain[POCET_JAZYKOV + 1] =
{
	"V ranných chválach ofícia za zosnulých namiesto žalmu 146 brať žalm 150",
	"Pro ranní chvály modliteb za zemřelé místo žalmu 146 (145) vzít žalm 150.",
	"instead of psalm 146 use psalm 150",
	"Ad Laudes matutinas Officii defunctorum pro psalmo 145 (146) psalmum 150 sumere",
	"",
	"Pro ranní chvály modliteb za zemřelé místo žalmu 145 (146) vzít žalm 150.",
	"a 145. helyett vehető a 150. zsoltár",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_OffDefZ146_150_NORMAL[POCET_JAZYKOV + 1] =
{
	"namiesto žalmu 150 brať žalm 146",
	"místo žalmu 150 vzít žalm 146 (145)",
	"instead of psalm 150 use psalm 146",
	"pro psalmo 150 psalmum 145 (146) sumere",
	"",
	"místo žalmu 150 vzít žalm 145 (146)",
	"a 150. helyett vehető a 145. zsoltár",
	"ru_text",
	"выкарыстоўваць псальм 146 (145) замест 150",
	"í stað sálms 150 er tekin sálmur 146",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_zaver_knaz_diakon[POCET_JAZYKOV + 1] =
{
	"záver, ak predsedá kňaz alebo diakon",
	"závěr, předsedá-li kněz nebo jáhen",
	"conclusion in case when priest or diacon is present",
	"conclusio, si præest sacerdos vel diaconus",
	"",
	"závěr, pokud předsedá kněz nebo jáhen",
	"ha az imaórát pap vagy diakónus vezeti",
	"ru_text",
	"завяршэнне на выпадак, калі прысутны святар ці дыякан",
	"lok bænar, ef prestur eða djákni leiða hana",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_zaver_knaz_diakon_explain[POCET_JAZYKOV + 1] =
{
	"V ranných chválach a vešperách závisí záver modlitby od toho, či predsedá kňaz alebo diakon, alebo nie.",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_5_zaver_knaz_diakon_NORMAL[POCET_JAZYKOV + 1] =
{
	"záver, ak nepredsedá kňaz alebo diakon a pri recitovaní jednotlivca",
	"závěr, není-li přítomen kněz nebo jáhen anebo modlí-li se někdo sám",
	"conclusion in case when priest or diacon is not present and for individual prayer",
	"conclusio, si absit sacerdos vel diaconus et in reciatione a solo",
	"",
	"závěr, pokud nepředsedá kněz nebo jáhen a při recitovaní jednotlivce",
	"ha nincs jelen pap vagy diakónus, valamint egyéni imádkozás esetén",
	"ru_text",
	"завяршэнне на выпадак, калі святара ці дыякана няма альбо для індывідуальнай малітвы",
	"lok bænar, ef prestur eða djákni leiða hana ekki, eða einstaklingur les hana",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_6_alternatives_multi[POCET_JAZYKOV + 1] =
{
	"alternatívy (viac možností)",
	"alternativy (více možností)",
	"alternatives (multiple)",
	"optiones (plures possibilitates)",
	"",
	"alternativy (více možností)",
	"lehetőségek",
	"ru_text",
	"альтэрнатывы",
	"valkostir (fleiri kostir)",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_6_alternatives_multi_hymnus[POCET_JAZYKOV + 1] =
{
	"iný hymnus",
	"jiný hymnus",
	"another hymn",
	"hymnus alius",
	"",
	"jiný hymnus",
	"más himnusz",
	"ru_text",
	"by_text",
	"annars konar hymni",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_6_alternatives_multi_psalm[POCET_JAZYKOV + 1] =
{
	"iný žalm",
	"jiný žalm",
	"another psalm",
	"psalmus alius",
	"",
	"jiný žalm",
	"másik zsoltár",
	"ru_text",
	"by_text",
	"annars konar sálmur",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// html_text_opt_6_alternatives_multi_citanie used both for 1st and 2nd reading
const char* html_text_opt_6_alternatives_multi_citanie[POCET_JAZYKOV + 1] =
{
	"iné čítanie",
	"jiné čtení",
	"another reading",
	"lectio alia",
	"",
	"jiné čtení",
	"más olvasmány",
	"ru_text",
	"by_text",
	"annars konar lestur",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// html_text_opt_6_alternatives_multi_antifona used for Benedictus (morning prayer), Magnificat (evening prayer) antiphone and antiphone for invitatory; used as replacement for (deprecated) html_text_opt_5_invitatorium_ant
const char* html_text_opt_6_alternatives_multi_antifona[POCET_JAZYKOV + 1] =
{
	"iná antifóna",
	"jiná antifona",
	"another antiphone",
	"antiphona alia",
	"",
	"jiná antifona",
	"másik antifóna",
	"ru_text",
	"by_text",
	"annars konar andstef",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_6_alternatives_multi_maria_ant[POCET_JAZYKOV + 1] =
{
	"iná antifóna",
	"jiná antifona",
	"another antiphone",
	"antiphona alia",
	"",
	"jiná antifona",
	"másik Mária-antifóna",
	"ru_text",
	"by_text",
	"annars konar andstef",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_6_alternatives_multi_prosby[POCET_JAZYKOV + 1] =
{
	"iné prosby",
	"jiné prosby",
	"another preces",
	"preces aliæ",
	"",
	"jiné prosby",
	"más fohászok",
	"ru_text",
	"by_text",
	"annars konar fyrirbænir",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_6_alternatives_multi_otcenas_uvod[POCET_JAZYKOV + 1] =
{
	"iný úvod",
	"jiný úvod",
	"another introduction",
	"introit alius",
	"",
	"jiný úvod",
	"más bevezetés",
	"ru_text",
	"by_text",
	"annars konar inngangur",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_6_alternatives_multi_ukonkaj[POCET_JAZYKOV + 1] =
{
	"iná forma úkonu kajúcnosti",
	"jiná forma úkonu kajícnosti",
	"another act of repentance",
	"alia forma actus pœnitentialis",
	"",
	"jiná forma úkonu kajícnosti",
	"más hu_text",
	"ru_text",
	"by_text",
	"annars konar form yfirbótarathafna ",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_6_alternatives_multi_kcit_resp[POCET_JAZYKOV + 1] =
{
	"iné čítanie a responzórium",
	"jiné čtení a zpěv",
	"another reading & responsory",
	"aliæ lectio et responsorium",
	"",
	"jiné čtení a krátké responsorium",
	"más olvasmány és válaszos ének",
	"ru_text",
	"by_text",
	"annars konar lestur og stutt svarstef",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_6_alternatives_multi_kresp[POCET_JAZYKOV + 1] =
{
	"iné responzórium",
	"jiný zpěv",
	"another responsory",
	"aliud responsorium",
	"",
	"jiné krátké responsorium",
	"más válaszos ének",
	"ru_text",
	"by_text",
	"annars konar stutt svarstef",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_opt_6_alternatives_multi_modlitba[POCET_JAZYKOV + 1] =
{
	"iná modlitba",
	"jiná modlitba",
	"another prayer",
	"alia oratio",
	"",
	"jiná modlitba",
	"más könyörgés",
	"ru_text",
	"by_text",
	"annars konar bæn",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_font_name_simple[POCET_JAZYKOV + 1] =
{
	"alebo použi písmo",
	"nebo použij písmo",
	"or use font",
	"vel font",
	"",
	"nebo použij písmo",
	"betűtípus kiválasztása",
	"ru_text",
	"by_text",
	"eða notaðu leturgerð",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_font_name_simple_explain[POCET_JAZYKOV + 1] =
{
	"Ak nie je zvolené konkrétne písmo, použije sa predvolené písmo prehliadača (pätkové alebo bezpätkové podľa predchádzajúcej voľby zaškrtávacieho políčka).",
	"",
	"",
	"",
	"",
	"",
	"Ha nem választunk betűtípust, akkor a böngészőablakban látható az alapértelmezett (talpas vagy talpatlan az előző kiválasztás szerint).",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_font_name[POCET_JAZYKOV + 1] =
{
	"písmo",
	"písmo",
	"font",
	"font",
	"",
	"písmo",
	"betűtípus",
	"ru_text",
	"by_text",
	"leturgerð",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_font_size[POCET_JAZYKOV + 1] =
{
	"veľkosť písma",
	"velikost písma",
	"font size",
	"magnitudo litterarum",
	"",
	"velikost písma",
	"betűméret",
	"ru_text",
	"памер шрыфта",
	"leturstærð",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_font_size_explain[POCET_JAZYKOV + 1] =
{
	"Veľkosť písma",
	"",
	"",
	"Magnitudo litterarum",
	"",
	"",
	"betűméret",
	"",
	"",
	"Leturstærð",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// HTML option selected
const char* html_option_selected = " selected=\"selected\"";

// HTML option checked (pre checkboxy)
const char* html_option_checked = " checked=\"checked\"";

const char* html_text_kalendar[POCET_JAZYKOV + 1] =
{
	"kalendár",
	"kalendář",
	"calendar",
	"calendarium",
	"",
	"kalendář",
	"a naptárat",
	"ru_text",
	"каляндар",
	"dagatal",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_kalendar_miestny[POCET_JAZYKOV + 1] =
{
	"Kalendár Liturgie hodín",
	"Kalendář Liturgie hodin",
	"Calendar of Liturgy of hours",
	"Calendarium Liturgiæ horarum",
	"",
	"Kalendář Liturgie hodin",
	"Az imaórák liturgiája",
	"ru_text",
	"Каляндар Літургіі гадзінаў",
	"Litúrgískt dagatal",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* html_text_kalendar_miestny_text_after_combo[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	" naptárát használja", // note space before string
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_kalendar_miestny_explain[POCET_JAZYKOV + 1] =
{
	"Je možné zvoliť miestny kalendár (propriá) rehoľnej rodiny, rádu, kongregácie, inštitútu...",
	"Je možné vzít místní kalendář řeholní rodiny, řádu, kongregace, institutu...",
	"",
	"",
	"",
	"", // not applicable for CZOP
	"Lehetséges a helyi naptárt választani, szerzetesrendét, kongregációét, intézményét...",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* html_text_detaily_explain[POCET_JAZYKOV + 1] =
{
	"Ostatné nastavenia sa použijú z predchádzajúcej (hlavnej) stránky." HTML_P_END "\n" HTML_P_BEGIN "Pokiaľ sú niektoré parametre pre vybranú modlitbu nepoužiteľné, neberú sa do úvahy (môžu byť teda nastavené ľubovoľne).",
	"Jestliže jsou některé výše uvedené volby nepoužitelné pro nějakou modlitbu, neberou se v úvahu (mohou být nastaveny dle libovůle).",
	"If any of described options are not applicable for a chosen prayer, they can be set anyhow.",
	"",
	"",
	"Když jsou některé výše uvedené volby nepoužitelné pro nějakou modlitbu, neberou se v úvahu (mohou být nastaveny dle libovůle).",
	"A többi beállítási lehetőség a főoldalon található." HTML_P_END "\n" HTML_P_BEGIN "Amennyiben valamelyik kiválasztott paraméter nem működik, figyelmen kívül kell hagyni (vagyis tetszőlegesen állíthatók).",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// descriptive text for Invitatory prayer
const char* html_text_inv_slavaotcu[POCET_JAZYKOV + 1] =
{
	"Nasleduje <" HTML_SPAN_NORMAL ">Sláva Otcu" HTML_SPAN_END " a opakuje sa antifóna.",
	"Následuje <" HTML_SPAN_NORMAL ">Sláva Otci" HTML_SPAN_END " a opakuje se antifona.",
	"Follows <" HTML_SPAN_NORMAL ">Glory..." HTML_SPAN_END " and repeats antiphone.",
	"Consequitur <" HTML_SPAN_NORMAL ">Gloria Patri" HTML_SPAN_END " et repetitur antiphona.",
	"Nasleduje <" HTML_SPAN_NORMAL ">Sláva Otcu" HTML_SPAN_END " a opakuje sa antifóna.",
	"Následuje <" HTML_SPAN_NORMAL ">Sláva Otci" HTML_SPAN_END " a opakuje se antifona.",
	"Következik a <" HTML_SPAN_NORMAL ">Dicsőség az Atyának" HTML_SPAN_END " és megismételjük az antifónát.",
	"ru_text",
	"by_text",
	"Fylgir <" HTML_SPAN_NORMAL ">Dýrð sé Föðurnum" HTML_SPAN_END " og andstefin er endurtekin.",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// page navigation (top, bottom)
const char* html_text_top[POCET_JAZYKOV + 1] = { "navrch", "nahoru", "top", "", "", "nahoru", "fel", "ru_text", "by_text", "efst", /* STRING_1_FOR_NEW_LANGUAGE */ }; // HU: to up -> felfelé | up -> fel | Andy: fent | top -> eleje | to top -> elejére
const char* html_text_bottom[POCET_JAZYKOV + 1] = { "naspodok", "dolů", "bottom", "", "", "dolů", "le", "ru_text", "by_text", "neðst", /* STRING_1_FOR_NEW_LANGUAGE */ }; // HU: to down -> lefelé | down -> le | Andy: lent | bottom -> vége | to bottom -> végére

// titles & navigation for batch mode
const char* html_text_batch_Zoznam1[POCET_JAZYKOV + 1] = { "Zoznam modlitieb", "Seznam modliteb", "List of prayers", "", "", "Seznam modliteb", "Az imák jegyzéke", "ru_text", "by_text", "Listi yfir bænir", /* STRING_1_FOR_NEW_LANGUAGE */ };
const char* html_text_batch_Zoznam1m[POCET_JAZYKOV + 1] = { "Zoznam modlitieb po mesiacoch", "Seznam modliteb dle měsíců", "List of prayers by months", "", "", "Seznam modliteb dle měsíců", "Az imák jegyzéke hónapok szerint", "ru_text", "by_text", "Listi yfir bænir eftir mánuði", /* STRING_1_FOR_NEW_LANGUAGE */ };
const char* html_text_batch_obdobie1m[POCET_JAZYKOV + 1] = { "("/*obdobie */"od %d. %s %d do %d. %s %d)", "(pro období od %d. %s %d do %d. %s %d)", "(%d. %s %d — %d. %s %d)", "(%d. %s %d — %d. %s %d)", "(%d. %s %d — %d. %s %d)", "(pro období od %d. %s %d do %d. %s %d)", "(%d. %s %d — %d. %s %d)", "(%d. %s %d — %d. %s %d)", "(%d. %s %d — %d. %s %d)", "(%d. %s %d — %d. %s %d)", /* STRING_3_FOR_NEW_LANGUAGE */ };
const char* html_text_batch_Zoznam2[POCET_JAZYKOV + 1] = {/* Zoznam modlitieb pre */"%s %d", "%s %d", "%s %d", "%s %d", "%s %d", "%s %d", "%s %d", "%s %d", "%s %d", "%s %d", /* STRING_3_FOR_NEW_LANGUAGE */ };
const char* html_text_batch_Back[POCET_JAZYKOV + 1] = { "hore", "nahoru", "up", "", "", "nahoru", "felfelé", "ru_text", "by_text", "upp", /* STRING_1_FOR_NEW_LANGUAGE */ };

// zakončenie modlitby trojaké, krátke resp. dlhé | triple prayer ending (short, long)
const char* text_ZAKONCENIE_SKRZE_dlhe[POCET_JAZYKOV + 1] =
{
	"Skrze nášho Pána Ježiša Krista, tvojho Syna, ktorý je Boh a s_tebou žije a kraľuje v_jednote Ducha Svätého po všetky veky vekov.",
	"Skrze tvého Syna Ježíše Krista, našeho Pána, neboť on s_tebou v_jednotě Ducha Svatého žije a kraluje po všechny věky věků.",
	"",
	"Per D&#243;minum nostrum Iesum Christum, F&#237;lium tuum, qui tecum vivit et regnat in unit&#225;te Sp&#237;ritus Sancti, Deus, per &#243;mnia s&#509;cula sæcul&#243;rum.",
	"",
	"Skrze tvého Syna Ježíše Krista, našeho Pána, neboť on s_tebou v_jednotě Ducha Svatého žije a kraluje po všechny věky věků.",
	"A mi Urunk, Jézus Krisztus, a te Fiad által, aki veled él és uralkodik a Szentlélekkel egységben, Isten mindörökkön-örökké.",
	"ru_text",
	"by_text",
	"Fyrir Drottin vorn Jesúm Krist, Son þinn, sem með þér lifir og ríkir í einingu Heilags Anda, Guð, um aldir alda.",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* text_ZAKONCENIE_SKRZE_kratke[POCET_JAZYKOV + 1] =
{
	"Skrze Krista, nášho Pána.",
	"Skrze Krista, našeho Pána.",
	"",
	"Per Christum Dóminum nostrum.",
	"",
	"Skrze Krista, našeho Pána.",
	"Krisztus, a mi Urunk által.",
	"ru_text",
	"by_text",
	"Fyrir Krist, Drottin vorn.",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* text_ZAKONCENIE_LEBO_ON_dlhe[POCET_JAZYKOV + 1] =
{
	"Lebo on je Boh a s_tebou žije a kraľuje v_jednote Ducha Svätého po všetky veky vekov.",
	"Neboť on s_tebou v_jednotě Ducha Svatého žije a kraluje po všechny věky věků.",
	"",
	"Qui tecum vivit et regnat in unit&#225;te Sp&#237;ritus Sancti, Deus, per &#243;mnia s&#509;cula sæcul&#243;rum.",
	"",
	"Neboť on s tebou v jednotě Ducha Svatého žije a kraluje po všechny věky věků.",
	"Aki veled él és uralkodik a Szentlélekkel egységben, Isten mindörökkön-örökké.",
	"ru_text",
	"by_text",
	"Því að hann er Guð, sem með þér lifir og ríkir í einingu Heilags Anda, um aldir alda.",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* text_ZAKONCENIE_LEBO_ON_kratke[POCET_JAZYKOV + 1] =
{
	"Lebo on žije a kraľuje na veky vekov.",
	"Neboť on s_tebou žije a kraluje na věky věků.",
	"",
	"Qui vivit et regnat in s&#509;cula sæcul&#243;rum.",
	"",
	"Neboť on s tebou žije a kraluje na věky věků.",
	"Aki él és uralkodik mindörökkön-örökké.",
	"ru_text",
	"by_text",
	"Hann, sem lifir og ríkir um aldir alda.",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* text_ZAKONCENIE_LEBO_TY_dlhe[POCET_JAZYKOV + 1] =
{
	"Lebo ty si Boh a žiješ a kraľuješ s Bohom Otcom v_jednote Ducha Svätého po všetky veky vekov.",
	"Neboť ty žiješ a kraluješ s_Bohem Otcem v_jednotě Ducha Svatého po všechny věky věků.",
	"",
	"Qui vivis et regnas cum Deo Patre in unit&#225;te Sp&#237;ritus Sancti, Deus, per &#243;mnia s&#509;cula sæculórum.",
	"",
	"Neboť ty žiješ a kraluješ s Bohem Otcem v jednotě Ducha Svatého po všechny věky věků.",
	"Aki élsz és uralkodol az Atyaistennel és a Szentlélek­kel egységben, Isten mindörökkön-örökké.",
	"ru_text",
	"by_text",
	"Því að þú ert Guð, sem lifir og ríkir með Guði Föður, í einingu Heilags Anda, um aldir alda.",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* text_ZAKONCENIE_LEBO_TY_kratke[POCET_JAZYKOV + 1] =
{
	"Lebo ty žiješ a kraľuješ na veky vekov.",
	"Neboť ty žiješ a kraluješ na věky věků.",
	"",
	"Qui vivis et regnas in s&#509;cula sæculórum.",
	"",
	"Neboť ty žiješ a kraluješ na věky věků.",
	"Aki élsz és uralkodol mindörökkön-örökké.",
	"ru_text",
	"by_text",
	"Þú sem lifir og ríkir um aldir alda.",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// SK only (POST1_MODLITBA5NE)
const char* text_SK_ZAKONCENIE_ON_JE_dlhe = "On je Boh a s_tebou žije a kraľuje v_jednote Ducha Svätého po všetky veky vekov.";
const char* text_SK_ZAKONCENIE_ON_JE_kratke = "On žije a kraľuje na veky vekov.";
const char* text_SK_ZAKONCENIE_KTORY_JE_dlhe = "ktorý je Boh a s_tebou žije a kraľuje v_jednote Ducha Svätého po všetky veky vekov."; // SK: == ZAKONCENIE_KTORY_JE_MALE
const char* text_SK_ZAKONCENIE_KTORY_JE_kratke = "ktorý žije a kraľuje na veky vekov."; // SK: == ZAKONCENIE_KTORY_JE_MALE
// IS only
const char* text_IS_ZAKONCENIE_KTORY_JE_dlhe = "Sem með þér lifir og ríkir í einingu Heilags Anda, Guð, um aldir alda.";
const char* text_IS_ZAKONCENIE_KTORY_JE_kratke = "Sem með þér lifir og ríkir um aldir alda.";
const char* text_IS_ZAKONCENIE_KTORY_ZIJES_dlhe = "Þú sem lifir og ríkir með Guði Föður, í einingu Heilags Anda, Guð, um aldir alda.";
const char* text_IS_ZAKONCENIE_KTORY_ZIJES_kratke = "Þú sem lifir og ríkir um aldir alda.";

const char* text_ZAKONCENIE_O_TO_TA_PROSIME[POCET_JAZYKOV + 1] =
{
	"O_to ťa prosíme",
	"Prosíme o_to",
	"",
	"",
	"",
	"Prosíme o_to",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// nasledujú názvy liturgických dní -- follow the names of special liturgical celebrations

// --------------- 00 pohyblivé slávenia | celebrations with moving dates ---------------

const char* text_DRUHA_NEDELA_PO_NAR_PANA[POCET_JAZYKOV + 1] =
{
	"2. nedeľa po Narodení Pána",
	"2. neděle po Narození Páně",
	"",
	"Dominica II post Nativitatem",
	"",
	"2. neděle po Narození Páně",
	"Karácsony Utáni 2. Vasárnap",
	"ru_text",
	"II Нядзеля пасля Нараджэння Пана", // convertToRoman()
	"2. sunnudagur eftir jól, Birting Drottins",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// --------------- 01 január | january ---------------

const char* text_JAN_01[POCET_JAZYKOV + 1] =
{
	"Panny Márie Bohorodičky",
	"Matky Boží, Panny Marie",
	"",
	"Sanctæ Dei Genetricis Mariæ",
	"",
	"Matky Boží, Panny Marie",
	"Szűz Mária, Isten Anyja (újév)",
	"Пресвятая Богородица Мария",
	"Святой Багародзіцы Марыі",
	"Stórhátíð Maríu Guðsmóður",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_01_SJ[POCET_JAZYKOV + 1] =
{
	"Panny Márie Bohorodičky a Mena Ježiš " HTML_LINE_BREAK "(Titulárny sviatok Spoločnosti Ježišovej)", // titulárny sviatok Spoločnosti Ježišovej
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_02[POCET_JAZYKOV + 1] =
{
	"Sv. Bazila Veľkého a Gregora Nazianzského, " HTML_LINE_BREAK "biskupov a učiteľov Cirkvi",
	"Sv. Basila Velikého a Řehoře Naziánského, " HTML_LINE_BREAK "biskupů a učitelů církve",
	"",
	"Ss. Basilii Magni et Gregorii Nazianzeni, " HTML_LINE_BREAK "episcoporum et Ecclesiæ doctorum",
	"",
	"Sv. Basila Velikého a Řehoře Naziánského, " HTML_LINE_BREAK "biskupů a učitelů církve",
	"Nagy Szent Vazul és Nazianzi Szent Gergely " HTML_LINE_BREAK "püspökök és egyháztanítók",
	"Свв. Василий Великий и Григорий Назианзин, " HTML_LINE_BREAK "епископы и учители Церкви",
	"Св. Базыля Вялікага і Грыгорыя Назіянзскага, " HTML_LINE_BREAK "біскупаў і доктараў Касцёла",
	"Hl. Basilíusar mikla og Gregoríusar frá Nazianz, " HTML_LINE_BREAK "biskupa og kirkjufeðra",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_03[POCET_JAZYKOV + 1] =
{
	"Najsvätejšieho mena Ježiš",
	"Nejsvětějšího jména Ježíš",
	"",
	"Sanctissimi Nominis Iesu",
	"",
	"Nejsvětějšího jména Ježíš",
	"Jézus szent neve", // "Jézus Szentséges Nevének"
	"ru_text",
	"Найсвяцейшага Імя Езуса",
	"Alheilagt nafn Jesú",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_03_SJ[POCET_JAZYKOV + 1] =
{
	"Najsvätejšieho mena Ježiš",
	"Nejsvětějšího jména Ježíš" HTML_LINE_BREAK "(Titulární slavnost Tovaryšstva Ježíšova)",
	"",
	"Sanctissimi Nominis Iesu",
	"",
	"Nejsvětějšího jména Ježíš",
	"Jézus szentséges neve" HTML_LINE_BREAK "Jézus társasága névünnepe",
	"ru_text",
	"Найсвяцейшага Імя Езуса",
	"Alheilagt nafn Jesú",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_03_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Štefánie Quinzaniovej, panny",
	"Bl. Štěpánky Quinzaniové, panny, řeholnice",
	"",
	"",
	"",
	"Bl. Štěpánky Quinzaniové, panny, řeholnice",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_04_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Kyriaka Eliáša Chavaru, kňaza",
	"Sv. Cyriaka Eliáše Chavary, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_04_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Angely z Foligna, rehoľníčky, členky 3. rádu",
	"Sv. Anděly z Foligna, členky 3. řádu",
	"",
	"",
	"",
	"Sv. Anděly z Foligna, členky 3. řádu",
	"Folignói Szent Angéla, szerzetesnő a III. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_04_CM[POCET_JAZYKOV + 1] =
{
	"Sv. Alžbety Anny Bayleyovej Setonovej, rehoľníčky",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_05_CSSR[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Nepomuckého Neumanna, biskupa",
	"", // CZ (aj CZ CSsR): 19JUN
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_05_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Didaka Jozefa z Cádizu, kňaza, člena 1. rádu",
	"Bl. Diega Josefa z Cádizu, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_06[POCET_JAZYKOV + 1] = // 6. januára | alebo nedeľu medzi 2. a 8. januárom
{
	"Zjavenie Pána",
	"Zjevení Páně",
	"The Epiphany of the Lord",
	"In Epiphania Domini",
	"",
	"Zjevení Páně",
	"Urunk megjelenése (Vízkereszt)",
	"ru_text",
	"Аб'яўленне Пана",
	"Birting Drottins", // Geisladagur
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_07[POCET_JAZYKOV + 1] =
{
	"Sv. Rajmunda z Peňafortu, kňaza",
	"Sv. Rajmunda z Peňafortu, kněze",
	"",
	"S. Raimundi de Penyafort, presbyteri",
	"",
	"Sv. Rajmunda z Peňafortu, kněze",
	"Penyaforti Szent Rajmund áldozópap",
	"ru_text",
	"Св. Раймунда Пеньяфорцкага, прэзбітэра",
	"Hl. Raimunds frá Peñafort, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_08_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Petra Tomáša, biskupa",
	"Sv. Petra Tomáše, biskupa",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Péturs Tómasar, biskups",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_08_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Titusa Zemana, kňaza a mučeníka",
	"Bl. Tita Zemana, kněze a mučedníka",
	"",
	"",
	"",
	"",
	"Boldog Zeman Titusz áldozópap és vértanú",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_09_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Andreja Corsiniho, biskupa",
	"Sv. Ondřeje Corsini, biskupa",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Andrésar Corsini, biskups",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_09_CSA[POCET_JAZYKOV + 1] =
{
	"Bl. Alexie Le Clerc, panny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_10_1_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Gundislava z Amarante, kňaza",
	"Bl. Gundisalva z Amaranta, kněze",
	"",
	"",
	"",
	"Bl. Gundisalva z Amaranta, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_10_2_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Anny od Anjelov Monteagudovej, panny",
	"Bl. Anny od Andělů Monteagudové, panny, mnišky",
	"",
	"",
	"",
	"Bl. Anny od Andělů Monteagudové, panny, mnišky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_11_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Bernarda Scammaccu, kňaza",
	"Bl. Bernarda Scammacca, kněze",
	"",
	"",
	"",
	"Bl. Bernarda Scammacca, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_KRST[POCET_JAZYKOV + 1] = // v nedeľu po 6. januári | (v nedeľu po Zjavení Pána) alebo: ak však táto nedeľa (zrejme Zjavenia Pána) padne na deň 7. alebo 8. januára, ofícium sa slávi v nasledujúci deň
{
	"Krst Pána", // bolo: "Krst Krista Pána"; podľa 3RM opravené bez 'Krista'
	"Křtu Páně",
	"",
	"In Baptismate Domini",
	"",
	"Křtu Páně",
	"Urunk megkeresztelkedése",
	"ru_text",
	"Хрост Пана",
	"Skírn Drottins",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_12_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Bernarda z Corleone, rehoľníka, člena 1. rádu",
	"Sv. Bernarda z Corleone, řeholníka",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_13[POCET_JAZYKOV + 1] =
{
	"Sv. Hilára, biskupa a učiteľa Cirkvi",
	"Sv. Hilaria, biskupa a učitele církve",
	"",
	"S. Hilarii, episcopi et Ecclesiæ doctoris",
	"",
	"Sv. Hilaria, biskupa a učitele církve",
	"Szent Hiláriusz (Vidor) püspök és egyháztanító",
	"ru_text",
	"Св. Гілярыя, біскупа і доктара Касцёла",
	"Hl. Hilaríusar, biskups og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_14_CSSR[POCET_JAZYKOV + 1] =
{
	"Bl. Petra Dondersa, kňaza",
	"Bl. Petra Donderse, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_14_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Odorika z Pordenone, kňaza, člena 1. rádu",
	"Bl. Odorika z Pordenone, kněze 1. řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_14_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Sv. Bohumíra, rehoľníka z našej rehole",
	"Sv. Gotfrída, řeholníka z premonstrátského řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_15_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Remete Szent Pál szerzetes",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_15_SVD[POCET_JAZYKOV + 1] =
{
	"Sv. Arnolda Janssena, kňaza a zakladateľa troch misijných rehoľných spoločností",
	"",
	"",
	"",
	"",
	"",
	"Janssen Szent Arnold áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_15_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Alojza Variaru, kňaza",
	"Bl. Aloise Variary, kněze",
	"",
	"",
	"",
	"",
	"Boldog Variara Alajos áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_16_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Berarda, kňaza, a spoločníkov, prvých františkánskych mučeníkov",
	"Sv. Berarda, kněze, a druhů, mučedníků",
	"",
	"",
	"",
	"",
	"Szent Berárd, pap és vértanú társai az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_17[POCET_JAZYKOV + 1] =
{
	"Sv. Antona, opáta",
	"Sv. Antonína, opata",
	"",
	"S. Antonii, abbatis",
	"",
	"Sv. Antonína, opata",
	"Szent Antal apát",
	"ru_text",
	"Св. Антонія, абата",
	"Hl. Antóníusar ábóta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_18_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Panny Marie, Matky jednoty křesťanů",
	"",
	"",
	"",
	"Panny Marie, Matky jednoty křesťanů",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_18[POCET_JAZYKOV + 1] =
{
	"Sv. Margity Uhorskej, panny",
	"",
	"",
	"",
	"",
	"Sv. Markéty Uherské, panny, mnišky", // CZOP 19. januára kvôli text_JAN_18_CZ
	"Árpád-házi Szent Margit szűz",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_19_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Andreja z Peschiera, kňaza",
	"Bl. Ondřeje z Peschiery, kněze",
	"",
	"",
	"",
	"Bl. Ondřeje z Peschiery, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_19_SJ[POCET_JAZYKOV + 1] =
{
	"Bl. Jakuba Salèsa a Viliama Saultemouchea, " HTML_LINE_BREAK "Ignáca de Azevedo a spoločníkov, " HTML_LINE_BREAK "Jakuba Bonnauda a spoločníkov, mučeníkov",
	"Bl. Ignáce de Azevedo, kněze, a druhů; " HTML_LINE_BREAK "bl. Jakuba Salèse, kněze, a Viléma Saultemouche, řeholníka, mučedníků",
	"",
	"",
	"",
	"_",
	"Ogilvie Szent János áldozópap; " HTML_LINE_BREAK "Boldog De Azevedo Ignác áldozópap és társai; " HTML_LINE_BREAK "Boldog Salės Jakab áldozópap; " HTML_LINE_BREAK "Boldog Saultemouche Vilmos szerzetes, vértanúk",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_20_1[POCET_JAZYKOV + 1] =
{
	"Sv. Fabiána, pápeža a mučeníka",
	"Sv. Fabiána, papeže a mučedníka",
	"",
	"S. Fabiani, papæ et martyris",
	"",
	"Sv. Fabiána, papeže a mučedníka",
	"Szent Fábián pápa és vértanú",
	"ru_text",
	"Св. Фабіяна, папы і мучаніка",
	"Hl. Fabíans, páfa og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_20_2[POCET_JAZYKOV + 1] =
{
	"Sv. Šebastiána, mučeníka",
	"Sv. Šebestiána, mučedníka",
	"",
	"S. Sebastiani, martyris",
	"",
	"Sv. Šebestiána, mučedníka",
	"Szent Sebestyén vértanú",
	"ru_text",
	"Св. Себасцьяна, мучаніка",
	"Hl. Sebastians píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_20_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Jána Krstiteľa Triquerie, kňaza a mučeníka, člena 1. rádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_20_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Esztergomi Boldog Özséb áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_21[POCET_JAZYKOV + 1] =
{
	"Sv. Agnesy, panny a mučenice",
	"Sv. Anežky, panny a mučednice",
	"",
	"S. Agnetis, virginis et martyris",
	"",
	"Sv. Anežky, panny a mučednice",
	"Szent Ágnes szűz és vértanú",
	"ru_text",
	"Св. Агнешкі, панны і мучаніцы",
	"Hl. Agnesar, meyjar og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_22[POCET_JAZYKOV + 1] =
{
	"Sv. Vincenta, diakona a mučeníka",
	"Sv. Vincence, jáhna a mučedníka",
	"",
	"S. Vincentii, diaconi et martyris",
	"",
	"Sv. Vincence, jáhna a mučedníka",
	"Szent Vince diakónus és vértanú",
	"ru_text",
	"Св. Вінцэнта, дыякана і мучаніка",
	"Hl. Vinsentíusar, djákna og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_22_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Antona della Chiesa, kňaza",
	"Bl. Antonína della Chiesa, kněze",
	"",
	"",
	"",
	"Bl. Antonína della Chiesa, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_22_OFM_HU[POCET_JAZYKOV + 1] =
{
	"Bl. Ladislava Battyány-Strattmanna, " HTML_LINE_BREAK "otca rodiny, člena 3. rádu",
	"",
	"",
	"",
	"",
	"",
	"Boldog Batthyány-Strattmann László hitvalló",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_22_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Laury Vicuňovej, dievčaťa",
	"Bl. Laury Vicuňi, panny",
	"",
	"",
	"",
	"",
	"Boldog Vicuña Laura leány",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_23_SK[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Almužníka, biskupa",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_23_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Henricha Suzu, kňaza",
	"Bl. Jindřicha Seuse, kněze",
	"",
	"",
	"",
	"Bl. Jindřicha Seuse, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_24[POCET_JAZYKOV + 1] =
{
	"Sv. Františka Saleského, biskupa a učiteľa Cirkvi",
	"Sv. Františka Saleského, biskupa a učitele církve",
	"",
	"S. Francisci de Sales, episcopi et Ecclesiæ doctoris",
	"",
	"Sv. Františka Saleského, biskupa a učitele církve",
	"Szalézi Szent Ferenc püspök és egyháztanító",
	"ru_text",
	"Св. Францішка Сальскага, біскупа і доктара Касцёла",
	"Hl. Frans frá Sales, biskups og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_24_SDB[POCET_JAZYKOV + 1] =
{
	"Sv. Františka Saleského, biskupa a učiteľa Cirkvi, " HTML_LINE_BREAK "titulárneho patróna Spoločnosti sv. Františka Saleského",
	"Sv. Františka Saleského, biskupa a učitele církve, " HTML_LINE_BREAK "titulárního patrona Společnosti sv. Františka Saleského",
	"",
	"",
	"",
	"",
	"Szalézi Szent Ferenc püspök és egyháztanító, " HTML_LINE_BREAK "a Szalézi Szent Ferenc Társaság névadója és pártfogója",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_25[POCET_JAZYKOV + 1] =
{
	"Obrátenie svätého Pavla, apoštola",
	"Obrácení svatého Pavla, apoštola",
	"",
	"In Conversione S. Pauli, apostoli",
	"",
	"Obrácení svatého Pavla, apoštola",
	"Szent Pál apostol megtérése (Pál fordulása)",
	"ru_text",
	"Навяртанне св. Паўла, апостала",
	"Hátíð sinnaskipta hl. Páls postula",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_25_CM[POCET_JAZYKOV + 1] =
{
	"Obrátenie svätého Pavla, apoštola" HTML_LINE_BREAK "Výročný deň založenia Misijnej spoločnosti",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_26[POCET_JAZYKOV + 1] =
{
	"Sv. Timoteja a Títa, biskupov",
	"Sv. Timoteje a Tita, biskupů",
	"",
	"Ss. Timothei et Titi, episcoporum",
	"",
	"Sv. Timoteje a Tita, biskupů",
	"Szent Timóteus és Szent Titusz püspökök",
	"ru_text",
	"Св. Цімафея і Ціта, біскупаў",
	"Hl. Tímóteusar og Títusar, biskupa",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_27[POCET_JAZYKOV + 1] =
{
	"Sv. Angely Merici, panny",
	"Sv. Anděly Mericiové, panny",
	"",
	"S. Angelæ Merici, virginis",
	"",
	"Sv. Anděly Mericiové, panny",
	"Merici Szent Angéla szűz",
	"ru_text",
	"Св. Анжэлы Мэрычы, панны",
	"Hl. Angelu Merici, meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_27_OSU[POCET_JAZYKOV + 1] =
{
	"Sv. Angely Merici, panny",
	"Sv. Anděly Mericiové, panny",
	"",
	"S. Angelæ Merici, virginis",
	"",
	"Sv. Anděly Mericiové, panny",
	"Merici Szent Angéla szűz",
	"ru_text",
	"Св. Анжэлы Мэрычы, панны",
	"Hl. Angelu Merici, meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_27_BY[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Бл. Юрыя Матулевіча, біскупа",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_27_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Markolína z Forl&#236;, kňaza", // &igrave;
	"Bl. Markolína z Forli, kněze",
	"",
	"",
	"",
	"Bl. Markolína z Forli, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_27_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Henricha de Ossó y Cervello, kňaza",
	"Sv. Jindřicha de Ossó, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Henriks de Ossó y Cervello, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_28[POCET_JAZYKOV + 1] =
{
	"Sv. Tomáša Akvinského, kňaza a učiteľa Cirkvi",
	"Sv. Tomáše Akvinského, kněze a učitele církve",
	"",
	"S. Thomæ de Aquino, presbyteri et Ecclesiæ doctoris",
	"",
	"Sv. Tomáše Akvinského, kněze a učitele církve",
	"Aquinói Szent Tamás áldozópap és egyháztanító",
	"ru_text",
	"Св. Тамаша Аквінскага, прэзбітэра і доктара Касцёла",
	"Hl. Tómasar frá Aquino, prests og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_29_BY[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Бл. Баляславы Марыі Лямэнт, панны",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_29_SVD[POCET_JAZYKOV + 1] =
{
	"Sv. Jozefa Freinademetza, kňaza",
	"",
	"",
	"",
	"",
	"",
	"Freinademetz Szent József áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_29_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Villany delle Botti, matky rodiny",
	"Bl. Villany delle Botti, matky rodiny, terciářky",
	"",
	"",
	"",
	"Bl. Villany delle Botti, matky rodiny, terciářky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_29_OFMCONV[POCET_JAZYKOV + 1] =
{
	"Bl. Františka Zirana, kňaza a mučeníka",
	"Bl. Františka Zirana, kněze a mučedníka",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_30_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Bronislava Markiewicza, kňaza",
	"Bl. Bronislava Markiewicze, kněze",
	"",
	"",
	"",
	"",
	"Boldog Markiewicz Bronisław áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_30_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Hyacinty Mariscottiovej, panny, členky 3. rádu",
	"Sv. Hyacinty Mariscotti, panny", // niekedy aj podľa talianskeho mena: Giacinta Marescotti
	"",
	"",
	"",
	"",
	"Szent Jácinta, szűz a III. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_31[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Boska, kňaza", // Direktórium 2012, str. 72, má: 'Bosca'
	"Sv. Jana Boska, kněze",
	"",
	"S. Ioannis Bosco, presbyteri",
	"",
	"Sv. Jana Boska, kněze",
	"Bosco Szent János áldozópap",
	"ru_text",
	"Св. Яна Боска, прэзбітэра",
	"Hl. Jóhannesar Bosco, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JAN_31_SDB[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Boska, kňaza, otca a učiteľa mládeže, " HTML_LINE_BREAK "zakladateľa Spoločnosti sv. Františka Saleského, " HTML_LINE_BREAK "Inštitútu dcér Márie Pomocnice, " HTML_LINE_BREAK "Združenia saleziánov spolupracovníkov " HTML_LINE_BREAK "a Združenia ctiteľov Panny Márie Pomocnice",
	"Sv. Jana Boska, kněze, otce a učitele mládeže, " HTML_LINE_BREAK "zakladatele Společnosti sv. Františka Saleského, " HTML_LINE_BREAK "Institutu Dcer Panny Marie Pomocnice " HTML_LINE_BREAK "a Salesiánů spolupracovníků",
	"",
	"",
	"",
	"",
	"Bosco Szent János áldozópap, " HTML_LINE_BREAK "a Szalézi Szent Ferenc Társaság, " HTML_LINE_BREAK "a Segítő Szűz Mária Leányai Intézménye, " HTML_LINE_BREAK "a Szalézi Munkatársak Egyesülete és a Szűz Mária, " HTML_LINE_BREAK "a Keresztények Segítsége Egyesülete alapítója",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// --------------- 02 február | february ---------------

const char* text_FEB_01_SDB[POCET_JAZYKOV + 1] =
{
	"Spomienka na všetkých zosnulých spolubratov saleziánov",
	"Připomínka zemřelých salesiánů",
	"",
	"",
	"",
	"",
	"Megemlékezés az összes elhunyt szalézi rendtársról",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_01_CM[POCET_JAZYKOV + 1] =
{
	"Bl. Márie Anny Vaillotovej a Odilie Baumgartenovej, " HTML_LINE_BREAK "panien a mučeníc",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_02[POCET_JAZYKOV + 1] =
{
	"Obetovanie Pána",
	"Uvedení Páně do chrámu",
	"",
	"In Præsentatione Domini",
	"",
	"Uvedení Páně do chrámu",
	"Urunk bemutatása (Gyertyaszentelő Boldogasszony)",
	"ru_text",
	"Ахвяраванне Пана",
	"Kyndilmessa (Jesús færður Drottni í musterinu)",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_03_1[POCET_JAZYKOV + 1] =
{
	"Sv. Blažeja, biskupa a mučeníka",
	"Sv. Blažeje, biskupa a mučedníka",
	"",
	"S. Blasii, episcopi et martyris",
	"",
	"Sv. Blažeje, biskupa a mučedníka",
	"Szent Balázs püspök és vértanú",
	"ru_text",
	"Св. Блажэя, біскупа і мучаніка",
	"Hl. Blasíusar, biskups og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_03_2[POCET_JAZYKOV + 1] =
{
	"Sv. Oskara, biskupa",
	"Sv. Ansgara, biskupa",
	"",
	"S. Ansgarii, episcopi",
	"",
	"Sv. Ansgara, biskupa",
	"Szent Anszgár (Oszkár) püspök",
	"ru_text",
	"Св. Анзгара, біскупа",
	"Hl. Ansgars biskups",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_03_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Petra z Ruff&#236;a, Antona Pavoniho a Bartolomeja Cerveriho, kňazov a mučeníkov", // &igrave;
	"Bl. Petra z Ruffìa, Antonína Pavoniho a Bartoloměje Cerveriho, kněží a mučedníků",
	"",
	"",
	"",
	"Bl. Petra z Ruffìa, Antonína Pavoniho a Bartoloměje Cerveriho, kněží a mučedníků",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_04_OP[POCET_JAZYKOV + 1] =
{
	"Sv. Kataríny de’ Ricci, panny",
	"Sv. Kateřiny z Ricci, panny, řeholnice",
	"",
	"",
	"",
	"Sv. Kateřiny z Ricci, panny, řeholnice",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_04_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Jána de Brito, kňaza a mučeníka; " HTML_LINE_BREAK "bl. Rudolfa Acquavivu, kňaza a spoločníkov, mučeníkov; " HTML_LINE_BREAK "bl. Františka Pacheca, Karola Spinolu, kňazov a spoločníkov, mučeníkov",
	"Sv. Jana de Brito, kněze; " HTML_LINE_BREAK "bl. Rudolfa Acquavivy, kněze, a druhů, mučedníků",
	"",
	"",
	"",
	"",
	"De Brito Szent János, áldozópap, " HTML_LINE_BREAK "Boldog Acquviva Rudolf áldozópap és társai, vértanúk",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_04_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Jozefa z Leonissy, kňaza, člena 1. rádu",
	"Sv. Josefa z Leonessy, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_04_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Sv. Fridricha, opáta z našej rehole",
	"Sv. Bedřicha, opata z premonstrátského řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_04_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Máriu Eugena od Dieťaťa Ježiša, kňaza",
	"Bl. Marie-Eugena od Dítěte Ježíše, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_05[POCET_JAZYKOV + 1] =
{
	"Sv. Agáty, panny a mučenice", // direktóriá uvádzajú Agáta s dlhým "á"; LH s krátkym "a" Agata
	"Sv. Agáty, panny a mučednice",
	"",
	"S. Agathæ, virginis et martyris",
	"",
	"Sv. Agáty, panny a mučednice",
	"Szent Ágota szűz és vértanú",
	"ru_text",
	"Св. Агаты, панны і мучаніцы",
	"Hl. Agötu, meyjar og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_06[POCET_JAZYKOV + 1] =
{
	"Sv. Pavla Mikiho a spoločníkov, mučeníkov",
	"Sv. Pavla Mikiho a druhů, mučedníků",
	"",
	"Ss. Pauli Miki et sociorum, martyrum",
	"",
	"Sv. Pavla Mikiho a druhů, mučedníků",
	"Miki Szent Pál és társai vértanúk",
	"ru_text",
	"Св. Паўла Мікі і паплечнікаў, мучанікаў",
	"Hl. Páls Miki og félaga, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_06_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Pavla Mikiho, rehoľníka, a jeho spoločníkov, mučeníkov",
	"Sv. Pavla Mikiho, řeholníka, a druhů; " HTML_LINE_BREAK "bl. Karla Spinoly a Šebestiána Kimury, kněží, a druhů, " HTML_LINE_BREAK "a bl. Petra Kibe Kasuiho, kněze, a druhů, mučedníků",
	"",
	"",
	"",
	"",
	"Miki Szent Pál szerzetes és társai; " HTML_LINE_BREAK "Boldog Spinola Károly és Kimura Sebestyén, áldozópapok és társaik, " HTML_LINE_BREAK "Boldog Kibe Kasui Péter áldozópap és társai",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_06_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Petra Baptistu, kňaza, a spoločníkov, františkánskych mučeníkov",
	"Sv. Petra Křtitele, Pavla Mikiho a druhů, mučedníků",
	"",
	"",
	"",
	"",
	"Keresztelő Szent Péter, Miki Pál és vértanú társai",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_07_OP[POCET_JAZYKOV + 1] =
{
	"Spomienka na zosnulých otcov a matky členov rehole",
	"",
	"",
	"",
	"",
	"Vzpomínka zemřelých otců a matek členů Řádu kazatelů",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_07_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Pia IX., pápeža",
	"Bl. Pia IX., papeže",
	"",
	"",
	"",
	"",
	"Boldog IX. Piusz pápa",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_07_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Kolety z Corbie, panny, členky 2. rádu",
	"Sv. Kolety z Corbie, panny",
	"",
	"",
	"",
	"",
	"Szent Koléta, szűz a II. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_08_1[POCET_JAZYKOV + 1] =
{
	"Sv. Hieronyma Emilianiho",
	"Sv. Jeronýma Emilianiho",
	"",
	"S. Hieronymi Emiliani",
	"",
	"Sv. Jeronýma Emilianiho",
	"Emiliáni Szent Jeromos",
	"ru_text",
	"Св. Гераніма Эміліяні",
	"Hl. Hieronýmus Emilíani",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_08_2[POCET_JAZYKOV + 1] =
{
	"Sv. Jozefíny Bakhity, panny",
	"Sv. Josefiny Bakhity, panny",
	"",
	"S. Iosephinæ Bakhita, virginis",
	"",
	"Sv. Josefiny Bakhity, panny",
	"Bakhita Szent Jozefina szűz",
	"ru_text",
	"Св. Жазэфіны Бакіты, панны",
	"Hl. Jósefínu Bakhita, meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_09_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Euzébie Palominovej-Yenesovej, panny",
	"Bl. Eusebie Palomino Yenesové, panny",
	"",
	"",
	"",
	"",
	"Boldog Palomino Yenes Eusebia szűz",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_09_OFMCAP[POCET_JAZYKOV + 1] =
{
	"",
	"Bl. Leopolda z Alpandeire, řeholníka", // (Marquez-Sánchez)
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_10[POCET_JAZYKOV + 1] =
{
	"Sv. Školastiky, panny",
	"Sv. Scholastiky, panny",
	"",
	"S. Scholasticæ, virginis",
	"",
	"Sv. Scholastiky, panny",
	"Szent Skolasztika szűz",
	"ru_text",
	"Св. Схалястыкі, панны",
	"Hl. Skólastíku, meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_10_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Bl. Huga, prvého opáta v Premóntré",
	"Bl. Huga, opata z premonstrátského řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_11[POCET_JAZYKOV + 1] =
{
	"Prebl. Panny Márie Lurdskej",
	"Panny Marie Lurdské",
	"",
	"Beatæ Mariæ Virginis de Lourdes",
	"",
	"Panny Marie Lurdské",
	"A Lourdes-i Boldogságos Szűz Mária",
	"ru_text",
	"Найсвяцейшай Панны Марыі з Люрда",
	"Hl. Guðsmóður frá Lourdes",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_12_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Reginalda Orleánskeho, kňaza",
	"",
	"",
	"",
	"",
	"Bl. Reginalda z Orleansu, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_13_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Jordána Saského, kňaza",
	"",
	"",
	"",
	"",
	"Bl. Jordána Saského, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_14[POCET_JAZYKOV + 1] =
{
	"Sv. Cyrila, mnícha, a Metoda, biskupa", // (na Slovensku sa slávi 5. júla) | odstránený popis "patrónov Európy"
	"(slaví se 5. června)",
	"",
	"Ss. Cyrilli, monachi, et Methodii, episcoporum",
	"",
	"",
	"Szent Cirill szerzetes és Szent Metód püspök, " HTML_LINE_BREAK "Európa társvédőszentjei",
	"ru_text",
	"Св. Кірыла, мніха, і Мятода, біскупа, " HTML_LINE_BREAK "апекуноў Еўропы",
	"Hl. Kýrils munks og hl. Methódíusar biskups, " HTML_LINE_BREAK "verndardýrlinga Evrópu",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_15_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Klaudia La Colombièra, kňaza",
	"Sv. Klaudia la Colombière, kněze",
	"",
	"",
	"",
	"",
	"La Colombiėre Szent Kolos áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_15_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Bl. Bedřicha Bachsteina a druhů, mučedníků",
	"",
	"",
	"",
	"Bl. Bedřicha Bachsteina a druhů, mučedníků",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_16_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Mikuláša Pagliu, kňaza", // SK OP: 13FEB
	"Bl. Mikuláše Paglia, kněze",
	"",
	"",
	"",
	"Bl. Mikuláše Paglia, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_17[POCET_JAZYKOV + 1] =
{
	"Siedmich svätých zakladateľov " HTML_LINE_BREAK "rehole Služobníkov prebl. Panny Márie", // 3RM: doplnené "PREBLAHOSLAVENEJ" P. M.
	"Sv. Alexia a druhů, řeholníků",
	"",
	"Ss. Septem Fundatorum " HTML_LINE_BREAK "Ordinis Servorum B. M. V.",
	"",
	"Sv. Alexia a druhů, řeholníků",
	"A szervita rend hét szent alapítója",
	"ru_text",
	"Св. сямі Заснавальнікаў ордэна " HTML_LINE_BREAK "Слугаў Найсвяцейшай Панны Марыі (сэрвітаў)",
	"Sjö stofnenda Servítareglunnar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_17_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Sv. Evermoda, biskupa z našej rehole",
	"Sv. Evermoda, biskupa z premonstrátského řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_18_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Siedmich svätých zakladateľov rehole Služobníkov Panny Márie",
	"Sv. sedmi zakladatelů řádu servitů",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_18_CM[POCET_JAZYKOV + 1] =
{
	"Sv. Františka Regisa Cleta " HTML_LINE_BREAK "a Augustína Zhao Ronga, kňazov, " HTML_LINE_BREAK "a spoločníkov, mučeníkov", // moved to 09JUL
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_18_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Jána (Angelika) z Fiesole, kňaza",
	"Bl. Angelica neboli Jana z Fiesole, kněze",
	"",
	"",
	"",
	"Bl. Angelica neboli Jana z Fiesole, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_19_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Alvara z Kordovy, kňaza",
	"Bl. Alvara z Cordoby, kněze",
	"",
	"",
	"",
	"Bl. Alvara z Cordoby, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_19_OFM[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Piacenzai Szent Konrád, remete a III. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_20_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Krištofa z Milána, kňaza",
	"Bl. Kryštofa z Milána, kněze",
	"",
	"",
	"",
	"Bl. Kryštofa z Milána, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_21[POCET_JAZYKOV + 1] =
{
	"Sv. Petra Damianiho, biskupa a učiteľa Cirkvi",
	"Sv. Petra Damianiho, biskupa a učitele církve",
	"",
	"S. Petri Damiani, episcopi et Ecclesiæ doctoris",
	"",
	"Sv. Petra Damianiho, biskupa a učitele církve",
	"Damiáni Szent Péter püspök és egyháztanító",
	"ru_text",
	"Св. Пятра Дам'яна, біскупа і доктара Касцёла",
	"Hl. Péturs Damíanus, biskups og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_22[POCET_JAZYKOV + 1] =
{
	"Katedra sv. Petra, apoštola",
	"Stolce svatého Petra, apoštola",
	"",
	"Cathedræ S. Petri Apostoli",
	"",
	"Stolce svatého Petra, apoštola",
	"Szent Péter apostol székfoglalása",
	"ru_text",
	"Катэдры св. Пятра, апостала",
	"Pétursmessa á vetri, biskupsstóll Péturs postula",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_23[POCET_JAZYKOV + 1] =
{
	"Sv. Polykarpa, biskupa a mučeníka",
	"Sv. Polykarpa, biskupa a mučedníka",
	"",
	"S. Polycarpi, episcopi et martyris",
	"",
	"Sv. Polykarpa, biskupa a mučedníka",
	"Szent Polikárp püspök és vértanú",
	"ru_text",
	"Св. Палікарпа, біскупа і мучаніка",
	"Hl. Polykarps, biskups og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_24_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Konštanca z Fabriana, kňaza",
	"Bl. Konstance z Fabriana, kněze",
	"",
	"",
	"",
	"Bl. Konstance z Fabriana, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_24_OP_2[POCET_JAZYKOV + 1] =
{
	"Bl. Ascensiony Nicol Goñi, panny a rehoľníčky",
	"Bl. Ascensiony Nicol Goñi, panny, řeholnice",
	"",
	"",
	"",
	"Bl. Ascensiony Nicol Goñi, panny, řeholnice",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_24_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Jozefy Naval Girbés, panny",
	"Bl. Josefy Naval Girbes, panny", // 06NOV
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Bl. Jósefu Naval Girbés", // 07NOV?
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_25_SDB[POCET_JAZYKOV + 1] =
{
	"Sv. Alojza Versigliu, biskupa, a Kalixta Caravaria, kňaza, " HTML_LINE_BREAK "prvých saleziánskych mučeníkov",
	"Sv. Aloise Versiglii, biskupa, a Kalista Caravaria, kněze, " HTML_LINE_BREAK "prvních salesiánských mučedníků",
	"",
	"",
	"",
	"",
	"Versiglia Szent Alajos, püspök és Caravario Szent Kallixtusz, áldozópap, " HTML_LINE_BREAK "szalézi vértanúk",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_26_SCHP[POCET_JAZYKOV + 1] =
{
	"Sv. Pauly Montal, panny a rehoľníčky, " HTML_LINE_BREAK "zakladateľky Kongregácie sestier piaristiek",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_FEB_27[POCET_JAZYKOV + 1] =
{
	"Sv. Gregora z Nareku, opáta a učiteľa Cirkvi",
	"Sv. Řehoře z Nareku, opata a učitele církve",
	"",
	"S. Gregorii Narecensis, abbatis et Ecclesiæ doctoris",
	"",
	"Sv. Řehoře z Nareku, opata a učitele církve",
	"Nareki Szent Gergely apát és egyháztanító",
	"",
	"",
	"Hl. Gregoríusar frá Narec, ábóta og kirkjufræðara", // ToDo
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// --------------- 00 pohyblivé slávenia ---------------

const char* text_POPOLCOVA_STREDA[POCET_JAZYKOV + 1] =
{
	"Popolcová streda",
	"Popeleční středa",
	"Ash Wednesday",
	"Feria IV Cinerum",
	"",
	"Popeleční středa",
	"Hamvazószerda",
	"ru_text",
	"Папяльцовая серада",
	"Öskudagur",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// --------------- 03 marec | march ---------------

const char* text_MAR_02_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Anežky Českej, panny, členky 2. rádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_04[POCET_JAZYKOV + 1] =
{
	"Sv. Kazimíra",
	"Sv. Kazimíra",
	"",
	"S. Casimiri",
	"",
	"Sv. Kazimíra",
	"Szent Kázmér",
	"ru_text",
	"Св. Казіміра",
	"Hl. Kasimírs, prins",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_04_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Boldog Meszlényi Zoltán püspök és vértanú",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_07[POCET_JAZYKOV + 1] =
{
	"Sv. Perpetuy a Felicity, mučeníc",
	"Sv. Perpetuy a Felicity, mučednic",
	"",
	"Ss. Perpetuæ et Felicitatis, martyrum",
	"",
	"Sv. Perpetuy a Felicity, mučednic",
	"Szent Perpétua és Felicitász vértanúk",
	"ru_text",
	"Св. Пэрпэтуі і Фэліцыты, мучаніц",
	"Hl. Perpetúu og hl. Felisítas, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_08[POCET_JAZYKOV + 1] =
{
	"Sv. Jána od Boha, rehoľníka", // kedysi: "Sv. Jána z Boha, rehoľníka"
	"Sv. Jana z Boha, řeholníka",
	"",
	"S. Ioannis a Deo, religiosi",
	"",
	"Sv. Jana z Boha, řeholníka",
	"Istenes Szent János szerzetes",
	"ru_text",
	"Св. Яна Божага, законніка",
	"Hl. Jóhannesar af Guði, reglubróður",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_08_SCHP[POCET_JAZYKOV + 1] =
{
	"Sv. Faustina Mígueza, rehoľníka, " HTML_LINE_BREAK "zakladateľa Inštitútu dcér Božskej Pastierky",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_09[POCET_JAZYKOV + 1] =
{
	"Sv. Františky Rímskej, rehoľníčky",
	"Sv. Františky Římské, řeholnice",
	"",
	"S. Franciscæ Romanæ, religiosæ",
	"",
	"Sv. Františky Římské, řeholnice",
	"Római Szent Franciska szerzetesnő",
	"ru_text",
	"Св. Францішкі Рымскай, законніцы",
	"Hl. Fransisku frá Róm, ekkju og reglusystur",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_10_SK[POCET_JAZYKOV + 1] =
{
	"Výročie posviacky katedrálneho chrámu " HTML_LINE_BREAK "sv. Martina z Tours",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_10_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Sv. Jana Ogilvie, kněze a mučedníka",
	"",
	"",
	"",
	"Sv. Jana Ogilvie, kněze a mučedníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_12_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Angely Salawovej, panny, členky 3. rádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_15_CSSR[POCET_JAZYKOV + 1] =
{
	"Sv. Klementa Máriu Hofbauera, kňaza",
	"Sv. Klementa Marie Hofbauera (Dvořáka), kněze", // CZ CSsR: 20MAJ
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_17[POCET_JAZYKOV + 1] =
{
	"Sv. Patrika, biskupa",
	"Sv. Patrika, biskupa",
	"",
	"S. Patricii, episcopi",
	"",
	"Sv. Patrika, biskupa",
	"Szent Patrik püspök",
	"ru_text",
	"Св. Патрыка, біскупа",
	"Hl. Patreks, biskups",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_17_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"A győri Könnyező Szűz Mária",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_18[POCET_JAZYKOV + 1] =
{
	"Sv. Cyrila Jeruzalemského, biskupa a učiteľa Cirkvi",
	"Sv. Cyrila Jeruzalémského, biskupa a učitele církve",
	"",
	"S. Cyrilli Hierosolymitani, episcopi et Ecclesiæ doctoris",
	"",
	"Sv. Cyrila Jeruzalémského, biskupa a učitele církve",
	"Jeruzsálemi Szent Cirill püspök és egyháztanító",
	"ru_text",
	"Св. Кірыла Ерузалемскага, біскупа і доктара Касцёла",
	"Hl. Kýrils frá Jerúsalem, biskups og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_18_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Salvatora z Horty, kňaza, člena 1. rádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_18_SCHP[POCET_JAZYKOV + 1] =
{
	"Bl. Celestiny Donati, panny, " HTML_LINE_BREAK "zakladateľky sestier Kalazanciánok",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_19[POCET_JAZYKOV + 1] =
{
	"Sv. Jozefa, ženícha prebl. Panny Márie", // 3RM: "PREBLAHOSLAVENEJ"
	"Sv. Josefa, Snoubence Panny Marie",
	"",
	"S. Ioseph, Sponsi Beatæ Mariæ Virginis",
	"",
	"Sv. Josefa, Snoubence Panny Marie",
	"Szent József, a Boldogságos Szűz Mária jegyese",
	"ru_text",
	"Св. Юзафа, абранніка Найсвяцейшай Панны Марыі",
	"Hl. Jósefs, brúðguma sællar Maríu meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_19_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Jozefa, ženícha prebl. Panny Márie, " HTML_LINE_BREAK "patróna Spoločnosti Ježišovej",
	"Sv. Josefa, Snoubence Panny Marie, " HTML_LINE_BREAK "patrona Tovaryšstva Ježíšova",
	"",
	"S. Ioseph, Sponsi Beatæ Mariæ Virginis",
	"",
	"Sv. Josefa, Snoubence Panny Marie, " HTML_LINE_BREAK "patrona Tovaryšstva Ježíšova",
	"Szent József, a Boldogságos Szűz Mária jegyese, " HTML_LINE_BREAK "Jézus Társaságának védőszentje",
	"",
	"Св. Юзафа, абранніка Найсвяцейшай Панны Марыі",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_23[POCET_JAZYKOV + 1] =
{
	"Sv. Turibia de Mongrovejo, biskupa",
	"Sv. Turibia z Mongroveja, biskupa",
	"",
	"S. Turibii de Mogrovejo, episcopi",
	"",
	"Sv. Turibia z Mongroveja, biskupa",
	"Mongrovejói Szent Turibiusz püspök",
	"ru_text",
	"Св. Турыбія Мангравэха, біскупа",
	"Hl. Túribíusar frá Mogrovejo, biskups",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAR_25[POCET_JAZYKOV + 1] =
{
	"Zvestovanie Pána",
	"Zvěstování Páně",
	"",
	"In Annuntiatione Domini",
	"",
	"Zvěstování Páně",
	"Urunk születésének hírüladása (Gyümölcsoltó Boldogasszony)",
	"ru_text",
	"Звеставанне Пана",
	"Boðun Drottins",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// --------------- 04 apríl | april ---------------

const char* text_APR_01_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Jozefa Girottiho, kňaza a mučeníka",
	"Bl. Josefa Girottiho, kněze a mučedníka",
	"",
	"",
	"",
	"Bl. Josefa Girottiho, kněze a mučedníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_02[POCET_JAZYKOV + 1] =
{
	"Sv. Františka z Paoly, pustovníka",
	"Sv. Františka z Pauly, poustevníka",
	"",
	"S. Francisci de Paola, eremitæ",
	"",
	"Sv. Františka z Pauly, poustevníka",
	"Paolai Szent Ferenc remete",
	"ru_text",
	"Св. Францішка з Паолы, пустэльніка",
	"Hl. Frans frá Paola, einsetumanns",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_04[POCET_JAZYKOV + 1] =
{
	"Sv. Izidora, biskupa a učiteľa Cirkvi",
	"Sv. Izidora, biskupa a učitele církve",
	"",
	"S. Isidori, episcopi et Ecclesiæ doctoris",
	"",
	"Sv. Izidora, biskupa a učitele církve",
	"Szent Izidor püspök és egyháztanító",
	"ru_text",
	"Св. Ізыдора, біскупа і доктара Касцёла",
	"Hl. Isidors, biskups og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_05[POCET_JAZYKOV + 1] =
{
	"Sv. Vincenta Ferrera, kňaza",
	"Sv. Vincence Ferrerského, kněze",
	"",
	"S. Vincentii Ferrer, presbyteri",
	"",
	"Sv. Vincence Ferrerského, kněze",
	"Ferrer Szent Vince áldozópap",
	"ru_text",
	"Св. Вінцэнта Фэрэра, прэзбітэра",
	"Hl. Vincents Ferrer, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_07[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Krstiteľa de la Salle, kňaza",
	"Sv. Jana Křtitele de la Salle, kněze",
	"",
	"S. Ioannis Baptistæ de la Salle, presbyteri",
	"",
	"Sv. Jana Křtitele de la Salle, kněze",
	"De la Salle Szent János áldozópap",
	"ru_text",
	"Св. Жана Батыста Сальскага, прэзбітэра",
	"Hl. Jóhannesar Baptist de la Salle, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_10_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Antona Neyrota, kňaza a mučeníka",
	"Bl. Antonína Neyrota, kněze a mučedníka",
	"",
	"",
	"",
	"Bl. Antonína Neyrota, kněze a mučedníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_11[POCET_JAZYKOV + 1] =
{
	"Sv. Stanislava, biskupa a mučeníka",
	"Sv. Stanislava, biskupa a mučedníka",
	"",
	"S. Stanislai, episcopi et martyris",
	"",
	"Sv. Stanislava, biskupa a mučedníka",
	"Szent Szaniszló püspök és vértanú",
	"ru_text",
	"Св. Станіслава, біскупа і мучаніка",
	"Hl. Stanislás, biskups og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_13[POCET_JAZYKOV + 1] =
{
	"Sv. Martina I., pápeža a mučeníka",
	"Sv. Martina I., papeže a mučedníka",
	"",
	"S. Martini I, papæ et martyris",
	"",
	"Sv. Martina I., papeže a mučedníka",
	"Szent I. Márton pápa és vértanú",
	"ru_text",
	"Св. Марціна I, папы і мучаніка",
	"Hl. Marteins I., páfa og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_13_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Margity z Citt&#224; di Castello, panny", // &agrave;
	"Bl. Markéty z Citta di Castello, panny, terciářky",
	"",
	"",
	"",
	"Bl. Markéty z Citta di Castello, panny, terciářky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_14_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Petra Gonzáleza, kňaza",
	"Bl. Petra Gonzaleze, kněze",
	"",
	"",
	"",
	"Bl. Petra Gonzaleze, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_16[POCET_JAZYKOV + 1] =
{
	"Sv. Márie Bernadety Soubirousovej, panny",
	"Sv. Marie Bernadetty Soubirous, panny",
	"",
	"S. Mariæ Bernardæ Soubirous, virginis",
	"",
	"Sv. Marie Bernadetty Soubirous, panny",
	"Soubirous Szent Mária Bernadett szűz",
	"",
	"",
	"Heilög María Bernadetta Soubirous, meyja",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_17_1_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Kláry Gambacortovej, rehoľníčky",
	"Bl. Kláry Gambacortové, vdovy, mnišky",
	"",
	"",
	"",
	"Bl. Kláry Gambacortové, vdovy, mnišky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_17_2_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Márie Manciniovej, rehoľníčky",
	"Bl. Marie Manciniové, vdovy, mnišky",
	"",
	"",
	"",
	"Bl. Marie Manciniové, vdovy, mnišky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_17_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Baptistu Spagnoliho, kňaza",
	"Bl. Baptisty Spagnoli, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_18_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Márie od Vtelenia, rehoľníčky",
	"Bl. Marie od Vtělení (Acarie), řeholnice",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Bl. Maríu af holdtekjunni, karmelnunnu", // IS
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_19_1_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Isnarda z Chiampa, kňaza",
	"Bl. Isnarda z Chiampa, kněze",
	"",
	"",
	"",
	"Bl. Isnarda z Chiampa, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_19_2_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Sybiliny Biscossiovej, panny",
	"Bl. Sibylliny Biscossiové, panny, terciářky",
	"",
	"",
	"",
	"Bl. Sibylliny Biscossiové, panny, terciářky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_20_OP[POCET_JAZYKOV + 1] =
{
	"Sv. Agnesy z Montepulciana, panny",
	"Sv. Anežky z Montepulciana, panny, mnišky",
	"",
	"",
	"",
	"Sv. Anežky z Montepulciana, panny, mnišky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_21[POCET_JAZYKOV + 1] =
{
	"Sv. Anzelma, biskupa a učiteľa Cirkvi",
	"Sv. Anselma, biskupa a učitele církve",
	"",
	"S. Anselmi, episcopi et Ecclesiæ doctoris",
	"",
	"Sv. Anselma, biskupa a učitele církve",
	"Szent Anzelm püspök és egyháztanító",
	"ru_text",
	"Св. Анзэльма, біскупа і доктара Касцёла",
	"Hl. Anselms, biskups og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_21_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Konráda z Parzhamu, rehoľníka, člena 1. rádu",
	"Sv. Konráda z Parzhamu, řeholníka",
	"",
	"",
	"",
	"",
	"Parzhami Szent Konrád, szerzetes az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_22_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Eliáša z Assisi, rehoľníka",
	"Bl. Jiljí z Assisi, řeholníka",
	"",
	"",
	"",
	"Bl. Jiljí z Assisi, řeholníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_22_SJ[POCET_JAZYKOV + 1] =
{
	"Prebl. Panny Márie, Matky Spoločnosti Ježišovej",
	"Panny Marie, Matky Tovaryšstva Ježíšova",
	"",
	"",
	"",
	"Panny Marie, Matky Tovaryšstva Ježíšova",
	"Boldogságos Szűz Mária, Jézus Társasága Édesanyja",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_23[POCET_JAZYKOV + 1] =
{
	"Sv. Vojtecha, biskupa a mučeníka",
	"Sv. Vojtěcha, biskupa a mučedníka, " HTML_LINE_BREAK "hlavního patrona pražské arcidiecéze",
	"",
	"S. Adalberti, episcopi et martyris",
	"",
	"Sv. Vojtěcha, biskupa a mučedníka",
	"Szent Adalbert (Béla) püspök és vértanú",
	"ru_text",
	"Св. Адальбэрта (Войцеха), біскупа і мучаніка",
	"Hl. Aðalberts, biskups og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_23_HU[POCET_JAZYKOV + 1] =
{
	"Sv. Vojtecha, biskupa a mučeníka",
	"Sv. Vojtěcha, biskupa a mučedníka",
	"",
	"S. Adalberti, episcopi et martyris",
	"",
	"Sv. Vojtěcha, biskupa a mučedníka",
	"Szent Adalbert (Béla) püspök és vértanú, " HTML_LINE_BREAK "az Esztergomi főegyházmegye védőszentje",
	"",
	"Св. Адальбэрта (Войцеха), біскупа і мучаніка",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_23_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Egida z Assisi, rehoľníka, člena 1. rádu",
	"",
	"",
	"",
	"",
	"",
	"Assisi Boldog Egyed, szerzetes az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_24_1[POCET_JAZYKOV + 1] =
{
	"Sv. Juraja, mučeníka", // SK, CZ: 24APR; general calendar: 23APR
	"Sv. Jiří, mučedníka",
	"",
	"S. Georgii, martyris",
	"",
	"Sv. Jiří, mučedníka",
	"Szent György vértanú",
	"ru_text",
	"Св. Юрыя, мучаніка",
	"Hl. Georgs, píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_24_2[POCET_JAZYKOV + 1] =
{
	"Sv. Fidéla zo Sigmaringenu, kňaza a mučeníka",
	"Sv. Fidela ze Sigmaringy, kněze a mučedníka",
	"",
	"S. Fidelis a Sigmaringen, presbyteri et martyris",
	"",
	"Sv. Fidela ze Sigmaringy, kněze a mučedníka",
	"Sigmaringeni Szent Fidél áldozópap és vértanú",
	"ru_text",
	"Св. Фідэля Сігмарынгенскага, прэзбітэра і мучаніка",
	"Hl. Fídelis frá Sigmaringen, prests og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_24_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Fidela zo Sigmaringenu, kňaza a mučeníka, člena 1. rádu",
	"Sv. Fidela ze Sigmaringy, kněze a mučedníka",
	"",
	"",
	"",
	"",
	"Sigmaringeni Szent Fidél, pap és vértanú az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_24_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Terézie Márie od Kríža (Manetti), panny",
	"Bl. Terezie Marie od Kříže (Terezie Manetti), panny", // 23APR
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Bl. Teresu Maríu af krossi, meyjar", // IS
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_24_AUG[POCET_JAZYKOV + 1] =
{
	"Obrátenie nášho svätého otca Augustína", // SK CSA
	"Obrácení našeho otce svatého Augustina, " HTML_LINE_BREAK "biskupa a učitele církve", // CZ OPraem
	"",
	"",
	"",
	"Obrácení sv. Augustina", // CZ OP
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_25[POCET_JAZYKOV + 1] =
{
	"Sv. Marka, evanjelistu",
	"Sv. Marka, evangelisty",
	"",
	"S. Marci, evangelistæ",
	"",
	"Sv. Marka, evangelisty",
	"Szent Márk evangélista",
	"ru_text",
	"Св. Марка, евангеліста",
	"Hl. Markúsar guðspjallamanns",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_26_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Sv. Ludolfa, biskupa a mučeníka z našej rehole",
	"Sv. Ludolfa, biskupa a mučedníka " HTML_LINE_BREAK "z premonstrátského řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_26_CM[POCET_JAZYKOV + 1] =
{
	"Prenesenie pozostatkov sv. Vincenta de Paul",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_26_OSU[POCET_JAZYKOV + 1] =
{
	"Panny Márie, Matky dobrej rady",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_27_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Petra Kanízia, kňaza a učiteľa Cirkvi",
	"Sv. Petra Kanisia, kněze a učitele církve",
	"",
	"",
	"",
	"Sv. Petra Kanisia, kněze a učitele církve",
	"Kaníziusz Szent Péter, áldozópap és egyháztanító, " HTML_LINE_BREAK "a Közép- és Keleteurópai asszisztencia védőszentje",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_27_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Hosanny Kotorskej, panny",
	"Bl. Hosanny z Kotoru, panny, terciářky",
	"",
	"",
	"",
	"Bl. Hosanny z Kotoru, panny, terciářky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_28_1[POCET_JAZYKOV + 1] =
{
	"Sv. Petra Chanela, kňaza a mučeníka",
	"Sv. Petra Chanela, kněze a mučedníka",
	"",
	"S. Petri Chanel, presbyteri et martyris",
	"",
	"Sv. Petra Chanela, kněze a mučedníka",
	"Chanel Szent Péter áldozópap és vértanú",
	"ru_text",
	"Св. Пятра Шанэля, прэзбітэра і мучаніка",
	"Hl. Péturs Chanel, prests og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_28_2[POCET_JAZYKOV + 1] =
{
	"Sv. Ľudovíta Máriu Grigniona z Montfortu, kňaza",
	"Sv. Ludvíka Marie Grigniona z Montfortu, kněze",
	"",
	"S. Ludovici M. Grignion de Montfort, presbyteri",
	"",
	"Sv. Ludvíka Marie Grigniona z Montfortu, kněze, terciáře",
	"Montforti Grignion Szent Lajos Mária áldozópap",
	"ru_text",
	"Св. Людвіка Марыі Грыньён дэ Манфора, прэзбітэра",
	"Hl. Ludvigs Maria Grignion de Montfort, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_28_OFM[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Boldog Luchesius a III. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_29[POCET_JAZYKOV + 1] =
{
	"Sv. Kataríny Sienskej, panny a učiteľky Cirkvi, " HTML_LINE_BREAK "patrónky Európy",
	"Sv. Kateřiny Sienské, panny a učitelky církve, " HTML_LINE_BREAK "patronky Evropy",
	"",
	"S. Catharinæ Senensis, virginis et Ecclesiæ doctoris",
	"",
	"Sv. Kateřiny Sienské, panny a učitelky církve, " HTML_LINE_BREAK "patronky Evropy, terciářky",
	"Sienai Szent Katalin szűz és egyháztanító, " HTML_LINE_BREAK "Európa társvédőszentje",
	"ru_text",
	"Св. Кацярыны Сіенскай, панны і доктара Касцёла, " HTML_LINE_BREAK "апякункі Еўропы",
	"Hl. Katrínar frá Síena, meyjar, kirkjufræðara, " HTML_LINE_BREAK "verndardýrlings Evrópu",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_30[POCET_JAZYKOV + 1] =
{
	"Sv. Pia V., pápeža",
	"Sv. Pia V., papeže",
	"",
	"S. Pii V, papæ",
	"",
	"Sv. Pia V., papeže",
	"Szent V. Piusz pápa",
	"ru_text",
	"Св. Пія V, папы",
	"Hl. Píusar V. páfa",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_30_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Sv. Zikmunda, mučedníka",
	"",
	"",
	"",
	"Sv. Zikmunda, mučedníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_30_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Benedikta z Urbina, kňaza, člena 1. rádu",
	"Bl. Benedikta z Urbina, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_APR_30_OSU[POCET_JAZYKOV + 1] =
{
	"Sv. Márie od Vtelenia, rehoľníčky",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// --------------- 05 máj | may ---------------

const char* text_MAJ_01[POCET_JAZYKOV + 1] =
{
	"Sv. Jozefa, robotníka",
	"Sv. Josefa, Dělníka",
	"",
	"S. Ioseph Opificis",
	"",
	"Sv. Josefa, Dělníka",
	"Munkás Szent József",
	"ru_text",
	"Св. Юзафа рамесніка",
	"Hl. Jósef, verndari verkamanna",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_02[POCET_JAZYKOV + 1] =
{
	"Sv. Atanáza, biskupa a učiteľa Cirkvi",
	"Sv. Atanáše, biskupa a učitele církve",
	"",
	"S. Athanasii, episcopi et Ecclesiæ doctoris",
	"",
	"Sv. Atanáše, biskupa a učitele církve",
	"Szent Atanáz püspök és egyháztanító",
	"ru_text",
	"Св. Атаназія, біскупа і доктара Касцёла",
	"Hl. Aþanasíusar, biskups og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_02_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Prenesenie nášho Otca svätého Norberta",
	"Přenesení sv. Norberta, našeho otce", // iba na Strahove
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_03[POCET_JAZYKOV + 1] =
{
	"Sv. Filipa a Jakuba, apoštolov",
	"Sv. Filipa a Jakuba, apoštolů",
	"",
	"Ss. Philippi et Iacobi, apostolorum",
	"",
	"Sv. Filipa a Jakuba, apoštolů",
	"Szent Fülöp és Szent Jakab apostolok",
	"ru_text",
	"Св. Філіпа і Якуба, апосталаў",
	"Hl. Filippusar og Jakobs, postula",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_04[POCET_JAZYKOV + 1] =
{
	"Sv. Floriána, mučeníka",
	"Sv. Floriána, mučedníka",
	"",
	"",
	"",
	"Sv. Floriána, mučedníka",
	"Szent Flórián vértanú",
	"",
	"Св. Флоряна, мучаніка",
	"Heilagur Flórían, píslavottur",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_04_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Jozefa Máriu Rubia, kňaza",
	"Sv. Josefa Marie Rubio, kněze",
	"",
	"",
	"",
	"Sv. Josefa Marie Rubio, kněze",
	"Rubio Szent József Mária, áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_04_OFM[POCET_JAZYKOV + 1] =
{
	"",
	"Bl. Tomáše z Olery, řeholníka",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_04_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Emílie Bicchieriovej, panny",
	"Bl. Emílie Bicchieriové, panny, mnišky",
	"",
	"",
	"",
	"Bl. Emílie Bicchieriové, panny, mnišky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_04_2_OP[POCET_JAZYKOV + 1] =
{
	"",
	"Utrpení našeho Pána Ježíše Krista",
	"",
	"",
	"",
	"Utrpení našeho Pána Ježíše Krista",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_04_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Angela Máriu Prata, Lukáša od sv. Jozefa, " HTML_LINE_BREAK "kňazov, a spoločníkov, mučeníkov",
	"Bl. Angela Marie Prat, Lukáše od sv. Josefa " HTML_LINE_BREAK "a druhů, mučedníků",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_06_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Sv. Jana Sarkandra, kněze a mučedníka",
	"",
	"",
	"",
	"Sv. Jana Sarkandra, kněze a mučedníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_06_SDB[POCET_JAZYKOV + 1] =
{
	"Sv. Dominika Savia, mladíka",
	"Sv. Dominika Savia, chlapce",
	"",
	"",
	"",
	"",
	"Savio Szent Domonkos ifjú",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_07_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Alberta z Bergama",
	"Bl. Alberta z Bergama, terciáře",
	"",
	"",
	"",
	"Bl. Alberta z Bergama, terciáře",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_07_HU_1[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Boldog Gizella királyné",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_07_HU_2[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Az Egri bazilika-főszékesegyház felszentelése",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_08_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Panny Márie, patrónky Rehole kazateľov",
	"",
	"",
	"",
	"",
	"Panny Marie, ochránkyně Řádu kazatelů", // CZ: 15MAJ
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_08_2_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Petra Claverieho, biskupa, a spoločníkov, mučeníkov",
	"Bl. Petra Claverieho, biskupa, a druhů, mučedníků",
	"",
	"",
	"",
	"Bl. Petra Claverieho, biskupa, a druhů, mučedníků",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_08_CZ[POCET_JAZYKOV + 1] =
{
	"Prebl. Panny Márie, Matky a Sprostredkovateľky milostí",
	"Panny Marie, Prostřednice všech milostí",
	"",
	"",
	"",
	"Panny Marie, Prostřednice všech milostí",
	"",
	"",
	"",
	"María mey, móðir guðlegrar náðar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_08_OFM[POCET_JAZYKOV + 1] =
{
	"Prebl. Panny Márie, Matky a Sprostredkovateľky milostí",
	"Panny Marie, Prostřednice všech milostí",
	"",
	"",
	"",
	"Panny Marie, Prostřednice všech milostí",
	"",
	"",
	"",
	"María mey, móðir guðlegrar náðar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_08_2_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Ulriky Nischovej, panny, rehoľníčky, členky 3. rádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_08_3_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Jeremiáša z Valašska, rehoľníka, člena 1. rádu",
	"Bl. Jeremiáše z Valachie, řeholníka",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_08_SJ[POCET_JAZYKOV + 1] =
{
	"Bl. Jána Sullivana, kňaza",
	"Bl. Jana Sullivana, kněze",
	"",
	"",
	"",
	"Bl. Jana Sullivana, kněze",
	"hu_texz",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_08_SCHP[POCET_JAZYKOV + 1] =
{
	"Preblahoslavenej Panny Márie, " HTML_LINE_BREAK "Matky Zbožných škôl",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_09_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Kataríny z Bologne, panny, členky 2. rádu",
	"Sv. Kateřiny z Boloně, panny, členky 2. řádu",
	"",
	"",
	"",
	"",
	"Bolognai Szent Katalin, szűz a II. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_09_CM[POCET_JAZYKOV + 1] =
{
	"Sv. Lujzy de Marillac, rehoľníčky, " HTML_LINE_BREAK "spoluzakladateľky spoločnosti Dcér kresťanskej lásky",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_10_OP[POCET_JAZYKOV + 1] =
{
	"Sv. Antonína Florentského, biskupa",
	"Sv. Antonína Florentského, biskupa",
	"",
	"",
	"",
	"Sv. Antonína Florentského, biskupa",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_10[POCET_JAZYKOV + 1] =
{
	"Sv. Jána z Avily, kňaza a učiteľa Cirkvi",
	"Sv. Jana z Avily, kněze a učitele církve",
	"",
	"S. Ioannis De Avila, presbyteri et Ecclesiæ doctoris",
	"",
	"Sv. Jana z Avily, kněze a učitele církve",
	"De Avila Szent János áldozópap és egyháztanító",
	"",
	"",
	"Hl. Jóhannesar frá Avila, prests og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_11_SK[POCET_JAZYKOV + 1] =
{
	"Bl. Sáry Salkaháziovej, panny a mučenice",
	"",
	"",
	"",
	"",
	"",
	"Boldog Salkaházi Sára szűz és vértanú",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_11_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Ignáca z Laconie, rehoľníka, člena 1. rádu",
	"Sv. Ignáce z Laconi, řeholníka",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_12_1[POCET_JAZYKOV + 1] =
{
	"Sv. Nerea a Achila, mučeníkov",
	"Sv. Nerea a Achillea, mučedníků",
	"",
	"Ss. Nerei et Achillei, martyrum",
	"",
	"Sv. Nerea a Achillea, mučedníků",
	"Szent Néreusz és Szent Achilleusz vértanúk",
	"ru_text",
	"Св. Нэрэя і Ахіла, мучанікаў",
	"Hl. Nereusar og Achilleusar, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_12_2[POCET_JAZYKOV + 1] =
{
	"Sv. Pankráca, mučeníka",
	"Sv. Pankráce, mučedníka",
	"",
	"S. Pancratii, martyris",
	"",
	"Sv. Pankráce, mučedníka",
	"Szent Pongrác vértanú",
	"ru_text",
	"Св. Панкрата, мучаніка",
	"Hl. Pankratíusar, píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_12_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Výročí posvěcení katedrály sv. Víta",
	"",
	"",
	"",
	"Výročí posvěcení katedrály sv. Víta",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_12_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Leopolda Mandića, kňaza, člena 1. rádu",
	"Sv. Leopolda Mandiče, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_12_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Jany Portugalskej, panny",
	"Bl. Jany Portugalské, panny, mnišky",
	"",
	"",
	"",
	"Bl. Jany Portugalské, panny, mnišky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_13[POCET_JAZYKOV + 1] =
{
	"Prebl. Panny Márie Fatimskej",
	"Panny Marie Fatimské",
	"",
	"Beatæ Mariæ Virginis de Fatima",
	"",
	"Panny Marie Fatimské",
	"A Fatimai Boldogságos Szűz Mária",
	"ru_text",
	"Найсв. Панны Марыі з Фацімы",
	"Maríu meyjar frá Fatíma",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_13_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Imeldy Lambertiniovej, panny",
	"Bl. Imeldy Lambertiniové, panny",
	"",
	"",
	"",
	"Bl. Imeldy Lambertiniové, panny",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_13_SDB[POCET_JAZYKOV + 1] =
{
	"Sv. Márie Dominiky Mazzarellovej, panny, " HTML_LINE_BREAK "spoluzakladateľky Inštitútu dcér Márie Pomocnice",
	"Sv. Marie Dominiky Mazzarellové, panny " HTML_LINE_BREAK "a spoluzakladatelky Institutu Dcer Panny Marie Pomocnice",
	"",
	"",
	"",
	"",
	"Mazzarello Szent Mária Dominika szűz," HTML_LINE_BREAK "A Segítő Szűz Mária Leányai szerzetes intézmény Társalapító-nője",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_13_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Petra Regalada, kňaza, člena 1. rádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_14[POCET_JAZYKOV + 1] =
{
	"Sv. Mateja, apoštola",
	"Sv. Matěje, apoštola",
	"",
	"S. Matthiæ, apostoli",
	"",
	"Sv. Matěje, apoštola",
	"Szent Mátyás apostol", // v HU sa slávi 24.2.
	"ru_text",
	"Св. Мацея, апостала",
	"Hl. Matthíasar, postula",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_15_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Margity z Cortony, kajúcnice, členky 3. rádu",
	"Sv. Markéty z Cortony, kajícnice 3. řádu",
	"",
	"",
	"",
	"",
	"Cortonai Szent Margit a III. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_15_1_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Egída z Vauzela, kňaza",
	"Bl. Jiljí z Vouzely, kněze",
	"",
	"",
	"",
	"Bl. Jiljí z Vouzely, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_15_2_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Andreja Abellona, kňaza",
	"Bl. Ondřeje Abellona, kněze",
	"",
	"",
	"",
	"Bl. Ondřeje Abellona, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_16_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Andreja Bobolu, kňaza a mučeníka", // text_MAJ_15_SJ: na Slovensku sa slávi 15. mája
	"Sv. Ondřeje Boboly, kněze a mučedníka", // v Čechách sa slávi 17. mája
	"",
	"",
	"",
	"",
	"Bobola Szent András, áldozópap és vértanú, " HTML_LINE_BREAK "a Közép- és Keleteurópai asszisztencia társvédőszentje",
	"",
	"Св. Андрэя Баболі, прэзбітэра і мучаніка",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_16_CZ_SJ[POCET_JAZYKOV + 1] =
{
	"",
	"Sv. Jana Nepomuckého, kněze a mučedníka, " HTML_LINE_BREAK "hlavního patrona Čech " HTML_LINE_BREAK "a České provincie Tovaryšstva Ježíšova",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_16[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Nepomuckého, kňaza a mučeníka",
	"Sv. Jana Nepomuckého, kněze a mučedníka, " HTML_LINE_BREAK "hlavního patrona Čech",
	"",
	"",
	"",
	"Sv. Jana Nepomuckého, kněze a mučedníka, " HTML_LINE_BREAK "hlavního patrona Čech",
	"Nepomuki Szent János áldozópap és vértanú",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_16_SDB[POCET_JAZYKOV + 1] =
{
	"Sv. Alojza Orioneho, kňaza",
	"Sv. Aloise Orioneho, kněze",
	"",
	"",
	"",
	"",
	"Orione Szent Alajos áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_16_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Vladimíra Ghika, mučeníka",
	"Bl. Vladimíra Ghiky, mučedníka",
	"",
	"",
	"",
	"Bl. Vladimíra Ghiky, mučedníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_17_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Šimona Stocka, rehoľníka",
	"Sv. Šimona Stocka, řeholníka", // CZ: 16MAJ
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Símonar Stock, prests", // IS: 15MAJ
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_17_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Paschala Baylona, rehoľníka, člena 1. rádu",
	"Sv. Paschala Baylóna, řeholníka",
	"",
	"",
	"",
	"",
	"Baylon Szent Paszkál, szerzetes az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_17_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Boldog Scheffler János püspök és vértanú",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_18[POCET_JAZYKOV + 1] =
{
	"Sv. Jána I., pápeža a mučeníka",
	"Sv. Jana I., papeže a mučedníka",
	"",
	"S. Ioannis I, papæ et martyris",
	"",
	"Sv. Jana I., papeže a mučedníka",
	"Szent I. János pápa és vértanú",
	"ru_text",
	"Св. Яна I, папы і мучаніка",
	"Hl. Jóhannesar I., páfa og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_18_IS[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Eiríks, píslarvotts, verndardýrlings Svíþjóðar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_18_SDB[POCET_JAZYKOV + 1] =
{
	"Sv. Leonarda Murialda, kňaza",
	"Sv. Leonarda Murialda, kněze",
	"",
	"",
	"",
	"",
	"Murialdo Szent Leonardo áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_18_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Felixa z Cantalicie, rehoľníka, člena 1. rádu",
	"Sv. Felixe z Cantalice, řeholníka",
	"",
	"",
	"",
	"",
	"Kantalicei Szent Félix, szerzetes az 1. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_18_OSU[POCET_JAZYKOV + 1] =
{
	"Bl. Blandíny Mertenovej, panny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_19_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Krišpína z Viterba, rehoľníka, člena 1. rádu",
	"Sv. Kryšpína z Viterba, řeholníka",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_19_OP[POCET_JAZYKOV + 1] =
{
	"Sv. Františka Colla Guitarta, kňaza",
	"Sv. Františka Colla Guitarta, kněze",
	"",
	"",
	"",
	"Sv. Františka Colla Guitarta, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_20_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Sv. Klementa Marie Hofbauera, kněze",
	"",
	"",
	"",
	"Sv. Klementa Marie Hofbauera, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_20[POCET_JAZYKOV + 1] =
{
	"Sv. Bernardína Sienského, kňaza",
	"Sv. Bernardina Sienského, kněze",
	"",
	"S. Bernardini Senensis, presbyteri",
	"",
	"Sv. Bernardina Sienského, kněze",
	"Sienai Szent Bernardin áldozópap",
	"ru_text",
	"Св. Бэрнардына Сіенскага, прэзбітэра",
	"Hl. Bernardíns frá Síena, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_20_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Bernardína Sienského, kňaza, člena 1. rádu",
	"Sv. Bernardina Sienského, kněze",
	"",
	"",
	"",
	"",
	"Sienai Szent Bernardin, pap az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_21_2_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Kolumby z Rieti, panny",
	"Bl. Kolumby z Rieti, panny, řeholnice",
	"",
	"",
	"",
	"Bl. Kolumby z Rieti, panny, řeholnice",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_21_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Výročí posvěcení katedrály sv. Petra a Pavla",
	"",
	"",
	"",
	"Výročí posvěcení katedrály sv. Petra a Pavla",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_21[POCET_JAZYKOV + 1] =
{
	"Sv. Krištofa Magallanesa, kňaza, a spoločníkov, mučeníkov",
	"Sv. Kryštofa Magallanese, kněze, a druhů, mučedníků",
	"",
	"",
	"",
	"Sv. Kryštofa Magallanese, kněze, a druhů, mučedníků",
	"Magallán Szent Kristóf áldozópap és társai, mexikói vértanúk",
	"ru_text",
	"Св. Хрыстафора Магалана, прэзбітэра, і паплечнікаў, мучанікаў",
	"Hl. Kristófers Magellan, prests, og félaga, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_21_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Hyacinta Máriu Cormiera, kňaza",
	"Bl. Hyacinta Marie Cormiera, kněze",
	"",
	"",
	"",
	"Bl. Hyacinta Marie Cormiera, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_21_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Franza Jägerstättera, otca rodiny, mučeníka, člena 3. rádu",
	"Bl. Franze Jägerstättera, otce rodiny, mučedníka, člena 3. řádu",
	"",
	"",
	"",
	"Bl. Franze Jägerstättera, otce rodiny, mučedníka, člena 3. řádu",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_22[POCET_JAZYKOV + 1] =
{
	"Sv. Rity z Cascie, rehoľníčky",
	"Sv. Rity z Cascie, řeholnice",
	"",
	"S. Ritæ de Cascia, religiosæ",
	"",
	"Sv. Rity z Cascie, řeholnice",
	"Szent Rita szerzetesnő",
	"ru_text",
	"Св. Рыты з Касіі, законніцы",
	"Hl. Ritu frá Cascia, nunnu", // reglusystir?
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_22_SJ[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Úti Boldogasszony",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_22_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Joachimy de Vedrúna y Mas, rehoľníčky",
	"Sv. Jáchymy de Vedruna de Mas, řeholnice",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Jóakimu de Vedruna de Mas, ekkju",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_23_CM[POCET_JAZYKOV + 1] =
{
	"Sv. Jany Antidy Thouretovej, panny, " HTML_LINE_BREAK "zakladateľky Sestier kresťanskej lásky",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_23_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Boldog Apor Vilmos püspök és vértanú",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_24_OP[POCET_JAZYKOV + 1] =
{
	"Prenesenie pozostatkov sv. otca Dominika",
	"Přenesení ostatků sv. otce Dominika",
	"",
	"",
	"",
	"Přenesení ostatků sv. otce Dominika",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_24_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Sv. Hermana Jozefa, kňaza z našej rehole",
	"Sv. Heřmana Josefa, kněze z premonstrátského řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_24_SJ[POCET_JAZYKOV + 1] =
{
	"",
	"Panny Marie della Strada",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_24_OFM[POCET_JAZYKOV + 1] =
{
	"Výročie posviacky Baziliky sv. Františka v Assisi",
	"Posvěcení baziliky sv. Františka v Assisi",
	"",
	"",
	"",
	"",
	"Szent Ferenc atyánk assisi bazilikájának felszentelése",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_24[POCET_JAZYKOV + 1] =
{
	"Panny Márie, Pomocnice kresťanov",
	"Panny Marie Pomocnice křesťanů",
	"",
	"",
	"",
	"",
	"Szűz Mária, a keresztények segítsége",
	"",
	"",
	"Hl. Maríu meyjar, hjálpar kristinna manna",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_24_SDB[POCET_JAZYKOV + 1] =
{
	"Panny Márie, Pomocnice kresťanov, " HTML_LINE_BREAK "hlavnej patrónky Spoločnosti sv. Františka Saleského " HTML_LINE_BREAK "a Inštitútu dcér Márie Pomocnice",
	"Panny Marie Pomocnice křesťanů, " HTML_LINE_BREAK "hlavní patronky Společnosti sv. Františka Saleského, " HTML_LINE_BREAK "Institutu Dcer Panny Marie " HTML_LINE_BREAK "a Sekulárního institutu Volontárií Dona Boska",
	"",
	"",
	"",
	"",
	"Szűz Mária, a keresztények segítsége, " HTML_LINE_BREAK "a Szalézi Szent Ferenc Társaság, " HTML_LINE_BREAK "a Segítő Szűz Mária Leányai Intézménye " HTML_LINE_BREAK "és a Don Bosco Voluntáriák Világi Intézménye főpatrónája",
	"",
	"",
	"Hl. Maríu meyjar, hjálpar kristinna manna",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_25_1[POCET_JAZYKOV + 1] =
{
	"Sv. Bédu Ctihodného, kňaza a učiteľa Cirkvi",
	"Sv. Bedy Ctihodného, kněze a učitele církve",
	"",
	"S. Bedæ Venerabilis, presbyteri et Ecclesiæ doct.",
	"",
	"Sv. Bedy Ctihodného, kněze a učitele církve",
	"Tiszteletreméltó Szent Béda áldozópap és egyháztanító",
	"ru_text",
	"Св. Бэды Вялебнага, прэзбітэра і доктара Касцёла",
	"Hl. Beda hins æruverðuga, prests og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_25_2[POCET_JAZYKOV + 1] =
{
	"Sv. Gregora VII., pápeža",
	"Sv. Řehoře VII., papeže",
	"",
	"S. Gregorii VII, papæ",
	"",
	"Sv. Řehoře VII., papeže",
	"Szent VII. Gergely pápa",
	"ru_text",
	"Св. Грыгорыя VII, папы",
	"Hl. Gregoríusar VII., páfa",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_25_3[POCET_JAZYKOV + 1] =
{
	"Sv. Márie Magdalény de’ Pazzi, panny",
	"Sv. Marie Magdalény de’Pazzi, panny",
	"",
	"S. Mariæ Magdalenæ de’ Pazzi, virginis",
	"",
	"Sv. Marie Magdalény de’Pazzi, panny",
	"Pazzi Szent Mária Magdolna szűz",
	"ru_text",
	"Св. Марыі Магдалены Паццы, панны",
	"Hl. Maríu Magdalenu deʼ Pazzi, meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_26[POCET_JAZYKOV + 1] =
{
	"Sv. Filipa Neriho, kňaza",
	"Sv. Filipa Neriho, kněze",
	"",
	"S. Philippi Neri, presbyteri",
	"",
	"Sv. Filipa Neriho, kněze",
	"Néri Szent Fülöp áldozópap",
	"ru_text",
	"Св. Філіпа Нэры, прэзбітэра",
	"Hl. Filippusar Nerí, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_27[POCET_JAZYKOV + 1] =
{
	"Sv. Augustína z Canterbury, biskupa",
	"Sv. Augustina z Canterbury, biskupa",
	"",
	"S. Augustini Cantuariensis, episcopi",
	"",
	"Sv. Augustina z Canterbury, biskupa",
	"Canterbury-i Szent Ágoston püspök",
	"ru_text",
	"Св. Аўгустына Кэнтэрберыйскага, біскупа",
	"Hl. Ágústínusar frá Kantaraborg, biskups",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_27_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Andreja Franchiho, biskupa",
	"Bl. Ondřeje Franchiho, biskupa",
	"",
	"",
	"",
	"Bl. Ondřeje Franchiho, biskupa",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_27_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Jozefa z Igualady, kňaza",
	"Bl. Josefa z Igualady, kněze",
	"",
	"",
	"",
	"Bl. Josefa z Igualady, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_28_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Márie Bartolomey Bagnesiovej, panny",
	"Bl. Marie Bartolomey Bagnesiové, panny, terciářky",
	"",
	"",
	"",
	"Bl. Marie Bartolomey Bagnesiové, panny, terciářky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_28_OFM[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Paredes-i Szent Mária Anna, szűz a III. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_29[POCET_JAZYKOV + 1] =
{
	"Sv. Pavla VI., pápeža",
	"Sv. Pavla VI., papeže",
	"",
	"S. Pauli VI, papæ",
	"",
	"Sv. Pavla VI., papeže",
	"Szent VI. Pál pápa",
	"",
	"",
	"Hl. Páls VI., páfa",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_29_OSU[POCET_JAZYKOV + 1] =
{
	"Sv. Uršule Ledóchovskej, panny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_29_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Viliama Arnauda, kňaza, a spoločníkov, mučeníkov",
	"Bl. Viléma Arnauda, kněze, a druhů, mučedníků",
	"",
	"",
	"",
	"Bl. Viléma Arnauda, kněze, a druhů, mučedníků",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_29_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Jozefa Kowalského, mučeníka",
	"Bl. Josefa Kowalského, kněze a mučedníka",
	"",
	"",
	"",
	"",
	"Boldog Kowalski József áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_29_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Elie od sv. Klementa, panny",
	"Bl. Elie od sv. Klementa, panny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_30_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Jakuba Salomoniho, kňaza",
	"Bl. Jakuba Salomoniho, kněze",
	"",
	"",
	"",
	"Bl. Jakuba Salomoniho, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_30_CZ[POCET_JAZYKOV + 1] =
{
	"Sv. Zdislavy z Lemberka", // všeobecný OP kalendár: 04JAN (prekladanie v CZ)
	"Sv. Zdislavy",
	"",
	"",
	"",
	"Sv. Zdislavy z Lemberka, matky rodiny, terciářky, " HTML_LINE_BREAK "patronky provincie",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_30_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Szent István király ereklyéinek átvitele",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_30_OFM[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Boldog Baptista Verano, szűz a II. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_MAJ_31[POCET_JAZYKOV + 1] =
{
	"Návšteva prebl. Panny Márie", // doplnené "prebl." podľa 3RM
	"Navštívení Panny Marie",
	"",
	"In visitatione Beatæ Mariæ Virginis",
	"",
	"Navštívení Panny Marie",
	"Szűz Mária látogatása Erzsébetnél " HTML_LINE_BREAK "(Sarlós Boldogasszony)",
	"ru_text",
	"Адведзіны Найсв. Панны Марыі",
	"Vitjunardagur Maríu meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// --------------- 00 pohyblivé slávenia ---------------

const char* text_NANEBOVSTUPENIE_PANA[POCET_JAZYKOV + 1] =
{
	"Nanebovstúpenie Pána",
	"Nanebevstoupení Páně",
	"The Ascension of the Lord",
	"In Ascensione Domini",
	"",
	"Nanebevstoupení Páně",
	"Urunk mennybemenetele",
	"ru_text",
	"Урачыстасць Унебаўшэсця Пана",
	"Uppstigningardagur",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_VELKONOCNA_NEDELA[POCET_JAZYKOV + 1] =
{
	"Veľkonočná nedeľa",
	"Neděle Zmrtvýchvstání Páně",
	"",
	"Dominica Paschæ",
	"",
	"Neděle Zmrtvýchvstání Páně",
	"Húsvétvasárnap",
	"ru_text",
	"Велікодная нядзеля",
	"Páskadagur",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NEDELA_PANOVHO_ZMRTVYCHVSTANIA[POCET_JAZYKOV + 1] = // 2012-12-13: XML nepodporuje &mdash; -- použitý číselný kód &#8212; http://en.wikipedia.org/wiki/List_of_XML_and_HTML_character_entity_references
{
	HTML_LINE_BREAK "Pánovho zmŕtvychvstania",
	"",
	"",
	HTML_LINE_BREAK "In Resurrectione Domini",
	"",
	"",
	", " HTML_LINE_BREAK "Krisztus feltámadása",
	"",
	", " HTML_LINE_BREAK "урачыстасць Уваскрасення Пана",
	HTML_LINE_BREAK " &#8212; Upprisuhátíð Drottins",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NEDELA_VO_VELKONOCNEJ_OKTAVE[POCET_JAZYKOV + 1] =
{
	"Nedeľa vo Veľkonočnej oktáve",
	"Neděle v oktávu velikonočním",
	"",
	"Dominica in octava Paschæ",
	"",
	"Neděle v oktávu velikonočním",
	"Vasárnap Húsvét nyolcadában",
	"ru_text",
	"II Велікодная нядзеля", // convertToRoman()
	"Áttundi dagur Páskanna",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NEDELA_VO_VELKONOCNEJ_OKTAVE_SUBSTRING[POCET_JAZYKOV + 1] =
{
	"Druhá veľkonočná nedeľa — Božieho milosrdenstva",
	"Druhá neděle velikonoční – Božího milosrdenství",
	"",
	"Dominica II Paschæ – Divinæ Misericordiæ",
	"",
	"Druhá neděle velikonoční – Božího milosrdenství",
	"Húsvét 2. vasárnapja – Az Isteni Irgalmasság vasárnapja",
	"ru_text",
	"by_text",
	"II. Sunnudagur á Páskatíma – Sunnudagur hinnar guðdómlegu miskunnsemi",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEN_VO_VELKONOCNEJ_OKTAVE[POCET_JAZYKOV + 1] =
{
	"%s vo Veľkonočnej oktáve", // kedysi: "Veľkonočn%s %s",
	"%s velikonoční",
	"",
	"%s infra octavam Paschæ",
	"",
	"%s velikonoční",
	"%s Húsvét nyolcadában",
	"ru_text",
	"%s у актаве Пасхі",
	"%s á Páskaviku",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// pre HU + IS špeciálny názov veľkonočného pondelka
const char* text_VELKONOCNY_PONDELOK[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Húsvéthétfő",
	"",
	"",
	"Annar Páskadagur",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* text_HU_VELKY_TYZDEN_PREFIX = "Nagy"; // pre HU špeciálne názvy dní veľkného týždňa (pondelok až streda)

const char* text_MARIE_MATKY_CIRKVI[POCET_JAZYKOV + 1] =
{
	"Prebl. Panny Márie, Matky Cirkvi",
	"Panny Marie, Matky církve",
	"",
	"Beatæ Mariæ Virginis Ecclesiæ Matris",
	"",
	"Panny Marie, Matky církve",
	"Szűz Mária az Egyház Anyja",
	"ru_text",
	"by_text",
	"Maríu meyjar, móður kirkjunnar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NPJK_NAJ_KNAZA[POCET_JAZYKOV + 1] =
{
	"Nášho Pána Ježiša Krista, " HTML_LINE_BREAK "najvyššieho a večného kňaza",
	"Ježíše Krista, nejvyššího a věčného kněze",
	"",
	"Domini nostri Iesu Christi " HTML_LINE_BREAK "Summi et Æterni Sacerdotis",
	"",
	"Našeho Pána Ježíše Krista, nejvyššího a věčného kněze",
	"A mi Urunk, Jézus Krisztus, az Örök Főpap",
	"ru_text",
	"by_text",
	"Drottins vors Jesú Krists " HTML_LINE_BREAK "hinn æðsta og eilífa prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NAJSVATEJSEJ_TROJICE[POCET_JAZYKOV + 1] =
{
	"Najsvätejšej Trojice",
	"Nejsvětější Trojice",
	"",
	"Sanctissimæ Trinitatis",
	"",
	"Nejsvětější Trojice",
	"Szentháromság vasárnapja",
	"ru_text",
	"Найсвяцейшай Тройцы",
	"Alheilög Þrenning",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_KRISTA_KRALA[POCET_JAZYKOV + 1] =
{
	"Nášho Pána Ježiša Krista, " HTML_LINE_BREAK "Kráľa neba i zeme", // podľa 3RM
	"Ježíše Krista Krále",
	"",
	"Domini nostri Iesu Christi " HTML_LINE_BREAK "universorum regis",
	"",
	"Ježíše Krista Krále",
	"Krisztus Király",
	"ru_text",
	"Урачыстасць Пана Нашага Езуса Хрыста," HTML_LINE_BREAK " Валадара Сусвету",
	"Kristur Konungur", // Drottinn vor Jesús Kristur Konungur alheims
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NAJSV_KRISTOVHO_TELA_A_KRVI[POCET_JAZYKOV + 1] =
{
	"Najsvätejšieho Kristovho tela a krvi",
	"Těla a krve Páně",
	"The Most Holy Body and Blood of Christ",
	"Sanctissimi Corporis et Sanguinis Christi",
	"",
	"Těla a krve Páně",
	"Krisztus Szent Teste és Vére",
	"ru_text",
	"Найсвяцейшага Цела і Крыві Хрыста",
	"Alheilagur líkama og blóðs Krists",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NAJSV_SRDCA_JEZISOVHO[POCET_JAZYKOV + 1] =
{
	"Najsvätejšieho Srdca Ježišovho",
	"Nejsvětějšího Srdce Ježíšova",
	"",
	"Sacratissimi Cordis Iesu",
	"",
	"Nejsvětějšího Srdce Ježíšova",
	"Jézus Szent Szíve",
	"ru_text",
	"Найсвяцейшага Сэрца Езуса",
	"Hið AlhelgaHjarta Jesú",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NEPOSKVRNENEHO_SRDCA_PM[POCET_JAZYKOV + 1] =
{
	"Nepoškvrneného Srdca prebl. Panny Márie", // 2010-06-16: opravený názov podľa breviára i direktória; opätovne opravené podľa 3RM
	"Neposkvrněného Srdce Panny Marie",
	"",
	"Immaculati Cordis Beatæ Mariæ Virginis",
	"",
	"Neposkvrněného Srdce Panny Marie",
	"A Boldogságos Szűz Mária Szeplőtelen Szíve",
	"ru_text",
	"Беззаганнага Сэрца Найсвяцейшай Панны Марыі",
	"Hið flekklausa hjarta sællar Maríu meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NEPOSKVRNENEHO_SRDCA_PM_OFM[POCET_JAZYKOV + 1] =
{
	"Nepoškvrneného Srdca prebl. Panny Márie, " HTML_LINE_BREAK "patrónky slovenskej provincie Rádu menších bratov kapucínov",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NARODENIE_PANA[POCET_JAZYKOV + 1] =
{
	"Narodenie Pána",
	"Narození Páně",
	"",
	"In Nativitate Domini",
	"",
	"Narození Páně",
	"Urunk születése (Karácsony)",
	"ru_text",
	"Нараджэнне Пана",
	"Fæðing Drottins", // Fæðingarhátíð Drottins
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_ZOSLANIE_DUCHA_SVATEHO[POCET_JAZYKOV + 1] =
{
	"Zoslanie Ducha Svätého",
	"Seslání Ducha Svatého",
	"",
	"Dominica Pentecostes",
	"",
	"Seslání Ducha Svatého",
	"Pünkösd",
	"ru_text",
	"Нядзеля Спаслання Святога Духа",
	"Hvítasunna",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_PRVA_ADVENTNA_NEDELA[POCET_JAZYKOV + 1] =
{
	"Prvá adventná nedeľa",
	"První neděle adventní",
	"",
	"Dominica prima Adventus",
	"",
	"První neděle adventní",
	"Advent első vasárnapja",
	"ru_text",
	"by_text",
	"Fyrsti sunnudagur í adventu",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NEDELA_SV_RODINY[POCET_JAZYKOV + 1] =
{
	"Svätej rodiny Ježiša, Márie a Jozefa",
	"Svaté rodiny Ježíše, Marie a Josefa",
	"",
	"Sanctæ Familiæ Iesu, Mariæ et Ioseph",
	"",
	"Svaté rodiny Ježíše, Marie a Josefa",
	"A Szent Család: Jézus, Mária és József", // "Szent Család ünnepe"
	"ru_text",
	"Святой Сям'і: Езуса, Марыі і Юзафа",
	"Hin Heilaga Fjölskylda Jesú, Maríu og Jósefs", // HEILÖG FJÖLSKYLDA JESÚ, MARÍU OG JÓSEFS
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SPOMIENKA_PM_V_SOBOTU[POCET_JAZYKOV + 1] =
{
	"Spomienka Panny Márie v sobotu",
	"Sobotní památka Panny Marie",
	"",
	"Memoria S. Mariæ in sabbato",
	"",
	"Sobotní památka Panny Marie",
	"Szűz Mária szombati emléknapja",
	"ru_text",
	"by_text",
	"Minning alsællar Maríu Meyar á laugardögum",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// --------------- 06 jún | june ---------------

const char* text_JUN_01[POCET_JAZYKOV + 1] =
{
	"Sv. Justína, mučeníka",
	"Sv. Justina, mučedníka",
	"",
	"S. Iustini, martyris",
	"",
	"Sv. Justina, mučedníka",
	"Szent Jusztínusz vértanú",
	"ru_text",
	"Св. Юстына, мучаніка",
	"Hl. Justins, píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_02[POCET_JAZYKOV + 1] =
{
	"Sv. Marcelína a Petra, mučeníkov",
	"Sv. Marcelina a Petra, mučedníků",
	"",
	"Ss. Marcellini et Petri, martyrum",
	"",
	"Sv. Marcelina a Petra, mučedníků",
	"Szent Marcellínusz és Szent Péter vértanúk",
	"ru_text",
	"Св. Марцэліна і Пятра, мучанікаў",
	"Hl. Marsellínusar og hl. Péturs, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_02_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Felixa z Nikózie, rehoľníka, člena 1. rádu",
	"Sv. Felixe z Nicosie, řeholníka",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_02_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Sadoka, kňaza, a spoločníkov, mučeníkov",
	"Bl. Sadoka, kněze, a druhů, mučedníků",
	"",
	"",
	"",
	"Bl. Sadoka, kněze, a druhů, mučedníků",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_03[POCET_JAZYKOV + 1] =
{
	"Sv. Karola Lwangu a spoločníkov, mučeníkov",
	"Sv. Karla Lwangy a druhů, mučedníků",
	"",
	"Ss. Caroli Lwanga et sociorum, martyrum",
	"",
	"Sv. Karla Lwangy a druhů, mučedníků",
	"Lwanga Szent Károly és társai, ugandai vértanúk",
	"ru_text",
	"Св. Караля Луангі і паплечнікаў, мучанікаў",
	"Hl. Karls Lwanga og félaga, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_04_OP[POCET_JAZYKOV + 1] =
{
	"Sv. Petra Veronského, kňaza a mučeníka",
	"",
	"",
	"",
	"",
	"Sv. Petra Veronského, kněze a mučedníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_04_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Szent Quirinus (Kerény) püspök és vértanú",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_05[POCET_JAZYKOV + 1] =
{
	"Sv. Bonifáca, biskupa a mučeníka",
	"Sv. Bonifáce, biskupa a mučedníka",
	"",
	"S. Bonifatii, episcopi et martyris",
	"",
	"Sv. Bonifáce, biskupa a mučedníka",
	"Szent Bonifác püspök és vértanú",
	"ru_text",
	"Св. Баніфацыя, біскупа і мучаніка",
	"Hl. Bonifatíusar, biskups og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_05_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Debrecen-Nyíregyháza: A székesegyház felszentelése",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_06[POCET_JAZYKOV + 1] =
{
	"Sv. Norberta, biskupa",
	"Sv. Norberta, biskupa",
	"",
	"S. Norberti, episcopi",
	"",
	"Sv. Norberta, biskupa",
	"Szent Norbert püspök",
	"ru_text",
	"Св. Норбэрта, біскупа",
	"Hl. Norberts, biskups og reglustofnanda",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_06_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Nášho Otca sv. Norberta, biskupa a zakladateľa našej rehole",
	"Našeho otce sv. Norberta, biskupa " HTML_LINE_BREAK "a zakladatele premonstrátského řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_07_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Anny od sv. Bartolomeja, panny",
	"Bl. Anny od sv. Bartoloměje, panny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Önnu af hl. Bartolómeusi, meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_07_OFMCONV[POCET_JAZYKOV + 1] =
{
	"Bl. Michala Tomaszeka a Zbigneva Strzałkowského, kňazov a mučeníkov",
	"Bl. Michala Tomaszka a Zbyňka Strzałkowského, kněží mučedníků 1. řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_08_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Prágai Szent Ágnes szűz",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_08_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Mikuláša z Gesturi, rehoľníka, člena 1. rádu",
	"Bl. Mikuláše z Gesturi (Medda), řeholníka",
	"",
	"",
	"",
	"",
	"Prágai Szent Ágnes, szűz a II. Rendből", // pozor, iné slávenie!
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_08_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Štefana Šándora, rehoľníka, mučeníka",
	"Bl. Štěpána Šándora, mučedníka",
	"",
	"",
	"",
	"",
	"Boldog Sándor István szalézi szerzetes testvér",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_08_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Diany a Cecílie, panien",
	"Bl. Diany a Cecílie, panen, mnišek",
	"",
	"",
	"",
	"Bl. Diany a Cecílie, panen, mnišek",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_08_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Jakuba Berthieua, kňaza a mučeníka",
	"Sv. Jakuba Berthieu, kněze a mučedníka",
	"",
	"",
	"",
	"Sv. Jakuba Berthieu, kněze a mučedníka",
	"Berthieu Szent Jakab, áldozópap és vértanú",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_09[POCET_JAZYKOV + 1] =
{
	"Sv. Efréma, diakona a učiteľa Cirkvi",
	"Sv. Efréma Syrského, jáhna a učitele církve",
	"",
	"S. Ephræm, diaconi et Ecclesiæ doctoris",
	"",
	"Sv. Efréma Syrského, jáhna a učitele církve",
	"Szent Efrém diakónus és egyháztanító",
	"ru_text",
	"Св. Эфрэма, дыякана і доктара Касцёла",
	"Hl. Efraíms, djákna og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_09_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Jozefa de Anchieta, kňaza",
	"Sv. Josefa de Anchieta, kněze",
	"",
	"",
	"",
	"Sv. Josefa de Anchieta, kněze",
	"De Anchieta SzentJózsef, áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_10_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Jána Dominiciho, biskupa",
	"",
	"",
	"",
	"",
	"Bl. Jana Dominiciho, biskupa",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_11[POCET_JAZYKOV + 1] =
{
	"Sv. Barnabáša, apoštola",
	"Sv. Barnabáše, apoštola",
	"",
	"S. Barnabæ, apostoli",
	"",
	"Sv. Barnabáše, apoštola",
	"Szent Barnabás apostol",
	"ru_text",
	"Св. Барнабы, апостала",
	"Hl. Barnabas, postuli",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_12_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Bl. Marie Antoníny Kratochvílové, panny, a druhů mučedníků",
	"",
	"",
	"",
	"Bl. Marie Antoníny Kratochvílové, panny, a druhů mučedníků",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_12_BY[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Бл. Генрыха Глябовіча, прэзбітэра, і паплечнікаў, мучанікаў",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_12_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Františka Kęsyho a spoločníkov, mučeníkov", // Bl. Františka Kesyho a spoločníkov, mučeníkov (ę = small latin letter e with ogonek = &#281;)
	"Bl. Františka Kęsyho a druhů, mučedníků",
	"",
	"",
	"",
	"",
	"Boldog Kęsy Ferenc és négy oratorista társa vértanúk",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_12_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Štefana Bandelliho, kňaza",
	"Bl. Štěpána Bandelliho, kněze",
	"",
	"",
	"",
	"Bl. Štěpána Bandelliho, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_12_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Alfonza Máriu Mazurka, kňaza," HTML_LINE_BREAK " a spoločníkov, mučeníkov",
	"Bl. Alfonsa Marie Mazurka, kněze, a druhů, mučedníků",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Alfons Maria Mazurek og félaga, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_12_OSU[POCET_JAZYKOV + 1] =
{
	"Bl. Márie Klemensy Staszewskej, panny a mučenice",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_12_SVD[POCET_JAZYKOV + 1] =
{
	"Bl. Ľudovíta Mzyka, kňaza," HTML_LINE_BREAK " a jeho spoločníkov, mučeníkov",
	"",
	"",
	"",
	"",
	"",
	"Boldog Mzyk Lajos áldozópap és társai vértanúk",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_12_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Jolandy Uhorskej, rehoľníčky, členky 2. rádu",
	"Bl. Jolanty Uherské, řeholnice",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_12_2_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Floridy Cevoliovej, panny, členky 2. rádu",
	"Bl. Floridy Cevoli, panny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_12_3_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Antona Bajewského a spoločníkov, mučeníkov: " HTML_LINE_BREAK "Pia Bartošika, Inocenta Guza, Achilla Puchalu, Hermana St&#281;npie&nacute;a, kňazov; " HTML_LINE_BREAK "Timoteja Trojanowského, Bonifáca &#379;ukowského, rehoľníkov, členov 1. rádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_13[POCET_JAZYKOV + 1] =
{
	"Sv. Antona Paduánskeho, kňaza a učiteľa Cirkvi",
	"Sv. Antonína z Padovy, kněze a učitele církve",
	"",
	"S. Antonii de Padova, presbyteri et Ecclesiæ doctoris",
	"",
	"Sv. Antonína z Padovy, kněze a učitele církve",
	"Páduai Szent Antal áldozópap és egyháztanító",
	"ru_text",
	"Св. Антонія Падуанскага, прэзбітэра і доктара Касцёла",
	"Hl. Antóníusar frá Padúa, prests og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_13_SK[POCET_JAZYKOV + 1] =
{
	"Výročie posviacky katedrálneho chrámu " HTML_LINE_BREAK "sv. Šebastiána",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_13_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Antona Paduánskeho, kňaza a učiteľa Cirkvi, člena 1. rádu",
	"Sv. Antonína z Padovy, kněze a učitele církve",
	"",
	"",
	"",
	"",
	"Páduai Szent Antal, pap, egyháztanító az I. Rendből",
	"",
	"Св. Антонія Падуанскага, прэзбітэра і доктара Касцёла",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_14_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"A Szombathelyi székesegyház felszentelése",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_14_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Márie Candidy od Eucharistie, panny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_14_2_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Elizea, proroka",
	"Sv. Elizea, proroka",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_15_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Sv. Víta, mučedníka",
	"",
	"",
	"",
	"Sv. Víta, mučedníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_15_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Árpád-házi Boldog Jolán szerzetesnő",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_15_OFM_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Boldog Jolán, szerzetesnő a II. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_16_SK[POCET_JAZYKOV + 1] =
{
	"Sv. Neita, mučeníka",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_16_1_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Márie Terézie Schererovej, panny, rehoľníčky, členky 3. rádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_16_2_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Aniceta Koplina, kňaza, a spoločníkov, mučeníkov, členov 1. rádu",
	"Bl. Aniceta Koplińského, kněze, a druhů, mučedníků",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_16_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Sv. Isfrída, biskupa z našej rehole", // SK OPraem: 15JUN
	"Sv. Isfrída, biskupa z premonstrátského řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_16_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Tours-i Szent Márton püspök ereklyéinek átvitele",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_17_IS[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Bótólfs, ábóta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_17_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Alberta Chmielowského, rehoľníka, člena 3. rádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_18_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Hosanny z Mantovy, panny",
	"Bl. Hosanny z Mantovy, panny, terciářky",
	"",
	"",
	"",
	"Bl. Hosanny z Mantovy, panny, terciářky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_19[POCET_JAZYKOV + 1] =
{
	"Sv. Romualda, opáta",
	"Sv. Romualda, opata",
	"",
	"S. Romualdi, abbatis",
	"",
	"Sv. Romualda, opata",
	"Szent Romuald apát",
	"ru_text",
	"Св. Рамуальда, абата",
	"Hl. Romualds, ábóta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_19_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Sv. Jana Nepomuckého Neumanna, biskupa",
	"",
	"",
	"",
	"Sv. Jana Nepomuckého Neumanna, biskupa",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_20_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Margity Ebnerovej, panny",
	"Bl. Markéty Ebnerové, panny, mnišky",
	"",
	"",
	"",
	"Bl. Markéty Ebnerové, panny, mnišky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_21[POCET_JAZYKOV + 1] =
{
	"Sv. Alojza Gonzágu, rehoľníka",
	"Sv. Aloise Gonzagy, řeholníka",
	"",
	"S. Aloisii Gonzaga, religiosi",
	"",
	"Sv. Aloise Gonzagy, řeholníka",
	"Gonzága Szent Alajos szerzetes",
	"ru_text",
	"Св. Алаізія Ганзагі, законніка",
	"Hl. Aloisíusar Gonzaga, reglubróður",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_21_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Alojza Gonzagu, rehoľníka",
	"Sv. Aloise Gonzagy, řeholníka",
	"",
	"",
	"",
	"Sv. Aloise Gonzagy, řeholníka",
	"Gonzága Szent Alajos, szerzetes",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_22_2[POCET_JAZYKOV + 1] =
{
	"Sv. Pavlína z Noly, biskupa",
	"Sv. Paulina Nolánského, biskupa",
	"",
	"S. Paulini Nolani, episcopi",
	"",
	"Sv. Paulina Nolánského, biskupa",
	"Nolai Szent Paulínusz püspök",
	"ru_text",
	"Св. Паўліна Нольскага, біскупа",
	"Hl. Pálínusar frá Nóla, biskups",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_22_1[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Fishera, biskupa, " HTML_LINE_BREAK "a Tomáša Morusa, mučeníkov", // kedysi: Mórusa; Direktórium 2012, str. 156, uvádza už iba s krátkym "o"; 3RM uvádza bez druhého "sv." (prvé "Sv." sa myslí ako plurál)
	"Sv. Jana Fishera, biskupa, " HTML_LINE_BREAK "a Tomáše Mora, mučedníků",
	"",
	"Ss. Ioannis Fisher, episcopi, " HTML_LINE_BREAK "et Thomæ More, martyrum",
	"",
	"Sv. Jana Fishera, biskupa, " HTML_LINE_BREAK "a Tomáše Mora, mučedníků",
	"Fisher Szent János püspök " HTML_LINE_BREAK "és Morus Szent Tamás vértanúk",
	"ru_text",
	"Св. Джона Фішара, біскупа, " HTML_LINE_BREAK "і Томаса Мора, мучанікаў",
	"Hl. Jóhannesar Fisher, biskups " HTML_LINE_BREAK "og Tómasar More, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_22_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"A Pécsi székesegyház felszentelése",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_23_SDB[POCET_JAZYKOV + 1] =
{
	"Sv. Jozefa Cafassa, kňaza",
	"Sv. Josefa Cafassa, kněze",
	"",
	"",
	"",
	"",
	"Cafasso Szent József áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_23_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Inocenta V., pápeža",
	"Bl. Inocence V., papeže",
	"",
	"",
	"",
	"Bl. Inocence V., papeže",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_24[POCET_JAZYKOV + 1] =
{
	"Narodenie sv. Jána Krstiteľa",
	"Narození svatého Jana Křtitele",
	"",
	"In Nativitate S. Ioannis Baptistæ",
	"",
	"Narození svatého Jana Křtitele",
	"Keresztelő Szent János születése",
	"ru_text",
	"Нараджэнне св. Яна Хрысціцеля",
	"Jóhannesar skírara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_26_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Andreja Hyacinta Longina, biskupa, člena 1. rádu",
	"Bl. Ondřeje Hyacinta Longhina, biskupa",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_26_2_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Jakuba z Ghazíru, kňaza",
	"Bl. Jakuba z Ghaziru (Al-Haddad), kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_26_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Márie Jozefíny od Ukrižovaného Ježiša, panny",
	"Bl. Marie Josefiny od Ježíše Ukřižovaného, panny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_26_CM[POCET_JAZYKOV + 1] =
{
	"Bl. Márie Magdalény Fontainovej a spoločníčok, " HTML_LINE_BREAK "panien a mučeníc",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_27[POCET_JAZYKOV + 1] =
{
	"Sv. Cyrila Alexandrijského, biskupa a učiteľa Cirkvi",
	"Sv. Cyrila Alexandrijského, biskupa a učitele církve",
	"",
	"S. Cyrilli Alexandrini, episcopi et Ecclesiæ doctoris",
	"",
	"Sv. Cyrila Alexandrijského, biskupa a učitele církve",
	"Alexandriai Szent Cirill püspök és egyháztanító", // HU: 26JUN
	"ru_text",
	"Св. Кірыла Александрыйскага, біскупа і доктара Касцёла",
	"Hl. Kýrils frá Alexandríu, biskups og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_27_SK_HU[POCET_JAZYKOV + 1] =
{
	"Sv. Ladislava",
	"",
	"",
	"S. Ladislai, regis",
	"",
	"",
	"Szent László király",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_27_CSSR[POCET_JAZYKOV + 1] =
{
	"Panny Márie, Matky ustavičnej pomoci",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_28[POCET_JAZYKOV + 1] =
{
	"Sv. Ireneja, biskupa a mučeníka, učiteľa Cirkvi",
	"Sv. Ireneje, biskupa a mučedníka, učitele církve",
	"",
	"S. Irenæi, episcopi et martyris, Ecclesiæ doctoris",
	"",
	"Sv. Ireneje, biskupa a mučedníka, učitele církve",
	"Szent Iréneusz püspök és vértanú, egyháztanító",
	"ru_text",
	"Св. Ірэнэя, біскупа і мучаніка, доктара Касцёла",
	"Hl. Íreneusar, biskups og píslarvotts, kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_29[POCET_JAZYKOV + 1] =
{
	"Sv. Petra a Pavla, apoštolov",
	"Sv. Petra a Pavla, apoštolů, " HTML_LINE_BREAK "hlavních patronů brněnské diecéze",
	"",
	"Ss. Petri et Pauli, Apostolorum",
	"",
	"Sv. Petra a Pavla, apoštolů, " HTML_LINE_BREAK "hlavních patronů brněnské diecéze",
	"Szent Péter és Szent Pál apostolok",
	"ru_text",
	"Св. Пятра і Паўла, апосталаў",
	"Pétursmessa og Páls, postula",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_29_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Sv. Petra a Pavla, apoštolov",
	"Sv. Petra a Pavla, apoštolů, " HTML_LINE_BREAK "titulární slavnost opatského kostela",
	"",
	"Ss. Petri et Pauli, apostolorum",
	"",
	"Sv. Petra a Pavla, apoštolů",
	"Szent Péter és Szent Pál apostolok",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_30[POCET_JAZYKOV + 1] =
{
	"Prvých svätých mučeníkov Cirkvi v Ríme",
	"Svatých prvomučedníků římských",
	"",
	"Ss. Protomartyrum Sanctæ Romanæ Ecclesiæ",
	"",
	"Svatých prvomučedníků římských",
	"A római Egyház első szent vértanúi",
	"ru_text",
	"Св. Першамучанікаў Рымскага Касцёла",
	"Hinna fyrstu píslarvotta kirkjunnar í Rómaborg",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_30_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Výročí posvěcení katedrály sv. Václava",
	"",
	"",
	"",
	"Výročí posvěcení katedrály sv. Václava",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_30_CSSR[POCET_JAZYKOV + 1] =
{
	"Bl. Januára Máriu Sarnelliho, kňaza",
	"Bl. Geranno Marie Sarnelliho, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUN_30_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Rajmunda Lulla, mučeníka 3. rádu",
	"Bl. Rajmunda Lulla, mučedníka 3. řádu",
	"",
	"",
	"",
	"",
	"Boldog Raymundus Lullus, vértanú a III. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// --------------- 07 júl |july ---------------

const char* text_JUL_02_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Bernardína Realina, Jána Františka Régisa a Františka de Geronimo; " HTML_LINE_BREAK "bl. Juliána Maunoira, Antona Baldinucciho a Jána Filipa Jeningena, kňazov", // text_JUL_01_SJ: na Slovensku aj v Maďarsku sa slávi 1. júla
	"Sv. Bernardina Realino, Jana Františka Régis a Františka de Geronimo; " HTML_LINE_BREAK "bl. Juliana Maunoira, Antonína Baldinucciho, Tiburcia Arnaize a Jana Filipa Jeningena, kněží",
	"",
	"",
	"",
	"Sv. Bernardina Realino, Jana Františka Régis a Františka de Geronimo; " HTML_LINE_BREAK "bl. Juliana Maunoira, Antonína Baldinucciho, Tiburcia Arnaize a Jana Filipa Jeningena, kněží",
	"Realino Szent Benardin, Régis Szent János Ferenc és de Geronimo Szent Ferenc; " HTML_LINE_BREAK "Boldog Maunoir Julián és Boldog Baldinucci Antal, áldozópapok",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_02_BY[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Найсв. Панны Марыі Будслаўскай",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_03[POCET_JAZYKOV + 1] =
{
	"Sv. Tomáša, apoštola",
	"Sv. Tomáše, apoštola",
	"",
	"S. Thomæ, apostoli",
	"",
	"Sv. Tomáše, apoštola",
	"Szent Tamás apostol",
	"ru_text",
	"Св. Тамаша, апостала",
	"Hl. Tómasar, postula",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_04[POCET_JAZYKOV + 1] =
{
	"Sv. Alžbety Portugalskej",
	"Sv. Alžběty Portugalské",
	"",
	"S. Elisabeth Lusitaniæ",
	"",
	"Sv. Alžběty Portugalské",
	"Portugáliai Szent Erzsébet",
	"ru_text",
	"Св. Альжбеты Партугальскай",
	"Hl. Elísabetar frá Portúgal",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_04_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Sv. Prokopa, opata",
	"",
	"",
	"",
	"Sv. Prokopa, opata",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_04_1_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Kataríny Jarrigeovej, panny",
	"Bl. Kateřiny Jarrige, panny, terciářky",
	"",
	"",
	"",
	"Bl. Kateřiny Jarrige, panny, terciářky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_04_2_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Petra Juraja Frassatiho, laika",
	"Bl. Petra Jiřího Frassatiho, terciáře",
	"",
	"",
	"",
	"Bl. Petra Jiřího Frassatiho, terciáře",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_05_LA[POCET_JAZYKOV + 1] =
{
	"Sv. Antona Máriu Zaccariu, kňaza", // SK: 07JUL
	"",
	"",
	"S. Antonii Mariæ Zaccaria, presbyteri",
	"",
	"",
	"Zaccaria Szent Antal Mária áldozópap",
	"ru_text",
	"Св. Антонія Марыі Дзаккарыя, прэзбітэра",
	"Hl. Antoníusar Maríu Sakaría, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_05_SK_CZ[POCET_JAZYKOV + 1] =
{
	"Sv. Cyrila, mnícha, a Metoda, biskupa, " HTML_LINE_BREAK "slovanských vierozvestov, patrónov Európy", // názov upravený podľa 3RM
	"Sv. Cyrila, mnicha, a Metoděje, biskupa, " HTML_LINE_BREAK "patronů Evropy, hlavních patronů Moravy",
	"",
	"",
	"",
	"Sv. Cyrila, mnicha, a Metoděje, biskupa, " HTML_LINE_BREAK "patronů Evropy, hlavních patronů Moravy",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_05_BY[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Найсв. Панны Марыі Тракельскай",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_06[POCET_JAZYKOV + 1] =
{
	"Sv. Márie Goretti, panny a mučenice",
	"Sv. Marie Gorettiové, panny a mučednice",
	"",
	"S. Mariæ Goretti, virginis et martyris",
	"",
	"Sv. Marie Gorettiové, panny a mučednice",
	"Goretti Szent Mária szűz és vértanú",
	"ru_text",
	"Св. Марыі Гарэцці, панны і мучаніцы",
	"Hl. Maríu Goretti, meyjar og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_07_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Márie Romerovej-Menesesovej, panny",
	"Bl. Marie Romero Menesesové, panny",
	"",
	"",
	"",
	"",
	"Boldog Romero Mária szűz",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_07_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Benedikta XI., pápeža",
	"Bl. Benedikta XI., papeže",
	"",
	"",
	"",
	"Bl. Benedikta XI., papeže",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_07_OCD[POCET_JAZYKOV + 1] =
{
	"Prebl. Panny Márie, Matky Božej milosti",
	"Panny Marie, Matky božské milosti", // CZ: 19JUL
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_08_IS[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Sunnivu og félaga, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_08_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Hadriána Fortescuea, mučeníka",
	"Bl. Adriána Fortescue, otce rodiny, terciáře, mučedníka",
	"",
	"",
	"",
	"Bl. Adriána Fortescue, otce rodiny, terciáře, mučedníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_08_OFM[POCET_JAZYKOV + 1] =
{
	"",
	"Sv. Řehoře Grassiho, biskupa, sv. Hermíny, panny, a druhů, mučedníků 1. a 3. řádu",
	"",
	"",
	"",
	"",
	"Szent Grassi Gergely, püspök és vértanú társai az I és a III. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_09[POCET_JAZYKOV + 1] =
{
	"Sv. Augustína Zhao Ronga, kňaza, " HTML_LINE_BREAK "a spoločníkov, mučeníkov",
	"Sv. Augustina Žao Ronga, kněze, " HTML_LINE_BREAK "a druhů, mučedníků",
	"",
	"Ss. Augustini Zhao Rong, presbyteri, " HTML_LINE_BREAK "et sociorum, martyrum",
	"",
	"Sv. Augustina Žao Ronga, kněze, " HTML_LINE_BREAK "a druhů, mučedníků",
	"Zhao Rong Szent Ágoston áldozópap és társai, kínai vértanúk",
	"ru_text",
	"Св. Аўгустына Джао Жонга, прэзбітэра, " HTML_LINE_BREAK "і паплечнікаў, мучанікаў",
	"Hl. Ágústínusar Zhao Rong, prestur, " HTML_LINE_BREAK "og félaga, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_09_OSU[POCET_JAZYKOV + 1] =
{
	"Bl. Alžbety Terézie a spoločníčok, panien a mučeníc",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_09_1_OP[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Kolínskeho, kňaza, a spoločníkov, mučeníkov",
	"",
	"",
	"",
	"",
	"Sv. Jana Kolínského, kněze, a druhů, mučedníků",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_09_2_OP[POCET_JAZYKOV + 1] =
{
	"Sv. Františka Fernándeza de Capillas, kňaza, " HTML_LINE_BREAK "sv. Petra Sansa, biskupa, sv. Augustína Zhao Ronga, kňaza, " HTML_LINE_BREAK "a spoločníkov, mučeníkov",
	"",
	"",
	"",
	"",
	"Sv. Františka Fernándeze de Capillas, kněze, " HTML_LINE_BREAK "Petra Sanse, biskupa, Augustina Žao Ronga, kněze, " HTML_LINE_BREAK "a druhů, čínských mučedníků",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_09_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Mikuláša Picka, Antona von Willehada a spoločníkov, " HTML_LINE_BREAK "mučeníkov v Holandsku, členov 1. rádu",
	"Sv. Mikuláše Picka, Antonína van Willehada a druhů, mučedníků 1. řádu",
	"",
	"",
	"",
	"",
	"Szent Nicolaus Pick, Wilhaldus és vértanú társai az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_09_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Leva Mangina, kňaza a spoločníkov, mučeníkov",
	"Sv. Lva Ignáce Mangina, kněze, Marie Zhu Wu a druhů, mučedníků",
	"",
	"",
	"",
	"Sv. Lva Ignáce Mangina, kněze, Marie Zhu Wu a druhů, mučedníků",
	"Mangin Szent Leó Ignác áldozópap, " HTML_LINE_BREAK "Zhu Wu Mária és társaik, vértanúk",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_09_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Sv. Adriána a Jakuba, kňazov z našej rehole " HTML_LINE_BREAK "a spoločníkov, gorkumských mučeníkov",
	"Sv. Adriána a Jakuba, kněží premonstrátského řádu, " HTML_LINE_BREAK "a jejich druhů, mučedníků Gorkumských",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_10_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Veroniky Giulianiovej, panny, členky 2. rádu",
	"Sv. Veroniky Giuliani, panny",
	"",
	"",
	"",
	"",
	"Giuliani Szent Veronika, szűz a II. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_11[POCET_JAZYKOV + 1] =
{
	"Sv. Benedikta, opáta, " HTML_LINE_BREAK "patróna Európy",
	"Sv. Benedikta, opata, " HTML_LINE_BREAK "patrona Evropy",
	"",
	"S. Benedicti, abbatis",
	"",
	"Sv. Benedikta, opata, " HTML_LINE_BREAK "patrona Evropy",
	"Szent Benedek apát, " HTML_LINE_BREAK "Európa fővédőszentje",
	"ru_text",
	"Св. Бэнэдыкта, абата, апекуна Еўропы",
	"l. Benedikts, ábóta " HTML_LINE_BREAK "og verndardýrlings Evrópu",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_12_OFM[POCET_JAZYKOV + 1] =
{
	"",
	"Sv. Jana Jonese a Jana Walla, kněží a mučedníků anglických",
	"",
	"",
	"",
	"",
	"Szent Joannes Jones és Joannes Wall, papok és vértanúk az I Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_12_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Ľudovíta a Márie Zélie Martinovcov",
	"Sv. Ludvíka a Zelie Martinových",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_13[POCET_JAZYKOV + 1] =
{
	"Sv. Henricha",
	"Sv. Jindřicha",
	"",
	"S. Henrici",
	"",
	"Sv. Jindřicha",
	"Szent Henrik",
	"ru_text",
	"Св. Генрыха",
	"Hl. Henriks",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_13_IS[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Margrétar frá Antiokkíu, píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_13_OFM[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Marscianói Boldog Angelina, szerzetesnő a III. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_13_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Jakuba z Varazze, biskupa",
	"Bl. Jakuba z Varazze, biskupa",
	"",
	"",
	"",
	"Bl. Jakuba z Varazze, biskupa",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_13_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Terézie od Ježiša de Los Andes, panny",
	"Sv. Terezie od Ježíše (z Los Andes), panny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Teresu af Jesú de Los Andes, meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_14[POCET_JAZYKOV + 1] =
{
	"Sv. Kamila z Lellisu, kňaza", // podľa 3RM; predtým: Kamila de Lellis
	"Sv. Kamila de Lellis, kněze",
	"",
	"S. Camilli de Lellis, presbyteri",
	"",
	"Sv. Kamila de Lellis, kněze",
	"Lellisi Szent Kamill áldozópap",
	"ru_text",
	"Св. Каміла Леліскага, прэзбітэра",
	"Hl. Kamillusar frá Lellis, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_14_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Františka Solanského, kňaza, člena 1. rádu",
	"Sv. Františka Solanského, kněze",
	"",
	"",
	"",
	"Sv. Františka Solanského, kněze",
	"Szolánói Szent Ferenc, pap az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_14_CZ[POCET_JAZYKOV + 1] =
{
	"Bl. Hroznatu, mučeníka",
	"Bl. Hroznaty, mučedníka",
	"",
	"",
	"",
	"Bl. Hroznaty, mučedníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_14_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Bl. Hroznatu, mučeníka našej rehole",
	"Bl. Hroznaty, mučedníka z premonstrátského řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_15[POCET_JAZYKOV + 1] =
{
	"Sv. Bonaventúru, biskupa a učiteľa Cirkvi",
	"Sv. Bonaventury, biskupa a učitele církve",
	"",
	"S. Bonaventuræ, episcopi et Ecclesiæ doctoris",
	"",
	"Sv. Bonaventury, biskupa a učitele církve",
	"Szent Bonaventura püspök és egyháztanító",
	"ru_text",
	"Св. Бонавэнтуры, біскупа і доктара Касцёла",
	"Hl. Bónaventura, biskups og kirkjufræðari",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_15_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Bonaventúru z Bagnoregia, biskupa a učiteľa Cirkvi, člena 1. rádu",
	"Sv. Bonaventury z Bagnoregia, biskupa a učitele církve",
	"",
	"",
	"",
	"",
	"Szent Bonaventura, püspök és egyháztanító az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_15_SCHP[POCET_JAZYKOV + 1] =
{
	"sk_text",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_16[POCET_JAZYKOV + 1] =
{
	"Prebl. Panny Márie Karmelskej",
	"Panny Marie Karmelské",
	"",
	"Beatæ Mariæ Virginis de Monte Carmelo",
	"",
	"Panny Marie Karmelské",
	"Kármelhegyi Boldogságos Szűz Mária",
	"ru_text",
	"Найсв. Панны Марыі з гары Кармэль",
	"Hl. Maríu meyjar frá Karmelfjalli",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_16_OCD[POCET_JAZYKOV + 1] =
{
	"Prebl. Panny Márie z hory Karmel",
	"Panny Marie Karmelské",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. María mey frá Karmelfjalli",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_16_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Výročí posvěcení katedrály Božského Spasitele",
	"",
	"",
	"",
	"Výročí posvěcení katedrály Božského Spasitele",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_17_SK[POCET_JAZYKOV + 1] =
{
	"Sv. Andreja Svorada a Beňadika, pustovníkov", // od r. 2016 direktórium nepoužíva spojovník, kedysi: "Andreja-Svorada"; 3RM: Beňadika; predtým: Beneditka
	"",
	"",
	"Ss. Andreæ-Zœrardi et Benedicti, eremitarum",
	"",
	"",
	"Szent Zoerárd-András és Benedek remeték",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_17_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Bl. Česlava a sv. Hyacinta, kněží",
	"",
	"",
	"",
	"Bl. Česlava a sv. Hyacinta, kněží",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_17_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Česlava Poľského, kňaza",
	"Bl. Česlava z Polska, kněze",
	"",
	"",
	"",
	"Bl. Česlava z Polska, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_17_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Terézie od sv. Augustína a spoločníčok, panien a mučeníc", // SK: 18JUL
	"Bl. Terezie od sv. Augustina a spolusester, panen a mučednic",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"l. Teresu af hl. Ágústínusi og félaga, meyja og píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_18_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Szent Hedvig királynő",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_18_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Bartolomeja od Mučeníkov, biskupa",
	"Bl. Bartoloměje od Mučedníků, biskupa",
	"",
	"",
	"",
	"Bl. Bartoloměje od Mučedníků, biskupa",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_18_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Šimona z Lipnice, kňaza, člena 1. rádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_19_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Jána z Dukly, kňaza, člena 1. rádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_20[POCET_JAZYKOV + 1] =
{
	"Sv. Apolinára, biskupa a mučeníka",
	"Sv. Apolináře, biskupa a mučedníka",
	"",
	"S. Apollinaris, episcopi et martyris",
	"",
	"Sv. Apolináře, biskupa a mučedníka",
	"Szent Apollinaris püspök és vértanú",
	"ru_text",
	"Св. Апалінарыя, біскупа і мучаніка",
	"Hl. Appollinaris, biskups og píslarvottur",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_20_IS[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Þorláks, verndardýrlings Íslendinga",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_20_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Eliáša, proroka a nášho Otca",
	"Sv. Eliáše, proroka", // CZ: nemá "a našeho Otce"
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_21[POCET_JAZYKOV + 1] =
{
	"Sv. Vavrinca z Brindisi, kňaza a učiteľa Cirkvi",
	"Sv. Vavřince z Brindisi, kněze a učitele církve",
	"",
	"S. Laurentii de Brindisi, presbyteri et Ecclesiæ doctoris",
	"",
	"Sv. Vavřince z Brindisi, kněze a učitele církve",
	"Brindisi Szent Lőrinc áldozópap és egyháztanító",
	"ru_text",
	"Св. Лаўрэнція з Брындызі, прэзбітэра і доктара Касцёла",
	"Hl. Lárentíusar frá Brindisi, prests og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_21_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Vavrinca z Brindisi, kňaza a učiteľa Cirkvi, člena 1. rádu",
	"Sv. Vavřince z Brindisi, kněze a učitele církve",
	"",
	"S. Laurentii de Brindisi, presbyteri et Ecclesiæ doctoris",
	"",
	"Sv. Vavřince z Brindisi, kněze a učitele církve, člena 1. řádu",
	"Brindisi Szent Lőrinc, pap és Egyháztanító az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_21_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Títa Brandsmu, kňaza a mučeníka",
	"Bl. Tita Brandsmy, kněze a mučedníka", // 27JUL
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_22[POCET_JAZYKOV + 1] =
{
	"Sv. Márie Magdalény",
	"Sv. Marie Magdalény",
	"",
	"S. Mariæ Magdalenæ",
	"",
	"Sv. Marie Magdalény",
	"Szent Mária Magdolna",
	"ru_text",
	"Св. Марыі Магдалены",
	"Hl. Maríu Magdalenu",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_23[POCET_JAZYKOV + 1] =
{
	"Sv. Brigity, rehoľníčky, " HTML_LINE_BREAK "patrónky Európy",
	"Sv. Brigity, řeholnice, " HTML_LINE_BREAK "patronky Evropy",
	"",
	"S. Brigitæ, religiosæ",
	"",
	"Sv. Brigity, řeholnice, " HTML_LINE_BREAK "patronky Evropy",
	"Szent Brigitta szerzetesnő, " HTML_LINE_BREAK "Európa társvédőszentje",
	"ru_text",
	"Св. Брыгіты, законніцы, апякункі Еўропы",
	"Hl. Birgittu, reglustofnanda " HTML_LINE_BREAK "og verndardýrlings Evrópu",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_24[POCET_JAZYKOV + 1] =
{
	"Sv. Šarbela Machlúfa, kňaza", // 2009-07-15: direktórium (2012, str. 171) má "Sarbel", predtým bolo "Charbel" ale číta sa "Šarbel", tak Direktórium 2020/2012; kedysi priezvisko: Makhluf, po novom fonetický prepis: Machlúf
	"Sv. Šarbela Makhlufa, kněze",
	"",
	"S. Sarbelii Makhlūf, presbyteri",
	"",
	"Sv. Šarbela Makhlufa, kněze",
	"Szent Charbel Makhlouf áldozópap", // HU: 27JUL
	"ru_text",
	"Св. Шарбэля Маклуфа, прэзбітэра",
	"Hl. Sarbel Makhlūf, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_24_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Árpád-házi Szent Kinga szűz", // 2011-07-05: sv. Sarbela v HU: 27JUL
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_24_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Antona Lucciho, biskupa, člena 1. rádu",
	"",
	"",
	"",
	"",
	"",
	"Savoiai Boldog Ludovica, szerzetesnő a II. Rendből", // HU: different saint!
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_24_1_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Jany z Orvieta, panny",
	"Bl. Jany z Orvieta, panny, terciářky",
	"",
	"",
	"",
	"Bl. Jany z Orvieta, panny, terciářky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_24_2_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Augustína z Biella, kňaza",
	"Bl. Augustina z Bielly, kněze",
	"",
	"",
	"",
	"Bl. Augustina z Bielly, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_24_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Márie Pilar od sv. Františka Borgiáša, " HTML_LINE_BREAK "Márie Sagrario od sv. Alojza Gonzágu " HTML_LINE_BREAK "a spoločníčok, panien a mučeníc",
	"Bl. Marie Pilar, Marie Sagrario od sv. Aloise Gonzagy " HTML_LINE_BREAK "a družek, panen a mučednic",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Bl. Maríu Pilar og bl. Maríu Angeles, meyja og píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_25[POCET_JAZYKOV + 1] =
{
	"Sv. Jakuba, apoštola",
	"Sv. Jakuba, apoštola",
	"",
	"S. Iacobi, apostoli",
	"",
	"Sv. Jakuba, apoštola",
	"Szent Jakab apostol",
	"ru_text",
	"Св. Якуба, апостала",
	"Hl. Jakobs, postula",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_26[POCET_JAZYKOV + 1] =
{
	"Sv. Joachima a Anny, rodičov prebl. Panny Márie", // doplnené "prebl." podľa 3RM
	"Sv. Jáchyma a Anny, rodičů Panny Marie",
	"",
	"Ss. Ioachim et Annæ, parentum Beatæ Mariæ Virginis",
	"",
	"Sv. Jáchyma a Anny, rodičů Panny Marie",
	"Szent Joakim és Szent Anna, a Boldogságos Szűz Mária szülei",
	"ru_text",
	"Св. Яўхіма і Ганны, бацькоў Найсв. Панны Марыі",
	"Hl. Jóakims og hl. Önnu, foreldra Maríu meyjar", // Anna?
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_27[POCET_JAZYKOV + 1] =
{
	"Sv. Gorazda a spoločníkov",
	"Sv. Gorazda a druhů",
	"",
	"S. Gorasdi et sociorum",
	"",
	"Sv. Gorazda a druhů",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_27_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Róberta Nuttera, kňaza a mučeníka",
	"Bl. Roberta Nuttera, kněze a mučedníka",
	"",
	"",
	"",
	"Bl. Roberta Nuttera, kněze a mučedníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_28_1_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Márie Magdalény Martinengovej, panny, členky 2. rádu",
	"Bl. Marie Magdalény Martinengo, panny",
	"",
	"",
	"",
	"",
	"Boldog Martinengo Mária Magdolna, szűz a II. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_28_2_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Márie Terézie Kowalskej, panny a mučenice, členky 2. rádu",
	"Bl. Terezie Kowalské, panny a mučednice",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_28_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Jána Soretha, kňaza",
	"Bl. Jana Soretha, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_29[POCET_JAZYKOV + 1] =
{
	"Sv. Marty, Márie a Lazára",
	"Sv. Marty, Marie a Lazara",
	"",
	"Ss. Marthæ, Mariæ et Lazari",
	"",
	"Sv. Marty, Marie a Lazara",
	"Szent Márta, Szent Mária és Szent Lázár",
	"ru_text",
	"Св. Марты", // ToDo
	"Hl. Mörtu, Maríu og Lasarusar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_29_IS[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Ólafs, píslarvotts, og verndardýrlings Noregs",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_30[POCET_JAZYKOV + 1] =
{
	"Sv. Petra Chryzológa, biskupa a učiteľa Cirkvi",
	"Sv. Petra Chryzologa, biskupa a učitele církve",
	"",
	"S. Petri Chrysologi, episcopi et Ecclesiæ doctoris",
	"",
	"Sv. Petra Chryzologa, biskupa a učitele církve",
	"Aranyszavú (Krizologosz) Szent Péter püspök és egyháztanító",
	"ru_text",
	"Св. Пятра Хрызалога, біскупа і доктара Касцёла",
	"Hl. Péturs Krýsológus, biskups og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_30_SK[POCET_JAZYKOV + 1] =
{
	"Bl. Zdenky Cecílie Schelingovej, panny a mučenice", // Direktórium 2012, str. 173, neuvádza priezvisko ('Schelingovej'); dekrét https://www.kbs.sk/obsah/sekcia/h/dokumenty-a-vyhlasenia/p/dokumenty-kbs/c/dekret-o-doplneni-partikularneho-kalendara-2016 uvádza plné meno (aj 3RM, 2021)
	"",
	"",
	"B. Sidoniæ Schelling, virginis et martyris",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_30_SK_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Zdenky Cecílie Schelingovej, panny a mučenice, " HTML_LINE_BREAK "rehoľníčky, členky 3. rádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_30_CM[POCET_JAZYKOV + 1] =
{
	"Sv. Justína de Iacobis, biskupa",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_30_OFMCAP[POCET_JAZYKOV + 1] =
{
	"Bl. Františka Solana Caseyho, kňaza",
	"Bl. Františka Solana Caseyho, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_31[POCET_JAZYKOV + 1] =
{
	"Sv. Ignáca z Loyoly, kňaza",
	"Sv. Ignáce z Loyoly, kněze",
	"",
	"S. Ignatii de Loyola, presbyteri",
	"",
	"Sv. Ignáce z Loyoly, kněze",
	"Loyolai Szent Ignác áldozópap",
	"ru_text",
	"Св. Ігнацыя Лаёлы, прэзбітэра",
	"Hl. Ignatíusar frá Loyola, prests og reglustofnanda",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_JUL_31_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Ignáca Loyolského, kňaza a zakladateľa Spoločnosti Ježišovej",
	"Sv. Ignáce z Loyoly, kněze a zakladatele Tovaryšstva Ježíšova",
	"",
	"",
	"",
	"Sv. Ignáce z Loyoly, kněze a zakladatele Tovaryšstva Ježíšova",
	"Loyolai Szent Ignác áldozópap és Jézus Társaságának alapítója",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// --------------- 00 pohyblivé slávenia ---------------

const char* text_POSVIACKA_KATEDRALNEHO_CHRAMU[POCET_JAZYKOV + 1] =
{
	"Výročie posviacky katedrálneho chrámu",
	"Výročí posvěcení katedrály",
	"",
	"Anniversarium consecrationis ecclesiæ cathedralis",
	"",
	"Výročí posvěcení katedrály",
	"A székesegyház felszentelése",
	"ru_text",
	"Гадавіна пасвячэння катэдральнага касцёла",
	"Vígsluafmæli dómkirkju",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* text_CSSR_TITUL_KONGREGACIE[POCET_JAZYKOV + 1] =
{
	"Najsvätejšieho Vykupiteľa, titul Kongregácie", // 3. nedeľa v júli
	"Nejsvětějšího Vykupitele, titul kongregace", // v každém roce 3. neděle v červenci
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// --------------- 08 august ---------------

const char* text_AUG_01[POCET_JAZYKOV + 1] =
{
	"Sv. Alfonza Máriu de’ Liguori, biskupa a učiteľa Cirkvi",
	"Sv. Alfonsa Marie z Liguori, biskupa a učitele církve",
	"",
	"S. Alfonsi Mariæ de’ Liguori, episcopi et Ecclesiæ doctoris",
	"",
	"Sv. Alfonsa Marie z Liguori, biskupa a učitele církve",
	"Liguori Szent Alfonz Mária püspök és egyháztanító",
	"ru_text",
	"Св. Альфонса Марыі Лігуоры, біскупа і доктара Касцёла",
	"Hl. Alfonsar Maríu frá Lígúrí, biskups og  kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_01_CSSR[POCET_JAZYKOV + 1] =
{
	"Sv. Alfonza Máriu de’ Liguori, biskupa a učiteľa Cirkvi, zakladateľa kongregácie",
	"Sv. Alfonsa z Liguori, biskupa a učitele církve, zakladatele kongregace",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_02_1[POCET_JAZYKOV + 1] =
{
	"Sv. Euzébia Vercellského, biskupa",
	"Sv. Eusebia z Vercelli, biskupa",
	"",
	"S. Eusebii Vercellensis, episcopi",
	"",
	"Sv. Eusebia z Vercelli, biskupa",
	"Vercelli Szent Özséb püspök",
	"ru_text",
	"Св. Эўзэбія Вэрчэльскага, біскупа",
	"Hl. Efsebíusar frá Vercelli, biskups", // Evsebíus?
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_02_2[POCET_JAZYKOV + 1] =
{
	"Sv. Petra Juliána Eymarda, kňaza",
	"Sv. Petra Juliána Eymarda, kněze",
	"",
	"S. Petri Iuliani Eymard, presbyteri",
	"",
	"Sv. Petra Juliána Eymarda, kněze",
	"Eymard Szent Julián Péter áldozópap",
	"ru_text",
	"Св. Пятра Юліяна Эймарда, прэзбітэра",
	"Hl. Péturs Julian Eymard, prests", // Júlíanus?
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_02_OFM[POCET_JAZYKOV + 1] =
{
	"Prebl. Panny Márie Anjelskej v Porciunkule",
	"Panny Marie Andělské z Porciunkule", // "Panny Marie Královny andělů",
	"",
	"",
	"",
	"",
	"Angyalos Boldogasszony (Portiuncula)",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_02_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Jany z Azy, matky sv. otca Dominika",
	"",
	"",
	"",
	"",
	"Bl. Jany, matky sv. otce Dominika",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_03_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Augustína Kazotića, biskupa",
	"",
	"",
	"",
	"",
	"Bl. Augustina Kazotiče, biskupa",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_02_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Augustína Czartoryského, kňaza",
	"Bl. Augustina Czartoryského, kněze",
	"",
	"",
	"",
	"",
	"Boldog Czartoryski Ágoston áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_02_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Petra Favra, kňaza",
	"Sv. Petra Fabera, kněze",
	"",
	"",
	"",
	"Sv. Petra Fabera, kněze",
	"Favre Szent Péter, áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_04[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Máriu Vianneya, kňaza", // 'Vianneyho' podľa Direktória 2012, str. 176; späť na 'Vianneya' podľa Direktória 2020
	"Sv. Jana Marie Vianneye, kněze",
	"",
	"S. Ioannis Mariæ Vianney, presbyteri",
	"",
	"Sv. Jana Marie Vianneye, kněze",
	"Vianney Szent János Mária áldozópap",
	"ru_text",
	"Св. Яна Марыі Віянэя, прэзбітэра",
	"Hl. Jóhannesar Maríu Vianney, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_05[POCET_JAZYKOV + 1] =
{
	"Výročie posviacky hlavnej mariánskej baziliky v Ríme", // malé 'h' podľa 3RM
	"Posvěcení římské baziliky Panny Marie",
	"",
	"In dedicatione Basilicæ s. Mariæ",
	"",
	"Posvěcení římské baziliky Panny Marie",
	"Szűz Mária római főtemplomának felszentelése (Havas Boldogasszony)",
	"ru_text",
	"Гадавіна пасвячэння рымскай базілікі Найсв. Панны Марыі",
	"Vígsludagur Maríukirkju hinnar meiri í Róm",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_05_BY[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Найсв. Панны Марыі Кангрэгацкай (Студэнцкай)",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_06[POCET_JAZYKOV + 1] =
{
	"Premenenie Pána",
	"Proměnění Páně",
	"",
	"In Transfiguratione Domini",
	"",
	"Proměnění Páně",
	"Urunk színeváltozása",
	"ru_text",
	"Перамяненне Пана",
	"Ummyndun Drottins",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_07_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Alberta z Trapani, kňaza",
	"Sv. Alberta z Trapani, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Alberts frá Trapani, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_07_1[POCET_JAZYKOV + 1] =
{
	"Sv. Sixta II., pápeža, a jeho spoločníkov, mučeníkov",
	"Sv. Sixta II., papeže, a druhů, mučedníků",
	"",
	"Ss. Xysti II, Papæ, et sociorum, martyrum",
	"",
	"Sv. Sixta II., papeže, a druhů, mučedníků",
	"Szent II. Szixtusz pápa és társai vértanúk",
	"ru_text",
	"Св. Сікста II, папы, і паплечнікаў, мучанікаў",
	"Hl. Sixtusar II., páfa, og félaga, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_07_2[POCET_JAZYKOV + 1] =
{
	"Sv. Kajetána, kňaza",
	"Sv. Kajetána, kněze",
	"",
	"S. Caietani, presbyteri",
	"",
	"Sv. Kajetána, kněze",
	"Szent Kajetán áldozópap",
	"ru_text",
	"Св. Каятана, прэзбітэра",
	"Hl. Kajetanusar, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_07_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Agatangela a Kasiána, kňazov a mučeníkov, " HTML_LINE_BREAK "členov 1. rádu",
	"Bl. Agathangela a Kassiána, kněží a mučedníků",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_08[POCET_JAZYKOV + 1] =
{
	"Sv. Dominika, kňaza",
	"Sv. Dominika, kněze",
	"",
	"S. Dominici, presbyteri",
	"",
	"Sv. Dominika, kněze",
	"Szent Domonkos áldozópap",
	"ru_text",
	"Св. Дамініка, прэзбітэра",
	"Hl. Dóminíkusar, prests og reglustofnanda",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_08_OP[POCET_JAZYKOV + 1] =
{
	"Sv. Dominika, kňaza, zakladateľa rehole",
	"Sv. otce Dominika, kněze",
	"",
	"S. Dominici, presbyteri",
	"",
	"Sv. otce Dominika, kněze",
	"Szent Domonkos áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_08_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Dominika, kňaza, " HTML_LINE_BREAK "zakladateľa Rádu dominikánov",
	"Sv. Dominika, kněze",
	"",
	"S. Dominici, presbyteri",
	"",
	"Sv. Dominika, kněze",
	"Szent Domonkos atya, pap, a Prédikátorok Rendjének Alapítója",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_09[POCET_JAZYKOV + 1] =
{
	"Sv. Terézie Benedikty od Kríža, " HTML_LINE_BREAK "panny a mučenice, patrónky Európy", // podľa Direktória 2012, str. 178: "Sv. Terézie Benedikty z Kríža (Edity Steinovej), "; Direktórium 2020: oprava
	"Sv. Terezie Benedikty od Kříže, panny a mučednice, " HTML_LINE_BREAK "patronky Evropy",
	"",
	"S. Teresiæ Benedictæ et Cruce, virginis et martyris",
	"",
	"Sv. Terezie Benedikty od Kříže, panny a mučednice, " HTML_LINE_BREAK "patronky Evropy",
	"A keresztről nevezett Szent Teréz Benedikta (Edith Stein) " HTML_LINE_BREAK "szűz és vértanú, Európa társvédőszentje",
	"ru_text",
	"Св. Тэрэзы Бэнэдыкты ад Крыжа (Эдыты Штайн), " HTML_LINE_BREAK "панны і мучаніцы, апякункі Еўропы",
	"Hl. Teresu Benediktu af krossinum, píslarvotts, " HTML_LINE_BREAK "verndardýrlings Evrópu",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_09_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Jána zo Salerna, kňaza",
	"",
	"",
	"",
	"",
	"Bl. Jana ze Salerna, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_09_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Terézie Benedikty od Kríža, panny a mučenice, patrónky Európy",
	"Sv. Terezie Benedikty od Kříže (Edith Stein), " HTML_LINE_BREAK "panny a mučednice, patronky Evropy",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Teresu Benediktu af krossinum, píslarvotts, " HTML_LINE_BREAK "verndardýrlings Evrópu",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_10[POCET_JAZYKOV + 1] =
{
	"Sv. Vavrinca, diakona a mučeníka",
	"Sv. Vavřince, mučedníka",
	"",
	"S. Laurentii, diaconi et martyris",
	"",
	"Sv. Vavřince, mučedníka",
	"Szent Lőrinc diakónus és vértanú",
	"ru_text",
	"Св. Лаўрэнція, дыякана і мучаніка",
	"Hl. Lárentíusar, djákna og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_11[POCET_JAZYKOV + 1] =
{
	"Sv. Kláry, panny",
	"Sv. Kláry, panny",
	"",
	"S. Claræ, virginis",
	"",
	"Sv. Kláry, panny",
	"Szent Klára szűz",
	"ru_text",
	"Св. Клары, панны",
	"Hl. Klöru frá Assisí, meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_11_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Kláry z Assisi, panny, členky 2. rádu",
	"Sv. Kláry z Assisi, panny",
	"",
	"",
	"",
	"Sv. Kláry, panny",
	"Assisi Szent Klára, szűz a II. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_12[POCET_JAZYKOV + 1] =
{
	"Sv. Jany Františky de Chantal, rehoľníčky", // kedysi sa slávil 12. decembra
	"Sv. Jany Františky de Chantal, řeholnice",
	"",
	"S. Ioannæ Franciscæ de Chantal, religiosæ",
	"",
	"Sv. Jany Františky de Chantal, řeholnice",
	"Chantal Szent Johanna Franciska szerzetesnő",
	"ru_text",
	"Св. Жаны Франсуазы дэ Шанталь, законніцы",
	"Hl. Jóhönnu Fransisku Chantal",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_12_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Jána Juraja Rehma, kňaza a mučeníka",
	"",
	"",
	"",
	"",
	"Bl. Jana Jiřího Rehma, kněze a mučedníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_13[POCET_JAZYKOV + 1] =
{
	"Sv. Ponciána, pápeža, a Hipolyta, kňaza, mučeníkov", // kedysi "Sv. Ponciána, pápeža, a sv. Hypolita, kňaza, mučeníkov"
	"Sv. Ponciána, papeže, a Hippolyta, kněze, mučedníků",
	"",
	"Ss. Pontiani, papæ, et Hippolyti, presbyteri, martyrum",
	"",
	"Sv. Ponciána, papeže, a Hippolyta, kněze, mučedníků",
	"Szent Ponciánusz pápa és Szent Hippolitusz áldozópap vértanúk", // HU: 16AUG
	"ru_text",
	"Св. Пантыяна, папы, і Гіпаліта, прэзбітэра, мучанікаў",
	"Hl. Pontíanusar páfa og Hippolýtusar prests, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_13_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Boldog XI. Ince pápa", // HU
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_13_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Bl. Gertrúdy, panny našej rehole",
	"Bl. Gertrudy, panny z premonstrátského řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_13_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Marka z Aviana, kňaza, člena 1. rádu",
	"Bl. Marka z Aviana, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_13_OP[POCET_JAZYKOV + 1] =
{
	"Sv. Alexandra Longu, kňaza, a spoločníkov, mučeníkov",
	"",
	"",
	"",
	"",
	"Sv. Alexandra Longa, kněze, a druhů, mučedníků",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_14[POCET_JAZYKOV + 1] =
{
	"Sv. Maximiliána Máriu Kolbeho, kňaza a mučeníka", // podľa Direktória 2012, str. 180
	"Sv. Maxmiliána Marie Kolbeho, kněze a mučedníka",
	"",
	"S. Maximiliani Mariæ Kolbe, presbyteri et martyris",
	"",
	"Sv. Maxmiliána Marie Kolbeho, kněze a mučedníka",
	"Szent Maximilián Mária Kolbe áldozópap és vértanú",
	"ru_text",
	"Св. Максімільяна Марыі Кольбэ, прэзбітэра і мучаніка",
	"l. Maximilíans Maríu Kolbe, prests og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_14_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Aimona Taparelliho, kňaza",
	"",
	"",
	"",
	"",
	"Bl. Aima Taparelliho, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_14_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Maximiliána Máriu Kolbeho, " HTML_LINE_BREAK "kňaza a mučeníka, člena 1. rádu",
	"Sv. Maxmiliána Marie Kolbeho, kněze a mučedníka",
	"",
	"S. Maximiliani Mariæ Kolbe, presbyteri et martyris",
	"",
	"Sv. Maxmiliána Marie Kolbeho, kněze a mučedníka",
	"Szent Maximilián Mária Kolbe áldozópap és vértanú",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_15[POCET_JAZYKOV + 1] =
{
	"Nanebovzatie prebl. Panny Márie", // kedysi: "Nanebovzatie prebl. Panny Márie"; 3RM: PREBLAHOSLAVENEJ
	"Nanebevzetí Panny Marie",
	"",
	"In Assumptione Beatæ Mariæ Virginis",
	"",
	"Nanebevzetí Panny Marie",
	"Szűz Mária mennybevétele (Nagyboldogasszony)",
	"ru_text",
	"Унебаўзяцце Найсв. Панны Марыі",
	"Uppnumning Maríu meyjar til himna",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_16[POCET_JAZYKOV + 1] =
{
	"Sv. Štefana Uhorského",
	"Sv. Štěpána Uherského",
	"",
	"S. Stephani Hungariæ",
	"",
	"Sv. Štěpána Uherského",
	"Szent István király, Magyarország fővédőszentje",
	"ru_text",
	"Св. Стэфана Венгерскага",
	"Hl. Stefáns frá Ungverjalandi",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_16_2[POCET_JAZYKOV + 1] =
{
	"Sv. Rocha", // not used yet
	"Sv. Rocha", // CZ: OPraem only
	"",
	"",
	"",
	"",
	"Szent Rókus hitvalló", // HU: general calendar
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_17_OP[POCET_JAZYKOV + 1] =
{
	"Sv. Hyacinta Poľského, kňaza",
	"",
	"",
	"",
	"",
	"Sv. Hyacinta z Polska, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_17_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Beatrix de Silva, panny, zakladateľky " HTML_LINE_BREAK "koncepcionistiek, členky 2. rádu",
	"Sv. Beatrice de Silva, panny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_17_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Kaposvár: A székesegyház felszentelése",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_18[POCET_JAZYKOV + 1] =
{
	"Sv. Heleny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_18_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Vác: A székesegyház felszentelése",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_18_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Alberta Hurtada Cruchagu, kňaza",
	"Sv. Alberta Hurtado Cruchaga, kněze",
	"",
	"",
	"",
	"Sv. Alberta Hurtado Cruchaga, kněze",
	"Hurtado Cruchaga Szent Albert, áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_18_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Manesa, kňaza, brata sv. otca Dominika",
	"",
	"",
	"",
	"",
	"Bl. Mannesa, kněze, bratra sv. otce Dominika",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_18_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Jána Krstiteľa, Michala Alojza a Jakuba, " HTML_LINE_BREAK "kňazov, a spoločníkov, mučeníkov",
	"Bl. Jana Křtitele (Leonarda) Duvernevila, Michaela Ludvíka Brularda" HTML_LINE_BREAK " a Jakuba Gagnota, a druhů, mučedníků",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Bl. Jóhannesar skírara, Mikaels Aloisius og Jakobs, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_18_1_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Alojza Adama a Mikuláša Savoureta, " HTML_LINE_BREAK "kňazov a mučeníkov, členov 1. rádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_18_2_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Jána, Protáza a Sebastiána, kňazov, " HTML_LINE_BREAK "členov 1. rádu, a spoločníkov, mučeníkov",
	"Bl. Jana Ludvíka, Protasia a Sebastiana, kněží a mučedníků",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_19[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Eudesa, kňaza",
	"Sv. Jana Eudese, kněze",
	"",
	"S. Ioannis Eudes, presbyteri",
	"",
	"Sv. Jana Eudese, kněze",
	"Eudes Szent János áldozópap",
	"ru_text",
	"Св. Яна Эда, прэзбітэра",
	"Hl. Jóhannesar Eudes, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_19_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Jordána z Pisy, kňaza",
	"",
	"",
	"",
	"",
	"Bl. Jordána z Pisy, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_19_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Ľudovíta, biskupa, člena 1. rádu",
	"Sv. Ludvíka z Anjou, biskupa", // CZ OFM: Sv. Ludvíka, biskupa tuluského
	"",
	"",
	"",
	"",
	"Szent Lajos, püspök az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_20[POCET_JAZYKOV + 1] =
{
	"Sv. Bernarda, opáta a učiteľa Cirkvi",
	"Sv. Bernarda, opata a učitele církve",
	"",
	"S. Bernardi, abbatis et Ecclesiæ doctoris",
	"",
	"Sv. Bernarda, opata a učitele církve",
	"Szent Bernát apát és egyháztanító", // HU 19AUG
	"ru_text",
	"Св. Бэрнарда, абата і доктара Касцёла",
	"Hl. Bernharðs, ábóta og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_21[POCET_JAZYKOV + 1] =
{
	"Sv. Pia X., pápeža",
	"Sv. Pia X., papeže",
	"",
	"S. Pii X, papæ",
	"",
	"Sv. Pia X., papeže",
	"Szent X. Piusz pápa",
	"ru_text",
	"Св. Пія X, папы",
	"Hl. Píusar X., páfa",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OPATSKY_KOSTOL_OPRAEM[POCET_JAZYKOV + 1] =
{
	"",
	"Výročí posvěcení opatského kostela",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_22[POCET_JAZYKOV + 1] =
{
	"Prebl. Panny Márie Kráľovnej", // podľa Direktória 2012, str. 183; 2018, str. 225, tam nie je 'Prebl.'; 3RM má PREBLAHOSLAVENEJ
	"Panny Marie Královny",
	"",
	"Beatæ Mariæ Virginis Reginæ",
	"",
	"Panny Marie Královny",
	"Boldogságos Szűz Mária Királynő",
	"ru_text",
	"Найсв. Панны Марыі Каралевы",
	"Hl. Maríu meyjar og drottningar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_23[POCET_JAZYKOV + 1] =
{
	"Sv. Ruženy Limskej, panny",
	"Sv. Růženy z Limy, panny",
	"",
	"S. Rosæ de Lima, virginis",
	"",
	"Sv. Růženy z Limy, panny, terciářky",
	"Limai Szent Róza szűz",
	"ru_text",
	"Св. Ружы Лімскай, панны",
	"Hl. Rósu frá Líma, meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_23_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Bernarda z Offidy, rehoľníka, člena 1. rádu",
	"Bl. Bernarda z Offidy, řeholníka",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_24[POCET_JAZYKOV + 1] =
{
	"Sv. Bartolomeja, apoštola",
	"Sv. Bartoloměje, apoštola",
	"",
	"S. Bartholomæi, apostoli",
	"",
	"Sv. Bartoloměje, apoštola",
	"Szent Bertalan apostol",
	"ru_text",
	"Св. Барталамея, апостала",
	"Hl. Barthólómeusar, postula",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_25_1[POCET_JAZYKOV + 1] =
{
	"Sv. Jozefa Kalazanského, kňaza", // kedysi: "Sv. Jozefa de Calasanz, kňaza"
	"Sv. Josefa Kalasanského, kněze",
	"",
	"S. Ioseph de Calasanz, presbyteri",
	"",
	"Sv. Josefa Kalasanského, kněze",
	"Kalazanci Szent József áldozópap",
	"ru_text",
	"Св. Юзафа Каласанса, прэзбітэра",
	"Hl. Jósefs frá Calasanz, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_25_2[POCET_JAZYKOV + 1] =
{
	"Sv. Ľudovíta",
	"Sv. Ludvíka",
	"",
	"S. Ludovici",
	"",
	"Sv. Ludvíka",
	"Szent Lajos",
	"ru_text",
	"Св. Людвіка",
	"Hl. Lúðvíks",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_25_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Ľudovíta IX., kráľa, člena 3. rádu",
	"Sv. Ludvíka IX., krále, patrona 3. řádu",
	"",
	"",
	"",
	"",
	"Szent IX. Lajos, király a III. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_25_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Sv. Benedikta, Jana, Matouše, Izáka a Kristina, mučedníků",
	"",
	"",
	"",
	"Sv. Benedikta, Jana, Matouše, Izáka a Kristina, mučedníků",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_25_2_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Bl. Metoděje Dominika Trčky, mučedníka",
	"",
	"",
	"",
	"Bl. Metoděje Dominika Trčky, mučedníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_25_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Kalocsa-Kecskemét: A főszékesegyház felszentelése",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_25_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Márie Troncattiovej, panny",
	"Bl. Marie Troncattiové, panny",
	"",
	"",
	"",
	"",
	"Boldog Troncatti Mária szűz",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_25_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Márie od Ukrižovaného Ježiša, panny",
	"Sv. Miriam od Ukřižovaného (Mariam Baouardy)",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Maríu af hinum krossfesta Jesú, meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_25_SCHP[POCET_JAZYKOV + 1] =
{
	"sk_text",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_26_BY[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Найсв. Панны Марыі Чанстахоўскай",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_26_OCD[POCET_JAZYKOV + 1] =
{
	"Spomienka prebodnutia srdca sv. Terézie od Ježiša, našej matky",
	"Probodení srdce sv. Terezie od Ježíše",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Minning þess að engill laust kærleikseldi Guðs í hjarta hl.Teresu af Jesú",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_26_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Zefirína Namuncurá, mladíka",
	"Bl. Zefyrina Namuncurá, chlapce",
	"",
	"",
	"",
	"",
	"Boldog Namuncurá Ceferino ifjú",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_26_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Jakuba z Bevagna, kňaza",
	"",
	"",
	"",
	"",
	"Bl. Jakuba z Bevagny, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_27[POCET_JAZYKOV + 1] =
{
	"Sv. Moniky",
	"Sv. Moniky",
	"",
	"S. Monicæ",
	"",
	"Sv. Moniky",
	"Szent Mónika",
	"ru_text",
	"Св. Монікі",
	"Hl. Móniku",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_27_AUG[POCET_JAZYKOV + 1] =
{
	"Sv. Moniky, matky nášho svätého otca Augustína", // SK CSA, SK OPraem
	"Sv. Moniky, matky našeho otce sv. Augustina", // CZ OPraem
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_28[POCET_JAZYKOV + 1] =
{
	"Sv. Augustína, biskupa a učiteľa Cirkvi",
	"Sv. Augustina, biskupa a učitele církve",
	"",
	"S. Augustini, episcopi et Ecclesiæ doctoris",
	"",
	"Sv. Augustina, biskupa a učitele církve",
	"Szent Ágoston püspök és egyháztanító",
	"ru_text",
	"Св. Аўгустына, біскупа і доктара Касцёла",
	"Hl.  Ágústínusar, biskups og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_28_AUG[POCET_JAZYKOV + 1] =
{
	"Nášho otca sv. Augustína, biskupa a učiteľa Cirkvi", // SK CSA, SK OPraem
	"Našeho otce sv. Augustina, biskupa a učitele církve", // CZ OPraem
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_29[POCET_JAZYKOV + 1] =
{
	"Mučenícka smrť sv. Jána Krstiteľa",
	"Umučení svatého Jana Křtitele",
	"",
	"In Passione s. Ioannis Baptistæ",
	"",
	"Umučení svatého Jana Křtitele",
	"Keresztelő Szent János vértanúsága",
	"ru_text",
	"Мучаніцтва Яна Хрысціцеля",
	"Píslarvætti hl. Jóhannesar skírara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_30_SK[POCET_JAZYKOV + 1] =
{
	"Výročie posviacky katedrálneho chrámu " HTML_LINE_BREAK "sv. Jána Krstiteľa",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_30_CM[POCET_JAZYKOV + 1] =
{
	"Bl. Michala Ghebreho, kňaza a mučeníka",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_30_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Bl. Bronislavy, panny našej rehole",
	"Bl. Bronislavy, panny z premonstrátského řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_AUG_31_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Esztergom-Budapest: A prímási bazilika-" HTML_LINE_BREAK "főszékesegyház felszentelése",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// --------------- 09 september ---------------

const char* text_SEP_01_OFM[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Szent Beatrix de Silva, szűz",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_01_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Terézie Margity Redi " HTML_LINE_BREAK "od Najsvätejšieho Srdca Ježišovho, panny",
	"Sv. Terezie Markéty od Srdce Ježíšova" HTML_LINE_BREAK " (Anny Marie Redi), panny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Margrétar af hinu alhelga hjarta Jesú, meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_02_CM[POCET_JAZYKOV + 1] =
{
	"Bl. Ľudovíta Jozefa Françoisa, Jána Henricha Gruyera " HTML_LINE_BREAK "a Petra Renáta Rogueho, kňazov a mučeníkov",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_02_SJ[POCET_JAZYKOV + 1] =
{
	"",
	"Bl. Jakuba Bonnauda, kněze, a druhů; " HTML_LINE_BREAK "bl. Josefa Imberta a Jana Mikuláše Cordiera, kněží; " HTML_LINE_BREAK "bl. Tomáše Sitjara, kněze, a druhů; " HTML_LINE_BREAK "bl. Jana Faustiho, kněze, a druhů, mučedníků",
	"",
	"",
	"",
	"",
	"Boldog Bonnaud Jakab, áldozópap és társai; " HTML_LINE_BREAK "Boldog Imbert József és Cordier Miklós, áldozópapok; " HTML_LINE_BREAK "Boldog Sitjar Tamás, áldozópap és társai vértanúk",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_02_1_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Gualu z Bergama, biskupa",
	"",
	"",
	"",
	"",
	"Bl. Gualy z Bergama, biskupa",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_02_2_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Ingridy zo Skänninge, rehoľníčky",
	"",
	"",
	"",
	"",
	"Bl. Ingrid ze Skänninge, vdovy, mnišky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_02_1_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Jána Františka Burtého, kňaza a mučeníka, " HTML_LINE_BREAK "člena 1. rádu",
	"Bl. Jana Františka Burtè, kněze a mučedníka",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_02_2_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Apolinára z Posatu, kňaza, člena 1. rádu, " HTML_LINE_BREAK "a spoločníkov, mučeníkov",
	"Bl. Apolináře z Posatu, kněze, a druhů, mučedníků",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_03[POCET_JAZYKOV + 1] =
{
	"Sv. Gregora Veľkého, pápeža a učiteľa Cirkvi",
	"Sv. Řehoře Velikého, papeže a učitele církve",
	"",
	"S. Gregorii Magni, papæ et Ecclesiæ doctoris",
	"",
	"Sv. Řehoře Velikého, papeže a učitele církve",
	"Nagy Szent Gergely pápa és egyháztanító",
	"ru_text",
	"Св. Грыгорыя Вялікага, папы і доктара Касцёла",
	"Hl. Gregoríusar mikla, páfa og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_04_BY[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Бл. Марыі Стэллы і паплечніц, паннаў і мучаніц",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_04_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Kataríny z Racconigi, panny",
	"",
	"",
	"",
	"",
	"Bl. Kateřiny z Racconigi, panny, terciářky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_04_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Ruženy z Viterba, panny, členky 3. rádu",
	"Sv. Růženy z Viterba, panny",
	"",
	"",
	"",
	"",
	"Viterbói Szent Róza, szűz a III. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_04_OSU[POCET_JAZYKOV + 1] =
{
	"Panny Márie, Matky potechy",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_05[POCET_JAZYKOV + 1] =
{
	"Sv. Terézie z Kalkaty (Matky Terezy), panny a rehoľnice",
	"Sv. Terezie z Kalkaty (Matky Terezy), panny, řeholnice",
	"St. Teresa of Calcutta, virgin, nun",
	"S. Teresiæ de Calcutta, virginis",
	"",
	"Sv. Terezie z Kalkaty (Matky Terezy), panny a řeholnice",
	"Kalkuttai Szent Teréz szűz", // Mother Theresa of Calcutta - removed from the hungarian roman general calendar (at the Vatican request)
	"",
	"",
	"Hl. Móðir Teresa, stofnandi reglunnar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_05_1_OP[POCET_JAZYKOV + 1] =
{
	"Spomienka na zosnulých príbuzných a dobrodincov našej rehole",
	"Vzpomínka zemřelých příbuzných a dobrodinců řádu",
	"",
	"",
	"",
	"Vzpomínka zemřelých příbuzných a dobrodinců řádu",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_06_SK[POCET_JAZYKOV + 1] =
{
	"Výročie posviacky katedrálneho chrámu " HTML_LINE_BREAK "sv. Alžbety",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_06_1_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Bertranda z Garrigue, kňaza",
	"",
	"",
	"",
	"",
	"Bl. Bertranda z Garrigua, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_06_2_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Michala Czartoryského, kňaza, " HTML_LINE_BREAK "a bl. Júlie Rodzińskej, panny a rehoľníčky, " HTML_LINE_BREAK "mučeníkov",
	"",
	"",
	"",
	"",
	"Bl. Michaela Czartoryského, kněze, " HTML_LINE_BREAK "a Julie Rodzinské, panny, řeholnice, " HTML_LINE_BREAK "polských mučedníků",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_07[POCET_JAZYKOV + 1] =
{
	"Sv. Marka Križina, Melichara Grodzieckeho " HTML_LINE_BREAK "a Štefana Pongrácza, kňazov a mučeníkov",
	"Sv. Melichara Grodeckého, kněze a mučedníka",
	"",
	"",
	"",
	"Sv. Melichara Grodeckého, kněze a mučedníka",
	"Szent Márk, István és Menyhért áldozópapok, kassai vértanúk",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_07_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Jána Jozefa Latasta, kňaza",
	"",
	"",
	"",
	"",
	"Bl. Jana Josefa Latasta, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_07_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. košických mučeníkov: Štefana Pongrácza a Melichara Grodzieckeho, kňazov Spoločnosti Ježišovej; " HTML_LINE_BREAK "Marka Križina, ostrihomského kanonika, patrónov Slovenskej provincie Spoločnosti Ježišovej",
	"Sv. Štěpána Pongrácze, Melichara Grodeckého, kněží, " HTML_LINE_BREAK "a Marka Križína, kanovníka ostřihomského, mučedníků",
	"",
	"",
	"",
	"Sv. Štěpána Pongrácze, Melichara Grodeckého, kněží, " HTML_LINE_BREAK "a Marka Križína, kanovníka ostřihomského, mučedníků",
	"Pongrácz Szent István, Grodzieski Szent Menyhért áldozópapok és Kőrösi Márk esztergomi kanonok, " HTML_LINE_BREAK "a Magyarországi Rendtartomány védőszentjei, vértanúk",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_08[POCET_JAZYKOV + 1] =
{
	"Narodenie prebl. Panny Márie", // podľa Direktória 2012, str. 191, tam nie je 'prebl.'; 3RM už opäť má PREBLAHOSLAVENEJ
	"Narození Panny Marie",
	"",
	"In Nativitate Beatæ Mariæ Virginis",
	"",
	"Narození Panny Marie",
	"Szűz Mária születése (Kisboldogasszony)",
	"ru_text",
	"Нараджэнне Найсв. Панны Марыі",
	"Fæðing Sællar Maríu Meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_08_BY[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Найсв. Панны Марыі Браслаўскай",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_09[POCET_JAZYKOV + 1] =
{
	"Sv. Petra Clavera, kňaza",
	"Sv. Petra Klavera, kněze",
	"",
	"S. Petri Claver, presbyteri",
	"",
	"Sv. Petra Klavera, kněze",
	"Claver Szent Péter áldozópap",
	"ru_text",
	"Св. Пятра Клявэра, прэзбітэра",
	"Hl. Péturs Claver, prests", // Klaver?
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_09_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Petra Clavera, kňaza",
	"Sv. Petra Klavera, kněze	",
	"",
	"",
	"",
	"Sv. Petra Klavera, kněze	",
	"Claver Szent Péter áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_10_SJ[POCET_JAZYKOV + 1] =
{
	"Bl. Františka Gárateho, rehoľníka",
	"Bl. Františka Gárate, řeholníka",
	"",
	"",
	"",
	"Bl. Františka Gárate, řeholníka",
	"Boldog Gárate Ferenc, szerzetes",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_10_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Bl. Karla Spinoly, kněze a mučedníka",
	"",
	"",
	"",
	"Bl. Karla Spinoly, kněze a mučedníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_11_CSSR[POCET_JAZYKOV + 1] =
{
	"Bl. Márie Celesty Crostarosa, rehoľníčky a zakladateľky",
	"Bl. Marie Celesty Crostarosa, řeholnice a zakladatelky",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_11_CM[POCET_JAZYKOV + 1] =
{
	"Bl. Jána Gabriela Perboyreho, kňaza a mučeníka",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_11_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Márie od Ježiša, panny",
	"Bl. Marie od Ježíše (Lopez Rivas), panny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Bl. Maríu af Jesú, meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_12[POCET_JAZYKOV + 1] =
{
	"Najsv. mena Mária", // podľa Direktória 2012, str. 192; pôvodne bolo: 'Mena prebl. Panny Márie'; 3RM: NAJSVÄTEJŠIEHO MENA MÁRIA
	"Jména Panny Marie",
	"",
	"Ss. Nominis B. Mariæ Virginis",
	"",
	"Jména Panny Marie",
	"Szűz Mária Szent Neve",
	"ru_text",
	"Найсвяцейшага Імя Марыі",
	"Alheilagt nafn Maríu meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_12_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Najsv. mena Panny Márie",
	"Nejsvětějšího jména Panny Marie",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_13[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Zlatoústeho, biskupa a učiteľa Cirkvi",
	"Sv. Jana Zlatoústého, biskupa a učitele církve",
	"",
	"S. Ioannis Chrysostomi, episcopi et Ecclesiæ doctoris",
	"",
	"Sv. Jana Zlatoústého, biskupa a učitele církve",
	"Aranyszájú (Krizosztomosz) Szent János püspök és egyháztanító",
	"ru_text",
	"Св. Яна Златавуснага (Хрызастома), " HTML_LINE_BREAK "біскупа і доктара Касцёла",
	"Hl. Jóhannesar Krýsostómusar, biskups og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_13_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Győr: A székesegyház felszentelése",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_14[POCET_JAZYKOV + 1] =
{
	"Povýšenie Svätého kríža",
	"Povýšení svatého kříže",
	"",
	"In Exaltatione Sanctæ Crucis",
	"",
	"Povýšení svatého Kříže",
	"A Szent Kereszt felmagasztalása",
	"ru_text",
	"Узвышэнне святога Крыжа",
	"Upphafningar hins heilaga kross",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_15[POCET_JAZYKOV + 1] =
{
	"Sedembolestnej Panny Márie, patrónky Slovenska",
	"Panny Marie Bolestné",
	"",
	"Beatæ Mariæ Virginis Perdolentis",
	"",
	"Panny Marie Bolestné",
	"A Fájdalmas Szűzanya",
	"ru_text",
	"Найсв. Панны Марыі Балеснай",
	"Harmkvæli Maríu meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_16_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Sv. Ludmily, mučednice",
	"",
	"",
	"",
	"Sv. Ludmily, mučednice",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_16[POCET_JAZYKOV + 1] =
{
	"Sv. Kornela, pápeža, a Cypriána, biskupa, mučeníkov", // kedysi: Kornélia, opravené podľa 3RM
	"Sv. Kornélia, papeže, a Cypriána, biskupa, mučedníků",
	"",
	"Ss. Cornelii, papæ, et Cypriani, episcopi, martyrum",
	"",
	"Sv. Kornélia, papeže, a Cypriána, biskupa, mučedníků",
	"Szent Kornél pápa és Szent Ciprián püspök vértanúk",
	"ru_text",
	"Св. Карнэлія, папы, і Кіпрыяна, біскупа, мучанікаў",
	"Hl. Kornelíusar páfa og hl. Kypríanusar, biskups, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_17[POCET_JAZYKOV + 1] =
{
	"Sv. Róberta Bellarmína, biskupa a učiteľa Cirkvi",
	"Sv. Roberta Bellarmina, biskupa a učitele církve",
	"",
	"S. Roberti Bellarmino, episcopi et Ecclesiæ doctoris",
	"",
	"Sv. Roberta Bellarmina, biskupa a učitele církve",
	"Bellarmin Szent Róbert püspök és egyháztanító",
	"ru_text",
	"Св. Робэрта Бэлярміна, біскупа і доктара Касцёла",
	"Hl. Róberts Bellarmínó, biskups og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_17_2[POCET_JAZYKOV + 1] =
{
	"Sv. Hildegardy z Bingenu, panny a učiteľky Cirkvi",
	"Sv. Hildegardy z Bingenu, panny a učitelky církve",
	"",
	"S. Hildegardis Bingensis, virginis et Ecclesiæ doctoris",
	"",
	"Sv. Hildegardy z Bingenu, panny a učitelky církve",
	"Bingeni Szent Hildegárd szűz és egyháztanító",
	"ru_text",
	"",
	"Hl. Hildegarda frá Bingen, meyjar og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_17_IS[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Lamberts, biskups og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_17_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Róberta Bellarmína, biskupa a učiteľa Cirkvi", // dlhé í podľa 3RM
	"Sv. Roberta Bellarmina, biskupa a učitele církve",
	"",
	"",
	"",
	"Sv. Roberta Bellarmina, biskupa a učitele církve",
	"Bellarmino Szent Róbert, püspök és egyháztanító",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_17_OFM[POCET_JAZYKOV + 1] =
{
	"Stigmatizácia nášho otca sv. Františka",
	"Vtisknutí ran (stigmat) našemu sv. Otci Františkovi",
	"",
	"",
	"",
	"",
	"Szent Ferenc atyánk stigmatizációja",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_17_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Alberta Jeruzalemského, " HTML_LINE_BREAK "biskupa a zákonodarcu nášho rádu",
	"Sv. Alberta Jeruzalémského, biskupa",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Alberts frá Jerúsalem, biskups",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_18_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Jozefa Kupertínskeho, kňaza, člena 1. rádu",
	"Sv. Josefa Kupertinského, kněze",
	"",
	"",
	"",
	"",
	"Copertinói Szent József, pap az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_18_OP[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Macíasa, rehoľníka",
	"",
	"",
	"",
	"",
	"Sv. Jana Maciase, řeholníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_18_OPRAEM[POCET_JAZYKOV + 1] =
{
	"",
	"Výročí posvěcení kostela",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_19[POCET_JAZYKOV + 1] =
{
	"Sv. Januára, biskupa a mučeníka",
	"Sv. Januária, biskupa a mučedníka",
	"",
	"S. Ianuarii, episcopi et martyris",
	"",
	"Sv. Januária, biskupa a mučedníka",
	"Szent Januáriusz püspök és vértanú",
	"ru_text",
	"Св. Януарыя, біскупа і мучаніка",
	"Hl. Janúaríusar, biskups og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_19_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Františka Máriu z Camporossa, " HTML_LINE_BREAK "rehoľníka, člena 1. rádu",
	"Sv. Františka Marie z Camporossa, řeholníka",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_19_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Pia Alberta del Corona, biskupa",
	"",
	"",
	"",
	"",
	"Bl. Pia Alberta del Corona, biskupa",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_19_SCHP[POCET_JAZYKOV + 1] =
{
	"sk_text",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_20[POCET_JAZYKOV + 1] =
{
	"Sv. Andreja Kima Taegona, kňaza, " HTML_LINE_BREAK "Pavla Chonga Hasanga a spoločníkov, mučeníkov",
	"Sv. Ondřeje Kim Tae-g&#335;na, kněze, " HTML_LINE_BREAK "Pavla Ch&#335;ng Ha-sanga a druhů, mučedníků",
	"",
	"Ss. Andreæ Kim Taegǒn, presbyteri, " HTML_LINE_BREAK "et Pauli Chǒng Hasang, et sociorum, martyrum",
	"",
	"Sv. Ondřeje Kim Tae-g&#335;na, kněze, " HTML_LINE_BREAK "Pavla Ch&#335;ng Ha-sanga a druhů, mučedníků",
	"Kim Taegon Szent András áldozópap, " HTML_LINE_BREAK "Csong Haszang Szent Pál és társaik, koreai vértanúk",
	"ru_text",
	"Св. Андрэя Кім Таэгона, прэзбітэра, " HTML_LINE_BREAK "і Паўла Чон Хасана, і паплечнікаў, мучанікаў",
	"Hl. Andrésar Kim Taegon, prests " HTML_LINE_BREAK "og hl. Páls Chǒng Ha-sang og félaga, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_20_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Výročí posvěcení katedrály sv. Štěpána",
	"",
	"",
	"",
	"Výročí posvěcení katedrály sv. Štěpána",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_20_1_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Františka de Posadas, kňaza",
	"",
	"",
	"",
	"",
	"Bl. Františka de Posadas, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_20_2_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Marka z Modeny, kňaza",
	"",
	"",
	"",
	"",
	"Bl. Marka z Modeny, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_21[POCET_JAZYKOV + 1] =
{
	"Sv. Matúša, apoštola a evanjelistu",
	"Sv. Matouše, apoštola a evangelisty",
	"",
	"S. Matthæi, apostoli et evangelistæ",
	"",
	"Sv. Matouše, apoštola a evangelisty",
	"Szent Máté apostol és evangélista",
	"ru_text",
	"Св. Мацвея, апостала і евангеліста",
	"Hl. Matteusar, postula og guðspjallamanns",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_22_SK[POCET_JAZYKOV + 1] =
{
	"Sv. Emeráma, biskupa a mučeníka",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_22_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Ignáca zo Santhie, kňaza, člena 1. rádu",
	"Sv. Ignáce ze Santhi&#224;, kněze", // &agrave;
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_22_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Jozefa Calasanza Marquésa " HTML_LINE_BREAK "a Enrica Sáiza Aparicia, kňazov, " HTML_LINE_BREAK "a 93 spoločníkov, mučeníkov",
	"Bl. Josefa Calasanze Marquéze " HTML_LINE_BREAK "a Enrika Sáize Aparicia, kněží a druhů, mučedníků",
	"",
	"",
	"",
	"",
	"Boldog Calasanz Marqués József " HTML_LINE_BREAK "és Sáiz Aparicio Henrik áldozópapok " HTML_LINE_BREAK "és kilencvenhárom társa vértanúk",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_22_SCHP[POCET_JAZYKOV + 1] =
{
	"sk_text",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_23[POCET_JAZYKOV + 1] =
{
	"Sv. Pia z Pietrelčiny, kňaza",
	"Sv. Pia z Pietrelciny, kněze",
	"",
	"S. Pii de Pietrelcina, presbyteri",
	"",
	"Sv. Pia z Pietrelciny, kněze",
	"Pietrelcinai Szent Pio áldozópap",
	"ru_text",
	"Св. Піо з П'етрэльчыны, прэзбітэра",
	"Hl. Pio de Pietrelcina, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_23_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Pia z Pietrelciny, kňaza, člena 1. rádu",
	"Sv. Pia z Pietrelciny (Forgione), kněze",
	"",
	"",
	"",
	"Sv. Pia z Pietrelciny, kněze",
	"Pietrelcinai Szent Pió szerzetes és áldozópap az I. rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_24_SK[POCET_JAZYKOV + 1] =
{
	"Výročie posviacky katedrálneho chrámu " HTML_LINE_BREAK "sv. Františka Xaverského",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_24_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Dalmáca Monera, kňaza",
	"",
	"",
	"",
	"",
	"Bl. Dalmáce Monera, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_24_OFM[POCET_JAZYKOV + 1] =
{
	"",
	"Sv. Pacifika ze San Severina, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_24_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Szent Gellért püspök és vértanú",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_25_OFM[POCET_JAZYKOV + 1] =
{
	"",
	"Bl. Inocence z Berza, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_26[POCET_JAZYKOV + 1] =
{
	"Sv. Kozmu a Damiána, mučeníkov",
	"Sv. Kosmy a Damiána, mučedníků",
	"",
	"Ss. Cosmæ et Damiani, martyrum",
	"",
	"Sv. Kosmy a Damiána, mučedníků",
	"Szent Kozma és Damján vértanúk",
	"ru_text",
	"Св. Космы і Дам'яна, мучанікаў",
	"Hl. Kosmasar og Damíanusar, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_26_CSSR[POCET_JAZYKOV + 1] =
{
	"Bl. Gašpara Stanggassingera, kňaza",
	"Bl. Kašpara Stanggassingera, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_26_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Aurélia z Vinalesy, kňaza, a spoločníkov, " HTML_LINE_BREAK "mučeníkov, členov 1. rádu",
	"Bl. Aurelia z Vinalesy (Ample-Alcaide), kněze, a druhů, mučedníků",
	"",
	"",
	"",
	"",
	"Sabrani Szent Elzeár és Boldog Delphina, házastársak a III. Rendből", // HU: different saints!
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_27[POCET_JAZYKOV + 1] =
{
	"Sv. Vincenta de Paul, kňaza",
	"Sv. Vincence z Paula, kněze",
	"",
	"S. Vincentii de Paul, presbyteri",
	"",
	"Sv. Vincence z Paula, kněze",
	"Páli Szent Vince áldozópap",
	"ru_text",
	"Св. Вінцэнта дэ Поля, прэзбітэра",
	"Hl. Vinsents af Páli, prests og reglustofnanda",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_27_CM[POCET_JAZYKOV + 1] =
{
	"Sv. Vincenta de Paul, kňaza, " HTML_LINE_BREAK "zakladateľa Misijnej spoločnosti " HTML_LINE_BREAK "a spoločnosti Dcér kresťanskej lásky",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_28[POCET_JAZYKOV + 1] =
{
	"Sv. Václava, mučeníka",
	"Sv. Václava, mučedníka, hlavního patrona českého národa",
	"",
	"S. Venceslai, martyris",
	"",
	"Sv. Václava, mučedníka, hlavního patrona českého národa, " HTML_LINE_BREAK "hlavního patrona provincie",
	"Szent Vencel vértanú",
	"ru_text",
	"Св. Вацлава, мучаніка",
	"Hl. Venceslas, píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_28_2[POCET_JAZYKOV + 1] =
{
	"Sv. Vavrinca Ruiza a spoločníkov, mučeníkov",
	"",
	"",
	"S. Laurentii Ruiz et sociorum, martyrum",
	"",
	"",
	"Ruiz Szent Lőrinc és társai, Fülöp-szigeteki vértanúk",
	"ru_text",
	"Св. Лаўрэнція Руіса і паплечнікаў, мучанікаў",
	"Hl. Laurentius Ruiz og félaga, píslarvotta", // Lárentíus?
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_28_OP[POCET_JAZYKOV + 1] =
{
	"Sv. Dominika Ibanéza z Erquicia, kňaza, " HTML_LINE_BREAK "Vavrinca Ruiza z Manily, laika, " HTML_LINE_BREAK "bl. Alfonza Navarettu, kňaza, a spoločníkov, mučeníkov",
	"",
	"",
	"",
	"",
	"Sv. Dominika Ibaněze z Erquicia, kněze, " HTML_LINE_BREAK "Vavřince Ruize, otce rodiny, " HTML_LINE_BREAK "bl. Alfonse Navaretty, kněze, a druhů, " HTML_LINE_BREAK "japonských mučedníků", // CZOP kvôli sv. Václavovi slávia 26SEP
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_28_2_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Vavrinca z Ripafratty, kňaza",
	"",
	"",
	"",
	"",
	"Bl. Vavřince z Ripafratty, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_28_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Inocenta z Berza, kňaza, člena 1. rádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_29[POCET_JAZYKOV + 1] =
{
	"Sv. Michala, Gabriela a Rafaela, archanjelov",
	"Sv. Michaela, Gabriela a Rafaela, archandělů",
	"",
	"Ss. Michaelis, Gabrielis et Raphaelis, archangelorum",
	"",
	"Sv. Michaela, Gabriela a Rafaela, archandělů",
	"Szent Mihály, Szent Gábor és Szent Rafael főangyalok",
	"ru_text",
	"Св. Міхала Арханёла " HTML_LINE_BREAK "(апекуна Мінска-Магілёўскай правінцыі касцёла), " HTML_LINE_BREAK "св. Габрыэля і Рафала, арханёлаў",
	"Hl. Mikaels, Gabríels og Rafaels, erkienglar", // höfuðengla
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_SEP_30[POCET_JAZYKOV + 1] =
{
	"Sv. Hieronyma, kňaza a učiteľa Cirkvi",
	"Sv. Jeronýma, kněze a učitele církve",
	"",
	"S. Hieronymi, presbyteri et Ecclesiæ doctoris",
	"",
	"Sv. Jeronýma, kněze a učitele církve",
	"Szent Jeromos áldozópap és egyháztanító",
	"ru_text",
	"Св. Гераніма, прэзбітэра і доктара Касцёла",
	"Hl. Híerónýmusar, prests og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// --------------- 10 október | october ---------------

const char* text_OKT_01[POCET_JAZYKOV + 1] =
{
	"Sv. Terézie od Dieťaťa Ježiša (z Lisieux), " HTML_LINE_BREAK "panny a učiteľky Cirkvi", // kedysi: "Sv. Terézie z Lisieux, panny a učiteľky Cirkvi"
	"Sv. Terezie od Dítěte Ježíše, panny a učitelky církve",
	"",
	"S. Teresiæ a Iesu Infante, virginis et Ecclesiæ doctoris",
	"",
	"Sv. Terezie od Dítěte Ježíše, panny a učitelky církve",
	"A Gyermek Jézusról nevezett (Lisieux-i) Szent Teréz szűz és egyháztanító",
	"ru_text",
	"Св. Тэрэзы ад Дзіцятка Езус, панны і доктара Касцёла",
	"Hl. Teresu af Jesúbarninu, meyjar og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_01_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Terézie od Dieťaťa Ježiša, " HTML_LINE_BREAK "panny a učiteľky Cirkvi",
	"Sv. Terezie od Dítěte Ježíše a svaté Tváře, " HTML_LINE_BREAK "panny a učitelky církve",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_02[POCET_JAZYKOV + 1] =
{
	"Svätých anjelov strážcov",
	"Svatých andělů strážných",
	"",
	"Ss. Angelorum custodum",
	"",
	"Svatých andělů strážných",
	"Szent Őrzőangyalok",
	"ru_text",
	"Св. Анёлаў Ахоўнікаў",
	"Hl. verndarenglar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_03_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Františka de Borja, kňaza",
	"Sv. Františka Borgiáše, kněze",
	"",
	"",
	"",
	"Sv. Františka Borgiáše, kněze",
	"De Borja Szent Ferenc, áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_03_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Dominika Spadaforu, kňaza",
	"",
	"",
	"",
	"",
	"Bl. Dominika Spadafory, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_04[POCET_JAZYKOV + 1] =
{
	"Sv. Františka Assiského",
	"Sv. Františka z Assisi",
	"",
	"S. Francisci Assisiensis",
	"",
	"Sv. Františka z Assisi, jáhna",
	"Assisi Szent Ferenc",
	"ru_text",
	"Св. Францішка Асізскага",
	"Hl. Frans frá Assisi, reglustofnanda",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_04_OFM[POCET_JAZYKOV + 1] =
{
	"Nášho otca sv. Františka, diakona, " HTML_LINE_BREAK "zakladateľa troch rádov",
	"Sv. Františka, jáhna, zakladatele tří řádů",
	"",
	"",
	"",
	"",
	"Szent Ferenc atyánk, diakónus, a három rend alapítója",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_04_OP[POCET_JAZYKOV + 1] =
{
	"Sv. Františka Assiského, diakona",
	"Sv. otce Františka z Assisi, jáhna",
	"",
	"",
	"",
	"Sv. otce Františka z Assisi, jáhna",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_05_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Alberta Marvelliho, mladíka",
	"Bl. Alberta Marvelliho, oratoriána",
	"",
	"",
	"",
	"",
	"Boldog Maravelli Albert laikus",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_05_CSSR[POCET_JAZYKOV + 1] =
{
	"Bl. Františka Xaverského Seelosa, kňaza",
	"Bl. Františka Xavera Seelose, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_05_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Veszprém: A bazilika-főszékesegyház felszentelése",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_05[POCET_JAZYKOV + 1] =
{
	"Sv. Faustíny Kowalskej, panny",
	"Sv. Faustiny Kowalské, panny",
	"",
	"S. Faustinæ Kowalska, virginis",
	"",
	"Sv. Faustiny Kowalské, panny",
	"Szent Faustina Kowalska szűz",
	"",
	"",
	"Hl. Fástínu Kowalska, meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_05_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Rajmunda z Kapuy, kňaza",
	"",
	"",
	"",
	"",
	"Bl. Rajmunda z Kapuy, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_05_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Anny Schäffer",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_06[POCET_JAZYKOV + 1] =
{
	"Sv. Bruna, kňaza",
	"Sv. Bruna, kněze",
	"",
	"S. Brunonis, presbyteri",
	"",
	"Sv. Bruna, kněze",
	"Szent Brúnó áldozópap",
	"ru_text",
	"Св. Бруна, прэзбітэра",
	"Hl. Brúnó, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_06_HU_OFM[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Az Úr Jézus Öt Sebéről nevezett Szent Mária Franciska, szűz A III. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_06_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Bartolomeja Longu",
	"",
	"",
	"",
	"",
	"Bl. Bartoloměje Longa, terciáře",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_07[POCET_JAZYKOV + 1] =
{
	"Ružencovej Panny Márie", // podľa Direktória 2012, str. 206, nie je 'prebl.', ani 3RM nemá
	"Panny Marie Růžencové",
	"",
	"Beatæ Mariæ Virginis a Rosario",
	"",
	"Panny Marie Růžencové",
	"A Boldogságos Szűz Mária, a szentolvasó Királynéja", // HU: old name: "Rózsafüzér Királynője"
	"ru_text",
	"Найсв. Панны Марыі Ружанцовай",
	"Rósakransmessa, hl. Maríu meyjar", // ToDo
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_08_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Szűz Mária, Magyarok Nagyasszonya, " HTML_LINE_BREAK "Magyarország főpátronája",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_08_1_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Ambróza Sansedoniho, kňaza",
	"",
	"",
	"",
	"",
	"Bl. Ambrože Sansedoniho, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_08_2_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Matúša Carreriho, kňaza",
	"",
	"",
	"",
	"",
	"Bl. Matěje Carreriho, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_09_1[POCET_JAZYKOV + 1] =
{
	"Sv. Dionýza, biskupa, a spoločníkov, mučeníkov",
	"Sv. Dionýsia, biskupa, a druhů, mučedníků",
	"",
	"Ss. Dionysii, episcopi, et sociorum martyrum",
	"",
	"Sv. Dionýsia, biskupa, a druhů, mučedníků",
	"Szent Dénes püspök és társai vértanúk",
	"ru_text",
	"Св. Дыянісія, біскупа, і паплечнікаў, мучанікаў",
	"Hl. Díónysíusar og félaga, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_09_2[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Leonardiho, kňaza",
	"Sv. Jana Leonardiho, kněze",
	"",
	"S. Ioannis Leonardi, presbyteri",
	"",
	"Sv. Jana Leonardiho, kněze",
	"Leonardi Szent János áldozópap",
	"ru_text",
	"Св. Яна Леанардзі, прэзбітэра",
	"Hl. Jóhannesar Leonardi, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_09_OP[POCET_JAZYKOV + 1] =
{
	"Sv. Ľudovíta Bertrána, kňaza",
	"",
	"",
	"",
	"",
	"Sv. Ludvíka Bertrána, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_10_SK[POCET_JAZYKOV + 1] =
{
	"Výročie posviacky katedrálneho chrámu " HTML_LINE_BREAK "Najsvätejšej Trojice",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_10_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Sv. Gereona a spoločníkov, mučeníkov",
	"Sv. Gereona a druhů, mučedníků",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_10_HU_OFM[POCET_JAZYKOV + 1] =
{
	"",
	"Sv. Daniela a druhů, mučedníků mauretánských",
	"",
	"",
	"",
	"",
	"Szent Dániel és vértanú társai az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_11[POCET_JAZYKOV + 1] =
{
	"Sv. Jána XXIII., pápeža",
	"Sv. Jana XXIII., papeže",
	"",
	"S. Joannis XXIII, papæ",
	"",
	"Sv. Jana XXIII., papeže",
	"Szent XXIII. János pápa",
	"ru_text",
	"Св. Яна XXIII, папы",
	"Hl. Jóhannesar XXIII., páfa",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_11_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Jána XXIII., pápeža, člena 3. rádu",
	"Sv. Jana XXIII., papeže, člena 3. řádu",
	"",
	"",
	"",
	"",
	"Szent XXIII. János, pápa a III. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_11_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Jakuba z Ulmu, rehoľníka",
	"Bl. Jakuba z Ulmu, řeholníka",
	"",
	"",
	"",
	"Bl. Jakuba z Ulmu, řeholníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_12_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Sv. Radima, biskupa",
	"",
	"",
	"",
	"Sv. Radima, biskupa",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_12_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Serafína z Montegranara, rehoľníka, člena 1. rádu",
	"Sv. Serafína z Montegranara, řeholníka",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_12_SJ[POCET_JAZYKOV + 1] =
{
	"Bl. Jána Beyzyma, kňaza",
	"Bl. Jana Beyzyma, kněze",
	"",
	"",
	"",
	"Bl. Jana Beyzyma, kněze",
	"Boldog Beyzym János, áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_13_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Honoráta Kożmińského, kňaza, člena 1. rádu",
	"Bl. Honoráta Kožmiňského, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_13_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Magdalény Panatieriovej, panny",
	"Bl. Magdalény Panatieriové, panny, terciářky",
	"",
	"",
	"",
	"Bl. Magdalény Panatieriové, panny, terciářky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_13_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Alexandry Márie da Costovej, panny", // podľa CZ SDB doplnené: "panny"
	"Bl. Alessadriny Marie da Costa, panny",
	"",
	"",
	"",
	"",
	"Boldog Da Costa Alexandrina Mária szűz",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_13_OPRAEM[POCET_JAZYKOV + 1] =
{
	"",
	"Bl. Petra Adriána Toulorge, kněze a mučedníka " HTML_LINE_BREAK "z premonstrátského řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_14[POCET_JAZYKOV + 1] =
{
	"Sv. Kalixta I., pápeža a mučeníka",
	"Sv. Kalista I., papeže a mučedníka",
	"",
	"S. Callisti I, papæ et martyris",
	"",
	"Sv. Kalista I., papeže a mučedníka",
	"Szent I. Kallixtusz pápa és vértanú",
	"ru_text",
	"Св. Калікста I, папы і мучаніка",
	"Hl. Kalixtusar I., páfa og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_14_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Ogilvieho, kňaza a mučeníka",
	"Sv. Jana Ogilvie, kněze a mučedníka", // CZ: 10MAR
	"",
	"",
	"",
	"Sv. Jana Ogilvie, kněze a mučedníka",
	"Ogilvie Szent János áldozópap és vértanú",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_14_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Márie Poussepinovej, panny",
	"Bl. Marie Poussepinové, panny, terciářky",
	"",
	"",
	"",
	"Bl. Marie Poussepinové, panny, terciářky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_15[POCET_JAZYKOV + 1] =
{
	"Sv. Terézie od Ježiša (z Avily), " HTML_LINE_BREAK "panny a učiteľky Cirkvi", // 'z Avily' upravené podľa Direktória 2012, str. 209; "(Z AVILY)" podľa 3RM
	"Sv. Terezie od Ježíše, " HTML_LINE_BREAK "panny a učitelky církve",
	"",
	"S. Teresiæ a Iesu, virginis et Ecclesiæ doctoris",
	"",
	"Sv. Terezie od Ježíše, " HTML_LINE_BREAK "panny a učitelky církve",
	"A Jézusról nevezett (Avilai) Szent Teréz " HTML_LINE_BREAK "szűz és egyháztanító",
	"ru_text",
	"Св. Тэрэзы ад Езуса, " HTML_LINE_BREAK "панны і доктара Касцёла",
	"Hl. Teresu af Jesú, meyjar og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_15_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Terézie od Ježiša, " HTML_LINE_BREAK "panny a učiteľky Cirkvi, našej Matky",
	"Sv. Terezie od Ježíše, " HTML_LINE_BREAK "panny a učitelky církve",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Teresu af Jesú, meyjar og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_16_1[POCET_JAZYKOV + 1] =
{
	"Sv. Margity Márie Alacoque, panny",
	"Sv. Markéty Marie Alacoque, panny",
	"",
	"S. Margaritæ Mariæ Alacoque, virginis",
	"",
	"Sv. Markéty Marie Alacoque, panny",
	"Alacoque Szent Margit Mária szűz",
	"ru_text",
	"Св. Маргарыты Марыі Алякок, панны",
	"Hl. Margrétar Maríu Alacoque, meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_16_2[POCET_JAZYKOV + 1] =
{
	"Sv. Hedvigy, rehoľníčky",
	"Sv. Hedviky, řeholnice, hlavní patronky Slezska",
	"",
	"S. Hedvigis, religiosæ",
	"",
	"Sv. Hedviky, řeholnice, hlavní patronky Slezska",
	"Szent Hedvig szerzetesnő",
	"ru_text",
	"Св. Ядзвігі, законніцы",
	"Hl. Heiðveigar, reglusystur",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_16_3[POCET_JAZYKOV + 1] =
{
	"Sv. Gála, kňaza",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_16_CSSR[POCET_JAZYKOV + 1] =
{
	"Sv. Gerarda Majellu, rehoľníka",
	"Sv. Gerarda Majelly, řeholníka",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_16_SCHP[POCET_JAZYKOV + 1] =
{
	"sk_text",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_17[POCET_JAZYKOV + 1] =
{
	"Sv. Ignáca Antiochijského, biskupa a mučeníka",
	"Sv. Ignáce Antiochijského, biskupa a mučedníka",
	"",
	"S. Ignatii Antiocheni, episcopi et martyris",
	"",
	"Sv. Ignáce Antiochijského, biskupa a mučedníka",
	"Antiochiai Szent Ignác püspök és vértanú",
	"ru_text",
	"Св. Ігнацыя з Антыёхіі, біскупа і мучаніка",
	"Hl. Ignatíusar frá Antiokkíu, biskups og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_18[POCET_JAZYKOV + 1] =
{
	"Sv. Lukáša, evanjelistu",
	"Sv. Lukáše, evangelisty",
	"",
	"S. Lucæ, evangelistæ",
	"",
	"Sv. Lukáše, evangelisty",
	"Szent Lukács evangélista",
	"ru_text",
	"Св. Лукі, евангеліста",
	"Hl. Lúkasar, guðspjallamanns",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_19_1[POCET_JAZYKOV + 1] =
{
	"Sv. Jána de Brébeuf a Izáka Jogues, kňazov, " HTML_LINE_BREAK "a spoločníkov, mučeníkov", //  // 'sv. Izáka', podľa Direktória 2012, str. 210 nie je 'sv.'
	"Sv. Jana de Brébeuf a Izáka Joguese, kněží, " HTML_LINE_BREAK "a druhů, mučedníků",
	"",
	"Ss. Ioannis de Brebeuf et Isaac Jogues, presbyterorum, " HTML_LINE_BREAK "et sociorum, martyrum",
	"",
	"Sv. Jana de Brébeuf a Izáka Joguese, kněží, " HTML_LINE_BREAK "a druhů, mučedníků",
	"De Brébeuf Szent János és Jogues Szent Izsák áldozópap " HTML_LINE_BREAK "és társaik, észak-amerikai vértanúk",
	"ru_text",
	"Св. Жана дэ Брэбёфа і Ісаака Жога, прэзбітэраў, " HTML_LINE_BREAK "і паплечнікаў, мучанікаў",
	"Hl. Jóhannes de Brébeuf og félaga, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_19_2[POCET_JAZYKOV + 1] =
{
	"Sv. Pavla od Kríža, kňaza", // kedysi: "Sv. Pavla z Kríža, kňaza"
	"Sv. Pavla od Kříže, kněze",
	"",
	"S. Pauli a Cruce, presbyteri",
	"",
	"Sv. Pavla od Kříže, kněze",
	"Keresztes Szent Pál áldozópap",
	"ru_text",
	"Св. Паўла ад Крыжа, прэзбітэра",
	"Hl. Páls af krossi, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_19_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Jána de Brébeuf, Izáka Joguesa, kňazov, a spoločníkov, mučeníkov",
	"Sv. Jana de Brébeuf a Izáka Jogues, kněží, a druhů, mučedníků",
	"",
	"",
	"",
	"Sv. Jana de Brébeuf a Izáka Jogues, kněží, a druhů, mučedníků",
	"De Brebeuf Szent János, Jogues Izsák, áldozópapok és társaik vértanúk",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_19_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Agnesy od Ježiša Galandovej, panny",
	"",
	"",
	"",
	"",
	"Bl. Anežky od Ježíše Galandové, panny, mnišky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_19_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Petra z Alcantary, kňaza, člena 1. rádu",
	"Sv. Petra z Alkantary, kněze",
	"",
	"",
	"",
	"",
	"Alkantarai Szent Péter, pap az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_20_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Jakuba Strepu, biskupa, člena 1. rádu",
	"Bl. Jakuba Strepy, biskupa",
	"",
	"",
	"",
	"",
	"Boldog Contardo Ferrini, a III. Rendből", // HU: different saint!
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_20_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Bl. Jakuba Kerna, kňaza našej rehole",
	"Bl. Jakuba Kerna, kněze z premonstrátského řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_21_CZ_HU[POCET_JAZYKOV + 1] =
{
	"Bl. Karla Habsburského",
	"Bl. Karla Rakouského",
	"",
	"",
	"",
	"Bl. Karla Rakouského",
	"Boldog IV. Károly király",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_21_SJ[POCET_JAZYKOV + 1] =
{
	"Bl. Diega Alojza de san Vitores, kňaza a mučeníka", // SK SJ: 06OKT
	"Bl. Diega Luise de San Vitores, kněze, " HTML_LINE_BREAK "a sv. Petra Calungsoda, mučedníků",
	"",
	"",
	"",
	"Bl. Diega Luise de San Vitores, kněze, " HTML_LINE_BREAK "a sv. Petra Calungsoda, mučedníků",
	"Boldog de San Vitores Didák Alajos, áldozópap " HTML_LINE_BREAK "és Calungsod Péter, vértanúk",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_21_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Petra z Citt&#224; di Castello, kňaza", // &agrave;
	"",
	"",
	"",
	"",
	"Bl. Petra z Citt&#224; di Castello, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_21_OFMCAP[POCET_JAZYKOV + 1] =
{
	"Bl. Márie Laurencie Longo, rehoľníčky",
	"Bl. Marie Laurencie Longo, řeholnice a zakladatelky", // br. Petr, doplněno dle italské předlohy
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_21_OSU[POCET_JAZYKOV + 1] =
{
	"Sv. Uršule a spoločníčok, panien a mučeníc",
	"Sv. Voršily a jejich družek, mučednic",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_22_OP[POCET_JAZYKOV + 1] =
{
	"Výročie posviacky konventného kostola, " HTML_LINE_BREAK "ktorého deň posviacky nie je známy",
	"",
	"",
	"",
	"",
	"Výročí posvěcení klášterního kostela, " HTML_LINE_BREAK "jehož den dedikace není známý",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_22_HU_OFM[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Boldog Josephina, szűz és vértanú A II. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_22[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Pavla II., pápeža",
	"Sv. Jana Pavla II., papeže",
	"",
	"S. Ioannis Pauli II, papæ",
	"",
	"Sv. Jana Pavla II., papeže",
	"Szent II. János Pál pápa",
	"ru_text",
	"Св. Яна Паўла II, папы",
	"Hl. Jóhannesar Páls II., páfa",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_23[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Kapistránskeho, kňaza",
	"Sv. Jana Kapistránského, kněze",
	"",
	"S. Ioannis de Capestrano, presbyteri",
	"",
	"Sv. Jana Kapistránského, kněze",
	"Kapisztrán Szent János áldozópap",
	"ru_text",
	"Св. Яна Капістрана, прэзбітэра",
	"Hl. Jóhannesar frá Capistrano, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_23_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Kapistránskeho, kňaza, člena 1. rádu",
	"Sv. Jana Kapistránského, kněze", // z Capestrana
	"",
	"",
	"",
	"",
	"Kapisztrán Szent János, pap az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_23_OSU[POCET_JAZYKOV + 1] =
{
	"Bl. Márie Klotildy Angely a spoločníčok, " HTML_LINE_BREAK "panien a mučeníc",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_24[POCET_JAZYKOV + 1] =
{
	"Sv. Antona Máriu Clareta, biskupa",
	"Sv. Antonína Marie Klareta, biskupa",
	"",
	"S. Antonii Mariæ Claret, episcopi",
	"",
	"Sv. Antonína Marie Klareta, biskupa",
	"Claret Szent Antal Mária püspök",
	"ru_text",
	"Св. Антонія Марыі Клярэта, біскупа",
	"Hl. Antóníusar Maríu Claret, biskups",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_24_SDB[POCET_JAZYKOV + 1] =
{
	"Sv. Alojza Guanellu, kňaza",
	"Sv. Aloise Guanelly, kněze",
	"",
	"",
	"",
	"",
	"Guanalla Szent Alajos áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_24_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"A székesegyház felszentelése",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_25_SK[POCET_JAZYKOV + 1] =
{
	"Výročie posviacky katedrálneho chrámu " HTML_LINE_BREAK "sv. Martina z Tours",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_25[POCET_JAZYKOV + 1] =
{
	"Sv. Maura, biskupa",
	"",
	"",
	"",
	"",
	"",
	"Szent Mór püspök",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_25_CONS[POCET_JAZYKOV + 1] =
{
	"Výročie posviacky vlastného chrámu " HTML_LINE_BREAK "(keď sa nepozná dátum posviacky)", // SK SDB
	"Výročí posvěcení vlastního kostela", // CZ OFMCap.
	"",
	"",
	"",
	"",
	"A saját templom feleszentelése", // HU SDB
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_25_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Petra Geremiu, kňaza",
	"",
	"",
	"",
	"",
	"Bl. Petra Geremii, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_25_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Márie od Ježiša Masie Ferragutovej a spoločníc, " HTML_LINE_BREAK "panien a mučeníc, členiek 2. rádu",
	"Bl. Marie od Ježíše Masiáové a družek, panen a mučednic",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_26[POCET_JAZYKOV + 1] =
{
	"Výročie posviacky chrámov, " HTML_LINE_BREAK "ktorých deň posviacky nie je známy", // 'je neznámy' opravené podľa Direktória 2012, str. 214
	"Výročí posvěcení chrámu, " HTML_LINE_BREAK "jehož den dedikace není známý",
	"",
	"",
	"",
	"Výročí posvěcení chrámu, " HTML_LINE_BREAK "jehož den dedikace není známý",
	"A saját templom felszentelése " HTML_LINE_BREAK "(ha annak napja nem ismeretes)", // A felszentelt templomokban: A saját templom felszentelése; HU: old subtitle: "amennyiben annak napja nem ismeretes"
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_26_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Damiána z Finalborga, kňaza",
	"",
	"",
	"",
	"",
	"Bl. Damiána z Finalborga, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_26_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Sv. Gilberta, opáta našej rehole",
	"Sv. Gilberta, opata z premonstrátského řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_26_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Bonaventúru z Potenzy, kňaza, člena 1. rádu",
	"Bl. Bonaventury z Potenzy, kněze 1. řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_27_SK[POCET_JAZYKOV + 1] =
{
	"Výročie posviacky katedrálneho chrámu " HTML_LINE_BREAK "Nanebovzatia Panny Márie",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_27_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Bartolomeja z Vicenze, biskupa",
	"",
	"",
	"",
	"",
	"Bl. Bartoloměje z Vicenzy, biskupa",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_28[POCET_JAZYKOV + 1] =
{
	"Sv. Šimona a Júdu, apoštolov",
	"Sv. Šimona a Judy, apoštolů",
	"",
	"Ss. Simonis et Iudæ, apostolorum",
	"",
	"Sv. Šimona a Judy, apoštolů",
	"Szent Simon és Szent Júdás Tádé apostolok",
	"ru_text",
	"Св. Сымона і Юды, апосталаў",
	"Hl. Símonar og Júdasar (Taddeusar), postula",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_29_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Michala Ruu, kňaza",
	"Bl. Michala Ruy, kněze",
	"",
	"",
	"",
	"",
	"Boldog Rua Mihály áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_29_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Bl. Marie Restituty Kafkové, panny a mučednice",
	"",
	"",
	"",
	"Bl. Marie Restituty Kafkové, panny a mučednice",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_30_SJ[POCET_JAZYKOV + 1] =
{
	"Bl. Dominika Collinsa, mučeníka",
	"Bl. Dominika Collinse, řeholníka a mučedníka",
	"",
	"",
	"",
	"Bl. Dominika Collinse, řeholníka a mučedníka",
	"Boldog Collins Domonkos, szerzetes",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_30_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Márie Terézie od sv. Jozefa, panny",
	"Bl. Terezie Marie od sv. Josefa, panny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Bl. María Teresa, stofnandi reglunnar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_30_1_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Benvenuty Boianiovej, panny",
	"",
	"",
	"",
	"",
	"Bl. Benvenuty Boianiové, panny, terciářky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_30_2_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Terenca Alberta O’Brien, biskupa, " HTML_LINE_BREAK "a bl. Petra Higginsa, kňaza, mučeníkov",
	"",
	"",
	"",
	"",
	"Bl. Terence Alberta O’Briena, biskupa, " HTML_LINE_BREAK "a Petra Higginse, kněze, irských mučedníků",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_30_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Výročí posvěcení katedrály Svatého Ducha",
	"",
	"",
	"",
	"Výročí posvěcení katedrály Svatého Ducha",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_30_HU_OFM[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"A saját templom fölszentelesenek évfordulója",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_31_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Alfonza Rodrígueza, rehoľníka",
	"Sv. Alfonse Rodrígueze, řeholníka",
	"",
	"",
	"",
	"Sv. Alfonse Rodrígueze, řeholníka",
	"Rodríguez Szent Alfonz, szerzetes",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_31_OFMCAP[POCET_JAZYKOV + 1] =
{
	"Sv. Angela z Acri, kňaza, člena 1. rádu",
	"Sv. Anděla z Acri, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_31_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Sv. Wolfganga, biskupa",
	"",
	"",
	"",
	"Sv. Wolfganga, biskupa",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_OKT_31_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Boldog Romzsa Tódor püspök és vértanú",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// --------------- 11 november ---------------

const char* text_NOV_01[POCET_JAZYKOV + 1] =
{
	"Všetkých svätých",
	"Všech svatých",
	"",
	"Omnium sanctorum",
	"",
	"Všech svatých",
	"Mindenszentek",
	"ru_text",
	"Усіх Святых",
	"Allra heilagra",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_02[POCET_JAZYKOV + 1] =
{
	"Spomienka na všetkých zosnulých veriacich", // podľa Direktória 2012, str. 218: "Spomienka na všetkých verných zosnulých"; opravené podľa 3RM (2022)
	"Vzpomínka na všechny věrné zemřelé",
	"",
	"In Commemoratione omnium fidelium defunctorum",
	"",
	"Vzpomínka na všechny věrné zemřelé",
	"Halottak napja",
	"ru_text",
	"Успамін усіх памерлых вернікаў",
	"Minning allra framliðinna",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_03[POCET_JAZYKOV + 1] =
{
	"Sv. Martina de Porres, rehoľníka", // 'de Porres': podľa Direktória 2012, str. 218, nie je 'de'; Direktórium 2020/2021 opäť "de"
	"Sv. Martina de Porres, řeholníka",
	"",
	"S. Martini de Porres, religiosi",
	"",
	"Sv. Martina de Porres, řeholníka",
	"Porres Szent Márton szerzetes",
	"ru_text",
	"Св. Марціна дэ Порэса, законніка",
	"Hl. Martins frá Porres",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_03_SJ[POCET_JAZYKOV + 1] =
{
	"Bl. Ruperta Mayera, kňaza",
	"Bl. Ruperta Mayera, kněze",
	"",
	"",
	"",
	"Bl. Ruperta Mayera, kněze",
	"Boldog Mayer Rupert, áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_03_OFM[POCET_JAZYKOV + 1] =
{
	"Spomienka na všetkých zosnulých " HTML_LINE_BREAK "troch františkánskych rádov",
	"Vzpomínka na všechny zemřelé serafínského řádu",
	"",
	"",
	"",
	"",
	"Megemlékezés a Szeráfi Rend elhunytjairól", // HU: 24NOV
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_04[POCET_JAZYKOV + 1] =
{
	"Sv. Karola Boromejského, biskupa", // kedysi: "Sv. Karola Borromea, biskupa"
	"Sv. Karla Boromejského, biskupa",
	"",
	"S. Caroli Borromeo, episcopi",
	"",
	"Sv. Karla Boromejského, biskupa",
	"Borromeo Szent Károly püspök",
	"ru_text",
	"Св. Караля Барамэя, біскупа",
	"Hl. Karls Borrómeus, biskups",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_05_SK[POCET_JAZYKOV + 1] =
{
	"Sv. Imricha",
	"",
	"",
	"",
	"",
	"",
	"Szent Imre herceg",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_05_SJ[POCET_JAZYKOV + 1] =
{
	"Všetkých svätých a blahoslavených zo Spoločnosti Ježišovej",
	"Všech svatých Tovaryšstva Ježíšova", // bolo: "Všech svatých a blahoslavených Tovaryšstva Ježíšova"
	"",
	"",
	"",
	"",
	"Jézus Társasága minden szentje és boldogja", // HU SJ: 06NOV
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_05_SDB[POCET_JAZYKOV + 1] =
{
	"Všetkých zomrelých dobrodincov Saleziánskej rodiny",
	"Připomínka zemřelých dobrodinců a členů salesiánské rodiny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_05_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Šimona Ballacchiho, rehoľníka",
	"Bl. Šimona Ballacchiho, řeholníka",
	"",
	"",
	"",
	"Bl. Šimona Ballacchiho, řeholníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_06_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Alfonza Lopeza a spoločníkov, mučeníkov, členov 1. rádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_06_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Bonaventúru Garcia Paredesa, " HTML_LINE_BREAK "Hyacinta Serrana Lopeza, kňazov, " HTML_LINE_BREAK "a spoločníkov, španielskych mučeníkov",
	"Bl. Bonaventury Garcia Paredese, " HTML_LINE_BREAK "Hyacinta Serrana Lopeze, kněží, " HTML_LINE_BREAK "a druhů, španělských mučedníků",
	"",
	"",
	"",
	"Bl. Bonaventury Garcia Paredese, " HTML_LINE_BREAK "Hyacinta Serrana Lopeze, kněží, " HTML_LINE_BREAK "a druhů, španělských mučedníků",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_06_SJ[POCET_JAZYKOV + 1] =
{
	"",
	"Vzpomínka na všechny zemřelé z Tovaryšstva Ježíšova",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_06_1_OFMCAP[POCET_JAZYKOV + 1] =
{
	"Bl. Ondreja z Palazuela, kňaza, a spoločníkov, mučeníkov",
	"Bl. Ondřeje z Palazuela, kněze, a druhů, mučedníků",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_06_2_OFMCAP[POCET_JAZYKOV + 1] =
{
	"Bl. Fridricha z Bergy (Tarrez-Puigpelat), kňaza, a spoločníkov, mučeníkov",
	"Bl. Fridricha z Bergy (Tarrez-Puigpelat), kněze, a druhů, mučedníků",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_06_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Nonia Alvareza Pereiru, rehoľníka",
	"Sv. Nonia Alvarese Pereiry, řeholníka",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_07_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Františka od Ježiša, Márie a Jozefa " HTML_LINE_BREAK "(Palau y Quer), kňaza",
	"Bl. Františka od Ježíše, Marie a Josefa " HTML_LINE_BREAK "(Francisca Palau y Quer), kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_07_OP[POCET_JAZYKOV + 1] =
{
	"Všetkých svätých Rehole kazateľov",
	"",
	"",
	"",
	"",
	"Všech svatých Řádu kazatelů",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_07_SJ[POCET_JAZYKOV + 1] =
{
	"Spomienka na všetkých zosnulých " HTML_LINE_BREAK "zo Spoločnosti Ježišovej",
	"Všech zemřelých bratří a sester " HTML_LINE_BREAK "Tovaryšstva Ježíšova", // CZ: 06NOV
	"",
	"",
	"",
	"",
	"Megemlékezés Jézus Társasága minden halottjáról",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_08_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Alžbety od Najsvätejšej Trojice, panny",
	"Sv. Alžběty od Trojice, panny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Elísabetar af Þrenningunni, meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_08_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Jána Dunsa Scota, kňaza, člena 1. rádu",
	"Bl. Jana z Dunsu, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_08_OP[POCET_JAZYKOV + 1] =
{
	"Spomienka na všetkých zosnulých " HTML_LINE_BREAK "bratov a sestry Rehole kazateľov",
	"",
	"",
	"",
	"",
	"Všech zemřelých bratří a sester " HTML_LINE_BREAK "Řádu kazatelů",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_13_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Všetkých svätých vašej rehole " HTML_LINE_BREAK "a všetkých svätých rehoľných kanonikov",
	"Všech svatých premonstrátského řádu " HTML_LINE_BREAK "a všech svatých z řádů řeholních kanovníků", // CZ 08NOV
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_09[POCET_JAZYKOV + 1] =
{
	"Výročie posviacky Lateránskej baziliky",
	"Posvěcení lateránské baziliky",
	"",
	"In dedicatione basilicæ Lateranensis",
	"",
	"Posvěcení lateránské baziliky",
	"A lateráni-bazilika felszentelése",
	"ru_text",
	"Гадавіна пасвячэння Латэранскай базылікі",
	"Vígsludagur basilíkunnar í Lateran", // Vígsla Höfuðkirkjunnar í Lateran
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_10[POCET_JAZYKOV + 1] =
{
	"Sv. Leva Veľkého, pápeža a učiteľa Cirkvi",
	"Sv. Lva Velikého, papeže a učitele církve",
	"",
	"S. Leonis Magni, papæ et Ecclesiæ doctoris",
	"",
	"Sv. Lva Velikého, papeže a učitele církve",
	"Nagy Szent Leó pápa és egyháztanító",
	"ru_text",
	"Св. Льва Вялікага, папы і доктара Касцёла",
	"Hl. Leós mikla, páfa og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_11[POCET_JAZYKOV + 1] =
{
	"Sv. Martina z Tours, biskupa",
	"Sv. Martina, biskupa",
	"",
	"S. Martini, episcopi",
	"",
	"Sv. Martina, biskupa",
	"Tours-i Szent Márton püspök",
	"ru_text",
	"Св. Марціна Турскага, біскупа",
	"Hl. Marteins frá Tours, biskups",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_12[POCET_JAZYKOV + 1] =
{
	"Sv. Jozafáta, biskupa a mučeníka",
	"Sv. Josafata, biskupa a mučedníka",
	"",
	"S. Iosaphat, episcopi et martyris",
	"",
	"Sv. Josafata, biskupa a mučedníka",
	"Szent Jozafát püspök és vértanú",
	"ru_text",
	"Св. Язафата, біскупа і мучачніка",
	"Hl. Jósafats, biskups og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_13_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Artemida Zattiho, rehoľníka", // rehoľníka doplnené podľa CZ SDB -> koadjutora
	"Bl. Artemide Zattiho, koadjutora",
	"",
	"",
	"",
	"",
	"Szent Zatti Artemide szerzetes testvér",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_13_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Stanislava Kostku, rehoľníka",
	"Sv. Stanislava Kostky, řeholníka", // CZ: 18SEP (kvůli Anežce)
	"",
	"",
	"",
	"Sv. Stanislava Kostky, řeholníka",
	"Kosztka Szent Szaniszló, szerzetes",
	"",
	"Св. Станіслава Косткі, законніка", // BY: 18SEP
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_13_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Didaka z Alcaly, rehoľníka, člena 1. rádu",
	"Sv. Didaka z Alkaly, řeholníka",
	"",
	"",
	"",
	"",
	"Alcalai Szent Didák, szerzetes az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_13_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Sv. Anežky České, panny",
	"",
	"",
	"",
	"Sv. Anežky České, panny",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_13_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Magyar szentek és boldogok",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_14_OCD[POCET_JAZYKOV + 1] =
{
	"Všetkých svätých karmelitánskeho rádu",
	"Všech svatých našeho řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Allrasálnamessa Karmelreglunnar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_14_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Jozefa Pignatelliho, kňaza",
	"Sv. Josefa Pignatelliho, kněze",
	"",
	"",
	"",
	"Sv. Josefa Pignatelliho, kněze",
	"Pignatelli Szent József, áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_14_OPRAEM[POCET_JAZYKOV + 1] =
{
	"Sv. Siarda, opáta našej rehole",
	"Sv. Siarda, opata z premonstrátského řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_14_1_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Jána Licciu, kňaza",
	"Bl. Jana Liccia, kněze",
	"",
	"",
	"",
	"Bl. Jana Liccia, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_14_2_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Lucie z Narni, panny",
	"Bl. Lucie z Narni, panny, řeholnice",
	"",
	"",
	"",
	"Bl. Lucie z Narni, panny, řeholnice",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_14_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Mikuláša Tavelića a spoločníkov, " HTML_LINE_BREAK "kňazov a mučeníkov, členov 1. rádu",
	"Sv. Mikuláše Taveliče, kněze, a druhů, mučedníků",
	"",
	"",
	"",
	"",
	"Tavelic Szent Miklós, pap és vértanú társai az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_15[POCET_JAZYKOV + 1] =
{
	"Sv. Alberta Veľkého, biskupa a učiteľa Cirkvi",
	"Sv. Alberta Velikého, biskupa a učitele církve",
	"",
	"S. Alberti Magni, episcopi et Ecclesiæ doctoris",
	"",
	"Sv. Alberta Velikého, biskupa a učitele církve",
	"Nagy Szent Albert püspök és egyháztanító",
	"ru_text",
	"Св. Альбэрта Вялікага, біскупа і доктара Касцёла",
	"Hl. Alberts mikla, biskups og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_15_OCD[POCET_JAZYKOV + 1] =
{
	"Spomienka na všetkých zosnulých " HTML_LINE_BREAK "karmelitánskeho rádu",
	"Vzpomínka na všechny věrné zemřelé našeho řádu",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_15_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Magdalény Moranovej, panny",
	"Bl. Magdalény Morano, panny",
	"",
	"",
	"",
	"",
	"Boldog Morano Magdolna szűz",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_16_1[POCET_JAZYKOV + 1] =
{
	"Sv. Margity Škótskej",
	"Sv. Markéty Skotské",
	"",
	"S. Margaritæ Scotiæ",
	"",
	"Sv. Markéty Skotské",
	"Skóciai Szent Margit",
	"ru_text",
	"Св. Маргарыты Шатландскай",
	"Hl. Margrétar frá Skotlandi",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_16_2[POCET_JAZYKOV + 1] =
{
	"Sv. Gertrúdy, panny",
	"Sv. Gertrudy, panny",
	"",
	"S. Gertrudis, virginis",
	"",
	"Sv. Gertrudy, panny",
	"Nagy Szent Gertrúd szűz", // HU 17NOV
	"ru_text",
	"Св. Гертруды, панны",
	"Hl. Geirþrúðar, meyjar",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_16_BY[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Найсв. Панны Марыі, Маці Міласэрнасці " HTML_LINE_BREAK "(Маці Божай Вострабрамскай)",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_16_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Rocha Gonzáleza, Alfonza Rodrígueza " HTML_LINE_BREAK "a Jána del Castillo; bl. Jána Antona Solinasa, kňazov a mučeníkov",
	"Sv. Rocha Gonzáleze, Alfonse Rodrígueze " HTML_LINE_BREAK "a Jana del Castillo; bl. Jana Antonína Solinase, kněží a mučedníků",
	"",
	"",
	"",
	"Sv. Rocha Gonzáleze, Alfonse Rodrígueze " HTML_LINE_BREAK "a Jana del Castillo; bl. Jana Antonína Solinase, kněží a mučedníků",
	"González Szent Rókus, Rodríguez Szent Alfonz, " HTML_LINE_BREAK "del Castillo Szent János, áldozópapok és vértanúk",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_17[POCET_JAZYKOV + 1] =
{
	"Sv. Alžbety Uhorskej, rehoľníčky",
	"Sv. Alžběty Uherské, řeholnice",
	"",
	"S. Elisabeth Hungariæ",
	"",
	"Sv. Alžběty Uherské, řeholnice",
	"Árpád-házi Szent Erzsébet", // HU 19NOV
	"ru_text",
	"Св. Альжбеты Венгерскай, законніцы",
	"Hl. Elísabetar frá Ungverjalandi, reglusystir",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_17_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Alžbety Uhorskej, rehoľníčky, " HTML_LINE_BREAK "patrónky františkánskeho svetského rádu",
	"Sv. Alžběty Uherské, patronky 3. řádu",
	"",
	"",
	"",
	"",
	"Árpádházi Szent Erzsébet a III. Rend Pátrónája", // HU: 19NOV
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_18[POCET_JAZYKOV + 1] =
{
	"Výročie posviacky bazilík " HTML_LINE_BREAK "sv. Petra a Pavla, apoštolov",
	"Posvěcení římských bazilik " HTML_LINE_BREAK "svatých apoštolů Petra a Pavla",
	"",
	"In dedicatione basilicarum " HTML_LINE_BREAK "Ss. Petri et Pauli, apostolorum",
	"",
	"Posvěcení římských bazilik " HTML_LINE_BREAK "svatých apoštolů Petra a Pavla",
	"Szent Péter- és Szent Pál-bazilikák felszentelése",
	"ru_text",
	"Гадавіна пасвячэння рымскіх базылік " HTML_LINE_BREAK "св. апосталаў Пятра і Паўла",
	"Vígsludagur höfuðkirkna postulanna Péturs og Páls", // Vígsla höfuðkirkna hinna heilögu postula Péturs og Páls
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_18_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Salome z Krakova, panny, členky 2. rádu",
	"",
	"",
	"",
	"",
	"",
	"Krakkói Boldog Szalome, szűz a II. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_18_SCHP[POCET_JAZYKOV + 1] =
{
	"sk_text",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_19_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Agnesy z Assisi, panny, členky 2. rádu",
	"Sv. Anežky z Assisi, panny",
	"",
	"",
	"",
	"",
	"Assisi Szent Ágnes, szűz A II. Rendből", // HU: 16NOV
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_19_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Jakuba Benfattiho, biskupa",
	"Bl. Jakuba Benfattiho, biskupa",
	"",
	"",
	"",
	"Bl. Jakuba Benfattiho, biskupa",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_19_2_OP[POCET_JAZYKOV + 1] =
{
	"Sv. Márie Alfonzíny Danil Ghattas, panny",
	"",
	"",
	"",
	"",
	"Sv. Marie Alfonsiny Danil Ghattas, panny",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_19_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Rafaela Kalinowského, kňaza",
	"Sv. Rafaela od sv. Josefa (Josefa Kalinowského), kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Rafaels Kalinowski, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_20_SK[POCET_JAZYKOV + 1] =
{
	"Výročie posviacky katedrálneho chrámu " HTML_LINE_BREAK "sv. Emeráma",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_20_SK_2[POCET_JAZYKOV + 1] =
{
	"Bl. Anny Kolesárovej, panny a mučenice",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_20_BY[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Св. Рафала Каліноўскага, прэзбітэра",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_21[POCET_JAZYKOV + 1] =
{
	"Obetovanie prebl. Panny Márie", // podľa Direktória 2012, str. 226, nie je 'prebl.'; 3RM má: PREBLAHOSLAVENEJ
	"Zasvěcení Panny Marie v Jeruzalémě",
	"",
	"In Præsentatione Beatæ Mariæ Virginis",
	"",
	"Zasvěcení Panny Marie v Jeruzalémě",
	"A Boldogságos Szűz Mária bemutatása a templomban",
	"ru_text",
	"Ахвяраванне Найсв. Панны Марыі",
	"Offurgerð Maríu",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_22[POCET_JAZYKOV + 1] =
{
	"Sv. Cecílie, panny a mučenice",
	"Sv. Cecílie, panny a mučednice",
	"",
	"S. Cæciliæ, virginis et martyris",
	"",
	"Sv. Cecílie, panny a mučednice",
	"Szent Cecília szűz és vértanú",
	"ru_text",
	"Св. Цэцыліі, панны і мучаніцы",
	"Hl. Sesselju, meyjar og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_23_1[POCET_JAZYKOV + 1] =
{
	"Sv. Klimenta I. pápeža a mučeníka", // upravené podľa 3RM; predtým "Klement"
	"Sv. Klementa I., papeže a mučedníka",
	"",
	"S. Clementis I, papæ et martyris",
	"",
	"Sv. Klementa I., papeže a mučedníka",
	"Szent I. Kelemen pápa és vértanú",
	"ru_text",
	"Св. Клімэнта I, папы і мучаніка",
	"Hl. Klemensar I., páfa og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_23_2[POCET_JAZYKOV + 1] =
{
	"Sv. Kolumbána, opáta",
	"Sv. Kolumbána, opata",
	"",
	"S. Columbani, abbatis",
	"",
	"Sv. Kolumbána, opata",
	"Szent Kolumbán apát",
	"ru_text",
	"Св. Калюмбана, абата",
	"Hl. Kólúmbanusar, ábóta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_23_SJ[POCET_JAZYKOV + 1] =
{
	"Bl. Michala Augustína Pro, Emilia Moscosa a Rutília Grandeho, kňazov a mučeníkov",
	"Bl. Michaela Augustina Pro, Emilia Moscosa a Rutilia Grandeho, kněží a mučedníků",
	"",
	"",
	"",
	"Bl. Michaela Augustina Pro, Emilia Moscosa a Rutilia Grandeho, kněží a mučedníků",
	"Boldog Pro Mihály Ágoston, áldozópap és vértanú",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_24[POCET_JAZYKOV + 1] =
{
	"Sv. Andreja Dung-Laka, kňaza, " HTML_LINE_BREAK "a spoločníkov, mučeníkov", // upravené podľa 3RM; kedysi: Ondreja Dung-Laca
	"Sv. Ondřeje Dũng-Lạca, kněze, a druhů, mučedníků",
	"",
	"Ss. Andreæ Dũng-Lạc, presbyteri, et sociorum, martyrum",
	"",
	"Sv. Ignáce Delgada, biskupa, Vincence Liema, kněze, " HTML_LINE_BREAK "Dominika An-Khama, otce rodiny, a druhů, vietnamských mučedníků",
	"Dung-Lac Szent András áldozópap és társai, vietnámi vértanúk",
	"ru_text",
	"Св. Андрэя Зунг Лака, прэзбітэра, " HTML_LINE_BREAK "і паплечнікаў, мучанікаў",
	"Hl. Andrésar Dũng Lạc, prestur, og félaga, píslarvotta",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_24_OP[POCET_JAZYKOV + 1] =
{
	"Sv. Ignáca Klementa Delgadu, biskupa, " HTML_LINE_BREAK "Vincenta Le Quang Liem a Pace, kňaza, " HTML_LINE_BREAK "Dominika Pham Trong (An) Khama, laika, " HTML_LINE_BREAK "a spoločníkov, mučeníkov",
	"Sv. Ignáce Delgada, biskupa, Vincence Liema, kněze, " HTML_LINE_BREAK "Dominika An-Khama, otce rodiny, a druhů, vietnamských mučedníků",
	"",
	"",
	"",
	"Sv. Ignáce Delgada, biskupa, Vincence Liema, kněze, " HTML_LINE_BREAK "Dominika An-Khama, otce rodiny, a druhů, vietnamských mučedníků",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_25[POCET_JAZYKOV + 1] =
{
	"Sv. Kataríny Alexandrijskej, panny a mučenice",
	"Sv. Kateřiny Alexandrijské, panny a mučednice",
	"",
	"S. Catharinæ Alexandrinæ, virginis et martyris",
	"",
	"Sv. Kateřiny Alexandrijské, panny a mučednice",
	"Alexandriai Szent Katalin szűz és vértanú",
	"ru_text",
	"Св. Кацярыны Александрыйскай, панны і мучаніцы",
	"Hl. Katrínar frá Alexandríu, meyjar og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_25_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"A bazilika-székesegyház felszentelése",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_25_SDB[POCET_JAZYKOV + 1] =
{
	"Všetkých zomrelých rodičov saleziánov",
	"Připomínka zemřelých rodičů salesiánů",
	"",
	"",
	"",
	"",
	"¨hu_text",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_25_SCHP[POCET_JAZYKOV + 1] =
{
	"sk_text",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_26_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Berchmansa, rehoľníka",
	"Sv. Jana Berchmanse, řeholníka",
	"",
	"",
	"",
	"Sv. Jana Berchmanse, řeholníka",
	"Berchmans Szent János, szerzetes",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_26_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Leonarda z Porto Mauricia, kňaza, člena 1. rádu",
	"Sv. Leonarda z Porta Mauritia, kněze",
	"",
	"",
	"",
	"",
	"Portomauriziói Szent Lénárd, pap az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_27_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Františka Antona Fasaniho, kňaza, člena 1. rádu",
	"Sv. Františka Antonína Fasaniho, kněze",
	"",
	"",
	"",
	"",
	"Fasani Szent Ferenc Antal áldozópap az I. rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_27_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Margity Savojskej, matky rodiny a rehoľníčky",
	"Bl. Markéty Savojské, vdovy, mnišky",
	"",
	"",
	"",
	"Bl. Markéty Savojské, vdovy, mnišky",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_27_CM[POCET_JAZYKOV + 1] =
{
	"Nepoškvrnenej Panny Márie Zázračnej medaily",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_28_CM[POCET_JAZYKOV + 1] =
{
	"Sv. Kataríny Labouré, panny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_28_OFM[POCET_JAZYKOV + 1] =
{
	"Sv. Jakuba z Marky, kňaza, člena 1. rádu",
	"Sv. Jakuba z Marky, kněze",
	"",
	"",
	"",
	"",
	"Marchiai Szent Jakab, pap az I. Rendből",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_28_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"Marchiai Szent Jakab áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_29_SJ[POCET_JAZYKOV + 1] =
{
	"Bl. Františka Hoyos, kňaza",
	"Bl. Bernarda Františka de Hoyos, kněze",
	"",
	"",
	"",
	"Bl. Bernarda Františka de Hoyos, kněze",
	"Boldog de Hoyos Ferenc, áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_29_OFM[POCET_JAZYKOV + 1] =
{
	"Všetkých svätých troch františkánskych rádov",
	"Všech svatých serafínského řádu",
	"",
	"",
	"",
	"",
	"A szeráfi rend összes szentjei",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_29_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Dionýza, kňaza, a Redempta, rehoľníka, mučeníkov",
	"Bl. Dionýsia od Narození a Redempta od Kříže, " HTML_LINE_BREAK "řeholníků, mučedníků",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_NOV_30[POCET_JAZYKOV + 1] =
{
	"Sv. Ondreja, apoštola",
	"Sv. Ondřeje, apoštola",
	"",
	"S. Andreæ, apostoli",
	"",
	"Sv. Ondřeje, apoštola",
	"Szent András apostol",
	"ru_text",
	"Св. Андрэя, апостала",
	"Hl. Andrésar, postula",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// --------------- 12 december ---------------

const char* text_DEC_01_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Edmunda Campiona, Róberta Southwella a ich spoločníkov, mučeníkov",
	"Sv. Edmunda Kampiána a Roberta Southwella, kněží, a druhů, mučedníků", // bolo: "Sv. Edmunda Kampiána, kněze a mučedníka"
	"",
	"",
	"",
	"Sv. Edmunda Kampiána a Roberta Southwella, kněží, a druhů, mučedníků",
	"Campion Szent Ödön, Southwell Szent Róbert áldozópapok és társaik, vértanúk",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_01_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Jána Vercellského, kňaza",
	"Bl. Jana z Vercelli, kněze",
	"",
	"",
	"",
	"Bl. Jana z Vercelli, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_01_CZ[POCET_JAZYKOV + 1] =
{
	"Sv. Edmunda Campiona, kňaza a mučeníka",
	"Sv. Edmunda Kampiána, kněze a mučedníka",
	"",
	"",
	"",
	"Sv. Edmunda Kampiána, kněze a mučedníka",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_02_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Výročí posvěcení katedrály sv. Bartoloměje",
	"",
	"",
	"",
	"Výročí posvěcení katedrály sv. Bartoloměje",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_02_1_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Rafaela Chylińského, kňaza, člena 1. rádu",
	"Bl. Rafała Chylińského, kněze",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_02_2_OFM[POCET_JAZYKOV + 1] =
{
	"Bl. Angely Márie Astorchovej, panny, členky 2. rádu",
	"Bl. Marie Anděly Astorchové, panny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_03[POCET_JAZYKOV + 1] =
{
	"Sv. Františka Xaverského, kňaza",
	"Sv. Františka Xaverského, kněze",
	"",
	"S. Francisci Xavier, presbyteri",
	"",
	"Sv. Františka Xaverského, kněze",
	"Xavéri Szent Ferenc áldozópap",
	"ru_text",
	"Св. Фрацішка Ксавэрыя, прэзбітэра",
	"Hl. Frans Xavier, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_03_SJ[POCET_JAZYKOV + 1] =
{
	"Sv. Františka Xavérskeho, misionára",
	"Sv. Františka Xaverského, kněze",
	"",
	"",
	"",
	"Sv. Františka Xaverského, kněze",
	"Xavéri Szent Ferenc, áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_04[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Damascénskeho, kňaza a učiteľa Cirkvi",
	"Sv. Jana Damašského, kněze a učitele církve",
	"",
	"S. Ioannis Damasceni, presbyteri et Ecclesiæ doctoris",
	"",
	"Sv. Jana Damašského, kněze a učitele církve",
	"Damaszkuszi Szent János áldozópap és egyháztanító",
	"ru_text",
	"Св. Яна Дамаскіна, прэзбітэра і доктара Касцёла",
	"Hl. Jóhannesar Damasenus, prests og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_04_2[POCET_JAZYKOV + 1] =
{
	"Sv. Barbory, panny a mučenice",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Hl. Barböru, meyjar og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_05_SDB[POCET_JAZYKOV + 1] =
{
	"Bl. Filipa Rinaldiho, kňaza, " HTML_LINE_BREAK "zakladateľa Sekulárneho inštitútu dobrovoľníčok dona Bosca",
	"Bl. Filipa Rinaldiho, kněze, " HTML_LINE_BREAK "zakladatele Sekulárního institutu Volontárií Dona Boska",
	"",
	"",
	"",
	"",
	"Boldog Rinaldi Fülöp áldozópap",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_06[POCET_JAZYKOV + 1] =
{
	"Sv. Mikuláša, biskupa",
	"Sv. Mikuláše, biskupa",
	"",
	"S. Nicolai, episcopi",
	"",
	"Sv. Mikuláše, biskupa",
	"Szent Miklós püspök",
	"ru_text",
	"Св. Мікалая, біскупа",
	"Hl. Nikulásar, biskups",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_07[POCET_JAZYKOV + 1] =
{
	"Sv. Ambróza, biskupa a učiteľa Cirkvi",
	"Sv. Ambrože, biskupa a učitele církve",
	"",
	"S. Ambrosii, episcopi et Ecclesiæ doctoris",
	"",
	"Sv. Ambrože, biskupa a učitele církve",
	"Szent Ambrus püspök és egyháztanító",
	"ru_text",
	"Св. Амброзія, біскупа і доктара Касцёла",
	"Hl. Ambrósíusar, biskups og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_08[POCET_JAZYKOV + 1] =
{
	"Nepoškvrnené počatie prebl. Panny Márie",
	"Panny Marie, počaté bez poskvrny prvotního hříchu",
	"",
	"In Conceptione Immaculata Beatæ Mariæ Virginis",
	"",
	"Neposkvrněného početí Panny Marie",
	"A Boldogságos Szűz Mária szeplőtelen fogantatása",
	"ru_text",
	"Беззаганнага зачацця Найсв. Панны Марыі",
	"Flekklaus getnaður Maríu meyjar", // MARÍUMESSA, MARÍA MEY GETIN ÁN ERFÐASYNDAR
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_09[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Diega Cuauhtlatoatzina", // v španielčine sa volá Juan Diego, čo by v slovenčine malo byť Ján Jakub; do latinčiny preložili ako s. Joannes Didacus; z toho pri preklade textov vzniklo slovenské Ján Didak; v novom misáli: "sv. Jána Diega"
	"Sv. Jana Didaka Cuauhtlatoatzina",
	"",
	"S. Ioannis Didaci Cuauhtlatoatzin",
	"",
	"Sv. Jana Didaka Cuauhtlatoatzina",
	"Szent Juan Diego Cuauhtlatoatzin, Guadalupei látnok",
	"ru_text",
	"Св. Яна Дзідаха Куаухтлатоацына",
	"Hl. Juans Diego Cuauhtlatoatzin",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_09_CSA[POCET_JAZYKOV + 1] =
{
	"Sv. Petra Fouriera, kňaza",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_09_OP[POCET_JAZYKOV + 1] =
{
	"Sv. Narcisy od Ježiša Martillo y Moran, panny",
	"",
	"",
	"",
	"",
	"Sv. Narcisy od Ježíše Martillo y Moran, panny",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_10[POCET_JAZYKOV + 1] =
{
	"Prebl. Panny Márie Loretánskej",
	"Panny Marie Loretánské",
	"",
	"Beatæ Mariæ Virginis de Loreto",
	"",
	"Panny Marie Loretánské",
	"A loretói Boldogságos Szűz Mária",
	"ru_text",
	"by_text",
	"Hl. María mey frá Loreto",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_10_OFMCAP[POCET_JAZYKOV + 1] =
{
	"Bl. Arzénia Migliavacca z Trigola, kňaza",
	"Bl. Arsenia z Trigola (Migliavacca), kněze",
	"",
	"",
	"",
	"Bl. Arsenia Migliavacca z Trigola, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_11[POCET_JAZYKOV + 1] =
{
	"Sv. Damaza I., pápeža",
	"Sv. Damasa I., papeže",
	"",
	"S. Damasi I, papæ",
	"",
	"Sv. Damasa I., papeže",
	"Szent I. Damazusz pápa",
	"ru_text",
	"Св. Дамаса I, папы",
	"Hl. Damasusar I., páfa",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_11_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Márie Maravillas od Ježiša, panny",
	"Sv. Marie Maravillas od Ježíše, panny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_12[POCET_JAZYKOV + 1] =
{
	"Prebl. Panny Márie Guadalupskej",
	"Panny Marie Guadalupské",
	"",
	"Beatæ Mariæ Virginis de Guadalupe",
	"",
	"Panny Marie Guadalupské",
	"A Guadalupei Boldogságos Szűz Mária",
	"ru_text",
	"Найсв. Панны Марыі з Гвадэлупы",
	"Alsællar Maríu meyjar frá Guadalupe",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_13[POCET_JAZYKOV + 1] =
{
	"Sv. Lucie, panny a mučenice",
	"Sv. Lucie, panny a mučednice",
	"",
	"S. Luciæ, virginis et martyris",
	"",
	"Sv. Lucie, panny a mučednice",
	"Szent Lúcia szűz és vértanú",
	"ru_text",
	"Св. Люцыі, панны і мучаніцы",
	"Hl. Lúsíu, meyjar og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_14[POCET_JAZYKOV + 1] =
{
	"Sv. Jána od Kríža, kňaza a učiteľa Cirkvi", // kedysi: "Sv. Jána z Kríža, kňaza a učiteľa Cirkvi",
	"Sv. Jana od Kříže, kněze a učitele církve",
	"",
	"S. Ioannis a Cruce, presbyteri et Ecclesiæ doctoris",
	"",
	"Sv. Jana od Kříže, kněze a učitele církve",
	"Keresztes Szent János áldozópap és egyháztanító",
	"ru_text",
	"Св. Яна ад Крыжа, прэзбітэра і доктара Касцёла",
	"Hl. Jóhannesar af krossi, prests og kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_14_OCD[POCET_JAZYKOV + 1] =
{
	"Sv. Jána od Kríža, " HTML_LINE_BREAK "kňaza a učiteľa Cirkvi, nášho Otca",
	"Sv. Jana od Kříže, kněze a učitele církve",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_15_HU[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"B. Ioannis Brenner, martyr",
	"",
	"",
	"Boldog Brenner János áldozópap és vértanú",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_16_OP[POCET_JAZYKOV + 1] =
{
	"Bl. Šebastiána Maggiho, kňaza",
	"Bl. Šebestiána Maggiho, kněze",
	"",
	"",
	"",
	"Bl. Šebestiána Maggiho, kněze",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_16_OCD[POCET_JAZYKOV + 1] =
{
	"Bl. Márie od Anjelov, panny",
	"Bl. Marie od Andělů, panny",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_21[POCET_JAZYKOV + 1] =
{
	"Sv. Petra Kanízia, kňaza a učiteľa Cirkvi",
	"Sv. Petra Kanisia, kněze a učitele církve",
	"",
	"S. Petri Canisii, presbyteri et Ecclesiæ doctoris",
	"",
	"Sv. Petra Kanisia, kněze a učitele církve",
	"Kaníziusz Szent Péter áldozópap és egyháztanító",
	"ru_text",
	"Св. Пятра Канізія, прэзбітэра і доктара Касцёла",
	"Hl. Péturs Canisíus, prests og  kirkjufræðara",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_22_CZ[POCET_JAZYKOV + 1] =
{
	"",
	"Výročí posvěcení katedrály sv. Mikuláše",
	"",
	"",
	"",
	"Výročí posvěcení katedrály sv. Mikuláše",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_22_OP[POCET_JAZYKOV + 1] =
{
	"Výročie potvrdenia Rehole kazateľov (1216)",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_23[POCET_JAZYKOV + 1] =
{
	"Sv. Jána Kentského, kňaza",
	"Sv. Jana Kentského, kněze",
	"",
	"S. Ioannis de Kęty, presbyteri",
	"",
	"Sv. Jana Kentského, kněze",
	"Kęty Szent János áldozópap",
	"ru_text",
	"Св. Яна Кенцкага, прэзбітэра",
	"Hl. Jóhannesar frá Kęty, prests",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_23_IS[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Þorláksmessa á vetri",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_26[POCET_JAZYKOV + 1] =
{
	"Sv. Štefana, prvého mučeníka",
	"Sv. Štěpána, prvomučedníka",
	"",
	"S. Stephani, protomartyris",
	"",
	"Sv. Štěpána, prvomučedníka",
	"Szent István első vértanú",
	"ru_text",
	"Св. Стэфана, першамучаніка",
	"Hl. Stefáns, frumvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_27[POCET_JAZYKOV + 1] =
{
	"Sv. Jána, apoštola a evanjelistu",
	"Sv. Jana, apoštola a evangelisty",
	"",
	"S. Ioannis, apostoli et evangelistæ",
	"",
	"Sv. Jana, apoštola a evangelisty",
	"Szent János apostol és evangélista",
	"ru_text",
	"Св. Яна, апостала і евангеліста",
	"Hl. Jóhannesar postula og guðspjallamanns",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_28[POCET_JAZYKOV + 1] =
{
	"Svätých Neviniatok, mučeníkov",
	"Svatých Mláďátek, mučedníků",
	"",
	"Ss. Innocentium, martyrum",
	"",
	"Svatých Mláďátek, mučedníků",
	"Aprószentek",
	"ru_text",
	"Св. Немаўлят, мучанікаў",
	"Hl. börnin saklausu",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_29[POCET_JAZYKOV + 1] =
{
	"Sv. Tomáša Becketa, biskupa a mučeníka",
	"Sv. Tomáše Becketa, biskupa a mučedníka",
	"",
	"S. Thomæ Becket, episcopi et martyris",
	"",
	"Sv. Tomáše Becketa, biskupa a mučedníka",
	"Becket Szent Tamás püspök és vértanú",
	"ru_text",
	"Св. Томаса Бекета, біскупа і мучаніка",
	"Hl. Tómasar Becket, biskups og píslarvotts",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_DEC_31[POCET_JAZYKOV + 1] =
{
	"Sv. Silvestra I., pápeža",
	"Sv. Silvestra I., papeže",
	"",
	"S. Silvestri I, papæ",
	"",
	"Sv. Silvestra I., papeže",
	"Szent I. Szilveszter pápa",
	"ru_text",
	"Св. Сільвэстра I, папы",
	"Hl. Silvesters I., páfa",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

// --------------- 00 pohyblivé slávenia | celebrations with moving date ---------------

const char* text_VELKY_PONDELOK[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Вялікі панядзелак",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_VELKY_UTOROK[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Вялікі аўторак",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_VELKA_STREDA[POCET_JAZYKOV + 1] =
{
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Вялікая серада",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_ZELENY_STVRTOK[POCET_JAZYKOV + 1] =
{
	"Štvrtok Svätého týždňa (Zelený štvrtok)",
	"Zelený čtvrtek",
	"Maundy Thursday",
	"",
	"",
	"Zelený čtvrtek",
	"Nagycsütörtök",
	"ru_text",
	"Вялікі чацвер",
	"Skírdagur",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_ZELENY_STVRTOK_VESPERY[POCET_JAZYKOV + 1] =
{
	"Štvrtok Pánovej večere",
	"Zelený čtvrtek – Památka Večeře Páně",
	"Maundy Thursday",
	"",
	"",
	"Zelený čtvrtek – Památka Večeře Páně",
	"Nagycsütörtök",
	"ru_text",
	"Вялікі чацвер",
	"Skírdagur",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_VELKY_PIATOK[POCET_JAZYKOV + 1] =
{
	"Piatok utrpenia Pána (Veľký piatok)",
	"Velký pátek",
	"Good Friday",
	"Feria VI in Passione Domini",
	"",
	"Velký pátek",
	"Nagypéntek",
	"ru_text",
	"Вялікая пятніца Мукі Пана",
	"Föstudagurinn langi",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_BIELA_SOBOTA[POCET_JAZYKOV + 1] =
{
	"Svätá sobota (Biela sobota)",
	"Bílá sobota",
	"Holy Saturday",
	"Sabbato sancto",
	"",
	"Bílá sobota",
	"Nagyszombat",
	"ru_text",
	"Вялікая субота",
	"Laugardagur í Dymbilviku",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_KVETNA_NEDELA[POCET_JAZYKOV + 1] =
{
	"Palmová (Kvetná) nedeľa," HTML_LINE_BREAK "čiže Nedeľa utrpenia Pána",
	"Květná neděle",
	"Palm Sunday of the Passion of the Lord",
	"Dominica in Palmis " HTML_LINE_BREAK "De Passione Domini",
	"",
	"Květná neděle",
	"Virágvasárnap, vagyis az Úr szenvedésének vasárnapja",
	"ru_text",
	"Пальмовая нядзеля альбо нядзеля Мукі Пана",
	"Pálmasunnudagur",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_PO_POPOLCOVEJ_STREDE[POCET_JAZYKOV + 1] =
{
	"po Popolcovej strede",
	"po Popeleční středě",
	"",
	"post Cineres",
	"",
	"po Popeleční středě",
	"Hamvazószerda után",
	"ru_text",
	"by_text",
	"eftir Öskudag",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_V_OKTAVE_NARODENIA[POCET_JAZYKOV + 1] =
{
	"v oktáve Narodenia Pána",
	"v oktávu Narození Páně",
	"",
	"infra octavam Nativitatis",
	"",
	"v oktávu Narození Páně",
	"Karácsony nyolcada",
	"ru_text",
	"ў актаве Нараджэння Пана",
	"í Jólaviku",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_KONIEC_OKTAVY_NARODENIA_PANA[POCET_JAZYKOV + 1] =
{
	"koniec Oktávy narodenia Pána",
	"konec Oktávu Narození Páně",
	"",
	"",
	"",
	"konec Oktávu Narození Páně",
	"Karácsony nyolcada – Kiskarácsony",
	"ru_text",
	"канец Актавы нараджэння Пана",
	"lok Áttundar Fæðingar Drottins",
	/* STRING_2_FOR_NEW_LANGUAGE */
};
const char* text_LEN_V_KONSEKROVANYCH_KOSTOLOCH[POCET_JAZYKOV + 1] =
{
	"len v posvätených kostoloch", // kedysi: "len v konsekrovaných kostoloch"
	"jen v posvěcených kostelích",
	"",
	"in ecclesiis consecratis tantum",
	"",
	"jen v posvěcených kostelích",
	"csak a felszentelt templomokban",
	"ru_text",
	"by_text",
	"bara í vígðum kirkjum",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* menu_item_type_name[POCET_MENU_ITEM_TYPE + 1] =
{ "undefined", "switch", "bitopt", "application" };

const char* text_menu_group_jazyk[POCET_MENU_GROUPS + 1][POCET_JAZYKOV + 1] =
{
	{ "Všeobecné nastavenia", "Obecné nastavení", "General settings", "General settings", "", "Obecné nastavení", "General settings", "General settings", "General settings", "General settings", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Zariadenie", "Zařízení", "Device", "Apparatus", "", "Zařízení", "Eszköz", "Device", "Device", "Tæki", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Vzhľad", "Vzhled", "Appearance", "Visual", "", "Vzhled", "Megjelenés", "Appearance", "Appearance", "Útlit", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Texty modlitieb", "Texty modliteb", "Prayer texts", "Textus", "", "Texty modliteb", "Imaóra szövege", "Prayer texts", "Prayer texts", "Bænatextar", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Liturgický kalendár", "Liturgický kalendář", "Liturgical calendar", "Calendarium liturgicum", "", "Liturgický kalendář", "Liturgikus naptár", "Liturgical calendar", "Liturgical calendar", "Helgidagatal", /* STRING_1_FOR_NEW_LANGUAGE */ }
	, { "Hlasový výstup", "Hlasový výstup", "Voice output", "Vox output", "", "Hlasový výstup", "Hangkimenet", "Voice output", "Voice output", "Raddúttak", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

#define		text_menu_group(a)	text_menu_group_jazyk[a][_global_jazyk]

const char* menu_text_mode[POCET_JAZYKOV + 1] =
{
	"Režim online/offline",
	"Režim online/offline",
	"Mode online/offline",
	"Modus online/offline",
	"",
	"Režim online/offline",
	"Režim online/offline",
	"ru_text",
	"by_text",
	"Režim online/offline",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* menu_text_volume_buttons[POCET_JAZYKOV + 1] =
{
	"Použiť tlačidlá hlasitosti na listovanie",
	"Tlačítka hlasitosti na listování",
	"Volume buttons for scrolling",
	"Pulsabulæ ad mutandum gradus claritatis ad promovendum",
	"",
	"Tlačítka hlasitosti na listování",
	"Hangerőt állító gombok használata görgetéshez",
	"ru_text",
	"by_text",
	"Notið hljóðhnappana til að skruna",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* menu_text_do_not_dim_screen[POCET_JAZYKOV + 1] =
{
	"Nezhasínať obrazovku",
	"Nezhasínat obrazovku",
	"Do not dim screen",
	"Scrinium non claudere",
	"",
	"Nezhasínat obrazovku",
	"Ne sötétüljön el a képernyő",
	"ru_text",
	"by_text",
	"Ekki slökkva á skjánum",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* menu_text_do_not_disturb[POCET_JAZYKOV + 1] =
{
	"Režim Nerušiť",
	"Režim Nerušit",
	"Do Not Disturb mode",
	"Modus «Non perturbare»",
	"",
	"Režim Nerušit",
	"A csengetés kikapcsolása",
	"ru_text",
	"by_text",
	"Ekki trufla haminn",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* menu_text_lock_font_size[POCET_JAZYKOV + 1] =
{
	"Zakázať gesto priblíženia (uzamknúť veľkosť písma)",
	"Zakázat gesto přiblížení (uzakmnout velikost písma)",
	"Disable zoom gesture (lock font size)",
	"Admotionem vetare (magnitudinem litterarum claudere)",
	"",
	"Zakázat gesto přiblížení (uzakmnout velikost písma)",
	"Tiltsa le a zoom gesztusát (zárja be a betűméretet)",
	"ru_text",
	"by_text",
	"Aftengið aðdrátt (læsið leturstærð)",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

const char* menu_text_alt_background[POCET_JAZYKOV + 1] =
{
	"Alternatívna farba pozadia (žltá)",
	"Alternativní barva pozadí (žlutá)",
	"Alternative background color (yellow)",
	"Alius color reductiorum (flavus)",
	"",
	"Alternativní barva pozadí (žlutá)",
	"Választható háttérszín (sárga)",
	"ru_text",
	"by_text",
	"Annars konar bakgrunnslitur (gulur)",
	/* STRING_2_FOR_NEW_LANGUAGE */
};

short int lokal_slav_slavnost_fma[POCET_JAZYKOV + 1] =
{
	LOKAL_SLAV_SLAVNOST_FMA,
	LOKAL_SLAV_SLAVNOST_FMA_CZ,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_SLAVNOST_FMA_CZ,
	LOKAL_SLAV_SLAVNOST_FMA_HU,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_NEURCENE,
	/* ADD_VALUE_FOR_NEW_LANGUAGE */
};

short int lokal_slav_spomienka_fma[POCET_JAZYKOV + 1] =
{
	LOKAL_SLAV_SPOMIENKA_FMA,
	LOKAL_SLAV_SPOMIENKA_FMA_CZ,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_SPOMIENKA_FMA_CZ,
	LOKAL_SLAV_SPOMIENKA_FMA_HU,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_NEURCENE,
	/* ADD_VALUE_FOR_NEW_LANGUAGE */
};

short int lokal_slav_lub_spomienka_fma_vdb[POCET_JAZYKOV + 1] =
{
	LOKAL_SLAV_LUB_SPOMIENKA_FMA_VDB,
	LOKAL_SLAV_LUB_SPOMIENKA_FMA_VDB_CZ,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_LUB_SPOMIENKA_FMA_VDB_CZ,
	LOKAL_SLAV_LUB_SPOMIENKA_FMA_VDB_HU,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_NEURCENE,
	/* ADD_VALUE_FOR_NEW_LANGUAGE */
};

short int lokal_slav_sviatok_vdb[POCET_JAZYKOV + 1] =
{
	LOKAL_SLAV_SVIATOK_VDB,
	LOKAL_SLAV_SVIATOK_VDB_CZ,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_SVIATOK_VDB_CZ,
	LOKAL_SLAV_SVIATOK_VDB_HU,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_NEURCENE,
	LOKAL_SLAV_NEURCENE,
	/* ADD_VALUE_FOR_NEW_LANGUAGE */
};

#endif // __HODIN_H_

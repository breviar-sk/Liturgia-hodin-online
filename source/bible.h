/******************************************************************/
/*                                                                */
/* bible.h                                                        */
/* (c)2017-2023 | Juraj Vidéky                                    */
/*                                                                */
/* description | utilities for biblical readings                  */
/*                                                                */
/******************************************************************/

#ifndef __BIBLE_H_
#define __BIBLE_H_

#include "mydefs.h"

#define 	BIBLE_BOOKS_OT_COUNT 	39
#define 	BIBLE_BOOKS_NT_COUNT 	27
#define 	BIBLE_BOOKS_DC_COUNT 	7
#define		BIBLE_BOOKS_COUNT		73

// Bible books, catholic canon, numbered from 0
#define		BIBLE_BOOK_OT_Gen		0
#define		BIBLE_BOOK_OT_Exod		1
#define		BIBLE_BOOK_OT_Lev		2
#define		BIBLE_BOOK_OT_Num		3
#define		BIBLE_BOOK_OT_Deut		4
#define		BIBLE_BOOK_OT_Josh		5
#define		BIBLE_BOOK_OT_Judg		6
#define		BIBLE_BOOK_OT_Ruth		7
#define		BIBLE_BOOK_OT_1Sam		8
#define		BIBLE_BOOK_OT_2Sam		9
#define		BIBLE_BOOK_OT_1Kgs		10
#define		BIBLE_BOOK_OT_2Kgs		11
#define		BIBLE_BOOK_OT_1Chr		12
#define		BIBLE_BOOK_OT_2Chr		13
#define		BIBLE_BOOK_OT_Ezra		14
#define		BIBLE_BOOK_OT_Neh		15
#define		BIBLE_BOOK_OT_Esth		16
#define		BIBLE_BOOK_OT_Job		17
#define		BIBLE_BOOK_OT_Ps		18
#define		BIBLE_BOOK_OT_Prov		19
#define		BIBLE_BOOK_OT_Eccl		20
#define		BIBLE_BOOK_OT_Song		21
#define		BIBLE_BOOK_OT_Isa		22
#define		BIBLE_BOOK_OT_Jer		23
#define		BIBLE_BOOK_OT_Lam		24
#define		BIBLE_BOOK_OT_Ezek		25
#define		BIBLE_BOOK_OT_Dan		26
#define		BIBLE_BOOK_OT_Hos		27
#define		BIBLE_BOOK_OT_Joel		28
#define		BIBLE_BOOK_OT_Amos		29
#define		BIBLE_BOOK_OT_Obad		30
#define		BIBLE_BOOK_OT_Jonah		31
#define		BIBLE_BOOK_OT_Mic		32
#define		BIBLE_BOOK_OT_Nah		33
#define		BIBLE_BOOK_OT_Hab		34
#define		BIBLE_BOOK_OT_Zeph		35
#define		BIBLE_BOOK_OT_Hag		36
#define		BIBLE_BOOK_OT_Zech		37
#define		BIBLE_BOOK_OT_Mal		38
#define		BIBLE_BOOK_NT_Matt		39
#define		BIBLE_BOOK_NT_Mark		40
#define		BIBLE_BOOK_NT_Luke		41
#define		BIBLE_BOOK_NT_John		42
#define		BIBLE_BOOK_NT_Acts		43
#define		BIBLE_BOOK_NT_Rom		44
#define		BIBLE_BOOK_NT_1Cor		45
#define		BIBLE_BOOK_NT_2Cor		46
#define		BIBLE_BOOK_NT_Gal		47
#define		BIBLE_BOOK_NT_Eph		48
#define		BIBLE_BOOK_NT_Phil		49
#define		BIBLE_BOOK_NT_Col		50
#define		BIBLE_BOOK_NT_1Thess		51
#define		BIBLE_BOOK_NT_2Thess		52
#define		BIBLE_BOOK_NT_1Tim		53
#define		BIBLE_BOOK_NT_2Tim		54
#define		BIBLE_BOOK_NT_Titus		55
#define		BIBLE_BOOK_NT_Phlm		56
#define		BIBLE_BOOK_NT_Heb		57
#define		BIBLE_BOOK_NT_Jas		58
#define		BIBLE_BOOK_NT_1Pet		59
#define		BIBLE_BOOK_NT_2Pet		60
#define		BIBLE_BOOK_NT_1John		61
#define		BIBLE_BOOK_NT_2John		62
#define		BIBLE_BOOK_NT_3John		63
#define		BIBLE_BOOK_NT_Jude		64
#define		BIBLE_BOOK_NT_Rev		65
#define		BIBLE_BOOK_DC_Tob		66
#define		BIBLE_BOOK_DC_Jdt		67
#define		BIBLE_BOOK_DC_Wis		68
#define		BIBLE_BOOK_DC_Sir		69
#define		BIBLE_BOOK_DC_Bar		70
#define		BIBLE_BOOK_DC_1Macc		71
#define		BIBLE_BOOK_DC_2Macc		72
// #define		BIBLE_BOOK_DC_GkEsth // catholic canon: content of BIBLE_BOOK_OT_Esth
// #define		BIBLE_BOOK_DC_PrAzar // catholic canon: content of BIBLE_BOOK_OT_Dan in chapter 3
// #define		BIBLE_BOOK_DC_Sus // catholic canon: content of BIBLE_BOOK_OT_Dan as chapter 13
// #define		BIBLE_BOOK_DC_Bel // catholic canon: content of BIBLE_BOOK_OT_Dan as chapter 14
// #define		BIBLE_BOOK_DC_SgThree // catholic canon: content of BIBLE_BOOK_OT_Dan in chapter 3
// #define		BIBLE_BOOK_DC_EpJer // catholic canon: content of BIBLE_BOOK_DC_Bar as chapter 6
// the following are not in catholic canon
// #define		BIBLE_BOOK_DC_3Macc
// #define		BIBLE_BOOK_DC_4Macc
// #define		BIBLE_BOOK_DC_1Esd
// #define		BIBLE_BOOK_DC_2Esd
// #define		BIBLE_BOOK_DC_PrMan

// taken from https://wiki.crosswire.org/OSIS_Book_Abbreviations
const char* bible_paratext_shortcut[BIBLE_BOOKS_COUNT + 1] =
{
	"GEN", /* BIBLE_BOOK_OT_Gen */
	"EXO", /* BIBLE_BOOK_OT_Exod */
	"LEV", /* BIBLE_BOOK_OT_Lev */
	"NUM", /* BIBLE_BOOK_OT_Num */
	"DEU", /* BIBLE_BOOK_OT_Deut */
	"JOS", /* BIBLE_BOOK_OT_Josh */
	"JDG", /* BIBLE_BOOK_OT_Judg */
	"RUT", /* BIBLE_BOOK_OT_Ruth */
	"1SA", /* BIBLE_BOOK_OT_1Sam */
	"2SA", /* BIBLE_BOOK_OT_2Sam */
	"1KI", /* BIBLE_BOOK_OT_1Kgs */
	"2KI", /* BIBLE_BOOK_OT_2Kgs */
	"1CH", /* BIBLE_BOOK_OT_1Chr */
	"2CH", /* BIBLE_BOOK_OT_2Chr */
	"EZR", /* BIBLE_BOOK_OT_Ezra */
	"NEH", /* BIBLE_BOOK_OT_Neh */
	"EST", /* BIBLE_BOOK_OT_Esth */
	"JOB", /* BIBLE_BOOK_OT_Job */
	"PSA", /* BIBLE_BOOK_OT_Ps */
	"PRO", /* BIBLE_BOOK_OT_Prov */
	"ECC", /* BIBLE_BOOK_OT_Eccl */
	"SNG", /* BIBLE_BOOK_OT_Song */
	"ISA", /* BIBLE_BOOK_OT_Isa */
	"JER", /* BIBLE_BOOK_OT_Jer */
	"LAM", /* BIBLE_BOOK_OT_Lam */
	"EZK", /* BIBLE_BOOK_OT_Ezek */
	"DAN", /* BIBLE_BOOK_OT_Dan */
	"HOS", /* BIBLE_BOOK_OT_Hos */
	"JOL", /* BIBLE_BOOK_OT_Joel */
	"AMO", /* BIBLE_BOOK_OT_Amos */
	"OBA", /* BIBLE_BOOK_OT_Obad */
	"JON", /* BIBLE_BOOK_OT_Jonah */
	"MIC", /* BIBLE_BOOK_OT_Mic */
	"NAM", /* BIBLE_BOOK_OT_Nah */
	"HAB", /* BIBLE_BOOK_OT_Hab */
	"ZEP", /* BIBLE_BOOK_OT_Zeph */
	"HAG", /* BIBLE_BOOK_OT_Hag */
	"ZEC", /* BIBLE_BOOK_OT_Zech */
	"MAL", /* BIBLE_BOOK_OT_Mal */
	"MAT", /* BIBLE_BOOK_NT_Matt */
	"MRK", /* BIBLE_BOOK_NT_Mark */
	"LUK", /* BIBLE_BOOK_NT_Luke */
	"JHN", /* BIBLE_BOOK_NT_John */
	"ACT", /* BIBLE_BOOK_NT_Acts */
	"ROM", /* BIBLE_BOOK_NT_Rom */
	"1CO", /* BIBLE_BOOK_NT_1Cor */
	"2CO", /* BIBLE_BOOK_NT_2Cor */
	"GAL", /* BIBLE_BOOK_NT_Gal */
	"EPH", /* BIBLE_BOOK_NT_Eph */
	"PHP", /* BIBLE_BOOK_NT_Phil */
	"COL", /* BIBLE_BOOK_NT_Col */
	"1TH", /* BIBLE_BOOK_NT_1Thess */
	"2TH", /* BIBLE_BOOK_NT_2Thess */
	"1TI", /* BIBLE_BOOK_NT_1Tim */
	"2TI", /* BIBLE_BOOK_NT_2Tim */
	"TIT", /* BIBLE_BOOK_NT_Titus */
	"PHM", /* BIBLE_BOOK_NT_Phlm */
	"HEB", /* BIBLE_BOOK_NT_Heb */
	"JAS", /* BIBLE_BOOK_NT_Jas */
	"1PE", /* BIBLE_BOOK_NT_1Pet */
	"2PE", /* BIBLE_BOOK_NT_2Pet */
	"1JN", /* BIBLE_BOOK_NT_1John */
	"2JN", /* BIBLE_BOOK_NT_2John */
	"3JN", /* BIBLE_BOOK_NT_3John */
	"JUD", /* BIBLE_BOOK_NT_Jude */
	"REV", /* BIBLE_BOOK_NT_Rev */
	"TOB", /* BIBLE_BOOK_DC_Tob */
	"JDT", /* BIBLE_BOOK_DC_Jdt */
	"WIS", /* BIBLE_BOOK_DC_Wis */
	"SIR", /* BIBLE_BOOK_DC_Sir */
	"BAR", /* BIBLE_BOOK_DC_Bar */
	"1MA", /* BIBLE_BOOK_DC_1Macc */
	"2MA", /* BIBLE_BOOK_DC_2Macc */
};

const char* bible_paratext_shortcut_with_dot[BIBLE_BOOKS_COUNT + 1] =
{
	"GEN.", /* BIBLE_BOOK_OT_Gen */
	"EXO.", /* BIBLE_BOOK_OT_Exod */
	"LEV.", /* BIBLE_BOOK_OT_Lev */
	"NUM.", /* BIBLE_BOOK_OT_Num */
	"DEU.", /* BIBLE_BOOK_OT_Deut */
	"JOS.", /* BIBLE_BOOK_OT_Josh */
	"JDG.", /* BIBLE_BOOK_OT_Judg */
	"RUT.", /* BIBLE_BOOK_OT_Ruth */
	"1SA.", /* BIBLE_BOOK_OT_1Sam */
	"2SA.", /* BIBLE_BOOK_OT_2Sam */
	"1KI.", /* BIBLE_BOOK_OT_1Kgs */
	"2KI.", /* BIBLE_BOOK_OT_2Kgs */
	"1CH.", /* BIBLE_BOOK_OT_1Chr */
	"2CH.", /* BIBLE_BOOK_OT_2Chr */
	"EZR.", /* BIBLE_BOOK_OT_Ezra */
	"NEH.", /* BIBLE_BOOK_OT_Neh */
	"EST.", /* BIBLE_BOOK_OT_Esth */
	"JOB.", /* BIBLE_BOOK_OT_Job */
	"PSA.", /* BIBLE_BOOK_OT_Ps */
	"PRO.", /* BIBLE_BOOK_OT_Prov */
	"ECC.", /* BIBLE_BOOK_OT_Eccl */
	"SNG.", /* BIBLE_BOOK_OT_Song */
	"ISA.", /* BIBLE_BOOK_OT_Isa */
	"JER.", /* BIBLE_BOOK_OT_Jer */
	"LAM.", /* BIBLE_BOOK_OT_Lam */
	"EZK.", /* BIBLE_BOOK_OT_Ezek */
	"DAN.", /* BIBLE_BOOK_OT_Dan */
	"HOS.", /* BIBLE_BOOK_OT_Hos */
	"JOL.", /* BIBLE_BOOK_OT_Joel */
	"AMO.", /* BIBLE_BOOK_OT_Amos */
	"OBA.", /* BIBLE_BOOK_OT_Obad */
	"JON.", /* BIBLE_BOOK_OT_Jonah */
	"MIC.", /* BIBLE_BOOK_OT_Mic */
	"NAM.", /* BIBLE_BOOK_OT_Nah */
	"HAB.", /* BIBLE_BOOK_OT_Hab */
	"ZEP.", /* BIBLE_BOOK_OT_Zeph */
	"HAG.", /* BIBLE_BOOK_OT_Hag */
	"ZEC.", /* BIBLE_BOOK_OT_Zech */
	"MAL.", /* BIBLE_BOOK_OT_Mal */
	"MAT.", /* BIBLE_BOOK_NT_Matt */
	"MRK.", /* BIBLE_BOOK_NT_Mark */
	"LUK.", /* BIBLE_BOOK_NT_Luke */
	"JHN.", /* BIBLE_BOOK_NT_John */
	"ACT.", /* BIBLE_BOOK_NT_Acts */
	"ROM.", /* BIBLE_BOOK_NT_Rom */
	"1CO.", /* BIBLE_BOOK_NT_1Cor */
	"2CO.", /* BIBLE_BOOK_NT_2Cor */
	"GAL.", /* BIBLE_BOOK_NT_Gal */
	"EPH.", /* BIBLE_BOOK_NT_Eph */
	"PHP.", /* BIBLE_BOOK_NT_Phil */
	"COL.", /* BIBLE_BOOK_NT_Col */
	"1TH.", /* BIBLE_BOOK_NT_1Thess */
	"2TH.", /* BIBLE_BOOK_NT_2Thess */
	"1TI.", /* BIBLE_BOOK_NT_1Tim */
	"2TI.", /* BIBLE_BOOK_NT_2Tim */
	"TIT.", /* BIBLE_BOOK_NT_Titus */
	"PHM.", /* BIBLE_BOOK_NT_Phlm */
	"HEB.", /* BIBLE_BOOK_NT_Heb */
	"JAS.", /* BIBLE_BOOK_NT_Jas */
	"1PE.", /* BIBLE_BOOK_NT_1Pet */
	"2PE.", /* BIBLE_BOOK_NT_2Pet */
	"1JN.", /* BIBLE_BOOK_NT_1John */
	"2JN.", /* BIBLE_BOOK_NT_2John */
	"3JN.", /* BIBLE_BOOK_NT_3John */
	"JUD.", /* BIBLE_BOOK_NT_Jude */
	"REV.", /* BIBLE_BOOK_NT_Rev */
	"TOB.", /* BIBLE_BOOK_DC_Tob */
	"JDT.", /* BIBLE_BOOK_DC_Jdt */
	"WIS.", /* BIBLE_BOOK_DC_Wis */
	"SIR.", /* BIBLE_BOOK_DC_Sir */
	"BAR.", /* BIBLE_BOOK_DC_Bar */
	"1MA.", /* BIBLE_BOOK_DC_1Macc */
	"2MA.", /* BIBLE_BOOK_DC_2Macc */
};

// default Bible online translation URLs
const char* bible_references_default[POCET_JAZYKOV + 1] =
{
	"https://dkc.kbs.sk/dkc.php?in=",
	"",
	"",
	"http://www.vatican.va/archive/bible/nova_vulgata/documents/",
	"",
	"",
	"http://www.szentiras.hu/SZIT/",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};


// bible.com version id codes; usage for web HTTP requests
// ToDo: to be moved as default to config file
const char* bible_version_id_default[POCET_JAZYKOV + 1] =
{ "163", "509", "463", "823", "", "509", "198", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ };

const char* bible_book_shortcut_jazyk[BIBLE_BOOKS_COUNT + 1][POCET_JAZYKOV + 1] =
{
	{ /*BIBLE_BOOK_OT_Gen */ "Gn", "Gn", "Gn", "Gn", "", "Gn", "Ter", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Exod */ "Ex", "Ex", "Ex", "Ex", "", "Ex", "Ex", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Lev */ "Lv", "Lv", "Lv", "Lv", "", "Lv", "Lev", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Num */ "Nm", "Nm", "Nm", "Nm", "", "Nm", "Szám", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Deut */ "Dt", "Dt", "Dt", "Dt", "", "Dt", "MTörv", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Josh */ "Joz", "Joz", "Joz", "Joz", "", "Joz", "Joz", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Judg */ "Sdc", "Sd", "Sdc", "Sdc", "", "Sd", "Bír", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Ruth */ "Rút", "Rt", "Rút", "Rút", "", "Rt", "Rut", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_1Sam */ "1Sam", "1Sam", "1Sam", "1Sam", "", "1Sam", "1Sám", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_2Sam */ "2Sam", "2Sam", "2Sam", "2Sam", "", "2Sam", "2Sám", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_1Kgs */ "1Kr", "1Kr", "1Kr", "1Kr", "", "1Kr", "1Kir", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_2Kgs */ "2Kr", "2Kr", "2Kr", "2Kr", "", "2Kr", "2Kir", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_1Chr */ "1Krn", "1Krn", "1Krn", "1Krn", "", "1Krn", "1Krón", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_2Chr */ "2Krn", "2Krn", "2Krn", "2Krn", "", "2Krn", "2Krón", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Ezra */ "Ezd", "Ezd", "Ezd", "Ezd", "", "Ezd", "Ezd", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Neh */ "Neh", "Neh", "Neh", "Neh", "", "Neh", "Neh", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Esth */ "Est", "Est", "Est", "Est", "", "Est", "Eszt", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Job */ "Jób", "Jób", "Jób", "Jób", "", "Jób", "Jób", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Ps */ "Ž", "Žl", "Ž", "Ž", "", "Žl", "Zsolt", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Prov */ "Prís", "Př", "Prís", "Prís", "", "Př", "Péld", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Eccl */ "Kaz", "Kaz", "Kaz", "Kaz", "", "Kaz", "Préd", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Song */ "Pies", "Pís", "Pies", "Pies", "", "Pís", "Én", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Isa */ "Iz", "Iz", "Iz", "Iz", "", "Iz", "Iz", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Jer */ "Jer", "Jer", "Jer", "Jer", "", "Jer", "Jer", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Lam */ "Nár", "Nář", "Nár", "Nár", "", "Nář", "Siral", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Ezek */ "Ez", "Ez", "Ez", "Ez", "", "Ez", "Ez", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Dan */ "Dan", "Dan", "Dan", "Dan", "", "Dan", "Dán", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Hos */ "Oz", "Oz", "Oz", "Oz", "", "Oz", "Oz", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Joel */ "Joel", "Jl", "Joel", "Joel", "", "Jl", "Joel", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Amos */ "Am", "Am", "Am", "Am", "", "Am", "Am", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Obad */ "Abd", "Abd", "Abd", "Abd", "", "Abd", "Abd", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Jonah */ "Jon", "Jon", "Jon", "Jon", "", "Jon", "Jon", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Mic */ "Mich", "Mich", "Mich", "Mich", "", "Mich", "Mik", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Nah */ "Nah", "Nah", "Nah", "Nah", "", "Nah", "Nah", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Hab */ "Hab", "Hab", "Hab", "Hab", "", "Hab", "Hab", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Zeph */ "Sof", "Sof", "Sof", "Sof", "", "Sof", "Sof", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Hag */ "Ag", "Ag", "Ag", "Ag", "", "Ag", "Ag", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Zech */ "Zach", "Zach", "Zach", "Zach", "", "Zach", "Zak", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_OT_Mal */ "Mal", "Mal", "Mal", "Mal", "", "Mal", "Mal", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_Matt */ "Mt", "Mt", "Mt", "Mt", "", "Mt", "Mt", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_Mark */ "Mk", "Mk", "Mk", "Mk", "", "Mk", "Mk", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_Luke */ "Lk", "Lk", "Lk", "Lk", "", "Lk", "Lk", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_John */ "Jn", "Jan", "Jn", "Jn", "", "Jan", "Jn", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_Acts */ "Sk", "Sk", "Sk", "Sk", "", "Sk", "ApCsel", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_Rom */ "Rim", "Řím", "Rim", "Rim", "", "Řím", "Róm", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_1Cor */ "1Kor", "1Kor", "1Kor", "1Kor", "", "1Kor", "1Kor", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_2Cor */ "2Kor", "2Kor", "2Kor", "2Kor", "", "2Kor", "2Kor", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_Gal */ "Gal", "Gal", "Gal", "Gal", "", "Gal", "Gal", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_Eph */ "Ef", "Ef", "Ef", "Ef", "", "Ef", "Ef", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_Phil */ "Flp", "Flp", "Flp", "Flp", "", "Flp", "Fil", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_Col */ "Kol", "Kol", "Kol", "Kol", "", "Kol", "Kol", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_1Thess */ "1Sol", "1Sol", "1Sol", "1Sol", "", "1Sol", "1Tessz", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_2Thess */ "2Sol", "2Sol", "2Sol", "2Sol", "", "2Sol", "2Tessz", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_1Tim */ "1Tim", "1Tim", "1Tim", "1Tim", "", "1Tim", "1Tim", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_2Tim */ "2Tim", "2Tim", "2Tim", "2Tim", "", "2Tim", "2Tim", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_Titus */ "Tít", "Tit", "Tít", "Tít", "", "Tit", "Tít", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_Phlm */ "Flm", "Flm", "Flm", "Flm", "", "Flm", "Flm", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_Heb */ "Hebr", "Žid", "Hebr", "Hebr", "", "Žid", "Zsid", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_Jas */ "Jak", "Jak", "Jak", "Jak", "", "Jak", "Jak", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_1Pet */ "1Pt", "1Petr", "1Pt", "1Pt", "", "1Petr", "1Pét", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_2Pet */ "2Pt", "2Petr", "2Pt", "2Pt", "", "2Petr", "2Pét", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_1John */ "1Jn", "1Jan", "1Jn", "1Jn", "", "1Jan", "1Jn", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_2John */ "2Jn", "2Jan", "2Jn", "2Jn", "", "2Jan", "2Jn", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_3John */ "3Jn", "3Jan", "3Jn", "3Jn", "", "3Jan", "3Jn", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_Jude */ "Júd", "Júd", "Júd", "Júd", "", "Júd", "Júd", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_NT_Rev */ "Zjv", "Zj", "Zjv", "Zjv", "", "Zj", "Jel", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_DC_Tob */ "Tob", "Tob", "Tob", "Tob", "", "Tob", "Tób", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_DC_Jdt */ "Jdt", "Jdt", "Jdt", "Jdt", "", "Jdt", "Jdt", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_DC_Wis */ "Múd", "Mdr", "Múd", "Múd", "", "Mdr", "Bölcs", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_DC_Sir */ "Sir", "Sir", "Sir", "Sir", "", "Sir", "Sir", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_DC_Bar */ "Bar ", "Bar ", "Bar ", "Bar ", "", "Bar ", "Bar ", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_DC_1Macc */ "1Mach", "1Mak", "1Mach", "1Mach", "", "1Mak", "1Mak", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
	,{ /*BIBLE_BOOK_DC_2Macc */ "2Mach", "2Mak", "2Mach", "2Mach", "", "2Mak", "2Mak", "ru_text", "by_text", "is_text", /* STRING_1_FOR_NEW_LANGUAGE */ }
};

#define		bible_book_shortcut(a)	bible_book_shortcut_jazyk[a][_global_jazyk]


#endif // __BIBLE_H_


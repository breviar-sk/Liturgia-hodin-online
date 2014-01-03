/***************************************************************/
/*                                                             */
/* mysysdef.h                                                  */
/* (c)1999-2014 | Juraj Vidéky | videky@breviar.sk             */
/*                                                             */
/* obsahuje definície pre jednotlivé systémy                   */
/*                                                             */
/***************************************************************/
#include "vstudio.h"
#include "mysystem.h"

#ifndef __MYSYSDEF_H_
#define __MYSYSDEF_H_

#undef USE_UNCGI

/***************************************************************/
/*                                                             */
/* mysystem.h -> mysysdef.h                                    */
/* (c)1999-2014 | Juraj Vidéky | videky@breviar.sk             */
/*                                                             */
/* description | obsahuje jediny #define, urcujuci, v akom     */
/*               systeme program pracuje; ovplyvnuje tvorbu    */
/*               linkov, DEBUG #define, veci pre loggovanie a  */
/*               export                                        */
/* document history                                            */
/*   02/11/1999A.D. | created                                  */
/*   24/02/2000A.D. | prekopane                                */
/*   30/03/2000A.D. | pridane OS_Windows, MODEL_DEBUG_Windows, */
/*                    MODEL_Windows                            */
/*   06/09/2001A.D. | tento popis                              */
/*   2004-03-17a.D. | poznamka k OS_...                        */
/*   2005-03-22a.D. | zrusene DOS, vytvoreny novy model        */
/*   2005-03-28a.D. | pridane na zaciatok #undef pre vsetky    */
/*   2006-01-28a.D. | pridané define pre spôsob exportu        */
/*   2006-07-11a.D. | prvé kroky k jazykovým mutáciám          */
/*   2007-05-25a.D. | pridané MODEL_Windows_RUBY               */
/*   2007-06-01a.D. | vèlenený "config.h" pre confuse          */
/*   2007-06-19a.D. | odstránený "config.h" pre confuse        */
/*   2007-06-28a.D. | oprava jednotlivých modelov, popisy      */
/*   2007-11-20a.D. | doplnené EXPORT_HTML_SPECIALS            */
/*   2008-05-19a.D. | EXPORT_HTML_FILENAME_ANCHOR aj pre linux */
/*   2008-08-08a.D. | doplnené EXPORT_CMDLINE_CSS              */
/*   2009-08-26a.D. | pred popis predsunuté samotné nastavenie */
/*   2011-07-13a.D. | pôvodný mysystem.h rozdelený na 2 súbory */
/*                                                             */
/***************************************************************/

/*
 * Poznámka: Pri buildovaní nezabudni zmeni datum v mybuild.h (BUILD_DATE).
 *
 * Popis jednotlivých modelov (JUV, 2007-06-28):
 *
 * MODEL_linux - takto to vyzerá na internete (www.breviar.sk): 
 *		- žiadne logovanie, export do stdout, systém linux
 *		- debug verzia (s výpismi na stdout do HTML súboru ako poznámky): MODEL_DEBUG_linux
 *
 * MODEL_android - verzia pre android. Ako MODEL_linux, ale s pouzitim IO
 *                 wrappera pre android.
 *
 * MODEL_linux_commandline - off-line command-line verzia pre linux: 
 *		- žiadne logovanie, export do súboru, systém linux 
 *		  (použitie pre off-line ruèné generovanie HTML stránok, 
 *		  napr. aj pre batch mód - dávkové generovanie ve¾a stránok na súvislé obdobie)
 *		- debug verzia (s výpismi do samostatného súboru): MODEL_DEBUG_linux_commandline
 *
 * MODEL_Windows_RUBY - off-line verzia pre Windows s použitím Ruby webservera: 
 *		- žiadne logovanie, export do stdout, systém Windows
 *		// 2007-05-24: pridané; používame pre Windows/ruby
 *		- debug verzia (s výpismi na stdout do HTML súboru ako poznámky): MODEL_DEBUG_Windows_RUBY
 *
 * MODEL_Windows_commandline - off-line command-line verzia pre Windows: 
 *		- žiadne logovanie, export do súboru, systém Windows 
 *		  (použitie pre off-line ruèné generovanie HTML stránok, 
 *		  napr. aj pre batch mód - dávkové generovanie ve¾a stránok na súvislé obdobie)
 *		- debug verzia (s výpismi do samostatného súboru): MODEL_DEBUG_Windows_commandline
 *
 * 2 základné druhy správania aplikácie (JUV, 2010-06-07):
 *
 * BEHAVIOUR_WEB -- správanie ako na webe: export príp. logovanie ide na STDOUT (t. j. ako output pre web browser)
 * BEHAVIOUR_CMDLINE -- správanie pre command-line verziu: export príp. logovanie ide do súboru/súborov (t. j. ako output pre batch mód)
 *
 */

// OS_...    - uz ani nie su potrebne (kedysi pre cesty)
// MODEL_... - model kompilacie

// ---------------------------------------------------------------------
// prerobene 23/02/2000A.D. -- 24/02/2000A.D.
// 2006-01-28: pridané define pre spôsob výpisu kotiev a názvov súborov do HTML výsledku
#undef EXPORT_HTML_FILENAME_ANCHOR
#undef EXPORT_HTML_FILENAME
#undef EXPORT_HTML_ANCHOR
#undef EXPORT_HTML_SPECIALS // 2007-11-20: vytvorené, kvôli výpisom do výsledného HTML vo funkcii interpretParameter(), napr. "nie je velkonocne obdobie"
#undef EXPORT_CMDLINE_CSS // 2008-08-08: doplnené kvôli tomu, èi exportova v hlavièke /breviar.css alebo ./breviar.css

#undef BEHAVIOUR_WEB // 2010-06-07: správanie ako na webe: export príp. logovanie ide na STDOUT (t. j. ako output pre web browser)
#undef BEHAVIOUR_CMDLINE // 2010-06-07: správanie pre command-line verziu: export príp. logovanie ide do súboru/súborov (t. j. ako output pre batch mód)
#undef IO_ANDROID
#undef LITURGICKE_CITANIA_ANDROID

// ostry linux:
#if defined(MODEL_linux)
	#define BEHAVIOUR_WEB
	#define OS_linux
	#undef LOGGING
	#define EXPORT_HTML_FILENAME_ANCHOR
	#define EXPORT_TO_STDOUT
// pomocne funkcie pre liturgicke citania:
#elif defined(MODEL_linux_citania)
	#define BEHAVIOUR_WEB
	#define OS_linux
	#undef LOGGING
	#define EXPORT_HTML_FILENAME_ANCHOR
	#define EXPORT_TO_STRING
	#define LITURGICKE_CITANIA_ANDROID
// android:
#elif defined(MODEL_android)
	#define BEHAVIOUR_WEB
	#define OS_linux
	#undef LOGGING
	#define EXPORT_HTML_FILENAME_ANCHOR
	#define EXPORT_TO_FILE
	#define IO_ANDROID
	#define LITURGICKE_CITANIA_ANDROID
// android + debug log:
#elif defined(MODEL_android_debug)
	#define BEHAVIOUR_WEB
	#define OS_linux
	#define LOGGING
	#define LOG_TO_ANDROID
	#define EXPORT_HTML_FILENAME_ANCHOR
	#define EXPORT_TO_FILE
	#define IO_ANDROID
	#define LITURGICKE_CITANIA_ANDROID
// ostré Windows/RUBY:
#elif defined(MODEL_Windows_RUBY)
	#define BEHAVIOUR_WEB
	#define OS_Windows_Ruby
	#undef LOGGING
	#define EXPORT_HTML_FILENAME_ANCHOR
	#define EXPORT_HTML_SPECIALS
	#define EXPORT_TO_STDOUT
// debugovanie Windows/RUBY -- vsetko sa vypisuje na stdout
#elif defined(MODEL_DEBUG_Windows_RUBY)
	#define BEHAVIOUR_WEB
	#define OS_Windows_Ruby
	#define LOGGING
	#define LOG_TO_STDOUT
	#define EXPORT_HTML_FILENAME_ANCHOR
	#define EXPORT_HTML_SPECIALS
	#define EXPORT_TO_STDOUT
	#define DEBUG
// debugovanie linux -- vsetko sa vypisuje na stdout
#elif defined(MODEL_DEBUG_linux)
	#define BEHAVIOUR_WEB
	#define OS_linux
	#define LOGGING
	#define LOG_TO_STDOUT
	#define EXPORT_HTML_FILENAME_ANCHOR
	#define EXPORT_HTML_SPECIALS
	#define EXPORT_TO_STDOUT
	#define DEBUG
// ostry Windows (command-line verzia):
#elif defined(MODEL_Windows_commandline)
	#define BEHAVIOUR_CMDLINE
	#define OS_Windows
	#undef LOGGING
	#define EXPORT_TO_FILE
	#define EXPORT_CMDLINE_CSS
// debugovanie Windows/command-line -- vsetko sa loguje do suboru
#elif defined(MODEL_DEBUG_Windows_commandline)
	#define BEHAVIOUR_CMDLINE
	#define OS_Windows
	#define LOGGING
	#define LOG_TO_FILE
	#define EXPORT_HTML_FILENAME_ANCHOR
	#define EXPORT_HTML_SPECIALS
	#define EXPORT_TO_FILE
	#define EXPORT_CMDLINE_CSS
// ostry linux (command-line verzia):
#elif defined(MODEL_linux_commandline)
	#define BEHAVIOUR_CMDLINE
	#define OS_linux
	#undef LOGGING
	#define EXPORT_TO_FILE
	#define EXPORT_CMDLINE_CSS
// debugovanie linux/command-line -- vsetko sa loguje do suboru
#elif defined(MODEL_DEBUG_linux_commandline)
	#define BEHAVIOUR_CMDLINE
	#define OS_linux
	#define LOGGING
	#define LOG_TO_FILE
	#define EXPORT_HTML_FILENAME_ANCHOR
	#define EXPORT_HTML_SPECIALS
	#define EXPORT_TO_FILE
	#define EXPORT_CMDLINE_CSS
#elif defined(MODEL_linux_strexport)
	#define BEHAVIOUR_WEB
	#define OS_linux
	#undef LOGGING
	#define EXPORT_HTML_FILENAME_ANCHOR
	#define EXPORT_TO_STRING
#else
	#error Unsupported system model (see mysystem.h) - Nepodporovaný systémový model (pozri súbor mysystem.h)
#endif

// 2010-06-07: doplnené pod¾a direktívy Visual Studia (vlastne tak trocha prepisuje vyššie uvedené)
#ifdef _DEBUG
	#define DEBUG
	#define LOGGING
	#ifdef BEHAVIOUR_WEB
		#define LOG_TO_STDOUT
		#define EXPORT_TO_STDOUT
	#elif defined (BEHAVIOUR_CMDLINE)
		#define LOG_TO_FILE
		#define EXPORT_TO_FILE
	#endif
	#define EXPORT_HTML_FILENAME_ANCHOR
	#define EXPORT_HTML_SPECIALS
/*
#else
	#undef DEBUG
	#undef LOGGING
	#undef LOG_TO_STDOUT
	#undef LOG_TO_FILE
*/
#endif

#ifdef LOG_TO_EXPORT
	#define Log Export
#else
	#define Log __Log
#endif

// v DOSe
#ifdef OS_DOS
	#define DEFINED_strcmpi
#endif

// 2006-07-17: Pridané/
#define		PATH_SEPARATOR_linux	'/'
#define		PATH_SEPARATOR_Windows	'\\'
// 2008-08-08: Pridané
#define		STR_PATH_SEPARATOR_linux	"/"
#define		STR_PATH_SEPARATOR_Windows	"\\"
// 2009-08-03: pridané pre HTML súbory
#define		STR_PATH_SEPARATOR_HTML	STR_PATH_SEPARATOR_linux

#define		SYSTEM_RUBY    0
#define		SYSTEM_LINUX   1
#define		SYSTEM_WINDOWS 2

// 2007-05-29: upravené; pre Ruby on Windows tiež separátor ako pod linuxom
// 2011-05-16: pri debugovaní Ruby on Windows treba backslashe
// 2011-08-12: pri debugovaní Ruby on Windows treba backslashe -> naèo? zapoznámkované!
#if defined(OS_linux)
	#define		PATH_SEPARATOR	PATH_SEPARATOR_linux
	#define		STR_PATH_SEPARATOR	STR_PATH_SEPARATOR_linux
//#elif defined(OS_Windows_Ruby) && defined(DEBUG)
//	#define		PATH_SEPARATOR	PATH_SEPARATOR_Windows
//	#define		STR_PATH_SEPARATOR	STR_PATH_SEPARATOR_Windows
#elif defined(OS_Windows_Ruby)
	#define		PATH_SEPARATOR	PATH_SEPARATOR_linux
	#define		STR_PATH_SEPARATOR	STR_PATH_SEPARATOR_linux
#else
	#define		PATH_SEPARATOR	PATH_SEPARATOR_Windows
	#define		STR_PATH_SEPARATOR	STR_PATH_SEPARATOR_Windows
#endif

// 2006-07-31: Pridané
#define		UNDERSCORE	'_'

// 2006-07-31: kvôli jazykovým mutáciám; zmenené 2008-08-15 na 5 
// 2009-01-29: zmenené na 6 (maïarèina)
// 2011-04-13: presunuté sem spolu s POCET_GLOBAL_OPT aj MAX_STR, GLOBAL_OPTION_NULL
#define	POCET_JAZYKOV	     6
#define POCET_GLOBAL_OPT     6
#define MAX_STR            300 // maximalna dlzka retazca
#define GLOBAL_OPTION_NULL  -1 // neurèená hodnota pre global option


#endif // __MYSYSDEF_H_

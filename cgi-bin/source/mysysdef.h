/***************************************************************/
/*                                                             */
/* mysysdef.h                                                  */
/* (c)1999-2015 | Juraj Vidéky | videky@breviar.sk             */
/*                                                             */
/* description | contains #defines for various systems         */
/*                                                             */
/***************************************************************/
#include "vstudio.h"
#include "mysystem.h"

#ifndef __MYSYSDEF_H_
#define __MYSYSDEF_H_

#undef USE_UNCGI

/*
 * NOTE: Do not forget to change date of biuld in mybuild.h (BUILD_DATE).
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
 *		  (použitie pre off-line ručné generovanie HTML stránok, 
 *		  napr. aj pre batch mód - dávkové generovanie veľa stránok na súvislé obdobie)
 *		- debug verzia (s výpismi do samostatného súboru): MODEL_DEBUG_linux_commandline
 *
 * MODEL_Windows_RUBY - off-line verzia pre Windows s použitím Ruby webservera: 
 *		- žiadne logovanie, export do stdout, systém Windows
 *		// 2007-05-24: pridané; používame pre Windows/ruby
 *		- debug verzia (s výpismi na stdout do HTML súboru ako poznámky): MODEL_DEBUG_Windows_RUBY
 *
 * MODEL_Windows_commandline - off-line command-line verzia pre Windows: 
 *		- žiadne logovanie, export do súboru, systém Windows 
 *		  (použitie pre off-line ručné generovanie HTML stránok, 
 *		  napr. aj pre batch mód - dávkové generovanie veľa stránok na súvislé obdobie)
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
#undef EXPORT_CMDLINE_CSS // 2008-08-08: doplnené kvôli tomu, či exportovať v hlavičke /breviar.css alebo ./breviar.css

#undef BEHAVIOUR_WEB // 2010-06-07: správanie ako na webe: export príp. logovanie ide na STDOUT (t. j. ako output pre web browser)
#undef BEHAVIOUR_CMDLINE // 2010-06-07: správanie pre command-line verziu: export príp. logovanie ide do súboru/súborov (t. j. ako output pre batch mód)
#undef IO_ANDROID
#undef LITURGICKE_CITANIA_ANDROID

// production linux:
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
	#define LIBC_BIONIC
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
	#define LIBC_BIONIC
	#define DEBUG
// production Windows/RUBY:
#elif defined(MODEL_Windows_RUBY)
	#define BEHAVIOUR_WEB
	#define OS_Windows_Ruby
	#undef LOGGING
	#define EXPORT_HTML_FILENAME_ANCHOR
	#define EXPORT_HTML_SPECIALS
	#define EXPORT_TO_STDOUT
// debugging in Windows/RUBY -- all output is sent to stdout
#elif defined(MODEL_DEBUG_Windows_RUBY)
	#define BEHAVIOUR_WEB
	#define OS_Windows_Ruby
	#define LOGGING
	#define LOG_TO_STDOUT
	#define EXPORT_HTML_FILENAME_ANCHOR
	#define EXPORT_HTML_SPECIALS
	#define EXPORT_TO_STDOUT
	#define DEBUG
// debugging in linux -- all output is sent to stdout
#elif defined(MODEL_DEBUG_linux)
	#define BEHAVIOUR_WEB
	#define OS_linux
	#define LOGGING
	#define LOG_TO_STDOUT
	#define EXPORT_HTML_FILENAME_ANCHOR
	#define EXPORT_HTML_SPECIALS
	#define EXPORT_TO_STDOUT
	#define DEBUG
// production Windows (command-line version):
#elif defined(MODEL_Windows_commandline)
	#define BEHAVIOUR_CMDLINE
	#define OS_Windows
	#undef LOGGING
	#define EXPORT_TO_FILE
	#define EXPORT_CMDLINE_CSS
// debugging in Windows/command-line -- all output is written into log file
#elif defined(MODEL_DEBUG_Windows_commandline)
	#define BEHAVIOUR_CMDLINE
	#define OS_Windows
	#define LOGGING
	#define LOG_TO_FILE
	#define EXPORT_HTML_FILENAME_ANCHOR
	#define EXPORT_HTML_SPECIALS
	#define EXPORT_TO_FILE
	#define EXPORT_CMDLINE_CSS
// production linux (command-line version):
#elif defined(MODEL_linux_commandline)
	#define BEHAVIOUR_CMDLINE
	#define OS_linux
	#undef LOGGING
	#define EXPORT_TO_FILE
	#define EXPORT_CMDLINE_CSS
// debugging in linux/command-line -- all output is written into log file
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

// added according to Visual Studio directive (overrides some previous settings)
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
#endif

#ifdef LOG_TO_EXPORT
	#define Log Export
#else
	#define Log __Log
#endif

// under MS DOS
#ifdef OS_DOS
	#define DEFINED_strcmpi
#endif

#define		PATH_SEPARATOR_linux	'/'
#define		PATH_SEPARATOR_Windows	'\\'

#define		STR_PATH_SEPARATOR_linux	"/"
#define		STR_PATH_SEPARATOR_Windows	"\\"

#define		STR_PATH_SEPARATOR_HTML	STR_PATH_SEPARATOR_linux

#define		SYSTEM_RUBY    0
#define		SYSTEM_LINUX   1
#define		SYSTEM_WINDOWS 2

#if defined(OS_linux)
	#define		PATH_SEPARATOR	PATH_SEPARATOR_linux
	#define		STR_PATH_SEPARATOR	STR_PATH_SEPARATOR_linux
#elif defined(OS_Windows_Ruby)
	#define		PATH_SEPARATOR	PATH_SEPARATOR_linux
	#define		STR_PATH_SEPARATOR	STR_PATH_SEPARATOR_linux
#else
	#define		PATH_SEPARATOR	PATH_SEPARATOR_Windows
	#define		STR_PATH_SEPARATOR	STR_PATH_SEPARATOR_Windows
#endif

#define		UNDERSCORE	'_'

// number of supported rites (roman catholic, greek catholic, etc.)
#define	POCET_RITOV	         1

// number of supported languages | Warning: for all string constants we use arrays [POCET_JAZYKOV + 1] => be careful when incrementing POCET_JAZYKOV!
/* INCREMENT_FOR_NEW_LANGUAGE */
#define	POCET_JAZYKOV	     7

// when adding new language, the following comments MUST BE replaced:
// 
// 1. few numeric constants [ADD_VALUE_FOR_NEW_LANGUAGE]
// 2. string constants in one line [STRING_1_FOR_NEW_LANGUAGE]
// 3. string constants in separate line ('multi-line alignment' in source code) []
// 4. string arrays [STRING_ARRAY_FOR_NEW_LANGUAGE]
// 5. consider adding new calendar -> see [INCREMENT_FOR_NEW_CALENDAR]
//
// Detailed description:
//
// 1. change the following: ADD_VALUE_FOR_NEW_LANGUAGE
// -- especially set constants: skratka_jazyka[], cfg_option_postfix[], postfix_jazyka[], skratka_kalendara[] (see [INCREMENT_FOR_NEW_CALENDAR])
//
// 2. replace string constants in one line: STRING_1_FOR_NEW_LANGUAGE
//
// , /* STRING_1_FOR_NEW_LANGUAGE */ -> , "string_for_new_language", /* STRING_1_FOR_NEW_LANGUAGE */
//
// Note: always preserve ", "ru_text", /* STRING_1_FOR_NEW_LANGUAGE */" with preceding comma!
//
// 3. replace string constants in multi-line constants: STRING_2_FOR_NEW_LANGUAGE
// 
// /* STRING_2_FOR_NEW_LANGUAGE */ -> (replace with the following two lines)
// "string_for_new_language", 
// /* STRING_2_FOR_NEW_LANGUAGE */
//
// 4. string arrays: STRING_ARRAY_FOR_NEW_LANGUAGE to be replaced manually

#define POCET_GLOBAL_OPT     6
#define MAX_STR            300 // max string length
#define GLOBAL_OPTION_NULL  -1 // undefined value for global option

#endif // __MYSYSDEF_H_

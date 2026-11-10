/******************************************************************/
/*                                                                */
/* bible.h                                                        */
/* (c)2017-2026 | Juraj Vidéky                                    */
/*                                                                */
/* description | utilities for biblical readings                  */
/*                                                                */
/******************************************************************/

#ifndef __BIBLE_H_
#define __BIBLE_H_

#include "mydefs.h"

// default Bible online translation URLs
const char* bible_references_default[POCET_JAZYKOV + 1] =
{
	"https://dkc.kbs.sk/dkc.php?in=",
	"",
	"",
	"https://www.vatican.va/archive/bible/nova_vulgata/documents/",
	"",
	"",
	"https://szentiras.hu/szit/",
	"",
	"",
	"",
	"",
	"",
	/* STRING_2_FOR_NEW_LANGUAGE */
};


// bible.com version id codes; usage for web HTTP requests
// ToDo: to be moved as default to config file
const char* bible_version_id_default[POCET_JAZYKOV + 1] =
{ "163", "509", "463", "823", "", "509", "198", "ru_text", "by_text", "is_text", "es_text", "az_text", /* STRING_1_FOR_NEW_LANGUAGE */ };

#endif // __BIBLE_H_

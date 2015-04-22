/************************************************************/
/*                                                          */
/* liturgia.cpp                                             */
/* (c)1999-2015 | Juraj Vidéky | videky@breviar.sk          */
/*                                                          */
/* description | basic 'liturgical' methods for calendar,   */
/*               working with dates and strings             */
/*                                                          */
/************************************************************/

#include "vstudio.h"

#ifndef __LITURGIA_CPP_
#define __LITURGIA_CPP_

#include "liturgia.h"
#include "breviar.h"

#include "mylog.h"
#include "myexpt.h"
#include "mydefs.h"
#include "mysystem.h"
#include "mysysdef.h"
#include "mystring.h"
#include "utf8-utils.h"
#include <ctype.h>
#include <wctype.h>

//---------------------------------------------------------------------
short int _allocate_global_var(void){
	short int ret = SUCCESS;
	Log("Allocating memory...\n");

	// _global_den_ptr
	if ((_global_den_ptr = (_struct_dm*)malloc(sizeof(_struct_dm))) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_den_ptr'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_den_ptr'\n", sizeof(_struct_dm));
		_INIT_DM(_global_den);
	}

	// _global_result_ptr
	if ((_global_result_ptr = (_struct_dm*)malloc(sizeof(_struct_dm))) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_result_ptr'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_result_ptr'\n", sizeof(_struct_dm));
		_INIT_DM(_global_result);
	}

	// _global_pm_sobota_ptr
	if ((_global_pm_sobota_ptr = (_struct_dm*)malloc(sizeof(_struct_dm))) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_pm_sobota_ptr'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_pm_sobota_ptr'\n", sizeof(_struct_dm));
		_INIT_DM(_global_pm_sobota);
	}

	for (short int i = 0; i < MAX_POCET_SVATY; i++){
		// _global_svaty(i)_ptr
		if ((_global_svaty_ptr[i] = (_struct_dm*)malloc(sizeof(_struct_dm))) == NULL){
			Log("  Not enough memory to allocate buffer for `_global_svaty_ptr[%d]'\n", i);
			ret = FAILURE;
		}
		else{
			Log("  %d bytes for `_global_svaty_ptr[%d]'\n", sizeof(_struct_dm), i);
			_INIT_DM((_global_svaty(i + 1)));
		}
	}

	// _global_modl_prve_vespery_ptr
	if ((_global_modl_prve_vespery_ptr = (_type_1vespery*)malloc(sizeof(_type_1vespery))) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_modl_prve_vespery_ptr'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_modl_prve_vespery_ptr'\n", sizeof(_type_1vespery));
		_INIT_TMODLITBA1(_global_modl_prve_vespery);
	}

	// _global_modl_1kompletorium_ptr
	if ((_global_modl_1kompletorium_ptr = (_type_1kompletorium*)malloc(sizeof(_type_1kompletorium))) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_modl_1kompletorium_ptr'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_modl_1kompletorium_ptr'\n", sizeof(_type_1kompletorium));
		_INIT_TMODLITBA3(_global_modl_prve_kompletorium);
	}

	// _global_modl_invitatorium_ptr
	if ((_global_modl_invitatorium_ptr = (_type_invitatorium*)malloc(sizeof(_type_invitatorium))) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_modl_invitatorium_ptr'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_modl_invitatorium_ptr'\n", sizeof(_type_invitatorium));
		_INIT_TMODLITBA4(_global_modl_invitatorium);
	}

	// _global_modl_ranne_chvaly_ptr
	if ((_global_modl_ranne_chvaly_ptr = (_type_ranne_chvaly*)malloc(sizeof(_type_ranne_chvaly))) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_modl_ranne_chvaly_ptr'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_modl_ranne_chvaly_ptr'\n", sizeof(_type_ranne_chvaly));
		_INIT_TMODLITBA1(_global_modl_ranne_chvaly);
	}

	// _global_modl_posv_citanie_ptr
	if ((_global_modl_posv_citanie_ptr = (_type_posv_citanie*)malloc(sizeof(_type_posv_citanie))) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_modl_posv_citanie_ptr'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_modl_posv_citanie_ptr'\n", sizeof(_type_posv_citanie));
		_INIT_TMODLITBA5(_global_modl_posv_citanie);
	}

	// _global_modl_cez_den_9_ptr
	if ((_global_modl_cez_den_9_ptr = (_type_cez_den_9*)malloc(sizeof(_type_cez_den_9))) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_modl_cez_den_9_ptr'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_modl_cez_den_9_ptr'\n", sizeof(_type_cez_den_9));
		_INIT_TMODLITBA2(_global_modl_cez_den_9);
	}

	// _global_modl_cez_den_12_ptr
	if ((_global_modl_cez_den_12_ptr = (_type_cez_den_12*)malloc(sizeof(_type_cez_den_12))) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_modl_cez_den_12_ptr'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_modl_cez_den_12_ptr'\n", sizeof(_type_cez_den_12));
		_INIT_TMODLITBA2(_global_modl_cez_den_12);
	}

	// _global_modl_cez_den_3_ptr
	if ((_global_modl_cez_den_3_ptr = (_type_cez_den_3*)malloc(sizeof(_type_cez_den_3))) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_modl_cez_den_3_ptr'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_modl_cez_den_3_ptr'\n", sizeof(_type_cez_den_3));
		_INIT_TMODLITBA2(_global_modl_cez_den_3);
	}

	// _global_modl_vespery_ptr
	if ((_global_modl_vespery_ptr = (_type_vespery*)malloc(sizeof(_type_vespery))) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_modl_vespery_ptr'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_modl_vespery_ptr'\n", sizeof(_type_vespery));
		_INIT_TMODLITBA1(_global_modl_vespery);
	}

	// _global_modl_kompletorium_ptr
	if ((_global_modl_kompletorium_ptr = (_type_kompletorium*)malloc(sizeof(_type_kompletorium))) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_modl_kompletorium_ptr'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_modl_kompletorium_ptr'\n", sizeof(_type_kompletorium));
		_INIT_TMODLITBA3(_global_modl_kompletorium);
	}

	// _global_include_static_text_ptr
	if ((_global_include_static_text_ptr = (_struct_anchor_and_file*)malloc(sizeof(_struct_anchor_and_file))) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_include_static_text_ptr'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_include_static_text_ptr'\n", sizeof(_struct_anchor_and_file));
		_INIT_ANCHOR_AND_FILE(_global_include_static_text);
	}

	// _global_r_ptr
	if ((_global_r_ptr = (_struct_lrok*)malloc(sizeof(_struct_lrok))) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_r_ptr'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_r_ptr'\n", sizeof(_struct_lrok));
	}

	// _global_link_ptr
	if ((_global_link_ptr = (char*)malloc(MAX_GLOBAL_LINK)) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_link_ptr'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_link_ptr'\n", MAX_GLOBAL_LINK);
		mystrcpy(_global_link_ptr, STR_UNDEF, MAX_GLOBAL_LINK);
	}

	// _global_pom_str
	if ((_global_pom_str = (char*)malloc(MAX_STR)) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_pom_str'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_pom_str'\n", MAX_STR);
		mystrcpy(_global_pom_str, STR_UNDEF, MAX_STR);
	}

	// _global_string
	if ((_global_string = (char*)malloc(MAX_GLOBAL_STR)) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_string'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_string'\n", MAX_GLOBAL_STR);
		mystrcpy(_global_string, STR_UNDEF, MAX_GLOBAL_STR);
	}

	// _global_string2
	if ((_global_string2 = (char*)malloc(MAX_GLOBAL_STR2)) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_string2'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_string2'\n", MAX_GLOBAL_STR2);
		mystrcpy(_global_string2, STR_EMPTY, MAX_GLOBAL_STR2);
	}

	// _global_string_farba
	if ((_global_string_farba = (char*)malloc(MAX_GLOBAL_STR_FARBA)) == NULL){
		Log("  Not enough memory to allocate buffer for `_global_string_farba'\n");
		ret = FAILURE;
	}
	else{
		Log("  %d bytes for `_global_string_farba'\n", MAX_GLOBAL_STR_FARBA);
		mystrcpy(_global_string_farba, STR_EMPTY, MAX_GLOBAL_STR_FARBA);
	}

	Log("...done.\n");
	return ret;
}

short int _deallocate_global_var(void){
	Log("Deallocating memory...\n");

	Log("_global_den_ptr\n"); free(_global_den_ptr);
	Log("_global_result_ptr\n"); free(_global_result_ptr);
	Log("_global_pm_sobota_ptr\n"); free(_global_pm_sobota_ptr);
	for (short int i = 0; i < MAX_POCET_SVATY; i++){
		Log("_global_svaty_ptr[%d]\n", i); free(_global_svaty_ptr[i]);
	}
	Log("_global_modl_prve_vespery_ptr\n"); free(_global_modl_prve_vespery_ptr);
	Log("_global_modl_1kompletorium_ptr\n"); free(_global_modl_1kompletorium_ptr);
	Log("_global_modl_invitatorium_ptr\n"); free(_global_modl_invitatorium_ptr);
	Log("_global_modl_ranne_chvaly_ptr\n"); free(_global_modl_ranne_chvaly_ptr);
	Log("_global_modl_posv_citanie_ptr\n"); free(_global_modl_posv_citanie_ptr);
	Log("_global_modl_cez_den_9_ptr\n"); free(_global_modl_cez_den_9_ptr);
	Log("_global_modl_cez_den_12_ptr\n"); free(_global_modl_cez_den_12_ptr);
	Log("_global_modl_cez_den_3_ptr\n"); free(_global_modl_cez_den_3_ptr);
	Log("_global_modl_vespery_ptr\n"); free(_global_modl_vespery_ptr);
	Log("_global_modl_kompletorium_ptr\n"); free(_global_modl_kompletorium_ptr);
	Log("_global_r_ptr\n"); free(_global_r_ptr);

	Log("_global_link_ptr\n"); free(_global_link_ptr);
	Log("_global_pom_str\n"); free(_global_pom_str);
	Log("_global_string\n"); free(_global_string);
	Log("_global_string2\n"); free(_global_string2);
	Log("_global_string_farba\n"); free(_global_string_farba); // pridané 2006-08-19

	Log("...done.\n");
	return SUCCESS;
}// _deallocate_global_var()

//---------------------------------------------------------------------
// vezme retazec a porovna s nazvami mesiaca; ak najde, vrati, inak 0
short int cislo_mesiaca(char *mesiac){
	short int ret = 0;
	short int i;
	for (i = 0; i < 12; i++){
		if (equals(nazov_mesiaca(i), mesiac)){
			ret = i + 1;
		}
	}
	return ret;
}// cislo_mesiaca()

//---------------------------------------------------------------------
// urobi velke pismena 
// 2011-01-31: nesmie pritom v HTML stringoch upravovať kódové mená, napr. &mdash; na veľké písmená
// Assumes utf-8 encoding.
char *caps_BIG(const char* input) {
	short int ok = TRUE;
	const char* in = input;
	char* out = _global_pom_str;
	while (out - _global_pom_str < MAX_STR - 5 && *in) {
		int c = DecodeWchar(&in);
		if ((c == '&') && (ok == TRUE)){
			ok = FALSE;
		}
		if ((c == ';') && (ok == FALSE)){
			ok = TRUE;
		}
		// 2011-01-31: ToDo: ešte by bolo potrebné ošetriť aj to, že za & nenasleduje regulérny znak pre špeciálny HTML kód, t. j. niečo iné ako upper+lowercase ascii abeceda + # a číslice
		if (ok == TRUE){
			c = WcharToUppercase(c);
		}// ok == TRUE
		EncodeWchar(c, &out);
	}
	*out = 0;
	return (_global_pom_str);
}// caps_BIG()

//---------------------------------------------------------------------
// odstráni diakritiku
// 2011-04-05: nesmie pritom v HTML stringoch upravovať kódové mená, napr. &mdash;
// 2011-04-06: zmení aj dlhé pomlčky na obyčajný spojovník (znak mínus)
char *remove_diacritics(const char *input){
	short int ok = TRUE;
	const char* in = input;
	char* out = _global_pom_str;
	while (out - _global_pom_str < MAX_STR - 5 && *in) {
		int c = DecodeWchar(&in);
		if ((c == '&') && (ok == TRUE)){
			ok = FALSE;
		}
		if ((c == ';') && (ok == FALSE)){
			ok = TRUE;
		}
		// 2011-01-31: ToDo: ešte by bolo potrebné ošetriť aj to, že za & nenasleduje regulérny znak pre špeciálny HTML kód, t. j. niečo iné ako upper+lowercase ascii abeceda + # a číslice
		if (ok == TRUE) {
			c = RemoveDiacriticsFromWchar(c);
		}// ok == TRUE
		EncodeWchar(c, &out);
	}
	*out = 0;
	return (_global_pom_str);
}// remove_diacritics()

//---------------------------------------------------------------------
// konvertuje underscore na nezlomiteľné medzery
// (char sa musí najprv konvertovať na char * a až potom appendovať strcat)
char *convert_nonbreaking_spaces(const char *input){
	Log("convert_nonbreaking_spaces() -- začiatok...\n");
	const char* in = input;
	char* out = _global_pom_str;
	while (out - _global_pom_str < MAX_STR - 7 && *in) {
		int c = DecodeWchar(&in);
		if (c == CHAR_NONBREAKING_SPACE) {
			strcpy(out, HTML_NONBREAKING_SPACE);
			out += strlen(HTML_NONBREAKING_SPACE);
		}// c == CHAR_NONBREAKING_SPACE
		else {
			EncodeWchar(c, &out);
		}
	}
	*out = 0;
	Log("convert_nonbreaking_spaces() -- koniec, returning `%s'.\n", _global_pom_str);
	return (_global_pom_str);
}// convert_nonbreaking_spaces()

void prilep_request_options(char pom2[MAX_STR], char pom3[MAX_STR], short int force_opt /* default = PRILEP_REQUEST_OPTIONS_DEFAULT */){
	short int i;
	Log("prilep_request_options() -- začiatok...\n");

	// fix pre Android (nastavenie jazyka v menu vs. v HTML forme): vždy nastavovať (prilepovať) jazyk
#ifndef IO_ANDROID
	if (_global_jazyk != JAZYK_SK){
#endif
		sprintf(pom3, HTML_AMPERSAND"%s=%s", STR_JAZYK, skratka_jazyka[_global_jazyk]);
		strcat(pom2, pom3);
		Log("\tPrilepil som aj jazyk: `%s' (2006-07-31)\n", pom3);
#ifndef IO_ANDROID
	}
#endif

	if (PODMIENKA_EXPORTOVAT_KALENDAR){
		sprintf(pom3, HTML_AMPERSAND"%s=%s", STR_KALENDAR, skratka_kalendara[_global_kalendar]);
		strcat(pom2, pom3);
		Log("\tPrilepil som aj kalendár: `%s' (2010-08-04)\n", pom3);
	}
	else{
		Log("\tNetreba prilepiť kalendár (jazyk == %s, kalendár == %s)\n", skratka_jazyka[_global_jazyk], skratka_kalendara[_global_kalendar]);
	}

	if ((_global_css != CSS_breviar_sk) && (_global_css != CSS_UNDEF)){
		sprintf(pom3, HTML_AMPERSAND"%s=%s", STR_CSS, skratka_css[_global_css]);
		strcat(pom2, pom3);
		Log("\tPrilepil som aj css: `%s' (2008-08-08)\n", pom3);
	}

	if ((_global_font != FONT_CSS) && (_global_font != FONT_UNDEF)){
		sprintf(pom3, HTML_AMPERSAND"%s=%s", STR_FONT_NAME, nazov_fontu[_global_font]);
		strcat(pom2, pom3);
		Log("\tPrilepil som aj font: `%s'\n", pom3);
	}
	else{
		Log("\tNetreba prilepiť font (_global_font == %d, názov == %s)\n", _global_font, nazov_fontu[_global_font]);
	}

	if (PODMIENKA_EXPORTOVAT_FONTSIZE){
		sprintf(pom3, HTML_AMPERSAND"%s=%s", STR_FONT_SIZE, nazov_font_size_css[_global_font_size]);
		strcat(pom2, pom3);
		Log("\tPrilepil som aj font size: `%s'\n", pom3);
	}
	else{
		Log("\tNetreba prilepiť font size (_global_font_size == %d, názov == %s)\n", _global_font_size, nazov_font_size_css[_global_font_size]);
	}

	if (PODMIENKA_EXPORTOVAT_STYLE_MARGIN){
		sprintf(pom3, HTML_AMPERSAND"%s=%d", STR_STYLE_MARGIN, _global_style_margin);
		strcat(pom2, pom3);
		Log("\tPrilepil som aj style margin: `%s'\n", pom3);
	}
	else{
		Log("\tNetreba prilepiť style margin (_global_style_margin == %d)\n", _global_style_margin);
	}

	char local_str[SMALL];
	int local_opt_default;
	short int podmienka;
	for (i = 0; i < POCET_GLOBAL_OPT; i++){
		Log("i == %d...\n", i);
		local_opt_default = CFG_OPTION_DEFAULT(i);
#ifdef IO_ANDROID
		// Export all options in android, so that the UI can parse and
		// modify their values correctly.
		podmienka = 1;
#else
		if (force_opt != PRILEP_REQUEST_OPTIONS_LEN_FORCE){
			Log("_global_opt[%d] == %d; CFG_OPTION_DEFAULT(%d) == %d;\n", i, _global_opt[i], i, local_opt_default);
			podmienka = (_global_opt[i] != local_opt_default);
		}
		else{
			Log("_global_opt[%d] == %d; _global_optf[%d] == %d; CFG_OPTION_DEFAULT(%d) == %d;\n", i, _global_opt[i], i, _global_optf[i], i, local_opt_default);
			podmienka = (_global_optf[i] != local_opt_default);
		}
#endif
		if(podmienka){
			strcpy(local_str, STR_EMPTY);

			strcat_str_modl_opt_bit_order(local_str, i, USE_STR_MODL_OPT);

			sprintf(pom3, HTML_AMPERSAND"%s=%d", local_str, (force_opt != PRILEP_REQUEST_OPTIONS_LEN_FORCE) ? _global_opt[i] : _global_optf[i]);
			strcat(pom2, pom3);
			Log("\tPrilepil som aj opt%c %d: `%s'\n", (force_opt != PRILEP_REQUEST_OPTIONS_LEN_FORCE) ? CHAR_SPACE : 'f', i, pom3);
		}
	}// for i

	if (force_opt == PRILEP_REQUEST_OPTIONS_AJ_FORCE){
		Log("prilepujem aj force options...\n");
		for (i = 0; i < POCET_GLOBAL_OPT; i++){
			Log("i == %d...\n", i);
			local_opt_default = CFG_OPTION_DEFAULT(i);
			Log("_global_opt[%d] == %d; _global_optf[%d] == %d; CFG_OPTION_DEFAULT(%d) == %d;\n", i, _global_opt[i], i, _global_optf[i], i, local_opt_default);
			if ((_global_opt[i] != _global_optf[i]) && (_global_opt[i] != local_opt_default)){
				strcpy(local_str, STR_EMPTY);

				strcat_str_modl_opt_bit_order(local_str, i, USE_STR_MODL_OPTF);

				sprintf(pom3, HTML_AMPERSAND"%s=%d", local_str, _global_optf[i]);
				strcat(pom2, pom3);
				Log("\tPrilepil som aj optf %d: `%s'\n", i, pom3);
			}
		}// for i
	}// aj_force

	Log("prilep_request_options() -- koniec.\n");
}// prilep_request_options();

char *_vytvor_string_z_datumu(short int den, short int mesiac, short int rok, short int _case, short int typ, short int align){
	char pom[MAX_STR] = STR_EMPTY;
	char vypln[SMALL] = STR_EMPTY;
	char strden[SMALL] = STR_EMPTY;
	mystrcpy(_global_pom_str, STR_EMPTY, MAX_STR);
	// pre export medzery pre jednociferné čísla dní zarovnáme nezlomiteľnou medzerou
	if ((align != NIE) && (den < 10)){
		mystrcpy(vypln, HTML_NONBREAKING_SPACE, SMALL);
	}
	if (den != VSETKY_DNI){
		if (_global_jazyk == JAZYK_EN){
			sprintf(strden, " %s%d", vypln, den);
		}
		else if (_global_jazyk == JAZYK_HU){
			sprintf(strden, " %s%d.", vypln, den);
		}
		else{
			// default pre JAZYK_LA, JAZYK_SK, JAZYK_CZ, JAZYK_CZ_OP
			sprintf(strden, "%s%d. ", vypln, den);
		}
	}
	if (_global_jazyk == JAZYK_LA){
		sprintf(pom, "%s%s", strden, nazov_Mesiaca_gen(mesiac - 1));
		if (typ == LINK_DEN_MESIAC_ROK){
			// pridame aj rok
			strcat(_global_pom_str, pom);
			sprintf(pom, " %d", rok);
		}
	}
	else if (_global_jazyk == JAZYK_EN){
		sprintf(pom, "%s%s", nazov_Mesiaca(mesiac - 1), strden);
		if (typ == LINK_DEN_MESIAC_ROK){
			// pridame aj rok
			strcat(_global_pom_str, pom);
			sprintf(pom, ", %d", rok);
		}
	}
	// 2010-05-21: doplnené pre maďarčinu: 1999. augusztus 1. -- http://en.wikipedia.org/wiki/Date_and_time_notation_by_country#Hungary [2010-05-24]
	else if (_global_jazyk == JAZYK_HU){
		if (typ == LINK_DEN_MESIAC_ROK){
			// pridáme najprv rok
			sprintf(pom, "%d. ", rok);
			strcat(_global_pom_str, pom);
		}
		sprintf(pom, "%s", nazov_mesiaca(mesiac - 1));
		strcat(_global_pom_str, pom);
		sprintf(pom, "%s", strden);
	}
	else{
		// doterajšie správanie pre slovenčinu a češtinu
		switch (_case){
		case CASE_case:
			sprintf(pom, "%s%s", strden, (typ == LINK_DEN_MESIAC_GEN) ? nazov_mesiaca_gen(mesiac - 1) : nazov_mesiaca(mesiac - 1));
			break;
		case CASE_Case:
			sprintf(pom, "%s%s", strden, (typ == LINK_DEN_MESIAC_GEN) ? nazov_Mesiaca_gen(mesiac - 1) : nazov_Mesiaca(mesiac - 1));
			break;
		case CASE_CASE:
			sprintf(pom, "%s%s", strden, /* (typ == LINK_DEN_MESIAC_GEN)? nazov_MESIACA_gen(mesiac - 1) : */ nazov_MESIACA(mesiac - 1));
			break;
		}// switch(_case)
		if (typ == LINK_DEN_MESIAC_ROK){
			// pridame aj rok
			strcat(_global_pom_str, pom);
			sprintf(pom, " %d", rok);
		}
	}
	strcat(_global_pom_str, pom);
	return (_global_pom_str);
}// _vytvor_string_z_datumu()

/* do globalneho stringu _global_link vrati retazec, ktory je linkou
 * na SCRIPT_NAME ++ ? zoznam param(i) = value(i)
 *
 * premenna typ oznacuje, ci ide o vypisanie tvaru (napr.)
 *         11. december 1999 (LINK_DEN_MESIAC_ROK)
 * alebo   11                (LINK_DEN)
 * alebo   'meno sviatku'    (default)
 * alebo   1999-12-11        (LINK_ISO_8601) - pridane 2005-03-21
 *
 */
void _vytvor_global_link(short int den, short int mesiac, short int rok, short int _case, short int typ, short int align){
	Log("_vytvor_global_link(orig): volám s hodnotou html_class == NULL...\n");
	_vytvor_global_link(den, mesiac, rok, _case, typ, align, NULL);
	Log("_vytvor_global_link(orig): koniec.\n");
}

void _vytvor_global_link(short int den, short int mesiac, short int rok, short int _case, short int typ, short int align, const char * html_class){
	Log("_vytvor_global_link(new): začiatok...\n");
	Log("den == %d, mesiac == %d, rok == %d...\n", den, mesiac, rok);
	// 2003-07-09 zmeneny & na HTML_AMPERSAND kvoli HTML 4.01
	char pom[MAX_STR];
	mystrcpy(pom, STR_EMPTY, MAX_STR);

	char pom2[MAX_STR];
	mystrcpy(pom2, STR_EMPTY, MAX_STR);

	char str_subor[SMALL] = STR_EMPTY;
	char str_month[SMALL] = STR_EMPTY;

	// ak pozadujeme vytvorenie linku s inou farbou pre prestupny rok, 2003-07-02
	if (typ == LINK_DEN_MESIAC_ROK_PRESTUP){
		mystrcpy(_global_link, "<"HTML_LINK_RED" href=\"", MAX_GLOBAL_LINK);
	}
	else{ // inak normalny a href, toto tu bolo predtym; 2003-07-02
		if ((html_class != NULL) && (strlen(html_class) > 0)){
			sprintf(_global_link, "<"HTML_LINK_CLASS_B"%s"HTML_LINK_CLASS_E" href=\"", html_class);
		}
		else{
			mystrcpy(_global_link, "<"HTML_LINK_NORMAL" href=\"", MAX_GLOBAL_LINK);
		}
	}

	if (_global_opt_batch_monthly == NIE){
		if (_global_linky == ANO){
			// linka ano

			strcat(_global_link, script_name);

			// query_type
			sprintf(pom, "?%s=%s"HTML_AMPERSAND, STR_QUERY_TYPE, STR_PRM_DATUM);
			strcat(_global_link, pom);

			// deň
			if (den == VSETKY_DNI)
				sprintf(pom, "%s=%s"HTML_AMPERSAND, STR_DEN, STR_VSETKY_DNI);
			else
				sprintf(pom, "%s=%d"HTML_AMPERSAND, STR_DEN, den);
			strcat(_global_link, pom);

			// mesiac
			if (mesiac == VSETKY_MESIACE)
				sprintf(pom, "%s=%s"HTML_AMPERSAND, STR_MESIAC, STR_VSETKY_MESIACE);
			else
				sprintf(pom, "%s=%d"HTML_AMPERSAND, STR_MESIAC, mesiac);
			strcat(_global_link, pom);

			// rok
			sprintf(pom, "%s=%d", STR_ROK, rok);
			strcat(_global_link, pom);

		}// linka ano
		else{ // linka nie
			strcat(_global_link, FILE_NAME_POKEC);
			if (mesiac == VSETKY_MESIACE){
				strcat(_global_link, "r");
			}
			else if (den == VSETKY_DNI){
				strcat(_global_link, "m");
			}
			else{
				strcat(_global_link, "d");
			}
			strcat(_global_link, ".htm");
		}// linka nie

		prilep_request_options(_global_link, pom2);

	}// if(_global_opt_batch_monthly == NIE)
	else{
		// najprv podľa typu exportu rozhodneme, či treba predlepiť aj adresár
		if (typ == LINK_DEN_MESIAC_PREDOSLY || typ == LINK_DEN_MESIAC_NASLEDOVNY){
			if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE)
				sprintf(str_month, ".."STR_PATH_SEPARATOR_HTML""DIRNAME_EXPORT_MONTH_SIMPLE""STR_PATH_SEPARATOR_HTML, rok % 100, mesiac, nazov_mes[mesiac - 1]);
			else // EXPORT_DATE_FULL
				sprintf(str_month, ".."STR_PATH_SEPARATOR_HTML""DIRNAME_EXPORT_MONTH_FULL""STR_PATH_SEPARATOR_HTML, rok, mesiac, nazov_mesiaca_asci(mesiac - 1));
		}
		else{
			mystrcpy(str_month, STR_EMPTY, SMALL);
		}
		Log("str_month == %s\n", str_month);
		// reťazec pre deň a pre názov súboru
		if (den != VSETKY_DNI){
			if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE)
				sprintf(str_subor, FILENAME_EXPORT_DATE_SIMPLE, rok % 100, mesiac, den);
			else // EXPORT_DATE_FULL
				sprintf(str_subor, FILENAME_EXPORT_DATE_FULL, rok, mesiac, den);
		}
		else{
			// den == VSETKY_DNI
			if (_global_opt_export_date_format == EXPORT_DATE_SIMPLE)
				sprintf(str_subor, FILENAME_EXPORT_MONTH_SIMPLE, rok % 100, mesiac);
			else // EXPORT_DATE_FULL
				sprintf(str_subor, FILENAME_EXPORT_MONTH_FULL, rok, mesiac);
		}
		Log("str_subor == %s\n", str_subor);
		sprintf(pom, "%s%s.htm", str_month, str_subor);
		Log("\treťazec pom == %s\n", pom);
		strcat(_global_link, pom);
	}

	strcat(_global_link, "\">");

	// printing link
	switch (typ){
	case LINK_DEN_MESIAC_ROK_PRESTUP:
	case LINK_DEN_MESIAC_PREDOSLY:
	case LINK_DEN_MESIAC_NASLEDOVNY:
	case LINK_DEN_MESIAC_ROK:
	case LINK_DEN_MESIAC:
		if (den == VSETKY_DNI){
			if (mesiac == VSETKY_MESIACE)
				sprintf(pom, "%d</a>", rok);
			else{
				if (typ == LINK_DEN_MESIAC_PREDOSLY){
					sprintf(pom, ""HTML_LEFT_ARROW_WIDE"");
				}
				else if (typ == LINK_DEN_MESIAC_NASLEDOVNY){
					sprintf(pom, ""HTML_RIGHT_ARROW_WIDE"");
				}
				else{
					switch (_case){
					case CASE_case:
						sprintf(pom, "%s", nazov_mesiaca(mesiac - 1));
						break;
					case CASE_Case:
						sprintf(pom, "%s", nazov_Mesiaca(mesiac - 1));
						break;
					case CASE_CASE:
						sprintf(pom, "%s", nazov_MESIACA(mesiac - 1));
						break;
					}// switch(_case)
				}
				if (typ == LINK_DEN_MESIAC_ROK){
					// pridame aj rok
					strcat(_global_link, pom);
					sprintf(pom, " %d", rok);
				}
				strcat(pom, "</a>");
			}// mesiac != VSETKY_MESIACE
		}// if(den == VSETKY_DNI)
		else{
			if (typ == LINK_DEN_MESIAC_PREDOSLY){
				sprintf(pom, ""HTML_LEFT_ARROW_WIDE"");
			}
			else if (typ == LINK_DEN_MESIAC_NASLEDOVNY){
				sprintf(pom, ""HTML_RIGHT_ARROW_WIDE"");
			}
			else{
				strcpy(pom, _vytvor_string_z_datumu(den, mesiac, rok, _case, typ, align));
			}
			strcat(pom, "</a>");
		}// den != VSETKY_DNI
		break;
	case LINK_DEN:
		sprintf(pom, "%d</a>", den);
		break;
	case LINK_ISO_8601:
		sprintf(pom, HTML_ISO_FORMAT"</a>", rok, mesiac, den);
		break;
	default:
		switch (_case){
		case CASE_case:
			sprintf(pom, "%s</a>", _global_den.meno);
			break;
		case CASE_Case:
			sprintf(pom, "%s</a>", _global_den.meno);
			break;
		case CASE_CASE:
			sprintf(pom, "%s</a>", caps_BIG(_global_den.meno));
			break;
		}// switch(_case)
		break;
	}// switch(typ)

	strcat(_global_link, pom);
	Log("_vytvor_global_link(new): koniec.\n");
}// _vytvor_global_link();

// vrati 1, ak je rok priestupny, inak vrati 0
short int prestupny(short int rok){
	if ((rok MOD 4) == 0){
		if ((rok MOD 100) == 0){
			return ((rok MOD 400) == 0);
		}
		else
			return 1;
	}
	else
		return 0;
}

short int pocet_dni_v_roku(short int rok){
	if (prestupny(rok))
		return POCET_DNI_V_ROKU + 1;
	else
		return POCET_DNI_V_ROKU;
}

// vrati poradove cislo dna v roku, 1.1. == 1, 2.1. == 2, ..., 31.12. == 365/366 | ocakava cislo mesiaca 1-12 (pozn. 2003-07-04)
short int poradie(short int den, short int mesiac, short int rok){
	if (mesiac > 2)
		return prvy_den[mesiac - 1] + den - 1 + prestupny(rok);
	else
		return prvy_den[mesiac - 1] + den - 1;
}// poradie()

short int poradie(_struct_den_mesiac den_a_mesiac, short int rok){
	return poradie(den_a_mesiac.den, den_a_mesiac.mesiac, rok);
}// poradie()

short int zjavenie_pana(short int rok){
	short int ZJAVENIE_PANA; // zjavenie Pána
	char nedelne_pismenko = _global_r.p1;

	if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA)){
		if (nedelne_pismenko == 'A'){
			nedelne_pismenko = 'h'; // aby vyšla nedeľa Zjavenia Pána na 8.1.
		}
		Log("Zjavenie Pána sa slávi v nedeľu; %c/%c\n", _global_r.p1, nedelne_pismenko);
		ZJAVENIE_PANA = poradie((nedelne_pismenko - 'a') + 1, 1, rok); // nedeľa medzi 2. a 8. januárom
	}
	else{
		ZJAVENIE_PANA = poradie(6, 1, rok);
	}
	return ZJAVENIE_PANA;
}// zjavenie_pana()

//---------------------------------------------------------------------

/* Francuzsky vedec Joseph Scaliger vydal v roku 1583 traktat
 * "Nova praca o zdokonaleni letopoctu". Zaviedol juliansky datum
 * (podla svojho otca Juliusa), pricom zaciatok julianskej periody vzal
 * 1. januar roku 4713 pred Kr.
 *
 * 1. januar 1 po Kr. == 1721058 JD (podla julianskeho kalendara)
 * 1. januar 1920     == 2422325 JD
 * 1. januar 1968     == 2439857 JD
 */
long juliansky_datum(short int por, short int rok){
	short int r;
	long jd = 0;
	if (rok >= ROK_1968){
		for (r = ROK_1968; r < rok; r++)
			jd = jd + pocet_dni_v_roku(r);
		return (jd + por + JUL_DATE_0_JAN_1968);
	}
	else{
		for (r = rok; r < ROK_1968; r++)
			jd = jd + pocet_dni_v_roku(r);
		return (por + JUL_DATE_0_JAN_1968 - jd);
	}
}

// ocakava cislo mesiaca 1-12 (pozn. 2003-07-04)
long juliansky_datum(short int den, short int mesiac, short int rok){
	short int por;
	por = poradie(den, mesiac, rok);
	return juliansky_datum(por, rok);
}

//---------------------------------------------------------------------
// nasledujuce funkcie zistuju datum velkonocnej nedele

// urcenie datumu VELKONOCNA_NEDELA podla Gaussovho pravidla
_struct_den_mesiac velkonocna_nedela(short int R){
	short int x, y, k, q, p, a, b, c, d, e;
	_struct_den_mesiac result;

	// 1. urcenie konstant
	// juliansky kalendar: x = 15, y = 6
	// gregoriansky kalendar:
	k = R DIV 100;				// DEBUG("k==%d", k);
	q = k DIV 4;    			// DEBUG("q==%d", q);
	p = ((8 * k) + 13) DIV 25;  // DEBUG("p==%d", p);
	x = (15 - p + k - q) MOD 30;// DEBUG("x==%d", x);
	y = (4 + k - q) MOD 7;      // DEBUG("y==%d", y);
	// 2. samotny vypocet
	a = R MOD 19;				// DEBUG("a==%d", a);
	b = R MOD 4;                // DEBUG("b==%d", b);
	c = R MOD 7;                // DEBUG("c==%d", c);
	d = (x + (19 * a)) MOD 30;  // DEBUG("d==%d", d);
	e = (y + (2 * b) + (4 * c) + (6 * d)) MOD 7;  // DEBUG("e==%d", e);
	// velkonocna nedela je (22 + d + e). marca == (d + e - 9). aprila
	// 22 + d + e je "poradové číslo dňa v marci" (22 až 56), a teda ak je väčšie ako 31, je to apríl; 
	// ak je viac ako 56, treba posunúť na predošlú nedeľu; viď nižšie
	if ((22 + d + e) > 31){
		// 2010-02-18: opravené
		// ak veľkonočná nedeľa Gaussovým pravidlom vyjde na 26. apríla, posunie sa o týždeň dopredu | upozornil Peter Chren <zal@zal.sk> 
		// podľa http://en.wikipedia.org/wiki/Computus upravené:
		// Gregorian Easter is 22 + d + e March or d + e - 9 April
		// if d = 29 and e = 6, replace 26 April with 19 April
		// if d = 28, e = 6, and (11M + 11) mod 30 < 19, replace 25 April with 18 April
		if ((d == 29) && (e == 6)){
			result.den = 19;
		}
		else if ((d == 28) && (e == 6) && ((11 * x + 11) MOD 30 < 19)){
			result.den = 18;
		}
		else{
			result.den = d + e - 9;
		}
		result.mesiac = 4; // apríl
	}
	else{
		result.den = 22 + d + e;
		result.mesiac = 3; // marec
	}
	return result;
}

// vrati poradie velkonocnej nedele; 1.1. == 1, 31.12. == 365/366
short int _velkonocna_nedela(short int rok){
	_struct_den_mesiac result;

	result = velkonocna_nedela(rok);
	return poradie(result, rok);
}

// vrati cislo dna v tyzdni zodpovedajuce datumu,
// 0 == DEN_NEDELA, 1 == DEN_PONDELOK atd.
short int den_v_tyzdni(short int por, short int rok){
	short int vn;
	vn = _velkonocna_nedela(rok);
	return ((por MOD 7) + 7 - (vn MOD 7)) MOD 7;
}

short int den_v_tyzdni(short int den, short int mesiac, short int rok){
	short int por;
	por = poradie(den, mesiac, rok);
	return den_v_tyzdni(por, rok);
}

short int den_v_tyzdni(_struct_den_mesiac den_a_mesiac, short int rok){
	return den_v_tyzdni(den_a_mesiac.den, den_a_mesiac.mesiac, rok);
}

// vrati nedelne pismeno pre dany rok;
// ak je rok prestupny, vracia PRVE nedelne pismeno, 
// DRUHE sa dostane tak, ze char_nedelne_pismeno[(PRVE + 6) MOD 7];
// _nedelne_pismeno vrati ciselny udaj (0 -- 6), ktory je vstupom pre konstantne pole char_nedelne_pismeno[]
unsigned char _nedelne_pismeno(short int rok){
	short int vn;
	vn = _velkonocna_nedela(rok);
	return (char)((vn + 5) MOD 7); // (char) pridane 01/03/2000A.D.
}

char nedelne_pismeno(short int rok){
	return char_nedelne_pismeno[_nedelne_pismeno(rok)];
}

// vrati nedelne pismeno v tej casti roka, kde je den.mesiac.
// to pre prestupny rok znamena, ze pocnuc 1. marcom je druhe nedelne pismeno
unsigned char _nedelne_pismeno(short int por, short int rok){
	if ((prestupny(rok)) && (por > poradie(29, MES_FEB + 1, rok)))
		return (char)((_nedelne_pismeno(rok) + 6) MOD 7);
	else
		return _nedelne_pismeno(rok);
}

char nedelne_pismeno(short int por, short int rok){
	return char_nedelne_pismeno[_nedelne_pismeno(por, rok)];
}

char nedelne_pismeno(short int den, short int mesiac, short int rok){
	short int por;
	por = poradie(den, mesiac, rok);
	return nedelne_pismeno(por, rok);
}

unsigned char _nedelne_pismeno(short int den, short int mesiac, short int rok){
	short int por;
	por = poradie(den, mesiac, rok);
	return _nedelne_pismeno(por, rok);
}

// vrati nedelne pismeno v spravnej casti roka, ale neberie do uvahy typ modlitby, t.j. ked su (prve) vespery, vrati zly den, pozor na to (prípadne [ToDo] dokončiť)
unsigned char _nedelne_pismeno(_struct_den_mesiac den_a_mesiac, short int rok){
	return
	_nedelne_pismeno(poradie(den_a_mesiac.den, den_a_mesiac.mesiac, rok), rok);
}// _nedelne_pismeno()

char nedelne_pismeno(_struct_den_mesiac den_a_mesiac, short int rok){
	return char_nedelne_pismeno[_nedelne_pismeno(den_a_mesiac, rok)];
}// nedelne_pismeno()

// z poradoveho cisla dna v roku urobi datum,
// 1 == 1.1., 2 == 2.1., 32 == 1.2., ... 365 == 31.12./30.12.
_struct_den_mesiac por_den_mesiac(short int poradie, short int rok){
	short int d, m;
	_struct_den_mesiac result;

	if (prestupny(rok))
		pocet_dni[MES_FEB] = 29;
	else
		pocet_dni[MES_FEB] = 28;
	d = poradie;
	m = MES_JAN; // január
	while (d > pocet_dni[m]){
		d = d - pocet_dni[m];
		m++;
	}
	result.den = d;
	result.mesiac = m + 1; // výsledok: 1--12
	return result;
}

// zoslanie ducha sv. je 50.-ty den po velkej noci, treba VELKONOCNA_NEDELA + 49
short int _zoslanie_ducha(short int rok){
	return (_velkonocna_nedela(rok) + OD_VELKEJ_NOCI_PO_ZOSLANIE_DUCHA);
}// _zoslanie_ducha()

// _prva_adventna_nedela() vrati poradove cislo dna, kt. zodpoveda prvej adventnej nedeli;
// prva_adventna_nedela() vracia strukturu (datum) prvej adv. nedele
short int _prva_adventna_nedela(short int rok){
	char p;
	_struct_den_mesiac datum;

	// volime 1.3.rok
	datum.den = 1;
	datum.mesiac = 3;
	// po februari, pretoze potrebujeme DRUHE nedelne pismeno
	p = _nedelne_pismeno(datum, rok);
	return (PRVA_ADVENTNA_NEDELA_b + p + prestupny(rok));
}// _prva_adventna_nedela()

//---------------------------------------------------------------------
// nasledujuce _struct_den_mesiac ...() funkcie vracaju <den, mesiac>

_struct_den_mesiac prva_adventna_nedela(short int rok){
	return (por_den_mesiac(_prva_adventna_nedela(rok), rok));
}// prva_adventna_nedela()

//---------------------------------------------------------------------

// vrati 0 == rok A, 1 == rok B, 2 == rok C
// pozor!
// neuvazujeme o tom, ze vecer toho dna su prve vespery z dalsieho dna, ktory uz moze byt inym liturgickym rokom. to nie je osetrene ani vo funkcii nedelny_cyklus(_struct_den_mesiac, int);
short int vseobecny_cyklus(short int por, short int rok, short int perioda){
	_struct_den_mesiac pan;
	short int porpan;
	pan = prva_adventna_nedela(rok);
	porpan = poradie(pan.den, pan.mesiac, rok);
	if (por < porpan)
		return ((rok - 1) MOD perioda);
	else
		return (rok MOD perioda);
}

short int nedelny_cyklus(short int por, short int rok){
	return vseobecny_cyklus(por, rok, 3);
}

short int ferialny_cyklus(short int por, short int rok){
	return vseobecny_cyklus(por, rok, 2);
}

short int nedelny_cyklus(short int den, short int mesiac, short int rok){
	short int por;
	por = poradie(den, mesiac, rok);
	return nedelny_cyklus(por, rok);
}

short int ferialny_cyklus(short int den, short int mesiac, short int rok){
	short int por;
	por = poradie(den, mesiac, rok);
	return ferialny_cyklus(por, rok);
}

short int nedelny_cyklus(_struct_den_mesiac den_a_mesiac, short int rok){
	return nedelny_cyklus(poradie(den_a_mesiac.den, den_a_mesiac.mesiac, rok), rok);
}

// z poradoveho cisla dna v roku urobi datum,
// 1 == 1.1., 2 == 2.1., 32 == 1.2., ... 365 == 31.12./30.12.
// zapise tiez do _struct_dm tieto polozky:
//    .den, .mesiac, .rok, .denvr, .denvt, .link, .litrok
_struct_dm por_den_mesiac_dm(short int poradie, short int rok){
	_struct_den_mesiac pom;
	_struct_dm result;

	pom = por_den_mesiac(poradie, rok);
	result.den = pom.den;
	result.mesiac = pom.mesiac;
	result.rok = rok;
	result.denvr = poradie;
	result.denvt = den_v_tyzdni(poradie, rok);
	result.litrok = (char)('A' + nedelny_cyklus(pom.den, pom.mesiac, rok)); // (char) pridane 01/03/2000A.D.
	// dalsia cast pridana kvoli tomu, aby nic nebolo nedefinovane :-) | 27/04/2000A.D.
	result.tyzden = 0;
	result.tyzzal = 0;
	result.litobd = OBD_CEZ_ROK; // nemam neurcene...
	result.typslav = SLAV_NEURCENE;
	result.smer = 14; // neurcene
	result.prik = NIE_JE_PRIKAZANY_SVIATOK;
	result.spolcast =
		_encode_spol_cast(MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA);
	mystrcpy(result.meno, STR_EMPTY, MENO_SVIATKU);
	mystrcpy(result.lc_str_id, STR_EMPTY, MAX_LC_STR_ID);
	return result;
}

// vrati cislo tyzdna v obdobi cez rok, ktory nasleduje po nedeli zoslania ducha sv. - teda po konci velkonocneho obdobia
short int tyzden_cez_rok_po_vn(short int rok){
	short int zds, pan;

	pan = _prva_adventna_nedela(rok);
	zds = _zoslanie_ducha(rok);
	return (POCET_NEDIEL_CEZ_ROK - ((pan - zds) DIV 7));
}

short int cislo_nedele_cez_rok_po_vn(short int rok){
	return (tyzden_cez_rok_po_vn(rok) + 1);
}

// naplni strukturu _global_pm_sobota, ale az vtedy, ked v _global_den su spravne udaje
void init_global_pm_sobota(void){
	_global_pm_sobota.den = _global_den.den;
	_global_pm_sobota.mesiac = _global_den.mesiac;
	_global_pm_sobota.rok = _global_den.rok;
	_global_pm_sobota.denvt = _global_den.denvt;
	_global_pm_sobota.denvr = _global_den.denvr;
	_global_pm_sobota.litobd = _global_den.litobd;
	_global_pm_sobota.litrok = _global_den.litrok;
	_global_pm_sobota.tyzden = _global_den.tyzden;
	_global_pm_sobota.tyzzal = _global_den.tyzzal;
	// a teraz vlastne udaje
	_global_pm_sobota.smer = 12; // ľubovoľné spomienky
	_global_pm_sobota.typslav = SLAV_LUB_SPOMIENKA;
	_global_pm_sobota.typslav_lokal = LOKAL_SLAV_NEURCENE; // nie je obmedzenie na lokalitu, pridané 2005-07-27
	mystrcpy(_global_pm_sobota.meno, text_SPOMIENKA_PM_V_SOBOTU[_global_jazyk], MENO_SVIATKU);
	_global_pm_sobota.prik = NIE_JE_PRIKAZANY_SVIATOK;
	_global_pm_sobota.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA, MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA);
	_global_pm_sobota.farba = LIT_FARBA_BIELA;
	_global_pm_sobota.kalendar = KALENDAR_VSEOBECNY;
	mystrcpy(_global_pm_sobota.lc_str_id, _global_den.lc_str_id, MAX_LC_STR_ID);
}

void _dm_popolcova_streda(short int rok, short int _vn){
	_global_result = por_den_mesiac_dm(_vn + OD_VELKEJ_NOCI_PO_POPOLCOVU_STR, rok);
	_global_result.typslav = SLAV_NEURCENE;
	_global_result.typslav_lokal = LOKAL_SLAV_NEURCENE;
	_global_result.litobd = OBD_POSTNE_I;
	_global_result.tyzden = 0; // 4. tyzden zaltara
	_global_result.smer = 2;
	_global_result.prik = NIE_JE_PRIKAZANY_SVIATOK;
	mystrcpy(_global_result.meno, text_POPOLCOVA_STREDA[_global_jazyk], MENO_SVIATKU);
	_global_result.tyzzal = 4; // 4. tyzden zaltara
	_global_result.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA);
	_global_result.farba = LIT_FARBA_FIALOVA;
	_global_result.kalendar = KALENDAR_VSEOBECNY;
	mystrcpy(_global_result.lc_str_id, "0P3", MAX_LC_STR_ID);
}// _dm_popolcova_streda()

void _dm_nanebovstupenie(short int rok, short int _vn){
	short int _nan;
	if (isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA)){
		_nan = (_vn + OD_VELKEJ_NOCI_PO_NANEBOSTUPENIE_NE);
	}
	else{
		_nan = (_vn + OD_VELKEJ_NOCI_PO_NANEBOSTUPENIE);
	}
	_global_result = por_den_mesiac_dm(_nan, rok);
	_global_result.typslav = SLAV_SLAVNOST;
	_global_result.typslav_lokal = LOKAL_SLAV_NEURCENE;
	_global_result.litobd = OBD_VELKONOCNE_I;
	_global_result.tyzden = 0;
	_global_result.tyzzal = 1;
	_global_result.smer = 2;
	_global_result.prik = PRIKAZANY_SVIATOK;
	mystrcpy(_global_result.meno, text_NANEBOVSTUPENIE_PANA[_global_jazyk], MENO_SVIATKU);
	_global_result.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA);
	_global_result.farba = LIT_FARBA_BIELA;
	_global_result.kalendar = KALENDAR_VSEOBECNY;
	mystrcpy(_global_result.lc_str_id, "6V4", MAX_LC_STR_ID);
}// _dm_nanebovstupenie()

void _dm_zoslanie_ducha(short int rok, short int _vn){
	_global_result = por_den_mesiac_dm(_vn + OD_VELKEJ_NOCI_PO_ZOSLANIE_DUCHA, rok);
	_global_result.typslav = SLAV_SLAVNOST;
	_global_result.typslav_lokal = LOKAL_SLAV_NEURCENE;
	_global_result.litobd = OBD_VELKONOCNE_II;
	_global_result.tyzden = 0;
	_global_result.tyzzal = 1;
	_global_result.smer = 2;
	_global_result.prik = PRIKAZANY_SVIATOK;
	mystrcpy(_global_result.meno, text_ZOSLANIE_DUCHA_SVATEHO[_global_jazyk], MENO_SVIATKU);
	_global_result.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA);
	_global_result.farba = LIT_FARBA_CERVENA;
	_global_result.kalendar = KALENDAR_VSEOBECNY;
	mystrcpy(_global_result.lc_str_id, "8V", MAX_LC_STR_ID);
}// _dm_zoslanie_ducha()

void _dm_prva_adventna_nedela(short int rok, short int p2){
	_global_result = por_den_mesiac_dm(PRVA_ADVENTNA_NEDELA_b + p2 + prestupny(rok), rok);
	_global_result.typslav = SLAV_VLASTNE;
	_global_result.typslav_lokal = LOKAL_SLAV_NEURCENE;
	_global_result.litobd = OBD_ADVENTNE_I;
	_global_result.tyzden = 1; // 1. adventna nedela
	_global_result.smer = 2;
	_global_result.prik = NIE_JE_PRIKAZANY_SVIATOK;
	mystrcpy(_global_result.meno, text_PRVA_ADVENTNA_NEDELA[_global_jazyk], MENO_SVIATKU);
	_global_result.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA);
	_global_result.tyzzal = 1;
	_global_result.farba = LIT_FARBA_FIALOVA;
	_global_result.kalendar = KALENDAR_VSEOBECNY;
	mystrcpy(_global_result.lc_str_id, "1A", MAX_LC_STR_ID);
}// _dm_prva_adventna_nedela()

void _dm_svatej_rodiny(short int rok){
	short int _svrod;
	if (den_v_tyzdni(25, 12, rok) == DEN_NEDELA){
		_svrod = poradie(30, 12, rok);
	}
	else{
		_svrod = poradie(25, 12, rok);
		while (den_v_tyzdni(_svrod, rok) != DEN_NEDELA){
			_svrod++;
		}
	}
	_global_result = por_den_mesiac_dm(_svrod, rok);
	_global_result.typslav = SLAV_SVIATOK;
	_global_result.typslav_lokal = LOKAL_SLAV_NEURCENE;
	_global_result.litobd = OBD_OKTAVA_NARODENIA;
	_global_result.smer = 5;
	_global_result.tyzden = 1; // 1. tyzden vianocneho obdobia, oktava
	_global_result.prik = NIE_JE_PRIKAZANY_SVIATOK;
	mystrcpy(_global_result.meno, text_NEDELA_SV_RODINY[_global_jazyk], MENO_SVIATKU);
	_global_result.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA);
	_global_result.tyzzal = 1;
	_global_result.farba = LIT_FARBA_BIELA;
	_global_result.kalendar = KALENDAR_VSEOBECNY;
	mystrcpy(_global_result.lc_str_id, "SvR", MAX_LC_STR_ID);
}// _dm_svatej_rodiny()

void _dm_krst_krista_pana(short int rok){
	short int _zjavenie_pana = zjavenie_pana(rok); // bolo tu static, ale pre viacnásobné volanie z analyzuj_rok() pre tabuľku tu 'static' nesmie byť
	short int _krst = _zjavenie_pana + 1;

	if (!(isGlobalOption(OPT_0_SPECIALNE, BIT_OPT_0_ZJAVENIE_PANA_NEDELA) && ((_zjavenie_pana == 7) || (_zjavenie_pana == 8)))){
		while (den_v_tyzdni(_krst, rok) != DEN_NEDELA){
			_krst++;
		}// while -- hľadáme nedeľu
	}// Zjavenie Pána sa slávi 6.1. alebo v nedeľu medzi 2. a 8. januárom, ktorá však nepripadne na 7. alebo 8. januára
	_global_result = por_den_mesiac_dm(_krst, rok);
	_global_result.typslav = SLAV_SVIATOK;
	_global_result.typslav_lokal = LOKAL_SLAV_NEURCENE;
	_global_result.litobd = OBD_VIANOCNE_II;
	_global_result.tyzden = 1; // 1. nedeľa "cez rok" (resp. v krajinách, kde sa Zjavenie Pána slávi v nedeľu, pričom táto pripadne na 7. alebo 8. januára, je to pondelok)
	_global_result.smer = 5; // sviatky Pána uvedené vo všeobecnom kalendári
	mystrcpy(_global_result.meno, text_JAN_KRST[_global_jazyk], MENO_SVIATKU); // 2003-08-11 zmenena na mystrcpy
	_global_result.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA);
	_global_result.prik = NIE_JE_PRIKAZANY_SVIATOK;
	_global_result.tyzzal = 1;
	_global_result.farba = LIT_FARBA_BIELA;
	_global_result.kalendar = KALENDAR_VSEOBECNY;
	mystrcpy(_global_result.lc_str_id, "1C", MAX_LC_STR_ID);
}// _dm_krst_krista_pana()

void _dm_velkonocna_nedela(short int rok, short int _vn){
	_global_result = por_den_mesiac_dm(_vn, rok);
	_global_result.typslav = SLAV_SLAVNOST;
	_global_result.typslav_lokal = LOKAL_SLAV_NEURCENE;
	_global_result.litobd = OBD_VELKONOCNE_TROJDNIE;
	_global_result.tyzden = 1; // 1. velkonocna nedela
	_global_result.smer = 1;
	mystrcpy(_global_result.meno, text_VELKONOCNA_NEDELA[_global_jazyk], MENO_SVIATKU);
	strcat(_global_result.meno, text_NEDELA_PANOVHO_ZMRTVYCHVSTANIA[_global_jazyk]);
	_global_result.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA);
	_global_result.prik = NIE_JE_PRIKAZANY_SVIATOK;
	_global_result.tyzzal = 1;
	_global_result.farba = LIT_FARBA_BIELA;
	_global_result.kalendar = KALENDAR_VSEOBECNY;
	mystrcpy(_global_result.lc_str_id, "1V", MAX_LC_STR_ID);
}// _dm_velkonocna_nedela()

short int modlitba_predchadzajuca(short int modlitba, short int exclude_mcd_komplet){
	short int ret = modlitba - 1;

	if (exclude_mcd_komplet == ANO){
		if (je_modlitba_cez_den(ret)){
			ret = MODL_RANNE_CHVALY;
		}
		else if (je_kompletorium12(ret)){
			;
		}
	}

	// kontrola
	if (!je_modlitba_ok_buttons(ret)){
		ret = MODL_NEURCENA;
	}
	return ret;
}// modlitba_predchadzajuca()

short int modlitba_nasledujuca(short int modlitba, short int exclude_mcd_komplet){
	short int ret = modlitba + 1;

	if (exclude_mcd_komplet == ANO){
		if (je_modlitba_cez_den(ret)){
			ret = MODL_VESPERY;
		}
		else if (je_kompletorium12(ret)){
			ret = MODL_NEURCENA;
		}
	}

	// kontrola
	if (!je_modlitba_ok_buttons(ret)){
		ret = MODL_NEURCENA;
	}
	return ret;
}// modlitba_nasledujuca()

//---------------------------------------------------------------------
/* analyzuj_rok()
 *
 * vstup:  short int year
 * vystup: do globalnej premennej struct lrok _global_r da jednotlive vyznacne dni
 *         a ostatne data (prestupny, p1, p2, litrok, tyzden_ocr_po_vn, _den[]
 */
void analyzuj_rok(short int year){
	short int _vn; // poradie velkonocnej nedele
	_struct_den_mesiac vn; // datum velkonocnej nedele
	short int p1, p2; // nedelne pismena

	Log("analyzuj_rok(%d) -- begin\n", year);
	vn = velkonocna_nedela(year);
	_vn = poradie(vn, year);

	// ci je rok prestupny
	if (prestupny(year))
		_global_r.prestupny = YES;
	else
		_global_r.prestupny = NO;

	// urcime nedele pismena
	p1 = ((_vn + 5) MOD 7);
	p2 = (_global_r.prestupny == YES) ?
		((p1 + 6) MOD 7) : // ak je rok prestupny, ma dve nedelne pismena
		p1;               // inak p1 == p2
	// teraz znaky (char)
	_global_r.p1 = char_nedelne_pismeno[p1];
	_global_r.p2 = (_global_r.prestupny == YES) ?
		char_nedelne_pismeno[p2] :
		NIJAKE_NEDELNE_PISMENO;

	// slavnosti a sviatky
	_dm_krst_krista_pana(year);      _global_r._KRST_KRISTA_PANA = _global_result;
	_dm_popolcova_streda(year, _vn); _global_r._POPOLCOVA_STREDA = _global_result;
	_dm_velkonocna_nedela(year, _vn); _global_r._VELKONOCNA_NEDELA = _global_result;
	_dm_nanebovstupenie(year, _vn); _global_r._NANEBOVSTUPENIE_PANA = _global_result;
	_dm_zoslanie_ducha(year, _vn); _global_r._ZOSLANIE_DUCHA_SV = _global_result;
	_dm_prva_adventna_nedela(year, p2);  _global_r._PRVA_ADVENTNA_NEDELA = _global_result;
	_dm_svatej_rodiny(year);      _global_r._SVATEJ_RODINY = _global_result;

	// cislo nedele obdobia "cez rok" po velkej noci
	_global_r.tyzden_ocr_po_vn = (POCET_NEDIEL_CEZ_ROK - ((_global_r._PRVA_ADVENTNA_NEDELA.denvr - _global_r._ZOSLANIE_DUCHA_SV.denvr) DIV 7)) + 1;

	// cislo tyzdna obdobia "cez rok" pred postom, kedy zacina post
	_global_r.tyzden_ocr_pred_po = ((_global_r._POPOLCOVA_STREDA.denvr - _global_r._KRST_KRISTA_PANA.denvr) DIV 7) + 1;

	Log("analyzuj_rok(%d) -- end\n", year);
}// analyzuj_rok();

void Log(_struct_lrok r){
	Log_struktura_rok("struktura liturgicky rok:\n");
	Log_struktura_rok("   prestupny: %s\n", (r.prestupny == YES)? "ANO":"NIE");
	Log_struktura_rok("   p1, p2: %c, %c\n", r.p1, r.p2);
	Log_struktura_rok("   litrok: %c\n", r.litrok);
	Log_struktura_rok("   tyzden_ocr_po_vn: %d\n", r.tyzden_ocr_po_vn);
	Log_struktura_rok("   struct dm _den[POCET_ALIASOV]:\n");
	Log_struktura_rok("   _KRST_KRISTA_PANA         :\n"); Log(r._den[idx_KRST_KRISTA_PANA]);
	Log_struktura_rok("   _POPOLCOVA_STREDA         :\n"); Log(r._den[idx_POPOLCOVA_STREDA]);
	Log_struktura_rok("   _VELKONOCNA_NEDELA        :\n"); Log(r._den[idx_VELKONOCNA_NEDELA]);
	Log_struktura_rok("   _NANEBOVSTUPENIE_PANA     :\n"); Log(r._den[idx_NANEBOVSTUPENIE_PANA]);
	Log_struktura_rok("   _PRVA_ADVENTNA_NEDELA     :\n"); Log(r._den[idx_PRVA_ADVENTNA_NEDELA]);
	Log_struktura_rok("   _ZOSLANIE_DUCHA_SV        :\n"); Log(r._den[idx_ZOSLANIE_DUCHA_SV]);
	Log_struktura_rok("   _SVATEJ_RODINY            :\n"); Log(r._den[idx_SVATEJ_RODINY]);
}

void Log(_struct_dm g){
	Log_struktura_dm("struktura dm:\n");
	Log_struktura_dm("   den:    %d\n", g.den);
	Log_struktura_dm("   mesiac: %s\n", nazov_mesiaca(g.mesiac - 1));
	Log_struktura_dm("   rok:    %d\n", g.rok);
	Log_struktura_dm("   denvt:  %s\n", nazov_dna(g.denvt));
	Log_struktura_dm("   denvr:  %d\n", g.denvr);

	Log_struktura_dm("   litrok: %c\n", g.litrok);
	Log_struktura_dm("   tyzden: %d\n", g.tyzden);
	Log_struktura_dm("   tyzzal: %d\n", g.tyzzal);
	Log_struktura_dm("   litobd: %s\n", nazov_obdobia_[g.litobd]);
	Log_struktura_dm("   typslav:%s\n", nazov_slavenia(g.typslav));
	Log_struktura_dm("   typslav_lokal: %s\n", nazov_slavenia_lokal[g.typslav_lokal]);	
	Log_struktura_dm("   smer:   %d\n", g.smer);
	Log_struktura_dm("   prik:   %d\n", g.prik);
	Log_struktura_dm("   meno:   %s\n", g.meno);
	_struct_sc sc = _decode_spol_cast(g.spolcast);
	Log_struktura_dm("   spolcast: (%d) %s, (%d) %s, (%d) %s\n", sc.a1, nazov_spolc(sc.a1), sc.a2, nazov_spolc(sc.a2), sc.a3, nazov_spolc(sc.a3));
	Log_struktura_dm("   lc_str_id: %s\n", g.lc_str_id);
}

void Log(struct tmodlitba1 t){
	Log_struktura_tm1("struktura tmodlitba1:\n");
	Log_struktura_tm1("   alternativy = %d\n", t.alternativy);
	Log_struktura_tm1("   popis                 file `%s', anchor `%s'\n", t.popis.file, t.popis.anchor);
	Log_struktura_tm1("   hymnus                file `%s', anchor `%s'\n", t.hymnus.file, t.hymnus.anchor);
	Log_struktura_tm1("   antifona1             file `%s', anchor `%s'\n", t.antifona1.file, t.antifona1.anchor);
	Log_struktura_tm1("   zalm1                 file `%s', anchor `%s'\n", t.zalm1.file, t.zalm1.anchor);
	Log_struktura_tm1("   antifona2             file `%s', anchor `%s'\n", t.antifona2.file, t.antifona2.anchor);
	Log_struktura_tm1("   zalm2                 file `%s', anchor `%s'\n", t.zalm2.file, t.zalm2.anchor);
	Log_struktura_tm1("   antifona3             file `%s', anchor `%s'\n", t.antifona3.file, t.antifona3.anchor);
	Log_struktura_tm1("   zalm3                 file `%s', anchor `%s'\n", t.zalm3.file, t.zalm3.anchor);
	Log_struktura_tm1("   kcitanie              file `%s', anchor `%s'\n", t.kcitanie.file, t.kcitanie.anchor);
	Log_struktura_tm1("   kresponz              file `%s', anchor `%s'\n", t.kresponz.file, t.kresponz.anchor);
	Log_struktura_tm1("   bened/magnifikat      file `%s', anchor `%s'\n", t.benediktus.file, t.benediktus.anchor); // antifona na benediktus/magnifikat
	Log_struktura_tm1("   prosby                file `%s', anchor `%s'\n", t.prosby.file, t.prosby.anchor);
	Log_struktura_tm1("   modlitba              file `%s', anchor `%s'\n", t.modlitba.file, t.modlitba.anchor);
	Log_struktura_tm1("   ant_spomprivileg      file `%s', anchor `%s'\n", t.ant_spomprivileg.file, t.ant_spomprivileg.anchor);
	Log_struktura_tm1("   modlitba_spomprivileg file `%s', anchor `%s'\n", t.modlitba_spomprivileg.file, t.modlitba_spomprivileg.anchor);
}

void Log(struct tmodlitba2 t){
	Log_struktura_tm2("struktura tmodlitba2:\n");
	Log_struktura_tm2("   alternativy = %d\n", t.alternativy);
	Log_struktura_tm2("   popis        file `%s', anchor `%s'\n", t.popis.file, t.popis.anchor);
	Log_struktura_tm2("   hymnus       file `%s', anchor `%s'\n", t.hymnus.file, t.hymnus.anchor);
	Log_struktura_tm2("   antifona1    file `%s', anchor `%s'\n", t.antifona1.file, t.antifona1.anchor);
	Log_struktura_tm2("   zalm1        file `%s', anchor `%s'\n", t.zalm1.file, t.zalm1.anchor);
	Log_struktura_tm2("   antifona2    file `%s', anchor `%s'\n", t.antifona2.file, t.antifona2.anchor);
	Log_struktura_tm2("   zalm2        file `%s', anchor `%s'\n", t.zalm2.file, t.zalm2.anchor);
	Log_struktura_tm2("   antifona3    file `%s', anchor `%s'\n", t.antifona3.file, t.antifona3.anchor);
	Log_struktura_tm2("   zalm3        file `%s', anchor `%s'\n", t.zalm3.file, t.zalm3.anchor);
	Log_struktura_tm2("   kcitanie     file `%s', anchor `%s'\n", t.kcitanie.file, t.kcitanie.anchor);
	Log_struktura_tm2("   kresponz     file `%s', anchor `%s'\n", t.kresponz.file, t.kresponz.anchor);
	Log_struktura_tm2("   modlitba     file `%s', anchor `%s'\n", t.modlitba.file, t.modlitba.anchor);
}

void Log(struct tmodlitba3 t){
	Log_struktura_tm3("struktura tmodlitba3:\n");
	Log_struktura_tm3("   alternativy = %d\n", t.alternativy);
	Log_struktura_tm3("   pocet_zalmov = %d\n", t.pocet_zalmov);
	Log_struktura_tm3("   popis          file `%s', anchor `%s'\n", t.popis.file, t.popis.anchor);
	Log_struktura_tm3("   hymnus         file `%s', anchor `%s'\n", t.hymnus.file, t.hymnus.anchor);
	Log_struktura_tm3("   antifona1      file `%s', anchor `%s'\n", t.antifona1.file, t.antifona1.anchor);
	Log_struktura_tm3("   zalm1          file `%s', anchor `%s'\n", t.zalm1.file, t.zalm1.anchor);
	Log_struktura_tm3("   antifona2      file `%s', anchor `%s'\n", t.antifona2.file, t.antifona2.anchor);
	Log_struktura_tm3("   zalm2          file `%s', anchor `%s'\n", t.zalm2.file, t.zalm2.anchor);
	Log_struktura_tm3("   kcitanie       file `%s', anchor `%s'\n", t.kcitanie.file, t.kcitanie.anchor);
	Log_struktura_tm3("   kresponz       file `%s', anchor `%s'\n", t.kresponz.file, t.kresponz.anchor);
	Log_struktura_tm3("   nunc_dimittis  file `%s', anchor `%s'\n", t.nunc_dimittis.file, t.nunc_dimittis.anchor);
	Log_struktura_tm3("   modlitba       file `%s', anchor `%s'\n", t.modlitba.file, t.modlitba.anchor);
}

void Log(struct tmodlitba4 t){
	Log_struktura_tm4("struktura tmodlitba4:\n");
	Log_struktura_tm4("   popis        file `%s', anchor `%s'\n", t.popis.file, t.popis.anchor);
	Log_struktura_tm4("   antifona1    file `%s', anchor `%s'\n", t.antifona1.file, t.antifona1.anchor);
	Log_struktura_tm4("   zalm1        file `%s', anchor `%s'\n", t.zalm1.file, t.zalm1.anchor);
}

void Log(struct tmodlitba5 t){
	Log_struktura_tm5("struktura tmodlitba5:\n");
	Log_struktura_tm5("   alternativy = %d\n", t.alternativy);
	Log_struktura_tm5("   popis                 file `%s', anchor `%s'\n", t.popis.file, t.popis.anchor);
	Log_struktura_tm5("   hymnus                file `%s', anchor `%s'\n", t.hymnus.file, t.hymnus.anchor);
	Log_struktura_tm5("   antifona1             file `%s', anchor `%s'\n", t.antifona1.file, t.antifona1.anchor);
	Log_struktura_tm5("   zalm1                 file `%s', anchor `%s'\n", t.zalm1.file, t.zalm1.anchor);
	Log_struktura_tm5("   antifona2             file `%s', anchor `%s'\n", t.antifona2.file, t.antifona2.anchor);
	Log_struktura_tm5("   zalm2                 file `%s', anchor `%s'\n", t.zalm2.file, t.zalm2.anchor);
	Log_struktura_tm5("   antifona3             file `%s', anchor `%s'\n", t.antifona3.file, t.antifona3.anchor);
	Log_struktura_tm5("   zalm3                 file `%s', anchor `%s'\n", t.zalm3.file, t.zalm3.anchor);
	Log_struktura_tm5("   kresponz              file `%s', anchor `%s'\n", t.kresponz.file, t.kresponz.anchor);
	Log_struktura_tm5("   1. citanie            file `%s', anchor `%s'\n", t.citanie1.file, t.citanie1.anchor);
	Log_struktura_tm5("   2. citanie            file `%s', anchor `%s'\n", t.citanie2.file, t.citanie2.anchor);
	Log_struktura_tm5("   citanie_spomprivileg  file `%s', anchor `%s'\n", t.citanie_spomprivileg.file, t.citanie_spomprivileg.anchor);
	Log_struktura_tm5("   ant_chval             file `%s', anchor `%s'\n", t.ant_chval.file, t.ant_chval.anchor);
	Log_struktura_tm5("   chval1                file `%s', anchor `%s'\n", t.chval1.file, t.chval1.anchor);
	Log_struktura_tm5("   chval2                file `%s', anchor `%s'\n", t.chval2.file, t.chval2.anchor);
	Log_struktura_tm5("   chval3                file `%s', anchor `%s'\n", t.chval3.file, t.chval3.anchor);
	Log_struktura_tm5("   evanjelium            file `%s', anchor `%s'\n", t.evanjelium.file, t.evanjelium.anchor);
	Log_struktura_tm5("   modlitba              file `%s', anchor `%s'\n", t.modlitba.file, t.modlitba.anchor);
}

void Log_filename_anchor(_struct_anchor_and_file af){
	Log("file `%s', anchor `%s'\n", af.file, af.anchor);
}

//---------------------------------------------------------------------
/* popis:
 *
 * int _struct_dm::spolcast obsahuje zakodovane data pre svatych o tom,
 * z akej spolocnej casti sa ma modlit;
 * obsahuje max. 3 spolocne casti vo formate
 *
 * spolcast == a1 + a2 * MAX + a3 * MAX * MAX,
 *
 * kde
 * - MAX je MAX_MODL_SPOL_CAST,
 * - a1, a2, a3 su konstanty MODL_SPOL_CAST_...
 *   (v poradi a1, ak druhe tak a2, ak tretie tak aj a3)
 *
 * _encode_..., _decode_spol_cast(); robia tuto konverziu
 *
 */
int _encode_spol_cast(short int a1, short int a2, short int a3){
	return(a1 + a2 * MAX_MODL_SPOL_CAST + a3 * MAX_MODL_SPOL_CAST * MAX_MODL_SPOL_CAST);
}
int _encode_spol_cast(short int a1, short int a2){
	return _encode_spol_cast(a1, a2, MODL_SPOL_CAST_NEURCENA);
}
int _encode_spol_cast(short int a1){
	return _encode_spol_cast(a1, MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA);
}
_struct_sc _decode_spol_cast(int spolc){
	_struct_sc ret;
	ret.a3 = spolc DIV(MAX_MODL_SPOL_CAST * MAX_MODL_SPOL_CAST);
	ret.a2 = (spolc MOD(MAX_MODL_SPOL_CAST * MAX_MODL_SPOL_CAST)) DIV MAX_MODL_SPOL_CAST;
	ret.a1 = (spolc MOD(MAX_MODL_SPOL_CAST * MAX_MODL_SPOL_CAST)) MOD MAX_MODL_SPOL_CAST;
	return ret;
}

void strcat_str_modl_opt_bit_order(char str_to_append[SMALL], short opt, short bit_order){

	char str[SMALL] = STR_EMPTY;

	switch (opt)
	{
	case OPT_0_SPECIALNE:
		if (bit_order < POCET_OPT_0_SPECIALNE){
			switch (bit_order)
			{
			case -2: mystrcpy(str, STR_MODL_OPT_0, SMALL); break; // no bit = ordinary option string | USE_STR_MODL_OPT
			case -1: mystrcpy(str, STR_MODL_OPTF_0, SMALL); break; // no bit = force option string | USE_STR_MODL_OPTF
			case 0: mystrcpy(str, STR_MODL_OPTF_0_VERSE, SMALL); break; // BIT_OPT_0_VERSE
			case 1: mystrcpy(str, STR_MODL_OPTF_0_REF, SMALL); break; // BIT_OPT_0_REFERENCIE
			case 2: mystrcpy(str, STR_MODL_OPTF_0_CIT, SMALL); break; // BIT_OPT_0_CITANIA
			case 3: mystrcpy(str, STR_MODL_OPTF_0_ZJAV_NED, SMALL); break; // BIT_OPT_0_ZJAVENIE_PANA_NEDELA
			case 4: mystrcpy(str, STR_MODL_OPTF_0_NAN_NED, SMALL); break; // BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA
			case 5: mystrcpy(str, STR_MODL_OPTF_0_TK_NED, SMALL); break; // BIT_OPT_0_TELAKRVI_NEDELA
			case 6: mystrcpy(str, STR_MODL_OPTF_0_FONT_NORMAL, SMALL); break; // BIT_OPT_0_FONT_NORMAL
			case 7: mystrcpy(str, STR_MODL_OPTF_0_BUTTONS_ORDER, SMALL); break; // BIT_OPT_0_BUTTONS_ORDER
			case 8: mystrcpy(str, STR_MODL_OPTF_0_BLIND_FRIENDLY, SMALL); break; // BIT_OPT_0_BLIND_FRIENDLY
			}
		}
		break;
	case OPT_1_CASTI_MODLITBY:
		if (bit_order < POCET_OPT_1_CASTI_MODLITBY){
			switch (bit_order)
			{
			case -2: mystrcpy(str, STR_MODL_OPT_1, SMALL); break; // no bit = ordinary option string | USE_STR_MODL_OPT
			case -1: mystrcpy(str, STR_MODL_OPTF_1, SMALL); break; // no bit = force option string | USE_STR_MODL_OPTF
			case 0: mystrcpy(str, STR_MODL_OPTF_1_TD, SMALL); break; // BIT_OPT_1_TEDEUM
			case 1: mystrcpy(str, STR_MODL_OPTF_1_RUB, SMALL); break; // BIT_OPT_1_RUBRIKY
			case 2: mystrcpy(str, STR_MODL_OPTF_1_CHV, SMALL); break; // BIT_OPT_1_CHVALOSPEVY
			case 3: mystrcpy(str, STR_MODL_OPTF_1_SL, SMALL); break; // BIT_OPT_1_SLAVA_OTCU
			case 4: mystrcpy(str, STR_MODL_OPTF_1_OT, SMALL); break; // BIT_OPT_1_OTCENAS
			case 5: mystrcpy(str, STR_MODL_OPTF_1_MCD_DOPLNKOVA, SMALL); break; // BIT_OPT_1_MCD_DOPLNKOVA
			case 6: mystrcpy(str, STR_MODL_OPTF_1_VIGILIA, SMALL); break; // BIT_OPT_1_PC_VIGILIA
			case 7: mystrcpy(str, STR_MODL_OPTF_1_SPOMIENKA_SPOL_CAST, SMALL); break; // BIT_OPT_1_SPOMIENKA_SPOL_CAST
			case 8: mystrcpy(str, STR_MODL_OPTF_1_PLNE_RESP, SMALL); break; // BIT_OPT_1_PLNE_RESP
			case 9: mystrcpy(str, STR_MODL_OPTF_1_ZALM95, SMALL); break; // BIT_OPT_1_ZALM95
			case 10: mystrcpy(str, STR_MODL_OPTF_1_PROSBY_ZVOLANIE, SMALL); break; // BIT_OPT_1_PROSBY_ZVOLANIE
			case 11: mystrcpy(str, STR_MODL_OPTF_1_SKRY_POPIS, SMALL); break; // BIT_OPT_1_SKRY_POPIS
			case 12: mystrcpy(str, STR_MODL_OPTF_1_ZOBRAZ_SPOL_CAST, SMALL); break; // BIT_OPT_1_ZOBRAZ_SPOL_CAST
			case 13: mystrcpy(str, STR_MODL_OPTF_1_VESP_KRATSIE_PROSBY, SMALL); break; // BIT_OPT_1_VESP_KRATSIE_PROSBY
			case 14: mystrcpy(str, STR_MODL_OPTF_1_MCD_ZALTAR_TRI, SMALL); break; // BIT_OPT_1_MCD_ZALTAR_TRI
			}
		}
		break;
	case OPT_2_HTML_EXPORT:
		if (bit_order < POCET_OPT_2_HTML_EXPORT){
			switch (bit_order)
			{
			case -2: mystrcpy(str, STR_MODL_OPT_2, SMALL); break; // no bit = ordinary option string | USE_STR_MODL_OPT
			case -1: mystrcpy(str, STR_MODL_OPTF_2, SMALL); break; // no bit = force option string | USE_STR_MODL_OPTF
			case 0: mystrcpy(str, STR_MODL_OPTF_2_ISO_DATUM, SMALL); break; // BIT_OPT_2_ISO_DATUM
			case 1: mystrcpy(str, STR_MODL_OPTF_2_PRVE_VESPERY, SMALL); break; // BIT_OPT_2_BUTTON_PRVE_VESPERY
			case 2: mystrcpy(str, STR_MODL_OPTF_2_FONT_FAMILY, SMALL); break; // BIT_OPT_2_FONT_FAMILY
			case 3: mystrcpy(str, STR_MODL_OPTF_2_FONT_NAME_CHOOSER, SMALL); break; // BIT_OPT_2_FONT_NAME_CHOOSER
				// case 4: mystrcpy(str, STR_MODL_OPTF_2_FONT_SIZE, SMALL); break; // BIT_OPT_2_FONT_SIZE_CHOOSER
			case 5: mystrcpy(str, STR_MODL_OPTF_2_NAVIGATION, SMALL); break; // BIT_OPT_2_NAVIGATION
			case 6: mystrcpy(str, STR_MODL_OPTF_2_TEXT_WRAP, SMALL); break; // BIT_OPT_2_TEXT_WRAP
			case 7: mystrcpy(str, STR_MODL_OPTF_2_BUTTONY_USPORNE, SMALL); break; // BIT_OPT_2_BUTTONY_USPORNE
			case 8: mystrcpy(str, STR_MODL_OPTF_2_NOCNY_REZIM, SMALL); break; // BIT_OPT_2_NOCNY_REZIM
			case 9: mystrcpy(str, STR_MODL_OPTF_2_ROZNE_MOZNOSTI, SMALL); break; // BIT_OPT_2_ROZNE_MOZNOSTI
			case 10: mystrcpy(str, STR_MODL_OPTF_2_HIDE_NAVIG_BUTTONS, SMALL); break; // BIT_OPT_2_HIDE_NAVIG_BUTTONS
			case 11: mystrcpy(str, STR_MODL_OPTF_2_HIDE_KALENDAR, SMALL); break; // BIT_OPT_2_HIDE_KALENDAR
			case 12: mystrcpy(str, STR_MODL_OPTF_2_HIDE_OPTIONS1, SMALL); break; // BIT_OPT_2_HIDE_OPTIONS1
			case 13: mystrcpy(str, STR_MODL_OPTF_2_HIDE_OPTIONS2, SMALL); break; // BIT_OPT_2_HIDE_OPTIONS2
			case 14: mystrcpy(str, STR_MODL_OPTF_2_ALTERNATIVES, SMALL); break; // BIT_OPT_2_ALTERNATIVES
			case 15: mystrcpy(str, STR_MODL_OPTF_2_SHOW_DEFAULT_CALENDAR, SMALL); break; // BIT_OPT_2_SHOW_DEFAULT_CALENDAR
			}
		}
		break;
	case OPT_3_SPOLOCNA_CAST:
		switch (bit_order)
		{
		case -2: mystrcpy(str, STR_MODL_OPT_3, SMALL); break; // no bit = ordinary option string | USE_STR_MODL_OPT
		case -1: mystrcpy(str, STR_MODL_OPTF_3, SMALL); break; // no bit = force option string | USE_STR_MODL_OPTF
		}
		break;
	case OPT_4_OFFLINE_EXPORT:
		if (bit_order < POCET_OPT_4_OFFLINE_EXPORT){
			switch (bit_order)
			{
			case -2: mystrcpy(str, STR_MODL_OPT_4, SMALL); break; // no bit = ordinary option string | USE_STR_MODL_OPT
			case -1: mystrcpy(str, STR_MODL_OPTF_4, SMALL); break; // no bit = force option string | USE_STR_MODL_OPTF
			}
		}
		break;
	case OPT_5_ALTERNATIVES:
		if (bit_order < POCET_OPT_5_ALTERNATIVES){
			switch (bit_order)
			{
			case -2: mystrcpy(str, STR_MODL_OPT_5, SMALL); break; // no bit = ordinary option string | USE_STR_MODL_OPT
			case -1: mystrcpy(str, STR_MODL_OPTF_5, SMALL); break; // no bit = force option string | USE_STR_MODL_OPTF
			case 0: mystrcpy(str, STR_MODL_OPTF_5_HYMNUS_KOMPL, SMALL); break; // BIT_OPT_5_HYMNUS_KOMPL
			case 1: mystrcpy(str, STR_MODL_OPTF_5_HYMNUS_PC, SMALL); break; // BIT_OPT_5_HYMNUS_PC
			case 2: mystrcpy(str, STR_MODL_OPTF_5_HYMNUS_MCD_PREDPOL, SMALL); break; // BIT_OPT_5_HYMNUS_MCD_PREDPOL
			case 3: mystrcpy(str, STR_MODL_OPTF_5_HYMNUS_MCD_NAPOL, SMALL); break; // BIT_OPT_5_HYMNUS_MCD_NAPOL
			case 4: mystrcpy(str, STR_MODL_OPTF_5_HYMNUS_MCD_POPOL, SMALL); break; // BIT_OPT_5_HYMNUS_MCD_POPOL
			case 5: mystrcpy(str, STR_MODL_OPTF_5_DOPLNK_PSALM_122_129, SMALL); break; // BIT_OPT_5_DOPLNK_PSALM_122_129
			case 6: mystrcpy(str, STR_MODL_OPTF_5_DOPLNK_PSALM_127_131, SMALL); break; // BIT_OPT_5_DOPLNK_PSALM_127_131
			case 7: mystrcpy(str, STR_MODL_OPTF_5_DOPLNK_PSALM_126_129, SMALL); break; // BIT_OPT_5_DOPLNK_PSALM_126_129
			case 8: mystrcpy(str, STR_MODL_OPTF_5_HYMNUS_VN_PC, SMALL); break; // BIT_OPT_5_HYMNUS_VN_PC
			case 9: mystrcpy(str, STR_MODL_OPTF_5_HYMNUS_VN_RCH, SMALL); break; // BIT_OPT_5_HYMNUS_VN_RCH
			case 10: mystrcpy(str, STR_MODL_OPTF_5_HYMNUS_VN_VESP, SMALL); break; // BIT_OPT_5_HYMNUS_VN_VESP
			case 11: mystrcpy(str, STR_MODL_OPTF_5_HYMNUS_1VESP, SMALL); break; // BIT_OPT_5_HYMNUS_1VESP
			case 12: mystrcpy(str, STR_MODL_OPTF_5_POPOL_STREDA_PSALMODIA, SMALL); break; // BIT_OPT_5_POPOL_STREDA_PSALMODIA
			case 13: mystrcpy(str, STR_MODL_OPTF_5_CZ_HYMNY_VYBER, SMALL); break; // BIT_OPT_5_CZ_HYMNY_VYBER
			}
		}
		break;
	}// switch

	strcat(str_to_append, str);
}

#endif // __LITURGIA_CPP_


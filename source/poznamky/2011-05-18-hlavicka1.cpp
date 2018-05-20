void hlavicka(char *title, short int level, short int spec){
	Log("hlavicka() -- zaËiatok...\n");
	_local_modlitba = _global_modlitba;
	if((_local_modlitba == MODL_PRVE_VESPERY) || (_local_modlitba == MODL_DRUHE_VESPERY))
		_local_modlitba = MODL_VESPERY;
	if((_local_modlitba == MODL_PRVE_KOMPLETORIUM) || (_local_modlitba == MODL_DRUHE_KOMPLETORIUM))
		_local_modlitba = MODL_KOMPLETORIUM;

	/* 2009-08-04: viackr·t sa pri exporte modlitby do HTML exportovala hlaviËka; pridan· kontrola */
	if(_global_hlavicka_Export > 0)
		return;
	_global_hlavicka_Export++;
	/* 
	 * 2003-07-01, pridane pripadne citanie zo suboru
	 * 2008-08-08: ËÌtanie zo s˙boru odstr·nenÈ
	 */
	const char *nazov_css_suboru;
	if(_global_css == CSS_UNDEF)
		nazov_css_suboru = nazov_css[CSS_breviar_sk];
	else
		nazov_css_suboru = nazov_css[_global_css];

	/*
	 * 2011-05-05: nastavenie font-family
	 *             zatiaæ len pevnÈ reùazce; Ëasom moûno bude premenn· pre n·zov fontu
	 * 2011-05-06: doplnenÈ: najprv sa testuje nastavenie _global_font; n·sledne sa prÌpadne nastavia defaulty
	 */
	if((_global_font == FONT_UNDEF) || (_global_font == FONT_CHECKBOX)){
		if((_global_opt[OPT_2_HTML_EXPORT] & BIT_OPT_2_FONT_FAMILY) == BIT_OPT_2_FONT_FAMILY){
			mystrcpy(_global_css_font_family, DEFAULT_FONT_FAMILY_SANS_SERIF, MAX_STR);
		}
		else{
			mystrcpy(_global_css_font_family, DEFAULT_FONT_FAMILY_SERIF, MAX_STR);
		}
	}/* (_global_font == FONT_UNDEF)  || (_global_font == FONT_CHECKBOX) */
	else if(_global_font == FONT_CSS){
		mystrcpy(_global_css_font_family, DEFAULT_FONT_FAMILY_INHERIT, MAX_STR);
	}/* (_global_font == FONT_CSS) */
	else{
		mystrcpy(_global_css_font_family, nazov_fontu[_global_font], MAX_STR);
	}/* else */
	/*
	 * 2011-05-13: doplnenÈ: nastavenie font-size
	 */
	if(_global_font_size == FONT_SIZE_UNDEF){
		mystrcpy(_global_css_font_size, STR_EMPTY, MAX_STR);
	}/* (_global_font_size == FONT_SIZE_UNDEF) */
	else if(_global_font_size == FONT_SIZE_CSS){
		mystrcpy(_global_css_font_size, DEFAULT_FONT_SIZE_INHERIT, MAX_STR);
	}/* (_global_font_size == FONT_SIZE_CSS) */
	else{
		mystrcpy(_global_css_font_size, nazov_font_size_css[_global_font_size], MAX_STR);
	}/* else */

	if(bol_content_type_text_html == NIE){
#if defined(OS_linux)
		Export("Content-type: text/html\n");
		Export("\n");
#elif defined(OS_Windows_Ruby)
		Export("Content-type: text/html\n");
		Export("\n");
#endif
		bol_content_type_text_html = ANO;
	}
	Log("creating header...\n");
	/* 2003-07-15, zmenene na hlavicku pre css-ko; zrusene <style>
	 * 2008-08-08: pridanÈ dynamicky css-ko
	 * 2010-02-15: statickÈ texty do konöt·nt
	 * 2011-05-18: charset sa nastavÌ podæa jazyka
	 */
	Export((char *)html_header_1, charset_jazyka[_global_jazyk]);
#ifdef	EXPORT_CMDLINE_CSS
	// pre command-line pouûitie (aj pre batch mÛd): "./breviar.css" resp. ".\breviar.css"
	/* 2009-08-03: level oznaËuje poËet adres·rov, o ktorÈ je treba Ìsù "hore" (pre mesaËn˝ export) */
	if(level == 0 && _global_opt_batch_monthly == ANO)
		level = 1;
	if(level < 0 || level > 5)
		level = 0;
	if(level == 0)
		Export(".");
	else{
		while(level > 1){
			Export("..");
			Export(STR_PATH_SEPARATOR_HTML);
			level--;
		}
		Export("..");
	}
	Export(STR_PATH_SEPARATOR_HTML);
#else
	// pre web-pouûitie (aj pre ruby): "/breviar.css"
	Export("/");
#endif
	Export("%s\">\n", nazov_css_suboru); // n·zov css s˙boru
	Export("<title>%s</title>\n", title);
	Export("</head>\n\n");
	/* 2011-05-05: pridanie font-family 
	 * 2011-05-06: font sa neprid·va vûdy
	 */
	Export("<body");
	if((_global_font != FONT_CSS) || (_global_font_size != FONT_SIZE_CSS)){
		Export(" style=\"");
		if(_global_font != FONT_CSS){
			Export("font-family: %s", _global_css_font_family);
		}
		if(_global_font_size != FONT_SIZE_CSS){
			if(_global_font != FONT_CSS){
				Export("; ");
			}
			Export("font-size: %s", _global_css_font_size);
		}
		Export("\"");
	}
	/* 2010-02-15: kvÙli öpeci·lnemu "zoznam.htm" */
	if(spec == 1){
		Export(" onLoad=\"fn_aktualne(0,0,0)\"");
	}
	Export(">\n");

	/* 2010-02-15: doplnenÈ predoöl· a nasledovn· modlitba */
	if(_global_opt_batch_monthly == ANO && query_type != PRM_BATCH_MODE){
		Export("<center>\n");
		pismeno_modlitby = CHAR_MODL_NEURCENA;
		if((_local_modlitba < MODL_NEURCENA) && (_local_modlitba >= MODL_INVITATORIUM))
			pismeno_modlitby = char_modlitby[_local_modlitba];
		sprintf(ext, "%c", pismeno_modlitby);
		strcat(ext, ".htm");
		Export("<p>");
		// << prev
		mystrcpy(file_name_pom, FILE_EXPORT, MAX_STR);
		ptr = strstr(file_name_pom, ext);
		if((_local_modlitba < MODL_NEURCENA) && (_local_modlitba > MODL_INVITATORIUM)){
			if(ptr != NULL){
				sprintf(pismeno_prev, "%c", char_modlitby[_local_modlitba - 1]);
				strncpy(ptr, pismeno_prev, 1);
			}
			Export("<a href=\"%s\">", file_name_pom);
			Export((char *)html_text_batch_Prev[_global_jazyk]);
			Export(" ");
			Export((char *)nazov_modlitby(_local_modlitba - 1));
			Export("</a>");
		}
		// |
		Export(" | ");
		// ^ hore
		Export("<a href=\".%s%s\">", STR_PATH_SEPARATOR_HTML, _global_export_navig_hore); // v tom istom adres·ri
		Export((char *)html_text_batch_Back[_global_jazyk]);
		Export("</a>");
		// |
		Export(" | ");
		// >> next
		mystrcpy(file_name_pom, FILE_EXPORT, MAX_STR);
		ptr = strstr(file_name_pom, ext);
		if((_local_modlitba != MODL_NEURCENA) && (_local_modlitba < MODL_KOMPLETORIUM)){
			if(ptr != NULL){
				sprintf(pismeno_next, "%c", char_modlitby[_local_modlitba + 1]);
				strncpy(ptr, pismeno_next, 1);
			}
			Export("<a href=\"%s\">", file_name_pom);
			Export((char *)nazov_modlitby(_local_modlitba + 1));
			Export(" ");
			Export((char *)html_text_batch_Next[_global_jazyk]);
			Export("</a>");
		}
		Export("</p>");
		Export("</center>\n");
	}/* << predoöl· | ^ hore | nasledovn· >> */
	Log("hlavicka() -- koniec.\n");
	return;
}/* hlavicka() */

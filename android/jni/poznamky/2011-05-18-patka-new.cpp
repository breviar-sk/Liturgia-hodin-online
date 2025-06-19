void _patka(FILE * expt){
	Log("_patka() -- za�iatok...\n");
	_local_modlitba = _global_modlitba;
	if((_local_modlitba == MODL_PRVE_VESPERY) || (_local_modlitba == MODL_DRUHE_VESPERY))
		_local_modlitba = MODL_VESPERY;
	if((_local_modlitba == MODL_PRVE_KOMPLETORIUM) || (_local_modlitba == MODL_DRUHE_KOMPLETORIUM))
		_local_modlitba = MODL_KOMPLETORIUM;

	time_t t;
	struct tm dnes;
	int baserok = 1999;
#define ROK 5
	char rok[ROK];

	time(&t);

	/* konvertuje date/time na strukturu */
	dnes = *localtime(&t);
	/* upravenie time_check structure with the data */
	dnes.tm_year = dnes.tm_year + 1900;
	dnes.tm_yday = dnes.tm_yday + 1;
	mystrcpy(rok, STR_EMPTY, ROK);
	if(dnes.tm_year > baserok){
		sprintf(rok, "-%d", dnes.tm_year);
	}

	/* 2010-02-15: vlo�en� "^ hore" pod�a hlavicka(); doplnen� predo�l� a nasledovn� modlitba */
	if(_global_opt_batch_monthly == ANO && query_type != PRM_BATCH_MODE){
		Export_to_file(expt, "<center>\n");
		pismeno_modlitby = CHAR_MODL_NEURCENA;
		if((_local_modlitba < MODL_NEURCENA) && (_local_modlitba >= MODL_INVITATORIUM))
			pismeno_modlitby = char_modlitby[_local_modlitba];
		sprintf(ext, "%c", pismeno_modlitby);
		strcat(ext, ".htm");
		Export_to_file(expt, "<p>");
		// << prev
		mystrcpy(file_name_pom, FILE_EXPORT, MAX_STR);
		ptr = strstr(file_name_pom, ext);
		if((_local_modlitba < MODL_NEURCENA) && (_local_modlitba > MODL_INVITATORIUM)){
			if(ptr != NULL){
				sprintf(pismeno_prev, "%c", char_modlitby[_local_modlitba - 1]);
				strncpy(ptr, pismeno_prev, 1);
			}
			Export_to_file(expt, "<a href=\"%s\">", file_name_pom);
			Export_to_file(expt, (char *)html_text_batch_Prev[_global_jazyk]);
			Export_to_file(expt, " ");
			Export_to_file(expt, (char *)nazov_modlitby(_local_modlitba - 1));
			Export_to_file(expt, "</a>");
		}
		// |
		Export_to_file(expt, " | ");
		// ^ hore
		Export_to_file(expt, "<a href=\".%s%s\">", STR_PATH_SEPARATOR_HTML, _global_export_navig_hore); // v tom istom adres�ri
		Export_to_file(expt, (char *)html_text_batch_Back[_global_jazyk]);
		Export_to_file(expt, "</a>");
		// |
		Export_to_file(expt, " | ");
		// >> next
		mystrcpy(file_name_pom, FILE_EXPORT, MAX_STR);
		ptr = strstr(file_name_pom, ext);
		if((_local_modlitba != MODL_NEURCENA) && (_local_modlitba < MODL_KOMPLETORIUM)){
			if(ptr != NULL){
				sprintf(pismeno_next, "%c", char_modlitby[_local_modlitba + 1]);
				strncpy(ptr, pismeno_next, 1);
			}
			Export_to_file(expt, "<a href=\"%s\">", file_name_pom);
			Export_to_file(expt, (char *)nazov_modlitby(_local_modlitba + 1));
			Export_to_file(expt, " ");
			Export_to_file(expt, (char *)html_text_batch_Next[_global_jazyk]);
			Export_to_file(expt, "</a>");
		}
		Export_to_file(expt, "</p>");
		Export_to_file(expt, "</center>\n");
	}/* << predo�l� | ^ hore | nasledovn� >> */

	Export_to_file(expt, (char *)html_footer_1);

	if(_global_opt_batch_monthly == ANO && query_type != PRM_BATCH_MODE){
		mystrcpy(html_mail_label, html_mail_label_short, MAX_MAIL_LABEL);
	}
	else
	{
		mystrcpy(html_mail_label, html_mail_label_long, MAX_MAIL_LABEL);
	}

	Export("\n");
	/* 2010-02-15: cel� zapozn�mkovan� */
	if(1 == 1 || _global_opt_batch_monthly == ANO && query_type != PRM_BATCH_MODE){
		Export_to_file(expt, "<"HTML_P_PATKA">\n");
	}
	else{
		Export_to_file(expt, "<"HTML_P_PATKA">%s\n", gpage[_global_jazyk]);
		/* Export_to_file(expt, "(%s). ", ctime(&t) + 4); */
		/* 2008-12-22: odvetven� - pre commandline export (do s�boru) sa netla�� �asov� zlo�ka, kedy bolo HTML generovan� */
#if defined(EXPORT_TO_FILE)
		Export_to_file(expt, (char *)datum_template[_global_jazyk],
			dnes.tm_mday,
			nazov_mesiaca(dnes.tm_mon) /* nm[dnes.tm_mon] */,
			dnes.tm_year
			);
#else
		Export_to_file(expt, (char *)datum_cas_template[_global_jazyk],
			dnes.tm_mday,
			nazov_mesiaca(dnes.tm_mon) /* nm[dnes.tm_mon] */,
			dnes.tm_year,
			dnes.tm_hour,
			dnes.tm_min
			// , dnes.tm_sec
			);
#endif
		Export_to_file(expt, ". ");

		/* nezabudni zmenit #define BUILD_DATE v mydefs.h (2003-07-15) */
		Export_to_file(expt, (char *)build_template[_global_jazyk], BUILD_DATE);

		/* zapoznamkovane, 2003-06-30 */
		/* Export_to_file(expt, "K�dovanie Windows-1250 (Central European).\n"); */
		Export_to_file(expt, "<br>\n");
	}

	/* pridana stranka cfg_HTTP_ADDRESS_default, 12/04/2000A.D. */
	Export_to_file(expt, "<"HTML_LINK_NORMAL" href=\"%s\" target=\"_top\">%s</a>\n", cfg_HTTP_ADDRESS_default, cfg_HTTP_DISPLAY_ADDRESS_default);
	Export_to_file(expt, "&#169; %d%s <"HTML_LINK_NORMAL" href=\"mailto:%s\">%s</a>\n", baserok, rok, cfg_MAIL_ADDRESS_default, html_mail_label);

	Export_to_file(expt, "</p>\n"); /* pridane kvoli tomu, ze cele to bude <p class="patka">, 2003-07-02 */

	Export_to_file(expt, "</body>\n</html>\n");
	Log("_patka() -- koniec.\n");
	return;
}/* _patka() */


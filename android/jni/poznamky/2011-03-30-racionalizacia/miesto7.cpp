	/* 2006-08-01: pridanÈ odovzdanie parametra pre jazyk */
	if(_global_jazyk != JAZYK_SK){
		sprintf(pom2, HTML_AMPERSAND"%s=%s", STR_JAZYK, skratka_jazyka[_global_jazyk]);
		Log("\tBudem prilepovaù aj jazyk: `%s' (2006-07-31)\n", pom2);
	}

	/* 2010-08-04: pridanÈ odovzdanie parametra pre kalend·r 
	 * 2010-09-14: podmienka opraven·; ak nie je kalend·r urËen˝ resp. je vöeobecn˝ pre dan˝ jazyk, nie je potrebnÈ ho exportovaù
	 */
	if(PODMIENKA_EXPORTOVAT_KALENDAR){
		sprintf(pom3, HTML_AMPERSAND"%s=%s", STR_KALENDAR, skratka_kalendara[_global_kalendar]);
		strcat(pom2, pom3);
		Log("\tPrilepil som aj kalend·r: `%s' (2010-08-04)\n", pom3);
	}
	else{
		Log("\tNetreba prilepiù kalend·r (jazyk == %s, kalend·r == %s)\n", skratka_jazyka[_global_jazyk], skratka_kalendara[_global_kalendar]);
	}

	/* 2006-08-01: pridanÈ odovzdanie parametra pre css */
	if(_global_css != CSS_breviar_sk){
		sprintf(pom3, HTML_AMPERSAND"%s=%s", STR_CSS, skratka_css[_global_css]);
		strcat(pom2, pom3);
		Log("\tBudem prilepovaù aj css: `%s' (2008-08-08)\n", pom3);
	}

	/* 2011-01-26: pridanÈ odovzdanie parametrov pre options1 atÔ. */
	if(_global_opt1 != CFG_OPTION1_DEFAULT){
		sprintf(pom3, HTML_AMPERSAND"%s=%d", STR_MODL_OPT1, _global_opt1);
		strcat(pom2, pom3);
		Log("\tPrilepil som aj opt1: `%s' (2011-01-26)\n", pom3);
	}
	if(_global_opt2 != CFG_OPTION2_DEFAULT){
		sprintf(pom3, HTML_AMPERSAND"%s=%d", STR_MODL_OPT2, _global_opt2);
		strcat(pom2, pom3);
		Log("\tPrilepil som aj opt2: `%s' (2011-01-26)\n", pom3);
	}
	if(_global_opt4 != CFG_OPTION4_DEFAULT){
		sprintf(pom3, HTML_AMPERSAND"%s=%d", STR_MODL_OPT4, _global_opt4);
		strcat(pom2, pom3);
		Log("\tPrilepil som aj opt4: `%s' (2011-01-26)\n", pom3);
	}
	if(_global_opt5 != CFG_OPTION5_DEFAULT){
		sprintf(pom3, HTML_AMPERSAND"%s=%d", STR_MODL_OPT5, _global_opt5);
		strcat(pom2, pom3);
		Log("\tPrilepil som aj opt5: `%s' (2011-01-26)\n", pom3);
	}
	if(_global_opt8 != CFG_OPTION8_DEFAULT){
		sprintf(pom3, HTML_AMPERSAND"%s=%d", STR_MODL_OPT8, _global_opt8);
		strcat(pom2, pom3);
		Log("\tPrilepil som aj opt8: `%s' (2011-03-23)\n", pom3);
	}
	if(_global_opt9 != CFG_OPTION9_DEFAULT){
		sprintf(pom3, HTML_AMPERSAND"%s=%d", STR_MODL_OPT9, _global_opt9);
		strcat(pom2, pom3);
		Log("\tPrilepil som aj opt9: `%s' (2011-03-25)\n", pom3);
	}


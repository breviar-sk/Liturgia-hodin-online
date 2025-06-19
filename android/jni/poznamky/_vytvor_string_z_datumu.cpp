char *_vytvor_string_z_datumu(short int den, short int mesiac, short int rok, short int _case, short int typ){
	/* 2007-03-20: spôsob výpisu dátumu pod¾a jazyka 
	 * 2011-05-11: vytiahnutý z _vytvor_global_pom_str() ako samostatná funkcia
	 */
	char pom[MAX_STR] = EMPTY_STR;
	mystrcpy(_global_pom_str, EMPTY_STR, MAX_STR);
	if(_global_jazyk == JAZYK_LA){
		sprintf(pom, "%d. %s", den, nazov_Mesiaca_gen(mesiac - 1));
		if(typ == LINK_DEN_MESIAC_ROK){
			/* pridame aj rok */
			strcat(_global_pom_str, pom);
			sprintf(pom, " %d", rok);
		}
	}
	else if(_global_jazyk == JAZYK_EN){
		sprintf(pom, "%s %d", nazov_Mesiaca(mesiac - 1), den);
		if(typ == LINK_DEN_MESIAC_ROK){
			/* pridame aj rok */
			strcat(_global_pom_str, pom);
			sprintf(pom, ", %d", rok);
		}
	}
	/* 2010-05-21: doplnené pre maïarèinu: 1999. augusztus 1. -- http://en.wikipedia.org/wiki/Date_and_time_notation_by_country#Hungary [2010-05-24] */
	else if(_global_jazyk == JAZYK_HU){
		if(typ == LINK_DEN_MESIAC_ROK){
			/* pridáme najprv rok */
			sprintf(pom, "%d. ", rok);
			strcat(_global_pom_str, pom);
			sprintf(pom, "%s %d.", nazov_mesiaca(mesiac - 1), den);
		}
		else{
			sprintf(pom, "%s %d.", nazov_Mesiaca(mesiac - 1), den);
		}
	}
	else{
		/* doterajšie správanie pre slovenèinu a èeštinu */
		switch(_case){
			case CASE_case:
				sprintf(pom, "%d. %s", den, nazov_mesiaca(mesiac - 1));
				break;
			case CASE_Case:
				sprintf(pom, "%d. %s", den, nazov_Mesiaca(mesiac - 1));
				break;
			case CASE_CASE:
				sprintf(pom, "%d. %s", den, nazov_MESIACA(mesiac - 1));
				break;
		}/* switch(_case) */
		if(typ == LINK_DEN_MESIAC_ROK){
			/* pridame aj rok */
			strcat(_global_pom_str, pom);
			sprintf(pom, " %d", rok);
		}
	}
	strcat(_global_pom_str, pom);
	return (_global_pom_str);
}/* _vytvor_string_z_datumu() */


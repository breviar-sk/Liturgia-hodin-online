	/* premenn· MODL_OPT1 (nepovinn·)
	 * 
	 * 2006-08-01: dynamickÈ zisùovanie hodnÙt parametrov */
	i = 0; /* param[0] by mal sÌce obsahovaù query type, ale radöej kontrolujeme od 0 */
	Log("pok˙öam sa zistiù hodnotu parametra %s...\n", STR_MODL_OPT1);
	while((equalsi(pom_MODL_OPT[1], STR_EMPTY)) && (i < pocet)){
		// Log("...parameter %i (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if(equals(param[i].name, STR_MODL_OPT1)){
			/* ide o parameter STR_MODL_OPT1 */
			mystrcpy(pom_MODL_OPT[1], param[i].val, SMALL);
			Log("hodnota parametra %s je %s.\n", STR_MODL_OPT1, pom_MODL_OPT[1]);
		}
		i++;
	}
	if(equalsi(pom_MODL_OPT[1], STR_EMPTY)){
		Log("Nebola zadan· premenn· %s (nevadÌ).\n", STR_MODL_OPT1);
	}

	/* premenn· MODL_OPT2 (nepovinn·)
	 * 
	 * 2006-08-01: dynamickÈ zisùovanie hodnÙt parametrov */
	i = 0; /* param[0] by mal sÌce obsahovaù query type, ale radöej kontrolujeme od 0 */
	Log("pok˙öam sa zistiù hodnotu parametra %s...\n", STR_MODL_OPT2);
	while((equalsi(pom_MODL_OPT[2], STR_EMPTY)) && (i < pocet)){
		// Log("...parameter %i (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if(equals(param[i].name, STR_MODL_OPT2)){
			/* ide o parameter STR_MODL_OPT2 */
			mystrcpy(pom_MODL_OPT[2], param[i].val, SMALL);
			Log("hodnota parametra %s je %s.\n", STR_MODL_OPT2, pom_MODL_OPT[2]);
		}
		i++;
	}
	if(equalsi(pom_MODL_OPT[2], STR_EMPTY)){
		Log("Nebola zadan· premenn· %s (nevadÌ).\n", STR_MODL_OPT2);
	}
	
	/* premenn· MODL_OPT3 (nepovinn·)
	 * 
	 * 2006-08-01: dynamickÈ zisùovanie hodnÙt parametrov */
	i = 0; /* param[0] by mal sÌce obsahovaù query type, ale radöej kontrolujeme od 0 */
	Log("pok˙öam sa zistiù hodnotu parametra %s...\n", STR_MODL_OPT3);
	while((equalsi(pom_MODL_OPT[3], STR_EMPTY)) && (i < pocet)){
		// Log("...parameter %i (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if(equals(param[i].name, STR_MODL_OPT3)){
			/* ide o parameter STR_MODL_OPT3 */
			mystrcpy(pom_MODL_OPT[3], param[i].val, SMALL);
			Log("hodnota parametra %s je %s.\n", STR_MODL_OPT3, pom_MODL_OPT[3]);
		}
		i++;
	}
	if(equalsi(pom_MODL_OPT[3], STR_EMPTY)){
		Log("Nebola zadan· premenn· %s (nevadÌ).\n", STR_MODL_OPT3);
	}
	
	/* premenn· MODL_OPT4 (nepovinn·)
	 * 
	 * 2006-08-01: dynamickÈ zisùovanie hodnÙt parametrov */
	i = 0; /* param[0] by mal sÌce obsahovaù query type, ale radöej kontrolujeme od 0 */
	Log("pok˙öam sa zistiù hodnotu parametra %s...\n", STR_MODL_OPT4);
	while((equalsi(pom_MODL_OPT[4], STR_EMPTY)) && (i < pocet)){
		// Log("...parameter %i (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if(equals(param[i].name, STR_MODL_OPT4)){
			/* ide o parameter STR_MODL_OPT4 */
			mystrcpy(pom_MODL_OPT[4], param[i].val, SMALL);
			Log("hodnota parametra %s je %s.\n", STR_MODL_OPT4, pom_MODL_OPT[4]);
		}
		i++;
	}
	if(equalsi(pom_MODL_OPT[4], STR_EMPTY)){
		Log("Nebola zadan· premenn· %s (nevadÌ).\n", STR_MODL_OPT4);
	}

	/* premenn· MODL_OPT6 (nepovinn·); pridan· podæa OPT1 2007-06-01
	 * 
	 * 2006-08-01: dynamickÈ zisùovanie hodnÙt parametrov */
	i = 0; /* param[0] by mal sÌce obsahovaù query type, ale radöej kontrolujeme od 0 */
	Log("pok˙öam sa zistiù hodnotu parametra %s...\n", STR_MODL_OPT6);
	while((equalsi(pom_MODL_OPT[6], STR_EMPTY)) && (i < pocet)){
		// Log("...parameter %i (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if(equals(param[i].name, STR_MODL_OPT6)){
			/* ide o parameter STR_MODL_OPT6 */
			mystrcpy(pom_MODL_OPT[6], param[i].val, SMALL);
			Log("hodnota parametra %s je %s.\n", STR_MODL_OPT6, pom_MODL_OPT[6]);
		}
		i++;
	}
	if(equalsi(pom_MODL_OPT[6], STR_EMPTY)){
		Log("Nebola zadan· premenn· %s (nevadÌ).\n", STR_MODL_OPT6);
	}

	/* premenn· MODL_OPT7 (nepovinn·); pridan· podæa OPT1 2007-06-01
	 * 
	 * 2006-08-01: dynamickÈ zisùovanie hodnÙt parametrov */
	i = 0; /* param[0] by mal sÌce obsahovaù query type, ale radöej kontrolujeme od 0 */
	Log("pok˙öam sa zistiù hodnotu parametra %s...\n", STR_MODL_OPT7);
	while((equalsi(pom_MODL_OPT[7], STR_EMPTY)) && (i < pocet)){
		// Log("...parameter %i (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if(equals(param[i].name, STR_MODL_OPT7)){
			/* ide o parameter STR_MODL_OPT7 */
			mystrcpy(pom_MODL_OPT[7], param[i].val, SMALL);
			Log("hodnota parametra %s je %s.\n", STR_MODL_OPT7, pom_MODL_OPT[7]);
		}
		i++;
	}
	if(equalsi(pom_MODL_OPT[7], STR_EMPTY)){
		Log("Nebola zadan· premenn· %s (nevadÌ).\n", STR_MODL_OPT7);
	}

	/* premenn· MODL_OPT8 (nepovinn·); pridan· podæa OPT7 2011-03-22
	 * 
	 * 2006-08-01: dynamickÈ zisùovanie hodnÙt parametrov */
	i = 0; /* param[0] by mal sÌce obsahovaù query type, ale radöej kontrolujeme od 0 */
	Log("pok˙öam sa zistiù hodnotu parametra %s...\n", STR_MODL_OPT8);
	while((equalsi(pom_MODL_OPT[8], STR_EMPTY)) && (i < pocet)){
		// Log("...parameter %i (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if(equals(param[i].name, STR_MODL_OPT8)){
			/* ide o parameter STR_MODL_OPT8 */
			mystrcpy(pom_MODL_OPT[8], param[i].val, SMALL);
			Log("hodnota parametra %s je %s.\n", STR_MODL_OPT8, pom_MODL_OPT[8]);
		}
		i++;
	}
	if(equalsi(pom_MODL_OPT[8], STR_EMPTY)){
		Log("Nebola zadan· premenn· %s (nevadÌ).\n", STR_MODL_OPT8);
	}

	/* premenn· MODL_OPT9 (nepovinn·); pridan· podæa OPT8 2011-03-25
	 * 
	 * 2006-09-01: dynamickÈ zisùovanie hodnÙt parametrov */
	i = 0; /* param[0] by mal sÌce obsahovaù query type, ale radöej kontrolujeme od 0 */
	Log("pok˙öam sa zistiù hodnotu parametra %s...\n", STR_MODL_OPT9);
	while((equalsi(pom_MODL_OPT[9], STR_EMPTY)) && (i < pocet)){
		// Log("...parameter %i (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if(equals(param[i].name, STR_MODL_OPT9)){
			/* ide o parameter STR_MODL_OPT9 */
			mystrcpy(pom_MODL_OPT[9], param[i].val, SMALL);
			Log("hodnota parametra %s je %s.\n", STR_MODL_OPT9, pom_MODL_OPT[9]);
		}
		i++;
	}
	if(equalsi(pom_MODL_OPT[9], STR_EMPTY)){
		Log("Nebola zadan· premenn· %s (nevadÌ).\n", STR_MODL_OPT9);
	}

	/* premenn· MODL_OPT0 (nepovinn·); pridan· podæa OPT9 2011-04-04
	 * 
	 * 2006-00-01: dynamickÈ zisùovanie hodnÙt parametrov */
	i = 0; /* param[0] by mal sÌce obsahovaù query type, ale radöej kontrolujeme od 0 */
	Log("pok˙öam sa zistiù hodnotu parametra %s...\n", STR_MODL_OPT0);
	while((equalsi(pom_MODL_OPT[0], STR_EMPTY)) && (i < pocet)){
		// Log("...parameter %i (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if(equals(param[i].name, STR_MODL_OPT0)){
			/* ide o parameter STR_MODL_OPT0 */
			mystrcpy(pom_MODL_OPT[0], param[i].val, SMALL);
			Log("hodnota parametra %s je %s.\n", STR_MODL_OPT0, pom_MODL_OPT[0]);
		}
		i++;
	}
	if(equalsi(pom_MODL_OPT[0], STR_EMPTY)){
		Log("Nebola zadan· premenn· %s (nevadÌ).\n", STR_MODL_OPT0);
	}

	/* premenn· MODL_OPT5 (nepovinn·) -- doplnenÈ 2011-01-26, asi sa na Úu predt˝m zabudlo?... */
	i = 0; /* param[0] by mal sÌce obsahovaù query type, ale radöej kontrolujeme od 0 */
	Log("pok˙öam sa zistiù hodnotu parametra %s...\n", STR_MODL_OPT5);
	while((equalsi(pom_MODL_OPT[5], STR_EMPTY)) && (i < pocet)){
		// Log("...parameter %i (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if(equals(param[i].name, STR_MODL_OPT5)){
			/* ide o parameter STR_MODL_OPT5 */
			mystrcpy(pom_MODL_OPT[5], param[i].val, SMALL);
			Log("hodnota parametra %s je %s.\n", STR_MODL_OPT5, pom_MODL_OPT[5]);
		}
		i++;
	}
	if(equalsi(pom_MODL_OPT[5], STR_EMPTY)){
		Log("Nebola zadan· premenn· %s (nevadÌ).\n", STR_MODL_OPT5);
	}

	/* premenn· MODL_OPTF1 (nepovinn·) */
	i = 0; /* param[0] by mal sÌce obsahovaù query type, ale radöej kontrolujeme od 0 */
	Log("pok˙öam sa zistiù hodnotu parametra %s...\n", STR_MODL_OPTF1);
	while((equalsi(pom_MODL_OPTF[1], STR_EMPTY)) && (i < pocet)){
		// Log("...parameter %i (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if(equals(param[i].name, STR_MODL_OPTF1)){
			/* ide o parameter STR_MODL_OPTF1 */
			mystrcpy(pom_MODL_OPTF[1], param[i].val, SMALL);
			Log("hodnota parametra %s je %s.\n", STR_MODL_OPTF1, pom_MODL_OPTF[1]);
		}
		i++;
	}
	if(equalsi(pom_MODL_OPTF[1], STR_EMPTY)){
		Log("Nebola zadan· premenn· %s (nevadÌ).\n", STR_MODL_OPTF1);
	}

	/* premenn· MODL_OPTF2 (nepovinn·) */
	i = 0; /* param[0] by mal sÌce obsahovaù query type, ale radöej kontrolujeme od 0 */
	Log("pok˙öam sa zistiù hodnotu parametra %s...\n", STR_MODL_OPTF2);
	while((equalsi(pom_MODL_OPTF[2], STR_EMPTY)) && (i < pocet)){
		// Log("...parameter %i (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if(equals(param[i].name, STR_MODL_OPTF2)){
			/* ide o parameter STR_MODL_OPTF2 */
			mystrcpy(pom_MODL_OPTF[2], param[i].val, SMALL);
			Log("hodnota parametra %s je %s.\n", STR_MODL_OPTF2, pom_MODL_OPTF[2]);
		}
		i++;
	}
	if(equalsi(pom_MODL_OPTF[2], STR_EMPTY)){
		Log("Nebola zadan· premenn· %s (nevadÌ).\n", STR_MODL_OPTF2);
	}
	
	/* premenn· MODL_OPTF3 (nepovinn·) */
	i = 0; /* param[0] by mal sÌce obsahovaù query type, ale radöej kontrolujeme od 0 */
	Log("pok˙öam sa zistiù hodnotu parametra %s...\n", STR_MODL_OPTF3);
	while((equalsi(pom_MODL_OPTF[3], STR_EMPTY)) && (i < pocet)){
		// Log("...parameter %i (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if(equals(param[i].name, STR_MODL_OPTF3)){
			/* ide o parameter STR_MODL_OPTF3 */
			mystrcpy(pom_MODL_OPTF[3], param[i].val, SMALL);
			Log("hodnota parametra %s je %s.\n", STR_MODL_OPTF3, pom_MODL_OPTF[3]);
		}
		i++;
	}
	if(equalsi(pom_MODL_OPTF[3], STR_EMPTY)){
		Log("Nebola zadan· premenn· %s (nevadÌ).\n", STR_MODL_OPTF3);
	}
	
	/* premenn· MODL_OPTF4 (nepovinn·) */
	i = 0; /* param[0] by mal sÌce obsahovaù query type, ale radöej kontrolujeme od 0 */
	Log("pok˙öam sa zistiù hodnotu parametra %s...\n", STR_MODL_OPTF4);
	while((equalsi(pom_MODL_OPTF[4], STR_EMPTY)) && (i < pocet)){
		// Log("...parameter %i (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if(equals(param[i].name, STR_MODL_OPTF4)){
			/* ide o parameter STR_MODL_OPTF4 */
			mystrcpy(pom_MODL_OPTF[4], param[i].val, SMALL);
			Log("hodnota parametra %s je %s.\n", STR_MODL_OPTF4, pom_MODL_OPTF[4]);
		}
		i++;
	}
	if(equalsi(pom_MODL_OPTF[4], STR_EMPTY)){
		Log("Nebola zadan· premenn· %s (nevadÌ).\n", STR_MODL_OPTF4);
	}

	/* premenn· MODL_OPTF5 (nepovinn·) */
	i = 0; /* param[0] by mal sÌce obsahovaù query type, ale radöej kontrolujeme od 0 */
	Log("pok˙öam sa zistiù hodnotu parametra %s...\n", STR_MODL_OPTF5);
	while((equalsi(pom_MODL_OPTF[5], STR_EMPTY)) && (i < pocet)){
		// Log("...parameter %i (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if(equals(param[i].name, STR_MODL_OPTF5)){
			/* ide o parameter STR_MODL_OPTF5 */
			mystrcpy(pom_MODL_OPTF[5], param[i].val, SMALL);
			Log("hodnota parametra %s je %s.\n", STR_MODL_OPTF5, pom_MODL_OPTF[5]);
		}
		i++;
	}
	if(equalsi(pom_MODL_OPTF[5], STR_EMPTY)){
		Log("Nebola zadan· premenn· %s (nevadÌ).\n", STR_MODL_OPTF5);
	}

	/* premenn· MODL_OPTF8 (nepovinn·) */
	i = 0; /* param[0] by mal sÌce obsahovaù query type, ale radöej kontrolujeme od 0 */
	Log("pok˙öam sa zistiù hodnotu parametra %s...\n", STR_MODL_OPTF8);
	while((equalsi(pom_MODL_OPTF[8], STR_EMPTY)) && (i < pocet)){
		// Log("...parameter %i (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if(equals(param[i].name, STR_MODL_OPTF8)){
			/* ide o parameter STR_MODL_OPTF8 */
			mystrcpy(pom_MODL_OPTF[8], param[i].val, SMALL);
			Log("hodnota parametra %s je %s.\n", STR_MODL_OPTF8, pom_MODL_OPTF[8]);
		}
		i++;
	}
	if(equalsi(pom_MODL_OPTF[8], STR_EMPTY)){
		Log("Nebola zadan· premenn· %s (nevadÌ).\n", STR_MODL_OPTF8);
	}

	/* premenn· MODL_OPTF9 (nepovinn·) */
	i = 0; /* param[0] by mal sÌce obsahovaù query type, ale radöej kontrolujeme od 0 */
	Log("pok˙öam sa zistiù hodnotu parametra %s...\n", STR_MODL_OPTF9);
	while((equalsi(pom_MODL_OPTF[9], STR_EMPTY)) && (i < pocet)){
		// Log("...parameter %i (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if(equals(param[i].name, STR_MODL_OPTF9)){
			/* ide o parameter STR_MODL_OPTF9 */
			mystrcpy(pom_MODL_OPTF[9], param[i].val, SMALL);
			Log("hodnota parametra %s je %s.\n", STR_MODL_OPTF9, pom_MODL_OPTF[9]);
		}
		i++;
	}
	if(equalsi(pom_MODL_OPTF[9], STR_EMPTY)){
		Log("Nebola zadan· premenn· %s (nevadÌ).\n", STR_MODL_OPTF9);
	}

	/* premenn· MODL_OPTF0 (nepovinn·) */
	i = 0; /* param[0] by mal sÌce obsahovaù query type, ale radöej kontrolujeme od 0 */
	Log("pok˙öam sa zistiù hodnotu parametra %s...\n", STR_MODL_OPTF0);
	while((equalsi(pom_MODL_OPTF[0], STR_EMPTY)) && (i < pocet)){
		// Log("...parameter %i (meno: %s, hodnota: %s)\n", i, param[i].name, param[i].val);
		if(equals(param[i].name, STR_MODL_OPTF0)){
			/* ide o parameter STR_MODL_OPTF0 */
			mystrcpy(pom_MODL_OPTF[0], param[i].val, SMALL);
			Log("hodnota parametra %s je %s.\n", STR_MODL_OPTF0, pom_MODL_OPTF[0]);
		}
		i++;
	}
	if(equalsi(pom_MODL_OPTF[0], STR_EMPTY)){
		Log("Nebola zadan· premenn· %s (nevadÌ).\n", STR_MODL_OPTF0);
	}


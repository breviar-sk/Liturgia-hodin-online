	/* premenna WWW_MODL_OPT1 */
	ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_OPT1));
	/* ak nie je vytvorena, ak t.j. ptr == NULL, tak nas to netrapi,
	 * lebo pom_... su inicializovane na STR_EMPTY */
	if(ptr != NULL){
		if(strcmp(ptr, STR_EMPTY) != 0)
			mystrcpy(pom_MODL_OPT[1], ptr, SMALL);
	}

	/* premenna WWW_MODL_OPT2 */
	ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_OPT2));
	/* ak nie je vytvorena, ak t.j. ptr == NULL, tak nas to netrapi,
	 * lebo pom_... su inicializovane na STR_EMPTY */
	if(ptr != NULL){
		if(strcmp(ptr, STR_EMPTY) != 0)
			mystrcpy(pom_MODL_OPT[2], ptr, SMALL);
	}

	/* premenna WWW_MODL_OPT3 */
	ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_OPT3));
	/* ak nie je vytvorena, ak t.j. ptr == NULL, tak nas to netrapi,
	 * lebo pom_... su inicializovane na STR_EMPTY */
	if(ptr != NULL){
		if(strcmp(ptr, STR_EMPTY) != 0)
			mystrcpy(pom_MODL_OPT[3], ptr, SMALL);
	}

	/* premenna WWW_MODL_OPT4 */
	ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_OPT4));
	/* ak nie je vytvorena, ak t.j. ptr == NULL, tak nas to netrapi,
	 * lebo pom_... su inicializovane na STR_EMPTY */
	if(ptr != NULL){
		if(strcmp(ptr, STR_EMPTY) != 0)
			mystrcpy(pom_MODL_OPT[4], ptr, SMALL);
	}

	/* premenna WWW_MODL_OPT5, pridana 2003-08-13 */
	ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_OPT5));
	/* ak nie je vytvorena, ak t.j. ptr == NULL, tak nas to netrapi,
	 * lebo pom_... su inicializovane na STR_EMPTY */
	if(ptr != NULL){
		if(strcmp(ptr, STR_EMPTY) != 0)
			mystrcpy(pom_MODL_OPT[5], ptr, SMALL);
	}

	/* premenná WWW_MODL_OPT6, pridaná 2007-06-01 */
	ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_OPT6));
	/* ak nie je vytvorena, ak t.j. ptr == NULL, tak nas to netrapi,
	 * lebo pom_... su inicializovane na STR_EMPTY */
	if(ptr != NULL){
		if(strcmp(ptr, STR_EMPTY) != 0)
			mystrcpy(pom_MODL_OPT[6], ptr, SMALL);
	}

	/* premenná WWW_MODL_OPT7, pridaná 2007-06-01 */
	ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_OPT7));
	/* ak nie je vytvorena, ak t.j. ptr == NULL, tak nas to netrapi,
	 * lebo pom_... su inicializovane na STR_EMPTY */
	if(ptr != NULL){
		if(strcmp(ptr, STR_EMPTY) != 0)
			mystrcpy(pom_MODL_OPT[7], ptr, SMALL);
	}

	/* premenná WWW_MODL_OPT8, pridaná 2011-03-22 */
	ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_OPT8));
	/* ak nie je vytvorena, ak t.j. ptr == NULL, tak nas to netrapi,
	 * lebo pom_... su inicializovane na STR_EMPTY */
	if(ptr != NULL){
		if(strcmp(ptr, STR_EMPTY) != 0)
			mystrcpy(pom_MODL_OPT[8], ptr, SMALL);
	}

	/* premenná WWW_MODL_OPT9, pridaná 2011-03-25 */
	ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_OPT9));
	/* ak nie je vytvorena, ak t.j. ptr == NULL, tak nas to netrapi,
	 * lebo pom_... su inicializovane na STR_EMPTY */
	if(ptr != NULL){
		if(strcmp(ptr, STR_EMPTY) != 0)
			mystrcpy(pom_MODL_OPT[9], ptr, SMALL);
	}

	/* premenná WWW_MODL_OPT0, pridaná 2011-04-04 */
	ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_OPT0));
	/* ak nie je vytvorena, ak t.j. ptr == NULL, tak nas to netrapi,
	 * lebo pom_... su inicializovane na STR_EMPTY */
	if(ptr != NULL){
		if(strcmp(ptr, STR_EMPTY) != 0)
			mystrcpy(pom_MODL_OPT[0], ptr, SMALL);
	}

	/* premenna WWW_MODL_OPTF1 */
	ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_OPTF1));
	/* ak nie je vytvorena, ak t.j. ptr == NULL, tak nas to netrapi,
	 * lebo pom_... su inicializovane na STR_EMPTY */
	if(ptr != NULL){
		if(strcmp(ptr, STR_EMPTY) != 0)
			mystrcpy(pom_MODL_OPTF[1], ptr, SMALL);
	}

	/* premenna WWW_MODL_OPTF2 */
	ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_OPTF2));
	/* ak nie je vytvorena, ak t.j. ptr == NULL, tak nas to netrapi,
	 * lebo pom_... su inicializovane na STR_EMPTY */
	if(ptr != NULL){
		if(strcmp(ptr, STR_EMPTY) != 0)
			mystrcpy(pom_MODL_OPTF[2], ptr, SMALL);
	}

	/* premenna WWW_MODL_OPTF3 */
	ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_OPTF3));
	/* ak nie je vytvorena, ak t.j. ptr == NULL, tak nas to netrapi,
	 * lebo pom_... su inicializovane na STR_EMPTY */
	if(ptr != NULL){
		if(strcmp(ptr, STR_EMPTY) != 0)
			mystrcpy(pom_MODL_OPTF[3], ptr, SMALL);
	}

	/* premenna WWW_MODL_OPTF4 */
	ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_OPTF4));
	/* ak nie je vytvorena, ak t.j. ptr == NULL, tak nas to netrapi,
	 * lebo pom_... su inicializovane na STR_EMPTY */
	if(ptr != NULL){
		if(strcmp(ptr, STR_EMPTY) != 0)
			mystrcpy(pom_MODL_OPTF[4], ptr, SMALL);
	}

	/* premenna WWW_MODL_OPTF5 */
	ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_OPTF5));
	/* ak nie je vytvorena, ak t.j. ptr == NULL, tak nas to netrapi,
	 * lebo pom_... su inicializovane na STR_EMPTY */
	if(ptr != NULL){
		if(strcmp(ptr, STR_EMPTY) != 0)
			mystrcpy(pom_MODL_OPTF[5], ptr, SMALL);
	}

	/* premenna WWW_MODL_OPTF8 */
	ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_OPTF8));
	/* ak nie je vytvorena, ak t.j. ptr == NULL, tak nas to netrapi,
	 * lebo pom_... su inicializovane na STR_EMPTY */
	if(ptr != NULL){
		if(strcmp(ptr, STR_EMPTY) != 0)
			mystrcpy(pom_MODL_OPTF[8], ptr, SMALL);
	}

	/* premenna WWW_MODL_OPTF9 */
	ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_OPTF9));
	/* ak nie je vytvorena, ak t.j. ptr == NULL, tak nas to netrapi,
	 * lebo pom_... su inicializovane na STR_EMPTY */
	if(ptr != NULL){
		if(strcmp(ptr, STR_EMPTY) != 0)
			mystrcpy(pom_MODL_OPTF[9], ptr, SMALL);
	}

	/* premenna WWW_MODL_OPTF0 */
	ptr = getenv(ADD_WWW_PREFIX_(STR_MODL_OPTF0));
	/* ak nie je vytvorena, ak t.j. ptr == NULL, tak nas to netrapi,
	 * lebo pom_... su inicializovane na STR_EMPTY */
	if(ptr != NULL){
		if(strcmp(ptr, STR_EMPTY) != 0)
			mystrcpy(pom_MODL_OPTF[0], ptr, SMALL);
	}


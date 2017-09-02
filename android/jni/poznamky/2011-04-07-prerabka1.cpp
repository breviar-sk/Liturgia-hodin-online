	/* pom_MODL_OPT[1]..pom_MODL_OPT[5] */
	mystrcpy(local_str, STR_EMPTY, MAX_STR);
	if(!equals(pom_MODL_OPT[1], STR_EMPTY)){
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_OPT1), MAX_STR);
		strcat(local_str, "=");
		strcat(local_str, pom_MODL_OPT[1]);
		Log("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		Log("--- setForm: putenv returned %d.\n", ret); /* 2005-03-30: Pridany vypis */
	}
	mystrcpy(local_str, STR_EMPTY, MAX_STR);
	if(!equals(pom_MODL_OPT[2], STR_EMPTY)){
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_OPT2), MAX_STR);
		strcat(local_str, "=");
		strcat(local_str, pom_MODL_OPT[2]);
		Log("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		Log("--- setForm: putenv returned %d.\n", ret); /* 2005-03-30: Pridany vypis */
	}
	mystrcpy(local_str, STR_EMPTY, MAX_STR);
	if(!equals(pom_MODL_OPT[3], STR_EMPTY)){
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_OPT3), MAX_STR);
		strcat(local_str, "=");
		strcat(local_str, pom_MODL_OPT[3]);
		Log("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		Log("--- setForm: putenv returned %d.\n", ret); /* 2005-03-30: Pridany vypis */
	}
	mystrcpy(local_str, STR_EMPTY, MAX_STR);
	if(!equals(pom_MODL_OPT[4], STR_EMPTY)){
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_OPT4), MAX_STR);
		strcat(local_str, "=");
		strcat(local_str, pom_MODL_OPT[4]);
		Log("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		Log("--- setForm: putenv returned %d.\n", ret); /* 2005-03-30: Pridany vypis */
	}
	mystrcpy(local_str, STR_EMPTY, MAX_STR);
	if(!equals(pom_MODL_OPT[5], STR_EMPTY)){
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_OPT5), MAX_STR);
		strcat(local_str, "=");
		strcat(local_str, pom_MODL_OPT[5]);
		Log("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		Log("--- setForm: putenv returned %d.\n", ret); /* 2005-03-30: Pridany vypis */
	}

	/* pom_MODL_OPT[6] resp. pom_MODL_OPT[7] pridané 2007-06-01, pretože sa používali (pre rozbor mesiaca) opt1 resp. opt2; default sa "bil" */
	mystrcpy(local_str, STR_EMPTY, MAX_STR);
	if(!equals(pom_MODL_OPT[6], STR_EMPTY)){
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_OPT6), MAX_STR);
		strcat(local_str, "=");
		strcat(local_str, pom_MODL_OPT[6]);
		Log("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		Log("--- setForm: putenv returned %d.\n", ret);
	}
	mystrcpy(local_str, STR_EMPTY, MAX_STR);
	if(!equals(pom_MODL_OPT[7], STR_EMPTY)){
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_OPT7), MAX_STR);
		strcat(local_str, "=");
		strcat(local_str, pom_MODL_OPT[7]);
		Log("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		Log("--- setForm: putenv returned %d.\n", ret);
	}

	/* pom_MODL_OPT[8] pridané 2011-03-22 */
	mystrcpy(local_str, STR_EMPTY, MAX_STR);
	if(!equals(pom_MODL_OPT[8], STR_EMPTY)){
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_OPT8), MAX_STR);
		strcat(local_str, "=");
		strcat(local_str, pom_MODL_OPT[8]);
		Log("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		Log("--- setForm: putenv returned %d.\n", ret);
	}

	/* pom_MODL_OPT[9] pridané 2011-03-25 */
	mystrcpy(local_str, STR_EMPTY, MAX_STR);
	if(!equals(pom_MODL_OPT[9], STR_EMPTY)){
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_OPT9), MAX_STR);
		strcat(local_str, "=");
		strcat(local_str, pom_MODL_OPT[9]);
		Log("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		Log("--- setForm: putenv returned %d.\n", ret);
	}

	/* pom_MODL_OPT[0] pridané 2011-03-25 */
	mystrcpy(local_str, STR_EMPTY, MAX_STR);
	if(!equals(pom_MODL_OPT[0], STR_EMPTY)){
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_OPT0), MAX_STR);
		strcat(local_str, "=");
		strcat(local_str, pom_MODL_OPT[0]);
		Log("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		Log("--- setForm: putenv returned %d.\n", ret);
	}

	/* pom_MODL_OPTF[1]..pom_MODL_OPTF[1] -- force verzie pom_MODL_OPT[1]..pom_MODL_OPT[5] */
	mystrcpy(local_str, STR_EMPTY, MAX_STR);
	if(!equals(pom_MODL_OPTF[1], STR_EMPTY)){
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_OPTF1), MAX_STR);
		strcat(local_str, "=");
		strcat(local_str, pom_MODL_OPTF[1]);
		Log("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		Log("--- setForm: putenv returned %d.\n", ret);
	}
	mystrcpy(local_str, STR_EMPTY, MAX_STR);
	if(!equals(pom_MODL_OPTF[2], STR_EMPTY)){
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_OPTF2), MAX_STR);
		strcat(local_str, "=");
		strcat(local_str, pom_MODL_OPT[2]);
		Log("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		Log("--- setForm: putenv returned %d.\n", ret);
	}
	mystrcpy(local_str, STR_EMPTY, MAX_STR);
	if(!equals(pom_MODL_OPTF[3], STR_EMPTY)){
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_OPTF3), MAX_STR);
		strcat(local_str, "=");
		strcat(local_str, pom_MODL_OPTF[3]);
		Log("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		Log("--- setForm: putenv returned %d.\n", ret);
	}
	mystrcpy(local_str, STR_EMPTY, MAX_STR);
	if(!equals(pom_MODL_OPTF[4], STR_EMPTY)){
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_OPTF4), MAX_STR);
		strcat(local_str, "=");
		strcat(local_str, pom_MODL_OPTF[4]);
		Log("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		Log("--- setForm: putenv returned %d.\n", ret);
	}
	mystrcpy(local_str, STR_EMPTY, MAX_STR);
	if(!equals(pom_MODL_OPTF[5], STR_EMPTY)){
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_OPTF5), MAX_STR);
		strcat(local_str, "=");
		strcat(local_str, pom_MODL_OPTF[5]);
		Log("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		Log("--- setForm: putenv returned %d.\n", ret);
	}
	mystrcpy(local_str, STR_EMPTY, MAX_STR);
	if(!equals(pom_MODL_OPTF[8], STR_EMPTY)){
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_OPTF8), MAX_STR);
		strcat(local_str, "=");
		strcat(local_str, pom_MODL_OPTF[8]);
		Log("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		Log("--- setForm: putenv returned %d.\n", ret);
	}
	mystrcpy(local_str, STR_EMPTY, MAX_STR);
	if(!equals(pom_MODL_OPTF[9], STR_EMPTY)){
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_OPTF9), MAX_STR);
		strcat(local_str, "=");
		strcat(local_str, pom_MODL_OPTF[9]);
		Log("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		Log("--- setForm: putenv returned %d.\n", ret);
	}
	mystrcpy(local_str, STR_EMPTY, MAX_STR);
	if(!equals(pom_MODL_OPTF[0], STR_EMPTY)){
		mystrcpy(local_str, ADD_WWW_PREFIX_(STR_MODL_OPTF0), MAX_STR);
		strcat(local_str, "=");
		strcat(local_str, pom_MODL_OPTF[0]);
		Log("--- setForm: putenv(%s); ...\n", local_str);
		ret = putenv(local_str);
		Log("--- setForm: putenv returned %d.\n", ret);
	}


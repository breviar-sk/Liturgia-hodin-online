short int ExpL2HTML(char *fmt)
{
	short int i;
	short int ilen;
	char c;
	ilen = strlen(fmt);
	for(i = 0; i < ilen; i++){
		c = fmt[i];
		switch(c){
			case '¬': YYcharHTML(128, 172, 67, "È", "\\vC ", 67); /*C makcen*/ break;
			case '': YYcharHTML(129, 129, 117, "&uuml;", "\\\"u", 117); /*u bodky*/ break;
			case '‚': YYcharHTML(130, 130, 101, "é", "\\\'e", 130); /*e dlzen*/ break;
			case 'Ô': YYcharHTML(131, 212, 100, "ï", "\\vd ", 100); /*d makcen*/ break;
			case '„': YYcharHTML(132, 132, 97, "&auml;", "\\\"a", 132); /*a bodky*/ break;
			case 'Ò': YYcharHTML(133, 210, 68, "Ï", "\\vD ", 68); /*D makcen*/ break;
			case '›': YYcharHTML(134, 155, 84, "", "\\vT ", 84); /*T makcen*/ break;
			case 'Ÿ': YYcharHTML(135, 159, 99, "è", "\\vc ", 99); /*c makcen*/ break;
			case 'Ø': YYcharHTML(136, 216, 101, "ì", "\\ve ", 101); /*e makcen*/ break;
			case '·': YYcharHTML(137, 183, 69, "Ì", "\\vE ", 69); /*E makcen*/ break;
			case '‘': YYcharHTML(138, 145, 76, "Å", "\\\'L ", 76); /*L dlzen*/ break;
			case 'Ö': YYcharHTML(139, 214, 73, "&Iacute;", "\\\'I ", 73); /*I dlzen*/ break;
			case '–': YYcharHTML(140, 150, 108, "¾", "\\vl ", 108); /*l makcen*/ break;
			case '’': YYcharHTML(141, 146, 108, "å", "\\\'l ", 108); /*l dlzen*/ break;
			case 'Ž': YYcharHTML(142, 142, 65, "&Auml;", "\\\"A ", 142); /*A bodky*/ break;
			case 'µ': YYcharHTML(143, 181, 65, "&Aacute;", "\\\'A ", 65); /*A dlzen*/ break;
			case '': YYcharHTML(144, 144, 69, "&Eacute;", "\\\'E ", 144); /*E dlzen*/ break;
			case '§': YYcharHTML(145, 167, 122, "ž", "\\vz ", 122); /*z makcen*/ break;
			case '¦': YYcharHTML(146, 166, 90, "Ž", "\\vZ ", 90); /*Z makcen*/ break;
			case '“': YYcharHTML(147, 147, 111, "&ocirc;", "\\^o ", 147); /*o vokan */ break;
			case '”': YYcharHTML(148, 148, 111, "&ouml;", "\\\"o", 148); /*o bodky*/ break;
			case 'à': YYcharHTML(149, 224, 79, "&Oacute;", "\\\'O", 79); /*O dlzen*/ break;
			case '…': YYcharHTML(150, 133, 117, "ù", "\\ou ", 117); /*u kruzok */ break;
			case 'é': YYcharHTML(151, 233, 85, "&Uacute;", "\\\'U ", 85); /*U dlzen*/ break;
			case 'ì': YYcharHTML(152, 236, 121, "&yacute;", "\\\'y", 121); /*y dlzen*/ break;
			case '™': YYcharHTML(153, 153, 79, "&Ouml;", "\\\"O", 153); /*O bodky*/ break;
			case 'š': YYcharHTML(154, 154, 85, "&Uuml;", "\\\"U", 154); /*U bodky*/ break;
			case 'æ': YYcharHTML(155, 230, 83, "Š", "\\vS ", 83); /*S makcen*/ break;
			case '•': YYcharHTML(156, 149, 76, "¼", "\\vL ", 76); /*L makcen*/ break;
			case 'í': YYcharHTML(157, 237, 89, "&Yacute;", "\\\'Y ", 89); /*Y dlzen*/ break;
			case 'ü': YYcharHTML(158, 252, 82, "Ø", "\\vR ", 82); /*R makcen*/ break;
			case 'œ': YYcharHTML(159, 156, 116, "", "\\vt ", 116); /*t makcen*/ break;
			case ' ': YYcharHTML(160, 160, 97, "&aacute;", "\\\'a ", 160); /*a dlzen*/ break;
			case '¡': YYcharHTML(161, 161, 105, "&iacute;", "\\\'i ", 161); /*i dlzen*/ break;
			case '¢': YYcharHTML(162, 162, 111, "&oacute;", "\\\'o ", 162); /*o dlzen*/ break;
			case '£': YYcharHTML(163, 163, 117, "&uacute;", "\\\'u ", 163); /*u dlzen*/ break;
			case 'å': YYcharHTML(164, 229, 110, "ò", "\\vn ", 110); /*n makcen*/ break;
			case 'Õ': YYcharHTML(165, 213, 78, "Ò", "\\vN ", 78); /*N makcen*/ break;
			case 'Þ': YYcharHTML(166, 222, 85, "Ù", "\\oU ", 85); /*U kruzok */ break;
			case 'â': YYcharHTML(167, 226, 79, "&Ocirc;", STR_EMPTY, 79); /*O vokan */ break;
			case 'ç': YYcharHTML(168, 231, 115, "š", "\\vs ", 115); /*s makcen*/ break;
			case 'ý': YYcharHTML(169, 253, 114, "ø", "\\vr ", 114); /*r makcen*/ break;
			case 'ê': YYcharHTML(170, 234, 114, "à", "\\\'r ", 114); /*r dlzen*/ break;
			case 'è': YYcharHTML(171, 232, 82, "À", "\\\'R ", 82); /*R dlzen*/ break;
			case 'õ': YYcharHTML(173, 245, 0, "§", STR_EMPTY, 0); /*paragraf */ break;
			default: YYdefault();
		}
	}
	return 0;
}


	short int pocet = 1; // po�et z�znamov, ktor� sa exportuj� (�i u� riadky tabu�ky alebo len zoznam)
	short int zoznam[6] = {0, -1, -1, -1, -1, -1}; // prv� hodnota, t. j. zoznam[0], ur�uje po�et; ak je ��slo > 10, znamen� to, �e ide o * 10 kv�li inform�cii o tom, �e sa neexportuje modlitba cez de� a komplet�rium pre �ubovo�n� spomienky
	short int poradie_svaty;
	// pozor, hoci je nedela, predsa na nu mohlo pripadnut slavenie s vyssou prioritou
	if((_global_den.denvt == DEN_NEDELA) ||
		(_global_den.prik == PRIKAZANY_SVIATOK) ||
		(_global_den.smer < 5)){
		// nedele a prikazane sviatky - cervenou, velkymi pismenami
		// slavnosti - velkymi pismenami

		// 23/02/2000A.D. -- teraz este testujeme, ci nema nahodou pred nedelou (trebars v obdobi cez rok, smer == 6) prednost napr. sviatok Pana (smer == 5); dalsia cast je skopirovana podla casti v _rozbor_dna, v poznamke SVATY_VEDIE
		// ... alebo c. 60: "ak na jeden den pripadnu viacere slavenia, uprednostni sa to, ktore ma v tabulke liturgickych dni vyssi stupen [t.j. .smer].

		// 2006-12-07: sl�vnosti sv�t�ch (k fixn�m d�tumom: napr. 8.12., 29.6., 5.7., 15.8.), ktor� nepripadn� na nede�u, neboli spr�vne zobrazovan�
		// 2010-07-28: doplnen� alternat�vne porovnanie aj s _global_svaty2.smer (kv�li dominik�nskej sl�vnosti 8.8.)
		// 2010-10-06: upraven�; nesmie �s� o lok�lnu sl�vnos� (smer == 4) lebo nem� preb�ja� "glob�lnu" v danom kalend�ri [napr. czop pre 22.10.]
		//             p�vodne tu bolo: if((_global_den.smer > _global_svaty1.smer) || (_global_den.smer > _global_svaty2.smer) || (_global_den.smer > _global_svaty3.smer)){
		// 2011-02-02: zadefinovan� MIESTNE_SLAVENIE_CZOP_SVATY1 a� 3, aby sa zjednodu�ila podmienka (plat� len pre CZOP)
		// 2011-03-07: MIESTNE_SLAVENIE_CZOP_SVATY1 a� 3 pou�it� aj pre in� lok�lne sl�venia ako MIESTNE_SLAVENIE_LOKAL_SVATY1 a� 3
		if(((_global_den.smer > _global_svaty1.smer) && !MIESTNE_SLAVENIE_LOKAL_SVATY1)
			|| ((_global_den.smer > _global_svaty2.smer) && !MIESTNE_SLAVENIE_LOKAL_SVATY2)
			|| ((_global_den.smer > _global_svaty3.smer) && !MIESTNE_SLAVENIE_LOKAL_SVATY3)
			){
			if(_global_den.smer > _global_svaty1.smer){
				poradie_svaty = 1;
			}
			else if(_global_den.smer > _global_svaty2.smer){
				poradie_svaty = 2;
			}
			else if(_global_den.smer > _global_svaty3.smer){
				poradie_svaty = 3;
			}
			zoznam[pocet] = poradie_svaty;
		}
		else{
			poradie_svaty = 0;
			zoznam[pocet] = poradie_svaty;
			// 2010-10-06: upraven�; v tejto vetve rozhodovania treba rie�i� to, �e je splnen� z�kladn� podmienka (nede�a alebo prik�zan� sviatok alebo smer < 5),
			//             av�ak nebola splnen� vy��ie uveden� novo-upraven� podmienka o "prebit�" nedele napr. lok�lnou sl�vnos�ou
			if((_global_den.smer > _global_svaty1.smer) || (_global_den.smer > _global_svaty2.smer) || (_global_den.smer > _global_svaty3.smer)){
				pocet = 2;
				NEWLINE;
				if(_global_den.smer > _global_svaty1.smer){
					poradie_svaty = 1;
				}
				else if(_global_den.smer > _global_svaty2.smer){
					poradie_svaty = 2;
				}
				else if(_global_den.smer > _global_svaty3.smer){
					poradie_svaty = 3;
				}
				zoznam[pocet] = poradie_svaty;
			}
		}
	}// if((_global_den.denvt == DEN_NEDELA) || (_global_den.prik == PRIKAZANY_SVIATOK) || (_global_den.smer < 5))
	else if(_global_pocet_svatych > 0){
		// sviatky (spomienky, ls) svatych
		// 2010-07-28: doplnen� alternat�vne porovnanie aj s _global_svaty2.smer (kv�li dominik�nskej sl�vnosti 8.8.)
		if(((_global_den.smer > _global_svaty1.smer) || (_global_den.smer > _global_svaty2.smer) || (_global_den.smer > _global_svaty3.smer)) ||
			((_global_den.smer == 9) && (_global_svaty1.smer == 12))){
		// svaty
			// 2009-01-05: Vlado K. ma upozornil, �e ak je smer sv�t� == 12, ale de� je 9 (bod 59. smern�c o LH a kalend�ri, �. 12), bolo by lep�ie pon�knu� najprv de� a a� potom ostatn� sl�venia 
			// 2010-05-21: Rastislav Hamr��ek SDB <rastohamracek@sdb.sk> upozornil defacto na to ist� ako Vlado: aby to bolo pod�a direkt�ria
			// ----------------------------------------------------------------------------
			// 2005-08-22: p�vodne sa tu porovn�valo s 12, ale aj pre 11 (lok�lne sl�venia) by mal syst�m pon�knu� v�edn� de� - ke� je to napr. v inej diec�ze
			// 2009-11-26: porovn�vame klasicky, resp. �peci�lne pre body 4, 8, 11 [Miestne sl�vnosti, Miestne sviatky, Miestne povinn� spomienky] pred touto �pravou tu bolo: if((_global_svaty1.smer >= 11) && at�.
			// 2010-05-21: sem presunut� potenci�lne vypisovanie (export) v�edn�ho d�a pred prv�ho sv�tca, ak je �ubovo�n� spomienka teraz vlastne obe vetvy vyzeraj� rovnako, asi to zjednot�m �asom...
			// 2010-05-24: zjednoten�; bolo odvetven� "if(_global_den.smer > _global_svaty1.smer)"; 
			//             else vetva mala nap�san�: "�ubovo�n� spomienka sv�t�ho/sv�t�ch, pri�om v�edn� de� m� vy��iu prioritu sl�venia"
			//             a e�te: "2010-05-21: odtia�to presunut� potenci�lne vypisovanie (export) v�edn�ho d�a pred prv�ho sv�tca, ak je �ubovo�n� spomienka"
			// 2011-02-02: zadefinovan� MIESTNE_SLAVENIE_CZOP_SVATY1 a� 3, aby sa zjednodu�ila podmienka (plat� len pre CZOP)
			// 2011-03-07: MIESTNE_SLAVENIE_CZOP_SVATY1 a� 3 pou�it� aj pre in� lok�lne sl�venia ako MIESTNE_SLAVENIE_LOKAL_SVATY1 a� 3
			// 2012-08-21: cdoplnen� premenn� (kv�li tomu, �i sa maj� pre sv�tca 1 zobrazi� buttons modlitba cez de�)
			aj_feria = NIE;
			if(((_global_svaty1.smer >= 12) || MIESTNE_SLAVENIE_LOKAL_SVATY1) && (typ != EXPORT_DNA_VIAC_DNI)){
				// ak je to iba lubovolna spomienka, tak vsedny den
				// 2010-05-21: NEWLINE; bolo pred; mus�me ho zaradi� za :)
				aj_feria = ANO;
			}
			if(aj_feria == ANO){
				// ak je to iba lubovolna spomienka, tak vsedny den
				poradie_svaty = 0;
				zoznam[pocet] = poradie_svaty;
				pocet++;
				NEWLINE;
			}
			// 2010-05-21: p�vodne bolo: "sviatok, spomienka alebo �ubovo�n� spomienka sv�t�ho/sv�t�ch, ide prv ako v�edn� de�"; dnes ide prv len ak je to sviatok alebo spomienka 
			// (a vlastne vtedy sa v�edn� de� vypisuje len pre lok�lne sviatky resp. spomienky) 
			poradie_svaty = 1;
			if(!(aj_feria)){
				poradie_svaty *= 10;
			}
			zoznam[pocet] = poradie_svaty;
			if(_global_pocet_svatych > 1){
				poradie_svaty = 2;
				poradie_svaty *= 10;
				pocet++;
				zoznam[pocet] = poradie_svaty;
				if(_global_pocet_svatych > 2){
					poradie_svaty = 3;
					poradie_svaty *= 10;
					pocet++;
					zoznam[pocet] = poradie_svaty;
				}
			}
		}// svaty ma prednost
		else{
		// prednost ma den
			poradie_svaty = 0;
			zoznam[pocet] = poradie_svaty;
		}
	}// if(_global_pocet_svatych > 0)
	else{
		// obycajne dni, nie sviatok
		poradie_svaty = 0;
		zoznam[pocet] = poradie_svaty;
	}// if(equals(_global_den.meno, STR_EMPTY))

	// este spomienka panny marie v sobotu, cl. 15
	if((_global_den.litobd == OBD_CEZ_ROK) &&
		(_global_den.denvt == DEN_SOBOTA) &&
		(
			((_global_den.smer >= 11) && (_global_pocet_svatych == 0)) ||
			(((_global_svaty1.smer >= 12) || MIESTNE_SLAVENIE_LOKAL_SVATY1) && (_global_pocet_svatych > 0))) &&
		(typ != EXPORT_DNA_VIAC_DNI)){
		// 2005-08-22: p�vodne sa tu porovn�valo s 12, ale aj pre 11 (lok�lne sl�venia) by mal syst�m pon�knu� (v sobotu) spomienku p. m�rie - ke� je to napr. v inej diec�ze 
		// 2006-02-02: pridan� posv. ��tania a upraven�; ke�e smer == 11 pou��vame pre lok�lne povinn� spomienky, upravili sme kontrolu z 12 na 11
		// 2011-02-02: zadefinovan� MIESTNE_SLAVENIE_CZOP_SVATY1 a� 3, aby sa zjednodu�ila podmienka (plat� len pre CZOP)
		// 2011-03-07: MIESTNE_SLAVENIE_CZOP_SVATY1 a� 3 pou�it� aj pre in� lok�lne sl�venia ako MIESTNE_SLAVENIE_LOKAL_SVATY1 a� 3
		poradie_svaty = 4;
		poradie_svaty *= 10;
		pocet++;
		zoznam[pocet] = poradie_svaty;
	}
	zoznam[0] = pocet;



interpretovanie zoznamu:

short int poradie_svaty;
short int zobrazit_mcd = ANO;
short int pocet = zoznam[0];
for(int i = 1; i++; i <= pocet){
	poradie_svaty = zoznam[i];
	zobrazit_mcd = ANO;

	if(zoznam[i] > 10){
		poradie_svaty /= 10;
		zobrazit_mcd = NIE;
		
	}
	execute_command(poradie_svaty, batch_command, modlitba, d_from_m_from_r_from);

	// alebo

	if(i > 1){
		NEWLINE;
	}
	_export_rozbor_dna_buttons(typ, poradie_svaty, ANO, zobrazit_mcd);

}

	short int pocet = 1; // poËet z·znamov, ktorÈ sa exportuj˙ (Ëi uû riadky tabuæky alebo len zoznam)
	short int zoznam[6] = {0, -1, -1, -1, -1, -1}; // prv· hodnota, t. j. zoznam[0], urËuje poËet; ak je ËÌslo > 10, znamen· to, ûe ide o * 10 kvÙli inform·cii o tom, ûe sa neexportuje modlitba cez deÚ a kompletÛrium pre æubovoænÈ spomienky
	short int poradie_svaty;
	// pozor, hoci je nedela, predsa na nu mohlo pripadnut slavenie s vyssou prioritou
	if((_global_den.denvt == DEN_NEDELA) ||
		(_global_den.prik == PRIKAZANY_SVIATOK) ||
		(_global_den.smer < 5)){
		// nedele a prikazane sviatky - cervenou, velkymi pismenami
		// slavnosti - velkymi pismenami

		// 23/02/2000A.D. -- teraz este testujeme, ci nema nahodou pred nedelou (trebars v obdobi cez rok, smer == 6) prednost napr. sviatok Pana (smer == 5); dalsia cast je skopirovana podla casti v _rozbor_dna, v poznamke SVATY_VEDIE
		// ... alebo c. 60: "ak na jeden den pripadnu viacere slavenia, uprednostni sa to, ktore ma v tabulke liturgickych dni vyssi stupen [t.j. .smer].

		// 2006-12-07: sl·vnosti sv‰t˝ch (k fixn˝m d·tumom: napr. 8.12., 29.6., 5.7., 15.8.), ktorÈ nepripadn˙ na nedeæu, neboli spr·vne zobrazovanÈ
		// 2010-07-28: doplnenÈ alternatÌvne porovnanie aj s _global_svaty2.smer (kvÙli dominik·nskej sl·vnosti 8.8.)
		// 2010-10-06: upravenÈ; nesmie Ìsù o lok·lnu sl·vnosù (smer == 4) lebo nem· prebÌjaù "glob·lnu" v danom kalend·ri [napr. czop pre 22.10.]
		//             pÙvodne tu bolo: if((_global_den.smer > _global_svaty1.smer) || (_global_den.smer > _global_svaty2.smer) || (_global_den.smer > _global_svaty3.smer)){
		// 2011-02-02: zadefinovanÈ MIESTNE_SLAVENIE_CZOP_SVATY1 aû 3, aby sa zjednoduöila podmienka (platÌ len pre CZOP)
		// 2011-03-07: MIESTNE_SLAVENIE_CZOP_SVATY1 aû 3 pouûitÈ aj pre inÈ lok·lne sl·venia ako MIESTNE_SLAVENIE_LOKAL_SVATY1 aû 3
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
			_export_rozbor_dna_buttons(typ, poradie_svaty, ANO, ANO);
		}
		else{
			poradie_svaty = 0;
			_export_rozbor_dna_buttons(typ, poradie_svaty, ANO, ANO);
			// 2010-10-06: upravenÈ; v tejto vetve rozhodovania treba rieöiù to, ûe je splnen· z·kladn· podmienka (nedeæa alebo prik·zan˝ sviatok alebo smer < 5),
			//             avöak nebola splnen· vyööie uveden· novo-upraven· podmienka o "prebitÌ" nedele napr. lok·lnou sl·vnosùou
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
				_export_rozbor_dna_buttons(typ, poradie_svaty, ANO, ANO);
			}
		}
	}// if((_global_den.denvt == DEN_NEDELA) || (_global_den.prik == PRIKAZANY_SVIATOK) || (_global_den.smer < 5))
	else if(_global_pocet_svatych > 0){
		// sviatky (spomienky, ls) svatych
		// 2010-07-28: doplnenÈ alternatÌvne porovnanie aj s _global_svaty2.smer (kvÙli dominik·nskej sl·vnosti 8.8.)
		if(((_global_den.smer > _global_svaty1.smer) || (_global_den.smer > _global_svaty2.smer) || (_global_den.smer > _global_svaty3.smer)) ||
			((_global_den.smer == 9) && (_global_svaty1.smer == 12))){
		// svaty
			// 2009-01-05: Vlado K. ma upozornil, ûe ak je smer sv‰t˝ == 12, ale deÚ je 9 (bod 59. smernÌc o LH a kalend·ri, Ë. 12), bolo by lepöie pon˙knuù najprv deÚ a aû potom ostatnÈ sl·venia 
			// 2010-05-21: Rastislav Hamr·Ëek SDB <rastohamracek@sdb.sk> upozornil defacto na to istÈ ako Vlado: aby to bolo podæa direktÛria
			// ----------------------------------------------------------------------------
			// 2005-08-22: pÙvodne sa tu porovn·valo s 12, ale aj pre 11 (lok·lne sl·venia) by mal systÈm pon˙knuù vöedn˝ deÚ - keÔ je to napr. v inej diecÈze
			// 2009-11-26: porovn·vame klasicky, resp. öpeci·lne pre body 4, 8, 11 [Miestne sl·vnosti, Miestne sviatky, Miestne povinnÈ spomienky] pred touto ˙pravou tu bolo: if((_global_svaty1.smer >= 11) && atÔ.
			// 2010-05-21: sem presunutÈ potenci·lne vypisovanie (export) vöednÈho dÚa pred prvÈho sv‰tca, ak je æubovoæn· spomienka teraz vlastne obe vetvy vyzeraj˙ rovnako, asi to zjednotÌm Ëasom...
			// 2010-05-24: zjednotenÈ; bolo odvetvenÈ "if(_global_den.smer > _global_svaty1.smer)"; 
			//             else vetva mala napÌsanÈ: "æubovoæn· spomienka sv‰tÈho/sv‰t˝ch, priËom vöedn˝ deÚ m· vyööiu prioritu sl·venia"
			//             a eöte: "2010-05-21: odtiaæto presunutÈ potenci·lne vypisovanie (export) vöednÈho dÚa pred prvÈho sv‰tca, ak je æubovoæn· spomienka"
			// 2011-02-02: zadefinovanÈ MIESTNE_SLAVENIE_CZOP_SVATY1 aû 3, aby sa zjednoduöila podmienka (platÌ len pre CZOP)
			// 2011-03-07: MIESTNE_SLAVENIE_CZOP_SVATY1 aû 3 pouûitÈ aj pre inÈ lok·lne sl·venia ako MIESTNE_SLAVENIE_LOKAL_SVATY1 aû 3
			// 2012-08-21: cdoplnen· premenn· (kvÙli tomu, Ëi sa maj˙ pre sv‰tca 1 zobraziù buttons modlitba cez deÚ)
			aj_feria = NIE;
			if(((_global_svaty1.smer >= 12) || MIESTNE_SLAVENIE_LOKAL_SVATY1) && (typ != EXPORT_DNA_VIAC_DNI)){
				// ak je to iba lubovolna spomienka, tak vsedny den
				// 2010-05-21: NEWLINE; bolo pred; musÌme ho zaradiù za :)
				aj_feria = ANO;
			}
			if(aj_feria == ANO){
				poradie_svaty = 0;
				_export_rozbor_dna_buttons(typ, poradie_svaty, ANO, ANO);
				NEWLINE;
			}
			// 2010-05-21: pÙvodne bolo: "sviatok, spomienka alebo æubovoæn· spomienka sv‰tÈho/sv‰t˝ch, ide prv ako vöedn˝ deÚ"; dnes ide prv len ak je to sviatok alebo spomienka 
			// (a vlastne vtedy sa vöedn˝ deÚ vypisuje len pre lok·lne sviatky resp. spomienky) 
			poradie_svaty = 1;
			_export_rozbor_dna_buttons(typ, poradie_svaty, ANO, !(aj_feria));
			if(_global_pocet_svatych > 1){
				NEWLINE;
				poradie_svaty = 2;
				_export_rozbor_dna_buttons(typ, poradie_svaty, ANO, NIE);
				if(_global_pocet_svatych > 2){
					NEWLINE;
					poradie_svaty = 3;
					_export_rozbor_dna_buttons(typ, poradie_svaty, ANO, NIE);
				}
			}
		}// svaty ma prednost
		else{
		// prednost ma den
			_export_rozbor_dna_buttons(typ, 0, ANO, ANO);
		}
	}// if(_global_pocet_svatych > 0)
	else{
		// obycajne dni, nie sviatok
		_export_rozbor_dna_buttons(typ, 0, ANO, ANO);
	}// if(equals(_global_den.meno, STR_EMPTY))

	// este spomienka panny marie v sobotu, cl. 15
	if((_global_den.litobd == OBD_CEZ_ROK) &&
		(_global_den.denvt == DEN_SOBOTA) &&
		(
			// 2005-08-22: pÙvodne sa tu porovn·valo s 12, ale aj pre 11 (lok·lne sl·venia) by mal systÈm pon˙knuù (v sobotu) spomienku p. m·rie - keÔ je to napr. v inej diecÈze 
			// 2011-02-02: zadefinovanÈ MIESTNE_SLAVENIE_CZOP_SVATY1 aû 3, aby sa zjednoduöila podmienka (platÌ len pre CZOP)
			// 2011-03-07: MIESTNE_SLAVENIE_CZOP_SVATY1 aû 3 pouûitÈ aj pre inÈ lok·lne sl·venia ako MIESTNE_SLAVENIE_LOKAL_SVATY1 aû 3
			((_global_den.smer >= 11) && (_global_pocet_svatych == 0)) ||
			(((_global_svaty1.smer >= 12) || MIESTNE_SLAVENIE_LOKAL_SVATY1) && (_global_pocet_svatych > 0))) &&
		(typ != EXPORT_DNA_VIAC_DNI)){
		NEWLINE;
		_export_rozbor_dna_buttons(typ, 4, ANO, NIE);
	}

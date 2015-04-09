/***************************************************************/
/*                                                             */
/* citania.cpp                                                 */
/* (c)2010-2015 | Richard Královiè                             */
/*                                                             */
/* description | code for liturgical readings for Android app  */
/*                                                             */
/***************************************************************/

#include "mysystem.h"
#include "mysysdef.h"
#include "citania.h"
#include "liturgia.h"
#include <string.h>
#include <stdlib.h>

#ifdef LITURGICKE_CITANIA_ANDROID

static struct citanie Citania[] = {
#include "citania-merged.cpp"
  { NULL, NULL, NULL, NULL }
};

static short int nc = -1;

static int cmpcitanie(const void *a, const void *b) {
	return strcmp((const char *)a, ((struct citanie *)b)->kod);
}

static void initCitania() {
	if (nc == -1) {
		for (nc = 0; Citania[nc].kod; ++nc);
	}
}  

void checkCitania() {
	initCitania();
	for (nc=0; Citania[nc].kod; nc++) {
		if (nc > 0 && strcmp(Citania[nc - 1].kod, Citania[nc].kod) > 0) {
			fprintf(stderr, "Citania nie su utriedene! %s >= %s\n", Citania[nc - 1].kod, Citania[nc].kod);
		}
	}
}

struct citanie *najdiCitanie(const char *kod) {
	struct citanie *c;
	initCitania();
	c = (citanie *)bsearch(kod, Citania, nc, sizeof(struct citanie), cmpcitanie);
	if (!c) return NULL;
	if (!c->citania[0]) return NULL;
	return c;
};

static char nedelnyCyklus(_struct_dm *d) {
	return 'A' + nedelny_cyklus(d->den, d->mesiac, d->rok);
}

static char ferialnyCyklus(_struct_dm *d) {
	return '1' + ferialny_cyklus(d->den, d->mesiac, d->rok);
}

char *getCode(_struct_dm *d) {
	static char buf[100];

	if (d->smer == 1) { sprintf(buf, "%02d%02d%d", d->smer, d->litobd, d->denvt); // Velkonocne trojdnie
	} else if (d->smer == 2) { // niektore maju nedelny cyklus, niektore nie (Popolcova streda).
		if (d->meno[0]) {        // zatial dame pismeno cyklu vzdy; neublizi to.
			sprintf(buf, "%02d%c%s", d->smer, nedelnyCyklus(d), remove_diacritics(d->meno));
		} else {
			sprintf(buf, "%02d%c%02d%02d%02d", d->smer, nedelnyCyklus(d), d->litobd, d->tyzden, d->denvt);
		}
	} else if (d->smer <= 5) {
		sprintf(buf, "%02d%c%s", d->smer, nedelnyCyklus(d), remove_diacritics(d->meno));
	} else if (d->smer == 6) { // nedele vianocneho a cezrocneho obdobia
		sprintf(buf, "%02d%c%02d%02d", d->smer, nedelnyCyklus(d), d->litobd, d->tyzden);
	} else if (d->smer <= 8) {
		sprintf(buf, "%02d%s", d->smer, remove_diacritics(d->meno));
	} else if (d->smer <= 9) {
		if (d->smer == 9 && d->mesiac == 12 && d->den <=24) { // na konci adventu rozhoduje kalendarny datum
			sprintf(buf, "%02d%02d%02d", d->smer, d->litobd, d->den);
		} else if (d->litobd == OBD_OKTAVA_NARODENIA) {
			// V oktave Vianoc sa citania beru podla dna v oktave.
			sprintf(buf, "%02d%02d%d", d->smer, d->litobd, d->den - 24);
		} else {
			sprintf(buf, "%02d%c%02d%02d%02d", d->smer, ferialnyCyklus(d), d->litobd, d->tyzden, d->denvt);
		}
	} else if (d->smer <= 12) {
		sprintf(buf, "%02d%s", d->smer, remove_diacritics(d->meno));
	} else {
		if (d->litobd == OBD_VIANOCNE_I || d->litobd == OBD_VIANOCNE_II) {
			// Ferie vo Vianocnom obdobi su predpisane na dni kalendara.
			sprintf(buf, "%02d%c%02d%02d%02d", d->smer, ferialnyCyklus(d), d->litobd, d->den, d->mesiac);
		} else {
			// Ostatne ferie sa viazu na dni v tyzdni.
			sprintf(buf, "%02d%c%02d%02d%02d", d->smer, ferialnyCyklus(d), d->litobd, d->tyzden, d->denvt);
		}
	}
	return buf;
}

char *StringEncode(const char *in) {
	static unsigned char tab[17]="0123456789ABCDEF";
	int i;
	const char *s;
	static char out[65536];

	for (s=(const char *)in,i=0; i<(int)sizeof(out)-5 && *s; s++) {
		if ( 
			( (*s>='a')&&(*s<='z') ) ||
			( (*s>='A')&&(*s<='Z') ) ||
			( (*s>='0')&&(*s<='9') )
			) {
			out[i]=*s;
			i+=1;
		} else {
			out[i]='%';
			out[i+1]=tab[(*s) >> 4];
			out[i+2]=tab[(*s) & 0xf];
			i+=3;
		}
	}
	out[i]=0;
	return out;
}

#endif // LITURGICKE_CITANIA_ANDROID

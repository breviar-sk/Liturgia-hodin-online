#include "mysystem.h"
#include "mysysdef.h"
#include "citania.h"
#include "liturgia.h"
#include <string.h>
#include <stdlib.h>

#ifdef LITURGICKE_CITANIA

static struct citanie Citania[] = {
#include "citania-gen.cpp"
  { NULL, NULL, NULL, NULL }
};

static int nc = -1;

static int cmpcitanie(const void *a, const void *b) {
  return strcmp((const char *)a, ((struct citanie *)b)->kod);
}

struct citanie *najdiCitanie(const char *kod) {
  struct citanie *c;
  if (nc == -1) {
    for (nc=0; Citania[nc].kod; nc++);
  }
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
    } else {
      sprintf(buf, "%02d%c%02d%02d%02d", d->smer, ferialnyCyklus(d), d->litobd, d->tyzden, d->denvt);
    }
  } else if (d->smer <= 12) {
    sprintf(buf, "%02d%s", d->smer, remove_diacritics(d->meno));
  } else {
    sprintf(buf, "%02d%c%02d%02d%02d", d->smer, ferialnyCyklus(d), d->litobd, d->tyzden, d->denvt);
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

char *toUtf(const char *in) {
  char *i;
  const char *s;
  static char out[65536];

  out[0] = 0;
  for (s=in, i=out; *s && i-out<(int)sizeof(out)-5; i += strlen(i), s++) {
    switch(*s) {
      case '\x97': strcpy(i, "\xe2\x80"); break;
      case '\x96': strcpy(i, "\xe2\x80"); break;
      case '\xe1': strcpy(i, "\xc3\xa1"); break;
      case '\xe9': strcpy(i, "\xc3\xa9"); break;
      case '\xed': strcpy(i, "\xc3\xad"); break;
      case '\xf3': strcpy(i, "\xc3\xb3"); break;
      case '\xfa': strcpy(i, "\xc3\xba"); break;
      case '\xfd': strcpy(i, "\xc3\xbd"); break;
      case '\xc1': strcpy(i, "\xc3\x81"); break;
      case '\xc9': strcpy(i, "\xc3\x89"); break;
      case '\xcd': strcpy(i, "\xc3\x8d"); break;
      case '\xd3': strcpy(i, "\xc3\x93"); break;
      case '\xda': strcpy(i, "\xc3\x9a"); break;
      case '\xdd': strcpy(i, "\xc3\x9d"); break;
      case '\xe4': strcpy(i, "\xc3\xa4"); break;
      case '\xf4': strcpy(i, "\xc3\xb4"); break;
      case '\xec': strcpy(i, "\xc4\x9b"); break;
      case '\xf9': strcpy(i, "\xc5\xaf"); break;
      case '\xc4': strcpy(i, "\xc3\x84"); break;
      case '\xd4': strcpy(i, "\xc3\x94"); break;
      case '\xcc': strcpy(i, "\xc4\x9a"); break;
      case '\xd9': strcpy(i, "\xc5\xae"); break;
      case '\xe8': strcpy(i, "\xc4\x8d"); break;
      case '\xef': strcpy(i, "\xc4\x8f"); break;
      case '\xbe': strcpy(i, "\xc4\xbe"); break;
      case '\xf2': strcpy(i, "\xc5\x88"); break;
      case '\xf8': strcpy(i, "\xc5\x99"); break;
      case '\x9a': strcpy(i, "\xc5\xa1"); break;
      case '\x9d': strcpy(i, "\xc5\xa5"); break;
      case '\x9e': strcpy(i, "\xc5\xbe"); break;
      case '\xc8': strcpy(i, "\xc4\x8c"); break;
      case '\xcf': strcpy(i, "\xc4\x8e"); break;
      case '\xbc': strcpy(i, "\xc4\xbd"); break;
      case '\xd2': strcpy(i, "\xc5\x87"); break;
      case '\xd8': strcpy(i, "\xc5\x98"); break;
      case '\x8a': strcpy(i, "\xc5\xa0"); break;
      case '\x8d': strcpy(i, "\xc5\xa4"); break;
      case '\x8e': strcpy(i, "\xc5\xbd"); break;
      case '\xe5': strcpy(i, "\xc4\xba"); break;
      case '\xe0': strcpy(i, "\xc5\x95"); break;
      case '\xc5': strcpy(i, "\xc4\xb9"); break;
      case '\xc0': strcpy(i, "\xc5\x94"); break;
      case '\xfb': strcpy(i, "\xc5\xb1"); break;
      case '\xf5': strcpy(i, "\xc5\x91"); break;
      case '\xfc': strcpy(i, "\xc3\xbc"); break;
      case '\xf6': strcpy(i, "\xc3\xb6"); break;
      case '\xdb': strcpy(i, "\xc5\xb0"); break;
      case '\xd5': strcpy(i, "\xc5\x90"); break;
      case '\xdc': strcpy(i, "\xc3\x9c"); break;
      case '\xd6': strcpy(i, "\xc3\x96"); break;
      default: i[0] = *s; i[1] = 0;
    }/* switch */
  }
  return out;
}

#endif // LITURGICKE_CITANIA

#include <stdio.h>

#include "breviar.h"
#include "citania.h"
#include "liturgia.h"

void PrintDay(int r, int m, int d, _struct_dm* dm) {
  char* kod = getCode(dm);
  struct citanie* c = najdiCitanie(kod);
  const char* citania = "";
  const char* zalm = "";
  const char* aleluja = "";
  if (c != NULL) {
    citania = c->citania;
    zalm = c->zalm;
    aleluja = c->aleluja;
  }
  printf(" { \"%s\", \"%s\", \"%s\", \"%s\" },  /* %04d-%02d-%02d %s */\n", kod, citania, zalm, aleluja, r, m, d, dm->meno);
}

int main() {
  char ds[10], ms[10], ys[10];
  char *v[] = { "breviar", "-qpdt", ds, ms, ys, NULL };
  int D[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  int d,m,r;

  checkCitania();
  for (r = 2013; r <= 2013; r++) {
    for (m=12; m<=12; m++) {
      for (d=1; d<=D[m-1] + (m==2 && r%4==0); d++) {
        sprintf(ds, "-d%02d", d);
        sprintf(ms, "-m%02d", m);
        sprintf(ys, "-r%04d", r);
        breviar_main(5, v);
        PrintDay(r, m, d, &_global_den);
        if (_global_pocet_svatych >= 1) {
          PrintDay(r, m, d, &_global_svaty1);
        }
        if (_global_pocet_svatych >= 2) {
          PrintDay(r, m, d, &_global_svaty2);
        }
        if (_global_pocet_svatych >= 3) {
          PrintDay(r, m, d, &_global_svaty2);
        }
        _deallocate_global_var();
      }
    }
  }

  return 0;
}

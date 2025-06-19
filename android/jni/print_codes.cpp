#include <string>

#include <stdio.h>

#include "breviar.h"
#include "citania.h"
#include "liturgia.h"

std::string Escape(const char* s) {
  std::string out;
  while (*s) {
    switch(*s) {
      case '\\':
        out.append("\\\\");
        break;
      case '\n':
        out.append("\\n");
        break;
      case '"':
        out.append("\\\"");
        break;
      default:
        out.push_back(*s);
    }
    s++;
  }
  return out;
}

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
  printf(" { \"%s\", \"%s\", \"%s\", \"%s\" },  /* %04d-%02d-%02d %s */\n",
         Escape(kod).c_str(), Escape(citania).c_str(), Escape(zalm).c_str(),
         Escape(aleluja).c_str(), r, m, d, Escape(dm->meno).c_str());
}

int main() {
  char ds[10], ms[10], ys[10];
  const char *v[] = { "breviar", "-qpdt", ds, ms, ys, NULL };
  int D[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  int d,m,r;

  checkCitania();
  for (r = 2021; r <= 2021; r++) {
    for (m = 1; m <= 12; m++) {
      for (d=1; d<=D[m-1] + (m==2 && r%4==0); d++) {
        sprintf(ds, "-d%02d", d);
        sprintf(ms, "-m%02d", m);
        sprintf(ys, "-r%04d", r);
        breviar_main(5, v);
        PrintDay(r, m, d, &_global_den);
        for (int sv = 1; sv <= _global_pocet_svatych; ++sv) {
          PrintDay(r, m, d, &_global_svaty(sv));
        }
        _deallocate_global_var();
      }
    }
  }

  return 0;
}

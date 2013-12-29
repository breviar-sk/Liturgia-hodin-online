#ifndef __CITANIA_H_
#define __CITANIA_H_

#include "breviar.h"
#include "mysystem.h"
#include "mysysdef.h"

#ifdef LITURGICKE_CITANIA_ANDROID

struct citanie {
  const char *kod, *citania, *zalm, *aleluja;
};

void checkCitania();
struct citanie *najdiCitanie(const char *kod);
char *getCode(_struct_dm *d);

char *StringEncode(const char *in, bool utf_safe=false);
char *toUtf(const char *in);

#endif // LITURGICKE_CITANIA_ANDROID

#endif // __CITANIA_H_

/******************************************************************/
/*                                                                */
/* citania.h                                                      */
/* (c)2010-2019 | Richard Královič                                */
/*                                                                */
/* description | declarations of methods for liturgical readings  */
/*               for Android app                                  */
/*                                                                */
/******************************************************************/

#ifndef __CITANIA_H_
#define __CITANIA_H_

#include "breviar.h"
#include "mysystem.h"
#include "mysysdef.h"
#include "mydefs.h"
#include "common.h"

#ifdef LITURGICKE_CITANIA_ANDROID

struct citanie {
  const char *kod, *citania, *zalm, *aleluja;
};

void checkCitania();
struct citanie *najdiCitanie(const char *kod);
char *getCode(_struct_dm *d);

char *StringEncode(const char *in);
char *HtmlEncode(const char *in);

#endif // LITURGICKE_CITANIA_ANDROID

#endif // __CITANIA_H_

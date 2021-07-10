#include "utf8-utils.h"

#include <stdio.h>
#include <string.h>

#define EXPECT(condition, msg...) do {    \
  if (!condition) {                       \
    printf("Failure: "); printf(msg);     \
  } else {                                \
    printf("OK\n");                       \
  }                                       \
} while(0)

void TestChar(const char* s) {
  const char* in = s;
  int w = DecodeWchar(&in);
  printf("Testing %s:\n", s);
  EXPECT(0 == *in, "0 == %d\n", *in);

  char buf[10];
  char* out = buf;
  EncodeWchar(w, &out);
  *out = 0;
  EXPECT(!strcmp(in, out), "%s == %s\n", s, buf);
}

void TestFirstToLower() {
  {
    char s[] = "Ľšč4567";
    FirstToLower(s, 16);
    EXPECT(!strcmp(s, "ľšč4567"), "%s == %s\n", s, "ľšč4567");
  }
  {
    char s[] = "Ľšč4567";
    FirstToLower(s, 8);
    EXPECT(!strcmp(s, "ľšč4"), "%s == %s\n", s, "ľšč4");
  }
}

int main() {
  TestChar("ľ");
  TestChar("\xe2\xb0\xbf");

  TestFirstToLower();

  return 0;
}


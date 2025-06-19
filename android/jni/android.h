#include "mysystem.h"
#include "breviar.h"

#ifdef IO_ANDROID

extern FILE *stdin_pipe;
char *android_getenv(const char *name);
int android_putenv(const char *string);

#endif


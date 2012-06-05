#include "mysystem.h"
#include "breviar.h"

#ifdef IO_ANDROID

#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include <string.h>
#include <errno.h>
#include "myexpt.h"
#include "liturgia.h"
#include "citania.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <android/log.h>

static char *environment = NULL;
static char *environment2 = NULL;
static int envlen;
static int envlen2;
static jobject inst = NULL;
FILE *stdin_pipe = NULL;
static jobject out_fd;
static JNIEnv* jenv;

static void err(const char *msg) {
  __android_log_print(ANDROID_LOG_INFO, "Breviar", msg);
  exit(1);
}

jobject createFd(JNIEnv *env, int fdnum) {
  static jclass FDclass = NULL;
  static jmethodID cid = NULL;
  static jfieldID mDescriptor = NULL;
  jobject fd;

  if (!FDclass) {
    FDclass = env->FindClass("java/io/FileDescriptor");
    if (!FDclass) err("createFd: Cannot find class FileDescriptor");
    cid = env->GetMethodID(FDclass, "<init>", "()V");
    if (!cid) err("createFd: Cannot find constructor");
    mDescriptor = env->GetFieldID(FDclass, "descriptor", "I");
    if (!mDescriptor) err("createFd: Cannot find field descriptor");
  }
  fd = env->NewObject(FDclass, cid);
  env->SetIntField(fd, mDescriptor, fdnum);

  return fd;
}

int getFd(JNIEnv* env, jobject fd) {
  static jfieldID mDescriptor = NULL;
  if (mDescriptor==NULL) {
    jclass clazz;
    clazz = env->FindClass("java/io/FileDescriptor");
    if (!clazz) err("getFd: Cannot find class FileDescriptor");
    mDescriptor = env->GetFieldID(clazz, "descriptor", "I");
    if (!mDescriptor) err("getFd: Cannot find field descriptor");
  }
  return env->GetIntField(fd, mDescriptor);
}


FILE *fopen(const char *path, const char *mode) {
  FILE *out = NULL;
  static jclass server = NULL;
  static jmethodID reader = NULL;
  static jmethodID checkfile = NULL;

  if (mode[0] == 'w' || mode[0] == 'a') {
    if (strcmp(path, DEFAULT_FILE_EXPORT)) {
      // __android_log_print(ANDROID_LOG_INFO, "Breviar", "Trying to open file for writing:");
      // __android_log_print(ANDROID_LOG_INFO, "Breviar", path);
      return NULL;
    }
    out = fdopen(getFd(jenv, out_fd), "w");
  } else {
    int fd[2];
    if (!server) {
      server = jenv->FindClass("sk/breviar/android/Server");
      if (!server) err("fopen: Cannot find class Server");
      reader = jenv->GetMethodID(server, "reader", "(Ljava/lang/String;Ljava/io/FileDescriptor;)V");
      if (!reader) err("fopen: Cannot find method reader");
      checkfile = jenv->GetMethodID(server, "checkfile", "(Ljava/lang/String;)I");
      if (!checkfile) err("fopen: Cannot find method checkfile");
    }

    if (path[0] == '/') path++;
    //__android_log_print(ANDROID_LOG_INFO, "Breviar", path);
    
    jobject jfn = jenv->NewStringUTF(path);
    if (!jenv->CallIntMethod(inst, checkfile, jfn)) {
      out = NULL;
    } else {
      if (pipe(fd)) err("fopen: Cannot create pipe");
      jenv->CallVoidMethod(inst, reader, jfn, createFd(jenv, fd[1]));
      out = fdopen(fd[0], "r");
    }
  }
  return out;
}

char *getenv(const char *name) {
  // handled by java:
    // QUERY_STRING
    // REQUEST_METHOD
    // CONTENT_TYPE
    // CONTENT_LENTGTH
  char *i;
  int l, j;
  char *S[2] = { environment2, environment };
  int L[2] = { envlen2, envlen };

  l = strlen(name);

  //__android_log_print(ANDROID_LOG_INFO, "Breviar", "getenv:");
  //__android_log_print(ANDROID_LOG_INFO, "Breviar", name);

  for (j=0; j<2; j++) {
    for (i=S[j]; i-S[j] < L[j]; i += strlen(i)+1) {
      if (strncmp(i, name, l)==0 && i[l]=='=') {
        //__android_log_print(ANDROID_LOG_INFO, "Breviar", "getenv return:");
        //__android_log_print(ANDROID_LOG_INFO, "Breviar", i+l+1);
        return (i+l+1);
      }
    }
  }
  return NULL;
}

int putenv(const char *string) {
  char *env3;
  int envlen3;
  int len = strlen(string);

  //__android_log_print(ANDROID_LOG_INFO, "Breviar", "putenv:");
  //__android_log_print(ANDROID_LOG_INFO, "Breviar", string);

  envlen3 = len+1 + envlen2;
  if (! (env3 = (char *)malloc(envlen3)) ) return 0;
  strcpy(env3, string);
  if (envlen2) memcpy(env3+len+1, environment2, envlen2);
  free(environment2);
  environment2 = env3;
  envlen2 = envlen3;
  return 1;
}

int main(int argc, const char **argv);

void closeFd(JNIEnv* env, jobject fd) {
  close(getFd(env, fd));
}

extern "C" {

JNIEXPORT jstring JNICALL Java_sk_breviar_android_Server_main(JNIEnv* env, jobject thiz, jobject outfd, jobject infd, jstring environ) {
  const char* params[] = { "breviar.cgi", NULL };
  jstring jout;

//  __android_log_print(ANDROID_LOG_INFO, "Breviar", "starting Server.main");
  inst = thiz;
  environment = (char *)env->GetStringUTFChars(environ, NULL);
  envlen = env->GetStringUTFLength(environ);
  environment2 = NULL;
  envlen2 = 0;
  for (char *i = environment; *i; i++)
    if (*i==1) *i = 0;
  jenv = env;
  out_fd = outfd;
  stdin_pipe = fdopen(getFd(env, infd), "r");
  //int nullfd = open("/dev/null", O_RDONLY);
  //stdin_pipe = fdopen(nullfd, "r");
  
//  __android_log_print(ANDROID_LOG_INFO, "Breviar", "calling main");
  main(1, params);
//  __android_log_print(ANDROID_LOG_INFO, "Breviar", "main finished");
  char pom2[MAX_STR], pom3[MAX_STR];
  strcpy(pom2, ""); strcpy(pom3, "");
  prilep_request_options(pom2, pom3);
  jout = env->NewStringUTF(StringEncode(pom2, true));
//  __android_log_print(ANDROID_LOG_INFO, "Breviar", "prilep_request_options finished");

  env->ReleaseStringUTFChars(environ, environment);
  if (envlen2) free(environment2);
  inst = NULL;

  fclose(stdin_pipe);
  stdin_pipe = NULL;

  // should be closed by main
  out_fd = NULL;
  jenv = NULL;

  return jout;
}

JNIEXPORT void JNICALL Java_sk_breviar_android_FdInputStream_closefd(JNIEnv* env, jclass thiz, jobject fd) { closeFd(env, fd); }
JNIEXPORT void JNICALL Java_sk_breviar_android_FdOutputStream_closefd(JNIEnv* env, jclass thiz, jobject fd) { closeFd(env, fd); }

JNIEXPORT jobjectArray JNICALL Java_sk_breviar_android_Server_createPipe(JNIEnv* env, jobject thiz) {
  int fd[2];
  jobjectArray res;
  static jclass fdcls = NULL;

  if (!fdcls) {
    fdcls = env->FindClass("java/io/FileDescriptor");
    if (!fdcls) err("createPipe: Cannot find class FileDescriptor");
  }

  if (pipe(fd)) {
    __android_log_print(ANDROID_LOG_INFO, "Breviar", strerror(errno));
    return NULL;
  }
  res = env->NewObjectArray(2, fdcls, NULL);
  env->SetObjectArrayElement(res, 0, createFd(env, fd[0]));
  env->SetObjectArrayElement(res, 1, createFd(env, fd[1]));

  return res;
}

}

#endif


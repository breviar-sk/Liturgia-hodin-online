LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := libbreviar

LOCAL_SRC_FILES := android.cpp breviar.cpp cgiutils.cpp dbzaltar.cpp \
                   liturgia.cpp myconf.cpp mydefs.cpp myexpt.cpp \
		   mygetopt.cpp myhpage.cpp mylog.cpp mystring.cpp

LOCAL_LDLIBS    := -llog
LOCAL_CFLAGS    := -DMODEL_SELECTED_IN_MAKEFILE -DMODEL_android

#LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

#$(call import-module,android/native_app_glue)

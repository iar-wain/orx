LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := orx
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/liborx.a
LOCAL_STATIC_LIBRARIES := LiquidFun-prebuilt Tremolo-prebuilt OpenAL-prebuilt WebP-prebuilt android_native_app_glue

TARGET_PLATFORM = android-9

LOCAL_EXPORT_CFLAGS := -DTARGET_OS_ANDROID_NATIVE
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../../include
LOCAL_EXPORT_LDLIBS := -llog -lGLESv2 -landroid -lEGL

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := orxd
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/liborxd.a
LOCAL_STATIC_LIBRARIES := LiquidFun-prebuilt Tremolo-prebuilt OpenAL-prebuilt WebP-prebuilt android_native_app_glue

TARGET_PLATFORM = android-9

LOCAL_EXPORT_CFLAGS := -DTARGET_OS_ANDROID_NATIVE -D__orxDEBUG__
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../../include
LOCAL_EXPORT_LDLIBS := -llog -lGLESv2 -landroid -lEGL

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := orxp
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/liborxp.a
LOCAL_STATIC_LIBRARIES := LiquidFun-prebuilt Tremolo-prebuilt OpenAL-prebuilt WebP-prebuilt android_native_app_glue

TARGET_PLATFORM = android-9

LOCAL_EXPORT_CFLAGS := -DTARGET_OS_ANDROID_NATIVE -D__orxPROFILER__
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../../include
LOCAL_EXPORT_LDLIBS := -llog -lGLESv2 -landroid -lEGL

include $(PREBUILT_STATIC_LIBRARY)

$(call import-module,../extern/LiquidFun-1.1.0/lib/android)
$(call import-module,../extern/openal-soft/lib/android)
$(call import-module,../extern/Tremolo/lib/android)
$(call import-module,../extern/libwebp/lib/android)
$(call import-module,android/native_app_glue)

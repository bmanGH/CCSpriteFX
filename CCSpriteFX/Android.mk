LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := ccspritefx_static
LOCAL_MODULE_FILENAME := libccspritefx

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_SRC_FILES := \
CCActionColorMatrix.cpp \
CCActionTextureTransform.cpp \
CCColorMatrix.cpp \
CCColorMatrixShader.cpp \
CCSpriteFX.cpp \
CCTextureTransformShader.cpp

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..
                                 
include $(BUILD_STATIC_LIBRARY)

$(call import-module,2d)
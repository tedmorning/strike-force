LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellocpp_shared

LOCAL_MODULE_FILENAME := libhellocpp



FILE_LIST := hellocpp/main.cpp 
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp) 
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/scene/*.cpp) 
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/dialog/*.cpp) 
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/data/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/common/*.cpp) 
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/ccxGUI/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/ccxGUI/ccxControl/*.cpp)  
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%) 
				   
				   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/scene
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/data
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/common
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/dialog
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/ccxGUI
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/ccxGUI/ccxControl
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/ZG


LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)
$(call import-module,external/Box2D)
$(call import-module,extensions)
$(call import-module,CocosDenshion/android)

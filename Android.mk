#	MakeFile to build PoC for Android.
#
#	In order for this to work you need to setup an Android 
# project. If you have the SDL2 source code, look at its README.android.
# 
# poc/
#	 jni/
#		SDL2/				<--- Library Files go here.
#		src/				<--- Source files go here.
#			engine
#			Android.mk
#

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main  				#If changed, also change in SDLActivity.java

SDL_PATH := ../SDL2

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/$(SDL_PATH)/include 	\
	$(LOCAL_PATH)/$(SDL_PATH) 			\
	$(LOCAL_PATH)/../SDL_image			\
	$(LOCAL_PATH)/engine
	

LOCALCFLAGS:= -DSDL_NO_COMPAT -DSDL_VIDEO_RENDER_OGL_ES2=0
LOCAL_CPPFLAGS := -c -std=gnu++0x  -Wall -pedantic #-std=c++0x

# Add your application source files here...
LOCAL_SRC_FILES := 			\
	$(SDL_PATH)/src/main/android/SDL_android_main.cpp \
	engine/main.cpp 		\
	engine/engine.cpp 		\
	engine/window.cpp 		\
	engine/character.cpp	\
	engine/player.cpp 		\
	engine/animation.cpp	\
	engine/component/input.cpp	\
	engine/component/animation.cpp	\
	engine/component/physics.cpp

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image 

LOCAL_LDLIBS := -llog -lGLESv1_CM #-lstdc++

include $(BUILD_SHARED_LIBRARY)

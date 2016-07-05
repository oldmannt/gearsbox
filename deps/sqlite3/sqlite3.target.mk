# This file is generated by gyp; do not edit.

include $(CLEAR_VARS)

LOCAL_MODULE_CLASS := STATIC_LIBRARIES
LOCAL_MODULE := sqlite3
LOCAL_MODULE_SUFFIX := .a
LOCAL_MODULE_TARGET_ARCH := $(TARGET_$(GYP_VAR_PREFIX)ARCH)
LOCAL_SDK_VERSION := 19
gyp_intermediate_dir := $(call local-intermediates-dir,,$(GYP_VAR_PREFIX))
gyp_shared_intermediate_dir := $(call intermediates-dir-for,GYP,shared,,,$(GYP_VAR_PREFIX))

# Make sure our deps are built first.
GYP_TARGET_DEPENDENCIES :=

GYP_GENERATED_OUTPUTS :=

# Make sure our deps and generated files are built first.
LOCAL_ADDITIONAL_DEPENDENCIES := $(GYP_TARGET_DEPENDENCIES) $(GYP_GENERATED_OUTPUTS)

LOCAL_GENERATED_SOURCES :=

GYP_COPIED_SOURCE_ORIGIN_DIRS :=

LOCAL_SRC_FILES := \
	deps/sqlite3/sqlite3.c


# Flags passed to both C and C++ files.
MY_CFLAGS_Debug := \
	-gdwarf-2 \
	-Wall \
	-Wno-missing-field-initializers \
	-DHAVE_USLEEP=1 \
	-DSQLITE_TEMP_STORE=3 \
	-Wno-unused-const-variable \
	-Wno-unused-parameter \
	-g \
	-O0 \
	-DDEBUG=1

MY_DEFS_Debug := \
	'-DHAVE_USLEEP=1' \
	'-DSQLITE_TEMP_STORE=3' \
	'-DDEBUG=1'


# Include paths placed before CFLAGS/CPPFLAGS
LOCAL_C_INCLUDES_Debug := \
	$(LOCAL_PATH)/deps/sqlite3 \
	$(LOCAL_PATH)/deps/sqlite3/sqlite3


# Flags passed to only C++ (and not C) files.
LOCAL_CPPFLAGS_Debug := \
	-std=c++11 \
	-frtti \
	-fexceptions \
	-Wno-literal-suffix


# Flags passed to both C and C++ files.
MY_CFLAGS_Release := \
	-gdwarf-2 \
	-Wall \
	-Wno-missing-field-initializers \
	-DHAVE_USLEEP=1 \
	-DSQLITE_TEMP_STORE=3 \
	-Wno-unused-const-variable \
	-Wno-unused-parameter \
	-Os \
	-fomit-frame-pointer \
	-fdata-sections \
	-ffunction-sections \
	-DNDEBUG=1

MY_DEFS_Release := \
	'-DHAVE_USLEEP=1' \
	'-DSQLITE_TEMP_STORE=3' \
	'-DNDEBUG=1'


# Include paths placed before CFLAGS/CPPFLAGS
LOCAL_C_INCLUDES_Release := \
	$(LOCAL_PATH)/deps/sqlite3 \
	$(LOCAL_PATH)/deps/sqlite3/sqlite3


# Flags passed to only C++ (and not C) files.
LOCAL_CPPFLAGS_Release := \
	-std=c++11 \
	-frtti \
	-fexceptions \
	-Wno-literal-suffix


LOCAL_CFLAGS := $(MY_CFLAGS_$(GYP_CONFIGURATION)) $(MY_DEFS_$(GYP_CONFIGURATION))
LOCAL_C_INCLUDES := $(GYP_COPIED_SOURCE_ORIGIN_DIRS) $(LOCAL_C_INCLUDES_$(GYP_CONFIGURATION))
LOCAL_CPPFLAGS := $(LOCAL_CPPFLAGS_$(GYP_CONFIGURATION))
LOCAL_ASFLAGS := $(LOCAL_CFLAGS)
### Rules for final target.
include $(BUILD_STATIC_LIBRARY)

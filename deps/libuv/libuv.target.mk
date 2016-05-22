# This file is generated by gyp; do not edit.

include $(CLEAR_VARS)

LOCAL_MODULE_CLASS := STATIC_LIBRARIES
LOCAL_MODULE := libuv
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
	gearsbox/deps/libuv/src/fs-poll.c \
	gearsbox/deps/libuv/src/inet.c \
	gearsbox/deps/libuv/src/threadpool.c \
	gearsbox/deps/libuv/src/uv-common.c \
	gearsbox/deps/libuv/src/version.c \
	gearsbox/deps/libuv/src/unix/async.c \
	gearsbox/deps/libuv/src/unix/core.c \
	gearsbox/deps/libuv/src/unix/dl.c \
	gearsbox/deps/libuv/src/unix/fs.c \
	gearsbox/deps/libuv/src/unix/getaddrinfo.c \
	gearsbox/deps/libuv/src/unix/getnameinfo.c \
	gearsbox/deps/libuv/src/unix/loop.c \
	gearsbox/deps/libuv/src/unix/loop-watcher.c \
	gearsbox/deps/libuv/src/unix/pipe.c \
	gearsbox/deps/libuv/src/unix/poll.c \
	gearsbox/deps/libuv/src/unix/process.c \
	gearsbox/deps/libuv/src/unix/signal.c \
	gearsbox/deps/libuv/src/unix/stream.c \
	gearsbox/deps/libuv/src/unix/tcp.c \
	gearsbox/deps/libuv/src/unix/thread.c \
	gearsbox/deps/libuv/src/unix/timer.c \
	gearsbox/deps/libuv/src/unix/tty.c \
	gearsbox/deps/libuv/src/unix/udp.c \
	gearsbox/deps/libuv/src/unix/proctitle.c \
	gearsbox/deps/libuv/src/unix/linux-core.c \
	gearsbox/deps/libuv/src/unix/linux-inotify.c \
	gearsbox/deps/libuv/src/unix/linux-syscalls.c \
	gearsbox/deps/libuv/src/unix/pthread-fixes.c \
	gearsbox/deps/libuv/src/unix/android-ifaddrs.c \
	gearsbox/deps/libuv/src/unix/pthread-barrier.c


# Flags passed to both C and C++ files.
MY_CFLAGS_Debug := \
	-gdwarf-2 \
	-Werror \
	-Wall \
	-Wextra \
	-Wno-missing-field-initializers \
	-fvisibility=hidden \
	-g \
	--std=gnu89 \
	-pedantic \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-Wstrict-aliasing \
	-g \
	-O0 \
	-DDEBUG=1

MY_DEFS_Debug := \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DDEBUG=1'


# Include paths placed before CFLAGS/CPPFLAGS
LOCAL_C_INCLUDES_Debug := \
	$(LOCAL_PATH)/gearsbox/deps/libuv/include \
	$(LOCAL_PATH)/gearsbox/deps/libuv/src


# Flags passed to only C++ (and not C) files.
LOCAL_CPPFLAGS_Debug := \
	-std=c++11 \
	-frtti \
	-fexceptions \
	-Wno-literal-suffix


# Flags passed to both C and C++ files.
MY_CFLAGS_Release := \
	-gdwarf-2 \
	-Werror \
	-Wall \
	-Wextra \
	-Wno-missing-field-initializers \
	-fvisibility=hidden \
	-g \
	--std=gnu89 \
	-pedantic \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-Wstrict-aliasing \
	-Os \
	-fomit-frame-pointer \
	-fdata-sections \
	-ffunction-sections \
	-DNDEBUG=1

MY_DEFS_Release := \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DNDEBUG=1'


# Include paths placed before CFLAGS/CPPFLAGS
LOCAL_C_INCLUDES_Release := \
	$(LOCAL_PATH)/gearsbox/deps/libuv/include \
	$(LOCAL_PATH)/gearsbox/deps/libuv/src


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

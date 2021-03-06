# This file is generated by gyp; do not edit.

include $(CLEAR_VARS)

LOCAL_MODULE_CLASS := STATIC_LIBRARIES
LOCAL_MODULE := libcurl
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
	gearsbox/deps/curl/src/amigaos.c \
	gearsbox/deps/curl/src/asyn-ares.c \
	gearsbox/deps/curl/src/asyn-thread.c \
	gearsbox/deps/curl/src/axtls.c \
	gearsbox/deps/curl/src/base64.c \
	gearsbox/deps/curl/src/bundles.c \
	gearsbox/deps/curl/src/conncache.c \
	gearsbox/deps/curl/src/connect.c \
	gearsbox/deps/curl/src/content_encoding.c \
	gearsbox/deps/curl/src/cookie.c \
	gearsbox/deps/curl/src/curl_addrinfo.c \
	gearsbox/deps/curl/src/curl_darwinssl.c \
	gearsbox/deps/curl/src/curl_fnmatch.c \
	gearsbox/deps/curl/src/curl_gethostname.c \
	gearsbox/deps/curl/src/curl_gssapi.c \
	gearsbox/deps/curl/src/curl_memrchr.c \
	gearsbox/deps/curl/src/curl_multibyte.c \
	gearsbox/deps/curl/src/curl_ntlm.c \
	gearsbox/deps/curl/src/curl_ntlm_core.c \
	gearsbox/deps/curl/src/curl_ntlm_msgs.c \
	gearsbox/deps/curl/src/curl_ntlm_wb.c \
	gearsbox/deps/curl/src/curl_rtmp.c \
	gearsbox/deps/curl/src/curl_sasl.c \
	gearsbox/deps/curl/src/curl_schannel.c \
	gearsbox/deps/curl/src/curl_sspi.c \
	gearsbox/deps/curl/src/curl_threads.c \
	gearsbox/deps/curl/src/cyassl.c \
	gearsbox/deps/curl/src/dict.c \
	gearsbox/deps/curl/src/dotdot.c \
	gearsbox/deps/curl/src/easy.c \
	gearsbox/deps/curl/src/escape.c \
	gearsbox/deps/curl/src/file.c \
	gearsbox/deps/curl/src/fileinfo.c \
	gearsbox/deps/curl/src/formdata.c \
	gearsbox/deps/curl/src/ftp.c \
	gearsbox/deps/curl/src/ftplistparser.c \
	gearsbox/deps/curl/src/getenv.c \
	gearsbox/deps/curl/src/getinfo.c \
	gearsbox/deps/curl/src/gopher.c \
	gearsbox/deps/curl/src/gskit.c \
	gearsbox/deps/curl/src/gtls.c \
	gearsbox/deps/curl/src/hash.c \
	gearsbox/deps/curl/src/hmac.c \
	gearsbox/deps/curl/src/hostasyn.c \
	gearsbox/deps/curl/src/hostcheck.c \
	gearsbox/deps/curl/src/hostip.c \
	gearsbox/deps/curl/src/hostip4.c \
	gearsbox/deps/curl/src/hostip6.c \
	gearsbox/deps/curl/src/hostsyn.c \
	gearsbox/deps/curl/src/http.c \
	gearsbox/deps/curl/src/http2.c \
	gearsbox/deps/curl/src/http_chunks.c \
	gearsbox/deps/curl/src/http_digest.c \
	gearsbox/deps/curl/src/http_negotiate.c \
	gearsbox/deps/curl/src/http_negotiate_sspi.c \
	gearsbox/deps/curl/src/http_proxy.c \
	gearsbox/deps/curl/src/idn_win32.c \
	gearsbox/deps/curl/src/if2ip.c \
	gearsbox/deps/curl/src/imap.c \
	gearsbox/deps/curl/src/inet_ntop.c \
	gearsbox/deps/curl/src/inet_pton.c \
	gearsbox/deps/curl/src/krb5.c \
	gearsbox/deps/curl/src/ldap.c \
	gearsbox/deps/curl/src/llist.c \
	gearsbox/deps/curl/src/md4.c \
	gearsbox/deps/curl/src/md5.c \
	gearsbox/deps/curl/src/memdebug.c \
	gearsbox/deps/curl/src/mprintf.c \
	gearsbox/deps/curl/src/multi.c \
	gearsbox/deps/curl/src/netrc.c \
	gearsbox/deps/curl/src/non-ascii.c \
	gearsbox/deps/curl/src/nonblock.c \
	gearsbox/deps/curl/src/nss.c \
	gearsbox/deps/curl/src/nwlib.c \
	gearsbox/deps/curl/src/nwos.c \
	gearsbox/deps/curl/src/openldap.c \
	gearsbox/deps/curl/src/parsedate.c \
	gearsbox/deps/curl/src/pingpong.c \
	gearsbox/deps/curl/src/pipeline.c \
	gearsbox/deps/curl/src/polarssl.c \
	gearsbox/deps/curl/src/polarssl_threadlock.c \
	gearsbox/deps/curl/src/pop3.c \
	gearsbox/deps/curl/src/progress.c \
	gearsbox/deps/curl/src/qssl.c \
	gearsbox/deps/curl/src/rawstr.c \
	gearsbox/deps/curl/src/rtsp.c \
	gearsbox/deps/curl/src/security.c \
	gearsbox/deps/curl/src/select.c \
	gearsbox/deps/curl/src/sendf.c \
	gearsbox/deps/curl/src/share.c \
	gearsbox/deps/curl/src/slist.c \
	gearsbox/deps/curl/src/smtp.c \
	gearsbox/deps/curl/src/socks.c \
	gearsbox/deps/curl/src/socks_gssapi.c \
	gearsbox/deps/curl/src/socks_sspi.c \
	gearsbox/deps/curl/src/speedcheck.c \
	gearsbox/deps/curl/src/splay.c \
	gearsbox/deps/curl/src/ssh.c \
	gearsbox/deps/curl/src/sslgen.c \
	gearsbox/deps/curl/src/ssluse.c \
	gearsbox/deps/curl/src/strdup.c \
	gearsbox/deps/curl/src/strequal.c \
	gearsbox/deps/curl/src/strerror.c \
	gearsbox/deps/curl/src/strtok.c \
	gearsbox/deps/curl/src/strtoofft.c \
	gearsbox/deps/curl/src/telnet.c \
	gearsbox/deps/curl/src/tftp.c \
	gearsbox/deps/curl/src/timeval.c \
	gearsbox/deps/curl/src/transfer.c \
	gearsbox/deps/curl/src/url.c \
	gearsbox/deps/curl/src/version.c \
	gearsbox/deps/curl/src/warnless.c \
	gearsbox/deps/curl/src/wildcard.c \
	gearsbox/deps/curl/src/x509asn1.c


# Flags passed to both C and C++ files.
MY_CFLAGS_Debug := \
	-gdwarf-2 \
	-Werror \
	-Wall \
	-Wextra \
	-Wno-missing-field-initializers \
	-g \
	-O0 \
	-DDEBUG=1

MY_DEFS_Debug := \
	'-DDEBUG=1'


# Include paths placed before CFLAGS/CPPFLAGS
LOCAL_C_INCLUDES_Debug := \
	$(LOCAL_PATH)/gearsbox/deps/curl \
	$(LOCAL_PATH)/gearsbox/deps/curl/curl


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
	-Os \
	-fomit-frame-pointer \
	-fdata-sections \
	-ffunction-sections \
	-DNDEBUG=1

MY_DEFS_Release := \
	'-DNDEBUG=1'


# Include paths placed before CFLAGS/CPPFLAGS
LOCAL_C_INCLUDES_Release := \
	$(LOCAL_PATH)/gearsbox/deps/curl \
	$(LOCAL_PATH)/gearsbox/deps/curl/curl


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

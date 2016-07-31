//
//  macro.h
//  gearsbox
//
//  Created by dyno on 7/27/16.
//
//

#ifndef macro_h
#define macro_h

#include "ilog.h"

#ifdef	NDEBUG
#define		CHECK(x, ...)	{ if(!(x)) { g_logout(LOG_FILE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); } }
#define		CHECK_RT(x, ...)	{ if(!(x)) { g_logout(LOG_FILE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); return;} }
#define		CHECK_F(x, ...)	{ if(!(x)) { g_logout(LOG_FILE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); return false;} }
#define		CHECK_P(x,p, ...)	{ if(!(x)) { g_logout(LOG_FILE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); return p;} }
#else
#define		CHECK(x, ...)	{ if(!(x)) { g_logout(LOG_FILE|LOG_CONSOLE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); } }
#define		CHECK_RT(x, ...)	{ if(!(x)) { g_logout(LOG_FILE|LOG_CONSOLE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); return;} }
#define		CHECK_F(x, ...)	{ if(!(x)) { g_logout(LOG_FILE|LOG_CONSOLE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); return false;} }
#define		CHECK_P(x,p, ...)	{ if(!(x)) { g_logout(LOG_FILE|LOG_CONSOLE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); return p;} }
#endif

#endif /* macro_h */

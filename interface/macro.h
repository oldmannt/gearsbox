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
#include "utils.hpp"

#ifdef	NDEBUG
#define		CHECK(x, ...)	{ if(!(x)) { g_logout(LOG_FILE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); } }
#define		CHECK_RT(x, ...)	{ if(!(x)) { g_logout(LOG_FILE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); return;} }
#define		CHECK_RTF(x, ...)	{ if(!(x)) { g_logout(LOG_FILE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); return false;} }
#define		CHECK_RTP(x,p, ...)	{ if(!(x)) { g_logout(LOG_FILE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); return p;} }
#define		CHECK_RTNULL(x, ...)	{ if(!(x)) { g_logout(LOG_FILE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); return nullptr;} }

#define     CONTINUE(x, ...) { if(!(x)) { g_logout(LOG_FILE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); continue;} }
#define     BREAK(x, ...) { if(!(x)) { g_logout(LOG_FILE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); break;} }

#define     TEST_EQ(x,y, s) 
#define     TEST_NQ(x,y, s)
#define     TEST_LT(x,y, s)
#define     TEST_LE(x,y, s)

#else
#define		CHECK(x, ...)	{ if(!(x)) { g_logout(LOG_FILE|LOG_CONSOLE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); } }
#define		CHECK_RT(x, ...)	{ if(!(x)) { g_logout(LOG_FILE|LOG_CONSOLE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); return;} }
#define		CHECK_RTF(x, ...)	{ if(!(x)) { g_logout(LOG_FILE|LOG_CONSOLE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); return false;} }
#define		CHECK_RTP(x,p, ...)	{ if(!(x)) { g_logout(LOG_FILE|LOG_CONSOLE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); return p;} }
#define		CHECK_RTNULL(x, ...)	{ if(!(x)) { g_logout(LOG_FILE|LOG_CONSOLE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); return nullptr;} }

#define     CONTINUE(x, ...) { if(!(x)) { g_logout(LOG_FILE|LOG_CONSOLE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); continue;} }
#define     BREAK(x, ...) { if(!(x)) { g_logout(LOG_FILE|LOG_CONSOLE, LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__); break;} }

#define     TEST_EQ(x,y, s) {\
                        if(x==y)\
                            g_logout(LOG_FILE, LOG_INFO, __FUNCTION__, __FILE__, __LINE__, "%s test equal ok", s);\
                        else\
                            g_logout(LOG_FILE, LOG_INFO, __FUNCTION__, __FILE__, __LINE__, "%s test equal failed x:%s y:%s", s, std::to_string(x).c_str(), std::to_string(y).c_str());}

#define     TEST_NQ(x,y, s) {\
                        if(x!=y)\
                            g_logout(LOG_FILE, LOG_INFO, __FUNCTION__, __FILE__, __LINE__, "%s test equal ok", s);\
                        else\
                            g_logout(LOG_FILE, LOG_INFO, __FUNCTION__, __FILE__, __LINE__, "%s test not equal failed x:%s y:%s", s, std::to_string(x).c_str(), std::to_string(y).c_str());}

#define     TEST_LT(x,y, s) {\
                        if(x<y)\
                            g_logout(LOG_FILE, LOG_INFO, __FUNCTION__, __FILE__, __LINE__, "%s test less than ok", s);\
                        else\
                            g_logout(LOG_FILE, LOG_INFO, __FUNCTION__, __FILE__, __LINE__, "%s test less than failed x:%s y:%s", s, std::to_string(x).c_str(), std::to_string(y).c_str());}

#define     TEST_LE(x,y, s) {\
                        if(x<=y)\
                            g_logout(LOG_FILE, LOG_INFO, __FUNCTION__, __FILE__, __LINE__, "%s test less equal than ok", s);\
                        else\
                            g_logout(LOG_FILE, LOG_INFO, __FUNCTION__, __FILE__, __LINE__, "%s test less equal than failed x:%s y:%s", s, std::to_string(x).c_str(), std::to_string(y).c_str());}

#endif



#endif /* macro_h */

/*
 * @file trace.h
 *
 * @brief A simple trace macro which can be controlled by individual modules,
 * or if brave, the entire program.
 *
 * (c) Delaney & Morgan Computing 2009-2010.
 * <admin@delaneymorgan.com.au>
 * Anyone is free to copy this software as is, or modified as long as
 * this attribution remains. i.e. no complicated licences, no lawyers,
 * and no restrictions. Just use it, enjoy it, and relax.
 * We won't hassle you about it if you don't hassle us.
 * 
 * To use:
 * 
 *     In client module:
 *         #define TRACE_ON
 *         #include "include/trace.h
 * 
 *     In client functions/methods:
 *         TRACE_START();
 *         TRACE_START( "myVariable: %d", myVariable);
 *         TRACE_END();
 *         TRACE_END( "myVariable: %d", myVariable);
 *
 * To disable:
 *     // #define TRACE_ON
 */

#ifndef TRACE_H_
#define TRACE_H_


#include "macros.h"

#if defined( _WIN32) && defined( TRACE_ON)
// VS C/C++

#include <processthreadsapi.h>

/**
 * NOTE: these macros will trigger the following warning:
 * 
 *     C4003: not enough arguments for function-like macro invocation
 * 
 * Unfortunately this is a standards issue with the VS pre-processor.  Runs as expected though.
 * 
 * VS has an "/experimental:preprocessor" option which should fix this, otherwise just disable the C4003 warning.
 * Or just ignore the warnings - you wouldn't leave trace on in a production build anyway.
 * 
 */

#define DETAIL_STRING_FORMAT "(%lu)%s::%s:%d "
#define START_STRING_FORMAT "Starting " DETAIL_STRING_FORMAT
#define END_STRING_FORMAT "Ending " DETAIL_STRING_FORMAT
#define CHECK_STRING_FORMAT "Check " DETAIL_STRING_FORMAT
#define CHANGE_STRING_FORMAT "Change " DETAIL_STRING_FORMAT

#define TRACE_START( format, ... ) \
    do { \
        printf( START_STRING_FORMAT format "\n", GetCurrentThreadId(), __FILE__, __PRETTY_FUNCTION__,  __LINE__, ##__VA_ARGS__ ); \
        fflush( stdout); \
    } while (0)

#define TRACE_END( format, ... ) \
    do { \
        printf( END_STRING_FORMAT format "\n", GetCurrentThreadId(), __FILE__, __PRETTY_FUNCTION__,  __LINE__, ##__VA_ARGS__ ); \
        fflush( stdout); \
    } while (0)

#define TRACE_CHECK( format, ... ) \
    do { \
        printf( CHECK_STRING_FORMAT format "\n", GetCurrentThreadId(), __FILE__, __PRETTY_FUNCTION__,  __LINE__, ##__VA_ARGS__ ); \
        fflush( stdout); \
    } while (0)

#define TRACE_SINGLE_CHECK( format, ...) \
    do { \
        static bool firstTime = true; \
        if (firstTime) \
        { \
            firstTime = false; \
            printf( CHECK_STRING_FORMAT format "\n", GetCurrentThreadId(), __FILE__, __PRETTY_FUNCTION__,  __LINE__, ##__VA_ARGS__ ); \
            fflush( stdout); \
        } \
    } while (0)

#define TRACE_ON_CHANGE( format, ...) \
    do { \
        static std::string lastTime;  \
        size_t size = std::snprintf( NULL, 0, format, ##__VA_ARGS__ ); \
        char buf[size + 1]; \
        snprintf( buf, sizeof( buf ), format, ##__VA_ARGS__ ); \
        std::string thisTime( buf ); \
        if (thisTime != lastTime) \
        { \
            lastTime = thisTime; \
            printf( CHANGE_STRING_FORMAT " %s\n", pthread_self(), __FILE__, __PRETTY_FUNCTION__,  __LINE__, thisTime.c_str() ); \
            fflush( stdout); \
        } \
    } while (0)

#elif defined(__GNUG__) && defined( TRACE_ON)
// GNU C++

#include <cstdio>
#include <unistd.h>

#define DETAIL_STRING_FORMAT "(%u)%s::%s:%d "
#define START_STRING_FORMAT "Starting " DETAIL_STRING_FORMAT
#define END_STRING_FORMAT "Ending " DETAIL_STRING_FORMAT
#define CHECK_STRING_FORMAT "Check " DETAIL_STRING_FORMAT
#define CHANGE_STRING_FORMAT "Change " DETAIL_STRING_FORMAT

#define TRACE_START(format, ...) \
    do { \
        printf( START_STRING_FORMAT format "\n", gettid(), __FILE__, __PRETTY_FUNCTION__,  __LINE__, ##__VA_ARGS__); \
        fflush( stdout); \
    } while (0)

#define TRACE_END(format, ...) \
    do { \
        printf( END_STRING_FORMAT format "\n", gettid(), __FILE__, __PRETTY_FUNCTION__,  __LINE__, ##__VA_ARGS__); \
        fflush( stdout); \
    } while (0)

#define TRACE_CHECK(format, ...) \
    do { \
        printf( CHECK_STRING_FORMAT format "\n", gettid(), __FILE__, __PRETTY_FUNCTION__,  __LINE__, ##__VA_ARGS__); \
        fflush( stdout); \
    } while (0)

#define TRACE_SINGLE_CHECK( format, ...) \
    do { \
        static bool firstTime = true; \
        if (firstTime) \
        { \
            firstTime = false; \
            printf( CHECK_STRING_FORMAT format "\n", gettid(), __FILE__, __PRETTY_FUNCTION__,  __LINE__, ##__VA_ARGS__); \
            fflush( stdout); \
        } \
    } while (0)

#define TRACE_ON_CHANGE( format, ...) \
    do { \
        static std::string lastTime;  \
        size_t size = std::snprintf( NULL, 0, format, ##__VA_ARGS__ ); \
        char buf[size + 1]; \
        snprintf( buf, sizeof( buf ), format, ##__VA_ARGS__ ); \
        std::string thisTime( buf ); \
        if (thisTime != lastTime) \
        { \
            lastTime = thisTime; \
            printf( CHANGE_STRING_FORMAT " %s\n", gettid(), __FILE__, __PRETTY_FUNCTION__,  __LINE__, thisTime.c_str() ); \
            fflush( stdout); \
        } \
    } while (0)

#elif defined(__GNUC__) && defined( TRACE_ON)
// GNU C

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>

#define DETAIL_STRING_FORMAT "(%ld)%s::%s:%d "
#define START_STRING_FORMAT "Starting " DETAIL_STRING_FORMAT
#define END_STRING_FORMAT "Ending " DETAIL_STRING_FORMAT
#define CHECK_STRING_FORMAT "Check " DETAIL_STRING_FORMAT
#define CHANGE_STRING_FORMAT "Change " DETAIL_STRING_FORMAT

#define TRACE_START( format, ...) \
    do { \
        printf( START_STRING_FORMAT format "\n", syscall(SYS_gettid), __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
        fflush( stdout); \
    } while (0)

#define TRACE_END( format, ...) \
    do { \
        printf( END_STRING_FORMAT format "\n", syscall(SYS_gettid), __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
        fflush( stdout); \
    } while (0)

#define TRACE_CHECK( format, ...) \
    do { \
        printf( CHECK_STRING_FORMAT format "\n", syscall(SYS_gettid), __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
        fflush( stdout); \
    } while (0)

#define TRACE_SINGLE_CHECK( format, ...) \
    do { \
        static bool firstTime = true; \
        if (firstTime) \
        { \
            firstTime = false; \
            printf( CHECK_STRING_FORMAT format "\n", syscall(SYS_gettid), __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
            fflush( stdout); \
        } \
    } while (0)

#define TRACE_ON_CHANGE_MAX_SIZE 255

#define TRACE_ON_CHANGE( format, ...) \
    do { \
        static char lastTime[TRACE_ON_CHANGE_MAX_SIZE]; \
        char thisTime[TRACE_ON_CHANGE_MAX_SIZE]; \
        snprintf( thisTime, sizeof(thisTime), format, ##__VA_ARGS__ ); \
        if ( strcmp( lastTime, thisTime ) != 0 ) { \
            strcpy( lastTime, thisTime ); \
            printf( CHANGE_STRING_FORMAT "%s \n", syscall(SYS_gettid), __FILE__, __func__, __LINE__, thisTime ); \
            fflush( stdout); \
        } \
    } while (0)

#else

// unsupported or disabled
#define TRACE_START( format, ... )
#define TRACE_END( format, ... )
#define TRACE_CHECK( format, ... )
#define TRACE_SINGLE_CHECK( format, ... )
#define TRACE_ON_CHANGE( format, ... )

#endif

#endif  // TRACE_H_

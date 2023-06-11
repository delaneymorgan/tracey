/*
 * @file trace.h
 *
 * @brief A simple trace macro which can be controlled by individual modules,
 * or if brave, the entire program.
 *
 * (c) Delaney & Morgan Computing
 * <admin@delaneymorgan.com.au>
 *
 * Anyone is free to copy this software as is, or modified as long as
 * this attribution remains. i.e. no complicated licences, no lawyers,
 * and no restrictions. Just use it, enjoy it, and relax.
 * We won't hassle you about it if you don't hassle us.
 * 
 * To use:
 * 
 *     In client module:
 *         #define TRACE_ON
 *         #include "include/trace.h"
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

/**
 * NOTE: In Visual Studio these macros will trigger the following warning:
 *
 *     C4003: not enough arguments for function-like macro invocation
 *
 * Unfortunately this is a standards issue with the VS pre-processor.  Runs as expected though.
 *
 * VS has an "/experimental:preprocessor" option which should fix this, otherwise just disable the C4003 warning.
 * Or just ignore the warnings - you wouldn't leave trace on in a production build anyway.
 *
 */

#ifndef TRACE_H_
#define TRACE_H_


#include "macros.h"

#if defined( _WIN32) && defined(__cplusplus) && defined( TRACE_ON)
// VS C++

#include <processthreadsapi.h>

#define DETAIL_STRING_FORMAT "(%lu)%s::%s:%d "
#define START_STRING_FORMAT "Starting " DETAIL_STRING_FORMAT
#define END_STRING_FORMAT "Ending " DETAIL_STRING_FORMAT
#define CHECK_STRING_FORMAT "Check " DETAIL_STRING_FORMAT
#define CHANGE_STRING_FORMAT "Change " DETAIL_STRING_FORMAT

#if defined(TRACE_LONG_FILENAMES)
    #define TRACE_FILENAME __FILE__
#else // defined(TRACE_LONG_FILENAMES)
    #define TRACE_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif // defined(TRACE_LONG_FILENAMES)

#if defined(TRACE_LONG_METHOD_SIGNATURES)
    #define TRACE_METHOD __PRETTY_FUNCTION__
#else // defined(TRACE_LONG_METHOD_SIGNATURES)
    #define TRACE_METHOD TRACE_ShortMethodName(__PRETTY_FUNCTION__).c_str()
#endif // defined(TRACE_LONG_METHOD_SIGNATURES)

#define TRACE_START( format, ... ) \
    do { \
        printf( START_STRING_FORMAT format "\n", GetCurrentThreadId(), TRACE_FILENAME, TRACE_METHOD,  __LINE__, ##__VA_ARGS__ ); \
        fflush( stdout); \
    } while (0)

#define TRACE_END( format, ... ) \
    do { \
        printf( END_STRING_FORMAT format "\n", GetCurrentThreadId(), TRACE_FILENAME, TRACE_METHOD,  __LINE__, ##__VA_ARGS__ ); \
        fflush( stdout); \
    } while (0)

#define TRACE_CHECK( format, ... ) \
    do { \
        printf( CHECK_STRING_FORMAT format "\n", GetCurrentThreadId(), TRACE_FILENAME, TRACE_METHOD,  __LINE__, ##__VA_ARGS__ ); \
        fflush( stdout); \
    } while (0)

#define TRACE_SINGLE_CHECK( format, ...) \
    do { \
        static bool firstTime = true; \
        if (firstTime) \
        { \
            firstTime = false; \
            printf( CHECK_STRING_FORMAT format "\n", GetCurrentThreadId(), TRACE_FILENAME, TRACE_METHOD,  __LINE__, ##__VA_ARGS__ ); \
            fflush( stdout); \
        } \
    } while (0)

#define TRACE_ON_CHANGE( format, ...) \
    do { \
        static std::string lastTime;  \
        size_t size = std::snprintf( NULL, 0, format, ##__VA_ARGS__ ); \
        std::unique_ptr<char> buf(new char[size]); \
        std::snprintf(buf.get(), size, "param: %s", param.c_str()); \
        std::string thisTime(buf.get()); \
        if (thisTime != lastTime) \
        { \
            lastTime = thisTime; \
            printf( CHANGE_STRING_FORMAT " %s\n", GetCurrentThreadId(), TRACE_FILENAME, TRACE_METHOD,  __LINE__, thisTime.c_str() ); \
            fflush( stdout); \
        } \
    } while (0)

#elif defined( _WIN32) && !defined(__cplusplus) && defined( TRACE_ON)
// VS C

#include <processthreadsapi.h>

#define DETAIL_STRING_FORMAT "(%lu)%s::%s:%d "
#define START_STRING_FORMAT "Starting " DETAIL_STRING_FORMAT
#define END_STRING_FORMAT "Ending " DETAIL_STRING_FORMAT
#define CHECK_STRING_FORMAT "Check " DETAIL_STRING_FORMAT
#define CHANGE_STRING_FORMAT "Change " DETAIL_STRING_FORMAT

#if defined(TRACE_LONG_FILENAMES)
    #define TRACE_FILENAME __FILE__
#else // defined(TRACE_LONG_FILENAMES)
    #define TRACE_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif // defined(TRACE_LONG_FILENAMES)

#define TRACE_START( format, ... ) \
    do { \
        printf( START_STRING_FORMAT format "\n", GetCurrentThreadId(), TRACE_FILENAME, __func__,  __LINE__, ##__VA_ARGS__ ); \
        fflush( stdout); \
    } while (0)

#define TRACE_END( format, ... ) \
    do { \
        printf( END_STRING_FORMAT format "\n", GetCurrentThreadId(), TRACE_FILENAME, __func__,  __LINE__, ##__VA_ARGS__ ); \
        fflush( stdout); \
    } while (0)

#define TRACE_CHECK( format, ... ) \
    do { \
        printf( CHECK_STRING_FORMAT format "\n", GetCurrentThreadId(), TRACE_FILENAME, __func__,  __LINE__, ##__VA_ARGS__ ); \
        fflush( stdout); \
    } while (0)

#define TRACE_SINGLE_CHECK(format, ...) \
    do { \
        static int firstTime = 1; \
        if (firstTime) \
        { \
            firstTime = 0; \
            printf( CHECK_STRING_FORMAT format "\n", GetCurrentThreadId(), TRACE_FILENAME, __func__, __LINE__, ##__VA_ARGS__); \
            fflush( stdout); \
        } \
    } while (0)

#define TRACE_ON_CHANGE_MAX_SIZE 255

#define TRACE_ON_CHANGE(format, ...) \
    do { \
        static char lastTime[TRACE_ON_CHANGE_MAX_SIZE]; \
        char thisTime[TRACE_ON_CHANGE_MAX_SIZE]; \
        snprintf( thisTime, sizeof(thisTime), format, ##__VA_ARGS__ ); \
        if ( strcmp( lastTime, thisTime ) != 0 ) { \
            strcpy( lastTime, thisTime ); \
            printf( CHANGE_STRING_FORMAT "%s \n", GetCurrentThreadId(), TRACE_FILENAME, __func__, __LINE__, thisTime ); \
            fflush( stdout); \
        } \
    } while (0)

#elif defined(__GNUG__) && defined( TRACE_ON)
// GNU C++

#include <cstdio>
#include <cstring>
#include <unistd.h>

#define DETAIL_STRING_FORMAT "(%u)%s::%s:%d "
#define START_STRING_FORMAT "Starting " DETAIL_STRING_FORMAT
#define END_STRING_FORMAT "Ending " DETAIL_STRING_FORMAT
#define CHECK_STRING_FORMAT "Check " DETAIL_STRING_FORMAT
#define CHANGE_STRING_FORMAT "Change " DETAIL_STRING_FORMAT

std::string TRACE_ShortMethodName(const char* fullName);

#if defined(TRACE_LONG_FILENAMES)
    #define TRACE_FILENAME __FILE__
#else // defined(TRACE_LONG_FILENAMES)
    #define TRACE_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif // defined(TRACE_LONG_FILENAMES)

#if defined(TRACE_LONG_METHOD_SIGNATURES)
    #define TRACE_METHOD __PRETTY_FUNCTION__
#else // defined(TRACE_LONG_METHOD_SIGNATURES)
    #define TRACE_METHOD TRACE_ShortMethodName(__PRETTY_FUNCTION__).c_str()
#endif // defined(TRACE_LONG_METHOD_SIGNATURES)

#define TRACE_START(format, ...) \
    do { \
        printf( START_STRING_FORMAT format "\n", gettid(), TRACE_FILENAME, TRACE_METHOD,  __LINE__, ##__VA_ARGS__); \
        fflush( stdout); \
    } while (0)

#define TRACE_END(format, ...) \
    do { \
        printf( END_STRING_FORMAT format "\n", gettid(), TRACE_FILENAME, TRACE_METHOD,  __LINE__, ##__VA_ARGS__); \
        fflush( stdout); \
    } while (0)

#define TRACE_CHECK(format, ...) \
    do { \
        printf( CHECK_STRING_FORMAT format "\n", gettid(), TRACE_FILENAME, TRACE_METHOD,  __LINE__, ##__VA_ARGS__); \
        fflush( stdout); \
    } while (0)

#define TRACE_SINGLE_CHECK( format, ...) \
    do { \
        static bool firstTime = true; \
        if (firstTime) \
        { \
            firstTime = false; \
            printf( CHECK_STRING_FORMAT format "\n", gettid(), TRACE_FILENAME, TRACE_METHOD,  __LINE__, ##__VA_ARGS__); \
            fflush( stdout); \
        } \
    } while (0)

#define TRACE_ON_CHANGE( format, ...) \
    do { \
        static std::string lastTime;  \
        size_t size = std::snprintf( NULL, 0, format, ##__VA_ARGS__ ); \
        char buf[size + 1]; \
        std::snprintf( buf, sizeof( buf ), format, ##__VA_ARGS__ ); \
        std::string thisTime( buf ); \
        if (thisTime != lastTime) \
        { \
            lastTime = thisTime; \
            printf( CHANGE_STRING_FORMAT " %s\n", gettid(), TRACE_FILENAME, TRACE_METHOD,  __LINE__, thisTime.c_str() ); \
            fflush( stdout); \
        } \
    } while (0)

#elif defined(__GNUC__) && defined( TRACE_ON)
// GNU C

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

#define DETAIL_STRING_FORMAT "(%ld)%s::%s:%d "
#define START_STRING_FORMAT "Starting " DETAIL_STRING_FORMAT
#define END_STRING_FORMAT "Ending " DETAIL_STRING_FORMAT
#define CHECK_STRING_FORMAT "Check " DETAIL_STRING_FORMAT
#define CHANGE_STRING_FORMAT "Change " DETAIL_STRING_FORMAT

#if defined(TRACE_LONG_FILENAMES)
    #define TRACE_FILENAME __FILE__
#else // defined(TRACE_LONG_FILENAMES)
    #define TRACE_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif // defined(TRACE_LONG_FILENAMES)

#define TRACE_START(format, ...) \
    do { \
        printf( START_STRING_FORMAT format "\n", syscall(SYS_gettid), TRACE_FILENAME, __func__, __LINE__, ##__VA_ARGS__); \
        fflush( stdout); \
    } while (0)

#define TRACE_END(format, ...) \
    do { \
        printf( END_STRING_FORMAT format "\n", syscall(SYS_gettid), TRACE_FILENAME, __func__, __LINE__, ##__VA_ARGS__); \
        fflush( stdout); \
    } while (0)

#define TRACE_CHECK(format, ...) \
    do { \
        printf( CHECK_STRING_FORMAT format "\n", syscall(SYS_gettid), TRACE_FILENAME, __func__, __LINE__, ##__VA_ARGS__); \
        fflush( stdout); \
    } while (0)

#define TRACE_SINGLE_CHECK(format, ...) \
    do { \
        static bool firstTime = true; \
        if (firstTime) \
        { \
            firstTime = false; \
            printf( CHECK_STRING_FORMAT format "\n", syscall(SYS_gettid), TRACE_FILENAME, __func__, __LINE__, ##__VA_ARGS__); \
            fflush( stdout); \
        } \
    } while (0)

#define TRACE_ON_CHANGE_MAX_SIZE 255

#define TRACE_ON_CHANGE(format, ...) \
    do { \
        static char lastTime[TRACE_ON_CHANGE_MAX_SIZE]; \
        char thisTime[TRACE_ON_CHANGE_MAX_SIZE]; \
        snprintf( thisTime, sizeof(thisTime), format, ##__VA_ARGS__ ); \
        if ( strcmp( lastTime, thisTime ) != 0 ) { \
            strcpy( lastTime, thisTime ); \
            printf( CHANGE_STRING_FORMAT "%s \n", syscall(SYS_gettid), TRACE_FILENAME, __func__, __LINE__, thisTime ); \
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

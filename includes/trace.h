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

#ifndef _TRACE_H_
#define _TRACE_H_


#include "macros.h"

#if defined( TRACE_ON)

#define START_STRING_FORMAT "Starting (%lu)%s::%s:%d "
#define END_STRING_FORMAT "Ending (%lu)%s::%s:%d "

#if defined( _WIN32)
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
 * 
 */
#define TRACE_START( format, ... ) \
    do { \
        printf( START_STRING_FORMAT format "\n", GetCurrentThreadId(), __FILE__, __PRETTY_FUNCTION__,  __LINE__, ##__VA_ARGS__ ); \
    } while (0)

#define TRACE_END( format, ... ) \
    do { \
        printf( END_STRING_FORMAT format "\n", GetCurrentThreadId(), __FILE__, __PRETTY_FUNCTION__,  __LINE__, ##__VA_ARGS__ ); \
    } while (0)

#elif defined(__GNUG__)
// GNU C++

#include <cstdio>
#include <pthread.h>

#define TRACE_START(format, ...) \
    do { \
        printf( START_STRING_FORMAT format "\n", pthread_self(), __FILE__, __PRETTY_FUNCTION__,  __LINE__, ##__VA_ARGS__); \
    } while (0)

#define TRACE_END(format, ...) \
    do { \
        printf( END_STRING_FORMAT format "\n", pthread_self(), __FILE__, __PRETTY_FUNCTION__,  __LINE__, ##__VA_ARGS__); \
    } while (0)

#elif defined(__GNUC__)
// GNU C

#include <stdio.h>
#include <pthread.h>

#define TRACE_START( format, ...) \
    do { \
        printf( START_STRING_FORMAT format "\n", pthread_self(), __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
    } while (0)

#define TRACE_END( format, ...) \
    do { \
        printf( END_STRING_FORMAT format "\n", pthread_self(), __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
    } while (0)

#else
#define TRACE_START( format, ... )
#define TRACE_END( format, ... )
#endif
#else
#define TRACE_START( format, ... )
#define TRACE_END( format, ... )
#endif

#endif  // _TRACE_H_

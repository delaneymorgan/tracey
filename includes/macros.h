/**
 * @file macros.h
 *
 * @brief A collection of useful macros
 *
 */

#ifndef _MACROS_H_
#define _MACROS_H_


// returns a string of the identifer
#define QUOTE(x) #x


/**
 * close the gap between gcc and Microsoft
 */
#if defined(_WIN32)

#if !defined(__PRETTY_FUNCTION__) && !defined(__GNUC__)
    #define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

#endif  // defined(_WIN32)


#endif  // _MACROS_H_

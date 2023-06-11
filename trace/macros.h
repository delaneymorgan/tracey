/**
 * @file macros.h
 *
 * @brief A collection of useful macros
 *
 */

#ifndef MACROS_H_
#define MACROS_H_


// returns a string of the identifer
#define QUOTE(x) #x

#if !defined(max)
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
#endif  // !defined(max)

#if !defined(min)
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
#endif // !defined(min)


/**
 * close the gap between gcc and Microsoft
 */
#if defined(_WIN32)

#if !defined(__PRETTY_FUNCTION__) && !defined(__GNUC__)
    #define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

#endif  // defined(_WIN32)


#endif  // MACROS_H_

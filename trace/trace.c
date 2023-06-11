/*
 * @file trace.c
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
 */


#include "macros.h"

#include <string.h>

char* shortMethodName( const char* const fullName, char* const shortName, const size_t shortNameSize) {
    memset(shortName, '\0', shortNameSize);
    strncpy( shortName, fullName, min(strlen(fullName), shortNameSize));
    char* openBracket = strchr( shortName, '(');
    *openBracket = '\0';
    char* methodStart = strrchr( shortName, ' ');
    memcpy(shortName, methodStart, openBracket-methodStart);
    strcat(shortName, "()");
    return shortName;
}
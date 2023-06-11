/*
 * @file trace.cpp
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

#include <string>

std::string TRACE_ShortMethodName(const char* fullName) {
    std::string shortName = fullName;
    size_t openBracket = shortName.find('(');
    shortName = shortName.substr(0, openBracket);
    size_t methodStart = shortName.find_last_of(' ');
    shortName = shortName.substr(methodStart + 1);
    shortName += "()";
    return shortName;
}
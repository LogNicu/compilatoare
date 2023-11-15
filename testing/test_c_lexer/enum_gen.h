#ifndef ENUM_GEN_H
#define ENUM_GEN_H

#include <stdio.h>

#include "foreach.h"

#define STRINGIFY(X)    #X,
#define STRINGIFY_VA(...) FOREACH(STRINGIFY, (__VA_ARGS__))
#define DEFINE_ENUM(ENUM_NAME , ...)        \
    typedef enum { \
        __VA_ARGS__ \
    }ENUM_NAME; \
    const char* ENUM_NAME##ToStr(ENUM_NAME type) { \
        static const char* enum_str[] = {STRINGIFY_VA(__VA_ARGS__)}; \
        return enum_str[type]; \
    } 

#endif

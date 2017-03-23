//---------------------------------------
//! @file Utils.h
//! Extra utilities
//---------------------------------------

#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#include <cassert>
#include <iostream>

#define ERROR_LOG

#define ERROR_STREAM std::cerr
#define LOG_STREAM std::cout

#ifdef FULL_LOG

#define INFO( object )          \
if(!(object).ok())              \
{                               \
    (object).dump(ERROR_STREAM);\
    assert(!"Object is OK");    \
}                               \
else                            \
{                               \
    (object).dump(LOG_STREAM);  \
}

#else
#ifdef ERROR_LOG

#define INFO( object )          \
if(!(object).ok())              \
{                               \
    (object).dump(ERROR_STREAM);\
    assert(!"Object is ok");    \
}

#else
#define INFO( object )
#endif
#endif

#define LOG(x)
//LOG_STREAM<<( x )<<std::endl

namespace utils
{

    constexpr int access[8] = {0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b10000000};

//---------------------------------------
//! @brief Forms a specific padding
//! @param symbol A character to repeat
//! @param amount Amount of repeats
//! @return The formed padding string
//---------------------------------------

    char* getPadding(char symbol, int amount);
}

#endif //VECTOR_UTILS_H

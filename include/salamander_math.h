/**
 * salamander_math.h
 * 
 * See the 'LICENSE' file for this file's license.
 *
 * @authors:
 *   1. SD Asif Hossein <s.dah.ingularity@gmail.com> 13th Dec. 2022
 */

#ifndef __SALAMANDER_MATH_H__
#define __SALAMANDER_MATH_H__

#include <salamander_core.h>

// Union to bit cast from double to unsigned 64-bit integer.

typedef union union_DoubleBits {
    uint64_t bits64;
    double num;
} BitCast;

// Converts a double value to unsigned 64-bit integer by bits.

static inline uint64_t salamander_Math_double_to_bits(double num) {
    BitCast cast;

    cast.num = num;

    return cast.bits64;
}

// Converts a 64-bit integer to double value by bits.

static inline double salamander_Math_double_from_bits(uint64_t bits) {
    BitCast cast;

    cast.bits64 = bits;

    return cast.num;
}

#endif    // __SALAMANDER_MATH_H__
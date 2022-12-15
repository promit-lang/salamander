/**
 * libutil.h
 * 
 * See the 'LICENSE' file for this file's license.
 * 
 * SalamanderVM does not have any core library predefined. So, it's a 
 * requirement that the compiler/language targetting SVM, should define the 
 * whole core library (e.g. Wrapper Classes for primitive data types and 
 * other functions, classes etc.) by themselves. It's a flexibility provided 
 * by the SVM and also a pain in the as* at the same time. So, this header 
 * file has useful macros and function which will make writing the whole
 * library for SVM much easier.
 *
 * @authors:
 *   1. SD Asif Hossein <s.dah.ingularity@gmail.com> 15th Dec. 2022
 */

#ifndef __SALAMANDER_LIBUTIL_H__
#define __SALAMANDER_LIBUTIL_H__

#include <salamander_value.h>

// Why these operator functions? Well in SVM, you are allowed to do operator 
// overloading. Plus, it also those utility functions also handle operations
// like adding number to a string and stuffs like that.

// Binary operators.
// 
// Note: Maintain order.

SALAMANDER_API Value salamander_Value_add(SalamanderVM*, Value*, Value*);

// Unary operators.

SALAMANDER_API Value salamander_Value_negate(SalamanderVM*, Value*);

// Converts any type of value representation to number.
// TODO: Add more specification.

SALAMANDER_API Value salamander_Value_convert_to_num(SalamanderVM*, Value*);

// In SVM, a valid number is a number which is neither INFINITY nor NAN.
// This function checks whether the provided number is valid.

SALAMANDER_API bool salamander_Value_is_valid_num(double);

#endif    // __SALAMANDER_LIBUTIL_H__
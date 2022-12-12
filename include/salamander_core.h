/**
 * core.h
 * 
 * See the 'LICENSE' file for this file's license.
 *
 * This file will be included in almost all the translations of this project
 * through other header files or directly. As the name suggests, this file
 * consist all the macros which defines the very behaviour of SalamanderVM
 * and various header files we are gonna use almost everywhere in the VM.
 *
 * @authors:
 *   1. SD Asif Hossein <s.dah.ingularity@gmail.com> 27th Nov. 2022
 */

#ifndef __SALAMANDER_CORE_H__
#define __SALAMANDER_CORE_H__

// C++ compilers does not allow C++ programs to use C99 standard specific
// macros defined in 'stdint.h' despite having included in the program. So,
// in a C++ environment, we cannot access macros like uint64_t, UINT8_MAX etc.
// unless __STDC_LIMIT_MACROS and __STDC_CONSTANT_MACROS macros are defined
// before including 'stdint.h'.

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS
#include <stdint.h>

// To have access to Boolean related macros such as true, false and bool
// which is respectively defined as 1, 0 and _Bool.

#include <stdbool.h>

// To use macros like 'ptrdiff_t', 'size_t' and 'NULL'.

#include <stddef.h>

/**
 * Flags defined after this will control the behaviour of the interpreter
 * implementation.

 * They are generally trade-offs between speed and portability. Defaults to the
 * most efficient implementation possible depending on the computer and
 * compiler features.
 */

// If true, SalamanderVM uses a feature called 'NaN Tagging' as it's core value
// representation, otherwise conventional struct. NaN Tagging will allow SVM to
// consume less space and perform significantly faster.

#ifndef SALAMANDER_NAN_TAGGING
#define SALAMANDER_NAN_TAGGING 1
#endif    // SALAMANDER_NAN_TAGGING

// SVM uses a GCC extension called computed goto's for faster loop dispatching.
// Enable this feature if you are compiling SVM with GCC compiler.
// See more about this at:
//     http://gcc.gnu.org/onlinedocs/gcc-3.1.1/gcc/Labels-as-Values.html

#ifndef SALAMANDER_COMPUTED_GOTO

#ifdef __GNUC__
#define SALAMANDER_COMPUTED_GOTO 1
#else
#define SALAMANDER_COMPUTED_GOTO 0
#endif    // __GNUC__

#endif    // SALAMANDER_COMPUTED_GOTO

// __builtin_expect(n, e) is an extension to both GCC and clang compiler used
// for branch predictions which optimizes the condition pipeline, thus makes
// the condition related statements run faster.

#if defined __GNUC__ || defined __clang__

#define is_true(x) __builtin_expect(!!(x), 1)
#define is_false(x) __builtin_expect(!!(x), 0)

#else

#define is_true(x) x
#define is_false(x) !x

#endif    // __GNUC__ and __clang__

// The macros defined below is used throughout the implementation of SVM.
// If any of it triggers, that means we have bugs in our nice VM. Catching 
// and dumping errors creates a significant overhead. So, do it only in DEBUG
// mode.

#ifdef SALAMANDER_DEBUG

#include <stdio.h>

// Assertion is used to validate expected values in runtime. If the VM expects 
// some condition to be true at a point of execution and it turns out false, 
// VM will throw an assertion error.

#define ASSERT(condition, message)                                           \
	if(is_false(condition)) {                                                \
		(void) fprintf(stderr,                                               \
			"[%s:%d] Debug assertion failed in %s() : %s",                   \
			__FILE__, __LINE__, __func__, message);                          \
		abort();                                                             \
	}

// Indicates the program execution shouldn't reach the portion of code. If it
// does, dump error in DEBUG mode.

// In release mode, use compiler specific built-in functions to indicate 
// uncreachable codes. It tells the compilers a portion of code should never
// be reached. This gets rid of the 'expected a return' warnings.

#define UNREACHABLE()                                                        \
	fprintf(stderr,                                                          \
		"[%s:%d] This portion of code should not be reached in %s()!",       \
		__FILE__, __LINE__, __func__);                                       \
	abort();

#else 

#define ASSERT(condition, message) 

// '__assume' in MSVC compiler indicates unreachable code to optimizer where
// '__builtin_unreachable' is used for GCC compilers of version 4.5 or higher.

#if defined _MSC_VER

#define UNREACHABLE() __assume(0)

#elif (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5))

#define UNREACHABLE() __builtin_unreachable()

#else 

#define UNREACHABLE() 

#endif    // _MSC_VER and __GNUC__

#endif    // SALAMANDER_DEBUG

#endif    // __SALAMANDER_CORE_H__
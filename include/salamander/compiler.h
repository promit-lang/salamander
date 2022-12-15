/**
 * compiler.h
 * 
 * See the 'LICENSE' file for this file's license.
 *
 * This file contains necessary functions to help emit bytecode with required 
 * opearnds of that bytecode, making writing a compiler for SVM easier. This 
 * file provides the compiler backends.
 * 
 * Note: This file will not be included in this project.
 *
 * @authors:
 *   1. SD Asif Hossein <s.dah.ingularity@gmail.com> 12th Dec. 2022
 */

#ifndef __SALAMANDER_COMPILER_H__
#define __SALAMANDER_COMPILER_H__

#include <salamander_value.h>

SALAMANDER_API void salamander_Compiler_emit_CONSTANT(SalamanderVM*, ObjFn*, Value, int);
SALAMANDER_API void salamander_Compiler_emit_ADD(SalamanderVM*, ObjFn*, int);
SALAMANDER_API void salamander_Compiler_emit_NEGATE(SalamanderVM*, ObjFn*, int);
SALAMANDER_API void salamander_Compiler_emit_RETURN(SalamanderVM*, ObjFn*, int);
SALAMANDER_API void salamander_Compiler_emit_END(SalamanderVM*, ObjFn*, int);

#endif    // __SALAMANDER_COMPILER_H__
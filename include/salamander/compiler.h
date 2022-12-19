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

#include <salamander/api.h>
#include <salamander/object.h>

// Literal types used while emitting a constant instruction.

typedef enum enum_LiteralType {
	LITERAL_NUM
} LiteralType;

// Emits the instruction 'CONSTANT', which loads a constant to the fiber 
// stack from constant pool. In [void*] parameter pass: 
// For number types (double): &number
// For strings: Just the pointer to the first character.

SALAMANDER_API void salamander_Compiler_emit_CONSTANT(SalamanderVM*, ObjFn*, 
	LiteralType, void*, int);

// Emits the 'BINARY' instruction passing provided binary operation type as 
// operand. The 'BINARY' instruction makes binary operation with two values
// on top of the stack.

// SALAMANDER_API void 
// 	salamander_Compiler_emit_BINARY(SalamanderVM*, ObjFn*, BinaryOpType, int);

// Emits the instruction 'BINARY' with parameter 'BINARY_ADD', which adds two 
// values. If the values are string, then they will be concatenated. In case 
// of other type of values, addition will be performed accordingly.
// 
// This function is a helper function to 'salamander_Compiler_emit_BINARY()'.

SALAMANDER_API void salamander_Compiler_emit_ADD(SalamanderVM*, ObjFn*, int);

// The SalamanderVM does not have any 'SUBSTRACT' instruction. It does it's 
// substraction operation simply by negating the right hand side value and 
// then doing a addition operation. Upon calling this function the compiler 
// will emit the instructions 'NEGATE' and 'BINARY(ADD)' respectively.

/** These function are called hybrid functions emitting more than one 
    instructions, which would be equivalent to one instruciton. These function
	have a 'H_' prefix in their instruction name. */

SALAMANDER_API void 
	salamander_Compiler_emit_H_SUBSTRACT(SalamanderVM*, ObjFn*, int);

// Emits the instruction 'BINARY' with parameter 'BINARY_MUL', which 
// multiplies the left-hand side argument (or the first value pushed in the 
// stack following polish notation) with the right-side argument. In case of
// value types other than number, multiplication will be performed accordingly.
// 
// This function is a helper function to 'salamander_Compiler_emit_BINARY()'.

SALAMANDER_API void 
	salamander_Compiler_emit_MULTIPLY(SalamanderVM*, ObjFn*, int);

// Emits the instruction 'BINARY' with parameter 'BINARY_DIV', which 
// divides the left-hand side argument by the right-side argument. In case of
// value types other than number, division will be performed accordingly.
// 
// This function is a helper function to 'salamander_Compiler_emit_BINARY()'.

SALAMANDER_API void 
	salamander_Compiler_emit_DIVIDE(SalamanderVM*, ObjFn*, int);

// Emits the instruction 'NEGATE', which negates the value at the top
// of the stack, if the value number or convertible to number.

SALAMANDER_API void 
	salamander_Compiler_emit_NEGATE(SalamanderVM*, ObjFn*, int);

// Emits the instruction 'RETURN', which returns a value and terminates
// function/fiber execution.

SALAMANDER_API void 
	salamander_Compiler_emit_RETURN(SalamanderVM*, ObjFn*, int);

// Emits the instruction 'END', which practically breaks the VM. This code 
// should always come after 'RETURN' instruction. The 'RETURN' instruction
// completes the code execution and exits out of function/fiber. Stick with
// this instruction to indicate wrong code generation.

SALAMANDER_API void salamander_Compiler_emit_END(SalamanderVM*, ObjFn*, int);

#endif    // __SALAMANDER_COMPILER_H__
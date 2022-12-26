/**
 * compiler.h
 * 
 * See the 'LICENSE' file for this file's license.
 *
 * Sometimes making a compiler targetting a VM can be a hassle. You have to 
 * manage the emission of bytecode and their operands all by yourself. Well, 
 * SalamanderVM tries to make it a little bit tolerable for the compiler 
 * designers, by providing a proper kit to design the compiler with functions 
 * to emit bytecodes with their respective operands.
 * 
 * Note: This file will not be included in this project.
 *
 * @authors:
 *   1. SD Asif Hossein <s.dah.ingularity@gmail.com> 12th Dec. 2022
 */

#ifndef __SALAMANDER_COMPILER_H__
#define __SALAMANDER_COMPILER_H__

#include <salamander/salamander.h>

// Forward declaration of CompilerKit struct.
// 
// What the heck is that thing? Well, SalamanderVM is designed in such way 
// that it abstracts all it's internal core objects. But, in order to write a 
// compiler for SVM, you are gonna need those objects. This is where the kit 
// comes into play. It holds all the necessary objects to write a compiler, 
// but abstracts the core functions and symbols to manupulate the object.
// 
// CompilerKit: 
//     ObjFn* fn;           -> The function you are going to emit your 
//                             bytecode to.
//     ObjFiber* fiber;     -> The fiber holding the [fn] as the first frame.
//     ObjModule* module;   -> Current module used to create [fn] and [fiber].

typedef struct struct_CompilerKit CompilerKit;

// Literal types used while emitting a constant instruction.

typedef enum enum_LiteralType {
	CONSTANT_NUM
} LiteralType;

// Creates a CompilerKit in the heap and returns it.
// 
// Note: Uses the configs reallocator function for heap creation.

SALAMANDER_API CompilerKit* salamander_CompilerKit_new(SalamanderVM*);

// Creates a new function object (ObjFn) in CompilerKit.

SALAMANDER_API void salamander_CompilerKit_new_fn(SalamanderVM*, CompilerKit*);

// Frees the CompilerKit, as it's manually created in the heap.

SALAMANDER_API void salamander_CompilerKit_free(SalamanderVM*, CompilerKit*);

// Emits the instruction 'CONSTANT', which loads a constant to the fiber 
// stack from constant pool. In [void*] parameter pass: 
// For number types (double): &number
// For strings:               Just the pointer to the first character.
// For functions and fibers:  Pointer to the CompilerKit.

SALAMANDER_API void salamander_CompilerKit_emit_CONSTANT(SalamanderVM*, 
    CompilerKit*, LiteralType, void*, int);

// Emits the 'BINARY' instruction passing provided binary operation type as 
// operand. The 'BINARY' instruction makes binary operation with two values
// on top of the stack.

// SALAMANDER_API void 
// 	salamander_Compiler_emit_BINARY(SalamanderVM*, CompilerKit*, BinaryOpType, int);

// Emits the instruction 'BINARY' with parameter 'BINARY_ADD', which adds two 
// values. If the values are string, then they will be concatenated. In case 
// of other type of values, addition will be performed accordingly.
// 
// This function is a helper function to 'salamander_Compiler_emit_BINARY()'.

SALAMANDER_API void salamander_CompilerKit_emit_ADD(SalamanderVM*, 
    CompilerKit*, int);

// The SalamanderVM does not have any 'SUBSTRACT' instruction. It does it's 
// substraction operation simply by negating the right hand side value and 
// then doing a addition operation. Upon calling this function the compiler 
// will emit the instructions 'NEGATE' and 'BINARY(ADD)' respectively.

/** These function are called hybrid functions emitting more than one 
    instructions, which would be equivalent to one instruciton. These function
	have a 'H_' prefix in their instruction name. */

SALAMANDER_API void 
	salamander_CompilerKit_emit_H_SUBSTRACT(SalamanderVM*, CompilerKit*, int);

// Emits the instruction 'BINARY' with parameter 'BINARY_MUL', which 
// multiplies the left-hand side argument (or the first value pushed in the 
// stack following polish notation) with the right-side argument. In case of
// value types other than number, multiplication will be performed accordingly.
// 
// This function is a helper function to 'salamander_Compiler_emit_BINARY()'.

SALAMANDER_API void 
	salamander_CompilerKit_emit_MULTIPLY(SalamanderVM*, CompilerKit*, int);

// Emits the instruction 'BINARY' with parameter 'BINARY_DIV', which 
// divides the left-hand side argument by the right-side argument. In case of
// value types other than number, division will be performed accordingly.
// 
// This function is a helper function to 'salamander_Compiler_emit_BINARY()'.

SALAMANDER_API void 
	salamander_CompilerKit_emit_DIVIDE(SalamanderVM*, CompilerKit*, int);

// Emits the instruction 'NEGATE', which negates the value at the top
// of the stack, if the value number or convertible to number.

SALAMANDER_API void 
	salamander_CompilerKit_emit_NEGATE(SalamanderVM*, CompilerKit*, int);

// Emits the instruction 'RETURN', which returns a value and terminates
// function/fiber execution.

SALAMANDER_API void 
	salamander_CompilerKit_emit_RETURN(SalamanderVM*, CompilerKit*, int);

// Emits the instruction 'END', which practically breaks the VM. This code 
// should always come after 'RETURN' instruction. The 'RETURN' instruction
// completes the code execution and exits out of function/fiber. Stick with
// this instruction to indicate wrong code generation.

SALAMANDER_API void salamander_CompilerKit_emit_END(SalamanderVM*, 
    CompilerKit*, int);

#endif    // __SALAMANDER_COMPILER_H__
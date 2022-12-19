/** Implements API functions declared in 'salamander/compiler.h'. */

#include <salamander/compiler.h>
#include <salamander_vm.h>

// Converts provided data as void pointer to SalamanderVM's representative
// 'Value'.

static Value to_value(LiteralType type, void* value) {
    switch(type) {
        case LITERAL_NUM: return NUMBER_VAL(*((double*) value)); break;
    }

    UNREACHABLE();
}

// void salamander_Compiler_emit_CONSTANT(SalamanderVM*, ObjFn*, Value, int);
//
// Emits the instruction 'CONSTANT', which loads a constant to the fiber 
// stack from constant pool.

void salamander_Compiler_emit_CONSTANT(SalamanderVM* vm, ObjFn* fn, 
    LiteralType type, void* value, int line) 
{
    int constant_index = 
        salamander_ObjFn_write_constant(vm, fn, to_value(type, value));

    // Emit the instruction.

    salamander_ObjFn_write_byte(vm, fn, (uint8_t) CODE_CONSTANT, line);

    // Emit the constant index as short.

    salamander_ObjFn_write_short(vm, fn, (uint16_t) constant_index, line);
}

// void 
// 	salamander_Compiler_emit_BINARY(SalamanderVM*, ObjFn*, BinaryOpType, int);
// 
// Emits the 'BINARY' instruction passing provided binary operation type as 
// operand. The 'BINARY' instruction makes binary operation with two values
// on top of the stack.

void salamander_Compiler_emit_BINARY(SalamanderVM* vm, ObjFn* fn, 
    BinaryOpType type, int line) 
{
    salamander_ObjFn_write_byte(vm, fn, (uint8_t) CODE_BINARY, line);
    salamander_ObjFn_write_byte(vm, fn, (uint8_t) type, line);
}

// void salamander_Compiler_emit_ADD(SalamanderVM*, ObjFn*, int);
// 
// Emits the instruction 'ADD', which adds two values. If the values are
// string, then they will be concatenated. In case of other type of values, 
// addition will be performed accordingly.

void salamander_Compiler_emit_ADD(SalamanderVM* vm, ObjFn* fn, int line) {
    salamander_Compiler_emit_BINARY(vm, fn, BINARY_ADD, line);
}

// void salamander_Compiler_emit_MULTIPLY(SalamanderVM*, ObjFn*, int);
// 
// Emits the instruction 'BINARY' with parameter 'BINARY_MUL', which 
// multiplies the left-hand side argument (or the first value pushed in the 
// stack following polish notation) with the right-side argument. In case of
// value types other than number, multiplication will be performed accordingly.
// 
// This function is a helper function to 'salamander_Compiler_emit_BINARY()'.

void salamander_Compiler_emit_MULTIPLY(SalamanderVM* vm, ObjFn* fn, int line) {
    salamander_Compiler_emit_BINARY(vm, fn, BINARY_MUL, line);
}

// void salamander_Compiler_emit_DIVIDE(SalamanderVM*, ObjFn*, int);
// 
// Emits the instruction 'BINARY' with parameter 'BINARY_DIV', which 
// divides the left-hand side argument by the right-side argument. In case of
// value types other than number, division will be performed accordingly.
// 
// This function is a helper function to 'salamander_Compiler_emit_BINARY()'.

void salamander_Compiler_emit_DIVIDE(SalamanderVM* vm, ObjFn* fn, int line) {
    salamander_Compiler_emit_BINARY(vm, fn, BINARY_DIV, line);
}

// void salamander_Compiler_emit_H_SUBSTRACT(SalamanderVM*, ObjFn* fn, int);
// 
// The SalamanderVM does not have any 'SUBSTRACT' instruction. It does it's 
// substraction operation simply by negating the right hand side value and 
// then doing a addition operation. Upon calling this function the compiler 
// will emit the instructions 'NEGATE' and 'ADD' respectively.

void salamander_Compiler_emit_H_SUBSTRACT(SalamanderVM* vm, ObjFn* fn, int line) {
    salamander_Compiler_emit_NEGATE(vm, fn, line);
    salamander_Compiler_emit_ADD(vm, fn, line);
}

// void salamander_Compiler_emit_NEGATE(SalamanderVM*, ObjFn*, int);
//
// Emits the instruction 'NEGATE', which negates the value at the top
// of the stack, if the value number or convertible to number.

void salamander_Compiler_emit_NEGATE(SalamanderVM* vm, ObjFn* fn, int line) {
    salamander_ObjFn_write_byte(vm, fn, (uint8_t) CODE_NEGATE, line);
}

// void salamander_Compiler_emit_RETURN(SalamanderVM*, ObjFn*, int);
// 
// Emits the instruction 'RETURN', which returns a value and terminates
// function/fiber execution.

void salamander_Compiler_emit_RETURN(SalamanderVM* vm, ObjFn* fn, int line) {
    salamander_ObjFn_write_byte(vm, fn, (uint8_t) CODE_RETURN, line);
}

// void salamander_Compiler_emit_END(SalamanderVM*, ObjFn*, int);
//
// Emits the instruction 'END', which practically breaks the VM. This code 
// should always come after 'RETURN' instruction. The 'RETURN' instruction
// completes the code execution and exits out of function/fiber. Stick with
// this instruction to indicate wrong code generation.

void salamander_Compiler_emit_END(SalamanderVM* vm, ObjFn* fn, int line) {
    salamander_ObjFn_write_byte(vm, fn, (uint8_t) CODE_END, line);
}
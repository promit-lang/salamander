/** Implements API functions declared in 'salamander/compiler.h'. */

#include <salamander/compiler.h>
#include <salamander_vm.h>

// Holds the necessary objects to write a compiler.
// 
// See the details in 'salamander/compiler.h:23'.

struct struct_CompilerKit {
    ObjFn* fn;
};

// Converts provided data as void pointer to SalamanderVM's representative
// 'Value'.

static Value to_value(LiteralType type, void* value) {
    switch(type) {
        case CONSTANT_NUM: return NUMBER_VAL(*((double*) value)); break;
    }

    UNREACHABLE();
}

// CompilerKit* salamander_CompilerKit_new(SalamanderVM*);
// 
// Creates a CompilerKit in the heap and returns it.
// 
// Note: Uses the configs reallocator function for heap creation.

CompilerKit* salamander_CompilerKit_new(SalamanderVM* vm) {
    CompilerKit* kit = (CompilerKit*) 
        vm -> config -> reallocator(NULL, sizeof(CompilerKit));
    
    kit -> fn = NULL;
    
    return kit;
}

// void salamander_CompilerKit_new_fn(SalamanderVM*, CompilerKit*);
// 
// Creates a new function object (ObjFn) in CompilerKit.

void salamander_CompilerKit_new_fn(SalamanderVM* vm, CompilerKit* kit) {
    kit -> fn = salamander_ObjFn_new(vm);
}

// void salamander_CompilerKit_free(SalamanderVM*, CompilerKit*);
// 
// Frees the CompilerKit, as it's manually created in the heap.

void salamander_CompilerKit_free(SalamanderVM* vm, CompilerKit* kit) {
    // Free the [kit] pointer.

    vm -> config -> reallocator(kit, 0u);
}

// void salamander_CompilerKit_emit_CONSTANT(SalamanderVM*, 
//     CompilerKit*, Value, int);
//
// Emits the instruction 'CONSTANT', which loads a constant to the fiber 
// stack from constant pool.

void salamander_CompilerKit_emit_CONSTANT(SalamanderVM* vm, CompilerKit* kit, 
    LiteralType type, void* value, int line) 
{
    int constant_index = 
        salamander_ObjFn_write_constant(vm, kit -> fn, to_value(type, value));

    // Emit the instruction.

    salamander_ObjFn_write_byte(vm, kit -> fn, (uint8_t) CODE_CONSTANT, line);

    // Emit the constant index as short.

    salamander_ObjFn_write_short(vm, kit -> fn, 
        (uint16_t) constant_index, line);
}

// void salamander_CompilerKit_emit_BINARY(SalamanderVM*, CompilerKit*, 
//     BinaryOpType, int);
// 
// Emits the 'BINARY' instruction passing provided binary operation type as 
// operand. The 'BINARY' instruction makes binary operation with two values
// on top of the stack.

void salamander_CompilerKit_emit_BINARY(SalamanderVM* vm, CompilerKit* kit, 
    BinaryOpType type, int line) 
{
    salamander_ObjFn_write_byte(vm, kit -> fn, (uint8_t) CODE_BINARY, line);
    salamander_ObjFn_write_byte(vm, kit -> fn, (uint8_t) type, line);
}

// void salamander_CompilerKit_emit_ADD(SalamanderVM*, CompilerKit*, int);
// 
// Emits the instruction 'ADD', which adds two values. If the values are
// string, then they will be concatenated. In case of other type of values, 
// addition will be performed accordingly.

void salamander_CompilerKit_emit_ADD(SalamanderVM* vm, CompilerKit* kit, 
    int line) 
{
    salamander_CompilerKit_emit_BINARY(vm, kit, BINARY_ADD, line);
}

// void salamander_CompilerKit_emit_MULTIPLY(SalamanderVM*, CompilerKit*, int);
// 
// Emits the instruction 'BINARY' with parameter 'BINARY_MUL', which 
// multiplies the left-hand side argument (or the first value pushed in the 
// stack following polish notation) with the right-side argument. In case of
// value types other than number, multiplication will be performed accordingly.
// 
// This function is a helper function to 'salamander_Compiler_emit_BINARY()'.

void salamander_CompilerKit_emit_MULTIPLY(SalamanderVM* vm, CompilerKit* kit, 
    int line) 
{
    salamander_CompilerKit_emit_BINARY(vm, kit, BINARY_MUL, line);
}

// void salamander_CompilerKit_emit_DIVIDE(SalamanderVM*, CompilerKit*, int);
// 
// Emits the instruction 'BINARY' with parameter 'BINARY_DIV', which 
// divides the left-hand side argument by the right-side argument. In case of
// value types other than number, division will be performed accordingly.
// 
// This function is a helper function to 'salamander_Compiler_emit_BINARY()'.

void salamander_CompilerKit_emit_DIVIDE(SalamanderVM* vm, CompilerKit* kit, 
    int line) 
{
    salamander_CompilerKit_emit_BINARY(vm, kit, BINARY_DIV, line);
}

// void salamander_CompilerKit_emit_H_SUBSTRACT(SalamanderVM*, 
//     CompilerKit*, int);
// 
// The SalamanderVM does not have any 'SUBSTRACT' instruction. It does it's 
// substraction operation simply by negating the right hand side value and 
// then doing a addition operation. Upon calling this function the compiler 
// will emit the instructions 'NEGATE' and 'ADD' respectively.

void salamander_CompilerKit_emit_H_SUBSTRACT(SalamanderVM* vm, CompilerKit* kit, int line) {
    salamander_CompilerKit_emit_NEGATE(vm, kit, line);
    salamander_CompilerKit_emit_ADD(vm, kit, line);
}

// void salamander_CompilerKit_emit_NEGATE(SalamanderVM*, CompilerKit*, int);
//
// Emits the instruction 'NEGATE', which negates the value at the top
// of the stack, if the value number or convertible to number.

void salamander_CompilerKit_emit_NEGATE(SalamanderVM* vm, CompilerKit* kit, 
    int line) 
{
    salamander_ObjFn_write_byte(vm, kit -> fn, (uint8_t) CODE_NEGATE, line);
}

// void salamander_CompilerKit_emit_RETURN(SalamanderVM*, CompilerKit*, int);
// 
// Emits the instruction 'RETURN', which returns a value and terminates
// function/fiber execution.

void salamander_CompilerKit_emit_RETURN(SalamanderVM* vm, CompilerKit* kit, 
    int line) 
{
    salamander_ObjFn_write_byte(vm, kit -> fn, (uint8_t) CODE_RETURN, line);
}

// void salamander_CompilerKit_emit_END(SalamanderVM*, CompilerKit*, int);
//
// Emits the instruction 'END', which practically breaks the VM. This code 
// should always come after 'RETURN' instruction. The 'RETURN' instruction
// completes the code execution and exits out of function/fiber. Stick with
// this instruction to indicate wrong code generation.

void salamander_CompilerKit_emit_END(SalamanderVM* vm, CompilerKit* kit, int line) {
    salamander_ObjFn_write_byte(vm, kit -> fn, (uint8_t) CODE_END, line);
}
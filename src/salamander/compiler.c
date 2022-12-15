#include <salamander/compiler.h>
#include <salamander_vm.h>

// void salamander_Compiler_emit_CONSTANT(SalamanderVM*, ObjFn*, Value, int);
//
// Emits the instruction 'CONSTANT', which loads a constant to the fiber 
// stack from constant pool.

void salamander_Compiler_emit_CONSTANT(SalamanderVM* vm, ObjFn* fn, 
	Value constant, int line) 
{
	int constant_index = salamander_ObjFn_write_constant(vm, fn, constant);

	// Emit the instruction.

	salamander_ObjFn_write_byte(vm, fn, (uint8_t) CODE_CONSTANT, line);
	
	// Emit the constant index as short.

	salamander_ObjFn_write_short(vm, fn, (uint16_t) constant_index, line);
}

// void salamander_Compiler_emit_ADD(SalamanderVM*, ObjFn*, int);
// 
// Emits the instruction 'ADD', which adds two values. If the values are
// string, then they will be concatenated. In case of other type of values, 
// addition will be performed accordingly.

void salamander_Compiler_emit_ADD(SalamanderVM* vm, ObjFn* fn, int line) {
	salamander_ObjFn_write_byte(vm, fn, (uint8_t) CODE_ADD, line);
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
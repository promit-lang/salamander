/**
 * salamander_opcode.h
 * 
 * See the 'LICENSE' file for this file's license.
 * 
 * This header file defines the bytecode instructions available in 
 * SalamanderVM. It uses a macro called 'INSTR(code, stack_effect)', which 
 * will be defined prior to including this file.
 * 
 * The first paramter to the 'INSTR' macro is the instruction code name,
 * and second one is stack effect. Stack effect means, how the instruction
 * will affect the stack, where positive number signifies the stack will
 * grow and vice versa.
 *
 * @authors:
 *   1. SD Asif Hossein <s.dah.ingularity@gmail.com> 7th Dec. 2022
 */

// Load a constnat from constant pool into the stack.

OPCODE(CONSTANT, 1)

// Pops 2 values from stack and makes a defined binary operation. Takes 
// 1 byte of data as an operand telling it which operation to do.
// 
// Note: This opcode is also responsible for bitwise operations.

OPCODE(BINARY, -1)

// Negates the top most value of the stack. If the value is not a number, it
// will be converted to a number. Calls the overloaded operator '-' if defined
// in class or wrapper class.

OPCODE(NEGATE, 0)

// Exits from the current running function and pushes the return value into 
// the stack.

OPCODE(RETURN, 0)

// Indicates the end of the bytecode. It is not supposed to be ran by the VM.
// It should always come after the the 'RETURN' instruction, which terminates
// the function execution. If the VM reaches this instruction, the compiler 
// generated wrong code.

OPCODE(END, 0)

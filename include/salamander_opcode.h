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
 * will affect the stack, where positive number signifies values will be 
 * pushed to stack and vice versa.
 *
 * @authors:
 *   1. SD Asif Hossein <s.dah.ingularity@gmail.com> 7th Dec. 2022
 */

OPCODE(CONSTANT, 1)

OPCODE(RETURN, 0)

OPCODE(END, 0)
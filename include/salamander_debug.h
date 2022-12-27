/**
 * salamander_debug.h
 * 
 * See the 'LICENSE' file for this file's license.
 *
 * As the name suggests, this header file consists of utility functions to 
 * dump values in stack, intructions and stack traces etc. which can help
 * debugging and rehacking the VM.
 *
 * @authors:
 *   1. SD Asif Hossein <s.dah.ingularity@gmail.com> 8th Dec. 2022
 */

#include <salamander_vm.h>

// Prints an instruction to the stdout and it's line number from source.

int salamander_Debug_dump_instruction(ObjFn*, int);

// Prints all the available instructions of a function/fn and it's respective 
// line number from source to stdout.

void salamander_Debug_dump_fn(ObjFn*);

// TODO: Add fiber.

void salamander_Debug_dump_stack(SalamanderVM*);
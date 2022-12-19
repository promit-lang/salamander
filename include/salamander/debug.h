/**
 * salamander_debug.h
 * 
 * See the 'LICENSE' file for this file's license.
 *
 * As the name suggests, this header file consists of utility functions to 
 * dump values in stack, intructions and stack traces etc. which can help
 * debugging and rehacking the VM.
 * 
 * Note: These functions are also exposed as API, which can help to debug
 *       compilers.
 *
 * @authors:
 *   1. SD Asif Hossein <s.dah.ingularity@gmail.com> 8th Dec. 2022
 */

#include <salamander/salamander.h>
#include <salamander/object.h>

// Prints an instruction to the stdout and it's line number from source.

SALAMANDER_API int  salamander_Debug_dump_instruction(ObjFn*, int);

// Prints all the available instructions of a function/fn and it's respective 
// line number from source to stdout.

SALAMANDER_API void salamander_Debug_dump_fn(ObjFn*);

// TODO: Add fiber.

SALAMANDER_API void salamander_Debug_dump_stack(SalamanderVM*);
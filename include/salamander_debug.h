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

void salamander_Debug_dump_value(Value);
int  salamander_Debug_dump_instruction(ObjFn*, int);
void salamander_Debug_dump_fn(ObjFn*);
void salamander_Debug_dump_stack(SalamanderVM* vm);
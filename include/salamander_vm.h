/**
 * salamander_vm.h
 * 
 * See the 'LICENSE' file for this file's license.
 *
 * @authors:
 *   1. SD Asif Hossein <s.dah.ingularity@gmail.com> 7th Dec. 2022
 */

#ifndef __SALAMANDER_VM_H__
#define __SALAMANDER_VM_H__

#include <salamander/salamander.h>
#include <salamander_value.h>

// 'Code' represents a single bytecode instruction for the VM.

#define OPCODE(code, _) CODE_##code,

typedef enum enum_Code {
#include <salamander_opcode.h>
} Code;

#undef OPCODE

struct struct_SalamanderVM {
	ObjFn* fn;
	Value stack[256];
	Value* stack_top;
};

// Weird, huh?

void             salamander_SalamanderVM_init(SalamanderVM*);
void             salamander_SalamanderVM_free(SalamanderVM*);
SalamanderResult salamander_SalamanderVM_execute(SalamanderVM*);

#endif    // __SALAMANDER_VM_H__
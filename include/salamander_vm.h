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

// 'Code' represents a single bytecode instruction for the VM.

#define INSTR(code, _) CODE_##code,

typedef enum enum_Code {
#include <salamander_instr.h>
} Code;

#undef INSTR

struct struct_SalamanderVM {

};

#endif    // __SALAMANDER_VM_H__
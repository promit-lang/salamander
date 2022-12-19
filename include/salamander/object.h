/**
 * object.h
 * 
 * See the 'LICENSE' file for this file's license.
 *
 * The SalamanderVM provides you the tools and backend to implement a compiler 
 * exposing as less internals as possible. But still, you are going to need 
 * some objects and functions to even start working with your compiler. In 
 * that case the VM exposes some necessary object symbols and some functions 
 * to work with them to the outside world and those symbols and functions will
 * be defined in this header and it's respecting C translation.
 * 
 * And for the symbols and functions of objects that you don't need to write a 
 * compiler are in the 'salamander_value.h'.
 * 
 * For example: You need the 'ObjFn' object to write your bytecodes and push 
 * your constants to. But there is some essential function you are gonna need, 
 * such as: 
 * 
 *     salamander_ObjFn_new(SalamanderVM*); -> To get a new 'ObjFn' object.
 * 
 * This function is required to write a compiler, cause if you can't even 
 * create a function, how are you supposed to emit bytecodes to. But, look at 
 * another 'ObjFn' function of 'ObjFn' as following: 
 * 
 *     salamander_ObjFn_write_byte(SalamanderVM*, ObjFn*, uint8_t, int); -> To 
 *     write a byte to the bytecode sequence.
 * 
 * The function mentioned above is not part of the API, cause functions 
 * abstracting this function have already been exposed as a part of the API.
 * 
 * Note: This header is included in 'salamander/compiler.h' file, so it is not 
 *       necessary to include this file explicitly.
 *
 * @authors:
 *   1. SD Asif Hossein <s.dah.ingularity@gmail.com> 19th Dec. 2022
 */

#ifndef __SALAMANDER_OBJECT_H__
#define __SALAMANDER_OBJECT_H__

#include <salamander/salamander.h>

// Forward declarations of object types.
// Note: These symbols only can be used as a pointer.

typedef struct struct_Obj Obj;
typedef struct struct_ObjFn ObjFn;

SALAMANDER_API ObjFn* salamander_ObjFn_new(SalamanderVM*);
SALAMANDER_API void   salamander_ObjFn_free(SalamanderVM*, ObjFn*);

#endif    // __SALAMANDER_OBJECT_H__
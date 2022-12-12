/**
 * salamander_value.h
 * 
 * See the 'LICENSE' file for this file's license.
 *
 * @authors:
 *   1. SD Asif Hossein <s.dah.ingularity@gmail.com> 7th Dec. 2022
 */

#ifndef __SALAMANDER_VALUE_H__
#define __SALAMANDER_VALUE_H__

#include <salamander_core.h>
#include <salamander_utils.h>

// To identify the heap-allocated object type.

// When adding a new object type in the future, please follow the alphabetical
// naming order.

typedef enum enum_ObjType {
	OBJ_FIBER
} ObjType;

// The core object representation, which will be inherited by every other
// object types through conventional C structure inheritance.

typedef struct struct_Obj {
	ObjType type;
} Obj;

// The main value representation.

#ifdef SALAMANDER_NAN_TAGGING

typedef uint64_t Value;

#else 

typedef enum enum_ValueType {
	VAL_NUMBER
} ValueType;

typedef struct struct_Value {
	ValueType type;

	union {
		double number;
		Obj* obj;
	} data;
} Value;

#endif    // SALAMANDER_NAN_TAGGING

DECLARE_BUFFER(Value, Value);

// Holds all the debug related function data such as function name, bytecodes 
// corresponding line numbers, etc.

typedef struct struct_FnDebug {
	// Stores the line numbers using run-length encoding method.

	IntBuffer lines;
} FnDebug;

// A function object.
// TODO: Add more features.

typedef struct struct_ObjFn {
	Obj obj;

	// To store the sequence of bytecodes.

	ByteBuffer code;

	// Constant pool to store constants.

	ValueBuffer pool;

	FnDebug* debug;
} ObjFn;

int  salamander_ObjFn_byte_line(ObjFn*, int);
void salamander_ObjFn_write_byte(SalamanderVM*, ObjFn*, uint8_t byte, int line);

#endif    // __SALAMANDER_VALUE_H__
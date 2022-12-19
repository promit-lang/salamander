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

#include <salamander_math.h>
#include <salamander_util.h>

// To identify the heap-allocated object type.

// When adding a new object type in the future, please follow the alphabetical
// naming order.

typedef enum enum_ObjType {
    OBJ_FIBER
} ObjType;

// All the forward declarations of objects reside in this file.

#include <salamander/object.h>

// The core object representation, which will be inherited by every other
// object types through conventional C structure inheritance.

struct struct_Obj {
    ObjType type;
};

// The main value representation.

#if SALAMANDER_NAN_TAGGING

// We only need 64-bits to represent a value.

typedef uint64_t Value;

// A mask which selects the sign bit.

#define SIGN_BIT ((uint64_t) 1 << 63)

// Selects the bits which indicate a quiet NaN.

#define QNAN ((uint64_t) 0x7FFC000000000000)

// If the NaN bits are set, it's not a number.

#define IS_NUM(value) (((value) & QNAN) != QNAN)

#else 

typedef enum enum_ValueType {
    VAL_NUMBER
} ValueType;

typedef struct struct_Value {
    ValueType type;

    union {
        double num;
        Obj* obj;
    } data;
} Value;

#define IS_NUM(value) ((value).type == VAL_NUMBER)

#endif    // SALAMANDER_NAN_TAGGING

// Common macros to convert 'Value' to certain types of data like boolean, 
// number or any types of object.

#define AS_NUM(value) (salamander_Value_value_to_num(value))

// Macros to convert certain types of data like boolean, number or any type
// of objects to 'Value' representation.

#define NUMBER_VAL(num) (salamander_Value_num_to_value(num))

DECLARE_BUFFER(Value, Value);

// Holds all the debug related function data such as function name, bytecodes 
// corresponding line numbers, etc.

typedef struct struct_FnDebug {
    // Stores the line numbers using run-length encoding method.

    IntBuffer lines;
} FnDebug;

// A function object.
// TODO: Add more features.

struct struct_ObjFn {
    Obj obj;

    // To store the sequence of bytecodes.

    ByteBuffer code;

    // Constant pool to store constants.

    ValueBuffer pool;

    FnDebug* debug;
};

int  salamander_ObjFn_byte_line(ObjFn*, int);
void salamander_ObjFn_write_byte(SalamanderVM*, ObjFn*, uint8_t, int);
void salamander_ObjFn_write_short(SalamanderVM*, ObjFn*, uint16_t, int);
int  salamander_ObjFn_write_constant(SalamanderVM*, ObjFn*, Value);

// Converts a double number to 'Value' representation.

static inline Value salamander_Value_num_to_value(double num) {
#if SALAMANDER_NAN_TAGGING
    return (Value) salamander_Math_double_to_bits(num);
#else
    Value value;

    value.type      = VAL_NUMBER;
    value.data.num  = num;

    return value;
#endif
}

// Converts a 'Value' representation to double number.

static inline double salamander_Value_value_to_num(Value value) {
#if SALAMANDER_NAN_TAGGING
    return salamander_Math_double_from_bits((uint64_t) value);
#else 
    return value.data.num;
#endif
}

#endif    // __SALAMANDER_VALUE_H__
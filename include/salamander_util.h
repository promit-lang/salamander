/**
 * salamander_util.h
 * 
 * See the 'LICENSE' file for this file's license.
 *
 * Holds all the utility macros and functions, which is going to be used 
 * throughout the VM implementation.
 *
 * @authors:
 *   1. SD Asif Hossein <s.dah.ingularity@gmail.com> 7th Dec. 2022
 */

#ifndef __SALAMANDER_UTIL_H__
#define __SALAMANDER_UTIL_H__

#include <salamander/salamander.h>
#include <salamander_memory.h>

// To free allocated buffers.

#define FREE_BUFFER(vm, type, memory, old_size)                               \
	salamander_reallocate(vm, memory, sizeof(type) * (old_size), 0);

// To allocate more memory for provided buffer.

#define GROW_BUFFER(vm, type, memory, old_size, new_size)                     \
	salamander_reallocate(vm, memory, sizeof(type) * (old_size),              \
		sizeof(type) * (new_size));

// We are going to use buffers in a lot of cases, e.g. ByteBuffers, 
// ValueBuffers etc. All those buffers are managed in similar way, so 
// declaring a macro to take care about all the general "Buffers".

// This macro is going to be used in ".h" files, somewhere in the VM.

#define DECLARE_BUFFER(name, type)                                            \
	typedef struct struct_##name##Buffer {                                    \
		type* data;                                                           \
		int count;                                                            \
		int capacity;                                                         \
	} name##Buffer;                                                           \
	                                                                          \
	void salamander_##name##Buffer_init(name##Buffer*);                       \
	void salamander_##name##Buffer_free(SalamanderVM*, name##Buffer*);        \
	void salamander_##name##Buffer_fill(SalamanderVM*, name##Buffer*,         \
		type, int);                                                           \
	void salamander_##name##Buffer_write(SalamanderVM*, name##Buffer*, type);

// This macro is complementary to "DECLARE_BUFFER" macro,  which will define 
// all the declared buffer methods.

#define DEFINE_BUFFER(name, type)                                             \
	void salamander_##name##Buffer_init(name##Buffer* buffer) {               \
		buffer -> data     = NULL;                                            \
		buffer -> count    = 0;                                               \
		buffer -> capacity = 0;                                               \
	}                                                                         \
                                                                              \
	void                                                                      \
	salamander_##name##Buffer_free(SalamanderVM* vm, name##Buffer* buffer) {  \
		FREE_BUFFER(vm, type, buffer -> data, buffer -> capacity);            \
		salamander_##name##Buffer_init(buffer);                               \
	}                                                                         \
                                                                              \
	void                                                                      \
	salamander_##name##Buffer_fill(SalamanderVM* vm,                          \
		name##Buffer* buffer, type data, int count)                           \
	{                                                                         \
		int total_count = count + buffer -> count;                            \
                                                                              \
		if(is_true(total_count > buffer -> capacity)) {                       \
			int capacity =                                                    \
				salamander_next_power_of_2(total_count);                      \
                                                                              \
			buffer -> data = GROW_BUFFER(vm, type, buffer -> data,            \
				buffer -> capacity, capacity);                                \
                                                                              \
			buffer -> capacity = capacity;                                    \
		}                                                                     \
                                                                              \
		while(is_true(count--))                                               \
			buffer -> data[buffer -> count++] = data;                         \
	}                                                                         \
                                                                              \
	void                                                                      \
	salamander_##name##Buffer_write(SalamanderVM* vm, name##Buffer* buffer,   \
		 type data)                                                           \
	{                                                                         \
		salamander_##name##Buffer_fill(vm, buffer, data, 1);                  \
	}

// Some essential buffers.

DECLARE_BUFFER(Byte, uint8_t);
DECLARE_BUFFER(Int, int);

// To find a number which is power of 2 and greater than or equal to the 
// provided number.

// This function will generally be used to increase capacity of a buffer.
// Having capacity a power of 2 sits well with the memory management.

int salamander_next_power_of_2(int);

#endif    // __SALAMANDER_UTIL_H__
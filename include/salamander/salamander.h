/**
 * salamander.h
 * 
 * See the 'LICENSE' file for this file's license.
 *
 * This header file provides the main API functions and symbols related to
 * SalamanderVM. Include this file, if you wish to run bytecodes and do
 * interaction with the VM through the API stack.
 *
 * @authors:
 *   1. SD Asif Hossein <s.dah.ingularity@gmail.com> 7th Dec. 2022
 */

#ifndef __SALAMANDER_H__
#define __SALAMANDER_H__

// Standard C libraries.

#include <salamander_value.h>

// For API access specifier.

#include <salamander/api.h>

// SalamanderVM version number componenets.

#define SALAMANDER_VERSION_MAJOR 1
#define SALAMANDER_VERSION_MINOR 0
#define SALAMANDER_VERSION_PATCH 1
#define SALAMANDER_VERSION_REVIS 1    // Revision.

// SVM version string.

#define SALAMANDER_VERSION_STRING "1.0.1r1"

// Numeric representation of SVM version number. Use this if you want to do 
// altogether version check and use specific features in the host application.
// 
// Version number does not include revision.

#define SALAMANDER_VERSION_NUMBER (SALAMANDER_VERSION_MAJOR * 1000000 \
                                   SALAMANDER_VERSION_MINOR *    1000 \
								   SALAMANDER_VERSION_PATCH)

// Forward declaration of structure SalamanderVM. When you embed SVM in your 
// host application, you don't need to access the contents of that struct. So, 
// therefore for security reasons, the contents has been abstracted and the 
// struct declaration can be found on "vm.h" in the main VM implementation.

typedef struct struct_SalamanderVM SalamanderVM;

// A generic user definable allocator function used for VM's memory 
// manangement. The function definition should look like this: 
// 
// void* my_reallocator(void* memory, size_t new_size) { --CODE-- }
// 
// The function will be used like following: 
// 
// (1) To allocate new memory of [new_size] bytes and assign it to a new
//     pointer -> [memory] is 'NULL' and [new_size] is a non-zero positive 
//     value.
// (2) To deallocate the existing memory of a pointer -> [memory] is a valid 
//     pointer and [new_size] is zero (0).
// (3) To extend or shrink the existing memory pointer -> [memory] is valid 
//     pointer and [new_size] is a non-zero positive value.

typedef void* (*SalamanderReallocatorFn)(void*, size_t);

// TODO: add conf.

typedef struct struct_SalamanderConfiguration {
    // The callback SVM will use to allocate, reallocate and deallocate the 
    // memory.
    //
    // If set to 'NULL', SVM will use it's default realloctor function.

    SalamanderReallocatorFn reallocator;
} SalamanderConfiguration;

typedef enum enum_SalamanderResult {
	SALAMANDER_RESULT_RUNTIME_ERROR,
	SALAMANDER_RESULT_SUCCESS
} SalamanderResult;

SALAMANDER_API void 
    salamander_SalamanderConfiguration_init(SalamanderConfiguration*);

#endif    // __SALAMANDER_H__
/**
 * salamander_memory.h
 * 
 * See the 'LICENSE' file for this file's license.
 *
 * @authors:
 *   1. SD Asif Hossein <s.dah.ingularity@gmail.com> 8th Dec. 2022
 */

#include <salamander/salamander.h>
#include <salamander_core.h>

// Forward declaration of objects.

typedef struct struct_Obj Obj;
typedef struct struct_ObjFn ObjFn;

// Allocates new sequence of memory in the heap managed by the VM.

#define ALLOCATE(type)                                                        \
    (type*) salamander_Memory_reallocate(vm, NULL, 0u,                        \
        sizeof(type))

// Free non-sequential memory.

#define FREE(type, memory)                                                    \
    salamander_Memory_reallocate(vm, memory, sizeof(type), 0u)

// To allocate a new buffer.

#define ALLOCATE_BUFFER(type, count)                                          \
    (type*) salamander_Memory_reallocate(vm, NULL, 0u,                        \
        sizeof(type) * (count))

// To allocate more memory for provided buffer.

#define GROW_BUFFER(vm, type, memory, old_size, new_size)                     \
    salamander_Memory_reallocate(vm, memory, sizeof(type) * (old_size),       \
        sizeof(type) * (new_size))

// Frees allocated buffers.

#define FREE_BUFFER(vm, type, memory, old_size)                               \
    salamander_Memory_reallocate(vm, memory, sizeof(type) * (old_size), 0)

// SalamanderVM's default reallocator function.

void* salamander_Memory_default_reallocator(void*, size_t);

// A wrapper memory management function, which will call the default 
// reallocator function defined in the configuration. The purpose of this 
// function is to check whether the VM is out of memory (exceeding the defined 
// memory limit) and call the GC whenever needed, which the reallocator 
// function defined in config is not supposed to do.

void* salamander_Memory_reallocate(SalamanderVM*, void*, size_t, size_t);

// Frees an object.

void salamander_Memory_free_obj(SalamanderVM*, Obj*);
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

// SalamanderVM's default reallocator function.

void* salamander_Memory_default_reallocator(void*, size_t);

// A wrapper memory management function, which will call the default 
// reallocator function defined in the configuration. The purpose of this 
// function is to check whether the VM is out of memory (exceeding the defined 
// memory limit) and call the GC whenever needed, which the reallocator 
// function defined in config is not supposed to do.

void* salamander_Memory_reallocate(SalamanderVM*, void*, size_t, size_t);

// Default SalamanderVM
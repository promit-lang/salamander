#include <salamander_memory.h>
#include <salamander_vm.h>

// Standard C includes.

#include <stdlib.h>

// void* salamander_Memory_default_reallocator(void*, size_t);
// 
// SalamanderVM's default reallocator function.

void* salamander_Memory_default_reallocator(void* memory, size_t new_size) {
    // If [new_size] is 0, free the memory.

    if(likely(new_size == 0u)) {
        free(memory);

        return NULL;
    }

    return realloc(memory, new_size);
}

// void* salamander_Memory_reallocate(SalamanderVM*, void*, size_t, size_t);
// 
// A wrapper memory management function, which will call the default 
// reallocator function defined in the configuration. The purpose of this 
// function is to check whether the VM is out of memory (exceeding the defined 
// memory limit) and call the GC whenever needed, which the reallocator 
// function defined in config is not supposed to do.

void* salamander_Memory_reallocate(SalamanderVM* vm, void* memory, size_t old_size, size_t new_size) {
    // TODO: Add memory limit.
    // TODO: Add GC.

    vm -> total_allocated += new_size - old_size;

    return vm -> config -> reallocator(memory, new_size);
}
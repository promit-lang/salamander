#include <salamander_memory.h>
#include <salamander_vm.h>

// Standard C includes.

#include <stdlib.h>

void* salamander_reallocate(SalamanderVM* vm, void* memory, size_t old_size, size_t new_size) {
	// If 'new_size' is 0, then we are trying to free the memory.

	if(is_true(new_size == 0)) {
		free(memory);

		return NULL;
	}

	void* result = realloc(memory, new_size);

	if(is_true(result == NULL)) {
		// TODO: Add errors.
	}

	return result;
}
#include <salamander/libutil.h>
#include <salamander_vm.h>

#if SALAMANDER_DEBUG_TRACE_EXECUTION
#include <salamander_debug.h>
#endif

// void salamander_SalamanderVM_init(SalamanderVM*);

void salamander_SalamanderVM_init(SalamanderVM* vm) {
	vm -> fn        = NULL;
	vm -> stack_top = vm -> stack;
}

// void salamander_SalamanderVM_free(SalamanderVM*);

void salamander_SalamanderVM_free(SalamanderVM* vm) {

}

static SalamanderResult salamander_execute(SalamanderVM* vm) {
	// These macros are going to be frequently used in this function.

#define PUSH(value)  (*vm -> stack_top++ = (value))
#define POP()        (*(--vm -> stack_top))
#define DROP()       (--vm -> stack_top)
#define PEEK()       (vm -> stack_top - 1)
#define PEEK2()      (vm -> stack_top - 2)
#define READ_BYTE()  (*ip++)
#define READ_SHORT() (ip += 2, (uint16_t) ((ip[-2] << 0x8) | ip[-1]))

// Trace every instruction if 'SALAMANDER_DEBUG_TRACE_EXECUTION' is set.

#if SALAMANDER_DEBUG_TRACE_EXECUTION

#define DEBUG_TRACE_INSTRUCTIONS()  do {              \
		salamander_debug_dump_stack(vm);              \
		salamander_debug_dump_instruction(vm -> fn,   \
			(int) (ip - vm -> fn -> code.data));      \
	} while(false)

#else
#define DEBUG_TRACE_INSTRUCTIONS()
#endif

// Using labels as values aka computed goto, a GCC extension.

#ifdef SALAMANDER_COMPUTED_GOTO

#define OPCODE(code, _) &&CODE_##code,

	static void* dispatch_table[] = {
#include <salamander_opcode.h>
	};

#undef OPCODE

#define INTERPRETER_LOOP DISPATCH();

#define VMCASE(code) CODE_##code
#define DISPATCH()   do {                                  \
		DEBUG_TRACE_INSTRUCTIONS();                        \
		goto *dispatch_table[instruction = READ_BYTE()];   \
	} while(false)

#else

#define INTERPRETER_LOOP                   \
	vm_loop:                               \
		DEBUG_TRACE_INSTRUCTIONS();        \
		switch(instruction = READ_BYTE()) 

#define VMCASE(code) case CODE_##code
#define DISPATCH()   goto vm_loop

#endif

	Code instruction;
	uint8_t* ip = vm -> fn -> code.data;

	INTERPRETER_LOOP 
	{
		VMCASE(CONSTANT): 
			PUSH(vm -> fn -> pool.data[READ_SHORT()]);
			DISPATCH();
		
		VMCASE(ADD): {
			Value result = salamander_Value_add(vm, PEEK2(), PEEK());

			DROP();
			DROP();

			PUSH(result);

			DISPATCH();
		}

		VMCASE(NEGATE): {
			Value result = salamander_Value_negate(vm, PEEK());

			DROP();

			PUSH(result);

			DISPATCH();
		}

		VMCASE(RETURN): 
			return SALAMANDER_RESULT_SUCCESS;

			DISPATCH();
		
		VMCASE(END): 
			UNREACHABLE();
			DISPATCH();
	}
}

// SalamanderResult salamander_SalamanderVM_execute(SalamanderVM*);

SalamanderResult salamander_SalamanderVM_execute(SalamanderVM* vm) {
	return salamander_execute(vm);
}
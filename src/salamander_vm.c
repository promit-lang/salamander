#include <salamander/libutil.h>
#include <salamander_vm.h>

#if SALAMANDER_DEBUG_TRACE_EXECUTION
#include <salamander_debug.h>
#endif

// Frees all bjects allocated with the VM's reallocator.

static void free_objects(SalamanderVM* vm, Obj* start) {
    while(start != NULL) {
        Obj* next = start -> next;

        salamander_Memory_free_obj(vm, start);

        start = next;
    } 
}

// salamander/salamander.h
// 
// void salamander_SalamanderConfiguration_init(SalamanderConfiguration*);
// 
// Initialize the config struct with SVM's default config.

void salamander_SalamanderConfiguration_init(SalamanderConfiguration* config) {
    config -> reallocator = salamander_Memory_default_reallocator;
}

// salamander/salamander.h
// 
// void salamander_SalamanderVM_new(SalamanderConfiguration*);
// 
// Creates a new VM in the heap and returns a pointer to it.
// 
// Note: The reallocator defined in the configuration is used to create the 
//       heap object.

SalamanderVM* salamander_SalamanderVM_new(SalamanderConfiguration* config) {
    SalamanderVM* vm = (SalamanderVM*) 
        config -> reallocator(NULL, sizeof(SalamanderVM));
    
    vm -> fn              = NULL;
    vm -> stack_top       = vm -> stack;
    vm -> config          = config;
    vm -> total_allocated = 0;
    vm -> last            = NULL;

    return vm;
}

// salamander/salamander.h
// 
// void salamander_SalamanderVM_free(SalamanderVM*);
// 
// Frees the heap allocated instance of VM struct. Uses the configs 
// reallocator to free the VM.

void salamander_SalamanderVM_free(SalamanderVM* vm) {
    // First free all the objects.

    free_objects(vm, vm -> last);

    vm -> config -> reallocator(vm, 0u);
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
        salamander_Debug_dump_stack(vm);              \
        salamander_Debug_dump_instruction(vm -> fn,   \
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

        VMCASE(BINARY): {
            BinaryOpType type = (BinaryOpType) READ_BYTE();

            Value* left = PEEK2(),
                    *right = PEEK();
                
            Value result;

            switch(type) {
                case BINARY_ADD: 
                    result = salamander_Value_add(vm, 
                        (Value* const) left, (Value* const) right);
                    break;

                case BINARY_MUL: 
                    result = salamander_Value_multiply(vm,
                        (Value* const) left, (Value* const) right);
                    break;
                
                case BINARY_DIV: 
                    result = salamander_Value_divide(vm, 
                        (Value* const) left, (Value* const) right);
                break;
            
                default: UNREACHABLE();
            }

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

SalamanderResult 
    salamander_SalamanderVM_execute(SalamanderVM* vm, ExecutionType type, void* exe) 
{
    vm -> fn = (ObjFn*) exe;
    
    return salamander_execute(vm);
}
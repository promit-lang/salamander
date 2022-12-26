/** Implements API functions declared in 'salamander/debug.h'. */

#include <salamander_debug.h>

// C standard includes.

#include <stdio.h>

// Dump out the provided value.

static void dump_value(Value value) {
#ifdef SALAMANDER_NAN_TAGGING
    if(likely(IS_NUM(value))) 
        printf("%.14g", AS_NUM(value));
#else
    switch(value.type) {
        case VAL_NUM: printf("'%.14d'", AS_NUM(value)); break;
        default: UNREACHABLE();
    }
#endif
}

// To dump a single instruciton in a single line. Other functions will use 
// this utility to dump whole instruction sets.

static int dump_instruction(ObjFn* fn, int i, int* last_line) {
#define READ_BYTE() (bytecode[i++])
#define READ_SHORT()                                                    \
    (i += 2, (uint16_t) ((bytecode[i - 2] << 0x8) | bytecode[i - 1]))

    int start        = i,
        current_line = salamander_ObjFn_byte_line(fn, i);

    if(unlikely(last_line == NULL || *last_line != current_line)) {
        printf("%4d:", current_line);

        if(unlikely(last_line != NULL))
            *last_line = current_line;
    } else printf("     ");

    uint8_t* bytecode = fn -> code.data;

    Code code = (Code) bytecode[i];

    // Print the instruction offset.

    printf("  %04d  ", i++);

    switch(code) {
        case CODE_CONSTANT: {
            uint16_t index = READ_SHORT();

            printf("%-16s %5hu '", "CONSTANT", index);

            dump_value(fn -> pool.data[index]);

            printf("'");

            break;
        }

        case CODE_BINARY: {
            uint8_t type = READ_BYTE();

            printf("%-16s %5u -> '", "BINARY", type);

            switch(type) {
                case BINARY_ADD: printf("+"); break;
                case BINARY_MUL: printf("*"); break;
                case BINARY_DIV: printf("/"); break;
            }

            printf("'");

            break;
        }
        
        case CODE_NEGATE: printf("NEGATE"); break;
        case CODE_RETURN: printf("RETURN"); break;
        case CODE_END:    printf("END"); break;
    }

    printf("\n");

    // In the very end of each instruction set, there will be CODE_END which
    // indicates the end of execution.

    if(likely(code == CODE_END)) 
        return -1;

    return i - start;

#undef READ_BYTE
#undef READ_SHORT
}

// int salamander_Debug_dump_instruction(ObjFn*, int);

int salamander_Debug_dump_instruction(ObjFn* fn, int i) {
    return dump_instruction(fn, i, NULL);
}

// void salamander_debug_dump_fn(ObjFn*);

void salamander_Debug_dump_fn(ObjFn* fn) {
    int i, offset;

    i = offset = 0;

    int last_line = -1;

    while(offset != -1) {
        offset = dump_instruction(fn, i, &last_line);

        i += offset;
    }

    printf("\n");
}

// void salamander_debug_dump_stack(SalamanderVM*);
//
// Dump the whole fiber stack.

void salamander_Debug_dump_stack(SalamanderVM* vm) {
    printf("Stack: [ ");

    for(Value* slot = vm -> stack; slot < vm -> stack_top; slot++) {
        dump_value(*slot);

        if(likely(slot + 1 < vm -> stack_top))
            printf(", ");
    }

    printf(" ]\n");
}
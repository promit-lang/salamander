#include <salamander_debug.h>

// C standard includes.

#include <stdio.h>

// To dump a single instruciton in a single line. Other functions will use 
// this utility to dump whole instruction sets.

static int dump_instruction(ObjFn* fn, int i, int* last_line) {
#define READ_BYTE() (bytecode[i++])
#define READ_SHORT()                                                    \
	(i += 2, (uint16_t) ((bytecode[i - 2] << 0x8) | bytecode[i - 1]))

	int start        = i,
	    current_line = salamander_ObjFn_byte_line(fn, i);

	if(last_line == NULL || *last_line != current_line) {
		printf("%4d:", current_line);

		*last_line = current_line;
	} else printf("     ");

	uint8_t* bytecode = fn -> code.data;

	Code code = (Code) bytecode[i];

	// Print the instruction offset.

	printf("  %04d  ", i++);

	switch(code) {
		case CODE_CONSTANT: {
			printf("%-16s %5hu ", "CONSTANT", READ_SHORT());

			break;
		}

		case CODE_RETURN:   printf("RETURN"); break;
		case CODE_END:      printf("END"); break;
	}

	printf("\n");

	// In the very end of each instruction set, there will be CODE_END which
	// indicates the end of execution.

	if(code == CODE_END) 
		return -1;
	
	return i - start;

#undef READ_BYTE
#undef READ_SHORT
}

int salamander_dump_instruction(ObjFn* fn, int i) {
	return dump_instruction(fn, i, NULL);
}

void salamander_dump_fn(ObjFn* fn) {
	int i, offset;

	i = offset = 0;

	int last_line = -1;

	while(is_true(offset != -1)) {
		offset = dump_instruction(fn, i, &last_line);

		i += offset;
	}

	printf("\n");
}
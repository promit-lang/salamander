#include <salamander_value.h>

DEFINE_BUFFER(Value, Value);

// int salamander_fn_get_line_of_byte(ObjFn*, int);
//
// Gets the source line number where the provided byte is compiled from.

int salamander_ObjFn_byte_line(ObjFn* fn, int offset) {
	IntBuffer buffer = fn -> debug -> lines;

	// Use binary search like approach to find the line number.

	int left = 0, right = buffer.count - 1, mid = (left + right) / 2;

	while(is_true(left != right)) {
		if(is_true(offset <= buffer.data[mid])) {
			if(is_true(mid == 0 || offset > buffer.data[mid - 1])) 
				return mid + 1;
			else right = mid - 1;
		} else left = mid + 1;

		mid = (right + left) / 2;
	}

	// Above loop doesn't cover the very last line, thus checking whether it
	// is the last line which should be returned.

	if(mid == right && offset <= buffer.data[mid]) 
		return mid + 1;

	// Will not reach, cause it should be ensured by the compiler that a valid
	// line number exists of provided offset number.

	UNREACHABLE();

	return -1;
}

// void salamander_ObjFn_write_byte(SalamanderVM*, ObjFn*, uint8_t, int);
//
// Appends provided byte to the bytecode sequence with encoding the line 
// number the byte is compiled from.

void salamander_ObjFn_write_byte(SalamanderVM* vm, 
	ObjFn* fn, uint8_t byte, int line) 
{
	// Add the line number as debugging info.

	if(is_true(line > fn -> debug -> lines.count)) 
		salamander_IntBuffer_write(vm, &fn -> debug -> lines, fn -> code.count);
	else fn -> debug -> lines.data[line - 1]++;    // Run-length encoding.

	// Insert the byte into the buffer.

	salamander_ByteBuffer_write(vm, &fn -> code, byte);
}

// void salamander_ObjFn_write_short(SalamanderVM*, ObjFn*, uint16_t, int);
// 
// Appends provided short (unsigned 16-bit integer) to the bytecode sequence
// by disecting it to bytes.

void salamander_ObjFn_write_short(SalamanderVM* vm, ObjFn* fn, 
	uint16_t bytes, int line) 
{
	salamander_ObjFn_write_byte(vm, fn, (uint8_t) ((bytes >> 0x8) & 0xFF), line);
	salamander_ObjFn_write_byte(vm, fn, (uint8_t) (bytes & 0xFF), line);
}

// int salamander_ObjFn_write_constant(SalamanderVM, ObjFn*, Value);
//
// Writes the provided constant to the constant pool.

int salamander_ObjFn_write_constant(SalamanderVM* vm, ObjFn* fn, Value constant) {
	int idx = fn -> pool.count;

	salamander_ValueBuffer_write(vm, &fn -> pool, constant);

	return idx;
}
#include <salamander_util.h>

// Buffer definitions.

DEFINE_BUFFER(Byte, uint8_t);
DEFINE_BUFFER(Int, int);

// int salamander_next_power_of_2(int);

int salamander_next_power_of_2(int x) {
	// This method of finding power of 2 only works if current value of 'x'
	// is not a power of 2. So, for precautions, decrease the number by 1.

	x--;

	// Main ideology: 
	// Say if we have something like: x -> 00100101
	// We are going to make it something like: x -> 00111111
	// Then if we increase the value by 1, we get: x -> 01000000
	// which is going to be a power of 2 and greater than or equal to
	// the number we had.

	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;

	x++;

	return x;
}
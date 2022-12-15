/** Implements API functions in 'salamander/libutil.h'. */

#include <salamander/libutil.h>

// Value salamander_Value_add(SalamanderVM*, Value, Value);
// 
// Does addition of the second value to the first value. Calls overloaded
// operator '+' on the first value argument if defined in the class or 
// wrapper class.

Value salamander_Value_add(SalamanderVM* vm, Value* a, Value* b) {
	return NUMBER_VAL(AS_NUM(*a) + AS_NUM(*b));
}

// Value salamander_Value_negate(SalamanderVM*, Value);
// 
// Negates the provided value. Calls the '-' overloaded operator if defined
// in class or wrapper class.

Value salamander_Value_negate(SalamanderVM* vm, Value* value) {
	Value result = salamander_Value_convert_to_num(vm, value);

	return NUMBER_VAL(-AS_NUM(result));
}

// double salamander_Value_convert_to_num(SalamanderVM*, Value);
// 
// Attempts to convert a 'Value' of any type of to number.

Value salamander_Value_convert_to_num(SalamanderVM* vm, Value* value) {
	Value result = *value;

#if SALAMANDER_NAN_TAGGING

	if(is_true(IS_NUM(*value))) {}

#else

	switch(value -> type) {
		
	}

#endif

	return result;
}

// bool salamander_Value_is_valid_num(double);
// 
// Checks whether provided number is valid or not.

bool salamander_is_valid_num(double num) {
	return !isnan(num) && !isinf(num);
}
/** Implements API functions declared in 'salamander/libutil.h'. */

#include <salamander/libutil.h>

// Value salamander_Value_add(SalamanderVM*, Value* const, Value* const);
// 
// Does addition of the second value to the first value. Calls overloaded
// operator '+' on the first value argument if defined in the class or 
// wrapper class.

Value salamander_Value_add(SalamanderVM* vm, Value* const a, Value* const b) {
	return NUMBER_VAL(AS_NUM(*a) + AS_NUM(*b));
}

// Value salamander_Value_multiply(SalamanderVM*, Value* const, Value* const);
// 
// Multiplies the first value with the second value. Calls overloaded
// operator '*' on the first value argument if defined in the class or 
// wrapper class.

Value salamander_Value_multiply(SalamanderVM* vm, 
	Value* const a, Value* const b) 
{
	return NUMBER_VAL(AS_NUM(*a) * AS_NUM(*b));
}

// Value salamander_Value_divide(SalamanderVM*, Value* const, Value* const);
// 
// Divides the first value with the second value. Calls overloaded
// operator '*' on the first value argument if defined in the class or 
// wrapper class.

Value salamander_Value_divide(SalamanderVM* vm, 
	Value* const a, Value* const b) 
{
	return NUMBER_VAL(AS_NUM(*a) / AS_NUM(*b));
}

// Value salamander_Value_negate(SalamanderVM*, Value* const);
// 
// Negates the provided value. Calls the '-' overloaded operator if defined
// in class or wrapper class.

Value salamander_Value_negate(SalamanderVM* vm, Value* const value) {
	Value result = salamander_Value_convert_to_num(vm, value);

	return NUMBER_VAL(-AS_NUM(result));
}

// double salamander_Value_convert_to_num(SalamanderVM*, Value* const);
// 
// Attempts to convert a 'Value' of any type of to number.

Value salamander_Value_convert_to_num(SalamanderVM* vm, Value* value) {
	Value result = *value;

#if SALAMANDER_NAN_TAGGING

	if(is_true(IS_NUM(*value))) {}

#else

	switch(value -> type) {
		case VAL_NUMBER: break;
	}

#endif

	return result;
}

// bool salamander_Value_is_valid_num(Value* const);
// 
// Checks whether provided number is valid or not.

bool salamander_Value_is_valid_num(Value* const value) {
	if(is_false(IS_NUM(*value))) 
		return false;
	
	double num = AS_NUM(*value);

	return !isnan(num) && !isinf(num);
}
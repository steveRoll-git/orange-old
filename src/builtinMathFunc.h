#define STRINGIFY(X) #X
#define TOSTRING(x) STRINGIFY(x)

Value MATH_FUNCNAME(VM& vm, Value& list)
{
	NumberType result;
	Value* current = &list;

	if (current->type != ValueType::List)
	{
		throw RuntimeException(std::string("Not enough arguments for " TOSTRING(MATH_OPERATOR)));
	}

	bool gotFirst = false;

	while (current != nullptr && current->type == ValueType::List)
	{
		Value& num = vm.evaluate(current->cons->car);

		if (num.type != ValueType::Number)
		{
			throw RuntimeException(std::string(TOSTRING(MATH_OPERATOR) " cannot perform arithmetic on ") + num.getTypeName() + " value");
		}

		if (gotFirst)
		{
			result = result MATH_OPERATOR num.number;
		}
		else
		{
			gotFirst = true;
			result = num.number;
		}

		current = &current->cons->cdr;
	}

	return Value(ValueType::Number, result);
}
Value MATH_FUNCNAME(VM& vm, Value& list)
{
	NumberType result;
	Value* current = &list;

	bool gotFirst = false;

	while (current != nullptr && current->type == ValueType::List)
	{
		Value& num = vm.evaluate(current->cons->car);

		if (num.type != ValueType::Number)
		{
			throw RuntimeException(std::string("cannot perform arithmetic on ") + num.getTypeName() + " value");
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
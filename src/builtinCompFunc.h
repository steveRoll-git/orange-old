#define STRINGIFY(X) #X
#define TOSTRING(x) STRINGIFY(x)

Value COMP_FUNCNAME(VM& vm, Value& args)
{
	expectArgsExactly(args, 2, STRINGIFY(COMP_OPERATOR));

	Value a = vm.evaluate(args.cons->car);

	if (a.type != ValueType::Number)
	{
		throw RuntimeException(std::string(TOSTRING(COMP_OPERATOR) " cannot compare ") + a.getTypeName() + " value");
	}

	Value b = vm.evaluate(args.cons->cdr.cons->car);

	if (b.type != ValueType::Number)
	{
		throw RuntimeException(std::string(TOSTRING(COMP_OPERATOR) " cannot compare ") + b.getTypeName() + " value");
	}

	return Value(ValueType::Boolean, a.number COMP_OPERATOR b.number);
}

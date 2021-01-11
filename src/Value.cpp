#include "Value.h"

using namespace Orange;

const char* Value::getTypeName()
{
	switch (type)
	{
	case Orange::ValueType::Nil:
		return "nil";
	case Orange::ValueType::Number:
		return "number";
	case Orange::ValueType::String:
		return "string";
	case Orange::ValueType::Symbol:
		return "symbol";
	case Orange::ValueType::List:
		return "list";
	default:
		return "invalid";
	}
}

std::string Value::toString(bool hideListParens)
{
	if (type == ValueType::String || type == ValueType::Symbol)
	{
		return string;
	}
	else if (type == ValueType::Number)
	{
		std::string result = std::to_string(number);
		result.erase(result.find_last_not_of('0') + 1, std::string::npos);
		if (result.back() == '.')
		{
			result.pop_back();
		}
		return result;
	}
	else if (type == ValueType::List)
	{
		std::string result;

		if (!hideListParens)
		{
			result.push_back('(');
		}

		result.append(cons->toString());

		if (!hideListParens)
		{
			result.push_back(')');
		}

		return result;
	}
	else
	{
		return getTypeName();
	}
}

std::string ConsCell::toString()
{
	std::string result;

	result.append(car.toString());

	if (cdr.type != ValueType::Nil)
	{
		result.push_back(' ');
		bool isDottedList = cdr.type != ValueType::List;
		if (isDottedList)
		{
			result.append(". ");
		}
		result.append(cdr.toString(!isDottedList));
	}

	return result;
}
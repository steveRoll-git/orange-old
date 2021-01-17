#include "Value.h"

#include <sstream>

using namespace Orange;

std::string to_hex_string(std::size_t i)
{
	std::stringstream s;
	s << "0x" << std::hex << i;
	return s.str();
}

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
	case Orange::ValueType::Boolean:
		return "boolean";
	case Orange::ValueType::Symbol:
		return "symbol";
	case Orange::ValueType::List:
		return "list";
	case Orange::ValueType::Function:
		return "function";
	case Orange::ValueType::InternalFunction:
		return "internal function";
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
	else if (type == ValueType::Boolean)
	{
		return boolean ? "true" : "false";
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
		std::string result = std::string("<") + getTypeName();
		if (type == ValueType::InternalFunction)
		{
			result.push_back(' ');
			result.append(to_hex_string((std::size_t)internalFunc));
		}
		result.push_back('>');
		return result;
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
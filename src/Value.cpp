#include "Value.h"
#include "ConsCell.h"

#include <sstream>

using namespace Orange;

std::string to_hex_string(std::size_t i)
{
	std::stringstream s;
	s << "0x" << std::hex << i;
	return s.str();
}

Value::Value() : type(ValueType::Nil) {};
Value::Value(ValueType _type) : type(_type)
{
	if (type == ValueType::Symbol || type == ValueType::String)
	{
		new(&stringVal) std::string;
	}
}
Value::Value(ValueType _type, NumberType _number) : type(_type)
{
	setValue(_number);
}
Value::Value(ValueType _type, const std::string& _string) : type(_type)
{
	setValue(_string);
}
Value::Value(ValueType _type, bool _boolean) : type(_type), boolean(_boolean) {};
Value::Value(ValueType _type, ConsCell* _cons) : type(_type), cons(_cons) {};
Value::Value(ValueType _type, InternalFunction _func) : type(_type), internalFunc(_func) {};

Value::Value(const Value& other)
{
	copyOther(other);
}
void Value::operator =(const Value& other)
{
	copyOther(other);
}

void Value::setValue(const std::string& _string)
{
	new(&stringVal) std::string;
	stringVal = _string;
	valueSet = true;
}
void Value::setValue(double _number)
{
	number = _number;
	valueSet = true;
}

bool Value::isTruthy() const
{
	return !(type == ValueType::Nil || (type == ValueType::Boolean && boolean == false));
}

Value::~Value()
{
	if ((type == ValueType::Symbol || type == ValueType::String) && valueSet)
	{
		stringVal.std::string::~string();
	}
}

void Value::copyOther(const Value& other)
{
	type = other.type;
	if ((other.type == ValueType::Symbol || other.type == ValueType::String) && other.valueSet)
	{
		setValue(other.stringVal);
	}
	else if (other.type == ValueType::Number)
	{
		number = other.number;
	}
	else if (other.type == ValueType::Boolean)
	{
		boolean = other.boolean;
	}
	else if (other.type == ValueType::List)
	{
		cons = other.cons;
	}
	else if (other.type == ValueType::InternalFunction)
	{
		internalFunc = other.internalFunc;
	}
}

const char* Value::getTypeName() const
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

std::string Value::toString(bool hideListParens) const
{
	if (type == ValueType::String || type == ValueType::Symbol)
	{
		return stringVal;
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

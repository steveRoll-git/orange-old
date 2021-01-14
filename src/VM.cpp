#include "VM.h"

#include "RuntimeException.h"

Value VM::evaluate(Value& v)
{
	if (v.type == ValueType::Nil || v.type == ValueType::Number || v.type == ValueType::String)
	{
		//self-evaluating
		return v;
	}
	else if (v.type == ValueType::Symbol)
	{
		//symbol lookup
		if (bindings.count(v.string))
		{
			return bindings.at(v.string);
		}
		else
		{
			return Value();
		}
	}
	else if (v.type == ValueType::List)
	{
		//function call
		Value func = evaluate(v.cons->car);

		if (func.type != ValueType::Function && func.type != ValueType::InternalFunction)
		{
			throw RuntimeException(std::string("cannot call value of type ") + func.getTypeName());
		}

		if (func.type == ValueType::InternalFunction)
		{
			return func.internalFunc(*this, v.cons->cdr);
		}
	}
}

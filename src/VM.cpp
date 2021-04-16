#include "VM.h"

#include "RuntimeException.h"

#include "builtinFunctions.h"

VM::VM()
{
	for (auto& func : builtinFunctions)
	{
		pushBinding(func.first, Value(ValueType::InternalFunction, func.second));
	}
}

Value VM::evaluate(Value& v)
{
	if (v.type == ValueType::Nil || v.type == ValueType::Number || v.type == ValueType::String || v.type == ValueType::Boolean)
	{
		//self-evaluating
		return v;
	}
	else if (v.type == ValueType::Symbol)
	{
		//symbol lookup
		return getBinding(v.string);
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

void Orange::VM::pushBinding(std::string& name, Value& value)
{
	if (!bindings.count(name))
	{
		bindings[name] = std::vector<Value>();
	}

	bindings[name].push_back(value);
}

void Orange::VM::popBinding(std::string& name)
{
	if (bindings.count(name))
	{
		bindings[name].pop_back();
	}
}

Value Orange::VM::getBinding(std::string& name)
{
	if (bindings.count(name))
	{
		std::vector<Value>& vec = bindings.at(name);
		if (vec.size() > 0)
		{
			return vec[vec.size() - 1];
		}
	}
	return Value();
}

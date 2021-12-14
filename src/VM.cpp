#include "VM.h"

#include "RuntimeException.h"

#include "builtinFunctions.h"

VM::VM()
{
	pushScope();
	for (auto& func : builtinFunctions)
	{
		setBinding(func.first, Value(ValueType::InternalFunction, func.second));
	}
}

Value VM::evaluate(const Value& v)
{
	if (v.type == ValueType::Nil || v.type == ValueType::Number || v.type == ValueType::String || v.type == ValueType::Boolean)
	{
		//self-evaluating
		return v;
	}
	else if (v.type == ValueType::Symbol)
	{
		//symbol lookup
		return getBinding(v.stringVal);
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

void Orange::VM::pushScope()
{
	scopes.push_back(std::unordered_map<std::string, Value>());
}

void Orange::VM::popScope()
{
	scopes.pop_back();
}

std::unordered_map<std::string, Value>& Orange::VM::lastScope()
{
	return scopes.back();
}

void Orange::VM::setBinding(const std::string& name, const Value& value)
{
	if (!scopes.empty())
	{
		scopes.back()[name] = value;
	}
}

Value Orange::VM::getBinding(const std::string& name)
{
	if (!scopes.empty())
	{
		for (int i = scopes.size() - 1; i >= 0; i--)
		{
			std::unordered_map<std::string, Value>& scope = scopes[i];
			if (scope.count(name))
			{
				return scope[name];
			}
		}
	}
	return Value();
}

#pragma once

#include "VM.h"
#include "RuntimeException.h"

#include <iostream>
#include <sstream>

namespace Orange
{
#define MATH_OPERATOR +
#define MATH_FUNCNAME math_add
#include "builtinMathFunc.h"

#define MATH_OPERATOR -
#define MATH_FUNCNAME math_sub
#include "builtinMathFunc.h"

#define MATH_OPERATOR *
#define MATH_FUNCNAME math_mul
#include "builtinMathFunc.h"

#define MATH_OPERATOR /
#define MATH_FUNCNAME math_div
#include "builtinMathFunc.h"

	Value builtin_print(VM& vm, Value& list)
	{
		Value* current = &list;

		std::stringstream output;

		while (current != nullptr && current->type == ValueType::List)
		{
			Value& val = vm.evaluate(current->cons->car);

			output << val.toString();

			current = &current->cons->cdr;
		}

		std::cout << output.str() << std::endl;

		return Value();
	}

	Value builtin_if(VM& vm, Value& args)
	{
		if (!(args.type == ValueType::List && args.cons->getLength() == 3))
		{
			throw RuntimeException(std::string("'if' expected 3 parameters"));
		}

		Value& condition = args.cons->car;

		if (vm.evaluate(condition).isTruthy())
		{
			return vm.evaluate(args.cons->cdr.cons->car);
		}
		else
		{
			return vm.evaluate(args.cons->cdr.cons->cdr.cons->car);
		}
	}

	Value builtin_quote(VM&, Value& args)
	{
		if (!(args.type == ValueType::List && args.cons->getLength() == 1))
		{
			throw RuntimeException(std::string("'quote' expected 1 parameter"));
		}

		return args.cons->car;
	}

	std::pair<std::string, InternalFunction> builtinFunctions[] = {
		std::make_pair(std::string("+"), math_add),
		std::make_pair(std::string("-"), math_sub),
		std::make_pair(std::string("*"), math_mul),
		std::make_pair(std::string("/"), math_div),
		std::make_pair(std::string("print"), builtin_print),
		std::make_pair(std::string("if"), builtin_if),
		std::make_pair(std::string("quote"), builtin_quote),
	};
}
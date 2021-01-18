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

	std::pair<std::string, InternalFunction> builtinFunctions[] = {
		std::make_pair(std::string("+"), math_add),
		std::make_pair(std::string("-"), math_sub),
		std::make_pair(std::string("*"), math_mul),
		std::make_pair(std::string("/"), math_div),
		std::make_pair(std::string("print"), builtin_print),
	};
}
#pragma once

#include "VM.h"
#include "RuntimeException.h"
#include "ConsCell.h"

#include <iostream>
#include <sstream>

using ss = std::stringstream;

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

	void expectArgsExactly(Value& args, int count, const char* funcName)
	{
		if (!(args.type == ValueType::List && args.cons->getLength() == count))
		{
            std::stringstream ss;
            ss << "'" << funcName << "' expected " << count << " parameters";
			throw RuntimeException(ss.str());
		}
	}

	void expectArgsAtLeast(Value& args, int count, const char* funcName)
	{
		if (!(args.type == ValueType::List && args.cons->getLength() >= count))
		{
			std::stringstream ss;
			ss << "'" << funcName << "' expected at least " << count << " parameters";
			throw RuntimeException(ss.str());
		}
	}

#define COMP_OPERATOR <
#define COMP_FUNCNAME builtin_lt
#include "builtinCompFunc.h"

#define COMP_OPERATOR >
#define COMP_FUNCNAME builtin_gt
#include "builtinCompFunc.h"

#define COMP_OPERATOR <=
#define COMP_FUNCNAME builtin_le
#include "builtinCompFunc.h"

#define COMP_OPERATOR >=
#define COMP_FUNCNAME builtin_ge
#include "builtinCompFunc.h"

	Value builtin_eq(VM& vm, Value& args)
	{
		expectArgsExactly(args, 2, "=");

		Value a = vm.evaluate(args.cons->car);

		Value b = vm.evaluate(args.cons->cdr.cons->car);

		if (a.type == b.type)
		{
			if (a.type == ValueType::Number)
			{
				return Value(ValueType::Boolean, a.number == b.number);
			}
			else if (a.type == ValueType::String)
			{
				return Value(ValueType::Boolean, a.stringVal == b.stringVal);
			}
		}

		throw RuntimeException((ss() << "Cannot compare values of types " << a.getTypeName() << " and " << b.getTypeName()).str());
	}

	Value builtin_ne(VM& vm, Value& args)
	{
		expectArgsExactly(args, 2, "/=");

		Value a = vm.evaluate(args.cons->car);

		Value b = vm.evaluate(args.cons->cdr.cons->car);

		if (a.type == b.type)
		{
			if (a.type == ValueType::Number)
			{
				return Value(ValueType::Boolean, a.number != b.number);
			}
			else if (a.type == ValueType::String)
			{
				return Value(ValueType::Boolean, a.stringVal != b.stringVal);
			}
		}

		throw RuntimeException((ss() << "Cannot compare values of types " << a.getTypeName() << " and " << b.getTypeName()).str());
	}

	Value builtin_print(VM& vm, Value& list)
	{
		Value* current = &list;

		std::stringstream output;

		while (current != nullptr && current->type == ValueType::List)
		{
			const Value& val = vm.evaluate(current->cons->car);

			output << val.toString();

			current = &current->cons->cdr;
		}

		std::cout << output.str() << std::endl;

		return Value();
	}

	Value builtin_if(VM& vm, Value& args)
	{
		expectArgsExactly(args, 3, "if");

		const Value& condition = args.cons->car;

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
		expectArgsExactly(args, 1, "quote");

		return args.cons->car;
	}

	Value builtin_car(VM& vm, Value& args)
	{
		expectArgsExactly(args, 1, "car");

		const Value& theList = vm.evaluate(args.cons->car);

		if (theList.type != ValueType::List)
		{
			throw RuntimeException(std::string("'car' expected list parameter"));
		}

		return theList.cons->car;
	}

	Value builtin_cdr(VM& vm, Value& args)
	{
		expectArgsExactly(args, 1, "cdr");

		const Value& theList = vm.evaluate(args.cons->car);

		if (theList.type != ValueType::List)
		{
			throw RuntimeException(std::string("'cdr' expected list parameter"));
		}

		return theList.cons->cdr;
	}

	Value builtin_list(VM& vm, Value& args)
	{
		Value* current_arg = &args;

		Value result_first = Value(ValueType::List);
		ConsCell* result_last = nullptr;

		while (current_arg != nullptr && current_arg->type == ValueType::List)
		{
			const Value& val = vm.evaluate(current_arg->cons->car);

			ConsCell* newList = new ConsCell(val, Value());

			if (result_last == nullptr)
			{
				result_first.cons = newList;
			}
			else
			{
				result_last->cdr = Value(ValueType::List, newList);
			}

			result_last = newList;

			current_arg = &current_arg->cons->cdr;
		}

		if (result_last == nullptr)
		{
			result_first.cons = new ConsCell();
		}

		return result_first;
	}

	Value builtin_cons(VM& vm, Value& args)
	{
		expectArgsExactly(args, 2, "cons");

		return Value(ValueType::List, new ConsCell(vm.evaluate(args.cons->car), vm.evaluate(args.cons->cdr.cons->car)));
	}

	Value builtin_eval(VM& vm, Value& args)
	{
		expectArgsExactly(args, 1, "eval");

		return vm.evaluate(vm.evaluate(args.cons->car));
	}

	Value builtin_let(VM& vm, Value& args)
	{
		expectArgsAtLeast(args, 2, "let");

		vm.pushScope();

		Value* currentVar = &args.cons->car;

		while (currentVar != nullptr && currentVar->type == ValueType::List && currentVar->cons->car.type != ValueType::Nil)
		{
			Value currentDef = currentVar->cons->car;

			if (currentDef.type != ValueType::List || currentDef.cons->car.type != ValueType::Symbol || currentDef.cons->cdr.type != ValueType::List)
			{
				throw RuntimeException((ss() << "Invalid variable definition: " << currentDef.toString()).str());
			}

			Value varName = currentDef.cons->car;
			Value varValue = currentDef.cons->cdr.cons->car;

			vm.lastScope()[varName.stringVal] = vm.evaluate(varValue);

			currentVar = &currentVar->cons->cdr;
		}

		Value returnValue;

		Value* currentForm = &args.cons->cdr;

		while (currentForm != nullptr && currentForm->type == ValueType::List)
		{
			returnValue = vm.evaluate(currentForm->cons->car);

			currentForm = &currentForm->cons->cdr;
		}

		vm.popScope();

		return returnValue;
	}

	Value builtin_defun(VM& vm, Value& args)
	{
		expectArgsAtLeast(args, 3, "defun");

		if (args.cons->car.type != ValueType::Symbol)
		{
			throw RuntimeException((ss() << "Function name must be a symbol (was a " << args.cons->car.getTypeName() << " " << args.cons->car.toString() << ")").str());
		}
		string name = args.cons->car.stringVal;

		vector<string> argNames;

		Value* currentArg = &args.cons->cdr.cons->car;
		if (currentArg->type != ValueType::List)
		{
			throw RuntimeException((ss() << "Function arguments list must be a list (was a " << currentArg->getTypeName() << " " << currentArg->toString() << ")").str());
		}

		while (currentArg != nullptr && currentArg->type == ValueType::List && currentArg->cons->car.type != ValueType::Nil)
		{
			Value theArg = currentArg->cons->car;
			if (theArg.type != ValueType::Symbol)
			{
				throw RuntimeException((ss() << "Function argument must be a symbol (was a " << theArg.getTypeName() << " " << theArg.toString() << ")").str());
			}
			argNames.push_back(theArg.stringVal);
			currentArg = &currentArg->cons->cdr;
		}

		Function theFunc = Function(argNames, args.cons->cdr.cons->cdr.cons);

		Function bleh = theFunc;

		vm.lastScope()[name] = Value(ValueType::Function, theFunc);

		return Value();
	}

	std::pair<std::string, InternalFunction> builtinFunctions[] = {
		std::make_pair(std::string("+"), math_add),
		std::make_pair(std::string("-"), math_sub),
		std::make_pair(std::string("*"), math_mul),
		std::make_pair(std::string("/"), math_div),
		std::make_pair(std::string("<"), builtin_lt),
		std::make_pair(std::string(">"), builtin_gt),
		std::make_pair(std::string("<="), builtin_le),
		std::make_pair(std::string(">="), builtin_ge),
		std::make_pair(std::string("="), builtin_eq),
		std::make_pair(std::string("/="), builtin_ne),
		std::make_pair(std::string("print"), builtin_print),
		std::make_pair(std::string("if"), builtin_if),
		std::make_pair(std::string("quote"), builtin_quote),
		std::make_pair(std::string("car"), builtin_car),
		std::make_pair(std::string("cdr"), builtin_cdr),
		std::make_pair(std::string("list"), builtin_list),
		std::make_pair(std::string("cons"), builtin_cons),
		std::make_pair(std::string("eval"), builtin_eval),
		std::make_pair(std::string("let"), builtin_let),
		std::make_pair(std::string("defun"), builtin_defun),
	};
}

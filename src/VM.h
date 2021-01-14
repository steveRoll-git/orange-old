#pragma once

#include "Value.h"
#include <unordered_map>

using namespace Orange;

namespace Orange
{
	class VM
	{
	public:
		VM();

		Value evaluate(Value& v);

	private:
		std::unordered_map<std::string, Value> bindings;
	};
}


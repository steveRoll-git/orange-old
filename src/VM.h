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

		void pushBinding(std::string& name, Value& value);
		void popBinding(std::string& name);
		Value getBinding(std::string& name);

	private:
		std::unordered_map<std::string, std::vector<Value>> bindings;
	};
}


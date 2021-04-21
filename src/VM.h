#pragma once

#include "Value.h"
#include <unordered_map>
#include <vector>

using namespace Orange;

namespace Orange
{
	class VM
	{
	public:
		VM();

		Value evaluate(const Value& v);

		void pushBinding(const std::string& name, const Value& value);
		void popBinding(const std::string& name);
		Value getBinding(const std::string& name);

	private:
		std::unordered_map<std::string, std::vector<Value>> bindings;
	};
}


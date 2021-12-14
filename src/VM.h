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

		void pushScope();
		void popScope();
		std::unordered_map<std::string, Value>& lastScope();
		void setBinding(const std::string& name, const Value& value);
		Value getBinding(const std::string& name);

	private:
		std::vector<std::unordered_map<std::string, Value>> scopes; // a stack of scopes
	};
}


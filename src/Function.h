#pragma once

#include <unordered_map>
#include <vector>

using namespace std;

namespace Orange
{
	struct ConsCell;

	struct Function
	{
	public:
		vector<string> argumentNames;
		ConsCell* body;

		Function(vector<string>& argumentNames, ConsCell* body) : argumentNames(argumentNames), body(body) {};
	};
}
#pragma once

#include "Value.h"

namespace Orange
{
	struct ConsCell
	{
		Value car;
		Value cdr;

		ConsCell() {}
		ConsCell(const Value& car, const Value& cdr) : car(car), cdr(cdr) {}

		std::string toString();
		bool isEmpty();

		int getLength();
	};
}

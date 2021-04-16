#include "ConsCell.h"

using namespace Orange;

std::string ConsCell::toString()
{
	std::string result;

	result.append(car.toString());

	if (cdr.type != ValueType::Nil)
	{
		result.push_back(' ');
		bool isDottedList = cdr.type != ValueType::List;
		if (isDottedList)
		{
			result.append(". ");
		}
		result.append(cdr.toString(!isDottedList));
	}

	return result;
}

bool ConsCell::isEmpty()
{
	return car.type == ValueType::Nil && cdr.type == ValueType::Nil;
}

int ConsCell::getLength()
{
	return 1 + (cdr.type == ValueType::List ? cdr.cons->getLength() : 0);
}
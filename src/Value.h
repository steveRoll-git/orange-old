#ifndef VALUE_H
#define VALUE_H

namespace Orange
{
	enum class ValueType
	{
		Nil,
		Number,
		String,
		Symbol,
		List
	};

	typedef double NumberType;

	struct List;

	struct Value
	{
		ValueType type;

		union
		{
			NumberType number;
			char* string;
			char* symbol;
			List* list;
		};
	};

	struct List
	{
		Value car;
		Value cdr;
	};
}

#endif // VALUE_H

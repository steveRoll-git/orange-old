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

	struct ConsCell;

	struct Value
	{
		ValueType type;

		union
		{
			NumberType number;
			char* string;
			//char* symbol;
			ConsCell* cons;
		};

		Value() : type(ValueType::Nil) {};
		Value(ValueType _type) : type(_type) {};
		Value(ValueType _type, NumberType _number) : type(_type), number(_number) {};
		Value(ValueType _type, char* _string) : type(_type), string(_string) {};
		//Value(ValueType _type, char* _symbol) : type(_type), symbol(_symbol) {};
		Value(ValueType _type, ConsCell* _cons) : type(_type), cons(_cons) {};
	};

	struct ConsCell
	{
		Value car;
		Value cdr;
	};
}

#endif // VALUE_H

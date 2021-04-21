#ifndef VALUE_H
#define VALUE_H

#include <string>

namespace Orange
{
	enum class ValueType
	{
		Nil,
		Number,
		String,
		Boolean,
		Symbol,
		List,
		Function,
		InternalFunction,
	};

	struct Value;

	class VM;

	typedef Value(*InternalFunction)(VM&, Value&);

	typedef double NumberType;

	struct ConsCell;

	struct Value
	{
		ValueType type;

		union
		{
			NumberType number;
			std::string stringVal;
			bool boolean;
			ConsCell* cons;
			InternalFunction internalFunc;
		};

		bool valueSet = false;

		Value();
		Value(ValueType _type);
		Value(ValueType _type, NumberType _number);
		Value(ValueType _type, const std::string& _string);
		Value(ValueType _type, bool _boolean);
		Value(ValueType _type, ConsCell* _cons);
		Value(ValueType _type, InternalFunction _func);
		Value(const Value& other);

		void operator =(const Value& other);

		void copyOther(const Value& other);

		void setValue(const std::string& _string);
		void setValue(double _number);

		bool isTruthy() const;

		~Value();

		const char* getTypeName() const;
		std::string toString(bool hideListParens = false) const;
	};
}

#endif // VALUE_H

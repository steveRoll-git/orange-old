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
			std::string string;
			bool boolean;
			ConsCell* cons;
			InternalFunction internalFunc;
		};

		bool valueSet = false;

		Value() : type(ValueType::Nil) {};
		Value(ValueType _type) : type(_type)
		{
			if (type == ValueType::Symbol || type == ValueType::String)
			{
				new(&string) std::string;
			}
		}
		Value(ValueType _type, NumberType _number) : type(_type)
		{
			setValue(_number);
		}
		Value(ValueType _type, std::string& _string) : type(_type)
		{
			setValue(_string);
		}
		Value(ValueType _type, bool _boolean) : type(_type), boolean(_boolean) {};
		Value(ValueType _type, ConsCell* _cons) : type(_type), cons(_cons) {};
		Value(ValueType _type, InternalFunction _func) : type(_type), internalFunc(_func) {};

		void copyOther(Value& other)
		{
			type = other.type;
			if ((other.type == ValueType::Symbol || other.type == ValueType::String) && other.valueSet)
			{
				setValue(other.string);
			}
			else if (other.type == ValueType::Number)
			{
				number = other.number;
			}
			else if (other.type == ValueType::Boolean)
			{
				boolean = other.boolean;
			}
			else if (other.type == ValueType::List)
			{
				cons = other.cons;
			}
			else if (other.type == ValueType::InternalFunction)
			{
				internalFunc = other.internalFunc;
			}
		}

		Value(Value& other)
		{
			copyOther(other);
		}
		void operator =(Value& other)
		{
			copyOther(other);
		}

		void setValue(std::string& _string)
		{
			new(&string) std::string;
			string = _string;
			valueSet = true;
		}
		void setValue(double _number)
		{
			number = _number;
			valueSet = true;
		}

		~Value()
		{
			if ((type == ValueType::Symbol || type == ValueType::String) && valueSet)
			{
				string.~string();
			}
		}

		const char* getTypeName();
		std::string toString(bool hideListParens = false);
	};

	struct ConsCell
	{
		Value car;
		Value cdr;

		std::string toString();
		bool isEmpty()
		{
			return car.type == ValueType::Nil && cdr.type == ValueType::Nil;
		}
	};
}

#endif // VALUE_H

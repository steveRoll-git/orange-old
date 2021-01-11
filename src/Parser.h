#pragma once

#include "Lang/Lexer.h"

#include "Value.h"

using namespace Orange::Lang;

namespace Orange
{
	class Parser : Lexer
	{
	public:
		Parser(std::istream& _codeStream, std::string& _sourceName);

	private:
		Token curToken;
		void nextToken();
		Token accept(Token t);
		void expect(Token t);

		Value parseValue();
		ConsCell* parseList();
	};
}

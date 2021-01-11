#include "Parser.h"

#include "Lang/SyntaxErrorException.h"

using namespace Orange;

Parser::Parser(std::istream& _codeStream, std::string& _sourceName) : Lexer(_codeStream, _sourceName)
{
	nextToken();
}

void Parser::nextToken()
{
	curToken = Lexer::nextToken();
}

Token Parser::accept(Token t)
{
	if (curToken.compareTo(t))
	{
		Token current = curToken;
		nextToken();
		return current;
	}
	return Token();
}

void Parser::expect(Token t)
{
	Token result = accept(t);
	if (!result)
	{
		throw SyntaxErrorException(sourceName, currentLine, "Expected " + t.toString() + ", got " + curToken.toString());
	}
}

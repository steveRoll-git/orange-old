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

Value Parser::parseValue()
{
	Token lastTok = curToken;
	nextToken();

	if (lastTok.type == TokenType::LParen)
	{
		ConsCell* theList = parseList();
		expect(Token(TokenType::RParen));
		return Value(ValueType::List, theList);
	}
	else if (lastTok.type == TokenType::Number)
	{
		return Value(ValueType::Number, lastTok.number);
	}
	else if (lastTok.type == TokenType::Identifier)
	{
		if (lastTok.string == "nil")
		{
			return Value();
		}
		else
		{
			return Value(ValueType::Symbol, lastTok.string);
		}
	}
	else if (lastTok.type == TokenType::String)
	{
		return Value(ValueType::String, curToken.string);
	}

	throw SyntaxErrorException(sourceName, currentLine, "Did not expect " + curToken.toString() + " here");
}

ConsCell* Parser::parseList()
{
	ConsCell* first = nullptr;
	ConsCell* last = nullptr;

	while (curToken.type != TokenType::RParen)
	{
		if (last != nullptr && curToken.type == TokenType::Identifier && curToken.string == ".")
		{
			nextToken();
			last->cdr = parseValue();
			break;
		}

		ConsCell* newList = new ConsCell();

		newList->car = parseValue();

		if (first == nullptr)
		{
			first = newList;
			last = newList;
		}
		else
		{
			last->cdr = Value(ValueType::List, newList);
			last = newList;
		}
	}

	return (first == nullptr ? new ConsCell() : first);
}

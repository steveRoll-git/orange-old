#include "Token.h"

using namespace Orange::Lang;

const char* Token::getTypeName()
{
    switch (type)
    {
    case Orange::Lang::TokenType::Eof:
        return "Eof";
    case Orange::Lang::TokenType::Identifier:
        return "Identifier";
    case Orange::Lang::TokenType::Number:
        return "Number";
    case Orange::Lang::TokenType::String:
        return "String";
    case Orange::Lang::TokenType::LParen:
        return "LParen";
    case Orange::Lang::TokenType::RParen:
        return "RParen";
    case Orange::Lang::TokenType::Quote:
        return "Quote";
    default:
        return "???";
    }
}

std::string Token::toString()
{
    std::string result(getTypeName());
    if ((type == TokenType::Identifier || type == TokenType::String) && valueSet)
    {
        result.append(" \"");
        result.append(string);
        result.push_back('"');
    }
    else if (type == TokenType::Number)
    {
        result.push_back(' ');
        result.append(std::to_string(number));
    }
    return result;
}

Token::~Token()
{
    if ((type == TokenType::Identifier || type == TokenType::String) && valueSet)
    {
        string.~string();
    }
}
#include "Token.h"

using namespace Orange::Lang;

Token::~Token()
{
    if (type == TokenType::Identifier || type == TokenType::String)
    {
        ~value.string();
    }
}
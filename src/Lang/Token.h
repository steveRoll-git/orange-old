#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace Orange::Lang
{
    enum class TokenType
    {
        Eof,
        Identifier,
        Number,
        String,
        LParen,
        RParen,
        Quote
    };

    struct Token
    {
        TokenType type;

        union
        {
            std::string string;
            double number;
        };

        Token(TokenType _type) : type(_type) {};
        Token(TokenType _type, std::string _string) : type(_type), string(_string) {};
        Token(TokenType _type, double _number) : type(_type), number(_number) {};
        
        ~Token();
    };
} // namespace Orange

#endif // TOKEN_H

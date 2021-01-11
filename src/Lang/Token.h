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
        Quote,

        Invalid = -1
    };

    struct Token
    {
        TokenType type;

        union
        {
            std::string string;
            double number;
        };

        Token() : type(TokenType::Invalid) {};
        Token(TokenType _type) : type(_type) {};
        Token(TokenType _type, std::string _string) : type(_type), string(_string) {};
        Token(double _number) : type(TokenType::Number), number(_number) {};

        Token(const Token& other)
        {
            type = other.type;
            if (other.type == TokenType::Identifier || other.type == TokenType::String)
            {
                string = other.string;
            }
            else if (other.type == TokenType::Number)
            {
                number = other.number;
            }
        }

        void operator =(const Token& other)
        {
            type = other.type;
            if (other.type == TokenType::Identifier || other.type == TokenType::String)
            {
                string = other.string;
            }
            else if (other.type == TokenType::Number)
            {
                number = other.number;
            }
        }

        explicit operator bool() const
        {
            return type != TokenType::Invalid;
        }

        bool compareTo(Token& other)
        {
            return type == other.type;
        }

        const char* getTypeName();
        std::string toString();
        
        ~Token();
    };
} // namespace Orange

#endif // TOKEN_H

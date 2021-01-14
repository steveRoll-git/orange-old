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

        bool valueSet = false;

        Token() : type(TokenType::Invalid) {};
        Token(TokenType _type) : type(_type) {};
        Token(TokenType _type, std::string _string) : type(_type), string(_string), valueSet(true) {};
        Token(double _number) : type(TokenType::Number), number(_number), valueSet(true) {};

        void copyOther(Token& other)
        {
            type = other.type;
            if ((other.type == TokenType::Identifier || other.type == TokenType::String) && other.valueSet)
            {
                setValue(other.string);
            }
            else if (other.type == TokenType::Number && other.valueSet)
            {
                setValue(other.number);
            }
        }

        Token(Token& other)
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

        void operator =(Token& other)
        {
            copyOther(other);
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

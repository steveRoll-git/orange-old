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
        RParen
    };

    struct Token
    {
        TokenType type;

        union
        {
            std::string string;
            double number;
        } value;
        
        ~Token();
    };
} // namespace Orange

#endif // TOKEN_H

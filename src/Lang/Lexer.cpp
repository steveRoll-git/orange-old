#include "Lexer.h"

#include "SyntaxErrorException.h"

using namespace Orange::Lang;

bool isIdentifierChar(char c)
{
    return c != '(' && c != ')' && c != '\'' && c != '"' && c != ';' && !isspace(c);
}

Lexer::Lexer(std::istream& _codeStream, std::string& _sourceName) :
codeStream(_codeStream),
sourceName(_sourceName),
currentLine(1),
reachedEnd(false)
{
    advanceChar();
}

void Lexer::advanceChar()
{
    if (!reachedEnd)
    {
        codeStream.get(currentChar);
        if (currentChar == '\n')
        {
            currentLine++;
        }
        
        reachedEnd = codeStream.eof();
    }
}

Token Lexer::nextToken()
{
    while (!reachedEnd && (isspace(currentChar) || currentChar == ';'))
    {
        if (currentChar == ';')
        {
            //single line comment
            while (currentChar != '\n')
            {
                advanceChar();
            }
            
        }
        
        advanceChar();
    }
    
    if (reachedEnd)
    {
        return Token(TokenType::Eof);
    }
    
    if (currentChar == '(')
    {
        advanceChar();
        return Token(TokenType::LParen);
    }
    else if (currentChar == ')')
    {
        advanceChar();
        return Token(TokenType::RParen);
    }
    else if (currentChar == '\'')
    {
        advanceChar();
        return Token(TokenType::Quote);
    }
    else if (isdigit(currentChar) || (currentChar == '-' && isdigit(codeStream.peek())))
    {
        bool isNegative = false;
        if (currentChar == '-')
        {
            isNegative = true;
            advanceChar();
        }

        double number = parseNumber();

        if (isNegative)
        {
            number = -number;
        }

        return Token(number);
    }
    else if (currentChar == '"')
    {
        advanceChar();

        std::string contents = parseName(true);

        if (currentChar != '"')
        {
            throw SyntaxErrorException(sourceName, currentLine, std::string("unfinished string"));
        }

        advanceChar();

        return Token(TokenType::String, contents);
    }
    else
    {
        std::string contents = parseName();

        return Token(TokenType::Identifier, contents);
    }
    
}

std::string Lexer::parseName(bool allowSpace)
{
    std::string contents;

    while (!reachedEnd && (isIdentifierChar(currentChar) || (allowSpace && currentChar == ' ')))
    {
        contents.push_back(currentChar);
        advanceChar();
    }

    return contents;
}

double Lexer::parseNumber()
{
    std::string contents;

    while (!reachedEnd && (isalnum(currentChar) || currentChar == '.'))
    {
        contents.push_back(currentChar);
        advanceChar();
    }

    double result;

    try
    {
        result = stod(contents);
    }
    catch(const std::exception& e)
    {
        throw SyntaxErrorException(sourceName, currentLine, std::string("malformed number: ") + e.what());
    }
    

    return result;
}

bool Lexer::hasReachedEnd()
{
    return reachedEnd;
}

Lexer::~Lexer()
{
    
}

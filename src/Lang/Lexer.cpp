#include "Lexer.h"

using namespace Orange::Lang;

Lexer::Lexer(std::istream& _codeStream, std::string& _sourceName) :
codeStream(_codeStream),
sourceName(_sourceName),
currentLine(1)
{
    //ctor
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

Lexer::~Lexer()
{
    
}

#include "Lexer.h"

using namespace Orange::Lang;

Lexer::Lexer(std::istream& _codeStream) :
codeStream(_codeStream)
{
    //ctor
}

void Lexer::advanceChar()
{
    if (!reachedEnd)
    {
        codeStream.get(currentChar);
        reachedEnd = codeStream.eof();
    }
}

Lexer::~Lexer()
{
    
}

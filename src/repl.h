#include <iostream>
#include <sstream>

#include "./Parser.h" //put the ./ here because visual studio confused this with some MSVC parser file
#include "VM.h"
#include "Lang/SyntaxErrorException.h"
#include "RuntimeException.h"

using namespace std;
using namespace Orange;
using namespace Orange::Lang;

bool isEmpty(string& str)
{
	return str.find_first_not_of(" \t\n\v\f\r") == std::string::npos;
}

void repl()
{
	VM vm;

	while (true)
	{
		try
		{
			cout << "> ";

			string inputLine;
			getline(cin, inputLine);

			if (inputLine.length() == 0 || isEmpty(inputLine))
			{
				continue;
			}

			//cout << "line: " << inputLine << endl;

			stringstream str = stringstream(inputLine);

			Parser p(str, std::string("input"));

			Value* v = new Value(p.parseValue());

			Value evaluated = vm.evaluate(*v);

			cout << "= " << evaluated.toString() << endl;
		}
		catch (SyntaxErrorException& e)
		{
			cout << "Syntax error: " << endl << e.getFormattedError() << endl;
		}
		catch (RuntimeException& e)
		{
			cout << e.getFormattedError() << endl;
		}
	}
}

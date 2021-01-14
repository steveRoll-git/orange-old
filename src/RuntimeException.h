#pragma once

#include <exception>
#include <string>

namespace Orange
{
	class RuntimeException : public std::exception
	{
	private:
		std::string message;
	public:
		RuntimeException(std::string& _message) : message(_message) {}

		std::string getFormattedError()
		{
			return "Runtime error: " + message;
		}

		const char* what() const throw ()
		{
			return "Runtime error";
		}
	};
}
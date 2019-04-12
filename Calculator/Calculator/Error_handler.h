#pragma once
#include <string>
#include <exception>

class Error_handler :public std::exception
{
	std::string _error;
public:
	const char* what() const throw()
	{
		return _error.c_str();
	}
	Error_handler(const std::string &error) :_error(error) {}
};

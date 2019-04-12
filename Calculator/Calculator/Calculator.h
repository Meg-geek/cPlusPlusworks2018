#pragma once
#include "Context.h"
#include "Error_handler.h"
#include "Command.h"
class Calculator
{
	Context context;
	void find_and_do_command(const std::string &line);
	const std::string find_argument(const std::string &line, size_t pos); //оставить, аргументы будут в векторе/листе
	std::string find_command(const std::string &line);
public:
	Calculator() {};
	void run(std::istream &in); //убрать конструкторы, запуск с метода
};


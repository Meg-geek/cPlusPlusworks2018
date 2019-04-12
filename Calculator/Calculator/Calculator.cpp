#include "Calculator.h"
#include "Factories.h"

#include <vector>
#include <iostream>
#include <string>


void Calculator::run(std::istream &in)
{
	std::string line;
	while (std::getline(in, line))
	{
		if (!line.empty() && line[0] != '#')
			find_and_do_command(line);
	}
}

std::string Calculator::find_command(const std::string &line)
{
	size_t command_pos = line.find(' ');
	if (command_pos > line.length())
		return line;
	std::string command = line.substr(0, command_pos);
	return command;
}

void Calculator::find_and_do_command(const std::string &line)
{
	std::vector<std::string> arguments;
	std::string command_name = find_command(line); 
	size_t i = command_name.length() + 1;
	std::string argument = find_argument(line, i);
	while (!argument.empty())
	{
		arguments.push_back(argument);
		i = i + argument.length() + 1; 
		argument = find_argument(line, i);
	}
	try {
		std::auto_ptr<Command> command( CommandFactory::instance().getCommand(command_name)); //????
			command->do_command(context, arguments);
	}
	catch (Error_handler &error)
	{
		std::cout << error.what() << std::endl;
	}
}

const std::string Calculator::find_argument(const std::string &line, size_t pos)
{
	std::string arg = "";
	if ( pos < line.length() )
	{
		arg = line.substr(pos, line.length());
		size_t end_of_argument = arg.find(' ');
		if ( end_of_argument < arg.length() ) //if there's ' '
		{
			std::string arg_1 = arg.substr(0, end_of_argument);
			return arg_1;
		}
		return arg;
	}
	return arg;
}

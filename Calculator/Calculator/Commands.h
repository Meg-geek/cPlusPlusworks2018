#pragma once
#include "Command.h"
#include "Context.h"
#include <cmath>
#include <iostream>
#include <sstream>

double string_to_double(const std::string &line);


class POP_command : public Command
{
public:
	void do_command (Context &context, const std::vector <std::string> &arguments)
	{
		if (context.empty())
			throw Error_handler("POP ERROR. The stack is empty.");
		context.pop();
	}
};

class PUSH_command : public Command
{
public:
	void do_command(Context &context, const std::vector <std::string> &arguments)
	{
		if (arguments.size() < 1)
			throw Error_handler("PUSH ERROR. No arguments for PUSH.");
		double numb = string_to_double(arguments[0]);
		std::string parameter = arguments[0];
		if (numb != 0)
			context.push(numb);
		else
			if (numb == 0 && parameter[0] != '0')
				context.push(parameter);
			else
				context.push(numb);
	}
};

class ADD_command : public Command
{
public:
	void do_command(Context &context, const std::vector <std::string> &arguments)
	{
		if (context.size() < 2)
			throw Error_handler("Stack doesn't have two arguments for +.");
		double a = context.top();
		context.pop();
		double numb = context.top();
		context.pop();
		context.push(a + numb);
	}
};

class SUB_command : public Command
{
public:
	void do_command(Context &context, const std::vector <std::string> &arguments)
	{
		if (context.size() < 2)
			throw Error_handler("Stack doesn't have two arguments for -.");
		double a = context.top();
		context.pop();
		double numb = context.top();
		context.pop();
		context.push(a - numb);
	}
};

class MUL_command : public Command
{
public:
	void do_command(Context &context, const std::vector <std::string> &arguments)
	{
		if (context.size() < 2)
			throw Error_handler("Stack doesn't have two arguments for *.");
		double a = context.top();
		context.pop();
		double numb = context.top();
		context.pop();
		context.push(a * numb);
	}
};

class DIV_command : public Command
{

public:
	void do_command(Context &context, const std::vector <std::string> &arguments)
	{
		if(context.size() < 2)
			throw Error_handler("Stack doesn't have two arguments for /.");
		double a = context.top();
		context.pop();
		double numb = context.top();
		if (numb == 0)
		{
			context.push(a);
			throw Error_handler("Division by zero.");
		}
		context.pop();
		context.push(a / numb);
	}
};

class SQRT_command : public Command
{
public:
	void do_command(Context &context, const std::vector <std::string> &arguments)
	{
		if (context.empty())
			throw Error_handler("Stack is empty.");
		double a = sqrt(context.top());
		context.pop();
		context.push(a);
	}
};

class DEFINE_command : public Command
{
public:
	void do_command(Context &context, const std::vector <std::string> &arguments)
	{
		if (arguments.size() < 2)
			throw Error_handler("DEFINE doesn't have enough arguments.");
		context.define(arguments[0], string_to_double( arguments[1]));
	}
};

class PRINT_command : public Command
{
public:
	void do_command(Context &context, const std::vector <std::string> &arguments)
	{
		if (context.empty())
			throw Error_handler("Stack is empty.");
		double numb = context.top();
		std::cout << numb << std::endl;
	}
};




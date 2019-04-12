#pragma once
#include "Context.h"
#include "Error_handler.h"
#include <vector>

class Command
{
public:
	virtual void do_command(Context &context, const std::vector <std::string> &arguments) = 0;
	virtual ~Command() = default;

};


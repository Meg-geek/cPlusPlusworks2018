#pragma once
#include "Command.h"
#include <map>
class ComandsCreator
{
public:
	virtual Command* makeCommand() = 0;
	virtual ~ComandsCreator() = default;
};

class CommandFactory {
	CommandFactory() = default;
	std::map<std::string, ComandsCreator*> commands;
public:
	static CommandFactory& instance() {
		static CommandFactory f;
		return f;
	}
	~CommandFactory()
	{
		for (auto &item : commands) {
			delete item.second;
		}
	}
	Command *getCommand(const std::string &name) {
		if (commands[name] == nullptr)
			throw Error_handler("Command doesn't exist.");
		Command *command = commands[name]->makeCommand();
		return command;
	}

	void registerComand(const std::string &name, ComandsCreator*creator)
	{
		commands[name] = creator;
	}
};


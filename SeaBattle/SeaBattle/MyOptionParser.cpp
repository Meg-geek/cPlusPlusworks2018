#include "MyOptionParser.h"
#include "optionparser.h"
#include <vector>
#include <iostream>

struct Arg : public option::Arg
{
	static option::ArgStatus String(const option::Option& option, bool msg)
	{
		if (option.arg)
			return option::ARG_OK;
		return option::ARG_ILLEGAL;
	}

	static option::ArgStatus Numeric(const option::Option& option, bool msg)
	{
		char* endptr = 0;
		if (option.arg != 0 && strtol(option.arg, &endptr, 10)) {};
		if (endptr != option.arg && *endptr == 0)
			return option::ARG_OK;
		return option::ARG_ILLEGAL;
	}
};

enum  optionIndex { UNKNOWN, HELP, COUNT, FIRST, SECOND };
const option::Descriptor usage[] =
{

	{ UNKNOWN, 0, "", "",option::Arg::None, "Hello! This is the game SeaBattle. This are the arguments you can use. "
	"Options:" },
	{ HELP, 0,"h", "help",option::Arg::None, "  --help, -h  \tPrint usage and exit." },
	{ COUNT, 2,"c","count", Arg::Numeric, "  --count=<arg>, -c <arg>  \tAmount of rounds in the game." },
	{ FIRST, 0,"f","first", Arg::String, "  --first[=<arg>], -f [<arg>]  \tThe type of the first player. It can be random, real or optimal" },
	{ SECOND, 0,"s","second",Arg::String, "  --second[=<arg>], -s [<arg>] \tThe type of the second player. It can be random, real or optimal" },
};

void printUsage()
{
	std::cout <<  "Hello! This is the game SeaBattle. This are the arguments you can use. "<<"Options:"<<std::endl;
	std::cout << "  --count=<arg>, -c <arg>  \tAmount of rounds in the game." << std::endl;
	std::cout << "  --first[=<arg>], -f [<arg>]  \tThe type of the first player. It can be random, real or optimal" << std::endl;
	std::cout << "  --second[=<arg>], -s [<arg>] \tThe type of the second player. It can be random, real or optimal" << std::endl;
}

Arguments MyOptionParser::get_arguments(int argc, char ** argv)
{
	Arguments arguments;
	argc -= (argc>0); argv += (argc>0); // skip program name argv[0] if present
	option::Stats  stats(usage, argc, argv);
	std::vector<option::Option> options(stats.options_max);
	std::vector<option::Option> buffer(stats.buffer_max);
	option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);

	if (parse.error())
		return arguments;

	if (argc == 0)
		return arguments;

	if (options[HELP]) {
		printUsage();
		arguments.count = 0;
		return arguments;
	}

	for (int i = 0; i < parse.optionsCount(); ++i)
	{
		option::Option& opt = buffer[i];
		switch (opt.index())
		{
		case HELP:
			// not possible, because handled further above and exits the program
		case FIRST:
			if (opt.arg)
				arguments.first_gamer = opt.arg;
			else
				std::cout << "--first of -f argument error" << std::endl;
			break;
		case SECOND:
			if (opt.arg)
				arguments.second_gamer = opt.arg;
			else
				std::cout << "--second or -s argument error" << std::endl;
			break;
		case COUNT:
			if (opt.arg)
				arguments.count = atoi(opt.arg);
			break;
		case UNKNOWN:
			// not possible because Arg::Unknown returns ARG_ILLEGAL
			// which aborts the parse with an error
			break;
		}
	}
	return arguments;
}

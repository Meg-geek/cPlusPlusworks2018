#include "Commands.h"
#include "ComandsFactory.h"
#include "Factories.h"

namespace {

	bool registerCommands() {
		CommandFactory::instance().registerComand("+", new Factory_ADD());
		CommandFactory::instance().registerComand("-", new Factory_SUB());
		CommandFactory::instance().registerComand("POP", new Factory_POP());
		CommandFactory::instance().registerComand("PUSH", new Factory_PUSH());

		CommandFactory::instance().registerComand("/", new Factory_DIV());
		CommandFactory::instance().registerComand("*", new Factory_MUL());
		CommandFactory::instance().registerComand("DEFINE", new Factory_DEFINE());
		CommandFactory::instance().registerComand("PRINT", new Factory_PRINT());

		CommandFactory::instance().registerComand("SQRT", new Factory_SQRT());
		return true;
	}
	bool b = registerCommands();
}

double string_to_double(const std::string &line)
{
	std::istringstream s(line);
	double x;
	if (!(s >> x))
		return 0;
	return x;
}

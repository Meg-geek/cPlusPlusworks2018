#include <iostream>
#include "Calculator.h"
#include <fstream>
int main(int argc, char **argv)
{
	Calculator calc;
	if (argc >= 1)
	{
		std::ifstream input_file("input.txt");
		calc.run(input_file);
	}
	else
	{
		calc.run(std::cin);
	}
	Calculator calc2;
	calc2.run(std::cin);
	return 0;
}
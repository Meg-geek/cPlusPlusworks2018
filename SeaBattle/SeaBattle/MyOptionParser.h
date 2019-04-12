#pragma once
#include <string>
#include <iostream>

struct Arguments
{
	int count;
	std::string first_gamer, second_gamer;
	Arguments():count(1), first_gamer("random"), second_gamer("random") {}
};
class MyOptionParser
{
public:
	MyOptionParser() {}
	~MyOptionParser() {}
	Arguments get_arguments(int argc, char **argv);
};


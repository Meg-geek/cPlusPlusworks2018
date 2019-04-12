#include "MyOptionParser.h"
#include "SeaBattle.h"

int main(int argc, char **argv)
{
	MyOptionParser parser;
	SeaBattle first(parser.get_arguments(argc, argv));
	first.start();
	return 0;
}





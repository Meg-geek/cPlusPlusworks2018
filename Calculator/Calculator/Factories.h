#pragma once
#include "ComandsFactory.h"
#include "Commands.h"
class Factory_POP : public ComandsCreator
{
public:
	Command* makeCommand() { return new POP_command(); }
};

class Factory_PUSH : public ComandsCreator
{
public:
		Command* makeCommand() { return new PUSH_command(); }
};

class Factory_ADD : public ComandsCreator
{
public:
	Command* makeCommand() { return new ADD_command(); }
};

class Factory_SUB : public ComandsCreator
{
public:
	Command* makeCommand() { return new SUB_command(); }
};

class Factory_MUL : public ComandsCreator
{
public:
	Command* makeCommand() { return new MUL_command(); }
};

class Factory_DIV : public ComandsCreator
{
public:
	Command* makeCommand() { return new DIV_command(); }
};

class Factory_SQRT : public ComandsCreator
{
public:
	Command* makeCommand() { return new SQRT_command(); }
};

class Factory_DEFINE : public ComandsCreator
{
public:
	Command* makeCommand() { return new DEFINE_command(); }
};

class Factory_PRINT : public ComandsCreator
{
public:
	Command* makeCommand() { return new PRINT_command(); }
};
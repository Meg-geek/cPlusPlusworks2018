#pragma once
#include "Gamers.h"
#include "GamersCreator.h"

class Factory_Real_Gamer : public GamersCreator
{
public:
	Gamer* makeGamer(GameModel *model, ConsoleView *view) { return new RealGamer(model, view); }
};

class Factory_Random_Gamer : public GamersCreator
{
public:
	Gamer* makeGamer(GameModel *model, ConsoleView *view) { return new RandomGamer(model, view); }
};

class Factory_Optimal_Gamer : public GamersCreator
{
public:
	Gamer* makeGamer(GameModel *model, ConsoleView *view) { return new OptimalGamer(model, view); }
};

#pragma once
#include <map>
#include "GamersFactories.h"
#include "Gamer.h"
#include "whats_wrong.h"



class GamersFactory {
	GamersFactory() = default;
	std::map<std::string, GamersCreator*> gamers;
	GameModel *_model;
	ConsoleView *_view;
public:
	~GamersFactory()
	{
		for (auto &item : gamers) {
			delete item.second;
		}
	}
	GamersFactory(GameModel *model, ConsoleView *view):_model(model), _view(view)
	{
		gamers["real"] = new Factory_Real_Gamer();
		gamers["random"] = new Factory_Random_Gamer();
		gamers["optimal"] = new Factory_Optimal_Gamer();
	}
	Gamer *getGamer(const std::string &name) {
		if (gamers[name] == nullptr)
			throw whats_wrong("Wrong argument for first or second gamer.");
		Gamer *gamer = gamers[name]->makeGamer(_model, _view);
		return gamer;
	}
};
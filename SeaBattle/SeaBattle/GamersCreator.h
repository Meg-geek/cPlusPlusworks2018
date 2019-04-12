#pragma once
class Gamer;

class GamersCreator {
public:
	virtual Gamer* makeGamer(GameModel *model, ConsoleView *view) = 0;
	virtual ~GamersCreator() = default;
};
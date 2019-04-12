#pragma once
class GameModel;
class ConsoleView;

class Gamer
{
public:
	GameModel *_model;
	ConsoleView *_view;
	Gamer(GameModel *model, ConsoleView *view)
	{
		_model = model;
		_view = view;
	}
	virtual ~Gamer() {}
	virtual void set_ship() = 0;
	virtual void make_move() = 0;
};


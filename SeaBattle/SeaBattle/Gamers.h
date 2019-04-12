#pragma once
#include "Gamer.h"
#include "Field.h"
class GameModel;

class RealGamer:public Gamer
{
	bool check_coord(const coord &first, const coord &second);
	void _set_ship();
	bool _make_move();
public:
	virtual void set_ship();
	virtual void make_move();
	RealGamer(GameModel *model, ConsoleView *view);
	~RealGamer() {}
};

class OptimalGamer :public Gamer
{
	void set_smart_ship_1();
	void set_smart_ship_2();
	void set_smart_ship_3();
	size_t field_size;
	int x, y, begin_x, begin_y;
	bool _rand;
	bool is_in_field();
	bool _make_move();
	void change_x_y();
	void change_x_y_2();
	void check();
	bool _make_random_move();
	bool clever_move();
	void change() { x = begin_x = 0; y = begin_y = 0;  }
public:
	virtual void set_ship();
	OptimalGamer(GameModel *model, ConsoleView *view);
	virtual void make_move();
	~OptimalGamer() { }
};

class RandomGamer :public Gamer
{
	size_t field_size;
	bool _make_move();
	void _set_ship(size_t ship_size);
public:
	RandomGamer(GameModel *model, ConsoleView *view);
	virtual void set_ship();
	virtual void make_move();
	~RandomGamer() {}
};


#pragma once
#include "Observer.h"
#include "GameModel.h"

void delete_array(unsigned char**array, size_t size);

class ConsoleView:public Observer
{
	GameModel *_model;
	size_t width, height;
	void set_width_and_hight();
	void draw_top();
	unsigned char _wall;
	void draw_field();
	int _print_gamer;
	void print_arrays(unsigned char **array_1, unsigned char **array_2, size_t size);
public:
	ConsoleView(GameModel *model):_wall(177)
	{
		_model = model;
		_model->addObserver(this);
		set_width_and_hight();
	}
	~ConsoleView();
	void set_print_gamer(int print_gamer)
	{
		_print_gamer = print_gamer;
	}
	virtual void update() 
	{
		system("cls");
		draw_top();
		draw_field();
	}
	virtual void announce(const std::string &announcment);
	virtual void announce_winners(const std::vector <int> &win_vec);
};


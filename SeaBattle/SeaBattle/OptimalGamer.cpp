#include "Gamers.h"
#include "GameModel.h"
#include <ctime>

OptimalGamer::OptimalGamer(GameModel * model, ConsoleView *view) :Gamer(model, view), x(1), y(0), _rand(false), begin_x(1), begin_y(0)
{
	field_size = _model->get_field_size();
}

void OptimalGamer::make_move()
{
	_model->change_error_flag(false);
	if (!_rand)
	{
		while (!_make_move() && _model->game_continue())
		{
		}
	}
	else
		while(!_make_random_move() && _model->game_continue())
		{ }
}

bool OptimalGamer::_make_move()
{
	int result = _model->make_move(x, y);
	if (result == 0)
	{
		change_x_y();
		return true;
	}
	if (result == 2)
	{
		change_x_y();
		return false;
	} 
	return clever_move();
}

bool OptimalGamer::clever_move()
{
	int result = 2;
	bool ready = true;
	for (int i = -1; (result != 0) && i <=1 && ready; i++)
	{
		for (int j = -1; (result != 0) && j <= 1 && ready; j++)
		{
			if (i == 0 || j == 0)
			{
				result = _model->make_move(x + i, y + j);
				ready = _model->game_continue();
			}
		}
	}
	if (result == 0)
		return true;
	return false;
}

void OptimalGamer::check()
{
	uchar **enemy_field = _model->get_enemy_field();
	bool right = false;
	if (is_in_field() && enemy_field[x][y] == '?')
	{
		while (!right)
		{
			bool next = true;
			for (int i = -1; i <= 1 && next;i++)
				for (int j = -1; j <= 1 && next; j++)
				{
					x += i;
					y += j;
					if (is_in_field())
					{
						if (enemy_field[x][y] == '#')
						{
							next = false;
							x -= i;
							y -= j;
							change_x_y_2();
						}
					}
					if (next)
					{
						x -= i;
						y -= j;
					}
				}
			if (next)
				right = true;
		}
	}
	for (size_t i = 0; i < field_size; i++)
		delete[] enemy_field[i];
	delete enemy_field;
}

bool OptimalGamer::_make_random_move()
{
	check();
	int result = _model->make_move(x, y);
	if (result == 0)
	{
		change_x_y_2();
		return true;
	}
	if (result == 2)
	{
		change_x_y_2();
		return false;
	}
	return clever_move();
}

void OptimalGamer::change_x_y()
{
	x--;
	y++;
	if (!is_in_field())
	{
		if (begin_y == 8 && begin_x == 9)
		{
			_rand = true; //прошли все диагонали
			change(); //перешли на другие
		}
		else
		{
			if (begin_x == 9)
			{
				begin_y += 2;
				x = begin_x;
				y = begin_y;
			}
			else
			{
				begin_x += 2;
				x = begin_x;
				y = begin_y;
			}
		}
	}
}

void OptimalGamer::change_x_y_2()
{
	x--;
	y++;
	if (!is_in_field())
	{
			if (begin_x == 8)
			{
				begin_y = 1;
				x = begin_x = 9;
				y = begin_y;
			}
			else
				if (begin_x == 9)
				{
					begin_y += 2;
					y = begin_y;
					x = begin_x;
				}
				else
			{
				begin_x += 2;
				x = begin_x;
				y = begin_y;
			}
	}
}

bool OptimalGamer::is_in_field()
{
	return (static_cast<size_t>(x) >= 0 && static_cast<size_t>(x) < field_size && static_cast<size_t>(y) >= 0 && static_cast<size_t>(y) < field_size);
}

void OptimalGamer::set_ship()
{
	_model->change_error_flag(false);
	srand(static_cast<unsigned int>(time(0)));
	int strategy = 1 + rand() % 3;//установим стратегию
	if (strategy == 1)
		set_smart_ship_1();
    else
		if (strategy == 2)
			set_smart_ship_2();
		else
			set_smart_ship_3();
	//пока не заполнили, ставим рандомом, не забывая устанавливать игрока
	while (!_model->field_is_ready_to_start()) //returns true if field is ready
	{
		srand(static_cast<unsigned int>(time(0)));
		int x = rand() % field_size, y = rand() % field_size;
		_model->_set_ship(coord(x, y));
	}
}

void OptimalGamer::set_smart_ship_1()
{
	_model->_set_ship(coord(0, 0), coord(3, 0), direction::VERTICALLY);
	_model->_set_ship(coord(5, 0), coord(6, 0), direction::VERTICALLY);
	_model->_set_ship(coord(8, 0), coord(9, 0), direction::VERTICALLY);

	_model->_set_ship(coord(0, 2), coord(2, 2), direction::VERTICALLY);
	_model->_set_ship(coord(4, 2), coord(6, 2), direction::VERTICALLY);
	_model->_set_ship(coord(8, 2), coord(9, 2), direction::VERTICALLY);
}

void OptimalGamer::set_smart_ship_2()
{
	_model->_set_ship(coord(0, 0), coord(3, 0), direction::VERTICALLY);
	_model->_set_ship(coord(5, 0), coord(7, 0), direction::VERTICALLY);
	_model->_set_ship(coord(9, 0), coord(9, 1), direction::HORIZONTALLY);

	_model->_set_ship(coord(0, 2), coord(0, 4), direction::HORIZONTALLY);
	_model->_set_ship(coord(0, 6), coord(0, 7), direction::HORIZONTALLY);
	_model->_set_ship(coord(0, 9), coord(1, 9), direction::VERTICALLY);
}

void OptimalGamer::set_smart_ship_3()
{
	_model->_set_ship(coord(0, 0), coord(3, 0), direction::VERTICALLY);
	_model->_set_ship(coord(5, 0), coord(6, 0), direction::VERTICALLY);
	_model->_set_ship(coord(8, 0), coord(9, 0), direction::VERTICALLY);

	_model->_set_ship(coord(0, 9), coord(2, 9), direction::VERTICALLY);
	_model->_set_ship(coord(4, 9), coord(5, 9), direction::VERTICALLY);
	_model->_set_ship(coord(7, 9), coord(9, 9), direction::VERTICALLY);
}


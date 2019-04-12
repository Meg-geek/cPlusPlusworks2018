#include "Gamers.h"
#include "Field.h"
#include <ctime>
#include "GameModel.h"
#include "ConsoleView.h"

RandomGamer::RandomGamer(GameModel * model, ConsoleView *view) : Gamer(model, view)
{
	field_size = _model->get_field_size();
}

void RandomGamer::_set_ship (size_t ship_size)
{
	srand(static_cast<unsigned int>(time(0)));
	int x = rand() % field_size, y = rand() % field_size;
	if (ship_size == 1)
		_model->_set_ship(coord(x, y));
	else
	{
		int dir = 1 + rand() % 4;
		switch (dir)
		{
		case 1:
		{
			_model->_set_ship(coord(x - ship_size + 1, y), coord(x, y), direction::VERTICALLY);
			break;
		}
		case 2:
		{
			_model->_set_ship(coord(x, y), coord(x, y + ship_size - 1), direction::HORIZONTALLY);
			break;
		}
		case 3:
		{
			_model->_set_ship(coord(x, y), coord(x + ship_size - 1, y), direction::VERTICALLY);
			break;
		}
		default:
		{
			_model->_set_ship(coord(x, y - ship_size + 1), coord(x, y), direction::HORIZONTALLY);
			break;
		}
		}
	}
}

void RandomGamer::set_ship()
{
	_model->change_error_flag(false);
	for (size_t i = 4; i >= 1; i--)
	{
		_set_ship(i);
	}
	for (size_t i = 3; i >= 1; i--)
	{
		_set_ship(i);
	}
	for (size_t i = 2; i >= 1; i--)
	{
		_set_ship(i);
	}
}

/*returns true if move is made*/
bool RandomGamer:: _make_move()
{
	srand(static_cast<unsigned int>(time(0)));
	size_t x = rand() % field_size, y = rand() % field_size;
	int result = _model->make_move(x, y);
	if (result == 0)
		return true;
	return false;
}

void RandomGamer::make_move()
{
	_model->change_error_flag(false);
	while (!_make_move() && _model->game_continue())
	{

	}
}

#include "Gamers.h"
#include "whats_wrong.h"
#include "ConsoleView.h"
#include <string>
#include <iostream>

void get_coord(const std::string &line, std::vector <coord> &coord_vec)
{
	for (size_t i = 0; i < line.length(); i++)
	{
		if (line[i] != ' ') //если в строке пошла координата, сначала цифра
		{
			int numb = 0;
			numb = line[i] - '1';
			if (line[i + 1] == '0')
			{
				numb = 9;
				i++;
			}
			i++;
			if (i < line.length())
			{
				int y = line[i] - 'A';
				coord_vec.push_back(coord(numb, y));
			}
		}
	}
}

RealGamer::RealGamer(GameModel * model, ConsoleView *view) :Gamer(model, view)
{

}

void RealGamer::set_ship()
{
	try
	{
		_set_ship();
	}
	catch (whats_wrong &problem)
	{
		_view->announce(problem.what());
	}
}


void RealGamer::_set_ship()
{
	_model->change_error_flag(true);
	_view->announce("Enter the first and the last coordinate to set ship or only one coordinate. One space between coordinates. Like : 1A 1B"); 
	std::string line;
	std::getline(std::cin, line);
	std::vector <coord> coord_vec;
	get_coord(line, coord_vec);

	if (coord_vec.size() < 1)
		throw whats_wrong("Coordinate error.");

	if (coord_vec.size() == 1)
		_model->_set_ship(coord_vec[0]);

	if (coord_vec.size() > 1)
	{
		if (check_coord(coord_vec[0], coord_vec[1]))
			throw whats_wrong("Coordinate error.");
		if (coord_vec[0].x == coord_vec[1].x) //if 'h'
		{
			if (coord_vec[0].y > coord_vec[1].y)
				std::swap(coord_vec[0], coord_vec[1]);
			_model->_set_ship(coord_vec[0], coord_vec[1], direction::HORIZONTALLY);
		}
		else //if 'v'
		{
			if (coord_vec[0].x > coord_vec[1].x)
				std::swap(coord_vec[0], coord_vec[1]);
			_model->_set_ship(coord_vec[0], coord_vec[1], direction::VERTICALLY);
		}
	}
}

/*returns true if move is made*/
bool RealGamer::_make_move()
{
	_view->announce("Now make a move. Write coordinate like 1A.");
	std::string line;
	std::getline(std::cin, line);
	std::vector <coord> coord_vec;
	get_coord(line, coord_vec);
	if (coord_vec.size() < 1)
	{
		_view->announce("No coordinate.");
		return false;
	}
	int result = _model->make_move(coord_vec[0].x, coord_vec[0].y);
	if (result == 0)
		return true;
	return false;
}

void RealGamer::make_move()
{
	_model->change_error_flag(true);
	while (!_make_move() && _model->game_continue())
	{

	}
}

/*returns true if coordinates are NOT OK*/
bool RealGamer::check_coord(const coord & first, const coord & second)
{
	if (first.x == second.x && abs(first.y - second.y) <= 4)
		return false;
	if (first.y == second.y && abs(first.x - second.x) <= 4)
		return false;
	return true;
}
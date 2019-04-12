#include "Gamers.h"
#include "Field.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include "whats_wrong.h"
#include <cmath>
#include <algorithm>
#include "GameModel.h"
#include <vector>

void get_coord(const std::string &line, std::vector <coord> &coord_vec )
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

OptimalGamer::OptimalGamer(GameModel * model) :Gamer(model)
{
	field_size = _model->get_field_size();
}

RandomGamer::RandomGamer(GameModel * model) : Gamer(model)
{
	field_size = _model->get_field_size();
}

/*void RandomGamer::set_ship()
{
	//set_gamer();
	_model->change_error_flag(false);
	srand(static_cast<unsigned int>(time(0)));
	set_four();
	set_gamer();
	int x = rand() % field_size, y = rand() % field_size;
	_model->_set_ship(coord(x, y));
	
}*/

void RandomGamer::set_ship()
{
	set_gamer();
	_model->change_error_flag(false);
	srand(static_cast<unsigned int>(time(0)));
	int ship_size = 1 + rand() % 4;
	int x = rand() % field_size, y = rand() % field_size;
	if (ship_size == 1)
		_model->_set_ship(coord(x,y));
	else
	{
		int dir = 1 + rand() % 4;
		switch (dir)
		{
		case 1:
		{
			_model->_set_ship(coord(x-  ship_size + 1, y), coord(x, y), 'v');
			break;
		}
		case 2:
		{
			_model->_set_ship(coord(x, y), coord(x, y + ship_size - 1), 'h');
			break;
		}
		case 3:
		{
			_model->_set_ship(coord(x, y), coord(x + ship_size - 1 , y), 'v');
			break;
		}
		default:
		{
			_model->_set_ship(coord(x, y - ship_size + 1), coord(x, y), 'h');
			break;
		}
		}
	}
}

void OptimalGamer::set_ship()
{
	set_gamer();
	_model->change_error_flag(false);
	srand(static_cast<unsigned int>(time(0)));
	int strategy = 1 + rand() % 3;//установим стратегию
	/*if (strategy == 1)
		set_smart_ship_1();
	else
		if (strategy == 2)
			set_smart_ship_2();
		else
			set_smart_ship_3();*/
	set_smart_ship_1();
	//пока не заполнили, ставим рандомом, не забывая устанавливать игрока
	set_gamer();
	while (!_model->field_is_ready_to_start()) //returns true if field is ready
	{
		srand(static_cast<unsigned int>(time(0)));
		int x = rand() % field_size, y = rand() % field_size;
		_model->_set_ship(coord(x, y));
		set_gamer();
	}
}

void OptimalGamer::set_smart_ship_1()
{
	_model->_set_ship(coord(0, 0), coord(3, 0), 'v');
	set_gamer();
	_model->_set_ship(coord(5, 0), coord(6, 0), 'v');
	set_gamer();
	_model->_set_ship(coord(8, 0), coord(9, 0), 'v');

	set_gamer();
	_model->_set_ship(coord(0, 2), coord(2, 2), 'v');
	set_gamer();
	_model->_set_ship(coord(4, 2), coord(6, 2), 'v');
	set_gamer();
	_model->_set_ship(coord(8, 2), coord(9, 2), 'v');
}

void OptimalGamer::set_smart_ship_2()
{

}

void OptimalGamer::set_smart_ship_3()
{

}

RealGamer::RealGamer(GameModel * model):Gamer(model)
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
		std::cout << problem.what() << std::endl;
	}
}

void RealGamer::_set_ship()
{
	set_gamer();
	_model->change_error_flag(true);
	std::cout << "Enter the first and the last coordinate to set ship or only one coordinate. One space between coordinates. Like : 1A 1B" << std::endl;
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
			_model->_set_ship(coord_vec[0], coord_vec[1], 'h');
		}
		else //if 'v'
		{
			if (coord_vec[0].x > coord_vec[1].x)
				std::swap(coord_vec[0], coord_vec[1]);
			_model->_set_ship(coord_vec[0], coord_vec[1], 'v');
		}
	}
}


/*void RealGamer::set_ship()
{
	set_gamer();
	_model->change_error_flag(true);
	std::cout << "Enter the first and the last coordinate to set ship or only one coordinate. One space between coordinates. Like : 1A 1B" << std::endl;
	std::string line;
	std::getline(std::cin, line);
	if (line.length() < 3)
	{
		_model->_set_ship(coord(line[0] - '1', line[1] - 'A'));
	}
	else
	{
		if (line.length() < 5)
			throw whats_wrong("Coordinate error.");
		else
		{
			coord first(line[0] - '1', line[1] - 'A'), second(line[3] - '1', line[4] - 'A');
			if (check_coord(first, second))
				throw whats_wrong("Coordinate error.");
			if (first.x == second.x) //if 'h'
			{
				if (first.y > second.y)
					std::swap(first, second);
				_model->_set_ship(first, second, 'h');
			}
			else //if 'v'
			{
				if (first.x > second.x)
					std::swap(first, second);
				_model->_set_ship(first, second, 'v');
			}
		}
			
	}
}*/


/*returns true if coordinates are NOT OK*/
bool RealGamer::check_coord(const coord & first, const coord & second)
{
	if (first.x == second.x && abs(first.y - second.y) <= 4)
		return false;
	if (first.y == second.y && abs(first.x - second.x) <= 4)
		return false;
	return true;
} 

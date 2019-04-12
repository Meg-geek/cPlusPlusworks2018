#include "GameModel.h"
#include "whats_wrong.h"
#include <iostream>
#include "ConsoleView.h"

bool GameModel::field_is_ready_to_start() //returns true if field is ready
{
	if (current_gamer == 1)
		return first_field->is_ready();
	return second_field->is_ready();
}

bool GameModel::game_continue()
{
	return (first_field->ready_to_continue() && second_field->ready_to_continue());
}

std::vector<std::vector<size_t>> GameModel::get_statistics()
{
	std::vector<std::vector<size_t>> stat;
	stat.push_back(first_field->get_statistics());
	stat.push_back(second_field->get_statistics());
	return stat;
}

int GameModel::winner()
{
	if (first_field->ready_to_continue() && !second_field->ready_to_continue())
		return 1;
	return 2;
}

void GameModel::_set_ship(const coord & one_coord)
{
	bool condition = true;
	try
	{
		if (current_gamer == 1)
			first_field->set_ship(one_coord);
		if (current_gamer == 2)
			second_field->set_ship(one_coord);
	}
	catch (whats_wrong &problem)
	{
		if (error_flag)
			_view->announce(problem.what());
		condition = false;
	}
	if (condition && current_gamer == 1) notifyUpdate();
}

void GameModel::_set_ship(const coord & begin_coord, const coord & end_coord, direction dir)
{
	bool condition = true;
	try
	{
		if (current_gamer == 1)
			first_field->set_ship(begin_coord, end_coord, dir);
		if (current_gamer == 2)
			second_field->set_ship(begin_coord, end_coord, dir);
	}
	catch (whats_wrong &problem)
	{
		if (error_flag)
			_view->announce(problem.what());//std::cout << problem.what() << std::endl;
		condition = false;
	}
	if (condition && current_gamer == 1) notifyUpdate();
}

uchar ** GameModel::get_my_field()
{
	if (current_gamer == 1)
	{
		return get_first_field();
	}
	if (current_gamer == 2)
	{
		return get_second_field();
	}
	return nullptr;
}

uchar ** GameModel::get_enemy_field()
{
	if (current_gamer == 1)
	{
		return get_second_progress_field();
	}
	if (current_gamer == 2)
	{
		return get_first_progress_field();
	}
	return nullptr;
}


/*
0 - ход совершен, больше нельзя
1 - ход совершен, можно еще один
2 - ход не был совершен по каким-то причинам(возмoжен вывод на консоль)
*/
int GameModel::make_move(size_t i, size_t j)
{
	if (current_gamer == 0) return 2;
	Field *enemy_field = (current_gamer == 1) ? (second_field) : (first_field);
	bool was_there = false;
	try
	{
		was_there = enemy_field->was_there(i, j);
	}
	catch (whats_wrong &problem)
	{
		if (error_flag)
			_view->announce(problem.what());
	}
	if (!was_there) //if you can't make a move here
	{
		return 2;
	}
	if (enemy_field->make_move(i, j))
	{
		notifyUpdate();
		return 1;
	}
	notifyUpdate();
	return 0;
}

#include "Field.h"
#include "whats_wrong.h"
#include <algorithm>

Field::Field():_empty(176), _ship(219), amount_one(0), amount_two(0), amount_three(0), amount_four(0), field_size(10), _miss(127),  _damaged('X'), _destroyed('#'), _unknown('?')
{
	field = new uchar*[field_size];
	progress_field = new uchar*[field_size];
	for (size_t i = 0; i < field_size; i++)
	{
		field[i] = new uchar[field_size];
		progress_field[i] = new uchar[field_size];
		for (size_t j = 0; j < field_size; j++)
		{
			field[i][j] = _empty;
			progress_field[i][j] = _unknown;
		}
	}
}


Field::~Field()
{
	for (size_t i = 0; i < field_size; i++)
	{
		delete[] field[i];
		delete[] progress_field[i];
	}
}

uchar** Field::get_field()
{
	uchar **returned_field = new uchar*[field_size];
	for (size_t i = 0; i < field_size; i++)
	{
		returned_field[i] = new uchar[field_size];
		for (size_t j = 0; j < field_size; j++)
			returned_field[i][j] = field[i][j];
	}
	return returned_field;
}

void Field::set_ship(const coord & one_coord)
{
	if (amount_one >= 4)
		throw whats_wrong("Ship's amount error.");
	if (!is_in_field(one_coord))
		throw whats_wrong("Coordinate error.");
	if (!check_coord(one_coord))
		throw whats_wrong("Wrong position.");
	amount_one++;
	field[one_coord.x][one_coord.y] = _ship;
}

void Field::set_ship(const coord & begin_coord, const coord & end_coord, direction dir)
{
	if (!is_in_field(begin_coord) || !is_in_field(end_coord))
		throw whats_wrong("Coordinate error.");
	if (!check_coord(begin_coord) || !check_coord(end_coord))
		throw whats_wrong("Wrong position.");
	if (dir == direction::VERTICALLY)
	{
		int length = end_coord.x - begin_coord.x + 1;
		if (length > 4)
			throw whats_wrong("Ship's size error.");
		if (check_length(length))
		{
			for (int i = 0; i < length; i++)
			{
				field[begin_coord.x + i][begin_coord.y] = _ship;
			}
		}
		else
			throw whats_wrong("Ship's amount error.");
	}
	else
	{
		int length = end_coord.y - begin_coord.y + 1;
		if (length > 4)
			throw whats_wrong("Ship's size error.");
		if (check_length(length))
		{
			for (int i = 0; i < length; i++)
			{
				field[begin_coord.x][begin_coord.y + i] = _ship;
			}
		}
		else
			throw whats_wrong("Ship's amount error.");
	}
}

/*return true if coord is in the field*/
bool Field::is_in_field(const coord & one_coord) //return true if coord is in the field
{
	return (!(one_coord.x < 0 || one_coord.y < 0 || one_coord.x >= static_cast<int>(field_size) || one_coord.y >= static_cast<int>(field_size)));
}

/*returns true if position is OK*/
bool Field::check_coord(const coord & one_coord) //returns true if position is OK
{
	bool direction = true;
	for (int i = -1; i <= 1; i++)//(int i = -1; i <= 1, direction; i++)
	{
		for (int j = -1; j <= 1; j++)//(int j = -1; j <= 1, direction; j++)
		{
			coord next(one_coord.x + i, one_coord.y + j);
			if (is_in_field(next))
				if (field[next.x][next.y] == _ship)
					direction = false;
		}
	}
	return direction;
}

bool Field::check_length(int length)// true if everything is OK, increases amount counter
{
	
	if (length == 2)
		if (amount_two >= 3)
		return false;
		else
		{
			amount_two++;
			return true;
		}
	if (length == 3)
		if (amount_three >= 2)
			return false;
		else
		{
			amount_three++;
			return true;
		}
	if (length == 4)
		if (amount_four >= 1)
			return false;
		else
		{
			amount_four++;
			return true;
		}
	return false;
}

bool Field::is_ready() //returns true if field is ready
{
	return (amount_one == 4 && amount_two == 3 && amount_three == 2 && amount_four == 1);
}

bool Field::ready_to_continue()
{
	return (amount_one > 0 || amount_two > 0 || amount_three > 0 || amount_four > 0);
}

uchar ** Field::get_progress_field()
{
	uchar **returned_field = new uchar*[field_size];
	for (size_t i = 0; i < field_size; i++)
	{
		returned_field[i] = new uchar[field_size];
		for (size_t j = 0; j < field_size; j++)
			returned_field[i][j] = progress_field[i][j];
	}
	return returned_field;
}

/*returns TRUE if you CAN make a move here*/
bool Field::was_there(size_t x, size_t y)
{
	if (!is_in_field(coord(x,y)))
		throw whats_wrong("Wrong position.");
	return (progress_field[x][y] == _unknown);
}

/*TRUE if ship*/
bool Field::make_move(size_t i, size_t j)
{
	if (field[i][j] != _ship)
	{
		field[i][j] = _miss;
		progress_field[i][j] = _miss;
		return false;
	}
	else
	{
		field[i][j] = _damaged;
		progress_field[i][j] = _damaged;
		//если однопалубный, то меняем, иначе смотрим, ранили ми корабль или убили
		if (is_one(i, j))
			return true;
		check_destroyed(i, j);
	}
	return true;
}

/*TRUE  если однопалубный и засчитан как убит, FALSE иначе*/
bool Field::is_one(size_t i, size_t j)
{
	field[i][j] = _empty;
	if (check_one_ship(i, j)) //если однопалубный, чтобы проверить, что вокруг нет кораблей
	{
		field[i][j] = _destroyed;
		progress_field[i][j] = _destroyed;
		amount_one--;
		return true;
	}
	field[i][j] = _damaged;
	return false;
}

/*TRUE если однопалубный*/
bool Field::check_one_ship(size_t x, size_t y)
{
	bool direction = true;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			coord next(x + i, y + j);
			if ( is_in_field(next))
				if (field[next.x][next.y] == _ship || field[next.x][next.y] == _damaged)
					direction = false;
		}
	}
	return direction;
}

/*смотрим, убит корабль или только ранен и соотв отмечаем*/
void Field::check_destroyed(size_t i, size_t j)
{
	std::vector <coord> next = find_next_damaged(i, j);
	if (next.size() == 0)
	{
		field[i][j] = _damaged;
		progress_field[i][j] = _damaged;
	}
	else
	{
		if (!check_full_ship(i, j, next)) //если там не полностью убит корабль
		{
			field[i][j] = _damaged;
			progress_field[i][j] = _damaged;
		}
	}
}

/*как вариант - вернуть вектор тех, кто подбит и рядом, сразу смотреть на предмет, если рядом есть и не подбиты еще*/
std::vector <coord>  Field::find_next_damaged(size_t x, size_t y)
{
	std::vector <coord> vec_coord;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i != j && is_in_field(coord(x + i, y + j)) && (i != 0 || j != 0))
			{
				if (field[x + i][y + j] == _damaged)
					vec_coord.push_back(coord(x + i, y + j));
				if (field[x + i][y + j] == _ship)
				{
					std::vector <coord> vec_coord1;
					return vec_coord1;
				}
			}
		}
	}
	return vec_coord;
}

/*if ship is all damaged, make it destroyed and returns TRUE*/
bool Field::check_full_ship(size_t i, size_t j, const std::vector <coord> &vec_coord)
{
	field[i][j] = _damaged;
	for (size_t l = 0; l < vec_coord.size(); l++)
	{
		std::vector <coord> next_damaged = find_next_damaged(vec_coord[l].x, vec_coord[l].y);
		if (next_damaged.size() == 0) //значит есть продолжение корабля, и оно не ранено еще
			return false;
		if (next_damaged.size() > 1) //есть еще раненые, кроме исходной клетки
		{
			int index = (next_damaged[0].x == i) ? 1 : 0;
			std::vector <coord> next_next_damaged = find_next_damaged(next_damaged[index].x, next_damaged[index].y);
			if (next_next_damaged.size() == 0)
				return false;
		}
	}
	size_t size = 1;
	field[i][j] = _destroyed;
	progress_field[i][j] = _destroyed;
	if (vec_coord[0].x == i) //if 'h'
	{
		int k = -1;
		while (is_in_field(coord(i, j + k)) && field[i][j + k] == _damaged)
		{
			field[i][j + k] = _destroyed;
			progress_field[i][j + k] = _destroyed;
			k--; size++;
		}
		k = 1;
		while (is_in_field(coord(i, j + k)) && field[i][j + k] == _damaged)
		{
			field[i][j + k] = _destroyed;
			progress_field[i][j + k] = _destroyed;
			k++; size++;
		}
	}
	else //if 'v'
	{
		int k = -1;
		while (is_in_field(coord(i + k, j)) && field[i + k][j] == _damaged)
		{
			field[i + k][j] = _destroyed;
			progress_field[i + k][j] = _destroyed;
			k--; size++;
		}
		k = 1;
		while (is_in_field(coord(i + k, j)) && field[i + k][j] == _damaged)
		{
			field[i + k][j] = _destroyed;
			progress_field[i + k][j] = _destroyed;
			k++; size++;
		}
	}
	if (size == 2 && amount_two > 0)
		amount_two--;
	else
		if (size == 3 && amount_three > 0)
			amount_three--;
		else
			if (amount_four > 0) amount_four--;
	return true;
}

std::vector<size_t> Field::get_statistics()
{
	std::vector<size_t> amount_vec;
	amount_vec.push_back(amount_one);
	amount_vec.push_back(amount_two);
	amount_vec.push_back(amount_three);
	amount_vec.push_back(amount_four);
	return amount_vec;
}








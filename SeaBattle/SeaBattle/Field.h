#pragma once
#include <vector>
using uchar = unsigned char;
enum class direction
{
	HORIZONTALLY = 0,
	VERTICALLY
};
struct coord
{
	int x, y; //x - first coord, y - second
	coord(int i, int j):x(i), y(j) {}
};
class Field
{
	uchar **field, **progress_field; //field - наше поле, progress field как отображается наше поле для противника
	size_t field_size; //нужен ли const?
	uchar _ship, _empty,_miss, _damaged, _destroyed, _unknown;
	size_t amount_one, amount_two, amount_three, amount_four;
	bool check_coord(const coord &one_coord);
	bool is_in_field(const coord &one_coord);
	bool check_length(int length);
	bool is_one(size_t i, size_t j);
	void check_destroyed(size_t i, size_t j);
	std::vector <coord> find_next_damaged(size_t x, size_t y);
	bool check_full_ship(size_t i, size_t j, const std::vector <coord> &vec_coord);
	bool check_one_ship(size_t x, size_t y);
public:
	Field();
	~Field();
	//uchar get_content(size_t i, size_t j);
	bool is_ready();
	const size_t get_size() { return field_size; }
	uchar **get_field(); //for ConsoleView
	uchar **get_progress_field(); //for ConsoleView
	void set_ship(const coord &begin_coord, const coord &end_coord, direction dir); //h - horizontally,  v - vertical
	void set_ship(const coord &one_coord);
	bool ready_to_continue();
	bool was_there(size_t x, size_t y);
	bool make_move(size_t i, size_t j);
	std::vector <size_t> get_statistics();
};


#pragma once
#include "Observable.h"
#include "Field.h"

class ConsoleView;

class GameModel:public Observable
{
	Field *first_field, *second_field;
	int current_gamer; //1,2
	uchar **get_first_field() { return first_field->get_field(); }
	uchar **get_first_progress_field() { return first_field->get_progress_field(); }
	uchar **get_second_field() { return second_field->get_field(); }
	uchar **get_second_progress_field() { return second_field->get_progress_field(); }
	bool error_flag;
	ConsoleView *_view;
public:
	GameModel() :error_flag(true) { first_field = new Field(); second_field = new Field(); };
	void set_console_view(ConsoleView *view) { _view = view; } 
	void refresh_fields() { delete first_field; delete second_field;  first_field = new Field(); second_field = new Field();}
	~GameModel() { delete first_field; delete second_field; };
	void change_error_flag(bool flag) { error_flag = flag; }
	bool field_is_ready_to_start();
	bool game_continue(); //if game can continue
	int winner();
	void set_current_gamer(int gamer_numb) { current_gamer = gamer_numb; }
	uchar **get_my_field();
	uchar **get_enemy_field();
	void _set_ship(const coord &begin_coord, const coord &end_coord, direction dir); //h - horizontally,  v - vertical
	void _set_ship(const coord &one_coord);
	size_t get_field_size() { return first_field->get_size(); }
	int make_move(size_t i, size_t j);
	std::vector <std::vector <size_t>> get_statistics();
};


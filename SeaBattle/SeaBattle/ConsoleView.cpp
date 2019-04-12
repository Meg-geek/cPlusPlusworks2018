#include "ConsoleView.h"
#include <iostream>
#include <cstdio>
#include <windows.h>
#include <string>

void delete_array(unsigned char**array, size_t size)
{
	for (size_t i = 0; i < size; i++)
		delete[] array[i];
}

void print_letters()
{
	for (int i = 0; i < 18; i++)
		std::cout << " ";
	for (int i = 0; i < 2; i++)
	{
		uchar letter = 'A';
		for (int i = 0; i < 10; i++)
		{
			std::cout << letter << " ";
			letter++;
		}
		std::cout << "                         ";
	}
	std::cout << std::endl;
}

void print_stat(size_t i, const std::vector <std::vector <size_t>> &vec_stat, size_t player)
{
	if (i <= 1 || i > 8 || i % 2 == 1)
	{
		for (int k = 0; k < 15; k++)
		{
			std::cout << ' ';
		}
	}
	else
	{
		std::cout << " amount " << i / 2 << ": " << vec_stat[player][i / 2 - 1] << "   ";
	}
}

void ConsoleView:: print_arrays(unsigned char **array_1, unsigned char **array_2, size_t size)
{
	std::vector <std::vector <size_t>> vec_stat = _model->get_statistics();
	unsigned char _wall = 178;
	print_letters();
	for (size_t i = 0; i < size; i++)
	{
		print_stat(i, vec_stat, 0);
		//std::cout << "   ";// << (i + 1) << " ";
		printf_s("%.2d ", i+1);
		for (size_t j = 0; j < size; j++)
			std::cout << array_1[i][j]<<" ";
		std::cout <<"  " << _wall << _wall<<"   ";//something 
		print_stat(i, vec_stat, 1);
		printf_s("%.2d ", i + 1);
		for (size_t k = 0; k < size; k++)
			std::cout << array_2[i][k]<<" ";
		std::cout << std::endl;
		if (i < size - 1)
		{
			for (size_t l = 0; l < size + 9; l++)
				std::cout << "  ";
			std::cout << "  " << _wall << _wall << "   ";
		}
		std::cout << std::endl;
	}
}

ConsoleView::~ConsoleView()
{
}

void ConsoleView::set_width_and_hight()
{
	HANDLE hWndConsole;
	if (hWndConsole = GetStdHandle(-12))
	{
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
		{
			width = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
			height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
		}
		//else
			//printf("Error: %d\n", GetLastError());
	}
	//else
		//printf("Error: %d\n", GetLastError());
}

void ConsoleView::draw_top()
{
	/*set the bigger font*/
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo;
	// эта строка нужна
	fontInfo.cbSize = sizeof(fontInfo);
	GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
	wcscpy_s(fontInfo.FaceName, L"Lucida Console");
	fontInfo.dwFontSize.Y = 15;
	SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
	for (size_t i = 0; i < width/2 - 6; i++)
		std::cout << ' ';
	std::cout << "SEA BATTLE";
	std::cout << std::endl;
	std::cout << std::endl;
	for (size_t i = 0; i < width / 8 - 3; i++)
		std::cout << ' ';
	std::cout << "PLAYER 1";
	for (size_t i = 0; i < width / 3; i++)
		std::cout << ' ';
	std::cout << "PLAYER 2";
	std::cout << std::endl;
	std::cout << std::endl;
}

void ConsoleView::draw_field()
{
	_model->set_current_gamer(_print_gamer);
	uchar **first_field = _model->get_my_field();
	_model->set_current_gamer(_print_gamer);
	uchar **second_field = _model->get_enemy_field();
	size_t size = _model->get_field_size();
	print_arrays(first_field, second_field, size);
	delete_array(first_field, size);
	delete_array(second_field, size);
}

void ConsoleView::announce(const std::string & announcment)
{
	std::cout << announcment << std::endl;
}

void ConsoleView::announce_winners(const std::vector<int>& win_vec)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo;
	// эта строка нужна
	fontInfo.cbSize = sizeof(fontInfo);
	GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
	wcscpy_s(fontInfo.FaceName, L"Lucida Console");
	fontInfo.dwFontSize.Y = 15;
	SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
	for (size_t i = 0; i < width / 2 - 6; i++)
		std::cout << ' ';
	std::cout << "SEA BATTLE";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "GAME STATISTIC: "<<std::endl;
	for (size_t i = 0; i < win_vec.size(); i++)
	{
		std::cout << i + 1 << " ROUND: ";
		if (win_vec[i] == 1)
			std::cout << "FIRST PLAYER" << std::endl;
		else
			std::cout << "SECOND PLAYER" << std::endl;
	}
}

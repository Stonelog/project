#pragma once 

#include <iostream>
#include <string>
#include <curses.h>
#include <semaphore.h>
#include "comm.h"

class chat_window
{
public:

	chat_window();

	void flush_win(WINDOW* _win);
	void put_str(WINDOW* _win , int _y , int _x ,std::string &str);
	void clear_win_line(WINDOW* _win ,int begin_y , int nums);

	WINDOW* create_newwin(int h , int w , int y, int x);

	void get_str(WINDOW* _win, std::string &out);

	void creat_header();
	void creat_output();
	void creat_flist();
	void creat_input();

	~chat_window();

public:
	WINDOW* header;
	WINDOW* output;
	WINDOW* flist;
	WINDOW* input;
	sem_t lock;
};



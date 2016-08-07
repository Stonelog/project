#include "chat_window.h"

chat_window::chat_window()
{
	initscr();
	curs_set(0);
	sem_init(&lock,0, 1);
}

WINDOW* chat_window::create_newwin(int h , int w , int y ,int x)
{
	WINDOW *local_win = newwin(h, w ,y, x);
//	box(local_win , 0,0);
	box(local_win , '|', '-');  /*draw a box*/
	return local_win;
}

void chat_window::get_str(WINDOW* _win, std::string &out)
{
	char buf[_SIZE_];
	wgetnstr(_win , buf , _SIZE_);
	out = buf;
}

void chat_window::flush_win(WINDOW* _win)
{
	sem_wait(&lock);
	wrefresh(_win);
	sem_post(&lock);
}

void chat_window::put_str(WINDOW* _win , int _y , int _x ,std::string &str)
{
	//initscr();
	//start_color();
	//init_pair(1, COLOR_RED, COLOR_BLACK);
	//wattron(_win ,COLOR_PAIR(0));
	
	wattron(_win , A_BOLD  | A_BLINK);
	sem_wait(&lock);
	mvwaddstr(_win , _y, _x, str.c_str());
	sem_post(&lock);
}

void chat_window::clear_win_line(WINDOW* _win ,int begin_y , int nums)
{
	while(nums-- > 0)
	{
		sem_wait(&lock);
		wmove(_win, begin_y++ , 0);
		wclrtoeol(_win);
		sem_post(&lock);
	}
}

void chat_window::creat_header()
{
	int _y = 0;
	int _x = 0;
	int _h = LINES/6;
	int _w = 0;

	header = create_newwin(_h , _w , _y, _x);
}

void chat_window::creat_output()
{
	int _y = LINES/6;
	int _x = 0;
	int _h = (LINES*4)/6;
	int _w = (COLS*3)/4;

	output = create_newwin(_h , _w , _y, _x);
}

void chat_window::creat_flist()
{
	int _y = LINES/6;
	int _x = (COLS*3)/4;
	int _h = (LINES*4)/6;
	int _w = COLS/4;

	flist = create_newwin(_h , _w , _y, _x);
}

void chat_window::creat_input()
{
	int _y = (LINES*5)/6;
	int _x = 0;
	int _h = LINES/6;
	int _w = 0;

	input = create_newwin(_h , _w , _y, _x);
}

chat_window::~chat_window()
{
	delwin(header);
	delwin(output);
	delwin(flist);
	delwin(input);
	sem_destroy(&lock);
	endwin();
}


#ifdef _DEBUG_

int main()
{
	chat_window win;
	win.creat_header();
	win.flush_win(win.header);
	sleep(1);

	win.creat_output();
	win.flush_win(win.output);
	sleep(1);

	win.creat_flist();
	win.flush_win(win.flist);
	sleep(1);

	win.creat_input();
	win.flush_win(win.input);
	sleep(1);

	std::string out = "Welcome chat...";

	int max_x = 0;
	int max_y = 0;
	getmaxyx(win.header, max_y, max_x);

	int header_y = max_y/2;
	if (max_y % 2 == 0)
	{
		header_y -=  1;
	}
	int index = 2;

	while(1)
	{
		win.creat_header();
		win.put_str(win.header , header_y, index+=2 ,out);
		wattron(win.header , A_BOLD  | A_BLINK);

		win.flush_win(win.header);

		usleep(500000);
		win.clear_win_line(win.header ,header_y , 1);

		if ((index+out.size()) >= (COLS*4)/5 )
		{
			index = 2;
		}
	}

	return 0;
}

#endif



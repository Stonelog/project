#include "udp_client.h"
#include <unistd.h> 
#include "udp_data.h"
#include "chat_window.h"
#include <strstream>
#include <curses.h>
#include <semaphore.h>

chat_window *win_p = NULL;
std::string nick_name ;
std::string school ;
std::string cmd = "Null" ;
sem_t lock;

void* draw_header(void* arg)
{
	win_p->creat_header();
	win_p->flush_win(win_p->header);

	std::string head_line = "Welcome chat...";

	int max_x = 0;
	int max_y = 0;
	getmaxyx(win_p->header, max_y, max_x);

	int header_y = max_y/2;
	if (max_y % 2 == 0)
	{
		header_y -=  1;
	}
	int index = 2;

	while(1)
	{
		win_p->creat_header();
		win_p->put_str(win_p->header , header_y, index+=2 ,head_line);
		wattron(win_p->header , A_BOLD  | A_BLINK);
		win_p->flush_win(win_p->header);

		if(index >= (max_x*3)/4)
		{
			index = 2;
		}

		usleep(500000);
		win_p->clear_win_line(win_p->header ,header_y , 1);
	}
}

void* draw_output(void* arg)
{
	udp_client *cli_p = (udp_client *)arg;
	win_p->creat_output();
	win_p->flush_win(win_p->output);

	std::string recv_str;
	udp_data data;

	std::string name;
	std::string school;
	std::string msg;
	std::string cmd;

	int max_x = 0;
	int max_y = 0;
	getmaxyx(win_p->output, max_y, max_x);

	int index = 1;

	while(1)
	{
		cli_p->udp_recv(recv_str);
		data. unserialize(recv_str);

		data.get_nick_name(name);
		data.get_school(school);
		data.get_msg(msg);
		data.get_cmd(cmd);
		
		std::string user;
	    std::string win_str = name;
	    win_str += "-";
		win_str += school;

		user = win_str;

		win_str += " # ";
		win_str += msg;
	
		if(cmd == "Q")
		{
			sem_wait(&lock);
			cli_p->del_flist(user);
		//	std::cout << "Size: " << cli_p->flist.size() << std::endl;
		//	sleep(2);
			sem_post(&lock);
		}
		else
		{
			sem_wait(&lock);
			cli_p->add_flist(user);
//			std::cout << "Size: " << cli_p->flist.size() << std::endl;
//			sleep(3);
			sem_post(&lock);
		}
		
		win_p->put_str(win_p->output,index++ , 1 ,win_str);
		if(index >= max_y-1)
		{
			win_p->flush_win(win_p->output);
			sleep(1);
			index = 1;
			win_p->clear_win_line(win_p->output , 1 , max_y);
			win_p->creat_output();
		}
	
		//draw_flist(arg);
		win_p->flush_win(win_p->output);
	}
}

void* draw_flist(void* arg)
{
	udp_client *cli_p = (udp_client*)arg ;
	win_p->creat_flist();
	win_p->flush_win(win_p->flist);
	
	int max_x = 0;
	int max_y = 0;
	getmaxyx(win_p->flist, max_y, max_x);
	
	int num =0;
	int index = 0;
	while(1)
	{
		//win_p->clear_win_line(win_p->flist ,1,max_y);
		win_p->creat_flist();
		win_p->flush_win(win_p->flist);

		int fnums = cli_p->flist.size();
		int page = max_y - 3;
		int pages = fnums/page+1;
		int last_page = fnums%page;

		int i = 0;
		for ( ; num < pages ; ++num)
		{
			for(i = 0; i < page && i < fnums; ++i)
			{
				if (num ==  last_page-1)
				{
					int k = index;
					int line = 1;
					for(; k < fnums; ++k)
					{
						win_p->put_str(win_p->flist, line++ , 1 ,cli_p->flist[k]);
						win_p->flush_win(win_p->flist);
					}
				
					break;
				}
				else
				{
					index = num*page + i;
					win_p->put_str(win_p->flist, i+1 , 1 ,cli_p->flist[index]);
					win_p->flush_win(win_p->flist);
				}
			}

			break;
		}

		std::string str_num;
		std::string str_total;
		std::strstream ss;
		std::strstream ss1;
		ss<<num;
		ss>>str_num;
		ss1<<pages;
		ss1>>str_total;

		std::string str_page;
		str_page = str_num;
		str_page += "/";
		str_page += str_total;

		win_p->put_str(win_p->flist, max_y-2 , max_x/2 ,str_page);
		win_p->flush_win(win_p->flist);

		usleep(10000000);
	}
}

void* draw_input(void* arg)
{
	udp_client *cli_p = (udp_client*)arg ;
	std::string line = "Please Enter: ";

	win_p->creat_input();
	win_p->flush_win(win_p->input);
	char buf[1024];

	int max_x = 0;
	int max_y = 0;
	getmaxyx(win_p->header, max_y, max_x);

	udp_data data;

	while(1)
	{
		win_p->creat_input();
		std::string msg;
		win_p-> put_str(win_p->input ,1, 1 ,line);
		win_p->flush_win(win_p->input);
		win_p->get_str(win_p->input, msg);
		win_p->clear_win_line(win_p->input ,1 , 1);

		if(msg == "quit" || msg == "q")
		{
			cmd = "Q";
		}

		std::string send;
		data.set_nick_name(nick_name);
		data.set_school(school);
		data.set_cmd(cmd);
		data.set_msg(msg);

		data.serialize(send) ;
		
		cli_p->udp_send(send);

		if (msg == "quit" || msg == "q")
		{
			delwin(win_p->header);
			delwin(win_p->output);
			delwin(win_p->flist);
			delwin(win_p->input);
			endwin();
			_exit(0);
		}

		usleep(100000);
	}
}

int main(int argc , char *argv[])
{
	if(argc != 3)
	{
		std::cout << "argc: ["<<argc<<"]"  <<"[ip]" << "[port]"<< std::endl;
		exit(1);
	}

	sem_init(&lock,0,1);

	std::string ip(argv[1]);
	int port = atoi(argv[2]);

	udp_client _client(ip, port);
	_client.init();
	char buf[_SIZE_];
    
	std::cout <<"Please input name : ";
	fflush(stdout);
	std::cin >> nick_name;

	std::cout <<"Please input school : ";
	fflush(stdout);
	std::cin >> school;

	chat_window win;
	win_p = &win;

	pthread_t header , output, flist, input;
	pthread_create(&header, NULL, draw_header,(void*)&_client);
	pthread_create(&output, NULL, draw_output,(void*)&_client);
	pthread_create(&flist , NULL, draw_flist, (void*)&_client);
	pthread_create(&input , NULL, draw_input, (void*)&_client);

	pthread_join(header, NULL);
	pthread_join(output, NULL);
	pthread_join(flist, NULL);
	pthread_join(input, NULL);
	
	if (cmd == "Q")
	{
		return 0;
	}
	
	return 0;
}



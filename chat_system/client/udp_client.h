#pragma once

#include <iostream>
using namespace std;
#include "comm.h"
#include <vector>
#include "udp_data.h"

class udp_client
{
public :

	udp_client(const std::string& _ip = _IP_, int _port = _PORT_);
	//udp_client();
	
	void init();

	ssize_t udp_recv(std::string &out);

	ssize_t  udp_send(std::string &in);

	~udp_client();

	void del_flist(std::string &user);
	void add_flist(std::string &user);

	std::vector<std::string> flist;

private:
	int sock;
	std::string ip;
	int port;
};



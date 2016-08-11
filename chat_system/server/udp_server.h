#pragma once 

#include <iostream>
using namespace std;
#include "comm.h"
#include <map>
#include "data_pool.h"
#include <vector>

class udp_server
{
	void add_user(struct sockaddr_in &client);
	void del_user(struct sockaddr_in &client, std::string &out);
public:

//	udp_server();
	udp_server(const std::string& _ip=_IP_ , int _port=_PORT_);

	void init();
	
	ssize_t udp_recv(std::string &out);

	ssize_t udp_send(std::string &in ,struct sockaddr_in &cli , socklen_t len);

	void broadcast();

	~udp_server();

private:
	int sock;	
	std::string ip;
	int port;

	data_pool pool;
	std::map<std::string, struct sockaddr_in> online_user;
};



#include "udp_server.h"
#include "udp_data.h"

udp_server::udp_server(const std::string& _ip , int _port)
	:ip(_ip)
	 ,port(_port)
	 ,sock(-1)
{ }

//char *inet_ntoa(struct in_addr in);

void udp_server::add_user(struct sockaddr_in &client)
{
	std::string  _key = inet_ntoa(client.sin_addr);

	std::map<std::string, struct sockaddr_in>::iterator iter = online_user.find(_key);

	if(iter == online_user.end())
	{
		online_user.insert(std::pair<std::string , struct sockaddr_in>(_key ,client) );
		std::cout <<"["<< _key <<"] : add server succeed !" <<std::endl;
	}
}

void udp_server::del_user(struct sockaddr_in &client, std::string &out)
{
	std::string  _key = inet_ntoa(client.sin_addr);

	udp_data data;
	data.unserialize(out);

	std::string cmd ;
	data.get_cmd(cmd);

	if(cmd == "Q")
	{
		online_user.erase(_key);
		std::cout <<"["<< _key <<"] : del server succeed !" <<std::endl;
	}
}

void udp_server::init()
{
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
	{
		print_log(strerror(errno) , __FUNCTION__, __LINE__ );
		exit(1);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip.c_str());

	if(	bind(sock ,(struct sockaddr *)&local ,sizeof(local)) < 0)
	{
		print_log(strerror(errno) , __FUNCTION__, __LINE__);
		exit(1);
	}
}

ssize_t udp_server::udp_recv(std::string &out)
{
	struct sockaddr_in client;
	socklen_t len = sizeof(client);
	char buf[_SIZE_];
	memset(buf , '\0', sizeof(buf));

	ssize_t _ret =recvfrom(sock, buf , sizeof(buf)-1  ,0,(struct sockaddr*)&client, &len );
	if(	_ret > 0 )
	{
		out = buf;
		pool.data_put(out);

		add_user(client);
		del_user(client,out);
	}
	else
	{
		print_log(strerror(errno) , __FUNCTION__, __LINE__ );
		exit(1);
	}

	return _ret;
}

ssize_t  udp_server::udp_send(std::string &in ,struct sockaddr_in &cli , socklen_t len)
{
	ssize_t _ret = sendto( sock , in.c_str() ,in.size(), 0, (struct sockaddr*)&cli , len );

	if(_ret < 0)
	{
		print_log(strerror(errno) , __FUNCTION__, __LINE__ );
		exit(1);
	}
	return _ret;
}

void udp_server::broadcast()
{
	std::map<std::string, struct sockaddr_in>::iterator vectIter = online_user.begin();
	std::string msg;
	pool.data_get(msg);

	for( ; vectIter != online_user.end(); ++vectIter)
	{
		udp_send(msg ,vectIter->second, sizeof(vectIter->second));
	}
}

udp_server::~udp_server()
{
	if(sock != -1)
	{
		close(sock);
	}
}



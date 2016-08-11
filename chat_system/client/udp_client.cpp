#include "udp_client.h"

//udp_client::udp_client()
//	:ip(_IP_)
//	 ,port(_PORT_)
//{ }

udp_client::udp_client(const std::string& _ip , int _port )
	: ip(_ip)
	, port(_port)
	, sock(-1)
{ }

void udp_client::init()
{
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	if(sock < 0)
	{
		print_log(strerror(errno) , __FUNCTION__, __LINE__ );
		exit(1);
	}
}

ssize_t udp_client::udp_recv(std::string &out)
{
	struct sockaddr_in remote;
	socklen_t len = sizeof(remote);
	char buf[_SIZE_];
	memset(buf , '\0', sizeof(buf));
	ssize_t _ret =recvfrom(sock, buf , sizeof(buf)-1  ,0,(struct sockaddr*)&remote, &len );

	udp_data data;
	
	if(	_ret > 0 )
	{
		out = buf;
		
		//data. unserialize(out);

		//add_flist(out);
	}
	else
	{
		print_log(strerror(errno) , __FUNCTION__, __LINE__ );
		exit(1);
	}

	return _ret;
}

ssize_t  udp_client::udp_send(std::string &in)
{
	struct sockaddr_in remote;
	remote.sin_family = AF_INET;
	remote.sin_port = htons(port);
	remote.sin_addr.s_addr = inet_addr(ip.c_str());
	
	socklen_t len = sizeof(remote);

	ssize_t _ret = sendto( sock , in.c_str() ,in.size(), 0, (struct sockaddr*)&remote , len );
	if(_ret < 0)
	{
		print_log(strerror(errno) , __FUNCTION__, __LINE__ );
		exit(1);
	}

	return _ret;
}

void udp_client::del_flist(std::string &user)
{
	std::vector<std::string>::iterator _iter = flist.begin();

	for( ; _iter != flist.end(); )
	{
		if(*_iter == user)
		{
			_iter = flist.erase(_iter);
//			std::cout<< user <<"exit....."<<std::endl;
		}
		else
		{
			++_iter;
		}
	}
}

void udp_client::add_flist(std::string &user)
{ 
	int i = 0;
	int size = flist.size();

	for(i = 0; i < size; ++i)
	{
		if (user == flist[i])
		{
			return ;
		}
	}

	flist.push_back(user);
}

udp_client::~udp_client()
{
	if(sock > 0)
	{
		close(sock);
	}
}



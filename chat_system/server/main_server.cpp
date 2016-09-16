#include  "udp_server.h"
#include <pthread.h>
#include "udp_data.h"

void* recv_product(void* arg)
{
	udp_server* _serp = (udp_server*)arg ;
	bool done = false;
	std::string msg;
	while(!done)
	{
		_serp->udp_recv(msg);
		printf("client:\n");
		fflush(stdout);
		std::cout<< msg << std::endl;
	}
}

void* recv_comsum(void* arg)
{
	udp_server* _serp = (udp_server*)arg ;
	bool done = false;
	while(!done)
	{
		_serp->broadcast();
	}
}

int main(int argc , char* argv[])
{
	if (argc != 3)
	{
		std::cout << "argc: ["<<argc<<"]"  <<"[ip]" << "[port]"<< std::endl;
		exit(1);
	}
	
	std::string ip(argv[1]);
	int port = atoi(argv[2]);

	udp_server _ser(ip, port);

	_ser.init();

	pthread_t th1 , th2;
	pthread_create(&th1 , NULL, recv_product, (void*)&_ser);
	pthread_create(&th2 , NULL, recv_comsum, (void*)&_ser);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	return 0;
}



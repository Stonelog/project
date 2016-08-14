#include <sys/time.h>
#include <sys/wait.h>
#include <sys/epoll.h>
#include <sys/types.h>         
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

#define _SIZE_ 1024

static void usage(const char*proc)
{
	printf("Usage : %s [IP] [PORT] \n",proc);
}

static int startup(const char *_ip , int _port)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("socket");
		exit(2);
	}

	int opt = 1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));	

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(_port);
	local.sin_addr.s_addr = inet_addr(_ip);

	if(bind(sock,(struct sockaddr *)&local,sizeof(local)) < 0)
	{
		perror("bind");
		exit(3);
	}

	if(listen(sock,4) < 0)
	{
		perror("listen");
		exit(4);
	}
	return sock;
}
	
static int get_line(int sock,char buf[], int len)
{
	if(NULL == buf || len < 0)
		return -1;

	char ch = '\0';
	int n = recv(sock, &ch, 1, 0);
	int index = 0;

	while(index < (len-1) &&  n > 0 && ch != '\n')
	{
		if(ch == '\r')
		{
			n = recv(sock, &ch, 1, MSG_PEEK);
			if(n > 0 && ch != '\n')
			{
				recv(sock, &ch, 1, 0);
			}
			else
			{
				ch = '\n'; 
			}
		}
		buf[index++] = ch;
		n = recv(sock, &ch, 1, 0);
	}

	buf[index] = '\0';
	
	return index;
}

void echo_error(int sock,int status)
{
	char buf[_SIZE_];
	memset(buf,'\0',sizeof(buf));

    switch(status)
	{
		case 404:
			strcpy(buf,"404 NOT FIND");
			send(sock,buf,strlen(buf),0);
			break;
		case 500:
			strcpy(buf,"500 SERVER ERROR");
			send(sock,buf,strlen(buf),0);
			break;
		case 503:
			strcpy(buf,"503 SERVER DO NOT CLIENT REQUEST,PLEASE WAIT....");
			send(sock,buf,strlen(buf),0);
			break;
	}
	close(sock);
}

void clear_header(int sock)
{
	char buf[_SIZE_];
	memset(buf,'\0',sizeof(buf));
	int ret  = -1;

	do
	{
		ret = get_line(sock,buf,sizeof(buf));

	}while(ret > 0 && strcmp(buf,"\n") != 0);
}

void exec(int sock,const char *path,const char *method,const char *query_string)
{
	char buf[_SIZE_];
	int ret = -1;
	int content_length = -1;
	int cgi_input[2] = {0,0};
	int cgi_output[2] = {0,0}; //相对与cig来说 cgi == 通用网关接口

	if(strcasecmp(method,"GET") == 0)
	{
		clear_header(sock);
	}
	else
	{
		do
		{
			ret = get_line(sock,buf,sizeof(buf));

			if(strncasecmp(buf, "Content-Length:", strlen("Content-Length:")) == 0)
			{
				content_length = atoi(&buf[16]);
			}
		
		}while(ret > 0 && strcmp(buf,"\n") != 0);

		if(content_length == -1)
		{
			echo_error(sock,500);
			return ;
		}
	}

	printf("method :%s\n",method);
	printf("query string :%s\n",query_string);
	printf("content_lenght :%d\n",content_length);

	char buf1[_SIZE_] = "HTTP/1.1 200 OK \r\n\r\n";
	send(sock,buf1,strlen(buf1),0);

	if(pipe(cgi_input) < 0)
	{
		perror("pipe(cgi_input)");	
		echo_error(sock,500);
		return ;
	}
	if(pipe(cgi_output) < 0)
	{
		perror("pipe(cgi_input)");	
		echo_error(sock,500);
		close(cgi_input[0]);
		close(cgi_input[1]);
		return ;
	}

	pid_t pid = -1;
	pid = fork();
	if(pid < 0)
	{
		perror("fork");	
		close(cgi_input[0]);
		close(cgi_input[1]);
		close(cgi_output[0]);
		close(cgi_output[1]);
		echo_error(sock,503);
		return ;
	}
	if(pid == 0)
	{
		char method_env[_SIZE_];
		char query_string_env[_SIZE_];
		char length_env[_SIZE_];

		memset(method_env,'\0',sizeof(method_env));
		memset(query_string_env,'\0',sizeof(query_string_env));
		memset(length_env,'\0',sizeof(length_env));


		close(cgi_input[1]);
		close(cgi_output[0]);

		dup2(cgi_input[0],0);
		dup2(cgi_output[1],1); //cgi write

		sprintf(method_env,"REQUEST_METHOD=%s",method);
		putenv(method_env);

		if(strcasecmp(method,"GET") == 0)
		{
			sprintf(query_string_env,"QUERY_STRING=%s",query_string);
			putenv(query_string_env);
		}
		else
		{
			sprintf(length_env,"CONTENT_LENGTH=%d",content_length);
			putenv(length_env);
		}

		execl(path,path,NULL);

		exit(-1);
	}
	else
	{
		close(cgi_input[0]);
		close(cgi_output[1]);

		size_t i = 0;
		char ch = '\0';

		if(strcasecmp(method,"POST") == 0)
		{
			for( ; i < content_length; ++i)
			{
				recv(sock,&ch,1,0);
				write(cgi_input[1],&ch,1);
			}
		}

		while(read(cgi_output[0],&ch,1) > 0)
		{
			send(sock,&ch,1,0);
		}

		close(cgi_input[1]);
		close(cgi_output[0]);

		waitpid(pid,NULL,0);
	}
}

void echo_www(int sock,char *path, int len)
{
	int fd = open(path, O_RDONLY);

	char buf[_SIZE_] = "HTTP/1.1 200 OK \r\n\r\n";
	send(sock,buf,strlen(buf),0);

	ssize_t ret = sendfile(sock, fd, NULL, len);
	if(ret < 0)
	{
		perror("sendfile");
		return ;
	}

	close(fd);
}

void* request(void *arg)
{
	pthread_detach(pthread_self());

	int sock = (int)arg;
	char buf[_SIZE_];
	char method[_SIZE_]; //方法
	char url[_SIZE_];    
	char path[_SIZE_];
	char *query_string =  NULL;
	
	memset(buf,'\0',sizeof(buf));
	int ret  = -1;

	ret = get_line(sock,buf,sizeof(buf));
	if(ret < 0)
	{
		perror("get_line");
		return (void*)1;
	}

	int i = 0;
	int j = 0;

	while((i < sizeof(method)-1) && (j < sizeof(buf)-1))
	{
		if(buf[j] == ' ')
		{
			break;
		}
		method[i] = buf[j];
		++i;
		++j;
	}
	method[i] = '\0';

	//处理空格
	while((j < sizeof(buf)-1) && isspace(buf[j]))
	{
		++j;
	}

	i = 0;
	while((i < sizeof(url)-1) && (j < sizeof(buf)-1) && (!isspace(buf[j])))
	{
		if(buf[j] == ' ')
		{
			break;
		}
		
		url[i] = buf[j];
		++i;
		++j;
	}
	url[i] = '\0';

	int cgi = 0;
	
	if(strcasecmp(method,"GET") != 0 && strcasecmp(method,"POST") != 0)
	{
		echo_error(sock,404);
		return (void*)-1;
	}

	if(strcasecmp(method,"POST") == 0)
	{
		cgi = 1;
	}

	if(strcasecmp(method,"GET") == 0)
	{
		query_string = url;
		while(*query_string != '\0'&& *query_string != '?')
		{
			query_string++;
		}
		if(*query_string == '?')
		{
			cgi = 1;
			*query_string = '\0';
			++query_string;
		}
	}

	sprintf(path,"htdoc%s",url);

	if(strcmp(url,"/") == 0)
	{
		strcat(path,"index.html");
	}

	printf("path :%s\n",path);
	struct stat st  ;

	if(stat(path, &st) < 0)
	{
		echo_error(sock,404);
		perror("stat");
		return (void *)-2;
	}

	if(S_ISDIR(st.st_mode)) //(st.st_mode & S_IFMT) == S_IFDIR
	{
		strcpy(path,"htdoc/index.html");	
	}
	else if ((st.st_mode & S_IXUSR) ||(st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH) )
	{
		cgi = 1;
	}
	else 
	{	}

	if(cgi)
	{
		exec(sock, path, method, query_string);
	}
	else
	{
		clear_header(sock);
		echo_www(sock,path,st.st_size);
	}

	close(sock);

	return (void *)0;
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		exit(1);
	}

	int listen_sock = startup(argv[1],atoi(argv[2]));

	int epfd = epoll_create(126);

	struct epoll_event events[20];
	struct epoll_event ev;

	ev.events = EPOLLIN;
	ev.data.fd = listen_sock;

	fcntl(listen_sock, F_SETFL, O_NONBLOCK );

    epoll_ctl(epfd, EPOLL_CTL_ADD, listen_sock, &ev); //将新的fd添加到epoll的监听队列中

	int i = 0;
    int nfds = 0;

	while(1)
	{
		nfds = epoll_wait(epfd, events, sizeof(events)/sizeof(events[0]), -1); 

		switch (nfds)
		{
			case -1:
				perror("epoll_wait");  break;
			case 0:
				printf("timeout....\n");  break;
			default:

				for(i = 0;i < nfds; ++i)
    		    {
					int sockfd =  events[i].data.fd;

    		        if( events[i].data.fd == listen_sock ) //如果是主socket的事件，则表示有新的连接
    		        {
						struct sockaddr_in clientaddr;
						socklen_t clilen = sizeof(clientaddr);

    		            int connfd = accept(listen_sock,(struct sockaddr *)&clientaddr, &clilen); //accept这个连接
						if (connfd < 0)
						{
							perror("accept");
							continue;
						}
				
						printf("create new client , [%s]->[%d] \n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));

						fcntl(connfd, F_SETFL, O_NONBLOCK );

    		            ev.data.fd = connfd;
    		            ev.events = EPOLLIN | EPOLLET;
    		            epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev); //将新的fd添加到epoll的监听队列中
    		        }
				    else if( events[i].events & EPOLLIN ) //接收到数据，读socket
				    {
						if (sockfd  < 0)
						{
							continue;
						}

						pthread_t th1;
						pthread_create(&th1,NULL,request,(void *)sockfd);

    		            ev.data.fd = sockfd;
    		            ev.events = EPOLLOUT | EPOLLET;
    		            epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&ev); //将新的fd添加到epoll的监听队列中
					}
					else if( events[i].events & EPOLLOUT ) //有数据待发送，写socket
					{
						if (sockfd  < 0) 
						{
							continue;
						}
						
						//pthread_t th2;
						//pthread_create(&th2,NULL,request,(void *)sockfd);

						ev.data.fd = sockfd;
						ev.events = EPOLLIN | EPOLLET;
						epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev); //修改标识符，等待下一个循环时接收数据
					}
					else
					{
				                 //其他情况的处理
					}

					break;
				}
		}
	}

	close(epfd);

	return 0;
}



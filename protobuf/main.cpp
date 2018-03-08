#include <iostream>
#include "proto/practice.person.pb.h"
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <thread>

using namespace practice;
using namespace std;

int FormatSockaddr(struct sockaddr* paddr,char *stringbuf,int size);

int main(int argc,char *argv[])
{
	int lsfd=0;
	int ret=0;
	int port=0;
	if(argc<2)
	{
		std::cout<<"input listen port\n";
		return 0;
	}
	port=std::atoi(argv[1]);
	std::cout<<port<<std::endl;
	return 0;
	lsfd=socket(AF_INET,SOCK_STREAM,0);
	if(lsfd<1)
	{
		std::cout<<"socket error"<<std::endl;
		return 0;
	}

	struct sockaddr_in local;
	bzero(&local,sizeof(local));
	local.sin_family=AF_INET;
	local.sin_port=htons(port);
	local.sin_addr.s_addr=htonl(INADDR_ANY);

	ret=bind(lsfd,(struct sockaddr*)&local,sizeof(local));
	if(ret!=0)
	{
		std::cout<<"bing failed\n";
		return 0;
	}
	ret=listen(lsfd,SOMAXCONN);
	if(ret !=0)
	{
		std::cout<<"listen error \n";
		return 0;
	}

	struct sockaddr_in client;
	bzero(&client,sizeof(client));
	std::cout<<"\n start accept prot:"<<port<<std::endl;

	while(1)
	{
		int cli_fd=0;
		socklen_t clen=0;
		cli_fd=accept(lsfd,(struct sockaddr*)&client,&clen);
		if(cli_fd<0)
		{
			std::cout<<"accept error\n";
			return 0;
		}


	}

	practice::Person person;
	person.set_age(25);
    person.set_address("new york");
    person.set_name("Tom");

	return 0;
}

int FormatSockaddr(struct sockaddr* paddr,char *stringbuf,int size)
{
   struct sockaddr_in *paddrin=(struct sockaddr_in*)paddr;
   int port=ntohs(paddrin->sin_port);
   char buf[20]={0};
   inet_ntop(AF_INET,&(paddrin->sin_addr),buf,sizeof(buf));
   sprintf(stringbuf,"%s:%d",buf,port);
}


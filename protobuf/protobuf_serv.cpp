#include <iostream>
#include "src/practice.person.pb.h"
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
typedef struct _client {
	int fd;
	struct sockaddr_in addr;
} Client;

void* OnConnect(void *arg);

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
	lsfd=socket(AF_INET,SOCK_STREAM,0);//申请socket文件描述符
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

	int flag=1;
	ret=setsockopt(lsfd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag));//地址复用
	if(ret !=0 )
	{
		std::cout<<"reuse address failed\n";
		return 0;
	}
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
		socklen_t clen=sizeof(client);
		cli_fd=accept(lsfd,(struct sockaddr*)&client,&clen);
		if(cli_fd<0)
		{
			std::cout<<"accept error\n";
			return 0;
		}

		Client *pclient=new Client;
		pclient->fd=cli_fd;
		pclient->addr=client;
		std::thread t1(OnConnect,pclient);
		t1.detach();
	}
/*
	practice::Person person;
	person.set_age(25);
	person.set_address("new york");
	person.set_name("Tom");
*/
	return 0;
}


int FormattSockAddr(struct sockaddr *addr,char *strbuf,size_t slen)
{
	if(addr==NULL|| addr==nullptr)
	{
		return 1;
	}
	char buf[32]={0};
	struct sockaddr_in *paddrin=reinterpret_cast<struct sockaddr_in*>(addr);
	if(paddrin==NULL)
	{
		std::cout<<"  FormattSockAddr ";
		std::cout<<"cast sockaddr failed"<<std::endl;
		return 1;
	}
	inet_ntop(AF_INET,&(paddrin->sin_addr),buf,sizeof(buf));
	int port=0;
	port=ntohs(paddrin->sin_port);

	sprintf(strbuf,"%s:%d",buf,port);

	return 0;
}

void* OnConnect(void *arg)
{
	if(NULL==arg)
	{
		std::cout<<"thread arg is NULL"<<std::endl;
		return NULL;
	}
	Client *pclient=reinterpret_cast<Client*>(arg);
	char addrstr[32]={0};
	FormattSockAddr(reinterpret_cast<struct sockaddr*>(&pclient->addr),addrstr,sizeof(addrstr));
	std::cout<<"client "<<addrstr<<" connected\n";

	int ret=0;
	char buff[1024]={0};
	std::string message="";

	while(1)
	{
		ret=recv(pclient->fd,buff,sizeof(buff),0);
		if(ret<1)
		{
			std::cout<<"client:"<<addrstr<<" disconnected\n";
			break;
		}
		practice::Person person;
		bool issuc=person.ParseFromArray(buff,ret);
		if(!issuc)
		{
			std::cout<<"Person convert failed"<<std::endl;
			continue;
		}

		printf("recv %d bytes message from %s\n",ret,addrstr);
		std::cout<<"person address:"<<person.address()<<std::endl;
		std::cout<<"person phone number:"<<person.phone().phonenumber()<<std::endl;
		memset(buff,0,ret);
	}
	close(pclient->fd);
	delete (pclient);
	return NULL;
}

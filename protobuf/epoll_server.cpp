#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>
#include <errno.h>
#include <sys/epoll.h>
#include <iostream>
#include "epoll_server.h"

using namespace std;


#define INIT_PORT 21345

EpollServer::EpollServer():port(INIT_PORT)
{

}

//发生了事件 即 epoll有了返回
void EpollServer::OnEvent(struct epoll_event* events,size_t len)
{
    size_t i;
    for(i=0;i<len;++i)
    {
        struct epoll_event reaev=events[i];
        if(reaev.events & EPOLLIN && reaev.data.fd==ls_fd)
        {
            OnConnect();
        }
        else if(reaev.events & EPOLLIN)
        {
            OnReadable(reaev.data.fd);
        }
    }
}
//连接请求
void EpollServer::OnConnect()
{
    struct sockaddr_in client;
    socklen_t socklen=sizeof(client);
    bzero(&client,socklen);

    int fd= accept(this->ls_fd,(struct sockaddr*)&client,&socklen);
    if(fd<0)
    {
        printf("accept error\n");
        return ;
    }
    char ip[20]={0};
    int cport=0;
    inet_ntop(AF_INET,&client.sin_addr.s_addr,ip,20);
    cport=ntohs(client.sin_port);
    printf("Client %s:%d connect...\n",ip,cport);
    struct epoll_event event;
    bzero(&event,sizeof(event));
    event.events=EPOLLIN;
    event.data.fd=fd;
    int ret=epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event);
    if(ret<0)
    {
        printf("epoll_ctl add client  error\n");
        return ;
    }

}
//可读事件
void EpollServer::OnReadable(int fd)
{
    char buf[2048]={0};
    int len;
    len=recv(fd,buf,sizeof(buf),0);
    if(len==0)
    {
        printf("Client disconnect\n");
        epoll_ctl(this->epfd,EPOLL_CTL_DEL,fd,NULL);
        close(fd);
        return;
    }
    //客户端发来了报文
    /*此时应该向线程池的任务队列中添加任务*/
    cout<<"recv message from client\n/*******************"<<buf<<endl<<"****************/"<<endl;
}

int EpollServer::Init()
{
    int ret;
    if(port<1)
    {
        puts("tcp port invalid");
        return 2;
    }
    ls_fd = socket(AF_INET,SOCK_STREAM,0);
    if(ls_fd<0)
    {
        perror("socket creat error");
        return 1;
    }
    struct sockaddr_in addr;
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    addr.sin_family = AF_INET;
    addr.sin_port=htons(port);
    int flags=1;
    //设置地址复用
    ret= setsockopt(ls_fd,SOL_SOCKET,SO_REUSEADDR,&flags,sizeof(addr));
    if(ret<0)
    {
        perror("addr reuser error");
        return -1;
    }
    ret= bind(ls_fd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret<0)
    {
        perror("socket bind error");
        return -1;
    }
    ret=listen(ls_fd,SOMAXCONN);
    if(ret<0)
    {
        perror("socket listen error");
        return -2;
    }

    return 0;
}

int EpollServer::Run()
{

    this->epfd=epoll_create(10);
    struct epoll_event event;
    bzero(&event,sizeof(event));
    event.events=EPOLLIN;
    event.data.fd=this->ls_fd;
    epoll_ctl(this->epfd,EPOLL_CTL_ADD,this->ls_fd,&event);

    puts("Start accept....");
    while (1)
    {
        struct epoll_event events[20]={0};
        int count;
        count=epoll_wait(this->epfd,events,20,-1);
        if(count<1)
        {
            perror("epoll wait return error");
            return -1;
        }
        OnEvent(events,count);
    }

    return 0;
}

void EpollServer::SetPort(int p)
{
    this->port=p;
}
EpollServer::~EpollServer()
{

}

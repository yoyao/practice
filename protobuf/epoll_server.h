#ifndef EPOLL_SERVER_H
#define EPOLL_SERVER_H

// EpollServer
class EpollServer
{
public:
    EpollServer();
    ~EpollServer();

protected:
    void OnEvent(struct epoll_event* event,size_t len);
    void OnConnect();
    void OnReadable(int fd);

public:
    int Run();
    int Init();
    void SetPort(int p);

protected:
    //负责监听的描述符
    int ls_fd;
    //epoll描述符
    int epfd;
    //端口
    int port;

};





#endif // EPOLL_SERVER_H

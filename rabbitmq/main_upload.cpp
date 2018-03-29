#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <event.h>
#include <event2/bufferevent.h>
#include <event2/listener.h>
#include <evhttp.h>
#include <event2/http.h>
#include <event2/http_struct.h>
#include <iostream>
#include <json/json.h>

#define LISTEN_PORT 31763
#define READ_BUFF_SIZE (1024*4)

using namespace std;
using namespace Json;

/*
 * typedef void (*evconnlistener_cb)(struct evconnlistener *, evutil_socket_t, struct sockaddr *, int socklen, void *);
*/

typedef struct _transinfo
{
    int fd;
    int datasize;//数据域大小
    int readsize;//已经读取的大小
    char hash[33];
} TranInfo;

void OnClientConnect(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *client, int socket_len, void *arg);
void OnRequest(struct evhttp_request *request,void *arg);
int WorkSaveFile(struct bufferevent *bufev,int fd);

int main_http(int argc, char *argv[])
{
    int lsfd,ret=0;

    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    addr.sin_family=AF_INET;
    addr.sin_port=htons(LISTEN_PORT);
    struct event_base *p_evbase=NULL;
    p_evbase=event_base_new();
    if(p_evbase==NULL)
    {
        perror("create event_base error");
        return 0;
    }
    struct evhttp *p_http=NULL;
    p_http=evhttp_new(p_evbase);
    if(p_http==NULL)
    {
        perror("create evhttp_new error");
        return 0;
    }
    struct evconnlistener *listener=NULL;

    struct evhttp_bound_socket *p_bound_socket=NULL;
    p_bound_socket=evhttp_bind_socket_with_handle(p_http,"0.0.0.0",LISTEN_PORT);

    evhttp_set_gencb(p_http,OnRequest,(void*)p_http);

    //设置特定路径的回调方法
    // evhttp_set_cb(p_http,)

    printf("\nProgram Start........\n\n");
    event_base_dispatch(p_evbase);
    //只接收POST请求
    evhttp_set_allowed_methods(p_http,EVHTTP_REQ_POST);


    evconnlistener_free(listener);
    evhttp_free(p_http);
    event_base_free(p_evbase);
    return 0;
}

void OnRequest(struct evhttp_request *request,void *arg)
{
    //printf("client %s request\n",evhttp_request_get_host(request));
    struct evhttp_connection *p_conn= evhttp_request_get_connection(request);
    char *ip=NULL;
    int port=NULL;
    evhttp_connection_get_peer(p_conn,&ip,(uint16_t*)&port);
    printf("client %s:%d request\n",ip,port);
    //sleep(10);
    struct evbuffer *databuf=evbuffer_new();
    evbuffer_add(databuf,"hello world",11);
    evhttp_send_reply(request,200,"OK",databuf);

}

void OnSockReadable(struct bufferevent *bufev,void *arg);
void OnSockWriteable();
void OnsocketEvent(struct bufferevent *bufev, short events, void *arg);

int main(int argc, char *argv[])
{
    int lsfd,ret=0;
    lsfd=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    addr.sin_family=AF_INET;
    addr.sin_port=htons(LISTEN_PORT);
    struct event_base *p_evbase=NULL;
    p_evbase=event_base_new();
    if(p_evbase==NULL)
    {
        perror("create event_base error");
        return 0;
    }
    struct evconnlistener *listener=NULL;
    listener=evconnlistener_new_bind(p_evbase,OnClientConnect,(void*)p_evbase,LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE,SOMAXCONN,(struct sockaddr*)&addr,sizeof(addr));

    evconnlistener_enable(listener);

    printf("\nProgram Start........\nListening in prot %d\n",port);
    event_base_dispatch(p_evbase);

    evconnlistener_free(listener);
    event_base_free(p_evbase);
    return 0;
}

void OnClientConnect(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *client, int socket_len, void *arg)
{
    struct sockaddr_in *addr=(struct sockaddr_in*)client;
    char ip[24]={0};
    inet_ntop(AF_INET,&addr->sin_addr.s_addr,ip,socket_len);
    printf("client %s:%d connect\n",ip,ntohs(addr->sin_port));
    struct bufferevent *bufev=NULL;
    bufev=bufferevent_socket_new((struct event_base*)arg,fd,BEV_OPT_CLOSE_ON_FREE|EV_PERSIST|EV_ET);
    if(bufev==NULL)
    {
        printf("set bufevent error\n");
        return;
    }
    TranInfo *p_tran=(TranInfo*)calloc(sizeof(TranInfo),1);
    p_tran->fd=-1;
    bufferevent_setcb(bufev,OnSockReadable,NULL,OnsocketEvent,p_tran);
    //只监听读事件
    bufferevent_enable(bufev,EV_READ);

}

void OnSockReadable(struct bufferevent *bufev,void *arg)
{
    int len;
    int datalen=-1;
    int jsonlen=-1;
    int ret=0;
    char buff[READ_BUFF_SIZE]={0};
    char datalen_buf[4]={0};
    char jsonlen_buf[4]={0};
    char *p_json=NULL;

return ;
    TranInfo *p_tran=(TranInfo*)arg;

}

int WorkSaveFile(struct bufferevent *bufev,int fd)
{
    char *p_content=NULL;
    char *p_back=NULL;
    char *p_json=NULL;
    int len;
    int datalen=-1;
    int ret=0;
//先搞到数据 然后上传到fdfs
    return ret;
}

void OnsocketEvent(struct bufferevent *bufev, short events, void *arg)
{
    if(events&BEV_EVENT_EOF)
    {
        printf("client exit\n");
        TranInfo *p_tran=(TranInfo*)arg;
        if(p_tran !=NULL)
        {
            free(p_tran);
        }
        bufferevent_free(bufev);
    }
}

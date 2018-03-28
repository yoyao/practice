/*************************************************************************
    > File Name: main.cpp
    > Author: yoyao
    > Mail: yoyao@126.com
    > Created Time: Fri 23 Mar 2018 06:15:49 PM CST
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <SimpleAmqpClient/SimpleAmqpClient.h>

using namespace std;
using namespace AmqpClient;
/*
我们将称呼我们的消息发布者（publisher）为 Send 和我们的消息接收者(或者消费者)为 Recv 。Send 将连接到RabbitMQ，发送一条消息，然后退出。
消息的发布者 接收者 和 rabbitmq 可以不在一台主机上 其实rabbitmq可以看作是一台转发器,
任何人可以当订阅者  任何人可以当发布者 只要你们定好规则,绑定到rabbitmq集可
*/
int main(int argc,char *argv[])
{

    /*
     * 操作都是幂等的 即只有不存在的时候才会被创建
     */

    std::string exchange="direct_exchange";
    std::string route_key="yesok";
    std::string host="127.0.0.1";
    std::string user="admin";
    std::string pwd="123456";
    std::string vhost="vh_sweet";
    short port=5672;
    std::string msg("hello world");
    std::string queue="direct_queue";

    try
    {
        AmqpClient::Channel::ptr_t pchannel=AmqpClient::Channel::Create(host,port,user,pwd,vhost);

        pchannel->DeclareQueue(queue,false,false,false,false);

        std::string consumer_tag = pchannel->BasicConsume(queue,"",true,true,true,1);
		std::cout<<"\nStart recv message....\n";
		while(1)
		{
        AmqpClient::Envelope::ptr_t penvelope;
        penvelope =pchannel->BasicConsumeMessage(consumer_tag);
        //收到了信息
        std::string message=  penvelope->Message()->Body();
        std::cout<<"recv message:"<<message<<std::endl;
		}	
        //pchannel->BasicAck(penvelope);
    }
    catch(std::exception &ex)
    {
        std::cout<<"exception happend:\n";
        std::cout<<ex.what();
        std::cout<<std::endl;
        return 0;
    }

    return 0;
}

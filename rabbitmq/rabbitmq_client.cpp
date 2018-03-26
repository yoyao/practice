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


/*
[fgo@ali-v-server project]$ openssl req -new -out client/client-req.csr -key client/client-key.pem
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.
-----
Country Name (2 letter code) [AU]:cn
State or Province Name (full name) [Some-State]:beijing
Locality Name (eg, city) []:fengtai
Organization Name (eg, company) [Internet Widgits Pty Ltd]:sky
Organizational Unit Name (eg, section) []:sale
Common Name (e.g. server FQDN or YOUR name) []:sale
Email Address []:123456

Please enter the following 'extra' attributes
to be sent with your certificate request
A challenge password []:123456
An optional company name []:good

 * */


/*
 * 这是创建CA
[fgo@ali-v-server project]$ openssl req -new -out ca/ca-req.csr -key ca/ca-key.pem
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.
-----
Country Name (2 letter code) [AU]:cn
State or Province Name (full name) [Some-State]:beijing
Locality Name (eg, city) []:fengtai
Organization Name (eg, company) [Internet Widgits Pty Ltd]:sweetour
Organizational Unit Name (eg, section) []:lucky
Common Name (e.g. server FQDN or YOUR name) []:root
Email Address []:sky

Please enter the following 'extra' attributes
to be sent with your certificate request
A challenge password []:123456
An optional company name []:fly

 * */


/*
 *这是创建服务器的证书
Country Name (2 letter code) [AU]:cn
State or Province Name (full name) [Some-State]:beijing
Locality Name (eg, city) []:fengtai
Organization Name (eg, company) [Internet Widgits Pty Ltd]:sweetour
Organizational Unit Name (eg, section) []:lucky
Common Name (e.g. server FQDN or YOUR name) []:47.93.50.121
Email Address []:123456@qq.com

Please enter the following 'extra' attributes
to be sent with your certificate request
A challenge password []:123456
An optional company name []:luckytour
 * /
int main(int argc,char *argv[])
{

    /*
     * 操作都是幂等的 即只有不存在的时候才会被创建
     */
int main(int argc,char *argv[])
{
    std::string exchange="direct_exchange";
    std::string route_key="yesok";
    std::string host="47.93.50.121";
    //host="127.0.0.1";
    std::string user="admin";
    std::string pwd="123456";
    std::string vhost="vh_sweet";
    short port=5671;
    std::string msg("hello world");
    std::string queue="direct_queue";
    std::string cacert_path="/home/fgo/program/ca.crt";

    std::string client_key_path="/home/fgo/program/client-cert.crt";
    std::string client_cert_path="/home/fgo/program/client-private.key";

    try
    {
        //AmqpClient::Channel::ptr_t pchannel=AmqpClient::Channel::Create(host,port,user,pwd,vhost);
         AmqpClient::Channel::ptr_t pchannel=AmqpClient::Channel::CreateSecure(cacert_path,host,client_key_path,client_cert_path,port,user,pwd,vhost);

        pchannel->DeclareQueue(queue,true,true);
        AmqpClient::BasicMessage::ptr_t pmsg=AmqpClient::BasicMessage::Create(msg);
        pchannel->BasicPublish(exchange,route_key,AmqpClient::BasicMessage::Create(msg));

    }
    catch(std::exception &ex)
    {
        std::cout<<"exception happend:\n";
        std::cout<<ex.what();
        std::cout<<std::endl;
        return 0;
    }

    std::cout<<"sent message:"<<msg<<std::endl;

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include "epoll_server.h"

using namespace std;

int main(int argc,char *argv[])
{
EpollServer server;

server.SetPort(29781);
server.Init();

server.Run();


return 0;
}

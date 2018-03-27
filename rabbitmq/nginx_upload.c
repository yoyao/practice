#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fastcgi.h>
#include <fcgi_stdio.h>


int main(int argc,char *argv[])
{
    int count=0;
    while (FCGI_Accept() >= 0)
    {
        printf("Content-type: text/html\r\n"
               "\r\n"
               ""
               "FastCGI Hello!"
               "Request number %d running on host:%s "
               "Request Method:%s "
               "Process ID: %d\n", ++count, getenv("SERVER_NAME"), getenv("REQUEST_METHOD"), getpid());
    }
    return 0;
}


/*************************************************************************
  > File Name: https_conn.cpp
  > Author: yoyao
  > Mail: yoyao@126.com
  > Created Time: Mon 26 Mar 2018 02:16:03 PM CST
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define HOSTNAME_VERIFICATION 0
#define PEER_VERIFICATION 1

#define FALSE 0L
#define TRUE 1L

size_t write_callback( void *ptr, size_t size, size_t nmemb, void *stream );


int main(int argc,char *argv[])
{
    if(argc<3)
    {
        std::cout<<"input ip:port\n";
        return 0;
    }

    std::string ip=argv[1];
    short   port=atoi(argv[2]);
    std::string url("https://");
    url+=ip;
    url+=":";
    url+=argv[2];
    url+="/first.html";
    std::cout<<"connect to "<<url<<std::endl;

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    do
    {
        if(!curl)
        {
            std::cout<<"curl init error\n";
            break;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
         curl_easy_setopt(curl, CURLOPT_POST, FALSE); // post req
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST,FALSE );
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);//忽略证书检查
#if PEER_VERIFICATION
        /*
             If you want to connect to a site who isn't using a certificate that is signed by one of the certs in the CA bundle you have, you can skip the verification of the server's certificate. This makes the connection A LOT LESS SECURE.
             If you have a CA cert for the server stored someplace else than in the default bundle, then the CURLOPT_CAPATH option might come handy for you.
             */

        /* 双向验证下面是客户端的ＣＡ*/
        // 配置 https 请求所需证书
        curl_easy_setopt(curl,CURLOPT_CAINFO,"/home/fgo/program/ca/ca.crt");
        curl_easy_setopt(curl, CURLOPT_SSLCERT, "/home/fgo/program/client/clientcert.pem");
        curl_easy_setopt(curl,CURLOPT_SSLCERTTYPE,"PEM");
        curl_easy_setopt(curl,CURLOPT_SSLKEYPASSWD,"123456");
        curl_easy_setopt(curl, CURLOPT_SSLKEY, "/home/fgo/program/client/client-private.key");
        curl_easy_setopt(curl,CURLOPT_SSLKEYTYPE,"PEM");
        curl_easy_setopt(curl, CURLOPT_KEYPASSWD, "123456");

#else

#endif

#if  HOSTNAME_VERIFICATION
        /*
                If the site you're connecting to uses a different host name that what
                they have mentioned in their server certificate's commonName (or subjectAltName) fields,
                libcurl will refuse to connect. You can skip this check, but this will make the connection less secure.
             */
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
        //设置回调
        curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, write_callback);
        //这个变量可作为接收或传递数据的作用
        curl_easy_setopt( curl, CURLOPT_WRITEDATA, NULL );
        /* Now specify the POST data */
       // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
        }

    }while(0);


    /* always cleanup */
    curl_easy_cleanup(curl);


    curl_global_cleanup();


    return 0;
}




//这是libcurl接收数据的回调函数，相当于recv的死循环
//其中stream可以自定义数据类型，这里我传入的是文件保存路径
size_t write_callback( void *ptr, size_t size, size_t nmemb, void *stream )
{
    int len = size * nmemb;
    int written = len;
    std::cout<<"response html\n"<<reinterpret_cast<char*>(ptr);
    return written;
}

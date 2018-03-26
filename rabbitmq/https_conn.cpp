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

#define SKIP_HOSTNAME_VERIFICATION 1
#define SKIP_PEER_VERIFICATION 1

int main(int argc,char *argv[])
{
	if(argc<3)
	{
		std::cout<<"input ip:port\n";
		return 0;
	}

	std::string ip=argv[1];
	short     port=atoi(argv[2]);

	std::cout<<"connect to "<<ip<<":"<<port<<std::endl;

	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://example.com/");

#if SKIP_PEER_VERIFICATION
		/*
		 If you want to connect to a site who isn't using a certificate that is signed by one of the certs in the CA bundle you have, you can skip the verification of the server's certificate. This makes the connection A LOT LESS SECURE.
		 If you have a CA cert for the server stored someplace else than in the default bundle, then the CURLOPT_CAPATH option might come handy for you.
		 */ 
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
		/*
		    If the site you're connecting to uses a different host name that what
		    they have mentioned in their server certificate's commonName (or subjectAltName) fields, 
			libcurl will refuse to connect. You can skip this check, but this will make the connection less secure.
		 */ 
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

		/* Perform the request, res will get the return code */ 
		res = curl_easy_perform(curl);
		/* Check for errors */ 
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));

		/* always cleanup */ 
		curl_easy_cleanup(curl);

	}

	curl_global_cleanup();


	return 0;
}

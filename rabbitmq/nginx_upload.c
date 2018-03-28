#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fastcgi.h>
#include <fcgi_stdio.h>

extern  char** environ;

int main(int argc,char *argv[])
{
	int count=0;
	while (FCGI_Accept() >= 0)
	{
		printf("Content-type: text/html\r\n"
				"\r\n"
				""
				"FastCGI Hello!<br/>"
				"Request number %d running on host:%s <br/>"
				"Request Method:%s <br/>"
				"Process ID: %d <br/>", ++count, getenv("SERVER_NAME"), getenv("REQUEST_METHOD"), getpid());


		const char *file_name=getenv("file_name");
		const char *file_size=getenv("file_size");
		const char *file_md5=getenv("file_md5");
		const char *file_path=getenv("_tmp_path");
		if(NULL==file_name)
		{
			file_name="None";
		}
		if(NULL==file_size)
		{
			file_size="None";
		}
		if(NULL==file_md5)
		{
			file_md5="None";
		}
		if(NULL==file_path)
		{
			file_path="None";
		}
		printf("file path:%s <br/>"
				"file name:%s <br/>"
				"file size:%s <br/>"
				"file MD5:%s <br/>",file_path,file_name,file_size,file_md5);

		if(environ ==NULL)
		{
			return 0;
		}
		const char **env =environ;

		while(*env !=NULL)
		{
			   printf("%s <br/>",*env);
			      env++;
				    
		}
	}
	return 0;
}


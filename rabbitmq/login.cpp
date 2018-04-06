
#include <stdlib.h>
#include <unistd.h>
#include <cstdio>
#include <map>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>
#include <fcgio.h>
#include <fcgi_config.h>  // HAVE_IOSTREAM_WITHASSIGN_STREAMBUF

using namespace std;

void ParseForm(std::string formstr, std::string &boundary);
void BuildPair(std::string &prstr,std::map<std::string,std::string> *result);

// Maximum number of bytes allowed to be read from stdin

extern char ** environ;
#define  STDIN_MAX 1000000

static void penv(const char * const * envp)
{
	cout << "<PRE>\n";
	for ( ; *envp; ++envp)
	{
		cout << *envp << "\n";
	}
	cout << "</PRE>\n";
}

static long gstdin(FCGX_Request * request, char ** content)
{
	char * clenstr = FCGX_GetParam("CONTENT_LENGTH", request->envp);
	unsigned long clen = STDIN_MAX;

	if (clenstr)
	{
		clen = strtol(clenstr, &clenstr, 10);
		if (*clenstr)
		{
			cerr << "can't parse \"CONTENT_LENGTH="
				<< FCGX_GetParam("CONTENT_LENGTH", request->envp)
				<< "\"\n";
			clen = STDIN_MAX;
		}

		// *always* put a cap on the amount of data that will be read
		if (clen > STDIN_MAX) clen = STDIN_MAX;

		*content = new char[clen];

		cin.read(*content, clen);
		clen = cin.gcount();
	}
	else
	{
		// *never* read stdin when CONTENT_LENGTH is missing or unparsable
		*content = 0;
		clen = 0;
	}

	// Chew up any remaining stdin - this shouldn't be necessary
	// but is because mod_fastcgi doesn't handle it correctly.

	// ignore() doesn't set the eof bit in some versions of glibc++
	// so use gcount() instead of eof()...
	do 
	{
		cin.ignore(1024);
	}
	while (cin.gcount() == 1024);

	return clen;
}




int main (int argc,char *argv[])
{

	streambuf * cin_streambuf  = cin.rdbuf();
	streambuf * cout_streambuf = cout.rdbuf();
	streambuf * cerr_streambuf = cerr.rdbuf();

	FCGX_Request request;

	FCGX_Init();
	FCGX_InitRequest(&request, 0, 0);

	while (FCGX_Accept_r(&request) == 0)
	{
		fcgi_streambuf cin_fcgi_streambuf(request.in);
		fcgi_streambuf cout_fcgi_streambuf(request.out);
		fcgi_streambuf cerr_fcgi_streambuf(request.err);


		cin.rdbuf(&cin_fcgi_streambuf);
		cout.rdbuf(&cout_fcgi_streambuf);
		cerr.rdbuf(&cerr_fcgi_streambuf);


		cout << "Content-type: text/html\r\n"
			"\r\n";

		std::cout<<R"({"username":"Luffy","passwd":"123456"})"<<std::endl;

	}

	cin.rdbuf(cin_streambuf);
	cout.rdbuf(cout_streambuf);
	cerr.rdbuf(cerr_streambuf);

	return 0;

}







void BuildPair(std::string &prstr,std::map<std::string,std::string> *result)
{
	regex reg1("\"([^\"]*)\"");
	string s1 = prstr;

	std::string::size_type pos = s1.find_first_of(' ');

	std::string value = s1.substr(pos + 1);

	smatch r1;
	regex_search(s1, r1, reg1);
	std::string rstr=r1.str();

	if (rstr.length() > 0)
	{
		rstr.erase(rstr.begin());
		rstr.erase(rstr.end()-1);

	}
	result->insert(make_pair(rstr, value));

}

void ParseForm(std::string formstr, std::string &boundary)
{
	std::vector<std::string> vec_pair;
	int blen = boundary.length();
	while (true)
	{
		std::string::size_type pos = formstr.find(boundary);
		if (pos == std::string::npos)
		{
			break;

		}
		std::string pair = formstr.substr(0, pos);
		if (pair.length() > 2)
		{
			vec_pair.push_back(pair);

		}
		formstr = formstr.substr(blen + pair.length());

	}

	for_each(vec_pair.begin(), vec_pair.end(), [&](std::string &str){
			//strTrim(&str);
			std::map<std::string, std::string> pair_result;
			BuildPair(str, &pair_result);

			std::map<std::string, std::string>::iterator it = pair_result.begin();
			for (it=pair_result.begin(); it != pair_result.end(); ++it)
			{
			std::cout << "   Key:*" << it->first << "*   Value:*" << it->second << "*"<<std::endl;

			}


			});


}

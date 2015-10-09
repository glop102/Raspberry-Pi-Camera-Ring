#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string>
#include "../libs/stdSocketTools.h"
#ifndef webServerWrapper
#define webServerWrapper

/*
This library handles talking with a web browser
This assumes reading the header is to be passed in
*/

class buffer;
void engageBrowser(int socketFD,std::string header);
std::string getRequestedPage(std::string header);
void sendHTMLFile(int socketFD,std::string request);
buffer replaceSymbols(buffer input);

class buffer{
public:
	char* buf;
	unsigned int length;
	~buffer();
	buffer();
	buffer(char);
	buffer(char*);
	buffer(const buffer&);
	buffer(const std::string&);
	void clear();
	void operator+=(char);
	void operator+=(const char*);
	void operator+=(const buffer&);
	void append(const char*,unsigned int);
	void operator+=(std::string);
	void operator=(const buffer&);
	void operator=(buffer*);
	void operator=(char);
	void operator=(const char*);
	void operator=(std::string);
};

#endif
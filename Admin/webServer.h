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
#include "../libs/buffer.h"
#ifndef webServerWrapper
#define webServerWrapper

/*
This library handles talking with a web browser
engageBrowser if the first function called
it starts by getting the requested URL
it then checks to see if the URL is hardcoded to do something
	If it is hardcodded to do something - does that
	default - load file from the www directory relative to where it is executed
*/

void engageBrowser(int socketFD,std::string header);
std::string getRequestedPage(std::string header); //gets the requested URL from the header passed in
void sendHTMLFile(int socketFD,std::string request); //sends a file from the filesystem
buffer replaceSymbols(buffer input); //replaces speacial symbols with special information before letting it be sent to the browser

#endif
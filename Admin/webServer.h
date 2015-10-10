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
This assumes reading the header is to be passed in
*/

void engageBrowser(int socketFD,std::string header);
std::string getRequestedPage(std::string header);
void sendHTMLFile(int socketFD,std::string request);
buffer replaceSymbols(buffer input);

#endif
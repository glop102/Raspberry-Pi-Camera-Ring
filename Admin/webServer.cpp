#include "webServer.h"

void engageBrowser(int socketFD,std::string header){
	std::string cannedResponse="HTTP/1.1 200 OK\n\r\n\r<html><body><h1>Hello There</h1></body></html>\n\r";
    int charsWriten=write(socketFD,cannedResponse.c_str(),cannedResponse.length());
    if(charsWriten<0) printf("Unable to write socket");
    close(socketFD);
}
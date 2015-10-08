#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../libs/stdSocketTools.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char** args){
	int listenFD=simpleOpenListenSocket(63036);
	if(listenFD<0){
		printf("UNABLE to open socket\n");
		exit(1);
	}

	char buffer[256];
	while(1){
		struct newConnectionInfo peer = simpleAccept(listenFD);
		int newSockFD = peer.FD; //get the FD of the new client connection
		if (newSockFD < 0) 
	          error("ERROR on accept");
	    bzero(buffer,256); //make our buffer full of zeros
	    printf("\n\n=== New Connection ===\n%s\n\n\n",peer.address);

	    int charsRead=1;
	    while(charsRead>=1){
	    	bzero(buffer,256); //make our buffer full of zeros
		    charsRead=read(newSockFD,buffer,255);//read the message
		    if(charsRead<0) error("Unable to read socket");
		    printf("%s\n", buffer);
		    if(charsRead>=4 && strstr(buffer,"exit")!=NULL){ //exit program
		    	printf("Caught exit command\n");
		    	close(listenFD);
		    	close(newSockFD);
		    	exit(0);
		    }
		    if((charsRead>=4 && strstr(buffer,"\r\n\r\n")!=NULL) || (charsRead>=1 && buffer[1]==0)){ //break read loop and continue program
		    	break;
		    }
		}
		printf("\n\n=== Writing ===\n\n");

		std::string cannedResponse="HTTP/1.1 200 OK\n\r\n\r<html><body><h1>Hello There</h1></body></html>\n\r";
	    charsRead=write(newSockFD,cannedResponse.c_str(),cannedResponse.length());
	    if(charsRead<0) error("Unable to write socket");
	    close(newSockFD);
	}

	printf("Exiting\n");
	close(listenFD);

	return 0;
}
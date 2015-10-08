#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../libs/stdSocketTools.h"
#include "webServer.h"
#include "raspiControlSystem.h"

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

	char buf;
	while(1){
		struct newConnectionInfo peer = simpleAccept(listenFD);
		int newSockFD = peer.FD; //get the FD of the new client connection
		if (newSockFD < 0) 
	          error("ERROR on accept");
	    printf("\n\n=== New Connection ===\n%s\n\n\n",peer.address);

	    int charsRead=1;
	    std::string header;
	    while(charsRead){
		    charsRead=read(newSockFD,&buf,1);//read the message
		    if(charsRead<0) error("Unable to read socket");
		    printf("%c", buf);
		    header+=buf;

		    int headerLength=header.length();
		    if(headerLength<5) continue;
		    if(header.substr(headerLength-4) == "\r\n\r\n"){
		    	//found the end of the header of the newly connected client
		    	//now lets break so that we can analyze what we need to do
		    	break;
		    }
		}
		printf("\n\n=== Writing ===\n\n");

		if(header.substr(0,3)=="GET")
			engageBrowser(newSockFD,"");
		if(header.substr(0,5)=="RASPI")
			raspiConnection(peer,header);
	}

	printf("Exiting\n");
	close(listenFD);

	return 0;
}
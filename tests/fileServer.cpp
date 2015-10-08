#include <stdlib.h>
#include <stdio.h>
#include "../libs/fileSave.h"
#include "../libs/stdSocketTools.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}
int main(){
	int port=63036;
	int listenFD;

	listenFD = simpleOpenListenSocket(port);
	if(listenFD<0){
		error("UNABLE to open socket\n");
	}

	struct sockaddr_in cli_addr;
	socklen_t clientLength = sizeof(cli_addr);//size of the struct
	listen(listenFD,5); //start listening so that we can get new connections
	char buffer[256];

	while(1){
		int newSockFD = accept(listenFD, (struct sockaddr *) &cli_addr, &clientLength); //get the FD of the new client connection
		if (newSockFD < 0) 
	          error("ERROR on accept");
	    printf("=== New Conenction ===\n");
	    saveFile(newSockFD);
	}

	printf("Exiting\n");
	close(listenFD);

	return 0;
}
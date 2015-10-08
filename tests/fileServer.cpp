#include <stdlib.h>
#include <stdio.h>
#include "../libs/fileSave.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}
int main(){
	int port=63036;
	socklen_t clientLength;
	struct sockaddr_in serv_addr, cli_addr;
	int listenFD;

	listenFD = socket(AF_INET, SOCK_STREAM, 0); //voodoo line 1
	if (listenFD < 0) 
        error("ERROR opening socket");
    serv_addr.sin_family = AF_INET; //internet domain, not unix domain
	serv_addr.sin_addr.s_addr = INADDR_ANY; //allow us to listen to all interfaces
	serv_addr.sin_port = htons(port); //change order of the bytes from the host specific to the network order (so dont worry about Big or Little endian)
	if (bind(listenFD, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		error("ERROR on binding");

	listen(listenFD,5); //start listening so that we can get new connections
	clientLength = sizeof(cli_addr); //size of the struct
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
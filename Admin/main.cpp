#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char* args){
	int port=63036;
	socklen_t clientLength;
	struct sockaddr_in serv_addr, cli_addr;
	int listenFD;
	int newFD;

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
	    bzero(buffer,256); //make our buffer full of zeros
	    printf("\n\n=== New Connection ===\n\n\n");

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

	    charsRead=write(newSockFD,"Hello There\n\r",13);
	    if(charsRead<0) error("Unable to write socket");
	    close(newSockFD);
	}

	printf("Exiting\n");
	close(listenFD);

	return 0;
}
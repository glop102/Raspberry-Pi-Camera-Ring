#include <string>
#include "../libs/stdSocketTools.h"
#include "../libs/fileSend.h"

int main(int argc,char**args){
	if(argc<3){
		printf("Insuficent Parameters\n");
		printf("%s   hostname   filepath\n",args[0]);
	}

	int port=63036;
	int socketFD;
	socketFD = simpleOpenSocket();
	if(socketFD<0){
		printf("UNABLE to open socket\n");
		exit(1);
	}

	sendFile(socketFD,args[1],port,args[2]);
	close(socketFD);
	return 0;
}
#include "../libs/stdSocketTools.h"
#include "../libs/fileSend.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

int main(int argc, char const *args[]){
	int socketFD = simpleConnectToHost("127.0.1.2",63036);
	if(socketFD<0){
		printf("ERROR opening socket\n");
		exit(1);
	}
	//char header[]="RASPI CAMERA\r\nREPORTING\r\n\r\n";
	char header[]="RASPI CAMERA\r\nIMAGE SEND\r\n\r\n";
	write(socketFD,header,strlen(header));
	sendFileAlreadyConnected(socketFD,"127.0.0.1",63036,"../Examples/1430098684987.png");
	close(socketFD);

	return 0;
}
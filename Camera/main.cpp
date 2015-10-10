#include "../libs/stdSocketTools.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

int main(int argc, char const *args[]){
	int socketFD = simpleConnectToHost("127.0.1.2",63036);
	if(socketFD<0){
		printf("ERROR opening socket\n");
		exit(1);
	}
	char header[]="RASPI CAMERA\r\n\r\n";
	write(socketFD,header,strlen(header));

	return 0;
}
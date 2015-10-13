#include "../libs/stdSocketTools.h"
#include "../libs/fileSend.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void firstConnect(){
	int socketFD = simpleConnectToHost("192.168.1.1",63036);
	while(socketFD<0){
		sleep(5); //5 seconds
		socketFD=simpleConnectToHost("192.168.1.1",63036);
	}
	char header[]="RASPI CAMERA\r\nREPORTING\r\n\r\n";
	write(socketFD,header,strlen(header));
	close(socketFD);
}

int main(int argc, char const *args[]){
	system("");
	firstConnect(); //connect to the admin to say that we are here

	

	return 0;
}
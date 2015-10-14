#include "../libs/stdSocketTools.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	int socketFD=simpleOpenSocket_UDP(63036);
	while(1){
		struct newConnectionInfo peer = listen_UDP(socketFD);
		printf("Got A Hit\n%s\n%s\n",peer.address,peer.message.c_str());
	}
	close(socketFD);
	return 0;
}
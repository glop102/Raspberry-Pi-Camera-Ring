#include "../libs/stdSocketTools.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	//int socketFD=simpleOpenSocket_UDPBroadcast(63036);
	int socketFD=simpleOpenSocket_UDP(63036);
	//send_UDP(socketFD,63036,"10.42.0.44","This Is It.");
	send_UDP(socketFD,63036,"255.255.255.255","This Is It.");
	//sendBroadcast_UDP(socketFD,63036,"This Is It.");
	close(socketFD);
	return 0;
}
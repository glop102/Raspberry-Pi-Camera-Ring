#include "../libs/stdSocketTools.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	//int socketFD=simpleOpenSocket_UDPBroadcast(63036);
	int socketFD=simpleOpenSocket_UDP(63036);
	send_UDP(socketFD,63036,"10.42.0.44","Regulat");
	send_UDP(socketFD,63036,"255.255.255.255","All Cast");
	sendBroadcast_UDP(socketFD,63036,"Broadcast");
	close(socketFD);
	return 0;
}
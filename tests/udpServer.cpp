#include "../libs/stdSocketTools.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	int socketFD=simpleOpenSocket_UDPBroadcast(63036);
	send_UDP(socketFD,63036,"10.42.0.44","This Is It.");
	close(socketFD);
	return 0;
}
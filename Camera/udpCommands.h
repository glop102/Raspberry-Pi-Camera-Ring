#ifndef __UDPCOMMANDS
#define __UDPCOMMANDS

#include <stdio.h>
#include "../libs/stdSocketTools.h"
#include "globals.h"
#include "cameraCommands.h"

void* recieveUDPCommands(void* nada); //thread starts here
extern void reportToAdmin(std::string adminAddress);

void* recieveUDPCommands(void* nada){
	int socketFD = simpleOpenSocket_UDP(63036);
	struct newConnectionInfo peer;
	while(1){
		peer=listen_UDP(socketFD);
		if(peer.message=="ADMIN ANNOUNCE"){//admin reporting
			reportToAdmin(adminAddress);
		}else if(peer.message=="IMAGE CAPTURE"){
			bufferQueue.add(takeImage);
		}
	}
	close(socketFD); //just in case we somehow end up here
}

#endif
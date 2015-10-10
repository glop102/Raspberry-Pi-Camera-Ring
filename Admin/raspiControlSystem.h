#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string>
#include <vector>
#include "../libs/stdSocketTools.h"
#include "../libs/threadSafeList.h"
#ifndef raspiControlSystem
#define raspiControlSystem

/*
The new connection is found to be a Raspberry PI
This is found by looking at the header of the messsage
The socket of the new connection is passed here along with the header
*/

void raspiConnection(struct newConnectionInfo peer,std::string header);
void downloadFile(struct newConnectionInfo peer);

struct PI_INFO
{
	std::string address;
	std::string role; //Camera, Projector, etc
	bool operator==(const PI_INFO& other){
		return this->address==other.address;
	}
};

#endif

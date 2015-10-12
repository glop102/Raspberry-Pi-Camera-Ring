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
#include <dirent.h>
#include "../libs/stdSocketTools.h"
#include "../libs/threadSafeList.h"
#include "../libs/fileSave.h"
#ifndef raspiControlSystem
#define raspiControlSystem

/*
The new connection is found to be a Raspberry PI
This is found by looking at the header of the messsage
The socket of the new connection is passed here along with the header

CALL raspiConnection FIRST - the logic spreads from there
*/

void raspiConnection(struct newConnectionInfo peer,std::string header);
void downloadImage(struct newConnectionInfo peer); //command was to download image
std::vector<std::string> listDirectoryContents(std::string);
std::vector<std::string> sortContents(std::vector<std::string>);
int stringDifference(std::string,std::string);
//void sendCaptureCommand_All(); //each socket connection needs to be in a new thread so that there is less time between the call and it happening
//void sendRebootCommand(std::string address);
//void sendVideoRestartCommand(std::string address);

struct PI_INFO
{
	std::string address;
	std::string role; //Camera, Projector, etc
	bool operator==(const PI_INFO& other){
		return this->address==other.address;
	}
};

extern threadSafeList<PI_INFO> globalIPList; //global list of PIs that have reported to the admin
	//NOTE: this list is global so that the webserver can use it to send commands when the client says to

#endif

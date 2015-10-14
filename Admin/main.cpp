#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "../libs/stdSocketTools.h"
#include "webServer.h"
#include "raspiControlSystem.h"
#include "globalVarInit.h"

void* spawnThread(void* peer){
	int newSockFD=((struct newConnectionInfo*)peer)->FD;

	char buf;
	int charsRead=1;
    std::string header;
    while(charsRead){
	    charsRead=read(newSockFD,&buf,1);//read the message
	    if(charsRead<0){
	    	printf("Unable to read socket\n");
	    	exit(0);
	    }
	    header+=buf;

	    int headerLength=header.length();
	    if(headerLength<5) continue;
	    if(header.substr(headerLength-4) == "\r\n\r\n"){
	    	//found the end of the header of the newly connected client
	    	//now lets break so that we can analyze what we need to do
	    	break;
	    }
	}
	//printf("\n\n=== Writing ===\n\n");

	if(header.substr(0,3)=="GET")
		engageBrowser(newSockFD,header);
	if(header.substr(0,4)=="POST")
		engageBrowser(newSockFD,header);
	if(header.substr(0,5)=="RASPI")
		raspiConnection(*(struct newConnectionInfo*)peer,header);

	//note: do not close the socket here
	//the functions we pass to are supposed to close them
	delete (struct newConnectionInfo*)peer;
}

void* constantAnnounce(void* data){
	int socketFD=simpleOpenSocket_UDPBroadcast(63036);
	while(1){
		sleep(3); //only announce every 3 seconds
		sendBroadcast_UDP(socketFD,63036,"ADMIN ANNOUNCE");
		send_UDP(socketFD,63036,"10.42.0.44","ADMIN ANNOUNCE");
		printf("Sending Broadcast\n");
	}
}

int main(int argc, char** args){
	int listenFD=simpleOpenListenSocket(63036);
	if(listenFD<0){
		printf("UNABLE to open socket\n");
		exit(1);
	}
	pthread_t threadFD;
	pthread_create(&threadFD,NULL,constantAnnounce,NULL);

	while(1){
		struct newConnectionInfo* peer=new struct newConnectionInfo;
		*peer = simpleAccept(listenFD);

		int newSockFD = peer->FD; //get the FD of the new client connection
		if (newSockFD < 0)
	          printf("ERROR on accept");
	    printf("=== New Connection ===\n%s\n",peer->address);

		pthread_create(&threadFD,NULL,spawnThread,peer);
	}

	printf("Exiting\n");
	close(listenFD);

	return 0;
}
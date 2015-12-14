#ifndef __TCPCOMMANDS
#define __TCPCOMMANDS

#include <stdio.h>
#include "globals.h"
#include "cameraCommands.h"

void* recieveTCPCommands(void* nada); //thread starts here
std::string getHeader(int socketFD);  // gets the tcp header that holds the command
void sendImageBack(std::string adminAddress); //sends the file output.png to the admin server

void* recieveTCPCommands(void* nada){ //thread starts here
	int listenFD = simpleOpenListenSocket(63036);
	printf("Accepting Commands\n");
	while(1){
		struct newConnectionInfo newConc = simpleAccept(listenFD);
		std::string header=getHeader(newConc.FD);
		printf("%s\n", header.c_str());
		if(header=="RASPI ADMIN\r\nIMAGE TAKE\r\n\r\n"){
			//takeImage_toFile();
			//sendImageBack(adminAddress);
			bufferQueue.add(takeImage());
		}else if(header=="RASPI ADMIN\r\nREBOOT\r\n\r\n"){
			system("sudo reboot");
		}else if(header=="RASPI ADMIN\r\nUPDATE\r\n\r\n"){
			system("git pull");
			system("make");
			system("sudo reboot");
		}
		close(newConc.FD);
	}
}

std::string getHeader(int socketFD){
	char buf;
	int charsRead=1;
    std::string header;
    while(charsRead){
	    charsRead=read(socketFD,&buf,1);//read the message
	    if(charsRead<0){
	    	printf("Unable to read socket\n");
	    	return ""; //default to safety
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
	return header;
}

void sendImageBack(std::string adminAddress){
	//printf("sending file back\n");
	int socketFD = simpleConnectToHost(adminAddress,63036);
	std::string header="RASPI CAMERA\r\nIMAGE SEND\r\n\r\n";
	write(socketFD,header.c_str(),header.length());
	sendFileAlreadyConnected(socketFD,"output.png");
}

#endif

#include "../libs/stdSocketTools.h"
#include "../libs/fileSend.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include "globals.h"
#include "udpCommands.h"
#include "tcpCommands.h"
#include "cameraCommands.h"

std::string findAdmin(){
	int socketFD = simpleOpenSocket_UDP(63036);
	struct newConnectionInfo peer;
	while(1){
		peer=listen_UDP(socketFD);
		if(peer.message=="ADMIN ANNOUNCE") break; //we found the admin
		printf("\t%s\n", peer.message.c_str());
	}
	close(socketFD);
	return peer.address;
}

void reportToAdmin(std::string adminAddress){
	int socketFD = simpleConnectToHost(adminAddress,63036);
	//printf("%d\n", socketFD);
	while(socketFD<=0){
		printf("Failed to report to admin\n");
		sleep(2);
		socketFD=simpleConnectToHost(adminAddress,63036);
	}
	std::string header="RASPI CAMERA\r\nREPORTING\r\n\r\n";
	//printf("Chars Sent To Admin:  %lu\n",write(socketFD,header.c_str(),header.length()) );
	write(socketFD,header.c_str(),header.length());
	close(socketFD);
}

void setupCamera(raspicam::RaspiCam &cam){
	cam.setCaptureSize(2560 , 1920); //max size
	cam.setFormat(raspicam::RASPICAM_FORMAT_RGB);
	cam.setAWB(raspicam::RASPICAM_AWB_AUTO);
	if(!cam.open()){
		printf("Unable to open Camera\n");
		exit(1);
	}
}

int main(int argc, char const *args[]){
	//raspicam::RaspiCam still;
	setupCamera(cam);

	adminAddress=findAdmin();
	printf("Admin Address %s\n",adminAddress.c_str());
	reportToAdmin(adminAddress); //connect to the admin to say that we are here

	pthread_t threadFD;
	pthread_create(&threadFD,NULL,recieveTCPCommands,NULL); //start the tcp command system
	pthread_create(&threadFD,NULL,recieveUDPCommands,NULL); //start the udp command system
	pthread_create(&threadFD,NULL,encodingQueueThread,NULL); //start the encoding thread

	while(1){sleep(1);}

	printf("\nProgram Finished\n\n");

	return 0;
}

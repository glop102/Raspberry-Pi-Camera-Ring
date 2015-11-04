#include "../libs/stdSocketTools.h"
#include "../libs/fileSend.h"
#include "raspicam/src/raspicam_still.h"
#include "raspicam/src/raspicam.h"
#include "raspicam/src/raspicamtypes.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>

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

void takeImage(raspicam::RaspiCam_Still &cam){
	// puts into output.png
	// no preview on screen
	// waits 900 milliseconds to capture
	// the camera seems to need time to warm up
	//system("raspistill -o output.png -e png --nopreview --timeout 900");

	//new method that is faster, a lot faster
	size_t bufSize = cam.getImageBufferSize();
	unsigned char* buf = (unsigned char*)malloc(bufSize);
	cam.grab_retrieve(buf,bufSize);

	FILE* of = fopen("output.png","wb");
	fwrite(buf,1,bufSize,of);
	fclose(of);

	cam.release();
	free(buf);
}
void sendImageBack(std::string adminAddress){
	int socketFD = simpleConnectToHost(adminAddress,63036);
	std::string header="RASPI CAMERA\r\nIMAGE SEND\r\n\r\n";
	write(socketFD,header.c_str(),header.length());
	sendFileAlreadyConnected(socketFD,"output.png");
}
void reportToAdmin(std::string adminAddress){
	int socketFD = simpleConnectToHost(adminAddress,63036);
	//printf("%d\n", socketFD);
	while(socketFD<=0){
		printf("Failed to report to admin\n");
		sleep(5);
		socketFD=simpleConnectToHost(adminAddress,63036);
	}
	std::string header="RASPI CAMERA\r\nREPORTING\r\n\r\n";
	//printf("Chars Sent To Admin:  %lu\n",write(socketFD,header.c_str(),header.length()) );
	write(socketFD,header.c_str(),header.length());
	close(socketFD);
}

void setupCamera(raspicam::RaspiCam_Still &still){
	still.setEncoding(raspicam::RASPICAM_ENCODING_PNG);
	still.setCaptureSize(2592 , 1944); //max size
	if(!still.open()){
		printf("Unable to open Camera\n");
		exit(1);
	}
}

int main(int argc, char const *args[]){
	raspicam::RaspiCam_Still still;
	setupCamera(still);

	std::string adminAddress=findAdmin();
	printf("Admin Address %s\n",adminAddress.c_str());
	reportToAdmin(adminAddress); //connect to the admin to say that we are here

	int listenFD = simpleOpenListenSocket(63036);
	printf("Accepting Commands\n");
	while(1){
		struct newConnectionInfo newConc = simpleAccept(listenFD);
		std::string header=getHeader(newConc.FD);
		printf("%s\n", header.c_str());
		if(header=="RASPI ADMIN\r\nIMAGE TAKE\r\n\r\n"){
			takeImage(still);
			sendImageBack(adminAddress);
		}else if(header=="RASPI ADMIN\r\nREBOOT\r\n\r\n"){
			system("sudo reboot");
		}else if(header=="RASPI ADMIN\r\nUPDATE\r\n\r\n"){
			system("git pull");
			system("make");
			system("sudo reboot");
		}
		close(newConc.FD);
	}

	return 0;
}

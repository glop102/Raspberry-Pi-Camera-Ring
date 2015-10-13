#include "../libs/stdSocketTools.h"
#include "../libs/fileSend.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

void firstConnect(){
	int socketFD = simpleConnectToHost("192.168.1.1",63036);
	while(socketFD<0){
		sleep(5); //5 seconds
		socketFD=simpleConnectToHost("192.168.1.1",63036);
	}
	char header[]="RASPI CAMERA\r\nREPORTING\r\n\r\n";
	write(socketFD,header,strlen(header));
	close(socketFD);
}

std::string getHeader(int socketFD){
	char buf;
	int charsRead=1;
    std::string header;
    while(charsRead){
	    charsRead=read(socketFD,&buf,1);//read the message
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
	return header;
}

void startVideoStream(){
	system("uv4l --audio-video_nr --driver raspicam --server-option '--enable-webrtc=0' --server-option '--enable-webrtc-audio=0' --server-option '--webrtc-receive-audio=0' --server-option '--port=63136'");
}
void stopVideoStream(){
	system("killall uv4l");
}
void takeImage(){
	// puts into output.png
	// no preview on screen
	// waits 900 milliseconds to capture
	// the camera seems to need time to warm up
	system("raspistill -o output.png -e png --nopreview --timeout 900");
}
void sendImageBack(){
	int socketFD = simpleConnectToHost("192.168.1.1",63036);
	std::string header="RASPI CAMERA\r\nIMAGE SEND\r\n\r\n";
	write(socketFD,header.c_str(),header.length());
	sendFileAlreadyConnected(socketFD,"output.png");
}

int main(int argc, char const *args[]){
	stopVideoStream();
	startVideoStream();
	firstConnect(); //connect to the admin to say that we are here

	int listenFD = simpleOpenListenSocket(63036);
	struct newConnectionInfo newConc = simpleAccept(listenFD);
	std::string header=getHeader(newConc.FD);
	printf("%s\n", header.c_str());
	if(header=="RASPI ADMIN\r\nIMAGE TAKE\r\n\r\n"){
		stopVideoStream();
		takeImage();
		startVideoStream();
		sendImageBack();
		close(listenFD);
	}

	return 0;
}
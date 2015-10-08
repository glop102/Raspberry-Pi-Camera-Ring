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
#ifndef fileSave_socketThreaded
#define fileSave_socketThreaded
/*
This makes a new thread to save a file
Pass in the file descriptor and the incoming address info

There is also the secondary saveFile function to change the default save parameters
*/

pthread_t saveFile(int incomingFD);
pthread_t saveFile(int incomingFD,std::string saveDestFolder,std::string saveDestName);

void* saveFile_thread(void* dataIN);
std::string getFilename(int incomingFD);
void saveFileToDisk(int incomingFD,std::string saveDestFolder,std::string saveDestName);

struct fileDataThreadPasser{
	int FD;
	std::string saveDestFolder;
	std::string saveDestName;
};

//==========================================================================
#endif
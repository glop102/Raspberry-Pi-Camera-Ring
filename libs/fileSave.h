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
This is useful for when recieving images from the PIs to put them in the independent image set folders

There are also nonThreaded versions that use the same weight-lifting code
These are for use in threads done per-connection
*/

pthread_t saveFile(int incomingFD);
pthread_t saveFile(int incomingFD,std::string saveDestFolder,std::string saveDestName);
void saveFile_noThread(int incomingFD);
void saveFile_noThread(int incomingFD,std::string saveDestFolder,std::string saveDestName);

void* saveFile_thread(void* dataIN); //thread starting function
std::string getFilename(int incomingFD);//part 1
void saveFileToDisk(int incomingFD,std::string saveDestFolder,std::string saveDestName);//part two

//passes needed data to the starting function of the new thread
struct fileDataThreadPasser{
	int FD;
	std::string saveDestFolder;
	std::string saveDestName;
};

//==========================================================================
#endif
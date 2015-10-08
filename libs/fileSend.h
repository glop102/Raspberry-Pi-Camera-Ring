#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#ifndef fileSave_socketLibs
#define fileSave_socketLibs

void sendFile(int socketFD,std::string hostName,int port,std::string filePath);
int lastIndexOf(const char* buf,char search);
std::string itoa(int here);
struct sockaddr_in determineDestinationData(std::string hostName,int port);
void writeFileToSocket(int socketFD,std::string filePath);

#endif
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
#ifndef standardSocketTools
#define standardSocketTools

/*
This provides several common basic tools that dont deserve their own headers
This makes it a collection of smaller functions
*/

std::string incomingAddr(struct sockaddr_in ADDR); //gives the IP address of the connection
int simpleOpenSocket();
int simpleOpenListenSocket(int port);
struct newConnectionInfo simpleAccept(int socketFD);

struct newConnectionInfo{
	int FD;
	char address[16];
};

#endif
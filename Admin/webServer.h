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
#include "../libs/stdSocketTools.h"
#include "../libs/fileSave.h" //to get the itoa function I wrote
#include "raspiControlSystem.h"
#ifndef webServerWrapper
#define webServerWrapper

/*
This library handles talking with a web browser
engageBrowser if the first function called
it starts by getting the requested URL
it then checks to see if the URL is hardcoded to do something
	If it is hardcodded to do something - does that
	default - load file from the www directory relative to where it is executed
*/

void engageBrowser(int socketFD,std::string header);
std::string getRequestedPage(std::string header); //gets the requested URL from the header passed in
void sendHTMLFile(int socketFD,std::string request); //sends a file from the filesystem
void replaceSymbols(std::vector<char>& input); //replaces speacial symbols with special information before letting it be sent to the browser
std::string makeNextImageSet(); //makes the folder for the next image set
std::string currentImageSet(); //gets the last image set name
std::string itoa(unsigned int here);
void redirectPage(int socketFD,std::string here);

void sendHTML_ImageSet(int socketFD,std::string setName); //special case for when opening an image set to look at the images and download archive
void replaceSymbols_ImageSet(std::string& doc, std::string setName);

void imageSetDownload(int socketFD,std::string imageSetName);
void imageSetDelete(int socketFD,std::string imageSetName);

#endif
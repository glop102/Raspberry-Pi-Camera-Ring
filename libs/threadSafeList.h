#include <thread>
#include <mutex>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#ifndef threadSafeList_header
#define threadSafeList_header

/*
NOTE: This is only intended to be used to store strings
The original intent was to make this a global list of IP addresses
WARNING: the strings returned are not original from the list
you cannot simply do list[66]="10.0.0.1" or something
*/

class threadSafeList{
private:
	std::mutex working; //this is what governs the modification of the class
	std::vector<std::string> buf;
public:
	threadSafeList();
	std::string operator[](unsigned int index);
	void remove(unsigned int index);
	void remove(std::string input);
	void append(std::string input);
	void clear();
	int  find(std::string);
	int length();
};

#endif
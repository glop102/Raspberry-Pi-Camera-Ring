#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifndef glop102Buffer
#define glop102Buffer

/*
THIS IS EXCLUSIVLY FOR USE IN THE WEB SECTION OF THE ADMIN PROGRAM
PLEASE BE CAREFUL USING THIS AS THERE IS A LITTLE MAGIC SAUCE
not thread safe also
*/

class buffer{
public:
	char* buf;
	unsigned int length;
	~buffer();
	buffer();
	buffer(char);
	buffer(char*);
	buffer(const buffer&);
	buffer(const std::string&);
	void clear();
	void operator+=(char);
	void operator+=(const char*);
	void operator+=(const buffer&);
	void append(const char*,unsigned int);
	void operator+=(std::string);
	void operator=(const buffer&);
	void operator=(buffer*);
	void operator=(char);
	void operator=(const char*);
	void operator=(std::string);
};

#endif
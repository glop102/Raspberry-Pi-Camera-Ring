#include "webServer.h"

void engageBrowser(int socketFD,std::string header){
	//what page are they trying to get to?
	std::string request=getRequestedPage(header);//this is also going to be used to open the file

	printf("File Request:  %s\n",request.c_str());
	if(request=="/"){ //hard-coded response
		sendHTMLFile(socketFD,"www/index.html");
	}else if(request=="/images"){
		sendHTMLFile(socketFD,"www/images.html");
		//This needs to branch out to send other data
	}else{ //default - try to load the file
		sendHTMLFile(socketFD,"www"+request);
	}
}

std::string getRequestedPage(std::string header){
	if(header.substr(0,3)=="GET"){
		int index=header.find(' ',5);
		return header.substr(4,index-4);
	}
}

void sendHTMLFile(int socketFD,std::string request){
	static std::string response200="HTTP/1.1 200 OK\r\n\r\n";
	static std::string response404="HTTP/1.1 404 Not Found\r\n\r\n";
	static std::string response301="HTTP/1.1 301 Moved Permanently\n\rLocation: /\r\n\r\n";

	buffer response;
	char buf[256];
	int charsRead=255;
	FILE* input=fopen(request.c_str(),"r");
	if(input==NULL){
		FILE* input=fopen("www/404.html","r");
		response+=response404;
		if(input!=NULL){
			while(charsRead==255){
				bzero(buf,256);
				charsRead=fread(buf,1,255,input);
				response.append(buf,charsRead);
			}
			fclose(input);
		}
	}else{
		response+=response200;
		while(charsRead==255){
			bzero(buf,256);
			charsRead=fread(buf,1,255,input);
			response.append(buf,charsRead);
		}
		fclose(input);
	}
	write(socketFD,response.buf,response.length);
	close(socketFD);
}

buffer replaceSymbols(buffer input){
	return input;
}


//==========================================================================
buffer::~buffer(){
	if(this->buf!=NULL) free(this->buf);
}
buffer::buffer(){
	this->buf=NULL;
	this->clear();
}
buffer::buffer(char input){
	this->buf=NULL;
	this->clear();
	(*this)+=input;
}
buffer::buffer(char* input){
	this->buf=NULL;
	this->clear();
	(*this)+=input;
}
buffer::buffer(std::string input){
	this->buf=NULL;
	this->clear();
	(*this)+=input;
}
void buffer::clear(){
	if(this->buf!=NULL) free(this->buf);
	this->buf=(char*)malloc(1);
	this->length=0;
}
void buffer::operator+=(char input){
	this->length+=1;
	char* other=(char*)malloc(this->length);
	if(other!=this->buf){
		//copy to new buffer
		unsigned int curt=0;
		while(curt<this->length-1){
			other[curt]=this->buf[curt];
			curt++;
		}
		free(this->buf);
	}
	other[this->length-1]=input;
	this->buf=other;
}
void buffer::operator+=(const char* input){
	unsigned int inputLength=strlen(input);
	char* other=(char*)malloc(this->length+inputLength);
	if(other!=this->buf){
		//copy the old to the new
		unsigned int curt=0;
		while(curt<this->length){
			other[curt]=this->buf[curt];
			curt++;
		}
		free(this->buf);
		this->buf=other;
	}

	//copy in the new
	unsigned int curt=0;
	while(curt<inputLength){
		this->buf[this->length+curt]=input[curt];
		curt++;
	}
	this->length+=inputLength;
}
void buffer::append(const char* input,unsigned int inputLength){
	char* other=(char*)malloc(this->length+inputLength);
	if(other!=this->buf){
		//copy the old to the new
		unsigned int curt=0;
		while(curt<this->length){
			other[curt]=this->buf[curt];
			curt++;
		}
		free(this->buf);
		this->buf=other;
	}

	//copy in the new
	unsigned int curt=0;
	while(curt<inputLength){
		this->buf[this->length+curt]=input[curt];
		curt++;
	}
	this->length+=inputLength;
}
void buffer::operator+=(std::string input){
	unsigned int inputLength=input.length();
	char* other=(char*)malloc(this->length+inputLength);
	if(other!=this->buf){
		//copy the old to the new
		unsigned int curt=0;
		while(curt<this->length){
			other[curt]=this->buf[curt];
			curt++;
		}
		free(this->buf);
		this->buf=other;
	}

	//copy in the new
	unsigned int curt=0;
	while(curt<inputLength){
		this->buf[this->length+curt]=input[curt];
		curt++;
	}
	this->length+=inputLength;
}
void buffer::operator=(buffer other){
	this->clear(); //stop memory leaks
	(*this).append(other.buf,other.length);
}
void buffer::operator=(buffer* other){
	this->clear(); //stop memory leaks
	(*this).append(other->buf,other->length);
}
void buffer::operator=(char input){
	this->clear();
	(*this)+=input;
}
void buffer::operator=(const char* input){
	this->clear();
	(*this)+=input;
}
void buffer::operator=(std::string input){
	this->clear();
	(*this)+=input;
}
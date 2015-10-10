#include "webServer.h"

void engageBrowser(int socketFD,std::string header){
	//what page are they trying to get to?
	std::string request=getRequestedPage(header);//this is also going to be used to open the file

	printf("File Request:  %s\n",request.c_str());
	if(request=="/"){ //hard-coded response
		sendHTMLFile(socketFD,"www/index.html");
	}else if(request=="/images"){
		sendHTMLFile(socketFD,"www/images.html");
	}else if(request.find("/images/")==0){ //if they are looking at an image set
		request=request.substr(8);
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
		//printf("=============================\n%s\n\n\n", response.buf);
		while(charsRead==255){
			bzero(buf,256);
			charsRead=fread(buf,1,255,input);
			response.append(buf,charsRead);
			//printf("=============================\n%s\n\n\n", response.buf);
		}
		fclose(input);
	}
	response+=(char)0; //give the end of string char just to make sure
	response=replaceSymbols(response);

	write(socketFD,response.buf,response.length);
	close(socketFD);
}

buffer replaceSymbols(buffer input){
	if(strstr(input.buf,"<html>") < strstr(input.buf,"</html>")){ //if this is an HTML document
		unsigned long index=strstr(input.buf,"<?raspi testFlag?>")-input.buf;
		while(index>0 && index<input.length){
			buffer temp;
			temp.append(input.buf,index);
			temp+="<h2>Test Flag Works</h2>";
			temp+=input.buf+index+strlen("<?raspi testFlag?>");
			input=temp;
			index=strstr(input.buf,"<?raspi testFlag?>")-input.buf;
		}
		index=strstr(input.buf,"<?raspi debugFlag?>")-input.buf;
		while(index>0 && index<input.length){
			buffer temp;
			temp.append(input.buf,index);
			temp+="<h2>Debug Info</h2>\n";
			temp+="<p>Admin Server version 0.1.0</p>\n";
			temp+="<p>This is highly experimental, apparently stable, with few features. Expect massive changes, namely with the hard coded paths and extra flags</p>";
			temp+=input.buf+index+strlen("<?raspi debugFlag?>");
			input=temp;
			index=strstr(input.buf,"<?raspi debugFlag?>")-input.buf;
		}
	}
	return input;
}

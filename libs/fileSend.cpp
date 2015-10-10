#include "fileSend.h"

int lastIndexOf(const char* buf,char search){
    //gives the last occuring index of a char
    int last=-1;
    int curt=0;
    while(*buf){
        if(*buf==search)last=curt;
        buf++; curt++;
    }
    return last;
}

std::string itoa(unsigned int here){
	//unsigned numbers and assumes unlimited buffer
	std::string buf="";
	while(here){
		buf+= (here%10) + '0';
		here/=10;
	}

	//now reverse buf
	char temp;
	for(int x=0;x<buf.length()/2;x++){
		temp=buf[x];
		buf[x]=buf[buf.length()-x-1];
		buf[buf.length()-x-1]=temp;
	}
	return buf;
}

void sendFile(int socketFD,std::string hostName,int port,std::string filePath){
    //first figure out where the server is
    struct sockaddr_in serv_addr=determineDestinationData(hostName,port);
    //make the connection to the server
    if (connect(socketFD,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        printf("ERROR connecting\n");
        return;
    }
    writeFileToSocket(socketFD,filePath);
}

struct sockaddr_in determineDestinationData(std::string hostName,int port){
    //given the name of the server (IP of URL)
    //returns the server info to make the connection
	struct hostent *server=gethostbyname(hostName.c_str());
	if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        //return NULL;
        //There should be some smart way of returning safe but useless data
    }

    //set the data for where we are sending the file
    //yes, this is quite the block of text, but it is greek to me
    struct sockaddr_in serv_addr;
    bzero((char*)&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*)server->h_addr,(char*)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port=htons(port);

    return serv_addr;
}

void writeFileToSocket(int socketFD,std::string filePath){
    //the meat of the system
    // 1. make sure the file can be opened
    // 2. write to the socket the basic info about the file
    // 3. write the file itself to the socket

    //structure of data sent
    // 1. length of the filename
    // 2. filename
    // 3. length of the file
    // 4. file data
    //there is a SINGLE newline between each field
    //although the fileSave function can handle extra newlines
    //    don't be sloppy and send them in the first place

	FILE* input=fopen(filePath.c_str(),"r");
	if(input==NULL){
    	printf("Unable to open file\n");
    	return; //safe to return since have not written anything???
    }

    //get the basic data about the file
    //filename and file length
    std::string fileName=filePath.substr(lastIndexOf(filePath.c_str(),'/')+1);
    fseek(input,0l,SEEK_END);
    int fileLength=ftell(input);
    fseek(input,0l,SEEK_SET);

    //write the basic stuff of the file to the socket
    const char newline='\n';
    write(socketFD,itoa(fileName.length()).c_str(),itoa(fileName.length()).length());
    write(socketFD,&newline,1);
    write(socketFD,fileName.c_str(),fileName.length());
    write(socketFD,&newline,1);
    write(socketFD,itoa(fileLength).c_str(),itoa(fileLength).length());
    write(socketFD,&newline,1);

    //now we only have to write the file
    char buf[256];
    bzero(buf,256);
    int charsRead=255;
    while(charsRead==255){
    	charsRead=fread(buf,1,255,input);
    	write(socketFD,buf,charsRead);
    }
}
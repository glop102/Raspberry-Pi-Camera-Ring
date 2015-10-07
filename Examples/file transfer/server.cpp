#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

struct argPasser
{
	int FD; //file descriptor
	struct sockaddr_in ADDR;
};

void* downloadFile(void* data){
	int newSockFD=((argPasser*)data)->FD; //copy out the data so that the thread is fine when the main continues
	struct sockaddr_in cli_addr=((argPasser*)data)->ADDR;

	printf("\n\n=== New Connection ===\n\n");
	    char clientAddress[INET6_ADDRSTRLEN+1]; bzero(clientAddress,sizeof(clientAddress));
	    inet_ntop(AF_INET, &(cli_addr.sin_addr),clientAddress,sizeof(clientAddress));
	    printf("clientAddress\t%s\n",clientAddress);

	    //get the filename that will be used to save to
	    char bbb;
	    int filenameLength=0;
	    while(1){
	    	if(!read(newSockFD,&bbb,1)){ //get the next char
	    		printf("Unable to read socket.\n");
	    		filenameLength=0;
	    		break;
	    	}
	    	if(bbb>='0' && bbb<='9'){
	    		filenameLength*=10;
	    		filenameLength+=bbb-'0';
	    	}else break;
	    }
	    if(filenameLength==0){close(newSockFD);return NULL;}
	    printf("Filename Length: %d\n", filenameLength);
	    char filename[filenameLength+1];
	    bzero(filename,filenameLength+1);
	    read(newSockFD,&bbb,1); //clear out the newline seperator
	    filename[0]=bbb;

	    char *curt=filename+1;
	    while(curt < filename+filenameLength){
	    	if(!read(newSockFD,curt,1)){ //get the next char
	    		printf("Unable to read socket.\n");
	    		filename[0]=0;
	    		break;
	    	}
	    	curt++;
	    }
	    if(filename[0]==0){close(newSockFD);return NULL;}
	    printf("%s\n", filename);
	    read(newSockFD,&bbb,1); //clear out the newline seperator

	    //get the length of the file
	    int fileLength=0;
	    while(1){
	    	if(!read(newSockFD,&bbb,1)){ //get the next char
	    		printf("Unable to read socket.\n");
	    		filenameLength=0;
	    		break;
	    	}
	    	if(bbb>='0' && bbb<='9'){
	    		fileLength*=10;
	    		fileLength+=bbb-'0';
	    	}else break;
	    }
	    if(fileLength==0){close(newSockFD);return NULL;}
	    printf("File     Length: %d\n", fileLength);

	    //time to read the file and write to a file
	    FILE* output= fopen(filename,"w");
	    read(newSockFD,&bbb,1); //clear out the newline to begin reading
	    while(fileLength){
	    	fwrite(&bbb,1,1,output); //buf, 1 byte wide chars, 1 char total, file to write to
	    	if(!read(newSockFD,&bbb,1)){
	    		printf("Unable to read socket.\n");
	    		break;
	    	}
	    	fileLength--;
	    }
	    fclose(output);
	    printf("Done Reading File\n");

	    close(newSockFD);
}

int main(int argc, char** args){
	int port=63036;
	socklen_t clientLength;
	struct sockaddr_in serv_addr, cli_addr;
	int listenFD;

	listenFD = socket(AF_INET, SOCK_STREAM, 0); //voodoo line 1
	if (listenFD < 0) 
        error("ERROR opening socket");
    serv_addr.sin_family = AF_INET; //internet domain, not unix domain
	serv_addr.sin_addr.s_addr = INADDR_ANY; //allow us to listen to all interfaces
	serv_addr.sin_port = htons(port); //change order of the bytes from the host specific to the network order (so dont worry about Big or Little endian)
	if (bind(listenFD, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		error("ERROR on binding");

	listen(listenFD,5); //start listening so that we can get new connections
	clientLength = sizeof(cli_addr); //size of the struct
	char buffer[256];

	while(1){
		int newSockFD = accept(listenFD, (struct sockaddr *) &cli_addr, &clientLength); //get the FD of the new client connection
		if (newSockFD < 0) 
	          error("ERROR on accept");
	    //downloadFile(newSockFD,cli_addr);
	    pthread_t temp;
	    static struct argPasser data;
	    data.FD=newSockFD;
	    data.ADDR=cli_addr;
	    if(pthread_create(&temp,NULL,downloadFile,&data)){
	    	printf("ERROR making new thread\n");
	    }
	}

	printf("Exiting\n");
	close(listenFD);

	return 0;
}
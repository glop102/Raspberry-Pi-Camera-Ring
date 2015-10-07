#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int lastIndexOf(char* buf,char search){
    int last=-1;
    int curt=0;
    while(*buf){
        if(*buf==search)last=curt;
        buf++; curt++;
    }
    return last;
}
int lastIndexOf_0NF(char* buf,char search){
    int last=0;
    int curt=0;
    while(*buf){
        if(*buf==search)last=curt;
        buf++; curt++;
    }
    return last;
}

char * itoa(int here, char* buf){
	//unsigned numbers and assumes unlimited buffer
	char * temp=buf;
	while(here){
		*temp= (here%10) + '0';
		here/=10;
		temp++;
	}
	*temp=0;
	//now reverse buf
	temp--;
	char ttt;
	char*temp2=buf;
	while(temp2<temp){
		ttt=*temp2;
		*temp2=*temp;
		*temp=ttt;
		temp2++;
		temp--;
	}
	return buf;
}

int main(int argc, char *argv[])
{
    int socketFD, port;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 3) {
       fprintf(stderr,"usage: %s hostname filename\n", argv[0]);
       exit(0);
    }
    port=63036;
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    //setup the connection info
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    //make the connection to the server
    if (connect(socketFD,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    //open the file and get some things prepared for use
    FILE* input=fopen(argv[2],"r");
    if(input==NULL){
    	error("Unable to open file\n");
    }
    char buf[256];
    bzero(buf,256);
    int n=255;
    char filenameLengthA[20];
    char fieldSeperator='\n';
    bzero(filenameLengthA,20);
    itoa(strlen(argv[2]+lastIndexOf_0NF(argv[2],'/')),filenameLengthA);
    printf("Filename        %s\nFileLength      %s\n", argv[2]+lastIndexOf_0NF(argv[2],'/'),filenameLengthA);

    //tell the name of the file
    write(socketFD,filenameLengthA,strlen(filenameLengthA));
    write(socketFD,&fieldSeperator,1);
    write(socketFD,argv[2]+lastIndexOf_0NF(argv[2],'/'),strlen(argv[2]+lastIndexOf_0NF(argv[2],'/')));
    write(socketFD,&fieldSeperator,1);

    //tell how long the file is
    fseek(input,0L,SEEK_END);
    char fileLength[30];
    itoa(ftell(input),fileLength);
    fseek(input,0L,SEEK_SET);
 	write(socketFD,fileLength,strlen(fileLength));
    write(socketFD,&fieldSeperator,1);

    //write the file itself to the socket
    while(n==255){ //while there are things to be read from the file
    	n=fread(buf,1,255,input);
    	write(socketFD,buf,n);
    }
    bzero(buf,255);
    write(socketFD,buf,255); //make damn sure that you get a zero to end this thing
    close(socketFD);

    return 0;
}
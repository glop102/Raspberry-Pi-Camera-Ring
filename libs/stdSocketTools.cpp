#include "stdSocketTools.h"

std::string incomingAddr(struct sockaddr_in ADDR){
	//http://stackoverflow.com/questions/2064636/getting-the-source-address-of-an-incoming-socket-connection
	char ipstr[INET6_ADDRSTRLEN + 1];

	// deal with both IPv4 and IPv6:
	if (ADDR.sin_family == AF_INET) {
	    inet_ntop(AF_INET, &ADDR.sin_addr, ipstr, sizeof ipstr);
	} else { // AF_INET6
		//WARNING: THIS MAY BREAK
		//this ipv6 implementation may be broken
		//this is NOT tested
	    inet_ntop(AF_INET6, &ADDR.sin_addr, ipstr, sizeof ipstr);
	}

	std::string temp=ipstr;
	return temp;
}
int simpleOpenSocket(){
	return socket(AF_INET, SOCK_STREAM, 0);
}
int simpleOpenListenSocket(int port){
	struct sockaddr_in serv_addr;
	int listenFD;

	listenFD = socket(AF_INET, SOCK_STREAM, 0);
	if (listenFD < 0){
        //error("ERROR opening socket");
        return -1;
    }
    serv_addr.sin_family = AF_INET; //internet domain, not unix domain
	serv_addr.sin_addr.s_addr = INADDR_ANY; //allow us to listen to all interfaces
	serv_addr.sin_port = htons(port); //change order of the bytes from the host specific to the network order (so dont worry about Big or Little endian)
	if (bind(listenFD, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		//error("ERROR on binding");
		return -1;
	}
	listen(listenFD,15);//start listening so that we can get new connections
	return listenFD;
}

struct newConnectionInfo simpleAccept(int socketFD){
	//listens to a port until a person connects
	//this then sends back the basic info
	//file descriptor of the new connection
	//IP address of the incomming person
	struct sockaddr_in cli_addr;
	socklen_t clientLength = sizeof(cli_addr);//size of the struct
	int newSockFD = accept(socketFD, (struct sockaddr *) &cli_addr, &clientLength); //get the FD of the new client connection
	if (newSockFD < 0) 
	    printf("ERROR on accept");

	struct newConnectionInfo peer;
	peer.FD=newSockFD;
	strcpy(peer.address,incomingAddr(cli_addr).c_str());
	return peer;
}

int simpleConnectToHost(std::string ADDR,int port){
	int socketFD=simpleOpenSocket();
	if(socketFD<0) return -1; //error

	struct hostent *server = gethostbyname(ADDR.c_str());
	if(server==NULL){
		close(socketFD);
		return -1; //error
	}

	struct sockaddr_in serv_addr;
	//setup the connection info
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    if (connect(socketFD,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		close(socketFD);
		return -1; //error
	}

	return socketFD;
}
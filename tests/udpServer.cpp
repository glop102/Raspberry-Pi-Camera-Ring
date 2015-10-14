#include "../libs/stdSocketTools.h"
#include <stdio.h>
#include <stdlib.h>

int tempSend(int socketFD,int port,std::string message){
	struct sockaddr_in bcast;
	bzero((char*)&bcast,sizeof(bcast));
	bcast.sin_family=AF_INET;
	bcast.sin_port=htons(port);
	bcast.sin_addr.s_addr=htonl(INADDR_ANY);

	//host lookup
	//struct hostent *host;
	//host = gethostbyname("255.255.255.255");
	//memcpy((void *)&bcast.sin_addr, host->h_addr_list[0], host->h_length);
	return sendto(socketFD,message.c_str(),message.length(),0,(struct sockaddr*)&bcast,sizeof(bcast));
}

int main(){
	int socketFD=simpleOpenSocket_UDP(63036);
	printf("%d\n",send_UDP(socketFD,63036,"10.42.0.44","Unicast"));
	printf("%d\n",send_UDP(socketFD,63036,"10.42.0.255","Subnet broadcast"));
	printf("%d\n",send_UDP(socketFD,63036,"255.255.255.255","All Cast"));
	printf("%d\n",sendBroadcast_UDP(socketFD,63036,"Broadcast"));
	printf("%d\n",tempSend(socketFD,63036,"All Interfaces"));
	printf("%d\n",send_UDP(socketFD,63036,"0.0.0.0","No Cast"));
	printf("%d\n",send_UDP(socketFD,63036,"10.42.0.1","Myself"));
	close(socketFD);
	return 0;
}
#include "raspiControlSystem.h"

threadSafeList<std::string> globalIPList;

void raspiConnection(struct newConnectionInfo peer,std::string header){
	//printf("%s\n%d\n", peer.address,peer.FD);
	//printf("%s\n", header.c_str());
	if(globalIPList.find(peer.address)==-1){ //this is not in the list
		globalIPList.append(peer.address);
	}
	printf("%d total found\n", globalIPList.length());
	for(int x=0;x<globalIPList.length();x++){
		printf("\t%s\n", globalIPList[x].c_str());
	}
}
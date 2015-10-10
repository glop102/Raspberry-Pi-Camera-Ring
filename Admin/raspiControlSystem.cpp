#include "raspiControlSystem.h"

void raspiConnection(struct newConnectionInfo peer,std::string header){
	printf("%s\n%d\n", peer.address,peer.FD);
	printf("%s\n", header.c_str());
}
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
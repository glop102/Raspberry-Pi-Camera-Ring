#include "raspiControlSystem.h"

threadSafeList<PI_INFO> globalIPList;

void raspiConnection(struct newConnectionInfo peer,std::string header){
	//printf("%s\n%d\n", peer.address,peer.FD);
	//printf("%s\n", header.c_str());
	if(globalIPList.find({peer.address})==-1){ //this is not in the list
		globalIPList.append({peer.address,header.substr(6,header.find('\r',6)-6)}); //fills out the basic info of the PI
	}
	printf("%d total found\n", globalIPList.length());
	for(int x=0;x<globalIPList.length();x++){
		printf("\t%s\t%s\n", globalIPList[x].address.c_str(),globalIPList[x].role.c_str());
	}

	header=header.substr(header.find('\r')+2); //get to the second line to see what it wanted to do
	if(header=="\r\n" || header=="REPORTING\r\n\r\n"){
		close(peer.FD);
		return;//just reporting in, nothing to see here
	}else if(header.substr(0,header.find('\r'))=="IMAGE SEND"){
		downloadFile(peer); //dont need the header since the file is the next thing coming down the pipe
	}else{
		printf("Unknown Command:  %s\n", header.substr(0,header.find('\r')).c_str());
	}
	close(peer.FD);
}

void downloadFile(struct newConnectionInfo peer){
	// puts the files coming down the pipe next in the highest sorted directory
	// 1. list folders in "images"
	// 2. sort folders
	// 3. saveFile_noThread(peer.FD,"images/"+highestFolderName,peer.address);
	// this keeps all files that were taken at the same time in the same folder
	// this makes each image have a unique name that will always match between the same setups
	// NOTE TO FUTURE:
	//     For the command sending to each PI to take a picture
	//     FIRST!!! make sure that the images directory exists
	//     SECOND!! make the folder for the image set that is used here
	//     THIRD!!! open connections to the PIs and send command
}
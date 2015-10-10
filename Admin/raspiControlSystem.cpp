#include "raspiControlSystem.h"

threadSafeList<PI_INFO> globalIPList; //global list of PIs that have reported to the admin
	//NOTE: this list is global so that the webserver can use it to send commands when the client says to

void raspiConnection(struct newConnectionInfo peer,std::string header){
	/*
	CALL THIS FIRST
	This is what all the logic spreads from in order to do the PI control
	*/

	//check that we have this PI in our list of available PIs
	if(globalIPList.find({peer.address})==-1){ //this is not in the list
		globalIPList.append({peer.address,header.substr(6,header.find('\r',6)-6)}); //fills out the basic info of the PI
	}

	//DEBUG - lets you see all the clients connected everytime a new connection happens
	printf("%d total found\n", globalIPList.length());
	for(int x=0;x<globalIPList.length();x++){
		printf("\t%s\t%s\n", globalIPList[x].address.c_str(),globalIPList[x].role.c_str());
	}

	//Parse the second line for the major command of what to do
	//we spread out from here
	header=header.substr(header.find('\r')+2); //get to the second line to see what it wanted to do
	if(header=="\r\n" || header=="REPORTING\r\n\r\n"){
		//this was just a trivial connection to tell the Admin they exist
		close(peer.FD);
		return;
	}else if(header.substr(0,header.find('\r'))=="IMAGE SEND"){
		//the image from the last photo shot is ready to be sent
		//dont need the header since the file is the next thing coming down the pipe
		downloadImage(peer);
	}else{
		printf("Unknown Command:  %s\n", header.substr(0,header.find('\r')).c_str());
	}
	close(peer.FD);
}

void downloadImage(struct newConnectionInfo peer){
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
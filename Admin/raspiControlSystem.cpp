#include "raspiControlSystem.h"

void raspiConnection(struct newConnectionInfo peer,std::string header){
	/*
	CALL THIS FIRST
	This is what all the logic spreads from in order to do the PI control
	*/

	//check that we have this PI in our list of available PIs
	int index = globalIPList.find({peer.address});
	if(index==-1){ //this is not in the list
		globalIPList.append({peer.address,header.substr(6,header.find('\r',6)-6),0}); //fills out the basic info of the PI
	}else{//it is in the list
		globalIPList[index].failedReports=0;
	}

	//DEBUG - lets you see all the clients connected everytime a new connection happens
	//printf("%d total found\n", globalIPList.length());
	//for(int x=0;x<globalIPList.length();x++){
	//	printf("\t%s\t%s\n", globalIPList[x].address.c_str(),globalIPList[x].role.c_str());
	//}

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

	/* Opens the local dir and prints every file AND folder there
	DIR* fd=opendir(".");
	if(fd==0) return;
	struct dirent *de;
	while((de=readdir(fd))!=NULL){ //read everything in the folder
		printf("\t%s\n", de->d_name);
	}
	closedir(fd);
	*/

	/* Find every directory by seeing if you can open it
	DIR* fd=opendir(".");
	if(fd==0) return;
	struct dirent *de;
	while((de=readdir(fd))!=NULL){ //read everything in the folder
		DIR* fd2=opendir(de->d_name);
		printf("\t%lu\t%s\n",fd2,de->d_name); //is 0 if not a directory
		if(fd2)closedir(fd2);
	}
	closedir(fd);
	*/
	std::vector<std::string> dirContents;
	dirContents=listDirectoryContents("./images/");

	unsigned int x=0;
	std::vector<std::string> dirContents2=listDirectoryContents("images/"+dirContents[dirContents.size()-1]);
	bool has=false;
	printf("Downloading Image\n");

	for(int y=0;y<dirContents2.size();y++){
		if(dirContents2[y]==std::string(peer.address)+"_"+itoa(x)+".png"){
			has=true;
			break;
		}
	}
	while(has){
		x++;
		has=false;
		for(int y=0;y<dirContents2.size();y++){
			if(dirContents2[y]==std::string(peer.address)+"_"+itoa(x)+".png"){
				has=true;
				break;
			}
		}
	}
	printf("\t%s\n",(std::string(peer.address)+"_"+itoa(x)+".png").c_str());
	saveFile_noThread(peer.FD,"images/"+dirContents[dirContents.size()-1],std::string(peer.address)+"_"+itoa(x)+".png");
}

std::vector<std::string> listDirectoryContents(std::string input){
	DIR* fd=opendir(input.c_str());
	if(fd==0) return {};

	struct dirent *de;
	std::vector<std::string> v;
	while((de=readdir(fd))!=NULL){ //read everything in the folder
		if(de->d_name[0]=='.' && de->d_name[1]==0) continue; //ignore the dots
		if(de->d_name[0]=='.' && de->d_name[1]=='.' && de->d_name[2]==0) continue;
		v.push_back(de->d_name);
	}
	closedir(fd);
	return sortContents(v);
}

std::vector<std::string> sortContents(std::vector<std::string> input){
	//insertion sort
	for(int x=1;x<input.size();x++){
		int diff=stringDifference(input[x],input[x-1]); //neg means we need to move up
		if(diff<0){
			int y=x;
			while(diff<0 && y>=1){
				std::string temp=input[y];
				input[y]=input[y-1];
				input[y-1]=temp;
				y--;
				if(y>0)diff=stringDifference(input[y],input[y-1]); //neg means we need to move up
			}
		}
	}
	return input;
}

int stringDifference(std::string first,std::string sec){
	//negative means first comes before sec
	//positive means sec comes before first
	int counter=0;
	while(first[counter]!=0 && sec[counter]!=0 && first[counter]==sec[counter]){
		counter++;
	}
	return first[counter]-sec[counter];
}

void sendTakeCommand_All(){
	for(int x=0;x<globalIPList.length();x++){
		if(globalIPList[x].role!="CAMERA")continue;
		pthread_t thread;
		pthread_create(&thread,NULL,__sendTakeCommand_All,(void*)globalIPList[x].address.c_str());
	}
}
void* __sendTakeCommand_All(void* data){
	std::string address=(char*)data;
	int socketFD=simpleConnectToHost(address,63036);
	if(socketFD==0)return NULL;
	static std::string header="RASPI ADMIN\r\nIMAGE TAKE\r\n\r\n";
	write(socketFD,header.c_str(),header.length());
	close(socketFD);
	return NULL;
}
void sendCaptureCommand_All(){
	int socketFD=simpleOpenSocket_UDP(63036);
	sendBroadcast_UDP(socketFD,63036,"IMAGE CAPTURE");
}

void sendUpdateCommand_All(){
	for(int x=0;x<globalIPList.length();x++){
		if(globalIPList[x].role!="CAMERA")continue;
		int socketFD=simpleConnectToHost(globalIPList[x].address,63036);
		if(socketFD==0)return;
		static std::string header="RASPI ADMIN\r\nUPDATE\r\n\r\n";
		write(socketFD,header.c_str(),header.length());
		close(socketFD);
	}
	globalIPList.clear(); //we dont know if they will have the same address
}
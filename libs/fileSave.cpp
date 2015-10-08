#include "fileSave.h"

pthread_t saveFile(int incomingFD){
	return saveFile(incomingFD,"",""); //default to simply save to where the executable was run from
}
pthread_t saveFile(int incomingFD,std::string saveDestFolder,std::string saveDestName){
	fileDataThreadPasser *temp=new fileDataThreadPasser;
	if(temp==0){
		printf("ERROR getting data struct made\n");
		return 0;
	}
	temp->FD=incomingFD;
	temp->saveDestFolder=saveDestFolder;
	temp->saveDestName=saveDestName;

	pthread_t threadFD;
	pthread_create(&threadFD,NULL,saveFile_thread,(void*)temp);
	return threadFD; //give back the thread descriptor so it can checked if it worked
}

//==========================================================================
	
void* saveFile_thread(void* dataIN){
	//first lets setup how i want the enviroment
	int incomingFD=((struct fileDataThreadPasser*)dataIN)->FD;
	std::string saveDestFolder=((struct fileDataThreadPasser*)dataIN)->saveDestFolder;
	std::string saveDestName=((struct fileDataThreadPasser*)dataIN)->saveDestName;
	delete (fileDataThreadPasser*)dataIN; //fix the malloc that we did to make this thread

	//steps
	//1 - get the length of the incoming filename
	//2 - read the filename
	//3 - get the length of the file
	//4 - read the file and write to the HDD

	if(saveDestName.length()==0){ //default, reuse incoming filename
		saveDestName=getFilename(incomingFD);
	}else{
		getFilename(incomingFD); //if we are using a different name, clear out the space
	}

	saveFileToDisk(incomingFD,saveDestFolder,saveDestName);

	return NULL;
}

std::string getFilename(int incomingFD){
	std::string filename="";
	char buf='\n';
	int filenameLength=0;
	while(buf=='\n')read(incomingFD,&buf,1); //read until newlines are removed
	while(buf>= '0' && buf<='9'){ //while we are reading digits
		filenameLength*=10;
		filenameLength+=buf-'0';
		read(incomingFD,&buf,1);
	} //buf has a newline in it
	//since we read first, we clear out the newline and then add to the name
	while(filenameLength){
		read(incomingFD,&buf,1); //get the next letter
		filename+=buf; //save the letter
		filenameLength--; //we have one less letter to read
	}
	read(incomingFD,&buf,1); //move out to the newline seperator
							//the name adding while loop ends by staying on the last
							//letter of the filename - just move it to the newline
							//seperator so that we can procede to the file part

	return filename;
}
void saveFileToDisk(int incomingFD,std::string saveDestFolder,std::string saveDestName){
	char buf='\n';
	int fileLength=0;
	while(buf=='\n')read(incomingFD,&buf,1); //read until newlines are removed
	while(buf>= '0' && buf<='9'){ //while we are reading digits
		fileLength*=10;
		fileLength+=buf-'0';
		read(incomingFD,&buf,1);
	} //buf has a newline in it
	//the next char to be read is the first char of the file

	std::string fileSavePath="";
	if(saveDestFolder.length()==0){
		fileSavePath=saveDestName;
	}else{
		//make sure we have the slash seperator between the folder and the file
		if(saveDestFolder[saveDestFolder.length()-1]!='/'){
			saveDestFolder+='/';
		}
		fileSavePath=saveDestFolder+saveDestName;
	}

	FILE* output=fopen(fileSavePath.c_str(),"w");
	while(fileLength){
		if(!read(incomingFD,&buf,1)){
			printf("Socket Closed Early\n");
			break;
		}
		fwrite(&buf,1,1,output); //buf, 1 byte wide chars, 1 char total, file to write to
		fileLength--;
	}
	fclose(output);
}
#include "webServer.h"

void engageBrowser(int socketFD,std::string header){
	/*
	CALL THIS FIRST
	This is what all the logic spreads from in order to do the website control
	*/
	//what page are they trying to get to?
	std::string request=getRequestedPage(header);//this is also going to be used to open the file

	//Parse the url to see what to do
	//we spread out from here
	printf("File Request:  %s\n",request.c_str());
	if(request=="/"){ //hard-coded response
		sendHTMLFile(socketFD,"www/index.html");
	}else if(request=="/images"){
		sendHTMLFile(socketFD,"www/images.html");
	}else if(request.find("/images/")==0){ //if they are looking at an image set
		std::string imageSetName=request.substr(strlen("/images/"),5);
		if(imageSetName.length()==5 && imageSetName[0]>='0' && imageSetName[0]<='9' //if this is a valid images/setNumber URL
									&& imageSetName[1]>='0' && imageSetName[1]<='9'
									&& imageSetName[2]>='0' && imageSetName[2]<='9'
									&& imageSetName[3]>='0' && imageSetName[3]<='9'
									&& imageSetName[4]>='0' && imageSetName[4]<='9'){
			if(request.length()>strlen("/images/XXXXX")){
				//NOTE:: add the delete and download check here
				//something like
				//request.substr(strlen("/images/XXXXX/"))=="download"
				//then send to the imageSetDownload(socketFD,imageSetName)
				if(request.substr(strlen("/images/XXXXX/"))=="delete"){
					imageSetDelete(socketFD,imageSetName);
				}else if(request.substr(strlen("/images/XXXXX/"))=="download"){
					imageSetDownload(socketFD,imageSetName);
				}else sendHTMLFile(socketFD,request.substr(1)); //if it is /images/setNumber/something
			} else sendHTML_ImageSet(socketFD,imageSetName);
		}
	}else if(request=="/capturePicture"){
		//tell PIs to capture the picture
		//load new page - prefiably redirects to the home page
		//i mean it really changes the location of the page to the index page
		std::string nextSetName=makeNextImageSet();
		sendCaptureCommand_All();
		redirectPage(socketFD,"/images/"+nextSetName);
	}else{ //default - try to load the file
		if(request[0]=='/')
			sendHTMLFile(socketFD,"www"+request);
		else
			sendHTMLFile(socketFD,"www/"+request);
	}
	close(socketFD);
}

std::string getRequestedPage(std::string header){
	//grabs the URL from the first line of a header
	if(header.substr(0,3)=="GET"){
		int index=header.find(' ',5);
		std::string URL = header.substr(4,index-4);
		
		index=URL.find('%');
		while(index>0 && index<URL.length()){
			std::string temp;
			temp=URL.substr(0,index);
			int firstHEX=URL[index+1]-'0'; if(firstHEX<0)firstHEX+='A';
			int secHEX=URL[index+2]-'0'; if(secHEX<0)secHEX+='A';
			temp+=(char)(firstHEX*16 + secHEX);
			temp+=URL.substr(index+3);
			URL=temp;
			index=URL.find('%');
		}

		return URL;
	}
	return "/404.html"; //error, cant find the stuff mate
}

void sendHTMLFile(int socketFD,std::string request){
	static std::string response200="HTTP/1.1 200 OK\r\n\r\n";
	static std::string response404="HTTP/1.1 404 Not Found\r\n\r\n";
	static std::string response301="HTTP/1.1 301 Moved Permanently\n\rLocation: /\r\n\r\n";

	//start with trying to open the file
	std::vector<char> response;
	char buf[256];
	int charsRead=255;
	FILE* input=fopen(request.c_str(),"r");

	//check that the file could be opened
	if(input==NULL){
		//cant open
		FILE* input=fopen("www/404.html","r");
		for(int x=0;x<response404.length();x++)response.push_back(response404[x]);
		if(input!=NULL){
			while(charsRead==255){
				bzero(buf,256);
				charsRead=fread(buf,1,255,input);
				for(int x=0;x<charsRead;x++)
					response.push_back(buf[x]);
			}
			fclose(input);
		}
	}else{
		//default load file and give to the client
		for(int x=0;x<response200.length();x++)response.push_back(response200[x]);
		//printf("=============================\n%s\n\n\n", response.buf);
		while(charsRead==255){
			bzero(buf,256);
			charsRead=fread(buf,1,255,input);
			for(int x=0;x<charsRead;x++)
					response.push_back(buf[x]);
			//printf("=============================\n%s\n\n\n", response.buf);
		}
		fclose(input);
	}

	//we have the file in memory
	//parse the file text and replace special symbols
	response.push_back((char)0); //give the end of string char just to make sure
	replaceSymbols(response);

	//give the parsed file to the user
	write(socketFD,response.data(),response.size());
}

void replaceSymbols(std::vector<char> &input){
	//finds special symbols and replaces them with special information
	//this is the second major place that branches off doing stuff

	if(strstr(input.data(),"<html>") < strstr(input.data(),"</html>")){
		//if this is an HTML document, then look
		//this is to safeguard us screwing with binary files such as images

		std::string doc=input.data();

		//DEBUG FLAGS
		unsigned long index=doc.find("<?raspi testFlag?>");
		while(index>0 && index<doc.length()){
			std::string temp;
			temp=doc.substr(0,index);
			temp+="<h2>Test Flag Works</h2>";
			temp+=doc.substr(index+strlen("<?raspi testFlag?>"));
			doc=temp;
			index=doc.find("<?raspi testFlag?>");
		}
		index=doc.find("<?raspi debugFlag?>");
		while(index>0 && index<doc.length()){
			std::string temp;
			temp=doc.substr(0,index);
			temp+="<h2>Debug Info</h2>\n";
			temp+="<p>Admin Server version 0.1.0</p>\n";
			temp+="<p>This is highly experimental, apparently stable, with few features. Expect massive changes, namely with the hard coded paths and extra flags</p>";
			temp+=doc.substr(index+strlen("<?raspi debugFlag?>"));
			doc=temp;
			index=doc.find("<?raspi debugFlag?>");
		}

		// RASPI info stuffs
		index=doc.find("<?raspi listIPs?>");
		while(index>0 && index<doc.length()){
			std::string temp;
			temp=doc.substr(0,index);
			temp+="<div class='IPList'>";
			for(int x=0;x<globalIPList.length();x++){
				temp+="<p>";
				temp+=globalIPList[x].address;
				temp+="</p>";
			}
			temp+="</div>";
			temp+=doc.substr(index+strlen("<?raspi listIPs?>"));
			doc=temp;
			index=doc.find("<?raspi listIPs?>");
		}
		index=doc.find("<?raspi listPIs?>");
		while(index>0 && index<doc.length()){
			std::string temp;
			temp=doc.substr(0,index);
			temp+="<div class='PIList'>";
			for(int x=0;x<globalIPList.length();x++){
				temp+="<div class='PIInfo'>";
					temp+="<p class='Address'>";
					temp+=globalIPList[x].address;
					temp+="</p>";
					temp+="<p class='Role'>";
					temp+=globalIPList[x].role;
					temp+="</p>";
				temp+="</div>";
			}
			temp+="</div>";
			temp+=doc.substr(index+strlen("<?raspi listPIs?>"));
			doc=temp;
			index=doc.find("<?raspi listPIs?>");
		}

		//IMAGES and stuff
		index=doc.find("<?raspi listImageSets?>");
		while(index>0 && index<doc.length()){
			std::string temp;
			temp=doc.substr(0,index);
			std::vector<std::string> dirContents=listDirectoryContents("images");
			temp+="<div class='ImageSetList'>";
			for(int x=0;x<dirContents.size();x++){
				temp+="<a class='imageSetName' ";
				temp+="href='/images/"; temp+=dirContents[x]; temp+="'>";
				temp+=dirContents[x];
				temp+="</a>";
			}
			temp+="</div>";
			temp+=doc.substr(index+strlen("<?raspi listImageSets?>"));
			doc=temp;
			index=doc.find("<?raspi listImageSets?>");
		}
		index=doc.find("<?raspi listImages/");
		while(index>0 && index<doc.length()){
			std::string setName=doc.substr(index+strlen("<?raspi listImages/"),5);
			std::string temp;
			temp=doc.substr(0,index);
			std::vector<std::string> dirContents=listDirectoryContents("images/"+setName);
			temp+="<div class='ImageSet_ImageList'>";
			for(int x=0;x<dirContents.size();x++){
				temp+="<a class='imageName' href='/images/"; temp+=setName+'/'+dirContents[x]; temp+="'>";
				temp+="<img src='/images/"; temp+=setName+'/'+dirContents[x]; temp+="'>";
				//temp+=dirContents[x];
				temp+="</img></a>";
			}
			temp+="</div>";
			temp+=doc.substr(index+strlen("<?raspi listImages/XXXXX?>"));
			doc=temp;
			index=doc.find("<?raspi listImages/");
		}
		index=doc.find("<?raspi imageSetDownloadURL/");
		while(index>0 && index<doc.length()){
			std::string setName=doc.substr(index+strlen("<?raspi imageSetDownloadURL/"),5);
			std::string temp;
			temp=doc.substr(0,index);
			temp+="/images/"+setName+"/download";
			temp+=doc.substr(index+strlen("<?raspi imageSetDownloadURL/XXXXX?>"));
			doc=temp;
			index=doc.find("<?raspi imageSetDownloadURL/");
		}
		index=doc.find("<?raspi imageSetDeleteURL/");
		while(index>0 && index<doc.length()){
			std::string setName=doc.substr(index+strlen("<?raspi imageSetDeleteURL/"),5);
			std::string temp;
			temp=doc.substr(0,index);
			temp+="/images/"+setName+"/delete";
			temp+=doc.substr(index+strlen("<?raspi imageSetDeleteURL/XXXXX?>"));
			doc=temp;
			index=doc.find("<?raspi imageSetDeleteURL/");
		}
		//<?raspi imageSetDeleteURL/XXXXX?>

		std::vector<char> temp;
		temp.reserve(doc.length());
		for(int x=0;x<doc.length();x++){
			temp.push_back(doc[x]);
		}
		temp.push_back((char)0); //the std::string strips out the null on the end
		input=temp;
	}
	return;
}

void sendHTML_ImageSet(int socketFD,std::string setName){
	static std::string response200="HTTP/1.1 200 OK\r\n\r\n";
	static std::string response404="HTTP/1.1 404 Not Found\r\n\r\n";
	static std::string response301="HTTP/1.1 301 Moved Permanently\n\rLocation: /\r\n\r\n";

	//start with trying to open the file
	std::string response;
	char buf[256];
	int charsRead=255;
	FILE* input=fopen("www/imageSets.html","r");

	//check that the file could be opened
	if(input==NULL){
		//cant open
		FILE* input=fopen("www/404.html","r");
		for(int x=0;x<response404.length();x++)response+=(response404[x]);
		if(input!=NULL){
			while(charsRead==255){
				bzero(buf,256);
				charsRead=fread(buf,1,255,input);
				for(int x=0;x<charsRead;x++)
					response+=(buf[x]);
			}
			fclose(input);
		}
	}else{
		//default load file and give to the client
		for(int x=0;x<response200.length();x++)response+=(response200[x]);
		//printf("=============================\n%s\n\n\n", response.buf);
		while(charsRead==255){
			bzero(buf,256);
			charsRead=fread(buf,1,255,input);
			for(int x=0;x<charsRead;x++)
					response+=(buf[x]);
			//printf("=============================\n%s\n\n\n", response.buf);
		}
		fclose(input);
	}

	//we have the file in memory
	//parse the file text and replace special symbols
	replaceSymbols_ImageSet(response,setName);

	//give the parsed file to the user
	write(socketFD,response.data(),response.size());
}
void replaceSymbols_ImageSet(std::string& doc, std::string setName){
	//replace the special tags with the generic tags and the iamge set name filled in
	//the work has been done, so might as well just use it
	//the tags to do this with
	// - currentSetImages
	// - currentSetDownloadURL
	// - currentSetDeleteURL

	//tags that are to be done here only
	// - currentSetNum
	// - currentSetDownload
	// - currentSetDelete

	unsigned long index=doc.find("<?raspi currentSetImages?>");
	while(index>0 && index<doc.length()){
		std::string temp;
		temp=doc.substr(0,index);
		temp+="<?raspi listImages/"+setName+"?>";
		temp+=doc.substr(index+strlen("<?raspi currentSetImages?>"));
		doc=temp;
		index=doc.find("<?raspi currentSetImages?>");
	}
	index=doc.find("<?raspi currentSetDownloadURL?>");
	while(index>0 && index<doc.length()){
		std::string temp;
		temp=doc.substr(0,index);
		temp+="<?raspi imageSetDownloadURL/"+setName+"?>";
		temp+=doc.substr(index+strlen("<?raspi currentSetDownloadURL?>"));
		doc=temp;
		index=doc.find("<?raspi currentSetDownloadURL?>");
	}
	index=doc.find("<?raspi currentSetDeleteURL?>");
	while(index>0 && index<doc.length()){
		std::string temp;
		temp=doc.substr(0,index);
		temp+="<?raspi imageSetDeleteURL/"+setName+"?>";
		temp+=doc.substr(index+strlen("<?raspi currentSetDeleteURL?>"));
		doc=temp;
		index=doc.find("<?raspi currentSetDeleteURL?>");
	}

	//===================================================================================================

	index=doc.find("<?raspi currentSetNum?>");
	while(index>0 && index<doc.length()){
		std::string temp;
		temp=doc.substr(0,index);
		temp+=setName;
		temp+=doc.substr(index+strlen("<?raspi currentSetNum?>"));
		doc=temp;
		index=doc.find("<?raspi currentSetNum?>");
	}
	index=doc.find("<?raspi currentSetDownload?>");
	while(index>0 && index<doc.length()){
		std::string temp;
		temp=doc.substr(0,index);
		temp+="<button onclick='location.href=\"/images/"+setName+"/download\"'>Download</button>";
		temp+=doc.substr(index+strlen("<?raspi currentSetDownload?>"));
		doc=temp;
		index=doc.find("<?raspi currentSetDownload?>");
	}
	index=doc.find("<?raspi currentSetDelete?>");
	while(index>0 && index<doc.length()){
		std::string temp;
		temp=doc.substr(0,index);
		temp+="<button onclick='location.href=\"/images/"+setName+"/delete\"''>Delete</button>";
		temp+=doc.substr(index+strlen("<?raspi currentSetDelete?>"));
		doc=temp;
		index=doc.find("<?raspi currentSetDelete?>");
	}

	//standard special tag parsing
	//this is also where the overloaded tag replacing work is done
	std::vector<char> v;
	v.reserve(doc.length());
	for(int x=0;x<doc.length();x++)
		v.push_back(doc[x]);
	v.push_back((char)0);
	replaceSymbols(v); //parse all the normal tags also
	std::string temp;
	for(int x=0;x<v.size();x++)
		temp+=v[x];
	doc=temp;
}

std::string makeNextImageSet(){
	std::vector<std::string> dirContents=listDirectoryContents("images");
	if(dirContents.size()==0){
		system("mkdir images"); //make sure the folder exists in the first place
		system("mkdir images/00001");
		return "00001"; //already did the work
	}
	int last=atoi(dirContents[dirContents.size()-1].c_str());
	last++;
	std::string nextSetName="mkdir images/";
	nextSetName+=itoa(last);
	system(nextSetName.c_str());
	return itoa(last);
}
std::string itoa(unsigned int here){
	//unsigned numbers and assumes unlimited buffer
	std::string buf="";
	while(here){
		buf+= (here%10) + '0';
		here/=10;
	}

	//now reverse buf
	char temp;
	for(int x=0;x<buf.length()/2;x++){
		temp=buf[x];
		buf[x]=buf[buf.length()-x-1];
		buf[buf.length()-x-1]=temp;
	}
	while(buf.length()<5) buf='0'+buf; //pad the front with zeros
	return buf;
}
void imageSetDelete(int socketFD,std::string imageSetName){
	std::string command="rm -rf images/";
	command+=imageSetName;
	system(command.c_str());

	redirectPage(socketFD,"/images");
}

void redirectPage(int socketFD,std::string here){
	static std::string response301="HTTP/1.1 301 Moved Permanently\n\rLocation: /\r\n\r\n";
	std::string page="<html><script>location='";
	page+=here;
	page+="'</script></html>\r\n";
	write(socketFD,response301.c_str(),response301.length());
	write(socketFD,page.c_str(),page.length());
}

void imageSetDownload(int socketFD,std::string imageSetName){
	redirectPage(socketFD,imageSetName);
}
#include "raspicam/src/raspicam_still.h"
#include "raspicam/src/raspicamtypes.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	raspicam::RaspiCam_Still cam;
	if(!cam.open()){
		printf("Unable to open Camera\n");
		exit(1);
	}
	cam.setCaptureSize(1280,960);
	//cam.setFormat(raspicam::RASPICAM_FORMAT_YUV420);
	cam.setEncoding(raspicam::RASPICAM_ENCODING_PNG);

	size_t bufSize = cam.getImageBufferSize();
	unsigned char* buf = (unsigned char*)malloc(bufSize);
	for(int x=0;x<60;x++) cam.grab_retrieve(buf,bufSize); //get the image into our buffer

	for(unsigned long x=0;x<bufSize;x++){
		printf("%c",buf[x]); //put the image on the stdout
	}

	cam.release();
	free(buf);

	return 0;
}

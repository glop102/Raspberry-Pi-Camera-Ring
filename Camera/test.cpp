#include "raspicam/src/raspicam_still.h"
#include "raspicam/src/raspicam.h"
#include "raspicam/src/raspicamtypes.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void captureStill(raspicam::RaspiCam_Still& cam){
	size_t bufSize = cam.getImageBufferSize();
	unsigned char* buf = (unsigned char*)malloc(bufSize);
	cam.grab_retrieve(buf,bufSize);

	for(unsigned long x=0;x<bufSize;x++){
		printf("%c",buf[x]); //put the image on the stdout
	}

	cam.release();
	free(buf);
}

int main(){
	//raspicam::RaspiCam preview;
	raspicam::RaspiCam_Still still;
	//preview.setFormat(raspicam::RASPICAM_FORMAT_RGB);
	still.setEncoding(raspicam::RASPICAM_ENCODING_PNG);
	still.setCaptureSize(1200,960);
	//if(!preview.open()){
	//	printf("Unable to open Camera\n");
	//	exit(1);
	//}
	if(!still.open()){
		printf("Unable to open Camera\n");
		exit(1);
	}
	sleep(1); //wait for a stable image
	//preview.setFormat(raspicam::RASPICAM_FORMAT_RGB);
	//still.setEncoding(raspicam::RASPICAM_ENCODING_PNG);

	captureStill(still);

	return 0;
}

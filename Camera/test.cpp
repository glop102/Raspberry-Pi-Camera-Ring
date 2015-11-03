#include "raspicam/src/raspicam_still.h"
#include "raspicam/src/raspicam.h"
#include "raspicam/src/raspicamtypes.h"
#include <stdlib.h>
#include <stdio.h>

void captureStill(raspicam::RaspiCam_Still& cam){
	size_t bufSize = cam.getImageBufferSize();
	unsigned char* buf = (unsigned char*)malloc(bufSize);
<<<<<<< HEAD
	cam.grab_retrieve(buf,bufSize);
		
=======
	for(int x=0;x<60;x++) cam.grab_retrieve(buf,bufSize); //get the image into our buffer

>>>>>>> 026104e3257385f5d702ac600aee08b5267feca6
	for(unsigned long x=0;x<bufSize;x++){
		printf("%c",buf[x]); //put the image on the stdout
	}

	cam.release();
	free(buf);
}

int main(){
	raspicam::RaspiCam preview;
	raspicam::RaspiCam_Still still;
	if(!preview.open()){
		printf("Unable to open Camera\n");
		exit(1);
	}
	if(!still.open()){
		printf("Unable to open Camera\n");
		exit(1);
	}
	preview.setFormat(raspicam::RASPICAM_FORMAT_RGB);
	still.setEncoding(raspicam::RASPICAM_ENCODING_PNG);

	captureStill(still);

	return 0;
}

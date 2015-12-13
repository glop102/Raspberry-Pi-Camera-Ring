#ifndef __CAMERACOMMANDS
#define __CAMERACOMMANDS

#include <stdio.h>
#include <stdlib.h>
#include "png++/png.hpp"
#include "globals.h"

class ImageBuffer{
	/*
	* Handles the life of the array of 
	*/
private:
	unsigned char* buf;
	size_t bufSize;
public:
	ImageBuffer(){
		this->bufSize = cam.getImageBufferSize();
		this->buf = (unsigned char*)malloc(bufSize);
	}
	ImageBuffer(ImageBuffer& other){
		this->bufSize = other.size();
		this->buf = (unsigned char*)malloc(bufSize);
		for(unsigned int x=0;x<bufSize;x++) this->buf[x] = other[x];
	}
	~ImageBuffer(){
		free(buf);
	}

	unsigned char operator[](unsigned int index){
		return buf[index];
	}
	//void operator=(ImageBuffer& other){
	//	this->bufSize = other.size();
	//	this->buf = (unsigned char*)malloc(bufSize);
	//	for(unsigned int x=0;x<bufSize;x++) this->buf[x] = other[x];
	//}
	unsigned char* raw_array(){
		return this->buf;
	}
	size_t size(){
		return this->bufSize;
	}
};

void takeImage_toFile();
ImageBuffer takeImage();
void saveImageToFile(ImageBuffer& buf, std::string filename);

void takeImage_toFile(){
	/*
	* Takes a picture, encodes it, and dumps it to a file "output.png"
	*/
	//size_t bufSize = cam.getImageBufferSize();
	//unsigned char* buf = (unsigned char*)malloc(bufSize);
	//cam.grab();
	//cam.retrieve(buf);

	//png::image< png::rgb_pixel > image(2560, 1920);
	//int counter=0;
	//for (png::uint_32 y = 0; y < image.get_height(); ++y){
	//    for (png::uint_32 x = 0; x < image.get_width(); ++x){
	//        image[y][x] = png::rgb_pixel(buf[counter],buf[counter+1],buf[counter+2]);
	        // non-checking equivalent of image.set_pixel(x, y, ...);
	//        counter+=3;
	//    }
	//}
	//image.write("output.png");

	//free(buf);
	ImageBuffer buf;
	buf=takeImage();
	printf("Image Buffer Size: %d\n",buf.size());
	saveImageToFile(buf,"output.png");
}

ImageBuffer takeImage(){
	/*
	* Retrieves the RGB values from the camera and returns an array of them
	* new method that is faster, a lot faster
	*/
	ImageBuffer buf;
	cam.grab();
	cam.retrieve(buf.raw_array());
	return buf;
}
void saveImageToFile(ImageBuffer& buf, std::string filename){
	png::image< png::rgb_pixel > image(2560, 1920);
//	image.set_interlace_type(png::interlace_none);
//	image.set_compression_type(png::compression_type_base);
	int counter=0;
	for (png::uint_32 y = 0; y < image.get_height(); ++y){
	    for (png::uint_32 x = 0; x < image.get_width(); ++x){
	        image[y][x] = png::rgb_pixel(buf[counter],buf[counter+1],buf[counter+2]);
	        // non-checking equivalent of image.set_pixel(x, y, ...);
	        counter+=3;
	    }
	}
	image.write("output.png");
}

#endif

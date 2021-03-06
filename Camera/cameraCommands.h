#ifndef __CAMERACOMMANDS
#define __CAMERACOMMANDS

#include <stdio.h>
#include <stdlib.h>
#include "png++/png.hpp"
#include "globals.h"
#include "../glopLibs/imageLibrary/image.h"

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
		if(buf==0) printf("error on ImageBuffer allocation\n");
	}
	ImageBuffer(const ImageBuffer& other){
		//printf("copying the buffer\n");
		this->bufSize = other.size();
		this->buf = (unsigned char*)malloc(this->bufSize);
		if(buf==0) printf("error on ImageBuffer allocation\n");
		for(unsigned int x=0;x<bufSize;x++) this->buf[x] = other[x];
	}
	~ImageBuffer(){
		free(buf);
		//printf("buffer freed %d\n",buf);
	}

	unsigned char operator[](unsigned int index) const {
		return this->buf[index];
	}

	unsigned char* raw_array() const {
		return this->buf;
	}
	size_t size() const {
		return this->bufSize;
	}
};

class BufferQueue{
private:
	struct ITEM{
		ImageBuffer buf;
		ITEM* next;
	};
	BufferQueue::ITEM * buffer;
public:
	BufferQueue(){
		buffer=0;
	}
	void add(ImageBuffer other){
		auto newest = new ITEM{other,0};
		//newest->buf = other;
		//newest->next= 0;
		if(this->buffer==0){
			this->buffer=newest;
		}else{
			auto temp=this->buffer;
			while(temp->next != 0) temp=temp->next;
			temp->next=newest;
		}
	}
	ImageBuffer pop(){
		if(this->buffer==0){
			ImageBuffer temp;
			return temp;
		}
		ImageBuffer temp(this->buffer->buf); //save the image buffer
		auto temp2=this->buffer; //save the current struct
		this->buffer=this->buffer->next; //move to the next struct
		delete temp2; //delete the old struct
		return temp;
	}
	bool hasNext(){
		if(buffer)return true;
		return false;
	}
};

BufferQueue bufferQueue;

void takeImage_toFile();
ImageBuffer takeImage();
void saveImageToFile(ImageBuffer& buf, std::string filename);
void saveImageToFile__PNGLIB(ImageBuffer& buf, std::string filename);
//void saveImageToFile(unsigned char* buf, std::string filename);
extern void sendImageBack(std::string);

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
	ImageBuffer buf=takeImage();
	saveImageToFile(buf,"output.png");
}

ImageBuffer takeImage(){
	/*
	* Retrieves the RGB values from the camera and returns an array of them
	* new method that is faster, a lot faster
	*/
	ImageBuffer buf;
	printf("Taking New Image\n");
	cam.grab();
	cam.retrieve(buf.raw_array());
	return buf;
}
void saveImageToFile__PNGLIB(ImageBuffer& buf, std::string filename){
//void saveImageToFile(unsigned char* buf,std::string filename){
	png::image< png::rgb_pixel > image(2560, 1920);
	image.set_interlace_type(png::interlace_none);
	image.set_compression_type(png::compression_type_default);
	int counter=0;
	for (png::uint_32 y = 0; y < image.get_height(); ++y){
	    for (png::uint_32 x = 0; x < image.get_width(); ++x){
	        image[y][x] = png::rgb_pixel(buf[counter],buf[counter+1],buf[counter+2]);
	        // non-checking equivalent of image.set_pixel(x, y, ...);
	        counter+=3;
	    }
	}
	image.write(filename.c_str());
}
void saveImageToFile(ImageBuffer& buf, std::string filename){
	Image im(2560, 1920,RGB);

	for(unsigned long y=0 ; y<im.height() ; y++){
		for(unsigned long x=0 ; x<im.width() ; x++){
			Pixel pix;
			pix.R=buf[(3*y*im.width()) + 3*x + 0];
			pix.G=buf[(3*y*im.width()) + 3*x + 1];
			pix.B=buf[(3*y*im.width()) + 3*x + 2];
			im[y][x] = pix;

		}
	}
	im.saveImage(filename,BMP,0);
}

void * encodingQueueThread(void* nada){
	while(1){
		while(bufferQueue.hasNext()){
			ImageBuffer temp=bufferQueue.pop();
			printf("Encoding New Image\n");
			saveImageToFile(temp,"output.png");
			printf("Saved Image\n");
			sendImageBack(adminAddress);
			printf("Sent Image\n");
		}
		sleep(1);
	}
	return 0;
}

#endif

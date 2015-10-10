#include "buffer.h"

buffer::~buffer(){
	if(this->buf!=NULL) free(this->buf);
	this->buf=NULL;
}
buffer::buffer(){
	this->buf=NULL;
	this->clear();
}
buffer::buffer(char input){
	this->buf=NULL;
	this->clear();
	(*this)+=input;
}
buffer::buffer(char* input){
	this->buf=NULL;
	this->clear();
	(*this)+=input;
}
buffer::buffer(const buffer& input){
	this->buf=NULL;
	this->clear();
	(*this).append(input.buf,input.length);
}
buffer::buffer(const std::string& input){
	this->buf=NULL;
	this->clear();
	(*this)+=input;
}
void buffer::clear(){
	this->buf=(char*)realloc(this->buf,1);
	this->length=0;
}
void buffer::operator+=(char input){
	this->append(&input,1);
}
void buffer::operator+=(const char* input){
	//warning - some sort of magic sauce here that makes it work for strings
	//this sauce was added because of a buffer overflow issue
	//this occured when parsing text in the web browser
	this->buf[this->length-1]=*input;
	this->append(input+1,strlen(input));
}
void buffer::append(const char* input,unsigned int inputLength){
	//adds the input to the end of the internal buffer
	//this is what every other method eventually gets to

	char* other=(char*)malloc(this->length+inputLength);
	//copy the old to the new
	unsigned int curt=0;
	while(curt<this->length){
		other[curt]=this->buf[curt];
		curt++;
	}
	free(this->buf);
	this->buf=other;
	//copy in the new
	curt=0;
	while(curt<inputLength){
		this->buf[this->length+curt]=input[curt];
		curt++;
	}
	this->length+=inputLength;
}
void buffer::operator+=(const buffer& input){
	this->append(input.buf,input.length);
}
void buffer::operator+=(std::string input){
	this->append(input.c_str(),input.length());
}
void buffer::operator=(const buffer& other){
	this->clear(); //stop memory leaks
	(*this).append(other.buf,other.length);
}
void buffer::operator=(buffer* other){
	this->clear(); //stop memory leaks
	(*this).append(other->buf,other->length);
}
void buffer::operator=(char input){
	this->clear();
	(*this)+=input;
}
void buffer::operator=(const char* input){
	this->clear();
	(*this)+=input;
}
void buffer::operator=(std::string input){
	this->clear();
	(*this)+=input;
}
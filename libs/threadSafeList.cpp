#include "threadSafeList.h"

threadSafeList::threadSafeList(){
}
std::string threadSafeList::operator[](unsigned int index){
	std::lock_guard<std::mutex> threadSafety(this->working); //makes this class thread safe
	return this->buf[index];
}
void threadSafeList::remove(unsigned int index){
	std::lock_guard<std::mutex> threadSafety(this->working); //makes this class thread safe
	this->buf.erase(this->buf.begin()+index);
}
void threadSafeList::remove(std::string input){
	std::lock_guard<std::mutex> threadSafety(this->working); //makes this class thread safe
	for(int x=0;x<this->buf.size();x++){
		if(this->buf[x]==input) this->remove(x);
	}
}
void threadSafeList::append(std::string input){
	std::lock_guard<std::mutex> threadSafety(this->working); //makes this class thread safe
	this->buf.push_back(input);
}
void threadSafeList::clear(){
	std::lock_guard<std::mutex> threadSafety(this->working); //makes this class thread safe
	this->buf.clear();
}
int threadSafeList::find(std::string input){
	std::lock_guard<std::mutex> threadSafety(this->working); //makes this class thread safe
	for(int x=0;x<this->buf.size();x++){
		if(this->buf[x]==input)return x;
	}
	return -1;
}
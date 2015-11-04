#include "threadSafeList.h"

template <class ttt>
threadSafeList<ttt>::threadSafeList(){
}
template <class ttt>
ttt threadSafeList<ttt>::operator[](unsigned int index){
	std::lock_guard<std::mutex> threadSafety(this->working); //makes this class thread safe
	return this->buf[index];
}
template <class ttt>
void threadSafeList<ttt>::remove(unsigned int index){
	std::lock_guard<std::mutex> threadSafety(this->working); //makes this class thread safe
	this->buf.erase(this->buf.begin()+index);
}
template <class ttt>
void threadSafeList<ttt>::remove(ttt input){
	std::lock_guard<std::mutex> threadSafety(this->working); //makes this class thread safe
	for(int x=0;x<this->buf.size();x++){
		if(this->buf[x]==input) this->remove(x);
	}
}
template <class ttt>
void threadSafeList<ttt>::append(ttt input){
	std::lock_guard<std::mutex> threadSafety(this->working); //makes this class thread safe
	this->buf.push_back(input);
}
template <class ttt>
void threadSafeList<ttt>::clear(){
	std::lock_guard<std::mutex> threadSafety(this->working); //makes this class thread safe
	this->buf.clear();
}
template <class ttt>
int threadSafeList<ttt>::find(ttt input){
	std::lock_guard<std::mutex> threadSafety(this->working); //makes this class thread safe
	for(int x=0;x<this->buf.size();x++){
		if(this->buf[x]==input)return x;
	}
	return -1;
}
template <class ttt>
int threadSafeList<ttt>::length(){
	std::lock_guard<std::mutex> threadSafety(this->working); //makes this class thread safe
	return this->buf.size();
}
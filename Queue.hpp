// Author: Alexander Edwards



#ifndef QUEUE_HPP_
#define QUEUE_HPP_
#include "List.hpp"
#include <iostream>
// ============ class definition ================
template <typename TYPE>
class Queue : public List<TYPE> {
public:
	Queue();
	TYPE showTop();
	virtual ~Queue();
	void enQueue(TYPE dataIn);
	TYPE deQueue();
};

/*******************************************************************************
 * It's best implementation not be in a header file but for ease of compiling  *
 * I kept in the header. I may move the implementation into a separate file.   *
 * That being said pretend it isn't here.                                      *
 *******************************************************************************/

template <typename TYPE>
void Queue<TYPE>::enQueue(TYPE dataIn){
	this->append(dataIn);
}
template <typename TYPE>
TYPE Queue<TYPE>::showTop(){
	return this->peekAt(this->headOfList());
}
template <typename TYPE>
TYPE Queue<TYPE>::deQueue(){
	TYPE queueThis = this->peekAt(this->headOfList());
	this->removeThisItem(this->headOfList());
	return queueThis;
}
template <typename TYPE>
Queue<TYPE>::Queue(): List<TYPE>() {
	// I believe parent constructor will suffice

}

template <typename TYPE>
Queue<TYPE>::~Queue() {

}
#endif /* QUEUE_H_ */

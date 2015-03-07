// Alexander Edwards
// CISP 430 Wednesday 6-9pm
// Spring 2015
// Assignment #2

#include "List.h"
#ifndef QUEUE_H_
#define QUEUE_H_

template <typename TYPE>
class Queue : public List<TYPE> {
public:
	Queue();
	virtual ~Queue();
	void enQueue(TYPE dataIn);
	TYPE deQueue();
};
template <typename TYPE>
void Queue<TYPE>::enQueue(TYPE dataIn){
	this->insert(dataIn, this->end(), List<TYPE>::After);
}
template <typename TYPE>
TYPE Queue<TYPE>::deQueue(){
	TYPE temp = this->peek(this->start());
	this->remove(this->start());
	return temp;
}
template <typename TYPE>
Queue<TYPE>::Queue(): List<TYPE>() {
	// TODO Auto-generated constructor stub

}

template <typename TYPE>
Queue<TYPE>::~Queue() {
	// TODO Auto-generated destructor stub
}
#endif /* QUEUE_H_ */

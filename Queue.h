/* Alexander Edwards
 * CISP 430 Wednesday 6-9pm
 * Spring 2015
 * assignment #3
 */

#include "List.h"
#ifndef QUEUE_H_
#define QUEUE_H_
#include <iostream>
// ============ class definition ================
template <typename TYPE>
class Queue : public List<TYPE> {
public:
	Queue();
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
	// I believe parent constructor will suffice

}

template <typename TYPE>
Queue<TYPE>::~Queue() {

}
#endif /* QUEUE_H_ */

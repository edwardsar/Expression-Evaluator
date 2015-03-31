/* Alexander Edwards
 * CISP 430 Wednesday 6-9pm
 * Spring 2015
 * assignment #3
 */

#include "List.h"
#ifndef STACK_H_
#define STACK_H_

// ============ class definition ================
template <typename TYPE>
class Stack: public List<TYPE> {
public:
	Stack();
	virtual ~Stack();
	void push(TYPE dataIn);
	TYPE pop();
	TYPE showTop();
};

/*******************************************************************************
 * It's best implementation not be in a header file but for ease of compiling  *
 * I kept in the header. I may move the implementation into a separate file.   *
 * That being said pretend it isn't here.                                      *
 *******************************************************************************/

// ==== showTop ========
template <typename TYPE>
TYPE Stack<TYPE>::showTop(){
	return this->peek(this->start());
}

// ==== pop =====
template <typename TYPE>
TYPE Stack<TYPE>::pop(){
	TYPE temp = showTop();
	this->remove(this->start());
	return temp;
}

// ==== push ====
template <typename TYPE>
void Stack<TYPE>::push(TYPE dataIn){
	this->insert(dataIn, this->start(), List<TYPE>::Before);
}

// ==== constructor =====
template <typename TYPE>
Stack<TYPE>::Stack(): List<TYPE>(){
	// I believe the parent constructor will suffice
}

// ==== destructor ====
template <typename TYPE>
Stack<TYPE>::~Stack(){
	// I believe parent deconstructor will suffice
}
#endif /* STACK_H_ */

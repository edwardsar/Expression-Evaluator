/*
 * author: Alexander Edwards
 */


#ifndef STACK_H_
#define STACK_H_
#include "List.hpp"

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
	return this->peekAt(this->headOfList());
}

// ==== pop =====
template <typename TYPE>
TYPE Stack<TYPE>::pop(){
	TYPE popThis = this->peekAt(this->headOfList());
	this->removeThisItem(this->headOfList());
	return popThis;
}

// ==== push ====
template <typename TYPE>
void Stack<TYPE>::push(TYPE dataIn){
	this->prepend(dataIn);
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

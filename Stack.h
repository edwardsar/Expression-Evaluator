// Alexander Edwards
// CISP 430 Wednesday 6-9pm
// Spring 2015
// Assignment #2

#include "List.h"
#ifndef STACK_H_
#define STACK_H_

template <typename TYPE>
class Stack: public List<TYPE> {
public:
	Stack();
	virtual ~Stack();
	void push(TYPE dataIn);
	void pop();
	TYPE showTop();
};
// ==== showTop ========
template <typename TYPE>
TYPE Stack<TYPE>::showTop(){
	return this->peek(this->start());
}

// ==== pop =====
template <typename TYPE>
void Stack<TYPE>::pop(){
	this->remove(this->start());
}

// ==== push ====
template <typename TYPE>
void Stack<TYPE>::push(TYPE dataIn){
	this->insert(dataIn, this->start(), List<TYPE>::Before);
}

// ==== constructor =====
template <typename TYPE>
Stack<TYPE>::Stack(): List<TYPE>(){

}

// ==== destructor ====
template <typename TYPE>
Stack<TYPE>::~Stack(){

}
#endif /* STACK_H_ */

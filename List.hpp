/*
 * Author: Alexander Edwards
 */


#ifndef LIST_HPP_
#define LIST_HPP_
#include "ListNode.hpp"
#include <iostream>
// ======= class definition =======
template <typename TYPE>
class List {
public:
	// ======= Iterator definition =======
	class Iterator {
	public:
		void getNext(){ptr = ptr->getNext(); }
		void getPrev(){ptr = ptr->getPrev(); }
		TYPE getData(){return ptr->getData();}
		void startAtHead(){ ptr = coupledList->start(); }
		void startAtTail(){ ptr = coupledList->end(); }
		bool end(){ return ptr == nullptr;}
		void operator=(List<TYPE>::Iterator sourceOfCopy){	ptr = sourceOfCopy.ptr; coupledList = sourceOfCopy.coupledList;}
		Iterator(){ ptr = nullptr; coupledList = nullptr;}
	private:
		Iterator(List<TYPE>* listToCoupleWith){ coupledList = listToCoupleWith; ptr = nullptr;}
		friend class List<TYPE>;
		ListNode<TYPE>* ptr;
		List<TYPE>* coupledList;
	};
	// ---- end Iterator definition ----
	List();
	virtual ~List();
	bool isEmpty() const;
	bool search(TYPE dataKey) const;
	int size() const;
	void append(TYPE dataIn);
	void prepend(TYPE dataIn);
	void remove(ListNode<TYPE>* removeFrom);
	TYPE peek(ListNode<TYPE>* peekAt);
	bool isFull();
	void removeAllListEntries();
	List<TYPE>::Iterator getIterator();
protected:
	enum InsertPlacementModifier { Before, After};
	void insertHere(TYPE dataIn, InsertPlacementModifier placementModifier, ListNode<TYPE>* insertHerePtr);
	ListNode<TYPE>* start();
	ListNode<TYPE>* end();
private:
	ListNode<TYPE> *head, *tail;
	unsigned int listSize;
};

/*******************************************************************************
 * It's best implementation not be in a header file but for ease of compiling  *
 * I kept in the header. I may move the implementation into a separate file.   *
 * That being said pretend it isn't here.                                      *
 *******************************************************************************/
// ==== getIterator ====
template <typename TYPE>
typename List<TYPE>::Iterator List<TYPE>::getIterator(){
	return List<TYPE>::Iterator(this);
}
// ==== start ====
template <typename TYPE>
ListNode<TYPE>* List<TYPE>::start(){
	return head;
}
// ====== end ====
template <typename TYPE>
ListNode<TYPE>* List<TYPE>::end(){
	return tail;
}
// ==== peek ====
template <typename TYPE>
TYPE List<TYPE>::peek(ListNode<TYPE>* peekAt){
	return peekAt->getData();
}
// ====== prepend =======
template <typename TYPE>
void List<TYPE>::prepend(TYPE dataIn){
		insertHere(dataIn, Before, head);
}
// ====== append =======
template <typename TYPE>
void List<TYPE>::append(TYPE dataIn){
		insertHere(dataIn, After, tail);
}
// ====== insertHere =======
template <typename TYPE>
void List<TYPE>::insertHere(TYPE dataIn, InsertPlacementModifier placementModifier,  ListNode<TYPE>* insertHerePtr){
	// special empty list case
	if( this->isEmpty() ){
		head = tail = new ListNode<TYPE>(dataIn,nullptr, nullptr);
	}
	else if( placementModifier == Before){
		// insert before head
		if ( insertHerePtr->getPrev() == nullptr){
				head = new ListNode<TYPE>(dataIn,nullptr,head);
				head->getNext()->setPrev(head);
		}
		// insert before element pointed to by insertHerePtr
		else{
			insertHerePtr->getPrev()->setNext( new ListNode<TYPE>(dataIn, insertHerePtr->getPrev(), insertHerePtr->getNext()));
			insertHerePtr->getNext()->setPrev(insertHerePtr->getPrev()->getNext());
		}
	}
	else if( placementModifier == After){
		// insert after tail
		if( insertHerePtr->getNext() == nullptr){
			tail = new ListNode<TYPE>(dataIn, tail, nullptr);
			tail->getPrev()->setNext(tail);
		}
		else{
			insertHerePtr->getNext()->setPrev( new ListNode<TYPE>(dataIn, insertHerePtr, insertHerePtr->getNext()));
			insertHerePtr->setNext(insertHerePtr->getNext()->getPrev());
		}
	}
	listSize++;
}
// ====== remove ====
template <typename TYPE>
void List<TYPE>::remove(ListNode<TYPE>* removeFrom){
	// special empty list case
	if(isEmpty()){
		return;
	}
	// list has one element to remove
	else if( head == tail){
		delete head;
		head = tail = nullptr;
		listSize--;
	}
	else{
		// remove head
		if(removeFrom == head){
			head = removeFrom->getNext();
			head->setPrev(nullptr);
		}
		// remove tail
		else if(removeFrom == tail){
			tail = removeFrom->getPrev();
			tail->setNext(nullptr);
		}
		// remove from insertHerePtr iterator points
		else{
			(removeFrom->getPrev())->setNext( removeFrom->getNext() );
			(removeFrom->getNext())->setPrev( removeFrom->getPrev() );
		}
		delete removeFrom;
		listSize--;
	}
}
// ====== size ======
template <typename TYPE>
int List<TYPE>::size() const {
	return listSize;
}

// ==== removeAllListEntries ====
template <typename TYPE>
void List<TYPE>::removeAllListEntries(){
	ListNode<TYPE> *iterator, *tempPlaceHolder;
	iterator = head;
	while(iterator != nullptr){
		tempPlaceHolder = iterator;
		iterator = iterator->getNext();
		delete tempPlaceHolder;
	}
	listSize = 0;
}

// ===== constructor ====
template <typename TYPE>
List<TYPE>::List(){
						head = nullptr;
						tail = nullptr;
						listSize = 0;
}

// ====== destructor ======
template <typename TYPE>
List<TYPE>::~List() {
	removeAllListEntries();
}

// ====== is empty =====
template <typename TYPE>
bool List<TYPE>::isEmpty() const{
	if(listSize > 0)
		return false;
	else
		return true;
}
// ===== search ========
template <typename TYPE>
bool List<TYPE>::search(TYPE dataKey) const {
	ListNode<TYPE>* currentNode;
	currentNode = head;
	if(isEmpty()){
		return false;
	}
	if(currentNode->getData() == dataKey){
		return true;
	}
	while(currentNode->hasNext()){
		currentNode = currentNode->getNext();
		if(currentNode->getData() == dataKey){
			return true;
		}
	}
	return false;
}

#endif /* LIST_H_ */

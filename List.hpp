// Author: Alexander Edwards


#ifndef LIST_HPP_
#define LIST_HPP_
#include "ListNode.hpp"
#include <iostream>
#include <cassert>
// ======= class definition =======
template <typename TYPE>
class List {
public:
	class Iterator {
	public:
		void getNext();
		void getPrev();
		TYPE getData();
		void startAtHead();
		void startAtTail();
		bool end();
		void operator=(List<TYPE>::Iterator sourceOfCopy);
		Iterator();
	private:
		Iterator(List<TYPE>* listToCoupleWith);
		friend class List<TYPE>;
		ListNode<TYPE>* ptr;
		List<TYPE>* coupledList;
	};

	List();
	virtual ~List();
	bool isEmpty() const;
	bool search(TYPE dataKey) const;
	void remove(TYPE dataKey);
	int size() const;
	void append(TYPE dataIn);
	void prepend(TYPE dataIn);
	bool isFull();
	void erase();
	List<TYPE>::Iterator getIterator();
protected:
	enum InsertPlacementModifier { Before, After};
	TYPE peekAt(ListNode<TYPE>* peekAtThisNode);
	void insertHere(TYPE dataIn, InsertPlacementModifier placementModifier, ListNode<TYPE>* insertHerePtr);
	ListNode<TYPE>* headOfList();
	ListNode<TYPE>* tailOfList();
	void removeThisItem(ListNode<TYPE>* removeFromHere);
	ListNode<TYPE>* find(TYPE dataKey) const;
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
// ==== headOfList ====
template <typename TYPE>
ListNode<TYPE>* List<TYPE>::headOfList(){
	return head;
}
// ==== peekAt ====
template <typename TYPE>
TYPE List<TYPE>::peekAt(ListNode<TYPE>* peekAtThisNode){
	assert(peekAtThisNode != nullptr);
	return peekAtThisNode->getData();
}
// ====== tailOfList ====
template <typename TYPE>
ListNode<TYPE>* List<TYPE>::tailOfList(){
	return tail;
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
// ==== remove ====
template <typename TYPE>
void List<TYPE>::remove(TYPE itemToRemove){
	ListNode<TYPE>* locationOfItemToBeRemoved = find(itemToRemove);
	if(locationOfItemToBeRemoved != nullptr){
		removeThisItem(locationOfItemToBeRemoved);
	}
}
// ====== removeThisItem ====
template <typename TYPE>
void List<TYPE>::removeThisItem(ListNode<TYPE>* removeFromHere){
	// list has one element to remove
	if( removeFromHere == head && removeFromHere == tail){
		delete head;
		head = tail = nullptr;
		listSize--;
	}
	else{
		// remove head
		if(removeFromHere == head){
			head = removeFromHere->getNext();
			head->setPrev(nullptr);
		}
		// remove tail
		else if(removeFromHere == tail){
			tail = removeFromHere->getPrev();
			tail->setNext(nullptr);
		}
		// remove something in the middle
		else{
			(removeFromHere->getPrev())->setNext( removeFromHere->getNext() );
			(removeFromHere->getNext())->setPrev( removeFromHere->getPrev() );
		}
		delete removeFromHere;
		listSize--;
	}
}
// ====== size ======
template <typename TYPE>
int List<TYPE>::size() const {
	return listSize;
}

// ==== erase ====
template <typename TYPE>
void List<TYPE>::erase(){
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
	erase();
}

// ====== is empty =====
template <typename TYPE>
bool List<TYPE>::isEmpty() const{
	if(listSize > 0)
		return false;
	else
		return true;
}
// ==== find ====
template <typename TYPE>
ListNode<TYPE>* List<TYPE>::find(TYPE dataKey) const {
	ListNode<TYPE>* iterator;
	if(isEmpty()){
		return nullptr;
	}
	iterator = head;
	if(iterator->getData() == dataKey){
		return iterator;
	}
	while(iterator->hasNext()){
		iterator = iterator->getNext();
		if(iterator->getData() == dataKey){
			return iterator;
		}
	}
	return nullptr;
}
// ===== search ========
template <typename TYPE>
bool List<TYPE>::search(TYPE dataKey) const {
	if(find(dataKey) != nullptr){
		return true;
	}
	else{
		return false;
	}
}
// ======= Iterator definition =======
template <typename TYPE>
void List<TYPE>::Iterator::getNext(){
	assert(ptr != nullptr);
	ptr = ptr->getNext();
}

template <typename TYPE>
void List<TYPE>::Iterator::getPrev(){
	assert(ptr != nullptr);
	ptr = ptr->getPrev();
}
template <typename TYPE>
TYPE List<TYPE>::Iterator::getData(){
	assert(ptr != nullptr);
	return ptr->getData();
}
template <typename TYPE>
void List<TYPE>::Iterator::startAtHead(){
	ptr = coupledList->headOfList();
}
template <typename TYPE>
void List<TYPE>::Iterator::startAtTail(){
	ptr = coupledList->tailOfList();
}
template <typename TYPE>
bool List<TYPE>::Iterator::end(){
	return ptr == nullptr;
}
template <typename TYPE>
void List<TYPE>::Iterator::operator=(List<TYPE>::Iterator sourceOfCopy){
	ptr = sourceOfCopy.ptr;
	coupledList = sourceOfCopy.coupledList;
}
template <typename TYPE>
List<TYPE>::Iterator::Iterator(){
	ptr = nullptr;
	coupledList = nullptr;
}
template <typename TYPE>
List<TYPE>::Iterator::Iterator(List<TYPE>* listToCoupleWith){
	coupledList = listToCoupleWith;
	ptr = nullptr;
}
#endif /* LIST_H_ */

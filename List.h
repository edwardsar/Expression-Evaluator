/* Alexander Edwards
 * CISP 430 Wednesday 6-9pm
 * Spring 2015
 * assignment #3
 */


#ifndef LIST_H_
#define LIST_H_
#include "ListNode.h"
#include <iostream>
// ======= class definition =======
template <typename TYPE>
class List {
public:
	enum ORDER { ASCENDING, DESCENDING, DEFAULT };
	enum BeforeOrAfter { Before, After};
	// ======= Iterator definition =======
	class ListIterator {
	public:
		void getNext(){ptr=ptr->getNext(); }
		void getPrev(){ptr=ptr->getPrev(); }
		TYPE getData(){return ptr->getData();}
		bool hasNext(){ return ptr->hasNext();}
		void start(){ ptr = ls->start(); }
		void end(){ ptr = ls->end();}
		bool isNull(){return ptr==nullptr;}
		ListIterator(List<TYPE>* coupleWith){ ls = coupleWith; ptr = nullptr;}
	private:
		ListNode<TYPE>* ptr;
		List<TYPE>* ls;
	};
	// === end Iterator definition =====
	List();
	virtual ~List();
	bool isEmpty() const;
	bool search(TYPE dataKey) const;
	int size() const;
	void insert(TYPE dataIn, ListNode<TYPE>* Where, BeforeOrAfter BA);
	void insert(TYPE dataIn);
	void remove(ListNode<TYPE>* removeFrom);
	bool isOrdered();
	TYPE peek(ListNode<TYPE>* peekAt);
	void makeOrderedList(ORDER x);
	bool isFull();
protected:
	ListNode<TYPE>* start();
	ListNode<TYPE>* end();
private:
	ListNode<TYPE> *head, *tail;
	int listSize;
	bool ordered;
	ORDER orderingFunction;
	void ascendingOrder(TYPE dataIn);
	void descendingOrder(TYPE dataIn);
};
/*******************************************************************************
 * It's best implementation not be in a header file but for ease of compiling  *
 * I kept in the header. I may move the implementation into a separate file.   *
 * That being said pretend it isn't here.                                      *
 *******************************************************************************/

// ==== isFull ====
// attempts to allocate memory with new, if successful it returns true.
template <typename TYPE>
bool List<TYPE>::isFull(){
	ListNode<TYPE>* temp= new ListNode<TYPE>();
	if(temp == nullptr){
		return true;
	}
	else{
		delete temp;
		return false;
	}
}
// ==== makeOrderedList ====
template <typename TYPE>
void List<TYPE>::makeOrderedList( ORDER x ){
	if (isEmpty()){
		ordered = true;
		orderingFunction = x;
	}
}
// ==== start ====
template <typename TYPE>
ListNode<TYPE>* List<TYPE>::start(){
	return head;
}
// ====== end ====
template <typename TYPE>
ListNode<TYPE>* List<TYPE>::end(){
	// insert behind element in one element list(end)
	// end = true
	return tail;
}
// ==== peek ====
template <typename TYPE>
TYPE List<TYPE>::peek(ListNode<TYPE>* peekAt){
	return peekAt->getData();
}
// ==== isSorted ====
template <typename TYPE>
bool List<TYPE>::isOrdered(){
	return ordered;
}
// ====== descendingOrder =======
template <typename TYPE>
void List<TYPE>::descendingOrder(TYPE dataIn){
	if(isEmpty()){
		insert(dataIn, head, Before);
	}
	else if(dataIn > head->getData()){
		insert(dataIn, head, Before);
	}
	else if(dataIn < tail->getData()){
		insert(dataIn, tail, After);
	}
	else{
		ListNode<TYPE>* currentNode = head;
		while ( !((dataIn < currentNode->getData()) && (dataIn >= currentNode->getNext()->getData()))){
			currentNode = currentNode->getNext();
		}
		insert(dataIn, currentNode, After);
	}
}
// ====== ascendingOrder =======
template <typename TYPE>
void List<TYPE>::ascendingOrder(TYPE dataIn){
	if(isEmpty()){

		insert(dataIn, head, Before);
	}
	else if(dataIn < head->getData()){

		insert(dataIn, head, Before);
	}
	else if( dataIn > tail->getData()){

		insert(dataIn, tail, After);
	}
	else {
		ListNode<TYPE>* currentNode = head;
		while ( !((dataIn > currentNode->getData()) && (dataIn <= currentNode->getNext()->getData()))){
			currentNode = currentNode->getNext();
		}
		insert(dataIn, currentNode, After);
	}
}
// ====== insert =======
template <typename TYPE>
void List<TYPE>::insert(TYPE dataIn){
	if(orderingFunction == ASCENDING)
		ascendingOrder(dataIn);
	else if(orderingFunction == DESCENDING)
		descendingOrder(dataIn);
	else
		insert(dataIn, head, Before);
}
// ====== insert =======
template <typename TYPE>
void List<TYPE>::insert(TYPE dataIn, ListNode<TYPE>* where, BeforeOrAfter BA){
	// special empty list case
	if( isEmpty() ){
		head = tail = new ListNode<TYPE>(dataIn,nullptr, nullptr);
	}
	else if( BA == Before){
		// insert before head
		if ( where->getPrev() == nullptr){
				head = new ListNode<TYPE>(dataIn,nullptr,head);
				head->getNext()->setPrev(head);
		}
		// insert before element pointed to by where
		else{
			where->getPrev()->setNext( new ListNode<TYPE>(dataIn, where->getPrev(), where->getNext()));
			where->getNext()->setPrev(where->getPrev()->getNext());
		}
	}
	else if( BA == After){
		// insert after tail
		if( where->getNext() == nullptr){
			tail = new ListNode<TYPE>(dataIn, tail, nullptr);
			tail->getPrev()->setNext(tail);
		}
		else{
			where->getNext()->setPrev( new ListNode<TYPE>(dataIn, where, where->getNext()));
			where->setNext(where->getNext()->getPrev());
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
		// remove from where iterator points
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

// ===== constructor ====
template <typename TYPE>
List<TYPE>::List() : head(nullptr), tail(nullptr),
					listSize(0), ordered(false),
					orderingFunction(DEFAULT){}

// ====== destructor ======
template <typename TYPE>
List<TYPE>::~List() {

	ListNode<TYPE> *it, *temp;
	it = head;
	while(it!=nullptr){
		temp = it;
		it=it->getNext();
		delete temp;
	}

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

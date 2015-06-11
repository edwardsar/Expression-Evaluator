// Author: Alexander Edwards


#ifndef LISTNODE_HPP_
#define LISTNODE_HPP_

// ============ class definition ================
template <typename TYPE>
class ListNode {
private:
	TYPE data;
	ListNode<TYPE> *prevNode, *nextNode;
public:
	ListNode(TYPE dataIn, ListNode<TYPE>* prev, ListNode<TYPE>* next);
	virtual ~ListNode();
	bool hasPrev() const;
	bool hasNext() const;
	TYPE getData() const;
	void setData(TYPE dataIn);
	ListNode<TYPE>* getNext() const;
	ListNode<TYPE>* getPrev() const;
	void setNext(ListNode<TYPE>* next);
	void setPrev(ListNode<TYPE>* prev);
};
/*******************************************************************************
 * It's best implementation not be in a header file but for ease of compiling  *
 * I kept in the header. I may move the implementation into a separate file.   *
 * That being said pretend it isn't here.                                      *
 *******************************************************************************/

// ====== setPrev ======
template <typename TYPE>
void ListNode<TYPE>::setPrev(ListNode<TYPE>* prev){
	prevNode = prev;
}
// ====== setNext ======
template <typename TYPE>
void ListNode<TYPE>::setNext(ListNode<TYPE>* next){
	nextNode = next;
}
// ====== getNext ======
template <typename TYPE>
ListNode<TYPE>* ListNode<TYPE>::getNext() const {
	if(hasNext())
		return nextNode;
	else
		return nullptr;
}

// ======= getPrev ======
template <typename TYPE>
ListNode<TYPE>* ListNode<TYPE>::getPrev() const {
	if(hasPrev())
		return prevNode;
	else
		return nullptr;
}
// ====== hasPrev ====
template <typename TYPE>
bool ListNode<TYPE>::hasPrev() const {
	if(prevNode != nullptr)
		return true;
	else
		return false;
}
// ======== setData =======
template <typename TYPE>
void ListNode<TYPE>::setData(TYPE dataIn){
	data = dataIn;
}
// ====== getData ======
template <typename TYPE>
TYPE ListNode<TYPE>::getData() const {
	return data;
}
// ====== hasNext ======
template <typename TYPE>
bool ListNode<TYPE>::hasNext() const {
	if( nextNode != nullptr)
		return true;
	else
		return false;
}

// ==== constructor ====
template <typename TYPE>
ListNode<TYPE>::ListNode(TYPE dataIn, ListNode<TYPE>* prev, ListNode<TYPE>* next):
	data(dataIn), prevNode(prev), nextNode(next)
{}
// ==== destructor =======
template <typename TYPE>
ListNode<TYPE>::~ListNode(){

}
#endif /* LISTNODE_H_ */

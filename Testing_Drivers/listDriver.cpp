#include "../List.hpp"
#include <iostream>
int main(void){
  List<int> intList;
  List<int>::Iterator itr;
  intList.append(2);
  intList.append(3);
  intList.prepend(1);
  intList.prepend(0);
  intList.prepend(8);
  itr = intList.getIterator();
  for(itr.startAtHead();!itr.end();itr.getNext()){
    std::cout << itr.getData() << ", ";
  }
  std::cout << std::endl;

  intList.remove(8);
  intList.remove(2);

  for(itr.startAtTail();!itr.end();itr.getPrev()){
    std::cout << itr.getData() << ", ";
  }
  std::cout << std::endl;
  std::cout << intList.search(3) << std::endl;
  std::cout << intList.search(8) << std::endl;
  return 0;
}

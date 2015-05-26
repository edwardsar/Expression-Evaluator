#include "../List.hpp"
#include <iostream>
int main(void){
  List<int> intList;
  List<int>::Iterator itr;
  intList.append(10);
  intList.prepend(3);
  itr = intList.getIterator();
  for(itr.startAtHead();!itr.end();itr.getNext()){
    std::cout << itr.getData() << std::endl;
  }
  return 0;
}

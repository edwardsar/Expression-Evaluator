#include "../Queue.hpp"
#include <iostream>
int main(void){
  Queue<int> intQueue;
  intQueue.enQueue(3);
  intQueue.enQueue(2);
  std::cout << intQueue.search(3) << std::endl;
  std::cout << intQueue.search(5) << std::endl;
  while(!intQueue.isEmpty()){
    std::cout << intQueue.deQueue() << ", ";
  }
  std::cout << std::endl;

  int i = 0;
  while(i < 100){
    intQueue.enQueue(i);
    i++;
  }

  while(!intQueue.isEmpty()){
    std::cout << intQueue.deQueue() << ", ";
  }
  std::cout << std::endl;
  return 0;
}

/*
 * author: Alexander Edwards
 */

#include "../Stack.hpp"
#include <iostream>

int main(void){
  Stack<int> intStack;

  intStack.push(2);
  intStack.pop();

  int i = 0;
  while(i<100){
    intStack.push(i);
    i++;
  }



  while(!intStack.isEmpty()){
    std::cout << intStack.pop() << ", ";
  }
  std::cout << std::endl;
  return 0;
}

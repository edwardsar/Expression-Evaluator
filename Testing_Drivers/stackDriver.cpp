/*
 * author: Alexander Edwards
 */

#include "../Stack.hpp"
#include <iostream>

int main(void){
  Stack<int> intStack;
  intStack.push(3);
  intStack.push(2);
  intStack.push(1);

  while(!intStack.isEmpty()){
    std::cout << intStack.pop() << std::endl;
  }
  return 0;
}

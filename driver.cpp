// Author: Alexander Edwards

#include "HashTable.hpp"
#include<iostream>
#include<string.h>
#include "ParseTable.hpp"
#include "Evaluator.hpp"
#include "Queue.hpp"

bool balanced(std::string input);

int main(void){
	HashTable<double> symbolTable;
	std::string input;
	Evaluator evaluator(&symbolTable);
	Queue<std::string> postfixQueue;
    ParseTable parsTable(&postfixQueue);
    std::cout << "\n==== Expression Evaluator ====" << std::endl;
    std::cout << "A symbol table is implemented so please define variables before use." << std::endl
    		  << "The evaluator is case sensitive and use parenthesis with functions." << std::endl
			  << "Do not enter negative values. Instead subtract value from zero." << std::endl
			  << "Example: (0 - 5) will allow you to work with negative values." << std::endl
    		  << "Enter \"quit\" to exit program.\n" << std::endl;

	std::cout << "Enter Expression\n> ";
	std::getline(std::cin, input);
	while(input!="quit" && balanced(input)){
		parsTable.convertToPostfix(input);
		std::cout << "EXP = " << evaluator.evaluatePostfix(&postfixQueue) << std::endl << std::endl;
		std::cout << "Enter Expression\n> ";
		std::getline(std::cin, input);
	}
	return 0;
}

bool balanced(std::string input){
	int x = 0;
	int size = input.size();
	for(int i =0; i<size; i++){
		if( input[i] ==  '('){
			x+=1;
		}
		else if(input[i] == ')'){
			x-=1;
		}
		if(x < 0){
			std::cout << "Error: Parenthesis unbalanced." << std::endl;
			return false;
		}
	}
	if(x==0)
		return true;
	else{
		std::cout << "Error: Parenthesis unbalanced." << std::endl;
		return false;
	}
}
